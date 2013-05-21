/******************************************************************************/
/*!
********************************************************************************
  @file     TestAppDecoder.c
  @brief    This is the top level client file that drives the MPEG4 Decoder
            (Baseline Profile) Video Decoder Call using XDM Interface

********************************************************************************
*/



/******************************************************************************
*                                 INCLUDE FILES
******************************************************************************/

/* ----------------------- SYSTEM header files ------------------------*/

#include "tistdtypes.h"
#include <stdlib.h>
/*---------------------------------------------------------------------------*/
/*  Mpeg4 Decoder Interface header files                                     */        
/*---------------------------------------------------------------------------*/
#include "mp4vdec_ti.h"
#include "imp4vdec.h"



/*---------------------------------------------------------------------------*/
/*  Client header file                                                       */
/*---------------------------------------------------------------------------*/                                                       
#include "TestAppDecoder.h"
#include "dec_params.h"
#include "buffermanager.h"
#include "testapp_arm926intc.h"

/* ----------------------- Platform related header files ------------------------*/


#define ENABLE_RMAN

#ifdef __linux
#include <signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include<sys/time.h>
#include <ti/sdo/linuxutils/cmem/include/cmem.h>


#else
//#include <csl_psc.h>
#endif


/* Header Files for IRES/RMAN */
#ifdef ENABLE_RMAN
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/vicp/iresman_vicp2.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/edma3/edma3_config.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>
#include <ti/xdais/dm/xdm.h>

#include <ti/sdo/fc/ires/addrspace/ires_addrspace.h>
#include <ti/sdo/fc/ires/addrspace/iresman_addrspace.h>

//#include <ti/sdo/utils/trace/gt.h>
#include "mp4vdec_ti_ires.h"
#endif

/*--------------------Macros---------------------------------------------------*/
#define STRING_SIZE 256
#define APP_DEFND_NUMFRAMES 10 //1000
#define USE_CONFIG

/*------------------- To enable profile--------------------------------------- */
//#define PROFILE

/*---------------------------------------------------------------------------*/
/*  Redirecting the input and reference data buffers to appropriate data     */
/*  sections in external memory.                                             */
/*---------------------------------------------------------------------------*/


#ifdef __linux
XDAS_Int8 *inputData;
XDAS_Int8 *outputData;
#else
XDAS_Int8 inputData[INPUT_BUFFER_SIZE];
XDAS_Int8 *outputData;
#endif

extern unsigned char *ExternalGlobalMemPool;




/*---------------------------------------------------------------------------*/
/*  Global timer stamps and structures used for profiling.             */
/*---------------------------------------------------------------------------*/

#ifdef PROFILE
#define NUM_MICROSECS_IN_SEC     (1000000)
void timerStart();
unsigned long  timerRead();
unsigned long start, timerEnd;


XDAS_Int32 TotalTime_IMCOP = 0;
XDAS_Int32 TimeDiff_IMCOP = 0;

void profile_start();
unsigned int profile_end();

#endif

#ifdef __linux
struct timeval tvstart, tvend, tvstartint, tvendint;
#endif




/* ------------------------- Global Param structures -------------------------------*/
/*Parameter structures*/
IMP4VDEC_Params mp4vdecparams;
IVIDDEC2_Params mp4vdecparams_base;

/**---------------------- Function for IDMA3_create ------------------------------------------------**/
extern IALG_Handle IDMA3_create(IDMA3_Fxns *fxns, IALG_Handle p);




/**------------- Token Map array for inputs from testparams.cfg file.   ------------------------**/
sTokenMapping sTokenMap[] = {
{"maxHeight", &mp4vdecparams.viddecParams.maxHeight},
{"maxWidth", &mp4vdecparams.viddecParams.maxWidth},
{"dataEndianness", &mp4vdecparams.viddecParams.dataEndianness},
{"forceChromaFormat", &mp4vdecparams.viddecParams.forceChromaFormat},
/*Codec specific extended parameters */
{"rotation", &mp4vdecparams.rotation},
{"displayWidth", &mp4vdecparams.displayWidth},
{"meRange", &mp4vdecparams.meRange},
{"unrestrictedMV", &mp4vdecparams.unrestrictedMV},
{NULL,NULL}
};


/* Mapping of Prameters from config file string to the place holder*/
/*Token Map for Base Parameters*/

sTokenMapping sTokenMap_base[]= {
{"maxHeight", &mp4vdecparams_base.maxHeight},
{"maxWidth", &mp4vdecparams_base.maxWidth},
{"dataEndianness", &mp4vdecparams_base.dataEndianness},
{"forceChromaFormat", &mp4vdecparams_base.forceChromaFormat},
{NULL , NULL}
};




#ifdef PROFILE
XDAS_Int32 TotalTime_IP = 0;	/*for profiling across MP4VDEC_TI_DM350_InitParams */
XDAS_Int32 TimeDiff_IP = 0;
XDAS_Int32 TotalTime_IS = 0;	/*for profiling across MP4VDEC_TI_DM350_InitParams */
XDAS_Int32 TimeDiff_IS = 0;
#endif



/* String variables */
XDAS_Int8 line[STRING_SIZE], inFile[STRING_SIZE],testFile[STRING_SIZE], paramsFile[STRING_SIZE], testCompliance;

/* Error code returned from codec for input params */
int ErrorCode_input;


/* File Read parameters */ 
int FileSize,lastReadflag=0;

/* Profile data declarations */
int Time_Activate,Process_Time,Time_IMCOP,Time_Deactivate; 

int yuv_420 = 0;

/* Main Function acting as a client for Video Decode Call*/
XDAS_Int32 main(int argc, char **argv)
{
    
    /*-------------------------------------------------------------------------*/
    /*   local variables and arrays                                                      */
    /*-------------------------------------------------------------------------*/
    
    unsigned char *ExternalGlobalMemPoolBase ;

    FILE *finFile;
    FILE *ftestFile;
    FILE *fConfigFile,*fparamsFile;
    FILE *CSVFileHandle,*CSVPerfHandle;
    
    
    char baseParams[STRING_SIZE],cmd[STRING_SIZE];
    int Offset,lTemporary=0,lRefreadbytes=0;


    int lStatus,rowno;
    int use_csv=1;
    decoder_params lmpeg4decparams;
    profiledata  lprofiledata;

    XDAS_Int32 lTemp = 0,countConfigSet;
    XDAS_Int32 TotalTime = 0;
    XDAS_Int32 TimeDiff = 0;
    XDAS_Int32 InputbufferRequired,OutputbufferRequired;
    int baseParamsOnly;
    int timerDiff=0,timerEnd=0,start=0;

    /*-------------------------------------------------------------------------*/
    /*   Cache Settings for LINUX                                              */
    /*-------------------------------------------------------------------------*/

#ifdef __linux
    CMEM_AllocParams memParams;
    memParams.type=CMEM_POOL;
    memParams.flags=CMEM_NONCACHED;
    memParams.alignment=256;
#endif

    /* Input/Output  buffers  and their sizes*/

    XDAS_Int8 *pOutputBuf[XDM_MAX_IO_BUFFERS];

    XDAS_Int32 outBufSize[XDM_MAX_IO_BUFFERS];



    /*-------------------------------------------------------------------------*/
    /*  Declaring Algorithm specific handle                                    */
    /*-------------------------------------------------------------------------*/                                            
    IALG_Handle handle;


	    /*-------------------------------------------------------------------------*/
    /*  Base Class Structures for status, input and output arguments.          */
    /*-------------------------------------------------------------------------*/
    IVIDDEC2_Status     status;
    IVIDDEC2_Fxns *ividDecfxns;
    IVIDDEC2_OutArgs outArgs;
    IVIDDEC2_InArgs inArgs;
    IVIDDEC2_DynamicParams dynamicParams;

    /*-------------------------------------------------------------------------*/
    /*  Input/Output Buffer Descriptors                                        */
    /*-------------------------------------------------------------------------*/
    XDM1_BufDesc inputBufDesc;
    XDM_BufDesc outputBufDesc;

	/* Handle to a buffer element allocated by the buffer manager module */
    BUFFMGR_buffEleHandle buffEle;


    /*-------------------------------------------------------------------------*/
    /* Input Buffer Management specific variables*/
	/*-------------------------------------------------------------------------*/

    XDAS_Int32 num,validBytes=0;
    XDAS_UInt32 bytesConsumed,bytesConsumed_buffer;

    /* Other variables */
    XDAS_Int32 retVal, frameCount,ret_val;
    int val,queue_word,queue_num,i,k,size;

    XDAS_Int32 TotalTime_ACTIVATE = 0;
    XDAS_Int32 TimeDiff_ACTIVATE = 0;

    XDAS_Int32 TotalTime_DEACTIVATE = 0;
    XDAS_Int32 TimeDiff_DEACTIVATE = 0;
 
/* Config File support and CSV support */  

#ifndef USE_CONFIG

#ifdef __linux
   	XDAS_Int8 *fname = "Dec_Params.csv";
#else // LINUX
    XDAS_Int8 *fname = "C:\\Dec_Params.csv";
#endif

#else  // USE_CONFIG

#ifdef __linux
   	XDAS_Int8 *fname = "TestVecs/Config/Testvecs.cfg";
#else
    XDAS_Int8 *fname = "..\\..\\Test\\TestVecs\\Config\\Testvecs_ccs.cfg";
#endif  // LINUX

#endif //USE_CONFIG 


#ifdef ENABLE_RMAN // IRES/RMAN Related declarations
    IRES_Status iresStatus;
    Int Size =0;
    Int scratchId =0;
    Bool result = TRUE;
    IRES_Fxns *resFxns = &MP4VDEC_TI_IRES;
    IRESMAN_Edma3ChanParams configParams;
    IRESMAN_VicpParams iresmanConfigParams;
	IRESMAN_AddrSpaceParams addrspaceConfigParams;
    //MP4VENC_TI_Obj *handle = NULL;
    //MP4VENC_TI_Handle handle = NULL;
    iresStatus = RMAN_init();
    if (IRES_OK != iresStatus) {
        printf("RMAN initialization Failed \n");
        return -1;
    }
    printf("RMAN initialization done \n");

#endif 
//IRES/RMAN related code ends here



    /* Interrupt enable related function calls please refer to User
     * guide for a detailed description of these functions and the 
     * DM510_IPC_INTC_ENABLE macro usage */
#ifndef __linux	//def DM510_IPC_INTC_ENABLE
        /* Call the functions to enable ARM926 FIQ and do some basic
         * setup to AINTC to accept KLD INTC (arm968) interupt in 
         * FIQ pin of Arm926  
         */
        ARM926_enable_FIQ();  /* SWI call to enable interrupts */
        ARM926_INTC_init();  /* Init AINTC */
#endif







#ifdef __linux
    
    /*--------------------------------------------------------------------------------*/
    /*--Token support to test extended and base class with same executable in Linux---*/
    /*-------- Token = -ext then its extended class-----------------------------------*/
    /*-------- When there is no token then its base class ----------------------------*/
    /*--------------------------------------------------------------------------------*/

	
	 if(argc==2)
	 {	 
             
        strncpy(baseParams,argv[1],256);
        if (!strcmp(baseParams,"-ext"))
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
    



    /*---------------------------------------------------------------------------*/
    /*  Allocating contigous memory for input & output data buffers, ring buffer
    	and external memory in LINUX                            */
    /*---------------------------------------------------------------------------*/

    CMEM_init();
    //DM350MM_init();
    /*memory allocation for buffers*/
    ExternalGlobalMemPoolBase = CMEM_alloc(EXTERNAL_DATA_MEM_SIZE,&memParams);
    ExternalGlobalMemPool = ExternalGlobalMemPoolBase ;

#else

    baseParamsOnly=0;
#endif

    /*---------------------------------------------------------------------------*/
    /* Initialization of parameters needed fStatusor Algorithm Instance create */
    /*---------------------------------------------------------------------------*/

    countConfigSet=1;
    rowno = 2;//To neglect the First Row of CSV 


#ifndef USE_CONFIG
    while (1)
    {

#ifdef __linux
        ExternalGlobalMemPool = ExternalGlobalMemPoolBase;
#endif



        if (!(CSVFileHandle = fopen(fname, "r")))
    	{
			fprintf(stderr, "Could not open \"params.csv\" for reading\n");
			exit(0);
	    }  
        /*Call CSV Parser Function*/
        lStatus = ParseReadCSV(CSVFileHandle,&lmpeg4decparams,rowno);
		if(lStatus == 1)
		{
			break;
			
		}
		else if(lStatus == -1)
		{
		    ++rowno;
			fclose(CSVFileHandle);
		    continue;
		}

		
		++rowno;//Increment the variable so that next time it will read the next row
   
        /*Populate "mp4vdecparams" structure*/
#else

      /* Open Test Config File */
   fConfigFile = fopen(fname, "r");
   if (!fConfigFile)
    {
	      printf("Couldn't open parameter file %s\n", fname);
              return XDM_EFAIL;
    }

     countConfigSet=1;

 /* Read the Config File until it reaches the end of file  */
     while (!feof(fConfigFile))
     {
     
#ifdef __linux
        ExternalGlobalMemPool = ExternalGlobalMemPoolBase;
#endif
      /* Read Compliance Checking parameter */
         if (fgets(line, 254, fConfigFile))
          {
             sscanf(line, "%d\n", &testCompliance);
             printf("\nTestcompliance = %d",testCompliance);
	  } 
	 else 
	 {
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
   //fparamsFile = fopen("Testparams.cfg", "rb");
    if (!fparamsFile)
     {
       printf("\nCouldn't open Parameters file...   %s\n ", paramsFile);
       printf("Exiting for this configuration...\n");
       continue;
     }
       printf("\nParameter file read starts...\n");
	  
	  
	   if(baseParamsOnly)
	   {
           readparamfile(fparamsFile,baseParamsOnly);
	   if (readparamfile(fparamsFile,baseParamsOnly) < 0)
	    {
        printf("\nSyntax Error in %s\n ", paramsFile);
        printf("Exiting for this configuration...\n");
	    continue;
        }
       }
       else
       {
	   readparamfile(fparamsFile,baseParamsOnly);
	   if (readparamfile(fparamsFile,baseParamsOnly) < 0)
	   {
       printf("\nSyntax Error in %s\n ", paramsFile);
       printf("Exiting for this configuration...\n");
	   continue;
       }
	   
	   }
   
   
                                                                                    		                                                            /* Close Parameters File */
    fclose(fparamsFile);

#endif    
    /*-----------------------------------------------------------------------*/
    /*  Setting the sizes of Base Class and Extended Class Objects and read params from csv                             */
    /*-----------------------------------------------------------------------*/
    mp4vdecparams.viddecParams.size = sizeof(IMP4VDEC_Params);//IVIDDEC2_Params
    mp4vdecparams_base.size= sizeof(IVIDDEC2_Params);
    outArgs.size = sizeof(IVIDDEC2_OutArgs);
   
#ifndef USE_CONFIG        
	if(baseParamsOnly == 0)
    {
	mp4vdecparams.viddecParams.maxHeight         = lmpeg4decparams.maxHeight;
    mp4vdecparams.viddecParams.maxWidth          = lmpeg4decparams.maxWidth;
    mp4vdecparams.viddecParams.dataEndianness    = lmpeg4decparams.dataEndianness;
    mp4vdecparams.viddecParams.forceChromaFormat = lmpeg4decparams.forceChromaFormat;       
	mp4vdecparams.rotation                    = lmpeg4decparams.rotation;
	mp4vdecparams.displayWidth                   = lmpeg4decparams.displayWidth;
	mp4vdecparams.meRange                        = lmpeg4decparams.meRange;
    mp4vdecparams.unrestrictedMV                            = lmpeg4decparams.unrestrictedMV;
	    
	strcpy(inFile,lmpeg4decparams.input);//Copy the Path and the InputFile Name 
	strcpy(testFile,lmpeg4decparams.output);//Copy the Path and the OutputFile Name
    }
	else
	{
    mp4vdecparams_base.maxHeight         = lmpeg4decparams.maxHeight;
    mp4vdecparams_base.maxWidth          = lmpeg4decparams.maxWidth;
    mp4vdecparams_base.dataEndianness    = lmpeg4decparams.dataEndianness;
    mp4vdecparams_base.forceChromaFormat = lmpeg4decparams.forceChromaFormat;      
    strcpy(inFile,lmpeg4decparams.input);//Copy the Path and the InputFile Name 
	strcpy(testFile,lmpeg4decparams.output);//Copy the Path and the OutputFile Name 
	}

#endif
      
        finFile = fopen(inFile, "rb");
        if (!finFile)
        {
            printf("\nCouldn't open Input file...   %s\n ", inFile);
            printf("Exiting for this configuration...\n");
            exit(0);
	    //break;
        }
        
         ret_val = BUFFMGR_Init(SXVGA_YUV422); /*1280*960*2*/
         
	 if(ret_val == -1)
          {
           printf("Failed to allocate memory\n");
	   exit(1);
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

       
        if (baseParamsOnly==0)
        {
             /**------------- For Extended Class ----------------------------------**/
            if ((handle = (IALG_Handle) ALG_create((IALG_Fxns *) &
                                                   MP4VDEC_TI_IMP4VDEC,
                                                   (IALG_Handle) NULL,
                                                   (IALG_Params *)&mp4vdecparams))
                    == NULL)
            {
                printf
                ("\nFailed to Create Instance... Exiting for this configuration..");
                printf("ErrorCode_input=0x%x\n",ErrorCode_input);
                continue;
		//exit(0);

            }
		  
		 if(mp4vdecparams.viddecParams.forceChromaFormat == XDM_YUV_420SP)
		 {
		  yuv_420 = 1;
         }
         else
         {
          yuv_420 = 0;
         }  
        
        }
        else
        {
            /**------------- For Base Class ----------------------------------**/

            if ((handle = (IALG_Handle) ALG_create((IALG_Fxns *) &
                                                   MP4VDEC_TI_IMP4VDEC,
                                                   (IALG_Handle) NULL,
                                                   (IALG_Params *) & mp4vdecparams_base))
                    == NULL)
            {
                printf
                ("\nFailed to Create Instance... Exiting for this configuration..");
                printf("ErrorCode_input=0x%x\n",ErrorCode_input);
                //continue;
		exit(0);
            }
         if(mp4vdecparams_base.forceChromaFormat == XDM_YUV_420SP)
		 {
		  yuv_420 = 1;
         }
         else
         {
          yuv_420 = 0;
         }

        }

#ifdef ENABLE_IDMA3
        /* Currently channels and paRamSets are hardcoded in the codec.
         * channels used ---> {32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,60,61,62,63};
         * paramentries used----> {32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77};*/


      if (handle!=NULL)
        {
            if (IDMA3_create((IDMA3_Fxns *) &MP4VDEC_TI_IDMA3, handle) == NULL)
            {
                printf("\nFailed to allocate DMA channels Exiting for this configuration.");
            }
            fflush(stdout);
        }
#endif


        /**-----------  Assigning Algorithm handle fxns field to ividDecfxns----------**/ 
        ividDecfxns = (IVIDDEC2_Fxns *) handle->fxns;

        


#ifdef ENABLE_RMAN // IRES/RMAN Related code

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

#if 1
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

        /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
        iresStatus = RMAN_assignResources((IALG_Handle)handle, resFxns,scratchId);
        printf("iresStatus = %d\n",iresStatus);
        if (IRES_OK != iresStatus) {
            printf("Assign Resource Failed \n");
            result = FALSE;
	    return -1;
        }
        printf("Assign Resource Success \n");

#endif //IRES/RMAN code ends here.
        
        
#if 1        
       
       status.size = sizeof(IVIDDEC2_Status); 
       dynamicParams.size = sizeof(IVIDDEC2_DynamicParams); 
        /*-----------------------------------------------------------------------*/
        /*  The GETBUFINFO call gives information for number and size of input   */
        /*  and output buffers. For this call, the actual width and height       */
        /*  of the picture is not known hence, this control call returns the out */
        /*  buffer sizes based on the maxHeight and maxWidth.                    */
        /*-----------------------------------------------------------------------*/
        retVal = ividDecfxns->control((IVIDDEC2_Handle)handle, XDM_GETBUFINFO,
                                      (IVIDDEC2_DynamicParams *)&dynamicParams,
                                      (IVIDDEC2_Status *)&status);
        if (retVal==IALG_EFAIL)
        {
            printf("Control (XDM_GETBUFINFO) returned an error\n");
            exit(0);
        }

        /* set space for buffer descriptors */
        outputBufDesc.bufs = (XDAS_Int8 **) pOutputBuf;
        outputBufDesc.bufSizes = (XDAS_Int32 *) outBufSize;


         /*-----------------------------------------------------------------------*/
            /*  Initialize the input buffer properties as required by algorithm      */
            /*  based on info received by preceding GETBUFINFO call for extended     */
            /*	class. First init the number of input bufs.                          */
            /*-----------------------------------------------------------------------*/
        inputBufDesc.numBufs =  status.bufInfo.minNumInBufs;
		
		InputbufferRequired = 0;
        
        for(i=0; i<status.bufInfo.minNumInBufs ; i++)
		{
		  InputbufferRequired +=  status.bufInfo.minInBufSize[i];
        }
#ifdef __linux      
        inputData = CMEM_alloc(InputbufferRequired,&memParams);
#else
//      inputData = malloc(sizeof(char) * InputbufferRequired); 
#endif         
                
        Offset = 0;

        for (i=0;i<inputBufDesc.numBufs;i++)
        {
            inputBufDesc.descs[i].buf = (XDAS_Int8 *) ( (unsigned int)inputData +
                                        Offset);
            Offset +=  status.bufInfo.minInBufSize[i];
            inputBufDesc.descs[i].bufSize = status.bufInfo.minInBufSize[i];
        }

        outputBufDesc.numBufs =  status.bufInfo.minNumOutBufs;
		
		OutputbufferRequired = 0;
        
        for(i=0; i<status.bufInfo.minNumOutBufs ; i++)
		{
		  OutputbufferRequired +=  status.bufInfo.minOutBufSize[i];
        }

                       
        Offset = 0;


		 /*-----------------------------------------------------------------------*/
            /*  Initialize the output buffer properties as required by algorithm     */
            /*  based on info received by preceding GETBUFINFO call for extended     */
            /*	class. First init the number of output bufs.                          */
            /*-----------------------------------------------------------------------*/
        for (i=0;i<outputBufDesc.numBufs;i++)
        {
                        
            outputBufDesc.bufSizes[i] = status.bufInfo.minOutBufSize[i];
        }


        /* Initializing Variables */
        frameCount = 0;             /* Tracks the number of frames decoded */

        TotalTime = 0;
        TotalTime_ACTIVATE = 0;
        TotalTime_DEACTIVATE = 0;

#ifdef PROFILE
        TotalTime_IMCOP = 0;
#endif


    
    /*---------------------------------------------------------------------*/
        /*  The SETPARAMS call gives information to the algorithm about the    */
        /*  dynamic parameters that have been initialized.                     */
        /*---------------------------------------------------------------------*/
        dynamicParams.decodeHeader=0;
        dynamicParams.mbDataFlag=0;
	
	retVal=ividDecfxns->control((IVIDDEC2_Handle)handle, XDM_SETPARAMS,
                                    (IVIDDEC2_DynamicParams *)&dynamicParams,
                                    (IVIDDEC2_Status *)&status);
        if (retVal==IALG_EFAIL)
        {
            printf("Control (XDM_SETPARAMS) returned an error\n");
            exit(0);
        }
        
        
        /* Resetting bytesConsumed variable */
        bytesConsumed = 0;
        bytesConsumed_buffer=0;
        lastReadflag=0;
        validBytes=0;
        
        
        fseek(finFile, 0, SEEK_END);
        FileSize = ftell(finFile);
        ErrorCode_input=0x0;

		fclose(finFile);


        /* Do-While Loop for Decode Call */
        do
        {


            if (validBytes<500*1024 && lastReadflag==0)
            {
                /* Read the bitstream in the Application Input Buffer                    */
                finFile = fopen(inFile, "rb");
                if (!finFile)
                {
                    printf("\nCouldn't open Input file...   %s\n ", inFile);
                    printf("Exiting for this configuration...\n");
                    break;
                }

                fprintf(stdout, "Input File is %s ...\n", inFile);
                fflush(stdout);

                validBytes = TestApp_ReadByteStream(finFile,bytesConsumed,inputBufDesc.descs[0].bufSize);
                bytesConsumed_buffer=0;
                fclose(finFile);
            }

            /* Return if there is an error in reading the file    */

            if (validBytes < 0)
            {       /* Error condition                                   */

                printf("Valid Bytes incorrect... Exiting for this configuration...\n");
                continue;

            }

            /* Setting of input arguments                                          */
          inArgs.numBytes = validBytes;
          inputBufDesc.descs[0].buf = (XDAS_Int8 *) ((XDAS_Int32) inputData +
                                        bytesConsumed_buffer);

           
	  
           buffEle = BUFFMGR_GetFreeBuffer();

           outputData = (XDAS_Int8 *) buffEle->buf[0];
          
	       inArgs.inputID = buffEle->bufId;
	   
           outputBufDesc.bufs[0] = (XDAS_Int8 *) ( (unsigned int)outputData);
           
if(yuv_420 == 1)
{ 
           outputBufDesc.bufs[1] = (XDAS_Int8 *) ( (unsigned int)outputData + status.bufInfo.minOutBufSize[0] );
}
           
           
            /*---------------- Activate the Algorithm --------------------------------------   */
#ifdef PROFILE
            profile_start();
#endif
            handle->fxns->algActivate(handle);
#ifdef PROFILE
	    TimeDiff_ACTIVATE = profile_end();
            TotalTime_ACTIVATE += TimeDiff_ACTIVATE;
#endif
        /*---------------------------------------------------------------------*/
        /*  start the decode process by calling the process function.           */
        /*---------------------------------------------------------------------*/
            inArgs.size = sizeof(IVIDDEC2_InArgs);
            outArgs.size = sizeof(IVIDDEC2_OutArgs);
#ifdef PROFILE
	    profile_start();
#endif
            retVal = ividDecfxns->process((IVIDDEC2_Handle) handle,
                                          (XDM1_BufDesc *) & inputBufDesc,
                                          (XDM_BufDesc *) & outputBufDesc,
                                          (IVIDDEC2_InArgs *) & inArgs,
                                          (IVIDDEC2_OutArgs *) & outArgs);
#ifdef PROFILE
            TimeDiff = profile_end();
            TotalTime += TimeDiff;
#endif


	    /*---------------- Deactivate the Algorithm --------------------------------------   */
#ifdef PROFILE 
 	    profile_start();
#endif
            handle->fxns->algDeactivate(handle);
#ifdef PROFILE      
      	    TimeDiff_DEACTIVATE = profile_end();
            TotalTime_DEACTIVATE += TimeDiff_DEACTIVATE;
#endif

	    
            printf("Frame Number = %d\n",frameCount);
            printf("TimeDiff_A = %d\n",TimeDiff_ACTIVATE);
            fflush(NULL);
            printf("Process Time = %dus\n",TimeDiff);
            fflush(NULL);
            printf("TimeDiff_D = %d\n\n",TimeDiff_DEACTIVATE);
            fflush(NULL);

			ividDecfxns->control((IVIDDEC2_Handle)handle, XDM_GETSTATUS,
                                     (IVIDDEC2_DynamicParams *)&dynamicParams,
                                     (IVIDDEC2_Status *)&status);

            
            bytesConsumed += outArgs.bytesConsumed;
            bytesConsumed_buffer+=outArgs.bytesConsumed;
            validBytes -= outArgs.bytesConsumed;

           if (retVal == XDM_EFAIL)
           {

			/*------------------------------------------------------------------*/
            /*--  Invoke a GETSTATUS control call to get the extended error     */
            /*  , image height, image width, outputchromaformat and other status*/
            /*   related to the image decoded ----------------------------------*/
            /*------------------------------------------------------------------*/
           printf("Bytes Consumed for the frame = %d\n",outArgs.bytesConsumed);
           ividDecfxns->control((IVIDDEC2_Handle)handle, XDM_GETSTATUS,
                                     (IVIDDEC2_DynamicParams *)&dynamicParams,
                                     (IVIDDEC2_Status *)&status);

           printf("Error Code = %d\n",status.extendedError);
           printf("\n Process function returned an Error...  ");

//	   printf("\n\nWidth and Height = %d x %d \n",
//		   outArgs.displayBufs[0].frameWidth,
//		   (!yuv_420 ? outArgs.displayBufs[0].bufDesc[0].bufSize / (outArgs.displayBufs[0].frameWidth) : outArgs.displayBufs[0].bufDesc[0].bufSize / (outArgs.displayBufs[0].frameWidth*2)));
#ifdef __linux           
           CMEM_free(inputData,&memParams);
#endif                
           
           break;/* Error Condition: Application may want to break off          */
           }



		  BUFFMGR_ReleaseBuffer((XDAS_UInt32 *)outArgs.freeBufID);
		  
		  if(outArgs.outputID[0] < 0)
		   {
		    printf("Invalid output id\n");
		    break;
		   }
          
          
          
          
          
           /* ================================================== */
            /* Open YUV file for OUTPUT to store the decoded data */
            /* ================================================== */
	if(outArgs.outputID[0] != 0)
	{

#ifndef  USE_CONFIG          
           if(!strcmp(lmpeg4decparams.DumpORCompareflag1,"D"))
		   {
#endif           		 /* Open output file */
            	if (frameCount != 0 )
            	{
                	ftestFile = fopen(testFile, "ab+");
            	}
            	else
            	{
                	ftestFile = fopen(testFile, "wb");
                	fprintf(stdout, "Dumping decoded picture %s\n", testFile);
                	fflush(stdout);
                	if (!ftestFile)
                	{
                    	printf("\nCouldn't open Output file...   %s\n ", testFile);
                    	break;
                	}
            	}
            TestApp_WriteOutputData(ftestFile, &outputBufDesc, (IVIDDEC2_OutArgs *)&outArgs);
            	fclose(ftestFile);
			
		   
#ifndef  USE_CONFIG 
	        }	
		else
			{
			    
                strcpy(testFile,lmpeg4decparams.reference);
                ftestFile = fopen(testFile, "rb");
				if (!ftestFile)
        		{
           			 printf("\nCouldn't open Reference File...%s\n ", ftestFile);
            		 break;
        		}
            	
            	lTemporary= TestApp_Compare_Ouput_and_Ref(ftestFile, lRefreadbytes, (IVIDDEC2_OutArgs *)&outArgs);
	        lRefreadbytes += lTemporary;
            	fclose(ftestFile);
			}

#endif
		}
      
            frameCount++;

            /* Check for Break off condition */
            if ((FileSize-bytesConsumed)<6 || frameCount >= APP_DEFND_NUMFRAMES )
            {

                printf("\n --------------  SUMMARY --------------------\n");
                printf("  Total number of Frames          = %d\n",
                       (XDAS_UInt32) frameCount);
                printf("  Bit Rate at 30 frames/Sec       = %d Kbps\n",
                       (XDAS_UInt32) (((bytesConsumed * 8 * 30) / frameCount) / 1000));
                printf("  Width and Height                = %d, %d \n",
                       outArgs.displayBufs[0].frameWidth,
                       (yuv_420 ? outArgs.displayBufs[0].bufDesc[0].bufSize / (outArgs.displayBufs[0].frameWidth) : outArgs.displayBufs[0].bufDesc[0].bufSize / (outArgs.displayBufs[0].frameWidth*2)));
                Time_Activate   = (TotalTime_ACTIVATE/frameCount);
				Time_Deactivate = (TotalTime_DEACTIVATE/frameCount);
                Process_Time    = (TotalTime/frameCount);
#ifdef PROFILE
                Time_IMCOP      = (TotalTime_IMCOP/frameCount);
#endif

#ifndef USE_CONFIG                
				strcpy(lprofiledata.TestCaseId,lmpeg4decparams.TestCaseId);
				lprofiledata.avg_processtime    = Process_Time;
				lprofiledata.avg_time_IMCOP     = Time_IMCOP;
				lprofiledata.avg_activatetime   = Time_Activate;
				lprofiledata.avg_deactivatetime = Time_Deactivate;
				lStatus = ParseWriteCSV(&lprofiledata);
#endif				

#ifdef __linux 
				CMEM_free(inputData,&memParams);
#endif				
				break;
            }
         
         
        
        } while (1);


        /*-----------------------------------------------------------------------*/
        /*--------------  Call XDM_RESET --------------------                    */
        /*-----------------------------------------------------------------------*/

       ividDecfxns->control((IVIDDEC2_Handle)handle, XDM_RESET,
                                     (IVIDDEC2_DynamicParams *)&dynamicParams,
                                     (IVIDDEC2_Status *)&status);

       
        /* Delete the Algorithm instance object specified by handle */
	BUFFMGR_DeInit();
#endif       
#ifdef ENABLE_RMAN
        /*
        *          * Free resources assigned to this algorihtm
        *                   */
       
        printf("RMAN_freeResources call\n");       
	iresStatus = RMAN_freeResources((IALG_Handle)(handle), resFxns, scratchId);
        if (IRES_OK != iresStatus) {
            printf("Free Resource Failed \n");
            result = FALSE;
        }
        printf("Free Resource : Success \n");
#endif
    

    ALG_delete(handle);
        //fclose(CSVFileHandle);



    }/*End of loop for configuration file*/

#ifdef __linux

    /*-------Freeing the memories which are allocated thro' CMEM Driver -----*/
    
    CMEM_free(ExternalGlobalMemPoolBase,&memParams);
    CMEM_exit();
    //DM350MM_exit();
#endif

    if (frameCount == 0)
    {
        frameCount = 1;         /* To avoid division with zero */
    }

   
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
        printf("EDMA3 Unregister Protocol Success \n");

        iresStatus = RMAN_unregister(&IRESMAN_VICP2);
        if (IRES_OK != iresStatus) {
            printf("VICP Unregister Protocol Failed \n");
            return (-1);
        }
        printf("VICP Unregister Protocol : Sucess \n");

        RMAN_exit();

#endif
   
    return XDM_EOK;

}//End of Main()                               

/*
============================================================================
  				 TestApp_ReadByte   Stream
  				 Reading Byte Stream from a File
============================================================================
*/

XDAS_Int32 TestApp_ReadByteStream(FILE * finFile,int bytesProcessed,int appBufferSize)
{
    XDAS_UInt32 BytesRead,remainingBytes,bytesForRead;

    remainingBytes=FileSize-bytesProcessed;

    fseek(finFile, bytesProcessed, SEEK_SET);


    if (remainingBytes >=  appBufferSize)
    {
        lastReadflag=0;
        bytesForRead = appBufferSize;
    }
    else
    {
        lastReadflag=1;
        bytesForRead=remainingBytes;
    }

    /*Read the "BufferSize" number of bytes in the input buffer */
    BytesRead = fread(inputData, 1, bytesForRead, finFile);

    if (BytesRead != bytesForRead)
    {
        printf("\nFailure:Bytes read = %d bytes to be read size = %d\n", BytesRead,
               bytesForRead);
        return (-1);
    }
    printf("\nInput File read successfully...\n");
    return (BytesRead);
}


/*============================================================================
					TestApp_WriteOutputData
					Writing Output Data in a File
==============================================================================*/

XDAS_Void TestApp_WriteOutputData(FILE * fOutFile,
                                  XDM_BufDesc * outputBufDesc,
                                  IVIDDEC2_OutArgs * outArgs)
{

    XDAS_UInt8 *s;
    XDAS_Int32 i;
    int width,height;
    XDAS_UInt8 * buf;
    XDAS_UInt8 * buf1;
	XDAS_UInt8 * org_buf;

	
    
	if(yuv_420)
	{
        width = outArgs->displayBufs[0].framePitch;
        //height =(outArgs->displayBufs[0].bufDesc[0].bufSize) / (outArgs->displayBufs[0].frameWidth);
        height =outArgs->displayBufs[0].frameHeight;

	buf = malloc((width*height)>>1);
	org_buf = (XDAS_UInt8 *) outArgs->displayBufs[0].bufDesc[1].buf;
	// org_buf += (width*height);
    buf1 = buf + (int)((width*height)>>2);
    
	for(i=0;i<width*height*0.25;i++)
	{
	 buf1[i] = org_buf[2*i];
	 buf[i] = org_buf[2*i + 1];
        }

    
  //  for (i = 0; i < outArgs->displayBufs[0].numBufs; i++)
    {
        s = (XDAS_UInt8 *) outArgs->displayBufs[0].bufDesc[0].buf;
        fwrite(s, 1, width*height,fOutFile);
    }
	fwrite(buf, 1,width*height*0.5,fOutFile);
	free(buf);
	}
	else
	{
	for (i = 0; i < outArgs->displayBufs[0].numBufs; i++)
    {

        s = (XDAS_UInt8 *) outArgs->displayBufs[0].bufDesc[i].buf;
        fwrite(s, 1, outArgs->displayBufs[0].bufDesc[i].bufSize,
               fOutFile);
    }

	}
    fflush(fOutFile);
    return;
}

/*============================================================================
					TestApp_Compare_Ouput_and_Ref
					Compare Output Buffer and Reference Buffer
==============================================================================*/

XDAS_Int32 TestApp_Compare_Ouput_and_Ref(FILE * fOutFile,
                                  int lRefReadBytes,
                                  IVIDDEC2_OutArgs * outArgs)
{

    XDAS_UInt8 *s;
    XDAS_Int32 i,diff,j;
    char *refbuf;
    XDAS_UInt32 BytesRead;

    fseek(fOutFile, lRefReadBytes, SEEK_SET);

    for (i = 0; i < outArgs->displayBufs[0].numBufs; i++)
    {

		refbuf = (char *)malloc(outArgs->displayBufs[0].bufDesc[i].bufSize);
    	BytesRead = fread(refbuf, 1, outArgs->displayBufs[0].bufDesc[i].bufSize, fOutFile);
        
	    for (j = 0; j < outArgs->displayBufs[0].bufDesc[i].bufSize; j++)
	    {
		    diff = refbuf[j]- outArgs->displayBufs[0].bufDesc[i].buf[j];

        }

		if(diff == 0)
		{
		   printf("Both Output and Reference are Same\n");
		}
		else
		{
           printf("Both Output and Reference are not Same\n");
		}
        free(refbuf);
	    fflush(fOutFile);
	}
    return(BytesRead);
}

#ifdef PROFILE
/*============================================================================
				profile_start
				take the start time for profiling
==============================================================================*/

void profile_start()
{

#ifdef __linux
    tvstartint.tv_sec = 0;
    tvstartint.tv_usec = 0;
    tvendint.tv_sec = 0;
    tvendint.tv_usec = 0;
    gettimeofday(&tvstartint, 0);
#else
    timerStart();
    start= timerRead();

#endif

}

/*============================================================================
				profile_end
				take the end time of profiling
==============================================================================*/

unsigned int profile_end()
{
    unsigned int TimeDiff = 0;
#ifdef __linux
    gettimeofday(&tvendint, 0);
    TimeDiff = ((tvendint.tv_sec*NUM_MICROSECS_IN_SEC)+tvendint.tv_usec)-((tvstartint.tv_sec*NUM_MICROSECS_IN_SEC)+tvstartint.tv_usec);
#else
    timerEnd= timerRead();
    TimeDiff= ((timerEnd-start) * 9)/216;
#endif

    return TimeDiff;
}
#endif


/******************************************************************************/
/*    Copyright (c) 2006 Texas Instruments, Incorporated                      */
/*    All Rights Reserved                                                     */
/******************************************************************************/


