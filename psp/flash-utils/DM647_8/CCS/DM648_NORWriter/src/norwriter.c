/* --------------------------------------------------------------------------
    FILE        : norwriter.c 				                             	 	        
    PURPOSE     : NOR writer main program
    PROJECT     : DM648 CCS NOR Flashing Utility
    AUTHOR      : Daniel Allred
    DESC        : Main function for flashing the NOR device on the DM648 EVM  
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

// I2C_ECP module (for contacting the EVM's MSP430)
#include "i2c_ecp.h"

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

  UTIL_waitLoop(1000000);

  // Set board-level muxes for EMIFA access
  status = I2C_ECP_write(I2C_ECP_VMX_REG,0x20);
  if (status != E_PASS)
  {
    DEBUG_printString("Write to ECP EMIF/VP control register appears to have failed.");
    return;
  }

  DEVICE_pinmuxControl( 0, DEVICE_PINMUX_EMIF_MASK, DEVICE_PINMUX_EMIF_EN );

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
  Uint8	*ublPtr, *appPtr;
  Int32	ublFileSize = 0,appFileSize = 0;
  Int8	fileName[256];
  Uint32  baseAddress = 0, blockSize, blockAddr;

  DEBUG_printString( "Starting DM648_NORWriter.\r\n");

  // Initialize NOR Flash
  hNorInfo = NOR_open((Uint32)&NORStart);
  if (hNorInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NOR Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Set base address to start putting data at
  baseAddress = hNorInfo->flashBase;

  // Read the UBL file from host
  DEBUG_printString("Enter the binary AIS UBL file name (enter 'none' to skip): \r\n");
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

    // Read file size
    fseek(fPtr,0,SEEK_END);
    ublFileSize = ftell(fPtr);

    // Check to make sure image was read correctly
    if(ublFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }
    // Check to make sure the app image will fit 
    else if (ublFileSize > hNorInfo->flashSize )
    {
      DEBUG_printString("\tERROR: File too big.. Closing program.\r\n");
      fclose (fPtr);
    }

    // Setup pointer in RAM
    ublPtr = (Uint8 *) UTIL_allocMem(ublFileSize);

    fseek(fPtr,0,SEEK_SET);

    if (ublFileSize != fread(ublPtr, 1, ublFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }
    fclose (fPtr);

    // Erase the NOR flash to accomadate the file size
    if (NOR_erase( hNorInfo, baseAddress, ublFileSize ) != E_PASS)
    {
      DEBUG_printString("\tERROR: Erasing NOR failed.\r\n");
      return E_FAIL;
    }

    // Write the application data to the flash
    if (NOR_writeBytes( hNorInfo, baseAddress, ublFileSize, (Uint32)ublPtr) != E_PASS)
    {
      DEBUG_printString("\tERROR: Writing NOR failed.\r\n");
      return E_FAIL;
    }
  }

  // Read the file from host
  DEBUG_printString("Enter the binary AIS application file name (enter 'none' to skip): \r\n");
  DEBUG_readString(fileName);
	fflush(stdin);

  if (strcmp(fileName,"none") != 0)
  {
    // Open a file from the hard drive
    fPtr = fopen(fileName, "rb");
    if(fPtr == NULL)
    {
      DEBUG_printString("\tERROR: File open failed.\r\n");
      return E_FAIL;
    }

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
    else if ( (appFileSize + ublFileSize) > hNorInfo->flashSize )
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

    // Get block info (size and start address) for the block in which UBL is written
    NOR_getBlockInfo(hNorInfo, (baseAddress + ublFileSize), &blockSize, &blockAddr);
    // Get block info (size and start address) for the block immediately following where the UBL is written
    NOR_getBlockInfo(hNorInfo, (blockAddr + blockSize), &blockSize, &blockAddr);

    // Erase the NOR flash to accomadate the file size
    if (NOR_erase( hNorInfo, blockAddr, appFileSize ) != E_PASS)
    {
      DEBUG_printString("\tERROR: Erasing NOR failed.\r\n");
      return E_FAIL;
    }

    // Write the application data to the flash
    if (NOR_writeBytes( hNorInfo, blockAddr, appFileSize, (Uint32)appPtr) != E_PASS)
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

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  16-Aug-2007
 	        Completion
 ----------------------------------------------------------------------------- */


