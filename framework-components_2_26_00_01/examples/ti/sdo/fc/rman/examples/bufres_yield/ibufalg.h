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
 *  ======== ibufalg.h ========
 *  IBUFALG Interface Header
 *
 */
#ifndef ti_sdo_fc_rman_examples_bufres_yield_IBUFALG_
#define ti_sdo_fc_rman_examples_bufres_yield_IBUFALG_

#include <ti/xdais/ialg.h>

#define BUFALG_SOK      0
#define BUFALG_EFAIL    -1
#define BUFALG_EMEMORY  -2


/*
 *  ======== IBUFALG_HANDLE ========
 *  This handle is used to reference all BUFALG instance objects
 */
typedef struct IBUFALG_Obj *IBUFALG_Handle;

/*
 *  ======== IBUFALG_Obj ========
 *  This structure must be the first field of all BUFALG instance objects
 */
typedef struct IBUFALG_Obj {
    struct IBUFALG_Fxns *fxns;
} IBUFALG_Obj;

/*
 *  ======== IBUFALG_Cmd ========
 *  The Cmd enumeration defines the control commands for the BUFALG
 *  control method.
 */
typedef enum IBUFALG_Cmd {
    IBUFALG_GET,      /* Get command */
    IBUFALG_SET       /* Set command */
} IBUFALG_Cmd;

/*
 *  ======== IBUFALG_Params ========
 *  This structure defines the creation parameters for all BUFALG objects
 */
typedef struct IBUFALG_Params {
    Int size;           /* must be first field of all params structures */
} IBUFALG_Params;

/*
 *  ======== IBUFALG_PARAMS ========
 *  Default parameter values for BUFALG instance objects
 */
extern IBUFALG_Params IBUFALG_PARAMS;

/*
 *  ======== IBUFALG_Fxns ========
 *  This structure defines all of the operations on BUFALG objects
 */
typedef struct IBUFALG_Fxns {
    IALG_Fxns   ialg;    /* IBUFALG extends IALG */
    Int         (*useBufs)(IBUFALG_Handle handle, unsigned int fillValue,
            int taskId);
} IBUFALG_Fxns;

#endif
/*
 *  @(#) ti.sdo.fc.rman.examples.bufres_yield; 1, 0, 0,177; 12-1-2010 17:25:39; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

