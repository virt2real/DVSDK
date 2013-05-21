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
 * without copying the frame, i.e. the output frame of the capture device is
 * given as input to the display device. This is used to test capture and
 * device drivers if they properly handle user allocated buffers.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "appMain.h"

#define NUM_BUFS            3

/******************************************************************************
 * appMain
 ******************************************************************************/
Int appMain(Args * args)
{
    BufferGfx_Attrs  gfxAttrs = BufferGfx_Attrs_DEFAULT;
    Time_Attrs       tAttrs   = Time_Attrs_DEFAULT;
    Display_Handle   hDisplay = NULL;
    Capture_Handle   hCapture = NULL;
    BufTab_Handle    hBufTab  = NULL;
    Time_Handle      hTime    = NULL;
    Int              numFrame = 0;
    Display_Attrs    dAttrs;
    Capture_Attrs    cAttrs;
    Buffer_Handle    cBuf, dBuf;
    VideoStd_Type    videoStd;
    UInt32           time;
    Int32            bufSize;
    Cpu_Device       device;    
    ColorSpace_Type  colorSpace;
    Int32            width, height, lineLength;
    Int              ret = Dmai_EOK;

    /* Initialize DMAI */
    Dmai_init();

    /* Determine which device the application is running on */
    if (Cpu_getDevice(NULL, &device) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to determine target board\n");
        goto cleanup;
    }

    switch (device) {
        case Cpu_Device_DM6467:
            colorSpace = ColorSpace_YUV422PSEMI;
            dAttrs     = Display_Attrs_DM6467_VID_DEFAULT;
            cAttrs     = Capture_Attrs_DM6467_DEFAULT;
            break;
        case Cpu_Device_DM365:
        case Cpu_Device_DM368:
            colorSpace = ColorSpace_YUV420PSEMI;
            dAttrs     = Display_Attrs_DM365_VID_DEFAULT;
            cAttrs     = Capture_Attrs_DM365_DEFAULT;            
            cAttrs.videoInput = args->videoInput;
            break;
        case Cpu_Device_OMAPL138:
            colorSpace = ColorSpace_YUV422PSEMI;
            dAttrs     = Display_Attrs_OMAPL138_VID_DEFAULT;
            cAttrs     = Capture_Attrs_OMAPL138_DEFAULT;            
            break;
        case Cpu_Device_OMAP3530:
        case Cpu_Device_DM3730:
            colorSpace = ColorSpace_UYVY;
            dAttrs     = Display_Attrs_O3530_VID_DEFAULT;
            cAttrs     = Capture_Attrs_OMAP3530_DEFAULT;
            dAttrs.rotation = 270;
            break;
        default:
            colorSpace = ColorSpace_UYVY;
            dAttrs     = Display_Attrs_DM6446_DM355_VID_DEFAULT;
            cAttrs     = Capture_Attrs_DM6446_DM355_DEFAULT;
            break;            
    }

    if (args->benchmark) {
        hTime = Time_create(&tAttrs);

        if (hTime == NULL) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to create Time object\n");
            goto cleanup;
        }
    }

    if (args->videoStd == VideoStd_AUTO) {
        /* Detect which video input is connected on the component input */
        if (Capture_detectVideoStd(NULL, &videoStd, &cAttrs) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to detect input video standard, input connected?\n");
            goto cleanup;
        }
    }
    else {
        videoStd = args->videoStd;
    }

    if (VideoStd_getResolution(videoStd, &width, &height) < 0) {
        goto cleanup;
    }

    lineLength = BufferGfx_calcLineLength(width, colorSpace);
    if (lineLength < 0) {
        goto cleanup;
    }

    if ((device == Cpu_Device_DM365) || (device == Cpu_Device_DM368)) {
        /* In DM365, the capture buffer lineLength need to be divisible by 32 */
        lineLength = Dmai_roundUp(lineLength, 32);
    }

    if (colorSpace == ColorSpace_YUV422PSEMI) {
        bufSize = lineLength * height * 2;
    }
    else if (colorSpace == ColorSpace_YUV420PSEMI) {
        bufSize = lineLength * height * 3 / 2;
    }
    else {
        bufSize = lineLength * height;
    }

    /* Calculate the dimensions of the video standard */
    if (BufferGfx_calcDimensions(videoStd, colorSpace, &gfxAttrs.dim) < 0) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to calculate dimensions for video driver buffers\n");
        goto cleanup;
    }

    gfxAttrs.colorSpace = colorSpace;

    /* Create a table of buffers to use with the capture and display drivers */
    hBufTab = BufTab_create(NUM_BUFS, bufSize,
                            BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hBufTab == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to allocate contiguous buffers\n");
        goto cleanup;
    }

    /* Create the capture display driver instance */
    cAttrs.numBufs          = NUM_BUFS;
    cAttrs.captureDimension = &gfxAttrs.dim;
    cAttrs.colorSpace       = colorSpace;
    cAttrs.videoInput       = args->videoInput;
    cAttrs.videoStd         = videoStd;
    hCapture = Capture_create(hBufTab, &cAttrs);

    if (hCapture == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create capture device\n");
        goto cleanup;
    }

    /* Free buffers for Display driver */
    BufTab_freeAll(hBufTab);

    /* Create the display display driver instance */
    dAttrs.numBufs     = NUM_BUFS;
    dAttrs.colorSpace  = colorSpace;
    dAttrs.videoStd    = videoStd;
    dAttrs.videoOutput = args->videoOutput;
    hDisplay = Display_create(hBufTab, &dAttrs);

    if (hDisplay == NULL) {
        ret = Dmai_EFAIL;
        fprintf(stderr,"Failed to create display device\n");
        goto cleanup;
    }

    while (args->numFrames == 0 || numFrame++ < args->numFrames) {
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

        /* Get a frame from the display device */
        if (Display_get(hDisplay, &dBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to get display buffer\n");
            goto cleanup;
        }

        /* Give the frame from the display device to the capture device */
        if (Capture_put(hCapture, dBuf) < 0) {
            ret = Dmai_EFAIL;
            fprintf(stderr,"Failed to put capture buffer\n");
            goto cleanup;
        }

        /* Give the frame from the capture device to the display device */
        if (Display_put(hDisplay, cBuf) < 0) {
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
    if (hCapture) {
        Capture_delete(hCapture);
    }

    if (hDisplay) {
        Display_delete(hDisplay);
    }

    if (hBufTab) {
        BufTab_delete(hBufTab);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    if (ret == Dmai_EFAIL)
        return 1;
    else
        return 0;
}
