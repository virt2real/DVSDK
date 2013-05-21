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
 *  ======== viddec2_stubs.c ========
 *  This file contains an implemenation of the IVIDDEC2 interface for the
 *  video decoder class of algorithms.
 *
 *  These functions are the "client-side" of a "remote" implementation.
 *
 */
#include <xdc/std.h>
#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/ividdec2.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/utils/trace/gt.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "viddec2.h"
#include "_viddec2.h"

static XDAS_Int32 process(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs);
static XDAS_Int32 processAsync(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs);
static XDAS_Int32 processWait(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs,
    UInt timeout);
static XDAS_Int32 control(IVIDDEC2_Handle h, IVIDDEC2_Cmd id,
    IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status);
static XDAS_Int32 marshallMsg(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs,
    _VIDDEC2_Msg **pmsg);
static XDAS_Int32 unmarshallMsg(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs,
    _VIDDEC2_Msg *msg, XDAS_Int32 retVal);


IVIDDEC2_Fxns VIDDEC2_STUBS = {
    {&VIDDEC2_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};

extern GT_Mask ti_sdo_ce_video2_VIDDEC2_curTrace;
#define CURTRACE ti_sdo_ce_video2_VIDDEC2_curTrace

/*
 *  ======== marshallMsg ========
 */
static XDAS_Int32 marshallMsg(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs,
    _VIDDEC2_Msg **pmsg)
{
    XDAS_Int32 retVal = IVIDDEC2_EOK;
    VISA_Handle visa = (VISA_Handle)h;
    _VIDDEC2_Msg *msg;
    Int i;
    IVIDDEC2_OutArgs *pMsgOutArgs;
    Int numBufs;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((inArgs == NULL) || (inArgs->size < sizeof(IVIDDEC2_InArgs)) ||
        (outArgs == NULL) || (outArgs->size < sizeof(IVIDDEC2_OutArgs))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (IVIDDEC2_EFAIL);
    }

    if (pmsg == NULL) {
        return (IVIDDEC2_EFAIL);
    }

    /* make sure it'll all fit! */
    payloadSize = sizeof(VISA_MsgHeader) + (sizeof(*inBufs)) +
            (sizeof(outBufs[0]) * XDM_MAX_IO_BUFFERS) +
            sizeof(msg->cmd.process.numOutBufs) +
            (sizeof(msg->cmd.process.outBufSizes[0]) * XDM_MAX_IO_BUFFERS) +
            inArgs->size + outArgs->size;

    if (payloadSize > VISA_getMaxMsgSize(visa)) {
        /* Can't handle these large extended args. */
        GT_2trace(CURTRACE, GT_6CLASS,
                "process> invalid arguments - too big (0x%x > 0x%x).  "
                "Validate .size fields\n", payloadSize,
                VISA_getMaxMsgSize(visa));

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_VIDDEC2_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (IVIDDEC2_EFAIL);
    }

    /* zero out msg->cmd (not msg->visa!) */
    memset(&(msg->cmd), 0, sizeof(msg->cmd));

    /*
     * Marshall the command: copy the client-passed arguments into flattened
     * message data structures, converting every pointer address to alg.
     * data buffer into physical address.
     */

    /* First specify the processing command that the skeleton should do */
    msg->visa.cmd = _VIDDEC2_CPROCESS;

    /* commentary follows for marshalling the inBufs argument: */

    /* 1) inBufs->numBufs is a plain integer, we just copy it */
    msg->cmd.process.inBufs.numBufs = inBufs->numBufs;

    /*
     * 2) inBufs->bufSizes is a sparse array of integers, we copy them all.
     *
     * 3) inBufs->bufs is a pointer to a sparse array of pointers, so we take
     * individual pointers, convert them if non-NULL, and store them in the
     * message counterpart of inBufs->bufs.
     */
    for (i = 0, numBufs = 0;
         ((numBufs < inBufs->numBufs) && (i < XDM_MAX_IO_BUFFERS)); i++) {
        if (inBufs->descs[i].buf != NULL) {
            /* valid member of sparse array, convert it */
            msg->cmd.process.inBufs.descs[i].bufSize = inBufs->descs[i].bufSize;

            msg->cmd.process.inBufs.descs[i].buf = (XDAS_Int8 *)
                Memory_getBufferPhysicalAddress(inBufs->descs[i].buf,
                    inBufs->descs[i].bufSize, NULL);

            if (msg->cmd.process.inBufs.descs[i].buf == NULL) {
                retVal = IVIDDEC2_EFAIL;
                goto exit;
            }

            /* Clear .accessMask; the local processor won't access this buf */
            inBufs->descs[i].accessMask = 0;

            /* found, and handled, another buffer. */
            numBufs++;
        }
        else {
            /* empty member of sparse array, no conversion needed. */
            msg->cmd.process.inBufs.descs[i].bufSize = 0;
            msg->cmd.process.inBufs.descs[i].buf = NULL;
        }
    }

    if (VISA_isChecked()) {
        /* check that we found inBufs->numBufs pointers in inBufs->bufs[] */
        GT_assert(CURTRACE, inBufs->numBufs == numBufs);
    }

    /* we're done (with inBufs). Because msg->cmd.process is non-cacheable
     * and contiguous (it has been allocated by MSGQ), we don't have to do
     * anything else.
     */

    /* Now we repeat the procedure for outBufs. Note that
     * inArgs contains no pointers, so we can simply copy the
     * entire original structure, accounting for the first "size" field.
     */
    msg->cmd.process.numOutBufs = outBufs->numBufs;

    for (i = 0, numBufs = 0;
         ((numBufs < outBufs->numBufs) && (i < XDM_MAX_IO_BUFFERS)); i++) {

        if (outBufs->bufs[i] != NULL) {
            /* valid member of sparse array, convert it */
            msg->cmd.process.outBufSizes[i] = outBufs->bufSizes[i];

            msg->cmd.process.outBufs[i] = (XDAS_Int8 *)
                Memory_getBufferPhysicalAddress(outBufs->bufs[i],
                    outBufs->bufSizes[i], NULL);

            if (msg->cmd.process.outBufs[i] == NULL) {
                /* TODO:M - should add at least a trace statement when trace
                 * is supported.  Another good idea is to return something
                 * more clear than EFAIL.
                 */
                retVal = IVIDDEC2_EFAIL;
                goto exit;
            }

            /* found, and handled, another buffer. */
            numBufs++;
        }
        else {
            /* empty member of sparse array, no conversion needed */
            msg->cmd.process.outBufSizes[i] = 0;
            msg->cmd.process.outBufs[i] = NULL;
        }
    }

    if (VISA_isChecked()) {
        /* check that we found outBufs->numBufs pointers in outBufs->bufs[] */
        GT_assert(CURTRACE, outBufs->numBufs == numBufs);
    }

    /* inArgs has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.process.inArgs), inArgs, inArgs->size);

    /* point at outArgs and set the "size" */
    pMsgOutArgs = (IVIDDEC2_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
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
static XDAS_Int32 unmarshallMsg(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs,
    _VIDDEC2_Msg *msg, XDAS_Int32 retVal)
{
    VISA_Handle visa = (VISA_Handle)h;
    Int i, j;
    IVIDDEC2_OutArgs *pMsgOutArgs;
    Int numBufs;

    /*
     * Do a wholesale replace of skeleton returned structure.
     * Pointer conversion of fields in outArgs is done below (only
     * in the case of a successful return value).
     */
    pMsgOutArgs = (IVIDDEC2_OutArgs *)((UInt)(&(msg->cmd.process.inArgs)) +
        inArgs->size);

    if (VISA_isChecked()) {
        /* ensure the codec didn't change outArgs->size */
        GT_assert(CURTRACE, pMsgOutArgs->size == outArgs->size);
    }

    memcpy(outArgs, pMsgOutArgs, outArgs->size);

    /* If VISA_call was successful, unmarshall the necessary buffers. */
    if (retVal == IVIDDEC2_EOK) {
        /* unmarshall the output data: outBufs and mbDataBuf. */

        if (VISA_isChecked()) {
            /* ensure the codec didn't send back "too many" buffers */
            GT_assert(CURTRACE,
                    msg->cmd.process.numOutBufs < XDM_MAX_IO_BUFFERS);
        }

        /* The outBufs may have changed, so don't rely on what was passed in */
        outBufs->numBufs = msg->cmd.process.numOutBufs;

        for (i = 0, numBufs = 0;
             ((numBufs < outBufs->numBufs) && (i < XDM_MAX_IO_BUFFERS)); i++) {

            if (msg->cmd.process.outBufs[i] != NULL) {
                /* valid member of sparse array, convert it */
                outBufs->bufSizes[i] = msg->cmd.process.outBufSizes[i];

                outBufs->bufs[i] = (XDAS_Int8 *)
                    Memory_getBufferVirtualAddress(
                        (UInt32)msg->cmd.process.outBufs[i],
                        outBufs->bufSizes[i]);

                if (outBufs->bufs[i] == NULL) {
                    /* TODO:M - should add at least a trace statement when trace
                     * is supported.  Another good idea is to return something
                     * more clear than EFAIL.
                     */
                    retVal = IVIDDEC2_EFAIL;
                    goto exit;
                }

                /* found, and handled, another buffer. */
                numBufs++;
            }
            else {
                /* empty member of sparse array, no conversion needed */
                outBufs->bufSizes[i] = 0;
                outBufs->bufs[i] = NULL;
            }
        }

        /* convert mbDataBuf */
        if (outArgs->mbDataBuf.buf != NULL) {
            Memory_getBufferVirtualAddress((UInt32)outArgs->mbDataBuf.buf,
                outArgs->mbDataBuf.bufSize);

            /* Clear .accessMask; the local processor didn't access this buf */
            outArgs->mbDataBuf.accessMask = 0;
        }

    }

    /*
     * Note that buffers can also be returned if IVIDDEC_EFAIL is returned
     * with a non-fatal .extendedError in displayBufs[] and decodedBufs.
     */

    /* address translate the decoded buffers if non-fatal error */
    if ((retVal == IVIDDEC2_EOK) ||
            (!(XDM_ISFATALERROR(outArgs->decodedBufs.extendedError)))) {
        for (i = 0; i < IVIDEO_MAX_YUV_BUFFERS; i++) {
            if (outArgs->decodedBufs.bufDesc[i].buf != NULL) {
                outArgs->decodedBufs.bufDesc[i].buf =
                    Memory_getBufferVirtualAddress(
                    (UInt32)outArgs->decodedBufs.bufDesc[i].buf,
                    outArgs->decodedBufs.bufDesc[i].bufSize);

                /* Clear .accessMask; the local proc didn't access this buf */
                outArgs->decodedBufs.bufDesc[i].accessMask = 0;
            }
        }
    }

    /* Buffers in outArgs.displayBufs are physical, so convert them if needed */
    for (i = 0; i < IVIDDEC2_MAX_IO_BUFFERS; i++) {
        if (outArgs->outputID[i] != 0) {
            if ((retVal == IVIDDEC2_EOK) ||
                    (!(XDM_ISFATALERROR(outArgs->
                               displayBufs[i].extendedError)))) {

                for (j = 0; j < IVIDEO_MAX_YUV_BUFFERS; j++) {
                    if (outArgs->displayBufs[i].bufDesc[j].buf != NULL) {
                        outArgs->displayBufs[i].bufDesc[j].buf =
                            Memory_getBufferVirtualAddress(
                                (UInt32)outArgs->displayBufs[i].bufDesc[j].buf,
                                outArgs->displayBufs[i].bufDesc[j].bufSize);

                        /*
                         * Clear .accessMask; the local processor didn't
                         * access this buf.
                         */
                        outArgs->displayBufs[i].bufDesc[j].accessMask = 0;
                    }
                }
            }
        }
    }


    /* Note that we did *nothing* with inBufs nor inArgs.  This should be ok. */

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== process ========
 *  This is the sync stub-implementation for the process method
 */
static XDAS_Int32 process(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _VIDDEC2_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBufs, outBufs, inArgs, outArgs, &msg);
    if (retVal != IVIDDEC2_EOK) {
        return retVal;
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /*
     * Regardless of return value, unmarshall outArgs.
     */
    retVal = unmarshallMsg(h, inBufs, outBufs, inArgs, outArgs, msg, retVal);

    return (retVal);
}

/*
 *  ======== processAsync ========
 *  This is the async stub-implementation for the process method
 */
static XDAS_Int32 processAsync(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _VIDDEC2_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, inBufs, outBufs, inArgs, outArgs, &msg);
    if (retVal != IVIDDEC2_EOK) {
        return retVal;
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_callAsync(visa, (VISA_Msg *)&msg);

    return (retVal);
}

/*
 *  ======== processWait ========
 */
static XDAS_Int32 processWait(IVIDDEC2_Handle h, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, IVIDDEC2_InArgs *inArgs, IVIDDEC2_OutArgs *outArgs,
    UInt timeout)
{
    XDAS_Int32 retVal;
    _VIDDEC2_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    GT_assert(CURTRACE, !VISA_isLocal(visa));

    /* wait for completion of "last" message */
    retVal = VISA_wait(visa, (VISA_Msg *)&msg, timeout);

    if (msg != NULL) {
        GT_assert(CURTRACE, msg->visa.cmd == _VIDDEC2_CPROCESS);

        retVal = unmarshallMsg(h, inBufs, outBufs, inArgs, outArgs, msg,
                               retVal);
    }

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(IVIDDEC2_Handle h, IVIDDEC2_Cmd id,
     IVIDDEC2_DynamicParams *params, IVIDDEC2_Status *status)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _VIDDEC2_Msg *msg;
    IVIDDEC2_Status *pMsgStatus;
    XDAS_Int8 *virtAddr = NULL;
    Int payloadSize;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * debug builds via GT_assert()?
     */
    if ((params == NULL) || (params->size < sizeof(IVIDDEC2_DynamicParams)) ||
            (status == NULL) || (status->size < sizeof(IVIDDEC2_Status))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (IVIDDEC2_EFAIL);
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

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_VIDDEC2_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (IVIDDEC2_EFAIL);
    }

    /* marshall the command */
    msg->visa.cmd = _VIDDEC2_CCONTROL;

    msg->cmd.control.id = id;

    /* params has no pointers so simply memcpy "size" bytes into the msg */
    memcpy(&(msg->cmd.control.params), params, params->size);

    /* unmarshall status based on the "size" of params */
    pMsgStatus = (IVIDDEC2_Status *)((UInt)(&(msg->cmd.control.params)) +
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
            retVal = IVIDDEC2_EFAIL;
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
    GT_assert(CURTRACE, msg->visa.cmd == _VIDDEC2_CCONTROL);

    /* unmarshall status */
    pMsgStatus = (IVIDDEC2_Status *)((UInt)(&(msg->cmd.control.params)) +
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
 *  ======== VIDDEC2_processAsync ========
 */
XDAS_Int32 VIDDEC2_processAsync(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_5trace(CURTRACE, GT_ENTER, "VIDDEC2_processAsync> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBufs, outBufs, inArgs, outArgs);

    if (handle) {
        IVIDDEC2_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
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
            }

            retVal = processAsync(alg, inBufs, outBufs, inArgs, outArgs);
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC2_processAsync> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}

/*
 *  ======== VIDDEC2_processWait ========
 */
XDAS_Int32 VIDDEC2_processWait(VIDDEC2_Handle handle, XDM1_BufDesc *inBufs,
    XDM_BufDesc *outBufs, VIDDEC2_InArgs *inArgs, VIDDEC2_OutArgs *outArgs,
    UInt timeout)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;
    VIDDEC2_InArgs refInArgs;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_5trace(CURTRACE, GT_ENTER, "VIDDEC2_processWait> "
        "Enter (handle=0x%x, inBufs=0x%x, outBufs=0x%x, inArgs=0x%x, "
        "outArgs=0x%x)\n", handle, inBufs, outBufs, inArgs, outArgs);

    if (handle) {
        IVIDDEC2_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

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

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC2_processWait> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.video2; 1, 0, 2,176; 12-2-2010 21:28:24; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

