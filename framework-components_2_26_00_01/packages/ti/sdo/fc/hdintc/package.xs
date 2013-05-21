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
 *  ======== validate ========
 */
function validate()
{
   var status = 0;

   /* TODO: validate the range of all the config params */
   if (this.HDINTC.interruptVectorId_0 == undefined) {
       /*
        * ERROR. Interrupt select line must be assigned in HDINTC config
        * to an unused interrupt line.
        */
       print("ERROR: Undefined HDINTC::interruptVectorId_0 !!!" +
               " Application must configure HDINTC::interruptVectorId_0" +
               " by selecting an unused interrupt vector id that will be " +
               " used by HDINTC to service HDVICP processor:0 interrupts." +
               " The valid range is between: 5-13." );
       status = 1;
    }
    else if ((this.HDINTC.interruptVectorId_0 < 5)   ||
               (this.HDINTC.interruptVectorId_0 == 14) ||
               (this.HDINTC.interruptVectorId_0 > 15)) {
           /* failed the range check */
           print("ERROR: HDINTC::interruptVectorId_0 => " +
               this.HDINTC.interruptVectorId_0 + " is Out of Range!\n" +
               " Application must configure HDINTC::interruptVectorId_0" +
               " by selecting an unused interrupt vector id that will be " +
               " used by HDINTC to service HDVICP processor:0 interrupts." +
               " The valid range is between: {5-13, 15}." );
           status = 1;
    }

   if (this.HDINTC.interruptVectorId_1 == undefined) {
       /*
        * ERROR. Interrupt select line must be assigned in HDINTC config
        * to an unused interrupt line.
        */
       print("ERROR: Undefined HDINTC::interruptVectorId_1 !!!"  +
               " Application must configure HDINTC::interruptVectorId_1" +
               " by selecting an unused interrupt vector id that will be " +
               " used by HDINTC to service HDVICP processor:1 interrupts." +
               " The valid range is between: 5-13." );
       status = 1;
    }
    else if ((this.HDINTC.interruptVectorId_1 < 5)   ||
               (this.HDINTC.interruptVectorId_1 == 14) ||
               (this.HDINTC.interruptVectorId_1 > 15)) {
           /* failed the range check */
           print("ERROR: HDINTC::interruptVectorId_1 => " +
               this.HDINTC.interruptVectorId_1 + " is Out of Range!\n" +
               " Application must configure HDINTC::interruptVectorId_1" +
               " by selecting an unused interrupt vector id that will be " +
               " used by HDINTC to service HDVICP processor:1 interrupts." +
               " The valid range is between: {5-13, 15}." );
           status = 1;
    }

    if (this.HDINTC.hdvicpInterruptEventNo_0 == undefined) {
        print("ERROR: Undefined HDINTC::hdvicpInterruptEventNo_0. " +
               " Interrupt Event Number must be assigned in HDINTC config to" +
               " match the physical event-id associated with the HDVICP" +
               " processor:1 interrupts that need to be serviced by GEM, via " +
               " the interrupt line selected by 'interruptVectorId_0'." +
               " On DM6467 this Event Id is 29." );
        status = 1;
    }
    else if (this.HDINTC.hdvicpInterruptEventNo_0 != 29) {
        print("WARNING: HDINTC::hdvicpInterruptEventNo_0 is set to: <" +
               this.HDINTC.hdvicpInterruptEventNo_0 +
               " On DM6467 this Event Id must be set to 29." );
    }

    if (this.HDINTC.hdvicpInterruptEventNo_1 == undefined) {
        print("ERROR: Undefined HDINTC::hdvicpInterruptEventNo_1. " +
               " Interrupt Event Number must be assigned in HDINTC config to" +
               " match the physical event-id associated with the HDVICP" +
               " processor:1 interrupts that need to be serviced by GEM, via " +
               " the interrupt line selected by 'interruptVectorId_1'." +
               " On DM6467 this Event Id is 39." );
        status = 1;
    }
    else if (this.HDINTC.hdvicpInterruptEventNo_1 != 39) {
        print("WARNING: HDINTC::hdvicpInterruptEventNo_1 is set to: <" +
               this.HDINTC.hdvicpInterruptEventNo_1 +
               " On DM6467 this Event Id must be set to 39." );
    }

    if (status == 1) {
        throw new Error("ERROR configuring HDINTC!");
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

    if (this.HDINTC.spinloop) {
        var libs = "hdintc_spinloop_fc"
    }
    else {
        var libs = "hdintc_fc";
    }

    libs += ".a" +  suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + libs ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                    + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
    }

    print("    will link with " + this.$name + ":" + dir + "/" + libs);
    return (dir + "/" + libs);
}


/*
 * ======== close ========
 */
function close() {

    /* This module is for DSP/BIOS only */
    xdc.loadPackage("ti.bios");

    xdc.loadPackage("ti.xdais");

    xdc.useModule("ti.sdo.fc.ires.hdvicp.HDVICP");

    if ((this.HDINTC.debug) || (this.HDINTC.trace)) {
        print(this + ": This module no longer supports the .debug "
                + "or the .trace config params. Set desired profile for all "
                + "FC modules as follows: "
                + "xdc.useModule\('ti.sdo.fc.global.Settings'\).profile = "
                + "\"debug\""
                + " or set profiles for individual packages like this: "
                + "xdc.loadPackage('"
                + this + "').profile = \"debug\"\;"
                + " .\n\tWill default to the 'release' if profile not set");
    }

    if (this.profile == undefined) {
        this.profile = xdc.useModule('ti.sdo.fc.global.Settings').profile;
    }

    /* conditionally introduce trace dependency */
    if (this.profile.match("trace")) {
        xdc.useModule("ti.sdo.utils.trace.GT");
    }

    if (this.HDINTC.biosInterruptEventNo_1 == undefined) {
        print("Warning: Undefined HDINTC::biosInterruptEventNo_1. " +
               "An unused interrupt Event Number must be assigned in HDINTC " +
               "config to be used as the BIOS ISR interrupt line. Using " +
               "event number 31. If this event Id is already in use, please " +
               "re-configure with a suitable Event number.");

        this.HDINTC.biosInterruptEventNo_1 = 31;
    }

    if (this.HDINTC.biosInterruptEventNo_0 == undefined) {
        print("Warning: Undefined HDINTC::biosInterruptEventNo_0. " +
               "An unused interrupt Event Number must be assigned in HDINTC " +
               "config to be used as the BIOS ISR interrupt line. Using " +
               "event number 30. If this event Id is already in use, please " +
               "re-configure with a suitable Event number.");

        this.HDINTC.biosInterruptEventNo_0 = 30;
    }

    if (this.HDINTC.biosInterruptVectorId_0 == undefined) {
        print("Warning: Undefined HDINTC::biosInterruptVectorId_0. " +
               "An unused interrupt Event Number must be assigned in HDINTC " +
               "config to be used as the BIOS ISR interrupt line. Using " +
               "interrupt line 7. If this line is already in use, please " +
               "re-configure with a suitable Event number.");

        this.HDINTC.biosInterruptVectorId_0 = 7;
    }

    if (this.HDINTC.biosInterruptVectorId_1 == undefined) {
        print("Warning: Undefined HDINTC::biosInterruptVectorId_1. " +
               "An unused interrupt Event Number must be assigned in HDINTC " +
               "config to be used as the BIOS ISR interrupt line. Using " +
               "interrupt line 8. If this line is already in use, please " +
               "re-configure with a suitable Event number.");

        this.HDINTC.biosInterruptVectorId_1 = 8;
    }
}
/*
 *  @(#) ti.sdo.fc.hdintc; 1, 0, 4,133; 12-1-2010 17:24:49; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

