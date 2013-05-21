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
 *  ======== TMS320C5510.xdc ========
 */
package ti.catalog.c5500;

/*!
 *  ======== TMS320C5510 ========
 *  The C5510 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C5510 inherits ITMS320C55xx
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["DARAM", {
            comment: "8 blocks of 8K bytes of on-chip Dual-Access RAM",
            name: "DARAM",
            base: 0x0000c0,
            len:  0x00ff40,
            space: "code/data",
            access: "RWX"
        }],
    
        ["SARAM", {
            comment: "32 blocks of 8K bytes of on-chip Single-Access RAM",
            name: "SARAM",
            base: 0x10000,
            len:  0x40000,
            space: "code/data",
            access: "RWX"
        }],

        ["ROM", {
            comment: "32K bytes of on-chip ROM",
            name: "ROM",
            base: 0xff8000,
            len:  0x008000,
            space: "code/data",
            access: "RX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

