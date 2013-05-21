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
 *  ======== acpy3_wait.h ========
 */


#ifdef _ACPY3_

#ifndef _ACPY3_WAIT_
#define _ACPY3_WAIT_

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3_qdma.h>
#include <ti/sdo/fc/acpy3/acpy3_util.h>

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#ifndef _ACPY3_CPUCOPY_

#if defined(ACPY3_WAIT_INLINE) || defined(ACPY3_INLINE_ALL)
ACPY3_VERSION_MACRO
static __inline 
#endif
#if defined(ACPY3_WAIT_INLINE) || defined(ACPY3_INLINE_ALL) || \
    defined(ACPY3_WAIT_IMPLEMENTATION)

/*
 *  ======== ACPY3_wait ========
 */
Void ACPY3_wait(IDMA3_Handle restrict handle)
{
    Uns                       csr;
    IDMA3_Handle  * restrict  lockPtr;

    ACPY3_MoreEnv * restrict  moreEnv;
    volatile Uns             *iprRegister; /* QDMA Interrupt pending register */
    Uns                       iprMask;  
    Uns                       icrlMask;  
    Uns                       icrhMask;  
    Uns                       pending;
    Uns                       StatusReg;
    IDMA3_Handle              prevLock;
  
#if defined(ACPY3_WAIT_IMPLEMENTATION)
    GT_assert(ti_sdo_fc_acpy3_GTMask, handle != NULL);

    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_wait> Enter "
            "(handle=0x%x)\n", handle);
#endif    

    moreEnv = (ACPY3_MoreEnv *)(handle->env);         /* read in advance ptr */
    ACPY3_INSTR_CALLHOOKFXN(moreEnv->hooks, handle, ACPY3_INSTR_WAIT_ENTER);

    pending = handle->transferPending;                /* read in advance */
    lockPtr = &_ACPY3_qchLockTbl[handle->qdmaChan];   /* read in advance ptr */
    handle->transferPending = FALSE;                  /* reset in advance */

    iprRegister = (volatile Uns *)moreEnv->iprRegister; /* read in advance */
    iprMask = moreEnv->iprMask;                       /* read in advance */
    icrlMask = moreEnv->icrlMask;                     /* read in advance */
    icrhMask = moreEnv->icrhMask;                     /* read in advance */
    StatusReg = *iprRegister;                         /* read STATUS */

    /* 
     * Wait for a channel only once. Set the 'pending' flag whenever new
     * transfer is submitted, then clear it when ACPY3_wait* is issued.
     */
    if (!pending) {
        ACPY3_INSTR_CALLHOOKFXN(moreEnv->hooks, handle, ACPY3_INSTR_WAIT_EXIT);

        GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_4CLASS, "ACPY3_wait> No transfer"
                " pending\n");

        GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_wait> Exit\n");

        return;
    }

    while (!(StatusReg & iprMask)) {    /* wait on the final TCC being set */
        StatusReg = *iprRegister;
    }

    /*
     * Mark the QDMA channel as unlocked.
     * This must be done atomically.
     */
    csr = _disable_interrupts();
    prevLock = *lockPtr;

    /* Clear all the TCCs for the channel (moved here for removing nops) */
    if (icrlMask)
       *ACPY3_QDMA_ICR = icrlMask;
    if (icrhMask)
       *ACPY3_QDMA_ICRH = icrhMask;

    if (prevLock == handle)
        *lockPtr = 0;

    _restore_interrupts(csr); /* reenable interrupts */

    ACPY3_INSTR_CALLHOOKFXN(moreEnv->hooks, handle, ACPY3_INSTR_WAIT_EXIT);

#if defined(ACPY3_WAIT_IMPLEMENTATION)
    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_wait> Exit\n");
#endif

}
#endif /* if defined(ACPY3_WAIT_INLINE) ||
       **    defined(ACPY3_INLINE_ALL) ||
       **    defined(ACPY3_WAIT_IMPLEMENTATION)
       */
#  endif /* ifndef _ACPY3_CPUCOPY_ */
# endif /* _ACPY3_WAIT_ */
#else
#error "ti/sdo/fc/acpy3/acpy3.h must be included first"
#endif
/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

