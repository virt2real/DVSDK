#ifndef TEST_RESET
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
* @file TestAppDecoder_ih264_arm926.c
*
* @path $(PROJDIR)\src
*
* @brief  This is the top level client file that drives the H264
*        (High Profile) Video Decoder Call using XDM v1.2 Interface
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
/***************************************************************
*  INCLUDE FILES
****************************************************************/
/* ----- system and platform files ----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/xdais/dm/ividdec2.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>

#include <ti/xdais/idma.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>

#ifdef ON_LINUX
/******************************************************************/
/* To get the overall profile numbers, enable the following macro */
/******************************************************************/
#define PROFILE_ONLINUX
/**********************************************************************/
/* To get the profile numbers for ARM 968, enable the following macro */
/* This needs modification on ARM 926 library source code as well.    */
/**********************************************************************/
//#define PROFILE_ONLINUX_ARM968
#endif


//#define PRINT_SEI_VUI_MSG
//#define PRINT_OUT_ARGS
//#define PRINT_BUFR_IDS
//#define PRINT_STATUS

#ifdef PROFILE_ONLINUX_ARM968
#include <sys/time.h>
int max_arm968_time = 0;
int avg_arm968_time = 0;
int com_arm968_time = 0;
extern int arm968_time;
#endif

#ifdef PROFILE_ONLINUX
#include <sys/time.h>
#endif


/*------- program files ----------------------------------------*/
/* H264 Interface header files */
#include <ih264vdec.h>
#include <ih264vdec_tii.h>
#include <h264vdec_tii.h>
#include "hdvicp_framework.h"
#include "buffermanager.h"
#include "testapp_arm926intc.h"
#include "TestAppDecoder.h"
//#include "h264vdec_ti_constant.h"
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/* This global variable is defined inside hdvicp_framework.c */
#ifndef ON_LINUX
extern volatile XDAS_UInt32 * poll_word;
#endif
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
IH264VDEC_Params             params;
IH264VDEC_DynamicParams      dynamicParams;

XDAS_UInt32                framesToDecode;
/* This global array of structure elements define the format of
 * config file being used. User needs to modify this array either
 * by adding new elements or by deleting existing elements in
 * correspondence to the changes required in parameters configuration
 * .cfg file
 */
sTokenMapping sTokenMap[] =
{
  {"FramesToDecode", &framesToDecode},
  {"ImageHeight",    &params.viddecParams.maxHeight},
  {"ImageWidth",     &params.viddecParams.maxWidth},
  {"ChromaFormat",   &params.viddecParams.forceChromaFormat},
  {"Closedloopflag",	&params.frame_closedloop_flag},
  {NULL,             NULL}
};

/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/

/*--------macros ----------------------------------------------*/

/***************************************************************************/
/* Ideally the H264_DPB_SIZE_PROFILE should be the memory required for the */
/* maximum reference buffers possible for a particular level including one */
/* buffer for decoding current picture. But as per implementation, buffer  */
/* includes field padding as well, that includes 48 more lines both on top */
/* and the bottom of the buffer, thereby increasing the memory requirement */
/***************************************************************************/
#define H264_DPB_SIZE_PROFILE_3_0  5000000
#define H264_DPB_SIZE_PROFILE_3_1 11500000
#define H264_DPB_SIZE_PROFILE_4_1 19000000
#define H264_DPB_SIZE_PROFILE_4_2 19000000

#ifdef PROFILE_ONLINUX
/* Extended params and Arguments */
#define EXTENDED_PARAMS_ARGS
#else
#ifdef PROFILE_ONLINUX_ARM968
/* Extended params and Arguments */
#define EXTENDED_PARAMS_ARGS
#else
/*************************************************/
/* Macro to enable Extended params and Arguments */
/*************************************************/
#define EXTENDED_PARAMS_ARGS
/*************************************************/
/*  Macro to enable Extended XDM 1.2 headerMode  */
/*************************************************/
//#define HEADER_DECODE_MODE
/*************************************************/
/* Macro to test dynamic loading of ARM 968 code */
/*************************************************/
//#define TOGGLE_ARM968_LOADING
/*************************************************/
/*  Macro to enable decoded YUV dump to a file.  */
/*************************************************/
#define ENABLE_FILE_OUTPUT
#endif
#endif


#define _ENABLE_IRES_EDMA3

/*******************************************************/
/*           Setting the default level to 4.2          */
/*******************************************************/
#define H264_DPB_SIZE_PROFILE	H264_DPB_SIZE_PROFILE_4_2

/* Additional debug printfs are controlled by defining this macro */
//#define _DBG_VERBOSE
//#define _DEBUG_LINUX

/* In H264 decoder; decode order of frames and display order can
 * be different. Especially in the case when B-frames are present
 * in the video stream; it is important that decoder delays display
 * of decoded frames suitably to maintain correct display order.
 * Initial "DISPLAY_DELAY" number of process calls would result in
 * no-output frames. DISPLAY_DELAY values are limited between 0
 * and 16 for H.264 standard. Display delay of 16 guarantees the
 * the correct display order for any stream, compliant to standard
 */
#define DISPLAY_DELAY            16


#define DEFAULT_DISPLAY_WIDTH	 0

/* Decoded picture buffer size is defined by the H.264 standard
 * as a look-up table indexed by the profile and level supported.
 * As per "ITU-T Rec.H.264, Advanced video coding for generic
 * audio-visual services:video Table A-1 Level limits" MAX DPB limit
 * for level 3 would be 3110400 bytes for 4:2:0 YUV output format.
 * At this DPB size we'll be able to support a max of 6 reference frames
 * A 24-pixels of padding on all the four sides of both LUMA and CHROMA
 * frames is intended as well.
 * Assuming PAL D1 with picture size of 720x576 & for 5
 * reference frames  + one output frame we need:
 * 720x576 at 25fps   = (720 + 48) * (576+48) *1.5 * 6 = 4313088 bytes
 * 576x720 at 25fps   = ((576+48) + 16) * (720 + 48) *1.5 * 6 = 4423680 bytes
 * additional 16 bytes for rotated picture due to making every row a multiple
 * of 32.
 * Assuming WVGA with picture size of 864x480 & for 5
 * reference frames  + one output frame we need:
 * 864x480 at 25fps  = ((864 + 48) + 16) * (480 + 48) * 1.5 * 6 = 4409856 bytes
 * 480x864 at 25fps  = ((480 + 48) + 16) * (864 + 48) * 1.5 * 6 = 4465152 bytes
 * We need Additional 16 bytes for making every row a multiple of 32.
 */
//#define H264_DPB_SIZE_PROFILE_3_0 4644864


/*--------data declarations -----------------------------------*/
#ifdef ON_LINUX
XDAS_Int8 *inputData;
/* Input buffer allocation INPUT_BUFFER_SIZE defined in TestAppDecoder.h */
#else
#ifdef __TMS470__
#pragma DATA_SECTION(inputData,      ".input_buffer")
#endif
XDAS_Int8 inputData[INPUT_BUFFER_SIZE];
#endif
/* This buffer holds the seperated out Cb Cr component - useful for dumping
 * the decoded output to a file stream - this array can be avoided if CbCr
 * need nto be seperated before writing the the outptu file
 * total size depends on the maximum picture size supported MAX width and
 * height  are defined in TestAppDecoder.h */
XDAS_Int8  Chroma_seperate[IMAGE_WIDTH*IMAGE_HEIGHT];

/* Temporary buffer used to compare decoded output with a reference file */
XDAS_Int8  refData[IMAGE_WIDTH*IMAGE_HEIGHT];

/*Stores the total bytes consumed by the decoder from the encoded input
 * bit-stream during previous process call. */
XDAS_UInt32 bytesConsumed = 0;
#ifdef LOW_LATENCY_FEATURE
XDAS_UInt32 nalPayloadBytesConsumed = 0;
#endif //LOW_LATENCY_FEATURE
/* Used as a boolean flag to indicate if the end-of-input-encoded bit-stream
 * file has been encountered.
 */
XDAS_UInt32 reachedEndOfFile;

/* Total number of valid Bytes still left over in the input bit-stream
 * buffer. This values is first initialised to the total bytes read from
 * the input file and it keeps getting decremented as the data is consumed
 * by every successive process call. It is also used to signal error in
 * reading the input file */
XDAS_Int32 validBytes;
#ifdef LOW_LATENCY_FEATURE
#define NUM_NALS_PER_CALBK 1
XDAS_Int32 g_nalStartCodeSize[IH264VDEC_TI_MAXNUMBLOCKS];
#endif //LOW_LATENCY_FEATURE
/* Offset in the input file from where next read happens */
XDAS_UInt32 fileOffset;

/* Defining the macro ENABLE_PROFILE_AT_FRM_LVL_ON_926 enables parts
 * of the code which is essential for profiling on ARM926 at Frame level
 * This macro is used in the present file and hdvicp_framework.c
 *
 * profileSrt: holds cycles consumed by start-porting of processign on
 *              ARM926 - its updated in hdvicp_framework.c
 * profileEd: holds cycles consumed for end-portion of the process call.
 * profile968: holds cycles taken by ARM968 part of the process call.
 */
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
XDAS_UInt32 profileSrt, profileEd, profile968;
#endif
int GlobalDbgFlag = 1;

/* Allocate CMEM structure and intialize it */
#ifdef ON_LINUX
CMEM_AllocParams memParams;
#endif

/*--------function definitions---------------------------------*/
/*===========================================================================*/
/*
 *@brief  This is the top level function which flushes  and invalidate Data
 *        cache of ARM926.
 *
 *@param  void *hdvicpHandle
 *        HDVICP handle address - initialised with default values by
 *        HDVICP_initHandle function
 *
 *@return None
 *
 *@note   None
 */
/*===========================================================================*/
#ifdef ON_LINUX
void Host_DCache_Flush(void *hdvicpHandle)
{
	return;
}
#endif
#ifdef LOW_LATENCY_FEATURE

xdc_Char inFile[STRING_SIZE];
XDAS_UInt32 nalSize[IH264VDEC_TI_MAXNUMBLOCKS];
/*****************************************************************************/
/**
*@func  findNalStartCode()
*@brief  Sample main program implementation which uses xDM v1.0 H264 
*        decoder's APIs to create a decoder instance and decode multiple
*       input files. It supports dumping of output decoded YUV data in 4:2:0
*       format or comparision fo decoded raw data with reference data. 
*       Uses single instance of the decoder and uses only base params for 
*       all input classes.
*
*       Uses buffer manager for XDM v1.0 compatible buffer management and 
*        uses utility functions for reading encoded bit-stream, 
*        Seperating CbCr components,
*        Comparing output data with reference data &
*        Dumping raw YUV data into a file in binary format.
*
*
*@param  none
*
*
*@return XDM_EOK : If successfully decoded all input streams/files
*
*@note   Always returns XDM_EOK - this return value is still retained since its
*         desirable to have integer return value for main program 
*           [Kernigham & Ritche]
*/
/*****************************************************************************/

XDAS_UInt32 gBytesRead;
XDAS_Int32 findNalStart(XDAS_UInt32 validBytesInBuffer, 
                        XDAS_UInt8 *nalStartAddrs[],
                        XDAS_UInt32 *nalLength,
                        XDAS_UInt8 streamFormat)
{
    XDAS_UInt8 *bufPtr = (XDAS_UInt8 *)inputData + bytesConsumed;
    XDAS_UInt32 startCode = 0;
    XDAS_Int32 numNalUnit = 0;
    XDAS_UInt8 nalStartCodeLength, bufIndexMoved;
    XDAS_UInt8 *endBufPtr = (XDAS_UInt8 *)inputData + gBytesRead;
    XDAS_UInt8 numNalsPerCallback = NUM_NALS_PER_CALBK;
    while (startCode != 0x000001)
    {
        startCode = (bufPtr[0] << 16) | (bufPtr[1] << 8) | bufPtr[2];
        bufPtr++;
        if (bufPtr >= endBufPtr)
        {
            printf("no valid NAL start code in this buffer\n");
            return -1;
        }
    }

    bufPtr += 2;

    if (*(bufPtr - 4) != 0)
    {
        nalStartCodeLength = 3;
    }
    else
    {
        nalStartCodeLength = 4;
    }
    do
    {
        if (streamFormat == IH264VDEC_TI_NALSTREAM)
        {
            nalStartAddrs[numNalUnit] = bufPtr;
            g_nalStartCodeSize[numNalUnit] = nalStartCodeLength;
        }
        else
        {
            nalStartAddrs[numNalUnit] = bufPtr - nalStartCodeLength;
        }

        startCode = 0;
        while (startCode != 0x000001)
        {
            startCode = (bufPtr[0] << 16) | (bufPtr[1] << 8) | bufPtr[2];
            bufPtr++;
            if (bufPtr > endBufPtr)
            {
                break;
            }
        }
        if (*(bufPtr - 2) != 0)
        {
            nalStartCodeLength = 3;
            bufIndexMoved = 1;
        }
        else
        {
            nalStartCodeLength = 4;
            bufIndexMoved = 2;
        }

        nalLength[numNalUnit] =
            (XDAS_UInt32) (bufPtr - nalStartAddrs[numNalUnit] - bufIndexMoved);

        bufPtr += 2;
        numNalUnit++;
        if (numNalUnit >= numNalsPerCallback)
        {
            break;
        }

    }while (bufPtr <= endBufPtr);
    return (numNalUnit);
}

/*****************************************************************************/
/**
*@func  dataSyncPutData()
*@brief  Sample main program implementation which uses xDM v1.0 H264 
*        decoder's APIs to create a decoder instance and decode multiple
*       input files. It supports dumping of output decoded YUV data in 4:2:0
*       format or comparision fo decoded raw data with reference data. 
*       Uses single instance of the decoder and uses only base params for 
*       all input classes.
*
*       Uses buffer manager for XDM v1.0 compatible buffer management and 
*        uses utility functions for reading encoded bit-stream, 
*        Seperating CbCr components,
*        Comparing output data with reference data &
*        Dumping raw YUV data into a file in binary format.
*
*
*@param  none
*
*
*@return XDM_EOK : If successfully decoded all input streams/files
*
*@note   Always returns XDM_EOK - this return value is still retained since its
*         desirable to have integer return value for main program 
*           [Kernigham & Ritche]
*/
/*****************************************************************************/
XDAS_Int32 dataSyncPutData(  
                           IH264VDEC_TI_DataSyncHandle dataSyncHandle, 
                           IH264VDEC_TI_DataSyncDesc * dataSyncDesc)
{
    XDAS_Int8 i, numNalUnits;
    XDAS_UInt8 *nalStartAddrs[IH264VDEC_TI_MAXNUMBLOCKS];

    for (i = 0; i < dataSyncDesc->numBlocks; i++)
    {
        bytesConsumed += dataSyncDesc->blockSizes[i];
		nalPayloadBytesConsumed += dataSyncDesc->blockSizes[i];
        validBytes = validBytes - dataSyncDesc->blockSizes[i];
        if (params.sliceFormat == IH264VDEC_TI_NALSTREAM)
        {
            bytesConsumed += g_nalStartCodeSize[i];
            validBytes -= g_nalStartCodeSize[i];
        }
    }

    validBytes = TestApp_ReadByteStream (inFile);
    numNalUnits =
        findNalStart (validBytes, nalStartAddrs, nalSize, params.sliceFormat);

    dataSyncDesc->numBlocks = numNalUnits;
    for (i = 0; i < numNalUnits; i++)
    {
        dataSyncDesc->baseAddr[i] = (XDAS_Int32 *) nalStartAddrs[i];
        dataSyncDesc->blockSizes[i] = nalSize[i];
    }

    /* Sometimes it is possible that decoder reports one byte 
    * extra consumption than what is available in the input 
    * bit-stream due to rounding off errors. validBytes == -1 
    * would trigger an input file read error condition. To 
    * avoid this faux-paus we re-initialsie validBytes variable 
    * to zero - which serves the purpose perfectly well.
    */
    if (validBytes < 0)
        validBytes = 0;

    return (XDM_EOK);
}
#endif //LOW_LATENCY_FEATURE

/*****************************************************************************/
/**
*@func  main()
*@brief  Sample main program implementation which uses xDM v1.0 H264
*        decoder's APIs to create a decoder instance and decode multiple
*       input files. It supports dumping of output decoded YUV data in 4:2:0
*       format or comparision fo decoded raw data with reference data.
*       Uses single instance of the decoder and uses only base params for
*       all input classes.
*
*       Uses buffer manager for XDM v1.0 compatible buffer management and
*        uses utility functions for reading encoded bit-stream,
*        Seperating CbCr components,
*        Comparing output data with reference data &
*        Dumping raw YUV data into a file in binary format.
*
*
*@param  none
*
*
*@return XDM_EOK : If successfully decoded all input streams/files
*
*@note   Always returns XDM_EOK - this return value is still retained since its
*         desirable to have integer return value for main program
*           [Kernigham & Ritche]
*/
/*****************************************************************************/
main ()
{

    /* File I/O variables */
    FILE *fConfigFile, *ftestFile, *fparamsFile;
#ifndef LOW_LATENCY_FEATURE
    xdc_Char line[STRING_SIZE], inFile[STRING_SIZE], testFile[STRING_SIZE];
#else //LOW_LATENCY_FEATURE
    xdc_Char line[STRING_SIZE], testFile[STRING_SIZE];
    XDAS_UInt32 prevBytesConsumed = 0;
#endif //LOW_LATENCY_FEATURE
    xdc_Char paramsFile[STRING_SIZE];
    XDAS_UInt32 testCompliance;
#ifdef ON_LINUX
//    XDAS_Int8 *fname = "./testvecs/config/testvecs_linux.cfg";
    XDAS_Int8 *fname = "../../test/testvecs/config/testvecs_linux.cfg";
#else
    xdc_Char *fname = "..\\..\\..\\Test\\TestVecs\\Config\\TestVecs.cfg";
#endif

    /* Base Class Structures */
    IH264VDEC_Status             status;
    IH264VDEC_InArgs             inArgs;
    IH264VDEC_OutArgs            outArgs;
	sSeiVuiParams_t SeiVui_obj;
    IRES_Status iresStatus;
    /* Algorithm specific handle */
    IALG_Handle handle = NULL;


    /* Input/Output Buffer Descriptors */
    XDM1_BufDesc inputBufDesc;
    XDM_BufDesc outputBufDesc;

    /* Handle to a buffer element allocated by the buffer manager module */
    BUFFMGR_buffEleHandle buffEle=NULL;

    /* Other variables */
    XDAS_Int32  decode_frameCount, retVal, testVal;
	XDAS_Int32  countConfigSet;
    /* inFlushModeFlag is a boolean flag which indicates the state
     * of the decoder instance - XDM_FLUSH or non-flush mode.
     * refer to user guide for details on XDM_FLUSH */
    XDAS_Int32  isReinitDone, inFlushModeFlag;
    XDAS_UInt32  ii;
    XDAS_Int8  *tmpInputBufPtr;
    XDAS_Int32 displayedFrameCount;
#ifdef HEADER_DECODE_MODE
    XDAS_Int32 decodeHeaderMode;
#endif
	XDAS_Int8 versionBuf[256];
	XDAS_Int8 userDataBuf0[512];
	XDAS_Int8 userDataBuf1[512];
/* Memory allocation params required in linux */
#ifdef ON_LINUX
	
    Sem_init();
    GT_init();
    Memory_init();
    Global_init();
    SemMP_init();
    LockMP_init();

#endif
#ifdef PROFILE_ONLINUX
    XDAS_UInt32 time_before_process, time_after_process;
	XDAS_UInt32 commulative_time = 0;
	XDAS_UInt32 max_time = 0;
	float average_time;
    struct timeval decoder_time, *decoder_timeptr;
    static unsigned int frame_count_p, total_time_p;
#endif
/* Memory allocation params required in linux */

#ifdef ENABLE_CACHE
    ARM926_Set_MMU_Base();
    ARM926_Set_Domains();
    ARM926_Enable_MMU();
    ARM926_Icache_Enable();
    ARM926_Flush_Icache();
    ARM926_Cache_Set_RoundRobin();
    ARM926_Dcache_Enable();
    ARM926_CleanFlush_Dcache();
#else
#ifndef ON_LINUX
    ARM926_Icache_Disable();
    ARM926_Dcache_Disable();
#endif
#endif
    /* Interrupt enable related function calls please refer to User
     * guide for a detailed description of these functions and the
     * DM365_IPC_INTC_ENABLE macro usage */
#ifdef DM365_IPC_INTC_ENABLE
        /* Call the functions to enable ARM926 FIQ and do some basic
         * setup to AINTC to accept KLD INTC (arm968) interupt in
         * FIQ pin of Arm926
         */
#ifndef ON_LINUX //dont init FIQ as it is already done
        ARM926_enable_FIQ();  /* SWI call to enable interrupts */
        ARM926_INTC_init();  /* Init AINTC */
#endif
#endif

#ifdef ON_LINUX
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_CACHED;
    memParams.alignment=256;
#endif
//	GT_init();
//	GT_create(&someGTMask, "ti.sdo.fc.rman.examples.dummyEdma3");
//	GT_set("*" "=01234567");

#ifdef ON_LINUX
    /* Initialization and allocation */
    CMEM_init();
    inputData = CMEM_alloc(INPUT_BUFFER_SIZE,&memParams);
#endif

#ifdef _ENABLE_IRES_EDMA3

    /*--------------------------------------------------------------------*/
    /* IRES related functions */
    /*--------------------------------------------------------------------*/
    iresStatus = (IRES_Status) RMAN_init();
    if (IRES_OK != iresStatus) {
        printf("RMAN initialization Failed \n");
        return -1;
    }
    {
    IRESMAN_Edma3ChanParams configParams;
    /*
     * Supply initialization information for the EDMA3 RESMAN while registering
     */
    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = sizeof(IRESMAN_Edma3ChanParams);

    /* Register the EDMA3CHAN protocol/resource manager with the
     * generic resource manager */

    iresStatus = (IRES_Status) RMAN_register(&IRESMAN_EDMA3CHAN,
                               (IRESMAN_Params *)&configParams);
    if (IRES_OK != iresStatus) {
        printf("EDMA3 Protocol Registration Failed \n");
        return -1;
    }
    }
    {
    IRESMAN_VicpParams configParams;
    /*
     * Supply initialization information for the RESMAN while registering
     */
    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = sizeof(IRESMAN_VicpParams);

    /* Register the VICP protocol/resource manager with the
     * generic resource manager */
   iresStatus = (IRES_Status)RMAN_register(&IRESMAN_VICP2,
                                            (IRESMAN_Params *)&configParams);

    if (IRES_OK != iresStatus) {
        printf("VICP Protocol Registration Failed \n");
        return -1;
    }
    }
    {
        IRESMAN_HdVicpParams configParams;
    /*
     * Supply initialization information for the RESMAN while registering
     */
    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = sizeof(IRESMAN_HdVicpParams);
    configParams.numResources = 1;
    /* Register the HDVICP protocol/resource manager with the
     * generic resource manager */
   iresStatus = (IRES_Status)RMAN_register(&IRESMAN_HDVICP,
                                            (IRESMAN_Params *)&configParams);

    if (IRES_OK != iresStatus) {
        printf("VICP Protocol Registration Failed \n");
        return -1;
    }
    }
#ifdef ON_LINUX
    {
        IRESMAN_AddrSpaceParams configParams;
    /*
     * Supply initialization information for the ADDRSPACE RESMAN while
     * registering */
    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = sizeof(IRESMAN_AddrSpaceParams);
    /* Register the HDVICP protocol/resource manager with the
     * generic resource manager */
    iresStatus = RMAN_register(&IRESMAN_ADDRSPACE,
            (IRESMAN_Params *)&configParams);

		if (IRES_OK != iresStatus)
		{
        printf("ADDRSPACE Protocol Registration Failed \n");
        return -1;
    }
    }
#endif
#endif

    /* Clear polling bit of ARM968; This is not required when Interrupt is
     * enabled between ARM926 and ARM968. But disablign needs corresponding
     * change in hdvicp_framework.c file When interrupt is enabled poll_word
     * points to a memory location in external memory. When interrupt is
     * disabled it points to a memory location in DTCM of ARM968 - as a way
     * of inter processor signaling.
     */
#ifndef ON_LINUX
    (*poll_word) = 0x0;
#endif

    /* Open Test Config File  */

    fConfigFile = fopen(fname,"r");

    if (!fConfigFile)
    {
        printf("Couldn't open parameter file %s",fname);
        return XDM_EFAIL;
    }

    /* Initialise configuration file count to one. This gets incremented
     * every time a new config file is read
     */
    countConfigSet = 1;

  /* Read the Config File until it reaches the end of file */
  while(!feof(fConfigFile))
  {
    handle = NULL;
	isReinitDone = 0;
    displayedFrameCount = 0;
    /* Read Compliance Checking parameter */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%d",&testCompliance);
        else break;
    /* Read Parameters file name */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%s",paramsFile);
        else break ;
    /* Read Input file name */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%s",inFile);
        else break ;
    /* Read Output/Reference file name */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%s",testFile);
        else break ;

#if 1//def _DBG_VERBOSE
    printf("\n*******************************************");
    printf("\nRead Configuration Set %d\n",countConfigSet);
    printf("%d\n", testCompliance);
    printf("Input file %s\n", inFile);
    printf("paramsFile file %s\n", paramsFile);
    printf("Test file %s\n", testFile);
    printf("\n*******************************************\n");
    fflush(stdout);
#endif
    countConfigSet++;

    /* Open Parameters file - read params and close the file */
    fparamsFile = fopen (paramsFile, "rb");
    if (!fparamsFile)
    {
      printf("\nCouldn't open Parameters file...   %s\n ",paramsFile);
      printf("Exiting for this configuration...\n");
      goto EndOfFile;
    }
    /* Read parameters defined by the user in sTokenMap array above. */
    if(readparamfile(fparamsFile) < 0)
    {
      printf("\nSyntax Error in %s\n ",paramsFile);
      printf("Exiting for this configuration...\n");
      fclose(fparamsFile);
      goto EndOfFile;
    }
    fclose(fparamsFile);
     /* Check if the configuration is set for reference coparison or
     * dumping of decoded YUV file. User guide details values for
     * testCompliance variable.
     * Output dump file or the test reference file is opened accordingly.
     */
    if(testCompliance)
    {
#ifdef _DBG_VERBOSE
        printf("\nRunning in Compliance Mode");
#endif
        ftestFile = fopen (testFile, "rb");
    }
    else
    {
#ifdef _DBG_VERBOSE
        printf("\nRunning in Output Dump Mode");
#endif
        ftestFile = fopen (testFile, "wb");
    }

    if( !ftestFile)
    {
      printf("Couldn't open Test File... %s",ftestFile);
      printf("\n Exiting for this configuration..." );
      goto EndOfFile;
    }
    /* Initialise the buffer manager with sufficient buffer size for output
     * and reference frames the value specified here is dependent on the
     * level supported */
    if(BUFFMGR_Init(H264_DPB_SIZE_PROFILE) == -1)
    {
      printf("Buffer manager failed not enuf memory to allocate\n");
      goto EndOfFile;
    }
    /*-------------------------------------------------------------------*/
    /* Initialization of parameters needed for Algorithm Instance create */
    /*-------------------------------------------------------------------*/
#ifdef EXTENDED_PARAMS_ARGS
    params.viddecParams.size     = sizeof(IH264VDEC_Params);
	dynamicParams.viddecDynamicParams.size = sizeof(IH264VDEC_DynamicParams);
#else
    params.viddecParams.size     = sizeof(IVIDDEC2_Params);
	dynamicParams.viddecDynamicParams.size = sizeof(IVIDDEC2_DynamicParams);
#endif

    /* Max Frame Rate: Not currently used in the algorithm */
    //params.viddecParams.maxFrameRate        = 30000;
    /* Max Bit Rate: Not currently used in the algorithm */
    params.viddecParams.maxBitRate          = 10485760;
    /* Data Endianness (Big:1, Little 16 bit:2, Little 32 bit:3) */
    params.viddecParams.dataEndianness      = XDM_BYTE;
	/* The only Chroma format supported is XDM_YUV_420SP */
	params.viddecParams.forceChromaFormat   = XDM_YUV_420SP;
    /* DMA initialization related calls - To initialise the structure with
     * exact DMA channels and number of EDMA param entries allocated for the
     * algorithms usage. This enables applciation to control the DMA
     * resource allocation to the algorithm. */
    //TestApp_SetDMAInitParams(&(params.dmaParams));
    /* Setting the display delay */
    params.displayDelay = DISPLAY_DELAY;
	//params.displayDelay = 0;
    /* Reset coprocessor flag enables the algorithm to save context from the
     * co-processor at the end of every frame decoding */
    //params.resetHDVICPeveryFrame = 0;
	/* Set the liit for the level */
	params.levelLimit = LEVEL_4_2;

    params.hdvicpHandle = (void*) NULL;

#ifdef LOW_LATENCY_FEATURE
    params.inputDataMode = IH264VDEC_TI_ENTIREFRAME;
    params.sliceFormat   = IH264VDEC_TI_BYTESTREAM;
#endif //LOW_LATENCY_FEATURE
    /*---------------- Decoder creation -----------------*/
		handle = (IALG_Handle)
				H264VDEC_create((IALG_Fxns*)&H264VDEC_TI_IH264VDEC,
								(IALG_Params*)&params);
		if (handle == NULL)
		{
		  printf( "\nFailed to Create Instance... \
					 Exiting for this configuration..");
			fflush(stdout);
      goto EndOfFile;
		}

#ifdef _ENABLE_IRES_EDMA3
		/*
        * Create an instance of an algorithm that implements IALG and IRES_Fxns
        */
		if (IRES_OK != RMAN_assignResources((IALG_Handle)handle,
											&H264VDEC_TI_IRES, /* IRES_Fxns */
											1 /* scratchId */)) {
		  printf( "\nFailed in assignign resources \
					 Exiting for this configuration..");
      goto EndOfFile;
		}
#endif

#ifdef EXTENDED_PARAMS_ARGS
        status.viddecStatus.size = sizeof(IH264VDEC_Status);
#else
        status.viddecStatus.size = sizeof(IVIDDEC2_Status);    
#endif
		status.viddecStatus.data.buf = versionBuf;
		status.viddecStatus.data.bufSize = sizeof(versionBuf);
        
	/*------Control call for ---- Get version number --------------*/
	H264VDEC_control(handle,
                     XDM_GETVERSION,
					 (IVIDDEC2_DynamicParams *) NULL,
                    (IVIDDEC2_Status *)&status);
	printf("\nLibrary Version: %s\n", status.viddecStatus.data.buf);

	printStatus(&status, XDM_GETVERSION);

	/*------Control call for ---- Set params --------------*/
	dynamicParams.viddecDynamicParams.displayWidth = DEFAULT_DISPLAY_WIDTH;
	dynamicParams.viddecDynamicParams.frameSkipMode = IVIDEO_NO_SKIP;
	dynamicParams.viddecDynamicParams.frameOrder = IVIDDEC2_DISPLAY_ORDER;
	/* Reset coprocessor flag enables the algorithm to save context from the
     * co-processor at the end of every frame decoding */
#ifdef PROFILE_ONLINUX
    dynamicParams.resetHDVICPeveryFrame = 1;
#else
	dynamicParams.resetHDVICPeveryFrame = 1;
#endif
#ifdef HEADER_DECODE_MODE
	dynamicParams.viddecDynamicParams.decodeHeader = XDM_PARSE_HEADER;
	decodeHeaderMode = 1;
#else
	dynamicParams.viddecDynamicParams.decodeHeader = XDM_DECODE_AU;
#endif


#ifdef LOW_LATENCY_FEATURE
    dynamicParams.getDataFxn     = dataSyncPutData;
    dynamicParams.dataSyncHandle = NULL;
#endif //LOW_LATENCY_FEATURE      
  
    H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);
	printStatus(&status, XDM_SETPARAMS);


    /*------Control call for ---- Get Buffer Sizes --------------*/
    H264VDEC_control(handle,
                     XDM_GETBUFINFO,
                    (IVIDDEC2_DynamicParams *) NULL,
                    (IVIDDEC2_Status *)&status);
	printStatus(&status, XDM_GETBUFINFO);
    /* Now allocated the various input/output buffer pointers to inbuf and
     *  outbuf. Set up temp pointer to the start of global input and output
     * buffer.
     */
    tmpInputBufPtr     = inputData;

    /* Fill up the input buffer values and pointers. Please note that at this
     * stage picture size is still unknown hence default picture size of PAL-D1
	 * is assumed internally by the control API. This default picture size is
     * used initialise minimum input and output buffer sizes.
     */
    inputBufDesc.numBufs     = status.viddecStatus.bufInfo.minNumInBufs ;
    for(ii=0; ii<(status.viddecStatus.bufInfo.minNumInBufs);ii++ )
    {
        inputBufDesc.descs[ii].buf = tmpInputBufPtr;
        tmpInputBufPtr += status.viddecStatus.bufInfo.minInBufSize[ii];
        inputBufDesc.descs[ii].bufSize = \
            status.viddecStatus.bufInfo.minInBufSize[ii];
    }


    /* Setting the sizes of Base Class Objects */
#ifdef EXTENDED_PARAMS_ARGS
    inArgs.viddecInArgs.size                  = sizeof(IH264VDEC_InArgs);
    outArgs.viddecOutArgs.size                 = sizeof(IH264VDEC_OutArgs);
#else
    inArgs.viddecInArgs.size                  = sizeof(IVIDDEC2_InArgs);
    outArgs.viddecOutArgs.size                 = sizeof(IVIDDEC2_OutArgs);
#endif
	/* doung initilaization of extended class objects */
	inArgs.seiVuiParseFlag = 1;
    /* Initialise the pointer values in the structure to indicate to the
     * decoder library whether that data element needs to b parsed and populated
     * or to be just skipped
     */
	SeiVui_obj.sei_messages.user_data_unregistered.user_data_payload_byte = \
        (XDAS_UInt8 *) userDataBuf0;
    SeiVui_obj.sei_messages.user_data_unregistered.buffer_size = \
        sizeof(userDataBuf0);
    SeiVui_obj.sei_messages.user_data_registered.itu_t_t35_payload_byte = \
        (XDAS_UInt8 *)userDataBuf1;
	SeiVui_obj.sei_messages.user_data_registered.buffer_size = \
        sizeof(userDataBuf1);
	inArgs.seiVuiBufferPtr = &(SeiVui_obj);

    /* Initializing one input file processign specific variables */
    /* Count for decded frames    */
    decode_frameCount             = 0;
    /* Resetting bytesGenerated variable */
    bytesConsumed = 0;
    reachedEndOfFile = FALSE;
    fileOffset = 0;
    validBytes = 0;
    inFlushModeFlag = FALSE;

	validBytes = TestApp_ReadByteStream(inFile);
    /*-------------------------------------------------------------------*/
    /* Do-While Loop for Decode Call  for a given stream */
    /*-------------------------------------------------------------------*/
#ifdef FLD_API
	outArgs.viddecOutArgs.outBufsInUseFlag=0;
#endif
#ifdef LOW_LATENCY_FEATURE
        outArgs.numBlocksConsumed = IH264VDEC_TI_MAXNUMBLOCKS;
#endif //LOW_LATENCY_FEATURE
    do
    {
#ifdef LOW_LATENCY_FEATURE
            XDAS_UInt8 *nalStartAddrs[IH264VDEC_TI_MAXNUMBLOCKS];
            XDAS_Int32 numNalUnits = IH264VDEC_TI_MAXNUMBLOCKS, i;
#endif //#ifdef LOW_LATENCY_FEATURE

#ifdef HEADER_DECODE_MODE
		if(decodeHeaderMode)
		{
			if((decode_frameCount == 0) ||
			   //(decode_frameCount == 1) ||
			   (decode_frameCount == 2) ||
			   //(decode_frameCount == 3) ||
			   (decode_frameCount == 4)
			   )
			{
				dynamicParams.viddecDynamicParams.decodeHeader = XDM_DECODE_AU;
			}
			else 
			{
				dynamicParams.viddecDynamicParams.decodeHeader = \
                    XDM_PARSE_HEADER;
			}
		}

	    H264VDEC_control(handle,
	                     XDM_SETPARAMS,
	                    (IVIDDEC2_DynamicParams *) &dynamicParams,
	                    (IVIDDEC2_Status *)&status);
		printStatus(&status, XDM_SETPARAMS);
#endif

        /* Read the bitstream in the Application Input Buffer. validBytes
         * would be initialised with the actual number of bytes read from the
         * input file */

#ifdef LOW_LATENCY_FEATURE
        if((params.inputDataMode == IH264VDEC_TI_SLICEMODE) && (validBytes > 0))
        {

            numNalUnits = findNalStart(validBytes,
                                       nalStartAddrs,
                                       nalSize,
                                       params.sliceFormat);
            inputBufDesc.numBufs = numNalUnits;
            for (i = 0; i < numNalUnits; i++)
            {
                inputBufDesc.descs[i].buf = (XDAS_Int8 *) nalStartAddrs[i];
                inArgs.pNumBytesInDesc[i] = nalSize[i];
            }
        }
#endif //LOW_LATENCY_FEATURE

        /* validBytes is also used to indicate error in reading the
         * input file*/
        if(validBytes == -1)
        {
            break;
        }

        /* Get a handle to the available buffer from the buffer manager.
         * buffEle would be NULL incase no buffer are free. buffEle is
         * used to initialise the output buffer descriptor structure for
         * next process call */
#ifdef FLD_API
		if(outArgs.viddecOutArgs.outBufsInUseFlag==0)
#endif
		if(inFlushModeFlag != TRUE)
		{
			buffEle = BUFFMGR_GetFreeBuffer();
		}
		else
		{
			buffEle->bufId = 0;
		}
        /*----------------------------------------------------------------*/
        /* Setting of input arguments */
        /*----------------------------------------------------------------*/
        /* Assign the number of bytes available, and point to
         * correct location in the input bufer for next process call
         */
		inArgs.viddecInArgs.numBytes        = validBytes;
#ifdef LOW_LATENCY_FEATURE
            if (params.inputDataMode == IH264VDEC_TI_ENTIREFRAME)
            {
            inputBufDesc.descs[0].buf   = inputData + bytesConsumed;         
            }
#else //LOW_LATENCY_FEATURE
        inputBufDesc.descs[0].buf   = inputData + bytesConsumed;
#endif //LOW_LATENCY_FEATURE


        inArgs.viddecInArgs.inputID = buffEle->bufId;
        /* Fill up the output buffer values and pointers - number of
         * output buffers are always set to two. One bufffer is for
         * Luma component and the other buffer for chroma component in
         * packed and interleaved format. Output is always in YUV 4:2:0
         * packed chroma format.
         */
        outputBufDesc.numBufs     = 2;
        outputBufDesc.bufSizes = (XDAS_Int32 *) buffEle->bufSize;
        outputBufDesc.bufs = (XDAS_Int8 **) buffEle->buf;
#ifdef _DBG_VERBOSE
        {
            printf("InBufId = %d, ", inArgs.viddecInArgs.inputID);
        }
#endif

        if(decode_frameCount == 0)
				printf("\n\nStarting Decode on ARM968...\n\n");

        /*---------------------------------------------------------*/
        /*   Configuring timer-0 to start counting                 */
        /*---------------------------------------------------------*/
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        profileInit(0);
        profileStart(0);
#endif
        /*------------------------------------------------------------------*/
        /* Start the process : To start decoding a frame                    */
        /* This will always follow a H264VDEC_decode_end call               */
        /*------------------------------------------------------------------*/
#ifdef PROFILE_ONLINUX
        decoder_timeptr = &decoder_time;
        time_before_process = gettimeofday(decoder_timeptr, NULL);
        time_before_process = decoder_timeptr->tv_usec;
#endif

#ifdef PRINT_BUFR_IDS
		printf("\nDecoding... with input ID %d\n", inArgs.viddecInArgs.inputID);
#endif
        retVal = H264VDEC_decode(handle,
                               (XDM1_BufDesc *)&inputBufDesc,
                               (XDM_BufDesc *)&outputBufDesc,
                               (IVIDDEC2_InArgs *)&inArgs,
                               (IVIDDEC2_OutArgs *)&outArgs);

#ifdef PROFILE_ONLINUX
        time_after_process = gettimeofday(decoder_timeptr, NULL);
	    if(decoder_timeptr->tv_usec <= time_before_process)
	    {

	    	decoder_timeptr->tv_usec += 1000000;
	    }

	    /* Print the time in micro-second for current frame, Commulative time */
	    /* and the average up to the current decoded frame */
		commulative_time += (decoder_timeptr->tv_usec - time_before_process);
		average_time = (float)commulative_time/(decode_frameCount + 1);
		if((max_time < (decoder_timeptr->tv_usec - time_before_process)))
			max_time = decoder_timeptr->tv_usec - time_before_process;

	    printf("FRAME LEVEL DECODE TIME = %d, C %d, A %f, M %d\n",
			(decoder_timeptr->tv_usec - time_before_process),
            commulative_time, average_time, max_time);
#endif

#ifdef PROFILE_ONLINUX_ARM968
		com_arm968_time += arm968_time;
		avg_arm968_time = com_arm968_time/(decode_frameCount + 1);
		if(max_arm968_time < arm968_time)
			max_arm968_time = arm968_time;
		printf("ARM968 FRAME DECODE TIME = C %d, A %d, M %d\n",arm968_time,
            avg_arm968_time, max_arm968_time);
#endif



#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        profileEd = profileEnd(0);
        printf("Start = %d; End = %d; On 968 = %d\n",
                    profileSrt, profileEd, profile968);
#endif


#ifdef HEADER_DECODE_MODE

		/* Check if process call with decode Header mode returned XDM_EOK */
		if((decodeHeaderMode == 1) && (retVal == XDM_EOK))
		{
			/*------Control call for ---- Set params --------------*/
			/* Keep all other params constant, toggle only decodeHeader */
			if(dynamicParams.viddecDynamicParams.decodeHeader == XDM_DECODE_AU)
			{
				decodeHeaderMode = 1;
			}
			else
			{
				dynamicParams.viddecDynamicParams.decodeHeader = XDM_DECODE_AU;
				decodeHeaderMode = 0;
			}

			H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);
			printStatus(&status, XDM_SETPARAMS);
		}
		else if((decodeHeaderMode == 0) && (retVal == XDM_EOK))
		{
			/*------Control call for ---- Set params --------------*/
			/* Keep all other params constant, toggle only decodeHeader */
			dynamicParams.viddecDynamicParams.decodeHeader = XDM_PARSE_HEADER;
			decodeHeaderMode = 1;

			H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);
			printStatus(&status, XDM_SETPARAMS);
		}
#endif


#ifdef PRINT_BUFR_IDS
		{
			unsigned int count;
			for(count = 0; count < 20; count++)
			{
				if(outArgs.viddecOutArgs.outputID[count] == 0)
					break;
				printf("Displaying... with outut ID %d\n", \
                    outArgs.viddecOutArgs.outputID[count]);
			}

			for(count = 0; count < 20; count++)
			{
				if(outArgs.viddecOutArgs.freeBufID[count] == 0)
					break;
				printf("Freeing... with Buf ID %d\n", \
                    outArgs.viddecOutArgs.freeBufID[count]);
			}
		}
#endif

#ifdef PRINT_OUT_ARGS
		printOutArgs(&outArgs);
#endif


        /*------------------------------------------------------------------*/
        /* Get status control call enables the user to get the exact picture*/
        /* size in terms of pixel height and width                          */
        /*------------------------------------------------------------------*/
        H264VDEC_control(handle, XDM_GETSTATUS,
                        (IVIDDEC2_DynamicParams *) NULL,
                        (IVIDDEC2_Status *)&status);
		printStatus(&status, XDM_GETSTATUS);
        if(status.viddecStatus.extendedError)
        {
           printf("Error code [Control Frame] %x \n", \
            status.viddecStatus.extendedError);
        }


         /* Check for return value of the process call. Please note
         * that when the decoder instance is in XDM_FLUSH mode
         * end-of-decode i.e emptying of picture buffer of all the
         * previously decoded frames is indicated by returning error.
         * hence if the process call returns error all we need to do
         * is break out of the do-while loop if inFlushModeFlag is TRUE
         */

        if(retVal == XDM_EFAIL && 
            ((XDM_ISFATALERROR(status.viddecStatus.extendedError) == 0x1))
            &&(FALSE == inFlushModeFlag)) //start of frame error
        {
            printf("Terminating execution due to critical error (0x%x) at: %d \
                    , Flushing out remaining frames. \n", \
                    status.viddecStatus.extendedError, \
                    decode_frameCount);

            if(decode_frameCount > displayedFrameCount) {
                /*-------------------------------------------------------*/
                /* Call FLUSH command to set the flush mode for decoder  */
                /* This is required to flush out left over displayable   */
                /*   frames in DPB                                       */
                /*-------------------------------------------------------*/

                H264VDEC_control(handle, XDM_FLUSH, NULL,
                    (IVIDDEC2_Status *) &status);
				printStatus(&status, XDM_FLUSH);

                /* Set the flush mode flag to ON condition -
                 * this flag will help us exit out of the while loop
                 * process return error.
                 */
                inFlushModeFlag = TRUE;
                /* Dont read any more bytes from the input file */
                reachedEndOfFile = TRUE;
                /* Buffer manager would allocate free buffer elements through
                 * BUFFMGR_GetFreeBuffer API.
                 */

                 BUFFMGR_ReleaseBuffer(
                                (XDAS_UInt32 *)outArgs.viddecOutArgs.freeBufID);
                continue;
            }
            else
            {
                break; /* Error Condition: Application may want to break off */
            }
        }

        if(FALSE == inFlushModeFlag)
        {
#ifdef LOW_LATENCY_FEATURE
            if (params.inputDataMode == IH264VDEC_TI_SLICEMODE)
            {
                for (i = 0; i < outArgs.numBlocksConsumed; i++)
                {
                    bytesConsumed += nalSize[i];
                    /*  Incase of NAL stream it is without nal header. In  */
                    /* Bytes stream payload with headers                   */
                    nalPayloadBytesConsumed += nalSize[i];
                    validBytes = validBytes - nalSize[i];
                    if (params.sliceFormat == IH264VDEC_TI_NALSTREAM)
                    {
                        bytesConsumed += g_nalStartCodeSize[i];
                        validBytes -= g_nalStartCodeSize[i];
                    }
                }

                if((nalPayloadBytesConsumed - prevBytesConsumed) != \
                    outArgs.viddecOutArgs.bytesConsumed)
                {
                    printf("bytesConsumed returned incorrect value\n");
                    printf("returned value = %d, consumed value = %d\n", \
                        outArgs.viddecOutArgs.bytesConsumed, 
                        (bytesConsumed - prevBytesConsumed));
                }
                prevBytesConsumed = nalPayloadBytesConsumed;
            }         
            else
            {
                bytesConsumed += outArgs.viddecOutArgs.bytesConsumed;            
                validBytes = validBytes -  outArgs.viddecOutArgs.bytesConsumed;
            }                       
#else //LOW_LATENCY_FEATURE
            /* If not then update the variables managing the input encoded
             * bit-stream buffer
             */
            bytesConsumed += outArgs.viddecOutArgs.bytesConsumed;
            validBytes = validBytes -  outArgs.viddecOutArgs.bytesConsumed;
#endif //LOW_LATENCY_FEATURE            
            /* Sometimes it is possible that decoder reports one byte
             * extra consumption than what is available in the input
             * bit-stream due to rounding off errors. validBytes == -1
             * would trigger an input file read error condition. To
             * avoid this faux-paus we re-initialsie validBytes variable
             * to zero - which serves the purpose perfectly well.
             */
            if(validBytes < 0)
				validBytes = 0;

#ifndef PROFILE_ONLINUX
            /* Print-out decoded frame number, consumed bytes by the
             * just concluded process call and left over valid bytes
             * in the input bit-stream buffer
             */
            printf("Decoded Frm#:%d | \t BytesConsumed:%d | \t LeftBytes:%d\n",
                    decode_frameCount,
                    outArgs.viddecOutArgs.bytesConsumed,
                    validBytes);
            fflush(stdout);
#endif
		}


		/* If the library has decoded the frame data */
		if((outArgs.viddecOutArgs.decodedBufs.numBufs == 2) &&
			(outArgs.viddecOutArgs.outBufsInUseFlag == 0))
		{
			decode_frameCount++;
		}



		/* Buffer manager would allocate free buffer elements through
         * BUFFMGR_GetFreeBuffer API. These buffers are used and owned
         * by the alorithm until it explicitly releases them by way of
         * mentionign thier buffer Ids in freeBufId array of outArgs
         * parameter. So release bufffers needs to be returned back
         * to the buffer manager. It is perfectly possible to have
         * zero or more buffers to be freed by the algorithm in one
         * process call.
         */

         BUFFMGR_ReleaseBuffer((XDAS_UInt32 *)outArgs.viddecOutArgs.freeBufID);


        /* After first frame decoded - get the actual
         * frame sizes required and use this information to
         * re-distribute buffers. Since the exact picture size
         * is unknown until the first successful process call we
         * cannot complete buffermanager initialisation at one go.
         * Call GETBUFINFO control call on the decoder instance for
         * the very first time after a successful process call is made
         * to know the exact luma and chroma buffer requirements -
         * these buffer requirements would include frame level padding
         * and 32-byte multiple width requirements on the picture frame as
         * well.
         */
		if((isReinitDone == 0) && (outArgs.viddecOutArgs.outBufsInUseFlag == 0))
		{
			/* Check if any the first alocated buffer is still free */
			if(NULL == BUFFMGR_QueryFreeBuffer())
			{
				//printf("\n BUFFMGR_QueryFreeBuffer: No free buffer\n");
				/* Get the exact luma and chroma buffer requirements for the
				 * YUV piture buffers, given input bit-stream. */
				H264VDEC_control(handle, XDM_GETBUFINFO, NULL, \
                    (IVIDDEC2_Status *) &status);
				printStatus(&status, XDM_GETBUFINFO);
				/* Use the above exact luma and chroma buffer reuqirements
				 * for the input bit-stream to re-initialise the buffer manager.
				 * refer to buffermanager specific XDM 1.2 intergation doc
				 * for more details.				 */
				BUFFMGR_ReInit(status.viddecStatus.bufInfo.minOutBufSize[0],
							   status.viddecStatus.bufInfo.minOutBufSize[1]);

				isReinitDone = 1;
			}

		}


#ifdef TOGGLE_ARM968_LOADING

			/*------Control call for ---- Set params --------------*/
			/* Keep all other params constant, 
             * toggle only resetHDVICPeveryFrame */
			dynamicParams.resetHDVICPeveryFrame = \
                1 - dynamicParams.resetHDVICPeveryFrame;

			H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);
			printStatus(&status, XDM_SETPARAMS);
#endif

        /* Check if the decoder instance is in XDM_FLUSH mode */
        if(FALSE == inFlushModeFlag)
        {


#ifdef PRINT_SEI_VUI_MSG
			if(inArgs.seiVuiParseFlag == 1)
			{
				printSEI_VUI_messages((void *)outArgs.seiVuiBufferPtr);
			}
#endif
            if(outArgs.viddecOutArgs.decodedBufs.extendedError)
            {
                printf("Error code [Decoded Frame %d] %x \
                        Erroneous Mbs in curr frame: %d\n", \
                        decode_frameCount,
                        outArgs.viddecOutArgs.decodedBufs.extendedError,
                        outArgs.numErrMbs);
            }
        }

        /*-------------------------------------------*/
        /* Dump the Output in file                    */
        /*-------------------------------------------*/
        /* Check for frame ready via outputId array. 0 is not a
         * valid buffer Id hence if the first entry in the output
         * Id array is zero then we donot have any buffers for display
         * Please note that in this implementation we are assuming just
         * one display buffer to be populated per call. Ideally we need
         * to check all elements in outputId array until its value
         * becomes zero - the corresponding entries in displaybufs
         * would give the display buffer pointers .
         */

		if(outArgs.viddecOutArgs.outputID[0] != 0)
        {
            ii = 0;
            while(outArgs.viddecOutArgs.outputID[ii] != 0)
            {
                if(testCompliance)
                {
                    /* Compare the output frames with the Reference File */
                    testVal = TestApp_CompareOutputData(ftestFile,
                                ii,
                                (IVIDDEC2_OutArgs *)&outArgs,
                                status.viddecStatus.outputHeight,
                                status.viddecStatus.outputWidth);

                    if(testVal != XDM_EOK) {
#ifdef _DBG_VERBOSE
                         printf("Breaking at: %d \n", displayedFrameCount);
#endif
                        /* Test Compliance Failed... Breaking...*/
                         goto EndOfFile1;
                    }
#ifdef _DBG_VERBOSE
                    printf("Verified ");
#endif
                }
                else
                {
#ifdef ENABLE_FILE_OUTPUT

					printf("\n Writing display buffer to file\n");
                    /* Write the output frames in the display order */
                    /* display_marker(2nd arg) is i for normal decode calls */
                    TestApp_WriteOutputData(ftestFile,
                                             ii,
                                             (IVIDDEC2_OutArgs *)&outArgs,
                                             status.viddecStatus.outputHeight,
                                             status.viddecStatus.outputWidth);
#endif
#ifdef _DBG_VERBOSE
                    printf("Dumped ");fflush(stdout);
#endif
                }
#ifdef _DBG_VERBOSE
                /* Print-out displayed/verified frame number
                 */
                printf("Displayed Frm#:%d \n ", displayedFrameCount);
				fflush(stdout);
#endif
                if(outArgs.viddecOutArgs.displayBufs[ii].extendedError)
                    printf("Error code [Display Frame %d] %x \n",
                          displayedFrameCount,
                          outArgs.viddecOutArgs.displayBufs[ii].extendedError);
                ii++;
                displayedFrameCount++;
            }
			printf("\n");
        }
        else if(TRUE == inFlushModeFlag)
        {
            /* If outpuId is zero - it either indicates that there are no
             * frames to display at this point of time or bit-stream has
             * been ended - In order to distinguish between these two
             * conditions inFlushModeFlag is used.
             * Infact this condition should not occur since process call
             * is expected to return XDM_EFAIL when decode end is
             * encountered. Please refer to user guide for mdoe details.
             */
             break;
        }

        /* Check if the input-bitstream has ended or if user specified
         * number of frames are already decoded - in either case we need
         * to stop decoding
         * A Minimum of 5 bytes has to be present in the encoded bit-stream
         * [4 for start code prefix and one for NAL header] before we go ahead
         * further decoding - else its concluded that input-bit-stream buffer
         * has ended.
         */

		 validBytes = TestApp_ReadByteStream(inFile);

        if (((validBytes < 4) ||
             (decode_frameCount >= framesToDecode)) &&
            (FALSE == inFlushModeFlag))
        {
#ifdef _DBG_VERBOSE
            printf("\n Bitstream Ended. or  ");
            printf("\n Specified number of Frames Decoded...\n  ");
            printf("\n Flushing out Displayable frames from DPB...\n  ");
#endif
            /*
             * Please note that decode end and input bit-stream end
             * are not always same. A non-zero DISPLAY_DELAY would
             * mean that decoder instance woudl contain DISPLAY_DELAY
             * number of frames yet to be displayed even after encoded
             * input bit-stream has ended. This facilitated by
             * explictly instructing the decoder instance to enter
             * XDM_FLUSH mode by the following control function call.
             */
            /*-------------------------------------------------------*/
            /* Call FLUSH command to set the flush mode for decoder     */
            /* This is required to flush out left over displayable   */
            /*   frames in DPB                                       */
            /*-------------------------------------------------------*/
            				printf("\nFlush Called\n");
            H264VDEC_control(handle, XDM_FLUSH, NULL, (IVIDDEC2_Status *) &status);
			printStatus(&status, XDM_FLUSH);

            /* Set the flush mode flag to ON condition -
             * this flag will help us exit out of the while loop
             * process return error.
             */
            inFlushModeFlag = TRUE;
        }
    }  while(1);  /* end of Do-While loop - which decodes frames */
EndOfFile1:

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle),
                                        &H264VDEC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
        printf("Free Resource Failed \n");
        //return -1;
    }
#endif
EndOfFile:
    /* Delete the Algorithm instance object specified by handle */
    if(handle)
        ALG_delete (handle);

    /* Output file close */
    if(ftestFile)
        fclose(ftestFile);

    /* To avoid division with zero */
    if(decode_frameCount == 0)
            decode_frameCount = 1;

    printf("\n --------------  SUMMARY --------------------\n");
    printf("End Input file %s\n", inFile);

    if(!testCompliance)
        printf(" Decoder output dump completed\n");
    else
    {
        if(testVal == 0 && decode_frameCount > 0)
            printf(" Compliance test pass.\n");
        else
            printf(" Compliance test FAIL.\n");
    }

    printf("\t Total number of Frames              = %d\n",
                (XDAS_UInt32)decode_frameCount);

   /* fileOffset indicates total encoded bit-stream length in bytes
    * fileOffset*8*30 indicates total encoded bits for 30-frames
    */
    printf("\t Bit Rate at 30 frames/Sec           = %d Kbps\n",
      (XDAS_UInt32)(((fileOffset*8*30)/decode_frameCount)/1000));
    printf("\t Width and Height                    = %d, %d \n", \
      (XDAS_UInt32)status.viddecStatus.outputWidth, \
      (XDAS_UInt32)status.viddecStatus.outputHeight);
    printf (" --------------    END   --------------------\n");

    BUFFMGR_DeInit();
  } /* Read the Config File until it reaches the end of file */

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&IRESMAN_EDMA3CHAN)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }
    if (IRES_OK != RMAN_unregister(&IRESMAN_VICP2)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }
    if (IRES_OK != RMAN_unregister(&IRESMAN_HDVICP)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }
#ifdef ON_LINUX
	if(IRES_OK != RMAN_unregister(&IRESMAN_ADDRSPACE)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }
#endif
    RMAN_exit();
#endif

  /*------------------------------------------------------------------------*/
  /* Signal ARM968 to terminate wait and goto sleep                         */
  /*------------------------------------------------------------------------*/
#ifndef ON_LINUX
  (*poll_word) = 0xFFFFFFFF;
#endif
#ifdef ON_LINUX
    /* De-Initialization */
    CMEM_free(inputData, &memParams);
#endif
#ifdef _DBG_VERBOSE
  printf("\n End of execution\n");fflush(stdout);
#endif
  /* Close the config files */
  if(fConfigFile != NULL)
  fclose(fConfigFile);
  return XDM_EOK;
} /* main() */

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
XDAS_Int32 TestApp_ReadByteStream(xdc_Char *inFile)
{
    XDAS_UInt32 BytesRead, BufferSize, Index;
    FILE  *finFile;

    /* If end-of-file had already been encountered for this config
     * record, then just return the remainign bytes in the input
     * bit-stream.
     */
    if(TRUE == reachedEndOfFile)
        return validBytes;

    /* Open input file */
    finFile = fopen (inFile, "rb");
    if (!finFile)
    {
        printf("\n Couldn't open Input file...  %s  ",inFile);
        printf("\n Exiting for this configuration...");
        return -1;
    }
    /* Seek to the exact location in the input file from where previous
     * read had left over
     */
    fseek (finFile, fileOffset, SEEK_SET);


    /* Shift data from lower-half to upper part */
    for(Index = 0; Index < validBytes; Index++)
        inputData[Index] = inputData[bytesConsumed + Index];

    /*Read the "BufferSize" number of bytes in the input buffer*/
    bytesConsumed = 0;
    BufferSize = INPUT_BUFFER_SIZE - validBytes;
    BytesRead = fread (&inputData[validBytes], 1, BufferSize, finFile);
#ifdef LOW_LATENCY_FEATURE
    gBytesRead = BytesRead;
#endif //LOW_LATENCY_FEATURE

    /* Store the exact pointer in the input file for next read.
     * fileOffset is also used to keep track of total file size
     * processed at any given instant. Its used to calculate the
     * bit-rate of the input file as well at the end of decoding */
    fileOffset = ftell(finFile);
    fclose(finFile);

    /* Determine end-of-file condition */
    if (BytesRead != BufferSize)
    {
        reachedEndOfFile = TRUE;
    }

    /* Return total bytes available for further decoding */
    return (validBytes + BytesRead);
}




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
void printStatus(void *pvStatus, XDAS_Int32 cmdId)
{
#ifdef PRINT_STATUS

    IH264VDEC_Status *h264status = (IH264VDEC_Status *)pvStatus;
    IVIDDEC2_Status *status = &h264status->viddecStatus;
	XDAS_Int32 count, numBufCnt;

	switch(cmdId)
	{
		case XDM_GETVERSION:
			printf("\nDetails for XDM_GETVERSION:\n");
			printf("Status size           = %d\n", status->size);
			printf("Status Extended error = %d\n", status->extendedError);
			if(status->data.buf)
				printf("\nVersion: %s\n", status->data.buf);
			break;

		case XDM_SETDEFAULT:
			printf("\nDetails for XDM_SETDEFAULT:\n");
		case XDM_SETPARAMS:
			printf("\nDetails for XDM_SETPARAMS:\n");
		case XDM_FLUSH:
			printf("\nDetails for XDM_FLUSH:\n");
			printf("Status size           = %d\n", status->size);
			printf("Status Extended error = %d\n", status->extendedError);
			break;

		case XDM_GETBUFINFO:
			printf("\nDetails for XDM_GETBUFINFO:\n");
			printf("Status size           = %d\n", status->size);
			printf("Status Extended error = %d\n", status->extendedError);
			printf("\nMin Input Buffers      = %d\n", \
                status->bufInfo.minNumInBufs);
			for(count = 0; count < status->bufInfo.minNumInBufs; count++)
			{
				printf("Input Buf[%d] size = %d\n",
					count, status->bufInfo.minInBufSize[count]);
			}
			printf("Min Output Buffers   = %d\n", \
                status->bufInfo.minNumOutBufs);
			printf("Max Display Buffers   = %d\n", status->maxNumDisplayBufs);
			for(count = 0; count < status->maxNumDisplayBufs; count++)
			{
				printf("\nDisplay Buf[%d]:\n", count);
				for(numBufCnt = 0;
                    numBufCnt < status->bufInfo.minNumOutBufs;
                    numBufCnt++)
				{
					printf("Buf%d size = %d ", numBufCnt, \
                        status->bufInfo.minOutBufSize[numBufCnt]);
				}
			}
			printf("\n");
			return;


		case XDM_GETSTATUS:
			printf("\nDetails for XDM_GETSTATUS:\n");
			printf("Status size           = %d\n", status->size);
			printf("Status Extended error = %d\n", status->extendedError);
			printf("\nOutput Height       = %d\n", status->outputHeight);
			printf("\nOutput Width        = %d\n", status->outputWidth);
			printf("\nMax Display Buffers = %d\n", status->maxNumDisplayBufs);
			printf("\nBit Rate            = %d\n", status->bitRate);
			printf("\nFrame Rate          = %d\n", status->frameRate);
			printf("\nContent Type        = %d\n", status->contentType);
			printf("\nChroma Format       = %d\n", status->outputChromaFormat);
#ifdef EXTENDED_PARAMS_ARGS            
            printf("\nFrameType           = %d\n", h264status->frameType);
            printf("\nFirst MB in Slice   = %d\n", h264status->firstMBinSlc);
            printf("\nFrmNum in SliceHdr  = %d\n", h264status->frmNuminSlcHdr);
#endif            
			break;

	}
#endif
}


/*****************************************************************************/
/**
*@func  printOutArgs()
*@brief  Sample utility function for printing outArgs
*
*
*@param  IH264VDEC_OutArgs *poutArgs:
*           outArgs pointer.
*
*@return void
*
*@note   None
*/
/*****************************************************************************/
void printOutArgs(void *pvOutArgs)
{
	IH264VDEC_OutArgs *outArgs = (IH264VDEC_OutArgs *)pvOutArgs;
    XDAS_UInt32 outcount, bufCount;

	printf("OutArgs size = %d\n", outArgs->viddecOutArgs.size);
	printf("Bytes consumed = %d\n", outArgs->viddecOutArgs.bytesConsumed);
	printf("Out Buffer in use flag = %d\n", \
        outArgs->viddecOutArgs.outBufsInUseFlag);

	/* Decoded Buffer details */
	printf("Decoded Buffer numBufs = %d\n", outArgs->viddecOutArgs.decodedBufs.numBufs);
	if(outArgs->viddecOutArgs.decodedBufs.numBufs)
	{
		printf("Decoded Buffer frameWidth           = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.frameWidth);
		printf("Decoded Buffer frameHeight          = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.frameHeight);
		printf("Decoded Buffer framePitch           = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.framePitch);
		printf("Decoded Buffer extendedError        = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.extendedError);
		printf("Decoded Buffer frameType            = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.frameType);
		printf("Decoded Buffer topFieldFirstFlag    = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.topFieldFirstFlag);
		printf("Decoded Buffer repeatFirstFieldFlag = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.repeatFirstFieldFlag);
		printf("Decoded Buffer frameStatus          = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.frameStatus);
		printf("Decoded Buffer repeatFrame          = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.repeatFrame);
		printf("Decoded Buffer contentType          = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.contentType);
		printf("Decoded Buffer chromaFormat         = %d\n", \
            outArgs->viddecOutArgs.decodedBufs.chromaFormat);

		for(bufCount = 0;
            bufCount < outArgs->viddecOutArgs.decodedBufs.numBufs;
            bufCount++)
		{
			printf("Decoded Buffer Buf[%d] Address = 0x%X\n", \
                bufCount, \
                outArgs->viddecOutArgs.decodedBufs.bufDesc[bufCount].buf);
			printf("Decoded Buffer Buf[%d] Size = 0x%X\n", \
                bufCount, \
                outArgs->viddecOutArgs.decodedBufs.bufDesc[bufCount].bufSize);
			printf("Decoded Buffer Buf[%d] Access Mask = 0x%X\n", \
                bufCount, \
                outArgs->viddecOutArgs.decodedBufs.\
                bufDesc[bufCount].accessMask);
		}
	}

	/* Display Buffer details */
	for(outcount = 0;
        outArgs->viddecOutArgs.outputID[outcount] != 0;
        outcount++)
	{
		printf("Display Buffer %d: Output ID %d numBufs = %d:\n",
			outcount, outArgs->viddecOutArgs.outputID[outcount],
			outArgs->viddecOutArgs.displayBufs[outcount].numBufs);

		if(outArgs->viddecOutArgs.displayBufs[outcount].numBufs)
		{
			printf("frameWidth           = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].frameWidth);
			printf("frameHeight          = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].frameHeight);
			printf("framePitch           = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].framePitch);
			printf("extendedError        = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].extendedError);
			printf("frameType            = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].frameType);
			printf("topFieldFirstFlag    = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].topFieldFirstFlag);
			printf("repeatFirstFieldFlag = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].repeatFirstFieldFlag);
			printf("frameStatus          = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].frameStatus);
			printf("repeatFrame          = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].repeatFrame);
			printf("contentType          = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].contentType);
			printf("chromaFormat         = %d\n", \
            outArgs->viddecOutArgs.displayBufs[outcount].chromaFormat);

			for(bufCount = 0;
                bufCount < outArgs->viddecOutArgs.decodedBufs.numBufs;
                bufCount++)
			{
				printf("Display Buffer Buf[%d] Address = 0x%X\n", \
                    bufCount, \
                    outArgs->viddecOutArgs.displayBufs[outcount].\
                    bufDesc[bufCount].buf);
				printf("Display Buffer Buf[%d] Size = 0x%X\n", \
                    bufCount, \
                    outArgs->viddecOutArgs.displayBufs[outcount].\
                    bufDesc[bufCount].bufSize);
				printf("Display Buffer Buf[%d] Access Mask = 0x%X\n",
					bufCount, outArgs->viddecOutArgs.displayBufs[outcount].\
                    bufDesc[bufCount].accessMask);
			}
		}
	}

	/* Free Buffer IDs */
	for(outcount = 0;
        outArgs->viddecOutArgs.outputID[outcount] != 0;
        outcount++)
	{
		if(outArgs->viddecOutArgs.freeBufID[outcount] == 0)
			break;
		printf("Free Buf ID[%d]: %d\n", outcount, \
            outArgs->viddecOutArgs.freeBufID[outcount]);
	}

	printf("\n");
}


/*****************************************************************************/
/**
*@func  printSEI_VUI_messages()
*@brief  Sample utility function for printing selected SEI and VUI messages
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
void printSEI_VUI_messages(void *seiVuiBufferPtr)
{
	sSeiVuiParams_t *pSeiVuiParams = (sSeiVuiParams_t *)seiVuiBufferPtr;
	sVSP_t *vui_params =           &pSeiVuiParams->vui_params;
	sSeiMessages_t *sei_messages = &pSeiVuiParams->sei_messages;

	if(pSeiVuiParams->parsed_flag == 0)
		return;

	/* Get selected VUI params VUI */
	if(vui_params->parsed_flag)
	{
		/* Aspect Ratio */
		if(vui_params->aspect_ratio_info_present_flag)
		{
			printf("\n Aspect ratio VUI:");
			printf("\n Aspect Raio IDC: %d, SAR Width: %d and SAR Height: %d\n",
				vui_params->aspect_ratio_idc,
				vui_params->sar_width,
				vui_params->sar_height);
		}

		/* Video Signal type VUI */
		if(vui_params->video_signal_type_present_flag)
		{
			printf("\n Video Signal Type VUI:");
			printf("\n Video format: %d, Video full range flag: %d\n",
				vui_params->video_format,
				vui_params->video_full_range_flag);

			if(vui_params->colour_description_present_flag)
			{
				printf("Color prim: %d, Transfer Char: %d, Martix Coef: %d\n",
					vui_params->colour_primaries,
					vui_params->transfer_characteristics,
					vui_params->matrix_coefficients);
			}
		}
	}

	/* Get selected SEI params SEI */
	if(sei_messages->parsed_flag)
	{
		/* Frame freeze repetition */
		if(sei_messages->frame_freeze_repetition.parsed_flag == 1)
		{
			sFullFrameFreezeRepetition_t *sei_frm_frz_rept =
			  &(sei_messages->frame_freeze_repetition);

			printf("\n Freeze repetition SEI:");
			printf("\n full_frame_freeze_repetition_period: %d\n",
				sei_frm_frz_rept->full_frame_freeze_repetition_period);
		}

		/* Frame freeze release SEI */
		if(sei_messages->frame_freeze_release.parsed_flag == 1)
		{
			printf("\n Freeze release SEI\n");
		}

		/* Progressive Refinement Start SEI */
		if(sei_messages->prog_refine_start.parsed_flag == 1)
		{
			printf("\n Refinement start SEI:");
			printf("\n Refinement ID: %d, refinement steps: %d \n",
			  sei_messages->prog_refine_start.progressive_refinement_id,
			  sei_messages->prog_refine_start.num_refinement_steps_minus1);

		}

		/* Progressive Refinement End SEI */
		if(sei_messages->prog_refine_end.parsed_flag == 1)
		{
			printf("\n Refinement end SEI:");
			printf("\n Refinement Stop: ID: %d \n",
				sei_messages->prog_refine_start.progressive_refinement_id);
		}

		/* Recovery Point SEI */
		if(sei_messages->recovery_pt_info.parsed_flag == 1)
		{
			printf("\n Recovery point SEI:");
			printf("\n Recovery FrmCnt: %d, Exact match: %d, Broken Link: %d\n",
				sei_messages->recovery_pt_info.recovery_frame_cnt,
				sei_messages->recovery_pt_info.exact_match_flag,
				sei_messages->recovery_pt_info.broken_link_flag);
			printf(" Recovery Changing group idc: %d\n",
				sei_messages->recovery_pt_info.changing_slice_group_idc);
		}

		/* Unregistered user data SEI */
		if(sei_messages->user_data_unregistered.parsed_flag == 1)
		{
			sUserDataUnregistered_t *user_data =
				&sei_messages->user_data_unregistered;

			printf("\n Unregistered user data SEI:");
			if((user_data->buffer_size_insufficient == 1) &&
				(user_data->user_data_size == 0))
			{
				printf("\n Couldn't get user data, Buf pointer set to NULL\n");
			}
			else if(user_data->user_data_size != 0)
			{
				XDAS_Int32 offset = 0;

				if(user_data->buffer_size_insufficient == 1)
				{
					printf("\n Buffer size insufficient to hold complete ");
					printf("user data. Copied Data follows: \n");
				}
				else
				{
					printf("\n Copied User data follows: \n");
				}

				while(offset < user_data->user_data_size)
				{
					printf("%c",
						user_data->user_data_payload_byte[offset++]);
				}
				printf("\n\n");

			}
			else
			{
				printf("\n No user data found\n");
			}
		}

		/* Registered user data SEI */
		if(sei_messages->user_data_registered.parsed_flag == 1)
		{
			sUserDataRegisteredITUT_t *user_data =
				&sei_messages->user_data_registered;

			printf("\n Registered user data SEI:");
			printf("\n Country code: %d", user_data->itu_t_t35_country_code);
			if(user_data->itu_t_t35_country_code == 0xFF)
			{
				printf(". Country code extn.: %d\n",
					user_data->itu_t_t35_country_code_extension_byte);
			}

			if((user_data->buffer_size_insufficient == 1) &&
				(user_data->user_data_size == 0))
			{
				printf("\n Couldn't copy data, Buffer pointer set to NULL\n");
			}
			else if(user_data->user_data_size != 0)
			{
				XDAS_Int32 offset = 0;

				if(user_data->buffer_size_insufficient == 1)
				{
					printf("\n Buffer size insufficient to hold complete ");
					printf("user data. Copied Data follows: \n");
				}
				else
				{
					printf("\n Copied User data follows: \n");
				}

				while(offset < user_data->user_data_size)
				{
					printf("%c",
						user_data->itu_t_t35_payload_byte[offset++]);
				}
				printf("\n\n");
			}
			else
			{
				printf("\n No user data found\n");
			}
		}

		/* Picture timing SEI */
		if(sei_messages->pic_timing.parsed_flag == 1)
		{
			XDAS_Int32 tsCount;

			printf("\n Picture timing SEI:");
			printf("\n CBP rem delay: %d, DPB out delay: %d, Pic struct: %d\n",
				sei_messages->pic_timing.cpb_removal_delay,
				sei_messages->pic_timing.dpb_output_delay,
				sei_messages->pic_timing.pic_struct);

			for(tsCount = 0; tsCount < 3; tsCount++)
			{
				if(sei_messages->pic_timing.clock_timestamp_flag[tsCount])
				{
					printf("\nTime stamp %d:", tsCount);
					printf("\n ct_type               : %d", \
                        sei_messages->pic_timing.ct_type[tsCount]);
					printf("\n nuit_field_based_flag : %d", \
                        sei_messages->pic_timing.\
                        nuit_field_based_flag[tsCount]);
					printf("\n counting_type         : %d", \
                        sei_messages->pic_timing.counting_type[tsCount]);
					printf("\n full_timestamp_flag   : %d", \
                        sei_messages->pic_timing.full_timestamp_flag[tsCount]);
					printf("\n discontinuity_flag    : %d", \
                        sei_messages->pic_timing.discontinuity_flag[tsCount]);
					printf("\n cnt_dropped_flag      : %d", \
                        sei_messages->pic_timing.cnt_dropped_flag[tsCount]);
					printf("\n n_frames              : %d", \
                        sei_messages->pic_timing.n_frames[tsCount]);
					printf("\n time_offset           : %d", \
                        sei_messages->pic_timing.time_offset[tsCount]);
					printf("\n hours_value           : %d", \
                        sei_messages->pic_timing.hours_value[tsCount]);
					printf("\n minutes_value         : %d", \
                        sei_messages->pic_timing.minutes_value[tsCount]);
					printf("\n seconds_value         : %d", \
                        sei_messages->pic_timing.seconds_value[tsCount]);
					printf("\n");
				}
				else
				{
					break;
				}
			}
		}
	}

	return;
}

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
                                    XDAS_Int32  width)
{
    XDAS_Int32 pic_size;
    XDAS_Int8 *CbCr_seperate[2];
    XDAS_Int8 *Luma_data;
    XDAS_Int8 *CbCr_data;
    XDAS_UInt32 refCRC, dataCRC;

    pic_size = width * height;

    /*----------------------------------------------------------------*/
    /* Init input subPic_buf with  outArgs                              */
    /*----------------------------------------------------------------*/
    Luma_data = outArgs->displayBufs[display_marker].bufDesc[0].buf;

    /*----------------------------------------------------------------*/
    /* Write YUV data to File    row-by row. Please note that display
     * buffer picture contains padded area as well. hence File write
     * is performed for every row circumventing the paddign area      */
    /*----------------------------------------------------------------*/
    for(height= 0;
        height < outArgs->displayBufs[display_marker].frameHeight;
        height++)
    {
        memcpy(Chroma_seperate +
            (height*outArgs->displayBufs[display_marker].frameWidth),
            Luma_data,
            outArgs->displayBufs[display_marker].frameWidth);
        Luma_data += outArgs->displayBufs[display_marker].framePitch;
    }

    fread (&refCRC, 1, sizeof(XDAS_UInt32), fRefFile);
    crcInit();
    dataCRC = crcFast(Chroma_seperate,
                     (height*outArgs->displayBufs[display_marker].frameWidth));

    if(dataCRC != refCRC)
    {
        printf("Luma data doesnot match \n");
        return -1;
    }


    CbCr_data = outArgs->displayBufs[display_marker].bufDesc[1].buf;
    /*----------------------------------------------------------------*/
    /* Init output yuv_buffer with global pointer fullPic              */
    /*----------------------------------------------------------------*/
    CbCr_seperate[0] = Chroma_seperate; ////Init for Cb
    CbCr_seperate[1] = CbCr_seperate[0] + (pic_size>> 2); //Init for Cr
    /*----------------------------------------------------------------*/
    /* This function seperated out the Cb and Cr component              */
    /*----------------------------------------------------------------*/
    separateCbCrPixels(CbCr_data,
                       CbCr_seperate,
                       (height >> 1),
                       width,
                       outArgs->displayBufs[display_marker].framePitch);

    fread (&refCRC, 1, sizeof(XDAS_UInt32), fRefFile);
    crcInit();
    dataCRC = crcFast(CbCr_seperate[0], pic_size>>2);

    if(dataCRC != refCRC)
    {
        printf("Cb data doesnot match \n");
        return -1;
    }
    fread (&refCRC, 1, sizeof(XDAS_UInt32), fRefFile);
    crcInit();
    dataCRC = crcFast(CbCr_seperate[1], pic_size>>2);

    if(dataCRC != refCRC)
    {
        printf("Cr data doesnot match \n");
        return -1;
    }
#ifdef _DBG_VERBOSE
    printf("Frame matches\n");
#endif

    return XDM_EOK;
}

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

//#define DUMP_PADDING
XDAS_Void TestApp_WriteOutputData(  FILE *fOutFile,
                                    XDAS_Int32 display_marker,
                                    IVIDDEC2_OutArgs *outArgs,
                                    XDAS_Int32  height,
                                    XDAS_Int32  width)
{
    XDAS_Int32 pic_size;
    XDAS_Int8 *CbCr_seperate[2];
    XDAS_Int8 *Luma_data;
    XDAS_Int8 *CbCr_data;

    pic_size = width * height;

    /*----------------------------------------------------------------*/
    /* Init input subPic_buf with  outArgs                            */
    /*----------------------------------------------------------------*/
    Luma_data = outArgs->displayBufs[display_marker].bufDesc[0].buf;
    CbCr_data = outArgs->displayBufs[display_marker].bufDesc[1].buf;

    /*----------------------------------------------------------------*/
    /* Init output yuv_buffer with global pointer fullPic             */
    /*----------------------------------------------------------------*/
    CbCr_seperate[0] = Chroma_seperate; ////Init for Cb
    CbCr_seperate[1] = CbCr_seperate[0] + (pic_size>> 2); //Init for Cr
    /*----------------------------------------------------------------*/
    /* This function seperated out the Cb and Cr component            */
    /*----------------------------------------------------------------*/
    separateCbCrPixels(CbCr_data,
                       CbCr_seperate,
                       (height >> 1),
                       width,
                       outArgs->displayBufs[display_marker].framePitch);
    /*----------------------------------------------------------------*/
    /* Write YUV data to File    row-by row. Please note that display */
    /* buffer picture contains padded area as well. hence File write  */
    /* is performed for every row circumventing the paddign area      */
    /*----------------------------------------------------------------*/
#ifdef DUMP_PADDING

	Luma_data -= 24;
    for(height= 0;
        height < outArgs->displayBufs[display_marker].frameHeight;
        height++)
    {
        fwrite (Luma_data,
               sizeof (xdc_Char),
               outArgs->displayBufs[display_marker].framePitch,
                fOutFile);
        Luma_data += outArgs->displayBufs[display_marker].framePitch;

    }

#else

    for(height= 0;
        height < outArgs->displayBufs[display_marker].frameHeight;
        height++)
    {
        fwrite (Luma_data,
                sizeof (char),
                outArgs->displayBufs[display_marker].frameWidth,
                fOutFile);
        Luma_data += outArgs->displayBufs[display_marker].framePitch;
    }
#endif
    /* Write chroma samples one after the other. Please note that
     * chroma writes are performed in one go since seperateCbCr utility
     * function would have taken care of jumping across the padded
     * region in the display buffer.
     */
    fwrite (CbCr_seperate[0], sizeof  (xdc_Char),pic_size>>2,fOutFile);
    fwrite (CbCr_seperate[1], sizeof  (xdc_Char),pic_size>>2,fOutFile);
    fflush (fOutFile);
    return;
}

#endif
/*****************************************************************************/
/*    Copyright (c) 2006 Texas Instruments, Incorporated                     */
/*    All Rights Reserved                                                    */
/*****************************************************************************/
/*!
*! Revision History
*! ================
*!
*! 07-Aug-2007 Vinay M K: Incorporated code review comments.
*! 31-May-2007 Vinay M K: Modified to comply with MMCodecs
*!                        coding guidelines.
*! 15-May-2007 Vinay M K: Modified to integrate regular and flush mode of
*!                        operation in single do-while loop; added XDM1.0
*!                        specific
*!                        changes.
*! 05-Jan-2006 Dinesh Kumar: Created.
*/
