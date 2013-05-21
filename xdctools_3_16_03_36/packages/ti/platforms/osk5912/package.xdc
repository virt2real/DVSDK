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

requires ti.catalog.c5500;

/*!
 *  ======== ti.platforms.osk5912 ========
 *  Platform package for the osk5912 platform.
 *
 *  This package implements the interfaces (xdc.platform.IPlatform) necessary
 *  to build and run executables on the osk5912 platform.
 *
 *  @a(Throws)
 *  `XDCException` exceptions are thrown for fatal errors. The following error
 *  codes are reported in the exception message:
 *  @p(dlist)                            
 *      -  `ti.platfoms.osk5912.LINK_TEMPLATE_ERROR`
 *           This error is raised when this platform cannot found the default
 *           linker command template `linkcmd.xdt` in the build target's
 *           package. When a target does not contain this file, the config
 *           parameter `{@link xdc.cfg.Program#linkTemplate}` must be set.
 *  @p
 */
package ti.platforms.osk5912 [1,0,1,0] {
    module Platform;
}
/*
 *  @(#) ti.platforms.osk5912; 1, 0, 1, 0,276; 2-23-2010 16:53:32; /db/ztree/library/trees/platform/platform-k32x/src/
 */

