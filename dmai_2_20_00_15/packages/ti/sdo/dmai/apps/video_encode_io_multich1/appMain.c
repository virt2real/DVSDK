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
 * This application encodes multiple channels of video data from files, one 
 * channel per application thread, and stores the encoded files to the
 * file system.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <limits.h>
#include <pthread.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Ccv.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/Framecopy.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ce/Venc1.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

#define THREAD_FAILURE          (Void*)-1
#define THREAD_SUCCESS          (Void*)0

#define intStrSizeDec(tp)       (((sizeof(tp) * CHAR_BIT) >> 1)+2)

/******************************************************************************
 * readFrameUYVY
******************************************************************************/
Int readFrameUYVY(Buffer_Handle hBuf, FILE *outFile)
{
    Int8 *ptr = Buffer_getUserPtr(hBuf);
    Int y;

    BufferGfx_Dimensions dim;

    BufferGfx_getDimensions(hBuf, &dim);

    for (y = 0; y < dim.height; y++) {
        if (fread(ptr, dim.width * 2, 1, outFile) != 1) {
            printf("Failed to read data from file\n");
            return -1;
        }

        ptr += dim.lineLength;
    }

    printf("Read UYVY frame size %d (%dx%d) from file\n",
           (Int) (dim.width * 2 * dim.height),
           (Int) dim.width, (Int) dim.height);

    return 0;
}


/******************************************************************************
 * filenameInsertId   
 *    Converts "filename.ext" into "filename<id>.ext"
 *    The returned string must be freed by the caller.
 ******************************************************************************/
Char *filenameInsertId(Char *name, Int id)
{
    Char *baseBuf;
    Char *extBuf;
    Char *idBuf;
    Char *result;
    Bool  hasExt;

    /* Make a copy of the entire filename into baseBuf */
    baseBuf = (Char*)malloc(strlen(name)+1);
    strcpy(baseBuf, name);

    /* If an extension exists, set extBuf to the extension and truncate it   */
    /* from the end of baseBuf                                               */
    extBuf = rindex(baseBuf, '.');
    if ((hasExt = (extBuf != NULL))) {
       *extBuf = '\0';
       extBuf++;
    }

    /* Convert an id number into a string, and store the result in idBuf     */
    idBuf = (Char*)malloc(intStrSizeDec(Int)+1);
    sprintf(idBuf, "%d", id);

    /* Allocate space for the result filename                                */
    result = (Char*)malloc(strlen(baseBuf) + strlen(idBuf) + 1 +
                           strlen(extBuf) + 1);

    /* Build the result filename, and return it                              */
    strcpy(result, baseBuf);
    strcat(result, idBuf);

    if (hasExt) {
        strcat(result, ".");
        strcat(result, extBuf);
    }

    free(baseBuf);
    free(idBuf);
    return result;
}


/******************************************************************************
 * main
 ******************************************************************************/
Void *encodeThrFxn(Void *thrArgs)
{
    Args                  *args           = (Args*)thrArgs;
    VIDENC1_Params         params         = Venc1_Params_DEFAULT;
    VIDENC1_DynamicParams  dynParams      = Venc1_DynamicParams_DEFAULT;
    BufferGfx_Attrs        gfxAttrs       = BufferGfx_Attrs_DEFAULT;
    Time_Attrs             tAttrs         = Time_Attrs_DEFAULT;
    Venc1_Handle           hVe1           = NULL;
    FILE                  *outFile        = NULL;
    FILE                  *inFile         = NULL;
    Engine_Handle          hEngine        = NULL;
    Time_Handle            hTime          = NULL;
    Buffer_Handle          hOutBuf        = NULL;
    Buffer_Handle          hInBuf         = NULL;
    Int                    numFrame       = 0;
    Char*                  inFilenameThr  = NULL;
    Char*                  outFilenameThr = NULL;
    Int                    inBufSize, outBufSize;
    ColorSpace_Type        colorSpace;
    UInt32                 time;

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Determine full file name and open the input file */
    inFilenameThr = filenameInsertId(args->inFile, args->thrId);
    inFile = fopen(inFilenameThr, "rb");
    
    if (inFile == NULL) {
        printf("Failed to open input file %s\n", args->inFile);
        goto cleanup;
    }

    /* Determine full file name and open the output file */
    outFilenameThr = filenameInsertId(args->outFile, args->thrId);
    outFile = fopen(outFilenameThr, "wb");

    if (outFile == NULL) {
        printf("Failed to open output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        printf("Failed to open codec engine: %s\n", args->engineName);
        goto cleanup;
    }

    params.maxWidth = args->width;
    params.maxHeight = args->height;
        
    params.rateControlPreset = args->bitRate < 0 ? IVIDEO_NONE :
                                                   IVIDEO_LOW_DELAY;
    params.maxBitRate = args->bitRate < 0 ? 2000000 : args->bitRate;
    params.inputChromaFormat = XDM_YUV_422ILE;
    params.reconChromaFormat = XDM_YUV_420P;

    dynParams.targetBitRate = params.maxBitRate;
    dynParams.inputWidth = params.maxWidth;
    dynParams.inputHeight = params.maxHeight;

    /* Create the video encoder */
    hVe1 = Venc1_create(hEngine, args->codecName, &params, &dynParams);

    if (hVe1 == NULL) {
        printf("Failed to create video encoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Ask the codec which buffer sizes are required */
    outBufSize = Venc1_getOutBufSize(hVe1);
    inBufSize = Venc1_getInBufSize(hVe1);

    colorSpace = ColorSpace_UYVY;

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = Memory_CACHED;
    } 
    
    /* Calculate the buffer attributes */
    gfxAttrs.dim.width = args->width;
    gfxAttrs.dim.height = args->height;
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(args->width, colorSpace);
    gfxAttrs.colorSpace = colorSpace;

    if (inBufSize < 0) {
        printf("Failed to calculate buffer attributes\n");
        goto cleanup;
    }

    /* Create input buffer for raw video data */
    hInBuf = Buffer_create(Dmai_roundUp(inBufSize, BUFSIZEALIGN), 
        (Buffer_Attrs *) &gfxAttrs);

    if (hInBuf == NULL) {
        printf("Failed to allocate contiguous buffer\n");
        goto cleanup;
    }

    /* Create output buffer for encoded video data */
    hOutBuf = Buffer_create(Dmai_roundUp(outBufSize, BUFSIZEALIGN), 
        (Buffer_Attrs *) &gfxAttrs);

    if (hOutBuf == NULL) {
        printf("Failed to create contiguous buffer\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames) {
        /* Get a new input frame */
        if (readFrameUYVY(hInBuf, inFile) < 0) {
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                printf("Failed to reset timer\n");
                goto cleanup;
            }
        }

        if (args->cache) {
            /*  
             *  To meet xDAIS DMA Rule 7, when input buffers are cached, we 
             *  must writeback the cache into physical memory.  Also, per DMA 
             *  Rule 7, we must invalidate the output buffer from
             *  cache before providing it to any xDAIS algorithm.
             */
            Memory_cacheWbInv(Buffer_getUserPtr(hInBuf), Buffer_getSize(hInBuf));
    
            /* Per DMA Rule 7, our output buffer cache lines must be cleaned */
            Memory_cacheInv(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
    
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Cache invalidate: %uus ", (Uns) time);
            }
        }
        
        /* Decode the video buffer */
        if (Venc1_process(hVe1, hInBuf, hOutBuf) < 0) {
            printf("Failed to encode video buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get encode time\n");
                goto cleanup;
            }

            printf("[%d] Encode: %uus\n", numFrame, (Uns) time);
        }


        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
    
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Cache write back: %uus ", (Uns) time);
            }
        }
        
        /* Write the encoded frame to the file system */
        if (Buffer_getNumBytesUsed(hOutBuf)) {
            if (fwrite(Buffer_getUserPtr(hOutBuf),
                       Buffer_getNumBytesUsed(hOutBuf), 1, outFile) != 1) {
                printf("Failed to write encoded video data to file\n");
                goto cleanup;
            }
        }
        
        if (args->benchmark) {
            if (Time_total(hTime, &time) < 0) {
                printf("Failed to get timer total\n");
                goto cleanup;
            }

            printf("Total: %uus\n", (unsigned int)time);
        }
    }

cleanup:
    /* Clean up the thread */
    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hInBuf) {
        Buffer_delete(hInBuf);
    }

    if (hVe1) {
        Venc1_delete(hVe1);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (inFile) {
        fclose(inFile);
    }
   
    if (outFile) {
        fclose(outFile);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (inFilenameThr) {
        free(inFilenameThr);
    }

    if (outFilenameThr) {
        free(outFilenameThr);
    }

    return 0;
}


/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    Int        status = EXIT_SUCCESS;
    pthread_t *threads;
    Args      *thrArgs;
    Void      *ret;
    Int        thrId;

    /* Initialize the codec engine run time */
    CERuntime_init();
    
    /* Initialize DMAI */
    Dmai_init();
    
    /* Allocate space for video thread handles */
    threads = calloc(args->numThreads, sizeof(pthread_t));
    thrArgs = calloc(args->numThreads, sizeof(Args));

    if (threads == NULL || thrArgs == NULL) {
        printf("Failed to allocate thread information records\n");
        goto cleanup;
    }

    /* Create a thread for each channel */
    for (thrId = 0; thrId < args->numThreads; thrId++) {

        thrArgs[thrId]       = *args;
        thrArgs[thrId].thrId = thrId;

        if (pthread_create(&threads[thrId], NULL, encodeThrFxn,
                            &thrArgs[thrId])) {
            printf("Failed to create video thread %d\n", thrId);
            status = EXIT_FAILURE;
            goto cleanup;
        }
    }

    /* Wait for all threads to finish */
    for (thrId = 0; thrId < args->numThreads; thrId++) {
        args->thrId = thrId;

        if (pthread_join(threads[thrId], &ret) == 0) {
            if (ret == THREAD_FAILURE) {
                status = EXIT_FAILURE;
            }
        }
    }

cleanup:
    /* Clean up the application and exit */
    free(threads);
    free(thrArgs);

    exit(status);
}
