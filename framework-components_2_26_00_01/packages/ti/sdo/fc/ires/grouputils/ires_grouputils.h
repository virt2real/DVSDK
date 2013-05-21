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
 *  @file       ti/sdo/fc/ires/examples/resources/grouputils/ires_grouputils.h 
 *
 *  @brief      IRES PROTOCOL GROUPUTILS Interface Definitions (C64P) - 
 *              Allows algorithms to request and receive handles representing 
 *              the GROUPUTILS resource 
 */

#ifndef ti_sdo_fc_ires_grouputils_IRES_GROUPUTILS
#define ti_sdo_fc_ires_grouputils_IRES_GROUPUTILS

/** @ingroup    DSPIRESMANPROTGROUPUTILS */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ires.h>

/**
 * @brief Name used to describe this protocol
 */
#define IRES_GROUPUTILS_PROTOCOLNAME  "ti.sdo.fc.ires.examples.resources.grouputils"

/**
 * @brief Name used to identify this GT module
 */
#define GROUPUTILS_GTNAME  "ti.sdo.fc.ires.examples.resources.grouputils"

/*
 * Note, we wrap the PROTOCOLVERSION in an ifdef so the
 * resource managers and algs get this version data placed in their object
 * files.  Apps, which include rman.h, will have this 'NOPROTOCOLREV' defined.
 */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

/**
 * @brief Revision used to identify this protocol 
 */
static IRES_ProtocolRevision IRES_GROUPUTILS_PROTOCOLREVISION = {1,0,0}; 

#endif


typedef Void (*ti_sdo_fc_ires_grouputils_LockFxn)(Int groupId, IALG_Handle alg);

/**
 *  @brief      Handle to "logical" resource
 */
typedef struct IRES_GROUPUTILS_Obj *IRES_GROUPUTILS_Handle;

/**
 *  @brief      GROUPUTILS Protocol Arguments definition.
 */
typedef struct IRES_GROUPUTILS_ProtocolArgs {

   IRES_ProtocolArgs base;

} IRES_GROUPUTILS_ProtocolArgs;

/**
 *  @brief          IRES_GROUPUTILS_Obj extends the generic IRES_Obj structure
 *                  that is returned back to the algorithm requesting the
 *                  resource
 */
typedef struct  IRES_GROUPUTILS_Obj {

    IRES_Obj ires;

    /* Functional layer returned as part of the object */
    /** API to release scratch group lock (that was granted to it during
        _activation_ of the algorithm). This API should be 
        used only if no scratch resources are going to be used by the alg till
        the lock is re-acquired. */   
    /* TODO either we need to add a context handle here, or assume the codecs
       will always save context before calling this */
    IRES_Status (*releaseGroupLock)(IALG_Handle alg, IRES_GROUPUTILS_Handle h); 

    /** API to re-acquire scratch group lock by this algorithm after it has been
        relinquished using the scratchGroupUnlock API. You do not need to call 
        this API if you are not going to use scratch resources till the end of
        this process call */ 
    /* TODO either we need to add a context handle here, or assume the codecs
       will always save context before calling this */
    IRES_Status (*reacquireGroupLock)(IALG_Handle alg,IRES_GROUPUTILS_Handle h);      
    /** API to call just before you start to use the IRES resources that have 
        been acquired as IRES_LATEACQUIRE type resources. This API *must* be 
        called prior to using these resources, as this ensure no other ALG 
        is currently using them */
    IRES_Status (*lockLateAcquireResources)(IALG_Handle alg, 
            IRES_GROUPUTILS_Handle h);      

    /** API to call after this alg is done using the IRES resources that have
        been acquired as IRES_LATEACQUIRE type resources. This API *must* be
        called to unlock these resources for use by other algorihtms */ 
    IRES_Status (*unlockLateAcquireResources) (IALG_Handle alg, 
            IRES_GROUPUTILS_Handle h);      

} IRES_GROUPUTILS_Obj;

/*
 * @brief           GROUPUTILS Register Layout 
 */
typedef struct IRES_GROUPUTILS_RegisterLayer  {

    unsigned int reg1;
} IRES_GROUPUTILS_RegisterLayer;


/*
 * @brief       Static Resource Properties 
 */
typedef struct IRES_GROUPUTILS_Properties {

    IRES_GROUPUTILS_RegisterLayer *globalRegs;
} IRES_GROUPUTILS_Properties;

typedef void    *GROUPUTILS_SemHandle;

typedef GROUPUTILS_SemHandle 
        (*ti_sdo_fc_ires_grouputils_GROUPUTILS_SemCreateFxn) (Int key, 
        Int count); 

typedef Int (*ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPendFxn)
        (GROUPUTILS_SemHandle sem, UInt32 count); 

typedef Void (*ti_sdo_fc_ires_grouputils_GROUPUTILS_SemDeleteFxn) 
        (GROUPUTILS_SemHandle sem); 

typedef Void (*ti_sdo_fc_ires_grouputils_GROUPUTILS_SemPostFxn)
        (GROUPUTILS_SemHandle sem); 

/*@}*/ /** @ingroup    DSPIRESPROTGROUPUTILS */


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  /* ti_sdo_fc_ires_grouputils_IRES_GROUPUTILS*/
/*
 *  @(#) ti.sdo.fc.ires.grouputils; 1, 0, 0,32; 12-1-2010 17:25:14; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

