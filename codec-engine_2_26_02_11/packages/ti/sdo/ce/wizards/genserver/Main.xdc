/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*!
 * ======== Main ========
 * Codec Engine GenServer Wizard
 *
 * The wizard generates the files needed to create a unit-test server
 * for codec packages. All arguments are optional, unless otherwise  
 * noted. Two versions of this program exist: gui (default) and 
 * command line (use -f option).
 * 
 * ------------------------------
 *     Wizard Pre-Requisites
 * ------------------------------
 * Please see Codec Engine v2.23 release notes for version dependencies 
 * needed to run the wizard and build the server.
 *
 * To only run the wizard, you need the following on your XDCPATH:
 * Codec Engine/packages,
 * Codec Engine/cetools/packages OR the repositories for xDAIS, FC, CMEM, 
 * DSPLink, and BIOSUTILS and your repository containing codec packages      
 *
 * ------------------------------
 *     Wizard Instructions
 * ------------------------------  
 * To start the graphical version, use: 
 * xs ti.sdo.ce.wizards.genserver
 *  
 * This will allow you to enter all of the information needed to create 
 * a package. If you prefer to use the command line option, follow the 
 * directions below.
 * 
 * To run the command line wizard:
 *      xs ti.sdo.ce.wizards.genserver -f=xmlFileName
 *
 * The XML file must have been previously saved with the graphical version.
 *     
 * The graphical version has its own "Help" available in the GUI menu
 * 
 * ------------------------------
 *     Release Instructions
 * ------------------------------
 * After generating files using the Codec Engine GenServer Wizard, edit
 * codec.cfg. Assign values to any settings that are undefined:
 * 
 * Example: Original line: VIDDEC_COPY.alg.codeSection = undefined;
 * Modified line: VIDDEC_COPY.alg.codeSection = "DDR2";
 * Don't forget the quotes!
 *    
 * Note:
 *  - You must have the following on your XDCPATH to build a server:
 *      1. Codec Engine Dir/packages
 *      2. Codec Engine Dir/cetools/packages
 *      3. BIOS Directory/packages
 *  - Additionally you must have a config.bld or user.bld!
 *      1. Recommended: Edit the user.bld in XDC_x_xx/packages
 *      Note: XDC_x_xx/packages is automatically on your package path!
 *      2. Alternatively, you may create a user.bld anywhere as long as 
 *       its parent directory is on your XDCPATH 
 *  
 * Run "gmake all" to generate the server executable from the 
 * destination directory (destination directory + server.package.name.with.dots.
 * turned.into.forward.slashes).
 *    
 *   
 * Other information is available in the README.    
 */
metaonly module Main inherits xdc.tools.ICmd {

    override config String usage[] = [
        '[-g] [-f <file> | --xml <file>] [--cgtools <cgtools dir>] [-d <destination dir>]'
    ];

instance:

    /*! Gui */
    @CommandOption("g")
    config Bool gui = false;

    /*! TI C6000 codegen tools directory */
    @CommandOption('cgtools')
    config String cgTools = null;

    /*! package destination directory */
    @CommandOption('d')
    config String destDir = null;

    /*! XML File containing saved user input */
    @CommandOption("f,xml")
    config String xmlFile = null;

    //!Print informative messages during execution
    @CommandOption('debug')
    config Bool debugFlag = false;
}

/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

