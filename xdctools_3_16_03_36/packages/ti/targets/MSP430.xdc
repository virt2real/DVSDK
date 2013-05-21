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
 *  ======== MSP430.xdc ========
 */

/*!
 *  ======== MSP430.xdc ========
 *  TI MSP430 little endian target
 */

metaonly module MSP430 inherits ti.targets.ITarget {
    override readonly config string name             = "MSP430"; 
    override readonly config string suffix           = "430";
    override readonly config string isa              = "430";    
    override readonly config string rts              = "ti.targets.rts430";
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little"
    };

    override readonly config ITarget.Command ar = {
        cmd:  "ar430",
        opts: "rq"
    };

    override readonly config ITarget.Command cc = {
        cmd:  "cl430 -c",
        opts: " -vmsp"
    };

    override readonly config ITarget.Command vers = {
        cmd:  "cl430",
        opts: "-version"
    };

    override readonly config ITarget.Command asm = {
        cmd:  "cl430 -c",
        opts: " -vmsp"
    };

    override readonly config ITarget.Command lnk = {
        cmd:  "lnk430",
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
     *  ======== linkLib ========
     *  Default MSP430 cgtools runtime library to link with 
     *  (options: rts16e.lib, rts32e.lib)
     */
    config string linkLib = "rts430.lib";
    
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
                copts: "-oe -O2",
            },
        }],
        ["whole_program_debug", {
            compileOpts: {
                copts: "-oe --symdebug:dwarf",
            },
        }],
    ];

    override config string includeOpts = "-I$(rootDir)/include ";

    final override readonly config string sectMap[string] = [
        [".text", "code"],
        [".cinit", "code"],
        [".const", "code"],
        [".pinit", "code"],

        [".bss", "data"],
        [".sysmem", "data"],
        [".stack", "stack"],
        [".args", "data"],
        [".cio", "data"],
        [".reset", "data"],
    ];

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 2, align: 2 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 4, align: 2 },
        t_Float         : { size: 4, align: 2 },
        t_Fxn           : { size: 2, align: 2 },
        t_Int           : { size: 2, align: 2 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 2, align: 2 },
        t_Int32         : { size: 4, align: 2 },
        t_Long          : { size: 4, align: 2 },
        t_LDouble       : { size: 4, align: 2 },
        t_LLong         : { size: 4, align: 2 },
        t_Ptr           : { size: 2, align: 2 },
        t_Short         : { size: 2, align: 2 },
        t_Size          : { size: 2, align: 2 },
    };
};
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:15; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

