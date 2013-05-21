/* --------------------------------------------------------------------------
    FILE        : i2cwriter.c
    PROJECT     : C672x CCS I2C Flashing Utility
    AUTHOR      : Daniel Allred
    DESC        : Main function for flashing the I2C device on the C672x PADK  
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

// I2C memory driver include
#include "i2c_mem.h"

// This module's header file 
#include "i2cwriter.h"


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

static Uint32 i2cwriter(void);


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

  // Execute the I2C flashing
  status = i2cwriter();

  if (status != E_PASS)
  {
    DEBUG_printString("\tI2C EEPROM flashing failed!\r\n");
  }
  else
  {
    DEBUG_printString("\tI2C EEPROM boot preparation was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 i2cwriter()
{
  I2C_MemInfoHandle hI2cMemInfo;

  FILE	*fPtr;
  Uint8	*appPtr;
  Int32	appFileSize = 0;
  Int8	fileName[256];
  Uint32  baseAddress = 0;

  I2C_ConfigObj i2cCfg;
  I2C_MemConfigObj i2cMemCfg;

  DEBUG_printString( "Starting I2CWriter.\r\n");

  // Initialize I2C Config
  i2cCfg.ownAddr = 0x29;
  i2cCfg.prescalar = 14;
  i2cCfg.i2cclkl = 6;
  i2cCfg.i2cclkh = 6;
  i2cCfg.addrMode = I2C_ADDRESSING_7BIT;

  // Initialize I2C Memory Config
  i2cMemCfg.i2cMemAddr = 0x50;
  i2cMemCfg.addrWidth = 16;
  i2cMemCfg.pageSize = 64;
  i2cMemCfg.memorySize = 32 *1024;

  hI2cMemInfo = I2C_MEM_open(0,&i2cCfg,&i2cMemCfg);
  if (hI2cMemInfo == NULL)
  {
    DEBUG_printString( "\tERROR: I2C Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Set base address to start putting data at
  baseAddress = 0x00;

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
    else if ( appFileSize > hI2cMemInfo->hI2CMemCfg->memorySize)
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

    // Erase the I2C flash to accomodate the file size
#if (0)
    if (I2C_MEM_eraseBytes( hI2cMemInfo, baseAddress, appFileSize ) != E_PASS)
    {
      DEBUG_printString("\tERROR: Erasing I2C failed.\r\n");
      return E_FAIL;
    }
#endif

    {
      Uint8 *verifyBuffer = UTIL_allocMem(appFileSize);

      // Write the application data to the flash
      if (I2C_MEM_writeBytes(hI2cMemInfo, baseAddress, appFileSize, appPtr) != E_PASS)
      {
        DEBUG_printString("\tERROR: Writing I2C memory failed.\r\n");
        return E_FAIL;
      }

      if (I2C_MEM_verifyBytes(hI2cMemInfo, baseAddress, appFileSize, appPtr, verifyBuffer) != E_PASS)
      {
        DEBUG_printString("\tERROR: Verifying I2C memory failed.\r\n");
        return E_FAIL;
      }
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
