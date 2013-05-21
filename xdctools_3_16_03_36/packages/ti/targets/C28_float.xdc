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
 *  ======== C28_float.xdc ========
 *
 */

/*!
 *  ======== C28_float ========
 *  TI C28 with float point support (fpu32) target
 */
metaonly module C28_float inherits ti.targets.ITarget {
    override readonly config string name                = "C28_float";        
    override readonly config string suffix              = "28FP";
    override readonly config string isa                 = "28FP"; 
    override readonly config xdc.bld.ITarget.Model model = {
        dataModel: "large",
        endian: "little"
    };
    
    override readonly config string rts                 = "ti.targets.rts2800";

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["28L"];

    final override readonly config Bool alignDirectiveSupported = false;

    /*!
     *  ======== ar ========
     *  Define archiver executable
     *
     *  Options:
     *  @p(dlist)
     *      -`-r`
     *          replace file
     *      -`-q`
     *          quiet mode
     */
    override readonly config ITarget.Command ar = {
        cmd: "ar2000",
        opts: "rq"
    };


    /*!
     *  ======== cc ========
     *  Define compiler executable
     *
     *  Options:
     *  @p(dlist)
     *      -`-c`
     *          no linking
     *      -`-v28`
     *          compile for c28x.
     *      -`-ml`
     *          use large memory model
     *      -`-DLARGE_MODEL=1`
     *          required to use va_arg in large model
     *      -`--float_support=fpu32`
     *          Enable FPU
     */
    override readonly config ITarget.Command cc = {
        cmd: "cl2000 -c",
        opts: "-v28 -DLARGE_MODEL=1 -ml --float_support=fpu32"
    };

    /*!
     *  ======== vers ========
     *  Define the vers command
     */
    override readonly config ITarget.Command vers = {
        cmd: "cl2000",
        opts: "-version"
    };


    /*!
     *  ======== asm ========
     *  Define assembler executable
     *
     *  Options:
     *  @p(dlist)
     *      -`-c`
     *          no linking
     *      -`-v28`
     *          compile for c28x.
     *      -`-ml`
     *          use large memory model
     *      -`-DLARGE_MODEL=1`
     *          because compiler and BIOS are broken; asembler
     *          defines __LARGE_MODEL but BIOS uses LARGE_MODEL
     *      -`--float_support=fpu32`
     *          Enable FPU
     */
    override readonly config ITarget.Command asm = {
        cmd: "cl2000 -c",
        opts: "-v28 -ml -DLARGE_MODEL=1 --float_support=fpu32"
    };


    /*!
     *  ======== lnk ========
     *  Define linker executable
     */
    override readonly config ITarget.Command lnk = {
        cmd: "lnk2000",
        opts: ""
    };
    

    /*!
     *  ======== asmOpts ========
     *  User configurable assembler options.
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-qq`
     *          super quiet mode
     */
    override config ITarget.Options asmOpts = {
        prefix: "-qq",
        suffix: ""
    };

    /*!
     *  ======== ccOpts ========
     *  Compiler options
     *  @p(dlist)
     *      -`-qq`
     *          super quiet mode
     *      -`-pdsw225`
     *          generate a warning for implicitly declared functions; i.e.,
     *          functions without prototypes
     *      -`-Dfar= `
     *          ignore keyword far; this allows one to write code that can
     *          be compiled in large model and small model without #ifdef's
     */
    override config ITarget.Options ccOpts = {
        prefix: "-qq -pdsw225 -Dfar= ",
        suffix: ""
    };


    /*!
     *  ======== lnkOpts ========
     *  Linker options
     *
     *  Options:
     *  @p(dlist)
     *      -`-q`
     *          Quite run
     *      -`-u`
     *          Place unresolved external symbol into symbol table
     *      -`-c`
     *          ROM autoinitialization model
     *      -`-m`
     *          create a map file
     *      -`-l`
     *          archive library file as linker input
     */
    override config ITarget.Options lnkOpts = {
        prefix: "-w -q -u _c_int00",
        suffix: "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts2800_fpu32.lib"
    };
        
    /*!
     *  ======== includeOpts ========
     *  Default include search path
     */
    override config string includeOpts = "-I$(rootDir)/include";

    final override readonly config string sectMap[string] =
        ti.targets.C28.sectMap;

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 2, align: 2 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 2, align: 2 },
        t_Float         : { size: 2, align: 2 },
        t_Fxn           : { size: 2, align: 2 }, /* far */
        t_Int           : { size: 1, align: 1 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 1, align: 1 },
        t_Int32         : { size: 2, align: 2 },
        t_Int64         : { size: 4, align: 2 },
        t_Long          : { size: 2, align: 2 },
        t_LDouble       : { size: 2, align: 2 },
        t_LLong         : { size: 4, align: 2 },
        t_Ptr           : { size: 2, align: 2 },
        t_Short         : { size: 1, align: 1 },
        t_Size          : { size: 2, align: 2 },
    };

    override readonly config Int bitsPerChar = 16;
}
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:14; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

