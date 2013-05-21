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
 *  ======== Uni.xs ========
 */

var Dcl = xdc.loadCapsule('Dcl.xs');
var Doc = xdc.loadCapsule('Doc.xs');
var Gbl = xdc.loadCapsule('Gbl.xs');
var Grp = xdc.loadCapsule('Grp.xs');
var Out = xdc.loadCapsule('Out.xs');
var Pag = xdc.loadCapsule('Pag.xs');
var Src = xdc.loadCapsule('Src.xs');
var Syn = xdc.loadCapsule('Syn.xs');
var Txt = xdc.loadCapsule('Txt.xs');
var Xml = xdc.loadCapsule('Xml.xs');

var _pkgDir;
var _unitNodeList;

function PL( s ) { Gbl.outstr().println(s); }

/*
 *  ======== gen ========
 */
function genAll( uNodeList, pDir )
{
    _pkgDir = pDir;
    _unitNodeList = uNodeList;

    var pos = 0;

    for each (var uNode in uNodeList) {
        Gbl.unitNode(uNode);
        _genBody(uNode, pos++);
    }

    /* release memory */
    Gbl.unitNode(null);
    _unitNodeList = undefined;
}

/*
 *  ======== _genBody ========
 */
function _genBody( uNode, pos )
{
    Gbl.outstr(new Out.Stream(_pkgDir + '/' + uNode.@name + '.html'));

    var left = pos && _unitNodeList[pos - 1] ? _unitNodeList[pos - 1] : null;
    var right = _unitNodeList[pos + 1] ? _unitNodeList[pos + 1] : null;
    
    Pag.genPrefix(String(uNode.@kind) + ' ' + Gbl.pkgNode().@name +
                  '.' + uNode.@name, Gbl.decode(uNode.@summary));
    Pag.genHdr(uNode, left, Gbl.pkgNode(), right);

    Pag.genToc(uNode);
    Doc.genBrief(uNode);

    _genInfo(uNode);

    if (uNode.@kind == 'interface') {
        _genSynop(uNode, Gbl.SPEC_SYN);
    }
    if (Gbl.hasTargSyn(uNode)) {
        _genSynop(uNode, Gbl.TARG_SYN);
    }
    if (Gbl.hasMetaSyn(uNode)) {
        _genSynop(uNode, Gbl.META_SYN);
    }
    if (uNode.@kind == 'module') {
        _genSynop(uNode, Gbl.SPEC_SYN);
    }
    
    if (Gbl.hasDoc(uNode)) {
        Doc.genAll(uNode);
    }
    
    _genElems(uNode);

    Pag.genSuffix();
    Gbl.outstr().close();
}

/*
 *  ======== _genElems ========
 */
function _genElems( uNode )
{
    PL('<div id="xdocElems">');
    for each (var gNode in uNode.group) {
        Grp.genElem(gNode, uNode);
        for each (var dNode in gNode.decl) {
            if (dNode.@spacer == '1') continue;
            Dcl.gen(dNode, uNode);
        }
    }
    PL('</div>');
}

/*
 *  ======== _genInfo ========
 */
function _genInfo( uNode )
{
    Pag.genSpecFile(Gbl.unitNode(), 'summary');
    Pag.genSynTabBeg('xdocSynX');

    for each (var ln in uNode.specInfo.line) {
        if (ln.@blank == '1') {
            Gbl.genRowB();
        }
        else if (ln.@comment.length()) {
            PL("<div class='xdocSynSum'>" + Gbl.indent(ln.@tab) + "//&nbsp;" + Gbl.decode(ln.@comment) + "</div>");
        }
        else {
            Gbl.genRowC(Gbl.mkCode(ln));
        }
    }
    Pag.genSynTabEnd();
}


/*
 *  ======== _genSynop ========
 */
function _genSynop( uNode, sName )
{
    Syn.genPrefix(uNode, sName);

    var sNode = uNode[sName];
    var last = sNode.line.length() - 1;
    
    if (last) {
        for (i = 0; i < last; i++) {
            if (sNode.line[i].@blank == '1') {
                Gbl.genRowB();
            }
            else {
                Gbl.genRowC(Gbl.mkCode(sNode.line[i]));
            }
        }
    }
    else {
        Gbl.genRowC(Gbl.mkCode(sNode.line[0]));
    }

    for each (var gNode in uNode.group) {
        if (Grp.hasUnitSynop(gNode, sName)) {
            Grp.genUnitSynop(gNode, sName);
        }    
    }

    if (last) {
        Gbl.genRowC(Gbl.mkCode(sNode.line[last]));
    }
    else {
        Gbl.genRowB();
    }

    Syn.genSuffix();
}
