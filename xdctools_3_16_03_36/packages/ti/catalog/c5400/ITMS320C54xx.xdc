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
 *  ======== ITMS320C54xx.xdc ========
 */
package ti.catalog.c5400;

/*!
 *  ======== ITMS320C54xx ========
 *  An interface implemented by all ITMS320C54xx devices.
 *
 *  This interface is defined to factor common data about this family into
 *  a single place; all ITMS320C54xx devices extend this interface.
 */
metaonly interface ITMS320C54xx inherits ti.catalog.ICpuDataSheet
{
instance:    
    override config string   cpuCore        = "5400";
    override config string   isa            = "54";
    override config int     minProgUnitSize = 2;
    override config int     minDataUnitSize = 2;    
    override config int     dataWordSize    = 2;
};
/*
 *  @(#) ti.catalog.c5400; 1, 0, 0, 0,226; 2-23-2010 16:53:05; /db/ztree/library/trees/platform/platform-k32x/src/
 */

