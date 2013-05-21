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
 *  ======== acpy3_instrument.c ========
 *  C model of the acpy3_instrument() implementation using Joule QDMA.
 */

#include <xdc/std.h>

#include <ti/xdais/idma3.h>
#include "acpy3_qdma.h"
#include "acpy3_util.h"
#include "acpy3_instr.h"

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

/*
 *  ======== ACPY3_INSTR_registerHooks ========
 * Call to register the instrumentation hook functions with the ACPY3 library
 */
Void ACPY3_INSTR_registerHooks(IDMA3_Handle handle, ACPY3_INSTR_Hooks * hooks,
    ACPY3_INSTR_ExtendedHooks * extendedHooks)
{
    ACPY3_MoreEnv * restrict moreEnv;
    /* extract the environment from the handle */

    GT_3trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_INSTR_registerHooks> "
            "(handle=0x%x, hooks=0x%x, extendedHooks=0x%x)\n", handle, hooks,
            extendedHooks);        

    moreEnv = (ACPY3_MoreEnv *)(handle->env);
    moreEnv->hooks = hooks;
    moreEnv->extendedHooks = extendedHooks;

    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_INSTR_registerHooks> "
            "Exit\n");
}

/*
 *  ======== ACPY3_INSTR_unregisterHooks ========
 * Call to unregister the instrumentation hook functions from the ACPY3 library
 */
Void ACPY3_INSTR_unregisterHooks(IDMA3_Handle handle)
{
    ACPY3_MoreEnv * restrict moreEnv;

    GT_1trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_INSTR_unregisterHooks> "
            "Enter (handle=0x%x)\n",handle);

    moreEnv = (ACPY3_MoreEnv *)(handle->env);
    moreEnv->hooks = NULL;
    moreEnv->extendedHooks = NULL;

    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_INSTR_unregisterHooks> "
            "Exit\n"); 
}
/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

