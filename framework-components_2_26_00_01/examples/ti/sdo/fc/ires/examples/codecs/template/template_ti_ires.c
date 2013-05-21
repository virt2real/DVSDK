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
 *  ======== template_ti_ires.c ========
 *  Audio decoder "copy" algorithm's implementation of IRES_Fxns.
 */

#include <xdc/std.h>
#include <string.h>

/* #include <ti/xdais/dm/itemplate.h>*/
#include <ti/sdo/fc/ires/examples/codecs/template/itemplate.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>

/* Header file for the NULL resource (NULLRES) used in this example. */
#include <ti/sdo/fc/ires/nullresource/ires_nullres.h>

#include "template_ti.h"
#include "template_ti_priv.h"

/* IRES Function Declarations */
static IRES_Status TEMPLATE_TI_activateRes(IALG_Handle handle, IRES_Handle res);
static IRES_Status TEMPLATE_TI_activateAllRes(IALG_Handle handle);
static IRES_Status TEMPLATE_TI_deactivateRes(IALG_Handle h, IRES_Handle res);
static IRES_Status TEMPLATE_TI_deactivateAllRes(IALG_Handle handle);
static Int32 TEMPLATE_TI_numResources(IALG_Handle handle);
static IRES_Status TEMPLATE_TI_getResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc);
static IRES_Status TEMPLATE_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor * desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);
static IRES_Status TEMPLATE_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc);
static IRES_Status TEMPLATE_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);

/*
 *  ======== TEMPLATE_TI_IRES ========
 */
IRES_Fxns TEMPLATE_TI_IRES = {
    &TEMPLATE_TI_IRES,
    TEMPLATE_TI_getResources,
    TEMPLATE_TI_numResources,
    TEMPLATE_TI_initResources,
    TEMPLATE_TI_reInitResources,
    TEMPLATE_TI_deInitResources,
    TEMPLATE_TI_activateRes,
    TEMPLATE_TI_activateAllRes,
    TEMPLATE_TI_deactivateRes,
    TEMPLATE_TI_deactivateAllRes
};


/*
 *  ======== TEMPLATE_TI_activateAllRes ========
 */
static IRES_Status TEMPLATE_TI_activateAllRes(IALG_Handle handle)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)handle;
    IRES_Status      status;

    /* Activate all resources - this example has only one. */
    status = TEMPLATE_TI_activateRes(handle, (IRES_Handle)alg->nullres);
    if (status != IRES_OK) {
        return (status);
    }

    return (IRES_OK);
}

/*
 *  ======== TEMPLATE_TI_activateRes ========
 */
static IRES_Status TEMPLATE_TI_activateRes(IALG_Handle handle, IRES_Handle res)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)handle;
    /* IRES_NULLRES_Handle    nullres = (IRES_NULLRES_Handle)res; */

    /* Check that res = alg->nullres */
    if (res != (IRES_Handle)(alg->nullres)) {
        return (IRES_EFAIL);
    }

    if (alg->resActive == FALSE) {
        /*
         *  Add code here to do any necessary initialization of the resource 
         *  before starting to use it.
         */

        /* Set the resource to active state */
        alg->resActive = TRUE;
        return (IRES_OK);
    }
    else {
        /* The resource was already active */
        return (IRES_EFAIL);
    }
}

/*
 *  ======== TEMPLATE_TI_deactivateAllRes ========
 */
static IRES_Status TEMPLATE_TI_deactivateAllRes(IALG_Handle handle) 
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)handle;
    IRES_Status      status = IRES_OK;

    status = TEMPLATE_TI_deactivateRes(handle, (IRES_Handle)alg->nullres);

    return (status);
}

/*
 *  ======== TEMPLATE_TI_deactivateRes ========
 */
static IRES_Status TEMPLATE_TI_deactivateRes(IALG_Handle h, IRES_Handle res)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)h;

    /* Check that res = alg->nullres */
    if (res != (IRES_Handle)(alg->nullres)) {
        return (IRES_EFAIL);
    }

    if (alg->resActive == TRUE) {
        /*
         *  Add code here to do what needs to be done when finished using
         *  this resource
         */

        alg->resActive = FALSE;
        return (IRES_OK);
    }
    else {
        /* The resource was not found or was already active */
        return (IRES_EFAIL);
    }
}

/*
 *  ======== TEMPLATE_TI_deInitResources ========
 */
/* ARGSUSED */
static IRES_Status TEMPLATE_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)h;

    alg->resActive = FALSE;

    /* Algorithm relinquishing resource holdings */
    alg->nullres = NULL;

    return (IRES_OK);
}

/*
 *  ======== TEMPLATE_TI_getResources ========
 */
static IRES_Status TEMPLATE_TI_getResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)h;

    desc->resourceName = IRES_NULLRES_PROTOCOLNAME;
    desc->revision = &IRES_NULLRES_PROTOCOLREVISION;
    desc->protocolArgs = NULL; 
    desc->protocolArgs->mode = IRES_SCRATCH;

    /* 
     * This API could be called to query for resource requirements and after
     * having granted the resources, could also be queried for resource 
     * holdings of the algorithm. The difference is that in the second case a 
     * valid resource handle (that had been granted earlier) would be expected.
     */   
    if (alg->nullres != NULL) {
        desc->handle = (IRES_Handle)(alg->nullres);
    }

    return (IRES_OK);
}

/*
 *  ======== TEMPLATE_TI_initResources ========
 */
static IRES_Status TEMPLATE_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)h;

    /* 
     * Resource manager has returned a resource handle. Save it in the 
     * algorithm's instance object 
     */ 
    alg->nullres = desc->handle;

    /* 
     * Resource Manager also provides yield functions and yield Args alongwith  
     * the resource handle.
     */
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    return (IRES_OK);
}

/*
 *  ======== TEMPLATE_TI_numResources ========
 */
/* ARGSUSED */
static Int32 TEMPLATE_TI_numResources(IALG_Handle handle) 
{
    return (1);
}

/*
 *  ======== TEMPLATE_TI_reInitResources ========
 */
static IRES_Status TEMPLATE_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs)
{
    TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)handle;

    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;

    /* 
     * This function implies that the resource holdings of the algorithms have
     * been changed.
     * Update them in the algorithm instance object. 
     */
    alg->nullres = (IRES_Handle)desc->handle;
    alg->yieldFxn = yieldFxn;
    alg->yieldArgs = yieldArgs;
    alg->resActive = FALSE;

    return (IRES_OK);
}

/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.template; 1, 0, 0,170; 12-1-2010 17:25:09; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

