/* --------------------------------------------------------------------------
  FILE        : norboot.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Header file for the NOR Boot part of the UBL - used when a UBL is 
                present in the NOR flash
 ----------------------------------------------------------------------------- */

#ifndef _NORBOOT_H_
#define _NORBOOT_H_

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

typedef struct _NORBOOT_HEADER_
{
	Uint32		magicNum;
	Uint32		entryPoint;	
	Uint32		appSize;
	Uint32		ldAddress;	/* Starting RAM address where image is to copied - XIP Mode */
}
NORBOOT_HeaderObj,*NORBOOT_HeaderHandle;


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

Uint32 NORBOOT_copy(void);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_NORBOOT_H_



