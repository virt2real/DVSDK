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
package xdc.runtime;

/*! 
 *  ======== GateNull ========
 *  Empty implementation of `{@link IGateProvider}`
 *
 *  An instance of this `IGateProvider` implementation is assigned to all
 *  gated modules as a default module-wide gate. Instances of this gate
 *  implementation provide no protection for critical sections and should only
 *  be used for modules in which the data structures protected by module-level
 *  gates are never accessed by concurrent threads.
 */
module GateNull inherits IGateProvider {

instance:
    /*!
     *  ======== create ========
     *  Create a `GateNull` gate
     */
    create();
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

