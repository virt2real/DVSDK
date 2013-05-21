/* --------------------------------------------------------------------------
    FILE        : aistest.c 				                             	 	        
    PROJECT     : DM648 CCS AIS Utility
    AUTHOR      : Daniel Allred
    DESC        : Main function for flashing the NOR device on the DM648 EVM  
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

// I2C module
#include "i2c.h"

// SPI module
#include "spi.h"

//AIS util module
#include "ais_util.h"

// This module's header file 
#include "aistest.h"



/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define KAILASH_ENABLE_CTRL_REG_WRITES   *((volatile Uint32 *)(0x02049054)) = 0xADDDECAF

#define KAILASH_DEVCFG_PINMUX_SPIUARTEN_MASK              (0x00003000u)
#define KAILASH_DEVCFG_PINMUX_SPIUARTEN_SHIFT             (12u)
#define KAILASH_DEVCFG_PINMUX_SPIUARTEN_SPIENABLE         (0x1u)
#define KAILASH_DEVCFG_PINMUX_SPIUARTEN_UARTEN_NOFC       (0x3)
#define KAILASH_DEVCFG_PINMUX_SPIUARTEN_UARTEN_FC         (0x2)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 aistest(void);

static Uint32 LOCAL_I2C_read(void * hI2CInst,Uint8 *readBuff, Uint32 byteCnt, Uint32 timeOut);
static Uint32 LOCAL_I2C_write(void * hI2CInst,Uint8 *writeBuff, Uint32 byteCnt, Uint32 timeOut);
static Uint32 LOCAL_SPI_read();
static Uint32 LOCAL_SPI_write();


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

  UTIL_waitLoop(1000000);

  // Execute the NOR flashing
  status = aistest();

  if (status != E_PASS)
  {
    DEBUG_printString("\tAIS host loading failed!\r\n");
  }
  else
  {
    DEBUG_printString("\tAIS host loading was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 aistest()
{
  AIS_IO_Obj aisObj;

  FILE	*fPtr;
  Uint8	*appPtr;
  Int32	appFileSize = 0;
  Int8	fileName[256];

  DEBUG_printString( "Starting DM648_AISUtil Host Program.\r\n");

  // Ask what interface to use (SPI or I2C)
  DEBUG_printString("What interface, I or S (I=I2C, S=SPI)? \r\n");
  DEBUG_readString(fileName);

  if ((strcmp(fileName,"I") == 0) || (strcmp(fileName,"i") == 0) )
  {
    I2C_Config i2cCfg;
    I2C_InfoHandle hi2cInfo;
    i2cCfg.addrMode = I2C_ADDRESSING_7BIT;
    i2cCfg.ownAddr = 0x28;
    i2cCfg.prescalar = 12;
    i2cCfg.i2cclkl = 60;
    i2cCfg.i2cclkh = 60;

    // Open the I2C object
    hi2cInfo = I2C_open(0,I2C_ROLE_MASTER,I2C_MODE_AUTO_STOP,&i2cCfg);
    hi2cInfo->slaveAddr = 0x29;
    
    // Assign aisObj elements
    aisObj.hostDevice = AIS_I2C;
    aisObj.readFxn = (FxnPtr) LOCAL_I2C_read;
    aisObj.writeFxn = (FxnPtr) LOCAL_I2C_write;
    aisObj.ioBits = 8;
    aisObj.posN = 1;
    aisObj.hInst = (void *) hi2cInfo;
    aisObj.cfgFxn = NULL;
    aisObj.ioDelay = 0;
    aisObj.opcodeDelay = 0;
  }
  else if ((strcmp(fileName,"S") == 0) || (strcmp(fileName,"s") == 0) )
  {
    SPI_Config spiCfg;
    SPI_InfoHandle hSpiInfo;

    spiCfg.charLen = 16;
    spiCfg.polarity = 1;
    spiCfg.phase = 0;
    spiCfg.prescalar = 255;

    // Set up required pinmuxing
    KAILASH_ENABLE_CTRL_REG_WRITES;
	  SYSTEM->PINMUX[0] = ( SYSTEM->PINMUX[0] & (~KAILASH_DEVCFG_PINMUX_SPIUARTEN_MASK))
	                       | (KAILASH_DEVCFG_PINMUX_SPIUARTEN_SPIENABLE << KAILASH_DEVCFG_PINMUX_SPIUARTEN_SHIFT);

    hSpiInfo = SPI_open(0,SPI_ROLE_MASTER,SPI_MODE_3PIN,&spiCfg);


    aisObj.hostDevice = AIS_SPI;
    aisObj.readFxn = (FxnPtr) LOCAL_SPI_read;
    aisObj.writeFxn = (FxnPtr) LOCAL_SPI_write;
    aisObj.ioBits = 16;
    aisObj.posN = 2;
    aisObj.hInst = (void *) hSpiInfo;
    aisObj.cfgFxn = NULL;
    aisObj.ioDelay = 0;
    aisObj.opcodeDelay = 0;
  }
  else
  {
    DEBUG_printString("\tERROR: Not supported mode.");
    return E_FAIL;
  }

  // Read the UBL file from host
  DEBUG_printString("Enter the binary AIS file name to load to slave (enter 'none' to skip): \r\n");
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
    appFileSize = ftell(fPtr);

    // Check to make sure image was read correctly
    if(appFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }

    // Setup pointer in RAM
    appPtr = (Uint8 *) UTIL_allocMem(appFileSize);

    fseek(fPtr,0,SEEK_SET);

    if (appFileSize != fread(appPtr, 1, appFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }
    fclose (fPtr);

    // Write the application data to the flash
    if ( AIS_parse((void *)appPtr,&aisObj) != E_PASS )
    {
      DEBUG_printString("\tERROR: Writing NOR failed.\r\n");
      return E_FAIL;
    }
  }


  return E_PASS;
}

static Uint32 LOCAL_I2C_read(void * hI2CInst, Uint8 *readBuff, Uint32 byteCnt, Uint32 timeOut)
{
  return I2C_readBytes((I2C_InfoHandle)hI2CInst,byteCnt, readBuff);
}


static Uint32 LOCAL_I2C_write(void * hI2CInst, Uint8 *writeBuff, Uint32 byteCnt, Uint32 timeOut)
{
  return I2C_writeBytes((I2C_InfoHandle)hI2CInst,byteCnt, writeBuff);
}

static Uint32 LOCAL_SPI_read(void * hSPIInst, Uint8 *readBuff, Uint32 byteCnt, Uint32 timeOut)
{
  Uint32 status;
  SPI_enableCS((SPI_InfoHandle) hSPIInst);
  status =  SPI_readBytes((SPI_InfoHandle) hSPIInst, byteCnt, readBuff);
  SPI_disableCS((SPI_InfoHandle) hSPIInst);
  return status;
}

static Uint32 LOCAL_SPI_write(void * hSPIInst, Uint8 *writeBuff, Uint32 byteCnt, Uint32 timeOut)
{
  Uint32 status;
  SPI_enableCS((SPI_InfoHandle) hSPIInst);
  status = SPI_writeBytes((SPI_InfoHandle) hSPIInst, byteCnt, writeBuff);
  SPI_disableCS((SPI_InfoHandle) hSPIInst);
  return status;
}


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  16-Aug-2007
 	        Completion
 ----------------------------------------------------------------------------- */


