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
 * This application does a video loopback between the capture and display device
 * while blending a bitmap on top of the video frames.
 */

#include <stdio.h>
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Blend.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/Framecopy.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "appMain.h"

/******************************************************************************
 * bmpInit
 ******************************************************************************/
static Void bmpInit(Buffer_Handle hBmpBuf)
{
    BufferGfx_Dimensions dim;
    Int8 *ptr = Buffer_getUserPtr(hBmpBuf);
    Int stride;

    BufferGfx_getDimensions(hBmpBuf, &dim);

    stride = dim.lineLength * dim.height / 4;

    /*
     * This logic divides the bitmap buffer into 4 equal horizontal
     * parts. With every part there is an bitmap table associated
     * which will blend associated color with appropriate blend factor.
     */
    memset(ptr, 0, stride);
    memset(ptr + stride, 0x55, stride);
    memset(ptr + 2 * stride, 0xaa, stride);
    memset(ptr + 3 * stride, 0xff, stride);
}

/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    Display_Attrs           dAttrs        = Display_Attrs_DM6467_VID_DEFAULT;
    Capture_Attrs           cAttrs        = Capture_Attrs_DM6467_DEFAULT;
    Blend_Attrs             blAttrs       = Blend_Attrs_DEFAULT;
    BufferGfx_Attrs         gfxAttrs      = BufferGfx_Attrs_DEFAULT;
    Framecopy_Attrs         fcAttrs       = Framecopy_Attrs_DEFAULT;
    Blend_Config_Params     bConfigParams = Blend_Config_Params_DEFAULT;
    Time_Attrs              tAttrs        = Time_Attrs_DEFAULT;
    Display_Handle          hDisplay      = NULL;
    Capture_Handle          hCapture      = NULL;
    Blend_Handle            hBlend        = NULL;
    Buffer_Handle           hBmpBuf       = NULL;
    Framecopy_Handle        hFc           = NULL;
    Time_Handle             hTime         = NULL;
    BufTab_Handle           hCBufTab      = NULL;
    BufTab_Handle           hDBufTab      = NULL;
    Int                     numFrame      = 0;
    VideoStd_Type           videoStd;
    BufferGfx_Dimensions    dim;
    Buffer_Handle           cBuf, dBuf, iBuf;
    Int32                   bufSize;
    Int32                   bmpBufSize;
    Cpu_Device              device;
    Uint32                  time;
    Int                     bufIdx;

    /* Initialize DMAI */
    Dmai_init();
    
    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Determine which device the application is running on */
    if (Cpu_getDevice(NULL, &device) < 0) {
        printf("Failed to determine target board\n");
        goto cleanup;
    }

    /* Detect which video input is connected on the component input */
    if (Capture_detectVideoStd(NULL, &videoStd, &cAttrs) < 0) {
        printf("Failed to detect input video standard, input connected?\n");
        goto cleanup;
    }

    if (args->captureUalloc) {
        gfxAttrs.colorSpace = cAttrs.colorSpace;
        if (BufferGfx_calcDimensions(videoStd,
                                     cAttrs.colorSpace, &gfxAttrs.dim) < 0) {
            printf("Failed to calculate dimensions of video standard\n");
            goto cleanup;
        }

        bufSize = BufferGfx_calcSize(videoStd, cAttrs.colorSpace);
        if (bufSize < 0) {
            printf("Failed to calculate capture buffer size\n");
            goto cleanup;
        }

        hCBufTab = BufTab_create(cAttrs.numBufs, bufSize,
                                 BufferGfx_getBufferAttrs(&gfxAttrs));
        if (hCBufTab == NULL) {
            printf("Failed to create buftab\n");
            goto cleanup;
        }
    }

    /* Create the capture device driver instance */
    hCapture = Capture_create(hCBufTab, &cAttrs);

    if (hCapture == NULL) {
        printf("Failed to create capture device\n");
        goto cleanup;
    }

    if (args->displayUalloc) {
        gfxAttrs = BufferGfx_Attrs_DEFAULT;
        gfxAttrs.colorSpace = dAttrs.colorSpace;
        if (BufferGfx_calcDimensions(videoStd,
                                     dAttrs.colorSpace, &gfxAttrs.dim) < 0) {
            printf("Failed to calculate dimensions of video standard\n");
            goto cleanup;
        }

        bufSize = BufferGfx_calcSize(videoStd, dAttrs.colorSpace);
        if (bufSize < 0) {
            printf("Failed to calculate display buffer size\n");
            goto cleanup;
        }

        hDBufTab = BufTab_create(dAttrs.numBufs, bufSize,
                                 BufferGfx_getBufferAttrs(&gfxAttrs));
        if (hDBufTab == NULL) {
            printf("Failed to create buftab\n");
            goto cleanup;
        }
    }

    /* Create the display device driver instance */
    dAttrs.videoStd = Capture_getVideoStd(hCapture);
    dAttrs.videoOutput = args->videoOutput;
    hDisplay = Display_create(hDBufTab, &dAttrs);

    if (hDisplay == NULL) {
        printf("Failed to create display device\n");
        goto cleanup;
    }

    /*
     * Alter the dimensions of the captured buffers and position
     * the smaller image inside the full screen.
     */
    if (args->width != -1 && args->height != -1) {
        for (bufIdx = 0;
             bufIdx < BufTab_getNumBufs(Capture_getBufTab(hCapture));
             bufIdx++) {

            cBuf = BufTab_getBuf(Capture_getBufTab(hCapture), bufIdx);
            BufferGfx_getDimensions(cBuf, &dim);

            dim.width   = args->width;
            dim.height  = args->height;
            dim.x       = args->xIn;
            dim.y       = args->yIn;

            if (BufferGfx_setDimensions(cBuf, &dim) < 0) {
                printf("Input resolution does not fit in capture frame\n");
                goto cleanup;
            }
        }
    }

    /*
     * Alter the dimensions of the display buffers and position
     * the smaller image inside the full screen.
     */
    if (args->width != -1 && args->height != -1) {
        for (bufIdx = 0;
             bufIdx < BufTab_getNumBufs(Display_getBufTab(hDisplay));
             bufIdx++) {

            dBuf = BufTab_getBuf(Display_getBufTab(hDisplay), bufIdx);
            BufferGfx_getDimensions(dBuf, &dim);

            dim.width   = args->width;
            dim.height  = args->height;
            dim.x       = args->xOut;
            dim.y       = args->yOut;

            if (BufferGfx_setDimensions(dBuf, &dim) < 0) {
                printf("Output resolution does not fit in display frame\n");
                goto cleanup;
            }
        }
    }

    gfxAttrs                = BufferGfx_Attrs_DEFAULT;
    gfxAttrs.colorSpace     = ColorSpace_2BIT;
    gfxAttrs.dim.width      = args->bitmapWidth;
    gfxAttrs.dim.height     = args->bitmapHeight;
    gfxAttrs.dim.lineLength = 
        Dmai_roundUp(BufferGfx_calcLineLength(args->bitmapWidth,
                                              gfxAttrs.colorSpace), 8);

    bmpBufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;

    /* Create the bitmap buffer which will be blended */
    hBmpBuf = Buffer_create(bmpBufSize, BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hBmpBuf == NULL) {
        printf("Failed to allocate contiguous bitmap buffer\n");
        goto cleanup;
    }

    /* Initialize the bitmap */
    bmpInit(hBmpBuf);

    /* Should the blending have the same input and output buffers? */
    if (args->inplace) {
        /* Create the frame copy job */
        fcAttrs.accel = FALSE;
        hFc = Framecopy_create(&fcAttrs);

        if (hFc == NULL) {
            printf("Failed to create frame copy job\n");
            goto cleanup;
        }

        /* Configure the frame copy job */
        if (Framecopy_config(hFc, BufTab_getBuf(Capture_getBufTab(hCapture), 0),
                             BufTab_getBuf(Display_getBufTab(hDisplay), 0)
                            ) < 0) {
            printf("Failed to configure frame copy job\n");
            goto cleanup;
        }

        /* The source buffer for the blend will be a display buffer */
        iBuf = BufTab_getBuf(Display_getBufTab(hDisplay), 0);
    }
    else {
        /* The source buffer for the blend will be a capture buffer */
        iBuf = BufTab_getBuf(Capture_getBufTab(hCapture), 0);
    }

    /* Create the blending job */
    hBlend = Blend_create(&blAttrs);

    if (hBlend == NULL) {
        printf("Failed to create blending job\n");
        goto cleanup;
    }

    /* Configure the blending job */
    bConfigParams.bmpXpos = args->xBitmap;
    bConfigParams.bmpYpos = args->yBitmap;

    if (Blend_config(hBlend, NULL, hBmpBuf, iBuf,
                     BufTab_getBuf(Display_getBufTab(hDisplay), 0),
                     &bConfigParams) < 0) {
        printf("Failed to configure blending job\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames || args->numFrames == 0) {
        /* Get a captured buffer from the capture device driver */
        if (Capture_get(hCapture, &cBuf) < 0) {
            printf("Failed to get capture buffer\n");
            goto cleanup;
        }

        /* Get a buffer from the display device driver to be filled */
        if (Display_get(hDisplay, &dBuf) < 0) {
            printf("Failed to get display buffer\n");
            goto cleanup;
        }

        if (args->inplace) {
            /* First copy the captured frame to the display frame */
            if (Framecopy_execute(hFc, cBuf, dBuf) < 0) {
                printf("Failed to execute frame copy job\n");
                goto cleanup;
            }

            /*
             * This will make the input buffer to the blend operation the
             * same as the output buffer, i.e. "in place".
             */
            iBuf = dBuf;
        }
        else {
            /*
             * Use the captured buffer as input buffer. This will make the
             * blend operation copy the whole buffer from input to output
             * while performing the blend.
             */
            iBuf = cBuf;
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                printf("Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Execute the blending job */
        if (Blend_execute(hBlend, hBmpBuf, iBuf, dBuf) < 0) {
            printf("Failed to execute blending job\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Blend: %uus\n", (Uns) time);
        }

        /* Give the captured buffer back to the capture device */
        if (Capture_put(hCapture, cBuf) < 0) {
            printf("Failed to put capture buffer\n");
            goto cleanup;
        }

        /* Send the blended buffer back to the display device to be displayed */
        if (Display_put(hDisplay, dBuf) < 0) {
            printf("Failed to put display buffer\n");
            goto cleanup;
        }
    }

cleanup:
    /* Clean up the application */
    if (hBlend) {
        Blend_delete(hBlend);
    }

    if (hFc) {
        Framecopy_delete(hFc);
    }

    if (hBmpBuf) {
        Buffer_delete(hBmpBuf);
    }

    if (hCapture) {
        Capture_delete(hCapture);
    }

    if (hDisplay) {
        Display_delete(hDisplay);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (hCBufTab) {
        BufTab_delete(hCBufTab);
    }

    if (hDBufTab) {
        BufTab_delete(hDBufTab);
    }

    return;
}
