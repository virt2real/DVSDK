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
 *  ======== ITMS320C6x0x.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== ITMS320C6x0x ========
 *  An interface implemented by all TMS320C6x0x devices.
 *
 *  This interface is defined to factor common data about this family into
 *  a single place; all TMS320C6x0x devices extend this interface.
 */
metaonly interface ITMS320C6x0x inherits ti.catalog.ICpuDataSheet
{
    config xdc.platform.IPlatform.Memory memBlock[string]  = [
        ["IPRAM0", {
            comment: "Internal Program memory map 0",
            name: "IPRAM",
            base: 0x1400000,
            len:  0x0010000,
            space: "code"
        }],
    
        ["IPRAM1", {
            comment: "Internal Program memory map 1",
            name: "IPRAM",
            base: 0x0000000,
            len:  0x0010000,
            space: "code"
        }],
    
        ["IDRAM", {
            comment: "Internal Data memory",
            name: "IDRAM",
            base: 0x80000000,
            len:  0x00010000,
            space: "data"
        }],
    ];    


instance:
    override config string   cpuCoreRevision = "1.0";

    override config int     minProgUnitSize = 1;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 4;
    
    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string];
}
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:38; /db/ztree/library/trees/platform/platform-k32x/src/
 */

