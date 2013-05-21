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
 *  ======== universal.c ========
 *  The XDM IUNIVERSAL-compliant algorithm APIs
 *
 *  The methods defined here must be independent of whether the underlying
 *  algorithm is executed locally or remotely.
 *
 *  In fact, these methods must exist on *both* the client and server;
 *  the UNIVERSAL skeletons (universal_skel.c) call these APIs
 *  to create instances on the remote CPU.
 */
#include <xdc/std.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/osal/Log.h>
#include <ti/sdo/utils/trace/gt.h>

#include <ti/xdais/ialg.h>
#include <ti/xdais/dm/iuniversal.h>

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "universal.h"
#include "_universal.h"

#define GTNAME "ti.sdo.ce.universal.UNIVERSAL"

GT_Mask ti_sdo_ce_universal_UNIVERSAL_curTrace = {NULL, NULL};
#define CURTRACE ti_sdo_ce_universal_UNIVERSAL_curTrace


/*
 *  ======== UNIVERSAL_create ========
 */
UNIVERSAL_Handle UNIVERSAL_create(Engine_Handle engine, String name,
    UNIVERSAL_Params *params)
{
    UNIVERSAL_Handle visa;
    static Bool curInit = FALSE;

    /* TODO:M  Race here!  Do we need ATM_Increment in our OSAL? */
    if (curInit != TRUE) {
        curInit = TRUE;
        GT_create(&CURTRACE, GTNAME);
    }

    GT_4trace(CURTRACE, GT_ENTER, "UNIVERSAL_create> "
        "Enter (engine=0x%x, name='%s', params=0x%x (size=0x%x))\n",
        engine, name, params, (params == NULL) ? 0 : params->size);

    visa = VISA_create(engine, name, (IALG_Params *)params,
        sizeof (_UNIVERSAL_Msg), "ti.sdo.ce.universal.IUNIVERSAL");

    GT_1trace(CURTRACE, GT_ENTER, "UNIVERSAL_create> return (0x%x)\n",visa);

    return (visa);
}


/*
 *  ======== UNIVERSAL_delete ========
 */
Void UNIVERSAL_delete(UNIVERSAL_Handle handle)
{
    GT_1trace(CURTRACE, GT_ENTER, "UNIVERSAL_delete> Enter (handle=0x%x)\n",
        handle);

    VISA_delete(handle);

    GT_0trace(CURTRACE, GT_ENTER, "UNIVERSAL_delete> return\n");
}


/*
 *  ======== UNIVERSAL_process ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* universal algs.
 */
XDAS_Int32 UNIVERSAL_process(UNIVERSAL_Handle handle,
        XDM1_BufDesc *inBufs, XDM1_BufDesc *outBufs, XDM1_BufDesc *inOutBufs,
        IUNIVERSAL_InArgs *inArgs, IUNIVERSAL_OutArgs *outArgs)
{
    XDAS_Int32 retVal = UNIVERSAL_EFAIL;

    UNIVERSAL_InArgs refInArgs;

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

    GT_6trace(CURTRACE, GT_ENTER, "UNIVERSAL_process> "
            "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inOutBufs=0x%x, "
            "inArgs=0x%x, outArgs=0x%x)\n",
            handle, inBufs, outBufs, inOutBufs, inArgs, outArgs);

    if (handle) {
        IUNIVERSAL_Fxns *fxns =
            (IUNIVERSAL_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IUNIVERSAL_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (fxns && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"UNIVERSAL:process",
                (Arg)handle, (Arg)0);

            if (checked) {

                /*
                 * Validate inBufs and outBufs.  Note that the IUNIVERSAL
                 * spec allows for NULL bufdescs - that's not an error.
                 */
                if (inBufs) {
                    XdmUtils_validateSparseBufDesc1(inBufs, "inBufs");
                }
                if (outBufs) {
                    XdmUtils_validateSparseBufDesc1(outBufs, "outBufs");
                }
                if (inOutBufs) {
                    XdmUtils_validateSparseBufDesc1(inOutBufs, "inOutBufs");
                }

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
            retVal = fxns->process(alg, inBufs, outBufs, inOutBufs, inArgs,
                    outArgs);
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

    GT_2trace(CURTRACE, GT_ENTER, "UNIVERSAL_process> "
            "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}


/*
 *  ======== UNIVERSAL_control ========
 *  This method must be the same for both local and remote invocation;
 *  each call site in the client might be calling different implementations
 *  (one that marshalls & sends and one that simply calls).  This API
 *  abstracts *all* universal algs.
 */
XDAS_Int32 UNIVERSAL_control(UNIVERSAL_Handle handle,
    IUNIVERSAL_Cmd id, UNIVERSAL_DynamicParams *dynParams,
    UNIVERSAL_Status *status)
{
    XDAS_Int32 retVal = UNIVERSAL_EFAIL;

    UNIVERSAL_DynamicParams refDynParams;
    XDAS_Int32 refStatusSize;
    XDAS_Int32 refStatusDataNumBufs;

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

    GT_6trace(CURTRACE, GT_ENTER, "UNIVERSAL_control> "
        "Enter (handle=0x%x, id=%d, dynParams=0x%x (size=0x%x), "
        "status=0x%x (size=0x%x)\n",
        handle, id, dynParams, dynParams->size, status, status->size);

    if (handle) {
        IUNIVERSAL_Fxns *fxns =
            (IUNIVERSAL_Fxns *)VISA_getAlgFxns((VISA_Handle)handle);
        IUNIVERSAL_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if ((fxns != NULL) && (alg != NULL)) {
            Log_printf(ti_sdo_ce_dvtLog, "%s", (Arg)"UNIVERSAL:control",
                (Arg)handle, (Arg)0);

            if (checked) {

                /*
                 * Make a reference copy of dynParams, status->size, and
                 * status->data.numBufs so we can check that the codec
                 * didn't modify these read-only fields during control().
                 */
                refDynParams = *dynParams;
                refStatusSize = status->size;
                refStatusDataNumBufs = status->data.numBufs;
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

                /* ensure the codec didn't change status->data.numBufs */
                if (status->data.numBufs != refStatusDataNumBufs) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only "
                        "status->data.numBufs field!\n", handle);
                }
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "UNIVERSAL_control> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.universal; 1, 0, 0,141; 12-2-2010 21:27:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

