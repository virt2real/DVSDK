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
 *  ======== Utils.assembleMemoryMap ========
 */
function assembleMemoryMap(cpu, plat, noCheck)
{
    if (arguments.length < 3) {
        noCheck = false;	
    }

    var map = new xdc.om['xdc.platform.IPlatform'].MemoryMap();

    /* XDC 3.00 and earlier releases kept platform instance arguments in
     * $private.args, without having a config parameter for each instance
     * argument. The first if-clause supports those platforms.
     */
    if (plat.$private != undefined && plat.$private.args != undefined) {
        map.$self = cpu.attrs.getMemoryMap(plat.$private.args);
    }
    else {
        map.$self = cpu.attrs.getMemoryMap(plat);
    }

    var extMap = plat.externalMemoryMap;
    
    if (extMap != undefined && extMap != null) {
        for (var i = 0; i < extMap.length; i++) {
            /* don't override the data sheet */
            var seg = extMap[i];
            var segFound = false;
            for (var j = 0; j < map.length; j++) {
                if (map[j].name == seg.name) {
                    segFound = true;
                    plat.$module.$logError("Memory name " + seg.name + 
                        " is already used for an existing memory object", plat,
                        plat.externalMemoryMap);
                    break;
                }
            }
            if (!segFound) {
                map[seg.name] = seg;
            }
        }
    }

    /* Go through the rename map */
    if (plat.renameMap != undefined && plat.renameMap != null) {
        for (var p in plat.renameMap) {
            var pFound = false;
            for (var j = 0; j < map.length; j++) {
                if (map[j].name == p) {
                    map[j].name = plat.renameMap[p];
                    pFound = true;
                }
            }
            if (!pFound) {
                plat.$module.$logWarning("Memory name " + p + " from renameMap"
                   + " could not be found in the memory map", plat,
                   plat.renameMap);	
            }
        }
    }

    if (plat.customMemoryMap.length != 0) {
        if (!noCheck && this.checkFit(map, plat.customMemoryMap) == false) {
	    plat.$module.$logError("Custom memory map does not fit into a " +
	         "physical memory", plat, plat.customMemoryMap);
	}
        map = plat.customMemoryMap;
    }

    /* check for various problem with names, for example spaces */
    for (var i = 0; i < map.length; i++) {
        /* if there is a white space in the middle of a name, fail */
        if (map[i].name.match(/\S+\s+\S+/)) {
            plat.$module.$logError("Spaces are not allowed in memory names. "
                + "The name `" + map[i].name + "' is not a valid name.", plat);
            continue;
        }
        var noSpacesName = map[i].name.replace(/\s/g, "");
        if (noSpacesName != map[i].name) {
            /* If removing spaces on both ends does not create a duplicate
             * memory name, we continue silently. Otherwise, it's an error.
             */
            var nameFound = false
            for (var j = 0; j < map.length; j++) {
                if (i != j && map[j].name == noSpacesName) {
                    nameFound = true;
                    plat.$module.$logError("Memory names `" + map[i].name
                        + "' and '" + map[j].name + "' are identical to some "
                        + "linkers. One of the names must be changed.", plat);
                    break;
                }
            }
            if (!nameFound) {
                map[i].name = noSpacesName;
            }
        }
    }
    
    /* check for spaces in codeMemory, dataMemory and stackMemory, if they
     * are defined.
     */
    for each (var name in ["codeMemory", "dataMemory", "stackMemory"]) {
        /* if there is a white space in the middle of a name, fail */
        if (plat[name] != undefined) {
            if(plat[name].match(/\S+\s+\S+/)) {
                plat.$module.$logError("Spaces are not allowed in memory names."
                    + " The parameter '" + name + "' is set to '" + map[i].name
                    + "'.", plat);
                continue;
            }
            plat.$unseal(name);
            plat[name] = plat[name].replace(/\s/g, "");
            plat.$seal(name);
        }
    } 

    return (map);
}


/*
 *  ======== Utils.getCpuDataSheet ========
 */
function getCpuDataSheet(cpuDesc)
{
    var rev   = cpuDesc.revision;
    var dname = cpuDesc.deviceName;
    var cname = cpuDesc.catalogName;
    var mname = cname + '.' + dname;
    var err = "can't create an xdc.platform.ICpuDataSheet instance";
    
    if (!(cname in xdc.om) || !(xdc.om[cname] instanceof $$Package)) {
	this.$logFatal(err + "; the platform's CPU catalog package '"
	    + cname + "' not imported", this, null);
    }

    if (!(mname in xdc.om) || !(xdc.om[mname] instanceof $$Module)) {
	this.$logFatal(
	    err + "; the package '" + cname + 
	    "' does not include the module '" + dname + "'", this, null);
    }

    /* mark the device module from the catalog package as "used" */
    var mod = xdc.useModule(mname);

    /* create a "data sheet" instance for the device */
    return (mod.create(rev == null ? undefined : rev));
}

/*
 *  ======== checkDefaults ========
 */
function checkDefaults(inst, memMap) 
{
    var dm = null;
    var cm = null;
    var sm = null;
    var result = true;
    for (var i = 0; i < memMap.length; i++) {
        if (memMap[i].name == inst.dataMemory) {
            dm = memMap[i];
            break;
        }
    }
    if (dm == null) {
        inst.$module.$logError("Parameter 'dataMemory' is set to a nonexisting "
            + "memory object " + inst.dataMemory, inst, inst.dataMemory);
        result = false;
    }
    else if (dm.space != undefined) {
        if (dm.space.indexOf("data") == -1) {
            inst.$module.$logError("Parameter 'dataMemory' is set to the " +
                "memory segment " + inst.dataMemory + " that does not store " +
                "data", inst, inst.dataMemory);
            result = false;
        }
    }
    
    for (var i = 0; i < memMap.length; i++) {
        if (memMap[i].name == inst.codeMemory) {
            cm = memMap[i];
            break;
        }
    }
    if (cm == null) {
        inst.$module.$logError("Parameter 'codeMemory' is set to a nonexisting "
            + "memory object " + inst.codeMemory, inst, inst.codeMemory);	
        result = false;
    }
    else if (cm.space != undefined) {
        if (cm.space.indexOf("code") == -1) {
            inst.$module.$logError("Parameter 'codeMemory' is set to the " +
                "memory segment " + inst.codeMemory + " that does not store " +
                "code", inst, inst.codeMemory);
            result = false;
        }
    }

    for (var i = 0; i < memMap.length; i++) {
        if (memMap[i].name == inst.stackMemory) {
            sm = memMap[i];
            break;
        }
    }
    if (sm == null) {
        inst.$module.$logError("Parameter 'stackMemory' is set to a " + 
            "nonexisting memory object " + inst.stackMemory, inst,
            inst.stackMemory);	
        result = false;
    }
    else if (sm.space != undefined) {
        if (sm.space.indexOf("data") == -1) {
            inst.$module.$logError("Parameter 'stackMemory' is set to the " +
                "memory segment " + inst.stackMemory + " that does not store " +
                "data", inst, inst.stackMemory);
            result = false;
        }
    }

    return (result);
	
}

/*
 *  ======== checkFit ========
 */
function checkFit(realMemMap, customMemMap)
{
    for (var j = 0; j < customMemMap.length; j++) {
	var covered = false;
	var base = customMemMap[j].base;
	var end = customMemMap[j].base + customMemMap[j].len;
	var page = (customMemMap[j].page != undefined) ?
	    customMemMap[j].page : 0;
	while (base < end) {
	    var selected = null;
	    for (var k = 0; k < realMemMap.length; k++) {
	    	var realPage = (realMemMap[k].page != undefined) ?
	    	    realMemMap[k].page : 0;
	        if (page == realPage && realMemMap[k].base <= base &&
	    	    realMemMap[k].base + realMemMap[k].len > base) {
	    	    selected = realMemMap[k];
	    	    break;
	    	}
	    }
	    if (selected == null) {
	        return (false);	
	    }
	    else {
	    	base = selected.base + selected.len;
	    }
	}
    }
    return (true);
}

/*
 *  ======== checkOverlap ========
 */
function checkOverlap(memMap)
{
    for (var i = 0; i < memMap.length; i++) {
    	var im = memMap[i];
    	for (var j = i + 1; j < memMap.length; j++) {
    	    var jm = memMap[j];
    	    var overlap = false;
            if (('page' in im) && (im.page != null) && ('page' in jm) &&
                (jm.page != null) && (jm.page != im.page)) {
                continue;    
            }
            if ((im.base <= jm.base && (im.base + im.len) > jm.base) ||
                (im.base >= jm.base && (jm.base + jm.len) > im.base)) {
                overlap = true;
                return (im.name + " and " + jm.name);
            }
    	}
    }
    return (null);
}

/*
 *  @(#) xdc.platform; 1, 0, 1, 0,237; 2-22-2010 10:33:24; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

