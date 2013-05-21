#ifndef _TESTAPPDEC_H_
#define _TESTAPPDEC_H_

/** ============================================================================
 *  @file   vc1vdec_ti_testappdec.h
 *
 *  @path   $(PROJDIR)\inc
 *
 *  @desc    This is the top level client header file that drives the VC1
 *           (Main Profile) Video Decoder Call using XDM Interface
 *  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===========================================================================*/

/* ---------------------compilation control switches -------------------------*/

/*******************************************************************************
*                  INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

//#include <xdas.h>
//#include <tistdtypes.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/ivideo.h>
//#include "ividdec1.h"
#include <ti/xdais/dm/ividdec2.h>
//#include <stdio.h>

/*----------------------program files ----------------------------------------*/

#include "vc1vdec_ti_config.h"

/*******************************************************************************
*          EXTERNAL REFERENCES NOTE : only use if not found in header file
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*-----------------------function prototypes ---------------------------------*/


/*******************************************************************************
*            PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/


/*-----------------------function prototypes ---------------------------------*/
/** ============================================================================
* @func  TestApp_EnableCache
*
* @desc  Enable cache settings for system
*
* @arg   void
*        None
*
* @ret   Null
* ==============================================================================
*/
XDAS_Void   TestApp_EnableCache(void);

/** ============================================================================
* @func  TestApp_ReadByteStream
*
* @desc  Reads Input Data from FILE
*
* @arg   inFile
*        Input File Handle.
*
* @ret   XDAS_Int32
*        Status of the operation ( PASS / FAIL )
* ==============================================================================
*/
XDAS_Int32  TestApp_ReadByteStream(xdc_Char *inFile);

/** ============================================================================
* @func  TestApp_WriteOutputData
*
* @desc  Writes Output Data into FILE
*
* @arg   fOutFile
*        Output File Handle
*
* @arg   height
*        Frame Height
*
* @arg   width
*        Frame Width
*
* @ret   Null
* ==============================================================================
*/
XDAS_Void TestApp_WriteOutputData(
                        FILE *fOutFile,
                        XDAS_Int32  height,
                        XDAS_Int32  width
                        );

/*****************************************************************************/
/**
 *@func  TestApp_CompareOutputData()
 *@brief  Sample utility function for comparing the raw decoded output with
 *           reference output data.
 *
 *@param  FILE *fRefFile:
 *           Reference file pointer.
 *  @param    height
 *            Frame height
 *
 *  @param    width
 *            Frame width
 *@return XDM_EFAIL : If comparision fails.
 *        XDM_EOK: If comparision passes.
 *
 *@note   None
 */
/*****************************************************************************/
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
                                    XDAS_Int32  height,
                                    XDAS_Int32  width);
/* =============================================================================
 *  @func     separateCbCrPixels
 *
 *  @desc     Separate the interleaved croma pixels into diff buffers
 *
 *  @param    CbCr_data
 *            Interleaved input
 *
 *  @param    Chroma_buf[2]
 *            Output buffers
 *
 *  @param    height
 *            Frame height
 *
 *  @param    width
 *            Frame width
 *
 *  @param    paddedWidth
 *            Padded width
 *
 *  @parma    paddedHeight
 *            Padded height
 *
 *  @return   XDAS_Void
 *            Null
 *  ============================================================================
 */

void separateCbCrPixels(XDAS_UInt8  *CbCr_data,
                        XDAS_UInt8  *Chroma_buf[2],
                        XDAS_Int32  height,
                        XDAS_Int32  width,
                        XDAS_UInt16 paddedWidth,
                        XDAS_UInt16 paddedHeight
                        );
/* =============================================================================
 * TestApp_ResolutionUpsample()
 * Description:
 *              Sample Upsample filter for VC1 decoded frame.
 *
 * Remarks:
 * This is just an example upsample filter and is not specified in the spec.
 * The spec leaves the choice of resolution scale upsample filter as
 * implementation dependant
 *
 * Inputs:
 * pDest    - Pointer to destination line (upsampled)
 * pSrc     - Pointer to source line
 * Skip     - Byte skip between each line element
 * Length   - Number of output samples to write
 * Limit    - Number of input samples available
 *=============================================================================
 */
XDAS_Void TestApp_ResolutionUpsample(
                        XDAS_UInt8 *pDest,
                        XDAS_UInt8 *pSrc,
                        XDAS_Int32 Skip,
                        XDAS_Int32 Length,
                        XDAS_Int32 Limit
                        );
/*****************************************************************************/
/**
 *@func  TestApp_CompareOutputData()
 *@brief  Sample utility function for postprocessing of VC1 Stream decoded data
 *
 *@param  FILE *fRefFile:
 *           Reference file pointer.
 *  @param    height
 *            Frame height
 *
 *  @param    width
 *            Frame width
 *@return XDM_EFAIL : If comparision fails.
 *        XDM_EOK: If comparision passes.
 *
 *@note   None
 */
/*****************************************************************************/
XDAS_Int32 TestApp_PostProcessData( IVIDDEC2_OutArgs *outArgs,
                                    XDAS_Int32  height,
                                    XDAS_Int32  width
                                  );

/** ============================================================================
* @func  TestApp_SetInitParams
*
* @desc  Set creation time parameters
*
* @arg   Params
*        Creation parameters
*
* @ret   Null
* ==============================================================================
*/
XDAS_Void   TestApp_SetInitParams(IVIDDEC2_Params *Params);

/** ============================================================================
* @func  TestApp_SetDynamicParams
*
* @desc  Set run time parameters
*
* @arg   DynamicParams
*        Run time parameters.
*
* @ret   Null
* ==============================================================================
*/
XDAS_Void   TestApp_SetDynamicParams(IVIDDEC2_DynamicParams *DynamicParams);

/** ============================================================================
* @func  readparamfile
*
* @desc  Parses codec specific parameter file and populates configurable
*        parameters.
*
* @arg   fname
*        parameter FILE handle.
*
* @ret   Null
* ==============================================================================
*/
XDAS_Int32 readparamfile(FILE * fname) ;

/** ============================================================================
* @func  VC1VDEC_TI_Decode_Picture
*
* @desc  Decode start at slice level
*
* @arg   fname
*        parameter FILE handle.
*
* @ret   Null
* ==============================================================================
*/
#ifndef SINGLE_PROCESSOR
XDAS_Int32 VC1VDEC_TI_Decode_Picture();
#endif
/*******************************************************************************
*              PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*-----------------------function prototypes ---------------------------------*/

/*-----------------------macros ----------------------------------------------*/

/** ============================================================================
* @const  INPUT_BUFFER_SIZE
*
* @desc   This is the Maximum size for D1 frame
*         As per the standard the maximum size of
*
* ==============================================================================
*/
//#define INPUT_BUFFER_SIZE      0x4E2000
#define INPUT_BUFFER_SIZE        0x200000
//#define INPUT_BUFFER_SIZE      0x7D000

/** ============================================================================
* @const  OUTPUT_BUFFER_SIZE
*
* @desc   Size of the output buffer.
*
* ==============================================================================
*/
/* Below is hack done for VC1 QT setup we will discuss and finalise later */
//#define OUTPUT_BUFFER_SIZE     (784*640*3)/2
#define OUTPUT_BUFFER_SIZE     (1920*1088*3)/2
/** ============================================================================
* @const  MAX_LUMA_BUFFER_SIZE
*
* @desc    Max Luma buffer size for DM510.
*
* ==============================================================================
*/
//#define MAX_LUMA_BUFFER_SIZE 720*576
#define MAX_LUMA_BUFFER_SIZE 1920*1088
/** ============================================================================
* @const  MAX_LUMA_BUFFER_SIZE
*
* @desc    Max Croma buffer size for DM510 this includes both Cb and Cr data
*
* ==============================================================================
*/
#define MAX_CROMA_BUFFER_SIZE MAX_LUMA_BUFFER_SIZE>>2

/** ============================================================================
* @const REF_BUFFER_SIZE
*
* @desc   Size of the output buffer.
*
* ==============================================================================
*/
/* Below is hack done for VC1 QT setup we will discuss and finalise later */
#define REF_BUFFER_SIZE     1024 * 500

/** ============================================================================
* @const  STRING_SIZE
*
* @desc   Size of string.
*
* ==============================================================================
*/
#define STRING_SIZE            600

/** ============================================================================
* @const  NUM_ALGS
*
* @desc   Number of Algorithms.
*
* ==============================================================================
*/
#define NUM_ALGS                 1

/** ============================================================================
* @const  DISPLAY_YUV_SIZE
*
* @desc   Size of the display YUV.
*
* ==============================================================================
*/
//#define DISPLAY_YUV_SIZE        784*640
#define DISPLAY_YUV_SIZE        1920*1088

 /** ===========================================================================
  *  @name   sTokenMapping
  *
  *  @desc   Token Mapping structure for parsing codec specific config file.
  *
  *  @field  tokenName
  *          String name in the configuration file
  *
  *  @field  place
  *          Place Holder for the data
  *
  *  ===========================================================================
  */
typedef struct _sTokenMapping {
  xdc_Char *tokenName;
  XDAS_Void *place;
} sTokenMapping;

/********************************************************************
 * RCV constants
 *******************************************************************/

/*
 * The RCV format contains a type byte. The top bit indicates
 * extension data. We need VC1 type, with extension data.
 */
#define RCV_VC1_TYPE (0x85)
/* Bit 6 of the type indicates V1 if 0, V2 if 1 */
#define RCV_V2_MASK (1 << 6)
/* Top nibble bits of frame size word are flags in V2 */
#define RCV_V2_FRAMESIZE_FLAGS (0xf0000000)
#define RCV_V2_KEYFRAME_FLAG   (0x80000000)

/* V2 extra information has a VBR flag */
#define RCV_V2_VBR_FLAG (0x10000000)



#endif /* end of _TESTAPPDEC_H_ */


