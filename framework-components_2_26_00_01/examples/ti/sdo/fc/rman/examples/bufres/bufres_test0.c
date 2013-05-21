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
 *  ======== bufres_test0.c ========
 *  Test the functionality of the Buffer Resource Manager, independent
 *  of the RMAN framework.
 */

#include <xdc/std.h>
#include <stdio.h>

#include <ti/sdo/fc/ires/iresman.h>
#include <ti/sdo/fc/dskt2/dskt2.h>  /* for persistentAlloc/Free */

/* Including this to get rid of warnings when the static variable,  
   PROTOCOLREVISION in ires headers isn't being used */
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/bufres/bufres.h>
#include "bufres_util.h"

extern far UInt32 BUFMEM_base;
extern far UInt32 BUFMEM_end;

extern Void smain(Int argc, Char * argv[]);

/*
 *  ======== main ========
 */
Void main(Int argc, Char * argv[])
{
}

/*
 *  ======== smain ========
 */
/* ARGSUSED */
Void smain(Int argc, Char * argv[])
{
    BUFRES_Args        args;
    BUFRES_Handle      bufres[10];
    BUFRES_Params      config;
    IRES_Status        status;
    Int                scratchId;
    Void              *base;
    Bool               passed = FALSE;

    config.iresConfig.size = sizeof(BUFRES_Params);
    config.iresConfig.allocFxn = DSKT2_allocPersistent;
    config.iresConfig.freeFxn = DSKT2_freePersistent;

    config.base = (Void *)&BUFMEM_base;
    config.length = (UInt32)&BUFMEM_end - (UInt32)&BUFMEM_base + 1;

    status = BUFRES_init(&config);

    if (status != IRES_OK) {
        /* Test failed */
        goto done;
    }
    else {
        /* Allocate a bunch of resources */
        args.iresArgs.size = sizeof(BUFRES_Args);
        args.iresArgs.mode = IRES_SCRATCH;
        args.align = 8;
        args.length = 0x18;

        scratchId = 1;
        if ((bufres[0] = BUFRES_get((IALG_Handle)NULL, &args, scratchId, 
                &status)) == NULL) {
            goto done;
        }
        else {
            base = bufres[0]->base;
            status = BUFRES_free((IALG_Handle)NULL, bufres[0], &args, 
                    scratchId);
            bufres[0] = NULL;
            if (status != IRES_OK) {
                goto done;
            }
        }

        args.iresArgs.mode = IRES_PERSISTENT;
        bufres[0] =  BUFRES_get((IALG_Handle) NULL, &args, scratchId, &status);

        if (bufres[0] == NULL) {
            printf("BUFRES_get() failed [0x%x]\n", status);
            goto done;
        }
        else {
            /* Should get the same base address as before */
            if (base != bufres[0]->base) {
                printf("BUFRES_get() returned wrong base address [0x%x] "
                        "should have been [0x%x]\n",
                        bufres[0]->base, base);
                goto done;
            }
        }

        /* Should not be allowed to allocate another persistent buffer */
        args.iresArgs.mode = IRES_PERSISTENT;
        if ((bufres[1] = BUFRES_get((IALG_Handle)NULL, &args, scratchId, 
                &status)) != NULL) {
            goto done;
        }

        /* Should not be allowed to allocate another scratch buffer */
        args.iresArgs.mode = IRES_SCRATCH;
        bufres[1] = BUFRES_get((IALG_Handle)NULL, &args, scratchId, &status);
        if (bufres[1] != NULL) {
            printf("BUFRES_get() failed to fail for scratch resource [0x%x]\n",
                    status);
            goto done;
        }

        status = BUFRES_free((IALG_Handle)NULL, bufres[0], &args, scratchId);
        bufres[0] = NULL;
        if (status != IRES_OK) {
            printf("BUFRES_free() failed [0x%x]\n", status);
            goto done;
        }
        args.iresArgs.mode = IRES_SCRATCH;
        bufres[0] = BUFRES_get((IALG_Handle)NULL, &args, scratchId, &status);
        if (bufres[0] == NULL) {
            printf("BUFRES_get() failed for scratch resource [0x%x]\n",
                    status);
            goto done;
        }

        /* Should not be allowed to allocate scratch buffer in another group */
        args.iresArgs.mode = IRES_SCRATCH;
        bufres[1] = BUFRES_get((IALG_Handle)NULL, &args, scratchId + 1,
                &status);
        if (bufres[1] != NULL) {
            printf("BUFRES_get() failed to fail for allocating scratch "
                    "resource from another group [0x%x]\n", status);
            goto done;
        }

        /* Allowed to allocate another scratch buffer in same group */
        bufres[1] = BUFRES_get((IALG_Handle)NULL, &args, scratchId, &status);
        if (bufres[1] == NULL) {
            printf("BUFRES_get() failed for second scratch resource [0x%x]\n",
                    status);
            goto done;
        }
        if (bufres[1]->base != bufres[0]->base) {
            printf("BUFRES_get() failed: bufres[1]->base [0x%x] different "
                    "from bufres[0]->base [0x%x]\n", bufres[1]->base,
                    bufres[0]->base);
            goto done;
        }
        BUFRES_free((IALG_Handle)NULL, bufres[0], &args, scratchId);
        BUFRES_free((IALG_Handle)NULL, bufres[1], &args, scratchId);
        bufres[0] = bufres[1] = NULL;

        passed = TRUE;
    }

done:
    if (passed) {
        printf("TEST PASSED\n");
    }
    else {
        printf("TEST FAILED\n");
    }
}
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres; 1, 0, 0,177; 12-1-2010 17:25:35; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

