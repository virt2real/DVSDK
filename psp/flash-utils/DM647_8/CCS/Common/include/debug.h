/* --------------------------------------------------------------------------
  FILE        : debug.h
  PURPOSE     : Debug utility header file
  PROJECT     : Dm648 CCS NORWriter flashing utility
  AUTHOR      : Daniel Allred
  DESC	      : Header for the DM648 debug routines  
 ----------------------------------------------------------------------------- */ 

#ifndef _DEBUG_H_
#define _DEBUG_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

/***********************************************************
* Global Function Declarations                             *
***********************************************************/

void DEBUG_printString(String s);
void DEBUG_printHexInt(Uint32 i);
void DEBUG_readString(String s);
void DEBUG_readChar(Int8 *c);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_DEBUG_H_

/* --------------------------------------------------------------------------
    HISTORY
		v1.00  -  DJA  -  07-Nov-2007
 	        Initial release 
 ----------------------------------------------------------------------------- */
