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
 *  ======== iresman_sdma.c ========
 *  Template file that implements an abstract resource manager for IRES
 *  resources.
 */

#include <xdc/std.h>

#include <ti/sdo/linuxutils/sdma/include/sdma.h>

/*
 * Define this, before including ires_<>.h, as that checks for this
 * define to avoid multiple inclusion of the static Protocol Version definition
 * of IRES_<>_PROTOCOLREVISION from the header file.
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_sdma.h"
#include "ires_sdma.h"
#include "_sdma.h"
#include "iresman_protocol_sdma.h"

#include <ti/sdo/utils/trace/gt.h>

GT_Mask ti_sdo_fc_ires_sdma_GTMask;
static Int _SDMA_gtInit = 0;

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_SDMA_InternalState {

    IRESMAN_PersistentAllocFxn * allocFxn;      /* Memory allocation Function */
    IRESMAN_PersistentFreeFxn * freeFxn;        /* Memory free Function */
} IRESMAN_SDMA_InternalState;

/*
 * Flag indicating if the resource manager is initialized
 */
static unsigned int _initialized = 0;

/*
 * Represents the IRES EDMA3 Resource manager
 */
static IRESMAN_SDMA_InternalState _resmanInternalState;

/*
 *  ======== IRESMAN_SDMA_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_SDMA_getProtocolName()
{
    if (_SDMA_gtInit == 0 ) {

        GT_init();
        GT_create(&ti_sdo_fc_ires_sdma_GTMask, "ti.sdo.fc.ires.sdma");

        _SDMA_gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_getProtocolName> Enter\n");

    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_getProtocolName> Exit (Name=%s)\n",
            IRESMAN_SDMA_CONSTRUCTFXNS.getName());

    return (IRESMAN_SDMA_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_SDMA_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_SDMA_getProtocolRevision()
{

#if (GT_TRACE == 1)
    IRES_ProtocolRevision * version;
#endif

    if (_SDMA_gtInit == 0 ) {

        GT_init();
        GT_create(&ti_sdo_fc_ires_sdma_GTMask, "ti.sdo.fc.ires.sdma");

        _SDMA_gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_getProtocolRevision> Enter\n");

#if (GT_TRACE == 1)
    version = IRESMAN_SDMA_CONSTRUCTFXNS.getRevision();
#endif

    GT_3trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_getProtocolRevision> Exit (Version=(%d.%d.%d))\n",
            version->Major, version->Source, version->Radius);

    return (IRESMAN_SDMA_CONSTRUCTFXNS.getRevision());
}

/*
 *  ======== IRESMAN_SDMA_init ========
 *  Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_SDMA_init(IRESMAN_Params * initArgs)
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
{

    IRESMAN_SdmaParams * resmanArgs = (IRESMAN_SdmaParams *)initArgs;

    if (_SDMA_gtInit == 0 ) {

        GT_init();
        GT_create(&ti_sdo_fc_ires_sdma_GTMask, "ti.sdo.fc.ires.sdma");

        _SDMA_gtInit = 1;
    }

    GT_assert(ti_sdo_fc_ires_sdma, initArgs != NULL);

    /*  Check if already initialized */
    if (_initialized) {
        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
                "_IRESMAN_SDMA_init> Exit (status=IRES_EEXISTS)\n");

       return (IRES_EEXISTS);
    }

    GT_1trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_init> Enter (initArgs=0x%x)\n", initArgs);

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _resmanInternalState.allocFxn = resmanArgs->baseConfig.allocFxn;
    _resmanInternalState.freeFxn = resmanArgs->baseConfig.freeFxn;

    if (0 != SDMA_init()) {
        return (IRES_EFAIL);
    }

    /* Set Initalized flag to 1 if successful */
     _initialized = 1;

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_init> Exit (status=IRES_OK)\n");

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_SDMA_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_SDMA_exit()
{
    /* Check if initialized */
    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_exit> Enter \n");

    if (!(_initialized)) {

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
                "_IRESMAN_SDMA_exit> Exit (status=IRES_ENOINIT)\n");

        return (IRES_ENOINIT);
    }

    /*
     * Free up any memory that might be allocated in this module
     * Basically memory that has been used by the protocol implementation
     */

    if (0 != SDMA_exit()) {
        return (IRES_EFAIL);
    }

    /* Set the initialized flag to zero again */
    _initialized = 0;

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_exit> Exit (status=IRES_OK)\n");

    GT_exit();

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_SDMA_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_SDMA_getHandles( IALG_Handle algHandle,
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec resourceMemRecs[1];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    IRES_SDMA_ConstructHandleArgs * constructArgs;

    GT_2trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId);

    GT_assert(ti_sdo_fc_ires_sdma_GTMask, protocolArgs);

    if (_initialized != 1) {
        *status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRESMAN_SDMA_getHandles> RMAN register for SDMA "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (NULL);
    }

    numMemRecs = IRESMAN_SDMA_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_SDMA_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRES_SDMA_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_ESDATA;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == _resmanInternalState.allocFxn(&constructHandleMemRec, 1)) {

        GT_2trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRESMAN_SDMA_getHandles> Error allocating memory for "
                "construct args of size 0x%x, alignment 0x%x, space IALG_ESDATA"
                ", attrs IALG_PERSIST\n", constructHandleMemRec.size,
                constructHandleMemRec.alignment);

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
                "_IRESMAN_SDMA_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        *status = IRES_ENOMEM;
        return (NULL);
    }

    constructArgs = constructHandleMemRec.base;


    /* Supports only Persistent resources */
    constructArgs->persistent = TRUE;

    if (FALSE == _resmanInternalState.allocFxn(resourceMemRecs, numMemRecs)) {

        GT_2trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRESMAN_SDMA_getHandles> Error allocating memory for "
                "resource handle of size 0x%x, alignment 0x%x, space "
                "IALG_ESDATA, attrs IALG_PERSIST\n", resourceMemRecs->size,
                resourceMemRecs->alignment);

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
                "_IRESMAN_SDMA_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        *status = IRES_ENOMEM;
        return (NULL);

    }

    /*
     * Use IRES_SDMA_RESOURCEPROTOCOL to init the resource protocol
     * if required
     */
    resourceHandle = IRESMAN_SDMA_CONSTRUCTFXNS.constructHandle(
            protocolArgs, resourceMemRecs,
            (IRESMAN_ConstructArgs *)constructArgs, status);

    /* Populate logicalChannel with information about chnnel obtained  */
    if (SDMA_OK != SDMA_getChannels(1,
            ((IRES_SDMA_Handle)resourceHandle)->channel)) {

        *status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRESMAN_SDMA_getHandles> SDMA library did not successfully "
                "return requested resources. \n");

        /* Free resource handle memory */
        _resmanInternalState.freeFxn(resourceMemRecs, numMemRecs);
    }

    /*
     * Free the memory for the handles
     */
    _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

    GT_2trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_getHandles> Exit (status=%d, "
            "resourceHandle=0x%x)\n", *status, resourceHandle);

    return (resourceHandle);
}

/*
 *  ======== IRESMAN_SDMA_freeHandle ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_SDMA_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ProtocolArgs * protocolArgs,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[1];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    IRES_SDMA_Handle resHandle = (IRES_SDMA_Handle)algResourceHandle;

    GT_assert(ti_sdo_fc_ires_sdma_GTMask, protocolArgs);
    GT_assert(ti_sdo_fc_ires_sdma_GTMask, algResourceHandle);

    GT_3trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_freeHandles> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle,
            protocolArgs, scratchGroupId);

    if (_initialized != 1) {
        status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRESMAN_SDMA_getHandles> RMAN register for SDMA "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (status);
    }

    if (SDMA_OK != SDMA_freeChannels(1, resHandle->channel)) {

        status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_7CLASS,
                "_IRESMAN_SDMA_getHandles> SDMA library did not successfully "
                "free requested resources. \n");

        return (status);

    }

    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_SDMA_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_SDMA_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    /* Set Base address of Memory location to free */
    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_SDMA_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_SDMA_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _resmanInternalState.freeFxn(resourceMemRecs, numMemRecs);

    GT_0trace(ti_sdo_fc_ires_sdma_GTMask, GT_ENTER,
            "_IRESMAN_SDMA_freeHandles> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

IRESMAN_Fxns IRESMAN_SDMA =  {
    IRESMAN_SDMA_getProtocolName,
    IRESMAN_SDMA_getProtocolRevision,
    IRESMAN_SDMA_init,
    IRESMAN_SDMA_exit,
    IRESMAN_SDMA_getHandles,
    IRESMAN_SDMA_freeHandle
};

IRESMAN_SdmaParams IRESMAN_SDMA_DEFAULTPARAM;

IRESMAN_Fxns * SDMA_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_SDMA));
}


IRESMAN_Params * SDMA_getDefaultParams()
{
    IRESMAN_SDMA_DEFAULTPARAM.baseConfig.size = 
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_SDMA_DEFAULTPARAM);
}
/*
 *  @(#) ti.sdo.fc.ires.sdma; 1, 0, 0,132; 12-1-2010 17:25:22; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

