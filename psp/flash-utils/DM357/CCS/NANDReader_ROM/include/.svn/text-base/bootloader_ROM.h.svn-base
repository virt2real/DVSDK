/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: bootloader.h		 				                          	  */
/*	PURPOSE	: Definitions for boot loader			                          */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/

#ifndef _BOOTLOADER_H_
#define _BOOTLOADER_H_
//#define PROFILE

#include "cslr_intc.h"
#include "cslr_psc.h"

#include <error.h>

#ifdef PROFILE      
#include "cslr_tmr.h"
#endif

#include "tistdtypes.h"

/* System module registers */
#define PINMUX0			((volatile Uint32*)0x01C40000)
#define PINMUX1	        ((volatile Uint32*)0x01C40004)
#define DSPBOOTADDR     ((volatile Uint32*)0x01C40008)
#define INTGEN			((volatile Uint32*)0x01C40010)
#define BOOTCFG 		((volatile Uint32*)0x01C40014)
#define CHP_SHRTSW      ((volatile Uint32*)0x01C40038)
#define SEC_SCAN_REG 	((volatile Uint32*)0x01C40050)
#define SEC_TEST_REG 	((volatile Uint32*)0x01C40054)
#define PUBLIC_KEY0		((volatile Uint32*)0x01C4005C)
#define PUBLIC_KEY1		((volatile Uint32*)0x01C40060)
#define PUBLIC_KEY2		((volatile Uint32*)0x01C40064)
#define PUBLIC_KEY3		((volatile Uint32*)0x01C40068)

#define BL_MEM 		(0x00008020) 	/* starting address in IRAM where User boot loader will be copied */
#define NOR_BASE    (0x02000000)    /* starting address of NOR flash */

#define MAGIC_NUMBER_VALID (0xA1ACED00)

#define UBL_MAGIC_SAFE			(0xA1ACED00)		/* Safe boot mode */
#define UBL_MAGIC_DMA			(0xA1ACED11)		/* DMA boot mode */
#define UBL_MAGIC_IC			(0xA1ACED22)		/* I Cache boot mode */
#define UBL_MAGIC_FAST			(0xA1ACED33)		/* Fast EMIF boot mode */
#define UBL_MAGIC_DMA_IC		(0xA1ACED44)		/* DMA + I Cache boot mode */
#define UBL_MAGIC_DMA_IC_FAST	(0xA1ACED55)		/* DMA + I Cache + Fast EMIF boot mode */

#define DSP_SEC_ROM_ADDR_0x00E00000 0x00E00000
#define DEVICE_TYPE_MASK_0X00000007 0x00000007
#define BOOTCFG_MASK_0X000000C0 0x000000C0

#define MAGIC_DSP_ID (0xAA55BEEF)

typedef struct {
	Uint32 entryPoint;	/* Entry point of the user boot loader (should be in 0x2000-0x3FFF region */
	Uint32 numPage;		/* Number of pages where boot loader is stored */
	Uint32 block;		/* starting block number where User boot loader is stored */
	Uint32 page;		/* starting page number where boot-loader is stored */
} NAND_BOOT;

typedef enum DeviceType_ {
	TEST = 0,
	EMU,
	SECURE,
	NON_SECURE,
	BAD 

} DeviceType;

typedef enum BootMode_ {
	/* Non secure NAND mode - Using ROM bootloader */
	NON_SECURE_NAND = 0,
	/* Non secure NOR mode - Direct boot */
	NON_SECURE_NOR,
	/* Non secure HPI mode - Using ROM bootloader */
	NON_SECURE_UHPI,
	/* Non secure UART mode - Using ROM bootloader */
	NON_SECURE_UART,
	/* Secure NAND mode - Using ROM bootloader */
	SECURE_NAND,
	/* Secure NOR mode - Using ROM bootloader */
	SECURE_NOR,
	/* Secure UART mode - Using ROM bootloader */
	SECURE_UART
		
} BootMode;

/* Function prototypes */
Uint32 LPSCEnable(Uint8 PdNum, Uint8 LPSCNUM);
void EnableICache();
void DisableICache();
BootMode FindBootMode();
Uint32 NORSecureCopy();
void waitloop (Uint32 count);
Uint32 BootDSP();
Uint32 MagicSwitch(Uint32 magicNum);


#endif //_BOOTLOADER_H_
