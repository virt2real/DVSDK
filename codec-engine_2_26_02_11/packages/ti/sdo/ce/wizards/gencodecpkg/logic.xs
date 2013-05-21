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

var xmlOps = xdc.loadCapsule("xmlOps.xs");
var shared_gui = xdc.loadCapsule("shared_gui.xs");
var wizard_constants = xdc.loadCapsule("wizard_constants.xs");
var mkpkg = xdc.module("xdc.tools.mkpkg.Main");
var csd = String(xdc.csd()).replace(/\\/g,"/");

var inheritsMap = {
    'IAUDENC' : 'ti.sdo.ce.audio.IAUDENC',
    'IAUDDEC' : 'ti.sdo.ce.audio.IAUDDEC',
    'IAUDENC1' : 'ti.sdo.ce.audio1.IAUDENC1',
    'IAUDDEC1' : 'ti.sdo.ce.audio1.IAUDDEC1',
    'IIMGDEC'  : 'ti.sdo.ce.image.IIMGDEC',
    'IIMGENC'  : 'ti.sdo.ce.image.IIMGENC',
    'IIMGENC1' : 'ti.sdo.ce.image1.IIMGENC1',
    'IIMGDEC1' : 'ti.sdo.ce.image1.IIMGDEC1',
    'ISPHENC'  : 'ti.sdo.ce.speech.ISPHENC',
    'ISPHDEC'  : 'ti.sdo.ce.speech.ISPHDEC',
    'ISPHENC1' : 'ti.sdo.ce.speech1.ISPHENC1',
    'ISPHDEC1' : 'ti.sdo.ce.speech1.ISPHDEC1',
    'IUNIVERSAL' : 'ti.sdo.ce.universal.IUNIVERSAL',
    'IVIDANALYTICS' : 'ti.sdo.ce.vidanalytics.IVIDANALYTICS',
    'IVIDDEC'  : 'ti.sdo.ce.video.IVIDDEC',
    'IVIDENC'  : 'ti.sdo.ce.video.IVIDENC',
    'IVIDDEC1' : 'ti.sdo.ce.video1.IVIDDEC1',
    'IVIDENC1' : 'ti.sdo.ce.video1.IVIDENC1',
    'IVIDDEC2' : 'ti.sdo.ce.video2.IVIDDEC2',
    'IVIDTRANSCODE' : 'ti.sdo.ce.vidtranscode.IVIDTRANSCODE'
};

function argsValidation(codecPkgEnv)
{

    var proot = csd + '/..';
    var pn = 'ti.sdo.ce.wizards.gencodecpkg';
    for (var i = 0; (i = pn.indexOf('.', i) + 1) > 0; ) {
            proot += '/..';
    }
    proot = String(java.io.File(proot).getCanonicalPath()).replace(/\\/g, '/');
  
    if (codecPkgEnv.xmlFile != null && codecPkgEnv.xmlFile != "null") {
        if ( java.io.File(codecPkgEnv.xmlFile).exists() ) {
            try {
                codecPkgEnv = xmlOps.loadXml(codecPkgEnv.xmlFile, codecPkgEnv);
                if (codecPkgEnv.gui) {
                    codecPkgEnv.genAlgFileLoaded = true;
                }
            }
            catch(e) { 
                gprint("Error: " + e, codecPkgEnv); 
            }
        }
        else { 
            gprint("XML File, " + codecPkgEnv.xmlFile + ", not found. "
                + "Wizard starting without loading XML File...", 
                codecPkgEnv); 
            codecPkgEnv.xmlFile = "null";
        }
    }

    if (codecPkgEnv.useGenAlg != true && codecPkgEnv.useGenAlg != false) {
        codecPkgEnv.useGenAlg = true;
        codecPkgEnv.useLib = false;
        codecPkgEnv.useInput = false;
    }

    if (!codecPkgEnv.genAlg) {
        codecPkgEnv.genAlg = {};
    }
    if (!codecPkgEnv.genAlg.moduleName) {
        codecPkgEnv.genAlg.moduleName = '';
    }
    if (!codecPkgEnv.genAlg.vendorName) {
        codecPkgEnv.genAlg.vendorName = '';
    }
    if (!codecPkgEnv.genAlg.interfaceName) {
        codecPkgEnv.genAlg.interfaceName = '';
    }
    if (!codecPkgEnv.genAlg.packageName) {
        codecPkgEnv.genAlg.packageName = '';
    }
    if (!codecPkgEnv.lib) {
        codecPkgEnv.lib = {};
    }
    if (!codecPkgEnv.lib.moduleName) {
        codecPkgEnv.lib.moduleName = '';
    }
    if (!codecPkgEnv.lib.vendorName) {
        codecPkgEnv.lib.vendorName = '';
    }
    if (!codecPkgEnv.lib.interfaceName) {
        codecPkgEnv.lib.interfaceName = '';
    }
    if (!codecPkgEnv.lib.packageName) {
        codecPkgEnv.lib.packageName = 'mycompany.mycodec';
    }

    if (!codecPkgEnv.input) {
        codecPkgEnv.input = {};
    }
    if (!codecPkgEnv.input.moduleName) {
        codecPkgEnv.input.moduleName = 'MYMODULE';
    }
    if (!codecPkgEnv.input.vendorName) {
        codecPkgEnv.input.vendorName = 'MYCOMPANY';
    }
    if (!codecPkgEnv.input.interfaceName) {
        codecPkgEnv.input.interfaceName = 'I' + codecPkgEnv.input.moduleName;
    }
    if (!codecPkgEnv.input.packageName) {
        codecPkgEnv.input.packageName = codecPkgEnv.input.vendorName.toLowerCase() +
                                        '.' +
                                        codecPkgEnv.input.moduleName.toLowerCase();
    }
    if (!codecPkgEnv.input.targets) {
        try {
            var tmod = xdc.useModule(wizard_constants.targetList[0]);
            var data = {};
            data.target = wizard_constants.targetList[0];
            data.targname = tmod.name;
            data.targsuffix = tmod.suffix;
            data.ccOpts = wizard_constants.ccOpts[0];
            data.cgTools = wizard_constants.cgTools[0];
            codecPkgEnv.input.targets = [];
            codecPkgEnv.input.targets.push(data);
        }
        catch (e) {
        }
    }

    if (!codecPkgEnv.xdaisPackageName) {
        codecPkgEnv.xdaisPackageName = '';
    }

    if (codecPkgEnv.output == null || codecPkgEnv.output == 'null') {
        codecPkgEnv.output = wizard_constants.ENTER_OUTREPO;
    }

    if (!codecPkgEnv.ceInstall ||
        !java.io.File(codecPkgEnv.ceInstall).exists()) {
        codecPkgEnv.ceInstall = proot.replace(/\/packages$/, '');
    }
    if (!codecPkgEnv.xdaisInstall ||
        !java.io.File(codecPkgEnv.xdaisInstall).exists()) {
        try {
            codecPkgEnv.xdaisInstall = xdc.getPackageBase('ti.xdais.dm');
            codecPkgEnv.xdaisInstall = codecPkgEnv.xdaisInstall.replace(/\\/g, '/');
            codecPkgEnv.xdaisInstall = codecPkgEnv.xdaisInstall.replace(/\/+$/, '');
            codecPkgEnv.xdaisInstall = codecPkgEnv.xdaisInstall.replace(/\/packages\/ti\/xdais\/dm$/, '');
        }
        catch (e) {
            if (java.io.File(codecPkgEnv.ceInstall + '/cetools/packages').exists()) {
                codecPkgEnv.xdaisInstall = codecPkgEnv.ceInstall + '/cetools';
            }
            else {
                codecPkgEnv.xdaisInstall = wizard_constants.ENTER_XDAIS;
            }
            
        }
    }

    if (!codecPkgEnv.templatesDir || 
        !java.io.File(codecPkgEnv.templatesDir).exists()) {
        var dir = codecPkgEnv.xdaisInstall + '/packages/ti/xdais/dm/templates';
        if (java.io.File(dir).exists()) {
            codecPkgEnv.templatesDir = dir;
        }
        else {
            codecPkgEnv.templatesDir = '';
        }
    }

    if (!codecPkgEnv.xdcInstall ||
        !java.io.File(codecPkgEnv.xdcInstall).exists()) {
        codecPkgEnv.xdcInstall = xdc.getPackageBase('xdc');
        codecPkgEnv.xdcInstall = codecPkgEnv.xdcInstall.replace(/\\/g, '/');
        codecPkgEnv.xdcInstall = codecPkgEnv.xdcInstall.replace(/\/+$/, '');
        codecPkgEnv.xdcInstall = codecPkgEnv.xdcInstall.replace(/\/packages\/xdc$/, '');
        codecPkgEnv.xdcVersOK = false;
        for each (var f in java.io.File(codecPkgEnv.xdcInstall + '/eclipse/plugins').listFiles()) {
            if (f.isFile()) {
                continue;
            }
            var name = String(f.getName());
            if (name.match(/^org.eclipse.rtsc.xdctools.core_/)) {
                codecPkgEnv.xdcVers = name.substr(31);
                if (Number(codecPkgEnv.xdcVers.substr(0, 4)) >= 3.16) {
                    codecPkgEnv.xdcVersOK = true;
                }
                break;
            }
        }
    }

    if (!codecPkgEnv.algRepo) {
        codecPkgEnv.algRepo = '';
    }

    if (codecPkgEnv.genCCSProj != true && codecPkgEnv.genCCSProj != false) {
        codecPkgEnv.genCCSProj = true;
    }
    if (!codecPkgEnv.cgTools) {
        var cgTools = codecPkgEnv.xdcInstall + '/../ccsv4/tools/compiler/c6000';
        var validCgTools = validCgToolsDir(cgTools);
        if (!validCgTools && java.io.File(codecPkgEnv.xdaisInstall).exists()) {
            cgTools = codecPkgEnv.xdaisInstall + '/../ccsv4/tools/compiler/c6000';
            validCgTools = validCgToolsDir(cgTools);
        }
        if (validCgTools) {
            codecPkgEnv.cgTools =
                String(java.io.File(cgTools).getCanonicalPath()).replace(/\\/g, '/');
        }
    }
    if (!codecPkgEnv.v5TcgTools) {
        codecPkgEnv.v5TcgTools = wizard_constants.ENTER_ARM_CGTOOLS
    }
    return codecPkgEnv;
}

function gprint(message, codecPkgEnv) {
    if (codecPkgEnv.gui == true) {
        shared_gui.createMessageBox(message, codecPkgEnv);
    }
    else{
        print(message);
    }
}

function createFiles(codecPkgEnv) {

    var status = 0;
    //codecPkgEnv = argsValidation(codecPkgEnv);
    codecPkgEnv = translateUseCase(codecPkgEnv);
    codecPkgEnv.output = codecPkgEnv.output.replace("//", "/");
    codecPkgEnv.output = codecPkgEnv.output.replace(/\\/g,"/");

    var outputDir = codecPkgEnv.output + '/' + codecPkgEnv.packageName.replace(/\./g,'/');
    if (java.io.File(outputDir).exists()) {
        var list = java.io.File(outputDir).list();
        if (list.length!=0) {
            if (!codecPkgEnv.gui) {
                gprint("\nWarning: " + outputDir + " is not empty--files may be "
                    + "overwritten... Would you like to continue? y/n", 
                    codecPkgEnv);
                var isr = new java.io.InputStreamReader( 
                    java.lang.System["in"]);
                var br = new java.io.BufferedReader(isr);
                
                try{
                    var output = br.readLine();
                }
                catch(e) {}
    
                if (output == "n") {
                    gprint("Quitting now...", codecPkgEnv);
                    status = 1;
                }
                else if(output != "y") {
                    gprint("Invalid selection. Quitting now...", codecPkgEnv);
                    status = 1;
                }
            }
        }
    } 

    if (status == 0) {    
        /* function mkpkg( template_dir, output, args) */
        try {
            var pkgObj = {};
            pkgObj.packageName = codecPkgEnv.packageName;
            pkgObj.xdaisPackage = codecPkgEnv.xdaisPackage;
            pkgObj.module = codecPkgEnv.moduleName.toUpperCase();
            pkgObj.vendor = codecPkgEnv.vendorName.toUpperCase();
            pkgObj.inface = codecPkgEnv.interfaceName.toUpperCase();
            pkgObj.inherits = inheritsMap[codecPkgEnv.templateName];
            pkgObj.ceInstall = codecPkgEnv.ceInstall;
            pkgObj.xdaisInstall = codecPkgEnv.xdaisInstall.replace(/\\/g,'/');;
            pkgObj.xdcInstall = codecPkgEnv.xdcInstall;
            pkgObj.algRepo = codecPkgEnv.algRepo;
            pkgObj.useGenAlg = codecPkgEnv.useGenAlg;
            pkgObj.useLib = codecPkgEnv.useLib;
            pkgObj.useInput = codecPkgEnv.useInput;
            pkgObj.xdcVersOK = codecPkgEnv.xdcVersOK;
            pkgObj.cgTools = '';
            pkgObj.ires = codecPkgEnv.ires;
            pkgObj.templateName = codecPkgEnv.templateName;
            if (codecPkgEnv.useInput) {
                pkgObj.targets = codecPkgEnv.targets;

                var C6x = false;
                var v5T = false;
                for (var i = 0; i < pkgObj.targets.length; i++) {
                    if (!C6x && (pkgObj.targets[i].cgTools == 'C64P' || pkgObj.targets[i].cgTools == 'C674')) {
                        C6x = true;
                    }
                    else if (!v5T && pkgObj.targets[i].cgTools == 'v5T') {
                        v5T = true;
                    }
                    if (C6x && v5T) {
                        break;
                    }
                }
                if (C6x) {
                    pkgObj.cgTools = codecPkgEnv.cgTools;
                    if (pkgObj.cgTools) {
                        pkgObj.cgTools = pkgObj.cgTools.replace(/\\/g,'/');
                    }
                }
                else {
                    pkgObj.cgTools = null;
                }
                if (v5T) {
                    pkgObj.v5TcgTools = codecPkgEnv.v5TcgTools;
                    if (pkgObj.v5TcgTools) {
                        pkgObj.v5TcgTools = pkgObj.v5TcgTools.replace(/\\/g,'/');
                    }
                }
                else {
                    pkgObj.v5TcgTools = null;
                }
                mkpkg.mkpkg(codecPkgEnv.templatesDir + '/' + codecPkgEnv.templateName,
                            outputDir, pkgObj);

                mkpkg.mkpkg(codecPkgEnv.xdaisInstall +
                            '/packages/ti/xdais/wizards/genalg/templates/build',
                            outputDir, pkgObj);
            }
            else if (codecPkgEnv.useLib) {
                pkgObj.libFile =
                       String(java.io.File(codecPkgEnv.libFile).getName());
                pkgObj.targsuffix = codecPkgEnv.targsuffix;
                copyFile(codecPkgEnv.libFile, outputDir + '/lib');
            }
            mkpkg.mkpkg('ti/sdo/ce/wizards/gencodecpkg/templates', outputDir,
                        pkgObj);
            if (codecPkgEnv.ires) {
                mkpkg.mkpkg("ti/xdais/wizards/genalg/templates", outputDir,
                            pkgObj);
            }
            if (codecPkgEnv.genCCSProj) {
                mkpkg.mkpkg("ti/sdo/ce/wizards/gencodecpkg/templates/ccsv4",
                            outputDir, pkgObj);
            }
            if (codecPkgEnv.gui && (codecPkgEnv.useInput || codecPkgEnv.useLib)) {
                var fname = outputDir + '/' +
                            codecPkgEnv.packageName.replace(/\./g,'_') +
                            '_wizard.gencodecpkg';
                saveXmlFile(codecPkgEnv, fname);
            }
        }
        catch (e) {
            gprint("An error while creating package " +
                    codecPkgEnv.packageName + ":\n" + e, codecPkgEnv);
            status = 1;
        }
    }
    return(status);
}


function translateUseCase(codecPkgEnv)
{
    if (codecPkgEnv.useGenAlg) {
        codecPkgEnv.packageName = codecPkgEnv.genAlg.packageName;
        codecPkgEnv.moduleName = codecPkgEnv.genAlg.moduleName;
        codecPkgEnv.vendorName = codecPkgEnv.genAlg.vendorName;
        codecPkgEnv.interfaceName = codecPkgEnv.genAlg.interfaceName;
        codecPkgEnv.templateName = codecPkgEnv.genAlg.templateName;
        codecPkgEnv.targets = codecPkgEnv.genAlg.targets;
        codecPkgEnv.ires = codecPkgEnv.genAlg.ires;
    }
    else if (codecPkgEnv.useLib) {
        codecPkgEnv.packageName = codecPkgEnv.lib.packageName;
        codecPkgEnv.moduleName = codecPkgEnv.lib.moduleName;
        codecPkgEnv.vendorName = codecPkgEnv.lib.vendorName;
        codecPkgEnv.interfaceName = codecPkgEnv.lib.interfaceName;
        codecPkgEnv.templateName = codecPkgEnv.lib.templateName;
        codecPkgEnv.targsuffix = codecPkgEnv.lib.targsuffix;
    }
    else if (codecPkgEnv.useInput) {
        codecPkgEnv.packageName = codecPkgEnv.input.packageName;
        codecPkgEnv.moduleName = codecPkgEnv.input.moduleName;
        codecPkgEnv.vendorName = codecPkgEnv.input.vendorName;
        codecPkgEnv.interfaceName = codecPkgEnv.input.interfaceName;
        codecPkgEnv.templateName = codecPkgEnv.input.templateName;
        codecPkgEnv.targets = codecPkgEnv.input.targets;
        codecPkgEnv.ires = codecPkgEnv.input.ires;
    }
    return (codecPkgEnv);
}

/*
 *  ======== copyFile ========
 */
function copyFile(srcFileName, dstDir)
{
    var srcFile = java.io.File(srcFileName);
    var dstFile = java.io.File(dstDir + '/' + srcFile.getName());
    dstFile.getParentFile().mkdirs();

    var outs;
    var ins;
    try {
        outs = new java.io.FileOutputStream(dstFile);
        ins = new java.io.FileInputStream(srcFile);
    }
    catch (e) {
        if (ins) ins.close();
        if (outs) outs.close();
        throw new Error('cannot create stream');
    }

    var inc = ins.getChannel();
    var outc = outs.getChannel();
    inc.transferTo(0, inc.size(), outc);

    ins.close();
    outs.close();
}

/*
 *  ======== saveXmlFile ========
 */
function saveXmlFile(codecPkgEnv, file) { 
    var xmlText = xmlOps.saveXml(codecPkgEnv, file);
    try {
        var status = xmlOps.textFileWriter(file, xmlText);
        if (status == -1) {
            return (false)
        }
        return (true);
    }
    catch(e) {
    }  
    return (false);
}

function validCgToolsDir(dir)
{
    if (!String(dir).length) {
        return (false);
    }
    var valid = true;
    var clFile = dir + '/bin/cl6x';
    var clExeFile = dir + '/bin/cl6x.exe';
    if (!java.io.File(clFile).exists() &&
        !java.io.File(clExeFile).exists()) {
        valid = false;
    }
    return (valid);
}

function validv5TcgToolsDir(dir)
{
    if (!String(dir).length) {
        return (false);
    }
    var valid = true;
    if (!java.io.File(dir + '/bin/arm-none-linux-gnueabi-gcc').exists()) {
        valid = false;
    }
    return (valid);
}

function getTargetIndex(target)
{
    for (var i = 0; i < wizard_constants.targetList.length; i++) {
        if (wizard_constants.targetList[i] == target) {
            return (i);
        }
    }
    return (-1);
}
/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,57; 12-2-2010 21:28:47; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

