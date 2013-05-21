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
 *  ======== dman3_externalRM_initImpl.c ========
 *  Initialize the DMAN3 module
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>  /* Need this so that _TI_ is defined */


#include <ti/sdo/fc/utils/dbc.h>
#include <ti/bios/include/mem.h>
#include <ti/bios/include/lck.h>

#include "rmm.h"
#include "dman3.h"
#include "dman3_externalRM_impl.h"
#include <ti/sdo/fc/edma3/edma3_config.h>

#include <ti/sdo/utils/trace/gt.h>
GT_Mask ti_sdo_fc_dman3_GTMask;

#pragma CODE_SECTION(_DMAN3_initImpl, ".text:DMAN3_init");

far Int _DMAN3_heapInt;
far Int _DMAN3_heapExt;
far Int _DMAN3_heapIdma3;

far DMAN3_ScratchAllocFxn _DMAN3_allocScratch = NULL;
far DMAN3_ScratchFreeFxn _DMAN3_freeScratch = NULL;

far Uns _DMAN3_qdmaIndex = 0;

far DMAN3_QdmaObj * DMAN3_QDMA;
 
EDMA3_RM_Handle _DMAN3_systemRMHandle = NULL;

UInt32          *_DMAN3_paRamAddr = NULL;
UInt32          *_DMAN3_edma3Addr = NULL;
UInt32          _DMAN3_nullPaRam = 0x0;

UInt32 _DMAN3_qdmaBase[DMAN3_MAXGROUPS + 1]; 
UInt32 _DMAN3_qdmaCounter[DMAN3_MAXGROUPS + 1]; 

static Int _DMAN3_refCount = 0;

LCK_Handle _DMAN3_lock = (LCK_Handle)NULL;


/*
 *  ======== _DMAN3_initImpl ========
 *  Initialize the DMAN module
 */
Void _DMAN3_initImpl(Void)
{
    Int totalQdmas = -1;
    Int i = -1;

    if (_DMAN3_refCount == 0) {
        GT_init();
        GT_create(&ti_sdo_fc_dman3_GTMask, DMAN3_GTNAME);
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "_DMAN3_initImpl> Enter\n");

    if (_DMAN3_refCount++ == 0) {

        _DMAN3_lock = LCK_create(NULL);

        if (_DMAN3_lock == NULL) {

            GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS,
                    "_DMAN3_initImpl> Failed to create IPC lock\n");
        } 

        /*
         *  Initialize _DMAN3_heapInt and _DMAN3_heapExt with provided
         *  heaps. Use internal heap for _DMAN3_heapInt when provided.
         *  (Actually this is a fatal error if ACPY3 uses internal DMA
         *  (IDMA) to write to PARAMs.
         */
        _DMAN3_heapInt = DMAN3_PARAMS.heapInternal;
        _DMAN3_heapExt = DMAN3_PARAMS.heapExternal;

        _DMAN3_heapInt = (_DMAN3_heapInt == -1) ?
            _DMAN3_heapExt : _DMAN3_heapInt;
        _DMAN3_heapExt = (_DMAN3_heapExt == -1) ?
            _DMAN3_heapInt : _DMAN3_heapExt;
        _DMAN3_heapIdma3 = (DMAN3_PARAMS.idma3Internal) ?
            _DMAN3_heapInt : _DMAN3_heapExt;

        /* This is a fatal configuration error. */
        DBC_assert(_DMAN3_heapInt != -1);
        GT_assert(ti_sdo_fc_dman3_GTMask, _DMAN3_heapInt != -1);

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
        GT_assert(ti_sdo_fc_dman3_GTMask,
                    (_DMAN3_allocScratch != NULL) ||
                    (_DMAN3_freeScratch == NULL));
        GT_assert(ti_sdo_fc_dman3_GTMask,
                    (_DMAN3_freeScratch != NULL) ||
                    (_DMAN3_allocScratch == NULL));


        if (ti_sdo_fc_dman3_DMAN3_useCustomDma) {
    
            /* Distribute channels among scratch groups */
            totalQdmas = 0;
    
            for (i =0; i < DMAN3_MAXGROUPS; i++) {
                if (_DMAN3_numQdmaGroup(i) >0) {
                    GT_assert(ti_sdo_fc_dman3_GTMask, 
                            totalQdmas < DMAN3_PARAMS.numQdmaChannels);  
                    /* Set the allocation base for each scratch group */ 
                    _DMAN3_qdmaBase[i] = totalQdmas;
                    _DMAN3_qdmaCounter[i] = totalQdmas;
                }
                else {
                    //TODO: Should this be set to "0" ?
                    _DMAN3_qdmaBase[i] = -1;
                    _DMAN3_qdmaCounter[i] = -1;
                }
                totalQdmas += _DMAN3_numQdmaGroup(i);
            } 
    
          /* Leave the rest of the QDMA channels (if any) to scratch group -1 */ 
            ti_sdo_fc_dman3_DMAN3_numQdmaGroup[DMAN3_MAXGROUPS] = 
                    DMAN3_PARAMS.numQdmaChannels - totalQdmas;
            _DMAN3_qdmaBase[DMAN3_MAXGROUPS] = totalQdmas;
            _DMAN3_qdmaCounter[i] = totalQdmas;
        }
        else {
                        /* Not using custom library */
            for (i =0; i < DMAN3_MAXGROUPS + 1; i++) {
                
                                /* Set base to the first qdma channel */
                                _DMAN3_qdmaBase[i] = 0;
                _DMAN3_qdmaCounter[i] = 0;
                /* Set num to total Qdma channels available */
                                ti_sdo_fc_dman3_DMAN3_numQdmaGroup[i] = 
                        DMAN3_PARAMS.numQdmaChannels;
            }
        }
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

    if (_DMAN3_refCount == 0) {
        GT_0trace(ti_sdo_fc_dman3_GTMask, GT_7CLASS, "DMAN3_exit> Reference "
                "count already zero, mismatch between DMAN3_init and DMAN3_exit"                "calls\n");
    }
    else {
        --_DMAN3_refCount;
    }

    GT_0trace(ti_sdo_fc_dman3_GTMask, GT_ENTER, "DMAN3_exit> Exit\n");

    GT_exit();
}

/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

