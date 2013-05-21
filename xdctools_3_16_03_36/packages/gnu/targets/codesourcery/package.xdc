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
requires gnu.targets [1,0,1];

/*!
 *  ======== gnu.targets.codesourcery ========
 *  Codesourcery code generation targets for Arm processors
 *
 *  This package supports two Codesourcery gcc targets. One is `GCArmv5T` for 
 *  code compatible with Arm v5T architecture, and another one is `GCArmv6` for
 *  Arm v6 architecture. These targets are deprecated, and the targets from
 *  {@link gnu.targets.arm} should be used instead.
 */
package gnu.targets.codesourcery [1,0,0,0] {
    module GCArmv5T, GCArmv6;
}
/*
 *  @(#) gnu.targets.codesourcery; 1, 0, 0, 0,241; 2-24-2010 16:24:01; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

