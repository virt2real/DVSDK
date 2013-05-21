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
 *  ======== TMS470.xdc ========
 *
 */

/*!
 *  ======== TMS470.xdc ========
 *  TI TMS470 (Arm) little endian ELF EABI target
 */
metaonly module TMS470 inherits ti.targets.ITarget {
    override readonly config string name             = "TMS470"; 
    override readonly config string suffix           = "e470";
    override readonly config string isa              = "470";    
    override readonly config string rts              = "ti.targets.arm.rtsarm";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little",
        shortEnums: true
    };

    override config string platform = "ti.platforms.sim470xx";

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["7"];

    override readonly config ti.targets.ITarget.Command ar = {
        cmd:  "ar470",
        opts: "rq"
    };

    override readonly config ti.targets.ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: " -me -mv4 --abi=eabi"
    };

    override readonly config ti.targets.ITarget.Command vers = {
        cmd:  "cl470",
        opts: "-version"
    };

    override readonly config ti.targets.ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: " -me -mv4 --abi=eabi"
    };

    override readonly config ti.targets.ITarget.Command lnk = {
        cmd:  "lnk470",
        opts: " --abi=eabi"
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
     */
    override config ti.targets.ITarget.Options ccConfigOpts = {
        prefix: "$(ccOpts.prefix) -ms",
        suffix: "$(ccOpts.suffix)"
    };

    /*!
     *  ======== linkLib ========
     *  Default TMS470 cgtools runtime library to link with 
     *  (options: rtsv4_T_le_eabi.lib,
     *   rtsv7M3_T_le_eabi.lib, rtsv4_A_le_eabi_eh.lib,
     *   rtsv7A8_A_le_n_eabi.lib, rtsv7R4_T_le_eabi.lib)
     */
    config string linkLib = "rtsv4_T_le_eabi.lib";
    
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

    override config string includeOpts = "-I$(rootDir)/include/rts -I$(rootDir)/include ";

    final override readonly config string sectMap[string] = [
        [".intvecs", "code"],

        [".text", "code"],
        [".cinit", "code"],
        [".const", "code"],
        [".data", "data"],
        [".pinit", "code"],

        [".bss", "data"],
        [".sysmem", "data"],
        [".stack", "stack"],
        [".args", "data"],
    ];

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
 *  @(#) ti.targets.elf; 1, 0, 0,152; 2-24-2010 16:24:19; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

