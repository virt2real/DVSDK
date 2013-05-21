/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*
 *  ======== xs.js ========
 *
 *! Revision History
 *! ================
 *! 03-Sep-2008 sasha	removed redundant setting of xdc.path (CQ25861)
 *! 19-Feb-2008 sasha	fixed CQ23793
 */

/* necessary to bootstrap!!! */
addJars(environment['xdc.root'] + '/packages/xdc/services/intern/cmd/java');
addJars(environment['xdc.root'] + '/packages/xdc/services/intern/gen/java');
addJars(environment['xdc.root'] + '/packages/xdc/services/spec/java');  
                
/* Set up the xdc root object using default xdc.path. Inside xdc/xdc.tci
 * there are calls to xdc.services.global.Env class, where the package path is
 * being set.
 */
utils.loadCapsule('xdc/xdc.tci');
                
/* if we're in a package, define this as the current package */
var file = new java.io.File('./package.xdc');
if (file.exists()) {
    var scan = new Packages.xdc.services.intern.cmd.Scan(xdc.$$private.Env);
    var _pkgname = "" + scan.read("package.xdc", false);
    xdc.$$private.Env.setCurPkgBase('.', _pkgname);
}
else {
    xdc.$$private.Env.setCurPkgRoot('');
}

environment["xdc.rootDir"] = environment["config.rootDir"];

/* om2.xs capsule accesses xdc.global assuming it's the top-level scope,
 * while xdc.tci sets xdc.global to the local scope of the capsule.
 */
xdc.global = this;
                
xdc.loadCapsule('xdc/om2.xs');

var Trace = xdc.module('xdc.services.global.Trace');
if (environment['xdc.traceLevel']) {
    Trace.setLevel(parseInt(environment['xdc.traceLevel'].toString()));      
}
if (environment['xdc.traceCapsules']) {
    Trace.capsuleEnable(environment['xdc.traceCapsules'].split(";"));	
}
if (environment['xdc.tracePackages']) {
    Trace.packageEnable(environment['xdc.tracePackages'].split(";"));	
}
var previousGroups = [];
if (environment['xdc.traceGroups']) {
    previousGroups = environment['xdc.traceGroups'].split(";");
    Trace.groupEnable(previousGroups);	
}
if (environment['xdc.traceEnable']) {
    var simpleInput = environment['xdc.traceEnable'];
    if (simpleInput == "all") {
        Trace.setLevel(utils.trace.$maxLevel);
        previousGroups.push("all");
        Trace.groupEnable(previousGroups);
    }
    else if (simpleInput == "load") {
        Trace.setLevel(utils.trace.$maxLevel);
        previousGroups.push("packageLoad");
        Trace.groupEnable(previousGroups);
    }
    else {
        Trace.setLevel(utils.trace.$maxLevel);
        Trace.capsuleEnable(environment['xdc.traceEnable'].split(";"));
    }
}
               
/* interpret the arguments */
if (arguments[0] == "-m") {
    var mod;
    var Cap;
    arguments.shift();
    mod = arguments.shift();
    /* 'mod' is the name of the module to be found on XDCPATH */
    if (mod == null) {
        throw xdc.$$XDCException(
            "xdc.TOOL_USAGE_ERROR",
            "xs: option -m must be followed by a module name");
    }
                    
    environment["xdc.scriptName"] = mod;

    Cap = xdc.module(mod.replace(/\//g, '\.'));
    if ("main" in Cap) {
        var save = utils.csd;
        utils.csd = Cap.$package.packageBase;
        Cap.main(arguments);
        utils.csd = save;
    }
    else {
        throw xdc.$$XDCException(
            "xdc.MODULE_UNDEFINED_MAIN_FUNCTION", "the module '" + mod
            + "' does not define a main() function");
    }
}
                
else if (arguments[0] == "-f" || arguments[0] == "-c") {
    var flag = arguments.shift();
    var spath = './' + ';' + xdc.curPath();
    var fname = arguments.shift();
    if (fname == null) {
        throw xdc.$$XDCException(
            "xdc.TOOL_USAGE_ERROR", "xs:option " + flag
            + " must be followed by a file name");  
    }
    environment["xdc.scriptName"] = fname;

    var cname = utils.findFile(fname, spath, ';');
    if (cname == null) {
        throw xdc.$$XDCException(
            "xdc.FILE_NOT_FOUND", "xs: can't find '" + fname
            + "' along the path '" + spath + "'"
            + "; Ensure that environment variable XDCPATH is set correctly."
            + "For further details refer XDC Getting Started Guide in "
            + "<xdc_install_dir>/docs");
    }
                
    if (flag == "-c") {
        var Cap = xdc.loadCapsule(cname);
        if (typeof Cap.main != "function") {
            throw xdc.$$XDCException(
                "xdc.UNDEFINED_MAIN_FUNCTION", "the module '" + cname
                + "' does not define a main() function");
        }
        Cap.main(arguments);
    }
    else {
        utils.load(cname);
    }
}

/* If '-f', '-m' or '-c' are not specified, the first argument is the name of a
 * package. The module Main in that package is loaded, and its function main()
 * is invoked.
 */
else if (arguments[0] != undefined) {
    var pkgName = arguments.shift();
    if (pkgName == "xdc.cfg") {
        xdc.$$make_om('cfg');
    }
    var pkg = xdc.loadPackage(pkgName);
    environment["xdc.scriptName"] = pkgName + ".Main";
    if ("Main" in pkg) {
        if ("main" in pkg.Main) {
            var save = utils.csd;
            utils.csd = pkg.packageBase;
            pkg.Main.main(arguments);
            utils.csd = save;
        }
        else {
            throw xdc.$$XDCException(
                "xdc.UNDEFINED_MAIN_FUNCTION", "the module '" + pkg.Main.$name
                +"' does not define a main() function");
        }
    }
    else {
        throw xdc.$$XDCException(
            "xdc.UNDEFINED_MAIN_FUNCTION", "the package '" + pkgName
            + "' does not have a module 'Main'");
    }
}
/*
 *  @(#) xdc; 1, 1, 1,239; 2-22-2010 10:32:54; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

