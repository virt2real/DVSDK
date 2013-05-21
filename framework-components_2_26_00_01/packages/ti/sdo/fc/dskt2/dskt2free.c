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
 *  ======== dskt2free.c ========
 *  DSKT2 API to free the memory used by an XDAIS algorithm instance, and then
 *  delete the instance.
 *
 */
#include <xdc/std.h>

#include <ti/xdais/ialg.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/mem.h>
#include <ti/bios/include/tsk.h>

#include "dskt2.h"
#include "_dskt2.h"

#include "dskt2_lock.h" 
extern Int _DSKT2_algReferenceCount; 
 
/*
 *  ======== DSKT2_freeAlg ========
 */
Bool DSKT2_freeAlg(Int scratchMutexId, IALG_Handle alg)
{
    Int numRecs;
    Int memTabSize;
    IALG_MemRec *memTab;
    Int extHeapId;
    Int status = TRUE;

    GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_freeAlg> Enter "
            "(scratchMutexId=%d, alg=0x%x)\n", scratchMutexId, alg); 

    /*
     * If alg instance is currently active remove info from active table.
     * (No need to actually 'deactivate' the instance.)
     *
     * We need to do this early so pre-empting tasks know not to deactivate
     * alg.
     */
    if ((scratchMutexId >= 0) && (scratchMutexId < DSKT2_NUM_SCRATCH_GROUPS)) {
        TSK_disable();

        if (_DSKT2_activeAlg[scratchMutexId] == alg) {
            _DSKT2_activeAlg[scratchMutexId] = NULL;
        }
        else if (_DSKT2_lastActiveAlg[scratchMutexId] == alg) {
            _DSKT2_lastActiveAlg[scratchMutexId] = NULL;
        }

        /* 
         * GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS, "DSKT2_freeAlg> "
         * "Remove alg \n"); 
         * "information from DSKT2_activateAlg and lastActiveAlg tables\n"); 
         */

        TSK_enable();
    }

    /*
     * Use the memTab stored during create phase to deallocate instance
     * memory, as well as the memTab structure itself.
     * No need to call alg's algFree function anymore.
     */
    GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS, "DSKT2_freeAlg> Dequeue alg "
            " information\n"); 

    memTab =_DSKT2_dequeueMemTab(_DSKT2_heapId, alg, &memTabSize, &numRecs,
            &extHeapId);

    if (memTab == MEM_ILLEGAL) {

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_freeAlg> Illegal "
                "Memory\n");

        return FALSE; /* return without freeing any memory */
    }

    GT_4trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS, "DSKT2_freeAlg> Dequeued alg"
            " information, memTab 0x%x memTabSize %d, numRecs %d, "
            "extHeapId %d\n", memTab, memTabSize, numRecs, extHeapId); 

    /*
     * free algorithm's memory, using the scratch-group Id for determining
     * shared scratch heap.
     */

    GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS,"DSKT2_freeAlg> Free instance"
            " memory\n"); 

    status = _DSKT2_freeInstanceMemory(scratchMutexId, memTab, numRecs,
            extHeapId);

    /* done with stashed away memTab, free it */
    if (MEM_free(_DSKT2_heapId, memTab, memTabSize)) {

    } else {
        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_freeAlg> Error "
                "freeing memTab\n");
    }

    GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_freeAlg> Exit\n"); 

    _DSKT2_algReferenceCount--;

    return (status);
}
/*
 *  @(#) ti.sdo.fc.dskt2; 1, 0, 4,300; 12-1-2010 17:24:36; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

