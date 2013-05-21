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
 *  ======== TMS320C2320.xdc ========
 *
 */
package ti.catalog.c5500;

/*!
 *  ======== TMS320C2320 ========
 *  The C2320 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C2320 inherits IOMAP
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    override config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["DARAM", {
            comment: "12 blocks of 8K bytes",
            name: "DARAM",
            base: 0x000000,
            len:  0x018000,
            space: "code/data",
            access: "RWX"
        }],
    
        ["SARAM", {
            comment: "20 blocks of 8K bytes",
            name: "SARAM",
            base: 0x018000,
            len:  0x028000,
            space: "code/data",
            access: "RWX"
        }],

        ["PDROM", {
            comment: "320K bytes On-Chip ROM",
            name: "PDROM",
            base: 0xfb0000,
            len:  0x050000,
            space: "code/data",
            access: "RX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

