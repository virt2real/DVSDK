/* --------------------------------------------------------------------------
  FILE        : norboot.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : UBL Nor boot functionality for when a UBL image sits
                at the start of the NOR flash
----------------------------------------------------------------------------- */

#ifdef UBL_NOR

// General type include
#include "tistdtypes.h"

// Device specific module
#include "device.h"

// Debug I/O module
#include "debug.h"

// Misc utility module
#include "util.h"

// Main UBL module
#include "ubl.h"

// NOR driver fucntions
#include "nor.h"

// This module's header file
#include "norboot.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 EMIFStart;
extern __FAR__ Uint32 DDRStart;
extern __FAR__ Uint32 DDRSize;
extern __FAR__ Uint32 DRAMSize;


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


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Function to find out where the Application is and copy to RAM
Uint32 NORBOOT_copy(void)
{
  NOR_InfoHandle hNorInfo = NULL;
  volatile NORBOOT_HeaderHandle	hNorHeader = 0;
  VUint32 *norPtr = NULL;
  VUint32	*ramPtr = NULL;
  Uint32 count = 0, blkSize, blkAddress;

  DEBUG_printString("Starting NOR Copy...\r\n");

  // Nor Initialization
  hNorInfo = NOR_open((Uint32)&EMIFStart, (Uint8)DEVICE_emifBusWidth() );
  if (hNorInfo == NULL)
    return E_FAIL;
	    
  NOR_getBlockInfo( hNorInfo, ((hNorInfo->flashBase) + UBL_IMAGE_SIZE), &blkSize, &blkAddress );

  // Assume header is at start of Block 1 of NOR device (Block 0 has 
  // this UBL)
  hNorHeader = (NORBOOT_HeaderHandle) (blkAddress + blkSize);

  // Check for magic number
  if((hNorHeader->magicNum & 0xFFFFFF00) != MAGIC_NUMBER_VALID)
  {
    return E_FAIL;
  }

  // Set the Start Address
  norPtr = (Uint32 *)(((Uint8*)hNorHeader) + sizeof(NORBOOT_HeaderObj));

  ramPtr = (Uint32 *) hNorHeader->ldAddress;

  // Copy data to RAM
  for(count = 0; count < ((hNorHeader->appSize + 3)/4); count ++)
  {
    ramPtr[count] = norPtr[count];
  }
  gEntryPoint = hNorHeader->entryPoint;

  // Since our entry point is set, just return success
  return E_PASS;

}



/************************************************************
* Local Function Definitions                                *
************************************************************/


/************************************************************
* End file                                                  *
************************************************************/
#endif  // #ifdef UBL_NOR
