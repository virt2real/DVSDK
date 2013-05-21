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
 *  ======== TMS470_big_endian.xdc ========
 *
 */

/*!
 *  ======== TMS470_big_endian.xdc ========
 *  TI TMS470 (Arm) big endian target
 */
metaonly module TMS470_big_endian inherits ti.targets.ITarget {
    override readonly config string name                 ="TMS470_big_endian"; 
    override readonly config string suffix               = "470e";
    override readonly config string isa                  = "470";    
    override readonly config string rts                  = "ti.targets.rts470";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "big"
    };

    override config string platform = "ti.platforms.sim470xx";

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["7e"];

    override readonly config xdc.bld.ITarget.Module base = ti.targets.TMS470;

    override readonly config ITarget.Command ar = {
        cmd:  "ar470",
        opts: "rq"
    };

    override readonly config ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: "-mv4"
    };

    override readonly config ITarget.Command vers = {
        cmd:  "cl470",
        opts: "-version"
    };

    override readonly config ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: "-mv4"
    };

    override readonly config ITarget.Command lnk = {
        cmd:  "lnk470",
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
     *  ======== ccConfigOpts ========
     *  User configurable compiler options for the generated config C file.
     */
    override config ITarget.Options ccConfigOpts = {
        prefix: "$(ccOpts.prefix) -ms",
        suffix: "$(ccOpts.suffix)"
    };

    /*!
     *  ======== profiles ========
     *  Standard options profiles for the TI tool-chain.
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-g",
                defs:  "-D_DEBUG_=1",
            }
        }],
        ["release", {
            compileOpts: {
                copts: "-O2",
            },
        }],
        ["profile", {
            compileOpts: {
                copts: "-gp",
            },
        }],
        ["coverage", {
            compileOpts: {
                copts: "-gp",
            },
        }],
        ["whole_program", {
            compileOpts: {
                copts: "-oe -O2 -ms",
            },
        }],
        ["whole_program_debug", {
            compileOpts: {
                copts: "-oe --symdebug:dwarf -ms",
            },
        }],
    ];

    /*!
     *  ======== linkLib ========
     *  Default TMS470 cgtools runtime library to link with 
     *  (options: rts16.lib, rts32.lib)
     */
    config string linkLib = "rts16.lib";
    
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
     */
    override config ITarget.Options lnkOpts = {
        prefix: "-w -q -u _c_int00",
        suffix: "-c -m $(XDCCFGDIR)/$@.map " /* + -l $(rootDir)/lib/linkLib */
    };

    override config string includeOpts = "-I$(rootDir)/include/rts -I$(rootDir)/include ";

    final override readonly config string sectMap[string] =
        ti.targets.TMS470.sectMap;

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 4, align: 4 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 8, align: 4 },
        t_Float         : { size: 4, align: 4 },
        t_Fxn           : { size: 4, align: 4 },
        t_Int           : { size: 4, align: 4 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 2, align: 2 },
        t_Int32         : { size: 4, align: 4 },
        t_Int64         : { size: 8, align: 4 },
        t_Long          : { size: 4, align: 4 },
        t_LDouble       : { size: 8, align: 4 },
        t_LLong         : { size: 8, align: 4 },
        t_Ptr           : { size: 4, align: 4 },
        t_Short         : { size: 2, align: 2 },
    };
};
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:16; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

