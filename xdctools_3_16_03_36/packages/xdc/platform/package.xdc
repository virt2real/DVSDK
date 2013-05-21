/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*!
 *  ======== xdc.platform ========
 *  Interfaces and modules necessary for the XDC Platform Model
 */
package xdc.platform [1,0,1,0] {
    /* platform model interfaces */
    interface IPlatform, ICpuDataSheet, IExeContext;

    /* utility modules that implement core behavior */
    module ExeContext, Utils;
}
/*
 *  @(#) xdc.platform; 1, 0, 1, 0,237; 2-22-2010 10:33:24; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

