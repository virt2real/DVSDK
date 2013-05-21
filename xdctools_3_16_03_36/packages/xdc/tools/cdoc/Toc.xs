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
 *  ======== Toc.xs ========
 */

var Gbl = xdc.loadCapsule('Gbl.xs');
var Out = xdc.loadCapsule('Out.xs');
var Pag = xdc.loadCapsule('Pag.xs');

var tocPkgs = [];
var tocPkgNames = [];

function PL( s ) { Gbl.outstr().println(s); }

/*
 *  ======== genToc ======== 
 */
function genToc(outdir)
{
    print('Generating table of contents ...');

    var pkgdirs = [];
    Gbl.findDocXmlDirs(java.io.File(outdir), pkgdirs);

    _getTocPkgs(pkgdirs);

    /* our toc */
    Gbl.outstr(new Out.Stream(outdir + '/toc.xml'));
    _genPageTop();
    var gtree = _bldGroups();
    _genAllPkgs();
    _genGroups(gtree, "")
    _genPageSuf();
    Gbl.outstr().close();

    /* eclipse toc */
    Gbl.outstr(new Out.Stream(outdir + '/eclipse_toc.xml'));
    _genPageTop();
    for each (var pName in tocPkgNames) {
        _genPkgTopic(pName, pName);
        _genPkg(pName);
        PL('</topic>');
    }
    _genPageSuf();
    Gbl.outstr().close();

    /* all-packages */
    _genAllPkgsPage(outdir);
}

/*
 *  ======== _bldGroups ========
 */
function _bldGroups()
{
    var grpTree = [];

    for each (var pkg in tocPkgs) {
	var pnarr = pkg.name.split('.');
	var gtree = grpTree;
	for (var j = 0; j < pnarr.length; j++) {
	    var elem = pnarr[j];
	    if (elem in gtree) {
		gtree = gtree[elem]
	    }
	    else {
		gtree.push(elem);
		gtree = gtree[elem] = [];
	    }
	}
    }
    return grpTree;
}

/*
 *  ======== _genAllPkgs ========
 */
function _genAllPkgs()
{
    PL('<topic class="toc-pkgs" label="all packages" href="all-packages.html">');
    for each (var pName in tocPkgNames) {
        _genPkgTopic(pName, pName);
        _genUnits(tocPkgs[pName]);
        PL('</topic>');
    }
    PL('</topic>');
}

/*
 *  ======== _genAllPkgsPage ========
 */
function _genAllPkgsPage(outdir)
{
    Gbl.outstr(new Out.Stream(outdir + '/all-packages.html'));
    Gbl.root('./');
    Gbl.pkgNode(null);
    Pag.genPrefix("All Packages");
    Pag.genHdr(new XML('<group name="all packages"/>'), null, null, null);
    Pag.genSynTabBeg('xdocSynX');

    for (var i = 0; i < tocPkgNames.length; i++) {
        var pName = tocPkgNames[i];
        var link = Gbl.sprintf("<a class='xdocSynGo' href='$1/package.html' title='$2'>$3;</a>",
            pName.replace(/\./g, '/'),
            pName,
            Gbl.span('xdoc-id', pName)
        );
        Gbl.genRowC(Gbl.sprintf('$1 $2', Gbl.span('xdoc-kw1', 'package'), link));
        PL(Gbl.sprintf("<div class='xdocSynSum'>//&nbsp;$1</div>", Gbl.decode(tocPkgs[pName].summary)));
    }

    Pag.genSynTabEnd();
    Pag.genSuffix();
    Gbl.outstr().close();
}

/*
 *  ======== _genDecls ========
 */
function _genDecls(unit)
{
    for (var i = 0; i < unit.decls.length; i++) {

        var decl = unit.decls[i];
        PL('<topic class="toc-id" label="' + decl.name + '" href="' + decl.href + '" title="' + decl.title + '"/>');
    }
}

/*
 *  ======== _genGroups ========
 */
function _genGroups(gtree, pre)
{
    if (gtree.length) {
        gtree.sort();
        for (var i = 0; i < gtree.length; i++) {
	    var elem = gtree[i];
	    if (elem in gtree) {
                var qelem = pre ? (pre + '.' + elem) : elem;
                var isPkg = tocPkgs[qelem] != undefined;
                if (isPkg) {
                    _genPkgTopic(qelem, elem);
                }
                else {
                    PL('<topic class="toc-id" label="' + elem + '">');
                }
	        _genGroups(gtree[elem], qelem)
                if (isPkg) {
                    _genPkg(qelem);
                }
                PL('</topic>');
	    }
        }
    }
}

/*
 *  ======== _genPageSuf ========
 */
function _genPageSuf()
{
    PL('</toc>');
}

/*
 *  ======== _genPageTop ========
 */
function _genPageTop()
{

    PL('<?xml version="1.0"?>');
    PL('<?xml-stylesheet type="text/xsl" href="toc.xsl"?>');
    PL('<toc label="XDC Packages" topic="packages.html">');
}

/*
 *  ======== _genPkg ======== 
 */
function _genPkg(pname)
{
    var pkg = tocPkgs[pname];
    if (pkg.units.length) {
        _genUnits(pkg);
    }
}

/*
 *  ======== _genPkgTopic ======== 
 */
function _genPkgTopic(pname, label)
{
    var pre = pname.replace(/\./g, '/') + '/';    
    PL('<topic class="toc-id" label="' + label + '" href="' + pre + 'package.html" title="package ' + pname + '">');
}

/*
 *  ======== _genUnits ========
 */
function _genUnits(pkg)
{
    for (var i = 0; i < pkg.units.length; i++) {

	var unit = pkg.units[i];

        PL('<topic class="toc-id" label="' + unit.name + '" href="' + unit.href + '" title="' + unit.title + '">');
/*        
        if (unit.decls.length) {
            _genDecls(unit);
        }
*/
        PL('</topic>');
    }
}

/*
 *  ======== _getTocPkgs ========
 *
 *  Return a package name-keyed hash of packages in pkgdirs
 *
 */
function _getTocPkgs(pkgdirs)
{
    tocPkgs = [];
    tocPkgNames = [];
    for each (var d in pkgdirs) {
        var pkgNode = xdc.loadXML(d + '/package/package.doc.xml');
        if (pkgNode.@nodoc == '1') {
            continue;
        }
        var units = _getTocUnits(pkgNode);
        var pkg = {};
        pkg.name = '' + pkgNode.@name;
        pkg.summary = '' + pkgNode.@summary;
        pkg.units = units;
        tocPkgNames.push(pkg.name);
        tocPkgs[pkg.name] = pkg;
    }
    tocPkgNames.sort();
}

/*
 *  ======== _getTocUnits ========
 */
function _getTocUnits(pNode)
{
    var unitArr = [];

    var name = '' + pNode.@name;
    var pre = name.replace(/\./g, '/') + '/';
    for each (var uNode in pNode.unit) {
        if (uNode.@nodoc == '1') {
            continue;
        }
        var unit = {};
        unit.name = '' + uNode.@name;
        unit.href = pre + unit.name + '.html';
        unit.title = _mkTitle(uNode, pNode);
/*
        unit.decls = [];
        for each (var gNode in uNode.group) {
            for each(var dNode in gNode.decl) {
                if (dNode.@external == '0' || dNode.@spacer == '1' || dNode.@nodoc == '1') {
                    continue;
                }
                var decl = {};
                decl.name = '' + dNode.@name;
                decl.href = pre + uNode.@name + '.html#' +
                            dNode.@anchor; 
                decl.title = _mkTitle(dNode, uNode);
                unit.decls.push(decl);
            }
        }
        unit.decls.sort(_objNameCompare);
*/
        unitArr.push(unit);
    }
    unitArr.sort(_objNameCompare);
    return (unitArr);
}

/*
 *  ======== _mkTitle ========
 */
function _mkTitle(node, scope)
{
    var title = '';
    if (node.@metaonly == '1') {
        title += 'metaonly ';
    }
    if (node.@kind != 'fxn') {
        title += node.@kind + ' ';
    }
    title += scope.@name + '.' + node.@name;
    if (node.@kind == 'fxn') {
        title += '( )';
    }
    return title;
}

/*
 *  ======== _objNameCompare ========
 *
 *  Compare function for sorting names of units and decls
 *
 */
function _objNameCompare(obj1, obj2)
{
    var name1 = obj1.name.toUpperCase();
    var name2 = obj2.name.toUpperCase();
    if (name1 < name2) {
        return (-1);
    }
    if (name1 > name2) {
        return (1);
    }
    else {
        /* if equal, put upper case first */
        var ch1 = obj1.name.substr(0, 1);
        var ch2 = obj2.name.substr(0, 1);
        if (ch1.toUpperCase() == ch2) {
            return (1);
        }
        if (ch2.toUpperCase() == ch1) {
            return (-1);
        }
    }
    return (0);
}


/*
 *  ======== inToc ========
 */
function inToc(pname)
{
    return (pname in tocPkgs);
}

/*
 *  ======== getFirstPkg ========
 */
function getFirstPkg()
{
    if (tocPkgNames.length) {
        return (tocPkgNames[0]);
    }
    else {
        return ('');
    }
}

