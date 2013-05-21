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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <media/davinci/videohd.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "../priv/_VideoBuf.h"
#include "../priv/_Display.h"
#include "priv/_SysFs.h"

#define MODULE_NAME     "Display"

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Display_Handle hDisplay)
{
    Int                   ret     = Dmai_EOK;
    BufTab_Handle         hBufTab = hDisplay->hBufTab;
    enum v4l2_buf_type    type;
    Int                   bufIdx;
    Buffer_Handle         hDispBuf;

    if (hDisplay->fd != -1) {
        if (hDisplay->started) {
            /* Shut off the video display */
            type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

            if (ioctl(hDisplay->fd, VIDIOC_STREAMOFF, &type) == -1) {
                Dmai_err1("VIDIOC_STREAMOFF failed (%s)\n", strerror(errno));
                ret = Dmai_EFAIL;
            }
        }

        if (hDisplay->userAlloc == FALSE) {
            if (hBufTab) {
                for (bufIdx = 0;
                     bufIdx < BufTab_getNumBufs(hBufTab);
                     bufIdx++) {

                    hDispBuf = BufTab_getBuf(hBufTab, bufIdx);

                    if (munmap(Buffer_getUserPtr(hDispBuf),
                               hDisplay->bufDescs[bufIdx].v4l2buf.length) == -1) {
                        Dmai_err1("Failed to unmap capture buffer%d\n", bufIdx);
                        ret = Dmai_EFAIL;
                    }
                }
            }
        }

        if (close(hDisplay->fd) == -1) {
            Dmai_err1("Failed to close capture device (%s)\n", strerror(errno));
            ret = Dmai_EIO;
        }
        
    }

    if (hDisplay->bufDescs) {
        free(hDisplay->bufDescs);
    }

    free(hDisplay);

    return ret;
}

/******************************************************************************
 * Display_v4l2_create
 ******************************************************************************/
Display_Handle Display_v4l2_create(BufTab_Handle hBufTab, Display_Attrs *attrs)
{
    struct v4l2_format         fmt;
    enum v4l2_buf_type         type;
    Display_Handle             hDisplay;

    assert(attrs);

    Dmai_clear(fmt);
   
    /* delayStreamon not supported for this platform */
    if (attrs->delayStreamon == TRUE) {
        Dmai_err0("Support for delayed VIDIOC_STREAMON not implemented\n");
        return NULL;
    }
 
    /* Allocate space for state object */
    hDisplay = calloc(1, sizeof(Display_Object));

    if (hDisplay == NULL) {
        Dmai_err0("Failed to allocate space for Display Object\n");
        return NULL;
    }

    hDisplay->userAlloc = TRUE;

    if ((strcmp(attrs->displayDevice, "/dev/video2") != 0) &&
        (strcmp(attrs->displayDevice, "/dev/video3") != 0)) {
        Dmai_err1("%s not a display device\n", attrs->displayDevice);
        cleanup(hDisplay);
        return NULL;
    }

    /* Set up the sysfs variables before opening the display device */
    if (_SysFs_setup(attrs) < 0) {
        cleanup(hDisplay);
        return NULL;
    }

    /* Open video capture device */
    hDisplay->fd = open(attrs->displayDevice, O_RDWR, 0);

    if (hDisplay->fd == -1) {
        Dmai_err2("Cannot open %s (%s)\n",
                  attrs->displayDevice, strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    /* Determine the video image dimensions */
    fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

    if (ioctl(hDisplay->fd, VIDIOC_G_FMT, &fmt) == -1) {
        Dmai_err0("Failed to determine video display format\n");
        cleanup(hDisplay);
        return NULL;
    }

    fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    switch(attrs->colorSpace) {
        case ColorSpace_UYVY: 
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
            break;
        case ColorSpace_YUV420PSEMI:
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
            break;
        case ColorSpace_YUV422PSEMI:
            fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV16;
            break;    
        default:
            Dmai_err1("Unsupported color format %g\n", attrs->colorSpace);            
            cleanup(hDisplay);
            return NULL;
    };

    if (hBufTab == NULL) {
        fmt.fmt.pix.bytesperline =
            Dmai_roundUp(BufferGfx_calcLineLength(fmt.fmt.pix.width, 
                                                  attrs->colorSpace), 32);
        fmt.fmt.pix.sizeimage =
            BufferGfx_calcSize(attrs->videoStd, attrs->colorSpace);
    } else {
        /* This will help user to pass lineLength to display driver. */
        Buffer_Handle hBuf;
        BufferGfx_Dimensions dim;

        hBuf = BufTab_getBuf(hBufTab, 0);
        BufferGfx_getDimensions(hBuf, &dim);
        if((dim.height > fmt.fmt.pix.height) ||
           (dim.width > fmt.fmt.pix.width)) {
            Dmai_err2("User buffer size check failed %dx%d\n", 
                            dim.height, dim.width);
            cleanup(hDisplay);
            return NULL;
        }
        fmt.fmt.pix.bytesperline = dim.lineLength;
        fmt.fmt.pix.sizeimage = Buffer_getSize(hBuf);
    }
    Dmai_dbg4("Video output set to size %dx%d pitch %d imageSize %d\n",
              fmt.fmt.pix.width, fmt.fmt.pix.height, 
              fmt.fmt.pix.bytesperline, fmt.fmt.pix.sizeimage);

    if ((attrs->videoStd == VideoStd_CIF) ||
        (attrs->videoStd == VideoStd_SIF_PAL) || 
        (attrs->videoStd == VideoStd_SIF_NTSC) ||
        (attrs->videoStd == VideoStd_D1_PAL) ||
        (attrs->videoStd == VideoStd_D1_NTSC) ||
        (attrs->videoStd == VideoStd_1080I_30) ||
        (attrs->videoStd == VideoStd_1080I_25)) {
        fmt.fmt.pix.field        = V4L2_FIELD_INTERLACED;
    } else {
        fmt.fmt.pix.field        = V4L2_FIELD_NONE;
    }

    if (ioctl(hDisplay->fd, VIDIOC_S_FMT, &fmt) == -1) {
        Dmai_err2("Failed VIDIOC_S_FMT on %s (%s)\n", attrs->displayDevice,
                                                      strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    /* Should the device driver allocate the display buffers? */
    if (hBufTab == NULL) {
        hDisplay->userAlloc = FALSE;

        if (_Dmai_v4l2DriverAlloc(hDisplay->fd,
                                  attrs->numBufs,
                                  V4L2_BUF_TYPE_VIDEO_OUTPUT,
                                  &hDisplay->bufDescs,
                                  &hBufTab,
                                  0, attrs->colorSpace) < 0) {
            Dmai_err1("Failed to allocate display driver buffers on %s\n",
                      attrs->displayDevice);
            cleanup(hDisplay);
            return NULL;
        }
    }
    else {
        hDisplay->userAlloc = TRUE;

        if (_Dmai_v4l2UserAlloc(hDisplay->fd,
                                attrs->numBufs,
                                V4L2_BUF_TYPE_VIDEO_OUTPUT,
                                &hDisplay->bufDescs,
                                hBufTab,
                                0, attrs->colorSpace) < 0) {
            Dmai_err1("Failed to intialize display driver buffers on %s\n",
                      attrs->displayDevice);
            cleanup(hDisplay);
            return NULL;
        }
    }

    /* Start the video streaming */
    type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

    if (ioctl(hDisplay->fd, VIDIOC_STREAMON, &type) == -1) {
        Dmai_err2("VIDIOC_STREAMON failed on %s (%s)\n", attrs->displayDevice,
                                                         strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    hDisplay->started = TRUE;
    hDisplay->hBufTab = hBufTab;
    hDisplay->displayStd = Display_Std_V4L2;

    return hDisplay;
}

/******************************************************************************
 * Display_v4l2_delete
 ******************************************************************************/
Int Display_v4l2_delete(Display_Handle hDisplay)
{
    Int ret = Dmai_EOK;

    if (hDisplay) {
        ret = cleanup(hDisplay);
    }

    return ret;
}

/******************************************************************************
 * Display_v4l2_get
 ******************************************************************************/
Int Display_v4l2_get(Display_Handle hDisplay, Buffer_Handle *hBufPtr)
{
    struct v4l2_buffer  v4l2buf;

    assert(hDisplay);
    assert(hBufPtr);

    Dmai_clear(v4l2buf);
    v4l2buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    v4l2buf.memory = hDisplay->userAlloc ? V4L2_MEMORY_USERPTR :
                                           V4L2_MEMORY_MMAP;

    /* Get a frame buffer with captured data */
    if(ioctl(hDisplay->fd, VIDIOC_DQBUF, &v4l2buf) < 0) {
        Dmai_err1("VIDIOC_DQBUF failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

    *hBufPtr = hDisplay->bufDescs[v4l2buf.index].hBuf;
    hDisplay->bufDescs[v4l2buf.index].used = TRUE;

    return Dmai_EOK;
}

/******************************************************************************
 * Display_v4l2_put
 ******************************************************************************/
Int Display_v4l2_put(Display_Handle hDisplay, Buffer_Handle hBuf)
{
    Int                  idx;
    BufferGfx_Dimensions dim;
    UInt32               offset;

    assert(hDisplay);
    assert(hBuf);

    idx = getUsedIdx(hDisplay->bufDescs, BufTab_getNumBufs(hDisplay->hBufTab));

    if (idx < 0) {
        Dmai_err0("No v4l2 buffers available\n");
        return Dmai_ENOMEM;
    }

    BufferGfx_getDimensions(hBuf, &dim);
    offset = dim.y * dim.lineLength + 
        dim.x * ColorSpace_getBpp(BufferGfx_getColorSpace(hBuf)) / 8;
    
    hDisplay->bufDescs[idx].v4l2buf.m.userptr = (Int)Buffer_getUserPtr(hBuf) + offset;
    hDisplay->bufDescs[idx].v4l2buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    hDisplay->bufDescs[idx].v4l2buf.length = Buffer_getSize(hBuf);

    /* Issue captured frame buffer back to device driver */
    if (ioctl(hDisplay->fd, VIDIOC_QBUF,
              &hDisplay->bufDescs[idx].v4l2buf) == -1) {
        Dmai_err1("VIDIOC_QBUF failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

    hDisplay->bufDescs[idx].hBuf = hBuf;
    hDisplay->bufDescs[idx].used = FALSE;

    return Dmai_EOK;
}

/******************************************************************************
 * Display_v4l2_control
 ******************************************************************************/
Int Display_v4l2_control(Display_Handle hDisplay, 
                         Display_Control_Message message,
                         void * parameters,
                         BufTab_Handle hBufTab,
                         Display_Attrs *attrs)
{
    return Dmai_EOK;
}
