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
 *  A TI specific extension to the base `xdc.bld.ITarget` interface.
 */
@TargetHeader("xdc/bld/stddefs.xdt")
metaonly interface ITarget inherits xdc.bld.ITarget {

    override readonly config string stdInclude = "ti/targets/std.h";
    
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
     *  See `ti.targets.ITarget.Command`.
     */
    struct Options {
        string prefix;  /*! options that appear before Command.opts */
        string suffix;  /*! options that appear after Command.opts */
    }

    /*!
     *  ======== binDir ========
     *  This parameter controls the location of the target's commands.
     *
     *  All build commands returned within a command set
     *  (`xdc.bld.ITarget.CommandSet.cmds`) are formed by prefixing `binDir`
     *  to this target's Command.cmd specification.  For example, the
     *  compile command returned is formed as follows:
     *  @p(code)
     *      $(binDir)$(cc.cmd)
     *  @p
     *  where, `$(binDir)` is this target's `binDir` value and `$(cc.cmd)` is
     *  the value of this target's `cc.cmd` string.
     *  
     *  If `binDir` is non-empty then it must end with '/'.  If it is empty, 
     *  the target's commands (compiler, linker, archiver, etc.) will be
     *  located along a path constructed from this target's `pathPrefix`.
     */
    config string binDir = "$(rootDir)/bin/";

    /*!
     *  ======== pathPrefix ========
     *  A prefix to the PATH environment variable
     *
     *  Each target command is executed with C_DIR set to "" and PATH
     *  set as follows:
     *  @p(code)
     *      $(pathPrefix);$(binDir);$(PATH)
     *  @p
     *  where, `$(pathPrefix)` and `$(binDir)` are the values of the
     *  configuration parameters and `$(PATH)` is the value of the `PATH`
     *  environment variable set by the `xdc` command (type 'xdc -n' to
     *  see this).
     *
     *  Embedded ';' characters within `pathPrefix` separate directory
     *  names.  On UNIX hosts these ';' characters are convered to an
     *  appropriate separator; i.e., ':'.
     */
    config string pathPrefix = "";
    
    override config String binaryParser = "ti.targets.omf.cof.Coff";

    /*!
     *  ======== debugGen ========
     *  TI Debugger/IDE file generation support.
     *
     *  The settings below generate CCS project files that enable one
     *  to debug (and even rebuild) Executables from within the CCS GUI.
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
     *  Note: if you are using CCS 2.x, disable CodeMaestro to prevent
     *  instabilities when re-loading project files.  CodeMaestro can be
     *  disabled via: Options->"Customize ..."->"CodeMaestro Settings"
     *
     *  To debug an executable:
     *  @p(nlist)
     *      - load generated project for the executable:
     *             package/cfg/<cfg_name>.pjt
     *      - load generated GEL script for the executable:
     *             package/cfg/<cfg_name>.gel
     *      - load prerequisite packages:
     *             GEL->"XDC Package"->open_project
     *  @p
     *  where <cfg_name> is the name of the executable (foo.x62) with the
     *  '.' replaced by and '_' (foo_x62).
     *
     *  Alternatively, one can use the `ccs_start.pl` script in this package
     *  to automate the steps above.  In addition, it is possible to
     *  associate `ccs_start.bat` (also in this package) with the generated 
     *  `.pjt` files to automate the above by double-clicking on the `.pjt`
     *  file.
     *
     *  To avoid navigation to the executable via file menus, you can load
     *  the executable associated with the project via:
     *
     *      GEL->"XDC Package"->load_executable
     *
     *  @a(See Also) `xdc.bld.ITarget` contains addition information about
     *  how to create and use these templates.
     */
    override config xdc.bld.ITarget.DebugGen debugGen = {
        execTemplate   : "ti/targets/ccs_exec.xdt",
        execPattern    : "$(cfgDir)$(cfgName).pjt",
        packageTemplate: "ti/targets/ccs_package.xdt",
        packagePattern : "package/$(pkgName).pjt"
    };
    
    /*!
     *  ======== extensions ========
     *  File extensions recognized by TI targets
     *
     *  @a(TI Specifics)
     *  For TI targets, the `typ` string field of an
     *  `xdc.bld.ITarget.Extension` structure may be of the form
     * `"<cmd>:<langOpt>"` where `<cmd>` is one of `"asm"`, `"c"`, `"cpp"`,
     *  and `<langOpt>` is the language option to used to identify the source
     *  language of a source file.  This allows one to explicitly control the
     *  language flag passed to the compiler based on a source file's
     *  extension; in particular, one can define separate source extensions
     *  for "linear" and "scheduled" assembly files, or simply cause `".s62"`
     *  files to be treated as "linear" assembly rather than "scheduled"
     *  assembly.
     *
     *  For example,
     *  @p(code)
     *  tiTargets.C62.extensions[".s62"] = {suf: ".s62", typ: "asm:-fl"};
     *  @p
     *  causes all `".s62"` files to be treated as linear assembly.
     *
     *  If no ':' appears in the `typ` string, a default will be used:
     *  `"-fa"` for `"asm"` files `"-fc"` for `"c"` files, and `"-fp"` for
     *  `"cpp"` files.
     */
    override config xdc.bld.ITarget.Extension extensions[string] =
        xdc.bld.ITarget.extensions;

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
                copts: "-oe -O2 -mo",
            },
        }],
        ["whole_program_debug", {
            compileOpts: {
                copts: "-oe --symdebug:dwarf -mo",
            },
        }],
    ];

    /*!
     *  ======== versionMap ========
     *  Map of TI compiler version numbers to compatibility keys.
     *
     *  This map translates version string information from the compiler
     *  into a compatibility key.  The compatibility key is used to validate
     *  consistency among a collection of packages used in a configuration.
     *
     *  TI compiler strings are formed by parsing the output of the
     *  compiler's -version option and creating a string of the form:
     *  @p(code)
     *      <comp>_<ver>
     *  @p
     *  where `<comp>` is the first word of the output and `<ver>` is the
     *  version number that appears on this same line.
     *
     *  There are two forms of version numbers output by the TI code gen
     *  tools; an "old" style that is of the form "<major>.<minor>" and a
     *  new style of the form "<major>.<minor>.<update>[.<branch>][<qual>],
     *  where <major>, <minor>, <update>, and <branch> are non-negative
     *  integers and <qual> is of  the form "[IBAP]<yyddd>", and <yyddd>
     *  is the last two digits of the year concatenated with the number of
     *  the day.
     *
     *  If a compiler version is not found in this map the default is
     *  "1,0,<major>.<minor>" for old style version numbers, and
     *  "1,0,<major>.<minor>,<update>[.<branch>][,<yyddd>]" for new style
     *  version numbers.
     *
     *  The user only needs to extend this table when a significant
     *  incompatibility occurs (and this package doesn't know about it) or
     *  when two versions of the compiler should be treated as 100%
     *  compatible.
     *
     *  @a(Examples)
     *  @p(code)
     *      var C62 = xdc.useModule('ti.targets.C62');
     *
     *      // assert that 4.0 is forward compatible with 4.32
     *      C62.versionMap["TMS320C6x_4.32"] =  "1,0,4.0,0";
     *
     *      // assert that 4.28 is incompatible with all other compilers
     *      C62.versionMap["TMS320C6x_4.28"] =  "1,1,4.28,0";
     */
    override config string versionMap[string] = [
        ["TMS320C6x_4.32", "1,0,4.32,0"],
        ["TMS320C55x_2.56", "1,0,2.56,0"],
        ["TMS320C54x_3.83", "1,0,3.83,0"],
        ["TMS320C2000_3.07", "1,0,3.07,0"],
    ];    
    
    /*!
     *  ======== alignDirectiveSupported ========
     *  The compiler supports an align directive.
     */
    override readonly config Bool alignDirectiveSupported = true;
    
    /*!
     *  ======== ar ========
     *  The command used to create an archive
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
     *  ======== ccConfigOpts ========
     *  User configurable compiler options for the generated config C file.
     *
     *  By default, this parameter inherits values specified in ccOpts, by
     *  expanding $(ccOpts.prefix) and $(ccOpts.suffix) into the values
     *  specified in ccOpts for this target.
     */
    config Options ccConfigOpts = {
        prefix: "$(ccOpts.prefix) -mo",
        suffix: "$(ccOpts.suffix)"
    };

    /*!
     *  ======== asm ========
     *  The command used to assembles assembly source files into object files
     */
    readonly config Command asm;

    /*!
     *  ======== asmName ========
     *  The function that converts a C name into an assembly name
     */
    String asmName(String CName);

    /*!
     *  ======== asmOpts ========
     *  User configurable assembler options.
     */
    config Options asmOpts = {
        prefix: "",
        suffix: ""
    };

    /*!
     *  ======== vers ========
     *  The command used to get the tool-chain to return a version number.
     */
    readonly config Command vers;

    /*!
     *  ======== version ========
     *  The Compatibility Key associated with this target.
     *
     *  The first two components of this target Compatibility Key are '1,0'.
     *  The rest of the Key represents the compiler version. The third
     *  component combines the major and the minor version number in the format
     *  Major.Minor. The fourth component is the patch number, and the optional
     *  fifth component is the version of an Alpha or Beta release.
     *
     *  @a(Example)
     *  If this target's `rootDir` points to the compiler version 6.0.11, the 
     *  Compatibility Key is [1,0,6.0,11]. If this target's `rootDir` points to
     *  the compiler version 7.0.0B1, the Compatibility Key is [1,0,7.0,0,1]. 
     *  
     */
    override metaonly config String version;

    /*!
     *  ======== includeOpts ========
     *  Additional user configurable target-specific include path options
     */
    config string includeOpts;
}
/*
 *  @(#) ti.targets; 1, 0, 3,385; 2-24-2010 16:24:15; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

