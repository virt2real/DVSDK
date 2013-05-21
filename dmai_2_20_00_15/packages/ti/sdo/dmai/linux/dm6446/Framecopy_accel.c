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

#ifdef CONFIG_RESIZER
#include <linux/davinci_resizer.h>
#endif

#define MODULE_NAME     "Framecopy"

#define RESIZER_DEVICE  "/dev/davinci_resizer"
#define FIR_RND_SCALE   256
#define NUM_COEFS       32
#define SCREEN_BPP      16

typedef struct Framecopy_Object {
    Framecopy_CommonObject  common;
    Int                     fd;
    Int32                   inSize;
    Int32                   outSize;
} Framecopy_Object;

#ifdef CONFIG_RESIZER
/******************************************************************************
 * inSizeCalc
 ******************************************************************************/
static int inSizeCalc(int inSize)
{
    int hFc;
    int in = inSize;

    while (1) {
        hFc = ((in - 4) * 256 - 16) / (inSize - 1);

        if (hFc < 256) {
            if (in < inSize) {
                break;
            }
            in++;
        }
        else if (hFc > 256) {
            if (in > inSize) {
                break;
            }
            in--;
        }
        else {
            break;
        }
    }

    return in;
}
#endif

/******************************************************************************
 * Framecopy_accel_config
 ******************************************************************************/
Int Framecopy_accel_config(Framecopy_Handle hFc,
                           Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_RESIZER
    Int width, height;
    BufferGfx_Dimensions srcDim, dstDim;
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
            256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0,
            256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0, 256, 0, 0, 0
        },
        {                               /* yenh_params */
            RSZ_YENH_DISABLE,               /* type */
            0,                              /* gain */
            0,                              /* slop */
            0                               /* core */
        }
    };

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* Select the smallest resolution */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;

    if (width & 1) {
        Dmai_err0("Width needs to be even\n");
        return Dmai_EINVAL;
    }

    Dmai_dbg2("Configuring resizer to copy image of resolution %dx%d\n",
              width, height);

    /* Set up the copy job */
    params.in_hsize   = inSizeCalc(width);
    params.in_vsize   = inSizeCalc(height);
    params.in_pitch   = srcDim.lineLength;
    params.out_hsize  = width;
    params.out_vsize  = height;
    params.out_pitch  = dstDim.lineLength;

    hFc->inSize  = srcDim.lineLength * params.in_vsize;
    hFc->outSize = dstDim.lineLength * params.out_vsize;

    if (ioctl(hFc->fd, RSZ_S_PARAM, &params) == -1) {
        Dmai_err0("Framecopy setting parameters failed.\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Framecopy_accel_create
 ******************************************************************************/
Framecopy_Handle Framecopy_accel_create(Framecopy_Attrs *attrs)
{
#ifdef CONFIG_RESIZER
    Framecopy_Handle hFc;

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

    if (attrs->rszRate > 0) {
        if (ioctl(hFc->fd, RSZ_S_EXP, &attrs->rszRate) == -1) {
            Dmai_err0("Error calling RSZ_S_EXP on resizer.\n");
            close(hFc->fd);
            return NULL;
        }
    }

    return hFc;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

/******************************************************************************
 * Framecopy_accel_execute
 ******************************************************************************/
Int Framecopy_accel_execute(Framecopy_Handle hFc,
                            Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_RESIZER
    struct rsz_resize   rsz;
    Int                 rszError;
    UInt32              srcOffset, dstOffset;

    BufferGfx_Dimensions srcDim, dstDim;

    /* Pointers must be a multiple of 32 bytes */
    assert((Buffer_getPhysicalPtr(hDstBuf) & 0x1F) == 0);
    assert((Buffer_getPhysicalPtr(hSrcBuf) & 0x1F) == 0);

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* Because resulting pointers must be a multiple of 32 bytes */
    assert((srcDim.x & 0xF) == 0);
    assert((dstDim.x & 0xF) == 0);

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x * 2;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x * 2;

    rsz.in_buf.index     = -1;
    rsz.in_buf.buf_type  = RSZ_BUF_IN;
    rsz.in_buf.offset    = Buffer_getPhysicalPtr(hSrcBuf) + srcOffset;
    rsz.in_buf.size      = hFc->inSize;

    rsz.out_buf.index    = -1;
    rsz.out_buf.buf_type = RSZ_BUF_OUT;
    rsz.out_buf.offset   = Buffer_getPhysicalPtr(hDstBuf) + dstOffset;
    rsz.out_buf.size     = hFc->outSize;

    do {
        rszError = ioctl(hFc->fd, RSZ_RESIZE, &rsz);
    } while (rszError == -1 && errno == EAGAIN);

    if (rszError == -1) {
        Dmai_err0("Failed to execute resize job\n");
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
 * Framecopy_accel_delete
 ******************************************************************************/
Int Framecopy_accel_delete(Framecopy_Handle hFc)
{
    if (hFc->fd > 0) {
        close(hFc->fd);
    }

    free(hFc);

    return Dmai_EOK;
}

