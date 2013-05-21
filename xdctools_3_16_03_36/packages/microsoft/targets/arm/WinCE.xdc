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
 *  ======== WinCE.xdc ========
 */

package microsoft.targets.arm;

/*!
 *  ======== WinCE.xdc ========
 *  Microsoft Windows Embedded "target" using the ARM compiler.
 */

metaonly module WinCE inherits microsoft.targets.ITarget {

    override readonly config string name                    = "WinCE";
    override readonly config string os                      = "WindowsCE";
    override readonly config string suffix                  = "v4TCE";
    override readonly config string isa                     = "v4T";
    override readonly config xdc.bld.ITarget.Model model    = {
        endian: "little"
    };

    override readonly config string stdInclude = "microsoft/targets/arm/std.h";
    override readonly config string rts     = "microsoft.targets.arm.rts";
/* readonly */    override config string platform   = "host.platforms.PC";
/* readonly */    override config string execExt    = ".exe";
    override config bool strictANSI  = false;
    
    /*!
     *  ======== remoteInitScript ========
     *  @_nodoc
     *  Environment initialization script.
     *
     *  When a WinCE compiler is invoked remotely, a script that initializes
     *  various environment variables must be run first.
     */
    config string remoteInitScript;

    /*!
     *  ======== projectRoot ========
     *  Path to the project root of the selected OS configuration.
     *
     *  This parameter specifies the absolute path to the root of an OS
     *  configuration within an OS design. OS configurations are located in 
     *  the subdirectory 'Wince600' of your OS design directory. Each 
     *  project root contains the batch file `PBInitEnv.bat`.
     *  This parameter determines where this target is searching for OS 
     *  modules when linking an application.
     */
    config string projectRoot;

    /*!
     *  ======== sysGenIsa ========
     *  @_nodoc
     *  Selected Arm architecture.
     *
     *  This parameter defaults to ARMV4I.
     */
    config string sysGenIsa = "ARMV4I";

   /*!
    *  ======== EntryPoint ========
    *  Entry point options
    */
    enum EntryPoint {
        UNDEFINED,         /*! -entry option is user specified */
        mainCRTStartup,    /*! for apps using SUBSYSTEM:CONSOLE, calls main */
        WinMainCRTStartup, /*! for SUBSYSTEM:WINDOWS, calls WinMain */
        _DllMainCRTStartup /*! for DLLS, calls DllMain */
    };

   /*!
    *  ======== entryPoint ========
    *  Define which function is called at startup
    */
    config EntryPoint entryPoint = mainCRTStartup;

    /*!
     *  ======== path ========
     *  Path components added during execution of commands.
     *
     *  The WinCE compiler DLLs are located in ?? subdirectory?
     *  The pdb DLL is located in ?? directory?
     */
    readonly config string path =
        "$(rootDir)/sdk/bin/i386;$(rootDir)/sdk/bin/i386/arm";

    /*!
     *  ======== ar ========
     *  The archiver command and all required options.
     *
     *  4001 warning warns that there are only libraries being supplied.
     */
    override readonly config microsoft.targets.ITarget.Command ar = {
        cmd: "$(rootDir)/sdk/bin/i386/arm/link.exe -lib -nologo",
        opts: "-ignore:4001"
    };

    /*!
     *  ======== cc ========
     *  The compile command and all required options.
     */
    override readonly config microsoft.targets.ITarget.Command cc = {
        cmd: "$(rootDir)/sdk/bin/i386/arm/cl.exe -nologo -c",
        opts: "-Gy -GF -D_CRT_SECURE_NO_DEPRECATE -D_USE_32BIT_TIME_T -DUNICODE  -D_UNICODE -DUNDER_CE=600 -D_WIN32_WCE=0x600 -DWIN32 -DSTRICT -DARM -DARMV4I  -D_ARM_ -DINTERNATIONAL -DINTLMSG_CODEPAGE=1252 -Zc:wchar_t- -Zc:forScope- -wd4867 -wd4430 -MT -U_MT -W3 /GR- -QRarch4T -DTHUMBSUPPORT -QRimplicit-import- -QRinterwork-return /GS"
    };

    /*!
     *  ======== asm ========
     *  The assemble command and all required options.
     */
    override readonly config microsoft.targets.ITarget.Command asm = {
        cmd: "$(rootDir)/sdk/bin/i386/arm/armasm.exe -nologo",
        opts: "-arch 4T"
    };

    /*!
     *  ======== lnk ========
     *  The linker command and all required options.
     */
    override readonly config microsoft.targets.ITarget.Command lnk = {
        cmd: "$(rootDir)/sdk/bin/i386/arm/link -nologo",
        opts: "-base:0x00010000 -MERGE:.rdata=.text -MERGE:.astart=.text -align:4096 -ignore:4001,4070,4078,4086,4089,4096,4099,4108,4229 /STACK:65536,4096 /LARGEADDRESSAWARE -incremental:no /opt:ref -SUBSYSTEM:WINDOWSCE,6.00"
    };

    /*!
     *  ======== ccOpts ========
     *  User modifiable default options.
     */
    override config microsoft.targets.ITarget.Options ccOpts = {
        prefix: "",
        suffix: ""
    };

    /*!
     *  ======== includeOpts ========
     *  User modifiable include paths.
     */
    override config string includeOpts = " ";

    /*!
     *  ======== lnkOpts ========
     *  User modifiable linker options.
     */
    override config microsoft.targets.ITarget.Options lnkOpts = {
        prefix: "-stack:65536,4096",
        suffix: "-map:$(XDCCFGDIR)/$@.map -pdb:$(XDCCFGDIR)/$@.pdb -nodefaultlib"
    };

    /*!
     *  ======== profiles ========
     *  User modifiable default profiles.
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-Od -Z7",
                defs:  "-D_DEBUG, -DDEBUG",
            },
            linkOpts: "-debug -debugtype:cv,fixup coredll.lib corelibc.lib",
        }],
        ["release", {
            compileOpts: {
                copts: "-O2",
                defs:  "-DNDEBUG=1",
            },
            linkOpts: "coredll.lib corelibc.lib",
        }],
    ];
}

/*
 *  @(#) microsoft.targets.arm; 1, 0, 0, 0,140; 2-24-2010 16:24:11; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

