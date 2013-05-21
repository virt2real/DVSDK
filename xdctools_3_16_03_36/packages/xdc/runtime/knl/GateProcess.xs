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
 *  ======== GateProcess.xs ========
 */

var GateProcess = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    GateProcess = this;

    if (GateProcess.Proxy == undefined || GateProcess.Proxy == null) {
        GateProcess.$logFatal("GateProcess.Proxy is not bound " +
            "to OS specific implementation", this);
    }

    /* push diags and logger settings to delegate */
    for (var dl in GateProcess.common$) {
        if (dl.match(/^diags_/) || dl.match(/^logger/)) {
            GateProcess.Proxy.delegate$.common$[dl] = GateProcess.common$[dl];
        }
    }

    /* 
     * force abstractInstances$  to false for proxy because delegate's
     * fxntab is set to false in package.xs
     */
     GateProcess.Proxy.abstractInstances$ = false;
}

/*
 *  ======== module$validate ========
 */
function module$validate()
{
    if (GateProcess.Proxy.abstractInstances$ == true) {
        GateProcess.$logFatal("GateProcess.Proxy.abstractInstances$ " + 
	    "cannot be set to true", this);
    }
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, params)
{
    var proxyParams = new GateProcess.Proxy.Params();

    proxyParams.key = params.key;
    obj.proxyHandle = GateProcess.Proxy.create(proxyParams);
}

/*
 *  ======== queryMeta ========
 */
function queryMeta(qual)
{
    GateProcess = this;
    return GateProcess.Proxy.queryMeta(qual);
}

 /*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya   Review updates
 */
 /*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:51; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

