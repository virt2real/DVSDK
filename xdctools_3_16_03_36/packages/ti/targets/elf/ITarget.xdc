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
 *  ======== ITarget.xdc ========
 *
 */

/*!
 *  ======== ITarget ========
 *  An ELF extension to the `ti.targets.ITarget` interface.
 */
metaonly interface ITarget inherits ti.targets.ITarget {

    override readonly config xdc.bld.ITarget.Model model = {
        shortEnums: true
    };

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
                copts: "-oe -O2 -mo",
            },
        }],
        ["whole_program_debug", {
            compileOpts: {
                copts: "-oe --symdebug:dwarf -mo",
            },
        }],
    ];

    final override readonly config string sectMap[string] = [
        [".text", "code"],
        [".ti.decompress", "code"],
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
        [".cio", "data"],
        [".ti.handler_table", "data"],
    ];

    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 4, align: 4 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 8, align: 8 },
        t_Float         : { size: 4, align: 4 },
        t_Fxn           : { size: 4, align: 4 },
        t_Int           : { size: 4, align: 4 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 2, align: 2 },
        t_Int32         : { size: 4, align: 4 },
        t_Int64         : { size: 8, align: 8 },
        t_Long          : { size: 4, align: 4 },
        t_LDouble       : { size: 8, align: 8 },
        t_LLong         : { size: 8, align: 8 },
        t_Ptr           : { size: 4, align: 4 },
        t_Short         : { size: 2, align: 2 },
    };
    
    override config String stdInclude = "ti/targets/elf/std.h";

    override config String binaryParser = "ti.targets.omf.elf.Elf32";
}
/*
 *  @(#) ti.targets.elf; 1, 0, 0,152; 2-24-2010 16:24:19; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

