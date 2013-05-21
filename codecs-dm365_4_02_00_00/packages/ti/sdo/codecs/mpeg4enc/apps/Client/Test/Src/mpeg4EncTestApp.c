/* Standard C header files                                                    */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* MPEG4 Encoder Interface header files                                                */
#include "tistdtypes.h"
#include "imp4venc.h"
/* Client header file                                                         */
#include "TestAppEncoder.h"
#define APP_DEFND_NUMFRAMES 5//3000
/* Input buffer allocation                                                    */
#define STREAMBUF_SIZE (512*1024)

#define ENABLE_RMAN
/* Header Files for IRES/RMAN */
#ifdef ENABLE_RMAN
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>
#include <ti/sdo/fc/edma3/edma3_config.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
//#include <ti/sdo/utils/trace/gt.h>
#include "mp4venc_ti_ires.h"
#endif

//#define USERDATA_TEST

#ifdef LINUX
#include <sys/time.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#define STRING_SIZE 256


/***************/

XDAS_Int8 *inputData;
XDAS_Int8 *OrgPictureY;
XDAS_Int8 *OrgPictureCb;
XDAS_Int8 *OrgPictureCr;
XDAS_Int8 *outputData;
XDAS_Int8 *MVData;
XDAS_Int8 *reconData;

#define NUM_MICROSECS_IN_SEC     (1000000)

extern unsigned char *ExternalGlobalMemPool;
extern unsigned char *pInternalDataMemory;
unsigned char *ExternalGlobalMemPoolBase, *pInternalDataMemoryBase;

struct timeval tvstart, tvend, tvstartint, tvendint;
struct timeval tvstart_activate, tvend_activate, tvstartint_activate, tvendint_activate;
struct timeval tvstart_deactivate, tvend_deactivate, tvstartint_deactivate, tvendint_deactivate;

#else

//#include <csl_intc.h>
#include "testapp_arm926intc.h"
#ifdef TIMER_PROFILE
//#include <csl_psc.h>
void timerStart();
unsigned long timerRead();
volatile unsigned long timerDiff;
volatile unsigned long start, timerEnd;
unsigned long Total_time = 0;
#endif




static XDAS_Int8  inputData[INPUT_BUFFER_SIZE];
XDAS_Int8 * OrgPictureY  = &inputData[0];
XDAS_Int8 * OrgPictureCb = (&inputData[0])  + (IMAGE_WIDTH*IMAGE_HEIGHT);
XDAS_Int8 * OrgPictureCr = (&inputData[0])  + (IMAGE_WIDTH*IMAGE_HEIGHT) + ((IMAGE_WIDTH*IMAGE_HEIGHT)/2);
XDAS_Int8  outputData[STREAMBUF_SIZE];

/* Buffer for dtoring motion vectors */
XDAS_Int8 MVData[MVDATA_SIZE];

#endif

/*for queue mapping*/
//extern unsigned int *virt_dmaq4;


/*Extended Class structures*/
IMP4VENC_Params extn_params;
IVIDENC1_Params baseParams;
IMP4VENC_DynamicParams   extn_dynamicParams;
IVIDENC1_DynamicParams   dynamicParams;


#ifdef PROFILE_IMCOP
XDAS_Int32 TotalTime_IMCOP = 0;
XDAS_Int32 TimeDiff_IMCOP = 0;
#endif

/* Mapping of Prameters from config file string to the place holder           */
sTokenMapping sTokenMap[] = {
    {"ImageHeight", &extn_params.videncParams.maxHeight},
    {"ImageWidth", &extn_params.videncParams.maxWidth},
    {"FrameRate", &extn_params.videncParams.maxFrameRate},
    {"Bitrate", &extn_params.videncParams.maxBitRate},
    {"ChromaFormat", &extn_params.videncParams.inputChromaFormat},

    /*Codec specific extended parameters */
    {"RCAlgo", &extn_params.videncParams.rateControlPreset},
    {"subWindowHeight", &extn_params.subWindowHeight},
    {"subWindowWidth", &extn_params.subWindowWidth},
    {"IntraPeriod", &extn_dynamicParams.videncDynamicParams.intraFrameInterval},
    {"intraAlgo", &extn_dynamicParams.intraAlgo},
    {"numMBRows", &extn_dynamicParams.numMBRows},
    {"initQ", &extn_dynamicParams.initQ},
    {"rcQ_MAX", &extn_dynamicParams.rcQMax},
    {"rcQ_MIN", &extn_dynamicParams.rcQMin},
    {"rateFix", &extn_dynamicParams.rateFix},
    {"rateFixRange", &extn_dynamicParams.rateFixRange},
    {"rotation", &extn_params.rotation},
    {"meAlgo", &extn_dynamicParams.meAlgo},
    {"SkipMBAlgo", &extn_dynamicParams.skipMBAlgo},
    {"UMV", &extn_dynamicParams.unrestrictedMV},
    {"VBV_size",&extn_params.vbvSize},
    {"targetBitrate",&extn_dynamicParams.videncDynamicParams.targetBitRate},
    {"minBitrate", &extn_params.minBitRate},
    {"peakBufWindow", &extn_params.peakBufWindow},
    {NULL, NULL}
};

sTokenMapping sTokenMap_base[] =
{
    {"ImageHeight", &baseParams.maxHeight},
    {"ImageWidth", &baseParams.maxWidth},
    {"FrameRate", &baseParams.maxFrameRate},
    {"Bitrate", &baseParams.maxBitRate},
    {"ChromaFormat", &baseParams.inputChromaFormat},
    {NULL, NULL}
};


XDAS_Int8 line[STRING_SIZE], inFile[STRING_SIZE],
testFile[STRING_SIZE], paramsFile[STRING_SIZE], testCompliance;

XDAS_Int8 *pOutputBuf[XDM_MAX_IO_BUFFERS];
XDAS_Int32 outBufSize[XDM_MAX_IO_BUFFERS];
void temp_trace_init(void);
XDAS_Int32 FormatConversion_420Pto420SP(FILE * finFile, XDAS_UInt32 frameCount,
                                        IVIDEO1_BufDescIn * inputBufDesc);
/* Main Function acting as a client for Video Encode Call                     */
XDAS_Int32 main(int argc , char **argv)
{

    /* File I/O variables */
    FILE *fConfigFile, *ftestFile, *finFile, *fparamsFile;
#ifdef LINUX
    CMEM_AllocParams memParams;
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_CACHED;
    memParams.alignment=256;

#endif
#ifdef LINUX
    XDAS_Int8 *fname = "../TestVecs/Config/Testvecs.cfg";
#else
    XDAS_Int8 *fname = "..\\..\\Test\\TestVecs\\Config\\Testvecs_ccs.cfg";
#endif

    int size;
    int i,k;


    IVIDENC1_Fxns       *ividEncfxns;

    IMP4VENC_Status     status;
    IMP4VENC_InArgs     inArgs;
    IMP4VENC_OutArgs    outArgs;

    int Offset;

    /* Algorithm specific handle                                                */
    IALG_Handle handle;

    /* Input/Output Buffer Descriptor variables */
    IVIDEO1_BufDescIn inputBufDesc;
    XDM_BufDesc outputBufDesc;
    /* Output Buffer Management specific variables                              */
    XDAS_UInt32 bytesGenerated;

    /* Other variables                                                          */
    XDAS_Int32 retVal, frameCount;
    XDAS_Int32 countConfigSet;

    XDAS_Int32 lTemp = 0;
    int lCnt = 0;

    XDAS_Int32 TotalTime = 0;
    XDAS_Int32 TimeDiff = 0;

    char baseParamsStr[STRING_SIZE];
    int baseParamsOnly;

#ifdef PROFILE_ACTIVATE
    XDAS_Int32 TotalTime_ACTIVATE = 0;
    XDAS_Int32 TimeDiff_ACTIVATE = 0;
#endif

#ifdef PROFILE_DEACTIVATE
    XDAS_Int32 TotalTime_DEACTIVATE = 0;
    XDAS_Int32 TimeDiff_DEACTIVATE = 0;
#endif

#ifdef ENABLE_RMAN // IRES/RMAN Related declarations
//GT_init();
//GT_set("*" "=4567");
//	temp_trace_init();
    IRES_Status iresStatus;
    Int scratchId =0;
    Bool result = TRUE;
    IRES_Fxns *resFxns = &MP4VENC_TI_IRES;
    IRESMAN_Edma3ChanParams configParams;
    IRESMAN_VicpParams iresmanConfigParams;
    IRESMAN_AddrSpaceParams addrspaceConfigParams;
    iresStatus = RMAN_init();
    if (IRES_OK != iresStatus) {
        printf("RMAN initialization Failed \n");
        return -1;
    }
    printf("RMAN initialization done \n");

#ifndef LINUX	//def DM510_IPC_INTC_ENABLE
        /* Call the functions to enable ARM926 FIQ and do some basic
         * setup to AINTC to accept KLD INTC (arm968) interupt in 
         * FIQ pin of Arm926  
         */
        ARM926_enable_FIQ();  /* SWI call to enable interrupts */
        ARM926_INTC_init();  /* Init AINTC */
#endif

    /*
     * Supply initialization information for the RESMAN while registering
     */
    size = sizeof(IRESMAN_VicpParams);

    iresmanConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    iresmanConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    iresmanConfigParams.baseConfig.size = size;

    /* Register the VICP protocol/resource manager with the
    *      * generic resource manager */

    iresStatus = RMAN_register(&IRESMAN_VICP2, (IRESMAN_Params *)&iresmanConfigParams);

    if (IRES_OK != iresStatus) {
        printf("VICP Protocol Registration Failed \n");
        return -1;
    }
    printf("VICP Protocol Registration Success \n");
    /*
     *      * Supply initialization information for the EDMA3 RESMAN while registering
     *           */
    size = sizeof(IRESMAN_Edma3ChanParams);

    configParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    configParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    configParams.baseConfig.size = size;

    iresStatus = RMAN_register(&IRESMAN_EDMA3CHAN, (IRESMAN_Params *)&configParams);

    if (IRES_OK != iresStatus) {
        printf("EDMA3 Protocol Registration Failed \n");
        return -1;
    }
    printf("EDMA3 Protocol Registration Success \n");

    /*
     *      * Supply initialization information for the ADDRSPACE RESMAN while registering
     *           */
    size = sizeof(IRESMAN_AddrSpaceParams);

    addrspaceConfigParams.baseConfig.allocFxn = RMAN_PARAMS.allocFxn;
    addrspaceConfigParams.baseConfig.freeFxn = RMAN_PARAMS.freeFxn;
    addrspaceConfigParams.baseConfig.size = size;

    iresStatus = RMAN_register(&IRESMAN_ADDRSPACE, (IRESMAN_Params *)&addrspaceConfigParams);

    if (IRES_OK != iresStatus) {
        printf("ADDRSPACE Protocol Registration Failed \n");
        return -1;
    }
    printf("ADDRSPACE Protocol Registration Success \n");
#endif //IRES/RMAN related code ends here
#ifdef LINUX
    if (argc==2)
    {
        strcpy(baseParamsStr,argv[1]);
        if (!strcmp(baseParamsStr,"-ext"))
        {
            printf("\n----- Running in extended parameter mode -----\n");
            baseParamsOnly=0;

        }
        else
        {
            printf("Argument  -ext needed to run in  extended param mode\n");
            exit(0);
        }
    }

    else
    {
        printf("\n----- Running in base parameter mode -----\n");
        baseParamsOnly=1;
    }

#else
    baseParamsOnly=0;//0
#endif

#ifdef LINUX
    CMEM_init();
    /*memory allocation for buffers*/
    inputData = CMEM_alloc(INPUT_BUFFER_SIZE,&memParams);
    outputData = CMEM_alloc(OUTPUT_BUFFER_SIZE,&memParams);
    ExternalGlobalMemPoolBase = CMEM_alloc(EXTERNAL_DATA_MEM_SIZE,&memParams);
    ExternalGlobalMemPool = ExternalGlobalMemPoolBase ;
    //MVData = CMEM_alloc(MVDATA_SIZE,&memParams);
    //reconData = CMEM_alloc(1280*1080*1.5,&memParams);

#else

#ifdef TIMER_PROFILE
    VAL_chipInit();
    pscInit(0);
    lpscEnable(0, LPSC_IMCOP);
    lpscEnable(0, LPSC_TIMER3);
#endif

#endif

    /* Initialization of parameters needed for Algorithm Instance create */
        if (baseParamsOnly)
        {
            baseParams.size = sizeof(IVIDENC1_Params);
        }
        else
        {
            extn_params.videncParams.size = sizeof(IMP4VENC_Params);
        }
    //extn_dynamicParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
    outArgs.videncOutArgs.size = sizeof(IMP4VENC_OutArgs);
    inArgs.videncInArgs.size = sizeof(IMP4VENC_InArgs);
#ifdef USERDATA_TEST
    inArgs.insertUserData = 1;
    inArgs.lengthUserData =16;
#else
    inArgs.insertUserData = 0;
    inArgs.lengthUserData =0;
#endif
    /* Open Test Config File                                                    */
    fConfigFile = fopen(fname, "r");

    if (!fConfigFile)
    {
        printf("Couldn't open parameter file %s\n", fname);
        return XDM_EFAIL;
    }
    countConfigSet = 1;         /* Reset countConfigSet value to 1 */

    /* Read the Config File until it reaches the end of file                    */
    while (!feof(fConfigFile))
    {
        /* Read Compliance Checking parameter */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%d\n", &testCompliance);
            printf("\nTestcompliance = %d",testCompliance);
        } else {
            break;
        }
        /* Read Parameters file name */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%s", paramsFile);
            printf("\nParam file = %s\n",paramsFile);
        }
        else
        {
            break;
        }
        /* Read Input file name */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%s", inFile);
            printf("\nInput file = %s\n",inFile);
        }
        else
        {
            break;
        }

        /* Read Output/Reference file name */
        if (fgets(line, 254, fConfigFile))
        {
            sscanf(line, "%s", testFile);
            printf("\nOutput file = %s\n",testFile);
        }
        else
        {
            break;
        }

        printf("\n*******************************************");
        printf("\nRead Configuration Set %d", countConfigSet);
        printf("\n*******************************************");
        countConfigSet++;

        /* Open Parameters file */
        fparamsFile = fopen(paramsFile, "rb");
        if (!fparamsFile)
        {
            printf("\nCouldn't open Parameters file...   %s\n ",
                   paramsFile);
            printf("Exiting for this configuration...\n");
            continue;
        }

        printf("\nParameter file read starts...\n");

        if (baseParamsOnly)
        {
            if (readparamfile(fparamsFile,baseParamsOnly) < 0)
            {
                printf("\nSyntax Error in %s\n ", paramsFile);
                printf("Exiting for this configuration...\n");
                continue;
            }
        }
        else
        {
            if (readparamfile(fparamsFile,baseParamsOnly) < 0)
            {
                printf("\nSyntax Error in %s\n ", paramsFile);
                printf("Exiting for this configuration...\n");
                continue;
            }

        }

        /* Close Parameters File */
        fclose(fparamsFile);

        if (testCompliance)
        {
            printf("\nRunning in Compliance Mode");
        }
        else
        {
            printf("\nRunning in Output Dump Mode");
        }


        /* Create the Algorithm object (instance) */

        printf("\nCreating Algorithm Instance...");
        if (!baseParamsOnly)
        {
            printf("Ext params\n");
            extn_params.videncParams.encodingPreset = XDM_USER_DEFINED;//XDM_HIGH_SPEED;
            //extn_params.videncParams.encodingPreset = XDM_HIGH_SPEED;
            extn_params.videncParams.maxInterFrameInterval = XDM_DEFAULT;
            extn_params.videncParams.reconChromaFormat = XDM_DEFAULT;
            extn_params.videncParams.inputContentType = XDM_DEFAULT;
            extn_params.videncParams.dataEndianness = XDM_BYTE;
            extn_params.svhMode = 0;
		extn_params.IFrameBitRateBiasFactor = 256;  /* Q7 number for I frame bit rate biasing: For no effect use 256 */ 
		extn_params.PFrameBitRateBiasFactor = 256;  /* Q7 number for P frame bit rate biasing: For no effect use 256 */ 

            if ((handle = (IALG_Handle) ALG_create((IALG_Fxns *) &
                                                   MP4VENC_TI_IMP4VENC,
                                                   (IALG_Handle) NULL,
                                                   (IALG_Params *) &
                                                   extn_params)) == NULL)
            {
                printf("\nFailed to Create Instance... Exiting for this configuration..");
                continue;
            }

        }
        else
        {

            printf("BaseParams\n");
            baseParams.encodingPreset = XDM_HIGH_SPEED;
            baseParams.rateControlPreset = XDM_DEFAULT;
            baseParams.maxInterFrameInterval = XDM_DEFAULT;
            baseParams.reconChromaFormat = XDM_DEFAULT;
            baseParams.inputContentType = XDM_DEFAULT;
            baseParams.dataEndianness = XDM_DEFAULT;
            baseParams.size = sizeof(IVIDENC1_Params);

            if ((handle = (IALG_Handle) ALG_create((IALG_Fxns *) &
                                                   MP4VENC_TI_IMP4VENC,
                                                   (IALG_Handle) NULL,
                                                   (IALG_Params *) &
                                                   baseParams)) == NULL)
            {
                printf
                ("\nFailed to Create Instance... Exiting for this configuration..");
                continue;
            }
        }
#ifdef ENABLE_RMAN // IRES/RMAN Related code
        /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
        iresStatus = RMAN_assignResources((IALG_Handle)handle, resFxns,scratchId);
        if (IRES_OK != iresStatus) {
            printf("Assign Resource Failed \n");
            result = FALSE;
        }

#endif //IRES/RMAN code ends here.
        ividEncfxns = (IVIDENC1_Fxns *) handle->fxns;

        /* Activate the Algorithm                                              */
        handle->fxns->algActivate(handle);

        /*external params*/
        if (baseParamsOnly!=1)
        {
            extn_dynamicParams.videncDynamicParams.inputHeight =
                extn_params.videncParams.maxHeight;
            extn_dynamicParams.videncDynamicParams.inputWidth =
                extn_params.videncParams.maxWidth;
            extn_dynamicParams.videncDynamicParams.targetFrameRate =
                extn_params.videncParams.maxFrameRate;

            extn_dynamicParams.videncDynamicParams.targetBitRate =
                extn_params.videncParams.maxBitRate;

            extn_dynamicParams.videncDynamicParams.generateHeader = 0;
    	    extn_dynamicParams.videncDynamicParams.intraFrameInterval=30;
            extn_dynamicParams.videncDynamicParams.forceFrame = 0;
    	    extn_dynamicParams.videncDynamicParams.interFrameInterval=0;
            extn_dynamicParams.mvDataEnable = 0;
            extn_dynamicParams.intraFrameQP = 0;
            extn_dynamicParams.interFrameQP = 0;
	    extn_dynamicParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);
	    status.videncStatus.size = sizeof(IMP4VENC_Status);

            /* Set Dynamic Params */
            retVal = ividEncfxns->control((IVIDENC1_Handle)handle, XDM_SETPARAMS,
                                          (IVIDENC1_DynamicParams *)&extn_dynamicParams,
                                          (IVIDENC1_Status *)&status);

            if (retVal == XDM_EFAIL)
            {
                printf("\n SETPARAMS function returned an Error...  ");
                break;          /* Error Condition: Application may want to break off          */
            }
        /* Get Buffer information */
        retVal = ividEncfxns->control((IVIDENC1_Handle)handle, XDM_GETBUFINFO,
                                      (IVIDENC1_DynamicParams *)&extn_dynamicParams,
                                      (IVIDENC1_Status *)&status);
        if (retVal == XDM_EFAIL)
        {
            printf("\n GETBUFINFO function returned an Error...  ");
            break;          /* Error Condition: Application may want to break off          */
        }
        }
	else
	{
		/* Base parameter Mode */
            dynamicParams.inputHeight = baseParams.maxHeight;
            dynamicParams.inputWidth = baseParams.maxWidth;
            dynamicParams.targetFrameRate = baseParams.maxFrameRate;
            dynamicParams.targetBitRate = baseParams.maxBitRate;
            dynamicParams.generateHeader = 0;
            dynamicParams.forceFrame = 0;
    	    dynamicParams.intraFrameInterval=30;
    	    dynamicParams.size = sizeof(IVIDENC1_DynamicParams);

            /* Set Dynamic Params */
            retVal = ividEncfxns->control((IVIDENC1_Handle)handle, XDM_SETPARAMS,
                                          (IVIDENC1_DynamicParams *)&dynamicParams,
                                          (IVIDENC1_Status *)&status);

            if (retVal == XDM_EFAIL)
            {
                printf("\n SETPARAMS function returned an Error...  ");
                break;          /* Error Condition: Application may want to break off          */
            }
        /* Get Buffer information */
        retVal = ividEncfxns->control((IVIDENC1_Handle)handle, XDM_GETBUFINFO,
                                      (IVIDENC1_DynamicParams *)&dynamicParams,
                                      (IVIDENC1_Status *)&status);
        if (retVal == XDM_EFAIL)
        {
            printf("\n GETBUFINFO function returned an Error...  ");
            break;          /* Error Condition: Application may want to break off          */
        }

	}


        outputBufDesc.bufs = (XDAS_Int8 **) pOutputBuf;
        outputBufDesc.bufSizes = (XDAS_Int32 *) outBufSize;


        inputBufDesc.numBufs = status.videncStatus.bufInfo.minNumInBufs;
        Offset = 0;
        for (i=0;i<inputBufDesc.numBufs;i++)
        {
            inputBufDesc.bufDesc[i].buf = (XDAS_Int8 *) ( (unsigned int)inputData +
                                          Offset);
            Offset +=  status.videncStatus.bufInfo.minInBufSize[i];
            inputBufDesc.bufDesc[i].bufSize = status.videncStatus.bufInfo.minInBufSize[i];
        }

        outputBufDesc.numBufs = status.videncStatus.bufInfo.minNumOutBufs;
        Offset = 0;

        for (i=0;i<outputBufDesc.numBufs;i++)
        {
            outputBufDesc.bufs[i] = (XDAS_Int8 *) ( (unsigned int)outputData +
                                                    Offset);
            Offset +=  status.videncStatus.bufInfo.minOutBufSize[i];
            outputBufDesc.bufSizes[i] = status.videncStatus.bufInfo.minOutBufSize[i];
        }


        /* Initializing Variables */
        frameCount = 0;         /* Tracks the number of frames decoded */

        /* Resetting bytesGenerated variable                                      */
        bytesGenerated = 0;
        lTemp = 0;
        TotalTime = 0;
#ifdef PROFILE_IMCOP
        TotalTime_IMCOP = 0;
#endif
#ifdef PROFILE_ACTIVATE
        TotalTime_ACTIVATE = 0;
#endif
#ifdef PROFILE_DEACTIVATE
        TotalTime_DEACTIVATE = 0;
#endif


        /* Do-While Loop for Encode Call                                          */
        do
        {
            /* Open input file */
            finFile = fopen(inFile, "rb");
            if (!finFile)
            {
                printf("\n Couldn't open Input file...  %s  ", inFile);
                printf("\n Exiting for this configuration...");
                lTemp =1;
            }
            else
            {

                /* Read from Input File                                                 */
                if ((TestApp_ReadInputData(finFile, frameCount,
                                           &inputBufDesc)) == -1)
                {
                    lTemp = 1;
                    fclose(finFile);
                }
                else
                {
                    fclose(finFile);
                }
            }

            if (!lTemp)
            {
#if 0 //Test for dynamic Parameter
	if((frameCount==45)||(frameCount==59))
	{
            extn_dynamicParams.videncDynamicParams.targetFrameRate = \
                extn_params.videncParams.maxFrameRate; 
            extn_dynamicParams.videncDynamicParams.targetBitRate = \
                extn_params.videncParams.maxBitRate; 
            extn_dynamicParams.videncDynamicParams.forceFrame = -1; 
    	    //extn_dynamicParams.videncDynamicParams.intraFrameInterval=15; 
        //extn_dynamicParams.intraAlgo=3;  
        //extn_dynamicParams.numMBRows=10; 
        //extn_dynamicParams.initQ=12;             
        extn_dynamicParams.rcQMax=20 + 45-frameCount;             
        extn_dynamicParams.rcQMin=15 + 45-frameCount+3;             
        //extn_dynamicParams.intraFrameQP=15;     
        //extn_dynamicParams.interFrameQP=17;    
        //extn_dynamicParams.rateFix=1;        
        //extn_dynamicParams.rateFixRange=4; 
        //extn_dynamicParams.meAlgo=0;              
        //extn_dynamicParams.skipMBAlgo=1;         
        //extn_dynamicParams.unrestrictedMV=1;         
	    
	extn_dynamicParams.videncDynamicParams.size = sizeof(IMP4VENC_DynamicParams);

            /* Set Dynamic Params */
            retVal = ividEncfxns->control((IVIDENC1_Handle)handle, XDM_SETPARAMS,
                                          (IVIDENC1_DynamicParams *)&extn_dynamicParams,
                                          (IVIDENC1_Status *)&status);

            if (retVal == XDM_EFAIL)
            {
                printf("\n SETPARAMS function returned an Error...  ");
                break;          /* Error Condition: Application may want to break off          */
            }
	}

#endif
                /* Basic Algorithm process() call */
                inArgs.subWindowHozOfst = 0;
                inArgs.subWindowVerOfst = 0;
#ifdef TIMER_PROFILE
                timerStart();
                start = timerRead();
#endif

#ifdef PROFILE_ACTIVATE
                tvstartint_activate.tv_sec = 0;
                tvstartint_activate.tv_usec = 0;
                tvendint_activate.tv_sec = 0;
                tvendint_activate.tv_usec = 0;
                gettimeofday(&tvstartint_activate, 0);
#endif
                handle->fxns->algActivate(handle);

#ifdef PROFILE_ACTIVATE
                gettimeofday(&tvendint_activate, 0);

                TimeDiff_ACTIVATE = ((tvendint_activate.tv_sec*NUM_MICROSECS_IN_SEC)+tvendint_activate.tv_usec)-((tvstartint_activate.tv_sec*NUM_MICROSECS_IN_SEC)+tvstartint_activate.tv_usec);
                TotalTime_ACTIVATE += TimeDiff_ACTIVATE;
                //printf("TimeDiff_A = %d\n",TimeDiff_ACTIVATE);
#endif

#ifdef LINUX
                tvstartint.tv_sec = 0;
                tvstartint.tv_usec = 0;
                tvendint.tv_sec = 0;
                tvendint.tv_usec = 0;
                gettimeofday(&tvstartint, 0);

#endif
                retVal = ividEncfxns->process((IVIDENC1_Handle) handle,
                                              (IVIDEO1_BufDescIn *) & inputBufDesc,
                                              (XDM_BufDesc *) & outputBufDesc,
                                              (IVIDENC1_InArgs *) & inArgs,
                                              (IVIDENC1_OutArgs *) & outArgs);

                if (retVal == XDM_EFAIL)
                {
                    printf("\n Process function returned an Error...  ");
                    break;          /* Error Condition:           */
                }

#ifdef USERDATA_TEST
                printf("UserData Offset = %d bytes.\n",outArgs.offsetUserData);
#endif
                printf("FrameNum#%d(%c),  EncBits=%d,  ",
                       frameCount, (outArgs.videncOutArgs.encodedFrameType) ? 'P' : 'I',
                       outArgs.videncOutArgs.bytesGenerated * 8);
                fflush(stdout);

#ifdef LINUX
                gettimeofday(&tvendint, 0);

                TimeDiff = ((tvendint.tv_sec*NUM_MICROSECS_IN_SEC)+tvendint.tv_usec)-((tvstartint.tv_sec*NUM_MICROSECS_IN_SEC)+tvstartint.tv_usec);
                TotalTime += TimeDiff;
                printf("Process Time= %.2fms\n",(float)TimeDiff/1000);
#ifdef PROFILE_IMCOP
                printf("TimeDiff_IMCOP = %d\n",TimeDiff_IMCOP);
#endif
#endif


#ifdef PROFILE_DEACTIVATE
                tvstartint_deactivate.tv_sec = 0;
                tvstartint_deactivate.tv_usec = 0;
                tvendint_deactivate.tv_sec = 0;
                tvendint_deactivate.tv_usec = 0;
                gettimeofday(&tvstartint_deactivate, 0);
#endif
                handle->fxns->algDeactivate(handle);

#ifdef PROFILE_DEACTIVATE
                gettimeofday(&tvendint_deactivate, 0);

                TimeDiff_DEACTIVATE = ((tvendint_deactivate.tv_sec*NUM_MICROSECS_IN_SEC)+tvendint_deactivate.tv_usec)-((tvstartint_deactivate.tv_sec*NUM_MICROSECS_IN_SEC)+tvstartint_deactivate.tv_usec);
                TotalTime_DEACTIVATE += TimeDiff_DEACTIVATE;
                //printf("TimeDiff_D = %d\n\n",TimeDiff_DEACTIVATE);
#endif


#ifdef TIMER_PROFILE
                timerEnd = timerRead();
                timerDiff = timerEnd - start;
                printf("timerDiff = %d\n",(timerDiff*9));
                Total_time += timerDiff;
#endif



                /* Open output file */
                if (frameCount != 0)
                {
                    ftestFile = fopen(testFile, "ab+");
                } else {
                    ftestFile = fopen(testFile, "wb");
                }
                fflush(stdout);

                /* Write the output frames in the display order */
                TestApp_WriteOutputData(ftestFile, bytesGenerated,
                                        &outputBufDesc, &outArgs.videncOutArgs);

                fclose(ftestFile);



                frameCount++;
                bytesGenerated += outArgs.videncOutArgs.bytesGenerated;

                outputBufDesc.bufs[0] =
                    (XDAS_Int8 *) ((XDAS_Int32) outputData);


                /* Check for Break off condition */
                if (frameCount >= APP_DEFND_NUMFRAMES)
                {
                    printf("\n Specified number of Frames Encoded...  ");

                    /* calculate check sum for bitstream verification */
                    {
                        XDAS_Int32 i, streamCheckSum = 0;
                        XDAS_Int32 *pStream32 = (XDAS_Int32 *) outputData;
                        for (i = 0; i < (bytesGenerated + 3) / 4; i++) {
                            streamCheckSum += pStream32[i];
                        }
                        //printf("\n streamCheckSum = %d \n", streamCheckSum);
                    }
                    break;
                }

            }

        } while (!lTemp);            /* end of Do-While loop */


        /* Deactivate the Algorithm     */
        handle->fxns->algDeactivate(handle);
#ifdef ENABLE_RMAN
        /*
        *          * Free resources assigned to this algorihtm
        *                   */
        iresStatus = RMAN_freeResources((IALG_Handle)(handle), resFxns, scratchId);
        if (IRES_OK != iresStatus) {
            printf("Free Resource Failed \n");
            result = FALSE;
        }
#endif

        /* Delete the Algorithm instance object specified by handle */
        ALG_delete(handle);

        if (frameCount == 0)
        {
            frameCount = 1;     /* To avoid division with zero */
        }

        printf("\n --------------  SUMMARY --------------------\n");

        printf("  Total number of Frames          = %d\n",
               (XDAS_UInt32) frameCount);
        printf("  Bit Rate at 30 frames/Sec       = %d Kbps\n",
               (XDAS_UInt32) (((bytesGenerated * 8 * 30) / frameCount) /
                              1000));
        if (!baseParamsOnly)
        {
            printf("  Width and Height                = %d, %d \n",
                   extn_params.subWindowWidth, extn_params.subWindowHeight);
        }
        else
        {
            printf("  Width and Height                = %d, %d \n",
                   baseParams.maxWidth, baseParams.maxHeight);
        }

#ifdef LINUX
        printf("  Average Process Time = %.3f \n", (float)(TotalTime/frameCount)/1000);
#ifdef PROFILE_IMCOP
        printf("avg time_IMCOP = %d \n", (TotalTime_IMCOP/frameCount));
#endif
#ifdef PROFILE_ACTIVATE
        printf("avg time_activate = %d \n", (TotalTime_ACTIVATE/frameCount));
#endif
#ifdef PROFILE_DEACTIVATE
        printf("avg time_deactivate = %d \n", (TotalTime_DEACTIVATE/frameCount));
#endif

#ifdef TIMER_PROFILE
        lTemp = ((Total_time * 9) / frameCount) >> 10;
        printf("  Avg time per frame          = %d ms \n",
               (lTemp / 216));
#endif

        printf (" --------------    END   --------------------\n");
#endif

    } /* Read the Config File until it reaches the end of file */
#ifdef ENABLE_RMAN
    /*
     *      * Unregister the protocol
     *           */
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

    iresStatus = RMAN_unregister(&IRESMAN_VICP2);
    if (IRES_OK != iresStatus) {
        printf("VICP Unregister Protocol Failed \n");
        return (-1);
    }


    RMAN_exit();
#endif

    /* Close the config files */
    fclose(fConfigFile);

#ifdef LINUX
    CMEM_free(inputData,&memParams);
    CMEM_free(outputData,&memParams);
    CMEM_free(ExternalGlobalMemPoolBase,&memParams);
    CMEM_exit();
#endif
    printf("\n End of execution\n");
    return XDM_EOK;

}                               /* main() */

/*
============================================================================
              TestApp_ReadInputData
              Reading Byte Stream from a File
============================================================================
*/

XDAS_Int32 TestApp_ReadInputData(FILE * finFile, XDAS_UInt32 frameCount,
                                 IVIDEO1_BufDescIn * inputBufDesc)
{
    XDAS_Int32 i, bytesRead, offset, sizeFrame;

    sizeFrame = 0;
    for (i = 0; i < inputBufDesc->numBufs; i++) {
        sizeFrame += inputBufDesc->bufDesc[i].bufSize;
    }
    offset = frameCount * sizeFrame;

    for (i = 0; i < inputBufDesc->numBufs; i++) {
        /*Read the input buffers from FILE                                      */
        fseek(finFile, offset, SEEK_SET);
        bytesRead = fread(inputBufDesc->bufDesc[i].buf,
                          1, inputBufDesc->bufDesc[i].bufSize, finFile);

        if (bytesRead != inputBufDesc->bufDesc[i].bufSize) {
            bytesRead = -1;
            break;
        }
        offset += inputBufDesc->bufDesc[i].bufSize;
    }
    return (bytesRead);
}


/*
============================================================================
              TestApp_WriteOutputData
              Writing Output Data in a File
============================================================================
*/


XDAS_Void TestApp_WriteOutputData(FILE * fOutFile, XDAS_UInt32 offset,
                                  XDM_BufDesc * outputBufDesc,
                                  IVIDENC1_OutArgs * outArgs)
{
    if (outArgs->bytesGenerated > 0)
    {
        fwrite(&outputData[0], 1, outArgs->bytesGenerated, fOutFile);
        //fprintf(stdout, "OK\n");
    }
}

