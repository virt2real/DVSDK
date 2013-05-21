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
 *  ======== SyncGeneric.xs ========
 *
 *! Revision History
 *! ================
 *! 17-APr-2008 nitya   created
 */

/*
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, params)
{
    obj.userSignal = params.userSignal;   
    obj.signalArg = params.signalArg;   
    obj.userWait = params.userWait; 
    obj.waitArg = params.waitArg;
    obj.userQuery = params.userQuery;
}

 /*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya   Review updates
 */
 /*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

