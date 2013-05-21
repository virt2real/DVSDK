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
 *  ======== rman_yield.c ========
 *  Implementation of RMAN's DSKT2 dependent yield function  
 *  This function provides support for cooperative preemption. Algorithms can
 *  call the yield function (provided to them through their IRES handle) when 
 *  they want to yield to another algorithm of same (if configured) or higher
 *  priority algorithm. 
 */

#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <ti/bios/include/tsk.h>
#include <ti/sdo/fc/dskt2/dskt2.h>
#include <ti/sdo/fc/dskt2/dskt2_lock.h>
#include <ti/sdo/fc/rman/rman.h>

#include <ti/sdo/fc/utils/dbc.h>
#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_rman_GTMask;

/*
 *  ======== RMAN_yield ========
 *  Yields execution to another algorithm of higher or same (if configured) 
 *  priority.
 *  Currently only supports yield of ALL resources.
 */
/* ARGSUSED */
void RMAN_yield(IRES_YieldResourceType resource,
        IRES_YieldContextHandle algYieldContext, IRES_YieldArgs yieldArgs)
{
    Int groupId;
    IRES_YieldContextHandle yieldingContext;

    RMAN_YieldArgs * args = (RMAN_YieldArgs *)yieldArgs;

    GT_3trace(ti_sdo_fc_rman_GTMask, GT_ENTER, "RMAN_yield> Enter "
            "(resource=%d, algYieldContext=0x%x, yieldArgs=0x%x)\n", resource,
            algYieldContext, yieldArgs);

    GT_assert(ti_sdo_fc_rman_GTMask, IRES_ALL == resource);

    groupId = args->groupId;

    DSKT2_setContext(groupId, algYieldContext);

    GT_2trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> Group Id %d "
            "yielding current context 0x%x\n", groupId, algYieldContext);

    GT_1trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> Group Id %d "
            "releasing lock\n", groupId);

    /* 
     * Release group lock
     */
    DSKT2_releaseLock(groupId);

    /*
     * Depending on what kind of argument is supplied do yield or not
     */
    if (args->yieldFlag) {

        GT_1trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> Group Id "
                "%d Yielding to same priority task\n", groupId);

        TSK_yield();
    }

    DSKT2_acquireLock(groupId);

    yieldingContext = DSKT2_getContext(groupId);

    GT_2trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> Group Id %d "
            "acquired lock, yieldingContext 0x%x\n", groupId, yieldingContext);

    if (yieldingContext != NULL) {

        if (args->yieldFlag) {

            /*
             * Could have been a yield to same priority task
             */
            if (yieldingContext->algHandle != algYieldContext->algHandle) {

                /*
                 * Yield to same priority task occured and a yield back happened
                 * so context is not NULL, save their context and restore own.
                 */
                GT_2trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> "
                        "Yielded to same priority task, Save context of "
                        "yielding task 0x%x, restore own context 0x%x\n",
                        yieldingContext, algYieldContext);

                yieldingContext->contextSave(yieldingContext->algHandle,
                        yieldingContext->contextArgs);

                algYieldContext->contextRestore(algYieldContext->algHandle,
                        algYieldContext->contextArgs);
            }
        }
    }
    else {

        /*
         * Yielding context is NULL, so context switch occured and task ran to
         * completion
         */

        /*
         * Make sure the algorithm is truly deactivated, so that if it is 
         * activated again, we don't trample its context. 
         */ 
        DSKT2_deactivateAll();

        /*
         *
         * Restore own context
         */
         GT_1trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> "
                "Previously yielded-to task, ran to completion. Restore own "
                "context 0x%x\n", algYieldContext);

         algYieldContext->contextRestore(algYieldContext->algHandle,
                algYieldContext->contextArgs);
    }

    GT_1trace(ti_sdo_fc_rman_GTMask, GT_4CLASS, "RMAN_yield> Yielding "
            "context set to NULL for group Id %d\n", groupId);

    DSKT2_setContext(groupId, NULL);

    GT_0trace(ti_sdo_fc_rman_GTMask, GT_ENTER, "RMAN_yield> Exit\n");
}
/*
 *  @(#) ti.sdo.fc.rman; 2, 0, 0,207; 12-1-2010 17:25:37; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

