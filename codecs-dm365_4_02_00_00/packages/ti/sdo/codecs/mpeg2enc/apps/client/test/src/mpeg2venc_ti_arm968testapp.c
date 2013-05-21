/** ===========================================================================
* @file mpeg2venc_ti_arm968testapp.c
*
* @path $\\(PROJDIR)..\\Client\\Test\Src\\
*
* @desc This is the main application file calling the high level MPEG-4
*       encoding function on ARM968 side. This function also handles/semd
*       interrupts from/to ARM926 for frame encoding
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/

/* --------------------- COMPILATION CONTROL SWITCHES -----------------------*/

/*****************************************************************************/
/*                              INCLUDE FILES                                */
/*****************************************************************************/
/* ---------------------- SYSTEM AND PLATFORM FILES -------------------------*/
/*#include "mpeg2venc_ti_datatypedefs.h"
#include "mpeg2venc_ti_handle.h"
#include "edma_dm510.h"
#include "kld_ti_arm968intc.h"
#include "mpeg2venc_ti_pvop.h"
#include "kld_ti_common.h"
*/

/*----------------------------- PROGRAM FILES -------------------------------*/
#include "kld_ti_arm968intc.h"
#include "kld_ti_common_coprocessor.h"
/*****************************************************************************/
/*     EXTERNAL REFERENCES NOTE : only use if not found in header file       */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/
/* Interrupt vector table
 */
extern unsigned int vec_table[];
/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/
/*****************************************************************************/
/*               PUBLIC DECLARATIONS Defined here, used elsewhere            */
/*****************************************************************************/
/*--------------------------- DATA DECLARATIONS -----------------------------*/

/*-------------------------- FUNCTION PROTOTYPES ----------------------------*/

/*--------------------------------- MACROS ----------------------------------*/
/* XENA_ARM968_DTCM_BASE
 * ARM 968 DTCM starting address is 0x400000 when it is seen from ARM968
 */
#define XENA_ARM968_DTCM_BASE 0x400000
/*****************************************************************************/
/*              PRIVATE DECLARATIONS Defined here, used only here            */
/*****************************************************************************/
/*===========================================================================*/
/**
*@brief This is the main Application code used to call MP2 Encoder on ARM968 .
*       This fucntion takes control from host initiate frame encoding.
*       Checks controfalg from host side and call enoding function
*
*@param  None
*
*@return None
*
*@see    None
*
*@note   None
*/
/*===========================================================================*/

signed int main()
{
    volatile unsigned int*  poll_word;

    /* if the first entry of interrupt vector is NULL, return*/
	if(vec_table[0] == 0)
	{
	    return (-1);
	}

    /* Initialise the pointer with absolute address of the shared memory
     * location which is used for communication between ARM968 and ARM926.
     * This address hard coded over here needs to be in-sync with .cmd file
     */

    poll_word = (unsigned int*)XENA_ARM968_DTCM_BASE;
	*poll_word = 0;

    /* Incase if interrupt is enabled then explicitly set the poll-word to zero
     * since ARM926 will not be initialising this any more */
#ifdef DM360_IPC_INTC_ENABLE
    *poll_word = 0;
#endif


    do
    {
       /* DM510_POWER_OPT macro enables/disables power optimization code. When
        * it is enabled, all coprocessor switched off when they are not running
        * and coprocessors are turned on at the start of frame encoding at
        * turned off at the end of frame encoding
	    */
#ifdef DM510_POWER_OPT
        /* Switch off all coprcoessors and Coprocessor buffers until
		 * ARM968 get interrupt from ARM926 to start frame processing
		 */
		HDVICP_TI_ALL_COPROC_CG_EBL();
		HDVICP_TI_BUF_CG_EBL();
#endif

       /* Going into Superviser mode to enter WFI mode
	    * Refer to design doc for details on DM510_IPC_WFI_ENABLE macro
	    */
#ifdef DM510_IPC_WFI_ENABLE
		asm(" SWI #1 ");
#else
        /*-------------------------------------------------------------------*/
        /* Polling for ARM 926 command   								     */
        /* bit 0 in polling word is used for ARM968 to start                 */
        /*-------------------------------------------------------------------*/
        while(((*poll_word) & 0x01) == 0);
        //*poll_word = 0;
#endif

#ifdef DM510_POWER_OPT
       /* Switch on all coprocessor buffers as the frame encoding starting
	    * now
		*/
		HDVICP_TI_BUF_CG_DBL();
#endif

        /*-------------------------------------------------------------------*/
        /* Check if HOST ARM926 has asked to terminate operation		     */
        /* ARM926 signals 'No more frames to encode' by setting poll word to */
        /* 0xFFFFFFFF                                                        */
        /*-------------------------------------------------------------------*/
        if((*poll_word) == 0xFFFFFFFF)
            break;

        /*-------------------------------------------------------------------*/
        /* If the ARM926 command is to encode a frame set the wait bit to 0  */
        /* poll word and call encode function on ARM968                      */
        /*-------------------------------------------------------------------*/
        (*poll_word) &= 0xFFFFFFFE ;
        /* high level function to encode one frame*/



        MPEGVENC_TI_Encode_Frame968();

#ifdef DM510_POWER_OPT
        /* Switch off all coprocessor buffers after completion of frame encoding
		 * for power optimization/saving
		 */
		HDVICP_TI_BUF_CG_EBL();
#endif

#ifdef DM360_IPC_INTC_ENABLE
        /* ------------------------------------------------------------------*/
        /* Send interrupt to ARM926: FIQ by writing sw_int_out1 bit KLD INTC */
        /* This interrupt says ARM926 that frame encoding is completed       */
        /* ------------------------------------------------------------------*/
         SW_INT_OUT1();
#else
         /* -----------------------------------------------------------------*/
         /* in polling mode set poll word to 2 to inform ARM926 that frame   */
         /* encoding is completed (bit 1 for ARM926 to start)                */
         /* -----------------------------------------------------------------*/
		(*poll_word) |= 0x02 ;
#endif

    }while(1);

    return (0);
}


/*!
 *! Revision History
 *! ================
 *! 17-Jun-2007   RSV: Added Interrupt based IPC and Power optimization code
 *!
 *! 02-Apr-2007   RSV: File name and other chages to meet coding guidelines
 *!                    requirements.
 *!
 *! 18-Dec-2006   RSV: Create file and added initial code.
 */


