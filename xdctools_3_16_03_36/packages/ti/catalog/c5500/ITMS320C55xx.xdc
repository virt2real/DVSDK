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
 *  ======== ITMS320C55xx.xdc ========
 */
package ti.catalog.c5500;

/*!
 *  ======== ITMS320C55xx ========
 *  An interface implemented by all TMS320C55xx devices.
 *
 *  This interface is defined to factor common data about this family into
 *  a single place; all TMS320C55xx devices extend this interface.
 */
metaonly interface ITMS320C55xx inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string   cpuCore        = "5500";
    override config string   isa            = "55";
    override config int     minProgUnitSize = 2;
    override config int     minDataUnitSize = 1;    
    override config int     dataWordSize    = 2;
};
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

