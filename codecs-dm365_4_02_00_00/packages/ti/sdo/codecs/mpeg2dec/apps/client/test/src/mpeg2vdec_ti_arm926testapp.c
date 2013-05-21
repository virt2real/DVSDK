/** ==========================================================================
 *  @file  mpeg2vdec_ti_arm926testapp.c
 *
 *  @path   $(PROJDIR)\Src
 *
 *  @desc   This is the top level client file that drives the MPEG2
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
/* ------------------------- program files -------------------------------- */
/* Mpeg-4 Interface header files */
#include "imp2vdec_tii.h"
#include "mpeg2vdec_ti_arm926testapp.h"
//#include "edma_dm510.h"
#include "buffermanager.h"
#include "hdvicp_framework.h"
#include "testapp_arm926intc.h"
//#include "mpeg2vdec_ti_misc.h"
//#include "mpeg2vdec_ti_ialg.h"

//#define PROFILE_ONLINUX

#ifdef PROFILE_ONLINUX
#include <sys/time.h>
extern int arm968_time;
#endif

#ifdef DEVICE_ID_CHECK
/* Link modules used for DEVICE ID check */
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>
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

Imp2VDEC_Params             params;

Imp2VDEC_DynamicParams      dynamicParams;

extern IRES_Fxns MPEG2VDEC_TI_IRES;
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
  //{"ResetvIMCOPEveryFrame",   &params.reset_HDVICP_every_frame},
  {"display_delay",           &params.display_delay},
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

/*---------------------------------------------------------------------------*/
/*  Redirecting the input and reference data buffers to appropriate data     */
/*  sections in external memory.                                             */
/*---------------------------------------------------------------------------*/
#pragma    DATA_SECTION(inputData, ".input_buffer")
#pragma    DATA_SECTION(refData,   ".ref_buffer")


/* ------------------------- DATA DECLARATIONS ------------------------------*/

/*---------------------------------------------------------------------------*/
/*  Input buffer allocation                                                  */
/*---------------------------------------------------------------------------*/
//XDAS_Int8                   inputData[INPUT_BUFFER_SIZE];

/*---------------------------------------------------------------------------*/
/*  Reference data buffer allocation. This is required for test compliance   */
/*  mode which is currently not supported.                                   */
/*---------------------------------------------------------------------------*/
XDAS_Int8                   refData[OUTPUT_BUFFER_SIZE];

/*---------------------------------------------------------------------------*/
/*  Temporary buffer allocation used while separating chroma CB and CR for   */
/*  writing to file.                                                         */
/*---------------------------------------------------------------------------*/
XDAS_Int8                   Chroma_separate[DISPLAY_YUV_SIZE];

/* --------------------- function prototypes ------------------------------ */
/*--------------------------- FUNCTION PROTOTYPES ---------------------------*/
/*---------------------------------------------------------------------------*/
/*  Function used for separating interleaved CB/CR chroma pixels before file */
/*  write of display frame takes place.                                      */
/*---------------------------------------------------------------------------*/
static void separateCbCrPixels
(
      XDAS_Int8  *CbCr_data,
      XDAS_Int8  *Chroma_buf[2],
      XDAS_Int32  height,
      XDAS_Int32  width,
      XDAS_Int32  pitch
);

/* ---------------------------- macros ------------------------------------ */
/* The maximum external memory required for supplying input buffers to the
 * decoder process call by the buffer manager. The value is calculated as
 * following (720 + 48) * (576 + 32) * 1.5 * 3
 * full HD   (1920 + 48)* (1088 + 32)* 1.5 * 3
 * HD		 (1280 + 48)* (720 + 32) * 1.5 * 3
 */
//#define     MAX_IN_BUF_SIZE         2101248
//#define     MAX_IN_BUF_SIZE         4493952
#define     MAX_IN_BUF_SIZE         (IMAGE_WIDTH+48) * (IMAGE_HEIGHT+32) * 1.5 * 3

volatile int MPEG2VDEC_TI_scratchId = -1; /* Assign scratch Id for MPEG2VDEC.
                                  -1 for No Scratch Sharing */


/* The macro to enable or disable Out-loop de-blocking filter for post
 * processing.
 */
#define     DEBLOCK                 0

/* The macro to enable or disable Out-loop De-Ringing filter for post
 * processing.
 */
#define     DERING                  0

/* Processer running frequency                                              */
#ifndef _ENABLE_IRES_EDMA3
	#define _ENABLE_IRES_EDMA3
#endif
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
    XDAS_Int8 line[2*STRING_SIZE], inFile[STRING_SIZE], testFile[STRING_SIZE];
    XDAS_Int8 paramsFile[STRING_SIZE];
    XDAS_Int32  testCompliance;
    XDAS_UInt8 *chksum, *ref_byte;
    FILE *mb_data_fp;

    XDAS_UInt32	mb_data_size;

#ifdef TST_FRAME_MODE
    XDAS_Int8 sizeFile[STRING_SIZE];
    FILE *fsizeFile;
#endif
#ifdef _STR_CUT_
    FILE * fp;
#endif
#ifndef ON_LINUX
#ifdef ONELINE_CONFIG
    XDAS_Int8 *fname = (XDAS_Int8 *) "..\\..\\..\\test\\testvecs\\config\\Testvecs1.cfg";
#else
    XDAS_Int8 *fname =(XDAS_Int8 *) "..\\..\\..\\test\\testvecs\\config\\Testvecs.cfg";
#endif
#else
    XDAS_Int8 *fname = (XDAS_Int8 *)"../../test/testvecs/Config/testvecs_linux.cfg";
#endif

	  /*-------------------------------------------------------------------------*/
	  /*  Base Class Structures for status, input and output arguments.          */
	  /*-------------------------------------------------------------------------*/
	  Imp2VDEC_Status             status;
	  IVIDDEC2_InArgs             inArgs;
	  IVIDDEC2_OutArgs            outArgs;

    IRES_Status iresStatus;
#ifdef PROFILE_ONLINUX
    XDAS_UInt32 time_before_process, time_after_process;
    struct timeval decoder_time, *decoder_timeptr;
    static unsigned int frame_count_p, total_time_p;
#endif
    /* Algorithm specific handle                                            */
    IALG_Handle handle;


    /* Input/Output Buffer Descriptors                                      */
    XDM1_BufDesc inputBufDesc;
    XDM_BufDesc  outputBufDesc;

    /* Handle to a buffer element allocated by the buffer manager module    */
    BUFFMGR_buffEleHandle buffEle;
	XDAS_Int32 outBufsInUseFlag;
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
    fConfigFile = fopen((const char *)fname,"r");
    if (!fConfigFile)
    {
        printf("Couldn't open parameter file %s",fname);
        return XDM_EFAIL;
    }

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

   /*
		IRESMAN_VicpParams configParams;

		  Supply initialization information for the RESMAN while registering

		configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
		configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
		configParams.baseConfig.size = sizeof(IRESMAN_VicpParams);

		 Register the VICP protocol/resource manager with the
		 generic resource manager
		iresStatus = (IRES_Status)RMAN_register(&IRESMAN_VICP2,
												(IRESMAN_Params *)&configParams);

		if (IRES_OK != iresStatus) {
			printf("VICP Protocol Registration Failed \n");
			return -1;
	*/


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
        if(fgets((char *)line,254,fConfigFile))
        {
          sscanf((const char *)line,"%d",&testCompliance);
        }
        else
        {
          break ;
        }
        /* Read Parameters file name                                        */
        if(fgets((char *)line,254,fConfigFile))
        {
          sscanf((const char *)line,"%s",paramsFile);
        }
        else
        {
          break ;
        }
        /* Read Input file name                                             */
        if(fgets((char *)line,254,fConfigFile))
        {
          sscanf((const char *)line,"%s",inFile);
        }
        else
        {
          break ;
        }
        /* Read Output/Reference file name                                  */
        if(fgets((char *)line,254,fConfigFile))
        {
          sscanf((const char *)line,"%s",testFile);
        }
        else
        {
          break ;
        }
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
         * related to the MPEG2 decoder codec.
         */
        fparamsFile = fopen ((const char *)paramsFile, "rb");
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
//        fclose(fparamsFile);
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
          ftestFile = fopen ((const char *)testFile, "rb");
          chksum   = (XDAS_UInt8 *)(malloc(16));
          ref_byte = (XDAS_UInt8 *)(malloc(16));
        }
        else
        {
          ftestFile = fopen ((const char *)testFile, "wb");
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

        memset(&outArgs, 0, sizeof(IVIDDEC2_OutArgs));

	    /*-----------------------------------------------------------------------*/
	    /*  Setting the sizes of Base Class Objects                              */
	    /*-----------------------------------------------------------------------*/
	    params.viddecParams.size               = sizeof(IVIDDEC2_Params);
	    status.viddecStatus.size               = sizeof(IVIDDEC2_Status);

	    dynamicParams.viddecDynamicParams.size = sizeof(Imp2VDEC_DynamicParams);

	    inArgs.size                            = sizeof(IVIDDEC2_InArgs);
	    outArgs.size                           = sizeof(IVIDDEC2_OutArgs);

        /* Initializing one input file processign specific variables        */
        frameCount                   = 0;
        bytesConsumed                = 0;
        reachedEndOfFile             = 0;
        fileOffset                   = 0;
        validBytes                   = 0;
        outArgs.bytesConsumed        = 0;
        inputBufDesc.descs[0].buf    = inputData;
		status.viddecStatus.extendedError = 0;

        /* HDVICP calls enables non-blockign implementation on the host
         * processor in a OS scenario with support for multi-thread/task
         * creations. hdvicpObj which will be part of the decoder instance.
         * All future calls to HDVICP module made by the algorithm will
         * contain this as the handle.HDVICP module initialises it suitably
         * to enable context identification is future calls.
         */
       //HDVICP_initHandle(&hdvicpObj);
        //params.hdvicpHandle          = (void*) &hdvicpObj;

#ifdef XDM_RESET_TST
        if(countConfigSet == 1)
        {
#endif
		 /* Create the Algorithm object (instance)                           */
        printf("\nCreating Algorithm Instance...");
		handle =
          (IALG_Handle) MPEG2VDEC_create((IALG_Fxns *) &MPEG2VDEC_TI_IMPEG2VDEC,
             (IALG_Params *) &params);

        if (handle== NULL)
        {
            printf("\nFailed to Create Instance Exiting this configuration");
	        printErrorMsg(status.viddecStatus.extendedError);
            continue;
        }
        printf("\nAlgorithm Instance Creation Done...\n");

#ifdef _ENABLE_IRES_EDMA3
{
 int temp;
 temp = RMAN_assignResources((IALG_Handle)handle,
                                        &MPEG2VDEC_TI_IRES, /* IRES_Fxns* */
                                        1 /* scratchId */);
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != temp) {
      printf( "\nFailed in assigning resources \
                 Exiting for this configuration..");
      goto EndOfFile;
    }

	/* Activate All resources */
}
#endif



#ifdef XDM_RESET_TST
        }
#endif
        printf("Started decoding Test File %s\n",inFile);
		MPEG2VDEC_TI_IRES.activateAllResources((IALG_Handle)handle);

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

	    /*-----------------------------------------------------------------------*/
	    /*  Set the flag for the DDR bandwidth optimization by dropping B field  */
	    /*  dumps if required.                                                   */
	    /*-----------------------------------------------------------------------*/
	    dynamicParams.bottom_fld_DDR_Opt = 0;

	    /*-----------------------------------------------------------------------*/
	    /*  Set the flag for the mb error reporting in the current frame         */
	    /*  and also enable the slice level sync up for continuing decoding      */
	    /*  with the next slice in case of error in the frame                    */
	    /*-----------------------------------------------------------------------*/
	    dynamicParams.mb_error_reporting = 0;

	   	/*-----------------------------------------------------------------------*/
	    /*-----------------------------------------------------------------------*/
	    /*  Set the flag for the error conceal in the current frame              */
	    /*  to enable the slice level concealment                                */
	    /*-----------------------------------------------------------------------*/
	    dynamicParams.errorConceal = 1;

		dynamicParams.reset_HDVICP_every_frame = 1;

		dynamicParams.viddecDynamicParams.displayWidth = 0;

		dynamicParams.viddecDynamicParams.frameOrder = 0;

	   	/*-----------------------------------------------------------------------*/
		/* Open a file for the MBdata and the frame level data                   */
		/*-----------------------------------------------------------------------*/
		if(dynamicParams.viddecDynamicParams.mbDataFlag)
		{
			mb_data_fp = fopen("mb_frm_data.txt","wb");

			if(mb_data_fp == 0)
			{
				printf("\nMB_data file open error\n");
				exit(1);
			}
		}


//CHANGED taken from testapp of mp2
	    /*-----------------------------------------------------------------------*/
	    /*  The XDM_RESET call gives resets all the internal data structures and */
	    /*  context for the new stream that is to be decoded.                    */
	    /*-----------------------------------------------------------------------*/

	   //printf("frameOrder %d\n", dynamicParams.viddecDynamicParams.frameOrder);
	   retVal =  MPEG2VDEC_control(handle, XDM_RESET,
	                   (IVIDDEC2_DynamicParams *)&dynamicParams,
	                   (IVIDDEC2_Status *)&(status.viddecStatus));
		if(retVal == XDM_EFAIL)
		{
			printf("XDM reset Command Failed\n");
			printErrorMsg(status.viddecStatus.extendedError);
	        fflush (stdout);
	        continue;
		}


        /* Control call for Get Buffer Sizes                                */
       retVal =  MPEG2VDEC_control(handle, XDM_GETBUFINFO,
                       (IVIDDEC2_DynamicParams *)&dynamicParams,
                       (IVIDDEC2_Status *)&(status.viddecStatus));

		if(retVal == XDM_EFAIL)
		{
			printf("XDM get buf info Command Failed\n");
			printErrorMsg(status.viddecStatus.extendedError);
	        fflush (stdout);
	        continue;
		}

		if(status.viddecStatus.extendedError)
		{
			printErrorMsg(status.viddecStatus.extendedError);
		}

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
        printf("Frame Num | PreP Cycles | ARM968 cycles | PostP cycles\
				|    Total    | fps For D1 |  EC Applied | \n");
        printf("------------------------------------------------------\
----------------------------------------------\n");
#endif

        outBufsInUseFlag = 0;
        /* Setting of input arguments                                   */
        inArgs.inputID = 0;

        /* Do-While Loop for Decode Call                                    */
        do
        {
            /* Setting of input arguments                                   */
            /* Assign the number of bytes available                         */
            inArgs.numBytes= validBytes;
            /* Read the bitstream in the Application Input Buffer. validBytes
             * would be initialised with the actual number of bytes read from
             * the input file
             */
#ifndef TST_FRAME_MODE
            validBytes = TestApp_ReadByteStream(inFile);
#else
            validBytes = TestApp_ReadByteStream(inFile,fsizeFile,frameCount);
#endif
            if(validBytes == -1)
            {
                break;
            }

            /* Assign the number of bytes available                         */
            inArgs.numBytes  = validBytes;
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
             if(outBufsInUseFlag == 0)
             {
            buffEle = BUFFMGR_GetFreeBuffer();
            /* Fill up the output buffer values and pointers                */
            outputBufDesc.numBufs           = 2;
            outputBufDesc.bufSizes          = (XDAS_Int32 *) buffEle->bufSize;
            outputBufDesc.bufs              = (XDAS_Int8 **) buffEle->buf;
            inArgs.inputID     = buffEle->bufId;
//            dynamicParams.outloopDeblocking = DEBLOCK;
//            dynamicParams.outloopDeRinging  = DERING;
            }
            /* Optional: Set Run time parameters in the Algorithm           */
		    retVal =   MPEG2VDEC_control(handle, XDM_SETPARAMS,
                       (IVIDDEC2_DynamicParams *)&dynamicParams,
                       (IVIDDEC2_Status *)&status);

			if(retVal == XDM_EFAIL)
			{
				printf("XDM set params info Command Failed\n");
				printErrorMsg(status.viddecStatus.extendedError);
		        fflush (stdout);
		        break;
			}

			if(status.viddecStatus.extendedError)
			{
				printErrorMsg(status.viddecStatus.extendedError);
			}

			if(XDM_ISFATALERROR(status.viddecStatus.extendedError))
	        {
	            break;
	        }



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

	MPEG2VDEC_TI_IRES.activateAllResources((IALG_Handle)handle);

	if(outArgs.outBufsInUseFlag == 0)
	{
        memset(&outArgs, 0, sizeof(IVIDDEC2_OutArgs));
        outArgs.size = sizeof(IVIDDEC2_OutArgs);
	}
            /* Basic Algorithm process() call to decode a frame             */
     retVal = MPEG2VDEC_decode (handle,
                             (XDM1_BufDesc *)&inputBufDesc,
                             (XDM_BufDesc *)&outputBufDesc,
                             (IVIDDEC2_InArgs *)&inArgs,
                             (IVIDDEC2_OutArgs *)&outArgs);

        outBufsInUseFlag = outArgs.outBufsInUseFlag;
#ifdef PROFILE_ONLINUX
            time_after_process = gettimeofday(decoder_timeptr, NULL);
            //printf("time After = %d\n",decoder_timeptr->tv_usec);
            //printf("time before = %d, time after = %d\n",time_before_process,time_after_process);
	    if(decoder_timeptr->tv_usec <= time_before_process)
	    {

	    	decoder_timeptr->tv_usec += 1000000;
	    }
	    printf("PROCESS LEVEL FRAME DECODE TIME 926 = %d\t",(decoder_timeptr->tv_usec - time_before_process));
#endif


#ifdef _PROFILE_
        ARM926cycles = profileEnd(0);
        printf("%6d -", frameCount);
        printf("%2d", outArgs.displayBufs[0].frameType);
        printf("%13d",ARM968cycles0);
        printf("%15d",(ARM968cycles1 - ARM968cycles0));
        printf("%15d",(ARM926cycles - ARM968cycles1));
        printf("%15d",ARM926cycles);
        {
            XDAS_UInt32 DecMbWidth,DecMbHeight;
            XDAS_UInt32 MBCycles, fps;
            DecMbWidth =
            (outArgs.displayBufs[0].frameWidth >> 4) ;
            DecMbHeight =
            (outArgs.displayBufs[0].frameHeight >> 4);
            MBCycles = (ARM926cycles / (DecMbWidth * DecMbHeight));
            fps      = (CLOCK_SEC / (MBCycles * 45 * 30));
            printf("%12d",fps);
        }
        if(outArgs.displayBufs[0].extendedError & 0x200)
        {
            printf("           Y\n");
        }
        else
        {
            printf("           N\n");
        }
#endif
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
                            (XDAS_UInt32 *)outArgs.freeBufID
                                 );
                MPEG2VDEC_control((Imp2VDEC_Handle)handle,
                XDM_GETSTATUS,
                (Imp2VDEC_DynamicParams *)&dynamicParams,
                (Imp2VDEC_Status *)&status);
                printf("\n Process function returned an Error : %x\n",
                                           status.viddecStatus.extendedError);
            }

            bytesConsumed          += outArgs.bytesConsumed;
            validBytes             -= outArgs.bytesConsumed;

	      /*---------------------------------------------------------------------*/
	      /*  Invoke a GETSTATUS control call to populate the actual width and   */
	      /*  height of the picture that got decoded into the status outputWidth */
	      /*  and outputHeight fields.                                           */
	      /*---------------------------------------------------------------------*/
	      MPEG2VDEC_control(handle,
	        Imp2VDEC_GETSTATUS,
	        (IVIDDEC2_DynamicParams *)&dynamicParams,
	        (IVIDDEC2_Status *)&status);
#ifdef _STR_CUT_
            if((frameCount == 0) ||(frameCount == 60))
            {
                if(frameCount == 0)
                {
                    fp = fopen("..\\..\\..\\test\\testvecs\\input\\mask_WCDMA_64KB_211HZ_3_VER2_akiyo.263","wb");
                    fwrite(inputData,1,outArgs.bytesConsumed,fp);
                    fflush (fp);
                }
                else
                {
                    fwrite(inputData,1,(outArgs.bytesConsumed+1000),fp);
                    fflush (fp);
                    fclose(fp);
                    break;
                }
            }
#endif
#ifndef _PROFILE_
			if(!dynamicParams.viddecDynamicParams.decodeHeader)
			{
			if(!dynamicParams.viddecDynamicParams.frameOrder)
	            printf(" : %1d", outArgs.displayBufs[0].frameType);
			else
	            printf(" : %1d", outArgs.decodedBufs.frameType);
			}
            printf(" : BytesConsumed :%6d",outArgs.bytesConsumed);
#endif

#if 0
			printf("\n*********** decodedBufs ***********\n");
			{
				IVIDEO1_BufDesc *ptr = &outArgs.decodedBufs;
				printf("numBufs=%d\n",ptr->numBufs);
				printf("frameWidth=%d\n",ptr->frameWidth);
				printf("frameHeight=%d\n",ptr->frameHeight);
				printf("framePitch=%d\n",ptr->framePitch);
				printf("bufDes=%x %x %d %d\n",ptr->bufDesc[0].buf, ptr->bufDesc[1].buf, ptr->bufDesc[0].bufSize, ptr->bufDesc[1].bufSize);
				printf("extendedError=%d\n",ptr->extendedError);
				printf("frameType=%d\n",ptr->frameType);
				printf("topFieldFirstFlag=%d\n",ptr->topFieldFirstFlag);
				printf("repeatFirstFieldFlag=%d\n",ptr->repeatFirstFieldFlag);
				printf("frameStatus=%d\n",ptr->frameStatus);
				printf("repeatFrame=%d\n",ptr->repeatFrame);
				printf("contentType=%d\n",ptr->contentType);
				printf("chromaFormat=%d\n",ptr->chromaFormat);
				printf("**********************\n");

			}

			if(outArgs.outputID[0] != 0)
			{
				IVIDEO1_BufDesc *ptr = &outArgs.displayBufs[0];
				printf("\n*********** displayBufs ***********\n");
				printf("numBufs=%d\n",ptr->numBufs);
				printf("frameWidth=%d\n",ptr->frameWidth);
				printf("frameHeight=%d\n",ptr->frameHeight);
				printf("framePitch=%d\n",ptr->framePitch);
				printf("bufDes=%x %x %d %d\n",ptr->bufDesc[0].buf, ptr->bufDesc[1].buf, ptr->bufDesc[0].bufSize, ptr->bufDesc[1].bufSize);
				printf("extendedError=%d\n",ptr->extendedError);
				printf("frameType=%d\n",ptr->frameType);
				printf("topFieldFirstFlag=%d\n",ptr->topFieldFirstFlag);
				printf("repeatFirstFieldFlag=%d\n",ptr->repeatFirstFieldFlag);
				printf("frameStatus=%d\n",ptr->frameStatus);
				printf("repeatFrame=%d\n",ptr->repeatFrame);
				printf("contentType=%d\n",ptr->contentType);
				printf("chromaFormat=%d\n",ptr->chromaFormat);
				printf("**********************\n");

			}
#endif

            if(frameCount == 0)
            {
#ifndef _PROFILE_
				if(!dynamicParams.viddecDynamicParams.frameOrder)
                printf(" :\n",frameCount);
#endif
                MPEG2VDEC_control((Imp2VDEC_Handle)handle,
                XDM_GETBUFINFO,
                (Imp2VDEC_DynamicParams *)&dynamicParams,
                (Imp2VDEC_Status *)&status);
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
                            (XDAS_UInt32 *)outArgs.freeBufID
                                 );
			}
            /* Check for frame ready via display buffer pointers            */
            if(outArgs.outputID[0] != 0)
            {
                if(testCompliance)
                {
#if 1
		            void   *Base_ptr;

		            /* This code generates the checksum 16 Bytes Luma followed */
		            /* by 16 Bytes of Chroma */
		            /* Luma */
		            Base_ptr = outArgs.displayBufs[0].bufDesc[0].buf;

		            Calculate_MD5_CkSum_buf(Base_ptr,
		                                    outArgs.displayBufs[0].frameWidth,
		                                    outArgs.displayBufs[0].framePitch,
		                                    outArgs.displayBufs[0].frameHeight,
		                                    chksum);

		            fread(ref_byte, 1, 16, ftestFile);
		            if(*ref_byte == *chksum)
		                testVal = 1;
		            else
		                testVal = 0;

		            /* Chroma */
		            Base_ptr = outArgs.displayBufs[0].bufDesc[1].buf;
		            Calculate_MD5_CkSum_buf(Base_ptr,
		                                    outArgs.displayBufs[0].frameWidth,
		                                    outArgs.displayBufs[0].framePitch,
		                                    outArgs.displayBufs[0].frameHeight>>1,
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
			          /*-----------------------------------------------------------------*/
			          /*  Compare the output frames with the Reference File              */
			          /*-----------------------------------------------------------------*/
			          testVal = TestApp_CompareOutputData(ftestFile,
			            &outputBufDesc,
			            &outArgs);

			          /*-----------------------------------------------------------------*/
			          /*  Check for success/failure based on returned value.             */
			          /*-----------------------------------------------------------------*/
			          if(testVal == XDM_EOK)
			          {
			            printf("\n Decoder compliance test passed for this frame.  ");
			          }
			          else
			          {
			            /*---------------------------------------------------------------*/
			            /* Test Compliance Failed... Breaking...                         */
			            /*---------------------------------------------------------------*/
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
	                TestApp_WriteOutputData(ftestFile,
	                                        &outputBufDesc,
	                                        &outArgs,
	                                        &status,
	                                        dynamicParams.viddecDynamicParams.frameOrder);
                    }
                }
            }


			  /*** Tapping the Frame_level and MB_level_data ***/
            if(dynamicParams.viddecDynamicParams.mbDataFlag)
		    {
				if(dynamicParams.viddecDynamicParams.frameOrder)
				{
					mb_data_size = (40 * ((outArgs.decodedBufs.frameWidth  >> 4)*
					  			  (outArgs.decodedBufs.frameHeight >> 4) + 14) + 128);
				}
				else
				{
					mb_data_size = (40 * ((outArgs.displayBufs[0].frameWidth  >> 4)*
					  			  (outArgs.displayBufs[0].frameHeight >> 4) + 14) + 128);
				}

				printf("\nmbDataBuf.buf = 0x%x :mbDataBuf.bufSize = %d\n",outArgs.mbDataBuf.buf,mb_data_size);
				mb_data_size = fwrite(outArgs.mbDataBuf.buf,mb_data_size,1,mb_data_fp);

				/*if(mb_data_size != outArgs.mbDataBuf.bufSize)
				{
					printf("\n Bytes written in the mb_data_file incorrect \n");
					exit(1);
				}*/
			}

		      /*---------------------------------------------------------------------*/
		      /*  Increment the local framecount variable when an entire frame or    */
		      /*  both fields of an interlaced frame have got decoded. The outbufsin */
		      /*  use flag is a good indicator of an interlaced frame continuing as  */
		      /*  the algorithm sets this only in the said condition.                */
		      /*---------------------------------------------------------------------*/
           if (!outArgs.outBufsInUseFlag)
		   {
		       frameCount++;
		   }


            /* Check for Break off condition                                */
           if (validBytes < 4)
            {
                printf("\n Bitstream Ended...  ");
                break; /* Bitstream ended: Break off the while loop         */
            }
            /* NUM_FRAMES is added for debug purpose. During complete testing
             * this can be read fron parameter file into framesToDecode.The
             * following code to be modified as (frameCount >= framesToDecode)
             */
            if (frameCount >= framesToDecode)
            {
                printf("\n Specified number of Frames Decoded...  ");
                break; /* Bitstream ended: Break off the while loop         */
            }

			dynamicParams.viddecDynamicParams.decodeHeader = XDM_DECODE_AU;

        }  while(1);  /* end of Do-While loop                               */

       /*---------------------------------------------------------------------*/
      /*  Invoke a GETSTATUS control call to populate the actual width and   */
      /*  height of the picture that got decoded into the status outputWidth */
      /*  and outputHeight fields.                                           */
      /*---------------------------------------------------------------------*/
      MPEG2VDEC_control(handle,
        Imp2VDEC_GETSTATUS,
        (IVIDDEC2_DynamicParams *)&dynamicParams,
        (IVIDDEC2_Status *)&status);

    do
    {

      /*---------------------------------------------------------------------*/
      /*  Implement the flush process calls if any frame is held by the      */
      /*  algorithm.                                                         */
      /*---------------------------------------------------------------------*/
      MPEG2VDEC_control(handle,
        Imp2VDEC_FLUSH,
        (IVIDDEC2_DynamicParams *)&dynamicParams,
        (IVIDDEC2_Status *)&status);

	  MPEG2VDEC_TI_IRES.activateAllResources((IALG_Handle)handle);

      /*---------------------------------------------------------------------*/
      /*  Call the process call after the XDM_FLUSH control call.            */
      /*---------------------------------------------------------------------*/
      retVal = MPEG2VDEC_decode (handle,
                             (XDM1_BufDesc *)&inputBufDesc,
                             (XDM_BufDesc *)&outputBufDesc,
                             (IVIDDEC2_InArgs *)&inArgs,
                             (IVIDDEC2_OutArgs *)&outArgs);

      /*---------------------------------------------------------------------*/
      /*  Check for frame ready via display buffer pointers. If outputID of  */
      /*  outargs is non-zero, only then a frame is required to be displayed.*/
      /*  Call the display routines after performing the check.              */
      /*---------------------------------------------------------------------*/
      if((outArgs.outputID[0] > 0) && (!dynamicParams.viddecDynamicParams.frameOrder))
      {
        printf ("\nFlushing held frames\n");
        printf ("\nDecoded Frame # %d\n", frameCount);

        printf("\n  Displaying Frame\n");

        frameCount++;

        /*-------------------------------------------------------------------*/
        /*  Check for test compliance or output dump mode and call appropri- */
        /*  ate functions. Currently, testcompliance is not supported.       */
        /*-------------------------------------------------------------------*/
        if(testCompliance)
        {
#if 1
            void   *Base_ptr;

            /* This code generates the checksum 16 Bytes Luma followed */
            /* by 16 Bytes of Chroma */
            /* Luma */
            Base_ptr = outArgs.displayBufs[0].bufDesc[0].buf;

            Calculate_MD5_CkSum_buf(Base_ptr,
                                    outArgs.displayBufs[0].frameWidth,
                                    outArgs.displayBufs[0].framePitch,
                                    outArgs.displayBufs[0].frameHeight,
                                    chksum);

            fread(ref_byte, 1, 16, ftestFile);
            if(*ref_byte == *chksum)
                testVal = 1;
            else
                testVal = 0;

            /* Chroma */
            Base_ptr = outArgs.displayBufs[0].bufDesc[1].buf;
            Calculate_MD5_CkSum_buf(Base_ptr,
                                    outArgs.displayBufs[0].frameWidth,
                                    outArgs.displayBufs[0].framePitch,
                                    outArgs.displayBufs[0].frameHeight>>1,
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
          /*-----------------------------------------------------------------*/
          /*  Compare the output frames with the Reference File              */
          /*-----------------------------------------------------------------*/
          testVal = TestApp_CompareOutputData(ftestFile,
            &outputBufDesc,
            &outArgs);

          /*-----------------------------------------------------------------*/
          /*  Check for success/failure based on returned value.             */
          /*-----------------------------------------------------------------*/
          if(testVal == XDM_EOK)
          {
            printf("\n Decoder compliance test passed for this frame.  ");
          }
          else
          {
            /*---------------------------------------------------------------*/
            /* Test Compliance Failed... Breaking...                         */
            /*---------------------------------------------------------------*/
            break;
          }
#endif
        }
        else
        {
            /*---------------------------------------------------------------*/
            /*  Call the function to write the output frame to the file.     */
            /*  This function will separate the CB/CR pixels before writing  */
            /*  to the file.                                                 */
            /*---------------------------------------------------------------*/
           if(frameCount >= DumpFrom)            {
                TestApp_WriteOutputData(ftestFile,
                                        &outputBufDesc,
                                        &outArgs,
	                                        &status,
	                                        dynamicParams.viddecDynamicParams.frameOrder);
            }
        }

      }

    }while ((outArgs.outputID[0])  && (!dynamicParams.viddecDynamicParams.frameOrder) );

	if(!dynamicParams.viddecDynamicParams.frameOrder)
		frameCount--;

EndOfFile:
        /* Output file close                                                */
        fclose(ftestFile);
#ifdef TST_FRAME_MODE
        fclose(fsizeFile);
#endif



#ifdef XDM_RESET_TST
        MPEG2VDEC_control((Imp2VDEC_Handle)handle,
        XDM_RESET,
        (Imp2VDEC_DynamicParams *)&dynamicParams,
        (Imp2VDEC_Status *)&status);
#endif
#ifndef XDM_RESET_TST
	//#ifndef ON_LINUX
	#ifdef _ENABLE_IRES_EDMA3
	    /*
	     * Free resources assigned to this algorihtm
	     */
		 {
		 int temp;

		 temp = RMAN_freeResources((IALG_Handle)(handle),
	               &MPEG2VDEC_TI_IRES, 1);
	    if (IRES_OK != temp) {
	        printf("Free Resource Failed \n");
	        //return -1;
	    }
		}
	#endif
	//#endif

     /* Delete the Algorithm instance object specified by handle */
       MPEG2VDEC_delete ((Imp2VDEC_Handle)handle);
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
		if(!dynamicParams.viddecDynamicParams.frameOrder)
	    {
	        printf("\t Width and Height                    = %d, %d \n",
	          (XDAS_UInt32)outArgs.displayBufs[0].frameWidth,
	          (XDAS_UInt32)outArgs.displayBufs[0].frameHeight);
        }
		else
		{
	        printf("\t Width and Height                    = %d, %d \n",
	          (XDAS_UInt32)outArgs.decodedBufs.frameWidth,
	          (XDAS_UInt32)outArgs.decodedBufs.frameHeight);
		}
        printf (" --------------    END   --------------------\n");

        /* Free the application external memory allocated for supplying to
         * decoder to hold decoded frame.
         */
        BUFFMGR_DeInit();
  } /* Read the Config File until it reaches the end of file                */
#ifdef XDM_RESET_TST

	//#ifndef ON_LINUX
	#ifdef _ENABLE_IRES_EDMA3
	    /*
	     * Free resources assigned to this algorihtm
	     */
		 {
		 int temp;

		 temp = RMAN_freeResources((IALG_Handle)(handle),
	               &MPEG2VDEC_TI_IRES, 1);
	    if (IRES_OK != temp) {
	        printf("Free Resource Failed \n");
	        //return -1;
	    }
		}
	#endif
	//#endif

    /* Delete the Algorithm instance object specified by handle */
    MPEG2VDEC_delete ((Imp2VDEC_Handle)handle);
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
XDAS_Int32 TestApp_ReadByteStream(XDAS_Int8 *inFile)
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
    finFile = fopen ((const char *)inFile, "rb");
    if (!finFile)
    {
        printf("\n Couldn't open Input file...  %s  ",(const char *)inFile);
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
    XDAS_Int8 *inFile,
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

/* ==========================================================================
*
*@func   TestApp_CompareOutputData()
*
*@brief  Application function to ompare output data
*
*@param  input file ptr
*
*@param  outputBufDesc      Output buffer descriptors
*
*@param  outArgs            Output arguments
*
*@ret    success/fail
*
*@note   Currently, this function is not getting used as testcompliance mode
*        is not yet supported.
* ============================================================================
*/
XDAS_Int32 TestApp_CompareOutputData(FILE *fRefFile,
    XDM_BufDesc * outputBufDesc,
    IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 i, bufferSize, retVal;
    XDAS_UInt8 *outputData;

    retVal = XDM_EOK;

    for(i = 0; i < outputBufDesc->numBufs; i++)
    {
      outputData = (XDAS_UInt8 *)outArgs->displayBufs[0].bufDesc[i].buf;
      bufferSize = outArgs->displayBufs[0].bufDesc[i].bufSize;
      fread (refData, 1, bufferSize, fRefFile);
      if(memcmp(outputData, refData, bufferSize)) {
        printf( "\n Decoder compliance test failed for this frame. ");
        retVal = XDM_EFAIL;
        break;
      }
    }
    return retVal;
}

/* ==========================================================================
*
*@func   TestApp_WriteOutputData()
*
*@brief  Application function to write output data to a file
*
*@param  fOutFile           output file ptr
*
*@param  outputBufDesc      Output buffer descriptors
*
*@param  outArgs            Output arguments
*
*@param  status             current status struct
*
*@ret    none
*
* ============================================================================
*/
XDAS_Void TestApp_WriteOutputData  (FILE             *fOutFile,
                                    XDM_BufDesc      *outputBufDesc,
                                    IVIDDEC2_OutArgs *outArgs,
                                    Imp2VDEC_Status  *status,
                                    XDAS_Int8         output_order)
{
    XDAS_Int32 pic_size, width, height, framePitch,frame_width,frame_height;
    XDAS_Int8 *CbCr_seperate[2];
    XDAS_Int8 *Luma_data;
    XDAS_Int8 *CbCr_data;

    width    = status->viddecStatus.outputWidth;
    height   = status->viddecStatus.outputHeight;

    pic_size = width * height;

    /*-----------------------------------------------------------------------*/
    /*  Init input buffer with pointers supplied with outArgs                */
    /*-----------------------------------------------------------------------*/
	if(!output_order)
	{
    	Luma_data   = outArgs->displayBufs[0].bufDesc[0].buf; /* Init for Y        */
    	CbCr_data   = outArgs->displayBufs[0].bufDesc[1].buf; /* Init for CbCr     */
	    framePitch  = outArgs->displayBufs[0].framePitch;
		frame_width = outArgs->displayBufs[0].frameWidth;
		frame_height= outArgs->displayBufs[0].frameHeight;
	}
	else
	{
		Luma_data = outArgs->decodedBufs.bufDesc[0].buf; /* Init for Y        */
    	CbCr_data = outArgs->decodedBufs.bufDesc[1].buf; /* Init for CbCr     */
	    framePitch = outArgs->decodedBufs.framePitch;
		frame_width = outArgs->decodedBufs.frameWidth;
		frame_height= outArgs->decodedBufs.frameHeight;
	}
    /*-----------------------------------------------------------------------*/
    /*  Init output yuv_buffer with global pointer fullPic                   */
    /*-----------------------------------------------------------------------*/
    CbCr_seperate[0] = Chroma_separate;                   /* Init for Cb     */
    CbCr_seperate[1] = CbCr_seperate[0] + (pic_size>> 2); /* Init for Cr     */

    /*-----------------------------------------------------------------------*/
    /*  This function separates out the Cb and Cr component                  */
    /*-----------------------------------------------------------------------*/
    separateCbCrPixels(CbCr_data, CbCr_seperate,
                       (height >> 1), width, framePitch);

    /*-----------------------------------------------------------------------*/
    /*  Write YUV data to File                                               */
    /*-----------------------------------------------------------------------*/
    for(height= 0; height < frame_height; height++)
    {
        fwrite (Luma_data, 1,frame_width,fOutFile);
        Luma_data += framePitch;
    }
    /*-----------------------------------------------------------------------*/
    /*  Write CB and CR data one after other to the file.                    */
    /*-----------------------------------------------------------------------*/
    fwrite (CbCr_seperate[0], 1,pic_size>>2,fOutFile);
    fwrite (CbCr_seperate[1], 1,pic_size>>2,fOutFile);

    /*-----------------------------------------------------------------------*/
    /*  Flush the outfile                                                    */
    /*-----------------------------------------------------------------------*/
    fflush (fOutFile);
    return;
}



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
 *  @param  Imp2VDEC_DynamicParams *dynamicParams
 *          Dynamic parameter structure..
 *
 *  @return None
 *
 *  @note   None
 * ===========================================================================
 */
XDAS_Void TestApp_SetDynamicParams(Imp2VDEC_DynamicParams *dynamicParams)
{
    /* Set IVIDDEC2 Run time parameters */
    dynamicParams->viddecDynamicParams.decodeHeader  = XDM_DECODE_AU;
    //dynamicParams->viddecDynamicParams.displayHeight = 0;
    dynamicParams->viddecDynamicParams.displayWidth  = 0;
    dynamicParams->viddecDynamicParams.frameSkipMode = IVIDEO_NO_SKIP;
    dynamicParams->viddecDynamicParams.mbDataFlag    = 0;
    dynamicParams->viddecDynamicParams.newFrameFlag  = 0;
	dynamicParams->viddecDynamicParams.frameOrder    = 0;  /* 0=Display: 1=Decode */
    return;
}/* TestApp_SetDynamicParams() */

/* ==========================================================================
*
*@func   separateCbCrPixels()
*
*@brief  Function to separate interleaved CB CR pixels for purpose of
*        preparing output data for file writing.
*
*
*@param  CbCr_data      Pointer to CB CR interleaved data.
*
*@param  Chroma_buf[]   Array of pointers for CB and CR separate buffers.
*
*@param  height         Display Height of picture.
*
*@param  width          Display width of picture.
*
*@param  pitch          pitch of the reference buffer
*
*@ret    None
*
* ============================================================================
*/
void separateCbCrPixels
(
      XDAS_Int8  *CbCr_data,
      XDAS_Int8  *Chroma_buf[2],
      XDAS_Int32  height,
      XDAS_Int32  width,
      XDAS_Int32  pitch
)
{

    XDAS_UInt32 i,j;
    XDAS_UInt32 pix_count = 0;
    XDAS_Int8* Cb_data;
    XDAS_Int8* Cr_data;
    XDAS_Int8* CbCr_buf;

    /*-----------------------------------------------------------------------*/
    /*  Initialize CB and CR data ptrs to the start of chroma bufs 0 and 1.  */
    /*-----------------------------------------------------------------------*/
    Cb_data  = Chroma_buf[0];
    Cr_data  = Chroma_buf[1];
    CbCr_buf = CbCr_data;
    pix_count = 0;

    /*-----------------------------------------------------------------------*/
    /*  Start a loop to copy the interleaved cb/cr data to separate CB/CR    */
    /*  buffers.                                                             */
    /*-----------------------------------------------------------------------*/
    for(i = 0; i < height; i++)
    {
        for(j = 0; j< width; j+=2)
        {
            Cb_data[pix_count] = CbCr_buf[j];
            Cr_data[pix_count] = CbCr_buf[j+1];
            pix_count++;
        }
        /*-------------------------------------------------------------------*/
        /*  Increment by the pitch supplied and not by width.                */
        /*-------------------------------------------------------------------*/
        CbCr_buf += pitch;
    }
}

/*===========================================================================*/
/*!
*@func   printErrorMsg
*
*@brief  This print the decoder error code string for the input error code
*
*@param  errorCode
*        input MPEG2 encoder error codes
*
*@return void
*
*@note
*/
/*===========================================================================*/
int printErrorMsg(XDAS_Int32 errorCode)
{
	printf("\n");

	if(XDM_ISCORRUPTEDHEADER(errorCode))
		printf("HEADER_CORRUPT \n");
    if(XDM_ISUNSUPPORTEDPARAM(errorCode))
		printf("UNSUPPORTED PARAM \n");
	if(XDM_ISFATALERROR(errorCode))
		printf("FATAL ERROR \n");
	if(XDM_ISUNSUPPORTEDINPUT(errorCode))
		printf("UNSUPPORTED INPUT \n");
	if(XDM_ISCORRUPTEDDATA(errorCode))
		printf("CORRUPTED DATA \n");
	if(XDM_ISINSUFFICIENTDATA(errorCode))
		printf("INSUFFICIENT DATA \n");
	if(XDM_ISAPPLIEDCONCEALMENT(errorCode))
		printf("APPLIED CONCEAL \n");

	errorCode = errorCode & 0x7F;
	switch(errorCode)
	{

		case IMPEG2VDEC_ERR_INCORRECT_HANDLE:
			printf("MPEG2VDEC_ERR_MEMTAB_NULL\n");
			break;

		case IMPEG2VDEC_ERR_INCORRECT_CODEC_ID:
			printf("MPEG2VDEC_ERR_INCORRECT_CODEC_ID\n");
			break;

		case IMPEG2VDEC_ERR_RESOURCE_INIT_UNSUCCESSFUL:
			printf("MPEG2VDEC_ERR_RESOURCE_INIT_UNSUCCESSFUL\n");
			break;

		case IMPEG2VDEC_ERR_INPUT_ARGUMENT_NULL:
			printf("MPEG2VDEC_ERR_INPUT_ARGUMENT_NULL\n");
			break;

		case IMPEG2VDEC_ERR_INPUT_ARGUMENT_SIZE_INCORRECT:
			printf("MPEG2VDEC_ERR_INPUT_ARGUMENT_SIZE_INCORRECT\n");
			break;

		case IMPEG2VDEC_ERR_IVIDENC1_INBUFS_BUFDESC:
			printf("MPEG2VDEC_ERR_IVIDENC1_INBUFS_BUFDESC\n");
			break;

		case IMPEG2VDEC_ERR_IVIDENC1_OUTBUFS_BUFDESC:
			printf("MPEG2VDEC_ERR_IVIDENC1_OUTBUFS_BUFDESC\n");
			break;

		case IMPEG2VDEC_ERR_IVIDDEC2_INARGS_SIZE:
			printf("MPEG2VDEC_ERR_IVIDDEC2_INARGS_SIZE\n");
			break;

		case IMPEG2VDEC_ERR_SEQ_HEADER:
			printf("ERRONEOUS SEQ HEADER\n");
			break;

		case IMPEG2VDEC_ERR_INV_ARG_HANDLE_IN_CONTROL:
			printf("MPEG2VDEC_ERR_INV_ARG_HANDLE_IN_CONTROL");
			break;

		case IMPEG2VDEC_ERR_ALGO_NOT_ACTIVATED:
			printf("MPEG2VDEC_ERR_ALGO_NOT_ACTIVATED");
			break;

		case IMPEG2VDEC_ERR_RESOURCES_NOT_INITIATED:
			printf("MPEG2VDEC_ERR_RESOURCES_NOT_INITIATED");
			break;

		case IMPEG2VDEC_ERR_REQ_RESOURCES_NOTALL_ACTIVATED:
			printf("MPEG2VDEC_ERR_REQ_RESOURCES_NOTALL_ACTIVATED");
			break;

		case IMPEG2VDEC_ERR_INVALID_INPUT_ID:
			printf("MPEG2VDEC_ERR_INVALID_INPUT_ID");
			break;

		case IMPEG2VDEC_ERR_INVALID_NUM_BYTES:
			printf("MPEG2VDEC_ERR_INVALID_NUM_BYTES");
			break;

		case IMPEG2VDEC_ERR_FORBIDDEN_FRAME_RATE_CODE:
			printf("IMPEG2VDEC_ERR_FORBIDDEN_FRAME_RATE_CODE");
			break;

		case IMPEG2VDEC_ERR_FORBIDDEN_BIT_RATE:
			printf("IMPEG2VDEC_ERR_FORBIDDEN_BIT_RATE");
			break;

		case IMPEG2VDEC_ERR_DISPLAY_VERTICAL_SIZE_ZERO:
			printf("IMPEG2VDEC_ERR_DISPLAY_VERTICAL_SIZE_ZERO");
			break;

		case IMPEG2VDEC_ERR_DISPLAY_HOR_SIZE_ZERO:
			printf("IMPEG2VDEC_ERR_DISPLAY_HOR_SIZE_ZERO");
			break;

		case IMPEG2VDEC_ERR_SLICE_VERIFICATION_CHECK_FAILED:
			printf("IMPEG2VDEC_ERR_SLICE_VERIFICATION_CHECK_FAILED");
			break;

		case IMPEG2VDEC_ERR_JUNK_DATA:
			printf("IMPEG2VDEC_ERR_JUNK_DATA");
			break;

		case IMPEG2VDEC_ERR_INVALID_DISPLAY_WIDTH:
			printf("IMPEG2VDEC_ERR_INVALID_DISPLAY_WIDTH");
			break;

		case IMPEG2VDEC_ERR_DISPLAY_WIDTH_DYNAMIC_CHANGE_INVALID:
			printf("IMPEG2VDEC_ERR_DISPLAY_WIDTH_DYNAMIC_CHANGE_INVALID");
			break;

		case IMPEG2VDEC_ERR_SET_DEFAULT_VALUE_ZERO:
			printf("IMPEG2VDEC_ERR_SET_DEFAULT_VALUE_ZERO");
			break;

		case IMPEG2VDEC_ERR_VALUE_OUT_OF_RANGE:
			printf("IMPEG2VDEC_ERR_VALUE_OUT_OF_RANGE");
			break;

		case IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_EXCEEDING_MAX     :
			printf("IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_EXCEEDING_MAX");
			break;
		case IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_LESSTHAN_MIN      :
			printf("IMPEG2VDEC_ERR_HEIGTH_OR_WIDTH_LESSTHAN_MIN");
			break;

		case IMPEG2VDEC_ERR_MARKER_BIT_NOT_FOUND              :
			printf("IMPEG2VDEC_ERR_MARKER_BIT_NOT_FOUND");
			break;

		case IMPEG2VDEC_ERR_INCORRECT_QUANT_MATRIX            :
			printf("IMPEG2VDEC_ERR_INCORRECT_QUANT_MATRIX");
			break;

		case IMPEG2VDEC_ERR_INVALID_PIC_CODING_TYPE           :
			printf("IMPEG2VDEC_ERR_INVALID_PIC_CODING_TYPE");
			break;

		case IMPEG2VDEC_ERR_FIELD_PIC_PAIR_NOT_FOUND          :
			printf("IMPEG2VDEC_ERR_FIELD_PIC_PAIR_NOT_FOUND");
			break;

		case IMPEG2VDEC_ERR_OUTPUT_FORMAT_NOT_SUPPORTED       :
			printf("IMPEG2VDEC_ERR_OUTPUT_FORMAT_NOT_SUPPORTED");
			break;

		case IMPEG2VDEC_ERR_MP_LEVEL_HT_WD_LIMITS_EXCEEDED:
			printf("IMPEG2VDEC_ERR_MP_LEVEL_HT_WD_LIMITS_EXCEEDED");
			break;

		case IMPEG2VDEC_ERR_SCALABILITY_NOT_SUPPORTED         :
			printf("IMPEG2VDEC_ERR_SCALABILITY_NOT_SUPPORTED");
			break;

		case IMPEG2VDEC_ERR_INVALID_F_CODE               :
			printf("IMPEG2VDEC_ERR_INVALID_F_CODE");
			break;

		case IMPEG2VDEC_ERR_ILLEGAL_INTERLACE_CONTENT         :
			printf("IMPEG2VDEC_ERR_ILLEGAL_INTERLACE_CONTENT");
			break;

		case IMPEG2VDEC_ERR_INVALID_FRAME_PRED_FRAME_DCT      :
			printf("IMPEG2VDEC_ERR_INVALID_FRAME_PRED_FRAME_DCT");
			break;

		case IMPEG2VDEC_ERR_INVALID_REPEAT_1ST_FIELD          :
			printf("IMPEG2VDEC_ERR_INVALID_REPEAT_1ST_FIELD");
			break;

        case IMPEG2VDEC_ERR_422FORMAT_UNSUPPORTED:
			printf("IMPEG2VDEC_ERR_422FORMAT_UNSUPPORTED");
			break;

		case IMPEG2VDEC_ERR_PROFILE_AND_LEVEL_UNSUPPORTED:
			printf("IMPEG2VDEC_ERR_PROFILE_AND_LEVEL_UNSUPPORTED");
			break;

		case IMPEG2VDEC_ERR_INCORRECT_INPUTID_FOR_SECOND_FLD:
			printf("IMPEG2VDEC_ERR_INCORRECT_INPUTID_FOR_SECOND_FLD");
			break;

		case IMPEG2VDEC_ERR_FRAME_ORDER_NON_CONF_AFTER_FIRST_FRAME:
			printf("IMPEG2VDEC_ERR_FRAME_ORDER_NON_CONF_AFTER_FIRST_FRAME");
			break;

		default:
			if(errorCode)
			printf("Unknown Error code\n");
	}

	return 1;
}


/*!
 *! Revision History
 *! ================
 *! 08-Oct-2007   Kumar    : Added the support for frame mode input handling.
 *! 16-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth:  Created.
 *!
 */
