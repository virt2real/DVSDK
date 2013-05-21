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
 * */
/*
 *  ======== idma3codec1_ti_priv.h ========
 *  Internal vendor specific (TI) interface header for IDMA3CODEC1
 *  algorithm. Only the implementation source files include
 *  this header; this header is not shipped as part of the
 *  algorithm.
 *
 *  This header contains declarations that are specific to
 *  this implementation and which do not need to be exposed
 *  in order for an application to use the IDMA3CODEC1 algorithm.
 */
#ifndef IDMA3CODEC1_TI_PRIV_
#define IDMA3CODEC1_TI_PRIV_


#include <ti/xdais/idma3.h>


typedef struct IDMA3CODEC1_TI_CtxtArgs {
    Int size;           
} IDMA3CODEC1_TI_CtxtArgs;

typedef struct IDMA3CODEC1_TI_Obj {
    IALG_Obj       alg;            /* MUST be first field of all XDAS algs */

    Int         *workBuf1;   /* on-chip scratch */
    Int         *workBuf2;   /* on-chip scratch */ 
    Int         srcLineLen;  /* Source line length (# of 8-bit elements) */
    Int         srcNumLines; /* Number of lines for source */
    Int         srcStride;   /* Stride between lines for source */
    Int         dstLineLen;  /* Destination line length (# of 8-bit elements) */
    Int         dstNumLines; /* Number of lines for destination */
    Int         dstStride;   /* Stride between lines for destination */
    IDMA3_Handle dmaHandle1D1D8B;  /* DMA logical channel for 1D to 1D xfers */
    IDMA3_Handle dmaHandle1D2D8B;  /* DMA logical channel for 1D to 2D xfers */
    IDMA3_Handle dmaHandle2D1D8B;  /* DMA logical channel for 2D to 1D xfers */
} IDMA3CODEC1_TI_Obj;

extern Int IDMA3CODEC1_TI_alloc(const IALG_Params *algParams, IALG_Fxns **pf,
    IALG_MemRec memTab[]);

extern Int IDMA3CODEC1_TI_free(IALG_Handle handle, IALG_MemRec memTab[]);

extern Int IDMA3CODEC1_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
        IALG_Handle parent, const IALG_Params *algParams);

#endif /* IDMA3CODEC1_TI_PRIV_ */
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.idma3codec1; 1, 0, 0,19; 12-1-2010 17:25:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

