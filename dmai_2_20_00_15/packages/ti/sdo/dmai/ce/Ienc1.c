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
#include <ti/sdo/ce/image1/imgenc1.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ce/Ienc1.h>

#define MODULE_NAME     "Ienc1"

typedef struct Ienc1_Object {
    IMGENC1_Handle          hEncode;
    IMGENC1_DynamicParams   *dynParams;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Ienc1_Object;

const IMGENC1_Params Ienc1_Params_DEFAULT = {
    sizeof(IMGENC1_Params),
    0,
    0,
    XDM_DEFAULT,
    XDM_BYTE,
    XDM_YUV_422P   
};

const IMGENC1_DynamicParams Ienc1_DynamicParams_DEFAULT = {
    sizeof(IMGENC1_DynamicParams),
    XDM_DEFAULT,
    XDM_YUV_422ILE,
    0,
    0,
    0,
    XDM_ENCODE_AU,
    75
};

/******************************************************************************
 * Ienc1_process
 ******************************************************************************/
Int Ienc1_process(Ienc1_Handle hIe, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    BufferGfx_Dimensions    dim;
    IMGENC1_InArgs          inArgs;
    IMGENC1_OutArgs         outArgs;
    XDM1_BufDesc            inBufDesc;
    XDM1_BufDesc            outBufDesc;
    XDAS_Int32              status;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;
    UInt32                  offset = 0;
    UInt32                  bpp;
    UInt32                  i;  
    
    assert(hIe);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hInBuf));
    assert(Buffer_getSize(hOutBuf));
    assert(Buffer_getType(hInBuf) == Buffer_Type_GRAPHICS);
 
    bpp = ColorSpace_getBpp(BufferGfx_getColorSpace(hInBuf));

    BufferGfx_getDimensions(hInBuf, &dim);
    offset = (dim.y * dim.lineLength) + (dim.x * (bpp >> 3));
    assert(offset < Buffer_getSize(hInBuf));

    inPtr  = Buffer_getUserPtr(hInBuf) + offset;
    outPtr = Buffer_getUserPtr(hOutBuf);

    offset = 0;
    for(i = 0; i < hIe->minNumInBufs; i++)
    {
        inBufDesc.descs[i].buf = (XDAS_Int8 *)((unsigned int)inPtr + offset);
        offset +=  hIe->minInBufSize[i];
        inBufDesc.descs[i].bufSize = hIe->minInBufSize[i];
    }
    inBufDesc.numBufs = hIe->minNumInBufs;

    outBufDesc.numBufs               = 1;
    outBufDesc.descs[0].buf          = outPtr;
    outBufDesc.descs[0].bufSize      = Buffer_getSize(hOutBuf);

    inArgs.size             = sizeof(IMGENC1_InArgs);
    outArgs.size            = sizeof(IMGENC1_OutArgs);

    /* Encode video buffer */
    status = IMGENC1_process(hIe->hEncode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    if (status != IMGENC1_EOK) {
        Dmai_err2("IMGENC1_process() failed with error (%d ext: 0x%x)\n",
                  (Int)status, (Uns) outArgs.extendedError);
        return Dmai_EFAIL;
    }

    Buffer_setNumBytesUsed(hOutBuf, outArgs.bytesGenerated);

    return Dmai_EOK;
}

/******************************************************************************
 * Ienc1_create
 ******************************************************************************/
Ienc1_Handle Ienc1_create(Engine_Handle hEngine,
                        Char *codecName,
                        IMGENC1_Params *params,
                        IMGENC1_DynamicParams *dynParams)
{
    Ienc1_Handle         hIe;
    IMGENC1_Handle       hEncode;
    IMGENC1_Status       encStatus;
    XDAS_Int32           status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hIe = (Ienc1_Handle)calloc(1, sizeof(Ienc1_Object));

    if (hIe == NULL) {
        Dmai_err0("Failed to allocate space for Ienc1 Object\n");
        return NULL;
    }

    /* Create imaging encoder */
    hEncode = IMGENC1_create(hEngine, codecName, params);

    if (hEncode == NULL) {
        Dmai_err0("Can't open imaging encode algorithm\n");
        free(hIe);
        return NULL;
    }

    /* Set dynamic parameters */
    encStatus.data.buf = NULL;
    encStatus.size = sizeof(IMGENC1_Status);
    status = IMGENC1_control(hEncode, XDM_SETPARAMS, dynParams, &encStatus);

    if (status != IMGENC1_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        IMGENC1_delete(hEncode);
        free(hIe);
        return NULL;
    }

    /* Get buffer requirements */
    status = IMGENC1_control(hEncode, XDM_GETBUFINFO, dynParams, &encStatus);

    if (status != IMGENC1_EOK) {
        Dmai_err1("XDM_GETBUFINFO failed, status=%d\n", status);
        IMGENC1_delete(hEncode);
        free(hIe);
        return NULL;
    }

    Dmai_dbg1("Buffer size %u obtained from XDM_GETBUFINFO control call\n",
              (UInt) encStatus.bufInfo.minInBufSize[0]);

    hIe->dynParams = (IMGENC1_DynamicParams *)calloc(1, dynParams->size);
    if (hIe->dynParams == NULL) {
        Dmai_err0("Failed to allocate space to record dynamic params\n");
        IMGENC1_delete(hEncode);
        free(hIe);
        return NULL;
    }
    memcpy(hIe->dynParams, dynParams, dynParams->size);
    
    hIe->hEncode = hEncode;
    memcpy(hIe->minInBufSize,
           encStatus.bufInfo.minInBufSize, sizeof(hIe->minInBufSize));
    hIe->minNumInBufs = encStatus.bufInfo.minNumInBufs;
    memcpy(hIe->minOutBufSize,
           encStatus.bufInfo.minOutBufSize, sizeof(hIe->minOutBufSize));
    hIe->minNumOutBufs = encStatus.bufInfo.minNumOutBufs;

    hIe->hEncode = hEncode;

    return hIe;
}

/******************************************************************************
 * Ienc1_delete
 ******************************************************************************/
Int Ienc1_delete(Ienc1_Handle hIe)
{
    if (hIe) {
        if (hIe->hEncode) {
            IMGENC1_delete(hIe->hEncode);
        }
        if (hIe->dynParams) {
            free(hIe->dynParams);
        }
        free(hIe);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Ienc1_getVisaHandle
 ******************************************************************************/
IMGENC1_Handle Ienc1_getVisaHandle(Ienc1_Handle hIe)
{
    assert(hIe);

    return hIe->hEncode;
}

/******************************************************************************
 * Ienc1_getInBufSize
 ******************************************************************************/
Int32 Ienc1_getInBufSize(Ienc1_Handle hIe)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hIe);

    for (bufIdx = 0; bufIdx < hIe->minNumInBufs; bufIdx++) {
        size += hIe->minInBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Ienc1_getOutBufSize
 ******************************************************************************/
Int32 Ienc1_getOutBufSize(Ienc1_Handle hIe)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hIe);

    for (bufIdx = 0; bufIdx < hIe->minNumOutBufs; bufIdx++) {
        size += hIe->minOutBufSize[bufIdx];
    }

    return size;
}
