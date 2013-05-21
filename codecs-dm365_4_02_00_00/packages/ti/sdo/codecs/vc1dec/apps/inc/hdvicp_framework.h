/** ===========================================================================
* @file hdvicp_framework.h
*
* @path $(PROJDIR)\..\test\src
*
* @brief This File contains function declarations and structures required to
*            implement hdvicp framework
* =============================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**============================================================================*/
/* ------compilation control switches -------------------------*/
#ifndef HDVICP_FRAMEWORK_H
#define HDVICP_FRAMEWORK_H
/***************************************************************
*  INCLUDE FILES
****************************************************************/
/* ----- system and platform files ----------------------------*/
//#include <xdas.h>
//#include <ialg.h>
//#include <tistdtypes.h>
#include <ti/xdais/xdas.h>
//#include <ialg.h>
//#include <ti/xdais/ialg.h>
/*-------program files ----------------------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
typedef struct hdvicpAppHandle
{
    /*! handle size useful when extended */
    XDAS_UInt32    handleSize;
    /*! process-Id */
    XDAS_UInt32    processId;
    /*! application specific information */
    void*       info;
} HDVICP_Obj;

typedef HDVICP_Obj* HDVICP_Handle;
/*--------function prototypes ---------------------------------*/
/*===========================================================================*/
/*
 *@brief  This is the top level function which flushes  and invalidate Data
 *        cache of ARM926.
 *
 *@param  void *hdvicpHandle
 *        HDVICP handle address - initialised with default values by
 *        HDVICP_initHandle function
 *
 *@return None
 *
 *@note   None
 */
/*===========================================================================*/
void Host_DCache_Flush(void *hdvicpHandle);
/*****************************************************************************/
/**
*@func HDVICP_initHandle()
*@brief  TI's (Texas Instrument) implementation of HDVICP initialization
*           module
*
*        The HDVICP_initHandle function is called by the test application to
*        initialise the HDVICP handle. This initialized handle will be passed
*        to algorithm instance as well. When the algorithm calls HDVICP wait
*        and done functions HDVICP handle needs to be passed on for context.
*
*@param  void *hdvicpHandle
*        HDVICP handle address - will be initialised with default values by
*           this function
*
*@return None
*
*/
/*****************************************************************************/
void HDVICP_initHandle(void * hdvicpHandle);
/*****************************************************************************/
/**
*@func HDVICP_configure()
*@brief  TI's (Texas Instrument) implementation of HDVICP configuration
*           module
*
*        Configuration function which initialises its global variables with
*        algorithm specific ISR function and its context information - to be
*           called when actual interrupt occurs
*
*@param  IALG_Handle handle
*       Algorithm handle to be passed as context information to ISR routine.
*
*@param  void *hdvicpHandle
*        HDVICP handle address - initialised with default values by
*           HDVICP_initHandle function
*
*@param  void (*ISRfunctionptr)(IALG_Handle handle)
*        Function pointer which is registered as the interuppt service
*           routine from the algorithm.
*
*@return None
*
*/
/*****************************************************************************/
void HDVICP_configure(IALG_Handle handle,
                      void * hdvicpHandle,
                      void (*ISRfunctionptr)(IALG_Handle handle));
/*****************************************************************************/
/**
*@func HDVICP_wait()
*@brief  TI's (Texas Instrument) implementation of HDVICP wait
*           module
*
*        XDMv1.0 specifications doesn't allow for non-blocking process
*           call in a multi-core architecture. If bulk of the processign
*           happens in co-processors then the host processor would spend bulk
*           of its time checking for completion of tasks on the co-processors.
*        HDVICP wait function allows the algorithm to exactly specify the time
*           between which the host processor is "free".
*
*@param  void *hdvicpHandle
*        HDVICP handle address - initialised with default values by
*           HDVICP_initHandle function
*
*@return None
*
*/
/*****************************************************************************/
void HDVICP_wait( void * hdvicpHandle );
/*****************************************************************************/
/**
*@func HDVICP_done()
*@brief  TI's (Texas Instrument) implementation of HDVICP done module
*
*        HDVICP_doen function is called by the ISR function implemented by the
*           algorithm which would inturn update the global semaphore on which
*           HDVICP_wait function is pending. This global defintion allows for
*           unified semaphore handling feature for multiple algorithms.
*
*@param  void *hdvicpHandle
*        HDVICP handle address - initialised with default values by
*           HDVICP_initHandle function
*
*@return None
*
*/
/*****************************************************************************/
void HDVICP_done( void * hdvicpHandle );

/*--------macros ----------------------------------------------*/
/*--------function definitions---------------------------------*/

#endif /* HDVICP_FRAMEWORK_H */

/*!
*! Revision History
*! ================
*! 05-May-2007 Vinay M K: Created.
*/

