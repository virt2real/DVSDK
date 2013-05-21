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
 *  @file       ti/sdo/fc/ires/addrspace/ires_addrspace.h
 *
 *  @brief      IRES PROTOCOL ADDRSPACE Interface Definitions -
 *              Allows algorithms to request and receive handles that allow an
 *              OS agnostic way of accessing hardware address spaces.
 */

#ifndef ti_sdo_fc_ires_addrspace_IRES_ADDRSPACE_
#define ti_sdo_fc_ires_addrspace_IRES_ADDRSPACE_

/** @ingroup    ti_sdo_fc_ires_addrspace_IRES_ADDRSPACE */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_ADDRSPACE_PROTOCOLNAME \
        "ti.sdo.fc.ires.addrspace"

/**
 * @brief Name used to identify this GT module
 */
#define ADDRSPACE_GTNAME  "ti.sdo.fc.ires.addrspace"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief Revision used to identify this protocol
 */
static IRES_ProtocolRevision IRES_ADDRSPACE_PROTOCOLREVISION = {1, 0, 0};

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_ADDRSPACE_Obj *IRES_ADDRSPACE_Handle;


/**
 *  @brief      Decription of kinds of accesses that may be allowed on returned
 *              addresses
 */
typedef enum IRES_ADDRSPACE_AccessType {
    IRES_ADDRSPACE_READ = 1,
    IRES_ADDRSPACE_WRITE = 2,
    IRES_ADDRSPACE_EXEC = 4,
    IRES_ADDRSPACE_NONE = 8
} IRES_ADDRSPACE_AccessType;

/**
 *  @brief      ADDRSPACE Protocol Arguments definition.
 */
typedef struct IRES_ADDRSPACE_ProtocolArgs {

    IRES_ProtocolArgs   base;   /**< Implementation of base protocol args */
    Void *              addr;   /**< Hardware address accessed by alg */
    unsigned int        len;    /**< Length of the address space */
    IRES_ADDRSPACE_AccessType
                        attrib; /**< Describes the kind of access required
                                         R, W, E etc */
} IRES_ADDRSPACE_ProtocolArgs;

/**
 *  @brief          IRES_ADDRSPACE_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_ADDRSPACE_Obj {
    IRES_Obj            ires;
    Void *              addr;
    unsigned int        len;
} IRES_ADDRSPACE_Obj;

/*
 * @brief       Static Resource Properties
 */
typedef struct IRES_ADDRSPACE_Properties {
    int size;
} IRES_ADDRSPACE_Properties;

/*@}*/ /** @ingroup    ti_sdo_fc_ires_addrspace_IRES_ADDRSPACE */


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
/*
 *  @(#) ti.sdo.fc.ires.addrspace; 1, 0, 0,61; 12-1-2010 17:24:55; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

