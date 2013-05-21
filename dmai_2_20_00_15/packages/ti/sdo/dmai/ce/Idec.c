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
#include <ti/sdo/ce/image/imgdec.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Idec.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Idec"

typedef struct Idec_Object {
    IMGDEC_Handle           hDecode;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Idec_Object;

const IMGDEC_Params Idec_Params_DEFAULT = {
    sizeof(IMGDEC_Params),          /* size */
    576,                            /* maxHeight */
    720,                            /* maxWidth */
    15,                             /* maxScans */
    XDM_BYTE,                       /* dataEndianess */
    XDM_YUV_422ILE,                 /* forceChromaFormat */
};

const IMGDEC_DynamicParams Idec_DynamicParams_DEFAULT = {
    sizeof(IMGDEC_DynamicParams),   /* size */
    XDM_DEFAULT,                    /* numAu */    
    XDM_DECODE_AU,                  /* decodeHeader */
    0,                              /* displayWidth */
};

/******************************************************************************
 * Idec_process
 ******************************************************************************/
Int Idec_process(Idec_Handle hId, Buffer_Handle hInBuf,
                 Buffer_Handle hOutBuf)
{
    BufferGfx_Dimensions    dim;
    IMGDEC_DynamicParams    dynParams;
    IMGDEC_InArgs           inArgs;
    IMGDEC_OutArgs          outArgs;
    IMGDEC_Status           decStatus;
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[XDM_MAX_IO_BUFFERS];
    XDAS_Int8              *outBufPtrArray[XDM_MAX_IO_BUFFERS];
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              status;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;
    UInt32                  offset = 0;
    UInt32                  i;

    assert(hId);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getSize(hInBuf));   
    assert(Buffer_getUserPtr(hInBuf)); 
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hOutBuf));
    assert(Buffer_getType(hOutBuf) == Buffer_Type_GRAPHICS);

    BufferGfx_getDimensions(hOutBuf, &dim);
    
    inPtr                   = Buffer_getUserPtr(hInBuf);
    outPtr                  = Buffer_getUserPtr(hOutBuf);

    inArgs.size             = sizeof(IMGDEC_InArgs);
    inArgs.numBytes         = Buffer_getNumBytesUsed(hInBuf);

    outArgs.size            = sizeof(IMGDEC_OutArgs);

    inBufSizeArray[0]       = Buffer_getSize(hInBuf);

    inBufDesc.numBufs       = 1;
    inBufDesc.bufSizes      = inBufSizeArray;
    inBufDesc.bufs          = &inPtr;    

    outBufDesc.numBufs      = hId->minNumOutBufs;
    outBufDesc.bufs         = outBufPtrArray;
    outBufDesc.bufSizes     = outBufSizeArray;
    
    for(i = 0; i < hId->minNumOutBufs; i++)
    {
        outBufDesc.bufs[i] = (XDAS_Int8 *)((XDAS_Int32)outPtr + offset);
        offset +=  hId->minOutBufSize[i];
        outBufDesc.bufSizes[i] = hId->minOutBufSize[i];
    }

    /* Decode image buffer */
    status = IMGDEC_process(hId->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    Buffer_setNumBytesUsed(hInBuf, outArgs.bytesconsumed);

    if (status != IMGDEC_EOK) {
        if (XDM_ISFATALERROR(outArgs.extendedError)) {
            Dmai_err2("IMGDEC_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns) outArgs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("IMGDEC_process() non-fatal error 0x%x\n",
                      (Uns) outArgs.extendedError);
            return Dmai_EBITERROR;
        }
    }

    /* Get the dynamic codec status */
    decStatus.size = sizeof(IMGDEC_Status);
    dynParams.size = sizeof(IMGDEC_DynamicParams);
    status = IMGDEC_control(hId->hDecode, XDM_GETSTATUS, &dynParams,
                            &decStatus);

    if (status != IMGDEC_EOK) {
        Dmai_err1("XDM_GETSTATUS failed, status=%d\n", status);
        return Dmai_EFAIL;
    }
    
    /* Set output Color Format */
    
    switch (decStatus.outChromaformat) {
        case XDM_YUV_422ILE:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_UYVY); 
            break;
        case XDM_YUV_420P:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_YUV420P); 
            break;
        case XDM_YUV_422P:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_YUV422P); 
            break;
        case XDM_YUV_444P:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_YUV444P); 
            break;
        case XDM_GRAY:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_GRAY); 
            break;
        default:
            printf("Unsupported output color space.\n");
            return Dmai_EFAIL;        
    }
    
    dim.x = dim.y = 0;
    dim.width = decStatus.outputWidth;
    dim.height = decStatus.outputHeight;
    dim.lineLength = decStatus.outputWidth *
                      ColorSpace_getBpp(BufferGfx_getColorSpace(hOutBuf)) / 8;

    
    if (BufferGfx_setDimensions(hOutBuf, &dim) < 0) {
        Dmai_err0("Frame does not fit in allocated buffer\n");
        return Dmai_EFAIL;
    }
    
    return Dmai_EOK;
}

/******************************************************************************
 * Idec_create
 ******************************************************************************/
Idec_Handle Idec_create(Engine_Handle hEngine, Char *codecName,
                        IMGDEC_Params *params, IMGDEC_DynamicParams *dynParams)
{
    Idec_Handle             hId;
    IMGDEC_Handle           hDecode;
    IMGDEC_Status           decStatus;
    XDAS_Int32              status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hId = (Idec_Handle)calloc(1, sizeof(Idec_Object));

    if (hId == NULL) {
        Dmai_err0("Failed to allocate space for Idec Object\n");
        return NULL;
    }

    /* Create image decoder instance */
    hDecode = IMGDEC_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err0("Failed to open image decode algorithm\n");
        free(hId);
        return NULL;
    }

    Dmai_dbg0("Image decoder instance created\n");

    /* Set image decoder dynamic params */
    decStatus.size = sizeof(IMGDEC_Status);
    status = IMGDEC_control(hDecode, XDM_SETPARAMS, dynParams,
                            &decStatus);

    if (status != IMGDEC_EOK) {
        Dmai_err0("XDM_SETPARAMS control failed\n");
        IMGDEC_delete(hDecode);
        free(hId);
        return NULL;
    }

    /* Get buffer information from image decoder */
    status = IMGDEC_control(hDecode, XDM_GETBUFINFO, dynParams,
                            &decStatus);

    if (status != IMGDEC_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        IMGDEC_delete(hDecode);
        free(hId);
        return NULL;
    }

    Dmai_dbg1("Buffer size %u obtained from XDM_GETBUFINFO control call\n",
              (UInt) decStatus.bufInfo.minInBufSize[0]);

    hId->hDecode = hDecode;
    memcpy(hId->minInBufSize,
           decStatus.bufInfo.minInBufSize, sizeof(hId->minInBufSize));
    hId->minNumInBufs = decStatus.bufInfo.minNumInBufs;
    memcpy(hId->minOutBufSize,
           decStatus.bufInfo.minOutBufSize, sizeof(hId->minOutBufSize));
    hId->minNumOutBufs = decStatus.bufInfo.minNumOutBufs;

    return hId;
}

/******************************************************************************
 * Idec_delete
 ******************************************************************************/
Int Idec_delete(Idec_Handle hId)
{
    if (hId) {
        if (hId->hDecode) {
            IMGDEC_delete(hId->hDecode);
        }

        free(hId);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Idec_getInBufSize
 ******************************************************************************/
Int32 Idec_getInBufSize(Idec_Handle hId)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hId);

    for (bufIdx = 0; bufIdx < hId->minNumInBufs; bufIdx++) {
        size += hId->minInBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Idec_getOutBufSize
 ******************************************************************************/
Int32 Idec_getOutBufSize(Idec_Handle hId)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hId);

    for (bufIdx = 0; bufIdx < hId->minNumOutBufs; bufIdx++) {
        size += hId->minOutBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Idec_getVisaHandle
 ******************************************************************************/
IMGDEC_Handle Idec_getVisaHandle(Idec_Handle hId)
{
    assert(hId);

    return hId->hDecode;
}
