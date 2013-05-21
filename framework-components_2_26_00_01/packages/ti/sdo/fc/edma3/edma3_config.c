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
 *  ======== edma3_config.c ========
 *  APIs to configure the EDMA3 resources for various scratch groups and obtain
 *  handles to the same
 *  Specifically for the use of IRES EDMA3CHAN protocol and DMAN3 when it uses
 *  a common Resource Manager layer
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include "edma3_config.h"

#include <ti/xdais/ialg.h>
#include <ti/sdo/edma3/rm/edma3_common.h>
#include <ti/sdo/edma3/rm/edma3_rm.h>

#include <ti/sdo/utils/trace/gt.h>

/* TODO: Fix the SEMKEY function */
/*
 *  Macro to create a Key from a seed value passed to it
 */
#define EDMA3_SEMKEY(seed) seed
#define EDMA3_MIN(a,b,c) ((a) <= (b) ? ((a) <= (c) ? (a) : (c)) \
        : ((b) <= (c) ? (b) : (c)))

__FAR__ GT_Mask ti_sdo_fc_edma3_GTMask;         /* GT Mask */

/*
 *  ======== EDMA3_ScratchTableEntry ========
 * Structure to store resource Manager associated with each algorithm
 */
typedef struct EDMA3_ScratchTableEntry {
    IALG_Handle alg;                        /* Algorithm handle */
    EDMA3_RM_Handle resourceManager;        /* Resource Manager handle */
    Void * sem;                             /* Semaphore being used by the
                                               Resource Manager */
    Int refCount;                           /* Counts the number of times the
                                               handle is requested */
    struct EDMA3_ScratchTableEntry * next;  /* Pointer to the next entry */
} EDMA3_ScratchTableEntry;

/*
 *  ======== EDMA3_Table ========
 *  Structure to store the Scratch Table Entries per scratch group
 */
typedef struct EDMA3_Table {
    EDMA3_ScratchTableEntry * entry;
    Bool populated;
} EDMA3_Table;

static EDMA3_Table _table[EDMA3_MAXGROUPS];     /* Table to hold the algHandle
                                                   and Resource Manager handle
                                                   info per scratch group */

static Int _initialized = 0;                    /* Initialization flag */

static EDMA3_RM_Handle _systemResourceManagerHandle = NULL;
                                                /* Handle to the system-wide
                                                   Resource Manager */
static Void * _systemResourceManagerSem = NULL; /* Semaphore to keep track of
                                                   System resource allocations*/

static Int _sysResourceManagerRefCount = 0;     /* Reference count for system
                                                   wide resource manager
                                                   handles requested */

static EDMA3_RM_InstanceInitConfig _regionConfig;
                                                                                                /* Stores the region specific
                                                                                                   configuration for the
                                                   Resource Manager handle */

/*
 * Initializes the EDMA3 Meta config module, creates the Resource Manager object
 */
static Int EDMA3_init();
/*
 * Exits the EDMA3 Meta config module, deletes the Resource Manager object
 */
static Int EDMA3_exit();

/*
 * Function to release an RM handle for a scratch group
 */
static EDMA3_RM_Result closeRMHandle(EDMA3_RM_Handle handle);

/*
 * Function to return an RM handle for a scratch group
 */
static EDMA3_RM_Handle openRMHandle(Int scratchId, Void * sem);

/*
 * Populates the scratch groups with respective EDMA resources
 */
static Int populateScratchGroup(Int scratchGroupId);

static Int unpopulateScratchGroup(Int scratchGroupId);

/*
 *  ======== EDMA3_getResourceManager ========
 *  Function to obtain the resource manager handle corresponding to this
 *  algorithm in this scratch group
 */
EDMA3_Handle EDMA3_getResourceManager(IALG_Handle algHandle,
        Int scratchGroupId)
{
    EDMA3_RM_Handle handle = NULL;
    EDMA3_ScratchTableEntry * entry = NULL;
    EDMA3_ScratchTableEntry * pEntry = NULL;
    IALG_MemRec memTab;
    Void * sem;

    if (0 == _initialized) {

        GT_init();

        GT_create(&ti_sdo_fc_edma3_GTMask, EDMA3_GTNAME);

        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Enter (alg=0x%x, scratchGroupId"
                "=%d)\n", algHandle, scratchGroupId);

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "EDMA3_getResourceManager>"
                        " Initializing EDMA3 Meta config module\n");

        if (1 != EDMA3_init()) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "EDMA3_getResourceManager> Error Intializaing EDMA3 Meta "
                    "config module \n");

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getResourceManager> Exit (handle=NULL)\n");

            return (NULL);
        }

        GT_assert(ti_sdo_fc_edma3_GTMask, _sysResourceManagerRefCount == 0);
        GT_assert(ti_sdo_fc_edma3_GTMask, _systemResourceManagerHandle == NULL);
        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "EDMA3_getResourceManager>"
                " Creating semaphore for System Resource Manager Handle\n");

        _systemResourceManagerSem = (Void *)EDMA3_semCreate
                (EDMA3_SEMKEY((Int)&_systemResourceManagerHandle), 1);

        /*
         *  The system semaphore needs to be unique, and different for a handle
         *  opened on any other region on this hardware.
         */
        if (NULL == _systemResourceManagerSem) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "EDMA3_getResourceManager> Error creating Semaphore\n");

            if (1 != EDMA3_exit()) {

                GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "EDMA3_getResourceManager> Error exiting EDMA3 Meta "
                        "config module\n");
            }

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getResourceManager> Exit (handle=NULL)\n");

            return (NULL);
        }

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "EDMA3_getResourceManager>"
                " Opening System Resource Manager Handle\n");

        _systemResourceManagerHandle = openRMHandle(-1,
                _systemResourceManagerSem);

        if (NULL == _systemResourceManagerHandle ) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "EDMA3_getResourceManager> Error opening System Resource "
                    "Manager Handle\n");

            /* Delete the Semaphore */
            EDMA3_semDelete(_systemResourceManagerSem);

                _systemResourceManagerSem = NULL;

            if (1 != EDMA3_exit()) {
                GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "EDMA3_getResourceManager> Error exiting EDMA3 Meta "
                        "config module\n");
            }

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getResourceManager> Exit (handle=NULL)\n");

            return (NULL);
        }

                _sysResourceManagerRefCount = 1;
        _initialized = 1;

        if (-1 == scratchGroupId) {
    
            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "EDMA3_getResourceManager> Return system Resource Manager "
                    "handle\n");
    
            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getResourceManager> Exit (handle=0x%x)\n",
                    _systemResourceManagerHandle);
    
            return ((EDMA3_Handle)_systemResourceManagerHandle);
        }

    }
    else {

        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Enter (alg=0x%x, scratchGroupId"
                "=%d)\n", algHandle, scratchGroupId);

        if (-1 == scratchGroupId) {
    
            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "EDMA3_getResourceManager> Return system Resource Manager "
                    "handle\n");
    
            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getResourceManager> Exit (handle=0x%x)\n",
                    _systemResourceManagerHandle);
    
            _sysResourceManagerRefCount++;
    
            return ((EDMA3_Handle)_systemResourceManagerHandle);
        }
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_getResourceManager> Look for matching entry for ALG 0x%x\n",
            algHandle);

    /* Search for entry */
    entry = _table[scratchGroupId].entry;
    pEntry = NULL;

    while (entry != NULL) {

        if (algHandle == entry->alg) {

                        entry->refCount++;

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "EDMA3_getResourceManager> Exit (handle=0x%x)\n",
                    entry->resourceManager);

            return ((EDMA3_Handle)(entry->resourceManager));
        }

        /* No matching entry was found, try next */
        pEntry = entry;
        entry = entry->next;
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_getResourceManager> Match not found, "
            "create new entry, get resource handle\n");

    memTab.size = sizeof(EDMA3_ScratchTableEntry);
    memTab.alignment = sizeof(int);
    memTab.space = IALG_ESDATA;
    memTab.attrs = IALG_PERSIST;

    if (FALSE == EDMA3_PARAMS.allocFxn(&memTab, 1)) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "EDMA3_getResourceManager> Could not allocate memory to add alg"
                " entry.\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Exit (handle=NULL)\n");

        return (NULL);
    }

    sem = (Void *)EDMA3_semCreate((Int)(EDMA3_SEMKEY(memTab.base)), 1);

    /*
     *  This semaphore is created per algorithm per scratch group. The algorithm
     *  owns a copy of the handle, there won't be contention for resources
     *  protected by this semaphore.
     */
    if (NULL == sem) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_getResourceManager> Error creating semaphore."
                " Free memory and exit\n");

        /* Free memory */
        EDMA3_PARAMS.freeFxn(&memTab, 1);

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Exit (handle=NULL)\n");

        return (NULL);
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
           "EDMA3_getResourceManager> Opening new Resource Manager Handle\n");

    handle = openRMHandle(scratchGroupId, sem);

    if (NULL == handle) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_getResourceManager> Error opening Resource "
                " Manager handle. Delete semaphore and free memory\n");

        /* Delete sem */
        EDMA3_semDelete(sem);

        /* Free memory */
        EDMA3_PARAMS.freeFxn(&memTab, 1);

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_getResourceManager> Exit (handle=NULL)\n");

        return (NULL);
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
           "EDMA3_getResourceManager> Populate new Table entry\n");

    entry = (EDMA3_ScratchTableEntry *)memTab.base;
    entry->alg = algHandle;
    entry->resourceManager = handle;
    entry->sem = sem;
    entry->refCount = 1;
    entry->next = NULL;

    if (NULL != pEntry) {
        pEntry->next = entry;
    }
    else {
        _table[scratchGroupId].entry = entry;
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_getResourceManager> Exit (handle=0x%x)\n",
            entry->resourceManager);

    return ((EDMA3_Handle)(handle));
}

/*
 *  ======== EDMA3_releaseResourceManager ========
 *  Function to release the Resource manager corresponding to this
 *  algorithm and this scratch group
 */
EDMA3_Result EDMA3_releaseResourceManager(IALG_Handle algHandle,
        Int scratchGroupId)
{
    IALG_MemRec memTab;
    EDMA3_RM_Handle handle = NULL;
    EDMA3_ScratchTableEntry * entry, * pEntry;
    EDMA3_Result status = EDMA3_SOK;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_releaseResourceManager> Enter (alg=0x%x, scratchGroupId=%d"
            ")\n", algHandle, scratchGroupId);

    if (-1 == scratchGroupId) {

        _sysResourceManagerRefCount--;

        if (0 == _sysResourceManagerRefCount) {

            /* Delete the RM handle */
            if (EDMA3_RM_SOK != closeRMHandle(_systemResourceManagerHandle)) {

                GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "EDMA3_releaseResourceManager> Error deleting"
                        " RM handle 0x%x\n", _systemResourceManagerHandle);

                status = EDMA3_E_RES_ALREADY_FREE;
            }

            /* Delete the Semaphore */
            EDMA3_semDelete(_systemResourceManagerSem);

                        _systemResourceManagerHandle = NULL;
                _systemResourceManagerSem = NULL;

            if (!EDMA3_exit()) {

                GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "EDMA3_releaseResourceManager> Error deleting"
                        " RM Object\n");

                status =  EDMA3_E_RES_ALREADY_FREE;
            }
        }

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_releaseResourceManager> Exit (status=0x%x)\n",
                status);

        return (status);
    }

    /* Search for entry */
    entry = _table[scratchGroupId].entry;
    pEntry = NULL;

    while (entry != NULL) {

        if (algHandle == entry->alg) {
            handle = entry->resourceManager;
            break;
        }

        /* No matching entry was found, try next */
        pEntry = entry;
        entry = entry->next;
    }

    if (NULL == entry) {

/* TODO: Figure out if there is a better error for this */
        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "EDMA3_releaseResourceManager> Could not find "
                "Resource Manager handle corresponding to algHandle 0x%x "
                "in scratch group %d\n", algHandle, scratchGroupId);

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "EDMA3_releaseResourceManager> Exit (status=0x%x)\n",
                status);

        return (EDMA3_E_RES_ALREADY_FREE);
    }

    entry->refCount--;

    GT_3trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_releaseResourceManager> (alg=0x%x, scratchGroupId=%d) "
            "entry->refCount=%d\n", algHandle, scratchGroupId, entry->refCount);

    if (entry->refCount <= 0) {

        GT_2trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_releaseResourceManager> Closing RM Handle (alg=0x%x, "
            "scratchGroupId=%d)\n", algHandle, scratchGroupId);

        /* Close the RM handle */
        if(EDMA3_RM_SOK != closeRMHandle(handle)) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "EDMA3_releaseResourceManager> Error deleting"
                    " RM handle 0x%x\n", handle);
        }

        /* Delete the Semaphore */
        EDMA3_semDelete(entry->sem);

        /* Fix the linked list */
        if (NULL != pEntry) {
            pEntry->next = entry->next;
        }
        else {
            _table[scratchGroupId].entry = entry->next;
        }

        /* Free the memory for this entry */
        memTab.base = entry;
        memTab.size = sizeof(EDMA3_ScratchTableEntry);
        memTab.alignment = 4;
        memTab.space = IALG_ESDATA;
        memTab.attrs = IALG_PERSIST;

        EDMA3_PARAMS.freeFxn(&memTab, 1);

        entry = NULL;
    }

/* TODO: Before closing the RM handle, can check if this is the last alg
         in the scratch group, and if so, can release the resources abck
         to the system */

    if ( NULL == _table[scratchGroupId].entry) {

        /* No more RM handles requesting this resource, release resources
           back to the system */
        if (!(unpopulateScratchGroup(scratchGroupId))) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "openRMHandle> Error releasing scratch group resources"
                    " back to the system\n");

            status = EDMA3_E_RES_ALREADY_FREE;
        }
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "EDMA3_releaseResourceManager> Exit (status=%d)\n", status);

    return (EDMA3_SOK);
}

/*
 *  ======== EDMA3_exit() ========
 *  Exits the EDMA3 Meta config module, deletes the Resource Manager object
 */
Int EDMA3_exit()
{

    Int i;
    Int status = 1;
    EDMA3_ScratchTableEntry * entry;

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "EDMA3_exit> Enter\n");

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_exit> Initializing table of Resource Manager handles\n");

    for (i = 0; i < EDMA3_MAXGROUPS; i++) {

        entry = _table[i].entry;

        while (NULL != entry ) {

            entry->alg = NULL;

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "EDMA3_exit> Closing resource manager handle 0x%x\n",
                    entry->resourceManager);

            if (EDMA3_RM_SOK != closeRMHandle(entry->resourceManager)) {

                GT_1trace(ti_sdo_fc_edma3_GTMask, GT_6CLASS,
                        "EDMA3_exit> Error closing resource manager handle "
                        "0x%x\n", entry->resourceManager);

                status = 0;
            }

            EDMA3_semDelete(entry->sem);
            entry = entry->next;
        }

        _table[i].entry = NULL;
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_exit> Deleting resource manager object\n");

   /* Delete the Resource Manager object */
    if (EDMA3_SOK != EDMA3_deleteResourceManagerObject()) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_6CLASS,
                "EDMA3_exit> Error deleting resource manager object\n");

        status = 0;
    }

    _initialized = 0;

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "EDMA3_exit> Exit(status=%d)\n",
            status);

    return (status);
}

/*
 *  ======== EDMA3_init() ========
 *  Initializes the EDMA3 Meta config module, creates the Resource Manager
 *  object
 */
Int EDMA3_init()
{

    Int i,k;

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "EDMA3_init> Enter\n");

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "EDMA3_init> Initializing table of Resource Manager handles\n");

    for (i = 0; i < EDMA3_MAXGROUPS; i++) {

        _table[i].entry = NULL;
        _table[i].populated = FALSE;

        for( k =0; k < EDMA3_MAX_TCC_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownTccs[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdTccs[k] = 0x0;
        }

        for( k =0; k < EDMA3_MAX_DMA_CHAN_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownDmaChannels[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdDmaChannels[k] = 0x0;
        }

        for( k =0; k < EDMA3_MAX_PARAM_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownPaRAMSets[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdPaRAMSets[k] = 0x0;
        }

        for( k =0; k < EDMA3_MAX_QDMA_CHAN_DWRDS; k++) {
            EDMA3_scratchResourceConfig[i].ownQdmaChannels[k] = 0x0;
            EDMA3_scratchResourceConfig[i].resvdQdmaChannels[k] = 0x0;
        }
    }

    /* Create the Resource Manager object */
    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "EDMA3_init> Create Resource"
                " Manager object\n");

    if (EDMA3_SOK != EDMA3_createResourceManagerObject()) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS, "EDMA3_init> Error "
                "creating Resource Manager object\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "EDMA3_init> Exit "
                "(status=0)\n");

        return (0);
    }

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "EDMA3_init> Exit "
           "(status=1)\n");

    return (1);
}


/*
 *  ======== populateScratchGroup ========
 *  Populates the Instance information for all the scratch groups
 */
static Int populateScratchGroup(Int scratchGroupId)
{
    Int k = 0;
    Int tccs = 0;
    Int edmas = 0;
    Int qdmas = 0;
    Int params = 0;
    Int tccIndex = 0;
    Int paramIndex = 0;
    Int edmaIndex = 0;
    Int qdmaIndex = 0;
    Int tccWord = 0;
    Int paramWord = 0;
    Int edmaWord = 0;
    Int qdmaWord = 0;
    Int minMarker = 0;
    short numReqTccs = 0;
    short reqTccs[64];
    Int count = 0;

    EDMA3_RM_Result rmStatus;
    EDMA3_RM_ResDesc resObj;

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "poulateScratchGroups> Enter (scratchGroupId=%d)\n",
            scratchGroupId);

    if (_table[scratchGroupId].populated) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "poulateScratchGroups> "
                "Exit (status=1)\n");

        return (1);
    }

    tccs = EDMA3_tccScratchSizes[scratchGroupId];
    edmas = EDMA3_edmaChanScratchSizes[scratchGroupId];
    qdmas = EDMA3_qdmaChanScratchSizes[scratchGroupId];
    params = EDMA3_paRamScratchSizes[scratchGroupId];

    minMarker = EDMA3_MIN(tccs, edmas, params);

    if (!( tccs + edmas + qdmas + params)) {
            goto populateEnd;
    }

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "populateScratchGroup> Allocating %d tccs %d edma %d "
            "qdma channels and %d params\n", tccs, edmas, qdmas, params);


    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "populateScratchGroup> Attempting symmetric allocation of EDMA "
            "channels and Tccs\n");

    resObj.type = EDMA3_RM_RES_TCC;
    resObj.resId = EDMA3_RM_RES_ANY;

    rmStatus = EDMA3_RM_allocResource(_systemResourceManagerHandle,
            &resObj);

    while ((EDMA3_RM_SOK == rmStatus) && (count < minMarker)) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                "populateScratchGroup> Allocated New Tcc %d\n",
                resObj.resId);

        resObj.type = EDMA3_RM_RES_DMA_CHANNEL;

        if (EDMA3_RM_SOK == EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            tccWord = (resObj.resId)/32;
            tccIndex = resObj.resId - (32 * tccWord);

            EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[tccWord] |=
                    (0x1 << tccIndex);

            EDMA3_scratchResourceConfig[scratchGroupId].ownDmaChannels
                    [tccWord] |= (0x1 << tccIndex);

            tccs--;
            edmas--;

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "populateScratchGroup> Obtained EDMA channel %d and "
                    "corresponding Tcc\n", resObj.resId);

            count++;
        }
        else {

            reqTccs[numReqTccs] = resObj.resId;
            numReqTccs++;

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "populateScratchGroup> Could not allocate EDMA channel"
                    " %d\n", resObj.resId);
        }

        resObj.type = EDMA3_RM_RES_TCC;
        resObj.resId = EDMA3_RM_RES_ANY;

        rmStatus = EDMA3_RM_allocResource(_systemResourceManagerHandle,
                &resObj);
    }

    if (numReqTccs > 0) {

        /* Free all extra Tccs requested */
        resObj.type = EDMA3_RM_RES_TCC;

        for (k = 0; k < numReqTccs; k++) {

            resObj.resId = reqTccs[k];

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "populateScratchGroup> Free Extra Tcc %d\n",
                    resObj.resId);

            if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                    _systemResourceManagerHandle, & resObj)) {

                GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "populateScratchGroup> Error freeing Tcc %d\n",
                    resObj.resId);

                /* Fatal error */
                return (0);
            }
        }
    }

    resObj.type = EDMA3_RM_RES_TCC;

    while(tccs) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "populateScratchGroup> Error allocating tcc %d\n",
                    resObj.resId);

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "populateScratchGroup> Exit (status=0)\n");

            return (0);
        }

        tccWord = (resObj.resId)/32;
        tccIndex = resObj.resId - (32 * tccWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[tccWord] |=
                (0x1 << tccIndex);

        tccs--;
    }

    if (tccs) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "populateScratchGroup> Error allocating TCCs for scratch "
                "group %d\n",scratchGroupId);

        goto populateEnd;
    }

    resObj.type = EDMA3_RM_RES_DMA_CHANNEL;

    while(edmas ) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "populateScratchGroup> Error allocating edma channel "
                    "%d\n",resObj.resId);

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "populateScratchGroup> Exit (status=0)\n");

            return (0);
        }

        edmaWord = (resObj.resId)/32;
        edmaIndex = resObj.resId - (32 * edmaWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownDmaChannels[edmaWord]
            |= (0x1 << edmaIndex);
        edmas--;
    }

    if (edmas) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "populateScratchGroup> Error allocating EDMA channels for"
                " scratch group %d\n",scratchGroupId);

        goto populateEnd;
    }

    resObj.type = EDMA3_RM_RES_QDMA_CHANNEL;
    while(qdmas ) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "populateScratchGroup> Error allocating qdma channel "
                    "%d\n", resObj.resId);

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "populateScratchGroup> Exit (status=0)\n");

            return (0);
        }

        qdmaWord = (resObj.resId)/32;
        qdmaIndex = resObj.resId - (32 * qdmaWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownQdmaChannels[qdmaWord]
                |= (0x1 << qdmaIndex);

        qdmas--;
    }

    if (qdmas) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "populateScratchGroup> Error allocating QDMA channels for"
                " scratch group %d\n",scratchGroupId);

        goto populateEnd;
    }

    resObj.type = EDMA3_RM_RES_PARAM_SET;
    while(params ) {

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_PARAMS.contigParams) {
            if (EDMA3_RM_SOK != EDMA3_RM_allocContiguousResource(
                    _systemResourceManagerHandle, &resObj, params)) {

                GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "populateScratchGroup> Error allocating %d "
                        "contiguous param sets\n", params);

                GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                        "populateScratchGroup> Exit (status=0)\n");

                return (0);
            }
            else {

                for (k = 0 ; k < params; k++) {

                    paramWord = (k + resObj.resId)/32;
                    paramIndex = (k + resObj.resId) - (32 * paramWord);

                    EDMA3_scratchResourceConfig[scratchGroupId].
                            ownPaRAMSets[paramWord] |= (0x1 << paramIndex);
                }

                params = 0;
                break;
            }
        }

        resObj.resId = EDMA3_RM_RES_ANY;

        if (EDMA3_RM_SOK != EDMA3_RM_allocResource(
                _systemResourceManagerHandle, &resObj)) {

            GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "populateScratchGroup> Error allocating param set %d\n",
                    resObj.resId);

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                    "populateScratchGroup> Exit (status=0)\n");

            return (0);
        }

        paramWord = (resObj.resId)/32;
        paramIndex = resObj.resId - (32 * paramWord);

        EDMA3_scratchResourceConfig[scratchGroupId].ownPaRAMSets[paramWord]
                |= (0x1 << paramIndex);

        params--;
    }

    if (params) {

        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "populateScratchGroup> Error allocating PaRAMs for"
                " scratch group %d\n",scratchGroupId);
    }

populateEnd:
    if (tccs + edmas + params + qdmas) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "populateScratchGroup> Error allocating resources\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "populateScratchGroup> Exit (status=0)\n");

        return (0);
    }

    _table[scratchGroupId].populated = TRUE;

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
           "populateScratchGroup> Exit (status=1)\n");

    return (1);
}

/*
 *  ======== openRMHandle ========
 *  Opens a new RM handle for a particular scratch group
 */
static EDMA3_RM_Handle openRMHandle(Int scratchId, Void * sem )
{
    EDMA3_RM_Handle handle;
    EDMA3_RM_Result status;
    EDMA3_RM_Param initParam;
    EDMA3_RM_IoctlCmd ioctlCmd = EDMA3_RM_IOCTL_SET_PARAM_CLEAR_OPTION;

    GT_2trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "openRMHandle> Enter (scratchId=%d, sem=0x%x)\n", scratchId, sem);

    initParam.isMaster = 0;         /* ? This module is never the master */

    if (-1 == scratchId) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "openRMHandle> System "
                "RM handle requested\n");

        initParam.rmInstInitConfig = (EDMA3_RM_InstanceInitConfig *)
                EDMA3_PARAMS.regionConfig;

        initParam.regionId = EDMA3_PARAMS.regionId;
    }
    else {

/* TODO: Adding some book keeping from the Region Config would let us expand the
         resources allocated as per the first requesting Alg in that scratch
         Group. (new API will be required for that in this MODULE to share
         that information)
 */

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "openRMHandle>"
                " Populating Scratch Groups with Resources\n");

        if (!(populateScratchGroup(scratchId))) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                    "openRMHandle> Error populating RM scratch groups\n");

            if (EDMA3_RM_SOK != closeRMHandle(_systemResourceManagerHandle)) {

                GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "openRMHandle> Error deleting RM handle 0x%x\n",
                        _systemResourceManagerHandle);
            }

            _systemResourceManagerHandle = NULL;

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
                    "openRMHandle> Deleting System semaphore\n");

            EDMA3_semDelete(_systemResourceManagerSem);

                _systemResourceManagerSem = NULL;

            if (1 != EDMA3_exit()) {

                GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                        "openRMHandle> Error exiting EDMA3 Meta config module"
                        "\n");
            }

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "openRMHandle> Exit "
                    "(handle=NULL)\n");

            return (NULL);
                }

        initParam.rmInstInitConfig = (EDMA3_RM_InstanceInitConfig *)
                &EDMA3_scratchResourceConfig[scratchId];

        initParam.regionId = EDMA3_PARAMS.regionId;
    }

    initParam.rmSemHandle = sem;

    initParam.regionInitEnable = 0; /* ? Not supporting region access etc */

    handle = EDMA3_RM_open(ti_sdo_fc_edma3_EDMA3_physicalId, &initParam, 
            &status);

    if (EDMA3_RM_SOK != status) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS, "openRMHandle> Error "
                "opening RM handle requested\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "openRMHandle> Exit "
                "(handle=NULL)\n");

        return (NULL);
    }

    status = EDMA3_RM_Ioctl(handle, ioctlCmd, (void *)EDMA3_PARAMS.globalInit,
            NULL);

    if (EDMA3_RM_SOK != status) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS, "openRMHandle> Error "
                "during IOCTL command EDMA3_RM_IOCTL_SET_PARAM_CLEAR_OPTION "
                "on EDMA3 Low Level Resource Manager\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "openRMHandle> Exit "
                "(handle=NULL)\n");

        return (NULL);
    }

    ioctlCmd = EDMA3_RM_IOCTL_SET_GBL_REG_MODIFY_OPTION;

    status = EDMA3_RM_Ioctl(handle, ioctlCmd, (void *)EDMA3_PARAMS.globalInit,
            NULL);

    if (EDMA3_RM_SOK != status) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS, "openRMHandle> Error "
                "during IOCTL command EDMA3_RM_IOCTL_SET_GBL_REG_MODIFY_OPTION "
                "on EDMA3 Low Level Resource Manager\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "openRMHandle> Exit "
                "(handle=NULL)\n");

        return (NULL);
    }

    if ((-1 == scratchId) && (NULL == EDMA3_PARAMS.regionConfig)) {

        if (EDMA3_RM_SOK != EDMA3_RM_getInstanceInitCfg(handle,
                &_regionConfig)) {

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS, "openRMHandle> Error "
                    "trying to get Region information from EDMA3 RM\n");

            GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "openRMHandle> Exit "
                    "(handle=NULL)\n");

            return (NULL);
        }

        EDMA3_PARAMS.regionConfig = (EDMA3_InstanceInitConfig * )&_regionConfig;
    }

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "openRMHandle> Exit "
            "(handle=0x%x)\n", handle);

    return (handle);
}

/*
 *  ========  closeRMHandle ========
 *  Closes the RM Handle for a particular scratch group
 */
static EDMA3_RM_Result closeRMHandle(EDMA3_RM_Handle handle)
{
    EDMA3_RM_Result status = EDMA3_RM_SOK;

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "closeRMHandle> Enter "
            "(handle=0x%x)\n", handle);

    status = EDMA3_RM_close(handle, NULL);

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER, "closeRMHandle> Exit "
            "(status=0x%x)\n", status);

    return (status);
}

/*
 *  ======== unpopulateScratchGroup ========
 *  Unpopulates the scratch resources for the scratch group
 */
static Int unpopulateScratchGroup(Int scratchGroupId)
{
    Int i,j = 0;
    Int tccs = 0;
    Int edmas = 0;
    Int qdmas = 0;
    Int params = 0;
    Int resourceWord = 0;
    Int status = 1;

    EDMA3_RM_ResDesc resObj;

    GT_1trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
            "unpoulateScratchGroups> Enter (scratchGroupId=%d)\n",
            scratchGroupId);

    if (!(_table[scratchGroupId].populated)) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS, "unpoulateScratchGroups> "
                "Exit (status=0)\n");

        return (0);
    }

    tccs = EDMA3_tccScratchSizes[scratchGroupId];
    edmas = EDMA3_edmaChanScratchSizes[scratchGroupId];
    qdmas = EDMA3_qdmaChanScratchSizes[scratchGroupId];
    params = EDMA3_paRamScratchSizes[scratchGroupId];

    if (!( tccs + edmas + qdmas + params)) {
            goto unpopulateEnd;
    }

    GT_4trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
            "unpopulateScratchGroup> Freeing %d tccs %d edma %d "
            "qdma channels and %d params\n", tccs, edmas, qdmas, params);

    resObj.type = EDMA3_RM_RES_TCC;

    for (i = 0; i < EDMA3_MAX_TCC_DWRDS; i++) {
        if (EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[i] == 0x0) {
            continue;
        }
        else {
            resourceWord =
                    EDMA3_scratchResourceConfig[scratchGroupId].ownTccs[i];
            for (j = 0; j < 32; j++) {
                if (resourceWord & (0x1 << j)) {
                    resObj.resId = i * 32 + j;
                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {
                        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                                "unpopulateScratchGroup> Error freeing tcc %d\n"                                , resObj.resId);
                        status = 0;
                    }
                }
            }
        }
    }

    resObj.type = EDMA3_RM_RES_DMA_CHANNEL;

    for (i = 0; i < EDMA3_MAX_DMA_CHAN_DWRDS; i++) {
        if (EDMA3_scratchResourceConfig[scratchGroupId].ownDmaChannels[i] ==
                0x0) {
            continue;
        }
        else {
            resourceWord = EDMA3_scratchResourceConfig[scratchGroupId].
                    ownDmaChannels[i];
            for (j = 0; j < 32; j++) {

                if (resourceWord & (0x1 << j)) {

                    resObj.resId = i * 32 + j;
                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {

                        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                                "unpopulateScratchGroup> Error freeing DMA %d\n"                                , resObj.resId);
                        status = 0;
                    }
                }
            }
        }
    }

    resObj.type = EDMA3_RM_RES_QDMA_CHANNEL;

    for (i = 0; i < EDMA3_MAX_QDMA_CHAN_DWRDS; i++) {

        if (EDMA3_scratchResourceConfig[scratchGroupId].ownQdmaChannels[i] ==
                0x0) {
            continue;
        }
        else {

            resourceWord = EDMA3_scratchResourceConfig[scratchGroupId].
                    ownQdmaChannels[i];

            for (j = 0; j < 32; j++) {

                if (resourceWord & (0x1 << j)) {

                    resObj.resId = i * 32 + j;

                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {

                        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                                "unpopulateScratchGroup> Error freeing DMA %d\n"                                , resObj.resId);
                        status = 0;
                    }
                }
            }
        }
    }

    resObj.type = EDMA3_RM_RES_PARAM_SET;

    for (i = 0; i < EDMA3_MAX_PARAM_DWRDS; i++) {

        if (EDMA3_scratchResourceConfig[scratchGroupId].ownPaRAMSets[i] ==
                0x0) {
            continue;
        }
        else {

            resourceWord = EDMA3_scratchResourceConfig[scratchGroupId].
                    ownPaRAMSets[i];

            for (j = 0; j < 32; j++) {

                if (resourceWord & (0x1 << j)) {

                    resObj.resId = i * 32 + j;

                    if (EDMA3_RM_SOK != EDMA3_RM_freeResource(
                            _systemResourceManagerHandle, &resObj)) {

                        GT_1trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                                "unpopulateScratchGroup> Error freeing PARAM %d"
                                "\n", resObj.resId);
                        status = 0;
                    }
                }
            }
        }
    }

unpopulateEnd:
    if (status == 0) {

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_7CLASS,
                "unpopulateScratchGroup> Error freeing resources\n");

        GT_0trace(ti_sdo_fc_edma3_GTMask, GT_ENTER,
                "unpopulateScratchGroup> Exit (status=0)\n");

        return (0);
    }

    _table[scratchGroupId].populated = FALSE;

    GT_0trace(ti_sdo_fc_edma3_GTMask, GT_2CLASS,
           "unpopulateScratchGroup> Exit (status=1)\n");

    return (1);
}

EDMA3_Result EDMA3_getBaseAddress(EDMA3_Handle hEdmaResMgr,
        EDMA3_Cntrlr_PhyAddr controllerId, unsigned int *phyAddress)
{
    return ((EDMA3_Result)EDMA3_RM_getBaseAddress((EDMA3_RM_Handle)hEdmaResMgr,
            (EDMA3_RM_Cntrlr_PhyAddr)controllerId, phyAddress));
}

EDMA3_Result EDMA3_getCCRegister(EDMA3_Handle hEdmaResMgr,
        unsigned int regOffset, unsigned int *regValue)
{
    return ((EDMA3_RM_Result)EDMA3_RM_getCCRegister(
            (EDMA3_RM_Handle)hEdmaResMgr, regOffset, regValue));
}

EDMA3_Result EDMA3_allocResource(EDMA3_Handle hEdmaResMgr,
                                        EDMA3_ResDesc *resObj)
{
    return ((EDMA3_Result)(EDMA3_RM_allocResource((EDMA3_RM_Handle)hEdmaResMgr,
            (EDMA3_RM_ResDesc *)resObj)));
}

EDMA3_Result EDMA3_freeResource(EDMA3_Handle hEdmaResMgr,
        const EDMA3_ResDesc *resObj)
{
    return ((EDMA3_Result)(EDMA3_RM_freeResource((EDMA3_RM_Handle)
            hEdmaResMgr, (const EDMA3_RM_ResDesc *)resObj)));
}

EDMA3_Result EDMA3_allocContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *firstResIdObj, unsigned int numResources)
{
    return ((EDMA3_Result)(EDMA3_RM_allocContiguousResource((EDMA3_RM_Handle) 
            hEdmaResMgr, (EDMA3_RM_ResDesc *)firstResIdObj, numResources)));
}

EDMA3_Result EDMA3_allocLogicalChannel(EDMA3_Handle hEdmaResMgr,
       EDMA3_ResDesc *lChObj, unsigned int *pParam, unsigned int *pTcc)
{
    return ((EDMA3_Result)EDMA3_RM_allocLogicalChannel((EDMA3_RM_Handle)
            hEdmaResMgr, (EDMA3_RM_ResDesc *)lChObj, pParam, pTcc));

}

EDMA3_Result EDMA3_freeLogicalChannel (EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *lChObj)
{
    return ((EDMA3_Result)EDMA3_RM_freeLogicalChannel((EDMA3_RM_Handle) 
            hEdmaResMgr, (EDMA3_RM_ResDesc *)lChObj));
}

EDMA3_Result EDMA3_freeContiguousResource(EDMA3_Handle hEdmaResMgr,
        EDMA3_ResDesc *firstResIdObj, unsigned int numResources)
{
    return ((EDMA3_Result)(EDMA3_RM_freeContiguousResource((EDMA3_RM_Handle) 
            hEdmaResMgr, (EDMA3_RM_ResDesc *)firstResIdObj, numResources)));
}


/*
 *  @(#) ti.sdo.fc.edma3; 3, 0, 0,152; 12-1-2010 17:24:42; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

