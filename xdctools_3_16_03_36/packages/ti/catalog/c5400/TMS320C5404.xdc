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
 *  ======== TMS320C5404.xdc ========
 */
package ti.catalog.c5400;

/*!
 *  ======== TMS320C5404 ========
 *  The C5404 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is used
 *  by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C5404 inherits ITMS320C54xx
{
    config xdc.platform.IPlatform.Memory memBlock[string]  = [
        ["P_DARAM", {
            comment: "On-Chip Program DARAM",
            name: "P_DARAM",
            base: 0x0080,
            len:  0x3F80,
            space: "code"
        }],
    
        ["P_ROM0", {
            comment: "On-Chip Program ROM0",
            name: "P_ROM0",
            base: 0x8000,
            len:  0x7F00,
            space: "code"
        }],
    
        ["VECT", {
            comment: "On-Chip Interrupts",
            name: "VECT",
            base: 0xff80,
            len:  0x0080,
            space: "code"
        }],
    
        ["P_ROM1", {
            comment: "On-Chip Program ROM1",
            name: "P_ROM1",
            base: 0x18000,
            len:  0x08000,
            space: "code"
        }],
    
        ["D_SPRAM", {
            comment: "Scratch-Pad RAM",
            name: "D_SPRAM",
            base: 0x60,
            len:  0x20, 
            space: "data"
        }],
    
        ["D_DARAM", {
            comment: "On-Chip Data DARAM",
            name: "D_DARAM",
            base: 0x0080,
            len:  0x3F80,
            space: "data"
        }],
    
        ["D_ROM", {
            comment: "On-Chip Data ROM",
            name: "D_ROM", 
            base: 0xC000,
            len:  0x4000, 
            space: "data"
        }],
    ];

instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string];
};
/*
 *  @(#) ti.catalog.c5400; 1, 0, 0, 0,226; 2-23-2010 16:53:05; /db/ztree/library/trees/platform/platform-k32x/src/
 */

