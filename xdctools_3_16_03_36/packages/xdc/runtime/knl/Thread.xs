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
 *  ======== Thread.xs ========
 */

var Thread = null;
var IThreadSupport = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    Thread = this;

    IThreadSupport = xdc.module("xdc.runtime.knl.IThreadSupport");

    if (Thread.Proxy == undefined || Thread.Proxy == null) {
        Thread.$logFatal("Thread.Proxy is not bound to " +
	    "OS specific implementation", this);
    }

    /* push diags and logger to delegate */
    for (var dl in Thread.common$) {
        if (dl.match(/^diags_/) || dl.match(/^logger/)) {
            Thread.Proxy.delegate$.common$[dl] = Thread.common$[dl];
        }
    }

    /* 
     * force abstractInstances$  to false for proxy because delegate's
     * fxntab is set to false in package.xs
     */
    Thread.Proxy.abstractInstances$ = false;
}

/*
 *  ======== module$validate ========
 */
function module$validate()
{
    if (Thread.Proxy.abstractInstances$ == true) {
        Thread.$logFatal("Thread.Proxy.abstractInstances$ " +
	    "cannot be set to true", this);
    }
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, fxn, params)
{
    var new_params = new Thread.Proxy.Params;
    new_params.arg = params.arg;

    if (params.priority == Thread.Priority_LOWEST) {
        new_params.priority = IThreadSupport.Priority_LOWEST;
    }
    else if (params.priority == Thread.Priority_BELOW_NORMAL) {
        new_params.priority = IThreadSupport.Priority_BELOW_NORMAL;
    }
    else if (params.priority == Thread.Priority_NORMAL) {
        new_params.priority = IThreadSupport.Priority_NORMAL;
    }
    else if (params.priority == Thread.Priority_ABOVE_NORMAL) {
        new_params.priority = IThreadSupport.Priority_ABOVE_NORMAL;
    }
    else if (params.priority == Thread.Priority_HIGHEST) {
        new_params.priority = IThreadSupport.Priority_HIGHEST;
    }
    else {
        new_params.priority = IThreadSupport.Priority_INVALID;
    }

    new_params.osPriority = params.osPriority;
    if (params.stackSize != 0) {
        new_params.stackSize = params.stackSize;
    }
    else if (Thread.defaultStackSize !=0) {
        new_params.stackSize = Thread.defaultStackSize;
    }
    new_params.tls = obj;
    obj.tls = params.tls;
    obj.proxyHandle = Thread.Proxy.create(fxn, new_params);
}


 /*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya   Review updates
 */
 /*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

