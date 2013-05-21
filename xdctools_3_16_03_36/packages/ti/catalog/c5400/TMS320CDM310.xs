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
 *  ======== TMS320CDM310.xs ========
 *
 */

/*
 *  ======== TMS320CDM270.getMemoryMap ========
 *  Returns the memory map as seen by a program running on this device
 *  when the registers are set as specified by the regs hash.
 */
function getMemoryMap(regs)
{
    if (regs == null) {
        regs = {};
    }
    if (!("pmst" in regs)) {
        regs.pmst = 0xffe0;
    }

    var memBlock = this.$module.memBlock;
    var map = this.memMap;
    
    /* care about OVLY bit only. */
    var pmst = (regs.pmst - 0) & 0x20;
    
    switch (pmst) {
        case 0x0:   /* OVLY = 0 */
            map = [
                ["P_ROM", memBlock["P_ROM"]],
                ["VECT", memBlock["VECT"]],
                ["P_SARAM", memBlock["P_SARAM"]],
                ["D_SPRAM", memBlock["D_SPRAM"]],
                ["IMAGE_BUFFER_AC", memBlock["IMAGE_BUFFER_AC"]],
                ["IMAGE_BUFFER_B", memBlock["IMAGE_BUFFER_B"]],
                ["D_ROM", memBlock["D_ROM"]]
            ];
            break;

        case 0x20:  /* OVLY = 1 */
            map = [
                ["P_DARAM", memBlock["P_DARAM"]],
                ["P_ROM", memBlock["P_ROM"]],
                ["VECT", memBlock["VECT"]],
                ["P_SARAM", memBlock["P_SARAM"]],
                ["D_SPRAM", memBlock["D_SPRAM"]],
                ["IMAGE_BUFFER_AC", memBlock["IMAGE_BUFFER_AC"]],
                ["IMAGE_BUFFER_B", memBlock["IMAGE_BUFFER_B"]],
                ["D_ROM", memBlock["D_ROM"]]
            ];
            break;

        default: {
            map = [];
            break;
        }
    }

    return (map);
}
/*
 *  @(#) ti.catalog.c5400; 1, 0, 0, 0,226; 2-23-2010 16:53:06; /db/ztree/library/trees/platform/platform-k32x/src/
 */

