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
 *  ======== Tesla.xdc ========
 *
 */
package ti.catalog.c6000.nda;

/*!
 *  ======== Tesla ========
 *  The C64T device data sheet module.
 */
metaonly module Tesla inherits ti.catalog.ICpuDataSheet
{

instance:
    override config int     minProgUnitSize = 1;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 4;

    override config string   cpuCore         = "Tesla";
    override config string   isa             = "64T";
    override config string   cpuCoreRevision = "1.0";

    config xdc.platform.IPlatform.Memory memMap[string]  = [
        
        ["L2SRAM", {
            comment:    "Shared 256KB SRAM",
            name:       "L2SRAM",
            base:       0x10900000,
            len:        0x00040000,
            space:      "code/data",
            access:     "RWX"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c6000.nda; 1, 0, 0, 0,105; 2-23-2010 16:58:53; /db/ztree/library/trees/platform/platform-k32x/src/
 */

