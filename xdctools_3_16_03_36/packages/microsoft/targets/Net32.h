/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== Net32.h ========
 *  DO NOT MODIFY: This header is generated from stddef.xdt
 *
 *  This header contains target-specific definitions of target-independent
 *  macros required by the ITarget interface.  These definitions allow C/C++
 *  sources to portably compile for multiple targets (using #ifdef ...).
 */
#ifndef xdc_target_macros_include__
#define xdc_target_macros_include__    1

/*
 *  ======== microsoft_targets_Net32 ========
 *  This macro identifies the specific target being used.  This macro should
 *  probably be avoided in portable sources.
 */
#define microsoft_targets_Net32  1

/*
 *  ======== xdc_target__isaCompatible_* macros ========
 *  The following definitions enable clients to conditionally compile for any
 *  compatible subset of the actual target ISA.
 */
#define xdc_target__isaCompatible_x86  1

/*
 *  ======== xdc_target__isa_x86 ========
 *  This macro identifies the specific target ISA for which we are being
 *  compiled.
 */
#define xdc_target__isa_x86  1

/*
 *  ======== xdc_target__{big|little}Endian ========
 *  The following macro enables clients to portably compile for big or little
 *  endian targets.
 */
#define xdc_target__littleEndian   1

/*
 *  ======== xdc_target__os_Windows ========
 *  The following macro enables clients to portably compile for target specific
 *  OS; e.g., Linux, Solaris, Windows, undefined.
 */
#define xdc_target__os_Windows    1

/*
 *  ======== xdc_target__sizeof_ ========
 *  The following macros enable clients to portably determine type sizes
 *  within #ifdef blocks; sizeof() can't be used and the definitions in
 *  stdint.h are not available to C++ clients (unless the special macro
 *  __STDC_LIMIT_MACROS is defined).
 */
#define  xdc_target__sizeof_IArg 4
#define  xdc_target__sizeof_Char 1
#define  xdc_target__sizeof_Double 8
#define  xdc_target__sizeof_Float 4
#define  xdc_target__sizeof_Fxn 4
#define  xdc_target__sizeof_Int 4
#define  xdc_target__sizeof_Int8 1
#define  xdc_target__sizeof_Int16 2
#define  xdc_target__sizeof_Int32 4
#define  xdc_target__sizeof_Int64 8
#define  xdc_target__sizeof_Long 4
#define  xdc_target__sizeof_LDouble 8
#define  xdc_target__sizeof_Ptr 4
#define  xdc_target__sizeof_Short 2

/*
 *  ======== xdc_target__alignof_ ========
 *  The following macros enable clients to portably determine type alignment
 *  within #ifdef blocks; even if provided by the compiler, alignof() can't
 *  be used in pre-processor statements.
 */
#define  xdc_target__alignof_IArg 1
#define  xdc_target__alignof_Char 1
#define  xdc_target__alignof_Double 1
#define  xdc_target__alignof_Float 1
#define  xdc_target__alignof_Fxn 1
#define  xdc_target__alignof_Int 1
#define  xdc_target__alignof_Int8 1
#define  xdc_target__alignof_Int16 1
#define  xdc_target__alignof_Int32 1
#define  xdc_target__alignof_Int64 1
#define  xdc_target__alignof_Long 1
#define  xdc_target__alignof_LDouble 1
#define  xdc_target__alignof_Ptr 1
#define  xdc_target__alignof_Short 1

/*
 *  ======== xdc_target__bitsPerChar ========
 *  The number of bits in a char.  This macro allow one to determine the
 *  precise number of bits in any of the standard types (whose sizes are
 *  expressed as a number of chars).
 */
#define  xdc_target__bitsPerChar 8

#endif  /* end multi-include guard */
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

