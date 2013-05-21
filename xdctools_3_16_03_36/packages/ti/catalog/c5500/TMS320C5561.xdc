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
 *  ======== TMS320C5561.xdc ========
 *  The chip configuration settings are based on document SPRS012B.
 *
 */
package ti.catalog.c5500;

/*!
 *  ======== TMS320C5561 ========
 *  The C5561 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C5561 inherits ITMS320C55xx
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["DARAM", {
            comment: "4 blocks of 16K bytes on-chip Dual-Access RAM",
            name: "DARAM",
            base: 0x000000,
            len:  0x010000,
            space: "data",
            access: "RWX"
        }],

        ["SARAM", {
            comment: "64K bytes on-chip Single-Access RAM",
            name: "SARAM",
            base: 0x010000,
            len:  0x010000,
            space: "code/data",
            access: "RWX"
        }],
    
        ["SARAM1", {
            comment: "4 blocks of 64K bytes on-chip Single-Access RAM",
            name: "SARAM1",
            base: 0x020000,
            len:  0x040000,
            space: "data",
            access: "RWX"
        }],
    
        ["SHRAM", {
            comment: "2 block of 256K bytes shared memory",
            name: "SHRAM",
            base: 0xf80000,
            len:  0x07f000,
            space: "code/data",
            access: "RWX"
        }],
    
        ["ROM", {
            comment: "4K byte on-chip ROM",
            name: "ROM",
            base: 0xfff000,
            len:  0x001000,
            space: "code/data",
            access: "RX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

