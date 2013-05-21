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
 *  ======== TMS320C5401.xdc ========
 */
package ti.catalog.c5400;

/*!
 *  ======== TMS320C5401 ========
 *  The C5401 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is used
 *  by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C5401 inherits ITMS320C54xx
{
    config xdc.platform.IPlatform.Memory memBlock[string]  = [
        ["P_DARAM", {
            comment: "On-Chip Program DARAM",
            name: "P_DARAM",
            base: 0x1000,
            len:  0x2000,
            space: "code"
        }],
    
        ["P_ROM", {
            comment: "On-Chip Program ROM",
            name: "P_ROM",
            base: 0xf000,
            len:  0x0f00,
            space: "code"
        }],
    
        ["VECT", {
            comment: "On-Chip Interrupts",
            name: "VECT",
            base: 0xff80,
            len:  0x0080,
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
            base: 0x1000,
            len:  0x2000,
            space: "data"
        }],
    
        ["D_ROM", {
            comment: "On-Chip Data ROM",
            name: "D_ROM", 
            base: 0xf000,
            len:  0x0f00, 
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

