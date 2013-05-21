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
 * by copying the captured frame to the display.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Smooth.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/Framecopy.h>

#include "appMain.h"

/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{
    Framecopy_Attrs         fcAttrs      = Framecopy_Attrs_DEFAULT;
    BufferGfx_Attrs         gfxAttrs     = BufferGfx_Attrs_DEFAULT;
    Smooth_Attrs            smAttrs      = Smooth_Attrs_DEFAULT;
    Time_Attrs              tAttrs       = Time_Attrs_DEFAULT;
    BufTab_Handle           hCapBufTab   = NULL;
    BufTab_Handle           hDisBufTab   = NULL;
    Display_Handle          hDisplay     = NULL;
    Capture_Handle          hCapture     = NULL;
    Framecopy_Handle        hFc          = NULL;
    Smooth_Handle           hSmooth      = NULL;
    Time_Handle             hTime        = NULL;
    Int                     numFrame     = 0;
    Display_Attrs           dAttrs;
    Capture_Attrs           cAttrs;
    Buffer_Handle           cBuf, dBuf;
    Cpu_Device              device;
    Int                     bufIdx;
    UInt32                  time;
    BufferGfx_Dimensions    dim;
    Int32                   bufSize;
    Int                     ret = Dmai_EOK;

    /* Initialize DMAI */
    Dmai_init();

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create Time object\n");
            goto cleanup;
        }
    }

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
            dAttrs.colorSpace = ColorSpace_YUV420PSEMI;
            cAttrs.colorSpace = dAttrs.colorSpace;
            break;
        case Cpu_Device_OMAPL138:
            dAttrs = Display_Attrs_OMAPL138_VID_DEFAULT;
            cAttrs = Capture_Attrs_OMAPL138_DEFAULT;
            break;
        case Cpu_Device_OMAP3530:
        case Cpu_Device_DM3730:
            dAttrs     = Display_Attrs_O3530_VID_DEFAULT;
            cAttrs     = Capture_Attrs_OMAP3530_DEFAULT;
            dAttrs.colorSpace = cAttrs.colorSpace = ColorSpace_UYVY;
            dAttrs.rotation = 270;
            break;
        default:
            dAttrs = Display_Attrs_DM6446_DM355_VID_DEFAULT;
            cAttrs = Capture_Attrs_DM6446_DM355_DEFAULT;
            break;
    }

    if (args->displayStd != -1) {
        dAttrs.displayStd = args->displayStd;
    }

    if (args->displayDevice) {
        dAttrs.displayDevice = args->displayDevice;
    }

    if (args->displayNumBufs != -1) {
        dAttrs.numBufs = args->displayNumBufs;
    }

    /* Enable cropping in capture driver if selected */
    if (args->width != -1 && args->height != -1 && args->crop) {
        cAttrs.cropX = args->xIn;
        cAttrs.cropY = args->yIn;
        cAttrs.cropWidth = args->width;
        cAttrs.cropHeight = args->height;
    }

    cAttrs.videoInput = args->videoInput;

    if (Capture_detectVideoStd(NULL, &cAttrs.videoStd, &cAttrs) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to detect capture video standard\n");
        goto cleanup;
    }

    /* The color space of the capture buffers depend on the device */
    gfxAttrs.colorSpace = cAttrs.colorSpace;

    if (VideoStd_getResolution(cAttrs.videoStd, &gfxAttrs.dim.width, 
                                &gfxAttrs.dim.height) < 0) {
        goto cleanup;
    }

    gfxAttrs.dim.lineLength =
        Dmai_roundUp(BufferGfx_calcLineLength(gfxAttrs.dim.width, 
                                              gfxAttrs.colorSpace), 32); 
    gfxAttrs.dim.x = 0;
    gfxAttrs.dim.y = 0;

    if (gfxAttrs.colorSpace == ColorSpace_YUV422PSEMI) {
        bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height * 2;
    }
    else if (gfxAttrs.colorSpace == ColorSpace_YUV420PSEMI) {
        bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height * 3 / 2;
    }
    else {
        bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height;
    }

    if (args->captureUalloc) {
        /* Create a table of video buffers to use with the capture device */
        hCapBufTab = BufTab_create(cAttrs.numBufs, bufSize,
                                   BufferGfx_getBufferAttrs(&gfxAttrs));
        if (hCapBufTab == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to allocate contiguous buffers\n");
            goto cleanup;
        }
    }

    /* Create the capture device driver instance */
    hCapture = Capture_create(hCapBufTab, &cAttrs);

    if (hCapture == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create capture device\n");
        goto cleanup;
    }

    /* Create the display device driver instance */
    dAttrs.videoStd = Capture_getVideoStd(hCapture);
    dAttrs.videoOutput = args->videoOutput;

    if (args->displayUalloc) {
        /* Create a table of video buffers to use with the display device */
        hDisBufTab = BufTab_create(dAttrs.numBufs, bufSize,
                                   BufferGfx_getBufferAttrs(&gfxAttrs));

        if (hDisBufTab == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to allocate contiguous buffers\n");
            goto cleanup;
        }
    }

    hDisplay = Display_create(hDisBufTab, &dAttrs);

    if (hDisplay == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create display device\n");
        goto cleanup;
    }

    if (args->smooth) {
        /* Create the smooth job */
        hSmooth = Smooth_create(&smAttrs);

        if (hSmooth == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create smooth job\n");
        }
    }
    else {
        /* Create the frame copy job */
        fcAttrs.accel = args->accel;
        hFc = Framecopy_create(&fcAttrs);

        if (hFc == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create frame copy job\n");
            goto cleanup;
        }
    }

    /*
     * If cropping is not used, alter the dimensions of the captured
     * buffers and position the smaller image inside the full screen.
     */
    if (args->width != -1 && args->height != -1 && !args->crop) {
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
                ret = Dmai_EFAIL;
                fprintf(stderr,"Output resolution does not fit in display frame\n");
                goto cleanup;
            }
        }
    }

    if (args->smooth) {
        if (Smooth_config(hSmooth,
                          BufTab_getBuf(Capture_getBufTab(hCapture), 0),
                          BufTab_getBuf(Display_getBufTab(hDisplay), 0)) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to configure smooth job\n");
            goto cleanup;
        }
    }
    else {
        /* Configure the frame copy job */
        if (Framecopy_config(hFc, BufTab_getBuf(Capture_getBufTab(hCapture), 0),
                          BufTab_getBuf(Display_getBufTab(hDisplay), 0)) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to configure frame copy job\n");
            goto cleanup;
        }
    }

    while (numFrame++ < args->numFrames || args->numFrames == 0) {
        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Get a captured frame from the capture device */
        if (Capture_get(hCapture, &cBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get capture buffer\n");
            goto cleanup;
        }

        /* Get a frame from the display device to be filled with data */
        if (Display_get(hDisplay, &dBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get display buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer delta\n");
                goto cleanup;
            }
        }

        if (args->smooth) {
            /*
             * Remove interlacing artifacts from the captured buffer and
             * store the result in the display buffer.
             */
            if (Smooth_execute(hSmooth, cBuf, dBuf) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to execute smooth job\n");
                goto cleanup;
            }
        }
        else {
            /* Copy the captured buffer to the display buffer */
            if (Framecopy_execute(hFc, cBuf, dBuf) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to execute frame copy job\n");
                goto cleanup;
            }
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer delta\n");
                goto cleanup;
            }

            printf("Smooth / Framecopy: %uus ", (Uns) time);
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

        if (args->benchmark) {
            if (Time_total(hTime, &time) < 0) {
                ret = Dmai_EFAIL;
                fprintf(stderr,"Failed to get timer total\n");
                goto cleanup;
            }

            printf("Frame time: %uus\n", (Uns) time);
        }
    }

cleanup:
    /* Clean up the application */
    if (hSmooth) {
        Smooth_delete(hSmooth);
    }

    if (hFc) {
        Framecopy_delete(hFc);
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

    if (hCapBufTab) {
        BufTab_delete(hCapBufTab);
    }

    if (hDisBufTab) {
        BufTab_delete(hDisBufTab);
    }

    if (ret == Dmai_EFAIL)
        return 1;
    else
        return 0;
}
