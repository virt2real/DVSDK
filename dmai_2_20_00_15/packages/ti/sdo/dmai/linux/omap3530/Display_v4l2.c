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
    struct v4l2_requestbuffers  req;

    if (hDisplay->fd != -1) {
        if (hDisplay->started) {
            /* Shut off the video display */
            type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

            if (ioctl(hDisplay->fd, VIDIOC_STREAMOFF, &type) == -1) {
                Dmai_err1("VIDIOC_STREAMOFF failed (%s)\n", strerror(errno));
                ret = Dmai_EFAIL;
            }
        }

        if (close(hDisplay->fd) == -1) {
            Dmai_err1("Failed to close display device (%s)\n", strerror(errno));
            ret = Dmai_EIO;
        }

        if (hDisplay->userAlloc == FALSE) {
            if (hBufTab) {
                for (bufIdx = 0;
                     bufIdx < BufTab_getNumBufs(hBufTab);
                     bufIdx++) {

                    hDispBuf = BufTab_getBuf(hBufTab, bufIdx);

                    if (munmap(Buffer_getUserPtr(hDispBuf),
                               (hDisplay->bufDescs[bufIdx].v4l2buf.length))
                                == -1) {
                        Dmai_err1("Failed to unmap display buffer%d\n", bufIdx);
                        ret = Dmai_EFAIL;
                    }
                }
            }
        }
        else {
            Dmai_clear(req);
            req.type   = V4L2_BUF_TYPE_VIDEO_OUTPUT;
            req.count  = 0;
            req.memory = V4L2_MEMORY_USERPTR;
            if (ioctl(hDisplay->fd, VIDIOC_REQBUFS, &req) == -1) {
                Dmai_err0("Could not allocate video display buffers\n");
                return Dmai_ENOMEM;
            }
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
    Int32                      width, height;
#if defined(V4L2_CID_ROTATE)
    struct v4l2_control        control;
#endif
    assert(attrs);

    /* Allocate space for state object */
    hDisplay = calloc(1, sizeof(Display_Object));

    if (hDisplay == NULL) {
        Dmai_err0("Failed to allocate space for Display Object\n");
        return NULL;
    }

    /* Setup sysfs variable */
    if (_SysFs_change(&attrs->videoOutput, attrs->displayDevice,
                      &attrs->videoStd, &attrs->rotation) < 0) {
        Dmai_err0("Failed to setup sysfs variables\n");
        return NULL;
    }
    hDisplay->userAlloc = TRUE;
    hDisplay->attrs     = *attrs;

    /* Open video capture device */
    hDisplay->fd = open(attrs->displayDevice, O_RDWR, 0);

    if (hDisplay->fd == -1) {
        Dmai_err2("Cannot open %s (%s)\n",
                  attrs->displayDevice, strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }
    
#if defined(V4L2_CID_ROTATE)
    /* Make rotation by default 0 for DVI and S-video*/

    if (attrs->videoOutput == Display_Output_LCD) {
        if (attrs->rotation == 0 || attrs->rotation == 90 ||
            attrs->rotation == 180 || attrs->rotation == 270) {

            control.value = attrs->rotation;
        }
    }
    else {
        attrs->rotation = 0;
        control.value = attrs->rotation;
    }

    /* Enable hardware rotation */
    control.id    = V4L2_CID_ROTATE;

    if (ioctl(hDisplay->fd, VIDIOC_S_CTRL, &control) == -1) {
        Dmai_err0("Failed to set rotation angle\n");
        cleanup(hDisplay);
        return NULL;
    }
#endif
    /* Determine the video image dimensions */   
   switch(attrs->videoStd) {
        case VideoStd_CIF:
            width = VideoStd_CIF_WIDTH;
            height = VideoStd_CIF_HEIGHT;
            break;
        case VideoStd_SIF_NTSC:
            width = VideoStd_SIF_WIDTH;
            height = VideoStd_SIF_NTSC_HEIGHT;
            break;
        case VideoStd_SIF_PAL:
            width = VideoStd_SIF_WIDTH;
            height = VideoStd_SIF_PAL_HEIGHT;
            break;
        case VideoStd_VGA:
            width = VideoStd_VGA_WIDTH;
            height = VideoStd_VGA_HEIGHT;        
            break;
        case VideoStd_D1_NTSC:
            width = VideoStd_D1_WIDTH;
            height = VideoStd_D1_NTSC_HEIGHT;
            break;
        case VideoStd_D1_PAL:
            width = VideoStd_D1_WIDTH;
            height = VideoStd_D1_PAL_HEIGHT;
            break;
        case VideoStd_480P:
            width = VideoStd_480P_WIDTH;
            height = VideoStd_480P_HEIGHT;
            break;
        case VideoStd_576P:
            width = VideoStd_576P_WIDTH;
            height = VideoStd_576P_HEIGHT;
            break;
        case VideoStd_720P_60:
            width = VideoStd_720P_WIDTH;
            height = VideoStd_720P_HEIGHT;
            break;
        default:
            break;
    }

    /* If width and height is specified then use those values */
    if (attrs->width > 0) {
        width = attrs->width;   
    }

    if (attrs->height > 0) {
        height = attrs->height;   
    }

    fmt.fmt.pix.width = width;
    fmt.fmt.pix.height = height;  
    fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
    fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
    
    if (ioctl(hDisplay->fd, VIDIOC_S_FMT, &fmt) == -1) {
        Dmai_err0("Failed to Set video display format\n");
        cleanup(hDisplay);
        return NULL;
    }

    if (ioctl(hDisplay->fd, VIDIOC_G_FMT, &fmt) == -1) {
        Dmai_err0("Failed to determine video display format\n");
        cleanup(hDisplay);
        return NULL;
    }

    Dmai_dbg4("Video output set to size %dx%d pitch %d, Format %d\n",
              fmt.fmt.pix.width, fmt.fmt.pix.height,
              fmt.fmt.pix.bytesperline, fmt.fmt.pix.pixelformat);

    /* Should the device driver allocate the display buffers? */
    if (attrs->streamonDisable == TRUE) {
      /* do nothing */
    }
    else {
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
            if (attrs->delayStreamon == FALSE) {
                if (_Dmai_v4l2UserAlloc(hDisplay->fd, attrs->numBufs,
                    V4L2_BUF_TYPE_VIDEO_OUTPUT, &hDisplay->bufDescs, hBufTab, 0,
                    attrs->colorSpace, !attrs->delayStreamon) < 0) {
                    Dmai_err1("Failed to allocate display driver buffers on %s\n",
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
    }

    return hDisplay;
}

/******************************************************************************
 * _Display_v4l2_streamon (INTERNAL)
 ******************************************************************************/
static Int _Display_v4l2_streamon(Display_Handle hDisplay)
{
    enum v4l2_buf_type type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
   
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
    Int idx;

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
    assert(hDisplay);
    assert(parameters);
    struct v4l2_format             *fmt;
    enum v4l2_buf_type              type;
    fmt = (struct v4l2_format *)    parameters;

    switch(message) {
        case Display_Control_V4L2_Overlay_FMT:
        /* Set the overlay parameters*/
            fmt->type = V4L2_BUF_TYPE_VIDEO_OVERLAY;
            if (ioctl(hDisplay->fd, VIDIOC_S_FMT, fmt) < 0) {
                Dmai_err1("VIDIOC_S_FMT (OVERLAY) failed (%s)\n",
                          strerror(errno));
                return Dmai_EIO;
            }
            break;

        case Display_Control_V4L2_Output_FMT:
        /* Set the output parameters*/
            fmt->type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
            if (ioctl(hDisplay->fd, VIDIOC_S_FMT, fmt) < 0) {
                Dmai_err1("VIDIOC_S_FMT (OUTPUT) failed (%s)\n",
                          strerror(errno));
                return Dmai_EIO;
            }
            if (ioctl(hDisplay->fd, VIDIOC_G_FMT, fmt) == -1) {
                Dmai_err0("Failed to determine video display format\n");
                cleanup(hDisplay);
                return NULL;
            }

            Dmai_dbg4("Video output set to size %dx%d pitch %d, Format %d\n",
                      fmt->fmt.pix.width, fmt->fmt.pix.height,
                      fmt->fmt.pix.bytesperline, fmt->fmt.pix.pixelformat);
            break;

        case Display_Control_V4L2_Streamoff:
        /* Stop streaming*/
            if (hDisplay->started) {
                attrs->streamonDisable = TRUE;
                type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

                if (ioctl(hDisplay->fd, VIDIOC_STREAMOFF, &type) < 0) {
                    Dmai_err1("VIDIOC_STREAMOFF failed (%s)\n",
                              strerror(errno));
                    return Dmai_EFAIL;
                }
            } 
            break;

        case Display_Control_V4L2_Qbuf:
        /* Queue the buffers before streaming*/
             attrs->streamonDisable = FALSE;
            if (_Dmai_v4l2UserAlloc(hDisplay->fd,
                             attrs->numBufs,
                             V4L2_BUF_TYPE_VIDEO_OUTPUT,
                             &hDisplay->bufDescs,
                             hBufTab,
                             0, attrs->colorSpace, TRUE) < 0) {
                Dmai_err1("Failed to allocate display driver buffers on %s\n",
                          attrs->displayDevice);
                cleanup(hDisplay);
                return NULL;
            }

            hDisplay->hBufTab = hBufTab;
            hDisplay->started = TRUE;
            hDisplay->displayStd = Display_Std_V4L2;
            break;

        case Display_Control_V4L2_Streamon:
        /* Start the video streaming */
            type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

            if (ioctl(hDisplay->fd, VIDIOC_STREAMON, &type) == -1) {
                Dmai_err2("VIDIOC_STREAMON failed on %s (%s)\n",
                          attrs->displayDevice, strerror(errno));
                cleanup(hDisplay);
                return NULL;
            }

            hDisplay->started = TRUE;
            hDisplay->hBufTab = hBufTab;
            hDisplay->displayStd = Display_Std_V4L2;
            break;

        default:
            Dmai_dbg1("Unsupported Message in Display_v4l2_control: %d\n", 
                message);            
    }    

    return Dmai_EOK;
}

