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
 *  ======== main.c ========
 */
#include <xdc/std.h>

#include <ti/sdo/ce/CERuntime.h>

#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ires/bufres/bufres.h>
#include <ti/sdo/fc/rman/rman.h>

#include <ti/sdo/ce/trace/gt.h>

extern Int smain(Int argc, String argv[]);

#define BUFLEN 0x400

/* trace info: module name, mask */
#define MOD_NAME "ti.sdo.ce.examples.apps.audio1_copy"
GT_Mask curMask = {0,0};

#ifdef LOCAL
Char buffer[BUFLEN];

extern Bool _ALG_allocMemory(IALG_MemRec *memTab, Int n);
extern Void _ALG_freeMemory(IALG_MemRec *memTab, Int n);
#endif

/*
 *  ======== main ========
 */
Int main(Int argc, String argv[])
{
#ifdef LOCAL
    BUFRES_Params  config;
    IRES_Status     status;
#endif

    /* init Codec Engine */
    CERuntime_init();

    /* init trace */
    GT_init();

    /* create a mask to allow a trace-print welcome message below */
    GT_create(&curMask, MOD_NAME);

    /* Enable all trace for this module */
    GT_set(MOD_NAME "=01234567");

    GT_0trace(curMask, GT_2CLASS, "main> " MOD_NAME "\n");

#ifdef LOCAL
    RMAN_init();

    /*
     *  Configure and register BUFRES resource. This code is used for both
     *  local and remote Linux apps. In the remote case, registering will
     *  not have any affect, since the IRES codec will be run on the DSP.
     *
     *  This particular resource cannot be auto-registered, since it needs
     *  to be configured with a buffer.
     */
    config.iresConfig.size = sizeof(BUFRES_Params);
    config.iresConfig.allocFxn = _ALG_allocMemory;
    config.iresConfig.freeFxn = _ALG_freeMemory;

    config.base = (Void *)buffer;
    config.length = BUFLEN;

    status = RMAN_register(&BUFRES_MGRFXNS, (IRESMAN_Params *)&config);
    GT_1trace(curMask, GT_2CLASS, "main>  RMAN_register returned 0x%x\n",
            (IArg)status);
#endif
    return (smain(argc, argv));
}
/*
 *  @(#) ti.sdo.ce.examples.apps.audio1_ires; 1,0,0,222; 12-2-2010 21:19:30; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

