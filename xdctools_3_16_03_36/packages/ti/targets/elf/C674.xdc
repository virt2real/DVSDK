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
 *  ======== C674.xdc ========
 *
 */

/*!
 *  ======== C674 ========
 *  TI C674 little endian target -- for ELF
 */
metaonly module C674 inherits ITarget {
    override readonly config string name                 = "C674";
    override readonly config string suffix               = "e674";
    override readonly config string isa                  = "674";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little",
        shortEnums: true
    };
    override readonly config xdc.bld.ITarget.Module base = ti.targets.C62;

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["e64P", "e64", "e62"];

    override readonly config string rts = "ti.targets.rts6000";
    override config string platform     = "ti.platforms.evmDA830";
    
    override readonly config ti.targets.ITarget.Command ar = {
        cmd: "ar6x",
        opts: "rq"
    };

    override readonly config ti.targets.ITarget.Command cc = {
        cmd: "cl6x -c",
        opts: "-mv6740 --abi=elfabi"
    };

    override readonly config ti.targets.ITarget.Command vers = {
        cmd: "cl6x",
        opts: "-version"
    };

    override readonly config ti.targets.ITarget.Command asm = {
        cmd: "cl6x -c",
        opts: "-mv6740 --abi=elfabi"
    };

    override readonly config ti.targets.ITarget.Command lnk = {
        cmd: "lnk6x",
        opts: "--abi=elfabi"
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
    override config ti.targets.ITarget.Options asmOpts = {
        prefix: "-qq",
        suffix: ""
    };

    /*!
     *  ======== ccOpts ========
     *  User configurable compiler options.
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-qq`
     *          super quiet mode
     *      -`-pdsw225`
     *          generate a warning for implicitly declared functions; i.e.,
     *          functions without prototypes
     */
    override config ti.targets.ITarget.Options ccOpts = {
        prefix: "-qq -pdsw225",
        suffix: ""
    };

    /*!
     *  ======== ccConfigOpts ========
     *  User configurable compiler options for the generated config C file.
     *
     *  -mo places all functions into subsections
     *  --no_compress helps with compile time with no real difference in
     *  code size since the generated config.c is mostly data and small
     *  function stubs.
     */
    override config ti.targets.ITarget.Options ccConfigOpts = {
        prefix: "$(ccOpts.prefix) -mo --no_compress",
        suffix: "$(ccOpts.suffix)"
    };

    /*!
     *  ======== lnkOpts ========
     *  User configurable linker options.
     *
     *  Defaults:
     *  @p(dlist)
     *      -`-w`
     *          Display linker warnings
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
    override config ti.targets.ITarget.Options lnkOpts = {
        prefix: "-w -q -u _c_int00",
        suffix: "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6740_elf.lib"
    };
        
    override config string includeOpts = "-I$(rootDir)/include";

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = 
        ti.targets.elf.C64P.stdTypes;
    
    override readonly config Int bitsPerChar = 
        ti.targets.C62.bitsPerChar;
}
/*
 *  @(#) ti.targets.elf; 1, 0, 0,152; 2-24-2010 16:24:19; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

