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
 *  ======== GateThread.xdc ========
 */

import xdc.runtime.IGateProvider;
import xdc.runtime.knl.IGateThreadSupport;

/*!
 *  ======== GateThread ========
 *  Provides protection of critical sections across threads. [EXPERIMENTAL]
 *
 *  This module provides services through its proxy 
 *  IGateThreadSupport interface. It has a module wide config parameter 
 *  {@link #Proxy} which needs to be bound to an OS specific delegate before 
 *  this module can be used.
 *  
 *  Here is an example showing how the proxy is bound to an BIOS 6.x specific 
 *  delegate.
 *
 *  var GateThread = xdc.useModule('xdc.runtime.knl.GateThread');
 *  GateThread.Proxy = 
 *      xdc.useModule('ti.sysbios.xdcruntime.GateThreadSupport');
 *
 *  Typically the package containing the delegates have a Settings module that 
 *  will bind all {@link xdc.runtime.knl} proxies. The following
 *  example sets up all the xdc.runtime.knl proxies.
 *  
 *  xdc.useModule("ti.sysbios.xdcruntime.Settings");
 *  
 */
 
@InstanceInitError      /* because initialization can fail */
@InstanceFinalize       /* have to Gate_Proxy_delete(sem) on delete */

module GateThread inherits IGateProvider
{
    /*! Proxy that needs to be bound to an OS specific delegate. */
    proxy Proxy inherits IGateThreadSupport;

internal:

    struct Instance_State {
        Proxy.Handle proxyHandle;
    }

}

/*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya    Review updates
 */
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:51; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

