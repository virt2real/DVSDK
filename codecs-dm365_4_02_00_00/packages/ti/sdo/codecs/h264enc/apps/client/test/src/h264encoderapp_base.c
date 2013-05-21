/** ===========================================================================
* @file  h264encoderapp.c
*
* @path  $(PROJDIR)\Client\Test\Src
*
* @brief This is the main application file calling the H264 Encoder application
*        using XDM 1.0 APIs. This file has all functionality to read the input
*        data, set up the encoder intialization params, encode the stream,
*        write out the data and close down the application.
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied 
*
* ===========================================================================
*/
/* --------------------- COMPILATION CONTROL SWITCHES -----------------------*/
/* The following macros are enabled for reading the profile figures when the
 * profiling is done on ARM968 side. The appropriate macro is also defined
 * in ARM968 workspace.
 * FRAME_PROFILE enables only Frame Level Profiling on ARM968 side
 * MB_TTL_PROFILE enables profiling of total MB Loop Execution
 * MB_LOOP_PROFILE enables profiling for each MB Loop Execution
 * _PROFILE enables the writing of the profile figures to file
 */
#if defined(FRAME_PROFILE)  || \
    defined(MB_TTL_PROFILE) || \
    defined(MB_LOOP_PROFILE)
#define _PROFILE
#endif

#define _ENABLE_IRES_EDMA3

#ifdef ON_LINUX
	#define CHANGE_PATH 3 /* one ../ should be removed to run on linux */
#endif

//#define _55_
//#define _67_

/* The following macro is for enabling the set of new parameters during run
 * time. If this macro is not defined, the dynamic parameters are set before
 * encoding the first frame.
 */
//#define UPDATE_PARAMS_AT_RUN_TIME
//#define SCRATCH_CONTAMINATION_TEST

/* ------------------------------------ PRAGMAS ---------------------------- */
/*****************************************************************************/
/*                              INCLUDE FILES                                */
/*****************************************************************************/
/* ---------------------- SYSTEM AND PLATFORM FILES -------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <ti/xdais/idma.h>
#include <ti/sdo/fc/utils/api/_alg.h>
#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>

#ifdef DEVICE_ID_CHECK
/* Link modules used for DEVICE ID check */
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>
#endif
/*----------------------------- PROGRAM FILES -------------------------------*/
#include "h264venc.h"
//#include "ih264venc.h"
#include "h264venc_tii.h"
#include <ti/xdais/idma.h>
#include "testapp_arm926intc.h"

/* ENABLE_PROFILE_AT_FRM_LVL_ON_926 macro is defined for enabling profiling of
 * code for cycles on ARM926 side. This macro is also used in hdvicp_framework.c
 * to tap points for profiling
 */ 
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
#include "timerAPI.h"
#endif //ENABLE_PROFILE_AT_FRM_LVL_ON_926

/*****************************************************************************/
/*     EXTERNAL REFERENCES NOTE : only use if not found in header file       */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/
/* This global variable is defined inside hdvicp_framework.c and is temporarily 
 * used for polling during sem-pend
 */
extern IRES_Fxns H264VENC_TI_IRES;
/* Allocate CMEM structure and intialize it */
    CMEM_AllocParams memParams;
/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
/* Declaration of functions for counting the cycles when profiling on ARM926
 * is enabled. The functions are defined in timerAPI.c file
 */ 
extern void profileInit(int i);
extern void profileStart(int i);
extern Uint64 profileCount(int i);
extern Uint64 profileEnd(int i);
#endif //ENABLE_PROFILE_AT_FRM_LVL_ON_926
void ARM926_Icache_Disable()
{
	return;
}
void ARM926_Dcache_Disable()
{
	return;
}
/*****************************************************************************/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/
/* For Profiling on ARM926, variables for storing the profile cycles
 * profileSrt - Cycles before control is switched to ARM968 for encoding
 * profile968 - Cycles consumed while ARM968 is encoding
 * profileEd - cycles for end of frame processing after control is transferred
 *             back to ARM926
 */
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
XDAS_UInt32 profileSrt;
XDAS_UInt32 profile968;
XDAS_UInt32 profileEd;
#endif //ENABLE_PROFILE_AT_FRM_LVL_ON_926

/* When profiling is enabled on ARM968, defining array for copying the cycles
 * from ARM968
 */
#ifdef _PROFILE
XDAS_UInt32 profArr[4096];
XDAS_UInt32 frmCycles;
#endif //_PROFILE

XDAS_Int32 PACKET_SIZES[200];
static GT_Mask someGTMask;
/*****************************************************************************/
/*              PRIVATE DECLARATIONS Defined here, used only here            */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/
/** ===========================================================================
* @name   sTokenMapping
*
* @desc   Token Mapping structure for parsing codec specific configuration file
*
* @field  tokenName
*         String name in the configuration file
*
* @field  bType
*         type of Token - Numerical type(0) or String type(1)
*
* @field  place
*         Place Holder for the data
*
* @see    
* =============================================================================
*/
typedef struct _sTokenMapping
{
    XDAS_Int8 *tokenName;
    XDAS_Int8 bType;
    XDAS_Void *place;
} sTokenMapping;

/* Macro defining the maximum number of parameters to be parsed from the input
 * configuration file
 */
#define MAX_ITEMS_TO_PARSE  1000

/* Array of elements of type sTokenMapping for parsing and holding the tokens
 * from the input configuration file.
 */
static sTokenMapping sTokenMap[MAX_ITEMS_TO_PARSE];
/* Array for reading and storing the contents of input configuration file */
static XDAS_Int8 buf[20000];
/* Pointers to memory location containing input YUV420 data */
static XDAS_UInt8 *pubInY;
static XDAS_UInt8 *pubInU;
static XDAS_UInt8 *pubInV;

/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/
Int
H264VENC_setinitparams (
    H264VENC_Params *params
);

Int
H264VENC_setrunparams (
    H264VENC_DynamicParams *params
);

static XDAS_Int32
ParameterNameToMapIndex (
    XDAS_Int8 *s
);
static XDAS_Int8 *
GetConfigFileContent (
    FILE *fname
);

static XDAS_Int32
readparamfile (
    FILE * fname
);

static XDAS_Int32
ParseContent (
    XDAS_Int8 *buf,
    XDAS_Int32 bufsize
);

static XDAS_Int32
AllocateH264IOBuffers (
    IVIDENC1_Status H264EncStatus,
    IVIDEO1_BufDescIn *ptH264EncInpBufDesc, 
    XDM_BufDesc *ptH264EncOutBufDesc
);

static void
FreeH264IOBuffers (
    IVIDEO1_BufDescIn *ptH264EncInpBufDesc, 
    XDM_BufDesc *ptH264EncOutBufDesc
);

static XDAS_Int32
WriteDataOut (
    IVIDENC1_OutArgs outArgs, 
    FILE *pfOutBitStreamFile, 
    XDAS_Int32 iMode
);

static XDAS_Int32
WriteReconOut (
    XDAS_UInt8* pubReconY, 
    XDAS_UInt8* pubReconU, 
    XDAS_UInt8* pubReconV, 
    XDAS_Int32 uiWidth, 
    XDAS_Int32 uiHeight, 
    FILE *pfOutYUVFile
);

static XDAS_Int32
ReadInputData(IVIDEO1_BufDescIn tInpBufferDesc,
	XDAS_UInt32 uiOrgWidth,
	XDAS_UInt32 uiOrgHeight, 
	XDAS_UInt32 uiExtWidth, 
	XDAS_UInt32 uiExtHeight,
	FILE *pfInYUVFile
);

void
DoChromaInterleave (
    unsigned char *pubYFrameData, 
    unsigned char *pubUFrameData, 
    unsigned char *pubVFrameData, 
    unsigned char *pubSubPictY, 
    unsigned char *pubSubPictUV, 
    unsigned int uiPictWidth, 
    unsigned int uiPictHeight
);

void
GetReconFrame (
    unsigned char *pubYFrameData, 
    unsigned char *pubUFrameData, 
    unsigned char *pubVFrameData, 
    unsigned char *pubSubPictY, 
    unsigned char *pubSubPictUV, 
    unsigned int uiPictWidth, 
    unsigned int uiPictHeight,
    unsigned int uiRecPitch,
    unsigned int uiContentType
);

/*--------------------------------- MACROS ----------------------------------*/
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
/* MAX_FRAMES - The total number of frames to be profiled when profiling is 
 * enabled on ARM926
 */
#define MAX_FRAMES          10000
#endif //ENABLE_PROFILE_AT_FRM_LVL_ON_926
/* Macros defining the constraints on the application and the codec
 * MAX_WIDTH - The maximum width of video that can be supported by encoder
 * MAX_HEIGHT - The maximum height of video that can be supported by encoder
 * MAX_QP - The maximum quantization parameter supported by encoder
 * MIN_QP - The minumum quantization parameter supported by encoder
 * The min and max QP should not be defined here, it should be communicated 
 * between the encoder and application. Defined here for Debug purpose
 */
#define MAX_WIDTH           1280
#define MAX_HEIGHT          720
#define MAX_QP              51
#define MIN_QP              0

/* Following macros are used for dumping reconstructed frames. The reconstructed
 * frame returned by encoder library is in padded form. These macros define
 * the size of padding. For correct results these macros should remain
 * consistent with the padding done inside the encoder library
 */
#define PAD_Y_HORIZ                   32 /*!< Padding along Horizontal for Y */
#define PAD_Y_PROG_VERT               26 /*!< Padding along Veritcal for Y   */
#define PAD_UV_HORIZ                  32 /*!< Padding along Horizontal for C */
#define PAD_UV_PROG_VERT              12 /*!< Padding along Veritcal for C   */

#define MAX_FRAMES_TO_ENCODE 5000

/*===========================================================================*/
/**
*@func   main
*
*@brief  This is the main Application code used to call the H.264 Encoder. 
*        The encoder is interfaced through XDM 1.0 APIs. The creation,
*        execution, and deletion of the encoder is done using the xDM 1.0 APIs.
*        This function also performs allocation of memory for input and output,
*        parsing input configuration file, reading input data, conversion of
*        input data to chroma interleaved form, preparing input and output
*        params and writing encoded data and reconstructed frame to file.
*
*@param  argc
*        Number of arguments passed in command line
*
*@param  argv
*        Pointer to the charater array contining the arguments
*
*@return void
*
*@see    None
*
*@note   None
*/
/*===========================================================================*/
 main(XDAS_Int32 argc, XDAS_Int8 **argv)
{
    H264VENC_Handle  handle;  /* Handle to the Encoder instance      - XDAIS */
    IH264VENC_Fxns fxns;      /* Function table for the H.264 Encoder- XDAIS */
    IVIDENC1_Params params;   /* Instance creation Parameter         - XMI   */
    IVIDENC1_Status status;   /* Stores the status of process call   - XDM   */
    IVIDENC1_InArgs inargs;   /* Input Parameter to the process call - XDM   */
    IVIDENC1_OutArgs outargs; /* Ouput parameters from process call  - XDM   */ 
    IVIDENC1_DynamicParams dynamicparams; /* Dynamic Parameter struct- XDM   */ 
    IVIDEO1_BufDescIn inobj;  /* Input Buffer description array      - XDM   */
    XDM_BufDesc outobj;       /* Output Buffer description array     - XDM   */ 
    XDAS_Int32 iErrorFlag;    /* Local Variables to Keep track of errors     */
    XDAS_UInt8 *pubYRecon;    /* Pointer to the Reconstructed Luma Frame */
    XDAS_UInt8 *pubURecon;    /* Pointer to the Reconstructed U Frame */
    XDAS_UInt8 *pubVRecon;    /* Pointer to the Reconstructed V Frame */

    /* Variables to keep track of various input configuration parameters */
    XDAS_UInt32 uiNumFrames;            /* Number of frames encoded         */
    XDAS_UInt32 uiNumFramesToBeEncoded; /* Number of frames to be encoded   */
    XDAS_UInt32 uiNumBytesWritten;      /* Number of encoded bytes written  */
    XDAS_UInt32 uiTokenCtr;             /* Token map counter                */
    XDAS_UInt32 numTicksPerFrame;       /* For generating Time Stamp        */
    XDAS_Int32 uiExtWidth;              /* Width with padding to 16         */
    XDAS_Int32 uiExtHeight;             /* Height with padding to 16        */
	XDAS_Int32 uiFrmPitch;              /* Line Pitch for the input frame   */
    XDAS_Int8  bWriteEncodedData;       /* Switch for Bitstream write out   */
    XDAS_Int8  bWriteReconData;         /* Switch for Recon write out       */
	XDAS_Int8  bSEIFlagOut;				/* Switch for adding SEI userdata	*/
    XDAS_Int8  bInputFile[400];         /* Input file name                  */ 
    XDAS_Int8  bEncOutFile[400];        /* Encoded output file name         */ 
    XDAS_Int8  bReconOutFile[400];      /* Reconstructed decoded output file*/ 
    XDAS_Int8  bConfigFile[400];        /* Config Parameters */
    XDAS_Int8  line[400];
	XDAS_Int32  testCompliance;
	XDAS_Int32 retVal;
	XDAS_Int32 iSkipCnt;                /* Variable for keeping skip count  */
	XDAS_Int32 iStatus;                 /* Flag for file read error check */

    FILE *pfConfigParamsFile;  /* Pointer to the Configuration File         */ 
    FILE *pfInputYUVFile;      /* Pointer to the Input Video YUV File       */
    FILE *pfOutBitStreamFile;  /* Pointer to the output BitStream File      */
    FILE *pfOutYUVFile;        /* Pointer to the output reconstructed File  */
    FILE *pfConfigFileList ;   /* Pointer to the list of Config Files */
    XDAS_Int32 configFileCount =0;
	IRES_Status iresStatus;
#ifdef DEVICE_ID_CHECK
	IRESMAN_AddrSpaceParams addrspaceConfigParams;
#endif
#ifdef ON_LINUX
	/* This is used as temporary variable to change the path, reading from 
	 * config files. */ 
	XDAS_Int8 *bChangeDirForConfigFile;	/* Config file directory change */
#endif

#ifdef PROFILE_ONLINUX
    XDAS_UInt32 time_before_process, time_after_process;
    struct timeval encoder_time, *encoder_timeptr;
    static unsigned int frame_count_p, total_time_p;
#endif

#ifdef _PROFILE
    /* Open a output file for profile data */
    FILE *profFilePtr; /* File Pointer to file for writing profile figures */
    profFilePtr = fopen("..\\..\\..\\Test\\TestVecs\\Output\\profile.txt", "w");
#endif //_PROFILE

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
    XDAS_UInt32 ProfDataArray[MAX_FRAMES];
    FILE *pfProfFile =
        fopen("..\\..\\..\\Test\\TestVecs\\Output\\ProfileData.txt", "w"); 
    if(pfProfFile == NULL)
    {
        printf("\nERROR! - Could Not open Profile Log File %s", pfProfFile);
        exit(-1);
    }
#endif /* #ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926 */
#ifdef ON_LINUX
    LockMP_init();
    SemMP_init();
    Memory_init();
#endif

#ifndef SINGLE_PROC_CODE
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
    ARM926_Icache_Disable();
    ARM926_Dcache_Disable();
#endif //ENABLE_CACHE
#endif //SINGLE_PROC_CODE

    bSEIFlagOut = 0;
    bWriteEncodedData = 1; /* Enable writing of encoded data to file */
    bWriteReconData = 0; /* Enabled writing reconstructed frame to file */
  
    /* Intialize function table pointer to the function table implementation for
     * H.264 Encoder by TI.
     */
    fxns = H264VENC_TI_IH264VENC;
	//GT_init();
	//GT_create(&someGTMask, "ti.sdo.fc.rman.examples.dummyEdma3");
	//GT_set("*" "=01234567");

    /* Initialization and allocation */
    CMEM_init();
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_CACHED;
    memParams.alignment=256;

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
    /* Register the VICP protocol/resource manager with the
     * generic resource manager */
   iresStatus = (IRES_Status)RMAN_register(&IRESMAN_HDVICP,
                                            (IRESMAN_Params *)&configParams);

    if (IRES_OK != iresStatus) {
        printf("VICP Protocol Registration Failed \n");
        return -1;
    }
    }

#ifdef DEVICE_ID_CHECK
	{
	IRESMAN_AddrSpaceParams addrspaceConfigParams;
    /*
     * Supply initialization information for the ADDRSPACE RESMAN while registering
     *           */
    addrspaceConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    addrspaceConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    addrspaceConfigParams.baseConfig.size = sizeof(IRESMAN_AddrSpaceParams);;

    iresStatus = RMAN_register(&IRESMAN_ADDRSPACE, (IRESMAN_Params *)&addrspaceConfigParams);

    if (IRES_OK != iresStatus) {
        printf("ADDRSPACE Protocol Registration Failed \n");
        return -1;
    }
    printf("ADDRSPACE Protocol Registration Success \n");
	}
#endif
#endif

    /* If the code is running on QT the input parameters are preset as file
     * read for configuration parameters is not possible. For other case the
     * configuration list is read from file and the configuration parameters
     * are parsed from configuration files
     */
#ifdef ON_LINUX
    pfConfigFileList =
        fopen("../../test/testvecs/config/testvecs.cfg", "r");
#else
    pfConfigFileList =
        fopen("../../../test/testvecs/config/testvecs.cfg", "r");
#endif
	if(pfConfigFileList == NULL)
	{
		printf("\n ERROR! - Could Not open Config File %s", pfConfigFileList);
		exit(-1);
	}
configFileCount = 0;
	    /* Interrupt enable related function calls please refer to User
	     * guide for a detailed description of these functions and the 
	     * DM365_IPC_INTC_ENABLE macro usage 
	     */
#ifdef DM365_IPC_INTC_ENABLE
	    /*--------------------------------------------------------------------*/
	    /* Interrupt enable related function calls please refer to User       */
	    /* guide for a detailed description of these functions and the        */ 
	    /* DM365_IPC_INTC_ENABLE macro usage                                  */
	    /* Call the functions to enable ARM926 FIQ and do some basic setup to */
	    /* AINTC to accept KLD INTC (arm968) interupt in FIQ pin of Arm926    */
	    /*--------------------------------------------------------------------*/
#ifndef ON_LINUX
	     ARM926_enable_FIQ();  /* SWI call to enable interrupts */
	     ARM926_INTC_init();   /* Init ARM INTC */
#endif
#endif //DM365_IPC_INTC_ENABLE
    while(!feof(pfConfigFileList))
    {
		configFileCount++;

		/*--------------------------------------------------------------------*/
		/* Clear polling bit of ARM968; This is not required when Interrupt   */
		/* is enabled between ARM926 and ARM968. But disabling needs          */
		/* corresponding change in hdvicp_framework.c file When interrupt is  */ 
		/* enabled poll_word points to a memory location in external memory.  */
		/* When interrupt is disabled it points to a memory location in DTCM  */
		/* of ARM968 - as a way of inter processor signaling.                 */
		/*--------------------------------------------------------------------*/
	    //(*poll_word) = 0x0;

		/* Read Compliance Checking parameter */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%d",&testCompliance);
		}
		else
		{
			break ;
		}

		/* Read Parameters file name */
		if(fgets(line,254, pfConfigFileList))
		{
			sscanf(line,"%s",bConfigFile);
		}
		else
		{
			break ;
		}

		/* Read Input file name */
		if(fgets(line,254, pfConfigFileList))
		{
			sscanf(line,"%s",bInputFile);
		}
		else
		{
			break ;
		}

		/* Read Output/Reference file name */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%s",bEncOutFile);
		}
		else
		{
			break ;
		}

		/* Read Recon file name */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%s",bReconOutFile);
		}
		else
		{
			break ;
		}

        /* Point the param pointer to default parameters from encoder */
        uiTokenCtr = 0;

        /* Set up Token Map for all the input parameters to be read from the
         * configuration file
         */
        sTokenMap[uiTokenCtr].tokenName = "FramesToEncode";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =  &uiNumFramesToBeEncoded;

        sTokenMap[uiTokenCtr].tokenName = "ImageHeight";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =  
            &dynamicparams.inputHeight;

        sTokenMap[uiTokenCtr].tokenName = "ImageWidth";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =  
            &dynamicparams.inputWidth;

        sTokenMap[uiTokenCtr].tokenName = "FrameRate";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =  
            &dynamicparams.targetFrameRate; 

        sTokenMap[uiTokenCtr].tokenName = "BitRate";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = 
            &dynamicparams.targetBitRate;

        sTokenMap[uiTokenCtr].tokenName = "ChromaFormat";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = 
            &params.inputChromaFormat;

        sTokenMap[uiTokenCtr].tokenName = "InterlacedVideo";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &params.inputContentType;
        sTokenMap[uiTokenCtr].tokenName = "IntraPeriod";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =  
            &dynamicparams.intraFrameInterval;

        sTokenMap[uiTokenCtr].tokenName = "RC_PRESET";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &params.rateControlPreset;

        sTokenMap[uiTokenCtr].tokenName = "ENC_PRESET";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.encodingPreset;

        sTokenMap[uiTokenCtr].tokenName = NULL; 
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = NULL;

        /*--------------------------------------------------------------------*/
        /*                    READ INPUT CONFIG FILE                          */
        /*--------------------------------------------------------------------*/
#ifndef ON_LINUX
        pfConfigParamsFile = fopen(bConfigFile, "r");
#else
	/* One ../ should be removed for the config file path to run on linux */
	bChangeDirForConfigFile = bConfigFile;
	bChangeDirForConfigFile += CHANGE_PATH;
	pfConfigParamsFile = fopen(bChangeDirForConfigFile, "r");
#endif
        if(pfConfigParamsFile == NULL) 
        {
            printf("ERROR! - Could Not open Config File %s\n", bConfigFile);
            continue;
        }
        printf("\nReading Configuration file %s...\n",bConfigFile);
        /* pass config file for parsing */
        if(readparamfile(pfConfigParamsFile) != 0)
        {
            printf("ERROR! - Unable to read Config File %s\n", bConfigFile);
            fclose(pfConfigParamsFile);
            continue;
        } 
        fclose(pfConfigParamsFile);

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        fprintf(pfProfFile, "\nConfiguration file: %s...\n",bConfigFile);
#endif //ENABLE_PROFILE_AT_FRM_LVL_ON_926
#ifndef ON_LINUX
        pfInputYUVFile = fopen(bInputFile, "rb");
#else
	/* One ../ should be removed for the config file path to run on linux */
	bChangeDirForConfigFile = bInputFile;
	bChangeDirForConfigFile += CHANGE_PATH;
	pfInputYUVFile = fopen(bChangeDirForConfigFile, "rb");
#endif
        if(pfInputYUVFile == NULL)
        {
            printf("\n ERROR! - Could Not open Input YUV File %s", bInputFile);
            exit(-1);
        }

        /* Compute extended width and extended height */
        uiExtWidth = (dynamicparams.inputWidth + 15) & ~0x0F;
        uiExtHeight = (dynamicparams.inputHeight + 15) & ~0x0F;
		uiFrmPitch = uiExtWidth;

		if(testCompliance)
		{
			printf("Running in reference bit-stream complaince check Mode\n");
		}
		else
		{
			printf("Running in Output Dump Mode\n");
		}

        /* Disable encode output file write if file not specified */
        if(bEncOutFile[0] == '0') 
        {
            bWriteEncodedData = 0; 
        }

        if(bWriteEncodedData)
        {
			if(testCompliance)
			{
				pfOutBitStreamFile = fopen(bEncOutFile, "rb");
	            if(pfOutBitStreamFile == NULL)
	            {
	                printf("\n ERROR! -Could Not open Output bitstream File %s",
	                       bEncOutFile);
	                exit(-1);
	            }
			}
			else
			{
#ifndef ON_LINUX
				pfOutBitStreamFile = fopen(bEncOutFile, "wb");
#else
		
				/* One ../ should be removed for the config file path to run on linux */
				bChangeDirForConfigFile = bEncOutFile ;
				bChangeDirForConfigFile += CHANGE_PATH;
				pfOutBitStreamFile = fopen(bChangeDirForConfigFile, "wb");

#endif
	            if(pfOutBitStreamFile == NULL)
	            {
	                printf("\n ERROR! -Could Not open Output bitstream File %s",
	                       bEncOutFile);
	                exit(-1);
	            }
			}
        }

        /* Disable reconstructed frame file write if file not specified */
        if(bReconOutFile[0] == '0')
        {
            bWriteReconData = 0; 
        }

        if(bWriteReconData)
        {
            XDAS_Int32 uiSize = uiExtWidth * uiExtHeight;
#ifndef ON_LINUX
            pfOutYUVFile = fopen(bReconOutFile, "wb");
#else
				/* One ../ should be removed for the config file path to run on linux */
				bChangeDirForConfigFile = bReconOutFile;
				bChangeDirForConfigFile += CHANGE_PATH;
				pfOutYUVFile = fopen(bChangeDirForConfigFile, "wb");
#endif
            if(pfOutYUVFile == NULL)
            {
                printf("\n ERROR! - Could Not open Input YUV File %s",
                       pfOutYUVFile);
                exit(-1);
            }

            /* Allocate memory for the reconstructed frames */
            pubYRecon = malloc(uiSize * sizeof(XDAS_Int8)); 
            pubURecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
            pubVRecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
        }

        /* Allocate memory for the input frame */
        {
            XDAS_UInt32 uiFrmSize = uiFrmPitch * uiExtHeight;

            pubInY = (XDAS_UInt8 *) malloc(uiFrmSize * sizeof(XDAS_UInt8));
            pubInU =
                (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
            pubInV =
                (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
        }

        /*--------------------------------------------------------------------*/
        /*                        H.264 ENCODER INSTANCE CREATION             */
        /*--------------------------------------------------------------------*/
        /*
         * The process of instance creation has two parts: 
         * - Setting up the creation time Parameters
         * - Calling the XDAIS Create function to create the instance
         */
        /*
         * Set the Create-Time parameters required for setting up the instance 
         * of the H.264 Encoder.
         *
         * As standardized by XDAIS, the structure defining the create time 
         * params is named as \b imod_Params \b and is defined in the file 
         * \b imod.h \b.
         *
         * So for this module the create-time parameter structure is 
         * \b iH264VENC_Params \b defined in \b ih264enc.h \b. 
         * XDAIS also provides default create-time parameter in \b mod_PARAMS 
         * (H264VENC_PARAMS here)\b defined in \b imod.c (ih264enc.c here) \b
         * which can be used for most scenarios. 
         *
         * The code below uses the default create-time parameter set 
         * H264VENC_PARAMS and then modifes few of the fields as necessary
         */

        /* Function for seeting initial parameters. Currently not defined, will
         * defined later.
         * H264VENC_setinitparmas(&params);
         */
        /*--------------------------------------------------------------------*/
        /*                       STATIC PARAMETERS INTIALIZATION              */
        /*--------------------------------------------------------------------*/
        params.size = sizeof(IVIDENC1_Params);
        params.maxBitRate = 10000000;
        params.maxFrameRate = 30000;
        params.maxHeight = MAX_HEIGHT;
        params.maxWidth = MAX_WIDTH;
        params.dataEndianness = XDM_BYTE;
        params.inputContentType = IVIDEO_PROGRESSIVE;
        params.maxInterFrameInterval = 0;
        params.reconChromaFormat = IH264VENC_YUV_420IUV; 
        if(bWriteReconData == 0)
        {
            params.reconChromaFormat = IH264VENC_YUV_420IUV;
        }
        /* Xena hardware provides only single VIMCOP which is indexed by 0 */
        //params.imcop_selector = 0; /* Allways 0 */
        //params.resetHDVICPeveryFrame = 0;

        /* DMA initialization parameter should be set before Encoder creation as
         * DMA will be configured based on these parameters during creation.
         * Setting of these parameters is done through the following function
         * defined in file testapp_idma.c. Application writer can update this
         * file
         */

        /* Encoder Create function - Calls ALG Framework function -
         * ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
         */

        if((handle = H264VENC_create((IALG_Fxns *)&fxns, (IALG_Params*)(&params))) == NULL)
        {
            printf("\nERROR! - Encoder Creation Failed");
			fflush(stdout);
            goto FREE_FRAME_IO_BUFFERS; /* Creation failed - exit the encoder */
        }
        printf("Encoder Creation Done\n");
#ifdef _ENABLE_IRES_EDMA3
		/* Create an instance of an algorithm that implements IALG and IRES_Fxns */
		if (IRES_OK != RMAN_assignResources((IALG_Handle)handle,
											&H264VENC_TI_IRES, /* IRES_Fxns* */
											1 /* scratchId */)) {
		  printf( "\nFailed in assignign resources \
					 Exiting for this configuration..");
		  goto FREE_ENCODER_IO_BUFFERS;
		}
#endif

        /*--------------------------------------------------------------------*/
        /*              Check for any warnings set at create time             */
        /*--------------------------------------------------------------------*/
        status.size = sizeof(IVIDENC1_Status);
		dynamicparams.size= sizeof(IVIDENC1_DynamicParams);
		dynamicparams.refFrameRate = dynamicparams.targetFrameRate;
		dynamicparams.generateHeader = 0;
		dynamicparams.forceFrame = IVIDEO_NA_FRAME;
		dynamicparams.mbDataFlag = 0;
        iErrorFlag = H264VENC_control(
            handle,         // Instance Handle
            XDM_GETSTATUS,  // Command
            (H264VENC_DynamicParams *)&dynamicparams, // Pointer to Dynamic Params structure -Input
            (H264VENC_Status *)&status         // Pointer to the status structure - Output
        );

        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Get Status Info Command Faile\n");
			goto FREE_ENCODER_OBJECT;
		}
		if(status.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
		{
			printf("Parameter not supported\n");
		}
		if(status.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
		{
			printf("Input not supported\n");
		}

        /*--------------------------------------------------------------------*/
        /*            GET H.264 ENCODER INPUT/OUTPUT BUFFER INFORMATION       */ 
        /*--------------------------------------------------------------------*/
        /* The Number of Input output buffers and their sizes are alogrithm 
         * specific. For a genric codec independent application like this, the 
         * buffer information for a codec can be obatined by making a call to 
         * the XDAIS control func - H264VENC_control() with the command 
         * \b XDM_GETBUFINFO\b. The function will return back the number of 
         * input and output arrays and the size of each array. 
         */
		status.size = sizeof(IVIDENC1_Status);
		dynamicparams.size= sizeof(IVIDENC1_DynamicParams);
		dynamicparams.captureWidth = 0;
        iErrorFlag = H264VENC_control(
            handle,         // Instance Handle
            XDM_GETBUFINFO, // Command
            (H264VENC_DynamicParams *)&dynamicparams, // Pointer to Dynamic Params structure -Input
            (H264VENC_Status*)&status         // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Get Buffer Info Command Faile\n");
			goto FREE_ENCODER_OBJECT;
		}

        /*--------------------------------------------------------------------*/
        /*            GET H.264 ENCODER INPUT/OUTPUT BUFFER INFORMATION       */
        /*--------------------------------------------------------------------*/
        /* Based on the Num of buffers requested by the algorithm, the
         * application will allocate for the same here
         */
		inobj.frameHeight = uiExtHeight;
		inobj.frameWidth = uiExtWidth;
		inobj.framePitch = uiFrmPitch;
		if((dynamicparams.captureWidth == 0) ||
		   (dynamicparams.captureWidth < uiExtWidth))
		{
			inobj.framePitch = uiExtWidth;
		}

        if(AllocateH264IOBuffers( 
            status, // status structure - Input
            &inobj, // Pointer to Input Buffer Descriptor - Output 
            &outobj) // Pointer to Output Buffer Descriptor - Output
        )
        {
            printf("Not Enough Memory\n");
            FreeH264IOBuffers(
                &inobj, // Pointer to Input Buffer Descriptor - Input 
                &outobj // Pointer to Output Buffer Descriptor - Input
            );
            goto FREE_FRAME_IO_BUFFERS;
        }
		inobj.frameHeight = uiExtHeight;
		inobj.frameWidth = uiExtWidth;
		inobj.framePitch = uiFrmPitch;
		if((dynamicparams.captureWidth == 0) ||
		   (dynamicparams.captureWidth < uiExtWidth))
		{
			inobj.framePitch = uiExtWidth;
		}

        /*--------------------------------------------------------------------*/
        /*                     SET DYNAMIC INPUT PARAMETERS                   */
        /*--------------------------------------------------------------------*/
		dynamicparams.size= sizeof(IVIDENC1_DynamicParams);
        iErrorFlag = H264VENC_control(
            handle,        // Instance Handle
            XDM_SETPARAMS, // Command
            (H264VENC_DynamicParams *)&dynamicparams,// Pointer to Dynamic structure - Input
            (H264VENC_Status *)&status        // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Set Encoder parameters Command Failed\n");
			goto FREE_ENCODER_IO_BUFFERS;
		}

        /* Initialize Input Arguements */
        inargs.size = sizeof(IVIDENC1_InArgs);
        inargs.inputID = 1;
        inargs.topFieldFirstFlag = XDAS_TRUE;
		//inargs.timeStamp = 0;

        /* Initialize Output Arguments */
        outargs.size = sizeof(IVIDENC1_OutArgs);
        outargs.extendedError = 0;
        outargs.bytesGenerated = 0;
        outargs.encodedFrameType = IVIDEO_NA_FRAME;
        outargs.inputFrameSkip = IVIDEO_FRAME_ENCODED;
        outargs.outputID = 1;
		//outargs.numPackets = 0;
		//outargs.packetSize = PACKET_SIZES;

#ifdef _PROFILE
        fprintf(profFilePtr, "%s\n", bConfigFile);
#endif //_PROFILE

		/* If the number of Frames is input as 0, interpret that as number
		 * of frames in the input unknown and encode till file end
		 */
		if(uiNumFramesToBeEncoded == 0)
		{
			uiNumFramesToBeEncoded = MAX_FRAMES_TO_ENCODE;
		}

		iSkipCnt = 0;
		uiNumBytesWritten = 0;
        printf("\nStarting Encode...\n");
        /*--------------------------------------------------------------------*/
        /*                                  ENCODE LOOP                       */
        /*--------------------------------------------------------------------*/
		uiNumFrames = 0;
		while(uiNumFrames < uiNumFramesToBeEncoded &&
		      !feof(pfInputYUVFile))
        /*for(uiNumFrames = 0; uiNumFrames < uiNumFramesToBeEncoded;
            uiNumFrames++)*/
        {
            /* Implement any Dynamic Parameter changes here
             * (Call H264VENC_control()
             * with approriate command and parameters).
             */
#ifdef UPDATE_PARAMS_AT_RUN_TIME
#endif //UPDATE_PARAMS_AT_RUN_TIME
            /*----------------------------------------------------------------*/
            /*                              SET INPUTS                        */
            /*----------------------------------------------------------------*/
            /* The Inputs for the encode call are: 
             * - YUV Frame - To be read from the input file. 
             * - Any Dynamic Parameter Changes.
             */
            printf("Reading Input Frame - ");
            fflush(stdout);
            iStatus = ReadInputData(
                inobj, 
            	dynamicparams.inputWidth,
            	dynamicparams.inputHeight,
                uiFrmPitch, 
                uiExtHeight,
                pfInputYUVFile
            );

			if(iStatus)
			{
	            printf("Input Frame Read Failed\n");
	            break;
			}
			else
			{
	            printf("Input Frame Read Done\n");
	            fflush(stdout);
			}
#ifdef TEST_FORCE_FRAME
        /* force every alternate frame to IDR frame */
        if(!(uiFrameNum & 0x01))
		{
		    dynamicparams.forceFrame = IVIDEO_IDR_FRAME;
		}
#endif //TEST_FORCE_FRAME

            /* Update InArgs */

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
            /* Configuring timer-0 to start counting for the start portion
             * of process call
             */            
            profileInit(0);
            profileStart(0);
#endif/* ENABLE_PROFILE_AT_FRM_LVL_ON_926 */

            /*----------------------------------------------------------------*/
            /*                          ENCODE FRAME                          */
            /*----------------------------------------------------------------*/
#ifdef PROFILE_ONLINUX
            encoder_timeptr = &encoder_time;
            time_before_process = gettimeofday(encoder_timeptr, NULL);
	    time_before_process = encoder_timeptr->tv_usec;
            //printf("time before = %d\n",encoder_timeptr->tv_usec);
#endif
			inargs.size = sizeof(IVIDENC1_InArgs);
			outargs.size = sizeof(IVIDENC1_OutArgs);
			inargs.topFieldFirstFlag = 0;
            iErrorFlag = H264VENC_encode (
                handle,   // Instance Handle    - Input
                &inobj,   // Input Buffers      - Input
                &outobj,  // Output Buffers     - Output
                (H264VENC_InArgs *)&inargs,  // Input Parameters   - Input
                (H264VENC_OutArgs *)&outargs  // Output Parameters  - Output
            );

#ifdef PROFILE_ONLINUX
            time_after_process = gettimeofday(encoder_timeptr, NULL);
            //printf("time After = %d\n",encoder_timeptr->tv_usec);
            //printf("time before = %d, time after = %d\n",time_before_process,time_after_process);
	    if(encoder_timeptr->tv_usec <= time_before_process)
	    {

	    	encoder_timeptr->tv_usec += 1000000;
	    }
	    total_time_p += (encoder_timeptr->tv_usec - time_before_process);
	    if(frame_count_p++ == 14)
	    {
		printf("\n");
            	printf("TIME TAKEN TO ENCODE 15 FRAMES AT PROCESS LEVEL = %d\n",total_time_p);
		printf("\n");
		total_time_p = 0;
		frame_count_p = 0;
	    }
#endif
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
            profileEd = (XDAS_UInt32)profileEnd(0);
            ProfDataArray[uiNumFrames] = profileSrt + profileEd + profile968;
#endif/* ENABLE_PROFILE_AT_FRM_LVL_ON_926 */

            if(iErrorFlag == XDM_EFAIL)
            {
                /* Get Detailed information regarding the failure by querying
                 * the encoder with the control function.
                 */
                H264VENC_control(
                    handle,         // Instance Handle
                    XDM_GETSTATUS,  // Command - GET STATUS
                   (H264VENC_DynamicParams *)&dynamicparams, // Input
                   (H264VENC_Status *)&status         // Output
                );

                printf("Encoder Returned a Failure\n");
                printf("\tFrame No              : %d\n", uiNumFrames);
                printf("\tError Status          : %d\n", iErrorFlag);
                printf("\tExtended Error Status : %d\n",
                       status.extendedError);
                goto FREE_ENCODER_IO_BUFFERS;
            }

            if(status.extendedError == XDM_FATALERROR)
            {
                goto FREE_ENCODER_IO_BUFFERS; 
            }
            else
            {
                uiNumBytesWritten += outargs.bytesGenerated;
                if(outargs.inputFrameSkip == IVIDEO_FRAME_SKIPPED)
                {
					iSkipCnt++;
                    printf("Frame : %d Skipped: ", uiNumFrames);
                }
                else
                {
                    printf("Frame : %d Encoded: ", uiNumFrames);
                }
	            printf("Bytes Generated : %d\n",
	                   outargs.bytesGenerated); 
			

			
            }
		
            /*----------------------------------------------------------------*/
            /*                      ADDITIONAL PROCESSING                     */
            /*----------------------------------------------------------------*/
            /* Currently there is no additional processing -                  */

#ifdef MB_LOOP_PROFILE
            /* Write the profile values copied from DTCM during the encode call
             * to file
             */
            {
                XDAS_UInt32 cnt;
                fprintf(profFilePtr, "Frame : %d\n", uiNumFrames);
                for(cnt = 1; cnt <= profArr[0]; cnt++)
                {
                    fprintf(profFilePtr, "Cycles %d\n", profArr[cnt]);
                }
            } 
#endif //MB_LOOP_PROFILE

#ifdef MB_TTL_PROFILE
            printf("Total MB Loop Cycles %d\n", profArr[1]);
#endif //MB_TTL_PROFILE

#ifdef FRAME_PROFILE
            printf("Frame Profile %d\n", profArr[0]);
#endif //FRAME_PROFILE

            /*----------------------------------------------------------------*/
            /*                         OUTPUT DATA WRITE                      */
            /*----------------------------------------------------------------*/
            /* Write out the Encoded bit-stream to output file */
            retVal = XDM_EOK;
            if(bWriteEncodedData && outargs.bytesGenerated)
			{
                printf("Writing encoded frame to file\n");
                retVal = WriteDataOut(outargs, pfOutBitStreamFile,
                                      testCompliance);
				if(testCompliance && (retVal == XDM_EFAIL))
				{
			        printf("\n\n reference bit-stream complaince check FAILED");
			        printf(" at this frame\n");			        
			        goto FREE_ENCODER_IO_BUFFERS;	        			  
				}
            }

            /* Write out the reconstructed frame. This is debug feature only and
             * will be disabled in the final code release
             */
            if(bWriteReconData && outargs.reconBufs.numBufs)
            {
                XDAS_UInt8 *pubInBufY;
                XDAS_UInt8 *pubInBufUV;
                XDAS_UInt32 uiRecPitch = (XDAS_UInt32)
                outargs.videncOutArgs.reconBufs.framePitch;

                pubInBufY =
                    (XDAS_UInt8 *)outargs.reconBufs.
                        bufDesc[0].buf; 
                pubInBufUV =
                    (XDAS_UInt8 *)outargs.reconBufs.
                        bufDesc[1].buf;

                /* The reconstructed frame in the encoder is padded format and
                 * the Chroma component is in interleaved format. This is
                 * converted by de-interleaving chroma components.
                 */
                GetReconFrame (
                    pubYRecon,
                    pubURecon,
                    pubVRecon,
                    pubInBufY,
                    pubInBufUV,
                    uiExtWidth,
                    uiExtHeight,
                    uiRecPitch,
                    0
                );
				printf("Writing Reconstructed Frame - ");
                WriteReconOut(
                    pubYRecon,
                    pubURecon,
                    pubVRecon,
                    uiExtWidth,
                    uiExtHeight,
                    pfOutYUVFile
                );
				printf("Done\n");
            }

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
            printf("Profile: %d %d %d\n", profileSrt, profile968, profileEd);
            fprintf(pfProfFile, "Profile: %8d %8d %8d\n",
            		profileSrt, profile968, profileEd);
#endif/* ENABLE_PROFILE_AT_FRM_LVL_ON_926 */
			uiNumFrames++;
        }//0 - uiNumFramesTobeEncoded

        /*--------------------------------------------------------------------*/
        /*             FREE H.264 ENCODER INPUT/OUTPUT BUFFERS                */
        /*--------------------------------------------------------------------*/
FREE_ENCODER_IO_BUFFERS:
        FreeH264IOBuffers(
            &inobj, // Pointer to Input Buffer Descriptor - Input 
            &outobj // Pointer to Output Buffer Descriptor - Input
        );

        /*--------------------------------------------------------------------*/
        /*                           PRINT STATS                              */
        /*--------------------------------------------------------------------*/
        if(uiNumFrames == 0)
        {
            uiNumFrames = 1; /* To avoid division with zero */
        }
        printf("\n --------------  SUMMARY --------------------\n");fflush(stdout);
        printf("  Total number of Frames          = %d\n",
            (XDAS_UInt32)uiNumFrames);fflush(stdout);
		printf("  Encoded: %8d, Skipped: %8d\n",
			(XDAS_UInt32)uiNumFrames - iSkipCnt, iSkipCnt);fflush(stdout);
        printf("  Bit Rate at 30 frames/Sec       = %d Kbps\n",(
            XDAS_UInt32)(((uiNumBytesWritten*8*30)/uiNumFrames)/1000));fflush(stdout);
        printf("  Width and Height                = %d, %d \n",
            dynamicparams.inputWidth,
            dynamicparams.inputHeight);fflush(stdout);
        printf (" --------------    END   --------------------\n");fflush(stdout);

        /*--------------------------------------------------------------------*/
        /*                 FREE Frame INPUT & RECON BUFFERS                   */
        /*--------------------------------------------------------------------*/
		H264VENC_control(handle, XDM_RESET, (H264VENC_DynamicParams *)&dynamicparams/*NULL*/,(H264VENC_Status*) &status/*NULL*/);
FREE_FRAME_IO_BUFFERS:
        free(pubInY); 
        free(pubInU); 
        free(pubInV);

        if(bWriteReconData)
        {
            free(pubYRecon);
            free(pubURecon);
            free(pubVRecon);
        }

        /* Close all input and output data files */
        fclose(pfInputYUVFile);
        if(bWriteEncodedData)
        {
            fclose(pfOutBitStreamFile);
        }
        if(bWriteReconData)
        {
            fclose(pfOutYUVFile);
        }
    }/* End of 'config file list' while() loop */

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle),
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
        printf("Free Resource Failed \n");
        return -1;
    }
#endif
FREE_ENCODER_OBJECT:
        H264VENC_delete(handle);

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Unregister the protocol
     */
    if (IRES_OK != RMAN_unregister(&IRESMAN_EDMA3CHAN)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }

    RMAN_exit();
#endif
    /*------------------------------------------------------------------------*/
    /* Signal ARM968 to terminate wait and goto sleep                         */
    /*------------------------------------------------------------------------*/
    //(*poll_word) = 0xFFFFFFFF;

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
    /* Close Profile Log file */
    fclose(pfProfFile);
#endif /* ENABLE_PROFILE_AT_FRM_LVL_ON_926 */

#ifdef _PROFILE
    fclose(profFilePtr);
#endif //_PROFILE

    fclose(pfConfigFileList);
}/* main */



/*---------------------------------------------------------------------------*/
/*                           LOCAL STATIC FUNCTIONS                          */
/*---------------------------------------------------------------------------*/
/*===========================================================================*/
/**
*@func   H264VENC_setinitparams
*
*@brief  Setting of creation time parameters from the config file data
*
*@param  params
*        Pointer to the create time parameters
*
*@return Int
*        IALG_EOK - Initialization successful
*        IALG_EFAIL - Initialization failed
*
*@see    None
*
*@note   
*/
/*===========================================================================*/
Int H264VENC_setinitparams(H264VENC_Params *params)
{
    return(IALG_EOK);
}/* H264VENC_setinitparams */



/*===========================================================================*/
/**
*@func   H264VENC_setrunparams
*
*@brief  Setting of run-time time parameters from the config file data
*
*@param  params
*        Pointer to the Dynamic parameters structure
*
*@return Int
*        IALG_EOK - Initialization successful
*        IALG_EFAIL - Initialization failed
*
*@see    None
*
*@note   
*/
/*===========================================================================*/
Int H264VENC_setrunparams(H264VENC_DynamicParams *params)
{
    /* set common run time parameters */
    params->videncDynamicParams.captureWidth = 176;
    params->videncDynamicParams.inputHeight  = 144;
    params->videncDynamicParams.inputWidth   = 176;

    return(IALG_EOK);
}/* H264VENC_setrunparams */



/*===========================================================================*/
/**
*@func   AllocateH264IOBuffers
*
*@brief  Allocate memory buffers as required by the algorithm for the input and 
*        output
*
*@param  H264EncStatus
*        Algorithm status structure.
*
*@param  ptH264EncInpBufDesc
*        Pointer to the buffer descriptor structure with requirements for the 
*        input buffers.
*
*@param  ptH264EncOutBufDesc
*        Pointer to the buffer descriptor structure with requirements for the 
*        output buffers.
*
*@return XDAS_Int32
*        0 - Allocation Successful
*        -1 - Allocation Failure
*
*@note   
*/
/*===========================================================================*/
XDAS_Int32 AllocateH264IOBuffers(IVIDENC1_Status H264EncStatus,
                                 IVIDEO1_BufDescIn *ptH264EncInpBufDesc, 
                                 XDM_BufDesc *ptH264EncOutBufDesc)
{
    XDAS_Int32 i; 

    /*------------------------------------------------------------------------*/
    /*                           ALLOCATE INPUT BUFFERS                       */
    /*------------------------------------------------------------------------*/
    ptH264EncInpBufDesc->numBufs = 
        H264EncStatus.bufInfo.minNumInBufs;

    for( i = 0; i < H264EncStatus.bufInfo.minNumInBufs; i++)
    {
        /* Assign size for the current buffer */
        ptH264EncInpBufDesc->bufDesc[i].bufSize = 
            H264EncStatus.bufInfo.minInBufSize[i];

        /* Allocate memory for buffer pointer */
        ptH264EncInpBufDesc->bufDesc[i].buf = 
            (XDAS_Int8 *) CMEM_alloc(ptH264EncInpBufDesc->bufDesc[i].bufSize *
                                sizeof(XDAS_Int8),&memParams);
       printf("Size of I/P buffer:%d\n",ptH264EncInpBufDesc->bufDesc[i].bufSize);
        if(ptH264EncInpBufDesc->bufDesc[i].buf == NULL)
        {
            return (-1); /* Memory not allocated, return failure */
        }
    }

    /*------------------------------------------------------------------------*/
    /*                          ALLOCATE OUTPUT BUFFERS                       */
    /*------------------------------------------------------------------------*/
    ptH264EncOutBufDesc->numBufs = 
        H264EncStatus.bufInfo.minNumOutBufs;

    ptH264EncOutBufDesc->bufSizes = 
        (XDAS_Int32 *) malloc(ptH264EncOutBufDesc->numBufs *
                              sizeof(XDAS_Int32));
    if(ptH264EncOutBufDesc->bufSizes == NULL)
    {
        return (-1); /* Memory not allocated, return failure */
    }

    ptH264EncOutBufDesc->bufs = 
        (XDAS_Int8 **) malloc(ptH264EncOutBufDesc->numBufs *
                              sizeof(XDAS_Int8 *));
    if(ptH264EncOutBufDesc->bufs == NULL)
    {
        return (-1); /* Memory not allocated, return failure */
    }

    for( i = 0; i < ptH264EncOutBufDesc->numBufs; i++)
    {
        /* Assign size for the current buffer */
        ptH264EncOutBufDesc->bufSizes[i] = 
            H264EncStatus.bufInfo.minOutBufSize[i];

        /* Allocate memory for buffers */
        ptH264EncOutBufDesc->bufs[i] = 
            (XDAS_Int8 *) CMEM_alloc(ptH264EncOutBufDesc->bufSizes[i] *
                                 sizeof(XDAS_Int8), &memParams);
        if(ptH264EncOutBufDesc->bufs[i] == NULL)
        {
            return (-1); /* Memory not allocated, return failure */
        }
    }
  
    return(0);
}/* AllocateH264IOBuffers */



/*===========================================================================*/
/**
*@func   FreeH264IOBuffers
*
*@brief  Free buffers as used by the algorithm for the input and output. This 
*        function is called at the end of the encoding process to free the used
*        buffers and also when function AllocateH264IOBuffers fails to release
*        partially allloated buffers.
*
*@param  ptH264EncInpBufDesc
*        Pointer to the buffer descriptor structure with requirements for the 
*        input buffers.
*
*@param  ptH264EncOutBufDesc
*        Pointer to the buffer descriptor structure with requirements for the 
*        output buffers.
*
*@return void
*
*@note   
*/
/*===========================================================================*/
void FreeH264IOBuffers(IVIDEO1_BufDescIn *ptH264EncInpBufDesc, 
                       XDM_BufDesc *ptH264EncOutBufDesc)
{
    XDAS_Int32 i; 
  
    /*------------------------------------------------------------------------*/
    /*                               FREE INPUT BUFFERS                       */
    /*------------------------------------------------------------------------*/
    for(i = 0; i < ptH264EncInpBufDesc->numBufs; i++)
    {   
        if(ptH264EncInpBufDesc->bufDesc[i].buf != NULL)
        {
            CMEM_free(ptH264EncInpBufDesc->bufDesc[i].buf, &memParams);
        }
        else
        {
            return;
        }
    }
    ptH264EncInpBufDesc->numBufs = 0;

    /*------------------------------------------------------------------------*/
    /*                              FREE OUTPUT BUFFERS                       */
    /*------------------------------------------------------------------------*/
    if(ptH264EncOutBufDesc->bufSizes == NULL)
    {
        return;
    }
    if(ptH264EncOutBufDesc->bufs == NULL)
    {
        return;
    }
    for(i = 0; i < ptH264EncOutBufDesc->numBufs; i++)
    {
        if(ptH264EncOutBufDesc->bufs[i] != NULL)
        {
            CMEM_free(ptH264EncOutBufDesc->bufs[i], &memParams);
        }
        else
        {
            break;
        }
    }
    free(ptH264EncOutBufDesc->bufs);
    free(ptH264EncOutBufDesc->bufSizes);
    ptH264EncOutBufDesc->numBufs = 0;
}/* FreeH264IOBuffers */



/*===========================================================================*/
/**
*@func   ReadInputData
*
*@brief  The function reads the input YUV frame from file and converts the data
*        to chroma interleave format for input to the encoder library. In case 
*        of QT execution the frame is read from memory.
*
*@param  ptH264EncInpBufDesc
*        Pointer to the buffer descriptor structure with requirements for the 
*        input buffers.
*
*@param  uiPicWidth
*        Input Picture Width
*
*@param  uiPicHeight
*        output buffers.
*
*@param  pfInYUVFile
*        File Pointer to the input YUV File
*
*@return XDAS_Int32
*        0 - Read Input Succesful
*        1 - Read Input Failure
*
*@note   
*/
/*===========================================================================*/
XDAS_Int32 ReadInputData(IVIDEO1_BufDescIn tInpBufferDesc,
						 XDAS_UInt32 uiOrgWidth,
						 XDAS_UInt32 uiOrgHeight, 
                         XDAS_UInt32 uiExtWidth, 
                         XDAS_UInt32 uiExtHeight,
                         FILE *pfInYUVFile)
{
    XDAS_UInt8 *pubSubPictY;
    XDAS_UInt8 *pubSubPictUV;
    XDAS_UInt32 uiLineCnt;
    XDAS_Int32 iStatus = 0;

    /* Read the current input frame from the input YUV File */
	if(uiOrgWidth == uiExtWidth)
	{
		XDAS_Int32 iFrmSize = (uiOrgWidth * uiOrgHeight);

		if(fread((Void *)pubInY, 1, iFrmSize, pfInYUVFile) != iFrmSize)
		{
	        iStatus = -1;
		}
		iFrmSize >>= 2;
		if(fread((Void *)pubInU, 1, iFrmSize, pfInYUVFile) != iFrmSize)
		{
	        iStatus = -1;
		}
		if(fread((Void *)pubInV, 1, iFrmSize, pfInYUVFile) != iFrmSize)
		{
	        iStatus = -1;
		}
	}
	else
	{
		pubSubPictY = pubInY;
		for(uiLineCnt = 0; uiLineCnt < uiOrgHeight; uiLineCnt++)
		{
		    if(fread((Void *)pubSubPictY, 1, uiOrgWidth, pfInYUVFile) !=
		    	uiOrgWidth)
		    {
		        iStatus = -1;
		    }
			pubSubPictY += uiExtWidth;
		}

		pubSubPictUV = pubInU;
		for(uiLineCnt = 0; uiLineCnt < (uiOrgHeight >> 1); uiLineCnt++)
		{
		    if(fread((Void *)pubSubPictUV, 1, (uiOrgWidth >> 1), pfInYUVFile) != 
		       (uiOrgWidth >> 1))
		    {
		        iStatus = -1;
		    }
			pubSubPictUV += (uiExtWidth >> 1);
		}

		pubSubPictUV = pubInV;
		for(uiLineCnt = 0; uiLineCnt < (uiOrgHeight >> 1); uiLineCnt++)
		{
		    if(fread((Void *)pubSubPictUV, 1, (uiOrgWidth >> 1), pfInYUVFile) != 
		       (uiOrgWidth >> 1))
		    {
		        iStatus = -1;
		    }
			pubSubPictUV += (uiExtWidth >> 1);
		}
	}

    /* Convert input YUV frame data into chroma interleaved foramt and store it 
     * into buffers acllocated by the system for the input YUV 
     */
    if(!iStatus)
    {
        pubSubPictY = (XDAS_UInt8 *)tInpBufferDesc.bufDesc[0].buf; 
        pubSubPictUV = (XDAS_UInt8 *)tInpBufferDesc.bufDesc[1].buf; 
        DoChromaInterleave(
            pubInY, 
            pubInU, 
            pubInV, 
            pubSubPictY, 
            pubSubPictUV, 
            uiExtWidth, 
            uiExtHeight
        );
    }

    return(iStatus);  
}/* ReadInputData */



/*===========================================================================*/
/**
*@brief  The encoder data accepts Luma data in raster order and the chroma in
*        interleaved format. This function reads the raster input and converts
*        chroma components to UV interleave format. The Luma component is copied
*        as it is.
* 
*@param  pubYFrameData
*        Pointer to the Y component of the raster-scan frame. 
*
*@param  pubUFrameData
*        Pointer to the U component of the raster-scan frame. 
*
*@param  pubVFrameData
*        Pointer to the V component of the raster-scan frame. 
*
*@param  pubSubPictY
*        Pointer to the Luminance (Y) component of the input frame data 
*        for the encoder
*
*@param  pubSubPictUV
*        Pointer to the Chrominance (UV) component of the input frame data
*        for the encoder
*
*@param  uiPicWidth
*        Width of the input picture.
*
*@param  uiPicHeight
*        Heigth of the input picture.
*
*@return None
*
*@see    None
*
*@note   The Y component is copied as it is. This can be avoided.
*/
/*===========================================================================*/
void
DoChromaInterleave(
    unsigned char *pubYFrameData, 
    unsigned char *pubUFrameData, 
    unsigned char *pubVFrameData, 
    unsigned char *pubSubPictY, 
    unsigned char *pubSubPictUV, 
    unsigned int uiPictWidth, 
    unsigned int uiPictHeight) 
{
    unsigned short j,k;
    unsigned char *pubSrcY, *pubSrcU, *pubSrcV;
    unsigned char *pubDst;

    /*------------------------------------------------------------------------*/
    /*                          COPY LUMINANCE DATA                           */
    /*------------------------------------------------------------------------*/
    pubDst = pubSubPictY;
    for(j = 0; j < uiPictHeight; j++)
    {
        pubSrcY = pubYFrameData + (j * uiPictWidth);               
        memcpy(pubDst, pubSrcY, uiPictWidth); 
        pubDst += uiPictWidth;
    }
  
    /*------------------------------------------------------------------------*/
    /*                 CHROMA INTERLEAVE                                      */
    /*------------------------------------------------------------------------*/
    uiPictHeight >>= 1; 
    uiPictWidth >>= 1;
    pubDst = pubSubPictUV;
    for(j = 0; j < uiPictHeight; j++)
    {
        unsigned char *pubCurDst;

        pubSrcU = pubUFrameData + (j * uiPictWidth);
        pubSrcV = pubVFrameData + (j * uiPictWidth);
        pubCurDst = pubDst; 
        for(k = 0; k < uiPictWidth; k++)
        {
            *pubCurDst++ = *pubSrcU++; 
            *pubCurDst++ = *pubSrcV++;
        }
        pubDst += (uiPictWidth << 1);
    }
}/* DoChromaInterleave */



/*===========================================================================*/
/**
*@brief  This function copies the reconstructed frame returned by the encoder
*        library to the application memory. The reconstructed frame contains
*        frame data with padding and the chroma data is in interleaved format.
*        This function extracts the proper frame data and de-interleaves the
*        chroma data.
* 
*@param  pubYFrameData
*        Pointer to the Y component of the raster-scan frame. 
*
*@param  pubUFrameData
*        Pointer to the U component of the raster-scan frame. 
*
*@param  pubVFrameData
*        Pointer to the V component of the raster-scan frame. 
*
*@param  pubSubPictY
*        Pointer to the Luminance (Y) component of the recontructed frame.
*
*@param  pubSubPictUV
*        Pointer to the Chrominance (UV) component of the reconstructed frame.
*
*@param  uiPicWidth
*        Width of the input picture.
*
*@param  uiPicHeight
*        Heigth of the input picture.
*
*@return None
*
*@see    None
*
*@note   The recontructed frame returned by the encoder library is in encoder
*        allocated space. This is not supposed to be exposed. Also, the 
*        reconstructed frame widths should be same for Luma and chroma
*        components as per XDM 1.0. These 2 rules are being flouted by this
*        function. So, this function should be used ONLY FOR DEBUG PURPOSE.
*/
/*===========================================================================*/
void
GetReconFrame (
    unsigned char *pubYFrameData,
    unsigned char *pubUFrameData,
    unsigned char *pubVFrameData,
    unsigned char *pubSubPictY,
    unsigned char *pubSubPictUV,
    unsigned int uiPictWidth,
    unsigned int uiPictHeight,
    unsigned int uiRecWidth,
    unsigned int uiContentType)
{
    unsigned short j,k;
    unsigned char *pubSrc;
    unsigned char *pubDstY, *pubDstU, *pubDstV;

    /*------------------------------------------------------------------------*/
    /*                           COPY LUMINANCE DATA                          */
    /*------------------------------------------------------------------------*/
    pubSrc = pubSubPictY;
    /* uiRecWidth = uiPictWidth + (PAD_Y_HORIZ << 1);*/
    /* pubSrc += (PAD_Y_PROG_VERT * uiRecWidth) + PAD_Y_HORIZ; */
    for(j = 0; j < uiPictHeight; j++)
    {
        pubDstY = pubYFrameData + (j * uiPictWidth);
        memcpy(pubDstY, pubSrc, uiPictWidth); 
        pubSrc += uiRecWidth;
    }
  
    /*------------------------------------------------------------------------*/
    /*                          COPY CHROMINANCE DATA                         */
    /*------------------------------------------------------------------------*/
    /* uiRecWidth = uiPictWidth + (PAD_UV_HORIZ << 1); */
    uiPictHeight >>= 1;
    uiPictWidth >>= 1;
    pubSrc = pubSubPictUV;
    /* pubSrc += (PAD_UV_PROG_VERT * uiRecWidth) + PAD_UV_HORIZ; */
    for(j = 0; j < uiPictHeight; j++)
    {
        unsigned char *pubCurSrc; 
        pubDstU = pubUFrameData + (j * uiPictWidth);
        pubDstV = pubVFrameData + (j * uiPictWidth);
        pubCurSrc = pubSrc; 
        for(k = 0; k < uiPictWidth; k++)
        {
            *pubDstU++  = *pubCurSrc++; 
            *pubDstV++  = *pubCurSrc++;
        }
        pubSrc += uiRecWidth;
    }
}/* GetReconFrame */



/*===========================================================================*/
/**
*@func   WriteReconOut
*
*@brief  The function writes the reconstructed frame to the file.
*
*@param  pubReconY
*        Pointer to the memory location containing reconstructed Luma
*        input buffers.
*
*@param  pubReconU
*        Pointer to the memory location containing reconstructed Chr(U)
*        input buffers.
*
*@param  pubReconV
*        Pointer to the memory location containing reconstructed Chr(V)
*        input buffers.
*
*@param  uiWidth
*        Picture Width
*
*@param  uiHeight
*        Picture Height
*
*@param  pfOutYUVFile
*        File Pointer to the file for writing reconstructed YUV frame 
*
*@return XDAS_Int32
*        0 - Output Write Succesful
*        1 - Output Write Failure
*
*@note   
*/
/*===========================================================================*/
XDAS_Int32 WriteReconOut(XDAS_UInt8* pubReconY, 
                         XDAS_UInt8* pubReconU, 
                         XDAS_UInt8* pubReconV, 
                         XDAS_Int32 uiWidth, 
                         XDAS_Int32 uiHeight, 
                         FILE *pfOutYUVFile)
{
    XDAS_Int32 uiSize = uiWidth * uiHeight;

    /*------------------------------------------------------------------------*/
    /*                        WRITE THE BITSTREAM                             */
    /*------------------------------------------------------------------------*/
    fwrite(pubReconY, 1, uiSize, pfOutYUVFile); 
    fwrite(pubReconU, 1, (uiSize >> 2), pfOutYUVFile); 
    fwrite(pubReconV, 1, (uiSize >> 2), pfOutYUVFile); 

    return(0);
}



/*===========================================================================*/
/**
*@func   WriteDataOut
*
*@brief  The function writes the encoded bitstream to the file.
*
*@param  tInBufferDesc
*        Pointer to the XDM_BufDesc object containing output bitstream
*        information.
*
*@param  pfOutBitStreamFile
*        File Pointer to the file for writing encoded stream 
*
*@param  iMode
*        Write Mode
*
*@return XDAS_Int32
*        0 - Output Write Succesful
*        1 - Output Write Failure
*
*@note   
*/
/*===========================================================================*/
XDAS_Int32 WriteDataOut(IVIDENC1_OutArgs outArgs, 
                        FILE *pfOutBitStreamFile, 
                        XDAS_Int32 iMode)
{
	XDAS_Int32 retVal = XDM_EOK;
	XDAS_Int8 *refData;
	retVal = XDM_EOK;
    /*------------------------------------------------------------------------*/
    /*                        WRITE THE BITSTREAM                             */
    /*------------------------------------------------------------------------*/
	if(iMode)
	{
	   	refData = (XDAS_Int8*)malloc(outArgs.bytesGenerated);
       	fread(refData, 1, outArgs.bytesGenerated, pfOutBitStreamFile);
    	if(memcmp(refData, outArgs.encodedBuf.buf, outArgs.bytesGenerated))
    	{
      		retVal = XDM_EFAIL;
     	}

		free(refData);
	}
	else
	{
        fwrite(outArgs.encodedBuf.buf, sizeof(XDAS_Int8),
               outArgs.bytesGenerated, pfOutBitStreamFile);
    	fflush(pfOutBitStreamFile);
	}

    return(retVal);
}/* WriteDataOut */



/*===========================================================================*/
/**
*@func   GetConfigFileContent
*
*@brief  Reads the configuration file content in a buffer and returns the  
*        address of the buffer 
*
*@param  fname
*        Pointer to the configuration file.
*
*@return XDAS_Int8 *
*        Pointer to memory loaction holding configuration parameters
*
*@note   
*/
/*===========================================================================*/
XDAS_Int8 *GetConfigFileContent (FILE *fname)
{
    XDAS_Int32 FileSize;

    if (0 != fseek (fname, 0, SEEK_END))
    {
        return 0;
    }

    FileSize = ftell (fname);
    if (FileSize < 0 || FileSize > 20000)
    {
        return 0;
    }

    if (0 != fseek (fname, 0, SEEK_SET))
    {
        return 0;
    }

    /* Note that ftell() gives us the file size as the file system sees it.
     * The actual file size, as reported by fread() below will be often
     * smaller due to CR/LF to CR conversion and/or control characters after
     * the dos EOF marker in the file.
     */
    FileSize = fread (buf, 1, FileSize, fname);
    buf[FileSize] = '\0';
    fclose (fname);

    return buf;
}/* GetConfigFileContent */



/*===========================================================================*/
/*!
*@func   ParameterNameToMapIndex
*
*@brief  Returns the index number from sTokenMap[] for a given parameter name.
*
*@param  s
*        parameter name string
*
*@return The index number if the string is a valid parameter name, -1 for error
*
*@note   
*/
/*===========================================================================*/
XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s)
{
    XDAS_Int32 i = 0;

    while (sTokenMap[i].tokenName != NULL)
    {
        if (0==strcmp (sTokenMap[i].tokenName, s))
            return i;
        else
            i++;
    }

    return -1;
}/* ParameterNameToMapIndex */



/*===========================================================================*/
/*!
*@func   ParseContent
*
*@brief  Parses the character array buf and writes global variable input.This is
*        necessary to facilitate the addition of new parameters through the 
*        sTokenMap[] mechanism. Need compiler-generated addresses in sTokenMap.
*
*@param  buf     
*        Pointer to the buffer to be parsed
*
*@param  bufsize 
*        size of buffer
*
*@return XDAS_Int32
*        0 - Parsing Successful
*        -1 - Parsing Failure
*
*@note   
*/
/*===========================================================================*/
XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize)
{
    XDAS_Int8 *items[MAX_ITEMS_TO_PARSE];
    XDAS_Int32 MapIdx;
    XDAS_Int32 item = 0;
    XDAS_Int32 InString = 0, InItem = 0;
    XDAS_Int8 *p = buf;
    XDAS_Int8 *bufend = &buf[bufsize];
    XDAS_Int32 IntContent;
    XDAS_Int32 i;
    FILE *fpErr = stderr;

    /*------------------------------------------------------------------------*/
    /*                                STAGE ONE                               */
    /*------------------------------------------------------------------------*/
    /* Generate an argc/argv-type list in items[], without comments and 
     * whitespace. This is context insensitive and could be done most easily
     * with lex(1).
     */
    while (p < bufend)
    {
        switch (*p)
        {
        case 13:
            p++;
            break;
        case '#': /* Found comment */
            *p = '\0'; /* Replace '#' with '\0' in case of comment */
            /* immediately following integer or string
             * Skip till EOL or EOF, whichever comes first
             */
            while (*p != '\n' && p < bufend)  
            p++;
            InString = 0;
            InItem = 0;
            break;
        case '\n':
            InItem = 0;
            InString = 0;
            *p++='\0';
            break;
        case ' ':
        case '\t': /* Skip whitespace, leave state unchanged */
            if (InString)
                p++;
            else
            {   /* Terminate non-strings once whitespace is found */
                *p++ = '\0';
                InItem = 0;
            }
            break;
        case '"': /* Begin/End of String */
            *p++ = '\0';
            if (!InString)
            {
                items[item++] = p;
                InItem = ~InItem;
            }
            else
                InItem = 0;
                InString = ~InString; /* Toggle */
            break;
        default:
            if (!InItem)
            {
                items[item++] = p;
                InItem = ~InItem;
            }
            p++;
        }
    }

    item--;
    for (i=0; i<item; i+= 3)
    {
        if (0 > (MapIdx = ParameterNameToMapIndex (items[i])))
        {
            fprintf(fpErr, "\nParameter Name '%s' not recognized.. ", items[i]);
            return -1;
        }

        if (strcmp ("=", items[i+1]))
        {
            fprintf(fpErr,
                    "\nfile: '=' expected as the second token in each line.");
            return -1;
        }
        if(sTokenMap[MapIdx].bType == 1)
        {
            strcpy((XDAS_Int8 *)sTokenMap[MapIdx].place, items[i+2]);
            /* sscanf (items[i+2], "%s", StringContent); */
        }
        else
        {
            sscanf (items[i+2], "%d", &IntContent);
            * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
        }
    }

    return 0 ;
}/* ParseContent */



/*===========================================================================*/
/*!
*@func   readparamfile
*
*@brief  Top Level function to read the parameter file.
*
*@param  fname     
*        Pointer to the configuration file
*
*@return XDAS_Int32
*        0 - Param File Read Successful
*        -1 - Param File Read Failure
*
*@note
*/
/*===========================================================================*/
XDAS_Int32 readparamfile(FILE * fname)
{
    XDAS_Int8 *FileBuffer = NULL ;
    XDAS_Int32 retVal ; 

    /* read the content in a buffer */
    FileBuffer = GetConfigFileContent(fname);

    if(FileBuffer)
    {
        retVal  = ParseContent(FileBuffer,strlen(FileBuffer));
        return retVal;
    }
    else
    {
        return -1;
    }
}/* readparamfile */

/*!
*! Revision History
*! ****************
*! 17-08-2007 Sunil Koteyar: Move some funtionality from subPictConv.c and
*!            renamed as GetReconFrame & DoChromaInterleave. subPictConv.c
*!            is defunct now.
*! 09-08-2007 Sunil Koteyar: Code changes related to Coding Guidelines
*! 18-01-2006 Anirban Basu: Created.
*/
