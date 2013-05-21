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
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Framecopy.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "../../priv/_Framecopy.h"

#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
#include <linux/omap_resizer.h>
#include <linux/videodev.h>
#endif

#define MODULE_NAME     "Framecopy"

#define RESIZER_DEVICE  "/dev/omap-resizer"
#define FIR_RND_SCALE   256
#define NUM_COEFS       32
#define SCREEN_BPP      16

typedef struct Framecopy_Object {
    Framecopy_CommonObject  common;
    Int                     fd;
    Int32                   inSize;
    Int32                   outSize;
} Framecopy_Object;

/******************************************************************************
 * Framecopy_resizer_accel_config
 ******************************************************************************/
Int Framecopy_resizer_accel_config(Framecopy_Handle hFc,
                           Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    struct v4l2_requestbuffers reqbuf;
    Int rszRate;
    BufferGfx_Dimensions srcDim, dstDim;
    struct rsz_params  params = {
        0,                              /* in_hsize (set at run time) */
        0,                              /* in_vsize (set at run time) */
        0,                              /* in_pitch (set at run time) */
        RSZ_INTYPE_YCBCR422_16BIT,      /* inptyp */
        0,                              /* vert_starting_pixel */
        0,                              /* horz_starting_pixel */
        0,                              /* cbilin */
        RSZ_PIX_FMT_UYVY,               /* pix_fmt */
        0,                              /* out_hsize (set at run time) */
        0,                              /* out_vsize (set at run time) */
        0,                              /* out_pitch (set at run time) */
        0,                              /* hstph */
        0,                              /* vstph */
        {                               /* hfilt_coeffs */
            256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0,
            256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0
        },
        {                               /* vfilt_coeffs */
            256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0,
            256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0
        },
        {                               /* yenh_params */
            0,                              /* type */
            0,                              /* gain */
            0,                              /* slop */
            0                               /* core */
        }
    };

    /* Pointers must be a multiple of 4096 bytes */
    assert((Buffer_getPhysicalPtr(hDstBuf) & 0xFFF) == 0);
    assert((Buffer_getPhysicalPtr(hSrcBuf) & 0xFFF) == 0);

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    Dmai_dbg2("Configuring resizer to copy image of resolution %dx%d\n",
              srcDim.width, srcDim.height);

    /* Source and destination pitch must be 32 bytes aligned */
    if (srcDim.lineLength % 32 || dstDim.lineLength % 32) {
        Dmai_err2("Src (%ld) and dst (%ld) must be aligned on 32 bytes\n",
                  srcDim.lineLength, dstDim.lineLength);
        return Dmai_EINVAL;
    }

    /* Set up the copy job */
    params.in_hsize            = srcDim.width;
    params.in_vsize            = srcDim.height;
    params.in_pitch            = srcDim.lineLength;
    params.out_hsize           = dstDim.width;
    params.out_vsize           = dstDim.height;
    params.out_pitch           = dstDim.lineLength;
    params.cbilin              = 0;
    params.pix_fmt             = RSZ_PIX_FMT_UYVY;
    params.vert_starting_pixel = 0;
    params.horz_starting_pixel = 0;
    params.inptyp              = RSZ_INTYPE_YCBCR422_16BIT;
    params.hstph               = 0;
    params.vstph               = 0;
    params.yenh_params.type    = 0;
    params.yenh_params.gain    = 0;
    params.yenh_params.slop    = 0;
    params.yenh_params.core    = 0;

    hFc->inSize  = srcDim.lineLength * params.in_vsize;
    hFc->outSize = dstDim.lineLength * params.out_vsize;

    if (ioctl(hFc->fd, RSZ_S_PARAM, &params) == -1) {
        Dmai_err0("Framecopy setting parameters failed.\n");
        return Dmai_EFAIL;
    }

    rszRate = 0x0;

    if (ioctl(hFc->fd, RSZ_S_EXP, &rszRate) == -1) {
        Dmai_err0("Framecopy setting read cycle failed.\n");
        return Dmai_EFAIL;
    }

    reqbuf.type     = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory   = V4L2_MEMORY_USERPTR;
    reqbuf.count    = 2;

    if (ioctl(hFc->fd, RSZ_REQBUF, &reqbuf) == -1) {
        Dmai_err0("Request buffer failed.\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}

/******************************************************************************
 * Framecopy_resizer_accel_create
 ******************************************************************************/
Framecopy_Handle Framecopy_resizer_accel_create(Framecopy_Attrs *attrs)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    Framecopy_Handle hFc;

    Dmai_dbg0("Creating resizer accelerated framecopy\n");

    hFc = (Framecopy_Handle)calloc(1, sizeof(Framecopy_Object));

    if (hFc == NULL) {
        Dmai_err0("Failed to allocate space for Framecopy Object\n");
        return NULL;
    }

    /* Open resizer device */
    hFc->fd = open(RESIZER_DEVICE, O_RDWR);

    if (hFc->fd == -1) {
        Dmai_err1("Failed to open %s\n", RESIZER_DEVICE);
        return NULL;
    }

    return hFc;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}

/******************************************************************************
 * Framecopy_resizer_accel_execute
 ******************************************************************************/
Int Framecopy_resizer_accel_execute(Framecopy_Handle hFc,
                                    Buffer_Handle hSrcBuf,
                                    Buffer_Handle hDstBuf)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    Int         i;
    struct      v4l2_buffer qbuf[2];

    assert(hFc);
    assert(hSrcBuf);
    assert(hDstBuf);

    /* Pointers must be a multiple of 32 bytes */
    assert((Buffer_getPhysicalPtr(hDstBuf) & 0x1F) == 0);
    assert((Buffer_getPhysicalPtr(hSrcBuf) & 0x1F) == 0);

    /* Queue the resizer buffers */
    for (i=0; i < 2; i++) { 

        qbuf[i].type         = V4L2_BUF_TYPE_VIDEO_CAPTURE;
        qbuf[i].memory       = V4L2_MEMORY_USERPTR;
        qbuf[i].index        = i;

        if (ioctl (hFc->fd, RSZ_QUERYBUF, &qbuf[i]) == -1) {
            Dmai_err1("Failed to query buffer index %d\n", i);
            return Dmai_EFAIL;
        }

        if (i == 0) {
            qbuf[i].m.userptr = (unsigned long) Buffer_getUserPtr(hSrcBuf);
        }
        else {
            qbuf[i].m.userptr = (unsigned long) Buffer_getUserPtr(hDstBuf);
        }

        if (ioctl (hFc->fd, RSZ_QUEUEBUF, &qbuf[i]) == -1) {
            Dmai_err1("Failed to queue buffer index %d\n",i);
            return Dmai_EFAIL;
        }
    }

    if (ioctl(hFc->fd, RSZ_RESIZE, NULL) == -1) {
        Dmai_err0("Failed to execute resize job\n");
        return Dmai_EFAIL;
    }

    Buffer_setNumBytesUsed(hDstBuf, Buffer_getNumBytesUsed(hSrcBuf));

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}

/******************************************************************************
 * Framecopy_resizer_accel_delete
 ******************************************************************************/
Int Framecopy_resizer_accel_delete(Framecopy_Handle hFc)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    if (hFc->fd > 0) {
        close(hFc->fd);
    }

    free(hFc);

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}
