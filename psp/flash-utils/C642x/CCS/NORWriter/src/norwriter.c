/* --------------------------------------------------------------------------
  FILE        : norwriter.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : CCS NOR Flashing Utility  
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "norwriter.h"

// NOR driver include
#include "nor.h"

// Misc. utility function include
#include "util.h"

// Debug module
#include "debug.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 norwriter(void);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions
************************************************************/

#pragma DATA_SECTION(NORStart,".aemif_mem");
VUint32 __FAR__ NORStart;

#pragma DATA_SECTION(DDRStart,".ddr_mem");
VUint32 __FAR__ DDRStart;


/************************************************************
* Global Function Definitions                               *
************************************************************/

void main( void )
{
  Uint32 status;

  // Init memory alloc pointer to start of DDR heap
  UTIL_setCurrMemPtr(0);

  // System init
  if (DEVICE_init() !=E_PASS)
  {
    exit();
  }

  // Execute the NOR flashing
  status = norwriter();

  if (status != E_PASS)
  {
    DEBUG_printString("\tNOR flashing failed!\r\n");
  }
  else
  {
    DEBUG_printString("\tNOR boot preparation was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 norwriter()
{
  NOR_InfoHandle hNorInfo;

  FILE	*fPtr;
  Uint8	*appPtr;
  Int32	appFileSize = 0;
  Int8	fileName[256];
  Uint32  baseAddress = 0;

  DEBUG_printString( "Starting NORWriter.\r\n");

  // Initialize NOR Flash
  hNorInfo = NOR_open((Uint32)&NORStart, (Uint8)DEVICE_emifBusWidth() );
  if (hNorInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NOR Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Set base address to start putting data at
  baseAddress = hNorInfo->flashBase;

  // Read the UBL file from host
  DEBUG_printString("Enter the binary AIS application file name (enter 'none' to skip): \r\n");
  DEBUG_readString(fileName);
  fflush(stdin);

  if (strcmp(fileName,"none") != 0)
  {
    // Open an File from the hard drive
    fPtr = fopen(fileName, "rb");
    if(fPtr == NULL)
    {
      DEBUG_printString("\tERROR: File ");
      DEBUG_printString(fileName);
      DEBUG_printString(" open failed.\r\n");
      return E_FAIL;
    }

    // Initialize the pointer
    appFileSize = 0;

    // Read file size
    fseek(fPtr,0,SEEK_END);
    appFileSize = ftell(fPtr);

    // Check to make sure image was read correctly
    if(appFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }
    // Check to make sure the app image will fit 
    else if ( appFileSize > hNorInfo->flashSize )
    {
      DEBUG_printString("\tERROR: File too big.. Closing program.\r\n");
      fclose (fPtr);
    }

    // Setup pointer in RAM
    appPtr = (Uint8 *) UTIL_allocMem(appFileSize);

    fseek(fPtr,0,SEEK_SET);

    if (appFileSize != fread(appPtr, 1, appFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }

    fclose (fPtr);

    // Erase the NOR flash to accomadate the file size
    if (NOR_erase( hNorInfo, baseAddress, appFileSize ) != E_PASS)
    {
      DEBUG_printString("\tERROR: Erasing NOR failed.\r\n");
      return E_FAIL;
    }

    // Write the application data to the flash
    if (NOR_writeBytes( hNorInfo, baseAddress, appFileSize, (Uint32)appPtr) != E_PASS)
    {
      DEBUG_printString("\tERROR: Writing NOR failed.\r\n");
      return E_FAIL;
    }
  }
  return E_PASS;
}


/***********************************************************
* End file                                                 *
***********************************************************/
