/* --------------------------------------------------------------------------
  FILE      : spi_mem.c
  PROJECT   : Catalog Boot-Loader and Flasher
  AUTHOR    : Daniel Allred
  DESC      : Generic SPI memory driver file
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Util functions
#include "util.h"

// SPI module's header file 
#include "spi.h"

// This module's header file
#include "spi_mem.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static void LOCAL_xferAddrBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 addr);
static void LOCAL_readDataBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 byteCnt, Uint8 *data);
static void LOCAL_writeDataBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 byteCnt, Uint8 *data);

/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

#ifdef USE_IN_ROM
SPI_MemInfoObj gSPIMemInfo;
#endif


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze SPI interface
SPI_MemInfoHandle SPI_MEM_open(Uint32 spiPeripheralNum)
{
  Uint8 spibuf;
  SPI_Config spiCfg;
  SPI_MemInfoHandle hSPIMemInfo;
  
     
#ifdef USE_IN_ROM
  hSPIMemInfo = (SPI_MemInfoHandle) &gSPIInfo;
#else
  hSPIMemInfo = (SPI_MemInfoHandle) UTIL_allocMem(sizeof(SPI_MemInfoObj));
#endif

  // Transfer 8 bits at a time
  spiCfg.charLen = 8;
  
  // Use industry standard mode 3 (note that our SPI peripheral phase value is
  // inverted compared to all other industry players)
  spiCfg.phase = 0;
  spiCfg.polarity = 1;
  spiCfg.prescalar = 79;

  hSPIMemInfo->hSPIInfo = SPI_open(spiPeripheralNum,
    SPI_ROLE_MASTER,
    SPI_MODE_3PIN,
    &spiCfg);

  
  // Assert chip select
  SPI_enableCS(hSPIMemInfo->hSPIInfo);

  // Send memory read command
  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_READ);

  // Send 8-bit adresss, receive dummy
  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);

  // Receive data from 8-bit device OR
  // Transmit next part of 16-bit address and receive dummy
  spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);

  // Check for 8-bit memory
  if (spibuf != 0x00)
    hSPIMemInfo->addrWidth = 8;
  else
  {
    // Receive data from 16-bit device OR
    // Transmit next part of 24-bit address and receive dummy
    spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);

    // Check for 16-bit memory
    if (spibuf != 0x00)
      hSPIMemInfo->addrWidth = 16;
    else
    {
      // Receive data from 24-bit device OR
      // Transmit dummy
      spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);

      // Check for 24-bit memory
      if (spibuf != 0x00)
        hSPIMemInfo->addrWidth = 24;
      else
      {
        // Assume Atmel devices
      }
    }
  }

  // De-assert chip select
  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  // Try to determine if this is flash or EEPROM by
  // issuing a DEVICE ID Read command

  // Assert chip select
  SPI_enableCS(hSPIMemInfo->hSPIInfo);

  // Send memory read command
  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_JEDEC_ID);

  // Send dummy data, receive manufacture ID
  spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);

  if (spibuf != 0x00)
  {
    hSPIMemInfo->memType = SPI_MEM_TYPE_FLASH;
    
    // Send dummy data, receive devicd ID1
    spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);

    // Send dummy data, receive manufacture ID
    spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);
  }
  else
  {
    hSPIMemInfo->memType = SPI_MEM_TYPE_EEPROM;
  }

  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  return hSPIMemInfo;
}

// Routine to read data from SPI
Uint32 SPI_MEM_readBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *dest)
{
  SPI_enableCS(hSPIMemInfo->hSPIInfo);

  // Send memory read command
  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_READ);

  // Send the address bytes
  LOCAL_xferAddrBytes(hSPIMemInfo,addr);

  // Receive data bytes
  LOCAL_readDataBytes(hSPIMemInfo, byteCnt, dest);

  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  return E_PASS;
}


// Defining this macro for the build will cause write (flash) ability to be removed
// This can be used for using this driver as read-only for ROM code
#ifndef USE_IN_ROM    

// Generic routine to write data to SPI
Uint32 SPI_MEM_writeBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src)
{
  Uint8 spibuf;
  
  // Set WE Latch
  SPI_enableCS(hSPIMemInfo->hSPIInfo);
  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_WREN);
  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  SPI_enableCS(hSPIMemInfo->hSPIInfo);
  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_RDSR);
  spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_WREN);
  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  // Verify latch is set and no write is in progress
  if ((!(spibuf & 0x02)) || (spibuf & 0x01) )
    return E_FAIL;

  SPI_enableCS(hSPIMemInfo->hSPIInfo);

  SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_WRITE);

  LOCAL_xferAddrBytes(hSPIMemInfo,addr);

  LOCAL_writeDataBytes(hSPIMemInfo,byteCnt,src);

  SPI_disableCS(hSPIMemInfo->hSPIInfo);

  // Wait until write is complete
  do
  {
    SPI_enableCS(hSPIMemInfo->hSPIInfo);
    SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_RDSR);
    spibuf = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,SPI_MEM_CMD_WREN);
    SPI_disableCS(hSPIMemInfo->hSPIInfo);
  } while ( spibuf & 0x01 );

  return E_PASS;
}

// Verify data written by reading and comparing byte for byte
Uint32 SPI_MEM_verifyBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src, Uint8* dest)
{
  Uint32 i;

  if (SPI_MEM_readBytes(hSPIMemInfo,addr,byteCnt,dest) != E_PASS);
    return E_FAIL;

  for (i=0; i<byteCnt; i++)
  {
    if (dest[i] != src[i]) return E_FAIL;
  }

  return E_PASS;
}

// Global Erase NOR Flash
Uint32 SPI_MEM_globalErase(SPI_MemInfoHandle hSPIMemInfo)
{
  return E_PASS;
}

// NAND Flash erase block function
Uint32 SPI_MEM_eraseBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 startAddr, Uint32 byteCnt)
{  
  return E_PASS;
}
#endif

/************************************************************
* Local Function Definitions                                *
************************************************************/

static void LOCAL_xferAddrBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 addr)
{
  Uint32 i;

  for (i=0; i<hSPIMemInfo->addrWidth; i+=8)
  {
    Uint8 addrByte = ((addr >> (hSPIMemInfo->addrWidth - i - 8)) & 0xFF);
    SPI_xferOneByte(hSPIMemInfo->hSPIInfo,addrByte);
  }
}

static void LOCAL_writeDataBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 byteCnt, Uint8 *data)
{
  Uint32 i;

  for (i=0; i< byteCnt; i++)
  {
    SPI_xferOneByte(hSPIMemInfo->hSPIInfo,data[i]);
  }
}

static void LOCAL_readDataBytes(SPI_MemInfoHandle hSPIMemInfo, Uint32 byteCnt, Uint8 *data)
{
  Uint32 i;

  for (i=0; i< byteCnt; i++)
  {
    data[i] = SPI_xferOneByte(hSPIMemInfo->hSPIInfo,0x00);
  }
}


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 19-Aug-2008
      Initial release
-------------------------------------------------------------------------- */

