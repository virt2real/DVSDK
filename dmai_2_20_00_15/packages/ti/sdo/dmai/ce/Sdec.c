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
#include <ti/sdo/ce/speech/sphdec.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Sdec.h>

#define MODULE_NAME     "Sdec"

typedef struct Sdec_Object {
    SPHDEC_Handle           hDecode;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Sdec_Object;

const SPHDEC_Params Sdec_Params_DEFAULT = {
    sizeof(SPHDEC_Params),
    0,
    ISPEECH_ALAW,
    0,
};

const SPHDEC_DynamicParams Sdec_DynamicParams_DEFAULT = {
    sizeof(SPHDEC_DynamicParams),
    0
};

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Sdec_Handle hSd)
{
    if (hSd->hDecode) {
        SPHDEC_delete(hSd->hDecode);
    }

    free(hSd);

    return Dmai_EOK;
}

/******************************************************************************
 * Sdec_process
 ******************************************************************************/
Int Sdec_process(Sdec_Handle hSd, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    SPHDEC_DynamicParams    dynamicParams;
    SPHDEC_Status           decStatus;
    XDM_BufDesc             inBufDesc;
    XDM_BufDesc             outBufDesc;
    XDAS_Int32              inBufSizeArray[1];
    XDAS_Int32              outBufSizeArray[1];
    XDAS_Int32              status;
    SPHDEC_InArgs           inArgs;
    SPHDEC_OutArgs          outArgs;
    XDAS_Int8              *inPtr;
    XDAS_Int8              *outPtr;

    assert(hSd);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hOutBuf));

    inPtr = Buffer_getUserPtr(hInBuf);
    outPtr = Buffer_getUserPtr(hOutBuf);

    inBufSizeArray[0]          = Buffer_getNumBytesUsed(hInBuf);
    outBufSizeArray[0]         = Buffer_getSize(hOutBuf);

    inBufDesc.bufSizes         = inBufSizeArray;
    inBufDesc.bufs             = &inPtr;
    inBufDesc.numBufs          = 1;

    outBufDesc.bufSizes        = outBufSizeArray;
    outBufDesc.bufs            = &outPtr;
    outBufDesc.numBufs         = 1;

    inArgs.size                = sizeof(SPHDEC_InArgs);
    inArgs.inBufferSize        = Buffer_getNumBytesUsed(hInBuf);

    outArgs.size               = sizeof(SPHDEC_OutArgs);

    /* Decode the speech buffer */
    status = SPHDEC_process(hSd->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    if (status != SPHDEC_EOK) {
        decStatus.size = sizeof(SPHDEC_Status);
        dynamicParams.size = sizeof(SPHDEC_DynamicParams);
        status = SPHDEC_control(hSd->hDecode, XDM_GETSTATUS, &dynamicParams,
                                &decStatus);
        if (status != SPHDEC_EOK) {
            Dmai_err1("XDM_GETSTATUS failed, status=%d\n", status);
            return Dmai_EFAIL;
        }

        if (status == SPHDEC_ERUNTIME ||
            XDM_ISFATALERROR(decStatus.extendedError)) {

            Dmai_err2("SPHDEC_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns) decStatus.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("SPHDEC_process() non-fatal error 0x%x\n",
                      (Uns) decStatus.extendedError);
            return Dmai_EBITERROR;
        }
    }

    /* A fixed x2 decompression ratio, only works for g711 */
    Buffer_setNumBytesUsed(hOutBuf, Buffer_getNumBytesUsed(hInBuf) * 2);

    return Dmai_EOK;
}

/******************************************************************************
 * Sdec_create
 ******************************************************************************/
Sdec_Handle Sdec_create(Engine_Handle hEngine, Char *codecName,
                        SPHDEC_Params *params, SPHDEC_DynamicParams *dynParams)
{
    Sdec_Handle         hSd;
    SPHDEC_Handle       hDecode;
    SPHDEC_Status       decStatus;
    XDAS_Int32          status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hSd = (Sdec_Handle)calloc(1, sizeof(Sdec_Object));

    if (hSd == NULL) {
        Dmai_err0("Failed to allocate space for Sdec Object\n");
        return NULL;
    }

    /* Create speech decoder */
    hDecode = SPHDEC_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err0("Failed to create speech decoder\n");
        cleanup(hSd);
        return NULL;
    }

    Dmai_dbg1("Speech decoder instance of %s created\n", codecName);

    /* Set dynamic parameters */
    decStatus.size = sizeof(SPHDEC_Status);
    status = SPHDEC_control(hDecode, XDM_SETPARAMS, dynParams, &decStatus);

    if (status != SPHDEC_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        SPHDEC_delete(hDecode);
        cleanup(hSd);
        return NULL;
    }

    /* Get buffer information from video decoder */
    status = SPHDEC_control(hDecode, XDM_GETBUFINFO, dynParams,
                            &decStatus);

    if (status != SPHDEC_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        SPHDEC_delete(hDecode);
        cleanup(hSd);
        return NULL;
    }

    Dmai_dbg2("Speech decoder requires buffer sizes in %u and out %u\n",
              (Uns) decStatus.bufInfo.minInBufSize[0],
              (Uns) decStatus.bufInfo.minInBufSize[1]);

    memcpy(hSd->minInBufSize,
           decStatus.bufInfo.minInBufSize, sizeof(hSd->minInBufSize));
    hSd->minNumInBufs = decStatus.bufInfo.minNumInBufs;
    memcpy(hSd->minOutBufSize,
           decStatus.bufInfo.minOutBufSize, sizeof(hSd->minOutBufSize));
    hSd->minNumOutBufs = decStatus.bufInfo.minNumOutBufs;

    hSd->hDecode = hDecode;

    return hSd;
}

/******************************************************************************
 * Sdec_delete
 ******************************************************************************/
Int Sdec_delete(Sdec_Handle hSd)
{
    if (hSd) {
        return cleanup(hSd);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Sdec_getVisaHandle
 ******************************************************************************/
SPHDEC_Handle Sdec_getVisaHandle(Sdec_Handle hSd)
{
    assert(hSd);

    return hSd->hDecode;
}

/******************************************************************************
 * Sdec_getOutBufSize
 ******************************************************************************/
Int32 Sdec_getOutBufSize(Sdec_Handle hSd)
{
    Int32 size = 0;

    assert(hSd);

#if 0 /* The g.711 decoder does not currently give sensible results */
    Int bufIdx;

    for (bufIdx = 0; bufIdx < hSd->minNumOutBufs; bufIdx++) {
        size += hSd->minOutBufSize[bufIdx];
    }
#else
    size = 160 * 2;
#endif

    return size;
}

/******************************************************************************
 * Sdec_getInBufSize
 ******************************************************************************/
Int32 Sdec_getInBufSize(Sdec_Handle hSd)
{
    Int32 size = 0;

    assert(hSd);

#if 0 /* The g.711 decoder does not currently give sensible results */
    Int bufIdx;

    for (bufIdx = 0; bufIdx < hSd->minNumInBufs; bufIdx++) {
        size += hSd->minInBufSize[bufIdx];
    }
#else
    size = 160;
#endif

    return size;
}
