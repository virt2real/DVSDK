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

#include <string.h>
#include <stdlib.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Framecopy.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "priv/_Framecopy.h"

#define MODULE_NAME     "Framecopy"

const Framecopy_Attrs Framecopy_Attrs_DEFAULT = {
    FALSE,
    0xe,
    FALSE,
};

typedef struct Framecopy_Object {
    Framecopy_CommonObject  common;
    Int                     fast;
    Int                     bpp;
} Framecopy_Object;

/******************************************************************************
 * _config
 ******************************************************************************/
static Int _config(Framecopy_Handle hFc,
                   Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    ColorSpace_Type colorSpace = BufferGfx_getColorSpace(hSrcBuf);
    Int width;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* Select the smallest width */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;

    /* Two adjacent pixels are dependent, hence we need even numbers */
    if ((colorSpace == ColorSpace_UYVY ||
         colorSpace == ColorSpace_YUV422PSEMI ||
         colorSpace == ColorSpace_YUV420PSEMI) &&
        (width & 1)) {

        Dmai_err1("Width needs to be even (%d)\n", width);
        return Dmai_EINVAL;
    }

    hFc->bpp = ColorSpace_getBpp(colorSpace);

    if (hFc->bpp < 0) {
        return hFc->bpp;
    }

    hFc->fast = (hFc->bpp / 8 * width == srcDim.lineLength) &&
                       (srcDim.lineLength == dstDim.lineLength);

    return Dmai_EOK;
}

/******************************************************************************
 * _execute
 ******************************************************************************/
static Int _execute(Framecopy_Handle hFc,
                    Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    Int8 *src, *dst;
    BufferGfx_Dimensions srcDim, dstDim;
    UInt32 srcOffset, dstOffset;
    Int width, height, y;

    assert(Buffer_getUserPtr(hSrcBuf));
    assert(Buffer_getUserPtr(hDstBuf));

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* Two adjacent pixels are dependent, hence we need even numbers */
    assert(!(((BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_UYVY) ||
               BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV422PSEMI ||
               BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV420PSEMI) &&
              (srcDim.x & 1)));

    /* Two adjacent pixels are dependent, hence we need even numbers */
    assert(!(((BufferGfx_getColorSpace(hDstBuf) == ColorSpace_UYVY) ||
               BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV422PSEMI ||
               BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI) &&
              (dstDim.x & 1)));

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x * hFc->bpp / 8;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x * hFc->bpp / 8;

    /* Select the smallest resolution */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;

    src = Buffer_getUserPtr(hSrcBuf) + srcOffset;
    dst = Buffer_getUserPtr(hDstBuf) + dstOffset;

    if (hFc->fast) {
        memcpy(dst, src, srcDim.lineLength * height);
    }
    else {
        for (y = 0; y < height; y++) {
            memcpy(dst, src, width * hFc->bpp / 8);
            src += srcDim.lineLength;
            dst += dstDim.lineLength;
        }
    }

    if (BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV422PSEMI) {
        /* On dm6467 only the luma was copied above, proceed with the chroma */
        src = Buffer_getUserPtr(hSrcBuf) + srcOffset +
                Buffer_getSize(hSrcBuf) / 2;
        dst = Buffer_getUserPtr(hDstBuf) + dstOffset +
                Buffer_getSize(hDstBuf) / 2;

        if (hFc->fast) {
            memcpy(dst, src, srcDim.lineLength * height);
        }
        else {
            for (y = 0; y < height; y++) {
                memcpy(dst, src, width * hFc->bpp / 8);
                src += srcDim.lineLength;
                dst += dstDim.lineLength;
            }
        }
    }

    Buffer_setNumBytesUsed(hDstBuf, width * height * hFc->bpp / 8);

    if (BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV420PSEMI) {
        assert((srcDim.y & 0x1) == 0);
        assert((dstDim.y & 0x1) == 0);

#if defined(Dmai_Device_dm365) || defined(Dmai_Device_dm368)
        srcOffset = srcDim.y * srcDim.lineLength / 2 +
            srcDim.x * (hFc->bpp >> 3);
        dstOffset = dstDim.y * dstDim.lineLength / 2 +
            dstDim.x * (hFc->bpp >> 3);
#else
        /* *Default* Assume DM6467 behavior */
        srcOffset = srcDim.y * srcDim.lineLength +
            srcDim.x * (hFc->bpp >> 3);
        dstOffset = dstDim.y * dstDim.lineLength +
            dstDim.x * (hFc->bpp >> 3);
#endif

        src = Buffer_getUserPtr(hSrcBuf) + srcOffset +
                (Buffer_getSize(hSrcBuf) * 2 / 3);
        dst = Buffer_getUserPtr(hDstBuf) + dstOffset +
                (Buffer_getSize(hDstBuf) * 2 / 3);
        
        if (hFc->fast) {
            memcpy(dst, src, srcDim.lineLength * height / 2);
        }
        else {
            for (y = 0; y < height / 2; y++) {
                memcpy(dst, src, width * hFc->bpp / 8);
                src += srcDim.lineLength;
                dst += dstDim.lineLength;
            }
        }
        Buffer_setNumBytesUsed(hDstBuf, width * height * 3 / 2);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Framecopy_create
 ******************************************************************************/
Framecopy_Handle Framecopy_create(Framecopy_Attrs *attrs)
{
    Framecopy_Handle hFc;

    if (attrs == NULL) {
        Dmai_err0("Cannot pass NULL for Framecopy_Attrs\n");
        return NULL;
    }

    if (attrs->accel) {
#if defined(Dmai_Device_omap3530) || defined(Dmai_Device_dm3730)
        if (attrs->sdma) {
            hFc = Framecopy_sdma_accel_create(attrs);
        }
        else {
            hFc = Framecopy_resizer_accel_create(attrs);
        }
#else
        hFc = Framecopy_accel_create(attrs);
#endif

        if (hFc == NULL) {
            return NULL;
        }
    }
    else {
        hFc = (Framecopy_Handle)calloc(1, sizeof(Framecopy_Object));

        if (hFc == NULL) {
            Dmai_err0("Failed to allocate space for Framecopy Object\n");
            return NULL;
        }
    }

    hFc->common.accel = attrs->accel;
    hFc->common.sdma = attrs->sdma;

    return hFc;
}

/******************************************************************************
 * Framecopy_config
 ******************************************************************************/
Int Framecopy_config(Framecopy_Handle hFc,
                     Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    assert(hFc);
    assert(hSrcBuf);
    assert(hDstBuf);
    assert(Buffer_getType(hSrcBuf) == Buffer_Type_GRAPHICS);
    assert(Buffer_getType(hDstBuf) == Buffer_Type_GRAPHICS);

    if (BufferGfx_getColorSpace(hSrcBuf) !=
        BufferGfx_getColorSpace(hDstBuf)) {
        Dmai_err2("Framecopy only between buffers with same color space fmt %d vs %d\n",
            BufferGfx_getColorSpace(hSrcBuf), BufferGfx_getColorSpace(hDstBuf));
        return Dmai_EINVAL;
    }

    if (hFc->common.accel) {
#if defined(Dmai_Device_omap3530) || defined(Dmai_Device_dm3730)
        if (hFc->common.sdma) {
            return Framecopy_sdma_accel_config(hFc, hSrcBuf, hDstBuf);
        }
        else {
            return Framecopy_resizer_accel_config(hFc, hSrcBuf, hDstBuf);
        }
#else
        return Framecopy_accel_config(hFc, hSrcBuf, hDstBuf);
#endif
    }

    return _config(hFc, hSrcBuf, hDstBuf);
}

/******************************************************************************
 * Framecopy_execute
 ******************************************************************************/
Int Framecopy_execute(Framecopy_Handle hFc,
                      Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    assert(hFc);
    assert(hSrcBuf);
    assert(hDstBuf);
    assert(Buffer_getType(hSrcBuf) == Buffer_Type_GRAPHICS);
    assert(Buffer_getType(hDstBuf) == Buffer_Type_GRAPHICS);

    if (hFc->common.accel) {
#if defined(Dmai_Device_omap3530) || defined(Dmai_Device_dm3730)
        if (hFc->common.sdma) {
            return Framecopy_sdma_accel_execute(hFc, hSrcBuf, hDstBuf);
        }
        else {
            return Framecopy_resizer_accel_execute(hFc, hSrcBuf, hDstBuf);
        }
#else
        return Framecopy_accel_execute(hFc, hSrcBuf, hDstBuf);
#endif
    }

    return _execute(hFc, hSrcBuf, hDstBuf);
}

/******************************************************************************
 * Framecopy_delete
 ******************************************************************************/
Int Framecopy_delete(Framecopy_Handle hFc)
{
    Int ret = Dmai_EOK;

    if (hFc) {
        if (hFc->common.accel) {
#if defined(Dmai_Device_omap3530) || defined(Dmai_Device_dm3730)
            if (hFc->common.sdma) {
                return Framecopy_sdma_accel_delete(hFc);
            }
            else {
                return Framecopy_resizer_accel_delete(hFc);
            }
#else
            ret = Framecopy_accel_delete(hFc);
#endif
        }
        else {
            free(hFc);
        }
    }

    return ret;
}

