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

/*!
 *  ======== ti.catalog.c2800 ========
 *  Package of devices for the c2800 family of DSPs.
 *
 *  Each module in this package implements the xdc.platform.ICpuDataSheet
 *  interface. This interface is used by platforms (modules that implement
 *  xdc.platform.IPlatform) to obtain the memory map supported by each CPU.
 */
package ti.catalog.c2800 [1,0,0,0] {
    interface ITMS320C28xx,ITMS320C283xx;

    module TMS320C2801, TMS320C2802, TMS320C2806, TMS320C2808, TMS320C2809; 
    module TMS320C2810, TMS320C2811, TMS320C2812, TMS320C28015, TMS320C28016;
    module TMS320C28232, TMS320C28234, TMS320C28235;
    module TMS320C28332, TMS320C28334, TMS320C28335;

    /* Piccolo Devices */
    module TMS320C28020, TMS320C28021;
    interface ITMS320C28026;
    module TMS320C28022, TMS320C28026;
    interface ITMS320C28027;
    module TMS320C28023, TMS320C28027;

    /* Piccolo-B Devices */
    module TMS320C28030, TMS320C28031;
    interface ITMS320C28032;
    module TMS320C28032, TMS320C28033;
    interface ITMS320C28034;
    module TMS320C28034, TMS320C28035;

    module TMS320C28044;

    /* Delfino Devices */
    interface ITMS320C28342;
    module TMS320C28341, TMS320C28342;
    interface ITMS320C28344;
    module TMS320C28343, TMS320C28344;
    interface ITMS320C28346;
    module TMS320C28345, TMS320C28346;
}
/*
 *  @(#) ti.catalog.c2800; 1, 0, 0, 0,227; 2-23-2010 16:58:49; /db/ztree/library/trees/platform/platform-k32x/src/
 */

