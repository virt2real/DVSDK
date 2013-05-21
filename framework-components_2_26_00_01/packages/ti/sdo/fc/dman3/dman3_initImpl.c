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
 *  ======== dman3_initImpl.c ========
 *  Initialize the DMAN3 module
 */

#include <xdc/std.h>

#ifdef xdc_target__isaCompatible_64P
#include <ti/bios/include/mem.h>
#include <ti/sdo/fc/utils/dbc.h>
#else
#include "bios_rts.h"
#endif

#include <string.h> /* For memset() */

#include "rmm.h"
#include "_rmm.h"
#include "dman3.h"
#include "dman3_impl.h"

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_dman3_GTMask;

#ifdef xdc_target__os_Linux
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/sem.h>
#include <unistd.h>
#include <fcntl.h>

#define SHMSIZE 0x4000      /* Size of shared memory chunk to allocate */

#endif

#ifdef xdc_target__isaCompatible_64P
#pragma CODE_SECTION(_DMAN3_initImpl, ".text:DMAN3_init");
#endif

/*
 *  QCHMAP: Queue to channel map register which specifies which parameter
 *  entry in bits 13-5 and the trigger word (which is word 7 in ACPY3
 *  implementation), in bits 4-2.
 */
//#define QCHMAP ((volatile Uns *)(0x01c00200))

// TODO: These 2 defines will go away with EDMA3 regs structures
#define QCHMAPOFFSET 0x200
#define PARAMOFFSET 0x4000
#define PARAMENTRYSIZE 8  /* Number of words in PaRam entry */

/* Byte offsets of QDMA registers */
#define QDMAQNUMOFFSET  0x0260
#define QUETCMAPOFFSET  0x0280
#define QUEPRIOFFSET    0x0284
#define QRAE0OFFSET     0x0380
#define QEESROFFSET     0x108C

/* Sizes of EDMA3 register and PaRam regions to map */
#define EDMA3REGSIZE 0x2000
#define PARAMREGSIZE 0x800

/* Align on 4-byte boundary */
#define ALIGN32(x) ((((UInt32)(x) + 3) / 4) * 4)

/* For putting offsets into shared data area rather than addresses */
#define OFFSET(base, address) ((UInt32)address - (UInt32)base)

_DMAN3_Data *_DMAN3_data;
UInt32 _DMAN3_qdmaBase[DMAN3_MAXGROUPS + 1]; 

static int      refCount = 0;   /* Process reference count */

#ifdef xdc_target__os_Linux

static Void freeDman3Obj();
static Bool getDman3Obj();
static Void unMapShm();

#ifndef _DMAN3_CPUCOPY_
static int      memfd;          /* File discriptor for "/dev/mem" */
#endif

static Int      shmId;          /* Shared memory id */
#endif /* xdc_target__os_Linux */

#ifdef _MULTI_PROCESS_
LockMP_Handle _DMAN3_lock = NULL;
#endif

static Void    *shmBase = NULL; /* Base address of shared memory chunk */
static Void    *shmFreeBase;    /* Next available location in shared memory */
static UInt32   shmSize;


static Int      heapInt;
static Int      heapExt;

UInt32          *_DMAN3_paRamAddr = NULL;
UInt32          *_DMAN3_edma3Addr = NULL;
UInt32          _DMAN3_nullPaRam = 0x0;
Int             _DMAN3_initStatus = 0x0;

/*
 *  Functions for allocating and freeing from the shared memory block.
 */
static Void *shmAlloc(Int segid, UInt32 size, UInt32 align);
static Bool shmFree(Int segid, Void *addr, UInt32 size);

static Int getNumAssignedTccs(UInt32 mask32b, UInt32 * maxTcc);
static Void updateTccAllocationTable(UInt32 mask32b, Int base);
static Void initQdmaConfiguration();
static Bool checkDMAN3Configuration();
static Int initializeDMAN3(); 
static Int finalizeDMAN3(); 

/*
 *  ======== _DMAN3_initImpl ========
 *  Initialize the DMAN module
 */
Void _DMAN3_initImpl(Void)
{
    if (refCount == 0) {
        GT_init();
        GT_create(&ti_sdo_fc_dman3_GTMask, DMAN3_GTNAME);
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_DMAN3_initImpl> Enter\n");

    if (refCount++ == 0) {
        heapInt = DMAN3_PARAMS.heapInternal;
        heapExt = DMAN3_PARAMS.heapExternal;

        heapInt = (heapInt == -1) ? heapExt : heapInt;
        heapExt = (heapExt == -1) ? heapInt : heapExt;

        /* This is a fatal configuration error. */
        DBC_assert(heapInt != -1);
        GT_assert(ti_sdo_fc_dman3_GTMask, heapInt != -1);

        _DMAN3_initStatus = initializeDMAN3();
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_DMAN3_initImpl> Exit\n");
}

/*
 *  ======== DMAN3_exit ========
 *  Finalization method of the DMAN3 module
 */
Void DMAN3_exit(Void)
{
    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_exit> Enter\n");

    if (refCount == 0) {
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, "DMAN3_exit> Reference "
                "count already zero, mismatch between DMAN3_init and DMAN3_exit"                "calls\n");
    }
    else {
        --refCount;
    }
    if (0 != _DMAN3_initStatus) {
        finalizeDMAN3();
        _DMAN3_initStatus = 0x0; 
    }
        
    GT_exit();
}

Int finalizeDMAN3()
{

#ifdef _MULTI_PROCESS_
    /* Enter critical section */
    if (_DMAN3_lock != NULL) {
        LockMP_acquire(_DMAN3_lock);
    }
#endif

    if (--_DMAN3_refCount == 0) {
        /*
         *  The global DMAN3 reference count is 0, ie, no other processes
         *  are using DMAN3.
         */
        /* No need to free RMM handles, since they are just offsets */

#ifdef xdc_target__os_Linux
        freeDman3Obj();
#else
#ifdef _YOUR_TARGET_
        /*
         *  TODO: Free the block allocated in DMAN3_initImpl() for
         *  _DMAN3_data
         */
#else
        /* Free _DMAN3_data */
        MEM_free(_DMAN3_heapExt, _DMAN3_data, shmSize);
#endif
#endif
        shmFreeBase = shmBase = NULL;
    }
    else {
        if (refCount == 0) {
            /* Only this process's refCount has gone to 0. */
#ifdef xdc_target__os_Linux
            /* Detach from the shared memory, unmap DMA registers */
            unMapShm();
#endif
#ifdef _YOUR_TARGET_
            /* TODO: Any cleanup that may be needed at this point */
#endif
            shmFreeBase = shmBase = NULL;
       }
    }

#ifdef _MULTI_PROCESS_
    /* Exit critical section */
    if (_DMAN3_lock != NULL) {
        LockMP_release(_DMAN3_lock);

        if (refCount == 0) {
            /* Delete the lock */
            LockMP_delete(_DMAN3_lock);
            _DMAN3_lock = NULL;
        }
        }
#endif

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "finalizeDMAN3> Exit\n");

    return (DMAN3_SOK);

}

Int initializeDMAN3() 
{
#ifndef _DMAN3_CPUCOPY_
    volatile Uns   *qchmap;
    Uns            *paRam;
    UInt32          chipTccs = 0x0;
    UInt32          cccfg = 0x0;
#endif
    RMM_Attrs       rmmAttrs;
    Int             i,chan;
    Int             rmmSize;
    Int             numTccs;
    UInt32          maxId = 0x0;
    UInt32          tempNum = 0x0;
    UInt32          totalQdmas = 0;
    
    /*
     *  First, need to know how many TCCs are used.
     */
    numTccs = getNumAssignedTccs(DMAN3_PARAMS.tccAllocationMaskH, &tempNum);
        
    /*
     *  Check if this allocation is legal    
     */

    /* 
     * Calculate the maximum Id of the tcc allocated. What is returned is 
     * the highest (Tcc number +1) that was configured for DMAN3  */

    if (tempNum > 0) {

        /* Adjust this number by 32 since this is the "H" mask */
        maxId = (tempNum-1) + 32;
    }
        
    numTccs += getNumAssignedTccs(DMAN3_PARAMS.tccAllocationMaskL,&tempNum);

    /* 
     * If the H mask was zero (and hence maxId was 0), then use this
     * returned number to figure out maxId
     */ 
    if (maxId == 0) {
        maxId = (tempNum-1);
    }

    /*
     *  We need to compute the size of the memory chunk that will hold
     *  _DMAN3_data and RMM objects. To compute the amount of memory
     *  needed by RMM, we can do 'dummy' creates of the RMM objects that
     *  will manage the TCCs and PaRams.
     */

    rmmSize = 2 * sizeof(RMM_Obj) + sizeof(RMM_Header) *
            ((DMAN3_PARAMS.numPaRamEntries + 1) / 2 + (numTccs + 1) / 2);

#ifdef _MULTI_PROCESS_

    /* Create a lock for protecting DMAN3 object */
    _DMAN3_lock = LockMP_create(_DMAN3_LOCKID);

    if (_DMAN3_lock == NULL) {
       GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
              "_DMAN3_initImpl> Failed to create IPC lock, key = 0x%x\n",
              _DMAN3_LOCKID);
       GT_assert(ti_sdo_fc_dman3_GTMask, _DMAN3_lock != NULL);

       /* Error condition */ 
       return (0); 
    }

#endif

#ifdef xdc_target__os_Linux
    /* Allocate the _DMAN3_data object for Linux */
    if (!getDman3Obj()) {
        return (0);
    }

#ifndef _DMAN3_CPUCOPY_
    /* Map the DMA registers */
    memfd = open("/dev/mem", O_RDWR | O_SYNC);
    _DMAN3_paRamAddr = mmap(0, PARAMREGSIZE, PROT_READ | PROT_WRITE,
           MAP_SHARED, memfd, (off_t)DMAN3_PARAMS.qdmaPaRamBase);

    _DMAN3_edma3Addr = mmap(0, EDMA3REGSIZE,
           PROT_READ | PROT_WRITE, MAP_SHARED, memfd,
           (off_t)((UInt32)DMAN3_PARAMS.qdmaPaRamBase - PARAMOFFSET));
#endif

#else
#ifdef _YOUR_TARGET_
    /*
     *  TODO: Allocate a block of memory for the _DMAN3_data object and
     *  other data that will be placed after the _DMAN3_data object. The
     *  size should be at least:
     *      sizeof(_DMAN3_Data) + rmmSize.
     *
     *  TODO: Set shmSize to the size of the allocated block.
     *  TODO: Set shmBase to the base address of the allocated block.
     *
     *  TODO: Set _DMAN3_data to the beginning of the allocated block,
     *        but make sure it is aligned on a 32 bit boundary.
     *
     *  TODO: Set shmFreeBase to the address of the first word after
     *        _DMAN3_data (see code below for an example).
     */

    /*
     *  TODO: Initialize _DMAN3_paRamAddr to the virtual or physical
     *  address of DMAN3_PARAMS.qdmaPaRamBase.
     */

    /*
     *  TODO: Initialize _DMAN3_edma3Addr to the virtual or physical
     *  address of (UInt32)DMAN3_PARAMS.qdmaPaRamBase - PARAMOFFSET.
     */
#else
    /*
     *  Allocate a block of memory for the _DMAN3_data object and
     *  other data that will be placed after the _DMAN3_data object. The
     *  size should be at least:
     *      sizeof(_DMAN3_Data) + rmmSize
     *  but we will add a little extra to be safe.
     */
    shmSize = sizeof(_DMAN3_Data) + rmmSize + 32;
    _DMAN3_data = (_DMAN3_Data *)MEM_calloc(DMAN3_PARAMS.heapExternal,
           shmSize, 0);

    /* Set shmBase to the base address of the allocated block. */
    shmBase = (Void *)_DMAN3_data;

    /* Make sure the shared memory base is aligned */
    shmFreeBase = (Void *)((UInt32)shmBase + ALIGN32(sizeof(_DMAN3_Data)));

    /* Start address of PaRams */
    _DMAN3_paRamAddr = DMAN3_PARAMS.qdmaPaRamBase;

    /* Start address of EDMA3 registers */
    _DMAN3_edma3Addr = (UInt32 *)((UInt32)DMAN3_PARAMS.qdmaPaRamBase -
           PARAMOFFSET);

#endif
#endif /* #ifdef xdc_target__os_Linux */

#ifndef _DMAN3_CPUCOPY_
    cccfg =  *(((volatile Uns *)_DMAN3_edma3Addr)+1);
    chipTccs = ( (( ((cccfg)>>8)&0x7)==0) ? 0 : 
           (0x4 << (((cccfg)>>8) & 0x7)) );
    if (maxId >= chipTccs) {

        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_6CLASS,
               "_DMAN3_initImpl> DMAN3 tccAllocationMaskH configures tcc "
               "%d, that is more than available on hardware %d\n", 
               maxId , numTccs);

        GT_assert(ti_sdo_fc_dman3_GTMask, 0);
       /* Error condition */ 
       return (0); 
    }
#endif

#ifdef _MULTI_PROCESS_
    /* Enter critical section */
    LockMP_acquire(_DMAN3_lock);
#endif

    if (_DMAN3_refCount++ == 0) {
        /* Initialize to _DMAN3_data object */

#ifndef xdc_target__isaCompatible_64P
        /* Scratch env not supported for non-DSP targets */
        _DMAN3_allocScratch = NULL;
        _DMAN3_freeScratch = NULL;
#else
        /*
         *  Configured function for allocating IDMA3 object's env from
         *  shared scratch memory.
         */
        _DMAN3_allocScratch = DMAN3_PARAMS.scratchAllocFxn;

        /*
         *  Configured function for allocating IDMA3 object's env from
         *  shared scratch memory.
         */
        _DMAN3_freeScratch = DMAN3_PARAMS.scratchFreeFxn;

        /*
         *  If one of _DMAN3_allocScratch or _DMAN3_freeScratch is NULL,
         *  then the other must be NULL.
         */
        DBC_require((_DMAN3_allocScratch != NULL) ||
                    (_DMAN3_freeScratch == NULL));
        DBC_require((_DMAN3_freeScratch != NULL) ||
                    (_DMAN3_allocScratch == NULL));
        GT_assert(ti_sdo_fc_dman3_GTMask, (_DMAN3_allocScratch != NULL) ||
                    (_DMAN3_freeScratch == NULL));
        GT_assert(ti_sdo_fc_dman3_GTMask, (_DMAN3_freeScratch != NULL) ||
                    (_DMAN3_allocScratch == NULL));
#endif

        /*
         * Initialize the tccAllocationTable with the provided TCCs.
         * Use the TCCs assigned in the High range (32-63) first, then
         * Low (0-31) when initializing the _DMAN3_tccAllocationTable.
         * Update the total number of assigned TCC count
         * (_DMAN3_numAssignedTccs)
         */
        _DMAN3_numAssignedTccs = 0;
        updateTccAllocationTable(DMAN3_PARAMS.tccAllocationMaskH, 32);
        updateTccAllocationTable(DMAN3_PARAMS.tccAllocationMaskL, 0);

        /*
         *  Initialize _DMAN3_heapInt and _DMAN3_heapExt with provided
         *  heaps. Use internal heap for _DMAN3_heapInt when provided.
         *  (Actually this is a fatal error if ACPY3 uses internal DMA
         *  (IDMA) to write to PARAMs.
         */
        _DMAN3_heapInt = heapInt;
        _DMAN3_heapExt = heapExt;

        _DMAN3_heapIdma3 = (DMAN3_PARAMS.idma3Internal) ?
                    heapInt : heapExt;

    
        for (i = 0; i < DMAN3_MAXGROUPS; i++) {
            _DMAN3_numTccGroup[i] = DMAN3_PARAMS.numTccGroup[i];
            _DMAN3_numPaRamGroup[i] = DMAN3_PARAMS.numPaRamGroup[i];
        }

        /* Initialize _DMAN3_data->context[] to offsets in shared memory */
        for (i = 0; i < DMAN3_MAXGROUPS; i++) {
            _DMAN3_data->context[i] = OFFSET(_DMAN3_data,
                    &(_DMAN3_data->contextObjs[i]));
        }

        /*
         *  Attributes of TCC array that will be managed by RMM for
         *  allocation:
         *    segid - Use the external memory for the RMM object.
         *    base = 0 - We allocate indices of the array, starting with 0
         *    length = _DMAN3_numAssignedTccs - the number of TCCs in the array
         *    maxFreeListBlocks - Set to maximum number of free (unallocated)
         *        blocks that the array can fragment into. This happens when
         *        every other index is free.
         */
        rmmAttrs.segid = _DMAN3_heapExt;
        rmmAttrs.base = 0;
        rmmAttrs.length = _DMAN3_numAssignedTccs;
        rmmAttrs.maxFreeListBlocks = (_DMAN3_numAssignedTccs + 1) / 2;
        rmmAttrs.allocFxn = shmAlloc;
        rmmAttrs.freeFxn = shmFree;

        /*
         *  Can't put a pointer in shared memory area if it's shared by
         *  different processes. Therefore, we store the offset from the
         *  _DMAN3_data.
         */
        _DMAN3_data->rmmTccs = OFFSET(_DMAN3_data, RMM_create(&rmmAttrs));

        DBC_assert(_DMAN3_rmmTccs != MEM_ILLEGAL);
        GT_assert(ti_sdo_fc_dman3_GTMask, _DMAN3_rmmTccs != MEM_ILLEGAL);
        if (_DMAN3_rmmTccs == MEM_ILLEGAL) {
            return (0);
        }

        /*
         *  Attributes of PaRam entry numbers that will be managed by RMM for
         *  allocation:
         *    segid - Use the external memory for the RMM object.
         *    base - The first PaRam index for DMAN3.
         *    length - Number of PaRam entries for DMAN3.
         *    maxFreeListBlocks - Set to maximum number of free (unallocated)
         *        blocks that can PaRam indices can fragment into. This
         *        happens when every other index is free.
         */
        rmmAttrs.base = DMAN3_PARAMS.paRamBaseIndex;
        rmmAttrs.length = DMAN3_PARAMS.numPaRamEntries;
        rmmAttrs.maxFreeListBlocks = (DMAN3_PARAMS.numPaRamEntries + 1) / 2;

        _DMAN3_data->rmmPaRams = OFFSET(_DMAN3_data, RMM_create(&rmmAttrs));

        DBC_assert(_DMAN3_rmmPaRams != MEM_ILLEGAL);
        GT_assert(ti_sdo_fc_dman3_GTMask, _DMAN3_rmmPaRams != MEM_ILLEGAL);

        if (_DMAN3_rmmPaRams == MEM_ILLEGAL) {
            return (0);
        }
        
                //TODO: Distribute channels among scratch groups
        totalQdmas = 0;

        if (ti_sdo_fc_dman3_DMAN3_useCustomDma) {

                for (i =0; i < DMAN3_MAXGROUPS; i++) {

            //_DMAN3_data->qdmaGroupNum[i] = 
            //        ti_sdo_fc_dman3_DMAN3_numQdmaGroup[i];

                if (_DMAN3_numQdmaGroup(i) > 0 ) {
                        GT_assert(ti_sdo_fc_dman3_GTMask, 
                                totalQdmas < DMAN3_PARAMS.numQdmaChannels);  
                
                                        /* Set the allocation base for each scratch group */ 
                        _DMAN3_qdmaBase[i] = totalQdmas;

                                //_DMAN3_data->qdmaGroupBase[i] = totalQdmas;
                //_DMAN3_data->qdmaGroupCounter[i] = 
                 //       _DMAN3_data->qdmaGroupBase[i];
                }
                else {
                        //TODO: Should this be set to "0" ?
                        _DMAN3_qdmaBase[i] = -1;
                                        //_DMAN3_data->qdmaGroupBase[i] = -1;
                        //_DMAN3_data->qdmaGroupCounter[i] = -1;
                }
                totalQdmas += _DMAN3_numQdmaGroup(i);
                } 

                /* Leave the rest of the QDMA channels (if any) to scratch group -1 */ 
                _DMAN3_data->qdmaPersistentNum = 
                        DMAN3_PARAMS.numQdmaChannels - totalQdmas;
                        _DMAN3_data->qdmaPersistentBase = totalQdmas;

                //_DMAN3_data->qdmaGroupBase[DMAN3_MAXGROUPS] = totalQdmas;
        }
        else {
                for (i =0; i < DMAN3_MAXGROUPS; i++) {
                _DMAN3_qdmaBase[i] = 0;
                ti_sdo_fc_dman3_DMAN3_numQdmaGroup[i] = 
                            DMAN3_PARAMS.numQdmaChannels;
                        //_DMAN3_data->qdmaGroupBase[i] = 0;
            //_DMAN3_data->qdmaGroupNum[i] = DMAN3_PARAMS.numQdmaChannels;
            //_DMAN3_data->qdmaGroupCounter[i] = i;
                }
                _DMAN3_data->qdmaPersistentNum = DMAN3_PARAMS.numQdmaChannels;
                        _DMAN3_data->qdmaPersistentBase = 0;
        
                }

    _DMAN3_nullPaRam = DMAN3_PARAMS.nullPaRamIndex;
    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
            "_DMAN3_initImpl> Null PaRam is %d\n", _DMAN3_nullPaRam);

#ifndef _DMAN3_CPUCOPY_
        /* Set qchmap to address of first QCHMAP register */
        qchmap = (volatile Uns *)((Uns)_DMAN3_edma3Addr + QCHMAPOFFSET);

        /*
         *  All channels owned by DMAN3 should point to the Null PARAM with 
         *  trigger word set to 7. This is so that no transfers are triggered
         *  accidentally when Null PARAM is edited to set its static bit to 0. 
         *  If there are any other QDMA channels however, that are also pointing
         *  to Null PaRAM, then they are illegally sharing a resource with DMAN3
         *  To avoid accidental transfers, their trigger word is also set to 7.
         *  Note:-  The above scenario, may occur if the Null PARAM is set to 0.
         *  On reset, QDMA channels come up mapped to PaRAM 0, if that isn't 
         *  changed to some other PaRAM for channels not owned by DMAN3, any
         *  edits to PaRAM 0, might result in accidental transfers.   
         */

        /* If channel belongs to DMAN3, point it to null param */ 
        for (i = 0; i < DMAN3_PARAMS.numQdmaChannels; i++) {
            chan = DMAN3_PARAMS.qdmaChannels[i];
            qchmap[chan] = (Uns)(_DMAN3_nullPaRam << 5); 
        }

        for (i = 0; i < DMAN3_PARAMS.maxQdmaChannels; i++) {
            /* Even if channel doesnt' belong to DMAN3, but points to null param
               change trigger word to # 7 */ 
            if (_DMAN3_nullPaRam == ((*qchmap >> 5 ) & 0x1FF)) {
                GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS,
                        "_DMAN3_initImpl> Qdma channel %d is pointing to "
                        "the nullPaRam. Change its trigger word bit to 0x7 so "
                        "it doesn't get triggered when we modify the null "
                        "PaRam\n", i);
                *qchmap = *qchmap | (0x7 << 2);
            }
            qchmap++;
        }

        /*
         *  Set the static bit of opts field of the null PaRam, since
         *  QCHMAP may get set to this PaRam when the channel is
         *  activated/deactivated. (The opts field is the first word of the
         *  PaRam entry).
         */
        paRam = (Uns *)((Uns)_DMAN3_paRamAddr +
                (_DMAN3_nullPaRam * PARAMENTRYSIZE * sizeof(UInt32)));

        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_2CLASS, "_DMAN3_initImpl> "
               "Setting static bit of null paRam (address = 0x%x)\n", paRam);
        *paRam |= 0x8;
#endif

        if (FALSE == checkDMAN3Configuration(_DMAN3_numAssignedTccs)) {
           GT_0trace(ti_sdo_fc_dman3_GTMask, GT_6CLASS, "_DMAN3_initImpl> "
                   "DMAN3 SOC-specific configuration different from hardware, "
                   "continuing with configured values\n");
        }

        initQdmaConfiguration();
    }

#ifdef _MULTI_PROCESS_
    /* Exit critical section */
    LockMP_release(_DMAN3_lock);
#endif

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_DMAN3_initImpl> "
            "Exiting, _DMAN3_data = 0x%x\n", _DMAN3_data);

    return (1);
}



/*
 *  ======== getNumAssignedTccs ========
 */
static Int getNumAssignedTccs(UInt32 mask32b, UInt32 * maxTcc)
{
    Int numTccs = 0;
    Int i;

    *maxTcc = 0x0;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getNumAssignedTccs> Enter\n");

    for (i = 0; i < 32; i++) {
        if (mask32b & (0x1 << i)) {
            numTccs++;
            *maxTcc = i+1; 
        }
    }
    
    
    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_4CLASS, "getNumAssignedTccs> Max TCC"
            " is 0x%x\n", *maxTcc);

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "getNumAssignedTccs> Exit\n");

    return (numTccs);
}


/* Functions for RMM to alloc and free its objects from shared memory */

/*
 *  ======== shmAlloc ========
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
static Void *shmAlloc(Int segid, UInt32 size, UInt32 align)
{
    UInt32  nFreeBytes;
    Void   *base;
    UInt32  alnSize;

    GT_3trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "DMAN3 shmAlloc> segid = %d, size = 0x%x, align = 0x%x\n",
            segid, size, align);

    /*
     *  Don't need to handle align parameter (yet). Just align size on
     *  4-byte boundary.
     */
    alnSize = ALIGN32(size);

    /* Number of bytes remaining in the shared memory chunk */
    nFreeBytes = shmSize + (UInt32)shmBase -(UInt32)shmFreeBase;

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "DMAN3 shmAlloc> bytes remaining before allocation: 0x%x\n",
            nFreeBytes);

    if (alnSize > nFreeBytes) {
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "DMAN3 shmAlloc> Shared memory allocation of [0x%x] bytes "
                "failed. Remaining free bytes: [0x%x]\n", alnSize, nFreeBytes);
        return (NULL);
    }

    base = shmFreeBase;
    shmFreeBase = (Void *)((UInt32)shmFreeBase + alnSize);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "DMAN3 shmAlloc> bytes remaining after allocation: 0x%x\n",
            shmSize + (UInt32)shmBase - (UInt32)shmFreeBase);

    memset((void *)base, 0, size);

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "DMAN3 shmAlloc> returning base address: 0x%x\n", base);

    return (base);
}

/*
 *  ======== shmFree ========
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
static Bool shmFree(Int segid, Void *addr, UInt32 size)
{
    return (TRUE);
}

/*
 *  ======== updateTccAllocationTable ========
 */
static Void updateTccAllocationTable(UInt32 mask32b, Int base)
{
    Int i;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "updateTccAllocationTable> "
            "Enter\n");

    for (i = 0; i < 32; i++) {

        if (mask32b & (0x1 << i)) {
            _DMAN3_tccAllocationTable[_DMAN3_numAssignedTccs++] = base + i;
        }
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "updateTccAllocationTable> Exit\n");
}

/*
 * ======== checkDMAN3Configuration ========
 */
/* ARGSUSED */
static Bool checkDMAN3Configuration(Int tccs)
{
    Bool status = TRUE;
#ifndef _DMAN3_CPUCOPY_
    Uns cccfg = 0x0;
    short numQdma = 0;
    short numParam = 0;
    short numTC = 0;
    volatile Uns * edma3Base = (Uns *)_DMAN3_edma3Addr;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "checkDMAN3Configuration> Enter\n");

    cccfg = edma3Base[1];
    cccfg = (edma3Base[1] >> 4);

    numQdma = (cccfg & 0x7) << 0x1;

    if  (DMAN3_PARAMS.maxQdmaChannels != numQdma) {
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_6CLASS,
                "checkDMAN3Configuration> DMAN3 max QDMA channels configured "
                "to be %d, hardware reads %d\n", DMAN3_PARAMS.maxQdmaChannels,
                numQdma);

        status = FALSE;
    }

    cccfg = (cccfg >> 4);
    cccfg = (cccfg >> 4);
    numParam = (((cccfg & 0x7) == 0) ? 0x0 : (0x10 << (cccfg & 0x7)));

    if  (DMAN3_PARAMS.maxPaRamEntries != numParam) {
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_6CLASS,
                "checkDMAN3Configuration> DMAN3 max PaRam entries configured "
                "to be %d, hardware reads %d\n", DMAN3_PARAMS.maxPaRamEntries,
                numParam);

        status = FALSE;
    }

    cccfg = (cccfg>>4);
    numTC = (cccfg &0x7) + 1;

    if  (DMAN3_PARAMS.maxTCs != numTC) {
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_6CLASS,
                "checkDMAN3Configuration> DMAN3 max TCs configured to be %d, "
                "hardware reads %d\n", DMAN3_PARAMS.maxTCs, numTC);

        status = FALSE;
    }
#endif

    GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "checkDMAN3Configuration> Exit (status=%d)\n", status);

    return (status);
}

/*
 *  ======== initQdmaConfiguration ========
 */
static Void initQdmaConfiguration()
{
#ifndef _DMAN3_CPUCOPY_
    Int i,chan;
    UInt32 * addr;
    Uns queueNum;
    Uns qeesr;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "_initQdmaConfiguration> Enter\n");

    /* Event queue to TC channel mapping */
    addr = (UInt32 *)((UInt32)_DMAN3_edma3Addr + QUETCMAPOFFSET);
    for (i = 0 ; i < DMAN3_PARAMS.maxTCs; i++) {
        (*addr) |= (DMAN3_PARAMS.queueTCMap[i] << (i *4));
    }

    /* Set Priority for each of the event queues. */
    addr = (UInt32 *)((UInt32)_DMAN3_edma3Addr + QUEPRIOFFSET);
    for (i = 0; i < DMAN3_PARAMS.maxTCs; i++) {
        (*addr) |= ( DMAN3_PARAMS.queuePri[i] << (i * 4));
    }

    /* QDMA region access enable register 0 */
    addr = (UInt32 *)((UInt32)_DMAN3_edma3Addr + QRAE0OFFSET);
    (*addr) = 0xFF;

    /* Set QDMA to queue mapping */
    addr = (UInt32 *)((UInt32)_DMAN3_edma3Addr + QDMAQNUMOFFSET);
    for (i = 0; i < DMAN3_PARAMS.numQdmaChannels; i++) {
        chan = DMAN3_PARAMS.qdmaChannels[i];
        queueNum = DMAN3_PARAMS.qdmaQueueMap[i];
        (*addr) |= (queueNum << (4 * chan));
    }

    /* Queue Event Enable Set register */
    qeesr = 0x0;
    for (i = 0; i < DMAN3_PARAMS.numQdmaChannels; i++) {
        qeesr |= (0x1 << DMAN3_PARAMS.qdmaChannels[i]);
    }
    addr = (UInt32 *)((UInt32)_DMAN3_edma3Addr + QEESROFFSET);
    (*addr) = qeesr;

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
            "_initQdmaConfiguration> Exit\n");

#endif /* DMAN3_CPUCOPY */
}

#ifdef xdc_target__os_Linux

/*
 *  ======== freeDman3Obj ========
 */
static Void freeDman3Obj()
{
#ifndef _DMAN3_CPUCOPY_
    /* close memfd, unmap */
    if (munmap(_DMAN3_edma3Addr, EDMA3REGSIZE) == -1) {
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to unmap _DMAN3_edma3Addr [0x%x]\n",
                _DMAN3_edma3Addr);
    }

    if (munmap(_DMAN3_paRamAddr, PARAMREGSIZE) == -1) {
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to unmap _DMAN3_paRamAddr [0x%x]\n",
                _DMAN3_paRamAddr);
    }

    close(memfd);
#endif
    /* Detach the shared memory */
    if (shmdt(shmBase) == -1) {
        /* error */
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to detach shared memory [0x%x], key = 0x%x\n",
                shmBase, _DMAN3_SHMID);
    }

    /* Free the shared memory */
    if (shmctl(shmId, IPC_RMID, 0) == -1) {
        /* error */
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to free shared memory [0x%x], key = 0x%x\n",
                shmBase, _DMAN3_SHMID);
    }
}

/*
 *  ======== getDman3Obj ========
 */
static Bool getDman3Obj()
{
    Bool            shmExists = TRUE;
    Int             lockRefCount;

#ifdef _MULTI_PROCESS_
    /* Enter critical section */
    LockMP_acquire(_DMAN3_lock);
#endif

    /*
     *  Allocate or locate the chunk of shared memory where internal
     *  DMAN3 objects will be placed. This is to ensure that multiple
     *  processes will see the same DMAN3 objects.
     *  First attempt to get the shared memory without the IPC_CREAT
     *  flag, to see if it's already been created.
     */
    shmSize = SHMSIZE;
    shmId = shmget((key_t)(_DMAN3_SHMID), SHMSIZE, 0666);
    if (shmId == -1) {
        /*
         *  Failed to get the shared memory, so it probably hasn't been
         *  created yet.
         */
        shmId = shmget((key_t)(_DMAN3_SHMID), SHMSIZE, 0666 | IPC_CREAT);
        if (shmId == -1) {
            /* Couldn't create the shared memory */
            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                    "_DMAN3_initImpl> Failed to create shared memory "
                    "region, key = 0x%x\n", _DMAN3_SHMID);

#ifdef _MULTI_PROCESS_
            /* Exit critical section */
            LockMP_release(_DMAN3_lock);
#endif
            /* Abort*/
            GT_assert(ti_sdo_fc_dman3_GTMask, shmId != -1);
            return (FALSE);
        }
        else {
            /* The segment had not been created before */
            GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                    "_DMAN3_initImpl> Created shared memory, key = 0x%x\n",
                    _DMAN3_SHMID);
            shmExists = FALSE;
        }
    }
    else {
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "_DMAN3_initImpl> Shared memory, key = 0x%x already"
                " exists\n", _DMAN3_SHMID);
    }

    /* Get the address of the shared memory region with shmat() */
    shmBase = shmat(shmId, NULL, 0);
    if (shmBase == (Void *)-1) {
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "_DMAN3_initImpl> Failed to get shared memory address, "
                "key = 0x%x\n", _DMAN3_SHMID);
        shmBase = NULL;

#ifdef _MULTI_PROCESS_
        /* Exit critical section */
        LockMP_release(_DMAN3_lock);
#endif
        /* Abort */
        GT_assert(ti_sdo_fc_dman3_GTMask, shmBase != NULL);
        return (FALSE);
    }

    /* Make sure the shared memory base is aligned */
    shmFreeBase = (Void *)ALIGN32(shmBase);

    _DMAN3_data = shmFreeBase;

    /* Make sure the shared memory base is aligned */
    shmFreeBase = (Void *)((UInt32)shmBase + ALIGN32(sizeof(_DMAN3_Data)));

    if (shmExists) {
        /*
         *  Shared memory segment already exists. Check the DMAN3 lock
         *  reference count. Since the lock is created only once per
         *  process, if the lock reference count is 1, the calling process
         *  is the only one using DMAN3 global data. In that case, a
         *  process must have died, and will re-initialize the DMAN3
         *  global data.
         */
        lockRefCount = LockMP_getRefCount(_DMAN3_lock);

        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_DMAN3_initImpl> "
                "DMAN3 shared memory reference count = %d\n"
                "DMAN3 lock reference count = %d\n",
                _DMAN3_refCount, lockRefCount);

        if (lockRefCount == 1) {
            GT_2trace(ti_sdo_fc_dman3_GTMask, GT_5CLASS,
                    "_DMAN3_initImpl> Warning: Inconsistent reference"
                    " count between DMAN3 shared memory [%d] and lock"
                    " [%d]\n", _DMAN3_refCount, lockRefCount);
            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_5CLASS,
                    "_DMAN3_initImpl> Warning: DMAN3 lock reference "
                    "count indicates no other processes are "
                    "currently using DMAN3 shared memory.  "
                    "Re-initializing DMAN3 shared memory\n");

            /* This will cause the DMAN3 data to be re-initialized */
            shmExists = FALSE;
        }
    }

    if (!shmExists) {
        /* Initialize the reference count in the shared data area */
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER,
                "Initializing DMAN3 shared data\n");
        _DMAN3_refCount = 0;

        /* Initialize the _DMAN3_data object to 0's */
        memset((Void *)_DMAN3_data, 0, sizeof(_DMAN3_Data));
    }

#ifdef _MULTI_PROCESS_
    /* Exit critical section */
    LockMP_release(_DMAN3_lock);
#endif
    return (TRUE);
}

/*
 *  ======== unMapShm ========
 */
static Void unMapShm()
{
#ifndef _DMAN3_CPUCOPY_
    /* close memfd, unmap */
    if (munmap(_DMAN3_edma3Addr, EDMA3REGSIZE) == -1) {
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to unmap _DMAN3_edma3Addr [0x%x]\n",
                _DMAN3_edma3Addr);
    }

    if (munmap(_DMAN3_paRamAddr, PARAMREGSIZE) == -1) {
        GT_1trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to unmap _DMAN3_paRamAddr [0x%x]\n",
                _DMAN3_paRamAddr);
    }

    close(memfd);
#endif
    /*
     *  Don't move this block of code. Cannot detach shmBase until
     *  _DMAN3_refCount is checked.
     */
    /* Detach the shared memory, but don't free it. */
    if (shmdt(shmBase) == -1) {
        /* error */
        GT_2trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                "Failed to detach shared memory [0x%x], key = 0x%x\n",
                shmBase, _DMAN3_SHMID);
    }
}

#endif
/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

