/* ---------------------------------------------------------------------------
  FILE        : debug.c 				                             	 	        
  PURPOSE     : Debug functions file
  PROJECT     : DM648 UBL
  AUTHOR      : Daniel Allred
  DESC        : Debug utility functions that are mapped to a specific I/O
                device for this particulat project.
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// I/O module
#include "uart.h"

// This module's header file
#include "debug.h"


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
\***********************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Debug print function (could use stdio or maybe UART)
Uint32 DEBUG_printString(String s)
{
  return UART_sendString((Uint8 *)s, FALSE);
}

Uint32 DEBUG_printHexInt(Uint32 i)
{
	UART_sendString((Uint8 *)"0x",FALSE);
  return UART_sendHexInt(i);
}

Uint32 DEBUG_readString(String s)
{
  return UART_recvString((Uint8 *)s);
}

Uint32 DEBUG_readChar(Char *c)
{
  Uint32 len = 1;
  return UART_recvStringN((Uint8 *) c,&len,FALSE);
}


/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/
/* ---------------------------------------------------------------------------
  HISTORY
    v1.00  -  DJA  -  07-Nov-2007
 	    Initial release
 ----------------------------------------------------------------------------- */



