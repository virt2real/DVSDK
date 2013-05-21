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
 *  ======== TMS320C5407.xdc ========
 *
 */
package ti.catalog.c5400;

/*!
 *  ======== TMS320C5407 ========
 *  The C5407 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is used
 *  by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C5407 inherits ITMS320C54xx
{
    config xdc.platform.IPlatform.Memory memBlock[string]  = [
        ["P_DARAM02", {
            comment: "On-Chip Program DARAM02",
            name: "P_DARAM02",
            base: 0x0080,
            len:  0x5F80,
            space: "code"
        }],
    
        ["P_DARAM04", {
            comment: "On-Chip Program DARAM04",
            name: "P_DARAM04",
            base: 0x0080,
            len:  0x9F80,
            space: "code"
        }],
    
        ["P_ROM0", {
            comment: "On-Chip Program ROM0",
            name: "P_ROM0",
            base: 0x6000,
            len:  0x9F00,
            space: "code"
        }],
    
        ["VECT", {
            comment: "On-Chip Interrupts",
            name: "VECT",
            base: 0xFF80,
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
    
        ["P_ROM2", {
            comment: "On-Chip Program ROM2",
            name: "P_ROM2",
            base: 0x28000,
            len:  0x08000,
            space: "code"
        }],
    
        ["P_ROM3", {
            comment: "On-Chip Program ROM3",
            name: "P_ROM3",
            base: 0x38000,
            len:  0x06000,
            space: "code"
        }],
    
        ["D_SPRAM", {
            comment: "Scratch-Pad RAM",
            name: "D_SPRAM",
            base: 0x60,
            len:  0x20, 
            space: "data"
        }],
    
        ["D_DARAM04", {
            comment: "On-Chip Data DARAM04",
            name: "D_DARAM04",
            base: 0x0080,
            len:  0x9F80,
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

