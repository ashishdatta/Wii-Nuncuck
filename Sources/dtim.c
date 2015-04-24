////**************************************************************************************************************
//// FILE: Timer.c
//// Lab Project: 2
//// AUTHORS
//// Ashish Datta
//// Adatta4@asu.edu
//// Shane Nelson
//// stnelso1@asu.edu
//// CSE325 Embedded Microprocessor Systems
//// Spring 2015
////**************************************************************
#include "support_common.h"
#include "dtim.h"
//
////**********************************************************
//// initialize the internal timer
//// 
////**********************************************************
void dtim_init(int n)
{  
    MCF_DTIM_DTMR(n) |= MCF_DTIM_DTMR_RST; // Reset timer
    MCF_DTIM_DTMR(n) &=  !MCF_DTIM_DTMR_RST;
    
    MCF_DTIM_DTMR(n) = (uint16)(MCF_DTIM_DTMR_PS(80-0x1) | MCF_DTIM_DTMR_CLK_DIV1);
    MCF_DTIM_DTXMR(n) = MCF_DTIM_DTXMR_HALTED;
}
//////**********************************************************
////// set a delay for the timer given an input
////// this input is in micro seconds
//////**********************************************************

void dtim_delay(int n, int u)
{
    MCF_DTIM_DTER(n) = MCF_DTIM_DTER_CAP | MCF_DTIM_DTER_REF;
    MCF_DTIM_DTCN(n) = MCF_DTIM_DTCR_CAP(0);
    MCF_DTIM_DTRR(n) = MCF_DTIM_DTRR_REF(u-0x1);
    MCF_DTIM_DTMR(n) |= MCF_DTIM_DTMR_RST;
    
    while (!(MCF_DTIM_DTER(n) & MCF_DTIM_DTER_REF)) {}
}