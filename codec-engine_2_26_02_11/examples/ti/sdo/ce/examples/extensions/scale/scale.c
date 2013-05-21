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
 *  ======== scale.c ========
 *  Scaling API, exposed to the application.
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server; the
 *  SCALE skeletons (scale_skel.c) call these API's to create instances on the
 *  remote CPU.
 */
#include <xdc/std.h>

#include <ti/xdais/ialg.h>
#include <ti/sdo/ce/visa.h>

#include <ti/sdo/ce/osal/Log.h>
#include <ti/sdo/ce/trace/gt.h>

#include "scale.h"
#include "_scale.h"

/* default params*/
SCALE_Params SCALE_PARAMS = {
   sizeof(SCALE_Params),
    1      /* default scale factor */
};

#define GTNAME "ti.sdo.ce.extensions.scale.SCALE"

static GT_Mask curTrace = {NULL,NULL};


/*
 *  ======== SCALE_create ========
 */
SCALE_Handle SCALE_create(Engine_Handle engine, String name,
    SCALE_Params *params)
{
    SCALE_Handle visa;
    static Bool curInit = FALSE;

    if (curInit != TRUE) {
        curInit = TRUE;
        GT_create(&curTrace, GTNAME);
    }

    GT_3trace(curTrace, GT_ENTER, "SCALE_create> "
        "Enter (engine=0x%x, name='%s', params=0x%x)\n",
        engine, name, params);

    if (params == NULL) {
        params = &SCALE_PARAMS;
    }

    visa = VISA_create(engine, name, (IALG_Params *)params,
        sizeof (_SCALE_Msg), "ti.sdo.ce.examples.extensions.scale.ISCALE");

    GT_1trace(curTrace, GT_ENTER, "SCALE_create> return (0x%x)\n", visa);

    return (visa);
}


/*
 *  ======== SCALE_delete ========
 */
Void SCALE_delete(SCALE_Handle handle)
{
    GT_1trace(curTrace, GT_ENTER, "SCALE_delete> Enter (handle=0x%x)\n",
        handle);

    VISA_delete(handle);

    GT_0trace(curTrace, GT_ENTER, "SCALE_delete> return\n");
}


/*
 *  ======== SCALE_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).
 */
XDAS_Int32 SCALE_process(SCALE_Handle handle, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, SCALE_InArgs *inArgs, SCALE_OutArgs *outArgs)
{
    XDAS_Int32 retVal = SCALE_EFAIL;

    GT_5trace(curTrace, GT_ENTER, "SCALE_process> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBuf, outBuf, inArgs, outArgs);

    if (handle) {
        ISCALE_Fxns *fxns =
            (ISCALE_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        ISCALE_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            /*
             * To better enable data visualization tooling, drop a
             * well-formed breadcrumb describing what we're doing.
             */
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"SCALE:process",
                (Arg)handle, (Arg)0);
            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inBuf, outBuf, inArgs, outArgs);
            VISA_exit((VISA_Handle)handle);
        }
    }

    GT_2trace(curTrace, GT_ENTER, "SCALE_process> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}


/*
 *  ======== SCALE_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* image decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 SCALE_control(SCALE_Handle handle, SCALE_Cmd id,
    SCALE_DynamicParams *params)
{
    XDAS_Int32 retVal = SCALE_EFAIL;

    GT_3trace(curTrace, GT_ENTER, "SCALE_control> "
        "Enter (handle=0x%x, id=%d, params=0x%x\n",
        handle, id, params);

    if (handle) {
        ISCALE_Fxns *fxns =
            (ISCALE_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        ISCALE_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            /*
             * To better enable data visualization tooling, drop a
             * well-formed breadcrumb describing what we're doing.
             */
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"SCALE:control",
                (Arg)handle, (Arg)0);
            VISA_enter((VISA_Handle)handle);
            retVal = fxns->control(alg, id, params);
            VISA_exit((VISA_Handle)handle);
        }
    }

    GT_2trace(curTrace, GT_ENTER, "SCALE_control> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1, 0, 0,261; 12-2-2010 21:23:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

