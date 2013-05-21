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
 *  ======== sphenc1_stubs.c ========
 *  This file contains an implemenation of the ISPHENC1 interface for the
 *  speech encoder class of algorithms.
 *
 *  These functions are the "client-side" of a "remote" implementation.
 *
 */
#include <xdc/std.h>
#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/isphenc1.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/utils/trace/gt.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include "sphenc1.h"
#include "_sphenc1.h"

static XDAS_Int32 process(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs);
static XDAS_Int32 processAsync(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs);
static XDAS_Int32 processWait(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs, UInt timeout);
static XDAS_Int32 control(ISPHENC1_Handle h, ISPHENC1_Cmd id,
    ISPHENC1_DynamicParams *params, ISPHENC1_Status *status);
static XDAS_Int32 marshallMsg(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs, _SPHENC1_Msg **pmsg);
static Void unmarshallMsg(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs, _SPHENC1_Msg *msg);


ISPHENC1_Fxns SPHENC1_STUBS = {
    {&SPHENC1_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};

extern GT_Mask ti_sdo_ce_speech1_SPHENC1_curTrace;
#define CURTRACE ti_sdo_ce_speech1_SPHENC1_curTrace

/*
 *  ======== marshallMsg ========
 */
static XDAS_Int32 marshallMsg(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs, _SPHENC1_Msg **pmsg)
{
    XDAS_Int32 retVal = ISPHENC1_EOK;
    VISA_Handle visa = (VISA_Handle)h;
    _SPHENC1_Msg *msg;
    ISPHENC1_OutArgs *pMsgOutArgs;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((inArgs == NULL) || (inArgs->size < sizeof(ISPHENC1_InArgs)) ||
            (outArgs == NULL) || (outArgs->size < sizeof(ISPHENC1_OutArgs))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (SPHENC1_EFAIL);
    }

    if (pmsg == NULL) {
        return (SPHENC1_EFAIL);
    }

    /* make sure it'll all fit! */
    payloadSize = sizeof(VISA_MsgHeader) + sizeof(*inBuf) + sizeof(*outBuf) +
            inArgs->size + outArgs->size;

    if (payloadSize > VISA_getMaxMsgSize(visa)) {
        /* Can't handle these large extended args. */
        GT_2trace(CURTRACE, GT_6CLASS,
                "process> invalid arguments - too big (0x%x > 0x%x).  "
                "Validate .size fields\n", payloadSize,
                VISA_getMaxMsgSize(visa));

        return (SPHENC1_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_SPHENC1_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (ISPHENC1_EFAIL);
    }

    /* zero out msg->cmd (not msg->visa!) */
    memset(&(msg->cmd), 0, sizeof(msg->cmd));

    /*
     * Marshall the command: copy the client-passed arguments into flattened
     * message data structures, converting every pointer address to alg.
     * data buffer into physical address.
     */

    /* First specify the processing command that the skeleton should do */
    msg->visa.cmd = _SPHENC1_CPROCESS;

    /* commentary follows for marshalling the inBuf argument: */

    /* 1) inBuf->bufSize is an integer, just copy it */
    msg->cmd.process.inBuf.bufSize = inBuf->bufSize;

    /*
     * 2) inBuf->buf is a pointer, so we convert it and store it
     * in the message
     */
    msg->cmd.process.inBuf.buf = (XDAS_Int8 *)
        Memory_getBufferPhysicalAddress(inBuf->buf,
            inBuf->bufSize, NULL);

    if (msg->cmd.process.inBuf.buf == NULL) {
        retVal = SPHENC1_EFAIL;
        goto exit;
    }

    /* Clear .accessMask; the local processor won't access this buf */
    inBuf->accessMask = 0;

    /* we're done (with inBuf).  Because msg->cmd.process is non-cacheable
     * and contiguous (it has been allocated by MSGQ), we don't have to do
     * anything else.
     */

    /* Now we repeat the procedure for outBuf. Note that
     * inArgs and outArgs contain no pointers, so we can simply copy the
     * entire original structure.
     */
    msg->cmd.process.outBuf.bufSize = outBuf->bufSize;

    msg->cmd.process.outBuf.buf = (XDAS_Int8 *)
        Memory_getBufferPhysicalAddress(outBuf->buf, outBuf->bufSize, NULL);

    if (msg->cmd.process.outBuf.buf == NULL) {
        retVal = SPHENC1_EFAIL;
        goto exit;
    }

    /* Clear .accessMask; the local processor won't access this buf */
    outBuf->accessMask = 0;

    /* inArgs has a pointer.  First, blindly copy all inArgs into the msg... */
    memcpy(&(msg->cmd.process.inArgs), inArgs, inArgs->size);

    /* ... then translate the single pointer if necessary */
    if (inArgs->data.buf != NULL) {
        msg->cmd.process.inArgs.data.buf = (XDAS_Int8 *)
            Memory_getBufferPhysicalAddress(inArgs->data.buf,
                inArgs->data.bufSize, NULL);
        if (msg->cmd.process.inArgs.data.buf == NULL) {
            retVal = ISPHENC1_EFAIL;
            goto exit;
        }

        /* Clear .accessMask; the local processor won't access this buf */
        inArgs->data.accessMask = 0;
    }

    /* point at outArgs and set the "size" */
    pMsgOutArgs = (ISPHENC1_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    /* set the size field - the rest is filled in by the codec */
    pMsgOutArgs->size = outArgs->size;

    *pmsg = msg;

    return retVal;

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return retVal;
}

/*
 *  ======== unmarshallMsg ========
 */
static Void unmarshallMsg(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs, _SPHENC1_Msg *msg)
{
    VISA_Handle visa = (VISA_Handle)h;
    ISPHENC1_OutArgs *pMsgOutArgs;

    /*
     * Do a wholesale replace of skeleton returned structure.
     */
    pMsgOutArgs = (ISPHENC1_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    if (VISA_isChecked()) {
        /* ensure the codec didn't change outArgs->size */
        GT_assert(CURTRACE, pMsgOutArgs->size == outArgs->size);
    }

    memcpy(outArgs, pMsgOutArgs, outArgs->size);

    /* outBuf->bufSize is an _out_ field (set by the alg) so copy it here. */
    outBuf->bufSize = msg->cmd.process.outBuf.bufSize;

    /*
     * Note, we can keep the original outBuf, since the caller's
     * outBuf already contains the virtual buffer pointers.
     *
     * Note also that we did *nothing* with inBuf nor inArgs.
     *
     * Note also that we _don't_ update inBuf->accessMask
     * or inArgs->data.accessMask.
     * That's accurate, since the local processor  _didn't_
     * access these buffers.
     */

    VISA_freeMsg(visa, (VISA_Msg)msg);

    return;
}

/*
 *  ======== process ========
 *  This is the sync stub-implementation for the process method
 */
static XDAS_Int32 process(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _SPHENC1_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBuf, outBuf, inArgs, outArgs, &msg);
    if (retVal != ISPHENC1_EOK) {
        return (retVal);
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* Regardless of return value, unmarshall outArgs. */
    unmarshallMsg(h, inBuf, outBuf, inArgs, outArgs, msg);

    return (retVal);
}

/*
 *  ======== processAsync ========
 *  This is the async stub-implementation for the process method
 */
static XDAS_Int32 processAsync(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _SPHENC1_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBuf, outBuf, inArgs, outArgs, &msg);
    if (retVal != ISPHENC1_EOK) {
        return retVal;
    }

    /* send the message to the skeleton without waiting for completion */
    retVal = VISA_callAsync(visa, (VISA_Msg *)&msg);

    return (retVal);
}

/*
 *  ======== processWait ========
 */
static XDAS_Int32 processWait(ISPHENC1_Handle h, XDM1_SingleBufDesc *inBuf,
    XDM1_SingleBufDesc *outBuf, ISPHENC1_InArgs *inArgs,
    ISPHENC1_OutArgs *outArgs, UInt timeout)
{
    XDAS_Int32 retVal;
    _SPHENC1_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    GT_assert(CURTRACE, !VISA_isLocal(visa));

    /* wait for completion of "last" message */
    retVal = VISA_wait(visa, (VISA_Msg *)&msg, timeout);

    /*
     * Unmarshall outArgs if there is a msg to unmarshall.
     */
    if (msg != NULL) {
        GT_assert(CURTRACE, msg->visa.cmd == _SPHENC1_CPROCESS);

        unmarshallMsg(h, inBuf, outBuf, inArgs, outArgs, msg);
    }

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(ISPHENC1_Handle h, ISPHENC1_Cmd id,
         ISPHENC1_DynamicParams *params, ISPHENC1_Status *status)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _SPHENC1_Msg *msg;
    ISPHENC1_Status *pMsgStatus;
    XDAS_Int8 *virtAddr = NULL;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((params == NULL) || (params->size < sizeof(ISPHENC1_DynamicParams)) ||
            (status == NULL) || (status->size < sizeof(ISPHENC1_Status))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (SPHENC1_EFAIL);
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

        return (SPHENC1_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_SPHENC1_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (ISPHENC1_EFAIL);
    }

    /* marshall the command */
    msg->visa.cmd = _SPHENC1_CCONTROL;

    msg->cmd.control.id = id;

    /* params has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.control.params), params, params->size);

    /* unmarshall status based on the "size" of params */
    pMsgStatus = (ISPHENC1_Status *)((UInt)(&(msg->cmd.control.params)) +
        params->size);

    /*
     * Initialize the .size and .data fields - the rest are filled in by
     * the codec.
     */
    pMsgStatus->size = status->size;

    if (status->data.buf != NULL) {
        pMsgStatus->data.bufSize = status->data.bufSize;

        /* save it for later */
        virtAddr = status->data.buf;

        pMsgStatus->data.buf = (XDAS_Int8 *)
            Memory_getBufferPhysicalAddress(status->data.buf,
                status->data.bufSize, NULL);

        if (pMsgStatus->data.buf == NULL) {
            retVal = ISPHENC1_EFAIL;
            goto exit;
        }
    }
    else {
        /* Place null into the msg so the skel knows it's invalid */
        pMsgStatus->data.buf = NULL;
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* ensure we get CCONTROL msg (ensure async CPROCESS pipeline drained) */
    GT_assert(CURTRACE, msg->visa.cmd == _SPHENC1_CCONTROL);

    /* unmarshall status */
    pMsgStatus = (ISPHENC1_Status *)((UInt)(&(msg->cmd.control.params)) +
        params->size);

    if (VISA_isChecked()) {
        /* ensure codec didn't modify status->size */
        GT_assert(CURTRACE, pMsgStatus->size == status->size);

        /*
         * TODO:L  Should we also check that pMsgStatus->data.buf is the same
         * after the call as before?
         */
    }

    memcpy(status, pMsgStatus, status->size);

    /*
     * And finally, restore status->data.buf to its original value.  Note that
     * this works even when status->data.buf was NULL because virtAddr is
     * initialized to NULL.
     *
     * While potentially more confusing, this is just as correct as
     * (and faster than!) calling Memory_getVirtualBuffer().
     */
    status->data.buf = virtAddr;

    /* Clear .accessMask; the local processor didn't access the buffer */
    status->data.accessMask = 0;

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== SPHENC1_processAsync ========
 */
XDAS_Int32 SPHENC1_processAsync(SPHENC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs)
{
    XDAS_Int32 retVal = SPHENC1_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_5trace(CURTRACE, GT_ENTER, "SPHENC1_processAsync> "
        "Enter (handle=0x%x, inBuf=0x%x, outBuf=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBuf, outBuf, inArgs, outArgs);

    if (handle) {
        ISPHENC1_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {

#if 0 /* Most will complain at this.  It's probably a different check level */
                /* validate inArgs with ranges. */
                if ((inArgs->nullTrafficChannel != ISPEECH1_NULLTRAFFICMODE_OFF)
                    && (inArgs->nullTrafficChannel !=
                        ISPEECH1_NULLTRAFFICMODE_ON)) {

                    GT_2trace(CURTRACE, GT_7CLASS,
                        "ERROR> app provided codec (0x%x) with out of range "
                        "inArgs->nullTrafficChannel field (0x%x)\n", alg,
                        inArgs->nullTrafficChannel);
                }
#endif

                /*
                 * Zero out the outArgs struct (except for .size field);
                 * it's write-only to the codec, so the app shouldn't pass
                 * values through it, nor should the codec expect to
                 * receive values through it.
                 */
                memset((void *)((XDAS_Int32)(outArgs) + sizeof(outArgs->size)),
                    0, (sizeof(*outArgs) - sizeof(outArgs->size)));
            }

            retVal = processAsync(alg, inBuf, outBuf, inArgs, outArgs);

            if (checked) {
#if 0 /* Most will complain at this.  It's probably a different check level */
                /* validate outArgs with ranges. */
                if ((outArgs->frameType != ISPHENC1_FTYPE_SPEECH)
                    && (outArgs->frameType != ISPHENC1_FTYPE_SIDFRAME)
                    && (outArgs->frameType != ISPHENC1_FTYPE_NODATA)) {

                    GT_2trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) provided out of range "
                        "outArgs->frameType (0x%x)\n", alg,
                        outArgs->frameType);
                }
#endif
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "SPHENC1_processAsync> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return retVal;
}

/*
 *  ======== SPHENC1_processWait ========
 */
XDAS_Int32 SPHENC1_processWait(SPHENC1_Handle handle,
    XDM1_SingleBufDesc *inBuf, XDM1_SingleBufDesc *outBuf,
    SPHENC1_InArgs *inArgs, SPHENC1_OutArgs *outArgs, UInt timeout)
{
    XDAS_Int32 retVal = SPHENC1_EFAIL;
    SPHENC1_InArgs refInArgs;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_5trace(CURTRACE, GT_ENTER, "SPHENC1_processWait> "
        "Enter (handle=0x%x, inBuf=0x%x, outBuf=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBuf, outBuf, inArgs, outArgs);

    if (handle) {
        ISPHENC1_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /*
                 * Make a reference copy of inArgs so we can check that
                 * the codec didn't modify them during process().
                 */
                refInArgs = *inArgs;
            }

            retVal = processWait(alg, inBuf, outBuf, inArgs, outArgs,
                    timeout);

            if (checked) {
                /* ensure the codec didn't modify the read-only inArgs */
                if (memcmp(&refInArgs, inArgs, sizeof(*inArgs)) != 0) {
                    GT_1trace(CURTRACE, GT_7CLASS,
                        "ERROR> codec (0x%x) modified read-only inArgs "
                        "struct!\n", alg);
                }
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "SPHENC1_processWait> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return retVal;
}
/*
 *  @(#) ti.sdo.ce.speech1; 1, 0, 1,276; 12-2-2010 21:25:22; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

