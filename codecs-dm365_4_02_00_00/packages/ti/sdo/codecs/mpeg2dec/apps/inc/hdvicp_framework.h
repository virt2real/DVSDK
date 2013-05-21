/** ==========================================================================
* @file  hdvicp_framework.h
*
* @path  $(PROJDIR)\..\Test\Inc
*
* @brief  Header file for hdvicp_framework.c
*
* ============================================================================
*
* Copyright (c) Texas Instruments Inc 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied 
*
* ===========================================================================
*/

#ifndef __HDVICP_FRAMEWORK__
#define __HDVICP_FRAMEWORK__

#include <ti/xdais/xdas.h>
#include <ti/xdais/ialg.h> 

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
                      void * hdvicpHandle, 
                      void (*ISRfunctionptr)(IALG_Handle handle));

/*===========================================================================*/
/*
 *@brief  This is the top level function on the gem side, which implements
 *        the hdvicp_wait(). Current implementation allows GEM to wait on a 
 *        global intc flag which will be 1 as long as one frame is not 
 *        completed.
 *
 *@param  hdvicpHandle      void pointer to the hdvicp handle.
 *
 *@return none
 *
 *@note   As per XDM, this function will be called from the algorithm but the
 *        implementation will lie in the application.
 */
/*===========================================================================*/
void HDVICP_wait (void * hdvicpHandle);

/*===========================================================================*/
/*
 *@brief  This is the top level function on the gem side, which implements
 *        the hdvicp_done(). Current implementation allows GEM to set a 
 *        global intc flag to 0 to come out of hdvicp_wait() as soon as one 
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
void HDVICP_done (void * hdvicpHandle);

#endif

/*!
*! Revision History
*!    05-06-2007 : Created.
*/
