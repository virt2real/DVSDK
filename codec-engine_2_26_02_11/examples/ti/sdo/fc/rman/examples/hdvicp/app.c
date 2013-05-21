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
 * ======== app.c ========
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>
#include <ti/bios/include/tsk.h>
#include <ti/bios/include/sys.h>
#include <ti/sdo/fc/dskt2/dskt2.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <stdio.h>
#include <stdlib.h>

#include "ires_algorithm.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_rman_examples_hdvicp;

/* Number of tasks to run */
#define NUMTASKS 12

/* Maximum number of tasks that can be configured */
#define MAXTASKS 12

/* MODNAME is used to configure trace for one or more modules */
#define MODNAME "ti.sdo.fc.rman.examples.hdvicp"
//#define MODNAME "*"

/*
 *  ======== ScratchTskAttrs ========
 *  Attributes of each task created
 */
typedef struct ScratchTskAttrs {
    Int         priority;       /* Priority of task */
    Int         scratchId;      /* Scratch group in which to create the task */
    IRES_HDVICP_RequestType id[NUM_RESOURCES];
                                /* Resource that will be requested */
    Int         yieldFlag;      /* Whether this alg will yield to another */
} ScratchTskAttrs;

/* heapId in which to create the tasks */
extern Int EXTMEM_HEAP;

extern Int smain(Int argc, Char * argv[]);
extern Int rmanTask(Arg scratchId, Arg resourceId,  Arg priority, Arg taskId,
        Arg yieldFlag);
extern Void myIdle();

/* Scratch task parameters */
static ScratchTskAttrs attrsTable[MAXTASKS] = {
    /* priority,    scratchGroup    resources (0,1)                 yieldFlag */
    12,              1,      {IRES_HDVICP_ID_0,         IRES_HDVICP_ID_1},   1,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    12,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 1,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    12,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 1,
    13,              1,      {IRES_HDVICP_ID_ANY,       IRES_HDVICP_ID_ANY}, 0,
    12,              1,      {IRES_HDVICP_ID_0,         IRES_HDVICP_ID_1},   1,
};

static SEM_Handle done = NULL;  /* Gets posted by last task to finish */
static SEM_Handle mutex = NULL; /* Protect DSKT2_createAlg and DSKT2_freeAlg */
/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);

IRESMAN_HdVicpParams configParams = {
    {0,      /* Size of this structure */
    NULL,
    NULL    /*
             * RMAN_PERSISTENTALLOCFXN,
             * RMAN_PERSISTENTFREEFXN,
             */
    },
    2,      /* Number of HDVICP resources to manage */
    NULL,   /* Rsvd for future use */
};

Int main()
{
    IRES_Status status;

    /* The 2 lines below, are if GT trace will be used to print trace from
       the app, not required if you will be using printfs in the apps files */
    GT_init();
    GT_create(&ti_sdo_fc_rman_examples_hdvicp,"ti.sdo.fc.rman.examples.hdvicp");

    /* GT_set lets you configure trace at different levels for different
       modules */
    GT_set(MODNAME "=01234567");
    GT_set("ti.sdo.fc.rman" "=4567");
    GT_set("ti.sdo.fc.dskt2" "=67");
    GT_set("ti.sdo.fc.ires.hdvicp" "=01234567");

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_main> Enter \n");

    /* Initialize Framework modules */
    status = RMAN_init();

    if (IRES_OK != status) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_main> RMAN "
                "Initialization failed \n");
        return (-1);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_main> Exit \n");

    return (0);

}

/*
 *  ======== myIdle ========
 * Idle task is lowest priority, will be run when all other tasks have finished
 */
Void myIdle()
{
    IRES_Status status ;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_myIdle> Enter \n");

    status = RMAN_exit();

    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_myIdle> "
            "RMAN exit failed\n");

        exit(-1);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_myIdle> Exit \n");

    exit(0);
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

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_smain> Enter \n");

    /* Keeps track of all tasks that are created */
    done = SEM_create(0, NULL);

    /* Makes sure accesses to DSKT2_create/delete are serialized */
    mutex = SEM_create(1, NULL);

    if ((done == NULL) || (mutex == NULL)) {

        SYS_abort("Sem create failed \n");
    }

    /* Specify which heap to use to create tasks */
    attrs.stackseg = EXTMEM_HEAP;

    /* Use a bigger stack size when printing out trace */
    attrs.stacksize = 0x1000;

    for (i = 0; i < NUMTASKS; i++) {

        attrs.priority = attrsTable[i].priority;

        /* Create a task */
        tsk = TSK_create((Fxn)rmanTask, &attrs,
                                (Arg)(attrsTable[i].scratchId),
                                (Arg)(&(attrsTable[i].id)),
                                (Arg)(attrsTable[i].priority),
                (Arg)(i +1),
                (Arg)(attrsTable[i].yieldFlag));

        if (tsk == NULL) {

            GT_1trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rman> "
                "Task #%d create failed \n",i);

            printf("TSK_create() of task %d failed\n",i+1);
            return (-1);
        }
    }

    /* Wait for each task to finish */
    for (i = 0; i < NUMTASKS; i++) {
        SEM_pend(done, SYS_FOREVER);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_smain> "
            "TEST PASSED \n");

    SEM_delete(mutex);
    SEM_delete(done);

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_smain> Exit \n");

    return 0;
}


/*
 *  ======== rmanTask ========
 *
 */
/* ARGSUSED */
Int rmanTask(Arg scratchId, Arg resourceId,  Arg priority, Arg taskId,
        Arg yieldFlag)
{
    Int i;
    IALG_Fxns * algFxns = (IALG_Fxns *)&DUMALG_TI_IDUMALG;
    IRES_Fxns * resFxns = &DUMALG_TI_IRES;
    IDUMALG_Handle dumHandle = NULL;
    IDUMALG_Params params;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_rmanTask> Enter \n");

    params.size = sizeof(IDUMALG_Params);

    GT_4trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_rmanTask> "
            "Task #%d: ScratchId %d, Priority %d Yield %d\n",taskId, scratchId,
            priority, yieldFlag);

    params.yieldFlag  = yieldFlag;
    params.taskId = taskId;

    /* Configure the params to indicate the HDVICP requirements of each alg */
    for (i = 0; i < NUM_RESOURCES; i++) {
        params.hdvicp[i] = *((IRES_HDVICP_RequestType *)resourceId + i);
        GT_1trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_rmanTask> "
                "Requesting resource %d (2 => ANY)\n",(Int)params.hdvicp[i]);
    }

    /* Use mutex to serialize the creates */
    SEM_pend(mutex, SYS_FOREVER);

    /* Create an instance of the algorithm using "algFxns" */
    dumHandle = (IDUMALG_Handle)DSKT2_createAlg((Int)scratchId,
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)&params);
    if (dumHandle == NULL) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Alg creation failed\n");
        printf("App failed\n");
        return (-1);
    }

    SEM_post(mutex);

    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Assign resource failed\n");
        return (-1);
    }


    /* Activate the Algorithm */
    DSKT2_activateAlg(scratchId, (IALG_Handle)dumHandle);

    /* Activate All Resources */
    RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /* Use the ALG handle to do something (with the resource acquired) */
    dumHandle->fxns->useHDVICP(dumHandle, taskId);

    /* Deactivate All Resources */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /* Deactivate the algorithm */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)dumHandle);

    /* Free resources assigned to this algorithm */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Free resource failed\n");
        return (-1);
    }

    SEM_pend(mutex, SYS_FOREVER);

    /* Free instance of the algorithm created */
    DSKT2_freeAlg(scratchId, (IALG_Handle)dumHandle);
    SEM_post(mutex);

    SEM_post(done);

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_rmanTask> Exit \n");

    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.hdvicp; 1, 0, 0,133; 12-1-2010 17:25:45; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

