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
 *  ======== TNETV1050.xdc ========
 *  The chip configuration settings are based on document SPRS238C.
 *
 */
package ti.catalog.c5500;

/*!
 *  ======== TNETV1050 ========
 *  The TNETV1050 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TNETV1050 inherits ITMS320C55xx
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["DARAM01", {
            comment: "2 blocks of 16K bytes on-chip Dual-Access RAM",
            name: "DARAM01",
            base: 0x000000,
            len:  0x008000,
            space: "code/data",
            access: "RWX"
        }],

        ["DARAM23", {
            comment: "2 blocks of 16K bytes on-chip Dual-Access RAM",
            name: "DARAM23",
            base: 0x008000,
            len:  0x008000,
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
    
        ["VECT", {
            comment: "On-Chip Interrupt Vector Table",
            name: "VECT",
            base: 0xfff800,
            len:  0x000100,
            space: "code",
            access: "RWX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:07; /db/ztree/library/trees/platform/platform-k32x/src/
 */

