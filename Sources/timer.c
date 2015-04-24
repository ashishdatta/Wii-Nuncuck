//**************************************************************************************************************
// FILE: Timer.c
// Lab Project: 2
// AUTHORS
// Ashish Datta
// Adatta4@asu.edu
// Shane Nelson
// stnelso1@asu.edu
// CSE325 Embedded Microprocessor Systems
// Spring 2015
//**************************************************************
#include "support_common.h"
#include "timer.h"

//**********************************************************
// initialize the internal timer
// 
//**********************************************************
void dtim0_init()
{
	MCF_DTIM3_DTMR |= 0x0001; // Reset Timer
	MCF_DTIM3_DTMR &= 0xFFFE;
	MCF_DTIM3_DTMR = 0x4F02; // Set PS = 79, Clk Div = 1
	MCF_DTIM3_DTXMR = 0x40; // Set HALTED.
}

//**********************************************************
// set a delay for the timer given an input
// this input is in micro seconds
//**********************************************************
void dtim0_delay_us(int u)
{
	MCF_DTIM3_DTER = 0x03; // Clear Events
	MCF_DTIM3_DTCN = 0x00000000; // Clear Timer Counter
	MCF_DTIM3_DTRR = u-1;
	MCF_DTIM3_DTMR |= 0x0001;
	while ( !(MCF_DTIM3_DTER & 0x02)) {}

}