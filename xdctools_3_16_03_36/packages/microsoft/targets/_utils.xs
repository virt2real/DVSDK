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
 *  ======== targetCmds ========
 *  Hash table of commands (indexed by target.suffix).  Commands are
 *  themselves hashtables (indexed by file type: "asm", "c", ...) that
 *  define the commands for cc, asm , etc.
 */
var targetCmds = null;

/*
 *  ======== targetPath ========
 *  Path environment variable settings required for the compile/link/archive
 *  commands.
 */
var targetPath = null;

var _bldUtils = xdc.module('xdc.bld.Utils');

/*
 *  ======== compile ========
 */
function compile(target, goal, asm)
{
    var result = null;

    this.initTabs();
    
    var tool2cmd = this.targetCmds[target.suffix];  /* get tool to template map */
    
    if (tool2cmd != null) {
        var ext = target.extensions[goal.srcSuffix];
        if (ext != null) {
            if (asm == true && ext.typ == "asm") {
                return (null);
            }

            var result = new xdc.om['xdc.bld.ITarget'].CommandSet;
            result.msg = (ext.typ == "c" ? "cl" : ext.typ)
                            + target.suffix
                            + (asm == true ? " -S $< ..." : " $< ...");
    
            var dstDir = goal.dstPrefix + goal.base;
            dstDir = dstDir.replace(/[^\/\\]*$/, "");
    
            this.setEnv(target, result);
                
            result.cmds = _bldUtils.expandString(tool2cmd[ext.typ], {
                COPTS_P:    target.ccOpts.prefix,
                COPTS_S:    target.ccOpts.suffix,
                AOPTS_P:    target.asmOpts.prefix,
                AOPTS_S:    target.asmOpts.suffix,
                ASMONLY:    asm ? "/Fa$@" : "",
                dstDir:     dstDir,
                srcExt:     goal.srcSuffix,
                copts:      goal.configOpts ? goal.opts.cfgcopts : 
                                              goal.opts.copts,
                aopts:      goal.opts.aopts,
                defs:       goal.opts.defs,
                incs:       goal.opts.incs,
            });
        }
    }
    
    return (result);
}

/*
 *  ======== initTabs ========
 */
function initTabs()
{
    var thisPkg = xdc.om["microsoft.targets"];

    if (targetCmds == null) {
        targetCmds = {};
        targetPath = {};

        /*
         * Loop over all packages in case another package has a module
         * that wants to extend this package's ITarget interface.
         */
        var pa = xdc.om.$packages;
        for (var j = 0; j < pa.length; j++) {
            var ma = pa[j].$modules;
            for (var i = 0; i < ma.length; i++) {
                if (ma[i] instanceof thisPkg.ITarget.Module) {
                    var targ = thisPkg.ITarget.Module(ma[i]);
                    targ.$orig.setPath();
                    mkCmds(targ);
                    mkEnvs(targ);
                }
            }
        }
    }
}

/*
 *  ======== mkCmds ========
 */
function mkCmds(target)
{
    target = target.$orig;
    var tmp, cmd, cmdOpts;
    var tool2cmd = {};
    var prefix = target.cmdPrefix;
    if ("remoteInitScript" in target && target.remoteInitScript != undefined) {
        prefix += target.remoteInitScript + " \\& ";
    }
    
    /* define assemble command template */
    cmdOpts = " $(AOPTS_P) " + target.asm.opts
                + " $(AOPTS_S) $(defs) $(aopts) $(incs) $(XDCINCS) "
                + target.includeOpts + " /Fo$@ $<";
    cmd  = prefix + target.asm.cmd + cmdOpts;
    cmd += "\n$(RM) $@.dep\n$(MKDEP) -a $@.dep -p $(dstDir) -s o"
            + target.suffix + " $< -C " + cmdOpts;

    tool2cmd["asm"] = cmd;
    
    /* define generic C/C++ options */
    var zaFlag = target.strictANSI ? " -Za" : "";
    cmdOpts = " $(COPTS_P) "
                + target.cc.opts
                + " $(COPTS_S) $(defs) $(copts) $(incs) $(XDCINCS) "
                + target.includeOpts;

    mkdep = "$(RM) $@.dep\n$(MKDEP) -a $@.dep -p $(dstDir) -s o"
            + target.suffix + " $< -C " + cmdOpts; 

    /* define the C compile command template */
    cmd = prefix + target.cc.cmd + zaFlag + cmdOpts + " /TC /Fo$@ $(ASMONLY) $<\n";
    cmd += mkdep;
    tool2cmd["c"] = cmd;

    /* define the C++ compile command template */
    cmd = prefix + target.cc.cmd + zaFlag + cmdOpts + " /TP /Fo$@ $(ASMONLY) $<\n";
    cmd += mkdep;
    tool2cmd["cpp"] = cmd;

    /* define the link command template */
    cmd = prefix + target.lnk.cmd
              + " $(LOPTS_P) $(lopts) -out:$@ $(files) " + target.lnk.opts
              + " $(LOPTS_S)\n";
    tool2cmd["link"] = cmd;

    /* define the ar command template */
    cmd  = prefix + target.ar.cmd
                + " $(AROPTS_P) " + target.ar.opts
                + " -out:$@ $(AROPTS_S) $(aropts) $(files)";
    tool2cmd["ar"] = cmd;

    /* add set of command templates to targetCmds */
    targetCmds[target.suffix] = tool2cmd;
}

/*
 *  ======== mkEnvs ========
 */
function mkEnvs(target)
{
    var path = ".;" + target.$orig.setPath() + ";$(PATH)";
    targetPath[target.suffix] = path.split(";");
}

/*
 *  ======== setEnv ========
 */
function setEnv(target, result)
{
    result.envs = ["INCLUDE=", "LIB="];
    result.path = targetPath[target.suffix];
}


/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

