/** ===========================================================================
* @file mpeg4venc_ti_formatconvt.h
*
* @path $\\(PROJDIR)\\..\\Client\\Test\\Inc\\
*
* @desc This file defines the function interfaces for CbCr format conversion
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied 
*
* ===========================================================================*/

#ifndef __MPEG4VENC_TI_FORMATCONVT__
#define __MPEG4VENC_TI_FORMATCONVT__

/******************************************************************************
*                               INCLUDE FILES                                                
******************************************************************************/
/*----- system and platform files -------------------------------------------*/

/*-------program files ------------------------------------------------------*/

/******************************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in this file
******************************************************************************/
/*--------data declarations -------------------------------------------------*/

/*--------function prototypes -----------------------------------------------*/

/******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/
/*--------data declarations -------------------------------------------------*/

/******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
******************************************************************************/
/*--------data declarations -------------------------------------------------*/

/*--------function prototypes -----------------------------------------------*/

/*--------macros ------------------------------------------------------------*/

/**===========================================================================
*@func   MPEG4VENC_TI_PlanartoInt_CbCrformat
*
*@desc   This function converts CbCr planar format to interleaved CbCr format.
* 
*@arg    pubYFrameData
*        Pointer to the Y component of the raster-scan frame. 
*
*@arg    pubUFrameData
*        Pointer to the U component of the raster-scan frame. 
*
*@arg    pubVFrameData
*        Pointer to the V component of the raster-scan frame. 
*
*@arg    pubSubPictY
*        Pointer to the Luminance (Y) component 
*
*@arg    pubSubPictUV
*        Pointer to the interleaved Chrominance (UV) component  
*
*@arg    uiPicWidth
*        Width of the input picture.
*
*@arg    uiPicHeight
*        Heigth of the input picture.
*
*@return None
*
*@see    None
*
*@note   All YUV planar frames need to be convereted to this format before
*        giving it to Xena MPEG-4 encoder
*==============================================================================
*/
void MPEG4VENC_TI_PlanartoInt_CbCrformat(unsigned char *pubYFrameData, 
                                         unsigned char *pubUFrameData, 
                                         unsigned char *pubVFrameData, 
                                         unsigned char *pubSubPictY, 
                                         unsigned char *pubSubPictUV, 
                                         unsigned int uiPictWidth, 
                                         unsigned int uiPictHeight);

/**============================================================================
*@func   MPEG4VENC_TI_InttoPlanar_CbCrformat
*
*@desc   This function converts CbCr interleaved format to planar CbCr format
* 
*@arg    pubYFrameData
*        Pointer to the Y component of the raster-scan frame. 
*
*@arg    pubUFrameData
*        Pointer to the U component of the raster-scan frame. 
*
*@arg    pubVFrameData
*        Pointer to the V component of the raster-scan frame. 
*
*@arg    pubSubPictY
*        Pointer to the Luminance (Y) component 
*
*@arg    pubSubPictUV
*        Pointer to the interleaved Chrominance (UV) component  
*
*@arg    uiPicWidth
*        Width of the input picture.
*
*@arg    uiPicHeight
*        Heigth of the input picture.
*
*@return None
*
*@see    None
*
*@note   This function is used when recon frame is being dumped
*===========================================================================
*/
void MPEG4VENC_TI_InttoPlanar_CbCrformat(unsigned char *pubYFrameData, 
                                         unsigned char *pubUFrameData, 
                                         unsigned char *pubVFrameData, 
                                         unsigned char *pubSubPictY, 
                                         unsigned char *pubSubPictUV, 
                                         unsigned int uiPictWidth, 
                                         unsigned int uiPictHeight);


#endif /* __MPEG4VENC_TI_FORMATCONVT__ */

/*!
 *! Revision History
 *! ================
 *! 20-Apr-2007   RSV: Modified sub picture fuctions for padding and CbCr
 *!                    format conversions 
 *!
 *! 02-Apr-2007   RSV: File name and other chages to meet coding guidelines
 *!                    requirements.
 *!
 *! 08-Mar-2006   Anirbanbasu Added function to convert from 
 *!                           raster scan to sub-picture conversion.
 *!
 *! 02-Mar-2006   Dinesh Kumar: Create file and added initial code.
 */
