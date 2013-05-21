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
 *  ======== acpy3_complete.c ========
 */



#include <xdc/std.h>

#include <ti/xdais/idma3.h>
#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

#define CURTRACE ti_sdo_fc_acpy3_GTMask

#include "acpy3.h"
#include "acpy3_util.h"



#ifdef __TI_COMPILER_VERSION__
#pragma CODE_SECTION(ACPY3_complete, ".text:ACPY3_complete")
#endif

#ifndef _ACPY3_CPUCOPY_

#define ACPY3_COMPLETE_IMPLEMENTATION
#include "acpy3_complete.h"

#else

/*
 *  ======== ACPY3_complete ========
 *  Check to see if all dma transfers on logical channel are finished.
 *  This is a non-blocking call.
 */
Bool ACPY3_complete(IDMA3_Handle handle)
{
    GT_1trace(CURTRACE, GT_ENTER, "ACPY3_complete> Enter (handle=0x%x)\n",
            handle);

    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks, 
            handle, ACPY3_INSTR_COMPLETE_ENTER);

    GT_assert(CURTRACE, handle != NULL);

    if (handle->transferPending) {
        GT_0trace(CURTRACE, GT_2CLASS, "ACPY3_complete> Transfer Pending\n");
        ACPY3_wait(handle);
    }

    GT_0trace(CURTRACE, GT_2CLASS, "ACPY3_complete> No Transfers Pending\n");

    /* No transfers pending. */
    ACPY3_INSTR_CALLHOOKFXN(((ACPY3_MoreEnv *)(handle->env))->extendedHooks, 
            handle, ACPY3_INSTR_COMPLETE_EXIT);

    GT_0trace(CURTRACE, GT_ENTER, "ACPY3_complete> Exit (status=TRUE)\n");

    return (TRUE);
}
#endif
/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

