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
requires xdc.runtime;

/*!
 *  ======== ti.targets.rts430 ========
 *  Runtime support package for the c430 targets.
 *
 *  This package builds a library of all modules in the xdc.runtime package.
 *  By building the xdc.runtime package here we avoid having multiple copies
 *  of the same source in different runtime support packages for different
 *  ISAs.  This also allows xdc.runtime to be a pure source package
 *  independent of any particular tool chain.
 */
package ti.targets.rts430 [1,0,0] {
}
/*
 *  @(#) ti.targets.rts430; 1, 0, 0,243; 2-24-2010 16:41:36; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
 */

