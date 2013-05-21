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
 * This applications decodes an elementary stream audio file using a specified
 * XDM audio codec to a raw pcm file.
 */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Sound.h>
#include <ti/sdo/dmai/Loader.h>
#include <ti/sdo/dmai/ce/Adec1.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{
    Sound_Attrs             sAttrs      = Sound_Attrs_STEREO_DEFAULT;
    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    Loader_Attrs            lAttrs      = Loader_Attrs_DEFAULT;
    AUDDEC1_Params          params      = Adec1_Params_DEFAULT;
    AUDDEC1_DynamicParams   dynParams   = Adec1_DynamicParams_DEFAULT;
    Adec1_Handle            hAd1        = NULL;
    Sound_Handle            hSound      = NULL;
    Loader_Handle           hLoader     = NULL;
    Engine_Handle           hEngine     = NULL;
    Buffer_Handle           hOutBuf     = NULL;
    Int                     numFrame    = 0;
    Buffer_Handle           hInBuf;
    Cpu_Device              device;
    Int                     ret         = Dmai_EOK;

    /* Initialize the codec engine run time */
    CERuntime_init();

    /* Initialize DMAI */
    Dmai_init();

    if (Cpu_getDevice(NULL, &device) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to determine target board\n");
        goto cleanup;
    }
    
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr, "Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }

    if ((device == Cpu_Device_DM365) || (device == Cpu_Device_DM368)) {
        params.dataEndianness = XDM_LE_16;
    }

    /* Create the AUDDEC1 based audio decoder */
    hAd1 = Adec1_create(hEngine, args->codecName, &params, &dynParams);

    if (hAd1 == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create audio decoder\n");
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    bAttrs.memParams.align = lAttrs.mParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */  
    if (args->cache) {
        bAttrs.memParams.flags = lAttrs.mParams.flags = Memory_CACHED;
    } 
    
    /* Ask the codec how much input data it needs */
    lAttrs.readSize = Adec1_getInBufSize(hAd1);

    /* Make the total ring buffer larger */
    lAttrs.readBufSize = Dmai_roundUp(lAttrs.readSize * 10, BUFSIZEALIGN);

    /* Create the file loader */
    hLoader = Loader_create(args->inFile, &lAttrs);

    if (hLoader == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create loader\n");
        goto cleanup;
    }

    /* Create an output buffer for decoded data */
    hOutBuf = Buffer_create(
        Dmai_roundUp(Adec1_getOutBufSize(hAd1), BUFSIZEALIGN), &bAttrs);

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

        /* Decode the audio buffer */
        ret = Adec1_process(hAd1, hInBuf, hOutBuf);

        if ((ret == Dmai_EFAIL)||
            (ret == Dmai_EBITERROR && Buffer_getNumBytesUsed(hInBuf) == 0)) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to decode audio buffer\n");
            goto cleanup;
        }

        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
        }

        if (Adec1_getSampleRate(hAd1)&&!hSound) {
            /* Create device driver instance when sample rate is known */
            sAttrs.sampleRate = Adec1_getSampleRate(hAd1);
            sAttrs.mode = Sound_Mode_OUTPUT;
            sAttrs.soundStd = args->soundStd;

            hSound = Sound_create(&sAttrs);

            if (hSound == NULL) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to create audio device\n");
                goto cleanup;
            }

            printf("Sample rate %d detected\n", Adec1_getSampleRate(hAd1));
        }

        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (numFrame >= args->startFrame) {
                /* Write the decoded samples to the device driver */
                if (Sound_write(hSound, hOutBuf) < 0) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to write audio buffer\n");
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

    if (hAd1) {
        Adec1_delete(hAd1);
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
        return 1;
    else
        return 0;
}
