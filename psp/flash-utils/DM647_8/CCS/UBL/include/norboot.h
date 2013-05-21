/* --------------------------------------------------------------------------
  FILE        : norboot.h
  PURPOSE     : UBL NOR boot header file
  PROJECT     : DM648 User Boot Loader
  AUTHOR      : Daniel Allred
  DESC        : Header file for the NOR Boot part of the UBL - used when a UBL is 
                present in the NOR flashon the DM648 EVM from Lyrtech.
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
	Uint32		ldAddress;
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

#endif //_NORWRITER_H_


/* -------------------------------------------------------------------------- 
    HISTORY
 		v1.00  -  DJA  -  07-Nov-2007
			Initial Release 	   
 ----------------------------------------------------------------------------- */
