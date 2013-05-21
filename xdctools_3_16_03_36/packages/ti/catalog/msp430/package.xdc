/* 
 *  Copyright (c) 2008 Texas Instruments and others.
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
 *  ======== ti.catalog.msp430 ========
 *  Package of devices for the msp430 family.
 *
 *  Each module in this package implements the xdc.platform.ICpuDataSheet
 *  interface. This interface is used by platforms (modules that implement
 *  xdc.platform.IPlatform) to obtain the memory map supported by each CPU.
 */
package ti.catalog.msp430 [1,0,0] {
    interface IMSP430;
    interface IMSP430x22xx;
    interface IMSP430F54xx;
    module MSP430F5418, MSP430F5419;
    module MSP430F5435, MSP430F5436;
    module MSP430F5437, MSP430F5438;
    module MSP430F223x, MSP430F225x, MSP430F227x;
}
/*
 *  @(#) ti.catalog.msp430; 1, 0, 0,17; 2-23-2010 16:52:59; /db/ztree/library/trees/platform/platform-k32x/src/
 */

