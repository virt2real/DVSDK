/** ==========================================================================
* @file jpgdTest355.c
*
* @desc This is the top level client file that drives the JPEG Decoder s/w.
* ==========================================================================**/

/******************************************************************************
*                                 INCLUDE FILES
******************************************************************************/

/* ----------------------- SYSTEM header files ------------------------*/
#include <stdio.h>
#include <string.h>
#include "tistdtypes.h"

/*---------------------------------------------------------------------------*/
/*  Jpeg Decoder Interface header files                                             */
/*---------------------------------------------------------------------------*/
#include "ijpegdec.h"

/*---------------------------------------------------------------------------*/
/*  Client header file                                                       */
/*---------------------------------------------------------------------------*/
#include "testFramework.h"
#include "JpegDec_params.h"

/* ----------------------- Platform related header files ------------------------*/
#ifdef LINUX
#include <sys/time.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#include "cache.h"
#else
//#include "timer_common.h"
//#include <csl_psc.h>
#endif

/** ---  Resourde Manager Enable Macro --------------------------------*/
#define ENABLE_RMAN

/*------------------- Header Files for IRES/RMAN -----------------------*/
#ifdef ENABLE_RMAN
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/edma3/edma3_config.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>

#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>

#include "jpegdec_ti_ires.h"
#endif

#include "testapp_arm926intc.h"
/*--------------------Macros---------------------------------------------------*/

/*------------------- To enable profile--------------------------------------- */
//#define PROFILE
/*------------------------------------------------------------------------------*/
/*------------------------------------------------------------------------------*/

//#define csv_parser

/*---------------------------------------------------------------------------*/
/*  Redirecting the input and reference data buffers to appropriate data     */
/*  sections in external memory.                                             */
/*---------------------------------------------------------------------------*/
#ifdef LINUX
Int8 *ringbuf, *bJpegStream, *bDecodedYCC, *bDecodedchroma, *bufnew;
#else
Int8 *bDecodedchroma;
#pragma DATA_SECTION( ringbuf, ".ddr");
Int8 ringbuf[RINGBUF_SIZE];
#pragma DATA_SECTION( bJpegStream, ".ddr");
Int8 bJpegStream[JPEG_MAX_NUM_JPEG_BYTES];
#pragma DATA_SECTION( bDecodedYCC, ".ddr");
Int8 bDecodedYCC[JPEG_MAX_NUM_YCC_BYTES];
#pragma DATA_SECTION( bufnew, ".ddr");
XDAS_Int8 bufnew[720*480];
#endif
extern unsigned char *ExternalGlobalMemPool;
extern unsigned char *pInternalDataMemory;

/* ------------------------- Global Param structures -------------------------------*/

IIMGDEC1_Params          params;
IIMGDEC1_DynamicParams   dynamicParams;
IJPEGDEC_Params          extn_params;
IJPEGDEC_DynamicParams   extn_dynamicParams;
/*---------------------------------------------------------------------------*/
/*  Global timer stamps and structures used for profiling.             */
/*---------------------------------------------------------------------------*/
#define NUM_MICROSECS_IN_SEC     (1000000)

#ifdef LINUX
struct timeval tvstart, tvend, tvstartint, tvendint, copcstart, copcend, copcstart1, copcend1;
struct timezone zstart;
#else
void timerStart();
unsigned long timerRead();
volatile unsigned long timerDiff;
volatile unsigned long start, timerStart_ccs, timerEnd;
float lTempTemp;
unsigned long Total_time = 0;
#endif

/**---------------------- Function for IDMA3_create ------------------------------------------------**/
extern IALG_Handle IDMA3_create(IDMA3_Fxns *fxns, IALG_Handle p);

/* ------------------------- Halfbuffer callback function declaration ------------------------------*/
XDAS_Int32 JPEGDEC_TI_DM350_HalfBufCB(XDAS_Int32, void *arg);

void JpegDecError(short val)
{
    printf("JPEG Dec error : %d\n", val);
}

/* ------------------------- DATA DECLARATIONS ------------------------------*/
Int32 areaDecode;
char baseParams[STRING_SIZE];
char csvParams[STRING_SIZE];

/** ------------------------ Media to Ring structure ---------------------------*/
typedef struct Media2Ring {
    Int8* mediaPtr;
    Int8* ringCurPtr;
    Int8* ringStartPtr;
    Int8* ringEndPtr;
} Media2Ring;

/**------------File I/O variables ------------------------------------**/
extern FILE *fConfigFile, *ftestFile, *fjpegFile, *fparamsFile;
extern FILE *fdumpFile;
FILE *fDumpFile;
FILE *CSVFileHandle,*CSVPerfHandle;
FILE *fileLog;


/**------------- Token Map array for inputs from testparams.cfg file.   ------------------------**/
sTokenMapping sTokenMap[14] =
{
    {"Resize",     			&extn_dynamicParams.resizeOption,sizeof(extn_dynamicParams.resizeOption)},
    {"DisplayWidth", 		&dynamicParams.displayWidth,sizeof(dynamicParams.displayWidth)      },
    {"rotation", 			&extn_dynamicParams.rotation,sizeof(extn_dynamicParams.rotation) },
    {"areaDecode",   		&areaDecode,sizeof(areaDecode) },
    {"maxWidth", 			&params.maxWidth,sizeof(params.maxWidth)  },
    {"maxHeight", 			&params.maxHeight,sizeof(params.maxHeight)  },
    {"forceChromaFormat", 	&params.forceChromaFormat,sizeof(params.forceChromaFormat)  },
    {"dataEndianness", 		&params.dataEndianness ,sizeof(params.dataEndianness) },
    {"subRegionUpLeftX", 	&extn_dynamicParams.subRegionUpLeftX,sizeof(extn_dynamicParams.subRegionUpLeftX) },
    {"subRegionUpLeftY", 	&extn_dynamicParams.subRegionUpLeftY,sizeof(extn_dynamicParams.subRegionUpLeftY) },
    {"subRegionDownRightX", &extn_dynamicParams.subRegionDownRightX,sizeof(extn_dynamicParams.subRegionDownRightX) },
    {"subRegionDownRightY", &extn_dynamicParams.subRegionDownRightY,sizeof(extn_dynamicParams.subRegionDownRightY)},
	{"decodingPreset", 		&extn_dynamicParams.decodingPreset,sizeof(extn_dynamicParams.decodingPreset)},
    {NULL,           	NULL                             }
};


/*--------------------- Linux Profile Related Macros  --------------------------*/
#define calcprofile(structstart,structend) ((structend.tv_sec*NUM_MICROSECS_IN_SEC)+structend.tv_usec)-((structstart.tv_sec*NUM_MICROSECS_IN_SEC)+structstart.tv_usec);

#define profstruct_init(structvar)\
       	structvar.tv_sec = 0,\
		structvar.tv_usec = 0\
 
/* ==========================================================================
 * *
 * *@func   main()
 * *
 * *@brief  Main function to kickstart the application
 * *
 * *@ret    success/fail
 * *
 * * ============================================================================
 * */

int main(int argc, char **argv)
{

    /*-------------------------------------------------------------------------*/
    /*   local variables and arrays                                                      */
    /*-------------------------------------------------------------------------*/
    int bufferSize, bytesConsumed, i, chroma_i, chroma_j;
    int lStatus,rowno;
    XDAS_Int8 line[STRING_SIZE], inFile[STRING_SIZE],
    testFile[STRING_SIZE], paramsFile[STRING_SIZE], testCompliance;
    int start = 0, ustart = 0, end = 0, uend = 0, processTime = 0, processTimeTotal = 0, processTimeCOPC1 =0, processTimeCOPC =0, actTime =0, deactTime =0, deactTime1 = 0;
    unsigned int Offset;
    int baseonly;
    Int32 retVal;
    int size;
    Uint32 totalAU, numAU;
    Uint16 mcuWidth[]= {16, 16, 16, 16, 16, 8, 8, 8, 8, 8};
    Uint16 mcuHeight[]= {8, 16, 8, 8, 8, 8, 8, 8, 8, 16};
    unsigned char *ExternalGlobalMemPoolBase, *pInternalDataMemoryBase;
    XDAS_Int8 * buf1;
    XDAS_Int8 * buf_org;    
    /*-------------------------------------------------------------------------*/
    /*   Cache Settings for LINUX                                              */
    /*-------------------------------------------------------------------------*/
#ifdef LINUX
    CMEM_AllocParams memParams;
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_CACHED;
    memParams.alignment=256;

    CACHE_InitPrm_t cacheFn;
    cacheFn.wbCb = CMEM_cacheWb;
    cacheFn.invCb = CMEM_cacheInv;
    cacheFn.wbInvCb = CMEM_cacheWbInv;
#endif

#ifdef ENABLE_RMAN // IRES/RMAN Related declarations
     IRES_Status iresStatus;
     Int Size =0;
     Int scratchId =0;
     Bool result = TRUE;
     IRES_Fxns *resFxns = &JPEGDEC_TI_IRES;
     IRESMAN_Edma3ChanParams configParams;
     IRESMAN_VicpParams iresmanConfigParams;
	 IRESMAN_AddrSpaceParams addrspaceConfigParams;
#endif
    /*-------------------------------------------------------------------------*/
    /*  Declaring Algorithm specific handle                                    */
    /*-------------------------------------------------------------------------*/
    IALG_Handle handle;

    /*-------------------------------------------------------------------------*/
    /*  Base Class Structures for status, input and output arguments.          */
    /*-------------------------------------------------------------------------*/
    IIMGDEC1_Status          status_base;
    IIMGDEC1_InArgs          inArgs_base;
    IIMGDEC1_OutArgs         outArgs_base;

    /*-------------------------------------------------------------------------*/
    /*  Extended Class Structures for status, input and output arguments.          */
    /*-------------------------------------------------------------------------*/
    IJPEGDEC_Status          status;
    IJPEGDEC_InArgs          inArgs;
    IJPEGDEC_OutArgs         outArgs;

    IIMGDEC1_Fxns            *IIMGDECFxns;

    /*-------------------------------------------------------------------------*/
    /*  Input/Output Buffer Descriptors                                        */
    /*-------------------------------------------------------------------------*/
    XDM1_BufDesc inputBufDesc, outputBufDesc;

    /*-------------------------------------------------------------------------*/
    /*  OTHER STRUCTURE VARIABLES                                              */
    /*-------------------------------------------------------------------------*/

    jpegdec_params ljpegdecparams;

    TestType testType;

    Media2Ring media2ring;

    /** ---------------------- color format array -------------------------------*/
    char* colorf[]={"YUV422", "YUV420", "YUV422",
                    "YUV422IL", "YUV422IL", "YUV444",
                    "YUV411", "GRAY", "RGB", "YUV_422VP"
                   };

    /*-------------------------------------------------------------------------*/
    /*  Initializing the path of file containing the test vectors to be test and log files.  */
    /*-------------------------------------------------------------------------*/

#ifdef LINUX
    Int8 *fileCfgName = "../TestVecs/Config/Testvecs.cfg";
    Int8 *fileLogName = "../TestVecs/Config/log.txt";
#else
    Int8 *fileCfgName = "..\\..\\Test\\TestVecs\\Config\\Testvecs_ccs.cfg";
    Int8 *fileLogName = "..\\..\\Test\\TestVecs\\Config\\log.txt";
#endif

#if 0//ndef LINUX
    resetTimer(3);
    setupTimerD32UC_Mode_TIM12(3,0xffffffff);	// JESSE: change from 0xffff, 32 bit wraparound, not 16
#endif

    /*---------------------------------------------------------------------------*/
    /*  Allocating contigous memory for input & output data buffers, ring buffer
    	and external memory in LINUX                            */
    /*---------------------------------------------------------------------------*/
#ifdef LINUX
    /* Cache Initialization */
    
    CMEM_init();
    ExternalGlobalMemPool = ExternalGlobalMemPoolBase =
                                CMEM_alloc(EXTERNAL_DATA_MEM_SIZE,&memParams);
    ringbuf = CMEM_alloc(RINGBUF_SIZE,&memParams);
    bJpegStream = CMEM_alloc(JPEG_MAX_NUM_JPEG_BYTES,&memParams);
    bDecodedYCC = CMEM_alloc(JPEG_MAX_NUM_YCC_BYTES,&memParams);
#endif

#ifdef ENABLE_RMAN // IRES/RMAN Related declarations
     iresStatus = RMAN_init();

#ifdef _DBG_MSG
     printf("iresStatus %d\n", iresStatus);
#endif     

     if (IRES_OK != iresStatus) {
         printf("RMAN initialization Failed \n");
         return -1;
        }
#ifdef _DBG_MSG
     printf("RMAN initialization done \n");
#endif     
    
#ifndef LINUX
        /* Call the functions to enable ARM926 FIQ and do some basic
         * setup to AINTC to accept KLD INTC (arm968) interupt in 
         * FIQ pin of Arm926  
         */
        ARM926_enable_FIQ();  /* SWI call to enable interrupts */
        ARM926_INTC_init();  /* Init AINTC */
#endif

#endif //IRES/RMAN related code ends here

#ifdef ENABLE_RMAN // IRES/RMAN Related code
/** Supply initialization information for the RESMAN while registering        */
   
	size = sizeof(IRESMAN_VicpParams);
        iresmanConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
        iresmanConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
        iresmanConfigParams.baseConfig.size = size;

/* Register the VICP protocol/resource manager with the
        *      * generic resource manager */

       	iresStatus = RMAN_register(&IRESMAN_VICP2, (IRESMAN_Params *)&iresmanConfigParams);
#ifdef _DBG_MSG
	printf("iresStatus register %d\n", iresStatus);
#endif        
	if (IRES_OK != iresStatus) {
	        printf("VICP Protocol Registration Failed \n");
	        return -1;
	}
#ifdef _DBG_MSG
	printf("VICP Protocol Registration Success \n");
#endif
	/**      * Supply initialization information for the EDMA3 RESMAN while registering */           

	size = sizeof(IRESMAN_Edma3ChanParams);
	configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
	configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
	configParams.baseConfig.size = size;
	iresStatus = RMAN_register(&IRESMAN_EDMA3CHAN, (IRESMAN_Params *)&configParams);
	if (IRES_OK != iresStatus) {
		printf("EDMA3 Protocol Registration Failed \n");
		return -1;
	}

#ifdef _DBG_MSG
	printf("EDMA3 Protocol Registration Success \n");
#endif
	size = sizeof(IRESMAN_AddrSpaceParams);
    addrspaceConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    addrspaceConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    addrspaceConfigParams.baseConfig.size = size;

    iresStatus = RMAN_register(&IRESMAN_ADDRSPACE, (IRESMAN_Params *)&addrspaceConfigParams);

    if (IRES_OK != iresStatus) {
	    printf("ADDRSPACE Protocol Registration Failed \n");
	return -1;
	}
#ifdef _DBG_MSG	
	printf("ADDRSPACE Protocol Registration Success \n");
#endif
#endif
    
    /*--------------------------------------------------------------------------------*/
    /*--Token support to test extended and base class with same executable in Linux---*/
    /*-------- Token = -ext then its extended class-----------------------------------*/
    /*-------- When there is no token then its base class ----------------------------*/
    /*--------------------------------------------------------------------------------*/
#ifdef LINUX
    if (argc==2)
    {
        strncpy(baseParams,argv[1],256);
        if (!strcmp(baseParams,"-ext"))
        {
            baseonly=0;
        }
        else
        {
            exit(0);
        }
    }
    else
    {
        baseonly=1;
    }
#else
    ExternalGlobalMemPoolBase = ExternalGlobalMemPool;
    baseonly=0;
#endif

    /*-----clearing all the buffers----------------------------------------*/
    memset(ExternalGlobalMemPoolBase, 0, EXTERNAL_DATA_MEM_SIZE);
    memset(bJpegStream, 0, JPEG_MAX_NUM_JPEG_BYTES);
    memset(bDecodedYCC, 0, JPEG_MAX_NUM_YCC_BYTES);
    memset(ringbuf, 0, RINGBUF_SIZE);

    /**-----Initialising Test Framework when config file is used  ---------**/
    if (initTestFramework(fileCfgName, &testType, sTokenMap)== XDM_EFAIL)
    {
#ifdef _DBG_MSG
        printf("\nTest framework could not be initialized, exiting ...\n");
#endif
        exit(1);
    }

    /*------ Initialised to neglect the First Row of CSV when csv is used----*/
    rowno = 2;

    /*---------- Open log file -----------------------------------------------*/
    fileLog= fopen(fileLogName, "wt");

    /*-----------------------------------------------------------------------*/
    /*  Setting the sizes of Base Class and Extended Class Objects                              */
    /*-----------------------------------------------------------------------*/
    if (baseonly == 0)
    {
        status.imgdecStatus.size = sizeof(IJPEGDEC_Status);
        inArgs.imgdecInArgs.size = sizeof(IJPEGDEC_InArgs);
        outArgs.imgdecOutArgs.size = sizeof(IJPEGDEC_OutArgs);
        params.size                = sizeof(IJPEGDEC_Params);
        dynamicParams.size = sizeof(IJPEGDEC_DynamicParams);
    }
    else
    {
        status_base.size = sizeof(IIMGDEC1_Status);
        inArgs_base.size = sizeof(IIMGDEC1_InArgs);
        outArgs_base.size = sizeof(IIMGDEC1_OutArgs);
        params.size  = sizeof(IIMGDEC1_Params);
        dynamicParams.size = sizeof(IIMGDEC1_DynamicParams);
    }
    /**---------- Loop to run number of test cases in config file -------------**/


    for (;;) {

        bytesConsumed= 0;
        retVal=nextTestSet();
        if (retVal==XDM_EFAIL || retVal==1)
        {
            break;
        }

        /*-------------------------------------------------------------------*/
        /*  Create the Algorithm object (instance)                           */
        /*-------------------------------------------------------------------*/
        /*-------------------------------------------------------------------*/
        /*  Algorithm create call. This function will allocate memory for    */
        /*  the algorithm handle and for all the buffers (memtabs) required  */
        /*  by the algorithm and initialize them accordingly. The alg handle */
        /*  is returned.                                                     */
        /*-------------------------------------------------------------------*/

	   
        if (baseonly == 0)
        {
            /**------------- For Extended Class ----------------------------------**/
            extn_params.imgdecParams= params;
            extn_params.halfBufCB = (XDAS_Void(*)())JPEGDEC_TI_DM350_HalfBufCB;
            extn_params.halfBufCBarg = (void *) &media2ring;


            if ((handle = (IALG_Handle) ALG_create((IALG_Fxns *) &JPEGDEC_TI_IJPEGDEC,
                                                   (IALG_Handle) NULL,
                                                   (IALG_Params *)
                                                   &extn_params)) == NULL)
            {
                printf("\nFailed to Create Instance.Exiting .");
                exit(-1);
            }

        }
        else
        {
            /**------------- For Base Class ----------------------------------**/
            if ((handle = (IALG_Handle) ALG_create((IALG_Fxns *) &JPEGDEC_TI_IJPEGDEC,
                                                   (IALG_Handle) NULL,
                                                   (IALG_Params *) &params)) == NULL)
            {
                printf("\nFailed to Create Instance.Exiting .");
                exit(-1);
            }
        }
	
#ifdef _DBG_MSG
        printf("Assigning Algorithm handle fxns field to IIMGDECfxns\n");
#endif

#ifdef ENABLE_RMAN
	/* Create an instance of an algorithm that implements IALG and IRES_Fxns */
	iresStatus = RMAN_assignResources((IALG_Handle)handle, resFxns,scratchId);
#ifdef _DBG_MSG
	printf("iresStatus %d\n", iresStatus);
#endif
	if (IRES_OK != iresStatus) {
		printf("Assign Resource Failed \n");
	        result = FALSE;
	    }
#ifdef _DBG_MSG
	printf("Assign Resource Success \n");
#endif
#endif //IRES/RMAN code ends here.
	
	/**-----------  Assigning Algorithm handle fxns field to IIMGDECfxns----------**/
        IIMGDECFxns = (IIMGDEC1_Fxns *)handle->fxns;
        extn_dynamicParams.imgdecDynamicParams = dynamicParams;

        /*-----------------------------------------------------------------------*/
        /*  The GETBUFINFO call gives information for number and size of input   */
        /*  and output buffers. For this call, the actual width and height       */
        /*  of the picture is not known hence, this control call returns the out */
        /*  buffer sizes based on the maxHeight and maxWidth.                    */
        /*-----------------------------------------------------------------------*/
        if (baseonly == 0)
        {
            /**------------- For Extended Class ----------------------------------**/
            retVal= IIMGDECFxns->control((IIMGDEC1_Handle)handle, XDM_GETBUFINFO,
                                         (IIMGDEC1_DynamicParams *)&extn_dynamicParams,
                                         (IIMGDEC1_Status *)&status);
        }
        else
        {
            /**------------- For Base Class --------------------------------------**/
            retVal= IIMGDECFxns->control((IIMGDEC1_Handle)handle,
                                         XDM_GETBUFINFO,
                                         &dynamicParams,
                                         &status_base);
        }
        if (retVal== XDM_EFAIL)
        {
            printf("\n Error in control call\n");
            ALG_delete(handle);
            exit(-1);
        }

        memset(bJpegStream, 0, JPEG_MAX_NUM_JPEG_BYTES);
        memset(bDecodedYCC, 0, JPEG_MAX_NUM_YCC_BYTES);


        /*-------------------------------------------------------------------------*/
        /*  Initialize the media2ring structure for extended class.                */
        /*Set the size of ring buffer using the macro RINGBUF_SIZE which is defined*/
        /* in the header file testframework.h--------------------------------------*/
        /*-------------------------------------------------------------------------*/
        media2ring.ringStartPtr = ringbuf;
        media2ring.ringEndPtr = ringbuf + RINGBUF_SIZE;
        media2ring.mediaPtr= bJpegStream;
        media2ring.ringCurPtr= ringbuf;
        bufferSize= testReadJpegfile(bJpegStream, JPEG_MAX_NUM_JPEG_BYTES);
if (baseonly == 0)
   {
        memcpy(media2ring.ringCurPtr, media2ring.mediaPtr, RINGBUF_SIZE);
        media2ring.mediaPtr += RINGBUF_SIZE;
}
	

	if (baseonly == 0)
        {
            inArgs.imgdecInArgs.size = sizeof(IJPEGDEC_InArgs);
            inArgs.imgdecInArgs.numBytes        = bufferSize;
            inArgs.ringBufStart= (XDAS_UInt8*) ringbuf;
            inArgs.ringBufSize= RINGBUF_SIZE;

            /*-----------------------------------------------------------------------*/
            /*  Initialize the input buffer properties as required by algorithm      */
            /*  based on info received by preceding GETBUFINFO call for extended     */
            /*	class. First init the number of input bufs.                          */
            /*-----------------------------------------------------------------------*/
            inputBufDesc.numBufs = status.imgdecStatus.bufInfo.minNumInBufs;
            Offset = 0;
            for (i=0;i<inputBufDesc.numBufs;i++)
            {
                inputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)ringbuf + Offset);
                Offset +=  status.imgdecStatus.bufInfo.minInBufSize[i];
                inputBufDesc.descs[0].bufSize = RINGBUF_SIZE;
            }
            /*-----------------------------------------------------------------------*/
            /*  Initialize the output buffer properties as required by algorithm     */
            /*  based on info received by preceding GETBUFINFO call for extended     */
            /*	class. First init the number of input bufs.                          */
            /*-----------------------------------------------------------------------*/

            outputBufDesc.numBufs = status.imgdecStatus.bufInfo.minNumOutBufs;
            Offset = 0;
            for (i=0;i<outputBufDesc.numBufs;i++)
            {
                outputBufDesc.descs[i].buf = (XDAS_Int8 *) ((unsigned int) bDecodedYCC + Offset);
                Offset +=  status.imgdecStatus.bufInfo.minOutBufSize[i];
                outputBufDesc.descs[i].bufSize = status.imgdecStatus.bufInfo.minOutBufSize[i];
            }
        }

        else
        {
            inArgs_base.numBytes        = bufferSize;
            /*-----------------------------------------------------------------------*/
            /*  Initialize the input buffer properties as required by algorithm      */
            /*  based on info received by preceding GETBUFINFO call for base         */
            /*	class. First init the number of input bufs.                          */
            /*-----------------------------------------------------------------------*/

            inputBufDesc.numBufs = status_base.bufInfo.minNumInBufs;
            Offset = 0;
            for (i=0;i<inputBufDesc.numBufs;i++)
            {
                inputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)bJpegStream + Offset);
                Offset +=  status_base.bufInfo.minInBufSize[i];
                inputBufDesc.descs[0].bufSize = status_base.bufInfo.minInBufSize[i];
            }

            /*-----------------------------------------------------------------------*/
            /*  Initialize the output buffer properties as required by algorithm     */
            /*  based on info received by preceding GETBUFINFO call for base         */
            /*	class. First init the number of input bufs.                          */
            /*-----------------------------------------------------------------------*/
            outputBufDesc.numBufs = status_base.bufInfo.minNumOutBufs;
            Offset = 0;
	       
            for (i=0;i<outputBufDesc.numBufs;i++)
            {
                outputBufDesc.descs[i].buf = (XDAS_Int8 *) ((unsigned int) bDecodedYCC + Offset);
                Offset +=  status_base.bufInfo.minOutBufSize[i];
                outputBufDesc.descs[i].bufSize = status_base.bufInfo.minOutBufSize[i];
            }
        }
        /* Set as: XDM_PARSE_HEADER for only header decoding */
        /* XDM_DECODE_AU: for actual image decoding          */

        if (params.forceChromaFormat == XDM_YUV_420SP)
	{
	   bDecodedchroma = (Int8 *)outputBufDesc.descs[1].buf;
   	}
	
	dynamicParams.decodeHeader = XDM_DECODE_AU;
        dynamicParams.numAU = XDM_DEFAULT;

        extn_dynamicParams.imgdecDynamicParams = dynamicParams;
        extn_dynamicParams.imgdecDynamicParams.decodeHeader = XDM_DECODE_AU;
        extn_dynamicParams.imgdecDynamicParams.numAU= XDM_DEFAULT;
        extn_dynamicParams.disableEOI = 0;

//        extn_dynamicParams.subRegionUpLeftY = (Int16)subRegionUpLeftY1;
//        extn_dynamicParams.subRegionDownRightY = (Int16)subRegionDownRightY1;

        /*---------------------------------------------------------------------*/
        /*  The SETPARAMS call gives information to the algorithm about the    */
        /*  dynamic parameters that have been initialized.                     */
        /*---------------------------------------------------------------------*/
        if (baseonly == 0)
        {
            retVal = IIMGDECFxns->control((IIMGDEC1_Handle)handle, XDM_SETPARAMS,
                                          (IIMGDEC1_DynamicParams *)&extn_dynamicParams,
                                          (IIMGDEC1_Status *)&status);
        }
        else
        {
            retVal = IIMGDECFxns->control((IIMGDEC1_Handle)handle,
                                          XDM_SETPARAMS,
                                          &dynamicParams,
                                          &status_base);

        }

        if (retVal== XDM_EFAIL)
        {
            printf("\n Error control Set params command Test\n");
            printf("status.extendederror %d\n",status.imgdecStatus.extendedError);
            ALG_delete(handle);
            continue;
        }

#ifdef _DBG_MSG
        printf("Set Run time params..\n");
#endif

#ifdef LINUX
        profstruct_init(tvstart);
        profstruct_init(tvend);
        gettimeofday(&tvstart, 0);
#endif
        /*---------------- Activate the Algorithm --------------------------------------   */

#ifdef _DBG_MSG
	printf("before activate\n");
#endif
	
	handle->fxns->algActivate(handle);

#ifdef LINUX
        profstruct_init(tvstartint);
        profstruct_init(tvendint);
        gettimeofday(&tvstartint, 0);
#else
        //startTimerD32UC_Mode_TIM12(3);
        //timerStart_ccs= getCnt12 (3);
#endif

#ifdef _DBG_MSG
        printf("Activation done\n");
#endif

	/*---------------------------------------------------------------------*/
        /*  start the decode process by calling the process function.           */
        /*---------------------------------------------------------------------*/

        if (baseonly == 0)
        {
            retVal = IIMGDECFxns->process((IIMGDEC1_Handle)handle,
                                              (XDM1_BufDesc *)&inputBufDesc,
                                              (XDM1_BufDesc *)&outputBufDesc,
                                              (IIMGDEC1_InArgs *)&inArgs,
                                              (IIMGDEC1_OutArgs *)&outArgs);
            
        }
        else
        {
            retVal = IIMGDECFxns->process((IIMGDEC1_Handle)handle,
                                          &inputBufDesc,
                                          &outputBufDesc,
                                          &inArgs_base,
                                          &outArgs_base);
        }
            if (retVal== XDM_EFAIL) 
	    {
                printf("!!!! Error during jpeg decode !!!!\n");
                break;
            }
	else
	{
        if (baseonly == 0)
            bytesConsumed += outArgs.imgdecOutArgs.bytesConsumed;
	else
            bytesConsumed += outArgs_base.bytesConsumed;

#ifdef LINUX
        gettimeofday(&tvendint, 0);
#else
        //timerEnd= getCnt12 (3);
        //timerDiff= timerEnd-timerStart_ccs;
        //lTempTemp = ((timerDiff*9)) / 216;
#endif

        /*---------------- Deactivate the Algorithm --------------------------------------   */
        handle->fxns->algDeactivate(handle);

#ifdef LINUX
        gettimeofday(&tvend, 0);
        processTime = calcprofile(tvstartint, tvendint);
        processTimeTotal = calcprofile(tvstart, tvend);
        processTimeCOPC = calcprofile(copcstart, copcend);
        actTime = calcprofile(tvstart, tvstartint);
        deactTime = calcprofile(tvendint, tvend);
#endif

        
	if (baseonly == 0)
        {
            /*------------------------------------------------------------------*/
            /*--  Invoke a GETSTATUS control call to get the extended error     */
            /*  , image height, image width, outputchromaformat and other status*/
            /*   related to the image decoded ----------------------------------*/
            /*------------------------------------------------------------------*/
            IIMGDECFxns->control((IIMGDEC1_Handle)handle, XDM_GETSTATUS,
                                 (IIMGDEC1_DynamicParams *)&extn_dynamicParams,(IIMGDEC1_Status *)&status);

            printf("%s \t %d bytes \t %d x %d \t %.2f:1 \t\n",
                   colorf[status.inputChromaFormat],
                   bytesConsumed,
                   status.imgdecStatus.outputWidth,
                   status.imgdecStatus.outputHeight,
                   (float)2*(status.imgdecStatus.outputWidth
                             * status.imgdecStatus.outputHeight)/(float) bytesConsumed);

            fflush(fileLog);

            /* ================================================== */
            /* Open YUV file for OUTPUT to store the decoded data */
            /* ================================================== */

            printf("================Test Summary======================\n");
            printf("Color format %s\n", colorf[status.inputChromaFormat]);
            printf("Total bytes consumed %d\n", bytesConsumed);
            printf( "status.imgdecStatus.outputWidth = %d... \n",status.imgdecStatus.outputWidth);
            printf( "dynamicParams.displayWidth = %d... \n",dynamicParams.displayWidth);
            printf( "status.imgdecStatus.outputHeight = %d... \n",status.imgdecStatus.outputHeight);
	    printf( "status.imgdecStatus.extendedError = %x... \n",status.imgdecStatus.extendedError);
            printf("==================================================\n");

            /*-----------------------------------------------------------------*/
            /*  Dumping the output image for extended class					   */
            /*-----------------------------------------------------------------*/
#ifdef _DBG_MSG
            printf( "main: making YUV... \n");
#endif

if (dynamicParams.displayWidth <= status.imgdecStatus.outputWidth)
{
	dynamicParams.displayWidth = status.imgdecStatus.outputWidth;
}
else
{
		status.imgdecStatus.outputWidth = dynamicParams.displayWidth;
}

if(params.forceChromaFormat == 4 | params.forceChromaFormat == 0)
{
         fwrite( bDecodedYCC,(status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight)*2,1,fdumpFile);
}
else
{
#ifdef LINUX
        bufnew = malloc(status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight>>1);
#endif
//	buf_org = (XDAS_Int8 *)outputBufDesc.descs[1].buf; 
	buf_org = (XDAS_Int8 *)bDecodedchroma;
        buf1 = bufnew + (int)((status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight)>>2);
       for(chroma_i=0;chroma_i<status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight*0.25;chroma_i++)
       {
         buf1[chroma_i] = buf_org[2*chroma_i+1];
         bufnew[chroma_i] = buf_org[2*chroma_i];
       }
       fwrite( bDecodedYCC, 1,((status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight)),fdumpFile);
       fwrite(bufnew, 1,(status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight)*0.25,fdumpFile);
       fwrite(buf1, 1,(status.imgdecStatus.outputWidth*status.imgdecStatus.outputHeight)*0.25,fdumpFile);
       
}
	   
#ifdef _DBG_MSG
            printf("yuv data is dumped\n");
#endif

        }
        else
        {
            /*------------------------------------------------------------------*/
            /*--  Invoke a GETSTATUS control call to get the extended error     */
            /*  , image height, image width, outputchromaformat and other status*/
            /*   related to the image decoded ----------------------------------*/
            /*------------------------------------------------------------------*/
            IIMGDECFxns->control((IIMGDEC1_Handle)handle,XDM_GETSTATUS,&dynamicParams,&status_base);

            printf("%d bytes \t %d x %d \t %.2f:1\n",
                   bytesConsumed,
                   status_base.imageWidth,
                   status_base.outputHeight,
                   (float)2*(status_base.imageWidth * status_base.outputHeight)/(float) bytesConsumed);
            printf("================Test Summary======================\n");
            printf("Total bytes consumed %d\n", bytesConsumed);
            printf( "status.imageWidth = %d... \n",status_base.imageWidth);
            printf( "status.imageHeight = %d... \n",status_base.outputHeight);
            printf("==================================================\n");

            /*-----------------------------------------------------------------*/
            /*  Dumping the output image for base class					   */
            /*-----------------------------------------------------------------*/
if(params.forceChromaFormat == 4 | params.forceChromaFormat == 0)
{	
	    fwrite( bDecodedYCC,
                    (status_base.imageWidth*status_base.outputHeight)*2,
                    1,
                    fdumpFile);
}
else
{
#ifdef LINUX
	bufnew = malloc((status_base.imageWidth*status_base.outputHeight)>>1);
#endif
	buf_org = (XDAS_Int8 *)bDecodedchroma;
	//	buf_org = (XDAS_Int8 *)outputBufDesc.descs[1].buf; 
        buf1 = bufnew + (int)((status_base.imageWidth*status_base.outputHeight)>>2);
       for(chroma_i=0;chroma_i<status_base.imageWidth*status_base.outputHeight*0.25;chroma_i++)
       {
         buf1[chroma_i] = buf_org[2*chroma_i+1];
         bufnew[chroma_i] = buf_org[2*chroma_i];
       }
       fwrite( bDecodedYCC, 1,((status_base.imageWidth*status_base.outputHeight)),fdumpFile);
       fwrite(bufnew, 1,(status_base.imageWidth*status_base.outputHeight)*0.5,fdumpFile);
}

        }
}
        /*-----------------------------------------------------------------------*/
        /* Output file close                                                     */
        /*-----------------------------------------------------------------------*/
        fclose(fdumpFile);

#ifdef ENABLE_RMAN
/*** 		Free resources assigned to this algorihtm *                   */
         iresStatus = RMAN_freeResources((IALG_Handle)(handle), resFxns, scratchId);
          if (IRES_OK != iresStatus) {
	  printf("Free Resource Failed \n");
          result = FALSE;
	  }
#ifdef _DBG_MSG
         printf("Free Resource : Success \n");
#endif
#endif
	 
	

        /*-----------------------------------------------------------------------*/
        /*--------------  Call XDM_RESET --------------------                    */
        /*-----------------------------------------------------------------------*/
        if (baseonly == 0)
        {

            retVal= IIMGDECFxns->control((IIMGDEC1_Handle)handle, XDM_RESET,
                                         (IIMGDEC1_DynamicParams *)&extn_dynamicParams,
                                         (IIMGDEC1_Status *)&status);
            if (retVal== XDM_EFAIL)
            {
                printf("\n Error in control call XDM_RESET\n");
                ALG_delete(handle);
                exit(-1);
            }
        }
        else
        {
            retVal= IIMGDECFxns->control((IIMGDEC1_Handle)handle,
                                         XDM_RESET,
                                         &dynamicParams,
                                         &status_base);
            if (retVal== XDM_EFAIL)  {
                printf("\n Error in control call XDM_RESET\n");
                ALG_delete(handle);
                return -1;
            }
        }


	ALG_delete (handle);	 
	
    }

#ifdef ENABLE_RMAN
 /**      * Unregister the protocol          *           */
		iresStatus = RMAN_unregister(&IRESMAN_ADDRSPACE);
		if (IRES_OK != iresStatus) {
			printf("ADDRSPACE Unregister Protocol Failed \n");
	        return -1;
		}
		iresStatus = RMAN_unregister(&IRESMAN_EDMA3CHAN);
        if (IRES_OK != iresStatus) {
        printf("EDMA3 Unregister Protocol Failed \n");
        return -1;
        }
#ifdef _DBG_MSG
        printf("EDMA3 Unregister Protocol Success \n");
#endif
#if 1
        iresStatus = RMAN_unregister(&IRESMAN_VICP2);
        if (IRES_OK != iresStatus) {
        printf("VICP Unregister Protocol Failed \n");
        return (-1);
        }
#ifdef _DBG_MSG
        printf("VICP Unregister Protocol : Sucess \n");
#endif
#endif

	RMAN_exit();	
#endif
#ifdef _DBG_MSG
    printf("RMAN Exit Done \n");
#endif

    printf("End of test\n");

    /*-------Freeing the memories which are allocated thro' CMEM Driver -----*/
#ifdef LINUX
    CMEM_free(ringbuf,&memParams);
    CMEM_free(bJpegStream,&memParams);
    CMEM_free(bDecodedYCC,&memParams);
    CMEM_free(ExternalGlobalMemPoolBase,&memParams);
    CMEM_exit();
#endif

    /*-----------------------------------------------------------------------*/
    /* Log file close                                                     */
    /*-----------------------------------------------------------------------*/
    fclose(fileLog);
    exit(1);
}

/*====================================================================================
	Whenever this function is called by the codec, half buffer boundary is reached
    Application is in charge of transferring half of the buffer to the card/media
    jpeg processing on the other half can resume before transfer finishes.
======================================================================================*/
XDAS_Int32 JPEGDEC_TI_DM350_HalfBufCB(XDAS_Int32 bufPtr, void *arg)
{
    Uint32 i, x, y, numToXfer;
    Media2Ring *media2ring = arg;
    XDAS_Int8 *bufPtr_p, *ringCurPtr_p, *ringMediaPtr_p, *ringEndPtr_p,
    *ringStartPtr_p;

    bufPtr_p = (XDAS_Int8 *) bufPtr;
    ringCurPtr_p = (XDAS_Int8 *) media2ring->ringCurPtr;
    ringMediaPtr_p = (XDAS_Int8 *) media2ring->mediaPtr;

    if (bufPtr_p > ringCurPtr_p)
    {
        numToXfer = bufPtr_p - ringCurPtr_p;
        memcpy(media2ring->ringCurPtr, media2ring->mediaPtr,  numToXfer);
        media2ring->ringCurPtr += numToXfer;
        media2ring->mediaPtr += numToXfer;
    }
    else
    {
        ringEndPtr_p =
            (XDAS_Int8 *) media2ring->ringEndPtr;
        numToXfer = ringEndPtr_p - ringCurPtr_p;
        memcpy(media2ring->ringCurPtr, media2ring->mediaPtr,  numToXfer);
        media2ring->ringCurPtr += numToXfer;
        media2ring->mediaPtr += numToXfer;
        media2ring->ringCurPtr = media2ring->ringStartPtr;
        ringEndPtr_p =
            (XDAS_Int8 *) media2ring->ringEndPtr;
        ringCurPtr_p = ringStartPtr_p =
                           (XDAS_Int8 *) media2ring->ringStartPtr;
        numToXfer = bufPtr_p - ringStartPtr_p;
        memcpy(media2ring->ringCurPtr, media2ring->mediaPtr,  numToXfer);
        media2ring->ringCurPtr += numToXfer;
        media2ring->mediaPtr += numToXfer;
    }

    return IALG_EOK;
}


/*============================================================================
					TestApp_Compare_Ouput_and_Ref
					Compare Output Buffer and Reference Buffer
==============================================================================*/

XDAS_Int32 TestApp_Compare_Ouput_and_Ref(FILE * fRefFile,Int8 * outputData, XDAS_UInt32 lRefReadtoBytes)

{

    XDAS_Int32 diff,j;
    char *refbuf;
    XDAS_UInt32 BytesRead;

    refbuf = (char *)malloc(lRefReadtoBytes);
    BytesRead = fread(refbuf, 1, lRefReadtoBytes,fRefFile);

    for (j = 0; j < lRefReadtoBytes; j++)
    {
        diff = refbuf[j]- outputData[j];
    }

    if (diff == 0)
    {
        printf("Both Output and Reference are Same\n");
    }
    else
    {
        printf("Both Output and Reference are not Same\n");
    }
    free(refbuf);
    fflush(fRefFile);

    return(BytesRead);
}
