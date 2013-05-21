/* 
 *Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

package xdc.tools.closure;

/*!
 *  ======== xdc.tools.closure.Main ========
 *  Utility that creates a closed bundle
 *
 *  The purpose of this tool is to build a bundle containing all packages
 *  loaded in the process of configuring an application. The bundle is 
 *  built in a user-selected repository, which can be then relocated to
 *  a different location or to a different host, where the application
 *  being configured can be recompiled and relinked.
 *
 *  The closure tool can run only after {@link xdc.tools.configuro} runs
 *  and finishes the configuration step. Then, `xdc.tools.closure' detects
 *  all packages involved in the configuration and copies them to a new
 *  repository. All absolute paths in the relevant generated files that 
 *  could be accessed by the user's makefile, when the application is
 *  rebuilt, are transformed into the paths relative to the the directory
 *  containing the closed bundle. 
 *
 *  Some files in the copied packages are deleted to keep the size of
 *  the closed bundle manageable. The default settings delete only selected
 *  files, but a user has an option of requesting aggressive filtering of
 *  files, which leaves in the closed bundle only header files and
 *  libraries referenced by linker command files.
 *
 *  @a(Examples)
 *  xs xdc.tools.configuro -t gnu.targets.arm.GCArmv6 -o configPkg --cb
 *                         memory.cfg
 *  xs xdc.tools.closure -d D:/bundle C:/examples/memory/configPkg
 *  @p(dlist)
 *  After `xdc.tools.configuro` creates a configuration in `configPkg`,
 *  `xdc.tools.closure` gathers all packages loaded during the 
 *  configuration in a repository located in D:/bundle
 *  @p
 *
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        '[-v] [-f] [-i pkg1 [-i pkg2 ...]] [-d dst_dir] package_base_dir'
    ];

instance:

    //!Print informative messages during execution
    @CommandOption('v')
    config Bool verboseFlag = false;

    //!Perform aggressive filtering
    @CommandOption('f')
    config Bool aggFilter = false;

    //!Name of the destination directory
    @CommandOption('d')
    config String destination = "";
    
    //!Additional packages to be included in the bundle
    @CommandOption('i')
    config String includes[] = [];
}


/*
 *  @(#) xdc.tools.closure; 1, 0, 0, 0,51; 11-20-2009 13:26:03; /db/ztree/library/trees/xdctools/xdctools-d08x/src/
 */

