//**************************************************************************************************************
// FILE: pit.h
// Lab Project: 
// AUTHORS
// Ashish Datta
// Adatta4@asu.edu
// Shane Nelson
// stnelso1@asu.edu
// CSE325 Embedded Microprocessor Systems
// Spring 2015
//**************************************************************************************************************

#ifndef PIT_H_
#define PIT_H_

#include "int.h"

void pit0_enable();
void pit0_disable();
void pit1_enable();
void pit1_disable();
void pit0_clear_flag();
void pit1_clear_flag();
void pit1_init();
void pit0_init();
void pit_init(int pit, int pre, int pmr, int_isr callback);
void pit_enable(int pit);
void pit_disable(int pit);
void pit_clear(int pit);



#endif
