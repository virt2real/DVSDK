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
 *  ======== TMS320CRYUJIN.xdc ========
 *
 */
package ti.catalog.c5500;

/*!
 *  ======== TMS320CRYUJIN ========
 *  The CRYUJIN device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320CRYUJIN inherits IOMAP
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    override config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["BANKED_SARAM", {
            comment: "64K bytes in 16 banks of SARAM",
            name: "BANKED_SARAM",
            base: 0x000000,
            len:  0x010000,
            space: "code/data",
            access: "RWX"
        }],
    
        ["SARAM", {
            comment: "192K bytes On-Chip Single-Access RAM",
            name: "SARAM",
            base: 0x010000,
            len:  0x030000,
            space: "code/data",
            access: "RWX"
        }],

        ["PDROM", {
            comment: "128K bytes On-Chip ROM",
            name: "PDROM",
            base: 0xfe0000,
            len:  0x020000,
            space: "code/data",
            access: "RX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:07; /db/ztree/library/trees/platform/platform-k32x/src/
 */

