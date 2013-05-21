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
 *  ======== package.xs ========
 *
 *! Revision History
 *! ================
 *! 07-Feb-2008 sasha	check if System's gate can't block and be preempted
 */

/*
 *  ======== package.init ========
 */
function init()
{
    if (xdc.om.$name != 'cfg') {
        return;
    }

    for each (var mod in this.$modules) {
        if (mod.$name == 'xdc.runtime.Main'
            || !("common$" in mod)          /* skip meta-only modues */
            || mod.$name == 'xdc.runtime.Defaults') {
            continue;
        }
        mod.common$.logger = null;
        for (var dl in mod.common$) {
            if (dl.match(/^diags_/) && dl != 'diags_ASSERT') {
                mod.common$[dl] = this.Diags.ALWAYS_OFF;
            }
        }
    }
}

/*
 *  ======== package.close ========
 */
function close()
{
    if (xdc.om.$name != 'cfg') {
        return;
    }

    var targMod = null;

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
        if (mod.$used && !mod.$hostonly && mod.$spec.needsRuntime()) {
            targMod = mod;
            break;
        }
    }

    if (Program.system !== undefined) {
        if (targMod && Program.system === null) {
            Program.$logError("the target module "
                + targMod.$name + " is present, but Program.system == null",
                Program);
            return;
        }
        else if (Program.build.cfgScript) {
            Program.$logWarning("assignment to Program.system is deprecated",
                Program);
        }
    }

    if (targMod) {
        xdc.useModule('xdc.runtime.System');
    }
    else {
	/* no target modules used but we may need to define a reset function */
        var Startup = xdc.module("xdc.runtime.Startup");
        var Reset = xdc.module("xdc.runtime.Reset");

        if (Startup.resetFxn != null || Reset.fxns.length > 0) {
            /* define RESETFXN so reset function will be called from boot */
            Program.symbol["xdc_runtime_Startup__RESETFXN__C"] = 1;

            /* ensure Reset.xdt template will be expanded */
            xdc.useModule("xdc.runtime.Reset");
        }
        else {
            /* no reset fxn is defined, stop boot from calling anything */
            Program.symbol["xdc_runtime_Startup__RESETFXN__C"] = 0;
            Program.symbol["xdc_runtime_Startup_reset__I"] = 0;
        }
        Program.symbol["xdc_runtime_Startup__EXECFXN__C"] = 0;
        Program.symbol["xdc_runtime_Startup_exec__E"] = 0;
    }

    var Types = xdc.module('xdc.runtime.Types');
    var Defaults = xdc.module('xdc.runtime.Defaults');
    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
//        print(mod.$name, mod.$$instflag, mod.$used);
        if (mod.$used && !mod.$hostonly && mod.$$instflag
            && Defaults.getCommon(mod, "memoryPolicy") != Types.STATIC_POLICY) {
                xdc.useModule('xdc.runtime.Memory');
                break;
        }
    }

    /* 'maxAtexitHandlers' is set here because after close(), all configuration
     * parameters are sealed and this is the last chance to change them.
     */
    var System = xdc.module('xdc.runtime.System');
    System.maxAtexitHandlers += System.exitFxns.length;

    /* Code from Memory.module$use is repeated here, only when Memory is
     * not a part of a ROM assembly.
     */
    var Memory = this.Memory;
    if (Memory.$used && Memory.$$scope != -1) {
        /*
         *  Make sure it has a default instance. This instance is used in
         *  Memory_alloc if NULL is specified for the heap.
         */
        if (Memory.defaultHeapInstance == null) {
            var HeapStd = xdc.useModule('xdc.runtime.HeapStd');
            Memory.defaultHeapInstance = HeapStd.create(
                {size: Memory.defaultHeapSize});
        }
        Memory.HeapProxy = Memory.defaultHeapInstance.$module;

        /* declare that instances may come from different modules; the
         * generated HeapProxy function stub must call through a vtable
         * pointer rather than directly call the HeapProxy module
         */
        Memory.HeapProxy.abstractInstances$ = true;
    }
}

/*
 *  ======== checkProxies ========
 */
function checkProxies(unit)
{
    if (!('$$proxies' in unit) || unit.PROXY$ || '$$proxyCheck' in unit) {
        return;
    }

    unit.$$bind('$$proxyCheck', 1);

    for (var i = 0; i < unit.$$proxies.length; i++) {
        var p = unit.$$proxies[i];
        var pud = unit[p + '$proxy'];

        if (!pud.delegate$) {
            throw new Error("unbound proxy: " + pud.$name);
        }

        if ('PROXY$' in pud.delegate$ && pud.delegate$.PROXY$) {
            throw new Error("proxy cannot be bound to another proxy: "
                + pud.delegate$.$name);
        }
    }
}

/*
 *  ======== finalize ========
 *  Called by the configuration model to initialize all common module
 *  settings
 */
function finalize()
{
    if (Program.system === null) {
        return;
    }

    var Defaults = xdc.module('xdc.runtime.Defaults');
    var System = xdc.module('xdc.runtime.System');

    /* if System gate is defined and Defaults isn't, make the System gate
     * the default
     */
    for each (var p in ['gate', 'gateParams']) {
        if (System.common$[p] !== undefined && !Defaults.common$[p]) {
            Defaults.common$[p] = System.common$[p];
        }
    }

    /* propagate the Defaults gate to all modules needing one; if the
     * Defaults gate is null, use GateNull
     */
    for each (var mod in xdc.om.$modules) {
        if (!mod.$used || mod.$hostonly || mod.PROXY$ || mod.$$scope == -1) {
            continue;
        }
	if (!mod.$spec.attrBool('@Gated')) {
	    if (mod.common$.gate !== undefined
		&& mod.$name != "xdc.runtime.Defaults") {
		mod.$logWarning("this module is non-gated but it was assigned "
		    + "a non-null gate", mod);
	    }
	    continue;
	}

        /* TODO: validate gateObj/gatePrms come from same module if former
         * is non-null
         */
        mod.Module__gateObj = (mod.common$.gate !== undefined) ?
            mod.common$.gate : Defaults.common$.gate;
        mod.Module__gatePrms = (mod.common$.gateParams !== undefined) ?
            mod.common$.gateParams : Defaults.common$.gateParams;
        mod.Module_GateProxy = mod.Module__gateObj ?
            mod.Module__gateObj.$module : xdc.useModule('xdc.runtime.GateNull');
    }

    /* for all used target module in the configuration ... */
    for each (var mod in xdc.om.$modules) {

        if (mod.$hostonly || !mod.$used) {
            continue;
        }

        checkProxies(mod);
        
        /*  Unless otherwise specified, force some modules to be named.
         *    Main  : This improves the error messages that come from calls to
         *            Error_raise() and Log_print/write in "non module" code.
         *    Memory: This improves the error message from the call to
         *            Error_raise in Memory_alloc().
         */
        if ((mod.$name == "xdc.runtime.Memory"
            || mod.$name == "xdc.runtime.Main") && mod.$$scope != -1) {
            if (mod.common$.namedModule === undefined) {
                mod.common$.namedModule = true;
            }
        }

	/* prevent unintended logging of loggers (usually a mistake) */
	if (mod instanceof xdc.om["xdc.runtime.ILogger"].Module) {
	    if (mod.common$.logger === undefined) {
		mod.common$.logger = null;
	    }
	}

        /* propagate Defaults to all used target modules, except the ones
         * imported from ROM assemblies. Those modules are already exported
         * in ROM asseblies and the generation code will not look at them
         * when building an application.
         */
        if (mod.$$scope != -1) {
            for (var p in Defaults.common$) {
                if (mod.common$[p] === undefined) {
                    mod.common$[p] = Defaults.common$[p];
                }
            }
        }

        Program.freezeRomConfig(mod.$name, 'Object__sizeof');
        if (mod.common$.instanceHeap == null) {
            Program.freezeRomConfig(mod.$name, 'Object__heap');
        }
        if (mod.common$.logger == null) {
            Program.freezeRomConfig(mod.$name, 'Module__loggerObj');
        }
        if (mod.Module__gateObj == null) {
            Program.freezeRomConfig(mod.$name, 'Module__gateObj');
        }
        if (mod.Module__gatePrms == null) {
            Program.freezeRomConfig(mod.$name, 'Module__gatePrms');
        }

        if (!mod.$$instflag) {
            Program.freezeRomConfig(mod.$name, 'Object__count');
            Program.freezeRomConfig(mod.$name, 'Object__table');
        }
    }
}

/*
 *  ======== validate ========
 *  This function is called during the validation phase of configuration
 */
function validate()
{
    /* for each module in this package ... */
    for each (var mod in this.$modules) {

        /* if the module's capsule has a validate function, run it */
        var cap = mod.$capsule;
        if (cap && "validate" in cap) {
            cap.validate.apply(mod, []);
        }
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:59; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

