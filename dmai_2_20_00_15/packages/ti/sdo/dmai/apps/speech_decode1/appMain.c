/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

/*
 * This applications decodes an elementary stream speech file using a specified
 * XDM speech codec to the sound device driver.
 */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Sound.h>
#include <ti/sdo/dmai/Loader.h>
#include <ti/sdo/dmai/ce/Sdec1.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{
    Sound_Attrs             sAttrs      = Sound_Attrs_MONO_DEFAULT;
    Loader_Attrs            lAttrs      = Loader_Attrs_DEFAULT;
    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    SPHDEC1_Params          params      = Sdec1_Params_DEFAULT;
    SPHDEC1_DynamicParams   dynParams   = Sdec1_DynamicParams_DEFAULT;
    Sdec1_Handle            hSd1        = NULL;
    Sound_Handle            hSound      = NULL;
    Loader_Handle           hLoader     = NULL;
    Engine_Handle           hEngine     = NULL;
    Buffer_Handle           hOutBuf     = NULL;
    Int                     numFrame    = 0;
    Buffer_Handle           hInBuf;
    Int                     ret         = Dmai_EOK;

    printf("Starting application...\n");

    /* Initialize the codec engine run time */
    CERuntime_init();

    /* Initialize DMAI */
    Dmai_init();
    
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }

    params.compandingLaw = args->compandingLaw;

    /* Create the SPHDEC1 based speech decoder */
    hSd1 = Sdec1_create(hEngine, args->codecName, &params, &dynParams);

    if (hSd1 == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    bAttrs.memParams.align = lAttrs.mParams.align = BUFSIZEALIGN; 

    /* Create the sound device */
    sAttrs.sampleRate = 8000;
    sAttrs.mode = Sound_Mode_OUTPUT;
    sAttrs.leftGain  = 127;
    sAttrs.rightGain = 127;
    sAttrs.bufSize   = Sdec1_getOutBufSize(hSd1);

    hSound = Sound_create(&sAttrs);

    if (hSound == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create speech device\n");
        goto cleanup;
    }

    /* Use cached buffers if requested */  
    if (args->cache) {
        bAttrs.memParams.flags = lAttrs.mParams.flags = Memory_CACHED;
    } 
    
    /* Ask the codec how much input data it needs */
    lAttrs.readSize = Sdec1_getInBufSize(hSd1);

    /* Make the total ring buffer larger */
    lAttrs.readBufSize = Dmai_roundUp(lAttrs.readSize * 512, BUFSIZEALIGN);

    /* Create the file loader */
    hLoader = Loader_create(args->inFile, &lAttrs);

    if (hLoader == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create loader\n");
        goto cleanup;
    }

    hOutBuf = Buffer_create(Sdec1_getOutBufSize(hSd1), &bAttrs);

    if (hOutBuf == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create contiguous buffers\n");
        goto cleanup;
    }

    /* Prime the file loader */
    Loader_prime(hLoader, &hInBuf);

    while (1) {
        if (numFrame++ >= args->numFrames && args->numFrames >= 0) {
            printf("\n%d frames decoded, exiting\n", numFrame - 1);
            goto cleanup;
        }

        if (args->cache) {
            /*  
             *  To meet xDAIS DMA Rule 7, when input buffers are cached, we 
             *  must writeback the cache into physical memory.  Also, per DMA 
             *  Rule 7, we must invalidate the output buffer from
             *  cache before providing it to any xDAIS algorithm.
             */
            Memory_cacheWbInv(Buffer_getUserPtr(hInBuf),Buffer_getSize(hInBuf));
    
            /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
            Memory_cacheInv(Buffer_getUserPtr(hOutBuf),Buffer_getSize(hOutBuf));
        }
        
        /* Decode the speech buffer */
        if (Sdec1_process(hSd1, hInBuf, hOutBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to decode speech buffer\n");
            goto cleanup;
        }

        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
        }

        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (numFrame >= args->startFrame) {
                /* Write the decoded samples to the device driver */
                if (Sound_write(hSound, hOutBuf) < 0) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to write speech buffer\n");
                    goto cleanup;
                }
                printf("#");
            }
            else {
                printf("-");
            }
        }
        else {
            printf("%%");
        }

        fflush(stdout);

        /* Load a new frame from the file system */
        Loader_getFrame(hLoader, hInBuf);

        if (Buffer_getUserPtr(hInBuf) == NULL) {
            printf("\nLoader returned null, clip finished\n");
            break;
        }
    }

cleanup:
    /* Clean up the application */
    if (hLoader) {
        Loader_delete(hLoader);
    }

    if (hSd1) {
        Sdec1_delete(hSd1);
    }

    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hSound) {
        Sound_delete(hSound);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    printf("End of application.\n");

    if (ret == Dmai_EFAIL)
        return 1
    else
        return 0;
}
