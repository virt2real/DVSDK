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
requires ti.catalog;

/*!
 *  ======== ti.catalog.c5400 ========
 *  Package of devices for the c5400 family of DSPs.
 *
 *  Each module in this package implements the xdc.platform.ICpuDataSheet
 *  interface. This interface is used by platforms (modules that implement
 *  xdc.platform.IPlatform) to obtain the memory map supported by each CPU.
 */
package ti.catalog.c5400 [1,0,0,0] {
    interface ITMS320C54xx;
    module TMS320C5401;
    module TMS320C5402;
    module TMS320C5402A;
    module TMS320C5404;
    module TMS320C5405;
    module TMS320C5407;
    module TMS320C5409;
    module TMS320C5409A;
    module TMS320C5410;
    module TMS320C5410A;
    module TMS320C5416;
    module TMS320C5420;
    module TMS320C5470;
    module TMS320C5471;
    module TMS320CDM270;
    module TMS320CDM310;
    module TMS320CDM320;
    module TMS320C54CST;
}
/*
 *  @(#) ti.catalog.c5400; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

