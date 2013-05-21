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
 * This applications encodes from a sound device driver using a specified
 * XDM audio codec to an elementary stream.
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Sound.h>
#include <ti/sdo/dmai/ce/Aenc1.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/******************************************************************************
 * main
 ******************************************************************************/
Int appMain(Args * args)
{
    Sound_Attrs             sAttrs      = Sound_Attrs_STEREO_DEFAULT;
    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    AUDENC1_Params          params      = Aenc1_Params_DEFAULT;
    AUDENC1_DynamicParams   dynParams   = Aenc1_DynamicParams_DEFAULT;
    Aenc1_Handle            hAe1        = NULL;
    Engine_Handle           hEngine     = NULL;
    Buffer_Handle           hOutBuf     = NULL;
    Buffer_Handle           hInBuf      = NULL;
    Sound_Handle            hSound      = NULL;
    FILE                   *outFile     = NULL;
    Int                     numFrame    = 0;
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

    /* Open the output file */
    outFile = fopen(args->outFile, "wb");

    if (outFile == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Create device driver instance */
    sAttrs.sampleRate = args->maxSampleRate;
    sAttrs.mode = Sound_Mode_INPUT;
    if (device == Cpu_Device_OMAPL137) {
        sAttrs.soundStd = Sound_Std_ALSA;
    }

    sAttrs.soundInput = args->soundInput;
    hSound = Sound_create(&sAttrs);

    if (hSound == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create audio device\n");
        goto cleanup;
    }

    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }

    params.sampleRate = dynParams.sampleRate = args->maxSampleRate;
    params.bitRate = dynParams.bitRate = args->maxBitrate;

    /* Create the AUDENC1 based audio encoder */
    hAe1 = Aenc1_create(hEngine, args->codecName, &params, &dynParams);

    if (hAe1 == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create audio encoder\n");
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        bAttrs.memParams.flags = Memory_CACHED;
    } 
    
    /* Create an output buffer for encoded data */
    hOutBuf = Buffer_create(
        Dmai_roundUp(Aenc1_getOutBufSize(hAe1), BUFSIZEALIGN), &bAttrs);

    if (hOutBuf == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create contiguous buffer\n");
        goto cleanup;
    }

    /* Create an input buffer for pcm data */
    hInBuf = Buffer_create(Dmai_roundUp(Aenc1_getInBufSize(hAe1), BUFSIZEALIGN),
        &bAttrs);

    if (hInBuf == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create contiguous buffer\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames) {
        /* Read samples from the Sound device */
        if (Sound_read(hSound, hInBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to write audio buffer\n");
            goto cleanup;
        }

        if (args->cache) {
            /*
             *  To meet xDAIS DMA Rule 7, when input buffers are cached, we
             *  must writeback the cache into physical memory.  Also, per DMA
             *  Rule 7, we must invalidate the output buffer from
             *  cache before providing it to any xDAIS algorithm.
             */
            Memory_cacheWbInv(Buffer_getUserPtr(hInBuf),
                              Buffer_getSize(hInBuf));

            /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
            Memory_cacheInv(Buffer_getUserPtr(hOutBuf),
                            Buffer_getSize(hOutBuf));
        }

        /* Encode the audio buffer */
        if (Aenc1_process(hAe1, hInBuf, hOutBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to encode audio buffer\n");
            goto cleanup;
        }

        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
        }

        /* Write the encoded frame to the file system */
        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (numFrame >= args->startFrame) {
                if (fwrite(Buffer_getUserPtr(hOutBuf),
                           Buffer_getNumBytesUsed(hOutBuf), 1, outFile) != 1) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr,"Failed to write encoded video data to file\n");
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
    }

    printf("\n%d frames encoded, exiting\n", numFrame - 1);

cleanup:
    /* Clean up the application */
    if (hAe1) {
        Aenc1_delete(hAe1);
    }

    if (hInBuf) {
        Buffer_delete(hInBuf);
    }

    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (hSound) {
        Sound_delete(hSound);
    }

    if (outFile) {
        fclose(outFile);
    }

    printf("End of application.\n");

    if (ret == Dmai_EFAIL)
        return 1;
    else
        return 0;
}
