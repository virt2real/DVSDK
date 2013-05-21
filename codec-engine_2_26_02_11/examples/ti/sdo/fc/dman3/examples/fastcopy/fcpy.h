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
 *  ======== fcpy.h ========
 *  This header defines all types, constants, and functions used by 
 *  clients of the FCPY algorithm.
 */
#ifndef FCPY_
#define FCPY_

#include <ti/sdo/fc/utils/api/alg.h>
#include <ifcpy.h>
#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*
 *  ======== FCPY_Cmd ========
 *  FCPY instance control commands.
 */
typedef IFCPY_Cmd FCPY_Cmd;

/* control commands */
#define FCPY_GETSTATUS IFCPY_GETSTATUS
#define FCPY_SETSTATUS IFCPY_SETSTATUS

/*
 *  ======== FCPY_Handle ========
 *  FCPY algorithm instance handle
 */
typedef struct IFCPY_Obj *FCPY_Handle;

/*
 *  ======== FCPY_Params ========
 *  FCPY algorithm instance creation parameters
 */
typedef IFCPY_Params FCPY_Params;

/*
 *  ======== FCPY_PARAMS ========
 *  Default interface parameters
 */
#define FCPY_PARAMS IFCPY_PARAMS

/*
 *  ======== FCPY_Status ========
 *  FCPY algorithm status parameters
 */
typedef IFCPY_Status FCPY_Status;

/*
 *  ======== FCPY_apply ========
 *  Apply a FCPY function to the input array and place results in the
 *  output array.
 */
extern Void FCPY_apply(FCPY_Handle handle, Void * in, Void * out);

/*
 *  ======== FCPY_create ========
 *  Create an instance of a FCPY object.
 */
static inline FCPY_Handle FCPY_create(const IFCPY_Fxns *fxns, const FCPY_Params *prms)
{
    return((FCPY_Handle)ALG_create((IALG_Fxns *)fxns, NULL, (IALG_Params *)prms));
}

/*
 *  ======== FCPY_control ========
 *  Used to either write to the read/write parameters in the status
 *  structure or to read all the parameters in the status structure.
 */
extern XDAS_Bool FCPY_control(FCPY_Handle handle, FCPY_Cmd cmd, FCPY_Status *status);

/*
 *  ======== FCPY_delete ========
 *  Delete a FCPY instance object
 */
static inline Void FCPY_delete(FCPY_Handle handle)
{
    ALG_delete((ALG_Handle)handle);
}

/*
 *  ======== FCPY_exit ========
 *  Module finalization
 */
extern Void FCPY_exit(Void);

/*
 *  ======== FCPY_init ========
 *  Module initialization
 */
extern Void FCPY_init(Void);

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif  /* FCPY_ */

/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

