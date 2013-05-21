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
 *  ======== app.c ========
 */

#include <xdc/std.h>
#include <stdio.h>
#include <stdlib.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>

/* For creation of algorithms */
#include <ti/sdo/fc/dskt2/dskt2.h>

/* To grant resources to IRES algorithm */
#include <ti/sdo/fc/rman/rman.h>

/* DMAN3 for IDMA3 resources */
#include <ti/sdo/fc/dman3/dman3.h>

/* Initializing all frameworks */
#include <ti/sdo/fc/acpy3/acpy3.h>

/* The Algorithms */
#include <ti/sdo/fc/ires/examples/codecs/edmacodec1/edmacodec1_ti.h>
#include <ti/sdo/fc/ires/examples/codecs/idma3codec1/idma3codec1_ti.h>
#include <ti/sdo/fc/ires/examples/codecs/idma3codec1/iidma3codec1.h>

/* Trace */
#include <ti/sdo/utils/trace/gt.h>

/*
 *  ======== ScratchTskAttrs ========
 *  Attributs of the tasks that will be created
 */
typedef struct ScratchTskAttrs {
    Int         priority;       /* Priority of task */
    Int         scratchId;      /* Scratch group in which to create the task */
    Int         yieldFlag;
    Uns         fillValue;
} ScratchTskAttrs;

/* Used to enable trace on specific modules */
#define MOD_NAME "*"

/* Size of the buffer to use for DMA */
#define DMAXFER_BUFSIZE 0x600

/* Number of tasks to create */
#define NUMTASKS 3
//3 /* 12 */

/* Maximum number of tasks */
#define MAXTASKS 3      
#define NUMALGS 2      
//12

/* Attributes for DMAN3 based transfer */
#define SLINELEN  32    /* in bytes */
#define SNUMLINES 32    /* in bytes */
#define SSTRIDE   32    /* in bytes */
#define DLINELEN  32    /* in bytes */
#define DNUMLINES 32    /* in bytes */
#define DSTRIDE   32    /* in bytes */

#define INPUTSIZE   1024        /* in words */
#define OUTPUTSIZE  INPUTSIZE   /* in words */
#define BUFSIZE         0x400


/* Required to GT generate trace from the app */
GT_Mask ti_sdo_fc_rman_examples_dma;

/* Buffers to perform DMA transfer on */
unsigned int SRCBUFF[DMAXFER_BUFSIZE];
unsigned int DSTBUFF[DMAXFER_BUFSIZE];

/*
 * heapId in which to create the tasks
 */
extern Int EXTMEM_HEAP;

/* Semaphores for the tasks */
static SEM_Handle done = NULL;  /* Gets posted by last task to finish */
static SEM_Handle mutex = NULL; /* Protect DSKT2_createAlg and DSKT2_freeAlg */

/* Scratch task parameters */
static ScratchTskAttrs attrsTable[MAXTASKS] = {
    /* priority,    scratchGroup   yieldFlag somAttr */
    12,              1,      1,     0x1,
    13,              1,      0,     0x2,
    13,              1,      0,     0x3,
};

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);
extern Int rmanTask(Arg taskId, Arg priority, Arg scratchId, Arg yieldFlag,
        Arg fillValue);
extern Int dman3Task(Arg taskId, Arg priority, Arg scratchId, Arg fillValue);

Int main()
{
    Int size = 0;
    Int i = 0;
    IRES_Status status;

    GT_create(&ti_sdo_fc_rman_examples_dma,
            "ti.sdo.fc.rman.examples.dma");

    //Uncomment the line below for trace
    //GT_set(MOD_NAME "=47");
    GT_set("ti.sdo.fc.edma3" "=47");


    /* Initialize the framework modules we're going to use */
    DMAN3_init();
    ACPY3_init();

    status = RMAN_init();
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return (-1);
    }

    /* Populate SRCBUF with data */
    for (i = 0; i < DMAXFER_BUFSIZE; i++) {
        SRCBUFF[i] = 0x8C0FFEE8;
        DSTBUFF[i] = 0xDEADBEEF;
    }

    return (0);
}

/*
 *  ======== smain ========
 */
/* ARGSUSED */
Int smain(Int argc, Char * argv[])
{
    TSK_Handle tsk;
    TSK_Attrs attrs = TSK_ATTRS;
    Int i;

    done = SEM_create(0, NULL);
    mutex = SEM_create(1, NULL);

    if ((done == NULL) || (mutex == NULL)) {

        GT_0trace(ti_sdo_fc_rman_examples_dma, GT_7CLASS,
        "_smain> Semaphore creation failed\n");

        SYS_abort("Sem create failed \n");
    }

    attrs.stackseg = EXTMEM_HEAP;

    /* Create multiple tasks */
    for (i = 0; i < NUMTASKS; i++) {

        attrs.priority = attrsTable[i].priority;
                attrs.stacksize = 0x4000;
        tsk = TSK_create((Fxn)rmanTask, &attrs,
                (Arg)(i), (Arg)(attrsTable[i].priority),
                (Arg)(attrsTable[i].scratchId), (Arg)(attrsTable[i].yieldFlag),
                (Arg)(attrsTable[i].fillValue));
        if (tsk == NULL) {

            GT_1trace(ti_sdo_fc_rman_examples_dma, GT_7CLASS,
            "_smain> TSK_create of task %d failed\n", i+1);

            SYS_abort("TSK_create() of task %d failed\n",i+1);
        }

        tsk = TSK_create((Fxn)dman3Task, &attrs,
                (Arg)(i), (Arg)(attrsTable[i].priority),
                (Arg)(attrsTable[i].scratchId),(Arg)(attrsTable[i].fillValue));
        if (tsk == NULL) {

            GT_1trace(ti_sdo_fc_rman_examples_dma, GT_7CLASS,
            "_smain> TSK_create of task %d failed\n", i+1);

            SYS_abort("TSK_create() of task %d failed\n",i+1);
        }
    }

    /* Wait for completion of each task */
    for (i=0; i < NUMTASKS * 2; i++) {
        SEM_pend(done, SYS_FOREVER);
    }

    SEM_delete(mutex);
    SEM_delete(done);

    GT_0trace(ti_sdo_fc_rman_examples_dma, GT_4CLASS,
            "_smain> TEST COMPLETED\n");

    return (0);
}


/* ARGSUSED */
Int rmanTask(Arg taskId, Arg priority, Arg scratchId, Arg yieldFlag,
        Arg fillValue)
{

    IALG_Fxns * algFxns = (IALG_Fxns *)&EDMACODEC1_TI_CODECIRES;
    IRES_Fxns * resFxns = &EDMACODEC1_TI_IRES;
    IEDMACODEC1_Handle alg = NULL;

    /*
     * Create an instance of the algorithm using "algFxns"
     */

    /* Use mutex to serialize DSKT2's create/delete */
    SEM_pend(mutex, SYS_FOREVER);
    alg = (IEDMACODEC1_Handle)DSKT2_createAlg(scratchId,
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)NULL);
    if (alg == NULL) {
        printf("Alg creation failed for alg\n");
        return (-1);
    }
    SEM_post(mutex);

    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)alg,
                resFxns, scratchId)) {
        printf("Assign Resource Failed \n");
        return (-1);
    }

    TSK_setpri(TSK_self(), priority-1);

    /* Activate the Algorithm */
    DSKT2_activateAlg(scratchId, (IALG_Handle)alg);

    /* Activate All Resources */
    RMAN_activateAllResources((IALG_Handle)alg, resFxns, scratchId);

    /* Use IALG interfaces to do something */
    /* Do a DMA of 1/3rd the buffer from different offsets */
    alg->fxns->doCopy(alg, SRCBUFF + 0x200 * (taskId),
            DSTBUFF + 0x200 * (taskId), DMAXFER_BUFSIZE/3 * 4 );

    /* Deactivate All Resources */
    RMAN_deactivateAllResources((IALG_Handle)alg, resFxns, scratchId);

    /* Deactivate algorithm */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)alg);

    /* Free resources assigned to this algorihtm */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(alg),
                resFxns, scratchId)) {
        printf("Free Resource Failed \n");
        return (-1);
    }

    /* Free instance of the algorithm created */
    SEM_pend(mutex, SYS_FOREVER);
    DSKT2_freeAlg(scratchId, (IALG_Handle)alg);

    SEM_post(mutex);

    SEM_post(done);

    GT_1trace(ti_sdo_fc_rman_examples_dma, GT_4CLASS,
            "rmanTask> Completed task %d\n", taskId);

    return (0);
}


/* ARGSUSED */
Int dman3Task(Arg taskId, Arg priority, Arg scratchId, Arg fillValue)
{

    IALG_Fxns * algFxns = (IALG_Fxns *)&IDMA3CODEC1_TI_CODECIDMA3;
    IDMA3_Fxns * idma3Fxns = &IDMA3CODEC1_TI_IDMA3;
    IALG_Handle alg = NULL;
    IIDMA3CODEC1_Handle codec = NULL;
    IIDMA3CODEC1_Params params = IDMA3CODEC1_TI_PARAMS;
    IDMA3_Fxns * dmaFxnsArray[NUMALGS];
    IALG_Handle algArray[NUMALGS];
    Int status;

    params.srcLineLen = SLINELEN;
    params.srcNumLines = SNUMLINES;
    params.srcStride = SSTRIDE;
    params.dstLineLen = DLINELEN;
    params.dstNumLines = DNUMLINES;
    params.dstStride = DSTRIDE;

    /*
     * Create an instance of the algorithm using "algFxns"
     */

    /* Use mutex to serialize DSKT2's create/delete */
    SEM_pend(mutex, SYS_FOREVER);
    codec = (IIDMA3CODEC1_Handle)DSKT2_createAlg(scratchId, 
            (IALG_Fxns *)algFxns, (IALG_Handle)NULL, (IALG_Params *)&params);

    alg = (IALG_Handle)codec;
    if (alg == NULL) {
        printf("Alg creation failed for alg\n");
        return (-1);
    }
    SEM_post(mutex);

    /* Assign resources to the algorithm */
    algArray[0] = (IALG_Handle)alg;
    dmaFxnsArray[0] = idma3Fxns;
    status  = DMAN3_grantDmaChannels(0, algArray, dmaFxnsArray, 1/* NUMALGS */);
    if (status != DMAN3_SOK) {
        printf("Could not grant DMA channels to algorithm 0x%x\n",alg); 
    }


    /* Activate the Algorithm */
    DSKT2_activateAlg(scratchId, (IALG_Handle)alg);

    /* Use IALG interfaces to do something */
    /* Do a DMA of 1/3rd the buffer from different offsets */
    /* TODO 
    IDMA3CODEC1_TI_CODECIDMA3->doCopy(&IDMA3CODEC1_TI_CODECIDMA3,  */
    codec->fxns->doCopy(codec, SRCBUFF + 0x200 * (taskId),
            (DSTBUFF + 0x200 * (taskId)), DMAXFER_BUFSIZE/3 * 4 );

    /* Deactivate algorithm */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)alg);

    /* Free resources assigned to this algorihtm */
    status = DMAN3_releaseDmaChannels(algArray, dmaFxnsArray, 1);
    if (status != DMAN3_SOK) {
        printf("Could not release DMA channels for algorithm 0x%x\n",alg);
    }

    /* Free instance of the algorithm created */
    SEM_pend(mutex, SYS_FOREVER);
    DSKT2_freeAlg(scratchId, (IALG_Handle)alg);

    SEM_post(mutex);

    SEM_post(done);

    GT_1trace(ti_sdo_fc_rman_examples_dma, GT_4CLASS,
            "rmanTask> Completed task %d\n", taskId);

    return (0);
}
/* Idle task can do the cleanup */
Void myIdle()
{
    IRES_Status status ;
    Bool result = TRUE;
    Int i;


    /* Check if DMA completed properly */
    for (i = 0; i < DMAXFER_BUFSIZE; i++) {
        if (DSTBUFF[i] != 0x8C0FFEE8) {
            result = FALSE;
            break;
        }
    }

    if (result) {
        printf("Application successful\n");
    }
    else {
        printf("DMA failed\n");
    }

    status = RMAN_exit();

    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_dma, GT_7CLASS,
                "_myIdle> RMAN Exit Failed\n");

        exit(-1);
    }

    exit(0);
}
/*
 *  @(#) ti.sdo.fc.examples.dma; 1, 0, 0,19; 12-1-2010 17:24:42; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

