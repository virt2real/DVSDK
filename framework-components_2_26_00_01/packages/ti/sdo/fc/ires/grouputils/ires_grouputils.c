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
 *  ======== ires_grouputils.c ========
 *  Template file that demonstrates the construction of the IRES handle for   
 *  a resource once it has been allocated by the iresman_<>.c file
 *  The handle created here is returned to the algorithm. 
 */

#include <xdc/std.h>
#include "ires_grouputils.h"
#include "iresman_protocol_grouputils.h"
#include "_grouputils.h"

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_ires_grouputils_GTMask;
#define CURTRACE ti_sdo_fc_ires_grouputils_GTMask

extern void IRES_GROUPUTILS_getStaticProperties(IRES_Handle resourceHandle, 
        IRES_Properties * resourceProperties);

extern ti_sdo_fc_ires_grouputils_LockFxn ti_sdo_fc_ires_grouputils_lockGroup;
extern ti_sdo_fc_ires_grouputils_LockFxn ti_sdo_fc_ires_grouputils_unlockGroup;

extern __FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemCreateFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semCreateFxn;
extern __FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemDeleteFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semDeleteFxn;
extern __FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPendFxn  
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semPendFxn;
extern __FAR__ ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPostFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semPostFxn;

/*
 * Holds the internal state of the protocol
static IRES_GROUPUTILS_InternalState internalState;
*/

static SemMP_Handle _GROUPUTILS_sem = NULL; 

static IALG_Handle currentAlg = NULL;


static IRES_Status lockScratchGroup(IALG_Handle alg, IRES_GROUPUTILS_Handle h); 

static IRES_Status unlockScratchGroup(IALG_Handle alg, IRES_GROUPUTILS_Handle h);

static IRES_Status lockLateAcquireResources(IALG_Handle alg, 
        IRES_GROUPUTILS_Handle h);

static IRES_Status unlockLateAcquireResources(IALG_Handle alg, 
        IRES_GROUPUTILS_Handle h);

/**
 *  ======= IRES_GROUPUTILS_getProtocolName =======
 *  Return the name of the protocol 
 */
String IRES_GROUPUTILS_getName()
{
    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getName> Enter \n");

    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getName> Exit (Name=%s)\n", 
            IRES_GROUPUTILS_PROTOCOLNAME);

    return (IRES_GROUPUTILS_PROTOCOLNAME);
}


/**
 *  ======= IRES_GROUPUTILS_getRevision =======
 *  Return the revision of the protocol 
 */
IRES_ProtocolRevision * IRES_GROUPUTILS_getRevision ()
{
    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getRevision> Enter\n");
    
    GT_3trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getRevision> Exit (Version=(%d.%d.%d))\n", 
            IRES_GROUPUTILS_PROTOCOLREVISION.Major, 
            IRES_GROUPUTILS_PROTOCOLREVISION.Source,
            IRES_GROUPUTILS_PROTOCOLREVISION.Radius);

    return (&IRES_GROUPUTILS_PROTOCOLREVISION);
}

/**
 *  ======= IRES_GROUPUTILS_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle. 
 *
 *  The 'protocol' determines the size and attributes of the memory that 
 *  represents the logical resource. The size must be at least the size of 
 *  IRES_GROUPUTILS_Obj. 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_GROUPUTILS_getMemRecs(IRES_Handle handle, 
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{
    /*
    IRES_GROUPUTILS_ProtocolArgs * protocolArgs = 
            (IRES_GROUPUTILS_ProtocolArgs *)resProtocolArgs;
    */

    GT_3trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)\n", handle, resProtocolArgs, 
            memRecs);
    
    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, resProtocolArgs != NULL);

    memRecs[0].alignment = 4;

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_ESDATA;

    /*
     * Memory should be persistent. 
     */
    memRecs[0].attrs = IALG_PERSIST;

    memRecs[0].size = sizeof(IRES_GROUPUTILS_IntObj);

    GT_2trace(ti_sdo_fc_ires_grouputils_GTMask, GT_4CLASS, 
            "_IRES_GROUPUTILS_getMemRecs> Requesting memory of size 0x%x, "
            "alignment 0x%x, space IALG_ESDATA, attrs IALG_PERSIST)\n", 
            memRecs[0].size, memRecs[0].alignment);

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getMemRecs> Exit (status=IRES_OK)\n" );

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_GROUPUTILS_getNumMemRecs =======
 *  GROUPUTILS protocol does not request any extra memory buffers. 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_GROUPUTILS_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getNumMemRecs> Enter (protArgs=0x%x)\n", protArgs);

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getNumMemRecs> Exit (Num=1)\n" );

    return ((Int)1);
}
    
/**
 *  ======= IRES_GROUPUTILS_constructHandle =======
 *  GROUPUTILS Protocol specific initialization function to finalize the 
 *  creation of a resource object (handle). 
 *  The protocol::initHandle function can extend the IRES_GROUPUTILS_Obj struct
 *  and must store any additional allocated 'environment' memory 
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_GROUPUTILS_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs, 
        IALG_MemRec *memRecs, 
        IRESMAN_ConstructArgs * constructHandleArgs, 
        IRES_Status *status)
{
    IRES_GROUPUTILS_Handle handle = (IRES_GROUPUTILS_Handle)memRecs[0].base;

    IRES_GROUPUTILS_ConstructHandleArgs * constructArgs =
        (IRES_GROUPUTILS_ConstructHandleArgs *)constructHandleArgs;

    GT_3trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "IRES_GROUPUTILS_constructHandle> Enter (resProtcolArgs=0x%x, "
            "memRecs=0x%x, constructHandleArgs=0x%x)\n", resProtocolArgs, 
            memRecs, constructHandleArgs);

    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, resProtocolArgs != NULL);
    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, constructHandleArgs != NULL);
    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, status != NULL);
    
    if (handle == NULL) {
        *status = IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_7CLASS, 
                "IRES_GROUPUTILS_constructHandle> NULL handle passed in "
                "memRecs[0].base\n");

        GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
                "IRES_GROUPUTILS_constructHandle> Exit (handle=0x%x, "
                "status=IRES_ENORESOURCE)\n", handle);

        return ((IRES_Handle) NULL);
    }

    if (NULL == _GROUPUTILS_sem) {
        _GROUPUTILS_sem = constructArgs->sem;
    }    

    handle->reacquireGroupLock = lockScratchGroup; 

    handle->releaseGroupLock = unlockScratchGroup; 

    handle->lockLateAcquireResources = lockLateAcquireResources; 

    handle->unlockLateAcquireResources = unlockLateAcquireResources;

    ((IRES_GROUPUTILS_IntObj *)handle)->scratchId = constructArgs->scratchId; 

    ((IRES_GROUPUTILS_Handle)handle)->ires.getStaticProperties = 
            IRES_GROUPUTILS_getStaticProperties;                
    *status = IRES_OK;

    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "IRES_GROUPUTILS_constructHandle> Exit (handle=0x%x, "
            "status=IRES_OK)\n", handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_GROUPUTILS_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_GROUPUTILS_getStaticProperties(IRES_Handle resourceHandle, 
        IRES_Properties * resourceProperties)
{
    /*
    IRES_GROUPUTILS_Properties * properties = 
            (IRES_GROUPUTILS_Properties *)resourceProperties;
    */

    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getStaticProperties> Enter (handle=0x%x)\n", 
            resourceHandle);

    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_getStaticProperties> Exit (resourceProperties=0x%x)"
            "\n", resourceProperties);
}

/**
 *  ======= IRES_GROUPUTILS_destructHandle =======
 *  De-initialize the env stored in the IRES_GROUPUTILS channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_GROUPUTILS_destructHandle(IRES_Handle handle)
{
    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_destructHandle> Enter (handle=0x%x)\n", handle);

    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRES_GROUPUTILS_destructHandle> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

static IRES_Status lockScratchGroup(IALG_Handle alg, 
        IRES_GROUPUTILS_Handle handle)     
{
    Int scratchId = ((IRES_GROUPUTILS_IntObj *)handle)->scratchId; 

    if (NULL == ti_sdo_fc_ires_grouputils_lockGroup) {

        GT_0trace(CURTRACE, GT_7CLASS, "lockScratchGroup> No implementation "
                "of lockScratchGroupFxn/unlockScratchGroupFxn supplied via "
                "  configuration.");

        return (IRES_EFAIL);
    }

    /* Functional layer returned as part of the object */
    (ti_sdo_fc_ires_grouputils_lockGroup)(scratchId, alg);

    return (IRES_OK); 
}

static IRES_Status unlockScratchGroup(IALG_Handle alg, 
        IRES_GROUPUTILS_Handle handle)
{

    Int scratchId = ((IRES_GROUPUTILS_IntObj *)handle)->scratchId; 

    if (NULL == ti_sdo_fc_ires_grouputils_unlockGroup) {

        GT_0trace(CURTRACE, GT_7CLASS, "unlockScratchGroup> No implementation "
                "of lockScratchGroupFxn/unlockScratchGroupFxn supplied via "
                "  configuration.");

        return (IRES_EFAIL);
    }

    (ti_sdo_fc_ires_grouputils_unlockGroup)(scratchId, alg);

    return (IRES_OK);
}

/* Probably don't need the scratch group lock either ?! */
static IRES_Status lockLateAcquireResources(IALG_Handle alg,
        IRES_GROUPUTILS_Handle h)
{
    Int returnval = 0;
    if (currentAlg != NULL) {
        //some issue with algorithm usage
        return (IRES_EALG);
    }
    returnval = 
        (*ti_sdo_fc_ires_grouputils_GROUPUTILS_semPendFxn)(_GROUPUTILS_sem, -1);
    if (0 != returnval) {
        return (IRES_EFAIL);
    } 
    currentAlg = alg; 
    return (IRES_OK);
}

static IRES_Status unlockLateAcquireResources(IALG_Handle alg, 
        IRES_GROUPUTILS_Handle h)
{
    if (alg != currentAlg) {
        //Some issue with algorithm usage 
        return (IRES_EALG);
    }

    currentAlg = NULL;
    (*ti_sdo_fc_ires_grouputils_GROUPUTILS_semPostFxn)(_GROUPUTILS_sem);
    return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_GROUPUTILS_CONSTRUCTFXNS = {
    IRES_GROUPUTILS_getName, 
    IRES_GROUPUTILS_getRevision, 
    IRES_GROUPUTILS_getMemRecs,
    IRES_GROUPUTILS_getNumMemRecs,
    IRES_GROUPUTILS_constructHandle,
    IRES_GROUPUTILS_destructHandle
};


/*
 *  @(#) ti.sdo.fc.ires.grouputils; 1, 0, 0,32; 12-1-2010 17:25:14; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

