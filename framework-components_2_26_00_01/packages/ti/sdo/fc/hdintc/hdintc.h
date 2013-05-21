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
 *  @file       ti/sdo/fc/hdintc/hdintc.h
 *
 *  @brief      HDINTC Interface Definitions -
 *              Application interface to the Interrupt Registry Manager.
 *              Registers non-BIOS, non-dispatched interrupt service handlers
 *              to register and synchronize with HDVICP interrupts.
 */

/**
 *  @defgroup   ti_sdo_fc_hdintc_HDINTC HDINTC
 *
 *              Application interface to the Interrupt Registry Manager.
 *              Registers non-BIOS, non-dispatched interrupt service handlers
 *              to register and synchronize with HDVICP interrupts.
 *              This module is used by frameworks or applications which have
 *              XDAIS algorithms that use HDVICP hardware accelarators and
 *              implement own interrupt handlers.
 */

#ifndef ti_sdo_fc_hdintc_HDINTC_
#define ti_sdo_fc_hdintc_HDINTC_

/** @ingroup    ti_sdo_fc_hdintc_HDINTC */
/*@{*/


#ifdef __cplusplus
extern "C" {
#endif

#include <ti/xdais/ialg.h>
#include <ti/xdais/xdas.h>

#define HDINTC_GTNAME "ti.sdo.fc.hdintc"  /**< Name to identify the GT module */

/**
 *  @name Defines: Status Codes
 *
 */
/*@{*/
#define HDINTC_SOK             0  /**< HDINTC Status Code: Successful. */
#define HDINTC_EOUTOFMEMORY   -1  /**< HDINTC Status Code: Failed to allocate
                                    memory for the handle. */
#define HDINTC_EFAIL          -2  /**< HDINTC Status Code: Unspecified error. */
/*@}*/

/**
 *  @brief      The module configuration structure for HDINTC implementation.
 *
 *  @remarks    It is set at design time by the system integrator to ensure
 *              the interrupt lines that are used to process HDVICP generated
 *              interrupts are not mapped by any other interrupt event.
 *              Additionally, the HDVICP event-numbers are configurable to
 *              support different SoCs.
 */
typedef struct HDINTC_Params {

    /**
     *  @brief      Interrupt Vector 0
     *
     *  @remarks    Map this to an unused interrupt vector ID
     */
     int interruptVectorId_0;

    /**
     *  @brief      Interrupt Vector 1
     *
     *  @remarks    Map this to an unused interrupt vector ID
     */
     int interruptVectorId_1;

    /**
     *  @brief      Interrupt Event 0
     *
     *  @remarks    This must match the physical event-id associated with the
     *              HDVICP processor:0 interrupts that need to be serviced by
     *              GEM, via the interrupt line selected by
     *              'interruptVectorId_0'.
     */
    int hdvicpInterruptEventNo_0;

    /**
     *  @brief      Interrupt Event 1
     *
     *  @remarks    This must match the physical event-id associated with the
     *              HDVICP processor:0 interrupts that need to be serviced by
     *              GEM, via the interrupt line selected by 'interruptVectorId_0'.
     */
    int hdvicpInterruptEventNo_1;

    /**
     *  @brief      BIOS Interrupt Vector ID 0
     *
     *  @remarks    Map this to an unused interrupt vector ID
     *
     *  @remarks    This vector ID is going to be used to set up a BIOS ISR
     */
    int biosInterruptVectorId_0;

    /**
     *  @brief      BIOS Interrupt Vector ID 1
     *
     *  @remarks    Map this to an unused interrupt vector ID
     *
     *  @remarks    This vector ID is going to be used to set up a BIOS ISR
     */
    int biosInterruptVectorId_1;

    /**
     *  @brief      BIOS Interrupt Event 0
     *
     *  @remarks    This must correspond to an unused event on this device.
     *              This is a dummy event that will be mapped to the
     *              biosInterruptVectorId_0 above.
     *
     *  @remarks    This interrupt will be software triggered (by writing to
     *              the ISR), it won't be triggered by an actual event.
     */
    int biosInterruptEventNo_0;

    /**
     *  @brief      BIOS Interrupt Event 1
     *
     *  @remarks    This must correspond to an unused event on this device.
     *              This is a dummy event that will be mapped to the
     *              biosInterruptVectorId_1 above.
     *
     *  @remarks    This interrupt will be software triggered (by writing to
     *              the ISR), it won't be triggered by an actual event.
     */
    int biosInterruptEventNo_1;
} HDINTC_Params;


/**
 *  @brief      Default module configuration structure (defined in hdintc.c).
 */
extern HDINTC_Params HDINTC_PARAMS;

/*---------------------------------------------------------------------------*/
/*  Dummy structure for HDVICP handle. Currently not at all used by the      */
/*  algorithm except for passing it with hdvicp calls.                       */
/*---------------------------------------------------------------------------*/
typedef struct hdvicpAppHandle
{
    /*-----------------------------------*/
    /* handle size useful when extended  */
    /*-----------------------------------*/
    XDAS_UInt32    handleSize;

    /*-----------------------------------*/
    /*  process-Id                       */
    /*-----------------------------------*/
    XDAS_UInt32    processId;

    /*-----------------------------------*/
    /* application specific information  */
    /*-----------------------------------*/
    void*       info;

} HDVICP_Obj;

typedef HDVICP_Obj* HDVICP_Handle;


/**
 * @brief   This is the top level function on the gem side, which sets the
 *          interrupt configuration for the interrupts received from ARM968.
 *          In effect, this function currently sets the global function ptr
 *          to the actual MB processing decode function that needs to be called
 *          from the interrupt service routine.
 *
 * @param   handle              Algorithm handle
 * @param   hdvicpHandle        void pointer to the hdvicp handle.
 * @param   ISRfunctionptr      Function pointer to the MB pair
 *                              processing function of the algorithm.
 *
 * @return  none
 *
 * @remarks This function will be called from the algorithm but the
 *          implementation will lie in the application.
 */
/*===========================================================================*/
void HDVICP_configure(IALG_Handle handle,
                      void * hdvicpHandle,
                      void (*ISRfunctionptr)(IALG_Handle handle));


/**
 * @brief   This is the top level function on the gem side, which implements
 *          the hdvicp_wait(). Current implementation allows GEM to wait on a
 *          global intc flag which will be 1 as long as one frame is not
 *          completed.
 *
 * @param   hdvicpHandle      void pointer to the hdvicp handle.
 *
 * @return  none
 *
 * @remarks This function will be called from the algorithm but the
 *          implementation will lie in the application.
 */
void HDVICP_wait (void * hdvicpHandle);


/**
 * @brief   This is the top level function on the gem side, which implements
 *          the hdvicp_done(). Current implementation allows GEM to set a
 *          global intc flag to 0 to come out of hdvicp_wait() as soon as one
 *          frame is completed.
 *
 * @param   hdvicpHandle      void pointer to the hdvicp handle.
 *
 * @return  none
 *
 * @remarks This function will be called from the algorithm but the
 *          implementation will lie in the application.
 */
void HDVICP_done (void * hdvicpHandle);

#ifdef __cplusplus
}
#endif /* extern "C" */

/*@}*/

#endif
/*
 *  @(#) ti.sdo.fc.hdintc; 1, 0, 4,133; 12-1-2010 17:24:48; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

