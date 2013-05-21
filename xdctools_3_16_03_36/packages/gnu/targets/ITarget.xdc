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
 *  ======== gnu.targets.ITarget ========
 *  Interface to GCC compatible compilers
 */
@TargetHeader("xdc/bld/stddefs.xdt")
metaonly interface ITarget inherits xdc.bld.ITarget {

    override readonly config string stdInclude = "gnu/targets/std.h";
    override config string dllExt     = ".so";

    /*!
     *  ======== GCCVERS ========
     *  Version number of the GCC compiler; e.g., "3.2".
     *
     *  This string can be supplied by the user, otherwise it is obtained
     *  by running "gcc -dumpversion".
     */
    config string GCCVERS = null;

    /*!
     *  ======== version ========
     *  The Compatibility Key associated with this target.
     *
     *  The first two components of this target's Compatibility Key are '1,0'.
     *  The rest of the Key represents the compiler version. The third
     *  component combines the major and the minor version number in the format
     *  Major.Minor. The fourth component is the patch number.
     *
     *  @a(Example)
     *  If this target's `rootDir` points to the compiler version 3.4.6, the 
     *  Compatibility Key is [1,0,3.4,6].
     *  
     */
    override metaonly config String version;

    /*!
     *  ======== GCCTARG ========
     *  The name of the platform executing programs produced by this target
     *
     *  This string can be supplied by the user, otherwise is is obtained
     *  from the compiler and follows the GNU standard format
     *  (<cpu>-<manufacturer>-<os> or <cpu>-<manufacturer>-<kernel>-<os>);
     *  e.g., "sparc-sun-solaris2.6" or "i586-pc-linux-gnu".
     *
     *  When building a GCC compiler, there are three different execution
     *  platforms to consider: the platform used to "build" the compiler, the
     *  "host" platform that runs the compiler, and the "target" platform
     *  that runs the executables produced by the compiler. All three
     *  platforms are identified using a
     *  {@link http://sources.redhat.com/autobook/autobook/autobook_17.html configuration name}
     *  defined by GNU Autotools.  `GCCTARG` is the name of the "target"
     *  platform.
     */
    config string GCCTARG = null;

    /*!
     *  ======== LONGNAME ========
     *  The "long name" of the gcc compiler
     *
     *  This name is used (in conjunction with rootDir) to find the compiler
     *  and linker for this target. The format of `LONGNAME` is always
     *  "/bin/<machine>-gcc". For majority of the targets, the default value
     *  for `LONGNAME` does not ever need to be changed. But, there are
     *  targets where the different but compatible compilers may have
     *  different `LONGNAME` parameters. For such targets and compilers,
     *  `LONGNAME` can be set in `config.bld`.
     *
     *  @a(Example)
     *  If a version 2007q3 of the CodeSourcery GNU toolchain for Arm is
     *  installed in C:/CodeSourcery/arm-2007q3, the following settings in
     *  `config.bld` configure `gnu.targets.arm.GCArmv6` target to use that
     *  toolchain:
     *  @p(code)
     *  var GCArmv6 = xdc.module("gnu.targets.arm.GCArmv6");
     *  GCArmv6.rootDir = "C:/CodeSourcery/arm-2007q3"; 
     *  GCArmv6.LONGNAME = "bin/arm-none-linux-gnueabi-gcc";
     *  @p
     *
     */
    config string LONGNAME = "/bin/gcc";
    
    /*!
     *  ======== CYGWIN ========
     *  Is the target's compiler a cygwin executable
     *
     *  Since file names produced by cygin-based tools differ from the
     *  names understood by other Windows executables, it is important
     *  to avoid using the names output by cygwin tools as input to
     *  non-cygwin programs.  This property tells the target whether
     *  or not it's possible to use the output from `gcc -MD -MF`, for
     *  example.
     */
    readonly config Bool CYGWIN = false;
    
    /*!
     *  ======== noStdLinkScript ========
     *  Don't use the standard linker script
     *
     *  If `true`, add a `-T` flag before the generated `package/cfg/*.xdl`
     *  file passed to the linker.  This flag suppresses use of the
     *  standard linker script implicit in the GCC flow, which effectively
     *  says the generated `.xdl` file assumes total control for all
     *  `MEMORY` and `SECTION` directives.
     *
     */
    config Bool noStdLinkScript = false;
    
    /*
     *  ======== profiles ========
     */
    override config xdc.bld.ITarget.OptionSet profiles[string] = [
        ["debug", {
            compileOpts: {
                copts: "-g",
                defs:  "-D_DEBUG_=1",
            },
            linkOpts: "-g",
        }],

        ["release", {
            compileOpts: {
                copts: "-O2",
            },
            linkOpts: "",
        }],

        ["profile", {
            compileOpts: {
                copts: "-g -pg",
            },
            linkOpts: "-pg"     /* can't use -static here */
        }],

        ["coverage", {
            compileOpts: {
                copts: "-fprofile-arcs -ftest-coverage",
            },
            linkOpts: "-fprofile-arcs -ftest-coverage",
        }],
    ];

    /*!
     *  ======== versionMap ========
     *  Map of GCC compiler version numbers to compatibility keys.
     *
     *  This map translates version string information from the compiler
     *  into a compatibility key.  The compatibilty key is used to
     *  validate consistency among a collection of packages used in
     *  a configuration.
     *
     *  The compiler version string is "gcc<ver>", where <ver> is
     *  GCCVERS.
     *
     *  If a compiler version is not found in this map the default is
     *  "1,0,<ver>", where <ver> is the compiler version number.  Thus,
     *  the user only needs to extend this table when a significant
     *  incompatibility occurs or when two versions of the compiler should
     *  be treated as 100% compatible.
     */
    override config string versionMap[string] = [
        ["gcc3.2", "1,0,3.2,0"],
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
     *  See ti.targets.ITarget.Command.
     */
    struct Options {
        string prefix;  /*! options that appear before Command.opts */
        string suffix;  /*! options that appear after Command.opts */
    }

    /*!
     *  ======== remoteHost ========
     *  Remote host used to run compiler, linker, and archiver tools
     *
     *  If `remoteHost` is `null` (or `undefined`), the configured compiler
     *  is run locally; otherwise, `remoteHost` is taken to be the host name
     *  of the machine that that should be used to run the specified compiler.
     *
     *  All target commands are prefixed with a command that uses `rsh` to run
     *  the commands on the specified host.  Thus, in order to use this
     *  setting, the remote machine must be support `rsh` and the user must 
     *  have permission to run commands from the local machine on the remote 
     *  host named `remoteHost`.  This usually involves adding a line to the 
     *  user's `~/.rhosts` file on the remote machine of the form:
     *  @p(code)
     *      local-machine-name user-name
     *  @p
     *  where `local-machine-name` is the name of the local machine and
     * `user-name` is the user's login name on the local machine.
     */
    config string remoteHost;
    
    /*!
     *  ======== ar ========
     *  The command used to create an archive
     */
    readonly config Command ar = {
        cmd: "$(rootDir)/$(GCCTARG)/bin/ar",
        opts: "cr"
    };

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
    readonly config Command lnk = {
        cmd: "$(rootDir)/$(LONGNAME)",
        opts: ""
    };

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
    readonly config Command cc = {
        cmd: "$(rootDir)/$(LONGNAME) -c -MD -MF $@.dep",
        opts: ""
    };

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
    readonly config Command asm = {
        cmd: "$(rootDir)/$(LONGNAME) -c -x assembler",
        opts: ""
    };

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
    config string includeOpts = "";
}
/*
 *  @(#) gnu.targets; 1, 0, 1,387; 2-24-2010 16:24:01; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

