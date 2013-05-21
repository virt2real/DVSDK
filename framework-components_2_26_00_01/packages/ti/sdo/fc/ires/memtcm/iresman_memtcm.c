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
 *  ======== iresman_memtcm.c ========
 *  IRESMAN implemenation for handling the TCM memory resource on the DM365 
 *  device 
 */

#include <xdc/std.h>

/*
 * Define this, before including ires_<>.h, as that checks for this 
 * define to avoid multiple inclusion of the static Protocol Version definition
 * of IRES_<>_PROTOCOLREVISION from the header file. 
 */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "iresman_memtcm.h"
#include "ires_memtcm.h"
#include "iresman_protocol_memtcm.h"
#include "_memtcm.h"


#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_ires_memtcm_GTMask;

#include <ti/sdo/linuxutils/cmem/include/cmem.h>
#include <ti/sdo/fc/utils/smgrmp.h>
#include <ti/sdo/fc/utils/sharedMem.h>
#include <sys/mman.h>
#include <fcntl.h>

#define IRESMAN_MEMTCM_RESOURCEFREE 0xFFFF
#define CURTRACE ti_sdo_fc_ires_memtcm_GTMask

#define MEMTCM_NUM_GROUPS 20 
#define MEMTCM_RESSIZE 0x200
#define MEMTCM_NUMRES ((MEMTCM_size)/(MEMTCM_RESSIZE))

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_MEMTCM_InternalState {

    void *  armtcmAddr;                         /* Addr of the beggging of ARM
                                                   TCM memory */
    Int numOpens;                               /* Number of times this object
                                                   has been accessed */ 
    Int sharedMemId;                            /* Shared memory Id of the 
                                                   mem block used to store 
                                                   this info */  
} IRESMAN_MEMTCM_InternalState;

extern UInt32 MEMTCM_blockId;                   /* Block Id from which to 
                                                   request ARM TCM CMEM mem */
extern UInt32 MEMTCM_size;                      /* Size of this memory */

/*
 * Flag indicating if the resource manager is initialized
 */
static unsigned int _initialized = 0;

/*
 * Flag indicating if gt has been initialized 
 */
static int gtInit = 0;

/*
 * Process lock to guard access to critical sections 
 */
static LockMP_Handle _MEMTCM_lock = NULL;

/*
 * Represents the IRES EDMA3 Resource manager
 */
static IRESMAN_MEMTCM_InternalState * _resmanInternalState = NULL;

/*
 * Memory alloc Function
 */
static IRESMAN_PersistentAllocFxn * _allocFxn = NULL;

/*
 * Memory free Function
 */
static IRESMAN_PersistentFreeFxn * _freeFxn = NULL;

/*
 * Handle to the scratch memory manager
 */ 
static SMGRMP_Handle smgr = NULL;

/*
 * Process specific address of this memory 
 */ 
static void * armtcmAddr = NULL;

/* 
 * Obtains a handle to the internal state information for this resource manager 
 */
static void getInternalState(); 

/* 
 * Frees the process specific handle to internal state information 
 */
static void freeInternalState();

/* 
 * Initializes the memory that holds internal state information 
 */
static void setInternalState();

/*
 *  ======== IRESMAN_MEMTCM_getProtocolName ========
 *  Function to return the name of the protocol
 */
String IRESMAN_MEMTCM_getProtocolName()
{
    if (gtInit == 0) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.memtcm");
    
        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_getProtocolName> Enter\n");

    GT_1trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_getProtocolName> Exit (Name=%s)\n", 
            IRESMAN_MEMTCM_CONSTRUCTFXNS.getName());

    return (IRESMAN_MEMTCM_CONSTRUCTFXNS.getName());
}

/*
 *  ======== IRESMAN_MEMTCM_getProtocolRevision ========
 *  Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_MEMTCM_getProtocolRevision()
{

#if (GT_TRACE == 1)
    IRES_ProtocolRevision * version;
#endif

    if (gtInit == 0) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.memtcm");
    
        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_getProtocolRevision> Enter\n");

#if (GT_TRACE == 1)
    version = IRESMAN_MEMTCM_CONSTRUCTFXNS.getRevision();
#endif
        
    GT_3trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_getProtocolRevision> Exit (Version=(%d.%d.%d))\n",
            version->Major, version->Source, version->Radius); 

    return (IRESMAN_MEMTCM_CONSTRUCTFXNS.getRevision());
}

/*
 *  ======== IRESMAN_MEMTCM_init ========
 *  Function to initialize the device specific resource manager implementation
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status IRESMAN_MEMTCM_init(IRESMAN_Params * initArgs) 
{

    SMGRMP_Attrs attrs;
    IRESMAN_MemTcmParams * resmanArgs = (IRESMAN_MemTcmParams *)initArgs;
    /* CMEM_AllocParams params; */
    
    GT_assert(ti_sdo_fc_ires_memtcm, initArgs != NULL);

    /* 
     *  Check if already initialized
     */
    if (_initialized) {

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_MEMTCM_init> Exit (status=IRES_EEXISTS)\n"); 

        return (IRES_EEXISTS); 

    }

    if (gtInit == 0) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.memtcm");
    
        gtInit = 1;
    }

    GT_1trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_init> Enter (initArgs=0x%x)\n", initArgs); 
    
    /*
     * Information regarding the memory allocation/free functions
     * is stored as part of the internal state of the resource
     * manager
     */
    if (NULL == _MEMTCM_lock) {

        /* Create a lock for protecting MEMTCM internal state object */
        _MEMTCM_lock = LockMP_create(_MEMTCM_LOCKID);
 
        if (_MEMTCM_lock == NULL) {
 
            GT_1trace(CURTRACE, GT_7CLASS,
                    "IRESMAN_MEMTCM_init> Failed to create IPC lock, "
                    "key = 0x%x\n", _MEMTCM_LOCKID);

            GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_MEMTCM_init> Exit (status="
                    "IRES_EFAIL)\n");
 
            return (IRES_EFAIL);
        }
    }

    getInternalState();

    if (NULL == _resmanInternalState) {

        GT_0trace(CURTRACE, GT_7CLASS,
                "IRESMAN_MEMTCM_init>Failed to obtain Internal state Object\n");

        GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_MEMTCM_init> Exit (status="
                "IRES_EFAIL)\n");

        LockMP_delete(_MEMTCM_lock);

        return (IRES_EFAIL);
    }

    /*
     * Information regarding the memory allocation/free functions
     */
    _allocFxn = resmanArgs->baseConfig.allocFxn;

    _freeFxn = resmanArgs->baseConfig.freeFxn;


    if (0 != CMEM_init()) {

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_init> Could not initialize CMEM\n"); 

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_MEMTCM_init> Exit (status=IRES_EFAIL)\n"); 

        freeInternalState();

        LockMP_delete(_MEMTCM_lock);

        return (IRES_EFAIL);
    }

/* TODO: Figure out how to populate the params */ 
    if (_resmanInternalState->numOpens == 0) {

        armtcmAddr = CMEM_alloc2(MEMTCM_blockId, MEMTCM_size, NULL);

        _resmanInternalState->armtcmAddr = (void *)CMEM_getPhys(armtcmAddr);
    }
    else {

        armtcmAddr = CMEM_registerAlloc(
                (unsigned long)_resmanInternalState->armtcmAddr);
    }

    if (NULL == armtcmAddr) {

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_init> Could not allocate TCM memory from CMEM"
                "\n"); 

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_MEMTCM_init> Exit (status=IRES_EFAIL)\n"); 

        freeInternalState();

        LockMP_delete(_MEMTCM_lock);

        return (IRES_EFAIL);
    }

    if (NULL == smgr) {

        attrs.numScratchGroups = MEMTCM_NUM_GROUPS;
        attrs.numResources = (MEMTCM_NUMRES);
                                     /* One resource corresponds to a 1/2 K
                                        chunk of memory (0x200), Manage memory
                                        in chunks of 0x200
                                      */
        attrs.lock = _MEMTCM_lock;

        attrs.key = (void *)_MEMTCM_MEMID;    /* A key specific to the resource 
                                                being managed */ 

        /* This will create a new resource manager or return a process-specific 
           handle to an existing smgr */ 
        smgr = SMGRMP_create(&attrs);

        if (NULL == smgr) {

            GT_0trace(CURTRACE, GT_7CLASS, "IRESMAN_MEMTCM_init> Error creating"
                    " scratch resource manager.\n");

            GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_MEMTCM_init> Exit (status="
                    "IRES_EFAIL)\n");

            freeInternalState();

            LockMP_delete(_MEMTCM_lock);

            return (IRES_EFAIL);
        }
    }

    _resmanInternalState->numOpens++;

    /*
     * Set Initalized flag to 1 if successful
     */
     _initialized = 1;

     GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_init> Exit (status=IRES_OK)\n"); 

     return (IRES_OK);
}

/*
 *  ======== IRESMAN_MEMTCM_exit ========
 *  Function called when RESMAN is no longer needed. Use it to free memory 
 *  allocated etc
 */
IRES_Status IRESMAN_MEMTCM_exit() 
{
    /*
     * Check if initialized
     */
    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_exit> Enter \n"); 

    if (!(_initialized)) {

        GT_0trace(CURTRACE, GT_ENTER, 
                "IRESMAN_MEMTCM_exit> Exit (status=IRES_ENOINIT)\n"); 

        return (IRES_ENOINIT);
    }

    freeInternalState();

    SMGRMP_delete(_MEMTCM_lock, smgr); 

    smgr = NULL;

    LockMP_delete(_MEMTCM_lock);

    _MEMTCM_lock = NULL;

    /*
     * Free up any memory that might be allocated in this module
     * Basically memory that has been used by the protocol implementation
     */

    /*
     * Set the initialized flag to zero again
     */
    _initialized = 0;

    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_exit> Exit (status=IRES_OK)\n"); 

    GT_exit();

    return (IRES_OK);
}

/*
 *  ======== IRESMAN_MEMTCM_getHandles ========
 *  Function that returns the IRES_Handle to the resource requested using the 
 *  IRES_ResourceProtocolArgs
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_MEMTCM_getHandles( IALG_Handle algHandle, 
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId, 
        IRES_Status * status)
{
    IALG_MemRec resourceMemRecs[1];
    IALG_MemRec constructHandleMemRec;
    IRES_MEMTCM_ConstructHandleArgs * constructArgs = NULL; 
    Int numMemRecs;
    IRES_Handle resourceHandle = (IRES_Handle)NULL;
    Int numResources, resourceId = -1;
    Bool smg_status = FALSE;
    unsigned int size = 0x0;
    void * addr = NULL;

    GT_2trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_getHandles> Enter (protocolArgs=0x%x, "
            "scratchGroupId=%d)\n", protocolArgs, scratchGroupId); 

    GT_assert(CURTRACE, protocolArgs);

    if (_initialized != 1) {
        *status =  IRES_ENORESOURCE;

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_getHandles> RMAN register for MEMTCM "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (NULL);
    }

    numMemRecs = IRESMAN_MEMTCM_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_MEMTCM_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);
 
    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRES_MEMTCM_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_ESDATA;
    constructHandleMemRec.attrs = IALG_PERSIST;
 
    if (FALSE == _allocFxn(&constructHandleMemRec, 1)) {

        GT_2trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_getHandles> Error allocating memory for "
                "construct args of size 0x%x, alignment 0x%x, space IALG_ESDATA"
                ", attrs IALG_PERSIST\n", constructHandleMemRec.size, 
                constructHandleMemRec.alignment);

        GT_0trace(CURTRACE, GT_ENTER,
                "IRESMAN_MEMTCM_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");
 
        *status = IRES_ENOMEM;
        return (NULL);
    }

    constructArgs = (IRES_MEMTCM_ConstructHandleArgs *) 
            constructHandleMemRec.base;

    if (FALSE == _allocFxn(resourceMemRecs, numMemRecs)) {

        GT_2trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_getHandles> Error allocating memory for "
                "resource handle of size 0x%x, alignment 0x%x, space "
                "IALG_ESDATA, attrs IALG_PERSIST\n", resourceMemRecs->size, 
                resourceMemRecs->alignment);

        /* Free constructHandleMemRec */
        _freeFxn(&constructHandleMemRec, 1);

        GT_0trace(CURTRACE, GT_ENTER,
                "IRESMAN_MEMTCM_getHandles> Exit (handle=NULL, "
                "status=IRES_ENOMEM)\n");
 
        *status = IRES_ENOMEM;
        return (NULL);

    }

    if (-1 == scratchGroupId) {
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    } 

/* TODO: Add resource work here */
/* TODO: smgrmp alloc */ 
    size = ((IRES_MEMTCM_ProtocolArgs *)protocolArgs)->memSize;
    resourceId = -1;
    numResources = (size + (MEMTCM_RESSIZE -1))/MEMTCM_RESSIZE;

    /* Round up number of resources to MEMTCM_RESSIZE */
    /* numResources */

    smg_status = SMGRMP_alloc(smgr, algHandle, &resourceId, numResources,
            scratchGroupId);

    if (smg_status == FALSE) {

        GT_1trace(CURTRACE, GT_7CLASS, "IRESMAN_MEMTCM_getHandles> Error "
                " requesting memory of size 0x%x\n", 
                numResources * MEMTCM_RESSIZE);

        GT_0trace(CURTRACE, GT_ENTER,
                "IRESMAN_MEMTCM_getHandles> Exit (handle=NULL, "
                "status=IRES_ENORESOURCE)\n");

        *status = IRES_ENORESOURCE;

        /*
         * Free the memory for the ConstructArgs
         */
        _freeFxn(&constructHandleMemRec, 1); 

        /*
         * Free the memory for the resource 
         */
        _freeFxn(resourceMemRecs, 1); 

        return (NULL);
    }

    GT_assert(CURTRACE, resourceId != -1);

    constructArgs->memSize = size;     

    /* Take the physical base address, add offset to it and mmap it to this 
       process */
    addr = armtcmAddr + (resourceId * MEMTCM_RESSIZE);

    constructArgs->memAddr = addr;

    if (NULL == constructArgs->memAddr) {

        *status = IRES_EFAIL;

        GT_1trace(CURTRACE, GT_7CLASS, "IRESMAN_MEMTCM_getHandles> Error "
                " calling mmap on returned memory 0x%x\n", addr); 

        GT_0trace(CURTRACE, GT_ENTER,
                "IRESMAN_MEMTCM_getHandles> Exit (handle=NULL, "
                "status=IRES_EFAIL)\n");

        SMGRMP_free(smgr, algHandle, resourceId, numResources, scratchGroupId);

        /*
         * Free the memory for the ConstructArgs
         */
        _freeFxn(&constructHandleMemRec, 1); 

        /*
         * Free the memory for the resource 
         */
        _freeFxn(resourceMemRecs, 1); 


        return (NULL);
    }

    /*
     * Use IRES_MEMTCM_RESOURCEPROTOCOL to init the resource protocol
     * if required
     */
    resourceHandle = IRESMAN_MEMTCM_CONSTRUCTFXNS.constructHandle(
            protocolArgs, resourceMemRecs, 
            (IRESMAN_ConstructArgs *)constructArgs, 
            status);

    /*
     * Free the memory for the ConstructArgs
     */
    _freeFxn(&constructHandleMemRec, 1); 

    GT_2trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_getHandles> Exit (status=%d, "
            "resourceHandle=0x%x)\n", *status, resourceHandle); 

    return (resourceHandle);
}

/*
 *  ======== IRESMAN_MEMTCM_freeHandle ========
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_MEMTCM_freeHandle(IALG_Handle algHandle, IRES_Handle
        algResourceHandle, IRES_ProtocolArgs * protocolArgs, 
        Int scratchGroupId) 
{
    IALG_MemRec resourceMemRecs[1];
    Int numMemRecs;
    IRES_Status status = IRES_OK;
    Int resourceId = -1;
    unsigned int numResources = 0;
    unsigned int addr = 0x0;
    unsigned int size = 0x0;
    Bool smg_status = FALSE;


    GT_assert(CURTRACE, protocolArgs);
    GT_assert(CURTRACE, algResourceHandle);

    GT_3trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_freeHandles> Enter (handle=0x%x, "
            "protocolArgs=0x%x, scratchGroupId=%d)\n", algResourceHandle, 
            protocolArgs, scratchGroupId); 

    if (_initialized != 1) {
        status =  IRES_ENORESOURCE;

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_getHandles> RMAN register for MEMTCM "
                "resource not happened successfully. Please call RMAN_register "
                "before trying to assign or release resources\n");

        return (status);
    }


    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_MEMTCM_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_MEMTCM_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    /* Set Base address of Memory location to free */
    resourceMemRecs[0].base = algResourceHandle;

    /* Free other things allocated */
    addr = CMEM_getPhys(((IRES_MEMTCM_Handle)algResourceHandle)->memAddr);

    size = ((IRES_MEMTCM_Handle)algResourceHandle)->memSize;

    resourceId = ((unsigned int)addr - 
            (unsigned int)_resmanInternalState->armtcmAddr)/MEMTCM_RESSIZE; 

    numResources = (size + (MEMTCM_RESSIZE -1))/MEMTCM_RESSIZE;

    smg_status = SMGRMP_free(smgr, algHandle, resourceId, numResources,
            scratchGroupId);

    if (smg_status == FALSE) {

        GT_1trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_MEMTCM_freeHandles> Error trying to free "
                "memory 0x%x\n",
                ((IRES_MEMTCM_Handle)algResourceHandle)->memAddr);

        return (IRES_EFAIL);
    }

    /*
     * Use IRES_MEMTCM_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_MEMTCM_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _freeFxn(resourceMemRecs, numMemRecs); 

    GT_0trace(CURTRACE, GT_ENTER, 
            "IRESMAN_MEMTCM_freeHandles> Exit (status=IRES_OK)\n"); 

    return (IRES_OK);
}

IRESMAN_Fxns IRESMAN_MEMTCM =  {
    IRESMAN_MEMTCM_getProtocolName,
    IRESMAN_MEMTCM_getProtocolRevision,
    IRESMAN_MEMTCM_init,
    IRESMAN_MEMTCM_exit,
    IRESMAN_MEMTCM_getHandles,
    IRESMAN_MEMTCM_freeHandle
};

IRESMAN_MemTcmParams IRESMAN_MEMTCM_DEFAULTPARAM;

IRESMAN_Fxns * MEMTCM_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_MEMTCM));
}


IRESMAN_Params * MEMTCM_getDefaultParams()
{
    IRESMAN_MEMTCM_DEFAULTPARAM.baseConfig.size = 
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_MEMTCM_DEFAULTPARAM);
}

static void getInternalState() 
{
    Int sharedMemId = -1;
 
    _resmanInternalState = (IRESMAN_MEMTCM_InternalState *)SHM_getObj(
            _MEMTCM_lock, sizeof(IRESMAN_MEMTCM_InternalState),
            _MEMTCM_LOCKID, &setInternalState, &sharedMemId);

    if ((NULL != _resmanInternalState) && (-1 != sharedMemId)) {

        _resmanInternalState->sharedMemId = sharedMemId;
    }
    else {
        _resmanInternalState = NULL;
        sharedMemId = -1;
    }
}

/*
 *  ======== freeInternalState ========
 */
static void freeInternalState()
{
    CMEM_unregister(armtcmAddr, NULL);

    armtcmAddr = NULL;

    _resmanInternalState->numOpens--;

    if (_resmanInternalState->numOpens == 0) {
        //Do whatever, CMEM_free no longer needed 
    }

    SHM_freeObj(_MEMTCM_lock, (Void *)_resmanInternalState,
            (Int)_resmanInternalState->sharedMemId);
}

/*
 *  ======= setInternalState =======
 */
static Void setInternalState(Void * addr)
{
    IRESMAN_MEMTCM_InternalState * intState =
            (IRESMAN_MEMTCM_InternalState *)addr;
 
    if (NULL != intState) {
        intState->numOpens = 0;
        intState->armtcmAddr = NULL;
    }
}
/*
 *  @(#) ti.sdo.fc.ires.memtcm; 1, 0, 0,45; 12-1-2010 17:25:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

