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
 *  ======== VC98.xdc ========
 */

package microsoft.targets

/*!
 *  ======== VC98.xdc ========
 *  Microsoft Windows 32-bit target using the Visual C/C++ 6.x compiler
 */

metaonly module VC98 inherits microsoft.targets.ITarget {

    override readonly config string name                    = "VC98";   
    override readonly config string os                      = "Windows";
    override readonly config string suffix                  = "86";
    override readonly config string isa                     = "x86";    
    override readonly config xdc.bld.ITarget.Model model    = {
        endian: "little"
    };

    override readonly config string rts = "microsoft.targets.rts";
    override config string platform     = "host.platforms.PC";
    override config string execExt      = ".exe";
    
    /*!
     *  ======== path ========
     *  Path components added during execution of commands
     *
     *  The VC98 compiler DLLs are located in the vc98/bin subdirectory 
     *  the pdb DLL is located in $(rootDir)/msdev98/bin.
     */
    readonly config string path =
        "$(rootDir)/vc98/bin;$(rootDir)/common/msdev98/bin";

    /*!
     *  ======== ar ========
     *  The archiver command and all required options
     *  @p(dlist)
     *      -`-nologo`
     *          don't display archiver copyright
     */
    override readonly config ITarget.Command ar = {
        cmd: "$(rootDir)/vc98/bin/lib",
        opts: "-nologo"
    };

    /*!
     *  ======== cc ========
     *  The compile command and all required options
     *  @p(dlist)
     *      -`-W3`
     *          enable all warnings recommended for production purposes.
     *      -`-Zp1`
     *          Packs structure members on 1-byte boundry
     *      -`-c`
     *          don't link
     *      -`-nologo`
     *          don't display compiler copyright
     */
    override readonly config ITarget.Command cc = {
        cmd: "$(rootDir)/vc98/bin/cl.exe -nologo -c",
        opts: '-W3 -Zp1 -DWIN32 -D_DLL -D_AFXDLL -DEXPORT=""'
    };

    /*!
     *  ======== asm ========
     *  The assemble command and all required options
     *  @p(dlist)
     *      -`-c`
     *          don't link
     *      -`-nologo`
     *          don't display compiler copyright
     */
    override readonly config ITarget.Command asm = {
        cmd: "$(rootDir)/vc98/bin/cl.exe -nologo -c",
        opts: ""
    };

    /*!
     *  ======== lnk ========
     *  The linker command and all required options
     *  @p(dlist)
     *      -`-nologo`
     *          Don't display linker copyright
     */
    override readonly config ITarget.Command lnk = {
        cmd: "$(rootDir)/vc98/bin/link -nologo",
        opts: ""
    };
    
    /*!
     *  ======== ccOpts ========
     *  User modifiable default options.
     *  @p(dlist)
     *      -`-G5`
     *          Optimizes code to favor the Pentium processor
     *      -`-Ob1`
     *          Expand only functions marked as inline or, in a C++
     *          member function, defined within a class declaration
     *      -`-Gs`
     *          Probe stack to automatically grow stack as necessary
     *      -`-GX`
     *          Enables synchronous exception handling
     *      -`-WL`
     *          Write errors/warnings on a single output line
     */
    override config ITarget.Options ccOpts = {
        prefix: "-G5 -Ob1 -Gs -GX",
        suffix: "-Dfar= "
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
        prefix: "-libpath:$(rootDir)/vc98/lib -libpath:$(rootDir)/vc98/mfc/lib",
        suffix: "-map:$(XDCCFGDIR)/$@.map -pdb:$(XDCCFGDIR)/$@.pdb -machine:ix86 -nodefaultlib -incremental:no"
    };
        
    /*!
     *  ======== includeOpts ========
     *  User modifiable include paths
     *  @p(dlist)
     *      -`-I$(rootDir)/include`
     *          include compiler specific headers
     */
    override config string includeOpts = "-I$(rootDir)/vc98/include -I$(rootDir)/vc98/mfc/include -I$(rootDir)/vc98/atl/include";


    /*!
     *  ======== profiles ========
     *  User modifiable default profiles
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-Z7 -Odi -MTd",
                defs:  "-D_DEBUG=1",
            },
            linkOpts: "-debug mfc42.lib mfcs42.lib msvcrt.lib msvcirt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib",
        }],

        ["release", {
            compileOpts: {
                copts: "-O2 -MT",
                defs:  "",
            },
            linkOpts: "mfc42.lib mfcs42.lib msvcrt.lib msvcirt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib",
        }],
    ];
}
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

