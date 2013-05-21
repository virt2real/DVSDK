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
#include <ti/sdo/ce/audio1/auddec1.h>

#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Adec1.h>

#define MODULE_NAME     "Adec1"

typedef struct Adec1_Object {
    AUDDEC1_Handle          hDecode;
    Int                     sampleRate;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Adec1_Object;

const AUDDEC1_Params Adec1_Params_DEFAULT = {
    sizeof(AUDDEC1_Params),
    16,
    IAUDIO_INTERLEAVED,
    XDM_BYTE,
};

const AUDDEC1_DynamicParams Adec1_DynamicParams_DEFAULT = {
    sizeof(AUDDEC1_DynamicParams),
    XDAS_FALSE,
};

/* Number of channels for each IAUDIO_ChannelMode */
static Int numChans[11] = { 1, 2, 2, 3, 3, 4, 4, 5, 5, 6, 7 };

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Adec1_Handle hAd1)
{
    if (hAd1->hDecode) {
        AUDDEC1_delete(hAd1->hDecode);
    }

    free(hAd1);

    return Dmai_EOK;
}

/******************************************************************************
 * Adec1_process
 ******************************************************************************/
Int Adec1_process(Adec1_Handle hAd1, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    XDM1_BufDesc            inBufDesc;
    XDM1_BufDesc            outBufDesc;
    XDAS_Int32              status;
    AUDDEC1_InArgs          inArgs;
    AUDDEC1_OutArgs         outArgs;
    Int                     channels;

    assert(hAd1);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hOutBuf));
    assert(Buffer_getSize(hInBuf));

    inBufDesc.numBufs           = 1;
    inBufDesc.descs[0].buf      = Buffer_getUserPtr(hInBuf);
    inBufDesc.descs[0].bufSize  = Buffer_getSize(hInBuf);

    outBufDesc.numBufs          = 1;
    outBufDesc.descs[0].buf     = Buffer_getUserPtr(hOutBuf);
    outBufDesc.descs[0].bufSize = Buffer_getSize(hOutBuf);

    inArgs.size                 = sizeof(AUDDEC1_InArgs);
    inArgs.numBytes             = Buffer_getNumBytesUsed(hInBuf);
    inArgs.desiredChannelMode   = IAUDIO_2_0;
    inArgs.lfeFlag              = XDAS_FALSE;

    outArgs.size                = sizeof(AUDDEC1_OutArgs);

    /* Decode the audio buffer */
    status = AUDDEC1_process(hAd1->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                             &outArgs);

    Dmai_dbg3("AUDDEC1_process() ret %d, consumed %d, created %d samples\n",
              (Int) status, (Int) outArgs.bytesConsumed,
              (Int) outArgs.numSamples);

    Buffer_setNumBytesUsed(hInBuf, outArgs.bytesConsumed);

    if (status != AUDDEC1_EOK) {
        if (XDM_ISFATALERROR(outArgs.extendedError)) {
            Dmai_err2("AUDDEC1_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns) outArgs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("AUDDEC1_process() non-fatal error 0x%x\n",
                      (Uns) outArgs.extendedError);
            return Dmai_EBITERROR;
        }
    }

    channels = numChans[outArgs.channelMode];

    Buffer_setNumBytesUsed(hOutBuf, outArgs.numSamples * 2 * channels);
    hAd1->sampleRate = outArgs.sampleRate;

    return Dmai_EOK;
}

/******************************************************************************
 * Adec1_create
 ******************************************************************************/
Adec1_Handle Adec1_create(Engine_Handle hEngine, Char *codecName,
                        AUDDEC1_Params *params,
                        AUDDEC1_DynamicParams *dynParams)
{
    Adec1_Handle        hAd1;
    AUDDEC1_Handle      hDecode;
    AUDDEC1_Status      decStatus;
    XDAS_Int32          status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hAd1 = (Adec1_Handle)calloc(1, sizeof(Adec1_Object));

    if (hAd1 == NULL) {
        Dmai_err0("Failed to allocate space for Adec1 Object\n");
        return NULL;
    }

    /* Create audio decoder */
    hDecode = AUDDEC1_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err1("Failed to open audio decode algorithm: %s\n", codecName);
        cleanup(hAd1);
        return NULL;
    }

    /* Set dynamic parameters */
    decStatus.data.buf = NULL;
    decStatus.size = sizeof(AUDDEC1_Status);
    status = AUDDEC1_control(hDecode, XDM_SETPARAMS, dynParams, &decStatus);

    if (status != AUDDEC1_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        cleanup(hAd1);
        return NULL;
    }

    /* Get buffer information from audio decoder */
    status = AUDDEC1_control(hDecode, XDM_GETBUFINFO, dynParams, &decStatus);

    if (status != AUDDEC1_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        cleanup(hAd1);
        return NULL;
    }

    Dmai_dbg2("Codec requires buffer sizes in %u and out %u\n",
              decStatus.bufInfo.minInBufSize[0],
              decStatus.bufInfo.minOutBufSize[0]);

    memcpy(hAd1->minInBufSize,
           decStatus.bufInfo.minInBufSize, sizeof(hAd1->minInBufSize));
    hAd1->minNumInBufs = decStatus.bufInfo.minNumInBufs;
    memcpy(hAd1->minOutBufSize,
           decStatus.bufInfo.minOutBufSize, sizeof(hAd1->minOutBufSize));
    hAd1->minNumOutBufs = decStatus.bufInfo.minNumOutBufs;

    hAd1->hDecode = hDecode;
    hAd1->sampleRate = 0;

    return hAd1;
}

/******************************************************************************
 * Adec1_delete
 ******************************************************************************/
Int Adec1_delete(Adec1_Handle hAd1)
{
    if (hAd1) {
        return cleanup(hAd1);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Adec1_getVisaHandle
 ******************************************************************************/
AUDDEC1_Handle Adec1_getVisaHandle(Adec1_Handle hAd1)
{
    assert(hAd1);

    return hAd1->hDecode;
}

/******************************************************************************
 * Adec1_getSampleRate
 ******************************************************************************/
Int Adec1_getSampleRate(Adec1_Handle hAd1)
{
    assert(hAd1);

    return hAd1->sampleRate;
}

/******************************************************************************
 * Adec1_getInBufSize
 ******************************************************************************/
Int32 Adec1_getInBufSize(Adec1_Handle hAd1)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hAd1);

    for (bufIdx = 0; bufIdx < hAd1->minNumInBufs; bufIdx++) {
        size += hAd1->minInBufSize[bufIdx];
    }

    return size;
}

/******************************************************************************
 * Adec1_getOutBufSize
 ******************************************************************************/
Int32 Adec1_getOutBufSize(Adec1_Handle hAd1)
{
    Int32 size = 0;
    Int bufIdx;

    assert(hAd1);

    for (bufIdx = 0; bufIdx < hAd1->minNumOutBufs; bufIdx++) {
        size += hAd1->minOutBufSize[bufIdx];
    }

    return size;
}
