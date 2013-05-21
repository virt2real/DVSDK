/** ===========================================================================
* @file datatypedefs.h
*
* @path $\\(PROJDIR)\\..\\inc\\
*
* @brief This file defines the data type definations that are used in the
*        project.
*
* Copyright (c) Texas Instruments Inc 2005, 2006, 2007
*
* Use of this software is controlled by the terms and conditions found
* in the license agreement under which this software has been supplied
*
* ===========================================================================*/

#ifndef __DATATYPEDEFS__
#define __DATATYPEDEFS__

/* ---------------------------- DATA DECLARATIONS -------------------------- */

typedef char                 S8;   /* typdef char                 S8         */
typedef short                S16;  /* typedef short               S16        */
typedef int                  S32;  /* typedef int                 S32        */
typedef long long            S64;  /* typedef long long           S64        */

typedef unsigned char        U8;   /* typedef unsigned char       U8         */
typedef unsigned short       U16;  /* typedef unsigned short      U16        */
typedef unsigned int         U32;  /* typedef unsigned int        U32        */
typedef unsigned long long   U64;  /* typedef unsigned long long  U64        */

typedef char*                pS8;  /* typedef char*               pS8        */
typedef short*               pS16; /* typedef short*              pS16       */
typedef int*                 pS32; /* typedef int*                pS32       */
typedef long long*           pS64; /* typedef long*               pS64       */

typedef const int *          pcU32;/* typedef const int *         pcU32      */
typedef unsigned char*       pU8;  /* typedef unsigned char*      pU8        */
typedef unsigned short*      pU16; /* typedef unsigned short*     pU16       */
typedef unsigned int*        pU32; /* typedef unsigned int*       pU32       */
typedef unsigned long long*  pU64; /* typedef unsigned long*      pU64       */
typedef void *               pV;   /* typedef void *               pV		 */
typedef void                 V;    /* typedef void                 V		 */
typedef unsigned int Se_fn_t; /* fixed-pattern bit string using n bits       */
typedef          int Se_in_t; /* signed int using n bits		   	         */
typedef unsigned int Se_un_t; /* unsigned int using n bits			         */
typedef          int Se_sev_t;/* int exp-golomb coded syntax element         */
typedef unsigned int Se_uev_t;/* unsigned int exp-golomb coded syntax element*/
typedef unsigned int Se_tev_t;/* truncated exp-golomb coded syntax element   */
typedef unsigned int Se_uv_t; /* length dependent on other syntax			 */

typedef int          IDX;     /* for Index									 */
typedef char         C_BOOL;

#endif /* __DATA_TYPEDEFS__ */


/*
*  <b> Revision History </b>
*  @n  ================  @n
*    @Version  0.1 : 27/01/2006 : Anirban Basu    : Created
*    @version  0.2 : 08/06/2007 : Naresh Inukurthi: Made Codingguideline chanes
*/

