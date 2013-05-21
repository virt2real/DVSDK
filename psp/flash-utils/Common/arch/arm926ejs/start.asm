    .global __stack
__stack:        .usect  ".stack",8,8

    .sect   ".text:.start"
    .global __STACK_SIZE
    .global main
    .global start

start:
	  /* set the cpu to SVC32 mode */
    mrs r0,cpsr
    bic	r0,r0,#0x1f
    orr	r0,r0,#0xd3
    msr	cpsr,r0

stack_setup:
    ; Set up the stack
    ldr	r0, stackptr
    ldr r1, stacksize
    add	r0, r0, r1
    sub	sp, r0, #4
    bic sp, sp, #7 ; eabi requires align to 8 bytes

    ; Load the Kernel entry point address
    ldr	r0, main_entry

    ; Jump to Entry Point
    mov pc, r0

stackptr:
    .word __stack
stacksize:
    .word 0x800
main_entry:
    .word  main