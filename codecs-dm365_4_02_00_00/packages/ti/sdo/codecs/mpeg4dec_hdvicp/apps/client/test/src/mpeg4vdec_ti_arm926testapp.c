/** ==========================================================================
 *  @file  mpeg4vdec_ti_arm926testapp.c
 *
 *  @path   $(PROJDIR)\Src
 *
 *  @desc   This is the top level client file that drives the MPEG4
 *        (Simple Profile) Video Decoder Call using XDM v1.0 Interface
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/


/* -------------------- compilation control switches -----------------------*/

/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/

/* -------------------- system and platform files ------------------------- */

#include <string.h>


#include <stdio.h>
#include <stdlib.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/ires.h>
#include <ti/xdais/dm/ividdec2.h>
//#include <csl_edma.h>
//#include <cslr_edmacc.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include <ti/sdo/utils/trace/gt.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#ifdef PROF_LINUX
#include <sys/time.h>
#endif

#ifdef DEVICE_ID_CHECK
/* Link modules used for DEVICE ID check */
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>
#endif


/* ------------------------- program files -------------------------------- */
/* Mpeg-4 Interface header files */
#include "imp4vdec_tii.h"
#include "mpeg4vdec_ti_arm926testapp.h"
//#include "edma_dm510.h"
#include "buffermanager.h"
#include "hdvicp_framework.h"
#include "testapp_arm926intc.h"
#include "mpeg4vdec_ti_api.h"

//#define PROFILE_ONLINUX

#ifdef PROFILE_ONLINUX
#include <sys/time.h>
extern int arm968_time;
#endif

/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/

/* ------------------------ data declarations ----------------------------- */

/* ----------------------- function prototypes ---------------------------- */


/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/

/* ----------------------- data declarations ------------------------------ */
/* The maximum number of frames decoded by the decoder. This macro is added
 * for debug purpose. This macro will be usefull in limitting the number of
 * frames to be decoded during testing
 */
XDAS_UInt32                 framesToDecode;
/* The frames number from which output need to be dumped. This macro is added
 * for debug purpose. This macro will be usefull in limitting the number of
 * frames to be dumped during testing
 */
XDAS_UInt32                 DumpFrom;
/* Flag to enable CRC calculation and dumping for Luma and chroma seperately
 * instead of dumping YUV.
 */
XDAS_UInt32                 CrcNyuv;
Imp4VDEC_Params             params;
Imp4VDEC_DynamicParams      dynamicParams;
extern IRES_Fxns MPEG4VDEC_TI_IRES;
//static GT_Mask someGTMask;
/* This global array of structure elements define the format of
 * config file being used. User needs to modify this array either
 * by adding new elements or by deleting existing elements in
 * correspondence to the changes required in parameters configuration
 * .cfg file
 */
sTokenMapping sTokenMap[] =
{
  {"FramesToDecode", &framesToDecode},
  {"DumpFrom",       &DumpFrom},
  {"CRCEnable",      &CrcNyuv},
  {"ImageHeight",    &params.viddecParams.maxHeight},
  {"ImageWidth",     &params.viddecParams.maxWidth},
  {"ChromaFormat",   &params.viddecParams.forceChromaFormat},
  {"displayDelay",           &params.displayDelay},
  {NULL,             NULL}
};

/* ---------------------- function prototypes ----------------------------- */
//typedef  unsigned char Byte;

/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/

/* ---------------------- data declarations ------------------------------- */
/* Input buffer allocation INPUT_BUFFER_SIZE defined in TestAppDecoder.h */
#ifdef ON_LINUX
XDAS_Int8 *inputData;
#else
#pragma     DATA_SECTION(inputData, ".input_buffer")
XDAS_Int8   inputData[INPUT_BUFFER_SIZE];
#endif
/* Total number of valid Bytes still left over in the input bit-stream
 * buffer. This values is first initialised to the total bytes read from
 * the input file and it keeps getting decremented as the data is consumed
 * by every successive process call. It is also used to signal error in
 * reading the input file
 */
XDAS_Int32  validBytes;

/*Stores the total bytes consumed by the decoder from the encoded input
 * bit-stream during previous process call.
 */
XDAS_UInt32 bytesConsumed;

/* Used as a boolean flag to indicate if the end-of-input-encoded bit-stream
 * file has been encountered.
 */
XDAS_UInt32 reachedEndOfFile;

/* Offset in the input file from where next read happens
 */
XDAS_UInt32 fileOffset;

/* This buffer holds the seperated out Cb Cr component - useful for dumping
 * the decoded output to a file stream - this array can be avoided if CbCr
 * need nto be seperated before writing the the outptu file
 * CHROMA_BUFFER_SIZE depends on the maximum picture size supported and is
 * defined in TestAppDecoder.h
 */
#pragma    DATA_SECTION(Chroma_seperate, ".chroma_buffer")
XDAS_Int8  Chroma_seperate[CHROMA_BUFFER_SIZE];
/* This buffers holds the reference out Cb Cr component - useful for comparing
 * the decoded output to a file stream
 * CHROMA_BUFFER_SIZE depends on the maximum picture size supported and is
 * defined in TestAppDecoder.h
 */
#pragma    DATA_SECTION(cb_ref, ".chroma_buffer")
XDAS_Int8  cb_ref[CHROMA_BUFFER_SIZE>>1];
#pragma    DATA_SECTION(cr_ref, ".chroma_buffer")
XDAS_Int8  cr_ref[CHROMA_BUFFER_SIZE>>1];

/* This buffer holds the cropped Luma component - useful for calculating
 * CRC of the decoded output. LUMA_BUFFER_SIZE calculated depends on
 * the maximum picture size supported and is defined in TestAppDecoder.h
 */
#pragma    DATA_SECTION(Luma_out, ".chroma_buffer")
#define    LUMA_BUFFER_SIZE   IMAGE_WIDTH*IMAGE_HEIGHT
XDAS_Int8  Luma_out[LUMA_BUFFER_SIZE];
/* This buffer holds the reference Luma component - useful for comparing
 * with reference of the decoded output.LUMA_BUFFER_SIZE calculated depends on
 * the maximum picture size supported and is defined in TestAppDecoder.h
 */
#pragma    DATA_SECTION(Luma_ref, ".chroma_buffer")
XDAS_Int8  Luma_ref[LUMA_BUFFER_SIZE];


/* --------------------- function prototypes ------------------------------ */


/* ---------------------------- macros ------------------------------------ */
/* The maximum external memory required for supplying input buffers to the
 * decoder process call by the buffer manager. The value is calculated as
 * following (720 + 48) * (576 + 32) * 1.5 * 3
 * full HD   (1920 + 48)* (1088 + 32)* 1.5 * 3
 * HD        (1280 + 48)* (720 + 32) * 1.5 * 3
 */
//#define     MAX_IN_BUF_SIZE         2101248
//#define     MAX_IN_BUF_SIZE         4493952
#define     MAX_IN_BUF_SIZE         (IMAGE_WIDTH+48) * (IMAGE_HEIGHT+32) * 1.5 * 3
/* The macro to enable or disable Out-loop de-blocking filter for post
 * processing.
 */
#define     DEBLOCK                 0

/* The macro to enable or disable Out-loop De-Ringing filter for post
 * processing.
 */
#define     DERING                  0



#define RESET_HDVICP_EVERY_FRAME    0
/* Processer running frequency                                              */

#define _ENABLE_IRES_EDMA3
#define     CLOCK_SEC               180000000

#ifdef _PROFILE_
XDAS_UInt32 ARM926cycles,ARM968cycles0,ARM968cycles1;
#endif
//#define _STR_CUT_


/* Allocate CMEM structure and intialize it */
#ifdef ON_LINUX
    CMEM_AllocParams memParams;
#endif
//#define _STR_CUT_

/* ===========================================================================
 *  @func   main()
 *
 *  @desc   Sample main program implementation which uses xDM v1.0 MPEG-4
 *          decoder's APIs to create a decoder instance and decode multiple
 *          input files. It supports dumping of output decoded YUV data in
 *          4:2:0 format or comparision fo decoded raw data with reference
 *          data.Uses single instance of the decoder and uses only base params
 *          for all input classes.
 *
 *          Uses buffer manager for XDM v1.0 compatible buffer management and
 *          uses utility functions for reading encoded bit-stream,
 *          Seperating CbCr components,
 *          Comparing output data with reference data &
 *          Dumping raw YUV data into a file in binary format.
 *
 *  @param  dynamic_ecd_context
 *          Pointer to ecd dynamic context structure.
 *
 *  @return XDM_EOK  : If successfully decoded all input streams/files
 *          XDM_EFAIL: If encountered error in decoding the given set of
 *                     input files.
 *
 *  @note   None
 *
 * ===========================================================================
 */
int main ()
{
    /* File I/O variables                                                   */
    FILE *fConfigFile, *ftestFile, *fparamsFile;
    xdc_Char line[2*STRING_SIZE], inFile[STRING_SIZE], testFile[STRING_SIZE];
    xdc_Char paramsFile[STRING_SIZE];
    XDAS_Int32  testCompliance;
    XDAS_UInt8 *chksum, *ref_byte;

#ifdef TST_FRAME_MODE
    xdc_Char sizeFile[STRING_SIZE];
    FILE *fsizeFile;
#endif
#ifdef _STR_CUT_
    FILE * fp;
#endif
#ifndef ON_LINUX
#ifdef ONELINE_CONFIG
    xdc_Char *fname = "..\\..\\..\\Test\\TestVecs\\Config\\Testvecs1.cfg";
#else
    xdc_Char *fname = "..\\..\\..\\Test\\TestVecs\\Config\\Testvecs.cfg";
#endif
#else
    xdc_Char *fname = "../../Test/TestVecs/Config/testvecs_linux.cfg";
#endif



    /* Base Class Structures                                                */
    Imp4VDEC_Status             status;
    Imp4VDEC_InArgs             inArgs;
    Imp4VDEC_OutArgs            outArgs;
    IRES_Status iresStatus;
#ifdef PROFILE_ONLINUX
    XDAS_UInt32 time_before_process, time_after_process;
    struct timeval decoder_time, *decoder_timeptr;
    static unsigned int frame_count_p, total_time_p;
#endif
    /* Algorithm specific handle                                            */
    IALG_Handle handle;

    /* HDVICP Framework related data declarations                           */
    HDVICP_Obj hdvicpObj;

    /* Input/Output Buffer Descriptors                                      */
    XDM1_BufDesc inputBufDesc;
    XDM_BufDesc  outputBufDesc;

    /* Handle to a buffer element allocated by the buffer manager module    */
    BUFFMGR_buffEleHandle buffEle;

    /* Other variables                                                      */
    XDAS_Int32  ii,frameCount, retVal, testVal, countConfigSet;
    /* Interrupt enable related function calls please refer to User
     * guide for a detailed description of these functions and the
     * DM360_IPC_INTC_ENABLE macro usage
     */
#ifdef ON_LINUX
    LockMP_init();
    SemMP_init();
    Memory_init();
#endif

#if DEBUG_LINUX
        printf("Started\n");
#endif

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
    //ARM926_Icache_Disable();
    //ARM926_Dcache_Disable();
#endif

#ifdef DM360_IPC_INTC_ENABLE
    /* Call the functions to enable ARM926 FIQ and do some basic setup to
     * AINTC to accept KLD INTC (arm968) interupt in FIQ pin of Arm926
     */
#ifndef ON_LINUX
    ARM926_enable_FIQ();  /* SWI call to enable interrupts                  */
    ARM926_INTC_init();   /* Init AINTC                                     */
#endif
#endif

#ifdef ON_LINUX
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_CACHED;
    memParams.alignment=256;
#endif

    /* Open Test Config File                                                */
    fConfigFile = fopen(fname,"r");
    if (!fConfigFile)
    {
        printf("Couldn't open parameter file %s",fname);
        return XDM_EFAIL;
    }

    //GT_init();
    //GT_create(&someGTMask, "ti.sdo.fc.rman.examples.dummyEdma3");
    //GT_set("*" "=01234567");


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
#endif

    countConfigSet = 0; /* Reset countConfigSet value to 1                  */

    /* Read the Config File until it reaches the end of file                */
    while(!feof(fConfigFile))
    {

        countConfigSet++;
#ifndef ONELINE_CONFIG
        /* Read Compliance Checking parameter                               */
        if(fgets(line,254,fConfigFile))
        {
          sscanf(line,"%d",&testCompliance);
        }
        else
        {
          break ;
        }
        /* Read Parameters file name                                        */
        if(fgets(line,254,fConfigFile))
        {
          sscanf(line,"%s",paramsFile);
        }
        else
        {
          break ;
        }
        /* Read Input file name                                             */
        if(fgets(line,254,fConfigFile))
        {
          sscanf(line,"%s",inFile);
        }
        else
        {
          break ;
        }
        /* Read Output/Reference file name                                  */
        if(fgets(line,254,fConfigFile))
        {
          sscanf(line,"%s",testFile);
        }
        else
        {
          break ;
        }
        printf("Output File name %s\n\n", testFile);

#ifdef TST_FRAME_MODE
        /* Read Frame size file name                                        */
        if(fgets(line,254,fConfigFile))
        {
            sscanf(line,"%s",sizeFile);
            fsizeFile = fopen (sizeFile, "rb");
            if(fsizeFile == NULL)
            {
                printf("\nCould not open Frame size file Exiting\n");
                continue ;
            }
        }
        else
        {
          break ;
        }
#endif /* TST_FRAME_MODE */
#else  /* ONELINE_CONFIG */
        /* Read Compliance Checking parameter                               */
        if(fscanf(fConfigFile,"%d",&testCompliance))
        {
            if(testCompliance == 2)
            {
                break;
            }
        }
        else
        {
            break;
        }
        /* Read Parameters file name                                        */
        if(!fscanf(fConfigFile,"%s",paramsFile))
        {
            break;
        }
        /* Read Input file name                                             */
        if(!fscanf(fConfigFile,"%s",inFile))
        {
            break;
        }
        /* Read Output/Reference file name                                  */
        if(!fscanf(fConfigFile,"%s",testFile))
        {
            break;
        }
        printf("Output File name %s\n\n", testFile);
#ifdef TST_FRAME_MODE
        if(!fscanf(fConfigFile,"%s",sizeFile))
        {
            break;
        }
        fsizeFile = fopen (sizeFile, "rb");
        if(fsizeFile == NULL)
        {
            printf("\nCould not open Frame size file Exiting\n");
            continue ;
        }
#endif  /* TST_FRAME_MODE */
        fgets(line,500,fConfigFile);
        if((testCompliance != 0) && (testCompliance != 1))
        {
            continue;
        }
#endif  /* ONELINE_CONFIG */
        printf("*******************************************\n");
        printf("Read Configuration Set %d\n", countConfigSet);
        printf("*******************************************\n");

        /*
         * Open Parameters file, and read the contents of parameters
         * related to the MPEG4 decoder codec.
         */
        fparamsFile = fopen (paramsFile, "rb");
        if(!fparamsFile)
        {
            printf("Couldn't open Parameters file...   %s\n", paramsFile);
            printf("Exiting for this configuration...\n");
            continue;
        }
        if(readparamfile(fparamsFile) < 0)
        {
            printf("Syntax Error in %s\n", paramsFile);
            printf("Exiting for this configuration...\n");
            continue;
        }
#if DEBUG_LINUX
    printf("Read Parameters done \n\n\n\n\n\n");
#endif
        /*
         * Close Parameters File after reading the contents of it.
         */
        //fclose(fparamsFile);
#if DEBUG_LINUX
    printf("********************Close done************ %s \n\n",testCompliance);
#endif

        if(testCompliance)
        {
          printf("Running in Compliance Mode\n");
        }
        else
        {
          printf("Running in Output Dump Mode\n");
        }

        /* Open output/reference file                                       */
        if(testCompliance)
        {
          ftestFile = fopen (testFile, "rb");

          chksum   = (XDAS_UInt8 *)(malloc(16));
          ref_byte = (XDAS_UInt8 *)(malloc(16));
        }
        else
        {
          printf("Output File name %s\n\n", testFile);
          ftestFile = fopen (testFile, "wb");
        }
        if( !ftestFile)
        {
          printf("Couldn't open Test File... %s",testFile);
          printf("\n Exiting for this configuration..." );
          continue;
        }

        /* Initialization of parameters needed for Algorithm  creation      */
        TestApp_SetInitParams(&params.viddecParams);
#if DEBUG_LINUX
    printf("TestApp_SetInitParams done %d \n\n");
#endif
        /* DMA initialization related calls - To initialise the structure with
         * exact DMA channels and number of EDMA param entries allocated for
         * the algorithms usage. This enables applciation to control the DMA
         * resource allocation to the algorithm.
         */
        //TestApp_SetDMAInitParams(&params.dmaParams);


        /* Setting the sizes of Base Class Objects                          */
        params.viddecParams.size     = sizeof(Imp4VDEC_Params);
        status.viddecStatus.size     = sizeof(Imp4VDEC_Status);
        inArgs.viddecInArgs.size     = sizeof(Imp4VDEC_InArgs);
        outArgs.viddecOutArgs.size                 = sizeof(Imp4VDEC_OutArgs);
        dynamicParams.viddecDynamicParams.size
                                     = sizeof(Imp4VDEC_DynamicParams);

        /* Initializing one input file processign specific variables        */
        frameCount                   = 0;
        bytesConsumed                = 0;
        reachedEndOfFile             = 0;
        fileOffset                   = 0;
        validBytes                   = 0;
        outArgs.viddecOutArgs.bytesConsumed        = 0;
        inputBufDesc.descs[0].buf    = inputData;


        /* HDVICP calls enables non-blockign implementation on the host
         * processor in a OS scenario with support for multi-thread/task
         * creations. hdvicpObj which will be part of the decoder instance.
         * All future calls to HDVICP module made by the algorithm will
         * contain this as the handle.HDVICP module initialises it suitably
         * to enable context identification is future calls.
         */
       //HDVICP_initHandle(&hdvicpObj);
        params.hdvicpHandle          = (void*) &hdvicpObj;

#ifdef XDM_RESET_TST
        if(countConfigSet == 1)
        {
#endif
        /* Create the Algorithm object (instance)                           */
        printf("\nCreating Algorithm Instance...");
        if ((handle =
              (IALG_Handle)mp4VDEC_create
                            (
                             (const Imp4VDEC_Fxns  *)&MPEG4VDEC_TI_IMPEG4VDEC,
                             (const Imp4VDEC_Params *) &params)) == NULL
                            )
        {
            printf("\nFailed to Create Instance Exiting this configuration");
            continue;
        }
        printf("\nAlgorithm Instance Creation Done...\n");

#ifdef _ENABLE_IRES_EDMA3
{
 int temp;
 temp = RMAN_assignResources((IALG_Handle)handle,
                                        &MPEG4VDEC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */);
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != temp) {
      printf( "\nFailed in assigning resources \
                 Exiting for this configuration..");
      goto EndOfFile;
    }
}
#endif



#ifdef XDM_RESET_TST
        }
#endif
    /**********************************************************************/
    /* Activate all IRES resources                                        */
    /**********************************************************************/
    MPEG4VDEC_TI_IRES.activateAllResources((IALG_Handle)handle);

        printf("Started decoding Test File %s\n",inFile);

        /* Initialise the buffer manager with sufficient buffer size for
         * output and reference frames the value specified here is dependent
         * on theprofile and level supported
         */
        BUFFMGR_Init(MAX_IN_BUF_SIZE);

        /* Initialization of parameters needed for Algorithm control call
         * Refer to user guide for detailed description fo each of the member
         * variables of dynamicParams
         */
        TestApp_SetDynamicParams(&dynamicParams);

        /* Control call for Get Buffer Sizes                                */
        mp4VDEC_control((Imp4VDEC_Handle)handle,
                         XDM_GETBUFINFO,
                        (Imp4VDEC_DynamicParams *)&dynamicParams,
                        (Imp4VDEC_Status *)&status
                       );

        /* Fill up the input buffer values and pointers. Please note that at
         * this stage picture size is still unknown hence default picture size
         * of PAL-D1 is assumed internally by the control API. This default
         * picture size is used initialise minimum input and output buffers.
         */
        inputBufDesc.numBufs          =
                                    status.viddecStatus.bufInfo.minNumInBufs ;
        inputBufDesc.descs[0].bufSize =
                                  status.viddecStatus.bufInfo.minInBufSize[0];
        for(ii=0; ii<(status.viddecStatus.bufInfo.minNumInBufs-1);ii++ )
        {
            inputBufDesc.descs[ii+1].buf     = inputBufDesc.descs[ii].buf +
                                 status.viddecStatus.bufInfo.minInBufSize[ii];
            inputBufDesc.descs[ii+1].bufSize =
                              status.viddecStatus.bufInfo.minInBufSize[ii +1];
        }
#ifdef _PROFILE_
        printf("------------------------------------------------------\
----------------------------------------------\n");
        printf(" | Frame Num | PreP Cycles | ARM968 cycles | PostP cycles\
|    Total    | fps For D1 |  EC Applied | \n");
        printf("------------------------------------------------------\
----------------------------------------------\n");
#endif

        /* Do-While Loop for Decode Call                                    */
        do
        {
            XDAS_UInt32 header_decode_done;

            /* Setting of input arguments                                   */
            inArgs.viddecInArgs.inputID = 0;
            /* Assign the number of bytes available                         */
            inArgs.viddecInArgs.numBytes= validBytes;
            /* Read the bitstream in the Application Input Buffer. validBytes
             * would be initialised with the actual number of bytes read from
             * the input file
             */
#ifndef TST_FRAME_MODE
            validBytes = TestApp_ReadByteStream(inFile);
#else
            validBytes = TestApp_ReadByteStream(inFile,fsizeFile,frameCount);
#endif
            MEMUTILS_cacheWb(inputBufDesc.descs[0].buf,inArgs.viddecInArgs.numBytes);
            if(validBytes <= 0)
            {
                break;
            }

            /* Assign the number of bytes available                         */
            inArgs.viddecInArgs.numBytes  = validBytes;
            inputBufDesc.descs[0].bufSize = validBytes;
#ifndef TST_FRAME_MODE
            inputBufDesc.descs[0].buf   = (XDAS_Int8 *)((XDAS_Int32)
                                                   inputData + bytesConsumed);
#else
            inputBufDesc.descs[0].buf   = (XDAS_Int8 *)((XDAS_Int32)
                                                   inputData);
#endif
            /* Get a handle to the available buffer from the buffer manager.
             * buffEle would be NULL incase no buffer are free. buffEle is
             * used to initialise the output buffer descriptor structure for
             * next process call
             */
            buffEle = BUFFMGR_GetFreeBuffer();
            /* Fill up the output buffer values and pointers                */
            outputBufDesc.numBufs           = 2;
            outputBufDesc.bufSizes          = (XDAS_Int32 *) buffEle->bufSize;
            outputBufDesc.bufs              = (XDAS_Int8 **) buffEle->buf;
            inArgs.viddecInArgs.inputID     = buffEle->bufId;
            dynamicParams.outloopDeblocking = DEBLOCK;
            dynamicParams.outloopDeRinging  = DERING;
            dynamicParams.resetHDVICPeveryFrame  = RESET_HDVICP_EVERY_FRAME;

            /* Optional: Set Run time parameters in the Algorithm           */
            mp4VDEC_control((Imp4VDEC_Handle)handle,
                             XDM_SETPARAMS,
                            (Imp4VDEC_DynamicParams  *)&dynamicParams,
                            (Imp4VDEC_Status *)&status
                           );
#ifndef _PROFILE_
            printf("#:%-4d", frameCount);
#endif
            fflush(stdout);
#ifdef _PROFILE_
    profileInit(0);
    profileStart(0);
#endif

#ifdef PROFILE_ONLINUX
            decoder_timeptr = &decoder_time;
            time_before_process = gettimeofday(decoder_timeptr, NULL);
        time_before_process = decoder_timeptr->tv_usec;
            //printf("time before = %d\n",decoder_timeptr->tv_usec);
#endif
            /* Basic Algorithm process() call to decode a frame             */
            retVal = mp4VDEC_decode((Imp4VDEC_Handle)handle,
                                    (XDM1_BufDesc *)&inputBufDesc,
                                    (XDM_BufDesc *)&outputBufDesc,
                                    (Imp4VDEC_InArgs *)&inArgs,
                                    (Imp4VDEC_OutArgs *)&outArgs
                                   );

#ifdef PROFILE_ONLINUX
            time_after_process = gettimeofday(decoder_timeptr, NULL);
            //printf("time After = %d\n",decoder_timeptr->tv_usec);
            //printf("time before = %d, time after = %d\n",time_before_process,time_after_process);
        if(decoder_timeptr->tv_usec <= time_before_process)
        {

            decoder_timeptr->tv_usec += 1000000;
        }
        printf("\nARM926_TIME = %d",(decoder_timeptr->tv_usec - time_before_process));
        printf("ARM926_TIME = %d\n",arm968_time);
#endif


#ifdef _PROFILE_
        ARM926cycles = profileEnd(0);
        printf("%6d -", frameCount);
        printf("%2d", outArgs.viddecOutArgs.displayBufs[0].frameType);
        printf("%13d",ARM968cycles0);
        printf("%15d",(ARM968cycles1 - ARM968cycles0));
        printf("%15d",(ARM926cycles - ARM968cycles1));
        printf("%15d",ARM926cycles);
        {
            XDAS_UInt32 DecMbWidth,DecMbHeight;
            XDAS_UInt32 MBCycles, fps;
            DecMbWidth =
            (outArgs.viddecOutArgs.displayBufs[0].frameWidth >> 4) ;
            DecMbHeight =
            (outArgs.viddecOutArgs.displayBufs[0].frameHeight >> 4);
            MBCycles = (ARM926cycles / (DecMbWidth * DecMbHeight));
            fps      = (CLOCK_SEC / (MBCycles * 45 * 30));
            printf("%12d",fps);
        }
        if(outArgs.viddecOutArgs.displayBufs[0].extendedError & 0x200)
        {
            printf("           Y\n");
        }
        else
        {
            printf("           N\n");
        }

#endif
            header_decode_done = 1;
           /* Check for return value of the process call. Please note
            * that when the decoder instance is in XDM_FLUSH mode
            * end-of-decode i.e emptying of picture buffer of all the
            * previously decoded frames is indicated by returning error.
            * hence if the process call returns error all we need to do
            * is break out of the do-while loop if inFlushModeFlag is TRUE
            */
            if(retVal == XDM_EFAIL)
            {
                BUFFMGR_ReleaseBuffer(
                            (XDAS_UInt32 *)outArgs.viddecOutArgs.freeBufID
                                 );
                mp4VDEC_control((Imp4VDEC_Handle)handle,
                XDM_GETSTATUS,
                (Imp4VDEC_DynamicParams *)&dynamicParams,
                (Imp4VDEC_Status *)&status);
                printf("\n Process function returned an Error : %x\n",
                                           status.viddecStatus.extendedError);
                /* If header not found in DECODE_AU mode then continue looking for header */
                if(status.viddecStatus.extendedError & 0x7F == IMPEG4VDEC_EX_ERR_HEADER_NOT_FOUND)
                {
                    header_decode_done = 0;
                }
            }

            bytesConsumed          += outArgs.viddecOutArgs.bytesConsumed;
            validBytes             -= outArgs.viddecOutArgs.bytesConsumed;
#ifdef _STR_CUT_
            if((frameCount == 0) ||(frameCount == 60))
            {
                if(frameCount == 0)
                {
                    fp = fopen("..\\..\\..\\Test\\TestVecs\\input\\mask_WCDMA_64KB_211HZ_3_VER2_akiyo.263","wb");
                    fwrite(inputData,1,outArgs.viddecOutArgs.bytesConsumed,fp);
                    fflush (fp);
                }
                else
                {
                    fwrite(inputData,1,(outArgs.viddecOutArgs.bytesConsumed+1000),fp);
                    fflush (fp);
                    fclose(fp);
                    break;
                }
            }
#endif
#ifndef _PROFILE_
            printf(": %1d", outArgs.viddecOutArgs.displayBufs[0].frameType);
            printf(" : BytesConsumed :%6d",outArgs.viddecOutArgs.bytesConsumed);
#endif
            if((frameCount == 0) && (header_decode_done == 1))
            {
#ifndef _PROFILE_
                printf(" :\n",frameCount);
#endif
                mp4VDEC_control((Imp4VDEC_Handle)handle,
                XDM_GETBUFINFO,
                (Imp4VDEC_DynamicParams *)&dynamicParams,
                (Imp4VDEC_Status *)&status);
               /* Use the above exact luma and chroma buffer reuqirements
                * for the input bit-stream to re-initialise the buffer manager.
                * refer to buffermanager specific XDM v1.0 intergation doc
                * for more details.
                */
                BUFFMGR_ReInit(status.viddecStatus.bufInfo.minOutBufSize[0],
                           status.viddecStatus.bufInfo.minOutBufSize[1]);
            }
            /* Always release buffers - which are released from teh algorithm
             * side   -back to the buffer manager
             */
            if(retVal != XDM_EFAIL)
            {
                BUFFMGR_ReleaseBuffer(
                            (XDAS_UInt32 *)outArgs.viddecOutArgs.freeBufID
                                 );
            }
            /* Check for frame ready via display buffer pointers            */
            if(outArgs.viddecOutArgs.outputID[0] != 0)
            {
                if(testCompliance)
                {

#if 1
                    void   *Base_ptr;

                    /* This code generates the checksum 16 Bytes Luma followed */
                    /* by 16 Bytes of Chroma */
                    /* Luma */
                    Base_ptr = outArgs.viddecOutArgs.displayBufs[0].bufDesc[0].buf;

                    Calculate_MD5_CkSum_buf(Base_ptr,
                                            outArgs.viddecOutArgs.displayBufs[0].frameWidth,
                                            outArgs.viddecOutArgs.displayBufs[0].framePitch,
                                            outArgs.viddecOutArgs.displayBufs[0].frameHeight,
                                            chksum);

                    fread(ref_byte, 1, 16, ftestFile);
                    if(*ref_byte == *chksum)
                        testVal = 1;
                    else
                        testVal = 0;

                    /* Chroma */
                    Base_ptr = outArgs.viddecOutArgs.displayBufs[0].bufDesc[1].buf;
                    Calculate_MD5_CkSum_buf(Base_ptr,
                                            outArgs.viddecOutArgs.displayBufs[0].frameWidth,
                                            outArgs.viddecOutArgs.displayBufs[0].framePitch,
                                            outArgs.viddecOutArgs.displayBufs[0].frameHeight>>1,
                                            chksum);
                    fread(ref_byte, 1, 16, ftestFile);
                    if(*ref_byte == *chksum)
                        testVal = 1;
                    else
                        testVal = 0;

                    if(testVal == 1)
                    {
                        printf(" : Passed\n");
                    }
                    else
                    {
                        /* Test Compliance Failed... Breaking...            */
                        printf("************Failed*************\n");
                        break;
                    }

#else
                    testVal = TestApp_CompareOutputData
                                            (ftestFile, 0, &outArgs,
                                            status.viddecStatus.outputHeight,
                                            status.viddecStatus.outputWidth
                                            );

                    if(testVal == 1)
                    {
                        printf(" : Passed\n");
                    }
                    else
                    {
                        /* Test Compliance Failed... Breaking...            */
                        printf("************Failed*************\n");
                        break;
                    }

#endif
                }
                else
                {

#ifndef _PROFILE_
                printf(" :\n",frameCount);
#endif
                    if(frameCount >= DumpFrom)
                    {
                    /* Write the output frames in the display order         */
                    TestApp_WriteOutputData(ftestFile, 0, &outArgs,
                                            status.viddecStatus.outputHeight,
                                            status.viddecStatus.outputWidth
                                            );
                    }
                }
                MEMUTILS_cacheInv(outArgs.viddecOutArgs.displayBufs[0].bufDesc[0].buf,
                                  outArgs.viddecOutArgs.displayBufs[0].bufDesc[0].bufSize);
                MEMUTILS_cacheInv(outArgs.viddecOutArgs.displayBufs[0].bufDesc[1].buf,
                                  outArgs.viddecOutArgs.displayBufs[0].bufDesc[1].bufSize);

            }
            frameCount++;

            /* NUM_FRAMES is added for debug purpose. During complete testing
             * this can be read fron parameter file into framesToDecode.The
             * following code to be modified as (frameCount >= framesToDecode)
             */
            if (frameCount >= framesToDecode)
            {
                printf("\n Specified number of Frames Decoded...  ");
                break; /* Bitstream ended: Break off the while loop         */
            }

        }  while(1);  /* end of Do-While loop                               */

        while(1)
        {
            /* Optional: Set Run time parameters in the Algorithm           */
            mp4VDEC_control((Imp4VDEC_Handle)handle,
                             XDM_FLUSH,
                            (Imp4VDEC_DynamicParams  *)&dynamicParams,
                            (Imp4VDEC_Status *)&status
                           );

            /* Basic Algorithm process() call to decode a frame             */
            retVal = mp4VDEC_decode((Imp4VDEC_Handle)handle,
                                    (XDM1_BufDesc *)&inputBufDesc,
                                    (XDM_BufDesc *)&outputBufDesc,
                                    (Imp4VDEC_InArgs *)&inArgs,
                                    (Imp4VDEC_OutArgs *)&outArgs
                                   );
           /* Check for return value of the process call. Please note
            * that when the decoder instance is in XDM_FLUSH mode
            * end-of-decode i.e emptying of picture buffer of all the
            * previously decoded frames is indicated by returning error.
            * hence if the process call returns error all we need to do
            * is break out of the do-while loop if inFlushModeFlag is TRUE
            */
            if(retVal == XDM_EFAIL)
            {
                break; /* Error Condition: application may want to break    */
            }
            if(outArgs.viddecOutArgs.outputID[0] != 0)
            {
                if(testCompliance)
                {
                    /* Compare the output frames with the Reference File    */
                }
                else
                {

                    if(frameCount >= DumpFrom)
                    {
                    /* Write the output frames in the display order         */
                    TestApp_WriteOutputData(ftestFile, 0, &outArgs,
                                            status.viddecStatus.outputHeight,
                                            status.viddecStatus.outputWidth
                                            );
                    }
                }

            }
        }
EndOfFile:
        /* Output file close                                                */
        fclose(ftestFile);
#ifdef TST_FRAME_MODE
        fclose(fsizeFile);
#endif

//#ifndef ON_LINUX
//#endif



#ifdef XDM_RESET_TST
        mp4VDEC_control((Imp4VDEC_Handle)handle,
        XDM_RESET,
        (Imp4VDEC_DynamicParams *)&dynamicParams,
        (Imp4VDEC_Status *)&status);
#endif
#ifndef XDM_RESET_TST
#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
     {
     int temp;

     temp = RMAN_freeResources((IALG_Handle)(handle),
                                        &MPEG4VDEC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */);
    if (IRES_OK != temp) {
        printf("Free Resource Failed \n");
        //return -1;
    }
    }
#endif

        /* Delete the Algorithm instance object specified by handle */
        mp4VDEC_delete ((Imp4VDEC_Handle)handle);
#endif
        if(frameCount == 0)
        {
            frameCount = 1; /* To avoid division with zero                  */
        }

        printf("\n --------------  SUMMARY --------------------\n");
        if(!testCompliance)
        {
            printf(" Decoder output dump completed\n");
        }
        printf("\t Total number of Frames              = %d\n",
          (XDAS_UInt32)frameCount);
        printf("\t Bit Rate at 30 frames/Sec           = %d Kbps\n",
          (XDAS_UInt32)(((bytesConsumed*8*30)/frameCount)/1000));
        printf("\t Width and Height                    = %d, %d \n",
          (XDAS_UInt32)outArgs.viddecOutArgs.displayBufs[0].frameWidth,
          (XDAS_UInt32)outArgs.viddecOutArgs.displayBufs[0].frameHeight);
        printf (" --------------    END   --------------------\n");

        /* Free the application external memory allocated for supplying to
         * decoder to hold decoded frame.
         */
        BUFFMGR_DeInit();
  } /* Read the Config File until it reaches the end of file                */
#ifdef XDM_RESET_TST
#ifdef _ENABLE_IRES_EDMA3
    /*
     * Free resources assigned to this algorihtm
     */
     {
     int temp;

     temp = RMAN_freeResources((IALG_Handle)(handle),
                                        &MPEG4VDEC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */);
    if (IRES_OK != temp) {
        printf("Free Resource Failed \n");
        //return -1;
    }
    }
#endif

    /* Delete the Algorithm instance object specified by handle */
    mp4VDEC_delete ((Imp4VDEC_Handle)handle);
#endif
#ifdef ON_LINUX
    /* De-Initialization */
    CMEM_free(inputData, &memParams);
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
  printf("\n End of execution\n");
  /* Close the config files                                                 */
  fclose(fConfigFile);
#ifdef ENABLE_CACHE
  ARM926_Icache_Disable();
  ARM926_Dcache_Disable();
#endif
  return XDM_EOK;
} /* main() */



/* ===========================================================================
 *  @func   TestApp_ReadByteStream()
 *
 *  @desc   Sample utility function for reading encoded bit-stream in chunks.
 *          The input file is opened every time and next
 *          "INPUT_BUFFER_SIZE - validBytes" number of bytes is read into the
 *          input buffer. End-of-file if encountered in previous runs is
 *          remebered for given input config record.
 *
 *  @param  XDAS_Int8 *inFile:
 *          Input file name as a null-terminated array of characters.
 *
 *  @return TotalBytes in the input bit-stream : If successfully read.
 *          -1: If encountered error in reading the input file.
 *
 *  @note   None
 * ===========================================================================
 */
#ifndef TST_FRAME_MODE
XDAS_Int32 TestApp_ReadByteStream(xdc_Char *inFile)
{
    XDAS_UInt32 BytesRead, BufferSize, Index;
    FILE  *finFile;

    /* If end-of-file had already been encountered for this config
     * record, then just return the remainign bytes in the input
     * bit-stream.
     */
    if(reachedEndOfFile)
    {
        return validBytes;
    }
    /* Open input file                                                      */
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
    /* Shift data from lower-half to upper part                             */
    for(Index = 0; Index < validBytes; Index++)
    {
        inputData[Index] = inputData[bytesConsumed + Index];
    }
    bytesConsumed = 0;
    BufferSize = INPUT_BUFFER_SIZE - validBytes;

    /* Read the "BufferSize" number of bytes in the input buffer
     * The line of code is commented for the time being
     */
    BytesRead  = fread (&inputData[validBytes], 1, BufferSize, finFile);

    /* Store the exact pointer in the input file for next read.
     * fileOffset is also used to keep track of total file size
     * processed at any given instant. Its used to calculate the
     * bit-rate of the input file as well at the end of decoding
     */
    fileOffset = ftell(finFile);
    fclose(finFile);
   /* Determine end-of-file condition                                       */
   if (BytesRead != BufferSize)
    {
        reachedEndOfFile = 1;
    }
    /* Return total bytes available for further decoding                    */
    return (validBytes + BytesRead);
} /* TestApp_ReadByteStream() */
#else
XDAS_Int32  TestApp_ReadByteStream
(
    xdc_Char *inFile,
    FILE      *fsizeFile,
    XDAS_Int32 frameCount
)
{
    XDAS_UInt32 tempval,BytesRead;
    XDAS_UInt32 frameSizeOffset = 0;
    XDAS_UInt32 frameSizeVal    = 0;

    FILE  *finFile;
    /* Open input file                                                      */
    finFile = fopen (inFile, "rb");
    if (!finFile)
    {
        printf("\n Couldn't open Input file...  %s  ",inFile);
        printf("\n Exiting for this configuration...");
        return -1;
    }
    if(!feof(fsizeFile))
    {
        if(frameCount == 0)
        {
            fscanf (fsizeFile,"%ld", &frameSizeOffset) ;
            fscanf (fsizeFile,"%ld", &frameSizeVal) ;
            tempval = frameSizeVal;
        }
        fscanf (fsizeFile,"%ld", &frameSizeOffset) ;
        fscanf (fsizeFile,"%ld", &frameSizeVal) ;
        if(frameCount == 0)
        {
           frameSizeVal += tempval ;
           fseek (finFile, 0, SEEK_SET) ;
        }
        else
        {
            fseek (finFile, frameSizeOffset, SEEK_SET) ;
        }
        if (frameSizeOffset == 0 && frameSizeVal == 0)
        {
            fclose(finFile);
            return -1;
        }
        BytesRead  = fread (&inputData[0], 1, frameSizeVal, finFile);
        fclose(finFile);
       /* Determine end-of-file condition                                  */
        if (BytesRead != frameSizeVal)
        {
            return -1;
        }
        /* Return total bytes available for further decoding               */
        return (BytesRead);
    }
    else
    {
            return -1;
    }

} /* TestApp_ReadByteStream() */
#endif


/* ===========================================================================
 *  @func   TestApp_CompareOutputData()
 *
 *  @desc   Currently this file dosen't have this feature.Need to add
 *
 *  @note   None
 * ===========================================================================
 */
XDAS_Int32 TestApp_CompareOutputData
(

    FILE             * fOutFile,
    XDAS_Int32         display_marker,
    Imp4VDEC_OutArgs * outArgs,
    XDAS_Int32         height,
    XDAS_Int32         width
)
{

  return 1;
} /* TestApp_CompareOutputData() */



/* ===========================================================================
 *  @func   TestApp_WriteOutputData()
 *
 *  @desc   Sample utility function for dumping encoded bit-stream. Before
 *          writing raw YUV data packed and interleaved chroma data is
 *          seperated into a seperate buffer.
 *
 *  @param  FILE *fOutFile:
 *          Output file pointer
 *
 *  @param  XDAS_Int32 display_marker:
 *          Index into the display buffer array which is marked for
 *          display.
 *
 *  @param  IVIDDEC2_OutArgs *outArgs:
 *          OutArgs structure containing display buffer array and thier
 *          properties like picture pitch, heigth and width.
 *
 *  @param  XDAS_Int32  height:
 *          Height of the displayed picture in pixels.
 *
 *  @param  XDAS_Int32  width:
 *          Width of the displayed picture in pixels.
 *
 *  @return None.
 *
 *  @note   None
 * ===========================================================================
 */
XDAS_Void TestApp_WriteOutputData
(
    FILE             * fOutFile,
    XDAS_Int32         display_marker,
    Imp4VDEC_OutArgs * outArgs,
    XDAS_Int32         height,
    XDAS_Int32         width
)
{

XDAS_Int32 pic_size;

    XDAS_Int32 i, j;
    XDAS_UInt8 *src,*dst1, *dst2;

    XDAS_Int8  *CbCr_seperate[2]; /* Pointers to hold seperated Cb and Cr   */
    XDAS_Int8  *Luma_data;
    XDAS_Int8 * Luma_outP = Luma_out;

    /* Picture size in pixels for luma                                      */
    pic_size = outArgs->viddecOutArgs.displayBufs[0].frameWidth *
               outArgs->viddecOutArgs.displayBufs[0].frameHeight;
    /* Base address of luma data from the output bufffer given by decoder   */
    Luma_data = outArgs->viddecOutArgs.displayBufs[0].bufDesc[0].buf;

    /* Running the loop over number of line in the picture to dump the output
     * to file.In case of CRC calculation mode (CRC_DUMP defined) luma data of
     * each pixel copied to a local buffer.
     */

    for(height= 0; height < outArgs->viddecOutArgs.displayBufs[0].frameHeight;
                                                                    height++)
    {

        if(CrcNyuv == 0)
        {
            fwrite (Luma_data, sizeof (char),
                 outArgs->viddecOutArgs.displayBufs[0].frameWidth, fOutFile);
        }
        else
        {
            memcpy(Luma_outP,Luma_data,
                            outArgs->viddecOutArgs.displayBufs[0].frameWidth);
            Luma_outP += outArgs->viddecOutArgs.displayBufs[0].frameWidth;
        }
        Luma_data += outArgs->viddecOutArgs.displayBufs[0].framePitch;
    }

    /* Init output yuv_buffer with global pointers                          */
    CbCr_seperate[0] = Chroma_seperate;
    CbCr_seperate[1] = CbCr_seperate[0] + (pic_size>> 2);
    src              =
           (XDAS_UInt8 *)outArgs->viddecOutArgs.displayBufs[0].bufDesc[1].buf;
    dst1             = (XDAS_UInt8 *)CbCr_seperate[0];
    dst2             = (XDAS_UInt8 *)CbCr_seperate[1];

    /* The following code is itrated Chroma picture size in pixel times to
     * separate the interleved Cb and Cr
     */
    for(j = 0;j < (outArgs->viddecOutArgs.displayBufs[0].frameHeight>>1);j++)
    {
        for(i = 0;i<(outArgs->viddecOutArgs.displayBufs[0].frameWidth>>1);i++)
        {
            dst1[i] = src[i*2];
            dst2[i] = src[(i*2) + 1];
        }
        src  += outArgs->viddecOutArgs.displayBufs[0].framePitch;
        dst1 += (outArgs->viddecOutArgs.displayBufs[0].frameWidth>>1);
        dst2 += (outArgs->viddecOutArgs.displayBufs[0].frameWidth>>1);
    }

    if(CrcNyuv == 0)
    {
        /* Write the saperated out CB and CR in to YUV output file          */
        fwrite (CbCr_seperate[0], sizeof (char),pic_size>>2,fOutFile);
        fwrite (CbCr_seperate[1], sizeof (char),pic_size>>2,fOutFile);
    }

    fflush (fOutFile);


  return;
} /* TestApp_WriteOutputData() */



/* ===========================================================================
 *  @func   TestApp_SetInitParams()
 *
 *  @desc   Initalizes the init parameter structure with proper values
 *
 *  @param  IVIDDEC2_Params *param
 *          Init parameter structure..
 *
 *  @return None
 *
 *  @note   None
 * ===========================================================================
 */
XDAS_Void TestApp_SetInitParams(IVIDDEC2_Params *params)
{
    /* Set IVIDDEC2 parameters                                              */
    /* Max Frame Rate: Not currently used in the algorithm                  */
    params->maxFrameRate        = 300000;
    /* Max Bit Rate: Not currently used in the algorithm                    */
    params->maxBitRate          = 10000000;
    /* Data Endianness (1: Big) : only Big Endian supported                 */
    params->dataEndianness      = XDM_BYTE;
    return;
} /* TestApp_SetInitParams() */



/* ===========================================================================
 *  @func   TestApp_SetDynamicParams()
 *
 *  @desc   Initalizes the Dynamic parameter structure with proper values
 *
 *  @param  Imp4VDEC_DynamicParams *dynamicParams
 *          Dynamic parameter structure..
 *
 *  @return None
 *
 *  @note   None
 * ===========================================================================
 */
XDAS_Void TestApp_SetDynamicParams(Imp4VDEC_DynamicParams *dynamicParams)
{
    /* Set IVIDDEC2 Run time parameters */
    dynamicParams->viddecDynamicParams.decodeHeader  = XDM_DECODE_AU;
    //dynamicParams->viddecDynamicParams.displayHeight = 0;
    dynamicParams->viddecDynamicParams.displayWidth  = 0;
    dynamicParams->viddecDynamicParams.frameOrder    = 0 ;
    dynamicParams->viddecDynamicParams.frameSkipMode = IVIDEO_NO_SKIP;
    dynamicParams->viddecDynamicParams.mbDataFlag    = 0;
    dynamicParams->viddecDynamicParams.newFrameFlag  = 0;
    return;
}/* TestApp_SetDynamicParams() */



/*!
 *! Revision History
 *! ================
 *! 08-Oct-2007   Kumar    : Added the support for frame mode input handling.
 *! 16-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth:  Created.
 *!
 */

