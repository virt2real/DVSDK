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
/* For converting between base 64, binary, and hex */
var base64s = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
var hexDigits = new Array('0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
		'A', 'B', 'C', 'D', 'E', 'F');

var sections;
        
/*
 *  ======== instance$meta$init ========
 *  This function initializes a core dump instance.
 *  The core dump instance has an array of "data" objects (one per
 *  .out file), each with an address, a length, and a string of binary
 *  data.
 */
function instance$meta$init(xmlFile, fname)
{
    Program.debugPrint("xmlFile = " + xmlFile);
    
    this.$private.memory = new Array();
    
    /* Generate an XML object from the xml file */
    var File = xdc.module('xdc.services.io.File');
    var file = File.getCanonicalPath(xmlFile);

    if (file == null) {
        throw new Error("Xml core dump file not provided");
    }
    var ofd = xdc.loadXML(file);
    var memory = this.$private.memory;
    
    // for every data section in xmlFile
    for (var i in ofd.object_file) {
        var data = new Object();
        data.addr = parseInt(ofd.object_file[i].ti_coff.section.physical_addr);
        data.raw_data_size = parseInt(ofd.object_file[i].ti_coff.section.raw_data_size);
        data.addr_size = parseInt(ofd.object_file[i].ti_coff.section.addr_size);
        data.size = data.raw_data_size / data.addr_size;
        var xmlData = ofd.object_file[i].ti_coff.section.raw_data;
        data.binData =base64ToBinary(xmlData.toString());
        this.$private.bitsPerChar = data.addr_size * 8;
        memory[i] = data;
    }
    
    // sort sections by address.
    memory.sort(function(a,b){
        return (a.addr > b.addr);
    });
    
    // merge contiguous sections
    if (memory.length > 1) {
        for (var i=0; i<memory.length-1; i++) {
            if (memory[i].addr + memory[i].size == memory[i+1].addr) {
                memory[i].size += memory[i+1].size;
                memory[i].raw_data_size += memory[i+1].raw_data_size;
                memory[i].binData += memory[i+1].binData;
                memory = memory.splice((i+1), 1);
            }
        }
    }
    
    sections = getOfdSections(fname);
}

/*
 *  ======== read ========
 *  This function returns the requested data in a byte array. The byte array contains
 *  8bit signed data. Note that length of byte array passed in has to be large enough
 *  to contain requested data. This function throws an error is memory is not available.
 */
function read(base, length, byteArr, addrCheck)
{
    Program.debugPrint("Reading memory 0x" + base.toString(16) + "    " + length + " bytes");
    
    var data = null;
    var memory = this.$private.memory;

    if (!length) {
        throw new Error("Length = " + length + " for data requested at " + base);
    }

    /* Check if the read is valid using the ofd section info. */
    if (addrCheck) {
        var valid = false;
        // sections is an array of all the valid data sections.
        for (var i = 0; i < sections.size(); i++) {
            var sect = sections.get(i);
            if ((base >= sect.base) && 
                ((base + length) <= (sect.base + sect.length))) {
                valid = true;
                break;
            }   
        }
        if (!valid) {
            throw (new Error("Memory read failed at address: 0x" + Number(base).toString(16) + " length: " + length +
                             ". Read is not within a valid data section."));
        }
    }

    for (var i=0; i< memory.length; i++) {
        if ((base >= memory[i].addr) &&
            (base + length <= memory[i].addr + memory[i].size)
            ) {
            var offset = base - memory[i].addr;
            var intLength = length * memory[i].addr_size;
            data = memory[i].binData.substr(offset, intLength);
            break;
        }
    }
    
    if (data == null) {
        throw new Error("Memory requested at " + base + " not available ");
    }
    else {
        binDataToDecArr(data, byteArr, this.$private.bitsPerChar);
    }
    
}

/*
 *  ======== binDataToDecArr ========
 *  This function converts a string containing binary data into a byte array of decimal numbers
 *  ranging from +128 to -128;
 */
function binDataToDecArr(data, byteArray, bitsPerChar)
{
    var max = Math.pow(2, bitsPerChar);
    var maxPos = max/2;
    var bytesPerChar = bitsPerChar / 8;
    byteArray.length = 0;
    
    for (var i=0; i<data.length; i+=bytesPerChar) {
        var num = 0;
        for (var j=0; j<bytesPerChar; j++) {
	        num |= ((data.charCodeAt(i + j) & 0xff) << (8 * j));
        }
        if (num > maxPos) {
	        num = num - max;
	    }
        byteArray[byteArray.length++] = num;
   }
}

/*
 *  ======== binDataToHexArr ========
 *  For internal testing
 */
function binDataToHexArr(data, byteArray)
{
    for (var i=0; i<data.length; i++) {
        num = data.charCodeAt(i) & 0xff;
        byteArray[i] = byteToHex(num);
   }
}

function byteToHex(n)
{
    return hexDigits[(n >> 4) & 0xf] + hexDigits[n & 0xf];
}


/*  
 *  ======== base64ToBinary ========
 *  This function takes a string of data in base 64 format
 *  and converts it to binary format.
 */
function base64ToBinary(encStr) 
{
    var bits, decOut = '', i = 0;
  
    for(; i<encStr.length; i += 4){
        bits =
            (base64s.indexOf(encStr.charAt(i))    & 0xff) <<18 |
            (base64s.indexOf(encStr.charAt(i +1)) & 0xff) <<12 | 
            (base64s.indexOf(encStr.charAt(i +2)) & 0xff) << 6 |
            base64s.indexOf(encStr.charAt(i +3)) & 0xff;
        decOut += String.fromCharCode(
            (bits & 0xff0000) >>16, (bits & 0xff00) >>8, bits & 0xff);
    }
    if(encStr.charCodeAt(i -2) == 61)
        undecOut=decOut.substring(0, decOut.length -2);
    else if(encStr.charCodeAt(i -1) == 61)
        undecOut=decOut.substring(0, decOut.length -1);
    else undecOut=decOut;
  
    return (undecOut);
}

function getOfdSections(fname)
{
    var ofdExe = "C:\\CCStudio_v3.3\\C6000\\cgtools\\bin\\ofd6x.exe";
    
    /* Run ofd to get section info */
    var xmlObject = runOfd(ofdExe, fname);
    
    /* Get the 'section' XML elements from the OFD output */
    var XMLSections = xmlObject.object_file.ti_coff.section;
  
    /* 
     * Go through all of the sections, add them to a new array,
     * and maintain running sizes for the benchmark.
     */
    sections = {};
    sections.sects = new Array();
    sections.size = function() { return sections.sects.length; };
    sections.get = function(index) { return sections.sects[index]; };
    
    for (var i in XMLSections) {
        if ((XMLSections[i].bss == true) ||
            (XMLSections[i].data == true)) {
            
            var section = new Object();
            section.name = String(XMLSections[i].name);
            section.base = Number(XMLSections[i].physical_addr);
            section.length = Number(XMLSections[i].raw_data_size);
            sections.sects[sections.sects.length] = section;
        }
    }
    /* Clean up */
    delete xmlObject;
    delete XMLSections;  
    
    return (sections);
}


/*
 * ======== runOfd ========
 * Runs ofd on the executable, returning an XML object
 */
function runOfd(ofd, filename)
{
    /* Run OFD on the executable */
    var ofdproc = xdc.jre.java.lang.Runtime.getRuntime().exec(ofd + " -x " + filename);
    
    /* Build the output into a single String using a String builder */
    var sr = new xdc.jre.java.io.InputStreamReader(ofdproc.getInputStream());
    var br = new xdc.jre.java.io.BufferedReader(sr);
    var sb = new java.lang.StringBuilder();
    var line = "";
    while ((line = br.readLine()) != null) {
        sb.append(line);
    }
    
    var javaStr = sb.toString();
    
    /* Strip the raw_data sections since they may violate xml */
    //var strippedXML = stripRawData(String(javaStr));
    
    /* Create an XML object from the String */
    //var XMLobject = new XML(strippedXML);
    
    var XMLobject = new XML(javaStr);
    
    /* clean up */
    delete javaStr;
    delete ofdproc;
    delete br;
    delete sb;
    delete sr;
    
    return(XMLobject);
}

function stripRawData(ofdOut)
{
    /* Raw data may contain a-z, A-Z, 0-9, =, +, /, or \n */
    return(ofdOut.replace(/<raw_data>[a-zA-Z0-9\=\+\/\n]*<\/raw_data>/g, ""));
}

