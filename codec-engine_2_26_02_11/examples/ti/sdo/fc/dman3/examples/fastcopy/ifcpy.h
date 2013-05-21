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
 *  ======== ifcpy.h ========
 *  This header defines all types, constants, and functions shared by all
 *  implementations of the FCPY algorithm.
 */
#ifndef IFCPY_
#define IFCPY_

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>

#ifdef __cplusplus
extern "C" {
#endif /*__cplusplus*/

/*
 *  ======== IFCPY_Obj ========
 *  This structure must be the first field of all FCPY instance objects.
 */
typedef struct IFCPY_Obj {
    struct IFCPY_Fxns *fxns;
} IFCPY_Obj;

/*
 *  ======== IFCPY_Handle ========
 *  This handle is used to reference all FCPY instance objects.
 */
typedef struct IFCPY_Obj *IFCPY_Handle;

/*
 *  ======== IFCPY_Cmd ========
 *  This structure defines the control commands for the FCPY module. 
 */
typedef enum IFCPY_Cmd {
    IFCPY_GETSTATUS,
    IFCPY_SETSTATUS
} IFCPY_Cmd;

/*
 *  ======== IFCPY_Params ========
 *  This structure defines the creation parameters for all FCPY instance
 *  objects.
 */
typedef struct IFCPY_Params {
    Int  size;        /* Size of this structure */ 

    /* The following two parameters are read-only */    
    Int  srcLineLen;  /* Source line length (# of 8-bit elements) */
    Int  srcNumLines; /* Number of lines for source */
    
    /* The following parameters are read/write */    
    Int  srcStride;   /* Stride between lines for source */
    Int  dstLineLen;  /* Destination line length (# of 8-bit elements) */
    Int  dstNumLines; /* Number of lines for destination */
    Int  dstStride;   /* Stride between lines for destination */
} IFCPY_Params;

extern const IFCPY_Params IFCPY_PARAMS; /* default params */

/*
 *  ======== IFCPY_Status ========
 *  This structure defines the parameters that can be changed at runtime
 *  (read/write), and the instance status parameters (read-only).
 */
typedef struct IFCPY_Status {
    Int  size;            /* Size of this structure */ 
    
    /* The following two parameters are read-only */
    Int  srcLineLen;      /* Source line length (# of 8-bit elements) */
    Int  srcNumLines;     /* Number of lines for source */
    
    /* The following parameters are read/write */
    Int  srcStride;       /* Stride between lines for source */
    Int  dstLineLen;      /* Destination line length (# of 8-bit elements) */
    Int  dstNumLines;     /* Number of lines for destination */
    Int  dstStride;       /* Stride between lines for destination */
} IFCPY_Status;

/*
 *  ======== IFCPY_Fxns ========
 *  This structure defines all of the operations on FCPY objects.
 */
typedef struct IFCPY_Fxns {
    IALG_Fxns   ialg;    /* IFCPY extends IALG */
    XDAS_Bool  (*control)(IFCPY_Handle handle, IFCPY_Cmd cmd, 
        IFCPY_Status *status);
    Void       (*doCopy)(IFCPY_Handle handle, Void * in, Void * out);
} IFCPY_Fxns;

#ifdef __cplusplus
}
#endif /*__cplusplus*/

#endif  /* IFCPY_ */





/*
 *  @(#) ti.sdo.fc.dman3.examples.fastcopy; 1, 0, 0,235; 12-1-2010 17:24:30; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

