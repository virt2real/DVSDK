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
#include <string.h>

#include <xdc/std.h>

#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/video/viddec.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Vdec.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

#include "../priv/_Buffer.h"

#define MODULE_NAME     "Vdec"

typedef struct Vdec_Object {
    VIDDEC_Handle           hDecode;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
    BufTab_Handle           hOutBufTab;
    VIDDEC_DynamicParams    dynParams;
    Buffer_Handle           hOutBuf;
} Vdec_Object;

const VIDDEC_Params Vdec_Params_DEFAULT = {
    sizeof(VIDDEC_Params),          /* size */
    576,                            /* maxHeight */
    720,                            /* maxWidth */
    0,                              /* maxFrameRate */
    0,                              /* maxBitRate */
    XDM_BYTE,                       /* dataEndianess */
    XDM_YUV_422ILE,                 /* forceChromaFormat */
};

const VIDDEC_DynamicParams Vdec_DynamicParams_DEFAULT = {
    sizeof(VIDDEC_DynamicParams),   /* size */
    XDM_DECODE_AU,                  /* decodeHeader */
    XDM_DEFAULT,                    /* displayWidth */
    IVIDEO_NO_SKIP,                 /* frameSkipMode */
};

/******************************************************************************
 * Vdec_process
 ******************************************************************************/
Int Vdec_process(Vdec_Handle hVd, Buffer_Handle hInBuf,
                 Buffer_Handle hDstBuf)
{
    BufferGfx_Dimensions    dim;
    VIDDEC_DynamicParams    dynParams;
    VIDDEC_InArgs           inArgs;
    VIDDEC_OutArgs          outArgs;
    VIDDEC_Status           decStatus;
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[1];
    XDAS_Int32              status;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *dstPtr;
    UInt32                  offset = 0;
    Uint32                  bpp;
    Int                     ret = Dmai_EOK;

    assert(hVd);
    assert(hInBuf);
    assert(hDstBuf);
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

    dynParams.size          = sizeof(VIDDEC_DynamicParams);
    decStatus.size          = sizeof(VIDDEC_Status);

    inBufSizeArray[0]       = Buffer_getNumBytesUsed(hInBuf);
    outBufSizeArray[0]      = Buffer_getSize(hDstBuf);

    inBufDesc.bufSizes      = inBufSizeArray;
    inBufDesc.bufs          = &inPtr;
    inBufDesc.numBufs       = 1;

    outBufDesc.bufSizes     = outBufSizeArray;
    outBufDesc.bufs         = &dstPtr;
    outBufDesc.numBufs      = 1;

    inArgs.size             = sizeof(VIDDEC_InArgs);
    inArgs.numBytes         = Buffer_getNumBytesUsed(hInBuf);
    inArgs.inputID          = Buffer_getId(hDstBuf);

    outArgs.size            = sizeof(VIDDEC_OutArgs);

    hVd->hOutBuf            = NULL;

    /* Decode video buffer */
    status = VIDDEC_process(hVd->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    Buffer_setNumBytesUsed(hInBuf, outArgs.bytesConsumed);

    Dmai_dbg4("VIDDEC_process() ret %d inId %d outID %d consumed %d\n",
              status, Buffer_getId(hDstBuf), outArgs.outputID,
              outArgs.bytesConsumed);

    if (status != VIDDEC_EOK) {
        if (status == VIDDEC_ERUNTIME ||
            outArgs.bytesConsumed == 0 ||
            XDM_ISFATALERROR(outArgs.extendedError)) {

            Dmai_err2("VIDDEC_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns) outArgs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("VIDDEC_process() non-fatal error 0x%x\n",
                      (Uns) outArgs.extendedError);
            _BufferGfx_setFrameDone(hDstBuf, 1);
            ret = Dmai_EBITERROR;
        }
    }

    BufferGfx_setFrameType(hDstBuf, outArgs.decodedFrameType);

    /* Get status to find out the frame resolution and if it is interlaced */
    status = VIDDEC_control(hVd->hDecode, XDM_GETSTATUS, &dynParams,
                            &decStatus);

    if (status != VIDDEC_EOK) {
        Dmai_err0("XDM_GETSTATUS control failed\n");
        return Dmai_EFAIL;
    }

    if (decStatus.contentType == IVIDEO_INTERLACED) {
        _BufferGfx_toggleFrameDone(hDstBuf);
    }

    /* Did the decoder keep the frame? */
    if (outArgs.displayBufs.bufs[0] == NULL) {
        if (_BufferGfx_getFrameDone(hDstBuf)) {
            return Dmai_EPRIME;
        }
        else {
            return Dmai_EFIRSTFIELD;
        }
    }

    /* Due to buffer reordering we might not receive the same buffer back */
    hVd->hOutBuf = BufTab_getBuf(hVd->hOutBufTab, outArgs.outputID);

    dim.x = dim.y = 0;
    dim.width = decStatus.outputWidth;
    dim.height = decStatus.outputHeight;
    dim.lineLength = decStatus.outputWidth *
        ColorSpace_getBpp(BufferGfx_getColorSpace(hVd->hOutBuf)) / 8;

    if (BufferGfx_setDimensions(hVd->hOutBuf, &dim) < 0) {
        Dmai_err0("Frame does not fit in allocated buffer\n");
        return Dmai_EFAIL;
    }

    return ret;
}

/******************************************************************************
 * Vdec_create
 ******************************************************************************/
Vdec_Handle Vdec_create(Engine_Handle hEngine, Char *codecName,
                        VIDDEC_Params *params, VIDDEC_DynamicParams *dynParams)
{
    Vdec_Handle             hVd;
    VIDDEC_Handle           hDecode;
    VIDDEC_Status           decStatus;
    XDAS_Int32              status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hVd = (Vdec_Handle)calloc(1, sizeof(Vdec_Object));

    if (hVd == NULL) {
        Dmai_err0("Failed to allocate space for Vdec Object\n");
        return NULL;
    }

    /* Create video decoder instance */
    hDecode = VIDDEC_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err0("Failed to open video decode algorithm\n");
        free(hVd);
        return NULL;
    }

    Dmai_dbg0("Video decoder instance created\n");

    /* Set video decoder dynamic params */
    decStatus.size = sizeof(VIDDEC_Status);
    status = VIDDEC_control(hDecode, XDM_SETPARAMS, dynParams,
                            &decStatus);

    if (status != VIDDEC_EOK) {
        Dmai_err0("XDM_SETPARAMS control failed\n");
        VIDDEC_delete(hDecode);
        free(hVd);
        return NULL;
    }

    memcpy(&hVd->dynParams, dynParams, sizeof(VIDDEC_DynamicParams));
    Dmai_dbg0("Made XDM_SETPARAMS control call\n");

    /* Get buffer information from video decoder */
    status = VIDDEC_control(hDecode, XDM_GETBUFINFO, dynParams,
                            &decStatus);

    if (status != VIDDEC_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        VIDDEC_delete(hDecode);
        free(hVd);
        return NULL;
    }

    Dmai_dbg1("Buffer size %u obtained from XDM_GETBUFINFO control call\n",
              (UInt) decStatus.bufInfo.minInBufSize[0]);

    hVd->hDecode      = hDecode;
    hVd->hOutBuf      = NULL;
    memcpy(hVd->minInBufSize,
           decStatus.bufInfo.minInBufSize, sizeof(hVd->minInBufSize));
    hVd->minNumInBufs = decStatus.bufInfo.minNumInBufs;
    memcpy(hVd->minOutBufSize,
           decStatus.bufInfo.minOutBufSize, sizeof(hVd->minOutBufSize));
    hVd->minNumOutBufs = decStatus.bufInfo.minNumOutBufs;

    return hVd;
}

/******************************************************************************
 * Vdec_delete
 ******************************************************************************/
Int Vdec_delete(Vdec_Handle hVd)
{
    if (hVd) {
        if (hVd->hDecode) {
            VIDDEC_delete(hVd->hDecode);
        }

        free(hVd);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Vdec_flush
 ******************************************************************************/
Int Vdec_flush(Vdec_Handle hVd)
{
    VIDDEC_Status         decStatus;
    XDAS_Int32             status;

    assert(hVd);

    decStatus.size = sizeof(VIDDEC_Status);

    /* Flush the codec */
    status = VIDDEC_control(hVd->hDecode, XDM_FLUSH,
                             &hVd->dynParams, &decStatus);

    if (status != VIDDEC_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Vdec_setBufTab
 ******************************************************************************/
Void Vdec_setBufTab(Vdec_Handle hVd, BufTab_Handle hBufTab)
{
    assert(hVd);

    hVd->hOutBufTab = hBufTab;
}

/******************************************************************************
 * Vdec_getBufTab
 ******************************************************************************/
BufTab_Handle Vdec_getBufTab(Vdec_Handle hVd)
{
    assert(hVd);

    return hVd->hOutBufTab;
}

/******************************************************************************
 * Vdec_getInBufSize
 ******************************************************************************/
Int32 Vdec_getInBufSize(Vdec_Handle hVd)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hVd);

    for (bufIdx = 0; bufIdx < hVd->minNumInBufs; bufIdx++) {
        size += hVd->minInBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Vdec_getOutBufSize
 ******************************************************************************/
Int32 Vdec_getOutBufSize(Vdec_Handle hVd)
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
 * Vdec_getDisplayBuf
 ******************************************************************************/
Buffer_Handle Vdec_getDisplayBuf(Vdec_Handle hVd)
{
    Buffer_Handle hOutBuf;

    assert(hVd);

    hOutBuf = hVd->hOutBuf;
    hVd->hOutBuf = NULL;

    return hOutBuf;
}

/******************************************************************************
 * Vdec_getVisaHandle
 ******************************************************************************/
VIDDEC_Handle Vdec_getVisaHandle(Vdec_Handle hVd)
{
    assert(hVd);

    return hVd->hDecode;
}
