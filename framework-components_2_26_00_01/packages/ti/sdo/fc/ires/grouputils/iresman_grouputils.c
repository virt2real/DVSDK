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
 *  ======== iresman_grouputils.c ========
 *  Template file that implements an abstract resource manager for IRES 
 *  resources.
 */

#include <xdc/std.h>

/*
 * Define this, before including ires_<>.h, as that checks for this 
 * define to avoid multiple inclusion of the static Protocol Version definition
 * of IRES_<>_PROTOCOLREVISION from the header file. 
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_grouputils.h"
#include "ires_grouputils.h"
#include "iresman_protocol_grouputils.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_ires_grouputils_GTMask;

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_GROUPUTILS_InternalState {

    IRESMAN_PersistentAllocFxn * allocFxn;      /* Memory allocation Function */
    IRESMAN_PersistentFreeFxn * freeFxn;        /* Memory free Function */ 
} IRESMAN_GROUPUTILS_InternalState;

extern ti_sdo_fc_ires_grouputils_GROUPUTILS_SemCreateFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semCreateFxn;
extern ti_sdo_fc_ires_grouputils_GROUPUTILS_SemDeleteFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semDeleteFxn;
extern ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPendFxn  
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semPendFxn;
extern ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPostFxn 
        ti_sdo_fc_ires_grouputils_GROUPUTILS_semPostFxn;


/*
 * Flag indicating if the resource manager is initialized
 */
static unsigned int _initialized = 0;


/*
 * Flag indicating if gt has been initialized 
 */
static int gtInit = 0;

/*
 * Represents the IRES EDMA3 Resource manager
 */
static IRESMAN_GROUPUTILS_InternalState _resmanInternalState;

/*
 * Controls access to the late acquired resources 
 */
static GROUPUTILS_SemHandle _GROUPUTILS_sem = NULL;

/*
 *  ======== IRESMAN_GROUPUTILS_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_GROUPUTILS_getProtocolName()
{
    if (gtInit == 0) {

        GT_init();

        GT_create(&ti_sdo_fc_ires_grouputils_GTMask, "ti.sdo.fc.ires.grouputils");
    
        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_getProtocolName> Enter\n");

    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_getProtocolName> Exit (Name=%s)\n", 
            IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getName());

    return (IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_GROUPUTILS_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_GROUPUTILS_getProtocolRevision()
{

#if (GT_TRACE == 1)
    IRES_ProtocolRevision * version;
#endif

    if (gtInit == 0) {

        GT_init();

        GT_create(&ti_sdo_fc_ires_grouputils_GTMask, "ti.sdo.fc.ires.grouputils");
    
        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_getProtocolRevision> Enter\n");

#if (GT_TRACE == 1)
    version = IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getRevision();
#endif
        
    GT_3trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_getProtocolRevision> Exit (Version=(%d.%d.%d))\n"            , version->Major, version->Source, version->Radius);

    return (IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getRevision());
}

/*
 *  ======== IRESMAN_GROUPUTILS_init ========
 *  Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_GROUPUTILS_init(IRESMAN_Params * initArgs) 
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
{

    IRESMAN_TempLateParams * resmanArgs = (IRESMAN_TempLateParams *)initArgs;

    GT_assert(ti_sdo_fc_ires_grouputils, initArgs != NULL);

    /* 
     *  Check if already initialized
     */

    if (_initialized) {

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
                "_IRESMAN_GROUPUTILS_init> Exit (status=IRES_EEXISTS)\n"); 

       return (IRES_EEXISTS); 

    }

    if (gtInit == 0) {

        GT_init();

        GT_create(&ti_sdo_fc_ires_grouputils_GTMask, "ti.sdo.fc.ires.grouputils");
    
        gtInit = 1;
    }

    GT_1trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_init> Enter (initArgs=0x%x)\n", initArgs); 
    
    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    _resmanInternalState.allocFxn = resmanArgs->baseConfig.allocFxn;

    _resmanInternalState.freeFxn = resmanArgs->baseConfig.freeFxn;

    _GROUPUTILS_sem = (*ti_sdo_fc_ires_grouputils_GROUPUTILS_semCreateFxn)
            (_GROUPUTILS_MEMID, 1); 

    if (NULL == _GROUPUTILS_sem) {

       return (IRES_EFAIL); 
    }

    /*
     * Set Initalized flag to 1 if successful
     */
     _initialized = 1;

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_init> Exit (status=IRES_OK)\n"); 

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_GROUPUTILS_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory 
 *  allocated etc
 */
IRES_Status IRESMAN_GROUPUTILS_exit() 
{
    /*
     * Check if initialized
     */
    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_exit> Enter \n"); 

    if (!(_initialized)) {

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
                "_IRESMAN_GROUPUTILS_exit> Exit (status=IRES_ENOINIT)\n"); 

        return (IRES_ENOINIT);
    }

    /*
     * Free up any memory that might be allocated in this module
     * Basically memory that has been used by the protocol implementation
     */

    /*
     * Set the initialized flag to zero again
     */
    _initialized = 0;


    (*ti_sdo_fc_ires_grouputils_GROUPUTILS_semDeleteFxn)(_GROUPUTILS_sem);

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_exit> Exit (status=IRES_OK)\n"); 

    GT_exit();

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_GROUPUTILS_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the 
 *  IRES_ResourceProtocolArgs
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_GROUPUTILS_getHandles( IALG_Handle algHandle, 
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId, 
        IRES_Status * status)
{
    IALG_MemRec resourceMemRecs[1];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    IRES_GROUPUTILS_ConstructHandleArgs args;  

    GT_2trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId); 

    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, protocolArgs);

    if (_initialized != 1) {
        *status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_7CLASS, 
                "_IRESMAN_GROUPUTILS_getHandles> RMAN register for GROUPUTILS "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (NULL);
    }

    numMemRecs = IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);
 
    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRES_GROUPUTILS_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_ESDATA;
    constructHandleMemRec.attrs = IALG_PERSIST;
 
    if (FALSE == _resmanInternalState.allocFxn(&constructHandleMemRec, 1)) {

        GT_2trace(ti_sdo_fc_ires_grouputils_GTMask, GT_7CLASS, 
                "_IRESMAN_GROUPUTILS_getHandles> Error allocating memory for "
                "construct args of size 0x%x, alignment 0x%x, space IALG_ESDATA"
                ", attrs IALG_PERSIST\n", constructHandleMemRec.size, 
                constructHandleMemRec.alignment);

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER,
                "_IRESMAN_GROUPUTILS_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");
 
        *status = IRES_ENOMEM;
        return (NULL);
    }

    if (FALSE == _resmanInternalState.allocFxn(resourceMemRecs, numMemRecs)) {

        GT_2trace(ti_sdo_fc_ires_grouputils_GTMask, GT_7CLASS, 
                "_IRESMAN_GROUPUTILS_getHandles> Error allocating memory for "
                "resource handle of size 0x%x, alignment 0x%x, space "
                "IALG_ESDATA, attrs IALG_PERSIST\n", resourceMemRecs->size, 
                resourceMemRecs->alignment);

        /* Free constructHandleMemRec */
        _resmanInternalState.freeFxn(&constructHandleMemRec, 1);

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER,
                "_IRESMAN_GROUPUTILS_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");
 
        *status = IRES_ENOMEM;
        return (NULL);

    }

    /*
     * Use IRES_GROUPUTILS_RESOURCEPROTOCOL to init the resource protocol
     * if required
     */
    args.sem = _GROUPUTILS_sem;
    args.scratchId = scratchGroupId;

    resourceHandle = IRESMAN_GROUPUTILS_CONSTRUCTFXNS.constructHandle(
            protocolArgs, resourceMemRecs, (IRESMAN_ConstructArgs *)&args, 
            status);

    /*
     * Free the memory for the ConstructArgs
     */
    _resmanInternalState.freeFxn(&constructHandleMemRec, 1); 

    GT_2trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_getHandles> Exit (status=%d, "
            "resourceHandle=0x%x)\n", *status, resourceHandle); 

    return (resourceHandle);
}

/*
 *  ======== IRESMAN_GROUPUTILS_freeHandle ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_GROUPUTILS_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ProtocolArgs * protocolArgs, 
        Int scratchGroupId) 
{
    IALG_MemRec resourceMemRecs[1];
    Int numMemRecs;
    IRES_Status status = IRES_OK;

    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, protocolArgs);
    GT_assert(ti_sdo_fc_ires_grouputils_GTMask, algResourceHandle);

    GT_3trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_freeHandles> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle, 
            protocolArgs, scratchGroupId); 

    if (_initialized != 1) {
        status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_7CLASS, 
                "_IRESMAN_GROUPUTILS_getHandles> RMAN register for GROUPUTILS "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (status);
    }


    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_GROUPUTILS_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    /* Set Base address of Memory location to free */
    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_GROUPUTILS_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_GROUPUTILS_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _resmanInternalState.freeFxn(resourceMemRecs, numMemRecs); 

    GT_0trace(ti_sdo_fc_ires_grouputils_GTMask, GT_ENTER, 
            "_IRESMAN_GROUPUTILS_freeHandles> Exit (status=IRES_OK)\n"); 

    return (IRES_OK);
}

IRESMAN_Fxns IRESMAN_GROUPUTILS =  {
    IRESMAN_GROUPUTILS_getProtocolName,
    IRESMAN_GROUPUTILS_getProtocolRevision,
    IRESMAN_GROUPUTILS_init,
    IRESMAN_GROUPUTILS_exit,
    IRESMAN_GROUPUTILS_getHandles,
    IRESMAN_GROUPUTILS_freeHandle
};

IRESMAN_TempLateParams IRESMAN_GROUPUTILS_DEFAULTPARAM;

IRESMAN_Fxns * GROUPUTILS_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_GROUPUTILS));
}


IRESMAN_Params * GROUPUTILS_getDefaultParams()
{
    IRESMAN_GROUPUTILS_DEFAULTPARAM.baseConfig.size = 
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_GROUPUTILS_DEFAULTPARAM);
}
/*
 *  @(#) ti.sdo.fc.ires.grouputils; 1, 0, 0,32; 12-1-2010 17:25:14; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

