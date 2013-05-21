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
 */

var Big = xdc.loadCapsule('Big.xs');
var Pkg = xdc.loadCapsule('Pkg.xs');
var Gbl = xdc.loadCapsule('Gbl.xs');
var Toc = xdc.loadCapsule('Toc.xs');
var Index = xdc.loadCapsule('Index.xs');

var _popt = false;
var _ropt = false;
var _aopt = false;
var _sopt = false;
var _bopt = false;
var _hopt = false;
var _nopt = false;
var _iopt = false;
var _qopt = false;

var XDCPATH = environment['xdc.path'];


/*
 *  ======== run ========
 */
function run(cmdr, args)
{
    var title = null;
    var ai = 0;

    _popt = this.popt;
    _ropt = this.ropt;
    _aopt = this.aopt;
    _sopt = this.sopt;
    _bopt = this.bopt;
    _hopt = this.hopt;
    _nopt = this.nopt;
    _iopt = this.iopt;
    _qopt = this.qopt;

    if (this.language != null) {
        print('The -l command option has been deprecated');
    }
    if (this.lopt) {
        print('The -L command option has been deprecated');
    }

    if (_ropt) {
        _popt = true;
    }

    if (this.title) {
        title = this.title;
    }
    var start = this.start;

    var outdir;
    if (this.outdir) {
        outdir = this.outdir + java.io.File.separator;
    }
    else {
        outdir = (_popt ? 'cdoc' : 'package/cdoc') + java.io.File.separator;
    }

    java.io.File(outdir).mkdirs();

    if (_iopt) {
        Toc.genToc(outdir);
        Index.gen(title, start, outdir, false);
        return;
    }

    /* -A option documents the entire XDCPATH */
    if (_aopt) {
        _popt = _ropt = true;
        
        /* check off all the directories that were listed explicitly */
        var dupes={};
        for (i=ai ; i < args.length; i++) {
            dupes[String(java.io.File(args[i]).getCanonicalPath())] = true;
        }

        /* add all the repositories in the package path */
        var paths = XDCPATH.split(';');
        for (var i in paths) {
            /* or at least, if they aren't there already */
            if (paths[i]) {
                var cpath = String(java.io.File(paths[i]).getCanonicalPath());
                if (!(cpath in dupes)) {
                    args.$add(cpath);
                }
            }
        }
    }

    var dirs = [];
    if (!_popt) {
        dirs.push('.');
    }
    else {
        for ( ; ai < args.length; ai++) {
            dirs.push(args[ai]);
        }
    }


    /* find package dirctories */
    var pkgdirs = [];

    for each (var d in dirs) {
        if (!java.io.File(d).exists()) {
            print("can't find directory " + d);
            continue;
        }

        if (_ropt) {
            Gbl.findRootedPackageDirs(String(java.io.File(d).getCanonicalPath()),
                                      java.io.File(d), pkgdirs);
        }
        else {
            if (Gbl.isPackageDir(d)) {
                pkgdirs.push(d);
            }
        }
    }

    if (pkgdirs.length == 0) {
        print('*** no packages found ***');
        return;
    }

    _copyAppFiles(outdir);

    /* generate package.doc.xml for all packages */
    for each (var d in pkgdirs) {
        Pkg.gen(d, outdir, dirs, {srcFlg: _sopt, msgFlg: !_qopt, nodFlg:_nopt});
    }

    if (!_hopt) {
        Toc.genToc(outdir);
        Index.gen(title, start, outdir, false);
    }

    if (_bopt) {
        Big.gen(title, outdir, {msgFlg: true});
    }
}

/*
 *  ======== _copyAppFiles ========
 */
function _copyAppFiles(outdir)
{
    java.io.File(outdir).mkdirs();
    var FILEDIR = xdc.findFile(Gbl.FILEDIR);
    var fList = java.io.File(FILEDIR).list();
    for each (var f in fList) {
        if (!(java.io.File(FILEDIR + '/' + f).isDirectory())) {
            Gbl.copyFile(FILEDIR + '/' + f, outdir);
        }
    }
}


