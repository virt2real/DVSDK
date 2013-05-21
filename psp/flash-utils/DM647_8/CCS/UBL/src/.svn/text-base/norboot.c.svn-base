/* --------------------------------------------------------------------------
  FILE        : norboot.c 				                             	 	        
  PURPOSE     : NOR user boot loader file
  PROJECT     : DM648 User Boot Loader
  AUTHOR      : Daniel Allred
  DESC        : UBL Nor boot functionality for when a UBL image sits
                at the start of the NOR flash
----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "norboot.h"

// NOR driver fucntions
#include "nor.h"

// AIS module
#include "ais.h"

// Debug I/O module
#include "debug.h"

// Misc utility module
#include "util.h"

// Main UBL module
#include "ubl.h"

/************************************************************
* Explicit External Declarations                            *
************************************************************/

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
\***********************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

#pragma DATA_SECTION(NORStart,".aemif_mem");
VUint32 __FAR__ NORStart;


/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 NORBOOT_copy(void)
{
  NOR_InfoHandle hNorInfo = NULL;
  volatile NORBOOT_HeaderHandle	hNorHeader = 0;
  Uint32 baseAddress, blockSize, blockAddr;

  DEBUG_printString("Starting NOR Copy...\r\n");

  // Open the NOR device and get it's parameters
  hNorInfo = NOR_open((Uint32)&NORStart);
  if (hNorInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NOR Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Set base address to start putting data at
  baseAddress = hNorInfo->flashBase;

  // Get block info (size and start address) for the 1st block (where this UBL is written)
  NOR_getBlockInfo(hNorInfo, baseAddress, &blockSize, &blockAddr);

  // Loop through all blocks searching for AIS image to load
  while ( (blockAddr + blockSize) < (baseAddress + hNorInfo->flashSize) )
  {
    // Get block info for the next block
    NOR_getBlockInfo(hNorInfo, (blockAddr + blockSize), &blockSize, &blockAddr);
        
    // Check for AIS magic word at start of block
    if ( *((Uint32 *)blockAddr) == AIS_MAGIC_NUMBER )
    {
      break;
    }
  }

  // Parse the image to load the AIS into DDR.
  DEBUG_printString("Application image located.  Parsing AIS...\r\n");
  gEntryPoint = (Uint32) AIS_parseImage( (void *)(blockAddr + 4));
  if ( gEntryPoint != NULL )
  {
    DEBUG_printString("\r\nApplication AIS image parsed and loaded...\r\n");
    return E_PASS;
  }
  else
  {
    DEBUG_printString("\r\nApplication AIS image parsing failed...\r\n");
    return E_FAIL;
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/


/************************************************************
* End file                                                  *
************************************************************/

/* -------------------------------------------------------------------------- 
    HISTORY
 		v1.00  -  DJA  -  07-Nov-2007
			Initial Release 	   
 ----------------------------------------------------------------------------- */
