;****************************************************************************
;* ROMBOOT.ASM
;*
;* THIS MODULE PERFORMS THE FOLLOWING ACTIONS:
;*   ALLOCATES THE STACK AND INITIALIZES THE STACK POINTER
;*   INITIALIZE CLOCK CONTROLLER
;*   COPY THE IVT to the IVT LOCATION
;*   MAKE VINTH = 0 TO MAKE IVT AT 0X0
;*
;* THIS MODULE DEFINES THE FOLLOWING GLOBAL SYMBOLS:
;*   1) _c_intDaVinci  BOOT ROUTINE
;*   2) _gEntryPoint    ENTRY POINT FOR THE USER BOOT LOADER
;*
;****************************************************************************
	.sect ".boot"

	.state32

	.global _c_intDaVinci
	.global	main
  .global STACKStart

;***************************************************************
;* FUNCTION DEF: _c_intDaVinci                                    
;***************************************************************
_c_intDaVinci: .asmfunc

	;*------------------------------------------------------
	;* SET TO SUPERVISOR  MODE
	;*------------------------------------------------------
	MRS	r0, cpsr
	BIC	r0, r0, #0x1F	; CLEAR MODES
	ORR	r0, r0, #0x13	; SET SUPERVISOR mode
	MSR	cpsr, r0       
	NOP
	NOP	

	;*------------------------------------------------------
	;* DISABLE IRQ and FIQ
	;*------------------------------------------------------
	MRS     r0, cpsr
	ORR     r0, r0, #0xC0  ; Disable IRQ and FIQ
	MSR     cpsr, r0
	NOP
	NOP
	                             
	;*------------------------------------------------------
	;* INITIALIZE SUPERVISOR STACK
	;*------------------------------------------------------
	LDR     SP, c_stack
	LDR     R0, c_STACK_SIZE
	ADD	SP, SP, R0

	;*------------------------------------------------------
	;* Set interrupt table to location 0x00000000
	;*------------------------------------------------------
	MRC	p15, #0, r1, c1, c0, #0
 	MOV	r0,#0x2000
	BIC	r1, r1, r0                    
   	NOP                                 
	NOP
	MCR	p15, #0, r1, c1, c0, #0
	NOP
	NOP                                 

	; Branch to main
	BL main
	
	NOP
	NOP

  ; go back to restart
  B _c_intDaVinci

	.endasmfunc
	
	.align 4
                        


;***************************************************************
;* CONSTANTS USED BY THIS MODULE
;***************************************************************
c_stack:
          .long    STACKStart
c_STACK_SIZE:
        	.long    0x2FC         

.end