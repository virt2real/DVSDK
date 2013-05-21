/*****************************************************\
 *  Copyright 2003, Texas Instruments Incorporated.  *
 *  All rights reserved.                             *
 *  Restricted rights to use, duplicate or disclose  *
 *  this   code   are  granted   through  contract.  *
\*****************************************************/

/* Standard Types File: [last revised: 2004-01-14] */

#ifndef _TISTDTYPES_H_
#define _TISTDTYPES_H_

/*
    The purpose of this header file is to consolidate all the primitive "C"
    data types into one file. This file is expected to be included in the
    basic types file exported by other software components, for example CSL.
 */

#ifndef _TI_STD_TYPES
#define _TI_STD_TYPES
#include <stdarg.h>
#include <stddef.h>

#include "imcop_types.h"

typedef int		Bool;

#ifndef TRUE

#define TRUE		((Bool) 1)
#define FALSE		((Bool) 0)

#endif

#ifndef NULL
#define NULL 0
#endif

typedef int             Int;
typedef unsigned int    Uns;    /* deprecated type */
typedef char            Char;
typedef char *          String;
typedef void            Void;
typedef void *          Ptr;

/* unsigned quantities */
typedef unsigned int   	Uint32;
typedef unsigned short 	Uint16;
typedef unsigned char   Uint8;
typedef unsigned short  UShort;
typedef unsigned long   ULong;

/* signed quantities */
typedef int             Int32;
typedef short           Int16;
typedef char            Int8;
typedef short           Short;
typedef long            Long;

typedef float           Float16;
typedef float           Float32;

#endif /* _TI_STD_TYPES */


#endif /* _TISTDTYPES_H_ */

/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 4          Aug 10:09:41 9         2272             xkeshavm      */
/*                                                                  */
/* To upload API CSL 0.51 Release                                   */
/********************************************************************/
/* Rev.No.   Date/Time               ECN No.          Modifier      */
/* -------   ---------               -------          --------      */

/* 1         13 Nov 2005 12:48:09    401              x0029935      */
/*                                                                  */
/* Modified from davicni CSL files to Dm350                         */
/* First CSL files build up fro Dm350                               */
/********************************************************************/



/* Standard Constants */

#undef NULL
#define NULL 0

#undef FALSE
#define FALSE 0

#undef TRUE
#define TRUE 1

/* Declaration Qualifiers */

#ifndef __FAR__
#define __FAR__
#endif

/* Code-Section Directive */

#ifndef xdc__CODESECT
#define xdc__CODESECT(fn, sn)
#endif


