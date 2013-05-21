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
 *  ======== Sync.xdc ========
 */
import xdc.runtime.Error;
import xdc.runtime.Assert;
import xdc.runtime.knl.ISync;

/*!
 *  ======== Sync ========
 *  Provides synchronization APIs when an ISync.Handle is available.
 *
 *  The application must first obtain an ISync.Handle. 
 *  It can get such a handle by directly calling {@link SyncGeneric#create} or 
 *  {@link SyncSemThread#create}. Then the application can use the generic 
 *  APIs provided by this module.
 */

module Sync
{
    /*!
     *  Proxy used for optimization.
     *
     *  If ALL ISync.Handles were created using the same module 
     *  (e.g SyncSemProcess) then setting this Proxy to SyncSemProcess and 
     *  setting Sync.Proxy.abstractInstances$ = false, 
     *  Sync APIs can have better performance.
     */
    proxy Proxy inherits ISync;

    /*!
     *  ======== query ========
     *  Query for a particular quality.
     *
     *  FALSE is returned if quality not supported.
     *
     *  @param(sync)    sync handle
     *  @param(qual)    quality
     *  @b(returns)     TRUE or FALSE.
     */
    Bool query(ISync.Handle sync, Int qual);

    /*!
     *  ======== signal ========
     *  Called at completion of an activity.
     *
     *  This function is non-blocking. It is also required that the underlying
     *  sync be binary in nature.
     *
     *  @param(sync)    sync handle
     */
    Void signal(ISync.Handle sync);

    /*!
     *  ======== wait ========
     *  Called to wait/poll for completion of an activity.
     *
     *  This function can block. Non-blocking implementations should return
     *  false;
     *
     *  @param(sync)        sync handle
     *  @param(timeout)     timeout
     *  @b(returns)         1 for success; 0 for timeout; -1 for error
     */
    Int wait(ISync.Handle sync, UInt timeout, Error.Block *eb);
}

/*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya    Review updates
 */
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

