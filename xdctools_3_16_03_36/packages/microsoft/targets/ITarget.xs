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

/*
 *  ======== _bldUtils ========
 */
var _bldUtils = xdc.module('xdc.bld.Utils');
var _utils = xdc.loadCapsule('microsoft/targets/_utils.xs');

/*
 *  ======== ITarget.archive ========
 */
function archive(goal)
{
    var target = this;

    _utils.initTabs();

    var result = null;
    var tool2cmd = _utils.targetCmds[target.suffix];
    
    if (tool2cmd != null) {
        result = new xdc.om['xdc.bld.ITarget'].CommandSet;
        result.msg = "archiving " + goal.files + " into $@ ...";
        _utils.setEnv(target, result);
        result.cmds = _bldUtils.expandString(tool2cmd["ar"], {
            AROPTS_P:   target.arOpts.prefix,
            AROPTS_S:   target.arOpts.suffix,
            aropts:     goal.opts,
            files:      goal.files,
        });
    }

    return (result);
}

/*
 *  ======== ITarget.compile ========
 */
function compile(goal) {
    return (_utils.compile(this, goal, false));
}

/*
 *  ======== ITarget.getVersion ========
 */
function getVersion()
{
    var target = this;

    if (target.$private._version != null) {
        return (target.$private._version);
    }

    _utils.initTabs();

    var result = target.$name + "{";

    /* the command to get the version is the first word of the cl command */
    var tool2cmd = _utils.targetCmds[target.suffix];
    
    var cmd = _bldUtils.expandString(tool2cmd["c"], {
        rootDir:        target.rootDir,
        compilerDir: target.$private._compilerDir
    })
    
    /* At this moment, cmd is a long string that contains cmdPrefix and the
     * complete compiler command line with all options and MKDEP command.
     * This complex match is used to split that command line into tokens,
     * separated by spaces, but ignoring spaces within quotes.
     */
    var cmdTokens = cmd.match(/(?:[^\s'"]+|(['"])[^'"]*\1)+/g);

    var cmd = cmdTokens[0];
    /* If there is no cmdPrefix, cmd now contains only the path to the
     * compiler executable. Otherwise, it contains the first token of the
     * cmdPrefix, which can be either remote script or an environment
     * variable that needs to be set for that script.
     */

    var prefEnv = [];
    if (target.cmdPrefix != null && target.cmdPrefix != "") {
        /* If there is cmdPrefix, we first extract optional environment
         * variables from cmdPrefix. The settings have to be extracted first,
         * and put in 'envs' because that's the only way xdc.exec can process
         * them.
         * Since we are using the same regular expression as above, the tokens
         * in prefTokens are the same as the tokens at the head of cmdTokens.
         */
        var prefTokens = target.cmdPrefix.match
            (/(?:[^\s'"]+|(['"])[^'"]*\1)+/g);

        /* cmd will now contain the last entry in prefTokens, which is the
         * remote execution command. Now, we need to add an optional remote init
         * script and then add the path to the compiler executable.
         */
        cmd = prefTokens[prefTokens.length - 1] + " ";
        var compLine = prefTokens.length;
        
        if ("remoteInitScript" in target
            && target.remoteInitScript != undefined) {
            cmd += cmdTokens[compLine++] + " "; 
            cmd += cmdTokens[compLine++] + " "; 
        }

        cmd += cmdTokens[compLine];
        if (prefTokens.length > 1) {
            for (var i = 0; i < prefTokens.length - 1; i++) {
                prefEnv.push(prefTokens[i]);
            }
        }
    }
    
    /* Check if rootDir is set correctly, but only if cmdPrefix is not 
     * specified. If it is, we are going somewhere else for the execution,
     * and the file system might look different.
     */
    var file = new java.io.File(target.rootDir);
    if (target.cmdPrefix == null && !file.exists()) {
        throw new Error(target.rootDir + " cannot be found. Ensure that" +
            " rootDir for the " + target.name + " target is set correctly in " +
            java.lang.System.getenv("XDCBUILDCFG"));
    }

    /* must set path so Windows can find DLLs such as mspdb70.dll */
    var path = _bldUtils.expandString(".;" + target.$orig.setPath(), {
            rootDir: target.rootDir,
            compilerDir: target.$private._compilerDir});

    var attrs = {
        envs: prefEnv.concat(["PATH=" + path, "Path=" + path, "TERM=dumb"]),
        useEnv: true
    }

    var status = {};
    if (xdc.exec(cmd, attrs, status) >= 0) {
        var va = status.output.match(/Version\s+[0-9\.]+/mg);
        if (va != null) {
            var cver = va[0].replace(/[Version\s]/g, "");
            var key = target.versionMap["cl_" + cver];
            if (key == null) {
//                  print(target.$name + " can't find 'cl_" + cver + "'");
                /* MS version numbers are x.y.z, where z is a build number */
                key = "1,0," +
                    cver.replace(/([0-9]+\.[0-9]+)\.([0-9]+).*/, "$1,$2");
            }
            result += key;
        }
        else {
            print("microsoft.targets: warning: version match failed on '"
                + status.output + "'");
        }
    }
    else {
        print("microsoft.targets: warning: exec of: '" + cmd + "' failed");
        $trace(status.output, 0);
    }

    target.$private._version = result;  /* cache result for later use */
    
    return (result);
}

/*
 *  ======== ITarget.link ========
 */
function link(goal)
{
    var target = this;
    _utils.initTabs();

    var result = null;
    var tool2cmd = _utils.targetCmds[target.suffix];

    if (tool2cmd != null) {
        result = new xdc.om['xdc.bld.ITarget'].CommandSet;
        result.msg = "lnk" + target.suffix + " $@ ...";

        var fileList = goal.files.replace(/(^|\s+)([\/\w\\\.]+\.xdl)($|\s+)/,
                                          " @$2 ");
        
        _utils.setEnv(target, result);
            
        var dllOpts = "-dll -map:$(XDCCFGDIR)/$@.map -mapinfo:exports ";

        result.cmds = _bldUtils.expandString(tool2cmd["link"], {
            LOPTS_P:    target.lnkOpts == null ? "" : target.lnkOpts.prefix,
            LOPTS_S:    target.lnkOpts == null ? "" : (goal.dllMode ? dllOpts : "") + target.lnkOpts.suffix,
            lopts:      goal.opts,
            files:      fileList,
        });

        if (goal.dllMode) {
            var ext = (this.dllExt != null) ? this.dllExt : ".p";
            result.cmds += "$(MV) $(basename $@).exp $(XDCCFGDIR)/$(basename $@)"
                + ext + target.suffix + ".exp\n";
            result.cmds += "$(MV) $(basename $@).lib $(XDCCFGDIR)/$(basename $@)"
                + ext + target.suffix + ".lib\n";
        }
    }

    return (result);
}

/*
 *  ======== ITarget.scompile ========
 */
function scompile(goal) {
    return (_utils.compile(this, goal, true));
}

    
/*
 *  ======== setPath ========
 *
 *  Default implementation of setPath().
 */
function setPath()
{
    if ("path" in this.$orig) {
        return (this.$orig.path);
    }
    else {
        return "";
    }
}
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

