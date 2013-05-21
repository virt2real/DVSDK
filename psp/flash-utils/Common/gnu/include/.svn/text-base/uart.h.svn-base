/* --------------------------------------------------------------------------
  FILE        : uart.h
  PROJECT     : TI Booting and Flashing Utilities
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
Uint32 UART_sendString(String seq, Bool includeNull);
Uint32 UART_sendHexInt(Uint32 value);
Uint32 UART_recvString(String seq);
Uint32 UART_recvStringN(String seq, Uint32* len, Bool stopAtNull);

Uint32 UART_checkSequence(String seq, Bool includeNull);
Uint32 UART_recvHexData(Uint32 numBytes, Uint32* data);



/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
extern far "c" }
#endif

#endif // End _UART_H_

