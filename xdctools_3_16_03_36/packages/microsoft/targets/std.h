/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
/*
 *  ======== microsoft/targets/std.h ========
 *
 */

#ifndef microsoft_targets_STD_
#define microsoft_targets_STD_

/* include target-specific "portable" macros */
#if defined(xdc_target_name__) & !defined(xdc_target_macros_include__)
#include xdc__local_include(xdc_target_name__)
#endif

#define inline __inline

/*
 * xdc__LONGLONG__ indicates if compiler supports 'long long' type
 * xdc__BITS<n> __ indicates if compiler supports 'uint<n>_t' type
 */
#undef xdc__LONGLONG__
#define xdc__BITS8__
#define xdc__BITS16__
#define xdc__BITS32__
#define xdc__BITS64__
#define xdc__INT64__

/*
 *  ======== [U]Int<n> ========
 */
typedef signed char     xdc_Int8;
typedef unsigned char   xdc_UInt8;
typedef short           xdc_Int16;
typedef unsigned short  xdc_UInt16;
typedef long            xdc_Int32;
typedef unsigned long   xdc_UInt32;

typedef __int64          xdc_Int64;
typedef unsigned __int64 xdc_UInt64;
typedef __int64          xdc_LLong;
typedef unsigned __int64 xdc_ULLong;

/*
 *  ======== Bits<n> ========
 */
typedef unsigned char   xdc_Bits8;
typedef unsigned short  xdc_Bits16;
typedef unsigned int    xdc_Bits32;

typedef unsigned __int64 xdc_Bits64;

/*
 *  ======== Arg ========
 */
typedef long            xdc_IArg;
typedef unsigned long   xdc_UArg;

#define xdc__ARG__
typedef xdc_IArg xdc_Arg;       /* deprecated, but compatible with BIOS 5.x */

#endif /* microsoft_targets_STD_ */
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

