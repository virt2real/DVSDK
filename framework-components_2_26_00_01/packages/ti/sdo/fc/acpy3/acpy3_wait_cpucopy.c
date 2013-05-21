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
 *  ======== acpy3_wait_cpucopy.c ========
 */


#include <xdc/std.h>

#include <ti/xdais/idma3.h>
#include "acpy3_util.h"

#ifdef _ACPY3_CPUCOPY_

#ifdef __TI_COMPILER_VERSION__
#pragma CODE_SECTION(ACPY3_wait, ".text:ACPY3_wait")
#endif

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#define CURTRACE ti_sdo_fc_acpy3_GTMask

static Void doTransfer(IDMA3_Handle handle);

/*
 *  ======== ACPY3_wait ========
 *  Wait for all submitted DMA transfer on this logical channel to complete.
 */
Void ACPY3_wait(IDMA3_Handle handle)
{
    GT_1trace(CURTRACE, GT_ENTER, "ACPY3_wait> Enter "
            "(handle=0x%x)\n",handle);
    
    GT_assert(CURTRACE, handle != NULL);

     ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->hooks,handle,\
            ACPY3_INSTR_WAIT_ENTER);

    /*
     * Wait for a channel only once. Set the 'pending' flag whenever new
     * transfer is submitted, then clear it when ACPY3_wait* is issued.
     */
    if (!handle->transferPending) {
        ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->hooks,handle,
                ACPY3_INSTR_WAIT_EXIT);

        GT_0trace(CURTRACE, GT_4CLASS, "_ACPY3_start> No transfer"
                " pending\n");

        GT_0trace(CURTRACE, GT_ENTER, "_ACPY3_start> Exit\n");

        return;  /* already  waited since last start. */
    }

    doTransfer(handle);

    /*
     * Mark channel handle state to indicate pending transfer has completed
     * and 'wait' done
     */
    handle->transferPending = FALSE;

     ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->hooks,handle,\
            ACPY3_INSTR_WAIT_EXIT);

    GT_assert(CURTRACE, handle->transferPending == FALSE);

    GT_0trace(CURTRACE, GT_ENTER, "ACPY3_wait> Exit\n");
    
}

/*
 *  ======= ACPY3_waitLinked ========
 * Blocking wait for an individual transfer in a Linked transfer to finish.
 * Requires the individual transfer indicated by the 'waitId'
 * to be configured as synchronous, otherwise returns immediately.
 */
Void ACPY3_waitLinked(IDMA3_Handle handle, unsigned short waitId)
{

    GT_2trace(CURTRACE, GT_ENTER, "ACPY3_waitLinked> Enter "
            "(handle=0x%x, waitId=%d)\n", handle, waitId);

    GT_assert(CURTRACE, (handle != NULL) && (waitId < handle->numTccs));

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks,
            handle, ACPY3_INSTR_WAITLINKED_ENTER);
    /*
     * Wait for a channel only once. Set the 'pending' flag whenever new
     * transfer is submitted, then clear it when ACPY3_wait* is issued.
     */
    if (handle->transferPending == FALSE) {
        ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks,
                handle, ACPY3_INSTR_WAITLINKED_EXIT);

        GT_0trace(CURTRACE, GT_4CLASS, "ACPY3_waitLinked> "
                "No transfer pending \n");

        GT_0trace(CURTRACE, GT_ENTER, 
                "ACPY3_waitLinked> Exit\n");

        return;  /* already  waited since last start. */
    }

    if (waitId == (handle->numTccs - 1)) {

        GT_0trace(CURTRACE, GT_4CLASS, "ACPY3_waitLinked> "
                "Waiting on the last transfer\n");

        ACPY3_wait(handle);
    }
    else {
        doTransfer(handle);
    }

    /*
     * Mark channel handle state to indicate pending transfer has completed
     * and 'wait' done
     */
    handle->transferPending = FALSE;

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks,
            handle, ACPY3_INSTR_WAITLINKED_EXIT);

    GT_0trace(CURTRACE, GT_ENTER, "ACPY3_waitLinked> Exit\n");
}


/*
 *  ======== doTransfer ========
 */
static Void doTransfer(IDMA3_Handle handle)
{
    unsigned char *src, *dst;
    unsigned char *srcFrameStart, *dstFrameStart;
    ACPY3_PaRamRegs *paRamCache;
    Int numTransfers = handle->numPaRams;
    Int transferNo;
    unsigned short ccnt;
    unsigned short bcnt;
    unsigned short acnt;
    short srcElementIndex;
    short dstElementIndex;
    short srcFrameIndex;
    short dstFrameIndex;

    GT_1trace(CURTRACE, GT_ENTER, "doTransfer> Enter "
            "(handle=0x%x) \n", handle);

    for (transferNo = 0; transferNo < numTransfers; transferNo++) {
        /*
         * Use each transfer's cached paRam settings. The
         */
        paRamCache = (ACPY3_PaRamRegs *)ACPY3_getPaRamCache(handle,
                transferNo);

        src  = paRamCache->src;
        dst  = paRamCache->dst;
        acnt = paRamCache->acnt;
        bcnt = paRamCache->bcnt;

        /*
         *  QDMA can only transfer a single frame, so ccnt must always be 1.
         */
        ccnt = 1;

        srcElementIndex = paRamCache->srcElementIndex;
        dstElementIndex = paRamCache->dstElementIndex;
        srcFrameIndex = paRamCache->srcFrameIndex;
        dstFrameIndex = paRamCache->dstFrameIndex;

        GT_6trace(CURTRACE, GT_2CLASS, "doTransfer> Transfer %d,"
                " acnt  0x%x, bcnt 0x%x, src 0x%x, dst 0x%x, srcIndex 0x%x, "
                "dstIndex 0x%x\n", acnt, bcnt, src, dst, srcElementIndex, 
                dstElementIndex);

        while (ccnt-- > 0) {
            /* Keep track of the start of the frame */
            srcFrameStart = src;
            dstFrameStart = dst;

            /* Copy a frame */
            while (bcnt-- > 0) {

                /* Copy an element */
                while (acnt-- > 0) {
                    *dst++ = *src++;
                }

                /*
                 * Reset ACNT counter.
                 * Advance src/dst ptrs to beginning of next line/1D-vector
                 */
                acnt = paRamCache->acnt;
                src = (src - acnt) + srcElementIndex ;
                dst = (dst - acnt) + dstElementIndex;
            }

            /* adjust src and dst to the beginning of a frame + frameIndex*/
            bcnt = paRamCache->bcnt;
            src = srcFrameStart + srcFrameIndex;
            dst = dstFrameStart + dstFrameIndex;
        }
    } /* for each transfer */

    GT_0trace(CURTRACE, GT_ENTER, "doTransfer> Exit\n");
}

#endif

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

