/* --------------------------------------------------------------------------
  FILE        : pciboot.c                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Texas Instruments Incorporated - http://www.ti.com/
  DESC        : Module to boot the from PCI
----------------------------------------------------------------------------- */

#ifdef UBL_PCI

// General type include
#include "tistdtypes.h"

// Debug I/O module
#include "debug.h"

// Device specific functions
#include "device.h"

// Misc utility module
#include "util.h"

// Main UBL module
#include "ubl.h"

/************************************************************
* Explicit External Declarations                            *
************************************************************/

// Entrypoint for application we are decoding out of flash
extern Uint32 gEntryPoint;


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

Uint32 PCIBOOT_copy()
{
  Uint32 bootComplete = 0;
  int *entry_point = (int *)0x00017ffc;

  //===================================================
  // Clear Boot Complete Flag
  //===================================================
  SYSTEM->BOOTSTAT &= ~0x1;

  DEBUG_printString("\r\nBooting via PCI Boot Mode\r\n");

  //===================================================
  // Wait Boot Complete Flag become to '1'
  //===================================================
  bootComplete = 0;
  while(!bootComplete)
  {
    bootComplete = (SYSTEM->BOOTSTAT & 0x1);
    DEBUG_printString(".");
  }

  DEBUG_printString("\r\n");

  /* Set the entry point */
  gEntryPoint = *entry_point;  	

  return E_PASS;
}

/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
#endif  // #ifdef UBL_PCI
