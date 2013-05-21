/* --------------------------------------------------------------------------
  FILE        : uart.h
  PURPOSE     : UART header file
  PROJECT     : DaVinci User Boot-Loader and Flasher
  AUTHOR      : Daniel Allred
  DESC        : UART driver header file
 ----------------------------------------------------------------------------- */

#ifndef _UART_H_
#define _UART_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

#define MAXSTRLEN 256


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/


/************************************************************
* Global Function Declarations                              *
************************************************************/

// Simple send/recv functions
Uint32 UART_sendString(Uint8* seq, Bool includeNull);
Uint32 UART_sendHexInt(Uint32 value);
Uint32 UART_recvString(Uint8* seq);
Uint32 UART_recvStringN(Uint8* seq, Uint32* len, Bool stopAtNull);

Uint32 UART_checkSequence(Uint8* seq, Bool includeNull);
Uint32 UART_recvHexData(Uint32 numBytes, Uint32* data);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
extern far "c" }
#endif

#endif // End _UART_H_

/* --------------------------------------------------------------------------
  HISTORY
 	  v1.00  -  DJA  -  07-Nov-2007
      Initial release
 ----------------------------------------------------------------------------- */
