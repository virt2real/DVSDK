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
 *  ======== iscale.h ========
 *  The scale interface.
 */

#ifndef codecs_scale_ISCALE_H_
#define codecs_scale_ISCALE_H_

#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h>

#define ISCALE_EOK      0
#define ISCALE_EFAIL    -1
#define ISCALE_ERUNTIME -2

/**
 *  @brief      This must be the first field of all ISCALE instance objects.
 */
typedef struct ISCALE_Obj {
    struct ISCALE_Fxns *fxns;
} ISCALE_Obj;

/**
 *  @brief      Opaque handle to an ISCALE object.
 */
typedef struct ISCALE_Obj *ISCALE_Handle;


typedef struct ISCALE_Params {
    XDAS_Int32 size;                /* size of this structure, in bytes */
    XDAS_Int32 initialScaleFactor;  /* default scaling factor */
} ISCALE_Params;

typedef struct ISCALE_InArgs {
    XDAS_Int32 inBufSize;
    XDAS_Int32 outBufSize;
    XDAS_Int32 inBufValidBytes;
} ISCALE_InArgs;

typedef struct ISCALE_OutArgs {
    XDAS_Int32 outBufValidBytes;
} ISCALE_OutArgs;

typedef IALG_Cmd ISCALE_Cmd;

#define ISCALE_SETPARAMS 0       /* only cmd we support */

typedef struct ISCALE_DynamicParams {
    XDAS_Int32 scaleFactor;     /* we only scale up */
} ISCALE_DynamicParams;

typedef struct ISCALE_Fxns{
    IALG_Fxns   ialg;
    XDAS_Int32 (*process)(ISCALE_Handle handle, XDAS_Int8 *inBuf,
        XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs);
    XDAS_Int32 (*control)(ISCALE_Handle handle, ISCALE_Cmd id,
        ISCALE_DynamicParams *params);
} ISCALE_Fxns;


#ifdef __cplusplus
}
#endif

/*@}*/  /* ingroup */

#endif
/*
 *  @(#) ti.sdo.ce.examples.codecs.scale; 1, 0, 0,261; 12-2-2010 21:22:23; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

