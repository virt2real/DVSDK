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
 *  ======== LoggerBuf.xs ========
 *
 *! Revision History
 *! ================
 *! 05-Mar-2008 sasha	added module$use with the fix for CQ24033
 */

var Logger;

/*
 *  ======== module$use ========
 */
function module$use()
{
    var Timestamp = xdc.module('xdc.runtime.Timestamp');

    Logger = this;
    
    /* bind LoggerSys.TimestampProxy to whatever Timestamp is using,
    *  unless LoggerSys.TimestampProxy was set already.
     */
    if (Logger.TimestampProxy == null) {
        Logger.TimestampProxy = Timestamp.SupportProxy.delegate$;
    }

    /* disable trace on timestamp proxy to prevent recursive callbacks */
    var Diags = xdc.module("xdc.runtime.Diags");
    var modName = Logger.TimestampProxy.delegate$.$name;
    Diags.setMaskMeta(modName, Diags.ALL & (~Diags.ASSERT), Diags.ALWAYS_OFF);
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init()
{
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

