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
#include <ti/sdo/ce/audio/auddec.h>

#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Adec.h>

#define MODULE_NAME     "Adec"

typedef struct Adec_Object {
    AUDDEC_Handle           hDecode;
    Int                     sampleRate;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Adec_Object;

const AUDDEC_Params Adec_Params_DEFAULT = {
    sizeof(AUDDEC_Params),
    48000,
    448000,
    IAUDIO_STEREO,
    XDM_BYTE,
};

const AUDDEC_DynamicParams Adec_DynamicParams_DEFAULT = {
    sizeof(AUDDEC_DynamicParams),
    IAUDIO_INTERLEAVED,
};

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Adec_Handle hAd)
{
    if (hAd->hDecode) {
        AUDDEC_delete(hAd->hDecode);
    }

    free(hAd);

    return Dmai_EOK;
}

/******************************************************************************
 * Adec_process
 ******************************************************************************/
Int Adec_process(Adec_Handle hAd, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    AUDDEC_DynamicParams    dynParams;
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[1];
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              status;
    AUDDEC_InArgs           inArgs;
    AUDDEC_OutArgs          outArgs;
    AUDDEC_Status           decStatus;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;

    assert(hAd);
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

    inArgs.size             = sizeof(AUDDEC_InArgs);
    inArgs.numBytes         = Buffer_getNumBytesUsed(hInBuf);

    outArgs.size            = sizeof(AUDDEC_OutArgs);

    /* Decode the audio buffer */
    status = AUDDEC_process(hAd->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    Buffer_setNumBytesUsed(hInBuf, outArgs.bytesConsumed);

    if (status != AUDDEC_EOK) {
        if (status == AUDDEC_ERUNTIME ||
            outArgs.bytesConsumed == 0 ||
            XDM_ISFATALERROR(outArgs.extendedError)) {

            Dmai_err2("AUDDEC_process() failed with error (%d ext: 0x%x)\n",
                   (Int)status, (Uns) outArgs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("AUDDEC_process() non-fatal error 0x%x\n",
                      (Uns) outArgs.extendedError);
            return Dmai_EBITERROR;
        }
    }

    /* Get the dynamic codec status */
    decStatus.size = sizeof(AUDDEC_Status);
    dynParams.size = sizeof(AUDDEC_DynamicParams);
    status = AUDDEC_control(hAd->hDecode, XDM_GETSTATUS, &dynParams,
                            &decStatus);

    if (status != AUDDEC_EOK) {
        Dmai_err1("XDM_GETSTATUS failed, status=%d\n", status);
        return Dmai_EFAIL;
    }

    Buffer_setNumBytesUsed(hOutBuf, decStatus.frameLen * 4);
    hAd->sampleRate = decStatus.sampleRate;

    return Dmai_EOK;
}

/******************************************************************************
 * Adec_create
 ******************************************************************************/
Adec_Handle Adec_create(Engine_Handle hEngine, Char *codecName,
                        AUDDEC_Params *params,
                        AUDDEC_DynamicParams *dynParams)
{
    Adec_Handle         hAd;
    AUDDEC_Handle       hDecode;
    AUDDEC_Status       decStatus;
    XDAS_Int32          status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hAd = (Adec_Handle)calloc(1, sizeof(Adec_Object));

    if (hAd == NULL) {
        Dmai_err0("Failed to allocate space for Adec Object\n");
        return NULL;
    }

    /* Create audio decoder */
    hDecode = AUDDEC_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err1("Failed to open audio decode algorithm: %s\n", codecName);
        cleanup(hAd);
        return NULL;
    }

    /* Set dynamic parameters */
    decStatus.size = sizeof(AUDDEC_Status);
    status = AUDDEC_control(hDecode, XDM_SETPARAMS, dynParams, &decStatus);

    if (status != AUDDEC_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        cleanup(hAd);
        return NULL;
    }

    /* Get buffer information from audio decoder */
    status = AUDDEC_control(hDecode, XDM_GETBUFINFO, dynParams, &decStatus);

    if (status != AUDDEC_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        cleanup(hAd);
        return NULL;
    }

    Dmai_dbg2("Codec requires buffer sizes in %u and out %u\n",
              decStatus.bufInfo.minInBufSize[0],
              decStatus.bufInfo.minInBufSize[1]);

    memcpy(hAd->minInBufSize,
           decStatus.bufInfo.minInBufSize, sizeof(hAd->minInBufSize));
    hAd->minNumInBufs = decStatus.bufInfo.minNumInBufs;
    memcpy(hAd->minOutBufSize,
           decStatus.bufInfo.minOutBufSize, sizeof(hAd->minOutBufSize));
    hAd->minNumOutBufs = decStatus.bufInfo.minNumOutBufs;

    hAd->hDecode = hDecode;
    hAd->sampleRate = 0;

    return hAd;
}

/******************************************************************************
 * Adec_delete
 ******************************************************************************/
Int Adec_delete(Adec_Handle hAd)
{
    if (hAd) {
        return cleanup(hAd);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Adec_getVisaHandle
 ******************************************************************************/
AUDDEC_Handle Adec_getVisaHandle(Adec_Handle hAd)
{
    assert(hAd);

    return hAd->hDecode;
}

/******************************************************************************
 * Adec_getSampleRate
 ******************************************************************************/
Int Adec_getSampleRate(Adec_Handle hAd)
{
    assert(hAd);

    return hAd->sampleRate;
}

/******************************************************************************
 * Adec_getInBufSize
 ******************************************************************************/
Int32 Adec_getInBufSize(Adec_Handle hAd)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hAd);

    for (bufIdx = 0; bufIdx < hAd->minNumInBufs; bufIdx++) {
        size += hAd->minInBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Adec_getOutBufSize
 ******************************************************************************/
Int32 Adec_getOutBufSize(Adec_Handle hAd)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hAd);

    for (bufIdx = 0; bufIdx < hAd->minNumOutBufs; bufIdx++) {
        size += hAd->minOutBufSize[bufIdx];
    }

    return size;
}
