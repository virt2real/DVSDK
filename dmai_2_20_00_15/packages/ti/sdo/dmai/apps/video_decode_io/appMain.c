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
 * This application decodes an elementary stream video file using a specified
 * codec to a raw yuv file using an xDM 0.9 codec. The format of the yuv file
 * depends on the device, for dm6446 amd dm355 it's 422 interleaved.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Loader.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Framecopy.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Vdec.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "appMain.h"

#define NUM_BUFS                2

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480

static Char vbuffer[VBUFSIZE];

/******************************************************************************
 * writeFrameUYVY
******************************************************************************/
static Int writeFrameUYVY(Buffer_Handle hBuf, FILE *outFile)
{
    Int8 *ptr = Buffer_getUserPtr(hBuf);
    Int y;

    BufferGfx_Dimensions dim;

    BufferGfx_getDimensions(hBuf, &dim);

    for (y = 0; y < dim.height; y++) {
        if (fwrite(ptr, dim.width * 2, 1, outFile) != 1) {
            printf("Failed to write data to disk\n");
            return -1;
        }

        ptr += dim.lineLength;
    }

    printf("Wrote UYVY frame size %d (%dx%d) to disk\n",
           (Int) (dim.width * 2 * dim.height),
           (Int) dim.width, (Int) dim.height);

    return 0;
}

/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    VIDDEC_Params           params       = Vdec_Params_DEFAULT;
    VIDDEC_DynamicParams    dynParams    = Vdec_DynamicParams_DEFAULT;
    Loader_Attrs            lAttrs       = Loader_Attrs_DEFAULT;
    BufferGfx_Attrs         gfxAttrs     = BufferGfx_Attrs_DEFAULT;
    Vdec_Handle             hVd          = NULL;
    Time_Attrs              tAttrs       = Time_Attrs_DEFAULT;
    Loader_Handle           hLoader      = NULL;
    Engine_Handle           hEngine      = NULL;
    BufTab_Handle           hBufTab      = NULL;
    Time_Handle             hTime        = NULL;
    Int                     ret          = Dmai_EOK;
    Int                     numFrame     = 0;
    FILE                   *outFile      = NULL;
    Buffer_Handle           hInBuf       = NULL;
    Buffer_Handle           hDstBuf      = NULL;
    Buffer_Handle           hOutBuf;
    UInt32                  time;
    
    printf("Starting application...\n");
    
    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Initialize the codec engine run time */
    CERuntime_init();

    /* Initialize DMAI */
    Dmai_init();
     
    /* Open output file */
    outFile = fopen(args->outFile, "wb");
    
    if (outFile == NULL) {
        printf("Failed to create output file %s\n", args->outFile);
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbuffer, _IOFBF, sizeof(vbuffer)) != 0) {
        printf("Failed to setvbuf on file descriptor\n");
        goto cleanup;   
    }
    
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        printf("Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }

    /* Create the XDM 0.9 based video decoder */
    params.forceChromaFormat    = XDM_YUV_422ILE;
    params.maxWidth             = VideoStd_D1_WIDTH;
    params.maxHeight            = VideoStd_D1_PAL_HEIGHT;

    hVd = Vdec_create(hEngine, args->codecName, &params, &dynParams);

    if (hVd == NULL) {
        printf("Failed to create video decoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = lAttrs.mParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = lAttrs.mParams.flags = Memory_CACHED;
    } 
    
    gfxAttrs.colorSpace     = ColorSpace_UYVY;
    gfxAttrs.dim.width      = params.maxWidth;
    gfxAttrs.dim.height     = params.maxHeight;
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(params.maxWidth,
                                                       gfxAttrs.colorSpace);

    hBufTab = BufTab_create(NUM_BUFS, 
        Dmai_roundUp(Vdec_getOutBufSize(hVd), BUFSIZEALIGN),
        BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hBufTab == NULL) {
        printf("Failed to allocate contiguous buffers\n");
        goto cleanup;
    }

    /* Set output buffer table */
    Vdec_setBufTab(hVd, hBufTab);
 
    /* Ask the codec how much input data it needs */
    lAttrs.readSize = Vdec_getInBufSize(hVd); 

    /* Make the total ring buffer larger */
    lAttrs.readBufSize = Dmai_roundUp(lAttrs.readSize * 2, BUFSIZEALIGN); 

    /* Increase the stdio buffer size for loader for better RTDX performance */
    lAttrs.vBufSize = VBUFSIZE;
    
    /* Create the file loader */
    hLoader = Loader_create(args->inFile, &lAttrs);

    if (hLoader == NULL) {
        printf("Failed to create loader\n");
        goto cleanup;
    }

    /* Prime the file loader */
    Loader_prime(hLoader, &hInBuf);

    printf("Loader created and primed, entering main loop..\n");

    while (numFrame++ < args->numFrames) {

        if (ret != Dmai_EFIRSTFIELD && ret != Dmai_EBITERROR) {
            /* Get a free buffer from the BufTab */
            hDstBuf = BufTab_getFreeBuf(hBufTab);

            if (hDstBuf == NULL) {
                printf("Failed to get a free contiguous buffer from BufTab\n");
                BufTab_print(hBufTab);
                goto cleanup;
            }
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
            Memory_cacheInv(Buffer_getUserPtr(hDstBuf), Buffer_getSize(hDstBuf));
    
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Pre-process cache maintenance: %uus \n", (Uns) time);
            }
        }
        
        /* Decode the video buffer */
        ret = Vdec_process(hVd, hInBuf, hDstBuf);
    
        if (ret < 0) {
            printf("Failed to decode video buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Frame %d - Decode: %uus \n", numFrame, (unsigned int)time);
        }

        printf("Loaded Frame %d: frame size %d\n", numFrame,
               (Int)Buffer_getNumBytesUsed(hInBuf));

        /* Do we have a valid frame to be displayed? */
        if (ret != Dmai_EPRIME &&
            ret != Dmai_EFIRSTFIELD &&
            ret != Dmai_EBITERROR) {
            
            /* Get display buffer */
            hOutBuf = Vdec_getDisplayBuf(hVd);

            if (args->cache) {
                /* Writeback the outBuf. */
                Memory_cacheWb(Buffer_getUserPtr(hOutBuf), 
                    Buffer_getSize(hOutBuf));
        
                if (args->benchmark) {
                    if (Time_delta(hTime, &time) < 0) {
                        printf("Failed to get timer delta\n");
                        goto cleanup;
                    }
        
                    printf("Post-process cache write back: %uus \n", (Uns) time);
                }
            }
                          
            if (numFrame >= args->startFrame) {
                printf("Display Frame %d: ", numFrame);
                                         
                if (writeFrameUYVY(hOutBuf, outFile) < 0) {
                    goto cleanup;
                }
            }
            
            if (args->benchmark) {
                if (Time_delta(hTime, &time) < 0) {
                    printf("Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Time - Writing frame: %uus ", (unsigned int)time);
            }
    
            BufTab_freeBuf(hOutBuf);
        }

        /* Load a new frame from the file system */
        Loader_getFrame(hLoader, hInBuf);

        if (Buffer_getUserPtr(hInBuf) == NULL) {
            printf("Loader returned null, clip finished\n");
            break;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Loader: %uus ", (unsigned int)time);
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
    if (hLoader) {
        Loader_delete(hLoader);
    }

    if (hVd) {
        Vdec_delete(hVd);
    }

    if (hBufTab) {
        BufTab_delete(hBufTab);
    }

    if (hEngine) {
        Engine_close(hEngine);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (outFile) {
        fclose(outFile);
    }
    
    printf("End of application.\n");
    
    return;
}
