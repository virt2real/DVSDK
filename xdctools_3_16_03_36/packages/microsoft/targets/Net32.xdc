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
 *  ======== Net32.xdc ========
 */
package microsoft.targets;

/*!
 *  ======== Net32 ========
 *  Microsoft .Net 32-bit native target
 *
 *  This target supports the free Microsoft .Net C/C++ compiler; aka the
 *  Microsoft Visual C++ Toolkit 2003 available from
 *  http://msdn.microsoft.com/visualc/vctoolkit2003.
 */
metaonly module Net32 inherits microsoft.targets.ITarget {

    override readonly config string name                    = "Net32";  
    override readonly config string os                      = "Windows";        
    override readonly config string suffix                  = "86N";
    override readonly config string isa                     = "x86";    
    override readonly config xdc.bld.ITarget.Model model    = {
        endian: "little"
    };

    /*!
     *  ======== profiles ========
     *  User modifiable default profiles
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-Z7 -Od -MTd",
                defs:  "-D_DEBUG=1",
            },
            linkOpts: "libcmt.lib kernel32.lib",
        }],

        ["release", {
            compileOpts: {
                copts: "-Oxi -MT",
            },
            linkOpts: "libcmt.lib kernel32.lib",
        }],
    ];

    override readonly config string rts     = "microsoft.targets.rts";
    override config string platform         = "host.platforms.PC";
    override config string execExt          = ".exe";
    
    /*!
     *  ======== ar ========
     *  The archiver command and all required options
     *  @p(dlist)
     *      -`-nologo`
     *          don't display archiver copyright
     */
    override readonly config ITarget.Command ar = {
        cmd: "$(rootDir)/bin/link.exe -lib -nologo",
        opts: ""
    };

    /*!
     *  ======== cc ========
     *  The compile command and all required options
     *  @p(dlist)
     *      -`-c`
     *          don't link
     *      -`-nologo`
     *          don't display compiler copyright
     */
    override readonly config ITarget.Command cc = {
        cmd: "$(rootDir)/bin/cl",
        opts: "-nologo -c",
    };

    /*!
     *  ======== asm ========
     *  The assemble command and all required options
     *  @p(dlist)
     *      -`-c`
     *          don't link
     */
    override readonly config ITarget.Command asm = {
        cmd: "$(rootDir)/bin/cl",
        opts: "-nologo -c",
    };

    /*!
     *  ======== lnk ========
     *  The linker command and all required options
     *  @p(dlist)
     *      -`-nologo`
     *          Don't display linker copyright
     */
    override readonly config ITarget.Command lnk = {
        cmd: "$(rootDir)/bin/link -nologo",
        opts: ""
    };
    
    /*!
     *  ======== ccOpts ========
     *  User modifiable default options.
     *  @p(dlist)
     *      -`-G5`
     *          Optimizes code to favor the Pentium processor
     *      -`-W3`
     *          enable all warnings recommended for production purposes.
     */
    override config ITarget.Options ccOpts = {
        prefix: "-G5 -W3",
    };

    /*!
     *  ======== lnkOpts ========
     *  User modifiable linker options
     *  @p(dlist)
     *      -`-libpath`...
     *              directories to search for toolchain specific libraries
     *      -`-nodefaultlib`
     *              don't search for default libraries when linking; all
     *              libraries used must be explicitly named
     *      -`-incremental:no`
     *              link for execution (no subsequent link will occur)
     *      -`-machine:ix86`
     *              link for the Intel x86 architecture
     *      -`-map:$(XDCCFGDIR)/$@.map`
     *              output any link map information to the specified file
     *              ($(XDCCFGDIR) is usually package/cfg)
     *      -`-pdb:$(XDCCFGDIR)/$@.pdb`
     *              output any program debug information to the specified file
     *              ($(XDCCFGDIR) is usually package/cfg)
     */
    override config ITarget.Options lnkOpts = {
        prefix: "-libpath:$(rootDir)/lib",
        suffix: "-map:$(XDCCFGDIR)/$@.map -pdb:$(XDCCFGDIR)/$@.pdb -mapinfo:exports -machine:ix86 -nodefaultlib -incremental:no"
    };
        
    /*!
     *  ======== includeOpts ========
     *  User modifiable default include directories
     *  @p(dlist)
     *      -`-I$(rootDir)/include`
     *          include compiler specific headers
     */
    override config string includeOpts = "-I$(rootDir)/include";
}
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

