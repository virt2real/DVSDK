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

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/Framecopy.h>

#include "../../priv/_Framecopy.h"

#define ti_sdo_fc_ires_NOPROTOCOLREV

#include <ti/sdo/fc/scpy/scpy.h>
#include <ti/sdo/fc/ires/sdma/ires_sdma.h>
#include <ti/sdo/linuxutils/sdma/include/sdma.h>

#define MODULE_NAME     "Framecopy"

typedef struct Framecopy_Object {
    Framecopy_CommonObject  common;
    IRES_SDMA_Obj           sdmaObj;
    SDMA_ChannelDescriptor  chan;
} Framecopy_Object;

/******************************************************************************
 * Framecopy_sdma_accel_create
 ******************************************************************************/
Framecopy_Handle Framecopy_sdma_accel_create(Framecopy_Attrs *attrs)
{
    Framecopy_Handle hFc;

    Dmai_dbg0("Creating SDMA accelerated framecopy\n");

    hFc = (Framecopy_Handle)calloc(1, sizeof(Framecopy_Object));

    if (hFc == NULL) {
        Dmai_err0("Failed to allocate space for Framecopy Object\n");
        return NULL;
    }

    SDMA_init();

    hFc->chan.chanNum = -1;   /* Channel number will be returned here */
    hFc->chan.addr = NULL;    /* Address will be returned here */

    if (SDMA_getChannels(1, &hFc->chan) != SDMA_OK) {
        Dmai_err0("Failed to allocate dma channel\n");
        free(hFc);
        return NULL;
    }

    hFc->sdmaObj.channel = &hFc->chan;

    return hFc;
}

/******************************************************************************
 * Framecopy_sdma_accel_config
 ******************************************************************************/
Int Framecopy_sdma_accel_config(Framecopy_Handle hFramecopy,
                           Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    return Dmai_EOK;
}

/******************************************************************************
 * Framecopy_sdma_accel_execute
 ******************************************************************************/
Int Framecopy_sdma_accel_execute(Framecopy_Handle hFc,
                             Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    BufferGfx_Dimensions    srcDim, dstDim;
    SCPY_TransferParams     transParams;
    SCPY_AddrParams         src, dst;
    SCPY_Params             scpyParams;
    UInt32                  srcOffset, dstOffset;
    Int32                   width, height;

    /* Modifications to perform burst mode copy */
    IRES_SDMA_Handle handle = &hFc->sdmaObj;
    unsigned int dmaAddr =  (unsigned int)handle->channel->addr;
    IRES_SDMA_RegisterLayer * regs = (IRES_SDMA_RegisterLayer *)(dmaAddr);
    /* Modifications to perform burst mode copy */

    assert(Buffer_getUserPtr(hSrcBuf));
    assert(Buffer_getUserPtr(hDstBuf));

    /* Pointers must be even since we have codependent pixels */
    assert(!(((UInt32) Buffer_getUserPtr(hSrcBuf)) & 1));
    assert(!(((UInt32) Buffer_getUserPtr(hDstBuf)) & 1));

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    /* X must be even since UYVY has codependent pixels */
    assert(!(srcDim.x & 1));
    assert(!(dstDim.x & 1));

    srcOffset = srcDim.y * srcDim.lineLength + srcDim.x * 2;
    dstOffset = dstDim.y * dstDim.lineLength + dstDim.x * 2;

    /* Select the smallest width and height */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;

    /*
     * Width must be even because UYVY has codependent pixels,
     * and we optimize using 32 bit transfers.
     */
    assert(!(width & 1));

    src.addr_mode           = OMAP_DMA_AMODE_POST_DOUBLE_INDEX;
    src.addr                = (Uns) Buffer_getUserPtr(hSrcBuf) + srcOffset;
    src.elem_index          = 1;
    src.frame_index         = (srcDim.lineLength - width * 2) + 1;

    dst.addr_mode           = OMAP_DMA_AMODE_POST_DOUBLE_INDEX;
    dst.addr                = (Uns) Buffer_getUserPtr(hDstBuf) + dstOffset;
    dst.elem_index          = 1;
    dst.frame_index         = (dstDim.lineLength - width * 2) + 1;

    transParams.dataType    = OMAP_DMA_DATA_TYPE_S32;
    transParams.elemCount   = width >> 1;
    transParams.frameCount  = height;

    scpyParams.src          = &src;
    scpyParams.dst          = &dst;
    scpyParams.transfer     = &transParams;

    SCPY_configure(&hFc->sdmaObj, &scpyParams);

    /* Modifications to perform burst mode copy */
    /* Ensure that the source and destination addresses are 64 byte aligned.
    ** The below code would not work if the addresses are not 64 byte aligned
    ** In case of CMEM allocated buffers, they are page aligned (4K bytes aligned).
    ** and hence should work with the code below
    */
    /* configure for the source burst mode enable - 64 byte burst */
    regs->DMA4_CSDP &= ~(0x03 << 7);
    regs->DMA4_CSDP |= (0x03 << 7); 
    /* configure for the destination burst mode enable - 64 byte burst*/
    regs->DMA4_CSDP &= ~(0x03 << 14);
    regs->DMA4_CSDP |= (0x03 << 14);
    /* Modifications to perform burst mode copy */

    SCPY_start(&hFc->sdmaObj);
    SCPY_wait(&hFc->sdmaObj);

    return Dmai_EOK;
}

/******************************************************************************
 * Framecopy_sdma_accel_delete
 ******************************************************************************/
Int Framecopy_sdma_accel_delete(Framecopy_Handle hFc)
{
    Int ret = Dmai_EOK;

    if (SDMA_freeChannels(1, &hFc->chan)) {
        ret = Dmai_EFAIL;
    }

    SDMA_exit();

    free(hFc);

    return ret;
}
