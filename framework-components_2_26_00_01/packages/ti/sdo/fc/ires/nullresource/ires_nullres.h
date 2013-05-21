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
 *  @file       ti/sdo/fc/ires/nullresource/ires_nullres.h 
 *
 *  @brief      IRES PROTOCOL NULLRES Interface Definitions - 
 *              Allows algorithms to request and receive handles representing 
 *              the NULLRES resource 
 */

#ifndef ti_sdo_fc_ires_nullresource_IRES_NULLRES_
#define ti_sdo_fc_ires_nullresource_IRES_NULLRES_

/** @ingroup    DSPIRESMANPROTNULLRES */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_NULLRES_PROTOCOLNAME  "ti.sdo.fc.ires.examples.resources.nullres"


/*
 * Note, we wrap the BUFRES_PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief   Protocol Revision for this resource
 */
static IRES_ProtocolRevision IRES_NULLRES_PROTOCOLREVISION = {1,0,0}; 

#endif

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_NULLRES_Obj *IRES_NULLRES_Handle;

/**
 *  @brief          IRES_NULLRES_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_NULLRES_Obj {

    IRES_Obj ires;

} IRES_NULLRES_Obj;


/*@}*/

#ifdef __cplusplus
}
#endif /* extern "C" */


#endif
/*
 *  @(#) ti.sdo.fc.ires.nullresource; 1, 0, 0,171; 12-1-2010 17:25:22; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

