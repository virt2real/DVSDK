/* 
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * */
var debug;
if (debug == null) {
    debug = function (msg) {};
}

/*
 *  ======== init ========
 *  Initialize this package.
 *
 *  This is called after all modules in this package are defined and
 *  initialized.
 */
function init()
{
    debug(this.$name + "$init() ...");

    /* initialize module configuration params that are computed */
    var ma = this.$modules;
    for (var i = 0; i < ma.length; i++) {
        if (ma[i] instanceof this.ITarget.Module) {
            var targ = this.ITarget.Module(ma[i]);
            var ext = ".s" + targ.suffix;
            targ.extensions[ext] = new xdc.om['xdc.bld.ITarget'].Extension({
                suf: ext,   typ: "asm"
            });
        }
    }
}

/*
 *  ======== Package.getLibs ========
 *  This package's implementation of xdc.IPackage.getLibs.
 */
function getLibs()
{
    return (null);    /* no library required for this package */
}
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

