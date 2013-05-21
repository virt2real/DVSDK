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
 *  ======== Cache.xs ========
 */

var Cache = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    Cache = this;

    if (Cache.Proxy == undefined || Cache.Proxy == null) {
        Cache.$logFatal("Cache.Proxy is not bound to " +
	    "OS specific implementation", this);
    }

    /* push diags and logger settings down to delegate */
    for (var dl in Cache.common$) {
           if (dl.match(/^diags_/) || dl.match(/^logger/)) {
            Cache.Proxy.delegate$.common$[dl] = Cache.common$[dl];
        }
    }
}

 /*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya   Review updates
 */
 /*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:51; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

