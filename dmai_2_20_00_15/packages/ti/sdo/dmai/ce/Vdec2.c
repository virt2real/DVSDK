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
#include <string.h>
#include <stdlib.h>

#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video2/viddec2.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Vdec2.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Vdec2"

/* As 0 is not a valid buffer id in XDM 1.0, we need macros for easy access */
#define GETID(x)  ((x) + 1)
#define GETIDX(x) ((x) - 1)

typedef struct Vdec2_Object {
    VIDDEC2_Handle          hDecode;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[IVIDDEC2_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[IVIDDEC2_MAX_IO_BUFFERS];
    Int32                   maxNumDisplayBufs;
    BufTab_Handle           hOutBufTab;
    Buffer_Handle           hFreeBufs[IVIDDEC2_MAX_IO_BUFFERS];
    Int                     freeBufIdx;
    Buffer_Handle           hDisplayBufs[IVIDDEC2_MAX_IO_BUFFERS];
    Int                     displayBufIdx;
    VIDDEC2_DynamicParams   dynParams;
} Vdec2_Object;

const VIDDEC2_Params Vdec2_Params_DEFAULT = {
    sizeof(VIDDEC2_Params),             /* size */
    576,                                /* maxHeight */
    720,                                /* maxWidth */
    30000,                              /* maxFrameRate */
    6000000,                            /* maxBitRate */
    XDM_BYTE,                           /* dataEndianess */
    XDM_YUV_420P,                       /* forceChromaFormat */
};

const VIDDEC2_DynamicParams Vdec2_DynamicParams_DEFAULT = {
    sizeof(VIDDEC2_DynamicParams),      /* size */
    XDM_DECODE_AU,                      /* decodeHeader */
    0,                                  /* displayWidth */
    IVIDEO_NO_SKIP,                     /* frameSkipMode */
    IVIDDEC2_DISPLAY_ORDER,             /* frameOrder */
    0,                                  /* newFrameFlag */
    0,                                  /* mbDataFlag */
};

/******************************************************************************
 * Vdec2_process
 ******************************************************************************/
Int Vdec2_process(Vdec2_Handle hVd, Buffer_Handle hInBuf,
                  Buffer_Handle hDstBuf)
{
    VIDDEC2_InArgs          inArgs;
    VIDDEC2_OutArgs         outArgs;
    XDM1_BufDesc            inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              outBufSizeArray[XDM_MAX_IO_BUFFERS];
    XDAS_Int8              *outBufPtrArray[XDM_MAX_IO_BUFFERS];
    XDAS_Int32              status;
    Int                     bufIdx;
    BufferGfx_Dimensions    dim;
    XDAS_Int8              *inPtr, *dstPtr;
    Int                     ret = Dmai_EOK;
    UInt32                  offset;
    UInt32                  bpp;

    assert(hVd);
    assert(hInBuf);
    assert(hDstBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hDstBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hDstBuf));
    assert(Buffer_getType(hDstBuf) == Buffer_Type_GRAPHICS);

    bpp = ColorSpace_getBpp(BufferGfx_getColorSpace(hDstBuf));
 
    BufferGfx_getDimensions(hDstBuf, &dim);

    offset = (dim.y * dim.lineLength) + (dim.x * (bpp >> 3));
    assert(offset < Buffer_getSize(hDstBuf));

    inPtr  = Buffer_getUserPtr(hInBuf);
    dstPtr = Buffer_getUserPtr(hDstBuf) + offset;

    if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420PSEMI) {
        outBufPtrArray[0]       = dstPtr;
        outBufSizeArray[0]      = hVd->minOutBufSize[0];

        outBufPtrArray[1]       = dstPtr + Buffer_getSize(hDstBuf) * 2 / 3;
        outBufSizeArray[1]      = hVd->minOutBufSize[1];
    }
    else if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_YUV420P) {
        outBufPtrArray[0]       = dstPtr;
        outBufSizeArray[0]      = hVd->minOutBufSize[0];

        outBufPtrArray[1]       = dstPtr + Buffer_getSize(hDstBuf) * 2 / 3;
        outBufSizeArray[1]      = hVd->minOutBufSize[1];

        outBufPtrArray[2]       = dstPtr + Buffer_getSize(hDstBuf) * 5 / 6;  
        outBufSizeArray[2]      = hVd->minOutBufSize[2];
    }
    else if (BufferGfx_getColorSpace(hDstBuf) == ColorSpace_UYVY) {
        outBufPtrArray[0]       = dstPtr;
        outBufSizeArray[0]      = hVd->minOutBufSize[0];
    }
    else {
        Dmai_err0("Unsupported color format of destination buffer\n");
        return Dmai_EINVAL;
    }

    outBufDesc.numBufs          = hVd->minNumOutBufs;
    outBufDesc.bufSizes         = outBufSizeArray;
    outBufDesc.bufs             = outBufPtrArray;

    /* One buffer with encoded data */
    inBufDesc.numBufs           = 1;
    inBufDesc.descs[0].buf      = inPtr;
    inBufDesc.descs[0].bufSize  = Buffer_getNumBytesUsed(hInBuf);

    inArgs.size                 = sizeof(VIDDEC2_InArgs);
    inArgs.numBytes             = Buffer_getNumBytesUsed(hInBuf);
    inArgs.inputID              = GETID(Buffer_getId(hDstBuf));

    outArgs.size                = sizeof(VIDDEC2_OutArgs);

    /* Decode video buffer */
    status = VIDDEC2_process(hVd->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                             &outArgs);

    Buffer_setNumBytesUsed(hInBuf, outArgs.bytesConsumed);

    Dmai_dbg4("VIDDEC2_process() ret %d inId %d inUse %d consumed %d\n",
              status, Buffer_getId(hDstBuf), outArgs.outBufsInUseFlag,
              outArgs.bytesConsumed);

    if (status != VIDDEC2_EOK) {
        if (XDM_ISFATALERROR(outArgs.decodedBufs.extendedError)) {
            Dmai_err2("VIDDEC2_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns) outArgs.decodedBufs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("VIDDEC2_process() non-fatal error 0x%x\n",
                      (Uns) outArgs.decodedBufs.extendedError);
            ret = Dmai_EBITERROR;
        }
    }

    /* Prepare buffers for display */
    for (bufIdx = 0;
         bufIdx < IVIDDEC2_MAX_IO_BUFFERS && outArgs.outputID[bufIdx] > 0;
         bufIdx++) {

        hVd->hDisplayBufs[bufIdx] =
            BufTab_getBuf(hVd->hOutBufTab, GETIDX(outArgs.outputID[bufIdx]));

        dim.width = outArgs.displayBufs[bufIdx].frameWidth;
        dim.height = outArgs.displayBufs[bufIdx].frameHeight;
        dim.lineLength = outArgs.displayBufs[bufIdx].framePitch;

        /* Is there an offset to where we are supposed to start displaying? */
        offset = outArgs.displayBufs[bufIdx].bufDesc[0].buf -
                 Buffer_getUserPtr(hVd->hDisplayBufs[bufIdx]);

        dim.y = offset / dim.lineLength;
        dim.x = offset - ((dim.y * dim.lineLength) >> (bpp >> 4));

        Buffer_setNumBytesUsed(hVd->hDisplayBufs[bufIdx],
                               Vdec2_getOutBufSize(hVd));
        BufferGfx_setFrameType(hVd->hDisplayBufs[bufIdx],
                               outArgs.displayBufs[bufIdx].frameType);

        if (BufferGfx_setDimensions(hVd->hDisplayBufs[bufIdx], &dim) < 0) {
            Dmai_err0("Frame does not fit in allocated buffer\n");
            return Dmai_EFAIL;
        }
    }

    /* Null terminate the list of display buffers */
    if (bufIdx < IVIDDEC2_MAX_IO_BUFFERS) {
        hVd->hDisplayBufs[bufIdx] = NULL;
    }

    hVd->displayBufIdx = 0;

    /* Prepare buffers to be freed */
    for (bufIdx = 0;
         bufIdx < IVIDDEC2_MAX_IO_BUFFERS && outArgs.freeBufID[bufIdx] > 0;
         bufIdx++) {

        hVd->hFreeBufs[bufIdx] =
            BufTab_getBuf(hVd->hOutBufTab, GETIDX(outArgs.freeBufID[bufIdx]));
    }

    /* Null terminate the list of free buffers */
    if (bufIdx < IVIDDEC2_MAX_IO_BUFFERS) {
        hVd->hFreeBufs[bufIdx] = NULL;
    }

    hVd->freeBufIdx = 0;

    /* Was this just the first field of an interlaced frame? */
    if (outArgs.outBufsInUseFlag) {
        ret = Dmai_EFIRSTFIELD;
    }

    return ret;
}

/******************************************************************************
 * Vdec2_getMinOutBufs
 ******************************************************************************/
Int32 Vdec2_getMinOutBufs(Vdec2_Handle hVd)
{
    VIDDEC2_Status  decStatus;
    XDAS_Int32      status;

    assert(hVd);

    decStatus.data.buf = NULL;
    decStatus.size = sizeof(VIDDEC2_Status);

    /* Get buffer information from video decoder */

    decStatus.maxNumDisplayBufs = 0;

    status = VIDDEC2_control(hVd->hDecode, XDM_GETBUFINFO,
                             &hVd->dynParams, &decStatus);

    if (status != VIDDEC2_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        return Dmai_EFAIL;
    }

    Dmai_dbg0("Made XDM_GETBUFINFO control call\n");

    memcpy(hVd->minInBufSize,
           decStatus.bufInfo.minInBufSize, sizeof(hVd->minInBufSize));
    hVd->minNumInBufs = decStatus.bufInfo.minNumInBufs;

    memcpy(hVd->minOutBufSize,
           decStatus.bufInfo.minOutBufSize, sizeof(hVd->minOutBufSize));
    hVd->minNumOutBufs = decStatus.bufInfo.minNumOutBufs;

    hVd->maxNumDisplayBufs = decStatus.maxNumDisplayBufs;

    return decStatus.maxNumDisplayBufs;
}

/******************************************************************************
 * Vdec2_flush
 ******************************************************************************/
Int Vdec2_flush(Vdec2_Handle hVd)
{
    VIDDEC2_Status         decStatus;
    XDAS_Int32             status;

    assert(hVd);

    decStatus.data.buf = NULL;
    decStatus.size = sizeof(VIDDEC2_Status);

    /* Flush the codec */
    status = VIDDEC2_control(hVd->hDecode, XDM_FLUSH,
                             &hVd->dynParams, &decStatus);

    if (status != VIDDEC2_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Vdec2_create
 ******************************************************************************/
Vdec2_Handle Vdec2_create(Engine_Handle hEngine, Char *codecName,
                          VIDDEC2_Params *params,
                          VIDDEC2_DynamicParams *dynParams)
{
    Vdec2_Handle           hVd;
    VIDDEC2_Handle         hDecode;
    VIDDEC2_Status         decStatus;
    XDAS_Int32             status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hVd = (Vdec2_Handle)calloc(1, sizeof(Vdec2_Object));

    if (hVd == NULL) {
        Dmai_err0("Failed to allocate space for Vdec2 Object\n");
        return NULL;
    }

    /* Create video decoder instance */
    hDecode = VIDDEC2_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err0("Failed to open video decode algorithm\n");
        free(hVd);
        return NULL;
    }

    Dmai_dbg0("Video decoder instance created\n");

    /* Set video decoder dynamic params */
    decStatus.data.buf = NULL;
    decStatus.size = sizeof(VIDDEC2_Status);
    status = VIDDEC2_control(hDecode, XDM_SETPARAMS, dynParams, &decStatus);

    if (status != VIDDEC2_EOK) {
        Dmai_err0("XDM_SETPARAMS control failed\n");
        VIDDEC2_delete(hDecode);
        free(hVd);
        return NULL;
    }

    Dmai_dbg0("Made XDM_SETPARAMS control call\n");

    hVd->dynParams = *dynParams;
    hVd->hDecode = hDecode;

    Vdec2_getMinOutBufs(hVd);

    return hVd;
}

/******************************************************************************
 * Vdec2_delete
 ******************************************************************************/
Int Vdec2_delete(Vdec2_Handle hVd)
{
    if (hVd) {
        if (hVd->hDecode) {
            VIDDEC2_delete(hVd->hDecode);
        }

        free(hVd);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Vdec2_setBufTab
 ******************************************************************************/
Void Vdec2_setBufTab(Vdec2_Handle hVd, BufTab_Handle hBufTab)
{
    assert(hVd);

    hVd->hOutBufTab = hBufTab;
}

/******************************************************************************
 * Vdec2_getBufTab
 ******************************************************************************/
BufTab_Handle Vdec2_getBufTab(Vdec2_Handle hVd)
{
    assert(hVd);

    return hVd->hOutBufTab;
}

/******************************************************************************
 * Vdec2_getOutBufSize
 ******************************************************************************/
Int32 Vdec2_getOutBufSize(Vdec2_Handle hVd)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hVd);

    for (bufIdx = 0; bufIdx < hVd->minNumOutBufs; bufIdx++) {
        size += hVd->minOutBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Vdec2_getInBufSize
 ******************************************************************************/
Int32 Vdec2_getInBufSize(Vdec2_Handle hVd)
{
    assert(hVd);

    return hVd->minInBufSize[0];
}

/******************************************************************************
 * Vdec2_getDisplayBuf
 ******************************************************************************/
Buffer_Handle Vdec2_getDisplayBuf(Vdec2_Handle hVd)
{
    assert(hVd);

    if (hVd->displayBufIdx < IVIDDEC2_MAX_IO_BUFFERS &&
        hVd->hDisplayBufs[hVd->displayBufIdx]) {

        return hVd->hDisplayBufs[hVd->displayBufIdx++];
    }
    else {
        return NULL;
    }
}

/******************************************************************************
 * Vdec2_getFreeBuf
 ******************************************************************************/
Buffer_Handle Vdec2_getFreeBuf(Vdec2_Handle hVd)
{
    assert(hVd);

    if (hVd->freeBufIdx < IVIDDEC2_MAX_IO_BUFFERS &&
        hVd->hFreeBufs[hVd->freeBufIdx]) {

        return hVd->hFreeBufs[hVd->freeBufIdx++];
    }
    else {
        return NULL;
    }
}

/******************************************************************************
 * Vdec2_getVisaHandle
 ******************************************************************************/
VIDDEC2_Handle Vdec2_getVisaHandle(Vdec2_Handle hVd)
{
    assert(hVd);

    return hVd->hDecode;
}
