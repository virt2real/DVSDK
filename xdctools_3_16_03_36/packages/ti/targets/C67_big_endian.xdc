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
 *  ======== C67_big_endian.xdc ========
 *
 */

/*!
 *  ======== C67_big_endian ========
 *  TI C67 big endian target
 */
metaonly module C67_big_endian inherits ti.targets.ITarget {
    override readonly config string name                 = "C67_big_endian";
    override readonly config string suffix               = "67e";
    override readonly config string isa                  = "67";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "big"
    };
    override readonly config xdc.bld.ITarget.Module base = ti.targets.C62;

    override readonly config string rts = "ti.targets.rts6000";
    override config string platform     = "ti.platforms.sim6xxx:TMS320C6713";
    
    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["62e"];

    override readonly config ITarget.Command ar = {
        cmd: "ar6x",
        opts: "rq"
    };

    override readonly config ITarget.Command cc = {
        cmd: "cl6x -c",
        opts: "-me -mv6700"
    };

    override readonly config ITarget.Command vers = {
        cmd: "cl6x",
        opts: "-version"
    };

    override readonly config ITarget.Command asm = {
        cmd: "cl6x -c",
        opts: "-me -mv6700"
    };

    override readonly config ITarget.Command lnk = {
        cmd: "lnk6x",
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
    override config ITarget.Options ccOpts = {
        prefix: "-qq -pdsw225",
        suffix: ""
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
    override config ITarget.Options lnkOpts = {
        prefix: "-q -u _c_int00",
        suffix: "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts6700e.lib"
    };
        
    override config string includeOpts = "-I$(rootDir)/include";

    final override readonly config string sectMap[string] =
        ti.targets.C62.sectMap;

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = C62.stdTypes;
    
    override readonly config Int bitsPerChar = C62.bitsPerChar;
};
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:15; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

