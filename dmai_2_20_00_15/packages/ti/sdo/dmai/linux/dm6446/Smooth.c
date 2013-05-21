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
 * This module uses the resizer H/W module of the VPSS on the DM6446 to
 * remove interlacing artifacts in a YUV422 interleaved image. It does this
 * by removing the odd field and extrapolating the odd lines using the
 * surrounding even lines. See the application note spraaXXXX for details.
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>

#ifdef CONFIG_RESIZER
#include <linux/davinci_resizer.h>
#endif

#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Smooth.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Smooth"

#define RESIZER_DEVICE "/dev/davinci_resizer"

typedef struct Smooth_Object {
    int      rszFd;
    Int32    inSize;
    Int32    outSize;
} Smooth_Object;

const Smooth_Attrs Smooth_Attrs_DEFAULT = {
    0xe,
};

#ifdef CONFIG_RESIZER
/******************************************************************************
 * inHeightCalc
 ******************************************************************************/
static int inHeightCalc(int height)
{
    int vrsz;
    int h = height / 2;

    while (1) {
        vrsz = ((h - 4) * 256 - 16) / (height - 1);

        if (vrsz < 128) {
            if (h < height / 2) {
                break;
            }
            h++;
        }
        else if (vrsz > 128) {
            if (h > height / 2) {
                break;
            }
            h--;
        }
        else {
            break;
        }
    }

    return h;
}

/******************************************************************************
 * inWidthCalc
 ******************************************************************************/
static int inWidthCalc(int width)
{
    int hrsz;
    int w = width;

    while (1) {
        hrsz = ((w - 4) * 256 - 16) / (width - 1);

        if (hrsz < 256) {
            if (w < width) {
                break;
            }
            w++;
        }
        else if (hrsz > 256) {
            if (w > width) {
                break;
            }
            w--;
        }
        else {
            break;
        }
    }

    return w;
}
#endif

/******************************************************************************
 * Smooth_create
 ******************************************************************************/
Smooth_Handle Smooth_create(Smooth_Attrs *attrs)
{
#ifdef CONFIG_RESIZER
    Smooth_Handle hSmooth;

    if (attrs == NULL) {
        Dmai_err0("Need valid attrs\n");
        return NULL;
    }

    hSmooth = calloc(1, sizeof(Smooth_Object));

    if (hSmooth == NULL) {
        Dmai_err0("Failed to allocate memory space for handle.\n");
        return NULL;
    }

    /* Open resizer device */
    hSmooth->rszFd = open(RESIZER_DEVICE, O_RDWR, 0);

    if (hSmooth->rszFd == -1) {
        Dmai_err1("Failed to open %s\n", RESIZER_DEVICE);
        free(hSmooth);
        return NULL;
    }

    /* The rate affects the priority of this resizer job for the DDR */
    if (attrs->rszRate >= 0) {
        if (ioctl(hSmooth->rszFd, RSZ_S_EXP, &attrs->rszRate) == -1) {
            Dmai_err0("Error calling RSZ_S_EXP on resizer.\n");
            close(hSmooth->rszFd);
            free(hSmooth);
            return NULL;
        }
    }

    return hSmooth;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

/******************************************************************************
 * Smooth_config
 ******************************************************************************/
Int Smooth_config(Smooth_Handle hSmooth,
                  Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_RESIZER
    BufferGfx_Dimensions srcDim, dstDim;
    Int width, height;
    struct rsz_params params = {
        0,                              /* in_hsize (set at run time) */
        0,                              /* in_vsize (set at run time) */
        0,                              /* in_pitch (set at run time) */
        RSZ_INTYPE_YCBCR422_16BIT,      /* inptyp */
        0,                              /* vert_starting_pixel */
        0,                              /* horz_starting_pixel */
        0,                              /* cbilin */
        RSZ_PIX_FMT_YUYV,               /* pix_fmt */
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
            0, 256, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            -32, 160, 160, -32, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0
        },
        {                               /* yenh_params */
            RSZ_YENH_DISABLE,               /* type */
            0,                              /* gain */
            0,                              /* slop */
            0                               /* core */
        }
    };

    if (hSmooth == NULL || hSrcBuf == NULL || hDstBuf == NULL) {
        Dmai_err0("Must supply valid Smooth and Buffer handles\n");
        return Dmai_EINVAL;
    }

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* Select the smallest resolution */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;

    if (width % 16) {
        Dmai_err1("Invalid width (%d), must be a multiple of 16 pixels\n",
                  srcDim.width);
        return Dmai_EINVAL;
    }

    if (height % 16) {
        Dmai_err1("Invalid height (%d), must be a multiple of 16 pixels\n",
                  srcDim.height);
        return Dmai_EINVAL;
    }

    Dmai_dbg2("Configuring smooth job of size %dx%d\n", width, height);

    params.in_hsize      = inWidthCalc(width);
    params.in_vsize      = inHeightCalc(height);
    params.in_pitch      = srcDim.lineLength * 2;
    params.out_hsize     = width;
    params.out_vsize     = height;
    params.out_pitch     = dstDim.lineLength;

    if (ioctl(hSmooth->rszFd, RSZ_S_PARAM, &params) == -1) {
        Dmai_err0("Resize setting parameters failed.\n");
        return Dmai_EFAIL;
    }

    hSmooth->inSize = srcDim.lineLength * params.in_vsize * 2;
    hSmooth->outSize = dstDim.lineLength * height;

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Smooth_execute
 ******************************************************************************/
Int Smooth_execute(Smooth_Handle hSmooth,
                   Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_RESIZER
    struct rsz_resize   rsz;
    int                 rszError;
    UInt32              srcOffset, dstOffset;

    BufferGfx_Dimensions srcDim, dstDim;

    assert(hSmooth);
    assert(hSrcBuf);
    assert(hDstBuf);
    assert((Buffer_getPhysicalPtr(hDstBuf) & 0x1F) == 0);
    assert((Buffer_getPhysicalPtr(hSrcBuf) & 0x1F) == 0);

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* x must be a multiple of 16 since address must be multiple of 32 */
    assert((srcDim.x & 0xF) == 0);
    assert((dstDim.x & 0xF) == 0);

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x * 2;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x * 2;

    rsz.in_buf.index     = -1;
    rsz.in_buf.buf_type  = RSZ_BUF_IN;
    rsz.in_buf.offset    = Buffer_getPhysicalPtr(hSrcBuf) + srcOffset;
    rsz.in_buf.size      = hSmooth->inSize;

    rsz.out_buf.index    = -1;
    rsz.out_buf.buf_type = RSZ_BUF_OUT;
    rsz.out_buf.offset   = Buffer_getPhysicalPtr(hDstBuf) + dstOffset;
    rsz.out_buf.size     = hSmooth->outSize;

    do {
        rszError = ioctl(hSmooth->rszFd, RSZ_RESIZE, &rsz);
    } while (rszError == -1 && errno == EAGAIN);

    if (rszError == -1) {
        Dmai_err0("Failed to do resize job\n");
        return Dmai_EFAIL;
    }

    Buffer_setNumBytesUsed(hDstBuf, Buffer_getNumBytesUsed(hSrcBuf));

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Smooth_delete
 ******************************************************************************/
Int Smooth_delete(Smooth_Handle hSmooth)
{
    if (hSmooth) {
        close(hSmooth->rszFd);
        free(hSmooth);
    }

    return Dmai_EOK;
}
