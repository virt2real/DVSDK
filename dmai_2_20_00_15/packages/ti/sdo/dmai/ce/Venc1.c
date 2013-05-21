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
#include <ti/sdo/ce/video1/videnc1.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/ce/Venc1.h>
#include <ti/sdo/dmai/BufferGfx.h>

#define MODULE_NAME     "Venc1"

/* As 0 is not a valid buffer id in XDM 1.0, we need macros for easy access */
#define GETID(x)  ((x) + 1)
#define GETIDX(x) ((x) - 1)

typedef struct Venc1_Object {
    VIDENC1_Handle          hEncode;
    IVIDEO1_BufDesc         reconBufs;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
    BufTab_Handle           hInBufTab;
    Buffer_Handle           hFreeBuf;
    VIDENC1_DynamicParams   dynParams;
} Venc1_Object;

const VIDENC1_Params Venc1_Params_DEFAULT = {
    sizeof(VIDENC1_Params),           /* size */
    XDM_DEFAULT,                      /* encodingPreset */
    IVIDEO_LOW_DELAY,                 /* rateControlPreset */
    720,                              /* maxHeight */
    1280,                             /* maxWidth */
    30000,                            /* maxFrameRate */
    6000000,                          /* maxBitRate */
    XDM_BYTE,                         /* dataEndianness */
    0,                                /* maxInterFrameInterval */
    XDM_YUV_420P,                     /* inputChromaFormat */
    IVIDEO_PROGRESSIVE,               /* inputContentType */
    XDM_CHROMA_NA                     /* reconChromaFormat */
};

const VIDENC1_DynamicParams Venc1_DynamicParams_DEFAULT = {
    sizeof(IVIDENC1_DynamicParams),   /* size */
    720,                              /* inputHeight */
    1280,                             /* inputWidth */
    30000,                            /* refFrameRate */
    30000,                            /* targetFrameRate */
    6000000,                          /* targetBitRate */
    30,                               /* intraFrameInterval */
    XDM_ENCODE_AU,                    /* generateHeader */
    0,                                /* captureWidth */
    IVIDEO_NA_FRAME,                  /* forceFrame */
    1,                                /* interFrameInterval */
    0                                 /* mbDataFlag */
};

/******************************************************************************
 * Venc1_process
 ******************************************************************************/
Int Venc1_process(Venc1_Handle hVe, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    IVIDEO1_BufDescIn       inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              outBufSizeArray[1];
    XDAS_Int32              status;
    VIDENC1_InArgs          inArgs;
    VIDENC1_OutArgs         outArgs;
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

    inPtr  = Buffer_getUserPtr(hInBuf)  + offset;
    outPtr = Buffer_getUserPtr(hOutBuf);

    /* Set up the codec buffer dimensions */
    inBufDesc.frameWidth                = dim.width;
    inBufDesc.frameHeight               = dim.height;
    inBufDesc.framePitch                = dim.lineLength;

    /* Point to the color planes depending on color space format */
    if (BufferGfx_getColorSpace(hInBuf) == ColorSpace_YUV420PSEMI) {
        inBufDesc.bufDesc[0].bufSize    = hVe->minInBufSize[0];
        inBufDesc.bufDesc[1].bufSize    = hVe->minInBufSize[1];

        inBufDesc.bufDesc[0].buf        = inPtr;
        inBufDesc.bufDesc[1].buf        = inPtr + Buffer_getSize(hInBuf) * 2/3;
        inBufDesc.numBufs               = 2;
    }
    else if (BufferGfx_getColorSpace(hInBuf) == ColorSpace_UYVY) {
        inBufDesc.bufDesc[0].bufSize    = Buffer_getSize(hInBuf);
        inBufDesc.bufDesc[0].buf        = inPtr;
        inBufDesc.numBufs               = 1;
    }
    else {
        Dmai_err0("Unsupported color format of input buffer\n");
        return Dmai_EINVAL;
    }

    outBufSizeArray[0]                  = Buffer_getSize(hOutBuf);

    outBufDesc.numBufs                  = 1;
    outBufDesc.bufs                     = &outPtr;
    outBufDesc.bufSizes                 = outBufSizeArray;

    inArgs.size                         = sizeof(VIDENC1_InArgs);
    inArgs.inputID                      = GETID(Buffer_getId(hInBuf));

    /* topFieldFirstFlag is hardcoded. Used only for interlaced content */
    inArgs.topFieldFirstFlag            = 1;
    
    outArgs.size                        = sizeof(VIDENC1_OutArgs);

    /* Encode video buffer */
    status = VIDENC1_process(hVe->hEncode, &inBufDesc, &outBufDesc, &inArgs,
                             &outArgs);

    Dmai_dbg4("VIDENC1_process() ret %d inId %d outID %d generated %d bytes\n",
        status, Buffer_getId(hInBuf), outArgs.outputID, outArgs.bytesGenerated);

    if (status != VIDENC1_EOK) {
        Dmai_err2("VIDENC1_process() failed with error (%d ext: 0x%x)\n",
                  (Int)status, (Uns) outArgs.extendedError);
        return Dmai_EFAIL;
    }
   
    /* if memTab was used for input buffers */
    if(hVe->hInBufTab != NULL) {
        /* One buffer is freed when output content is generated */
        if(outArgs.bytesGenerated>0) {
            /* Buffer released by the encoder */
            hVe->hFreeBuf = BufTab_getBuf(hVe->hInBufTab, GETIDX(outArgs.outputID));
        }
        else {
            hVe->hFreeBuf = NULL;
        }
    }

    /* Copy recon buffer information so we can retrieve it later */
    hVe->reconBufs = outArgs.reconBufs;

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
 * Venc1_create
 ******************************************************************************/
Venc1_Handle Venc1_create(Engine_Handle hEngine, Char *codecName,
                          VIDENC1_Params *params,
                          VIDENC1_DynamicParams *dynParams)
{
    Venc1_Handle            hVe;
    VIDENC1_Status          encStatus;
    XDAS_Int32              status;
    VIDENC1_Handle          hEncode;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hVe = (Venc1_Handle)calloc(1, sizeof(Venc1_Object));

    if (hVe == NULL) {
        Dmai_err0("Failed to allocate space for Venc1 Object\n");
        return NULL;
    }

    Dmai_dbg5("Creating encoder %s for max %dx%d bitrate %d ratectrl %d\n",
              codecName, params->maxWidth, params->maxHeight,
              params->maxBitRate, params->rateControlPreset);

    /* Create video encoder instance */
    hEncode = VIDENC1_create(hEngine, codecName, params);

    if (hEncode == NULL) {
        Dmai_err2("Failed to open video encode algorithm: %s (0x%x)\n",
                 codecName, Engine_getLastError(hEngine));
        free(hVe);
        return NULL;
    }

    Dmai_dbg3("Setting dynParams size %dx%d bitrate %d\n",
              dynParams->inputWidth, dynParams->inputHeight,
             dynParams->targetBitRate);

    /* Set video encoder dynamic parameters */
    encStatus.size = sizeof(VIDENC1_Status);
    encStatus.data.buf = NULL;

    status = VIDENC1_control(hEncode, XDM_SETPARAMS, dynParams, &encStatus);

    if (status != VIDENC1_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        VIDENC1_delete(hEncode);
        free(hVe);
        return NULL;
    }

    Dmai_dbg0("Made XDM_SETPARAMS control call\n");

    hVe->dynParams = *dynParams;

    /* Get buffer information from video encoder */
    status = VIDENC1_control(hEncode, XDM_GETBUFINFO, dynParams, &encStatus);

    if (status != VIDENC1_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        VIDENC1_delete(hEncode);
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
 * Venc1_delete
 ******************************************************************************/
Int Venc1_delete(Venc1_Handle hVe)
{
    if (hVe) {
        if (hVe->hEncode) {
            VIDENC1_delete(hVe->hEncode);
        }

        free(hVe);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Venc1_getInBufSize
 ******************************************************************************/
Int32 Venc1_getInBufSize(Venc1_Handle hVe)
{
    Int32 size = 0;
    Int i;

    assert(hVe);

    for (i = 0; i < hVe->minNumInBufs; i++) {
        size += hVe->minInBufSize[i];
    }

    return size;
}

/******************************************************************************
 * Venc1_getOutBufSize
 ******************************************************************************/
Int32 Venc1_getOutBufSize(Venc1_Handle hVe)
{
    assert(hVe);

    return hVe->minOutBufSize[0];
}

/******************************************************************************
 * Venc1_getVisaHandle
 ******************************************************************************/
VIDENC1_Handle Venc1_getVisaHandle(Venc1_Handle hVe)
{
    assert(hVe);

    return hVe->hEncode;
}

/******************************************************************************
 * Venc1_getReconBufs 
 ******************************************************************************/
IVIDEO1_BufDesc* Venc1_getReconBufs(Venc1_Handle hVe)
{
    assert(hVe);

    return &hVe->reconBufs;
}

/******************************************************************************
 * Venc1_setBufTab
 ******************************************************************************/
Void Venc1_setBufTab(Venc1_Handle hVe, BufTab_Handle hBufTab)
{
    assert(hVe);

    hVe->hInBufTab = hBufTab;
}

/******************************************************************************
 * Venc1_getBufTab
 ******************************************************************************/
BufTab_Handle Venc1_getBufTab(Venc1_Handle hVe)
{
    assert(hVe);

    return hVe->hInBufTab;
}

/******************************************************************************
 * Venc1_getFreeBuf
 ******************************************************************************/
Buffer_Handle Venc1_getFreeBuf(Venc1_Handle hVe)
{
    Buffer_Handle hFreeBuf;

    assert(hVe);

    hFreeBuf = hVe->hFreeBuf;
    hVe->hFreeBuf = NULL;

    return hFreeBuf;
}


/******************************************************************************
 * Venc1_flush
 ******************************************************************************/
Int Venc1_flush(Venc1_Handle hVe)
{
    VIDENC1_Status         encStatus;
    XDAS_Int32             status;

    assert(hVe);

    encStatus.data.buf = NULL;
    encStatus.size = sizeof(VIDENC1_Status);

    /* Flush the codec */
    status = VIDENC1_control(hVe->hEncode, XDM_FLUSH,
                             &hVe->dynParams,&encStatus);

    if (status != VIDENC1_EOK) {
        Dmai_err0("XDM_FLUSH control failed\n");
        return Dmai_EFAIL;
    }

    return Dmai_EOK;
}

