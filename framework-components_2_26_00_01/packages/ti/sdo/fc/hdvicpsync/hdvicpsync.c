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
 *  ======== hdvicpcsync.c ========
 */

#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>
#include "hdvicpsync.h" 

/* Linuxutils header */
#include <ti/sdo/linuxutils/vicp/include/vicp.h>


HDVICPSYNC_Params HDVICPSYNC_PARAMS;

#if (GT_TRACE== 1)
static GT_Mask ti_sdo_fc_hdvicpsync_GTMask;
static int gtInit = 0;
#endif



/* ARGSUSED */
HDVICPSYNC_Status HDVICPSYNC_start(IALG_Handle handle, 
        HDVICPSYNC_InterruptType intType, IRES_HDVICP_Handle hdvicpHandle)
{
    VICP_ResourceType vicp;
    VICP_InterruptType interruptType;
    VICP_InterruptLine interruptLine = VICP_FIXED;
    VICP_Status status;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&ti_sdo_fc_hdvicpsync_GTMask, "ti.sdo.fc.hdvicpsync");
        GT_init();
        gtInit = 1;
    }
#endif

    if (hdvicpHandle->id == IRES_HDVICP_ID_0) {
        vicp = VICP_HDVICP0;
    }
    else {
        return (HDVICPSYNC_ENORESOURCE);
    }

    if (intType == HDVICPSYNC_IRQ) {
        interruptType = VICP_IRQ;
    }
    else {
        interruptType = VICP_FIQ;
    }

    status = VICP_register(vicp, interruptLine, interruptType);

    if (VICP_OK == status) {
        GT_0trace(ti_sdo_fc_hdvicpsync_GTMask, GT_ENTER, "HDVICPSYNC_start>"
                " (status=HDVICPSYNC_OK)\n"); 
        return (HDVICPSYNC_OK);
    }
    else {
        GT_0trace(ti_sdo_fc_hdvicpsync_GTMask, GT_7CLASS, "HDVICPSYNC_start>"
                " Call to register interrupt, failed\n"); 
        GT_0trace(ti_sdo_fc_hdvicpsync_GTMask, GT_ENTER, "HDVICPSYNC_start>"
                " (status=HDVICPSYNC_EFAIL)\n"); 
        return (HDVICPSYNC_EFAIL);
    }
}

/* ARGSUSED */
HDVICPSYNC_Status HDVICPSYNC_wait (IRES_HDVICP_Handle hdvicpHandle)
{
    VICP_ResourceType vicp;
    VICP_Status status;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&ti_sdo_fc_hdvicpsync_GTMask, "ti.sdo.fc.hdvicpsync");
        GT_init();
        gtInit = 1;
    }
#endif

    if (hdvicpHandle->id == IRES_HDVICP_ID_0) {
        vicp = VICP_HDVICP0;
    }
    else {
        return (HDVICPSYNC_ENORESOURCE);
    }

    status = VICP_wait(vicp);

    if (status == VICP_OK) {
        return (HDVICPSYNC_OK);
    }
    else {
        return (HDVICPSYNC_EFAIL);
    }
}

/* ARGSUSED */
HDVICPSYNC_Status HDVICPSYNC_unregister (IRES_HDVICP_Handle hdvicpHandle)
{
    VICP_ResourceType vicp;
    VICP_Status status;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&ti_sdo_fc_hdvicpsync_GTMask, "ti.sdo.fc.hdvicpsync");
        GT_init();
        gtInit = 1;
    }
#endif

    if (hdvicpHandle->id == IRES_HDVICP_ID_0) {
        vicp = VICP_HDVICP0;
    }
    else {
        return (HDVICPSYNC_ENORESOURCE);
    }

    status = VICP_unregister(vicp);

    if (status == VICP_OK) {
        return (HDVICPSYNC_OK);
    }
    else {
        return (HDVICPSYNC_EFAIL);
    }
}

/* ARGSUSED */
Bool HDVICPSYNC_done (IRES_HDVICP_Handle hdvicpHandle)
{
    VICP_ResourceType vicp;
    int status = (int)TRUE;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&ti_sdo_fc_hdvicpsync_GTMask, "ti.sdo.fc.hdvicpsync");
        GT_init();
        gtInit = 1;
    }
#endif

    if (hdvicpHandle->id == IRES_HDVICP_ID_0) {
        vicp = VICP_HDVICP0;
    }
    else {
        return (HDVICPSYNC_ENORESOURCE);
    }


    if (VICP_OK == VICP_done(vicp, &status)) {
        return ((Bool)(status));   
    }
    else {
        return (FALSE); 
    }
}
/*
 *  @(#) ti.sdo.fc.hdvicpsync; 1, 0, 0,121; 12-1-2010 17:24:52; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

