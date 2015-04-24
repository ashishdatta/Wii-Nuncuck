//**********************************************************
// init_state_PushSW.h
//
// AUTHORS
// Shane Nelson (stnelso1@asu.edu)
// Ashish Datta
// Adatta4@asu.edu
// CSE325 Embedded Microprocessor Systems
// Spring 2015
// Lab Project 3
// 
//**********************************************************

#ifndef INIT_STATE_PUSHSW_H_
#define INIT_STATE_PUSHSW_H_

//**********************************************************
// Takes an int value and intialize that switch
// Only useful for switches 1 and 2
//**********************************************************
void InitPushSW(unsigned int Switch);

//**********************************************************
// Read and return the state of the specified push button
// Returns 1 for high and 0 for low (opposite the actual button in hardware
//**********************************************************
int ReadPushSW(unsigned int Switch);

//**********************************************************
// Digital filter based switch debounce
// 
//**********************************************************
int debounce1();

int debounce2();

#endif /* INIT_STATE_PUSHSW_H_ */
