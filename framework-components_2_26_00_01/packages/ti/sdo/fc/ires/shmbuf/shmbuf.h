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
 *  @file       ti/sdo/fc/ires/shmbuf/shmbuf.h          
 *
 *  @brief      Linux shared memory buffer resource. This is another simple 
 *              example of a resource manager that implements IRES and IRESMAN 
 *              interfaces.
 *              This resource manager manages a single buffer that can be used 
 *              by algorithms in different processes. An algorithm can request 
 *              a chunk of memory with a specified length and alignment, within
 *              this buffer.
 */

/**
 *  @addtogroup ti_sdo_fc_ires_shmbuf_SHMBUF Shared Memory Buffer Protocol
 *
 *              Allows algorithms to request and receive handles representing 
 *              a shared memory buffer.
 */


#ifndef SHMBUF_H_
#define SHMBUF_H_

/** @ingroup    ti_sdo_fc_ires_shmbuf_SHMBUF */
/*@{*/

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires_common.h>
#include <ti/sdo/fc/ires/iresman_protocol.h>
#include <ti/sdo/fc/ires/iresman.h>


#define SHMBUF_GTNAME "ti.sdo.fc.ires.shmbuf" /**< Name used to identify the
                                               *   GT module
                                               */

/**
 * @brief Name used to describe this protocol
 */
#define SHMBUF_PROTOCOLNAME "ti.sdo.fc.ires.shmbuf"


/*
 * Note, we wrap the SHMBUF_PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision SHMBUF_PROTOCOLVERSION = {1, 0, 0};

#endif


/**
 * @brief   SHMBUF specific params.
 *
 * @remarks This struct extends IRESMAN_Params.  These params are used to
 *          initialize the resource.
 */
typedef struct SHMBUF_Params {
    IRESMAN_Params iresConfig;

    /* Config params specific to this resource */
    Int       bufsize;    /* Size of the buffer */
    UInt32    key;        /* Key to identify shared memory object */
    UInt32    isScratch;  /* Can the buffer be shared? */
} SHMBUF_Params;

/*
 *  ======== SHMBUF_Obj ========
 *  Extension of IRES_Obj. This object holds the state of the logical resource
 *  granted to the algorithm.
 */
typedef struct SHMBUF_Obj {
    IRES_Obj        ires;

    /* Fields specific to this resource */
    Void   *base;    /* Base address of assigned memory chunk */
    Int     length;  /* Length of assigned memory chunk */
} SHMBUF_Obj;

/*
 *  ======== SHMBUF_Args ========
 *  Extends IRES_ProtocolArgs. Used by the algorithm to request this resource.
 */
typedef struct SHMBUF_Args {
    IRES_ProtocolArgs iresArgs;

    /* Fields filled in by algorithm when requesting this resource */
    Int    length;  /* Length of buffer requested */
    Int    align;   /* Buffer alignment: 0 (no alignment) or a power of 2 */
} SHMBUF_Args;

/*
 *  ======== SHMBUF_Props ========
 *  Implementation of IRES_Properties for the buffer resource, returned
 *  by SHMBUF_PROTOCOL.getStaticResourceProperties().
 */
typedef struct SHMBUF_Props {
    Int         size;    /* Size of this structure */

    /* Fields specific to this resource */
    Void   *base;        /* Base address of the shared memory resource */
    Int     length;      /* Length of the shared memory resource */
    Int     isScratch;   /* Can it be shared? */
} SHMBUF_Props;

/*
 *  ======== SHMBUF_Handle ========
 *  Opaque handle to the SHMBUF extension of the IRES_Obj object
 */
typedef struct SHMBUF_Obj *SHMBUF_Handle;

extern SHMBUF_Params SHMBUF_PARAMS;
extern IRESMAN_ConstructFxns SHMBUF_REQFXNS;
extern IRESMAN_Fxns SHMBUF_MGRFXNS;


#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif /* SHMBUF_H_ */

/*
 *  @(#) ti.sdo.fc.ires.shmbuf; 1, 0, 0,119; 12-1-2010 17:25:23; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

