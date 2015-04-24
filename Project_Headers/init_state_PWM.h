//**************************************************************************************************************
// FILE: init_state_PWM.h
// Lab Project: 3
// AUTHORS
// Ashish Datta
// Adatta4@asu.edu
// Shane Nelson
// stnelso1@asu.edu
// CSE325 Embedded Microprocessor Systems
// Spring 2015
//**************************************************************************************************************

#ifndef INIT_STATE_PWM_H_
#define INIT_STATE_PWM_H_

void initPWM();

void setPWM();

void clkSelect();

void initPreScaleClk();

void initScaleClk();

void disablePWM();

void enablePWM();

void setPolarity(int RGB, int state);

void setPeriod();

void initDuty();

#endif /* INIT_STATE_PWM_H_ */
