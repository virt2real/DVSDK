/*
 *  Copyright 2010 by Texas Instruments Incorporated.
 *
 */

/*
 *  ======== R4t_big_endian.h ========
 *  DO NOT MODIFY: This header is generated from stddef.xdt
 *
 *  This header contains target-specific definitions of target-independent
 *  macros required by the ITarget interface.  These definitions allow C/C++
 *  sources to portably compile for multiple targets (using #ifdef ...).
 */
#ifndef xdc_target_macros_include__
#define xdc_target_macros_include__    1

/*
 *  ======== ti_targets_arm_R4t_big_endian ========
 *  This macro identifies the specific target being used.  This macro should
 *  probably be avoided in portable sources.
 */
#define ti_targets_arm_R4t_big_endian  1

/*
 *  ======== xdc_target__isaCompatible_* macros ========
 *  The following definitions enable clients to conditionally compile for any
 *  compatible subset of the actual target ISA.
 */
#define xdc_target__isaCompatible_470  1
#define xdc_target__isaCompatible_v7R  1

/*
 *  ======== xdc_target__isa_v7R ========
 *  This macro identifies the specific target ISA for which we are being
 *  compiled.
 */
#define xdc_target__isa_v7R  1

/*
 *  ======== xdc_target__{big|little}Endian ========
 *  The following macro enables clients to portably compile for big or little
 *  endian targets.
 */
#define xdc_target__bigEndian   1

/*
 *  ======== xdc_target__{...}Code ========
 *  The following macro enables clients to portably compile for target specific
 *  code models; e.g., near, far, ...
 */
#define xdc_target__thumb2Code  1

/*
 *  ======== xdc_target__os_undefined ========
 *  The following macro enables clients to portably compile for target specific
 *  OS; e.g., Linux, Solaris, Windows, undefined.
 */
#define xdc_target__os_undefined    1

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
#define  xdc_target__sizeof_LLong 8
#define  xdc_target__sizeof_Ptr 4
#define  xdc_target__sizeof_Short 2

/*
 *  ======== xdc_target__alignof_ ========
 *  The following macros enable clients to portably determine type alignment
 *  within #ifdef blocks; even if provided by the compiler, alignof() can't
 *  be used in pre-processor statements.
 */
#define  xdc_target__alignof_IArg 4
#define  xdc_target__alignof_Char 1
#define  xdc_target__alignof_Double 4
#define  xdc_target__alignof_Float 4
#define  xdc_target__alignof_Fxn 4
#define  xdc_target__alignof_Int 4
#define  xdc_target__alignof_Int8 1
#define  xdc_target__alignof_Int16 2
#define  xdc_target__alignof_Int32 4
#define  xdc_target__alignof_Int64 4
#define  xdc_target__alignof_Long 4
#define  xdc_target__alignof_LDouble 4
#define  xdc_target__alignof_LLong 4
#define  xdc_target__alignof_Ptr 4
#define  xdc_target__alignof_Short 2

/*
 *  ======== xdc_target__bitsPerChar ========
 *  The number of bits in a char.  This macro allow one to determine the
 *  precise number of bits in any of the standard types (whose sizes are
 *  expressed as a number of chars).
 */
#define  xdc_target__bitsPerChar 8

#endif  /* end multi-include guard */
/*
 *  @(#) ti.targets.arm; 2, 0, 1, 0,202; 2-24-2010 16:24:12; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

