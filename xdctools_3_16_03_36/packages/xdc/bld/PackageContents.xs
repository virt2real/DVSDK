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
 *  ======== PackageContents.xs ========
 */
var _gen = xdc.loadCapsule("_gen.xs");

/*
 *  ======== PackageContents.addLibrary ========
 */
function addLibrary (name, target, libAttrs)
{
    function close(pkg)
    {
        _inheritAttrs(this.lib, pkg);
        var ra = this.lib.attrs.releases;
        ra[ra.length++] = pkg.defaultRelease;

        /* if objects have been specified, add them to the new library */
        _closeObjs(this.lib, this.objects);
    }

    var lib = this.$package.Library.create();

    /* make sure any sub-directory specified will be created */
    _gen.getDir(name, this.$private.dirs);

    lib.name = name;
    lib.target = target;
    lib.attrs = libAttrs;
    if (lib.attrs.suffix == null) {
        lib.attrs.suffix = ".a" + lib.target.suffix;
    }

    /* initialize private library state */
    var priv = lib.$private;
    priv.target = target;
    priv.objects = {};
    priv.name = lib.name + lib.attrs.suffix;
    priv.close = close;
    priv.lib = lib;

    /* ensure that the library name is unique */
    if (this.$private.libraries[priv.name] != null
        || this.$private.dlls[priv.name] != null) {
        throw xdc.$$XDCException(
            "xdc.bld.LIBRARY_EXISTS",
	    "Library '" + priv.name + "' already exists.");
    }
    /* if target is not in the current list of targets, ignore addLibrary  */
    if (xdc.om['xdc.bld.BuildEnvironment'].isInTargetsArray(target) != true) {
        print("Calling print targets in " + this.$package.BuildEnvironment);
        print("Warning: Target '" + target.$name +
            "' is not in the list of build targets, the library '" + priv.name
            + "' cannot be built.\n " +
            this.$package.BuildEnvironment.printBuildTargets());
        return (lib);
    }
        
    this.$private.libraries[priv.name] = lib;

    /* mark this file as a generated file */
    this.$private.generatedFiles[priv.name] = 1;

    return (lib);
}

/*
 *  ======== PackageContents.addAssembly ========
 */
function addAssembly (name, target, platform, attrs)
{
    function close(pkg)
    {
        _inheritAttrs(this.exe, this.asm);
    }
    
    var asm = this.$package.Assembly.create();
    asm.name = name;
    asm.target = target;
    asm.platform = platform;
    asm.attrs = attrs;

    var ext = target.dllExt == null ? (".p" + target.suffix) : target.dllExt;

    var apriv = asm.$private;
    apriv.target = target;
    apriv.name = asm.name + ext;
    apriv.close = close;
    apriv.asm = asm;

    apriv.exe = this.addExecutable(name, target, platform, attrs);

    var epriv = apriv.exe.$private;
    epriv.noasm = false;
    epriv.ext = ext;
    epriv.name = name + epriv.ext;

    this.$private.assemblies[apriv.name] = asm;

    /* mark this file as a generated file */
    this.$private.generatedFiles[apriv.name] = 1;

    return (asm);
}

/*
 *  ======== PackageContents.addExecutable ========
 */
function addExecutable (name, target, platform, progAttrs)
{
    function close(pkg)
    {
        _inheritAttrs(this.prog, pkg);

        /* set prog.attrs.xsopts to union of both tcopts and xsopts */
        var xsopts = this.prog.attrs.xsopts != null
            ? this.prog.attrs.xsopts : "";
	xsopts += this.prog.attrs.tcopts != null
            ? (" " + this.prog.attrs.tcopts) : "";
        if (xsopts != "") {
            this.prog.attrs.xsopts = xsopts;
        }
        
        /* set if prog.attrs.cfgcopts is not defined, use the content of
         * prog.attrs.copts, if any.
         */
        if (this.prog.attrs.cfgcopts == null && this.prog.attrs.copts != null) {
            this.prog.attrs.cfgcopts = this.prog.attrs.copts;
        }

        /* add a default test for this executable; run it with no arguments */
        this.prog.addTest(this.prog.attrs.test);

        /* add this executable to the default release */
        var ra = this.prog.attrs.releases;
        ra[ra.length++] = pkg.defaultRelease;
        
        /* compute the configuration script to use for this executable */
        var cfgScript = this.prog.attrs.cfgScript;

        if (cfgScript === undefined) {
            cfgScript = this.prog.name + ".cfg";
            pkg.$private.cfgs[cfgScript] = cfgScript;
        }
        else if (cfgScript != null) {
            var dot = cfgScript.lastIndexOf(".");
            if (dot <= 0 || cfgScript.substring(dot).indexOf("/") >= 0) {
                cfgScript += ".cfg";
            }
            pkg.$private.cfgs[cfgScript] = cfgScript;
        }
        this.prog.attrs.cfgScript = cfgScript;

        /* if objects have been specified, add them to executable */
        _closeObjs(this.prog, this.objects);
    
        /* close all tests */
        for (var i in this.tests) {
            this.tests[i].$private.close(this.prog);
        }
    }

    /* create a new executable with the specified attributes */
    var prog = this.$package.Executable.create();
    prog.name = name;
    prog.target = target;
    prog.platform = platform;
    prog.attrs = progAttrs;

    /* make sure any sub-directory specified will be created */
    _gen.getDir(name, this.$private.dirs);

    /* initialize private state */
    var priv = prog.$private;
    priv.noasm = true;
    priv.objects = {};
    priv.tests = [];
    if (prog.target.execExt == null) {
        priv.ext = ".x" + prog.target.suffix;
    }
    else {
        /* define some simple macros based on platform names */
        priv.ext = prog.target.execExt;
        if (priv.ext.indexOf('$') != -1) {
            var bld_Utils = xdc.useModule('xdc.bld.Utils');

            var pstat = bld_Utils.parsePlatName(platform);
            priv.ext = bld_Utils.expandString(priv.ext, {
                trgSuffix: prog.target.suffix,
                trgName:   prog.target.name,
                platPName: pstat.platPkgName,
                platIName: pstat.instName
            });
        }
    }
    priv.name = name + priv.ext;

    priv.close = close;
    priv.prog = prog;
    
    /* ensure executable name is unique and add to the list of executables */
    if (this.$private.exeNames[priv.name] != null) {
        throw xdc.$$XDCException(
	    "xdc.bld.EXECUTABLE_EXISTS",
            "Executable '" + priv.name + "' already exists in package '" 
	        + this.name + "'.");
    }
    /* if target isn't in the current list of targets, ignore addExecutable  */
    if (xdc.om['xdc.bld.BuildEnvironment'].isInTargetsArray(target) != true) {
        print("Warning: Target '" + target.$name
                + "' is not in the list of build targets, the executable '"
                + priv.name + "' cannot be built.\n " +
                this.$package.BuildEnvironment.printBuildTargets());
        return (prog);
    }

    /* mark this file as a generated file */
    this.$private.generatedFiles[priv.name] = 1;

    this.$private.exeNames[priv.name] = priv.name;
    this.$private.executables[this.$private.executables.length++] = prog;

    return (prog);
}

/*
 *  ======== PackageContents.addRelease ========
 */
function addRelease (name, releaseAttrs)
{
    function close(pkg)
    {
        /* get "global" package attrs that are undefined by this release */
        _inheritAttrs(this.release, pkg);

        /* add specified files to private file list */
        var oa = this.release.otherFiles;
        for (var i = 0; i < oa.length; i++) {
            this.files[oa[i]] = oa[i];
        }

        if (this.release.attrs.prefix == null) {
            if (pkg.releasePrefix != null) {
                this.release.attrs.prefix = pkg.releasePrefix;
                if (pkg.releasePrefix[0] == '^') {
                    this.release.attrs.prefix =
                        ("." + pkg.name).replace(/[^\.]+/g, "./")
                        + String(pkg.releasePrefix).substring(1);
                }
            }
            else {
                this.release.attrs.prefix = "";
            }
        }

        /* zip implicitly compresses */
        if ("archiver" in this.release.attrs
            && this.release.attrs.archiver == "zip") {
            this.release.attrs.compress = true;
        }
        
        /* to compress or not is controlled by the file's extension */
        if ("compress" in this.release.attrs
            && this.release.attrs.compress == true) {
            this.release.$private.name += ".gz";  
        }
        
        /* replace .tar.gz with .zip, if the archiver is zip */
        if ("archiver" in this.release.attrs
            && this.release.attrs.archiver == "zip") {
            this.release.$private.name =
                this.release.$private.name.replace(/\.tar\.gz$/, ".zip");
        }

        /* create the archive physical name */
        var aname = this.release.attrs.prefix + this.release.$private.name;

        if ((new java.io.File(aname)).isAbsolute()) {
            throw xdc.$$XDCException(
	        "xdc.bld.INVALID_RELEASE_NAME",
                "the release name '" + aname
		    + "' must be relative to package '"
                    + pkg.name + "'s base directory");
        }

        /* mark the archive file as a generated file */
        pkg.$private.generatedFiles[aname] = 1;

        /* make sure any sub-directory specified will be created */
        _gen.getDir(aname, pkg.$private.dirs);

    }

    var release = this.$package.Release.create();
    release.name = name;
    release.otherFiles = [];
    release.attrs = releaseAttrs;

    /* ensure that any release Prefix is a relative path */
    if (releaseAttrs.prefix != null
        && releaseAttrs.prefix != ""
        && (new java.io.File(releaseAttrs.prefix)).isAbsolute()) {
        throw xdc.$$XDCException(
	    "xdc.bld.INVALID_RELEASE_PREFIX",
            "the release prefix '" + releaseAttrs.prefix
                + "' must be a relative path");
    }

    /* initialize private state */
    var priv = release.$private;
    priv.name = name + ".tar";
    priv.close = close;
    priv.release = release;
    priv.files = {
        "package/package.bld.xml": "package/package.bld.xml",
        "package/package.ext.xml": "package/package.ext.xml",
        "package/package.rel.dot": "package/package.rel.dot",
        "package/build.cfg":"package/build.cfg"
    };
    
    /* ensure release name is unique and add to the list of releases */
    if (this.$private.releases[name] != null) {
        throw xdc.$$XDCException(
	    "xdc.bld.RELEASE_EXISTS",
            "Release '" + name + "' already exists.");
    }
    this.$private.releases[name] = release;

    /* mark this file as a generated file */
    this.$private.generatedFiles[priv.name] = 1;

    return (release);
}

/*
 *  ======== PackageContents.addRepository ========
 */
function addRepository(name)
{
    function close(pkg)
    {
        var ra = this.repository.attrs.releases;
        ra[ra.length++] = pkg.defaultRelease;
        for (var i = 0; i < ra.length; i++) {
            var rel = ra[i];
            rel.$private.files[repository.name] = repository.name;
        }
    }

    var repository = this.$package.Repository.create();
    repository.name = name;

    /* initialize private state */
    var priv = repository.$private;
    priv.name = name;
    priv.close = close;
    priv.repository = repository;
    priv.pkg = this;
    priv.packages = {};
    priv.pkgReleases = {};
    
    /* ensure repository name is unique and add to the list of repositories */
    if (this.$private.repositories[name] != null) {
        throw xdc.$$XDCException(
	    "xdc.bld.REPOSITORY_EXISTS",
            "Repository '" + name + "' already exists.");
    }
    this.$private.repositories[name] = repository;

    /* make sure any sub-directory specified will be created */
    this.$private.dirs[name] = name;

    /* mark the directory as being generated to prevent the files in
     * this directory being added to a release with exportAll set to true
     */
    this.$private.generatedFiles[repository.$private.name] = 1;

    return (repository);
}

/*
 *  ======== PackageContents.addScript ========
 */
function addScript (name, scriptAttrs)
{
    function close(pkg)
    {
        if (this.script.attrs.exportSrc != false) {
            var ra = this.script.attrs.releases;
            ra[ra.length++] = pkg.defaultRelease;
        }
        pkg.$private.srcs[this.name] = this.name;

        /* close all tests */
        for (var i in this.tests) {
            this.tests[i].$private.close(this.script);
        }
    }

    var script = this.$package.Script.create();

    /* make sure any sub-directory specified will be created */
    _gen.getDir(name, this.$private.dirs);

    script.name = name;
    script.attrs = scriptAttrs;

    /* initialize private script state */
    var priv = script.$private;
    priv.name = script.name;
    priv.close = close;
    priv.script = script;
    priv.tests = [];
    
    /* ensure that the script name is unique */
    if (this.$private.scripts[priv.name] != null) {
        throw xdc.$$XDCException(
	    "xdc.bld.SCRIPT_EXISTS",
            "Script '" + priv.name + "' already exists.");
    }
        
    this.$private.scripts[priv.name] = script;

    return (script);
}

/*
 *  ======== PackageContents.onInit ========
 *  Called when the singleton PackageContents Module Value is first
 *  created.
 *
 *  Params:
 *      this    the module
 *  Returns
 *      void
 */
function onInit()
{
    function close()
    {
        var pkg = this.pkg;

        /* validate package name */
        if ((pkg.$private.dotcnt = Packages.xdc.services.global.Path.validate(pkg.name)) == -1) {
             throw xdc.$$XDCException(
	         "xdc.bld.INCORRECT_PACKAGE_NAME",
		 "Package name '" + pkg.name 
		     + "' does not match directory name " 
		     + java.lang.System.getProperty("user.dir"));
        }

        /* create the default release for the package, if necessary */
        if (pkg.defaultRelease == null) {
            pkg.defaultRelease =
                pkg.addRelease(pkg.name.replace(/\./g, '_'),
                    {label: "default"});
        }
        else {
            if (pkg.defaultRelease.attrs.label == null) {
                pkg.defaultRelease.attrs.label = "default";
            }
        }
    
        /* ensure cfgDir and libDir ends with "/" */
        pkg.cfgDir = (pkg.cfgDir + "/").replace(/\/\//g, "/");
        pkg.libDir = (pkg.libDir + "/").replace(/\/\//g, "/");
        pkg.relDir = (pkg.relDir + "/").replace(/\/\//g, "/");
        
        /* create cfgDir and libDir, if necessary */
        var dir = new java.io.File(pkg.cfgDir);
        if (!(dir.exists() && dir.isDirectory()) && !dir.mkdirs()) {
            throw xdc.$$XDCException(
	        "xdc.bld.CREATE_DIR_ERROR",
                "can't create configuration directory " + pkg.cfgDir);
        }
        dir = new java.io.File(pkg.libDir);
        if (!(dir.exists() && dir.isDirectory()) && !dir.mkdirs()) {
            throw xdc.$$XDCException(
	        "xdc.bld.CREATE_DIR_ERROR",
                "can't create library directory " + pkg.libDir);
        }
        dir = new java.io.File(pkg.relDir);
        if (!(dir.exists() && dir.isDirectory()) && !dir.mkdirs()) {
            throw xdc.$$XDCException(
	        "xdc.bld.CREATE_DIR_ERROR",
                "can't create release directory " + pkg.relDir);
        }
    
        /* add cfgDir and libDir to list of directories */
        pkg.$private.dirs[pkg.cfgDir] = pkg.cfgDir;
        pkg.$private.dirs[pkg.libDir] = pkg.libDir;
        pkg.$private.dirs[pkg.relDir] = pkg.relDir;
    
        /* also add 'package/{external,internal}' to contain gen'd headers */
        dir = "package/internal/";
        pkg.$private.dirs[dir] = dir;
        dir = "package/external/";
        pkg.$private.dirs[dir] = dir;

        /* close all libraries */
        for (var i in pkg.$private.libraries) {
            pkg.$private.libraries[i].$private.close(pkg);
        }

        /* close all scripts */
        for (var i in pkg.$private.scripts) {
            pkg.$private.scripts[i].$private.close(pkg);
        }
    
        /* close all assemblies */
        for (var i in pkg.$private.assemblies) {
            pkg.$private.assemblies[i].$private.close(pkg);
        }
    
        /* close all executables */
        for (var i = 0; i < pkg.$private.executables.length; i++) {
            pkg.$private.executables[i].$private.close(pkg);
        }

        /* accumulate all targets used; these are used during makefile
         * generation and referenced in the generated XML file to do
         * target versioning
         */
        var targs = {};
        for (var i in pkg.$private.libraries) {
            targ = pkg.$private.libraries[i].target;
            targs[targ.suffix] = targ;
        }
        for (var i in pkg.$private.dlls) {
            targ = pkg.$private.dlls[i].target;
            targs[targ.suffix] = targ;
        }
        for (var i = 0; i < pkg.$private.executables.length; i++) {
            targ = pkg.$private.executables[i].target;
            targs[targ.suffix] = targ;
        }
        pkg.$private.targets = targs;

        /* add otherSrcs to srcs */
        for (var i = 0; i < pkg.otherSrcs.length; i++) {
            pkg.$private.srcs[pkg.otherSrcs[i]] = pkg.otherSrcs[i];
        }

        /* close all repositories */
        for (var i in pkg.$private.repositories) {
            pkg.$private.repositories[i].$private.close(pkg);
        }

        /* close all releases */
        for (var i in pkg.$private.releases) {
            pkg.$private.releases[i].$private.close(pkg);
        }
    }

    /*
     *  ======== gen ========
     *  Called by bld.js to generate all makefiles, dependencies, and
     *  any other "pre-build time" generated files.  This method is called
     *  after the user's build script runs but before any build occurs.
     *
     *  Params:
     *      out     output stream for generated makefile (java.io.Writer)
     *      args    arguments array passed to user's build script
     *  Returns
     *      void
     *  Throws
     *      exceptions thrown are for fatal errors
     */
    function gen(out, args) {
        var pkg = this.pkg; /* the PackageContents module object */
        
        var _Clock = xdc.useModule("xdc.services.global.Clock");
        
        /* do last pass over private model prior to generation */
        pkg.$private.close();    
    
        /* do any last minute checking (e.g., all required params are set) */
        
        /* generate package.mak and any other pre-build-time files */
        _gen.mkMake(pkg, out);
    
        _Clock.print("bld: package.mak generation complete.");
        
        /* generate project files for debuggers */
        _gen.mkProj(pkg, out);

        _Clock.print("bld: project generation complete.");
        
        /* generate script to initialize build info in CFG model */
        _gen.mkPkgBuild(pkg, "package/build.cfg");
        _Clock.print("bld: config data generation complete.");
        
        /* generate an XML representation of the private state */
        _gen.mkXML(pkg, "package/package.bld.xml");
        _Clock.print("bld: XML data generation complete.");
    }

    this.attrs = {profile: "release"};

    /* initialize private state */
    var priv = this.$private;   /* private package state */

    priv.scripts = {};
    priv.libraries = {};
    priv.repositories = {};
    priv.dlls = {};
    priv.assemblies = {};
    priv.executables = [];      /* array ensures tests run in same order */
    priv.exeNames = {};
    priv.releases = {};
    priv.dirs = {};
    priv.srcs = {};
    priv.generatedFiles = {"package.mak": 1};
    priv.makefiles = [{name:"package.mak", src:"package.bld"}];
    priv.copyGoals = {};
    priv.cfgs = {};

    /* private methods that we don't want user scripts to see */
    priv.gen   = gen;
    priv.close = close;
    priv.pkg   = this;
}

/*
 *  ======== _closeObjs ========
 */
function _closeObjs(goal, objects)
{
    for (var i in objects) {
        _inheritAttrs(objects[i], goal);
    }
}

/*
 *  ======== _inheritAttrs ========
 *  copy params from from.attrs to corresponding undefined to.attrs.
 */
function _inheritAttrs(to, from)
{
    /* define all undefined or 'null' to params as from params */
    for (var name in to.attrs) {
        if (to.attrs[name] == null) {
            if ((name in from.attrs) && from.attrs[name] !== undefined) {
                to.attrs[name] = from.attrs[name];
            }
        }
    }
}
/*
 *  @(#) xdc.bld; 1, 0, 2,238; 2-22-2010 10:33:32; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

