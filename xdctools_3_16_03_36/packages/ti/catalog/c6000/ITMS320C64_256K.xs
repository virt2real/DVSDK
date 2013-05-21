/*
 *  Copyright (c) 2010 by Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

var c6x = xdc.loadCapsule("c6x.xs");

/*
 *  ======== ITMS320C64_256K.getMemoryMap ========
 *  Returns the memory map as seen by a program running on this device
 *  when the registers are set as specified by the regs hash.
 */
function getMemoryMap(regs)
{
    return (c6x.init6x1xMap(this, this.memMap["IRAM"].len, regs));
}

/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:38; /db/ztree/library/trees/platform/platform-k32x/src/
 */

