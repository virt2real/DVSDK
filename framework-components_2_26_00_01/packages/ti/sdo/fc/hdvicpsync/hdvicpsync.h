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
 *  @file       ti/sdo/fc/hdvicpsync/hdvicpsync.h
 *
 *  @brief      HDVICPSYNC Interface Definitions -
 *              Framework support package for synchronization between codec
 *              and HDVICP coprocessor usage.
 */

/**
 *  @defgroup   ti_sdo_fc_hdvicpsync_HDVICPSYNC HDVICPSYNC
 *              HDVICPSYNC provides framework support for synchronization
 *              between codec and HDVICP coprocessor usage.
 *              This module is used by frameworks or applications which have
 *              xDAIS algorithms that use HDVICP hardware accelerators.
 */

#ifndef ti_sdo_fc_hdvicpsync_HDVICPSYNC_
#define ti_sdo_fc_hdvicpsync_HDVICPSYNC_

/** @ingroup    ti_sdo_fc_hdvicpsync_HDVICPSYNC */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

/**
 *  @brief      Name to identify the GT module
 */
#define HDVICPSYNC_GTNAME "ti.sdo.fc.hdvicpsync"


/**
 *  @brief      The module configuration structure for HDVICPSYNC implementation
 */
typedef struct HDVICPSYNC_Params {
    int size;
} HDVICPSYNC_Params;

/**
 *  @brief      Interrupt type that can be specified for each Resource type
 */
typedef enum HDVICPSYNC_InterruptType {
    HDVICPSYNC_IRQ,             /**< Regular Interrupt Request */
    HDVICPSYNC_FIQ              /**< Fast Interrupt Request */
} HDVICPSYNC_InterruptType;

typedef enum HDVICPSYNC_Status {
    HDVICPSYNC_OK,              /**< Success */
    HDVICPSYNC_EFAIL,           /**< general failure */
    HDVICPSYNC_ENORESOURCE      /**< resources not owned to be able to
                                     configure the interrupt */
} HDVICPSYNC_Status;


/**
 *  @brief      Default module configuration structure (defined in hdvicpsync.c)
 */
extern HDVICPSYNC_Params HDVICPSYNC_PARAMS;

/**
 * @brief  This function is used to mark the beginning of HDVICP coprocessor
 *         usage by the algorithm.
 *
 * @param  handle           Algorithm handle
 * @param  intType          Interrupt Type
 * @param  hdvicpHandle     Pointer to the hdvicp handle.
 *
 * @return none
 *
 * @note   This function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
HDVICPSYNC_Status HDVICPSYNC_start(IALG_Handle handle,
        HDVICPSYNC_InterruptType intType, IRES_HDVICP_Handle hdvicpHandle);

/**
 * @brief  This is the top level function that allows the ARM-side algorithm
 *         to wait for the Kaleido (frame) interrupt to fire.
 *
 * @param  hdvicpHandle      void pointer to the hdvicp handle.
 *
 * @return none
 *
 * @note   As per XDM, this function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
HDVICPSYNC_Status HDVICPSYNC_wait(IRES_HDVICP_Handle hdvicpHandle);

/*===========================================================================*/
/**
 * @brief  This is the top level function that allows the ARM-side algorithms  
 *         to explicitly unregister a particular interrupt handler for ISRS
 *         registerd via a call to HDVICPSYNC_start API. 
 *
 * @param  hdvicpHandle       void pointer to the hdvicp handle.
 *
 * @return HDVICPSYNC_Status  Returns status of this call
 *
 * @note   As per XDM, this function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
/*===========================================================================*/
HDVICPSYNC_Status HDVICPSYNC_unregister(IRES_HDVICP_Handle hdvicpHandle);

/**
 * @brief  This is the top level function that allows the ARM-side algorithm
 *         to return a status indicating if a Kaleido interrupt has fired
 *         (frame has been processed) since HDVICPSYNC_start was called.
 *
 * @param  hdvicpHandle      void pointer to the hdvicp handle.
 *
 * @return none
 *
 * @note   As per XDM, this function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
Bool HDVICPSYNC_done(IRES_HDVICP_Handle hdvicpHandle);

#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/

#endif
/*
 *  @(#) ti.sdo.fc.hdvicpsync; 1, 0, 0,121; 12-1-2010 17:24:52; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

