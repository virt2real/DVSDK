/*
******************************************************************************
*  
* DM36x Based H.264 Decoder Test Application
*
* "DM36x Based H.264 Decoder Test application is software module developed on TI's DM36x.
* This module shows XDM interface for H.264 Video Decoder.
* Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
* ALL RIGHTS RESERVED 
******************************************************************************
*/
/** ===========================================================================
* @file separateCbCr.c
*
* @path $(PROJDIR)\src
*
* @brief This File contains function definitions which provide a sample 
*        implementation for seperating interleaved chroma Cb Cr values into 
*        seperate blocks.
* =============================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**============================================================================*/
/* ------compilation control switches -------------------------*/
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
/* ----- system and platform files ----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
/*-------program files ----------------------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/*--------function definitions---------------------------------*/
/*****************************************************************************/
/**
*@func separateCbCrPixels()
*@brief  TI's (Texas Instrument) implementation of utility function used for 
*           seperatign Cb and Cr chroma components from packed format.
*
*        Chroma components which are stored in interleaved format with 
*           alternating bytes is the native format used on Kaleido-based 
*           platforms. Since external YUV players accept data in Y, Cb & Cr data
*           dumped in planar format one after the other we need the following 
*           utility function for conversion in the test application.
*
*@param  XDAS_Int8  *CbCr_data
*        Input pointer to CbCr data stored in interleaved byte-byte format.
*
*@param  XDAS_Int8  *Chroma_buf[2]
*        Pointers to output buffers which would hold the seperated Cb Cr data.
*
*@param  XDAS_Int32  height
*        Picture height in pixels [with one pixel = one byte]
*
*@param  XDAS_Int32  width
*        Picture width in pixels - Chroma width is half of this value since 
*           its sub-sampled in this dimension.
*
*@param  XDAS_UInt16 paddedWidth
*        Picture padding width in pixels - this gives the total chroma pad width
*           on both sides - ideally its the picture pitch expressed in bytes..
*
*@return None
*
*/
/*****************************************************************************/
void separateCbCrPixels
(
      XDAS_Int8  *CbCr_data,
      XDAS_Int8  *Chroma_buf[2],
      XDAS_Int32  height,
      XDAS_Int32  width,
      XDAS_UInt16 paddedWidth
)
{
  XDAS_UInt32 i,j;
  XDAS_UInt32 pix_count = 0;
  XDAS_Int8* Cb_data;
  XDAS_Int8* Cr_data;
  XDAS_Int8* CbCr_buf;
  Cb_data = Chroma_buf[0];
  Cr_data = Chroma_buf[1];
  CbCr_buf = CbCr_data;

  for(i = 0; i< height; i++)
  {
    for(j = 0; j< width; j+=2)
    {
       Cb_data[pix_count] = CbCr_buf[j];
       Cr_data[pix_count] = CbCr_buf[j+1];
       pix_count++;
    }
    CbCr_buf += paddedWidth;
  }
}
/*!
*! Revision History
*! ================
*! 31-May-2007 Vinay M K: Modified to comply with MMCodecs 
*!                        coding guidelines.
*! 24-Mar-2006: Shyam Jagannathan Created.
*/
