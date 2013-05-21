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
 * This applications decodes an elementary stream video file using a specified
 * codec to a raw yuv file. The format of the yuv file depends on the device,
 * for dm6467 it's 420 planar while on dm355 it's 422 interleaved.
 */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/CERuntime.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Loader.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/ce/Vdec2.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "appMain.h"

/* Temporary compilation error fix for OMAP 3530. 
   Remove the definition when it uses CE 2.22 or later */
#ifdef Dmai_Device_omap3530
#define XDM_YUV_420SP 9 
#endif

/* Align buffers to this cache line size (in bytes)*/
#define BUFSIZEALIGN            128

/* vbuf size that has been selected based on size/performance tradeoff */
#define VBUFSIZE                20480
 
static Char vbuffer[VBUFSIZE];

/* These definitions missing in some OS build environments (eg: WinCE) */
#ifndef _IOFBF
    #define _IOFBF  0
#endif  /* _IOFBF */
#ifndef _IOLBF
    #define _IOLBF  1
#endif  /* _IOLBF */
#ifndef _IONBF
    #define _IONBF  2
#endif  /* _IONBF */

/******************************************************************************
 * resizeBufTab
******************************************************************************/
Int resizeBufTab(Vdec2_Handle hVd2, Int displayBufs)
{
    BufTab_Handle hBufTab = Vdec2_getBufTab(hVd2);
    Int numBufs, numCodecBuffers, numExpBufs;
    Buffer_Handle hBuf;
    Int32 frameSize;

    /* How many buffers can the codec keep at one time? */
    numCodecBuffers = Vdec2_getMinOutBufs(hVd2);

    if (numCodecBuffers < 0) {
        fprintf(stderr, "Failed to get buffer requirements\n");
        return -1;
    }

    /*
     * Total number of frames needed are the number of buffers the codec
     * can keep at any time, plus the number of frames in the display pipe.
     */
    numBufs = numCodecBuffers + displayBufs;

    /* Get the size of output buffers needed from codec */
    frameSize = Vdec2_getOutBufSize(hVd2);

    /*
     * Get the first buffer of the BufTab to determine buffer characteristics.
     * All buffers in a BufTab share the same characteristics.
     */
    hBuf = BufTab_getBuf(hBufTab, 0);

    /* Do we need to resize the BufTab? */
    if (numBufs > BufTab_getNumBufs(hBufTab) ||
        frameSize < Buffer_getSize(hBuf)) {

        /* Should we break the current buffers in to many smaller buffers? */
        if (frameSize < Buffer_getSize(hBuf)) {

            /* First undo any previous chunking done */
            BufTab_collapse(Vdec2_getBufTab(hVd2));

            /*
             * Chunk the larger buffers of the BufTab in to smaller buffers
             * to accomodate the codec requirements.
             */
            numExpBufs = BufTab_chunk(hBufTab, numBufs, frameSize);

            if (numExpBufs < 0) {
                fprintf(stderr, "Failed to chunk %d bufs size %d to %d bufsize %d\n",
                    BufTab_getNumBufs(hBufTab), (Int)Buffer_getSize(hBuf),
                    numBufs, (Int)frameSize);
                return -1;
            }

            /*
             * Did the current BufTab fit the chunked buffers,
             * or do we need to expand the BufTab (numExpBufs > 0)?
             */
            if (BufTab_expand(hBufTab, numExpBufs) < 0) {
                fprintf(stderr, "Failed to expand BufTab with %d buffers\n",
                       numExpBufs);
                return -1;
            }
        }
        else {
            /* Just expand the BufTab with more buffers */
            if (BufTab_expand(hBufTab, numBufs - BufTab_getNumBufs(hBufTab)) < 0) {
                fprintf(stderr,"Failed to expand BufTab with %d buffers\n",
                       numCodecBuffers);
                return -1;
            }
        }
    }

    return numBufs;
}

/******************************************************************************
 * writeFrame420P
******************************************************************************/
Int writeFrame420P(Buffer_Handle hBuf, FILE *outFile, Cpu_Device device)
{
    Int8 *yPtr, *cbcrPtr;
    UInt32 offset;
    Int y, x;

    BufferGfx_Dimensions dim;
    BufferGfx_getDimensions(hBuf, &dim);

    offset = dim.y * dim.lineLength + dim.x;

    /* Write Y plane */
    yPtr = Buffer_getUserPtr(hBuf) + offset;
    for (y = 0; y < dim.height; y++) {
        if (fwrite(yPtr, dim.width, 1, outFile) != 1) {
            fprintf(stderr, "Failed to write data to disk\n");
            return -1;
        }

        yPtr += dim.lineLength;
    }

    if ((device == Cpu_Device_DM365) || (device == Cpu_Device_DM368)) {
        offset = dim.y * dim.lineLength / 2 + dim.x;
    } else {
        /* *Default* Assume DM6467 behavior */
        offset = dim.y * dim.lineLength + dim.x;
    }

    /* Separate Cb from CbCr interleaved and save Cb plane */
    cbcrPtr = Buffer_getUserPtr(hBuf) + offset + Buffer_getSize(hBuf) * 2 / 3;
    for (y = 0; y < dim.height / 2; y++) {
      for (x = 0; x < dim.width; x += 2) {
        if (fwrite(&cbcrPtr[x], 1, 1, outFile) != 1) {
            fprintf(stderr, "Failed to write data to disk\n");
            return -1;
        }
      }
      cbcrPtr += dim.lineLength;
    }

    /* Separate Cr from CbCr interleaved and save Cr plane */
    cbcrPtr = Buffer_getUserPtr(hBuf) + offset + Buffer_getSize(hBuf) * 2 / 3;
    for (y = 0; y < dim.height / 2; y++) {
      for (x = 1; x < dim.width; x += 2) {
        if (fwrite(&cbcrPtr[x], 1, 1, outFile) != 1) {
            fprintf(stderr, "Failed to write data to disk\n");
            return -1;
        }
      }
      cbcrPtr += dim.lineLength;
    }

    printf("Wrote 420P frame size %d (%dx%d) to disk\n",
           (Int) (dim.width * 3 / 2 * dim.height),
           (Int) dim.width, (Int) dim.height);

    return 0;
}

/******************************************************************************
 * writeFrame420SP
******************************************************************************/
Int writeFrame420SP(Buffer_Handle hBuf, FILE *outFile, Cpu_Device device)
{
    Int8 *yPtr, *cbcrPtr;
    UInt32 offset;
    Int y;

    BufferGfx_Dimensions dim;
    BufferGfx_getDimensions(hBuf, &dim);

    offset = dim.y * dim.lineLength + dim.x;

    /* Write Y plane */
    yPtr = Buffer_getUserPtr(hBuf) + offset;
    for (y = 0; y < dim.height; y++) {
        if (fwrite(yPtr, dim.width, 1, outFile) != 1) {
            fprintf(stderr, "Failed to write data to disk\n");
            return -1;
        }

        yPtr += dim.lineLength;
    }

    if ((device == Cpu_Device_DM365) || (device == Cpu_Device_DM368)) {
        offset = dim.y * dim.lineLength / 2 + dim.x;
    } else {
        /* *Default* Assume DM6467 behavior */
        offset = dim.y * dim.lineLength + dim.x;
    }

    /* Separate Cb from CbCr interleaved */
    cbcrPtr = Buffer_getUserPtr(hBuf) + offset + Buffer_getSize(hBuf) * 2 / 3;
    for (y = 0; y < dim.height / 2; y++) {
        if (fwrite(cbcrPtr, dim.width, 1, outFile) != 1) {
            fprintf(stderr, "Failed to write data to disk\n");
            return -1;
        }
        cbcrPtr += dim.lineLength;
    }

    printf("Wrote 420SP frame size %d (%dx%d) to disk\n",
           (Int) (dim.width * 3 / 2 * dim.height),
           (Int) dim.width, (Int) dim.height);

    return 0;
}

/******************************************************************************
 * writeFrameUYVY
******************************************************************************/
Int writeFrameUYVY(Buffer_Handle hBuf, FILE *outFile)
{
    Int8 *ptr;
    UInt32 offset;
    Int y;

    BufferGfx_Dimensions dim;
    BufferGfx_getDimensions(hBuf, &dim);

    offset = dim.y * dim.lineLength + dim.x * 2;
    ptr = Buffer_getUserPtr(hBuf) + offset;

    for (y = 0; y < dim.height; y++) {
        if (fwrite(ptr, dim.width * 2, 1, outFile) != 1) {
            fprintf(stderr, "Failed to write data to disk\n");
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
Int appMain(Args * args)
{
    VIDDEC2_Params          params       = Vdec2_Params_DEFAULT;
    VIDDEC2_DynamicParams   dynParams    = Vdec2_DynamicParams_DEFAULT;
    Loader_Attrs            lAttrs       = Loader_Attrs_DEFAULT;
    BufferGfx_Attrs         gfxAttrs     = BufferGfx_Attrs_DEFAULT;
    Time_Attrs              tAttrs       = Time_Attrs_DEFAULT;
    Vdec2_Handle            hVd2         = NULL;
    Loader_Handle           hLoader      = NULL;
    Engine_Handle           hEngine      = NULL;
    BufTab_Handle           hBufTab      = NULL;
    Buffer_Handle           hDstBuf      = NULL;
    Time_Handle             hTime        = NULL;
    FILE                   *outFile      = NULL;
    Bool                    flushed      = FALSE;
    Int                     ret          = Dmai_EOK;
    Int                     numFrame     = 1;
    Int                     numFrameDisp = 1;
    Buffer_Handle           hInBuf, hOutBuf, hFreeBuf;
    ColorSpace_Type         colorSpace;
    Cpu_Device              device;
    Int                     numBufs;
    UInt32                  time;
    BufferGfx_Dimensions    dim;
    Bool                    vc1Offset   = FALSE;
    Bool                    mpeg4Offset = FALSE;

    printf("Starting application...\n");
    
    /* Determine which device the application is running on */
    if (Cpu_getDevice(NULL, &device) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr, "Failed to determine target board\n");
        goto cleanup;
    }

    /* Initialize platform-specific settings */
    if ((device == Cpu_Device_DM6467) || 
        (device == Cpu_Device_DM365)  ||
        (device == Cpu_Device_DM368)) {
        colorSpace = ColorSpace_YUV420PSEMI;
        numBufs    = 5;
    }
    else {
        colorSpace = ColorSpace_UYVY;
        numBufs    = 2;
    }

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create Time object\n");
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
        fprintf(stderr,"Failed to create output file %s\n", args->outFile);
        ret = Dmai_EFAIL;
        goto cleanup;
    }

    /* Using a larger vbuf to enhance performance of file i/o */
    if (setvbuf(outFile, vbuffer, _IOFBF, sizeof(vbuffer)) != 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to setvbuf on file descriptor\n");
        goto cleanup;   
    }
    
    /* Open the codec engine */
    hEngine = Engine_open(args->engineName, NULL, NULL);

    if (hEngine == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr, "Failed to open codec engine %s\n", args->engineName);
        goto cleanup;
    }

    /* Set up codec parameters depending on device */
    if ((device == Cpu_Device_DM6467) ||
        (device == Cpu_Device_DM365)  ||
        (device == Cpu_Device_DM368)) {
        params.forceChromaFormat    = XDM_YUV_420SP;
        params.maxWidth             = VideoStd_1080I_WIDTH;
        params.maxHeight            = VideoStd_1080I_HEIGHT + 8;
    }
    else if (device == Cpu_Device_DM3730) {
        params.forceChromaFormat    = XDM_YUV_422ILE;
        params.maxWidth = VideoStd_720P_WIDTH;
        params.maxHeight = VideoStd_720P_HEIGHT;
    }
    else {
        params.forceChromaFormat    = XDM_YUV_422ILE;
        params.maxWidth             = VideoStd_D1_WIDTH;
        params.maxHeight            = VideoStd_D1_PAL_HEIGHT;
    }

    if(device == Cpu_Device_DM6467) {
        if (!strcmp(args->codecName, "mpeg4dec")) {
            params.maxWidth  = VideoStd_576P_WIDTH;
            params.maxHeight = VideoStd_576P_HEIGHT;
            mpeg4Offset      = TRUE;
        }
    }

    if ((device == Cpu_Device_DM365) || (device == Cpu_Device_DM368)) {
        if (!strcmp(args->codecName, "vc1dec")) {
            vc1Offset = TRUE;
        }
    }

    /* Create the XDM 1.2 based video decoder */
    hVd2 = Vdec2_create(hEngine, args->codecName, &params, &dynParams);

    if (hVd2 == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create video decoder: %s\n", args->codecName);
        goto cleanup;
    }

    /* Align buffers to cache line boundary */    
    gfxAttrs.bAttrs.memParams.align = lAttrs.mParams.align = BUFSIZEALIGN; 
    
    /* Use cached buffers if requested */    
    if (args->cache) {
        gfxAttrs.bAttrs.memParams.flags = lAttrs.mParams.flags = Memory_CACHED;
    } 
    
    gfxAttrs.colorSpace     = colorSpace;
    gfxAttrs.dim.width      = params.maxWidth;
    gfxAttrs.dim.height     = params.maxHeight;
    gfxAttrs.dim.lineLength = BufferGfx_calcLineLength(params.maxWidth,
                                                       colorSpace);

    /* Create a table of output buffers of the size requested by the codec */
    hBufTab = BufTab_create(numBufs, 
        Dmai_roundUp(Vdec2_getOutBufSize(hVd2), BUFSIZEALIGN),
        BufferGfx_getBufferAttrs(&gfxAttrs));
    
    if (hBufTab == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to allocate contiguous buffers\n");
        goto cleanup;
    }

    /* Set output buffer table */
    Vdec2_setBufTab(hVd2, hBufTab);
 
    /* Ask the codec how much input data it needs */
    lAttrs.readSize = Vdec2_getInBufSize(hVd2);

    /* Make the total ring buffer larger */
    lAttrs.readBufSize = Dmai_roundUp(lAttrs.readSize * 2, BUFSIZEALIGN); 

    /* Increase the stdio buffer size for loader for better RTDX performance */
    lAttrs.vBufSize = VBUFSIZE;
    
    /* Create the elementary stream file loader */
    hLoader = Loader_create(args->inFile, &lAttrs);

    if (hLoader == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr, "Failed to create loader\n");
        goto cleanup;
    }

    /* Prime the file loader */
    Loader_prime(hLoader, &hInBuf);

    printf("Loader created and primed, entering main loop..\n");

    /* Main loop */
    while (1) {
        if (ret != Dmai_EFIRSTFIELD && ret != Dmai_EBITERROR) {
            /* Get a free buffer from the BufTab */
            hDstBuf = BufTab_getFreeBuf(hBufTab);

            if (hDstBuf == NULL) {
                ret = Dmai_EFAIL;
                fprintf(stderr, "Failed to get a free contiguous buffer from BufTab\n");
                BufTab_print(hBufTab);
                goto cleanup;
            }
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr, "Failed to reset timer\n");
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
                    ret = Dmai_EFAIL;
                    fprintf(stderr, "Failed to get timer delta\n");
                    goto cleanup;
                }
    
                printf("Pre-process cache maintenance: %uus \n", (Uns) time);
            }
        }

        /* Make sure the whole buffer is used for output */
        BufferGfx_resetDimensions(hDstBuf);

        /* Decode the video buffer */
        ret = Vdec2_process(hVd2, hInBuf, hDstBuf);
     
        if (ret < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr, "Failed to decode video buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr, "Failed to get decode time\n");
                goto cleanup;
            }

            printf("Frame %d - Decode: %uus\n", numFrame, (Uns)time);
        }

        if (numFrame == 1) {
            /* Resize the BufTab after the first frame has been processed */
            numBufs = resizeBufTab(hVd2, numBufs);

            if (numBufs < 0) {
                ret = 1;
                goto cleanup;
            }
        }

        /* Query the codec for display buffers and write them to a file */
        hOutBuf = Vdec2_getDisplayBuf(hVd2);

        /* If the codec was previously flushed and there are no more display
         * buffers exit main thread.
         */

        if (flushed&&(hOutBuf==NULL)) {
            Buffer_delete(hInBuf);
            break;
        }

        while (hOutBuf) {
            if (args->cache) {
                /* Writeback the outBuf. */
                Memory_cacheWb(Buffer_getUserPtr(hOutBuf), 
                    Buffer_getSize(hOutBuf));
        
                if (args->benchmark) {
                    if (Time_delta(hTime, &time) < 0) {
                        ret = Dmai_EFAIL;
                        fprintf(stderr, "Failed to get timer delta\n");
                        goto cleanup;
                    }
        
                    printf("Post-process cache write back: %uus \n", 
                            (Uns) time);
                }
            }

            if (vc1Offset) {
                /* The VC1 codec for DM365 puts the CbCr plane in 
                 * (dim.y * dim.lineLength / 2) offset more than the expected 
                 * place. So we (virtual) increase buffer size which will cause 
                 * other components to pick up CbCr data from right place. 
                 */
                BufferGfx_getDimensions(hOutBuf, &dim);
                Buffer_setVirtualSize(hOutBuf, 
                    Buffer_getSize(hOutBuf) +
                    (dim.y * dim.lineLength / 2) * 3 / 2);
            }

            if (mpeg4Offset) {
                /* The MPEG4 codec for DM6467 puts the CbCr plane in 
                 * (dim.y * dim.lineLength / 2) offset less than the expected 
                 * place. So we (virtual) decrease buffer size which will cause 
                 * other components to pick up CbCr data from right place. 
                 */
                BufferGfx_getDimensions(hOutBuf, &dim);
                Buffer_setVirtualSize(hOutBuf, 
                    Buffer_getSize(hOutBuf) -
                    (dim.y * dim.lineLength / 2) * 3 / 2);
            }

            if (numFrameDisp++ >= args->startFrame) {
                printf("Display Frame %d: ", numFrameDisp - 1);

                if ((device == Cpu_Device_DM6467) ||
                    (device == Cpu_Device_DM365)  ||
                    (device == Cpu_Device_DM368)) {
                    if(args->sp) {
                        if (writeFrame420SP(hOutBuf, outFile, device) < 0) {
                            ret = Dmai_EFAIL;
                            goto cleanup;
                        }
                    } else {
                        if (writeFrame420P(hOutBuf, outFile, device) < 0) {
                            ret = Dmai_EFAIL;
                            goto cleanup;
                        }
                    }
                }
                else {
                    if (writeFrameUYVY(hOutBuf, outFile) < 0) {
                        ret = Dmai_EFAIL; 
                        goto cleanup;
                    }
                }
            }
            if (vc1Offset) {
                Buffer_setVirtualSize(hOutBuf, 0);
            }
            if (mpeg4Offset) {
                Buffer_setVirtualSize(hOutBuf, 0);
            }
            /* Get another buffer for display from the codec */
            hOutBuf = Vdec2_getDisplayBuf(hVd2);
        }

        /* Get a buffer to free from the codec */
        hFreeBuf = Vdec2_getFreeBuf(hVd2);
        while (hFreeBuf) {
            /* The codec is no longer using the buffer */
            BufTab_freeBuf(hFreeBuf);
            hFreeBuf = Vdec2_getFreeBuf(hVd2);
        }

        if (!flushed) {

            printf("Loaded Frame %d: frame size %d\n", numFrame,
                (Int)Buffer_getNumBytesUsed(hInBuf));

            /* Load a new frame from the file system */
            Loader_getFrame(hLoader, hInBuf);

            if (numFrame++ == args->numFrames ||
                        Buffer_getUserPtr(hInBuf) == NULL){
                flushed = TRUE;
                
                /* Flush the codec for display frames */
                Vdec2_flush(hVd2);

                /*
                * Temporarily create a temporary dummy buffer for the process
                * call. After a flush the codec ignores the input buffer, but
                * since Codec Engine still address translates the buffer, it
                * needs to exist.
                */
                hInBuf = Buffer_create(1, BufferGfx_getBufferAttrs(&gfxAttrs));

                if (hInBuf == NULL) {
                    ret = Dmai_EFAIL;
                    fprintf(stderr, "Failed to allocate dummy buffer\n");
                    goto cleanup;
                }   

                Buffer_setNumBytesUsed(hInBuf, 1);
            }   
        }

        if (flushed) {
            Buffer_setNumBytesUsed(hInBuf, 1);
        }

        if (args->benchmark) {
            if (Time_total(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr, "Failed to get timer total\n");
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

    if (hVd2) {
        Vdec2_delete(hVd2);
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

    if (ret == Dmai_EFAIL)     
        return 1;
    else
        return 0;
}
