////**************************************************************************************************************
//// FILE: pit.c
//// Lab Project: 3 
//// AUTHORS
//// Ashish Datta
//// Adatta4@asu.edu
//// Shane Nelson
//// stnelso1@asu.edu
//// CSE325 Embedded Microprocessor Systems
//// Spring 2015
////**************************************************************************************************************
//
#include "support_common.h"
#include "pit.h"
#include "int.h"
#include "dtim.h"
//
///* 
//	ENABLE Programmable Interrupt Timer 
//	- 24-4
//*/
void pit_enable(int pit)
{
	MCF_PIT_PCSR(pit) |= 0x0001;
}


///* 
//	DISABLE Programmable Interrupt Timer 
//	- 24-4
//*/
void pit0_disable(int pit)
{
	MCF_PIT_PCSR(pit) &= ~(MCF_PIT_PCSR_EN);
}

///* 
//	Clear PIF by writing a 1 to it or by
//	writing to PMR. Writing 0 has no effect. Reset clears PIF. 
//	- 24-4
//*/ 
void pit_clear(int pit)
{
	MCF_PIT_PCSR(pit) |= MCF_PIT_PCSR_PIF;
}

void pit_init(int pit, int pre, int pmr, int_isr callback)
{
    MCF_PIT_PCSR(pit) = 0x003E;
    MCF_PIT_PCSR(pit) |= pre << 0x8 ;  
    MCF_PIT_PMR(pit)  = pmr;
                    
    int_config(55 + pit, 1, 7, callback);
}

//void pit0_init(int pit, int pre, int pmr, int_isr callback)
//{	
//	// disable timer
////	pit0_disable(); 
//
//	//clear flag
//	//pit0_clear_flag();
//	
//	// enable PIT interrupts. NOTE: Use MCF_PIT_PCSR_PIE when ENABLING the interrupt, not the module
////	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PIE;
////
////	/* 
////		System reset and the loading of a new value into the counter also reset the
////		prescaler counter. Setting the EN bit and writing to PRE[3:0] can be done in this same write cycle. Clearing the EN
////		bit stops the prescaler counter
////	*/
////	MCF_PIT0_PCSR |= MCF_PIT_PCSR_PRE(pre);
////
////	/* ENABLE debug mode 
////	   NOTE: Changing the DBG bit from 1 to 0 during debug mode starts the PIT timer. Likewise, changing the DBG bit
////	   from 0 to 1 during debug mode stops the PIT timer
////	 */
////	MCF_PIT0_PCSR |= MCF_PIT_PCSR_DBG;
////
////	/*
////		ENABLE OVERRWRITE
////		NOTE: Overwrite. Enables writing to PMRn to immediately overwrite the value in the PIT counter.
////	*/
////	MCF_PIT0_PCSR |= MCF_PIT_PCSR_OVW;
////
////	/*
////		ENABLE RELOAD
////		NOTE: Reload bit. The read/write reload bit enables loading the value of PMRn into PIT counter when the count reaches
////		0x0000.
////	*/
////	MCF_PIT0_PCSR |= MCF_PIT_PCSR_RLD;
////
////	/* SET modulus to 20000 
////		@todo change val  
////	*/
////	MCF_PIT0_PCSR = MCF_PIT_PMR(pmr); 
//    
//    MCF_PIT_PCSR(pit) = ((pre & 0xF) << 0x8) | 0x003E;
//    MCF_PIT_PCSR(pit) = pmr; 
//
//	int_config(55+ pit, 1 , 7 ,callback); //Configure the ISR for the PIT0 module
//}
//
//void pit1_init(int pit, int pre, int pmr, int_isr callback)
//{	
////	// disable timer
////	//pit1_disable(); 
////
////	//clear flag
////	//pit1_clear_flag();
////	
////	// enable PIT interrupts. NOTE: Use MCF_PIT_PCSR_PIE when ENABLING the interrupt, not the module
////	MCF_PIT1_PCSR |= MCF_PIT_PCSR_PIE;
////
////	/* 
////		System reset and the loading of a new value into the counter also reset the
////		prescaler counter. Setting the EN bit and writing to PRE[3:0] can be done in this same write cycle. Clearing the EN
////		bit stops the prescaler counter
////	*/
////	MCF_PIT1_PCSR |= MCF_PIT_PCSR_PRE(pre);
////
////	/* ENABLE debug mode 
////	   NOTE: Changing the DBG bit from 1 to 0 during debug mode starts the PIT timer. Likewise, changing the DBG bit
////	   from 0 to 1 during debug mode stops the PIT timer
////	 */
////	MCF_PIT1_PCSR |= MCF_PIT_PCSR_DBG;
////
////	/*
////		ENABLE OVERRWRITE
////		NOTE: Overwrite. Enables writing to PMRn to immediately overwrite the value in the PIT counter.
////	*/
////	MCF_PIT1_PCSR |= MCF_PIT_PCSR_OVW;
////
////	/*
////		ENABLE RELOAD
////		NOTE: Reload bit. The read/write reload bit enables loading the value of PMRn into PIT counter when the count reaches
////		0x0000.
////	*/
////	MCF_PIT1_PCSR |= MCF_PIT_PCSR_RLD;
////
////	/* SET modulus  
////	*/
////	MCF_PIT1_PCSR = MCF_PIT_PMR(pmr);
//    MCF_PIT_PCSR(pit) = ((pre & 0xF) << 0x8) | 0x003E;
//    MCF_PIT_PCSR(pit) = pmr; 
//	int_config(55 + pit, 1, 7, callback);
//
//}