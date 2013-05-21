/** ==========================================================================
* @file testapp_arm926intc.h
*
* @path $(PROJDIR)\inc
*
* @brief This File contains the macros to program interrpt controller and SWI
*        functions decalration(alias) for programming system resource
* ============================================================================
* Copyright (c) Texas Instruments Inc 2005, 2006
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**==========================================================================*/

/****************************************************************************
*                     INCLUDE FILES
*****************************************************************************/


/* ----------------------- SYSTEM AND PLATFORM FILES -----------------------*/

/*------------------------------ PROGRAM FILES -----------------------------*/


/****************************************************************************
*  EXTERNAL REFERENCES NOTE :
*****************************************************************************/

/*---------------------------- DATA DECLARATIONS ---------------------------*/

/* ---------------------------- FUNCTION DECLARATIONS ----------------------*/
/* The below #pragmas are to generate SWI calls for various system related
 * fucntionalities whcih cannot be done in user mode.  Cache, interrput
 * and MMU related reisters are only accessible in system mode. These functions
 * fucntion generate a SWI and put the processor in supervisor mode. In that
 * mode, the required functionality is performed. 
 *
 * For more details on the #pragma - see 5.8.7 The SWI_ALIAS Pragma of 
 * TMS470R1x Optimizing C/C++ Compiler, User's Guide, LN: SPNU151C  
 *
 * For details of these SWI functions, see file testapp_arm926intc.c
 */

 /* SWI aliase function to enable MMU */
#pragma SWI_ALIAS(ARM926_Enable_MMU,           0); 
void ARM926_Enable_MMU ();

/* SWI aliase function to disbale MMU */
#pragma SWI_ALIAS(ARM926_Disable_MMU,          1); 
void ARM926_Disable_MMU ();

/* SWI aliase function to set MMU table base address */
#pragma SWI_ALIAS(ARM926_Set_MMU_Base,         2); 
void ARM926_Set_MMU_Base ();

/* SWI aliase function to set MMU protection domain*/
#pragma SWI_ALIAS(ARM926_Set_Domains,          3); 
void ARM926_Set_Domains ();

/* SWI aliase function to enable FIQ */
#pragma SWI_ALIAS(ARM926_enable_FIQ,           4); 
void ARM926_enable_FIQ ();

/* SWI aliase function to enable I-cache */
#pragma SWI_ALIAS(ARM926_Icache_Enable,        5); 
void ARM926_Icache_Enable ();

/* SWI aliase function to disable I-cache */
#pragma SWI_ALIAS(ARM926_Icache_Disable,       6); 
void ARM926_Icache_Disable ();

/* SWI aliase function to set round robin cache replacement strategy */
#pragma SWI_ALIAS(ARM926_Cache_Set_RoundRobin, 7);
void ARM926_Cache_Set_RoundRobin();

/* SWI aliase function to set random cache replacement strategy*/
#pragma SWI_ALIAS(ARM926_Cache_Set_Random,     8); 
void ARM926_Cache_Set_Random ();

/* SWI aliase function to enable D-cache */
#pragma SWI_ALIAS(ARM926_Dcache_Enable,        9); 
void ARM926_Dcache_Enable ();

/* SWI aliase function to disable D-cache */
#pragma SWI_ALIAS(ARM926_Dcache_Disable,      10); 
void ARM926_Dcache_Disable ();

/* SWI aliase function to invalidate/flush I-cache */
#pragma SWI_ALIAS(ARM926_Flush_Icache,        11); 
void ARM926_Flush_Icache ();

/* SWI aliase function invalidate/flush D-cache  */
#pragma SWI_ALIAS(ARM926_Flush_Dcache,        12); 
void ARM926_Flush_Dcache ();


/* SWI aliase function to clean D-cache  */
#pragma SWI_ALIAS(ARM926_Clean_Dcache,        13); 
void ARM926_Clean_Dcache ();

/* SWI aliase function to clean and invalidate D-cache */
#pragma SWI_ALIAS(ARM926_CleanFlush_Dcache,   14); 
void ARM926_CleanFlush_Dcache ();

/* Function to intialize ARM926 Interrupt controller */
void ARM926_INTC_init ();

/****************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/

/*---------------------------- DATA DECLARATIONS ---------------------------*/


/****************************************************************************
*  MACROS
*****************************************************************************/

/* ARM926 INTC registers: For details, see section 8 of DM510 ARM subsystem
  technical refernce manual */

/* Base address of FIQ status bits */
#define ARM926_FIQ0         0x01C48000
#define ARM926_FIQ1         0x01C48004

/* Base address of IRQ status bits */
#define ARM926_IRQ0         0x01C48008
#define ARM926_IRQ1         0x01C4800C

/* ENtry address for valid FIQ or IRQ interrupt  */
#define ARM926_FIQENTRY     0x01C48010
#define ARM926_IRQENTRY     0x01C48014

/* Register address to enable 64 interrupts  */
#define ARM926_EINT0        0x01C48018
#define ARM926_EINT1        0x01C4801C

/* Interrupt operation control register */
#define ARM926_INTCTL       0x01C48020

/* Interrupt entry base register */
#define ARM926_EABASE       0x01C48024

/* Interrupt priority set up registers */
#define ARM926_INTPRI0      0x01C48030
#define ARM926_INTPRI1      0x01C48034
#define ARM926_INTPRI2      0x01C48038
#define ARM926_INTPRI3      0x01C4803C
#define ARM926_INTPRI4      0x01C48040
#define ARM926_INTPRI5      0x01C48044
#define ARM926_INTPRI6      0x01C48048
#define ARM926_INTPRI7      0x01C4804C

/* Bit mask for Kaliedo Interrupt bit */
#define BIT_28_MASK         0x00000400

#define KAL2HOST_INT        10
/* Priority 7 - lowest */

#define PRIORITY_7			0x7
/* Kaliedo to Host interrupt priority - lower priority
 * maps to IRQ */
#define KAL2HOST_INT_PRI    0x00000700

/* Alternate  Kaliedo to Host interrupt priority
 * maps to FIQ */
#define KAL2HOST_INT_PRI_1  0xFFFFF9FF

/* EBASE default value */
#define INT_BASE			0x0






/*!
*! Revision History
*! ================
*! 15-Sep-2007   Yashwant Dutt : Modified to add comments.
*! 10-Sep-2007   Kumar    : Modified to add more SWI calls.
*! 06-Jun-2007   Yashwant Dutt: Created.
*/


