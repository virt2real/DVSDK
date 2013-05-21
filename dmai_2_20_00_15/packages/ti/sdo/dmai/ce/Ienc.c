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
#include <ti/sdo/ce/image/imgenc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ce/Ienc.h>

#define MODULE_NAME     "Ienc"

typedef struct Ienc_Object {
    IMGENC_Handle          hEncode;
    IMGENC_DynamicParams   *dynParams;
    Int32                  totalAU;
    Int32                  minNumInBufs;
    Int32                  minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                  minNumOutBufs;
    Int32                  minOutBufSize[XDM_MAX_IO_BUFFERS];
} Ienc_Object;

const IMGENC_Params Ienc_Params_DEFAULT = {
    sizeof(IMGENC_Params),               /* size */
    0,                                   /* maxHeight */
    0,                                   /* maxWidth */
    XDM_DEFAULT,                         /* maxScans */
    XDM_LE_32,                           /* dataEndianness */
    XDM_YUV_422P                         /* forceChromaFormat */
};

const IMGENC_DynamicParams Ienc_DynamicParams_DEFAULT = {
    sizeof(IMGENC_DynamicParams),        /* size */
    XDM_DEFAULT,                         /* numAU */
    XDM_YUV_422P,                        /* inputChromaFormat */
    0,                                   /* inputHeight */
    0,                                   /* inputWidth */
    0,                                   /* captureWidth */
    XDM_ENCODE_AU,                       /* generateHeader */
    75                                   /* qValue */
};

/******************************************************************************
 * Ienc_process
 ******************************************************************************/
Int Ienc_process(Ienc_Handle hIe, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    BufferGfx_Dimensions    dim;
    IMGENC_InArgs           inArgs;
    IMGENC_OutArgs          outArgs;
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              inBufSizeArray[XDM_MAX_IO_BUFFERS];
    XDAS_Int8              *inBufPtrArray[XDM_MAX_IO_BUFFERS];
    XDAS_Int32              outBufSizeArray[1];
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

    inPtr   = Buffer_getUserPtr(hInBuf) + offset;
    outPtr  = Buffer_getUserPtr(hOutBuf);

    inBufDesc.numBufs       = hIe->minNumInBufs;
    inBufDesc.bufs          = inBufPtrArray;
    inBufDesc.bufSizes      = inBufSizeArray;

    offset = 0;
    for(i = 0; i < hIe->minNumInBufs; i++)
    {
        inBufDesc.bufs[i] = (XDAS_Int8 *)((XDAS_Int32)inPtr + offset);
        offset +=  hIe->minInBufSize[i];
        inBufDesc.bufSizes[i] = hIe->minInBufSize[i];
    }
    
    outBufDesc.numBufs      = 1;
    outBufDesc.bufs         = &outPtr;
    outBufDesc.bufSizes     = outBufSizeArray;

    outBufSizeArray[0]      = Buffer_getSize(hOutBuf);

    inArgs.size             = sizeof(IMGENC_InArgs);
    outArgs.size            = sizeof(IMGENC_OutArgs);

    /* Encode video buffer */
    status = IMGENC_process(hIe->hEncode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    if (status != IMGENC_EOK) {
        Dmai_err2("IMGENC_process() failed with error (%d ext: 0x%x)\n",
                  (Int)status, (Uns) outArgs.extendedError);
        return Dmai_EFAIL;
    }

    Dmai_dbg2("Current AU=%d, Total=%d\n", outArgs.currentAU, 
              hIe->totalAU);

    Buffer_setNumBytesUsed(hOutBuf, outArgs.bytesGenerated);
    
    if (outArgs.currentAU >= hIe->totalAU) {
        /* The complete image is done */
        return Dmai_EOK;
    }
    else {
        /* The image is partially encoded. Need to repeat process call. */
        return Dmai_EAGAIN;
    }       
}

/******************************************************************************
 * Ienc_create
 ******************************************************************************/
Ienc_Handle Ienc_create(Engine_Handle hEngine,
                        Char *codecName,
                        IMGENC_Params *params,
                        IMGENC_DynamicParams *dynParams)
{
    Ienc_Handle         hIe;
    IMGENC_Handle       hEncode;
    IMGENC_Status       encStatus;
    XDAS_Int32          status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hIe = (Ienc_Handle)calloc(1, sizeof(Ienc_Object));

    if (hIe == NULL) {
        Dmai_err0("Failed to allocate space for Ienc Object\n");
        return NULL;
    }

    /* Create image encoder */
    hEncode = IMGENC_create(hEngine, codecName, params);

    if (hEncode == NULL) {
        Dmai_err0("Can't open image encode algorithm\n");
        free(hIe);
        return NULL;
    }

    /* Set dynamic parameters */
    encStatus.size = sizeof(IMGENC_Status);
    status = IMGENC_control(hEncode, XDM_SETPARAMS, dynParams, &encStatus);

    if (status != IMGENC_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        IMGENC_delete(hEncode);
        free(hIe);
        return NULL;
    }

    /* Get buffer requirements */
    status = IMGENC_control(hEncode, XDM_GETBUFINFO, dynParams, &encStatus);

    if (status != IMGENC_EOK) {
        Dmai_err1("XDM_GETBUFINFO failed, status=%d\n", status);
        IMGENC_delete(hEncode);
        free(hIe);
        return NULL;
    }
    
    Dmai_dbg1("Buffer size %u obtained from XDM_GETBUFINFO control call\n",
              (UInt) encStatus.bufInfo.minInBufSize[0]);

    /* Save some info into encoder object */
    hIe->dynParams = (IMGENC_DynamicParams *)calloc(1, dynParams->size);
    if (hIe->dynParams == NULL) {
        Dmai_err0("Failed to allocate space to record dynamic params\n");
        IMGENC_delete(hEncode);
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
    
    /* Get encoder status */
    status = IMGENC_control(hEncode, XDM_GETSTATUS, dynParams, &encStatus);

    if (status != IMGENC_EOK) {
        Dmai_err1("XDM_GETSTATUS failed, status=%d\n", status);
        IMGENC_delete(hEncode);
        free(hIe);
        return NULL;
    }
    
    hIe->totalAU = encStatus.totalAU;
    
    return hIe;
}

/******************************************************************************
 * Ienc_delete
 ******************************************************************************/
Int Ienc_delete(Ienc_Handle hIe)
{
    if (hIe) {
        if (hIe->hEncode) {
            IMGENC_delete(hIe->hEncode);
        }
        if (hIe->dynParams) {
            free(hIe->dynParams);
        }
        free(hIe);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Ienc_getVisaHandle
 ******************************************************************************/
IMGENC_Handle Ienc_getVisaHandle(Ienc_Handle hIe)
{
    assert(hIe);

    return hIe->hEncode;
}

/******************************************************************************
 * Ienc_getInBufSize
 ******************************************************************************/
Int32 Ienc_getInBufSize(Ienc_Handle hIe)
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
 * Ienc_getOutBufSize
 ******************************************************************************/
Int32 Ienc_getOutBufSize(Ienc_Handle hIe)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hIe);

    for (bufIdx = 0; bufIdx < hIe->minNumOutBufs; bufIdx++) {
        size += hIe->minOutBufSize[bufIdx];
    }

    return size;
}
