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
 * This application does a video loopback between the capture and display
 * device by resizing the captured frame to D1 NTSC before displaying it.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Resize.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>

#include "appMain.h"

#define NUM_DISPLAY_BUFS    3
#define NUM_CAPTURE_BUFS    3

/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{
    Resize_Attrs            rszAttrs       = Resize_Attrs_DEFAULT;
    Time_Attrs              tAttrs         = Time_Attrs_DEFAULT;
    Display_Handle          hDisplay       = NULL;
    Capture_Handle          hCapture       = NULL;
    BufTab_Handle           hCapBufTab     = NULL;
    BufTab_Handle           hDisBufTab     = NULL;
    Resize_Handle           hRsz           = NULL;
    Time_Handle             hTime          = NULL;
    Int                     numFrame       = 0;
    Display_Attrs           dAttrs;
    Capture_Attrs           cAttrs;
    BufferGfx_Attrs         gfxAttrs;
    VideoStd_Type           videoStd;
    BufTab_Handle           hCaptureBufTab;
    BufTab_Handle           hDisplayBufTab;
    Buffer_Handle           cBuf, dBuf;
    Cpu_Device              device;
    Int32                   bufSize;
    UInt32                  time;
    Int                     bufIdx;
    BufferGfx_Dimensions    dim;
    Int                     ret = Dmai_EOK;

    /* Initialize DMAI */
    Dmai_init();
    
    /* Determine which device the application is running on */
    if (Cpu_getDevice(NULL, &device) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to determine target board\n");
        goto cleanup;
    }

    /* Set the display and capture attributes depending on device */
    switch (device) {
        case Cpu_Device_DM6467:
            dAttrs = Display_Attrs_DM6467_VID_DEFAULT;
            cAttrs = Capture_Attrs_DM6467_DEFAULT;
            break;
        case Cpu_Device_DM365:
        case Cpu_Device_DM368:
            dAttrs = Display_Attrs_DM365_VID_DEFAULT;
            cAttrs = Capture_Attrs_DM365_DEFAULT;
            dAttrs.colorSpace = ColorSpace_UYVY;            
            cAttrs.colorSpace = ColorSpace_UYVY;
            break;
        case Cpu_Device_OMAP3530:
        case Cpu_Device_DM3730:
            dAttrs = Display_Attrs_O3530_VID_DEFAULT;
            cAttrs = Capture_Attrs_OMAP3530_DEFAULT;
            dAttrs.rotation = 270;
            break;
        default:
            dAttrs = Display_Attrs_DM6446_DM355_VID_DEFAULT;
            cAttrs = Capture_Attrs_DM6446_DM355_DEFAULT;
            break;
    }

    cAttrs.videoInput = args->videoInput;

    /*
     * Should the application allocate buffers for the capture device, or
     * does the device driver do this?
     */
    if (args->captureUalloc) {
        if (Capture_detectVideoStd(NULL, &videoStd, &cAttrs) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr, "Failed to detect capture video standard\n");
            goto cleanup;
        }

        gfxAttrs = BufferGfx_Attrs_DEFAULT;
        gfxAttrs.colorSpace = device == Cpu_Device_DM6467 ?
            ColorSpace_YUV422PSEMI : ColorSpace_UYVY;

        if (!args->crop) {
            /* Calculate the dimensions of a video standard given a color space */
            if (BufferGfx_calcDimensions(videoStd,
                                         gfxAttrs.colorSpace,
                                         &gfxAttrs.dim) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to calculate dimensions for display buffers\n");
                goto cleanup;
            }

        } else {
            gfxAttrs.dim.height = args->inHeight;
            gfxAttrs.dim.width  = args->inWidth;
            gfxAttrs.dim.lineLength = 
                Dmai_roundUp(BufferGfx_calcLineLength(gfxAttrs.dim.width, 
                                        gfxAttrs.colorSpace), 32);
        }

        if (gfxAttrs.colorSpace == ColorSpace_YUV422PSEMI) {
            bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height * 2;
        }
        else if (gfxAttrs.colorSpace == ColorSpace_YUV420PSEMI) {
            bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height * 3 / 2;
        }
        else {
            bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;
        }

        if (bufSize < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to calculated size for display buffers\n");
            goto cleanup;
        }

        /* Create a table of video buffers to use with the capture device */
        hCapBufTab = BufTab_create(NUM_CAPTURE_BUFS, bufSize,
                                   BufferGfx_getBufferAttrs(&gfxAttrs));

        if (hCapBufTab == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to allocate contiguous buffers\n");
            goto cleanup;
        }
    }

    if (args->inWidth != -1 && args->inHeight != -1 && args->crop) {
        cAttrs.cropX = args->xIn;
        cAttrs.cropY = args->yIn;
        cAttrs.cropWidth = args->inWidth;
        cAttrs.cropHeight = args->inHeight;
    }

    cAttrs.numBufs = NUM_CAPTURE_BUFS;

    /* Create the capture device driver instance */
    hCapture = Capture_create(hCapBufTab, &cAttrs);

    if (hCapture == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create capture device\n");
        goto cleanup;
    }

    /* Resolution defaults to display standard if not specified */
    videoStd = Capture_getVideoStd(hCapture);

    if (args->inWidth == -1) {
        if (VideoStd_getResolution(videoStd, &args->inWidth,
            &args->inHeight) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get resolution of capture video standard\n");
            goto cleanup;
        }
    }

    /*
     * Retrieve a handle to the BufTab used by the capture device, whether
     * it's driver or application created.
     */
    hCaptureBufTab = Capture_getBufTab(hCapture);

    /*
     * Should the application allocate buffers for the display device, or
     * does the device driver do this?
     */
    if (args->displayUalloc) {
        gfxAttrs = BufferGfx_Attrs_DEFAULT;
        gfxAttrs.colorSpace = device == Cpu_Device_DM6467 ?
            ColorSpace_YUV422PSEMI : ColorSpace_UYVY;

        /* Calculate the dimensions of a video standard given a color space */
        if (BufferGfx_calcDimensions(args->videoStd,
                                     gfxAttrs.colorSpace, &gfxAttrs.dim) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr, "Failed to calculate dimensions for display buffers\n");
            goto cleanup;
        }

        /* Calculate buffer size needed of video standard given a color space */
        bufSize = BufferGfx_calcSize(args->videoStd, gfxAttrs.colorSpace);

        if (bufSize < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to calculated size for display buffers\n");
            goto cleanup;
        }

        /* Create a table of video buffers to use with the display device */
        hDisBufTab = BufTab_create(NUM_DISPLAY_BUFS, bufSize,
                                   BufferGfx_getBufferAttrs(&gfxAttrs));

        if (hDisBufTab == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to allocate contiguous buffers\n");
            goto cleanup;
        }
    }

    /* Create the video display */
    dAttrs.videoStd = args->videoStd;
    dAttrs.numBufs = NUM_DISPLAY_BUFS;
    dAttrs.videoOutput = args->videoOutput;
    hDisplay = Display_create(hDisBufTab, &dAttrs);

    if (hDisplay == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to open display device\n");
        goto cleanup;
    }

    /*
     * Retrieve a handle to the BufTab used by the display device, whether
     * it's driver or application created.
     */
    hDisplayBufTab = Display_getBufTab(hDisplay);

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Create the resize job */
    hRsz = Resize_create(&rszAttrs);

    if (hRsz == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create resize job\n");
        goto cleanup;
    }

    /*
     * If cropping is not used, alter the dimensions of the captured
     * buffers and position the smaller image inside the full screen.
     */
    if (args->outWidth != -1 && args->outHeight != -1 && !args->crop) {
        for (bufIdx = 0;
             bufIdx < BufTab_getNumBufs(hCaptureBufTab);
             bufIdx++) {

            cBuf = BufTab_getBuf(hCaptureBufTab, bufIdx);
            BufferGfx_getDimensions(cBuf, &dim);

            dim.width   = args->inWidth;
            dim.height  = args->inHeight;
            dim.x       = args->xIn;
            dim.y       = args->yIn;

            if (BufferGfx_setDimensions(cBuf, &dim) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Input resolution does not fit in capture frame\n");
                goto cleanup;
            }
        }
    }

    /*
     * Alter the dimensions of the display buffers and position
     * the smaller image inside the full screen.
     */
    if (args->outWidth != -1 && args->outHeight != -1) {
        for (bufIdx = 0; bufIdx < BufTab_getNumBufs(hDisplayBufTab); bufIdx++) {
            dBuf = BufTab_getBuf(hDisplayBufTab, bufIdx);
            BufferGfx_getDimensions(dBuf, &dim);

            dim.width   = args->outWidth;
            dim.height  = args->outHeight;
            dim.x       = args->xOut;
            dim.y       = args->yOut;

            if (BufferGfx_setDimensions(dBuf, &dim) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Output resolution does not fit in display frame\n");
                goto cleanup;
            }
        }
    }

    /* Configure the resize job */
    if (Resize_config(hRsz, BufTab_getBuf(hCaptureBufTab, 0),
                      BufTab_getBuf(hDisplayBufTab, 0)) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to configure resize job\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames || args->numFrames == 0) {
        /* Get a captured buffer from the capture device driver */
        if (Capture_get(hCapture, &cBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get capture buffer\n");
            goto cleanup;
        }

        /* Get a possibly smaller buffer from the display device driver */
        if (Display_get(hDisplay, &dBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get display buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Resize the captured frame to the resolution of the display frame */
        if (Resize_execute(hRsz, cBuf, dBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to execute resize job\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer delta\n");
                goto cleanup;
            }

            printf("%d: Resize: %uus\n", numFrame, (Uns) time);
        }

        /* Give captured buffer back to the capture device driver */
        if (Capture_put(hCapture, cBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to put capture buffer\n");
            goto cleanup;
        }

        /* Send filled buffer to display device driver to be displayed */
        if (Display_put(hDisplay, dBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to put display buffer\n");
            goto cleanup;
        }
    }

cleanup:
    /* Clean up the application */
    if (hCapture) {
        Capture_delete(hCapture);
    }

    if (hDisplay) {
        Display_delete(hDisplay);
    }

    if (hRsz) {
        Resize_delete(hRsz);
    }

    if (hCapBufTab) {
        BufTab_delete(hCapBufTab);
    }

    if (hDisBufTab) {
        BufTab_delete(hDisBufTab);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (ret == Dmai_EFAIL)
        return 1;
    else
        return 0;
}
