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
#include <ti/sdo/ce/video/videnc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Venc.h>

#define MODULE_NAME     "Venc"

typedef struct Venc_Object {
    VIDENC_Handle          hEncode;
    Int32                  minNumInBufs;
    Int32                  minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                  minNumOutBufs;
    Int32                  minOutBufSize[XDM_MAX_IO_BUFFERS];
} Venc_Object;

const VIDENC_Params Venc_Params_DEFAULT = {
    sizeof(VIDENC_Params),
    XDM_DEFAULT,
    IVIDEO_NONE,
    576,
    720,
    30000,
    0,
    XDM_BYTE,
    0,
    XDM_YUV_422ILE,
    IVIDEO_PROGRESSIVE
};

const VIDENC_DynamicParams Venc_DynamicParams_DEFAULT = {
    sizeof(VIDENC_DynamicParams),
    576,
    720,
    30000,
    30000,
    0,
    30,
    XDM_ENCODE_AU,
    0,
    0
};

/******************************************************************************
 * Venc_process
 ******************************************************************************/
Int Venc_process(Venc_Handle hVe, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[1];
    XDAS_Int32              status;
    VIDENC_InArgs           inArgs;
    VIDENC_OutArgs          outArgs;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;
    BufferGfx_Dimensions    dim;
    UInt32                  offset = 0;
    Uint32                  bpp;

    assert(hVe);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getSize(hInBuf));
    assert(Buffer_getSize(hOutBuf));
    assert(Buffer_getType(hInBuf) == Buffer_Type_GRAPHICS);

    bpp = ColorSpace_getBpp(BufferGfx_getColorSpace(hInBuf));

    BufferGfx_getDimensions(hInBuf, &dim);
    offset = (dim.y * dim.lineLength) + (dim.x * (bpp >> 3));
    assert(offset < Buffer_getSize(hInBuf));

    inPtr                   = Buffer_getUserPtr(hInBuf) + offset;
    outPtr                  = Buffer_getUserPtr(hOutBuf);

    inBufSizeArray[0]       = Buffer_getSize(hInBuf);
    outBufSizeArray[0]      = Buffer_getSize(hOutBuf);

    inBufDesc.numBufs       = 1;
    inBufDesc.bufs          = &inPtr;
    inBufDesc.bufSizes      = inBufSizeArray;

    outBufDesc.numBufs      = 1;
    outBufDesc.bufs         = &outPtr;
    outBufDesc.bufSizes     = outBufSizeArray;

    inArgs.size             = sizeof(VIDENC_InArgs);
    outArgs.size            = sizeof(VIDENC_OutArgs);

    /* Encode video buffer */
    status = VIDENC_process(hVe->hEncode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    if (status != VIDENC_EOK) {
        Dmai_err2("VIDENC_process() failed with error (%d ext: 0x%x)\n",
                  (Int)status, (Uns) outArgs.extendedError);
        return Dmai_EFAIL;
    }

    /*
     * Setting the frame type in the input buffer even through it's a property
     * of the output buffer. This works for encoders without B-frames, but
     * when byte and display order are not the same the frame type will get
     * out of sync.
     */
    BufferGfx_setFrameType(hInBuf, outArgs.encodedFrameType);

    Buffer_setNumBytesUsed(hOutBuf, outArgs.bytesGenerated);

    return Dmai_EOK;
}

/******************************************************************************
 * Venc_create
 ******************************************************************************/
Venc_Handle Venc_create(Engine_Handle hEngine, Char *codecName,
                        VIDENC_Params *params, VIDENC_DynamicParams *dynParams)
{
    Venc_Handle             hVe;
    VIDENC_Status           encStatus;
    XDAS_Int32              status;
    VIDENC_Handle           hEncode;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    hVe = (Venc_Handle)calloc(1, sizeof(Venc_Object));

    if (hVe == NULL) {
        Dmai_err0("Failed to allocate space for Venc Object\n");
        return NULL;
    }

    /* Create video encoder instance */
    hEncode = VIDENC_create(hEngine, codecName, params);

    if (hEncode == NULL) {
        Dmai_err0("Failed to open video encode algorithm\n");
        return NULL;
    }

    /* Set video encoder dynamic parameters */
    encStatus.size = sizeof(VIDENC_Status);
    status = VIDENC_control(hEncode, XDM_SETPARAMS, dynParams, &encStatus);

    if (status != VIDENC_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        VIDENC_delete(hEncode);
        free(hVe);
        return NULL;
    }

    /* Get buffer information from video encoder */
    status = VIDENC_control(hEncode, XDM_GETBUFINFO, dynParams, &encStatus);

    if (status != VIDENC_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        VIDENC_delete(hEncode);
        free(hVe);
        return NULL;
    }

    memcpy(hVe->minInBufSize,
           encStatus.bufInfo.minInBufSize, sizeof(hVe->minInBufSize));
    hVe->minNumInBufs = encStatus.bufInfo.minNumInBufs;

    memcpy(hVe->minOutBufSize,
           encStatus.bufInfo.minOutBufSize, sizeof(hVe->minOutBufSize));
    hVe->minNumOutBufs = encStatus.bufInfo.minNumOutBufs;

    hVe->hEncode = hEncode;
        
    return hVe;
}

/******************************************************************************
 * Venc_delete
 ******************************************************************************/
Int Venc_delete(Venc_Handle hVe)
{
    if (hVe) {
        if (hVe->hEncode) {
            VIDENC_delete(hVe->hEncode);
        }

        free(hVe);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Venc_getInBufSize
 ******************************************************************************/
Int32 Venc_getInBufSize(Venc_Handle hVe)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hVe);

    for (bufIdx = 0; bufIdx < hVe->minNumInBufs; bufIdx++) {
        size += hVe->minInBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Venc_getOutBufSize
 ******************************************************************************/
Int32 Venc_getOutBufSize(Venc_Handle hVe)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hVe);

    for (bufIdx = 0; bufIdx < hVe->minNumOutBufs; bufIdx++) {
        size += hVe->minOutBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Venc_getVisaHandle
 ******************************************************************************/
VIDENC_Handle Venc_getVisaHandle(Venc_Handle hVe)
{
    assert(hVe);

    return hVe->hEncode;
}
