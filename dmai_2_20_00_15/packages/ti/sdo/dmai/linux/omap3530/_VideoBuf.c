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
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/VideoStd.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "priv/_VideoBuf.h"

#define MODULE_NAME "Dmai"

/* Black color in UYVY format */
#define UYVY_BLACK      0x10801080

/******************************************************************************
 * _Dmai_blackFill
 ******************************************************************************/
Void _Dmai_blackFill(Buffer_Handle hBuf)
{
    switch (BufferGfx_getColorSpace(hBuf)) {
        case ColorSpace_YUV422PSEMI:
        {
            Int8  *yPtr     = Buffer_getUserPtr(hBuf);
            Int32  ySize    = Buffer_getSize(hBuf) / 2;
            Int8  *cbcrPtr  = yPtr + ySize;
            Int32  cbCrSize = Buffer_getSize(hBuf) - ySize;
            Int    i;

            /* Fill the Y plane */
            for (i = 0; i < ySize; i++) {
                yPtr[i] = 0x0;
            }

            for (i = 0; i < cbCrSize; i++) {
                cbcrPtr[i] = 0x80;
            }
            break;
        }

        case ColorSpace_YUV420PSEMI:
        {
            Int8  *bufPtr = Buffer_getUserPtr(hBuf);
            Int    y;
            Int    bpp = ColorSpace_getBpp(ColorSpace_YUV420PSEMI);
            BufferGfx_Dimensions dim;
            
            BufferGfx_getDimensions(hBuf, &dim);

            for (y = 0; y < dim.height; y++) {
                memset(bufPtr, 0x0, dim.width * bpp / 8);
                bufPtr += dim.lineLength;
            }

            for (y = 0; y < (dim.height / 2); y++) {
                memset(bufPtr, 0x80, dim.width * bpp / 8);
                bufPtr += dim.lineLength;
            }
            
            break;
        }

        case ColorSpace_UYVY:
        {
            Int32 *bufPtr  = (Int32*)Buffer_getUserPtr(hBuf);
            Int32  bufSize = Buffer_getSize(hBuf) / sizeof(Int32);
            Int    i;

            /* Make sure display buffer is 4-byte aligned */
            assert((((UInt32) bufPtr) & 0x3) == 0);

            for (i = 0; i < bufSize; i++) {
                bufPtr[i] = UYVY_BLACK;
            }
            break;
        }

        case ColorSpace_RGB565:
        {
            memset(Buffer_getUserPtr(hBuf), 0, Buffer_getSize(hBuf));
            break;
        }

        default:
            Dmai_err0("Unsupported color space for _Dmai_blackFill\n");
            break;
    }
}

/******************************************************************************
 * _Dmai_v4l2UserAlloc
 ******************************************************************************/
Int _Dmai_v4l2UserAlloc(Int fd, Int numBufs, enum v4l2_buf_type type,
                        struct _VideoBufDesc **bufDescsPtr,
                        BufTab_Handle hBufTab, Int topOffset, 
                        ColorSpace_Type colorSpace, Int queueBuffers)
{
    struct v4l2_requestbuffers  req;
    struct v4l2_format          fmt;
    _VideoBufDesc              *bufDesc;
    Buffer_Handle               hBuf;
    Int                         bufIdx;

    Dmai_clear(fmt);
    fmt.type = type;
    if (ioctl(fd, VIDIOC_G_FMT, &fmt) == -1) {
        Dmai_err1("VIDIOC_G_FMT failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

    if (Buffer_getSize(BufTab_getBuf(hBufTab, 0)) <
        fmt.fmt.pix.width * fmt.fmt.pix.height * 2) {
        Dmai_err0("Supplied buffers not large enough for video standard\n");
        return Dmai_EINVAL;
    }
    /* Set the actual size of the buffers allocated */
    fmt.type                 = type;
    fmt.fmt.pix.sizeimage    = Buffer_getSize(BufTab_getBuf(hBufTab, 0));
    fmt.fmt.pix.pixelformat  = V4L2_PIX_FMT_UYVY;
    fmt.fmt.pix.bytesperline = fmt.fmt.pix.width;

    if (ioctl(fd, VIDIOC_S_FMT, &fmt) == -1) {
        Dmai_err1("VIDIOC_S_FMT failed (%s)\n", strerror(errno));
        return Dmai_EIO;
    }
    /*
     * Tell the driver that we will use user allocated buffers, but don't
     * allocate any buffers in the driver (just the internal descriptors).
     */
    Dmai_clear(req);
    req.type   = type;
    req.count  = numBufs; 
    req.memory = V4L2_MEMORY_USERPTR;

    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
        Dmai_err0("Could not allocate video display buffers\n");
        return Dmai_ENOMEM;
    }

    /* The driver may return less buffers than requested */
    if (req.count < numBufs || !req.count) {
        Dmai_err0("Insufficient device driver buffer memory\n");
        return Dmai_ENOMEM;
    }

    /* Allocate space for buffer descriptors */
    *bufDescsPtr = calloc(numBufs, sizeof(_VideoBufDesc));

    if (*bufDescsPtr == NULL) {
        Dmai_err0("Failed to allocate space for buffer descriptors\n");
        return Dmai_ENOMEM;
    }

    for (bufIdx = 0; bufIdx < numBufs; bufIdx++) {
        bufDesc = &(*bufDescsPtr)[bufIdx];
        hBuf = BufTab_getBuf(hBufTab, bufIdx);

        if (hBuf == NULL) {
            Dmai_err0("Failed to get buffer from BufTab for display\n");
            return Dmai_ENOMEM;
        }

        if (Buffer_getType(hBuf) != Buffer_Type_GRAPHICS) {
            Dmai_err0("Buffer supplied to Display not a Graphics buffer\n");
            return Dmai_EINVAL;
        }

        Dmai_clear(bufDesc->v4l2buf);
        bufDesc->v4l2buf.index     = bufIdx;
        bufDesc->v4l2buf.type      = type;
        bufDesc->v4l2buf.memory    = V4L2_MEMORY_USERPTR;
        bufDesc->v4l2buf.m.userptr = (UInt32) Buffer_getUserPtr(hBuf);
        bufDesc->v4l2buf.length    = (fmt.fmt.pix.sizeimage + 4096) & (~0xFFF);
        bufDesc->hBuf              = hBuf;
        bufDesc->used              = (queueBuffers == FALSE) ? TRUE : FALSE;

        /* If queueBuffers is TRUE, initialize the buffers to black and queue
         * them into the driver.
         */
        if (queueBuffers == TRUE) {
            Buffer_setNumBytesUsed(hBuf, Buffer_getSize(hBuf));
            _Dmai_blackFill(hBuf);

            /* Queue buffer in device driver */
            if (ioctl(fd, VIDIOC_QBUF, &bufDesc->v4l2buf) == -1) {
                Dmai_err1("VIODIC_QBUF failed (%s)\n", strerror(errno));
                return Dmai_EFAIL;
            }
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * _Dmai_v4l2DriverAlloc
 ******************************************************************************/
Int _Dmai_v4l2DriverAlloc(Int fd, Int numBufs, enum v4l2_buf_type type,
                          struct _VideoBufDesc **bufDescsPtr,
                          BufTab_Handle *hBufTabPtr, Int topOffset, 
                          ColorSpace_Type colorSpace)
{
    BufferGfx_Attrs             gfxAttrs = BufferGfx_Attrs_DEFAULT;
    struct v4l2_requestbuffers  req;
    struct v4l2_format          fmt;
    _VideoBufDesc              *bufDesc;
    Buffer_Handle               hBuf;
    Int                         bufIdx;
    Int8                       *virtPtr;

    Dmai_clear(fmt);
    fmt.type = type;

    if (ioctl(fd, VIDIOC_G_FMT, &fmt) == -1) {
        Dmai_err1("VIDIOC_G_FMT failed (%s)\n", strerror(errno));
        return Dmai_EFAIL;
    }

    Dmai_clear(req);
    req.count  = numBufs;
    req.type   = type;
    req.memory = V4L2_MEMORY_MMAP;

    /* Allocate buffers in the capture device driver */
    if (ioctl(fd, VIDIOC_REQBUFS, &req) == -1) {
        Dmai_err1("VIDIOC_REQBUFS failed (%s)\n", strerror(errno));
        return Dmai_ENOMEM;
    }

    if (req.count < numBufs || !req.count) {
        Dmai_err0("Insufficient device driver buffer memory\n");
        return Dmai_ENOMEM;
    }

    /* Allocate space for buffer descriptors */
    *bufDescsPtr = calloc(numBufs, sizeof(_VideoBufDesc));

    if (*bufDescsPtr == NULL) {
        Dmai_err0("Failed to allocate space for buffer descriptors\n");
        return Dmai_ENOMEM;
    }

    gfxAttrs.dim.width          = fmt.fmt.pix.width;
    gfxAttrs.dim.height         = fmt.fmt.pix.height;
    gfxAttrs.dim.lineLength     = fmt.fmt.pix.bytesperline;
    gfxAttrs.colorSpace         = colorSpace;
    gfxAttrs.bAttrs.reference   = TRUE;

    *hBufTabPtr = BufTab_create(numBufs, fmt.fmt.pix.sizeimage,
                                BufferGfx_getBufferAttrs(&gfxAttrs));

    if (*hBufTabPtr == NULL) {
        return Dmai_ENOMEM;
    }

    for (bufIdx = 0; bufIdx < numBufs; bufIdx++) {
        bufDesc = &(*bufDescsPtr)[bufIdx];

        /* Ask for information about the driver buffer */
        Dmai_clear(bufDesc->v4l2buf);
        bufDesc->v4l2buf.type   = type;
        bufDesc->v4l2buf.memory = V4L2_MEMORY_MMAP;
        bufDesc->v4l2buf.index  = bufIdx;

        if (ioctl(fd, VIDIOC_QUERYBUF, &bufDesc->v4l2buf) == -1) {
            Dmai_err1("Failed VIDIOC_QUERYBUF (%s)\n", strerror(errno));
            return Dmai_EFAIL;
        }

        /* Map the driver buffer to user space */
        virtPtr = mmap(NULL,
                       bufDesc->v4l2buf.length,
                       PROT_READ | PROT_WRITE,
                       MAP_SHARED,
                       fd,
                       bufDesc->v4l2buf.m.offset) + topOffset;

        if (virtPtr == MAP_FAILED) {
            Dmai_err1("Failed to mmap buffer (%s)\n", strerror(errno));
            return Dmai_EFAIL;
        }

        /* Initialize the Buffer with driver buffer information */
        hBuf = BufTab_getBuf(*hBufTabPtr, bufIdx);

        Buffer_setNumBytesUsed(hBuf, fmt.fmt.pix.bytesperline *
                                     fmt.fmt.pix.height);
        Buffer_setUseMask(hBuf, gfxAttrs.bAttrs.useMask);
        Buffer_setUserPtr(hBuf, virtPtr);

        /* Initialize buffer to black */
        _Dmai_blackFill(hBuf);

        Dmai_dbg3("Driver buffer %d mapped to %#x has physical address "
                  "%#lx\n", bufIdx, (Int) virtPtr, Buffer_getPhysicalPtr(hBuf));

        bufDesc->hBuf = hBuf;

        /* Queue buffer in device driver */
        if (ioctl(fd, VIDIOC_QBUF, &bufDesc->v4l2buf) == -1) {
            Dmai_err1("VIODIOC_QBUF failed (%s)\n", strerror(errno));
            return Dmai_EFAIL;
        }
    }

    return Dmai_EOK;
}
