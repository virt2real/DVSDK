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
 *  ======== TMS470R10.xdc ========
 */
package ti.catalog.c470;

/*!
 *  ======== TMS470R10 ========
 *  The C470 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 *
 *  Warning: The data for this module comes from the linker command file 
 *  shipped with the TI 470 tools and does NOT come from any published data
 *  sheet.
 */
metaonly module TMS470R10 inherits TMS470xx
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string] =
        ti.catalog.arm.TMS470R10.memMap;
};
/*
 *  @(#) ti.catalog.c470; 1, 0, 1, 1,226; 2-23-2010 16:53:01; /db/ztree/library/trees/platform/platform-k32x/src/
 */

