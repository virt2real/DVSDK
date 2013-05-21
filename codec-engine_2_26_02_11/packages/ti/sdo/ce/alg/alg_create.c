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
 *  ======== alg_create.c ========
 *  This file contains a simple implementation of the ALG_create API operation.
 */
#if _TI_
#pragma CODE_SECTION(ALG_create, ".text:create")
#pragma CODE_SECTION(ALG_delete, ".text:delete")
#endif

#include <xdc/std.h>
#include <ti/xdais/ialg.h>
#include <stdlib.h>

#include "alg.h"
#include "_alg.h"
#include <ti/sdo/utils/trace/gt.h>

/*
 * Mask to enable GT tracing
 */
extern GT_Mask ti_sdo_ce_alg_GTMask;

#define CURTRACE ti_sdo_ce_alg_GTMask


/*
 *  ======== ALG_create ========
 */
ALG_Handle ALG_create(Int scratchId, IALG_Fxns *fxns, IALG_Handle parent,
        IALG_Params *params, UInt32 useCacheMem)
{
    IALG_Fxns *fxnsPtr;
    ALG_Handle alg;
    Int numRecs;
    IALG_MemRec *memTab;
    Int i;
    Int  status;

    GT_5trace(CURTRACE, GT_ENTER, "ALG_create> Enter "
            "(scratchId=%d, fxns=0x%x, parentAlg=0x%x, params=0x%x, "
            "useCacheMem=%d)\n",
            scratchId, fxns, parent, params, useCacheMem);

    if (fxns != NULL) {
        /* determine size of the memTab structure */
        numRecs = (fxns->algNumAlloc != NULL) ?
                fxns->algNumAlloc() : IALG_DEFMEMRECS;
        GT_1trace(CURTRACE, (GT_4CLASS | GT_2CLASS),
                "ALG_create> algNumAlloc %d memory recs\n", numRecs);

        /* allocate a memTab based on number of records alg specified */
        if ((memTab = (IALG_MemRec *)malloc(numRecs * sizeof (IALG_MemRec)))) {

            /* call alg's algAlloc fxn to fill in memTab[]  */
            numRecs = fxns->algAlloc(params, &fxnsPtr, memTab);
            if (numRecs <= 0) {
                GT_1trace(CURTRACE, GT_7CLASS,
                        "ALG_create> alg's algAlloc() returned alg-specific "
                        "error code (0x%x)\n", numRecs);
                return (NULL);
            }

            GT_1trace(CURTRACE, (GT_4CLASS | GT_2CLASS),
                    "ALG_create> algAlloc returned numRecs=%d\n", numRecs);
            for (i = 0; i < numRecs; i++) {

                GT_5trace(CURTRACE, GT_4CLASS, "ALG_create> "
                        " Memory requested memTab[%d]: size=0x%x, align=0x%x, "
                        "space=0x%x, attrs=0x%x\n", i, memTab[i].size,
                        memTab[i].alignment, memTab[i].space,
                        memTab[i].attrs);

            }
            if (_ALG_allocMemory2(memTab, numRecs, useCacheMem)) {
                /* set alg object handle, and set instance's function pointer */
                alg = (IALG_Handle)memTab[0].base;
                alg->fxns = fxns;
                /* call alg initialize function with the memory it requested */
                /* if algInit successful return the alg object's handle */
                status = fxns->algInit(alg, memTab, parent, params);
                if (status == IALG_EOK) {
                    GT_0trace(CURTRACE, GT_4CLASS,
                            "ALG_create> algInit returned IALG_EOK\n");
                    free(memTab);

                    GT_1trace(CURTRACE, GT_ENTER,
                            "ALG_create> Exit (algHandle=0x%x)\n", alg);

                    return (alg);
                }
                GT_1trace(CURTRACE, GT_7CLASS, "ALG_create> "
                        "algInit call failed %d\n", status);

                /*
                 * Call algFree to free all instance memory, saved memTab recs.
                 */
                fxns->algFree(alg, memTab);
                _ALG_freeMemory2(memTab, numRecs, useCacheMem);
            }

            free(memTab);
        }
    }

    GT_0trace(CURTRACE, GT_ENTER, "ALG_create> Exit "
            "(algHandle=NULL)\n");

    return (NULL);
}

/*
 *  ======== ALG_delete ========
 */
Void ALG_delete(Int groupId, ALG_Handle alg, UInt32 useCachedMem)
{
    IALG_MemRec *memTab;
    Int n;
    IALG_Fxns *fxns;

    if (alg != NULL && alg->fxns != NULL) {
        fxns = alg->fxns;
        n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

        if ((memTab = (IALG_MemRec *)malloc(n * sizeof (IALG_MemRec)))) {
            memTab[0].base = alg;
            n = fxns->algFree(alg, memTab);
            _ALG_freeMemory2(memTab, n, useCachedMem);

            free(memTab);
        }
    }
}

/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,191; 12-2-2010 21:18:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

