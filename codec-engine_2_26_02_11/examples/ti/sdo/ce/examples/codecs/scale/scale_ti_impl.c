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
 *  ======== scale.c ========
 *  "Scale" algorithm.
 *
 *  This file contains an implementation of the IALG interface
 *  required by XDAS.
 */
#include <xdc/std.h>
#include <string.h>


#include "iscale.h"
#include "scale_ti.h"
#include "scale_ti_priv.h"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

extern IALG_Fxns SCALE_TI_IALG;

#define IALGFXNS  \
    &SCALE_TI_IALG,     /* module ID */                         \
    NULL,               /* activate */                          \
    SCALE_TI_alloc,     /* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    SCALE_TI_free,      /* free */                              \
    SCALE_TI_initObj,   /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== SCALE_TI_ISCALE ========
 *  This structure defines TI's implementation of the ISCALE interface
 *  for the SCALE_TI module.
 */
ISCALE_Fxns SCALE_TI_SCALE = {
    {IALGFXNS},
    SCALE_TI_process,
    SCALE_TI_control,
};

/*
 *  ======== SCALE_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the SCALECOPY_TI module.
 */
#ifdef _TI_

asm("_SCALE_TI_IALG .set _SCALE_TI_SCALE");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns SCALE_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

/*
 *  ======== SCALE_TI_alloc ========
 */
Int SCALE_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(SCALE_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== SCALE_TI_free ========
 */
Int SCALE_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    SCALE_TI_alloc(NULL, NULL, memTab);
    return (1);
}

/*
 *  ======== SCALE_TI_initObj ========
 */
Int SCALE_TI_initObj(IALG_Handle handle,
    const IALG_MemRec memTab[], IALG_Handle p,
    const IALG_Params *algParams)
{
    SCALE_TI_Obj *inst = (SCALE_TI_Obj *)handle;
    ISCALE_Params *params = (ISCALE_Params *)algParams;

    if (params == NULL) {
        inst->scaleFactor = 1; /* default scale is 1 */
    }
    else {
        inst->scaleFactor = params->initialScaleFactor;
    }

    return (IALG_EOK);
}

/*
 *  ======== SCALE_TI_process ========
 */
XDAS_Int32 SCALE_TI_process(ISCALE_Handle handle, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs)
{
    XDAS_Int32 i;
    SCALE_TI_Obj *inst = (SCALE_TI_Obj *)handle;

    for (i = 0; i < inArgs->inBufValidBytes; i++) {
        outBuf[i] = inBuf[i] * inst->scaleFactor;
    }

    /* Fill outArgs */
    outArgs->outBufValidBytes = i;

    return (ISCALE_EOK);
}

/*
 *  ======== SCALE_TI_control ========
 */
XDAS_Int32 SCALE_TI_control(ISCALE_Handle handle, ISCALE_Cmd id,
    ISCALE_DynamicParams *params)
{
    XDAS_Int32 retVal;
    SCALE_TI_Obj *inst = (SCALE_TI_Obj *)handle;

    switch (id) {
        case ISCALE_SETPARAMS:
            inst->scaleFactor = params->scaleFactor;

            retVal = ISCALE_EOK;

            break;

        default:
            /* unsupported cmd */
            retVal = ISCALE_EFAIL;

            break;
    }

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1, 0, 0,261; 12-2-2010 21:22:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

