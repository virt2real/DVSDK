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
 *  ======== vidtranscode.c ========
 *  The XDM IVIDTRANSCODE-compliant video transcode API's
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server;
 *  the VIDTRANSCODE skeletons (vidtranscode_skel.c) call these API's
 *  to create instances on the remote CPU.
 */
#include <xdc/std.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/osal/Log.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividtranscode.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "vidtranscode.h"
#include "_vidtranscode.h"

#define GTNAME "ti.sdo.ce.vidtranscode.VIDTRANSCODE"

GT_Mask ti_sdo_ce_vidtranscode_VIDTRANSCODE_curTrace = {NULL, NULL};
#define CURTRACE ti_sdo_ce_vidtranscode_VIDTRANSCODE_curTrace


/*
 *  ======== VIDTRANSCODE_create ========
 */
VIDTRANSCODE_Handle VIDTRANSCODE_create(Engine_Handle engine, String name,
    VIDTRANSCODE_Params *params)
{
    VIDTRANSCODE_Handle visa;
    static Bool curInit = FALSE;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (curInit != TRUE) {
        curInit = TRUE;
        GT_create(&CURTRACE, GTNAME);
    }

    GT_3trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_create> "
        "Enter (engine=0x%x, name='%s', params=0x%x)\n",
        engine, name, params);

    visa = VISA_create(engine, name, (IALG_Params *)params,
        sizeof (_VIDTRANSCODE_Msg), "ti.sdo.ce.vidtranscode.IVIDTRANSCODE");

    GT_1trace(CURTRACE, GT_ENTER, "AUDENC_create> return (0x%x)\n", visa);

    return (visa);
}


/*
 *  ======== VIDTRANSCODE_delete ========
 */
Void VIDTRANSCODE_delete(VIDTRANSCODE_Handle handle)
{
    GT_1trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_delete> Enter (handle=0x%x)\n",
        handle);

    VISA_delete(handle);

    GT_0trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_delete> return\n");
}


/*
 *  ======== VIDTRANSCODE_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video transcoders (both high and low complexity
 *  transcoders are invoked using this method).
 */
XDAS_Int32 VIDTRANSCODE_process(VIDTRANSCODE_Handle handle,
    XDM1_BufDesc *inBufs, XDM_BufDesc *outBufs, IVIDTRANSCODE_InArgs *inArgs,
    IVIDTRANSCODE_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDTRANSCODE_EFAIL;

    VIDTRANSCODE_InArgs refInArgs;

    /*
     * Note, we assign "VISA_isChecked()" results to a local variable
     * rather than repeatedly query it throughout this fxn because
     * someday we may allow dynamically changing the global
     * 'VISA_isChecked()' value on the fly.  If we allow that, we need
     * to ensure the value stays consistent in the context of this
     * call.
     */
    Bool checked = VISA_isChecked();

    if (checked) {
        /* Ensure inArgs and outArgs are non-NULL, per the XDM spec */

        if ((!(XdmUtils_validateExtendedStruct(inArgs, sizeof(*inArgs),
                "inArgs"))) || (!(XdmUtils_validateExtendedStruct(outArgs,
                sizeof(*outArgs), "outArgs")))) {
            /* for safety, return here before dereferencing and crashing */
            return (retVal);
        }
    }

    GT_5trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_process> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBufs, outBufs, inArgs, outArgs);

    if (handle) {
        IVIDTRANSCODE_Fxns *fxns =
            (IVIDTRANSCODE_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDTRANSCODE_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDTRANSCODE:process",
                (Arg)handle, (Arg)0);

            if (checked) {
                /*
                 * Validate inBufs and outBufs.
                 */
                XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
                XdmUtils_validateSparseBufDesc(outBufs, "outBufs");

                /*
                 * Zero out the outArgs struct (except for .size field);
                 * it's write-only to the codec, so the app shouldn't pass
                 * values through it, nor should the codec expect to
                 * receive values through it.
                 */
                memset((void *)((XDAS_Int32)(outArgs) + sizeof(outArgs->size)),
                    0, (sizeof(*outArgs) - sizeof(outArgs->size)));

                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;
            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inBufs, outBufs, inArgs, outArgs);
            VISA_exit((VISA_Handle)handle);

            if (checked) {
                /* ensure the codec didn't modify the read-only inArgs */
                if (memcmp(&refInArgs, inArgs, sizeof(*inArgs)) != 0) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only inArgs "
                        "struct!\n", handle);
                }
            }

        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_process> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}


/*
 *  ======== VIDTRANSCODE_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video transcoders (both high and low complexity
 *  transcoders are invoked using this method).
 */
XDAS_Int32 VIDTRANSCODE_control(VIDTRANSCODE_Handle handle,
    IVIDTRANSCODE_Cmd id, VIDTRANSCODE_DynamicParams *dynParams,
    VIDTRANSCODE_Status *status)
{
    XDAS_Int32 retVal = VIDTRANSCODE_EFAIL;

    VIDTRANSCODE_DynamicParams refDynParams;
    XDAS_Int32 refStatusSize;
    XDAS_Int32 refStatusDataBufSize;

    /*
     * Note, we assign "VISA_isChecked()" results to a local variable
     * rather than repeatedly query it throughout this fxn because
     * someday we may allow dynamically changing the global
     * 'VISA_isChecked()' value on the fly.  If we allow that, we need
     * to ensure the value stays consistent in the context of this
     * call.
     */
    Bool checked = VISA_isChecked();

    if (checked) {
        /* Ensure dynParams and status are non-NULL, per the XDM spec */

        if ((!(XdmUtils_validateExtendedStruct(dynParams, sizeof(*dynParams),
                "dynParams"))) || (!(XdmUtils_validateExtendedStruct(status,
                sizeof(*status), "status")))) {
            /* for safety, return here before dereferencing and crashing */
            return (retVal);
        }
    }

    GT_6trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_control> "
        "Enter (handle=0x%x, id=%d, dynParams=0x%x (size=0x%x), "
        "status=0x%x (size=0x%x)\n",
        handle, id, dynParams, dynParams->size, status, status->size);

    if (handle) {
        IVIDTRANSCODE_Fxns *fxns =
            (IVIDTRANSCODE_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDTRANSCODE_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDTRANSCODE:control",
                (Arg)handle, (Arg)0);

            if (checked) {

                /*
                 * Make a reference copy of dynParams, status->size, and
                 * status->data.bufSize so we can check that the codec
                 * didn't modify these read-only fields during control().
                 */
                refDynParams = *dynParams;
                refStatusSize = status->size;
                refStatusDataBufSize = status->data.bufSize;
            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->control(alg, id, dynParams, status);
            VISA_exit((VISA_Handle)handle);

            if (checked) {
                /* ensure the codec didn't modify the read-only dynParams */
                if (memcmp(&refDynParams, dynParams, sizeof(*dynParams)) != 0) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only dynParams "
                        "struct!\n", handle);
                }

                /* ensure the codec didn't change status->size */
                if (status->size != refStatusSize) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only status->size "
                        "field!\n", handle);
                }

                /* ensure the codec didn't change status->data.bufSize */
                if (status->data.bufSize != refStatusDataBufSize) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only "
                        "status->data.bufSize field!\n", handle);
                }
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDTRANSCODE_control> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.vidtranscode; 1, 0, 1,227; 12-2-2010 21:28:33; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

