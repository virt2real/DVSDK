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
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>

#ifdef CONFIG_VDCE
#include <linux/davinci_vdce.h>
#endif

#include <xdc/std.h>
#include <ti/sdo/dmai/Ccv.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "../../priv/_Ccv.h"

#define MODULE_NAME     "Ccv"

#define VDCE_DEVICE_NAME "/dev/DavinciHD_vdce"

/******************************************************************************
 * Ccv_accel_init
 ******************************************************************************/
Int Ccv_accel_init(Ccv_Handle hCcv, Ccv_Attrs *attrs)
{
#ifdef CONFIG_VDCE
    hCcv->fd = open(VDCE_DEVICE_NAME, O_RDWR);

    if (hCcv->fd == -1) {
        Dmai_err1("Unable to open VDCE device: %s\n", VDCE_DEVICE_NAME);
        return Dmai_EIO;
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Ccv_accel_config
 ******************************************************************************/
Int Ccv_accel_config(Ccv_Handle hCcv,
                     Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_params_t params;
    vdce_ccv_mode_t mode;
    Int32 width, height;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;

    /* Width must be even */
    if (width % 2) {
        Dmai_err1("Width (%d) must be even\n", width);
        return Dmai_EINVAL;
    }

    /* Pitches must be a multiple of 8 */
    if (dstDim.lineLength % 8 || srcDim.lineLength % 8) {
        Dmai_err2("Dst (%ld) and src (%ld) pitch must be a multiple of 8\n",
                  dstDim.lineLength, srcDim.lineLength);
        return Dmai_EINVAL;
    }

    switch (BufferGfx_getColorSpace(hSrcBuf)) {
        case ColorSpace_YUV422PSEMI:
            if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI) {
                mode = VDCE_CCV_MODE_422_420;
                hCcv->mode = Ccv_Mode_YUV422SEMI_YUV420SEMI;
            }
            else {
                Dmai_err0("Mode not supported accelerated for YUV422PSEMI src\n");
                return Dmai_ENOTIMPL;
            }
            break;
        case ColorSpace_YUV420PSEMI:
            if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV422PSEMI) {
                mode = VDCE_CCV_MODE_420_422;
                hCcv->mode = Ccv_Mode_YUV420SEMI_YUV422SEMI;
            }
            else {
                Dmai_err0("Mode not supported accelerated for YUV420PSEMI src\n");
                return Dmai_ENOTIMPL;
            }
            break;
        default:
            Dmai_err0("Mode not supported accelerated\n");
            return Dmai_ENOTIMPL;
    }

    params.vdce_mode = VDCE_OPERATION_CHROMINANCE_CONVERSION;

    if (ioctl(hCcv->fd, VDCE_GET_DEFAULT, &params) < 0) {
        Dmai_err0("Failed VDCE_GET_DEFAULT\n");
        return Dmai_EFAIL;
    }

    params.vdce_mode_params.ccv_params.conversion_type = mode;

    /* set input size */
    params.common_params.src_hsz_luminance = width;
    params.common_params.src_vsz_luminance = height;

    /* set output size */
    params.common_params.dst_hsz_luminance = width;
    params.common_params.dst_vsz_luminance = height;

    params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
    params.common_params.src_mode = VDCE_FRAME_MODE;
    params.common_params.res_mode = VDCE_FRAME_MODE;

    /* speed up the conversion */
    params.common_params.prcs_unit_value = 256;
    if(Buffer_getUserPtr(hSrcBuf) == Buffer_getUserPtr(hDstBuf)) {
        Dmai_dbg0("Configuring for CbCr conversion only\n");
        params.common_params.proc_control = VDCE_CHROMA_ENABLE;
    }
    /* call ioctl to set parameters */
    if (ioctl(hCcv->fd, VDCE_SET_PARAMS, &params) < 0) {
        Dmai_err0("Failed VDCE_SET_PARAMS\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

/******************************************************************************
 * Ccv_accel_execute
 ******************************************************************************/
Int Ccv_accel_execute(Ccv_Handle hCcv, Buffer_Handle hSrcBuf,
                      Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_address_start_t params;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 srcOffset, dstOffset;

    assert(hCcv);
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

    /*
     * Cannot use y dimensions for YUV420 semiplanar buffers due to limitation
     * in VDCE driver.
     */
    assert(!((BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV420PSEMI) &&
             (srcDim.y > 0)));
    assert(!((BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI) &&
             (dstDim.y > 0)));

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

    if (ioctl(hCcv->fd, VDCE_START, &params) < 0) {
        Dmai_err0("Failed VDCE_START\n");
        return Dmai_EFAIL;
    }

    if (hCcv->mode == Ccv_Mode_YUV422SEMI_YUV420SEMI) {
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
 * Ccv_accel_exit
 ******************************************************************************/
Int Ccv_accel_exit(Ccv_Handle hCcv)
{
#ifdef CONFIG_VDCE
    close(hCcv->fd);

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

