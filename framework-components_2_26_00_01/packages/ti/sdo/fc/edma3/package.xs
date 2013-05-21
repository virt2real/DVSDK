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
/*
 * ======== package.xs ========
 */
var UTILS = xdc.loadCapsule('ti/sdo/fc/utils/utils.xs');

/*
 * This var has scope of this file.  It's set in close() and used in
 * validate().
 */
var RMAN;

/*
 *  ======== close ========
 */
function close()
{
    var isa = Program.build.target.isa;

    /* To get the iresman header */
    xdc.loadPackage("ti.sdo.fc.ires");

    if ((this.Settings.debug) || (this.Settings.trace)) {
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

    if (this.profile.match("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }

    var FC = xdc.useModule("ti.sdo.fc.global.Settings");

    if ((null == this.Settings.semCreateFxn) ||
            (null == this.Settings.semDeleteFxn) ||
            (null == this.Settings.semPendFxn) ||
            (null == this.Settings.semPostFxn)) {

        /* Use RMAN to provide sem settings if no one configured them */
        //if (UTILS.usingPackage("ti.sdo.fc.rman")) {
        RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');
        this.Settings.semCreateFxn = RMAN.semCreateFxn;
        this.Settings.semDeleteFxn= RMAN.semDeleteFxn;
        this.Settings.semPendFxn = RMAN.semPendFxn;
        this.Settings.semPostFxn= RMAN.semPostFxn;
        //}

        if ((this.Settings.semCreateFxn == null) || 
                (this.Settings.semDeleteFxn == null) || 
                (this.Settings.semPendFxn == null)  ||
                (this.Settings.semPostFxn == null)) {

            if ( FC.osalPackage != null ) { 

                /* If osalPackage is configured, then it can be used */
                xdc.loadPackage(FC.osalPackage);

                if (Program.build.target.os == "Linux") {
                    this.Settings.semCreateFxn = "SemMP_create";
                    this.Settings.semDeleteFxn= "SemMP_delete";
                    this.Settings.semPendFxn = "SemMP_pend";
                    this.Settings.semPostFxn= "SemMP_post";
                }
                else {
                    this.Settings.semCreateFxn = "Sem_create";
                    this.Settings.semDeleteFxn= "Sem_delete";
                    this.Settings.semPendFxn = "Sem_pend";
                    this.Settings.semPostFxn= "Sem_post";
                }
            }
            else {
                print("EDMA3:- Semaphores not configured\n");
            }
        }
    }

    if ((null == this.Settings.persistentAllocFxn) ||
            (null == this.Settings.persistentFreeFxn)) {

        if (UTILS.usingPackage("ti.sdo.fc.rman")) {

            RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');
            if (RMAN.useDSKT2 == true) {
    
                //Check if the target is C64, DSKT2 works only for that !
                if ((isa != "64P") && (isa != "674")) {
    
                    //Not DSP, well are the alloc/free Fxns set properly ?! 
                    if ((RMAN.persistentAllocFxn == "null") || 
                            (RMAN.persistentFreeFxn == "null")) {

                        //Nope, not set, error !
                        throw("\n\n  RMAN Error: Config parameter useDSKT2 set "
                            + "to true for a non-DSP target. Please set this to"
                            + " false and configure RMAN.persistentAllocFxn and"
                            + " RMAN.persistentFreeFxn instead.");
                    }
                    else {
                        //Set, print warning and proceed 
                        print("Warning - RMAN.useDSKT2 was set to true for a " +
                            "non-DSP target, this will be set to FALSE and " +
                            "RMAN.persistentAllocFxn and persistentFreeFxn "
                            + "will be used instead."); 
    
                        RMAN.useDSKT2 = false;
                    }
                }
            }
    
            if (RMAN.useDSKT2 == true) {
    
               this.Settings.persistentAllocFxn = "DSKT2_allocPersistent";
               this.Settings.persistentFreeFxn = "DSKT2_freePersistent";
    
               /* RMAN should already have done this, but... */
               xdc.useModule("ti.sdo.fc.dskt2.DSKT2");
            }
            else {
               this.Settings.persistentAllocFxn = RMAN.persistentAllocFxn;
               this.Settings.persistentFreeFxn = RMAN.persistentFreeFxn;
            }
         }
    }

    var isa = Program.build.target.isa;
    var dsp;

    if ( isa.match(/64P/) || isa.match(/674/) || isa.match(/64T/)) {
        dsp = true;
    }
    else {
        dsp = false;
    }

    if (dsp) {

        xdc.useModule("ti.sdo.edma3.rm.RM");
    }

    var os = Program.build.target.os;
    if (dsp) {
        
        xdc.loadPackage("ti.bios");

        /* Load low-level Resource manager */
        var RM = xdc.useModule('ti.sdo.edma3.rm.RM');

        if (UTILS.usingPackage("ti.sdo.fc.rman")) {
            RM.edma3_max_rm_instances = RMAN.maxAlgs;
        }
        else {
            RM.edma3_max_rm_instances = this.Settings.maxAlgs;
        }
    }
    else {

        /* ARM */

        xdc.loadPackage("ti.sdo.fc.memutils");

        if (os == "Linux") {
        
            /* Load linuxutils resource management support */
            xdc.loadPackage('ti.sdo.linuxutils.edma');

            /* Need this for shared memory APIs */
            xdc.loadPackage('ti.sdo.fc.utils');
        }
    }

    var defaultTccs = [10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;
    var defaultPaRams = [20,20,20,20,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;
    var defaultEdma = [4,4,4,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;
    var defaultQdma = [1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];;

    /* Check if the deprecated configuration parameters are being used by
        comparing their values with the defaults */

    if (this.Settings.Region != 1) {

        print("Warning Deprecated configuration parameter \"Region\" being used"
            + ". Use parameter \"region\" to set the EDMA3 region number to be"
            + " configured\n");

        if (this.Settings.region != 1) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"Region\" as well as new parameter \"region\"  being used"
            + "to configure the EDMA3 module. Please reconfigure using new "
            + "parameter \"region\" only.");
        }
        else {
            this.Settings.region = this.Settings.Region;
        }
    }

    if (this.Settings.GlobalInit != false) {

        print("Warning Deprecated configuration parameter \"GlobalInit\" being "
            + "used. Use parameter \"globalInit\" to set the Global "
            + "initialization property\n");

        if (this.Settings.globalInit != false) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"GlobalInit\" as well as new parameter \"globalInit\"  being "
            + "used to configure the EDMA3 module. Please reconfigure using "
            + "parameter \"globalInit\" only.");
        }
        else {
            this.Settings.globalInit = this.Settings.GlobalInit;
        }
    }

    if (this.Settings.RegionConfig != null) {

        print("Warning Deprecated configuration parameter \"RegionConfig\" "
            + "being used. Use parameter \"regionConfig\" to set the Global "
            + "initialization property\n");

        if (this.Settings.regionConfig != null) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"RegionConfig\" as well as new parameter \"regionConfig\" "
            + "being used to configure the EDMA3 module. Please reconfigure "
            + "using parameter \"regionConfig\" only.");
        }
        else {
            this.Settings.regionConfig = this.Settings.RegionConfig;
        }
    }

    if (this.Settings.GlobalConfig != null) {

        print("Warning Deprecated configuration parameter \"GlobalConfig\" "
            + "being used. Use parameter \"globalConfig\" to set the Global "
            + "initialization property\n");

        if (this.Settings.globalConfig != null) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"GlobalConfig\" as well as new parameter \"globalConfig\" "
            + "used used to configure the EDMA3 module. Please reconfigure "
            + "using parameter \"globalConfig\" only.");
        }
        else {
            this.Settings.globalConfig = this.Settings.GlobalConfig;
        }
    }

    if (this.Settings.ContiguousPaRams != true) {

        print("Warning Deprecated configuration parameter \"ContiguousPaRams\" "
            + "being used. Use parameter \"contiguousPaRams\" to set the EDMA3 "
            + "region number to be configured\n");

        if (this.Settings.contiguousPaRams != true) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"ContiguousPaRams\" as well as new parameter "
            + "\"contiguousPaRams\"  being used to configure the EDMA3 module. "
            + "Please reconfigure using parameter \"contiguousPaRams\" only.");
        }
        else {
            this.Settings.contiguousPaRams = this.Settings.ContiguousPaRams;
        }
    }

    if (!(UTILS.compareArray(this.Settings.MaxTccs, defaultTccs))) {

        print("Warning Deprecated configuration parameter \"MaxTccs\" being "
            + "used. Use parameter \"maxTccs\" to configure the Tcc "
            + "distribution for the scratch groups.\n");

        if (!arrayUndef(this.Settings.maxTccs)) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"MaxTccs\" as well as new parameter \"maxTccs\"  being "
            + "used to configure the EDMA3 module. Please reconfigure using "
            + "parameter \"maxTccs\" only.");
        }
        else {
            this.Settings.maxTccs = this.Settings.MaxTccs;
        }
    }

    if (!(UTILS.compareArray(this.Settings.MaxPaRams, defaultPaRams))) {

        print("Warning Deprecated configuration parameter \"MaxPaRams\" being "
            + "used. Use parameter \"maxPaRams\" to configure the PaRams "
            + "distribution for the scratch groups.\n");

        if (!(arrayUndef(this.Settings.maxPaRams))) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"MaxPaRams\" as well as new parameter \"maxPaRams\"  being "
            + "used to configure the EDMA3 module. Please reconfigure using "
            + "parameter \"maxPaRams\" only.");
        }
        else {
            this.Settings.maxPaRams = this.Settings.MaxPaRams;
        }
    }

    if (!(UTILS.compareArray(this.Settings.MaxEdmaChannels, defaultEdma))) {

        print("Warning Deprecated configuration parameter \"MaxEdmaChannels\" "
            + "being used. Use parameter \"maxEdmaChannels\" to configure the "
            + "Edma Channel distribution for the scratch groups.\n");

        if (!arrayUndef(this.Settings.maxEdmaChannels)) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"MaxEdmaChannels\" as well as new parameter \"maxEdmaChannels\""
            + "being used to configure the EDMA3 module. Please reconfigure "
            + "using parameter \"maxEdmaChannels\" only.");
        }
        else {
            this.Settings.maxEdmaChannels = this.Settings.MaxEdmaChannels;
        }
    }

    if (!(UTILS.compareArray(this.Settings.MaxQdmaChannels, defaultQdma))) {

        print("Warning Deprecated configuration parameter \"MaxQdmaChannels\" "
            + "being used. Use parameter \"maxQdmaChannels\" to configure the "
            + "Qdma Channel distribution for the scratch groups.\n");

        if (!arrayUndef(this.Settings.maxQdmaChannels)) {
            throw("\n\n EDMA3 Error: Deprecated configuration parameter "
            + "\"MaxQdmaChannels\" as well as new parameter \"maxQdmaChannels\""
            + " being used to configure the EDMA3 module. Please reconfigure "
            + "using parameter \"maxQdmaChannels\" only.");
        }
        else {
            this.Settings.maxQdmaChannels = this.Settings.MaxQdmaChannels;
        }
    }

    if (this.Settings.maxEdmaChannels.length > this.Settings.EDMA3_MAXGROUPS) {
       throw("\n\n  EDMA3 Error: Config parameter maxEdmaChannels set to more "
            + "values than the number of groups. Please reduce size of array.");
    }

    if (this.Settings.maxQdmaChannels.length > this.Settings.EDMA3_MAXGROUPS) {
       throw("\n\n  EDMA3 Error: Config parameter maxQdmaChannels array has "
            + "more values than the number of groups. Please reduce size of "
            + "array.");
    }

    if (this.Settings.maxTccs.length > this.Settings.EDMA3_MAXGROUPS) {
       throw("\n\n  EDMA3 Error: Config parameter maxTccs has more values than "
        + "the number of groups. Please reduce size of array.");
    }

    if (this.Settings.maxPaRams.length > this.Settings.EDMA3_MAXGROUPS) {
       throw("\n\n  EDMA3 Error: Config parameter maxPaRams has more values "
        + "than the number of groups. Please reduce size of array.");
    }

    if (dsp == false) {
        /* Make sure no unncessary configuration has been done for non-dsp
           targets */
        if (this.Settings.region != 1) {
            print("Warning configuration parameter \"region\" being used. "
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (this.Settings.globalInit != false) {
            print("Warning configuration parameter \"globalInit\" being used. "
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (this.Settings.regionConfig != null) {
            print("Warning configuration parameter \"regionConfig\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (this.Settings.globalConfig != null) {
            print("Warning configuration parameter \"globalConfig\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (!arrayUndef(this.Settings.maxTccs)) {
            print("Warning configuration parameter \"maxTccs\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (!(arrayUndef(this.Settings.maxPaRams))) {
            print("Warning configuration parameter \"maxPaRams\" being used."
                    + "This parameter is not applicable for non-DSP targets."
                    + "Will be ignored by this module.");
        }
        if (!arrayUndef(this.Settings.maxEdmaChannels)) {
            print("Warning configuration parameter \"maxEdmaChannels\" being "
                    + "used. This parameter is not applicable for non-DSP "
                    + "targets. Will be ignored by this module.");
        }
        if (!arrayUndef(this.Settings.maxQdmaChannels)) {
            print("Warning configuration parameter \"maxQdmaChannels\" being "
                    + "used. This parameter is not applicable for non-DSP "
                    + "targets. Will be ignored by this module.");
        }
    }
}

/*
 *  ======== validate ========
 */
function validate()
{
    var suffix = Program.build.target.findSuffix(this);
    var dsp = (((suffix == "64P") || (suffix == "674")) ? true : false);
    var os = Program.build.target.os;

    if (dsp) {

        /* Validate config settings here */
        if (this.Settings.semCreateFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semCreateFxn.");
        }

        if (this.Settings.semDeleteFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semDeleteFxn.");
        }

        if (this.Settings.semPendFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semPendFxn.");
        }

        if (this.Settings.semPostFxn == null) {
            throw("\n\n: EDMA3 error : Configure valid semPostFxn.");
        }
    }

    if (this.Settings.persistentAllocFxn == null) {
        throw("\n\n: EDMA3 error : Configure valid persistentAllocFxn.");
    }

    if (this.Settings.persistentFreeFxn == null) {
        throw("\n\n: EDMA3 error : Configure valid persistentFreeFxn.");
    }
}

function arrayUndef(Array1)
{
    var status = true;
    for (i =0 ; i < Array1.length; i++) {
        if (undefined != Array1[i]) {
            return false;
        }
    }
    return status;
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


    var device = Program.cpu.deviceName;
    var isa = Program.build.target.isa;

    /* For Arm devices, this package is available only for DM355 and DM365 */
    if (prog.cpu.attrs.cpuCore == "v7A") {
        if (!(device.match("DM355") || (device.match("DM365")))) {
            return (null);
        }
    }

    /* Supported for all DSP devices */

    var libs = "edma3.a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libs).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                    + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    } 

    print("    will link with " + this.$name + ":" + dir + "/" + libs);

    return (dir + "/" + libs);
}

/*
 *  @(#) ti.sdo.fc.edma3; 3, 0, 0,152; 12-1-2010 17:24:42; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

