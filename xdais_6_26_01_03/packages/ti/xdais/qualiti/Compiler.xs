/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
var os = java.lang.System.getProperty("os.name") + "";
var isWin = (os.match(/^Windows/i) != null);
var csd = String(xdc.csd()).replace(/\\/g,"/") + '/';

var thisMod;
var thisPkg;
var thisPkgDir;
var System;

function module$meta$init()
{
    thisPkg     = this.$package;
    thisPkgDir  = csd;
    thisMod     = this;
    System      = xdc.module( thisPkg.$name + ".System" );
}

function getCompilerInfo(algoParams, testSettings, cbPrintLog, detailLevel)
{

    cbPrintLog( "Determining compiler info.\n\n" );

    cbPrintLog( "Chcking if this library was created with a TI compiler...\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/";
        var cmd;
    var runResult;

    //noPrintFxn = function() {}; // nothing will be printed
    noPrintFxn = null;

    var isC6x = (algoParams.architecture == "C6x");

    cbPrintLog( "Attempting to determine library format...\n" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    /* get path of command being called */
    var ofdPath = System.getCommandPath(cgtoolsDir + "bin/ofd6x");

    // check for COFF or ELF format
    var libFormat = "UNKNOWN";
    var ofd_cmd = ofdPath + " -x --xml_indent=0 --obj_display=none " + libPath;
    runResult = System.runShellCommand(ofd_cmd, cbPrintLog, detailLevel);
    if (runResult.status == 0) {
        if (runResult.stdout.match(/<.*coff>/)) {
            libFormat = "COFF";
        }
        else if (runResult.stdout.match(/<.*elf>/)) {
            libFormat = "ELF";
        }
    }

    cbPrintLog( "The library is in " + libFormat + " format.\n\n" );

     /* check for TI compiler */
    if (libFormat == "COFF") {
        var isTICompiler = runResult.stdout.match(/<ti_coff>/) != null;
    }
    else {
        /* check by looking for "Texas Instruments in "DW_AT_producer" */
        ofd_cmd = ofdPath + " -g " + libPath;

        runResult = System.runShellCommand(ofd_cmd, cbPrintLog, detailLevel);

        var stdoutLines = runResult.stdout.split('\n');
        var isTICompiler = false;
        for (var i = 0; i < stdoutLines.length; i++) {
            if (stdoutLines[i].match('DW_AT_producer')) {
                isTICompiler = stdoutLines[i].indexOf("Texas Instruments") != -1;
                break;
            }
        }
    }

    cbPrintLog( "This library was " + (isTICompiler ? "" : "not ") + " created with a TI compiler.\n\n" );

    cbPrintLog( "Attempting to determine the compiler version...\n" );

    // check for compiler version using 'strings'/'find' command (linux/windows)
    // TI compilers should contain "Texas Instruments"
    // GCC compilers start with "GCC:"
    var compilerVersion = "UNKNOWN";

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);
    var searchTerm = isTICompiler ? 'Texas Instruments Inc' : 'GCC:';
    if (isWin) {
        var strings_cmd = System.getCommandPath("find") + ' ' + '"' + searchTerm + '"';
    }
    else {
        var strings_cmd = System.getCommandPath("strings");
    }
    cmd = strings_cmd + " " + libPath;

    runResult = System.runShellCommand(cmd, cbPrintLog, detailLevel);
    if (runResult.status == 0) {
        var stdoutLines = runResult.stdout.split('\n');
        for (var i = 0; i < stdoutLines.length; i++) {
            if (stdoutLines[i].match(searchTerm)) {
                compilerVersion = stdoutLines[i];
                break;
            }
        }
    }

    cbPrintLog( "The compiler is " + compilerVersion + ".\n" );

    return {
        isTICompiler: isTICompiler,
        isC6x: isC6x,
        libFormat: libFormat,
        version: compilerVersion
    };

}
/*
 *  @(#) ti.xdais.qualiti; 1, 0, 0,108; 9-18-2010 14:46:36; /db/wtree/library/trees/dais/dais-t03x/src/ xlibrary

 */

