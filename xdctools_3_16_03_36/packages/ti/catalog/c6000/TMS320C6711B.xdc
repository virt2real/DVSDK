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
 *  ======== TMS320C67111B.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== TMS320C6711B ========
 *  The C6711B device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C6711B inherits ITMS320C6x1x
{

instance:
    override config string   cpuCore        = "6700";
    override config string   isa = "67";
    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
 
    override config xdc.platform.IPlatform.Memory memMap[string] =
        TMS320C6211.memMap;
};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:39; /db/ztree/library/trees/platform/platform-k32x/src/
 */

