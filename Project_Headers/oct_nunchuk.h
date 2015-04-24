// CSE325 - Project 4
// Authors: Ashish Datta <adatta4@asu.edu>, Shane Nelson <stnelso1@asu.edu>
// File: oct_nunchuck.h
// ASU 
#ifndef OCT_NUNCHUK_H
#define OCT_NUNCHUK_H

#define OCT_NUNCHUK_BUTTON_C 0x02 // Button C is in bit 1 of last rx byte
#define OCT_NUNCHUK_BUTTON_Z 0x01 // Button Z is in bit 0 of last rx byte

#define OCT_NUNCHUK_I2C_ADDR 0x52 // Wii Nunchuck I2C address
#define OCT_NUNCHUK_I2C_DELAY_US 150 // We have to delay 150 us after I2C byte transfers/receipts
#define OCT_NUNCHUK_REFRESH_FREQ_HZ 4

#define OCT_NUNCHUK_REG_F0 0xF0
#define OCT_NUNCHUK_REG_FB 0xFB
#define OCT_NUNCHUK_REG_NONE 0x00

#define OCT_NUNCHUK_STICK_LEFT_MAX 30
#define OCT_NUNCHUK_STICK_RIGHT_MIN 225
#define OCT_NUNCHUK_STICK_DOWN_MAX 30
#define OCT_NUNCHUK_STICK_UP_MIN 225

static int g_accel_x;  // x-axis acceleration
static int g_accel_y;  // y-axis acceleration
static int g_accel_z;  // z-axis acceleration
static int g_button_c; //1 if button C is pressed, 0 if button C is not pressed
static int g_button_z; //1 if button Z is pressed, 0 if button Z is not pressed
static int g_pos_x;   //Joystick x-axis (left/right) position 
static int g_pos_y;  //Joystick y-axis (up/down) position

 

	/* 
		RETURN X-axis acceleration value
	*/
	int oct_nunchuk_accel_x();
	/* 
		RETURN Y-axis acceleration value 
	*/
	int oct_nunchuk_accel_y();
	/* 
		RETURN Z-axis acceleration value 
	*/
	int oct_nunchuk_accel_z();
	/* 
		RETURN state of button C 
	*/
	int oct_nunchuk_button_c();
	/* 
		RETURN state of button Z
	*/
	int oct_nunchuk_button_z();
	/* 
		Initialize the Octopus Nunchuk module and the I2C module for communication
		with the Wii Nunchuk. Configures PIT 1 to generate periodic interrupts at 4 Hz (every 250 ms).
	*/
	void oct_nunchuk_init();
	/*
		Will save a callback function pointer for the user's function which is
		to be called when Nunchuk button C is pressed.
	*/
	void oct_nunchuk_on_button_c();
	/*
		Will save a callback function pointer for the user's function which is
		to be called when Nunchuk button Z is pressed.
	*/
	void oct_nunchuk_on_button_z();
	/* 
		Will save a callback function pointer for the user's function which is
		to be called when the Nunchuk joystick is moved to the DOWN position. 
	*/
	void oct_nunchuk_on_stick_down();
	/* 
		Will save a callback function pointer for the user's function which is
		to be called when the Nunchuk joystick is moved to the LEFT position. 
	*/
	void oct_nunchuk_on_stick_left();
	/* 
		Will save a callback function pointer for the user's function which is
		to be called when the Nunchuk joystick is moved to the RIGHT position. 
	*/
	void oct_nunchuk_on_stick_right();
	/* 
		Will save a callback function pointer for the user's function which is
		to be called when the Nunchuk joystick is moved to the UP position. 
	*/
	void oct_nunchuk_on_stick_up();
	/*
		Return the joystick x-axis (left/right) position
	*/
	int oct_nunchuk_pos_x();
	/*
		Return the joystick x-axis (left/right) position
	*/
	int oct_nunchuk_pos_y();
	/*
		Called every 250 ms by the PIT 1 interrupt service routine. This function
		reads the current state of the Nunchuk, stores the state information in global variables, and calls the user's callback
		functions as appropriate.
	*/
	void oct_nunchuk_read();
	/*
		Resets all of the callback function pointers to null.
	*/
	void oct_nunchuk_reset();
	/*
		Transmits a command to the Nunchuk.
	*/
	void oct_nunchuk_tx_cmd(uint8 reg, uint8 cmd);
#endif