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
 *  ======== acpy3_fastconfigure32b.h ========
 */

#ifdef _ACPY3_

#ifndef _ACPY3_FASTCONFIGURE32B_
#define _ACPY3_FASTCONFIGURE32B_

#include <xdc/std.h>

#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3_qdma.h>
#include <ti/sdo/fc/acpy3/acpy3_util.h>

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#ifdef xdc_target__isaCompatible_64P
#if defined(ACPY3_FASTCONFIGURE32B_INLINE) || defined(ACPY3_INLINE_ALL)
ACPY3_VERSION_MACRO
static __inline
#endif
#if defined(ACPY3_FASTCONFIGURE32B_INLINE) || defined(ACPY3_INLINE_ALL) || \
    defined(ACPY3_FASTCONFIGURE32B_IMPLEMENTATION)

/*
 *  ======== ACPY3_fastConfigure32b ========
 */
Void ACPY3_fastConfigure32b(IDMA3_Handle restrict handle,
    ACPY3_ParamField32b fieldId, Uns value, short transferNo)
{
    ACPY3_PaRamRegs * restrict paRamCache;
#if _ACPY3_DIRTY_BITS
    ACPY3_MoreEnv   * restrict env;
    short                      transferNoP1;
#endif

#if defined(ACPY3_FASTCONFIGURE32B_IMPLEMENTATION)
    GT_4trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, 
            "ACPY3_fastConfigure32b> Enter (handle=0x%x, fieldId=0x%x, "
            "value=0x%x, transferNo=%d)\n", handle, fieldId, value, transferNo);

    GT_assert(ti_sdo_fc_acpy3_GTMask, handle != NULL);
    GT_assert(ti_sdo_fc_acpy3_GTMask, handle->protocol == &ACPY3_PROTOCOL);
    GT_assert(ti_sdo_fc_acpy3_GTMask, transferNo >= 0);
    GT_assert(ti_sdo_fc_acpy3_GTMask, 
            transferNo < ((ACPY3_MoreEnv *)(handle->env))->numPaRams);
    GT_assert(ti_sdo_fc_acpy3_GTMask, !handle->transferPending);
#endif /* if defined(ACPY3_FASTCONFIGURE32B_IMPLEMENTATION) */

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks, 
            handle, ACPY3_INSTR_FASTCONFIGURE32_ENTER);

#if _ACPY3_DIRTY_BITS
    env = ((ACPY3_MoreEnv *)handle->env);
    /*
     * Mark a bit in the dirty bit table for this PaRAM as dirty
     */
    env->dirtyBitTable[transferNo] |= 1 << ((Int)fieldId >> 2);
    transferNoP1 = transferNo + 1;
    paRamCache = (ACPY3_PaRamRegs *)env - transferNoP1;
#else
    paRamCache = (ACPY3_PaRamRegs *)ACPY3_getPaRamCache(handle, transferNo);
#endif

    *((Uns *)((Uns)paRamCache + fieldId)) = value;
    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)handle->env)->extendedHooks, 
            handle, ACPY3_INSTR_FASTCONFIGURE32_EXIT);

#if defined(ACPY3_FASTCONFIGURE32B_IMPLEMENTATION)
    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_fastConfigure32b> "
            "Exit\n");
#endif

}
#endif /* if defined(ACPY3_FASTCONFIGURE32B_INLINE) ||
       **    defined(ACPY3_INLINE_ALL) ||
       **    defined(ACPY3_FASTCONFIGURE32B_IMPLEMENTATION)
       */
#endif /* _ACPY3_FASTCONFIGURE32B_ */
#else
#error "ti/sdo/fc/acpy3/acpy3.h must be included first"
#endif
#endif /* xdc_target__isaCompatible_64P */
/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

