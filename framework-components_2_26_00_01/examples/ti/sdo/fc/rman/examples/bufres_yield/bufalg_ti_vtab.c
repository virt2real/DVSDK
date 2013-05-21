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
 *  ======== bufalg_ti_vtab.c ========
 *  Definition of BUFALG_TI_IBUFALG.
 *
 *  Since IBUFALG derives from IALG,we also define the sym
 *  BUFALG_TI_IALG, TI's implementation of the IALG interface.
 */

#include <xdc/std.h>

#include "ibufalg.h"
#include "bufalg_ti.h"
#include "bufalg_ti_priv.h"

#define IALGFXNS \
    &BUFALG_TI_IALG,        /* module ID */                     \
    BUFALG_TI_activate,     /* activate */                      \
    BUFALG_TI_alloc,        /* algAlloc */                      \
    BUFALG_TI_control,      /* control ops */                   \
    BUFALG_TI_deactivate,   /* deactivate */                    \
    BUFALG_TI_free,         /* free */                          \
    BUFALG_TI_initObj,      /* init */                          \
    NULL,                   /* moved (NULL => not suported) */  \
    BUFALG_TI_numAlloc      /* numAlloc (NULL => IALG_DEFMEMRECS) */\


/*
 *  ======== BUFALG_TI_IBUFALG ========
 *  This structure defines TI's implementation of the IBUFALG interface
 *  for the BUFALG_TI module.
 */
IBUFALG_Fxns BUFALG_TI_IBUFALG = {    /* module_vendor_interface */
    IALGFXNS,
    BUFALG_TI_useBufs
};

/*
 *  ======== BUFALG_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the BUFALG_TI module.
 */
asm("_BUFALG_TI_IALG .set _BUFALG_TI_IBUFALG");
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,177; 12-1-2010 17:25:39; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

