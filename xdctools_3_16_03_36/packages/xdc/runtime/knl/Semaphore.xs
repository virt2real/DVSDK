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
 *  ======== Semaphore.xs ========
 */

var Semaphore = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    Semaphore = this;

    if ((Semaphore.Proxy == undefined) || (Semaphore.Proxy == null)) {
        Semaphore.Proxy = xdc.module("xdc.runtime.knl.SemThread");
    }

    /* 
     * If cfg file has not set abstractInstances$ for Semaphore.Proxy
     * then set it to true by default.
     */
    if (Semaphore.Proxy.$written("abstractInstances$") == false) {
        Semaphore.Proxy.abstractInstances$ = true;
    }
}

 /*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya   Review updates
 */
 /*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

