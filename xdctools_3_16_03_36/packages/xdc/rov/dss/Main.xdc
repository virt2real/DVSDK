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
/*!
 *  @_nodoc
 *  Memory core dump tool
 *
 *  This command line tool is used to view objects of RTSC Modules
 *  contained in a core dump file. This tool uses `{@link MemoryImage}`
 *  and `{@link SymbolTable}` to peruse a static memory image
 *  associated with an application executable and outputs XML data. 
 *
 *  The core dump file format is specified in `{@link xdc.rov.IMemoryImage}`.
 *  If an output file is not specified, output is sent to stdout. 
 *
 *  The -m option limits display output to selected modules in 
 *  the program. The module specified is either a single module or a
 *  wildcard string.
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        ' ',
        'Usage',
        '[-v] [-m module] [-o out file] [-d dump file] executable', 
        '[--help]',
        ' ',
    ];

instance:

    //!Print informative messages during execution.
    @CommandOption('v')
    config Bool verboseFlag = false;

    //!Print view for module specified. 
    @CommandOption('m')
    config String mods = null;
    
    //!Write xml output to specified file
    @CommandOption('o')
    config String output = "";

    //!Use the specified dump file
    @CommandOption('d')
    config String dumpFile = "";
    
}
