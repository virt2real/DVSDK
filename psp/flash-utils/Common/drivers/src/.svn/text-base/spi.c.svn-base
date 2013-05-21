/* --------------------------------------------------------------------------
  FILE      : spi.c
  PROJECT   : TI Booting and Flashing Utilities
  AUTHOR    : Daniel Allred
  DESC      : Generic SPI driver file for common SPI peripheral
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Util functions
#include "util.h"

// This module's header file 
#include "spi.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

#define DELAY_AFTER_CS_DN     (4700)
#define DELAY_BEFORE_CS_UP    (3800)
#define DELAY_AFTER_CS_UP     (9400)

/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 LOCAL_setupMode(SPI_InfoHandle hSPIInfo);

/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

#ifdef USE_IN_ROM
SPI_InfoObj gSPIInfo;
#endif


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze NAND interface and find the details of the NAND used
SPI_InfoHandle SPI_open(Uint32 spiPeripheralNum, SPI_Role role, SPI_Mode mode, SPI_Config *config)
{
  DEVICE_SPIRegs *SPI;
  SPI_InfoHandle hSPIInfo;
  
  if (spiPeripheralNum >= SPI_PERIPHERAL_CNT)
    return NULL;
    
#ifdef USE_IN_ROM
  hSPIInfo = (SPI_InfoHandle) &gSPIInfo;
#else
  hSPIInfo = (SPI_InfoHandle) UTIL_allocMem(sizeof(SPI_InfoObj));
#endif

  // Assign the correct register base
  hSPIInfo->peripheralNum = spiPeripheralNum;  
  hSPIInfo->regs = (void *) (((Uint32)SPI0) + (SPI_MEMORYMAP_SPACING *spiPeripheralNum) );
  SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;
  
  // Assign mode and role
  hSPIInfo->role = role;
  hSPIInfo->mode = mode;
  hSPIInfo->config = config;
  
  // Reset the SPI
  SPI_reset(hSPIInfo);

  LOCAL_setupMode(hSPIInfo);

  // Disable CS if in 3-pin mode
  SPI_disableCS(hSPIInfo);
  
  // Enable SPI
  SPI->SPIGCR1 |= ( 1 << 24 );
  
  return hSPIInfo;
}

// Routine to reset the SPI device
Uint32 SPI_reset(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  // Put the SPI in reset
  SPI->SPIGCR0 = 0x00;
  UTIL_waitLoop( 1000 );

  // Release SPI from reset
  SPI->SPIGCR0 = 0x01;

  return E_PASS;
}

Uint32 SPI_readBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *dest)
{
  Uint32 i;

  if (hSPIInfo->config->charLen == 16)
  {
    Uint16 *tempDest = (Uint16 *) dest;
    for (i=0; i< (byteCnt>>1); i++)
    {
      tempDest[i] = SPI_xferOneChar(hSPIInfo,0x0000);
    }
  }
  else if (hSPIInfo->config->charLen == 8)
  {
    for (i=0; i< byteCnt; i++)
    {
      dest[i] = SPI_xferOneChar(hSPIInfo,0x00);
    }
  }

  return E_PASS;
}

Uint32 SPI_writeBytes(SPI_InfoHandle hSPIInfo, Uint32 byteCnt, Uint8 *src)
{
  Uint32 i;

  if (hSPIInfo->config->charLen == 16)
  {
    Uint16 *tempSrc = (Uint16 *) src;
    for (i=0; i< (byteCnt>>1); i++)
    {
      SPI_xferOneChar(hSPIInfo,tempSrc[i]);
    }
  }
  else if (hSPIInfo->config->charLen == 8)
  {
    for (i=0; i< byteCnt; i++)
    {
      SPI_xferOneChar(hSPIInfo,src[i]);
    }
  }

  return E_PASS;
}

Uint32 SPI_xferOneChar(SPI_InfoHandle hSPIInfo, Uint32 dataOut)
{
  Uint32 spiflg, spibuf;
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  Uint32 mask = (0x1 << hSPIInfo->config->charLen) - 1;

  // Write output data
  SPI->SPIDAT0 = dataOut & mask;

  do 
  { 
    spiflg = SPI->SPIFLG;
    if (spiflg & SPI_RXINTFLAG)
    {
      spibuf = (SPI->SPIBUF);
      break;
    }
    if (spiflg & SPI_OVRNINTFLG)
    {
      spibuf = (SPI->SPIBUF);
      SPI->SPIFLG &= SPI_OVRNINTFLG;
      continue;
    }
    if (spiflg & SPI_BITERRFLG)
    {                      
      spibuf = 0x0;
      break;
    }
  } 
  while (TRUE);

  return (spibuf & mask);
}

void SPI_enableCS(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  if (hSPIInfo->mode != SPI_MODE_3PIN)
    return;

  // Clear GPIO
  SPI->SPIPC5 = 0x1 << hSPIInfo->peripheralNum;
  UTIL_waitLoopAccurate ((Uint32)DELAY_AFTER_CS_DN);
}

void SPI_disableCS(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;

  if (hSPIInfo->mode != SPI_MODE_3PIN)
    return;

  UTIL_waitLoopAccurate ((Uint32) DELAY_BEFORE_CS_UP);

  // Set GPIO
  SPI->SPIPC4 = 0x1 << hSPIInfo->peripheralNum;

  UTIL_waitLoopAccurate ((Uint32) DELAY_AFTER_CS_UP);
}


// Defining this macro for the build will cause write (flash) ability to be removed
// This can be used for using this driver as read-only for ROM code
#ifndef USE_IN_ROM    


#endif

/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 LOCAL_setupMode(SPI_InfoHandle hSPIInfo)
{
  DEVICE_SPIRegs *SPI = (DEVICE_SPIRegs *) hSPIInfo->regs;
  
  if (hSPIInfo->role == SPI_ROLE_MASTER)
  {
    SPI->SPIGCR1 = 0
        | ( 0 << 24 )
        | ( 0 << 16 )
        | ( 1 << 1 )
        | ( 1 << 0 );
  }
  else if (hSPIInfo->role == SPI_ROLE_SLAVE)
  {
    SPI->SPIGCR1 = 0
        | ( 0 << 24 )
        | ( 0 << 16 )
        | ( 0 << 1 )
        | ( 0 << 0 ); 
  }
  else
  {
    return E_FAIL;
  }
   
  switch (hSPIInfo->mode)
  {
    case SPI_MODE_3PIN:
      SPI->SPIPC0 =  0
        | ( 1 << 11 )   // SOMI
        | ( 1 << 10 )   // SIMO
        | ( 1 << 9 );   // SPI_CLK
      SPI->SPIPC4 |= 0x01;
      SPI->SPIPC1 |= 0x01;  // Make CS a GPIO output 
      break;
    case SPI_MODE_4PIN_CS:
      SPI->SPIPC0 =  0
        | ( 1 << 11 )   // DI
        | ( 1 << 10 )   // DO
        | ( 1 << 9 )    // CLK
        | ( 1 << 0 );   // CS0
      break;
    case SPI_MODE_4PIN_ENA:
    SPI->SPIPC0 =  0
        | ( 1 << 11 )   // DI
        | ( 1 << 10 )   // DO
        | ( 1 << 9 )    // CLK
        | ( 1 << 8 );   // ENA
      break;
    case SPI_MODE_5PIN:
      SPI->SPIPC0 =  0
        | ( 1 << 11 )   // DI
        | ( 1 << 10 )   // DO
        | ( 1 << 9 )    // CLK
        | ( 1 << 8 )    // ENA
        | ( 1 << 0 );   // CS0
      break;
    default: 
      return E_FAIL;
  }
  
  SPI->SPIFMT[0] = 0x0;
  if (hSPIInfo->config->polarity)
    SPI->SPIFMT[0] |= ( 1 << 17 );   // Polarity
  if (hSPIInfo->config->phase)
    SPI->SPIFMT[0] |= ( 1 << 16 );   // Phase
  SPI->SPIFMT[0] |= (hSPIInfo->config->charLen & 0xFF);
  SPI->SPIFMT[0] |= ((hSPIInfo->config->prescalar & 0xFF) << 8);

  // CSHOLD off, FMT[0] used  
  SPI->SPIDAT1 = 0x00;

  // All chip selects go high when no transfer
  SPI->SPIDEF = 0xFF;

  // Disable interrupts
  SPI->SPIINT = 0x00;
  SPI->SPILVL = 0x00;
  
  return E_PASS;
}



/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 19-Aug-2008
      Initial release
-------------------------------------------------------------------------- */

