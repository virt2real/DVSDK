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
 *  ======== ISemThreadSupport.xdc ========
 */

/*! 
 *  ======== ISemThreadSupport ========
 *  Interface for OS specific back-end. [EXPERIMENTAL]
 *
 *  The {@link xdc.runtime.knl} package contains modules that provide typical
 *  OS services. These xdc.runtime.knl modules require proxies to be
 *  bound to an OS specific delegate. This specifies the interface to 
 *  be implemented by the OS specific delegate for 
 *  {@link xdc.runtime.knl#SemThread} module.
 * 
 *
 *  This interface adds the create() function.
 */
interface ISemThreadSupport inherits ISemaphore
{

instance:

   /*!
    *  ======== create ========
    *  Create a Semaphore object
    *
    *  This function creates a new Semaphore object which is initialized to
    *  count.
    *
    *  @param(count)    initial semaphore count
    */
    create(Int count);
}

/*
 *! Revision History
 *! ================
 *! 17-Apr-2009 nitya    Review updates
 */
/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:51; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

