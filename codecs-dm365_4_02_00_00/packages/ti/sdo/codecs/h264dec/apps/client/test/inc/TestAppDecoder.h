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
* @file testappdecoder.h
*
* @path $(PROJDIR)\src
*
  @brief    This is the top level client header file that drives the H264
            Video Decoder Call using XDM Interface
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
#ifndef TESTAPP_H264D_DECODER_
#define TESTAPP_H264D_DECODER_
/***************************************************************
*  INCLUDE FILES
****************************************************************/
/* ----- system and platform files ----------------------------*/
/*-------program files ----------------------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------macros ----------------------------------------------*/
/* Maximum Width of the input image supported - used for
 * calculating display buffer size requirements in the test app */
#define IMAGE_WIDTH            1920
/* Maximu Height of the input image supported - used for calculating
 * the display buffer requirements in bytes  */
#define IMAGE_HEIGHT           1088
/* Maximu size of the input bit-stream array in bytes - used for
 * reading in input encoded data before passing it on to the decoder.
 * Please note that inptu buffer should be sufficiently big enough
 * to hold complete frame including multiple slices if any
 */
#define INPUT_BUFFER_SIZE      0x200000
//#define INPUT_BUFFER_SIZE      0x20000

/* Maximum string size used for complete path filenames */
#define STRING_SIZE            256

/*--------data declarations -----------------------------------*/
/*!
@struct sTokenMapping
@brief  Token Mapping structure for parsing codec specific configuration file
@param  tokenName : String name in the configuration file
@param  place     : Place Holder for the data
*/

typedef struct _sTokenMapping {
  xdc_Char *tokenName;
  XDAS_Void *place;
} sTokenMapping;
/*--------function prototypes ---------------------------------*/
/* Function Declarations */
/*****************************************************************************/
/**
*@func  TestApp_ReadByteStream()
*@brief  Sample utility function for reading encoded bit-stream in chunks.
*           The input file is opened every time and next
*           "INPUT_BUFFER_SIZE - validBytes" number of bytes is read into the
*           input buffer. End-of-file if encountered in previous runs is
*           remebered for given input config record.
*
*@param  XDAS_Int8 *inFile:
*           Input file name as a null-terminated array of characters.
*
*
*@return TotalBytes in the input bit-stream : If successfully read.
*        -1: If encountered error in reading the input file.
*
*@note   None
*/
/*****************************************************************************/
XDAS_Int32  TestApp_ReadByteStream(xdc_Char *inFile);

/*****************************************************************************/
/**
*@func  TestApp_WriteOutputData()
*@brief  Sample utility function for dumping encoded bit-stream. Before
*           writing raw YUV data packed and interleaved chroma data is
*           seperated into a seperate buffer.
*
*@param  FILE *fOutFile:
*           Output file pointer
*
*@param  XDAS_Int32 display_marker:
*           Index into the display buffer array which is marked for
*           display.
*
*@param  IVIDDEC2_OutArgs *outArgs:
*           OutArgs structure containing display buffer array and thier
*           properties like picture pitch, heigth and width.
*
*@param  XDAS_Int32  height:
*           Height of the displayed picture in pixels.
*
*@param  XDAS_Int32  width:
*           Width of the displayed picture in pixels.
*
*@return None.
*
*@note   None
*/
/*****************************************************************************/
XDAS_Void TestApp_WriteOutputData(FILE *fOutFile,
    XDAS_Int32 display_marker,
    IVIDDEC2_OutArgs *outArgs,
    XDAS_Int32  height,
    XDAS_Int32  width);


/*****************************************************************************/
/**
*@func  printStatus()
*@brief  Sample utility function for printing control command status
*
*
*@param  void *pvStatus,  XDAS_Int32 cmdId:
*           status pointer, control command ID
*
*@return void
*
*@note   None
*/
/*****************************************************************************/
void printStatus(void *pvStatus, XDAS_Int32 cmdId);


/*****************************************************************************/
/**
*@func  printOutArgs()
*@brief  Sample utility function for printing outArgs
*
*
*@param  void *poutArgs:
*           outArgs pointer.
*
*@return void
*
*@note   None
*/
/*****************************************************************************/
void printOutArgs(void *pvOutArgs);


/*****************************************************************************/
/**
*@func  printSEI_VUI_messages()
*@brief  Sample utility function for printing selected SEI messages
*
*
*@param  void *pSeiVui_obj:
*           SEI/VUI message pointer.
*
*@return void
*
*@note   None
*/
/*****************************************************************************/
void printSEI_VUI_messages(void *pSeiVui_obj);


/*****************************************************************************/
/**
*@func  TestApp_CompareOutputData()
*@brief  Sample utility function for comparing the raw decoded output with
*           reference output data.
*
*@param  FILE *fRefFile:
*           Reference file pointer.
*
*@param  IVIDDEC2_OutArgs *outArgs:
*               outArgs structure containing displayable frame.
*
*@return XDM_EFAIL : If comparision fails.
*        XDM_EOK: If comparision passes.
*
*@note   None
*/
/*****************************************************************************/
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
                                    XDAS_Int32 display_marker,
                                    IVIDDEC2_OutArgs *outArgs,
                                    XDAS_Int32  height,
                                    XDAS_Int32  width);

/*****************************************************************************/
/**
*@func  readparamfile
*@brief  Reads the entire param file contents into a global buffer - which is
*         used for parsing.
*
*@param  XDAS_Int8 *buf
*           buffer to be parsed
*
*@param FILE * fname
*           File pointer opened with the intended param file name
*
*@return 0 - if successfully parsed all the elements in param file and their
*           values read into the memory addresses given in token mapping array.
 *      -1 For any file read operation related errors or if unknown parameter
 *          names are entered or if the parameter file syntax is not in
 *          compliance with the below implementation.
*
*@note  Please refer to the user guide for intended syntax of the parameter
*           file -in the released sample code.
*/
/*****************************************************************************/
XDAS_Int32 readparamfile(FILE * fname) ;

#endif /* TESTAPP_H264D_DECODER_ */

/*!
*! Revision History
*! ================
*!
*! 31-May-2007 Vinay M K: Modified to comply with MMCodecs
*!                        coding guidelines.
*! 15-May-2007 Vinay M K: made changes to support XDM 1.0.
*! 05-Jan-2006 Dinesh Kumar: Created.
*/
