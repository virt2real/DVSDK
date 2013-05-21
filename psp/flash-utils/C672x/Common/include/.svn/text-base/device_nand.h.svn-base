/* --------------------------------------------------------------------------
  FILE        : device_nand.h
  PURPOSE     : Device-specific NAND  -  DA8xx version
  PROJECT     : DaVinci flashing utilities
  AUTHOR      : Daniel Allred
  DESC        : Provides device differentiation for the project files. This
                file MUST be modified to match the device specifics.
----------------------------------------------------------------------------- */

#ifndef _DEVICE_NAND_H_
#define _DEVICE_NAND_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

#ifdef PADK_FPGA_IN_USE
  // Testing on PADK with FPGA
  #define DEVICE_NAND_DATA_OFFSET        (0x00001000u)
  #define DEVICE_NAND_ALE_OFFSET         (0x00003000u)
  #define DEVICE_NAND_CLE_OFFSET         (0x00005000u)
#else
  #define DEVICE_NAND_DATA_OFFSET        (0x00000000u)
  #define DEVICE_NAND_ALE_OFFSET         (0x00001000u)
  #define DEVICE_NAND_CLE_OFFSET         (0x00002000u)
#endif

#define DEVICE_NAND_TIMEOUT            (10240)

#define DEVICE_NAND_MAX_BYTES_PER_OP       (512)   // Max Bytes per operation (EMIF IP constrained)
#define DEVICE_NAND_MAX_SPAREBYTES_PER_OP  (16)    // Max Spare Bytes per operation
#define DEVICE_NAND_MIN_SPAREBYTES_PER_OP  (4)    // Min Spare Bytes per operation (ECC operation constrained)

// Defines which NAND blocks the RBL will search in for a UBL image
#define DEVICE_NAND_RBL_SEARCH_START_BLOCK     (1)
#define DEVICE_NAND_RBL_SEARCH_END_BLOCK       (24)

#define DEVICE_NAND_ECC_START_OFFSET_LARGEPAGE (8)
#define DEVICE_NAND_ECC_START_OFFSET_SMALLPAGE (0)

/******************************************************
* Global Typedef declarations                         *
******************************************************/


/***********************************************************
* Global Function Declarations                             *
***********************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif // End _DEVICE_NAND_H_

/* --------------------------------------------------------------------------
    HISTORY
       v1.00  -  DJA  -  07-Nov-2007
         Initial Release
 ----------------------------------------------------------------------------- */
