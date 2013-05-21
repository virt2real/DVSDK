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
 */
package microsoft.targets;

/*!
 *  ======== ITarget ========
 *  A Microsoft-specific extension to the base xdc.bld.ITarget interface.
 */
@TargetHeader("xdc/bld/stddefs.xdt")
metaonly interface ITarget inherits xdc.bld.ITarget {

    override readonly config string stdInclude = "microsoft/targets/std.h";
    override config string dllExt     = ".dll";

    /*!
     *  ======== debugGen ========
     *  Debugger/IDE project file generation support.
     * 
     *  The settings below generate VC project files that enable one
     *  to debug (and even rebuild) Executables from within the VC GUI.
     *
     *  To avoid unnecessary build time overhead, these files are not always
     *  generated; by default, they are only generated for "debug" profiles.
     *  The generation of these files is controlled by the
     *  `{@link xdc.cfg.Program#gen}` configuration parameter.  To force these
     *  files to be generated for a particular executable, add the following
     *  line to the executable's program configuration script:
     *  @p(code)
     *      Program.gen.debuggerFiles = true;
     *  @p
     *  It is also possible to control the generation via build options; see
     *  `{@link xdc.bld.ITarget#DebugGen}`.
     *
     *  To debug an executable: double click on the generated *.vcproj file,
     *      when the debugger comes up, type F11 (step into).
     *
     *  The first time you debug an executable, the VC debugger may prompt
     *  you for a "solution file" to save.  Click OK (accepting the solution
     *  file name), and you will be at the first statement of your
     *  executable.
     *
     *  To set command line arguments prior to debugging: open the
     *  executable's "Project Properties" dialog (select the
     *  executable in the "Solution Explorer" window and pull-down
     *  View->"Property Pages" or type shift-F4), select "Debugging"
     *  in the left-most pane of the executable's "Property Pages", and
     *  enter command line arguments in the "Command Arguments" text box.
     *
     *  @see  http://msdn.microsoft.com/library/default.asp?url=/library/en-us/vsdebug/html/vxtskdebugginganexecreatedwithoutvisualstudioproject.asp
     */
    override config xdc.bld.ITarget.DebugGen debugGen = {
        execTemplate: "microsoft/targets/vc_exec.xdt",
        execPattern: "$(cfgName).vcproj"
    };

    /*!
     *  ======== profiles ========
     *  Standard options profiles for the microsoft tool-chain.
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-Z7 -Odi -MTd",
                defs:  "-D_DEBUG=1",
            },
            linkOpts: "-debug msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib",
        }],

        ["release", {
            compileOpts: {
                copts: "-O2 -MT",
                defs:  "",
            },
            linkOpts: "msvcrt.lib setargv.obj oldnames.lib ole32.lib oleaut32.lib olepro32.lib uuid.lib kernel32.lib user32.lib gdi32.lib advapi32.lib shell32.lib comctl32.lib",
        }],
    ];

    /*!
     *  ======== Command ========
     *  Required command and options.
     *
     *  The compile, link, and archive functions in this interface are
     *  implemented by expanding the strings specified in this structure
     *  and inserting strings from the Options structure to form a single
     *  command.  The strings in this structure can not be changed by
     *  the user (they are fixed by the target), but the string in the
     *  Options structure may be changed by the user.
     *
     *  The final command is:
     *      Command.cmd Options.prefix Command.opts Options.suffix
     *
     *  @field(cmd)     name of a tool-chain executable without any path
     *                  information.  The location of this executable is
     *                  specified by the binDir (or pathPrefix) 
     *                  configuration parameter.
     *
     *  @field(opts)    required options passed to the command; these options
     *                  can not be changed or eliminated by user's
     *                  configuration script.
     */
    struct Command {
        string cmd;     /*! the command to run */
        string opts;    /*! required options for the command */
    }

    /*!
     *  ======== Options ========
     *  User configurable command options.
     *
     *  The option strings allow the user to pass additional parameters to the
     *  executable that is responsible for compiling, linker, or archiving.
     *
     *  @a(see)
     *  microsoft.targets.ITarget.Command
     */
    struct Options {
        string prefix;  //! options placed before required command options
        string suffix;  //! options placed after required command options
    }

    /*!
     *  ======== ar ========
     *  The command used to create an archive (i.e., library)
     */
    readonly config Command ar;

    /*!
     *  ======== arOpts ========
     *  User configurable archiver options.
     */
    config Options arOpts = {
        prefix: "",
        suffix: ""
    };

    /*!
     *  ======== lnk ========
     *  The command used to link executables.
     */
    readonly config Command lnk;

    /*!
     *  ======== lnkOpts ========
     *  User configurable linker options.
     */
    config Options lnkOpts = {
        prefix: "",
        suffix: ""
    };

    /*!
     *  ======== cc ========
     *  The command used to compile C/C++ source files into object files
     */
    readonly config Command cc;

    /*!
     *  ======== ccOpts ========
     *  User configurable compiler options.
     */
    config Options ccOpts = {
        prefix: "",
        suffix: ""
    };

    /*!
     *  ======== asm ========
     *  The command used to assembles assembly source files into object files
     */
    readonly config Command asm;

    /*!
     *  ======== setPath ========
     *  Return path needed to find necessary DLLS
     *
     *  The microsoft compilers often require one or more directories to
     *  be in the PATH; this allows the compiler to find necessary DLLs.
     *  A target implementing this function returns a string with path
     *  components separated by ";".
     */
    function setPath();

    /*!
     *  ======== cmdPrefix ========
     *  Prefix to put in front of each command
     *
     *  This string is put in front of every Command before being passed to
     *  the shell for execution.  This string can be used to run the compiler
     *  in emulation environments.  
     */
    config String cmdPrefix = "";
    
    /*!
     *  ======== strictANSI ========
     *  Disable Microsoft C/C++ language extensions
     *
     *  Set to true if you plan to port your program to other environments.
     *  The compiler treats extended keywords as simple identifiers, disables
     *  the other Microsoft extensions, and automatically defines the
     *  `__STDC__` predefined macro for C programs. This option shows up
     *  as `"-Za"` on the command line when strictANSI is set to `true`.
     */
    config bool strictANSI = true;
    
    /*!
     *  ======== version ========
     *  The Compatibility Key associated with this target.
     *
     *  The first two components of this target Compatibility Key are '1,0'.
     *  The rest of the Key represents the compiler version. The third
     *  component combines the major and the minor version number in the format
     *  Major.Minor. The fourth component is the build number.
     *
     *  @a(Example)
     *  If this target's `rootDir` points to the Visual C++ 2005 Express 
     *  Edition, the output of the command `cl` may contains the compiler
     *  version string 14.00.50727.42. The Compatibility Key is
     *  [1,0,14.00,50727].
     *  
     */
    override metaonly config String version;

    /*!
     *  ======== asmOpts ========
     *  User configurable assembler options.
     */
    config Options asmOpts = {
        prefix: "",
        suffix: ""
    };

    /*!
     *  ======== includeOpts ========
     *  Additional user configurable target-specific include path options
     */
    config string includeOpts;

    /*!
     *  ======== stdTypes ========
     *  @_nodoc
     */
    override readonly config xdc.bld.ITarget.StdTypes stdTypes = {
        t_IArg          : { size: 4, align: 1 },
        t_Char          : { size: 1, align: 1 },
        t_Double        : { size: 8, align: 1 },
        t_Float         : { size: 4, align: 1 },
        t_Fxn           : { size: 4, align: 1 },
        t_Int           : { size: 4, align: 1 },
        t_Int8          : { size: 1, align: 1 },
        t_Int16         : { size: 2, align: 1 },
        t_Int32         : { size: 4, align: 1 },
        t_Int64         : { size: 8, align: 1 },
        t_Long          : { size: 4, align: 1 },
        t_LDouble       : { size: 8, align: 1 },
        t_Ptr           : { size: 4, align: 1 },
        t_Short         : { size: 2, align: 1 },
    };
}
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

