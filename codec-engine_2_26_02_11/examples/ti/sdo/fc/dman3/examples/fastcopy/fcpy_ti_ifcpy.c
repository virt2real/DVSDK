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
 *  ======== fcpy_ti_ifcpy.c ========
 *  FCPY Module - TI implementation of a FCPY algorithm
 *
 *  This file contains the implementation of the IFCPY abstract interface. 
 */

#pragma CODE_SECTION(FCPY_TI_doCopy, ".text:doCopy")
#pragma CODE_SECTION(FCPY_TI_control, ".text:control")

#include <xdc/std.h>

#include <ti/xdais/xdas.h>
#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

#include "ifcpy.h"
#include "fcpy_ti_priv.h"
#include "fcpy_ti.h"


/*
 *  ======== FCPY_TI_doCopy ========
 */
Void FCPY_TI_doCopy(IFCPY_Handle handle, Void * in, Void * out)
{
    FCPY_TI_Obj *fcpy = (Void *)handle;
    ACPY3_Params params;

    /* 
     * Activate Channel  scratch DMA channels. 
     */
    ACPY3_activate(fcpy->dmaHandle1D1D8B);
    ACPY3_activate(fcpy->dmaHandle1D2D8B);
    ACPY3_activate(fcpy->dmaHandle2D1D8B);

    /* Configure the logical channel */ 
    params.transferType = ACPY3_1D1D;

    params.srcAddr = (void *)(fcpy->workBuf1);
    params.dstAddr = (void *)(fcpy->workBuf2);
    params.elementSize = (Uns)(fcpy->srcLineLen) * (fcpy->srcNumLines);
    params.numElements = 1;
    params.numFrames = 1;
    params.srcElementIndex = 0;
    params.dstElementIndex = 0;
    params.srcFrameIndex = 0;
    params.dstFrameIndex = 0;
    params.waitId = 0;
        
    /* Configure logical dma channel */
    ACPY3_configure(fcpy->dmaHandle1D1D8B, &params, 0);

    /* Configure the logical channel */

    params.transferType = ACPY3_2D1D;

    params.srcAddr = (void *)in;
    params.dstAddr = (void *)(fcpy->workBuf1);
    params.elementSize = (Uns)(fcpy->srcLineLen);
    params.numElements = fcpy->srcNumLines;
    params.numFrames = 1;
    params.srcElementIndex = fcpy->srcStride + fcpy->srcLineLen ;
    params.dstElementIndex = fcpy->srcLineLen;
    params.srcFrameIndex = 0;
    params.dstFrameIndex = 0;
    params.waitId = 0;


    //params.numFrames = fcpy->srcNumLines;        
    //params.srcFrameIndex = fcpy->srcStride; 
    //params.dstFrameIndex = 0;     
    
    /* Configure logical dma channel */
    ACPY3_configure(fcpy->dmaHandle2D1D8B, &params, 0);

    /* Configure the logical channel */
    params.transferType = ACPY3_1D2D;
    //params.elemSize = IDMA3_ELEM8;
    //params.numFrames = 0;     
    //params.srcFrameIndex = 0;
    //params.dstFrameIndex = 0;
           
    params.srcAddr = (void *)(fcpy->workBuf2);
    params.dstAddr = (void *)out;
    params.elementSize = (Uns)(fcpy->dstLineLen);
//  params.numElements = fcpy->dstNumLines;
    params.numFrames = 1;
    params.srcElementIndex = fcpy->dstLineLen ;
//  params.dstElementIndex = fcpy->dstLineLen + fcpy->dstStride;


    /* Configure logical dma channel */
    ACPY3_configure(fcpy->dmaHandle1D2D8B, &params, 0);
    ACPY3_fastConfigure16b(fcpy->dmaHandle1D2D8B, 
            ACPY3_PARAMFIELD_NUMELEMENTS, 
            fcpy->dstNumLines, 0);

    ACPY3_fastConfigure16b(fcpy->dmaHandle1D2D8B, 
            ACPY3_PARAMFIELD_ELEMENTINDEX_DST, 
            fcpy->dstLineLen + fcpy->dstStride, 0);
 
    //ACPY2_setNumFrames(fcpy->dmaHandle1D2D8B, fcpy->dstNumLines);
    //ACPY2_setDstFrameIndex(fcpy->dmaHandle1D2D8B, fcpy->dstStride);
    
    /* Use DMA to fcpy input buffer into working buffer */
    ACPY3_start(fcpy->dmaHandle2D1D8B);
    //ACPY2_start(fcpy->dmaHandle2D1D8B, (Void *)in, 
    //    (Void *)(fcpy->workBuf1),
    //    (Uns)(fcpy->srcLineLen));

    /* Check that dma transfer has completed before finishing "processing" */
    while (!ACPY3_complete(fcpy->dmaHandle2D1D8B)) {
        ;
    };

    /* Use the DMA to copy data from working buffer 1 to working buffer 2 */ 
    ACPY3_start(fcpy->dmaHandle1D1D8B);
    //ACPY2_start(fcpy->dmaHandle1D1D8B, (Void *)(fcpy->workBuf1),
    ///   (Void *)(fcpy->workBuf2), 
    //    (Uns)((fcpy->srcLineLen) * (fcpy->srcNumLines)));


    /* wait for transfer to finish  */              
    ACPY3_wait(fcpy->dmaHandle1D1D8B);

    /* Quickly configure NumFrames and FrameIndex values for dmaHandle1D2D8B */
    //ACPY2_setNumFrames(fcpy->dmaHandle1D2D8B, fcpy->dstNumLines);
    //ACPY2_setDstFrameIndex(fcpy->dmaHandle1D2D8B, fcpy->dstStride);

    /* Use the DMA to copy data from working buffer 2 to output buffer */ 
    ACPY3_start(fcpy->dmaHandle1D2D8B);
    //ACPY2_start(fcpy->dmaHandle1D2D8B, (Void *)(fcpy->workBuf2),
    //    (Void *)out, (Uns)(fcpy->dstLineLen));
    
    /* wait for all transfers to complete before returning to the client */
    ACPY3_wait(fcpy->dmaHandle1D2D8B);

    /* 
     * DeActivate Channel  scratch DMA channels. 
     */
    ACPY3_deactivate(fcpy->dmaHandle1D1D8B);
    ACPY3_deactivate(fcpy->dmaHandle1D2D8B);
    ACPY3_deactivate(fcpy->dmaHandle2D1D8B);
}

/*
 *  ======== FCPY_TI_control ========
 */
XDAS_Bool FCPY_TI_control(IFCPY_Handle handle, IFCPY_Cmd cmd, IFCPY_Status
                          *status)
{
    FCPY_TI_Obj *fcpy = (FCPY_TI_Obj *)handle;

    if (cmd == IFCPY_GETSTATUS) {
        status->srcLineLen = fcpy->srcLineLen;
        status->srcNumLines = fcpy->srcNumLines;
        status->srcStride = fcpy->srcStride;
        status->dstLineLen = fcpy->dstLineLen;
        status->dstNumLines = fcpy->dstNumLines;
        status->dstStride = fcpy->dstStride;
        return (XDAS_TRUE);
    }
    else if (cmd == IFCPY_SETSTATUS) {
        /* 
         * Note that srcLineLen and srcNumLines cannot be changed once the
         * algorithm has been instantiated, as they determine the sizes of
         * the internal buffers used in FCPY_TI
         */ 
        fcpy->srcStride = status->srcStride;
        fcpy->dstLineLen = status->dstLineLen;
        fcpy->dstNumLines = status->dstNumLines;
        fcpy->dstStride = status->dstStride;
        return (XDAS_TRUE);
    }    
    
    /* Should not happen */
    return (XDAS_FALSE);
}
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

