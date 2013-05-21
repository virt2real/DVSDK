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
/*
 *  ======== app.c ========
 *
 *  Test app for EDMA3-requesting algorithms
 */
#include <xdc/std.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/ires/edma3chan/iresman_edma3Chan.h>
#include <ires_algorithm.h>
#include <stdio.h>

#include <ti/sdo/fc/ires/hdvicp/iresman_hdvicp.h>

#include <ti/sdo/utils/trace/gt.h>
#define MOD_NAME "*"
GT_Mask ti_sdo_fc_rman_examples_staticReg_GTMask;

extern Bool DSKT2_allocPersistent(IALG_MemRec *memTab, Int numRecs);

extern Void DSKT2_freePersistent(IALG_MemRec *memTab, Int numRecs);

static IRESMAN_Edma3ChanParams configParams = { sizeof(IRESMAN_Edma3ChanParams),        DSKT2_allocPersistent, DSKT2_freePersistent };

static IRESMAN_Fxns * RMAN_registryEntryArray[] = {&IRESMAN_EDMA3CHAN};  

static IRESMAN_Params * RMAN_registryResmanArgsArray[] = 
        {(IRESMAN_Params *)&configParams};

/*
 * extern declaration 
 */
extern Int smain(Int argc, Char * argv[]);

void main()
{
    GT_create(&ti_sdo_fc_rman_examples_staticReg_GTMask, 
            "ti.sdo.fc.rman.examples.staticReg");

    /* To see internal tracing details, uncomment this line */
    GT_set(MOD_NAME "=4567");

/* Statically register entries with RMAN */

    RMAN_numRegistryEntries  = 1;
    RMAN_registryEntries = RMAN_registryEntryArray; 
    RMAN_registryResmanArgs = RMAN_registryResmanArgsArray;
}


/* ARGSUSED - this line tells the compiler to not generate compiler warnings 
 * for unused arguments */ 
Int smain(Int argc, Char * argv[])
{
    IRES_Status status;
    Int scratchId = 1;
    IALG_Status algStatus;
    IALG_Fxns * algFxns = &DUMRES_TI_IALG;
    IRES_Fxns * resFxns = &DUMRES_TI_IRES;
    DUMRES_TI_Handle dumHandle = NULL; 

    /* Initialize the framework modules we're going to use */
    status = RMAN_init(); 
    if (IRES_OK != status) {
        printf("RMAN initialization Failed \n");
        return -1;
    }

    /* Create an instance of the algorithm using "algFxns" */
    dumHandle = (DUMRES_TI_Handle)DSKT2_createAlg(scratchId, 
            (IALG_Fxns *)algFxns, NULL,(IALG_Params *)NULL);
    if (dumHandle == NULL) {
        printf("Alg creation failed \n");
        return -1;
    } 

    /* Assign resources to the algorithm */
    if (IRES_OK != RMAN_assignResources((IALG_Handle)dumHandle,
                resFxns,-1)) {
        printf("Assign Resource Failed \n");
        return -1;
    }


    /* Activate the Algorithm */
    DSKT2_activateAlg(scratchId, (IALG_Handle)dumHandle);

    /* Activate All Resources */
    RMAN_activateAllResources((IALG_Handle)dumHandle, resFxns, -1);

    /* Typically, here the app would use the alg to do something ... */
    DSKT2_controlAlg((IALG_Handle)dumHandle, (IALG_Cmd)NULL, &algStatus);
    
    /* Deactivate All Resources */
    RMAN_deactivateAllResources((IALG_Handle)dumHandle, resFxns, -1);

    /* Deactivate algorithm */
    DSKT2_deactivateAlg(scratchId, (IALG_Handle)dumHandle);

     /* Free resources assigned to this algorihtm */
    if (IRES_OK != RMAN_freeResources((IALG_Handle)(dumHandle),
                resFxns, -1)) {
        printf("Free Resource Failed \n");
        return -1;
    }



    /* Free instance of the algorithm created */
    DSKT2_freeAlg(scratchId, (IALG_Handle)dumHandle);

    RMAN_exit();

    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.staticreg; 1, 0, 0,30; 12-1-2010 17:25:54; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

