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
 * */
codecPkgEnv = {};
var logic = xdc.loadCapsule("logic.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var gui;

/*
 *  ======== run ========
 */
function run(cmdr, args)
{
    var inst = this.$private
    inst.self = this;

    for (p in inst.self) inst[p] = inst.self[p];

    inst.cmdr = cmdr;
    inst.args = args;

    /* for each module in this package ... */
    for each (var mod in this.$package.$modules) {
        var cap = mod.$capsule;
        if (cap && "createPartControl" in cap) {
            gui = cap;
            break;
        }
    }

    if (!gui) {
        print("\nCannot start Codec Engine GenCodecPkg Wizard. Please " +
              "make sure the package ti.sdo.ce.wizards.gencodecpkg " +
              "is completely built.");
        return;
    }

    codecPkgEnv.wizardVersion = wizard_constants.wizardVersion;
    
    /* store the cmd line params in our data structure
        all arguments are optional unless otherwise noted */
    codecPkgEnv.xmlFile = inst.xmlFile;
    codecPkgEnv.gui = inst.gui ? inst.gui : !codecPkgEnv.xmlFile;
    codecPkgEnv.shellLocation;
    codecPkgEnv.error = false;
    
    codecPkgEnv.argvArgs = [];
    for each (var a in inst.args) {
        codecPkgEnv.argvArgs.push(a);
    }

    /* replace since user can enter backward slashes on command line */
    if (codecPkgEnv.xmlFile) {
        codecPkgEnv.xmlFile = (codecPkgEnv.xmlFile + "").replace(/\\/g,"/");
    }

    try {
        if (cmdr.tid) {
            codecPkgEnv.tid = cmdr.tid;
            codecPkgEnv.guiId = cmdr.tid + 1;
        }
        else {
            codecPkgEnv.tid = codecPkgEnv.guiId = 0; 
        }
    }
    catch (e) {
        codecPkgEnv.tid = codecPkgEnv.guiId = 0; 
    }

    if (codecPkgEnv.tid != codecPkgEnv.guiId) {
        codecPkgEnv = logic.argsValidation(codecPkgEnv);
        gui.setCodecPkgEnv(codecPkgEnv);

        /* create an instance of IWorkbenchPart and send it */
        /* back to the tools server to call gui.createPartControl */
        var wbp = new Packages.org.eclipse.ui.IWorkbenchPart(gui);
        cmdr.socket.giveToClient(wbp); 

        /* wait for gui to close */
        var val = cmdr.socket.takeFromClient();
    }
    else {
        if (codecPkgEnv.gui) {
            codecPkgEnv = logic.argsValidation(codecPkgEnv);

            /* inst overrides logic defaults */
            if (inst.xdaisInstall) {
                codecPkgEnv.xdaisInstall = inst.xdaisInstall;
            }
            if (inst.cgTools) {
                codecPkgEnv.cgTools = inst.cgTools;
            }
            if (inst.v5TcgTools) {
                codecPkgEnv.v5TcgTools = inst.v5TcgTools;
            }
            if (inst.destDir) {
                codecPkgEnv.output = inst.destDir;
            }
            gui.setCodecPkgEnv(codecPkgEnv);
            codecPkgEnv = gui.main(codecPkgEnv);
        
        }
        else if (codecPkgEnv.xmlFile == "null") {
            print("\nCommand Line Version requires XML File! "
                + "See xs ti.sdo.ce.wizards.gencodecpkg --help for more information.");
            codecPkgEnv.gui = true;
            codecPkgEnv = logic.argsValidation(codecPkgEnv);
            /* inst overrides logic defaults */
            if (inst.xdaisInstall) {
                codecPkgEnv.xdaisInstall = inst.xdaisInstall;
            }
            if (inst.cgTools) {
                codecPkgEnv.cgTools = inst.cgTools;
            }
            if (inst.v5TcgTools) {
                codecPkgEnv.v5TcgTools = inst.v5TcgTools;
            }
            if (inst.destDir) {
                codecPkgEnv.output = inst.destDir;
            }
            codecPkgEnv = gui.main(codecPkgEnv);
        }
        else {
            print("\nStarting Command Line Codec Engine GenCodecPkg Wizard...");
            codecPkgEnv = logic.argsValidation(codecPkgEnv);
            /* inst overrides both xml and logic defaults */
            if (inst.xdaisInstall) {
                codecPkgEnv.xdaisInstall = inst.xdaisInstall;
            }
            if (inst.cgTools) {
                codecPkgEnv.cgTools = inst.cgTools;
            }
            if (inst.v5TcgTools) {
                codecPkgEnv.v5TcgTools = inst.v5TcgTools;
            }
            if (inst.destDir) {
                codecPkgEnv.output = inst.destDir;
            }
        }
    }
    if (!codecPkgEnv.cancel) {
        if (logic.createFiles(codecPkgEnv) == 0) {
            var output = codecPkgEnv.output + '/' + codecPkgEnv.packageName.replace(/\./g,'/');

            logic.gprint( "\nPackage creation successful...\n"
                + "Files output to " + output, codecPkgEnv);
        }
        else {
            codecPkgEnv.error = true;
        }
    }
    if (codecPkgEnv.error) {
        logic.gprint("\nPackage creation unsuccessful.", codecPkgEnv);
    }
}



/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,57; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

