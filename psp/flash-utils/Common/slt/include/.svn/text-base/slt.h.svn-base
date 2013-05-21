/* --------------------------------------------------------------------------
  FILE        : slt.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : User boot loader header file for main components and intial
                entry point functions
 ----------------------------------------------------------------------------- */

#ifndef _SLT_H_
#define _SLT_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

// UBL version number
#define SLT_VERSION_STRING  ("1.50")

// Define MagicNumber constants
#define MAGIC_NUMBER_VALID          (0xA1ACED00)

#define SLT_MAGIC_LOADIMAGE         (0xA1ACEDEE)		// Download via image UART

// Define max UBL image size
#define UBL_IMAGE_SIZE              (((Uint32)&DRAMSize) - 0x800)

// Define max app image size
#define APP_IMAGE_SIZE              (((Uint32)&DDRSize) >> 3)

/***********************************************************
* Global Typedef declarations                              *
***********************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/

extern void main( void );


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_SLT_H_

