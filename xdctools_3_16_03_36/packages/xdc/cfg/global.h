/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*
 *  ======== global.h ========
 *  This header is used by C/C++ sources that want to "portably" include a
 *  configuration-specific generated header (which contains extern
 *  declarations of configuration specified global variables).
 *
 *  To use this header you must define the symbol xdc_cfg__header__ to be
 *  the package-qualified name of the configuration header.
 *
 *  For example, to compile sources that reference config values
 *  for a TI C6x target with a generated
 *  configuration header named "package/cfg/mycfg_x62.h" in a package
 *  named "local.examples" the following command line is sufficient:
 *
 *      cl6x -Dxdc_cfg__header__=local/examples/package/cfg/mycfg_x62.h ...
 */

#ifdef xdc_cfg__header__
#define xdc_cfg__xheader__ <xdc_cfg__header__>
#endif
#ifdef xdc_cfg__xheader__
#include xdc_cfg__xheader__
#endif
/*
 *  @(#) xdc.cfg; 1, 0, 2, 0,237; 2-22-2010 10:33:11; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

