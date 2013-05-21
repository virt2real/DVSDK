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

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/dskt2/dskt2.h>

/* IRES resources */
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/bufres/bufres.h>

/* Algorithm */
#include <ti/sdo/fc/ires/examples/codecs/edmacodec1/edmacodec1_ti.h>

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
#define NUMTASKS 3 /* 12 */

/* Maximum number of tasks */
#define MAXTASKS 12

/* Required to GT generate trace from the app */
GT_Mask ti_sdo_fc_rman_examples_dmaxferscratch;

/* Buffers to perform DMA transfer on */
unsigned int SRCBUFF[DMAXFER_BUFSIZE];
unsigned int DSTBUFF[DMAXFER_BUFSIZE];

/*
 * Buffer base and end generated via xdt file (required for ires.bufres resource)
 */
extern far UInt32 BUFMEM_base;
extern far UInt32 BUFMEM_end;

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
    13,              1,      0,     0x4,
    13,              1,      0,     0x5,
    13,              1,      0,     0x6,
    13,              1,      0,     0x7,
    12,              1,      1,     0x8,
    13,              1,      0,     0x9,
    12,              1,      1,     0xA,
    13,              1,      0,     0xB,
    12,              1,      1,     0xC
};

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);
extern Int rmanTask(Arg taskId, Arg priority, Arg scratchId, Arg yieldFlag,
        Arg fillValue);

Int main()
{
    Int size = 0;
    Int i = 0;
    IRES_Status status;
    BUFRES_Params bufParams;

    GT_create(&ti_sdo_fc_rman_examples_dmaxferscratch,
            "ti.sdo.fc.rman.examples.dmaxferscratch");

    //Uncomment the line below for trace
    GT_set(MOD_NAME "=4567");


    /* Initialize the framework modules we're going to use */
    status = RMAN_init();
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return (-1);
    }
        /* Bufres does not support autoRegister, so need to register it
           explicitly */
    bufParams.iresConfig.allocFxn = RMAN_PARAMS.allocFxn;
    bufParams.iresConfig.freeFxn = RMAN_PARAMS.freeFxn;
    bufParams.iresConfig.size = size;
    bufParams.base = (Void *)&BUFMEM_base;
    bufParams.length = (UInt32)&BUFMEM_end - (UInt32)&BUFMEM_base + 1;

    /* Register the BUFRES protocol/resource manager with the
       generic resource manager */
    status = RMAN_register(&BUFRES_MGRFXNS, (IRESMAN_Params *)&bufParams);

    if (IRES_OK != status) {
        printf("BUFRES Protocol Registration Failed \n");
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

        GT_0trace(ti_sdo_fc_rman_examples_dmaxferscratch, GT_7CLASS,
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

            GT_1trace(ti_sdo_fc_rman_examples_dmaxferscratch, GT_7CLASS,
            "_smain> TSK_create of task %d failed\n", i+1);

            SYS_abort("TSK_create() of task %d failed\n",i+1);
        }
    }

    /* Wait for completion of each task */
    for (i=0; i < NUMTASKS; i++) {
        SEM_pend(done, SYS_FOREVER);
    }

    SEM_delete(mutex);
    SEM_delete(done);

    GT_0trace(ti_sdo_fc_rman_examples_dmaxferscratch, GT_4CLASS,
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

    GT_1trace(ti_sdo_fc_rman_examples_dmaxferscratch, GT_4CLASS,
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

    /* Unregister the protocol */
    if (IRES_OK != RMAN_unregister(&BUFRES_MGRFXNS)) {

        GT_0trace(ti_sdo_fc_rman_examples_dmaxferscratch, GT_7CLASS,
                "_myIdle> Unregister BUFRES Protocol Failed\n");

        exit(-1);
    }

    status = RMAN_exit();

    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_dmaxferscratch, GT_7CLASS,
                "_myIdle> RMAN Exit Failed\n");

        exit(-1);
    }

    exit(0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.dmaxferscratch; 1, 0, 0,30; 12-1-2010 17:25:40; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

