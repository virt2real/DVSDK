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
 *  ======== Syn.xs ========
 */

var Gbl = xdc.loadCapsule('Gbl.xs');
var Pag = xdc.loadCapsule('Pag.xs');

function PL( s ) { Gbl.outstr().println(s); }

var _curId = 1;

/*
 *  ======== genLines ========
 */
function genLines( sNode, tab, node, elemFlg )
{
    if (sNode.length() == 0) return;

    var pre = Gbl.indent(tab);
    var sumText = null;
    var sumLine = null;
    var eSkip = false;
    var defAnc = null;
    var defAlt = null;

    if (node.name() == 'decl') {
        defAnc = String(node.@anchor);
        defAlt = String(node.@altext);
        sumText = "//&nbsp;" + node.@summary;
        sumLine = "<div class='xdocSynSum'>" + pre + Gbl.decode(sumText) + "</div>";
    }

    if (!elemFlg && node.name() == 'group') {
        defAnc = String(node.@name).replace(/ /g, '_');
        defAlt = String(node.@name);
    }

    sumLine = null;

    for each (var ln in sNode.line) {

        if (ln.@elem.length()) {
            eSkip = ln.@elem == '1';
            continue;
        }
        if (!elemFlg && eSkip) {
            continue;
        }

        if (ln.@blank == '1' && (elemFlg || ln.@always == '1')) {
            Gbl.genRowB();
            continue;
        }

        var anc = defAnc;
        var alt = defAlt;

        if (ln.@anchor.length()) {
            anc = String(ln.@anchor);
            alt = String(ln.@altext);
        }
        if (!elemFlg && ln.@comment.length()) {
            sumText = "//&nbsp;" + ln.@comment;
        }
        if (ln.@content.length()) {
            var cs = elemFlg ? _remGo(Gbl.mkCode(ln)) : _repGo(Gbl.mkCode(ln), anc, alt, sumText);
            Gbl.genRowC(pre + cs);
            sumText = null;
        }
        if (elemFlg && ln.@comment.length()) {
            PL("<div class='xdocSynSum'>" + pre + Gbl.indent(ln.@tab) + "//&nbsp;" + Gbl.decode(ln.@comment) + "</div>");
            sumLine = null;
        }

        if (sumLine) {
            PL(sumLine);
            sumLine = null;
        }
    }

    if (node.name() == 'group' || node.name() == 'decl' && node.@name == 'create' && sNode.name() == 'synopTarg') {
        return;
    }

    if (sumLine) {
        PL(sumLine);
    }

// FIX Gbl.sprintf !!!!
//    Gbl.TRACE = true;
//    PL(Gbl.sprintf("<div class='xdocSynSum'>$1//&nbsp;$2$3</div>", pre, Gbl.decode(node.@summary), link));
//    Gbl.TRACE = false;

}

/*
 *  ======== genPrefix ========
 */
function genPrefix( node, sName )
{
    var left, right;
    var cls;
    var id;

    if (sName == Gbl.META_SYN) {
        left = Gbl.sprintf("<tt>$1</tt> usage", Gbl.span('xdoc-id-meta2', 'XDCscript'));
        right = 'meta-domain';
        cls = 'xdocSynM';
        id = 'meta-synop'
    }
    else if (sName == Gbl.TARG_SYN) {
        left = Gbl.sprintf("<tt>$1</tt> synopsis", Gbl.span('xdoc-id-targ2', 'C'));
        right = 'target-domain';
        cls = 'xdocSynT';
        id = 'targ-synop'
    }
    else {
        cls = 'xdocSynX';
        id = 'spec-synop'
    }

    PL(Gbl.sprintf("<span id='$1'></span>", id));

    if (sName == Gbl.SPEC_SYN) {
        Pag.genSpecFile(Gbl.unitNode(), 'declarations');
    }
    else {
        Pag.genLabel(left, right);
    }

    Pag.genSynTabBeg(cls);
}

/*
 *  ======== genSuffix ========
 */
 function genSuffix()
 {
     Pag.genSynTabEnd();
 }

/*
 *  ======== _mkLink ========
 */
function _mkLink( anc, alt )
{
    return Gbl.sprintf("<a class='xdocSynGo' href='$1$2.html#$3' title='$4.$2.$5'>&nbsp;</a>",
        Gbl.path(),
        String(Gbl.unitNode().@name),
        anc,
        String(Gbl.pkgNode().@name),
        alt
    );
}

/*
 *  ======== _remGo ========
 */
function _remGo( s )
{
    return s.replace(/<go>(.*?)<\/go>/g, '$1');
}

/*
 *  ======== _repGo ========
 */
function _repGo( s, anc, alt, sum )
{
    var rep;
    var popup = '';

    if (sum) {
        sum = sum.replace(/%3Ca/g, '%3Cspan').replace(/%3C%2Fa%3E/g, '%3C%2Fspan%3E');
        var rep ='<a class="xdocSynGo" href="#' + anc + '">$1<span class="xdocSynHoverShadow"><span class="xdocSynHover">' + sum + '</span></span></a>';
    }
    else {
        rep = '<a class="xdocSynGo" href="#' + anc + '" title="' + alt + '">$1</a>'; 
    }

    return s.replace(/<go>(.*?)<\/go>/, rep);
}

