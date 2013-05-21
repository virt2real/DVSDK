/* --------------------------------------------------------------------------
  FILE        : i2c_ecp.c 				                             	 	  
  PURPOSE     : I2C routines to write and read EVM's ECP (MSP430)
  PROJECT     : DM648 UBL for application loading
  AUTHOR      : Daniel Allred
  DESC        : These routines are used to control the EVM components via
                the ECP
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "i2c_ecp.h"

// DEBUG module
#include "debug.h"

// Common UTIL module
#include "util.h"

// DEVICE module (chip-specific init)
#include "device.h"

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


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 I2C_ECP_write( Uint8 offset, Uint8 data)
{
  Uint32 retVal = E_PASS;
  Uint32 status, nack, al;
  Uint32 timeout,tryCnt = 0;

TX_TO_ECP_START:
  tryCnt++;
  I2C_ECP_reset();

  // Set number of bytes to write
  I2C0->ICCNT = 2;

  // Wait for tx rdy , Nack or timeout
  for (timeout = 10000000; timeout; timeout--)
  {
    status = I2C0->ICSTR;
    nack = (status & I2C_ICSTR_NACK_MSK);
    if ( ( (status & I2C_ICSTR_ICXRDY_MSK)!=0 ) || (nack!=0) )
    {
      break;
    }
  }

  if ( timeout == 0 )
  {
    DEBUG_printString("I2C_ECP_write(): Timeout waiting to initiate write.\r\n");
    retVal = E_TIMEOUT;
  }
  if (nack)
  {
    DEBUG_printString("I2C_ECP_write(): NACK waiting to initiate write.\r\n");
    retVal = E_FAIL;
  }

  if (retVal == E_PASS)
  {
    // Put offset in I2C tx buffer
    I2C0->ICDXR = (offset & 0xff);

    // Starts I2C transmission & Allow to Stop
    I2C0->ICMDR = I2C_ICMDR_FRE |
                  I2C_ICMDR_STT |
                  I2C_ICMDR_STP |
                  I2C_ICMDR_MST |
                  I2C_ICMDR_TRX |
                  I2C_ICMDR_IRS;
    
    // Wait for tx rdy , nack, arbitration loss, or timeout (BB should still be high)
    for (timeout = 10000000; timeout; timeout--)
    {
      status = I2C0->ICSTR;
      nack = (status & I2C_ICSTR_NACK_MSK);
      al = (status & I2C_ICSTR_AL_MSK);
      if ( ( (status & I2C_ICSTR_ICXRDY_MSK)!=0 ) || (nack!=0) || (al != 0) )
      {
        break;
      }
    }

    if (al)
    {
      // Arbitration should never be lost, since DM648 is only master
      // on this bus
      DEBUG_printString("I2C_ECP_write(): Lost Arbitration.\r\n");
      if (tryCnt < I2C_ECP_RETRY_CNT_MAX)
      {
        DEBUG_printString("I2C_ECP_write(): Restarting transmission, attempt #");
        DEBUG_printHexInt(tryCnt);
        DEBUG_printString(".\r\n");
        goto TX_TO_ECP_START;
      }
      else
      {
        retVal = E_FAIL;
      }
    }

    if ( timeout == 0 )
    {
      DEBUG_printString("I2C_ECP_write(): Timeout upon offset write.\r\n");
      retVal = E_TIMEOUT;
    }
    if (nack)
    {
      DEBUG_printString("I2C_ECP_write(): NACK upon offset write.\r\n");            
      retVal = E_FAIL;
    }
    if (retVal == E_PASS)
    {
      // Put data byte in I2C tx buffer
      I2C0->ICDXR = (data & 0xff);

      // Wait for (BB=0 and ICXRDY=1), NACK, or timeout
      for (timeout = 10000000; timeout; timeout--)
      {
        status = I2C0->ICSTR;
        nack = (status & I2C_ICSTR_NACK_MSK);
        if ( ( ((status & I2C_ICSTR_BB_MSK)==0 ) && ((status & I2C_ICSTR_ICXRDY_MSK)!=0 ) ) || (nack!=0) )
        {
          break;
        }
      }

      status = I2C0->ICSTR;
      if (status & I2C_ICSTR_SCD_MSK == 0)
      {
        DEBUG_printString("I2C_ECP_write(): Stop condition was not detected.\r\n");
        retVal = E_FAIL;
      }

      if ( timeout == 0 )
      {
        DEBUG_printString("I2C_ECP_write(): Timeout upon data write.\r\n");
        retVal = E_TIMEOUT;
      }
      if (nack)
      {
        DEBUG_printString("I2C_ECP_write(): NACK upon data write.\r\n");
        retVal = E_FAIL;
      }
    }
  }

  if (retVal != E_PASS)
  {
    DEBUG_printString("I2C_ECP_write(): Status = ");
    DEBUG_printHexInt(status);
    DEBUG_printString("\r\n");
  }
  return retVal;
}

Uint32 I2C_ECP_read( Uint8 offset, Uint8 *data )
{
  Uint32 retVal = E_PASS;
  Uint32 status, nack, al, bb;
  Uint32 timeout, tryCnt = 0;

RX_FROM_ECP_START:
  tryCnt++;
  I2C_ECP_reset();
   
  // Wait for tx rdy , Nack or timeout
  for (timeout = 10000000; timeout; timeout--)
  {
    status = I2C0->ICSTR;
    nack = (status & I2C_ICSTR_NACK_MSK);
    if ( ( (status & I2C_ICSTR_ICXRDY_MSK)!=0 ) || (nack!=0) )
    {
      break;
    }
  }

  if (timeout == 0)
  {
    DEBUG_printString("I2C_ECP_read(): Timeout waiting to initiate write of offset.\r\n");
    retVal = E_TIMEOUT;
  }
  if (nack)
  {
    DEBUG_printString("I2C_ECP_read(): NACK waiting to initiate write of offset.\r\n");
    retVal = E_FAIL;
  }

  // If no error, write the offset and then read a byte
  if (retVal == E_PASS)
  {
    // Put offset in transmission register
    I2C0->ICDXR = (offset & 0xff);

    // Starts I2C transmission (no stop)
    I2C0->ICMDR = I2C_ICMDR_FRE |
                  I2C_ICMDR_STT |
                  I2C_ICMDR_RM  |
                  I2C_ICMDR_MST |
                  I2C_ICMDR_TRX |
                  I2C_ICMDR_IRS;

    // Wait for tx rdy, nack, arbitration loss, or timeout (BB should still be high)
    for (timeout = 10000000; timeout; timeout--)
    {
      status = I2C0->ICSTR;
      nack = (status & I2C_ICSTR_NACK_MSK);
      al = (status & I2C_ICSTR_AL_MSK);
      if ( ( (status & I2C_ICSTR_ICXRDY_MSK)!=0 ) || (nack!=0) || (al != 0) )
      {
        break;
      }
    }

    if (al)
    {
      // Arbitration should never be lost, since DM648 is only master
      // on this bus
      DEBUG_printString("I2C_ECP_read(): Lost Arbitration.\r\n");
      if (tryCnt < I2C_ECP_RETRY_CNT_MAX)
      {
        DEBUG_printString("I2C_ECP_read(): Restarting transmission, attempt #");
        DEBUG_printHexInt(tryCnt);
        DEBUG_printString(".\r\n");
        goto RX_FROM_ECP_START;
      }
      else
      {
        retVal = E_FAIL;
      }
    }

    if ( timeout == 0 )
    {
      DEBUG_printString("I2C_ECP_read(): Timeout upon offset write.\r\n");
      retVal = E_TIMEOUT;
    }
    if (nack)
    {
      DEBUG_printString("I2C_ECP_read(): NACK upon offset write.\r\n");            
      retVal = E_FAIL;
    }
    if (retVal == E_PASS)
    {
      // Everything is good so far, now do read operation

      I2C_ECP_reset();

      // Set number of bytes to read
      I2C0->ICCNT = 1;

      I2C0->ICMDR = (I2C_ICMDR_FRE |
                    I2C_ICMDR_MST) &
                    (~I2C_ICMDR_IRS);

      // Starts I2C receiving & Allow to Stop
      I2C0->ICMDR = I2C_ICMDR_FRE |
                    I2C_ICMDR_STT |
                    I2C_ICMDR_MST |
                    I2C_ICMDR_STP |
                    I2C_ICMDR_IRS;

      // Wait for ICRRDY!=0 , Nack or timeout
      for (timeout = 10000000; timeout; timeout--)
      {
        status = I2C0->ICSTR;
        nack = (status & I2C_ICSTR_NACK_MSK);
        if ( ((status & I2C_ICSTR_ICRRDY_MSK)!=0) || (nack!=0) )
          break;
      }

      if ( timeout == 0 )
      {
        DEBUG_printString("I2C_ECP_read(): Timeout upon data read.\r\n");
        retVal = E_TIMEOUT;
      }
      if (nack)
      {
        DEBUG_printString("I2C_ECP_read(): NACK upon data read.\r\n");
        retVal = E_FAIL;
      }
      if (retVal == E_PASS)
      {
        // Read the data byte
        *data = I2C0->ICDRR & 0xff;

        // If no error, waits I2C module to finish receiving
        // Wait for BB=0 or timeout
        for (timeout = 10000000; timeout; timeout--)
        {
          status = I2C0->ICSTR;
          bb = (status & I2C_ICSTR_BB_MSK);
          if (bb == 0)
            break;
        }
        if (timeout == 0)
        {
          DEBUG_printString("I2C_ECP_read(): Timeout waiting for read cycle completion.\r\n");
          retVal = E_TIMEOUT;
        }
      }
    }
    else
    {
      // Some error was encountered so just send stop

      I2C0->ICMDR = I2C_ICMDR_FRE |
                    I2C_ICMDR_STP |
                    I2C_ICMDR_MST |
                    I2C_ICMDR_TRX |
                    I2C_ICMDR_RM  |
                    I2C_ICMDR_IRS;

      // Set timeout before polling tx rdy...
      timeout = 10000000;

      // Wait for BB=0 , ICXRDY=1, Nack or timeout
      for (timeout = 10000000; timeout; timeout--)
      {
        status=I2C0->ICSTR;
        nack=(status & I2C_ICSTR_NACK_MSK);
        bb = (status & I2C_ICSTR_BB_MSK);
        if ( (bb==0) || (nack!=0) )
          break;
      }

      // Check if we got timeout or Nack (indicates problem)
      if ( timeout == 0 )
      {
        retVal = E_TIMEOUT;
      }
      if (nack)
      {
        retVal = E_FAIL;
      }
    }
  }
  if (retVal != E_PASS)
  {
    DEBUG_printString("I2C_ECP_read(): Status = ");
    DEBUG_printHexInt(status);
    DEBUG_printString("\r\n");
  }
  return retVal;
}

void I2C_ECP_reset()
{
  // Free running, master, tx, 7 bits addr, non repeat, reset, 8 bits data
  I2C0->ICMDR =   ( I2C_ICMDR_MST  |
                    I2C_ICMDR_FRE) &
                    ~(I2C_ICMDR_IRS);
  UTIL_waitLoop(1000);

  // set backward compatibility mode
  I2C0->ICEMDR = I2C_ICEMDR_EXTMODE;

  // Set our device address
  I2C0->ICOAR = DEVICE_I2C_OWN_ADDRESS & 0xFF;

  // Set slave adress
  I2C0->ICSAR = I2C_ECP_ADDRESS;

  I2C0->ICIMR = 0;

  // Read and clear interrupt status register
  I2C0->ICSTR |= 0x0000703F;

  // Read ICIVR until clear
  while ((I2C0->ICIVR & 0x7) != 0x0);

  I2C0->ICMDR =   ( I2C_ICMDR_MST  |
                    I2C_ICMDR_FRE  |
                    I2C_ICMDR_IRS);
  UTIL_waitLoop(1000);
}


/***********************************************************
* Local Function Definitions                               *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  07-Nov-2007
 	        Initial release 
 ----------------------------------------------------------------------------- */
