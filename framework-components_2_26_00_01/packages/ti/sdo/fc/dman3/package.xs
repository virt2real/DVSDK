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

var UTILS = xdc.loadCapsule('ti/sdo/fc/utils/utils.xs');
/*
 *  ======== validate ========
 */
function validate()
{

    var suffix = Program.build.target.findSuffix(this); 

    if (null == suffix) {
        return (null);
    }

    if (!(suffix.match(/64P/)) && (!(suffix.match(/674/))) &&
            (this.DMAN3.useExternalRM == true)) {
       throw("\n\n  DMAN3 Error: Configured DMAN3.useExternalRM = true for " +
             "non-C64P device. This mode supported only for C64P devices.");  
    }

    if (this.DMAN3.useExternalRM == false) { 
        if ((this.DMAN3.paRamBaseIndex + this.DMAN3.numPaRamEntries) >
                this.DMAN3.maxPaRamEntries ) {
            throw("\n\n  DMAN3 Error: configured DMAN3.numPaRamEntries (base " +
                "index:  " + this.DMAN3.paRamBaseIndex + ", number of " + 
                "entries: " + this.DMAN3.numPaRamEntries + ") exceeds the " +
                "maximum number of PaRam entries on this Chip (" + 
                this.DMAN3.maxPaRamEntries + "). Reduce DMAN3.numPaRamEntries" +
                " and/or adjust DMAN3.paRamBaseIndex so that it is within a " +
                "valid range.");
        }

        if ( this.DMAN3.nullPaRamIndex  >= this.DMAN3.maxPaRamEntries ) {
            throw("\n\n  DMAN3 Error: configured DMAN3.nullPaRamIndex (" +
                this.DMAN3.nullPaRamIndex + ") assigned to a value greater " +
                "than DMAN3.maxPaRamEntries (" + this.DMAN3.maxPaRamEntries +
                ").");
        }

        if ((this.DMAN3.nullPaRamIndex >= this.DMAN3.paRamBaseIndex) &&
                (this.DMAN3.nullPaRamIndex <
                (this.DMAN3.paRamBaseIndex + this.DMAN3.numPaRamEntries))) {
            throw("\n\n  DMAN3 Error: configured DMAN3.nullPaRamIndex (" +
                this.DMAN3.nullPaRamIndex + ") already assigned " +
                "to DMAN3 as free PaRam.  Select a different " +
                "DMAN3.nullPaRamIndex value outside of assigned DMAN3 range (" +
                "currently (" + this.DMAN3.paRamBaseIndex + " - " +
                (this.DMAN3.paRamBaseIndex + this.DMAN3.numPaRamEntries) +").");
        }

        if ((this.DMAN3.maxTCs > 8) || (this.DMAN3.maxTCs <= 0)) {
            throw("\n\n DMAN3 Error: config DMAN3.maxTCs should be > 0 and " +
            "<= 8. " + "Bad value " + this.DMAN3.maxTCs + "; please " +
            "reconfigure.");

        }

        for (var i = 0; i < this.DMAN3.numQdmaChannels; i++) {
            if ((this.DMAN3.qdmaQueueMap[i] >= this.DMAN3.maxTCs) ||
                    (this.DMAN3.qdmaQueueMap[0] < 0)) {
                throw("\n\n DMAN3 Error: config DMAN3.qdmaQueueMap[", + i +"]" +
                " should be > 0 and < DMAN3.maxTCs. Bad value " +
                this.DMAN3.qdmaQueueMap[i] + ". Please reconfigure");
            }
        }

        for (var j = 0; i < this.DMAN3.numQdmaChannels; j++) {
            if ((this.DMAN3.queueTCMap[i] >= this.DMAN3.maxTCs) ||
                    (this.DMAN3.queueTCMap[0] < 0)) {
                throw("\n\n DMAN3 Error: config DMAN3.queueTCMap[" + j + "]" +
                    " should be > 0 and < DMAN3.maxTCs. Bad value " +
                    this.DMAN3.queueTCMap[j] + ". Please reconfigure");
            }
        }

        //TODO: Can total up the numQdmaGroup channels and make sure they are
        //      less than the numQdma total. 
    
    }
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{

    var suffix = Program.build.target.findSuffix(this);

    if (null == suffix) {
        return (null);
    }

    /* The below check is only for C64 targets, but that's already being
       checked below */ 
    if (this.DMAN3.useExternalRM) {
        var libs = "dman3RMCfg"
    }
    else {
        var libs = "dman3Cfg"
    }

    if (suffix == "86U") {
        /* Always add the cpu suffix for x86 */ 
        libs += "cpu";
    }
    else {
 
        /* For all other targets, check the configuration */ 
        if (this.DMAN3.cpu) {
            libs += "cpu";
        }
    }

    libs += ".a" + suffix;


    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libs).exists()) {
        print(this.$name + ": Requested profile '" + this.profile + "' does "
                + "not exist.\n\tDefaulting to the 'release' profile");
 
       dir = "lib/release";
    }

    print("    will link with " + this.$name + ":" + dir + "/" + libs);
    return (dir + "/" + libs);
}


/*
 * ======== close ========
 */
function close() {

    if ((this.DMAN3.debug) || (this.DMAN3.trace)) {
        print(this + ": This module no longer supports the .debug "
                + "or the .trace config params. Set desired profile for all "
                + "FC modules as follows: "
                + "xdc.useModule\('ti.sdo.fc.global.Settings'\).profile = "
                + "\"debug\""
                + " or set profiles for individual packages like this: "
                + "xdc.loadPackage('" 
                + this + "').profile = \"debug\"\;"
                + " .\n\tDefaulting to the 'release' profile");
    } 

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    var defaultQdmaPaRamBase = 0x1C04000;
    var defaultMaxPaRamEntries = 128;
    var defaultMaxQdmaChannels = 8;
    var defaultPaRamBaseIndex = 96;
    var defaultNumPaRamEntries = 32;
    var defaultNullPaRamIndex = 0;
    var defaultNumQdmaChannels = 4;
    
    var defaultQdmaChannels = [0,1,2,3];;
    var defaultTccAllocationMaskH = 0xffffffff; 
    var defaultTccAllocationMaskL = 0x00000000;
    var defaultQdmaQueueMap =[1,1,1,1,1,1,1,1];;
    var defaultQueueTCMap =[0,1,2,3,4,5,6,7];;
    var defaultQueuePri = [3,7,0,0,0,0,0,0];
    
    var defaultNumTccGroup = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
    var defaultNumPaRamGroup = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];
    var defaultNumQdmaGroup = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

    if (this.DMAN3.useExternalRM == true) {

        if (this.DMAN3.qdmaPaRamBase != defaultQdmaPaRamBase) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"qdmaPaRamBase\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (this.DMAN3.maxPaRamEntries != defaultMaxPaRamEntries) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"maxPaRamEntries\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (this.DMAN3.maxQdmaChannels != defaultMaxQdmaChannels) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"maxQdmaChannels\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (this.DMAN3.paRamBaseIndex != defaultPaRamBaseIndex) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"paRamBaseIndex\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (this.DMAN3.nullPaRamIndex != defaultNullPaRamIndex) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"nullPaRamIndex\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (!UTILS.compareArray(this.DMAN3.qdmaChannels, defaultQdmaChannels)){
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"qdmaChannels\" will be ignored. Configure" +
                " ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (this.DMAN3.tccAllocationMaskH != defaultTccAllocationMaskH) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"tccAllocationMaskH\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (this.DMAN3.tccAllocationMaskL != defaultTccAllocationMaskL) {
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"tccAllocationMaskL\" will be ignored. Configure " +
                "ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (!UTILS.compareArray(this.DMAN3.qdmaQueueMap, defaultQdmaQueueMap)){
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"qdmaQueueMap\" will be ignored. Configure" +
                " ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (!UTILS.compareArray(this.DMAN3.queueTCMap, defaultQueueTCMap)){
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"queueTCMap\" will be ignored. Configure" +
                " ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (!UTILS.compareArray(this.DMAN3.queuePri, defaultQueuePri)){
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"queuePri\" will be ignored. Configure" +
                " ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (!UTILS.compareArray(this.DMAN3.numTccGroup, defaultNumTccGroup)){
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"numTccGroup\" will be ignored. Configure" +
                " ti.sdo.fc.edma3.Settings module with appropriate values.");
        }
        if (!UTILS.compareArray(this.DMAN3.numPaRamGroup,defaultNumPaRamGroup)){
            print("Warning DMAN3.useExternalRM set to true, so configuration " +
                "parameter \"numPaRamGroup\" will be ignored. Configure" +
                " ti.sdo.fc.edma3.Settings module with appropriate values.");
        }

        /* If external RM is used, include low level Resource Manager module */ 
        xdc.useModule("ti.sdo.edma3.rm.RM");

        /* Needed to configure the low level resource manager module */ 
        xdc.useModule("ti.sdo.fc.edma3.Settings");
    }

    if (this.DMAN3.customDmaLib == undefined) {
        this.DMAN3.customDmaLib = false;
    }

    if (this.DMAN3.customDmaLib) {

        if (this.DMAN3.numQdmaGroup == undefined) {
            print("Warning, custom DMA library being used, but resources are "
                + " not partitioned across scratch groups. Qdma channels may be"
                + " shared among algorithms\n");

            this.DMAN3.customDmaLib = false; 
            this.DMAN3.numQdmaGroup = defaultNumQdmaGroup; 
        }
    }

    if (UTILS.arrayUndef(this.DMAN3.numQdmaGroup)) {
        this.DMAN3.numQdmaGroup = defaultNumQdmaGroup; 
    }

    if (this.profile.search("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }

    var osalPackage = xdc.useModule('ti.sdo.fc.global.Settings').osalPackage;

    if (osalPackage != undefined) {
        print("Loading osal package: " + osalPackage);
        xdc.loadPackage(osalPackage);
    }

    if (Program.build.target.os == undefined) {

        /* No OS, maybe it is bios */
        xdc.loadPackage("ti.bios");
    }

    if (Program.build.target.os == "Linux") { 
        /* To obtain the LockMP implementations etc */
        xdc.loadPackage("ti.sdo.fc.utils");
    }

    xdc.loadPackage("ti.xdais");
}

/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:25; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

