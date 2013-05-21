/******************************************************************************/
/*            Copyright (c) 2006 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/******************************************************************************/

/*!
********************************************************************************
  @file     TestAppEncoder.h
  @brief    This is the top level client header file that drives the H264
            (Baseline Profile) Video Encoder Call using XDM Interface
  @author   TI India
  @version  0.1 - May 11,2006    initial version
********************************************************************************
*/

#ifndef _TESTAPP_ENCODER_
#define _TESTAPP_ENCODER_

#include <stdio.h>
#include <imp4venc.h>

/* Macro definitions for constants and Buffer sizes*/
#define AIM_START_ADDRESS 0x10000
#define IMAGE_WIDTH         (1920)        //!< Maximum Width of the Input Buffer
#define IMAGE_HEIGHT        (1080)    //!< Maximum Height of the Input Buffer
#define INPUT_BUFFER_SIZE   (IMAGE_WIDTH*IMAGE_HEIGHT*2)        //!< Input Buf Size
#define OUTPUT_BUFFER_SIZE  ((IMAGE_WIDTH*IMAGE_HEIGHT)>>1)

#define MVDATA_SIZE  ((IMAGE_WIDTH*IMAGE_HEIGHT*8) >> 8)  //for storing motion vectors
//#define MVDATA_SIZE  ((IMAGE_WIDTH*IMAGE_HEIGHT))  //for storing motion vectors

#define STRING_SIZE         256 //!< Size of strings used for filenames
#define NUM_ALGS            1   //!< Number of Algorithms

#define INTERNAL_DATA_MEM_SIZE    (0x5000)
/* list of some parameters macros for worst case memory allocation in external memory */
#define EXTERNAL_DATA_MEM_SIZE    ( (IMAGE_WIDTH + 64)*(IMAGE_HEIGHT + 64)*3 + MVDATA_SIZE + 130000)


/*!
@struct sTokenMapping
@brief  Token Mapping structure for parsing codec specific configuration file
@param  tokenName : String name in the configuration file
@param  place     : Place Holder for the data
*/

typedef struct sTokenMapping {
    XDAS_Int8 *tokenName;
    XDAS_Void *place;
} sTokenMapping;

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
XDAS_Int32 TestApp_ReadInputData(FILE * finFile, XDAS_UInt32 frameCount,
                                 IVIDEO1_BufDescIn * inputBufDesc);

/*!
********************************************************************************
  @fn									      XDAS_Void TestApp_WriteOutputData(FILE *fOutFile,
                                  XDM_BufDesc * outputBufDesc,
                                  IVIDENC_OutArgs *outArgs);
	@brief							      Writes Output Data into FILE
  @param  fOutFile[IN]      Output File Handle
  @param  outputBufDesc[IN] Buffer Descriptor for output buffers
  @param  outArgs[IN]       Info for args related to output buf(like numBytes)
	@return							      NONE
********************************************************************************
*/

XDAS_Void TestApp_WriteOutputData(FILE * fOutFile, XDAS_UInt32 offset,
                                  XDM_BufDesc * outputBufDesc,
                                  IVIDENC1_OutArgs * outArgs);

/*!
********************************************************************************
  @fn									      XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
                                     XDM_BufDesc * outputBufDesc,
                                     IVIDENC_OutArgs *outArgs,
                                     XDAS_Int32 offset);
	@brief							      Compares Output Data with Reference
  @param  fRefFile[IN]      Reference File Handle
  @param  outputBufDesc[IN] Buffer Descriptor for output buffers
  @param  outArgs[IN]       Info for args related to output buf(like numBytes)
	@return							      NONE
********************************************************************************
*/
XDAS_Int32 TestApp_CompareOutputData(FILE * fRefFile, XDAS_UInt32 offset,
                                     XDM_BufDesc * outputBufDesc,
                                     IVIDENC1_OutArgs * outArgs);

/*!
********************************************************************************
  @fn									      XDAS_Int32 readparamfile(FILE * fname) ;
	@brief							      Parses codec specific parameter file and populates
                            configurable parameters
  @param  fname[IN]         parameter FILE handle
	@return							      NONE
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname, int baseParamsOnly);


/*!
********************************************************************************
@fn							   XDAS_Void TestApp_WriteOutputData(FILE *fOutFile,
                               XDM_BufDesc * outputBufDesc,
                               IVIDDEC_OutArgs *outArgs);
@brief					       Compare Output with Corresponding Reference
@param  fOutFile[IN]           Reference File Handle
@param  outputBufDesc[IN]      Buffer Descriptor for output buffers
@param  outArgs[IN]            Info for args related to output buf(like numBytes)
@return					       NONE
********************************************************************************
*/
XDAS_Int32 TestApp_Compare_Ouput_and_Ref(FILE * fRefFile, XDAS_UInt32 offset,
        XDM_BufDesc * outputBufDesc, IVIDENC1_OutArgs * outArgs);

#endif                          //_TESTAPP_ENCODER_

/******************************************************************************/
/*    Copyright (c) 2006 Texas Instruments, Incorporated                      */
/*    All Rights Reserved                                                     */
/******************************************************************************/
