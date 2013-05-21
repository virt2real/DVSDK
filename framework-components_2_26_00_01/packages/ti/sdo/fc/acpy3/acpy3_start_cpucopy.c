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
 *  ======== acpy3_start_cpuCopy.c ========
 *  No DMA (just CPU copy) C model of the acpy3_start() implementation.
 */

#include <xdc/std.h>
#include "acpy3.h"
#include <ti/xdais/idma3.h>
#include "acpy3_util.h"

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;


#ifdef _ACPY3_CPUCOPY_

#ifdef __TI_COMPILER_VERSION__
#pragma CODE_SECTION(ACPY3_start, ".text:ACPY3_start")
#endif

/*
 *  ======= ACPY3_start ========
 *  Submit a single or linked transfer using the most recently.
 *  configured transfer parameter settings.
 */
void ACPY3_start(IDMA3_Handle handle)
{
    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_start> Enter "
            "(handle=0x%x)\n",handle);

    if (handle->transferPending) {

        /* Wait for previously started transfer (if any) to complete */

        GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_4CLASS, "ACPY3_start> Waiting for"
                " previously started transfer\n");

        ACPY3_wait(handle);
    }

    /*
     * As soon as channel is clear mark the channel state to indicate a
     * new transfer is being issued and 'transfer is pending'.
     * Only a subsequent 'ACPY3_wait' will clear the pending state.
     */
    handle->transferPending = TRUE;

    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_start> Exit\n");

}


#endif

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

