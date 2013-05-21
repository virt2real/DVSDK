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
* @file TestAppXDMResetDecoder_ih264_arm926.c
*
* @path $(PROJDIR)\src
*
* @brief  This is the top level client file that drives the H264
*        (Baseline Profile) Video Encoder Call using XDM v1.0 Interface
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

#ifdef TEST_RESET

#ifdef ON_LINUX
//#define PROFILE_ONLINUX
//#define PROFILE_ONLINUX_ARM968
#endif

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

//static GT_Mask someGTMask;

/*-------program files ----------------------------------------*/
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
  {NULL,             NULL}
};
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
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

/* Extended params and Arguments */
#define EXTENDED_PARAMS_ARGS
/* Header Decode Mode */
//#define HEADER_DECODE_MODE
/* Toggle code loading of ARM968 */
//#define TOGGLE_ARM968_LOADING

/* Set the default level to 4.2 */
#define H264_DPB_SIZE_PROFILE	H264_DPB_SIZE_PROFILE_4_2

/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/* Defining this macro enables dumping of decoded data in packed
 * YUV 4:2:0 format - into a file stream. Useful for debugging.
 */
#define ENABLE_FILE_OUTPUT
#define _ENABLE_IRES_EDMA3
/* Additional debug printfs are controlled by defining this macro */
//#define _DBG_VERBOSE
//#define _DEBUG_LINUX
/* In H264 decoder; decode order of frames and display order CAN
 * be different. Especially in the case when B-frames are present
 * in the video stream; it is important that decoder delays display
 * of decoded frames suitably to maintain correct display order.
 * A minimum display delay of 2 is required to take care of IPBPB
 * sequences which are displayed as  IBPBP.
 * Initial "DISPLAY_DELAY" number of process calls would result in
 * no-output frames. DISPLAY_DELAY values are limited between 0
 * and 16.
 */
#define DISPLAY_DELAY            16
#define DEFAULT_DISPLAY_WIDTH	0

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
XDAS_UInt32 bytesConsumed;
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
    xdc_Char line[STRING_SIZE], inFile[STRING_SIZE], testFile[STRING_SIZE];
    xdc_Char paramsFile[STRING_SIZE];
    XDAS_UInt32 testCompliance;
#ifdef ON_LINUX
//    XDAS_Int8 *fname = "./testvecs/config/testvecs_linux.cfg";
    xdc_Char *fname = "../../test/TestVecs/Config/testvecs_linux.cfg";
#else
    xdc_Char *fname = "C:\\temp\\h264\\Testvecs.cfg";
#endif

    /* Base Class Structures */
    IVIDDEC2_Status             status;
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
    BUFFMGR_buffEleHandle buffEle;

    /* Other variables */
    XDAS_Int32  decode_frameCount, retVal, testVal, decodeHeaderRetVal;
	XDAS_Int32  countConfigSet;
    /* inFlushModeFlag is a boolean flag which indicates the state
     * of the decoder instance - XDM_FLUSH or non-flush mode.
     * refer to user guide for details on XDM_FLUSH */
    XDAS_Int32  inFlushModeFlag;
    XDAS_UInt32  ii;
    XDAS_Int8  *tmpInputBufPtr;
    XDAS_Int32 decodeHeaderMode, displayedFrameCount;
	XDAS_Int32  RMAN_assignResourcesSuccess = 0;
	XDAS_Int8 versionBuf[256];
/* Memory allocation params required in linux */
#ifdef ON_LINUX
    LockMP_init();
    SemMP_init();
    Memory_init();
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
    countConfigSet = 0;
	handle = NULL;

  /* Read the Config File until it reaches the end of file */
  while(!feof(fConfigFile))
  {

    displayedFrameCount = 0;
    /* Read Compliance Checking parameter */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%d",&testCompliance);
        else goto EndOfDecoding;
    /* Read Parameters file name */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%s",paramsFile);
        else goto EndOfDecoding ;
    /* Read Input file name */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%s",inFile);
        else goto EndOfDecoding ;
    /* Read Output/Reference file name */
    if(fgets(line,254,fConfigFile))
    	sscanf(line,"%s",testFile);
        else goto EndOfDecoding ;

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
    /*---------------- Decoder creation -----------------*/
	if(countConfigSet == 1)
	{
    handle = (IALG_Handle)
            H264VDEC_create((IALG_Fxns*)&H264VDEC_TI_IH264VDEC,
                            (IALG_Params*)&params);
    if (handle == NULL)
    {
      printf( "\nFailed to Create Instance... \
                 Exiting for this configuration..");
			fflush(stdout);
          goto EndOfDecoding;
    }
#ifdef _ENABLE_IRES_EDMA3
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)handle,
                                        &H264VDEC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
      printf( "\nFailed in assignign resources \
                 Exiting for this configuration..");
		  RMAN_assignResourcesSuccess = 0;
		  goto EndOfDecoding;
		}
		else
		{
			RMAN_assignResourcesSuccess = 1;
    }
#endif
		status.size                  = sizeof(IVIDDEC2_Status);
		status.data.buf = versionBuf;
		status.data.bufSize = sizeof(versionBuf);
    }

	/*------Control call for ---- Get version number --------------*/
	H264VDEC_control(handle,
                     XDM_GETVERSION,
					 (IVIDDEC2_DynamicParams *) NULL,
                    (IVIDDEC2_Status *)&status);
	printf("\nLibrary Version: %s\n", status.data.buf);

#if 1
	/*------Control call for ---- Set params --------------*/
	dynamicParams.viddecDynamicParams.displayWidth = DEFAULT_DISPLAY_WIDTH;
	dynamicParams.viddecDynamicParams.frameSkipMode = IVIDEO_NO_SKIP;
	dynamicParams.viddecDynamicParams.frameOrder = IVIDDEC2_DISPLAY_ORDER;
	/* Reset coprocessor flag enables the algorithm to save context from the
     * co-processor at the end of every frame decoding */
    dynamicParams.resetHDVICPeveryFrame = 0;
#ifdef HEADER_DECODE_MODE
	dynamicParams.viddecDynamicParams.decodeHeader = XDM_PARSE_HEADER;
	decodeHeaderMode = 1;
#else
	dynamicParams.viddecDynamicParams.decodeHeader = XDM_DECODE_AU;
	decodeHeaderMode = 0;
#endif


    H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);

#endif
    /*------Control call for ---- Get Buffer Sizes --------------*/
    H264VDEC_control(handle,
                     XDM_GETBUFINFO,
                    (IVIDDEC2_DynamicParams *) NULL,
                    (IVIDDEC2_Status *)&status);
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
    inputBufDesc.numBufs     = status.bufInfo.minNumInBufs ;
    for(ii=0; ii<(status.bufInfo.minNumInBufs);ii++ )
    {
        inputBufDesc.descs[ii].buf = tmpInputBufPtr;
        tmpInputBufPtr += status.bufInfo.minInBufSize[ii];
        inputBufDesc.descs[ii].bufSize = status.bufInfo.minInBufSize[ii];
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
    SeiVui_obj.sei_messages.user_data_unregistered.user_data_payload_byte = NULL;
    SeiVui_obj.sei_messages.user_data_registered.itu_t_t35_payload_byte = NULL;

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
    do
    {
        /* Read the bitstream in the Application Input Buffer. validBytes
         * would be initialised with the actual number of bytes read from the
         * input file */

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
        /*----------------------------------------------------------------*/
        /* Setting of input arguments */
        /*----------------------------------------------------------------*/
        /* Assign the number of bytes available, and point to
         * correct location in the input bufer for next process call
         */
		inArgs.viddecInArgs.numBytes        = validBytes;
        inputBufDesc.descs[0].buf   = inputData + bytesConsumed;
	//	if(!outArgs.viddecOutArgs.outBufsInUseFlag)
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

#if 1
        {
			if(decode_frameCount == 0)
				printf("\n\nStarting Decode on ARM968...\n\n");
        }
#endif

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
            //printf("time before = %d\n",decoder_timeptr->tv_usec);
#endif
        retVal = H264VDEC_decode(handle,
                               (XDM1_BufDesc *)&inputBufDesc,
                               (XDM_BufDesc *)&outputBufDesc,
                               (IVIDDEC2_InArgs *)&inArgs,
                               (IVIDDEC2_OutArgs *)&outArgs);


		/* If decodeHeaderMode, save the return value: XDM_EOK or XDM_EFAIL */
		if(decodeHeaderMode == 1)
		{
			decodeHeaderRetVal = retVal;
		}


#ifdef PROFILE_ONLINUX
            time_after_process = gettimeofday(decoder_timeptr, NULL);
            //printf("time After = %d\n",decoder_timeptr->tv_usec);
            //printf("time before = %d, time after = %d\n",time_before_process,time_after_process);
	    if(decoder_timeptr->tv_usec <= time_before_process)
	    {

	    	decoder_timeptr->tv_usec += 1000000;
	    }

	    /* Print the time in micro-second for current frame, Commulative time and */
	    /* the average up to the current decoded frame */
		commulative_time += (decoder_timeptr->tv_usec - time_before_process);
		average_time = (float)commulative_time/(decode_frameCount + 1);
		if((max_time < (decoder_timeptr->tv_usec - time_before_process)))
			max_time = decoder_timeptr->tv_usec - time_before_process;

	    printf("FRAME LEVEL DECODE TIME = %d, C %d, A %f, M %d\n",
			(decoder_timeptr->tv_usec - time_before_process), commulative_time, average_time, max_time);
#endif

#ifdef PROFILE_ONLINUX_ARM968
		com_arm968_time += arm968_time;
		avg_arm968_time = com_arm968_time/(decode_frameCount + 1);
		if(max_arm968_time < arm968_time)
			max_arm968_time = arm968_time;
		printf("ARM968 FRAME DECODE TIME = C %d, A %d, M %d\n",arm968_time, avg_arm968_time, max_arm968_time);
#endif

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        profileEd = profileEnd(0);
        printf("Start = %d; End = %d; On 968 = %d\n",
                    profileSrt, profileEd, profile968);
#endif
#ifdef _DBG_VERBOSE
        /* _DBG_VERBOSE macro controls printing of output buffer
         * IDs given by the decoder algorithms process call.
         * Giving no output for a particular process call and
         * giving multipe output buffers in a single call are both
         * valid conditions for the process API.
         */
        {
            XDAS_UInt32 outcount;
            XDAS_UInt32 TempOPId;

            for(outcount = 0; outArgs.viddecOutArgs.outputID[outcount] != 0; outcount++)
            {
                TempOPId = outArgs.viddecOutArgs.outputID[outcount];
                printf("OutBufId = %d", outArgs.viddecOutArgs.outputID[outcount]);
                printf("Frame Ht = %d\n",outArgs.viddecOutArgs.displayBufs[outcount].frameHeight);
                printf("Frame Wdth = %d\n",outArgs.viddecOutArgs.displayBufs[outcount].frameWidth);
                printf("Frame Pitch = %d\n",outArgs.viddecOutArgs.displayBufs[outcount].framePitch);
            }

            printf("\n");
			fflush(stdout);
        }
#endif


        /*------------------------------------------------------------------*/
        /* Get status control call enables the user to get the exact picture*/
        /* size in terms of pixel height and width                          */
        /*------------------------------------------------------------------*/
        H264VDEC_control(handle, IH264VDEC_GETSTATUS,
                        (IVIDDEC2_DynamicParams *) NULL,
                        (IVIDDEC2_Status *)&status);
        if(status.extendedError)
        {
           printf("Error code [Control Frame] %x \n", status.extendedError);
        }

         /* Check for return value of the process call. Please note
         * that when the decoder instance is in XDM_FLUSH mode
         * end-of-decode i.e emptying of picture buffer of all the
         * previously decoded frames is indicated by returning error.
         * hence if the process call returns error all we need to do
         * is break out of the do-while loop if inFlushModeFlag is TRUE
         */
//		 printf("Status Returned by the decoder = %d \n", retVal);
        if(retVal == XDM_EFAIL && ((XDM_ISFATALERROR(status.extendedError) == 0x1)
             ) //start of frame error
            &&
            (FALSE == inFlushModeFlag)
            )
        {
            printf("Terminating execution due to critical error (0x%x) at: %d \
                    , Flushing out remaining frames. \n", status.extendedError,
                                                            decode_frameCount);

            if(decode_frameCount > displayedFrameCount) {
                /*-------------------------------------------------------*/
                /* Call FLUSH command to set the flush mode for decoder     */
                /* This is required to flush out left over displayable   */
                /*   frames in DPB                                       */
                /*-------------------------------------------------------*/
                H264VDEC_control(handle, XDM_FLUSH, NULL, &status);

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


		/*********************************************************************/
		/* Frame count is incremented when following conditions are not true */
		/* 1. outBufsInUseFlag is set, i.e., buffer is still in use          */
		/* 2. Previous process call was made with decodeHeader mode          */
		/* 3. process returned XDM_UNSUPPORTEDINPUT for 1st frame            */
		/* 4. process returned XDM_CORRUPTEDHEADER for 1st frame             */
		/* 5. process returned IH264VDEC_EX_ERR_HEADER_NOT_FOUND for 1st frm */
		/*********************************************************************/
		if((outArgs.viddecOutArgs.outBufsInUseFlag == 0) &&
			(decodeHeaderMode == 0) && ((decode_frameCount != 0) ||
			(!(status.extendedError & (1 << XDM_UNSUPPORTEDINPUT)) &&
			 !(status.extendedError & (1 << XDM_CORRUPTEDHEADER)) &&
			 ((status.extendedError & 0xFF) != IH264VDEC_EX_ERR_HEADER_NOT_FOUND))))
		{
			decode_frameCount++;
		}

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

		/*********************************************************************/
		/* Cases for calling GETBUFINFO and ReInint after the process call.  */
		/* Case 1 - decodeHeaderMode = 1: If returned with XDM_EOK. Ideally, */
		/* it should happen when header is decoded but decode_frameCount = 0 */
		/* Case 2 - decodeHeaderMode = 0: If first frame is actually decoded */
		/* with correct header. Ideally, should be for decode_frameCount = 1 */
		/*********************************************************************/
		//printf("\n decodeHeaderMode = %d, decodeHeaderRetVal = %d\n",
		//	decodeHeaderMode, decodeHeaderRetVal);

#ifdef HEADER_DECODE_MODE
		if((decodeHeaderMode == 1) &&  (decodeHeaderRetVal != XDM_EFAIL))
#else
		if(decode_frameCount == 1)
#endif
		//if (((decodeHeaderMode == 0) && (decode_frameCount == 1)) ||
		//	((decodeHeaderMode == 1) && (decodeHeaderRetVal != XDM_EFAIL)))
        {
            /* Get the exact luma and chroma buffer requirements for the
             * YUV piture buffers, given input bit-stream. */
            H264VDEC_control(handle, XDM_GETBUFINFO, NULL, &status);
            /* Use the above exact luma and chroma buffer reuqirements
             * for the input bit-stream to re-initialise the buffer manager.
             * refer to buffermanager specific XDM v1.0 intergation doc
             * for more details.
             */
            BUFFMGR_ReInit(status.bufInfo.minOutBufSize[0],
                           status.bufInfo.minOutBufSize[1]);
        }

#ifdef HEADER_DECODE_MODE

		if((decodeHeaderMode == 1) && (decodeHeaderRetVal != XDM_EFAIL))
		{
			/*------Control call for ---- Set params --------------*/
			/* Keep all other params constant, toggle only decodeHeader */
			dynamicParams.viddecDynamicParams.decodeHeader = XDM_DECODE_AU;
			decodeHeaderMode = 0;

			H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);
		}
#endif

#ifdef TOGGLE_ARM968_LOADING
#ifdef EXTENDED_PARAMS_ARGS

			/*------Control call for ---- Set params --------------*/
			/* Keep all other params constant, toggle only resetHDVICPeveryFrame */
			dynamicParams.resetHDVICPeveryFrame = 1 - dynamicParams.resetHDVICPeveryFrame;

			H264VDEC_control(handle,
                     XDM_SETPARAMS,
                    (IVIDDEC2_DynamicParams *) &dynamicParams,
                    (IVIDDEC2_Status *)&status);
#endif
#endif

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
        /* Check if the decoder instance is in XDM_FLUSH mode */
        if(FALSE == inFlushModeFlag)
        {
            /* If not then update the variables managing the input encoded
             * bit-stream buffer
             */
            bytesConsumed += outArgs.viddecOutArgs.bytesConsumed;
            validBytes = validBytes -  outArgs.viddecOutArgs.bytesConsumed;
            /* Sometimes it is possible that decoder reports one byte
             * extra consumption than what is available in the input
             * bit-stream due to rounding off errors. validBytes == -1
             * would trigger an input file read error condition. To
             * avoid this faux-paus we re-initialsie validBytes variable
             * to zero - which serves the purpose perfectly well.
             */
            if(validBytes < 0) validBytes = 0;
#if 1 //_DBG_VERBOSE
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

            if(outArgs.viddecOutArgs.decodedBufs.extendedError)
            {
                printf("Error code [Decoded Frame %d] %x \
                        Erroneous Mbs in curr frame: %d\n", \
                        decode_frameCount,
                        outArgs.viddecOutArgs.decodedBufs.extendedError,
                        outArgs.numErrMbs);
            }

			printf("\n Process call complete\n");
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

#ifdef _DBG_VERBOSE
				IVIDDEC2_OutArgs *dispArgs = (IVIDDEC2_OutArgs *)&outArgs;
				printf("\n\n");
				printf("Frame Type: %d\n", dispArgs->displayBufs[ii].frameType);
				printf("Content Type: %d\n", dispArgs->displayBufs[ii].contentType);
				printf("TopFldFirst Flag: %d\n", dispArgs->displayBufs[ii].topFieldFirstFlag);
				printf("Repeat Frame: %d\n", dispArgs->displayBufs[ii].repeatFrame);
#endif
                if(testCompliance)
                {
                    /* Compare the output frames with the Reference File */
                    testVal =
                        TestApp_CompareOutputData(ftestFile, ii,
                                                 (IVIDDEC2_OutArgs *)&outArgs,
                                                 status.outputHeight,
                                                 status.outputWidth);

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
                                             status.outputHeight,
                                             status.outputWidth);
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
            H264VDEC_control(handle, XDM_FLUSH, NULL, &status);

            /* Set the flush mode flag to ON condition -
             * this flag will help us exit out of the while loop
             * process return error.
             */
            inFlushModeFlag = TRUE;
        }
    }  while(1);  /* end of Do-While loop - which decodes frames */

EndOfFile1:
EndOfFile:


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
    printf("\t Width and Height                    = %d, %d \n",
      (XDAS_UInt32)status.outputWidth, (XDAS_UInt32)status.outputHeight);
    printf (" --------------    END   --------------------\n");

    H264VDEC_control(handle, XDM_RESET, NULL, (IVIDDEC2_Status *)&status);


  } /* Read the Config File until it reaches the end of file */

EndOfDecoding:

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
	if(RMAN_assignResourcesSuccess == 1)
	{
		if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle),
											&H264VDEC_TI_IRES, /* IRES_Fxns* */
											1 /* scratchId */)) {
			printf("Free Resource Failed \n");
			//return -1;
		}
	}
#endif

	BUFFMGR_DeInit();

    /* Delete the Algorithm instance object specified by handle */
    if(handle)
        ALG_delete (handle);


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
    /* Init input subPic_buf with  outArgs                              */
    /*----------------------------------------------------------------*/
    Luma_data = outArgs->displayBufs[display_marker].bufDesc[0].buf;
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
    /*----------------------------------------------------------------*/
    /* Write YUV data to File    row-by row. Please note that display
     * buffer picture contains padded area as well. hence File write
     * is performed for every row circumventing the paddign area      */
    /*----------------------------------------------------------------*/
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
