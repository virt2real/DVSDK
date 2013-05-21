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
 *  ======== idmacodec1_ti.c ========
 *  This file contains an implementation of the IIDMA3CODEC1_Fxns interface, for
 *  a "copy" algorithm that uses the example IDMA3 resource.
 *  This algorithm implements the IDMA3_Fxns to allow the resources it uses
 *  to be granted and used by the algorithm. The IDMA3_Fxns implementation
 *  is in its own source file, separate from this file.
 */
#include <xdc/std.h>
#include <string.h>

#include "iidma3codec1.h"

#include <ti/xdais/idma3.h>

#include "idma3codec1_ti.h"
#include "idma3codec1_ti_priv.h"

/* Algorithm uses ACPY3 for transfers */
#include <ti/sdo/fc/acpy3/acpy3.h>

extern IALG_Fxns IDMA3CODEC1_TI_IALG;

#define ALIGN_FOR_CACHE 128
#define OBJECT 0
#define WORKBUF1 1
#define WORKBUF2 2
#define NUMBUFS 3

#define IALGFXNS  \
    &IDMA3CODEC1_TI_IALG,    /* module ID */                         \
    NULL,                   /* activate */                          \
    IDMA3CODEC1_TI_alloc,    /* alloc */                             \
    NULL,                   /* control (NULL => no control ops) */  \
    NULL,                   /* deactivate */                        \
    IDMA3CODEC1_TI_free,     /* free */                              \
    IDMA3CODEC1_TI_initObj,  /* init */                              \
    NULL,                   /* moved */                             \
    NULL                    /* numAlloc (NULL => IALG_MAXMEMRECS) */


Int IDMA3CODEC1_TI_doCopy(IIDMA3CODEC1_Handle handle, unsigned int *src,
        unsigned int *dst, unsigned int size);

/*
 *  ======== IDMA3CODEC1_TI_CODECIDMA3 ========
 *  This structure defines TI's implementation of the IIDMA3CODEC1 interface
 *  for the IDMA3CODEC1_TI module.
 */
IIDMA3CODEC1_Fxns IDMA3CODEC1_TI_CODECIDMA3 = {    /* module_vendor_interface */
    {IALGFXNS},
    IDMA3CODEC1_TI_doCopy
};

/*
 *  ======== IDMA3CODEC1_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the IDMA3CODEC1_TI module.
 */
#ifdef xdc_target__isaCompatible_64P

asm("_IDMA3CODEC1_TI_IALG .set _IDMA3CODEC1_TI_CODECIDMA3");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run on non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns IDMA3CODEC1_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

IIDMA3CODEC1_Params IDMA3CODEC1_TI_PARAMS = {
    sizeof(IIDMA3CODEC1_Params),
        8,                       /* Source Frame length */
    8,                       /* Number of frames for source */
    0,                       /* Stride between frames for source */
    8,                       /* Destination Frame length */
    8,                       /* Number of frames for destination */
    0                        /* Stride between frames for destination */
};

/*
 *  ======== IDMA3CODEC1_TI_alloc ========
 */
/* ARGSUSED */
Int IDMA3CODEC1_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    const IIDMA3CODEC1_Params *params = (IIDMA3CODEC1_Params *)algParams;
    if (params == NULL) {
        params = &IDMA3CODEC1_TI_PARAMS;  /* Use interface default params */
    }

    /* Request memory for object */
    memTab[OBJECT].size = sizeof (IDMA3CODEC1_TI_Obj);
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
 *  ======== IDMA3CODEC1_TI_free ========
 */
/* ARGSUSED */
Int IDMA3CODEC1_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    IDMA3CODEC1_TI_Obj *alg = (IDMA3CODEC1_TI_Obj *)handle;
    IDMA3CODEC1_TI_alloc(NULL, NULL, memTab);

    memTab[OBJECT].base = handle;

    memTab[WORKBUF1].base = alg->workBuf1;
    memTab[WORKBUF1].size = (alg->srcLineLen) * (alg->srcNumLines)
        * sizeof (Char);

    memTab[WORKBUF2].base = alg->workBuf2;
    memTab[WORKBUF2].size = (alg->srcLineLen) * (alg->srcNumLines)
        * sizeof (Char);

    return (NUMBUFS);
}

/*
 *  ======== IDMA3CODEC1_TI_initObj ========
 */
/* ARGSUSED */
Int IDMA3CODEC1_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    IDMA3CODEC1_TI_Obj *algHandle = (IDMA3CODEC1_TI_Obj *)handle;
    const IIDMA3CODEC1_Params *params = (IIDMA3CODEC1_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &IDMA3CODEC1_TI_PARAMS;
    }

    /* Set addresses of internal buffers */
    algHandle->workBuf1 = memTab[WORKBUF1].base;
    algHandle->workBuf2 = memTab[WORKBUF2].base;

    /* Configure the instance object */
    algHandle->srcLineLen  = params->srcLineLen;
    algHandle->srcStride   = params->srcStride;
    algHandle->srcNumLines = params->srcNumLines;
    algHandle->dstLineLen  = params->dstLineLen;
    algHandle->dstStride   = params->dstStride;
    algHandle->dstNumLines = params->dstNumLines;

    return (IALG_EOK);
}

/* ARGSUSED */
Int IDMA3CODEC1_TI_doCopy(IIDMA3CODEC1_Handle handle, unsigned int *src,
            unsigned int *dst, unsigned int size)
{
    /* Extract channel granted to this alg */ 
    IDMA3CODEC1_TI_Obj * algHandle = (IDMA3CODEC1_TI_Obj *)handle;  

    ACPY3_Params params;

    /* 
     * Activate Channel  scratch DMA channels. 
     */
    ACPY3_activate(algHandle->dmaHandle1D1D8B);
    ACPY3_activate(algHandle->dmaHandle1D2D8B);
    ACPY3_activate(algHandle->dmaHandle2D1D8B);

    /* Configure the logical channel */ 
    params.transferType = ACPY3_1D1D;

    params.srcAddr = (void *)(algHandle->workBuf1);
    params.dstAddr = (void *)(algHandle->workBuf2);
    params.elementSize = (Uns)(algHandle->srcLineLen) * (algHandle->srcNumLines);
    params.numElements = 1;
    params.numFrames = 1;
    params.srcElementIndex = 0;
    params.dstElementIndex = 0;
    params.srcFrameIndex = 0;
    params.dstFrameIndex = 0;
    params.waitId = 0;
        
    /* Configure logical dma channel */
    ACPY3_configure(algHandle->dmaHandle1D1D8B, &params, 0);

    /* Configure the logical channel */

    params.transferType = ACPY3_2D1D;

    params.srcAddr = (void *)src;
    params.dstAddr = (void *)(algHandle->workBuf1);
    params.elementSize = (Uns)(algHandle->srcLineLen);
    params.numElements = algHandle->srcNumLines;
    params.numFrames = 1;
    params.srcElementIndex = algHandle->srcStride + algHandle->srcLineLen ;
    params.dstElementIndex = algHandle->srcLineLen;
    params.srcFrameIndex = 0;
    params.dstFrameIndex = 0;
    params.waitId = 0;


    //params.numFrames = algHandle->srcNumLines;        
    //params.srcFrameIndex = algHandle->srcStride; 
    //params.dstFrameIndex = 0;     
    
    /* Configure logical dma channel */
    ACPY3_configure(algHandle->dmaHandle2D1D8B, &params, 0);

    /* Configure the logical channel */
    params.transferType = ACPY3_1D2D;
    //params.elemSize = IDMA3_ELEM8;
    //params.numFrames = 0;     
    //params.srcFrameIndex = 0;
    //params.dstFrameIndex = 0;
           
    params.srcAddr = (void *)(algHandle->workBuf2);
    params.dstAddr = (void *)dst;
    params.elementSize = (Uns)(algHandle->dstLineLen);
//  params.numElements = algHandle->dstNumLines;
    params.numFrames = 1;
    params.srcElementIndex = algHandle->dstLineLen ;
//  params.dstElementIndex = algHandle->dstLineLen + algHandle->dstStride;


    /* Configure logical dma channel */
    ACPY3_configure(algHandle->dmaHandle1D2D8B, &params, 0);
    ACPY3_fastConfigure16b(algHandle->dmaHandle1D2D8B, 
            ACPY3_PARAMFIELD_NUMELEMENTS, 
            algHandle->dstNumLines, 0);

    ACPY3_fastConfigure16b(algHandle->dmaHandle1D2D8B, 
            ACPY3_PARAMFIELD_ELEMENTINDEX_DST, 
            algHandle->dstLineLen + algHandle->dstStride, 0);
 
    //ACPY2_setNumFrames(algHandle->dmaHandle1D2D8B, algHandle->dstNumLines);
    //ACPY2_setDstFrameIndex(algHandle->dmaHandle1D2D8B, algHandle->dstStride);
    
    /* Use DMA to algHandle input buffer into working buffer */
    ACPY3_start(algHandle->dmaHandle2D1D8B);
    //ACPY2_start(algHandle->dmaHandle2D1D8B, (Void *)src, 
    //    (Void *)(algHandle->workBuf1),
    //    (Uns)(algHandle->srcLineLen));

    /* Check that dma transfer has completed before finishing "processing" */
    while (!ACPY3_complete(algHandle->dmaHandle2D1D8B)) {
        ;
    };

    /* Use the DMA to copy data from working buffer 1 to working buffer 2 */ 
    ACPY3_start(algHandle->dmaHandle1D1D8B);
    //ACPY2_start(algHandle->dmaHandle1D1D8B, (Void *)(algHandle->workBuf1),
    ///   (Void *)(algHandle->workBuf2), 
    //    (Uns)((algHandle->srcLineLen) * (algHandle->srcNumLines)));


    /* wait for transfer to finish  */              
    ACPY3_wait(algHandle->dmaHandle1D1D8B);

    /* Quickly configure NumFrames and FrameIndex values for dmaHandle1D2D8B */
    //ACPY2_setNumFrames(algHandle->dmaHandle1D2D8B, algHandle->dstNumLines);
    //ACPY2_setDstFrameIndex(algHandle->dmaHandle1D2D8B, algHandle->dstStride);

    /* Use the DMA to copy data from working buffer 2 to output buffer */ 
    ACPY3_start(algHandle->dmaHandle1D2D8B);
    //ACPY2_start(algHandle->dmaHandle1D2D8B, (Void *)(algHandle->workBuf2),
    //    (Void *)dst, (Uns)(algHandle->dstLineLen));
    
    /* wait for all transfers to complete before returning to the client */
    ACPY3_wait(algHandle->dmaHandle1D2D8B);

    /* 
     * DeActivate Channel  scratch DMA channels. 
     */
    ACPY3_deactivate(algHandle->dmaHandle1D1D8B);
    ACPY3_deactivate(algHandle->dmaHandle1D2D8B);
    ACPY3_deactivate(algHandle->dmaHandle2D1D8B);
    return (IALG_EOK);
}
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.idma3codec1; 1, 0, 0,19; 12-1-2010 17:25:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

