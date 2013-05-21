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
 *  ======== shmbuf_test0.c ========
 *  Test the functionality of the Buffer Resource Manager.
 */

#include <xdc/std.h>
#include <stdio.h>

#include <ti/sdo/utils/trace/gt.h>

#include <ti/sdo/fc/rman/rman.h>

#include <ti/sdo/fc/ires/shmbuf/shmbuf.h>
#include "shmbuf_util.h"

#define SHMBUFSIZE 0x400

extern Int smain(Int argc, Char * argv[]);

/*
 *  ======== main ========
 */
Int main(Int argc, Char * argv[])
{
    GT_init();

    /* To see internal tracing details, uncomment GT_set statements below */
    GT_set("ti.sdo.fc.ires.shmbuf=01234567");
    GT_set("ti.sdo.fc.utils.shm=01234567");
    GT_set("ti.sdo.fc.rman=01234567");

    return (smain(argc, argv));
}

/*
 *  ======== smain ========
 */
/* ARGSUSED */
Int smain(Int argc, Char * argv[])
{
    SHMBUF_Args        args;
    SHMBUF_Handle      shmBuf;
    IRES_Status        status;
    Int                scratchId;
    Void              *base;
    Bool               passed = FALSE;

    /* Initialize and register resource manager */
    RMAN_init();

    SHMBUF_PARAMS.bufsize = SHMBUFSIZE;

    printf("Calling RMAN_register()...\n");
    status = RMAN_register(&SHMBUF_MGRFXNS, (IRESMAN_Params *)&SHMBUF_PARAMS);

    if (status != IRES_OK) {
        /* Test failed */
        printf("RMAN_register() failed [0x%x]\n", status);
        goto done;
    }
    else {
        args.iresArgs.size = sizeof(SHMBUF_Args);
        args.iresArgs.mode = IRES_PERSISTENT;
        args.align = 8;
        args.length = 0x18;
        scratchId = 1;

        /* Allocate the resource */
        shmBuf = SHMBUF_get((IALG_Handle)NULL, &args, scratchId, &status);
        if (shmBuf == NULL) {
            printf("SHMBUF_get() failed [0x%x]\n", status);
            goto done;
        }
        else {
            base = shmBuf->base;
            printf("Sleeping...\n");
            sleep(10);

            printf("Freeing resource...\n");
            /* Free the resource */
            status = SHMBUF_free((IALG_Handle)NULL, shmBuf, &args, 
                    scratchId);
            shmBuf = NULL;
            if (status != IRES_OK) {
                goto done;
            }
        }

        status = RMAN_unregister(&SHMBUF_MGRFXNS);
        if (status != IRES_OK) {
            printf("RMAN_unregister() failed [0x%x]\n", status);
        }
        else {
            passed = TRUE;
        }
    }

done:

    RMAN_exit();

    if (passed) {
        printf("TEST PASSED\n");
    }
    else {
        printf("TEST FAILED\n");
    }

    return (0);
}
/*
 *  @(#) ti.sdo.fc.rman.examples.shmbuf; 1, 0, 0,119; 12-1-2010 17:25:54; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

