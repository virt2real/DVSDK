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
 *  ======== smgrmp.c ========
 *  Description:
 *
 *  This "scratch" memory manager provides general scratch management of an
 *  arbitrary resource.
 *  
 *  Notes:
 *
 */

#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>
#include <stdlib.h> /* For malloc and free */
#include <ti/sdo/fc/memutils/memutils.h>    /* To get physical address of alg */

#define CURTRACE ti_sdo_fc_utils_smgrmp_GTMask

#ifdef xdc_target__os_Linux 
#include "sharedMem.h"
#endif

#include "smgr.h"
#include "_smgr.h"
#include "_smgrmp.h"

#define OFFSET(base, address) ((UInt32)address - (UInt32)base)
#define SMGRHANDLE(handle)  (SMGR_Handle)((UInt32)(handle) + \
        handle->smgrOffset) 
#define ALIGN32(x) ((((UInt32)(x) + 3) / 4) * 4)

extern GT_Mask CURTRACE;

/*
 * These two arrays are filled up with resource requests, and then only when
 * all the entries are deleted, will the arrays be reused again. 
 */  
static unsigned int shmAddrs[SMGRMP_MAXINSTANCES];
static Int shmIndex[SMGRMP_MAXINSTANCES];

/*
 * Watermark on the array, reset to zero, when everything gets deleted 
 */  
static Int shmCount = 0;

/*
 * Maintains a total number of active entries in the arrays, when this goes to
 * zero, arrays can be re-used again, so shmCount is set to 0
 */ 
static Int shmTotal = 0;

static void setInternalState(void * addr); 
static Void *shmAlloc(Int segid, UInt32 size, UInt32 align);
static Bool shmFree(Int segid, Void *addr, UInt32 size);

/*
 *  ======== SMGRMP_alloc ========
 */
Bool SMGRMP_alloc(SMGRMP_Handle handle, IALG_Handle alg, Int *resourceId, 
        Int num, Int scratchId)
{
    Bool                status = TRUE;
    Void                * addr = (Void *)alg;

    /*
     * Call SMGR_alloc
     */
    if (NULL != alg) {
        addr = MEMUTILS_getPhysicalAddr((Ptr)alg); 
    } 
    status = SMGR_alloc(SMGRHANDLE(handle), (IALG_Handle)
            addr , resourceId, num, scratchId); 

    return (status);
} 

/*
 *  ======== SMGRMP_create ========
 */
SMGRMP_Handle SMGRMP_create(SMGRMP_Attrs *attrs)
{
    SMGRMP_Obj         *handle;
    Int             shmId = -1;
    unsigned int    shmSize = 0;
    Void            * addr;
    SMGR_Attrs       smgrAttrs;

    /* Create a shared memory object SMGRMP_Obj using the key and the lock 
    Size of this will depend numResources and SMGR_Obj etc  */
   
    GT_assert(CURTRACE, shmCount < SMGRMP_MAXINSTANCES); 

    shmSize = sizeof(SMGRMP_Obj) + sizeof(SMGR_Obj) + sizeof(UInt32); 
    shmSize = ALIGN32(shmSize);
    shmSize += (sizeof(SMGR_Counter) * attrs->numResources);
    shmSize = ALIGN32(shmSize);

#ifdef xdc_target__os_Linux
    addr = SHM_getObj(attrs->lock, shmSize, (key_t)attrs->key, 
            (SHM_InitFxn)&setInternalState, &shmId);
#else
    addr = (void *)malloc(shmSize);
    setInternalState(addr);
    shmId = 0;
#endif

    if (shmId != -1) {

       handle = (SMGRMP_Obj *)addr;

        /* This will return a unique object for each key, and the same object
           for different processes */
        if (0 == handle->refCount) {

            /* SMGR_create has to happen */ 
            smgrAttrs.segid = shmCount;          /* Use shmCount as segId */ 
            smgrAttrs.numResources = attrs->numResources;
            smgrAttrs.numScratchGroups = attrs->numScratchGroups;
            smgrAttrs.allocFxn = shmAlloc;
            smgrAttrs.freeFxn = shmFree;

            /* Store the shmCount in the  SHM_Obj part of the handle */
            handle->shmCount = shmCount;
            shmCount++;
            shmTotal++;
        }
        /* Successful acquisition of shared Mem object, so store in array
           for use by alloc/free functions */ 
        shmAddrs[handle->shmCount] = (unsigned int)addr;
        shmIndex[handle->shmCount] = sizeof(SMGRMP_Obj); /* Change this to 
                                                            work for the alloFxn
                                                          */
        if (handle->refCount == 0) {

            /* Whatever the SMGR_create returns, store that as an offset from 
               shmBase */
            handle->smgrOffset = OFFSET(handle, SMGR_create(&smgrAttrs));
        }

        handle->refCount++;
        /* Store the sharedMemId in the SMGRMP_Obj */ 
        handle->sharedMemId = shmId;
        return (handle);
    }
    else {
        return (NULL);
    }
}

/*
 *  ======== SMGRMP_delete ========
 */
/* ARGSUSED */
Void SMGRMP_delete(LockMP_Handle lock, SMGRMP_Handle handle)
{
#ifdef xdc_target__os_Linux
    Int shmId = handle->sharedMemId;                   /* Shared Mem Id */
#endif

    Void * base = (Void *)(shmAddrs[handle->shmCount]);    /* Base Address */ 

    /* Decrease the refCount */
    handle->refCount--;   

    /* If the referenceCount is zero, call the SMGR delete */ 
    if (0 == handle->refCount) {
        SMGR_delete(SMGRHANDLE(handle));
        shmAddrs[handle->shmCount] = NULL;
        shmIndex[handle->shmCount] = NULL;
        shmTotal--;
        if (shmTotal == 0) {
            shmCount = 0;
        }
    }

#ifdef xdc_target__os_Linux
    /* Free the shared memory segment */
    SHM_freeObj(lock, base, shmId);
#else
    free(base);        
#endif
}

/*
 *  ======== SMGRMP_exit ========
 */
Void SMGRMP_exit(Void)
{
}

/*
 *  ======== SMGRMP_free ========
 */
/* ARGSUSED */
Bool SMGRMP_free(SMGRMP_Handle handle, IALG_Handle alg, Int resourceId, Int num,
        Int scratchId)
{
    Bool status = TRUE;
    Void                * addr = (Void *)alg;

    /*
     * Call SMGR_alloc
     */
    if (NULL != alg) {
        addr = MEMUTILS_getPhysicalAddr((Ptr)alg); 
    } 

    status = SMGR_free(SMGRHANDLE(handle), (IALG_Handle) addr , 
            resourceId, num, scratchId); 

    return (status);
}

/*
 *  ======== SMGRMP_init ========
 */
Void SMGRMP_init(Void)
{
}

static void setInternalState(void * addr) 
{

    SMGRMP_Obj * smgr = (SMGRMP_Obj *)addr;
    /* In the init function of the object, call SMGR_create */ 
    smgr->refCount = 0;
}

/* ARGSUSED */
static Void *shmAlloc(Int segid, UInt32 size, UInt32 align)
{

    unsigned int baseAddr = shmAddrs[segid];        /* We stored the shmCount
                                                       in the segId */  
    Int index  = shmIndex[segid]; 
    Void * returnAddr = NULL; 
    
    returnAddr = (void *)(baseAddr + index);  
    shmIndex[segid] += size;

    return (returnAddr);
}

/* ARGSUSED */
static Bool shmFree(Int segid, Void *addr, UInt32 size)
{
    return (TRUE);
}
/*
 *  @(#) ti.sdo.fc.utils; 1, 0, 2,286; 12-1-2010 17:26:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

