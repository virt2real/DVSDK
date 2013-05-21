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
/**
 *  @file       ti/sdo/fc/scpy/scpy.h
 *
 *  @brief      SCPY Module interface Definitions (C64P) - 
 *              Allows algorithms submit and sychronize with SDMA transfers 
 */

/**
 *  @addtogroup ti_sdo_fc_scpy_SCPY SCPY - Functional library for SDMA resources
 *              The SCPY module provides a list of SDMA operations
 *              an algorithm can perform on logical SDMA channels
 *              it acquires through the IRES_SDMA protocol. Examples
 *              of SCPY operations include channel configuration, SDMA
 *              transfer scheduling, and SDMA transfer synchronization.
 */
#ifndef ti_sdo_fc_scpy_SCPY_
#define ti_sdo_fc_scpy_SCPY_


/* TODO: Uncommenting the below define creates ordering dependencies between
         ires_sdma.h and scpy.h (ires_sdma.h needs to be before scpy.h)   
         Need to figure this out, till then commenting it out. 
         Warnings appear during build of this library */
/*  #define ti_sdo_fc_ires_NOPROTOCOLREV*/

/** @ingroup    ti_sdo_fc_scpy_SCPY */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/fc/ires/sdma/ires_sdma.h>

#define OMAP_DMA_DATA_TYPE_S8       0x00  
#define OMAP_DMA_DATA_TYPE_S16      0x01 
#define OMAP_DMA_DATA_TYPE_S32      0x02

#define OMAP_DMA_PORT_EMIFF         0x00

#define OMAP_DMA_AMODE_POST_CONST           0x00
#define OMAP_DMA_AMODE_POST_INC             0x01
#define OMAP_DMA_AMODE_POST_SINGLE_INDEX    0x02
#define OMAP_DMA_AMODE_POST_DOUBLE_INDEX    0x03

/**
 *  @brief      To identify mode of sychronization of transfer 
 */
#define OMAP_DMA_SYNC_MODE_ELEMENT  0x00
#define OMAP_DMA_SYNC_MODE_FRAME    0x01
#define OMAP_DMA_SYNC_MODE_BLOCK    0x02

#define OMAP_DMA_SYNC_TYPE_DEST     0x00
#define OMAP_DMA_SYNC_TYPE_SRC      0x01


/**
 *  @brief      Parameters of Address (source or destination) of transfer  
 */
typedef struct SCPY_AddrParams {
    int addr_mode;
    unsigned int addr;
    int elem_index;
    int frame_index;
} SCPY_AddrParams;

/**
 *  @brief      Details of Transfer
 */
typedef struct SCPY_TransferParams {
    int dataType; 
    int elemCount;
    int frameCount;
} SCPY_TransferParams;

/*
 *  @brief      Paramters of transfer
 */
typedef struct SCPY_Params {
    SCPY_AddrParams * src;
    SCPY_AddrParams * dst;
    SCPY_TransferParams * transfer;
} SCPY_Params;

/**
 *  @brief      SCPY initialization API 
 */
void SCPY_init();

/**
 *  @brief      SCPY finalization API 
 */
void SCPY_exit();

/**
 *  @brief      Configures transfer on a particular logical handle 
 *   
 *  @param[in]  logicalChannel      Handle to the logical channel on which 
 *                                  transfer will be configured 
 *
 *  @param[in]  params              Params to describe the transfer, src/dst
 *                                  addresses, sychronization mode, transfer
 *                                  dimensions etc.   
 *   
 */
void SCPY_configure(IRES_SDMA_Handle logicalChannel, SCPY_Params * params);

/**
 *  @brief     Starts a transfer previously configured on a channel  
 *
 *  @param[in]  logicalChannel      Previously configured logical channel on
 *                                  which to start the transfer.
 */
void SCPY_start(IRES_SDMA_Handle logicalChannel);

/**
 *  @brief     Wait for the transfer to complete 
 * 
 *  @param[in]  logicalChannel      Logical channel on which transfer is 
 *                                  ongoing.
 */
void SCPY_wait(IRES_SDMA_Handle logicalChannel);

/**
 *  @brief     Returns status of transfer on the logical channel  
 * 
 *  @param[in]  logicalChannel      Logical channel on which transfer is 
 *                                  ongoing.
 *  @retval     TRUE                Transfer completed
 *  @retval     FALSE               Transfer in progress
 */
Bool SCPY_complete(IRES_SDMA_Handle logicalChannel);


#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/ /** @ingroup    ti_sdo_fc_scpy_SCPY */
#endif /* ti_sdo_fc_scpy_SCPY_*/
/*
 *  @(#) ti.sdo.fc.scpy; 1, 0, 0,131; 12-1-2010 17:26:01; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

