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
 *  ======== edmacodec1_ti_ires.c ========
 *  EDMA Codec1 algorithm's implementation of IRES_Fxns.
 */

#include <xdc/std.h>
#include <string.h>

/* #include <ti/xdais/dm/iedmacodec1.h>*/
#include <ti/sdo/fc/ires/examples/codecs/edmacodec1/iedmacodec1.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>

/* Header file for the resources used in this example. */
#include <ti/sdo/fc/ires/edma3chan/ires_edma3Chan.h>

#include "edmacodec1_ti.h"
#include "edmacodec1_ti_priv.h"

/* IRES Function Declarations */
static IRES_Status EDMACODEC1_TI_activateRes(IALG_Handle handle, IRES_Handle res);
static IRES_Status EDMACODEC1_TI_activateAllRes(IALG_Handle handle);
static IRES_Status EDMACODEC1_TI_deactivateRes(IALG_Handle h, IRES_Handle res);
static IRES_Status EDMACODEC1_TI_deactivateAllRes(IALG_Handle handle);
static Int32 EDMACODEC1_TI_numResources(IALG_Handle handle);
static IRES_Status EDMACODEC1_TI_getResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc);
static IRES_Status EDMACODEC1_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor * desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);
static IRES_Status EDMACODEC1_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc);
static IRES_Status EDMACODEC1_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);

extern IALG_Fxns EDMACODEC1_TI_IALG;

/*
 *  ======== EDMACODEC1_TI_IRES ========
 */
IRES_Fxns EDMACODEC1_TI_IRES = {
    &EDMACODEC1_TI_IALG,
    EDMACODEC1_TI_getResources,
    EDMACODEC1_TI_numResources,
    EDMACODEC1_TI_initResources,
    EDMACODEC1_TI_reInitResources,
    EDMACODEC1_TI_deInitResources,
    EDMACODEC1_TI_activateRes,
    EDMACODEC1_TI_activateAllRes,
    EDMACODEC1_TI_deactivateRes,
    EDMACODEC1_TI_deactivateAllRes
};


/*
 *  ======== EDMACODEC1_TI_activateAllRes ========
 */
static IRES_Status EDMACODEC1_TI_activateAllRes(IALG_Handle handle)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)handle;
    IRES_Status      status;

    /* Activate all resources - this example has only one. */
    status = EDMACODEC1_TI_activateRes(handle, (IRES_Handle)alg->edmaHandle);
    if (status != IRES_OK) {
        return (status);
    }

    return (IRES_OK);
}

/*
 *  ======== EDMACODEC1_TI_activateRes ========
 */
static IRES_Status EDMACODEC1_TI_activateRes(IALG_Handle handle, 
        IRES_Handle res)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)handle;

    /* Check that res = alg->edmaHandle */
    if (res == (IRES_Handle)(alg->edmaHandle)) {
        if (TRUE == alg->resActive[0]) {
            return (IRES_EFAIL);
        }
        alg->resActive[0] = TRUE;
    }

    return (IRES_OK);
}

/*
 *  ======== EDMACODEC1_TI_deactivateAllRes ========
 */
static IRES_Status EDMACODEC1_TI_deactivateAllRes(IALG_Handle handle) 
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)handle;
    IRES_Status      status = IRES_OK;

    status = EDMACODEC1_TI_deactivateRes(handle, (IRES_Handle)alg->edmaHandle);
    if (status != IRES_OK) {
        return (status);
    }

    return (status);
}

/*
 *  ======== EDMACODEC1_TI_deactivateRes ========
 */
static IRES_Status EDMACODEC1_TI_deactivateRes(IALG_Handle h, IRES_Handle res)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)h;

    /* Check that res = alg->edmaHandle */
    if (res == (IRES_Handle)(alg->edmaHandle)) {
        if (FALSE == alg->resActive[0]) {
            return (IRES_EFAIL);
        }
        alg->resActive[0] = TRUE;
    }

    return (IRES_OK);
}

/*
 *  ======== EDMACODEC1_TI_deInitResources ========
 */
static IRES_Status EDMACODEC1_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)h;


    if (desc[0].handle == (IRES_Handle)alg->edmaHandle) {
        alg->edmaHandle = NULL;
        alg->resActive[1] = FALSE;
    }
    else {
        return (IRES_ENOTFOUND);
    }

    return (IRES_OK);
}

/*
 *  ======== EDMACODEC1_TI_getResources ========
 */
static IRES_Status EDMACODEC1_TI_getResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)h;

    /* 
     * This API could be called to query for resource requirements and after
     * having granted the resources, could also be queried for resource 
     * holdings of the algorithm. The difference is that in the second case a 
     * valid resource handle (that had been granted earlier) would be expected.
     */   
    desc[0].resourceName = IRES_EDMA3CHAN_PROTOCOLNAME;
    desc[0].revision = &IRES_EDMA3CHAN_PROTOCOLREVISION;
    desc[0].protocolArgs = (IRES_ProtocolArgs *)&(alg->edmaArgs); 
    (alg->edmaArgs).size = sizeof(IRES_EDMA3CHAN_ProtocolArgs);
    //(alg->edmaArgs).numPaRams = 1;
    //(alg->edmaArgs).paRamIndex = IRES_EDMA3CHAN_PARAM_ANY; 
    (alg->edmaArgs).numPaRams = 0;
    (alg->edmaArgs).paRamIndex = IRES_EDMA3CHAN_PARAM_NONE; 
    //(alg->edmaArgs).tccIndex = IRES_EDMA3CHAN_TCC_ANY;
    //(alg->edmaArgs).numTccs = 1;
    (alg->edmaArgs).tccIndex = IRES_EDMA3CHAN_TCC_NONE;
    (alg->edmaArgs).numTccs = 0;
    (alg->edmaArgs).qdmaChan = IRES_EDMA3CHAN_CHAN_NONE;
    (alg->edmaArgs).edmaChan = IRES_EDMA3CHAN_EDMACHAN_ANY;
    (alg->edmaArgs).contiguousAllocation = TRUE;
    (alg->edmaArgs).shadowPaRamsAllocation = TRUE;

    desc[0].handle = (IRES_Handle)alg->edmaHandle; 

    return (IRES_OK);
}

/*
 *  ======== EDMACODEC1_TI_initResources ========
 */
static IRES_Status EDMACODEC1_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)h;

    /* 
     * Resource manager has returned a resource handle. Save it in the 
     * algorithm's instance object 
     */ 
    alg->edmaHandle = (IRES_EDMA3CHAN_Handle)desc[0].handle;

    /* 
     * Resource Manager also provides yield functions and yield Args alongwith  
     * the resource handle.
     */
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    return (IRES_OK);
}

/*
 *  ======== EDMACODEC1_TI_numResources ========
 */
/* ARGSUSED */
static Int32 EDMACODEC1_TI_numResources(IALG_Handle handle) 
{
    return (1);
}

/*
 *  ======== EDMACODEC1_TI_reInitResources ========
 */
static IRES_Status EDMACODEC1_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    EDMACODEC1_TI_Obj  *alg = (EDMACODEC1_TI_Obj *)handle;

    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    /* 
     * This function implies that the resource holdings of the algorithms have
     * been changed.
     * Update them in the algorithm instance object. 
     */
    alg->edmaHandle = (IRES_EDMA3CHAN_Handle)desc[0].handle;
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;
    alg->resActive[0] = FALSE;
    alg->resActive[1] = FALSE;

    return (IRES_OK);
}
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.edmacodec1; 1, 0, 0,133; 12-1-2010 17:25:05; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

