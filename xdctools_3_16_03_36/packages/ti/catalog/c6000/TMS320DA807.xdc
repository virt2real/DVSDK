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
 *  ======== TMS320DA807.xdc ========
 *
 */
package ti.catalog.c6000;

/*!
 *  ======== TMS320DA807 ========
 */
metaonly module TMS320DA807 inherits ITMS320DA8xx
{
instance:
    override config xdc.platform.IPlatform.Memory memMap[string]  = [
        ["L2ROM", {
            comment:    "Internal 1MB L2 ROM",
            name:       "IROM",
            base:       0x11700000,
            len:        0x00100000,
            space:      "code/data",
            access:     "RX"
        }],

        ["IRAM", {
            comment:    "Internal 256KB L2 memory",
            name:       "IRAM",
            base:       0x11800000,
            len:        0x00040000,
            space:      "code/data",
            access:     "RWX"
        }],
        
        ["L1PSRAM", {
            comment:    "Internal 32KB L1 program memory",
            name:       "L1PSRAM",
            base:       0x11E00000,
            len:        0x00008000,
            space:      "code",
            access:     "RWX"
        }],

        ["L1DSRAM", {
            comment:    "Internal 32KB L1 data memory",
            name:       "L1DSRAM",
            base:       0x11F00000,
            len:        0x00008000,
            space:      "data",
            access:     "RW"
        }],
    ];
};
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:40; /db/ztree/library/trees/platform/platform-k32x/src/
 */

