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
 *  ======== rcl.js ========
 *
 *  This command performs all file post-processing for a release of a
 *  package.
 *
 *  usage: rcl.js [opts] manifest-file output-tar-file [relScript output-deps]
 *
 *  where
 *      manifest-file is a tar manifest file (i.e., a file containing one
 *          file name per line and is suitable for passing to tar via tar's
 *          -I option),
 *
 *      output-tar-file is the name of the tar file that contains the
 *          post-processed results.
 *
 *      relScript is a Release Model script that can specifies what
 *          post-processing should occur with the specified files,
 *
 *      output-deps is the filename to put relScript dependencies in
 *
 *! Revision History
 *! ================
 *! 20-Feb-2008 sasha   removed catching errors, added code convention changes
 */

var Manifest;

/*
 *  ======== main ========
 */
function main(args)
{
    utils.loadCapsule('xdc/xdc.tci');
        
    /* om2.xs capsule accesses xdc.global assuming it's the top-level scope,
     * while xdc.tci sets xdc.global to the local scope of the capsule.
     */
    xdc.global = this;
    /* setCurPkgBase must be called before loadCapsule is called because
     * setCurPkgBase impacts the path in loadCapsule, when '^' is used.
     */
    xdc.setCurPkgBase(".");
    xdc.loadCapsule('xdc/om2.xs');
        
    /* This is where xs executable loads a model, if needed, and then give the
     * control to the user script.
     */
    /* ----------------------------------------------------------------------*/
                
    xdc.$$make_om('rel');           /* create and name this object model */
        
    /* java run-time functions */
    xdc.loadPackage('xdc.services.intern.cmd');
        
    Manifest = xdc.useModule('xdc.bld.Manifest');
    $om.$$bind('$root', Manifest);
        
    utils.importFile("rcl.tci");
                
    if (args.length >= 1) {
        var manifestFile = args.shift();
                    
        if (args.length < 1) {
            throw new Error("no output file specified (manifest = '"
			    + manifestFile + "'");
        }
        var outputFileName = args.shift();
                    
        var scriptFileName = null;
        if (args.length >= 1) {
            scriptFileName = args.shift();
        }
        if (args.length < 1) {
            throw new Error(
                "no output file for dependencies specified (relScript = '"
                    + scriptFileName + "'");
        }
        var depFileName = args.shift();
                    
        /* compute release name (from the archive file name) */
        var releaseName = outputFileName.replace(/\.tar$/, "");
                
        /* populate the release model from the manifest file */
        rcl.scan(releaseName, manifestFile);
                        
        /* run the user's script */
        if (scriptFileName != null) {
//          print("running release script '" + scriptFileName + "'");
            var spath = ".;" + xdc.curPath();
            var fullName = utils.findFile(scriptFileName, spath, ';');
            if (fullName == null) {
                throw new Error("can't find '" + scriptFileName
                    + "' along the path '" + spath + "'");
            }
            utils.load(fullName);
        }

        /* finalize each imported package */
        if (!config.hasReportedError) {
            for (var i = $om.$packages.length - 1; i >= 0; i--) {
                var pkg = $om.xdc.IPackage.Module($om.$packages[i]);
                pkg.close();
            }
        }
                
        /* the model is now "sealed"; let each package validate */
        if (!config.hasReportedError) {
            for (var i = $om.$packages.length - 1; i >= 0; i--) {
                var pkg = $om.xdc.IPackage.Module($om.$packages[i]);
                pkg.validate();
            }
        }
                        
        /* generate the post-processed files */
        if (!config.hasReportedError) {
            
            /* create release archive output file */
//          print("creating release archive '" + outputFileName + "'");
            rcl.gen(outputFileName);
                
            /* generate dependencies on files used during release processing */
            print("generating rcl dependencies " + depFileName);
            rcl.genDep(outputFileName, depFileName, utils.loadedFiles);
        }
                
        /* allow each imported package to exit */
        if (!config.hasReportedError) {
            for (var i = $om.$packages.length - 1; i >= 0; i--) {
                var pkg = $om.xdc.IPackage.Module($om.$packages[i]);
                pkg.exit();
            }
        }
    }
}

main(arguments);
/*
 *  @(#) xdc.bld; 1, 0, 2,238; 2-22-2010 10:33:33; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

