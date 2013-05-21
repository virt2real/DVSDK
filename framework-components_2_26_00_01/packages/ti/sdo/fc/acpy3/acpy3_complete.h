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
 *  ======== acpy3_complete.h ========
 */
 

#ifdef _ACPY3_

# ifndef _ACPY3_COMPLETE_
# define _ACPY3_COMPLETE_

#include <xdc/std.h>

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3_qdma.h>
#include <ti/sdo/fc/acpy3/acpy3_util.h>

#ifndef _ACPY3_CPUCOPY_

#if defined(ACPY3_COMPLETE_INLINE) || defined(ACPY3_INLINE_ALL)
ACPY3_VERSION_MACRO
static __inline 
#endif
#if defined(ACPY3_COMPLETE_INLINE) || defined(ACPY3_INLINE_ALL) || \
    defined(ACPY3_COMPLETE_IMPLEMENTATION)

/*
 *  ======== ACPY3_complete ========
 *  Check to see if all dma transfers on logical channel are finished. 
 *  This is a non-blocking call.
 */
Bool ACPY3_complete(IDMA3_Handle handle)
{       
#ifdef xdc_target__isaCompatible_64P
    Uns                    csr;
#endif
    IDMA3_Handle          *lockPtr;
    ACPY3_MoreEnv         *moreEnv;
    Uns                    icrlMask;  
    Uns                    icrhMask;  

#if defined(ACPY3_COMPLETE_IMPLEMENTATION) 
    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_complete> Enter "
            "(handle=0x%x)\n", handle);

    GT_assert(ti_sdo_fc_acpy3_GTMask, handle != NULL);
#endif

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks, 
            handle, ACPY3_INSTR_COMPLETE_ENTER);

    if (!handle->transferPending) {
        /* No tansfers pending - channel already waited on since last start */
        ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks,
                handle, ACPY3_INSTR_COMPLETE_EXIT);

#if defined(ACPY3_COMPLETE_IMPLEMENTATION)

        GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_4CLASS, "ACPY3_complete> No "
                "transfer pending\n");

        GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_complete> Exit "
                "(status=TRUE)\n");
#endif

        return (TRUE);
    }

    /* 
     * Wait for a channel only once. Set the 'pending' flag whenever new
     * transfer is submitted, then clear it when ACPY3_wait() is issued.
     */
    moreEnv = (ACPY3_MoreEnv *)(handle->env);
    if (!(*moreEnv->iprRegister & moreEnv->iprMask)) {
        ACPY3_INSTR_CALLHOOKFXN(moreEnv->extendedHooks,handle, \
                                ACPY3_INSTR_COMPLETE_EXIT);
        
#if defined(ACPY3_COMPLETE_IMPLEMENTATION)
        GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_complete> Exit "
                "(status=FALSE)\n");
#endif

        return (FALSE);
    }
       
    /* Clear all the TCCs for the channel */
    icrlMask = moreEnv->icrlMask;
    icrhMask = moreEnv->icrhMask;
    if (icrlMask)
       *ACPY3_QDMA_ICR = icrlMask;
    if (icrhMask)
       *ACPY3_QDMA_ICRH = icrhMask;

#if defined(ACPY3_COMPLETE_IMPLEMENTATION)
    GT_2trace(ti_sdo_fc_acpy3_GTMask, GT_2CLASS, "ACPY3_complete> ICR register"
            " set to 0x%x: 0x%x\n", icrhMask, icrlMask);
#endif
       
    /* 
     * Mark the QDMA channel as unlocked.
     * This must be done atomically.
     */
    lockPtr = &_ACPY3_qchLockTbl[handle->qdmaChan];
#ifdef xdc_target__isaCompatible_64P
    csr = _disable_interrupts();
#endif
    if (*lockPtr == handle)
        *lockPtr = 0;
#ifdef xdc_target__isaCompatible_64P
   _restore_interrupts(csr); /* reenable interrupts */
#endif       
   handle->transferPending = FALSE;
        
   ACPY3_INSTR_CALLHOOKFXN(moreEnv->extendedHooks, handle, 
            ACPY3_INSTR_COMPLETE_EXIT);

#if defined(ACPY3_COMPLETE_INLINE) || defined(ACPY3_INLINE_ALL) 
   GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_complete> Exit (status"
           "=TRUE)\n");
#endif

   return (TRUE);   
}
#endif /* if defined(ACPY3_COMPLETE_INLINE) || 
       **    defined(ACPY3_INLINE_ALL) || 
       **    defined(ACPY3_COMPLETE_IMPLEMENTATION)
       */
#  endif /* ifndef _ACPY3_CPUCOPY_ */
# endif /* _ACPY3_COMPLETE_ */
#else
#error "ti/sdo/fc/acpy3/acpy3.h must be included first"
#endif 
/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

