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
 *  ======== viddec2back_stubs.c ========
 *  This file contains an implemenation of the IVIDDEC2FRONT interface for the
 *  video decoder class of algorithms.
 *
 *  These functions are the "client-side" of a "remote" implementation.
 *
 */
#include <xdc/std.h>
#include <ti/sdo/ce/visa.h>
#include <ti/xdais/dm/split/ividdec2.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/utils/trace/gt.h>

#include <string.h>  /* for memcpy and memset.
                      * (TODO:L Should we introduce these in Memory_*? */

#include <ti/sdo/ce/utils/xdm/XdmUtils.h>

#include "viddec2.h"
#include "_viddec2back.h"

static XDAS_Int32 process(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs);
static XDAS_Int32 processAsync(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs);
static XDAS_Int32 processWait(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs,
        UInt timeout);
static XDAS_Int32 control(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_Status *status);
static XDAS_Int32 marshallMsg(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs, _VIDDEC2BACK_Msg **pmsg);
static XDAS_Int32 unmarshallMsg(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs, _VIDDEC2BACK_Msg *msg, XDAS_Int32 retVal);
static int copySparseSingleBufDescArrayWithV2P(XDM1_SingleBufDesc *pDest,
        XDM1_SingleBufDesc *pSrc, XDAS_Int32 numBufs, XDAS_Int32 maxBufs);
static int copySingleBufDescArrayWithV2P(XDM1_SingleBufDesc *pDest,
        XDM1_SingleBufDesc *pSrc, XDAS_Int32 maxBufs);
static int copySparseSingleBufDescArrayWithP2V(XDM1_SingleBufDesc *pDest,
        XDM1_SingleBufDesc *pSrc, XDAS_Int32 numBufs, XDAS_Int32 maxBufs);
static int copySingleBufDescArrayWithP2V(XDM1_SingleBufDesc *pDest,
        XDM1_SingleBufDesc *pSrc, XDAS_Int32 maxBufs);


IVIDDEC2BACK_Fxns VIDDEC2BACK_STUBS = {
    {&VIDDEC2BACK_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};

extern GT_Mask ti_sdo_ce_video2_split_VIDDEC2BACK_curTrace;
#define CURTRACE ti_sdo_ce_video2_split_VIDDEC2BACK_curTrace

static int copySingleBufDescArrayWithP2V(XDM1_SingleBufDesc *pDest,
    XDM1_SingleBufDesc *pSrc, XDAS_Int32 maxBufs)
{
    int i;

    for (i = 0; (i < maxBufs) && (pSrc[i].buf != NULL); i++) {
        /* found another, convert it */
        pDest[i].bufSize = pSrc[i].bufSize;

        pDest[i].buf = (XDAS_Int8 *)
            Memory_getBufferVirtualAddress((UInt32)pSrc[i].buf,
                    pSrc[i].bufSize);

        if (pDest[i].buf == NULL) {
            i = -1;
            break;
        }

        /* Clear .accessMask; the local processor won't access this buf */
        pDest[i].accessMask = 0;
    }

    return (i);
}

static int copySparseSingleBufDescArrayWithP2V(XDM1_SingleBufDesc *pDest,
    XDM1_SingleBufDesc *pSrc, XDAS_Int32 numBufs, XDAS_Int32 maxBufs)
{
    int i, foundBufs;

    for (i = 0, foundBufs = 0; ((foundBufs < numBufs) && (i < maxBufs)); i++) {
        if (pSrc[i].buf != NULL) {
            /* valid member of sparse array, convert it */
            pDest[i].bufSize =pSrc[i].bufSize;

            pDest[i].buf = (XDAS_Int8 *)
                Memory_getBufferVirtualAddress((UInt32)pSrc[i].buf,
                    pSrc[i].bufSize);

            if (pDest[i].buf == NULL) {
                foundBufs = -1;
                break;
            }

            /* Clear .accessMask; the local processor won't access this buf */
            pDest[i].accessMask = 0;

            /* found, and handled, another buffer. */
            foundBufs++;
        }
        else {
            /* empty member of sparse array, no conversion needed. */
            pDest[i].bufSize = 0;
            pDest[i].buf = NULL;
        }
    }

    return (foundBufs);
}

static int copySingleBufDescArrayWithV2P(XDM1_SingleBufDesc *pDest,
    XDM1_SingleBufDesc *pSrc, XDAS_Int32 maxBufs)
{
    int i;

    for (i = 0; (i < maxBufs) && (pSrc[i].buf != NULL); i++) {
        /* found another, convert it */
        pDest[i].bufSize = pSrc[i].bufSize;

        pDest[i].buf = (XDAS_Int8 *)
            Memory_getBufferPhysicalAddress(pSrc[i].buf, pSrc[i].bufSize,
                    NULL);

        if (pDest[i].buf == NULL) {
            i = -1;
            break;
        }

        /* Clear .accessMask; the local processor won't access this buf */
        pDest[i].accessMask = 0;
    }

    return (i);
}


static int copySparseSingleBufDescArrayWithV2P(XDM1_SingleBufDesc *pDest,
    XDM1_SingleBufDesc *pSrc, XDAS_Int32 numBufs, XDAS_Int32 maxBufs)
{
    int i, foundBufs;

    for (i = 0, foundBufs = 0; ((foundBufs < numBufs) && (i < maxBufs)); i++) {
        if (pSrc[i].buf != NULL) {
            /* valid member of sparse array, convert it */
            pDest[i].bufSize =pSrc[i].bufSize;

            pDest[i].buf = (XDAS_Int8 *)
                Memory_getBufferPhysicalAddress(pSrc[i].buf, pSrc[i].bufSize,
                    NULL);

            if (pDest[i].buf == NULL) {
                foundBufs = -1;
                break;
            }

            /* Clear .accessMask; the local processor won't access this buf */
            pDest[i].accessMask = 0;

            /* found, and handled, another buffer. */
            foundBufs++;
        }
        else {
            /* empty member of sparse array, no conversion needed. */
            pDest[i].bufSize = 0;
            pDest[i].buf = NULL;
        }
    }

    return (foundBufs);
}


/*
 *  ======== marshallMsg ========
 */
static XDAS_Int32 marshallMsg(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs,  _VIDDEC2BACK_Msg **pmsg)
{
    XDAS_Int32 retVal = IVIDDEC2_EOK;
    VISA_Handle visa = (VISA_Handle)h;
    _VIDDEC2BACK_Msg *msg;
    Int numBufs;

    GT_assert(CURTRACE, pmsg != NULL);

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * checked builds?
     */
    if ((context == NULL) || (outArgs == NULL) ||
            (outArgs->size < sizeof(IVIDDEC2_OutArgs))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (IVIDDEC2_EFAIL);
    }

    if (/* size of "stuff to marshall" > message size */
        (sizeof(VISA_MsgHeader) + sizeof(XDM_Context) +
            outArgs->size) > sizeof(_VIDDEC2BACK_Msg)) {

        /* Can't handle these large extended args. */
        GT_0trace(CURTRACE, GT_6CLASS,
            "process> invalid arguments - outArgs.size field is too large\n");

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_VIDDEC2BACK_Msg *)VISA_allocMsg(visa)) == NULL) {
        GT_0trace(CURTRACE, GT_6CLASS, "process> VISA_allocMsg failed\n");

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
    msg->visa.cmd = _VIDDEC2BACK_CPROCESS;

    /* address translation of XDM_Context buffers */
    if (context->algContext.buf != NULL) {
        msg->cmd.process.context.algContext.bufSize =
                context->algContext.bufSize;

        msg->cmd.process.context.algContext.buf = (XDAS_Int8 *)
                Memory_getBufferPhysicalAddress(context->algContext.buf,
                    context->algContext.bufSize, NULL);

            if (msg->cmd.process.context.algContext.buf == NULL) {
                retVal = IVIDDEC2_EFAIL;
                goto exit;
            }
    }

    /* context->num*Bufs are plain integers, just copy them */
    msg->cmd.process.context.numInBufs = context->numInBufs;
    msg->cmd.process.context.numOutBufs = context->numOutBufs;
    msg->cmd.process.context.numInOutBufs = context->numInOutBufs;

    /* address translate inBufs */
    numBufs =
        copySparseSingleBufDescArrayWithV2P(msg->cmd.process.context.inBufs,
                context->inBufs, context->numInBufs, XDM_MAX_CONTEXT_BUFFERS);

    if (numBufs == -1) {
        retVal = IVIDDEC2_EFAIL;
        goto exit;
    }

    if (VISA_isChecked()) {
        /* check that we found context->numInBufs in context->inBufs */
        GT_assert(CURTRACE, context->numInBufs == numBufs);
    }

    /* Repeat the procedure for outBufs and intermediateBufs. */
    numBufs =
        copySparseSingleBufDescArrayWithV2P(msg->cmd.process.context.outBufs,
                context->outBufs, context->numOutBufs, XDM_MAX_CONTEXT_BUFFERS);

    if (numBufs == -1) {
        retVal = IVIDDEC2_EFAIL;
        goto exit;
    }

    if (VISA_isChecked()) {
        /* check that we found context->numOutBufs in context->outBufs */
        GT_assert(CURTRACE, context->numOutBufs == numBufs);
    }

    numBufs =
        copySingleBufDescArrayWithV2P(msg->cmd.process.context.intermediateBufs,
                context->intermediateBufs, XDM_MAX_CONTEXT_BUFFERS);

    if (numBufs == -1) {
        retVal = IVIDDEC2_EFAIL;
        goto exit;
    }

    /* VIDDEC2BACK doesn't support any in/out buffers */
    if (VISA_isChecked()) {
        GT_assert(CURTRACE, context->numInOutBufs == 0);
    }

    /* outArgs has no 'inputs', so only .size needs marshalled */
    msg->cmd.process.outArgs.size = outArgs->size;

    *pmsg = msg;

    return (retVal);

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return retVal;
}

/*
 *  ======== unmarshallMsg ========
 */
static XDAS_Int32 unmarshallMsg(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs, _VIDDEC2BACK_Msg *msg, XDAS_Int32 retVal)
{
    VISA_Handle visa = (VISA_Handle)h;
    Int i;
    IVIDDEC2_OutArgs *pMsgOutArgs;
    Int numBufs;

#if 0
    if (VISA_isChecked()) {
        /* ensure the codec didn't change outArgs->size */
        GT_assert(CURTRACE, msg->cmd.process.outArgs.size == outArgs->size);
    }
#endif

    memcpy(outArgs, &(msg->cmd.process.outArgs), outArgs->size);

    /* if VISA_call was successful, also unmarshall outBufs */
    if (retVal == IVIDDEC2_EOK) {
        /* unmarshall the output data: outBufs and outArgs. */

        if (VISA_isChecked()) {
           /* sanity check context */
            GT_assert(CURTRACE, msg->cmd.process.context.numInBufs <
                    XDM_MAX_CONTEXT_BUFFERS);
            GT_assert(CURTRACE, msg->cmd.process.context.numOutBufs <
                    XDM_MAX_CONTEXT_BUFFERS);
            GT_assert(CURTRACE, msg->cmd.process.context.numInOutBufs == 0);
        }

        /* The outBufs may have changed, so don't rely on what was passed in */
        context->numOutBufs = msg->cmd.process.context.numOutBufs;

        numBufs = copySparseSingleBufDescArrayWithP2V(context->outBufs,
            msg->cmd.process.context.outBufs, context->numOutBufs,
            XDM_MAX_CONTEXT_BUFFERS);

        if (numBufs == -1) {
            retVal = IVIDDEC2_EFAIL;
            goto exit;
        }

        if (VISA_isChecked()) {
            /* check that we found the indicated number of buffers */
            GT_assert(CURTRACE, context->numOutBufs == numBufs);
        }

        /* address translate the decoded buffers */
        copySingleBufDescArrayWithP2V(outArgs->decodedBufs.bufDesc,
            outArgs->decodedBufs.bufDesc, IVIDEO_MAX_YUV_BUFFERS);

        /* buffers in outArgs.displayBufs are physical, so convert them */
        for (i = 0; i < IVIDDEC2_MAX_IO_BUFFERS; i++) {
            if (outArgs->outputID[i] != 0) {
                copySingleBufDescArrayWithP2V(outArgs->displayBufs[i].bufDesc,
                    outArgs->displayBufs[i].bufDesc, IVIDEO_MAX_YUV_BUFFERS);
            }
        }

        /* and finally the mbDataBuf */
        if (outArgs->mbDataBuf.buf != NULL) {
            Memory_getBufferVirtualAddress((UInt32)outArgs->mbDataBuf.buf,
                outArgs->mbDataBuf.bufSize);

            /* Clear .accessMask; the local processor didn't access this buf */
            outArgs->mbDataBuf.accessMask = 0;
        }
    }

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== process ========
 *  This is the sync stub-implementation for the process method
 */
static XDAS_Int32 process(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _VIDDEC2BACK_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, context, outArgs, &msg);
    if (retVal != IVIDDEC2_EOK) {
        return (retVal);
    }

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /*
     * Regardless of return value, unmarshall outArgs.
     */
    retVal = unmarshallMsg(h, context, outArgs, msg, retVal);

    return (retVal);
}


/*
 *  ======== processAsync ========
 *  This is the async stub-implementation for the process method
 */
static XDAS_Int32 processAsync(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    _VIDDEC2BACK_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    retVal = marshallMsg(h, context, outArgs, &msg);
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
static XDAS_Int32 processWait(IVIDDEC2BACK_Handle h, XDM_Context *context,
        IVIDDEC2_OutArgs *outArgs, UInt timeout)
{
    XDAS_Int32 retVal;
    _VIDDEC2BACK_Msg *msg;
    VISA_Handle visa = (VISA_Handle)h;

    GT_assert(CURTRACE, !VISA_isLocal(visa));

    /* wait for completion of "last" message */
    retVal = VISA_wait(visa, (VISA_Msg *)&msg, timeout);

    GT_assert(CURTRACE, msg->visa.cmd == _VIDDEC2BACK_CPROCESS);

    /*
     * Regardless of return value, unmarshall outArgs.
     */
    retVal = unmarshallMsg(h, context, outArgs, msg, retVal);

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(IVIDDEC2BACK_Handle h, XDM_Context *context,
     IVIDDEC2_Status *status)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _VIDDEC2BACK_Msg *msg;
    IVIDDEC2_Status *pMsgStatus;
    XDAS_Int8 *virtAddr = NULL;

    /*
     * Validate arguments.  Do we want to do this _every_ time, or just in
     * debug builds via GT_assert()?
     */
    if ((context == NULL) || (status == NULL) ||
            (status->size < sizeof(IVIDDEC2_Status))) {

        /* invalid args, could even assert here, it's a spec violation. */
        return (IVIDDEC2_EFAIL);
    }

    if (/* size of "stuff to marshall" > message size */
        (sizeof(VISA_MsgHeader) + sizeof(*context) + status->size)
            > sizeof(_VIDDEC2BACK_Msg)) {

        /* Can't handle these large extended args. */
        GT_0trace(CURTRACE, GT_6CLASS,
            "control> invalid arguments - validate .size fields\n");

        return (IVIDDEC2_EUNSUPPORTED);
    }

    /* get a message appropriate for this algorithm */
    if ((msg = (_VIDDEC2BACK_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (IVIDDEC2_EFAIL);
    }

    /* marshall the command */
    msg->visa.cmd = _VIDDEC2BACK_CCONTROL;

    /*
     * Initialize the .size and .data fields - the rest are filled in by
     * the codec.
     */
    msg->cmd.control.status.size = status->size;

#if 0
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
#endif
    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* ensure we get CCONTROL msg (ensure async CPROCESS pipeline drained) */
    GT_assert(CURTRACE, msg->visa.cmd == _VIDDEC2BACK_CCONTROL);

    if (VISA_isChecked()) {
        /* ensure codec didn't modify status->size */
        GT_assert(CURTRACE, msg->cmd.control.status.size == status->size);

        /*
         * TODO:L  Should we also check that pMsgStatus->data.buf is the same
         * after the call as before?
         */
    }
    memcpy(status, &(msg->cmd.control.status), status->size);
#if 0
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
#endif

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== VIDDEC2_processAsync ========
 */
XDAS_Int32 VIDDEC2BACK_processAsync(VIDDEC2FRONT_Handle handle,
        XDM_Context *context, VIDDEC2_OutArgs *outArgs)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_4trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_processAsync> "
            "Enter (handle=0x%x, context=0x%x outArgs=0x%x (size=0x%x))\n",
            handle, context, outArgs, outArgs->size);

    if (handle) {
        IVIDDEC2BACK_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /* validate context */
            }

            retVal = processAsync(alg, context, outArgs);
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_processAsync> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}

/*
 *  ======== VIDDEC2_processWait ========
 */
XDAS_Int32 VIDDEC2BACK_processWait(VIDDEC2BACK_Handle handle,
        XDM_Context *context, VIDDEC2_OutArgs *outArgs, UInt timeout)
{
    XDAS_Int32 retVal = VIDDEC2_EFAIL;

    /*
     * Note, we do this because someday we may allow dynamically changing
     * the global 'VISA_isChecked()' value on the fly.  If we allow that,
     * we need to ensure the value stays consistent in the context of this call.
     */
    Bool checked = VISA_isChecked();

    GT_4trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_processWait> "
        "Enter (handle=0x%x, context=0x%x, outArgs=0x%x (size=0x%x))\n",
            handle, context, outArgs, outArgs->size);

    if (handle) {
        IVIDDEC2BACK_Handle alg = VISA_getAlgHandle((VISA_Handle)handle);

        if (alg != NULL) {
            if (checked) {
                /* TBD */
            }

            retVal = processWait(alg, context, outArgs, timeout);

            if (checked) {
                /* TBD */
            }
        }
    }

    GT_2trace(CURTRACE, GT_ENTER, "VIDDEC2BACK_processWait> "
        "Exit (handle=0x%x, retVal=0x%x)\n", handle, retVal);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.video2.split; 1, 0, 0,165; 12-2-2010 21:28:42; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

