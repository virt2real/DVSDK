/*
 *  Copyright (c) 2010 by Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

if (arguments.length < 1) {
    print("usage: load prog");
    java.lang.System.exit(1);
}
print("loading " + arguments + " ...");

// Import the DSS packages into our namespace to save on typing
importPackage(Packages.com.ti.debug.engine.scripting);
importPackage(Packages.com.ti.ccstudio.scripting.environment);
importPackage(Packages.java.lang);

// Create our scripting environment object - which is the main entry point into any script and
// the factory for creating other Scriptable ervers and Sessions
var script = new ScriptingEnvironment();

// Create a log file in the current directory to log script execution
script.traceBegin("BreakpointsTestLog.xml", "DefaultStylesheet.xsl");

// Set our TimeOut
script.setScriptTimeout(20000);

// Log everything
script.traceSetConsoleLevel(TraceLevel.ALL);
script.traceSetFileLevel(TraceLevel.ALL);

// Get the Debug Server and start a Debug Session
debugServer = script.getServer("DebugServer.1");
print("####server created.");
debugServer.setConfig("./SystemSetup.xml");
print("####setConfig done.");

debugSession = debugServer.openSession(".*");
print("####openSession done.");

// Reset our Target
debugSession.target.connect();
print("####reset done.");

// Load a program
// (ScriptingEnvironment has a concept of a working folder and for all of the APIs which take
// path names as arguments you can either pass a relative path or an absolute path)
debugSession.memory.loadProgram(arguments[0]);
print("loaded app.out ...");

// Set a breakpoint at "foo"
var main = debugSession.symbol.getAddress("foo");
var bp1 = debugSession.breakpoint.add(main);

// Run.  Should halt at first BP
debugSession.target.run();

// Using an expression - get the current value of the PC
nPC = debugSession.expression.evaluate("PC");

// Verify we halted at the correct address.  Use the Static Java method Long.toHexString() to convert the
// result to a hex string when logging messages
if (nPC == main) {
    script.traceWrite("SUCCESS: Halted at correct location");
}
else {
    script.traceWrite("FAIL: Expected halt at 0x" + Long.toHexString(main) + ", actually halted at 0x" + Long.toHexString(nPC));
}

// let 'r rip!
debugSession.target.runAsynch();

// All done
debugSession.terminate();
debugServer.stop();

// Close our Log File
script.traceEnd();

java.lang.System.exit(0);

/*
 *  @(#) ti.platforms.ez430_rf2500; 1, 0, 0, 1,13; 2-23-2010 17:00:56; /db/ztree/library/trees/platform/platform-k32x/src/
 */

