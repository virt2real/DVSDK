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
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#ifdef CONFIG_VDCE
#include <linux/davinci_vdce.h>
#endif

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Resize.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Resize"

#define VDCE_DEVICE_NAME "/dev/DavinciHD_vdce"

const Resize_Attrs Resize_Attrs_DEFAULT = {
    0,
};

typedef struct Resize_Object {
    Int fd;
} Resize_Object;

/******************************************************************************
 * Resize_create
 ******************************************************************************/
Resize_Handle Resize_create(Resize_Attrs *attrs)
{
#ifdef CONFIG_VDCE
    Resize_Handle hResize;

    hResize = calloc(1, sizeof(Resize_Object));

    if (hResize == NULL) {
        Dmai_err0("Failed to allocate space for Resize Object\n");
        return NULL;
    }

    hResize->fd = open(VDCE_DEVICE_NAME, O_RDWR);

    if (hResize->fd == -1) {
        Dmai_err1("Unable to open VDCE device: %s\n", VDCE_DEVICE_NAME);
        free(hResize);
        return NULL;
    }

    return hResize;
#else
    Dmai_err0("not implemented\n");
    return NULL;
#endif
}

/******************************************************************************
 * Resize_config
 ******************************************************************************/
Int Resize_config(Resize_Handle hResize,
                  Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_params_t params;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    Int vrsz, hrsz;

    /* Buffer needs to be graphics buffers */
    if (Buffer_getType(hSrcBuf) != Buffer_Type_GRAPHICS ||
        Buffer_getType(hDstBuf) != Buffer_Type_GRAPHICS) {

        Dmai_err0("Src and dst buffers need to be graphics buffers\n");
        return Dmai_EINVAL;
    }

    /* Sanity check buffer color space */
    if (BufferGfx_getColorSpace(hSrcBuf) !=
        BufferGfx_getColorSpace(hDstBuf)) {

        Dmai_err0("Src and dst buffers need to have same colorspace\n");
        return Dmai_EINVAL;
    }

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    Dmai_dbg6("Configuring resize from %dx%d (pitch %d) to %dx%d (pitch %d)\n",
              srcDim.width, srcDim.height, srcDim.lineLength,
              dstDim.width, dstDim.height, dstDim.lineLength);

    /* Source and destination width must be even */
    if (dstDim.width % 2 || srcDim.width % 2) {
        Dmai_err2("Output (%d) and input width (%d) must be even\n",
                  dstDim.width, srcDim.width);
        return Dmai_EINVAL;
    }

    /* Pitches must be a multiple of 8 */
    if (dstDim.lineLength % 8 || srcDim.lineLength % 8) {
        Dmai_err2("Dst (%ld) and src (%ld) pitch must be a multiple of 8\n",
                  dstDim.lineLength, srcDim.lineLength);
        return Dmai_EINVAL;
    }

    hrsz = srcDim.width * 256 / dstDim.width;
    vrsz = srcDim.height * 256 / dstDim.height;

    /* The driver can only resize from 1x to 1/8x (no upscaling) */
    if (hrsz < 256 || hrsz > 2048 || vrsz < 256 || vrsz > 2048) {
        Dmai_err4("Resize between %dx%d and %dx%d not supported\n",
                  srcDim.width, srcDim.height, dstDim.width, dstDim.height);
        return Dmai_EINVAL;
    }

    params.vdce_mode = VDCE_OPERATION_RESIZING;

    if (ioctl(hResize->fd, VDCE_GET_DEFAULT, &params) < 0) {
        Dmai_err0("default params failed error.\n");
        return Dmai_EFAIL;
    }

    switch (BufferGfx_getColorSpace(hSrcBuf)) {
        case ColorSpace_YUV422PSEMI:
            params.vdce_mode_params.rsz_params.rsz_mode = VDCE_MODE_422;
            /* Speed up the conversion, note that this value hangs the resizer
             * for 420P color format 
             */
            params.common_params.prcs_unit_value = 256;
            break;
        case ColorSpace_YUV420PSEMI:
            params.vdce_mode_params.rsz_params.rsz_mode = VDCE_MODE_420;
            break;
        default:
            Dmai_err0("Colorspace format not supported\n");
            return Dmai_ENOTIMPL;
    }
 
    params.common_params.src_hsz_luminance = srcDim.width;
    params.common_params.src_vsz_luminance = srcDim.height;

    params.common_params.dst_hsz_luminance = dstDim.width;
    params.common_params.dst_vsz_luminance = dstDim.height;

    params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
    params.common_params.src_mode = VDCE_FRAME_MODE;
    params.common_params.res_mode = VDCE_FRAME_MODE;

    /* call ioctl to set parameters */
    if (ioctl(hResize->fd, VDCE_SET_PARAMS, &params) < 0) {
        Dmai_err0("VDCE_SET_PARAMS failed \n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Resize_execute
 ******************************************************************************/
Int Resize_execute(Resize_Handle hResize,
                   Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_address_start_t params;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 srcOffset, dstOffset;

    assert(hResize);
    assert(hSrcBuf);
    assert(hDstBuf);

    /* VDCE addresses must be a multiple of 8 */
    assert((((UInt32) Buffer_getUserPtr(hDstBuf)) & 0x7) == 0);
    assert((((UInt32) Buffer_getUserPtr(hSrcBuf)) & 0x7) == 0);

    /* Buffer sizes / 4 must be a multiple of 8 */
    assert(((Buffer_getSize(hSrcBuf) / 4) & 0x7) == 0);
    assert(((Buffer_getSize(hDstBuf) / 4) & 0x7) == 0);

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    assert(srcDim.x >= 0);
    assert(srcDim.y >= 0);
    assert(dstDim.x >= 0);
    assert(dstDim.y >= 0);
    assert((srcDim.x & 0x7) == 0);
    assert((dstDim.x & 0x7) == 0);

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x;

    params.buffers[VDCE_BUF_IN].index     = -1;
    params.buffers[VDCE_BUF_IN].buf_type  = VDCE_BUF_IN;
    params.buffers[VDCE_BUF_IN].virt_ptr  = ((Int32) Buffer_getUserPtr(hSrcBuf)+
                                                     srcOffset);
    params.buffers[VDCE_BUF_IN].size      = Buffer_getSize(hSrcBuf);

    params.buffers[VDCE_BUF_OUT].index    = -1;
    params.buffers[VDCE_BUF_OUT].buf_type = VDCE_BUF_OUT;
    params.buffers[VDCE_BUF_OUT].virt_ptr = ((Int32) Buffer_getUserPtr(hDstBuf)+
                                                     dstOffset);
    params.buffers[VDCE_BUF_OUT].size     = Buffer_getSize(hDstBuf);

    params.src_horz_pitch = srcDim.lineLength;
    params.res_horz_pitch = dstDim.lineLength;

    if (ioctl(hResize->fd, VDCE_START, &params) < 0) {
        Dmai_err0("Failed VDCE_START\n");
        return Dmai_EFAIL;
    }

    if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI) {
        Buffer_setNumBytesUsed(hDstBuf, dstDim.width * dstDim.height * 3 / 2);
    }
    else {
        Buffer_setNumBytesUsed(hDstBuf, dstDim.width * dstDim.height * 2);
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Resize_delete
 ******************************************************************************/
Int Resize_delete(Resize_Handle hResize)
{
#ifdef CONFIG_VDCE
    if (hResize) {
        close(hResize->fd);
        free(hResize);
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}
