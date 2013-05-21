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
 *  @file       ti/sdo/fc/ires/sdma/ires_sdma.h 
 *
 *  @brief      IRES PROTOCOL SDMA Interface Definitions (C64P) - 
 *              Allows algorithms to request and receive handles representing 
 *              the SDMA resource 
 */

/**
 *  @addtogroup ti_sdo_fc_ires_sdma_IRES_SDMA IRES SDMA Protocol
 *
 *              Allows algorithms to request and receive handles representing 
 *              SDMA resources associated with a single SDMA channel. 
 */


#ifndef ti_sdo_fc_ires_sdma_IRES_SDMA_
#define ti_sdo_fc_ires_sdma_IRES_SDMA_

/** @ingroup    ti_sdo_fc_ires_sdma_IRES_SDMA */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires.h>
#include <ti/sdo/linuxutils/sdma/include/sdma.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_SDMA_PROTOCOLNAME  "ti.sdo.fc.ires.sdma"

/**
 * @brief Name used to identify this GT module
 */
#define SDMA_GTNAME  "ti.sdo.fc.ires.sdma"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief Revision used to identify this protocol 
 */
static IRES_ProtocolRevision IRES_SDMA_PROTOCOLREVISION = {1,0,0}; 

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_SDMA_Obj *IRES_SDMA_Handle;

/**
 *  @brief      SDMA Protocol Arguments definition.
 */
typedef struct IRES_SDMA_ProtocolArgs {

    IRES_ProtocolArgs base;

} IRES_SDMA_ProtocolArgs;

/**
 *  @brief          IRES_SDMA_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_SDMA_Obj {

    IRES_Obj ires;

    SDMA_ChannelDescriptor * channel; 
                                        /* Channel number that is granted to
                                           the requestor */
} IRES_SDMA_Obj;

/*
 * @brief           SDMA Register Layout 
 */
typedef struct IRES_SDMA_RegisterLayer  {

    unsigned int DMA4_CCR;
    unsigned int DMA4_CLNK_CTRL;
    unsigned int DMA4_CICR;
    unsigned int DMA4_CSR;
    unsigned int DMA4_CSDP;
    unsigned int DMA4_CEN;
    unsigned int DMA4_CFN;
    unsigned int DMA4_CSSA;
    unsigned int DMA4_CDSA;
    unsigned int DMA4_CSE;
    unsigned int DMA4_CSF;
    unsigned int DMA4_CDE;
    unsigned int DMA4_CDF;
    unsigned int DMA4_CSAC;
    unsigned int DMA4_CDAC;
    unsigned int DMA4_CCEN;
    unsigned int DMA4_CCFN;
    unsigned int DMA4_COLOR;
} IRES_SDMA_RegisterLayer;


/*
 * @brief       Static Resource Properties 
 */
typedef struct IRES_SDMA_Properties {

    IRES_SDMA_RegisterLayer *globalRegs;

} IRES_SDMA_Properties;

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/ /** @ingroup    ti_sdo_fc_ires_sdma_IRES_SDMA */

#endif  /* ti_sdo_fc_ires_sdma_IRES_SDMA_ */
/*
 *  @(#) ti.sdo.fc.ires.sdma; 1, 0, 0,132; 12-1-2010 17:25:22; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

