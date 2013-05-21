/* --------------------------------------------------------------------------
  FILE        : uartboot.c                                                   
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Implementation of the UART boot mode for the UBL
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "uartboot.h"

// UART driver
#include "uart.h"

// Misc. utility function include
#include "util.h"

// Project specific debug functionality
#include "debug.h"

// Main UBL module
#include "ubl.h"

// Device module
#include "device.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern VUint32 gMagicFlag,gBootCmd;
extern Uint32 gEntryPoint;

extern __FAR__ Uint32 DDRStart;
extern __FAR__ Uint32 EMIFStart;
extern __FAR__ Uint32 DDRSize;


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 LOCAL_sendSequence(String s);
static Uint32 LOCAL_recvCommand(Uint32* bootCmd);
static Uint32 LOCAL_recvHeaderAndData(UARTBOOT_HeaderHandle ackHeader);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

Uint32 UARTBOOT_copy(void)
{
  UARTBOOT_HeaderObj  ackHeader;
  Uint32              bootCmd;

UART_tryAgain:
  DEBUG_printString("Starting UART Boot...\r\n");

  // UBL Sends 'BOOTUBL/0'
  if (LOCAL_sendSequence("BOOTUBL") != E_PASS)
    goto UART_tryAgain;

  // Receive the BOOT command
  if(LOCAL_recvCommand(&bootCmd) != E_PASS)
    goto UART_tryAgain;

  switch(bootCmd)
  {
    // Only used for doing simple boot of UART
    case UBL_MAGIC_SAFE:
    {
      if (LOCAL_sendSequence("SENDAPP") != E_PASS)
        goto UART_tryAgain;
      if (LOCAL_recvHeaderAndData(&ackHeader) != E_PASS)
        goto UART_tryAgain;
      gEntryPoint = ackHeader.startAddr;
      break;
    }
    default:
    {
      DEBUG_printString("Boot command not supported!");
      return E_FAIL;
    }
  }

  return E_PASS;
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 LOCAL_sendSequence(String s)
{
  return UART_sendString(s, TRUE);
}

static Uint32 LOCAL_recvCommand(Uint32* bootCmd)
{
  if(UART_checkSequence("    CMD", TRUE) != E_PASS)
  {
    return E_FAIL;
  }

  if(UART_recvHexData(4,bootCmd) != E_PASS)
  {
    return E_FAIL;
  }

  return E_PASS;
}

static Uint32 LOCAL_recvHeaderAndData(UARTBOOT_HeaderHandle ackHeader)
{
  Uint32 error = E_FAIL, recvLen;

  // Recv ACK command
  error = UART_checkSequence("    ACK", TRUE);
  if(error != E_PASS)
  {
    return E_FAIL;
  }

  // Get the ACK header elements
  error =  UART_recvHexData( 4, (Uint32 *) &(ackHeader->magicNum)     );
  error |= UART_recvHexData( 4, (Uint32 *) &(ackHeader->startAddr) );
  error |= UART_recvHexData( 4, (Uint32 *) &(ackHeader->byteCnt)  );
  error |= UART_checkSequence("0000", FALSE);
  if(error != E_PASS)
  {
    return E_FAIL;
  }

  // Verify that the data size is appropriate
  if((ackHeader->byteCnt == 0) || (ackHeader->byteCnt > APP_IMAGE_SIZE))
  {
    LOCAL_sendSequence(" BADCNT");  // trailing /0 will come along
      return E_FAIL;
  }

  // Verify application start address is in RAM (lower 16bit of appStartAddr also used 
  // to hold UBL entry point if this header describes a UBL)
  if( (ackHeader->startAddr < DEVICE_DDR2_START_ADDR) || (ackHeader->startAddr > DEVICE_DDR2_END_ADDR) )
  {
    LOCAL_sendSequence("BADADDR");  // trailing /0 will come along
    return E_FAIL;
  }

  // Send BEGIN command
  if (LOCAL_sendSequence("  BEGIN") != E_PASS)
    return E_FAIL;

  // Receive the data over UART
  recvLen = ackHeader->byteCnt;
  error = UART_recvStringN((String)(ackHeader->loadAddr), &recvLen, FALSE );
  if ( (error != E_PASS) || (recvLen != ackHeader->byteCnt) )
  {
    DEBUG_printString("\r\nUART Receive Error\r\n");
    return E_FAIL;
  }

  // Return DONE when all data arrives
  if ( LOCAL_sendSequence("   DONE") != E_PASS )
    return E_FAIL;

  return E_PASS;
}

/************************************************************
* End file                                                  *
************************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.0 completion                                  
            Daniel Allred  -  1-Nov-2007
 ----------------------------------------------------------------------------- */

