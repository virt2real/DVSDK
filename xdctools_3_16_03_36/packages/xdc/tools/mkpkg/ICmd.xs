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
 *  ======== main ========
 */
function main(args)
{
    /* convert to a real array */
    if (args == null) {
        args = [];
    }
    else {
        var _args = [];
        for (var i = 0; i < args.length; i++) {
            _args.push(args[i]);
        }
        args = _args;
    }

    var mod = this.$orig;
    var inst = mod.create();

    if (args == null) {
        args = [];
    }

    var cmdr = xdc.module('xdc.tools.Cmdr').create(mod);
    cmdr.getopts(inst, args);

    /* instantiate the template */
    var Gen  = xdc.module('xdc.tools.mkpkg.Gen');
    var gen = Gen.create(inst, inst.output);
    gen.gen();
}
/*
 *  @(#) xdc.tools.mkpkg; 1, 0, 1, 0,149; 11-20-2009 13:27:05; /db/ztree/library/trees/xdctools/xdctools-d08x/src/
 */

