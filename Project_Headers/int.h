//**********************************************************************************************************************************
// FILE: int.h
//
// DECRIPTION
// Public declarations for interrupt controller functions. The functions are written in assembly language and are found in int.s.
// Note that all of the functions are declared using the standard_abi calling convention.
//
// AUTHORS
// Kevin R. Burger (burgerk@asu.edu)
// Computer Science & Engineering
// Arizona State University, Tempe, AZ 85287-8809
// http://www.devlang.com
//**********************************************************************************************************************************
#ifndef INT_H
#define INT_H

//==================================================================================================================================
// Global Type Definitions
//==================================================================================================================================

// This typedef defines a function pointer type named int_isr.
typedef void (*int_isr)();

//==================================================================================================================================
// Public Function Declarations
//==================================================================================================================================

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(standard_abi) void int_config(int p_src, int p_level, int p_priority, int_isr p_isr)
// 
// DESCRIPTION
// Configures interrupt source p_src to have level p_level, priority p_priority. The address of the ISR in p_isr is placed in the
// exception vector table.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(standard_abi) void int_config(int p_src, int p_level, int p_priority, int_isr p_isr);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(standard_abi) void int_hibit_all()
// 
// DESCRIPTION
// Writes 111 to SR[I] to inhibit interrupt requests from all levels.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(standard_abi) void int_inhibit_all();

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(standard_abi) void int_mask_src(int p_src)
// 
// DESCRIPTION
// Masks interrupt requests from the interrupt source p_src by writing a 1 to the appropriate bit in either the IMRH (if p_src > 31)
// or IMRL (if p_src <= 31) register.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(standard_abi) void int_mask_src(int p_src);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(standard_abi) void int_unmask_src(int p_src)
// 
// DESCRIPTION
// Unmasks interrupt requests from the interrupt source p_src by writing a 0 to the appropriate bit in either the IMRH (if p_src >
// 31) or IMRL (if p_src <= 31) register.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(standard_abi) void int_unmask_src(int p_src);

//----------------------------------------------------------------------------------------------------------------------------------
// FUNCTION: __declspec(standard_abi) void int_unhibit_all()
// 
// DESCRIPTION
// Writes 000 to SR[I] to permit interrupt requests from all levels.
//----------------------------------------------------------------------------------------------------------------------------------
__declspec(standard_abi) void int_uninhibit_all();

#endif
