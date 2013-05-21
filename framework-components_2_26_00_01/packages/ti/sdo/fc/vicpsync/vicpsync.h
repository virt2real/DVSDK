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
 *  @file       ti/sdo/fc/vicpsync/vicpsync.h
 *
 *  @brief      VICPSYNC Interface Definitions - 
 *              Framework support package for synchronization between codec 
 *              and VICP usage. This package allows algorithms to wait on 
 *              interrupt completion of individual functional units of the VICP  *              coprocessor.
 */

/**
 *  @defgroup   ti_sdo_fc_vicpsync_VICPSYNC VICPSYNC
 *
 *              This module is used by frameworks or applications which have
 *              xDAIS algorithms that use VICP hardware accelerators. 
 */

#ifndef VICPSYNC_
#define VICPSYNC_

/** @ingroup    ti_sdo_fc_vicpsync_VICPSYNC */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ialg.h>
#include <ti/sdo/fc/ires/vicp/ires_vicp2.h>

#define VICPSYNC_GTNAME "ti.sdo.fc.vicpsync"  
                                        /**< Name to identify the GT module */ 

/**
 *  @brief      The module configuration structure for VICPSYNC implementation
 */
typedef struct VICPSYNC_Params {
    int size;
} VICPSYNC_Params;

/**
 *  @brief      Resource types for which the API can be called 
 */
typedef enum VICPSYNC_ResourceType {
    VICPSYNC_IMX0,
    VICPSYNC_IMX1,
    VICPSYNC_MJCP,
    VICPSYNC_NSF
} VICPSYNC_ResourceType;

/**
 *  @brief      Interrupt line that can be specified for each Resource type 
 */
typedef enum VICPSYNC_InterruptLine {
    VICPSYNC_FIXED,          /**< Use dedicated line for this resource */
    VICPSYNC_FLEXIBLE        /**< Use generic interrupt line for this resource*/
} VICPSYNC_InterruptLine;

/**
 *  @brief      Interrupt type that can be specified for each Resource type 
 */
typedef enum VICPSYNC_InterruptType {
    VICPSYNC_IRQ,           /**< Regular Interrupt Request */ 
    VICPSYNC_FIQ            /**< Fast Interrupt Request */
} VICPSYNC_InterruptType;

typedef enum VICPSYNC_Status {
    VICPSYNC_OK,            /**< Success */
    VICPSYNC_EFAIL,         /**< general failure */
    VICPSYNC_ENORESOURCE    /**< resources not owned to be able to 
                                 configure this interrupt*/
} VICPSYNC_Status;

/**
 *  @brief      Default module configuration structure (defined in vicpsync.c)
 */
extern VICPSYNC_Params VICPSYNC_PARAMS;

/*===========================================================================*/
/**
 * @brief  This is the top level function that allows ARM-side algorithms to 
 *         mark beginning of the usage of individual functional units of VICP  
 *
 * @param  handle                    Algorithm handle
 *
 * @param  res                       Particular function unit of the VICP to 
 *                                   configure
 * @param  intType                   Type of interrupt (FIQ/IRQ) to configure 
 *
 * @param  intLine                   Interrupt line to use (Fixed/Flexible)
 *
 * @param  vicpHandle                void pointer to the vicp handle.
 *
 * @return VICPSYNC_Status           Returns status of this call.    
 *
 * @note   This function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
/*===========================================================================*/
VICPSYNC_Status VICPSYNC_start(IALG_Handle handle, VICPSYNC_ResourceType res, 
        VICPSYNC_InterruptType intType, VICPSYNC_InterruptLine intLine, 
        IRES_VICP2_Handle vicpHandle);

/*===========================================================================*/
/**
 * @brief  This is the top level function that allows the ARM-side algorithms  
 *         to wait for interrupt corresponding to the functional unit of the 
 *         VICP to fire.
 *
 * @param  vicpHandle       void pointer to the vicp handle.
 *
 * @param  res              Particular function unit of the VICP that has been
 *                          configured to respond to interrupt. 
 *
 * @return VICPSYNC_Status  Returns status of this call
 *
 * @note   As per XDM, this function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
/*===========================================================================*/
VICPSYNC_Status VICPSYNC_wait (IRES_VICP2_Handle vicpHandle, 
        VICPSYNC_ResourceType res);

/*===========================================================================*/
/**
 * @brief  This is the top level function that allows the ARM-side algorithms  
 *         to query the status of the interrupt corresponding to the functional 
 *         unit that was configured using VICPSYNC_start call.  
 *
 * @param  vicpHandle      void pointer to the vicp handle.
 *
 * @param  res             Particular functional unit of the VICP to query for
 *                         status of interrupt.  
 *
 * @return Bool            value indicating if the interrupt has fired yet.
 *
 * @note   As per XDM, this function will be called from the algorithm but the
 *         implementation will lie in the application.
 */
/*===========================================================================*/
Bool VICPSYNC_done (IRES_VICP2_Handle vicpHandle, VICPSYNC_ResourceType res);

/*===========================================================================*/
/**
 * @brief  This is the top level function that allows the ARM-side algorithms  
 *         to unregister the ISR associated with the VICP resource that may 
 *         have been previously registered via a call to VICPSYNC_start 
 *
 * @param  vicpHandle      void pointer to the vicp handle.
 *
 * @param  res             Particular functional unit of the VICP to query for
 *                         status of interrupt.  
 *
 * @return VICPSYNC_Status Returns status of this call.    
 */
VICPSYNC_Status VICPSYNC_unregister(IRES_VICP2_Handle vicpHandle, 
        VICPSYNC_ResourceType res);

#ifdef __cplusplus
}
#endif /* extern "C" */


/*@}*/

#endif
/*
 *  @(#) ti.sdo.fc.vicpsync; 1, 0, 0,118; 12-1-2010 17:26:13; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

