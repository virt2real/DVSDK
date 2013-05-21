/* 
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
 * 
 */
/*
 *  ======== auddec1_ti.c ========
 *  This file contains an implementation of the IAUDDEC1_Fxns interface, for
 *  an audio decoder "copy" algorithm that uses the example BUFRES resource.
 *  This algorithm implements the IRES_Fxns to allow the resources it uses
 *  to be granted and used by the algorithm. The IRES_Fxns implementation
 *  is in its own source file, separate from this file.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/iauddec1.h>

#include <ti/xdais/ires.h>

/* This define gets rid of a warnign associated with the un-used static
   variable BUFRES_PROTOCOLVERSION from the header bufres.h */
#define ti_sdo_fc_ires_NOPROTOCOLREV

#include "auddec1_ti.h"
#include "auddec1_ti_priv.h"

/* TODO, need to autogenerate this */
#define AUDDEC1_IRES_VERSIONSTRING "1.00.00.0"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define BUFRESSIZE 0x100
#define BUFRESALIGN 0x20

#define IALGFXNS  \
    &AUDDEC1_TI_IALG,      /* module ID */                         \
    AUDDEC1_TI_activate,   /* activate */                          \
    AUDDEC1_TI_alloc,      /* alloc */                             \
    NULL,                  /* control (NULL => no control ops) */  \
    AUDDEC1_TI_deactivate, /* deactivate */                        \
    AUDDEC1_TI_free,       /* free */                              \
    AUDDEC1_TI_initObj,    /* init */                              \
    NULL,                  /* moved */                             \
    NULL                   /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== AUDDEC1_TI_AUDDECIRES ========
 *  This structure defines TI's implementation of the IAUDDEC1 interface
 *  for the AUDDEC1_TI module.
 */
IAUDDEC1_Fxns AUDDEC1_TI_AUDDECIRES = {    /* module_vendor_interface */
    {IALGFXNS},
    AUDDEC1_TI_process,
    AUDDEC1_TI_control,
};

/*
 *  ======== AUDDEC1_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the AUDDEC1_TI module.
 */
#ifdef __TI_COMPILER_VERSION__

asm("_AUDDEC1_TI_IALG .set _AUDDEC1_TI_AUDDECIRES");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run on non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns AUDDEC1_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IAUDDEC1_Params AUDDEC1_TI_PARAMS = {
    sizeof(IAUDDEC1_Params),
    8,                              /* outputPCMWidth */
    IAUDIO_BLOCK,                   /* pcmFormat */
    XDM_BYTE                        /* dataEndianness */
};

/*
 *  ======== AUDDEC1_TI_activate ========
 */
/* ARGSUSED Tells the compiler not to warn about unused arguments */
Void AUDDEC1_TI_activate(IALG_Handle handle)
{
}

/*
 *  ======== AUDDEC1_TI_alloc ========
 */
/* ARGSUSED Tells the compiler not to warn about unused arguments */
Int AUDDEC1_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(AUDDEC1_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== AUDDEC1_TI_deactivate ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Void AUDDEC1_TI_deactivate(IALG_Handle handle)
{
}

/*
 *  ======== AUDDEC1_TI_free ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDEC1_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    /*
     * Because our internal object size doesn't depend on create
     * params, we can just leverage the algAlloc() call with default
     * (NULL) create params.
     */
    return (AUDDEC1_TI_alloc(NULL, NULL, memTab));
}


/*
 *  ======== AUDDEC1_TI_initObj ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
Int AUDDEC1_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    AUDDEC1_TI_Obj *obj = (AUDDEC1_TI_Obj *)handle;
    const IAUDDEC1_Params *params = (IAUDDEC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &AUDDEC1_TI_PARAMS;
    }

    obj->outputPCMWidth = params->outputPCMWidth;
    obj->pcmFormat = params->pcmFormat;
    obj->dataEndianness = params->dataEndianness;

    /* Initialize obj->args with values for requesting resource buffer */
    obj->args.iresArgs.size = sizeof(BUFRES_Args);
    obj->args.length = BUFRESSIZE;
    obj->args.align = BUFRESALIGN;

    return (IALG_EOK);
}


/*
 *  ======== AUDDEC1_TI_process ========
 */
/* ARGSUSED - this line tells the TI compiler not to warn about unused args. */
XDAS_Int32 AUDDEC1_TI_process(IAUDDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM1_BufDesc *outBufs, IAUDDEC1_InArgs *inArgs, IAUDDEC1_OutArgs *outArgs)
{
    AUDDEC1_TI_Obj *obj = (AUDDEC1_TI_Obj *)handle;
    BUFRES_Handle    bufres = obj->bufres;
    Int              i;
    XDAS_Int32       numInBytes;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
            (outArgs->size != sizeof(*outArgs))) {
        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IAUDDEC1_EUNSUPPORTED);
    }

    /* validate that there's at least a single inBuf and outBuf */
    if ((inBufs->numBufs < 1) || (outBufs->numBufs < 1)) {
        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IAUDDEC1_EFAIL);
    }

    numInBytes = inArgs->numBytes;

    /*
     * Sanity check that inBufs->bufSizes[0] is really capable of holding
     * numInBytes bytes of data, and that outBufs->bufSizes[0]
     * can hold the 'encoded' data.
     */
    if ((numInBytes > inBufs->descs[0].bufSize) ||
        (numInBytes > outBufs->descs[0].bufSize)) {

        outArgs->extendedError = XDM_UNSUPPORTEDPARAM;

        return (IAUDDEC1_EFAIL);
    }

    /* Do something 'interesting' with the buffer resource */
    for (i = 0; i < bufres->length / sizeof(Int); i++) {
        ((Int *)(bufres->base))[i] = i;
    }

    /* everything looks good, do the 'encode', set outArgs and return */
    memcpy(outBufs->descs[0].buf, inBufs->descs[0].buf, numInBytes);

    /* report _how_ we accessed the 2 data buffers */
    XDM_CLEARACCESSMODE_WRITE(inBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_READ(inBufs->descs[0].accessMask);

    XDM_CLEARACCESSMODE_READ(outBufs->descs[0].accessMask);
    XDM_SETACCESSMODE_WRITE(outBufs->descs[0].accessMask);

    /* outArgs->bytesGenerated reports the total number of bytes encoded */
    outArgs->bytesConsumed = numInBytes;

    /* Fill out the rest of the outArgs struct */
    outArgs->extendedError = 0;
    outArgs->numSamples = outArgs->bytesConsumed;  /* a sample == a byte */
    outArgs->channelMode = IAUDIO_2_0;  /* TODO */
    outArgs->lfeFlag = XDAS_FALSE;  /* TODO */
    outArgs->dualMonoMode = 0;  /* TODO */
    outArgs->sampleRate = 0;  /* TODO */

    return (IAUDDEC1_EOK);
}


/*
 *  ======== AUDDEC1_TI_control ========
 */
XDAS_Int32 AUDDEC1_TI_control(IAUDDEC1_Handle handle, IAUDDEC1_Cmd id,
    IAUDDEC1_DynamicParams *dynParams, IAUDDEC1_Status *status)
{
    XDAS_Int32 retVal;
    AUDDEC1_TI_Obj *obj = (AUDDEC1_TI_Obj *)handle;

    /* validate arguments - this codec only supports "base" xDM. */
    if ((dynParams->size != sizeof(*dynParams)) ||
        (status->size != sizeof(*status))) {

        return (IAUDDEC1_EUNSUPPORTED);
    }

    /* initialize for the general case where we don't access the data buffer */
    XDM_CLEARACCESSMODE_READ(status->data.accessMask);
    XDM_CLEARACCESSMODE_WRITE(status->data.accessMask);

    switch (id) {
        case XDM_GETSTATUS:
        case XDM_GETBUFINFO:
            status->extendedError = 0;
            status->validFlag = XDAS_TRUE;
            status->lfeFlag = XDAS_FALSE;  /* TODO */
            status->bitRate = 0;  /* TODO */
            status->sampleRate = 0;  /* TODO */
            status->channelMode = IAUDIO_2_0;  /* TODO */
            status->pcmFormat = obj->pcmFormat;
            status->numSamples = 0;  /* TODO */
            status->outputBitsPerSample = 8;  /* a sample == a byte */
            status->dualMonoMode = 0;  /* TODO */

            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = IAUDDEC1_EOK;
            break;

        case XDM_SETPARAMS:
            retVal = IAUDDEC1_EOK;
            break;

        case XDM_SETDEFAULT:
            obj->outputPCMWidth = AUDDEC1_TI_PARAMS.outputPCMWidth;
            obj->pcmFormat = AUDDEC1_TI_PARAMS.pcmFormat;
            obj->dataEndianness = AUDDEC1_TI_PARAMS.dataEndianness;

            retVal = IAUDDEC1_EOK;
            break;

        case XDM_RESET:
        case XDM_FLUSH:
            retVal = IAUDDEC1_EOK;
            break;

        case XDM_GETVERSION:
            if ((status->data.buf != NULL) &&
                (status->data.bufSize >= strlen(AUDDEC1_IRES_VERSIONSTRING))) {
                strncpy((char *)status->data.buf, AUDDEC1_IRES_VERSIONSTRING,
                    strlen(AUDDEC1_IRES_VERSIONSTRING));

                /* null terminate the string */
                status->data.buf[strlen(AUDDEC1_IRES_VERSIONSTRING)] = '\0';

                /* strncpy wrote to the data buffer */
                XDM_SETACCESSMODE_WRITE(status->data.accessMask);

                retVal = IAUDDEC1_EOK;
            }
            else {
                retVal = IAUDDEC1_EFAIL;
            }

            break;

        default:
            /* unsupported cmd */
            retVal = IAUDDEC1_EUNSUPPORTED;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.auddec1; 1, 0, 0,175; 12-1-2010 17:25:04; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

