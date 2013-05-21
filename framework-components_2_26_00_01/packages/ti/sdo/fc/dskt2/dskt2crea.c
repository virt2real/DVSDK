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
 *  ======== dskt2crea.c ========
 *  DSKT2 API to instantiate an XDAIS algorithm instance.
 *
 */
#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <ti/sdo/fc/utils/dbc.h>
#include <ti/xdais/ialg.h>
#include <ti/bios/include/mem.h>

#include "dskt2.h"
#include "_dskt2.h"
#include <ti/sdo/fc/utils/gtinfra/gt_dais.h>
#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_dskt2_GTMask;

/*
 *  ======== DSKT2_ALGATTRS ========
 */
DSKT2_AlgAttrs DSKT2_ALGATTRS = {
    -1,     /**< extHeapId */
    FALSE   /**< singleHeap */
};

/*
 *  ======== DSKT_createAlg ========
 *
 * Creates an instance of a XDAIS algorithm using its IALG interface.
 * Instances created with the same scratch-group Id share the same DARAM and/or
 * SARAM scratch buffers (as mapped to BIOS heaps in configuration).
 * Scratch Group Id: -1 is used to turn OFF scratch sharing for this instance,
 * and allocate all scratch memory persistently.
 *
 * NOTE on RE-ENTRANCY:
 *
 * Since MEM_calloc() cannot be used within a TSK_disable()'d context
 * mutual exclusion needs to be enforced by the application framework
 * when executing this function. All algorithm instances created using
 * the same scratchId must be guaranteed by the
 * framework/application to run mutually exclusively.  This means, we
 * are assuming create phase of XDAIS algs at the same node
 * 'priority' cannot be scheduled concurrently.
 */
IALG_Handle DSKT2_createAlg(Int scratchId, IALG_Fxns * fxns,
        IALG_Handle parent, IALG_Params * params)
{
    IALG_Handle     alg;

    _DSKT2_init();

    GT_4trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_createAlg> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x)\n",
            scratchId, fxns, parent, params);

    /* Use default DSKT2_AlgAttrs */
    alg = DSKT2_createAlg3(scratchId, fxns, parent, params, NULL);

    GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER,"DSKT2_createAlg> Exit "
            "(algHandle=0x%x)\n", alg);
    return (alg);
}

/*
 *  ======== DSKT_createAlgExt ========
 *  Create alg with all memory allocated in external memory.
 */
IALG_Handle DSKT2_createAlgExt(Int scratchId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params)
{
    IALG_Handle     alg;
    DSKT2_AlgAttrs  attrs = DSKT2_ALGATTRS;

    _DSKT2_init();

    GT_4trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_createAlgExt> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x)\n",
            scratchId, fxns, parent, params);

    attrs.singleHeap = TRUE;

    alg = DSKT2_createAlg3(scratchId, fxns, parent, params, &attrs);

    GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER,"DSKT2_createAlgExt> Exit "
            "(algHandle=0x%x)\n",alg);

    return (alg);
}

/*
 *  ======== DSKT_createAlg2 ========
 */
IALG_Handle DSKT2_createAlg2(Int scratchId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params, Int extHeapId)
{
    DSKT2_AlgAttrs  attrs;
    IALG_Handle     alg;

    _DSKT2_init();

    GT_5trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_createAlg2> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x, "
            "extHeapId=%d)\n", scratchId, fxns, parent, params, extHeapId);

    DBC_require(extHeapId >= 0);
    GT_assert(ti_sdo_fc_dskt2_GTMask, extHeapId >= 0);

    attrs.singleHeap = FALSE;
    attrs.extHeapId = extHeapId;

    alg = DSKT2_createAlg3(scratchId, fxns, parent, params, &attrs);

    GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER,"DSKT2_createAlg2> Exit "
            "(algHandle=0x%x)\n",alg);

    return (alg);
}

/*
 *  ======== DSKT_createAlg3 ========
 */
/* ARGSUSED */
IALG_Handle DSKT2_createAlg3(Int scratchId, IALG_Fxns * fxns,
    IALG_Handle parent, IALG_Params * params, DSKT2_AlgAttrs *attrs)
{
    IALG_Fxns *fxnsPtr;
    IALG_Handle alg;
    Int numRecs;
    Int sizeofMemTab;
    IALG_MemRec *memTab;
    Int i;
    Int extHeapId;
    Bool singleHeap;
    Bool retVal = FALSE;
    Int  status;
    Bool scratchUsed = FALSE;

    _DSKT2_init();

    GT_6trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_createAlg3> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x, "
            "extHeapId=%d, singleHeap=%d)\n", scratchId, fxns, parent, params,
            attrs->extHeapId, attrs->singleHeap);

    if (fxns == NULL) {

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                "IALG_Fxns are NULL\n");

        return (NULL);
    }

    if (attrs == NULL) {
        attrs = &DSKT2_ALGATTRS;

        GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS,
                "DSKT2_createAlg3> DSKT2_AlgAttrs extHeapId %d and singleHeap "
                "%d\n", attrs->extHeapId, attrs->singleHeap);
    }
    extHeapId = attrs->extHeapId;
    singleHeap = attrs->singleHeap;

    if (extHeapId < 0) {
        extHeapId = _DSKT2_spaceToSeg(IALG_ESDATA);
    }
    DBC_assert(extHeapId >= 0);
    GT_assert(ti_sdo_fc_dskt2_GTMask, extHeapId >= 0);

    /* determine size of the memTab structure */
    if (fxns->algNumAlloc != NULL) {
        numRecs = fxns->algNumAlloc();

        GT_1trace(ti_sdo_fc_dskt2_GTMask, (GT_4CLASS|GT_2CLASS),
                "DSKT2_createAlg3> Num memory recs requested %d\n", numRecs);
    }
    else {
        /*
         * Note: as per XDAIS Spec (SPRU360) algNumAlloc() is optional
         * and if it is not implemented, the maximum number of memory
         * records for algAlloc() must be less than IALG_DEFMEMRECS.
         */
        numRecs = IALG_DEFMEMRECS;

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS,
                "DSKT2_createAlg3> AlgNumAlloc not implemented\n");
    }

    /* allocate a memTab based on number of records alg specified */
    sizeofMemTab = numRecs * sizeof(IALG_MemRec);
    memTab = MEM_calloc(_DSKT2_heapId, sizeofMemTab, 0);

    if (memTab == MEM_ILLEGAL) {

        GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                "memTab allocation failed in memory heap %d size=%d\n",
                _DSKT2_heapId, sizeofMemTab);

        return (NULL);
    }
    else {
        GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS,
                "DSKT2_createAlg3> memTab allocated at 0x%x size=0x%x\n",
                memTab, sizeofMemTab);
    }

    /* call alg's algAlloc fxn to fill in memTab[]  */
    numRecs = fxns->algAlloc((IALG_Params *)params, &fxnsPtr, memTab);

    /* allocate memory for alg */
    if (numRecs > 0) {

        GT_1trace(ti_sdo_fc_dskt2_GTMask, (GT_4CLASS | GT_2CLASS),
                "DSKT2_createAlg3> Num memory recs requested %d\n", numRecs);

        for (i = 0; i < numRecs; i++) {

            GT_5trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS, "DSKT2_createAlg3> "
                    "Requested memTab[%d]: size=0x%x, align=0x%x, "
                    "space=%s, attrs=%s\n", i, memTab[i].size,
                    memTab[i].alignment, gt_MemSpace(memTab[i].space),
                    gt_MemAttrs(memTab[i].attrs));

            if ( memTab[i].attrs == IALG_SCRATCH) {
                scratchUsed = TRUE;
            }
        }

        if (TRUE == scratchUsed) {

            if ((NULL == fxns->algActivate) || (NULL == fxns->algDeactivate)) {
                GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_6CLASS ,
                        "DSKT2_createAlg3> Scratch Memory requested by "
                        "algorithm, but algActivate, algDeactivate functions "
                        "not implemented.\n");
            }
        }

        if (singleHeap) {

            GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS|GT_2CLASS,
                    "DSKT2_createAlg3> Requested all memory in external memory"
                    " space %d\n", IALG_ESDATA);

            /* Change all memTab space fields to IALG_ESDATA */
            for (i = 0; i < numRecs; i++) {
                memTab[i].space = IALG_ESDATA;
            }
        }

        if (!(retVal = _DSKT2_assignInstanceMemory(scratchId, memTab, numRecs,
            extHeapId))) {

            GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                    "Instance memory allocation failed\n");
        }
        else {

            for(i = 0; i < numRecs; i++) {

                GT_6trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS,"DSKT2_createAlg3>"
                        " Allocated memTab[%d]: base=0x%x, size=0x%x, "
                        "align=0x%x, space=%s, attrs=%s\n", i, memTab[i].base,
                        memTab[i].size, memTab[i].alignment,
                        gt_MemSpace(memTab[i].space),
                        gt_MemAttrs(memTab[i].attrs));
            }
        }
    }
    else {
        /* Number of mem recs <= 0 */

        GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                "algAlloc returned numRecs=%d\n", numRecs);
    }

    /* Free memTab and return if memory was not assigned. */
    if (retVal == FALSE) {
        if (MEM_free(_DSKT2_heapId, memTab, sizeofMemTab)) {

            GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS,
                    "DSKT2_createAlg3> memTab memory freed from 0x%x, "
                    "size=%d\n", memTab, sizeofMemTab);
        }
        else {

            GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS,
                    "DSKT2_createAlg3> memTab memory could not be freed from "
                    "0x%x, size=%d\n", memTab, sizeofMemTab);
        }
        return (NULL);
    }

    /* set alg object handle, and set instance's function pointer */
    alg = ((IALG_Handle)memTab[0].base);
    alg->fxns = fxns;

    /* stash away memTab (to an ext.mem queue) til delete phase */
    if (!_DSKT2_enqueueMemTab(_DSKT2_heapId, memTab, sizeofMemTab, numRecs,
        extHeapId)) {

        /* if 'enqueue' fails abort create phase. */

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                "enqueue memTab failed\n");

        /* Can't call DSKT2_freeAlg() since memTab was not enqueued. */
        _DSKT2_freeInstanceMemory(scratchId, memTab, numRecs, extHeapId);

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS, "DSKT2_createAlg3> "
                "Freeing algorithm memory\n");

        MEM_free(_DSKT2_heapId, memTab, sizeofMemTab);

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                "Enqueue memtab failed\n");

        GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER,"DSKT2_createAlg3> Exit "
                "(algHandle=0x%x)\n", alg);

        return (NULL);
    }

    /* Writeback and invalidate cache, if function is specified */
    if (DSKT2_cacheWBInvFxn != NULL) {
        for (i = 0; i < numRecs; i++) {
            (DSKT2_cacheWBInvFxn)(memTab[i].base, memTab[i].size, TRUE);
        }
    }

    /* call alg initialize function with the memory it requested */
    /* if algInit successful return the alg object's handle */
    status = fxns->algInit(alg, memTab, NULL, (IALG_Params *)params) ;
    if (status == IALG_EOK) {

        GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS, "DSKT2_createAlg3> "
                "Algorithm init successful.\n");

        if (_DSKT2_createCallbackFxn != NULL) {
            _DSKT2_createCallbackFxn(alg, memTab, numRecs, scratchId);
        }

        GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER,"DSKT2_createAlg3> Exit "
                "(algHandle=0x%x)\n", alg);

        return ((IALG_Handle)alg);
    }
    else {

        GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_7CLASS, "DSKT2_createAlg3> "
                "algInit call failed %d\n", status);

        /*
         * Call freeAlg to free all instance memory, saved memTab recs
         * and maintain the shared scratch data structures.
         */
        DSKT2_freeAlg(scratchId, (IALG_Handle) alg);
    }

    GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_createAlg3> Exit "
            "(algHandle=NULL)\n");

    return (NULL);
}
/*
 *  @(#) ti.sdo.fc.dskt2; 1, 0, 4,300; 12-1-2010 17:24:36; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

