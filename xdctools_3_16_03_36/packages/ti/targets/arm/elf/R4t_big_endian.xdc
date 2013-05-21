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
 *  ======== R4t_big_endian.xdc ========
 *  Cortex R4 big endian thumb2 target
 */
metaonly module R4t_big_endian inherits ti.targets.arm.elf.IR4_big_endian {
    override readonly config string name        = "R4t_big_endian";
    override readonly config string suffix      = "er4te";
    override readonly config string rts         = "ti.targets.arm.rtsarm";

    override readonly config xdc.bld.ITarget.Model model = {
        endian: "big",
        codeModel: "thumb2",
        shortEnums: true
    };

    override readonly config ti.targets.ITarget.Command cc = {
        cmd:  "cl470 -c",
        opts: "-mt --endian=big -mv7R4 --abi=eabi"
    };

    override readonly config ti.targets.ITarget.Command asm = {
        cmd:  "cl470 -c",
        opts: "-mt --endian=big -mv7R4 --abi=eabi"
    };

    /*!
     *  ======== linkLib ========
     *  Default TMS470 cgtools runtime library to link with executable
     *  (comes from $rootDir/lib)
     */
    config string linkLib = "rtsv7R4_T_be_eabi.lib";
}
/*
 *  @(#) ti.targets.arm.elf; 1, 0, 0,134; 2-24-2010 16:24:15; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

