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
 *  ======== viddec1.c ========
 *  The XDM IVIDDEC1-compliant video decode APIs
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server; the
 *  VIDDEC1 skeletons (viddec1_skel.c) call these API's to create instances on
 *  the remote CPU.
 */
#include <xdc/std.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/osal/Log.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/ividdec1.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "viddec1.h"
#include "_viddec1.h"

#define GTNAME "ti.sdo.ce.video1.VIDDEC1"

GT_Mask ti_sdo_ce_video1_VIDDEC1_curTrace = {NULL, NULL};
#define CURTRACE ti_sdo_ce_video1_VIDDEC1_curTrace


/*
 *  ======== VIDDEC1_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 VIDDEC1_control(VIDDEC1_Handle handle, VIDDEC1_Cmd id,
    VIDDEC1_DynamicParams *dynParams, VIDDEC1_Status *status)
{
    XDAS_Int32 retVal = VIDDEC1_EFAIL;

    VIDDEC1_DynamicParams refDynParams;
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

    GT_6trace(CURTRACE, GT_ENTER, "VIDDEC1_control> "
        "Enter (handle=0x%x, id=%d, dynParams=0x%x (size=0x%x), "
        "status=0x%x (size=0x%x)\n",
        handle, id, dynParams, dynParams->size, status, status->size);

    if (handle) {
        IVIDDEC1_Fxns *fxns =
            (IVIDDEC1_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDDEC1_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if ((fxns != NULL) && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDDEC1:control",
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

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC1_control> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}


/*
 *  ======== VIDDEC1_create ========
 */
VIDDEC1_Handle VIDDEC1_create(Engine_Handle engine, String name,
    VIDDEC1_Params *params)
{
    VIDDEC1_Handle visa;
    static Bool curInit = FALSE;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (curInit != TRUE) {
        curInit = TRUE;
        GT_create(&CURTRACE, GTNAME);
    }

    GT_3trace(CURTRACE, GT_ENTER, "VIDDEC1_create> "
        "Enter (engine=0x%x, name='%s', params=0x%x)\n",
        engine, name, params);

    visa = VISA_create(engine, name, (IALG_Params *)params,
        sizeof (_VIDDEC1_Msg), "ti.sdo.ce.video1.IVIDDEC1");

    GT_1trace(CURTRACE, GT_ENTER, "VIDDEC1_create> return (0x%x)\n", visa);

    return (visa);
}


/*
 *  ======== VIDDEC1_delete ========
 */
Void VIDDEC1_delete(VIDDEC1_Handle handle)
{
    GT_1trace(CURTRACE, GT_ENTER, "VIDDEC1_delete> Enter (handle=0x%x)\n",
        handle);

    VISA_delete(handle);

    GT_0trace(CURTRACE, GT_ENTER, "VIDDEC1_delete> return\n");
}


/*
 *  ======== VIDDEC1_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* video decoders (both high and low complexity
 *  decoders are envoked using this method).
 */
XDAS_Int32 VIDDEC1_process(VIDDEC1_Handle handle, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC1_InArgs *inArgs, VIDDEC1_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDDEC1_EFAIL;

    VIDDEC1_InArgs refInArgs;
    Int32 i;

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

    GT_5trace(CURTRACE, GT_ENTER, "VIDDEC1_process> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBufs, outBufs, inArgs, outArgs);

    GT_4trace(CURTRACE, GT_4CLASS, "VIDDEC1_process inArgs> (size=0x%x, "
            "numBytes=0x%x, inputID=0x%x) outArgs> (size=0x%x)\n", inArgs->size, inArgs->numBytes,
            inArgs->inputID, outArgs->size);

    if (handle) {
        IVIDDEC1_Fxns *fxns =
            (IVIDDEC1_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IVIDDEC1_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if ((fxns != NULL) && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"VIDDEC1:process",
                (Arg)handle, (Arg)0);

            if (checked) {

                /* validate inArgs with ranges. */
                if (inArgs->inputID == 0) {

                    GT_2trace(CURTRACE, GT_7CLASS,
                        "ERROR> app provided codec (0x%x) with out of range "
                        "inArgs->inputID field (0x%x)\n", alg, inArgs->inputID);
                }

                /*
                 * Validate inBufs and outBufs.
                 */
                XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
                XdmUtils_validateSparseBufDesc(outBufs, "outBufs");

                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;

                /* inArgs->inputID == 0 is an application error */
                if (inArgs->inputID == 0) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) received invalid "
                        "inArgs->inputID == 0!\n", handle);
                }
            }

            VISA_enter((VISA_Handle)handle);
            retVal = fxns->process(alg, inBufs, outBufs, inArgs, outArgs);
            VISA_exit((VISA_Handle)handle);

            GT_4trace(CURTRACE, GT_4CLASS, "VIDDEC1_process outArgs> "
                    "(size=0x%x, bytesConsumed=0x%x, ..., outputMbDataID=0x%x "
                    "..., outBufsInUseFlag=%d)\n", outArgs->size,
                    outArgs->bytesConsumed, outArgs->outputMbDataID,
                    outArgs->outBufsInUseFlag);

            if (checked) {
                /* ensure the codec didn't modify the read-only inArgs */
                if (memcmp(&refInArgs, inArgs, sizeof(*inArgs)) != 0) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only inArgs "
                        "struct!\n", handle);
                }

                /* only check these on successful return */
                if ((retVal == IVIDDEC1_EOK) || (!(XDM_ISFATALERROR(
                        outArgs->decodedBufs.extendedError)))) {
                    /* Validate outArgs->decodedBufs */
                    XdmUtils_validateVideo1BufDesc(&(outArgs->decodedBufs),
                            "decodedBufs");
                }

                /* Validate outArgs->displayBufs */
                for (i = 0; ((outArgs->outputID[i] != 0) &&
                        (i < XDM_MAX_IO_BUFFERS)); i++) {

                    if ((retVal == IVIDDEC1_EOK) ||
                            (!(XDM_ISFATALERROR(outArgs->
                            displayBufs[i].extendedError)))) {
                        XdmUtils_validateVideo1BufDesc(&(outArgs->displayBufs[i]),
                                "displayBufs");
                    }
                }
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC1_process> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.video1; 1, 0, 2,269; 12-2-2010 21:28:27; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

