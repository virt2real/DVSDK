/******************************************************************************/
/*            TEXAS INSTRUMENTS INCORPORATED PROPRIETARY INFORMATION          */ 
/*   Created 2005, (C) Copyright 2005 Texas Instruments.  All rights reserved.*/ 
/*																			  */
/* 	FILE	: cslr_edma.h		 				                          	  */
/*  PROJECT	: DaVinci ROM boot-loader 		                                  */
/*  AUTHOR	: Vignesh LA					                                  */
/*  DATE	: April-25-2005                                                   */
/******************************************************************************/

#ifndef _CSLR_EDMA_H_
#define _CSLR_EDMA_H_

#include <cslr_edmacc_001.h>
#include <cslr_edmatc0_001.h>

#define CSL_EDMA_CC_CNT                 1
#define CSL_EDMA_TC0_CNT                1
#define CSL_EDMA_TC1_CNT                1

typedef volatile CSL_EdmaccRegs         *CSL_EdmaccRegsOvly;
typedef volatile CSL_EdmaccShadowRegs   *CSL_EdmaccShadowRegsOvly;
typedef volatile CSL_Edmatc0Regs        *CSL_Edmatc0RegsOvly;

#define CSL_EDMACC_0_REGS               ((CSL_EdmaccRegsOvly)  0x1C00000) 
#define CSL_EDMATC_0_REGS               ((CSL_Edmatc0RegsOvly) 0x1C10000) 

#endif/*_CSLR_EDMA_H_*/

