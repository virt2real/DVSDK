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
 *  ======== run ========
 *  
 */

/* Don't load ti.dss when building the tree, it won't be on the path */
if (xdc.om.$name === undefined) {
    xdc.loadPackage("ti.dss");
}

function run( cmdr, args )
{         
    if (args.length != 4) {
        throw (new Error("xdc.rov.dss takes the path to the CCS config, the executable, an ROV command, and the isa"));
    }
    
    print("\n\n");
    
    print("Path to CCS config = " + args[0]);
    var config = args[0];
    
    print("Path to executable = " + args[1]);
    var executable = args[1]; 

    print("Command = " + args[2]);
    var command = args[2];
    
    print("ISA = " + args[3]);
    var isa = args[3]
    
    print("Getting scripting environment...");
    var script = Packages.com.ti.ccstudio.scripting.environment.ScriptingEnvironment.instance();

    //var isr = new xdc.jre.java.io.InputStreamReader(xdc.jre.java.lang.System["in"]);
    //var stdin = new xdc.jre.java.io.BufferedReader(isr);
    
    //script.traceBegin("MemoryTestLog.xml", "DefaultStylesheet.xsl")
    //script.traceSetConsoleLevel(Packages.com.ti.ccstudio.scripting.environment.TraceLevel.ALL)
    //script.traceSetFileLevel(Packages.com.ti.ccstudio.scripting.environment.TraceLevel.ALL)
    
    print("Getting debug server...");
    var server = script.getServer("DebugServer.1");
    server.setConfig(config);
    
    print("Opening debug session for *, *...");
    xdc.global.session = server.openSession("*", "*");
    
    print("CPU Name: " + session.getCPUName());    
    print("DSS Board Name: " + session.getBoardName() + "\n");

    print("Connecting target...");
    session.target.connect();
    
    /* Load test */
    print("Loading program...");
    session.memory.loadProgram(executable);
    
    /* Add a breakpoint at special symbol */
    var addr = session.symbol.getAddress("dsstest");
    session.breakpoint.add(addr);
    
    /* Run to the breakpoint */
    print("Running program...");
    session.target.run();

    /* Start the ROV server */
    startModel(executable);
    
    var Model = xdc.useModule('xdc.rov.Model');
    var response = Model.processCommand(command);
    print("Response = " + response);
    
    //processAllViews();
    
    /* Stop DSS */
    session.terminate();
    server.stop();
}

/*
 *  ======== startModel ========
 *  Create the MemoryImage, SymbolTable, and CallBack instances, locate the
 *  recap file, and start the ROV Model.
 */
function startModel(executable)
{
    print('Creating IMemoryReader Instance');
    var memInst = xdc.module('xdc.rov.dss.MemoryImage').create();
    /* Pass the DSS session into the memory reader. */
    memInst.$private.session = session;
    
    print('Creating ISymbolReader Instance'); 
    var symInst = xdc.module('xdc.rov.dss.SymbolTable').create();
        
    print('Creating ICallBack Instance');
    var callBack = xdc.module('xdc.rov.dss.CallBack').create();

    var recapFile = "";
    /* First check if this is a BIOS 5 executable */
    if (symInst.getSymbolValue("BIOS_start") != -1) {
        var Recap = xdc.useModule('ti.bios.rov.Recap');
        recapFile = Recap.locateRecap(symInst);
    }
    /* Otherwise, use the Vers tool to find the recap. */
    else {
        xdc.loadPackage('xdc.rta');
        recapFile = Packages.xdc.rta.Recap.locateRecap(executable, ".rov.xs");
    }
    
    var Model = xdc.useModule('xdc.rov.Model');
    /* Just pass Model.xmlVers, since we're not parsing the XML */
    Model.start(Model.xmlVers, recapFile, symInst, memInst, callBack);
}

function processAllViews(rovServer)
{
    var Program = xdc.useModule('xdc.rov.Program');
    var Model = xdc.useModule('xdc.rov.Model');
    
	try{
       // Create file 
	   var fstream = new java.io.FileWriter("C:/processAllViews.txt");
	   var out = new java.io.BufferedWriter(fstream);
	   
	}
	catch (e){
	    print("Error: " + e.getMessage());
	}
    
    var cmd = "";
    
    /* For each module in the system... */
    for each (var modName in Program.moduleNames) {

        var tabs = Program.getSupportedTabs(modName);
        
        for each (var tab in tabs) {
            cmd = "m " + modName + " " + tab.name;
            print("Processing command: " + cmd);
            out.write("Processing command: " + cmd + "\n");
            
            var response = Model.processCommand(cmd);
            print("Response = " + response);
            out.write("Response = " + response + "\n");
        }
    }

    out.close();
}
