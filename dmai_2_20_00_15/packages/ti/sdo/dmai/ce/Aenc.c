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
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio/audenc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Aenc.h>

#define MODULE_NAME     "Aenc"

typedef struct Aenc_Object {
    AUDENC_Handle       hEncode;
    Int32               minInBufSize;
    Int32               minOutBufSize;
} Aenc_Object;

const AUDENC_Params Aenc_Params_DEFAULT = {
    sizeof(AUDENC_Params),
    XDM_DEFAULT,
    48000,
    288000,
    IAUDIO_STEREO,
    XDM_LE_16
};

const AUDENC_DynamicParams Aenc_DynamicParams_DEFAULT = {
    sizeof(AUDENC_DynamicParams),
    IAUDIO_INTERLEAVED,
    288000,
    48000,
    IAUDIO_STEREO,
    0,
    16
};

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Aenc_Handle hAe)
{
    if (hAe->hEncode) {
        AUDENC_delete(hAe->hEncode);
    }

    free(hAe);

    return Dmai_EOK;
}

/******************************************************************************
 * Aenc_process
 ******************************************************************************/
Int Aenc_process(Aenc_Handle hAe, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[1];
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              status;
    AUDENC_InArgs           inArgs;
    AUDENC_OutArgs          outArgs;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;

    assert(hAe);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hOutBuf));

    inPtr = Buffer_getUserPtr(hInBuf);
    outPtr = Buffer_getUserPtr(hOutBuf);

    inBufSizeArray[0]       = Buffer_getNumBytesUsed(hInBuf);
    outBufSizeArray[0]      = Buffer_getSize(hOutBuf);

    inBufDesc.bufSizes      = inBufSizeArray;
    inBufDesc.bufs          = &inPtr;
    inBufDesc.numBufs       = 1;

    outBufDesc.bufSizes     = outBufSizeArray;
    outBufDesc.bufs         = &outPtr;
    outBufDesc.numBufs      = 1;

    inArgs.size             = sizeof(AUDENC_InArgs);
    outArgs.size            = sizeof(AUDENC_OutArgs);

    /* Encode the audio buffer */
    status = AUDENC_process(hAe->hEncode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    if (status != AUDENC_EOK) {
        Dmai_err2("AUDENC_process() failed with error (%d ext: 0x%x)\n",
                  (Int)status, (Uns) outArgs.extendedError);
        return Dmai_EFAIL;
    }

    Buffer_setNumBytesUsed(hOutBuf, outArgs.bytesGenerated);

    return Dmai_EOK;
}

/******************************************************************************
 * Aenc_create
 ******************************************************************************/
Aenc_Handle Aenc_create(Engine_Handle hEngine,
                        Char *codecName,
                        AUDENC_Params *params,
                        AUDENC_DynamicParams *dynParams)
{
    Aenc_Handle         hAe;
    AUDENC_Handle       hEncode;
    AUDENC_Status       encStatus;
    XDAS_Int32          status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hAe = (Aenc_Handle)calloc(1, sizeof(Aenc_Object));

    if (hAe == NULL) {
        Dmai_err0("Failed to allocate space for Aenc Object\n");
        return NULL;
    }

    /* Create audio encoder */
    hEncode = AUDENC_create(hEngine, codecName, params);

    if (hEncode == NULL) {
        Dmai_err0("Can't open audio encode algorithm\n");
        cleanup(hAe);
        return NULL;
    }

    /* Set dynamic parameters */
    encStatus.size = sizeof(AUDENC_Status);
    status = AUDENC_control(hEncode, XDM_SETPARAMS, dynParams, &encStatus);

    if (status != AUDENC_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        cleanup(hAe);
        return NULL;
    }

    /* Get buffer requirements */
    status = AUDENC_control(hEncode, XDM_GETBUFINFO, dynParams, &encStatus);

    if (status != AUDENC_EOK) {
        Dmai_err1("XDM_GETBUFINFO failed, status=%d\n", status);
        cleanup(hAe);
        return NULL;
    }

    hAe->minInBufSize = encStatus.bufInfo.minInBufSize[0];
    hAe->minOutBufSize = encStatus.bufInfo.minOutBufSize[0];

    hAe->hEncode = hEncode;

    return hAe;
}

/******************************************************************************
 * Aenc_delete
 ******************************************************************************/
Int Aenc_delete(Aenc_Handle hAe)
{
    if (hAe) {
        return cleanup(hAe);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Aenc_getVisaHandle
 ******************************************************************************/
AUDENC_Handle Aenc_getVisaHandle(Aenc_Handle hAe)
{
    assert(hAe);

    return hAe->hEncode;
}

/******************************************************************************
 * Aenc_getInBufSize
 ******************************************************************************/
Int32 Aenc_getInBufSize(Aenc_Handle hAe)
{
    assert(hAe);

    return hAe->minInBufSize;
}

/******************************************************************************
 * Aenc_getOutBufSize
 ******************************************************************************/
Int32 Aenc_getOutBufSize(Aenc_Handle hAe)
{
    assert(hAe);

    return hAe->minOutBufSize;
}
