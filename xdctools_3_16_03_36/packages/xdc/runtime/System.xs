/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
/*
 *  ======== System.xs ========
 *
 *! Revision History
 *! ================
 *! 04-Mar-2008 sasha	Added validate with the fix for CQ18901
 *! 18-Jun-2007 nitya   Initialize numAtexitHandlers correctly
 *! 13-Jun-2007 nitya   Added atexitMeta; init exitStatus
 *! 31-Jan-2007 toddm   Added atexit handling
 *! 28-Nov-2006 toddm   Start revision history
 */

/*
 *  ======== module$meta$init ========
 */
function module$meta$init()
{
    /* process only in cfg flow */
    if (xdc.om.$name != 'cfg') {
        return;
    }

    this.SupportProxy = xdc.module('xdc.runtime.SysMin');
}

/*
 *  ======== module$use ========
 */
function module$use()
{
    /* If Program.system is set, it has to be a module that inherits from
     * ISystemSupport.
     */
    if (Program.system &&
        this.$package.ISystemSupport.Module(Program.system) == null) {
        Program.$logError(
            "Module assigned to Program.system must inherit from "
            + "xdc.runtime.ISystemSupport.", Program);
    }

    /* DEPRECATED FEATURE */
    if (Program.system) {
        this.SupportProxy = Program.system;
    }

    /* necessary when useModule not called on System */
    if (this.SupportProxy) {
        xdc.useModule(this.SupportProxy.delegate$);
    }

    xdc.useModule('xdc.runtime.Assert');
    xdc.useModule('xdc.runtime.Core');
    xdc.useModule('xdc.runtime.Defaults');
    xdc.useModule('xdc.runtime.Diags');
    xdc.useModule('xdc.runtime.Error');
    xdc.useModule('xdc.runtime.Gate');
    xdc.useModule('xdc.runtime.Log');
    xdc.useModule('xdc.runtime.Main');
    xdc.useModule('xdc.runtime.Startup');
    xdc.useModule('xdc.runtime.Text');
    
    /* $$scope == -1 means that Startup is loaded from a ROM assembly, so
     * it is already exported. Program.exportModule already does the check
     * so we could probably remove the check from here.
     */
    var Startup = this.$package.Startup;
    if (!('$$scope' in Startup && Startup.$$scope == -1)) {
        Program.exportModule('xdc.runtime.Startup');
    }

    Program.symbol["xdc_runtime_Startup__EXECFXN__C"] = 1;
    Program.symbol["xdc_runtime_Startup__RESETFXN__C"] = 1;
    
    this.$package.Types.$used = false;

    if (this.$$scope != -1) {
        this.$$bind('$$scope', 1);
    }
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(mod, params)
{
    mod.numAtexitHandlers     = this.exitFxns.length;
    
    /* Create only if there will be handlers */
    if (params.maxAtexitHandlers != 0) {
        mod.atexitHandlers.length = params.maxAtexitHandlers;
        xdc.module('xdc.runtime.Memory').staticPlace(mod.atexitHandlers,
            0, null);
    }
    
    for (var i = 0; i < this.exitFxns.length; i++) {
        mod.atexitHandlers[i] = this.exitFxns[i];
    }
    
    /* Need to null out the rest */
    for (var i = this.exitFxns.length; i < mod.atexitHandlers.length; i++) {
        mod.atexitHandlers[i] = null;
    }

    mod.exitStatus = this.STATUS_UNKNOWN;    
}

/*
 *  ======== atexitMeta ========
 */
function atexitMeta(func)
{
    this.exitFxns.$add(func);
}

/*
 *  ======== mprintf ========
 */
function mprintf(fmt, args)
{
    var Text = xdc.module('xdc.runtime.Text');

    var res = "";
    var mat;

    while (fmt && (mat = fmt.match(/%(([cdopsxf])|\$([ALMR]))(.*)/))) {
        res += fmt.slice(0, mat.index);
        var code = mat[1] ? mat[1] : mat[2];
        switch(code) {
            case 'c':
                res += String.fromCharCode(args.shift());
                break;
            case 'd':
                res += formatNum(args.shift(), 10);
                break;
            case 'o':
                res += formatNum(args.shift(), 8);
                break;
            case 'p':
                res += '@' + formatNum(args.shift(), 16);
                break;
            case 's':
                var a = args.shift();
                res += typeof(a) == 'string' ? a : Text.fetchAddr(a);
                break;
            case 'x':
                res += formatNum(args.shift(), 16);
                break;
            case '$R':
                res += Text.fetchAddr(args.shift());
                break;
            case 'f':
                var bits = args.shift();
                var s = ((bits >> 31) == 0) ? 1 : -1;
                var e = ((bits >> 23) & 0xff);
                var m = (e == 0) ? (bits & 0x7fffff) << 1 :
                                   (bits & 0x7fffff) | 0x800000;
                var f = s * m * Math.pow(2, (e-150));
                f = f.toFixed(4);
                res += formatNum(f, 10);

                break;
            }

        fmt = mat[4];
    }

    res += fmt;
    return res;
}

/*
 *  ======== formatNum ========
 */
function formatNum(num, base)
{
    return Number(num).toString(base);
}

/*
 *  ======== module$view$init ========
 */
function module$view$init(view, mod)
{
    var Model = xdc.useModule("xdc.rov.Model");
    
    /* TODO: fetch atexithandlers and get symbols for them */
    view.numAtexitHandlers = mod.numAtexitHandlers;
}

/*
 *  ======== validate ========
 */
function validate()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg" || !this.$used) {
        return;
    }

    /* Check if the System's gate is not blocking and cannot be
     * preempted.
     */
    var IGateProvider = xdc.module('xdc.runtime.IGateProvider');
    var Del = this.Module_GateProxy.delegate$;
    if (Del.queryMeta(IGateProvider.Q_BLOCKING) == true
        || Del.queryMeta(IGateProvider.Q_PREEMPTING) == true) {
        this.$logWarning(
	    "System's gate may block the caller: "
		+ "ensure that all threads that can call an xdc.runtime "
		+ "method are capable of being blocked",
            this, null);
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

