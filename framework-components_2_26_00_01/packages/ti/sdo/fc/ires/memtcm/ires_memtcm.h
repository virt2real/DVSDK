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
 *  @file       ti/sdo/fc/ires/memtcm/ires_memtcm.h 
 *
 *  @brief      IRES PROTOCOL MEMTCM Interface Definitions (C64P) - 
 *              Allows algorithms to request and receive handles representing 
 *              (CMEM alloc-ed) ARM TCM memory on the DM365. 
 */

#ifndef ti_sdo_fc_ires_memtcm_IRES_MEMTCM_
#define ti_sdo_fc_ires_memtcm_IRES_MEMTCM_

/** @ingroup  ti_sdo_fc_ires_memtcm_IRES_MEMTCM   */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_MEMTCM_PROTOCOLNAME  "ti.sdo.fc.ires.examples.resources.memtcm"

/**
 * @brief Name used to identify this GT module
 */
#define MEMTCM_GTNAME  "ti.sdo.fc.ires.examples.resources.memtcm"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief Revision used to identify this protocol 
 */
static IRES_ProtocolRevision IRES_MEMTCM_PROTOCOLREVISION = {1,0,0}; 

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_MEMTCM_Obj *IRES_MEMTCM_Handle;

/**
 *  @brief      MEMTCM Protocol Arguments definition.
 */
typedef struct IRES_MEMTCM_ProtocolArgs {

   IRES_ProtocolArgs base;

   unsigned int memSize;            /* Size of the requested TCM memory */ 

} IRES_MEMTCM_ProtocolArgs;

/**
 *  @brief          IRES_MEMTCM_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_MEMTCM_Obj {

    IRES_Obj ires;

    unsigned int memSize;           /* Size of the returned TCM memory */

    void * memAddr;                 /* Base address of the returned TCM mem */
     
} IRES_MEMTCM_Obj;

/*
 * @brief       Static Resource Properties 
 */
typedef struct IRES_MEMTCM_Properties {

    int size;

} IRES_MEMTCM_Properties;

/*@}*/ /** @ingroup   ti_sdo_fc_ires_memtcm_IRES_MEMTCM  */


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  /* ti_sdo_fc_ires_memtcm_IRES_MEMTCM_ */
/*
 *  @(#) ti.sdo.fc.ires.memtcm; 1, 0, 0,45; 12-1-2010 17:25:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

