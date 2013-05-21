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
 *  ======== TMS570PSF762.getMemoryMap ========
 *  Returns the memory map as seen by a program running on this device
 *  when the registers are set as specified by the regs hash.
 */
function getMemoryMap(regs)
{
    if ("flash_lo" in regs) {
        var flash_lo = regs.flash_lo;
    }
    else {
        var flash_lo = true;
    }
    if (flash_lo == true) {
        delete this.memMap["LO_IRAM"];
        delete this.memMap["HI_FLASH"];
    }
    else {
        delete this.memMap["HI_IRAM"];
        delete this.memMap["LO_FLASH"];
    }
    return (this.memMap);
}

/*
 *  @(#) ti.catalog.arm; 1, 0, 1, 0,116; 2-23-2010 16:50:34; /db/ztree/library/trees/platform/platform-k32x/src/
 */

