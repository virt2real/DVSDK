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

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/Framecopy.h>

#ifdef CONFIG_VDCE
#include <linux/davinci_vdce.h>
#endif

#include "../../priv/_Framecopy.h"

#define VDCE_DEVICE_NAME "/dev/DavinciHD_vdce"

typedef struct Framecopy_Object {
    Framecopy_CommonObject  common;
    Int                     fd;
} Framecopy_Object;

#define MODULE_NAME     "Framecopy"

/******************************************************************************
 * Framecopy_accel_create
 ******************************************************************************/
Framecopy_Handle Framecopy_accel_create(Framecopy_Attrs *attrs)
{
#ifdef CONFIG_VDCE
    Framecopy_Handle hFc;

    hFc = calloc(1, sizeof(Framecopy_Object));

    if (hFc == NULL) {
        Dmai_err0("Failed to allocate space for Framecopy Object\n");
        return NULL;
    }

    hFc->fd = open(VDCE_DEVICE_NAME, O_RDWR);

    if (hFc->fd == -1) {
        Dmai_err1("Unable to open VDCE device: %s\n", VDCE_DEVICE_NAME);
        free(hFc);
        return NULL;
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
Int Framecopy_accel_config(Framecopy_Handle hFc,
                           Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_params_t params;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    Int width, height;

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

   /* Select the smallest resolution */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;

    Dmai_dbg2("Configuring resizer to copy image resolution %dx%d\n",
              width, height);

    params.vdce_mode = VDCE_OPERATION_RESIZING;

    if (ioctl(hFc->fd, VDCE_GET_DEFAULT, &params) < 0) {
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
 
    params.common_params.src_hsz_luminance = width;
    params.common_params.src_vsz_luminance = height;

    params.common_params.dst_hsz_luminance = width;
    params.common_params.dst_vsz_luminance = height;

    params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
    params.common_params.src_mode = VDCE_FRAME_MODE;
    params.common_params.res_mode = VDCE_FRAME_MODE;

    /* call ioctl to set parameters */
    if (ioctl(hFc->fd, VDCE_SET_PARAMS, &params) < 0) {
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
 * Framecopy_accel_execute
 ******************************************************************************/
Int Framecopy_accel_execute(Framecopy_Handle hFc,
                             Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
#ifdef CONFIG_VDCE
    vdce_address_start_t params;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32 srcOffset, dstOffset;

    assert(hFc);
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

    if (ioctl(hFc->fd, VDCE_START, &params) < 0) {
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
 * Framecopy_accel_delete
 ******************************************************************************/
Int Framecopy_accel_delete(Framecopy_Handle hFc)
{
#ifdef CONFIG_VDCE
    if (hFc) {
        close(hFc->fd);
        free(hFc);
    }

    return Dmai_EOK;
#else
    Dmai_err0("not implemented\n");
    return Dmai_ENOTIMPL;
#endif
}

