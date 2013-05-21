* ========================================================================= *
*                                                                           *
*   TEXAS INSTRUMENTS, INC.                                                 *
*                                                                           *
*   NAME                                                                    *
*       c55xasm.i -- compatibility bridge for pre-3.10 tools                *
*                                                                           *
*   USAGE                                                                   *
*       Just .include at top of your source file.  Alternately, use         *
*       the compiler flag -ahi or -ahc to force inclusion in the            *
*       source-file.                                                        *
*                                                                           *
*   DESCRIPTION                                                             *
*       This file provides a set of directives that are intended to be used *
*       to mark the boundaries of assembly-language functions.  The         *
*       point of the new directives is to allow the tools to provide more   *
*       precise information to the profiler as to which regions of code     *
*       were executed, as well as to give meaningful names to assembly      *
*       functions when debugging.                                           *
*                                                                           *
*   NOTES                                                                   *
*       This file is actually just a compatibility shim, intended to        *
*       provide forward compatibility between tool versions < 3.10          *
*       and tool versions >= 3.10.  The purpose of this file it purely      *
*       compatibility.  Tool versions >= 3.10 are required to gain the      *
*       features provided by these directives.                              *
* ------------------------------------------------------------------------- *
*             Copyright (c) 2004 Texas Instruments, Incorporated.           *
*                            All Rights Reserved.                           *
* ========================================================================= *

* ========================================================================= *
* Create "asmver" with current version of assembler. Value is 0 if assembler
* version predates the predefined symbol.
* ========================================================================= *
           .if $isdefed("__TI_ASSEMBLER_VERSION__")
           .asg    __TI_ASSEMBLER_VERSION__, asmver
           .else
           .asg    0, asmver
           .endif

* ========================================================================= *
* If the assembler version predates the new mnemonics and/or directives
* ========================================================================= *
           .if asmver < 310
           .asg ";", .asmfunc
           .asg ";", .endasmfunc
           .endif

