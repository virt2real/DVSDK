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
/**
 *  @file       ti/sdo/fc/rman/examples/hdvicp/appLinux.c
 *
 *  @brief      Test app for HDVICP-requesting algorithms
 *
 */
#include <xdc/std.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <stdio.h>
#include <stdlib.h>

#include "ires_algorithm.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_rman_examples_hdvicp;

/* Maximum number of tasks that can be configured */
#define MAXTASKS 12
/* MODNAME is used to configure trace for one or more modules */
#define MODNAME "ti.sdo.fc.rman.examples.hdvicp"

/*
 *  ======== ScratchTskAttrs ========
 *  Attributes of each task created
 */
typedef struct ScratchTskAttrs {
    Int         priority;       /* Priority of task */
    Int         scratchId;      /* Scratch group in which to create the task */
    IRES_HDVICP_RequestType id[2];
    Int         yieldFlag;
} ScratchTskAttrs;

/* heapId in which to create the tasks */
extern Int EXTMEM_HEAP;

extern Int smain(Int argc, Char * argv[]);
extern Int rmanTask(Int argc, Char * argv[]);
extern Int myIdle(Int argc, Char * argv[]);

/* Scratch task parameters */
static ScratchTskAttrs attrsTable[MAXTASKS] = {
    /* priority,  scratchGroup  resources                       yieldFlag */
    {12,        1,      {IRES_HDVICP_ID_0,      IRES_HDVICP_ID_1},   1},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_0},   0},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {12,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 1},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {12,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 1},
    {13,        1,      {IRES_HDVICP_ID_ANY,    IRES_HDVICP_ID_ANY}, 0},
    {12,        1,      {IRES_HDVICP_ID_0,      IRES_HDVICP_ID_1},   1},
/*
    {13,        1,      {IRES_HDVICP_ID_1,      IRES_HDVICP_ID_ANY}, 1},
    {13,        3,      {IRES_HDVICP_ID_0,      IRES_HDVICP_ID_ANY}, 0},
    {14,        3,      {IRES_HDVICP_ID_1,      IRES_HDVICP_ID_ANY}, 1},
    {13,        3,      {IRES_HDVICP_ID_1,      IRES_HDVICP_ID_ANY}, 1}
 */
};

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
    1,      /* Number of resources to manage */
    NULL,   /* Rsvd for future use */
};

Int main(Int argc, String argv[])
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

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_main> Enter\n");

    /* Initialize Framework modules */
    status = RMAN_init();

    if (IRES_OK != status) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_main> RMAN "
                "Initialization failed \n");
        return (-1);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_main> Exit\n");

    return (rmanTask(argc, argv));
}


/*
 * Idle task to clean up before app closes
 */
/* ARGSUSED */
Int myIdle(Int argc, Char * argv[])
{
    IRES_Status status ;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_myIdle> Enter\n");

    status = RMAN_exit();

    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_myIdle> "
            "RMAN exit failed\n");

        exit(-1);
    }

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_myIdle> Exit\n");

    return(0);
}


/* ARGSUSED */
Int rmanTask(Int argc, Char * argv[])
{
    Int i;
    IALG_Fxns * algFxns = (IALG_Fxns *)&DUMALG_TI_IDUMALG;
    IRES_Fxns * resFxns = &DUMALG_TI_IRES;
    IDUMALG_Handle dumHandle = NULL;
    IDUMALG_Params params;
    Int taskId = 1;
    Int scratchId = -1;

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_rmanTask> Enter\n");

    params.size = sizeof(IDUMALG_Params);

    params.yieldFlag  = FALSE;
    params.taskId = taskId;

    /* Configure the params to indicate the HDVICP requirements of each alg */
    for (i = 0; i < NUM_RESOURCES; i++) {
        params.hdvicp[i] = *((IRES_HDVICP_RequestType *)&attrsTable[0].id[i]);
        GT_1trace(ti_sdo_fc_rman_examples_hdvicp, GT_4CLASS, "_rmanTask> "
        "Requesting resource %d (2 => ANY)\n",(Int)params.hdvicp[i]);
    }

    ALG_init();

    /* Create an instance of the algorithm using "algFxns" */
    dumHandle = (IDUMALG_Handle)ALG_create((IALG_Fxns *)algFxns,
            (IALG_Handle)NULL, (IALG_Params *)&params);
    if (dumHandle == NULL) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Alg creation failed\n");
        printf("App failed\n");
        return (myIdle(argc, argv));
    }

    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Assign resource failed\n");
        return (myIdle(argc, argv));
    }


    /* Activate the Algorithm */
    ALG_activate((IALG_Handle)dumHandle);

    /* Activate All Resources */
    RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /* Use IALG interfaces to do something */
    dumHandle->fxns->useHDVICP(dumHandle, taskId);

    /* Deactivate All Resources */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /* Deactivate the algorithm */
    ALG_deactivate((IALG_Handle)dumHandle);

    /* Free resources assigned to this algorithm */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_7CLASS, "_rmanTask> "
                "Free resource failed\n");
        return (myIdle(argc, argv));
    }

    /* Free instance of the algorithm created */
    ALG_delete((IALG_Handle)dumHandle);

    GT_0trace(ti_sdo_fc_rman_examples_hdvicp, GT_ENTER, "_rmanTask> Exit\n");

    return (myIdle(argc, argv));
}
/*
 *  @(#) ti.sdo.fc.rman.examples.hdvicp; 1, 0, 0,133; 12-1-2010 17:25:45; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

