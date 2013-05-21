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
 *  ======== package.xs ========
 *
 */

/*
 *  ======== Package.getLibs ========
 */
function getLibs(prog)
{
    var libs = "lib/";

    if (Program.build.cfgScript == null || !Program.build.cfgScript.match(/\.tcf$/)) {
        libs += "Boot.a" + Program.build.target.suffix;
    }

    return (libs);
}
/*
 *  @(#) ti.catalog.c2800.init; 1, 0, 0,77; 2-23-2010 16:50:25; /db/ztree/library/trees/platform/platform-k32x/src/
 */

