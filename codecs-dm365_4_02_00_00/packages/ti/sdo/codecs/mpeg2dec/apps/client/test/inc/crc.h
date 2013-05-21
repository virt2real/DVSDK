/** ==========================================================================
 *  @file   crc.h
 *
 *  @path   $(PROJDIR)\Inc
 *
 *  @desc   A header file describing the various CRC standards
 *
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/

/* -------------------- compilation control switches ---------------------- */

#ifndef _crc_h
#define _crc_h

/*
 * Select the CRC standard from the list that follows.
 * CRC_CCITT,CRC32 and CRC16
 */
#define CRC32

/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/
/* -------------------- system and platform files ------------------------- */
/* ------------------------- program files -------------------------------- */

/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/
/* ------------------------ data declarations ----------------------------- */
/* ----------------------- function prototypes ---------------------------- */

/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/
/* ----------------------- data declarations ------------------------------ */
/* ---------------------- function prototypes ----------------------------- */
#define FALSE   0
#define TRUE    !FALSE

#if defined(CRC_CCITT)
typedef unsigned short      crc;
#define CRC_NAME            "CRC-CCITT"
#define POLYNOMIAL          0x1021
#define INITIAL_REMAINDER   0xFFFF
#define FINAL_XOR_VALUE     0x0000
#define REFLECT_DATA        FALSE
#define REFLECT_REMAINDER   FALSE
#define CHECK_VALUE         0x29B1

#elif defined(CRC16)
typedef unsigned short      crc;
#define CRC_NAME            "CRC-16"
#define POLYNOMIAL          0x8005
#define INITIAL_REMAINDER   0x0000
#define FINAL_XOR_VALUE     0x0000
#define REFLECT_DATA        TRUE
#define REFLECT_REMAINDER   TRUE
#define CHECK_VALUE         0xBB3D

#elif defined(CRC32)
typedef unsigned long       crc;
#define CRC_NAME            "CRC-32"
#define POLYNOMIAL          0x04C11DB7
#define INITIAL_REMAINDER   0xFFFFFFFF
#define FINAL_XOR_VALUE     0xFFFFFFFF
#define REFLECT_DATA        TRUE
#define REFLECT_REMAINDER   TRUE
#define CHECK_VALUE         0xCBF43926

#else
#error "One of CRC_CCITT, CRC16, or CRC32 must be #define'd."
#endif

/* ===========================================================================
 *  @func   crcInit(void)
 *
 *  @desc   Populate the partial CRC lookup table.
 *
 *  @param  None
 *
 *  @return None
 * ===========================================================================
 */
void  crcInit(void);

/* ===========================================================================
 *  @func   crcSlow()
 *
 *  @desc  Compute the CRC of a given message
 *.
 *  @param  message.: Input buffer for which CRC to be caclculated
 *
 *  @param  nBytes: Number of Bytes
 *
 *  @return The CRC of the message.
 *
 *  @Notes: None.
 *
 * ===========================================================================
 */
crc   crcSlow(unsigned char const message[], int nBytes);

/* ===========================================================================
 *  @func   crcFast()
 *
 *  @desc   Compute the CRC of a given message
 *.
 *  @param  message.: Input buffer for which CRC to be caclculated
 *
 *  @param  nBytes: Number of Bytes
 *
 *  @return The CRC of the message.
 *
 *  @Notes: None.
 *
 * ===========================================================================
 */
crc   crcFast(unsigned char const message[], int nBytes);

/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/
/* ---------------------- data declarations ------------------------------- */
/* --------------------- function prototypes ------------------------------ */

/* ---------------------------- macros ------------------------------------ */


#endif /* _crc_h */



/*!
 *! Revision History
 *! ================
 *! 27-Aug-2007   Kumar    : Incorporated code review comments.
 *! 01-Jul-2006   Prashanth: Created.
 *!
 */





