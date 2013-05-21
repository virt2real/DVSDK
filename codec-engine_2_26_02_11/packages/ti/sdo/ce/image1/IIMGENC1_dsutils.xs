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
 * ======== IIMGENC1_dsutils.xs ========
 * Utility Capsule for contributing IIMGENC1-specific details into a
 * Server data sheet.
 */
function genHTMLRow(mod) {
    var resultString = "";
    var cfgs;

    var configs = mod.$spec.getConfigs().toArray();
    resultString = '<tr><td valign="top" width="220">\n' +
                   '<a href="http://tiexpressdsp.com/index.php/' +
                   'Codec_Engine_Overhead">Cache Optimizations</a></td>\n'+
                   '<td valign="top">' +
                   '<table border="1" cellpadding="2" cellspacing="0">' +
                   '<tbody>\n';

    for each (cfgs in configs) {
        if (cfgs.getName() == "manageInBufsCache") {
            resultString += '<tr><td valign="top" width="105">' +
                    'manageInBufsCache[16]</td>\n' +
                    '<td valign="top">[';

            for (var cacheIndex = 0; cacheIndex < 16; cacheIndex++) {
                resultString += cfgs.getInit().getElems().toArray()[cacheIndex].getVal() + ', ';
            }

            resultString += ']</td>\n</tr>';
        }
    }
    for each (cfgs in configs) {
        if (cfgs.getName() == "manageOutBufsCache") {
            resultString += '<tr><td valign="top" width="105">' +
                    'manageOutBufsCache[16]</td>\n' +
                    '<td valign="top">[';

            for (var cacheIndex = 0; cacheIndex < 16; cacheIndex++) {
                resultString += cfgs.getInit().getElems().toArray()[cacheIndex].getVal() + ', ';
            }

            resultString += ']</td>\n</tr>';
        }
    }

    resultString += '</tbody></table><br></td></tr>';

    return (resultString);
}
/*
 *  @(#) ti.sdo.ce.image1; 1, 0, 1,276; 12-2-2010 21:24:03; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

