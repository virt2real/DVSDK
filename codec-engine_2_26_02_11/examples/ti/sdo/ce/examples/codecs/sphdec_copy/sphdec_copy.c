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
 *  ======== sphdec_copy.c ========
 *  Speech Decoder "copy" algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by XDAS.
 */
#include <xdc/std.h>
#include <string.h>

#include <ti/xdais/dm/isphdec.h>
#include <ti/sdo/ce/trace/gt.h>

#include "sphdec_copy_ti.h"
#include "sphdec_copy_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns SPHDECCOPY_TI_IALG;

#define IALGFXNS  \
    &SPHDECCOPY_TI_IALG,/* module ID */                         \
    NULL,               /* activate */                          \
    SPHDECCOPY_TI_alloc,/* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    SPHDECCOPY_TI_free, /* free */                              \
    SPHDECCOPY_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SPHDECCOPY_TI_ISPHDEC ========
 *  This structure defines TI's implementation of the ISPHDEC interface
 *  for the SPHDECCOPY_TI module.
 */
ISPHDEC_Fxns SPHDECCOPY_TI_SPHDECCOPY = {    /* module_vendor_interface */
    {IALGFXNS},
    SPHDECCOPY_TI_process,
    SPHDECCOPY_TI_control,
};

/*
 *  ======== SPHDEC_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SPHDECCOPY_TI module.
 */
#ifdef _TI_

asm("_SPHDECCOPY_TI_IALG .set _SPHDECCOPY_TI_SPHDECCOPY");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SPHDECCOPY_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/* tracing information */
#define GTNAME "ti.sdo.ce.examples.codecs.sphdec_copy"
static GT_Mask curTrace = {NULL,NULL};

/*
 *  ======== SPHDECCOPY_TI_alloc ========
 */
Int SPHDECCOPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    if (curTrace.modName == NULL) {   /* initialize GT (tracing) */
        GT_create(&curTrace, GTNAME);
    }

    GT_3trace(curTrace, GT_ENTER, "SPHDECCOPY_TI_alloc(0x%lx, 0x%lx, 0x%lx)\n",
        algParams, pf, memTab);

    /* Request memory for my object */
    memTab[0].size = sizeof(SPHDECCOPY_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}


/*
 *  ======== SPHDECCOPY_TI_free ========
 */
Int SPHDECCOPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    GT_2trace(curTrace, GT_ENTER, "SPHDECCOPY_TI_free(0x%lx, 0x%lx)\n",
        handle, memTab);

    SPHDECCOPY_TI_alloc(NULL, NULL, memTab);
    return (1);
}


/*
 *  ======== SPHDECCOPY_TI_initObj ========
 */
Int SPHDECCOPY_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    GT_4trace(curTrace, GT_ENTER,
        "SPHDECCOPY_TI_initObj(0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        handle, memTab, p, algParams);

    return (IALG_EOK);
}


/*
 *  ======== SPHDECCOPY_TI_process ========
 */
XDAS_Int32 SPHDECCOPY_TI_process(ISPHDEC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHDEC_InArgs *inArgs, ISPHDEC_OutArgs *outArgs)
{
    XDAS_Int32 curBuf;
    XDAS_Int32 minSamples;

    GT_5trace(curTrace, GT_ENTER,
        "SPHDECCOPY_TI_process(0x%lx, 0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        h, inBufs, outBufs, inArgs, outArgs);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((inArgs->size != sizeof(*inArgs)) ||
        (outArgs->size != sizeof(*outArgs))) {

        GT_2trace(curTrace, GT_ENTER, "SPHDECCOPY_TI_process, unsupported size "
            "(0x%lx, 0x%lx)\n", inArgs->size, outArgs->size);

        return (ISPHDEC_EFAIL);
    }

    /*
     * A couple constraints for this simple "copy" codec:
     *    - Speech decoding presumes a single input buffer, so only one input
     *      buffer will be decoded, regardless of inBufs->numBufs.
     *    - Given a different size of an input and output buffers, only
     *      decode (i.e., copy) the lesser of the sizes.
     */

    for (curBuf = 0; (curBuf < inBufs->numBufs) &&
        (curBuf < outBufs->numBufs); curBuf++) {

        /* there's an available in and out buffer, how many samples? */
        minSamples = inBufs->bufSizes[curBuf] < outBufs->bufSizes[curBuf] ?
            inBufs->bufSizes[curBuf] : outBufs->bufSizes[curBuf];

        /* process the data: read input, produce output */
        memcpy(outBufs->bufs[curBuf], inBufs->bufs[curBuf], minSamples);

        GT_1trace(curTrace, GT_2CLASS, "SPHDECCOPY_TI_process> "
            "Processed %d bytes.\n", minSamples);
    }

    /* Fill out the rest of the outArgs struct */
    outArgs->mode = ISPEECH_VOICED;    /* TODO */

    return (ISPHDEC_EOK);
}


/*
 *  ======== SPHDECCOPY_TI_control ========
 */
XDAS_Int32 SPHDECCOPY_TI_control(ISPHDEC_Handle handle, ISPHDEC_Cmd id,
    ISPHDEC_DynamicParams *params, ISPHDEC_Status *status)
{
    XDAS_Int32 retVal;

    GT_4trace(curTrace, GT_ENTER,
        "SPHDECCOPY_TI_control(0x%lx, 0x%lx, 0x%lx, 0x%lx)\n",
        handle, id, params, status);

    /* validate arguments - this codec only supports "base" xDM. */
    if ((params->size != sizeof(*params)) ||
        (status->size != sizeof(*status))) {

        GT_2trace(curTrace, GT_ENTER, "SPHDECCOPY_TI_control, unsupported size "
            "(0x%lx, 0x%lx)\n", params->size, status->size);

        return (ISPHDEC_EFAIL);
    }

    switch (id) {
        case XDM_GETSTATUS:
            status->extendedError = 0;
            status->postFilter = 0;  /* TODO */
            status->dataMode = 0; /* TODO */

            /* Note, intentionally no break here so we fill in bufInfo, too */

        case XDM_GETBUFINFO:
            status->bufInfo.minNumInBufs = MININBUFS;
            status->bufInfo.minNumOutBufs = MINOUTBUFS;
            status->bufInfo.minInBufSize[0] = MININBUFSIZE;
            status->bufInfo.minOutBufSize[0] = MINOUTBUFSIZE;

            retVal = ISPHDEC_EOK;

            break;

        case XDM_SETPARAMS:
        case XDM_SETDEFAULT:
        case XDM_RESET:
        case XDM_FLUSH:
            /* TODO - for now just return success. */

            retVal = ISPHDEC_EOK;
            break;

        default:
            /* unsupported cmd */
            retVal = ISPHDEC_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.sphdec_copy; 1, 0, 0,262; 12-2-2010 21:22:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

