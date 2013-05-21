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

//#ifdef ENABLE_ARM926_TCM
//Include only if linux build is used
#ifdef ON_LINUX
#include <ti/sdo/fc/ires/memtcm/ires_memtcm.h>
#include <ti/sdo/fc/ires/memtcm/iresman_memtcm.h>
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
#ifdef ON_LINUX
void ARM926_Icache_Disable()
{
    return;
}
void ARM926_Dcache_Disable()
{
    return;
}
#endif
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
//#define PROFILE_ONLINUX_ARM968
#ifdef PROFILE_ONLINUX_ARM968
extern XDAS_UInt32 max_time_arm968;
extern XDAS_UInt32 total_time_arm968;
#endif

#ifdef LOW_LATENCY_FEATURE
XDAS_UInt8 gSliceFormat = 0;
FILE *gFpOutBitStream = NULL;
XDM_BufDesc *gOutObj = NULL;
extern XDAS_Int32 getEncodedSliceProvideSpace(
    IH264VENC_TI_DataSyncHandle dataSyncHandle,
    IH264VENC_TI_DataSyncDesc *dataSyncDesc);
#endif //LOW_LATENCY_FEATURE
//XDAS_Int32 PACKET_SIZES[200];
//static GT_Mask someGTMask;

extern unsigned char gORG_Y_1[0x200000];
extern unsigned char gORG_C_1[0x100000];
extern unsigned char gORG_Y_2[0x200000];
extern unsigned char gORG_C_2[0x100000];
unsigned int gframe_count = 0;
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
    xdc_Char *tokenName;
    xdc_Char bType;
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
static xdc_Char buf[20000];
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
    xdc_Char *s
);
static xdc_Char *
GetConfigFileContent (
    FILE *fname
);

static XDAS_Int32
readparamfile (
    FILE * fname
);

static XDAS_Int32
ParseContent (
    xdc_Char *buf,
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
    unsigned int uiPictHeight,
    unsigned int uiRecPitch,
    unsigned int uiContentType
);

static void
printErrorMsg(
    XDAS_Int32 errorCode
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
#define MAX_WIDTH           2048
#define MAX_HEIGHT          2048
#define MAX_QP              51
#define MIN_QP              0


#define MAX_FRAMES_TO_ENCODE 5000
//#define PROFILE_ONLINUX


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
main(XDAS_Int32 argc, xdc_Char **argv)
{
    H264VENC_Handle  handle;  /* Handle to the Encoder instance      - XDAIS */
    IH264VENC_Fxns fxns;      /* Function table for the H.264 Encoder- XDAIS */
    H264VENC_Params params;   /* Instance creation Parameter         - XMI   */
    H264VENC_Status status;   /* Stores the status of process call   - XDM   */
    H264VENC_InArgs inargs;   /* Input Parameter to the process call - XDM   */
    H264VENC_OutArgs outargs; /* Ouput parameters from process call  - XDM   */
    H264VENC_DynamicParams dynamicparams; /* Dynamic Parameter struct- XDM   */
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
    xdc_Char  bWriteEncodedData;       /* Switch for Bitstream write out   */
    xdc_Char  bWriteReconData;         /* Switch for Recon write out       */
    xdc_Char  bWriteSADandMV;
    xdc_Char  bSEIFlagOut;              /* Switch for adding SEI userdata   */
    xdc_Char  bInputFile[400];         /* Input file name                  */
    xdc_Char  bEncOutFile[400];        /* Encoded output file name         */
    xdc_Char  bReconOutFile[400];      /* Reconstructed decoded output file*/
    xdc_Char  bConfigFile[400];        /* Config Parameters */
    xdc_Char  line[400];
    XDAS_Int8  lib_version[400] = "LIB";            /* Library version number */
#ifdef ENABLE_ROI
    xdc_Char  bROIFile[400];           /* ROI Parameters */
#endif
    XDAS_Int32  testCompliance;
    XDAS_Int32 retVal;
    XDAS_Int32 iSkipCnt;                /* Variable for keeping skip count  */
    XDAS_Int32 iStatus;                 /* Flag for file read error check */
    XDAS_Int32 loopcnt;

    XDAS_Int32 NumUnitsInTick = 2;
    XDAS_Int32 TimeScale = 60;
    
    FILE *pfConfigParamsFile;  /* Pointer to the Configuration File         */
    FILE *pfInputYUVFile;      /* Pointer to the Input Video YUV File       */
    FILE *pfOutBitStreamFile;  /* Pointer to the output BitStream File      */
    FILE *pfOutYUVFile;        /* Pointer to the output reconstructed File  */
    FILE *pfConfigFileList ;   /* Pointer to the list of Config Files */
#ifdef ENABLE_ROI
    FILE *pfROIParamsFile;     /* Pointer to the ROI params File            */
#endif
    XDAS_Int32 configFileCount =0;
    IRES_Status iresStatus;
#ifdef DEVICE_ID_CHECK
    //IRESMAN_AddrSpaceParams addrspaceConfigParams;
#endif
#ifdef ON_LINUX
    /* This is used as temporary variable to change the path, reading from
     * config files. */
    xdc_Char *bChangeDirForConfigFile;  /* Config file directory change */
#ifdef ENABLE_ROI
    xdc_Char *bChangeDirForROIFile;     /* ROI file directory change */
#endif
#endif

  /******** rrr ****************/
  /* sample structure for customized VUI */
   tCustomizedVUIbuffer_Interface gtCustomizedVUIbuffer =
      { 143, { 0xff,  0x80, 0x28, 0x00, 0x10,
			   0xa1,  0x01, 0x01, 0x01, 0x40,
			   0x00,  0x00, 0xfa, 0x40, 0x00,
			   0x3a,  0x98, 0x24 }
	  };
  /*************************/
#ifdef PROFILE_ONLINUX
    XDAS_UInt32 time_before_process, time_after_process;
    XDAS_UInt32 time_max;
    struct timeval encoder_time, *encoder_timeptr;
//    static unsigned int frame_count_p, total_time_p;
    long frame_count_p, total_time_p;
#endif
    FILE *SadMvFilePtr; /* File Pointer to file for writing profile figures */
#ifdef _PROFILE
    /* Open a output file for profile data */
    FILE *profFilePtr; /* File Pointer to file for writing profile figures */
    profFilePtr = fopen("..\\..\\..\\Test\\TestVecs\\Output\\profile.txt", "w");
#endif //_PROFILE
#ifndef ON_LINUX
    SadMvFilePtr = fopen("../../../test/testvecs/output/sadmvinfo.txt", "w");
#else
    SadMvFilePtr = fopen("../../test/testvecs/output/sadmvinfo.txt", "w");
#endif
    if(SadMvFilePtr == NULL)
    {
        printf("\nCODEC_DEBUG_ENABLE: ERROR! - Could Not open the file to dump Mv and SAD %s\n", SadMvFilePtr);
        exit(-1);
    }
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
    XDAS_UInt32 ProfDataArray[MAX_FRAMES];
    FILE *pfProfFile =
        fopen("..\\..\\..\\Test\\TestVecs\\Output\\ProfileData.txt", "w");
    if(pfProfFile == NULL)
    {
        printf("\nCODEC_DEBUG_ENABLE: ERROR! - Could Not open Profile Log File %s", pfProfFile);
        exit(-1);
    }
#endif /* #ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926 */
#ifdef ON_LINUX
    LockMP_init();
    SemMP_init();
    Memory_init();
    GT_init();
    Global_init();
    Sem_init();
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
    bWriteSADandMV = 1;

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
        printf("CODEC_DEBUG_ENABLE: RMAN initialization Failed \n");
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
        printf("CODEC_DEBUG_ENABLE: EDMA3 Protocol Registration Failed \n");
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
        printf("CODEC_DEBUG_ENABLE: VICP Protocol Registration Failed \n");
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
        printf("CODEC_DEBUG_ENABLE: VICP Protocol Registration Failed \n");
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
        printf("CODEC_DEBUG_ENABLE: ADDRSPACE Protocol Registration Failed \n");
        return -1;
    }
    printf("CODEC_DEBUG_ENABLE: ADDRSPACE Protocol Registration Success \n");
    }
#endif
#endif

//#ifdef ENABLE_ARM926_TCM
#ifdef ON_LINUX
    {
    IRESMAN_MemTcmParams memTcmConfigParams;
    /*
     * Supply initialization information for the ADDRSPACE RESMAN while registering
     *           */
    memTcmConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    memTcmConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    memTcmConfigParams.baseConfig.size = sizeof(IRESMAN_MemTcmParams);;

    iresStatus = RMAN_register(&IRESMAN_MEMTCM, (IRESMAN_Params *)&memTcmConfigParams);

    if (IRES_OK != iresStatus) {
        printf("CODEC_DEBUG_ENABLE: MEMTCM Protocol Registration Failed \n");
        return -1;
    }
    printf("CODEC_DEBUG_ENABLE: MEMTCM Protocol Registration Success \n");
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
#endif
    if(pfConfigFileList == NULL)
    {
        printf("CODEC_DEBUG_ENABLE:  ERROR! - Could Not open Config File %s", pfConfigFileList);
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

#ifdef ENABLE_ROI
        /* Read ROI input file name */
        if(fgets(line, 254, pfConfigFileList))
        {
            sscanf(line,"%s",bROIFile);
        }
        else
        {
            break ;
        }
#endif
        /* Point the param pointer to default parameters from encoder */
        params = H264VENC_PARAMS;
        dynamicparams.VUI_Buffer = &VUIPARAMSBUFFER;
		dynamicparams.CustomScaleMatrix_Buffer = &CUSTOMSEQSCALEMATRICES;
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
            &dynamicparams.videncDynamicParams.inputHeight;

        sTokenMap[uiTokenCtr].tokenName = "ImageWidth";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &dynamicparams.videncDynamicParams.inputWidth;

        sTokenMap[uiTokenCtr].tokenName = "FrameRate";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &dynamicparams.videncDynamicParams.targetFrameRate;

        sTokenMap[uiTokenCtr].tokenName = "BitRate";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &dynamicparams.videncDynamicParams.targetBitRate;

        sTokenMap[uiTokenCtr].tokenName = "ChromaFormat";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &params.videncParams.inputChromaFormat;

        sTokenMap[uiTokenCtr].tokenName = "InterlacedVideo";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &params.videncParams.inputContentType;

        sTokenMap[uiTokenCtr].tokenName = "IntraPeriod";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &dynamicparams.videncDynamicParams.intraFrameInterval;

        sTokenMap[uiTokenCtr].tokenName = "IDRFramePeriod";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &dynamicparams.idrFrameInterval;
		
        sTokenMap[uiTokenCtr].tokenName = "ME_Type";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.meAlgo;
		
        sTokenMap[uiTokenCtr].tokenName = "RC_PRESET";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   =
            &params.videncParams.rateControlPreset;

		sTokenMap[uiTokenCtr].tokenName = "ENC_PRESET";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.videncParams.encodingPreset;

        sTokenMap[uiTokenCtr].tokenName = "SliceSize";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.sliceSize;

        sTokenMap[uiTokenCtr].tokenName = "RateControl";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.rcAlgo;

        sTokenMap[uiTokenCtr].tokenName = "MaxDelay";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.maxDelay;

        sTokenMap[uiTokenCtr].tokenName = "AspectRatioWidth";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.aspectRatioX;

        sTokenMap[uiTokenCtr].tokenName = "AspectRatioHeight";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.aspectRatioY;

        sTokenMap[uiTokenCtr].tokenName = "EnableVUIParam";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.enableVUIparams;

        sTokenMap[uiTokenCtr].tokenName = "EnableBufSEI";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.enableBufSEI;

        sTokenMap[uiTokenCtr].tokenName = "QPInit";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.initQ;

        sTokenMap[uiTokenCtr].tokenName = "QPISlice";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.intraFrameQP;

        sTokenMap[uiTokenCtr].tokenName = "QPSlice";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.interPFrameQP;

        sTokenMap[uiTokenCtr].tokenName = "MaxQP";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.rcQMax;

        sTokenMap[uiTokenCtr].tokenName = "MinQP";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.rcQMin;

        sTokenMap[uiTokenCtr].tokenName = "MaxQPI";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.rcQMaxI;

        sTokenMap[uiTokenCtr].tokenName = "MinQPI";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.rcQMinI;

        sTokenMap[uiTokenCtr].tokenName = "ProfileIDC";
        sTokenMap[uiTokenCtr].bType     = 0;
        sTokenMap[uiTokenCtr++].place   = &params.profileIdc;

        sTokenMap[uiTokenCtr].tokenName = "LevelIDC";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.levelIdc;

        sTokenMap[uiTokenCtr].tokenName = "Log2MaxFrameNumMinus4";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.Log2MaxFrameNumMinus4;

        sTokenMap[uiTokenCtr].tokenName = "ConstraintFlag";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.ConstraintSetFlag;

        sTokenMap[uiTokenCtr].tokenName = "AirRate";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.airRate;

        sTokenMap[uiTokenCtr].tokenName = "LoopFilterDisable";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.lfDisableIdc;

        sTokenMap[uiTokenCtr].tokenName = "PerceptualRC";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.perceptualRC;

        sTokenMap[uiTokenCtr].tokenName = "EntropyCodingMode";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.entropyMode;

        sTokenMap[uiTokenCtr].tokenName = "Transform8x8FlagIntra";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.transform8x8FlagIntraFrame;

        sTokenMap[uiTokenCtr].tokenName = "Transform8x8FlagInter";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.transform8x8FlagInterFrame;

        sTokenMap[uiTokenCtr].tokenName = "SequenceScalingFlag";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.seqScalingFlag;

        sTokenMap[uiTokenCtr].tokenName = "EncoderQuality";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.encQuality;

        sTokenMap[uiTokenCtr].tokenName = "mvSADout";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.mvSADoutFlag;

        sTokenMap[uiTokenCtr].tokenName = "useARM926Tcm";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.enableARM926Tcm;

        sTokenMap[uiTokenCtr].tokenName = "enableROI";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.enableROI;

        sTokenMap[uiTokenCtr].tokenName = "mapIMCOPtoDDR";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.enableDDRbuff;

#ifdef ENABLE_ROI

        sTokenMap[uiTokenCtr].tokenName = "NumOfROI";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.numOfROI;

        sTokenMap[uiTokenCtr].tokenName = "ROI_1_Xmin";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[0].topLeft.x;

        sTokenMap[uiTokenCtr].tokenName = "ROI_1_Ymin";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[0].topLeft.y;

        sTokenMap[uiTokenCtr].tokenName = "ROI_1_Xmax";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[0].bottomRight.x;

        sTokenMap[uiTokenCtr].tokenName = "ROI_1_Ymax";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[0].bottomRight.y;

        sTokenMap[uiTokenCtr].tokenName = "ROI_1_prty";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.roiPriority[0];

        sTokenMap[uiTokenCtr].tokenName = "ROI_1_type";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.roiType[0];

        sTokenMap[uiTokenCtr].tokenName = "ROI_2_Xmin";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[1].topLeft.x;

        sTokenMap[uiTokenCtr].tokenName = "ROI_2_Ymin";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[1].topLeft.y;

        sTokenMap[uiTokenCtr].tokenName = "ROI_2_Xmax";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[1].bottomRight.x;

        sTokenMap[uiTokenCtr].tokenName = "ROI_2_Ymax";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.listROI[1].bottomRight.y;

        sTokenMap[uiTokenCtr].tokenName = "ROI_2_prty";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.roiPriority[1];

        sTokenMap[uiTokenCtr].tokenName = "ROI_2_type";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &inargs.roiParameters.roiType[1];

#endif
#ifdef SIMPLE_TWO_PASS
        sTokenMap[uiTokenCtr].tokenName = "metaDataGenerateConsume";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.metaDataGenerateConsume;
#endif
        sTokenMap[uiTokenCtr].tokenName = "sliceMode";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.sliceMode;

        sTokenMap[uiTokenCtr].tokenName = "numTemporalLayers";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.numTemporalLayers;

        sTokenMap[uiTokenCtr].tokenName = "svcSyntaxEnable";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.svcSyntaxEnable;

#ifdef LOW_LATENCY_FEATURE
        sTokenMap[uiTokenCtr].tokenName = "outputDataMode";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.outputDataMode;

        sTokenMap[uiTokenCtr].tokenName = "sliceFormat";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.sliceFormat;
#endif //LOW_LATENCY_FEATURE

        sTokenMap[uiTokenCtr].tokenName = "interlaceRefMode";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.interlaceRefMode;

        sTokenMap[uiTokenCtr].tokenName = "maxBitrateCVBR";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.maxBitrateCVBR;
		  

        sTokenMap[uiTokenCtr].tokenName = "enableGDR";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.enableGDR;

        sTokenMap[uiTokenCtr].tokenName = "GDRinterval";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.GDRinterval;

        sTokenMap[uiTokenCtr].tokenName = "GDRduration";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.GDRduration;
          
        sTokenMap[uiTokenCtr].tokenName = "LongTermRefreshInterval";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &dynamicparams.LongTermRefreshInterval;

        sTokenMap[uiTokenCtr].tokenName = "EnableLongTermFrame";
        sTokenMap[uiTokenCtr].bType     = 0 ;
        sTokenMap[uiTokenCtr++].place   = &params.EnableLongTermFrame;

          
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
            printf("CODEC_DEBUG_ENABLE: ERROR! - Could Not open Config File %s\n", bConfigFile);
            continue;
        }
        printf("CODEC_DEBUG_ENABLE: Reading Configuration file %s...\n",bConfigFile);
        /* pass config file for parsing */
        if(readparamfile(pfConfigParamsFile) != 0)
        {
            printf("CODEC_DEBUG_ENABLE: ERROR! - Unable to read Config File %s\n", bConfigFile);
            fclose(pfConfigParamsFile);
            continue;
        }
        //fclose(pfConfigParamsFile);
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        fprintf(pfProfFile, "\nCODEC_DEBUG_ENABLE: Configuration file: %s...\n",bConfigFile);
#endif //ENABLE_PROFILE_AT_FRM_LVL_ON_926

#ifdef ENABLE_ROI
#ifndef ON_LINUX
        pfROIParamsFile = fopen(bROIFile, "r");
#else
    /* One ../ should be removed for the config file path to run on linux */
    bChangeDirForROIFile = bROIFile;
    bChangeDirForROIFile += CHANGE_PATH;
    pfROIParamsFile = fopen(bChangeDirForROIFile, "r");
#endif
        if(pfROIParamsFile == NULL)
        {
            printf("CODEC_DEBUG_ENABLE: ERROR! - Could Not open ROI File %s\n", bROIFile);
            continue;
        }
        printf("CODEC_DEBUG_ENABLE: Reading Configuration file %s...\n",bROIFile);
        /* pass config file for parsing */
        if(readparamfile(pfROIParamsFile) != 0)
        {
            printf("CODEC_DEBUG_ENABLE: error");
            printf("ERROR! - Unable to read Config File %s\n", bROIFile);
            fclose(pfROIParamsFile);
            continue;
        }
#endif

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
        uiExtWidth =
            (dynamicparams.videncDynamicParams.inputWidth + 15) & ~0x0F;

        if(params.videncParams.inputContentType == 0)
        {
            /* Progressive case */
        uiExtHeight =
            (dynamicparams.videncDynamicParams.inputHeight + 15) & ~0x0F;
        }
        else
        {
            /* Interlaced case */
            uiExtHeight =
                (dynamicparams.videncDynamicParams.inputHeight + 31) & ~0x1F;
        }

        uiFrmPitch = uiExtWidth;

        if(testCompliance)
        {
            printf("CODEC_DEBUG_ENABLE: Running in reference bit-stream complaince check Mode\n");
        }
        else
        {
            printf("CODEC_DEBUG_ENABLE: Running in Output Dump Mode\n");
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
                    printf("CODEC_DEBUG_ENABLE:  ERROR! -Could Not open Output bitstream File %s",
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
            pubYRecon = malloc(uiSize * sizeof(xdc_Char));
            pubURecon = malloc((uiSize >> 2) * sizeof(xdc_Char));
            pubVRecon = malloc((uiSize >> 2) * sizeof(xdc_Char));
        }

        /* Allocate memory for the input frame */
        {
            XDAS_UInt32 uiFrmSize = uiFrmPitch * uiExtHeight;

            pubInY = (XDAS_UInt8 *) malloc(uiFrmSize * sizeof(XDAS_UInt8));
            pubInU =
                (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
            pubInV =
                (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));

            memset(pubInY, 0, uiFrmSize);
            memset(pubInU, 128, (uiFrmSize >> 2));
            memset(pubInV, 128, (uiFrmSize >> 2));
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
        /*                       DYNAMIC PARAMETERS INTIALIZATION             */
        /*--------------------------------------------------------------------*/
#ifdef BASE_PARAMS
        dynamicparams.videncDynamicParams.size = sizeof(IVIDENC1_DynamicParams);
        bSEIFlagOut = bSEIFlagOut & 0;
#else
        dynamicparams.videncDynamicParams.size = sizeof(IH264VENC_DynamicParams);
        bSEIFlagOut = bSEIFlagOut & 1;
#endif
        dynamicparams.videncDynamicParams.refFrameRate =
            dynamicparams.videncDynamicParams.targetFrameRate;
        dynamicparams.videncDynamicParams.generateHeader = 0;
        dynamicparams.videncDynamicParams.captureWidth =
        (uiFrmPitch << params.videncParams.inputContentType);
        dynamicparams.videncDynamicParams.forceFrame = IVIDEO_NA_FRAME;
        dynamicparams.videncDynamicParams.interFrameInterval = 0;
        dynamicparams.videncDynamicParams.mbDataFlag = 0;
        dynamicparams.enablePicTimSEI = dynamicparams.enableBufSEI;
        dynamicparams.resetHDVICPeveryFrame = 0;
        dynamicparams.disableMVDCostFactor = 0;
        dynamicparams.UseLongTermFrame = 0;
        dynamicparams.SetLongTermFrame = 0;
        dynamicparams.LBRmaxpicsize = 0;
		dynamicparams.LBRminpicsize = 0;
        dynamicparams.CVBRsensitivity = 0;
        dynamicparams.maxHighCmpxIntCVBR = 0;
        
#ifdef LOW_LATENCY_FEATURE
        dynamicparams.putDataGetSpaceFxn = getEncodedSliceProvideSpace;
        dynamicparams.dataSyncHandle = NULL;
#endif //LOW_LATENCY_FEATURE

//        numTicksPerFrame = ((dynamicparams.VUI_Buffer->time_scale/dynamicparams.VUI_Buffer->num_units_in_tick) * 1000)/
//                           (dynamicparams.videncDynamicParams.targetFrameRate);
        numTicksPerFrame = ((TimeScale / NumUnitsInTick) * 1000) / (dynamicparams.videncDynamicParams.targetFrameRate);
        //if(configFileCount == 1)
        {
        /*--------------------------------------------------------------------*/
        /*                       STATIC PARAMETERS INTIALIZATION              */
        /*--------------------------------------------------------------------*/

#ifdef BASE_PARAMS
        params.videncParams.size = sizeof(IVIDENC1_Params);
#else
        params.videncParams.size = sizeof(IH264VENC_Params);
#endif
        params.videncParams.maxWidth = MAX_WIDTH;//uiExtWidth;
        params.videncParams.maxHeight = MAX_HEIGHT;//uiExtHeight;
        params.videncParams.maxBitRate = 20000000;
        params.videncParams.maxFrameRate = 120000;
        if(bWriteReconData == 0)
        {
            params.videncParams.reconChromaFormat = IH264VENC_YUV_420IUV;
        }
        /* Xena hardware provides only single VIMCOP which is indexed by 0 */
        //params.imcop_selector = 0; /* Allways 0 */

        /* DMA initialization parameter should be set before Encoder creation as
         * DMA will be configured based on these parameters during creation.
         * Setting of these parameters is done through the following function
         * defined in file testapp_idma.c. Application writer can update this
         * file
         */

        /* Encoder Create function - Calls ALG Framework function -
         * ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
         */

        if((handle = H264VENC_create(&fxns, &params)) == NULL)
        {
            printf("CODEC_DEBUG_ENABLE: ERROR! - Encoder Creation Failed");
            fflush(stdout);
            goto FREE_FRAME_IO_BUFFERS; /* Creation failed - exit the encoder */
        }
        printf("\nCODEC_DEBUG_ENABLE: First Encoder Creation Done\n");
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

        /**********************************************************************/
        /* Activate all IRES resources                                        */
        /**********************************************************************/
        H264VENC_TI_IRES.activateAllResources((IALG_Handle)handle);

        /*--------------------------------------------------------------------*/
        /*              Check for any warnings set at create time             */
        /*--------------------------------------------------------------------*/
        status.videncStatus.size = sizeof(IH264VENC_Status);
        status.videncStatus.data.bufSize = sizeof(lib_version);
        status.videncStatus.data.buf = lib_version;
        iErrorFlag = H264VENC_control(
            handle,         // Instance Handle
            XDM_GETSTATUS,  // Command
            &dynamicparams, // Pointer to Dynamic Params structure -Input
            &status         // Pointer to the status structure - Output
        );

        if(iErrorFlag == XDM_EFAIL)
        {
            printf("Get Status Info Command Failed\n");
            printErrorMsg(status.videncStatus.extendedError);
            goto FREE_ENCODER_OBJECT;
        }

        if(status.videncStatus.extendedError)
        printErrorMsg(status.videncStatus.extendedError);

        iErrorFlag = H264VENC_control(
            handle,         // Instance Handle
            XDM_GETVERSION, // Command
            &dynamicparams, // Pointer to Dynamic Params structure -Input
            &status         // Pointer to the status structure - Output
        );

        if(iErrorFlag == XDM_EFAIL)
        {
            printf("Get Status Info Command Failed\n");
            printErrorMsg(status.videncStatus.extendedError);
            goto FREE_ENCODER_OBJECT;
        }
        printf("CODEC_DEBUG_ENABLE: 2nd Library Version %s\n",lib_version);

#if 0
        if(status.videncStatus.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
        {
            printf("Parameter not supported\n");
        }
        if(status.videncStatus.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
        {
            printf("CODEC_DEBUG_ENABLE: Input not supported\n");
        }
#endif

        } //end of if(configFileCount == 1)
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
        status.videncStatus.size = sizeof(IH264VENC_Status);
        iErrorFlag = H264VENC_control(
            handle,         // Instance Handle
            XDM_GETBUFINFO, // Command
            &dynamicparams, // Pointer to Dynamic Params structure -Input
            &status         // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
            printf("CODEC_DEBUG_ENABLE: Get Buffer Info Command Failed\n");
            goto FREE_ENCODER_OBJECT;
        }

        /*--------------------------------------------------------------------*/
        /*            GET H.264 ENCODER INPUT/OUTPUT BUFFER INFORMATION       */
        /*--------------------------------------------------------------------*/
        /* Based on the Num of buffers requested by the algorithm, the
         * application will allocate for the same here
         */
        memParams.flags=CMEM_NONCACHED;
        if(AllocateH264IOBuffers(
            status, // status structure - Input
            &inobj, // Pointer to Input Buffer Descriptor - Output
            &outobj) // Pointer to Output Buffer Descriptor - Output
        )
        {
            printf("CODEC_DEBUG_ENABLE: Not Enough Memory\n");
            FreeH264IOBuffers(
                &inobj, // Pointer to Input Buffer Descriptor - Input
                &outobj // Pointer to Output Buffer Descriptor - Input
            );
            goto FREE_FRAME_IO_BUFFERS;
        }
        memParams.flags=CMEM_CACHED;
        inobj.frameHeight = uiExtHeight;
        inobj.frameWidth = uiExtWidth;
        inobj.framePitch = uiFrmPitch;
        if((dynamicparams.videncDynamicParams.captureWidth == 0) ||
           (dynamicparams.videncDynamicParams.captureWidth < uiExtWidth))
        {
            inobj.framePitch = uiExtWidth;
        }

		/****************** rrr ***************/
		if(params.enableVUIparams & 8)
		{
		 /* initialize the VUI buffer with User defined encoded VUI parameters */
         memcpy(inobj.bufDesc[inobj.numBufs - 1].buf,
                 &gtCustomizedVUIbuffer,
                 sizeof(tCustomizedVUIbuffer_Interface) );
		}
		 
		/**************************************/
        /*--------------------------------------------------------------------*/
        /*                     SET DYNAMIC INPUT PARAMETERS                   */
        /*--------------------------------------------------------------------*/

        iErrorFlag = H264VENC_control(
            handle,        // Instance Handle
            XDM_SETPARAMS, // Command
            &dynamicparams,// Pointer to Dynamic structure - Input
            &status        // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
            printf("Set Encoder parameters Command Failed\n");
            printErrorMsg(status.videncStatus.extendedError);
            goto FREE_ENCODER_IO_BUFFERS;
        }

        if(status.videncStatus.extendedError)
        printErrorMsg(status.videncStatus.extendedError);
#if 0
        if(status.videncStatus.extendedError & (1 << XDM_UNSUPPORTEDPARAM))
        {
            printf("Parameter not supported\n");
        }
        if(status.videncStatus.extendedError & (1 << XDM_UNSUPPORTEDINPUT))
        {
            printf("CODEC_DEBUG_ENABLE: Input not supported\n");
        }
#endif

        /* Initialize Input Arguements */
#ifdef BASE_PARAMS
        inargs.videncInArgs.size = sizeof(IVIDENC1_InArgs);
#else
        inargs.videncInArgs.size = sizeof(IH264VENC_InArgs);
#ifdef SEI_USERDATA_INSERTION
        /* Input to the codec, to provide the space for adding SEI userdata unregistered
         * into the bitstream */
        inargs.insertUserData = (1 * bSEIFlagOut);
        inargs.lengthUserData = (60 * bSEIFlagOut);
#endif
#endif
        inargs.videncInArgs.inputID = 1;
        inargs.videncInArgs.topFieldFirstFlag = XDAS_TRUE;
        inargs.timeStamp = 0;

#ifdef LOW_LATENCY_FEATURE
        /* If outputDataMode is chosen as slice mode(0), than codec produces */
        /* encoded slice after numOutputDataUnits slices are encode          */
        inargs.numOutputDataUnits = 1;

        gSliceFormat = params.sliceFormat;
        gFpOutBitStream = pfOutBitStreamFile;
        gOutObj = &outobj;
#endif //LOW_LATENCY_FEATURE

        /* Initialize Output Arguments */
#ifdef BASE_PARAMS
        outargs.videncOutArgs.size = sizeof(IVIDENC1_OutArgs);
#else
        outargs.videncOutArgs.size = sizeof(IH264VENC_OutArgs);
#endif
        outargs.videncOutArgs.extendedError = 0;
        outargs.videncOutArgs.bytesGenerated = 0;
        outargs.videncOutArgs.encodedFrameType = IVIDEO_NA_FRAME;
        outargs.videncOutArgs.inputFrameSkip = IVIDEO_FRAME_ENCODED;
        outargs.videncOutArgs.outputID = 1;
        outargs.numPackets = 0;
        //outargs.packetSize = PACKET_SIZES;
/*#ifdef PASS_SAD_MV_APPL
        outargs.puiSadMVinfo =
            (XDAS_Int8 *) CMEM_alloc((inobj.frameHeight >> 4) * (inobj.frameWidth >> 4) * 8 *
             sizeof(XDAS_Int8), &memParams);
#endif //PASS_SAD_MV_APPL */

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
        printf("CODEC_DEBUG_ENABLE: Starting Encode...\n");
        /*--------------------------------------------------------------------*/
        /*                                  ENCODE LOOP                       */
        /*--------------------------------------------------------------------*/
        if(params.videncParams.inputContentType == 1) // Interlaced content
        {
            /* Process call corresponds to Odd field */
            inobj.bufDesc[0].buf += (dynamicparams.videncDynamicParams.captureWidth >> 1);
            inobj.bufDesc[1].buf += (dynamicparams.videncDynamicParams.captureWidth >> 1);
        }

        uiNumFrames = 0;
#ifdef PROFILE_ONLINUX		
        total_time_p = 0;
        time_max = 0;
#endif		
#ifdef PROFILE_ONLINUX_ARM968
        max_time_arm968 = 0;
        total_time_arm968 = 0 ;
#endif
        while(uiNumFrames < (uiNumFramesToBeEncoded << params.videncParams.inputContentType) &&
              !feof(pfInputYUVFile))
        /*for(uiNumFrames = 0; uiNumFrames < uiNumFramesToBeEncoded;
            uiNumFrames++)*/
        {
            /* Implement any Dynamic Parameter changes here
             * (Call H264VENC_control()
             * with approriate command and parameters).
             */
#ifdef UPDATE_PARAMS_AT_RUN_TIME
            //dynamicparams.QPISlice = uiNumFrames%51;
            //dynamicparams.QPSlice = uiNumFrames%51;
#if 0
            if(uiNumFrames == 25)
            {
                //dynamicparams.videncDynamicParams.targetFrameRate = 15000;
                //dynamicparams.videncDynamicParams.targetBitRate = 64000;
                //dynamicparams.QPInit = 40;
                //numTicksPerFrame =
                //  ((params.TimeScale/params.NumUnitsInTicks) * 1000)/
                //          (dynamicparams.videncDynamicParams.targetFrameRate);
                //dynamicparams.sliceSize = 1000;
                //dynamicparams.IntraSliceNum = 0;
                NumUnitsInTick = dynamicparams.VUI_Buffer->numUnitsInTicks;
                Timescale = dynamicparams.VUI_Buffer->timeScale;
                dynamicparams.VUI_Buffer->timeScale = 6000;
                dynamicparams.VUI_Buffer->numUnitsInTicks = 100;
            }

            if(uiNumFrames == 40)
            {
               dynamicparams.VUI_Buffer->video_signal_type_present_flag = 1;
               dynamicparams.VUI_Buffer->video_format = 0;
            }
            
            if(uiNumFrames == 70)
            {
               dynamicparams.VUI_Buffer->colour_description_present_flag = 1;
               dynamicparams.VUI_Buffer->colour_primaries = 1;
            }
#endif
            if(uiNumFrames == 35)
            {
               dynamicparams.SetLongTermFrame = 1;
            }
            
            if(uiNumFrames == 65)
            {
               dynamicparams.UseLongTermFrame = 1;
            }

            iErrorFlag = H264VENC_control(
                handle,        // Instance Handle
                XDM_SETPARAMS, // Command
                &dynamicparams,// Pointer to Dynamic structure - Input
                &status        // Pointer to the status structure - Output
            );
            if(iErrorFlag == XDM_EFAIL)
            {
                printf("CODEC_DEBUG_ENABLE: Set Encoder parameters Command Failed\n");
                printErrorMsg(status.videncStatus.extendedError);
                goto FREE_ENCODER_IO_BUFFERS;
            }
#endif //UPDATE_PARAMS_AT_RUN_TIME
            /*----------------------------------------------------------------*/
            /*                              SET INPUTS                        */
            /*----------------------------------------------------------------*/
            /* The Inputs for the encode call are:
             * - YUV Frame - To be read from the input file.
             * - Any Dynamic Parameter Changes.
             */
            if(params.videncParams.inputContentType == 1) // Interlaced content
            {
                if((uiNumFrames & 0x01))
                {
                    /* Process call corresponds to Odd field */
                    inobj.bufDesc[0].buf += (dynamicparams.videncDynamicParams.captureWidth >> 1);
                    inobj.bufDesc[1].buf += (dynamicparams.videncDynamicParams.captureWidth >> 1);
                }
                else
                {
                    /* Process call corresponds to even field */
                    inobj.bufDesc[0].buf -= (dynamicparams.videncDynamicParams.captureWidth >> 1);
                    inobj.bufDesc[1].buf -= (dynamicparams.videncDynamicParams.captureWidth >> 1);
                }
            }
            if(params.videncParams.inputContentType == 1) // Interlace Content
            {
                if((uiNumFrames & 0x01) == 0)
                {
#ifdef DEBUG_ENABLE
				   printf("CODEC_DEBUG_ENABLE: Reading Input Frame - \n");
                   fflush(stdout);
#endif                   
				  
                    iStatus = ReadInputData(
                        inobj,
                        dynamicparams.videncDynamicParams.inputWidth,
                        dynamicparams.videncDynamicParams.inputHeight,
                        uiFrmPitch,
                        uiExtHeight,
                        pfInputYUVFile
                    );

                    if(iStatus)
                    {
                        printf("CODEC_DEBUG_ENABLE: Input Frame Read Failed\n");
                        break;
                    }
                    else
                    {
#ifdef DEBUG_ENABLE
                        printf("CODEC_DEBUG_ENABLE: Input Frame Read Done\n");
                        fflush(stdout);
#endif
                    }
                }
            }
            else
            {
#ifdef DEBUG_ENABLE			
                printf("CODEC_DEBUG_ENABLE: Reading Input Frame - \n");
#endif				
                fflush(stdout);
                iStatus = ReadInputData(
                    inobj,
                    dynamicparams.videncDynamicParams.inputWidth,
                    dynamicparams.videncDynamicParams.inputHeight,
                    uiFrmPitch,
                    uiExtHeight,
                    pfInputYUVFile
                );

                if(iStatus)
                {
                    printf("CODEC_DEBUG_ENABLE: Input Frame Read Failed\n");
                    break;
                }
                else
                {
#ifdef DEBUG_ENABLE				
                    printf("CODEC_DEBUG_ENABLE: Input Frame Read Done\n");
#endif					
                    fflush(stdout);
                }
            }
            /* Update InArgs */
            if(uiNumFrames)
            {
                inargs.timeStamp += numTicksPerFrame; /* TimeStamp */
            }

#ifdef ENABLE_ROI
#if 0
            {
                inargs.roiParameters.numOfROI = 5;

                inargs.roiParameters.listROI[0].topLeft.x = 80;
                inargs.roiParameters.listROI[0].topLeft.y = 128;
                inargs.roiParameters.listROI[0].bottomRight.x = 96;
                inargs.roiParameters.listROI[0].bottomRight.y = 160;
                inargs.roiParameters.roiPriority[0] = 4;
                inargs.roiParameters.roiType[0] = 0;

                inargs.roiParameters.listROI[1].topLeft.x = 256;
                inargs.roiParameters.listROI[1].topLeft.y = 128;
                inargs.roiParameters.listROI[1].bottomRight.x = 272;
                inargs.roiParameters.listROI[1].bottomRight.y = 160;
                inargs.roiParameters.roiPriority[1] = 4;
                inargs.roiParameters.roiType[1] = 0;

                inargs.roiParameters.listROI[2].topLeft.x = 0;
                inargs.roiParameters.listROI[2].topLeft.y = 0;
                inargs.roiParameters.listROI[2].bottomRight.x = 64;
                inargs.roiParameters.listROI[2].bottomRight.y = 64;
                inargs.roiParameters.roiPriority[2] = 4;
                inargs.roiParameters.roiType[2] = 0;

                inargs.roiParameters.listROI[3].topLeft.x = 300;
                inargs.roiParameters.listROI[3].topLeft.y = 250;
                inargs.roiParameters.listROI[3].bottomRight.x =352;
                inargs.roiParameters.listROI[3].bottomRight.y = 288;
                inargs.roiParameters.roiPriority[3] = 4;
                inargs.roiParameters.roiType[3] = 0;

                inargs.roiParameters.listROI[4].topLeft.x = 32;
                inargs.roiParameters.listROI[4].topLeft.y = 240;
                inargs.roiParameters.listROI[4].bottomRight.x = 64;
                inargs.roiParameters.listROI[4].bottomRight.y = 256;
                inargs.roiParameters.roiPriority[4] = 4;
                inargs.roiParameters.roiType[4] = 1;

            }
#endif
#endif
#ifdef TEST_FORCE_FRAME
        /* force every alternate frame to IDR frame */
        if(!(uiNumFrames & 0x01))
		{
		    dynamicparams.forceFrame = IVIDEO_IDR_FRAME;

        iErrorFlag = H264VENC_control(
            handle,        // Instance Handle
            XDM_SETPARAMS, // Command
            &dynamicparams,// Pointer to Dynamic structure - Input
            &status        // Pointer to the status structure - Output
        );
        if(iErrorFlag == XDM_EFAIL)
        {
            printf("Set Encoder parameters Command Failed\n");
            printErrorMsg(status.videncStatus.extendedError);
            goto FREE_ENCODER_IO_BUFFERS;
        }

        if(status.videncStatus.extendedError)
        printErrorMsg(status.videncStatus.extendedError);
        }
#endif //TEST_FORCE_FRAME

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
            iErrorFlag = H264VENC_encode (
                handle,   // Instance Handle    - Input
                &inobj,   // Input Buffers      - Input
                &outobj,  // Output Buffers     - Output
                &inargs,  // Input Parameters   - Input
                &outargs  // Output Parameters  - Output
            );

#ifdef PROFILE_ONLINUX
            time_after_process = gettimeofday(encoder_timeptr, NULL);
            //printf("time After = %d\n",encoder_timeptr->tv_usec);
            //printf("time before = %d, time after = %d\n",time_before_process,time_after_process);
        if(encoder_timeptr->tv_usec <= time_before_process)
        {

            encoder_timeptr->tv_usec += 1000000;
        }
        printf("CODEC_DEBUG_ENABLE: PROCESS LEVEL FRAME CYCLES = %d\n",(encoder_timeptr->tv_usec - time_before_process));
        total_time_p += (encoder_timeptr->tv_usec - time_before_process);
        if ((encoder_timeptr->tv_usec - time_before_process) > time_max)
           time_max = (encoder_timeptr->tv_usec - time_before_process);
        //if(frame_count_p++ == 14)
       // {
       // printf("\n");
       //         printf("CODEC_DEBUG_ENABLE: TIME TAKEN TO ENCODE 15 FRAMES AT PROCESS LEVEL = %d\n",total_time_p);
       // printf("\n");
        //total_time_p = 0;
        //frame_count_p = 0;
        //}
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
                    &dynamicparams, // Input
                    &status         // Output
                );

                printf("Encoder Returned a Failure\n");
                printf("\tFrame No              : %d\n", uiNumFrames);
                printf("\tError Status          : %d\n", iErrorFlag);
                printf("\tExtended Error Status : %d\n",
                       status.videncStatus.extendedError);
                printErrorMsg(status.videncStatus.extendedError);
                goto FREE_ENCODER_IO_BUFFERS;
            }

#if 0
            if(status.videncStatus.extendedError == XDM_FATALERROR)
            {
                goto FREE_ENCODER_IO_BUFFERS;
            }
            else
#endif
            {
                XDAS_Int32 cnt;
                uiNumBytesWritten += outargs.videncOutArgs.bytesGenerated;
                if(outargs.videncOutArgs.inputFrameSkip == IVIDEO_FRAME_SKIPPED)
                {
                    iSkipCnt++;
                    printf("CODEC_DEBUG_ENABLE: Frame : %d Skipped: ", uiNumFrames);
                }
                else
                {
#ifndef PROFILE_ONLINUX
                    printf("CODEC_DEBUG_ENABLE: Frame : %d Encoded: ", uiNumFrames);
#endif
                }
#ifndef PROFILE_ONLINUX
                printf("Bytes Generated : %d\n",
                       outargs.videncOutArgs.bytesGenerated);
				if(outargs.numPackets)	   
                printf("CODEC_DEBUG_ENABLE: Number of Packets = %d\n", outargs.numPackets);
#endif
                {
                    XDAS_Int32 *packetSizes = (XDAS_Int32*)outobj.bufs[1];
                    XDAS_Int32 numPackets = outargs.numPackets;

                    /* Maximum slice sizes exported by encoder is 200 */
                    if(numPackets > 200)
                    {
                        numPackets = 200;
                    }

                    for(cnt = 0; cnt < numPackets; cnt++)
                    {
#ifndef PROFILE_ONLINUX
                        printf("CODEC_DEBUG_ENABLE: Packet No.%4d: Size:-%8d\n",
                                cnt, packetSizes[cnt]);
#endif
                        if (params.sliceMode == 1)
						{
						   if((dynamicparams.sliceSize > 0) &&
                              ((packetSizes[cnt] << 3) > dynamicparams.sliceSize)
                           )
                           {
                               printf("CODEC_DEBUG_ENABLE: Packet Size exceeded for the prev packet\n");
                           }
						}
                    }
                }

            }
            if(bSEIFlagOut)
            {
                printf("CODEC_DEBUG_ENABLE: Userdata unregistered SEI offset in Bytes in the bitstream = %d\n", outargs.offsetUserData);
            }

            /*----------------------------------------------------------------*/
            /*                      ADDITIONAL PROCESSING                     */
            /*----------------------------------------------------------------*/
            /* Currently there is no additional processing - */
//#ifdef PASS_SAD_MV_APPL
            if(bWriteSADandMV && (dynamicparams.mvSADoutFlag == 1))
            {
                XDAS_UInt32 cntRow, cntCol, cnt;
                XDAS_Int32 *puiSadMVinfo;
//                if (dynamicparams.sliceSize <= 0)
                if (params.sliceMode == 0)
                   puiSadMVinfo = (XDAS_Int32*)outobj.bufs[1];
                else
                   puiSadMVinfo = (XDAS_Int32*)outobj.bufs[2];
                if (params.entropyMode || !(params.encQuality))
                   puiSadMVinfo = (XDAS_Int32*)outobj.bufs[1];

                fprintf(SadMvFilePtr, "Frame : %d\n", uiNumFrames);
                for(cntRow = 0; cntRow < (inobj.frameHeight >> 4); cntRow++)
                {
                    cnt = cntRow * 2 * (inobj.frameWidth >> 4);
                    for(cntCol = 0; cntCol < 2 * (inobj.frameWidth >> 4); cntCol+=2)
                    {
                        fprintf(SadMvFilePtr, "Mvx = %d, Mvy = %d, SAD = %d\n",
                    (short)(puiSadMVinfo[cnt + cntCol] & 0x0000FFFF), (puiSadMVinfo[cnt + cntCol] >> 16),
                                (*((XDAS_Int32 *)(puiSadMVinfo) + cnt + 1 + cntCol)));
                    }
                }
            }
//#endif //PASS_SAD_MV_APPL

#if 0
#ifdef SIMPLE_TWO_PASS
        if(dynamicparams.metaDataGenerateConsume == 1)
        {
            XDAS_UInt32 loopcnt;
            XDAS_Int32 *frameinfoPtr;
            frameinfoPtr = (XDAS_Int32 *)(outobj.bufs[1]);
            if (dynamicparams.sliceSize > 0 && !(params.entropyMode || !(params.encQuality)))
            {
                if(dynamicparams.mvSADoutFlag == 0)
                    frameinfoPtr = (XDAS_Int32 *)(outobj.bufs[2]);
                else
                    frameinfoPtr = (XDAS_Int32 *)(outobj.bufs[3]);
            }
            else
            {
                if(dynamicparams.mvSADoutFlag == 1)
                frameinfoPtr = (XDAS_Int32 *)(outobj.bufs[2]);
            }
            for(loopcnt=0;loopcnt<=7;loopcnt++)
                printf("1st Pass Frameinfo Parameter [%d] value is %d\n",loopcnt,*(frameinfoPtr+loopcnt));
        }
#endif //SIMPLE_TWO_PASS
#endif

#ifdef MB_LOOP_PROFILE
            /* Write the profile values copied from DTCM during the encode call
             * to file
             */
            fprintf(profFilePtr, "Frame : %d\n", uiNumFrames);
            for(loopcnt = 1; loopcnt <= profArr[0]; loopcnt++)
            {
               fprintf(profFilePtr, "Cycles %d\n", profArr[loopcnt]);
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
#ifdef LOW_LATENCY_FEATURE
            /* In slice mode, encoded stream is written in callback function */
            if(bWriteEncodedData && outargs.videncOutArgs.bytesGenerated &&
                (params.outputDataMode == IH264VENC_TI_ENTIREFRAME))
#else  //LOW_LATENCY_FEATURE
            if(bWriteEncodedData && outargs.videncOutArgs.bytesGenerated)
#endif //LOW_LATENCY_FEATURE
            {
#ifdef DEBUG_ENABLE
                printf("CODEC_DEBUG_ENABLE: Writing encoded frame to file\n");
#endif                
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
            if(bWriteReconData && outargs.videncOutArgs.reconBufs.numBufs)
            {
                XDAS_UInt8 *pubInBufY;
                XDAS_UInt8 *pubInBufUV;
                XDAS_UInt32 uiRecPitch = (XDAS_UInt32) outargs.videncOutArgs.reconBufs.framePitch;
                XDAS_UInt32 dispHeight;

                pubInBufY = (XDAS_UInt8 *)((unsigned int)outargs.videncOutArgs.reconBufs.bufDesc[0].buf);// - 32 - (32 * uiRecPitch));
                pubInBufUV = (XDAS_UInt8 *)((unsigned int)outargs.videncOutArgs.reconBufs.bufDesc[1].buf);// - 32 - (16 * uiRecPitch));

                /* The reconstructed frame in the encoder is padded format and
                 * the Chroma component is in interleaved format. This is
                 * converted by de-interleaving chroma components.
                 */
	             dispHeight = uiExtHeight;
	             if(uiExtHeight == 1088)
	             {
	                 dispHeight = uiExtHeight - 8;
	             }


                if(params.videncParams.inputContentType == 0) // Progressive
                {
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
                        dispHeight,
                        pfOutYUVFile
                    );
                    printf("Done\n");
                }
                else    // Interlaced Input
                {
                    GetReconFrame (
                        (pubYRecon + uiExtWidth * (uiNumFrames & 0x01)),
                        (pubURecon + (uiExtWidth >> 1) * (uiNumFrames & 0x01)),
                        (pubVRecon + (uiExtWidth >> 1) * (uiNumFrames & 0x01)),
                        pubInBufY,
                        pubInBufUV,
                        uiExtWidth,
                        (dispHeight >> 1),
                        uiRecPitch,
                        1
                );
                    if(uiNumFrames & 0x01)
                    {
                        printf("Writing Reconstructed Frame - ");
                        WriteReconOut(
                            pubYRecon,
                            pubURecon,
                            pubVRecon,
                            uiExtWidth,
                            dispHeight,
                            pfOutYUVFile
                        );
                        printf("Done\n");
                    }
                }
            }

#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
            printf("Profile: %d %d %d\n", profileSrt, profile968, profileEd);
            fprintf(pfProfFile, "Profile: %8d %8d %8d\n",
                    profileSrt, profile968, profileEd);
#endif/* ENABLE_PROFILE_AT_FRM_LVL_ON_926 */
            uiNumFrames++;
        }//0 - uiNumFramesTobeEncoded

        //CMEM_free(outargs.puiSadMVinfo, &memParams);
        /*--------------------------------------------------------------------*/
        /*             FREE H.264 ENCODER INPUT/OUTPUT BUFFERS                */
        /*--------------------------------------------------------------------*/
FREE_ENCODER_IO_BUFFERS:
        if(params.videncParams.inputContentType == 1) // Interlaced content
        {
            /* Reverting the input buffer pointer offset to avoid CMEM_free error */
            if(!((uiNumFrames & 01) || iStatus))
            {
                /* Process call corresponds to Odd field */
                inobj.bufDesc[0].buf -= (dynamicparams.videncDynamicParams.captureWidth >> 1);
                inobj.bufDesc[1].buf -= (dynamicparams.videncDynamicParams.captureWidth >> 1);

            }
        }
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
        printf("CODEC_DEBUG_ENABLE:   Total number of Frames          = %d\n",
            (XDAS_UInt32)uiNumFrames);fflush(stdout);
        printf("CODEC_DEBUG_ENABLE:   Encoded: %8d, Skipped: %8d\n",
            (XDAS_UInt32)uiNumFrames - iSkipCnt, iSkipCnt);fflush(stdout);
        printf("CODEC_DEBUG_ENABLE:   Bit Rate at 30 frames/Sec       = %d Kbps\n",(
            XDAS_UInt32)(((uiNumBytesWritten*8*30)/uiNumFrames)/1000));fflush(stdout);
        printf("CODEC_DEBUG_ENABLE:   Width and Height                = %d, %d \n",
            dynamicparams.videncDynamicParams.inputWidth,
            dynamicparams.videncDynamicParams.inputHeight);fflush(stdout);
//	    printf ("INPUT YUV :%s\n",bInputFile);	
#ifdef PROFILE_ONLINUX
        printf ("CODEC_DEBUG_ENABLE: ARM926 Average cycles %d \n", (total_time_p/uiNumFrames));
        printf ("CODEC_DEBUG_ENABLE: ARM926 Maximum cycles %d \n", time_max);
#endif
#ifdef PROFILE_ONLINUX_ARM968
		printf("CODEC_DEBUG_ENABLE: ARM968 AVG FRAME cycles:%d\n",total_time_arm968/uiNumFrames);			
		printf("CODEC_DEBUG_ENABLE: ARM968 MAX FRAME cycles:%d\n",max_time_arm968);			
#endif		
        printf (" --------------    END   --------------------\n");fflush(stdout);

        /*--------------------------------------------------------------------*/
        /*                 FREE Frame INPUT & RECON BUFFERS                   */
        /*--------------------------------------------------------------------*/
        H264VENC_control(handle, XDM_RESET, &dynamicparams/*NULL*/, &status/*NULL*/);

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
#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle),
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
        printf("CODEC_DEBUG_ENABLE: Free Resource Failed \n");
        return -1;
    }
#endif		
        if(handle)
		{	
			H264VENC_delete(handle);
			handle = NULL;
		}

    }/* End of 'config file list' while() loop */

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
#if 0	 
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(handle),
                                        &H264VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */)) {
        printf("CODEC_DEBUG_ENABLE: Free Resource Failed \n");
        return -1;
    }
#endif	
#endif


        /*--------------------------------------------------------------------*/
        /*                             DELETE ENCODER INSTANCE                */
        /*--------------------------------------------------------------------*/

FREE_ENCODER_OBJECT:
        if(handle)
		{
			H264VENC_delete(handle);
            handle = NULL;
		}

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
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
    /* Close Profile Log file */
    fclose(pfProfFile);
#endif /* ENABLE_PROFILE_AT_FRM_LVL_ON_926 */

#ifdef _PROFILE
    fclose(profFilePtr);
#endif //_PROFILE
#ifdef PASS_SAD_MV_APPL
    fclose(SadMvFilePtr);
#endif //PASS_SAD_MV_APPL
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
#if 1
    for( i = 0; i < H264EncStatus.videncStatus.bufInfo.minNumInBufs; i++)
    {
        /* Assign size for the current buffer */
        ptH264EncInpBufDesc->bufDesc[i].bufSize =
            H264EncStatus.videncStatus.bufInfo.minInBufSize[i];

        /* Allocate memory for buffer pointer */
        ptH264EncInpBufDesc->bufDesc[i].buf =
            (XDAS_Int8 *) CMEM_alloc(ptH264EncInpBufDesc->bufDesc[i].bufSize *
                                sizeof(xdc_Char),&memParams);

       printf("CODEC_DEBUG_ENABLE: Size of I/P buffer:%d\n",ptH264EncInpBufDesc->bufDesc[i].bufSize);

        if(ptH264EncInpBufDesc->bufDesc[i].buf == NULL)
        {
            return (-1); /* Memory not allocated, return failure */
        }
    }
#else
        ptH264EncInpBufDesc->bufDesc[0].bufSize =
            H264EncStatus.videncStatus.bufInfo.minInBufSize[0];
        ptH264EncInpBufDesc->bufDesc[1].bufSize =
            H264EncStatus.videncStatus.bufInfo.minInBufSize[1];

        if(gframe_count == 0)
        {
           ptH264EncInpBufDesc->bufDesc[0].buf = gORG_Y_1;
           ptH264EncInpBufDesc->bufDesc[1].buf = gORG_C_1;
        }

        if(gframe_count == 1)
        {
           ptH264EncInpBufDesc->bufDesc[0].buf = gORG_Y_2;
           ptH264EncInpBufDesc->bufDesc[1].buf = gORG_C_2;
        }

        gframe_count++;
#endif
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
                              sizeof(xdc_Char *));
    if(ptH264EncOutBufDesc->bufs == NULL)
    {
        return (-1); /* Memory not allocated, return failure */
    }
#if 1
    for( i = 0; i < ptH264EncOutBufDesc->numBufs; i++)
    {
        /* Assign size for the current buffer */
        ptH264EncOutBufDesc->bufSizes[i] =
            H264EncStatus.videncStatus.bufInfo.minOutBufSize[i];

        /* Allocate memory for buffers */
        ptH264EncOutBufDesc->bufs[i] =
            (XDAS_Int8 *) CMEM_alloc(ptH264EncOutBufDesc->bufSizes[i] *
                                 sizeof(xdc_Char), &memParams);
        printf("CODEC_DEBUG_ENABLE: Output stream buffer size:%d\n",ptH264EncOutBufDesc->bufSizes[i]);

        if(ptH264EncOutBufDesc->bufs[i] == NULL)
        {
            return (-1); /* Memory not allocated, return failure */
        }
    }
#else
        ptH264EncOutBufDesc->bufSizes[0] =
            H264EncStatus.videncStatus.bufInfo.minOutBufSize[0];

        ptH264EncOutBufDesc->bufSizes[1] =
            H264EncStatus.videncStatus.bufInfo.minOutBufSize[1];


        ptH264EncOutBufDesc->bufs[0] =
#endif

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
    /* uiRecWidth = uiPictWidth + (PAD_Y_HORIZ << 1); */
    /* pubSrc += (PAD_Y_PROG_VERT * uiRecWidth) + PAD_Y_HORIZ; */
    for(j = 0; j < uiPictHeight; j++)
    {
        pubDstY = pubYFrameData + ((j << uiContentType) * uiPictWidth);
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
        pubDstU = pubUFrameData + ((j << uiContentType) * uiPictWidth);
        pubDstV = pubVFrameData + ((j << uiContentType) * uiPictWidth);
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
    xdc_Char *refData;
    retVal = XDM_EOK;
    /*------------------------------------------------------------------------*/
    /*                        WRITE THE BITSTREAM                             */
    /*------------------------------------------------------------------------*/
#ifdef ENABLE_CACHE
    MEMUTILS_cacheInv(outArgs.videncOutArgs.encodedBuf.buf,
        outArgs.videncOutArgs.bytesGenerated);
#endif// ENABLE_CACHE
    if(iMode)
    {
        refData = (xdc_Char*)malloc(outArgs.videncOutArgs.bytesGenerated);
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
#ifdef LOW_LATENCY_FEATURE
        if(gSliceFormat == IH264VENC_TI_NALSTREAM)
        {
            XDAS_UInt32 startCodePattern = 0x01000000;
            fwrite(&startCodePattern, 1, 4, pfOutBitStreamFile);
        }
#endif //LOW_LATENCY_FEATURE
        fwrite(outArgs.videncOutArgs.encodedBuf.buf, sizeof(xdc_Char),
               outArgs.videncOutArgs.bytesGenerated, pfOutBitStreamFile);
        fflush(pfOutBitStreamFile);
    }

    return(retVal);
}/* WriteDataOut */

#ifdef LOW_LATENCY_FEATURE
/*===========================================================================*/
/**
*@func   getEncodedSliceProvideSpace
*
*@brief  Callback module for low latency inetrface. Codec calls this module to
*        provide encoded slice and get memory space for future encoded stream
*
*@param  IH264VENC_TI_DataSyncHandle
*        handle to DataSync provided by App to codec at the time of instance
*         creation
*
*        IH264VENC_TI_DataSyncDesc
*        Descriptor carrying information on pointer to number of encoded slice,
*        pointer to bitstream,  slice sizes
*@return XDAS_Int32
*        Status
*
*@note
*/
/*===========================================================================*/
XDAS_Int32 getEncodedSliceProvideSpace(
                                       IH264VENC_TI_DataSyncHandle dataSyncHandle,
                                       IH264VENC_TI_DataSyncDesc *dataSyncDesc)
{
    XDAS_UInt8 i, numBlocks;
    FILE *pfOutBitStreamFile = gFpOutBitStream;
    XDAS_UInt32 startCodePattern = 0x01000000;
    numBlocks = dataSyncDesc->numBlocks;
    for (i = 0; i < numBlocks; i++)
    {
        if(gSliceFormat == IH264VENC_TI_NALSTREAM)
        {
            fwrite(&startCodePattern, 1, 4, pfOutBitStreamFile);
        }
        fwrite(dataSyncDesc->baseAddr[i], 1,
            dataSyncDesc->blockSizes[i], pfOutBitStreamFile);
#ifdef ENABLE_CACHE
        MEMUTILS_cacheWbInv(dataSyncDesc->baseAddr[i],
            dataSyncDesc->blockSizes[i]);
#endif
    }
    dataSyncDesc->numBlocks = 1;
    dataSyncDesc->baseAddr[0]   = (XDAS_Int32 *)gOutObj->bufs[0];
    dataSyncDesc->blockSizes[0] = gOutObj->bufSizes[0];
    return(XDM_EOK);
}
#endif //LOW_LATENCY_FEATURE
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
xdc_Char *GetConfigFileContent (FILE *fname)
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
XDAS_Int32 ParameterNameToMapIndex (xdc_Char *s)
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
XDAS_Int32 ParseContent (xdc_Char *buf, XDAS_Int32 bufsize)
{
    xdc_Char *items[MAX_ITEMS_TO_PARSE];
    XDAS_Int32 MapIdx;
    XDAS_Int32 item = 0;
    XDAS_Int32 InString = 0, InItem = 0;
    xdc_Char *p = buf;
    xdc_Char *bufend = &buf[bufsize];
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
            strcpy((xdc_Char *)sTokenMap[MapIdx].place, items[i+2]);
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
    xdc_Char *FileBuffer = NULL ;
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


/*===========================================================================*/
/*!
*@func   printErrorMsg
*
*@brief  This print the encoder error code string for the input error code
*
*@param  errorCode
*        input H264 encoder error code
*
*@return void
*
*@note
*/
/*===========================================================================*/
void printErrorMsg(XDAS_Int32 errorCode)
{
    if(0 == errorCode)
        return;

    printf("\n");
        printf("CODEC_DEBUG_ENABLE:");
    if(XDM_ISFATALERROR(errorCode))
    {
        printf("\tFatal Error");
    }

    if(XDM_ISUNSUPPORTEDPARAM(errorCode))
    {
        printf("\tUnsupported Param Error");
    }

    if(XDM_ISUNSUPPORTEDINPUT(errorCode))
    {
        printf("\tUnsupported Input Error");
    }
    printf(":\t");

    switch(errorCode)
    {
        case IH264VENC_ERR_MAXWIDTH :
            printf("IH264VENC_ERR_MAXWIDTH\n");
            break;

        case IH264VENC_ERR_MAXHEIGHT :
            printf("IH264VENC_ERR_MAXHEIGHT\n");
            break;

        case IH264VENC_ERR_ENCODINGPRESET :
            printf("IH264VENC_ERR_ENCODINGPRESET\n");
            break;

        case IH264VENC_ERR_RATECONTROLPRESET :
            printf("IH264VENC_ERR_RATECONTROLPRESET\n");
            break;

        case IH264VENC_ERR_MAXFRAMERATE :
            printf("IH264VENC_ERR_MAXFRAMERATE\n");
            break;

        case IH264VENC_ERR_MAXBITRATE :
            printf("IH264VENC_ERR_MAXBITRATE\n");
            break;

        case IH264VENC_ERR_DATAENDIANNESS :
            printf("IH264VENC_ERR_DATAENDIANNESS\n");
            break;

        case IH264VENC_ERR_INPUTCHROMAFORMAT :
            printf("IH264VENC_ERR_INPUTCHROMAFORMAT\n");
            break;

        case IH264VENC_ERR_INPUTCONTENTTYPE :
            printf("IH264VENC_ERR_INPUTCONTENTTYPE\n");
            break;

        case IH264VENC_ERR_RECONCHROMAFORMAT :
            printf("IH264VENC_ERR_RECONCHROMAFORMAT\n");
            break;

        case IH264VENC_ERR_INPUTWIDTH :
            printf("IH264VENC_ERR_INPUTWIDTH\n");
            break;

        case IH264VENC_ERR_INPUTHEIGHT :
            printf("IH264VENC_ERR_INPUTHEIGHT\n");
            break;

        case IH264VENC_ERR_MAX_MBS_IN_FRM_LIMIT_EXCEED :
            printf("IH264VENC_ERR_MAX_MBS_IN_FRM_LIMIT_EXCEED\n");
            break;

        case IH264VENC_ERR_TARGETFRAMERATE :
            printf("IH264VENC_ERR_TARGETFRAMERATE\n");
            break;

        case IH264VENC_ERR_TARGETBITRATE :
            printf("IH264VENC_ERR_TARGETBITRATE\n");
            break;

        case IH264VENC_ERR_PROFILEIDC :
            printf("IH264VENC_ERR_PROFILEIDC\n");
            break;

        case IH264VENC_ERR_LEVELIDC :
            printf("IH264VENC_ERR_LEVELIDC\n");
            break;

        case IH264VENC_ERR_ENTROPYMODE_IN_BP :
            printf("IH264VENC_ERR_ENTROPYMODE_IN_BP\n");
            break;

        case IH264VENC_ERR_TRANSFORM8X8FLAGINTRA_IN_BP_MP :
            printf("IH264VENC_ERR_TRANSFORM8X8FLAGINTRA_IN_BP_MP\n");
            break;

        case IH264VENC_ERR_TRANSFORM8X8FLAGINTER_IN_BP_MP :
            printf("IH264VENC_ERR_TRANSFORM8X8FLAGINTER_IN_BP_MP\n");
            break;

        case IH264VENC_ERR_SEQSCALINGFLAG_IN_BP_MP :
            printf("IH264VENC_ERR_SEQSCALINGFLAG_IN_BP_MP\n");
            break;

        case IH264VENC_ERR_ASPECTRATIOX :
            printf("IH264VENC_ERR_ASPECTRATIOX\n");
            break;

        case IH264VENC_ERR_ASPECTRATIOY :
            printf("IH264VENC_ERR_ASPECTRATIOY\n");
            break;

        case IH264VENC_ERR_PIXELRANGE :
            printf("IH264VENC_ERR_PIXELRANGE\n");
            break;

        case IH264VENC_ERR_TIMESCALE :
            printf("IH264VENC_ERR_TIMESCALE\n");
            break;

        case IH264VENC_ERR_NUMUNITSINTICKS :
            printf("IH264VENC_ERR_NUMUNITSINTICKS\n");
            break;

        case IH264VENC_ERR_ENABLEVUIPARAMS :
            printf("IH264VENC_ERR_ENABLEVUIPARAMS\n");
            break;

        case IH264VENC_ERR_RESETHDVICPEVERYFRAME :
            printf("IH264VENC_ERR_RESETHDVICPEVERYFRAME\n");
            break;

        case IH264VENC_ERR_MEALGO :
            printf("IH264VENC_ERR_MEALGO\n");
            break;

        case IH264VENC_ERR_UNRESTRICTEDMV :
            printf("IH264VENC_ERR_UNRESTRICTEDMV\n");
            break;

        case IH264VENC_ERR_ENCQUALITY :
            printf("IH264VENC_ERR_ENCQUALITY\n");
            break;

        case IH264VENC_ERR_ENABLEARM926TCM :
            printf("IH264VENC_ERR_ENABLEARM926TCM\n");
            break;

        case IH264VENC_ERR_ENABLEDDRBUFF :
            printf("IH264VENC_ERR_ENABLEDDRBUFF\n");
            break;

        case IH264VENC_ERR_LEVEL_NOT_FOUND :
            printf("IH264VENC_ERR_LEVEL_NOT_FOUND\n");
            break;

        case IH264VENC_ERR_REFFRAMERATE_MISMATCH :
            printf("IH264VENC_ERR_REFFRAMERATE_MISMATCH\n");
            break;

        case IH264VENC_ERR_INTRAFRAMEINTERVAL :
            printf("IH264VENC_ERR_INTRAFRAMEINTERVAL\n");
            break;

        case IH264VENC_ERR_GENERATEHEADER :
            printf("IH264VENC_ERR_GENERATEHEADER\n");
            break;

        case IH264VENC_ERR_FORCEFRAME :
            printf("IH264VENC_ERR_FORCEFRAME\n");
            break;

        case IH264VENC_ERR_RCALGO :
            printf("IH264VENC_ERR_RCALGO\n");
            break;

        case IH264VENC_ERR_INTRAFRAMEQP :
            printf("IH264VENC_ERR_INTRAFRAMEQP\n");
            break;

        case IH264VENC_ERR_INTERPFRAMEQP :
            printf("IH264VENC_ERR_INTERPFRAMEQP\n");
            break;

        case IH264VENC_ERR_RCQMAX :
            printf("IH264VENC_ERR_RCQMAX\n");
            break;

        case IH264VENC_ERR_RCQMIN :
            printf("IH264VENC_ERR_RCQMIN\n");
            break;

        case IH264VENC_ERR_RCIQMAX :
            printf("IH264VENC_ERR_RCIQMAX\n");
            break;

        case IH264VENC_ERR_RCIQMIN :
            printf("IH264VENC_ERR_RCIQMIN\n");
            break;

        case IH264VENC_ERR_INITQ :
            printf("IH264VENC_ERR_INITQ\n");
            break;

        case IH264VENC_ERR_MAXDELAY :
            printf("IH264VENC_ERR_MAXDELAY\n");
            break;

        case IH264VENC_ERR_LFDISABLEIDC :
            printf("IH264VENC_ERR_LFDISABLEIDC\n");
            break;

        case IH264VENC_ERR_ENABLEBUFSEI :
            printf("IH264VENC_ERR_ENABLEBUFSEI\n");
            break;

        case IH264VENC_ERR_ENABLEPICTIMSEI :
            printf("IH264VENC_ERR_ENABLEPICTIMSEI\n");
            break;

        case IH264VENC_ERR_SLICESIZE :
            printf("IH264VENC_ERR_SLICESIZE\n");
            break;

        case IH264VENC_ERR_INTRASLICENUM :
            printf("IH264VENC_ERR_INTRASLICENUM\n");
            break;

        case IH264VENC_ERR_AIRRATE :
            printf("IH264VENC_ERR_AIRRATE\n");
            break;

        case IH264VENC_ERR_MEMULTIPART :
            printf("IH264VENC_ERR_MEMULTIPART\n");
            break;

        case IH264VENC_ERR_INTRATHRQF :
            printf("IH264VENC_ERR_INTRATHRQF\n");
            break;

        case IH264VENC_ERR_PERCEPTUALRC :
            printf("IH264VENC_ERR_PERCEPTUALRC\n");
            break;

        case IH264VENC_ERR_IDRFRAMEINTERVAL :
            printf("IH264VENC_ERR_IDRFRAMEINTERVAL\n");
            break;

        case IH264VENC_ERR_ENABLEROI :
            printf("IH264VENC_ERR_ENABLEROI\n");
            break;

        case IH264VENC_ERR_MAXBITRATE_CVBR :
            printf("IH264VENC_ERR_MAXBITRATE_CVBR\n");
            break;

        case IH264VENC_ERR_CVBR_SENSITIVITY :
            printf("IH264VENC_ERR_CVBR_SENSITIVITY\n");
            break;

        case IH264VENC_ERR_CVBR_MAX_CMPX_INT :
            printf("IH264VENC_ERR_CVBR_MAX_CMPX_INT\n");
            break;          

        case IH264VENC_ERR_MVSADOUTFLAG :
            printf("IH264VENC_ERR_MVSADOUTFLAG\n");
            break;

        case IH264VENC_ERR_MAXINTERFRAMEINTERVAL :
            printf("IH264VENC_ERR_MAXINTERFRAMEINTERVAL\n");
            break;

        case IH264VENC_ERR_CAPTUREWIDTH :
            printf("IH264VENC_ERR_CAPTUREWIDTH\n");
            break;

        case IH264VENC_ERR_INTERFRAMEINTERVAL :
            printf("IH264VENC_ERR_INTERFRAMEINTERVAL\n");
            break;

        case IH264VENC_ERR_MBDATAFLAG :
            printf("IH264VENC_ERR_MBDATAFLAG\n");
            break;

        case IH264VENC_ERR_IVIDENC1_DYNAMICPARAMS_SIZE_IN_CORRECT :
            printf("IH264VENC_ERR_IVIDENC1_DYNAMICPARAMS_SIZE_IN_CORRECT\n");
            break;

        case IH264VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL :
            printf("IH264VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL\n");
            break;

        case IH264VENC_ERR_IVIDENC1_INARGS_SIZE :
            printf("IH264VENC_ERR_IVIDENC1_INARGS_SIZE\n");
            break;

        case IH264VENC_ERR_IVIDENC1_OUTARGS_SIZE :
            printf("IH264VENC_ERR_IVIDENC1_OUTARGS_SIZE\n");
            break;

        case IH264VENC_ERR_IVIDENC1_INARGS_INPUTID :
            printf("IH264VENC_ERR_IVIDENC1_INARGS_INPUTID\n");
            break;

        case IH264VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG :
            printf("IH264VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG\n");
            break;

        case IH264VENC_ERR_IVIDENC1_INBUFS :
            printf("IH264VENC_ERR_IVIDENC1_INBUFS\n");
            break;

        case IH264VENC_ERR_IVIDENC1_INBUFS_BUFDESC :
            printf("IH264VENC_ERR_IVIDENC1_INBUFS_BUFDESC\n");
            break;

        case IH264VENC_ERR_IVIDENC1_OUTBUFS :
            printf("IH264VENC_ERR_IVIDENC1_OUTBUFS\n");
            break;

        case IH264VENC_ERR_IVIDENC1_OUTBUFS_NULL :
            printf("IH264VENC_ERR_IVIDENC1_OUTBUFS_NULL\n");
            break;

        case IH264VENC_ERR_INTERLACE_IN_BP :
            printf("IH264VENC_ERR_INTERLACE_IN_BP\n");
            break;

        case IH264VENC_ERR_RESERVED :
            printf("IH264VENC_ERR_RESERVED\n");
            break;

        case IH264VENC_ERR_INSERTUSERDATA :
            printf("IH264VENC_ERR_INSERTUSERDATA\n");
            break;

        case IH264VENC_ERR_ROIPARAM :
            printf("IH264VENC_ERR_ROIPARAM\n");
            break;

        case IH264VENC_ERR_LENGTHUSERDATA :
            printf("IH264VENC_ERR_LENGTHUSERDATA\n");
            break;

        case IH264VENC_ERR_PROCESS_CALL :
            printf("IH264VENC_ERR_PROCESS_CALL\n");
            break;

        case IH264VENC_ERR_HANDLE_NULL :
            printf("IH264VENC_ERR_HANDLE_NULL\n");
            break;

        case IH264VENC_ERR_INCORRECT_HANDLE :
            printf("IH264VENC_ERR_INCORRECT_HANDLE\n");
            break;

        case IH264VENC_ERR_MEMTAB_NULL :
            printf("IH264VENC_ERR_MEMTAB_NULL\n");
            break;

        case IH264VENC_ERR_IVIDENC1_INITPARAMS_SIZE :
            printf("IH264VENC_ERR_IVIDENC1_INITPARAMS_SIZE\n");
            break;

        case IH264VENC_ERR_MEMTABS_BASE_NULL :
            printf("IH264VENC_ERR_MEMTABS_BASE_NULL\n");
            break;

        case IH264VENC_ERR_MEMTABS_BASE_NOT_ALIGNED :
            printf("IH264VENC_ERR_MEMTABS_BASE_NOT_ALIGNED\n");
            break;

        case IH264VENC_ERR_MEMTABS_SIZE :
            printf("IH264VENC_ERR_MEMTABS_SIZE\n");
            break;

        case IH264VENC_ERR_MEMTABS_ATTRS :
            printf("IH264VENC_ERR_MEMTABS_ATTRS\n");
            break;

        case IH264VENC_ERR_MEMTABS_SPACE :
            printf("IH264VENC_ERR_MEMTABS_SPACE\n");
            break;

        case IH264VENC_ERR_MEMTABS_OVERLAP :
            printf("IH264VENC_ERR_MEMTABS_OVERLAP\n");
            break;

        case IH264VENC_ERR_CODEC_INACTIVE :
            printf("IH264VENC_ERR_CODEC_INACTIVE\n");
            break;

        case IH264VENC_WARN_LEVELIDC :
            printf("IH264VENC_WARN_LEVELIDC\n");
            break;

        case IH264VENC_WARN_RATECONTROLPRESET :
            printf("IH264VENC_WARN_RATECONTROLPRESET\n");
            break;

        case IH264VENC_WARN_H241_SLICE_SIZE_EXCEEDED :
            printf("IH264VENC_WARN_H241_SLICE_SIZE_EXCEEDED\n");
            break;

        case IH264VENC_ERR_STATUS_BUF :
            printf("IH264VENC_ERR_STATUS_BUF\n");
            break;

        case IH264VENC_ERR_METADATAFLAG :
            printf("IH264VENC_ERR_METADATAFLAG\n");
            break;

        default:
            printf("Unknown Error code\n");
    }
}


/*!
*! Revision History
*! ****************
*! 25-11-2009 Manisha Agrawal: Added support for low latency interface
*! 17-08-2007 Sunil Koteyar: Move some funtionality from subPictConv.c and
*!            renamed as GetReconFrame & DoChromaInterleave. subPictConv.c
*!            is defunct now.
*! 09-08-2007 Sunil Koteyar: Code changes related to Coding Guidelines
*! 18-01-2006 Anirban Basu: Created.
*/
