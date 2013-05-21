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
 *  ======== dman3_impl.h ========
 *
 *  DMAN3 internal implementation declarations.
 */

#ifndef _DMAN3_IMPL
#define _DMAN3_IMPL

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

#include <xdc/std.h>
#include <rmm.h>
#include <_rmm.h>

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_dman3_GTMask;

/* Maximum number of TCCs available */
#define _DMAN3_MAXNUMTCCS    64


#ifndef xdc_target__isaCompatible_64P

/* Id offset from _DMAN3_ipcKeyBase to shared memory containing DMAN3 object */
#define _DMAN3_SHMID (_DMAN3_ipcKeyBase)

/* Id offset from _DMAN3_ipcKeyBase to semaphore used for critical sections */
#define _DMAN3_CSID (_DMAN3_ipcKeyBase + 1)

/* Id offset from _DMAN3_ipcKeyBase to lock used for protecting DMAN3 object */
#define _DMAN3_LOCKID (_DMAN3_ipcKeyBase + 2)

/* Extern declarations of Lock funtions that are in CE/osal/LockMP.h */
typedef struct LockMP_Obj *LockMP_Handle;

extern Void LockMP_acquire(LockMP_Handle lock);
extern LockMP_Handle LockMP_create(Int key);
extern Void LockMP_delete(LockMP_Handle lock);
extern Int LockMP_getRefCount(LockMP_Handle lock);
extern Void LockMP_release(LockMP_Handle lock);

#endif

/*
 *  ======== DMAN3_ContextObj ========
 */
typedef struct DMAN3_ContextObj {
    Int           groupId;      /* Group ID for TCCs, PaRams */
    Int           scratchId;    /* Group ID for scratch Env */
    Int           tccBase;
    Int           numTccs;
    Int           nextFreeTccIdx;
    Int           paRamBaseIdx;
    Uns          *paRamBase;
    Int           numPaRams;
    Int           numAssignedPaRams;
    Uns          *nextFreePaRamAddr; 
    Int           nextQdmaChannel;
    Int           refCount;
    Int           qdmaBase;
    Int           numQdmas;
} DMAN3_ContextObj;

typedef struct DMAN3_ContextObj *DMAN3_Context;


/*
 *  ======== _DMAN3_Data ========
 *  DMAN3 internal data that must be shared between processes.
 */
typedef struct _DMAN3_Data {
    UInt8         tccTable[_DMAN3_MAXNUMTCCS];
    UInt8         numTccGroup[DMAN3_MAXGROUPS];
    UInt16        numPaRamGroup[DMAN3_MAXGROUPS];

    /*
     *  Offsets of contexts within this structure. We can't use pointers,
     *  since the address of this object may be different for different
     *  processes. The value of context[i] will be the offset of contextObjs[i]
     *  from the beginning of this structure.
     *
     *  TODO: Can we remove context[] and just keep contextObjs[], if DSP
     *  and ARM both use _DMAN3_Data structure for storing information?
     */
    UInt32        context[DMAN3_MAXGROUPS];

    Int           numAssignedTccs;
    Int           heapInt;
    Int           heapExt;
    Int           heapIdma3;
    Int           refCount;

    /*
     *  These are offsets from base of object, since we can't use pointers
     *  in shared memory, as the address of the shared object may be different
     *  for different processes.
     */
    UInt32        rmmTccs;
    UInt32        rmmPaRams;

    /* Functions for allocating and freeing 'env' from scratch memory */
    DMAN3_ScratchAllocFxn allocScratch;
    DMAN3_ScratchFreeFxn freeScratch;
    DMAN3_ContextObj contextObjs[DMAN3_MAXGROUPS];
    /* Information about channels being set aside for persistent allocation */
        UInt32 qdmaPersistentNum; 
        UInt32 qdmaPersistentBase;
} _DMAN3_Data;

extern _DMAN3_Data *_DMAN3_data;

/* Base value of keys for DMAN3 Linux IPC objects */
extern UInt32 _DMAN3_ipcKeyBase;

/* Qdma channel number from which to start allocation for each scratch group */
extern UInt32 _DMAN3_qdmaBase[DMAN3_MAXGROUPS + 1]; 

/* Flag to indicate if custom DMA library allocation method is to be used */
extern __FAR__ Bool ti_sdo_fc_dman3_DMAN3_useCustomDma;

#define _DMAN3_heapInt (_DMAN3_data->heapInt)
#define _DMAN3_refCount (_DMAN3_data->refCount)
#define _DMAN3_heapExt (_DMAN3_data->heapExt)
#define _DMAN3_numAssignedTccs (_DMAN3_data->numAssignedTccs)
#define _DMAN3_heapIdma3 (_DMAN3_data->heapIdma3)
#define _DMAN3_tccAllocationTable (_DMAN3_data->tccTable)
#define _DMAN3_numTccGroup (_DMAN3_data->numTccGroup)
#define _DMAN3_numPaRamGroup (_DMAN3_data->numPaRamGroup)
#define _DMAN3_allocScratch (_DMAN3_data->allocScratch)
#define _DMAN3_freeScratch (_DMAN3_data->freeScratch)
#define _DMAN3_numQdmaGroup(i) (((i) >= 0) ? \
        ti_sdo_fc_dman3_DMAN3_numQdmaGroup[i] : \
        _DMAN3_data->qdmaPersistentNum)
#define _DMAN3_qdma(i) (((i) < 0) ? _DMAN3_data->qdmaPersistentBase : \
        _DMAN3_qdmaBase[(i)])


/* Convert offsets to addresses based on where _DMAN3_data is mapped */
#define _DMAN3_groupContext(i) \
   ((DMAN3_Context)((UInt32)_DMAN3_data + _DMAN3_data->context[i]))

#define _DMAN3_rmmTccs \
    ((RMM_Handle)((UInt32)_DMAN3_data + _DMAN3_data->rmmTccs))
#define _DMAN3_rmmPaRams \
    ((RMM_Handle)((UInt32)_DMAN3_data + _DMAN3_data->rmmPaRams))


#ifndef xdc_target__isaCompatible_64P
extern LockMP_Handle _DMAN3_lock;
#endif

/*
 *  ======== _DMAN_initParams ========
 *  Initialize DMAN3_PARAMS with satic configuration parameters
 */
extern Void _DMAN3_initParams(Void);
    
/*
 *  ======== _DMAN_initImpl   ========
 *  Implementation of DMAN3_init function which expects DMAN3_PARAMS
 *  to be initialized independent of RTSC or C configuration
 */
extern Void _DMAN3_initImpl(Void);


#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif /*_DMAN3_*/

/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

