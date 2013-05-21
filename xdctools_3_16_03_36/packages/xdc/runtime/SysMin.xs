/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
/*
 *  ======== SysMin.xs ========
 *
 *! Revision History
 *! ================
 *! 13-Jun-2007 nitya	Place buffer
 *! 28-Nov-2006 toddm	Start revision history
 */

/*
 *  ======== module$static$init ========
 */
function module$static$init(obj, params)
{
    obj.outbuf.length = params.bufSize;
    if (params.bufSize != 0) {
        var Memory = xdc.module('xdc.runtime.Memory');
        Memory.staticPlace(obj.outbuf, 0, params.sectionName);
    }

    obj.outidx = 0;
    obj.wrapped = false;  
}

/*
 *  ======== module$use ========
 */
function module$use(obj, params)
{
}

/*
 *  ======== viewInitModule ========
 *
 */
function viewInitModule(view, mod)
{
    view.outBuf = mod.outbuf;
    view.outBufIndex = mod.outidx;
    view.wrapped = mod.wrapped;
}

/*
 *  ======== viewInitOutputBuffer ========
 *
 */
function viewInitOutputBuffer(view)
{
    var Program = xdc.useModule('xdc.rov.Program');
    
    /* Retrieve the module's state */
    var rawView = null;
    try {
        rawView = Program.scanRawView('xdc.runtime.SysMin');
    }
    catch (e) {
        var elem = Program.newViewStruct('xdc.runtime.SysMin', 'OutputBuffer');
        elem.entry = "";
        elem.$status["entry"] = "Problem retrieving raw data: " + e.toString();
        return;
    }
    
    /* Get the buffer size from the configuration. */
    var bufSize = Program.getModuleConfig('xdc.runtime.SysMin').bufSize;
    
    /* Read in the outbuf */    
    var outbuf = null;
    try {
        outbuf = Program.fetchArray(rawView.modState.outbuf$fetchDesc, 
                                    rawView.modState.outbuf, bufSize);
    }    
    catch (e) {
        var elem = Program.newViewStruct('xdc.runtime.SysMin', 'OutputBuffer');
        elem.entry = "";
        elem.$status["entry"] = "Problem reading outbuf: " + e.toString();
        return;
    }
    
    var elements = new Array();
  
    /* Create Data Elements for each of the strings in the buffer. */
    var str = "";
    for each (var c in outbuf) {
        var ch = String.fromCharCode(c);
        str += ch;
        
        if (ch == '\0') {
            break;
        }
        
        /* 
         * If this is the end of the string, create a new data element 
         * for it. 
         */
        if (ch == '\n') {
            var elem = Program.newViewStruct('xdc.runtime.SysMin', 'OutputBuffer');
            elem.entry = str;           
            elements[elements.length] = elem;
            str = "";
        }
    }

    view.elements = elements;
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

