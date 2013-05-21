
/** ============================================================================
 *  @file   vc1vdec_ti_arm926testapp.c
 *
 *  @path   $(PROJDIR)\src
 *
 *  @desc   This is the top level client file that drives the VC1(Main Profile)
 *          Video Encoder Call using XDM Interface
 *  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===========================================================================*/

/* ---------------------compilation control switches -------------------------*/
/*
 * Below flag is used for debug purpose only when this is defined user can give
 * frame number which he need to dump. if frame number is not given it will dump
 * every frame. User has to put break point and set this frame number
 */

#define FILEDUMP_CONTROL
/*******************************************************************************
*                  INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>

//#include <tistdtypes.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/sdo/fc/rman/rman.h>
#if 1
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>


/*----------------------program files ----------------------------------------*/
/*------------------- VC1 Interface header files -----------------------------*/

#include "vc1vdec_ti.h"
#include "vc1vdec_ti_testappdec.h"
#include "buffermanager.h"
#include "hdvicp_framework.h"
#include "testapp_arm926intc.h"
#include "ivc1vdec.h"

/*******************************************************************************
*          EXTERNAL REFERENCES NOTE : only use if not found in header file
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/
/*
 * If the code is built for dual processor "Profile data" is used for storing
 * the cycle count and to know the status of "profilepollflag" is used
 */
#ifndef SINGLE_PROCESSOR
#ifdef _PROFILE
extern volatile XDAS_UInt32 *ProfileData;
extern volatile XDAS_UInt32 *ProfilePollFlag;
#endif
XDAS_UInt32 VC1VDEC_TI_Debug_StdDMAStart = 0;
#endif
/*-----------------------function prototypes ---------------------------------*/
/*******************************************************************************
*            PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*
 * Input buffer allocation
 */

XDAS_Int8 *inputData;

/*-----------------------data declarations -----------------------------------*/
/*
 * When profile is on
 * Timer1 - is used to store cycle count for stream parsing upto MB level
 * Timer2 - is used to store cycle count for MB level processing ARM968
 * Timer3 - is used to store cycle count for Miss tasks like Buffer
 *          management and frame padding
 */
#ifdef _PROFILE_FRAME
XDAS_UInt32             Timer1, Timer2, Timer3,TotalTime;
Float             fps;
#endif

#define PROF_LINUX_926  0



#if PROF_LINUX_926
#include <sys/time.h>
#endif
#if PROF_LINUX_926
XDAS_UInt32 time_before_process_926, time_after_process_926;
struct timeval decoder_time_926;
XDAS_UInt32 cycles_cum_926=0, frame_cnt_926 = 0;
extern XDAS_UInt32 time_before_process, time_after_process;
extern  XDAS_UInt32 cycles_cum_1, frame_cnt_1;
#endif

//XDAS_Int8               inputData[INPUT_BUFFER_SIZE];

/*
 * Input Buffer Management specific variables
 */
XDAS_UInt32 bytesConsumed;
XDAS_UInt32 reachedEndOfFile;
XDAS_UInt32 firstFrameInStream;
XDAS_UInt32 isAdvanced;
XDAS_Int32 partial_vde_bytes;
XDAS_Int32 validBytes;
XDAS_Int8 endofFile;
XDAS_UInt32             fileOffset;
XDAS_UInt8 ParseRcvInLib;
XDAS_UInt32 g_frame_num;
XDAS_UInt8 g_decodeHeader;
XDAS_Int8 g_decodeHeaderRetVal;
XDAS_Int8 g_processRetVal;
XDAS_UInt32 g_streamType;
XDAS_UInt32 g_seq_hdr_corrupt;
/*
 * Output buffer allocation
 * OUTPUT_BUFFER_SIZE - No of bytes to hold D1 frame
 * DISPLAY_YUV_SIZE - No bytes to hold only Chroma buffers for deinterleaving
 */
XDAS_Int8  outputData[OUTPUT_BUFFER_SIZE];
XDAS_UInt8               Chroma_seperate[DISPLAY_YUV_SIZE];
/*
 * Display buffer
 * This buffer is used to do post process the decoded picture.
 * Post processsing includes saparating the Cb and Cr pixels, Range scaling
 * also Resolution upsampling and down sampling
 */
XDAS_UInt8  Luma_separate[MAX_LUMA_BUFFER_SIZE];
XDAS_UInt8  Cb_seperate[MAX_CROMA_BUFFER_SIZE];
XDAS_UInt8  Cr_seperate[MAX_CROMA_BUFFER_SIZE];
/*
 * Ref Buffer allocation
 */
XDAS_Int8               refData[OUTPUT_BUFFER_SIZE];
/*
 * To reduce file oparations we will read entire ref CRC file into ref buffer
 * and below variable is used as pointer .
 */
XDAS_Int32          *RefCrcBufPtr;
/*
 * Codec specific params and dynamic params
 */
IVC1VDEC_Params         params;
IVC1VDEC_DynamicParams  dynamicParams;
/*
 * Number of frames to decode specified by testparams.cfg file
 */
XDAS_UInt32             framesToDecode;
/*
 * ActualNumberof frames in the stream
 */
XDAS_UInt32             Actual_No_Fr_decode;
/*
 * Token Map array for inputs from testparams.cfg file.
 */

extern IRES_Fxns VC1VDEC_TI_IRES;

sTokenMapping sTokenMap[] =
{
  {"ImageWidth",     &params.viddecParams.maxWidth},
  {"ImageHeight",    &params.viddecParams.maxHeight},
  {"ChromaFormat",   &params.viddecParams.forceChromaFormat},
  {"FramesToDecode", &framesToDecode},
  {NULL,             NULL}
};

/*
 * :KLUDGE: Below variable is not required just for debugging
 */
#ifndef SINGLE_PROCESSOR
XDAS_UInt32 VC1VDEC_TI_Debug_StdDMAStart;
#else
extern XDAS_UInt32 VC1VDEC_TI_Debug_StdDMAStart;
#endif

//#ifdef NO_RCV_HEADER_PARSING
static XDAS_UInt8     RCVIsV2Format;
/* We allocate a Max of 256 bytes for sequence header */
XDAS_UInt8 temp_Sequnce_Header[256];
XDAS_UInt8 temp_struct_b[256];
XDAS_UInt8 time_stamp[10];

//#endif
/*-----------------------function prototypes ---------------------------------*/
/*******************************************************************************
*              PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

/*-----------------------function prototypes ---------------------------------*/

/*-----------------------macros ----------------------------------------------*/

#define LOG_FILE_PATH "../../Test/TestVecs/Config/log.txt"
/* x clipped to 0 - 255 */
#define CLIP(x)     ((unsigned char)((x) < 0 ? 0 : ((x) > 255 ? 255 : (x))))

/* Number of input buffers is set to one.*/
#define INPUT_NUMBUFS 1

/* Number of output buffers is always set to two. One bufffer is for
 * Luma component and the other buffer for chroma component in
 * packed and interleaved format.
 */
#define OUTPUT_NUMBUFS 2
//#define DECODE_HEADER_MODE 1

/* For D1 PAL frame luma width is 720 pixels. Including left and right padding
 * and 32 bit alignment, the buffer requirement is (800) pixels per line.
 * Similarly luma height is 576. Including top and bottom padding, it is (640).
 * So the luma buffer size required is 800 * 640 = 512000.
 *
 * Since chroma buffers are interleaved, Chroma width is also 720. Including 32
 * byte alignment and padding, it is also (800).
 * Chroma height is half of luma height i.e., 576 / 2 = (288) lines. Including
 * top and bottom padding it is (352).
 *  the chroma buffer size required is (800 * 352) = 281600.
 *
 * For 4:2:0 sampling, in the absence of padding, if the luma buffer size
 * required is n x n, chroma buffer size required is exactly n/2 * n/2 for Cb
 * and Cr each, making total chroma buffer size half of the luma buffer size.
 * Thus the buffer manager allocates memory for luma and chroma buffers by
 * equally dividing the available buffer size into 3 parts and allocating
 * 2 parts for luma and 1 part for chroma.
 * But because of padding, we can see that the chroma buffer size required
 * is actually more than half the luma buffer size. Therefore we have to set
 * the total buffer size required as (3 * chroma buffer size required) so that
 * the buffer manager allocates enough size to the chroma buffer.
 *
 * Thus, the buffer size required for one buffer = 3 * 281600 = 844800.
 * Since we need 4 buffers, the total buffer size required = 4 * 844800.

 * Since WVGA stream also needs same Processing speed as D1 PAL we support
 * The memory for WVGA is calculated above and comes as 846336 bytes
 */
#define TOTAL_BUFSIZE (3428352 * 4)
#define _ENABLE_IRES_EDMA3


    CMEM_AllocParams memParams;

/* ------------------------Global variables ----------------------------------*/

/* =============================================================================
 *  @func  main
 *
 *  @brief Sample main program implementation which uses xDM v1.0 VC1
 *         decoder's APIs to create a decoder instance and decode multiple
 *         input files. It supports dumping of output decoded YUV data in 4:2:0
 *         format or comparision fo decoded raw data with reference data.
 *         Uses single instance of the decoder and uses only base params for
 *         all input classes.
 *
 *         Uses buffer manager for XDM v1.0 compatible buffer management and
 *         uses utility functions for reading encoded bit-stream,
 *         Separating CbCr components,
 *         Comparing output data with reference data &
 *         Dumping raw YUV data into a file in binary format.
 *
 *  @param  Null
 *
 *  @return XDAS_Int32 XDM_EOK, on success
 *
 * =============================================================================
 */
int main ()
{
/*
 * File pointers for Configuration file, Input file, paramsfile
 */
   FILE                 *fConfigFile,
                        *ftestFile,
                        *flogFile,
                        *fparamsFile;
/*
 * Arrays to store configuration parameters
 */
   xdc_Char            line[STRING_SIZE],
                        inFile[STRING_SIZE],
                        logFile[STRING_SIZE],
                        testFile[STRING_SIZE];
   xdc_Char            paramsFile[STRING_SIZE];
   XDAS_Int32           testCompliance;
/*
 * Path for Configuration file
 */
#ifndef ON_LINUX
   xdc_Char            *fname =
                        "..\\..\\..\\Test\\TestVecs\\Config\\Testvecs.cfg";
#else
   xdc_Char *fname = "../../test/testvecs/config/testvecs_linux.cfg";
#endif
/*
 * extended Class Structures
 */
   IVC1VDEC_Status      status;
   IVC1VDEC_InArgs      inArgs;
   IVC1VDEC_OutArgs     outArgs;

   IRES_Status iresStatus;
/*
 * Algorithm specific handle
 */
   IALG_Handle          handle;
/*
 * ires related data declarations
 */
   HDVICP_Obj           hdvicpObj;
/*
 * Input/Output XDM 1.0 Buffer Descriptors
 */
   XDM1_BufDesc         inputBufDesc;
   XDM_BufDesc          outputBufDesc;
/*
 * buffer element handler to hold Buffer information
 */
   BUFFMGR_buffEleHandle buffEle;
/*
 * Other variables
 * frameCount - The frame number to be displayed
 * retVal - Holds error status
 * testVal - Holds status after comparing output
 * countConfigSet - used to count the no of streams decoded
 */
   XDAS_Int32           frameCount,
                        retVal,
                        decode_frameCount,
                        testVal,
                        countConfigSet;
   XDAS_Int32           inFlushModeFlag = 0;
   XDAS_Int8 versionBuf[256];
#ifdef FILEDUMP_CONTROL
/*
 * KLUDGE: below variable is used for debug only
 * Make this flag always on such that file is dumped always.but while debugging
 * keep changing this variable for dumping accordingly
 */
   XDAS_Int32           Filedump = 0;
#endif


#ifdef ON_LINUX
    LockMP_init();
    SemMP_init();
    Memory_init();
#endif



    strcpy(logFile, LOG_FILE_PATH);
    flogFile = fopen(logFile,"w");
#ifdef ENABLE_CACHE
    ARM926_Set_MMU_Base();
    ARM926_Set_Domains();
    ARM926_Enable_MMU();
    ARM926_Icache_Enable();
    ARM926_Flush_Icache();
    ARM926_Cache_Set_RoundRobin();
    //ARM926_Dcache_Enable();
    //ARM926_CleanFlush_Dcache();
#else
    //ARM926_Icache_Disable();
    //ARM926_Dcache_Disable();
#endif

/*----------------------------------------------------------------------------*/
/* Clear polling bit of ARM968                                                */
/*----------------------------------------------------------------------------*/


/*
 * Reset countConfigSet value to 1
 */
   countConfigSet = 1;
#ifdef DM510_IPC_INTC_ENABLE
/*----------------------------------------------------------------------------*/
/* Call the functions to enable ARM926 FIQ and do some basic setup to AINTC   */
/* to accept KLD INTC (arm968) interupt in FIQ pin of Arm926                  */
/*----------------------------------------------------------------------------*/
#ifndef ON_LINUX
     ARM926_enable_FIQ();  /* SWI call to enable interrupts */
     ARM926_INTC_init();   /* Init AINTC                                     */
#endif
#endif


    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_CACHED;
    memParams.alignment=256;



    /* Initialization and allocation */
    CMEM_init();
    inputData = CMEM_alloc(INPUT_BUFFER_SIZE,&memParams);
    //memset(inputData,0x0,INPUT_BUFFER_SIZE);

/*--------------------------------------------------------------------------- */
/*  Start algorithm init here                                                 */
/*--------------------------------------------------------------------------- */
/*
 * Open config file and read params file name for Create parameter
 * Note: here we are considering only first stream config parameters
 */
    fConfigFile = fopen(fname,"r");
    if (!fConfigFile)
    {
        printf("Couldn't open parameter file %s",fname);
        return XDM_EFAIL;
    }

    //GT_init();
    //GT_create(&someGTMask, "ti.sdo.fc.rman.examples.dummyEdma3");
    //GT_set("*" "=01234567");


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

       /*{
            IRESMAN_VicpParams configParams;

            Supply initialization information for the RESMAN while registering

            configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
            configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
            configParams.baseConfig.size = sizeof(IRESMAN_VicpParams);

            Register the VICP protocolresource manager with the
             generic resource manager
            iresStatus = (IRES_Status)RMAN_register(&IRESMAN_VICP2,
                                                    (IRESMAN_Params *)&configParams);

            if (IRES_OK != iresStatus) {
                printf("VICP Protocol Registration Failed \n");
                return -1;
        }
        }*/


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

/*
 * Read Compliance Checking parameter
 */
    if(fgets(line,254,fConfigFile))
    {
        sscanf(line,"%d",&testCompliance);
    }
    else
    {
        exit(0);
    }
/*
 * Read Parameters file name
 */
    if(fgets(line,254,fConfigFile))
    {
        sscanf(line,"%s",paramsFile);
    }
    else
    {
        exit(0);
    }
    fclose(fConfigFile);
/*
 * Read parameters file
 */
/*
 * Open Parameters file
 */
    fparamsFile = fopen (paramsFile, "rb");
    if (!fparamsFile)
    {
        printf("\nCouldn't open Parameters file...   %s\n ",paramsFile);
        printf("Exiting for this configuration...\n");
        exit(0);
    }
/*
 * Read the parameter file to update decode options
 */
    if(readparamfile(fparamsFile) < 0)
    {
        printf("\nSyntax Error in %s\n ",paramsFile);
        printf("Exiting for this configuration...\n");
        exit(0);
    }
/*
 * Close Parameters File
 */
    //fclose(fparamsFile);
/*
 * Initialization of parameters needed for Algorithm Instance create
 */
    TestApp_SetInitParams(&params.viddecParams);
/*
 * Setting the sizes of Base Class Objects
 */
    params.viddecParams.size     = sizeof(IVC1VDEC_Params);
    status.viddecStatus.size     = sizeof(IVC1VDEC_Status);
    dynamicParams.viddecDynamicParams.size
                                = sizeof(IVC1VDEC_DynamicParams);
    inArgs.viddecInArgs.size     = sizeof(IVC1VDEC_InArgs);
    outArgs.viddecOutArgs.size   = sizeof(IVC1VDEC_OutArgs);

/*
 * Make display delay to default value
 */
    params.display_delay                        = 1;

/*
 * Set XDM Chroma format to 256
 */
    params.viddecParams.forceChromaFormat       = 9;
    params.rcvParseInLib						= 1;
    params.streamType							= 0;

    ParseRcvInLib = params.rcvParseInLib;
    g_streamType = params.streamType;
    g_seq_hdr_corrupt = 0;






/* HDVICP calls enable non-blocking implementation on the host processor
 * in a OS scenario with support for multi-thread/task creations.
 * hdvicpObj which will be part of the decoder instance. All future calls
 * to HDVICP module made by the algorithm will contain this as the handle.
 * HDVICP module initialises it suitably to enable context identification
 * in future calls.
 */
    //HDVICP_initHandle(&hdvicpObj);
    params.hdvicpHandle = (void*) &hdvicpObj;
    printf("\nCreating Algorithm Instance...\n");
    handle = (IALG_Handle)
              VC1VDEC_create((IVC1VDEC_Fxns *) &VC1VDEC_TI_IVC1VDEC,
                             (IVC1VDEC_Params *) &params);
    if (handle == NULL)
    {
        printf( "\nFailed to Create Instance... Exiting for this \
                                                          configuration..");
        exit(0);
    }
    printf("\nAlgorithm Instance Creation Done...\n");

    #ifdef _ENABLE_IRES_EDMA3
    {
     int temp;
     temp = RMAN_assignResources((IALG_Handle)handle,
                                            &VC1VDEC_TI_IRES, /* IRES_Fxns* */
                                            1 /* scratchId */);
        /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
        if (IRES_OK != temp) {
          printf( "\nFailed in assigning resources \
                     Exiting for this configuration..");
          goto EndOfFile;
        }
    }
   #endif

    #ifdef _ENABLE_IRES_EDMA3
    {
     int temp;
     temp = RMAN_activateAllResources((IALG_Handle)handle,
                                            &VC1VDEC_TI_IRES, /* IRES_Fxns* */
                                            1 /* scratchId */);
        /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
        if (IRES_OK != temp) {
          printf( "\nFailed in activate resources \
                     Exiting for this configuration..");
          goto EndOfFile;
        }
    }
   #endif

/*----------------------------------------------------------------------------*/
/*   Read the Config File until it reaches the end of file                    */
/*----------------------------------------------------------------------------*/
/*
 * Open Test Config File
 */
  fConfigFile = fopen(fname,"r");
  if (!fConfigFile)
  {
    printf("Couldn't open parameter file %s",fname);
    return XDM_EFAIL;
  }
  while(!feof(fConfigFile))
  {

/*----------------------------------------------------------------------------*/
/* Initialise the buffer manager with sufficient buffer size for output       */
/* and reference frames the value specified here is dependent on the          */
/* profile and level supported                                                */
/* Refer VC1 standard spec for Main profile Medium level                      */
/*----------------------------------------------------------------------------*/
    BUFFMGR_Init(TOTAL_BUFSIZE);
    fflush(flogFile);

/*
 * Read Compliance Checking parameter
 */
    if(fgets(line,254,fConfigFile))
    {
      sscanf(line,"%d",&testCompliance);
    }
    else
    {
      break ;
    }
/*
 * Read Parameters file name
 */
    if(fgets(line,254,fConfigFile))
    {
      sscanf(line,"%s",paramsFile);
    }
    else
    {
      break ;
    }
/*
 * Read Input file name
 */
    if(fgets(line,550,fConfigFile))
    {
      sscanf(line,"%s",inFile);
    }
    else
    {
      break ;
    }
/*
 * Read Output/Reference file name
 */
    if(fgets(line,550,fConfigFile))
    {
      sscanf(line,"%s",testFile);
    }
    else
    {
      break ;
    }
    printf("\n*******************************************");
    printf("\nRead Configuration Set %d",countConfigSet);
    printf("\n*******************************************");
    printf("\nDecoding : %s \n",inFile);
    countConfigSet++;
    if(testCompliance)
    {
      printf("\nRunning in Compliance Mode\n");
    }
    else
    {
      printf("\nRunning in Output Dump Mode\n");
    }
/*
 * Open output/reference file
 */
    if(testCompliance)
    {
      ftestFile = fopen (testFile, "rb");

      if( !ftestFile || !flogFile)
      {
        printf("Couldn't open Test File... %s\n",ftestFile);
        printf("Exiting for this configuration...\n" );
        goto EndOfFile;
      }
      fprintf(flogFile,"\n*******************************************");
      fprintf(flogFile,"\nRead Configuration Set %d",(countConfigSet-1));
      fprintf(flogFile,"\n*******************************************");
      fprintf(flogFile,"\nDecoding : %s \n",inFile);
      RefCrcBufPtr = (XDAS_Int32 *)refData;
/*
 * Read the entire file and it is assumed that max size of CRC file as 50K
 */
      fread (refData, 1, REF_BUFFER_SIZE, ftestFile);

    }
    else
    {
      ftestFile = fopen (testFile, "wb");
      if( !ftestFile)
      {
        printf("Couldn't open Test File... %s",ftestFile);
        printf("\n Exiting for this configuration..." );
        goto EndOfFile;
      }
    }
/*----------------------------------------------------------------------------*/
/* Init all the Buffer IDs to 0                                                */
/* Here VC1 decoder can lock max of 3 buffers so init only required buffers in*/
/* that array                                                                 */
/*----------------------------------------------------------------------------*/
       outArgs.viddecOutArgs.freeBufID[0]         = 0;
       outArgs.viddecOutArgs.freeBufID[1]         = 0;
       outArgs.viddecOutArgs.freeBufID[2]         = 0;
       outArgs.viddecOutArgs.outputID[0]          = 0;
       outArgs.viddecOutArgs.outputID[1]          = 0;
       outArgs.viddecOutArgs.outputID[2]          = 0;
       inArgs.viddecInArgs.inputID                = 0;
/*
 * Initializing Variables
 */
        frameCount                   = 0;
        bytesConsumed                = 0;
        reachedEndOfFile             = 0;
        firstFrameInStream           = 1;
        endofFile                    = 0;
        fileOffset                   = 0;
        validBytes                   = 0;
        decode_frameCount            = 0;
        inFlushModeFlag              = 0;
        Actual_No_Fr_decode          = 0;

        status.viddecStatus.extendedError = 0;

/* Get Buffer information                                              */
/*
 * Get Buffer requirements for VC1 decode by calling control function with
 * GETBUFINFO Command
 * At this point decoder has not decoded at least one frame so it has to use
 * dynamic parameters support and update the status stucture for buffer
 * requirements. But as of now dynamic params support is not added. Decoder
 * will update default values i.e 0 for output buffers and input buffers
 * with standard values i.e Number of buff is 1. and size is
 * BITSTREAM_BUFFER_SIZE_EXT
 */

    status.viddecStatus.size                  = sizeof(IVIDDEC2_Status);
	status.viddecStatus.data.buf = versionBuf;
	status.viddecStatus.data.bufSize = sizeof(versionBuf);

	 retVal = VC1VDEC_control((VC1VDEC_Handle)handle, XDM_GETVERSION,
					(IVC1VDEC_DynamicParams *)&dynamicParams,
					(IVC1VDEC_Status *)&status);


	printf("\nLibrary Version: %s\n", status.viddecStatus.data.buf);


        retVal = VC1VDEC_control((VC1VDEC_Handle)handle, XDM_GETBUFINFO,
                       (IVC1VDEC_DynamicParams *)&dynamicParams,
                       (IVC1VDEC_Status *)&status);
        if(retVal == XDM_EFAIL)
        {
            goto EndOfFile; /* Error Condition: Application may want to break off         */
        }
/*
 * Update the Input buffer discripter here we can update only size
 * and number of buffers required
 */
        inputBufDesc.numBufs        =
                                  status.viddecStatus.bufInfo.minNumInBufs ;
        inputBufDesc.descs[0].bufSize =
                                  status.viddecStatus.bufInfo.minInBufSize[0];


/*
 * Set Dynamic params
 * :NOTE: This sets the decoder_header only mode =1
 */


			TestApp_SetDynamicParams((IVIDDEC2_DynamicParams *)&dynamicParams);

			dynamicParams.reset_HDVICP_every_frame = 0;
#ifdef DECODE_HEADER_MODE
/*
 * Set The Dynamic parameters by updating dynamic params structure
 */
			dynamicParams.viddecDynamicParams.decodeHeader = 1;
			g_decodeHeader = 1;
#else
			dynamicParams.viddecDynamicParams.decodeHeader = 0;
			g_decodeHeader = 0;
#endif

            retVal = VC1VDEC_control((VC1VDEC_Handle)handle, XDM_SETPARAMS,
                            (IVC1VDEC_DynamicParams *)&dynamicParams,
                            (IVC1VDEC_Status *)&status);
            if(retVal == XDM_EFAIL)
            {
                goto EndOfFile; /* Error Condition: Application may want to break off         */
            }

/*
 * Do while loop for the decode call
 * Loop Until the specified frames in params file or till end of stream
 * decoded and displayed.
 */
        do
        {
/*
 * Read the bit stream in chunks of Input buffer size until end of the stream
 * If there is no more data to read from the input file, below function
 * will just update the Valid bytes.
 */
#ifndef NO_RCV_HEADER_PARSING
             validBytes = TestApp_ReadByteStream(inFile);
#else
/*
 * No Need to parse the input file in flush mode
 */
             if(!inFlushModeFlag)
             {
                validBytes = TestApp_ReadByteStream(inFile);
             }
#endif
             if(validBytes == -1)
             {
                goto EndOfFile; /* Error Condition: Application may want to break off         */
             }

/*
 * Setting of input arguments and input buffer descriptor for Input data pointer
 */
             inArgs.viddecInArgs.numBytes             = validBytes;
#ifndef NO_RCV_HEADER_PARSING
             inputBufDesc.descs[0].buf   = (XDAS_Int8 *)((XDAS_Int32)inputData +
                                           bytesConsumed);
#else
    if(isAdvanced)
             inputBufDesc.descs[0].buf   = (XDAS_Int8 *)inputData + bytesConsumed;
    else
             inputBufDesc.descs[0].buf   = (XDAS_Int8 *)inputData;
#endif
/* Get output buffer for decoder.
 * NOTE: if no frames are decoded till now Buffer manager will treat default
 * buffer size (Entire buffer) as single buffer and divides into Luma Croma
 * buffers and returns the updated structure.
 * Decoder has to use what ever needed.
 */
            buffEle = BUFFMGR_GetFreeBuffer();

/* Fill up the output buffer values and pointers
 * Output is always in YUV 4:2:0
 * packed chroma format.
 */
            outputBufDesc.numBufs = OUTPUT_NUMBUFS;
            outputBufDesc.bufSizes = (XDAS_Int32 *) buffEle->bufSize;
            outputBufDesc.bufs = (XDAS_Int8 **) buffEle->buf;

            inArgs.viddecInArgs.inputID = buffEle->bufId;

/*
 * KLUDGE:
 * Below code is added just for debugging purpose for a specified frame
 * we will go inside branch where break point is put
 */

#ifdef _PROFILE_FRAME
/*
 * _PROFILE_FRAME macro is used to get number of cycles taken to decode the
 * entire frame in steps of 3
 * Timer 1 - used to get Upto MB Level
 * Timer 2 - Used to get MB level
 * Timer 3 - Used to get Post MB level genarally decode end which has
 *           Vertical padding etc.
 * This Macro can Enabled/disabled in Build options.
 */
         printf("Dec St Fr No: %d\n",decode_frameCount);
         fprintf(flogFile,"Dec St Fr No: %d\n",decode_frameCount);
         //  printf("%d\n",decode_frameCount);
     //    Timer1 = Timer2 = Timer3 = 0;
      //   profileInit(0);
      //   profileStart(0);
#endif
      //   printf("Dec St Fr No: %d\n",decode_frameCount);
/*----------------------------------------------------------------------------*/
/* Start the process : To start decoding a frame                              */
/* This will always follow a VC1VDEC_decode_end call                          */
/*----------------------------------------------------------------------------*/
#if PROF_LINUX_926
       time_before_process_926 = gettimeofday(&(decoder_time_926), NULL);
       time_before_process_926 = decoder_time_926.tv_usec;
#endif

         retVal = VC1VDEC_decode((VC1VDEC_Handle)handle,
                                 (XDM1_BufDesc *)&inputBufDesc,
                                 (XDM_BufDesc *)&outputBufDesc,
                                 (IVC1VDEC_InArgs *)&inArgs,
                                 (IVC1VDEC_OutArgs *)&outArgs
                                );
		g_processRetVal = retVal;
        if(g_decodeHeader == 1)
		{
			g_decodeHeaderRetVal = retVal;
		}


/*----------------------------------------------------------------------------*/
/* GetStatus control call enables the user to get the exact picture           */
/* size in terms of pixel height and width                                    */
/*----------------------------------------------------------------------------*/
		retVal = VC1VDEC_control((VC1VDEC_Handle)handle,
						 IVC1VDEC_GETSTATUS,
						 (IVC1VDEC_DynamicParams *)&dynamicParams,
						 (IVC1VDEC_Status *)&status
						);
		if(retVal == XDM_EFAIL)
		{
			goto EndOfFile; /* Error Condition: Application may want to break off         */
		}
		g_seq_hdr_corrupt = (status.viddecStatus.extendedError & (1 << XDM_CORRUPTEDHEADER))
							|| (XDM_EFAIL == g_processRetVal);


		if((outArgs.viddecOutArgs.outBufsInUseFlag == 0) &&
			(g_decodeHeader == 0) && ((decode_frameCount != 0) ||
			 !(status.viddecStatus.extendedError & (1 << XDM_CORRUPTEDHEADER))
			 ))
			 {
				 decode_frameCount++;
			 }
#ifdef DECODE_HEADER_MODE
		if((g_decodeHeader == 1) &&  (g_decodeHeaderRetVal != XDM_EFAIL))
#else
		if(decode_frameCount == 1)
#endif

/* After first frame is decoded - get the actual
 * frame sizes required and use this information to
 * re-distribute buffers. Since the exact picture size
 * is unknown until the first successful process call we
 * cannot complete buffermanage initialisation at one go.
 * Call GETBUFINFO control call on the decoder instance for
 * the very first time after a successful process call is made
 * to know the exact luma and chroma buffer requirements -
 * these buffer requirements would include frame level padding
 * and 32-byte multiple width requirements on the picture frame as
 * well.
 */
			{
/*
 * Get the exact luma and chroma buffer requirements for the
 * given input bit-stream.
 */
                  retVal = VC1VDEC_control((VC1VDEC_Handle)handle, XDM_GETBUFINFO,
                                  (IVC1VDEC_DynamicParams *)&dynamicParams,
                                  (IVC1VDEC_Status *)&status
                                 );
                if(retVal == XDM_EFAIL)
                {
                    goto EndOfFile; /* Error Condition: Application may want to break off         */
                }
/*
 * Use the above exact luma and chroma buffer requirements
 * for the input bit-stream to re-initialise the buffer manager.
 * Refer to buffermanager specific XDM v1.0 intergation doc
 * for more details.
 */
                  BUFFMGR_ReInit(status.viddecStatus.bufInfo.minOutBufSize[0],
                                 status.viddecStatus.bufInfo.minOutBufSize[1]
                                );
             }

#ifdef DECODE_HEADER_MODE

		if((g_decodeHeader == 1) && (g_decodeHeaderRetVal != XDM_EFAIL))
		{


/*
 * Set Dynamic params
 * :NOTE: As off not decoder is not supported dynamic params so the controll
 * function will just returns SUCCESS without updating any thing.
 */
 			 g_decodeHeader = 0;
 			 TestApp_SetDynamicParams((IVIDDEC2_DynamicParams *)&dynamicParams);
             retVal = VC1VDEC_control((VC1VDEC_Handle)handle, XDM_SETPARAMS,
                            (IVC1VDEC_DynamicParams *)&dynamicParams,
                            (IVC1VDEC_Status *)&status);
            if(retVal == XDM_EFAIL)
            {
                goto EndOfFile; /* Error Condition: Application may want to break off         */
            }
		}
#endif



#if PROF_LINUX_926
       time_after_process_926 = gettimeofday(&(decoder_time_926), NULL);
       time_after_process_926 = decoder_time_926.tv_usec;
       if(time_after_process_926 < time_before_process_926)
       {
           time_after_process_926 += 1000000;
       }
       printf("Start 926 :time before = %d\n",time_before_process_926);
       printf("End 926 :time After = %d\n",time_after_process_926);

       cycles_cum_926 += time_after_process_926 - time_before_process_926;
       frame_cnt_926++;
       printf("\nCombined time926n968 = %d;\nframes = %d\t",time_after_process_926 - time_before_process_926, frame_cnt_926);


	   printf("Start 968 :time before = %d\n",time_before_process);
	   printf("End 968 :time After = %d\n",time_after_process);
	   cycles_cum_1 += time_after_process - time_before_process;
       printf("\nDecode Time of 968 = %d\n frames = %d\n",time_after_process - time_before_process, frame_cnt_1);

       {
		   int time_926;

		time_926 = (time_after_process_926 - time_before_process_926) - (time_after_process - time_before_process);
       printf("\nDecode Time of 926 = %d\n frames = %d\n",time_926, frame_cnt_1);
   	   }
#endif
#ifdef _PROFILE_FRAME
           //  Timer3 = profileEnd(0);
           //  TotalTime = (Timer1+Timer3+Timer2);
           //  fps = ((Float)(180000000))/((Float)TotalTime);
           //  if(fps < 30)
            // {
            //    printf("\n %d fps %f\n",decode_frameCount,fps);
            // }
//             printf("Fr No : %3d ARM 926: %9ld,   ARM 968: %9ld,   Total: %9ld\n",decode_frameCount,(Timer1+Timer3),Timer2,(Timer1+Timer3+Timer2));
        //   if(!(decode_frameCount % 20))
         //    {
          //      printf("\n");
           //  }
          //   printf("%d,",decode_frameCount);
#endif

             if(g_processRetVal == XDM_EFAIL && 1 != g_seq_hdr_corrupt)
             {
                printf("\nProcess function returned an Error...  \n");
/*----------------------------------------------------------------------------*/
/* GetStatus control call enables the user to get the exact picture           */
/* size in terms of pixel height and width                                    */
/*----------------------------------------------------------------------------*/
                VC1VDEC_control((VC1VDEC_Handle)handle,
                                 IVC1VDEC_GETSTATUS,
                                 (IVC1VDEC_DynamicParams *)&dynamicParams,
                                 (IVC1VDEC_Status *)&status
                                );
                /* Error Condition: Application may want to break off         */
                goto EndOfFile;
             }




/*
 * Check if the decoder instance is in XDM_FLUSH mode
 */
             if(!inFlushModeFlag)
             {
/*
 * If not then update the variables managing the input encoded
 * bit-stream buffer
 */
/*
 * Check whether extended params are used or not
 */
#ifndef NO_RCV_HEADER_PARSING
                  if(outArgs.viddecOutArgs.bytesConsumed !=
                     outArgs.frameSize)
                  {
                        printf("Frame Size is diff %d, %d\n",
                          outArgs.viddecOutArgs.bytesConsumed,outArgs.frameSize);
                  }
                  if(outArgs.viddecOutArgs.size == sizeof(IVIDDEC2_OutArgs))
                  {
                      bytesConsumed          +=
                                    outArgs.viddecOutArgs.bytesConsumed;
                      validBytes             -=
                                    outArgs.viddecOutArgs.bytesConsumed;
                  }
                  else
                  {
                      bytesConsumed          +=
                                    outArgs.frameSize;
                      validBytes             -=
                                    outArgs.frameSize;
                  }
#else
                  bytesConsumed          +=
                                    outArgs.viddecOutArgs.bytesConsumed;
                  validBytes             -=
                                    outArgs.viddecOutArgs.bytesConsumed;
#endif

                   //decode_frameCount++;
			}

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
                 /*Expanding back pixels before displaying
                   after Range Reduction */
                if(testCompliance)
                {
/*
 * To support Multi resolution and Range reduction application has to scale
 * each pixel with out affecting the Output buffer also frame needs to be
 * upsampled in terms of resolution when it is needed.
 * all the post processing operations are done inside this function.
 */
                    TestApp_PostProcessData(
                                (IVIDDEC2_OutArgs *)&outArgs,
                                 status.viddecStatus.outputHeight,
                                 status.viddecStatus.outputWidth
                              );
/*
 * Compare the output frames with the Reference File
 */
                    testVal = TestApp_CompareOutputData(ftestFile,
                                    status.viddecStatus.outputHeight,
                                    status.viddecStatus.outputWidth);
                    if(testVal != XDM_EOK)
                    {
                         printf("Breaking Due to CRC fail at: %d \n",
                                              decode_frameCount);
                        fprintf(flogFile,"Breaking Due to CRC fail at: %d \n",
                                              decode_frameCount);
                        /* Test Compliance Failed... Breaking...*/
                         goto EndOfFile;
                    }
                    printf("Verified CRC CHECK \n");
                    fprintf(flogFile,"Verified CRC CHECK \n");
                }
                else
                {
/*
 * Write the output frames in the display order
 * display_marker(2nd arg) is i for normal decode calls
 */
/*
 * KLUDEGE: Just for debug only
 */
#ifdef FILEDUMP_CONTROL
                    if((!Filedump) || ((decode_frameCount - 1) >= (Filedump + 1)))
                    {
#endif
/*
 * To support Multi resolution and Range reduction application has to scale
 * each pixel with out affecting the Output buffer also frame needs to be
 * upsampled in terms of resolution when it is needed.
 * all the post processing operations are done inside this function.
 */
                        TestApp_PostProcessData(
                                    (IVIDDEC2_OutArgs *)&outArgs,
                                     status.viddecStatus.outputHeight,
                                     status.viddecStatus.outputWidth
                                  );
/*
 * Compare the output frames with the Reference File
 */
                        TestApp_WriteOutputData(ftestFile,
                            status.viddecStatus.outputHeight,
                            status.viddecStatus.outputWidth);
#ifdef FILEDUMP_CONTROL
                    }
#endif
                }
            }
/*
 * Buffer manager would allocate free buffer elements through
 * BUFFMGR_GetFreeBuffer API. These buffers are used and owned
 * by the algorithm until it explicitly releases them by way of
 * mentioning their buffer Ids in freeBufId array of outArgs
 * parameter. So release buffers needs to be returned back
 * to the buffer manager. It is perfectly possible to have
 * zero or more buffers to be freed by the algorithm in one
 * process call.
 */
            if(outArgs.viddecOutArgs.freeBufID[0])
            {
                BUFFMGR_ReleaseBuffer(
                         (XDAS_UInt32 *)outArgs.viddecOutArgs.freeBufID);
/*
 * Make freebuffer ID to zero such that application will not free wrongly next
 * time it comes here.
 */
                outArgs.viddecOutArgs.freeBufID[0] = 0;
                outArgs.viddecOutArgs.freeBufID[1] = 0;
                outArgs.viddecOutArgs.freeBufID[2] = 0;
            }


            if(inFlushModeFlag)
            {
                  printf("\nBit stream ended or \n");
                  printf("Specified no of frames decoded \n");
/*----------------------------------------------------------------------------*/
/* Code added to support display delay                                        */
/*----------------------------------------------------------------------------*/
                  printf("Flushing out Displayable frames from DPB...\n");
/*
 * If outputId is zero - it either indicates that there are no
 * frames to display at this point of time or bit-stream has
 * been ended - In order to distinguish between these two
 * conditions inFlushModeFlag is used.
 * Infact this condition should not occur since process call
 * is expected to return XDM_EFAIL when decode end is
 * encountered. Please refer to user guide for more details.
 */
                break;
            }
/* ---------------------------------------------------------------------------*/
/* Print the status of the decoder                                            */
/* ---------------------------------------------------------------------------*/
		if(!g_seq_hdr_corrupt)
		{
          //  printf("Frame decoded : %d\n",decode_frameCount);
             printf("Bytes Consumed : %d ,Valid : %d\n",bytesConsumed,
                     validBytes);
             printf("\n");
             //fprintf(flogFile,"Bytes Consumed : %d ,Valid : %d\n\n",bytesConsumed,
             //        validBytes);
		}

/* ---------------------------------------------------------------------------*/
/* Decoder should end decoding of the stream when valid bytes is less than    */
/* 5 or specified no of frames decoded                                        */
/* ---------------------------------------------------------------------------*/


#ifdef NO_RCV_HEADER_PARSING
             if ((((decode_frameCount >=
                 Actual_No_Fr_decode)) &&
                 (inFlushModeFlag != 1)) || (endofFile && !validBytes)
                )
#else
             if (((validBytes < 5) ||
                 (decode_frameCount >=
                 framesToDecode)) &&
                 (inFlushModeFlag != 1)
                )
#endif
            {
/*----------------------------------------------------------------------------*/
/* Call FLUSH command to set the flush mode for decoder                       */
/* This is required to flush out left over displayable frames in DPB          */
/*----------------------------------------------------------------------------*/
                    retVal = VC1VDEC_control((VC1VDEC_Handle)handle,
                                  XDM_FLUSH,
                                  (IVC1VDEC_DynamicParams *)&dynamicParams,
                                  (IVC1VDEC_Status *)&status
                                 );
                    if(retVal == XDM_EFAIL)
                    {
                        break;
                    }
/*----------------------------------------------------------------------------*/
/* Set the flush mode flag to ON condition - this flag will help us           */
/* exit out of the while loop when display-bufs go NULL. This flag is         */
/* is required since display-bufs can go NULL even in the initial or          */
/* in-between decode state. By setting this flag we signal that when          */
/* when next time display-bufs go NULL its time to exit.                      */
/*----------------------------------------------------------------------------*/
                	inFlushModeFlag = 1;
            }
        }while(1);  /* end of Do-While loop for all the frames in stream */
EndOfFile:

/*
 * Reset the decode process.
 * Bring to the state where decode can start fresh i.e
 * The state immediately after algorithm init.
 */
        retVal = VC1VDEC_control((VC1VDEC_Handle)handle,
                                 XDM_RESET,
                                 (IVC1VDEC_DynamicParams *)&dynamicParams,
                                 (IVC1VDEC_Status *)&status
                                );
/*
 * Un init the buffer manager
 */
        BUFFMGR_DeInit();
/*
 * Output file close
 */
        fclose(ftestFile);
/*
 * When decoder ends up decoding first frame itself with some error
 * To avoid division with zero make frame count as 1
 */
    if(frameCount == 0)
    {
             frameCount = 1;
    }
    printf("\n --------------  SUMMARY --------------------\n");
    if(!testCompliance)
    {
        printf(" Decoder output dump completed\n");
    }
    printf("\t Total number of Frames              = %d\n",
      (XDAS_UInt32)decode_frameCount);

      if(decode_frameCount == 0)
      {
		  /*approximating so div_by_zero exception does_not_occur*/
		  decode_frameCount = 1;
	  }
    printf("\t Bit Rate at 30 frames/Sec           = %d Kbps\n",
      (XDAS_UInt32)(((bytesConsumed*8*30)/decode_frameCount)/1000));
    printf("\t Width and Height                    = %d, %d \n",
               (XDAS_UInt32)status.viddecStatus.outputWidth,
               (XDAS_UInt32)status.viddecStatus.outputHeight);
    printf (" --------------    END   --------------------\n");

   } /* Read the Config File until it reaches the end of file */
/*
 * Delete the Algorithm instance object specified by handle
 */
    ALG_delete (handle);

    /* De-Initialization */
    CMEM_free(inputData, &memParams);


#ifdef _ENABLE_IRES_EDMA3
        /*
         * Unregister the protocol
         */
        if (IRES_OK != RMAN_unregister(&IRESMAN_EDMA3CHAN)) {
                printf("Unregister Protocol Failed \n");
                return -1;
        }

	if(IRES_OK != RMAN_unregister(&IRESMAN_ADDRSPACE)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }

    if (IRES_OK != RMAN_unregister(&IRESMAN_HDVICP)) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }



        RMAN_exit();
#endif
/*----------------------------------------------------------------------------*/
/* Signal ARM968 to terminate wait and goto sleep                             */
/* This is not required when interrupt is enabled between ARM968 and ARM926     */
/*----------------------------------------------------------------------------*/

   printf("\n End of execution\n");
/*
 * Close the config files
 */
   fclose(fConfigFile);

#ifdef ENABLE_CACHE
  ARM926_Icache_Disable();
  ARM926_Dcache_Disable();
#endif

  return XDM_EOK;
} /* main() */

/* =============================================================================
 *  @func     TestApp_ReadByteStream
 *
 *  @desc     Sample utility function for reading encoded bit-stream in chunks.
 *             The input file is opened every time and next
 *             "INPUT_BUFFER_SIZE - validBytes" number of bytes is read into the
 *             input buffer. End-of-file if encountered in previous runs is
 *             remebered for given input config record.
 *
 *  @param   XDAS_Int8 *inFile:
 *           Input file name as a null-terminated array of characters.
 *
 *  @return   XDAS_Int32
 *            Returns the Bytes read
 *  ============================================================================
  */
XDAS_Int32 TestApp_ReadByteStream(xdc_Char *inFile)
  {
#ifndef NO_RCV_HEADER_PARSING
    XDAS_UInt32 BytesRead, BufferSize, Index;
#else
    XDAS_UInt32 StratCode;
    XDAS_UInt32 Size;
    XDAS_UInt32 frame_size;
#endif
    FILE  *finFile;
/*
 * If end-of-file had already been encountered for this config
 * record, then just return the remaining bytes in the input
 * bit-stream.
 */
   if( 2 == g_streamType)
   {
	   isAdvanced = 1;
   }
   if(reachedEndOfFile)
   {
        return validBytes;
   }
#ifdef NO_RCV_HEADER_PARSING

/*
 * Open input file
 */
    finFile = fopen (inFile, "rb");
    if (!finFile)
    {
        printf("\n Couldn't open Input file...  %s  ",inFile);
        printf("\n Exiting for this configuration...");
        return -1;
    }
/*
* Seek to the exact location in the input file from where previous
* read had left over
*/
    fseek (finFile, fileOffset, SEEK_SET);
/* check for the end of file */
    if(!isAdvanced && feof(finFile))
    {
        return 0;
    }
/*
 * Check if it is first frame or not
 * if it is first frame parse the RCV initial header and extrac sequence header
 * for simple and main profile.
 */
    if(firstFrameInStream)
    {
/*
 * Read first 4 bytes and ckeck for the advanced profile.
 * if advanced profile return 0 bytes to read.
 *
 */
        StratCode= 0;
        fread(&StratCode,1,4,finFile);
        fseek (finFile, 0, SEEK_SET);
        if(StratCode == 0x0F010000 || (2 == g_streamType))
        {
            int i,count;
            partial_vde_bytes = 0;
            firstFrameInStream = 0;
            isAdvanced = 1;
            Actual_No_Fr_decode = 30000;

        /* Read the input Frame data into the buffer */
           count = fread(&inputData[validBytes], 1, INPUT_BUFFER_SIZE, finFile);

            if (!count)
            {
                fclose(finFile);
                printf("Failed to read Input frame \n");
                return -1;
            }


            for(i = (count-1); i > 2; i--)
            {
                if((inputData[i] == 0x0d) && (inputData[i-1] == 0x01) &&
                (inputData[i-2] == 0x00) && (inputData[i-3] == 0x00))
                    break;
                else
                    partial_vde_bytes++;
            }
            if(i==2)
            {
                printf("Error! Buffer overrun\n");
                return -1;
            }
            partial_vde_bytes = partial_vde_bytes + 4;
            if(feof(finFile))
            {
                validBytes = count;
                endofFile = 1;
            }
            else
                validBytes = (count - partial_vde_bytes);
        /* Update the fileoffset counter */
            fileOffset = ftell(finFile);
        /* Close the file */
            fclose(finFile);
            return validBytes;
        }
        else
        {
            XDAS_UInt8 Type;
            validBytes = 0;
            isAdvanced = 0;

            /* pattern - 0xC5XXYYZZ where XXYYZZ-no. of frames in stream */
            if (fread(&Size, 1, 4, finFile) != 4)
            {
                fclose(finFile);
                printf("Failed to read RCV number of frames\n");
                return -1;
            }

			if(ParseRcvInLib)
			{

            memcpy(&inputData[validBytes],&Size,4);
            validBytes += 4;

			}
            Size = (Size << 8) >> 8;
            fseek(finFile,-1,SEEK_CUR);
/* Init the number of frames to decode */
            Actual_No_Fr_decode = Size;
            if(Actual_No_Fr_decode > framesToDecode)
            {
                Actual_No_Fr_decode = framesToDecode;
            }
            if(1 == g_decodeHeader)
            {
				Actual_No_Fr_decode += 1;
			}
            if (fread(&Type, 1, 1, finFile) != 1)
            {
                fclose(finFile);
                printf("Failed to read RCV header\n");
                return -1;
            }
            if ((Type & ~RCV_V2_MASK) != RCV_VC1_TYPE)
            {
                fclose(finFile);
                printf("Not an RCV file containing VC1 data \n");
                return -1;
            }
            RCVIsV2Format = (XDAS_UInt8)((Type & RCV_V2_MASK) != 0);

            /* pattern - 0x00000004 */
/*
 * Read the size of the extened data
 */
            if (fread(&Size, 1, 4, finFile) != 4)
            {
                fclose(finFile);
                printf("Failed Size of Sequence Header\n");
                return -1;
            }

			if(ParseRcvInLib)
			{

            memcpy(&inputData[validBytes],&Size,4);
            validBytes += 4;

			}


/* Check for the terminating condition*/
            if(Size > 256)
            {
                fclose(finFile);
                printf("ERROR: Header is more than Max expected \n");
                return -1;
            }

            /* pattern - 4 byte header 0xAABBCCDD-STRUCT_C */
/* Read seqence header into temporary buffer */
            if (fread(temp_Sequnce_Header, 1, Size, finFile) != Size)
            {
                fclose(finFile);
                printf("Failed Size of Sequence Header\n");
                return -1;
            }


/* Fill struct C now into input buffer */
            memcpy(&inputData[validBytes],temp_Sequnce_Header,4);
/* Update the validbytes counter */
            validBytes += 4;


		/* pattern - STRUCT_A : VERT_HT followed by HORZ_HT - 8 bytes */
/*
 * Next coming is STRUCT A write directly into input buffer
 */
            if (fread(&inputData[validBytes], 1, 8, finFile) != 8)
            {
                fclose(finFile);
                printf("Failed to read Size of STRUCT A\n");
                return -1;
            }
/* Update the validbytes counter */
            validBytes += 8;


			/* pattern - STRUCT_B for V2 only */
/* V2 format has another information block */
            if (RCVIsV2Format)
            {
                /* The block starts with its size */
                if(fread(&Size, 1, 4, finFile) != 4)
                {
                    fclose(finFile);
                    printf("Failed to read RCV picture size\n");
                    return -1;
                }


				if(ParseRcvInLib)
				{

                memcpy(&inputData[validBytes],&Size,4);
                validBytes += 4;

				}

                if (fread(temp_struct_b, 1, Size, finFile) != Size)
                {
                    fclose(finFile);
                    printf("Failed to read Size of STRUCT B\n");
                    return -1;
                }
                if(ParseRcvInLib)
                {

                memcpy(&inputData[validBytes],temp_struct_b,Size);
                validBytes += Size;

				}


#endif
			}

        }

    }
	if(!isAdvanced)
    {
		if(g_decodeHeader)
		{
			fileOffset += validBytes;
			return validBytes;
		}
	}

/* Frame header parsing to read time-stamp and number of bytes in frame for SP and MP */
    if(isAdvanced)
    {
        if(!validBytes || 1 == g_seq_hdr_corrupt)
        {
            int i,count;

            if(endofFile)
            {
                printf("EOF\n");
                return 0;
            }
            fseek(finFile,-partial_vde_bytes,SEEK_CUR);
            fseek(finFile,-validBytes,SEEK_CUR);
            partial_vde_bytes = 0;
            bytesConsumed = 0;
            validBytes = 0;

            /* Read the input Frame data into the buffer */
            count = fread(&inputData[validBytes], 1, INPUT_BUFFER_SIZE, finFile);
            if (!count)
            {
                fclose(finFile);
                printf("Failed to read Input frame \n");
                return -1;
            }

            for(i = (count-1); i > 2; i--)
            {
                if((inputData[i] == 0x0D) && (inputData[i-1] == 0x01) &&
                  (inputData[i-2] == 0x00) && (inputData[i-3] == 0x00))
                    break;
                else
                    partial_vde_bytes++;
            }
            if(i==2)
            {
                printf("Error! Buffer overrun\n");
                return -1;
            }

            partial_vde_bytes = partial_vde_bytes + 4;

            if(feof(finFile))
            {
                validBytes = count;
                endofFile = 1;
            }
            else
                validBytes = (count - partial_vde_bytes);

        }
    /* Update the fileoffset counter */
        fileOffset = ftell(finFile);
    /* Close the file */
        fclose(finFile);
        return validBytes;

    }
    else
    {
    /* If it is not first frame Just parse the RCV header to find out the size
       of the frame and extra data */
        if (fread(&Size, 1, 4, finFile) != 4)
        {
            fclose(finFile);
            printf("Failed to read RCV Frame size\n");
            return -1;
        }

		if(ParseRcvInLib)
		{

        memcpy(&inputData[validBytes],&Size,4);
        validBytes += 4;

		}
		else
		{
			if(RCVIsV2Format)
			{
				/*ignore the flags*/
				Size =  ((Size << 8) >> 8);

			}

		}


    /* Skip time stamp if it is RCV V2 format*/
        if (RCVIsV2Format)
        {
            /* Mask off the flag bits */
            Size = Size & ~RCV_V2_FRAMESIZE_FLAGS;
            /* Skip the timestamp */


			if (fread(time_stamp, 1, 4, finFile) != 4)
			{
				fclose(finFile);
				printf("Failed to read Size of Timestamp\n");
				return -1;
			}
			if(ParseRcvInLib)
			{

			memcpy(&inputData[validBytes],time_stamp,4);
			validBytes += 4;

			}


        }


		{

		XDAS_UInt32 curr_offset,total_bytes_in_file,bytes_left_in_file;

		curr_offset = ftell(finFile);
		fseek(finFile,0,SEEK_END);
		total_bytes_in_file = ftell(finFile);
		fseek(finFile,curr_offset,SEEK_SET);

		bytes_left_in_file = total_bytes_in_file - curr_offset;

		if(Size > bytes_left_in_file)
		{
			Size = bytes_left_in_file;
		}

    /* Read the input Frame data into the buffer */
        if (fread(&inputData[validBytes], 1, Size, finFile) != Size)
        {
            fclose(finFile);
            printf("Failed to read Input frame \n");
            return -1;
        }

		}

		if(ParseRcvInLib)
		{

    /* Update the validbytes counter */
        validBytes += Size;

		}


    /* Update the fileoffset counter */
        fileOffset = ftell(finFile);

    /* Close the file */
       fclose(finFile);

		if(!ParseRcvInLib)
		{

		/* to returm valid numBytes to Application */
			if (firstFrameInStream)
			{
				Size += 12;
			}
			frame_size = Size;

		}
       /*
	    * Make the firstframe flag to 0
	    */
        firstFrameInStream = 0;

		if(!ParseRcvInLib)
		{

        validBytes = frame_size;

		}

        return validBytes;
    }

#else

/*
 * Put a check such that application cannot read always from file and transfer bytes
 * from one place to another place
 */

/*
 * Open input file
 */
   finFile = fopen (inFile, "rb");
   if (!finFile)
   {
      printf("\n Couldn't open Input file...  %s  ",inFile);
      printf("\n Exiting for this configuration...");
      return -1;
   }
/*
 * Seek to the exact location in the input file from where previous
 * read had left over
 */
   fseek (finFile, fileOffset, SEEK_SET);
/*
 * Shift data from lower-half to upper part
 */
   for(Index = 0; Index < validBytes; Index++)
   {
        inputData[Index] = inputData[bytesConsumed + Index];
   }
/*
 * Read the "BufferSize" number of bytes in the input buffer
 */
    bytesConsumed = 0;
       BufferSize = INPUT_BUFFER_SIZE - validBytes;
   BytesRead = fread (&inputData[validBytes], 1, BufferSize, finFile);
/*
 * Store the exact pointer in the input file for next read.
 * fileOffset is also used to keep track of total file size
 * processed at any given instant. Its used to calculate the
 * bit-rate of the input file as well at the end of decoding
 */
        fileOffset = ftell(finFile);
   fclose(finFile);
/*
 * Determine end-of-file condition
 */
        if (BytesRead != BufferSize)
        {
          reachedEndOfFile = 1;
   }
/*
 * Return exact valid bytes in input buffer
 */
    return (validBytes + BytesRead);
#endif
}


/*****************************************************************************/
/**
*@func  TestApp_PostProcessData()
*@brief  Sample utility function for post process of VC1 decoder.
*        basically it does Cb and Cr separating, Range scaling and also
*        Resolution upscaling.
*        Note: The upsampling algo is exactly same as SMPTE ref decoder
*              implimentation
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
XDAS_Int32 TestApp_PostProcessData( IVIDDEC2_OutArgs *outArgs,
                                    XDAS_Int32  height,
                                    XDAS_Int32  width
                                  )
{
    int X, Y, K;
    int CodedWidth, CodedHeight;
    XDAS_UInt8 *CbCr_data;
    XDAS_UInt8 *CbCr_seperate[2];
    XDAS_UInt8 *pSData[3];
    XDAS_UInt32 SPitch[3];
    XDAS_Int32 error;
    XDAS_Int32 DisplayWidth,DisplayHeight;

    XDAS_UInt8 *pDData[3];
    XDAS_UInt32 DPitch[3];
    XDAS_UInt32 scale_luma,scale_croma;
    XDAS_UInt32 pic_size = ((outArgs->displayBufs[0].frameWidth) *
                             (outArgs->displayBufs[0].frameHeight));

    scale_luma= scale_croma = 8;
    error = 0;
/*
 * Separtet the Cb Cr samples
 */
    CbCr_data =
         (XDAS_UInt8 *)outArgs->displayBufs[0].bufDesc[1].buf;
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
                       ((outArgs->displayBufs[0].frameHeight) >> 1),
                       outArgs->displayBufs[0].frameWidth,
                       outArgs->displayBufs[0].framePitch,
                       0
                       );

/*
 * Assigne Source buffer pointers
 */
    pSData[0] = (XDAS_UInt8 *)outArgs->displayBufs[0].bufDesc[0].buf;
    SPitch[0] = outArgs->displayBufs[0].framePitch;
    pSData[1] = CbCr_seperate[0];
    SPitch[1] = outArgs->displayBufs[0].frameWidth >>1;
    pSData[2] = CbCr_seperate[1];
    SPitch[2] = outArgs->displayBufs[0].frameWidth >> 1;

/*
 * Assign Destination buffer pointers
 */
    pDData[0] = (XDAS_UInt8 *)Luma_separate;
    pDData[1] = (XDAS_UInt8 *)Cb_seperate;
    pDData[2] = (XDAS_UInt8 *)Cr_seperate;
    DPitch[0] = width;
    DPitch[1] = width >> 1;
    DPitch[2] = width >> 1;


/*
 * Check for the extended params and scaling
 */
    if(outArgs->size == sizeof(IVC1VDEC_OutArgs))
    {
        IVC1VDEC_OutArgs *TempOutargs = (IVC1VDEC_OutArgs *)outArgs;
        scale_luma = (TempOutargs->rangeYScale) ;
        scale_croma = (TempOutargs->rangeUVScale) ;
    }
    for (K = 0; K < 3; K++)
    {
        int Scale;
        int VertOffset = 0;
        CodedWidth = outArgs->displayBufs[0].frameWidth;
        CodedHeight = outArgs->displayBufs[0].frameHeight;
        DisplayWidth = width;
        DisplayHeight = height;
        if(K == 0)
        {
            Scale = scale_luma;
        }
        else
        {
            CodedWidth    >>= 1;
            CodedHeight   >>= 1;
            DisplayWidth  >>= 1;
            DisplayHeight >>= 1;
            Scale = scale_croma;
        }
/*
 * Check whether we need to upscale horizantally
 */
        if(DisplayWidth > CodedWidth)
        {
    /* Shrink according to resolution scale */
            pDData[K] += CodedWidth;
        }
/*
 * Check whether we need to upscale vertically
 */
        if(DisplayHeight > CodedHeight)
        {
            VertOffset = CodedHeight;
/*
 * We run the vertical filter up to the next multiple of 8
 * (luma) or 4 (chroma) or the height+2, whichever is the
 * smaller.
 * The bottom row pixels only depend on the two following rows.
 */
            if (K==0)
            {
                CodedHeight = (CodedHeight + 7) & ~7;
            }
            else
            {
                CodedHeight = (CodedHeight + 3) & ~3;
            }
            if (VertOffset + 2 < CodedHeight)
            {
                CodedHeight = VertOffset + 2;
            }
            VertOffset = 2*VertOffset - CodedHeight;

            pDData[K] += VertOffset*DPitch[K];
        }
/*
 * Copy data applying range reduction scale at the same time
 */
        for (Y = 0; Y < CodedHeight; Y++)
        {
            for (X = 0; X < CodedWidth; X++)
            {
                int Pixel;

                Pixel = pSData[K][X] - 128;
                Pixel = (Pixel*Scale + 4)>>3;
                pDData[K][X] = (XDAS_UInt8)CLIP(Pixel + 128);
            }

            pSData[K] += SPitch[K];
            pDData[K] += DPitch[K];
        }
/*
 * Expand according to resolution scale (Simple/Main profiles only)
 */
        if(DisplayWidth > CodedWidth)
        {
            pDData[K] -= CodedHeight * DPitch[K];

            /* Horizontal Upsample - Simple/Main only */
            for (Y=0; Y<CodedHeight; Y++)
            {
                TestApp_ResolutionUpsample(pDData[K]-CodedWidth, pDData[K], 1, CodedWidth, CodedWidth);
                pDData[K] += DPitch[K];
            }
            pDData[K] -= CodedWidth;
            CodedWidth <<= 1;
        }
        if(DisplayHeight > CodedHeight)
        {
            pDData[K] -= CodedHeight * DPitch[K];

            /* Vertical Upsample */
            for (X=0; X<CodedWidth; X++)
            {
                int Height = (VertOffset+CodedHeight)>>1;
                TestApp_ResolutionUpsample(pDData[K]-VertOffset*DPitch[K],
                                            pDData[K],
                                            DPitch[K],
                                            Height,
                                            CodedHeight);
                pDData[K]++;
            }
        }
    }
    return error;
}

/*****************************************************************************
 *@func  TestApp_CompareOutputData()
 *@brief  Sample utility function for comparing the raw decoded output with
 *           reference output data.
 *
 *@param  FILE *fRefFile:
 *           Reference file pointer.
 *
 *  @param    height
 *            Frame height
 *
 *  @param    width
 *            Frame width
 *
 *
 *@return XDM_EFAIL : If comparison fails.
 *        XDM_EOK: If comparison passes.
 *
 *@note   None
 */
/*****************************************************************************/
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
                                     XDAS_Int32  height,
                                     XDAS_Int32  width)
{
    XDAS_Int32 pic_size = height*width;
    XDAS_UInt32 refCRC, dataCRC;
    XDAS_Int32 ierrorflag = 0;

/*
 * First Compare Luma data
 */
    refCRC = *RefCrcBufPtr++;
    crcInit();
    dataCRC = crcFast(Luma_separate,(height*width));

    if(dataCRC != refCRC)
    {
        printf("Luma data doesnot match \n");
        ierrorflag = -1;
    }
    refCRC = *RefCrcBufPtr++;
    crcInit();
    dataCRC = crcFast(Cb_seperate, pic_size>>2);

    if(dataCRC != refCRC)
    {
        printf("Cb data doesnot match \n");
        ierrorflag = -1;
    }
    refCRC = *RefCrcBufPtr++;
    crcInit();
    dataCRC = crcFast(Cr_seperate, pic_size>>2);

    if(dataCRC != refCRC)
    {
        printf("Cr data doesnot match \n");
        ierrorflag = -1;
    }
    return ierrorflag;

}

/* =============================================================================
 *  @func     separateCbCrPixels
 *
 *  @desc     Separate the interleaved croma pixels into diff buffers
 *
 *  @param    CbCr_data
 *            Interleaved input
 *
 *  @param    Chroma_buf[2]
 *            Output buffers
 *
 *  @param    height
 *            Frame height
 *
 *  @param    width
 *            Frame width
 *
 *  @param    paddedWidth
 *            Padded width
 *
 *  @parma    paddedHeight
 *            Padded height
 *
 *  @return   XDAS_Void
 *            Null
 *  ============================================================================
 */
void separateCbCrPixels(XDAS_UInt8  *CbCr_data,
      XDAS_UInt8  *Chroma_buf[2],
      XDAS_Int32  height,
      XDAS_Int32  width,
      XDAS_UInt16 paddedWidth,
      XDAS_UInt16 paddedHeight
     )
{


  XDAS_UInt32 i,j;
  XDAS_UInt32 pix_count = 0;
  XDAS_UInt8* Cb_data;
  XDAS_UInt8* Cr_data;
   XDAS_UInt8* CbCr_buf;
/*
 * Assign Buffer pointers to temp ptrs
 */
  Cb_data = Chroma_buf[0];
  Cr_data = Chroma_buf[1];
  CbCr_buf = CbCr_data;
/*
 * Loop for entire rows and colums
 * Do not saparate for Padded pixels as it is not required store
 */
  for(i = 0; i< height; i++)
  {
    for(j = 0; j< width; j+=2)
    {
        Cb_data[pix_count] = CbCr_buf[j];
        Cr_data[pix_count] = CbCr_buf[j+1];
        pix_count++;
    }
    CbCr_buf += paddedWidth;
  }
}
/* =============================================================================
 *  @func     TestApp_WriteOutputData
 *
 *  @desc     Sample utility function for dumping encoded bit-stream. Before
 *            writing raw YUV data packed and interleaved chroma data is
 *            separated into a separate buffer.
 *
 *  @param    fOutFile
 *            Pointer to output file.
 *
 *  @param    Height
 *            Display height
 *
 *  @param    Width
 *            Display width
 *
 *  @return   XDAS_Void
 *            Null
 * =============================================================================
  */

XDAS_Void TestApp_WriteOutputData(FILE *fOutFile,
    XDAS_Int32  height,
    XDAS_Int32  width)
{
    XDAS_Int32 frame_size = height*width;
    fwrite (Luma_separate, sizeof (char),frame_size,fOutFile);
    fwrite (Cb_seperate, sizeof (char),frame_size >> 2,fOutFile);
    fwrite (Cr_seperate, sizeof (char),frame_size >> 2,fOutFile);
    fflush (fOutFile);
}
/* =============================================================================
 *  @func     TestApp_SetInitParams
 *
 *  @desc     Setting of creation time parameters
 *
 *  @param    params
 *            Pointer to IVIDDEC2_Params structure.
 *
 *  @return   XDAS_Void
 *            Null
 *  ============================================================================
  */
XDAS_Void TestApp_SetInitParams(IVIDDEC2_Params *params)
{
/*
 * Set IVIDDEC2 parameters
 */
/*
 * Data Endianness(1:Big, 2:16-bit Little, 3:32-bit Little)
 * Only Big Endian is supported in DM510 VC1 Decoder
 */
    params->dataEndianness      = 1;
    return;
  }

/* =============================================================================
 *  @func     TestApp_SetDynamicParams
 *
 *  @desc     Setting of run time parameters
 *
 *  @param    dynamicParams
 *            Pointer to IVIDDEC2_DynamicParams structure.
 *
 *  @return   XDAS_Void
 *            Null
 *  ============================================================================
  */
XDAS_Void TestApp_SetDynamicParams(IVIDDEC2_DynamicParams *dynamicParams)
{
/*
 * Set IVIDDEC2 Run time parameters
 */
   dynamicParams->decodeHeader  = XDM_DECODE_AU; /*Supported*/
/*
 * Not Supported: Set to default value
 */
   dynamicParams->displayWidth  = 0;
/*
 * Not Supported: Set to default value
 */
   //dynamicParams->displayHeight  = 0;
/*
 * Not Supported: Set to default value
 */
    dynamicParams->frameSkipMode = IVIDEO_NO_SKIP;
/*
 * Not Supported: Set to default value
 */
    dynamicParams->frameOrder = 0;
/*
 * Not Supported: Set to default value
 */
    dynamicParams->newFrameFlag = 0;
/*
 * Not Supported: Set to default value
 */
    dynamicParams->mbDataFlag = 0;

/*
 * Check whether extra dynamic params is set by checking the size
 */
    if(dynamicParams->size == sizeof(IVC1VDEC_DynamicParams))
    {
/*
 * For outloop deblocking for simple profile below flag is set. This can be
 * dynamically configured at frame level
 */
        IVC1VDEC_DynamicParams *extdynamic =
                            (IVC1VDEC_DynamicParams *)dynamicParams;
        extdynamic->outloopDeblocking = 0;

    }
    return;
  }


/* =============================================================================
 * TestApp_ResolutionUpsample()
 * Description:
 *              Sample Upsample filter for VC1 decoded frame.
 *
 * Remarks:
 * This is just an example upsample filter and is not specified in the spec.
 * The spec leaves the choice of resolution scale upsample filter as
 * implementation dependant
 *
 * Inputs:
 * pDest    - Pointer to destination line (upsampled)
 * pSrc     - Pointer to source line
 * Skip     - Byte skip between each line element
 * Length   - Number of output samples to write
 * Limit    - Number of input samples available
 *=============================================================================
 */

XDAS_Void TestApp_ResolutionUpsample(
                        XDAS_UInt8 *pDest,
                        XDAS_UInt8 *pSrc,
                        XDAS_Int32 Skip,
                        XDAS_Int32 Length,
                        XDAS_Int32 Limit
                        )
{
    int X0, X1, X2, X3, X4, X;
    int Y0, Y1;
    int Round = 15;

    if (Skip>1)
    {
        /* Vertical Upsample */
        Round = 16;
    }

    /* Initialize delay line */
    X3 = *pSrc;
    pSrc += Skip;

    X4 = *pSrc;
    pSrc += Skip;

    /* Reflect missing pixels */
    X2 = X3;
    X1 = X4;

    for (X=2; X<Length+2; X++)
    {
        /* shift samples */
        X0 = X1;
        X1 = X2;
        X2 = X3;
        X3 = X4;
        if (X<Limit)
        {
            X4 = *pSrc;
            pSrc += Skip;
        }
        else
        {
            /* Reflect missing pixels */
            if (X==Limit)
            {
                X4 = X3;
            }
            else
            {
                X4 = X1;
            }
        }

        /* Upsample x 2 */
        Y0 = (     6*X1 + 28*X2 - 3*X3 + X4 + Round) >> 5;
        Y1 = (X0 - 3*X1 + 28*X2 + 6*X3      + Round) >> 5;

        /* Save results */
        *pDest = (XDAS_UInt8)CLIP(Y0);
        pDest += Skip;
        *pDest = (XDAS_UInt8)CLIP(Y1);
        pDest += Skip;
    }
}
 /*!
  *! Revision History
  *! ================
  *!
  *! 09-Aug-2007   Ramamohan : Code clean up and added comments.
  *! 24-Apr-2007   Uday: File name and other changes to meet coding guidelines
  *!                    requirements.
  *! 12-0ct-2006   Krishnakanth Rapaka : Initial draft
*/



//#endif

