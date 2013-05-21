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
 *  ======== _dskt2.h ========
 *  internal XDAIS socket library definitions.
 *
 */

#ifndef _DSKT2_H
#define _DSKT2_H

#include "_dskt.h"
#include <ti/xdais/ialg.h>
#include "dskt2.h"

#define _DSKT2_MEMTAB_SIZE 16
#define _DSKT2_DARAMHEAP 0
#define _DSKT2_SARAMHEAP 1

#define _DSKT2_OK 0
#define _DSKT2_FAIL_FREE_SHARED_SCRATCH 1

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_dskt2_GTMask;

/*
 *  ======== DSKT2_AlgAttrs ========
 */
/**
 *  @brief      Attributes for creating algorithm with DSKT2_createAlg3().
 */
typedef struct DSKT2_AlgAttrs {
    /* TODO: Do we need a 'size' field? */
    Int     extHeapId;  /**< Use the @c extHeapId memory heap for all algorithm
                         *   memory requests in external memory, if
                         *   @c extHeapId >= 0. If @c extHeapId < 0, it will be
                         *   ignored. */
    Bool    singleHeap; /**< If TRUE, use a single external heap for all of the
                         *   algorithm's memory assignments. Otherwise, use the
                         *   algAlloc() function for memory assignments. */
} DSKT2_AlgAttrs;

typedef struct _DSKT2_ScratchBufferDesc {
    Uns size;
    Uns origSize;
    Void *base;
    Void *scratchPtr;
} _DSKT2_ScratchBufferDesc;

typedef struct _DSKT2_MemTabListNode {
    IALG_MemRec *memTab;
    Int memTabSize;
    Int numRecs;
    Int extHeapId;              /**< segId of algorithm's external heap */
    struct _DSKT2_MemTabListNode *next;
} _DSKT2_MemTabListNode;

typedef void (*_DSKT2_CreateCallbackFxn)(IALG_Handle h, const IALG_MemRec
   *memTab, Uns numTab, Uns scratchGroupId);

/* Cache writeback function pointer used by DSKT2 if not NULL */
#ifdef _6x_
extern far DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn;
#else
extern DSKT2_CacheWBInvFxn DSKT2_cacheWBInvFxn;
#endif

#ifdef _6x_
extern far Uns _DSKT2_HEAP;
extern far Uns _DSKT2_ALLOW_EXTERNAL_SCRATCH;
#else
extern Uns _DSKT2_HEAP;
extern Uns _DSKT2_ALLOW_EXTERNAL_SCRATCH;
#endif

extern _DSKT2_CreateCallbackFxn _DSKT2_createCallbackFxn;

extern Int _DSKT2_heapId;

extern IALG_Handle *_DSKT2_activeAlg;
extern IALG_Handle *_DSKT2_lastActiveAlg;

extern IALG_Handle DSKT2_createAlg3(Int scratchId, IALG_Fxns * fxns,
        IALG_Handle parent, IALG_Params * params, DSKT2_AlgAttrs *attrs);

extern Void _DSKT2_init();
extern Void _DSKT2_registerCreationCallbackFxn(_DSKT2_CreateCallbackFxn fxn);
extern Void _DSKT2_unRegisterCreationCallbackFxn(_DSKT2_CreateCallbackFxn fxn);
extern Uns  _DSKT2_spaceToSeg(Uns space);

extern Bool _DSKT2_freeInstanceMemory(Int scratchMutexId, IALG_MemRec *memTab,
    Int numRecs, Int extHeapId);
extern Bool _DSKT2_assignInstanceMemory(Int scratchMutexId,
    IALG_MemRec *memTab, Int numRecs, Int extHeapId);
extern Uns  _DSKT2_spaceToSeg(Uns space);

extern Bool _DSKT2_enqueueMemTab(Int segid, IALG_MemRec *memTab,
    Int memTabSize, Int numRecs, Int extHeapId);
extern IALG_MemRec *_DSKT2_dequeueMemTab(Int segid, IALG_Handle alg,
    Int *memTabSize, Int *numRecs, Int *extHeapId);
extern Void _DSKT2_throwMPUMemException(Char *msg);

extern Uns _DSKT2_DARAM_SCRATCH_SIZES[];
extern Uns _DSKT2_SARAM_SCRATCH_SIZES[];

extern Uns _DSKT2_NumYielded;
extern Uns _DSKT2_yielded;

#endif

/*
 *  @(#) ti.sdo.fc.dskt2; 1, 0, 4,300; 12-1-2010 17:24:35; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

