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
; *   @file   testapp_intveca.asm
; *
; *   @path   $(PROJDIR)\client\test\src
; *
; *   @brief  This File contains vector table for ARM926. 
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
;/* ----------------------- function prototypes ---------------------------- */
;
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

;/* ----------------------------------------------------------------------- */
;/*             VECTOR TABLE                                                */
;/* To know more about vector table, refer to ARM926 TRM : chapter 2        */
;/* ----------------------------------------------------------------------- */

 .global _S_Handler
 .global _IRQ_Handler
 .global _FIQ_Handler

 .state32
 .sect ".intvecs"

 ; reset interrupt is not defined as it is read-only Mapped to ROM addr
 .word 0                  ; undefined instruction interrupt - not implemented
  B _S_Handler            ; software interrupt- not implemented
 .word 0                  ; abort (prefetch) interrupt - not implemented
 .word 0                  ; abort (data) interrupt- not implemented
 .word 0                  ; reserved
 .word 0                  ; IRQ interrupt - not implemented
  B _FIQ_Handler          ; FIQ interrupt



;/*!
; *! Revision History
; *! ================
; *! 16-Sp-2007   Yashwant :  Added more commnets
; *! 16-Aug-2007   Kumar    : Incorporated code review comments.
; *! 11-Apr-2007   Yashwant :  Created.
; *!
; */
