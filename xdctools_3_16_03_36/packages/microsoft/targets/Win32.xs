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
var compDirReplaced = false;
var utils = xdc.loadCapsule('microsoft/targets/_utils.xs');

/*
 *  ======== Win32.archive ========
 */
function archive(goal)
{
    if (!compDirReplaced) {
        this.setPath(); 
    }
    return (this.$super.archive.$fxn.call(this, goal));
}

/*
 *  ======== Win32.compile ========
 */
function compile(goal) {
    if (!compDirReplaced) {
        this.setPath(); 
    }
    return (utils.compile(this, goal, false));
}

/*
 *  ======== Win32.getVersion ========
 */
function getVersion()
{
    if (!compDirReplaced) {
        this.setPath(); 
    }
    return (this.$super.getVersion.$fxn.call(this));
}

/*
 *  ======== Win32.link ========
 */
function link(goal) {
    if (!compDirReplaced) {
        this.setPath(); 
    }
    var result = this.$super.link.$fxn.call(this, goal);
    if (this.$private._vcVersion == "VC8" && this.cmdPrefix == "") {
        /* VC8.0 programs require manifests and linker create them as 
         * separate files. Since manifests are always required, and they
         * have to be in the same directory as programs, we use mt to
         * embed them into programs. However, it doesn't work for wine for now
         * because of missing Net Framework.
         */
        result.cmds += this.cmdPrefix + "$(rootDir)/VC/bin/mt -nologo -manifest $@.manifest -outputresource:'$@;#1'\n";
        result.cmds += "-$(RM) $@.manifest\n"; 
    }
    return (result);
}

/*
 *  ======== Win32.scompile ========
 */
function scompile(goal) {
    if (!compDirReplaced) {
        this.setPath(); 
    }
    return (utils.compile(this, goal, true));
}


/*
 *  ======== Win32.setPath ========
 */
function setPath()
{
    if (this.$private._path != undefined) {
        return (this.$private._path);
    }

    this.$private._path = "";

    if (this.rootDir != undefined) {
        /* Different versions of Visual Studio install DLLs required by
         * compiler in different directories. Here we go through vcPath
         * table looking for the directories that can be found in rootDir.
         */
        for (var vcVersion in this.vcPath) {
            var file = new java.io.File(this.rootDir + "/" +
                                        this.vcPath[vcVersion].compilerDir);
            if (file.exists()) {
                var dllPathComps = this.vcPath[vcVersion].dllPath.split(';');
              
                this.$private._path = this.rootDir + "/" +
                this.vcPath[vcVersion].compilerDir + "/bin";
                for (var j = 0; j < dllPathComps.length; j++) {
                    this.$private._path += ";" + this.rootDir + "/" +
                        dllPathComps[j];
                }
                this.$private._compilerDir = this.vcPath[vcVersion].compilerDir;
                this.$private._vcVersion = vcVersion;
                
                /* Find out if sdkPath is absolute or relative. If it's
                 * relative, add rootDir to is, otherwise use it as it is.
                 */
                var spath = new java.io.File(this.vcPath[vcVersion].sdkPath);
                if (spath.isAbsolute()) {
                this.$private._sdkPath = this.vcPath[vcVersion].sdkPath;
                }
                else {
                    this.$private._sdkPath = this.rootDir + "/" +
                        this.vcPath[vcVersion].sdkPath; 
                }
                
                /* Check if sdkPath actually exists, but only if it's not
                 * empty.
                 */
                if (this.vcPath[vcVersion].sdkPath != "") {
                    var sdk = new java.io.File(this.$private._sdkPath);
                    if (!sdk.exists()) {
                        throw new Error("The Platform SDK path " + 
                        this.$private._sdkPath + " could not be found." +
                "Ensure SDK path is specified correctly in " + java.lang.System.getenv("XDCBUILDCFG"));
                    }   
                }
                
                this.$private._libs = this.vcPath[vcVersion].libs;
                break;
            }
        }

        if (this.$private._path == "") {
            throw new Error("No compiler directories from vcPath table " +
            "could be found in " + this.rootDir + ". Ensure that the " +
            "parameter rootDir for the " + this.name + " target is set " +
            "correctly in " + java.lang.System.getenv("XDCBUILDCFG"));
        }
    }
    _initCmds();
    return (this.$private._path);
}

/*
 *  ======== Win32._initCmds ========
 *  Commands for Win32 target contain $(compilerDir) variable that needs to be
 *  replaced with the actual path to the compiler directory.
 */
function _initCmds()
{
    var target = xdc.module("microsoft.targets.Win32");

    var compDir = target.$private._compilerDir;
    var platDir = target.$private._sdkPath;

    function _replace(arg)
    {
        var Utils = xdc.module('xdc.bld.Utils');
        for (var prop in arg) {
            if (typeof(arg[prop]) == "object") {
                _replace(arg[prop]);
            }
            else if (typeof(arg[prop]) == "string") {
                arg[prop] = Utils.expandString(arg[prop], {
                    compilerDir: compDir,
                    sdkPath: platDir
                });
            }
        }
    }

    target.$unseal();

    _replace(target);

    for (var i = 0; i < target.profiles.length; i++) {
        target.profiles[i].linkOpts += target.$private._libs;
    }

    target.$seal();
    compDirReplaced = true;
}

/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

