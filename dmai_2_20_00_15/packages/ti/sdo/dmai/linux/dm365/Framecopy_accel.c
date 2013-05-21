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

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/Framecopy.h>

#include "../../priv/_Framecopy.h"

#include <pthread.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <unistd.h>

#define MODULE_NAME     "Framecopy"

typedef struct Framecopy_Object {
    Framecopy_CommonObject  common;
    Int                     fd;
    Int                     bpp;
} Framecopy_Object;

/******************************************************************************
 * DM365MMAP Kernel Module Interface
 ******************************************************************************/
typedef struct {
    unsigned long src;
    unsigned long dst;
    unsigned int  srcmode;
    unsigned int  srcfifowidth;
    int           srcbidx;
    int           srccidx;
    unsigned int  dstmode;
    unsigned int  dstfifowidth;
    int           dstbidx;
    int           dstcidx;
    int           acnt;
    int           bcnt;
    int           ccnt;
    int           bcntrld;
    int           syncmode;
} dm365mmap_params_t;

#define DM365MMAP_DEVICE    "/dev/dm365mmap"

#define DM365MMAP_IOCMEMCPY        0x7
#define DM365MMAP_IOCWAIT          0x8
#define DM365MMAP_IOCCLEAR_PENDING 0x9

pthread_mutex_t Dmai_DM365dmaLock = PTHREAD_MUTEX_INITIALIZER;

/******************************************************************************
 * Framecopy_accel_create
 ******************************************************************************/
Framecopy_Handle Framecopy_accel_create(Framecopy_Attrs *attrs)
{
    Framecopy_Handle hFc;

    hFc = (Framecopy_Handle)calloc(1, sizeof(Framecopy_Object));

    if (hFc == NULL) {
        Dmai_err0("Failed to allocate space for Framecopy Object\n");
        return NULL;
    }

    hFc->fd = open(DM365MMAP_DEVICE, O_RDWR | O_SYNC);

    if (hFc->fd == -1) {
        Dmai_err1("Failed to open %s\n", DM365MMAP_DEVICE);
        return NULL;
    }

    return hFc;
}

/******************************************************************************
 * Framecopy_accel_config
 ******************************************************************************/
Int Framecopy_accel_config(Framecopy_Handle hFc,
                           Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    if(BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV422PSEMI) {
        return Dmai_ENOTIMPL;
    }

    hFc->bpp = ColorSpace_getBpp(BufferGfx_getColorSpace(hSrcBuf));

    if (hFc->bpp < 0) {
        return hFc->bpp;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Framecopy_accel_execute
 ******************************************************************************/
Int Framecopy_accel_execute(Framecopy_Handle hFc,
                             Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf)
{
    BufferGfx_Dimensions  srcDim;
    BufferGfx_Dimensions  dstDim;
    UInt32                srcOffset = 0;
    UInt32                dstOffset = 0;
    dm365mmap_params_t    dm365mmap_params;
    unsigned long         src, dst;
    Int                   width, height;

    BufferGfx_getDimensions(hSrcBuf, &srcDim);
    BufferGfx_getDimensions(hDstBuf, &dstDim);

    srcOffset = (srcDim.y * srcDim.lineLength) + (srcDim.x * (hFc->bpp >> 3));
    dstOffset = (dstDim.y * dstDim.lineLength) + (dstDim.x * (hFc->bpp >> 3));

    /* Select the smallest resolution */
    width = srcDim.width < dstDim.width ? srcDim.width : dstDim.width;
    height = srcDim.height < dstDim.height ? srcDim.height : dstDim.height;

    dm365mmap_params.src      = Buffer_getPhysicalPtr(hSrcBuf) + srcOffset;
    dm365mmap_params.srcmode  = 0;
    dm365mmap_params.dst      = Buffer_getPhysicalPtr(hDstBuf) + dstOffset;
    dm365mmap_params.dstmode  = 0;
    dm365mmap_params.srcbidx  = srcDim.lineLength;
    dm365mmap_params.dstbidx  = dstDim.lineLength;
    dm365mmap_params.acnt     = width * (hFc->bpp >> 3);
    dm365mmap_params.bcnt     = height;
    dm365mmap_params.ccnt     = 1;
    dm365mmap_params.bcntrld  = dm365mmap_params.bcnt;
    dm365mmap_params.syncmode = 1;

    /* DMA function is not re-entrant -- guard with mutex */
    pthread_mutex_lock(&Dmai_DM365dmaLock);
    if (ioctl(hFc->fd, DM365MMAP_IOCMEMCPY, &dm365mmap_params) == -1) {
        Dmai_err0("Failed to execute memcpy\n");
        pthread_mutex_unlock(&Dmai_DM365dmaLock);
        return Dmai_EFAIL;
    }
    pthread_mutex_unlock(&Dmai_DM365dmaLock);

    if (BufferGfx_getColorSpace(hSrcBuf) == ColorSpace_YUV420PSEMI) {

        assert((srcDim.y & 0x1) == 0);
        assert((dstDim.y & 0x1) == 0);
    
        srcOffset = srcDim.y * srcDim.lineLength / 2 +
            srcDim.x * (hFc->bpp >> 3);
        dstOffset = dstDim.y * dstDim.lineLength / 2 +
            dstDim.x * (hFc->bpp >> 3);

        src = Buffer_getPhysicalPtr(hSrcBuf) + srcOffset +
            (Buffer_getSize(hSrcBuf) * 2 / 3);
        dst = Buffer_getPhysicalPtr(hDstBuf) + dstOffset + 
            (Buffer_getSize(hDstBuf) * 2 / 3);

        dm365mmap_params.src      = src;
        dm365mmap_params.srcmode  = 0;
        dm365mmap_params.dst      = dst;
        dm365mmap_params.dstmode  = 0;
        dm365mmap_params.srcbidx  = srcDim.lineLength;
        dm365mmap_params.dstbidx  = dstDim.lineLength;
        dm365mmap_params.acnt     = srcDim.width * (hFc->bpp >> 3);
        dm365mmap_params.bcnt     = srcDim.height / 2;
        dm365mmap_params.ccnt     = 1;
        dm365mmap_params.bcntrld  = dm365mmap_params.bcnt;
        dm365mmap_params.syncmode = 1;

        /* DMA function is not re-entrant -- guard with mutex */
        pthread_mutex_lock(&Dmai_DM365dmaLock);
        if (ioctl(hFc->fd, DM365MMAP_IOCMEMCPY, &dm365mmap_params) == -1) {
            Dmai_err0("Failed to execute memcpy\n");
            pthread_mutex_unlock(&Dmai_DM365dmaLock);
            return Dmai_EFAIL;
        }
        pthread_mutex_unlock(&Dmai_DM365dmaLock);
        
    }

    if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI) {
        Buffer_setNumBytesUsed(hDstBuf, 
            dstDim.width * dstDim.height * 3 / 2);
    }
    else {
        Buffer_setNumBytesUsed(hDstBuf, 
            dstDim.width * dstDim.height * (hFc->bpp >> 3));
    }

    return Dmai_EOK;
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
