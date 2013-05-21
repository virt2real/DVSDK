/* --------------------------------------------------------------------------
  FILE        : nanderaser.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Sandeep Paulraj <s-paulraj@ti.com>
  DESC	      : CCS-based utility to Erase the NAND connected to each CS.
                If the NAND has been flashed with the wrong layout, then
				this utility should be used to erase the entire NAND.
				The utility skips over bad blocks.
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "nanderaser.h"

// NAND driver include
#include "nand.h"
#include "device_nand.h"

// Misc. utility function include
#include "util.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 EMIFStart;
extern __FAR__ Uint32 DDRStart;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 nanderaser(void);


/************************************************************
* Global Variable Definitions
************************************************************/



/************************************************************
* Global Function Definitions                               *
************************************************************/

void main( void )
{
  int status;

  // Init memory alloc pointer
  UTIL_setCurrMemPtr(0);

  // System init
  if (DEVICE_init() !=E_PASS)
  {
    exit();
  }

  DEVICE_pinmuxControl( 0, DEVICE_PINMUX_EMIF_MASK, DEVICE_PINMUX_EMIF_EN );

  // Execute the NAND flashing
  status = nanderaser();

  if (status != E_PASS)
  {
    DEBUG_printString("\n\nNAND erasing failed!\r\n");
  }
  else
  {
    DEBUG_printString( "\n\nNAND Erasing was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 nanderaser()
{
  NAND_InfoHandle  hNandInfo;
  Int8  answer[24];
  Int32 CSAddr;

  DEBUG_printString("Starting DM35x NAND Erase Utility.\r\n");
  
  DEBUG_printString("Enter the Address where NAND is conencted (in hex): \n");
  DEBUG_readString(answer);
  CSAddr = strtoul(answer, NULL, 16);
  fflush(stdin);

  // Initialize NAND Flash
  hNandInfo = NAND_open(CSAddr, (Uint8) DEVICE_emifBusWidth() );
  
  if (hNandInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NAND Initialization failed.\r\n" );
    return E_FAIL;
  }

  DEBUG_printString("Attempting a global erase of NAND\n");
  NAND_globalErase_with_bb_check(hNandInfo);

  return E_PASS;
}


