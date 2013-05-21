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
 *  ======== acpy3_qdma.c ========
 *
 * New functions that are called to do Channel activation/deactivation
 * for scratch DMA channels.
 */
#include <xdc/std.h>

#include <ti/xdais/idma3.h>
#include "acpy3.h"
#include "acpy3_qdma_arm.h"
#include "acpy3_util.h"
#include "acpy3_lock.h"

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#define CURTRACE ti_sdo_fc_acpy3_GTMask

/*
 *  ======== ACPY3_activate ========
 */
Void ACPY3_activate(IDMA3_Handle handle)
{
    Int    numPaRamsM1;
    ACPY3_MoreEnv *env;
#ifndef _ACPY3_CPUCOPY_
    Int    i;
    Uns    paRam;
    Uns    begPaRam;
    Uns    endPaRam;
    unsigned short qdmaChan;
    volatile Uns   *paRamRegs;
    volatile Uns   *lastPaRam;
    Uns    triggerIdx;
    Uns    nullPaRam = ACPY3_QDMA.nullPaRamIndex;
#endif

    GT_0trace(CURTRACE, GT_ENTER, "ACPY3_activate> Enter\n");

    env = (ACPY3_MoreEnv *)(handle->env);

    GT_1trace(CURTRACE, GT_2CLASS, "ACPY3_activate> env = 0x%x\n", env);

#ifndef _ACPY3_CPUCOPY_
    qdmaChan = handle->qdmaChan;
#endif
    /* Set CCNT to 1 in all physical PaRams owned by this channel */
    numPaRamsM1 = env->numPaRams - 1;

#ifndef _ACPY3_CPUCOPY_
    /*
     * If any other QDMA channel uses the current PaRam set for this channel,
     * Modify it to use paRam 0 or 127 instead.
     * This shouldn't really happen, but we really need to avoid it.
     */
    endPaRam = ((Uns)handle->paRamAddr) - (Uns)ACPY3_QDMA_PARAM_BASE;
    begPaRam = endPaRam - (numPaRamsM1 << 5);

    GT_2trace(CURTRACE, GT_2CLASS, "ACPY3_activate> begPaRam ="
            "0x%x, endPaRam = 0x%x\n", begPaRam, endPaRam);

    /* Enter critical section for accessing QCHMAP */
    LockMP_acquire(_ACPY3_lock);

    GT_0trace(CURTRACE, GT_2CLASS,"ACPY3_activate> Acquired a LockMP\n");

    for (i = 0; i < ACPY3_NUM_QDMA_CHANNELS; i++) {
        if (i == qdmaChan) {
            continue;
        }
        paRam = (ACPY3_QCHMAP[i] & 0x3fe0);
        if ((paRam >= begPaRam) && (paRam <= endPaRam)) {
            /*
             *  Set trigger word of other channels to a paRam not in use
             *  (trigger word is ccnt of the null PaRam)
             */
            GT_2trace(CURTRACE, GT_2CLASS,"ACPY3_activate>"
                    "QDMA channel %d pointing to PaRam assigned to ACPY3, "
                    "map it %d to nullPaRam %d\n", i, nullPaRam);

            ACPY3_QCHMAP[i] = (Uns)(nullPaRam << 5) | (0x7 << 2);
        }
    }


    /*
     *  TODO: Make sure all linked transfers have completed on the mapped
     *  PaRam, before changing QCHMAP.
     */

    /*
     *  Set the QCHMAP for this channel to the null PaRam, since the static bit
     *  will always be set for it (and we know there is no transfer in progress
     *  on first call to ACPY3_start()).
     */
    GT_2trace(CURTRACE, GT_2CLASS,"ACPY3_activate> Mapping "
            "QDMA channel %d to nullPaRam %d\n", qdmaChan, nullPaRam);

    ACPY3_QCHMAP[qdmaChan] = (Uns)(nullPaRam << 5) | (0x7 << 2);
    GT_1trace(CURTRACE, GT_2CLASS,"Enabling QEESR for QDMA channel %d \n",
            qdmaChan);

    /* Enable QEER */
    *ACPY3_QEESR = 0x1 << (qdmaChan);

    /*
     * Set the last two elements of each real allocated paRam to their
     * expected values.  They should never get written again as long as
     * this handle is activated.
     */
    lastPaRam = (Uns *)((Uns)ACPY3_QDMA_PARAM_BASE +
            (ACPY3_QCHMAP[qdmaChan] & 0x3fe0));
    triggerIdx = (ACPY3_QCHMAP[qdmaChan] & (0x7 << 2))  >> 2;

    for (i = env->numPaRams - 1; i >= 0; i--) {
        paRamRegs = (Uns *)ACPY3_getPaRamPhysicalAddress(handle, i);

        if ((paRamRegs == lastPaRam) && (triggerIdx >= 6)) {
            /* set trigger word to link|bCntrld of 1st paRam */
            ACPY3_QCHMAP[qdmaChan] = (Uns)(handle->paRamAddr) | (0x5 << 2);
        }
        paRamRegs[0x6] = 0; /* frame indices = 0 */
        paRamRegs[0x7] = 1; /* ccnt=1, rsvd=0 */
    }

    /* Exit critical section */
    LockMP_release(_ACPY3_lock);
    GT_0trace(CURTRACE, GT_2CLASS, "Released LockMP\n");

#endif /* _ACPY3_CPUCOPY_ */

    handle->transferPending = FALSE;
    handle->numPaRams = numPaRamsM1 + 1;
    handle->numTccs = env->numTccs;

    GT_0trace(CURTRACE, GT_ENTER, "ACPY3_activate> Exit\n");

    return;
}

/*
 *  ======== ACPY3_deactivate ========
 */
Void ACPY3_deactivate(IDMA3_Handle handle)
{
    Uns    nBytesPaRams;
    Uns    nBytes;
    Uns    nWords;
    Int    i;
    ACPY3_MoreEnv *env;
    Void  * restrict scratchEnv;
    Void  * restrict persistEnv;
    Int   * restrict ptrPersist;
    Int   * restrict ptrScratch;
#ifndef _ACPY3_CPUCOPY_
    Uns    nullPaRam = ACPY3_QDMA.nullPaRamIndex;
#endif

    ///DBC_require(handle != NULL);

    env = (ACPY3_MoreEnv *)(handle->env);

    if ((scratchEnv = env->scratchEnv) && (env == scratchEnv)) {
        /*
         * Copy env->scratchEnv to env->persisthEnv.
         * Then set env in handle to point to persistent shadow until
         * next ACPY3_activate() is called.
         */
        nBytesPaRams = env->numPaRams * (sizeof(ACPY3_PaRamRegs));
        persistEnv = env->persistEnv;
        nBytes = sizeof(ACPY3_MoreEnv) + nBytesPaRams;

        ptrScratch = (Int *)(((char *)scratchEnv) - nBytesPaRams);
        ptrPersist = (Int *)(((char *)persistEnv) - nBytesPaRams);

        /* Copy 4 bytes at a time for optimization */
        nWords = (nBytes + 3) >> 2;

        for (i = 0; i < nWords; i++) {
            *ptrPersist++ = *ptrScratch++;
        }
        handle->env = persistEnv;
    }

#ifndef _ACPY3_CPUCOPY_
    /* Set the QCHMAP back to null PaRam */
    ACPY3_QCHMAP[handle->qdmaChan] = (Uns)(nullPaRam << 5) | (0x7 << 2);
#endif

    return;
}

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

