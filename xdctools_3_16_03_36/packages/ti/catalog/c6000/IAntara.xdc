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
 *  ======== IAntara.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== IAntara ========
 *  The Antara device data sheet module.
 *
 *  This module implements the xdc.platform.ICpuDataSheet interface and is 
 *  used by platforms to obtain "data sheet" information about this device.
 */
metaonly interface IAntara inherits ti.catalog.ICpuDataSheet
{
instance:
    override config int     minProgUnitSize = 1;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 4;

    override config string   cpuCore        = "67x+";
    override config string   isa = "67P";
    override config string   cpuCoreRevision = "1.0";

    config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["IRAM", {
            name:       "IRAM",
            comment:    "Internal memory",
            base:       0x10000000,
            len:        0x00040000,
            space:      "code/data",
            access:     "RWX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:37; /db/ztree/library/trees/platform/platform-k32x/src/
 */

