/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: nand.h		 				                             	  */
/*	PURPOSE	: Definitions for NAND					                          */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/

#ifndef _NAND_ROM_H_
#define _NAND_ROM_H_

#include "tistdtypes.h"
#include "cslr_emif.h"
#include "cslr_edma.h"

/* NAND FLASH ADDRESS */
#define NAND_DATA_ADDR  ((volatile Uint8*)0x02000000)	
#define NAND_ALE_ADDR	((volatile Uint8*)0x02000008)	
#define NAND_CMD_ADDR	((volatile Uint8*)0x02000010)	

#define NAND_TYPE_MASK_0X00000020 (0x00000020)  

/* NAND FLASH COMMANDS */
#define	NAND_RST			0xFF

                                   
#define MAX_NAND_SUPPORTED	(33) 			/* [vig]Change in accordance with the device info */
#define UNKNOWN_NAND		(0xFF)			/* Unknown device id */
#define NAND_NOT_FOUND      (0)
#define NAND_FOUND          (1)

typedef struct  {
    Uint8 dev_id;                 /* DeviceID */
    Uint8 p_cnt;                  /* page count per block */
    Uint16 p_byte1;               /* byte count per page(include redundant parts)*/
    Uint8 blk_shift;			  /* Number of bits by which block address is to be shifted */
    Uint8 addr_cycles;			  /* Number of address cycles */
} NAND_DEVICE_INFO;

/***    NAND_info structure */
typedef struct  {
	Uint8 nand_width;			   /* NAND width 1->16 bits 0->8 bits */ 
    Uint8 dev_code;                /* NAND_DevTable index */
    Uint8 page_cnt;                /* page count per block */
    Uint8 addr_cycles;			   /* Number of address cycles */
    Uint8 big_block;			   /* 1 - Big block device, 0 - small block device */
    Uint16 page_size;			   /* Number of bytes in a page including extra data 264/528 */
    Uint8 blk_shift;			   /* Number of bits by which block address is to be shifted */
    Uint8 page_shift;			   /* Number of bits by which 	page address is to be shifted */
} NAND_INFO;

/* Prototypes of functions for NAND flash */
void NANDConfig();
Uint32 NANDInit();
Uint32 NANDGetDetails();
Uint32 NANDReadPage(Uint32 blkAddr, Uint32 page, Uint8 *dest);
Uint32 NANDWaitRdy();                                         
Uint32 NANDWaitRdyReg();
Uint32 NANDSpareECCRead (Uint8* readPtr);
void NANDReadNBytes(Uint32 numBytes, Uint8* destAddr);     
Uint32 NANDReadNBytesDMA(Uint32 numBytes, Uint8* destAddr);

inline void NANDECCStart (void) {
	  CSL_EMIF_0_REGS->NANDFCR |= (1<<8);
}

inline Uint32 NANDECCRead (void) {
	 return CSL_EMIF_0_REGS->NANDF1ECC;
}

/* copies the UBL from NAND to IRAM */
Uint32 NANDCopy();

/* copies the UBL from NAND to IRAM and decrypt it(SECURE mode)*/
Uint32 NANDSecureCopy();

#endif //_NAND_ROM_H_
