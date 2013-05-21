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
#include <ti/sdo/ce/image1/imgdec1.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Idec1.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Idec1"

typedef struct Idec1_Object {
    IMGDEC1_Handle          hDecode;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Idec1_Object;

const IMGDEC1_Params Idec1_Params_DEFAULT = {
    sizeof(IMGDEC1_Params),         /* size */
    576,                            /* maxHeight */
    720,                            /* maxWidth */
    15,                             /* maxScans */
    XDM_BYTE,                       /* dataEndianess */
    XDM_YUV_422ILE,                 /* forceChromaFormat */
};

const IMGDEC1_DynamicParams Idec1_DynamicParams_DEFAULT = {
    sizeof(IMGDEC1_DynamicParams),  /* size */
    XDM_DEFAULT,                    /* numAu */    
    XDM_DECODE_AU,                  /* decodeHeader */
    0,                              /* displayWidth */
};

/******************************************************************************
 * Idec1_process
 ******************************************************************************/
Int Idec1_process(Idec1_Handle hId, Buffer_Handle hInBuf,
                 Buffer_Handle hOutBuf)
{
    BufferGfx_Dimensions    dim;
    IMGDEC1_DynamicParams   dynParams;
    IMGDEC1_InArgs          inArgs;
    IMGDEC1_OutArgs         outArgs;
    IMGDEC1_Status          decStatus;
    XDM1_BufDesc            inBufDesc;
    XDM1_BufDesc            outBufDesc;
    XDAS_Int32              status;
    XDAS_Int8 *             inPtr;
    XDAS_Int8 *             outPtr;
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

    Dmai_clear(dynParams); 

    BufferGfx_getDimensions(hOutBuf, &dim);
    
    inPtr  = Buffer_getUserPtr(hInBuf);
    outPtr = Buffer_getUserPtr(hOutBuf);

    inArgs.size             = sizeof(IMGDEC1_InArgs);
    inArgs.numBytes         = Buffer_getNumBytesUsed(hInBuf);

    outArgs.size            = sizeof(IMGDEC1_OutArgs);

    inBufDesc.numBufs       = 1;
    outBufDesc.numBufs      = hId->minNumOutBufs;
    
    inBufDesc.descs[0].buf = inPtr;
    inBufDesc.descs[0].bufSize = Buffer_getSize(hInBuf);

    for(i = 0; i < hId->minNumOutBufs; i++)
    {
        outBufDesc.descs[i].buf = (XDAS_Int8 *)((unsigned int)outPtr + offset);
        offset +=  hId->minOutBufSize[i];
        outBufDesc.descs[i].bufSize = hId->minOutBufSize[i];
    }   
        
    /* Decode image buffer */
    status = IMGDEC1_process(hId->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    Buffer_setNumBytesUsed(hInBuf, outArgs.bytesConsumed);

    if (status != IMGDEC1_EOK) {
        if (XDM_ISFATALERROR(outArgs.extendedError)) {
            Dmai_err2("IMGDEC1_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns) outArgs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("IMGDEC1_process() non-fatal error 0x%x\n",
                      (Uns) outArgs.extendedError);
            return Dmai_EBITERROR;
        }
    }

    /* Get the dynamic codec status */
    decStatus.data.buf = NULL;
    decStatus.size = sizeof(IMGDEC1_Status);
    dynParams.size = sizeof(IMGDEC1_DynamicParams);
    status = IMGDEC1_control(hId->hDecode, XDM_GETSTATUS, &dynParams,
                            &decStatus);

    if (status != IMGDEC1_EOK) {
        Dmai_err1("XDM_GETSTATUS failed, status=%d\n", status);
        return Dmai_EFAIL;
    }

    /* Set output Color Format */
    switch (decStatus.outputChromaFormat) {
        case XDM_YUV_422ILE:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_UYVY); 
            break;
        case XDM_YUV_420P:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_YUV420P); 
            break;
        case XDM_YUV_420SP:
            BufferGfx_setColorSpace (hOutBuf, ColorSpace_YUV420PSEMI); 
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
            printf("Unsupported output color space %ld.\n", 
                decStatus.outputChromaFormat);
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
 * Idec1_create
 ******************************************************************************/
Idec1_Handle Idec1_create(Engine_Handle hEngine, Char *codecName,
                        IMGDEC1_Params *params, 
                        IMGDEC1_DynamicParams *dynParams)
{
    Idec1_Handle             hId;
    IMGDEC1_Handle           hDecode;
    IMGDEC1_Status           decStatus;
    XDAS_Int32               status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hId = (Idec1_Handle)calloc(1, sizeof(Idec1_Object));

    if (hId == NULL) {
        Dmai_err0("Failed to allocate space for Idec1 Object\n");
        return NULL;
    }

    /* Create image decoder instance */
    hDecode = IMGDEC1_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err0("Failed to open image decode algorithm\n");
        free(hId);
        return NULL;
    }

    Dmai_dbg0("Image decoder instance created\n");

    /* Set image decoder dynamic params */
    decStatus.data.buf = NULL;
    decStatus.size = sizeof(IMGDEC1_Status);
    status = IMGDEC1_control(hDecode, XDM_SETPARAMS, dynParams,
                            &decStatus);

    if (status != IMGDEC1_EOK) {
        Dmai_err0("XDM_SETPARAMS control failed\n");
        IMGDEC1_delete(hDecode);
        free(hId);
        return NULL;
    }

    /* Get buffer information from image decoder */
    status = IMGDEC1_control(hDecode, XDM_GETBUFINFO, dynParams,
                            &decStatus);

    if (status != IMGDEC1_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        IMGDEC1_delete(hDecode);
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
 * Idec1_delete
 ******************************************************************************/
Int Idec1_delete(Idec1_Handle hId)
{
    if (hId) {
        if (hId->hDecode) {
            IMGDEC1_delete(hId->hDecode);
        }

        free(hId);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Idec1_getInBufSize
 ******************************************************************************/
Int32 Idec1_getInBufSize(Idec1_Handle hId)
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
 * Idec1_getOutBufSize
 ******************************************************************************/
Int32 Idec1_getOutBufSize(Idec1_Handle hId)
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
 * Idec1_getVisaHandle
 ******************************************************************************/
IMGDEC1_Handle Idec1_getVisaHandle(Idec1_Handle hId)
{
    assert(hId);

    return hId->hDecode;
}






