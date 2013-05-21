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
 *  ======== bufres.h ========
 *  Buffer resource. This is a very simple example of a resource manager that
 *  implements IRES and IRESMAN interfaces. This resource manager manages a
 *  single buffer that can be shared by multiple algorithms belonging to the
 *  same scratch group (ie, the algorithms don't preempt eachother). An
 *  algorithm can request a chunk of memory with a specified length and
 *  alignment, within this buffer.
 */

#ifndef BUFRES_H_
#define BUFRES_H_

#include <ti/xdais/ires_common.h>
#include <ti/sdo/fc/ires/iresman_protocol.h>
#include <ti/sdo/fc/ires/iresman.h>


#define NUMRES 1 
/*
 *  ======== BUFRES_NAME ========
 *  Name used for this resource.
 */
#define BUFRES_PROTOCOLNAME "ti.sdo.fc.rman.examples.bufres_yield"

/*
 *  ======== BUFRES_PROTOCOLVERSION ======
 *
 */
/* This define is to take care of warning errors for un-used variable. 
   RMAN undefs this variable and algs and resource managers should be able to
   use it */
#ifndef ti_sdo_fc_ires_NOPROTOCOLREV

static IRES_ProtocolRevision BUFRES_PROTOCOLVERSION = {1,0,0};

#endif
 
/*
 *  ======== BUFRES_Params ========
 *  Extends IRESMAN_Params. These params are used to initialize the resource.
 */
typedef struct BUFRES_Params {
    IRESMAN_Params iresConfig;

    /* Config params specific to this resource */
    Void      *base;      /* Base address of the buffer to manage */
    UInt32     length;    /* Size of the buffer */
    UInt32     fillValue; /* fillValue to initialize the buffer */   
} BUFRES_Params;

/*
 *  ======== BUFRES_Obj ========
 *  Extension of IRES_Obj. This object holds the state of the logical resource
 *  granted to the algorithm.
 */
typedef struct BUFRES_Obj {
    IRES_Obj        ires;

    /* Fields specific to this resource */
    Void   *base;    /* Base address of assigned memory chunk */
    Int     length;  /* Length of assigned memory chunk */
} BUFRES_Obj;

/*
 *  ======== BUFRES_Args ========
 *  Extends IRES_ProtocolArgs. Used by the algorithm to request this resource.
 */
typedef struct BUFRES_Args {
    IRES_ProtocolArgs iresArgs;

    /* Fields filled in by algorithm when requesting this resource */
    Int    length;  /* Length of buffer requested */
    Int    align;   /* Buffer alignment: 0 (no alignment) or a power of 2 */
} BUFRES_Args;

/*
 *  ======== BUFRES_Props ========
 *  Implementation of IRES_Properties for the buffer resource
 *  
 */
typedef struct BUFRES_Props {
    Int         size;    /* Size of this structure */

    /* Fields specific to this resource */
    Void   *base;    /* Base address of the buffer resource */
    Int     length;  /* Length of the buffer resource */
} BUFRES_Props;

/*
 *  ======== BUFRES_Handle ========
 *  Opaque handle to the BUFRES extension of the IRES_Obj object
 */
typedef struct BUFRES_Obj *BUFRES_Handle;

extern IRESMAN_ConstructFxns BUFRES_REQFXNS;
extern IRESMAN_Fxns BUFRES_MGRFXNS;

#endif /* BUFRES_H_ */

/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,177; 12-1-2010 17:25:39; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

