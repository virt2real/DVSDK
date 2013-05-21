/** ===========================================================================
* @file hdvicp_framework.c
*
* @path $(PROJDIR)\src
*
* @brief This File contains function definitions which enable non-blocking 
*            call simulation for blocking process-call in XDM 1.0 
* =============================================================================
* Copyright (c) Texas Instruments Inc 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
**============================================================================*/
/* ------compilation control switches -------------------------*/
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
/* ----- system and platform files ----------------------------*/
#include <xdc/std.h>
#include <ti/xdais/xdas.h> 
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/sdo/fc/utils/api/alg.h>
#include <ti/sdo/fc/hdvicpsync/hdvicpsync.h>
#include <ti/sdo/linuxutils/vicp/include/vicp.h>

/*-------program files ----------------------------------------*/
#include "testapp_arm926intc.h"
//#define _DBG_VERBOSE
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/* ENABLE_PROFILE_AT_FRM_LVL_ON_926 - enables user to capture actual
 * cycle consumption for "start" "end" and "ARM-968" portions 
 * of the decode process call.
 */
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
extern XDAS_UInt32 profileSrt, profileEd, profile968;
#endif
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
IRES_HDVICP_Handle g_handle;
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------macros ----------------------------------------------*/
/* ARM968_SHARED_MEM_START_LOCATION is the actual ARM-address as 
 * seen from ARM926 into the DTCM memory of ARM968. This address 
 * is used to poll for task completion on ARM968 when the decoder
 * is NOT-running in Interrupt mode. This value has to be sync-ed
 * up with the command file.
 */
#ifdef ENABLE_DM510
#define ARM968_SHARED_MEM_START_LOCATION    0x02160000
#else
#define ARM968_SHARED_MEM_START_LOCATION    0x01F60000
#endif
/*--------data declarations -----------------------------------*/
/* Function pointer which is initized to user provided ISR function */
Bool (* g_fnPtr) (IRES_HDVICP_Handle);
/* Global function whose address is filled into the interrupt vector 
 * table on arrival of the specified interrupt thsi function is called
 */
void Host_int_handler();

#ifdef DM365_IPC_INTC_ENABLE
/* If interrupt is enabled then there is no need to access the 
 * DTCM memory - interrupt handler would modify the global flag 
 * which is present in the data memory of ARM926 itself - used just 
 * for compatibility reasons with non-interrupt mode of operation.*/
volatile XDAS_UInt32 poll_word_on926;
volatile XDAS_UInt32 *poll_word = &poll_word_on926;
#else
/* Incase if interrupt is disabled then ARM926 continously polls on 
 * a shared memory location between ARM968 and ARM926 in the 
 * ARM968's DTCM memory.
 */
volatile XDAS_UInt32 *poll_word = 
        (XDAS_UInt32 *) ARM968_SHARED_MEM_START_LOCATION;  
#endif
/*--------function prototypes ---------------------------------*/
/*--------function definitions---------------------------------*/
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
void Host_DCache_Flush(void *hdvicpHandle)
{
#ifdef ENABLE_CACHE
    ARM926_CleanFlush_Dcache();
#endif //ENABLE_CACHE
    return;
}/*  main  */

/*****************************************************************************/
/**
*@func Host_int_handler()
*@brief  TI's (Texas Instrument) implementation of default ISR function 
*           registered in the interrupt vector table.
*
*        This is a constant global function which is registered in the 
*           interrupt vector table refer to testapp_inthandler.asm file for
*           actual implemntation. Since different algorithm would want different 
*           ISR routines this functions in turns calls the algorithm
*           registered ISR initialised by HDVICP_configure function.
*
*@param  None
*
*@return None
*
*/
/*****************************************************************************/
void Host_int_handler( void )
{
  (*g_fnPtr)(g_handle);
  return;
}

/*****************************************************************************/
/**
*@func VICP_register()
*@brief  TI's (Texas Instrument) implementation of HDVICP configuration 
*           module
*
*        Configuration function which initialises its global variables with 
*        algorithm specific ISR function and its context information - to be 
*           called when actual interrupt occurs
*
*@param  VICP_ResourceType resource
*       Used to initialise the global variable. 
*
*@param  VICP_InterruptLine intrLine
*        Not used
*
*@param  VICP_InterruptType intrType
*       Not Used
*
*@return None
*
*/
/*****************************************************************************/
VICP_Status VICP_register(VICP_ResourceType resource,
                          VICP_InterruptLine intrLine,
                          VICP_InterruptType intrType)
/* ARGSUSED */
{
#ifdef DEBUG_ENABLE
        printf("CODEC_DEBUG_ENABLE: VICP_Register called \n");
#endif
#ifndef DEBUG_ENABLE
	printf("VICP_Register called \n");
#endif
    g_handle = (IRES_HDVICP_Handle) resource;
    g_fnPtr = HDVICPSYNC_done;
    //(*poll_word) = 0x0;  
    return (VICP_OK);
}

VICP_Status VICP_unregister(VICP_ResourceType resource)
/* ARGSUSED */
{
#ifdef DEBUG_ENABLE
        printf("CODEC_DEBUG_ENABLE: VICP_UnRegister called \n");
#endif
#ifndef DEBUG_ENABLE
	printf("VICP_UnRegister called \n");
#endif
    /*If FC version < 25_02_26 comment below 2 lines, for low letency mode*/
    g_handle = NULL;
    g_fnPtr = NULL;
    //(*poll_word) = 0x0;  
    return (VICP_OK);
}
/*****************************************************************************/
/**
*@func VICP_wait()
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
*@param  VICP_ResourceType resource
*        HDVICP handle address - initialised with default values by 
*           HDVICP_initHandle function 
*
*@return None
*
*/
/*****************************************************************************/
VICP_Status VICP_wait(VICP_ResourceType resource)
/* ARGSUSED */
{
#ifdef DEBUG_ENABLE
        printf("CODEC_DEBUG_ENABLE: VICP_wait called \n");
#endif
#ifdef _DBG_VERBOSE
	printf("VICP_wait called \n");
#endif
    /*
     * Set the task priority to low over here
     */
    /*
     * When interrupt mode is not enabled then this poll word 
     * would be pointing to a location on ARM968 DTCM. If interrupt 
     * mode is enabled then setting this flag has no meaning.
     */
    (*poll_word) |= 0x01;  
    /* 
     * Waiting for ARM968 to finish. In interrupt mode this flag will be 
     * set by HDVICP_Done function called by interrupt handler on ARM926 
     * side.
     */
#ifdef DEBUG_ENABLE
        printf("CODEC_DEBUG_ENABLE: Control is given to ARM968\n");
#endif
#ifdef _DBG_VERBOSE
    printf("Control is given to ARM968\n");
#endif
    while(((*poll_word) & 0x02) == 0);  // bit 1 for ARM968 to start
#ifdef DEBUG_ENABLE
        printf("CODEC_DEBUG_ENABLE: Control is back to ARM926\n");
#endif
#ifdef _DBG_VERBOSE
    printf("Control is back to ARM926\n");
#endif
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        profile968 = profileEnd(0);
#endif
    /*---------------------------------------------------------*/
    /*   Configuring timer-0 to start counting for the end portion 
     *   of process call            */  
    /*---------------------------------------------------------*/            
#ifdef ENABLE_PROFILE_AT_FRM_LVL_ON_926
        profileInit(0); 
        profileStart(0);
#endif
    (*poll_word) &= 0xFFFFFFFD ;   // Set the wait bit to 0 again
    return (VICP_OK);
}

/*****************************************************************************/
/**
*@func VICP_done()
*@brief  TI's (Texas Instrument) implementation of HDVICP done module
*
*        HDVICP_doen function is called by the ISR function implemented by the
*           algorithm which would inturn update the global semaphore on which 
*           HDVICP_wait function is pending. This global defintion allows for 
*           unified semaphore handling feature for multiple algorithms.
*
*@param  VICP_ResourceType resource
*        HDVICP handle address - initialised with default values by 
*           HDVICP_initHandle function 
*
*@return None
*
*/
/*****************************************************************************/
VICP_Status VICP_done(VICP_ResourceType resource, int *done)
/* ARGSUSED */
{
    /*  
    * This function will be called by the interrupt 
    * handler function when it detects end-of-slice
    * or end-of-frame processing.
    */
    /* -------------------------------------------------------*/
    /* Send interrupt to ARM926: Set the poll bit              */
    /* -------------------------------------------------------*/
    (*poll_word) |= 0x02 ;   //bit 1 for ARM926 to start
    return (VICP_OK);
}

/*****************************************************************************/
/**
*@func H264VENC_TI_getArm926TcmBase()
*@brief  TI's (Texas Instrument) implementation of getting arm926 base address
*
*   H264VENC_TI_getArm926TcmBase function is called by the codec to get arm926
*    tcm memory base address, if codec uses Tcm memory as temporary buffer
*
*@param  VICP_ResourceType resource
*        HDVICP handle address - initialised with default values by 
*           HDVICP_initHandle function 
*
*@return None
* NOTE: Don't change function name and prototype of the function, this is 
* referred by codec, just change address of TCM depending on availibility.
*/
/*****************************************************************************/

int  H264VENC_TI_GetArm926TcmBase(unsigned int *Ram0BaseAddr, unsigned int *Ram1BaseAddr)
{
    *Ram0BaseAddr =(unsigned int) 0x00011000;
    *Ram1BaseAddr =(unsigned int) 0x00014000;

    return (0);
}

/*!
*! Revision History
*! ================
*! 31-May-2007 Vinay M K: Modified to comply with MMCodecs 
*!                      coding guidelines.
*! 15-May-2007 Vinay M K: Created.
*/
