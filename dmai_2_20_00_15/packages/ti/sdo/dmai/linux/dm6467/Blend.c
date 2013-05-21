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
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#ifdef CONFIG_VDCE
#include <linux/davinci_vdce.h>
#endif

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Blend.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Blend"

#define VDCE_DEVICE_NAME "/dev/DavinciHD_vdce"

/* Object holding the state of a Blending job. */
typedef struct Blend_Object {
    Int fd;
    Int inOffset;
    Int outOffset;
    Int inplace;
} Blend_Object;

const Blend_Attrs Blend_Attrs_DEFAULT = {
    0,
};

const Blend_Config_Params Blend_Config_Params_DEFAULT = {
    0,
    0,
    {
        { 0xf0, 0x5a, 0x51, 0xff, },
        { 0x22, 0x36, 0x91, 0xc0, },
        { 0x6e, 0xf0, 0x29, 0x80, },
        { 0xde, 0xca, 0x6a, 0x40, },
    },
};

/******************************************************************************
 * Blend_create
 ******************************************************************************/
Blend_Handle Blend_create(Blend_Attrs *attrs)
{
#ifdef CONFIG_VDCE
    Blend_Handle hBlend;

    hBlend = calloc(1, sizeof(Blend_Object));

    if (hBlend == NULL) {
        Dmai_err0("Failed to allocate space for Blend Object\n");
        return NULL;
    }

    hBlend->fd = open(VDCE_DEVICE_NAME, O_RDWR);

    if (hBlend->fd == -1) {
        Dmai_err1("Failed to open VDCE device: %s\n", VDCE_DEVICE_NAME);
        free(hBlend);
        return NULL;
    }

    return hBlend;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

/******************************************************************************
 * Blend_delete
 ******************************************************************************/
Int Blend_delete(Blend_Handle hBlend)
{
#ifdef CONFIG_VDCE
    if (hBlend) {
        close(hBlend->fd);
        free(hBlend);
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Blend_config
 ******************************************************************************/
Int Blend_config(Blend_Handle hBlend, Ccv_Handle hCcv, Buffer_Handle hBmpBuf,
                 Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf,
                 Blend_Config_Params *blendParams)
{
#ifdef CONFIG_VDCE
    vdce_params_t params;
    Int           i;
    Int16         width, height;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    BufferGfx_Dimensions bmpDim;

    /* Buffer needs to be graphics buffers */
    if (Buffer_getType(hSrcBuf) != Buffer_Type_GRAPHICS ||
        Buffer_getType(hDstBuf) != Buffer_Type_GRAPHICS) {

        Dmai_err0("Src and dst buffers need to be graphics buffers\n");
        return Dmai_EINVAL;
    }

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);
    BufferGfx_getDimensions(hBmpBuf, &bmpDim);

    /* Pitches must be a multiple of 8 */
    if (dstDim.lineLength % 8 || srcDim.lineLength % 8) {
        Dmai_err2("Dst (%ld) and src (%ld) pitch must be a multiple of 8\n",
                  dstDim.lineLength, srcDim.lineLength);
        return Dmai_EINVAL;
    }

    /*
     * If a color conversion job was supplied, do both color conversion and
     * blending as one VDCE operation.
     */
    if (hCcv) {
        if (Ccv_getMode(hCcv) != Ccv_Mode_YUV420SEMI_YUV422SEMI) {
            Dmai_err0("Unsupported Ccv mode for post codec mode\n");
            return Dmai_EINVAL;
        }

        if (BufferGfx_getColorSpace(hSrcBuf) != ColorSpace_YUV420PSEMI &&
            BufferGfx_getColorSpace(hDstBuf) != ColorSpace_YUV422PSEMI) {

            Dmai_err0("Src must be 420Psemi and dst 422Psemi\n");
            return Dmai_EINVAL;
        }

        params.vdce_mode = VDCE_OPERATION_POST_CODECMODE;

        /* Get the default parameters */
        if (ioctl(hBlend->fd, VDCE_GET_DEFAULT, &params) == -1) {
            Dmai_err0("Failed to get default VDCE params\n");
            return Dmai_EFAIL;
        }

        params.vdce_mode_params.ccv_params.conversion_type =
            VDCE_CCV_MODE_420_422;

        height = srcDim.height < dstDim.height ? srcDim.height: dstDim.height;
        width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;

        /* Enable blending, ccv is compulsory */
        params.modes_control = 0x2 | 0x8;

        /* Fill the blend values associated with every blend table */
        for(i = 0; i < 4; i++) {
            params.vdce_mode_params.postcodec_params.blend_params.
                bld_lut[i].blend_cr = blendParams->palette[i][0];
            params.vdce_mode_params.postcodec_params.blend_params.
                bld_lut[i].blend_cb = blendParams->palette[i][1];
            params.vdce_mode_params.postcodec_params.blend_params.
                bld_lut[i].blend_y = blendParams->palette[i][2];
            params.vdce_mode_params.postcodec_params.blend_params.
                bld_lut[i].blend_value = blendParams->palette[i][3];
        }
    }
    else {
        /* Sanity check buffers */
        if (BufferGfx_getColorSpace(hSrcBuf) !=
            BufferGfx_getColorSpace(hDstBuf)) {

            Dmai_err0("Src and dst buffers need to have same colorspace\n");
            return Dmai_EINVAL;
        }

        if (BufferGfx_getColorSpace(hSrcBuf) != ColorSpace_YUV420PSEMI &&
            BufferGfx_getColorSpace(hSrcBuf) != ColorSpace_YUV422PSEMI) {

            Dmai_err0("Colorspace format not supported\n");
            return Dmai_EINVAL;
        }

        /* inplace doesn't make sense when doing both ccv and blending */
        if (Buffer_getUserPtr(hSrcBuf) == Buffer_getUserPtr(hDstBuf)) {
            hBlend->inplace = TRUE;
        }

        params.vdce_mode = VDCE_OPERATION_BLENDING;

        /* Get the default parameters */
        if (ioctl(hBlend->fd, VDCE_GET_DEFAULT, &params) == -1) {
            Dmai_err0("Failed to get default VDCE params\n");
            return Dmai_EFAIL;
        }

        if (hBlend->inplace) {
            width = bmpDim.width;
            height = bmpDim.height;
        }
        else {
            height = srcDim.height < dstDim.height ?srcDim.height:dstDim.height;
            width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
        }

        /* Fill the blend values associated with every blend table */
        for(i = 0; i < 4; i++) {
            params.vdce_mode_params.blend_params.bld_lut[i].blend_cr =
                blendParams->palette[i][0];
            params.vdce_mode_params.blend_params.bld_lut[i].blend_cb =
                blendParams->palette[i][1];
            params.vdce_mode_params.blend_params.bld_lut[i].blend_y =
                blendParams->palette[i][2];
            params.vdce_mode_params.blend_params.bld_lut[i].blend_value =
                blendParams->palette[i][3];
        }
    }

    /* Width must be even */
    if (width % 2) {
        Dmai_err1("Width (%d) must be even\n", width);
        return Dmai_EINVAL;
    }

    if (hBlend->inplace) {
        /* X position must be aligned on 8 since resulting address must be */
        if (blendParams->bmpXpos % 8) {
            Dmai_err1("Bitmap X position (%d) must be a multiple of 8\n",
                      blendParams->bmpXpos);
            return Dmai_EINVAL;
        }
    }

    /* Set input size */
    params.common_params.src_hsz_luminance   = width;
    params.common_params.src_vsz_luminance   = height;

    /* Set output size  */
    params.common_params.dst_hsz_luminance   = width;
    params.common_params.dst_vsz_luminance   = height;

    /* Set the bitmap size */
    params.common_params.bmp_hsize           = bmpDim.width;
    params.common_params.bmp_vsize           = bmpDim.height;

    /* Set progressive mode */
    params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
    params.common_params.src_mode            = VDCE_FRAME_MODE;
    params.common_params.res_mode            = VDCE_FRAME_MODE;
    params.common_params.src_bmp_mode        = VDCE_FRAME_MODE;

    /* Postions the bitmap windows on the overall video window. */
    params.common_params.res_vsp_bitmap      = hBlend->inplace ? 0 :
        blendParams->bmpYpos;
    params.common_params.res_hsp_bitmap      = hBlend->inplace ? 0 :
        blendParams->bmpXpos;

    /* Set VDCE parameters */
    if (ioctl(hBlend->fd, VDCE_SET_PARAMS, &params) == -1) {
        Dmai_err0("Failed VDCE_SET_PARAMS\n");
        return Dmai_EFAIL;
    }

    hBlend->inOffset = hBlend->inplace ? blendParams->bmpYpos *
        srcDim.lineLength + blendParams->bmpXpos : 0;

    hBlend->outOffset = hBlend->inplace ? blendParams->bmpYpos *
            dstDim.lineLength + blendParams->bmpXpos : 0;

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Blend_execute
 ******************************************************************************/
Int Blend_execute(Blend_Handle hBlend, Buffer_Handle hBmpBuf,
                  Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_address_start_t params;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    BufferGfx_Dimensions bmpDim;
    UInt32 srcOffset, dstOffset;

    assert(hBlend);
    assert(hSrcBuf);
    assert(hDstBuf);

    /* VDCE addresses must be a multiple of 8 */
    assert((((UInt32) Buffer_getUserPtr(hDstBuf)) & 0x7) == 0);
    assert((((UInt32) Buffer_getUserPtr(hSrcBuf)) & 0x7) == 0);

    /* Buffer sizes / 4 must be a multiple of 8 */
    assert(((Buffer_getSize(hSrcBuf) / 4) & 0x7) == 0);
    assert(((Buffer_getSize(hDstBuf) / 4) & 0x7) == 0);

    BufferGfx_getDimensions(hBmpBuf, &bmpDim);
    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    assert(srcDim.x >= 0);
    assert(srcDim.y >= 0);
    assert(dstDim.x >= 0);
    assert(dstDim.y >= 0);

    /* x values needs to be a multiple of 8 because of address restriction */
    assert((srcDim.x & 0x7) == 0);
    assert((dstDim.x & 0x7) == 0);

    /* Pitch must be a multiple of 8 */
    assert((bmpDim.lineLength & 0x7) == 0);

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x;

    params.buffers[VDCE_BUF_IN].index       = -1;
    params.buffers[VDCE_BUF_IN].buf_type    = VDCE_BUF_IN;
    params.buffers[VDCE_BUF_IN].virt_ptr    = (Int)
                                              Buffer_getUserPtr(hSrcBuf) +
                                                  hBlend->inOffset + srcOffset;
    params.buffers[VDCE_BUF_IN].size        = Buffer_getSize(hSrcBuf);

    params.buffers[VDCE_BUF_OUT].index      = -1;
    params.buffers[VDCE_BUF_OUT].buf_type   = VDCE_BUF_OUT;
    params.buffers[VDCE_BUF_OUT].virt_ptr   = (Int)
                                              Buffer_getUserPtr(hDstBuf) +
                                                  hBlend->outOffset + dstOffset;
    params.buffers[VDCE_BUF_OUT].size       = Buffer_getSize(hDstBuf);

    params.buffers[VDCE_BUF_BMP].index      = -1;
    params.buffers[VDCE_BUF_BMP].buf_type   = VDCE_BUF_BMP;
    params.buffers[VDCE_BUF_BMP].virt_ptr   = (Int)
                                              Buffer_getUserPtr(hBmpBuf);
    params.buffers[VDCE_BUF_BMP].size       = Buffer_getSize(hBmpBuf);

    params.src_horz_pitch                   = srcDim.lineLength;
    params.res_horz_pitch                   = dstDim.lineLength;
    params.bmp_pitch                        = bmpDim.lineLength;

    if (ioctl(hBlend->fd, VDCE_START, &params) < 0) {
        Dmai_err0("Failed VDCE_START\n");
        return Dmai_EFAIL;
    }

    /* Don't alter the number of bytes used if the blending was done in place */
    if (!hBlend->inplace) {
        Buffer_setNumBytesUsed(hDstBuf, Buffer_getNumBytesUsed(hSrcBuf));
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}
