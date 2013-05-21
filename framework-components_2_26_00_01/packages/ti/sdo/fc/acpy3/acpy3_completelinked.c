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
 *  ======== acpy3_completelinked.c ========
 */

#include <xdc/std.h>

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#define CURTRACE ti_sdo_fc_acpy3_GTMask

#include <ti/xdais/idma3.h>
#include "acpy3.h"
#include "acpy3_qdma.h"
#include "acpy3_util.h"

#ifdef __TI_COMPILER_VERSION__
#pragma CODE_SECTION(ACPY3_completeLinked, ".text:ACPY3_completeLinked")
#endif

#ifndef _ACPY3_CPUCOPY_
static Bool checkForCompletion(Uns tcc);
#endif


/*
 *  ======== ACPY3_completeLinked ========
 * Non-blocking query to check completion of an individual
 * transfer in a Linked transfer.
 */
Bool ACPY3_completeLinked(IDMA3_Handle handle, unsigned short waitId)
{
#ifndef _ACPY3_CPUCOPY_
    Uns     tcc;
#endif
    Bool status;
   
    GT_2trace(CURTRACE, GT_ENTER,
            "ACPY3_completeLinked> Enter (handle=0x%x, waitId =%d)\n",
            handle, waitId); 

    GT_assert(CURTRACE, (handle != NULL) && (waitId < handle->numTccs));

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks, 
        handle, ACPY3_INSTR_COMPLETELINKED_ENTER);

    if (!handle->transferPending) {

        GT_0trace(CURTRACE, GT_2CLASS,
                "ACPY3_completeLinked> No transfers pending\n");

        /* No transfers pending - channel already waited on since last start */
        ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks,
                handle, ACPY3_INSTR_COMPLETELINKED_EXIT);

        GT_0trace(CURTRACE, GT_ENTER,
                "ACPY3_completeLinked> Exit (status=TRUE)\n");

        return (TRUE);
    }

    if (waitId == (handle->numTccs - 1)) {

        ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks,
                handle, ACPY3_INSTR_COMPLETELINKED_EXIT);

        GT_0trace(CURTRACE, GT_4CLASS, "ACPY3_completeLinked> "
                "Waiting for the last in a set of linked transfers\n");

        return (ACPY3_complete(handle));
    }

#ifndef _ACPY3_CPUCOPY_
    tcc = handle->tccTable[waitId + 1];

    /*
     * Wait for a channel only once. Set the 'pending' flag whenever new
     * transfer is submitted, then clear it when ACPY3_wait is issued.
     */
    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks, 
            handle, ACPY3_INSTR_COMPLETELINKED_EXIT);

    GT_1trace(CURTRACE, GT_4CLASS,
            "  _ACPY3_completeLinked> Waiting for tcc %d\n", tcc);

    status = checkForCompletion(tcc);

    GT_1trace(CURTRACE, GT_ENTER, "ACPY3_completeLinked> Exit (status=%d)\n",
            status);

    return (status);

#else

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks, 
            handle, ACPY3_INSTR_COMPLETELINKED_EXIT);

    status = ACPY3_complete(handle);

    GT_1trace(CURTRACE, GT_ENTER, "ACPY3_completeLinked> Exit (status=%d)\n",
            status);

    return (status);
#endif
}

#ifndef _ACPY3_CPUCOPY_
/*
 *  ======== checkForCompletion ========
 */
static Bool checkForCompletion(Uns tcc)
{
    Uns              mask;
    volatile Uns    *iprRegister; /* QDMA Interrupt pending register */

    GT_1trace(CURTRACE, GT_ENTER, "checkForCompletion> Enter (tcc=%d)\n", tcc);

    /*
     * Determine completion of a QDMA transfer by polling on the Transfer
     * Completion Code (TCC) assigned to the channel. For linked transfers
     * wait on the TCC for the last transfer.
     */

    /*
     *  There are 64 transfer completion codes on Davinci.
     *  0-31 associated with register IPR 32-63 with  IPRH.
     *  Select proper mask and register based on assigned TCC.
     *
     *  NOTE: Optimization TODO Item: store the mask and IPR info in
     *  the channel handle during ACPY3_configure to avoid the extra
     *  conditionals each time.
     */
    if (tcc < 32) {
        iprRegister = ACPY3_QDMA_IPR;
        mask = (0x1 << tcc);
    }
    else {
        iprRegister = ACPY3_QDMA_IPRH;
        mask = (0x1 << (tcc - 32));
    }

    GT_2trace(CURTRACE, GT_2CLASS,
            "checkForCompletion> IPR register 0x%x, IPR mask 0x%x\n",
            iprRegister, mask);

   /*
    *  Query the IPR register to check if the channel's TCC bit is set
    */
    if ((*iprRegister) & mask) {
        GT_0trace(CURTRACE, GT_ENTER,
                "checkForCompletion> Exit (status=TRUE)\n");
        return (TRUE);
    }
    else {
        GT_0trace(CURTRACE, GT_ENTER,
                "checkForCompletion> Exit (status=FALSE)\n");
        return (FALSE);
    }
}
#endif

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

