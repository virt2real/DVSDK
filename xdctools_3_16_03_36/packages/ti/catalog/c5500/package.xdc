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
 *  ======== ti.catalog.c5500 ========
 *  Package of devices for the c5500 family of DSPs.
 *
 *  Each module in this package implements the xdc.platform.ICpuDataSheet
 *  interface. This interface is used by platforms (modules that implement
 *  xdc.platform.IPlatform) to obtain the memory map supported by each CPU.
 */
package ti.catalog.c5500 [1,0,0,0] {
    interface IOMAP, ITMS320C55xx;
    module TMS320C5501;
    module TMS320C5502;
    module TMS320C5503;
    module TMS320C5504;
    module TMS320C5505;
    module TMS320C5507;
    module TMS320C5509;
    module TMS320C5509A;
    module TMS320C5510;
    module TMS320C5510A;
    module TMS320C5514;
    module TMS320C5515;
    module TMS320C5561;
    module TMS320C1035;
    module TMS320C1510;
    module TMS320C1610;
    module TMS320C1710;
    module TMS320C2320;
    module TMS320C2420;
    module TMS320C5903;
    module TMS320C5905;
    module TMS320C5910;
    module TMS320C5912;
    module TMS320C5944;
    module TMS320C5946;
    module TMS320C5948;
    module TMS320CRYUJIN;
    module TMS320CDA255;
    module TMS320CDA295;
    module TMS320CDA300;
    module TNETV1050, TNETV1055;
}
/*
 *  @(#) ti.catalog.c5500; 1, 0, 0, 0,226; 2-23-2010 16:53:07; /db/ztree/library/trees/platform/platform-k32x/src/
 */

