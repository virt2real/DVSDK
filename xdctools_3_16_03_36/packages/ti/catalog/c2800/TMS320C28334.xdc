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
 *  ======== TMS320C28334.xdc ========
 *
 */
package ti.catalog.c2800;

/*!
 *  ======== TMS320C28334 ========
 *  The C28334 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is used
 *  by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C28334 inherits ITMS320C283xx
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["MSARAM", {
            comment: "On-Chip RAM Memory",
            name: "MSARAM",
            base: 0x0,
            len:  0x800,
            page: 0,
            space: "code/data"
        }],
    
        ["PIEVECT", {
            comment: "On-Chip PIEVECT RAM Memory",
            name:    "PIEVECT",
            base:    0xD00,
            len:     0x100,
            page: 1,
            space:   "data"
        }],
    
        ["L03SARAM", {
            comment: "On-Chip RAM Memory",
            name: "L03SARAM",
            base: 0x8000,
            len:  0x4000,
            page: 0,
            space: "code/data"
        }],
    
        ["L47SARAM", {
            comment: "On-Chip RAM Memory",
            name: "L47SARAM",
            base: 0xC000,
            len:  0x4000,
            page: 0,
            space: "code/data"
        }],
    
        ["OTP", {
            comment: "1K X 16 OTP memory",
            name: "OTP",
            base: 0x380400,
            len:  0x400,
            page: 0,
            space: "code"
        }],
    
        ["FLASH", {
            comment: "128K X 16 Flash memory",
            name: "FLASH",
            base: 0x320000,
            len:  0x20000,
            page: 0,
            space: "code"
        }],
    
        ["BOOTROM", {
            comment: "On-Chip Boot ROM",
            name: "BOOTROM",
            base: 0x3fe000,
            len:  0x1fc0, 
            page: 0,
            space: "code"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c2800; 1, 0, 0, 0,227; 2-23-2010 16:58:49; /db/ztree/library/trees/platform/platform-k32x/src/
 */

