/* --------------------------------------------------------------------------
  FILE        : uartboot.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : UART boot code for UBL
 ----------------------------------------------------------------------------- */

#ifndef _UARTBOOT_H_
#define _UARTBOOT_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/


/************************************************************
* Global Typedef declarations                               *
************************************************************/

typedef struct _UARTBOOT_HEADER_
{
  Uint32      magicNum;
  Uint32      startAddr;
  Uint32      loadAddr;
  Uint32      byteCnt;
  Uint32      crcVal;
}
UARTBOOT_HeaderObj,*UARTBOOT_HeaderHandle;


/************************************************************
* Global Function Declarations                              *
************************************************************/

Uint32 UARTBOOT_copy(void);

#endif // End _UARTBOOT_H_

