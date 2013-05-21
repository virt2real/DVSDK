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

/*!
 *  ======== DspLinkCfg ========
 *  Dsplink ipc Settings.
 */

metaonly module DspLinkCfg inherits ti.sdo.ce.ipc.dsplink.IDspLinkCfg {

  /*
   * The DEFAULT_ARMDSPLINKCONFIG[] table is here mostly for backward
   * compatibility purposes.  The current recommended approach for creating
   * an 'ArmDspLinkConfig' is to simply use Engine.createFromServer(), which
   * creates and populates an 'ArmDspLinkConfig' object based on the server's
   * memory map for 'memTable' and default values for other fields.
   *
   * When Engine.createFromServer() is used, this table becomes unused.
   */
  override readonly config ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig
        DEFAULT_ARMDSPLINKCONFIG[string] = [

    /* DM6446, 256 MB of external memory */
    ["TMS320CDM6446",
    {
        memTable: [
           ["DDRALGHEAP", {addr: 0x88000000, size: 0x07A00000, type: "other"}],
           ["DDR2",       {addr: 0x8FA00000, size: 0x00400000, type: "main" }],
           ["DSPLINKMEM", {addr: 0x8FE00000, size: 0x00100000, type: "link" }],
           ["RESETCTRL",  {addr: 0x8FF00000, size: 0x00000080, type: "reset"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* DM357, 256 MB of external memory */
    ["TMS320DM357",
    {
        memTable: [
           ["DDRALGHEAP", {addr: 0x88000000, size: 0x07A00000, type: "other"}],
           ["DDR2",       {addr: 0x8FA00000, size: 0x00400000, type: "main" }],
           ["DSPLINKMEM", {addr: 0x8FE00000, size: 0x00100000, type: "link" }],
           ["RESETCTRL",  {addr: 0x8FF00000, size: 0x00000080, type: "reset"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* DM6467, 256 MB of external memory */
    ["TMS320CDM6467",
    {
        memTable: [
           ["DDRALGHEAP", {addr: 0x88000000, size: 0x07A00000, type: "other"}],
           ["DDR2",       {addr: 0x8FA00000, size: 0x00400000, type: "main" }],
           ["DSPLINKMEM", {addr: 0x8FE00000, size: 0x00100000, type: "link" }],
           ["RESETCTRL",  {addr: 0x8FF00000, size: 0x00000080, type: "reset"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* OMAP3430, 128 MB of external memory */
    ["TMS320C3430",
    {
        memTable: [
            ["L4CORE",     {addr: 0x48000000, size: 0x01000000, type: "other"}],
            ["L4PER",      {addr: 0x49000000, size: 0x00100000, type: "other"}],
            ["CMEM",       {addr: 0x85000000, size: 0x01000000, type: "other"}],
            ["DDRALGHEAP", {addr: 0x86000000, size: 0x01800000, type: "other"}],
            ["DDR2",       {addr: 0x87800000, size: 0x00600000, type: "main" }],
            ["DSPLINKMEM", {addr: 0x87E00000, size: 0x00100000, type: "link" }],
            ["RESETCTRL",  {addr: 0x87F00000, size: 0x00001000, type: "reset"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* OMAP3530, 128 MB of external memory */
    ["OMAP3530",
    {
        memTable: [
            ["L4CORE",     {addr: 0x48000000, size: 0x01000000, type: "other"}],
            ["L4PER",      {addr: 0x49000000, size: 0x00100000, type: "other"}],
            ["CMEM",       {addr: 0x85000000, size: 0x01000000, type: "other"}],
            ["DDRALGHEAP", {addr: 0x86000000, size: 0x01800000, type: "other"}],
            ["DDR2",       {addr: 0x87800000, size: 0x00600000, type: "main" }],
            ["DSPLINKMEM", {addr: 0x87E00000, size: 0x00100000, type: "link" }],
            ["RESETCTRL",  {addr: 0x87F00000, size: 0x00001000, type: "reset"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* OMAP2530, 64 MB of external memory */
    ["OMAP2530",
    {
        memTable: [
            ["L4CORE",     {addr: 0x48000000, size: 0x01000000, type: "other"}],
            ["L4WAKEUP",   {addr: 0x49000000, size: 0x00800000, type: "other"}],
            ["CMEM",       {addr: 0x82400000, size: 0x00800000, type: "other"}],
            ["DDR2",       {addr: 0x82C00000, size: 0x00300000, type: "main" }],
            ["DSPLINKMEM", {addr: 0x82F00000, size: 0x000FF000, type: "link" }],
            ["RESETCTRL",  {addr: 0x82FFF000, size: 0x00001000, type: "reset"}],
            ["DDRALGHEAP", {addr: 0x83000000, size: 0x01000000, type: "other"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* TMS320C2430, 128 MB of external memory */
    ["TMS320C2430",
    {
        memTable: [
            ["L4CORE",     {addr: 0x48000000, size: 0x01000000, type: "other"}],
            ["L4WAKEUP",   {addr: 0x49000000, size: 0x00800000, type: "other"}],
            ["CMEM",       {addr: 0x85800000, size: 0x00800000, type: "other"}],
            ["DDRALGHEAP", {addr: 0x86000000, size: 0x01800000, type: "other"}],
            ["DDR2",       {addr: 0x87800000, size: 0x00600000, type: "main" }],
            ["DSPLINKMEM", {addr: 0x87E00000, size: 0x00100000, type: "link" }],
            ["RESETCTRL",  {addr: 0x87F00000, size: 0x00001000, type: "reset"}],
        ],
        doPowerControl : false,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* OMAPL137, 64 MB of external memory */
    ["OMAPL137",
    {
        memTable: [
           ["DDRALGHEAP", {addr: 0xC3000000, size: 0x01000000, type: "other"}],
           ["DDR2",       {addr: 0xC2C00000, size: 0x00300000, type: "main" }],
           ["DSPLINKMEM", {addr: 0xC2F01000, size: 0x00100000, type: "link" }],
           ["RESETCTRL",  {addr: 0xC2F00000, size: 0x00001000, type: "reset"}],
        ],
        doPowerControl : true,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    /* OMAPL138, 64 MB of external memory */
    ["OMAPL138",
    {
        memTable: [
           ["DDRALGHEAP", {addr: 0xC3000000, size: 0x01000000, type: "other"}],
           ["DDR2",       {addr: 0xC2C00000, size: 0x00300000, type: "main" }],
           ["DSPLINKMEM", {addr: 0xC2F01000, size: 0x00100000, type: "link" }],
           ["RESETCTRL",  {addr: 0xC2F00000, size: 0x00001000, type: "reset"}],
        ],
        doPowerControl : true,
        dspManagement : ti.sdo.ce.ipc.IIpc.BootAndLoadDsp
    }],

    ];
}
/*
 *  @(#) ti.sdo.ce.ipc.dsplink; 2, 0, 1,182; 12-2-2010 21:24:20; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

