/* --------------------------------------------------------------------------
  FILE        : i2c.h
  PROJECT     : DaVinci User Boot-Loader and Flasher
  AUTHOR      : Texas Instruments Incorporated
  DESC        : Generic I2C driver header file
 ----------------------------------------------------------------------------- */

#ifndef _I2C_H_
#define _I2C_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

#define I2C_TIMEOUT       (0x10000u)

#define I2C_SLAVE_ADDR    (0x50u)
#define I2C_OWN_ADDR      (0x29u)


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

// I2C Module Roles
typedef enum _I2C_ROLE_
{
  I2C_ROLE_MASTER = 0x01,
  I2C_ROLE_SLAVE = 0x02
}
I2C_Role;

// I2C Module Modes of Operation
typedef enum _I2C_MODE_
{
  I2C_MODE_MANUAL_STOP          = 0x01,
  I2C_MODE_REPEAT_MANUAL_STOP   = 0x02,
  I2C_MODE_AUTO_STOP            = 0x04,
  I2C_MODE_REPEAT_AUTO_STOP     = 0x08
}
I2C_Mode;

typedef enum _I2C_STATUS_
{
  I2C_STATUS_RESET = 0x01,
  I2C_STATUS_READY = 0x02,
  I2C_STATUS_BUSY  = 0x03
}
I2C_Status;

typedef enum _I2C_ADDRESSING_MODE_
{
  I2C_ADDRESSING_7BIT  = 0x01,
  I2C_ADDRESSING_10BIT = 0x02
}
I2C_AddressingMode;

typedef struct _I2C_CONFIG_
{
  Uint32              ownAddr;
  Uint8               i2cclkl;
  Uint8               i2cclkh;
  Uint8               prescalar;
  I2C_AddressingMode  addrMode;
}
I2C_ConfigObj, *I2C_ConfigHandle;

// I2C driver structure
typedef struct _I2C_INFO_
{
  Uint32      peripheralNum;
  void        *regs;
  Uint32      slaveAddr;
  I2C_Role    role;
  I2C_Mode    mode;
  I2C_Status  status;
}
I2C_InfoObj, *I2C_InfoHandle;


/************************************************************
* Global Function Declarations                              *
************************************************************/

extern I2C_InfoHandle I2C_open(Uint32 i2cPeripheralNum, I2C_Role role, I2C_Mode mode, I2C_ConfigHandle hConfig);
extern void I2C_assertReset(I2C_InfoHandle hI2CInfo);
extern void I2C_releaseReset(I2C_InfoHandle hI2CInfo);
void I2C_setStopCondition(I2C_InfoHandle hI2CInfo);
void I2C_setStartCondition(I2C_InfoHandle hI2CInfo, Uint32 i2cmdr);
extern Uint32 I2C_readBytes(I2C_InfoHandle hI2CInfo, Uint32 byteCnt, Uint8 *dest);
extern Uint32 I2C_writeBytes(I2C_InfoHandle hI2CInfo, Uint32 byteCnt, Uint8 *src);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // _I2C_H_
