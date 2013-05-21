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
 *  ======== scale_stubs.c ========
 *  These functions are the "app-side" of a "remote" implementation.
 *
 */
#include <xdc/std.h>
#include <ti/sdo/ce/visa.h>
#include <ti/sdo/ce/examples/codecs/scale/iscale.h>
#include <ti/sdo/ce/osal/Memory.h>

#include "scale.h"
#include "_scale.h"

static XDAS_Int32 process(ISCALE_Handle h, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs);
static XDAS_Int32 control(ISCALE_Handle h, ISCALE_Cmd id,
    ISCALE_DynamicParams *params);

/*
 * Stubs must implement the interface they "stub" for.  This scale stub
 * proxy's for ISCALE_Fxns, which is IALG + process() and control().
 *
 * Note that the IALG fxns for the stub currently aren't called, so
 * they're all set to NULL.
 */
ISCALE_Fxns SCALE_STUBS = {
    {&SCALE_STUBS, NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL},
    process, control,
};

/*
 *  ======== process ========
 *  This is the stub-implementation for the process method
 */
static XDAS_Int32 process(ISCALE_Handle h, XDAS_Int8 *inBuf,
    XDAS_Int8 *outBuf, ISCALE_InArgs *inArgs, ISCALE_OutArgs *outArgs)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _SCALE_Msg *msg;

    /* get a message appropriate for this algorithm */
    if ((msg = (_SCALE_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (SCALE_ERUNTIME);
    }

    /* Specify the processing command that the skeleton should do */
    msg->visa.cmd = _SCALE_CPROCESS;

    /* inBuf is a pointer, so we have to convert it */
    msg->cmd.process.inBuf = (XDAS_Int8 *)
        Memory_getBufferPhysicalAddress(inBuf, inArgs->inBufSize, NULL);

    if (msg->cmd.process.inBuf == NULL) {
        retVal = SCALE_ERUNTIME;
        goto exit;
    }

    /* Similarly with outBuf. Note that inArgs and outArgs contain no
     * pointers, so we can simply copy the entire original structure.
     */
    msg->cmd.process.outBuf = (XDAS_Int8 *)
        Memory_getBufferPhysicalAddress(outBuf, inArgs->outBufSize, NULL);

    if (msg->cmd.process.outBuf == NULL) {
        retVal = SCALE_ERUNTIME;
        goto exit;
    }

    /* inArgs has no pointers, so simply copy the struct fields into the msg */
    msg->cmd.process.inArgs = *inArgs;

    /* Note that outArgs is *output* and need not be provided to the skel */

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* copy out the outArgs */
    *outArgs = msg->cmd.process.outArgs;

    /* Note that we need not copy inArgs out of the msg. */

    /*
     * Note that we don't have to do any reverse address translation, as the
     * originally provided buffers haven't changed.
     */

exit:
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}

/*
 *  ======== control ========
 *  This is the stub-implementation for the control method
 */
static XDAS_Int32 control(ISCALE_Handle h, ISCALE_Cmd id,
    ISCALE_DynamicParams *params)
{
    XDAS_Int32 retVal;
    VISA_Handle visa = (VISA_Handle)h;
    _SCALE_Msg *msg;

    /* get a message appropriate for this algorithm */
    if ((msg = (_SCALE_Msg *)VISA_allocMsg(visa)) == NULL) {
        return (SCALE_ERUNTIME);
    }

    /* marshall the command */
    msg->visa.cmd = _SCALE_CCONTROL;

    msg->cmd.control.id = id;

    /* no pointers, just copy the dynamic params struct into the msg */
    msg->cmd.control.params = *params;

    /* send the message to the skeleton and wait for completion */
    retVal = VISA_call(visa, (VISA_Msg *)&msg);

    /* nothing to unmarshall, just free the msg. */
    VISA_freeMsg(visa, (VISA_Msg)msg);

    return (retVal);
}
/*
 *  @(#) ti.sdo.ce.examples.extensions.scale; 1, 0, 0,261; 12-2-2010 21:23:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

