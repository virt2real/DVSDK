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

#include <pthread.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>

#ifdef CONFIG_DM355_IPIPE
#include <media/davinci/imp_previewer.h>
#include <media/davinci/imp_resizer.h>
#include <media/davinci/dm355_ipipe.h>
#endif

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/Resize.h>

#define MODULE_NAME   "Resize"
#define RESIZER_DEVICE   "/dev/davinci_resizer"
#define PREVIEWER_DEVICE "/dev/davinci_previewer"

typedef struct Resize_Object {
    int   fd;
} Resize_Object;

const Resize_Attrs Resize_Attrs_DEFAULT = {
    Resize_FilterType_LOWPASS,
    Resize_FilterType_LOWPASS,
    Resize_WindowType_BLACKMAN,
    Resize_WindowType_BLACKMAN,
    0xe
};

/******************************************************************************
 * Resize_create
 ******************************************************************************/
Resize_Handle Resize_create(Resize_Attrs *attrs)
{
#ifdef CONFIG_DM355_IPIPE
    Resize_Handle hResize;
    unsigned long oper_mode;    

    assert(attrs);

    hResize = (Resize_Handle)calloc(1, sizeof(Resize_Object));

    if (hResize == NULL) {
        Dmai_err0("Failed to allocate space for Framecopy Object\n");
        return NULL;
    }

    /* Open resizer device */
    hResize->fd = open(RESIZER_DEVICE, O_RDWR);

    if (hResize->fd == -1) {
        Dmai_err1("Failed to open %s\n", RESIZER_DEVICE);
        return NULL;
    }

    oper_mode = IMP_MODE_SINGLE_SHOT;

    if (ioctl(hResize->fd,RSZ_S_OPER_MODE, &oper_mode) < 0) {
        Dmai_err0("Resizer can't set operation mode\n");        
        goto cleanup;
    }

    if (ioctl(hResize->fd,RSZ_G_OPER_MODE, &oper_mode) < 0) {
        Dmai_err0("Resizer can't get operation mode\n");        
        goto cleanup;
    }
    
    if (oper_mode != IMP_MODE_SINGLE_SHOT) {
        Dmai_err1("Resizer can't set operation mode single shot, the mode is %d\n",
            oper_mode);        
        goto cleanup;
    }

    return hResize;

cleanup:
    close(hResize->fd);
    hResize->fd = 0;
    return NULL;
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
#ifdef CONFIG_DM355_IPIPE
    BufferGfx_Dimensions srcDim, dstDim;
    UInt                 hDif;
    UInt                 vDif;    
    struct rsz_channel_config rsz_chan_config;
    struct rsz_single_shot_config rsz_ss_config;

    /* Make sure our input parameters are valid */
    if (!hResize) {
        Dmai_err0("Resize_Handle parameter must not be NULL\n");
        return Dmai_EINVAL;
    }   
    
    if (!hSrcBuf) {
        Dmai_err0("Source buffer parameter must not be NULL\n");
        return Dmai_EINVAL;
    }   

    if (!hDstBuf) {
        Dmai_err0("Destination buffer parameter must not be NULL\n");
        return Dmai_EINVAL;
    }
    
    /* Buffer needs to be graphics buffers */
    if (Buffer_getType(hSrcBuf) != Buffer_Type_GRAPHICS ||
        Buffer_getType(hDstBuf) != Buffer_Type_GRAPHICS) {

        Dmai_err0("Src and dst buffers need to be graphics buffers\n");
        return Dmai_EINVAL;
    }
    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    if (dstDim.width <= 0) {
        Dmai_err0("Destination buffer width must be greater than zero\n");
        return Dmai_EINVAL;
    }

    if (dstDim.height <= 0) {
        Dmai_err0("Destination buffer height must be greater than zero\n");
        return Dmai_EINVAL;
    }

    if ((srcDim.lineLength & 0x1F) != 0) {
        Dmai_err0("Source buffer pitch must be a multiple of 32 bytes\n");
        return Dmai_EINVAL;
    }

    if ((dstDim.lineLength & 0x1F) != 0) {
        Dmai_err0("Destination buffer pitch must be a multiple of 32 bytes\n");
        return Dmai_EINVAL;
    }


    /* Check for valid buffer scaling */
    hDif = srcDim.width  * 256 / dstDim.width;
    vDif = srcDim.height * 256 / dstDim.height;

    if (hDif < 32) {
        Dmai_err0("Horizontal up-scaling must not exceed 8x\n");
        return Dmai_EINVAL;
    }

    if (hDif > 4096) {
        Dmai_err0("Horizontal down-scaling must not exceed 1/16x\n");
        return Dmai_EINVAL;
    }

    if (vDif < 32) {
        Dmai_err0("Vertical up-scaling must not exceed 8x\n");
        return Dmai_EINVAL;
    }

    if (vDif > 4096) {
        Dmai_err0("Vertical down-scaling must not exceed 1/16x\n");
        return Dmai_EINVAL;
    }

    /* Set the driver default parameters and retrieve what was set */
    Dmai_clear(rsz_ss_config);
    rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
    rsz_chan_config.chain = 0;
    rsz_chan_config.len = 0;
    rsz_chan_config.config = NULL; /* to set defaults in driver */
    if (ioctl(hResize->fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
        Dmai_err0("Error in setting default configuration for single shot mode\n");
        goto cleanup;
    }

    /* default configuration setting in Resizer successfull */
    Dmai_clear(rsz_ss_config);
    rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
    rsz_chan_config.chain = 0;
    rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
    rsz_chan_config.config = &rsz_ss_config;

    if (ioctl(hResize->fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
        Dmai_err0("Error in getting resizer channel configuration from driver\n");
        goto cleanup;
    }

    /* input params are set at the resizer */
    rsz_ss_config.input.image_width  = srcDim.width;
    rsz_ss_config.input.image_height = srcDim.height;
    rsz_ss_config.input.line_length  = srcDim.lineLength;
    rsz_ss_config.input.ppln = rsz_ss_config.input.image_width + 8;
    rsz_ss_config.input.lpfr = rsz_ss_config.input.image_height + 10;
    rsz_ss_config.input.pix_fmt = IPIPE_UYVY;
    rsz_ss_config.output1.pix_fmt = IPIPE_UYVY;
    rsz_ss_config.output1.enable = 1;
    rsz_ss_config.output1.width = dstDim.width;
    rsz_ss_config.output1.height = dstDim.height;
    rsz_ss_config.output1.line_length = dstDim.lineLength;
    rsz_ss_config.output2.enable = 0;

    rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
    rsz_chan_config.chain = 0;
    rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
    if (ioctl(hResize->fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
        Dmai_err0("Error in setting default configuration for single shot mode\n");
        goto cleanup;
    }
    rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
    rsz_chan_config.chain = 0;
    rsz_chan_config.len = sizeof(struct rsz_single_shot_config);

    /* read again and verify */
    if (ioctl(hResize->fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
        Dmai_err0("Error in getting configuration from driver\n");
        goto cleanup;
    }

    return Dmai_EOK;

cleanup:
    close(hResize->fd);
    hResize->fd = 0;    
    return Dmai_EFAIL;
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
#ifdef CONFIG_DM355_IPIPE
    struct imp_convert  rsz;
    BufferGfx_Dimensions srcDim;
    BufferGfx_Dimensions dstDim;
    UInt32               srcOffset;
    UInt32               dstOffset;

    assert(hResize);
    assert(hSrcBuf);
    assert(hDstBuf);

    Dmai_clear(rsz);

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    srcOffset = srcDim.y * srcDim.lineLength + (srcDim.x << 1);
    dstOffset = dstDim.y * dstDim.lineLength + (dstDim.x << 1);

    rsz.in_buff.index     = -1;
    rsz.in_buff.buf_type  = IMP_BUF_IN;
    rsz.in_buff.offset    = (UInt32) Buffer_getUserPtr(hSrcBuf) + srcOffset;
    rsz.in_buff.size      = Buffer_getSize(hSrcBuf);

    rsz.out_buff1.index    = -1;
    rsz.out_buff1.buf_type = IMP_BUF_OUT1;
    rsz.out_buff1.offset   = (UInt32) Buffer_getUserPtr(hDstBuf) + dstOffset;
    rsz.out_buff1.size     = Buffer_getSize(hDstBuf);
    
    /* 
     * The IPIPE requires that the memory offsets of the input and output
     * buffers start on 32-byte boundaries.
     */
    assert((rsz.in_buff.offset  & 0x1F) == 0);
    assert((rsz.out_buff1.offset & 0x1F) == 0);

    /* Start IPIPE operation */
    if (ioctl(hResize->fd, RSZ_RESIZE, &rsz) == -1) {
        Dmai_err0("Failed RSZ_RESIZE\n");
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
 * Resize_delete
 ******************************************************************************/
Int Resize_delete(Resize_Handle hResize)
{
#ifdef CONFIG_DM355_IPIPE
    if (hResize) {
        close(hResize->fd);
        free(hResize);
    }
#endif
    return Dmai_EOK;
}
