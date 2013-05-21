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
 *  ======== Win32.xdc ========
 */

/*!
 *  ======== Win32 ========
 *  Microsoft Windows 32-bit target using the Visual C/C++ compiler
 *
 *  This target can be configured to be used with different versions of
 *  Microsoft Visual C/C++ and different installations of Platform SDK (or a
 *  newer equivalent Windows SDK). The optional Platform SDK is needed only
 *  for building applications that use Windows API.
 *  The target `Win32` contains default configurations for Visual C/C++
 *  versions 6.0, 7.0 and 8.0, but in order to support future versions of
 *  Visual C/C++ and different Platform SDK installations, there
 *  is a parameter {@link #vcPath}, which users can set in their `config.bld`
 *  files to enable usage of this target with their installations. 
 *
 *  Unlike the Visual C/C++ 6.x tool chain, this compiler complies very
 *  closely with the C/C++ language specification.  This target may be
 *  necessary in situations that take full advantage of the C++ language.
 */
metaonly module Win32 inherits microsoft.targets.ITarget {

    override readonly config string name                = "Win32";      
    override readonly config string os                  = "Windows";    
    override readonly config string suffix              = "86W";
    override readonly config string isa                 = "x86";        
    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little"
    };

    override readonly config string rts = "microsoft.targets.rts";

    override config string platform     = "host.platforms.PC";
    override config string execExt      = ".exe";
    
    /*!
     *  ======== VCPath ========
     *
     *  Object that defines various paths in a particular Visual Studio
     *  installation.
     *
     *  Different Visual Studio installations keep the actual compiler and
     *  additional required DLLs in separate directories. Also, a Platform SDK
     *  installation is needed for building programs that use Windows API.
     *
     *  @field(compilerDir) Relative path from this target's rootDir to the
     *          directory that contains the compiler.
     *
     *  @field(dllPath) Relative path from this target's rootDir to the 
     *          directory that contains mspdb.dll, mspdbcore.dll, etc.
     *
     *  @field(sdkPath) Relative path from this target's rootDir to a
     *          Platform SDK installation or an absolute path to a Platform SDK
     *          installation. Platform SDK is required if the target is used to
     *          build executables that use Windows API.
     *
     *  @field(libs) List of libraries to be added to the linker command line.
     *          If Platform SDK is used, the list should contain required 
     *          libraries from sdkPath/lib. Otherwise, only the libraries from
     *          compilerDir/lib can be added to 'libs'.
     */
    struct VCPath {
        string compilerDir;
        string dllPath;
        string sdkPath;
        string libs;
    };

    /*!
     *  ======== vcPath ========
     *  Location of the compiler, additional DLLs, and Platform SDK
     *  installation
     *
     *  This parameter is a map that contains information about paths to DLLs
     *  needed for building applications, and paths to the optional Platform
     *  SDK. Keys in the map are user-selected aliases for different Visual
     *  C/C++ releases. The values are {@link #VCPath} objects. 
     *  This parameter can be set only in `config.bld`, together with
     *  `rootDir`. If `vcPath` is not set in `rootDir`, the default values
     *  specified below are used. After a user sets this target's `rootDir`,
     *  XDCtools search through the 
     *  values in `vcPath`, looking for a field `compilerDir` whose content
     *  matches a name of a subdirectory in `rootDir`. Once a match is found,
     *  the content of that element of the map is used to find a path to
     *  required DLLs, a path to Platform SDK and a list of libraries.
     *
     *  @a(Examples)
     *  If the content of `vcPath`, set in `config.bld` is
     *  @p(code)
     *      Win32.vcPath = [
     *          ["Visual Studio 7",
     *              {
     *                  compilerDir: "Vc7",
     *                  dllPath: "Common7/IDE;VisualStudio.NETProfessional-English",
     *                  sdkPath: "C:/PlatformSDK",
     *                  libs: " msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib mfc70.lib msvcirt.lib"
     *              }
     *          ],
     *          ["Visual Studio C++ 2005",
     *              {
     *                  compilerDir: "VC",
     *                  dllPath: "Common7/IDE",
     *                  sdkPath: "VC/PlatformSDK",
     *                  libs: " msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib"
     *              }
     *          ]
     *      ];
     *  @p
     *  and the `rootDir` for the target `Win32` is set to 
     *  `"C:/Program Files/Microsoft Visual Studio 8"`, XDCtools will first 
     *  check if there is a directory `"Vc7"` under `rootDir`. If the directory
     *  is not found, the next element in the map and its `compilerDir` field
     *  are queried. In this case, the next element's `compilerDir` is `"VC"`.
     *  If that directory is found under `rootDir`, the other fields in that
     *  element are used as follows: `compilerDir` and `dllPath` are added to
     *  the environment variable `PATH`. The contents of `sdkPath` and `libs`
     *  are added to appropriate command lines.
     *
     *  If none of the elements in the map has `compilerDir` that corresponds
     *  to a subdirectory in `rootDir`, the configuration fails.
     *
     *  Once a user sets up `vcPath` with all available installations of
     *  Visual Studio, simply by switching `rootDir` for this target, the
     *  right component of `vcPath` will be selected.
     *     
     *  The default version of this parameter contains settings for several
     *  Visual Studio releases. Therefore, a user does not have to completely
     *  redefine `vcPath`. Only the fields that corresponds to settings that
     *  differ between user's configuration and the default configuration
     *  need to be changes. For example, if the only difference between the
     *  default configuration and a user's environment is that the user
     *  installed Platform SDK to be used with Visual C/C++ 8 in a different
     *  directory, only that field needs to be changed.
     *  @p(code)
     *      var Win32 = xdc.module('microsoft.targets.Win32');
     *      Win32.vcPath["VC8"].sdkPath = "C:/WindowsSDK";
     *  @p
     *
     *  If Platform SDK is not installed, sdkPath should be empty and the 
     *  libraries from Platform SDK should be removed from 'libs':
     *  @p(code)
     *      var Win32 = xdc.module('microsoft.targets.Win32');
     *      Win32.vcPath = [
     *          ["VC8",
     *              {
     *                  compilerDir: "VC",
     *                  dllPath: "Common7/IDE",
     *                  sdkPath: "",
     *                  libs: " msvcrt.lib setargv.obj oldnames.lib"
     *              }
     *          ],
     *      ];
     *  @p
     *
     */
    config VCPath vcPath[string] = [
        ["VC6", {compilerDir: "vc98", dllPath: "common/msdev98/bin",
                 sdkPath: "",
                 libs: " msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib mfc42.lib msvcirt.lib"}],
        ["VC7", {compilerDir: "Vc7",
                 dllPath: "Common7/IDE;VisualStudio.NETProfessional-English",
                 sdkPath: "Vc7/PlatformSDK",
                 libs: " msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib mfc70.lib msvcirt.lib"}],
        /* Free version of VC8.0 doesn't include mfc libraries. */
        ["VC8", {compilerDir: "VC",   dllPath: "Common7/IDE",
                 sdkPath: "VC/PlatformSDK",
                 libs: " msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib"}],
    ];

    /*!
     *  ======== profiles ========
     *  Standard options profiles are overwritten because we can't use 'MTs'
     *  and -D_DEBUG=1. Both of them added the debug version of the C runtime
     *  library to the manifest.
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-Z7 -Odi -MT",
                defs:  "",
            },
            linkOpts: "-debug ",
        }],

        ["release", {
            compileOpts: {
                copts: "-O2 -MT",
                defs:  "",
            },
            linkOpts: "",
        }],
    ];

    /*!
     *  ======== ar ========
     *  The archiver command and all required options
     *  @p(dlist)
     *      -`-nologo`
     *          don't display archiver copyright
     */
    override readonly config ITarget.Command ar = {
        cmd: "$(rootDir)/$(compilerDir)/bin/lib.exe -nologo",
        opts: ""
    };

    /*!
     *  ======== cc ========
     *  The compile command and all required options
     *  @p(dlist)
     *      -`-W3`
     *          enable all warnings recommended for production purposes.
     *      -`-c`
     *          don't link
     *      -`-nologo`
     *          don't display compiler copyright
     *      -`-Zp1`
     *          Packs structure members on 1-byte boundry
     */
    override readonly config ITarget.Command cc = {
        cmd: "$(rootDir)/$(compilerDir)/bin/cl.exe -nologo -c",
        opts: '-Zp1 -W3 -DWIN32 -D_DLL -D_AFXDLL -DEXPORT=""'
    };

    /*!
     *  ======== asm ========
     *  The assemble command and all required options
     *  @p(dlist)
     *      -`-c`
     *          don't link
     *      -`-nologo`
     *          don't display macro assembler copyright
     */
    override readonly config ITarget.Command asm = {
        cmd: "$(rootDir)/$(compilerDir)/bin/ml -c",
        opts: "-nologo"
    };

    /*!
     *  ======== lnk ========
     *  The linker command and all required options
     *  @p(dlist)
     *      -`-nologo`
     *          Don't display linker copyright
     */
    override readonly config ITarget.Command lnk = {
        cmd: "$(rootDir)/$(compilerDir)/bin/link",
        opts: "-nologo"
    };
    
    /*!
     *  ======== ccOpts ========
     *  User modifiable default options.
     *  @p(dlist)
     *      -`-G5` (removed because it is incompatible with VC8.0)
     *          Optimizes code to favor the Pentium processor
     *      -`-Ob1`
     *          Expand only functions marked as inline or, in a C++
     *          member function, defined within a class declaration
     *      -`-Gs`
     *          Probe stack to automatically grow stack as necessary
     *      -`-GX` (removed because it is incompatible with VC8.0)
     *          Enables synchronous exception handling
     *      -`-WL`
     *          Write errors/warnings on a single output line
     */
    override config ITarget.Options ccOpts = {
        prefix: "-Ob1 -Gs",
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
        prefix: "-libpath:$(rootDir)/$(compilerDir)/lib -libpath:$(rootDir)/$(compilerDir)/atlmfc/lib -libpath:$(rootDir)/$(compilerDir)/mfc/lib -libpath:$(sdkPath)/lib",
        suffix: "-map:$(XDCCFGDIR)/$@.map -pdb:$(XDCCFGDIR)/$@.pdb -machine:ix86 -nodefaultlib -incremental:no"
    };
        
    /*!
     *  ======== includeOpts ========
     *  User modifiable include paths
     *  @p(dlist)
     *      -`-I$(rootDir)/$(compilerDir)/include`
     *          include compiler specific headers
     */
    override config string includeOpts = "-I$(rootDir)/$(compilerDir)/include -I$(rootDir)/$(compilerDir)/atlmfc/include -I$(rootDir)/$(compilerDir)/mfc/include -I$(rootDir)/$(compilerDir)/atl/include -I$(sdkPath)/include";
}
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

