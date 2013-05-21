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

/*
 *  ======== MSP430F5418.xdc ========
 *
 */
package ti.catalog.msp430;

/*!
 *  ======== MSP430F5418 ========
 *  MSP430F5418 CPU definition
 */
metaonly module MSP430F5418 inherits IMSP430F54xx
{
instance:
    override config string   cpuCoreRevision = "1.0";

    /*!
     *  ======== memMap ========
     *  The default memory map for this device
     */
    config xdc.platform.IPlatform.Memory memMap[string]  = [

        ["RAM", {
            comment:    "Data RAM",
            name:       "RAM",
            base:       0x1C00,
            len:        0x4000,
            space:      "code/data",
            access:     "RWX"
        }],

        ["FLASH", {
            comment:    "Program FLASH",
            name:       "FLASH",
            base:       0x5C00,
            len:        0xA380,
            space:      "code",
            access:     "RWX"
        }],

        ["FLASH2", {
            comment:    "Extended Program FLASH",
            name:       "FLASH2",
            base:       0x10000,
            len:        0x15C00,
            space:      "code",
            access:     "RWX"
        }],

    ];
};
/*
 *  @(#) ti.catalog.msp430; 1, 0, 0,17; 2-23-2010 16:52:59; /db/ztree/library/trees/platform/platform-k32x/src/
 */

