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
 *  ======== Memory_BIOS.c ========
 */
#include <xdc/std.h>

#include <string.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/mem.h>
#include <ti/bios/include/bcache.h>

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/osal/Memory.h>

/*
 *  _MEM_lock() and _MEM_unlock() as defined in _mem.h (a private file that
 *  is not exported).
 *  MEM_D_lockaddr and MEM_D_unlockaddr are declared in mem.h
 */
extern far Fxn MEM_D_lockaddr;
extern far Fxn MEM_D_unlockaddr;

#define _MEM_lock()     ((*MEM_D_lockaddr)())
#define _MEM_unlock()   ((*MEM_D_unlockaddr)())

/* default memory segment for allocs, defined in Global.xdt */
extern Int Memory_SEGID;

/*
 *  Number of heaps, their names, original base address and sizes - defined
 *  in Settings.xdt generated file
 */
extern Int Memory_numHeaps;
extern String Memory_heapNames[];
extern Uint32 Memory_heapBases[];
extern Uint32 Memory_heapSizes[];


static GT_Mask curTrace;

/*
 * Memory_DEFAULTPARAMS should be set such that legacy Memory_alloc behavior
 * is achieved (where "legacy" means before params were added).
 */
Memory_AllocParams Memory_DEFAULTPARAMS = {
    Memory_SEG,
    Memory_NONCACHED,
    0,
    0                   /* will get assigned Memory_SEGID in Memory_init */
};

/*
 *  ======== segAlloc ========
 */
static inline Ptr segAlloc(Int segid, UInt size, UInt align)
{
    return (MEM_alloc(segid, size, align));
}

/*
 *  ======== segFree ========
 */
static inline Bool segFree(Int segid, Ptr addr, UInt size)
{
    return (MEM_free(segid, addr, size));
}

/*
 *  ======== Memory_alloc ========
 */
Ptr Memory_alloc(UInt size, Memory_AllocParams *params)
{
    Ptr addr;

    GT_1trace(curTrace, GT_ENTER, "Memory_alloc> Enter(size=0x%x)\n", size);

    if (params == NULL) {
        params = &Memory_DEFAULTPARAMS;
    }

    addr = segAlloc(params->seg, size, params->align);

    GT_1trace(curTrace, GT_ENTER, "Memory_alloc> return (0x%x)\n", addr);

    return addr;
}


/*
 *  ======== Memory_cacheInv ========
 */
Void Memory_cacheInv(Ptr addr, Int sizeInBytes)
{
    GT_2trace(curTrace, GT_ENTER, "Memory_cacheInv> "
        "Enter(addr=0x%x, sizeInBytes=%d)\n", addr, sizeInBytes);

    BCACHE_inv(addr, sizeInBytes, TRUE);

    GT_0trace(curTrace, GT_ENTER, "Memory_cacheInv> return\n");
}


/*
 *  ======== Memory_cacheWb ========
 */
Void Memory_cacheWb(Ptr addr, Int sizeInBytes)
{
    GT_2trace(curTrace, GT_ENTER, "Memory_cacheWb> "
        "Enter(addr=0x%x, sizeInBytes=%d)\n", addr, sizeInBytes);

    BCACHE_wb(addr, sizeInBytes, TRUE);

    GT_0trace(curTrace, GT_ENTER, "Memory_cacheWb> return\n");
}


/*
 *  ======== Memory_cacheWbInv ========
 */
Void Memory_cacheWbInv(Ptr addr, Int sizeInBytes)
{
    GT_2trace(curTrace, GT_ENTER, "Memory_cacheWbInv> "
        "Enter(addr=0x%x, sizeInBytes=%d)\n", addr, sizeInBytes);

    BCACHE_wbInv(addr, sizeInBytes, TRUE);

    GT_0trace(curTrace, GT_ENTER, "Memory_cacheWbInv> return\n");
}


/*
 *  ======== Memory_cacheWbInvAll ========
 */
Void Memory_cacheWbInvAll()
{
    GT_0trace(curTrace, GT_ENTER, "Memory_cacheWbInvAll> Enter()\n");

    BCACHE_wbInvAll();

    GT_0trace(curTrace, GT_ENTER, "Memory_cacheWbInvAll> return\n");
}


/*
 *  ======== Memory_contigAlloc ========
 */
Ptr Memory_contigAlloc(UInt size, UInt align)
{
    Ptr addr;

    GT_2trace(curTrace, GT_ENTER, "Memory_contigAlloc> "
        "Enter(size=%d, align=%d)\n", size, align);

    addr = segAlloc(Memory_SEGID, size, align);

    GT_1trace(curTrace, GT_ENTER, "Memory_contigAlloc> return (0x%x)\n", addr);

    return addr;
}


/*
 *  ======== Memory_contigFree ========
 */
Bool Memory_contigFree(Ptr addr, UInt size)
{
    Bool retVal;

    GT_2trace(curTrace, GT_ENTER, "Memory_contigFree> "
        "Enter(addr=0x%x, size=%d)\n", addr, size);

    retVal = segFree(Memory_SEGID, addr, size);

    GT_1trace(curTrace, GT_ENTER, "Memory_contigFree> return (0x%x)\n", retVal);

    return retVal;
}


/*
 *  ======== Memory_contigStat ========
 */
Bool Memory_contigStat(Memory_Stat *statbuf)
{
    GT_1trace(curTrace, GT_ENTER, "Memory_contigStat(0x%x)\n", statbuf);

    return (Memory_segStat(Memory_SEGID, statbuf));
}


/*
 *  ======== Memory_free ========
 */
Bool Memory_free(Ptr addr, UInt size, Memory_AllocParams *params)
{
    Bool retVal;

    GT_2trace(curTrace, GT_ENTER, "Memory_free> "
        "Enter(addr=0x%x, size=%d)\n", addr, size );

    if (params == NULL) {
        params = &Memory_DEFAULTPARAMS;
    }

    retVal = segFree(params->seg, addr, size);

    GT_1trace(curTrace, GT_ENTER, "Memory_free> return (0x%x)\n", retVal);

    return retVal;
}


/*
 *  ======== Memory_getBufferPhysicalAddress ========
 */
UInt32 Memory_getBufferPhysicalAddress(Ptr virtualAddress, Int sizeInBytes,
    Bool *isContiguous)
{
    GT_3trace(curTrace, GT_ENTER,
        "Memory_getBufferPhysicalAddress(0x%x, 0x%x, 0x%x)\n",
        virtualAddress, sizeInBytes, isContiguous);

    if (isContiguous != NULL) {
        *isContiguous = TRUE;
    }
    return ((Uint32)virtualAddress);
}


/*
 *  ======== Memory_getBufferVirtualAddress ========
 */
Ptr Memory_getBufferVirtualAddress(
        UInt32 physicalAddress, Int sizeInBytes)
{
    GT_2trace(curTrace, GT_ENTER,
        "Memory_getBufferVirtualAddress(0x%x, 0x%x)\n",
        physicalAddress, sizeInBytes);

    return ((Ptr)physicalAddress);
}

/*
 *  ======== Memory_getHeapId ========
 */
Int Memory_getHeapId(String name)
{
    Int segId;

    /* Get the segment number of the heap with the given name */
    for (segId = 0; segId < Memory_numHeaps; segId++) {
        if (!strcmp(Memory_heapNames[segId], name)) {
            /* Found the memory segment */
            break;
        }
    }
    if (segId == Memory_numHeaps) {
        /* No memory heap found with the given name */
        return (-1);
    }

    return (segId);
}

/*
 *  ======== Memory_getNumHeaps ========
 */
Int Memory_getNumHeaps()
{
    return (Memory_numHeaps);
}

/*
 *  ======== Memory_init ========
 */
Bool Memory_init(Void)
{
    Memory_Stat stat;
    Int         i;

    static Bool curInit = FALSE;

    if (curInit != TRUE) {
        curInit = TRUE;
        Memory_DEFAULTPARAMS.seg = Memory_SEGID;
        GT_create(&curTrace, Memory_GTNAME);

        /*
         *  Get original sizes and base addresses of memory heaps so the
         *  heaps can be restored after they are redefined.
         */
        for (i = 0; i < Memory_numHeaps; i++) {
            if (!Memory_segStat(i, &stat)) {
                GT_1trace(curTrace, GT_7CLASS,
                        "RMS_init> Failed to get Memory_segStat[%d]\n", i);
            }
            Memory_heapBases[i] = stat.base;
            Memory_heapSizes[i] = stat.size;
        }
    }

    return (TRUE);
}


/*
 *  ======== Memory_exit ========
 */
Void Memory_exit(Void)
{
}

/*
 *  ======== Memory_redefine ========
 */
Bool Memory_redefine(Int segId, Uint32 base, Uint32 size)
{
    Memory_Stat   stat;

    /*
     *  We need to ensure that no other tasks allocate memory from
     *  this heap while we are redefining it.
     */
    _MEM_lock();

    /* Check that segId is valid and nothing is allocated in segment */
    if (!Memory_segStat(segId, &stat) || (stat.used > 0)) {
        _MEM_unlock();
        return (FALSE);
    }

    MEM_redefine(segId, (Ptr)base, (MEM_sizep)size);

    _MEM_unlock();

    return (TRUE);
}

/*
 *  ======== Memory_restoreHeap ========
 */
Bool Memory_restoreHeap(Int segId)
{
    Bool    retVal;

    retVal = Memory_redefine(segId, Memory_heapBases[segId],
            Memory_heapSizes[segId]);

    return (retVal);
}

/*
 *  ======== Memory_segAlloc ========
 */
Ptr Memory_segAlloc(Int segid, UInt size, UInt align)
{
    Ptr addr;

    GT_3trace(curTrace, GT_ENTER, "Memory_segAlloc> "
        "Enter(segid=%d, size=%d, align=%d)\n", segid, size, align);

    addr = segAlloc(segid, size, align);

    GT_1trace(curTrace, GT_ENTER, "Memory_segAlloc> return (0x%x)\n", addr);

    return addr;
}


/*
 *  ======== Memory_segFree ========
 */
Bool Memory_segFree(Int segid, Ptr addr, UInt size)
{
    Bool retVal;

    GT_3trace(curTrace, GT_ENTER, "Memory_segFree> "
        "Enter(segId=%d, addr=0x%x, size=%d)\n", segid, addr, size );

    retVal = segFree(segid, addr, size);

    GT_1trace(curTrace, GT_ENTER, "Memory_segFree> return (0x%x)\n", retVal);

    return retVal;
}


/*
 *  ======== Memory_segStat ========
 */
Bool Memory_segStat(Int segid, Memory_Stat *statbuf)
{
    MEM_Stat biosStatbuf;

    GT_2trace(curTrace, GT_ENTER, "Memory_segStat(0x%x, 0x%x)\n",
        segid, statbuf);

    if (MEM_stat(segid, &biosStatbuf) != TRUE) {
        return (FALSE);
    }

    statbuf->name   = Memory_heapNames[segid];

    statbuf->base = (Uint32)MEM_getBaseAddress(segid);
    statbuf->size   = biosStatbuf.size;    /* Original size */
    statbuf->used   = biosStatbuf.used;    /* Bytes used */
    statbuf->length = biosStatbuf.length;  /* Size of largest free block */

    return (TRUE);
}


/*
 *  ======== Memory_registerContigBuf ========
 */
Void Memory_registerContigBuf( 
    UInt32 virtualAddress, UInt32 sizeInBytes, UInt32 physicalAddress )
{
}
    
/*
 *  ======== Memory_unregisterContigBuf ========
 */
Void Memory_unregisterContigBuf( UInt32 virtualAddress, UInt32 sizeInBytes )
{
}

/*
 *  ======== Memory_dumpKnownContigBufs ========
 */
Void Memory_dumpKnownContigBufsList()
{
}
/*
 *  @(#) ti.sdo.ce.osal.bios; 2, 0, 1,182; 12-2-2010 21:24:43; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

