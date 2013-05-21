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
#include <ti/sdo/ce/speech/sphenc.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Senc.h>

#define MODULE_NAME     "Senc"

typedef struct Senc_Object {
    SPHENC_Handle       hEncode;
    Int32               minInBufSize;
    Int32               minOutBufSize;
} Senc_Object;

const SPHENC_Params Senc_Params_DEFAULT = {
    sizeof(SPHENC_Params),
    80,
    ISPEECH_ALAW,
    0,
    0,
};

const SPHENC_DynamicParams Senc_DynamicParams_DEFAULT = {
    sizeof(SPHENC_DynamicParams),
    80,
    0,
    0,
    0,
    0,
    0,
    1,
    0
};

/******************************************************************************
 * Senc_process
 ******************************************************************************/
Int Senc_process(Senc_Handle hSe, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[1];
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    SPHENC_InArgs           inArgs;
    SPHENC_OutArgs          outArgs;
    XDAS_Int32              status;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;

    assert(hSe);
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

    inBufDesc.numBufs       = 1;
    inBufDesc.bufs          = &inPtr;
    inBufDesc.bufSizes      = inBufSizeArray;

    outBufDesc.numBufs      = 1;
    outBufDesc.bufs         = &outPtr;
    outBufDesc.bufSizes     = outBufSizeArray;

    inArgs.size             = sizeof(SPHENC_InArgs);
    outArgs.size            = sizeof(SPHENC_OutArgs);

    /* Encode the speech buffer */
    status = SPHENC_process(hSe->hEncode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    if (status != SPHENC_EOK) {
        Dmai_err1("SPHENC_process() failed with error (%d)\n", (Int)status);
        return Dmai_EFAIL;
    }

    /* Fixed compression rate */
    Buffer_setNumBytesUsed(hOutBuf, Buffer_getNumBytesUsed(hInBuf) / 2);

    return Dmai_EOK;
}

/******************************************************************************
 * Senc_create
 ******************************************************************************/
Senc_Handle Senc_create(Engine_Handle hEngine, Char *codecName,
                        SPHENC_Params *params, SPHENC_DynamicParams *dynParams)
{
    Senc_Handle         hSe;
    SPHENC_Status       encStatus;
    XDAS_Int32          status;
    SPHENC_Handle       hEncode;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    hSe = (Senc_Handle)calloc(1, sizeof(Senc_Object));

    if (hSe == NULL) {
        Dmai_err0("Failed to allocate space for Senc Object\n");
        return NULL;
    }

    /* Create speech encoder */
    hEncode = SPHENC_create(hEngine, codecName, params);

    if (hEncode == NULL) {
        Dmai_err0("Can't open speech encode algorithm\n");
        return NULL;
    }

    /* Set dynamic parameters */
    encStatus.size = sizeof(SPHENC_Status);
    status = SPHENC_control(hEncode, XDM_SETPARAMS, dynParams, &encStatus);

    if (status != SPHENC_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        SPHENC_delete(hEncode);
        free(hSe);
        return NULL;
    }

    /* Get buffer requirements */
    status = SPHENC_control(hEncode, XDM_GETBUFINFO, dynParams, &encStatus);

    if (status != SPHENC_EOK) {
        Dmai_err1("XDM_GETBUFINFO failed, status=%d\n", status);
        SPHENC_delete(hEncode);
        free(hSe);
        return NULL;
    }

    hSe->minInBufSize = encStatus.bufInfo.minInBufSize[0];
    hSe->minOutBufSize = encStatus.bufInfo.minOutBufSize[0];

    hSe->hEncode = hEncode;

    return hSe;
}

/******************************************************************************
 * Senc_delete
 ******************************************************************************/
Int Senc_delete(Senc_Handle hSe)
{
    if (hSe) {
        if (hSe->hEncode) {
            SPHENC_delete(hSe->hEncode);
        }
        free(hSe);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Senc_getVisaHandle
 ******************************************************************************/
SPHENC_Handle Senc_getVisaHandle(Senc_Handle hSe)
{
    assert(hSe);

    return hSe->hEncode;
}

/******************************************************************************
 * Senc_getInBufSize
 ******************************************************************************/
Int32 Senc_getInBufSize(Senc_Handle hSe)
{
    assert(hSe);

#if 0 /* The g.711 encoder does not currently give sensible results */
    return hSe->minInBufSize;
#else
    return 160;
#endif
}

/******************************************************************************
 * Senc_getOutBufSize
 ******************************************************************************/
Int32 Senc_getOutBufSize(Senc_Handle hSe)
{
    assert(hSe);

#if 0 /* The g.711 encoder does not currently give sensible results */
    return hSe->minOutBufSize;
#else
    return 160 / 2;
#endif
}
