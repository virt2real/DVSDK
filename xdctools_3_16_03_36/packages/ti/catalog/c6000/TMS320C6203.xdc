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
 *  ======== TMS320C6203.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== TMS320C6203 ========
 *  The C6203 device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly module TMS320C6203 inherits ITMS320C6x0x
{
    override config xdc.platform.IPlatform.Memory memBlock[string]  = [
        ["IPRAM0", {
            comment: "Internal Program memory map 0",
            name: "IPRAM",
            base: 0x1400000,
            len:  0x0060000,
            space: "code"
        }],
    
        ["IPRAM1", {
            comment: "Internal Program memory map 1",
            name: "IPRAM",
            base: 0x0000000,
            len:  0x0060000,
            space: "code"
        }],
    
        ["IDRAM", {
            comment: "Internal Data memory",
            name: "IDRAM",
            base: 0x80000000,
            len:  0x00080000,
            space: "data"
        }],
    ];

instance:
    override config string   cpuCore        = "6200";
    override config string   isa = "62";

};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:39; /db/ztree/library/trees/platform/platform-k32x/src/
 */

