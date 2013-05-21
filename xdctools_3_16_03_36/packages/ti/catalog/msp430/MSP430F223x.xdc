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

/*!
 *  ======== MSP430F223x.xdc ========
 *  MSP430F223x Cpu definition
 *
 *  This device has 8KB + 256B of Flash Memory and 512B RAM.  The
 *  MSP430F2234 has two op-amps (OA) whereas the MSP430F2232 has none.
 */

metaonly module MSP430F223x inherits IMSP430x22xx
{
instance:
    /*!
     *  ======== deviceMap ========
     *  Device specific memory blocks
     *
     *  This memory together with the common family memory forms the 
     *  complete memory map retuned by `getMemoryMap()`.
     */
    config xdc.platform.IPlatform.Memory deviceMap[string]  = [
        ["RAM", {
            comment:    "Data RAM",
            name:       "RAM",
            base:       0x200,
            len:        0x200,
            space:      "code/data",
            access:     "RWX"
        }],

        ["FLASH", {
            comment:    "Program FLASH",
            name:       "FLASH",
            base:       0xE000,
            len:        0x1FDE,
            space:      "code",
            access:     "RWX"
        }],
    ];
}
/*
 *  @(#) ti.catalog.msp430; 1, 0, 0,17; 2-23-2010 16:52:59; /db/ztree/library/trees/platform/platform-k32x/src/
 */

