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
 *  ======== fcpy.c ========
 *  FCPY Module - implementation of FCPY module APIs.
 */

#pragma CODE_SECTION (FCPY_init, ".text:init")
#pragma CODE_SECTION (FCPY_exit, ".text:exit")
#pragma CODE_SECTION (FCPY_apply, ".text:apply")
#pragma CODE_SECTION (FCPY_control, ".text:control")

#include <xdc/std.h>

#include <ti/sdo/fc/utils/api/alg.h>

#include "fcpy.h"
#include "fcpy_ti.h"

/*
 *  ======== FCPY_apply ========
 *  Apply a FCPY function to the input array and place results in the
 *  output array.
 */
Void FCPY_apply(FCPY_Handle handle, Void * in, Void * out)
{
    /* activate instance object */
    ALG_activate((ALG_Handle)handle);
    
    handle->fxns->doCopy(handle, in, out);      /* copy data */

    /* deactivate instance object */
    ALG_deactivate((ALG_Handle)handle);
}

/*
 *  ======== FCPY_control ========
 *  Used to either write to the read/write parameters in the status
 *  structure or to read all the parameters in the status structure.
 */
XDAS_Bool FCPY_control(FCPY_Handle handle, FCPY_Cmd cmd, FCPY_Status *status)
{
    /* Check for valid handle and fxn ptr and do control operation */
    if (handle->fxns->control) {
        return (handle->fxns->control(handle, cmd, status));
    }

    return (XDAS_FALSE);
}

/*
 *  ======== FCPY_exit ========
 *  Module finalization
 */
Void FCPY_exit(Void)
{
    FCPY_TI_exit();
}

/*
 *  ======== FCPY_init ========
 *  Module initialization
 */
Void FCPY_init(Void)
{
    FCPY_TI_init();
}
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

