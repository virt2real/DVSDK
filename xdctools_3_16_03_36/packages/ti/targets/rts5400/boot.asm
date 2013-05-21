; --COPYRIGHT--,EPL
;   Copyright (c) 2008 Texas Instruments and others.
;   All rights reserved. This program and the accompanying materials
;   are made available under the terms of the Eclipse Public License v1.0
;   which accompanies this distribution, and is available at
;   http://www.eclipse.org/legal/epl-v10.html
;  
;   Contributors:
;       Texas Instruments - initial implementation
;  
; --/COPYRIGHT--
****************************************************************************
*  BOOT   v3.80                                                           *
*  Copyright (c) 1993-2002 Texas Instruments Incorporated                  *
****************************************************************************
;	.file "boot.asm"
	.c_mode
	.mmregs
CONST_COPY	.set 0
****************************************************************************
*                                                                          *
*   This module contains the following definitions :                       *
*                                                                          *
*         __stack    - Stack memory area                                   *
*         _c_int00   - Boot function                                       *
*         _var_init  - Function which processes initialization tables      *
*                                                                          *
****************************************************************************
        .ref	 cinit, pinit
	.global  _c_int00
	.global  _main, _exit, __STACK_SIZE
;
;  Define _argbeg here so that we don't need it in the linker command file;
;  this allows us to use this boot file for both xdc programs and legacy
;  DSP/BIOS programs.
;
	.global _argbeg
_argbeg:	.sect ".args"
		.sect ".text"

****************************************************************************
* Declare the stack.  Size is determined by the linker option -stack.  The *
* default value is 1K words.                                               *
****************************************************************************
__stack:	.usect	".stack",0

****************************************************************************
* FUNCTION DEF : _c_int00                                                  *
*                                                                          *
*   1) Set up stack                                                        *
*   2) Set up proper status                                                *
*   3) If "cinit" is not -1, init global variables                         *
*   4) call users' program                                                 *
*                                                                          *
****************************************************************************
	.text
_c_int00:
****************************************************************************
*  INIT STACK POINTER.  REMEMBER STACK GROWS FROM HIGH TO LOW ADDRESSES.   *
****************************************************************************
	STM	#__stack,SP		; set to beginning of stack memory
	ADDM	#(__STACK_SIZE-1),*(SP) ; add size to get to top
	ANDM	#0fffeh,*(SP)		; make sure it is an even address
	
	SSBX	SXM			; turn on SXM for LD #cinit,A

****************************************************************************
* SET UP REQUIRED VALUES IN STATUS REGISTER                                *
****************************************************************************
	SSBX	CPL			; turn on compiler mode bit
	RSBX	OVM			; clear overflow mode bit

****************************************************************************
* SETTING THESE STATUS BITS TO RESET VALUES.  IF YOU RUN _c_int00 FROM     *
* RESET, YOU CAN REMOVE THIS CODE                                          *
****************************************************************************
	LD	#0,ARP
	RSBX	C16
	RSBX	CMPT
	RSBX	FRCT

****************************************************************************
*  IF cinit IS NOT -1, PROCESS INITIALIZATION TABLES			   *
*  TABLES ARE IN PROGRAM MEMORY IN THE FOLLOWING FORMAT:                   *
*                                                                          *
*       .word  <length of init data in words>                              *
*       .word  <address of variable to initialize>                         *
*       .word  <init data>                                                 *
*       .word  ...                                                         *
*                                                                          *
*  The cinit table is terminated with a zero length                        *
*                                                                          *
****************************************************************************
	.if	__far_mode
	LDX	#cinit,16,A		
	OR	#cinit,A,A
	.else
	LD	#cinit,A                ; Get pointer to init tables
	.endif

	ADD	#1,A,B
	BC	DONE_CINIT,BEQ		; if (cinit == -1) no init tables

****************************************************************************
*  PROCESS INITIALIZATION TABLES.  TABLES ARE IN PROGRAM MEMORY IN THE     *
*  FOLLOWING FORMAT:                                                       *
*                                                                          *
*       .word  <length of init data in words>                              *
*       .word  <address of variable to initialize>                         *
*       .word  <init data>                                                 *
*       .word  ...                                                         *
*                                                                          *
*  The init table is terminated with a zero length                         *
*                                                                          *
****************************************************************************
	RSBX	SXM			; do address arithmetic unsignedly 
        .if	__far_mode
	.else
	NOP
	LD	#cinit,A		; don't want this sign extended anymore1
	.endif
	B 	START_CINIT		; start processing 

LOOP_CINIT:
	READA	*(AR2)			; AR2 = address
	ADD	#1,A			; A += 1

	RPT	*(AR1)			; repeat length+1 times
	READA	*AR2+			; copy from table to memory

	ADD	*(AR1),A		; A += length (READA doesn't change A)
	ADD	#1,A			; A += 1

START_CINIT:
	READA	*(AR1)			; AR1 = length
	ADD	#1,A			; A += 1
	BANZ	LOOP_CINIT,*AR1-	; if (length-- != 0) continue 
DONE_CINIT:

****************************************************************************
*  IF pinit IS NOT -1, PROCESS INITIALIZATION TABLES                       *
*  TABLES ARE IN PROGRAM MEMORY IN THE FOLLOWING FORMAT:                   *
*                                                                          *
*       .word  <address of initialization routine to call>                 *
*       .word  ...                                                         *
*                                                                          *
*  The pinit table is terminated with a NULL pointer                       *
*                                                                          *
****************************************************************************
	SSBX	SXM
	FRAME	-4
;	nop

	.if	__far_mode
	LDX	#pinit,16,A
	OR	#pinit,A,A
	.else
        LD      #pinit,A                ; A = &pinit table
	.endif

        ADD     #1,A,B                  ; B = A + 1
        BC      DONE_PINIT,BEQ          ; if (pinit == -1) no pinit tables

       .if     __far_mode
       .else
       RSBX    SXM                     ; do address arithmetic unsignedly
       NOP
       LD      #pinit,A                ; don't want this sign extended anymore
       .endif

        BD      START_PINIT 
	DST	A, @2
	nop

LOOP_PINIT:
	.if	__far_mode
	FCALA	B			; call function
	.else
	CALA	B			; call function
	.endif

        DLD     @2, A                   ; put PINIT pointer in A

START_PINIT:
        READA   @0                      ; "push" address of function

	.if	__far_mode
	ADD	#1,A
	READA	@1
	.endif

        .if	__far_mode
	ADD	#1, A
	DST	A, @2
        DLD     @0, B
        BC	LOOP_PINIT,BNEQ

        .else
        LD      @0, B                   ; "pop" address of function
        BCD     LOOP_PINIT,BNEQ         ; if not NULL, loop.
        ADDM    #1,@3                   ; move PINIT pointer (in stack)
        .endif

     
DONE_PINIT:
	RSBX	SXM
	FRAME	4

****************************************************************************
*  CALL USER'S PROGRAM                                                     *
****************************************************************************
	.if CONST_COPY
	.if __far_mode                  ; Use far calls for C548 in far mode
	FCALL	_const_init             ; move .const section to DATA mem
        .else
        CALL	_const_init
	.endif
	.endif

****************************************************************************
*  Set up C environment before calling main(argc, argv, envp).  	   *
****************************************************************************
        ld	#_argbeg,b
	stlm	b,ar1
	nop				; these 2 nops are necessary for 
	nop				; the latency of "stlm b, ar1"

	ld	*ar1+,a			; a = argc
	frame	-2
	ld	*ar1+,b
	stl	b,*sp(0)		; sp(0) = argv
	ld	*ar1,b
	stl	b,*sp(1)		; sp(1) = envp

	.if __far_mode                  ; Use far calls for C548 in far mode
	FCALL    _main			
	FCALL    _exit			; call exit instead of abort so that
	.else
	CALL    _main			
	CALL    _exit			; call exit instead of abort so that
	.endif

	.if CONST_COPY

****************************************************************************
* FUNCTION DEF : __const_init                                              *
*                                                                          *
*  COPY .CONST SECTION FROM PROGRAM TO DATA MEMORY                         *
*                                                                          *
*   The function depends on the following variables                        *
*   defined in the linker command file                                     *
*                                                                          *
*   __c_load         ; global var containing start                         *
*                      of .const in program memory                         *
*   __const_run      ; global var containing run                           *
*                      address in data memory                              *
*   __const_length   ; global var length of .const                         *
*                      section                                             *
*                                                                          *
****************************************************************************
        .global __const_length,__c_load
        .global __const_run
_const_init:
 
        .sect ".c_mark"              ; establish LOAD adress of
        .label __c_load             ; .const section
 
        .text
******************************************************
* C54x VERSION                                        *
******************************************************
        LD      #__const_length, A
        BC      __end_const,AEQ
        STM     #__const_run,AR2 ; Load RUN address of .const
 
 	.if	__far_mode

	LDX	#__c_load,16,A		
	OR	#__c_load,A,A
        RPT     #__const_length-1	
	READA   *AR2+

	.else
	
        RPT     #__const_length-1
        MVPD    #__c_load,*AR2+  ; Copy .const from program to data
	.endif
	
 
******************************************************
*  AT END OF .CONST SECTION RETURN TO CALLER         *
******************************************************
__end_const:
	.if    __far_mode

	.if __no_fret
	FB	_freti549
	.else
	FRET
	.endif

	.else
        RET

	.endif
        .endif
	.end

