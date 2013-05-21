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
 *  ======== iresman_hdvicp.c ========
 */

#include <xdc/std.h>

#include <ti/sdo/utils/trace/gt.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_hdvicp.h"
#include "iresman_protocol_hdvicp.h"
#include "ires_hdvicp.h"
#include "_hdvicp.h"

#ifdef xdc_target__os_Linux

#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ti/sdo/fc/utils/sharedMem.h>


extern int VICP_init();
extern int VICP_exit();

#endif

/* can't make this static, as it's used throughout this package */
GT_Mask ti_sdo_fc_ires_hdvicp_GTMask;

#define IRESMAN_HDVICP_RESOURCEFREE 0xFFFF

#define IRESMAN_HDVICP_MAXSCRATCHGROUPS 20

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_HDVICP_InternalState {

    int numOpens;

    int resourceBusy[IRES_HDVICP_MAXRESOURCES]; /**< Busy-status of HDVICP
                                                 *   resources.
                                                 */
    int refCount[IRES_HDVICP_MAXRESOURCES];     /**< Reference count
                                                 *   when multiple
                                                 *   requestors from
                                                 *   the same scratch
                                                 *   group have been
                                                 *   granted the
                                                 *   resource.
                                                 */
    int numResources;                           /**< Number of HDVICP resources
                                                 *   being managed.
                                                 */
    int sharedMemId;
} IRESMAN_HDVICP_InternalState;

static IRESMAN_PersistentAllocFxn * allocFxn;   /**< Memory alloc function */
static IRESMAN_PersistentFreeFxn * freeFxn;     /**< Memory free function */
/*
 * Flag indicating if the resource manager is initialized
 */
static unsigned int _initialized = 0;

/*
 * Represents the IRES EDMA3 Resource manager
 */
static IRESMAN_HDVICP_InternalState * _resmanInternalState;

static int gtInit = 0;

#ifdef xdc_target__os_Linux

/*
 * Lock to guard access to critical sections 
 */
static LockMP_Handle _HDVICP_lock = NULL;
#else

/*
 * For non-Linux, non-MP case, use statically allocated memory 
 */ 
static IRESMAN_HDVICP_InternalState _HDVICP_internalState;     
#endif

static void getInternalState(); 
static void setInternalState(); 
static void freeInternalState();

extern unsigned int _HDVICP_NUMRESOURCES; 

/*
 *  ======== IRESMAN_HDVICP_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_HDVICP_getProtocolName()
{

    if (0 == gtInit) {
        
        GT_init(); 

        GT_create(&ti_sdo_fc_ires_hdvicp_GTMask, "ti.sdo.fc.ires.hdvicp");
        
        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_getProtocolName> Enter\n");

    GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_getProtocolName> Exit (name=%s)\n",
            IRESMAN_HDVICP_CONSTRUCTFXNS.getName());

        return (IRESMAN_HDVICP_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_HDVICP_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_HDVICP_getProtocolRevision()
{
    IRES_ProtocolRevision * version;

    if (0 == gtInit) {
        
        GT_init(); 

        GT_create(&ti_sdo_fc_ires_hdvicp_GTMask, "ti.sdo.fc.ires.hdvicp");
        
        gtInit = 1;
    }

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_getProtocolRevision> Enter\n");

    version = IRESMAN_HDVICP_CONSTRUCTFXNS.getRevision();

    GT_3trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_getProtocolRevision> Exit (version=(%d.%d.%d))"
            "\n", version->Major, version->Source, version->Radius);

    return (version);
}

/*
 *  ======== IRESMAN_HDVICP_init ========
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_HDVICP_init(IRESMAN_Params * initArgs)
{

    IRESMAN_HdVicpParams * resmanArgs = (IRESMAN_HdVicpParams *)initArgs;

    if (0 == gtInit) {
        
        GT_init(); 

        GT_create(&ti_sdo_fc_ires_hdvicp_GTMask, "ti.sdo.fc.ires.hdvicp");
        
        gtInit = 1;
    }

    GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_init> Enter (initArgs=0x%x)\n", initArgs);


    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, initArgs != NULL);

    /*
     *  Check if already initialized
     */
    if (_initialized) {

       GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
               "IRESMAN_HDVICP_init> Exit (status=IRES_EEXISTS)\n");

       return (IRES_EEXISTS);
    }

    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    allocFxn = resmanArgs->baseConfig.allocFxn;
    freeFxn = resmanArgs->baseConfig.freeFxn;

#ifdef xdc_target__os_Linux
    if (NULL == _HDVICP_lock) {

        /* Create a lock for protecting VICP internal state object */
        _HDVICP_lock = LockMP_create(_HDVICP_LOCKID);
 
        if (_HDVICP_lock == NULL) {
 
            GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                    "IRESMAN_HDVICP_init> Failed to create IPC lock, "
                    "key = 0x%x\n", _HDVICP_LOCKID);

            GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER, 
                    "IRESMAN_HDVICP_init> Exit (status=IRES_EFAIL)\n");
 
            return (IRES_EFAIL);
        }
    }
#endif

    getInternalState();

    if (NULL == _resmanInternalState) {

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_VICP2_init> Failed to obtain Internal state Object\n");

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER, 
                "IRESMAN_VICP2_init> Exit (status=IRES_EFAIL)\n");

#ifdef xdc_target__os_Linux
        LockMP_delete(_HDVICP_lock);
#endif

        return (IRES_EFAIL);
    }

#ifdef xdc_target__os_Linux
    VICP_init();
#endif

    _resmanInternalState->numOpens++;

    if (sizeof(IRESMAN_Params) == resmanArgs->baseConfig.size) {
        _resmanInternalState->numResources = _HDVICP_NUMRESOURCES;
    }
    else {
        _resmanInternalState->numResources = resmanArgs->numResources;
    }


    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask,
            _resmanInternalState->numResources <= IRES_HDVICP_MAXRESOURCES);

    /*
     * Set Initalized flag to 1 if successful
     */
     _initialized = 1;

     GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_init> Exit (status=IRES_OK)\n");

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_HDVICP_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory
 *  allocated etc
 */
IRES_Status IRESMAN_HDVICP_exit()
{

    /*
     * Check if initialized
     */

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_exit> Enter\n");

    if (!(_initialized)) {

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_exit> Exit (status=IRES_ENOINIT)\n");

        return (IRES_ENOINIT);
    }

    /*
     * Set the initialized flag to zero again
     */
    _initialized = 0;


    _resmanInternalState->numOpens--;

    freeInternalState();

#ifdef xdc_target__os_Linux

    if (NULL != _HDVICP_lock) {
        LockMP_delete(_HDVICP_lock);
    }
#endif

    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_exit> Exit (status=IRES_OK)\n");

    GT_exit();

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_HDVICP_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the
 *  IRES_ResourceProtocolArgs
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Handle IRESMAN_HDVICP_getHandles(IALG_Handle algHandle,
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec protocolMemRecs[IRES_HDVICP_MAXRESOURCES];
    IALG_MemRec constructHandleMemRec;
    Int numMemRecs = 0;
    Int i;
    Int Id = -1;
    IRESMAN_HDVICP_ConstructHandleArgs * constructArgs = NULL;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;

    /*
     * Cast the protocolArgs
     */
    IRES_HDVICP_ProtocolArgs * configArgs =
            (IRES_HDVICP_ProtocolArgs *) protocolArgs;

    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, protocolArgs);

    GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId);


    if (_initialized != 1) {
        *status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_getHandles> RMAN register for HDVICP resource "
                "not happened successfully. Please call RMAN_register before "
                "trying to assign or release resources\n");

        return (NULL);
    }

    if (0 == _resmanInternalState->numResources) {

        *status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_getHandles> Trying to request HDVICP resource "
                "on a device with 0 HDVICP resources. Check device "
                "configuration.\n");

        return (NULL);
    }

    if (configArgs->base.mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } else if (configArgs->base.mode == IRES_LATEACQUIRE) {
        //Set to MAX SCRATCH GROUPS
        scratchGroupId = IRESMAN_HDVICP_MAXSCRATCHGROUPS;  
        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                "IRESMAN_HDVICP_getHandles> Requested IRES_LATEACQUIRE "
                "HDVICP resources. Ensure you \"lock\" resources using "
                "IRES RESUTILS API before using them for correct operation\n");
    }

    /*
     * Get IRES_HDVICP handle's memory requirements
     */
    numMemRecs = IRESMAN_HDVICP_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask,
            numMemRecs <= IRES_HDVICP_MAXRESOURCES);

    /*
     * Use the protocolArgs to determine which resource to allocate
     */
    if (configArgs->id == IRES_HDVICP_ID_ANY) {

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                "IRESMAN_HDVICP_getHandles> ANY Resource requested\n");

        for (i = (_resmanInternalState->numResources - 1); i >= 0; i--) {

            /*
             * If the requested resource is free or if the same scratch group
             * requests it return the Id
             * If the resourceBusy status is set to -1, this implies that the
             * resource has been granted persistently
             */
            if ((IRESMAN_HDVICP_RESOURCEFREE ==
                    _resmanInternalState->resourceBusy[i])) {

                _resmanInternalState->resourceBusy[i] = scratchGroupId;

                Id = i;

                _resmanInternalState->refCount[i] = 1;

                GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                        "IRESMAN_HDVICP_getHandles> HDVICP Resource %d is "
                        "available\n", Id);

                break;
            }
            else if ((_resmanInternalState->resourceBusy[i] != -1 ) &&
                    (_resmanInternalState->resourceBusy[i] == scratchGroupId)) {
                _resmanInternalState->refCount[i]++;

                Id = i;

                GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                        "IRESMAN_HDVICP_getHandles> HDVICP Resource %d is "
                        "available to scratch group %d\n", Id, scratchGroupId);

                break;
            }
        }

        if  (Id == -1) {
            *status = IRES_ENORESOURCE;

            GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                    "IRESMAN_HDVICP_getHandles> Error obtaining free HDVICP"
                    "resource.\n");

            GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                    "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)\n");

            return (NULL);
        }
    }
    else {

        switch (configArgs->id) {

            case IRES_HDVICP_ID_0 :
                Id = 0;
                if (Id >= _resmanInternalState->numResources)  {

                    *status = IRES_ENORESOURCE;
                    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                            "IRESMAN_HDVICP_getHandles> Did not recognize "
                            "HDVICP resource request.\n");

                    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                            "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                            "status=IRES_ENORESOURCE)\n");

                    return (NULL);
               }
               break;

            case IRES_HDVICP_ID_1:
                Id = 1;
                if (Id >= _resmanInternalState->numResources) {

                    *status = IRES_ENORESOURCE;
                    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                            "IRESMAN_HDVICP_getHandles> Did not recognize "
                            "HDVICP resource request.\n");

                    GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                            "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                            "status=IRES_ENORESOURCE)\n");

                    return (NULL);
               }
               break;

            default:
                *status = IRES_ENORESOURCE;
                GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                    "IRESMAN_HDVICP_getHandles> Did not recognize HDVICP "
                    "resource request.\n");

                GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                        "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                        "status=IRES_ENORESOURCE)\n");

                return (NULL);
        }

        GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                "IRESMAN_HDVICP_getHandles> Specific HDVICP Resource requested "                "%d\n", Id);

        if ((IRESMAN_HDVICP_RESOURCEFREE ==
                _resmanInternalState->resourceBusy[Id])) {
            _resmanInternalState->resourceBusy[Id] = scratchGroupId;
            _resmanInternalState->refCount[Id] = 1;

            GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                    "IRESMAN_HDVICP_getHandles> HDVICP Resource %d available\n",
                    Id);
        }
        else if ((_resmanInternalState->resourceBusy[Id] != -1) &&
                (_resmanInternalState->resourceBusy[Id] == scratchGroupId)) {
            _resmanInternalState->refCount[Id]++;

            GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_4CLASS,
                    "IRESMAN_HDVICP_getHandles> HDVICP Resource %d available "
                    "to scratch group %d\n", Id, scratchGroupId);
        }
        else {
            *status = IRES_ENORESOURCE;

            GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                    "IRESMAN_HDVICP_getHandles> Error obtaining HDVICP"
                    "resource.\n");

            GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                    "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                    "status=IRES_ENORESOURCE)\n");

            return (NULL);
        }
    }

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_HDVICP_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == allocFxn(&constructHandleMemRec, 1)) {
        *status =  IRES_ENOMEM;

        GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST\n",
                constructHandleMemRec.size, constructHandleMemRec.alignment);

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        _resmanInternalState->refCount[Id]-- ;
        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] = 
                    IRESMAN_HDVICP_RESOURCEFREE;
        }

        return (NULL);
    }

    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask,
            IALG_EXTERNAL == constructHandleMemRec.space);
    constructArgs = constructHandleMemRec.base;

    /*
     * Populate the construct args
     */
        (constructArgs->args).size = sizeof(IRESMAN_HDVICP_ConstructHandleArgs);
    constructArgs->id = Id;

    //TODO Find out what Info is required to be filled here
    constructArgs->info = NULL;

    if (-1 == scratchGroupId) {
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    }

    /*
     * Obtain memory resources to build the handle
     */
    IRESMAN_HDVICP_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, protocolMemRecs);

    /*
     * Allocate that memory
     */
    if (FALSE == allocFxn(protocolMemRecs, numMemRecs)) {

        *status = IRES_ENOMEM;

        GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_getHandles> Error allocating memory for "
                "constructing handle of size 0x%x, alignment 0x%x, space "
                "IALG_EXTERNAL, attrs IALG_PERSIST\n", protocolMemRecs->size,
                protocolMemRecs->alignment);

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");

        freeFxn(&constructHandleMemRec, 1);

        _resmanInternalState->refCount[Id]-- ;
        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] = 
                    IRESMAN_HDVICP_RESOURCEFREE;
        }

        return (NULL);
    }

    /*
     * Use the CONSTRUCT interface of the protocol implementation to
     * construct the handle within the allocated resource
     */
     resourceHandle = IRESMAN_HDVICP_CONSTRUCTFXNS.constructHandle(
            protocolArgs, protocolMemRecs,
            (IRESMAN_ConstructArgs *)constructArgs, status);

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */
    freeFxn(&constructHandleMemRec, 1);

    if (IRES_OK != *status) {

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_getHandles> Error freeing memory \n");

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)\n");

        _resmanInternalState->refCount[Id]-- ;

        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] = 
                    IRESMAN_HDVICP_RESOURCEFREE;
        }

        return (NULL);
    }
    else {

        GT_2trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_getHandles> Exit (handle=0x%x, "
                "status=0x%x)\n",resourceHandle, *status);

        return (resourceHandle);
    }
}

/*
 *  ======== IRESMAN_HDVICP_freeHandles ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_HDVICP_freeHandles(IALG_Handle algHandle,
        IRES_Handle algResourceHandle, IRES_ProtocolArgs * protocolArgs,
        Int scratchGroupId)
{
    IALG_MemRec resourceMemRecs[IRES_HDVICP_MAXRESOURCES];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    Int Id = -1;

    IRES_HDVICP_Handle resourceHandle = (IRES_HDVICP_Handle)
            algResourceHandle;

    IRES_HDVICP_ProtocolArgs * configArgs =
            (IRES_HDVICP_ProtocolArgs *) protocolArgs;

    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, protocolArgs);
    GT_assert(ti_sdo_fc_ires_hdvicp_GTMask, algResourceHandle);

    GT_3trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_freeHandle> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle,
            protocolArgs, scratchGroupId);

    if (_initialized != 1) {

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_freeHandles> RMAN register for HDVICP resource "
                "not happened successfully. Please call RMAN_register before "
                "trying to assign or release resources\n");

        status =  IRES_ENORESOURCE;

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_freeHandles> Exit (status=IRES_ENORESOURCE)\n");

        return (status);
    }

    if (configArgs->base.mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } 

    /*
     * Use the protocolArgs to determine which resource to free
     */
    Id = resourceHandle->id;

    if ((Id >= _resmanInternalState->numResources) || 
            (_resmanInternalState->resourceBusy[Id] != scratchGroupId)) {

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_7CLASS,
                "IRESMAN_HDVICP_freeHandles> Error freeing HDVICP resource. "
                "Resource already free\n");

        GT_0trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
                "IRESMAN_HDVICP_freeHandles> Exit (status=IRES_ENORESOURCE)\n");

        return (IRES_ENORESOURCE);
    }
    else {

        _resmanInternalState->refCount[Id]-- ;

        if ( 0 == _resmanInternalState->refCount[Id]) {
            _resmanInternalState->resourceBusy[Id] = 
                    IRESMAN_HDVICP_RESOURCEFREE;
        }
    }

    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_HDVICP_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_HDVICP_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_HDVICP_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_HDVICP_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    freeFxn(resourceMemRecs, numMemRecs);

    GT_1trace(ti_sdo_fc_ires_hdvicp_GTMask, GT_ENTER,
            "IRESMAN_HDVICP_freeHandles> Exit (status=%d)\n", status);

    return (status);
}

static void getInternalState() 
{
#ifdef xdc_target__os_Linux
    Int sharedMemId = -1;
 
    _resmanInternalState = (IRESMAN_HDVICP_InternalState *)SHM_getObj(
            _HDVICP_lock, sizeof(IRESMAN_HDVICP_InternalState),
            _HDVICP_LOCKID, &setInternalState, &sharedMemId);
    _resmanInternalState->sharedMemId = sharedMemId;
#else
    _resmanInternalState = (IRESMAN_HDVICP_InternalState *)
            &_HDVICP_internalState;
    setInternalState(_resmanInternalState);
    _resmanInternalState->sharedMemId = 0;
#endif
}

/*
 *  ======== freeInternalState ========
 */
static void freeInternalState()
{
#ifdef xdc_target__os_Linux

    VICP_exit();

    SHM_freeObj(_HDVICP_lock, _resmanInternalState,
            _resmanInternalState->sharedMemId);
#else
    _resmanInternalState = NULL;
#endif
}

/*
 *  ======= setInternalState =======
 */
static Void setInternalState(Void * addr)
{
    IRESMAN_HDVICP_InternalState * intState =
            (IRESMAN_HDVICP_InternalState *)addr;
    Int i;
 
    if (NULL != intState) {

        intState->numOpens = 0;

        for (i = 0; i < IRES_HDVICP_MAXRESOURCES; i++) {

            intState->resourceBusy[i] = IRESMAN_HDVICP_RESOURCEFREE;
            intState->refCount[i] = 0;
        }

    }
}
 
IRESMAN_Fxns IRESMAN_HDVICP =  {
    IRESMAN_HDVICP_getProtocolName,
    IRESMAN_HDVICP_getProtocolRevision,
    IRESMAN_HDVICP_init,
    IRESMAN_HDVICP_exit,
    IRESMAN_HDVICP_getHandles,
    IRESMAN_HDVICP_freeHandles
};

IRESMAN_HdVicpParams IRESMAN_HDVICP_DEFAULTPARAM;

IRESMAN_Fxns * HDVICP_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_HDVICP));
}


IRESMAN_Params * HDVICP_getDefaultParams()
{
    IRESMAN_HDVICP_DEFAULTPARAM.baseConfig.size = sizeof(IRESMAN_Params);

    /* Don't need to populate this, xdt will figure this one out */ 
    /* IRESMAN_HDVICP_DEFAULTPARAM->numResources = 2;*/
    return ((IRESMAN_Params *)&IRESMAN_HDVICP_DEFAULTPARAM);
}
/*
 *  @(#) ti.sdo.fc.ires.hdvicp; 1, 0, 1,133; 12-1-2010 17:25:16; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

