/* --------------------------------------------------------------------------
  FILE      : i2c_mem.c
  PROJECT   : Catalog Boot-Loader and Flasher
  AUTHOR    : Daniel Allred
  DESC      : Generic I2C memory driver
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Util functions
#include "util.h"

// The generic I2C module driver 
#include "i2c.h"

// This module's header file 
#include "i2c_mem.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
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

#ifdef USE_IN_ROM
I2C_MemInfoObj gI2CMemInfo;
#endif


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze I2C MEM interface and find the details of the I2C memory used
I2C_MemInfoHandle I2C_MEM_open(Uint32 i2cPeripheralNum, I2C_ConfigHandle hI2cCfg,  I2C_MemConfigHandle hI2CMemCfg)
{
  I2C_MemInfoHandle hI2CMemInfo;

  // Set I2CMemInfo handle
#ifdef USE_IN_ROM
  hI2CMemInfo = (I2C_MemInfoHandle) &gI2CMemInfo;
#else
  hI2CMemInfo = (I2C_MemInfoHandle) UTIL_allocMem(sizeof(I2C_MemInfoObj));
#endif

  hI2CMemInfo->hI2CMemCfg = hI2CMemCfg;

  hI2cCfg->addrMode   = I2C_ADDRESSING_7BIT;
  
  // Open I2C peripheral
  hI2CMemInfo->hI2CInfo = I2C_open(i2cPeripheralNum, I2C_ROLE_MASTER, I2C_MODE_MANUAL_STOP, hI2cCfg);
  if (hI2CMemInfo->hI2CInfo == NULL)
    return NULL;
  
  // Set the current slave address
  hI2CMemInfo->hI2CInfo->slaveAddr = hI2CMemCfg->i2cMemAddr;

  return hI2CMemInfo;
}


// Routine to read a page from I2C
Uint32 I2C_MEM_readBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *dest)
{
  Uint8 localAddr[4];

  // Check desired byte count verse
  if ((addr+byteCnt) > hI2CMemInfo->hI2CMemCfg->memorySize)
    return E_FAIL;

  // Write address bytes
  localAddr[0] = (addr>>8) & 0xFF;
  localAddr[1] = (addr>>0) & 0xFF;
  if ( I2C_writeBytes(hI2CMemInfo->hI2CInfo,2,localAddr) != E_PASS )
  {
    return E_FAIL;
  }

  // Read the data bytes
  if ( I2C_readBytes(hI2CMemInfo->hI2CInfo,byteCnt,dest) != E_PASS )
  {
    return E_FAIL;
  }

  // Manually assert stop condition
  I2C_setStopCondition(hI2CMemInfo->hI2CInfo);

  return E_PASS;
}


// Defining this macro for the build will cause write (flash) ability to be removed
// This can be used for using this driver as read-only for ROM code
#ifndef USE_IN_ROM    

// Generic routine to write a page of data to I2C EEPROM
Uint32 I2C_MEM_writeBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src)
{

  Int32 i,j,k, cycCnt;
  Uint8 localBuffer[256];

  if ((addr+byteCnt) > hI2CMemInfo->hI2CMemCfg->memorySize)
    return E_FAIL;

  // Write the bytes in page chunks
  cycCnt = 0;
	for ( i=0; i<byteCnt; i+= k )
	{
		k = ( (byteCnt-i) > hI2CMemInfo->hI2CMemCfg->pageSize ) ? hI2CMemInfo->hI2CMemCfg->pageSize : (byteCnt-i);

    // Copy the addr and data to local buffer
    localBuffer[0] = (addr>>8) & 0xFF;
    localBuffer[1] = (addr>>0) & 0xFF;
    for (j=0;j<k;j++)
    {
      localBuffer[j+2] = src[j];
    }

    // Then write addr and data bytes
    if ( I2C_writeBytes(hI2CMemInfo->hI2CInfo,k+2,localBuffer) != E_PASS )
		{
      DEBUG_printString("On Cycle Count ");
      DEBUG_printHexInt(cycCnt);
      DEBUG_printString("\r\n");
      return E_FAIL;
    }

    // Manually assert stop condition
    I2C_setStopCondition(hI2CMemInfo->hI2CInfo);

    // Wait for EEPROM  to finish
    UTIL_waitLoop(1000000);
		
    // Increment addr value and data pointer
		addr += k;
    src += k;
    cycCnt++;
  }


  return E_PASS;
}

// Verify data written by reading and comparing byte for byte
Uint32 I2C_MEM_verifyBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src, Uint8* dest)
{
  Uint32 i;

  if (I2C_MEM_readBytes(hI2CMemInfo,addr,byteCnt,dest) != E_PASS)
    return E_FAIL;

  for (i=0; i<byteCnt; i++)
  {
    if (dest[i] != src[i]) return E_FAIL;
  }

  return E_PASS;
}

// Global Erase NOR Flash
Uint32 I2C_MEM_globalErase(I2C_MemInfoHandle hI2CMemInfo)
{
  return E_PASS;
}

// NAND Flash erase block function
Uint32 I2C_MEM_eraseBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 startAddr, Uint32 byteCnt)
{  
  return E_PASS;
}
#endif

/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 19-Aug-2008
      Initial release
-------------------------------------------------------------------------- */

