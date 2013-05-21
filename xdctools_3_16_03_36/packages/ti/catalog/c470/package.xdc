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

requires xdc.platform;
requires ti.catalog.arm;

/*!
 *  ======== ti.catalog.c470 ========
 *  Package of devices for the c470 family of Arm processors.
 *
 *  Each module in this package implements the xdc.platform.ICpuDataSheet
 *  interface. This interface is used by platforms (modules that implement
 *  xdc.platform.IPlatform) to obtain the memory map supported by each CPU.
 */
package ti.catalog.c470 [1,0,1,1] {
    interface TMS470xx;
    module TMS470R10;
    module TMS320C5912;
    module TMS320C1030;
    module TMS320CDM6446, TMS320CDM6467;
    module TMS320CDM355, TMS320DM357, TMS320DM365;
    module TMS320CDM510;
    module OMAP2430, OMAP2431, OMAP2530, OMAP2531;
    module OMAP3403, OMAP3405, OMAP3503, OMAP3505, OMAP3515, OMAP3517;
    module OMAP3425, OMAP3525, TMS320C3430, OMAP3530;
    module TMS320DA828, TMS320DA830;
    module OMAPL137;
    module CortexM3;
    module TMS570PSF762;
}
/*
 *  @(#) ti.catalog.c470; 1, 0, 1, 1,226; 2-23-2010 16:53:01; /db/ztree/library/trees/platform/platform-k32x/src/
 */

