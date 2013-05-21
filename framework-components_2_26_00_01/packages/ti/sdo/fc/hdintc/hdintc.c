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
 *  @file       hdintc.c
 *
 *  @brief      HDINTC Interface Definitions (C64P) - 
 *              Application interface to the Interrupt Registry Manager. 
 *              Registers non-BIOS, non-dispatched interrupt service handlers
 *              to register and synchronize with HDVICP interrupts.
 */

/**
 *  @defgroup   DSPHDINTC HDINTC (C64P)
 *
 *              Application interface to the Interrupt Registry Manager. 
 *              Registers non-BIOS, non-dispatched interrupt service handlers
 *              to register and synchronize with HDVICP interrupts.
 *              This module is used by frameworks or applications which have
 *              XDAIS algorithms that use HDVICP hardware accelarators and
 *              implement own interrupt handlers.
 */

#include <xdc/std.h>
#include <ti/xdais/xdas.h>

#define ti_sdo_fc_ires_NOPROTOCOLREV
#include <ti/sdo/fc/hdintc/hdintc.h>
#include <ti/sdo/fc/ires/hdvicp/ires_hdvicp.h>

#include <ti/bios/include/std.h>
#include <ti/bios/include/c64.h>
#include <ti/bios/include/hwi.h>
#ifndef HDINTC_SPINLOOP_SYNCHRONIZATION
#include <ti/bios/include/sem.h>
#endif
#define NUM_HDVICP_PROCESSORS 2

#define FRAMEMASK(x) (1 << (x)) 

extern cregister volatile unsigned int ISR;

/*---------------------------------------------------------------------------*/
/*  Global Algorithm handle which will be initialized with the argument to   */
/*  the algorithm's MB processing function.                                  */
/*---------------------------------------------------------------------------*/
static IALG_Handle HDINTC_handle[NUM_HDVICP_PROCESSORS];

/*---------------------------------------------------------------------------*/
/*  Global function pointer which will be initialized to the algorithm's MB  */
/*  processing function and will be called by the gem interrupt handler      */
/*  function.                                                                */
/*---------------------------------------------------------------------------*/
static void (* HDINTC_fnPtr[NUM_HDVICP_PROCESSORS])(IALG_Handle handle);


/*---------------------------------------------------------------------------*/
/*  The gem interrupt handler function. The application ties down this func  */
/*  as service routine to the interrupts received by GEM from ARM968.        */
/*---------------------------------------------------------------------------*/
interrupt void HDINTC_int_handler_0 ();
interrupt void HDINTC_int_handler_1 ();

/*
 *  This global synchronization flag is used in hdvicp_wait() to synchronize
 *  with the completion of the full-frame processing by the HDVICP. The 
 *  HDVICP interrupt handler that gets called during MB-pair processing 
 *  detects the end of frame and signals this via HDVICP_done() function call
 *  which either sets the global synchronization flag or posts the semaphore.
 */
#ifdef HDINTC_SPINLOOP_SYNCHRONIZATION
/*
 * Use global variable to spin-loop. This is a busy wait, so DSP cycles will
 * not be released to same or lower pri tasks.
 */
volatile XDAS_Int8 HDINTC_finished[NUM_HDVICP_PROCESSORS];
#else 
/*
 * Use Semaphore based synchronization so that when in HDVICP_done, current
 * task will block and release DSP cycles for same or lower priority tasks 
 * while waiting for HDVICP processing to finish.
 */
typedef struct HDINTC_Sync {
    Int         intrId;
    Int         eventId;
    Int         mask;
    SEM_Obj     frameDone;
} HDINTC_Sync;

static HDINTC_Sync syncState[NUM_HDVICP_PROCESSORS];

/*---------------------------------------------------------------------------*/
/*  Initialization function that sets up the state object with the configured*/
/*  interrupt.                                                               */
static void _HDINTC_init();

#endif

typedef enum {
        HDVICP_STATE_RESET, 
        HDVICP_STATE_CLEANUP, 
        HDVICP_STATE_DONE
} HDINTC_State ;

static void HDINTC_setState(int processorId, HDINTC_State state)
{
    switch (state) {
        case HDVICP_STATE_RESET: 
        
#ifdef HDINTC_SPINLOOP_SYNCHRONIZATION
            HDINTC_finished[processorId] = 0;
#else 
#endif
            break;

        case HDVICP_STATE_CLEANUP: 
        
#ifndef HDINTC_SPINLOOP_SYNCHRONIZATION
#endif
            break;

        case  HDVICP_STATE_DONE:

#ifdef HDINTC_SPINLOOP_SYNCHRONIZATION

            HDINTC_finished[processorId] = 1;
#else 
            /* Called by HDVICP_done, this manually triggers the BIOS ISR.
               Note that this interrupt will be serviced immediately after
               returning from the non-BIOS ISR */  
            ISR = syncState[processorId].mask;
#endif
    }
}


/*===========================================================================*/
/*
 *@brief  This is the top level function on the gem side, which sets the 
 *        interrupt configuration for the interrupts received from ARM968.
 *        In effect, this function currently sets the global function ptr   
 *        to the actual MB processing decode function that needs to be called
 *        from the interrupt service routine.
 *
 *@param  handle                      Algorithm handle
 *
 *@param  hdvicpHandle                void pointer to the hdvicp handle.
 *
 *@param  (*ISRfunctionptr)(handle)   Function pointer to the MB pair 
 *                                    processing function of the algorithm.
 *
 *@return none
 *
 *@note   As per XDM, this function will be called from the algorithm but the
 *        implementation will lie in the application.
 */
/*===========================================================================*/
void HDVICP_configure(IALG_Handle handle,
                      void *hdvicpHandle,
                      void (*ISRfunctionptr)(IALG_Handle handle))
{
    extern volatile cregister unsigned int ICR;
    int tVectId;
    int tEventId;
    int processorId = ((IRES_HDVICP_Handle)hdvicpHandle)->id;

#ifndef HDINTC_SPINLOOP_SYNCHRONIZATION
    HWI_Attrs hwiAttrs = HWI_ATTRS;
    HDINTC_Sync * state;

    _HDINTC_init();
#endif

    /*-----------------------------------------------------------------------*/
    /*  Initialize the argument to the MB processing function that is        */
    /*  required to be called by the ISR.                                    */
    /*  Store the algorithm handle corresponding to the ISR function         */ 
    /*-----------------------------------------------------------------------*/
    HDINTC_handle[processorId] = handle;
    
    /*-----------------------------------------------------------------------*/
    /*  Initialize the global function ptr to the MB processing function     */
    /*  which will be called from the ISR.                                   */ 
    /*  Store the function pointer for this non-BIOS ISR that will be called */
    /*  for each sample                                                      */ 
    /*-----------------------------------------------------------------------*/
    HDINTC_fnPtr[processorId]  = ISRfunctionptr;

    /* initialize HDINTC_finished[procId] state to RESET  */
    HDINTC_setState(processorId, HDVICP_STATE_RESET);

    /* Obtain configured Vect and Event Ids that corresponds to HDINTC event */ 
    tVectId  = (processorId==0 ? HDINTC_PARAMS.interruptVectorId_0 : 
                                 HDINTC_PARAMS.interruptVectorId_1);
    tEventId = (processorId==0 ? HDINTC_PARAMS.hdvicpInterruptEventNo_0 : 
                                 HDINTC_PARAMS.hdvicpInterruptEventNo_1);

    /* Plug the local HDINTC handler at this Vector Id, this is a non BIOS 
       interrupt handler */  
    /*---------------------------------------------------------------------*/
    /*  The following function initializes and ties down the GEM interrupt */
    /* the last argument (-1) implies use CPU_COPY to store the IST */ 
    /*---------------------------------------------------------------------*/
    C64_plug(tVectId, 
             (Fxn)(processorId == 0 ? HDINTC_int_handler_0 : 
                                         HDINTC_int_handler_1),
             -1);

    /* Map the HDINTC event to the configured vector id */  
    HWI_eventMap(tVectId, tEventId);

    /* Clear previous interrupts that might be still set for this vector id */
    ICR = (1 << tVectId);

    /* Enable the Interrupts for this vector id */ 
    C64_enableIER((1 << tVectId));      

    /*---------------------------------------------------------------------*/
    /* The above code sets up the non-BIOS ISR that gets trigged for each  */
    /* sample. Once an entire frame of data is available, the non-BIOS ISR */ 
    /* function calls HDVICP_done that "software triggers" a  BIOS ISR     */ 
    /* that we set up below.                                               */   
    /*---------------------------------------------------------------------*/

#ifndef HDINTC_SPINLOOP_SYNCHRONIZATION
    /*
     *  Setup the End-Of-Frame (EOF) interrupt handling. Most of the needed
     *  work is done in the DSP/BIOS config (tcf) file. Here, we just need
     *  to enable the interrupts.
     */

    /* Obtain the state object corresponding to this processor Id */
    state = &syncState[processorId];

    /* Create and initialize a semaphore for it */ 
    SEM_new(&state->frameDone, 0);

    /* Map the unused event Id (configured for the BIOS ISR) to an available 
       interrupt line */ 
    HWI_eventMap(state->intrId, state->eventId);

    hwiAttrs.arg = (Arg)&state->frameDone;
    
    /* Configure the BIOS HWI so that the SEM_post is called when the
       interrupt is triggered */ 
    HWI_dispatchPlug(state->intrId, (Fxn)SEM_post, -1, &hwiAttrs);

    /* Clear previous interrupts*/
    ICR = state->mask;

    /* Enable the BIOS interrupt */ 
    C64_enableIER(state->mask);
#endif

    return;
}

#ifndef HDINTC_SPINLOOP_SYNCHRONIZATION
/*===========================================================================*/

/* 
 *@brief  This function intiializes the state object with the interrupts  
 *        to be used by the BIOS ISR
 */
 
static void _HDINTC_init()
{
    static int _initialized = 0;

    if (0 == _initialized) {

        syncState[0].intrId = HDINTC_PARAMS.biosInterruptVectorId_0; 
        syncState[0].eventId = HDINTC_PARAMS.biosInterruptEventNo_0;
        syncState[0].mask = FRAMEMASK(HDINTC_PARAMS.biosInterruptVectorId_0);
        
        syncState[1].intrId = HDINTC_PARAMS.biosInterruptVectorId_1; 
        syncState[1].eventId = HDINTC_PARAMS.biosInterruptEventNo_1;
        syncState[1].mask = FRAMEMASK(HDINTC_PARAMS.biosInterruptVectorId_1);

        _initialized = 1; 
    }
}
#endif

/*===========================================================================*/

/* 
 *@brief  This is the top level function on the gem side, which corresponds
 *        to the actual interrupt service routine for interrupts received 
 *        by GEM. The bare minimum that the application needs to do in this 
 *        non-BIOS ISR without dispatcher is to handle interrupts from Kaleido 
 *        processor:0.
 */
interrupt
void HDINTC_int_handler_0 () // processorId = 0 
{
  int processorId = 0;

  /* Call function configured for this interrupt (during HDVICP_configure) */
  (*HDINTC_fnPtr[processorId])(HDINTC_handle[processorId]);

  return;
}

/* 
 * non-BIOS ISR without dispatcher to handle interrupts from Kaleido 
 * processor:1
 */
interrupt
void HDINTC_int_handler_1 () // processorId = 0 
{
  int processorId = 1;

  /* Call function configured for this interrupt (during HDVICP_configured)*/   
  (*HDINTC_fnPtr[processorId])(HDINTC_handle[processorId]);

  return;
}
/*===========================================================================*/
/*
 *@brief  This is the top level function on the gem side, which implements
 *        the hdvicp_wait(). Current implementation allows GEM to wait on a 
 *        HDINTC_intc flag which will be 1 as long as one frame is not 
 *        completed.
 *
 *@param  hdvicpHandle      void pointer to the hdvicp handle.
 *
 *@return none
 *
 *@note   This function gets called by the algorithm as an external callback
 *        function  supplied by the application framework.
 */
/*===========================================================================*/
void HDVICP_wait(void *hdvicpHandle)
{
 
    int processorId = ((IRES_HDVICP_Handle)hdvicpHandle)->id;

#ifdef HDINTC_SPINLOOP_SYNCHRONIZATION

    while (!HDINTC_finished[processorId]) {
        ; 
    }
    
#else

    /* Pend on the semaphore. Semaphore will be posted by the BIOS ISR when a 
       frame's worth of data is processed */
    SEM_pend(&syncState[processorId].frameDone, SYS_FOREVER);

    /* clean up state */
    HDINTC_setState(processorId, HDVICP_STATE_CLEANUP);

#endif
}

/*===========================================================================*/
/*
 *@brief  This is the top level function on the gem side, which implements
 *        the hdvicp_done(). Current implementation allows GEM to set a 
 *        HDINTC_intc flag to 0 to come out of hdvicp_wait() as soon as one 
 *        frame is completed.
 *
 *@param  hdvicpHandle      void pointer to the hdvicp handle.
 *
 *@return none
 *
 *@note   As per XDM, this function will be called from the algorithm but the
 *        implementation will lie in the application.
 */
/*===========================================================================*/
void HDVICP_done(void *hdvicpHandle)
{
    int processorId = ((IRES_HDVICP_Handle)hdvicpHandle)->id;

    /* Manually trigger the BIOS ISR */ 
    HDINTC_setState(processorId, HDVICP_STATE_DONE);
}
 
/*
 *  @(#) ti.sdo.fc.hdintc; 1, 0, 4,133; 12-1-2010 17:24:48; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

