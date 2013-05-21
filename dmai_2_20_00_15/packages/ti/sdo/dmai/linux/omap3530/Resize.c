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

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/Resize.h>

/* Define CONFIG_VIDEO_OMAP34XX_ISP_RESIZER to enable resizer support */
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
#include <linux/omap_resizer.h>
#include <linux/videodev.h>
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */

/*
 * If PRECALC is set, a lookup table will be used for calculating sinus
 * and cosinus values instead of calling the math library. If you change this
 * define, note that you will have to set the define in
 * linux/dm6446/Resize_precalc.c accordingly.
 */
#define PRECALC

#ifdef PRECALC
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
#define _PI 3.14159265358979323846
extern Float Resize_sinFloat[];

/******************************************************************************
 * _sin
 ******************************************************************************/
static inline Float _sin(Float x)
{
    Int d;

    /* Scale and round up for positive values and down for negative values */
    d = x < 0 ? ((Float) x * 256 / _PI - 0.5) : ((Float) x * 256 / _PI + 0.5);

    /* Make "degrees" positive by adding 2 * pi */
    while (d < 0) d += 512;

    /* Cut "degrees" at 2 * pi */
    d &= 0x1ff;

    return Resize_sinFloat[d];
}

/******************************************************************************
 * _cos
 ******************************************************************************/
static inline Float _cos(Float x)
{
    Int d;

    /* Scale and round up for positive values and down for negative values */
    d = x < 0 ? ((Float) x * 256 / _PI - 0.5) : ((Float) x * 256 / _PI + 0.5);

    /* Make "degrees" positive by adding 2 * pi */
    while (d < 0) d += 512;

    /* Cut "degrees" at 2 * pi */
    d &= 0x1ff;

    /* Cosinus is "90 degrees" = 128 phase shifted from the sinus value */
    return Resize_sinFloat[d + 128];
}

/******************************************************************************
 * _abs
 ******************************************************************************/
static inline Int _abs(Int x)
{
    return x < 0 ? -x : x;
}

#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
#else
#include <math.h>
#define _PI M_PI
#define _cos(x) cos(x)
#define _sin(x) sin(x)
#define _abs(x) abs(x)
#endif

#define MODULE_NAME     "Resize"

#define RESIZER_DEVICE  "/dev/omap-resizer"
#define NUM_COEFS       32
#define COEF(nr, dr)   ((short)(((nr)*(int)QMUL)/(dr)))
#define RDRV_RESZ_SPEC__MAX_FILTER_COEFF 32
#define QMUL  (0x100)

typedef struct Resize_Object {
    Int                 fd;
    Resize_WindowType   hWindowType;
    Resize_WindowType   vWindowType;
    Resize_FilterType   hFilterType;
    Resize_FilterType   vFilterType;
    Int32               inSize;
    Int32               outSize;
} Resize_Object;

const Resize_Attrs Resize_Attrs_DEFAULT = {
    Resize_FilterType_LOWPASS,
    Resize_FilterType_LOWPASS,
    Resize_WindowType_BLACKMAN,
    Resize_WindowType_BLACKMAN,
    0xe
};

/* For resizing between */
short gRDRV_reszFilter4TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF]= {
        0, 256, 0, 0, -6, 246, 16, 0, -7, 219, 44, 0, -5, 179, 83, -1, -3,
        130, 132, -3, -1, 83, 179, -5, 0, 44, 219, -7, 0, 16, 246, -6
};

short gRDRV_reszFilter7TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF] = {
        -1, 19, 108, 112, 19, -1, 0, 0, 0, 6, 88, 126, 37, -1, 0, 0,
        0, 0, 61, 134, 61, 0, 0, 0, 0, -1, 37, 126, 88, 6, 0, 0
};

/******************************************************************************
 * Resize_create
 ******************************************************************************/
Resize_Handle Resize_create(Resize_Attrs *attrs)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    Resize_Handle hResize;

    hResize = calloc(1, sizeof(Resize_Object));

    if (hResize == NULL) {
        Dmai_err0("Failed to allocate space for Resize Object\n");
        return NULL;
    }

    /* Open resizer device */
    hResize->fd = open(RESIZER_DEVICE, O_RDWR);

    if (hResize->fd == -1) {
        Dmai_err1("Failed to open %s\n", RESIZER_DEVICE);
        Resize_delete(hResize);
        return NULL;
    }

    hResize->hWindowType = attrs->hWindowType;
    hResize->vWindowType = attrs->vWindowType;
    hResize->hFilterType = attrs->hFilterType;
    hResize->vFilterType = attrs->vFilterType;

    return hResize;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}

#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
/******************************************************************************
 * estimateRsz
 ******************************************************************************/
static Int estimateRsz(Int src, Int dst)
{
    Int rsz;

    /* Estimate rsz */
    rsz = ((src - 7) * 256 - 16) / (dst - 1);

    /* Recalculate rsz if 8-phase 4-tap */
    if (rsz <= 512) {
        rsz = ((src - 4) * 256 - 16) / (dst - 1);

        if (rsz > 512) {
            rsz = 512;
        }
    }

    return rsz;
}

/******************************************************************************
 * calcSrcSize
 ******************************************************************************/
static Int calcSrcSize(Int dst, Int rsz)
{
    Int rszTemp;
    Int src, srcOrig;

    /* Estimate src */
    if (rsz <= 512) {
        src = (((dst - 1) * rsz + 16) >> 8) + 4;
    }
    else {
        src = (((dst - 1) * rsz + 32) >> 8) + 7;
    }

    srcOrig = src;

    /* Fine tune src */
    while (1) {
        rszTemp = estimateRsz(src, dst);

        if (rszTemp < rsz) {
            if (src < srcOrig) break;
            src++;
        }
        else if (rszTemp > rsz) {
            if (src > srcOrig) break;
            src--;
        }
        else {
            break;
        }
    }

    return src;
}
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */

/******************************************************************************
 * Resize_config
 ******************************************************************************/
Int Resize_config(Resize_Handle hResize,
                  Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    BufferGfx_Dimensions        srcDim;
    BufferGfx_Dimensions        dstDim;
    struct rsz_params           params;
    struct v4l2_requestbuffers  reqbuf;
    Int                         hrsz, vrsz;
    Int                         width, height;
    Int                         rszRate,i;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    Dmai_dbg4("Configuring resizer job resizing %dx%d to %dx%d\n",
              srcDim.width, srcDim.height, dstDim.width, dstDim.height);

    memset (&params, 0, sizeof(struct rsz_params));

    /* Source and destination pitch must be 32 bytes aligned */
    if (srcDim.lineLength % 32 || dstDim.lineLength % 32) {
        Dmai_err2("Src (%ld) and dst (%ld) must be aligned on 32 bytes\n",
                  srcDim.lineLength, dstDim.lineLength);
        return Dmai_EINVAL;
    }

    /* Estimate the hrsz value */
    hrsz = srcDim.width == dstDim.width ? 256 :
        estimateRsz(srcDim.width, dstDim.width);

   /* Estimate the vrsz value */
    vrsz = srcDim.height == dstDim.height ? 256 :
        estimateRsz(srcDim.height, dstDim.height);

    width = calcSrcSize(dstDim.width, hrsz);
    height = calcSrcSize(dstDim.height, vrsz);

    /* Set up the resizer job */
    params.in_hsize            = srcDim.width;
    params.in_vsize            = srcDim.height;
    params.in_pitch            = srcDim.lineLength;
    params.cbilin              = 0;
    params.pix_fmt             = RSZ_PIX_FMT_UYVY;
    params.out_hsize           = dstDim.width;
    params.out_vsize           = dstDim.height;
    params.out_pitch           = dstDim.lineLength;
    params.vert_starting_pixel = 0;
    params.horz_starting_pixel = 0;
    params.inptyp              = RSZ_INTYPE_YCBCR422_16BIT;
    params.hstph               = 0;
    params.vstph               = 0;
    params.yenh_params.type    = 0;
    params.yenh_params.gain    = 0;
    params.yenh_params.slop    = 0;
    params.yenh_params.core    = 0;

            /* As we are downsizing, we put */
    for (i = 0; i < 32; i++)
         params.tap4filt_coeffs[i] =
                gRDRV_reszFilter4TapHighQuality[i];

   for (i = 0; i < 32; i++)
        params.tap7filt_coeffs[i] =
               gRDRV_reszFilter7TapHighQuality[i];

    if (ioctl(hResize->fd, RSZ_S_PARAM, &params) == -1) {
        Dmai_err0("Resize setting parameters failed.\n");
        return Dmai_EFAIL;
    }

    rszRate = 0;
    if (ioctl(hResize->fd, RSZ_S_EXP, &rszRate) == -1) {
            Dmai_err0("Resize setting read cycle failed.\n");
            return Dmai_EFAIL;
    }

    hResize->inSize = srcDim.lineLength * srcDim.height;
    hResize->outSize = dstDim.lineLength * dstDim.height;

    /* Request the resizer buffers */
    reqbuf.type     = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    reqbuf.memory   = V4L2_MEMORY_USERPTR;
    reqbuf.count    = 2;

    if (ioctl(hResize->fd, RSZ_REQBUF, &reqbuf) == -1) {
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
 * Resize_execute
 ******************************************************************************/
Int Resize_execute(Resize_Handle hResize,
                   Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    Int                         i;
    struct v4l2_buffer          qbuf[2];

    assert(hResize);
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

        if (ioctl (hResize->fd, RSZ_QUERYBUF, &qbuf[i]) == -1) {
            Dmai_err1("Failed to query buffer index %d\n", i);
            return Dmai_EFAIL;
        }

        if (i == 0) {
            qbuf[i].m.userptr = (unsigned long) Buffer_getUserPtr(hSrcBuf);
        }
        else {
            qbuf[i].m.userptr = (unsigned long) Buffer_getUserPtr(hDstBuf);
        }

        if (ioctl (hResize->fd, RSZ_QUEUEBUF, &qbuf[i]) == -1) {
            Dmai_err1("Failed to queue buffer index %d\n",i);
            return Dmai_EFAIL;
        }
    }

    if (ioctl(hResize->fd, RSZ_RESIZE, NULL) == -1) {
        Dmai_err0("Failed to execute resize job\n");
        return Dmai_EFAIL;
    }

    Buffer_setNumBytesUsed(hDstBuf, hResize->outSize);

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}

/******************************************************************************
 * Resize_delete
 ******************************************************************************/
Int Resize_delete(Resize_Handle hResize)
{
#if defined(CONFIG_VIDEO_OMAP34XX_ISP_RESIZER)
    if (hResize) {
        if (hResize->fd != -1) {
            close(hResize->fd);
        }
    }

    free(hResize);

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif /* end CONFIG_VIDEO_OMAP34XX_ISP_RESIZER */
}
