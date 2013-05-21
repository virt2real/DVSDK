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
 *  ======== template_ti.c ========
 *  This file contains an implementation of the ITEMPLATE_Fxns interface, for
 *  an audio decoder "copy" algorithm that uses the example BUFRES resource.
 *  This algorithm implements the IRES_Fxns to allow the resources it uses
 *  to be granted and used by the algorithm. The IRES_Fxns implementation
 *  is in its own source file, separate from this file.
 */
#include <xdc/std.h>
#include <string.h>

/* #include <ti/xdais/dm/itemplate.h>*/

#include <ti/xdais/ires.h>

/* This define is to avoid warnings generated due to unused static variable
   IRES_NULLRES_PROTOCOLREVISION from the file ires_nullres.h */  
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/nullresource/ires_nullres.h>

#include "template_ti.h"
#include "template_ti_priv.h"

#define TEMPLATE_IRES_VERSIONSTRING "1.00.00.0"

/* buffer definitions */
#define MININBUFS       1
#define MINOUTBUFS      1
#define MININBUFSIZE    1
#define MINOUTBUFSIZE   1

#define BUFRESSIZE 0x100
#define BUFRESALIGN 0x20

extern IALG_Fxns TEMPLATE_TI_IALG;

#define IALGFXNS  \
    &TEMPLATE_TI_IALG,   /* module ID */                         \
    NULL,               /* activate */                          \
    TEMPLATE_TI_alloc,   /* alloc */                             \
    NULL,               /* control (NULL => no control ops) */  \
    NULL,               /* deactivate */                        \
    TEMPLATE_TI_free,    /* free */                              \
    TEMPLATE_TI_initObj, /* init */                              \
    NULL,               /* moved */                             \
    NULL                /* numAlloc (NULL => IALG_MAXMEMRECS) */

static Void contextSave(IALG_Handle algHandle, Void *contextArgs);
static Void contextRestore(IALG_Handle algHandle, Void *contextArgs);

/*
 *  ======== TEMPLATE_TI_CODECIRES ========
 *  This structure defines TI's implementation of the ITEMPLATE interface
 *  for the TEMPLATE_TI module.
 */
ITEMPLATE_Fxns TEMPLATE_TI_CODECIRES = {    /* module_vendor_interface */
    {IALGFXNS},
    TEMPLATE_TI_process,
    TEMPLATE_TI_control,
};

/*
 *  ======== TEMPLATE_TI_IALG ========
 *  This structure defines TI's implementation of the IALG interface
 *  for the TEMPLATE_TI module.
 */
#ifdef xdc_target__isaCompatible_64P

asm("_TEMPLATE_TI_IALG .set _TEMPLATE_TI_CODECIRES");

#else

/*
 *  We duplicate the structure here to allow this code to be compiled and
 *  run on non-DSP platforms at the expense of unnecessary data space
 *  consumed by the definition below.
 */
IALG_Fxns TEMPLATE_TI_IALG = {      /* module_vendor_interface */
    IALGFXNS
};

#endif

ITEMPLATE_Params TEMPLATE_TI_PARAMS = {
    sizeof(ITEMPLATE_Params),
};

/*
 *  ======== TEMPLATE_TI_alloc ========
 */
/* ARGSUSED */
Int TEMPLATE_TI_alloc(const IALG_Params *algParams,
    IALG_Fxns **pf, IALG_MemRec memTab[])
{
    /* Request memory for my object */
    memTab[0].size = sizeof(TEMPLATE_TI_Obj);
    memTab[0].alignment = 0;
    memTab[0].space = IALG_EXTERNAL;
    memTab[0].attrs = IALG_PERSIST;

    return (1);
}

/*
 *  ======== TEMPLATE_TI_free ========
 */
/* ARGSUSED */
Int TEMPLATE_TI_free(IALG_Handle handle, IALG_MemRec memTab[])
{
    return (TEMPLATE_TI_alloc(NULL, NULL, memTab));
}

/*
 *  ======== TEMPLATE_TI_initObj ========
 */
/* ARGSUSED */
Int TEMPLATE_TI_initObj(IALG_Handle handle, const IALG_MemRec memTab[],
    IALG_Handle p, const IALG_Params *algParams)
{
    TEMPLATE_TI_Obj *obj = (TEMPLATE_TI_Obj *)handle;
    const ITEMPLATE_Params *params = (ITEMPLATE_Params *)algParams;

    /*
     * In lieu of xDM defined default params, use our codec-specific ones.
     * Note that these default values _should_ be documented in your algorithm
     * documentation so users know what to expect.
     */
    if (params == NULL) {
        params = &TEMPLATE_TI_PARAMS;
    }

    /* 
     * Also save the context save restore functions in the algorithm instance 
     * This can be done any time after the algorithm instance is created.
     * Not necessary to do it here 
     */ 
    (obj->yieldContext).contextSave = contextSave;
    (obj->yieldContext).contextRestore = contextRestore;
    (obj->yieldContext).contextArgs = &(obj->contextArgs);

    return (IALG_EOK);
}

/*
 *  ======== TEMPLATE_TI_process ========
 */
/* ARGSUSED */
Int TEMPLATE_TI_process(ITEMPLATE_Handle handle, ITEMPLATE_InArgs *inArgs, 
    ITEMPLATE_OutArgs *outArgs)
{
    /* Do something */
    /* Yield */
    /* Do something */
    return (ITEMPLATE_EOK);
}

/*
 *  ======== TEMPLATE_TI_control ========
 */
/* ARGSUSED */
Int TEMPLATE_TI_control(ITEMPLATE_Handle handle, ITEMPLATE_Cmd id,
    ITEMPLATE_DynamicParams *dynParams, ITEMPLATE_Status *status)
{
    return (ITEMPLATE_EOK);
}

/* ARGSUSED */
static Void contextSave(IALG_Handle algHandle, Void *contextArgs)
{
    /* TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)algHandle;*/
    /* TEMPLATE_TI_CtxtArgs *ctxt = (TEMPLATE_TI_CtxtArgs *)contextArgs;*/
    /* 
     * Add code here to save context of the algorithm object
     * Could involve something like copying scratch Memory contents into 
     * permanent etc
     * Contents will depend on where in algorithms execution it "yields" to  
     * another algorithm
     */ 
}

 
/* ARGSUSED */
static Void contextRestore(IALG_Handle algHandle, Void *contextArgs)
{
    /* TEMPLATE_TI_Obj  *alg = (TEMPLATE_TI_Obj *)algHandle;*/
    /* TEMPLATE_TI_CtxtArgs * ctxt = (TEMPLATE_TI_CtxtArgs *)contextArgs;*/
    /* 
     * Add code here to restore context of the algorithm object
     * During the yield of this algorithm, another algorithm ran and might have 
     * messed up the scratch state of this algorithm
     */
}
/*
 *  @(#) ti.sdo.fc.ires.examples.codecs.template; 1, 0, 0,170; 12-1-2010 17:25:09; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

