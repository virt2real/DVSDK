/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: cslr_uhpi.h		 				                          	  */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/

#ifndef _CSLR_UHPI_H_
#define _CSLR_UHPI_H_

#include <cslr_uhpi_001.h>
typedef volatile CSL_UhpiRegs           *CSL_UhpiRegsOvly;
#define CSL_UHPI_0_REGS                 ((CSL_UhpiRegsOvly) 0X01C67800)

#endif/*_CSLR_UHPI_H_*/


