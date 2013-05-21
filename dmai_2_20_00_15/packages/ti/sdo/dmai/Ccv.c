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
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/dmai/Ccv.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "priv/_Ccv.h"

#define MODULE_NAME     "Ccv"

/* Accelerated function prototypes */
extern Int Ccv_accel_init(Ccv_Handle hCcv, Ccv_Attrs *attrs);
extern Int Ccv_accel_config(Ccv_Handle hCcv,
                            Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);
extern Int Ccv_accel_execute(Ccv_Handle hCcv, Buffer_Handle hSrcBuf,
                             Buffer_Handle hDstBuf);
extern Int Ccv_accel_exit(Ccv_Handle hCcv);

const Ccv_Attrs Ccv_Attrs_DEFAULT = {
    FALSE,
};

static Void ycbcr422p_rgb565
(
    const Int16             coeff[5],   /* Matrix coefficients.             */
    const UInt8             *yData,     /* Luminence data        (Y')       */
    const UInt8             *cbData,    /* Blue color-difference (B'-Y')    */
    const UInt8             *crData,    /* Red color-difference  (R'-Y')    */
    UInt16                  *rgbData,   /* RGB 5:6:5 packed pixel output.   */
    UInt32                  numPixels   /* # of luma pixels to process.     */
);

static Void ycbcr420p_rgb565(
    const Int16             coeff[5],   /* Matrix coefficients.             */
    const UInt8             *yData,     /* Luminence data        (Y')       */
    const UInt8             *cbData,    /* Blue color-difference (B'-Y')    */
    const UInt8             *crData,    /* Red color-difference  (R'-Y')    */
    UInt16                  *rgbData,   /* RGB 5:6:5 packed pixel output.   */
    UInt32                  width,      /* Width of the buffer.             */
    UInt32                  height      /* Height of the buffer.            */
);

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Ccv_Handle hCcv)
{
    Int ret = Dmai_EOK;

    if (hCcv->accel) {
        ret = Ccv_accel_exit(hCcv);
    }

    free(hCcv);

    return ret;
}

/******************************************************************************
 * ccv_Yuv420semi_Yuv422semi
 ******************************************************************************/
static Void ccv_Yuv420semi_Yuv422semi(Ccv_Handle hCcv,
                                      Buffer_Handle hSrcBuf,
                                      Buffer_Handle hDstBuf)
{
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 srcOffset, dstOffset;
    Int8 *src, *dst;
    Int i;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    assert((srcDim.x & 0x1) == 0);
    assert((dstDim.x & 0x1) == 0);

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x;

    src = Buffer_getUserPtr(hSrcBuf) + srcOffset;
    dst = Buffer_getUserPtr(hDstBuf) + dstOffset;

    /* Copy Y if necessary */
    if (dst != src) {
        for(i = 0; i < srcDim.height; i++) {
            memcpy(dst, src, srcDim.width);
            dst += dstDim.lineLength;
            src += srcDim.lineLength;
        }
    }

    dst = Buffer_getUserPtr(hDstBuf) + dstOffset + Buffer_getSize(hDstBuf) / 2;
    src = Buffer_getUserPtr(hSrcBuf) +
          srcDim.y * srcDim.lineLength / 2 + srcDim.x +
          Buffer_getSize(hSrcBuf) * 2 / 3;

    for(i = 0; i < srcDim.height; i += 2) {
        memcpy(dst, src, srcDim.width);
        dst += dstDim.lineLength;
        memcpy(dst, src, srcDim.width);
        src += srcDim.lineLength;
        dst += dstDim.lineLength;
    }

    Buffer_setNumBytesUsed(hDstBuf, srcDim.width * srcDim.height * 2);
}

/******************************************************************************
 * ccv_Yuv422semi_Yuv420semi
 ******************************************************************************/
static Void ccv_Yuv422semi_Yuv420semi(Ccv_Handle hCcv,
                                      Buffer_Handle hSrcBuf,
                                      Buffer_Handle hDstBuf)
{
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 srcOffset, dstOffset;
    Int8 *src, *dst;
    Int i;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    assert((srcDim.x & 0x1) == 0);
    assert((dstDim.x & 0x1) == 0);

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x;

    src = Buffer_getUserPtr(hSrcBuf) + srcOffset;
    dst = Buffer_getUserPtr(hDstBuf) + dstOffset;

    /* Copy Y if necessary */
    if (dst != src) {
        for(i = 0; i < srcDim.height; i++) {
            memcpy(dst, src, srcDim.width);
            dst += dstDim.lineLength;
            src += srcDim.lineLength;
        }
    }

    src = Buffer_getUserPtr(hSrcBuf) + srcOffset + Buffer_getSize(hSrcBuf) / 2;
    dst = Buffer_getUserPtr(hDstBuf) +
          dstDim.y * dstDim.lineLength / 2 + dstDim.x +
          Buffer_getSize(hDstBuf) * 2 / 3;

    for(i = 0; i < srcDim.height; i += 2) {
        memcpy(dst, src, srcDim.width);
        src += srcDim.lineLength * 2;
        dst += dstDim.lineLength;
    }

    Buffer_setNumBytesUsed(hDstBuf, srcDim.width * srcDim.height * 3 / 2);
}

/******************************************************************************
 * ccv_Yuv420p_Rgb565,
 ******************************************************************************/
static Void ccv_Yuv420p_Rgb565(Ccv_Handle hCcv,
                               Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    Int8 *src, *dst;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 crOffset, cbOffset, frameSizeLuma, frameSizeChroma;
    UInt16 *rgbData;
    const Int16 coeff[5] = {0x2543, 0x3313, -0x0C8A, -0x1A04, 0x408D };
    UInt8 *yData, *cbData, *crData;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    src = Buffer_getUserPtr(hSrcBuf);
    dst = Buffer_getUserPtr(hDstBuf);

    frameSizeLuma = srcDim.width * srcDim.height;
    frameSizeChroma = frameSizeLuma/4;
    cbOffset = frameSizeLuma;
    crOffset = frameSizeLuma + frameSizeChroma;

    yData = (UInt8 *)src;
    cbData = (UInt8 *)src + cbOffset;
    crData = (UInt8 *)src + crOffset;
    rgbData = (UInt16 *) dst;

    ycbcr420p_rgb565(coeff, yData, cbData, crData, rgbData,
        (UInt32)srcDim.width, (UInt32)srcDim.height);

    Buffer_setNumBytesUsed(hDstBuf, srcDim.width * srcDim.height * 3/2);
}

/******************************************************************************
 * ccv_Yuv422p_Rgb565,
 ******************************************************************************/
static Void ccv_Yuv422p_Rgb565(Ccv_Handle hCcv,
                               Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    Int8 *src, *dst;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 crOffset, cbOffset, frameSizeLuma, frameSizeChroma;
    UInt16 *rgbData;
    const Int16 coeff[5] = {0x2543, 0x3313, -0x0C8A, -0x1A04, 0x408D };
    UInt8 *yData, *cbData, *crData;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    src = Buffer_getUserPtr(hSrcBuf);
    dst = Buffer_getUserPtr(hDstBuf);

    frameSizeLuma = srcDim.width * srcDim.height;
    frameSizeChroma = frameSizeLuma/4;
    cbOffset = frameSizeLuma;
    crOffset = frameSizeLuma + frameSizeChroma;

    yData = (UInt8 *)src;
    cbData = (UInt8 *)src + cbOffset;
    crData = (UInt8 *)src + crOffset;
    rgbData = (UInt16 *) dst;

    ycbcr422p_rgb565(coeff, yData, cbData, crData, rgbData,
        (UInt32)srcDim.width * (UInt32)srcDim.height);

    Buffer_setNumBytesUsed(hDstBuf, srcDim.width * srcDim.height * 3/2);
}

/******************************************************************************
 * ycbcr422p_rgb565
 ******************************************************************************/
static Void ycbcr422p_rgb565
(
    const Int16             coeff[5],   /* Matrix coefficients.             */
    const UInt8             *yData,     /* Luminence data        (Y')       */
    const UInt8             *cbData,    /* Blue color-difference (B'-Y')    */
    const UInt8             *crData,    /* Red color-difference  (R'-Y')    */
    UInt16                  *rgbData,   /* RGB 5:6:5 packed pixel output.   */
    UInt32                   numPixels  /* # of luma pixels to process.     */
)
{
    Int32 i;                      /* Loop counter                     */
    Int32 y0, y1;                 /* Individual Y components          */
    Int32 cb, cr;                 /* Color difference components      */
    Int32 y0t,y1t;                /* Temporary Y values               */
    Int32 rt, gt, bt;             /* Temporary RGB values             */
    Int32 r0, g0, b0;             /* Individual RGB components        */
    Int32 r1, g1, b1;             /* Individual RGB components        */
    Int32 r0t,g0t,b0t;            /* Truncated RGB components         */
    Int32 r1t,g1t,b1t;            /* Truncated RGB components         */
    Int32 r0s,g0s,b0s;            /* Saturated RGB components         */
    Int32 r1s,g1s,b1s;            /* Saturated RGB components         */

    Int16 luma = coeff[0];        /* Luma scaling coefficient.        */
    Int16 r_cr = coeff[1];        /* Cr's contribution to Red.        */
    Int16 g_cb = coeff[2];        /* Cb's contribution to Green.      */
    Int16 g_cr = coeff[3];        /* Cr's contribution to Green.      */
    Int16 b_cb = coeff[4];        /* Cb's contribution to Blue.       */

    Int16 rgb0, rgb1;             /* Packed RGB pixel data            */

    /* -------------------------------------------------------------------- */
    /*  Iterate for numPixels/2 iters, since we process pixels in pairs.   */
    /* -------------------------------------------------------------------- */
    i = numPixels >> 1;
    while (i-->0)
    {
        /* ---------------------------------------------------------------- */
        /*  Read in YCbCr data from the separate data planes.               */
        /*                                                                  */
        /*  The Cb and Cr channels come in biased upwards by 128, so        */
        /*  subtract the bias here before performing the multiplies for     */
        /*  the color space conversion itself.  Also handle Y's upward      */
        /*  bias of 16 here.                                                */
        /* ---------------------------------------------------------------- */

        y0 = *yData++  - 16;
        y1 = *yData++  - 16;
        cb = *cbData++ - 128;
        cr = *crData++ - 128;

        /* ================================================================ */
        /*  Convert YCrCb data to RGB format using the following matrix:    */
        /*                                                                  */
        /*      [ coeff[0] 0.0000   coeff[1] ]   [ Y' -  16 ]     [ R']     */
        /*      [ coeff[0] coeff[2] coeff[3] ] * [ Cb - 128 ]  =  [ G']     */
        /*      [ coeff[0] coeff[4] 0.0000   ]   [ Cr - 128 ]     [ B']     */
        /*                                                                  */
        /*  We use signed Q13 coefficients for the coefficients to make     */
        /*  good use of our 16-bit multiplier.  Although a larger Q-point   */
        /*  may be used with unsigned coefficients, signed coefficients     */
        /*  add a bit of flexibility to the kernel without significant      */
        /*  loss of precision.                                              */
        /* ================================================================ */

        /* ---------------------------------------------------------------- */
        /*  Calculate chroma channel's contribution to RGB.                 */
        /* ---------------------------------------------------------------- */
        rt  = r_cr * (Int16)cr;
        gt  = g_cb * (Int16)cb + g_cr * (Int16)cr;
        bt  = b_cb * (Int16)cb;

        /* ---------------------------------------------------------------- */
        /*  Calculate intermediate luma values.  Include bias of 16 here.   */
        /* ---------------------------------------------------------------- */
        y0t = luma * (Int16)y0;
        y1t = luma * (Int16)y1;

        /* ---------------------------------------------------------------- */
        /*  Mix luma, chroma channels.                                      */
        /* ---------------------------------------------------------------- */
        r0  = y0t + rt; r1 = y1t + rt;
        g0  = y0t + gt; g1 = y1t + gt;
        b0  = y0t + bt; b1 = y1t + bt;

        /* ================================================================ */
        /*  At this point in the calculation, the RGB components are        */
        /*  nominally in the format below.  If the color is outside the     */
        /*  our RGB gamut, some of the sign bits may be non-zero,           */
        /*  triggering saturation.                                          */
        /*                                                                  */
        /*                  3     2 2        1 1                            */
        /*                  1     1 0        3 2         0                  */
        /*                 [ SIGN  | COLOR    | FRACTION ]                  */
        /*                                                                  */
        /*  This gives us an 8-bit range for each of the R, G, and B        */
        /*  components.  (The transform matrix is designed to transform     */
        /*  8-bit Y/C values into 8-bit R,G,B values.)  To get our final    */
        /*  5:6:5 result, we "divide" our R, G and B components by 4, 8,    */
        /*  and 4, respectively, by reinterpreting the numbers in the       */
        /*  format below:                                                   */
        /*                                                                  */
        /*          Red,    3     2 2     1 1                               */
        /*          Blue    1     1 0     6 5            0                  */
        /*                 [ SIGN  | COLOR | FRACTION    ]                  */
        /*                                                                  */
        /*                  3     2 2      1 1                              */
        /*          Green   1     1 0      5 4           0                  */
        /*                 [ SIGN  | COLOR  | FRACTION   ]                  */
        /*                                                                  */
        /*  "Divide" is in quotation marks because this step requires no    */
        /*  actual work.  The code merely treats the numbers as having a    */
        /*  different Q-point.                                              */
        /* ================================================================ */

        /* ---------------------------------------------------------------- */
        /*  Shift away the fractional portion, and then saturate to the     */
        /*  RGB 5:6:5 gamut.                                                */
        /* ---------------------------------------------------------------- */
        r0t = r0 >> 16;
        g0t = g0 >> 15;
        b0t = b0 >> 16;
        r1t = r1 >> 16;
        g1t = g1 >> 15;
        b1t = b1 >> 16;

        r0s = r0t < 0 ? 0 : r0t > 31 ? 31 : r0t;
        g0s = g0t < 0 ? 0 : g0t > 63 ? 63 : g0t;
        b0s = b0t < 0 ? 0 : b0t > 31 ? 31 : b0t;
        r1s = r1t < 0 ? 0 : r1t > 31 ? 31 : r1t;
        g1s = g1t < 0 ? 0 : g1t > 63 ? 63 : g1t;
        b1s = b1t < 0 ? 0 : b1t > 31 ? 31 : b1t;

        /* ---------------------------------------------------------------- */
        /*  Merge values into output pixels.                                */
        /* ---------------------------------------------------------------- */
        rgb0 = (r0s << 11) + (g0s <<  5) + (b0s <<  0);
        rgb1 = (r1s << 11) + (g1s <<  5) + (b1s <<  0);

        /* ---------------------------------------------------------------- */
        /*  Store resulting pixels to memory.                               */
        /* ---------------------------------------------------------------- */
        *rgbData++ = (UInt16)rgb0;
        *rgbData++ = (UInt16)rgb1;
    }
    return;
}

/******************************************************************************
 * ycbcr420p_rgb565
 ******************************************************************************/
static Void ycbcr420p_rgb565(
    const Int16             coeff[5],   /* Matrix coefficients.             */
    const UInt8             *yData,     /* Luminence data        (Y')       */
    const UInt8             *cbData,    /* Blue color-difference (B'-Y')    */
    const UInt8             *crData,    /* Red color-difference  (R'-Y')    */
    UInt16                  *rgbData,   /* RGB 5:6:5 packed pixel output.   */
    UInt32                  width,      /* Width of the buffer.             */
    UInt32                  height      /* Height of the buffer.            */
)
{
    Int32 i;

    for(i=0; i<height; i+=2) {
        ycbcr422p_rgb565(coeff, yData, cbData, crData, rgbData, width);
         yData += width;
         rgbData += width;

         ycbcr422p_rgb565(coeff, yData, cbData, crData, rgbData, width);
         rgbData += width;
         yData += width;
         cbData += width >> 1;
         crData += width >> 1;
    }

    return;
}

/* Unaccelerated color conversion function pointers */
static Void (*ccvFxns[Ccv_Mode_COUNT])(Ccv_Handle hCcv, Buffer_Handle hSrcBuf,
                                      Buffer_Handle hDstBuf) = {
    ccv_Yuv420semi_Yuv422semi,
    ccv_Yuv422semi_Yuv420semi,
    ccv_Yuv420p_Rgb565,
    ccv_Yuv422p_Rgb565,
};

/******************************************************************************
 * Ccv_create
 ******************************************************************************/
Ccv_Handle Ccv_create(Ccv_Attrs *attrs)
{
    Int ret = Dmai_EOK;
    Ccv_Handle hCcv;

    if (attrs == NULL) {
        Dmai_err0("Need valid attrs\n");
        return NULL;
    }

    hCcv = (Ccv_Handle)calloc(1, sizeof(Ccv_Object));

    if (hCcv == NULL) {
        Dmai_err0("Failed to allocate space for Ccv Object\n");
        return NULL;
    }

    hCcv->accel = attrs->accel;

    if (attrs->accel) {
        ret = Ccv_accel_init(hCcv, attrs);

        if (ret == Dmai_ENOTIMPL) {
            Dmai_err0("No accelerated color conversion available\n");
        }

        if (ret < 0) {
            cleanup(hCcv);
            return NULL;
        }
    }

    return hCcv;
}

/******************************************************************************
 * Ccv_config
 ******************************************************************************/
Int Ccv_config(Ccv_Handle hCcv, Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    Int ret = Dmai_EOK;
    BufferGfx_Dimensions srcDim, dstDim;
    Int width;

    assert(hCcv);
    assert(hSrcBuf);
    assert(hDstBuf);
    assert(Buffer_getType(hSrcBuf) == Buffer_Type_GRAPHICS);
    assert(Buffer_getType(hDstBuf) == Buffer_Type_GRAPHICS);

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* Select the smallest width */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;

    /* Use device specific accelerated configuration function? */
    if (hCcv->accel) {
        ret = Ccv_accel_config(hCcv, hSrcBuf, hDstBuf);

        if (ret < 0) {
            return ret;
        }
    }
    else {
        switch (BufferGfx_getColorSpace(hSrcBuf)) {
            case ColorSpace_YUV422PSEMI:
                /* Two adjacent pixels are dependent, hence need even numbers */
                if (width & 1) {
                    Dmai_err1("Width needs to be even (%d)\n", width);
                    return Dmai_EINVAL;
                }

                if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI){
                    hCcv->mode = Ccv_Mode_YUV422SEMI_YUV420SEMI;
                }
                else {
                    Dmai_err0("Color conversion mode not supported\n");
                    return Dmai_ENOTIMPL;
                }
                break;
            case ColorSpace_YUV422P:
                /* Two adjacent pixels are dependent, hence need even numbers */
                if (width & 1) {
                    Dmai_err1("Width needs to be even (%d)\n", width);
                    return Dmai_EINVAL;
                }

                if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_RGB565){
                    hCcv->mode = Ccv_Mode_YUV422PSEMI_RGB565;
                }
                else {
                    Dmai_err0("Color conversion mode not supported\n");
                    return Dmai_ENOTIMPL;
                }
                break;
            case ColorSpace_YUV420PSEMI:
                /* Two adjacent pixels are dependent, hence need even numbers */
                if (width & 1) {
                    Dmai_err1("Width needs to be even (%d)\n", width);
                    return Dmai_EINVAL;
                }

                if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV422PSEMI){
                    hCcv->mode = Ccv_Mode_YUV420SEMI_YUV422SEMI;
                }
                else {
                    Dmai_err0("Color conversion mode not supported\n");
                    return Dmai_ENOTIMPL;
                }
                break;
            case ColorSpace_YUV420P:
                /* Two adjacent pixels are dependent, hence need even numbers */
                if (width & 1) {
                    Dmai_err1("Width needs to be even (%d)\n", width);
                    return Dmai_EINVAL;
                }

                if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_RGB565){
                    hCcv->mode = Ccv_Mode_YUV420P_RGB565;
                }
                else {
                    Dmai_err0("Color conversion mode not supported\n");
                    return Dmai_ENOTIMPL;
                }
                break;
            default:
                Dmai_err0("Color conversion mode not supported\n");
                return Dmai_ENOTIMPL;
        }
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Ccv_execute
 ******************************************************************************/
Int Ccv_execute(Ccv_Handle hCcv, Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    assert(hCcv);
    assert(hSrcBuf);
    assert(hDstBuf);
    assert(Buffer_getUserPtr(hSrcBuf));
    assert(Buffer_getUserPtr(hDstBuf));
    assert(Buffer_getNumBytesUsed(hSrcBuf));
    assert(Buffer_getSize(hDstBuf));
    assert(Buffer_getType(hSrcBuf) == Buffer_Type_GRAPHICS);
    assert(Buffer_getType(hDstBuf) == Buffer_Type_GRAPHICS);

    /* Call device specific accelerated execute or generic function? */
    if (hCcv->accel) {
        return Ccv_accel_execute(hCcv, hSrcBuf, hDstBuf);
    }

    if (ccvFxns[hCcv->mode]) {
        ccvFxns[hCcv->mode](hCcv, hSrcBuf, hDstBuf);
    }
    else {
        return Dmai_ENOTIMPL;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Ccv_getMode
 ******************************************************************************/
Ccv_Mode Ccv_getMode(Ccv_Handle hCcv)
{
    return hCcv->mode;
}

/******************************************************************************
 * Ccv_delete
 ******************************************************************************/
Int Ccv_delete(Ccv_Handle hCcv)
{
    Int ret = Dmai_EOK;

    if (hCcv) {
        ret = cleanup(hCcv);
    }

    return ret;
}

