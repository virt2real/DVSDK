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
var debug;
if (debug == null) {
    debug = function (msg) {};
}

var _bldUtils = xdc.useModule('xdc.bld.Utils');

/*
 *  ======== _targetCmds ========
 *  Hash table of commands (indexed by target.suffix).  Commands are
 *  themselves hashtables (indexed by file type: "asm", "c", ...) that
 *  define the commands for cc, asm , etc.
 */
var _targetCmds = null;

/*
 *  ======== _targetEnvs ========
 *  Environment variable settings required for the compile/link/archive
 *  commands.
 */
var _targetEnvs = "LD_LIBRARY_PATH=";

/*
 *  ======== _thisPkg ========
 *  This variable is initialized by this package's init method to the
 *  package containing this file.  We use this in lieu of hard coding
 *  this package's name in this file.
 */
var _thisPkg = null;

/*
 *  ======== ITarget.archive ========
 */
function archive(goal)
{
    var target = this;
    _initTab(target);

    var result = null;
    var tool2cmd = _targetCmds[target.suffix];

    if (tool2cmd != null) {
        result = new xdc.om['xdc.bld'].ITarget.CommandSet;
        result.msg = "archiving " + goal.files + " into $@ ...";
        result.envs = _targetEnvs.split("\n");
        result.cmds = _bldUtils.expandString(tool2cmd["ar"], {
            AROPTS_P:   target.arOpts.prefix,
            AROPTS_S:   target.arOpts.suffix,
            GCCVERS:    target.GCCVERS,
            GCCTARG:    target.GCCTARG,
            LONGNAME:   target.LONGNAME,
            aropts:     goal.opts,
            files:      goal.files
        });
    }

    return (result);
}

/*
 *  ======== ITarget.compile ========
 */
function compile(goal) {
    return (_compile(this, goal, false));
}

/*
 *  ======== ITarget.link ========
 */
function link(goal)
{
    var target = this;
    _initTab(target);
    
    var result = null;
    var tool2cmd = _targetCmds[target.suffix];
    var fileList = target.noStdLinkScript
        ? goal.files.replace(/(^|\s+)([\/\w\\\.]+\.xdl)($|\s+)/, " -T $2 ")
        : goal.files;

    if (tool2cmd != null) {
        result = new xdc.om['xdc.bld'].ITarget.CommandSet;
        result.msg = "lnk" + target.suffix + " $@ ...";
        result.envs = _targetEnvs.split("\n");
        result.cmds = _bldUtils.expandString(tool2cmd["link"], {
            LOPTS_P:    target.lnkOpts == null ? "" : target.lnkOpts.prefix,
            LOPTS_S:    target.lnkOpts == null ? "" : target.lnkOpts.suffix,
            GCCVERS:    target.GCCVERS,
            GCCTARG:    target.GCCTARG,
            LONGNAME:   target.LONGNAME,
            lopts:      goal.opts,
            files:      fileList
        });
    }

    return (result);
}

/*
 *  ======== ITarget.getVersion ========
 */
function getVersion()
{
    var target = this;
    
    _initTab(target);

    var result = target.$name + "{";
    var key;

    if ((key = target.versionMap["gcc" + target.GCCVERS]) == null) {
        /* map 2.3.4 to "1,0,2.3,4", 2.3 to "1,0,2.3", and 2 to "1,0,2" */
        key = "1,0";
        var va = target.GCCVERS.split('.');
        for (var i = 0; i < va.length; i++) {
            key += (i == 1 ? '.' : ',') + va[i];
        }
    }
    result += key;

    return (result);
}

/*
 *  ======== ITarget.scompile ========
 */
function scompile(goal) {
    return (_compile(this, goal, true));
}

/*
 *  ======== _compile ========
 */
function _compile(target, goal, asm)
{
    var result = null;

    _initTab(target);

    var tool2cmd = _targetCmds[target.suffix];  /* get tool to template map */
    
    if (tool2cmd != null) {
        var ext = target.extensions[goal.srcSuffix];
        if (ext != null) {
            if (asm == true && ext.typ == "asm") {
                return (null);
            }

            result = new xdc.om['xdc.bld'].ITarget.CommandSet;
            result.msg = (ext.typ == "c" ? "cl" : ext.typ)
                            + target.suffix
                            + (asm == true ? " -S $< ..." : " $< ...");
    
            var dstDir = goal.dstPrefix + goal.base;
            dstDir = dstDir.replace(/[^\/\\]*$/, "");
    
            result.envs = _targetEnvs.split("\n");
    
            result.cmds = _bldUtils.expandString(tool2cmd[ext.typ], {
                COPTS_P:    target.ccOpts.prefix,
                COPTS_S:    target.ccOpts.suffix,
                AOPTS_P:    target.asmOpts.prefix,
                AOPTS_S:    target.asmOpts.suffix,
                GCCVERS:    target.GCCVERS,
                GCCTARG:    target.GCCTARG,
                LONGNAME:   target.LONGNAME,
                ASMONLY:    asm ? "-S" : "",
                dstDir:     dstDir,
                srcExt:     goal.srcSuffix,
                copts:      goal.configOpts ? goal.opts.cfgcopts : 
                                              goal.opts.copts,
                aopts:      goal.opts.aopts,
                defs:       goal.opts.defs,
                incs:       goal.opts.incs
            });
        }
    }
    
    return (result);
}

/*
 *  ======== _init ========
 *  Initialize this capsule at package init time.
 */
function _init(pkg)
{
    _thisPkg = pkg;
}

/*
 *  ======== _initTab ========
 *  Check if the target command map is already initialized, and if not 
 *  initialize it.
 */
function _initTab(target)
{
    if (_targetCmds == null) {
        _targetCmds = {};
    }

    if (_targetCmds[target.suffix] == undefined) {
        _initVers(target);
        _mkCmds(target);
    }
}

/*
 *  ======== _initVers ========
 *  Initialize target.GCCVERS and target.GCCTARG if they are not already
 *  initialized by a previous call to _initVers() or by the user via
 *  the config.bld script.
 */
function _initVers(target)
{
    if (target.$private.vers == true || target.rootDir == null) {
        return;
    }

    target.$private.crossCompiler = false;    
    if (target.LONGNAME == null) {
        throw new Packages.xdc.services.global.XDCException(
            "gnu.targets.UNDEFINED_EXECUTABLE",
            "'LONGNAME' must be defined for the target " + target.$name);
    }

//    print("getting version for target " + target.$name);
    
    var prefix = "";
    if (target.remoteHost != null) {
        prefix = target.$package.packageBase
            + "/runh -h " + target.remoteHost + " ";
    }
    else if ("cmdPrefix" in target.$orig
             && target.$orig.cmdPrefix != undefined) {
        prefix = target.$orig.cmdPrefix;
    }

    function askGcc(target, opt, filter)
    {
        var gccCmd = target.rootDir + "/" + target.LONGNAME;
        
        /* If the gcc executable cannot be found, and the prefix is not used,
         * it's probably a misspelled directory path.
         */
        if (prefix == "") {
            var file = new java.io.File(gccCmd);
            if (!file.exists()
                && !(new java.io.File(gccCmd + ".exe").exists())) {
                throw new Error(gccCmd + " cannot be found. Ensure" +
                " that rootDir for the " + target.name + " target is set " +
                "correctly in " + java.lang.System.getenv("XDCBUILDCFG"));
            }
        }
    
        var cmd = prefix + gccCmd + " " + opt;
        var status = {};
        var attrs = {useEnv: true};
                
        if (xdc.exec(cmd, attrs, status) >= 0) {
            var va = status.output.match(filter);
            if (va != null) {
                return (va[0]);
            }
            else {
                print(target.$name + ": warning: failed to parse '"
                    + opt + "' output (= '" + status.output + "')"+
           "; check compiler options");
            }
        }
        else {
            print(target.$name + ": warning: exec of '" + cmd + "' failed:"
                + status.output + "; check tools installation");
        }

        return ("");
    }

    target.$unseal("GCCVERS");
    target.$unseal("GCCTARG");

//      print("setting " + target.$name + ".GCCVERS and .GCCTARG to ''");

    /* BUG: we should compare against target's tool-chain os */
    if (target.GCCTARG != null && target.GCCVERS != null) {
        return;
    }

    /* call compiler to get its version number and set GCCVERS */
    var result;
    if (target.GCCVERS == null) {
        if ((result = askGcc(target, "-dumpversion", /^[\d\.]+/)) == "") {
            print(target.$name + ": warning: can't determine gcc version; ");
            print("Check if " + target.rootDir + "/bin/gcc can run on ");
            if (target.remoteHost != null) {
                print(target.remoteHost + ". ");
            }
            else {
                print(xdc.om['xdc.bld'].BuildEnvironment.hostOSName + ". ");
            }
            print("Also, try explicitly setting the GCCVERS configuration "
                + "parameter.");
        }
//      print("setting " + target.$name + ".GCCVERS to " + result);
        target.GCCVERS = result;
    }

    /* call compiler to get its target machine and set GCCTARG */
    if (target.GCCTARG == null) {
        if ((result = askGcc(target, "-dumpmachine", /^[\w-\.]+/)) == "") {
            print(target.$name + ": warning: can't determine gcc target; ");
            print("Check if " + target.rootDir + "/bin/gcc can run on ");
            if (target.remoteHost != null) {
                print(target.remoteHost + ". ");
            }
            else {
                print(xdc.om['xdc.bld'].BuildEnvironment.hostOSName + ". ");
            }
            print("Also, try explicitly setting the GCCTARG configuration "
                + "parameter.");
        }
//      print("setting " + target.$name + ".GCCTARG to " + result);
        target.GCCTARG = result;
    }

    target.$seal("GCCVERS");
    target.$seal("GCCTARG");

    target.$private.vers = true;
}

/*
 *  ======== _mkCmds ========
 */
function _mkCmds(target)
{
    var cmd, cmdOpts;
    var tool2cmd = {};
    
    var prefix = "";
    var ccCmd = target.cc.cmd;
    if (target.remoteHost != null) {
        prefix = "$(packageBase)/runh -h " + target.remoteHost + " ";

        /* it is not sufficient to simply overwrite the .dep file; network
         * filesystem latencies can result in file corruption
         */
        ccCmd = ccCmd.replace("-MD -MF $@.dep", "");
    }
    else if ("cmdPrefix" in target.$orig && target.$orig.cmdPrefix != undefined) {
        prefix = target.$orig.cmdPrefix;

        /* it is not sufficient to simply overwrite the .dep file; network
         * filesystem latencies can result in file corruption
         */
        ccCmd = ccCmd.replace("-MD -MF $@.dep", "");
    }

    var mkdep = null;
    if (target.remoteHost != null || target.name == "Mingw" ||
        (environment["xdc.hostOS"] == "Windows" && target.CYGWIN == true)) {
        /* make dependencies command; we compute this rather than adding
         * "-MD -MF $@.dep" to the command line to ensure that dependency file
         * names are local.  If the names are computed remotely we run the
         * risk that non-existent files will constantly trigger unnecessary
         * rebuilds.  We also need to do this for cygwin environments because
         * we are using a natively built GNU make which does not understand
         * cygwin file names.
         */
        mkdep = "\n$(MKDEP) -o $@.dep -p $(dstDir) -s o"
            + target.suffix + " $< -C ";
    }
            
    /* define assemble command template */
    cmdOpts = " $(AOPTS_P) "
        + target.asm.opts
        + " $(AOPTS_S) $(defs) $(aopts) $(incs) $(XDCINCS) "
        + target.includeOpts;
    cmd  = prefix + target.asm.cmd + cmdOpts + " -o $@ $<";
    cmd = mkdep == null ? cmd : cmd.concat(mkdep + cmdOpts);
    tool2cmd["asm"] = cmd;

    /* define the C compile command template */
    cmdOpts = "$(COPTS_P) " + target.cc.opts
        + " $(COPTS_S) $(defs) $(copts) $(incs) $(XDCINCS) "
        + target.includeOpts;
    cmd = prefix + ccCmd
        + " -x c $(ASMONLY) " + cmdOpts + " -o $@ $<";
    tool2cmd["c"] = mkdep == null ? cmd : cmd.concat(mkdep + cmdOpts);

    /* define the C++ compile command template */
    cmd = prefix + ccCmd
        + " -x c++ $(ASMONLY) " + cmdOpts + " -o $@ $<";
    tool2cmd["cpp"] = mkdep == null ? cmd : cmd.concat(mkdep + cmdOpts);

    /* define the link command template */
    cmd = prefix + target.lnk.cmd
        + " $(LOPTS_P) $(lopts) -o $@ $(files) " + target.lnk.opts
        + " $(LOPTS_S)\n";
    tool2cmd["link"] = cmd;

    /* define the ar command template */
    cmd  = prefix + target.ar.cmd
        + " $(AROPTS_P) " + target.ar.opts
        + " $@ $(AROPTS_S) $(aropts) $(files)";
    tool2cmd["ar"] = cmd;

    /* add command template set to _targetCmds */
    _targetCmds[target.suffix] = tool2cmd;
}
/*
 *  @(#) gnu.targets; 1, 0, 1,387; 2-24-2010 16:24:01; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

