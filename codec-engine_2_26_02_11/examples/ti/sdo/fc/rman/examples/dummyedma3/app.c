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
 *
 *  Test app for a dummy codec that requests IRES EDMA3CHAN resources
 */
#include <xdc/std.h>
#include <stdio.h>
#include <stdlib.h>

#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include "ires_algorithm.h"

/* Trace */
#include <ti/sdo/utils/trace/gt.h>

/* Used to enable trace on specific modules */
#define MOD_NAME "*"
/* #define MOD_NAME "ti.sdo.fc.rman"*/

/* Required to GT generate trace from the app */
GT_Mask ti_sdo_fc_rman_examples_dummyEdma3_GTMask;

/*
 * extern declaration
 */
extern Int smain(Int argc, Char * argv[]);

Int main(Int argc, Char * argv[])
{
    GT_create(&ti_sdo_fc_rman_examples_dummyEdma3_GTMask,
            "ti.sdo.fc.rman.examples.dummyEdma3");

    //Uncomment below for trace
    //GT_set(MOD_NAME "=4567");

#ifdef xdc_target__os_Linux
    return (smain(argc, argv));
#else
    return (0);
#endif
}

Int smain(Int argc, Char * argv[])
{

    IRES_Status status;
    Int scratchId = 1;
    IALG_Status algStatus;
    IALG_Fxns * algFxns = &DUMRES_TI_IALG;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    DUMRES_TI_Handle dumHandle = NULL;
    Bool result = TRUE;
#ifdef xdc_target__os_Linux
    Int sleepTime = 0;

    if (argc > 1) {
        sleepTime = atoi(argv[1]);
    }
#endif

    if (argc > 2) {
        scratchId = atoi(argv[2]);
    }

    /* Initialize the framework modules we're going to use */
    status = RMAN_init();
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return (-1);
    }


    ALG_init();

    /*
     * Create an instance of the algorithm using "algFxns"
     */
    dumHandle = (DUMRES_TI_Handle)ALG_create( (IALG_Fxns *)algFxns,
            (IALG_Handle)NULL, (IALG_Params *)NULL);
    if (dumHandle == NULL) {
        printf("Alg creation failed \n");
        return -1;
    }

    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK == RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns, scratchId)) {

        /* Activate the Algorithm */
        ALG_activate((IALG_Handle)dumHandle);

        /* Activate All Resources */
        RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, -1);

        /* Use IALG interfaces to do something */
        ((IALG_Handle)dumHandle)->fxns->algControl((IALG_Handle)dumHandle,
                (IALG_Cmd)NULL, &algStatus);
#ifdef xdc_target__os_Linux
          sleep(sleepTime);
#endif

        /* Deactivate All Resources */
        RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, scratchId);

        /* Deactivate algorithm */
        ALG_deactivate((IALG_Handle)dumHandle);

        /* Free resources assigned to this algorithm */
        if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                    resFxns, scratchId)) {
            printf("Free Resource Failed \n");
            return -1;
        }
    }
    else {
        printf("Assign Resource Failed \n");
        result = FALSE;
    }

    /* Free instance of the algorithm created */
    ALG_delete((IALG_Handle)dumHandle);

    /* Unregister the protocol */
    if (IRES_OK != RMAN_exit()) {
            printf("Unregister Protocol Failed \n");
            return -1;
    }

    if (result) {
        printf("Application exiting normally\n");
    }
    else {
        printf("Error somewhere in the app.\n");
    }
    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.dummyedma3; 1, 0, 0,30; 12-1-2010 17:25:43; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

