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

/*!
 *  ======== IArm.xdc ========
 *  Common settings for all Arm targets
 */
metaonly interface IArm inherits ti.targets.ITarget {

    override config String stdInclude = "ti/targets/arm/elf/std.h";

    override config string platform   = "ti.platforms.sim470xx";

    override config string includeOpts = "-I$(rootDir)/include/rts -I$(rootDir)/include ";

    override readonly config xdc.bld.ITarget.Model model = {
        shortEnums: true,
    };

    override readonly config ti.targets.ITarget.Command ar = {
        cmd:  "ar470",
        opts: "rq"
    };

    override readonly config ti.targets.ITarget.Command vers = {
        cmd:  "cl470",
        opts: "-version"
    };

    override readonly config ti.targets.ITarget.Command lnk = {
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
    override config ti.targets.ITarget.Options ccOpts = {
        prefix: "-qq -pdsw225",
        suffix: ""
    };

    /*!
     *  ======== ccConfigOpts ========
     *  User configurable compiler options for the generated config C file.
     */
    override config ti.targets.ITarget.Options ccConfigOpts = {
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
    override config ti.targets.ITarget.Options asmOpts = {
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
    override config ti.targets.ITarget.Options lnkOpts = {
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
                copts: "--symdebug:dwarf",
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
                copts: "--gen_profile_info",
            },
        }],
        ["coverage", {
            compileOpts: {
                copts: "--gen_profile_info",
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
        [".text", "code"],
        [".stack", "stack"],
        [".bss", "data"],
        [".cinit", "data"],
        [".pinit", "data"],
        [".const", "data"],
        [".data", "data"],
        [".rodata", "data"],
        [".neardata", "data"],
        [".fardata", "data"],
        [".switch", "data"],
        [".sysmem", "data"],
        [".far", "data"],
        [".args", "data"],
        [".cio", "data"]
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

    override config String binaryParser = "ti.targets.omf.elf.Elf32";
}

/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,134; 2-24-2010 16:24:14; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

