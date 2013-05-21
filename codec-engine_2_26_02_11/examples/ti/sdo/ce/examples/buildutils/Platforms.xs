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

/* Utility function to ensure a platform is only added to a targ array once */
function addUniquePlatform(targ, plat) {
    var found = false;

    for (var i = 0; i < targ.platforms.length; i++) {
        if (targ.platforms[i] == plat) {
            found = true;
            break;
        }
    }
    if (!found) {
        targ.platforms[targ.platforms.length++] = plat;
    }
}

function addGPPOS(thePlatform) {
    if (gppos.match(/LINUX_GCC/)) {
        if (thePlatform.match(/host\.platforms\.PC/)) {
            /* This is X86 Linux - not sure the special case plat is good... */
            Linux86 = xdc.useModule('gnu.targets.Linux86');
            addUniquePlatform(Linux86, thePlatform);
        } else {
            /* assume it's an ARM */
            GCArmv5T = xdc.useModule('gnu.targets.arm.GCArmv5T');
            addUniquePlatform(GCArmv5T, thePlatform);
        }
    }
    if (gppos.match(/LINUX_UCLIBC/)) {
        UCArm9 = xdc.useModule('gnu.targets.UCArm9');
        addUniquePlatform(UCArm9, thePlatform);
    }
    if (gppos.match(/WINCE/)) {
        WinCE = xdc.useModule('microsoft.targets.arm.WinCE');
        addUniquePlatform(WinCE, thePlatform);
    }
}

/*
 * Match all words and trim off leading and trailing white space,
 * then split on white space (any amount) between words.
 */
var deviceArray = devices.match(/^\s*(.*\w+)\s*$/)[1].split(/\s+/);

/*
 * The allDevices[] array maps the DEVICES macro set in xdcpaths.mak with
 * XDC platforms.
 */
var allDevices = new Array();
allDevices['DM6446']   = {platform: 'ti.platforms.evmDM6446',   GPP:true,  DSP:'C64P'};
allDevices['DM6467']   = {platform: 'ti.platforms.evmDM6467',   GPP:true,  DSP:'C64P'};
allDevices['DM6467T']   = {platform: 'ti.platforms.evmDM6467T', GPP:true,  DSP:'C64P'};
allDevices['DM6437']   = {platform: 'ti.platforms.evmDM6437',   GPP:false, DSP:'C64P'};
allDevices['DM648']    = {platform: 'ti.platforms.evmDM648',    GPP:false, DSP:'C64P'};
allDevices['DM355']    = {platform: 'ti.platforms.evmDM355',    GPP:true             };
allDevices['DM357']    = {platform: 'ti.platforms.evmDM357',    GPP:true             };
allDevices['DM365']    = {platform: 'ti.platforms.evmDM365',    GPP:true             };
allDevices['OMAP3530'] = {platform: 'ti.platforms.evm3530',     GPP:true,  DSP:'C64P'};
allDevices['OMAP2530'] = {platform: 'ti.platforms.evm2530',     GPP:true,  DSP:'C64P'};
allDevices['OMAPL137'] = {platform: 'ti.platforms.evmOMAPL137', GPP:true,  DSP:'C674'};
allDevices['OMAPL138'] = {platform: 'ti.platforms.evmOMAPL138', GPP:true,  DSP:'C674'};
allDevices['X86']      = {platform: 'host.platforms.PC',        GPP:true             };

for (var i in deviceArray) {
//    print("**** " + deviceArray[i]);
    if (allDevices[deviceArray[i]] != undefined) {
        if (allDevices[deviceArray[i]].GPP &&
                (allDevices[deviceArray[i]].DSP != undefined)) {
            /* GPP + DSP */
            if (programs.match(/APP_CLIENT/)) {
                /* client implies server - we only support 'clients' on the GPP */
                addGPPOS(allDevices[deviceArray[i]].platform);
            }
            if (programs.match(/DSP_SERVER/)) {
                /* Need to determine the ISA of the server */
                if (allDevices[deviceArray[i]].DSP == 'C64P') {
                    /* C64P - based servers */
                    C64P = xdc.useModule('ti.targets.C64P');
                    addUniquePlatform(C64P, allDevices[deviceArray[i]].platform);
                }
                else if (allDevices[deviceArray[i]].DSP == 'C674') {
                    /* C674 - based servers */
                    C674 = xdc.useModule('ti.targets.C674');
                    addUniquePlatform(C674, allDevices[deviceArray[i]].platform);
                }
                else {
                    throw('Unsupported DSP Server type (' +
                        allDevices[deviceArray[i]].DSP + ').  Only C64P and ' +
                        'C674 are currently supported.');
                }
            }
            if (programs.match(/APP_LOCAL/)) {
                /* Local apps build for both GPP and DSP */
                addGPPOS(allDevices[deviceArray[i]].platform);
                /* Need to determine the ISA of the server */
                if (allDevices[deviceArray[i]].DSP == 'C64P') {
                    /* C64P - based servers */
                    C64P = xdc.useModule('ti.targets.C64P');
                    addUniquePlatform(C64P, allDevices[deviceArray[i]].platform);
                }
                else if (allDevices[deviceArray[i]].DSP == 'C674') {
                    /* C674 - based servers */
                    C674 = xdc.useModule('ti.targets.C674');
                    addUniquePlatform(C674, allDevices[deviceArray[i]].platform);
                }
                else {
                    throw('Unsupported DSP Server type (' +
                        allDevices[deviceArray[i]].DSP + ').  Only C64P and ' +
                        'C674 are currently supported.');
                }
            }
        } else if ((allDevices[deviceArray[i]].GPP) &&
                (allDevices[deviceArray[i]].DSP == undefined)) {
            /* GPP-only device */
            if (programs.match(/APP_LOCAL/)) {
                /* Local apps build for GPP */
                addGPPOS(allDevices[deviceArray[i]].platform);
            }
        } else if ((allDevices[deviceArray[i]].GPP == false) &&
                (allDevices[deviceArray[i]].DSP != undefined)) {
            /* DSP-only device */
            if (programs.match(/APP_LOCAL/)) {
                /* Local apps build for DSP */
                /* Need to determine the ISA of the server */
                if (allDevices[deviceArray[i]].DSP == 'C64P') {
                    /* C64P - based servers */
                    C64P = xdc.useModule('ti.targets.C64P');
                    addUniquePlatform(C64P, allDevices[deviceArray[i]].platform);
                }
                else if (allDevices[deviceArray[i]].DSP == 'C674') {
                    /* C674 - based servers */
                    C674 = xdc.useModule('ti.targets.C674');
                    addUniquePlatform(C674, allDevices[deviceArray[i]].platform);
                }
                else {
                    throw('Unsupported DSP Server type (' +
                        allDevices[deviceArray[i]].DSP + ').  Only C64P and ' +
                        'C674 are currently supported.');
                }
            }
        } else {
            throw('Unsupported device configuration!  GPP+DSP, GPP-only, and' +
                    ' DSP-only are supported.');
        }
    } else {
        throw('Unsupported DEVICE "' + deviceArray[i] + '".  Please check ' +
            'the DEVICES macro set in xdcpaths.mak.');
    }
}
/*
 *  @(#) ti.sdo.ce.examples.buildutils; 1, 0, 0,256; 12-2-2010 21:21:30; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

