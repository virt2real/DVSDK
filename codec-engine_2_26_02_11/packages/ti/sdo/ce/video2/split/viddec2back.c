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
 *  ======== viddec2.c ========
 *  The xDM split IVIDDEC2 compliant video decode API's
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server; the
 *  VIDDEC2 skeletons (viddec2_skel.c) call these API's to create instances on
 *  the remote CPU.
 */
#include <xdc/std.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/osal/Log.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/split/ividdec2.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "viddec2.h"
#include "_viddec2back.h"

#define GTNAME "ti.sdo.ce.video2.split.VIDDEC2"

GT_Mask ti_sdo_ce_video2_split_VIDDEC2BACK_curTrace = {NULL, NULL};
#define CURTRACE ti_sdo_ce_video2_split_VIDDEC2BACK_curTrace


/*
 *  ======== VIDDEC2BACK_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 VIDDEC2BACK_control(VIDDEC2BACK_Handle handle,
        XDM_Context *context, VIDDEC2_Status *status)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    XDAS_Int32 refStatusSize;
    XDAS_Int32 refStatusDataBufSize;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_4trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_control> "
        "Enter (handle=0x%x, context=0x%x, "
        "status=0x%x (size=0x%x)\n",
        handle, context, status, status->size);

    if (handle) {
        IVIDDEC2BACK_Fxns *fxns =
            (IVIDDEC2BACK_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDDEC2BACK_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDDEC2BACK:control",
                (Arg)handle, (Arg)0);

            if (checked) {
                /*
                 * Make a reference copy of params, status->size, and
                 * status->data.bufSize so we can check that the codec
                 * didn't modify these read-only fields during control().
                 */
                refStatusSize = status->size;
                refStatusDataBufSize = status->data.bufSize;
            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->control(alg, context, status);
            VISA_exit((VISA_Handle)handle);

            if (checked) {

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

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_control> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}


/*
 *  ======== VIDDEC2BACK_create ========
 */
VIDDEC2BACK_Handle VIDDEC2BACK_create(Engine_Handle engine, String name,
    VIDDEC2_Params *params)
{
    VIDDEC2BACK_Handle visa;
    static Bool curInit = FALSE;

    if (curInit != TRUE) {
        curInit = TRUE;
        GT_create(&CURTRACE, GTNAME);
    }

    GT_3trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_create> "
        "Enter (engine=0x%x, name='%s', params=0x%x)\n",
        engine, name, params);

    visa = VISA_create(engine, name, (IALG_Params *)params,
            sizeof (_VIDDEC2BACK_Msg), "ti.sdo.ce.video2.split.IVIDDEC2BACK");

    GT_1trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_create> return (0x%x)\n", visa);

    return (visa);
}


/*
 *  ======== VIDDEC2BACK_delete ========
 */
Void VIDDEC2BACK_delete(VIDDEC2_Handle handle)
{
    GT_1trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_delete> Enter (handle=0x%x)\n",
            handle);

    VISA_delete(handle);

    GT_0trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_delete> return\n");
}


/*
 *  ======== VIDDEC2BACK_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 VIDDEC2BACK_process(VIDDEC2BACK_Handle handle,
        XDM_Context *context, VIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_3trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_process> "
            "Enter (handle=0x%x, context=0x%x, outArgs=0x%x)\n",
            handle, context, outArgs);

    if (handle) {
        IVIDDEC2BACK_Fxns *fxns =
            (IVIDDEC2BACK_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDDEC2BACK_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDDEC2BACK:process",
                (Arg)handle, (Arg)0);

            if (checked) {

                /*
                 * Validate inBufs and outBufs.
                 */
//                XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
//                XdmUtils_validateSparseBufDesc(outBufs, "outBufs");

            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, context, outArgs);
            VISA_exit((VISA_Handle)handle);

            if (checked) {
                /* TBD */
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_process> "
            "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,165; 12-2-2010 21:28:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

