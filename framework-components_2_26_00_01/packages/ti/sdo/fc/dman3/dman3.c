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
 *  ======== dman3.c ========
 */

#include <xdc/std.h>

#include "dman3.h"

/*
 *  ======== DMAN3 ========
 *  This static initialization defines the default parameters used to
 *  initialize the DMAN3 module.
 */


/*
 * DMAN3_QDMA_PARAM_BASE: Default Physical base address for PARAM0 in the 
 * EDMA3/QDMA hardware whose resources are being managed by DMAN3. 
 *
 * DMAN3_MAX_PARAM_ENTRIES: Default total numbar of PaRam entries on the
 * hardware (= 128 for IVA2).
 *
 * DMAN3_PARAM_BASE_INDEX: (0>value>255) represents the first PARAM TABLE ENTRY
 * NUMBER that is assigned by configuration for exclusive DMAN3 allocation.
 *
 * The DMAN3_NUM_CONTIGUOUS_PARAM_ENTRIES many PARAM Table entries starting at
 * DMAN3_PARAM_BASE_INDEX are assigned by configuration for exclusive DMAN3 
 * allocation.
 */
#define DMAN3_QDMA_PARAM_BASE  (Uns *)((Uns)0x01C00000 + 0x4000)
#define DMAN3_MAX_PARAM_ENTRIES 128
#define DMAN3_PARAM_BASE_INDEX 96
#define DMAN3_NUM_CONTIGUOUS_PARAM_ENTRIES  32

/* 
 * DMAN3_MAX_QDMA_CHANNELS: contains the total number of Physical QDMA channels
 * available on the hardware (eg, 4 for IVA2).
 *
 * DMAN3_NUM_QDMA_CHANNELS: contains the number of Physical QDMA channels
 * that are assigned to DMAN3 via configuration.
 *
 * DMAN3_QDMA_CHANNELS: array containing list of DMAN3_NUM_QDMA_CHANNELS
 * many Physical QDMA channels assigned to DMAN3 via configuration.
 */
#define DMAN3_MAX_QDMA_CHANNELS   8 
#define DMAN3_NUM_QDMA_CHANNELS   8 
__FAR__ Uns DMAN3_QDMA_CHANNELS[] = {0, 1, 2, 3, 4, 5, 6, 7};

__FAR__ Bool ti_sdo_fc_dman3_DMAN3_useCustomDma = FALSE;

/* 
 * DMAN3_TCC_FREEMASK_H and DMAN3_TCC_FREEMASK_L:  are 32-bit bitmasks 
 * representing configuration provided list of TCCs for exclusive DMAN3 
 * allocation.
 * 
 * For example, for TCC's in the range 0-31 the Low Mask (DMAN3_TCC_FREEMASK_L)
 * is configured so that a '1' in bit position 'i' indicates the TCC 'i' is 
 * assigned to DMAN3
 */
#define DMAN3_TCC_FREEMASK_H  0xFFFFAFF7 
#define DMAN3_TCC_FREEMASK_L  0x05 

 /*
  * DMAN3_HEAP_INTERNAL: BIOS Heap ID for dynamic allocation of DMAN3 objects 
  * must be allocated in L1D Internal RAM.
  * DMAN3_HEAP_EXTERNAL: BIOS Heap ID for dyn allocation of private DMAN3
  * data structures. 
  * A value of -1 indicates that the heap is not defined.
  */
#define DMAN3_HEAP_INTERNAL  -1 
#define DMAN3_HEAP_EXTERNAL  0 

/*
 *  DMAN3_IDMA3INTERNAL: Use the internal DMAN3 memory heap to allocate IDMA3
 *  objects.
 */
#define DMAN3_IDMA3INTERNAL  1

#define DMAN3_SCRATCHALLOCFXN NULL
#define DMAN3_SCRATCHFREEFXN  NULL

#define DMAN3_NULLPARAM 0

/*
 *  DMAN3_ALLOWUNSHARED: Allow more TCCs or PaRams to be allocated to a given
 *  scratch group than the number configured. Also allow allocation of unshared
 *  TCCs and PaRams to an algorithm, if the number currently allocated to the
 *  scratch group is less than requested by the algorithm.
 */
#define DMAN3_ALLOWUNSHARED  1

__FAR__ Int DMAN3_heapInternal = DMAN3_HEAP_INTERNAL;
__FAR__ Int DMAN3_heapExternal = DMAN3_HEAP_EXTERNAL;

/* New DMAN3 configuration parameters */

#define DMAN3_MAX_TCS 4

__FAR__ Uns DMAN3_QDMA_QUEUE_MAP[] = {1,1,1,1,1,1,1,1};

__FAR__ Uns DMAN3_QUEUE_TC_MAP[] = {0,1,2,3};

__FAR__ Uns DMAN3_QUEUE_PRIORITIES[] = {3,7,0,0};

__FAR__ Uns ti_sdo_fc_dman3_DMAN3_numQdmaGroup[] = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,
        0,0,0,0,0,0};
/*
 *  ======== DMAN3_Config ========
 *  Default module configuration structure for DMAN3 implementation.
 *  It is set at design time by the system integrator to adjust the behavior
 *  of the module to be optimal for its execution environment.
 */
DMAN3_Params DMAN3_PARAMS = {

    /* qdmaPaRamBase: Physical base address for PARAM0 */
    DMAN3_QDMA_PARAM_BASE,

    /* maxPaRamEntries: Total number of PaRam entries */
    DMAN3_MAX_PARAM_ENTRIES,

    /*
     * paRamBaseIndex: (0>value>255) represents the first PARAM TABLE ENTRY
     * NUMBER that is assigned by configuration for exclusive DMAN3 allocation.
     */
    DMAN3_PARAM_BASE_INDEX,
 
    /*
     * numPaRamEntries:  number of PARAM Table entries starting at
     * DMAN3_PARAM_BASE_INDEX assigned by configuration for exclusive DMAN3 
     * allocation.
     */
    DMAN3_NUM_CONTIGUOUS_PARAM_ENTRIES,

    /* 
     * maxQdmaChannels: total number of Physical QDMA channels on the hardware.
     *
     * numQdmaChannels: contains the number of Physical QDMA channels
     * that are assigned to DMAN3 via configuration.
     * qdmaChannels: array containing list of DMAN3_NUM_QDMA_CHANNELS
     * many Physical QDMA channels assigned to DMAN3 via configuration.
     */
    DMAN3_MAX_QDMA_CHANNELS,
    DMAN3_NUM_QDMA_CHANNELS,
    DMAN3_QDMA_CHANNELS,

    /* 
     * tccAllocationMaskH and tccAllocationMaskL:  are 32-bit bitmasks 
     * representing configuration provided list of TCCs for exclusive DMAN3 
     * allocation.
     * 
     * For example, for TCC's in the range 0-31 the Low Mask (tccAllocationMaskL)
     * is configured so that a '1' in bit position 'i' indicates the TCC 'i' is 
     * assigned to DMAN3
     */
    DMAN3_TCC_FREEMASK_H, 
    DMAN3_TCC_FREEMASK_L,

     /*
      * heapInternal: BIOS Heap ID for dynamic allocation of DMAN3 objects 
      * must be allocated in L1D Internal RAM.
      * heapExternal: BIOS Heap ID for dyn allocation of private DMAN3
      * data structures. 
      *
      * A value of -1 indicates that the heap is NOT DEFINED.
      */
    DMAN3_HEAP_INTERNAL,
    DMAN3_HEAP_EXTERNAL,

    /* numTccGroup[DMAN3_MAXGROUPS] */
    {4,  4, 4, 4, 4,
     0,  0, 0, 0, 0,
     0,  0, 0, 0, 0,
     0,  0, 0, 0, 0
    },

    /* numPaRamGroup[DMAN3_MAXGROUPS] */
    {4,  4, 4, 4, 4,
     0,  0, 0, 0, 0,
     0,  0, 0, 0, 0,
     0,  0, 0, 0, 0
    },

    /* idma3Internal: Are IDMA3 objects allocated in internal memory? */
    DMAN3_IDMA3INTERNAL,

    /* scratchAllocFxn*/
    DMAN3_SCRATCHALLOCFXN,

    /* scratchFreeFxn*/
    DMAN3_SCRATCHFREEFXN,

    /* nullPaRamIndex */
    DMAN3_NULLPARAM,

    /* maxTCs */
    DMAN3_MAX_TCS,

    /* qdmaQueueMap */
    DMAN3_QDMA_QUEUE_MAP,

    /* queueTCMap */
    DMAN3_QUEUE_TC_MAP,

    /* queuePri */
    DMAN3_QUEUE_PRIORITIES,

    /* allowUnshared */
    DMAN3_ALLOWUNSHARED,
};

/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

