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
 *  ======== vicpysync.c ========
 */
#include <xdc/std.h>
#include <ti/sdo/utils/trace/gt.h>
#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>
#include "vicpsync.h" 
#include "_vicpsync.h" 

/* Linuxutils header */
#include <ti/sdo/linuxutils/vicp/include/vicp.h>

#define CURTRACE ti_sdo_fc_vicpsync_GTMask

VICPSYNC_Params VICPSYNC_PARAMS;

#if (GT_TRACE == 1)
static GT_Mask ti_sdo_fc_vicpsync_GTMask;
static int gtInit = 0; 
#endif

static inline Bool getRes(VICPSYNC_ResourceType res, 
        VICPSYNC_InterruptLine intLine, IRES_VICP2_Handle vicpHandle, 
        VICP_ResourceType * vicp);
/*
 *  ======== VICPSYNC_start ========
 *  API called to prepare for using a particular VICP functional unit. 
 *  Ensures that the Interrupt corresponding to this functional unit is
 *  registered. 
 */
/* ARGSUSED */
VICPSYNC_Status VICPSYNC_start(IALG_Handle handle, VICPSYNC_ResourceType res, 
        VICPSYNC_InterruptType intType, VICPSYNC_InterruptLine intLine, 
        IRES_VICP2_Handle vicpHandle)
{

    VICP_ResourceType vicp;
    VICP_InterruptType interruptType;    
    VICP_InterruptLine interruptLine;    
    VICP_Status status;
    Bool check = TRUE;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&CURTRACE, "ti.sdo.fc.vicpsync"); 
        GT_init();
        gtInit = 1;
    }
#endif

    check = getRes(res, intLine, vicpHandle, &vicp);

    if (FALSE == check) {
        return (VICPSYNC_ENORESOURCE);
    }

    if (intLine == VICPSYNC_FIXED) {
        interruptLine = VICP_FIXED;
    }
    else {
        interruptLine = VICP_FLEXIBLE;
    }

    if (intType == VICPSYNC_IRQ) {
        interruptType = VICP_IRQ;
    }
    else {
        interruptType = VICP_FIQ;
    }

    status = VICP_register(vicp, interruptLine, interruptType);

    if (VICP_OK == status) {
        return (VICPSYNC_OK);
    }

    return (VICPSYNC_EFAIL);
}

/*
 *  ======== VICPSYNC_wait ========
 *  Blocking API to wait on the interrupt corresponding to the VICP resource to  *  fire. Must have called VICPSYNC_start on the particular resource prior to 
 *  calling this API.  
 */
VICPSYNC_Status VICPSYNC_wait(IRES_VICP2_Handle vicpHandle, 
        VICPSYNC_ResourceType res)
{
    VICP_ResourceType vicp;
    VICP_Status status;
    Bool check = TRUE;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&CURTRACE, "ti.sdo.fc.vicpsync"); 
        GT_init();
        gtInit = 1;
    }
#endif

    check = getRes(res, VICPSYNC_FIXED, vicpHandle, &vicp);

    if (FALSE == check) {
        return (VICPSYNC_ENORESOURCE); 
    }

    status = VICP_wait(vicp);

    if (status == VICP_OK) {
        return (VICPSYNC_OK);
    }
    else {
        return (VICPSYNC_EFAIL);
    }
}

/*
 *  ======== VICPSYNC_done ========
 *  API to poll on the status of the interrupt corresponding to the VICP 
 *  resource. Must have called VICPSYNC_start on the particular resource prior 
 *  to calling this API.  
 */
Bool VICPSYNC_done(IRES_VICP2_Handle vicpHandle, VICPSYNC_ResourceType res)
{
    VICP_ResourceType vicp;
    int status = (int)TRUE;
    Bool check = TRUE;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&CURTRACE, "ti.sdo.fc.vicpsync"); 
        GT_init();
        gtInit = 1;
    }
#endif

    check = getRes(res, VICPSYNC_FIXED, vicpHandle, &vicp);
    if (FALSE == check) {
        return (FALSE);
    }    

    if (VICP_OK == VICP_done(vicp, &status)) {
        return ((Bool)(status));
    }
    else {
        return (FALSE);
    }
}
/*
 *  ======== VICPSYNC_unregister ========
 *  API to explicitly unregister a particular VICP interrupt. 
 *  Must have called VICPSYNC_waitPartial on the particular resource prior 
 *  to calling this API.  
 */
VICPSYNC_Status VICPSYNC_unregister(IRES_VICP2_Handle vicpHandle, 
        VICPSYNC_ResourceType res)
{
    VICP_ResourceType vicp;
    VICP_Status status;
    Bool check = TRUE;

#if (GT_TRACE == 1)
    if (0 == gtInit) {
        GT_create(&CURTRACE, "ti.sdo.fc.vicpsync"); 
        GT_init();
        gtInit = 1;
    }
#endif

    check = getRes(res, VICPSYNC_FIXED, vicpHandle, &vicp);

    if (FALSE == check) {
        return (VICPSYNC_ENORESOURCE); 
    }

    status = VICP_unregister(vicp);

    if (VICP_OK == status) {
        return (VICPSYNC_OK);
    }
    else {
        return (VICPSYNC_EFAIL);
    }
}


static inline Bool getRes(VICPSYNC_ResourceType res, 
        VICPSYNC_InterruptLine intLine, IRES_VICP2_Handle vicpHandle, 
        VICP_ResourceType * vicp)
{
    Bool check = TRUE;
    switch (res) {
        case VICPSYNC_IMX0:
            if (vicpHandle->assignedIMX0) {
                *vicp = VICP_IMX0;
            }
            else {
                check = FALSE;
            }
            break;
        case VICPSYNC_IMX1:
            if ((_VICPSYNC_dm365) && (vicpHandle->assignedIMX1)) {
                *vicp = VICP_IMX1;
            }
            else {
                check = FALSE;
            }
            break;
        case VICPSYNC_MJCP: 
            if ((vicpHandle->assignedMJCP) && (intLine == VICPSYNC_FIXED))  {
                *vicp = VICP_MJCP;
            }
            else {
                check = FALSE;
            }
            break;
        case VICPSYNC_NSF:
            if (vicpHandle->assignedNSF) {
                *vicp = VICP_NSF;
            }
            else {
                check = FALSE;
            }
            break;
        default:
            check = FALSE;
    } 

    return (check);
}
/*
 *  @(#) ti.sdo.fc.vicpsync; 1, 0, 0,118; 12-1-2010 17:26:13; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

