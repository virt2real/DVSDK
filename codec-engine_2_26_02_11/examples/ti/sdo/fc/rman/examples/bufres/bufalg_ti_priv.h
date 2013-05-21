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
 * */
/*
 *  ======== bufalg_ti_priv.h ========
 *
 *  Private internal vendor specific interface.
 *
 */

#ifndef ti_sdo_fc_rman_examples_bufres_BUFALG_TI_PRIV_
#define ti_sdo_fc_rman_examples_bufres_BUFALG_TI_PRIV_

#include <ti/xdais/ialg.h>
#include <ti/xdais/ires.h>

#include "ibufalg.h"
#include <ti/sdo/fc/ires/bufres/bufres.h>

#ifdef __cplusplus
extern "C" {
#endif

#define NUMRES 1            /* Number of resources used by the algorithm */

/*
 *  ======== BUFALG_TI_Obj ========
 */
typedef struct BUFALG_TI_Obj {
    IALG_Obj        alg;               /* Alogorithm handle */
    BUFRES_Handle   res[NUMRES];       /* Resource used by the alg */
    Bool            resActive[NUMRES]; /* Is the resource active? */
    BUFRES_Args     args[NUMRES];      /* args for each resource */
    IRES_YieldFxn   yieldFxn;
    IRES_YieldArgs  yieldArgs;
} BUFALG_TI_Obj;


/* IALG Function Declarations */
extern Void BUFALG_TI_activate(IALG_Handle);

extern Int BUFALG_TI_alloc(const IALG_Params *, struct IALG_Fxns **,
        IALG_MemRec *);

extern Void BUFALG_TI_deactivate(IALG_Handle);

extern Int BUFALG_TI_free(IALG_Handle, IALG_MemRec *);

extern Int BUFALG_TI_initObj(IALG_Handle, const IALG_MemRec *, IALG_Handle,
        const IALG_Params *);

extern Void BUFALG_TI_moved(IALG_Handle, const IALG_MemRec *, IALG_Handle,
        const IALG_Params *);

extern Int BUFALG_TI_useBufs(IBUFALG_Handle handle);

#ifdef _cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres; 1, 0, 0,177; 12-1-2010 17:25:34; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

