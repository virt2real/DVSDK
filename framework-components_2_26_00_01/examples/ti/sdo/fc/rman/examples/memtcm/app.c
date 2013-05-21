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
 *  Creates one algorithm, that requests a bunch of resources in a  particular
 *  (specified) scratch group.
 *
 */

#include <xdc/std.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/fc/ires/memtcm/iresman_memtcm.h>
#include "ires_algorithm.h"

#include <ti/sdo/fc/utils/api/alg.h>
#include <stdio.h>
#include <stdlib.h>

GT_Mask ti_sdo_fc_rman_examples_memtcm_GTMask;

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);
extern int sleep(unsigned int secs);
extern Int myIdle(Int argc, Char * argv[]);

static Bool result = TRUE;

#define CE_IPC 1

/* ARGSUSED */
Int main(Int argc, Char * argv[])
{
    IRES_Status status;

    GT_create(&ti_sdo_fc_rman_examples_memtcm_GTMask,
            "ti.sdo.fc.ires.memtcm.test");

    GT_set("*" "=01234567");

    status = RMAN_init();
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }

    return (smain(argc, argv));
}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings
 * for unused arguments */
Int smain(Int argc, Char * argv[])
{

    IRES_Status status;
    Int scratchId = 2;
    IALG_Fxns * algFxns = (IALG_Fxns *)&DUMRES_TI_IDUMRES;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    IDUMRES_Handle dumHandle = NULL;
    IDUMRES_Params params;
    Int sleepTime = 0;

    if (argc > 1) {
        sleepTime = atoi(argv[1]);
    }

    if (argc > 2) {
        scratchId = atoi(argv[2]);
    }

    ALG_init();

    /*
     * Create an instance of the algorithm using "algFxns"
     */
    //params.taskId = taskId;
    params.taskId = 6;
    dumHandle = (IDUMRES_Handle)ALG_create( (IALG_Fxns *)algFxns,
            (IALG_Handle)NULL, (IALG_Params *)&params);
    if (dumHandle == NULL) {
        printf("Alg creation failed \n");
        return -1;
    }

    /*
     * Supply initialization information for the RESMAN while registering
     */
    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    status = RMAN_assignResources((IALG_Handle)dumHandle, resFxns,scratchId);
    if (IRES_OK != status) {
        printf("Assign Resource Failed \n");
        result = FALSE;
    }
    else {


        /*
         * Activate the Algorithm
         */
        ALG_activate((IALG_Handle)dumHandle);

        /*
         * Activate All Resources
         */
        RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, -1);

        /*
         * Use IALG interfaces to do something
         */
        sleep(sleepTime);

        /*
         * Deactivate All Resources
         */
        RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, -1);

        /*
         * Deactivate algorithm
         */
        ALG_deactivate((IALG_Handle)dumHandle);

        /*
         * Free resources assigned to this algorihtm
         */
        status = RMAN_freeResources((IALG_Handle)(dumHandle), resFxns,
                scratchId);
        if (IRES_OK != status) {
            printf("Free Resource Failed \n");
            result = FALSE;
        }
    }

    /*
     * Free instance of the algorithm created
     */
    ALG_delete((IALG_Handle)dumHandle);

    return (myIdle(argc, argv));
}

/* ARGSUSED */
Int myIdle(Int argc, Char * argv[])
{
    IRES_Status status;

    status = RMAN_exit();

    if (status != IRES_OK) {
        result = FALSE;
    }

    if (result) {
        printf("TEST PASSED\n");
    }
    else {
        printf("TEST FAILED.\n");
    }
    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.memtcm; 1, 0, 0,45; 12-1-2010 17:25:44; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

