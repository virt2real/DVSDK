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
var _asmMap = {};
var _pkgTab = [];

var _romAsm = null;

var _targMods = [];

/*
 *  ======== _close ========
 */
function _close()
{
    var asmvec = this.$$bind('$$asmvec', []);
    for (var a in _asmMap) {
        /* This code won't work correctly when the name of the assembly
         * relative to its base package contains more than one level. If
         * the name is pkg.subdir.a, the code below will look for
         * pkg/subdir/package/cfg/a, instead of pkg/package/cfg/subdir/a.
         * So, we need to know here the name of the package or require that
         * assemblies are not in subdirectories.
         */
        var k = a.lastIndexOf('.');
	/* If there is a '.' in the assembly name, we assume it separates
	 * components of the package name and the last '.' separates
  	 * the assembly name from the name of its containing package.
	 */
	var fn;
	if (k != -1) {
            fn = a.substring(0, k).replace(/\./g, '/') + '/package/cfg/' +
                a.substring(k + 1) + '.p' + this.build.target.suffix + '.obj';
	}
	else {
	    fn = "./package/cfg/" + a + ".p" + this.build.target.suffix +
	        '.obj';
	}
        var path = xdc.jre.xdc.services.global.Path.search(fn);
        asmvec.push(path);
    }

    var isasm = this.$$isasm && asmvec.length > 0 ? 1 : 0;

    for (var i = 0; i < xdc.om.$packages.length; i++) {
        var pkg = xdc.om.$packages[i].$orig;
        pkg.$$bind('$$genflg', isasm);
    }

    /* If a ROM assembly is imported, its modules are already in _targMods */
    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
        if ('$$scope' in mod && mod.$$scope == -1) {
           continue;
        }
        if (!mod.$hostonly && mod.$used) {
            _targMods.push(mod);
        }
    }
}

/*
 *  ======== exportModule ========
 */
function exportModule(modName)
{
    var mod = xdc.useModule(modName);
    
    /* 
     * Don't export the module if the scope is -1, indicating that the module
     * is part of a ROM and already exported.
     */
    if (mod.$$scope != -1) {
        mod.$$bind('$$scope', 1);
    }
}

/*
 *  ======== freezeRomConfig ========
 */
function freezeRomConfig(modName, cfgName)
{
    var mod = xdc.module(modName);
    mod.$$bind('$$romcfgs', mod.$$romcfgs + cfgName + '|');
}

/*
 *  ======== freezeRomParams ========
 */
function freezeRomParams(modName)
{
    this.freezeRomConfig(modName, 'Object__PARAMS');
}

/*
 *  ======== frozenRomConfig ========
 */
function frozenRomConfig(modName, cfgName)
{
    return (xdc.module(modName).$$romcfgs.indexOf('|' + cfgName + '|') != -1);
}

/*
 *  ======== getSectMap ========
 */
function getSectMap()
{
    /* If BIOS 5 is also configured, only explicitly added section
     * specifications are left. Others are handled by BIOS 5.
     */
    if (this.build.cfgScript != null
        && this.build.cfgScript.match(/\.tcf$/) != null) {
        return (this.$capsule._getBiosSectMap());
    }

    var sectMap = {};
    for (sn in this.build.target.sectMap) {
        /* At this time, 'target' is a serialized content of the target module.
         * Therefore, sectMap contains $name as its first key. To avoid that
         * key we could either load the target module or simply ignore $name
         * key. If we load the target module, package.init() gets called, which
         * initializes various properties in that package. It's not clear how
         * safe it is, so I'll go for the second option of ignoring $name.
         * However, it should still be checked how safe it is to load ti.targets
         * package.
         */
        if (sn == "$name") {
            continue;
        }
        var space = this.build.target.sectMap[sn];

        sectMap[sn] = new this.SectionSpec();
        sectMap[sn].loadSegment = this.platform[space + "Memory"];
    }

    for (sn in this.platform.sectMap) {
         /* platform may override target */
        sectMap[sn].loadSegment = this.platform.sectMap[sn];
    }

    for (sn in this.sectMap) {
        /* prog may override platform and target */
        if (typeof(this.sectMap[sn]) == "string") {
            /* $copy is required, so that any changes to sectMap are not
             * copied to this.sectMap and this function stays idempotent.
             */
            sectMap[sn] = new this.SectionSpec();
            sectMap[sn].loadSegment = this.sectMap[sn];
        }
        else if (typeof(this.sectMap[sn]) == "object") {
            sectMap[sn] = new this.SectionSpec(this.sectMap[sn]);
        }
    }
    
    /* one more loop to figure out if we have '|' entries and pages */
    for (sn in sectMap) {

        /* segment may include more than one memory name separated by '|' */
        if (sectMap[sn].loadSegment == null &&
            sectMap[sn].loadSegment == undefined) {
            continue;
        }

        var ma = sectMap[sn].loadSegment.split(/[\s\|]+/);
        var result = "";
        for (var i = 0; i < ma.length; i++) {
            var mem = null;
            for (var j = 0; j < this.cpu.memoryMap.length; j++) {
                if (ma[i] == this.cpu.memoryMap[j].name) {
                    mem = this.cpu.memoryMap[j];
                }	
            }

            if (mem == null) {
                var validMemoryNames = "";
                for (var m in this.cpu.memoryMap) {
                    validMemoryNames = validMemoryNames + "'"
                        + this.cpu.memoryMap[m].name + "'" + ";";
                }
                throw new Error("memory name '" + ma[i] +
                    "' is not defined by the platform '" + this.platformName +
                     "'. " + "Fix the memory name in the configuration script. " 
                          + "Valid memory names are : " + validMemoryNames);
            }

            result += (i == 0 ? '' : " | ") + mem.name +
                ((mem.page != null && ma.length <= 1)
                ? (' PAGE ' + mem.page) : '');
        }
        sectMap[sn].loadSegment = result;

        if (sectMap[sn].runSegment == null &&
            sectMap[sn].runSegment == undefined) {
            continue;
        }
        ma = sectMap[sn].runSegment.split(/[\s\|]+/);

        result = "";
        for (var i = 0; i < ma.length; i++) {
            mem = null;
            for (var j = 0; j < this.cpu.memoryMap.length; j++) {
                if (ma[i] == this.cpu.memoryMap[j].name) {
                    mem = this.cpu.memoryMap[j];
                }	
            }
            if (mem == null) {
                var validMemoryNames = "";
                for (var m in this.cpu.memoryMap) {
                    validMemoryNames = validMemoryNames + "'"
                        + this.cpu.memoryMap[m].name + "'" + ";";
                }
                throw new Error("memory name '" + ma[i] +
                    "' is not defined by the platform '" + this.platformName +
                     "'. " + "Fix the memory name in the configuration script. " 
                          + "Valid memory names are : " + validMemoryNames);
            }
            result += (i == 0 ? '' : " | ") + mem.name +
                ((mem.page != null && ma.length <= 1)
                ? (' PAGE ' + mem.page) : '');
        }
        sectMap[sn].runSegment = result;
    }    
    return (sectMap);
}

/*
 *  ======== importAssembly ========
 */
function importAssembly(asmName)
{
    Program.system = null;
    if (_asmMap[asmName]) {
        return;
    }

    _asmMap[asmName] = true;
}

/*
 *  ======== importRomAssembly ========
 */
function importRomAssembly(qn)
{
    var k = qn.lastIndexOf('.');
    var pkgDir = (k != -1) ? xdc.findFile(qn.substring(0, k).replace(/\./g, '/')) : './';
    var asmName = (k != -1) ? qn.substring(k + 1) : qn;
    var fn = pkgDir + '/package/cfg/' + asmName + '_p' +
        Program.build.target.suffix + '.romasm.xs';

    _romAsm = xdc.loadCapsule(fn);

    xdc.loadCapsule(pkgDir + '/' + _romAsm.cfgScript);
    _romAsm.objfile = pkgDir + '/' + _romAsm.objfile;

    xdc.om.$$bind('$$phase', 3);

    for each (var m in _romAsm.modules) {
        var mod = xdc.useModule(m.name);
        mod.$$bind('$$scope', -1);
        mod.common$.romPatchTable = m.romPatchTable;
        
        /* We want the ROM modules to be first in the array of target modules,
         * so that whenever a ROM assembly is loaded, the modules that are a
         * part of the ROM assembly would have the same module IDs they had
         * when the assembly was built.
         */
        _targMods.push(mod);
    }

    /* When importing ROM assemblies, we have to replicate parts of code
     * from xdc.runtime.finalize(), which normally runs after all packages
     * are closed.
     */
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var System = xdc.module('xdc.runtime.System');

    for each (var p in ['gate', 'gateParams']) {
        if (System.common$[p] !== undefined && !Defaults.common$[p]) {
            Defaults.common$[p] = System.common$[p];
        }
    }

    for each (var m in _romAsm.modules) {
        /* This call goes to module$use immediately, because there are no
         * close() calls here, so we don't postpone module$use for a module
         * until its package is closing.
         */
        var mod = xdc.useModule(m.name);
        for each (var cn in mod.$$romcfgs.split('|')) {
            if (cn && cn != 'Object__PARAMS') {
                mod.$seal(cn);
            }
        }

        if (mod.$spec.attrBool('@Gated') && !mod.$hostonly && !mod.PROXY$) {
            mod.Module__gateObj = (mod.common$.gate !== undefined) ?
                mod.common$.gate : Defaults.common$.gate;
            mod.Module__gatePrms = (mod.common$.gateParams !== undefined) ?
                mod.common$.gateParams : Defaults.common$.gateParams;
            mod.Module_GateProxy = mod.Module__gateObj ?
                mod.Module__gateObj.$module :
                xdc.useModule('xdc.runtime.GateNull');
        }

        /* Set, if needed, and Seal all common$ properties, except for the
         * module Defaults. We leave defaults unsealed, because we still want
         * to leave the possibility for an application config script to set
         * defaults that will be used for non-ROM modules.
         */
        if (m.name == 'xdc.runtime.Defaults') {
            continue;
        }
        for (var p in Defaults.common$) {
            if (mod.common$[p] === undefined) {
                mod.common$[p] = Defaults.common$[p];
            }
            //mod.common$.$seal(p);
        }

        /* seal all proxy bindings */
        if ('$$proxies' in mod && !mod.PROXY$) {
            for (var i = 0; i < mod.$$proxies.length; i++) {
                var p = mod.$$proxies[i];
                var pud = mod[p + '$proxy'];
                pud.$seal('delegate$');
            }
        }

    }

    /* If the ROM recap file contains that information, we are going to
     * initialize Text.charTab here, so the message IDs seen by ROM end up
     * at the same offset in Text.charTab as seen by ROM configuration.
     */    
    if ("charTab" in _romAsm) {
        var Text = xdc.module('xdc.runtime.Text');
        for (var i = 1; i < _romAsm.charTab.length; i++) {
            Text.defineRopeCord(_romAsm.charTab[i]);
        }
    }

    xdc.om.$$bind('$$phase', 0);
}

/*
 *  ======== instSize ========
 */
function instSize(inst)
{
    var mod = inst.$module;
    var nmSz = 0;

    var named = mod.common$.namedInstance;
    named |= mod.common$.namedInstance === undefined && xdc.module('xdc.runtime.Defaults').common$.namedInstance;

    if (named) {
        nmSz = Program.build.target.stdTypes['t_Ptr'].size;
    }

    return mod.Instance_State.$sizeof() + nmSz;
}

/*
 *  ======== patchRomFxn ========
 */
function patchRomFxn(modName, fxnName, patchSym)
{
    var mod = xdc.module(modName);
    var psyms = ('$$patchsyms' in mod) ? (mod.$$patchsyms + ";") : "";
    mod.$$bind('$$patchsyms', psyms + fxnName + '=' + patchSym);
}

/*
 *  ======== targetModules ========
 */
function targetModules()
{
    return _targMods;
}

/*
 *  ======== _getBiosSectMap ========
 *  This function combines BIOS 5 settings and settings from Program.sectMap
 *  with the condition that Program.sectMap cannot overwrite BIOS 5 section
 *  allocations.
 */
function _getBiosSectMap()
{
    var sectMap = {};

    var uninitialized = [".data", ".far", ".bss", ".args", ".stack", ".cio"];
    
    for each (var m in uninitialized) {
        sectMap[m] = new Program.SectionSpec();
        var segprop = m.substr(1).toUpperCase() + "SEG";
        sectMap[m].runSegment = $$legacy.prog.module("MEM")[segprop].name;
    } 

    var initialized = [".text", ".bios", ".switch", ".const", ".cinit", ".hwi",
        ".pinit", ".sysinit", ".trcdata"];

    for each (var m in initialized) {
        sectMap[m] = new Program.SectionSpec();
        var segprop = m.substr(1).toUpperCase() + "SEG";
        sectMap[m].runSegment = $$legacy.prog.module("MEM")[segprop].name;
        var loadprop = "LOAD" + segprop;
        if ($$legacy.prog.module("MEM")[loadprop] != undefined) {
            sectMap[m].loadSegment = $$legacy.prog.module("MEM")[loadprop].name;
        }
        else {
            sectMap[m].loadSegment = sectMap[m].runSegment;
        }
    } 

    /* The following sections do not have a simple mapping between section
     * names and property names.
     */
    sectMap[".hwi_vec"] = new Program.SectionSpec();
    sectMap[".hwi_vec"].runSegment = $$legacy.prog.module("MEM").HWIVECSEG.name;
    if ($$legacy.prog.module("MEM").LOADHWIVECSEG != undefined) {
        sectMap[".hwi_vec"].loadSegment =
            $$legacy.prog.module("MEM").LOADHWIVECSEG.name;
    }
    else {
        sectMap[".hwi_vec"].loadSegment = sectMap[".hwi_vec"].runSegment;
    }

    sectMap[".rtdx_text"] = new Program.SectionSpec();
    sectMap[".rtdx_text"].runSegment =
        $$legacy.prog.module("MEM").RTDXTEXTSEG.name;
    if ($$legacy.prog.module("MEM").LOADRTDXTEXTSEG != undefined) {
        sectMap[".rtdx_text"].loadSegment =
            $$legacy.prog.module("MEM").LOADRTDXTEXTSEG.name;
    }
    else {
        sectMap[".rtdx_text"].loadSegment = sectMap[".rtdx_text"].runSegment;
    }

    /* Some modules have OBJMEMSEG, which specifies the segment for the
     * section for the module's instances.
     */
    for each (var mod in $$legacy.prog.modules()) {
        var mname = mod.name;
        if ($$legacy.prog.module(mname).OBJMEMSEG != undefined) {
            sectMap["." + mname.toLowerCase()] = new Program.SectionSpec();
            sectMap["." + mname.toLowerCase()].runSegment =
                $$legacy.prog.module(mname).OBJMEMSEG.name;
            sectMap["." + mname.toLowerCase()].loadSegment =
                sectMap["." + mname.toLowerCase()].runSegment;
        }
    }

    for (sn in Program.sectMap) {
        if (sectMap[sn] == undefined) {
            if (typeof(Program.sectMap[sn]) == "string") {
                sectMap[sn] = new Program.SectionSpec();
                sectMap[sn].loadSegment = Program.sectMap[sn];
            }
            else if (typeof(Program.sectMap[sn]) == "object") {
                sectMap[sn] = new Program.SectionSpec(Program.sectMap[sn]);
            }
        }
        else {
            $trace("Warning: Section " + sn + " is managed by BIOS 5. It "
                + "cannot be set through Program.sectMap.", 0);
        }
    }

    return (sectMap);
}
/*
 *  @(#) xdc.cfg; 1, 0, 2, 0,237; 2-22-2010 10:33:11; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

