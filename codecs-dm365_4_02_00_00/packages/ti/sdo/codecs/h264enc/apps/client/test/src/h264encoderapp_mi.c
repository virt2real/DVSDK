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
extern void copyHandles(void* handle0,void* handle1);
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


/* When profiling is enabled on ARM968, defining array for copying the cycles
 * from ARM968
 */

XDAS_Int32 PACKET_SIZES[2][200];
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
static sTokenMapping sTokenMap[2][MAX_ITEMS_TO_PARSE];
static	XDAS_Int32 lInstance = 0;
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
    H264VENC_Status H264EncStatus,
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
    H264VENC_OutArgs outArgs,
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
    unsigned int uiPictHeight
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
XDAS_Int32 main(XDAS_Int32 argc, XDAS_Int8 **argv)
{
    H264VENC_Handle  handle[2] = {NULL,NULL};  /* Handle to the Encoder instance      - XDAIS */
    IH264VENC_Fxns fxns;      /* Function table for the H.264 Encoder- XDAIS */
    H264VENC_Params params[2];   /* Instance creation Parameter         - XMI   */
    H264VENC_Status status[2];   /* Stores the status of process call   - XDM   */
    H264VENC_InArgs inargs[2];   /* Input Parameter to the process call - XDM   */
    H264VENC_OutArgs outargs[2]; /* Ouput parameters from process call  - XDM   */
    H264VENC_DynamicParams dynamicparams[2]; /* Dynamic Parameter struct- XDM   */
    IVIDEO1_BufDescIn inobj[2];  /* Input Buffer description array      - XDM   */
    XDM_BufDesc outobj[2];       /* Output Buffer description array     - XDM   */
    XDAS_Int32 iErrorFlag;    /* Local Variables to Keep track of errors     */
    XDAS_UInt8 *pubYRecon;    /* Pointer to the Reconstructed Luma Frame */
    XDAS_UInt8 *pubURecon;    /* Pointer to the Reconstructed U Frame */
    XDAS_UInt8 *pubVRecon;    /* Pointer to the Reconstructed V Frame */

    /* Variables to keep track of various input configuration parameters */
    XDAS_UInt32 uiNumFrames[2];            /* Number of frames encoded         */
    XDAS_UInt32 uiNumFramesToBeEncoded[2]; /* Number of frames to be encoded   */
    XDAS_UInt32 uiNumBytesWritten[2];      /* Number of encoded bytes written  */
    XDAS_UInt32 uiTokenCtr;             /* Token map counter                */
    XDAS_UInt32 numTicksPerFrame[2];       /* For generating Time Stamp        */
    XDAS_Int32 uiExtWidth[2];              /* Width with padding to 16         */
    XDAS_Int32 uiExtHeight[2];             /* Height with padding to 16        */
	XDAS_Int32 uiFrmPitch[2];              /* Line Pitch for the input frame   */
    XDAS_Int8  bWriteEncodedData;       /* Switch for Bitstream write out   */
    XDAS_Int8  bWriteReconData;         /* Switch for Recon write out       */
    XDAS_Int8  bInputFile[2][400];         /* Input file name                  */
    XDAS_Int8  bEncOutFile[2][400];        /* Encoded output file name         */
    XDAS_Int8  bReconOutFile[2][400];      /* Reconstructed decoded output file*/
    XDAS_Int8  bConfigFile[2][400];        /* Config Parameters */
    XDAS_Int8  line[400];
	XDAS_Int32  testCompliance;
	XDAS_Int32 retVal;
	XDAS_Int32 iSkipCnt;                /* Variable for keeping skip count  */
	XDAS_Int32 iStatus;                 /* Flag for file read error check */
	XDAS_Int32 uiFrmSize;
	XDAS_Int8  lEndFlag0,lEndFlag1;


    FILE *pfConfigParamsFile;  /* Pointer to the Configuration File         */
    FILE *pfInputYUVFile[2];      /* Pointer to the Input Video YUV File       */
    FILE *pfOutBitStreamFile[2];  /* Pointer to the output BitStream File      */
    FILE *pfOutYUVFile[2];        /* Pointer to the output reconstructed File  */
    FILE *pfConfigFileList ;   /* Pointer to the list of Config Files */
	IRES_Status iresStatus;


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

    bWriteEncodedData = 1; /* Enable writing of encoded data to file */
    bWriteReconData = 0; /* Enabled writing reconstructed frame to file */

    /* Intialize function table pointer to the function table implementation for
     * H.264 Encoder by TI.
     */
    fxns = H264VENC_TI_IH264VENC;
	GT_init();
	GT_create(&someGTMask, "ti.sdo.fc.rman.examples.dummyEdma3");
	GT_set("*" "=01234567");

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
   // pfConfigFileList[1] =
     //   fopen("../../../test/testvecs/config/second_testvecs.cfg", "r");
#endif
	if(pfConfigFileList == NULL /*|| pfConfigFileList[1] == NULL*/ )
	{
		printf("\n ERROR! - Could Not open Config File %s", pfConfigFileList[0]);
		exit(-1);
	}

    while(!feof(pfConfigFileList))
    {
	    /* Interrupt enable related function calls please refer to User
	     * guide for a detailed description of these functions and the
	     * DM360_IPC_INTC_ENABLE macro usage
	     */
#ifdef DM360_IPC_INTC_ENABLE
	    /*--------------------------------------------------------------------*/
	    /* Interrupt enable related function calls please refer to User       */
	    /* guide for a detailed description of these functions and the        */
	    /* DM360_IPC_INTC_ENABLE macro usage                                  */
	    /* Call the functions to enable ARM926 FIQ and do some basic setup to */
	    /* AINTC to accept KLD INTC (arm968) interupt in FIQ pin of Arm926    */
	    /*--------------------------------------------------------------------*/
#ifndef ON_LINUX
	     ARM926_enable_FIQ();  /* SWI call to enable interrupts */
	     ARM926_INTC_init();   /* Init ARM INTC */
#endif
#endif //DM360_IPC_INTC_ENABLE

		/*--------------------------------------------------------------------*/
		/* Clear polling bit of ARM968; This is not required when Interrupt   */
		/* is enabled between ARM926 and ARM968. But disabling needs          */
		/* corresponding change in hdvicp_framework.c file When interrupt is  */
		/* enabled poll_word points to a memory location in external memory.  */
		/* When interrupt is disabled it points to a memory location in DTCM  */
		/* of ARM968 - as a way of inter processor signaling.                 */
		/*--------------------------------------------------------------------*/

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
			sscanf(line,"%s",bConfigFile[0]);
		}
		else
		{
			break ;
		}

		/* Read Input file name */
		if(fgets(line,254, pfConfigFileList))
		{
			sscanf(line,"%s",bInputFile[0]);
		}
		else
		{
			break ;
		}

		/* Read Output/Reference file name */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%s",bEncOutFile[0]);
		}
		else
		{
			break ;
		}

		/* Read Recon file name */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%s",bReconOutFile[0]);
		}
		else
		{
			break ;
		}


        /* Point the param pointer to default parameters from encoder */
        params[0] = H264VENC_PARAMS;
		params[1] = H264VENC_PARAMS;
        uiTokenCtr = 0;

        /* Set up Token Map for all the input parameters to be read from the
         * configuration file
         */
        sTokenMap[0][uiTokenCtr].tokenName = "FramesToEncode";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =  &uiNumFramesToBeEncoded[0];

        sTokenMap[0][uiTokenCtr].tokenName = "ImageHeight";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &dynamicparams[0].videncDynamicParams.inputHeight;

        sTokenMap[0][uiTokenCtr].tokenName = "ImageWidth";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &dynamicparams[0].videncDynamicParams.inputWidth;

        sTokenMap[0][uiTokenCtr].tokenName = "FrameRate";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &dynamicparams[0].videncDynamicParams.targetFrameRate;

        sTokenMap[0][uiTokenCtr].tokenName = "BitRate";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &dynamicparams[0].videncDynamicParams.targetBitRate;

        sTokenMap[0][uiTokenCtr].tokenName = "ChromaFormat";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &params[0].videncParams.inputChromaFormat;

        sTokenMap[0][uiTokenCtr].tokenName = "InterlacedVideo";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &params[0].videncParams.inputContentType;

        sTokenMap[0][uiTokenCtr].tokenName = "IntraPeriod";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &dynamicparams[0].videncDynamicParams.intraFrameInterval;

        sTokenMap[0][uiTokenCtr].tokenName = "IDRFramePeriod";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &dynamicparams[0].idrFrameInterval;

        sTokenMap[0][uiTokenCtr].tokenName = "RC_PRESET";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   =
            &params[0].videncParams.rateControlPreset;

        sTokenMap[0][uiTokenCtr].tokenName = "ME_Type";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].meAlgo;

        sTokenMap[0][uiTokenCtr].tokenName = "ENC_PRESET";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].videncParams.encodingPreset;

        sTokenMap[0][uiTokenCtr].tokenName = "SliceSize";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].sliceSize;

        sTokenMap[0][uiTokenCtr].tokenName = "TimerScale";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].timeScale;

        sTokenMap[0][uiTokenCtr].tokenName = "NumUnitsInTicks";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].numUnitsInTicks;

        sTokenMap[0][uiTokenCtr].tokenName = "RateControl";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].rcAlgo;

        sTokenMap[0][uiTokenCtr].tokenName = "MaxDelay";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].maxDelay;

        sTokenMap[0][uiTokenCtr].tokenName = "AspectRatioWidth";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].aspectRatioX;

        sTokenMap[0][uiTokenCtr].tokenName = "AspectRatioHeight";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].aspectRatioY;

        sTokenMap[0][uiTokenCtr].tokenName = "PixelRange";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].pixelRange;

        sTokenMap[0][uiTokenCtr].tokenName = "EnableVUIParam";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].enableVUIparams;

        sTokenMap[0][uiTokenCtr].tokenName = "EnableBufSEI";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].enableBufSEI;

        sTokenMap[0][uiTokenCtr].tokenName = "QPInit";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].initQ;

        sTokenMap[0][uiTokenCtr].tokenName = "QPISlice";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].intraFrameQP;

        sTokenMap[0][uiTokenCtr].tokenName = "QPSlice";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].interPFrameQP;

        sTokenMap[0][uiTokenCtr].tokenName = "MaxQP";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].rcQMax;

        sTokenMap[0][uiTokenCtr].tokenName = "MinQP";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].rcQMin;

        sTokenMap[0][uiTokenCtr].tokenName = "ProfileIDC";
        sTokenMap[0][uiTokenCtr].bType     = 0;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].profileIdc;

        sTokenMap[0][uiTokenCtr].tokenName = "LevelIDC";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].levelIdc;

        sTokenMap[0][uiTokenCtr].tokenName = "AirRate";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].airRate;

        sTokenMap[0][uiTokenCtr].tokenName = "LoopFilterDisable";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].lfDisableIdc;

        sTokenMap[0][uiTokenCtr].tokenName = "UnRestrictedMV";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].unrestrictedMV;

        sTokenMap[0][uiTokenCtr].tokenName = "PerceptualRC";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &dynamicparams[0].perceptualRC;

        sTokenMap[0][uiTokenCtr].tokenName = "EntropyCodingMode";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].entropyMode;

        sTokenMap[0][uiTokenCtr].tokenName = "Transform8x8FlagIntra";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].transform8x8FlagIntraFrame;

        sTokenMap[0][uiTokenCtr].tokenName = "Transform8x8FlagInter";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].transform8x8FlagInterFrame;

        sTokenMap[0][uiTokenCtr].tokenName = "SequenceScalingFlag";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].seqScalingFlag;

        sTokenMap[0][uiTokenCtr].tokenName = "EncoderQuality";
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = &params[0].encQuality;

        sTokenMap[0][uiTokenCtr].tokenName = NULL;
        sTokenMap[0][uiTokenCtr].bType     = 0 ;
        sTokenMap[0][uiTokenCtr++].place   = NULL;

        /*--------------------------------------------------------------------*/
        /*                    READ INPUT CONFIG FILE                          */
        /*--------------------------------------------------------------------*/
        pfConfigParamsFile = fopen(bConfigFile[0], "r");
        if(pfConfigParamsFile == NULL)
        {
            printf("ERROR! - Could Not open Config File %s\n", bConfigFile[0]);
            continue;
        }
        printf("\nReading Configuration file %s...\n",bConfigFile[0]);
        /* pass config file for parsing */
        if(readparamfile(pfConfigParamsFile) != 0)
        {
            printf("ERROR! - Unable to read Config File %s\n", bConfigFile[0]);
            fclose(pfConfigParamsFile);
            continue;
        }
        //fclose(pfConfigParamsFile);

        pfInputYUVFile[0] = fopen(bInputFile[0], "rb");
		printf("\nReading inputYUV file %s...\n",bInputFile[0]);

        if(pfInputYUVFile[0] == NULL)
        {
            printf("\n ERROR! - Could Not open Input YUV File %s", bInputFile[0]);
            exit(-1);
        }

        /* Compute extended width and extended height */
        uiExtWidth[0] =
            (dynamicparams[0].videncDynamicParams.inputWidth + 15) & ~0x0F;
        uiExtHeight[0] =
            (dynamicparams[0].videncDynamicParams.inputHeight + 15) & ~0x0F;
		uiFrmPitch[0] = uiExtWidth[0];

		if(testCompliance)
		{
			printf("Running in reference bit-stream complaince check Mode\n");
		}
		else
		{
			printf("Running in Output Dump Mode\n");
		}

        /* Disable encode output file write if file not specified */
        if(bEncOutFile[0] == NULL)
        {
            bWriteEncodedData = 0;
        }

        if(bWriteEncodedData)
        {
			if(testCompliance)
			{
				pfOutBitStreamFile[0] = fopen(bEncOutFile[0], "rb");
	            if(pfOutBitStreamFile[0] == NULL)
	            {
	                printf("\n ERROR! -Could Not open Output bitstream File %s",
	                       bEncOutFile);
	                exit(-1);
	            }
			}
			else
			{
	            pfOutBitStreamFile[0] = fopen(bEncOutFile[0], "wb");
	            if(pfOutBitStreamFile[0] == NULL)
	            {
	                printf("\n ERROR! -Could Not open Output bitstream File %s",
	                       bEncOutFile);
	                exit(-1);
	            }
			}
        }

        /* Disable reconstructed frame file write if file not specified */
        if(bReconOutFile[0] == NULL)
        {
            bWriteReconData = 0;
        }

        if(bWriteReconData)
        {
            XDAS_Int32 uiSize = uiExtWidth[0] * uiExtHeight[0];

            pfOutYUVFile[0] = fopen(bReconOutFile[0], "wb");
            if(pfOutYUVFile[0] == NULL)
            {
                printf("\n ERROR! - Could Not open Input YUV File %s",
                       pfOutYUVFile[0]);
                exit(-1);
            }

            /* Allocate memory for the reconstructed frames */
            pubYRecon = malloc(uiSize * sizeof(XDAS_Int8));
            pubURecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
            pubVRecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
        }
		

/* Reading config file used for another instance of encoder */
		lInstance++;
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
			sscanf(line,"%s",bConfigFile[1]);
		}
		else
		{
			break ;
		}

		/* Read Input file name */
		if(fgets(line,254, pfConfigFileList))
		{
			sscanf(line,"%s",bInputFile[1]);
		}
		else
		{
			break ;
		}

		/* Read Output/Reference file name */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%s",bEncOutFile[1]);
		}
		else
		{
			break ;
		}

		/* Read Recon file name */
		if(fgets(line, 254, pfConfigFileList))
		{
			sscanf(line,"%s",bReconOutFile[1]);
		}
		else
		{
			break ;
		}
       /* Set up Token Map for all the input parameters to be read from the
         * configuration file
         */
		 uiTokenCtr = 0;
        sTokenMap[1][uiTokenCtr].tokenName = "FramesToEncode";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =  &uiNumFramesToBeEncoded[1];

        sTokenMap[1][uiTokenCtr].tokenName = "ImageHeight";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &dynamicparams[1].videncDynamicParams.inputHeight;

        sTokenMap[1][uiTokenCtr].tokenName = "ImageWidth";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &dynamicparams[1].videncDynamicParams.inputWidth;

        sTokenMap[1][uiTokenCtr].tokenName = "FrameRate";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &dynamicparams[1].videncDynamicParams.targetFrameRate;

        sTokenMap[1][uiTokenCtr].tokenName = "BitRate";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &dynamicparams[1].videncDynamicParams.targetBitRate;

        sTokenMap[1][uiTokenCtr].tokenName = "ChromaFormat";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &params[1].videncParams.inputChromaFormat;

        sTokenMap[1][uiTokenCtr].tokenName = "InterlacedVideo";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &params[1].videncParams.inputContentType;

        sTokenMap[1][uiTokenCtr].tokenName = "IntraPeriod";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &dynamicparams[1].videncDynamicParams.intraFrameInterval;

        sTokenMap[1][uiTokenCtr].tokenName = "IDRFramePeriod";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &dynamicparams[1].idrFrameInterval;

        sTokenMap[1][uiTokenCtr].tokenName = "RC_PRESET";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   =
            &params[1].videncParams.rateControlPreset;

        sTokenMap[1][uiTokenCtr].tokenName = "ME_Type";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].meAlgo;

        sTokenMap[1][uiTokenCtr].tokenName = "ENC_PRESET";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].videncParams.encodingPreset;

        sTokenMap[1][uiTokenCtr].tokenName = "SliceSize";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].sliceSize;

        sTokenMap[1][uiTokenCtr].tokenName = "TimerScale";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].timeScale;

        sTokenMap[1][uiTokenCtr].tokenName = "NumUnitsInTicks";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].numUnitsInTicks;

        sTokenMap[1][uiTokenCtr].tokenName = "RateControl";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].rcAlgo;

        sTokenMap[1][uiTokenCtr].tokenName = "MaxDelay";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].maxDelay;

        sTokenMap[1][uiTokenCtr].tokenName = "AspectRatioWidth";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].aspectRatioX;

        sTokenMap[1][uiTokenCtr].tokenName = "AspectRatioHeight";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].aspectRatioY;

        sTokenMap[1][uiTokenCtr].tokenName = "PixelRange";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].pixelRange;

        sTokenMap[1][uiTokenCtr].tokenName = "EnableVUIParam";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].enableVUIparams;

        sTokenMap[1][uiTokenCtr].tokenName = "EnableBufSEI";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].enableBufSEI;

        sTokenMap[1][uiTokenCtr].tokenName = "QPInit";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].initQ;

        sTokenMap[1][uiTokenCtr].tokenName = "QPISlice";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].intraFrameQP;

        sTokenMap[1][uiTokenCtr].tokenName = "QPSlice";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].interPFrameQP;

        sTokenMap[1][uiTokenCtr].tokenName = "MaxQP";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].rcQMax;

        sTokenMap[1][uiTokenCtr].tokenName = "MinQP";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].rcQMin;

        sTokenMap[1][uiTokenCtr].tokenName = "ProfileIDC";
        sTokenMap[1][uiTokenCtr].bType     = 0;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].profileIdc;

        sTokenMap[1][uiTokenCtr].tokenName = "LevelIDC";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].levelIdc;

        sTokenMap[1][uiTokenCtr].tokenName = "AirRate";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].airRate;

        sTokenMap[1][uiTokenCtr].tokenName = "LoopFilterDisable";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].lfDisableIdc;

        sTokenMap[1][uiTokenCtr].tokenName = "UnRestrictedMV";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].unrestrictedMV;

        sTokenMap[1][uiTokenCtr].tokenName = "PerceptualRC";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &dynamicparams[1].perceptualRC;

        sTokenMap[1][uiTokenCtr].tokenName = "EntropyCodingMode";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].entropyMode;

        sTokenMap[1][uiTokenCtr].tokenName = "Transform8x8FlagIntra";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].transform8x8FlagIntraFrame;

        sTokenMap[1][uiTokenCtr].tokenName = "Transform8x8FlagInter";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].transform8x8FlagInterFrame;

        sTokenMap[1][uiTokenCtr].tokenName = "SequenceScalingFlag";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].seqScalingFlag;

        sTokenMap[1][uiTokenCtr].tokenName = "EncoderQuality";
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = &params[1].encQuality;

        sTokenMap[1][uiTokenCtr].tokenName = NULL;
        sTokenMap[1][uiTokenCtr].bType     = 0 ;
        sTokenMap[1][uiTokenCtr++].place   = NULL;

        /*--------------------------------------------------------------------*/
        /*                    READ INPUT CONFIG FILE                          */
        /*--------------------------------------------------------------------*/
        pfConfigParamsFile = fopen(bConfigFile[1], "r");
        if(pfConfigParamsFile == NULL)
        {
            printf("ERROR! - Could Not open Config File %s\n", bConfigFile[1]);
            continue;
        }
        printf("\nReading Configuration file %s...\n",bConfigFile[1]);
        /* pass config file for parsing */
        if(readparamfile(pfConfigParamsFile) != 0)
        {
            printf("ERROR! - Unable to read Config File %s\n", bConfigFile[1]);
            fclose(pfConfigParamsFile);
            continue;
        }
        //fclose(pfConfigParamsFile);

        pfInputYUVFile[1] = fopen(bInputFile[1], "rb");
		printf("\nReading YUV input file for second instance file %s...\n",bInputFile[1]);

        if(pfInputYUVFile[1] == NULL)
        {
            printf("\n ERROR! - Could Not open Input YUV File %s", bInputFile[1]);
            exit(-1);
        }

        /* Compute extended width and extended height */
        uiExtWidth[1] =
            (dynamicparams[1].videncDynamicParams.inputWidth + 15) & ~0x0F;
        uiExtHeight[1] =
            (dynamicparams[1].videncDynamicParams.inputHeight + 15) & ~0x0F;
		uiFrmPitch[1] = uiExtWidth[1];

		if(uiExtHeight[0] > uiExtHeight[1])
			uiFrmSize = uiFrmPitch[0] * uiExtHeight[0];
		else
			uiFrmSize = uiFrmPitch[1] * uiExtHeight[1];

        /* Allocate memory for the input frame */
        {
            pubInY = (XDAS_UInt8 *) malloc(uiFrmSize * sizeof(XDAS_UInt8));
            pubInU =
                (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
            pubInV =
                (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
        }

		if(testCompliance)
		{
			printf("Running in reference bit-stream complaince check Mode\n");
		}
		else
		{
			printf("Running in Output Dump Mode\n");
		}

        /* Disable encode output file write if file not specified */
        if(bEncOutFile[1] == NULL)
        {
            bWriteEncodedData = 0;
        }

        if(bWriteEncodedData)
        {
			if(testCompliance)
			{
				pfOutBitStreamFile[1] = fopen(bEncOutFile[1], "rb");
	            if(pfOutBitStreamFile[1] == NULL)
	            {
	                printf("\n ERROR! -Could Not open Output bitstream File %s",
	                       bEncOutFile);
	                exit(-1);
	            }
			}
			else
			{
	            pfOutBitStreamFile[1] = fopen(bEncOutFile[1], "wb");
	            if(pfOutBitStreamFile[1] == NULL)
	            {
	                printf("\n ERROR! -Could Not open Output bitstream File %s",
	                       bEncOutFile);
	                exit(-1);
	            }
			}
        }

        /* Disable reconstructed frame file write if file not specified */
        if(bReconOutFile[1] == NULL)
        {
            bWriteReconData = 0;
        }

        if(bWriteReconData)
        {
            XDAS_Int32 uiSize = uiExtWidth[1] * uiExtHeight[1];

            pfOutYUVFile[0] = fopen(bReconOutFile[0], "wb");
            if(pfOutYUVFile[0] == NULL)
            {
                printf("\n ERROR! - Could Not open Input YUV File %s",
                       pfOutYUVFile[0]);
                exit(-1);
            }

            /* Allocate memory for the reconstructed frames */
            pubYRecon = malloc(uiSize * sizeof(XDAS_Int8));
            pubURecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
            pubVRecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
        }
/************************************************************/

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
        params[0].videncParams.maxWidth = MAX_WIDTH;/*uiExtWidth[0]*/;
        params[0].videncParams.maxHeight = MAX_HEIGHT;//uiExtHeight[0];
		params[0].videncParams.maxBitRate = 10000000;
        if(bWriteReconData == 0)
        {
            params[0].videncParams.reconChromaFormat = IH264VENC_YUV_420IUV;
        }
        /* Xena hardware provides only single VIMCOP which is indexed by 0 */
        //params.imcop_selector = 0; /* Allways 0 */
/*************************************************/
        params[1].videncParams.maxWidth = MAX_WIDTH;/*uiExtWidth[1];*/
        params[1].videncParams.maxHeight = MAX_HEIGHT;//uiExtHeight[1];
		params[1].videncParams.maxBitRate = 10000000;
        if(bWriteReconData == 0)
        {
            params[1].videncParams.reconChromaFormat = IH264VENC_YUV_420IUV;
        }
/*************************************************/


        /* DMA initialization parameter should be set before Encoder creation as
         * DMA will be configured based on these parameters during creation.
         * Setting of these parameters is done through the following function
         * defined in file testapp_idma.c. Application writer can update this
         * file
         */

        /* Encoder Create function - Calls ALG Framework function -
         * ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
         */

        if((handle[0] = H264VENC_create(&fxns, &params[0])) == NULL)
        {
            printf("\nERROR! - Encoder Creation Failed");
            goto FREE_ENCODER_OBJECT; /* Creation failed - exit the encoder */
        }
        printf("Encoder Creation Done\n");



        if((handle[1] = H264VENC_create(&fxns, &params[1])) == NULL)
        {
            printf("\nERROR! - Encoder Creation Failed");
            goto FREE_ENCODER_OBJECT; /* Creation failed - exit the encoder */
        }
        printf("Second Encoder Creation Done\n");

#ifdef _ENABLE_IRES_EDMA3
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)handle[0],
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
      printf( "\nFailed in assignign resources \
                 Exiting for this configuration..");
      goto FREE_RESOURCES;
    }
#endif 
#ifdef _ENABLE_IRES_EDMA3
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)handle[1],
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
      printf( "\nFailed in assignign resources \
                 Exiting for this configuration..");
      goto FREE_RESOURCES;
    }
#endif
		/*{
		 int i = sizeof(H264VENC_Handle);
		 printf("%d",i);fflush(stdout);
		}*/
//memcpy((unsigned char*)handle[1],(unsigned char*)handle[0],sizeof(H264VENC_Handle));

        /*--------------------------------------------------------------------*/
        /*                       DYNAMIC PARAMETERS INTIALIZATION             */
        /*--------------------------------------------------------------------*/
        dynamicparams[0].videncDynamicParams.size = sizeof(H264VENC_DynamicParams);
        dynamicparams[0].videncDynamicParams.refFrameRate =
        dynamicparams[0].videncDynamicParams.targetFrameRate;
        dynamicparams[0].videncDynamicParams.generateHeader = 0;
        dynamicparams[0].videncDynamicParams.captureWidth = uiFrmPitch[0];
        dynamicparams[0].videncDynamicParams.forceFrame = IVIDEO_NA_FRAME;
        dynamicparams[0].videncDynamicParams.interFrameInterval = 0;
        dynamicparams[0].videncDynamicParams.mbDataFlag = 0;
		dynamicparams[0].enablePicTimSEI = dynamicparams[0].enableBufSEI;
		dynamicparams[0].resetHDVICPeveryFrame = 0;
/*************************************************************************/
       /*--------------------------------------------------------------------*/
        /*                       DYNAMIC PARAMETERS INTIALIZATION             */
        /*--------------------------------------------------------------------*/
        dynamicparams[1].videncDynamicParams.size = sizeof(H264VENC_DynamicParams);
        dynamicparams[1].videncDynamicParams.refFrameRate =
        dynamicparams[1].videncDynamicParams.targetFrameRate;
        dynamicparams[1].videncDynamicParams.generateHeader = 0;
        dynamicparams[1].videncDynamicParams.captureWidth = uiFrmPitch[1];
        dynamicparams[1].videncDynamicParams.forceFrame = IVIDEO_NA_FRAME;
        dynamicparams[1].videncDynamicParams.interFrameInterval = 0;
        dynamicparams[1].videncDynamicParams.mbDataFlag = 0;
		dynamicparams[1].enablePicTimSEI = dynamicparams[1].enableBufSEI;
		dynamicparams[1].resetHDVICPeveryFrame = 0;
/***********************************************************************/

        numTicksPerFrame[0] = ((params[0].timeScale/params[0].numUnitsInTicks) * 1000)/
                           (dynamicparams[0].videncDynamicParams.targetFrameRate);

        numTicksPerFrame[1] = ((params[1].timeScale/params[1].numUnitsInTicks) * 1000)/
                           (dynamicparams[1].videncDynamicParams.targetFrameRate);


	//copyHandles(handle[0],handle[1]);


        /*--------------------------------------------------------------------*/
        /*              Check for any warnings set at create time             */
        /*--------------------------------------------------------------------*/
		status[0].videncStatus.size = sizeof(IH264VENC_Status);
		status[1].videncStatus.size = sizeof(IH264VENC_Status);

        iErrorFlag = H264VENC_control(
            handle[0],         // Instance Handle
            XDM_GETSTATUS,  // Command
            &dynamicparams[0], // Pointer to Dynamic Params structure -Input
            &status[0]         // Pointer to the status structure - Output
        );

        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Get Status Info Command Faile\n");
			goto FREE_ENCODER_OBJECT;
		}
		if(status[0].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
		{
			printf("Parameter not supported\n");
		}
		if(status[0].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
		{
			printf("Input not supported\n");
		}
/*********************************************************/
		iErrorFlag = H264VENC_control(
            handle[1],         // Instance Handle
            XDM_GETSTATUS,  // Command
            &dynamicparams[1], // Pointer to Dynamic Params structure -Input
            &status[1]         // Pointer to the status structure - Output
        );

        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Get Status Info Command Faile\n");
			goto FREE_ENCODER_OBJECT;
		}
		if(status[1].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
		{
			printf("Parameter not supported\n");
		}
		if(status[1].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
		{
			printf("Input not supported\n");
		}
/*********************************************************/

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
		status[0].videncStatus.size = sizeof(IH264VENC_Status);
		status[1].videncStatus.size = sizeof(IH264VENC_Status);

        iErrorFlag = H264VENC_control(
            handle[0],         // Instance Handle
            XDM_GETBUFINFO, // Command
            &dynamicparams[0], // Pointer to Dynamic Params structure -Input
            &status[0]         // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Get Buffer Info Command Faile\n");
			goto FREE_ENCODER_OBJECT;
		}
/****** Second encoder instance *******************/
        iErrorFlag = H264VENC_control(
            handle[1],         // Instance Handle
            XDM_GETBUFINFO, // Command
            &dynamicparams[1], // Pointer to Dynamic Params structure -Input
            &status[1]         // Pointer to the status structure - Output
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
        if(AllocateH264IOBuffers(
            status[0], // status structure - Input
            &inobj[0], // Pointer to Input Buffer Descriptor - Output
            &outobj[0]) // Pointer to Output Buffer Descriptor - Output
        )
        {
            printf("Not Enough Memory\n");
            FreeH264IOBuffers(
                &inobj[0], // Pointer to Input Buffer Descriptor - Input
                &outobj[0] // Pointer to Output Buffer Descriptor - Input
            );
            goto FREE_FRAME_IO_BUFFERS;
        }
		inobj[0].frameHeight = uiExtHeight[0];
		inobj[0].frameWidth = uiExtWidth[0];
		inobj[0].framePitch = uiFrmPitch[0];
		if((dynamicparams[0].videncDynamicParams.captureWidth == 0) ||
		   (dynamicparams[0].videncDynamicParams.captureWidth < uiExtWidth[0]))
		{
			inobj[0].framePitch = uiExtWidth[0];
		}
/****** Second encoder instance *******************/
        if(AllocateH264IOBuffers(
            status[1], // status structure - Input
            &inobj[1], // Pointer to Input Buffer Descriptor - Output
            &outobj[1]) // Pointer to Output Buffer Descriptor - Output
        )
        {
            printf("Not Enough Memory\n");
            FreeH264IOBuffers(
                &inobj[1], // Pointer to Input Buffer Descriptor - Input
                &outobj[1] // Pointer to Output Buffer Descriptor - Input
            );
            goto FREE_FRAME_IO_BUFFERS;
        }
		inobj[1].frameHeight = uiExtHeight[1];
		inobj[1].frameWidth = uiExtWidth[1];
		inobj[1].framePitch = uiFrmPitch[1];
		if((dynamicparams[1].videncDynamicParams.captureWidth == 0) ||
		   (dynamicparams[1].videncDynamicParams.captureWidth < uiExtWidth[1]))
		{
			inobj[1].framePitch = uiExtWidth[1];
		}
        /*--------------------------------------------------------------------*/
        /*                     SET DYNAMIC INPUT PARAMETERS                   */
        /*--------------------------------------------------------------------*/

        iErrorFlag = H264VENC_control(
            handle[0],        // Instance Handle
            XDM_SETPARAMS, // Command
            &dynamicparams[0],// Pointer to Dynamic structure - Input
            &status[0]        // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Set Encoder parameters Command Failed\n");
			goto FREE_ENCODER_IO_BUFFERS;
		}
		if(status[0].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
		{
			printf("Parameter not supported\n");
		}
		if(status[0].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
		{
			printf("Input not supported\n");
		}

/****** Second encoder instance *******************/
        iErrorFlag = H264VENC_control(
            handle[1],        // Instance Handle
            XDM_SETPARAMS, // Command
            &dynamicparams[1],// Pointer to Dynamic structure - Input
            &status[1]        // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
			printf("Set Encoder(second) parameters Command Failed\n");
			goto FREE_ENCODER_IO_BUFFERS;
		}
		if(status[1].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
		{
			printf("Parameter not supported\n");
		}
		if(status[1].videncStatus.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
		{
			printf("Input not supported\n");
		}




		/* If the number of Frames is input as 0, interpret that as number
		 * of frames in the input unknown and encode till file end
		 */
		if(uiNumFramesToBeEncoded[0] == 0)
		{
			uiNumFramesToBeEncoded[0] = MAX_FRAMES_TO_ENCODE;
		}
		if(uiNumFramesToBeEncoded[1] == 0)
		{
			uiNumFramesToBeEncoded[1] = MAX_FRAMES_TO_ENCODE;
		}

		iSkipCnt = 0;
        uiNumBytesWritten[0] = 0;
        uiNumBytesWritten[1] = 0;
        printf("\nStarting Encode...\n");
        /*--------------------------------------------------------------------*/
        /*                                  ENCODE LOOP                       */
        /*--------------------------------------------------------------------*/
		uiNumFrames[0] = uiNumFrames[1] = 0;
		lEndFlag0 = 0;
		lEndFlag1 = 0;
	do
	{
		//while(uiNumFrames[0] < uiNumFramesToBeEncoded[0] &&
		  //    !feof(pfInputYUVFile[0]) && !feof(pfInputYUVFile[1]))
        /*for(uiNumFrames = 0; uiNumFrames < uiNumFramesToBeEncoded;
            uiNumFrames++)*/
		if(!lEndFlag0)
        {
        /* Initialize Input Arguements */
        inargs[0].videncInArgs.size = sizeof(H264VENC_InArgs);
        inargs[0].videncInArgs.inputID = 1;
        inargs[0].videncInArgs.topFieldFirstFlag = XDAS_TRUE;
		inargs[0].timeStamp = 0;
		inargs[0].insertUserData = 0;
		//inargs[0].lengthUserData = 10;

        /* Initialize Output Arguments */
        outargs[0].videncOutArgs.size = sizeof(H264VENC_OutArgs);
        outargs[0].videncOutArgs.extendedError = 0;
        outargs[0].videncOutArgs.bytesGenerated = 0;
        outargs[0].videncOutArgs.encodedFrameType = IVIDEO_NA_FRAME;
        outargs[0].videncOutArgs.inputFrameSkip = IVIDEO_FRAME_ENCODED;
        outargs[0].videncOutArgs.outputID = 1;
		outargs[0].numPackets = 0;
		outargs[0].packetSize = PACKET_SIZES[0];

            /* Implement any Dynamic Parameter changes here
             * (Call H264VENC_control()
             * with approriate command and parameters).
             */
#ifdef UPDATE_PARAMS_AT_RUN_TIME
            iErrorFlag = H264VENC_control(
                handle[0],        // Instance Handle
                XDM_SETPARAMS, // Command
                &dynamicparams[0],// Pointer to Dynamic structure - Input
                &status[0]        // Pointer to the status structure - Output
            );
	        if(iErrorFlag == XDM_EFAIL)
	        {
				printf("Set Encoder parameters Command Failed\n");
				lEndFlag0 = 1;
				goto ENCODE_NEXT_FRAME_OF_NEXT_FILE;
			}
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
                inobj[0],
            	dynamicparams[0].videncDynamicParams.inputWidth,
            	dynamicparams[0].videncDynamicParams.inputHeight,
                uiFrmPitch[0],
                uiExtHeight[0],
                pfInputYUVFile[0]
            );

			if(iStatus)
			{
	            printf("Input Frame Read Failed\n");
				lEndFlag0 = 1;
	            goto ENCODE_NEXT_FRAME_OF_NEXT_FILE;;

			}
			else
			{
				printf("Input Frame Read Done\n");
				fflush(stdout);
			}


            /* Update InArgs */
			if(uiNumFrames[0])
			{
				inargs[0].timeStamp += numTicksPerFrame[0]; /* TimeStamp */
			}


            /*----------------------------------------------------------------*/
            /*                          ENCODE FRAME                          */
            /*----------------------------------------------------------------*/

             iErrorFlag = H264VENC_encode (
                handle[0],   // Instance Handle    - Input
                &inobj[0],   // Input Buffers      - Input
                &outobj[0],  // Output Buffers     - Output
                &inargs[0],  // Input Parameters   - Input
                &outargs[0]  // Output Parameters  - Output
            );



            if(iErrorFlag == XDM_EFAIL)
            {
                /* Get Detailed information regarding the failure by querying
                 * the encoder with the control function.
                 */
                H264VENC_control(
                    handle[0],         // Instance Handle
                    XDM_GETSTATUS,  // Command - GET STATUS
                    &dynamicparams[0], // Input
                    &status[0]         // Output
                );

                printf("Encoder Returned a Failure\n");
                printf("\tFrame No              : %d\n", uiNumFrames[0]);
                printf("\tError Status          : %d\n", iErrorFlag);
                printf("\tExtended Error Status : %d\n",
                       status[0].videncStatus.extendedError);
				lEndFlag0 = 1;
                goto ENCODE_NEXT_FRAME_OF_NEXT_FILE;
            }

            if(status[0].videncStatus.extendedError == XDM_FATALERROR)
            {
				lEndFlag0 = 1;
                goto ENCODE_NEXT_FRAME_OF_NEXT_FILE;;
            }
            else
            {
				XDAS_Int32 cnt;
                uiNumBytesWritten[0] += outargs[0].videncOutArgs.bytesGenerated;
                if(outargs[0].videncOutArgs.inputFrameSkip == IVIDEO_FRAME_SKIPPED)
                {
					iSkipCnt++;
                    printf("Frame : %d Skipped: ", uiNumFrames[0]);
                }
                else
                {
                    printf("Frame : %d Encoded: ", uiNumFrames[0]);
                }
	            printf("Bytes Generated : %d\n",
	                   outargs[0].videncOutArgs.bytesGenerated);
				printf("Number of Packets = %d\n", outargs[0].numPackets);
#if 1 //temp disabled as multiple slice is off
				for(cnt = 0; cnt < outargs[0].numPackets; cnt++)
				{
					printf("Packet No.%4d: Size:-%8d\n",
							cnt, outargs[0].packetSize[cnt]);
					if((dynamicparams[0].sliceSize > 0) &&
					   ((outargs[0].packetSize[cnt] << 3) > dynamicparams[0].sliceSize)
					)
					{
						printf("Packet Size exceeded for the prev packet\n");
					}
				}
#endif
            }


            /*----------------------------------------------------------------*/
            /*                         OUTPUT DATA WRITE                      */
            /*----------------------------------------------------------------*/
            /* Write out the Encoded bit-stream to output file */
			retVal = XDM_EOK;
            if(bWriteEncodedData && outargs[0].videncOutArgs.bytesGenerated)
            {
                printf("Writing encoded frame to file\n");
                retVal = WriteDataOut(outargs[0], pfOutBitStreamFile[0],
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
            if(bWriteReconData && outargs[0].videncOutArgs.reconBufs.numBufs)
            {
                XDAS_UInt8 *pubInBufY;
                XDAS_UInt8 *pubInBufUV;

                pubInBufY =
                    (XDAS_UInt8 *)outargs[0].videncOutArgs.reconBufs.
                        bufDesc[0].buf;
                pubInBufUV =
                    (XDAS_UInt8 *)outargs[0].videncOutArgs.reconBufs.
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
                    uiExtWidth[0],
                    uiExtHeight[0]
                );
				printf("Writing Reconstructed Frame - ");
                WriteReconOut(
                    pubYRecon,
                    pubURecon,
                    pubVRecon,
                    uiExtWidth[0],
                    uiExtHeight[0],
                    pfOutYUVFile[0]
                );
				printf("Done\n");
            }

			uiNumFrames[0] = uiNumFrames[0] + 1;
			printf("uiNumFrames[0] = %d\n",uiNumFrames[0]);
			if(uiNumFrames[0] == uiNumFramesToBeEncoded[0])
				lEndFlag0 = 1;
		} //end of if(!lEndFlag0)
/******************************************************/
/* Second file Encode with anoter instance of encoder */
/******************************************************/
  
ENCODE_NEXT_FRAME_OF_NEXT_FILE:
	if(!lEndFlag1)
     {
        /* Initialize Input Arguements */
        inargs[1].videncInArgs.size = sizeof(H264VENC_InArgs);
        inargs[1].videncInArgs.inputID = 1;
        inargs[1].videncInArgs.topFieldFirstFlag = XDAS_TRUE;
		inargs[1].timeStamp = 0;
		inargs[1].insertUserData = 0;
		//inargs[1].lengthUserData = 10;

        /* Initialize Output Arguments */
        outargs[1].videncOutArgs.size = sizeof(H264VENC_OutArgs);
        outargs[1].videncOutArgs.extendedError = 0;
        outargs[1].videncOutArgs.bytesGenerated = 0;
        outargs[1].videncOutArgs.encodedFrameType = IVIDEO_NA_FRAME;
        outargs[1].videncOutArgs.inputFrameSkip = IVIDEO_FRAME_ENCODED;
        outargs[1].videncOutArgs.outputID = 1;
		outargs[1].numPackets = 0;
		outargs[1].packetSize = PACKET_SIZES[1];

/******************************************************/
            /* Implement any Dynamic Parameter changes here
             * (Call H264VENC_control()
             * with approriate command and parameters).
             */
#ifdef UPDATE_PARAMS_AT_RUN_TIME
            iErrorFlag = H264VENC_control(
                handle[1],        // Instance Handle
                XDM_SETPARAMS, // Command
                &dynamicparams[1],// Pointer to Dynamic structure - Input
                &status[1]        // Pointer to the status structure - Output
            );
	        if(iErrorFlag == XDM_EFAIL)
	        {
				printf("Set Encoder parameters Command Failed\n");
				lEndFlag1 = 1;
				goto ENCODE_NEXT_FRAME_OF_NEXT_FILE_1;
			}
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
                inobj[1],
            	dynamicparams[1].videncDynamicParams.inputWidth,
            	dynamicparams[1].videncDynamicParams.inputHeight,
                uiFrmPitch[1],
                uiExtHeight[1],
                pfInputYUVFile[1]
            );

			if(iStatus)
			{
	            printf("Input Frame Read Failed\n");
				lEndFlag1 = 1;
	            goto ENCODE_NEXT_FRAME_OF_NEXT_FILE_1;
			}
			else
			{
	            printf("Input Frame Read Done\n");
	            fflush(stdout);
			}


            /* Update InArgs */
			if(uiNumFrames[1])
			{
            	inargs[1].timeStamp += numTicksPerFrame[1]; /* TimeStamp */
			}


            /*----------------------------------------------------------------*/
            /*                          ENCODE FRAME                          */
            /*----------------------------------------------------------------*/
           iErrorFlag = H264VENC_encode (
                handle[1],   // Instance Handle    - Input
                &inobj[1],   // Input Buffers      - Input
                &outobj[1],  // Output Buffers     - Output
                &inargs[1],  // Input Parameters   - Input
                &outargs[1]  // Output Parameters  - Output
            );



            if(iErrorFlag == XDM_EFAIL)
            {
                /* Get Detailed information regarding the failure by querying
                 * the encoder with the control function.
                 */
                H264VENC_control(
                    handle[1],         // Instance Handle
                    XDM_GETSTATUS,  // Command - GET STATUS
                    &dynamicparams[1], // Input
                    &status[1]         // Output
                );

                printf("Encoder Returned a Failure\n");
                printf("\tFrame No              : %d\n", uiNumFrames[1]);
                printf("\tError Status          : %d\n", iErrorFlag);
                printf("\tExtended Error Status : %d\n",
                       status[0].videncStatus.extendedError);
				lEndFlag1 = 1;
                goto ENCODE_NEXT_FRAME_OF_NEXT_FILE_1;
            }

            if(status[1].videncStatus.extendedError == XDM_FATALERROR)
            {
				lEndFlag1 = 1;
                goto ENCODE_NEXT_FRAME_OF_NEXT_FILE_1;
            }
            else
            {
				XDAS_Int32 cnt;
                uiNumBytesWritten[1] += outargs[1].videncOutArgs.bytesGenerated;
                if(outargs[1].videncOutArgs.inputFrameSkip == IVIDEO_FRAME_SKIPPED)
                {
					iSkipCnt++;
                    printf("Frame : %d Skipped: ", uiNumFrames[1]);
                }
                else
                {
                    printf("Frame : %d Encoded: ", uiNumFrames[1]);
                }
	            printf("Bytes Generated : %d\n",
	                   outargs[1].videncOutArgs.bytesGenerated);
				printf("Number of Packets = %d\n", outargs[1].numPackets);
#if 1 //temp disabled as multiple slice is off
				for(cnt = 0; cnt < outargs[1].numPackets; cnt++)
				{
					printf("Packet No.%4d: Size:-%8d\n",
							cnt, outargs[1].packetSize[cnt]);
					if((dynamicparams[1].sliceSize > 0) &&
					   ((outargs[1].packetSize[cnt] << 3) > dynamicparams[1].sliceSize)
					)
					{
						printf("Packet Size exceeded for the prev packet\n");
					}
				}
#endif
            }


            /*----------------------------------------------------------------*/
            /*                         OUTPUT DATA WRITE                      */
            /*----------------------------------------------------------------*/
            /* Write out the Encoded bit-stream to output file */
			retVal = XDM_EOK;
            if(bWriteEncodedData && outargs[1].videncOutArgs.bytesGenerated)
            {
                printf("Writing encoded frame to file\n");
                retVal = WriteDataOut(outargs[1], pfOutBitStreamFile[1],
                                      testCompliance);
				if(testCompliance && (retVal == XDM_EFAIL))
				{
			        printf("\n\n reference bit-stream complaince check FAILED");
			        printf(" at this frame\n");
			        goto FREE_ENCODER_IO_BUFFERS;
				}
			//	goto ENCODE_NEXT_FRAME_OF_NEXT_FILE_1;
            }

            /* Write out the reconstructed frame. This is debug feature only and
             * will be disabled in the final code release
             */
            if(bWriteReconData && outargs[1].videncOutArgs.reconBufs.numBufs)
            {
                XDAS_UInt8 *pubInBufY;
                XDAS_UInt8 *pubInBufUV;

                pubInBufY =
                    (XDAS_UInt8 *)outargs[1].videncOutArgs.reconBufs.
                        bufDesc[0].buf;
                pubInBufUV =
                    (XDAS_UInt8 *)outargs[1].videncOutArgs.reconBufs.
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
                    uiExtWidth[1],
                    uiExtHeight[1]
                );
				printf("Writing Reconstructed Frame - ");
                WriteReconOut(
                    pubYRecon,
                    pubURecon,
                    pubVRecon,
                    uiExtWidth[1],
                    uiExtHeight[1],
                    pfOutYUVFile[1]
                );
				printf("Done\n");
            }

			uiNumFrames[1] = uiNumFrames[1] + 1;
			printf("uiNumFrames[1] = %d\n",uiNumFrames[1]);
			if(uiNumFrames[1] == uiNumFramesToBeEncoded[1])
				lEndFlag1 = 1;
		}

ENCODE_NEXT_FRAME_OF_NEXT_FILE_1:
	printf("Encoding continuing..");
/******************************************************/

        }while((!lEndFlag0) || (!lEndFlag1));


        /*--------------------------------------------------------------------*/
        /*                           PRINT STATS                              */
        /*--------------------------------------------------------------------*/
        if(uiNumFrames[0] == 0)
        {
            uiNumFrames[0] = 1; /* To avoid division with zero */
        }

        printf("\n --------------  SUMMARY --------------------\n");
        printf("  Total number of Frames          = %d\n",
            (XDAS_UInt32)uiNumFrames[0]);
		printf("  Encoded: %8d, Skipped: %8d\n",
			(XDAS_UInt32)uiNumFrames[0] - iSkipCnt, iSkipCnt);
        printf("  Bit Rate at 30 frames/Sec       = %d Kbps\n",(
            XDAS_UInt32)(((uiNumBytesWritten[0]*8*30)/uiNumFrames[0])/1000));
        printf("  Width and Height                = %d, %d \n",
            dynamicparams[0].videncDynamicParams.inputWidth,
            dynamicparams[0].videncDynamicParams.inputHeight);
        printf (" --------------    END   --------------------\n");

        /*--------------------------------------------------------------------*/
        /*                           PRINT STATS                              */
        /*--------------------------------------------------------------------*/
        if(uiNumFrames[1] == 0)
        {
            uiNumFrames[1] = 1; /* To avoid division with zero */
        }

        printf("\n --------------  SUMMARY --------------------\n");
        printf("  Total number of Frames          = %d\n",
            (XDAS_UInt32)uiNumFrames[1]);
		printf("  Encoded: %8d, Skipped: %8d\n",
			(XDAS_UInt32)uiNumFrames[1] - iSkipCnt, iSkipCnt);
        printf("  Bit Rate at 30 frames/Sec       = %d Kbps\n",(
            XDAS_UInt32)(((uiNumBytesWritten[1]*8*30)/uiNumFrames[1])/1000));
        printf("  Width and Height                = %d, %d \n",
            dynamicparams[1].videncDynamicParams.inputWidth,
            dynamicparams[1].videncDynamicParams.inputHeight);
        printf (" --------------    END   --------------------\n");



        /*--------------------------------------------------------------------*/
        /*             FREE H.264 ENCODER INPUT/OUTPUT BUFFERS                */
        /*--------------------------------------------------------------------*/
FREE_ENCODER_IO_BUFFERS:
        FreeH264IOBuffers(
            &inobj[0], // Pointer to Input Buffer Descriptor - Input
            &outobj[0] // Pointer to Output Buffer Descriptor - Input
        );
        FreeH264IOBuffers(
            &inobj[1], // Pointer to Input Buffer Descriptor - Input
            &outobj[1] // Pointer to Output Buffer Descriptor - Input
        );
FREE_RESOURCES:
#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle[0]),
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
        printf("Free Resource Failed \n");
        return -1;
    }
#endif

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle[1]),
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
        printf("Free Resource Failed \n");
        return -1;
    }
#endif
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
        /*--------------------------------------------------------------------*/
        /*                             DELETE ENCODER INSTANCE                */
        /*--------------------------------------------------------------------*/
FREE_ENCODER_OBJECT:
        if(handle[0])H264VENC_delete(handle[0]);
		if(handle[1])H264VENC_delete(handle[1]);

        /*--------------------------------------------------------------------*/
        /*                 FREE Frame INPUT & RECON BUFFERS                   */
        /*--------------------------------------------------------------------*/
FREE_FRAME_IO_BUFFERS:
        if(pubInY)free(pubInY);
        if(pubInU)free(pubInU);
        if(pubInV)free(pubInV);

        if(bWriteReconData)
        {
            if(pubYRecon)free(pubYRecon);
            if(pubURecon)free(pubURecon);
            if(pubVRecon)free(pubVRecon);
        }

        /* Close all input and output data files */
        fclose(pfInputYUVFile[0]);
		fclose(pfInputYUVFile[1]);
        if(bWriteEncodedData)
        {
            fclose(pfOutBitStreamFile[0]);
			fclose(pfOutBitStreamFile[1]);
        }
        if(bWriteReconData)
        {
            fclose(pfOutYUVFile[0]);
			fclose(pfOutYUVFile[1]);
        }
    }/* End of 'config file list' while() loop */


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
XDAS_Int32 AllocateH264IOBuffers(H264VENC_Status H264EncStatus,
                                 IVIDEO1_BufDescIn *ptH264EncInpBufDesc,
                                 XDM_BufDesc *ptH264EncOutBufDesc)
{
    XDAS_Int32 i;

    /*------------------------------------------------------------------------*/
    /*                           ALLOCATE INPUT BUFFERS                       */
    /*------------------------------------------------------------------------*/
/* Memory allocation params required in linux */
    ptH264EncInpBufDesc->numBufs =
        H264EncStatus.videncStatus.bufInfo.minNumInBufs;

    for( i = 0; i < H264EncStatus.videncStatus.bufInfo.minNumInBufs; i++)
    {
        /* Assign size for the current buffer */
        ptH264EncInpBufDesc->bufDesc[i].bufSize =
            H264EncStatus.videncStatus.bufInfo.minInBufSize[i];

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
        H264EncStatus.videncStatus.bufInfo.minNumOutBufs;

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
            H264EncStatus.videncStatus.bufInfo.minOutBufSize[i];
        /* Allocate memory for buffers */
        ptH264EncOutBufDesc->bufs[i] =
            (XDAS_Int8 *) CMEM_alloc(ptH264EncOutBufDesc->bufSizes[i] *
                                 sizeof(XDAS_Int8), &memParams);
        printf("Output stream buffer size:%d\n",ptH264EncOutBufDesc->bufSizes[i]);

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
    unsigned int uiPictHeight)
{
    unsigned short j,k;
    unsigned char *pubSrc;
    unsigned char *pubDstY, *pubDstU, *pubDstV;
    unsigned int uiRecWidth;

    /*------------------------------------------------------------------------*/
    /*                           COPY LUMINANCE DATA                          */
    /*------------------------------------------------------------------------*/
    pubSrc = pubSubPictY;
    uiRecWidth = uiPictWidth + (PAD_Y_HORIZ << 1);
    pubSrc += (PAD_Y_PROG_VERT * uiRecWidth) + PAD_Y_HORIZ;
    for(j = 0; j < uiPictHeight; j++)
    {
        pubDstY = pubYFrameData + (j * uiPictWidth);
        memcpy(pubDstY, pubSrc, uiPictWidth);
        pubSrc += uiRecWidth;
    }

    /*------------------------------------------------------------------------*/
    /*                          COPY CHROMINANCE DATA                         */
    /*------------------------------------------------------------------------*/
    uiRecWidth = uiPictWidth + (PAD_UV_HORIZ << 1);
    uiPictHeight >>= 1;
    uiPictWidth >>= 1;
    pubSrc = pubSubPictUV;
    pubSrc += (PAD_UV_PROG_VERT * uiRecWidth) + PAD_UV_HORIZ;
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
XDAS_Int32 WriteDataOut(H264VENC_OutArgs outArgs,
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
	   	refData = (XDAS_Int8*)malloc(outArgs.videncOutArgs.bytesGenerated);
       	fread(refData, 1, outArgs.videncOutArgs.bytesGenerated,
       	                                            pfOutBitStreamFile);
    	if(memcmp(refData, outArgs.videncOutArgs.encodedBuf.buf,
    	                            outArgs.videncOutArgs.bytesGenerated))
    	{
      		retVal = XDM_EFAIL;
    	}

		free(refData);
	}
	else
	{
        fwrite(outArgs.videncOutArgs.encodedBuf.buf, sizeof(XDAS_Int8),
               outArgs.videncOutArgs.bytesGenerated, pfOutBitStreamFile);
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

    while (sTokenMap[lInstance][i].tokenName != NULL)
    {
        if (0==strcmp (sTokenMap[lInstance][i].tokenName, s))
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
        if(sTokenMap[lInstance][MapIdx].bType == 1)
        {
            strcpy((XDAS_Int8 *)sTokenMap[lInstance][MapIdx].place, items[i+2]);
            /* sscanf (items[i+2], "%s", StringContent); */
        }
        else
        {
            sscanf (items[i+2], "%d", &IntContent);
            * ((XDAS_Int32 *) (sTokenMap[lInstance][MapIdx].place)) = IntContent;
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
