/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

/*
 *  ======== package.xs ========
 *
 */

var codecInterfaces = [
    "ti.sdo.ce.speech",
    "ti.sdo.ce.speech1",
    "ti.sdo.ce.audio",
    "ti.sdo.ce.audio1",
    "ti.sdo.ce.video",
    "ti.sdo.ce.video1",
    "ti.sdo.ce.video2",
    "ti.sdo.ce.image",
    "ti.sdo.ce.image1",
];

function init()
{
    /* Make sure link order is correct */
    for (i = 0; i < codecInterfaces.length; i++) {
        try {
            var ci = xdc.loadPackage(codecInterfaces[i]);
        }
        catch (e) {
            print("    package " + codecInterfaces[i] +
                  " not found, skipping..");
        }
    }
}

function getLibs(prog)
{
    var lib = null;
    var suffix;

    if ("findSuffix" in  prog.build.target) {
        var suffixes = ["470MV", "64P"];
        suffix = prog.build.target.findSuffix(suffixes);
    }
    else {
        /* Primitive compatiblity check for older XDC tools than 3.05 */
        if (prog.build.target.suffix == "470MV" ||
            prog.build.target.suffix == "v5t" ||
            prog.build.target.suffix == "v5T") {

            suffix = "470MV";
        } 
        else if (prog.build.target.suffix == "64P" ||
                 prog.build.target.suffix == "64" ||
                 prog.build.target.suffix == "62") {

            suffix = "64P";
        }
        else {
            suffix = "";
        }
    }

    if (suffix == "64P") {
        if (prog.cpu.deviceName == "TMS320CDM6446") {
            lib = "lib/dmai_bios_dm6446.a64P";
        }
        else if (prog.cpu.deviceName == "TMS320CDM6437") {
            lib = "lib/dmai_bios_dm6437.a64P";
        }
        else if (prog.cpu.deviceName == "TMS320CDM6467") {
            lib = "lib/dmai_bios_dm6467.a64P";
        }
        else {
            lib = "lib/dmai_bios_" + prog.cpu.deviceName + ".a470MV";
        }
    }
    else if (suffix == "470MV") {
        if (prog.cpu.deviceName == "TMS320CDM6446") {
            lib = "lib/dmai_linux_dm6446.a470MV";
        }
        else if (prog.cpu.deviceName == "TMS320CDM355") {
            lib = "lib/dmai_linux_dm355.a470MV";
        }
        else if (prog.cpu.deviceName == "TMS320CDM6467") {
            lib = "lib/dmai_linux_dm6467.a470MV";
        }
        else if (prog.cpu.deviceName == "OMAPL137") {
            lib = "lib/dmai_linux_omapl137.a470MV";
        }
        else if (prog.cpu.deviceName == "OMAP3530") {
            lib = "lib/dmai_linux_omap3530.a470MV";
        }
        else if (prog.cpu.deviceName == "TMS320DM357") {
            lib = "lib/dmai_linux_dm357.a470MV"
        }
        else if (prog.cpu.deviceName == "OMAPL138") {
            lib = "lib/dmai_linux_omapl138.a470MV"
        }
        else if (prog.cpu.deviceName == "TMS320DM365") {
            lib = "lib/dmai_linux_dm365.a470MV";
        }
        else {
            lib = "lib/dmai_linux_" + prog.cpu.deviceName + ".a470MV";
        }
    }

    print("    will link with " + this.$name + ":" + lib);

    return (lib);
}

