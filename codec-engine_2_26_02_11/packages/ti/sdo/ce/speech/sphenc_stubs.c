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
 *  ======== sphenc_stubs.c ========
 *  This file contains an implemenation of the ISPHENC interface for the
 *  speech class of algorithms.
 *
 *  These functions are the "client-side" of a "remote" implementation.
 *
 */
#include <xdc/std.h>
#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/isphenc.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/utils/trace/gt.h>

#include <string.h>  /* for memcpy (TODO:L Should we introduce Memory_copy? */

#include "sphenc.h"
#include "_sphenc.h"

static XDAS_Int32 process(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs);
static XDAS_Int32 processAsync(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs);
static XDAS_Int32 processWait(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    UInt timeout);
static XDAS_Int32 control(ISPHENC_Handle h, ISPHENC_Cmd id,
    ISPHENC_DynamicParams *params, ISPHENC_Status *status);
static XDAS_Int32 marshallMsg(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    _SPHENC_Msg **pmsg);
static Void unmarshallMsg(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    _SPHENC_Msg *msg);


ISPHENC_Fxns SPHENC_STUBS = {
    {&SPHENC_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};

extern GT_Mask ti_sdo_ce_speech_SPHENC_curTrace;
#define CURTRACE ti_sdo_ce_speech_SPHENC_curTrace

/*
 *  ======== marshallMsg ========
 */
static XDAS_Int32 marshallMsg(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    _SPHENC_Msg **pmsg)
{
    XDAS_Int32 retVal = SPHENC_EOK;
    VISA_Handle visa = (VISA_Handle)h;
    _SPHENC_Msg *msg;
    Int i;
    ISPHENC_OutArgs *pMsgOutArgs;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((inArgs == NULL) || (inArgs->size < sizeof(ISPHENC_InArgs)) ||
        (outArgs == NULL) || (outArgs->size < sizeof(ISPHENC_OutArgs))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (SPHENC_EFAIL);
    }

    if (pmsg == NULL) {
        return (SPHENC_EFAIL);
    }

    /* make sure it'll all fit! */
    payloadSize = sizeof(VISA_MsgHeader) +
            (sizeof(msg->cmd.process.inBufs) * XDM_MAX_IO_BUFFERS) +
            sizeof(msg->cmd.process.numInBufs) +
            (sizeof(msg->cmd.process.inBufSizes[0]) * XDM_MAX_IO_BUFFERS) +
            (sizeof(msg->cmd.process.outBufs) * XDM_MAX_IO_BUFFERS) +
            sizeof(msg->cmd.process.numOutBufs) +
            (sizeof(msg->cmd.process.outBufSizes[0]) * XDM_MAX_IO_BUFFERS) +
            inArgs->size + outArgs->size;

    if (payloadSize > VISA_getMaxMsgSize(visa)) {
        /* Can't handle these large extended args. */
        GT_2trace(CURTRACE, GT_6CLASS,
                "process> invalid arguments - too big (0x%x > 0x%x).  "
                "Validate .size fields\n", payloadSize,
                VISA_getMaxMsgSize(visa));

        return (SPHENC_EFAIL);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_SPHENC_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (ISPHENC_ERUNTIME);
    }

    /*
     * Marshall the command: copy the client-passed arguments into flattened
     * message data structures, converting every pointer address to alg.
     * data buffer into physical address.
     */

    /* First specify the processing command that the skeleton should do */
    msg->visa.cmd = _SPHENC_CPROCESS;

    /* commentary follows for marshalling the inBufs argument: */

    /* 1) inBufs->numBufs is a plain integer, we just copy it */
    msg->cmd.process.numInBufs = inBufs->numBufs;

    /* 2) inBufs->bufSizes is an array of integers, we copy them all */
    for (i = 0; i < inBufs->numBufs; i++) {
        msg->cmd.process.inBufSizes[i] = inBufs->bufSizes[i];
    }

    /* 3) inBufs->bufs is a pointer to an array of pointers, so we take
     * individual pointers, convert them, and store in the the message
     * counterpart of inBufs->bufs
     */
    for (i = 0; i < inBufs->numBufs; i++) {
        msg->cmd.process.inBufs[i] = (XDAS_Int8 *)
            Memory_getBufferPhysicalAddress(inBufs->bufs[i],
                inBufs->bufSizes[i], NULL);

        if (msg->cmd.process.inBufs[i] == NULL) {
            retVal = SPHENC_ERUNTIME;
            goto exit;
        }
    }

    /* we're done (with inBufs). Because msg->cmd.process is non-cacheable
     * and contiguous (it has been allocated by MSGQ), we don't have to do
     * anything else.
     */

    /* Now we repeat the procedure for outBufs. Note that
     * inArgs and outArgs contain no pointers, so we can simply copy the
     * entire original structure, accounting for the first "size" field.
     */
    msg->cmd.process.numOutBufs = outBufs->numBufs;
    for (i = 0; i < outBufs->numBufs; i++) {
        msg->cmd.process.outBufSizes[i] = outBufs->bufSizes[i];
    }

    for (i = 0; i < outBufs->numBufs; i++) {
        msg->cmd.process.outBufs[i] = (XDAS_Int8 *)
            Memory_getBufferPhysicalAddress(outBufs->bufs[i],
                outBufs->bufSizes[i], NULL);

        if (msg->cmd.process.outBufs[i] == NULL) {
            retVal = SPHENC_ERUNTIME;
            goto exit;
        }
    }

    /* inArgs has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.process.inArgs), inArgs, inArgs->size);

    /* point at outArgs and set the "size" */
    pMsgOutArgs = (ISPHENC_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    /* set the size field - the rest is filled in by the codec */
    /* TODO:H probably want to zero out the rest of the outArgs struct */
    pMsgOutArgs->size = outArgs->size;

    *pmsg = msg;

    return (retVal);

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== unmarshallMsg ========
 */
static Void unmarshallMsg(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    _SPHENC_Msg *msg)
{
    VISA_Handle visa = (VISA_Handle)h;
    ISPHENC_OutArgs *pMsgOutArgs;

    /*
     * Do a wholesale replace of skeleton returned structure.
     */
    pMsgOutArgs = (ISPHENC_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    GT_assert(CURTRACE, pMsgOutArgs->size == outArgs->size);

    memcpy(outArgs, pMsgOutArgs, outArgs->size);

    /*
     * Note, we can keep the original outBufs, since speech
     * encoder codecs return buffers in order, and the caller's
     * outBufs already contains the virtual buffer pointers.
     *
     * Note also that we did *nothing* with inBufs nor inArgs.
     */

    VISA_freeMsg(visa, (VISA_Msg)msg);

    return;
}

/*
 *  ======== process ========
 *  This is the sync stub-implementation for the process method
 */
static XDAS_Int32 process(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _SPHENC_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBufs, outBufs, inArgs, outArgs, &msg);
    if (retVal != ISPHENC_EOK) {
        return retVal;
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /*
     * Regardless of return value, unmarshall outArgs.
     */
    unmarshallMsg(h, inBufs, outBufs, inArgs, outArgs, msg);

    return (retVal);
}

/*
 *  ======== processAsync ========
 *  This is the async stub-implementation for the process method
 */
static XDAS_Int32 processAsync(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _SPHENC_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBufs, outBufs, inArgs, outArgs, &msg);
    if (retVal != ISPHENC_EOK) {
        return retVal;
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_callAsync(visa, (VISA_Msg *)&msg);

    return (retVal);
}

/*
 *  ======== processWait ========
 */
static XDAS_Int32 processWait(ISPHENC_Handle h, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    UInt timeout)
{
    XDAS_Int32 retVal;
    _SPHENC_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    GT_assert(CURTRACE, !VISA_isLocal(visa));

    /* wait for completion of "last" message */
    retVal = VISA_wait(visa, (VISA_Msg *)&msg, timeout);

    /*
     * Unmarshall outArgs if there is a msg to unmarshall.
     */
    if (msg != NULL) {
        GT_assert(CURTRACE, msg->visa.cmd == _SPHENC_CPROCESS);

        unmarshallMsg(h, inBufs, outBufs, inArgs, outArgs, msg);
    }

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(ISPHENC_Handle h, ISPHENC_Cmd id,
         ISPHENC_DynamicParams *params, ISPHENC_Status *status)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _SPHENC_Msg *msg;
    ISPHENC_Status *pMsgStatus;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((params == NULL) || (params->size < sizeof(ISPHENC_DynamicParams)) ||
        (status == NULL) || (status->size < sizeof(ISPHENC_Status))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (SPHENC_EFAIL);
    }

    /* make sure it'll all fit! */
    payloadSize = sizeof(VISA_MsgHeader) + sizeof(id) + params->size +
            status->size;

    if (payloadSize > VISA_getMaxMsgSize(visa)) {
        /* Can't handle these large extended args. */
        GT_2trace(CURTRACE, GT_6CLASS,
                "process> invalid arguments - too big (0x%x > 0x%x).  "
                "Validate .size fields\n", payloadSize,
                VISA_getMaxMsgSize(visa));

        return (SPHENC_EFAIL);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_SPHENC_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (ISPHENC_ERUNTIME);
    }

    /* marshall the command */
    msg->visa.cmd = _SPHENC_CCONTROL;

    msg->cmd.control.id = id;

    /* params has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.control.params), params, params->size);

    /* unmarshall status based on the "size" of params */
    pMsgStatus = (ISPHENC_Status *)((UInt)(&(msg->cmd.control.params)) +
        params->size);

    /* set the size field - the rest is filled in by the codec */
    /* TODO:H probably want to zero out the rest of the status struct */
    pMsgStatus->size = status->size;

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* ensure we get CCONTROL msg (ensure async CPROCESS pipeline drained) */
    GT_assert(CURTRACE, msg->visa.cmd == _SPHENC_CCONTROL);

    /* unmarshall status */
    pMsgStatus = (ISPHENC_Status *)((UInt)(&(msg->cmd.control.params)) +
        params->size);

    if (VISA_isChecked()) {
        /* ensure codec didn't modify status->size */
        GT_assert(CURTRACE, pMsgStatus->size == status->size);
    }
    memcpy(status, pMsgStatus, status->size);

    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== SPHENC_processAsync ========
 */
XDAS_Int32 SPHENC_processAsync(SPHENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs)
{
    XDAS_Int32 retVal = SPHENC_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_5trace(CURTRACE, GT_ENTER, "SPHENC_processAsync> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBufs, outBufs, inArgs, outArgs);

    if (handle) {
        ISPHENC_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /*
                 * Zero out the outArgs struct (except for .size field);
                 * it's write-only to the codec, so the app shouldn't pass
                 * values through it, nor should the codec expect to
                 * receive values through it.
                 */
                memset((void *)((XDAS_Int32)(outArgs) + sizeof(outArgs->size)),
                    0, (sizeof(*outArgs) - sizeof(outArgs->size)));
            }

            retVal = processAsync(alg, inBufs, outBufs, inArgs, outArgs);
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "SPHENC_processAsync> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}

/*
 *  ======== SPHENC_processWait ========
 */
XDAS_Int32 SPHENC_processWait(SPHENC_Handle handle, XDM_BufDesc *inBufs,
    XDM_BufDesc *outBufs, ISPHENC_InArgs *inArgs, ISPHENC_OutArgs *outArgs,
    UInt timeout)
{
    XDAS_Int32 retVal = SPHENC_EFAIL;
    SPHENC_InArgs refInArgs;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_5trace(CURTRACE, GT_ENTER, "SPHENC_processWait> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBufs, outBufs, inArgs, outArgs);

    if (handle) {
        ISPHENC_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;
            }

            retVal = processWait(alg, inBufs, outBufs, inArgs, outArgs,
                    timeout);

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

    GT_2trace(CURTRACE, GT_ENTER, "SPHENC_processWait> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.speech; 1, 0, 2,416; 12-2-2010 21:25:17; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

