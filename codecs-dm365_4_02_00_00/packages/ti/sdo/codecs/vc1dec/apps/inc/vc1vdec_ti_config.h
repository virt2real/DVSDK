#ifndef CONFIG_H
#define CONFIG_H

/*!
******************************************************************************
* @file vc1vdec_ti_config.h

* @path $(PROJDIR)\Inc

*@brief This file contains various macros and context structure for VC1.
*
* Copyright (c) Texas Instruments Inc 2005, 2006

* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*  @defgroup  CONF_FILE Configuararion file for decoder
******************************************************************************/
/*!
*! Revision History
*!    05-11-2006 Krishnakanth Rapaka: Created.
*/

///////////////////////////////////////////////////////////////////////////////
///                                INCLUDE FILES
///////////////////////////////////////////////////////////////////////////////

/*!
 * ----------------------- SYSTEM AND PLATFORM FILES --------------------------
 */

/*!
 * ------------------------------ PROGRAM FILES -------------------------------
 */

///////////////////////////////////////////////////////////////////////////////
///               PUBLIC DECLARATIONS Defined here, used elsewhere
///////////////////////////////////////////////////////////////////////////////
/*!
* ---------------------------- MACRO DEFINATIONS -----------------------------
*/
/** @addtogroup CONF_FILE
* @{ */
/*!<!Number of MB to be processed in one go*/
#define TC0     0
/*!<!DMA TC0*/
#define TC1     1
/*!<!DMA TC1  */

/* -------------------------------------------------------------------------*/
/* To reduce the code sixe we are not checking the buffer exhaust ness when */
/* we read each bit from the buffer so when "NOEOFCHECK" is not defined we  */
/* we are checking the buffer exhaust ness if defined we wont check         */
/* -------------------------------------------------------------------------*/
#define NOEOFCHECK
/*
 * Max frame width supported on DM510
 * Actual Requirement is to have D1 PAL but for WVGA(8648480) has same
 * Numeber of MB to process. It is required to support WVGA and rotated WVGA
 */
#define MAX_FRAME_WIDTH    1920//864

#define MAX_FRAME_RESOLUTION 1920 * 1088

/*
 * Max Number of MB in PAL D1 Case
 * (720*576) / (16 * 16)
 */
#define MAX_NUM_MB         8160//1620
/*
 * Max and min resolutions that Xena will support
 * If we include WVGA and rotated WVGA
 */
#define PAL_D1_WIDTH   720
#define PAL_D1_HEIGHT  576

#define MIN_PIX_WIDTH  64
#define MIN_PIX_HEIGHT 16

/*
 * Padd width and pad height
 */
#define PAD_WIDTH     32
#define PAD_HEIGHT    32

/* Smallest picture size supported by VC1 Decoder on DM510 is 64x64 */
#define MIN_FRAME_WIDTH    64
#define MIN_FRAME_HEIGHT   64

#define LPF_HEIGHT   32
//#define MAX_FRAME_SIZE     761600 /* This size is Approximated to D1 Resolu
//                                   Image */
/*
 * Max supported frame size for dm510 is 720x576
 * after padding and 32 byte alignment size is 800x640
 * So totally for luma - 800 * 600  - 480000
 * For croma 800 * (576 / 2 + 64 lines) - 281600.
 * Totally -                            761600
 */
#define DM510_FRAME_SIZE 179712
/*
 * Minimum input buffer size required for decoder
 * This number is set appriximatly there is no restiction to vary this number
 */
#define  BITSTREAM_BUFFER_SIZE_EXT      (1024 * 1024)

#define     LOCAL_DMA_PARAM_SIZE  0x800


/* ECD MB Data to VC1 standard */
#define ECD_MB_DATA_SIZE  64
/* Max num of memtabs required for VC1 decoder */
#define MAX_MEM_TABS    23

//#define NUM_OF_OUT_BUFS         3
#define NUM_OF_OUT_BUFS         2


#define MIN_EDMA_LGL_CHANNELS 20



/*
 * DTCM OFFSETs for storing the hanlde, static commands, tables etc...
 */
#define DTCM_SHARE_BUF_SIZE           0x10
#define CALC_STATIC_COMM_BUF_SIZE     0x340
#define LPF_STATIC_COMM_BUF_SIZE      0x1100
#define LPF_STATIC_COMM_SIZE          0x660
#define DTCM_HANDLE_AREA_SIZE         0x2000
#define DTCM_LUTY_BUF_SIZE            0x100
#define DTCM_LUTUV_BUF_SIZE           0x100

#endif
