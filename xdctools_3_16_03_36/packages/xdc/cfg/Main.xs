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
 *  ======== Main.xs ========
 *
 *! Revision History
 *! ================
 *! 17-Aug-2006 sasha	renamed to Main.xs and removed getExecutables
 *! 10-Aug-2006 sasha	replaced utils.findFile with xdc.findFile
 *! 11-Jul-2006 sasha	moved pkg.close() before static$inits
 *! 22-Jun-2006 sasha	added getExecutables()
 *! 21-Mar-2006 sasha	created
 *! 05-Apr-2006 mas     added setPackage
 */

/*
 *  ======== Main.genFiles ========
 */
function genFiles(executable, prefix)
{
    this.$private.$$cfgCapsule._postinit();
    _genDependencyList();

    if (Program.$$isrom) {
        genRom(prefix);
    }

    var progGen = new Packages.xdc.services.intern.gen.Prog;

    /* generate configuration files */
    progGen.gen(prefix, executable, xdc.om, Program, true);

    if (config.hasReportedError) {
        throw xdc.$$XDCException(
            "xdc.cfg.CONFIG_ERROR", "Error in configuration");
    }

    /*
     * If an assembly, also gen linker files for executable's final link.
     * Specifically we want a linker command file that includes the memory
     * map. If the generated linker command file for the assembly is
     * named 'XX_pYY.xdl', the new linker command file will be 'XX_pYY_x.xdl'.
     */
    if (Program.$$isasm) {
        var save$$isasm = Program.$$isasm;
        Program.$$bind('$$isasm', 0);
        progGen.gen(prefix + '_x', executable, xdc.om, Program, false);
        Program.$$bind('$$isasm', save$$isasm);
    }

    if (config.hasReportedError) {
        throw xdc.$$XDCException(
            "xdc.cfg.CONFIG_ERROR", "Error in configuration");
    }

    /* generate config xml file, config graph, and debugger project files */
    genXML(prefix + ".cfg.xml");
    genDot(prefix + ".cfg.dot");
    genRov(prefix + ".rov.xs");
    
    var Rta = xdc.module('xdc.runtime.Rta');
    Rta.genRta(prefix + ".rta.xml");

    var genDebug = Program.gen.debuggerFiles;
    if (genDebug == null) {
        if (environment["xdc.cfg.gen.debuggerFiles"] != null) {
            genDebug = environment["xdc.cfg.gen.debuggerFiles"] == "true";
        }
    }
    if (genDebug
        || (genDebug == null
            && Program.build.profile.match(/debug/) != null)) {
        genDbg(prefix, executable, Program);
    }
}

/*
 *  ======== Main.init ========
 */
function init()
{
    this.$private.$$usestk = null;

    /* legacy tconf support */
    this.$private.$$legacy = {prog: prog, Program: Program, config: config};

    /* replace the default version of xdc.useModule with a cfg specific
     * version.
     */
    xdc.useModule = $$cfgUseModule;
    this.$private.$$usemod = $$usemod;

    Program = xdc.useModule('xdc.cfg.Program');

    xdc.om.$$bind('$root', Program);

    prog = Program; /* TODO: this should go away; find who uses it*/
}

var _Clock = xdc.useModule('xdc.services.global.Clock');

/*
 *  ======== Main.main ========
 */
function main(args)
{
    function errorCheck(val) {
        if (val != "") {
            /* There are some errors or warnings. If only warnings are present,
             * the configuration step continues.
             */
            if (val.substring(0,2) == "@@") {
                /* These are warnings/errors reported via $log functions */
                printErrors();
                if (xdc.om.$$errors.length > 0) {
                    throw new Error("Configuration failed!");
                }
                else {
                    xdc.om.$$warnings.length = 0;
                }
            }
            else {
                throw new Error(val);
            }
        }
    }

    if (args.length < 3) {
        print("usage: xs xdc.cfg exe-name cfg-file gen-files-prefix [pkg-name]");
        throw Error("Too few arguments");
    }

    if ($traceQuery()) {
        _Clock.enable = true;
    }

    _Clock.reset();

    var executable = args[0];
    var cfgScript = args[1];
    var prefix = args[2];
    var pkgName = args[3];

    xdc.$$make_om('cfg');

    var cfgmodel = xdc.useModule('xdc.cfg.Main');
    cfgmodel.init();
    /* necessary for backward compatibility with tconf */
    xdc.global.$$legacy = cfgmodel.$private.$$legacy;

    _myTrace("config model initialization: $$phase - >1", 1, ["xdccore"]);
    xdc.om.$$bind('$$phase', 1);
    var ret = cfgmodel.setExecutable(cfgScript, pkgName);
    errorCheck(ret);
    _Clock.print("cfg model initialized.");

    _myTrace("user script: $$phase - >2", 1, ["xdccore"]);
    xdc.om.$$bind('$$phase', 2);
    ret = cfgmodel.runCfg();
    errorCheck(ret);
    _Clock.print("cfg user script done.");

    _myTrace("validation phase: $$phase - >6", 1, ["xdccore"]);
    xdc.om.$$bind('$$phase', 6);
    ret = cfgmodel.validate();
    errorCheck(ret);

    _myTrace("C config file generation: $$phase - >7", 1, ["xdccore"]);
    xdc.om.$$bind('$$phase', 7);
    cfgmodel.genFiles(executable, prefix);

    _Clock.print("cfg generation done. Total cfg time: "
        + _Clock.getElapsedTime());
}

/*
 *  ======== Main.runCfg ========
 */
function runCfg()
{
    return (this.runStringCfg(null));
}

/*
 *  ======== Main.runStringCfg ========
 */
function runStringCfg(script)
{

    this.$private.$$cfgCapsule._userscript(this.$private.$$legacy, script);
    try {
        _myTrace("package closing phase: $$phase - >3", 1, ["xdccore"]);
        xdc.om.$$bind('$$phase', 3);
        closePackages();
	sealConfig();
	_myTrace("all config parameters sealed", 2, ["xdccore"]);
        _myTrace("module$static$init phase: $$phase - >4", 1, ["xdccore"]);
        xdc.om.$$bind('$$phase', 4);
        configureModules();
        _myTrace("instance$static$init phase: $$phase - >5", 1, ["xdccore"]);
        xdc.om.$$bind('$$phase', 5);
        configureInstances();
    }
    catch (e) {
        if (e.toString() == "Error: xdc.fatal.error") {
            return (getErrors());
        }
        else {
            /* The code that examines $$warnings and $$errors must not be a
             * function because it changes stack trace for the caught
             * exception rethrown later.
             * Error and warning messages are generated initially with ':::'
             * as a separator between fields, so that XGCONF can parse them.
             * When printed ':::' are replaced with ': '.
             */
            if (xdc.om.$$warnings.length > 0) {
                for (var i = 0; i < xdc.om.$$warnings.length; i++) {
                    print(xdc.om.$$warnings[i].replace(/\:\:\:/g, ": "));
                }
            }
            if (xdc.om.$$errors.length > 0) {
                for (var i = 0; i < xdc.om.$$errors.length; i++) {
                    print(xdc.om.$$errors[i].replace(/\:\:\:/g, ": "));
                }
            }
            throw (e);
        }
    }

    if (xdc.om.$$errors.length > 0) {
        return (getErrors());
    }
    return ("");
}

/*
 *  ======== sealConfig ========
 */
function sealConfig()
{
    for (var i = 0; i < $om.$packages.length; i++) {
        var pkg = $om.$packages[i].$orig;
        for (var j = 0; j < pkg.$modules.length; j++) {
            var mod = pkg.$modules[j];
            if ('PROXY$' in mod && mod.PROXY$) {
                continue;
            }

            if (mod.$used && mod.$name != "xdc.cfg.Program") {
                /* We leave internal config parameters unsealed because they
                 * should be accessed only by modules within this package
                 * because we keep changing them.
                 */
                var modParams = mod.$spec.getConfigs().listIterator();
                var internMap = {};

                while (modParams.hasNext()) {
                    var param = modParams.next();
                    if (param.isInternal() || param.isSys()) {
                    	internMap[param.getName()] = 1;
                    }
                }

                for (var f in mod) {
                    if (!(f in internMap)) {
                        mod.$seal(f);
                    }
                }
            }
        }
    }
}

/*
 *  ======== Main.setExecutable ========
 */
function setExecutable(cfgScript, pkgName)
{
    environment['config.scriptName'] = cfgScript;

    var cfgFile = null;
    if (pkgName == undefined) {
        cfgFile = new java.io.File(cfgScript);
    }
    else {
        cfgFile = new java.io.File(pkgName + "/" + cfgScript);
    }

    if (cfgFile == null) {
        throw Error("Configuration file " + cfgScript + " is not found!");
    }

    var genCfg = utils.loadCapsule(cfgFile.getCanonicalPath());
    this.$private.$$cfgCapsule = genCfg;
    try {
        genCfg._cfginit();
    }
    catch (e) {
        if (e.toString() == "Error: xdc.fatal.error") {
            return (getErrors());
        }
        else {
            /* The code that examines $$warnings and $$errors must not be a
             * function because it changes stack trace for the caught
             * exception rethrown later.
             * Error and warning messages are generated initially with ':::'
             * as a separator between fields, so that XGCONF can parse them.
             * When printed ':::' are replaced with ': '.
             */
            if (xdc.om.$$warnings.length > 0) {
                for (var i = 0; i < xdc.om.$$warnings.length; i++) {
                    print(xdc.om.$$warnings[i].replace(/\:\:\:/g, ": "));
                }
            }
            if (xdc.om.$$errors.length > 0) {
                for (var i = 0; i < xdc.om.$$errors.length; i++) {
                    print(xdc.om.$$errors[i].replace(/\:\:\:/g, ": "));
                }
            }
            throw (e);
        }
    }

    if (xdc.om.$$errors.length > 0 || xdc.om.$$warnings.length > 0) {
        return (getErrors());
    }

    return ("");
}

/*
 *  ======== Main.validate ========
 */
function validate()
{

    /* only the throws by $$logFatal are caught here */
    try {
        /* package validate() */
        for (var i = xdc.om.$packages.length - 1; i >= 0; i--) {
            var pkg = xdc.om['xdc.IPackage'].Module(xdc.om.$packages[i]);
            _myTrace("validating " + pkg.$name, 2, ["xdccore"]);
            for (var j = 0; j < pkg.$modules.length; j++) {
                if (pkg.$modules[j].$used) {
                    pkg.$modules[j].module$validate();
                }
            }
            pkg.validate();
        }
    }
    catch (e) {
        if (e.toString() == "Error: xdc.fatal.error") {
            return (getErrors());
        }
        else {
            /* The code that examines $$warnings and $$errors must not be a
             * function because it changes stack trace for the caught
             * exception rethrown later.
             * Error and warning messages are generated initially with ':::'
             * as a separator between fields, so that XGCONF can parse them.
             * When printed ':::' are replaced with ': '.
             */
            if (xdc.om.$$warnings.length > 0) {
                for (var i = 0; i < xdc.om.$$warnings.length; i++) {
                    print(xdc.om.$$warnings[i].replace(/\:\:\:/g, ": "));
                }
            }
            if (xdc.om.$$errors.length > 0) {
                for (var i = 0; i < xdc.om.$$errors.length; i++) {
                    print(xdc.om.$$errors[i].replace(/\:\:\:/g, ": "));
                }
            }
            throw (e);
        }
    }

    if (xdc.om.$$errors.length > 0) {
        return (getErrors());
    }

    _Clock.print("cfg model validate done.");

    /* check version consistency and fail on any discrepancy */
    var result = checkVersions(environment["xdc.cfg.check.exclude"]);

    _Clock.print("cfg package version checks done.");
    if (result.msg != "") {
        if (environment["xdc.cfg.check.fatal"] == "false"
            || result.eCount == 0) {
            print("Warning: " + result.msg);
        }
        else {
            return (result.msg);
        }
    }

    if (config.hasReportedError) {
        return ("Validation error");
    }

    if (xdc.om.$$warnings.length > 0) {
        return (getErrors());
    }

    return ("");
}

/*---------------- private functions ----------------- */
/* From this point on, 'this' refers to the file scope, not module Main */

/*
 *  ======== checkVersions ========
 *  Validate that the "built-with" versions of imported packages are
 *  compatible with their actual versions.
 *
 *  Returns an object with the properties wCount, eCount, and msg.  If there
 *  is no incompatibility msg == ""; otherwise msg is a meaningful message
 *  describing all incompatibilities found.  wCount is a count of warnings
 *  and eCount is a count of errors
 */
function checkVersions(exclude)
{
    var result = {eCount: 0, wCount: 0, msg: ""};
    var msgs = {};

    /* optionally subset the list of imported packages to check */
    var pkgList = [];
    if (exclude != null && exclude != undefined) {
        for (var i = 0; i < $om.$packages.length; i++) {
            var pkg = $om.$packages[i].$orig;
            var tmp = pkg.$name.match(exclude);
            if (tmp == null || tmp[0] != pkg.$name) {
//              print("including package " + pkg.$name);
                pkgList.push($om.$packages[i]);
            }
            else {
//              print("excluding package " + pkg.$name);
            }
        }
    }
    else {
        pkgList = $om.$packages;
    }

    /*  For every package pkg imported in this configuration, check that
     *  the target version used by pkg is compatible with the target
     *  version used by Program.
     */
    if (Program.build.target.version != null) {
        var pa = Program.build.target.version.split("{");
        for (var i = 0; i < pkgList.length; i++) {
            var pkg = pkgList[i].$orig;
            if (pkg.build.libraries.length == 0) {
                continue;   /* if pkg has no libraries, don't check it */
            }

            /* get target version info from pkg */
            var trgs = Packages.xdc.services.global.Vers.getTargetReferences(
                            pkg.packageBase + "/package/package.bld.xml");

            /* verify compatibility with Program.build.target version */
            for (var j = 0; j < trgs.length; j++) {
                var ta = ("" + trgs[j]).split("{");
                if (ta[0] == pa[0]) {
                    var emsg = isCompatible(ta[0], pa[1], ta[1], pkg.$name);
                    if (emsg != null) {
                        result.eCount += emsg.eCount;
                        result.wCount += emsg.wCount;
                        if (msgs[ta[0]] == null) {
                            msgs[ta[0]] = "xdc.cfg.INCOMPATIBLE_TARGET_VERSION:"
                                + " current target '" + ta[0] + "' [" + pa[1]
                                + "] is not compatible with targets used to "
                                + "build the following packages";
                        }
                        msgs[ta[0]] += "; " + "package " + pkg.$name
                            + " [in " + pkg.packageBase + "]"
                            + " was built using '" + ta[0]
                            + "' [" + ta[1] + "]\n";
                    }
                    break;
                }
            }
            /*
             *  Note that we do *not* ensure that the same targets are used.
             *  We only verify that for the targets used their keys indicate
             *  that they are compatible.  This allows a package to use a
             *  different target to build a library that is contributed to
             *  this executable; e.g., BIOS can use a single C55 target that
             *  supports 1510, 1610, and 1710 but the application can use a
             *  target that assumes the 1710.
             */
             if (j >= trgs.length) {
                 ;  /* package pkg was not built with the same target! */
             }
        }
    }

    /*  For every package pkg imported by this configuration, check that
     *  the packages used to build pkg are compatible with the packages
     *  imported by this configuration.
     */
    for (var i = 0; i < pkgList.length; i++) {
        var pkg = pkgList[i].$orig;

        /* get packages referenced by pkg during its build */
//        print("    imported package " + pkg.$name);
        var refs = Packages.xdc.services.global.Vers.getReferences(
                        pkg.packageBase + "/package/package.rel.xml");

        /* for each referenced package, check consistency with imported set */
        for (var j = 0; j < refs.length; j++) {
            var pa = ("" + refs[j]).split("{");
//            print("        built with: " + refs[j]);

            for (var k = 0; k < pkgList.length; k++) {
                var tmp = pkgList[k].$orig;

                /* if ref[j] is in the imported set ... */
                if (pa[0] == tmp.$name) {
                    /* build tmp's version string from vers number array */
                    var vers = "";
                    if (tmp.$vers != null) {
                        vers = tmp.$vers.slice(0,4).join(", ");
                    }

                    var emsg = isCompatible(tmp.$name, vers, pa[1], pkg.$name);
                    if (emsg != null) {
                        result.eCount += emsg.eCount;
                        result.wCount += emsg.wCount;
                        if (msgs[tmp.$name] == null) {
                            msgs[tmp.$name] = "incompatible use of package '"
                                + tmp.$name + "' [in " + tmp.packageBase
                                + "]: version of the loaded package '"
                                + tmp.$name + "' is [" + vers + "]";
                        }
                        msgs[tmp.$name] += ", while '" + pkg.$name + "' [in "
                            + pkg.packageBase + "]" + " was built with '"
                            + tmp.$name + "' [" + pa[1] + "]";
                    }
                }
            }
        }
    }

    var sep = "";
    for (var m in msgs) {
        result.msg += sep + msgs[m];
        sep = ";    ";
    }

    if (result.msg != "" && environment["xdc.cfg.check.fatal"] != "false"
        && result.eCount > 0) {
        result.msg += "\nAdding the following line to your program "
            + "configuration script:\n\tenvironment['xdc.cfg.check.fatal'] = "
            + "'false';\nconverts this incompatibility error into a warning. "
            + "Please, check the documentation for the package xdc.cfg for "
            + "more information.";
    }

    return (result);
}

/*
 *  ======== _genDependencyList ========
 *
 */
function _genDependencyList()
{
    var genList = [];

    /* Here we need to go through xdc.om.$require map and put the packages
     * from genList in order determined by dependencies from xdc.om.$require.
     */
//    print("_genDependencyList: (requires)"); for (var key in xdc.om.$require) print("    " + key);
//    _Clock.print("tsort:start (" + xdc.om.$require.length + " edges, " + xdc.om.$packages.length + " pkgs)");

    while (xdc.om.$require.length > 0) {

	/* select a package with no requirements; i.e., a leaf node */
        var selected = null;
        for (var key in xdc.om.$require) {
            var candidate = xdc.om.$require[key];
            //print("candidate " + candidate);
            var leaf = 1;
            for (var key2 in xdc.om.$require) {
                if (key2.split(/\s/)[0] == candidate) {
                    //print("found dependency on " + xdc.om.$require[key2]);
                    leaf = 0;
                    break;
                }
            }
            if (leaf == 1) {
                selected = candidate;
                break;
            }
        }

        if (selected == null) {
            /* There is a cycle in remaining dependencies. Find a package
             * from the cycle and use it as 'selected'. If there is a cycle,
             * the program is bogus anyway, so we just try to recover using a
             * random ordering and see if it goes through.
             * There could be some packages remaining that are not a part of
             * the cycle. If we just follow the cycle for the number of steps
             * equal to the number of packages, we are going to end up with one
             * of the packages from the cycle. That way, when we remove one of
             * the dependencies for a package from the cycle, we will actually
             * break the cycle (or one of the cycles).
             */
            selected = xdc.om.$require[0];
            var cycleStart;
            var counter = xdc.om.$packages.length - genList.length;
            while (counter > 0) {
                for (var key in xdc.om.$require) {
                    if (key.split(/\s/)[0] == selected) {
                        selected = xdc.om.$require[key];
                        cycleStart = key;
                        counter--;
                    }
                }
            }

            _myTrace(
                "warning: cycle detected involving the following packages:", 1,
                ["packageLoad"]);
            var next = xdc.om.$require[cycleStart];
            _myTrace("    " + cycleStart.split(/\s/)[0] + " --> " + next, 1,
                ["packageLoad"]);
            while (next != selected) {
                for (var key in xdc.om.$require) {
                    if (key.split(/\s/)[0] == next) {
                        next = xdc.om.$require[key];
                        _myTrace("   " + key.split(/\s/)[0] + " --> " + next, 1,
                            ["packageLoad"]);
                        break;
                    }
                }
            }

            /* Promote dependencies of the removed package, so they
             * are not completely lost when the cycle is broken.
             * Normally when a package is removed in this function it
             * is a leaf node -- it has no remaining dependencies. But in
             * this section we are breaking a cycle -- the package we will
             * remove still has remaining dependencies. The following code
             * essentially grafts together the incoming and outgoing
             * edges of the package about to be removed. By doing so
             * we at least retain the derivable constraints between the
             * packages "above" and "below" the removed package.
             */
            /* first find all the dependencies of the package about to
             * be removed (call these "child" packages)
             */
            var children = [];
            for (var key in xdc.om.$require) {
                var parent = key.split(/\s/)[0];
                if (parent == selected) {
                    children.push(xdc.om.$require[key]);
                }
            }
            /* next find all the packages that depend on the one about
             * to be removed (call these "grandparent" packages)
             */
            for (var key in xdc.om.$require) {
                var grandparent = key.split(/\s/)[0];
                var parent = xdc.om.$require[key];
                if (parent == selected) {
                    /* and add explicit dependencies from the grandparent
                     * packages to the child packages.
                     */
                    for each (var child in children) {
                        if (grandparent == child) {
                            /* no need to record a dependency on yourself */
                            continue;
                        }

                        /* record the dependency */
                        xdc.om.$require[grandparent + " " + child] = child;
                    }
                }
            }
        }

	/* append the selected leaf to the end of genList */
        genList.push(xdc.om[selected]);
        xdc.om[selected].$$bind('$$genflg', 1);

        /* Remove all elements from $require that have 'selected' as a
         * second element; i.e., edges that reference the selected leaf
         */
        for (var key in xdc.om.$require) {
            if (xdc.om.$require[key] == selected) {
                /* A very important assumption here is that 'key' shows up in
                 * the remaining dependencies as 'value. That must be true
                 * because someone must have loaded 'key', and since we haven't
                 * moved 'key' into the final list, that dependency hasn't been
                 * removed yet.
                 */
                //print("deleted " + key.split(/\s/)[0] + " -> " + key.split(/\s/)[1]);
                delete xdc.om.$require[key];
            }
        }
    }

    /* get $homepkg out of the list and add it at the end to ensure its
     * libraries will end up at the top of the linker command file.
     */
    for (var i = 0; i < genList.length; i++) {
        if (genList[i] == xdc.om.$homepkg) {
            genList.splice(i, 1);
            genList.push(xdc.om.$homepkg);
            break;
        }
    }

//    print("_genDependencyList:");for (var i in genList) print("    " + genList[i]);

    /* update the official list of packages */
    xdc.om.$packages.$self = genList;
//    _Clock.print("tsort:done");

}

/*
 *  ======== closePackages ========
 *
 *  call pkg.close() for all packages in the configuration
 */
function closePackages ()
{
    var curIndex = 0;
    var closeStack = [];

    var saveCurPkg = xdc.om.$curpkg;
    for (;;) {

        /* transfer current set of packages to a stack */
        for (var i = curIndex; i < xdc.om.$packages.length; i++) {
            closeStack.push(xdc.om.$packages[i]);
        }

	curIndex = xdc.om.$packages.length;
        if (closeStack.length == 0) {
            break;
        }

        /* close the top-most package */
        var curpkg = xdc.om['xdc.IPackage'].Module(closeStack.pop());

        /* Setting $curpkg to curpkg.$name must precede the useModule calls */
        xdc.om.$$bind('$curpkg', curpkg.$name);

        for each (var mod in curpkg.$modules) {
            /* Modules that never made it to $$usemod or went through it only
             * partially are calling $$usemod again.
             */
            if (mod.$used &&
                (!('$$cfgPhase' in mod) || (mod.$$cfgPhase == 1))) {
                xdc.useModule(mod);
            }
        }
        _myTrace("calling " + curpkg.$name + ".close()", 1, ["xdccore"]);
        curpkg.close();
    }
    xdc.om.$$bind('$curpkg', saveCurPkg);

    /*  special call into xdc.runtime package to "finalize" the
     *  modules in this configuration; e.g., propagate logggers, gates,
     *  and heap managers to all runtime modules in the configuration
     *
     *  Warning: no new modules can be added after this point; otherwise the
     *  common settings will not be properly initialized!
     */
    xdc.loadPackage('xdc.runtime').$capsule.finalize();
    Program.$capsule._close.apply(Program);
}

/*
 *  ======== configureInstances ========
 *
 *  call instance$static$init for all instances
 */
function configureInstances()
{
    /* construct instance meta-objects */
    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i].$orig;
        if (!mod.$used || mod.$hostonly) {
            continue;
        }
        for (var aname in {$instances: null, $objects: null}) {
            var arr = mod[aname];
            for (var j = 0; j < arr.length; j++) {
                var inst = arr[j];
                if ('$$phase' in inst && inst.$$phase >= 5) {
                    continue;
                }
                inst.$$bind('$$phase', 5);
                _myTrace("calling " + mod.$name + ".instance$static$init for "
                    + "instance " + aname, 2, ["xdccore"]);
                mod.__initObject(inst);
            }
        }
    }
}

/*
 *  ======== configureModules ========
 *
 *  call module$static$init for all modules
 */
function configureModules()
{
    var cfgModel = xdc.module('xdc.cfg.Main');

    /* propagate default profile to each imported package */
    for (var i = xdc.om.$packages.length - 1; i >= 0; i--) {
        var pkg = xdc.om['xdc.IPackage'].Module(xdc.om.$packages[i]);
        if (pkg.profile == null) {
            pkg.profile = Program.build.profile;
        }
    }

    /* propagate assertions of modules used */
    cfgModel.$private.$$usestk = [];
    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
        //mod.$seal();
        if (mod.$used) {
            _myTrace("calling " + mod.$orig.$name + ".module$static$init", 2,
                ["xdccore"]);
            mod.$orig.module$static$init(
                '$object' in mod ? mod.$object : null, mod.$orig);
        }
    }
}

/*
 *  ======== genDbg ========
 *  Generate debug support files for IDEs such as CCS.
 *
 *  Params:
 *      cfgName - the name of the generated configuration script
 *      exeName - the name of the output executable
 *      prog    - the configured xdc.cfg.Program object
 *
 *  both cfgName and exeName are relative to the directory containing
 *  package.bld.
 */
function genDbg(cfgName, exeName, prog)
{
    var template;
    var fPattern;
    var fname;

//    print("cfgName = '" + cfgName + "', " + "exeName = '" + exeName);

    if (prog.build.target.debugGen != null) {
        template = prog.build.target.debugGen.execTemplate;
        fPattern = prog.build.target.debugGen.execPattern;
    }
    if (template != null) {
        var bldUtils = xdc.module('xdc.bld.Utils');

        /* expand the output file name pattern */
        fname = bldUtils.expandDbgName(cfgName, exeName, fPattern);

        /* expand template */
//      print("template file '" + template + "', generating '" + fname + "'");
        var t = xdc.loadTemplate(template);
        t.genFile(fname, prog, [exeName]);
    }

    return (fname);
}

/*
 *  ======== genDot ========
 *  Generate Dot file that contains information about the configuration.
 */
function genDot(outputFileName)
{
    function toLabel(name)
    {
        return (name.replace(/\./g, '_'));
    }

    /* if outputFileName is null, write to stdout */
    var out;
    if (outputFileName != null) {
        var file = new java.io.File(outputFileName);
        file["delete"]();
        out = new java.io.FileWriter(outputFileName);
        out = new java.io.BufferedWriter(out);
    }
    else {
        out = new java.io.OutputStreamWriter(java.lang.System.out);
    }

    out.write('digraph configuration {\n');
    out.write('    size="7.5,10";\n');
    out.write('    rankdir=LR;\n');
    out.write('    ranksep=".50 equally";\n');
    out.write('    concentrate=true;\n');
    out.write('    compound=true;\n');
    out.write('    label="\\nConfiguration for '
        + Program.buildPackage + '/' + Program.name + '"\n');

    /* Create a distinguished subgraph that represents the config script */
    out.write('  node [font=Helvetica, fontsize=14, fontcolor=black];');
    out.write('  subgraph cluster0 {label=""; __cfg [label="'
        + Program.build.cfgScript + '", color=white, fontcolor=blue];\n');

    out.write('    node [font=Helvetica, fontsize=10];');

    /*  For every package imported by this configuration, create
     *  sub-graph cluster of modules within the package.
     */
    pkgNodes = [];
    for (var i = 0; i < $om.$packages.length; i++) {
        var pkg = $om.$packages[i].$orig;
        var vers = "";
        if (pkg.$vers != null) {
            vers = pkg.$vers.join(",");
        }

        out.write('    subgraph cluster' + (i + 1) + ' {\n');
        out.write('        label="";\n');

        /* create top node in the cluster to represent the pkg as a whole */
        var pnname = toLabel(pkg.$name);
        out.write('        '+ pnname + '__top [shape=box,label="'
            + pkg.$name + '\\n' + vers + '", color=white];\n');

        /* create bottom node in the cluster to represent pkg as a whole */
        if (pkg.$modules.length > 0) {
            out.write('        '+ pnname + '__bot [shape=point,label=""'
                + ', style=invis];\n');
            pkgNodes[i] = {top: pnname + '__top', bot: pnname + '__bot'};
        }
        else {
            pkgNodes[i] = {top: pnname + '__top', bot: pnname + '__top'};
        }

        /* create nodes for each module in the package pkg */
        for (var j = 0; j < pkg.$modules.length; j++) {
            var mod = pkg.$modules[j];
            var nname = toLabel(mod.$name);
            var mname = mod.$name + "";
            if (mname.indexOf(pkg.$name + '.') == 0) {
                mname = mname.substr(pkg.$name.length + 1);
            }

            /* make a node for each module; gray are used, white aren't */
            if (mod.$used) {
                out.write('        ' + nname + ' [style=filled,fillcolor='
                    + 'lightgray, label="' + mname + '"];\n');
            }
            else {
//              out.write('        ' + nname + ' [style=filled,fillcolor='
//                  + 'white, label="' + mname + '"];\n');
                continue;
            }

            /* top invisibly points to all modules in the package */
            out.write('        ' + pkgNodes[i].top + ' -> '
                + nname + '[style=invis];\n');
            /* and all modules in the package invisibly point to bot */
            out.write('        ' + nname + ' -> '
                + pkgNodes[i].bot + '[style=invis];\n');

            /* each module points to every other module it "uses" */
            for (var k = 0; k < mod.$uses.length; k++) {
                out.write('        ' + nname + ' -> '
                    + toLabel(mod.$uses[k].$name) + '\n');
            }
        }
        out.write('    }\n');   /* end package subgraph */
    }
    out.write('  }\n'); /* end cfg script sub-graph */

    /*  For every package pkg imported in this configuration, draw an edge
     *  from the bottom of the cluster to the target version used by pkg.
     */
    out.write('  node [font=Helvetica, fontsize=10];\n');
    var pa = Program.build.target.version.split("{");
    for (var i = 0; i < $om.$packages.length; i++) {
        var pkg = $om.$packages[i].$orig;

        /* get target version info from pkg */
        var trgs = Packages.xdc.services.global.Vers.getTargetReferences(
                        pkg.packageBase + "/package/package.bld.xml");

        /* find the target used by this config, and output its version */
        var tname = null;
        for (var j = 0; j < trgs.length; j++) {
            var ta = ("" + trgs[j]).split("{");
            if (ta[0] == pa[0]) {
                /* create a unique node name for each target version */
                tname = toLabel(ta[0]) + '__'
                    + ta[1].replace(/\./g, '__').replace(/,/g,'_');

                /* create the target node */
                out.write('    ' + tname
                    + ' [shape=record,label="' + ta[0] + '|' + ta[1]
		    + '",style=filled, fillcolor=lightgrey];\n');
                break;
            }
        }
        /* draw an edge to the target used by the package */
        if (tname != null) {
            out.write('    ' + pkgNodes[i].bot
                + ' -> ' + tname + ' [ltail=cluster' + (i + 1) + '];\n');
        }
    }

    out.write('}\n');
    out.flush();

    if (outputFileName != null) {
        out.close();
    }
}

/*
 *  ======== cfg.genRom ========
 */
function genRom( prefix )
{
    /* generate <prefix>.romasm.xs */

    var Text = xdc.module('xdc.runtime.Text');
    var str = "";
    var strings = [];

    for (var i = 0; i < Text.charTab.length; i++) {
        if (Text.charTab[i] != 0) {
            str += String.fromCharCode(Text.charTab[i]);
        }
        else {
            strings.push(str);
            str = "";
        }
    }

    var o = {
        asmName:        Program.name,
        cfgScript:      Program.build.cfgScript,
        isasm:          Program.$$isasm,
        isrom:          Program.$$isrom,
        fixedCodeAddr:  Program.fixedCodeAddr,
        fixedDataAddr:  Program.fixedDataAddr,
        modules: [],
        sectNamesC: [],
        sectNamesV: [],
        nodeTab: xdc.module('xdc.runtime.Text').nodeTab,
        charTab: strings,
    };

    var bset = {};

    o.objfile = 'package/cfg/' + o.asmName + '.obj';

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];

        if (mod.$hostonly || !mod.$used || mod.$$scope == -1) {
            continue;
        }

        o.modules.push(
            {name: mod.$name, romPatchTable: mod.common$.romPatchTable});

        if (mod.PROXY$) {
            continue;
        }

        var cname = mod.$name.replace(/\./g, '_') + '_';

        if (mod.common$.romPatchTable) {
            o.sectNamesC.push(cname + 'Module__MTAB__C');
        }
        o.sectNamesV.push(cname + 'Module__root__V');

        if ('$object' in mod) {
            o.sectNamesV.push(cname + 'Module__state__V');
        }

        if (mod.$$instflag) {
            if (mod.$$romcfgs.indexOf('|Object__PARAMS|') == -1) {
                o.sectNamesC.push(cname + 'Object__PARAMS__C');
            }
            if (mod.common$.instanceHeap) {
                o.sectNamesC.push(cname + 'Object__DESC__C');
            }
        }

        if (mod.$$iflag && mod.common$.fxntab) {
            for (var u = mod.$spec.getSuper(); u != null; u = u.getSuper()) {
                var cn = String(u.getQualName()).replace(/\./g, '_') + '_';
                if (!bset[cn]) {
                    o.sectNamesC.push(cn + 'Interface__BASE__C');
                    bset[cn] = true;
                }
            }
        }

        for each (var mc in mod.$$mcfgs) {
            if (mod.$$romcfgs.indexOf('|' + mc + '|') == -1) {
                o.sectNamesC.push(cname + mc + '__C');
            }
        }
    }

    var fn = prefix + '.romasm.xs';
    var file = new java.io.File(fn);
    file["delete"]();
    xdc.recapObject(o, fn);
    Program.$capsule._romAsm = o;

    /* generate <prefix>.rename */

    var fos = new java.io.PrintWriter(prefix + '.rename');

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
        var unit = mod.$spec;
        var cname = String(unit.getQualName()).replace(/\./g, '_') + '_';

        if (unit.isInter() || unit.isMeta()
            || !mod.$used || mod.$$scope == -1) {
            continue;
        }

        for each (var fxn in mod.$spec.getFxns().toArray()) {
            if (fxn.isSys()) {
                continue;
            }
            var fn = '_' + cname + fxn.getName();
            fos.print(fn + '__E ' + fn + '__ER\n');
            fos.print(fn + '__R ' + fn + '__E\n');
            if (fxn.isVarg()) {
                var fn = '_' + cname + fxn.getName() + '_va';
                fos.print(fn + '__E ' + fn + '__ER\n');
                fos.print(fn + '__R ' + fn + '__E\n');
            }
        }
    }

    for each (var sn in Program.$capsule._romAsm.sectNamesC) {
        fos.print('_' + sn + ' _' + sn + 'R\n');
    }

    for each (var sn in Program.$capsule._romAsm.sectNamesV) {
        fos.print('_' + sn + ' _' + sn + 'R\n');
    }

    fos.close();
}


/*
 *  ======== genRov ========
 *
 *  Recapture configuration information for rov model
 */
function genRov(outputFileName)
{
    var o = {};

    o.build = Program.build;
    o.$modules = {};

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var m = xdc.om.$modules[i];
        if (!m.$hostonly && m.$used && !m.PROXY$) {
            o.$modules[m.$name] = m;
            o.$modules["#" + m.Module__id] = m;
        }
    }

    if (outputFileName != null) {
        var file = new java.io.File(outputFileName);
        file["delete"]();
    }

    xdc.recapObject(o, outputFileName);
}

/*
 *  ======== genXML ========
 *  Generate XML file that contains information about the configuration.
 */
function genXML(outputFileName)
{
    /* if outputFileName is null, write to stdout */
    var out;
    if (outputFileName != null) {
        var file = new java.io.File(outputFileName);
        file["delete"]();
        out = new java.io.FileWriter(outputFileName);
        out = new java.io.BufferedWriter(out);
    }
    else {
        out = new java.io.OutputStreamWriter(java.lang.System.out);
    }

    out.write('<?xml version="1.0" encoding="UTF-8"?>\n');
//    out.write('<!DOCTYPE release SYSTEM "configuration.dtd">\n');
    out.write('<!--  This file conforms to the DTD xdc/cfg/configuration.dtd -->\n');
    out.write('<configuration name="'
        + Program.buildPackage + '/' + Program.name + '"\n    '
        + 'platformName="' + Program.platformName + '"\n    '
        + 'globalSection="' + Program.globalSection + '"\n    '
        + 'sysStack="' + Program.sysStack + '"\n    '
        + 'stack="' + Program.stack + '"\n    '
        + 'heap="' + Program.heap + '"\n    '
        + 'argSize="' + Program.argSize + '"\n    '
        + 'execCmd="' + escape(Program.execCmd) + '"\n    '
        + 'endian="' + Program.endian + '"\n    '
        + 'codeModel="' + Program.codeModel + '"\n    '
        + 'dataModel="' + Program.dataModel + '">\n');

    /*  For every package pkg imported in this configuration, output
     *  the target version used by the pkg.
     */
    out.write('<targets>\n');
    var pa = Program.build.target.version.split("{");
    for (var i = 0; i < $om.$packages.length; i++) {
        var pkg = $om.$packages[i].$orig;

        /* get target version info from pkg */
        var trgs = Packages.xdc.services.global.Vers.getTargetReferences(
                        pkg.packageBase + "/package/package.bld.xml");

        /* find the target used by this config, and output its version */
        for (var j = 0; j < trgs.length; j++) {
            var ta = ("" + trgs[j]).split("{");
            if (ta[0] == pa[0]) {
                out.write('    <target name="' + ta[0] + '"\n');
                out.write('            version="' + ta[1] + '"\n');
                out.write('            usedby="' + pkg.$name + '"/>\n');
                break;
            }
        }
    }
    out.write('</targets>\n');

    /*  For every package pkg imported by this configuration, output its
     *  version and its modules used list, and for each module, its uses
     *  list.
     */
    out.write('<imports>\n');
    for (var i = 0; i < $om.$packages.length; i++) {
        var pkg = $om.$packages[i].$orig;
        var vers = "";
        if (pkg.$vers != null) {
            vers = pkg.$vers.join(",");
        }

        out.write('    <package name="' + pkg.$name + '" version="'
            + vers + '" repository="' + pkg.packageRepository + '">\n');

        /* dump all modules (except for proxies) */
        for (var j = 0; j < pkg.$modules.length; j++) {
            var mod = pkg.$modules[j];
            if ('PROXY$' in mod && mod.PROXY$) {
		continue;
	    }
            out.write('        <module name="' + mod.$name + '"\n');
            out.write('                used="' + mod.$used + '"\n');
            out.write('                uses="');
            var prefix = "";
            for (var k = 0; k < mod.$uses.length; k++) {
                out.write(prefix + mod.$uses[k].$name);
                prefix = ';';
            }
            out.write('">\n');

            /* if the module is used, dump its config settings */
            if (mod.$used) {
                var m = xdc.om[mod.$name].Module(mod);
                for (f in m) {
                    var type = typeof m[f];
		    var value = String(m[f]);
		    var xml = null;
                    if (m[f] != null && type == "object") {
			if ("$type" in m[f]) {
			    type = escape("" + m[f].$type);
			}
			if ("$toText" in m[f]) {
			    value = m[f].$toText();
                            try {
				xml = ("$toXml" in m[f]) ? m[f].$toXml() : null;
                            }
			    catch (e) {
//				print("failed to gen XML for " + m + "." + f);
			    }
			}
                    }
                    out.write('            <feature name="' + f
                        + '" type="' + type
                        + '" value="' + escape(value) + '"');
		    if (xml == null) {
			 out.write('/>\n');
		    }
		    else {
			out.write(">" + xml + "\n            </feature>\n");
		    }
                }
            }

            out.write('        </module>\n');
        }
        out.write('    </package>\n');
    }
    out.write('</imports>\n');

    out.write('</configuration>\n');
    out.flush();

    if (outputFileName != null) {
        out.close();
    }
}

/*
 *  ======== getErrors ========
 *  Create a string out of all warnings and error messages separated by '@@'.
 *  The interface between XGCONF and cfg server does not allow arrays, so we
 *  had to use one long string.
 */
function getErrors()
{
    var ret = "@@";
    if (xdc.om.$$warnings.length > 0) {
        ret = ret + xdc.om.$$warnings.join("@@");
    }

    if (xdc.om.$$errors.length > 0) {
        if (xdc.om.$$warnings.length > 0) {
            ret = ret + "@@";
        }
        ret = ret + xdc.om.$$errors.join("@@");
    }
    return (ret);
}

/*
 *  ======== isCompatible ========
 *  Check compatibility when package rname uses version bvers of package
 *  pname during rname's build but version avers is being used in the
 *  current configuration.
 *
 *  Params:
 *      pname - package name
 *      avers - imported (actual) version of package pname
 *      bvers - version referenced during rname's build
 *      rname - name of package referencing package pname
 *
 *  Returns:
 *      null if versions avers and bvers are compatible; otherwise it returns
 *      a string starting with "Error" or "Warning" that indicates the
 *      failure.
 */
function isCompatible(pname, avers, bvers, rname)
{
//    print("checking compatibility between " + pname + " (vers = " + avers + ") and vers = " + bvers + " used by " + rname);

    if (avers == bvers) {
        return (null);
    }

    var result = {wCount: 0, eCount: 0, msg: ""};

    /* versions differ, check version numbers */
    var ava = avers.split(',');
    var bva = bvers.split(',');

    /* if one is a version number and the other isn't, assume incompatible */
    if (ava == null || bva == null) {
        result.wCount = 1;
        result.msg = "Warning: can't determine version of " + pname
            + " or the version of " + pname + " used to build " + rname;
        return (result);
    }

    /* otherwise, we need to interpret the version number to decide */
    for (var i = 0; i < bva.length; i++) {
        /* convert string digits to numbers */
        var a = ava[i] - 0;
        var b = bva[i] - 0;

        /* if digits differ (or as non-numeric strings they don't match) */
        if (a != b || (isNaN(a - b) && ava[i] != bva[i])) {
            switch (i) {
                case 0: {   /* incompatible releases */
                    result.eCount = 1;
                    result.msg = "Error: re-write of "+ rname + " is required";
                    return (result);
                }

                case 1: {   /* source compatible release */
                    result.eCount = 1;
                    result.msg = "Error: re-build of "+ rname + " is required";
                    return (result);
                }

                case 2: {   /* API radius */
                    if (a < b) {
                        result.wCount = 1;
                        result.msg = "Warning: the version of " + pname
                            + " included in this configuration is older than the version of "
                            + pname + " used to build " + rname;
                        return (result);
                    }
                    break;
                }

                case 3: {   /* binary 100% compatible release */
                    break;
                }
            }
            return (null);
        }
    }

    /* if we get here, the required version is prefix of the avail version */
    return (null);
}

/*
 *  ======== printErrors ========
 *  Print all warnings and error messages accumulated in $$warning and $$errors
 *  arrays.
 */
function printErrors()
{
    /* Error and warning messages are generated initially with ':::' as a
     * separator between fields, so that XGCONF can parse them. When printed
     * ':::' are replaced with ': '.
     */
    if (xdc.om.$$warnings.length > 0) {
        for (var i = 0; i < xdc.om.$$warnings.length; i++) {
            print(xdc.om.$$warnings[i].replace(/\:\:\:/g, ": "));
        }
    }
    if (xdc.om.$$errors.length > 0) {
        for (var i = 0; i < xdc.om.$$errors.length; i++) {
            print(xdc.om.$$errors[i].replace(/\:\:\:/g, ": "));
        }
    }
}

/*
 *  ======== $$usemod ========
 */
function $$usemod( mod, cycles )
{
    mod.$used = true;

    /* We need to know when the module was loaded for the first time, except
     * for cases when the user's script loads a module when we treat that
     * as the time when module was loaded.
     */
    if (!('$$usedPhase' in mod) || xdc.om.$$phase == 2) {
        mod.$$bind('$$usedPhase', xdc.om.$$phase);
    }

    if (xdc.om.$$phase >= 4) {
        print("WARNING: Can't call useModule() now:", mod.$name);
    }

    if (!('$$scope' in mod)) {
        mod.$$bind('$$scope', (xdc.om.$$phase < 3) ? 1 : 0);
    }

    if (!('$$cfgPhase' in mod)) {
        mod.$$bind('$$cfgPhase', 0);
    }

    if (mod.$$cfgPhase == -1 || mod.$$cfgPhase == 2) {
        return (mod);
    }

    if (xdc.om.$$phase < 3) {
        mod.$$bind('$$cfgPhase', 1);
        return mod;
    }
    
    mod.$$bind('$$cfgPhase', -1);
    _myTrace("calling " + mod.$orig.$name + ".module$use", 2, ["moduleUse"]);
    mod.$orig.module$use();

    if (!mod.$hostonly && '$$proxies' in mod && !mod.PROXY$) {
        for each (var p in mod.$$proxies) {
            var pud = mod[p + '$proxy'];
            $$usemod(pud);
            if (pud.delegate$) {
                $$usemod(pud.delegate$, true);
            }
        }
    }

    mod.$$bind('$$cfgPhase', 2);
    return mod;
}

/*
 *  ======== cfgUseModule ========
 *  Use a module in a package
 */
function $$cfgUseModule(qname, cycles)
{
    /* xdc.om.$curpkg contains the name of the current package. We keep track
     * of it to be able to record dependencies between packages. We need to
     * keep saving and retrieving $curpkg here because calls to xdc.module end
     * up calling xdc.loadPackage, where dependencies are recorded. If we
     * didn't change the value in $curpkg when getting the reference to
     * xdc.cfg.Main, we would create an invalid dependency between the package
     * that called xdc.useModule(qname) and 'xdc.cfg'.
     *
     * Afterwards, when calling xdc.module(qname), we need to set $curpkg back
     * to its initial value to correctly record the dependency between the
     * initial $curpkg and qname's package.
     *
     * Finally, when calling $$usemod, $curpkg is set to qname's package
     * because $$usemod may call qname.module$use. We could save $curpkg
     * inside $$usemod but it might be better to keep this part of $curpkg
     * handling here.
     *
     * The value of $curpkg is also changed in closePackages(), when calling
     * module$use for modules used in the user's script phase, and in
     * xdc.loadPackage() before loading schemas.
     */
    _myTrace("xdc.useModule called on " + qname, 2, ["moduleUse"]);
    var saveCurpkg = xdc.om.$curpkg;
    xdc.om.$$bind('$curpkg', undefined);
    var cfgModel = xdc.om['xdc.cfg.Main'];

    /* This lets us call useModule with a Module as a parameter */
    if (typeof qname != 'string') {     /// TEMPORARY HACK
        xdc.om.$$bind('$curpkg', qname.$orig.$package.$name);
        var mod = cfgModel.$private.$$usemod(qname, cycles);
        xdc.om.$$bind('$curpkg', saveCurpkg);
        return (mod);
    }

    xdc.om.$$bind('$curpkg', saveCurpkg);
    var unit = xdc.module(qname);

    if (unit.$spec.isInter()) {
        xdc.om.$$bind('$curpkg', saveCurpkg);
        return (unit);
    }

    xdc.om.$$bind('$curpkg', unit.$orig.$package.$name);
    cfgModel.$private.$$usemod(unit, cycles);
    xdc.om.$$bind('$curpkg', saveCurpkg);

    return unit;
}

/*
 *  ======== _myTrace ========
 */
function _myTrace(msg, level, groups)
{
    groups.push("all");
    utils._tracePrint("xdc: " + msg, "xdc/cfg/Main.xs", "xdc/cfg",
        groups, level);
}
/*
 *  @(#) xdc.cfg; 1, 0, 2, 0,237; 2-22-2010 10:33:11; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

