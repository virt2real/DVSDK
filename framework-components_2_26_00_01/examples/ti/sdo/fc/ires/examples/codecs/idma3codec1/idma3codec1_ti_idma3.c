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
 *  ======== idma3codec1_ti_idma3.c ========
 *  EDMA Codec1 algorithm's implementation of IDMA3_Fxns.
 */

#include <xdc/std.h>
#include <string.h>

/* #include <ti/xdais/dm/iidma3codec1.h>*/
#include <ti/sdo/fc/ires/examples/codecs/idma3codec1/iidma3codec1.h>

#include <ti/xdais/ialg.h>

/* Header file for the resources used in this codec example. */
#include <ti/xdais/idma3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

#include "idma3codec1_ti.h"
#include "idma3codec1_ti_priv.h"

#define NUM_LOGICAL_CH 3

static Void IDMA3CODEC1_TI_dmaChangeChannels(IALG_Handle handle, 
        IDMA3_ChannelRec dmaTab[]);
static Uns IDMA3CODEC1_TI_dmaGetChannelCnt(Void); 
static Uns IDMA3CODEC1_TI_dmaGetChannels(IALG_Handle h, 
        IDMA3_ChannelRec dmaTab[]);
static Int IDMA3CODEC1_TI_dmaInit(IALG_Handle h, IDMA3_ChannelRec dmaTab[]);

extern IALG_Fxns IDMA3CODEC1_TI_IALG;

/*
 *  ======== IDMA3 ========
 */
IDMA3_Fxns IDMA3CODEC1_TI_IDMA3 = {
    //&IDMA3CODEC1_TI_IDMA3,
    &IDMA3CODEC1_TI_IALG,
    IDMA3CODEC1_TI_dmaChangeChannels,  /* ChangeChannels */
    IDMA3CODEC1_TI_dmaGetChannelCnt,   /* GetChannelCnt */
    IDMA3CODEC1_TI_dmaGetChannels,     /* GetChannels */
    IDMA3CODEC1_TI_dmaInit             /* initialize logical channels */
};



/*
 *  ======== FCPY_TI_dmaChangeChannels ========
 *  Update instance object with new logical channel.
 */
Void IDMA3CODEC1_TI_dmaChangeChannels(IALG_Handle handle, IDMA3_ChannelRec dmaTab[])
{
    IDMA3CODEC1_TI_Obj  *alg = (IDMA3CODEC1_TI_Obj *)handle;

    alg->dmaHandle1D1D8B = dmaTab[0].handle;
    alg->dmaHandle1D2D8B = dmaTab[1].handle;
    alg->dmaHandle2D1D8B = dmaTab[2].handle;
}

/*
 *  ======== IDMA3CODEC1_TI_numResources ========
 */
/* ARGSUSED */
static Uns IDMA3CODEC1_TI_dmaGetChannelCnt(Void) 
{
    return(NUM_LOGICAL_CH);
}

/*
 *  ======== IDMA3CODEC1_TI_getResources ========
 */
static Uns IDMA3CODEC1_TI_dmaGetChannels(IALG_Handle h, IDMA3_ChannelRec dmaTab[])
{
    IDMA3CODEC1_TI_Obj  *alg = (IDMA3CODEC1_TI_Obj *)h;
    int i = -1;

    /* 
     * This API could be called to query for resource requirements and after
     * having granted the resources, could also be queried for resource 
     * holdings of the algorithm. The difference is that in the second case a 
     * valid resource handle (that had been granted earlier) would be expected.
     */   
    /* Initial values on logical channels */
    dmaTab[0].handle = alg->dmaHandle1D1D8B; 
    dmaTab[1].handle = alg->dmaHandle1D2D8B; 
    dmaTab[2].handle = alg->dmaHandle2D1D8B; 
    
        /* Request for resources to perform some transfers */
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
 *  ======== IDMA3CODEC1_TI_dmaInit ========
 */
static Int IDMA3CODEC1_TI_dmaInit(IALG_Handle h, IDMA3_ChannelRec dmaTab[])
{
    IDMA3CODEC1_TI_Obj  *alg = (IDMA3CODEC1_TI_Obj *)h;

    /* 
     * Resource manager has returned a resource handle. Save it in the 
     * algorithm's instance object 
     */ 
    alg->dmaHandle1D1D8B = dmaTab[0].handle;
    alg->dmaHandle1D2D8B = dmaTab[1].handle;
    alg->dmaHandle2D1D8B = dmaTab[2].handle;

    return (IALG_EOK);

}
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.idma3codec1; 1, 0, 0,19; 12-1-2010 17:25:08; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

