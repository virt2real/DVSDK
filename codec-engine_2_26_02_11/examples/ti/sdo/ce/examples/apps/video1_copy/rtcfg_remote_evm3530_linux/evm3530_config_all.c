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
 *  ======== evm3530_config.c ========
 *  Configuration for evm3530 Linux that rarely or never needs to be
 *  modified.
 *
 */

#include <xdc/std.h>


/* Configuration for interprocessor communication */

/* Size of the communication message */
UInt32 Comm_MSGSIZE = 4096;

/* Number of Comm_MSGSIZE-sized messages in the system */
UInt32 Comm_NUMMSGS = 64;

/* Configure the number of retries Comm_locate should do before giving up */
UInt32 Comm_LOCATERETRIES = 20;

/* Max timeout for MSGQ_get() allowed. */
UInt32 ti_sdo_ce_ipc_dsplink_Ipc_maxTimeout = 0xffffffff;


/*
 *  Arm-side DSPLINK configuration
 *  ==============================
 */
#include <ti/sdo/ce/osal/Global.h>

/* Arm-side DspLink configuration tables */

#if 1
/*
 *  Include a generated memory table from the server. This table can either
 *  be #include'd as in the statement below, or copied directly from the file:
 *      ti/sdo/ce/examples/servers/all_codecs/package/info/bin/
 *              ti_platforms_evm3530/all_x64P_memtab.c
 *  and pasted into this file. Choose one or the other method of
 *  including the memory map.
 */
#include <ti/sdo/ce/examples/servers/all_codecs/package/info/bin/ti_platforms_evm3530/all_x64P_memtab.c>

#else
/*
 *  Arm-side DspLink memory map for server "all.x64P":
 *  This table has been copied from
 *      ti/sdo/ce/examples/servers/all_codecs/package/info/bin/
 *              ti_platforms_evm3530/all_x64P_memtab.c
 *
 */
static Global_ArmDspLinkConfigMemTableEntry memTable_all_x64P[] = {
    { "DDR2",         0x87800000, 0x87800000, 0x00600000, 1, 0 },
    { "DSPLINKMEM",   0x87E00000, 0x87E00000, 0x00100000, 1, 0 },
    { "RESET_VECTOR", 0x87F00000, 0x87F00000, 0x00001000, 1, 0 },
    { "IVAMMU",       0x5D000000, 0x5D000000, 0x00001000, 0, 0 },
    { "L4PER",        0x49000000, 0x49000000, 0x00100000, 0, 0 },
    { "IRAM",         0x107F8000, 0x5C7F8000, 0x00008000, 1, 0 },
    { "L1DSRAM",      0x10F04000, 0x5CF04000, 0x0000C000, 1, 0 },
    { "DDRALGHEAP",   0x86000000, 0x86000000, 0x01800000, 0, 0 },
    { "L4CORE",       0x48000000, 0x48000000, 0x01000000, 0, 0 },
    { "CMEM",         0x00000000, 0x00000000, 0x00000000, 0, 0 },
    { NULL, 0, 0, 0, 0, 0 }
};
#endif

/*
 *  List of server names for all DspLink configuration tables.
 *  Change or add your server name[s] here.
 */
String ti_sdo_ce_ipc_armDspLinkConfigServerNames[] = {
    "all.x64P",
    NULL
};

/*
 *  Arm-side DspLink configuration table for server "all.x64P":
 */
static Global_ArmDspLinkConfig armDspLinkConfig_all_x64P = {
    memTable_all_x64P,
    BootNoPwr
};

/*
 *  List of matching-positions-by-name DspLink configuration tables for all
 *  servers.
 */
Global_ArmDspLinkConfig *ti_sdo_ce_ipc_armDspLinkConfigs[] = {
    &armDspLinkConfig_all_x64P,    /* all.x64P */
    NULL
};
/* end of arm-side DspLink configuration tables. */

/*
 *  Set to TRUE to use the Link Arbiter Daemon. LAD library must be linked
 *  in, if LAD is used.
 */
#define USE_LAD FALSE

/*
 * ======== ti.sdo.ce.osal.wince.Settings ========
 */
/*
 *  ======== Memory_maxCbListSize ========
 *  Maximum length of Contiguous Block List.
 *
 *  The maximum length of the contiguous block list
 *  used to speed up virtual-to-physical address translation of Arm
 *  buffer addresses.  The length indicates how many contiguous blocks
 *  are kept in the list, and was introduced to prevent performance
 *  degradation for applictions whose pattern of memory accesses made
 *  this list grow very large.  Most "regular" applications will not see
 *  a difference in performance with the introduction of this cut-off.
 *
 */
UInt32 Memory_maxCbListSize = 100;

/*
 * ======== ti.sdo.fc.global.Settings Configuration ========
 */
Bool ti_sdo_fc_multiProcess = TRUE;


/*
 *  ======== Global Configuration ========
 */
Bool Memory_skipVirtualAddressTranslation = FALSE;

/*
 *  =====================================================
 *  None of the code below should be modified (for Linux)
 *  =====================================================
 */

#if USE_LAD
Int Global_useLinkArbiter = TRUE;
#else

Int Global_useLinkArbiter = FALSE;

Int LAD_connect(String clientName, Int * id) { return 0; }
Int LAD_disconnect(Int id) { return 0; }
Int LAD_getDspStatus(Int cpuId, Int * statusInfo) { return 0; }
Int LAD_releaseDsp(Int id) { return 0; }
Int LAD_startupDsp(Int id, Int cpuId, Int linkId, String image) { return 0; }
#endif

/* Configuration parameters needed to avoid undefined references */
int PWRM_doImcopConfig = 0;
int PWRM_enableImcopAtPowerOn;

/*
 *  @(#) ti.sdo.ce.examples.apps.video1_copy; 1, 0, 0,264; 12-2-2010 21:21:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

