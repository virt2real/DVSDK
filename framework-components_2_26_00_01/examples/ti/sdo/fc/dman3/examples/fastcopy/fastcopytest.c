/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== fastcopytest.c ========
 *  Test application for FCPY algorithm.  Copies a 2D block from one
 *  location to another in memory, one quadrant at a time.
 */
/* External data sections */
#pragma DATA_SECTION(fcpyInput,".image:ext_sect1")
#pragma DATA_SECTION(fcpyOutput,".image:ext_sect2")
#pragma DATA_ALIGN(fcpyInput,128)   /* aligned on cache boundary */
#pragma DATA_ALIGN(fcpyOutput,128)  /* aligned on cache boundary */

#pragma DATA_ALIGN(srcArr,128)  /* aligned on cache boundary */
#pragma DATA_ALIGN(dstArr,128)  /* aligned on cache boundary */
#pragma DATA_ALIGN(tempMem,128)  /* aligned on cache boundary */
#pragma DATA_ALIGN(scratchMem,128)  /* aligned on cache boundary */

#include <xdc/std.h>

#include <stdio.h>

#ifndef _RTS_MODE

#include <sys.h>
#include <log.h>
#include <mem.h>

#endif

#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <ifcpy.h>

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>
#include <ti/sdo/fc/dman3/dman3.h>

/* For configuring GT */
#ifdef GT_CONFIG
#include <ti/sdo/utils/trace/gt.h>
extern Ptr myMalloc(Int size);
extern Void printfCaller(String fmt, ...);
extern GT_Config *GT;
#endif

#ifdef EDMA3_CONFIG
/* For configuring the EDMA3 module now required by DMAN3 */
#include <ti/sdo/fc/edma3/edma3_config.h>
extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int numRecs);
extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int numRecs);
extern EDMA3_InstanceInitConfig myRegionConfig;
#endif

#include <fcpy.h>

#ifdef _RTS_MODE
#include <bios_rts.h>
#endif

#define SLINELEN  32    /* in bytes */
#define SNUMLINES 32    /* in bytes */
#define SSTRIDE   32    /* in bytes */
#define DLINELEN  32    /* in bytes */
#define DNUMLINES 32    /* in bytes */
#define DSTRIDE   32    /* in bytes */

#define INPUTSIZE   1024        /* in words */
#define OUTPUTSIZE  INPUTSIZE   /* in words */
#define BUFSIZE         0x400

/* 2D 64x64 Input and output data buffers */
int fcpyInput[INPUTSIZE];
int fcpyOutput[OUTPUTSIZE];

#ifndef _RTS_MODE

#define LOG_printf0(a, b)       LOG_printf(a, b)
#define LOG_printf1(a, b, c)    LOG_printf(a, b, c)
#define LOG_printf2(a, b, c, d) LOG_printf(a, b, c, d)
extern far Int INTERNALHEAP;
extern far Int EXTMEMHEAP;
extern LOG_Obj LOG_myLog;
extern int L1DHEAP; /* Heap Label for L1DRAM memory allocation */
extern int EXTMEMHEAP; /* Heap Label for external memory allocation */

#else

#define LOG_printf0(a, b)
#define LOG_printf1(a, b, c)
#define LOG_printf2(a, b, c, d)

int INTERNALHEAP = 0;
int EXTMEMHEAP =  0;
int EXTERNALHEAP =  0;
int L1DHEAP = 0;

#endif

#define NUMALGS 1

extern Void exit(Int);
extern Void fastcopy_dman3_config(Void);
extern far IFCPY_Fxns FCPY_IFCPY;      /* FCPY algorithm's v-table */
extern far IDMA3_Fxns FCPY_IDMA3;      /* FCPY algorithm's IDMA2 v-table */

char srcArr[BUFSIZE];
char dstArr[BUFSIZE];
char tempMem[BUFSIZE];
char scratchMem[BUFSIZE];

void sortInput();
void activateChannels();
void deactivateChannels();
void processInput();
void sendOutput();

/*
 * An example of the use of a non-algorithm user of Framework Components to
 * create IDMA3 channels by directly calling DMAN3 API and subsequently
 * using ACPY3 API to configure and submit DMA transfers.
*/
IDMA3_Handle h;

#ifdef _ACPY3_INSTR_

#include <ti/sdo/fc/acpy3/acpy3_instr.h>

ACPY3_INSTR_Hooks hooks;
ACPY3_INSTR_ExtendedHooks extendedHooks;

extern Void ACPY3_INSTR_registerHooks(IDMA3_Handle handle, \
   ACPY3_INSTR_Hooks * hooks, ACPY3_INSTR_ExtendedHooks * extendedHooks);

unsigned int param_arr[ACPY3_INSTR_NUMHOOKS + ACPY3_INSTR_NUMEXTENDEDHOOKS];

/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void acpy3_instr_fn(IDMA3_Handle h, void * param)
{
    if ( *(int *)param < ACPY3_INSTR_NUMHOOKS) {
        LOG_printf1(&LOG_myLog, "ACPY Hook Fn %d\n", *(int *)param);
    }
    else {
        LOG_printf1(&LOG_myLog, "ACPY Extended Hook Fn %d\n", *(int *)param);
    }

}

#endif /* _ACPY3_INSTR_ */

void example_nonAlgorithmDMAN3Usage()
{
    int i;

    /* Initialize source and destination arrays for test */
    for (i = 0; i< 0x100; i++) {
        srcArr[i] = i >> 5;
        dstArr[i] = 0;
        tempMem[i] = 0;
        scratchMem[i] = 0;
    }
        for (i = 0x100; i < BUFSIZE; i++) {
        srcArr[i] = 0;
        dstArr[i] = 0;
        tempMem[i] = 0;
        scratchMem[i] = 0;
        
        }

    activateChannels();

    /* Obtain data from the srcArr sorted into the tempMem array */
    sortInput();

    processInput();

    sendOutput();

    deactivateChannels();

}


void activateChannels()
{
    IDMA3_ChannelRec dmaTab;
    Int status;
#ifdef _ACPY3_INSTR_
    int i;
#endif

    /* Set up the DMAN3 Configurable parameters */
    /* the heap settings of DMAN3 should be set to valid heap descriptors */
    DMAN3_PARAMS.heapInternal = L1DHEAP;
    DMAN3_PARAMS.heapExternal = EXTMEMHEAP;

    /* Set up the DMA Channel descriptor with the transfer parameters  */
    dmaTab.numTransfers = 4;
    dmaTab.numWaits = 4;
    dmaTab.priority = IDMA3_PRIORITY_LOW;

    /*
     * The ACPY3 transfer protocol will be used as the IDMA3 protocol object
     * This object defines the memory requirements and the initialization and
     * de-initialization functions for the protocol's environment
     */
    dmaTab.protocol = &ACPY3_PROTOCOL;
    dmaTab.persistent = FALSE;

    /*
     * On success this call will return a valid DMA channel handle with the
     * attributes defined above
     */
    status = DMAN3_createChannels(0, &dmaTab, 1);

    if (status == DMAN3_SOK ) {
        h = dmaTab.handle;

#ifdef _ACPY3_INSTR_

        for (i = 0; i < ACPY3_INSTR_NUMHOOKS; i++) {
            hooks.InstrHooks[i].fxn = acpy3_instr_fn;
            param_arr[i] = i;
            hooks.InstrHooks[i].args = &param_arr[i];
        }

        for (i = 0; i < ACPY3_INSTR_NUMEXTENDEDHOOKS; i++) {
            extendedHooks.InstrHooks[i].fxn = acpy3_instr_fn;
            param_arr[i + ACPY3_INSTR_NUMHOOKS] = i + ACPY3_INSTR_NUMHOOKS;
            extendedHooks.InstrHooks[i].args =
                &param_arr[i + ACPY3_INSTR_NUMHOOKS];
        }

        //ACPY3_INSTR_registerHooks(h, &hooks, NULL );
        ACPY3_INSTR_registerHooks(h, &hooks, &extendedHooks);

#endif /* _ACPY3_INSTR_ */

        /* Put the channel in active state */
        /* Now other ACPY3 APIs can be called on this handle */
        ACPY3_activate(h);
    }
    else {
        SYS_abort("Channel creeate failed. Status: %d\n", status);
    }
}

void processInput()
{
    ACPY3_Params p;

    /* Wait for trasnfer with waitId 0 to complete */
    ACPY3_waitLinked(h,0);
    /* Can go ahead and process channel One's data here */

    /* Wait for trasnfer with waitId 1 to complete */
    ACPY3_waitLinked(h,1);

    /* Process channel 2's data here etc.. */

    /* Wait for trasnfer with waitId 2 to complete */
    ACPY3_waitLinked(h,2);

    /* Wait for the entire trasnfer to complete */
    ACPY3_wait(h);

    /* Can process the entire data now */
    /* We simply DMA it from one array to another */

    /* Setting up the parameters for the  transfer (data grp 1) */
    p.transferType = ACPY3_1D1D;
    p.dstAddr = (void *)scratchMem;
    p.srcAddr = (void *)tempMem ;
    p.elementSize = 16 * 16;
    p.numElements = 1;
    p.numFrames = 1;

    /* waitId of 0 implies wait after the first transfer */
    p.waitId = 0;

    /*
     * Configure transfer number 0 on the active DMA handle with the
     * parameters set up above
     */
    ACPY3_configure(h, &p, 0);

    /* Submit the transfer configured on the logical channel handle */
    ACPY3_start(h);

    /* wait for it to finish */
    ACPY3_wait(h);

}

void sendOutput()
{
    ACPY3_Params p;

    /* Wait for the previous transfer to finish */
    ACPY3_wait(h);

    /* Revert the data back to the form it was received */

    /* Setting up the parameters for the first transfer (data grp 1) */
    p.transferType = ACPY3_2D1D;
    p.dstAddr = (void *)dstArr;
    p.srcAddr = (void *)scratchMem ;
    p.elementSize = 16;
    p.numElements = 4;
    p.numFrames = 1;
    /* No need to set p.srcElementIndex for a 1D2D transfer */
    p.srcElementIndex = 16 * 4;
    p.srcFrameIndex = 1;
    p.dstFrameIndex = 1;

    /* waitId of 0 implies wait after the first transfer */
    p.waitId = 0;

    /*
     * Configure transfer number 0 on the active DMA handle with the
     * parameters set up above
     */
    ACPY3_configure(h, &p, 0);

    /* Setting up the parameters for the second transfer (data grp 2) */
    p.dstAddr = (void *) &dstArr[16 * 4];
    p.srcAddr = (void *) &scratchMem[16];
    p.waitId = 1;

    /* Configure transfer number 1 */
    ACPY3_configure(h, &p, 1);

    /* Setting up the parameters for the third transfer (data grp 3 )*/
    p.dstAddr = (void *) &dstArr[16 * 4 * 2];
    p.srcAddr = (void *) &scratchMem[16 * 2];
    p.waitId = 2;

    /* Configure transfer number 2 */
    ACPY3_configure(h, &p, 2);


    /* Setting up the parameters for the third transfer (data grp 4) */
    p.dstAddr = (void *) &dstArr[16 * 4 * 3];
    p.srcAddr = (void *) &scratchMem[16 * 3];
    p.waitId = -1;

    /* Configure transfer number 2 */
    ACPY3_configure(h, &p, 3);

    /* Submit the transfer configured on the logical channel handle */
    ACPY3_start(h);
}

/*
 * Deactivate the logical DMA channel
 */
void deactivateChannels()
{
    Int status;

    /* Wait for the transfer to complete */
    ACPY3_wait(h);

    /* deactivate */
    ACPY3_deactivate(h);

#ifdef _ACPY3_INSTR_
    ACPY3_INSTR_unregisterHooks(h);
#endif /* _ACPY3_INSTR_ */

    /* Free the channel */
    if ((status = DMAN3_freeChannels(&h, 1)) != DMAN3_SOK ) {
        SYS_abort("DMAN3_freeChannels failed. Status: %d\n", status);
    }
}


/*
 * Assume data in the srcArray is multichannel input data and Sort it.
 * Uses temporary buffer tempArr.
 * srcArray contents of format: 1234123412341234 are sorted
 * tempArray 111122223333444 where 1,2,3,4 represents 16 byte channel data
 */
void sortInput()
{
    ACPY3_Params p;

    /* Setting up the parameters for the first transfer (data grp 1) */
    p.transferType = ACPY3_1D2D;
    p.dstAddr = (void *)tempMem;
    p.srcAddr = (void *)srcArr ;
    p.elementSize = 16;
    p.numElements = 4;
    p.numFrames = 1;
    /* No need to set p.srcElementIndex for a 1D2D transfer */
    p.dstElementIndex = 16 * 4;
    p.srcFrameIndex = 1;
    p.dstFrameIndex = 1;

    /* waitId of 0 implies wait after the first transfer */
    p.waitId = 0;

    /*
     * Configure transfer number 0 on the active DMA handle with the
     * parameters set up above
     */
    ACPY3_configure(h, &p, 0);

    /* Setting up the parameters for the second transfer (data grp 2) */
    p.transferType = ACPY3_1D2D;
    p.dstAddr = (void *) &tempMem[16];
    p.srcAddr = (void *) &srcArr[16 * 4];
    p.waitId = 1;

    /* Configure transfer number 1 */
    ACPY3_configure(h, &p, 1);

    /* Setting up the parameters for the third transfer (data grp 3 )*/
    p.transferType = ACPY3_1D2D;
    p.dstAddr = (void *) &tempMem[16 * 2];
    p.srcAddr = (void *) &srcArr[16 * 4 * 2];
    p.waitId = 2;

    /* Configure transfer number 2 */
    ACPY3_configure(h, &p, 2);


    /* Setting up the parameters for the third transfer (data grp 4) */
    p.transferType = ACPY3_1D2D;
    p.dstAddr = (void *) &tempMem[16 * 3];
    p.srcAddr = (void *) &srcArr[16 * 4 * 3];
    p.waitId = -1;

    /* Configure transfer number 2 */
    ACPY3_configure(h, &p, 3);

    /* Submit the transfer configured on the logical channel handle */
    ACPY3_start(h);
}



Void main(Void)
{
    Int i;
    FCPY_Params fcpyParams;
    FCPY_Handle fcpyAlg;
    IDMA3_Fxns *dmaFxns[NUMALGS];
    IALG_Handle alg[NUMALGS];
    Bool errorFlag = FALSE;
    Int status;

    IFCPY_Fxns * fxns = (IFCPY_Fxns *)&FCPY_IFCPY;

#ifdef GT_CONFIG
/* This configures GT to print out trace on stdout */
        GT->PRINTFXN = printfCaller;/* To print out GT trace, need to set these 
                                                                   three functions */
        GT->ERRORFXN = printfCaller;
        GT->MALLOCFXN = myMalloc;    
    GT_set("*" "=67");                  /* Use this to set desired level of trace,
                                                                   for e.g., to see only warnings and errors:-
                                                                                           GT_set("*" "=67");
                                                                                           To set full trace:-
                                                                                           GT_set("*" "=01234567"); */
#endif

#ifdef NON_RTSC_CONFIGURATION
/* This configures the DMAN3 module */
    fastcopy_dman3_config();           

#ifdef EDMA3_CONFIG
/* This configures the EDMA3 meta config module ti/sdo/fc/edma3 */
        EDMA3_PARAMS.regionId = 1;       /* Indicate region number, that is being
                                                                    configured, "1" is usually the DSP. */
        EDMA3_PARAMS.globalInit = 1; /* Bool value, indicates if registers/params 
                                    etc should be initialized when allocated */
                                                             /* Functions required to free/allocate memory
                                                                        for internal objects required by the EDMA3
                                                                        module */
        EDMA3_PARAMS.allocFxn = _ALG_allocMemory;
        EDMA3_PARAMS.freeFxn = _ALG_freeMemory;
        EDMA3_PARAMS.globalConfig = NULL;       
                                /* Can be used to overried default SOC specific
                                                           parameters of the EDMA3 device (number of
                                                                   params, number of tccs etc). The defualt
                                                                   values are determined from the SOC specific 
                                                                   library you use from ti/sdo/edma3/rm/lib  */
        EDMA3_PARAMS.regionConfig = NULL;          
                                /* This can be used to override default PSP 
                                                                   resource assignments for this region. This
                                                                   indicates the number of params, tcc, edma,
                                   qdma channels that are available to this 
                                   region etc 
                                   For e.g., you could set the following:- 
                                                                   EDMA3_PARAMS.regionConfig = &myRegionConfig;
                                                                   myConfig is defined below */
        EDMA3_PARAMS.numGroups = 6; /* Number of scratch groups being used */
        EDMA3_PARAMS.contigParams = TRUE;     /* Need for contiguous Params ? */
        DMAN3_PARAMS.numQdmaChannels = 1;     
                                /* Number of QDMA channels that should be 
                                   reserved for DMAN3. These will be used round                                    robin between multiple handles. 
                                   We are using '1' in this 
                                                                   example, as PSP drivers use up all others.
                                                                   To use anything other than 1, 
                                   the regionConfig needs to be changed as well
                                   (default won't work ) */

        /* Explicitly set the scratch groups resource assignments for each resource        required */
        EDMA3_paRamScratchSizes[0] = 4;
        EDMA3_paRamScratchSizes[1] = 3;
        EDMA3_paRamScratchSizes[2] = 2;
        EDMA3_paRamScratchSizes[3] = 0;
        EDMA3_paRamScratchSizes[4] = 0;
        EDMA3_paRamScratchSizes[5] = 5;

        EDMA3_tccScratchSizes[0] = 4;
        EDMA3_tccScratchSizes[1] = 3;
        EDMA3_tccScratchSizes[2] = 2;
        EDMA3_tccScratchSizes[3] = 0;
        EDMA3_tccScratchSizes[4] = 0;
        EDMA3_tccScratchSizes[5] = 5;

        /* Note, no edma channels required for DMAN3 */
        EDMA3_edmaChanScratchSizes[0] = 0;
        EDMA3_edmaChanScratchSizes[1] = 0;
        EDMA3_edmaChanScratchSizes[2] = 0;
        EDMA3_edmaChanScratchSizes[3] = 0;
        EDMA3_edmaChanScratchSizes[4] = 0;
        EDMA3_edmaChanScratchSizes[5] = 0;

        /* Note, no "scratch" qdma channels required for DMAN3, persistent
           QDMA channels will be allocated based on value set for 
           DMAN3_PARAMS.numQdmaChannels */
        EDMA3_qdmaChanScratchSizes[0] = 0;
        EDMA3_qdmaChanScratchSizes[1] = 0;
        EDMA3_qdmaChanScratchSizes[2] = 0;
        EDMA3_qdmaChanScratchSizes[3] = 0;
        EDMA3_qdmaChanScratchSizes[4] = 0;
        EDMA3_qdmaChanScratchSizes[5] = 0;
#endif
#endif
    /*
     * Initialize DMA manager and ACPY3 library for XDAIS algorithms
     * and grant DMA resources
     */
    DMAN3_init();
    ACPY3_init();

    example_nonAlgorithmDMAN3Usage();


    FCPY_init();        /* Initialize the framework  */

    /* Set up FCPY Module  param structure */
    fcpyParams = FCPY_PARAMS;
    fcpyParams.srcLineLen = SLINELEN;
    fcpyParams.srcNumLines = SNUMLINES;
    fcpyParams.srcStride = SSTRIDE;
    fcpyParams.dstLineLen = DLINELEN;
    fcpyParams.dstNumLines = DNUMLINES;
    fcpyParams.dstStride = DSTRIDE;

    /* Use the ALG interface to create a new algorithm instance */
    if ((fcpyAlg = FCPY_create(fxns, &fcpyParams)) == NULL) {
        SYS_abort("Could not create algorithm instance");
    }

    alg[0] = (IALG_Handle)fcpyAlg;
    dmaFxns[0] = &FCPY_IDMA3;

    status = DMAN3_grantDmaChannels(0, alg, dmaFxns, NUMALGS);
    if (status != DMAN3_SOK) {
        SYS_abort("Problem adding algorithm's dma resources");
    }

    /* Initialize data arrays */
    for (i = 0; i < INPUTSIZE; i++)
    {
        fcpyInput[i] = i;
        fcpyOutput[i] = 0xDEADBEEF;
    }

    /*
     * Copy input to the output one quadrant at a time
     */

    /* Quadrant 2 */
    FCPY_apply(fcpyAlg, fcpyInput, fcpyOutput);

    /* Quadrant 1 */
    FCPY_apply(fcpyAlg, fcpyInput + (SSTRIDE/4), fcpyOutput + (DSTRIDE/4));

    /* Quadrant 3 */
    FCPY_apply(fcpyAlg, fcpyInput + (INPUTSIZE/2), fcpyOutput + (OUTPUTSIZE/2));

    /* Quadrant 4 */
    FCPY_apply(fcpyAlg, fcpyInput + (INPUTSIZE/2) + (SSTRIDE/4),
                   fcpyOutput + (OUTPUTSIZE/2) + (DSTRIDE/4));

    /* Verify output */
    for (i = 0; i < OUTPUTSIZE; i++)
    {
        if (fcpyOutput[i] != i) {
            LOG_printf2(&LOG_myLog, " %d th elem in output should not be %d.\n"
                        , i, fcpyOutput[i]);
            errorFlag = TRUE;
        }
        if (dstArr[i] != srcArr[i]) {
            LOG_printf2(&LOG_myLog, " %d th elem in output should not be %d.\n"
                        , i, dstArr[i]);
            errorFlag = TRUE;
        }
    }

    if (errorFlag == FALSE) {
        LOG_printf0(&LOG_myLog, "Pass \n");
        printf("FC Example Passed\n");
    }
    else {
        LOG_printf0(&LOG_myLog, "Fail \n");
        printf("FC Example Failed\n");
    }

    /*
     * Reclaim DMA resources from algorithm and deinitialize the DMA
     * manager and ACPY3 library
     */
    if (DMAN3_releaseDmaChannels(alg, dmaFxns, NUMALGS) != DMAN3_SOK) {
        SYS_abort("Problem removing algorithm's dma resources");
    }

    /* delete the algorithm instance  */
    ALG_delete((IALG_Handle)fcpyAlg);

    /* module finalization */
    DMAN3_exit();
    ACPY3_exit();
    FCPY_exit();    /* Deinitialize the framework */

    exit (0);
}

#ifdef EDMA3_CONFIG

#define DMA_CHANNEL_TO_EVENT_MAPPING_0          (0x0)
#define DMA_CHANNEL_TO_EVENT_MAPPING_1          (0x0)

/* This is an example region configuration structure that may be assigned to:-
    EDMA3_PARAMS.regionConfig.  */

EDMA3_InstanceInitConfig myRegionConfig = {
    /* Resources owned by Region 1 */

    /* ownPaRAMSets */
        /* This is a bit mask representing the number of paRam sets that are
           available to this region. All are available in this case.
           Use bit zero for param#0 if it is not available to a particular region */
    {0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
     0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
     0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu,
     0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu, 0xFFFFFFFFu},

    /* ownDmaChannels */
        /* This is a bit mask representing the number of EDMA channels that are 
           available to this region. All are available in this case.
           Use bit zero for edma#0 if it is not available to a particular region.
           A channel may be in use by a driver, in which case you would not like
           it being used by the algorithm/codec, change the mask in that case */
    {0xFFFFFFFFu, 0xFFFFFFFFu},

    /* ownQdmaChannels */
        /* This is a bit mask representing the number of QDMA channels that are 
           available to this region. All are available in this case.
           Use bit zero for qdma#0 if it is not available to a particular region */
    {0x000000FFu},

    /* ownTccs */
        /* This is a bit mask representing the number of TCCs that are 
           available to this region. All are available in this case.
           Use bit zero for tcc#0 if it is not available to a particular region */
    {0xFFFFFFFFu, 0xFFFFFFFFu},

   /* Resources reserved by Region 1 */
   /* This is in case you would like certain resources to be reserved for 
      special use, this will not be granted to requesting algorithms, unless 
      requested explicitly by number. DMAN3 has no way of requesting resources
      explicitly, so any resource that is reserved, is unavailable to DMAN3 */

    /* resvdPaRAMSets */
    {0x0u, 0x0u, 0x0u, 0x0u,
     0x0u, 0x0u, 0x0u, 0x0u,
     0x0u, 0x0u, 0x0u, 0x0u,
     0x0u, 0x0u, 0x0u, 0x0u},

    /* resvdDmaChannels */
    {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},

    /* resvdQdmaChannels */
    {0x0u},

    /* resvdTccs */
    {DMA_CHANNEL_TO_EVENT_MAPPING_0, DMA_CHANNEL_TO_EVENT_MAPPING_1},
};
                            
#endif
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

