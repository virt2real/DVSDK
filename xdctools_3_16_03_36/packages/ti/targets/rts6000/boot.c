/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*****************************************************************************/
/* BOOT.C   v7.0.0A08274 - Initialize the C60 C runtime environment                */
/* Copyright (c) 1993-2008  Texas Instruments Incorporated                   */
/*****************************************************************************/
#include <c6x.h>

#include <xdc/runtime/Startup.h>

#ifndef __TI_ELFABI__

#define CINIT   ((void*)&__cinit__)
extern far int  __cinit__;
extern far void _auto_init(const void *cinit);

#else

extern far void _auto_init_elf(void);

#endif

extern __FAR__ int xdc_runtime_Startup__RESETFXN__C;

extern far int _args_main();
extern far void exit(int status);

/*---------------------------------------------------------------------------*/
/* ALLOCATE THE MEMORY FOR THE SYSTEM STACK.  THIS SECTION WILL BE SIZED     */
/* BY THE LINKER.                                                            */
/*---------------------------------------------------------------------------*/
#ifdef __VIRTUAL_ENCODING__
extern char _STACK_END[];
extern char __bss__[];
register volatile unsigned int __SP;
register volatile unsigned int __DP;
#else
#ifndef __TI_ELFABI__
__asm("\t.global __STACK_SIZE");
#else
__asm("\t.global __TI_STACK_END");
__asm("\t.global __TI_STATIC_BASE");
#endif
#endif

#pragma DATA_ALIGN   (_stack, 8);
#pragma DATA_SECTION (_stack, ".stack");
char _stack[8];

/*---------------------------------------------------------------------------*/
/* Rename c_int00 so that the linkage name remains _c_int00 in ELF           */
/*---------------------------------------------------------------------------*/
#ifdef __TI_ELFABI__
#define c_int00 _c_int00
#endif

/*****************************************************************************/
/* C_INT00() - C ENVIRONMENT ENTRY POINT                                     */
/*****************************************************************************/
extern void __interrupt c_int00()
{
   /*
    * Clear IER, IFR register.  This is necessary to prohibit left-over
    * interrupts from being serviced.
    */
   __asm("\t   ZERO\t\t   B0");
   __asm("\t   MVC\t\t    B0, IER");
   __asm("\t   MVK\t\t    -1, B0");
   __asm("\t   MVC\t\t    B0, ICR");


#ifdef __VIRTUAL_ENCODING__
    __SP = ((int)_stack + (int)_STACK_SIZE - 4) & ~7;
    __DP = (int)__bss__;
#else
   /*------------------------------------------------------------------------*/
   /* SET UP THE STACK POINTER IN B15.                                       */
   /* THE STACK POINTER POINTS 1 WORD PAST THE TOP OF THE STACK, SO SUBTRACT */
   /* 1 WORD FROM THE SIZE. ALSO THE SP MUST BE ALIGNED ON AN 8-BYTE BOUNDARY*/
   /*------------------------------------------------------------------------*/
#ifndef __TI_ELFABI__

   __asm("\t   MVKL\t\t   __stack + __STACK_SIZE - 4, SP");
   __asm("\t   MVKH\t\t   __stack + __STACK_SIZE - 4, SP");

#else

   __asm("\t   MVKL\t\t   __TI_STACK_END - 4, SP");
   __asm("\t   MVKH\t\t   __TI_STACK_END - 4, SP");

#endif

   __asm("\t   AND\t\t   ~7,SP,SP");               

   /*------------------------------------------------------------------------*/
   /* SET UP THE GLOBAL PAGE POINTER IN B14.                                 */
   /*------------------------------------------------------------------------*/
#ifndef __TI_ELFABI__

   __asm("\t   MVKL\t\t   $bss,DP");
   __asm("\t   MVKH\t\t   $bss,DP");

#else

   __asm("\t   MVKL\t\t   __TI_STATIC_BASE,DP");
   __asm("\t   MVKH\t\t   __TI_STATIC_BASE,DP");

#endif
#endif  /* Virtual Encoding */

   /*------------------------------------------------------------------------*/
   /* SET UP FLOATING POINT REGISTERS FOR C6700                              */
   /*------------------------------------------------------------------------*/
#ifdef _TMS320C6700
   FADCR = 0; FMCR  = 0;
#endif

   /*------------------------------------------------------------------------*/
   /* Call hook configured into Startup_resetFxn                             */
   /*------------------------------------------------------------------------*/
   if (&xdc_runtime_Startup__RESETFXN__C == (int*)1) {
      xdc_runtime_Startup_reset__I();
   }

   /*------------------------------------------------------------------------*/
   /* CALL THE AUTOINITIALIZATION ROUTINE.                                   */
   /*------------------------------------------------------------------------*/
#ifndef __TI_ELFABI__
   _auto_init(CINIT);
#else
   _auto_init_elf();
#endif
   
   _args_main();

   /*------------------------------------------------------------------------*/
   /* CALL EXIT.                                                             */
   /*------------------------------------------------------------------------*/
   exit(1);
}

/*
 *  @(#) ti.targets.rts6000; 1, 0, 0, 0,305; 2-24-2010 16:42:05; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

