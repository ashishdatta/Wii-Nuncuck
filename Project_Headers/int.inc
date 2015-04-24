;***********************************************************************************************************************************
; FILE: int.inc
;
; DESCRIPTION
; Contains function and constant declarations for functions defined in int.s.
;
; AUTHORS
; Kevin R. Burger (burgerk@asu.edu)
; Computer Science & Engineering
; Arizona State University
; Tempe, AZ 85287-8809
; http://www.devlang.com
;***********************************************************************************************************************************

;===================================================================================================================================
; Public Constants
;===================================================================================================================================

; GPT channel 0 is interrupt source 44. The level and priority are set to 1 and 7.
gpt0_int_src:       .equ  44
gpt0_int_level:     .equ   1
gpt0_int_priority:  .equ   7

; GPT channel 1 is interrupt source 45. The level and priority are set to 1 and 6.
gpt1_int_src:       .equ  45
gpt1_int_level:     .equ   1
gpt1_int_priority:  .equ   6

;=================================================================================================================
; Public Function Declarations
;=================================================================================================================
.extern _int_config
.extern _int_inhibit_all
.extern _int_mask_src
.extern _int_unmask_src
.extern _int_uninhibit_all
