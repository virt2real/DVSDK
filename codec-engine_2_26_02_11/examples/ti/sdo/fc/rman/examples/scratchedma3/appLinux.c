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
 * */
#include <xdc/std.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>
#include <ti/sdo/fc/edma3/edma3_config.h>
#include <stdio.h>
#include <stdlib.h>

#include <ti/sdo/fc/utils/api/alg.h>
#include "ires_algorithm.h"
#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_rman_examples_scratchEdma3_GTMask;
/* #define MOD_NAME "ti.sdo.fc.rman"*/
#define MOD_NAME "*"

/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);

Int main(Int argc, String argv[])
{
    IRES_Status status;

    GT_create(&ti_sdo_fc_rman_examples_scratchEdma3_GTMask, 
            "ti.sdo.fc.rman.examples.scratchEdma3");
    GT_set(MOD_NAME "=4567");
    GT_init();
    status = RMAN_init(); 
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }

    return (smain(argc, argv));
}

/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, String argv[])
{

    Int scratchId1 = 0;
        Int scratchId2 = 1;
/*      IALG_Status algStatus;*/
    IALG_Fxns * algFxns = &DUMRES_TI_IALG;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    DUMRES_TI_Handle dumHandle1 = NULL; 
    DUMRES_TI_Handle dumHandle2 = NULL; 
    EDMA3_Handle rmHandle = NULL;
    EDMA3_ResDesc resObj;
    Bool status = TRUE; 
    IDUMRES_Params params;

    if (argc > 1) {
        scratchId1 = atoi(argv[1]);
    }
 
    if (argc > 2) {
        scratchId2 = atoi(argv[2]);
    }
    ALG_init();
    /*
     * Create an instance of the algorithm using "algFxns" 
     */
    params.algNum = 1;
    dumHandle1 = (DUMRES_TI_Handle)ALG_create((IALG_Fxns *)algFxns,
            (IALG_Handle)NULL, (IALG_Params *)&params);
    if (dumHandle1 == NULL) {
        printf("Alg1 creation failed \n");
        return -1;
    } 

    params.algNum = 2;
    dumHandle2 = (DUMRES_TI_Handle)ALG_create((IALG_Fxns *)algFxns,
            (IALG_Handle)NULL, (IALG_Params *)&params);
    if (dumHandle2 == NULL) {
        printf("Alg2 creation failed \n");
        return -1;
    } 

    /* Create an instance of an algorithm that implements IALG and IRES_Fxns */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle1,
                resFxns,scratchId1)) {
        printf("Assign Resource Failed \n");
        status = FALSE;
        goto AppEnd1;
    }

    /*
     * Activate the Algorithm
     */
    ALG_activate((IALG_Handle)dumHandle1);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)dumHandle1, resFxns, scratchId1);

    /*
     * Use IALG interfaces to do something 
     */
    //TODO: DSKT2_controlAlg((IALG_Handle)dumHandle, (IALG_Cmd)NULL, &algStatus);
    
    /* Assign resources to the second algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle2,
                resFxns, scratchId2)) {
        printf("Assign Resource Failed \n");
        return -1;
    }
    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle1, resFxns, scratchId1);

    /*
     * Deactivate algorithm 
     */
    ALG_deactivate((IALG_Handle)dumHandle1);

    /*
     * Activate the Algorithm
     */
    ALG_activate((IALG_Handle)dumHandle2);

    /*
     * Activate All Resources
     */
    RMAN_activateAllResources((IALG_Handle)dumHandle2, resFxns, scratchId2);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle1),
                resFxns, scratchId1)) {
        printf("Free Resource Failed \n");
        return -1;
    }
    /* 
     * Acquire the EDMA3 handle first
     */           
    rmHandle = EDMA3_getResourceManager((IALG_Handle)NULL, (Int)-1);
    
    if (NULL == rmHandle) {
        printf("Error obtaining SYSTEM resource Manager Handle \n");
        return (-1);
    }

    resObj.resId = 65; 
    resObj.type = EDMA3_RES_PARAM_SET;
    

    if (EDMA3_SOK != EDMA3_allocResource(rmHandle, &resObj)) {
        printf("Note, could not allocate this resource.\n");
    }

    resObj.resId = 126; 
    if (EDMA3_SOK != EDMA3_allocResource(rmHandle, &resObj)) {
        printf("Note, could not allocate resource %d\n", resObj.resId);
    }
    
    if (EDMA3_SOK != EDMA3_releaseResourceManager(NULL, -1)) {
        printf("Note, releasing system resource manager handle\n");
    } 

    /*
     * Deactivate All Resources
     */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle2, resFxns, scratchId2);

    /*
     * Deactivate algorithm 
     */
    ALG_deactivate((IALG_Handle)dumHandle2);

    /*
     * Free resources assigned to this algorihtm
     */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle2),
                resFxns, scratchId2)) {
        printf("Free Resource Failed \n");
        return -1;
    }

AppEnd1:
    /*
     * Free instance of the algorithm created
     */
    ALG_delete((IALG_Handle)dumHandle1);

    /*
     * Free instance of the algorithm created
     */
    ALG_delete((IALG_Handle)dumHandle2);

    RMAN_exit();

    if (status)
        printf("Application exiting normally\n");

    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.scratchedma3; 1, 0, 0,30; 12-1-2010 17:25:52; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

