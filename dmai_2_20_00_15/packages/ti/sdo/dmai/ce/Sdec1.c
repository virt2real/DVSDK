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
#include <ti/sdo/ce/speech1/sphdec1.h>
#include <ti/xdais/dm/ispeech1_pcm.h>

#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Buffer.h>
#include <ti/sdo/dmai/ce/Sdec1.h>

#define MODULE_NAME     "Sdec1"

typedef struct Sdec1_Object {
    SPHDEC1_Handle           hDecode;
    Int32                   minNumInBufs;
    Int32                   minInBufSize[XDM_MAX_IO_BUFFERS];
    Int32                   minNumOutBufs;
    Int32                   minOutBufSize[XDM_MAX_IO_BUFFERS];
} Sdec1_Object;

const SPHDEC1_Params Sdec1_Params_DEFAULT = {
    sizeof(SPHDEC1_Params),
    ISPEECH1_PCM_COMPAND_ALAW,
    0,
    0,
    0,
    0,
    NULL,
};

const SPHDEC1_DynamicParams Sdec1_DynamicParams_DEFAULT = {
    sizeof(SPHDEC1_DynamicParams),
    0,
};
  
/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Sdec1_Handle hSd)
{
    if (hSd->hDecode) {
        SPHDEC1_delete(hSd->hDecode);
    }

    free(hSd);

    return Dmai_EOK;
}

/******************************************************************************
 * Sdec1_process
 ******************************************************************************/
Int Sdec1_process(Sdec1_Handle hSd, Buffer_Handle hInBuf, Buffer_Handle hOutBuf)
{
    XDM1_SingleBufDesc       inBufDesc;
    XDM1_SingleBufDesc       outBufDesc;
    XDAS_Int32               status;
    SPHDEC1_InArgs           inArgs;
    SPHDEC1_OutArgs          outArgs;
    XDAS_Int8               *inPtr;
    XDAS_Int8               *outPtr;

    assert(hSd);
    assert(hInBuf);
    assert(hOutBuf);
    assert(Buffer_getUserPtr(hInBuf));
    assert(Buffer_getUserPtr(hOutBuf));
    assert(Buffer_getNumBytesUsed(hInBuf));
    assert(Buffer_getSize(hOutBuf));

    inPtr = Buffer_getUserPtr(hInBuf);
    outPtr = Buffer_getUserPtr(hOutBuf);

    inBufDesc.buf              = inPtr;
    inBufDesc.bufSize          = Buffer_getNumBytesUsed(hInBuf);

    outBufDesc.buf             = outPtr;
    outBufDesc.bufSize         = Buffer_getSize(hOutBuf);

    inArgs.size                = sizeof(SPHDEC1_InArgs);
    inArgs.frameType           = ISPHDEC1_FTYPE_SPEECHGOOD;

    outArgs.size               = sizeof(SPHDEC1_OutArgs);

    /* We never use the inArgs.data fields, so initialize them to NULL. */
    inArgs.data.buf = (XDAS_Int8 *) NULL;
    inArgs.data.bufSize = 0L;

    /* Decode the speech buffer */
    status = SPHDEC1_process(hSd->hDecode, &inBufDesc, &outBufDesc, &inArgs,
                            &outArgs);

    Dmai_dbg1("SPHDEC1_process() ret %d \n", status);

    if (status != SPHDEC1_EOK) {
        if (XDM_ISFATALERROR(outArgs.extendedError)) {
            Dmai_err2("SPHDEC1_process() failed with error (%d ext: 0x%x)\n",
                      (Int)status, (Uns)outArgs.extendedError);
            return Dmai_EFAIL;
        }
        else {
            Dmai_dbg1("SPHDEC1_process() non-fatal error 0x%x\n", 
                         (Uns)outArgs.extendedError);
            return Dmai_EBITERROR;
        }
    }

    /* The codec will fill in how many bytes got used */
    Buffer_setNumBytesUsed(hOutBuf, Sdec1_getOutBufSize(hSd));

    return Dmai_EOK;
}

/******************************************************************************
 * Sdec1_create
 ******************************************************************************/
Sdec1_Handle Sdec1_create(Engine_Handle hEngine, Char *codecName,
                        SPHDEC1_Params *params, SPHDEC1_DynamicParams *dynParams)
{
    Sdec1_Handle         hSd;
    SPHDEC1_Handle       hDecode;
    SPHDEC1_Status       decStatus;
    XDAS_Int32           status;

    if (hEngine == NULL || codecName == NULL ||
        params == NULL || dynParams == NULL) {
        Dmai_err0("Cannot pass null for engine, codec name, params or "
                  "dynamic params\n");
        return NULL;
    }

    /* Allocate space for the object */
    hSd = (Sdec1_Handle)calloc(1, sizeof(Sdec1_Object));

    if (hSd == NULL) {
        Dmai_err0("Failed to allocate space for Sdec1 Object\n");
        return NULL;
    }

    /* Create speech1 decoder */
    hDecode = SPHDEC1_create(hEngine, codecName, params);

    if (hDecode == NULL) {
        Dmai_err0("Failed to create speech1 decoder\n");
        cleanup(hSd);
        return NULL;
    }

    Dmai_dbg1("Speech decoder instance of %s created\n", codecName);

    /* Set dynamic parameters */
    decStatus.size = sizeof(SPHDEC1_Status);
    decStatus.data.buf = (XDAS_Int8 *)NULL;
    decStatus.data.bufSize = 0L;

    status = SPHDEC1_control(hDecode, XDM_SETPARAMS, dynParams, &decStatus);

    if (status != SPHDEC1_EOK) {
        Dmai_err1("XDM_SETPARAMS failed, status=%d\n", status);
        cleanup(hSd);
        return NULL;
    }

    /* Get buffer information from video decoder */
    status = SPHDEC1_control(hDecode, XDM_GETBUFINFO, dynParams,
                             &decStatus);

    if (status != SPHDEC1_EOK) {
        Dmai_err0("XDM_GETBUFINFO control failed\n");
        cleanup(hSd);
        return NULL;
    }

    Dmai_dbg2("Speech decoder requires min buffer sizes in %u and out %u\n",
              (Uns)decStatus.bufInfo.minInBufSize[0],
              (Uns)decStatus.bufInfo.minOutBufSize[0]);

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
 * Sdec1_delete
 ******************************************************************************/
Int Sdec1_delete(Sdec1_Handle hSd)
{
    if (hSd) {
        return cleanup(hSd);
    }

    return Dmai_EOK;
}

/******************************************************************************
 * Sdec1_getVisaHandle
 ******************************************************************************/
SPHDEC1_Handle Sdec1_getVisaHandle(Sdec1_Handle hSd)
{
    assert(hSd);

    return hSd->hDecode;
}

/******************************************************************************
 * Sdec1_getOutBufSize
 ******************************************************************************/
Int32 Sdec1_getOutBufSize(Sdec1_Handle hSd)
{
    Int32 size = 0;

    assert(hSd);

    size = hSd->minOutBufSize[0];

    return size;
}

/******************************************************************************
 * Sdec1_getInBufSize
 ******************************************************************************/
Int32 Sdec1_getInBufSize(Sdec1_Handle hSd)
{
    Int32 size = 0;

    assert(hSd);

    size = hSd->minInBufSize[0];

    return size;
}
