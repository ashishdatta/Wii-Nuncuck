// CSE325 - Project 4
// Authors: Ashish Datta <adatta4@asu.edu>, Shane Nelson <stnelso1@asu.edu>
// File: i2c.h
// ASU 

#include "support_common.h"
#include "i2c.h"
#include "pit.h"
#include "int.h"
#include "dtim.h"


/*
	Busy-waits until the I2C bus is idle
*/
void i2c_acquire_bus(i2c_mod n)
{
	//MCF_I2Cn_I2SR if we use MCF_I2C2_I2SR
	// While I2Cn_I2SR[IBB] is Set Do Nothing 
	while(MCF_I2C_I2SR(n) & MCF_I2C_I2SR_IBB) {} 
}
/*
	 Initializes ColdFire I2C module n so: (1) The I2C clock frequency is freq with freq in [21, 4000] KHz;
	 (2) The MCF52259 is configured for slave-receiver mode; (3) The MCF52259 I2C address is p_addr; and (4) I2C
	 interrupts are disabled.
*/
void i2c_init(i2c_mod n, int frequency, int addr)
{
    uint8 dummy; 
	if (n == i2c_mod_0) //if R/W bit is set to READ
	{
		/* 
			Configure GPIO port AS pin 0 (I2C_SCL0) for the primary (I2C) function; CLEAR PASPAR0 
											& 
			Configure GPIO port AS pin 1 (I2C_SDA0) for the primary (I2C) function; clear PASPAR1
		*/
		MCF_GPIO_PASPAR &= 0xF0;
        MCF_GPIO_PASPAR |= 0x05;
	}
	else // R/W bit is set to WRITE
	{
		MCF_GPIO_PUBPAR &= 0xF0;
		MCF_GPIO_PUBPAR |= 0x0A;
	}

	/* Choose I2C address to I2Cn_ADR[ADR]*/
	MCF_I2C_I2ADR(n) = MCF_I2C_I2ADR_ADR(addr);
	
	/* 
		Write ic to I2Cn_I2FDR[IC] 
		divider â†� (fsys MHz Ã— 1000 KHz per MHz) / freq KHz
		ic â†� IC value from Table 29-3 corresponding to divider. If divider does not appear in Table 29-3 then choose the
 		smallest value for divider from Table 29-3 that is greater than divider.
 		
 		Assuming 0.1 MHZ. 80MHZ / 0.1 MHZ = 800 
 	*/
	MCF_I2C_I2FDR(n) = 0x3A;

	/* Reset the I2C module to its inital state which is as slave-receiver, interrupts disabled. */
	i2c_reset(n);

	/* If I2Cn_I2SR[IBB] is Set Then */
	if(MCF_I2C_I2SR(n) & MCF_I2C_I2SR_IBB)
	{
		MCF_I2C_I2CR(n) = 0x00; //Write 0x00 to I2Cn_I2CR -- I2C module is disabled; MCF52259 is slave-receiver
		MCF_I2C_I2CR(n) = 0xA0; //Write 0xA0 to I2Cn_I2CR -- I2C module is enabled ; MCF52259 is master-receiver; Sends start bit
		dummy = MCF_I2C_I2DR(n); //dummy â†� I2Cn_I2DR -- Perform a dummy read from the slave which is transmitting
		MCF_I2C_I2SR(n) = 0x00; //Write 0x00 to I2Cn_I2SR -- Clear I2C arbitration lost flag; Clear the I2C interrupt request flag
		MCF_I2C_I2CR(n) = 0x00; //Write 0x00 to I2Cn_I2CR -- I2C module is disabled; MCF52259 is slave-receiver; Sends stop bit
		MCF_I2C_I2CR(n) = 0x80; //Write 0x80 to I2Cn_I2CR -- Enable the I2C module.
	}
}

/* 
	When not acting as master-transmitter, the MCF52259 I2C module should be configured for slave-receiver
 	mode. This function configures I2CR so the MCF52259 will be in slave-receiver mode, interrupts are disabled (we are
 	going to use polling to determine when transfers complete), received data bytes will be automatically ACKed, and the
 	I2C module is enabled. 
*/

void i2c_reset(i2c_mod n)
{
	MCF_I2C_I2CR(n) |= MCF_I2C_I2CR_IEN;     //Set IEN to enable the I2C module
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_IIEN);   //Clear IIEN to disable I2C interrupts -- we are going to use polling to determine when transfers complete 
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_MSTA);  //Clear MSTA to make the MCF52259 a slave
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_MTX);  //Clear MTX to make the MCF52259 a slave-receiver
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_TXAK); //Clear TXAK so received data/address bytes will be automatically ACKed
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_RSTA); //Clear RSTA so Repeated Start bits will not be generated
}

/* 
	Reads and returns count data bytes from the slave addressed by addr. The data bytes are stored and returned
	in the array data. Busy waits for delay_us Î¼s following each transferred data or address byte. This is necessary as
	some I2C devices require a delay between reads.
*/

void i2c_rx(i2c_mod n, uint8 addr, int count, int delay_us, uint8 *data)
{
	int i; //Variable in for loop
	uint8 dummy; 
	/* Busy wait while waiting for the I2C bus to become idle*/
	i2c_acquire_bus(n);

	/* Transmits start bit, slave address, and R/W bit = read */
	i2c_tx_addr(n, addr, I2C_READ, delay_us);

	/* 
		The addressed slave ACKed our request to initiate a read, so clear I2CR[MTX] to become master-receiver. Note: we
		are already master-transmitter because i2c_tx_addr configures the I2C module for that mode.
	*/
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_MTX);

	/* 
		As master-receiver, we must ACK each received data byte except for the last which must be NACKed to tell the slave
		to stop transmitting. Clear I2CR[TXAK] to automatically ACK each received data byte.
	*/
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_TXAK);

	/*
		When we switch from master-transmitter mode to slave-receiver mode, we have to read a dummy byte from the I2C
		module. Why? I dunno but that's what the IMRM says in Â§29.4.6. 
	*/
	dummy = i2c_rx_byte(n, delay_us); // dummy â†� i2c_rx_byte(n, delay_us)

	/* 
		For i â†� 1 to count Do
		If i is count - 1 Then
		Set I2Cn_I2CR[TXAK] -- NACK penultimate byte.
		ElseIf i is count Then
		Call i2c_send_stop -- Send stop bit before reading last byte.
		EndIf
		data[i-1] â†� i2c_rx_byte(n, delay_us)
		End For
	*/
	for(i = 1; i <= count ; i++)
	{
		if(i == (count -1))
		{
			MCF_I2C_I2CR(n) |= MCF_I2C_I2CR_TXAK; // NACK penultimate byte.
		}
		else if(i == count)
		{
			i2c_send_stop(n); // Send stop bit before reading last byte
		}

		//data[i-1] â†� i2c_rx_byte(n, delay_us)
		data[i-1] = i2c_rx_byte(n, delay_us);
	}

	/*
		End the communication by switching back to slave-receiver mode. Note: the stop bit has already been sent.
	*/
	i2c_reset(n);
}

/*
	Receives one data byte from the slave-transmitter and returns it. Delays for delay_us Î¼s following the
	transfer. If delay_us is 0 we do not delay. 
*/
uint8 i2c_rx_byte(i2c_mod n, int delay_us)
{ 
	/* 
		When in master-receiver mode, reading from I2DR initiates the reception of the next data byte from the slave by
		generating 9 clock pulses on SCL. We automatically ACK or NACK on the 9th clock pulse depending on I2CR[TXAK].
	*/
	uint8 rx_byte;
	rx_byte = MCF_I2C_I2DR(n);

	/* 
		Clear the I2C irq flag which is set when a byte is received
		Clear I2Cn_I2CR[IIF]
	*/
	MCF_I2C_I2SR(n) &= ~(MCF_I2C_I2SR_IIF); // Clear interrupt request flag


	/*  Some devices require a delay between sending data bytes. */
	dtim_delay(0, delay_us);


	/*  Return the data byte that was received.  */
	return rx_byte;

}

/* Sends the stop bit prior to ending the communication. */
void i2c_send_stop(i2c_mod n )
{
	/* Clear I2Cn_I2CR[MSTA] -- Clear I2CR[MSTA] to become slave-receiver. The 1-to-0 transition sends the stop bit. */
	MCF_I2C_I2CR(n) &= ~(MCF_I2C_I2CR_MSTA);  //Clear MSTA to make the MCF52259 a slave
}

/* 
	Transmits count data bytes (stored in the array data) to the slave with address addr. Busy delay for delay_us
	Î¼s following each transferred byte as some devices require a delay between data bytes.
*/
void i2c_tx(i2c_mod n, uint8 addr, int count, int delay_us, uint8 *data)
{
    int i;
	/*  
		Busy wait while waiting for the I2C bus to become idle 
		Call i2c_acquire_bus(n)
	*/
	i2c_acquire_bus(n);

	/* Transmits start bit, slave address, and R/W bit = Write. */
	i2c_tx_addr(n, addr, I2C_WRITE, delay_us);

	/*
		Send each data byte in sequence delaying for delay_us after each byte is sent.
		For i â†� 0 to count - 1 Do
		i2c_tx_byte(n, data[i], delay_us)
		End For
	*/
	for(i = 0; i < count ; i++)
	{
		i2c_tx_byte(n, data[i], delay_us);
	}

	/*  End the communication by sending the stop bit and resetting the I2C module to be in slave-receiver mode. */
	i2c_send_stop(n);
	i2c_reset(n);
}

/* 
	Begins a transmission to the slave with address addr. This function will place the MCF52259 I2C module
	into master-transmitter mode, transmit the slave address addr, and transmit the R/W bit set to rw. Note: The I2C bus
	should be acquired by calling i2c_acquire_bus before calling this function.
*/
void i2c_tx_addr(i2c_mod n, uint8 addr, uint8 rw , int delay_us)
{
	uint8 tx_byte = 0; //
	/* 
		Configure MCF52259 to be master-transmitter which sends start bit. Note: i2c_reset has initialized I2CR so the
		I2C module is enabled (IEN = 1) for slave-receiver mode (MSTA = 0, MTX = 0) with interrupts disabled (IIEN = 0).
	*/
	MCF_I2C_I2CR(n) |= MCF_I2C_I2CR_MTX;
	MCF_I2C_I2CR(n) |= MCF_I2C_I2CR_MSTA;

	/* 
		Transfer the slave address followed by R/W = Write.
		tx_byte[7:1] â†� addr; tx_byte[0] â†� rw
		Return i2c_tx_byte(n, tx_byte, delay_us)
	*/
	tx_byte = addr << 0x1; // tx_byte[7:1] â†� addr
	tx_byte |= rw  &  0x01; // tx_byte[0] â†� rw

	i2c_tx_byte(n, tx_byte, delay_us);
}

/*
	Transmits one byte (either 8-bits of data or a 7-bit address followed by the R/W bit) to a slave. Busy
 	delays for delay_us Î¼s following the transfer as some slaves require a delay between bytes. After the ninth
 	SCL clock pulse, the slave will either ACK or NACK the byte. Note: I2
	C is exquisitely sensitive to timing, so
 	interrupts from all levels are inhibited while the transfer takes place.
*/

void i2c_tx_byte(i2c_mod n, uint8 tx_byte, int delay_us)
{
	int_inhibit_all(); //Inhibit interrupts at all levels while the transfer takes place
	MCF_I2C_I2DR(n) = tx_byte; // Transmit the byte
	while (!i2c_tx_complete(n)){ } // Busy wait for a transfer to complete
	MCF_I2C_I2SR(n) &= ~(MCF_I2C_I2SR_IIF);  // Clear the I2C transfer complete interrupt request flag
	int_uninhibit_all(); // Uninhibit interrupts at all levels
	dtim_delay(0, delay_us); // Post-transfer delay
}

/* 
	Returns true if the transfer of a data or address byte has completed or false if it is still in
 	progress. Note: You might think that you would check for transfer complete by examining I2SR[ICF] but if you read
 	Â§29.4.3 the IMRM tells you that I2SR[IIF] is also set when a transfer completes. Continuing, the second sentence of
 	the second paragraph states, "Polling should monitor IIF rather than ICF, because the operation is different when
 	arbitration is lost". Whatever.
*/

int i2c_tx_complete(i2c_mod n)
{
	//Return I2Cn_I2SR[IIF] == 1
	return (MCF_I2C_I2SR(n) & MCF_I2C_I2SR_IIF) >> 0x1;
}