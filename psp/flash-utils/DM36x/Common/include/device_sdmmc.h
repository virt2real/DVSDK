/* --------------------------------------------------------------------------
  FILE        : device_sdmmc.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Gaurav Agarwal
  DESC        : Provides device differentiation for the project files. This
                file MUST be modified to match the device specifics.
----------------------------------------------------------------------------- */

#ifndef _DEVICE_SDMMC_H_
#define _DEVICE_SDMMC_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#define DEVICE_SDMMC_DATA_OFFSET        (0x00000000u)

#define DEVICE_SDMMC_TIMEOUT            (10240)

#define DEVICE_SDMMC_MAX_BYTES_PER_OP       (512)   // Max Bytes per operation 

// Defines which SDMMC blocks the RBL will search in for a UBL image
#define DEVICE_SDMMC_RBL_SEARCH_START_BLOCK     (1)
#define DEVICE_SDMMC_RBL_SEARCH_END_BLOCK       (24)

// Defines which SDMMC blocks are valid for writing the APP data
#define DEVICE_SDMMC_UBL_SEARCH_START_BLOCK     (25)
#define DEVICE_SDMMC_UBL_SEARCH_END_BLOCK       (50)

// Used by UBL when doing UART boot, UBL Nor Boot, NAND boot or MMC_SD boot
#define UBL_MAGIC_BIN_IMG           (0xA1ACED66)		/* Execute in place supported*/

// Application image magic numbe
#define UBL_MAGIC_BINARY_BOOT       (0x55424CBBu)

/***********************************************************
* Global Typedef declarations                              *
***********************************************************/
typedef struct
{
  Uint32 magicNum;    // Expected magic number
  Uint32 entryPoint;  // Entry point of the user boot loader (should be in 0x2000-0x3FFF region 
  Uint32 numBlock;	  // Number of blocks where User boot loader is stored 
  Uint32 startBlock;  // starting block number where User boot loader is stored 
  Uint32 ldAddress;   // Starting RAM address where image is to copied - XIP Mode
}
SDMMC_Boot;



/***********************************************************
* Global Function Declarations                             *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_SDMMC_H_

