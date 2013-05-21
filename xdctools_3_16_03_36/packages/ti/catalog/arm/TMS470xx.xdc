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
 *  ======== TMS470xx.xdc ========
 */
package ti.catalog.arm;

/*!
 *  ======== TMS470xx ========
 *  An interface implemented by all TMS470xx devices.
 *
 *  This interface is defined to factor common data about this family into
 *  a single place; all TMS470xx devices extend this interface.
 */
metaonly interface TMS470xx inherits ti.catalog.ICpuDataSheet
{
instance:
    override config string   cpuCore        = "470";
    override config string   isa            = "v4T";

    override config int     minProgUnitSize = 1;
    override config int     minDataUnitSize = 1;
    override config int     dataWordSize    = 4;
};
/*
 *  @(#) ti.catalog.arm; 1, 0, 1, 0,116; 2-23-2010 16:50:34; /db/ztree/library/trees/platform/platform-k32x/src/
 */

