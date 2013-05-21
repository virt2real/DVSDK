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
 * by color converting the captured 422 semiplanar frame to 420 semiplanar
 * format and then converting the 420 semiplanar frame back to 422 semiplanar
 * before displaying the frame.
 */

#include <stdio.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Ccv.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Time.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "appMain.h"

#define NUM_DISPLAY_BUFS 3
#define NUM_CAPTURE_BUFS 3

/******************************************************************************
 * appMain
 ******************************************************************************/
Void appMain(Args * args)
{
    Ccv_Attrs               ccv420422Attrs = Ccv_Attrs_DEFAULT;
    Ccv_Attrs               ccv422420Attrs = Ccv_Attrs_DEFAULT;
    BufferGfx_Attrs         gfxAttrs       = BufferGfx_Attrs_DEFAULT;
    Time_Attrs              tAttrs         = Time_Attrs_DEFAULT;
    Display_Handle          hDisplay       = NULL;
    Capture_Handle          hCapture       = NULL;
    Buffer_Handle           hIntBuf        = NULL;
    BufTab_Handle           hCapBufTab     = NULL;
    BufTab_Handle           hDisBufTab     = NULL;
    Ccv_Handle              hCcv420to422   = NULL;
    Ccv_Handle              hCcv422to420   = NULL;
    Time_Handle             hTime          = NULL;
    Int                     numFrame       = 0;
    BufferGfx_Dimensions    dim;
    Display_Attrs           dAttrs;
    Capture_Attrs           cAttrs;
    VideoStd_Type           videoStd;
    BufTab_Handle           hCaptureBufTab;
    BufTab_Handle           hDisplayBufTab;
    Buffer_Handle           cBuf, dBuf;
    Cpu_Device              device;
    Int32                   bufSize;
    UInt32                  time;
    Int                     bufIdx;

    /* Initialize DMAI */
    Dmai_init();
    
    /* Determine which device the application is running on */
    if (Cpu_getDevice(NULL, &device) < 0) {
        printf("Failed to determine target board\n");
        goto cleanup;
    }

    /* Set the display and capture attributes depending on device */
    if (device == Cpu_Device_DM6467) {
        dAttrs = Display_Attrs_DM6467_VID_DEFAULT;
        cAttrs = Capture_Attrs_DM6467_DEFAULT;
    }
    else {
        dAttrs = Display_Attrs_DM6446_DM355_VID_DEFAULT;
        cAttrs = Capture_Attrs_DM6446_DM355_DEFAULT;
    }

    /* Detect which video input is connected on the video input */
    if (Capture_detectVideoStd(NULL, &videoStd, &cAttrs) < 0) {
        printf("Failed to detect capture video standard\n");
        goto cleanup;
    }

    /*
     * Should the application allocate buffers for the capture device, or
     * does the device driver do this?
     */
    if (args->captureUalloc) {
        /* The color space of the capture buffers depend on the device */
        gfxAttrs.colorSpace = device == Cpu_Device_DM6467 ?
                                    ColorSpace_YUV422PSEMI : ColorSpace_UYVY;

        /* Calculate the dimensions of a video standard given a color space */
        if (BufferGfx_calcDimensions(videoStd,
                                      gfxAttrs.colorSpace, &gfxAttrs.dim) < 0) {
            printf("Failed to calculate dimensions for display buffers\n");
            goto cleanup;
        }

        /* Calculate buffer size needed of video standard given a color space */
        bufSize = BufferGfx_calcSize(videoStd, gfxAttrs.colorSpace);

        if (bufSize < 0) {
            printf("Failed to calculated size for display buffers\n");
            goto cleanup;
        }

        /* Create a table of video buffers to use with the capture device */
        hCapBufTab = BufTab_create(NUM_CAPTURE_BUFS, bufSize,
                                   BufferGfx_getBufferAttrs(&gfxAttrs));

        if (hCapBufTab == NULL) {
            printf("Failed to allocate contiguous buffers\n");
            goto cleanup;
        }
    }

    /* Create the capture device driver instance */
    cAttrs.numBufs = NUM_CAPTURE_BUFS;
    hCapture = Capture_create(hCapBufTab, &cAttrs);

    if (hCapture == NULL) {
        printf("Failed to create capture device\n");
        goto cleanup;
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
        /* The color space of the display buffers depend on the device */
        gfxAttrs.colorSpace = device == Cpu_Device_DM6467 ?
                                    ColorSpace_YUV422PSEMI : ColorSpace_UYVY;

        /* Calculate the dimensions of a video standard given a color space */
        if (BufferGfx_calcDimensions(videoStd,
                                      gfxAttrs.colorSpace, &gfxAttrs.dim) < 0) {
            printf("Failed to calculate dimensions for display buffers\n");
            goto cleanup;
        }

        /* Calculate buffer size needed of video standard given a color space */
        bufSize = BufferGfx_calcSize(Capture_getVideoStd(hCapture),
                                      gfxAttrs.colorSpace);

        if (bufSize < 0) {
            printf("Failed to calculated size for display buffers\n");
            goto cleanup;
        }

        /* Create a table of video buffers to use with the display device */
        hDisBufTab = BufTab_create(NUM_DISPLAY_BUFS, bufSize,
                                   BufferGfx_getBufferAttrs(&gfxAttrs));

        if (hDisBufTab == NULL) {
            printf("Failed to allocate contiguous buffers\n");
            goto cleanup;
        }
    }

    /* Create the video display */
    dAttrs.videoStd = videoStd;
    dAttrs.numBufs = NUM_DISPLAY_BUFS;
    dAttrs.videoOutput = args->videoOutput;
    hDisplay = Display_create(hDisBufTab, &dAttrs);

    if (hDisplay == NULL) {
        printf("Failed to open display device\n");
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
            printf("Failed to create Time object\n");
            goto cleanup;
        }
    }

    /* Reset the attrs */
    gfxAttrs = BufferGfx_Attrs_DEFAULT;

    /* The color space used by the graphics buffers depends on the device */
    gfxAttrs.colorSpace = device == Cpu_Device_DM6467 ?
                                    ColorSpace_YUV420PSEMI : ColorSpace_UYVY;

    /* Set the size if one is given */
    if (args->width != -1 && args->height != -1) {
        gfxAttrs.dim.width = args->width;
        gfxAttrs.dim.height = args->height;
        gfxAttrs.dim.lineLength =
            BufferGfx_calcLineLength(args->width, gfxAttrs.colorSpace);
        bufSize = gfxAttrs.dim.lineLength * gfxAttrs.dim.height * 3 / 2;
    }
    else {
        /* Calculate the dimensions of a video standard given a color space */
        if (BufferGfx_calcDimensions(videoStd,
                                     gfxAttrs.colorSpace, &gfxAttrs.dim) < 0) {
            printf("Failed to calculate dimensions for display buffers\n");
            goto cleanup;
        }

        /* Calculate size needed of a video standard given a color space */
        bufSize = BufferGfx_calcSize(Capture_getVideoStd(hCapture),
                                     gfxAttrs.colorSpace);

        if (bufSize < 0) {
            printf("Failed to calculated size for display buffers\n");
            goto cleanup;
        }
    }

    /* Create an intermediate buffer for storing the converted video data */
    hIntBuf = Buffer_create(bufSize, BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hIntBuf == NULL) {
        printf("Failed to create buffer\n");
        goto cleanup;
    }

    /*
     * If cropping is not used, alter the dimensions of the captured
     * buffers and position the smaller image inside the full screen.
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

    /* Create the 422Psemi to 420Psemi color conversion job */
    ccv422420Attrs.accel = args->ccvinAccel;
    hCcv422to420 = Ccv_create(&ccv422420Attrs);

    if (hCcv422to420 == NULL) {
        printf("Failed to create 422 to 420 color conversion job\n");
        goto cleanup;
    }

    /* Configure the 422Psemi to 420Psemi color conversion job */
    if (Ccv_config(hCcv422to420, BufTab_getBuf(hCaptureBufTab, 0), hIntBuf)<0) {
        printf("Failed to configure color conversion job\n");
        goto cleanup;
    }

    /* Create the 420Psemi to 422Psemi color conversion job */
    ccv420422Attrs.accel = args->ccvoutAccel;
    hCcv420to422 = Ccv_create(&ccv420422Attrs);

    if (hCcv420to422 == NULL) {
        printf("Failed to create 420 to 422 color conversion job\n");
        goto cleanup;
    }

    /* Configure the 420Psemi to 422Psemi color conversion job */
    if (Ccv_config(hCcv420to422, hIntBuf, BufTab_getBuf(hDisplayBufTab, 0))<0) {
        printf("Failed to configure color conversion job\n");
        goto cleanup;
    }

    while (numFrame++ < args->numFrames || args->numFrames == 0) {
        /* Get a captured 422Psemi buffer from the capture device driver */
        if (Capture_get(hCapture, &cBuf) < 0) {
            printf("Failed to get capture buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                printf("Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Color convert the 422Psemi buffer to 420Psemi (used by codecs) */
        if (Ccv_execute(hCcv422to420, cBuf, hIntBuf) < 0) {
            printf("Failed to execute color conversion job\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }

            printf("%d: CCV 422->420: %uus ", numFrame, (Uns) time);
        }

        /* Get a buffer from the display device driver to fill with data */
        if (Display_get(hDisplay, &dBuf) < 0) {
            printf("Failed to get display buffer\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_reset(hTime) < 0) {
                printf("Failed to reset timer\n");
                goto cleanup;
            }
        }

        /* Color convert the 420Psemi buffer to 422Psemi (used by display) */
        if (Ccv_execute(hCcv420to422, hIntBuf, dBuf) < 0) {
            printf("Failed to execute color conversion job\n");
            goto cleanup;
        }

        if (args->benchmark) {
            if (Time_delta(hTime, &time) < 0) {
                printf("Failed to get timer delta\n");
                goto cleanup;
            }

            printf("CCV 420->422: %uus\n", (Uns) time);
        }

        /* Give captured buffer back to the capture device driver */
        if (Capture_put(hCapture, cBuf) < 0) {
            printf("Failed to put capture buffer\n");
            goto cleanup;
        }

        /* Send filled buffer to display device driver to be displayed */
        if (Display_put(hDisplay, dBuf) < 0) {
            printf("Failed to put display buffer\n");
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

    if (hCcv420to422) {
        Ccv_delete(hCcv420to422);
    }

    if (hCcv422to420) {
        Ccv_delete(hCcv422to420);
    }

    if (hCapBufTab) {
        BufTab_delete(hCapBufTab);
    }

    if (hDisBufTab) {
        BufTab_delete(hDisBufTab);
    }

    if (hIntBuf) {
        Buffer_delete(hIntBuf);
    }

    if (hTime) {
        Time_delete(hTime);
    }

    return;
}
