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
 *  ======== fcpy_ti_ialgvt.c ========
 *  This file contains the function table definitions for the
 *  IALG and IFCPY interfaces implemented by the FCPY_TI module.
 */

#include <xdc/std.h>

#include "fcpy_ti.h"
#include "ifcpy.h"
#include "fcpy_ti_priv.h"

#define IALGFXNS \
    &FCPY_TI_IALG,     /* module ID */                         \
    NULL,              /* activate (NULL => no need to initialize buffers */ \
    FCPY_TI_alloc,     /* alloc */                             \
    NULL,              /* control (NULL => no control ops) */  \
    NULL,              /* deactivate (NULL => no need to save data */ \
    FCPY_TI_free,      /* free */                              \
    FCPY_TI_initObj,   /* init */                              \
    FCPY_TI_moved,     /* moved */                             \
    NULL               /* numAlloc (NULL => IALG_MAXMEMRECS) */

/*
 *  ======== FCPY_TI_IFCPY ========
 *  This structure defines TI's implementation of the IFCPY interface
 *  for the FCPY_TI module.
 */
IFCPY_Fxns FCPY_TI_IFCPY = {       /* module_vendor_interface */
    IALGFXNS,                      /* IALG functions */    
    FCPY_TI_control,               /* Control function */
    FCPY_TI_doCopy                 /* The fcpy fxn */
};

/* Overlay v-tables to save data space */
asm("_FCPY_TI_IALG  .set _FCPY_TI_IFCPY");

/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

