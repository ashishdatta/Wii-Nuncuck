//**************************************************************************************************************
// FILE: Timer.h
// Lab Project: 2
// AUTHORS
// Josh Mazion
// Jmmazion@asu.edu
// Shane Nelson
// stnelso1@asu.edu
// CSE325 Embedded Microprocessor Systems
// Spring 2015
//**************************************************************

#ifndef TIMER_H_
#define TIMER_H_

//**********************************************************
// initialize the internal timer
// 
//**********************************************************
void dtim0_init();

//**********************************************************
// set a delay for the timer given an input
// this input is in micro seconds
//**********************************************************
void dtim0_delay_us(int u);

#endif /* TIMER_H_ */
