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

#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/sdma/iresman_sdma.h>
#include <ti/sdo/fc/ires/sdma/ires_sdma.h>
#include <ti/sdo/fc/utils/api/alg.h>

#include <stdio.h>
#include <stdlib.h>

#include "ires_algorithm.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_rman_examples_sdma;

#define NUMTASKS 12
#define MAXTASKS 12
#define MODNAME "ti.sdo.fc.rman.examples.sdma"

/*
 * Tasks
 */
extern Int rmanTask(Int argc, Char * argv[]);
extern Void myIdle();

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);

IDUMALG_Params params;

Int main(Int argc, String argv[])
{
    IRES_Status status;

    GT_init();
    GT_create(&ti_sdo_fc_rman_examples_sdma,"ti.sdo.fc.rman.examples.sdma");
    GT_set(MODNAME "=01234567");
    GT_set("ti.sdo.fc.rman=4567");
    GT_set("ti.sdo.fc.ires.sdma=01234567");

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_main> Enter\n");

    status = RMAN_init();
    if (IRES_OK != status) {
        GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_7CLASS, "_main> RMAN "
                "Initialization failed\n");
        return -1;
    }

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_main> Exit \n");

    return (rmanTask(argc, argv));
}

Void myIdle()
{
    IRES_Status status ;

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_myIdle> Enter \n");

    status = RMAN_exit();
    if (IRES_OK != status) {

        GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_7CLASS, "_myIdle> "
            "RMAN exit failed\n");

        exit(-1);
    }

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_myIdle> Exit\n");

    exit(0);
}

/*
 *  ======== smain ========
 */
/* ARGSUSED */
Int rmanTask(Int argc, Char * argv[])
{
    Int scratchId = -1;
    Int taskId = 1;
    Int yieldFlag = FALSE;

    IALG_Fxns * algFxns = &DUMALG_TI_IALG;
    IRES_Fxns * resFxns = &DUMALG_TI_IRES;
    IDUMALG_Handle dumHandle = NULL;

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_rmanTask> Enter\n");

    params.size = sizeof(IDUMALG_Params);

    GT_3trace(ti_sdo_fc_rman_examples_sdma, GT_4CLASS, "_rmanTask> "
            "Task #%d: ScratchId %d, Yield %d\n", taskId, scratchId,
            yieldFlag);

    params.yieldFlag  = yieldFlag;
    params.taskId = taskId;

    ALG_init();
    /*
     * Create an instance of the algorithm using "algFxns"
     */
    dumHandle = (IDUMALG_Handle)ALG_create((IALG_Fxns *)algFxns,
            (IALG_Handle)NULL, (IALG_Params *)&params);

    if (dumHandle == NULL) {
        GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_7CLASS, "_rmanTask> "
                "Alg creation failed\n");
        return -1;
    }
    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_7CLASS, "_rmanTask> "
                "Assign resource failed\n");
        return -1;
    }

    /* Activate the Algorithm */
    ALG_activate((IALG_Handle)dumHandle);

    /* Activate All Resources */
    RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /* Use IALG interfaces to do something */
    (DUMALG_TI_IDUMALG).useSDMA(dumHandle, taskId);

    /* Deactivate All Resources */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

    /* Deactivate algorithm */
    ALG_deactivate((IALG_Handle)dumHandle);

    /* Free resources assigned to this algorihtm */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                resFxns, scratchId)) {
        GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_7CLASS, "_rmanTask> "
                "Free resource failed\n");
        return -1;
    }

    /* Free instance of the algorithm created */
    ALG_delete((IALG_Handle)dumHandle);

    ALG_exit();

    GT_0trace(ti_sdo_fc_rman_examples_sdma, GT_ENTER, "_rmanTask> Exit\n");

    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.sdma; 1, 0, 0,132; 12-1-2010 17:25:55; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

