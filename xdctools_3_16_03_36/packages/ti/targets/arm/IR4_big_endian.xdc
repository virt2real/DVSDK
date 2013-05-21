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
import ti.targets.ITarget;

/*!
 *  ======== IR4_big_endian.xdc ========
 *  Cortex R4 big endian target
 */
metaonly interface IR4_big_endian inherits ti.targets.arm.IArm {
    override readonly config string isa         = "v7R";

    override readonly config xdc.bld.ITarget.Module base = ti.targets.arm.Arm9;

    override config string platform   = "ti.platforms.evmTMS570";

    override readonly config ti.targets.ITarget.Command lnk = {
        cmd:  "lnk470",
        opts: "--be32 --silicon_version=7R4 --strict_compatibility=on"
    };
}
/*
 *  @(#) ti.targets.arm; 2, 0, 1, 0,202; 2-24-2010 16:24:12; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

