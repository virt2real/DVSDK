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
    print("usage: load [-a] [-c config.xml] prog");
    java.lang.System.exit(1);
}

var config = null;
var aflag = false;

while (arguments[0][0] == '-') {
    switch (arguments[0][1]) {
        case 'a': {
            aflag = true;
            break;
        }
        case 'c': {
            config = arguments[1];
            arguments.shift();
            break;
        }
    }
    arguments.shift();
}

/* if no debug config file is specified, use one in the current directory */
if (config == null) {
    config = "./SystemConfig.xml";
}

// Import the DSS packages into our namespace to save on typing
importPackage(Packages.com.ti.debug.engine.scripting);
importPackage(Packages.com.ti.ccstudio.scripting.environment);

// Create our scripting environment object
var script = new ScriptingEnvironment();

// only show warnings or worse (the default is much more verbose)
script.traceSetConsoleLevel(TraceLevel.WARNING);
//script.traceBegin("Log.xml", "DefaultStylesheet.xsl");
//script.traceSetFileLevel(TraceLevel.ALL);

// Get the Debug Server and start a Debug Session
var debugServer = script.getServer("DebugServer.1");
debugServer.setConfig(config);

var debugSession = debugServer.openSession(".*");

// Connect to the Target
debugSession.target.connect();

// Load a program
// (ScriptingEnvironment has a concept of a working folder and for all of
// the APIs which take path names as arguments you can either pass a relative
// path or an absolute path)
print("loading " + arguments[0] + " ...");
debugSession.memory.loadProgram(arguments[0]);
print("starting " + arguments[0] + " ...");

if (aflag == false) {
    // Set a breakpoint at "exit"
    var progExit = debugSession.symbol.getAddress("xdc_runtime_System_exit__F");
    var bp1 = debugSession.breakpoint.add(progExit);

    // Run.  Should halt at first BP
    debugSession.target.run();

    // Using an expression - get the current value of the PC
    var pc = debugSession.expression.evaluate("PC");

    // Verify we halted at the correct address.
    if (pc != progExit) {
        print("FAIL: Expected halt at 0x" + Long.toHexString(progExit)
              + ", actually halted at 0x" + Long.toHexString(pc));
    }
}
else {
    // let 'r rip!
    debugSession.target.runAsynch();
    debugSession.target.disconnect();
}

// All done

debugSession.terminate();
debugServer.stop();

java.lang.System.exit(0);

/*
 *  @(#) ti.platforms.ez430_rf2500; 1, 0, 0, 1,13; 2-23-2010 17:00:56; /db/ztree/library/trees/platform/platform-k32x/src/
 */

