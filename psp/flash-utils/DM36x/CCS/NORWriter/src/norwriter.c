/* --------------------------------------------------------------------------
  FILE        : norwriter.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Main function for flashing the NOR device on the DM644x EVM  
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

static Uint32 norwriter(void);


/************************************************************
* Local Variable Definitions                                *
\***********************************************************/


/************************************************************
* Global Variable Definitions
************************************************************/


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

  DEVICE_pinmuxControl( 0, DEVICE_PINMUX_EMIF_MASK, DEVICE_PINMUX_EMIF_EN );
	
	// Execute the NOR flashing
  status = norwriter();

  if (status != E_PASS)
  {
    printf( "\tNOR flashing failed!\r\n");
  }
  else
  {
    printf( "\tNOR boot preparation was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 norwriter()
{
  NORWRITER_Boot  gNorBoot;
  NOR_InfoHandle hNorInfo;

  Bool    bUseUBL = FALSE;
  FILE	*fPtr;
  Uint8	*ublPtr, *appPtr;
  Int32	ublFileSize = 0,appFileSize = 0;
  Int8	fileName[256];
  Int8    answer[24];
  Uint32   baseAddress = 0, blockSize = 0, blockAddr = 0;

  DEBUG_printString( "Starting DM644x_NORWriter.\r\n");

  // Initialize NOR Flash
  hNorInfo = NOR_open( (Uint32)&EMIFStart, (Uint8)DEVICE_emifBusWidth() );
  if (hNorInfo == NULL)
	{
    DEBUG_printString( "\tERROR: NOR Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Ask if a UBL will be used at start of NOR flash
  DEBUG_printString("Do you wish to use a UBL in the NOR flash (Y/N)?\r\n");
	DEBUG_readChar(answer);
  bUseUBL =  ( (answer[0] == 'y') || (answer[0] == 'Y') );

  // Set base address to start putting data at
  baseAddress = hNorInfo->flashBase;

  if (bUseUBL)
  {
    DEBUG_printString("Enter the UBL file Name:\r\n");
    DEBUG_readString(fileName);
    fflush(stdin);

    // Open an File from the PC
    fPtr = fopen(fileName, "rb");
    if(fPtr == NULL)
    {
      DEBUG_printString("\tERROR: File ");
      DEBUG_printString(fileName);
      DEBUG_printString(" open failed.\r\n");
      return E_FAIL;
    }

    // Read file size
    fseek(fPtr,0,SEEK_END);
    ublFileSize = ftell(fPtr);

    // Setup pointer in RAM
    ublPtr = (Uint8 *) UTIL_allocMem(ublFileSize);

    if(ublFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }

    fseek(fPtr,0,SEEK_SET);

    if (ublFileSize != fread(ublPtr, 1, ublFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }

    fclose (fPtr);

    // Erasing the Flash
    if ( NOR_erase(hNorInfo, baseAddress, ublFileSize) != E_PASS )
    {
      DEBUG_printString("\tERROR: Erasing NOR failed.\r\n");
      return E_FAIL;
    }
	        
    // Write the actual application to the flash
    if (NOR_writeBytes( hNorInfo, baseAddress, ublFileSize, (Uint32)ublPtr) != E_PASS)
    {
      DEBUG_printString("\tERROR: Writing NOR failed.\r\n");
      return E_FAIL;
    }

    // Get block size and base of block where UBL was written
    NOR_getBlockInfo(hNorInfo,baseAddress+ublFileSize,&blockSize,&blockAddr);

    // Calculate the new base address at which the U-boot or App will now start
    baseAddress =  (blockAddr + blockSize);
  }

  // Read the file from host
  DEBUG_printString("Enter the U-boot or application file name:\r\n");
  DEBUG_readString(fileName);
  fflush(stdin);

  // Open an File from the hard drive
  fPtr = fopen(fileName, "rb");
  if(fPtr == NULL)
  {
    DEBUG_printString("\tERROR: File ");
    DEBUG_printString(fileName);
    DEBUG_printString(" open failed.\r\n");
    return E_FAIL;
  }

	// Read file size
	fseek(fPtr,0,SEEK_END);
  appFileSize = ftell(fPtr);

  // Check to make sure image was read correctly
  if(appFileSize == 0)
  {
    DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
    fclose (fPtr);
    return E_FAIL;
  }
  
  // Check to make sure the app image will fit 
	if ( appFileSize > (hNorInfo->flashSize - (bUseUBL?(blockSize + sizeof(gNorBoot)):0)) )
  {
    DEBUG_printString("\tERROR: File too big.. Closing program.\r\n");
    fclose (fPtr);
    return E_FAIL;
  }

  if (bUseUBL)
  {
    // Get the entry point and load addresses
    DEBUG_printString("Enter the U-boot or application entry point: \n");
    DEBUG_readString(answer);
    gNorBoot.entryPoint = strtoul(answer, NULL, 16);
    fflush(stdin);
    if ( (gNorBoot.entryPoint < DEVICE_DDR2_START_ADDR) || (gNorBoot.entryPoint > DEVICE_DDR2_END_ADDR) )
    {
      DEBUG_printString("\tWARNING: Entry point not in acceptable range - using default 0x81080000.\r\n");
      gNorBoot.entryPoint = 0x81080000;
    }

    DEBUG_printString("Enter the U-boot or application load address: \r\n");
    DEBUG_readString(answer);
    gNorBoot.ldAddress = strtoul(answer, NULL, 16);
    if ( (gNorBoot.ldAddress < DEVICE_DDR2_START_ADDR) || (gNorBoot.ldAddress > DEVICE_DDR2_END_ADDR) )
    {
      DEBUG_printString("\tWARNING: Load address not in acceptable range - using default 0x81080000.\r\n");
      gNorBoot.ldAddress = 0x81080000;
    }

    gNorBoot.magicNum = UBL_MAGIC_BIN_IMG;
    gNorBoot.appSize = appFileSize;
  }

  // Setup pointer in RAM
  appPtr = (Uint8 *) UTIL_allocMem(appFileSize);

  fseek(fPtr,0,SEEK_SET);

  if (appFileSize != fread(appPtr, 1, appFileSize, fPtr))
  {
	  DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
  }

  fclose(fPtr);

  if (NOR_erase( hNorInfo, baseAddress, (appFileSize + (bUseUBL?sizeof(gNorBoot):0)) ) != E_PASS)
  {
    DEBUG_printString("\tERROR: Erasing NOR failed.\r\n");
    return E_FAIL;
  }

	// Write the NOR_BOOT header to the flash
  if (bUseUBL)
  {
    if (NOR_writeBytes( hNorInfo, baseAddress, sizeof(gNorBoot), (Uint32) &gNorBoot) != E_PASS)
    {
      printf("\tERROR: Writing NOR failed.\r\n");
      return E_FAIL;
    }
  }

	// Write the application data to the flash
	if (NOR_writeBytes( hNorInfo, baseAddress + (bUseUBL?sizeof(gNorBoot):0), appFileSize, (Uint32)appPtr) != E_PASS)
  {
  printf("\tERROR: Writing NOR failed.\r\n");
  return E_FAIL;
  }

	return E_PASS;
}


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  06-Nov-2007
 	        Completion
 ----------------------------------------------------------------------------- */

