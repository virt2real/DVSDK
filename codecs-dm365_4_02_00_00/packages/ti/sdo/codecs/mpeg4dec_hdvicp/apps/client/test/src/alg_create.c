/*
 *  Copyright 2003 by Texas Instruments Incorporated.
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 *  @(#) XDAS 2.51.00 11-29-2003 (xdas-2.50.00.9)
 */
/*
 *  ======== alg_create.c ========
 *  This file contains a simple implementation of the ALG_create API operation.
 */
#pragma CODE_SECTION(ALG_create, ".text:create")
#pragma CODE_SECTION(ALG_delete, ".text:delete")

#include <xdc/std.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/xdais/ialg.h>
#include <stdlib.h>

#include <ti/sdo/fc/utils/api/_alg.h>

Bool _ALG1_allocMemory(IALG_MemRec memTab[], Int n);
Void _ALG1_freeMemory(IALG_MemRec memTab[], Int n);
/*
 *  ======== ALG_create ========
 */
IALG_Handle ALG_create(IALG_Fxns *fxns, IALG_Handle p, IALG_Params *params)
{
    IALG_MemRec *memTab;
    Int n;
    IALG_Handle alg;
    IALG_Fxns *fxnsPtr;

    if (fxns != NULL) {
        n = fxns->algNumAlloc != NULL ? fxns->algNumAlloc() : IALG_DEFMEMRECS;

        if ((memTab = (IALG_MemRec *)malloc(n * sizeof (IALG_MemRec)))) {

            n = fxns->algAlloc(params, &fxnsPtr, memTab);
            if (n <= 0) {
                return (NULL);
            }

            if (_ALG1_allocMemory(memTab, n)) {
                alg = (IALG_Handle)memTab[0].base;
                alg->fxns = fxns;
                if (fxns->algInit(alg, memTab, p, params) == IALG_EOK) {
                    free(memTab);
                    return (alg);
                }
                fxns->algFree(alg, memTab);
                _ALG1_freeMemory(memTab, n);
            }

            free(memTab);
        }
    }

    return (NULL);
}

/*
 *  ======== ALG_delete ========
 */
Void ALG_delete(IALG_Handle alg)
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
            _ALG1_freeMemory(memTab, n);

            free(memTab);
        }
    }
}

