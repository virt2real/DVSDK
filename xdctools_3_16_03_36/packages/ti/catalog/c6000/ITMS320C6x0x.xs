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
 *  ======== ITMS320C6x0x.getMemoryMap ========
 *  Returns the memory map as seen by a program running on this device
 *  when the registers are set as specified by the regs hash.
 */
function getMemoryMap(regs)
{

    var mapMode = 1;
    
    if (regs != null) {
        if (regs.mapMode != undefined) {
            mapMode = regs.mapMode;
        }
    }

    var memBlock = this.$module.memBlock;
    var map = this.memMap;
    
    if (mapMode == 0) {
        map = [
            ["IPRAM", memBlock["IPRAM0"]],
            ["IDRAM", memBlock["IDRAM"]]
        ];
    }
    else {
        map = [
            ["IPRAM", memBlock["IPRAM1"]],
            ["IDRAM", memBlock["IDRAM"]]
        ];
    }

    return (map);
}
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:38; /db/ztree/library/trees/platform/platform-k32x/src/
 */

