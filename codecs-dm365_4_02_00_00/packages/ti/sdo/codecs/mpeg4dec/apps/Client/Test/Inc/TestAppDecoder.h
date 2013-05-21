/******************************************************************************/
/*            Copyright (c) 2006 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/******************************************************************************/

/*!
********************************************************************************
  @file     TestAppDecoder.h
  @brief    This is the top level client header file that drives the H264
            (Baseline Profile) Video Decoder Call using XDM Interface
  @author   TI India
  @version  0.1 - May 11,2006    initial version
********************************************************************************
*/

#ifndef _TESTAPP_DECODER_
#define _TESTAPP_DECODER_

#include <stdio.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/ividdec2.h>

//#include "dec_params.h"

/* Macro definitions for constants and Buffer sizes*/
#define IMAGE_WIDTH         1280        //!< Width of the Display Buffer
#define IMAGE_HEIGHT        (960+64)    //!< Height of the Display Buffer


//#define DDR_START_ADDRESS 0x85A00000    // Boot MEM shall be set to 90 MB
#define AIM_START_ADDRESS 0x10000
//#define CODEC_RESERVED_SIZE 8192        //For statically initialized data used for DMA
#define OUTPUT_BUFFER_SIZE  (IMAGE_WIDTH*IMAGE_HEIGHT*2)        //!< Input Buf Size
//#define INPUT_BUFFER_SIZE   (0xE1000+0x800000+0x1600000+504*1024)
#define INPUT_BUFFER_SIZE   (4*1024*1024/*0x100000*/)
#define INTERNAL_DATA_MEM_SIZE    (0x1000)
/* list of some parameters macros for worst case memory allocation in external memory */
#define EXTERNAL_DATA_MEM_SIZE    (4*1024*1024)

#define STRING_SIZE         256 //!< Size of strings used for filenames
#define NUM_ALGS            1   //!< Number of Algorithms
#define SXVGA_YUV422       (1280*960*2)

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


/*!
********************************************************************************
  @fn									      XDAS_Int32 TestApp_ReadByteStream(FILE *finFile);
	@brief							      Reads Input Data from FILE
  @param  finFile[IN]       Input File Handle
  @param  inputBufDesc[IN]  Buffer Descriptor for input buffers
	@return							      Status of the operation ( PASS / FAIL )
********************************************************************************
*/
XDAS_Int32 TestApp_ReadByteStream(FILE * fInFile/*,XDAS_Int8 *inputData*/,int bytes ,int Size);

/*!
********************************************************************************
  @fn									      XDAS_Void TestApp_WriteOutputData(FILE *fOutFile, 
                                  XDM_BufDesc * outputBufDesc,  
                                  IVIDDEC_OutArgs *outArgs);
	@brief							      Writes Output Data into FILE
  @param  fOutFile[IN]      Output File Handle
  @param  outputBufDesc[IN] Buffer Descriptor for output buffers
  @param  outArgs[IN]       Info for args related to output buf(like numBytes)
	@return							      NONE
********************************************************************************
*/

XDAS_Void TestApp_WriteOutputData(FILE * fOutFile,
                                  XDM_BufDesc * outputBufDesc,
                                  IVIDDEC2_OutArgs * outArgs);

/*
********************************************************************************
  @fn									      XDAS_Int32 readparamfile(FILE * fname) ;
	@brief							      Parses codec specific parameter file and populates
                            configurable parameters
  @param  fname[IN]         parameter FILE handle
	@return							      NONE
********************************************************************************
*/
XDAS_Int32 readparamfile(FILE * fname,int baseParamsOnly );

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
XDAS_Int32 TestApp_Compare_Ouput_and_Ref(FILE * fOutFile,
                                  int lRefReadBytes,
                                  IVIDDEC2_OutArgs * outArgs);

#endif                         

/******************************************************************************/
/*    Copyright (c) 2006 Texas Instruments, Incorporated                      */
/*    All Rights Reserved                                                     */
/******************************************************************************/
