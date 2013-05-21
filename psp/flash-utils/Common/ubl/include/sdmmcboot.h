/* --------------------------------------------------------------------------
  FILE        : sdmmcboot.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : This file defines all needed structures and macros for 
                booting the UBL in SDMMC mode.
 ----------------------------------------------------------------------------- */

#ifndef _NANDBOOT_H_
#define _NANDBOOT_H_

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

typedef struct _SDMMCBOOT_HEADER_
{
  Uint32 magicNum;    // Expected magic number
  Uint32 entryPoint;  // Entry point of the user application
  Uint32 numPage;     // Number of pages where boot loader is stored
  Uint32 block;       // Starting block number where User boot loader is stored
  Uint32 page;        // Starting page number where boot-loader is stored
  Uint32 ldAddress;   // Starting RAM address where image is to copied - XIP Mode
}
SDMMCBOOT_HeaderObj,*SDMMCBOOT_HeaderHandle;


/******************************************************
* Global Function Declarations                        *
******************************************************/

extern Uint32 SDMMCBOOT_copy(void);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_NANDBOOT_H_




