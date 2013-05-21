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
 *  ======== vicp2codec1_ti_ires.c ========
 *  EDMA Codec1 algorithm's implementation of IRES_Fxns.
 */

#include <xdc/std.h>
#include <string.h>

/* #include <ti/xdais/dm/ivicp2codec1.h>*/
#include <ti/sdo/fc/ires/examples/codecs/vicp2codec1/ivicp2codec1.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>

/* Header file for the resources used in this example. */
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>

#include "vicp2codec1_ti.h"
#include "vicp2codec1_ti_priv.h"

/* IRES Function Declarations */
static IRES_Status VICP2CODEC1_TI_activateRes(IALG_Handle handle, IRES_Handle res);
static IRES_Status VICP2CODEC1_TI_activateAllRes(IALG_Handle handle);
static IRES_Status VICP2CODEC1_TI_deactivateRes(IALG_Handle h, IRES_Handle res);
static IRES_Status VICP2CODEC1_TI_deactivateAllRes(IALG_Handle handle);
static Int32 VICP2CODEC1_TI_numResources(IALG_Handle handle);
static IRES_Status VICP2CODEC1_TI_getResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc);
static IRES_Status VICP2CODEC1_TI_initResources(IALG_Handle h,
        IRES_ResourceDescriptor * desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);
static IRES_Status VICP2CODEC1_TI_deInitResources(IALG_Handle h,
        IRES_ResourceDescriptor *desc);
static IRES_Status VICP2CODEC1_TI_reInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *desc, IRES_YieldFxn  yieldFxn,
        IRES_YieldArgs yieldArgs);
                
/*
 *  ======== VICP2CODEC1_TI_IRES ========
 */
IRES_Fxns VICP2CODEC1_TI_IRES = {
    &VICP2CODEC1_TI_IRES,
    VICP2CODEC1_TI_getResources,
    VICP2CODEC1_TI_numResources,
    VICP2CODEC1_TI_initResources,
    VICP2CODEC1_TI_reInitResources,
    VICP2CODEC1_TI_deInitResources,
    VICP2CODEC1_TI_activateRes,
    VICP2CODEC1_TI_activateAllRes,
    VICP2CODEC1_TI_deactivateRes,
    VICP2CODEC1_TI_deactivateAllRes
};


/*
 *  ======== VICP2CODEC1_TI_activateAllRes ========
 */
/* ARGSUSED */
static IRES_Status VICP2CODEC1_TI_activateAllRes(IALG_Handle handle)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)handle;
    IRES_Status      status;
    int i;

    for (i = 0; i < ALGNUM_RESOURCES; i++) {
    
        if (algHandle->resourceState[i] == 0) {
            algHandle->resourceState[i] = 1;
        }
        else {
            return (IRES_EINIT);
        }
    }
    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_activateRes ========
 */
static IRES_Status VICP2CODEC1_TI_activateRes(IALG_Handle handle, 
        IRES_Handle res)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)handle;
    int i;

    for (i = 0; i < ALGNUM_RESOURCES; i++) {
        if ((IRES_Handle)algHandle->resourceHandles[i] == res) {
            if (algHandle->resourceState[0] == 0) {
                algHandle->resourceState[0] = 1;
                return (IRES_OK);
            }
            else {
                return (IRES_EINIT);
            }

        }
    }
    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_deactivateAllRes ========
 */
static IRES_Status VICP2CODEC1_TI_deactivateAllRes(IALG_Handle handle) 
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)handle;
    IRES_Status      status = IRES_OK;
    int i;

    for (i = 0; i < ALGNUM_RESOURCES; i++) {
        if (algHandle->resourceState[i] == 1) {
            algHandle->resourceState[i] = 0;
        }
        else {
            return (IRES_ENORESOURCE);
        }
    }
    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_deactivateRes ========
 */
static IRES_Status VICP2CODEC1_TI_deactivateRes(IALG_Handle h, IRES_Handle res)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)h;
    int i;

    for (i = 0; i < ALGNUM_RESOURCES; i++) {
        if ((IRES_Handle)algHandle->resourceHandles[i] == res) {
            if (algHandle->resourceState[0] == 1) {
                algHandle->resourceState[0] = 0;
                return (IRES_OK);
            }
            else {
                return (IRES_ENORESOURCE);
            }
        }
    }
    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_deInitResources ========
 */
static IRES_Status VICP2CODEC1_TI_deInitResources(IALG_Handle handle,
        IRES_ResourceDescriptor *resourceDescriptor)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)handle;
    int i;


    for (i = 0; i < ALGNUM_VICPRESOURCES; i++) {
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] = (IRES_VICP2_Handle)NULL;
    }
        algHandle->grouputils = NULL;
    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_getResources ========
 */
static IRES_Status VICP2CODEC1_TI_getResources(IALG_Handle handle,
        IRES_ResourceDescriptor *resourceDescriptors)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)handle;
    Int i=0;
    unsigned int bufreq = 0x0;
    Int j = 0;

    for (i = 0; i < ALGNUM_VICPRESOURCES; i++) {

        bufreq = 0;
        resourceDescriptors[i].resourceName = IRES_VICP2_PROTOCOLNAME;
        resourceDescriptors[i].revision = &IRES_VICP2_PROTOCOLREVISION;
        algHandle->protocolArgs[i].size = sizeof(IRES_VICP2_ProtocolArgs);
        if (i == 0) {
            algHandle->protocolArgs[i].mode = IRES_SCRATCH; 
                    bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_A);
                    bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_B);
                    bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_D);
        }
        else {
            algHandle->protocolArgs[i].mode = IRES_LATEACQUIRE; 
                    /* Shared late acquire resources */
                    bufreq |= (0x1 << IMCOP_BUFFER_IMGBUF_C);
                    algHandle->protocolArgs[i].requestIMX1 = 1;
        }
       /* This is a request for NSF, will be ignored on DM355 */ 

        /* Request specific buffers */
        algHandle->protocolArgs[i].numMemoryRequests = 0;

        algHandle->protocolArgs[i].requestIMCOPBuffers = bufreq;

        resourceDescriptors[i].protocolArgs =
                    (IRES_ProtocolArgs *)&(algHandle->protocolArgs[i]);
        resourceDescriptors[i].handle = 
                (IRES_Handle)algHandle->resourceHandles[i];
    }

    resourceDescriptors[i].resourceName = IRES_GROUPUTILS_PROTOCOLNAME;
    resourceDescriptors[i].revision = &IRES_GROUPUTILS_PROTOCOLREVISION;
    algHandle->protocolArgs[i].size = sizeof(IRES_GROUPUTILS_ProtocolArgs);
    resourceDescriptors[i].protocolArgs =
                 (IRES_ProtocolArgs *)&(algHandle->grouputilsArgs);
    resourceDescriptors[i].handle = 
             (IRES_Handle)algHandle->grouputils;


    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_initResources ========
 */
/* ARGSUSED */
static IRES_Status VICP2CODEC1_TI_initResources(IALG_Handle h,
    IRES_ResourceDescriptor * resourceDescriptor, IRES_YieldFxn  yieldFxn,
    IRES_YieldArgs yieldArgs)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)h;
    Int i = 0;
    IRES_VICP2_Handle res;
    IRES_VICP2_Properties props;
    IRES_VICP2_ProtocolArgs * p;
    IRES_GROUPUTILS_Handle grouputils;    

    /* 
     * Resource manager has returned a resource handle. Save it in the 
     * algorithm's instance object 
     */ 

    algHandle->grouputils = ((IRES_GROUPUTILS_Handle)
            resourceDescriptor[2].handle);
    grouputils = algHandle->grouputils;

    for (i = 0; i < ALGNUM_VICPRESOURCES; i++) {
        res = ((IRES_VICP2_Handle)resourceDescriptor[i].handle);
        algHandle->resourceState[i] = 0;
        algHandle->resourceHandles[i] = res;

        res->ires.getStaticProperties((IRES_Handle)res, 
                (IRES_Properties *)&props);  

        p = (IRES_VICP2_ProtocolArgs *)(resourceDescriptor[i].protocolArgs); 

/*          result &= checkRes((IRES_ProtocolArgs *)p,(IRES_Handle)res);*/

    }
    return (IRES_OK);
}

/*
 *  ======== VICP2CODEC1_TI_numResources ========
 */
/* ARGSUSED */
static Int32 VICP2CODEC1_TI_numResources(IALG_Handle handle) 
{
    return (ALGNUM_RESOURCES);
}

/*
 *  ======== VICP2CODEC1_TI_reInitResources ========
 */
static IRES_Status VICP2CODEC1_TI_reInitResources(IALG_Handle handle,
    IRES_ResourceDescriptor * resourceDescriptor,
    IRES_YieldFxn  yieldFxn, IRES_YieldArgs yieldArgs)
{
    VICP2CODEC1_TI_Obj  *algHandle = (VICP2CODEC1_TI_Obj *)handle;
    IRES_Status status = IRES_OK;
    int i;

    /* 
     * This function implies that the resource holdings of the algorithms have
     * been changed.
     * Update them in the algorithm instance object. 
     */
    
    for (i = 0; i < ALGNUM_RESOURCES; i++) {
        algHandle->resourceState[i] = 0;
    }
    status = VICP2CODEC1_TI_initResources(handle, resourceDescriptor, yieldFxn, 
                yieldArgs);

    return (status);
}

/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.vicp2codec1; 1, 0, 0,32; 12-1-2010 17:25:11; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

