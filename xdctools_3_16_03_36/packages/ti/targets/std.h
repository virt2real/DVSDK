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
 *  ======== ti/targets/std.h ========
 *  Standard types for supported TI compilers
 *
 */

#ifndef ti_targets_STD_
#define ti_targets_STD_

/* include target-specific "portable" macros */
#if defined(xdc_target_name__) & !defined(xdc_target_macros_include__)
#include xdc__local_include(xdc_target_name__)
#endif

#include <stdint.h>     /* C99 standard integer types */

#if !defined(xdc__strict)
    #if defined(_TMS320C28X) || defined(__TMS320C55X__) \
        || defined(__TMS320C55X_PLUS_BYTE__)
        #define xdc__ARG__
        typedef void *xdc_Arg;  /* deprecated, but compatible with BIOS 5.x */
    #elif defined(_TMS320C5XX) || defined(_TMS320C6X)
        #define xdc__ARG__
        typedef int xdc_Arg;    /* deprecated, but compatible with BIOS 5.x */
    #endif
#endif    

/*
 * xdc__LONGLONG__ indicates if compiler supports 'long long' type
 * xdc__BITS<n> __ indicates if compiler supports 'uint<n>_t' type
 */
#if defined(_TMS320C28X)                        /* 28x */
    #define xdc__LONGLONG__
    #undef xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
    #define xdc__BITS64__
    #define xdc__INT64__

#elif defined(_TMS320C5XX)                      /* 54x */
    #undef xdc__LONGLONG__
    #undef xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

#elif defined(__TMS320C55X__)                   /* 55x */
    #define xdc__LONGLONG__
    #undef xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
    #define xdc__INT40__

#elif defined(__TMS320C55X_PLUS_BYTE__)         /* 55x+ byte mode */
    #undef xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__

#elif defined(_TMS320C6X)                       /* all C6x */
    #define xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
    #define xdc__BITS64__
    #if !defined(__TI_ELFABI__)
        #define xdc__INT40__
    #endif
    #define xdc__INT64__

    #define __FAR__ far

#elif defined(__TMS470__)                       /* ARM */
    #define xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
    #define xdc__BITS64__
    #define xdc__INT64__

#elif defined(__MSP430__)                       /* MSP430 */
    #undef xdc__LONGLONG__
    #define xdc__BITS8__
    #define xdc__BITS16__
    #define xdc__BITS32__
#else
    #error <ti/targets/std.h> is not supported for this target
#endif

/*
 *  ======== [U]Int<n> ========
 */
typedef int_least8_t    xdc_Int8;
typedef uint_least8_t   xdc_UInt8;
typedef int_least16_t   xdc_Int16;
typedef uint_least16_t  xdc_UInt16;
typedef int_least32_t   xdc_Int32;
typedef uint_least32_t  xdc_UInt32;

#ifdef xdc__INT64__
    typedef int_least64_t   xdc_Int64;
    typedef int_least64_t   xdc_UInt64;
#endif

#ifdef xdc__INT40__
    typedef int_least40_t   xdc_Int40;
    typedef uint_least40_t  xdc_UInt40;

  /*  the following unqualified names are here because 40-bit types are not
   *  supported by xdc/std.h
   */
  #ifndef xdc__nolocalnames
    typedef xdc_Int40       Int40;
    typedef xdc_UInt40      UInt40;
  #endif
#endif

/*
 *  ======== Bits<n> ========
 */
#ifdef xdc__BITS8__
    typedef uint8_t     xdc_Bits8;
#endif
#ifdef xdc__BITS16__
    typedef uint16_t    xdc_Bits16;
#endif
#ifdef xdc__BITS32__
    typedef uint32_t    xdc_Bits32;
#endif
#ifdef xdc__BITS64__
    typedef uint64_t    xdc_Bits64;
#endif

/*
 *  ======== [UI]Arg ========
 */
typedef intptr_t        xdc_IArg;
typedef uintptr_t       xdc_UArg;

/*
 *  ======== restrict ========
 */
#define xdc__RESTRICT__


/*
 *  ======== ti_targets_mkPragma ========
 */
#define ti_targets_mkPragma(x) _Pragma(#x)

/*
 *  ======== xdc__META ========
 */
#define xdc__META(n,s) \
    ti_targets_mkPragma(DATA_SECTION(n, "xdc.meta")) \
    const char (n)[] = {s}

/*
 *  ======== __ti__ ========
 *  These symbols are used by RTSC tools to indicate presence/absence of
 *  assorted #pragma options in TI compiler.
 */
#define __ti__
#define __ti__align
#define __ti__sect

/* MSP430 LARGE_CODE target has 20-bit pointers, but sizeof operator returns
 * 4, same as for Args, which really are 32 bits long.
 */
#if (xdc_target__sizeof_IArg > xdc_target__sizeof_Ptr) \
    || (xdc_target__sizeof_IArg > xdc_target__sizeof_Fxn) \
    || (defined(__MSP430__) && defined(__LARGE_CODE_MODEL__) \
        && !defined(__LARGE_DATA_MODEL__))

#define xdc__ARGTOPTR
#define xdc__ARGTOFXN
static inline xdc_Ptr xdc_iargToPtr(xdc_IArg a) { return ((xdc_Ptr)(int)a); }
static inline xdc_Ptr xdc_uargToPtr(xdc_UArg a) { return ((xdc_Ptr)(int)a); }
static inline xdc_Fxn xdc_iargToFxn(xdc_IArg a) { return ((xdc_Fxn)(int)a); }
static inline xdc_Fxn xdc_uargToFxn(xdc_UArg a) { return ((xdc_Fxn)(int)a); }

#endif

/* On MSP430 large data model, Ptr and Fxn are 20 bit and the compiler warns about casting from 
 * integer to a smaller pointer. These pragmas suppress the warning.
 */
#if (defined(__MSP430__) && defined(__LARGE_CODE_MODEL__) && \
    defined(__LARGE_DATA_MODEL__))
#pragma diag_suppress 1107
#define xdc__ARGTOPTR
#define xdc__ARGTOFXN
static inline xdc_Ptr xdc_iargToPtr(xdc_IArg a) { return ((xdc_Ptr)a); }
static inline xdc_Ptr xdc_uargToPtr(xdc_UArg a) { return ((xdc_Ptr)a); }
static inline xdc_Fxn xdc_iargToFxn(xdc_IArg a) { return ((xdc_Fxn)a); }
static inline xdc_Fxn xdc_uargToFxn(xdc_UArg a) { return ((xdc_Fxn)a); }
#pragma diag_default 1107

#endif

#endif /* ti_targets_STD_ */
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:16; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

