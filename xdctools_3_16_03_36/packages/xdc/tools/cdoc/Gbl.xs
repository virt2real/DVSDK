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
 *  ======== Gbl.xs ========
 */

var DOCTYPE = '<!DOCTYPE HTML PUBLIC "-//W3C//DTD HTML 4.01 Transitional//EN" "http://www.w3.org/TR/html4/loose.dtd">';
var FILEDIR = 'xdc/tools/cdoc/files/';
var SP = '&nbsp;';
var TABWIDTH = 4;

var SPEC_SYN = 'synopSpec';
var META_SYN = 'synopMeta';
var TARG_SYN = 'synopTarg';

function DEBUG( expr ) { out.println('top.debug(' + expr + ')'); }

var _opts;
var _outdir;
var _outstr;
var _path;
var _pkgNode;
var _root;
var _unitNode;

/*
 *  ======== copyFile ========
 */
function copyFile(srcPath, destDir)
{
    var srcFile = java.io.File(srcPath);
    var destFile = java.io.File(destDir + '/' + srcFile.getName());

    Packages.xdc.services.global.Host.copyFile(srcFile, destFile);
}

/*
 *  ======== decode =========
 */
function decode( s )
{
    return '' + java.net.URLDecoder.decode(s, 'UTF-8');
}

/*
 *  ======== deepCopyFiles ========
 */
function deepCopyFiles(indir, outdir)
{
    Packages.xdc.services.global.Host.deepCopyFiles(java.io.File(indir), java.io.File(outdir));
}

/*
 *  ======== findDocXmlDirs ========
 */
function findDocXmlDirs(dir, res)
{
    for each (var f in dir.listFiles()) {

        if (f.isFile()) continue;

        if (f.getName() != 'package') {
            findDocXmlDirs(f, res);
            continue;
        }

        for each (var f2 in f.listFiles()) {
            if (f2.getName() == 'package.doc.xml') {
                res.push(String(dir.getCanonicalPath()));
                break;
            }
        }
    }
}

/*
 *  ======== findPackageDirs ========
 */
function findPackageDirs(dir, res)
{
    for each (var f in dir.listFiles()) {

        if (f.isFile()) continue;

        if (f.getName() != 'package') {
            findPackageDirs(f, res);
            continue;
        }

        for each (var f2 in f.listFiles()) {
            var fn = String(f2.getName());
            if (fn.match(/^(.+)\.sch$/)) {
                res.push(String(dir.getCanonicalPath()));
                break;
            }
        }
    }
}

/*
 *  ======== findRootedPackageDirs ========
 */
function findRootedPackageDirs(root, dir, res)
{
    for each (var f in dir.listFiles()) {

        if (f.isFile()) continue;

        if (f.getName() != 'package') {
            findRootedPackageDirs(root, f, res);
            continue;
        }

        for each (var f2 in f.listFiles()) {
            var fn = String(f2.getName());
            var m = fn.match(/^(.+)\.sch$/);
            if (m) {
                var pn = m[1];
                var ppath = String(dir.getPath());
                var pr = getPackageRoot(ppath, pn);
                if (pr && pr == root) {
                    res.push(String(dir.getCanonicalPath()));
                }
                break;
            }
        }
    }
}

/*
 *  ======== genRowB ========
 */
function genRowB()
{
    _outstr.println('<div class="xdocSynSpacer">&nbsp;</div>');
}

/*
 *  ======== genRowC ========
 */
function genRowC( code )
{
    _outstr.println('<div class="xdocSynCode">');
    _outstr.println(decode(code));
    _outstr.println('</div>');
}

/*
 *  ======== getPackageRoot ========
 */
function getPackageRoot(pkgDir, pname)
{
    var pn = pname;
    if (!pn) {
        pn = getPackageName(pkgDir);
    }
    if (pn) {
        var proot = pkgDir + '/..';
        for (var i = 0; (i = pn.indexOf('.', i) + 1) > 0; ) {
            proot += '/..';
        }
        return (String(java.io.File(proot).getCanonicalPath()));
    }
    return (null);
}

/*
 *  ======== getPackageName ========
 */
function getPackageName(pkgDir)
{
    for each (var f in java.io.File(pkgDir).listFiles()) {

        if (f.isFile()) continue;

        if (f.getName() != 'package') {
            continue;
        }

        for each (var f2 in f.listFiles()) {
            var fn = String(f2.getName());
            if (fn.match(/^(.+)\.sch$/)) {
                return (fn.substr(0, fn.lastIndexOf('.')));
            }
        }
    }
    return (null);
}

/*
 *  ======== hasDoc ========
 */
function hasDoc( node )
{
    return (node.docSect.(@name != 'details').length() ||
            node.docSect.(@name == 'details').docPara.length() > 1);
}

/*
 *  ======== hasMetaSyn ========
 */
function hasMetaSyn( node )
{
    return node.synopMeta.length() > 0;
}

/*
 *  ======== hasSpecSyn ========
 */
function hasSpecSyn( node )
{
    return node.synopSpec.length() > 0;
}

/*
 *  ======== hasTargSyn ========
 */
function hasTargSyn( node )
{
    return node.synopTarg.length() > 0;
}

/*
 *  ======== indent ========
 */
function indent( tabs )
{
    return '<tt>' + spaces(tabs * TABWIDTH) + '</tt>';
}

/*
 *  ======== isPackageDir ========
 */
function isPackageDir(dir)
{
    for each (var f in java.io.File(dir).listFiles()) {

        if (f.isFile()) continue;

        if (f.getName() != 'package') {
            continue;
        }

        for each (var f2 in f.listFiles()) {
            var fn = String(f2.getName());
            if (fn.match(/^(.+)\.sch$/)) {
                return (fn.substring(0, fn.lastIndexOf('.')));
            }
        }
    }
    return (null);
}

/*
 *  ======== mkCode ========
 */
function mkCode( lNode )
{
    return indent(lNode.@tab) + decode(lNode.@content);
}

/*
 *  ======== opts ========
 */
function opts( o )
{
    if (o !== undefined) _opts = o;
    return _opts;
}

/*
 *  ======== outdir ========
 */
function outdir( od )
{
    if (od !== undefined) _outdir = od;
    return _outdir;
}

/*
 *  ======== outstr ========
 */
function outstr( os )
{
    if (os !== undefined) _outstr = os;
    return _outstr;
}

/*
 *  ======== path ========
 */
function path( p )
{
    if (p !== undefined) _path = p;
    return _path;
}

/*
 *  ======== pkgNode ========
 */
function pkgNode( p )
{
    if (p !== undefined) _pkgNode = p;
    return _pkgNode;
}

/*
 *  ======== root ========
 */
function root( r )
{
    if (r !== undefined) _root = r;
    return _root;
}

/*
 *  ======== spaces ========
 */
function spaces( n )
{
    res = '';
    for (var i = 0; i < n; i++) res += SP;

    return res;
}

/*
 *  ======== span ========
 */
function span( cls, data )
{
    return '<span class="' + cls + '">' + String(data) + '</span>';
}

/*
 *  ======== sprintf ========
 */
function sprintf( fmt )
{
    res = fmt;
    
    for (var i = 1; i < arguments.length; i++) {
        var a = arguments[i].replace(/\$/g, '$$');
        var r = RegExp('\\$' + i, 'g');
        res = res.replace(r, a);
    }

    return res.replace(/\$\$/g, '$');
}

/*
 *  ======== unitNode ========
 */
function unitNode( u )
{
    if (u !== undefined) _unitNode = u;
    return _unitNode;
}


