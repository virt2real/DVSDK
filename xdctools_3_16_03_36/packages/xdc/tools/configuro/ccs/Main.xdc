/*
 *  Copyright 2007 by Texas Instruments Incorporated.
 *
 *  All rights reserved. Property of Texas Instruments Incorporated.
 *  Restricted rights to use, duplicate or disclose this code are
 *  granted through contract.
 *
 */

/*!
 *  ======== Main ========
 *  Command-line configuration tool adapter for Code Composer Studio
 *
 *  This command is a wrapper for {@link xdc.tools.configuro Configuro}
 *  that adapts it for use inside Code Composer Studio. It is not
 *  intended to be called directly by users.
 */
metaonly module Main inherits xdc.tools.ICmd {

    /*!
     * usage help message
     */
    override config String usage[] = [
        '[-v|--help]',
        '[-@ optionsfile] [--xp xdcpath]',
        '[-b config_bld | -c codegen_dir | --cb]',
        '[-t target] [-p platform[:instance]] [-r profile]',
        '[-Dname=value] [--tcf] [--bios5]',
        '[-w|-x regexp]',
        '[-o outdir] infile.cfg'
    ];

instance:

    /*!
     * XDC path
     */
    @CommandOption("xp")
    config String xdcPath[] = [];

    /*!
     * name of the text file containing xdc paths
     *
     * @_nodoc
     *
     * Both plain directory listing and javascript syntax are supported; 
     * for javascript, the file must start with double slashes -- "//" -- and 
     * it must define a variable called xdcpaths.
     */
    @CommandOption("xdcpathsfile")
    config String xdcPathsFile = null;        
    
    /*!
     * Process infile.tcf in addition to infile.cfg
     */
    @CommandOption("tcf")
    config Bool hasTconf = false;
    
    /*!
     * Add "include" directory from pacakge "ti.bios" to compiler options
     */
    @CommandOption("bios5")
    config Bool bios5Incs = false;

    /*!
     * name of the output directory
     */
    @CommandOption("o")
    config String output = null;

    /*!
     * config.bld file name
     *
     * The path to the user's config.bld. Replaces ROOTDIR.
     */
    @CommandOption("b")
    config String configbld = null;

    /*!
     * Use a config.bld found along the package path
     */
    @CommandOption("cb")

    config Bool searchForConfigBld = false;
    /*!
     * target module
     *
     * The name of an XDC build target module to use, for example
     * `ti.targets.C64P`. If no target is named, the target used is
     * `Build.targets[0]`, from `config.bld`.
     */
    @CommandOption("t")
    config String target = null;

    /*!
     * build profile to use
     *
     * The name of the build profile to use for the XDC content, for
     * example 'release' or 'debug'. The list of allowed profiles is
     * determined by the XDC build target named.
     */
    @CommandOption("r")
    config String profile = 'release';

    /*!
     * the platform to use
     *
     * If undefined, the default platform for the XDC build target
     * named.
     */
    @CommandOption("p")
    config String platform = null;

    /*!
     * root directory of the code generation tools
     *
     * The path to the installation directory of the compiler and linker.
     */
    @CommandOption("c")
    config String rootdir = null;

    /*!
     * show details during build
     */
    @CommandOption("v")
    config Bool verbose = false;

    /*!
     * exclude packages from compatibility checking
     *
     * A list of regular expressions used to select packages that should
     * be excluded from the set of packages checked during configuration.
     * @see xdc.cfg
     */
    @CommandOption("x")
    config String exclude = null;

    /*!
     * incompatibilites are treated only as warnings
     *
     * If set to "`true`", force any incompatibilities detected to be
     * treated as warnings only; otherwise incompatibilities are fatal.
     * @see xdc.cfg
     */
    @CommandOption("w")
    config Bool warn = false;

    /*!
     * set Java properties in the configuration environment
     *
     * -Dconfig.importPath is treated specially -- these directories are
     * added to the end of the package path.
     */
    @CommandOption("D")
    config String defines[] = [];
    
    /*!
     * Generate and build the configuration package.
     */
    int gen(String infile);
}
/*
 *  @(#) xdc.tools.configuro.ccs; 1, 0, 0, 0,34; 12-15-2007 18:23:21; /db/ztree/library/trees/bti-a52x/src/
 */

