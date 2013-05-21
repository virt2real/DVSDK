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
 *  ======== acpy3_fastsetfinal.h ========
 */


#ifdef _ACPY3_

#ifndef _ACPY3_FASTSETFINAL_
#define _ACPY3_FASTSETFINAL_

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3_util.h>
#include <ti/sdo/fc/acpy3/acpy3.h>
#include <ti/sdo/utils/trace/gt.h>

extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#if defined(ACPY3_FASTSETFINAL_INLINE) || defined(ACPY3_INLINE_ALL)
ACPY3_VERSION_MACRO
static __inline
#endif
#if defined(ACPY3_FASTSETFINAL_INLINE) || defined(ACPY3_INLINE_ALL) || \
    defined(ACPY3_FASTSETFINAL_IMPLEMENTATION)

/*
 *  ======== ACPY3_fastSetFinal ========
 */
Void ACPY3_fastSetFinal(IDMA3_Handle restrict handle, short transferNo)
{
    ACPY3_PaRamRegs * restrict paRamCacheOld;
    ACPY3_PaRamRegs * restrict paRamCacheNew;
    ACPY3_MoreEnv   * restrict env;
    short                      transferNoP1;
    short                      finalP1;
#if _ACPY3_DIRTY_BITS
    short                      final;
    unsigned char   * restrict dirtyBitTblPtr;
#endif

    GT_2trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_fastSetFinal> Enter "
            "(handle=0x%x, transferNo=%d)\n", handle, transferNo);

#if defined(ACPY3_FASTSETFINAL_IMPLEMENTATION)
    GT_assert(ti_sdo_fc_acpy3_GTMask, handle != NULL);
    GT_assert(ti_sdo_fc_acpy3_GTMask, handle->env != NULL);
    GT_assert(ti_sdo_fc_acpy3_GTMask, handle->protocol == &ACPY3_PROTOCOL);
    GT_assert(ti_sdo_fc_acpy3_GTMask, 
            (transferNo < ((ACPY3_MoreEnv *)(handle->env))->numPaRams) &&
            (transferNo >= 0));
    /* The handle is only allowed a single TCC */
    GT_assert(ti_sdo_fc_acpy3_GTMask, 
            ((ACPY3_MoreEnv *)(handle->env))->numTccs == 1);
#endif /* if defined(ACPY3_FASTSETFINAL_IMPLEMENTATION) */

    env = (ACPY3_MoreEnv *)handle->env;

    ACPY3_INSTR_CALLHOOKFXN(env->extendedHooks, handle,
            ACPY3_INSTR_SETFASTFINAL_ENTER);

    /* The previous transfer number that was configured as final. */
    finalP1 = (short)handle->numPaRams;
    transferNoP1 = transferNo + 1;
    handle->numPaRams = transferNoP1;

    GT_2trace(ti_sdo_fc_acpy3_GTMask, GT_2CLASS, "ACPY3_fastSetFinal> Previous"
            "final transfer %d Number of paRams %d\n", finalP1, transferNoP1);

#if _ACPY3_DIRTY_BITS
    final = finalP1 - 1;
#endif

    /* paRamCacheOld = (ACPY3_PaRamRegs *)ACPY3_getPaRamCache(handle,final); */
    /* paRamCacheNew = (ACPY3_PaRamRegs *)ACPY3_getPaRamCache(handle, 
    transferNo); */
    paRamCacheOld = (ACPY3_PaRamRegs *)env - finalP1;
    paRamCacheNew = (ACPY3_PaRamRegs *)env - transferNoP1;

#if _ACPY3_DIRTY_BITS
    dirtyBitTblPtr = env->dirtyBitTable;
#endif

    /*
     *  Reset the link id of the previous transfer that was configured as
     *  final, unless it is the last PaRam allocated to the channel.
     */

    paRamCacheOld->link =
        (unsigned short)ACPY3_getPaRamLinkIndex(handle, finalP1);

    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_2CLASS, "ACPY3_fastSetFinal> Reset "
            " the link id of the previous final paRam 0x%x\n", 
            paRamCacheOld->link);

    /*
     *  Clear the static bit since "final" is no longer the last transfer.
     *  Clear the old tcc and TCC_INTEN.
     */
    paRamCacheOld->opt &= ~(ACPY3_TCCMASK             |
                            ACPY3_PARAMOPTS_TCC_INTEN |
                            ACPY3_PARAMOPTS_STATIC);

    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_2CLASS, "ACPY3_fastSetFinal> Set the"
            " OPT of the previous final paRam 0x%x\n", paRamCacheOld->opt);

    /*
     * Update the paRam cache for the new final transfer.
     * Set up final transfer with no linking.
     */

    paRamCacheNew->link = 0xffff;

    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_2CLASS, "ACPY3_fastSetFinal> Set the"
            " link of the new final paRam 0x%x\n", paRamCacheNew->link);

    /*
     *  Since this will be the last transfer, we need to use a tcc.
     *  Since the last transfer always uses the first tcc in the table,
     *  we update the opt field of the PaRam to use that.
     */

    paRamCacheNew->opt = ACPY3_TCCBITS(handle->tccTable[0]) |   /* TCC_CHAN */
                         ACPY3_PARAMOPTS_AB_SYNC            |
                         ACPY3_PARAMOPTS_TCC_INTEN          |
                         ACPY3_PARAMOPTS_STATIC;

    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_2CLASS, "ACPY3_fastSetFinal> Set the"
            " OPT of the new final paRam 0x%x\n", paRamCacheNew->opt);

#if _ACPY3_DIRTY_BITS
    /* Mark the link field as dirty, since it has changed. */
    dirtyBitTblPtr[final] |= ACPY3_DIRTYLINK;

    /* Mark the opts field of the PaRam for this transfer as dirty. */
    dirtyBitTblPtr[transferNo] |= ACPY3_DIRTYLINK | ACPY3_DIRTYOPTS;
#endif
    ACPY3_INSTR_CALLHOOKFXN(env->extendedHooks, handle,
            ACPY3_INSTR_SETFASTFINAL_EXIT);

    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_fastSetFinal> Exit\n");
}
#endif /* if defined(ACPY3_FASTSETFINAL_INLINE) ||
       **    defined(ACPY3_INLINE_ALL) ||
       **    defined(ACPY3_FASTSETFINAL_IMPLEMENTATION)
       */
#endif /* _ACPY3_FASTSETFINAL_ */
#else
#error "ti/sdo/fc/acpy3/acpy3.h must be included first"
#endif

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

