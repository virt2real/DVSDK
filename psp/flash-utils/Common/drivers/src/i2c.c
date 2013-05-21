/* --------------------------------------------------------------------------
  FILE      : i2c.c
  PROJECT   : Catalog Boot-Loader and Flasher
  AUTHOR    : Daniel Allred
  DESC      : Generic I2C driver file for common I2C peripheral
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// Util functions
#include "util.h"

// This module's header file 
#include "i2c.h"


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
I2C_InfoObj gI2CInfo;
#endif


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Initialze NAND interface and find the details of the NAND used
I2C_InfoHandle I2C_open(Uint32 i2cPeripheralNum, I2C_Role role, I2C_Mode mode, I2C_ConfigHandle hConfig)
{
  I2C_InfoHandle hI2CInfo;
  DEVICE_I2CRegs *I2C;

  // Set NandInfo handle
#ifdef USE_IN_ROM
  hI2CInfo = (I2C_InfoHandle) &gI2CInfo;
#else
  hI2CInfo = (I2C_InfoHandle) UTIL_allocMem(sizeof(I2C_InfoObj));
#endif

  // Assign the correct register base
  if (i2cPeripheralNum >= I2C_PERIPHERAL_CNT)
    return NULL;

  hI2CInfo->peripheralNum = i2cPeripheralNum;
  hI2CInfo->regs = (void *) (((Uint32)I2C0) + (I2C_MEMORYMAP_SPACING *i2cPeripheralNum) );
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;

  // Put the I2C peripheral into reset
  I2C_assertReset(hI2CInfo);
  
	// Set Own Address
	I2C->ICOAR = hConfig->ownAddr;
	 
	// Set Default I2C High and Low Clock Hold
	I2C->ICPSC  = (hConfig->prescalar - 1) & 0xFF;
	I2C->ICCLKL = (hConfig->i2cclkl - 1) & 0xFF;
	I2C->ICCLKH = (hConfig->i2cclkh - 1) & 0xFF;
	
	// Set the device role
  hI2CInfo->role = role;
  
  // Set the device mode the 
  hI2CInfo->mode = mode;
  	                    
  // Take I2C Out of Reset
  I2C_releaseReset(hI2CInfo);

  // Clear BB and ARDY
  I2C->ICSTR |= (I2C_ICSTR_ARDY_MSK | I2C_ICSTR_BB_MSK);
  
  return hI2CInfo;
}

// Routine to reset the I2C device
void I2C_assertReset(I2C_InfoHandle hI2CInfo)
{
  DEVICE_I2CRegs *I2C;
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;

  // Send reset command to I2C
  I2C->ICMDR &= (~I2C_ICMDR_IRS);

  hI2CInfo->status = I2C_STATUS_RESET;
}

void I2C_releaseReset(I2C_InfoHandle hI2CInfo)
{
  DEVICE_I2CRegs *I2C;
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;

  // Release from reset
  I2C->ICMDR |= I2C_ICMDR_IRS;

  hI2CInfo->status = I2C_STATUS_READY;
}

void I2C_setStopCondition(I2C_InfoHandle hI2CInfo)
{
  DEVICE_I2CRegs *I2C;
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;

  if (hI2CInfo->role == I2C_ROLE_MASTER)
  {
    // Generate the Stop Condition
    I2C->ICMDR |= I2C_ICMDR_STP;

	  // Wait for Master mode cleared
	  while(I2C->ICMDR & I2C_ICMDR_MST);
  }

  // Put I2C in reset
  I2C->ICMDR &= ~I2C_ICMDR_IRS;

  // Set the status
  hI2CInfo->status = I2C_STATUS_RESET;
}

void I2C_setStartCondition(I2C_InfoHandle hI2CInfo, Uint32 i2cmdr)
{
  DEVICE_I2CRegs *I2C;
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;

  if (hI2CInfo->role == I2C_ROLE_MASTER)
  {
    i2cmdr |= I2C_ICMDR_MST;

    if (hI2CInfo->status != I2C_STATUS_BUSY)
    {
      // Wait till the Bus is free for transfer
	    while(I2C->ICSTR & I2C_ICSTR_BB_MSK);
    }

    I2C->ICMDR = (i2cmdr | I2C_ICMDR_STT | I2C_ICMDR_IRS);

    // Make sure the bus now says we are busy (since we set start cond.)
	  while(!(I2C->ICSTR & I2C_ICSTR_BB_MSK));

    // Set the status
    hI2CInfo->status = I2C_STATUS_BUSY;
  }
  else
  {
    I2C->ICMDR = (i2cmdr | I2C_ICMDR_IRS);
    hI2CInfo->status = I2C_STATUS_READY;
  }

}

// Generic routines to read a page from I2C
Uint32 I2C_readBytes(I2C_InfoHandle hI2CInfo, Uint32 byteCnt, Uint8 *dest)
{
  Uint8* currDestPtr;
  Uint32 currByteCnt,i2cstr,i2cmdr;
  DEVICE_I2CRegs *I2C;
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;

  currDestPtr = dest;
  currByteCnt = byteCnt;
  i2cmdr      = 0x0000;

  // Clear or set repeat mode
  if ((hI2CInfo->mode==I2C_MODE_REPEAT_MANUAL_STOP) || (hI2CInfo->mode==I2C_MODE_REPEAT_AUTO_STOP))
  {
    i2cmdr |= I2C_ICMDR_RM;
  }
  else
  {
    // Set the byte count to transfer
    I2C->ICCNT = currByteCnt;
  }

  // Set slave address
	I2C->ICSAR = hI2CInfo->slaveAddr;

  // Start Sending the bytes (only 
  I2C_setStartCondition(hI2CInfo,i2cmdr);

  while (currByteCnt)
  {
    i2cstr = I2C->ICSTR; 

    //Check if Receive Data Register is Ready
	  if (i2cstr & I2C_ICSTR_ICRRDY_MSK)
    {
      // Read data from Receive Data Register
      *currDestPtr++ = I2C->ICDRR;
      currByteCnt--;
    }
  }

  // Wait for register access to be ready
  while (!(I2C->ICSTR & I2C_ICSTR_ARDY_MSK));

  if ((hI2CInfo->mode == I2C_MODE_AUTO_STOP) || (hI2CInfo->mode == I2C_MODE_REPEAT_AUTO_STOP))
    I2C_setStopCondition(hI2CInfo);
 
	return E_PASS;
}


// Generic routine to write bytes to I2C
Uint32 I2C_writeBytes(I2C_InfoHandle hI2CInfo, Uint32 byteCnt, Uint8 *src)
{
  Uint8* currSrcPtr;
  Uint32 currByteCnt,i2cstr,i2cmdr;
  DEVICE_I2CRegs *I2C;
  I2C = (DEVICE_I2CRegs *) hI2CInfo->regs;
 
RESTART_WRITEBYTES:
  currByteCnt = byteCnt;
  currSrcPtr  = src;
  i2cmdr      = 0x0000;

  // Set as transmitter
  i2cmdr |= (I2C_ICMDR_TRX);

  // Clear or set repeat mode
  if ( (hI2CInfo->mode == I2C_MODE_REPEAT_MANUAL_STOP) || (hI2CInfo->mode == I2C_MODE_REPEAT_AUTO_STOP) )
  {
    i2cmdr |= I2C_ICMDR_RM;
  }
  else
  {
    I2C->ICCNT = currByteCnt;
  }

  // Set slave address
	I2C->ICSAR = hI2CInfo->slaveAddr;

  I2C_setStartCondition(hI2CInfo,i2cmdr);

  UTIL_waitLoop(100);

  // Transmit all bytes
  while (currByteCnt)
  {
    Int32 timeout;
    I2C->ICDXR = *currSrcPtr++;
    currByteCnt--;

    timeout = I2C_TIMEOUT;
    do
    {
      i2cstr = I2C->ICSTR;
      if ( timeout-- < 0 )
      {
        I2C_assertReset(hI2CInfo);
        return E_TIMEOUT;
      }
    } while ( (i2cstr & I2C_ICSTR_ICXRDY_MSK) == 0 ); // Wait for Tx Ready

    // If NACK condition, then we fail
    if (i2cstr & (I2C_ICSTR_NACK_MSK | I2C_ICSTR_ARDY_MSK | I2C_ICSTR_AL_MSK))
	  {
		  I2C_assertReset(hI2CInfo);
      I2C_releaseReset(hI2CInfo);
	    return E_FAIL;
    }
  }

  if ((hI2CInfo->mode == I2C_MODE_AUTO_STOP) || (hI2CInfo->mode == I2C_MODE_REPEAT_AUTO_STOP))
    I2C_setStopCondition(hI2CInfo);

  return E_PASS;
}


/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 25-Aug-2008
      Initial release
-------------------------------------------------------------------------- */

