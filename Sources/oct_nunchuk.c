// CSE325 - Project 4
// Authors: Ashish Datta <adatta4@asu.edu>, Shane Nelson <stnelso1@asu.edu>
// File: oct_nunchuck.c
// ASU 

#include <support_common.h>
#include "oct_nunchuk.h"
#include "i2c.h"
#include "pit.h"
#include "dtim.h"

static i2c_mod g_i2c_mod; //The I2C module used to communicate with the nunchuck

/* Return X-Axis Acceleration */
int oct_nunchuk_accel_x()
{
	return g_accel_x;  
}

/* Return Y-Axis Acceleration */
int oct_nunchuk_accel_y()
{
	return g_accel_y;
}

/* Return Z-Axis Acceleration */
int oct_nunchuk_accel_z()
{
	return g_accel_z;
}

/* Return 1 if C-Button is pressed and 0 if not */
int oct_nunchuk_button_c()
{
	return g_button_c;
}

/* Return 1 if Z-Button is pressed and 0 if not */
int oct_nunchuk_button_z()
{
	return g_button_z;
}

/*  
  	 oct_nunchuk_init: Initializes the MCF52259 hardware so we can read the Nunchuk state information. We use DMA timer 3
 	 to implement a busy delay for OCT_NUNCHUK_I2C_DELAY_US μs following the transfer and receipt of data bytes to and
	 from the Nunchuk. We use PIT timer 1 to generate periodic interrupts at OCT_NUNCHUK_REFRESH_FREQ_HZ Hz. On each
     interrupt oct_nunchuk_read will be called to read the Nunchuk state. 
*/
void oct_nunchuk_init(i2c_mod p_i2c_mod)
{
	g_i2c_mod = p_i2c_mod;
	dtim_init(3); // Initialize DTIM3
	/*
	  init I2C module g_i2c_mod for I2C Standard Mode (100Kbps). Configure the MCF52259 I2C slave address to 8.
	  100 KHZ
	*/
	i2c_init(g_i2c_mod, 100 , 8);
	
	/* Transmit command 0x55 to nunchuk register 0xF0 (note: we are master-transmitter) */
	oct_nunchuk_tx_cmd(OCT_NUNCHUK_REG_F0, 0x55);
	
	/* Transmit command 0x00 to nunchuk register 0xFB (note: we are master-transmitter) */
	oct_nunchuk_tx_cmd( OCT_NUNCHUK_REG_FB, 0x00);
	
	/* Configure PIT1 to generate interrupts at OCT_NUNCHUK_REFRESH_FREQ_HZ with oct_nunchuck_read as the callback */
	pit_init(1, 11, 4883, &oct_nunchuk_read);
}   

/* Return the joystick x-axis (left/right) position */
int oct_nunchuk_pos_x()
{
	return g_pos_x;
}

/* Return the joystick y-axis (up/down) position */
int oct_nunchuk_pos_y()
{
	return g_pos_y;
}

/* 
  Called at OCT_NUNCHUK_REFRESH_FREQ_HZ by the PIT timer 1 interrupt service routine. 
  We read the nunchuck state information using the nunchuk protocol Call user callback functions as appropriate
*/
__declspec(interrupt) static void oct_nunchuk_read()
{
	uint8 data[6];
	MCF_PIT_PCSR(1) |= 0x0004; //clear flag
	/* Transmit command 0x00 (note: we are master transmitter) */
	oct_nunchuk_tx_cmd(OCT_NUNCHUK_REG_NONE, 0x00);
	
	/* The nunchuck is now ready to send the six bytes of data. We read the data as master-receiver. 
	 * The data is returned in the array data which is an array of size six. For reasons I do not understand
	 * We hae to delay in between data bytes. I discovered by trial-and-error that 150us (OCT_NUCHUK_I2C_DELAY_US) works well
	 * Define data as 6-element array of uint8
	 */ 
	i2c_rx(g_i2c_mod, OCT_NUNCHUK_I2C_ADDR, 6, OCT_NUNCHUK_I2C_DELAY_US, data);
	
	/* The first two bytes are the joystick x-axis and y-axis positions */
	g_pos_x = data[0];
	g_pos_y = data[1];
	
	/* data[1], data[2], data[3] are the most significant 8-bit for the 10-bit x, y and z acceleration values
	 * The least significant 2 bits are in data[5]
	*/
	g_accel_x = (int)(data[2] << 2 | (data[5] & 0x0C) >> 2 ); // x-axis accel. from bits 7:0 of data[2] and bits 3:2 of data[5]
	g_accel_y = (int)(data[3] << 2 | (data[5] & 0x30) >> 4 );; // y-axis accel. from bits 7:0 of data[3] and bits 5:4 of data[5]
	g_accel_z = (int)(data[4] << 2 | (data[5] & 0xC0) >> 6 ); // z-axis accel. from bits 7:0 of data[4] and bits 7:6 of data[5]
	
	//button C
	if (data[5] & 0x02)
	    g_button_c = 0;
	  else
	    g_button_c = 1;

	  // button Z
	  if (data[5] & 0x01)
	    g_button_z = 0;
	  else
	    g_button_z = 1;
}

/* Transmits command cmd to nunchuk register reg. 
 * If reg is OCT_NUNCHUK_REG_NONE (because the command is not sent to Nunchuk register, 
 * then we only transmit 1 Byte, which is command. 
 * For Reasons 1 I do not understand we have to delay after transmitting. I discovered by trial and error that 300 us (2 x OCT_NUNCHUK_DELAY_US works well) 
 */
void oct_nunchuk_tx_cmd(uint8 reg, uint8 cmd)
{
	uint8 tx_data[2];
	int tx_count;
	if(reg != OCT_NUNCHUK_REG_NONE)
	{
		tx_data[0] = reg;
		tx_data[1] = cmd;
		tx_count = 2;
	}
	else
	{
		tx_data[0] = cmd;
		tx_count = 1;
	}
	
	i2c_tx(g_i2c_mod, OCT_NUNCHUK_I2C_ADDR, tx_count, OCT_NUNCHUK_I2C_DELAY_US, tx_data);
	dtim_delay(3, 300); // USe DMA TImer 3 to busy delay for 2 x OCT_NUNCHUK_US us
}
