/** ===========================================================================
* @file DataTypedefs.h
*
* @path $\\(PROJDIR)\\..\\include\\
*
*@brief This file defines the data type definations that are used in the
*       project.
*
* =============================================================================
*
* Copyright (c) Texas Instruments Inc 2005, 2006
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================
*
*  <b> Revision History </b>
*  @n  ================  @n
*     - \c Created : 27-01-2006 Anirban Basu
*     .
*/

#ifndef __DATA_TYPEDEFS__
#define __DATA_TYPEDEFS__

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
 *
 * ---------------------------- DATA DECLARATIONS -----------------------------
 *
 */
/*!
 *
 */


typedef long            S64; /*!< typedef long            S64   */



typedef char            S8;  /*!< typdef char             S8    */
typedef short           S16; /*!< typedef short           S16   */
typedef int             S32; /*!< typedef int             S32   */



typedef unsigned char   U8;  /*!< typedef unsigned char   U8    */
typedef unsigned short  U16; /*!< typedef unsigned short  U16   */
typedef unsigned int    U32; /*!< typedef unsigned int    U32   */
typedef unsigned long long   U64; /*!< typedef unsigned long   U64   */




typedef char*           pS8;  /*!< typedef char*           pS8  */
typedef short*          pS16; /*!< typedef short*          pS16 */
typedef int*            pS32; /*!< typedef int*            pS32 */
typedef long*           pS64; /*!< typedef long*           pS64 */

typedef unsigned char*  pU8;  /*!< typedef unsigned char*  pU8  */
typedef unsigned short* pU16; /*!< typedef unsigned short* pU16 */
typedef unsigned int*   pU32; /*!< typedef unsigned int*   pU32 */
typedef unsigned long*  pU64; /*!< typedef unsigned long*  pU64 */
typedef void *          pV;
typedef void            V;
typedef unsigned int   Se_fn_t;  //!< fixed-pattern bit string using n bits
typedef          int   Se_in_t;  //!< signed integer using n bits
typedef unsigned int   Se_un_t;  //!< unsigned integer using n bits
typedef          int   Se_sev_t; //!< signed integer exp-golomb coded syntax element
typedef unsigned int   Se_uev_t; //!< unsigned integer exp-golomb coded syntax element
typedef unsigned int   Se_tev_t; //!< truncated exp-golomb coded syntax element
typedef unsigned int   Se_uv_t;  //!< unsigned integer, length dependent on other syntax

typedef int               IDX; // for Index
typedef int            C_BOOL; // for Twofold chice

#ifndef FALSE
#define FALSE   (0)
#endif

#ifndef TRUE
#define TRUE    (1)
#endif

/*!
 * --------------------------- FUNCTION PROTOTYPES ----------------------------
 */

#endif /* __DATA_TYPEDEFS__ */
