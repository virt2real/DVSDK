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
 *  ======== IOsal ========
 *  OSAL interface
 *
 */
metaonly interface IIpc
{
    /*!
     *  ======== ArmDspLinkConfigMemTableEntry ========
     *  Description of one DSP memory segment entry.
     *
     *  @field(addr)   The beginning address of the segment
     *  @field(gppAddr) The GPP physical address of the segment (when needed)
     *  @field(size)   Size of the segment in bytes
     *  @field(type)   One of the following types:
     *                 "main"     -- main code/data segment (i.e. DDR2)
     *                 "link"     -- DSPLINKMEM segment
     *                 "reset"    -- RESETCTRL segment
     *                 "poolmem"  -- POOLMEM segment
     *                 "code"     -- dsp code/data, must map into GPP space
     *                 "other"    -- anything else
     */
    struct ArmDspLinkConfigMemTableEntry {
        UInt32 addr;
        UInt32 gppAddr;
        UInt32 size;
        String type;
    }

    /*!
     *  ======== DspManagement ========
     *  Value for controlling DSP from ARM w/ DspLink
     *
     *  @field(BootAndLoadDsp)    DspLink boots DSP and loads executable
     *  @field(BootDspAutonomously)    DspLink boots DSP w/o loading executable
     *  @field(None)    DspLink neither boots DSP nor loads executable
     */
    enum DspManagement {
        BootAndLoadDsp,
        BootDspAutonomously,
        None
    };

    /*!
     *  ======== ArmDspLinkConfig ========
     *  Configuration for the DspLink on the Arm side
     *
     *  Of the many fields that Link exposes for configuration,
     *  selected ones are exposed through this interface.
     *
     *  @field(memTable)    Memory table, describing all DSP segments.
     *                      NOTE: segments "DDR2" (or whatever is the name of
     *                      the main segment), "DSPLINKMEM", and
     *                      "RESETCTRL" must be present
     *
     *  @field(doPowerControl)    Flag indicating if Link should implement
     *                      power control of DSP.
     *
     *  @field(dspManagement)    Flag indicating how Link should boot/load DSP
     */
    struct ArmDspLinkConfig {
        ArmDspLinkConfigMemTableEntry memTable[string];
        Bool doPowerControl;
        DspManagement dspManagement;
        /* TODO:M add other select params here... */
    }

    /*!
     *  ======== LinkConfigEntry ========
     *  This structure associates a sever executable with an ipc link
     *  configuration. The type of the linkCfg field is left as "Any",
     *  since it will depend on the module that implements the IIpc
     *  interface. This is an internal field used only by codec engine
     *  scripting.
     *
     *  @_nodoc
     */
    struct LinkConfigEntry {
        string serverName;              /* Name of the server executable */
        ArmDspLinkConfig    linkCfg;         /* Link configuration */
    }

    /*!
     *  ======== linkConfigs ========
     *  Link configurations per server; if left undefined will be
     *  set to DEFAULT_ARMDSPLINKCONFIG, but with a warning. This is an
     *  internal field, set by the Engine scripting.
     *
     *  @_nodoc
     */
    config LinkConfigEntry linkConfigs[string];
}
/*
 *  @(#) ti.sdo.ce.ipc; 2, 0, 1,183; 12-2-2010 21:24:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

