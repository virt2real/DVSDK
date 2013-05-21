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
 *  ======== Arm9.xdc ========
 *  TI Arm9 little endian target
 */
metaonly module Arm9 inherits ti.targets.arm.elf.IArm {
    override readonly config string name        = "Arm9"; 
    override readonly config string suffix      = "e9";
    override readonly config string isa         = "v5T";    
    override readonly config string rts         = "ti.targets.arm.rtsarm";

    override readonly config xdc.bld.ITarget.Module base = ti.targets.TMS470;

    override readonly config xdc.bld.ITarget.Model model = {
        endian: "little",
        shortEnums: true
    };

    /*
     *  ======== compatibleSuffixes ========
     */
    override config String compatibleSuffixes[] = ["7", "470", "9t"];

    override readonly config ti.targets.ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: "-me -mv5e --abi=eabi"
    };

    override readonly config ti.targets.ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: "-me -mv5e --abi=eabi"
    };

    override readonly config ti.targets.ITarget.Command lnk = {
        cmd:  "lnk470",
        opts: "--silicon_version=5e --strict_compatibility=on"
    };

    /*!
     *  ======== linkLib ========
     *  Default TMS470 cgtools runtime library to link with executable
     *  (comes from $rootDir/lib)
     */
    config string linkLib = "rtsv5_A_le_eabi.lib";    
}
/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,134; 2-24-2010 16:24:14; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

