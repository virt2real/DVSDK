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
 *  ======== Sparc.xdc ========
 *  Native Sparc Solaris target
 *
 *  This module defines a native target for Solaris on Sparc workstations
 */
metaonly module Sparc inherits gnu.targets.ITarget {
    override readonly config string name                = "Sparc";      
    override readonly config string os                  = "Solaris";    
    override readonly config string suffix              = "5";
    override readonly config string isa                 = "sparc";      
    override readonly config xdc.bld.ITarget.Model model= {
        endian: "big"
    };

    override readonly config string rts                 = "gnu.targets.rts5";

    override config string platform = "host.platforms.SUN";
    
    override readonly config ITarget.Command ar = {
        cmd: "$(rootDir)/bin/ar",
        opts: "cr"
    };

    override readonly config ITarget.Command cc = {
        cmd: "$(rootDir)/bin/gcc -c -MD -MF $@.dep",
        opts: "-B$(rootDir)/lib/gcc/$(GCCTARG)/$(GCCVERS)/ -B$(rootDir)/lib/gcc-lib/$(GCCTARG)/$(GCCVERS)/"
    };

    override config ITarget.Options ccOpts = {
        prefix: "-fPIC -m32 -Wunused",
        suffix: "-Dfar="
    };

    override readonly config ITarget.Command asm = {
        cmd: "$(rootDir)/bin/gcc -c -x assembler",
        opts: "-B$(rootDir)/lib/gcc/$(GCCTARG)/$(GCCVERS)/ -B$(rootDir)/lib/gcc-lib/$(GCCTARG)/$(GCCVERS)/"
    };

    override config ITarget.Options lnkOpts = {
        prefix: "",
        suffix: "-lstdc++ -L$(rootDir)/lib"
    };
        
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
        t_LDouble       : { size: 16, align: 8 },
        t_LLong         : { size: 8, align: 8 },
        t_Ptr           : { size: 4, align: 4 },
        t_Short         : { size: 2, align: 2 },
    };
}
/*
 *  @(#) gnu.targets; 1, 0, 1,387; 2-24-2010 16:24:01; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

