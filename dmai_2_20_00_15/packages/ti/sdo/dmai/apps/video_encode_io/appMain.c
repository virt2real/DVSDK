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
 * This application encodes a raw yuv file using a codec implementing the 
 * VIDENC interface to an elementary stream video file. The format of the yuv 
 * file depends on the device, for dm6446 and dm355 it's 422 interleaved.
 */

#include <stdio.h>

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
#include <ti/sdo/dmai/ce/Venc.h>

#include "appMain.h"

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480

static Char vbufferIn[VBUFSIZE];
static Char vbufferOut[VBUFSIZE];

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

    printf("Read UYVY frame size %u (%ux%u) from file\n",
           (Uns)(dim.width * 2 * dim.height), (Uns)dim.width, (Uns)dim.height);

    Buffer_setNumBytesUsed(hBuf, dim.width * 2 * dim.height);

    return 0;
}

/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    VIDENC_Params           params      = Venc_Params_DEFAULT;
    VIDENC_DynamicParams    dynParams   = Venc_DynamicParams_DEFAULT;
    BufferGfx_Attrs         gfxAttrs    = BufferGfx_Attrs_DEFAULT;
    Buffer_Attrs            bAttrs      = Buffer_Attrs_DEFAULT;
    Time_Attrs              tAttrs      = Time_Attrs_DEFAULT;
    Venc_Handle             hVe         = NULL;
    FILE                   *outFile     = NULL;
    FILE                   *inFile      = NULL;
    Engine_Handle           hEngine     = NULL;
    Time_Handle             hTime       = NULL;
    Int                     numFrame    = 0;
    Buffer_Handle           hOutBuf     = NULL;
    Buffer_Handle           hInBuf      = NULL;
    ColorSpace_Type         colorSpace;
    UInt32                  time;

    printf("Starting application...\n");
    
    /* Initialize the codec engine run time */
    CERuntime_init();
    
    /* Initialize DMAI */
    Dmai_init();
    
    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Open input file */
    inFile = fopen(args->inFile, "rb");
    
    if (inFile == NULL) {
        printf("Failed to open input file %s\n", args->inFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(inFile, vbufferIn, _IOFBF, sizeof(vbufferIn)) != 0) {
        printf("Failed to setvbuf on input file descriptor\n");
        goto cleanup;   
    }   

    
    /* Open output file */
    outFile = fopen(args->outFile, "wb");

    if (outFile == NULL) {
        printf("Failed to open output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbufferOut, _IOFBF, sizeof(vbufferOut)) != 0) {
        printf("Failed to setvbuf on output file descriptor\n");
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

    /* Set up codec parameters depending on bit rate */
    if (args->bitRate < 0) {
        /* Variable bit rate */
        params.rateControlPreset = IVIDEO_NONE;

        /*
         * If variable bit rate use a bogus bit rate value (> 0)
         * since it will be ignored.
         */
        params.maxBitRate        = 2000000;
    }
    else {
        /* Constant bit rate */
        params.rateControlPreset = IVIDEO_LOW_DELAY;
        params.maxBitRate        = args->bitRate;
    }

    params.inputChromaFormat = XDM_YUV_422ILE;

    dynParams.targetBitRate = params.maxBitRate;
    dynParams.inputWidth = params.maxWidth;
    dynParams.inputHeight = params.maxHeight;
    
    /* Create the video encoder */
    hVe = Venc_create(hEngine, args->codecName, &params, &dynParams);

    if (hVe == NULL) {
        printf("Failed to create video encoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Only the UYVY colorspace is supported in this application */
    colorSpace = ColorSpace_UYVY;

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = bAttrs.memParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = bAttrs.memParams.flags 
            = Memory_CACHED;
    } 
    
    /* Calculate the buffer attributes */
    gfxAttrs.dim.width = args->width;
    gfxAttrs.dim.height = args->height;
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(args->width, colorSpace);
    gfxAttrs.colorSpace = colorSpace;

    /* Create input buffer */
    hInBuf = Buffer_create(Dmai_roundUp(Venc_getInBufSize(hVe), BUFSIZEALIGN),
                           BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hInBuf == NULL) {
        printf("Failed to allocate contiguous buffer\n");
        goto cleanup;
    }

    /* Create output buffer */
    hOutBuf = Buffer_create(Dmai_roundUp(Venc_getOutBufSize(hVe), BUFSIZEALIGN),
        &bAttrs);

    if (hOutBuf == NULL) {
        printf("Failed to create contiguous buffer\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames) {
        /* Read a yuv input frame */
        printf("Frame %d: ", numFrame);
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
    
                printf("Pre-process cache maintenance: %uus \n", (Uns) time);
            }
        }

        /* Encode the video buffer */
        if (Venc_process(hVe, hInBuf, hOutBuf) < 0) {
            printf("Failed to encode video buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get encode time\n");
                goto cleanup;
            }

            printf("[%d] Encode: %uus\n", numFrame, (Uns)time);
        }

        if (args->cache) {
            /* Writeback the outBuf. */
            Memory_cacheWb(Buffer_getUserPtr(hOutBuf), Buffer_getSize(hOutBuf));
    
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Post-process cache write back: %uus \n", (Uns) time);
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
    /* Clean up the application */
    if (hOutBuf) {
        Buffer_delete(hOutBuf);
    }

    if (hInBuf) {
        Buffer_delete(hInBuf);
    }

    if (hVe) {
        Venc_delete(hVe);
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

    printf("End of application.\n");
    
    return;
}
