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
/*
 *  ======== validate ========
 */
function validate()
{
    /* TODO: validate the range of all the config params */
}

/*
 *  ======== getLibs ========
 */
function getLibs(prog)
{
    var suffix = Program.build.target.findSuffix(this);

    if (suffix == null) {
        return (null);
    }

    var lib = "grouputils" ;
    lib += ".a" + suffix;

    var dir = "lib/" + this.profile;

    if (!java.io.File(this.packageBase + dir + "/" + lib ).exists()) {

        print(this.$name + ": Requested profile '" + this.profile + "' does"
                    + " not exist.\n\tDefaulting to the 'release' profile");

        dir = "lib/release";
 
    } 

    print("    will link with " + this.$name + ":" + dir + "/" + lib);
    return (dir + "/" + lib);
}

/*
 *  ======== getSects ========
 */
function getSects() {
   return (null);
}


function close() {
    xdc.loadPackage("ti.sdo.fc.ires");


    if ((null == this.GROUPUTILS.lockScratchGroupFxn) ||
            (null == this.GROUPUTILS.unlockScratchGroupFxn)) {

        /* Not doing anything for now, these are optional, complain later
           if these are being used */

    } else {

        /* Load the package that implements release/reacquire fxn*/   
        if (this.GROUPUTILS.scratchFxnPackage) {
            xdc.loadPackage(this.GROUPUTILS.scratchFxnPackage);
        }
        else {
            /* Complain as no one set the package */
            throw("\n\nGROUPUTILS ERROR: Please configure " +
                    "GROUPUTILS.scratchFxnPackage to the package that " +
                    "implements the lockScratchGroupFxn and " +
                    "unlockScratchGroupFxn");
        }
    }

    var FC = xdc.useModule("ti.sdo.fc.global.Settings");

    if ((null == this.GROUPUTILS.semCreateFxn) ||
            (null == this.GROUPUTILS.semDeleteFxn) ||
            (null == this.GROUPUTILS.semPendFxn) ||
            (null == this.GROUPUTILS.semPostFxn)) {

        /* Use RMAN to provide sem settings if no one configured them */
        RMAN = xdc.useModule('ti.sdo.fc.rman.RMAN');
        this.GROUPUTILS.semCreateFxn = RMAN.semCreateFxn;
        this.GROUPUTILS.semDeleteFxn= RMAN.semDeleteFxn;
        this.GROUPUTILS.semPendFxn = RMAN.semPendFxn;
        this.GROUPUTILS.semPostFxn= RMAN.semPostFxn;

        if ((this.GROUPUTILS.semCreateFxn == null) || 
                (this.GROUPUTILS.semDeleteFxn == null) || 
                (this.GROUPUTILS.semPendFxn == null)  ||
                (this.GROUPUTILS.semPostFxn == null)) {

            /* If still NULL, check the osalPackage setting */
            if (( FC.osalPackage != null )) {

                /* If osalPackage is configured, then it can be used */
                xdc.loadPackage(FC.osalPackage);

                if (Program.build.target.os == "Linux") {
                    this.GROUPUTILS.semCreateFxn = "SemMP_create";
                    this.GROUPUTILS.semDeleteFxn= "SemMP_delete";
                    this.GROUPUTILS.semPendFxn = "SemMP_pend";
                    this.GROUPUTILS.semPostFxn= "SemMP_post";
                }
                else {
                    this.GROUPUTILS.semCreateFxn = "Sem_create";
                    this.GROUPUTILS.semDeleteFxn= "Sem_delete";
                    this.GROUPUTILS.semPendFxn = "Sem_pend";
                    this.GROUPUTILS.semPostFxn= "Sem_post";
                }
            }
            else {
                throw("\n\nGROUPUTILS ERROR: Please configure GROUPUTILS" +
                        ".sem*Fxn correctly or set the FC.osalPackage to " +
                        "the package that implements the OSAL");
            }
        }
    }
}
/*
 *  @(#) ti.sdo.fc.ires.grouputils; 1, 0, 0,32; 12-1-2010 17:25:14; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

