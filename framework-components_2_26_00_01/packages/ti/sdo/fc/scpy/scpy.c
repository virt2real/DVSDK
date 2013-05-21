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
 *  ======== scpy.c ========
 *  Functional library for performing SDMA transfers using IRES_SDMA_Handle  
 *  allocated by RMAN/IRESMAN_SDMA 
 */

#include <xdc/std.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV
#include"scpy.h"

#include <stdio.h>

#include <ti/sdo/linuxutils/sdma/include/sdma.h>

#include <ti/sdo/linuxutils/cmem/include/cmem.h>

#define OMAP_DMA_CCR_EN     (1 << 7)

static int SCPY_refCount = 0;

static void omap_set_dma_transfer_params(int lch, unsigned long dmaAddr, 
        int data_type, int elem_count, int frame_count);
static void omap_set_dma_src_params(int lch, unsigned long dmaAddr, 
        int src_amode, unsigned long src_start,
                int src_ei, int src_fi);
static void omap_set_dma_dest_params(int lch, unsigned long dmaAddr, 
        int dest_amode, unsigned long dest_start,
                int dst_ei, int dst_fi);
static void omap_start_dma(int lch, unsigned int dmaAddr);

/*
 *  ======== SCPY_init ========
 * SCPY initialization API 
 */
void SCPY_init()
{
    SCPY_refCount++;
}

/*
 *  ======== SCPY_exit ========
 * SCPY finalization API 
 */
void SCPY_exit()
{
    SCPY_refCount--;
    if (0 <= SCPY_refCount) {
    } 
}

/*
 *  ======== SCPY_configure ========
 *  Configure a transfer on the SDMA handle
 */
void SCPY_configure(IRES_SDMA_Handle handle, SCPY_Params * params)
{
    /* SCPY_configure should be called with only one logicalChannel */ 
    int logicalChannel = handle->channel->chanNum; 
    unsigned int dmaAddr = (unsigned int)(handle->channel->addr);

    CMEM_init();
    
    omap_set_dma_transfer_params(logicalChannel, dmaAddr, 
            params->transfer->dataType, params->transfer->elemCount, 
            params->transfer->frameCount);


    omap_set_dma_src_params(logicalChannel, dmaAddr, 
            params->src->addr_mode, CMEM_getPhys((void *)(params->src->addr)),
            params->src->elem_index, params->src->frame_index);

    omap_set_dma_dest_params(logicalChannel, dmaAddr, 
            params->dst->addr_mode, CMEM_getPhys((void *)(params->dst->addr)),
            params->dst->elem_index, params->dst->frame_index);

    CMEM_exit();
}

/*
 *  ======== SCPY_start ========
 *  Start an SDMA transfer (configured previously) on this handle.  
 */
void SCPY_start(IRES_SDMA_Handle handle)
{
    int logicalChannel = handle->channel->chanNum; 
    unsigned int dmaAddr = (unsigned int)(handle->channel->addr);
    SCPY_wait(handle); 
    handle->channel->transferState.transferCompleted = 0;
    omap_start_dma(logicalChannel, dmaAddr);
}

/*
 *  ======== SCPY_wait ========
 * Blocking call that waits for the transfer on this handle to complete  
 */
void SCPY_wait(IRES_SDMA_Handle handle)
{
     volatile unsigned int transferComplete = 
             (handle->channel->transferState.transferCompleted); 

/* Check the transferComplete flag, if TRUE, return.
       If FALSE, then IOCTL to check status ? */   
    if (TRUE == transferComplete) {
        return; 
    }

    SDMA_wait(handle->channel); 
}

/*
 *  ======== SCPY_complete ========
 *  Non-blocking call that returns the status of the transfer configured on 
 *  this handle.
 */
Bool SCPY_complete(IRES_SDMA_Handle handle)
{
     return (handle->channel->transferState.transferCompleted); 
}


/*
 *  ======== omap_set_dma_transfer_params ========
 *  Sets the transfer parameters (transfer dimensions, address etc) 
 */
/* ARGSUSED */ 
static void omap_set_dma_transfer_params(int lch, unsigned long dmaAddr, 
        int data_type, int elem_count, int frame_count)
{
    IRES_SDMA_RegisterLayer * regs = (IRES_SDMA_RegisterLayer *)(dmaAddr);

        regs->DMA4_CSDP &= ~0x03;
        regs->DMA4_CSDP |= data_type;

        regs->DMA4_CEN = elem_count;
        regs->DMA4_CFN = frame_count;
}

/*
 *  ======== omap_set_dma_src_params ========
 *  Sets the source parameters  (addr, synchronization, address update mode etc)
 */
/* ARGSUSED */ 
static void omap_set_dma_src_params(int lch, unsigned long dmaAddr, 
        int src_amode, unsigned long src_start,
                int src_ei, int src_fi)
{
    IRES_SDMA_RegisterLayer * regs = (IRES_SDMA_RegisterLayer *)(dmaAddr);

        regs->DMA4_CCR &= ~(0x03 << 12);
        regs->DMA4_CCR |= src_amode << 12;

        regs->DMA4_CSSA = src_start;

        regs->DMA4_CSE = src_ei;
        regs->DMA4_CSF = src_fi;
}


/*
 *  ======== ompa_set_dma_dest_params ========
 *  Sets the dest. parameters  (addr, synchronization, address update mode etc)
 */
/* ARGSUSED */ 
static void omap_set_dma_dest_params(int lch, unsigned long dmaAddr, 
        int dest_amode, unsigned long dest_start,
                int dst_ei, int dst_fi)
{
    IRES_SDMA_RegisterLayer * regs = (IRES_SDMA_RegisterLayer *)(dmaAddr);

        regs->DMA4_CCR &= ~(0x03 << 14);
        regs->DMA4_CCR |= dest_amode << 14;

        regs->DMA4_CDSA = dest_start;

        regs->DMA4_CDE = dst_ei;
        regs->DMA4_CDF = dst_fi;

}

/*
 *  ======== omap_start_dma ========
 *  Fires off the SDMA transfer on the specified channel 
 */
static void omap_start_dma(int lch, unsigned int dmaAddr)
{
    IRES_SDMA_RegisterLayer * regs = (IRES_SDMA_RegisterLayer *)(dmaAddr);
        regs->DMA4_CLNK_CTRL = lch;
        regs->DMA4_CCR |= OMAP_DMA_CCR_EN;
}
/*
 *  @(#) ti.sdo.fc.scpy; 1, 0, 0,131; 12-1-2010 17:26:01; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

