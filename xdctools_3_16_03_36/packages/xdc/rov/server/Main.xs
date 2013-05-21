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
 *  ======== Main.xs ========
 *  The xdc.rov.server services ROV data requests from the ROV GUI in CCS 4.
 *  This server is not generic to the ROV core, but is specific to the ROV
 *  GUI in CCS 4. Other ROV-based tools (such as the ROV test scripts) would
 *  provide their own version of this server.
 */

var controller;
var nodeFactory;
 
/*
 *  ======== run ========
 *
 */
function run(cmdr, args)
{
    xdc.global.Program = xdc.useModule('xdc.rov.Program');

    Program.timestamp("Beginning of xdc.rov.server Main.xs run.");
    
    /* Read in the 'version' from the command line. */
    var pluginVers = this.version;
    Program.debugPrint("Version = " + pluginVers);
    
    /* Read in the path to the executable from the command line. */
    var executable = this.executable.replace(/\\/g, '/');
    Program.debugPrint("Executable = " + executable);
    
    /* Read in the controller index from the command line. */
    var controllerIndex = parseInt(this.controllerIndex); 
    Program.debugPrint("Controller = " + controllerIndex);  

    /* Verify the versions match. */
    if (!checkVersion(pluginVers, this.serverVers)) {
        cmdr.write("There is a version mismatch between the ROV server and " +
                   "the ROV plugin. Make sure the most recent XDC tools " +
                   "version is selected.");
        return;
    }
    
    /* Create the symbol table */
    Program.debugPrint('Creating ISymbolReader Instance'); 
    var SymbolTable = xdc.useModule('xdc.rov.server.DSSymbolReader');
    var symInst = SymbolTable.create(controllerIndex);
    
    /* Create the call back */
    Program.debugPrint('Creating ICallBack Instance');
    var CallBack = xdc.useModule('xdc.rov.server.DSCallBack');
    var callBack = CallBack.create(controllerIndex);
    
    /* Notify the CallBack that we are loading the recap file. */
    callBack.updateStartupProgress(60, "Loading ROV recap file ...");
    
    /* Locate the Recap file */
    var recap;
    try {
        recap = getRecap(executable, symInst);
    }
    catch (e) {
        var msg = e.message;
        
        /* 
         * Strip the java.lang.Exception from the message before returning
         * it. 
         */
        var index = msg.indexOf("Exception: ");
        if (index != -1) {
            msg = msg.substring(index + String("Exception: ").length);
        }
        
        Program.debugPrint("Failed to find recap file: " + msg);
        cmdr.write(msg);
        return;
    }
    
    /*
     * Ensure that the stdTypes array includes the t_Size type.
     * This is done to preserve compatibility with applications built with
     * older tools.
     * This code can be removed when XDC tools no longer supports applications
     * built with:
     *   - XDCtools older than 3.15.04.70
     *   - BIOS 5 older than 5.41.00.06
     */
    if (recap.build.target.stdTypes['t_Size'] === undefined) {
        var mapTo;
        
        var targName = recap.build.target.name;
        
        /* For these named targets, t_Size maps to t_Int32. */
        if ((targName == "C28") ||
            (targName == "C28_large") ||
            (targName == "C28_float") ||
            (targName == "C55_huge")) {
            mapTo = "t_Int32";
        }
        /* For all other targets, it maps to t_Int. */
        else {
            mapTo = "t_Int";
        }
        
        recap.build.target.stdTypes['t_Size'] = {
            size: recap.build.target.stdTypes[mapTo].size,
            align: recap.build.target.stdTypes[mapTo].align
        };
    }
    
    /* Get a handle to the ROV Controller */
    controller = xdc.jre.com.ti.dvt.server4.ControllerMap.getController(controllerIndex);
        
    /* Create the memory reader */
    Program.debugPrint('Creating MemoryReader Instance');
    
    /* Get the IMemoryImage instance from the Controller. */
    var iMemInst = controller.getMemoryReader();
    
    /* Get the target endianess and convert from string to enum. */
    var endianStr = recap.build.target.model.endian;
    var endian = Packages.xdc.rov.TargetType.strToEndianess(endianStr);
   
    /* Get the MAU size. */
    var bitsPerChar = recap.build.target.bitsPerChar;
    
    /* Create the MemoryImage instance */
    var memInst = new Packages.xdc.rov.MemoryImage(iMemInst, endian, 
                                                   bitsPerChar);
       
    Program.debugPrint('Starting ROV Model');
    var Model = xdc.useModule('xdc.rov.Model');    
    
    /* The ROV Model will verify that the XML versions match. */
    var xmlVers = parseInt(pluginVers.split('.')[0]);
    Program.debugPrint("xmlVers = " + xmlVers);
    
    /* If startModel throws any exceptions, report them back and exit. */
    try {
        Model.start(xmlVers, executable, recap, symInst, memInst, callBack);
    }
    catch (e) {
        var exception = Program.exToString(e);
        Program.debugPrint("Caught exception while starting ROV: " + exception);
        /*
         * Just write the message, we don't need an <Exception> tag here. 
         * The plugin looks for "started", and if the message is anything else,
         * it displays that as an error.
         */
        cmdr.write("Caught exception while starting ROV: " + exception);
        return;
    }

    /*
     * TODO - This is a temporary workaround to resolve a class loader issue.
     * Ideally, this API should just be called from the LoggerBuf Records view.
     * However, the view is called through a java call back mechanism which 
     * means that the view code actually has a different Java context. To work
     * around this, we create the LoggerBufDecoder while initializing the ROV
     * server, when we're still in the context of the xdc.tools.Server.
     */
    var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
    LoggerBuf.initDecoder();
    
    /* 
     * Set up the Java callback mechanism which allows for the ROV plugin to
     * call down to the ROV server.
     * We create a JavaScript object which implements the IServer interface
     * defined by the ROV plugin, then wrap this with a Java object. 
     * We then pass this Java object back to the ROV plugin so that it may
     * use it to call into the ROV server.
     */
    var iserver = new xdc.jre.com.ti.dvt.server4.servers.IServer({
                            clearCache: clearCache,
                            listModules: listModules,
                            retrieveView: retrieveView
                        });

    controller.setServer(iserver);
    
    /* Notify the ROV plugin that the server initialization is complete. */
    controller.serverInitialized = true;

    /* The NodeFactory is used to create GUI nodes for the views. */
    nodeFactory = xdc.jre.com.ti.dvt.server4.NodeFactory;
    
    Program.debugPrint("Done with startModel");
    
    /* Write 'started' to indicate that the server has started successfully. */
    cmdr.write("started");
    
    /* Wait for commands and process them as they come in. */
    Program.debugPrint("xdc.rov.server.Main: rov.server ready to receive commands.");
    
    var Model = xdc.useModule('xdc.rov.Model');
    
    while (true) {
        //var input = stdin.readLine();
        var input = String(cmdr.read());
        Program.timestamp("Server received request: " + input);
        
        if (input == "q") {
            Program.debugPrint("rov.server received quit command.");
            break;
        }
        else {
            print("Received unexpected command: " + input);
        }
    }
    
    Program.debugPrint("rov.server returning from 'run'.");
    /* Write empty string to acknowledge server quit. */
    cmdr.write("");
}

/*
 *  ======== clearCache ========
 *
 */
function clearCache()
{
    /* Clear Cache */
    Program.debugPrint("Clearing server cache...");
    Program.resetMods();
}

/*
 *  ======== listModules ========
 *
 */
function listModules(root)
{
    var Model = xdc.useModule('xdc.rov.Model');
     
    /* Get the JavaScript representation of the module heirarchy. */
    var modList = Model.getModuleList();
    
    var rootPkgs = new Array();
    
    for (var i = 0; i < modList.subPkgs.length; i++) {
        rootPkgs[i] = modListRecur(modList.subPkgs[i]);
    }

    return (rootPkgs);
}

/*
 *  ======== modListRecur ========
 *  Recursively copy the module heirarchy from the JavaScript object to the
 *  Java one.
 */
function modListRecur(pkg)
{
    var newPkg = nodeFactory.createPackage(pkg.name, pkg.fullName, (pkg.subPkgs.length != 0));
    
    /* Array of the package's children, both modules and subpackages. */
    var children = new Array();
    
    /* Copy over each of the sub packages. */
    for each (var subPkg in pkg.subPkgs) {        
        /* Fill in the package's modules and sub packages. */
        children[children.length] = modListRecur(subPkg);
    }
    
    /* Copy over each of the modules. */
    for each (var mod in pkg.modules) {

        var newMod = nodeFactory.createModule(mod.name, mod.fullName);        
        
        /* Copy over the module's tabs. */
        var tabs = new Array();
        
        for each (var tab in mod.tabs) {
            tabs[tabs.length] = nodeFactory.createTab(tab.name, tab.type);
        }
        
        newMod.setTabs(tabs);
        
        /* Add the module to the package's list */
        children[children.length] = newMod;
    }
    
    newPkg.setChildren(children);
    
    return (newPkg);
}

/*
 *  ======== retrieveView ========
 */
function retrieveView(modName, tabName)
{
    var viewType = Program.getViewType(modName, tabName);

    var ViewInfo = xdc.useModule('xdc.rov.ViewInfo');
    
    var begin = java.lang.System.currentTimeMillis();
    
    /*
     * The first step in any view is to call the appropriate Program.scan
     * function. We call those here in this try-catch block so the code for
     * handling the exceptions is all in one place.
     */
    var msgOk = "ROV detected errors in scan of";
    try {
        switch (String(viewType)) {
            case String(ViewInfo.MODULE):
                Program.scanModuleView(modName, tabName);
                break;
            case String(ViewInfo.INSTANCE):
                Program.scanInstanceView(modName, tabName);
                break;
            case String(ViewInfo.INSTANCE_DATA):
                Program.scanInstanceDataView(modName, tabName);
                break;
            case String(ViewInfo.MODULE_DATA):
                Program.scanModuleDataView(modName, tabName);
                break;
            case String(ViewInfo.RAW):
                Program.scanRawView(modName);
                break;
            default:
                throw (new Error("Undefined view type: " + viewType));
                break;
        }
    }
    catch (e) {
        /*
         * Program.scan* will intentionally throw exceptions to
         * force user to handle them. 
         * If this is that type of excpetion, continue on.
         * Otherwise, report the exception directly instead of continuing.
         */  
        if (!e.message.substring(0, msgOk.length).equals(msgOk)) {
            throw (e.message);
        }
    }
    
    Program.debugPrint("Retrieving the whole view took " + (java.lang.System.currentTimeMillis() - begin));

    begin = java.lang.System.currentTimeMillis();
    /*
     * At this point, the appropriate 'scan' API has been called and the data
     * is ready to be formatted for the GUI.
     */
    switch (String(viewType)) {
        case String(ViewInfo.MODULE):
            view = retrieveModuleView(modName, tabName);
            break;
        case String(ViewInfo.INSTANCE):
            view = retrieveInstanceView(modName, tabName);
            break;
        case String(ViewInfo.INSTANCE_DATA):
            view = retrieveInstanceDataView(modName, tabName);
            break;
        case String(ViewInfo.MODULE_DATA):
            view = retrieveModuleDataView(modName, tabName);
            break;
        case String(ViewInfo.RAW):
            view = retrieveRawView(modName);
            break;
        default:
            throw (new Error("Undefined view type: " + viewType));
            break;
    }
    
    Program.debugPrint("View to GUI took " + (java.lang.System.currentTimeMillis() - begin));

    /* TODO - Supposed to check for abort here? Possible that returning the value would confuse it? */
    return (view);
}

/*
 *  ======== retrieveModuleView ========
 *  Retrieve the specified module-type view. Call Program.getViewType to 
 *  determine which Model.retrieve* API to call.
 *  Returns an XML formatted string representing the view.
 */
function retrieveModuleView(modName, tabName)
{   
    /* Get the view manually in case it threw an exception. */
    var modDesc = Program.getModuleDesc(modName);
    var modView = modDesc.viewMap[tabName];
    
    var viewName = modName + "." + tabName;
    
    /* Get the error if there is one. */
    var error = "";
    if (modDesc.error) {
        error = modDesc.error;
    }        
    
    /* Create the ContentNode to represent the view. */
    var nodes = new Array();
    nodes[0] = viewToNode(viewName, modView, error);
    
    return (nodes);
}


/*
 *  ======== retrieveInstanceView ========
 *  Retrieve the specified instance-type view. Call Program.getViewType to 
 *  determine which Model.retrieve* API to call.
 *  Returns an XML formatted string representing the view.
 */
function retrieveInstanceView(modName, tabName)
{                  
    var mod = Program.getModuleDesc(modName);
                
    var count = 0;
    
    /* Get the instance views, add them to the XML output */
    Program.debugPrint("mod.instances.length = " + mod.instances.length);
    
    /* Convert each instance to XML. */
    var instances = new Array();
    
    var viewName = modName + "." + tabName;
    
    for (var i in mod.instances) {
        var view = mod.instances[i].viewMap[tabName];

        /* Get the error if there is one. */
        var error = "";
        if (mod.instances[i].error) {
            error = mod.instances[i].error;
        }        
        
        /* Add the instance to the array. */
        instances[instances.length] = viewToNode(viewName, view, error);
    }
    
    return (instances);
}

/*
 *  ======== retrieveInstanceDataView ========
 *  Retrieve the specified instance-data-type view. Call Program.getViewType to
 *  determine which Model.retrieve* API to call.
 *  Returns an XML formatted string representing the view.
 */
function retrieveInstanceDataView(modName, tabName)
{
    var modDesc = Program.getModuleDesc(modName);
    var dataArr = modDesc.viewMap[tabName];
    
    var viewName = modName + "." + tabName;
    
    /* Create the root node, which is just the module name. */
    var root = nodeFactory.createNode(modName);
    
    /* Create the array of instances */
    var instances = new Array();
    
    /* Add each instance. */
    for each (var instView in dataArr) {
        var inst = nodeFactory.createNode(instView.label);
        
        /* Create an array of all of the data elements */
        var elements = new Array();
        for each (var elem in instView.elements) {
            var node = viewToNode(viewName, elem, "");
            
            /* Use the value in the first column as the name of the node. */
            var nodeName = node.getProperties()[0].getValue();
            node.setDisplayName(nodeName);
            
            elements[elements.length] = node;
        }
        
        /* Add the data elements to the instance. */
        inst.setChildren(elements);
        
        /* Add the instance to list */
        instances[instances.length] = inst;
    }
    
    root.setChildren(instances);
    
    /* Expand the root node to display all of the instances. */
    root.setExpandAll(true);
    
    var nodes = new Array();
    nodes[0] = root;
    
    return (nodes);    
}

/*
 *  ======== retrieveModuleDataView ========
 *  Retrieve the specified module-data-type view. Call Program.getViewType
 *  to determine which Model.retrieve* API to call.
 *  Returns an XML formatted string representing the view.
 */
function retrieveModuleDataView(modName, tabName)
{
    var modDesc = Program.getModuleDesc(modName);
    var dataView = modDesc.viewMap[tabName];
    
    var viewName = modName + "." + tabName;
    
    var elements = new Array();
    
    /* Add each data element */
    for each (var elem in dataView.elements) {
        elements[elements.length] = viewToNode(viewName, elem, "");
    }
            
    return (elements);
}

/*
 *  ======== retrieveRawView ========
 *  The raw tab is handled specially because of it's more generic nature and
 *  the complexity of displaying the configuration object.
 *  All of the functions that follow are to support the raw tab.
 */
function retrieveRawView(modName)
{
    var viewName = modName +".Raw";
    
    /* Array of root nodes to return */
    var nodes = new Array();
    
    /* Get the module descriptor */
    var modDesc = Program.getModuleDesc(modName);

    /* Add the module state. */
    var modStateNode = strToNode(viewName, "Module State", modDesc.state, 0);
    nodes[0] = modStateNode;
    
    /* Add the instance states. */
    var instStateNode = nodeFactory.createNode("Instance States");
    var instStates = new Array();
    for each (var instDesc in modDesc.instances) {
        var elemName = Program.getShortName(instDesc.state.$label);
        if (elemName == "") {
            elemName = String(instDesc.state.$addr);
        }
        instStates[instStates.length] = strToNode(viewName, elemName, instDesc.state, 0);
    }
    
    instStateNode.setChildren(instStates);
    
    nodes[1] = instStateNode;
    
    /* Add the module config info */
    var modCfg = Program.getModuleConfig(modName);
    var modCfgNode = strToNode(viewName, "Configuration", modCfg, 0);

    nodes[2] = modCfgNode;
    
    return (nodes);
}

/*
 *  ======== strToNode ========
 *  Takes an arbitrary structure and turns it into a ContentNode. 
 *  To avoid loops, it will only go down five levels of objects.
 */
function strToNode(viewName, objName, obj, level)
{
    if ((level != undefined) && (level != -1)) {
        level++;
    }
    
    /* Create a node to represent the structure. */
    var node = nodeFactory.createNode(objName);
    
    /* 
     * Create arrays for the structure's fields (properties) and object
     * handles (children).
     */
    var properties = new Array();
    var children = new Array();
    
    /* Handle each of the structure's fields. */
    for (var field in obj) {       
        var value = obj[field];
        
        /* If this field is an object... */
        if (value && (typeof value) == 'object') {
            /* If this is an address or an enum (an Addr or EnumVal object)... */
            if (('$category' in value) && 
                ((value.$category == 'Addr') || 
                 (value.$category == 'EnumVal'))) {
                properties[properties.length] = 
                    nodeFactory.createProperty(viewName, field, String(value),
                                               "");
            }
            /* Otherwise it's just another structure... */
            else {
                if (level == 5) {
                    properties[properties.length] = 
                        nodeFactory.createProperty(viewName, field, 
                                                   "ROV reached max depth (5)",
                                                   "");
                }
                else {
                    children[children.length] = strToNode(viewName, field, 
                                                          value, level);
                }
            }
        }
        /* If the field is just a scalar value... */
        else {
            properties[properties.length] = 
                nodeFactory.createProperty(viewName, field, String(value), "");
        }
    }

    /* Sort the properties and children alphabetically. */
    properties = nodeFactory.sortProperties(properties);
    children = nodeFactory.sortNodes(children);
    
    node.setProperties(properties);
    node.setChildren(children);
    
    return (node);
}

/* 
 *  ======== viewToNode ========
 * Creates a ContentNode to represent the given view structure. 
 */
function viewToNode(viewName, view, error)
{
    /* Create a node to represent the instance. */
    var inst = nodeFactory.createNode("");
    
    /* Create the properties array. */
    var properties = new Array();
    
    /* 
     * Address field is added explicitly because it doesn't show up in 
     * the for/in loop.
     */
    if ('address' in view) {
        properties[0] = nodeFactory.createProperty(viewName, "address", 
                                                  view.address, error);
    }

    /* Fill in all of the properties. */
    for (var p in view) {
    
        /* If the status is undefined, don't include this field. */
        if (view.$status[p] === undefined) {
            continue;
        }
        
        var pError = "";
        if (view.$status[p] != null) {
            pError = view.$status[p];
        }
        
        /* If the field is an array... */
        if ((view[p]) && (view[p].$category == 'Vector')) {                
            /* Create a drop down for the array values. */
            var arr = new Array();
            for (var j = 0; j < view[p].length; j++) {
                arr[j] = view[p][j];
            }                
            properties[properties.length] = nodeFactory.createDropDown(viewName, p, arr, pError); 
        }
        /* If the field didn't get filled in, display an empty box */
        else if (view[p] == undefined) {
            properties[properties.length] = nodeFactory.createProperty(viewName, p, "", pError);
        }
        /* If this is just a normal field. */
        else {
            properties[properties.length] = nodeFactory.createProperty(viewName, p, view[p], pError);
        }            
    }
    
    /* Set the instance's properties. */
    inst.setProperties(properties);
    
    return(inst);
}

/* 
 * ======== checkVersion ========
 * The pluginVers parameter is a version string passed down from the ROV plugin
 * that contains two keys:
 *    <xml version>.<server version>
 * 
 * The ROV Model will verify that the xml version matches later.
 *
 * This API verifies that the server version matches the version of the 
 * xdc.rov.server.
 */
function checkVersion(pluginVers, thisVers)
{
    /* Fail if the plugin did not pass in a version. */
    if (pluginVers == "") {
        return (false);
    }
    
    /* Otherwise, check if the versions are compatible. */
    var keys = pluginVers.split('.');

    /* Second key is the ROV Server version. */
    var serverVers = parseInt(keys[1]);
    Program.debugPrint("serverVers = " + serverVers);
    
    /* Verify the ROV Server version matches the current version. */
    if (serverVers != thisVers) {
        Program.debugPrint("Plugin version " + serverVers + " does not " +
                           "match server version " + thisVers);
        return (false);
    }
    
    return (true);
}

/*
 *  ======== getRecap ========
 *  This API does not catch any exceptions, so it should be called from a 
 *  try / catch block in 'run'.
 */
function getRecap(executable, symInst)
{
    var Program = xdc.useModule('xdc.rov.Program');
    
    Program.debugPrint('Retrieving Recap File');  
    
    /* First check if this is a BIOS 5 executable */
    if (symInst.getSymbolValue("BIOS_start") != -1) {
        Program.debugPrint("Detected BIOS 5 executable...");
        
        /* Use the BIOS 5 Recap module to find the appropriate file. */
        var Recap = xdc.useModule('ti.bios.rov.recaps.Recap');
        recapFile = Recap.locateRecap(symInst);
        
        Program.debugPrint("Found BIOS 5 recap file: " + recapFile);
        
        /* 
         * Load the ti.bios.rta package for decoding LOG records.
         * This must be done in the main server thread, it can't be done in
         * the LOG view.
         */
        xdc.loadPackage('ti.bios.rta');
        
        /* Load the recap */
        var recap = xdc.loadCapsule(recapFile);
        
        return (recap);
    }
    
    /* Otherwise, check if it is a RTSC app */
    
    /* Use the xdc.rta.Recap class to find the recap file. */
    xdc.loadPackage('xdc.rta');
    recapFile = Packages.xdc.rta.Recap.locateRecap(executable, ".rov.xs");
        
    Program.debugPrint("Found RTSC recap file: " + recapFile);
    
    /* Load the recap */
    var recap = xdc.loadCapsule(recapFile);
    
    return (recap);
}