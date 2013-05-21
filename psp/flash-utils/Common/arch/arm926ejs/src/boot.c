/* --------------------------------------------------------------------------
  FILE        : boot.c                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : ARM926EJ-S entry point functionality
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific header file
#include "device.h"

// This module's header file 
#include "boot.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern void main(void);


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Boot entry point to setup the C environment
#if defined(__TMS470__)
  #pragma TASK(boot);
  #pragma NO_HOOKS(boot);
  #pragma CODE_SECTION(boot,".boot");
#endif
void boot(void)
{
  asm(" .global STACKStart");
  asm(" .global _stack");
  asm(" .global main");  
	asm(" NOP");
  asm(" MRS  r0, cpsr");
  asm(" BIC  r0, r0, #0x1F");       // CLEAR MODES
  asm(" ORR  r0, r0, #0x13");       // SET SUPERVISOR mode
  asm(" ORR  r0, r0, #0xC0");       // Disable FIQ and IRQ
  asm(" MSR  cpsr, r0");
  asm(" NOP");
  
  // Set the IVT to low memory, leave MMU & caches disabled
  asm(" MRC  p15,#0,r0,c1,c0,#0");
  asm(" BIC  r0,r0,#0x00002300");
  asm(" BIC  r0,r0,#0x00000087");
  asm(" ORR  r0,r0,#0x00000002");
  asm(" ORR  r0,r0,#0x00001000");  
  asm(" MCR  p15,#0,r0,c1,c0,#0");
  asm(" NOP");
  
  // Setup the stack pointer
  asm(" LDR  sp,_stack");
  asm(" SUB  sp,sp,#4");
  asm(" BIC  sp, sp, #7");
  
  // Call to main entry point
  main();
  
  asm("_stack:");
  asm(" .word STACKStart");
}

/************************************************************
* Local Function Definitions                                *
************************************************************/


/************************************************************
* End file                                                  *
************************************************************/
