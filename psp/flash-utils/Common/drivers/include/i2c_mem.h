/* --------------------------------------------------------------------------
  FILE        : i2c_mem.h
  PROJECT     : DaVinci User Boot-Loader and Flasher
  AUTHOR      : Texas Instruments Incorporated
  DESC        : Generic I2C memory device driver header file
 ----------------------------------------------------------------------------- */

#ifndef _I2C_MEM_H_
#define _I2C_MEM_H_

#include "tistdtypes.h"

#include "i2c.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

// I2C_MEM Config Structure
typedef struct _I2C_MEM_CONFIG_
{
  Uint32 i2cMemAddr;
  Uint32 pageSize;
  Uint32 addrWidth;
  Uint32 memorySize;
}
I2C_MemConfigObj, *I2C_MemConfigHandle;

// I2C_MEM Driver Structure
typedef struct _I2C_MEM_INFO_
{
  I2C_InfoHandle hI2CInfo;
  I2C_MemConfigHandle hI2CMemCfg;
}
I2C_MemInfoObj, *I2C_MemInfoHandle;



/************************************************************
* Global Function Declarations                              *
************************************************************/

extern I2C_MemInfoHandle I2C_MEM_open(Uint32 i2cPeripheralNum, I2C_ConfigHandle hI2cCfg, I2C_MemConfigHandle hI2CMemCfg);
extern Uint32 I2C_MEM_readBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *dest);
extern Uint32 I2C_MEM_writeBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src);
extern Uint32 I2C_MEM_verifyBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src, Uint8* dest);
extern Uint32 I2C_MEM_globalErase(I2C_MemInfoHandle hI2CMemInfo);
extern Uint32 I2C_MEM_eraseBytes(I2C_MemInfoHandle hI2CMemInfo, Uint32 startAddr, Uint32 byteCnt);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // _I2C_H_
