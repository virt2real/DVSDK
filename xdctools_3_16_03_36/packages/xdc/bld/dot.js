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
 *  ======== dot.js ========
 *  This command generates dot graph specification for a release.
 *
 *  usage: dot.js package-base-dir [output-file]
 *
 *! Revision History
 *! ================
 *! 20-Feb-2008 sasha   removed catching errors, added code convention changes
 */

/* set-up the om */
utils.loadCapsule('xdc/xdc.tci');
        
/* om2.xs capsule accesses xdc.global assuming it's the top-level scope, while
 * xdc.tci sets xdc.global to the local scope of the capsule.
 */
xdc.global = this;
xdc.loadCapsule('xdc/om2.xs');

/* This is where xs executable loads a model, if needed, and then give the
 * control to the user script.
 */
/* -------------------------------------------------------------------------*/
        
xdc.$$make_om('rel');
utils.importFile("rel.tci");
        
/*
 *  ======== main ========
 */
if (arguments.length >= 1) {
    var topdir = arguments.shift();
    var opts = {};
    if (topdir[0] == '-') {
        switch (topdir[1]) {
//          case 'f': {
//              opts.flat = true;
//              topdir = arguments.shift();
//              break;
//          }
            default: {
                print("usage: dot.js package-base-dir [output-file]");
                java.lang.System.exit(1);
            }
        }
    }
    var outputFileName = null;
    if (arguments.length >= 1) {
        outputFileName = arguments.shift();
    }
        
    /* set the package path for the current package under review */
    var ppath = rel.getPackagePath(topdir + '/.xdcenv.mak');
    environment["xdc.path"] = ppath;
    
    /* load java run-time support */
    xdc.loadPackage('xdc.services.intern.cmd');
        
    /* generate the package dependency graph */
    rel.genDot(topdir, outputFileName, opts);
}
/*
 *  @(#) xdc.bld; 1, 0, 2,238; 2-22-2010 10:33:33; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

