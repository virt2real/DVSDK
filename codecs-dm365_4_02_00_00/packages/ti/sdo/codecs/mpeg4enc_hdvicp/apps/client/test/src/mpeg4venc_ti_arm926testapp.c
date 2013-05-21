/** ===========================================================================
* @file mpeg4venc_ti_arm926testapp.c
*
* @path $\\(PROJDIR)\\..\\Client\\Test\\Src\\
*
* @desc This is main application file calling the MPEG4 Encoder application.
*       This file has all functionality to read the input data, set up the
*       encoder intialization params, encode the stream, write out the data and
*       close down the application.
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/
/*------compilation control switches ----------------------------------------*/
/* RECON_DUMP macro is to enable/disable dumping of reconstructed frame into
 * recon file mentioned in config file
 */
//#define RECON_DUMP
//#define ENABLE_CORRUPTION_TESTS
//#define PRINT_OUT_ARGS
#ifdef PRINT_OUT_BUFS
#define PRINT_OUT_BUFS_MPEG4(outbufdesc)	{\
	XDAS_Int8 i;\
	printf("\nPrinting OutBufs\n");\
	printf("outbufdesc.numBufs = %d\n",outbufdesc.numBufs);\
	for(i = 0;i < outbufdesc.numBufs;i++)\
	{\
		printf("outbufdesc.bufs[%d] = %x\n",i,outbufdesc.bufs[i]);\
		printf("outbufdesc.bufSizes[%d] = %d\n",i,outbufdesc.bufSizes[i]);\
	}\
}
#else
#define PRINT_OUT_BUFS_MPEG4(outbufdesc)
#endif

#ifdef PRINT_OUT_ARGS
#define PRINT_OUT_ARGS_MPEG4(outargs)	{\
    printf("\n<======== Video Encoder OutArgs Debug Start ==========>\n");\
    printf("Extended Error     : %d\n", (int) outargs.videncOutArgs.extendedError);\
    printf("Bytes Generated    : %d\n", (int) outargs.videncOutArgs.bytesGenerated);\
    printf("Encoded Frame Type : %d\n", (int) outargs.videncOutArgs.encodedFrameType);\
    printf("Input Frame Skip   : %d\n", (int) outargs.videncOutArgs.inputFrameSkip);\
    printf("Output ID      : %d\n", (int) outargs.videncOutArgs.outputID);\
\
    /*XDM1_SingleBufDesc encodedBuf; */\
    printf("encodedBuf            :\n");\
	printf("\tbuf                   : %x\n", (unsigned int)outargs.videncOutArgs.encodedBuf.buf);\
	printf("\tbufSize               : %d\n", (int)outargs.videncOutArgs.encodedBuf.bufSize);\
	printf("\taccessMask            : %d\n", (int)outargs.videncOutArgs.encodedBuf.accessMask);\
\
\
    /*IVIDEO1_BufDesc reconBufs;*/\
    printf("reconBufs          :\n");\
    printf("\tNumBufs               : %d\n", (int)outargs.videncOutArgs.reconBufs.numBufs);\
    printf("\tframeWidth            : %d\n", (int)outargs.videncOutArgs.reconBufs.frameWidth);\
    printf("\tframeHeight           : %d\n", (int)outargs.videncOutArgs.reconBufs.frameHeight);\
    printf("\tframePitch            : %d\n", (int)outargs.videncOutArgs.reconBufs.framePitch);\
\
    {\
		int i;\
		/*The following loop is for XDM1_SingleBufDesc bufDesc[3];*/\
		for(i=0; i<3; i++)\
		{\
			printf("\tbufDesc[%d]             :\n", i);\
			printf("\tbuf                   : %x\n", (unsigned int)outargs.videncOutArgs.reconBufs.bufDesc[i].buf);\
			printf("\tbufSize               : %d\n", (int)outargs.videncOutArgs.reconBufs.bufDesc[i].bufSize);\
			printf("\taccessMask            : %d\n", (int)outargs.videncOutArgs.reconBufs.bufDesc[i].accessMask);\
\
\
		}\
	}\
\
    printf("\textendedError         : %d\n", (int)outargs.videncOutArgs.reconBufs.extendedError);\
    printf("\tframeType             : %d\n", (int)outargs.videncOutArgs.reconBufs.frameType);\
    printf("\ttopFieldFirstFlag     : %d\n", (int)outargs.videncOutArgs.reconBufs.topFieldFirstFlag);\
    printf("\trepeatFirstFieldFlag  : %d\n", (int)outargs.videncOutArgs.reconBufs.repeatFirstFieldFlag);\
    printf("\tframeStatus           : %d\n", (int)outargs.videncOutArgs.reconBufs.frameStatus);\
    printf("\trepeatFrame           : %d\n", (int)outargs.videncOutArgs.reconBufs.repeatFrame);\
    printf("\tcontentType           : %d\n", (int)outargs.videncOutArgs.reconBufs.contentType);\
    printf("\tchromaFormat          : %d\n", (int)outargs.videncOutArgs.reconBufs.chromaFormat);\
\
    printf("\n<======== Video Encoder OutArgs Debug End ============>\n");\
}
#else
#define PRINT_OUT_ARGS_MPEG4(outargs)
#endif

/******************************************************************************
*                               INCLUDE FILES
******************************************************************************/
/*----- system and platform files -------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
//#include <tistdtypes.h>
/*-------program files ------------------------------------------------------*/
#include "mpeg4venc_ti_formatconvt.h"
#include "mpeg4venc_ti_api.h"
#include "imp4venc.h"
#include "mpeg4venc_ti.h"
#include "hdvicp_framework.h"
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
#include <ti/sdo/utils/trace/gt.h>

#define MAX_WIDTH  1920
#define MAX_HEIGHT 1088
#define MAX_BITRATE	20000000

#ifdef DEVICE_ID_CHECK
/* Link modules used for DEVICE ID check */
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>
#endif

#ifdef ON_LINUX
#define PROFILE_ONLINUX
#endif

//#define TEST_GEN_HEADER

#ifdef PROFILE_ONLINUX
#include <sys/time.h>
extern int arm968_time;
float count_arm926;
float count_arm968;
#endif

#ifdef ON_LINUX
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#endif
//#include "idma_dm510_for_926_fc.h"
//#include "buffermanager.h"
//#include "hdvicp_framework.h"
#include "testapp_arm926intc.h"
/******************************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in this file
******************************************************************************/
/*--------data declarations -------------------------------------------------*/
/* This global variable is defined inside hdvicp_framework.c */
#ifndef ON_LINUX
extern volatile XDAS_UInt32 * poll_word;
#endif
/*--------function prototypes -----------------------------------------------*/

/******************************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
******************************************************************************/

/*--------data declarations -------------------------------------------------*/

/******************************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
******************************************************************************/
/*--------data declarations -------------------------------------------------*/
extern IRES_Fxns MPEG4VENC_TI_IRES;
//static GT_Mask someGTMask;

/*---------------------------------------------------------------------------*/
/*  Token Map array for inputs from testparams.cfg file.                     */
/*---------------------------------------------------------------------------*/
typedef struct _sTokenMapping
{
  XDAS_Int8 *tokenName;
  XDAS_Int8  bType;
  XDAS_Void *place;
}sTokenMapping;
#ifdef ON_LINUX
    CMEM_AllocParams memParams;
#endif
/*---------------------------------------------------------------------------*/
/* Maximum tokens that can be read from config file are assumed as 100       */
/* Can be changed based on need                                              */
/*---------------------------------------------------------------------------*/
static sTokenMapping sTokenMap[100];

/*---------------------------------------------------------------------------*/
/* temporary buffer to read the contents of config file.                     */
/* Presently maximum buffer size is assumed as 20000.                        */
/* Can be changed based on need                                              */
/*---------------------------------------------------------------------------*/
static XDAS_Int8 buf[20000];

/*---------------------------------------------------------------------------*/
/* Buffer pointers for reading YUV data from input file                      */
/*---------------------------------------------------------------------------*/
XDAS_UInt8 *pubInY;
XDAS_UInt8 *pubInU;
XDAS_UInt8 *pubInV;
FILE *pfRefBitStreamFile;  /* Pointer to the output BitStream File      */
/*--------function prototypes -----------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Function used to map the index number from sTokenMap[] for a              */
/* given parameter name..                                                    */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s);

/*---------------------------------------------------------------------------*/
/* Function used to read the configuration file content in a buffer and      */
/* returns the address of the buffer                                         */
/*---------------------------------------------------------------------------*/
static XDAS_Int8* GetConfigFileContent(FILE *fname);

/*---------------------------------------------------------------------------*/
/* Top level function used to read and parse the parameter file content      */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 readparamfile(FILE *fname);

/*---------------------------------------------------------------------------*/
/* Function used to parse the character array buf and writes global variable */
/* input.This is necessary to facilitate the addition of new parameters      */
/* through the sTokenMap[] mechanism.                                        */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 ParseContent(XDAS_Int8 *buf, XDAS_Int32 bufsize);

/*---------------------------------------------------------------------------*/
/* Function used for allocating buffers as required by the algorithm         */
/* for the input and output                                                  */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 AllocateMP4IOBuffers(MP4VENC_Status     MP4EncStatus,
                                       IVIDEO1_BufDescIn *ptMP4EncInpBufDesc,
                                       XDM_BufDesc       *ptMP4EncOutBufDesc);

/*---------------------------------------------------------------------------*/
/* Function used to free buffers as used by the algorithm for the input      */
/* and output                                                                */
/*---------------------------------------------------------------------------*/
static void FreeMP4IOBuffers(IVIDEO1_BufDescIn *ptMP4EncInpBufDesc,
                             XDM_BufDesc       *ptMP4EncOutBufDesc);

/*---------------------------------------------------------------------------*/
/*  Function used to write bit-stream into output file                       */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 WriteDataOut(XDM_BufDesc *tOutBufferDesc,
                               FILE        *pfOutBitStreamFile,
                               MP4VENC_OutArgs *outargs,
                               XDAS_Int8  testCompliance);

/*---------------------------------------------------------------------------*/
/*  Function used to read input YUV data from file                           */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 ReadInputData(IVIDEO1_BufDescIn *tInpBufferDesc,
                                XDAS_UInt32        uiPicWidth,
                                 XDAS_UInt32       uiPicHeight,
								XDAS_UInt32 	   uiExtWidth,
								XDAS_UInt32        uiExtHeight,
                                 FILE             *pfInYUVFile);

#ifdef ENABLE_CORRUPTION_TESTS

/*---------------------------------------------------------------------------*/
/*  Function used to test the error robustness for process call's arguments  */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 proc_call_args_corruption_tests(MP4VENC_Handle     handle,
									  IVIDEO1_BufDescIn *inbufdesc ,
									  XDM_BufDesc       *outbufdesc,
									  MP4VENC_InArgs    *inargs,
									  MP4VENC_OutArgs   *outargs);



/*---------------------------------------------------------------------------*/
/*  Function used to test the error robustness for process call's arguments  */
/*---------------------------------------------------------------------------*/
#define	CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus) {\
		test_no++;\
		iErrorFlag =  MP4VENC_Encode(handle,\
									 &inbufdesc_local,\
									 &outbufdesc_local,\
									 &inargs_local,\
									 &outargs_local);\
		if(iErrorFlag == XDM_EFAIL)\
		{\
			/* printErrorMsg(outargs_local.videncOutArgs.extendedError);*/ \
			printf("Test no %2d: Passed\n",test_no);\
		}\
		else\
		{\
			globalStatus |= 1;\
			printf("Test no %2d: Failed\n",test_no);\
		}\
	}

#endif

#ifdef RECON_DUMP
/*---------------------------------------------------------------------------*/
/* Function used to write reconstructed YUV frame to file if RECON_DUMP      */
/* macro is enabled                                                          */
/*---------------------------------------------------------------------------*/
static XDAS_Int32 WriteReconOut (XDAS_UInt8* pubReconY,
                                 XDAS_UInt8* pubReconU,
                                 XDAS_UInt8* pubReconV,
                                 XDAS_Int32 uiWidth,
                                 XDAS_Int32 uiHeight,
                                 FILE *pfOutYUVFile);
#endif /* RECON_DUMP*/

/*--------MACROS ------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Maximum tokens to be parsed from config file are assumed to be 1000       */
/* can be changed based on need                                              */
/*---------------------------------------------------------------------------*/
#define MAX_ITEMS_TO_PARSE  1000

/*---------------------------------------------------------------------------*/
/* HDVICP framework used ARM 968 DTCM addess 0x02160000  to store poll word   */
/*---------------------------------------------------------------------------*/
//#define HDVICP_IPC_POLLWORD_DTCM 0x02160000
#define HDVICP_IPC_POLLWORD_DTCM 0x01F60000
/******************************************************************************
*       GLOBAL FUNCTION DEFINITIONS (DEFINED HERE / CALLED ELSEWHERE)
******************************************************************************/

/*===========================================================================
*@func  main()
*
*@brief This is the main Application code used to call the MP4 Encoder.
*
*       The alg_activate function has to be called by the system to restore
*       all the internal memory data to it's original location in the internal
*       memory from where they had been transferred to the external memory
*       location oh the alg_deactiavte call. This module should not be called
*       before the alg_deactiavte has been called.
*
*@param  none
*
*@return None
*
*@see    None
*
*@note   None
*===========================================================================
*/

#define _ENABLE_IRES_EDMA3

int main()
{
    MP4VENC_Handle  handle;  /* Handle to the Encoder instance      - XDAIS */
    IMP4HDVICPENC_Fxns fxns;      /* Function table for the MP4 Encoder  - XDAIS */
    MP4VENC_Params params;   /* Instance creation Parameter         - XDM   */
    MP4VENC_Status status;   /* Stores the status of process call   - XDM   */
    MP4VENC_InArgs inargs;   /* Input Parameter to the process call - XDM   */
    MP4VENC_OutArgs outargs; /* Ouput parameters from process call  - XDM   */
    MP4VENC_DynamicParams dynamicparams; /* Dynamic Parameter struct- XDM   */
    IVIDEO1_BufDescIn inbufdesc;/*Input Buffer description array    - XDM   */
    XDM_BufDesc outbufdesc;      /* Output Buffer description array - XDM   */
    XDAS_Int32 iErrorFlag;   /* Local Variables to Keep track of errors     */
    XDAS_UInt32 uiNumFrames;            /* Number of frames encoded         */
    XDAS_UInt32 uiNumFramesToBeEncoded; /* Number of frames to be encoded   */
    XDAS_UInt32 uiNumBytesWritten;      /* Number of encoded bytes written  */
    char   bInputFile[400];        /* Input file name                  */
    char   bEncOutFile[800];       /* Encoded output file name         */
    char   bReconOutFile[400];     /* Reconstructed decoded output file*/
    char   bConfigFile[400];       /* bConfigFile file name            */
    char   line[400];
    char   bWriteEncodedData;      /* Switch for Bitstream write out   */
    char   bMeInfoFile[400];       /* Me Info output file				*/
    XDAS_Int8   bWriteSADandMV;			/* Switch for ME Sad write out   */
    FILE *pfMeInfoFile          ;  /* Pointer to the Configuration File         */
    XDAS_UInt32 uiTokenCtr;             /* Token map counter                */
    FILE *pfConfigParamsFile;  /* Pointer to the Configuration File         */
    FILE *pfInputYUVFile;      /* Pointer to the Input Video YUV File       */
    FILE *pfOutBitStreamFile;  /* Pointer to the output BitStream File      */
    FILE *pfConfig          ;  /* Pointer to the Configuration File         */
    HDVICP_Obj hdvicpObj;      /* HDVICP framework handle                   */
    XDAS_UInt32 uiFrmSize;     /* Variable used to calculate frame size     */
	XDAS_Int32 testCompliance;
    XDAS_UInt32  countConfigSet;
	XDAS_Int32 retVal;
	XDAS_Int32 intTimer;
    XDAS_Int32 uiExtWidth;              /* Width with padding to 16         */
    XDAS_Int32 uiExtHeight;             /* Height with padding to 16        */
	XDAS_Int32 uiFrmPitch;              /* Line Pitch for the input frame   */
	IRES_Status iresStatus;
	XDAS_Int8 versionBuf[256];
	XDAS_Int32 uiIOBufferAllocDone = 0;

#ifdef ENABLE_CORRUPTION_TESTS
	XDAS_Int32 globalStatus = 0;
#endif

#ifdef DEVICE_ID_CHECK
	IRESMAN_AddrSpaceParams addrspaceConfigParams;
#endif

#ifdef PROFILE_ONLINUX
    XDAS_UInt32 time_before_process, time_after_process;
    struct timeval encoder_time, *encoder_timeptr;
    static unsigned int frame_count_p, total_time_p;

	count_arm926 = 0;
	count_arm968 = 0;
#endif
#ifdef RECON_DUMP
    /*----------------------------------------------------------------------*/
    /* Varibales used for reconstricted frame dumping when RECON_DUMP macro */
    /* is enabled.                                                          */
    /*----------------------------------------------------------------------*/
    XDAS_UInt8 *pubInBufY;
    XDAS_UInt8 *pubInBufUV;
    XDAS_Int8   bWriteReconData;        /* Switch for Recon write out       */
    XDAS_UInt8 *pubYRecon;
    XDAS_UInt8 *pubURecon;
    XDAS_UInt8 *pubVRecon;
    XDAS_Int32  uiSize;
    FILE *pfOutYUVFile;        /* Pointer to the output reconstructed File  */
#endif /*RECON_DUMP*/
#ifdef ON_LINUX
	/* Allocation params */
	memParams.type=CMEM_POOL;
	memParams.flags=CMEM_CACHED;
	memParams.alignment=256;
    /* Initialization and allocation */
    CMEM_init();
#endif
    /*----------------------------------------------------------------------*/
    /* Setting the sizes of Extended Objects                                */
    /*----------------------------------------------------------------------*/
    params.videncParams.size               = sizeof(IMP4HDVICPENC_Params);
    status.videncStatus.size               = sizeof(IMP4HDVICPENC_Status);
    dynamicparams.videncDynamicParams.size = sizeof(IMP4HDVICPENC_DynamicParams);
    inargs.videncInArgs.size               = sizeof(IMP4HDVICPENC_InArgs);
    outargs.videncOutArgs.size             = sizeof(IMP4HDVICPENC_OutArgs);
    status.videncStatus.data.buf 		   = versionBuf;
	status.videncStatus.data.bufSize       = sizeof(versionBuf);

    /*----------------------------------------------------------------------*/
    /* Intialize function table pointer to the function table implementation*/
    /* for MPEG4 Encoder by TI                                              */
    /*----------------------------------------------------------------------*/
    fxns   = MPEG4VENC_TI_IMPEG4VENC;

    /*----------------------------------------------------------------------*/
    /* initialize parameters with default vaules provided by codec          */
    /*----------------------------------------------------------------------*/
    params = MP4VENC_PARAMS;

    /*----------------------------------------------------------------------*/
    /* Call fucntions to enable I and D caches                              */
	/* And to initialize MMU table. This sequence of functiona calls should */
    /* for codec to function normall                                        */
    /*----------------------------------------------------------------------*/

	/*ARM926_ENABLE_CACHE macro enable/disables ARM926 I-cache and D-cache
	 */
#ifdef ARM926_ENABLE_CACHE
    ARM926_Set_MMU_Base();
    ARM926_Set_Domains();
    ARM926_Enable_MMU();
    ARM926_Icache_Enable();
    ARM926_Flush_Icache();
    ARM926_Cache_Set_RoundRobin();
    ARM926_Dcache_Enable();
    ARM926_CleanFlush_Dcache();
#endif /*ARM926_ENABLE_CACHE*/

    /* Interrupt enable related function calls please refer to User
     * guide for a detailed description of these functions and the
     * DM360_IPC_INTC_ENABLE macro usage
     */
#ifdef DM360_IPC_INTC_ENABLE
    /*----------------------------------------------------------------------*/
    /* Interrupt enable related function calls please refer to User         */
    /* guide for a detailed description of these functions and the          */
    /* DM360_IPC_INTC_ENABLE macro usage                                    */
    /* Call the functions to enable ARM926 FIQ and do some basic setup to   */
    /* AINTC to accept KLD INTC (arm968) interupt in FIQ pin of Arm926      */
    /*----------------------------------------------------------------------*/
#ifndef ON_LINUX
    ARM926_enable_FIQ();  /* SWI call to enable interrupts                  */
    ARM926_INTC_init();   /* Init AINTC                                     */
#endif
#endif/*DM360_IPC_INTC_ENABLE*/
#ifdef ON_LINUX
 pfConfig = fopen("..//..//Test//TestVecs//Config//testvecs_linux.cfg","r");
#else
 pfConfig = fopen("..\\..\\..\\Test\\TestVecs\\Config\\Testvecs.cfg","r");
#endif
 if(pfConfig == NULL)
 {
   printf("\n ERROR! - Could Not open Config File %s", bConfigFile);
   exit(-1);
 }
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
        printf("HDVICP Protocol Registration Failed \n");
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
 countConfigSet = 0; /* Reset countConfigSet value to 1 */
 while(!feof(pfConfig))
 {
    /*----------------------------------------------------------------------*/
    /* Clear polling bit of ARM968; This is not required when Interrupt is  */
    /* enabled between ARM926 and ARM968. But disabling needs corresponding */
    /* change in hdvicp_framework.c file When interrupt is enabled poll_word*/
    /* points to a memory location in external memory. When interrupt is    */
    /* disabled it points to a memory location in DTCM of ARM968 - as a way */
    /* of inter processor signaling.                                        */
    /*----------------------------------------------------------------------*/

NEXT_CONFIG:
#ifndef ON_LINUX
    (*poll_word) = 0x0;
#endif
    /* Read Compliance Checking parameter */
    if(fgets(line,254,pfConfig))
    {
      sscanf(line,"%d",&testCompliance);
    }
    else
    {
      printf("\n ERROR! - Could Not find compliance checking parameter");
      break ;
    }

    /* Read Parameters file name */
    if(fgets(line,254,pfConfig))
    {
      sscanf(line,"%s",bConfigFile);
    }
    else
    {
      printf("\n ERROR! - Could Not open Parameters File");
      break ;
    }

    /* Read Input file name */
    if(fgets(line,254,pfConfig))
    {
      sscanf(line,"%s",bInputFile);
    }
    else
    {
      printf("\n ERROR! - Could Not open Input File");
      break ;
    }

    /* Read Output/Reference file name */
    if(fgets(line,254,pfConfig))
    {
      sscanf(line,"%s",bEncOutFile);
    }
    else
    {
      printf("\n ERROR! - Could Not open Output/Reference File");
      break ;
    }

    /* Read Recon file name */
    if(fgets(line,254,pfConfig))
    {
      sscanf(line,"%s",bReconOutFile);
    }
    else
    {
      printf("\n ERROR! - Could Not open Recon File");
      break ;
    }

	/* Read Me Info file name */
    if(fgets(line,254,pfConfig))
    {
      sscanf(line,"%s",bMeInfoFile);
    }
    else
    {
      printf("\n ERROR! - Could Not open Meinfo File");
      break ;
    }

    /* Open Test Config File  */
    pfConfigParamsFile = fopen(bConfigFile,"r");

    if(pfConfigParamsFile == NULL)
    {
      printf("\n ERROR! - Could Not open Params File %s", bConfigFile);
      fflush (stdout);
      goto NEXT_CONFIG;
    }

    uiTokenCtr = 0;

    /* Framesto Encode token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"FramesToEncode";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   =  &uiNumFramesToBeEncoded;

    /* RateControlPreset token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"RateControlPreset";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.videncParams.rateControlPreset;

    /* EncoderPreset token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"EncoderPreset";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.videncParams.encodingPreset;

    /* ChromaFormat token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"ChromaFormat";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.videncParams.inputChromaFormat;

    /* ImageHeight token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"ImageHeight";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   =
  						&dynamicparams.videncDynamicParams.inputHeight;

    /* ImageWidth token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"ImageWidth";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   =
  						&dynamicparams.videncDynamicParams.inputWidth;

    /* FrameRate token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"FrameRate";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   =
  						&dynamicparams.videncDynamicParams.targetFrameRate;

    /* BitRate token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"BitRate";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   =
  						&dynamicparams.videncDynamicParams.targetBitRate;

    /* IntraPeriod token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"IntraPeriod";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   =
                        &dynamicparams.videncDynamicParams.intraFrameInterval;

    /* MPEG4_mode token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"MPEG4_mode";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.MPEG4_mode;

    /* Level token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"Level";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.levelIdc;

    /* useVOS token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"useVOS";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.useVOS;

    /* useGOV token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"useGOV";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.useGOV;

    /* useDataPartition token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"useDataPartition";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.useDataPartition;

    /* useRVLC token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"useRVLC";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.useRVLC;

    /* maxDelay token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"maxDelay";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.maxDelay;

    /* aspectRatio token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"aspectRatio";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.aspectRatio;

    /* pixelRange token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"pixelRange";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.pixelRange;

    /* timerResolution token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"timerResolution";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.timerResolution;

    /* ME_Type token to be read from configfile, btype- 0 means int*/
	sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"ME_Type";
	sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.ME_Type;

    /* PacketSize token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"PacketSize";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.PacketSize;

    /* Four_MV_mode token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"Four_MV_mode";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.Four_MV_mode;

    /* Intra_QP token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"Intra_QP";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.qpIntra;

    /* Inter_QP token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"Inter_QP";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.qpInter;

    /* useHEC token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"useHEC";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.useHEC;

    /* NumAIRMBs token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"NumAIRMBs";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.airRate;

    /* useGOBSync token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"useGOBSync";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.useGOBSync;

    /* RCAlgo token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"RCAlgo";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.RcAlgo;

    /* QPMax token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"QPMax";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.QPMax;


    /* QPInit token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"QPInit";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.qpInit;

    /* QPMin token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"QPMin";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.QPMin;

    /* UMV token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"UMV";
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.UMV;

    /* PerceptualRC token to be read from configfile, btype- 0 means int*/
	sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"PerceptualRC";
	sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &dynamicparams.PerceptualRC;

	/* mvSADoutFlag token to be read from configfile */
	sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"mvSADout";
	sTokenMap[uiTokenCtr].bType     = 0 ;
	sTokenMap[uiTokenCtr++].place   = &dynamicparams.mvSADoutFlag;

    /* EncQuality token to be read from configfile, btype- 0 means int*/
	sTokenMap[uiTokenCtr].tokenName = (XDAS_Int8 *)"EncQuality_mode";
	sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = &params.EncQuality_mode;

    /* RateControlPreset token to be read from configfile, btype- 0 means int*/
    sTokenMap[uiTokenCtr].tokenName = NULL;
    sTokenMap[uiTokenCtr].bType     = 0 ;
    sTokenMap[uiTokenCtr++].place   = NULL;

    printf("\n*******************************************");
    printf("\nRead Configuration Set %d",countConfigSet);
    printf("\n*******************************************");
    countConfigSet++;

    fflush (stdout);

    /* Read the Config File*/
    readparamfile(pfConfigParamsFile);

    if(testCompliance)
    {
      printf("\nRunning in reference bit-stream complaince check Mode");
    }
    else
    {
      printf("\nRunning in Output Dump Mode");
    }

    /*----------------------------------------------------------------------- */
    /*                             OPEN INPUT & OUTPUT FILEs                  */
    /*------------------------------------------------------------------------*/
    pfInputYUVFile = fopen(bInputFile, "rb");
    if(pfInputYUVFile == NULL)
    {
        printf("\n ERROR! - Could Not open Input YUV File %s", bInputFile);
        fflush (stdout);
        exit(-1);
    }

	/* Open Me Info file */
    pfMeInfoFile = fopen(bMeInfoFile, "w");
	if(pfMeInfoFile == NULL)
	{
		printf("\n ERROR! - Could Not open Me Info File %s", bMeInfoFile);
		fflush (stdout);
		exit(-1);
	}

    /* if the output file name is NULL, bitstream dumping will be disabled using
     * swicth varibale 'bWriteEncodedData'
     */
    if(bEncOutFile[0] == '0')
    {
        bWriteEncodedData = 0;
    }
    else
    {
        if(testCompliance)
		{
        	pfRefBitStreamFile = fopen(bEncOutFile, "rb");
	        if(pfRefBitStreamFile == NULL)
	        {
	            printf("\n ERROR! -Could Not open reference bitstream File %s",
	                                                           bEncOutFile);
	            fflush (stdout);
	            exit(-1);
	        }
		}
		else
		{
        	pfOutBitStreamFile = fopen(bEncOutFile, "wb");
	        if(pfOutBitStreamFile == NULL)
	        {
	            printf("\n ERROR! -Could Not open Output bitstream File %s",
	                                                           bEncOutFile);
	            fflush (stdout);
	            exit(-1);
	        }
		}

        /* enable bitstream dumping after output file opened successfully*/
        bWriteEncodedData = 1;
    }

    bWriteSADandMV = 1;

	/* Capture width = 0 means frame pitch/buffer line width is equal to
	 * input image width
	 */
    //dynamicparams.videncDynamicParams.captureWidth = 0;

	/* Here frame pitch/buffer line width is is made to 32-byte aligned by
	 * making capture width = immediate multiple of 32 which is greater than
	 * input image width
	 */
	dynamicparams.videncDynamicParams.captureWidth =
	               (dynamicparams.videncDynamicParams.inputWidth + 31) & ~31;

    uiExtWidth =
            (dynamicparams.videncDynamicParams.inputWidth + 15) & ~0x0F;
    uiExtHeight =
            (dynamicparams.videncDynamicParams.inputHeight + 15) & ~0x0F;

	if(dynamicparams.videncDynamicParams.captureWidth < uiExtWidth)
	{
    	uiFrmPitch = uiExtWidth;
	}
	else
	{
    	uiFrmPitch = dynamicparams.videncDynamicParams.captureWidth;
	}

#ifdef RECON_DUMP
    /*-----------------------------------------------------------------------*/
    /* open the recon file if RECON_DUMP macro is enabled                    */
    /*-----------------------------------------------------------------------*/

    if(bReconOutFile[0] == '0')
    {
        /* if recon file name is NULL, switch off recon dumping
         */
        bWriteReconData = 0;
    }
    else
    {
        uiSize = uiExtWidth * uiExtHeight;
        pfOutYUVFile = fopen(bReconOutFile, "wb");

        if(pfOutYUVFile == NULL)
        {
          printf("\n ERROR! - Could Not open recon YUV File %s", pfOutYUVFile);
          fflush (stdout);
          exit(-1);
        }
        /* Enable recon dumping after recon file is opened successfully
         */
        bWriteReconData = 1;

        /* allocate memory for recon buffers. These buffers used in test
         * application only
         */
#ifdef ON_LINUX
        pubYRecon = CMEM_alloc((uiSize * sizeof(XDAS_Int8)),&memParams);
        pubURecon = CMEM_alloc(((uiSize >> 2) * sizeof(XDAS_Int8)),&memParams);
        pubVRecon = CMEM_alloc(((uiSize >> 2) * sizeof(XDAS_Int8)),&memParams);
#else
        pubYRecon = malloc(uiSize * sizeof(XDAS_Int8));
        pubURecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
        pubVRecon = malloc((uiSize >> 2) * sizeof(XDAS_Int8));
#endif
    }
#endif /*RECON_DUMP*/

    /*-----------------------------------------------------------------------*/
    /*           Allocate buffers to read input yuv planar data              */
    /*-----------------------------------------------------------------------*/

    /* Allocate buffers for the single input frame of data to be read.
     * these buffer are used in test application only
     */
    uiFrmSize = uiFrmPitch * uiExtHeight;
#ifdef ON_LINUX
    pubInY = (XDAS_UInt8 *) CMEM_alloc((uiFrmSize * sizeof(XDAS_UInt8)),&memParams);
    pubInU = (XDAS_UInt8 *) CMEM_alloc(((uiFrmSize >> 2) * sizeof(XDAS_UInt8)),&memParams);
    pubInV = (XDAS_UInt8 *) CMEM_alloc(((uiFrmSize >> 2) * sizeof(XDAS_UInt8)),&memParams);
    outargs.packetSize = CMEM_alloc((396 * sizeof(XDAS_Int32)),&memParams);
#else
    pubInY = (XDAS_UInt8 *) malloc(uiFrmSize * sizeof(XDAS_UInt8));
    pubInU = (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
    pubInV = (XDAS_UInt8 *) malloc((uiFrmSize >> 2) * sizeof(XDAS_UInt8));
    outargs.packetSize = malloc(396 * sizeof(XDAS_Int32));
#endif
    uiNumFrames = 0;
    //params.ME_Type = 0;
	//params.UMV     = 1;
    /*-----------------------------------------------------------------------*/
    /* Initialze HDVICP frame work handle used for IPC                       */
    /*-----------------------------------------------------------------------*/
    //HDVICP_initHandle(&hdvicpObj);
    params.hdvicpHandle = (void*) &hdvicpObj;

    /*-----------------------------------------------------------------------*/
    /*                    HARDWARE RELATED INITIALIZATIONS                   */
    /*-----------------------------------------------------------------------*/

    /*-----------------------------------------------------------------------*/
    /* Calling this function to map DMA related params to IDMA_DynamicParams */
    /*-----------------------------------------------------------------------*/
    //TestApp_SetDMAInitParams(&(params.DmaParams));

    /*-----------------------------------------------------------------------*/
    /*                     PARAMETERS INTIALIZATION                          */
    /*-----------------------------------------------------------------------*/

    params.videncParams.maxWidth = MAX_WIDTH;
    params.videncParams.maxHeight = MAX_HEIGHT;
    params.videncParams.maxInterFrameInterval = 1;
    params.videncParams.inputChromaFormat = IMP4HDVICPENC_YUV_420IUV;
    params.videncParams.reconChromaFormat =IMP4HDVICPENC_YUV_420IUV;
    params.videncParams.size = sizeof(IMP4HDVICPENC_Params);
	params.videncParams.maxBitRate = MAX_BITRATE;
	params.videncParams.maxFrameRate = 30000;
	params.videncParams.dataEndianness = XDM_BYTE;
	params.videncParams.inputContentType = IVIDEO_PROGRESSIVE;

    /*-----------------------------------------------------------------------*/
    /*                        MPEG4 ENCODER INSTANCE CREATION                */
    /*-----------------------------------------------------------------------*/

	if(countConfigSet == 1)
	{

		/* Call the XDAIS defined instance creation function MP4VENC_create()
		 */
		if((handle = MP4VENC_create(&fxns, &params)) == NULL)
		{
			/* Creation failed, exit
			 */
			printf("\nERROR! - Object creation failed \n");
			printErrorMsg(status.videncStatus.extendedError);
			fflush (stdout);
			exit(-1);
		}

#ifdef _ENABLE_IRES_EDMA3

		/* Call Activate the  IRES resources to query and assign IRES resources */
		iresStatus = RMAN_assignResources((IALG_Handle)handle,
											&MPEG4VENC_TI_IRES, /* IRES_Fxns* */
											1 /* scratchId */);
		if (IRES_OK != iresStatus)
		{
		  printf( "\nFailed in assigning resources \
					 Exiting for this configuration..\n");
		  goto ENCODE_ERROR;
		}

		/* Activate the  IRES resources */
		if (IRES_OK != RMAN_activateAllResources((IALG_Handle)handle,
											&MPEG4VENC_TI_IRES, /* IRES_Fxns* */
											1 /* scratchId */))
		{
		  printf( "\nFailed in activate resources \
					 Exiting for this configuration..\n");
		  goto ENCODE_ERROR;
		}
#endif

	}


	iErrorFlag = MP4VENC_control(handle,         /* Instance Handle                       */
				  XDM_GETVERSION, /* Command                               */
				  &dynamicparams, /* Pointer to Dynamic Params struct-Input*/
				  &status);       /* Pointer to the status structure-Output*/

	if(iErrorFlag == XDM_EFAIL)
	{
		printf("Get Version Number Command Failed\n");
		printErrorMsg(status.videncStatus.extendedError);
		  fflush (stdout);
		  exit(-1);
	}

	printf("\nLibrary Version: %s\n", status.videncStatus.data.buf);
    /*-----------------------------------------------------------------------*/
    /*                     DYNAMIC PARAMETERS INTIALIZATION                  */
    /*-----------------------------------------------------------------------*/

//    dynamicparams.qpInit = dynamicparams.qpIntra;
    //printf("dynamicparams.qpInit = %d\n", dynamicparams.qpInit);
    /* reference frame rate mde equal to targetframerate as target frame rate
     * different from reference frame rate is not supported in this encoder
     * encoder implementation
     */
    dynamicparams.videncDynamicParams.refFrameRate =
                         dynamicparams.videncDynamicParams.targetFrameRate;
    /* generate header us initialized to 'XDM_ENCODE_AU' to generate bitstream
     * for one complete access uint i.e. frame
     */
    dynamicparams.videncDynamicParams.generateHeader = XDM_ENCODE_AU;
    /* interframeinterval is 0, becuase MPEG-$ SP won't support B-frames
     */
    dynamicparams.videncDynamicParams.interFrameInterval  = 0;
    /* No external data is supported, hence mbdataFlag = 0
     */
    dynamicparams.videncDynamicParams.mbDataFlag  = 0;
    dynamicparams.videncDynamicParams.forceFrame  = IVIDEO_NA_FRAME;
    dynamicparams.reset_vIMCOP_every_frame = 0;
	dynamicparams.PerceptualRC = 0; /* Reserved parameter; set to 0 */

    /*-----------------------------------------------------------------------*/
    /*              GET MP4 ENCODER INPUT/OUTPUT BUFFER INFORMATION          */
    /*-----------------------------------------------------------------------*/

    /*
     * The Number of Input output buffers and their sizes are alogrith specific.
     * For a genric codec independent application like this, the buffer
     * information for a codec can be obatined by making a call to the XDAIS
     * control function-MP4VENC_control() with the command \b XDM_GETBUFINFO\b
     * The function will return back the number of input and output arrays and
     * the size of each array.
     */
    iErrorFlag=MP4VENC_control(handle,         /* Instance Handle                       */
								XDM_GETBUFINFO, /* Command                               */
								&dynamicparams, /* Pointer to Dynamic Params struct-Input*/
								&status);       /* Pointer to the status structure-Output*/

	if(iErrorFlag == XDM_EFAIL)
	{
		printf("XDM_GETBUFINFO control call failed\n");
		printErrorMsg(status.videncStatus.extendedError);
        fflush (stdout);
        exit(-1);
	}

	if(status.videncStatus.extendedError)
	printErrorMsg(status.videncStatus.extendedError);

    /*
     * Based on the Number of buffers requested by the algorithm, the
     * application will allocate for the same here
     */
    inbufdesc.frameWidth = dynamicparams.videncDynamicParams.inputWidth;
    inbufdesc.frameHeight = dynamicparams.videncDynamicParams.inputHeight;
    inbufdesc.framePitch = uiFrmPitch;
    iErrorFlag = AllocateMP4IOBuffers(status,  /* status structure - Input*/
                       &inbufdesc,  /*  Input Buffer Descriptor-Output */
                       &outbufdesc);/*  Output Buffer Descriptor-Output*/

    if(iErrorFlag == IALG_EFAIL)
    {
        printf("\nERROR! - IO buffer Memory allocation failed \n");
        fflush (stdout);
        exit(-1);
    }
     uiIOBufferAllocDone = 1;

    /*-----------------------------------------------------------------------*/
    /*                        SET BASIC INPUT PARAMETERS                     */
    /*-----------------------------------------------------------------------*/
    iErrorFlag = MP4VENC_control (handle,        /* Instance Handle*/
                                  XDM_SETPARAMS, /* Command */
                                  &dynamicparams,/* Pointer to Dynamic struct*/
                                  &status);      /* Pointer to the status info*/

    inargs.videncInArgs.inputID = 1;
	if(iErrorFlag == XDM_EFAIL)
	{
		printf("XDM_SETPARAMS control call failed\n");
		printErrorMsg(status.videncStatus.extendedError);
        fflush (stdout);
        exit(-1);
	}

	if(status.videncStatus.extendedError)
	printErrorMsg(status.videncStatus.extendedError);

/*
    if(iErrorFlag == IALG_EFAIL)
    {
        printf("\nERROR! - Please check your config file \n");
        fflush (stdout);
        goto CONFIG_ERROR;
    }
*/
    /*-----------------------------------------------------------------------*/
    /*                                ENCODE LOOP                            */
    /*-----------------------------------------------------------------------*/

    printf("\nStarting Encoder...\n");
    fflush (stdout);
    uiNumBytesWritten = 0;
	intTimer = 0;
    for(uiNumFrames = 0; uiNumFrames < uiNumFramesToBeEncoded;uiNumFrames++)
    {
        /*-------------------------------------------------------------------*/
        /*                          SET INPUTS                               */
        /*-------------------------------------------------------------------*/

        /*!
         * The Inputs for the encode call are:
         * - YUV Frame - To be read from the input file.
         * - Any Dynamic Parameter Changes.
         */
        printf("\n Reading input frame -- ");
        fflush (stdout);
		//if(!uiNumFrames)
        {
        ReadInputData(&inbufdesc,
                      dynamicparams.videncDynamicParams.inputWidth,
                      dynamicparams.videncDynamicParams.inputHeight,
					  uiFrmPitch,
					  uiExtHeight,
                      pfInputYUVFile);
		}

        printf("Frame : %d", uiNumFrames);
        fflush (stdout);

        /*!
         * Implement any Dynamic Parameter changes here (Call MP4VENC_cintrol()
         * with approriate command and parameters).
         */
		if(uiNumFrames != 0)
		{
			if(params.MPEG4_mode == 0) /* H.263 case*/
			{
				intTimer += (XDAS_UInt32) (((long long)30 * 1000 * 1000)/
                 (long long)dynamicparams.videncDynamicParams.targetFrameRate);

				inargs.TimeStamp = intTimer/1000;
			}
			else /* MPEG-4 case */
			{
				inargs.TimeStamp += (XDAS_UInt32)
				(((long long)params.timerResolution * 1000)/
				(long long)dynamicparams.videncDynamicParams.targetFrameRate);
			}
		}
		else
		{
            inargs.TimeStamp = 0;
		}

        /*-------------------------------------------------------------------*/
        /*                          ENCODE FRAME                             */
        /*-------------------------------------------------------------------*/
#ifdef PROFILE_ONLINUX
            encoder_timeptr = &encoder_time;
            time_before_process = gettimeofday(encoder_timeptr, NULL);
	    time_before_process = encoder_timeptr->tv_usec;
            //printf("time before = %d\n",encoder_timeptr->tv_usec);
#endif

#ifdef TEST_GEN_HEADER

		if((inargs.TimeStamp % 2) == 1)
		{
			dynamicparams.videncDynamicParams.generateHeader = XDM_GENERATE_HEADER;
		}
		else
		{
			dynamicparams.videncDynamicParams.generateHeader = XDM_ENCODE_AU;
		}
		iErrorFlag = MP4VENC_control(handle,         /* Instance Handle                       */
						XDM_SETPARAMS, /* Command                               */
						&dynamicparams, /* Pointer to Dynamic Params struct-Input*/
						&status);       /* Pointer to the status structure-Output*/

		if(iErrorFlag == XDM_EFAIL)
		{
			printf("Get Status Info Command Faile\n");
			printErrorMsg(status.videncStatus.extendedError);
			fflush (stdout);
			exit(-1);
		}

		if(status.videncStatus.extendedError)
			printErrorMsg(status.videncStatus.extendedError);

#endif
#ifdef ENABLE_CORRUPTION_TESTS

		globalStatus |= proc_call_args_corruption_tests(handle,&inbufdesc,&outbufdesc,&inargs,&outargs);

#endif

        iErrorFlag =  MP4VENC_Encode( handle, /* Instance Handle    - Input*/
                                  &inbufdesc, /* Input Buffers      - Input*/
                                  &outbufdesc,/* Output Buffers     - Output*/
                                  &inargs,   /* Input Parameters   - Input*/
                                  &outargs); /* Output Parameters  - Output*/

#ifdef PROFILE_ONLINUX
            time_after_process = gettimeofday(encoder_timeptr, NULL);
            //printf("time After = %d\n",encoder_timeptr->tv_usec);
            //printf("time before = %d, time after = %d\n",time_before_process,time_after_process);
	    if(encoder_timeptr->tv_usec <= time_before_process)
	    {

	    	encoder_timeptr->tv_usec += 1000000;
	    }
	    printf("\n PROCESS LEVEL FRAME DECODE TIME = %d  ",(encoder_timeptr->tv_usec - time_before_process));
	    printf("ARM968 FRAME DECODE TIME = %d\n",arm968_time);
	    count_arm926 +=  ((float)(encoder_timeptr->tv_usec - time_before_process)/1000);
	    count_arm968 += ((float)arm968_time/1000);
#endif

		PRINT_OUT_BUFS_MPEG4(outbufdesc);
		PRINT_OUT_ARGS_MPEG4(outargs);

        if(iErrorFlag == XDM_EFAIL)
        {

			printf("Encoder Returned a Failure\n");
			printf("\tFrame No              : %d\n", uiNumFrames);
			printf("\tError Status          : %d\n", iErrorFlag);
			printf("\tExtended Error Status : %d\n",outargs.videncOutArgs.extendedError);
            printErrorMsg(outargs.videncOutArgs.extendedError);

            /*!
             * Get Detailed information regarding the failure
             */
#if 0
            MP4VENC_control(
                      handle,         /* Instance Handle*/
                      XDM_GETSTATUS,  /* Command - GET STATUS */
                      &dynamicparams, /* Input */
                      &status         /* Output */
                     );


            printErrorMsg(status.videncStatus.extendedError);
#endif
            fflush (stdout);
        }

        if(status.videncStatus.extendedError == XDM_FATALERROR)
        {
            break;
        }

        uiNumBytesWritten += outargs.videncOutArgs.bytesGenerated;

        /*-------------------------------------------------------------------*/
        /*                    ADDITIONAL INFORMATION READ                    */
		/* Call control() with XDM_GETSTATUS to get teh other satus info     */
        /*-------------------------------------------------------------------*/
        MP4VENC_control(handle,
                        XDM_GETSTATUS,
                        &dynamicparams,
                        &status);

        /*-------------------------------------------------------------------*/
        /*                         OUTPUT DATA WRITE                         */
        /*-------------------------------------------------------------------*/

        /* Write out the Encoded bit-stream
         */
	    retVal = XDM_EOK;
	    printf(" Bytes generated - %d\n",outargs.videncOutArgs.bytesGenerated);
        if(bWriteEncodedData && outargs.videncOutArgs.bytesGenerated)
        {
            retVal = WriteDataOut(&outbufdesc, pfOutBitStreamFile, &outargs,
                                                           testCompliance );


			if(testCompliance && (retVal == XDM_EFAIL))
			{
		        printf("\n\n reference bit-stream complaince check FAILED");
		        printf(" at this frame\n");
		        goto ENCODE_ERROR;
			}

        }

        /* Dump the MeInfo file */
		if(bWriteSADandMV && (dynamicparams.mvSADoutFlag == 1))
		{
			XDAS_UInt32 cntRow, cntCol;
			XDAS_Int32 *puiSadMVinfo;
            IMP4HDVICPENC_exportMEdata *psMeInfo;


			puiSadMVinfo = (XDAS_Int32*)outbufdesc.bufs[1];

			if(uiNumFrames != 0)
			{
				fprintf(pfMeInfoFile, "Frame : %d\n", uiNumFrames);
				for(cntRow = 0; cntRow < (inbufdesc.frameHeight >> 4); cntRow++)
				{
					for(cntCol = 0; cntCol < (inbufdesc.frameWidth >> 4); cntCol++)
					{
                        psMeInfo = (IMP4HDVICPENC_exportMEdata *)puiSadMVinfo + (cntRow * (inbufdesc.frameWidth >> 4)) + cntCol;

						fprintf(pfMeInfoFile, "[mbX = %3d,mbY = %3d]: SAD = %8d, Mvx = %4d, Mvy = %4d\n",cntCol,cntRow,psMeInfo->meSad,psMeInfo->mvX,psMeInfo->mvY);
					}
				}
			}
		}

        printf(" Frame encoding complete\n");
        fflush (stdout);

        /* RECON_DUMP macro is to enable/disable dumping of recon frame into
         * recon file mentioned in config file
         */
#ifdef RECON_DUMP
        if(bWriteReconData && outargs.videncOutArgs.reconBufs.numBufs)
        {
            pubInBufY  = (XDAS_UInt8*)outargs.videncOutArgs.
                                      reconBufs.bufDesc[0].buf;
            pubInBufUV = (XDAS_UInt8*)outargs.videncOutArgs.
                                      reconBufs.bufDesc[1].buf;

            /* funtion to convert chroma interleaved to chroma planar
             */
            MPEG4VENC_TI_InttoPlanar_CbCrformat (pubYRecon,
                          pubURecon,
                          pubVRecon,
                          pubInBufY,
                          pubInBufUV,
                          uiExtWidth,
                          uiExtHeight);

	        /* Write out the reconstructed frame
	         */
            WriteReconOut(pubYRecon,
                    pubURecon,
                    pubVRecon,
                    uiExtWidth,
                    uiExtHeight,
                    pfOutYUVFile);
        }
#endif /* RECON_DUMP */
    }/* for loop for uiNumFramesTobeEncoded */

#ifdef PROFILE_ONLINUX
	{
		float avg;

		avg = (count_arm926/(float)uiNumFramesToBeEncoded);
		avg = (1000/avg);
		printf("\n\n\nARM926 fps - %f\t",avg);
		avg = (count_arm968/(float)uiNumFramesToBeEncoded);
		avg = (1000/avg);
		printf("ARM968 fps - %f\n\n\n",avg);

#ifdef ENABLE_CORRUPTION_TESTS
		if(globalStatus == 0)
			printf(" Corruption Tests Results: PASS\n");
		else
			printf(" Corruption Tests Results: FAIL\n");
#endif

    }
#endif


	/* Write MPEG-4 sequence end code 0x000001B1 at the end of bitstream file
	 */
    if (params.MPEG4_mode == 1)
    {
        XDAS_UInt8  endcode_0 = 0x00; /* Seq end code byte-0*/
        XDAS_UInt8  endcode_1 = 0x00; /* Seq end code byte-1*/
        XDAS_UInt8  endcode_2 = 0x01; /* Seq end code byte-2*/
        XDAS_UInt8  endcode_3 = 0xB1; /* Seq end code byte-3*/
        fputc(endcode_0,pfOutBitStreamFile);
        fputc(endcode_1,pfOutBitStreamFile);
        fputc(endcode_2,pfOutBitStreamFile);
        fputc(endcode_3,pfOutBitStreamFile);
        fflush(pfOutBitStreamFile);
    }

//CONFIG_ERROR:

    /*-----------------------------------------------------------------------*/
    /*                              PRINT STATS                              */
    /*-----------------------------------------------------------------------*/
    printf("\n --------------  SUMMARY --------------------\n");
    printf("  Total number of Frames          = %d\n",
    (XDAS_UInt32)uiNumFrames);
    if(testCompliance)
	{
    	printf("\n reference bit-stream complaince check PASSED \n");
	}
	else
	{
		printf("\n Bit-stream dumped to output file \n");
	}
    printf (" --------------    END   --------------------\n");
    fflush (stdout);

	/*-------------------------------------------------------------------*/
	/* Call control() with XDM_RESET 								     */
	/*-------------------------------------------------------------------*/
	MP4VENC_control(handle,
					XDM_RESET,
					&dynamicparams,
					&status);

ENCODE_ERROR:

	if(uiIOBufferAllocDone)
	{
    	FreeMP4IOBuffers(&inbufdesc, /* Input Buffer Descriptor */
                   	&outbufdesc); /* Output Buffer Descriptor */
	}

    /*Free used up memory */
#ifdef ON_LINUX
    CMEM_free(pubInY,&memParams);
    CMEM_free(pubInU,&memParams);
    CMEM_free(pubInV,&memParams);
    CMEM_free(outargs.packetSize,&memParams);
#else
    free(pubInY);
    free(pubInU);
    free(pubInV);
    free(outargs.packetSize);
#endif

	/* free the recon buffers if RECON_DUMP is enabled
	 */
#ifdef RECON_DUMP
    if(bWriteReconData)
    {
#ifdef ON_LINUX
		CMEM_free(pubYRecon,&memParams);
		CMEM_free(pubURecon,&memParams);
		CMEM_free(pubVRecon,&memParams);
#else
        free(pubYRecon);
        free(pubURecon);
        free(pubVRecon);
#endif
    }
#endif /* RECON_DUMP*/

    /*------------------------------------------------------------------------*/
    /* Signal ARM968 to terminate wait and goto sleep						  */
    /*------------------------------------------------------------------------*/
#ifndef ON_LINUX
    (*poll_word) = 0xFFFFFFFF;
#endif

	/* Close the input YUV file
	 */
    fclose(pfInputYUVFile);

	/* Close the Me Info file
	 */
    fclose(pfMeInfoFile);

	/* Close the output bitstream and recon files
	 */
    if(testCompliance)
	{
    	fclose(pfRefBitStreamFile);
	}
    else
	{
    	fclose(pfOutBitStreamFile);
	}

#ifdef RECON_DUMP
    fclose(pfOutYUVFile);
#endif /* RECON_DUMP*/
  }/* while loop*/

    /*-----------------------------------------------------------------------*/
    /*                   FREE MP4 ENCODER INPUT/OUTPUT BUFFERS               */
    /*-----------------------------------------------------------------------*/

#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
     if (IRES_OK == iresStatus)
	 {
	 	iresStatus = RMAN_freeResources((IALG_Handle)(handle),
                                        &MPEG4VENC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */);
    	if (IRES_OK != iresStatus)
    	{
    	    printf("Free Resource Failed \n");
    	    //return -1;
		}
	}
#endif

    /*-----------------------------------------------------------------------*/
    /*                           DELETE ENCODER INSTANCE                     */
    /*-----------------------------------------------------------------------*/
    MP4VENC_delete(handle);

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
  fclose(pfConfig);

  return 0;
}/* main */


/*---------------------------------------------------------------------------*/
/*                           LOCAL STATIC FUNCTIONS                          */
/*---------------------------------------------------------------------------*/

/*===========================================================================*/
/**
*@brief  Allocate buffers as required by the algorithm for the input and output
*
*@param  MP4EncStatus
*        Algorithm status structure.
*
*@param  ptMP4EncInpBufDesc
*        Pointer to the buffer descriptor structure with requirements for the
*        input buffers.
*
*@param  ptMP4EncOutBufDesc
*        Pointer to the buffer descriptor structure with requirements for the
*        output buffers.

*
*@return None
*
*@note
*/
/*===========================================================================*/
XDAS_Int32 AllocateMP4IOBuffers( MP4VENC_Status     MP4EncStatus,
                                 IVIDEO1_BufDescIn *ptMP4EncInpBufDesc,
                                 XDM_BufDesc       *ptMP4EncOutBufDesc)
{
  XDAS_Int32 i;

  /*-------------------------------------------------------------------------*/
  /*                            ALLOCATE INPUT BUFFERS                       */
  /*-------------------------------------------------------------------------*/
  ptMP4EncInpBufDesc->numBufs = MP4EncStatus.videncStatus.bufInfo.minNumInBufs;

  for( i = 0; i < MP4EncStatus.videncStatus.bufInfo.minNumInBufs; i++)
  {
    /* Allocation size for the current buffer
     */
    ptMP4EncInpBufDesc->bufDesc[i].bufSize =
      MP4EncStatus.videncStatus.bufInfo.minInBufSize[i];

    /* Allocate buffer pointer
     */
#ifdef ON_LINUX
    ptMP4EncInpBufDesc->bufDesc[i].buf =
      (XDAS_Int8 *) CMEM_alloc((ptMP4EncInpBufDesc->bufDesc[i].bufSize *
                           sizeof(XDAS_Int8)),&memParams);
#else
    ptMP4EncInpBufDesc->bufDesc[i].buf =
      (XDAS_Int8 *) malloc(ptMP4EncInpBufDesc->bufDesc[i].bufSize *
                           sizeof(XDAS_Int8));
#endif
    if(ptMP4EncInpBufDesc->bufDesc[i].buf == NULL)
    {
      /* Memory not allocated, return failure
       */
      printf("couldn't allocate memory");
      return (-1);
    }
  }

  /*-------------------------------------------------------------------------*/
  /*                           ALLOCATE OUTPUT BUFFERS                       */
  /*-------------------------------------------------------------------------*/
  ptMP4EncOutBufDesc->numBufs =
    MP4EncStatus.videncStatus.bufInfo.minNumOutBufs;
#ifdef ON_LINUX
  ptMP4EncOutBufDesc->bufSizes =
    (XDAS_Int32 *) CMEM_alloc((ptMP4EncOutBufDesc->numBufs * sizeof(XDAS_Int32)),&memParams);
#else
  ptMP4EncOutBufDesc->bufSizes =
    (XDAS_Int32 *) malloc(ptMP4EncOutBufDesc->numBufs * sizeof(XDAS_Int32));
#endif
  if(ptMP4EncOutBufDesc->bufSizes == NULL)
  {
    /* Memory not allocated, return failure
     */
    return (-1);
  }
#ifdef ON_LINUX
  ptMP4EncOutBufDesc->bufs =
    (XDAS_Int8 **) CMEM_alloc((ptMP4EncOutBufDesc->numBufs * sizeof(XDAS_Int8 *)),&memParams);
#else
  ptMP4EncOutBufDesc->bufs =
    (XDAS_Int8 **) malloc(ptMP4EncOutBufDesc->numBufs * sizeof(XDAS_Int8 *));
#endif
  if(ptMP4EncOutBufDesc->bufs == NULL)
  {
    /* Memory not allocated, return failure*/
    return (-1);
  }

  for( i = 0; i < MP4EncStatus.videncStatus.bufInfo.minNumOutBufs; i++)
  {
    /* Allocate size for the current buffer*/
    ptMP4EncOutBufDesc->bufSizes[i] =
      MP4EncStatus.videncStatus.bufInfo.minOutBufSize[i];

    /* Allocate buffer pointer*/
#ifdef ON_LINUX
    ptMP4EncOutBufDesc->bufs[i] =
      (XDAS_Int8 *) CMEM_alloc(
                            (ptMP4EncOutBufDesc->bufSizes[i] *
                             sizeof(XDAS_Int8)),&memParams
                          );
#else
    ptMP4EncOutBufDesc->bufs[i] =
      (XDAS_Int8 *) malloc(
                            ptMP4EncOutBufDesc->bufSizes[i] *
                            sizeof(XDAS_Int8)
                          );
#endif
    if(ptMP4EncOutBufDesc->bufs[i] == NULL)
    {
      /* Memory not allocated, return failure*/
      return (-1);
    }
  }
  return(0);

}/* AllocateMP4IOBuffers */

/*===========================================================================*/
/**
*@brief  Free buffers as used by the algorithm for the input and output
*
*@param  ptMP4EncInpBufDesc
*        Pointer to the buffer descriptor structure with requirements for the
*        input buffers.
*
*@param  ptMP4EncOutBufDesc
*        Pointer to the buffer descriptor structure with requirements for the
*        output buffers.

*
*@return None
*
*@note
*/
/*===========================================================================*/
void FreeMP4IOBuffers (IVIDEO1_BufDescIn *ptMP4EncInpBufDesc,
                       XDM_BufDesc       *ptMP4EncOutBufDesc)
{
  XDAS_Int32 i;

  /*-------------------------------------------------------------------------*/
  /*                                FREE INPUT BUFFERS                       */
  /*-------------------------------------------------------------------------*/
  for(i = 0; i < ptMP4EncInpBufDesc->numBufs; i++)
  {
#ifdef ON_LINUX
      CMEM_free(ptMP4EncInpBufDesc->bufDesc[i].buf,&memParams);
#else
      free(ptMP4EncInpBufDesc->bufDesc[i].buf);
#endif
  }

  ptMP4EncInpBufDesc->numBufs = 0;

  /*-------------------------------------------------------------------------*/
  /*                               FREE OUTPUT BUFFERS                       */
  /*-------------------------------------------------------------------------*/
  for(i = 0; i < ptMP4EncOutBufDesc->numBufs; i++)
  {
#ifdef ON_LINUX
      CMEM_free(ptMP4EncOutBufDesc->bufs[i],&memParams);
#else
      free(ptMP4EncOutBufDesc->bufs[i]);
#endif
  }
#ifdef ON_LINUX
  CMEM_free(ptMP4EncOutBufDesc->bufs,&memParams);
  CMEM_free(ptMP4EncOutBufDesc->bufSizes,&memParams);
#else
  free(ptMP4EncOutBufDesc->bufs);
  free(ptMP4EncOutBufDesc->bufSizes);
#endif
  ptMP4EncOutBufDesc->numBufs = 0;
}/* FreeMP4IOBuffers */

/*===========================================================================*/
/*!
*@brief ReadInputData () function Reads input data from file
*
*@params tInpBufferDesc
*        Input buffer descriptor pointer
*
*        uiPicWidth
*        Width of input YUV image
*
*        uiPicHeight
*        Height of the input YUV image
*
*        pfInYUVFile
*        Input YUV file pointer
*
*@return status
*/
/*===========================================================================*/

XDAS_Int32 ReadInputData (IVIDEO1_BufDescIn *tInpBufferDesc,
                          XDAS_UInt32        uiPicWidth,
                          XDAS_UInt32        uiPicHeight,
						  XDAS_UInt32        uiExtWidth,
						  XDAS_UInt32        uiExtHeight,
                          FILE               *pfInYUVFile)
{
    XDAS_UInt8 *pubSubPictY;
    XDAS_UInt8 *pubSubPictUV;
    XDAS_UInt32 uiFrmSize = (uiPicWidth * uiPicHeight);
    XDAS_Int32 iStatus = 0;
	XDAS_UInt32 uiLineCnt;

    /* Code starts here */
	if((uiPicWidth == uiExtWidth) && (uiPicHeight == uiExtHeight))
	{
	    /* Read the current input frame*/
	    if(fread((Void *)pubInY, 1, uiFrmSize, pfInYUVFile) != uiFrmSize)
	    {
	        iStatus = -1;
	    }

	    if(fread((Void *)pubInU, 1, (uiFrmSize >> 2), pfInYUVFile) !=
	    (uiFrmSize >> 2))
	    {
	        iStatus = -1;
	    }

	    if(fread((Void *)pubInV, 1, (uiFrmSize >> 2), pfInYUVFile) !=
	    (uiFrmSize >> 2))
	    {
	        iStatus = -1;
	    }
	}
	else
	{
	    /* Read the current input frame from the input YUV File */
		pubSubPictY = pubInY;
		for(uiLineCnt = 0; uiLineCnt < uiPicHeight; uiLineCnt++)
		{
		    if(fread((Void *)pubSubPictY, 1, uiPicWidth, pfInYUVFile) !=
		       uiPicWidth)
		    {
		        iStatus = -1;
		    }
			pubSubPictY += uiExtWidth;
		}

		pubSubPictUV = pubInU;
		for(uiLineCnt = 0; uiLineCnt < (uiPicHeight >> 1); uiLineCnt++)
		{
		    if(fread((Void *)pubSubPictUV, 1, (uiPicWidth >> 1), pfInYUVFile) !=
		       (uiPicWidth >> 1))
		    {
		        iStatus = -1;
		    }
			pubSubPictUV += (uiExtWidth >> 1);
		}

		pubSubPictUV = pubInV;
		for(uiLineCnt = 0; uiLineCnt < (uiPicHeight >> 1); uiLineCnt++)
		{
		    if(fread((Void *)pubSubPictUV, 1, (uiPicWidth >> 1), pfInYUVFile) !=
		       (uiPicWidth >> 1))
		    {
		        iStatus = -1;
		    }
			pubSubPictUV += (uiExtWidth >> 1);
		}
	}
    /*
     * Convert data into subpicture and store it into buffers acllocated by the
     * system for the
     */
    if(!iStatus)
    {
        pubSubPictY  = (XDAS_UInt8 *)(tInpBufferDesc->bufDesc[0].buf);
        pubSubPictUV = (XDAS_UInt8 *)(tInpBufferDesc->bufDesc[1].buf);
        /* funtion to convert chroma planar to chroma interleaved*/
        MPEG4VENC_TI_PlanartoInt_CbCrformat( pubInY,
                        pubInU,
                        pubInV,
                        pubSubPictY,
                        pubSubPictUV,
                        uiExtWidth,
                        uiExtHeight);
    }
    return(iStatus);
}/* ReadInputData */

/*===========================================================================*/
/*!
*@brief WriteReconOut() Writes recon data  to file
*
*@params    pubReconY
*           Pointer to reconstructed Luma data
*
*           pubReconU
*           Pointer to reconstructed chroma Cb data
*
*           pubReconV
*           Pointer to reconstructed chroma Cr data
*
*           uiWidth
*           Width of the picture
*
*           uiHeight
*           Height of the picture
*
*           pfOutYUVFile
*           Pointer to recon YUV file
*
*@return status
*/
/*===========================================================================*/
#ifdef RECON_DUMP
XDAS_Int32 WriteReconOut (XDAS_UInt8 *pubReconY,
                          XDAS_UInt8 *pubReconU,
                          XDAS_UInt8 *pubReconV,
                          XDAS_Int32  uiWidth,
                          XDAS_Int32  uiHeight,
                          FILE       *pfOutYUVFile)
{
  XDAS_Int32 uiSize = uiWidth * uiHeight;

  /*--------------------------------------------------------------------------*/
  /*                        WRITE THE BITSTREAM                               */
  /*--------------------------------------------------------------------------*/
  fwrite(pubReconY, 1, uiSize, pfOutYUVFile);
  fwrite(pubReconU, 1, (uiSize >> 2), pfOutYUVFile);
  fwrite(pubReconV, 1, (uiSize >> 2), pfOutYUVFile);
  fflush(pfOutYUVFile);
  return(0);
}
#endif /* RECON_DUMP*/

/*===========================================================================*/
/*!
*@brief Writes bit-stream to output file.
*
*@param tOutBufferDesc
*       Pointer to output buffer descriptor which contains bitstream pointer
*       and no. of bytes encoded etc
*
*       pfOutBitStreamFile
*       Output file pounter to which bit-stream to be written
*
*@return The index number if the string is a valid parameter name, -1 for error
*/
/*===========================================================================*/

XDAS_Int32 WriteDataOut (XDM_BufDesc *tOutBufferDesc,
                         FILE *pfOutBitStreamFile,
                         MP4VENC_OutArgs *outargs,
                         XDAS_Int8 testCompliance)
{
  XDAS_Int32 i = 0;
  XDAS_Int32 retVal;
  XDAS_Int8 *refData;
  retVal = XDM_EOK;
  /*--------------------------------------------------------------------------*/
  /*                        WRITE THE BITSTREAM                               */
  /*--------------------------------------------------------------------------*/
  //for(i=0; i < tOutBufferDesc->numBufs ; i++)
  {
  	if(testCompliance)
	{
#ifdef ON_LINUX
	   	refData = (XDAS_Int8*)CMEM_alloc((outargs->videncOutArgs.bytesGenerated),&memParams);
#else
	   	refData = (XDAS_Int8*)malloc(outargs->videncOutArgs.bytesGenerated);
#endif
       	fread(refData, 1, outargs->videncOutArgs.bytesGenerated,
       	                                            pfRefBitStreamFile);
    	if(memcmp(refData, tOutBufferDesc->bufs[i],
    	                            outargs->videncOutArgs.bytesGenerated))
    	{
      		printf("\nXDM_EFAIL - Failed with reference bitstream\n");
      		retVal = XDM_EFAIL;
    	}
#ifdef ON_LINUX
		CMEM_free(refData,&memParams);
#else
		free(refData);
#endif
	}
	else
	{
   		fwrite(tOutBufferDesc->bufs[i],sizeof(XDAS_UInt8),
          outargs->videncOutArgs.bytesGenerated, pfOutBitStreamFile);
    }
  }

  fflush(pfOutBitStreamFile);
  return(retVal);

}/* WriteDataOut */

/*===========================================================================*/
/**
*@brief  Reads the configuration file content in a buffer and returns the
*        address of the buffer
*
*@param  fname
*        Pointer to the configuration file.
*
*@return None
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

  /*-------------------------------------------------------------------------*/
  /* Note that ftell() gives us the file size as the file system sees it.    */
  /* The actual file size, as reported by fread() below will be often smaller*/
  /* due to CR/LF to CR conversion and/or control characters after the dos   */
  /* EOF marker in the file.                                                 */
  /*-------------------------------------------------------------------------*/
  FileSize = fread (buf, 1, FileSize, fname);
  buf[FileSize] = '\0';

  fclose (fname);
  return buf;

}/* GetConfigFileContent */


/*===========================================================================*/
/*!
*@brief Returns the index number from sTokenMap[] for a given parameter name.
*
*@param s
*    parameter name string
*
*@return The index number if the string is a valid parameter name, -1 for error
*/
/*===========================================================================*/
XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s)
{
  XDAS_Int32 i = 0;

  while (sTokenMap[i].tokenName != NULL)
    if (0==strcmp ((char *)sTokenMap[i].tokenName, (char *)s))
      return i;
    else
      i++;
  return -1;
}/* ParameterNameToMapIndex */

/*===========================================================================*/
/*!
*@brief Parses the character array buf and writes global variable input.This is
*        necessary to facilitate the addition of new parameters through the
*        sTokenMap[] mechanism.Need compiler-generated addresses in sTokenMap.
*
*@param buf
*       Pointer to the buffer to be parsed
*
*@param bufsize
*       size of buffer
*
*@return status ( PASS/ FAIL)
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

  while (p < bufend)
  {
    switch (*p)
    {
      case 13:
        p++;
        break;
      case '#':     /* Found comment*/
        *p = '\0';  /* Replace '#' with '\0' in case of comment */
                    /* immediately following integer or string*/
        /* Skip till EOL or EOF, whichever comes first*/
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
      case '\t':            /* Skip whitespace, leave state unchanged*/
        if (InString)
          p++;
        else
      {                     /* Terminate non-strings once whitespace is found*/
          *p++ = '\0';
          InItem = 0;
        }
        break;

      case '"':             /* Begin/End of String*/
        *p++ = '\0';
        if (!InString)
        {
          items[item++] = p;
          InItem = ~InItem;
        }
        else
          InItem = 0;
        InString = ~InString; /* Toggle*/
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
      fprintf(fpErr, " \nParameter Name '%s' not recognized.. ", items[i]);
      return -1 ;

    }
    if (strcmp ("=", (char *)items[i+1]))
    {
      fprintf(fpErr, "\nfile: '=' expected as the second token in each line.");
      return -1 ;
    }
    if(sTokenMap[MapIdx].bType == 1)
    {
      strcpy((char *)sTokenMap[MapIdx].place, (char *)items[i+2]);
    }
    else
    {
      sscanf ((char *)items[i+2], "%d", &IntContent) ;
      * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
    }
  }
  return 0 ;
}/* ParseContent */

/*===========================================================================*/
/*!
*@brief Top Level function to read the parameter file.
*
*@param fname
*       Pointer to the configuration file
*
*@return status ( PASS/ FAIL)
*/
/*===========================================================================*/
XDAS_Int32 readparamfile(FILE * fname)
{
  XDAS_Int8 *FileBuffer = NULL ;
  XDAS_Int32 retVal ;

  /*-----------------------------------------------------*/
  /* read the contentof configfile in a buffer           */
  /*-----------------------------------------------------*/
  FileBuffer = GetConfigFileContent(fname);

  /*-----------------------------------------------------*/
  /* Call function to parse the contents of config file  */
  /*-----------------------------------------------------*/
  if(FileBuffer)
  {
    retVal  = ParseContent(FileBuffer,strlen((char *)FileBuffer));
    return retVal ;
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
*        input MPEG4 encoder error codes
*
*@return void
*
*@note
*/
/*===========================================================================*/
int printErrorMsg(XDAS_Int32 errorCode)
{
	printf("\n");
/*	if(XDM_ISFATALERROR(errorCode))
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
*/

	switch(errorCode)
	{

		case MPEG4VENC_ERR_HANDLE_NULL:
			printf("MPEG4VENC_ERR_HANDLE_NULL\n");
			break;

		case MPEG4VENC_ERR_INCORRECT_HANDLE:
			printf("MPEG4VENC_ERR_INCORRECT_HANDLE\n");
			break;

		case MPEG4VENC_ERR_MEMTAB_NULL:
			printf("MPEG4VENC_ERR_MEMTAB_NULL\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_INITPARAMS_SIZE:
			printf("MPEG4VENC_ERR_IVIDENC1_INITPARAMS_SIZE\n");
			break;

		case MPEG4VENC_ERR_MEMTABS_SIZE:
			printf("MPEG4VENC_ERR_MEMTABS_SIZE\n");
			break;

		case MPEG4VENC_ERR_MEMTABS_ATTRS:
			printf("MPEG4VENC_ERR_MEMTABS_ATTRS\n");
			break;

		case MPEG4VENC_ERR_MEMTABS_SPACE:
			printf("MPEG4VENC_ERR_MEMTABS_SPACE\n");
			break;

		case MPEG4VENC_ERR_MEMTABS_BASE_NULL:
			printf("MPEG4VENC_ERR_MEMTABS_BASE_NULL\n");
			break;

		case MPEG4VENC_ERR_MEMTABS_BASE_NOT_ALIGNED:
			printf("MPEG4VENC_ERR_MEMTABS_BASE_NOT_ALIGNED\n");
			break;

		case MPEG4VENC_ERR_MEMTABS_OVERLAP:
			printf("MPEG4VENC_ERR_MEMTABS_OVERLAP\n");
			break;

		case MPEG4VENC_ERR_ENCODINGPRESET:
			printf("MPEG4VENC_ERR_ENCODINGPRESET\n");
			break;

		case MPEG4VENC_ERR_INPUTCHROMAFORMAT:
			printf("MPEG4VENC_ERR_INPUTCHROMAFORMAT\n");
			break;

		case MPEG4VENC_ERR_MAXFRAMERATE:
			printf("MPEG4VENC_ERR_MAXFRAMERATE\n");
			break;

		case MPEG4VENC_ERR_MAXBITRATE:
			printf("MPEG4VENC_ERR_MAXBITRATE\n");
			break;

		case MPEG4VENC_ERR_MAXWIDTH:
			printf("MPEG4VENC_ERR_MAXWIDTH\n");
			break;

		case MPEG4VENC_ERR_MAXHEIGHT:
			printf("MPEG4VENC_ERR_MAXHEIGHT\n");
			break;

		case MPEG4VENC_ERR_MAX_TOTAL_MBS:
			printf("MPEG4VENC_ERR_MAX_TOTAL_MBS\n");
			break;

		case MPEG4VENC_ERR_DATAENDIANNESS:
			printf("MPEG4VENC_ERR_DATAENDIANNESS\n");
			break;

		case MPEG4VENC_ERR_MAXINTERFRAMEINTERVAL:
			printf("MPEG4VENC_ERR_MAXINTERFRAMEINTERVAL\n");
			break;

		case MPEG4VENC_ERR_RECONCHROMAFORMAT:
			printf("MPEG4VENC_ERR_RECONCHROMAFORMAT\n");
			break;

		case MPEG4VENC_ERR_INPUTCONTENTTYPE:
			printf("MPEG4VENC_ERR_INPUTCONTENTTYPE\n");
			break;

		case MPEG4VENC_ERR_RATECONTROLPRESET:
			printf("MPEG4VENC_ERR_RATECONTROLPRESET\n");
			break;

		case MPEG4VENC_ERR_MPEG4MODE:
			printf("MPEG4VENC_ERR_MPEG4MODE\n");
			break;

		case MPEG4VENC_ERR_LEVELIDC:
			printf("MPEG4VENC_ERR_LEVELIDC\n");
			break;

		case MPEG4VENC_ERR_ENCPARM_USE_VOS:
			printf("MPEG4VENC_ERR_ENCPARM_USE_VOS\n");
			break;

		case MPEG4VENC_ERR_USE_GOV:
			printf("MPEG4VENC_ERR_USE_GOV\n");
			break;

		case MPEG4VENC_ERR_DATA_PART:
			printf("MPEG4VENC_ERR_DATA_PART\n");
			break;

		case MPEG4VENC_ERR_RVLC:
			printf("MPEG4VENC_ERR_RVLC\n");
			break;

		case MPEG4VENC_ERR_DATA_PART_RVLC:
			printf("MPEG4VENC_ERR_DATA_PART_RVLC\n");
			break;

		case MPEG4VENC_ERR_TIMER_RESOLUTION:
			printf("MPEG4VENC_ERR_TIMER_RESOLUTION\n");
			break;

		case MPEG4VENC_ERR_ASPECTRATIO:
			printf("MPEG4VENC_ERR_ASPECTRATIO\n");
			break;

		case MPEG4VENC_ERR_PIXELRANGE:
			printf("MPEG4VENC_ERR_PIXELRANGE\n");
			break;

		case MPEG4VENC_ERR_RESETHDVICPEVERYFRAME:
			printf("MPEG4VENC_ERR_RESETHDVICPEVERYFRAME\n");
			break;

		case MPEG4VENC_ERR_METYPE:
			printf("MPEG4VENC_ERR_METYPE\n");
			break;

		case MPEG4VENC_ERR_UNRESTRICTEDMV:
			printf("MPEG4VENC_ERR_UNRESTRICTEDMV\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL:
			printf("MPEG4VENC_ERR_IVIDENC1_PROCESS_ARGS_NULL\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_INARGS_SIZE:
			printf("MPEG4VENC_ERR_IVIDENC1_INARGS_SIZE\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_OUTARGS_SIZE:
			printf("MPEG4VENC_ERR_IVIDENC1_OUTARGS_SIZE\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_INARGS_INPUTID:
			printf("MPEG4VENC_ERR_IVIDENC1_INARGS_INPUTID\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG:
			printf("MPEG4VENC_ERR_IVIDENC1_INARGS_TOPFIELDFIRSTFLAG\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_INBUFS:
			printf("MPEG4VENC_ERR_IVIDENC1_INBUFS\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_INBUFS_BUFDESC:
			printf("MPEG4VENC_ERR_IVIDENC1_INBUFS_BUFDESC\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_OUTBUFS:
			printf("MPEG4VENC_ERR_IVIDENC1_OUTBUFS\n");
			break;

		case MPEG4VENC_ERR_IVIDENC1_OUTBUFS_NULL:
			printf("MPEG4VENC_ERR_IVIDENC1_OUTBUFS_NULL\n");
			break;

		case MPEG4VENC_ERR_CODEC_INACTIVE:
			printf("MPEG4VENC_ERR_CODEC_INACTIVE\n");
			break;

		case MPEG4VENC_ERR_INV_CODEC_ID:
			printf("MPEG4VENC_ERR_INV_CODEC_ID\n");
			break;

		case MPEG4VENC_ERR_CODEC_NOT_INITIALIZED:
			printf("MPEG4VENC_ERR_CODEC_NOT_INITIALIZED\n");
			break;

		case MPEG4VENC_ERR_INPUTWIDTH_NON_MULT_OF_2:
			printf("MPEG4VENC_ERR_INPUTWIDTH_NON_MULT_OF_2\n");
			break;

		case MPEG4VENC_ERR_INPUTHEIGHT_NON_MULT_OF_2:
			printf("MPEG4VENC_ERR_INPUTHEIGHT_NON_MULT_OF_2\n");
			break;

		case MPEG4VENC_ERR_INPUTWIDTHHEIGHT:
			printf("MPEG4VENC_ERR_INPUTWIDTHHEIGHT\n");
			break;

		case MPEG4VENC_ERR_CAPTUREWIDTH:
			printf("MPEG4VENC_ERR_CAPTUREWIDTH\n");
			break;

		case MPEG4VENC_ERR_GENERATEHEADER:
			printf("MPEG4VENC_ERR_GENERATEHEADER\n");
			break;

		case MPEG4VENC_ERR_INTERFRAMEINTERVAL:
			printf("MPEG4VENC_ERR_INTERFRAMEINTERVAL\n");
			break;

		case MPEG4VENC_ERR_BITRATE:
			printf("MPEG4VENC_ERR_BITRATE\n");
			break;

		case MPEG4VENC_ERR_REFFRAMERATE_MISMATCH:
			printf("MPEG4VENC_ERR_REFFRAMERATE_MISMATCH\n");
			break;

		case MPEG4VENC_ERR_TARGETFRAMERATE:
			printf("MPEG4VENC_ERR_TARGETFRAMERATE\n");
			break;

		case MPEG4VENC_ERR_INTRAFRAMEINTERVAL:
			printf("MPEG4VENC_ERR_INTRAFRAMEINTERVAL\n");
			break;

		case MPEG4VENC_ERR_FORCEFRAME:
			printf("MPEG4VENC_ERR_FORCEFRAME\n");
			break;

		case MPEG4VENC_ERR_GOBHEADER:
			printf("MPEG4VENC_ERR_GOBHEADER\n");
			break;

		case MPEG4VENC_ERR_TIMESCALE:
			printf("MPEG4VENC_ERR_TIMESCALE\n");
			break;

		case MPEG4VENC_ERR_INTERFRAMEQP:
			printf("MPEG4VENC_ERR_INTERFRAMEQP_MPEG4\n");
			break;

		case MPEG4VENC_ERR_INTRAFRAMEQP:
			printf("MPEG4VENC_ERR_INTRAFRAMEQP_MPEG4\n");
			break;

		case MPEG4VENC_ERR_INITQ:
			printf("MPEG4VENC_ERR_INITQ_MPEG4\n");
			break;

		case MPEG4VENC_ERR_QPMAX:
			printf("MPEG4VENC_ERR_QPMAX\n");
			break;

		case MPEG4VENC_ERR_QPMIN:
			printf("MPEG4VENC_ERR_QPMIN\n");
			break;

		case MPEG4VENC_ERR_PACKETSIZE:
			printf("MPEG4VENC_ERR_PACKETSIZE\n");
			break;

		case MPEG4VENC_ERR_AIRRATE:
			printf("MPEG4VENC_ERR_AIRRATE\n");
			break;

		case MPEG4VENC_ERR_4MVMODE:
			printf("MPEG4VENC_ERR_4MVMODE\n");
			break;

		case MPEG4VENC_ERR_HECMODE:
			printf("MPEG4VENC_ERR_HECMODE\n");
			break;

		case MPEG4VENC_ERR_RCMETHOD:
			printf("MPEG4VENC_ERR_RCMETHOD\n");
			break;

		case MPEG4VENC_ERR_MAXDELAY:
			printf("MPEG4VENC_ERR_MAXDELAY\n");
			break;

		case MPEG4VENC_ERR_PERCEPTUALRC:
			printf("MPEG4VENC_ERR_PERCEPTUALRC\n");
			break;

		case MPEG4VENC_ERR_INVALID_H263_LEVEL:
			printf("MPEG4VENC_ERR_INVALID_H263_LEVEL\n");
			break;

		case MPEG4VENC_ERR_SP_LEVEL_RESOLUTION:
			printf("MPEG4VENC_ERR_SP_LEVEL_RESOLUTION\n");
			printf("Resolution not supported for this level\n");
			break;

		case MPEG4VENC_ERR_SP_LEVEL_TARGETFRAMERATE:
			printf("MPEG4VENC_ERR_SP_LEVEL_TARGETFRAMERATE\n");
			printf("Target Framerate not supported for this level\n");
			break;

		case MPEG4VENC_ERR_SP_LEVEL_TARGETBITRATE:
			printf("MPEG4VENC_ERR_SP_LEVEL_TARGETBITRATE\n");
			printf("Target Bitrate not supported for this level\n");
			break;

		case MPEG4VENC_ERR_SP_LEVEL_MAX_MBS_MAX_BITRATE:
			printf("MPEG4VENC_ERR_SP_LEVEL_MAX_MBS_MAX_BITRATE\n");
			printf("MBS per frame or Bitrate not supported\n");
			break;

		case MPEG4VENC_ERR_SP_LEVEL_MAX_ENCODED_MBS:
			printf("MPEG4VENC_ERR_SP_LEVEL_MAX_ENCODED_MBS\n");
			printf("Encoded MBS per frame not supported\n");
			break;

		case MPEG4VENC_ERR_MV_SAD_OUT_FLAG:
			printf("MPEG4VENC_ERR_MV_SAD_OUT_FLAG\n");
			break;

		case MPEG4VENC_WARN_SP_LEVEL_DP:
			printf("MPEG4VENC_WARN_SP_LEVEL_DP\n");
			printf("Invalid packet size for this level\n");
			break;

		default:
			printf("Unknown Error code\n");
	}
	return 0;
}


/*---------------------------------------------------------------------------*/
/*  Function used to test the error robustness for process call's arguments  */
/*---------------------------------------------------------------------------*/

#ifdef ENABLE_CORRUPTION_TESTS
static XDAS_Int32 proc_call_args_corruption_tests(MP4VENC_Handle     handle,
									  IVIDEO1_BufDescIn *inbufdesc ,
									  XDM_BufDesc       *outbufdesc,
									  MP4VENC_InArgs    *inargs,
									  MP4VENC_OutArgs   *outargs)
{
	XDAS_Int32 test_no = 0;
	IVIDEO1_BufDescIn inbufdesc_local;
	XDM_BufDesc       outbufdesc_local;
	MP4VENC_InArgs    inargs_local;
	MP4VENC_OutArgs   outargs_local;
	XDAS_Int32 iErrorFlag;
	XDAS_Int32 globalStatus = 0;


	/* Create a local copy of the parameters */
	memcpy(&inbufdesc_local,inbufdesc,sizeof(IVIDEO1_BufDescIn));
	memcpy(&outbufdesc_local,outbufdesc,sizeof(XDM_BufDesc));
	memcpy(&inargs_local,inargs,sizeof(MP4VENC_InArgs));
	memcpy(&outargs_local,outargs,sizeof(MP4VENC_OutArgs));

	/* IVIDEO1_BufDescIn Corruption tests */
	{
		printf("\n####### Starting In Bufs corruption tests #######\n");

		inbufdesc_local.numBufs = 1;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.numBufs = 3;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.frameWidth = inbufdesc->frameWidth - 20;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.frameWidth = inbufdesc->frameWidth + 20;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.frameHeight = inbufdesc->frameHeight - 20;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.frameHeight = inbufdesc->frameHeight + 20;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.framePitch = inbufdesc->framePitch - 2000;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.framePitch = inbufdesc->framePitch + 2000;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.bufDesc[0].buf = NULL;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.bufDesc[1].buf = NULL;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.bufDesc[0].bufSize = 0;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inbufdesc_local.bufDesc[1].bufSize = 0;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);
	}

	/* IVIDENC1_InArgs Corruption tests */

	{
		printf("\n####### Starting In Args corruption tests #######\n");

		inargs_local.videncInArgs.size = 0;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inargs_local.videncInArgs.inputID = 0;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

		inargs_local.videncInArgs.topFieldFirstFlag  = 1;
		CORRUPTION_TEST_MACRO(test_no,iErrorFlag,handle,inbufdesc_local,outbufdesc_local,inargs_local,outargs_local,globalStatus);

	}
	return(globalStatus);
}

#endif

/*!
 *! Revision History
 *! ================
 *!
 *! 02-Apr-2007   RSV: File name and other chages to meet coding guidelines
 *!                    requirements.
 *!
 *! 18-Jan-2006   Anirban Basu: Create file and added initial code.
 */
