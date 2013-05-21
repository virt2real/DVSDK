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
 *  ======== Dcl.xs ========
 */

var Doc = xdc.loadCapsule('Doc.xs');
var Gbl = xdc.loadCapsule('Gbl.xs');
var Pag = xdc.loadCapsule('Pag.xs');
var Syn = xdc.loadCapsule('Syn.xs');

function PL( s ) { Gbl.outstr().println(s); }

/*
 *  ======== gen ========
 */
function gen( dNode, uNode )
{
    if (dNode.@external == '0') return;
    if (!Gbl.opts().nodFlg && dNode.@nodoc == '1') return;

    Gbl.genRowB();
    Pag.genHdr(dNode, null, uNode, null);
    if (uNode.@kind == 'interface') {
        _genSynop(dNode, Gbl.SPEC_SYN);
    }
    if (Gbl.hasMetaSyn(dNode)) {
        _genSynop(dNode, Gbl.META_SYN);
    }
    if (Gbl.hasTargSyn(dNode)) {
        _genSynop(dNode, Gbl.TARG_SYN);
    }
    Gbl.genRowB();
    Doc.genAll(dNode);
}

/*
 *  ======== _genSynop ========
 */
function _genSynop( dNode, sName )
{
    Syn.genPrefix(dNode, sName);
    Syn.genLines(dNode[sName], 0, dNode, true);
    Syn.genSuffix();
}

