/* --------------------------------------------------------------------------
  FILE        : sft.h
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Serial Flasher Target header file for main function
 ----------------------------------------------------------------------------- */

#ifndef _SFT_H_
#define _SFT_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/***********************************************************
* Global Macro Declarations                                *
***********************************************************/

// UBL version number
#define SFT_VERSION_STRING  ("1.50")

// Define MagicNumber constants
#ifdef DM35X_REVC
#define MAGIC_NUMBER_VALID          (0xA1BCED00)
#else
#define MAGIC_NUMBER_VALID          (0xA1ACED00)
#endif

// Used by UBL when doing UART boot
#define UBL_UART_BOOT               (0xA1ACED00)		/* Safe boot mode */
#define UBL_NOR_BURN                (0xA1ACED11)		/* Download via UART & Burn NOR with UBL readable header and BIN data*/
#define UBL_NOR_ERASE               (0xA1ACED22)		/* Download via UART & Global erase the NOR Flash*/
#define UBL_NAND_BURN               (0xA1ACED33)		/* Download via UART & Burn NAND - Image is binary */
#define UBL_NAND_ERASE              (0xA1ACED44)		/* Download via UART & Global erase the NAND Flash*/

// Used by RBL when doing NAND boot
#define UBL_MAGIC_SAFE              (0xA1ACED00)		/* Safe boot mode */
#define UBL_MAGIC_DMA               (0xA1ACED11)		/* DMA boot mode */
#define UBL_MAGIC_IC                (0xA1ACED22)		/* I Cache boot mode */
#define UBL_MAGIC_FAST              (0xA1ACED33)		/* Fast EMIF boot mode */
#define UBL_MAGIC_DMA_IC            (0xA1ACED44)		/* DMA + ICache boot mode */
#define UBL_MAGIC_DMA_IC_FAST       (0xA1ACED55)		/* DMA + ICache + Fast EMIF boot mode */

// Used by DM35x RBL when doing NAND boot
#define UBL_DM35X_MAGIC_SAFE              (0xA1BCED00)		/* Safe boot mode */
#define UBL_DM35X_MAGIC_DMA               (0xA1BCED11)		/* DMA boot mode */
#define UBL_DM35X_MAGIC_IC                (0xA1BCED22)		/* I Cache boot mode */
#define UBL_DM35X_MAGIC_FAST              (0xA1BCED33)		/* Fast EMIF boot mode */
#define UBL_DM35X_MAGIC_DMA_IC            (0xA1BCED44)		/* DMA + ICache boot mode */
#define UBL_DM35X_MAGIC_DMA_IC_FAST       (0xA1BCED55)		/* DMA + ICache + Fast EMIF boot mode */

// Used by UBL when doing UART boot, UBL Nor Boot, or NAND boot
#define UBL_MAGIC_BIN_IMG           (0xA1ACED66)		/* Execute in place supported*/
#define UBL_DM35X_MAGIC_BIN_IMG     (0xA1BCED66)		/* Execute in place supported*/

// Used by UBL when doing UART boot
#define UBL_MAGIC_BIN_IMG           (0xA1ACED66)		/* Execute in place supported*/
#define UBL_MAGIC_NOR_FLASH_NO_UBL  (0xA1ACED77)		/* Download via UART & Burn NOR with u-boot only - legacy option */
#define UBL_MAGIC_NOR_FLASH         (0xA1ACED99)		/* Download via UART & Burn NOR with UBL and U-boot */
#define UBL_MAGIC_NOR_ERASE         (0xA1ACEDAA)		/* Download via UART & erase the NOR Flash */
#define UBL_MAGIC_NAND_FLASH        (0xA1ACEDCC)		/* Download via UART & Flash NAND with UBL and U-boot */
#define UBL_MAGIC_NAND_ERASE        (0xA1ACEDDD)		/* Download via UART & erase the NAND Flash */
#define UBL_MAGIC_SDMMC_FLASH       (0xA1ACEDEE)    /* Download via UART & Burn SD/MMC with UBL and U-boot */
#define UBL_MAGIC_SDMMC_ERASE       (0xA1ACEDFF)    /* Download via UART erase the SD/MMC Flash */        

// Define max UBL image size (DRAM size - 2048)
#define UBL_IMAGE_SIZE              (((Uint32)&DRAMSize) - 0x800)

// Define max app image size (1/8th of RAM size
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

#endif //_SFT_H_
