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
/**
 *  @file       iresman_protocol_vicp.h 
 *
 *  @brief      IRESMAN PROTOCOL VICP Interface Definitions (C64P) - 
 *              Interface exposed to the device specific IRESMAN layer used to 
 *              construct and destruct handles representing the resource 
 */

#ifndef ti_sdo_fc_ires_vicp2_IRESMAN_PROTOCOL_VICP2_
#define ti_sdo_fc_ires_vicp2_IRESMAN_PROTOCOL_VICP2_
/** @ingroup    ti_sdo_fc_ires_vicp2_IRESMAN_VICP2 */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/sdo/fc/ires/iresman_protocol.h>
#include "iresman_vicp2.h" 

/*
 * @brief           Arguments that are passed from the IRES Resource manager
 *                  to intialize the handle
 */
typedef struct IRESMAN_VICP2_ConstructHandleArgs {

    IRESMAN_ConstructArgs args;
    short               assignedIMX0;
    short               assignedIMX1;
    short               assignedMJCP;
    short               assignedNSF;
    unsigned int        assignedIMCOPBuffers[IRES_VICP2_NUMBUFFERS];
                                        /* Offset Addresses of Named buffers 
                                           granted,
                                           Index array with IMCOP_BUFFER_<> */
    unsigned int        assignedIMCOPBufferLens[IRES_VICP2_NUMBUFFERS];
    short               numMemBufs;     /* Number of individual memory buffers
                                           assigned */
    unsigned int        assignedMemAddrs[IRES_VICP2_NUMBUFFERS];   
                                        /* Offset addresses of Buffers granted*/
    unsigned int        assignedMemSizes[IRES_VICP2_NUMBUFFERS]; 
    Int                 buffSwitchesOnly[IRES_VICP2_NUMBUFFERS]; 
    Int                 numBuffSwitches;
 
    Bool persistent;

} IRESMAN_VICP2_ConstructHandleArgs;


/*
 * Interface to expose to the resource manager to be able to construct handles
 */
extern IRESMAN_ConstructFxns IRESMAN_VICP2_CONSTRUCTFXNS;

/*@}*/ /** @ingroup    DSPIRESPROTVICP */


#ifdef __cplusplus
}
#endif /* extern "C" */


#endif  /* ti_sdo_fc_ires_vicp2_IRESMAN_PROTOCOL_VICP2_*/

/*
 *  @(#) ti.sdo.fc.ires.vicp; 1, 0, 1,177; 12-1-2010 17:25:26; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

