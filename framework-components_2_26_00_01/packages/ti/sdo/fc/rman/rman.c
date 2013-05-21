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
 *  ======== rman.c ========
 *  Generic IRES Resource Manager for managing IRES Resources and Protocols
 */

#include <xdc/std.h>

#include <ti/sdo/fc/dskt2/dskt2.h>

#include <string.h>

#include <ti/sdo/utils/trace/gt.h>

#ifdef xdc_target__os_Linux
#include <ti/sdo/fc/utils/lock.h>
#endif

/*
 * Since we will be pre-registering the NULL resource
 */
#include <ti/sdo/fc/ires/nullresource/iresman_nullres.h>

#include "rman.h"


#ifdef xdc_target__os_Linux
#define _RMAN_ipcKeyBase 0x524D414E /* "RMAN" */

/* Id offset from _RMAN_ipcKeyBase to lock used for protecting RMAN object */
#define _RMAN_LOCKID (_RMAN_ipcKeyBase)

LockMP_Handle _RMAN_lock;

#else

#define LockMP_acquire(x)
#define LockMP_release(x)
#define LockMP_create(x)
#define LockMP_delete(x)

#endif  /* xdc_target__os_Linux */

GT_Mask ti_sdo_fc_rman_GTMask;
#define CURTRACE ti_sdo_fc_rman_GTMask

extern IRES_Status RMAN_autoRegister();

/*
 *  ======== RMAN_TableState ========
 *  State information about the RMAN_Table that holds all the Resource Manager
 *  entries
 */
typedef struct RMAN_TableState {

    short tableSize;              /* Current size of Resource Manager table */

    short tableIndex;             /* Index pointing to the next free entry */

    short freeIndex;              /* Index pointing to the last free entry in
                                      Free table */
} RMAN_TableState;

static RMAN_TableState resTable;  /* Resource Manager table (IRESMAN impl.) */

static short rmanInit = 0;                    /* Count of RMAN_init calls */
static IRES_Status initStatus = IRES_ENOINIT; /* Outcome of RMAN_init */

/* Array holding yield functions for each scratch group */
static RMAN_YieldArgs rmanYieldArgs[DSKT2_NUM_SCRATCH_GROUPS + 1];

/* Function that checks if two versions are compatibile */
static Bool checkRevision(IRES_ProtocolRevision *rev1,
        IRES_ProtocolRevision *rev2);

/* Function that finds a IRESMAN implementation corresponding to alg's request*/
static IRESMAN_Fxns * getResman(String name, IRES_ProtocolRevision * revision);

static Void *myAlloc(size_t size, size_t align);
static Void myFree(Ptr addr, size_t size);

/*
 *  ======== RMAN_assignResources ========
 *  Assign resources to the algorithm indicated by alg. The resource
 *  requirements can be determined by using the IRES_Fxns implementation
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
IRES_Status RMAN_assignResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    Int              numResources;
    Int              k;
    Int              n = 0;
    size_t           resDescSize;
    IRESMAN_Fxns   * resman = NULL;
    IRES_Status      status = IRES_OK;
    IRES_Status      freeStatus = IRES_OK;
    IRES_Status      algStatus = IRES_OK;
    IRES_YieldFxn    yieldFxn = NULL;
    IRES_YieldArgs * yieldArgs = NULL;
    IRES_ResourceDescriptor * resDesc = NULL;


    if (initStatus != IRES_OK) {
        if (rmanInit > 0) {
            /* Only call GT if initialized */
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> "
                    "RMAN_init call hasn't happened successfully. Please "
                    "initialize RMAN before calling any other RMAN API\n");

            GT_0trace(CURTRACE, GT_ENTER, "RMAN_assignResources> "
                    "Exit (status=IRES_ENOINIT)\n");
        }
        return (IRES_ENOINIT);
    }

    GT_assert(CURTRACE, resFxns != NULL);
    GT_assert(CURTRACE, RMAN_PARAMS.allocFxn != NULL);
    GT_assert(CURTRACE, RMAN_PARAMS.freeFxn != NULL);

    GT_3trace(CURTRACE, GT_ENTER, "RMAN_assignResources> "
            "Enter (alg=0x%x, resFxns=0x%x, scratchGroupId=%d)\n",
            alg, resFxns, scratchGroupId);

    /*
     *  Get resource requirements of the algorithm
     */
    numResources = (resFxns->numResourceDescriptors)(alg);
    resDescSize = numResources * sizeof(IRES_ResourceDescriptor);

    /* Allocate memory to hold algorithm's resource descriptors */
    if ((resDesc = myAlloc(resDescSize, 0)) == NULL) {
        GT_1trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> "
                "Could not allocate memory size 0x%x in space "
                "IALG_EXTERNAL of type IALG_PERSIST\n", resDescSize);

        GT_0trace(CURTRACE, GT_ENTER, "RMAN_assignResources> "
                "Exit (status=IRES_ENOMEM)\n");

        return (IRES_ENOMEM);
    }

    algStatus = resFxns->getResourceDescriptors(alg, resDesc);

    if (algStatus != IRES_OK) {
        GT_3trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> Error obtaining "
                "Resource Descriptors [status: %d] from alg 0x%x, "
                "IRES interface 0x%x\n", algStatus, alg, resDesc);

        status = IRES_EALG;
    }

    if (status == IRES_OK) {

        /* For each requested resource */
        for (n = 0 ; n < numResources; n++) {

            /* If someone populated the resource descriptor improperly, bail */ 
            if ((resDesc[n].resourceName == NULL) || 
                    (resDesc[n].revision == NULL)) {

                GT_0trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> "
                        "Resource protocol and/or version were NULL. "
                        "Most likely an issue  with the algorithm's "
                        "getResourceRequestDescriptor implementation.\n");

                status = IRES_EALG;
                break;
            }

            resman = getResman(resDesc[n].resourceName, resDesc[n].revision);

            if (resman != NULL) {
                /*
                 *  Call getHandle on the IRESMAN implementation using
                 *  the protocolArgs extracted.
                 */
                GT_1trace(CURTRACE, GT_2CLASS, "RMAN_assignResources> Call "
                        "getHandle on the IRESMAN implementation 0x%x\n",
                        resman);

                /* Acquire lock */
                LockMP_acquire(_RMAN_lock);

                resDesc[n].handle = resman->getHandle(alg,
                        resDesc[n].protocolArgs, scratchGroupId, &status);

                /* Release lock */
                LockMP_release(_RMAN_lock);

                if (IRES_OK != status) {
                    break;
                }
            }
            else {
                GT_2trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> "
                        "Resource protocol %s and version 0x%x didn't match "
                        "any registered protocol and version\n",
                        resDesc[n].resourceName, resDesc[n].revision);

                status = IRES_ENOTFOUND;
                break;
            }
        }
    }

    /* n = number of resources allocated */

    /*
     * Return those handles to IALG using the appropriate IRES call
     */
    if (IRES_OK == status) {

        if (RMAN_PARAMS.yieldFxn != NULL) {
            yieldFxn = RMAN_PARAMS.yieldFxn;

            /* Return those handles to IALG using the appropriate IRES call */
            if (scratchGroupId != -1) {
                rmanYieldArgs[scratchGroupId].groupId = scratchGroupId;
                rmanYieldArgs[scratchGroupId].yieldFlag =
                        RMAN_PARAMS.yieldSamePriority;
                yieldArgs = (IRES_YieldArgs *)&(rmanYieldArgs[scratchGroupId]);
            }
            else {
                yieldArgs = (IRES_YieldArgs *)
                        &(rmanYieldArgs[DSKT2_NUM_SCRATCH_GROUPS]);
            }
        }

        /* Acquire lock */
        LockMP_acquire(_RMAN_lock);

        algStatus = resFxns->initResources(alg, resDesc, yieldFxn, yieldArgs);

        /* Release lock */
        LockMP_release(_RMAN_lock);

        if (algStatus != IRES_OK) {
            GT_1trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> "
                      "resFxns->initResources() failed [%d]\n", algStatus);
            status = IRES_EALG;
        }
    }

    if (status != IRES_OK) {
        /*
         *  Error somewhere in initialization of resource handles
         *  Free all allocated handles.
         */

        for (k = 0; k < n; k++) {
            resman = getResman(resDesc[k].resourceName, resDesc[k].revision);

            if (NULL == resman) {
                /* Resource table is messed up - bail out */
                GT_2trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> Could "
                        "not find IRESMAN matching resource %s version 0x%x\n",
                        resDesc[k].resourceName, resDesc[k].revision);

                status = IRES_EFAIL;
                break;
            }

            /* Acquire lock */
            LockMP_acquire(_RMAN_lock);

            freeStatus = resman->freeHandle(alg, resDesc[k].handle,
                    resDesc[k].protocolArgs, scratchGroupId);

            /* Release lock */
            LockMP_release(_RMAN_lock);

            if (freeStatus != IRES_OK) {
                /*
                 *  If we can't free the resource handle, something is really
                 *  messed up. Don't try to free anything else.
                 */
                status = IRES_EFAIL;
                GT_2trace(CURTRACE, GT_7CLASS, "RMAN_assignResources> Free "
                        "handle failed [%d] on IRESMAN implementation 0x%x\n",
                        status, resman);

                break;
            }
        }
    }

    if (resDesc) {
        myFree(resDesc, resDescSize);
    }

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_assignResources> Exit (status=%d)\n",
            status);

    return (status);
}


/*
 *  ======== RMAN_exit ========
 *  Exit the generic IRES RMAN and free the memory back to the Memory manager
 *  using which it was created.
 */
IRES_Status RMAN_exit()
{
    Int         i;
    IRES_Status status = IRES_OK;

    if (rmanInit == 0) {
        /* Can't call GT_trace if GT_init() was never called. */
        return (IRES_ENOINIT);
    }

    GT_0trace(CURTRACE, GT_ENTER, "RMAN_exit> Enter\n");

    if (--rmanInit == 0) {
        if (initStatus != IRES_OK) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_exit> RMAN_init call didn't "
                    "happened successfully. RMAN_exit will not unregister "
                    "any resources.\n");
            status = IRES_ENOINIT;
        }
        else {

            /* Acquire lock */
            LockMP_acquire(_RMAN_lock);

            GT_1trace(CURTRACE, GT_ENTER, "RMAN_exit> tableIndex = %d\n",
                    resTable.tableIndex);

            /* Unregister the entries */
            GT_0trace(CURTRACE, GT_ENTER,
                    "RMAN_exit> Unregistering resources\n");

            for (i = 0; i < resTable.tableIndex; i++) {
                if (RMAN_TABLE[i] != NULL) {

                    /* Even if there is an error, unregister the rest */
                    if ((status = RMAN_TABLE[i]->exit()) != IRES_OK) {
                        GT_2trace(CURTRACE, GT_7CLASS, "RMAN_exit> Error "
                                "unregistering the IRESMAN implementation "
                                "0x%x, status = %d\n",
                                RMAN_TABLE[i], status);
                        status = IRES_EFAIL;
                    }
                }
            }

            /* Release lock */
            LockMP_release(_RMAN_lock);

#ifdef xdc_target__os_Linux
            LockMP_delete(_RMAN_lock);
            _RMAN_lock = NULL;
#endif
        }
    }

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_exit> Exit (status=%d)\n", status);

    return (status);
}

/*
 *  ======== RMAN_freeResources ========
 *  Free resources held by the algorithm resource handle
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
IRES_Status RMAN_freeResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    short           numResources;
    short           i;
    size_t          resDescSize;
    IRESMAN_Fxns  * resman = NULL;
    IRES_Status     status = IRES_OK;
    IRES_ResourceDescriptor * resDesc = NULL;

    if (initStatus != IRES_OK) {
        if (rmanInit > 0) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_freeResources> "
                    "RMAN_init call hasn't happened successfully. Please "
                    "initialize RMAN before calling any other RMAN API\n");

            GT_0trace(CURTRACE, GT_ENTER, "RMAN_freeResources> "
                    "Exit (status=IRES_ENOINIT)\n");
        }
        return (IRES_ENOINIT);
    }

    GT_assert(CURTRACE, resFxns != NULL);
    GT_assert(CURTRACE, RMAN_PARAMS.allocFxn != NULL);
    GT_assert(CURTRACE, RMAN_PARAMS.freeFxn != NULL);

    GT_3trace(CURTRACE, GT_ENTER, "RMAN_freeResources> Enter "
            "(alg=0x%x, resFxns=0x%x, scratchGroupId=%d)\n", alg,
            resFxns, scratchGroupId);


    /*
     *  Get resource descriptors held by the algorithm
     */
    numResources = (resFxns->numResourceDescriptors)(alg);
    resDescSize = numResources * sizeof(IRES_ResourceDescriptor);

    /* Allocate memory for algorithm's resource descriptors */
    if ((resDesc = myAlloc(resDescSize, 0)) == NULL) {
        GT_0trace(CURTRACE, GT_7CLASS, "RMAN_freeResources> Memory "
                "allocation failed\n");

        status = IRES_ENOMEM;
    }

    if (status == IRES_OK) {
        if (IRES_OK != (resFxns->getResourceDescriptors(alg, resDesc))) {

            GT_2trace(CURTRACE, GT_7CLASS, "RMAN_freeResources> Error "
                    "obtaining Resource Descriptors from alg 0x%x with IRES "
                    "interface 0x%x\n", alg, resDesc);

            status = IRES_ENORESOURCE;
        }
    }

    if (status == IRES_OK) {
        /* Deinit the Resources that were granted to the algorithm */
        if (IRES_OK != (resFxns->deinitResources(alg, resDesc))) {

            GT_2trace(CURTRACE, GT_7CLASS, "RMAN_freeResources> "
                    "De-init failed on alg 0x%x IRES interface 0x%x\n",
                    alg, resDesc);

            status = IRES_EALG;
        }

        for (i = 0 ; i < numResources; i++) {
            resman = getResman(resDesc[i].resourceName, resDesc[i].revision);

            if (NULL == resman) {
                GT_2trace(CURTRACE, GT_7CLASS, "RMAN_freeResources> IRESMAN "
                        "handle not found for resource %s version 0x%x\n",
                        resDesc[i].resourceName, resDesc[i].revision);

                status = IRES_ENOTFOUND;
            }
            else {
                /*
                 *  Call freeHandle on resman Implementation and deinit
                 *  resources held by the algorithm
                 */

                /* Acquire lock */
                LockMP_acquire(_RMAN_lock);

                status = resman->freeHandle(alg, resDesc[i].handle,
                        resDesc[i].protocolArgs, scratchGroupId);

                /* Release lock */
                LockMP_release(_RMAN_lock);
    
                if (status != IRES_OK) {
                    /* TODO: Some SYS ABORT type error here */
                    GT_1trace(CURTRACE, GT_7CLASS,
                            "RMAN_freeResources> Free handle failed on IRESMAN"
                            " implementation 0x%x\n", resman);

                    status = IRES_EFAIL;
                }
            }
        }
    }

    if (resDesc) {
        myFree(resDesc, resDescSize);
    }

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_freeResources> Exit (status=%d)\n",
            status);

    return (status);
}

/*
 *  ======== RMAN_init ========
 *  Initialize the RMAN object with static information from the headers/
 *  configuration etc. This function has to return successfully before the
 *  other APIs can be called
 */
IRES_Status RMAN_init()
{
    Int            i = 0;
    IRES_Status    status;
    IRESMAN_Params nullParams;

    /* Ensure it is called/initialized at least once */
    if (rmanInit++) {
        GT_0trace(CURTRACE, GT_ENTER, "RMAN_init> Enter\n");
        GT_0trace(CURTRACE, GT_ENTER, "RMAN_init> Exit (status=IRES_OK)\n");

        /* TODO: Return IRES_OK even if RMAN_init() failed earlier? */
        return (IRES_OK);
    }

    GT_init();
    GT_create(&CURTRACE, RMAN_GTNAME);
    GT_0trace(CURTRACE, GT_ENTER, "RMAN_init> Enter\n");

    if ((NULL == RMAN_PARAMS.allocFxn) || (NULL == RMAN_PARAMS.freeFxn)) {
        GT_0trace(CURTRACE, GT_7CLASS, "RMAN_init> RMAN_PARAMS not "
                "configured with allocFxn and freeFxn functions\n");

        initStatus = IRES_ENOMEM;
    }
    else {
        /* Set initStatus to IRES_OK so RMAN_register() can succeed. */
        initStatus = IRES_OK;
    }

#ifdef xdc_target__os_Linux
    if (initStatus == IRES_OK) {
        /* Create a lock for protecting RMAN_data object */
        _RMAN_lock = LockMP_create(_RMAN_LOCKID);

        GT_1trace(CURTRACE, GT_ENTER, "RMAN_init> _RMAN_lock = 0x%lx\n",
                _RMAN_lock);

        if (_RMAN_lock == NULL) {
            GT_1trace(CURTRACE, GT_7CLASS,
                    "RMAN_init> Failed to create IPC lock, key = 0x%x\n",
                    _RMAN_LOCKID);

            initStatus = IRES_EFAIL;            
        }
    }
#endif

    if (initStatus == IRES_OK) {
        /*
         *  Register the NULL resource.
         */
        resTable.tableSize = RMAN_PARAMS.numRegistries;

        /* Initialize the registry table and the free index table */
        for (i = 0; i < resTable.tableSize; i++) {
            RMAN_TABLE[i] = NULL;
            RMAN_FREE_ENTRIES[i] = 0;
        }

        resTable.tableIndex = 0;
        resTable.freeIndex = -1;

        nullParams.allocFxn = RMAN_PARAMS.allocFxn;
        nullParams.freeFxn = RMAN_PARAMS.freeFxn;
        nullParams.size = sizeof(IRESMAN_Params);

        status = RMAN_register(&IRESMAN_NULLRES, &nullParams);
        if (status != IRES_OK) {
            GT_1trace(CURTRACE, GT_7CLASS, "RMAN_init> Register "
                    "failed on NULL IRESMAN implementation: %d\n", status);

            initStatus = status;
        }
    }

    if (initStatus == IRES_OK) {

        /* In this function, we can populate the RMAN_registryEntries,
           RMAN_registeryResmanArgs and fix RMAN_numRegistryEntries */  
        initStatus = RMAN_autoRegister();
    }

    /*
     * Static registration of Resource Registry entries
     */
    if ((initStatus == IRES_OK) && (RMAN_registryEntries != NULL)) {

        GT_assert(CURTRACE, RMAN_numRegistryEntries < resTable.tableSize);
        GT_0trace(CURTRACE, GT_2CLASS, "RMAN_init> Registering statically "
                "added resources\n");
        /*
         *  Copy the entries from the static configuration into the resource
         *  table.
         */
        for (i = 0; i < RMAN_numRegistryEntries; i++) {

            status = RMAN_register(RMAN_registryEntries[i],
                    RMAN_registryResmanArgs[i]);

            if (status != IRES_OK) {
                GT_2trace(CURTRACE, GT_7CLASS, "RMAN_init> Register failed on "
                        "IRESMAN implementation 0x%x, status: %d\n",
                        RMAN_registryEntries[i], status);

                initStatus = status;
                break;
            }
        }
    }

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_init> Exit (status=%d)\n", initStatus);

    return (initStatus);
}

/*
 *  ======== RMAN_register ========
 *  Register the protocol/protocol revision and the device specific resource
 *  manager implementation with the Resource Registry of the RMAN
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
IRES_Status RMAN_register(IRESMAN_Fxns * resmanFxns, IRESMAN_Params * initArgs)
{
    Int            index = -1;
    Int            i = 0;
    IRESMAN_Fxns * resman = NULL;
    String         protocolName = NULL;
    IRES_Status    status = IRES_OK;
    IRES_ProtocolRevision * revNo;

    if (initStatus != IRES_OK) {
        if (rmanInit) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_register> RMAN_init call "
                    "hasn't happened successfully. Please initialize RMAN "
                    "before registering resources\n");
            GT_0trace(CURTRACE, GT_ENTER, "RMAN_register> Exit "
                    "(status=IRES_ENOINIT)\n");
        }
        return (IRES_ENOINIT);
    }

    GT_2trace(CURTRACE, GT_ENTER, "RMAN_register> Enter (resmanFxns=0x%x, "
            "initArgs=0x%x)\n", resmanFxns, initArgs);

    GT_assert(CURTRACE, resmanFxns != NULL);

    protocolName = resmanFxns->getProtocolName();

    GT_assert(CURTRACE, protocolName != NULL);

    revNo = resmanFxns->getProtocolRevision();

    GT_4trace(CURTRACE, GT_4CLASS, "RMAN_register> Registering protocol %s "
            "revision (%d.%d.%d)\n", protocolName, revNo->Major, revNo->Source,
            revNo->Radius);

    /*
     * Use the protocolName and revisionNo to log the Resman Implementation
     * in the ResourceRegistry table.
     */

    /* Acquire lock */
    LockMP_acquire(_RMAN_lock);

    /*
     * First check the entire table to see if there are any duplicates
     */
    for (i = 0; i < resTable.tableIndex; i++) {

        if ((resman = RMAN_TABLE[i]) &&
                !strcmp(protocolName, RMAN_TABLE[i]->getProtocolName()) &&
                checkRevision(RMAN_TABLE[i]->getProtocolRevision(), revNo)) {

            /* Found a match */
            if (resmanFxns == RMAN_TABLE[i]) {
                /* Re-registering the same protocol, do nothing. */
                LockMP_release(_RMAN_lock);

                GT_0trace(CURTRACE, GT_ENTER, "RMAN_register> "
                        "Exit (status=IRES_EEXISTS)\n");

                return (IRES_OK);
            }

            /*
             * Re-registering a different protocol for an existing entry.
             * Replace current entry with new entry
             */
            index = i;

            if ((status = resman->exit()) != IRES_OK) {
                /* Release lock */
                LockMP_release(_RMAN_lock);

                GT_2trace(CURTRACE, GT_7CLASS, "RMAN_register> Exit failed on"
                        "IRESMAN implementation 0x%x, status: %d\n",
                        resman, status);
                GT_0trace(CURTRACE, GT_ENTER, "RMAN_register> Exit "
                        "(status=IRES_EFAIL)\n");

                return (status);
            }
            break;
        }
    }

    /* Registering a new protocol */
    if ((status = resmanFxns->init(initArgs)) != IRES_OK) {
        /* Release lock */
        LockMP_release(_RMAN_lock);

        GT_2trace(CURTRACE, GT_7CLASS, "RMAN_register> Init failed on "
                "IRESMAN implementation 0x%x, status: %d\n", resman, status);
        GT_0trace(CURTRACE, GT_ENTER, "RMAN_register> Exit "
                "(status=IRES_ENORESOURCE)\n");

        return (status);
    }

    if (index == -1) {
        /* Not found in table. Check for available entry in freeIndex table */
        if (-1 != resTable.freeIndex) {
            index = RMAN_FREE_ENTRIES[resTable.freeIndex];
            resTable.freeIndex--;
        }
        else {
            /* No free entries available, use new one in the registry table */

            /* Should never exceed pre configured table size */
            GT_assert(CURTRACE, index < resTable.tableSize);

            index = resTable.tableIndex;
            resTable.tableIndex++;
        }
    }

    /* Add the actual entry to the Resource table */
    RMAN_TABLE[index] = resmanFxns;

    /* Release lock */
    LockMP_release(_RMAN_lock);

    GT_0trace(CURTRACE, GT_ENTER, "RMAN_register> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

/*
 *  ======== RMAN_unregister ========
 *  Unregister the protocol and the corresponding resource manager
 *  implementation from the Resource Registry
 */
/* ARGSUSED - Directive to compiler to not complain about unused args */
IRES_Status RMAN_unregister(IRESMAN_Fxns * resmanFxns)
{
    Int     i = 0;
    String  protocolName = NULL;
    IRES_ProtocolRevision * revNo;

    if (initStatus != IRES_OK) {
        if (rmanInit > 0) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_unregister> "
                    "RMAN_init call hasn't happened successfully. Please "
                    "initialize RMAN before calling other RMAN APIs\n");

            GT_0trace(CURTRACE, GT_ENTER, "RMAN_unregister> "
                    "Exit (status=IRES_ENOINIT)\n");
        }

        return (IRES_ENOINIT);
    }

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_unregister> Enter (resmanFxns=0x%x)\n",
            resmanFxns);

    protocolName = resmanFxns->getProtocolName();
    revNo = resmanFxns->getProtocolRevision();

    GT_assert(CURTRACE, protocolName != NULL);

    LockMP_acquire(_RMAN_lock);

    /*
     * Search the table matching the protocolName and revision Number
     * with the entries
     */
    for (i = 0; i < resTable.tableIndex; i++) {

        /* Check for NULL before checking for protocol and revision */
        if ((RMAN_TABLE[i]) &&
                checkRevision(RMAN_TABLE[i]->getProtocolRevision(), revNo) &&
                !strncmp(protocolName, RMAN_TABLE[i]->getProtocolName(),
                        RMAN_PROTOCOLNAMESIZE)) {
            /* Found a match */
            break;
        }
    }

    if (i == resTable.tableIndex) {
        /* Entry not found */
        LockMP_release(_RMAN_lock);

        GT_0trace(CURTRACE, GT_7CLASS, "RMAN_unregister> Entry not found "
                "in table of registered IRESMAN implementations\n");

        GT_0trace(CURTRACE, GT_ENTER, "RMAN_unregister> Exit "
                "(status=IRES_ENOTFOUND)\n");

        return (IRES_ENOTFOUND);
    }

    /*
     *  Call the exit interface of the specific IResman implementation and
     *  delete that entry from the table
     */
    if (IRES_OK != (RMAN_TABLE[i])->exit()) {
        LockMP_release(_RMAN_lock);

        GT_1trace(CURTRACE, GT_7CLASS, "RMAN_unregister> Exit "
                "failed on IRESMAN implementation 0x%x\n", RMAN_TABLE[i]);

        GT_0trace(CURTRACE, GT_ENTER, "RMAN_unregister> Exit "
                "(status=IRES_EFAIL)\n");

        return (IRES_EFAIL);
    }

    /* Reset this entry in the entries table */
    RMAN_TABLE[i] = NULL;

    /* Since this table index is now available, add it to the freeTable */
    resTable.freeIndex++;

    /* Should never run out of space in free Table */
    GT_assert(CURTRACE, resTable.freeIndex < resTable.tableSize);

    RMAN_FREE_ENTRIES[resTable.freeIndex] = i;

    LockMP_release(_RMAN_lock);

    GT_0trace(CURTRACE, GT_ENTER, "RMAN_unregister> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

/*
 *  ======== RMAN_activateResource ========
 *  Activate resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_activateResource(IALG_Handle alg,
        IRES_Handle resourceHandle, IRES_Fxns * resFxns, Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        if (rmanInit > 0) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_activateResource> RMAN_init "
                    "call hasn't happened successfully. Please initialize "
                    "RMAN before calling any other RMAN API\n");
            GT_0trace(CURTRACE, GT_ENTER, "RMAN_activateResource> Exit "
                    "(status=IRES_ENOINIT)\n");
        }

        return (IRES_ENOINIT);
    }

    GT_4trace(CURTRACE, GT_ENTER, "RMAN_activateResource> Enter "
            "(alg=0x%x, resourceHandle=0x%x, resFxns=0x%x, "
            "scratchGroupId=%d\n", alg, resourceHandle, resFxns,
            scratchGroupId);

    status = resFxns->activateResource(alg, resourceHandle);

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_activateResource> Exit (status=%d)\n",
            status);

    return (status);
}

/*
 * ======== RMAN_activateAllResource ========
 * Activate all resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_activateAllResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        if (rmanInit == 0) {

            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_activateAllResources>"
                    " RMAN_init call hasn't happened successfully. Please "
                    "initialize RMAN before calling any other RMAN API\n");

            GT_0trace(CURTRACE, GT_ENTER, "RMAN_activateAllResources> "
                    "Exit (status=IRES_ENOINIT)\n");
        }

        return (IRES_ENOINIT);
    }

    GT_3trace(CURTRACE, GT_ENTER, "RMAN_activateAllResources> "
            "Enter (alg=0x%x, resFxns=0x%x, scratchGroupId=%d)\n",
            alg, resFxns, scratchGroupId);

    status = resFxns->activateAllResources(alg);

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_activateAllResources> "
            "Exit (status=%d)\n",status);

    return (status);
}

/*
 * ======== RMAN_deactivateResource ========
 * Deactivate the resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_deactivateResource(IALG_Handle alg,
        IRES_Handle resourceHandle, IRES_Fxns * resFxns, Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        if (rmanInit > 0) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_deactivateResource>"
                    " RMAN_init call hasn't happened successfully. Please "
                    "initialize RMAN before calling any other RMAN API\n");

            GT_0trace(CURTRACE, GT_ENTER, "RMAN_deactivateResource> "
                    "Exit (status=IRES_ENOINIT)\n");
        }
        return (IRES_ENOINIT);
    }

    GT_4trace(CURTRACE, GT_ENTER, "RMAN_deactivateResource> "
            "Enter (alg=0x%x, resourceHandle=0x%x, resFxns=0x%x, "
            "scratchGroupId=%d)\n", alg, resourceHandle, resFxns,
            scratchGroupId);

    status =  resFxns->deactivateResource(alg, resourceHandle);

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_deactivateResource> "
            "Exit (status=%d)\n", status);

    return (status);
}

/*
 *  ======== RMAN_deactivateAllResources ========
 *  Deactivate the resource
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Status RMAN_deactivateAllResources(IALG_Handle alg, IRES_Fxns * resFxns,
        Int scratchGroupId)
{
    IRES_Status status;

    if (initStatus != IRES_OK) {
        if (rmanInit == 0) {
            GT_0trace(CURTRACE, GT_7CLASS, "RMAN_deactivateAllResources> "
                    "RMAN_init call hasn't happened successfully. Please "
                    "initialize RMAN before calling any other RMAN API\n");

            GT_0trace(CURTRACE, GT_ENTER, "RMAN_deactivateAllResources> "
                    "Exit (status=IRES_ENOINIT)\n");
        }

        return (IRES_ENOINIT);
    }

    GT_3trace(CURTRACE, GT_ENTER, "RMAN_deactivateAllResources> "
            "Enter (alg=0x%x, resFxns=0x%x, scratchGroupId=%d)\n",
            alg, resFxns, scratchGroupId);

    status = resFxns->deactivateAllResources(alg);

    GT_1trace(CURTRACE, GT_ENTER, "RMAN_deactivateAllResources> "
            "Exit (status=%d)\n", status);

    return (status);
}

/*
 *  ======== checkRevision ========
 *  Checks of the versions of the protocols are compatible
 */
static Bool checkRevision(IRES_ProtocolRevision *rev1,
        IRES_ProtocolRevision *rev2)
{
    /* Currently simply check if the (Major) versions match exactly */
    return ((rev1->Major == rev2->Major) ? TRUE : FALSE);
}

/*
 *  ======== getResman ========
 *  Searches through valid entries of RMAN_TABLE to find a RESMAN corresponding
 *  to the name and revision of the protocol.
 */
static IRESMAN_Fxns * getResman(String name, IRES_ProtocolRevision * rev)
{
    IRESMAN_Fxns  *fxns = NULL;
    Int     j;

    /* Acquire lock */
    LockMP_acquire(_RMAN_lock);

    /*
     *  For each non-NULL RMAN_TABLE entry, compare protocolName and version
     *  number.
     */
    for (j = 0; j < resTable.tableIndex; j++) {
        if ((RMAN_TABLE[j]) &&
                !strcmp(name, RMAN_TABLE[j]->getProtocolName()) &&
                checkRevision(RMAN_TABLE[j]->getProtocolRevision(), rev)) {

            /* Found a match */
            fxns = RMAN_TABLE[j];
            break;
        }
    }

    /* Release lock */
    LockMP_release(_RMAN_lock);

    return (fxns);
}

/*
 *  ======== myAlloc ========
 *  Wrapper around RMAN_PARAMS.allocFxn.
 */
static Void *myAlloc(size_t size, size_t align)
{
    IALG_MemRec memTab;
    Void       *addr = NULL;

    memTab.size = size;
    memTab.alignment = align;
    memTab.space = IALG_EXTERNAL;
    memTab.attrs = IALG_PERSIST;

    if (RMAN_PARAMS.allocFxn(&memTab, 1)) {
        addr = memTab.base;
    }

    /* Make sure memory was allocated in the space we asked for */
    GT_assert(CURTRACE, (IALG_EXTERNAL == memTab.space));

    return (addr);
}

/*
 *  ======== myFree ========
 *  Wrapper around RMAN_PARAMS.freeFxn.
 */
static Void myFree(Ptr addr, size_t size)
{
    IALG_MemRec memTab;

    memTab.base = addr;
    memTab.size = size;
    memTab.alignment = 0;         /* Alignment shouldn't be needed here */
    memTab.space = IALG_EXTERNAL;
    memTab.attrs = IALG_PERSIST;

    RMAN_PARAMS.freeFxn(&memTab, 1);
}
/*
 *  @(#) ti.sdo.fc.rman; 2, 0, 0,207; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

