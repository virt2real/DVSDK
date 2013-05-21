/** ===========================================================================
* @file  h264venc_tii.h
*
* @path  $\\(PROJDIR)\\..\\Inc\\
*
* @desc Interface for the H264VENC_TI module; TI's implementation
*                of the H264VENC interface.
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
#ifndef H264VENC_TII_
#define H264VENC_TII_

/******************************************************************************
*                               INCLUDE FILES                                                
******************************************************************************/
/*----- system and platform files -------------------------------------------*/
#include <ti/xdais/ialg.h>
/*-------program files ------------------------------------------------------*/
#include "ih264venc.h"
/******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/
/*--------data declarations -------------------------------------------------*/

/*--------macros-------------------------------------------------------------*/

/*--------function prototypes -----------------------------------------------*/

/*=============================================================================
 * H264VENC_TI_IALG
 *
 * TI's implementation of the IALG interface for H264VENC
 */
extern IALG_Fxns H264VENC_TI_IALG;

/*=============================================================================
 * H264VENC_TI_IH264VENC
 *
 * TI's implementation of the H264VENC interface
 */
extern IH264VENC_Fxns H264VENC_TI_IH264VENC;

#endif  /* H264VENC_TII_ */

/*!
 *! Revision History
 *! ================
 *! 02-10-2007   Sunil Koteyar: File and Function Header updates
 */
