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
 *  ======== acpy3_init.c ========
 */

#include <xdc/std.h>

#include "acpy3.h"

#ifdef __TI_COMPILER_VERSION__
#pragma CODE_SECTION(ACPY3_init, ".text:ACPY3_init")
#pragma CODE_SECTION(ACPY3_exit, ".text:ACPY3_exit")
#endif

#include <ti/sdo/utils/trace/gt.h>
extern GT_Mask ti_sdo_fc_acpy3_GTMask;

static __FAR__ Int _ACPY3_refCount  = 0;


/*
 *  ======== ACPY3_exit ========
 *  Finalize the ACPY3 module
 */
Void ACPY3_exit(Void)
{
    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_exit> Enter\n");

    _ACPY3_refCount--;

    if (_ACPY3_refCount == 0) {
    }

    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_exit> Exit\n");
}

/*
 *  ======== ACPY3_init ========
 *  Initialize the ACPY3 module
 */
void ACPY3_init(Void)
{
    if (_ACPY3_refCount == 0) {
        GT_init();
        GT_create(&ti_sdo_fc_acpy3_GTMask, ACPY3_GTNAME);
     }

    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_init> Enter\n");

    _ACPY3_refCount++;
    GT_0trace(ti_sdo_fc_acpy3_GTMask, GT_ENTER, "ACPY3_init> Exit\n");
}

/*
 *  @(#) ti.sdo.fc.acpy3; 1, 0, 4,301; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

