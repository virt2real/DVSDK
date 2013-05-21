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
 *  ======== C54_far.xdc ========
 *
 */

/*!
 *  ======== C54_far ========
 *  TI C54 far model target
 */
metaonly module C54_far inherits ti.targets.ITarget {
    override readonly config string name                = "C54_far";    
    override readonly config string suffix              = "54f";
    override readonly config string isa                 = "54"; 
    override readonly config xdc.bld.ITarget.Model model= {codeModel: "far"};
    override readonly config string rts                 = "ti.targets.rts5400";

    override readonly config xdc.bld.ITarget.Module base= ti.targets.C54;

    override readonly config ITarget.Command ar = {
        cmd: "ar500",
        opts: "rq"
    };

    override readonly config ITarget.Command cc = {
        cmd: "cl500 -c",
        opts: "-mf -v548"
    };

    override readonly config ITarget.Command vers = {
        cmd: "cl500",
        opts: "-version"
    };

    override readonly config ITarget.Command asm = {
        cmd: "cl500 -c",
        opts: "-mf -v548"
    };

    override readonly config ITarget.Command lnk = {
        cmd: "lnk500",
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
        prefix: "$(ccOpts.prefix)",
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
    override config ITarget.Options lnkOpts = {
        prefix: "-w -q -u _c_int00",
        suffix: "-c -m $(XDCCFGDIR)/$@.map -l $(rootDir)/lib/rts500EXT.lib"
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
                copts: "-oe -O2",
            },
        }],
        ["whole_program_debug", {
            compileOpts: {
                copts: "-oe --symdebug:dwarf",
            },
        }],
    ];

    override config string includeOpts = "-I$(rootDir)/include";

    final override readonly config string sectMap[string] =
        ti.targets.C54.sectMap;

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
        t_Long          : { size: 2, align: 2 },
        t_LDouble       : { size: 2, align: 2 },
        t_Ptr           : { size: 1, align: 1 },
        t_Short         : { size: 1, align: 1 },
    };

    override readonly config Int bitsPerChar = 16;
};
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:14; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

