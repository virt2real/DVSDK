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
 *  ======== iresman_vicp2.c ========
 */

#include <xdc/std.h>

#ifdef xdc_target__os_Linux
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <ti/sdo/fc/utils/sharedMem.h>
#endif

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "ires_vicp2.h"
#include "iresman_vicp2.h"
#include "_vicp2.h"
#include "iresman_protocol_vicp2.h"
#include <ti/sdo/fc/utils/smgrmp.h>
#include <ti/sdo/utils/trace/gt.h>

GT_Mask ti_sdo_fc_ires_vicp2_GTMask;

#define IRESMAN_VICP2_RESOURCEFREE 0xFFFF
#define CURTRACE ti_sdo_fc_ires_vicp2_GTMask

#define VICP2_NUM_GROUPS 20 
#define VICP2_RESSIZE 0x200
#define VICP2_NUMRES ((VICP2_BUFSIZE)/(VICP2_RESSIZE))

typedef enum IRES_VICP2_RESOURCETYPE {
    IMX0,
    IMX1,
    MJCP,
    NSF    
} IRES_VICP2_RESOURCETYPE;

/*
 * Holds the internal state of an initialized object
 */
typedef struct IRESMAN_Vicp2_InternalState {

    Int IMX0busy;           
    Int IMX1busy;           
    Int MJCPbusy;           
    Int NSFbusy;           
                                    /* Keeps track of busy status of resource */
    short refCount[4];               
                                    /* Reference count of number of algs using
                                       the same resource */
    Int numOpens;
    Int sharedMemId;
    Void * base;
} IRESMAN_Vicp2_InternalState;

unsigned int _VICP2_buffOffsets[IRES_VICP2_NUMBUFFERS];
unsigned int _VICP2_buffLens[IRES_VICP2_NUMBUFFERS];

unsigned int _VICP2_regSize;
unsigned int _VICP2_bufSize;

/*
 * Key to obtain shared memory for this module 
 */
extern Int32 _VICP2_ipcKeyBase;
/*
 * Linuxutils module for VICP2 */ 
extern int VICP_init();
extern int VICP_exit();

/*
 * Flag indicating if GT (trace) is initialized
 */
static unsigned int gtInit = 0;

/*
 * Lock to guard access to critical sections 
 */
static LockMP_Handle _VICP2_lock = NULL;

/*
 * Represents the IRES EDMA3 Resource manager
 */
static IRESMAN_Vicp2_InternalState * _resmanInternalState = NULL;

/*
 * Memory alloc Function
 */
static IRESMAN_PersistentAllocFxn * _allocFxn = NULL;

/*
 * Memory free Function
 */
static IRESMAN_PersistentFreeFxn * _freeFxn = NULL;

#ifndef xdc_target__os_Linux

/*
 * For non-Linux, non-MP case, use statically allocated memory 
 */ 
static IRESMAN_Vicp2_InternalState _VICP2_internalState;     
#endif

static SMGRMP_Handle smgr = NULL;

static void getInternalState(); 
static void freeInternalState();
static void initializeBufferOffsets();

/**
 * Function to return the name of the protocol
 */
String IRESMAN_VICP2_getProtocolName()
{
    if (0 == gtInit) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.vicp2");

        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_getProtocolName> Enter\n");

    GT_1trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_getProtocolName> Exit "
            "(name=%s)\n", IRESMAN_VICP2_CONSTRUCTFXNS.getName());

    return (IRESMAN_VICP2_CONSTRUCTFXNS.getName());
}

/**
 * Function to return the revision of the protocol
 */
IRES_ProtocolRevision * IRESMAN_VICP2_getProtocolRevision()
{

    IRES_ProtocolRevision * version;

    if (0 == gtInit) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.vicp2");

        gtInit = 1;
    }

    GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_getProtocolRevision> Enter\n");
 
    version = IRESMAN_VICP2_CONSTRUCTFXNS.getRevision();

    GT_3trace(CURTRACE, GT_ENTER,
            "IRESMAN_VICP2_getProtocolRevision> Exit (version=(%d.%d.%d))"
            "\n", version->Major, version->Source, version->Radius);
 
    return (version);
}

/**
 * Function to initialize the device specific resource manager implementation
 */
IRES_Status IRESMAN_VICP2_init(IRESMAN_Params * initArgs) 
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
{

    SMGRMP_Attrs attrs;
    Int numResources, resourceId = -1;
    Bool smg_status = FALSE;

    IRESMAN_VicpParams * resmanArgs = (IRESMAN_VicpParams *)initArgs;

    if (0 == gtInit) {

        GT_init();

        GT_create(&CURTRACE, "ti.sdo.fc.ires.vicp2");

        gtInit = 1;
    }

    GT_1trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_init> Enter (initArgs=0x%x)\n",
            initArgs);

    GT_assert(CURTRACE, initArgs != NULL);

    if (NULL == _VICP2_lock) {

        /* Create a lock for protecting VICP internal state object */
        _VICP2_lock = LockMP_create(_VICP2_LOCKID);
 
        if (_VICP2_lock == NULL) {
 
            GT_1trace(CURTRACE, GT_7CLASS,
                    "IRESMAN_VICP2_init> Failed to create IPC lock, "
                    "key = 0x%x\n", _VICP2_LOCKID);

            GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_init> Exit (status="
                    "IRES_EFAIL)\n");
 
            return (IRES_EFAIL);
        }
    }

    getInternalState();

    if (NULL == _resmanInternalState) {

        GT_0trace(CURTRACE, GT_7CLASS,
                "IRESMAN_VICP2_init> Failed to obtain Internal state Object\n");

        GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_init> Exit (status="
                "IRES_EFAIL)\n");

        LockMP_delete(_VICP2_lock);

        return (IRES_EFAIL);
    }

    /*
     * Information regarding the memory allocation/free functions
     */
    _allocFxn = resmanArgs->baseConfig.allocFxn;

    _freeFxn = resmanArgs->baseConfig.freeFxn;

    /* 
     *  Check if already initialized
     */
    VICP_init();


    initializeBufferOffsets();

    _resmanInternalState->numOpens++;

    if (NULL == smgr) {

        attrs.numScratchGroups = VICP2_NUM_GROUPS + 1; //Adding another group
                                                       //for IRES_LATEACQUIRE. 
        attrs.numResources = (VICP2_NUMRES);
                                     /* One resource corresponds to a 1/2 K
                                        chunk of memory (0x200), Manage memory
                                        in chunks of 0x200 */
        attrs.lock = _VICP2_lock;

        attrs.key = (void *)_VICP2_MEMID;    /* A key specific to the resource 
                                                being managed */ 
        smgr = SMGRMP_create(&attrs);

        if (NULL == smgr) {

            GT_0trace(CURTRACE, GT_7CLASS, "IRESMAN_VICP2_init> Error creating"
                    " scratch resource manager.\n");

            GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_init> Exit (status="
                    "IRES_EFAIL)\n");

            LockMP_delete(_VICP2_lock);

            return (IRES_EFAIL);
        }

    }

    if ((_resmanInternalState->numOpens == 1) && (_VICP2_dm365)) {

/* TODO: */
        /* Managing VICP2_BUFSIZE of buffer space, need to pre-allocate
           the RSVD blocks */ 

        resourceId = (RSVD_REGS_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_REGS_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_BIMXREF_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_BIMXREF_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_PREDMEM_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_PREDMEM_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_MVMEM_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_MVMEM_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_SEQBUF1_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_SEQBUF1_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_SEQBUF2_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_SEQBUF2_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_SEQBUF3_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_SEQBUF3_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }

        resourceId = (RSVD_SEQDMEM_BASE)/(VICP2_RESSIZE); 
        GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
        numResources = (RSVD_SEQDMEM_LEN/VICP2_RESSIZE);

        smg_status = SMGRMP_alloc(smgr, NULL, &resourceId, numResources, -1);
        
        if (FALSE == smg_status) {
            goto allocFail;
        }
    }
    
    GT_0trace(CURTRACE,GT_ENTER, "IRESMAN_VICP2_init> Exit (status=IRES_OK)\n");

    return (IRES_OK);

allocFail:

    GT_0trace(CURTRACE, GT_7CLASS,
           "IRESMAN_VICP2_init>Failed to lock the RSVD buffers\n");

    GT_0trace(CURTRACE, GT_ENTER, "IRESMAN_VICP2_init> Exit "
           "(status=IRES_EFAIL)\n");
 
    return (IRES_EFAIL);
}

/**
 * Function called when RESMAN is no longer needed. Use it to free memory 
 * allocated etc
 */
IRES_Status IRESMAN_VICP2_exit() 
{
    GT_0trace(CURTRACE, GT_ENTER,
            "IRESMAN_VICP2_exit> Enter\n");
  
    GT_assert(CURTRACE, _resmanInternalState != NULL );

    _resmanInternalState->numOpens--;

    freeInternalState(); 

    _resmanInternalState = NULL;

    SMGRMP_delete(_VICP2_lock , smgr);

    LockMP_delete(_VICP2_lock);

    _VICP2_lock = NULL;

    smgr = NULL;

    GT_0trace(CURTRACE,GT_ENTER, "IRESMAN_VICP2_exit> Exit (status=IRES_OK)\n");

    return (IRES_OK);
}

/*
 *  Function that returns the IRES_Handle to the resource requested using the 
 *  IRES_ResourceProtocolArgs
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
IRES_Handle IRESMAN_VICP2_getHandles(IALG_Handle algHandle,   
        IRES_ProtocolArgs * protocolArgs, Int scratchGroupId,
        IRES_Status * status)
{
    IALG_MemRec protocolMemRecs[IRES_VICP2_MAXRESOURCES];
    IALG_MemRec constructHandleMemRec;
    IRESMAN_VICP2_ConstructHandleArgs * constructArgs = NULL; 
    IRES_Handle resourceHandle = NULL;
    Int numMemRecs = 0;
    Int i, numResources, resourceId = -1;
    Int toFreeBufIndex = -1;
    Int toFreeMemIndex = -1;
    unsigned int mem_beg = 0x0;
    unsigned int mem_end = 0x0;
    unsigned int buf_beg = 0x0;
    unsigned int buf_end = 0x0;    
    unsigned int buf_num = 0x0;    
    Int numBuffSwitches = 0;
    Bool smg_status = FALSE;

    /*
     * Cast the protocolArgs 
     */
    IRES_VICP2_ProtocolArgs * configArgs = 
            (IRES_VICP2_ProtocolArgs *) protocolArgs;

    GT_assert(CURTRACE, configArgs);

    if (_resmanInternalState == NULL) {

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_VICP2_getHandles> RMAN_register call has not "
                "happened successfully\n. Please register VICP2 resource "
                "with RMAN before requesting or releasing resources.\n");

        *status =  IRES_ENORESOURCE;

        return (NULL);
    }

    /*
     * Get IRES_VICP2 handle's memory requirements
     */
    numMemRecs = IRESMAN_VICP2_CONSTRUCTFXNS.getNumMemRecs
         ( (IRES_ProtocolArgs *)protocolArgs);

    GT_assert(CURTRACE, numMemRecs <= IRES_VICP2_MAXRESOURCES);

    /*
     * Allocate memory for the constructHandle Arguments
     */
    constructHandleMemRec.size = sizeof(IRESMAN_VICP2_ConstructHandleArgs);
    constructHandleMemRec.alignment = 4;
    constructHandleMemRec.space = IALG_EXTERNAL;
    constructHandleMemRec.attrs = IALG_PERSIST;

    if (FALSE == _allocFxn(&constructHandleMemRec, 1)) {
        *status =  IRES_ENOMEM;

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_VICP2_getHandles> Allocation for memory for " 
                "the VICP2 handle failed.\n");

        return (NULL);
    }

    GT_assert(CURTRACE, IALG_EXTERNAL == constructHandleMemRec.space);
    constructArgs = constructHandleMemRec.base;
    (constructArgs->args).size = sizeof(IRESMAN_VICP2_ConstructHandleArgs);

    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } 
    else if (configArgs->mode == IRES_LATEACQUIRE) {
        scratchGroupId = VICP2_NUM_GROUPS;
        GT_0trace(CURTRACE, GT_4CLASS,
                "IRESMAN_VICP2_getHandles> Requested IRES_LATEACQUIRE "
                "VICP resources. Ensure you \"lock\" resources using "
                "IRES RESUTILS API before using them for correct operation\n");
    } 

    
    if (-1 == scratchGroupId) {
        constructArgs->persistent = TRUE;
    }
    else {
        constructArgs->persistent = FALSE;
    } 

    if ( configArgs->requestIMX0 ) {
        if (_resmanInternalState->IMX0busy == IRESMAN_VICP2_RESOURCEFREE){
            _resmanInternalState->IMX0busy = scratchGroupId;
            _resmanInternalState->refCount[IMX0] = 1;
            constructArgs->assignedIMX0 = 1;
        } 
        else if (( -1 != _resmanInternalState->IMX0busy) &&
                (_resmanInternalState->IMX0busy == scratchGroupId)) {
            _resmanInternalState->refCount[IMX0]++;
            constructArgs->assignedIMX0 = 1;
        } 
        else {
           *status = IRES_ENORESOURCE; 
            constructArgs->assignedIMX0 = 0;

            GT_2trace(CURTRACE, GT_7CLASS, 
                    "IRESMAN_VICP2_getHandles> Allocation of IMX0 for " 
                    "the VICP2 handle failed busy %d refcount %d\n",
                    _resmanInternalState->IMX0busy, 
                    _resmanInternalState->refCount[IMX0] );

            goto getHandleEnd;
        }
    }
    
    /* DM355 doesn't have an IMX1 */
    if (_VICP2_dm365) {
    
        if ( configArgs->requestIMX1 ) {
            if (_resmanInternalState->IMX1busy == IRESMAN_VICP2_RESOURCEFREE){
                _resmanInternalState->IMX1busy = scratchGroupId;
                _resmanInternalState->refCount[IMX1] = 1;
                constructArgs->assignedIMX1 = 1;
            } 
            else if (( -1 != _resmanInternalState->IMX1busy) &&
                    (_resmanInternalState->IMX1busy == scratchGroupId)) {
                _resmanInternalState->refCount[IMX1]++;
                constructArgs->assignedIMX1 = 1;
            } 
            else {
               *status = IRES_ENORESOURCE; 
                constructArgs->assignedIMX1 = 0;

                GT_2trace(CURTRACE, GT_7CLASS, 
                       "IRESMAN_VICP2_getHandles> Allocation of IMX1 for " 
                       "the VICP2 handle failed busy %d refcount %d\n",
                        _resmanInternalState->IMX1busy, 
                        _resmanInternalState->refCount[IMX1] );
   
                goto getHandleEnd;
            }
        }
    }

    if (configArgs->requestMJCP) {
        if (_resmanInternalState->MJCPbusy == IRESMAN_VICP2_RESOURCEFREE) {
            _resmanInternalState->MJCPbusy = scratchGroupId;
            _resmanInternalState->refCount[MJCP] = 1;
            constructArgs->assignedMJCP = 1;
        } 
        else if (( -1 != _resmanInternalState->MJCPbusy) &&
                (_resmanInternalState->MJCPbusy == scratchGroupId)) {
            _resmanInternalState->refCount[MJCP]++;
            constructArgs->assignedMJCP = 1;
        } 
        else {
           *status = IRES_ENORESOURCE; 
            constructArgs->assignedMJCP = 0;

            GT_2trace(CURTRACE, GT_7CLASS, 
                    "IRESMAN_VICP2_getHandles> Allocation of MJCP for " 
                    "the VICP2 handle failed busy %d refcount %d\n",
                    _resmanInternalState->MJCPbusy, 
                    _resmanInternalState->refCount[MJCP] );

            goto getHandleEnd;
        }
    }

    /* Ignore requests for NSF on the DM355 */
    if (_VICP2_dm365) {

        if (configArgs->requestNSF) {
            if (_resmanInternalState->NSFbusy == IRESMAN_VICP2_RESOURCEFREE) {
                _resmanInternalState->NSFbusy = scratchGroupId;
                _resmanInternalState->refCount[NSF] = 1;
                constructArgs->assignedNSF = 1;
            } 
            else if (( -1 != _resmanInternalState->NSFbusy) &&
                    (_resmanInternalState->NSFbusy == scratchGroupId)) {
                _resmanInternalState->refCount[NSF]++;
                constructArgs->assignedNSF = 1;
            } 
            else {
               *status = IRES_ENORESOURCE; 
                constructArgs->assignedNSF = 0;

                GT_2trace(CURTRACE, GT_7CLASS, 
                        "IRESMAN_VICP2_getHandles> Allocation of NSF for " 
                        "the VICP2 handle failed busy %d refcount %d\n",
                        _resmanInternalState->NSFbusy, 
                        _resmanInternalState->refCount[NSF] );
    
                goto getHandleEnd;
            }
        }
    }

    /* Initialize all buffers to  RESNA */
    for (i = 0; i < IRES_VICP2_NUMBUFFERS; i++) {
        constructArgs->assignedIMCOPBuffers[i] = RESNA;
    }


    /* Obtain buffers here */
    if (configArgs->requestIMCOPBuffers) {

        for (i = 0; i < IRES_VICP2_NUMBUFFERS; i++) {

            if (configArgs->requestIMCOPBuffers & (0x1 << i)) {
            
                /* Ignore invalid requests and continue */
                if (_VICP2_buffOffsets[i] == RESNA) {
                    continue;
                }

                /* Valid Request for Buffer i */
                /* Each resource corresponds to 0x200 or RESSIZE of memory */
                resourceId = (_VICP2_buffOffsets[i])/(VICP2_RESSIZE); 
                GT_assert(CURTRACE, (resourceId < VICP2_NUMRES));
                numResources = (_VICP2_buffLens[i]/VICP2_RESSIZE);

                if (TRUE == SMGRMP_alloc(smgr, algHandle, &resourceId, 
                        numResources, scratchGroupId)) {

                    constructArgs->assignedIMCOPBuffers[i] = 
                            _VICP2_buffOffsets[i]; 
                    constructArgs->assignedIMCOPBufferLens[i] = 
                            _VICP2_buffLens[i]; 
                }
                else {
                    /* Free buffers allocated so far */
                    *status = IRES_ENORESOURCE; 
                    toFreeBufIndex = i-1;

                    GT_2trace(CURTRACE, GT_7CLASS, 
                            "IRESMAN_VICP2_getHandles> Allocation of "
                            " assignedIMCOPBuffers for " 
                            "the VICP2 handle failed numResources %d sgrp %d\n",
                            numResources, scratchGroupId);
        
                    goto getHandleEnd;
                } 
            }
        }
        toFreeBufIndex = i - 1;
    } 
    
    constructArgs->numMemBufs = configArgs->numMemoryRequests;

    /* Request for memory chunks */
    for (i = 0; i < configArgs->numMemoryRequests; i++) {

        resourceId = -1; 

        /* Round up request size to 512b */ 
        numResources = ((configArgs->memRequestSizes[i] + 
                ((VICP2_RESSIZE) - 1))/(VICP2_RESSIZE));

        GT_assert(CURTRACE, numResources <VICP2_NUMRES);

        /* Request for Buffer i */
        if (TRUE == SMGRMP_alloc( smgr, algHandle, &resourceId, numResources,
                scratchGroupId)) {

            constructArgs->assignedMemAddrs[i] = resourceId * VICP2_RESSIZE;
            constructArgs->assignedMemSizes[i] = numResources * VICP2_RESSIZE; 
            /* Also update constructArgs->assignedIMCOPBuffers[k], where
               k corresponds to one or more buffers that this block overlaps
               with. */
            mem_beg = constructArgs->assignedMemAddrs[i];
            mem_end = mem_beg + constructArgs->assignedMemSizes[i];

            buf_num = 0;
            buf_beg =  _VICP2_buffOffsets[buf_num];
            buf_end = buf_beg + _VICP2_buffLens[buf_num];

            while (buf_num < IRES_VICP2_NUMBUFFERS) {

                if ((buf_beg != RESNA) && (buf_end > mem_beg) && 
                        (buf_beg < mem_end)) {

                    /* Update with the address of that buffer !! */ 
                    if (constructArgs->assignedIMCOPBuffers[buf_num] == RESNA) {

                        /* Even though these buffers weren't completely
                           assigned to this alg, these arrays are being updated
                           with their addresses, so that the alg can turn on
                           these buff switches */  
                        constructArgs->assignedIMCOPBuffers[buf_num] = 
                                _VICP2_buffOffsets[buf_num]; 

                        constructArgs->assignedIMCOPBufferLens[buf_num] = 
                                _VICP2_buffLens[buf_num]; 

                        /* Need to keep track of these entries as when its time 
                           to free buffers, these aren't freed, as
                           they were never explicitly granted to the alg */ 
                        constructArgs->buffSwitchesOnly[numBuffSwitches++] = 
                                buf_num;

                        constructArgs->numBuffSwitches = numBuffSwitches;
                    }
                } 

                buf_num++;
                buf_beg = _VICP2_buffOffsets[buf_num%IRES_VICP2_NUMBUFFERS];
                buf_end = buf_beg + 
                        _VICP2_buffLens[buf_num%IRES_VICP2_NUMBUFFERS];
            }
        } 
        else {
            *status = IRES_ENORESOURCE; 
            toFreeMemIndex = i-1; 

            GT_2trace(CURTRACE, GT_7CLASS, 
                    "IRESMAN_VICP2_getHandles> Allocation of "
                    " assignedIMCOPBuffers for " 
                    "the VICP2 handle failed numResources %d sgrp %d\n",
                    numResources, scratchGroupId);
        
            goto getHandleEnd;
        } 
    }
    toFreeMemIndex = i - 1; 


    /*
     * Obtain memory resources to build the handle
     */
    IRESMAN_VICP2_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *)protocolArgs, protocolMemRecs);
 
   /*
    * Allocate that memory
    */
    if (FALSE == _allocFxn(protocolMemRecs,
            numMemRecs)) {
        *status = IRES_ENOMEM;

        GT_0trace(CURTRACE, GT_7CLASS, 
                "IRESMAN_VICP2_getHandles> Allocation for memory for " 
                "the VICP2 handle failed.\n");
        
        resourceHandle = NULL;
    }
    else {

        /*
         * Use the CONSTRUCT interface of the protocol implementation to 
         * construct the handle within the allocated resource
         */
        resourceHandle = IRESMAN_VICP2_CONSTRUCTFXNS.constructHandle(
                protocolArgs, protocolMemRecs, 
                (IRESMAN_ConstructArgs *)constructArgs, status);

        if (NULL == resourceHandle) {

            GT_0trace(CURTRACE, GT_7CLASS, 
                    "IRESMAN_VICP2_getHandles> Construction of resource "
                    "handle for VICP2 failed.\n");
            
        }
    }

    if (*status != IRES_OK) {
        /* Need to free Buffer resources here  */
    }    

getHandleEnd:

    if (*status != IRES_OK) {

        /* First, fix assignedIMCOPBuffers array to remove BuffSwitches entries
           only. These entries were updated in assignedIMCOPBuffers, but 
           these buffers were never explicitly assigned to the alg */ 
        for (i = 0; i < constructArgs->numBuffSwitches; i++) {
            constructArgs->assignedIMCOPBuffers[constructArgs->buffSwitchesOnly
                    [i]] = RESNA;
        }

        /* Free the rest of the allocated buffers */
        while (toFreeBufIndex >= 0) {

            if (constructArgs->assignedIMCOPBuffers[toFreeBufIndex] == RESNA) {
                toFreeBufIndex--;
                continue; 
            }
            resourceId = (constructArgs->assignedIMCOPBuffers[toFreeBufIndex])/
                    (VICP2_RESSIZE);

            numResources = (constructArgs->assignedIMCOPBufferLens[
                    toFreeBufIndex])/(VICP2_RESSIZE);

            smg_status = SMGRMP_free(smgr, algHandle, resourceId, numResources, 
                    scratchGroupId);

            GT_assert(CURTRACE, smg_status);

            if (smg_status == FALSE) {
                *status = IRES_EFAIL;
            }

            toFreeBufIndex--;
        } 
    
        while (toFreeMemIndex >= 0) {

            resourceId = (constructArgs->assignedMemAddrs[toFreeMemIndex])/
                    (VICP2_RESSIZE);
            numResources = ((configArgs->memRequestSizes[toFreeMemIndex] + 
                    ((VICP2_RESSIZE) - 1))/(VICP2_RESSIZE));
            smg_status = SMGRMP_free(smgr, algHandle, resourceId, numResources,
                    scratchGroupId);
            GT_assert(CURTRACE, smg_status);

            if (smg_status == FALSE) {
                *status = IRES_EFAIL;
            }

            toFreeMemIndex--;

       } 

       if (constructArgs->assignedIMX0 == 1) {
           _resmanInternalState->refCount[IMX0]--;
            if (_resmanInternalState->refCount == 0 ) {
                _resmanInternalState->IMX0busy = IRESMAN_VICP2_RESOURCEFREE;
            }
        }
        else if (constructArgs->assignedIMX1 == 1) {
           _resmanInternalState->refCount[IMX1]--;
            if (_resmanInternalState->refCount == 0 ) {
                _resmanInternalState->IMX1busy = IRESMAN_VICP2_RESOURCEFREE;
            }
        }
        else if (constructArgs->assignedMJCP == 1) {
           _resmanInternalState->refCount[MJCP]--;
            if (_resmanInternalState->refCount == 0 ) {
                _resmanInternalState->MJCPbusy = IRESMAN_VICP2_RESOURCEFREE;
            }
        } 
        else if (constructArgs->assignedNSF == 1) {
           _resmanInternalState->refCount[NSF]--;
            if (_resmanInternalState->refCount == 0 ) {
                _resmanInternalState->NSFbusy = IRESMAN_VICP2_RESOURCEFREE;
            }
        } 
    } 

    /*
     * Free constructArgs memory, that was just to pass the arguments
     */
    _freeFxn(&constructHandleMemRec, 1);


    GT_1trace(CURTRACE, GT_ENTER, 
                "IRESMAN_VICP2_getHandles> Exit (resourceHandle=0x%x)\n", 
                resourceHandle);
    return (resourceHandle);
}

/**
 *  Frees handles back to the resource pool resources to free
 */
/*  ARGSUSED - this line tells the compiler not to warn about unused args */
IRES_Status IRESMAN_VICP2_freeHandles(IALG_Handle algHandle, 
        IRES_Handle algResourceHandle, IRES_ProtocolArgs * protocolArgs, 
        Int scratchGroupId) 
{
    IALG_MemRec resourceMemRecs[IRES_VICP2_MAXRESOURCES];
    Int numMemRecs;
    Int i, numResources, resourceId = -1;
    Bool smg_status = FALSE;
    IRES_Status retStatus = IRES_OK; 
    IRES_VICP2_Handle resourceHandle = (IRES_VICP2_Handle) algResourceHandle;
    /*
     * Cast the protocolArgs 
     */
    IRES_VICP2_ProtocolArgs * configArgs = 
            (IRES_VICP2_ProtocolArgs *) protocolArgs;

    GT_assert(CURTRACE, configArgs);
    GT_assert(CURTRACE, algResourceHandle);

    if (_resmanInternalState == NULL) {

        GT_0trace(CURTRACE, GT_7CLASS, 
                "_IRESMAN_VICP2_freeHandles> RMAN_register call has not "
                "happened successfully\n. Please register VICP2 resource "
                "with RMAN before requesting or releasing resources.\n");

        retStatus = IRES_ENORESOURCE;
        return (retStatus);
    }

    if (configArgs->mode == IRES_PERSISTENT) {
        scratchGroupId = -1;
    } 
    else if (configArgs->mode == IRES_LATEACQUIRE) {
        scratchGroupId = VICP2_NUM_GROUPS;
    } 
 
    /*
     * Free the handles to the resource manager  
     */
    if (resourceHandle->assignedIMX1 == 1) {
        if (_resmanInternalState->refCount[IMX1] == 0) {
            retStatus =  IRES_ENORESOURCE;
            return (retStatus);
        } 
        _resmanInternalState->refCount[IMX1]--;
        if (_resmanInternalState->refCount == 0 ) {
            _resmanInternalState->IMX1busy = IRESMAN_VICP2_RESOURCEFREE;
        }
    }
    else if (resourceHandle->assignedIMX0 == 1) {
        if (_resmanInternalState->refCount[IMX0] == 0) {
            retStatus = IRES_ENORESOURCE;
            return (retStatus);
        } 
        _resmanInternalState->refCount[IMX0]--;
        if (_resmanInternalState->refCount == 0 ) {
            _resmanInternalState->IMX0busy = IRESMAN_VICP2_RESOURCEFREE;
        }
    }
    else if (resourceHandle->assignedMJCP == 1) {
        if (_resmanInternalState->refCount[MJCP] == 0) {
            retStatus = IRES_ENORESOURCE;
            return (retStatus);
        } 
        _resmanInternalState->refCount[MJCP]--;
        if (_resmanInternalState->refCount == 0 ) {
            _resmanInternalState->MJCPbusy = IRESMAN_VICP2_RESOURCEFREE;
        }
    } 
    else if (resourceHandle->assignedNSF == 1) {
        if (_resmanInternalState->refCount[NSF] == 0) {
            retStatus = IRES_ENORESOURCE;
            return (retStatus);
        } 
        _resmanInternalState->refCount[NSF]--;
        if (_resmanInternalState->refCount == 0 ) {
            _resmanInternalState->NSFbusy = IRESMAN_VICP2_RESOURCEFREE;
        }
    } 


    /* Free buffers here */
    /* First, fix assignedIMCOPBuffers array to remove BuffSwitches entries
       only. These buffers were added to teh assignedIMCOPBuffer entries,
       but weren't really explicitly allocated to the alg, only memory
       chunks out of these buffers were allocated. */ 
    for (i = 0; i < ((_VICP2_IntObj *)(resourceHandle))->numBuffSwitches; i++) {
        resourceHandle->assignedIMCOPBuffers[((_VICP2_IntObj *)
                resourceHandle)->buffSwitchesOnly[i]] = RESNA;
    }

    for (i = 0; i < IRES_VICP2_NUMBUFFERS; i++) {

        if (RESNA != resourceHandle->assignedIMCOPBuffers[i]) {
            
            /* Valid Assigned Buffer i */
            /* Each resource corresponds to 0x200 of RESSIZE of memory */
            resourceId = ((resourceHandle->assignedIMCOPBuffers[i] - 
                    ((_VICP2_IntObj *)resourceHandle)->configBase))/
                    (VICP2_RESSIZE);

            numResources = (_VICP2_buffLens[i])/(VICP2_RESSIZE);

            smg_status =  SMGRMP_free(smgr, algHandle, resourceId, numResources,
                    scratchGroupId);

            GT_assert(CURTRACE, smg_status);

            if (FALSE == smg_status) {
                retStatus = IRES_EFAIL;
            }
        }
    } 

    for (i = 0; i < resourceHandle->numMemBufs;i++ ) {

        resourceId = (resourceHandle->assignedMemAddrs[i] -
                ((_VICP2_IntObj *)resourceHandle)->configBase)/VICP2_RESSIZE;
        numResources = ((resourceHandle->assignedMemSizes[i] + 
                ((VICP2_RESSIZE) - 1))/(VICP2_RESSIZE));
        smg_status = SMGRMP_free(smgr, algHandle, resourceId, numResources, 
                scratchGroupId);

        GT_assert(CURTRACE, smg_status);

   } 

   /*
    * Free memory resources to build the handle
    */
 
    /*
     * Obtain memory resources to free and free them
     */
    numMemRecs = IRESMAN_VICP2_CONSTRUCTFXNS.getNumMemRecs
        ( (IRES_ProtocolArgs *)protocolArgs);

    IRESMAN_VICP2_CONSTRUCTFXNS.getMemRecs((IRES_Handle)NULL,
            (IRES_ProtocolArgs *) protocolArgs, resourceMemRecs);

    resourceMemRecs[0].base = algResourceHandle;

    /*
     * Use IRES_VICP2_RESOURCEPROTOCOL to de-init the resource protocol
     * if required
     */
    IRESMAN_VICP2_CONSTRUCTFXNS.destructHandle(algResourceHandle);

    /*
     * Free the memory for the handles
     */
    _freeFxn(resourceMemRecs, numMemRecs); 

    return (IRES_OK);
}

 
/*
 *  ======= setInternalState =======
 */
static Void setInternalState(Void * addr)
{
    IRESMAN_Vicp2_InternalState * intState =
            (IRESMAN_Vicp2_InternalState *)addr;
 
    if (NULL != intState) {
        intState->numOpens = 0;
    
        intState->IMX0busy = IRESMAN_VICP2_RESOURCEFREE;
        intState->IMX1busy = IRESMAN_VICP2_RESOURCEFREE;
        intState->MJCPbusy = IRESMAN_VICP2_RESOURCEFREE;
        intState->NSFbusy = IRESMAN_VICP2_RESOURCEFREE;
    
        intState->refCount[0] = intState->refCount[1] = 
                intState->refCount[2] = intState->refCount[3] = 0;
        intState->base = NULL;
    }
}
 

static void getInternalState() 
{
    Int sharedMemId = -1;
#ifdef xdc_target__os_Linux
 
    _resmanInternalState = (IRESMAN_Vicp2_InternalState *)SHM_getObj(
            _VICP2_lock, sizeof(IRESMAN_Vicp2_InternalState),
            _VICP2_LOCKID, &setInternalState, &sharedMemId);
#else
    _resmanInternalState = (IRESMAN_Vicp2_InternalState *)
            &_VICP2_internalState;
    setInternalState(_resmanInternalState);
    sharedMemId = 0;
#endif
    _resmanInternalState->sharedMemId = sharedMemId;
}

/*
 *  ======== freeInternalState ========
 */
static void freeInternalState()
{
    //if (_resmanInternalState->numOpens == 0) {
    VICP_exit();
    //}
#ifdef xdc_target__os_Linux
   SHM_freeObj(_VICP2_lock, _resmanInternalState,
            _resmanInternalState->sharedMemId);
#else
    _resmanInternalState = NULL;
#endif
}

static void initializeBufferOffsets() {

    _VICP2_regSize = VICP2_REGSIZE;
    _VICP2_bufSize = VICP2_BUFSIZE;

    _VICP2_buffOffsets[IMCOP_BUFFER_IMGBUF_A]           = IMGBUF_A_FULL_BASE;
    _VICP2_buffOffsets[IMCOP_BUFFER_IMGBUF_B]           = IMGBUF_B_FULL_BASE; 
    _VICP2_buffOffsets[IMCOP_BUFFER_IMGBUF_C]           = IMGBUF_C_FULL_BASE;
    _VICP2_buffOffsets[IMCOP_BUFFER_IMGBUF_D]           = IMGBUF_D_FULL_BASE; 
    _VICP2_buffOffsets[IMCOP_BUFFER_IMGBUF_E]           = IMGBUF_E_FULL_BASE; 
    _VICP2_buffOffsets[IMCOP_BUFFER_IMX0COEFFBUF]       = IMX0COEFFBUF_BASE; 
    _VICP2_buffOffsets[IMCOP_BUFFER_IMX0CMDBUF]         = IMX0CMDBUF_BASE;    
    _VICP2_buffOffsets[IMCOP_BUFFER_IMX1COEFFBUF]       = IMX1COEFFBUF_BASE; 
    _VICP2_buffOffsets[IMCOP_BUFFER_IMX1CMDBUF]         = IMX1CMDBUF_BASE;    
    _VICP2_buffOffsets[IMCOP_BUFFER_BABYIMXCMDBUFFER]   = BABYIMXCMDBUF_BASE;
    _VICP2_buffOffsets[IMCOP_BUFFER_BABYIMXORIGBUFFER]  = BABYIMXORIGBUF_BASE;
    _VICP2_buffOffsets[IMCOP_BUFFER_BABYIMXREFBUFFER]   = BABYIMXREFBUF_BASE;
    _VICP2_buffOffsets[IMCOP_BUFFER_SEQUENCERPMEM]      = SEQ_PMEM_BASE;
    _VICP2_buffOffsets[IMCOP_BUFFER_QIQMEM]             = QIQMEM_BASE;   
    _VICP2_buffOffsets[IMCOP_BUFFER_HUFFMEM]            = HUFFMEM_BASE;   
    _VICP2_buffOffsets[IMCOP_BUFFER_SEQBUF4]            = SEQBUF4_BASE;   

    _VICP2_buffLens[IMCOP_BUFFER_IMGBUF_A]              = IMGBUF_A_FULL_LEN; 
    _VICP2_buffLens[IMCOP_BUFFER_IMGBUF_B]              = IMGBUF_B_FULL_LEN;
    _VICP2_buffLens[IMCOP_BUFFER_IMGBUF_C]              = IMGBUF_C_FULL_LEN;
    _VICP2_buffLens[IMCOP_BUFFER_IMGBUF_D]              = IMGBUF_D_FULL_LEN; 
    _VICP2_buffLens[IMCOP_BUFFER_IMGBUF_E]              = IMGBUF_E_FULL_LEN; 
    _VICP2_buffLens[IMCOP_BUFFER_IMX0COEFFBUF]          = IMX0COEFFBUF_LEN;
    _VICP2_buffLens[IMCOP_BUFFER_IMX0CMDBUF]            = IMX0CMDBUF_LEN;    
    _VICP2_buffLens[IMCOP_BUFFER_IMX1COEFFBUF]          = IMX1COEFFBUF_LEN; 
    _VICP2_buffLens[IMCOP_BUFFER_IMX1CMDBUF]            = IMX1CMDBUF_LEN;    
    _VICP2_buffLens[IMCOP_BUFFER_BABYIMXCMDBUFFER]      = BABYIMXCMDBUF_LEN;
    _VICP2_buffLens[IMCOP_BUFFER_BABYIMXORIGBUFFER]     = BABYIMXORIGBUF_LEN;
    _VICP2_buffLens[IMCOP_BUFFER_BABYIMXREFBUFFER]      = BABYIMXREFBUF_LEN;
    _VICP2_buffLens[IMCOP_BUFFER_SEQUENCERPMEM]         = SEQ_PMEM_LEN;   
    _VICP2_buffLens[IMCOP_BUFFER_QIQMEM]                = QIQMEM_LEN;   
    _VICP2_buffLens[IMCOP_BUFFER_HUFFMEM]               = HUFFMEM_LEN;   
    _VICP2_buffLens[IMCOP_BUFFER_SEQBUF4]               = SEQBUF4_LEN;   
}

IRESMAN_Fxns IRESMAN_VICP2 =  {
    IRESMAN_VICP2_getProtocolName,
    IRESMAN_VICP2_getProtocolRevision,
    IRESMAN_VICP2_init,
    IRESMAN_VICP2_exit,
    IRESMAN_VICP2_getHandles,
    IRESMAN_VICP2_freeHandles
};

IRESMAN_VicpParams IRESMAN_VICP2_DEFAULTPARAM;

IRESMAN_Fxns * VICP2_getIresmanFxns()
{
    return ((Void *)(&IRESMAN_VICP2));
}


IRESMAN_Params * VICP2_getDefaultParams()
{
    IRESMAN_VICP2_DEFAULTPARAM.baseConfig.size = 
            sizeof(IRESMAN_Params);

    return ((IRESMAN_Params *)&IRESMAN_VICP2_DEFAULTPARAM);
}
/*
 *  @(#) ti.sdo.fc.ires.vicp; 1, 0, 1,177; 12-1-2010 17:25:26; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

