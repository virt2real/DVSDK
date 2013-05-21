/* --------------------------------------------------------------------------
    FILE        : spiwriter.c 				                             	 	        
    PROJECT     : C672x CCS SPI Flashing Utility
    AUTHOR      : Daniel Allred
    DESC        : Main function for flashing the SPI device on the PADK  
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Misc. utility function include
#include "util.h"

// Debug module
#include "debug.h"

// SPI memory driver include
#include "spi_mem.h"

// This module's header file 
#include "spiwriter.h"


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

static Uint32 spiwriter(void);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


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

  // Execute the SPI flashing
  status = spiwriter();

  if (status != E_PASS)
  {
    DEBUG_printString("\tSPI flashing failed!\r\n");
  }
  else
  {
    DEBUG_printString("\tSPI boot preparation was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 spiwriter()
{
  SPI_MemInfoHandle hSpiMemInfo;

  FILE	*fPtr;
  Uint8	*appPtr;
  Int32	appFileSize = 0;
  Int8	fileName[256];
  Uint32  baseAddress = 0,i;

  DEBUG_printString( "Starting C672x_SPIWriter.\r\n");

  // Initialize SPI Memory Device on SPI0
  hSpiMemInfo = SPI_MEM_open(0);
  if (hSpiMemInfo == NULL)
  {
    DEBUG_printString( "\tERROR: SPI Memory Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Read the AIS file from host
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
    else if ( appFileSize > hSpiMemInfo->memorySize )
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

    // Erase the SPI flash to accomodate the file size
#if (0)
    if (SPI_MEM_erase( hSpiMemInfo, baseAddress, appFileSize ) != E_PASS)
    {
      DEBUG_printString("\tERROR: Erasing SPI failed.\r\n");
      return E_FAIL;
    }
#endif

    // Write the application data to the flash (32 bytes at a time)
    for (i = 0; i<appFileSize; i+=32)
    {
      Uint8 verifyBuffer[32];
      
      if (SPI_MEM_writeBytes( hSpiMemInfo, baseAddress, 32, appPtr) != E_PASS)
      {
        DEBUG_printString("\tERROR: Writing SPI failed.\r\n");
        return E_FAIL;
      }
      
      if (SPI_MEM_verifyBytes( hSpiMemInfo, baseAddress, 32, appPtr, verifyBuffer) != E_PASS)
      {
        DEBUG_printString("\tERROR: Verifying SPI failed.\r\n");
        return E_FAIL;
      }

      baseAddress += 32;
      appPtr += 32;

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
