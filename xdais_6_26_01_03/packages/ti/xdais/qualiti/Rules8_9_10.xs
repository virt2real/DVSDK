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
// this section (declarations and module$meta$init) is common for all tests:
var csd = String(xdc.csd()).replace(/\\/g,"/") + '/';
var thisMod;
var thisPkg;
var thisPkgDir;
var ITest;
var System;

function module$meta$init()
{
    thisPkg     = this.$package;
    thisPkgDir  = csd;
    thisMod     = this;
    ITest       = xdc.module( thisPkg.$name + ".ITest" );
    System = xdc.module( thisPkg.$name + ".System" );
}

// reset function resets any state that needs to be reset
function reset()
{
}

// return the attributes of the test, by testId (if there are more than 1 here)
function getAttrs( testId )
{
    return {
        description:
            "(Rule 8) All external definitions must be either API identifiers or API and vendor prefixed.\n\n" +
            "(Rule 9) All undefined references must refer either to the operations specified in Appendix B (a subset of C runtime support library functions and a subset of the DSP/BIOS HWI API functions), or TI's DSPLIB or IMGLIB functions or other XDAIS-compliant modules.\n\n" +
            "(Rule 10) All modules must follow the eXpressDSP naming conventions for those external declarations disclosed to the client." +
            "",
    };
}

// test execution function
function run( testId, algoParams, testSettings, testDetailLevel, cbPrintLog )
{
    cbPrintLog( "Running test '" + testId + "'\n" );

    cbPrintLog( "Extracting names of global symbols defined by the algorithm...\n" );

    var cgtoolsDir = testSettings.cgtoolsDir + "/bin/";

    var cmd = System.getCommandPath( cgtoolsDir + "nm6x" );

    /* always call checkPath when passing a path to a command */
    var libPath = System.checkPath(algoParams.baseDir + "/" + algoParams.library);

    cmd += " -g " + libPath;

    // execute the command line
    var runResult = System.runShellCommand( cmd, cbPrintLog, testDetailLevel );

    // return if command failed
    if (runResult.status != 0) {
        return {
            status:        ITest.TEST_RUNERROR,
            statusDetails: "",
            runResult:     runResult,
        }
    }

    // do the work
    var stdout = runResult.stdout;

    // define prefix
    var MOD = algoParams.moduleName;
    var VEND = algoParams.vendor;
    var PREFIX = MOD + "_" + VEND + "_";

    cbPrintLog( "Verifying that all global symbols are named XXX_" + VEND + "_xxx ...\n" +
                "and that no blacklisted external references are made\n" );

    /* sample output:
      00000000 T _FIR_TI_exit
      00000000 T _FIR_TI_init
      00000064 T _FIR_TI_filter
      00000000 B _FIR_TI_myTables
      00000000 T _dummy1
      00000000 U _memcpy
      00000000 T _FIR_TI_activate
      00000000 T _FIR_TI_alloc
      00000000 T _FIR_TI_control
      00000000 T _FIR_TI_deactivate
      00000000 T _FIR_TI_free
      00000000 T _FIR_TI_initObj
      00000000 T _FIR_TI_moved
      00000000 T _FIR_TI_numAlloc
      00000000 U _IFIR_PARAMS
      00000000 U _memcpy
      00000000 B _FIR_TI_IALG
      00000000 B _FIR_TI_IFIR
      00000000 U _FIR_TI_activate
      00000000 U _FIR_TI_alloc
      00000000 U _FIR_TI_control
      00000000 U _FIR_TI_deactivate
      00000000 U _FIR_TI_filter
      00000000 U _FIR_TI_free
      00000000 U _FIR_TI_initObj
      00000000 U _FIR_TI_moved
      00000000 U _FIR_TI_numAlloc
    */

    // is this a package? todo: this should be a param passed on by the caller
    var isPackage = false;
    if (java.io.File( algoParams.baseDir + "/package.xdc" ).exists()) {
        isPackage = true;
    }

    // check all function names
    var badList   = [];
    var undefList = {};

    var stdoutLines = stdout.split( "\n" );
    for (var i = 0; i < stdoutLines.length; i++) {
        if (!stdoutLines[i].match(/ [TBCUD] /)) {
            continue;
        }
        var symType = stdoutLines[i].substr(9, 1);  // "T", "B", "C", "U" or "D"
        var symName = stdoutLines[i].substr(11);     // "_FIR_TI_free"
        if (symName == "") {
            continue;
        }
        if (symName.charAt(0) == "_") {
            symName = symName.substr(1); // eat the underscore
        }

        if ((symName == "I" + MOD + "_PARAMS") && (symType != "U")) {
            cbPrintLog("Found symbol '" + "I" + MOD + "_PARAMS', that's okay.\n");
            continue;
        }

        if ((symName.match(/.*__dummy__$/)) && (symType == "B") || (symType == "C")) {
            cbPrintLog( "Found bad symbol '...__dummy__' but pretending to have not because the algorithm is in an XDC package.\n" );
            continue;
        }

        // this is what we're looking for in a good symbol
        var r = new RegExp( "^[A-Z0-9]+_" + VEND + "_" );
        if (symName.match( r ) == null) {
            // maybe not a good name. first check if it's an allowed symbol; if not
            // either it's defined symbol, in which case it's
            // definitely not a good name, or it's an undefined reference; it it's
            // the latter we'll save it and check later against the black list
            var goodReference = false;
            if (symType != "U") {
                for (var j = 0; j < thisMod.allowedFxns.length && symType == "T"; j++) {
                    if (symName == thisMod.allowedFxns[j] ) {
                        goodReference = true;
                        break;
                    }
                }
                if (goodReference == false) {
                    badList[ badList.length ] = symName + (symType == "T" ? "()" : "");
                    cbPrintLog("Error: here-defined global name '" + badList[badList.length - 1] + "' does not comply.\n");
                }
            } else {
                undefList[symName] = true; // just remember, will analyze later
            }
        }
    }

    var statusDetails = "";
    var status = ITest.TEST_PASS;

    if (badList.length > 0) {
        if (badList.length == 1) {
            statusDetails += "Problem: Global " + (badList[0].match(/\(/) ? "function" : "object") +
                             " '" + badList[0] + "' is non-compliant as it does not have the \"" +
                             PREFIX + "\" (i.e. \"module_vendor_\") prefix.\n\n";
        } else {
            statusDetails += "Problem: Not all global symbols defined by the module have the \"" +
                             PREFIX + "\" prefix (i.e. module_vendor_).\n\n" +
                             "The following is the list of offending symbols:\n";
            for (var i = 0; i < badList.length; i++) {
                statusDetails += badList[i] + "\n";
            }
            statusDetails += "\n";
        }
        status = ITest.TEST_FAIL;
    }

    // check that external references are namespace-compliant

    var badReference = false;
    for (var j = 0; j < thisMod.disallowedFxns.length; j++) {
        if (undefList[ thisMod.disallowedFxns[j] ]) {
            cbPrintLog( "Error: external reference '" + thisMod.disallowedFxns[j] + "' is not allowed.\n" );
            if (badReference == false) {
                badReference = true;
                statusDetails += "Problem: The algorithm makes the following disallowed external references:\n";
            }
            statusDetails += "  - " + thisMod.disallowedFxns[j] + "\n";
        }
    }

    if (badReference) {
        statusDetails += "\nPlease check that these references are resolved via allowed functions in RTS, IMG, DSP, ACPYx libraries.\n\n" +
                         "For your reference, the following external references are not allowed:\n";
        for (var j = 0; j < thisMod.disallowedFxns.length; j++) {
            statusDetails += "  - " + thisMod.disallowedFxns[j] + "\n";
        }
        status = ITest.TEST_FAIL;
    }

    if (status == ITest.TEST_PASS) {
        return {
            status: ITest.TEST_PASS,
            statusDetails: "Test passed.",
        };
    }
    else{
        return {
            status: ITest.TEST_FAIL,
            statusDetails: "Test failed. " + statusDetails,
        };
    }
}

/*
 *  @(#) ti.xdais.qualiti; 1, 0, 0,108; 9-18-2010 14:46:37; /db/wtree/library/trees/dais/dais-t03x/src/ xlibrary

 */

