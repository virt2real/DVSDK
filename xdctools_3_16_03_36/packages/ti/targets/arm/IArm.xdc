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
import ti.targets.ITarget;

/*!
 *  ======== IArm.xdc ========
 *  Common settings for all Arm targets
 */
metaonly interface IArm inherits ti.targets.ITarget {

    override readonly config string stdInclude = "ti/targets/arm/std.h";

    override config string platform   = "ti.platforms.sim470xx";

    override config string includeOpts =
        "-I$(rootDir)/include/rts -I$(rootDir)/include ";

    override readonly config ITarget.Command ar = {
        cmd:  "ar470",
        opts: "rq"
    };

    override readonly config ITarget.Command vers = {
        cmd:  "cl470",
        opts: "-version"
    };

    override readonly config ITarget.Command lnk = {
        cmd:  "lnk470",
        opts: ""
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

    final override readonly config string sectMap[string] = [
        [".intvecs", "code"],

        [".text", "code"],
        [".cinit", "code"],
        [".const", "code"],
        [".pinit", "code"],

        [".bss", "data"],
        [".sysmem", "data"],
        [".stack", "stack"],
        [".args", "data"],
    ];

    override readonly config Int bitsPerChar = 8;

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
}
/*
 *  @(#) ti.targets.arm; 2, 0, 1, 0,202; 2-24-2010 16:24:12; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

