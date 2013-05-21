/** ==========================================================================
 *  @file   crc.c
 *
 *  @path   $(PROJDIR)\Src
 *
 *  @desc  This File contains functions for calculating CRCfor given buffer,
 *          
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/


/* -------------------- compilation control switches -----------------------*/


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/

/* -------------------- system and platform files ------------------------- */

/* ------------------------- program files -------------------------------- */
#include "crc.h"

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


/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/

/* ---------------------- data declarations ------------------------------- */

/* --------------------- function prototypes ------------------------------ */


/* ---------------------------- macros ------------------------------------ */
/*
 * Derive parameters from the standard-specific parameters in crc.h.
 */
#define WIDTH    (8 * sizeof(crc))
#define TOPBIT   (1 << (WIDTH - 1))

#if (REFLECT_DATA == TRUE)
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			((unsigned char) reflect((X), 8))
#else
#undef  REFLECT_DATA
#define REFLECT_DATA(X)			(X)
#endif

#if (REFLECT_REMAINDER == TRUE)
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	((crc) reflect((X), WIDTH))
#else
#undef  REFLECT_REMAINDER
#define REFLECT_REMAINDER(X)	(X)
#endif


/* ===========================================================================
 *  @func   reflect()
 *
 *  @desc   Reorder the bits of a binary sequence, by reflecting
 *          them about the middle position
 *.
 *  @param  data.: Input data to be reflected
 *
 *  @param  nBits: Number of bits
 *
 *  @return The reflection of the original data.
 *
 *  @Notes: No checking is done that nBits <= 32.
 *
 * ===========================================================================
 */
static unsigned long
reflect(unsigned long data, unsigned char nBits)
{
	unsigned long  reflection = 0x00000000;
	unsigned char  bit;

	/*
	 * Reflect the data about the center bit.
	 */
	for (bit = 0; bit < nBits; ++bit)
	{
		/*
		 * If the LSB bit is set, set the reflection of it.
		 */
		if (data & 0x01)
		{
			reflection |= (1 << ((nBits - 1) - bit));
		}

		data = (data >> 1);
	}

	return (reflection);

}	/* reflect() */


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
crc
crcSlow(unsigned char const message[], int nBytes)
{
    crc            remainder = INITIAL_REMAINDER;
	int            byte;
	unsigned char  bit;


    /*
     * Perform modulo-2 division, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        /*
         * Bring the next byte into the remainder.
         */
        remainder ^= (REFLECT_DATA(message[byte]) << (WIDTH - 8));

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */
            if ((unsigned int)((unsigned int)remainder & (unsigned int)TOPBIT))
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }
    }

    /*
     * The final remainder is the CRC result.
     */
    return (REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE);

}   /* crcSlow() */

/*  Array to store the remainder valsue for 8-bit data which will be used 
 * for fast CRC calculation
 */
crc  crcTable[256];

/* ===========================================================================
 *  @func   crcInit()
 *
 *  @desc   Populate the partial CRC lookup table.
 *.
 *  @param  None
 *
 *  @return None
 *
 *  @Notes: This function must be rerun any time the CRC standard
 *			is changed.  If desired, it can be run "offline" and
 *			the table results stored in an embedded system's ROM.
 *
 * ===========================================================================
 */
void
crcInit(void)
{
    crc			   remainder;
	int			   dividend;
	unsigned char  bit;


    /*
     * Compute the remainder of each possible dividend.
     */
    for (dividend = 0; dividend < 256; ++dividend)
    {
        /*
         * Start with the dividend followed by zeros.
         */
        remainder = dividend << (WIDTH - 8);

        /*
         * Perform modulo-2 division, a bit at a time.
         */
        for (bit = 8; bit > 0; --bit)
        {
            /*
             * Try to divide the current data bit.
             */			
            if ((unsigned int)((unsigned int)remainder & (unsigned int)TOPBIT))
            {
                remainder = (remainder << 1) ^ POLYNOMIAL;
            }
            else
            {
                remainder = (remainder << 1);
            }
        }

        /*
         * Store the result into the table.
         */
        crcTable[dividend] = remainder;
    }

}   /* crcInit() */



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
crc
crcFast(unsigned char const message[], int nBytes)
{
    crc	           remainder = INITIAL_REMAINDER;
    unsigned char  data;
	int            byte;


    /*
     * Divide the message by the polynomial, a byte at a time.
     */
    for (byte = 0; byte < nBytes; ++byte)
    {
        data = REFLECT_DATA(message[byte]) ^ (remainder >> (WIDTH - 8));
  		remainder = crcTable[data] ^ (remainder << 8);
    }

    /*
     * The final remainder is the CRC.
     */
    return (REFLECT_REMAINDER(remainder) ^ FINAL_XOR_VALUE);

}   /* crcFast() */



/*!
 *! Revision History
 *! ================
 *! 08-Aug-2007   Kumar    : Created
 *!
 */
