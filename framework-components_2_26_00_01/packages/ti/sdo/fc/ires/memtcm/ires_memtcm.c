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
 *  ======== ires_memtcm.c ========
 *  Template file that demonstrates the construction of the IRES handle for   
 *  a resource once it has been allocated by the iresman_<>.c file
 *  The handle created here is returned to the algorithm. 
 */

#include <xdc/std.h>
#include "ires_memtcm.h"
#include "iresman_protocol_memtcm.h"
#include "_memtcm.h"

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_ires_memtcm_GTMask;

extern void IRES_MEMTCM_getStaticProperties(IRES_Handle resourceHandle, 
        IRES_Properties * resourceProperties);

/*
 * Holds the internal state of the protocol
static IRES_MEMTCM_InternalState internalState;
*/


/**
 *  ======= IRES_MEMTCM_getProtocolName =======
 *  Return the name of the protocol 
 */
String IRES_MEMTCM_getName()
{
    GT_0trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getName> Enter \n");

    GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getName> Exit (Name=%s)\n", 
            IRES_MEMTCM_PROTOCOLNAME);

    return (IRES_MEMTCM_PROTOCOLNAME);
}


/**
 *  ======= IRES_MEMTCM_getRevision =======
 *  Return the revision of the protocol 
 */
IRES_ProtocolRevision * IRES_MEMTCM_getRevision ()
{
    GT_0trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getRevision> Enter\n");
    
    GT_3trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getRevision> Exit (Version=(%d.%d.%d))\n", 
            IRES_MEMTCM_PROTOCOLREVISION.Major, 
            IRES_MEMTCM_PROTOCOLREVISION.Source,
            IRES_MEMTCM_PROTOCOLREVISION.Radius);

    return (&IRES_MEMTCM_PROTOCOLREVISION);
}

/**
 *  ======= IRES_MEMTCM_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle. 
 *
 *  The 'protocol' determines the size and attributes of the memory that 
 *  represents the logical resource. The size must be at least the size of 
 *  IRES_MEMTCM_Obj. 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_MEMTCM_getMemRecs(IRES_Handle handle, 
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{
    /*
    IRES_MEMTCM_ProtocolArgs * protocolArgs = 
            (IRES_MEMTCM_ProtocolArgs *)resProtocolArgs;
    */

    GT_3trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)\n", handle, resProtocolArgs, 
            memRecs);
    
    GT_assert(ti_sdo_fc_ires_memtcm_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_memtcm_GTMask, resProtocolArgs != NULL);

    memRecs[0].alignment = 4;

    memRecs[0].size = sizeof(IRES_MEMTCM_Obj);

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_ESDATA;

    /*
     * Memory should be persistent. 
     */
    memRecs[0].attrs = IALG_PERSIST;

    GT_2trace(ti_sdo_fc_ires_memtcm_GTMask, GT_4CLASS, 
            "_IRES_MEMTCM_getMemRecs> Requesting memory of size 0x%x, "
            "alignment 0x%x, space IALG_ESDATA, attrs IALG_PERSIST)\n", 
            memRecs[0].size, memRecs[0].alignment);

    GT_0trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getMemRecs> Exit (status=IRES_OK)\n" );

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_MEMTCM_getNumMemRecs =======
 *  MEMTCM protocol does not request any extra memory buffers. 
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_MEMTCM_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getNumMemRecs> Enter (protArgs=0x%x)\n", protArgs);

    GT_0trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getNumMemRecs> Exit (Num=1)\n" );

    return ((Int)1);
}
    
/**
 *  ======= IRES_MEMTCM_constructHandle =======
 *  MEMTCM Protocol specific initialization function to finalize the 
 *  creation of a resource object (handle). 
 *  The protocol::initHandle function can extend the IRES_MEMTCM_Obj struct
 *  and must store any additional allocated 'environment' memory 
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_MEMTCM_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs, 
        IALG_MemRec *memRecs, 
        IRESMAN_ConstructArgs * constructHandleArgs, 
        IRES_Status *status)
{
    IRES_MEMTCM_Handle handle = (IRES_MEMTCM_Handle)memRecs[0].base;

    IRES_MEMTCM_ConstructHandleArgs * constructArgs =
        (IRES_MEMTCM_ConstructHandleArgs *)constructHandleArgs;

    GT_3trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_constructHandle> Enter (resProtcolArgs=0x%x, "
            "memRecs=0x%x, constructHandleArgs=0x%x)\n", resProtocolArgs, 
            memRecs, constructHandleArgs);

    GT_assert(ti_sdo_fc_ires_memtcm_GTMask, resProtocolArgs != NULL);
    GT_assert(ti_sdo_fc_ires_memtcm_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_memtcm_GTMask, constructHandleArgs != NULL);
    GT_assert(ti_sdo_fc_ires_memtcm_GTMask, status != NULL);
    
    if (handle == NULL) {
        *status = IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_memtcm_GTMask, GT_7CLASS, 
                "_IRES_MEMTCM_constructHandle> NULL handle passed in "
                "memRecs[0].base\n");

        GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
                "_IRES_MEMTCM_constructHandle> Exit (handle=0x%x, "
                "status=IRES_ENORESOURCE)\n", handle);

        return ((IRES_Handle) NULL);
    }

    handle->ires.persistent = constructArgs->persistent;

    handle->memSize = constructArgs->memSize;

    handle->memAddr = constructArgs->memAddr; 

    ((IRES_MEMTCM_Handle)handle)->ires.getStaticProperties = 
            IRES_MEMTCM_getStaticProperties;                

    *status = IRES_OK;

    GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_constructHandle> Exit (handle=0x%x, "
            "status=IRES_OK)\n", handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_MEMTCM_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
void IRES_MEMTCM_getStaticProperties(IRES_Handle resourceHandle, 
        IRES_Properties * resourceProperties)
{
    /*
    IRES_MEMTCM_Properties * properties = 
            (IRES_MEMTCM_Properties *)resourceProperties;
    */

    GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getStaticProperties> Enter (handle=0x%x)\n", 
            resourceHandle);

    GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_getStaticProperties> Exit (resourceProperties=0x%x)"
            "\n", resourceProperties);
}

/**
 *  ======= IRES_MEMTCM_destructHandle =======
 *  De-initialize the env stored in the IRES_MEMTCM channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_MEMTCM_destructHandle(IRES_Handle handle)
{
    GT_1trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_destructHandle> Enter (handle=0x%x)\n", handle);

    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    GT_0trace(ti_sdo_fc_ires_memtcm_GTMask, GT_ENTER, 
            "_IRES_MEMTCM_destructHandle> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_MEMTCM_CONSTRUCTFXNS = {
    IRES_MEMTCM_getName, 
    IRES_MEMTCM_getRevision, 
    IRES_MEMTCM_getMemRecs,
    IRES_MEMTCM_getNumMemRecs,
    IRES_MEMTCM_constructHandle,
    IRES_MEMTCM_destructHandle
};
/*
 *  @(#) ti.sdo.fc.ires.memtcm; 1, 0, 0,45; 12-1-2010 17:25:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

