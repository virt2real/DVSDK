/* 
 *  Copyright (c) 2008 Texas Instruments and others.
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
 *  ======== exec ========
 */
function exec(cmd, path)
{
    function readOutput(oExec)
    {
        if (!oExec.StdOut.AtEndOfStream) {
            return oExec.StdOut.ReadAll();
        }
    
        if (!oExec.StdErr.AtEndOfStream) {
            return oExec.StdErr.ReadAll();
        }
    
        return -1;
    }

    var shell = WScript.CreateObject("WScript.Shell");
    var env = shell.Environment("PROCESS");
    var envTab = ["INCLUDE", "LIB", "LINK", "CL"];
    for (i = 0; i < envTab.length; i++) {
        var val = env(envTab[i]);
        if (val != null && val.length != 0) {
            env.Remove(envTab[i]);
        }
    }
    if (path != null) {
        env("PATH") = path;
    }

    var oExec = shell.Exec(cmd);
    var result = "";
    
    var tryCount = 0;
    while (true) {
        var input = readOutput(oExec);
        if (-1 == input) {
            if (tryCount++ > 10 && oExec.Status == 1) {
                break;
            }
        }
        else {
            result += input;
            tryCount = 0;
        }
    }
    
    WScript.Echo(result);
    return (oExec.ExitCode);
}

var args = WScript.Arguments;
var cmd = "";
var quote = "";
for (var i = 0; i < args.length; i++) {
    cmd += quote + args(i) + quote + " ";
    quote = '"';
}

var msdev = "c:/users/dr/cg/msvc32";

WScript.Quit(
    exec(cmd, "%WINDIR%;%WINDIR%/system32;"
                + msdev + "/vc98/bin;"
                + msdev + "/common/msdev98/bin"
    )
);
/*
 *  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

