/* --------------------------------------------------------------------------
  FILE        : ubl.h
  PURPOSE     : UBL main header file
  PROJECT     : DM648 User Boot Loader
  AUTHOR      : Daniel Allred
  DESC        : Header file for the User Boot Loader for booting AIS application
                images on the DM648 EVM from Lyrtech.  
 ----------------------------------------------------------------------------- */

#ifndef _UBL_H_
#define _UBL_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

//UBL version and type
#define UBL_VERSION_STRING  ("1.01")
#define UBL_FLASH_TYPE      ("NOR")


/************************************************************
* Global Typedef declarations                               *
************************************************************/


/************************************************************
* Global Function Declarations                              *
************************************************************/

extern void main(void);


/************************************************************
* End file                                                  *
************************************************************/

#ifdef __cplusplus
}
#endif

#endif //_UBL_H_

/* -------------------------------------------------------------------------- 
  HISTORY
 	  v1.00  -  DJA  -  15-Nov-2007
			Initial Release
 	  v1.01  -  DJA  -  02-Mar-2008
			Change to uart timeout handling and device init
 ----------------------------------------------------------------------------- */

