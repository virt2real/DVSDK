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
 *  ======== ti.catalog.c6000 ========
 *  Package of devices for the c6000 family of DSPs.
 *
 *  Each module in this package implements the xdc.platform.ICpuDataSheet
 *  interface.  This interface is used by platforms (modules that implement
 *  xdc.platform.IPlatform) to obtain the memory map supported by each CPU.
 */
package ti.catalog.c6000 [1,0,0,0] {
    interface ICacheInfo;
    interface ITMS320C6x0x, ITMS320C6x1x;
    interface ITMS320C64_1M, ITMS320C64_128K, ITMS320C64_256K, ITMS320C64_512K;
    interface IAntara, IDaVinci, IHimalaya;
    interface ITMS320C642x;
    interface ITMS320CTCI648x, ITMS320CTCI6484, ITMS320CTCI6486;
    interface ITMS320CTCI6497;
    interface ITMS320CDRx40x, ITMS320CDRA44x, ITMS320CDRA45x; 
    interface ITMS320DA8xx;
    interface ITMS320C6452, ITMS320CDM6467;
    module TMS320C6452, TMS320CDM647, TMS320CDM648, TMS320CTNETV2685;
    module TMS320C6428;
    module TMS320C6711;
    module TMS320C6711B;
    module TMS320C6712;
    module TMS320C6713;
    module TMS320C6211;
    module TMS320C6211B;
    module TMS320C6410;
    module TMS320C6411;
    module TMS320C6412;
    module TMS320C6413;
    module TMS320C6414;
    module TMS320C6415;
    module TMS320C6416;
    module TMS320C6418;
    module TMS320C6421, TMS320C6424;
    module TMS320CDM640;
    module TMS320CDM641;
    module TMS320CDM642;
    module TMS320CDA700;
    module TMS320CDA705;
    module TMS320CDA707;
    module TMS320CDA710;
    module TMS320CDA700SIM;
    module TMS320CDRA442, TMS320CDRA444, TMS320CDRA446, TMS320CDRA447;
    module TMS320CDRA457, TMS320CDRA459;
    module TMS320C6722, TMS320C6726, TMS320C6727;
    module TMS320CDM415;
    module TMS320CDM420;
    module TMS320CDM421;
    module TMS320CDM425;
    module TMS320CDM426;
    module TMS320CDM6431, TMS320CDM6433, TMS320CDM6435, TMS320CDM6437;
    module TMS320CDM6441, TMS320CDM6443;
    module TMS320CDM6446, TMS320DM357;
    module TMS320CDM6467;
    module TMS320CDRI300;
    module TMS320CTCI6482, TMS320CTCI6484;
    module TMS320CTCI6486;
    module TMS320TCI6485, TMS320CTCI6487, TMS320CTCI6488, TMS320TCI6489;
    module TMS320CTCI6496, TMS320CTCI6497, TMS320CTCI6498;
    module TMS320C6454, TMS320C6455;
    module TMS320C2430;
    module TMS320C3430;
    module TMS320C6701, TMS320C6201, TMS320C6202, TMS320C6203, TMS320C6203B;
    module TMS320C6204;
    module TMS320C6205;
    module TMS320CDRA406, TMS320CDRA402, TMS320CDRA404;
    module TMS320CDRA414, TMS320CDRA416;
    module TMS320CF761990;
    interface IOMAP2x3x, IOMAP3xxx;
    module OMAP2431, OMAP2530, OMAP2531, OMAP3425, OMAP3525, OMAP3530;
    module TMS320DA805, TMS320DA807, TMS320DA808, TMS320DA810;
    module TMS320DA828, TMS320DA830;
    module TMS320C6472, TMS320C6474;
    module TMS320C6747, TMS320C6745;
    module OMAPL137, OMAPL138;
    module TMS320C6457;
    module TMS320DA840, TMS320DA850;
    module TMS320C6742, TMS320C6746, TMS320C6748;
    module TMS320CDM740, TMS320CDM730;
    module TNETV107X;
}
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:40; /db/ztree/library/trees/platform/platform-k32x/src/
 */

