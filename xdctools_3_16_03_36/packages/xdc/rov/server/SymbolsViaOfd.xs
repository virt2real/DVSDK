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
 *  ======== instance$meta$init ========
 *  This function initializes the SymbolReader instance by
 *  reading symbols from executable using the ofd utility
 */

function instance$meta$init(fname, ofdExe)
{   
    this.$private.symbolTable = new Object();
    
    var File = xdc.module('xdc.services.io.File');
    var file = File.getCanonicalPath(fname);

    if (file == null) {
        throw new Error(" can't find executable named'" + fname
            + "' along the path '" + xdc.curPath() + "'");
    }
    
    var ofdproc = xdc.jre.java.lang.Runtime.getRuntime().exec(ofdExe + " -x " + file);

    // Code from xdc.tci
    var br = new xdc.jre.java.io.BufferedReader(new xdc.jre.java.io.InputStreamReader(ofdproc.getInputStream()));

    var sb = new java.lang.StringBuilder();

    var line = "";
    while ((line = br.readLine()) != null) {
        sb.append(line);
    }

    var XMLobject = new XML(sb.toString());
    var symbols = XMLobject.object_file.ti_coff.symbol_table.symbol;

    for (var i in symbols) {
       if (symbols[i].storage_class == "C_EXT") {
           this.$private.symbolTable[symbols[i].name] = 
	       Number(symbols[i].value);
       }
    }
}	


/*
 *  ======== lookUpSymbol ========
 *  This function returns the address of the requested symbol
 */
function lookupSymbol(symbolName)
{
    return(this.$private.symbolTable[symbolName]);
}

/*
 *  ======== lookupAddr ========
 *  This function returns an array of symbols that have the specified value.
 */
function lookupAddr(addr)
{
    var symArr = new this.$module.SymsArr();
    var symTable = this.$private.symbolTable;

    for (var i in  symTable) {
        if (symTable[i] == addr) {
            symArr.$add(i);
        }
    }

    return symArr;
}

