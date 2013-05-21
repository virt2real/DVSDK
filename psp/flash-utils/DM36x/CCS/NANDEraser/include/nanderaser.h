/* --------------------------------------------------------------------------
  FILE        : nandwriter.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  MODIFIED	  : Sandeep Paulraj; to add DM36x support
  DESC        : Header file for the NANDWriter application for flashing the 
                DM36x EVM from Spectrum Digital.
 ----------------------------------------------------------------------------- */

#ifndef _NANDWRITER_H_
#define _NANDWRITER_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/**************************************************
* Global Macro Declarations                       *
**************************************************/

//UBL version number
#define UBL_VERSION_STRING "1.00"
#ifdef UBL_NAND
#define UBL_FLASH_TYPE "NAND"
#endif

// Define MagicNumber constants
#define MAGIC_NUMBER_VALID          (0xA1ACED00)

// Used by RBL when doing NAND boot
#define UBL_MAGIC_SAFE              (0xA1ACED00)		/* Safe boot mode */
#define UBL_MAGIC_DMA               (0xA1ACED11)		/* DMA boot mode */
#define UBL_MAGIC_IC                (0xA1ACED22)		/* I Cache boot mode */
#define UBL_MAGIC_FAST              (0xA1ACED33)		/* Fast EMIF boot mode */
#define UBL_MAGIC_DMA_IC            (0xA1ACED44)		/* DMA + ICache boot mode */
#define UBL_MAGIC_DMA_IC_FAST       (0xA1ACED55)		/* DMA + ICache + Fast EMIF boot mode */

// Used by UBL when doing UART boot, UBL Nor Boot, or NAND boot
#define UBL_MAGIC_BIN_IMG           (0xA1ACED66)		/* Execute in place supported*/

// Define max UBL image size
#define UBL_IMAGE_SIZE              (0x00003800u)

// Define max app image size
#define APP_IMAGE_SIZE              (0x02000000u)


/************************************************
* Global Typedef declarations                   *
************************************************/

typedef struct
{
  Uint32 magicNum;    // Expected magic number
  Uint32 entryPoint;  // Entry point of the user application
  Uint32 numPage;     // Number of pages where boot loader is stored
  Uint32 block;       // Starting block number where User boot loader is stored
  Uint32 page;        // Starting page number where boot-loader is stored
  Uint32 ldAddress;   // Starting RAM address where image is to copied - XIP Mode
}
NANDWRITER_Boot;


/******************************************************
* Global Function Declarations                        *
******************************************************/

void main(void);


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_NANDWRITER_H_

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 02-Nov-2007
      Initial release
-------------------------------------------------------------------------- */




