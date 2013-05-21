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

metaonly module TMS320C5912 inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string cpuCore           = "Arm9";
    override config string isa               = "v5T";
    override config string cpuCoreRevision   = "1.0";
    override config int    minProgUnitSize   = 1;
    override config int    minDataUnitSize   = 1;
    override config int    dataWordSize      = 4;

    /*!
     *  ======== memMap ========
     *  The memory map returned be getMemoryMap().
     */
    config xdc.platform.IPlatform.Memory memMap[string] = [];
}
/*
 *  @(#) ti.catalog.arm; 1, 0, 1, 0,116; 2-23-2010 16:50:33; /db/ztree/library/trees/platform/platform-k32x/src/
 */

