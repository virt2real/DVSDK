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
 *  ======== SyncSemThread.xdc ========
 */

import xdc.runtime.knl.SemThread;

/*!
 *  ======== SyncSemThread ========
 *  A ISync implementation based on a SemThread. [EXPERIMENTAL]
 *
 *  This module implements the {@link ti.sdo.utils.ISync} interface
 *  using the {@link xdc.runtime.knl.SemThread} module.
 */

@InstanceInitError      /* instance initialization can fail */
@InstanceFinalize       /* instances require finalization */

module SyncSemThread inherits xdc.runtime.knl.ISync
{

internal:  /* not for client use */

    struct Instance_State {
        SemThread.Handle    semThread;
    };
}

/*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya    Review updates
 */
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

