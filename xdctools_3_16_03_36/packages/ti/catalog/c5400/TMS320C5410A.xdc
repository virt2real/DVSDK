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
 *  ======== TMS320C5410A.xdc ========
 *
 */
package ti.catalog.c5400;

/*!
 *  ======== TMS320C5410A ========
 *  The C5410A device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is used
 *  by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C5410A inherits ITMS320C54xx
{
    config xdc.platform.IPlatform.Memory memBlock[string]  = [
        ["P_DARAM03", {
            comment: "On-Chip Program DARAM 0-3",
            name: "P_DARAM03",
            base: 0x0080, 
            len:  0x7F80,
            space: "code"
        }],
    
        ["P_ROM", {
            comment: "On-Chip ROM",
            name: "P_ROM",
            base: 0xC000,
            len:  0x3F00,
            space: "code"
        }],
    
        ["VECT", {
            comment: "On-Chip Interrupts",
            name: "VECT",
            base: 0xff80,
            len:  0x80,
            space: "code"
        }],
    
        ["P_DARAM47", {
            comment: "On-Chip Program DARAM 4-7",
            name: "P_DARAM47",
            base: 0x18000,
            len:  0x08000,
            space: "code"
        }],
    
        ["D_SPRAM", {
            comment: "On-Chip Scratch-Pad RAM",
            name: "D_SPRAM",
            base: 0x60,
            len:  0x20, 
            space: "data"
        }],
    
        ["D_DARAM03", {
            comment: "On-Chip Data DARAM 0-3",
            name: "D_DARAM03",
            base: 0x0080,
            len:  0x7f80,
            space: "data"
        }],
    
        ["D_DARAM47", {
            comment: "On-Chip Data DARAM 4-7",
            name: "D_DARAM47",
            base: 0x8000,
            len:  0x8000,
            space: "data"
        }],

    ];

instance:
    override config string cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string];
}
/*
 *  @(#) ti.catalog.c5400; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

