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
 *  ======== dskt2actv.c ========
 *  Function to simplify call to algorithm's algActivate function.
 *
 */
#include <xdc/std.h>

#include <ti/sdo/fc/utils/dbc.h>
#include <ti/xdais/ialg.h>
#include "dskt2.h"
#include "_dskt2.h"
#include "dskt2_lock.h"

/*
 *  ======== DSKT2_activateAlg ========
 *
 * Does 'optimistic' algorithm activation/deactivation!
 * That is, we defer instance 'deactivation' until when we need to
 * 'activate' a *new* algorithm instance. At that point
 * the 'current' active instance  gets deactivated, and the new instance
 * get activated.
 */
Void DSKT2_activateAlg(Int scratchId, IALG_Handle alg)
{
    IALG_Handle lastActiveAlg = NULL;
    Bool validScratchRange;
    IRES_YieldContextHandle context;

    GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_activateAlg> Enter "
            "(scratchId=%d, alg=0x%x)\n", scratchId, alg);

    /*
     * First acquire a group lock using the scratch Id 
     */
    DSKT2_acquireLock(scratchId);

    /*
     * Check the yielding context, if that is not NULL, context of the
     * yielding algorithm needs to be saved.
     */
    context = DSKT2_getContext(scratchId);
    if (context != NULL) {
        context->contextSave(context->algHandle, context->contextArgs);

        /* Set context to NULL */ 
        DSKT2_setContext(scratchId, NULL);
        _DSKT2_yielded = 1;
        _DSKT2_NumYielded++;
    }

    validScratchRange = (scratchId >= 0) && (scratchId <
            DSKT2_NUM_SCRATCH_GROUPS);

    /* Use the scratchId for determining shared scratch heap */
    if (validScratchRange) {

        lastActiveAlg = _DSKT2_lastActiveAlg[scratchId];

        /*
         *  lastActiveAlg will either be deactivated or become the current
         *  activate alg, so we can set _DSKT2_lastActiveAlg[scratchId]
         *  to NULL.
         *
         *  Should we check for _DSKT2_activeAlg[scratchId] != NULL?
         *  (ie, somebody didn't call DSKT2_deactivateAlg())
         */
        _DSKT2_lastActiveAlg[scratchId] = NULL;
        _DSKT2_activeAlg[scratchId] = alg;
    }

    GT_2trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS, "DSKT2_activateAlg> Last "
            "active algorithm 0x%x, current algorithm to be activated 0x%x\n",
            lastActiveAlg, alg); 

    if (lastActiveAlg != alg) {

        /*
         * At given scratch group, if this instance is not the currently
         *  active alg instance, deactivate any existing 'current' active
         */
        if (lastActiveAlg != NULL) {
            /*
             *  lastActiveAlg has been 'lazily' deactivated. Now we need
             *  to really deactivate it.
             */
            GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS, "DSKT2_activateAlg> "
                    "Real deactivation of algorithm 0x%x\n", lastActiveAlg);

            if (lastActiveAlg->fxns->algDeactivate != NULL) {
                lastActiveAlg->fxns->algDeactivate(lastActiveAlg);
            }
        }

        if ((alg != NULL) && (alg->fxns->algActivate != NULL)) {
            /*
             * 'activate' current instance & make it the current active
             * instance for this scratch group.
             */
            GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_4CLASS, "DSKT2_activateAlg> "
                    "Real activation of algorithm 0x%x\n", alg);

            alg->fxns->algActivate(alg);
        }
    }
    else {

        GT_1trace(ti_sdo_fc_dskt2_GTMask, GT_2CLASS, "DSKT2_activateAlg> "
                "Activation of algorithm 0x%x not required, already active\n",
                lastActiveAlg);
    }
    /* else current algorithm instance is already active/or does not need
     * activation
     */
    GT_0trace(ti_sdo_fc_dskt2_GTMask, GT_ENTER, "DSKT2_activateAlg> Exit\n");
}
/*
 *  @(#) ti.sdo.fc.dskt2; 1, 0, 4,300; 12-1-2010 17:24:36; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

