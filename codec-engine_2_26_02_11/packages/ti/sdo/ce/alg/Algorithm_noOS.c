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
 *  ======== Algorithm_noOS.c ========
 */
#include <xdc/std.h>

#include <ti/sdo/fc/dman3/dman3.h>
#include <ti/sdo/fc/rman/rman.h>
#include <ti/xdais/idma3.h>
#include <ti/xdais/ires.h>
#include <ti/xdais/ialg.h>

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/osal/Global.h>

#include "alg.h"

#include "Algorithm.h"

extern unsigned int ti_sdo_ce_alg_ALG_maxGroups;

#define _ALGORITHM_MAXGROUPS ti_sdo_ce_alg_ALG_maxGroups

/*
 *  ======== Algorithm_Obj ========
 */
typedef struct Algorithm_Obj {
    IALG_Handle alg;
    Int         groupId;
    IDMA3_Fxns  *idma3Fxns;
    IRES_Fxns   *iresFxns;
    UInt32      useCachedMem;
} Algorithm_Obj;


extern Void DMAN3_CE_exit();

static Int curInit = FALSE;
static GT_Mask curTrace = {NULL, NULL};

/*
 *  ======== Algorithm_acquireLock ========
 */
Void Algorithm_acquireLock(Int groupId, IALG_Handle alg)
{

    GT_2trace(curTrace, GT_ENTER, "Algorithm_acquireLock> Enter(alg=0x%x,"
            " groupId=%d)\n", alg, groupId);

    ALG_acquireLock(groupId, alg);
    /* Would be NULL if noone else grabbed it, would be some other alg if
       some alg in some other thread grabbed it */
    _Algorithm_lockOwner[groupId] = alg;

    GT_0trace(curTrace, GT_ENTER, "Algorithm_acquireLock> Exit\n");
}

/*
 *  ======== Algorithm_releaseLock ========
 */
Void Algorithm_releaseLock(Int groupId, IALG_Handle alg)
{
    GT_2trace(curTrace, GT_ENTER, "Algorithm_releaseLock> Enter(alg=0x%x,"
            " groupId=%d)\n", alg, groupId);

    /* Make sure the alg releasing the lock, is the alg that owns it  */
    GT_assert(curTrace, _Algorithm_lockOwner[groupId] == alg);

    _Algorithm_lockOwner[groupId] = NULL;
    ALG_releaseLock(groupId, alg);

    GT_0trace(curTrace, GT_ENTER, "Algorithm_releaseLock> Exit\n");
}

/*
 *  ======== Algorithm_activate ========
 */
Void Algorithm_activate(Algorithm_Handle alg)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)alg;

    GT_1trace(curTrace, GT_ENTER, "Algorithm_activate> Enter(alg=0x%x)\n",
            alg);

    ALG_activate(pObject->groupId, pObject->alg);

    if (pObject->iresFxns) {
        RMAN_activateAllResources(pObject->alg, pObject->iresFxns,
                pObject->groupId);
    }

    _Algorithm_lockOwner[pObject->groupId] = pObject->alg;

    GT_0trace(curTrace, GT_ENTER, "Algorithm_activate> Exit\n");
}


/*
 *  ======== Algorithm_addGroup ========
 */
Bool Algorithm_addGroup(Int groupId)
{
    Bool    retVal;

    GT_1trace(curTrace, GT_ENTER, "Algorithm_addGroup> Enter(groupId=%d)\n",
            groupId);

    retVal = ALG_addGroup(groupId);

    GT_1trace(curTrace, GT_ENTER, "Algorithm_addGroup> Exit (status = %d)\n",
            retVal);

    return (retVal);
}

/*
 *  ======== Algorithm_create ========
 */
Algorithm_Handle Algorithm_create(IALG_Fxns *fxns, Void *idma3FxnsVoid,
        Void *iresFxnsVoid, IALG_Params *params, Algorithm_Attrs *attrs)
{
    Algorithm_Obj *pObject = NULL;
    Int         groupId;
    IDMA3_Fxns *idma3Fxns = (IDMA3_Fxns *)idma3FxnsVoid;
    IRES_Fxns  *iresFxns = (IRES_Fxns *)iresFxnsVoid;
    IRES_Status iresStatus;
    UInt32      useCachedMem;

    GT_5trace(curTrace, GT_ENTER, "Algorithm_create> Enter ("
            "fxns=0x%x, idma3Fxns=0x%x, iresFxns=0x%x, params=0x%x, "
            "attrs=0x%x)\n", fxns, idma3Fxns, iresFxns, params, attrs);

    groupId = (attrs != NULL) ? attrs->groupId : -1;
    useCachedMem = (attrs != NULL) ? attrs->useCachedMem :
            Algorithm_USECACHEDMEM_DEFAULT;

    GT_1trace(curTrace, GT_2CLASS, "Algorithm_create> useCachedMem = %d\n",
            useCachedMem);

    /* if (attrs == NULL) use default groupId */
    if ((pObject = (Algorithm_Obj *)Memory_alloc(sizeof(Algorithm_Obj),
                 NULL)) == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Algorithm_create> "
                "Alloc for a small object FAILED -- out of memory?");
        goto Algorithm_create_return;
    }

    pObject->alg = ALG_create(groupId, fxns, NULL, params, useCachedMem);
    pObject->idma3Fxns = NULL;
    pObject->iresFxns = NULL;
    pObject->groupId = groupId;

    if (pObject->alg == NULL) {
        GT_0trace(curTrace, GT_7CLASS, "Algorithm_create> "
           "Algorithm creation FAILED; make sure that 1) alg params are "
           "correct/supported, 2) there is enough internal and external "
           "algorithm memory available\n");
        Algorithm_delete(pObject);
        pObject = NULL;
        goto Algorithm_create_return;
    }

    /* if the alg implements IDMA3, we need to negotiate DMA resources */
    if (idma3Fxns != NULL) {
        Int status;
        status = DMAN3_grantDmaChannels(pObject->groupId, &pObject->alg,
                &idma3Fxns, 1);

        if (status != DMAN3_SOK) {
            GT_1trace(curTrace, GT_7CLASS, "Algorithm_create> "
                "Granting DMA channels to algorithm through DMAN3 FAILED"
                " (0x%x)\n", status);
            Algorithm_delete(pObject);
            pObject = NULL;
            goto Algorithm_create_return;
        }

        pObject->idma3Fxns = idma3Fxns;  /* tell Algorithm_delete to release */
    }

    /* If alg implements IRES, allocate resources */
    if (iresFxns != NULL) {
        iresStatus = RMAN_assignResources(pObject->alg, iresFxns,
                pObject->groupId);

        if (iresStatus != IRES_OK) {
            GT_1trace(curTrace, GT_7CLASS, "Algorithm_create> Assignment of "
                    "alg resources through RMAN FAILED (0x%x)\n", iresStatus);

            /* Free DMAN3 channels, if allocated */
            if (idma3Fxns != NULL) {
                DMAN3_releaseDmaChannels(&(pObject->alg),
                        &(pObject->idma3Fxns), 1);
            }

            Algorithm_delete(pObject);
            pObject = NULL;
            goto Algorithm_create_return;
        }
        pObject->iresFxns = iresFxns;
    }

Algorithm_create_return:

    GT_1trace(curTrace, GT_ENTER, "Algorithm_create> return (0x%x)\n",
            pObject);

    return (pObject);
}


/*
 *  ======== Algorithm_deactivate ========
 */
Void Algorithm_deactivate(Algorithm_Handle alg)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)alg;

    GT_1trace(curTrace, GT_ENTER, "Algorithm_deactivate> Enter(alg=0x%x)\n",
            alg);

    /*
         * At this stage, Algorithm could already have released
     * scratch group lock (using new APIs above). Which means they saved all
     * scratch context, and some other alg now have control of scratch group,
     * can't call RMAN_deactivate here.
     * Need to keep track of what ALG called release lock and probably not do
     * anything in deactivate for those ALG(s) ??!!
     */

    /* Need to actually deactivate if _Algorithm_lockOwner[groupId] == alg
     * If _Algorithm_lockOwner[groupId] == NULL, some other process may have
     * lock, i.e, alg is already deactivated
     * If _Algorithm_lockOwner[groupId] != NULL and != alg, some other
     * thread in this process has the group lock, and this alg is
         * deactive. In both of the above cases, do nothing here !!
     */


    if (_Algorithm_lockOwner[pObject->groupId] == pObject->alg) {

       _Algorithm_lockOwner[pObject->groupId] = NULL;

        if (pObject->iresFxns) {

            RMAN_deactivateAllResources(pObject->alg, pObject->iresFxns,
                    pObject->groupId);
        }

        ALG_deactivate(pObject->groupId, pObject->alg);
    }

    GT_0trace(curTrace, GT_ENTER, "Algorithm_deactivate> Exit\n");
}


/*
 *  ======== Algorithm_delete ========
 */
Void Algorithm_delete(Algorithm_Handle alg)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)alg;
    IRES_Status status;

    GT_1trace(curTrace, GT_ENTER, "Algorithm_delete> Enter(alg=0x%x)\n", alg);

    if (pObject != NULL) {
        if (pObject->iresFxns) {
            /* Call RMAN fuction to free resources */
            status = RMAN_freeResources(pObject->alg, pObject->iresFxns,
                    pObject->groupId);
            if (status != IRES_OK) {
                GT_1trace(curTrace, GT_7CLASS, "Algorithm_delete> Freeing "
                        "of alg resources through RMAN FAILED (0x%x)\n",
                        status);
            }
        }

        if (pObject->idma3Fxns) {
            DMAN3_releaseDmaChannels(&(pObject->alg), &(pObject->idma3Fxns),1);
        }

        if (pObject->alg != NULL) {
            ALG_delete(pObject->groupId, pObject->alg, pObject->useCachedMem);
        }

        Memory_free(pObject, sizeof (*pObject), NULL);
    }

    GT_0trace(curTrace, GT_ENTER, "Algorithm_delete> Exit\n");
}


/*
 *  ======== Algorithm_exit ========
 */
Void Algorithm_exit()
{
    GT_assert(curTrace, curInit > 0);

    if (--curInit == 0) {
        ALG_exit();

        DMAN3_CE_exit();
        RMAN_exit();
    }
}


/*
 *  ======== Algorithm_getAlgHandle ========
 */
IALG_Handle Algorithm_getAlgHandle(Algorithm_Handle handle)
{
    Algorithm_Obj *pObject = (Algorithm_Obj *)handle;

    /* reach into the internal object and return the iAlg handle */
    return (pObject->alg);
}


/*
 *  ======== Algorithm_getMemRecs ========
 */
Int Algorithm_getMemRecs(Algorithm_Handle alg, IALG_MemRec *memTab,
        Int size)
{
    /* This API is not supported */
    return (-1);
}

/*
 *  ======== Algorithm_getNumRecs ========
 */
Int Algorithm_getNumRecs(Algorithm_Handle handle)
{
    /* This API is not supported */
    return (-1);
}

/*
 *  ======== Algorithm_init ========
 */
Void Algorithm_init()
{
    extern Void DMAN3_CE_init();

    if (curInit++ == 0) {
        GT_create(&curTrace, Algorithm_GTNAME);
        RMAN_init();
        DMAN3_CE_init();

        /*
         *  NOTE: We are calling ALG_init() here rather than calling it in
         *  CERuntime_init(). This simplifies the auto-generation of
         *  CERuntime_init(), since ALG is not used in Algorithm_BIOS.c.
         *  Since ALG_init() is called here, to keep the symmetry, we will
         *  also call ALG_exit() from Algorithm_exit(), rather than having
         *  ALG_init() register its exit function through Global_atexit().
         */
        ALG_init();

        Global_atexit((Fxn)Algorithm_exit);
    }
}

/*
 *  ======== Algorithm_removeGroup ========
 */
Void Algorithm_removeGroup(Int groupId)
{
    GT_1trace(curTrace, GT_ENTER, "Algorithm_removeGroup> Enter(groupId=%d)\n",
            groupId);

    ALG_removeGroup(groupId);

    GT_0trace(curTrace, GT_ENTER, "Algorithm_removeGroup> Exit\n");
}
/*
 *  @(#) ti.sdo.ce.alg; 1, 0, 1,191; 12-2-2010 21:18:41; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

