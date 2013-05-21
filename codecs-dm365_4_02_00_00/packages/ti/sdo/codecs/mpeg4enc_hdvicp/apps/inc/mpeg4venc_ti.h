/** ===========================================================================
* @file  mpeg4venc_ti.h
*
* @path  $\\(PROJDIR)\\..\\Inc\\
*
* @desc Interface for the MPEG4VENC_TI module; TI's implementation
*                of the IMP4VENC interface.
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/
/*------compilation control switches ----------------------------------------*/
#ifndef __MPEG4VENC_TI__
#define __MPEG4VENC_TI__

/******************************************************************************
*                               INCLUDE FILES
******************************************************************************/
/*----- system and platform files -------------------------------------------*/
//#include <ialg.h>
#include <ti/xdais/ialg.h>
/*-------program files ------------------------------------------------------*/
#include "imp4venc.h"
/******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/
/*--------data declarations -------------------------------------------------*/

/*--------macros-------------------------------------------------------------*/

/*--------function prototypes -----------------------------------------------*/

/*=============================================================================
 * MPEG4VENC_TI_IALG
 *
 * TI's implementation of the IALG interface for MPEG4VENC
 */
extern IALG_Fxns MPEG4VENC_TI_IALG;


/*=============================================================================
 * MPEG4VENC_TI_IMPEG4VENC
 *
 * TI's implementation of the IMP4VENC interface
 */
extern IMP4HDVICPENC_Fxns MPEG4VENC_TI_IMPEG4VENC;


#endif  /* __MPEG4VENC_TI__ */

/*!
 *! Revision History
 *! ================
 *!
 *! 02-Apr-2007   RSV: File name and other chages to meet coding guidelines
 *!                    requirements.
 *!
 *! 27-Jan-2006   Anirban Basu: Create file and added initial code.
 */

