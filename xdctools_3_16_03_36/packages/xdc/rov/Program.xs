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
 *  ======== Program ========
 *  This module is structured such that all of the work of fetching and 
 *  decoding structures is handled by the decoder, and all processing of view
 *  init code is done by Program.
 *
 *  The caching policy is that caching is done by the callee, so Program may
 *  request data from the decoder and expect that if the data is already 
 *  available the decoder will return immediately.
 */

var modTab = [];
var timestampFunc;

/*
 *  ======== getSupportedTabs ========
 *  Functions of the form view$init$instance$* and view$init$module$* define
 *  the set of tabs supported by the module. 
 */
function getSupportedTabs(modName)
{
    /* 
     * Don't use getModuleDesc in order to avoid running useModule. 
     * The initial call of useModule will take the longest, so put it off
     * until we have to.
     */
    var mod = this.getModuleDesc(modName);
    //var modCfg = Program.$modules[modName];
    
    var tabs = new Array();
    
    /* Find the supported tabs in the module's view map. */
    if (mod.viewInfo != null) {
        for each (var viewName in mod.viewInfo.viewMap.$keys) {
            var tab = new Program.Tab();
            tab.name = viewName;
            tab.type = Program.getViewType(modName, viewName);
            tabs[tabs.length] = tab;
        }
        
        /* Don't add the raw tab if showRawTab is false */
        if (mod.viewInfo.showRawTab == false) {
            return (tabs);
        }
    }
    
    /* All modules automatically support the Raw tab */
    var ViewInfo = xdc.useModule('xdc.rov.ViewInfo');
    var tab = new Program.Tab();
    tab.name = "Raw";
    tab.type = String(ViewInfo.RAW);
    tabs[tabs.length] = tab;
    
    return (tabs);
}

/*
 *  ======== getViewType ========
 *  Returns the view type of the specified tab as an xdc.rov.ViewInfo.ViewType.
 */
function getViewType(modName, tabName)
{
    if (tabName == "Raw") {
        var ViewInfo = xdc.useModule('xdc.rov.ViewInfo');
        return (String(ViewInfo.RAW));
    }
   
    var mod = this.getModuleDesc(modName);

    /* Throw an error if the module does not support the tab. */   
    if ((mod.viewInfo == null) || 
        !(tabName in mod.viewInfo.viewMap)) {
        throw (new Error("Tab " + tabName + " not in module " + modName));
    }
       
    return (mod.viewInfo.viewMap[tabName].type);
}
 
 
/*
 *  ======== scanModuleView ========
 *  Processes the specified module-level view of the specified module.
 *  This function will verify that the specified module supports the specified
 *  tab, so that all other functions may assume that the tab is supported.
 */
function scanModuleView(modName, tabName)
{
    var mod = this.getModuleDesc(modName);
    
    if (!modSupportsTab(modName, tabName)) {
        throw (new Error(modName + " does not support the tab '" 
			 + tabName + "'"));
    }
    
    /* Check if the requested view has already been scanned. */
    if (mod.viewMap[tabName] != undefined) {
        /* Before returning it, check if there were any problems. */
        var view = mod.viewMap[tabName];
        for (var field in view.$status) {
            if (view.$status[field]) {
                throw (new Error("ROV detected errors in scan of '" 
                                 + tabName 
                                 + "' tab for module " + modName + "."));
            }
        }
        return (view);
    }

    /*  
     *  Make sure the module state is read in. Returns immediately if
     *  the state is already scanned, sets mod.state = null if there is no
     *  module state.
     */
    this.stateReader.fetchModuleState(mod);
    
    var error = false;
    
    if (!mod.error) {
        var res = runViewInit(mod, mod, tabName, "module");
        if (!res) {
            error = true;
        }
    }
    else {
        error = true;
        
        /* Create a dummy view just to display the error. */
        var view = newViewStruct(modName, tabName);
        
        view.$$bind("address", String(mod.addr));
        view.$status["address"] = mod.error;
        
        /* Add the view to the descriptor's viewMap */
        mod.viewMap[tabName] = view;
    }
    
    /* 
     * If there were errors, throw an exception, so that it must be caught and
     * handled if the caller wants  to continue.
     */
    if (error) {
        throw (new Error("ROV detected errors in scan of '" + tabName + 
                         "' tab for module " + modName + "."));
    }
    
    /* Return the view */
    return (mod.viewMap[tabName]);
}


/* 
 *  ======== scanInstanceView ========
 *  Checks to see if the particular instance view has already been scanned.
 *  If it has, it simply returns. Otherwise, it calls in to the decoder as
 *  necessary to scan the instance view.
 *  Once the instance view is scanned, it can be accessed through:
 *  for (var i in mod.instances) {
 *      var instView = mod.instances[i].viewMap[tabName];
 *  }
 */
function scanInstanceView(modName, tabName)
{   
    debugPrint("xdc.rov.Program: Scanning instance views for " + modName + " " + tabName);
    
    /* Get the module from cache or useModule */
    var mod = this.getModuleDesc(modName);
    
    /* Verify the module supports the requested tab. */
    if (!modSupportsTab(modName, tabName)) {
        throw (new Error("Module does not support the requested view level"));
    }
    if (!('Instance_State' in mod.useMod)) {
        throw(new Error("Calling scanInstance on module that does not support instances"));
    }
    
    /* 
     * Scan in the instance state structures. 
     * Returns immediately if they were already scanned. 
     */
    this.stateReader.fetchAllInstStates(mod);
       
    /* If there are no instances, return an empty array */
    if (mod.instances.length == 0) {
        return (new Array());
    }
    
    /* If we come across any problems, we'll throw an exception at the end */
    var error = false;
    
    /* 
     * At this point, we have the instance states, but may not
     * have the requested view.
     *
     * For each of the module's instances, call the view function specified
     * by tabName, then add the resulting view to the instance's $viewMap.
     */
    debugPrint("xdc.rov.Program: Number of instances = " + mod.instances.length);
    for (var i in mod.instances) {        
        var inst = mod.instances[i];
        debugPrint("xdc.rov.Program: Running view init on inst = 0x" 
                   + Number(inst.state.$addr).toString(16));
 
        var res = runViewInit(mod, inst, tabName, "instance");
        /* If the view status had any problems... */
        if (!res) {
            error = true;
        }
    }
    
    /* 
     * If there were errors, throw an exception, so that it must be caught and
     * handled if the caller wants to continue.
     */
    if (error) {
        throw (new Error("ROV detected errors in scan of '" + tabName + 
                         "' tab for module " + modName + "."));
    }
    
    /* Create an array of the requested instance views to return. */
    var instArr = new Array();
    for each (var inst in mod.instances) {
        instArr[instArr.length] = inst.viewMap[tabName];
    }
    
    return (instArr);
}

/*
 *  ======== newViewStruct ========
 */
function newViewStruct(modName, tabName)
{
    /* Verify the module and tab names are valid. */
    if (!modSupportsTab(modName, tabName)) {
        throw (new Error("Module " + modName + " does not support tab " + 
                         tabName + "."));
    }
    
    var modDesc = this.getModuleDesc(modName);
    
    var structName = modDesc.viewInfo.viewMap[tabName].structName;
    
    /* Verify the specified structure exists in the module. */
    if (!(structName in modDesc.useMod)) {
        throw (new Error("Module " + modName + " does not contain the " +
                         "view structure " + structName));
    }
    
    var struct = new modDesc.useMod[structName];
    
    /* Create the status map and bind it to the struct. */
    var status = new Object();

    for (var p in struct) {
        status[p] = null;
    }
    
    struct.$$bind('$status', status);
    
    // TODO: Seal the map's domain? Would need to add address field before 
    // sealing.
    
    return(struct);
}

/*
 *  ========= scanInstanceDataView ==========
 *  TODO - Added error handling
 */
function scanInstanceDataView(modName, tabName)
{
    /* Get the module from cache or useModule */
    var modDesc = this.getModuleDesc(modName);
    
    /* Verify the module supports the requested tab. */
    if (!modSupportsTab(modName, tabName)) {
        throw (new Error("Module does not support the requested view level"));
    }

    /* Check if the view has already been scanned. */
    if (modDesc.viewMap[tabName] != undefined) {
        /* TODO: Before returning check for erros and throw exception if found. */
        return (modDesc.viewMap[tabName]);
    }
    
    var Program = xdc.useModule('xdc.rov.Program');
    var Model = xdc.useModule('xdc.rov.Model');
    
    /* 
     * If there is any problem reading any of the state structures,
     * the scan will throw an exception.
     */
    try {
        var rawView = Program.scanRawView(modName);
    }
    catch (e) {
        // TODO: Handle this 
        throw e;
    }   
    
    var viewInitFunc = getViewInitFunc(modDesc, tabName);

    var dataArr = new Array();
    
    if (!('Instance_State' in modDesc.useMod)) {
        
        try {
            dataArr = viewInitFunc.call(modDesc.userPrivate);
        }
        catch (e) {
            //desc.error = "Caught exception in view init code: \n" + e.toString();
            debugPrint("xdc.rov.Program: Caught exception from view init: " +
                       Program.exToString(e));
        }
        
        /* 
         * Check abort flag again in case the view function caught the
         * abort signal.
         */
        if (Model.getICallBackInst().getAbortFlag()) {
            throw (new Error("abort"));
        }
    }
    else {
        for each (var inst in rawView.instStates) {
            
            var instDataView = new Program.InstDataView;
            
            try {
                viewInitFunc.call(modDesc.userPrivate, instDataView, inst);
            }
            catch (e) {
                //desc.error = "Caught exception in view init code: \n" + e.toString();
                debugPrint("xdc.rov.Program: Caught exception from view init: " +
                           Program.exToString(e));
            }
            
            /* 
             * Check abort flag again in case the view function caught the
             * abort signal.
             */
            if (Model.getICallBackInst().getAbortFlag()) {
                throw (new Error("abort"));
            }
            
            dataArr[dataArr.length] = instDataView;
        }
    }
    
    /* Add the view to the module's viewMap. */
    modDesc.viewMap[tabName] = dataArr;
    
    return (dataArr);
}

/*
 *  ========= scanModuleDataView ==========
 *
 */
function scanModuleDataView(modName, tabName)
{
    /* Get the module from cache or useModule */
    var modDesc = this.getModuleDesc(modName);
    
    /* Verify the module supports the requested tab. */
    if (!modSupportsTab(modName, tabName)) {
        throw (new Error("Module does not support the requested view level"));
    }

    /* Check if the view has already been scanned. */
    if (modDesc.viewMap[tabName] != undefined) {
        /* TODO: Before returning check for erros and throw exception if found. */
        return (modDesc.viewMap[tabName]);
    }
    
    var viewInitFunc = getViewInitFunc(modDesc, tabName);

    var modDataView = new Program.ModDataView;
        
    /* 
     * If the view code throws an exception, let it propogate up and be
     * displayed to the user. This means the user won't see any partial data
     * if there is any, but there's no other logical place to display the
     * exception message.
     */
    viewInitFunc.call(modDesc.userPrivate, modDataView);
    
    /* Add the view to the module's viewMap. */
    modDesc.viewMap[tabName] = modDataView;
    
    /* TODO - check for any errors and throw exception. */
    /*
    if (error) {
        throw (new Error("ROV detected errors in scan of '" + tabName + 
                         "' tab for module " + modName + "."));
    }
    */
    return (modDataView);
}

/*
 *  ======== runViewInit ========
 *  Process the view init code for the given descriptor and tabName.
 *  Returns false if any of the status fields report an error, returns true
 *  otherwise.
 */
function runViewInit(mod, desc, tabName, type)
{
    /* Check for abort flag before running view function. */
    var Model = xdc.useModule('xdc.rov.Model');
    if (Model.getICallBackInst().getAbortFlag()) {
        throw (new Error("abort"));
    }
    
    /* Check if the view has already been scanned by scanHandle */
    if (desc.viewMap[tabName] != undefined) {
        var view = desc.viewMap[tabName];
        for (var p in view.$status) {
            if (view.$status[p]) {
                return (false);
            }
        }
        return (true);
    }
    
    /* Create an empty view */
    var view = newViewStruct(mod.name, tabName);
    
    /* Add the address field to the view structure. */
    view.$$bind("address", String(desc.addr));
    view.$status["address"] = null;
    
    /* Get the view$init function from the capsule. */
    var viewInitFunc = getViewInitFunc(mod, tabName);

    try {
        /* 
         * Run from the context of an object the module writer can assign 
         * stuff to.
         */
        viewInitFunc.call(mod.userPrivate, view, desc.state);
    }
    catch (e) {
        var exception = Program.exToString(e);
        desc.error = "Caught exception in view init code: " + exception;
        debugPrint("xdc.rov.Program: Caught exception from view init: " + 
                   exception);
    }
    
    /* 
     * Check abort flag again in case the view function caught the
     * abort signal.
     */
    if (Model.getICallBackInst().getAbortFlag()) {
        throw (new Error("abort"));
    }
    
    /* Add the view to the descriptor's viewMap */
    desc.viewMap[tabName] = view;
    
    /* If there were any errors reported, return a message to be thrown */
    for (var p in view.$status) {
        if (view.$status[p]) {
            return (false);
        }
    }
    return (true);
}

/*
 *  ======== scanHandleView ========
 *  This function is called to scan a module from a different module's 
 *  view$init code.
 *  Returns the instance object with the attached $viewMap.
 */
function scanHandleView(modName, instAddr, tabName)
{
    var mod = this.getModuleDesc(modName);

    /* Read in the handle's instance state */
    var inst = this.stateReader.fetchHandleState(mod, Number(instAddr));
        
    /* Check if the view has already been scanned. */
    if (inst.viewMap[tabName] != undefined) {
        return (inst.viewMap[tabName]);
    }
    
    runViewInit(mod, inst, tabName, "instance");
    
    /* Return the inst object since they would have to go find it otherwise. */
    return (inst.viewMap[tabName]);
}

/*
 *  ======== scanRawView ========
 */
function scanRawView(modName)
{
    /* Get the module from cache or useModule */
    var mod = this.getModuleDesc(modName);
    
    /* Move the state data into a RawView structure to return. */
    var Program = xdc.useModule('xdc.rov.Program');
    var rawView = new Program.RawView;
    
    /* 
     * Make sure the module state is read in. 
     * Returns immediately if the state is already scanned, and returns null
     * if the module does not have module state.
     */
    this.stateReader.fetchModuleState(mod);
        
    rawView.modState = mod.state;   
    
    /* 
     * Scan in the instance state structures. Returns immediately
     * if they were already scanned. 
     */
    if ('Instance_State' in mod.useMod) {
        this.stateReader.fetchAllInstStates(mod);   
        
        var instStates = new Array();
        /* Add all of the instances... */
        for each (var inst in mod.instances) {
            instStates[instStates.length] = inst.state;
        }
        
        rawView.instStates = instStates;
    }
        
    rawView.modCfg = mod.cfg;
    
    return (rawView);
}

/*
 *  ======== scanObjectView ========
 *  When this function returns, the object that was passed in will now have 
 *  a $viewMap field attached where the view can be accessed.
 */
function scanObjectView(modName, obj, tabName)
{
    /* Get the module from cache or useModule */
    var mod = this.getModuleDesc(modName);

    /* Verify the module supports the requested tab. */
    if (!modSupportsTab(modName, tabName)) {
        throw (new Error("Module does not support the requested view level"));
    }
    if (!('Instance_State' in mod.useMod)) {
        throw(new Error("Calling scanInstance on module that does not support instances"));
    }
    
    var objDesc = this.stateReader.getInstDesc(mod, obj, -1);
    
    /* Check if the view has already been scanned. */
    if (objDesc.viewMap[tabName] != undefined) {
        /* Before returning it, check if there were any problems. */
        var view = objDesc.viewMap[tabName];
        for (var field in view.$status) {
            if (view.$status[field]) {
                throw (new Error("ROV detected errors in scan of '" 
                                 + tabName 
                                 + "' tab for module " + modName + "."));
            }
        }
        return (view);
    }

    /* Create an empty view */
    var view = newViewStruct(modName, tabName);
    
    /* Add the address field. */
    view.$$bind("address", String(obj.$addr));
    view.$status["address"] = null;   
    
    /* Get the view$init function from the capsule. */
    var viewInitFunc = getViewInitFunc(mod, tabName);
    /* Call view init */
    viewInitFunc.call(mod.userPrivate, view, obj);
    
    /* Add the view to the instance's viewMap */
    objDesc.viewMap[tabName] = view;  
    
    // TODO - Check view status before returning.
    
    /* Return the descriptor directly so user doesn't have to search for it. */
    return (view);
}    

/* 
 *  ======== modSupportsTab ========
 *  Returns true if the module supports the given tab.
 */
function modSupportsTab(modName, tabName)
{
    var mod = this.getModuleDesc(modName);

    if (mod.viewInfo == null) {
        return (false);
    }
    
    return (tabName in mod.viewInfo.viewMap);
}

/* 
 *  ======== getViewInitFunc ========
 *  Retrieves the function associated with the specified tabName for the
 *  specified mod.
 */
function getViewInitFunc(mod, tabName)
{
    var funcName = mod.viewInfo.viewMap[tabName].viewInitFxn;
        
    if (!(funcName in mod.useMod.$capsule)) {
        throw (new Error("The viewInitFxn '" + funcName + "' specified for " + mod.name + 
                             " - " + tabName + " does not exist."));
    }
    
    return (mod.useMod.$capsule[funcName]);
}

/*
 *  ======== getModuleDesc ========
 *  Gets the module from the cache or brings it in.
 */
function getModuleDesc(modName)
{
    /* If the module has already been brought in, just return it. */
    if (modTab[modName]) {
        return (modTab[modName]);
    }
    
    /* 
     * $modules maps module names to their configurations. This comes from the
     * ROV recap file; if a module is not in this map, then it is not in this
     * application.
     */
    var modCfg = Program.$modules[modName];
    if (!modCfg) {
        throw (new Error("Module " + modName + " does not exist in this configuration"));
    }
    
    var mod = new Program.ROVModuleDesc;
    mod.name = modName;
    
    /* Bring in the module */
    mod.useMod = xdc.useModule(modName);
    
    /* Initialize fields. */
    mod.instMap = {};
    mod.readAllAddrs = false;
    
    /* 
     * Place for users to store data. This is the calling context of view init
     * functions.
     */
    mod.userPrivate = {};
    
    /* 
     * Updated the structure size information based on whether this module
     * has named instances. This should only be done once, so check 
     * allModsRead.
     */
    if (!this.$private.allModsRead &&
        modCfg.common$.namedInstance &&
        ('Instance_State' in mod.useMod)) {
        var po = xdc.om[modName + '$$Instance_State'];
        po.$$fld('__name', $$PAdr('xdc_runtime_Types_CordAddr__*', 'PE'),
            undefined, 'w');
        /* 
         * Modules with instances but no Instance_State structure won't
         * have $$sizes. We catch these in the decoder by seeing that 
         * Instance_State does not have a $sizeof field and we just return
         * an empty object.
         */
        if ('$$sizes' in mod.useMod.Instance_State) {
            mod.useMod.Instance_State.$$sizes.push(['__name', 'UPtr']);
        }
    }
    
    /* Add the module's configuration to it as $config */
    mod.cfg = modCfg;
    
    /* Retrieve the ROV ViewInfo for the module. */
    var modSpec = mod.useMod.$spec;
    var facetConfig = modSpec.queryFacet('xdc.rov.ViewInfo');
    
    Program.debugPrint("Facet config for " + modName + " = " + facetConfig);
    
    /* Set viewInfo to null if this module does not have a ViewInfo facet. */
    if (facetConfig == null) {
        mod.viewInfo = null;
    }
    else {
        mod.viewInfo = mod.cfg[facetConfig];
    }
            
    /* Store the module in our cache */
    modTab[modName] = mod;

    return (mod);
}

/*
 *  ======== fetchStruct ========
 *  Fetches the specified structure from the target.
 */
function fetchStruct(desc, addr, addrCheck)
{
    return (Program.strDec.fetchStruct($om[desc.type], Number(addr), 
                                       addrCheck)); 
}
  
/*
 *  ======== fetchArray ========
 *  Retrieves the specified array from the target.
 */
function fetchArray(desc, addr, len, addrCheck)
{
    return (Program.strDec.fetchArray($om[desc.type], Number(addr), len,
                                      desc.isScalar, addrCheck));
}
    
/*
 *  ======== fetchString ========
 *  Retrieves the string starting at the specified address from the target.
 */
function fetchString(addr, addrCheck)
{
    return (Program.strReader.findString(Number(addr), addrCheck));
}

/*
 *  ======== fetchStaticString ========
 *  Retrieves the string at the specified address using an object file reader.
 */
function fetchStaticString(addr)
{
    return (Program.ofReader.findString(Number(addr)));
}
 
/*
 *  ======== getPrivateData ========
 */
function getPrivateData(modName) {
    var modDesc = this.getModuleDesc(modName);
    return (modDesc.userPrivate);
}

/*
 *  ======== getModuleConfig ========
 *  Returns the module config object for the requested module.
 */
function getModuleConfig(modName)
{
    return (this.getModuleDesc(modName).cfg);
}
 
/*
 *  ======== lookupFuncName ========
 */
function lookupFuncName(addr)
{
    var Model = xdc.useModule("xdc.rov.Model");
    
    var symInst = Model.getISymbolTableInst();
    
    var syms = null;
    
    /* For all arm-derived targets, check for thumb mode. */
    var targ = Model.$private.recap.build.target;
    if ((targ.name == "TMS470") || (targ.$name.indexOf('ti.targets.arm') == 0)) {
        syms = symInst.lookupFuncName(Number(addr) & ~1);
    }
    else {
        syms = symInst.lookupFuncName(Number(addr))
    }
    
    return (filterSymbols(syms));
}

/*
 *  ======== lookupDataSymbol ========
 *  Uses the SymbolTable to find the labels at the given address.
 */
function lookupDataSymbol(addr)
{
    var Model = xdc.useModule("xdc.rov.Model");
    var symInst = Model.getISymbolTableInst();
    
    var syms = symInst.lookupDataSymbol(Number(addr));
    
    return (filterSymbols(syms));
}

/*
 *  ======== filterSymbols ========
 *  Helper function used by lookupFuncName and lookupDataSymbol.
 *  There may be multiple symbols at a given address. To improve the chances
 *  of the first symbol in the array being the correct one:
 *    - Sort the symbols by length (shorter symbol is more likely correct)
 *    - Move any symbols containing '$' to the end
 */
function filterSymbols(jSyms)
{
    if (jSyms.length == 0) {
        return (new Array());
    }
    
    /* 
     * Copy the Java String array to a JavaScript array. Filter out any symbols
     * containing '$' and store these separately. 
     */
    var symsArr = new Array();
    var dSyms = new Array();
    for each (var sym in jSyms) {
        if (sym.indexOf("$") != -1) {
            dSyms.push(sym);
        }
        else {
            symsArr.push(sym);
        }
    }

    /* 
     * Sort the array by symbol length, from smallest to largest. In general, 
     * user given names are shorter than generated symbols.
     */
    function compare(a, b) {
        return (a.length - b.length);
    }
    
    symsArr.sort(compare);
    dSyms.sort(compare);
    
    /* Add the '$' symbols back on to the end. */
    return(symsArr.concat(dSyms));
}

/*
 *  ======== getSymbolValue ========
 */
function getSymbolValue(symName)
{
    var Model = xdc.useModule("xdc.rov.Model");
    var symInst = Model.getISymbolTableInst();
    return (symInst.getSymbolValue(symName));
}

/*
 *  ======== displayError ========
 *
 */
function displayError(view, fieldName, errorMsg)
{
    if (!(fieldName in view)) {
        throw (new Error("Trying to set error for field '" + fieldName + 
                         "' which does not exist in this view. The error " +
                         "message was: " + errorMsg));
    }
    
    view.$status[fieldName] = errorMsg;
}
 
/*
 *  ======== ptrToHex ========
 */
function ptrToHex(ptr)
{
    return ('0x' + String(ptr).substr(1));
}

/*
 *  ======== getShortName ========
 *  Parses canonical name for short name, returns either short name 
 *  or empty string "".
 */
function getShortName(name)
{
    /* Example: ti.sysbios.knl.Task@8000c5e9:myTsk0 */
    var index;
    if ((index = name.indexOf(':')) != -1) {
        return (name.substring(index + 1, name.length));
    }

    return ("");
}

var traceEnable;

/*
 *  ======== debugPrint ========
 */
function debugPrint(msg) {
    if (traceEnable === undefined) {
        traceEnable = xdc.jre.java.lang.System.getProperty("xdc.rov.traceEnable");
    }
    
    if (traceEnable == "true") {
        print("[Server    ] " + msg);
    }
}

/*
 *  ======== timestamp ========
 */
function timestamp(msg) {
    if (timestampFunc != undefined) {
        timestampFunc(msg);
    }
    else {
        var time = xdc.jre.java.lang.System.currentTimeMillis();
        Program.debugPrint("+++ (" + time + "ms) " + msg);
    }
}

/*
 *  ======== setTimestampFunc ========
 */
function setTimestampFunc(func)
{
    timestampFunc = func;
}
 
/*
 *  ======== resetMods ========
 */
function resetMods()
{
    modTab = new Object();
}

/*
 *  ======== exToString ========
 */
function exToString(e)
{
    /* Don't include the file name and line number if they're not present. */
    if ((e.message == undefined) || (e.fileName == undefined)
        || (e.fileName == "")) {
        return("" + e);
    }
    else {
        return('"' + e.fileName + '", line ' + e.lineNumber + ': ' + e.message);
    }
}

/*
 *  ======== moduleIdToName ========
 */
function moduleIdToName(mid)
{
    var modCfg = this.$modules['#' + mid];

    return !modCfg ? null : modCfg.$name;
}

/*
 *  @(#) xdc.rov; 1, 0, 0,237; 2-22-2010 10:33:39; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

