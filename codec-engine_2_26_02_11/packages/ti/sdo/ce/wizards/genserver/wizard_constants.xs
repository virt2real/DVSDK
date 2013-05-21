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
var wizardVersion = "2.26.00";
var DEFAULT_STACKSIZE = '<use codec defaults>';

var INIT_MESSAGE = "Codec Engine GenServer Wizard v" + wizardVersion
    + "\nTexas Instruments";

var FAQ_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenServer_Wizard_FAQ';
var BASIC_INFO_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenServer_Wizard_FAQ#Basic_Server_Information';
var ALG_VALS_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenServer_Wizard_FAQ#Server.algs_Array_Values';
var GROUP_IDS_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GroupIds';
var DSKT2_MEM_LINK = 'http://processors.wiki.ti.com/index.php/Memory_management_in_XDAIS_with_DSKT2';
var MEMMAP_LINK = 'http://processors.wiki.ti.com/index.php/Codec_Engine_GenServer_Wizard_FAQ#Memory_Map';

var ABOUT_MESSAGE = INIT_MESSAGE;

var VIDEO_GROUPID = 0;
var IMAGING_GROUPID = 1; 
var AUDIO_SPEECH_GROUPID = 2;

var ENTER_CGTOOLS = '<C6000 TI codegen tools directory>';
var ENTER_OUTREPO = '<Server destination directory>';

var CGTOOLS_DESC = 'Your TI C6000 codegen tools directory, e.g.\n' +
'"C:/Program Files/Texas Instruments/ccsv4/tools/compiler/c6000"';

var CODECS_DESC = 
      "These are the names of the codec modules you wish to create the Server for";

var SEARCH_DESC = 
    "Look on the search path for modules that inherit ti.sdo.ce.ICodec";


var SEARCH_PATH_DESC =
    "The path to search for codecs and for libraries used to build the Server";

var SCRATCH_HOVER = 'Worst case scratch sizes for the selected group';

/* selection specific hover? */
var USE_EDMA3_HOVER = 'When checked, EDMA3 LLD will manage all EDMA3 resources. When\n'+
                      'unchecked, DMAN3 will manage EDMA3 resources. This selection\n'+
                      'can only be modified when no algorithms implement IRES_Fxns.';

var DMAN3_CHANNELS = 
'Channels created with the currently selected group will\n'+
'use TCCs and Params allocated for that group, and may\n'+
'share them with other channels created with the same group ID.';

var DMAN3_TCC_HOVER =
'The number of TCCs that will be assigned to the currently selected\n'+
'group for sharing.\n'+ DMAN3_CHANNELS;

var DMAN3_PARAM_HOVER =
'The number of Param entries that will be assigned to the currently\n'+
'selected group for sharing.\n'+ DMAN3_CHANNELS;

var EDMA3_GROUPS =
'Algorithms created within the currently selected group\n'+
'will share the EDMA3 resources assigned to that group.';

var EDMA3_MAXTCC_HOVER =
'The maximum number of TCCs that will be assigned to the\n'+
'currently selected group for sharing.\n'+ EDMA3_GROUPS;

var EDMA3_MAXPARAM_HOVER =
'The maximum number of Params that will be assigned to the\n'+
'currently selected group for sharing.\n'+ EDMA3_GROUPS;

var EDMA3_MAXEDMACHANS_HOVER =
"The maximum number of Edma Channels that will be  assigned\n"+
"to the currently selected group for sharing.\n"+ EDMA3_GROUPS + "\n" +
"On devices where DCHMAP doesn't exist, it is recommended to\n"+
"request as many channels as Params requested. This is only\n"+
"required for groups with IRES-based codecs";

var EDMA3_MAXQDMACHANS_HOVER =
'The maximum number of Qdma Channels that will be  assigned\n'+
'to the currently selected group for sharing.\n'+ EDMA3_GROUPS;

var ENABLE_POWER_HOVER =
'Check to enable DSP power management on omap3530 and DM6446x platforms.\n'+
'When selected, the Local Power Manager install directory must be in the Search Path';

/*
 *  @(#) ti.sdo.ce.wizards.genserver; 1, 0, 0,84; 12-2-2010 21:28:48; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

