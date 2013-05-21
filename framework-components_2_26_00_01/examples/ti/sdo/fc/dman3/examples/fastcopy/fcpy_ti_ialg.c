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
 *  ======== fcpy_ti_ialg.c ========
 *  FCPY Module - TI implementation of the FCPY module.
 *
 *  This file contains the implementation of the required IALG interface.
 */

#pragma CODE_SECTION(FCPY_TI_alloc, ".text:algAlloc")
#pragma CODE_SECTION(FCPY_TI_free, ".text:algFree")
#pragma CODE_SECTION(FCPY_TI_initObj, ".text:algInit")
#pragma CODE_SECTION(FCPY_TI_moved, ".text:algMoved")

#include <xdc/std.h>

#include <ti/xdais/ialg.h>

#include "fcpy_ti_priv.h"
#include "ifcpy.h"

#define OBJECT 0
#define WORKBUF1 1
#define WORKBUF2 2
#define NUMBUFS 3

#define ALIGN_FOR_CACHE 128  /* alignment on cache boundary */

/*
 *  ======== FCPY_TI_alloc ========
 *  Request memory.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int FCPY_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **parentFxns, IALG_MemRec memTab[])
{
    const IFCPY_Params *params = (Void *)algParams;

    if (params == NULL) {
        params = &IFCPY_PARAMS;  /* Use interface default params */
    }

    /* Request memory for FCPY object */
    memTab[OBJECT].size = sizeof (FCPY_TI_Obj);
    memTab[OBJECT].alignment = 0;    /* No alignment required */
    memTab[OBJECT].space = IALG_EXTERNAL;
    memTab[OBJECT].attrs = IALG_PERSIST;

    /* Request memory for working buffer 1 */
    memTab[WORKBUF1].size = (params->srcLineLen) * (params->srcNumLines) *
        sizeof (Char);
    memTab[WORKBUF1].alignment = ALIGN_FOR_CACHE;
    memTab[WORKBUF1].space = IALG_DARAM0;
    memTab[WORKBUF1].attrs = IALG_SCRATCH;

    /* Request memory for working buffer 2 */
    memTab[WORKBUF2].size = (params->srcLineLen) * (params->srcNumLines) *
        sizeof (Char);
    memTab[WORKBUF2].alignment = ALIGN_FOR_CACHE;
    memTab[WORKBUF2].space = IALG_DARAM0;
    memTab[WORKBUF2].attrs = IALG_SCRATCH;

    return (NUMBUFS);
}


/*
 *  ======== FCPY_TI_free ========
 *  Return a complete memTab structure.
 */
Int FCPY_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    FCPY_TI_Obj *fcpy = (Void *)handle;

    FCPY_TI_alloc(NULL, NULL, memTab);

    memTab[OBJECT].base = handle;

    memTab[WORKBUF1].base = fcpy->workBuf1;
    memTab[WORKBUF1].size = (fcpy->srcLineLen) * (fcpy->srcNumLines)
        * sizeof (Char);

    memTab[WORKBUF2].base = fcpy->workBuf2;
    memTab[WORKBUF2].size = (fcpy->srcLineLen) * (fcpy->srcNumLines)
        * sizeof (Char);

    return (NUMBUFS);
}

/*
 *  ======== FCPY_TI_initObj ========
 *  Initialize instance object.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Int FCPY_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle parent, const IALG_Params *algParams)
{
    FCPY_TI_Obj *fcpy = (Void *)handle;
    const IFCPY_Params *params = (Void *)algParams;

    if (params == NULL) {
        params = &IFCPY_PARAMS;  /* Use interface default params */
    }

    /* Set addresses of internal buffers */
    fcpy->workBuf1 = memTab[WORKBUF1].base;
    fcpy->workBuf2 = memTab[WORKBUF2].base;

    /* Configure the instance object */
    fcpy->srcLineLen  = params->srcLineLen;
    fcpy->srcStride   = params->srcStride;
    fcpy->srcNumLines = params->srcNumLines;
    fcpy->dstLineLen  = params->dstLineLen;
    fcpy->dstStride   = params->dstStride;
    fcpy->dstNumLines = params->dstNumLines;

    return (IALG_EOK);
}

/*
 *  ======== FCPY_TI_moved ========
 *  Re-initialize buffer ptrs to new location.
 */
/* ARGSUSED - this line tells the compiler not to warn about unused args. */
Void FCPY_TI_moved(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle parent, const IALG_Params *algParams)
{
    FCPY_TI_Obj *fcpy = (Void *)handle;

    fcpy->workBuf1 = memTab[WORKBUF1].base;
    fcpy->workBuf2 = memTab[WORKBUF2].base;
}

/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

