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
 *  ======== package.xdc ========
 *
 */

requires xdc.bld [1,0,1];

/*!
 *  ======== ti.targets.arm.elf ========
 *  Package of Arm targets for TI code generation tools for ELF
 *
 */
package ti.targets.arm.elf [1,0,0] {
    interface IArm, IR4, IR4_big_endian;
    interface IM3, IM3_big_endian;
    module Arm7, Arm7_big_endian, Arm9, Arm9t;
    module M3, M3_big_endian;
    module R4, R4_big_endian;
    module R4t, R4t_big_endian;
    module R4F, R4F_big_endian;
    module R4Ft, R4Ft_big_endian;
}
/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,134; 2-24-2010 16:24:15; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

