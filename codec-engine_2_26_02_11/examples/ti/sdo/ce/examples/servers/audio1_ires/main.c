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
/**
 *  @file       ti/sdo/ce/examples/servers/audio1_ires/main.c
 */
#include <xdc/std.h>

#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#include <ti/xdais/ires.h>
#include <ti/sdo/fc/ires/bufres/bufres.h>
#include <ti/sdo/fc/rman/rman.h>

/* trace info: module name, mask */
static GT_Mask gtMask = {0,0};

/* Defined in linker template file, mark the beginning and end of buffer */
extern __FAR__ UInt32 BUFMEM_base;
extern __FAR__ UInt32 BUFMEM_end;

extern IRESMAN_PersistentAllocFxn DSKT2_allocPersistent;
extern IRESMAN_PersistentFreeFxn  DSKT2_freePersistent;

/* Configuration parameters for buffer resource */
static BUFRES_Params config;

/*
 *  ======== main ========
 */
Void main(Int argc, Char *argv[])
{
    /* init Codec Engine */
    CERuntime_init();

    /* init trace */
    GT_init();

    /* create a mask to allow a trace-print welcome message below */
    GT_create(&gtMask, "audio1_ires_server");

    /* ...and initialize all masks in this module to "on" */
    GT_set("audio1_ires_server=01234567");

    GT_0trace(gtMask, GT_4CLASS, "main> Welcome to DSP server's main().\n");

    /* Configure and register BUFRES resource with RMAN */

    /*
     * Note that we can't use RMAN's auto-register with the BUFRES resource
     * because it takes runtime config params that don't have logical
     * defaults.
     */
    config.iresConfig.size = sizeof(BUFRES_Params);
    config.iresConfig.allocFxn = DSKT2_allocPersistent;
    config.iresConfig.freeFxn = DSKT2_freePersistent;

    config.base = (Void *)&BUFMEM_base;
    config.length = (UInt32)&BUFMEM_end - (UInt32)&BUFMEM_base + 1;

    RMAN_register(&BUFRES_MGRFXNS, (IRESMAN_Params *)&config);
}
/*
 *  @(#) ti.sdo.ce.examples.servers.audio1_ires; 1, 0, 0,160; 12-2-2010 21:23:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

