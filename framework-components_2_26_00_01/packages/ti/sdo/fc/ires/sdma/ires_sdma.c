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
 *  ======== ires_sdma.c ========
 *  Template file that demonstrates the construction of the IRES handle for
 *  a resource once it has been allocated by the iresman_<>.c file
 *  The handle created here is returned to the algorithm.
 */

#include <xdc/std.h>

#include "ires_sdma.h"
#include "iresman_protocol_sdma.h"
#include "_sdma.h"

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_ires_sdma_GTMask;

extern void IRES_SDMA_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties);

/*
 * Holds the internal state of the protocol
 */
/*  static IRES_SDMA_InternalState internalState;*/


/**
 *  ======= IRES_SDMA_getProtocolName =======
 *  Return the name of the protocol
 */
String IRES_SDMA_getName()
{
    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getName> Enter\n");

    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getName> Exit (Name=%s)\n",
            IRES_SDMA_PROTOCOLNAME);

    return (IRES_SDMA_PROTOCOLNAME);
}


/**
 *  ======= IRES_SDMA_getRevision =======
 *  Return the revision of the protocol
 */
IRES_ProtocolRevision * IRES_SDMA_getRevision ()
{
    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getRevision> Enter\n");

    GT_3trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getRevision> Exit (Version=(%d.%d.%d))\n",
            IRES_SDMA_PROTOCOLREVISION.Major,
            IRES_SDMA_PROTOCOLREVISION.Source,
            IRES_SDMA_PROTOCOLREVISION.Radius);

    return (&IRES_SDMA_PROTOCOLREVISION);
}

/**
 *  ======= IRES_SDMA_getMemRecs =======
 *  Provide the memory requirements for allocating the Logical Resource
 *  handle.
 *
 *  The 'protocol' determines the size and attributes of the memory that
 *  represents the logical resource. The size must be at least the size of
 *  IRES_SDMA_Obj.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_SDMA_getMemRecs(IRES_Handle handle,
        IRES_ProtocolArgs * resProtocolArgs, IALG_MemRec *memRecs)
{

    GT_3trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getMemRecs> Enter (handle=0x%x, "
            "resProtocolArgs=0x%x, memRecs=0x%x)\n", handle, resProtocolArgs,
            memRecs);

    GT_assert(ti_sdo_fc_ires_sdma_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_sdma_GTMask, resProtocolArgs != NULL);

    memRecs[0].alignment = 4;

    /*
     * IALG_EXTERNAL because we don't care where this memory is allocated
     */
    memRecs[0].space = IALG_ESDATA;

    /*
     * Memory should be persistent.
     */
    memRecs[0].attrs = IALG_PERSIST;

    /*
     * Size of this handle depends on number of Logical Channels requested
     */
    memRecs[0].size = (sizeof(IRES_SDMA_Obj) + sizeof(SDMA_ChannelDescriptor));

    GT_2trace(ti_sdo_fc_ires_sdma_GTMask, GT_4CLASS,
            "_IRES_SDMA_getMemRecs> Requesting memory of size 0x%x, "
            "alignment 0x%x, space IALG_ESDATA, attrs IALG_PERSIST)\n",
            memRecs[0].size, memRecs[0].alignment);

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getMemRecs> Exit (status=IRES_OK)\n" );

    return (IRES_OK); /* number of MemRecs */
}

/**
 *  ======= IRES_SDMA_getNumMemRecs =======
 *  SDMA protocol does not request any extra memory buffers.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int IRES_SDMA_getNumMemRecs(IRES_ProtocolArgs * protArgs)
{
    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getNumMemRecs> Enter (protArgs=0x%x)\n", protArgs);

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getNumMemRecs> Exit (Num=1)\n" );

    return ((Int)1);
}

/**
 *  ======= IRES_SDMA_constructHandle =======
 *  SDMA Protocol specific initialization function to finalize the
 *  creation of a resource object (handle).
 *  The protocol::initHandle function can extend the IRES_SDMA_Obj struct
 *  and must store any additional allocated 'environment' memory
 *  within the resource handle and return the IALG_MemRec descriptors
 *  in protocol::getEnvBuffDescriptors() function.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRES_SDMA_constructHandle(
        IRES_ProtocolArgs * resProtocolArgs,
        IALG_MemRec *memRecs,
        IRESMAN_ConstructArgs * constructHandleArgs,
        IRES_Status *status)
{
    IRES_SDMA_Handle handle = (IRES_SDMA_Handle)memRecs[0].base;

    IRES_SDMA_ConstructHandleArgs * constructArgs =
        (IRES_SDMA_ConstructHandleArgs *)constructHandleArgs;

    GT_3trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_constructHandle> Enter (resProtcolArgs=0x%x, "
            "memRecs=0x%x, constructHandleArgs=0x%x)\n", resProtocolArgs,
            memRecs, constructHandleArgs);

    GT_assert(ti_sdo_fc_ires_sdma_GTMask, resProtocolArgs != NULL);
    GT_assert(ti_sdo_fc_ires_sdma_GTMask, memRecs != NULL);
    GT_assert(ti_sdo_fc_ires_sdma_GTMask, constructHandleArgs != NULL);
    GT_assert(ti_sdo_fc_ires_sdma_GTMask, status != NULL);

    if (handle == NULL) {

        *status = IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRES_SDMA_constructHandle> NULL handle passed in "
                "memRecs[0].base\n");

        GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
                "_IRES_SDMA_constructHandle> Exit (handle=0x%x, "
                "status=IRES_ENORESOURCE)\n", handle);

        return ((IRES_Handle) NULL);
    }

    ((IRES_SDMA_Handle)handle)->ires.getStaticProperties =
            IRES_SDMA_getStaticProperties;

    /*
     * Use the constructHandleargs to populate the handle
     */
    handle->channel = (SDMA_ChannelDescriptor *)
            (handle + sizeof(IRES_SDMA_Obj));

    handle->ires.persistent = constructArgs->persistent;

    *status = IRES_OK;

    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_constructHandle> Exit (handle=0x%x, "
            "status=IRES_OK)\n", handle);

    return ((IRES_Handle)handle);
}

/**
 *  ======= IRES_SDMA_getStaticProperties =======
 *  Returns the static properties of the particular resource
 */
void IRES_SDMA_getStaticProperties(IRES_Handle resourceHandle,
        IRES_Properties * resourceProperties)
{
    IRES_SDMA_Properties * properties =
            (IRES_SDMA_Properties *)resourceProperties;

    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getStaticProperties> Enter (handle=0x%x)\n",
            resourceHandle);

    properties->globalRegs = (IRES_SDMA_RegisterLayer *)
            (((IRES_SDMA_Handle)(resourceHandle))->channel->addr);


    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_getStaticProperties> Exit (resourceProperties=0x%x)"
            "\n", resourceProperties);
}

/**
 *  ======= IRES_SDMA_destructHandle =======
 *  De-initialize the env stored in the IRES_SDMA channel handle, before
 *  it is freed by the resource manager.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRES_SDMA_destructHandle(IRES_Handle handle)
{
    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_destructHandle> Enter (handle=0x%x)\n", handle);

    /*
     * Nothing allocated in this module
     * So nothing needs to be done.
     */
    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRES_SDMA_destructHandle> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

IRESMAN_ConstructFxns IRESMAN_SDMA_CONSTRUCTFXNS = {
    IRES_SDMA_getName,
    IRES_SDMA_getRevision,
    IRES_SDMA_getMemRecs,
    IRES_SDMA_getNumMemRecs,
    IRES_SDMA_constructHandle,
    IRES_SDMA_destructHandle
};
/*
 *  @(#) ti.sdo.fc.ires.sdma; 1, 0, 0,132; 12-1-2010 17:25:22; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

