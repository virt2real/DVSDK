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
 *  @file       ti/sdo/fc/ires/vicp/ires_vicp2.h 
 *
 *  @brief      IRES PROTOCOL VICP Interface Definitions - 
 *              Allows algorithms to request and receive handles representing 
 *              the VICP resource 
 */

/**
 *  @addtogroup ti_sdo_fc_ires_vicp2_IRES_VICP2 IRES VICP Protocol
 *
 *              Allows algorithms to request and receive handles representing 
 *              VICP resources.
 */

#ifndef ti_sdo_fc_ires_vicp2_IRES_VICP2_
#define ti_sdo_fc_ires_vicp2_IRES_VICP2_

/** @ingroup    ti_sdo_fc_ires_vicp2_IRES_VICP2 */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires.h>

/**
 * @brief  Maximum number of VICP resources(components) to be managed 
 */
#define IRES_VICP2_MAXRESOURCES  1


/**
 * @brief Name used to describe this protocol
 */
#define IRES_VICP2_PROTOCOLNAME     "ti.sdo.fc.ires.vicp2"

/**
 * @brief  Maximum number of VICP buffers to be managed 
 */
#define IRES_VICP2_NUMBUFFERS      16 

/**
 * @brief  Value indicating a bad VICP resource was returned 
 */
#define IRES_VICP2_BADRESOURCE     0xFFFFFFFF  

/**
 * @brief  VICP Buffer resources(components) to be managed 
 */

#define IMCOP_BUFFER_IMGBUF_A           0x0 
#define IMCOP_BUFFER_IMGBUF_B           0x1 
#define IMCOP_BUFFER_IMGBUF_C           0x2 
#define IMCOP_BUFFER_IMGBUF_D           0x3     /**< Only for DM365 */  
#define IMCOP_BUFFER_IMGBUF_E           0x4     /**< Only for DM365 */
#define IMCOP_BUFFER_IMX0COEFFBUF       0x5    
#define IMCOP_BUFFER_IMX0CMDBUF         0x6 
#define IMCOP_BUFFER_IMX1COEFFBUF       0x7     /**< Only for DM365 */
#define IMCOP_BUFFER_IMX1CMDBUF         0x8     /**< Only for DM365 */

#define IMCOP_BUFFER_BABYIMXCMDBUFFER   0x9     
#define IMCOP_BUFFER_BABYIMXORIGBUFFER  0xA     

#define IMCOP_BUFFER_BABYIMXREFBUFFER   0xB     /**< Only for DM355 */  
#define IMCOP_BUFFER_SEQUENCERPMEM      0xC     /**< Only for DM365 */

#define IMCOP_BUFFER_QIQMEM             0xD     
#define IMCOP_BUFFER_HUFFMEM            0xE     
#define IMCOP_BUFFER_SEQBUF4            0xF     

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision IRES_VICP2_PROTOCOLREVISION = {1, 0, 0}; 

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_VICP2_Obj *IRES_VICP2_Handle;

/**
 *  @brief      VICP Protocol Arguments definition.
 */
typedef struct IRES_VICP2_ProtocolArgs {

    int                 size;           /**< Size of this structure. */
    IRES_RequestMode    mode;           /**< Resource requested as Persistent 
                                             or Scratch. 
                                             This mode applies to all the 
                                             resources requested below */ 
    short               requestIMX0;     
    short               requestIMX1;    /**< Value of 1 to indicate resource 
                                           requested 0 otherwise */
    short               requestMJCP;    /**< MJCP, same as VLCD */
    short               requestNSF;     /**< NSF, Noise filter */  

    unsigned int        requestIMCOPBuffers;
                                        /**< Bit# IMCOP_BUFFER_<>  
                                           0 or 1 bit indicating if access to
                                           particular buffer is required. 
                                           ((0x1 << IMCOP_BUFFER_IMGBUF) | 
                                           (0x1 << IMCOP_BUFFER_IMGBUF_A)); 
                                        */
    unsigned int        numMemoryRequests;       
                                        /**< Number of individual memory buffers
                                           required */  
    unsigned int        memRequestSizes[IRES_VICP2_NUMBUFFERS];
                                        /**< Sizes of buffers required */

} IRES_VICP2_ProtocolArgs;

/**
 *  @brief          IRES_VICP2_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_VICP2_Obj {

    IRES_Obj            ires;
    short               assignedIMX0;    
    short               assignedIMX1;     /**< Value of 1 to indicate resource 
                                           was granted, 0 otherwise */
    short               assignedMJCP;
    short               assignedNSF;

    unsigned int        assignedIMCOPBuffers[IRES_VICP2_NUMBUFFERS];
                                          /**< Addresses of Named buffers 
                                               granted, index array with 
                                               IMCOP_BUFFER_<>*/
    short               numMemBufs;       /**< Number of individual memory 
                                               buffers assigned */  
    unsigned int        assignedMemAddrs[IRES_VICP2_NUMBUFFERS];
                                          /**< Addresses of buffers assigned,
                                               only the first numBufs will hold
                                               valid addresses */
    unsigned int        assignedMemSizes[IRES_VICP2_NUMBUFFERS]; 

    unsigned int        configBaseAddress;/**< Base address of config space */

    unsigned int        dmaViewConfigBaseAddr;  
                                          /**< Base address of DMA view of
                                               VICP buffers */     

    unsigned  int           pscRegisterSpace; /**< Base address of the PSC and 
                                               system module register space */

} IRES_VICP2_Obj;

/*
 * @brief           VICP Buffer Layout 
 */
typedef struct IRES_VICP2_Buffers {

    int size;   /**< Size of this structure. */
 
    unsigned char *vicp_cfg_base;
 
    unsigned char *imgBufA_base;
    unsigned char *imgBufB_base;
    unsigned char *imgBufC_base;
    unsigned char *imgBufD_base;
    unsigned char *imgBufE_base;
    unsigned char *imx0CoeffBuff_base;
    unsigned char *imx0CmdBuf_base;
    unsigned char *imx1CoeffBuff_base;
    unsigned char *imx1CmdBuf_base;

    
    unsigned char *babyImxCmdBuf_base;  /**< Not yet supported for DM365 */
    unsigned char *babyImxOrigBuf_base; /**< Not yet supported for DM365 */
    unsigned char *babyImxRefBuf_base;  /**< Not yet supported for DM365 */
    unsigned char *sequencerPmem_base;  
    unsigned int  *qiqmem_base;         /**< Not yet supported for DM365 */
    unsigned int  *predmem_base;        /**< Not yet supported for DM365 */ 
    unsigned int  *mvmem;               /**< Not yet supported for DM365 */ 
    unsigned int  *huffmem;             /**< Not yet supported for DM365 */ 
    unsigned int  *seqBuf1;             /**< Not yet supported for DM365 */ 
    unsigned int  *seqBuf2;             /**< Not yet supported for DM365 */ 
    unsigned int  *seqBuf3;             /**< Not yet supported for DM365 */ 
    unsigned int  *seqBuf4;             /**< Not yet supported for DM365 */ 
    unsigned int  *sequencerDmem;       /**< Not yet supported for DM365 */ 
    /* . . . */

} IRES_VICP2_Buffers;


/*
 * @brief       Static Resource Properties 
 */
typedef struct IRES_VICP2_Properties {
    
    int size;

    IRES_VICP2_Buffers buffers;

} IRES_VICP2_Properties;


#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/

#endif
/*
 *  @(#) ti.sdo.fc.ires.vicp; 1, 0, 1,177; 12-1-2010 17:25:26; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

