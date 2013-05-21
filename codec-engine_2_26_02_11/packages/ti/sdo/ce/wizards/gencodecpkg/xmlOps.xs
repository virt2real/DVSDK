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

var csd = String(xdc.csd()).replace(/\\/g,"/");
var fileModule = xdc.module('xdc.services.io.File');
var logic;
var wizard_constants;

function setLogic(log)
{
    logic = log;
}

function setWizardConstants(wc)
{
    wizard_constants = wc;
}

/**
 * Logic to save userInput to an XML file
 * @param userInput
 * @return text to be saved to XML file
/*
 *  ======== saveXml ========
 */
function saveXml(codecPkgEnv)
{ 
    codecPkgEnv = logic.argsValidation(codecPkgEnv);
    try {
        var doc = <codecengine_gencodecpkg_wizard/>;

        doc.useGenAlg = codecPkgEnv.useGenAlg;
        doc.useLib = codecPkgEnv.useLib;
        doc.useInput = codecPkgEnv.useInput;
        doc.ceInstall = codecPkgEnv.ceInstall;
        doc.xdaisInstall = codecPkgEnv.xdaisInstall;
        doc.xdcInstall = codecPkgEnv.xdcInstall;
        doc.output = codecPkgEnv.output;
        doc.xdcVersOK = codecPkgEnv.xdcVersOK;
        doc.rulesCheck = codecPkgEnv.rulesCheck == true ? 'true' : 'false';
        doc.expertCheck = codecPkgEnv.expertCheck == true ? 'true' : 'false';
        if (codecPkgEnv.useInput) {
            doc.packageName = codecPkgEnv.input.packageName;
            doc.moduleName = codecPkgEnv.input.moduleName;
            doc.vendorName = codecPkgEnv.input.vendorName;
            doc.interfaceName = codecPkgEnv.input.interfaceName;
            doc.templateName = codecPkgEnv.input.templateName;
            var targets = <targets/>;
            for (var i = 0; i < codecPkgEnv.input.targets.length; i++) {
                var targ = <target/>;
                targ.@target = codecPkgEnv.input.targets[i].target;
                targ.@name = codecPkgEnv.input.targets[i].targname;
                targ.@suffix = codecPkgEnv.input.targets[i].targsuffix;
                targ.@ccOpts = codecPkgEnv.input.targets[i].ccOpts;
                targ.@cgTools = codecPkgEnv.input.targets[i].cgTools;
                targets.appendChild(targ);
            }
            doc.appendChild(targets);
            doc.algRepo = codecPkgEnv.output;
            doc.templatesDir = codecPkgEnv.templatesDir;
            doc.cgTools = codecPkgEnv.cgTools;
            if (codecPkgEnv.m3cgTools) {
                doc.m3cgTools = codecPkgEnv.m3cgTools;
            }
            if (codecPkgEnv.v5TcgTools) {
                doc.v5TcgTools = codecPkgEnv.v5TcgTools;
            }
            doc.ires = codecPkgEnv.input.ires == true ? 'true' : 'false';
        }
        else if (codecPkgEnv.useLib) {
            doc.packageName = codecPkgEnv.lib.packageName;
            doc.moduleName = codecPkgEnv.lib.moduleName;
            doc.vendorName = codecPkgEnv.lib.vendorName;
            doc.interfaceName = codecPkgEnv.lib.interfaceName;
            doc.templateName = codecPkgEnv.lib.templateName;
            doc.libFile = codecPkgEnv.libFile;
            doc.targsuffix = codecPkgEnv.lib.targsuffix;
        }
        doc.genCCSProj = codecPkgEnv.genCCSProj;
        var version = "<?xml version=\"1.0\"?>";
        return(version + doc.toXMLString());
    }
    catch (e) {
        print('exception ' + e.message);
        return ('');
    }
}


/**
 * Writes text to a file
 * @param {String} Output file location
 * @param {String} Text to be written to file 
 * @return {Integer} 0 for completion, 1 for error
 */
function textFileWriter(outputFileLocation, fileText)
{
    var file = fileModule.open(outputFileLocation, "w");
    var completed = file.writeLine(fileText.toString());
    file.close();
    if (completed == false) { 
        return 1;
    }
    return 0;
}

function textFileReader(inputFileLocation)
{

    var text = "";
    var file = fileModule.open(inputFileLocation, "r");
    var line;
    while ((line = file.readLine()) != null) {
          text += line + "\n";
    }
    file.close();    
    return text;
}

/**
* Logic to update userInput based on XML file
* @param XML file containing userInput data
* @return updated userInput based on XML file
*/ 
function loadXml(file, codecPkgEnv)
{
    var readXml = textFileReader(file);
    var doc = new XML(readXml);         

    var docname = String(doc.name());
    if (docname == 'xdais_genalg_wizard') {
        codecPkgEnv.genAlg = {};
        codecPkgEnv.wizardVersion = String(doc.version);
        codecPkgEnv.xdaisPackage = String(doc.packageName);
        codecPkgEnv.base = String(doc.base);

        codecPkgEnv.genAlg.targets = [];
        for (var i = 0; i < doc.targets.target.length(); i++) {
            var data = {};
            var targIndex = null;
            data.target = String(doc.targets.target[i].@target);
            data.targname = String(doc.targets.target[i].@name);;
            data.targsuffix = String(doc.targets.target[i].@suffix);
            if (doc.targets.target[i].@ccOpts.length()) {
                data.ccOpts = String(doc.targets.target[i].@ccOpts);
            }
            else {
                targIndex = logic.getTargetIndex(data.target);
                if (targIndex != -1) {
                    data.ccOpts = wizard_constants.ccOpts(targIndex);
                }
            }
            if (doc.targets.target[i].@cgTools.length()) {
                data.cgTools = String(doc.targets.target[i].@cgTools);
            }
            else {
                targIndex = (targIndex == null) ? logic.getTargetIndex(data.target) : targIndex;
                if (targIndex != -1) {
                    data.cgTools = wizard_constants.cgTools(targIndex);
                }
            }
            codecPkgEnv.genAlg.targets.push(data);
        }

        codecPkgEnv.algRepo = String(doc.outputRepository);
        codecPkgEnv.output = codecPkgEnv.algRepo;
        codecPkgEnv.genCCSProj = (doc.genCCSProj == 'true') ? true : false;
        codecPkgEnv.genAlg.moduleName = String(doc.moduleName);
        codecPkgEnv.genAlg.vendorName = String(doc.vendorName);
        codecPkgEnv.genAlg.interfaceName = String(doc.interfaceName);
        codecPkgEnv.genAlg.packageName = codecPkgEnv.xdaisPackage + '.ce';
        codecPkgEnv.genAlg.templateName = String(doc.templateName);
        codecPkgEnv.useGenAlg = true; 
        codecPkgEnv.useLib = false; 
        codecPkgEnv.useInput = false;
        codecPkgEnv.genAlg.ires = doc.ires == 'true' ? true : false;
    }
    else if (docname == 'codecengine_gencodecpkg_wizard') {
        codecPkgEnv.useGenAlg = doc.useGenAlg == 'true' ? true : false;
        codecPkgEnv.useLib = doc.useLib == 'true' ? true : false;;
        codecPkgEnv.useInput = doc.useInput == 'true' ? true : false;
        if (codecPkgEnv.gui) {
            if (String(doc.ceInstall).length) {
                codecPkgEnv.ceInstall = String(doc.ceInstall);
            }
            if (String(doc.xdaisInstall).length) {
                codecPkgEnv.xdaisInstall = String(doc.xdaisInstall);
            }
            if (String(doc.xdcInstall).length) {
                codecPkgEnv.xdcInstall = String(doc.xdcInstall);
            }
        }
        else {
            codecPkgEnv.ceInstall = String(doc.ceInstall);
            codecPkgEnv.xdaisInstall = String(doc.xdaisInstall);
            codecPkgEnv.xdcInstall = String(doc.xdcInstall)
        }
        codecPkgEnv.output = String(doc.output)
        codecPkgEnv.xdcVersOK = doc.xdcVersOK == 'true' ? true : false;
        codecPkgEnv.rulesCheck = doc.rulesCheck == 'true' ? true : false;
        codecPkgEnv.expertCheck = doc.expertCheck == 'true' ? true : false;
        if (codecPkgEnv.useInput) {
            codecPkgEnv.input = {};
            codecPkgEnv.input.packageName = String(doc.packageName);
            codecPkgEnv.input.moduleName = String(doc.moduleName);
            codecPkgEnv.input.vendorName = String(doc.vendorName);
            codecPkgEnv.input.interfaceName = String(doc.interfaceName);
            codecPkgEnv.input.templateName = String(doc.templateName);
            codecPkgEnv.input.targets = [];
            for (var i = 0; i < doc.targets.target.length(); i++) {
                var data = {};
                data.target = String(doc.targets.target[i].@target);
                data.targname = String(doc.targets.target[i].@name);;
                data.targsuffix = String(doc.targets.target[i].@suffix);
                data.ccOpts = String(doc.targets.target[i].@ccOpts);
                data.cgTools = String(doc.targets.target[i].@cgTools);
                codecPkgEnv.input.targets.push(data);
            }
            codecPkgEnv.output = String(doc.algRepo);
            codecPkgEnv.templatesDir = String(doc.templatesDir);
            codecPkgEnv.cgTools = String(doc.cgTools);
            if (doc.m3cgTools.length()) {
                codecPkgEnv.m3cgTools = String(doc.m3cgTools);
            }
            if (doc.v5TcgTools.length()) {
                codecPkgEnv.v5TcgTools = String(doc.v5TcgTools);
            }
            codecPkgEnv.input.ires = doc.ires == 'true' ? true : false;
        }
        else if (codecPkgEnv.useLib) {
            codecPkgEnv.lib = {};
            codecPkgEnv.lib.packageName = String(doc.packageName); 
            codecPkgEnv.lib.moduleName = String(doc.moduleName);
            codecPkgEnv.lib.vendorName = String(doc.vendorName);
            codecPkgEnv.lib.interfaceName = String(doc.interfaceName);
            codecPkgEnv.lib.templateName = String(doc.templateName);
            codecPkgEnv.libFile = String(doc.libFile);
            codecPkgEnv.lib.targsuffix = String(doc.targsuffix);
        }
        codecPkgEnv.genCCSProj = doc.genCCSProj == 'true' ? true : false;
    }
    return codecPkgEnv;
}

/**
* A relative path in a saved XML file (used in the examples dir) must be 
* evaluated 
* @param {String} Exact string from XML file 
* @return {String} Canonical Path of Input 
*/            
function relativePathCheck(path)
{ 
    path = String(path);
    if (path.length) {
        if (!java.io.File(path).isAbsolute()) {
            var canonicalPath = csd + path.substring(1, path.length);
        }
        else {
            var canonicalPath = path;
        }
        canonicalPath = String(java.io.File(canonicalPath).getCanonicalPath());
        return (canonicalPath.replace(/\\/g,"/"));
    } 
    return ("");
}



/*
 *  @(#) ti.sdo.ce.wizards.gencodecpkg; 1, 0, 0, 0,57; 12-2-2010 21:28:48; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

