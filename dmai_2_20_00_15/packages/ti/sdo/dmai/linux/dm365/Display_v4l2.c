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
#include <media/davinci/davinci_display.h>
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

#include "priv/_VideoBuf.h"
#include "../priv/_Display.h"
#include "priv/_SysFs.h"

#define MODULE_NAME     "Display"

/* Static Functions */
static Int _Display_v4l2_streamon(Display_Handle hDisplay);
static Int _Display_v4l2_set_frame_offsets(Display_Handle hDisplay,
               Buffer_Handle hBuf);

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
    Display_Handle             hDisplay;
    BufferGfx_Dimensions       dim;
    Buffer_Handle              hBuf;

    assert(attrs);

    Dmai_clear(fmt);
    
    /* Allocate space for state object */
    hDisplay = calloc(1, sizeof(Display_Object));

    if (hDisplay == NULL) {
        Dmai_err0("Failed to allocate space for Display Object\n");
        return NULL;
    }

    hDisplay->userAlloc = TRUE;
    hDisplay->attrs     = *attrs;

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

    if (attrs->width > 0) {
        if (attrs->width <= fmt.fmt.pix.width)
            fmt.fmt.pix.width = attrs->width;
    }

    if (attrs->height > 0) {
        if (attrs->height <= fmt.fmt.pix.height)
            fmt.fmt.pix.height = attrs->height;
    }
    
    if (hBufTab == NULL) {
        VideoStd_getResolution(attrs->videoStd, &dim.width, &dim.height);
        dim.lineLength = 
            Dmai_roundUp(BufferGfx_calcLineLength(fmt.fmt.pix.width,
                                                  attrs->colorSpace), 32);
        fmt.fmt.pix.bytesperline = dim.lineLength;
        fmt.fmt.pix.sizeimage = BufferGfx_calcSizeDim(&dim, attrs->colorSpace);
    } else {
        hBuf = BufTab_getBuf(hBufTab, 0);
        BufferGfx_getDimensions(hBuf, &dim);
        fmt.fmt.pix.bytesperline = dim.lineLength;
        fmt.fmt.pix.sizeimage = Buffer_getSize(hBuf);
    }

    Dmai_dbg4("Video output set to size %dx%d pitch %d imageSize %d\n",
              fmt.fmt.pix.width, fmt.fmt.pix.height, 
              fmt.fmt.pix.bytesperline, fmt.fmt.pix.sizeimage);

    if ((attrs->videoStd == VideoStd_CIF) || (attrs->videoStd == VideoStd_SIF_PAL) || 
        (attrs->videoStd == VideoStd_SIF_NTSC) || (attrs->videoStd == VideoStd_D1_PAL) ||
        (attrs->videoStd == VideoStd_D1_NTSC) || (attrs->videoStd == VideoStd_1080I_30) ||
        (attrs->videoStd == VideoStd_1080I_25) || (attrs->videoStd == VideoStd_1080P_30) ||
        (attrs->videoStd == VideoStd_1080I_60)) {
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

        if (attrs->delayStreamon == FALSE) {
            if (_Dmai_v4l2UserAlloc(hDisplay->fd, attrs->numBufs,
                V4L2_BUF_TYPE_VIDEO_OUTPUT, &hDisplay->bufDescs, hBufTab, 0,
                hDisplay->attrs.colorSpace, !attrs->delayStreamon) < 0) {
                Dmai_err1("Failed to intialize display driver buffers on %s\n",
                          attrs->displayDevice);
                cleanup(hDisplay);
                return NULL;
            }
        }
    }

    /* If delayStreamon == FALSE, start the display now */
    if (attrs->delayStreamon == FALSE) {
        if (_Display_v4l2_streamon(hDisplay) != Dmai_EOK) {
            Dmai_err2("VIDIOC_STREAMON failed on %s (%s)\n",
                attrs->displayDevice, strerror(errno));
            cleanup(hDisplay);
            return NULL;
        }
    }

    hDisplay->hBufTab = hBufTab;
    hDisplay->displayStd = Display_Std_V4L2;

    return hDisplay;
}

/******************************************************************************
 * _Display_v4l2_set_framerate (INTERNAL)
 ******************************************************************************/
static Int _Display_v4l2_set_framerate(Display_Handle hDisplay)
{
    struct v4l2_streamparm parms;
   
    /* If a framerate was not specified, do nothing */
    if (hDisplay->attrs.forceFrameRateNum == 0) {
        return Dmai_EOK;
    }

    parms.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    if (ioctl(hDisplay->fd, VIDIOC_G_PARM, &parms) == -1) {
        Dmai_err1("VIDIOC_G_PARM failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

    if (!(parms.parm.output.capability & V4L2_CAP_TIMEPERFRAME)) {
        Dmai_err0("Setting framerate is not supported by driver\n");
        return Dmai_EFAIL;
    }

    parms.parm.output.timeperframe.numerator =
        hDisplay->attrs.forceFrameRateNum;
    parms.parm.output.timeperframe.denominator =
        hDisplay->attrs.forceFrameRateDen;

    if (ioctl(hDisplay->fd, VIDIOC_S_PARM, &parms) == -1) {
        Dmai_err1("VIDIOC_S_PARM failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

    if (parms.parm.output.timeperframe.numerator !=
            hDisplay->attrs.forceFrameRateNum ||
        parms.parm.output.timeperframe.denominator !=
            hDisplay->attrs.forceFrameRateDen) {
        Dmai_err0("driver did not honor specified framerate\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * _Display_v4l2_streamon (INTERNAL)
 ******************************************************************************/
static Int _Display_v4l2_streamon(Display_Handle hDisplay)
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
   
    /* If a framerate was specified, set it in the driver */
    if (_Display_v4l2_set_framerate(hDisplay) != Dmai_EOK) {
        return Dmai_EFAIL;
    }

    if (ioctl(hDisplay->fd, VIDIOC_STREAMON, &type) == -1) {
        return Dmai_EFAIL;
    }
   
    hDisplay->started = TRUE;
    return Dmai_EOK;
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

    assert(hDisplay);
    assert(hBuf);

    /* If the display hasn't been started yet, then the V4L2 data structures
     * haven't been initialized yet either.  Initialize them now.
     */
    if (!hDisplay->started) {
        if (_Dmai_v4l2UserAlloc(hDisplay->fd,
            BufTab_getNumBufs(hDisplay->hBufTab), V4L2_BUF_TYPE_VIDEO_OUTPUT,
            &hDisplay->bufDescs, hDisplay->hBufTab, 0,
            hDisplay->attrs.colorSpace, FALSE) < 0) {
            Dmai_err0("Failed to intialize display driver buffers\n");
            return Dmai_EFAIL;
        }
    }

    idx = getUsedIdx(hDisplay->bufDescs, BufTab_getNumBufs(hDisplay->hBufTab));

    if (idx < 0) {
        Dmai_err0("No v4l2 buffers available\n");
        return Dmai_ENOMEM;
    }

    hDisplay->bufDescs[idx].v4l2buf.m.userptr = (Int)Buffer_getUserPtr(hBuf);
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

    /* If the display was not started during display creation, start it now */
    if (!hDisplay->started) {
        if (_Display_v4l2_streamon(hDisplay) != Dmai_EOK) {
            Dmai_err1("VIDIOC_STREAMON failed (%s)\n", strerror(errno));
            return Dmai_EFAIL;
        }

        if (_Display_v4l2_set_frame_offsets(hDisplay, hBuf) != Dmai_EOK) {
            return Dmai_EFAIL;
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * _Display_v4l2_set_frame_offsets
 ******************************************************************************/
static Int _Display_v4l2_set_frame_offsets(Display_Handle hDisplay,
               Buffer_Handle hBuf)
{
    BufferGfx_Dimensions dim;
    unsigned long cbcrOffset;
    unsigned long ydOffset;

    BufferGfx_getDimensions(hBuf, &dim);

    /* Calculate the offset of the C-plane from the beginning of the buffer.
     * For H.264 and MPEG-4 it comes right after the Y-plane, but you need to
     * account for the codec padding in the Y-plane.  For MPEG-2, there is
     * padding between the Y-plane and C-plane.  In *all* cases, the C plane is
     * at the end of the buffer.
     * 
     * To handle all three currently known codecs, right now the best we can do
     * to calculate the C-plane offset is to calculate its size, assume it is
     * at the end of the buffer, and calculate what the offset is from the
     * beginning.  Then call VIDIOC_S_COFST with the result.
     */
    if (hDisplay->attrs.colorSpace == ColorSpace_YUV420PSEMI) {
        cbcrOffset = (Buffer_getSize(hBuf) * 2 / 3);

        if (ioctl(hDisplay->fd, VIDIOC_S_COFST, &cbcrOffset) == -1) {
            Dmai_err1("VIDIOC_S_COFST failed (%s)\n", strerror(errno));
            return Dmai_EFAIL;
        }
    }

    /* If dim.y > 0, then there is padding at the top of the frame.  We call
     * VIDIOC_S_YDOFST with the size of the padding.  This will instruct the
     * display driver to start the display at the specified offset, which
     * should cause the padding to be cropped.
     *
     * This value must be aligned to a 64-byte boundary, so we might not always
     * hit the offset we're after dead-on.  However, in most cases we can get
     * close enough, as most displays crop a little of the edges anyway.
     */
    ydOffset = dim.y * dim.lineLength;

    if (ydOffset & 0x3F) {
        Dmai_err1("ydOffset is not 64-byte aligned (%lu)\n", ydOffset);
        return Dmai_EFAIL;
    }

    if (ioctl(hDisplay->fd, VIDIOC_S_YDOFST, &ydOffset) == -1) {
        Dmai_err1("VIDIOC_S_YDOFST failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

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

