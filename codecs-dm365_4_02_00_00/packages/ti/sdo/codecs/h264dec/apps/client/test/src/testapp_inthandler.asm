;/*
;******************************************************************************
;*  
;* DM36x Based H.264 Decoder Test Application
;*
;* "DM36x Based H.264 Decoder Test application is software module developed on TI's DM36x.
;* This module shows XDM interface for H.264 Video Decoder.
;* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
;* ALL RIGHTS RESERVED 
;******************************************************************************
;*/
;/** ==========================================================================
; *   @file   testapp_inthandler.asm
; *
; *   @path   $(PROJDIR)\client\test\src
; *
; *   @brief  This File contains low level interrupt handler. 
; * ===========================================================================
; */
;
;/* -------------------- compilation control switches -----------------------*/
;
;
;/****************************************************************************
;*   INCLUDE FILES
;*****************************************************************************/
;
;/* -------------------- system and platform files ------------------------- */
;
;/* ------------------------- program files -------------------------------- */
;
;/****************************************************************************
;*   EXTERNAL REFERENCES NOTE : only use if not found in header file
;*****************************************************************************/
;
;/* ------------------------ data declarations ----------------------------- */
;
; /* These variables are defined in linker cmd file
 .global __S_STACK_SIZE
 .global __F_STACK_SIZE

;/* ----------------------- function prototypes ---------------------------- */
;
; /* Global extern varaibales */
 .global _ARM926_user_swi_handler
 .global _Host_int_handler

;
;/****************************************************************************
;*   PUBLIC DECLARATIONS Defined here, used elsewhere
;*****************************************************************************/
;
;/* ----------------------- data declarations ------------------------------ */
;
;/* ---------------------- function prototypes ----------------------------- */
;
;
;/****************************************************************************
;*   PRIVATE DECLARATIONS Defined here, used only here
;*****************************************************************************/
;
;/* ---------------------- data declarations ------------------------------- */
;

;/* Some #defines for Interrupt handler  */
ARM926_IRQ0 .set 0x01C48000 ; IRQ interrupt clear(satus) register of AINTC
BIT_10_MASK .set 0x00000400 ; MASK to enable 28 pin of AINTC 
                            ; (kld_arm to host_arm interrupt)


;*****************************************************************************
;* CONSTANT TABLE                                                            *
;*****************************************************************************
  .sect   ".handler"
  .global EXT_SWI_HANDLER
  .align  4
EXT_SWI_HANDLER:   .word  _ARM926_user_swi_handler
EXT_IRQ_HANDLER:   .word  _Host_int_handler
EXT_IRQ_ACK_ADD:   .word  ARM926_IRQ0
EXT_IRQ_ACK_VAL:   .word  BIT_10_MASK

s_STACK_SIZE       .long    __S_STACK_SIZE
s_stack            .long    __sstack
f_STACK_SIZE       .long    __F_STACK_SIZE
f_stack            .long    __fstack

;/* ---------------------- function definition ----------------------------- */


;/* ===========================================================================
; *  @func     S_Handler()
; *      
; *  @desc     Function is the low level SWI handler. This function gets called
; *            whenever a SWI is raised. This handler then extracts the SWI 
; *            number from the SWI instruciton and passes the control to a C 
; *            level SWI handler. For details of assemply intruction, refer
; *            to ARM Assembler guide
; *            LN# SPNU118   - TMS470R1x Assembly Language Tool User's Guide  
; *
; *  @param    None
; *
; *  @return   None
; *  ==========================================================================
; */
 
 .global _EXT_SWI_HANDLER
 .global _S_Handler
 .align  4
  
 .clink
 .armfunc _S_Handler
 .state32

 .sect ".handler"
__sstack:       .usect  ".sstack", 0x100, 4        
__fstack:       .usect  ".fstack", 0x100, 4        

_S_Handler: 

;*----------------------------------------------------------------------------
;* Set the FIQ and SWI stack here. This is an adhoc method of setting the
;* stack pointer of supervisor and FIQ mode. Ideally, this should have been
;* done in a boot code. Since the test app uses _c_init00() code for stratup
;* initialization, the stack pointer initialization of other mode(apart from 
;* user mode) cannot be done. Hence it is done at the start of a SWI call. 
;* Because of this method, nested SWI cannot be used in this setup.
;*---------------------------------------------------------------------------

;*------------------------------------------------------
;* SET TO FRQ  MODE
;*------------------------------------------------------
 MRS     r0, cpsr
 BIC     r0, r0, #0x1F  ; CLEAR MODES
 ORR     r0, r0, #0x11  ; SET  FRQ MODE
 MSR     cpsr, r0

;*------------------------------------------------------
;* INITIALIZE THE FRQ  MODE STACK                      
;*------------------------------------------------------
 LDR     SP, f_stack
 LDR     R0, f_STACK_SIZE
 ADD     SP, SP, R0
;*------------------------------------------------------
;* SET TO SWI  MODE
;*------------------------------------------------------
 MRS     r0, cpsr
 BIC     r0, r0, #0x1F  ; CLEAR MODES
 ORR     r0, r0, #0x13  ; SET  SWI MODE
 MSR     cpsr, r0
;*------------------------------------------------------
;* INITIALIZE THE SWI  MODE STACK                      
;*------------------------------------------------------
 LDR     SP, s_stack
 LDR     R0, s_STACK_SIZE
 ADD     SP, SP, R0

;*------------------------------------------------------
;* ACTUAL SWI HNADLER FUNCTION STARTS FROM HERE                      
;*------------------------------------------------------

 STMFD  sp!, {r0-r12, lr}   ; store used registers, modify as per use case
 SUB    r0, lr, #4          ; extract the SWI number 
 LDR    r0,[r0]
 BIC    r0,r0,#0xff000000   ; get SWI # by bit-masking
 LDR    r1, EXT_SWI_HANDLER 
 BLX    r1                  ; go to handler 
 LDMFD  sp!, {r0-r12, pc}^  ; unstack user's registers 



;/* ===========================================================================
; *  @func     _FIQ_Handler()
; *      
; *  @desc     Function is the low level FIQ handler. This function gets called
; *            whenever a FIQ is raised. This handler then passes the control 
; *            to a C level FIQ handler, EXT_IRQ_HANDLER. 
; *            For details of assembly instruction refer, ARM Assembler guide
; *            LN# SPNU118   - TMS470R1x Assembly Language Tool User's Guide
; *
; *  @param    None
; *
; *  @return   None
; *  ==========================================================================
; */ 
 .global _FIQ_Handler
 .align  4

 .clink
 .armfunc _FIQ_Handler
 .state32

 .sect ".handler"


_FIQ_Handler: 
 SUBS   lr, lr, #4         ; return from handler
 STMFD  sp!, {r0-r12, lr}  ; store user's gp registers
 ; Acknowledge the AINTC interrupt:
 ; We know it is from KAL in standalone case
 LDR r0, EXT_IRQ_ACK_ADD   ;load address
 LDR r1, EXT_IRQ_ACK_VAL   ;load constant
 STR r1, [r0]              ;ack int: writing 0 has no effect
 ; Now service the interrupt 
 LDR    r1, EXT_IRQ_HANDLER 
 BLX    r1                 ; go to handler 

 LDMFD  sp!, {r0-r12, pc}^ ; unstack user's registers and return from handler

 
 




;/*!
; *! Revision History
; *! ================
; *! 16-Sep-2007   Yashwant  : Added comments in file.
; *! 16-Aug-2007   Kumar    : Incorporated code review comments.
; *! 11-Apr-2007   Yashwant :  Created.
; *!
; */
