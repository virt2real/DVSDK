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

/*
 *  ======== TMS320C6701.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== TMS320C6701 ========
 *  The C6701 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C6701 inherits ITMS320C6x0x
{
instance:
    override config string   cpuCore        = "6700";
    override config string   isa = "67";
};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:39; /db/ztree/library/trees/platform/platform-k32x/src/
 */

