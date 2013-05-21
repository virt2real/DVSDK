/* 
 *Copyright (c) 2008 Texas Instruments and others.
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
 *  ======== Main.xs ========
 *  Main entry point for the configuro command
 */

/*
 *  ======== opts ========
 *  command line options
 */
var opts = {};

/*
 *  ======== run ========
 *  Main function, executed from the command line. 
 */
function run(cmdr, args)
{
    /* print the usage message if requested */
    if (args.length != 1) {
        cmdr.usage();
        return;
    }

    /* put config parameters in a local copy so gen() can add to them */
    for (var p in this) {
        opts[p] = this[p];
    }

    /* run the command and turn exceptions into one-liners */
    var status;
    try {
        status = this.gen(args[0]);
    }
    catch (e) {
        cmdr.error(e);
    }

    /* if we failed, make sure the generated files do not exist.  If
     * we don't delete these files, make based systems that are forced 
     * to declare the output files ".PRECIOUS" will try to continue 
     * to build using bogus files and won't try to rebuild them.
     */
    if (status != 0) {
        if (opts.output) {
            var tmp = opts.output + "/linker.cmd";
            java.io.File(tmp)["delete"]();
//  if we remove compiler.opt and the failure occurs 
//          tmp = opts.output + "/compiler.opt";
//          java.io.File(tmp)["delete"]();
        }

        /* do a sanity check on the repositories */
        checkRepositories(opts.xdcpath);

        cmdr.error("configuration failed due to earlier errors (status = "
                   + status + "); 'linker.cmd' deleted.");
    }
}

/*
 *  ======== gen ========
 *  Use mkpkg to generate the package, using the template in the "template"
 *  subdirectory.
 */
function gen(infile)
{
    /* check usage */
    if (!infile) {
        throw new Error("missing required parameter 'infile'");
    }

    if (!opts.searchForConfigBld && !opts.target && !opts.configbld) {
        throw new Error("no target named: please use -t, -b, or --cb");
    }

    /* check that the input file exists */
    var infileFile = java.io.File(infile);
    if (!infileFile.exists()) {
        throw new Error("can't open input file '" + infile + "'");
    }

    /* handle legacy .tcf files */
    if (opts.hasTconf) {
        infile = infile.replace(/\.[^.]*$/, '.tcf');
        infileFile = java.io.File(infile);
        if (!infileFile.exists()) {
            throw new Error("can't open .tcf input file '" + infile + "'");
        }
    }

    /* if user has asked for config.bld to be found on package path */
    if (opts.searchForConfigBld && !opts.configbld) {
        /* then set a default for config.bld */
        var configbld = xdc.findFile("config.bld");
        if (configbld) {
            opts.configbld = configbld.replace(/\\/g, '/');
        }
        else {
            throw new Error("no config.bld found along the package path");
        }
    }

    /* set default for output name */
    if (!opts.output) {
        /* get the absolute path to the directory it's in */
        var outputDir = infileFile.getAbsoluteFile().getParent();
        /* convert to slash separators */
        outputDir = (outputDir + '').replace(/\\/g, '/');
        /* strip the directory and filename extension off the input file */
        var outputBase = infile.replace(/^.*\/\\/, '').replace(/\.[^\.]*$/, '');
        /* construct the full path to the output directory */
        opts.output = outputDir + '/' + outputBase;
    }

    /* get user specified XDCPATH package path prefix */
    var xdcpathIn = getXdcPathPrefix();

    /* move -Dconfig.importPath=... to package path */
    if (opts.defines.length > 0) {
        var defines = [];
        for (var i = 0; i < opts.defines.length; i++) {
            var m = opts.defines[i].match(/^config\.importPath=(.*)$/);
            if (m) {
                /* strip quotes and append to package path */
                var path = m[1].replace(/^["']*|["']*$/g, "");
                xdcpathIn += ';' + path;
            }
            else {
                /* keep it as a -D */
                defines.push(opts.defines[i]);
            }
        }
        opts.defines = defines;
    }

    /* convert all repositories to absolute pathnames */
    var File = xdc.module("xdc.services.io.File");
    xdcpathIn = xdcpathIn.split(';');
    var xdcpathOut = [];
    var xdcpathSeen = {};
    for (var i = 0; i < xdcpathIn.length; i++) {
        var path = xdcpathIn[i];

        /* omit empty paths */
        if (!path || path.match(/^\s*$/)) {
            continue;
        }

        /* convert to absolute pathnames */
        var e;
        try {
            path = File.getCanonicalPath(path);
        }
        catch (e) {
            /* badly formed pathname */
            continue;
        }

        /* omit paths we've already used once */
        if (path in xdcpathSeen) {
            continue;
        }

        /* it's a keeper */
        xdcpathSeen[path] = true;
        xdcpathOut.push(path);
    }
    opts.xdcpath = xdcpathOut.join(';');

    /* generate the config package */
    var Main = xdc.module("xdc.tools.mkpkg.Main");
    Main.update = true;
    Main.mkpkg(
        "xdc/tools/configuro/template",
        opts.output,
        infile,
        opts
    );

    /* construct the arguments to build the package */
    var mkTarget = opts.mkPkgOnly ? '.interfaces' : '.configuro';
    var XDCROOT = environment['xdc.root'];
    var cmdarr = [XDCROOT + '/xdc'];
    if (opts.verbose) {
        cmdarr.push('XDCOPTIONS=v');
    }
    cmdarr = cmdarr.concat([
        'XDCPATH=' + opts.xdcpath,
        '--no-print-directory',
        '--directory',
        opts.output,
        mkTarget
    ]);

    /* build it and return the XDC command's exit status */
    return (_localExec(cmdarr));
}

/*
 *  ======== _copy_stream ========
 */
function _copy_stream(ins, outs) {
    var thread = new java.lang.Thread(function() {
        var isr = new java.io.InputStreamReader(ins);
        var br = new java.io.BufferedReader(isr);
        var line;
        while ((line = br.readLine()) != null) {
            outs.println(line);
        }
    });
    thread.start();
    return (thread);
}

/*
 *  ======== _localExec ========
 *  Execute a program. Works around some difficulties in executing the XDC
 *  command using xdc.exec(); we need to output lines as soon as they are
 *  available for long running commands.
 */
function _localExec(cmdarr)
{
    /* generate the name of the XDC command on this OS */
    var os = java.lang.System.getProperty("os.name") + "";
    if (os.match(/^Windows/i)) {
        cmdarr[0] += ".exe";
    }

    /* create the command array */
    var cmdarr_j = java.lang.reflect.Array.newInstance(
        java.lang.String, cmdarr.length);
    for (var i = 0; i < cmdarr.length; i++) {
        cmdarr_j[i] = cmdarr[i];
    }

    /* copy the environment array from the current environment */
    var env   = java.lang.System.getenv();
    var keys  = env.keySet().toArray();
    var env_j = java.lang.reflect.Array.newInstance(
        java.lang.String, keys.length);
    for (var i = 0; i < keys.length; i++) {
        var key = keys[i];
        env_j[i] = key + '=' + env.get(key);
    }

    /* create the process */
    var runtime = java.lang.Runtime.getRuntime();
    var proc = runtime.exec(cmdarr_j, env_j);

    /* create threads to copy the stdout and stderr streams */
    var cpyerr = _copy_stream(proc.getErrorStream(), java.lang.System.err);
    var cpyout = _copy_stream(proc.getInputStream(), java.lang.System.out);

    /* wait for the process to complete */
    var status = proc.waitFor();

    /* wait for the streams to complete */
    cpyerr.join();
    cpyout.join();

    /* return the exit status of the process */
    return (status);
}

/*
 *  ======== getXdcPathPrefix ========
 */
function getXdcPathPrefix()
{
    var result;

    /* use curPathPrefix, if it exists */
    if ("curPathPrefix" in xdc) {
        result = xdc.curPathPrefix();
    }
    else {
        /* otherwise approximate it with XDCPATH */
        result = environment["XDCPATH"];
        if (result == null) {
            result = "";
        }
        else {
            var hat = "" + Packages.xdc.services.global.Path.getCurPkgRoot();
            if (hat.length == 0) {
                var a = result.split(';');
                var b = [];
                for (var i = 0; i < a.length; i++) {
                    if (a[i].indexOf("^") == -1) {
                        b.push(a[i]);
                    }
                }
                result = b.join(';');
            }
            else {
                hat = hat.replace(/\\/g, '/');
                result = result.replace(/\^/g, hat);
            }
        }
    }

    return (result);
}

/*
 *  ======== checkRepositories ========
 */
function checkRepositories(path)
{
    var dirs = path.split(";");
    for each (dir in dirs) {
        checkRepository(dir);
    }
}

/*
 *  ======== checkRepository ========
 */
function checkRepository(dir)
{
    var err = java.lang.System.err;
    var File = java.io.File;

    if (!dir) {
        /* don't warn on empty string */
    }
    else if (!File(dir).exists()) {
        err.println("Warning: directory \"" + dir +
            "\" on package path does not exist");
    }
    else if (File(dir + "/packages").exists()) {
        err.println("Warning: directory \"" + dir +
            "\" on package path has a \"packages\" subdirectory - " +
            "did you mean this instead?");
    }
    else if (File(dir).name == "package" &&
            File(dir, "../packages").exists()) {
        err.println("Warning: directory \"" + dir +
            "\" on package path ends in \"package\" - " +
            "did you mean \"packages\" instead?");
    }
}
/*
 *  @(#) xdc.tools.configuro; 1, 0, 0, 0,151; 11-20-2009 13:26:12; /db/ztree/library/trees/xdctools/xdctools-d08x/src/
 */

