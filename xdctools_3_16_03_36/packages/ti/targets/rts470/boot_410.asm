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
;******************************************************************************
;* BOOT  v4.1.0                                                               *
;* Copyright (c) 1996-2004 Texas Instruments Incorporated                     *
;******************************************************************************

;****************************************************************************
;* BOOT.ASM
;*
;* THIS IS THE INITAL BOOT ROUTINE FOR TMS470 C++ PROGRAMS.
;* IT MUST BE LINKED AND LOADED WITH ALL C++ PROGRAMS.
;* 
;* THIS MODULE PERFORMS THE FOLLOWING ACTIONS:
;*   1) ALLOCATES THE STACK AND INITIALIZES THE STACK POINTER
;*   2) PERFORMS AUTO-INITIALIZATION
;*   3) CALLS INITALIZATION ROUTINES FOR FILE SCOPE CONSTRUCTION
;*   4) CALLS THE FUNCTION MAIN TO START THE C++ PROGRAM
;*   5) CALLS THE STANDARD EXIT ROUTINE
;*
;* THIS MODULE DEFINES THE FOLLOWING GLOBAL SYMBOLS:
;*   1) __stack     STACK MEMORY AREA
;*   2) _c_int00    BOOT ROUTINE
;*
;****************************************************************************
	.if .TMS470_16BIS

;****************************************************************************
;*  16 BIT STATE BOOT ROUTINE                                               *
;****************************************************************************

	.state32
	.global	__stack
;***************************************************************
;* DEFINE THE USER MODE STACK (DEFAULT SIZE IS 512)               
;***************************************************************
__stack:.usect	".stack", 0, 4

	.global	_c_int00
	.if __TI_ARM9ABI_ASSEMBLER
	.global __args_main
	.else
	.global $_args_main
	.endif

;
;  Define _argbeg here so that we don't need it in the linker command file;
;  this allows us to use this boot file for both xdc programs and legacy
;  DSP/BIOS programs.
;
	.global _argbeg
_argbeg:    .sect ".args"
	    .sect ".text"

;***************************************************************
;* FUNCTION DEF: _c_int00                                      
;***************************************************************
_c_int00: .asmfunc

        ;*------------------------------------------------------
	;* SET TO USER MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x10  ; SET USER MODE
        MSR     cpsr, r0

        ;*------------------------------------------------------
	;* CHANGE TO 16 BIT STATE
        ;*------------------------------------------------------
	ADD	r0, pc, #1
	BX	r0

	.state16
        ;*------------------------------------------------------
        ;* INITIALIZE THE USER MODE STACK                      
        ;*------------------------------------------------------
	LDR     r0, c_stack
	MOV	sp, r0
        LDR     r0, c_STACK_SIZE
	ADD	sp, r0

	;*-----------------------------------------------------
	;* ALIGN THE STACK TO 64-BITS IF EABI.
	;*-----------------------------------------------------
	.if __TI_EABI_ASSEMBLER
	MOV	r7, sp
	MOV	r0, #0x07
	BIC     r7, r0         ; Clear upper 3 bits for 64-bit alignment.
	MOV	sp, r7
	.endif

	;*-----------------------------------------------------
	;* SAVE CURRENT STACK POINTER FOR SDP ANALYSIS
	;*-----------------------------------------------------
	LDR	r0, c_mf_sp
	MOV	r7, sp
	STR	r7, [r0]

        ;*------------------------------------------------------
        ;* PROCESS BINIT LINKER COPY TABLE.  IF BINIT IS -1, THEN
	;* THERE IS NONE.
        ;*------------------------------------------------------
	LDR	r0, c_binit
	MOV	r7, #1 
	CMN	r0, r7
	BEQ	_b1_
	.if __TI_ARM9ABI_ASSEMBLER
	BL      _copy_in
	.else
	BL      $copy_in
	.endif

        ;*------------------------------------------------------
        ;* PERFORM AUTO-INITIALIZATION.  IF CINIT IS -1, THEN
	;* THERE IS NONE.
        ;*------------------------------------------------------
_b1_:	LDR	r0, c_cinit
	MOV	r7, #1 
	CMN	r0, r7
	BEQ	_c1_
        BL      auto_init

        ;*------------------------------------------------------
	;* CALL INITIALIZATION ROUTINES FOR CONSTRUCTORS. IF
	;* PINIT IS -1, THEN THERE ARE NONE.
	;* NOTE THAT r7 IS PRESERVED ACROSS AUTO-INITIALIZATION.
        ;*------------------------------------------------------
_c1_:	LDR	r5, c_pinit
	CMN	r5, r7
	BEQ	_c3_
	B	_c2_
_loop_:	BL	IND$CALL
_c2_:	LDMIA	r5!, {r4}
	CMP	r4, #0
	BNE	_loop_

        ;*------------------------------------------------------
	;* CALL APPLICATION                                     
        ;*------------------------------------------------------
_c3_:	LDR	r3, c_args
	LDR	r0, [r3, #0]
	LDR	r1, [r3, #4]
	LDR	r2, [r3, #8]
	.if __TI_ARM9ABI_ASSEMBLER
	BL      __args_main
	.else
	BL      $_args_main
	.endif


        ;*------------------------------------------------------
	;* IF APPLICATION DIDN'T CALL EXIT, CALL EXIT(1)
        ;*------------------------------------------------------
        MOV     r0, #1
	.if __TI_ARM9ABI_ASSEMBLER
	BL      _exit
	.else
        BL      $exit
	.endif

        ;*------------------------------------------------------
	;* DONE, LOOP FOREVER
        ;*------------------------------------------------------
L1:     B	L1
	.endasmfunc


;***************************************************************************
;*  PROCESS INITIALIZATION TABLE.
;*
;*  THE TABLE CONSISTS OF A SEQUENCE OF RECORDS OF THE FOLLOWING FORMAT:
;*                                                                          
;*       .word  <length of data (bytes)>
;*       .word  <address of variable to initialize>                         
;*       .word  <data>
;*                                                                          
;*  THE INITIALIZATION TABLE IS TERMINATED WITH A ZERO LENGTH RECORD.
;*                                                                          
;***************************************************************************

tbl_addr  .set    r0
var_addr  .set    r1
tmp	  .set    r2
length:   .set    r3
data:     .set    r4
three:    .set    r5

auto_init: .asmfunc
	MOV	three, #3		   ;
	B	rec_chk			   ;

        ;*------------------------------------------------------
	;* PROCESS AN INITIALIZATION RECORD
        ;*------------------------------------------------------
record:	LDR	var_addr, [tbl_addr, #4]   ;
	ADD	tbl_addr, #8		   ;

        ;*------------------------------------------------------
	;* COPY THE INITIALIZATION DATA
        ;*------------------------------------------------------
	MOV	tmp, var_addr		   ; DETERMINE ALIGNMENT
	AND	tmp, three		   ; AND COPY BYTE BY BYTE
	BNE	_bcopy			   ; IF NOT WORD ALIGNED

	MOV	tmp, length		   ; FOR WORD COPY, STRIP
	AND	tmp, three		   ; OUT THE NONWORD PART
	BIC	length, three		   ; OF THE LENGTH
	BEQ	_wcont			   ;		

_wcopy:	LDR	data, [tbl_addr]	   ;
	ADD	tbl_addr, #4		   ;
	STR	data, [var_addr]	   ; COPY A WORD OF DATA
	ADD	var_addr, #4		   ;
	SUB	length, #4		   ;
	BNE	_wcopy                     ;
_wcont:	MOV	length, tmp		   ;
	BEQ	_cont			   ;

_bcopy:	LDRB	data, [tbl_addr]	   ;
	ADD	tbl_addr, #1		   ;
	STRB	data, [var_addr]	   ; COPY A BYTE OF DATA
	ADD	var_addr, #1		   ;
	SUB	length, #1		   ;
	BNE	_bcopy                     ;

_cont:	MOV	tmp, tbl_addr	           ;
	AND	tmp, three	           ; MAKE SURE THE ADDRESS
	BEQ	rec_chk			   ; IS WORD ALIGNED
	BIC	tbl_addr, three		   ;
	ADD	tbl_addr, #0x4             ;

rec_chk:LDR	length, [tbl_addr]         ; PROCESS NEXT
	CMP	length, #0                 ; RECORD IF LENGTH IS
	BNE	record                     ; NONZERO 

	BX	lr
	.endasmfunc

;***************************************************************
;* CONSTANTS USED BY THIS MODULE
;***************************************************************
c_args		.long    _argbeg
c_stack		.long    __stack
c_STACK_SIZE  	.long    __STACK_SIZE
c_binit       	.long    binit
c_cinit       	.long    cinit
c_pinit       	.long    pinit
c_mf_sp	        .long    _main_func_sp

        .sect   ".cinit"
        .align  4
        .field          4,32
        .field          _stkchk_called+0,32
        .field          0,32

        .bss    _stkchk_called,4,4

;******************************************************
;* UNDEFINED REFERENCES                               *
;******************************************************
	.global IND$CALL
	.global	binit
	.global	cinit
	.global	pinit
	.global	__STACK_SIZE
	.global _stkchk_called
	.global _main_func_sp
	.if __TI_ARM9ABI_ASSEMBLER
	.global	_exit
	.else
	.global	$exit
	.endif
	.if __TI_ARM9ABI_ASSEMBLER
	.global	_copy_in
	.else
	.global	$copy_in
	.endif
	.else

;****************************************************************************
;*  32 BIT STATE BOOT ROUTINE                                               *
;****************************************************************************

	.global	__stack
;***************************************************************
;* DEFINE THE USER MODE STACK (DEFAULT SIZE IS 512)            
;***************************************************************
__stack:.usect	".stack", 0, 4

;
;  Define _argbeg here so that we don't need it in the linker command file;
;  this allows us to use this boot file for both xdc programs and legacy
;  DSP/BIOS programs.
;
	.global _argbeg
_argbeg:    .sect ".args"
	    .sect ".text"

	.global	_c_int00
;***************************************************************
;* FUNCTION DEF: _c_int00                                      
;***************************************************************
_c_int00: .asmfunc

        ;*------------------------------------------------------
	;* SET TO USER MODE
        ;*------------------------------------------------------
        MRS     r0, cpsr
        BIC     r0, r0, #0x1F  ; CLEAR MODES
        ORR     r0, r0, #0x10  ; SET USER MODE
        MSR     cpsr, r0

        ;*------------------------------------------------------
        ;* INITIALIZE THE USER MODE STACK                      
        ;*------------------------------------------------------
	LDR     sp, c_stack
        LDR     r0, c_STACK_SIZE
	ADD	sp, sp, r0

	;*-----------------------------------------------------
	;* ALIGN THE STACK TO 64-BITS IF EABI.
	;*-----------------------------------------------------
	.if __TI_EABI_ASSEMBLER
	BIC     sp, sp, #0x07  ; Clear upper 3 bits for 64-bit alignment.
	.endif

	;*-----------------------------------------------------
	;* SAVE CURRENT STACK POINTER FOR SDP ANALYSIS
	;*-----------------------------------------------------
	LDR	r0, c_mf_sp
	STR	sp, [r0]

        ;*------------------------------------------------------
        ;* PROCESS BINIT LINKER COPY TABLE.  IF BINIT IS -1, THEN
	;* THERE IS NONE.
        ;*------------------------------------------------------
	LDR	r0, c_binit
	CMN	r0, #1
        BLNE    _copy_in

        ;*------------------------------------------------------
        ;* PERFORM AUTO-INITIALIZATION.  IF CINIT IS -1, THEN
	;* THERE IS NONE.
        ;*------------------------------------------------------
	LDR	r0, c_cinit
	CMN	r0, #1
        BLNE    auto_init

        ;*------------------------------------------------------
	;* CALL INITIALIZATION ROUTINES FOR CONSTRUCTORS. IF
	;* PINIT IS -1, THEN THERE ARE NONE.
        ;*------------------------------------------------------
	LDR	r5, c_pinit
	CMN	r5, #1
	BEQ	_c2_
	B	_c1_
_loop_:	BL	IND_CALL
_c1_:	LDR	r4, [r5], #4
	CMP	r4, #0
	BNE	_loop_

        ;*------------------------------------------------------
	;* CALL APPLICATION                                     
        ;*------------------------------------------------------    
_c2_:	LDR	r3, c_args
	LDR	r0, [r3, #0]
	LDR	r1, [r3, #4]
	LDR	r2, [r3, #8]
	BL      __args_main

        ;*------------------------------------------------------
	;* IF APPLICATION DIDN'T CALL EXIT, CALL EXIT(1)
        ;*------------------------------------------------------
        MOV     R0, #1
        BL      _exit

        ;*------------------------------------------------------
	;* DONE, LOOP FOREVER
        ;*------------------------------------------------------
L1:     B	L1
	.endasmfunc

;***************************************************************************
;*  PROCESS INITIALIZATION TABLE.
;*
;*  THE TABLE CONSISTS OF A SEQUENCE OF RECORDS OF THE FOLLOWING FORMAT:
;*                                                                          
;*       .word  <length of data (bytes)>
;*       .word  <address of variable to initialize>                         
;*       .word  <data>
;*                                                                          
;*  THE INITIALIZATION TABLE IS TERMINATED WITH A ZERO LENGTH RECORD.
;*                                                                          
;***************************************************************************

tbl_addr: .set    R0
var_addr: .set    R1
length:   .set    R2
data:     .set    R3

auto_init: .asmfunc
	B	rec_chk

        ;*------------------------------------------------------
	;* PROCESS AN INITIALIZATION RECORD
        ;*------------------------------------------------------
record:	LDR	var_addr, [tbl_addr], #4   ;

        ;*------------------------------------------------------
	;* COPY THE INITIALIZATION DATA
        ;*------------------------------------------------------
	TST	var_addr, #3		   ; SEE IF DEST IS ALIGNED
	BNE     _bcopy			   ; IF NOT, COPY BYTES
	SUBS	length, length, #4	   ; IF length <= 3, ALSO
	BMI     _bcont			   ; COPY BYTES

_wcopy:	LDR	data, [tbl_addr], #4  	   ;
	STR	data, [var_addr], #4	   ; COPY A WORD OF DATA
	SUBS	length, length, #4	   ;
	BPL	_wcopy			   ;
_bcont:	ADDS	length, length, #4	   ;
	BEQ	_cont			   ;

_bcopy:	LDRB	data, [tbl_addr], #1       ;
	STRB	data, [var_addr], #1       ; COPY A BYTE OF DATA
	SUBS	length, length, #1	   ;
	BNE	_bcopy                     ;

_cont:	ANDS	length, tbl_addr, #0x3     ; MAKE SURE THE ADDRESS
	RSBNE	length, length, #0x4       ; IS WORD ALIGNED
	ADDNE	tbl_addr, tbl_addr, length ;

rec_chk:LDR	length, [tbl_addr], #4     ; PROCESS NEXT
	CMP	length, #0                 ; RECORD IF LENGTH IS
	BNE	record                     ; NONZERO

	BX	LR
	.endasmfunc

;***************************************************************
;* CONSTANTS USED BY THIS MODULE
;***************************************************************
c_args		.long    _argbeg
c_stack		.long    __stack
c_STACK_SIZE  	.long    __STACK_SIZE
c_binit       	.long    binit
c_cinit       	.long    cinit
c_pinit       	.long    pinit
c_mf_sp	        .long    _main_func_sp

        .sect   ".cinit"
        .align  4
        .field          4,32
        .field          _stkchk_called+0,32
        .field          0,32

        .bss    _stkchk_called,4,4



;******************************************************
;* UNDEFINED REFERENCES                               *
;******************************************************
	.global IND_CALL
	.global	_exit
	.global	__args_main
	.global	binit
	.global	cinit
	.global	pinit
	.global	_copy_in
	.global	__STACK_SIZE
	.global _stkchk_called
	.global _main_func_sp
	.endif

	.end
