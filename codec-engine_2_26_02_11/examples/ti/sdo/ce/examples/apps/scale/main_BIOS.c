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
/**
 *  @file       ti/sdo/ce/examples/apps/scale/main_BIOS.c
 *
 *  @brief      This is a BIOS main() routine
 */
#include <xdc/std.h>
#include <ti/bios/include/std.h>

#include <tsk.h>
#include <sys.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#include <smain.h>

/* trace info: module name, mask */
GT_Mask curMask = {0,0};

static String taskName = "scale";

/**
 *  @brief      The BIOS main() entry point.
 *
 *  @remark     The purpose of this function is to create a BIOS worker task
 *              to house our example.
 *
 *  @remark     This is called during BIOS_init, but before the scheduler
 *              has begun running.
 */
Int main(Int argc, String argv[])
{
    TSK_Attrs attrs = TSK_ATTRS;
    attrs.stacksize = 6 * 1024;
    attrs.name = taskName;

    CERuntime_init();

    GT_create(&curMask, "ZZ");

    /* Enable all trace for this "ZZ" module */
    GT_set("ZZ=01234567");

    GT_0trace(curMask, GT_2CLASS, "main> Welcome to app's main().\n");

    if (TSK_create((Fxn)smain, &attrs, argc, argv) == NULL) {
        SYS_abort("main: failed to create smain thread.");
    }

    return (0);
}

/*
 *  @(#) ti.sdo.ce.examples.apps.scale; 1,0,0,263; 12-2-2010 21:20:03; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

