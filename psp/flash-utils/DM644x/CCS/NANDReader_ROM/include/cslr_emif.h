/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: cslr_emif.h 				                          	  */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/

#ifndef _CSLR_EMIF_H_
#define _CSLR_EMIF_H_

#include <cslr_emif_001.h>
typedef volatile CSL_EmifRegs *CSL_EmifRegsOvly;
#define CSL_EMIF_0_REGS ((CSL_EmifRegsOvly) 0x01E00000)

#endif/*_CSLR_EMIF_H_*/
