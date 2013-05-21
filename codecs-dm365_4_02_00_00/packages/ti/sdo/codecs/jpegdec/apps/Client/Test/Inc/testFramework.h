/******************************************************************************/
/*            Copyright (c) 2006 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/******************************************************************************/

/*!
********************************************************************************
  @file     TestAppEncoder.h
  @brief    This is the top level client header file that drives the H264
            (Baseline Profile) Video Encoder Call using XDM Interface
  @author   Multimedia Codecs TI India
  @version  0.0 - Jan 24,2006    initial version
********************************************************************************
*/

#ifndef _TESTAPP_JPEG_DECODER_
#define _TESTAPP_JPEG_DECODER_

#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/xdm.h>
#include <ti/xdais/dm/iimgdec1.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_WIDTH 1280
#define MAX_HEIGHT 960
#define JPEG_MAX_NUM_JPEG_BYTES		(3*MAX_WIDTH*MAX_HEIGHT)       // Max stream size 1M byte
#define RINGBUF_SIZE                (1024*4096)       // (20*4096)       // Ring buffer size
#define JPEG_MAX_NUM_YCC_BYTES	    (3*MAX_WIDTH*MAX_HEIGHT)
#define AIM_START_ADDRESS           (0x10000)
#define INTERNAL_DATA_MEM_SIZE     (4096)
#define EXTERNAL_DATA_MEM_SIZE     (16*1024)
#define JPEG_MAX_NUM_RGB_BUFFER_LINES	(16)
#define JPEG_MAX_NUM_SAMPLES_PER_LINE	(5000+32)		// Width
#define STRING_SIZE         256      //!< Size of strings used for filenames

typedef enum TestTypeEnum{
 TEST_PATTERNCOMP,
 TEST_FILECOMP,
 TEST_FILEDUMP	
} TestType;

/*!
@struct sTokenMapping 
@brief  Token Mapping structure for parsing codec specific configuration file
@param  tokenName : String name in the configuration file
@param  place     : Place Holder for the data
*/

typedef struct sTokenMapping{
  XDAS_Int8 *tokenName;
  XDAS_Void *place;
  XDAS_Int32 size;
} sTokenMapping;


Int32 initTestFramework(Int8 *fname, TestType *testtype, sTokenMapping *sTokenmap);
Int32 initTestFramework1(Int8 *fname, TestType *testtype, sTokenMapping *sTokenmap_base);

Int32 nextTestSet();
Uint32 testReadJpegfile(char *output, Uint32 len);

/* Function Declarations                                                      */
/*!
********************************************************************************
  @fn									      XDAS_Int32 TestApp_ReadInputData(FILE *finFile,
                                   XDM_BufDesc* inputBufDesc);
	@brief							      Reads Input Data from FILE
  @param  finFile[IN]       Input File Handle
  @param  inputBufDesc[IN]  Buffer Descriptor for input buffers
	@return							      Status of the operation ( PASS / FAIL )
********************************************************************************
*/
XDAS_Int32 TestApp_ReadInputData(FILE *finFile, XDAS_UInt32  frameCount,
                                 XDM_BufDesc* inputBufDesc);

/*!
********************************************************************************
  @fn									      XDAS_Void TestApp_WriteOutputData(FILE *fOutFile, 
                                  XDM_BufDesc * outputBufDesc,  
                                  IIMGDEC1_OutArgs *outArgs);
	@brief							      Writes Output Data into FILE
  @param  fOutFile[IN]      Output File Handle
  @param  outputBufDesc[IN] Buffer Descriptor for output buffers
  @param  outArgs[IN]       Info for args related to output buf(like numBytes)
	@return							      NONE
********************************************************************************
*/

XDAS_Void TestApp_WriteOutputData(FILE *fOutFile, XDAS_UInt32  offset,
                                  XDM_BufDesc * outputBufDesc,  
                                  IIMGDEC1_OutArgs *outArgs);

/*!
********************************************************************************
  @fn									      XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile, 
                                     XDM_BufDesc * outputBufDesc, 
                                     IIMGDEC1_OutArgs *outArgs, 
                                     XDAS_Int32 offset);
	@brief							      Compares Output Data with Reference
  @param  fRefFile[IN]      Reference File Handle
  @param  outputBufDesc[IN] Buffer Descriptor for output buffers
  @param  outArgs[IN]       Info for args related to output buf(like numBytes)
	@return							      NONE
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile, XDAS_UInt32  offset,
                                     XDM_BufDesc * outputBufDesc, 
                                     IIMGDEC1_OutArgs *outArgs);
/*!
********************************************************************************
  @fn									      XDAS_Void TestApp_SetInitParams(
                                IIMGDEC1_Params *params);
	@brief							      Set creation time parameters
  @param  params[IN]        Creation parameters
	@return							      NONE
********************************************************************************
*/

XDAS_Void TestApp_SetInitParams(IIMGDEC1_Params *params);

/*!
********************************************************************************
  @fn									      XDAS_Void TestApp_SetDynamicParams(
                                IIMGDEC1_DynamicParams *dynamicParams);
	@brief							      Set run time parameters
  @param  dynamicParams[IN] run time parameters
	@return							      NONE
********************************************************************************
*/

XDAS_Void TestApp_SetDynamicParams(IIMGDEC1_DynamicParams *dynamicParams);

/*!
********************************************************************************
  @fn									      XDAS_Int32 readparamfile(FILE * fname) ;
	@brief							      Parses codec specific parameter file and populates
                            configurable parameters
  @param  fname[IN]         parameter FILE handle
	@return							      NONE
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname,  sTokenMapping *sTokenMap) ;

#endif //_TESTAPP_ENCODER_

/******************************************************************************/
/*    Copyright (c) 2006 Texas Instruments, Incorporated                      */
/*    All Rights Reserved                                                     */
/******************************************************************************/

