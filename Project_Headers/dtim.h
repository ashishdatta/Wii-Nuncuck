//**************************************************************************************************************
// FILE: DTIM.h
// Lab Project: 2
// AUTHORS
// Josh Mazion
// Jmmazion@asu.edu
// Shane Nelson
// stnelso1@asu.edu
// CSE325 Embedded Microprocessor Systems
// Spring 2015
//**************************************************************

#ifndef DTIM_H_
#define DTIM_H_

//**********************************************************
// initialize the internal timer
// 
//**********************************************************
void dtim_init(int n);

//**********************************************************
// set a delay for the timer given an input
// this input is in micro seconds
//**********************************************************
void dtim_delay(int n, int u);

#endif /* DTIM_H_ */
