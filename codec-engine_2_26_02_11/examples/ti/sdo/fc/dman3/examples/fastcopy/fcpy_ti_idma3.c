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
 *  ======== fcpy_ti_idma3.c ========
 *  FCPY Module - TI implementation of a FCPY algorithm
 *
 *  This file contains an implementation of the IDMA3 interface
 */

#pragma CODE_SECTION(FCPY_TI_dmaChangeChannels, ".text:dmaChangeChannels")
#pragma CODE_SECTION(FCPY_TI_dmaGetChannelCnt, ".text:dmaGetChannelCnt")
#pragma CODE_SECTION(FCPY_TI_dmaGetChannels, ".text:dmaGetChannels")
#pragma CODE_SECTION(FCPY_TI_dmaInit, ".text:dmaInit")

#include <xdc/std.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

#include "fcpy_ti_priv.h"

#define NUM_LOGICAL_CH 3

/*
 *  ======== FCPY_TI_dmaChangeChannels ========
 *  Update instance object with new logical channel.
 */
Void FCPY_TI_dmaChangeChannels(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    FCPY_TI_Obj *fcpy = (Void *)handle;

    fcpy->dmaHandle1D1D8B = dmaTab[0].handle;
    fcpy->dmaHandle1D2D8B = dmaTab[1].handle;
    fcpy->dmaHandle2D1D8B = dmaTab[2].handle;
}

/*
 *  ======== FCPY_TI_dmaGetChannelCnt ========
 *  Return max number of logical channels requested.
 */
Uns FCPY_TI_dmaGetChannelCnt(Void)
{
    return(NUM_LOGICAL_CH);
}

/*
 *  ======== FCPY_TI_dmaGetChannels ========
 *  Declare DMA resource requirement/holdings. 
 */
Uns FCPY_TI_dmaGetChannels(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    FCPY_TI_Obj *fcpy = (Void *)handle;
    int i;

    /* Initial values on logical channels */
    dmaTab[0].handle = fcpy->dmaHandle1D1D8B; 
    dmaTab[1].handle = fcpy->dmaHandle1D2D8B; 
    dmaTab[2].handle = fcpy->dmaHandle2D1D8B; 

    /*   */
    dmaTab[0].numTransfers = 1;
    dmaTab[0].numWaits = 1;
    
    dmaTab[1].numTransfers = 1;
    dmaTab[1].numWaits = 1;
    
    dmaTab[2].numTransfers = 1;
    dmaTab[2].numWaits = 1;
     
    /*
     * Request logical DMA channels for use with ACPY3 
     * AND with environment size obtained from ACPY3 implementation
     * AND with low priority.
     */
    for (i=0; i<NUM_LOGICAL_CH; i++) {
        dmaTab[i].priority = IDMA3_PRIORITY_LOW; 
        dmaTab[i].protocol = &ACPY3_PROTOCOL;
        dmaTab[i].persistent = FALSE;
    }

    return (NUM_LOGICAL_CH);
}

/*
 *  ======== FCPY_TI_dmaInit========
 *  Initialize instance object with granted logical channel.
 */
Int FCPY_TI_dmaInit(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    FCPY_TI_Obj *fcpy = (Void *)handle;     

    fcpy->dmaHandle1D1D8B = dmaTab[0].handle;
    fcpy->dmaHandle1D2D8B = dmaTab[1].handle;
    fcpy->dmaHandle2D1D8B = dmaTab[2].handle;
    
    return (IALG_EOK);
}
/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

