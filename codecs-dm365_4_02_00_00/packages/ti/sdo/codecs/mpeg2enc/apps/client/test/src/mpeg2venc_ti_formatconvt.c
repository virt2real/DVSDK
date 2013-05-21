/** ===========================================================================
* @file  mpeg2venc_ti_formatconvt.c
*
* @path  @path $\\(PROJDIR)\\..\Client\\Test\\Src\\
*
* @brief This File contains functions for padding and CbCr format conversion.
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/
/*------compilation control switches ----------------------------------------*/

/******************************************************************************
*                               INCLUDE FILES
******************************************************************************/
/*----- system and platform files -------------------------------------------*/
#include <string.h>
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
/* PAD_WIDTH
 * Padding width in pixels : 32, as ME horizontal search range is +/-32
 */
#define PAD_WIDTH           32
/* PAD_HEIGHT
 * Padding Height in pixels: 24, as ME vertical search range is +/-24
 */
#define PAD_HEIGHT          24

/*****************************************************************************/
/*       GLOBAL FUNCTION DEFINITIONS (DEFINED HERE / CALLED ELSEWHERE)       */
/*****************************************************************************/

/**===========================================================================
*@func   MPEG2VENC_TI_PlanartoInt_CbCrformat
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
*===========================================================================
*/
void MPEG2VENC_TI_PlanartoInt_CbCrformat(unsigned char *pubYFrameData,
                                         unsigned char *pubUFrameData,
                                         unsigned char *pubVFrameData,
                                         unsigned char *pubSubPictY,
                                         unsigned char *pubSubPictUV,
                                         unsigned int   uiPictWidth,
                                         unsigned int   uiPictHeight)
{
    unsigned short j,k;
    unsigned char *pubSrcY, *pubSrcU, *pubSrcV;
    unsigned char *pubDst[2];
    unsigned char ubIdx = 0;

    /*-----------------------------------------------------------------------*/
    /*                         CONVERT LUMINANCE DATA                        */
    /*-----------------------------------------------------------------------*/

    pubDst[0] = pubSubPictY;
    ubIdx = 0;

    for(j = 0; j < uiPictHeight; j++)
    {
        /* Update the source pointer*/
        pubSrcY = pubYFrameData + (j * uiPictWidth);

        memcpy(pubDst[ubIdx], pubSrcY, uiPictWidth);
        /* Update the destination pointer*/
        pubDst[ubIdx] += uiPictWidth;
    }/* 0 - uiPictHeight*/

    /*-----------------------------------------------------------------------*/
    /*                         CONVERT CHROMINANCE DATA                      */
    /*-----------------------------------------------------------------------*/

    uiPictHeight >>= 1;
    uiPictWidth >>= 1;
    pubDst[0] = pubSubPictUV;

    ubIdx = 0;
    for(j = 0; j < uiPictHeight; j++)
    {
        unsigned char *pubCurDst;
        /* update source and destination pointers for each row*/
        pubSrcU = pubUFrameData + (j * uiPictWidth);
        pubSrcV = pubVFrameData + (j * uiPictWidth);
        pubCurDst = pubDst[ubIdx];

        for(k = 0; k < uiPictWidth; k++)
        {
            *pubCurDst       = *pubSrcU;
            *(pubCurDst + 1) = *pubSrcV;

            /*Update pointers*/
            pubCurDst += 2;
            pubSrcU++;
            pubSrcV++;
         }
         pubDst[ubIdx] += (uiPictWidth << 1);
    }/* 0 - uiPictHeight*/
}/* MPEG2VENC_TI_PlanartoInt_CbCrformat */


/**============================================================================
*@func   MPEG2VENC_TI_InttoPlanar_CbCrformat
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
void MPEG2VENC_TI_InttoPlanar_CbCrformat(unsigned char *pubYFrameData,
                                         unsigned char *pubUFrameData,
                                         unsigned char *pubVFrameData,
                                         unsigned char *pubSubPictY,
                                         unsigned char *pubSubPictUV,
                                         unsigned int   uiPictWidth,
                                         unsigned int   uiPictHeight)
{
    unsigned short j,k;
    unsigned char *pubSrc[2];
    unsigned char *pubDstY;
    unsigned char *pubDstU;
    unsigned char *pubDstV;
    unsigned char *pubCurSrc;

    /*-----------------------------------------------------------------------*/
    /*                         CONVERT LUMINANCE DATA                        */
    /*-----------------------------------------------------------------------*/
#if 0
    pubSrc[0] = pubSubPictY + PAD_WIDTH +
    	    	((uiPictWidth  + (PAD_WIDTH<<1))* PAD_HEIGHT);
#else
	pubSrc[0] = pubSubPictY;
#endif

    for(j = 0; j < uiPictHeight; j++)
    {
        /*Update the destination pointer*/
        pubDstY = pubYFrameData  + (j * uiPictWidth);
        memcpy(pubDstY, pubSrc[0], uiPictWidth);
        /*Update the source pointer*/
        pubSrc[0] += (uiPictWidth  + (PAD_WIDTH<<1));
    }/* 0 - uiPictHeight*/

    /*-----------------------------------------------------------------------*/
    /*                           CONVERT CHROMINANCE DATA                    */
    /*-----------------------------------------------------------------------*/
#if 0
    pubSrc[0] = pubSubPictUV + PAD_WIDTH +
    	    	((uiPictWidth + (PAD_WIDTH<<1))* (PAD_HEIGHT>>1));
#else
	pubSrc[0] = pubSubPictUV;
#endif
    for(j = 0; j < (uiPictHeight>>1); j++)
    {
      /* update chrominance data pointers for each row*/
      pubDstU = pubUFrameData + (j * (uiPictWidth>>1));
      pubDstV = pubVFrameData + (j * (uiPictWidth>>1));
      pubCurSrc = pubSrc[0];
      for(k = 0; k < (uiPictWidth>>1); k++)
      {
          *pubDstU  = *pubCurSrc;
          *pubDstV  = *(pubCurSrc + 1);

          /* Update pointers*/
          pubCurSrc += 2;
          pubDstU++;
          pubDstV++;
      }
      pubSrc[0] += (uiPictWidth + (PAD_WIDTH<<1));

    }/* 0 - uiPictHeight*/

	return;
}/* MPEG2VENC_TI_InttoPlanar_CbCrformat */

/*---------------------------------------------------------------------------*/
/*       LOCAL STATIC FUNCTION DEFINITIONS (DEFINED HERE / USED HERE)        */
/*---------------------------------------------------------------------------*/

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

