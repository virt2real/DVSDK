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
 *  ======== DMAN3 ========
 *  EDMA3 QDMA resource manager.
 */
@Template("./DMAN3.xdt")

metaonly module DMAN3 {

    /*!
     *  ======= customDmaLib =======
     *  Set this to TRUE if a custom library is being used to perform DMA  
     *  transfers. In this case, qdma channels will have to be partitioned 
     *  into scratch groups using the numQdmaGroup configuration.
     */  
    config Bool customDmaLib; 

    /* DMAN3 configuration settings for memory requirements */
    /*!
     *  ======== heapInternal ========
     *  Heap ID for dynamic allocation of DMAN3 objects.
     *
     *  This must be allocated in L1D Internal RAM.
     *
     *  This parameter is unused when DMAN3 is used in a Linux environment.
     *
     *  This parameter is set to `DMAN3_HEAP_INTERNAL`.
     */
    config String heapInternal = "DMAN3_heapInternal_undefined";

    /*!
     *  ======== heapExternal ========
     *  Heap ID for dyn allocation of private DMAN3 data structures.
     *
     *  This parameter is unused when DMAN3 is used in a Linux environment.
     *
     *  This parameter is set to `DMAN3_HEAP_EXTERNAL`.
     */
    config String heapExternal = "DMAN3_heapExternal_undefined";

    /*!
     *  ======== scratchAllocFxn ========
     *  Function for allocating IDMA3 channel object's "env" in scratch
     *  memory.
     */
    config String scratchAllocFxn = null;

    /*!
     *  ======== scratchFreeFxn ========
     *  Function for freeing IDMA3 channel object's "env" that was allocated
     *  in scratch memory.
     */
    config String scratchFreeFxn = null;

    /*!
     *  ======== idma3Internal ========
     *  Use the internal memory heap for dynamic allocation of IDMA3 objects.
     *
     *  A value of `false` means that IDMA3 objects will be allocated
     *  in the heap specified by {@link #heapExternal}. If the
     *  value is `true`, IDMA3 objects will be
     *  allocated in the heap specified by {@link #heapInternal}.
     */
    config bool idma3Internal = true;

    /*!
     *  ======== cpu ========
     *  Use the non-EDMA3, CPU version of DMAN3.  
     */
    config bool cpu = false; 

    /*! 
     *  ======= useExternalRM =======
     *  Boolean flag indicating if the EDMA3 Low Level 
     *  Resource Manager should be used to manage EDMA3
     *  resources. If this flag is set to true, the SOC 
     *  specific settings are not required to be set in 
     *  this module. The ti.sdo.fc.edma3.Settings module
     *  should be set up correctly 
     */ 
    config bool useExternalRM = false;

    /*!
     *  ======== numQdmaChannels ========
     *  The number of Physical QDMA channels that are assigned to
     *  DMAN3 via configuration. These channels will be granted either 
     *  as scratch or persistently as part of IDMA3 handles.   
     *
     *  This parameter is set to `DMAN3_NUM_QDMA_CHANNELS`.
     */
    config UInt numQdmaChannels = 4;

    /* If DMAN3.useExternalRM is set to true, the SOC specific settings below
       are ignored.
    */
    /* SOC specific settings for EDMA3 */

    /*!
     *  ======== qdmaPaRamBase ========
     *  Physical base address of the PARAM0 in the EDMA3/QDMA
     *  hardware whose resources are being managed by DMAN3.
     *
     *  This parameter is set to `DMAN3_QDMA_PARAM_BASE`.
     */
    config Ptr  qdmaPaRamBase =  0x01C04000;

    /*!
     *  ======== maxPaRamEntries ========
     *  Total number of PARAM Table entries on the target hardware.
     *  (eg, for IVA2, Davinci this is 128, for Himalaya, this is 256).
     *
     *  This parameter is set to `DMAN3_MAX_PARAM_ENTRIES`.
     */
    config UInt maxPaRamEntries = 128;

    /*!
     *  ======== maxQdmaChannels ========
     *  The total number of Physical QDMA channels available on the
     *  target hardware (eg, 8 for DaVinci, 4 for IVA2).
     *
     *  This parameter is set to `DMAN3_MAX_QDMA_CHANNELS`.
     */
    config UInt maxQdmaChannels = 8;

   /*!
    *  ======= maxTCs ========
    *  Maximum number of transfer controllers on this SOC
    */
    config UInt maxTCs = 8;

    /* DMAN3 resource configuration settings */
    /* If DMAN3.useExternalRM is set to true, the resource specific settings 
       below are ignored.
       Instead setup the ti.sdo.fc.edma3.Settings module with the EDMA3
       that you would like to make available to this region */ 

    /*!
     *  ======== paRamBaseIndex ========
     *  (0 > value > 255) represents the first PARAM TABLE ENTRY
     *  NUMBER that is assigned by configuration for exclusive DMAN3 allocation.
     *
     *  Typically, addresses (PaRam sets) between 0 and 63 are reserved for use
     *  by drivers that need EDMA/chaining capabilities.
     *
     *  Additionally, on some multi-core devices (e.g. DM644x), PaRams are
     *  shared between the different cores (e.g. ARM and C64+).  In these
     *  cases, an executable will be configured for each core, and each
     *  executable should configure only the DMAN3 resources which will be used
     *  on that core.  E.g., on DM644x, the C64+ executable should
     *  be configured to avoid using what the ARM uses.  Note that on
     *  OMAP2430, the ARM doesn't have access to EDMA so all PaRam sets
     *  are available for the C64+ device.
     *
     *  This parameter is set to `DMAN3_PARAM_BASE_INDEX`.
     */
    config UInt paRamBaseIndex =  96;

    /*!
     *  ======== numPaRamEntries ========
     *  Number of PARAM Table entries starting at DMAN3_PARAM_BASE_INDEX
     *  assigned by configuration for exclusive DMAN3 allocation.
     *
     *  This parameter is set to `DMAN3_NUM_CONTIGUOUS_PARAM_ENTRIES`.
     */
    config UInt numPaRamEntries = 32;

    /*!
     *  ======== nullPaRamIndex ========
     *  Index of PARAM to be reserved as a "null" PaRam. This index will be
     *  used to set QCHMAP when the corresponding QDMA channel is not active.
     *  The value of nullPaRamIndex should be outside of the range of
     *  PaRam indices alloted to DMAN3, i.e., nullPaRamIndex should be less
     *  than paRamBaseIndex, or greater than paRamBaseIndex + numPaRamEntries.
     *  If PaRam registers are shared between two processors (eg, an Arm
     *  and a DSP), make sure the nullPaRamIndex is not used by the other
     *  processor.
     *     
     *  This parameter is set to `DMAN3_NULLPARAMINDEX`.
     */
    config UInt nullPaRamIndex = 0;

    /*!
     *  ======== qdmaChannels ========
     *  Array containing list of physical QDMA channels assigned to DMAN3.
     *
     *  This array is of size `DMAN3_NUM_QDMA_CHANNELS`
     *  (configured by {@link #numQdmaChannels}).
     *
     *  This parameter is set to `DMAN3_QDMA_CHANNELS[]`.
     *
     *  @see numQdmaChannels
     */
    config UInt qdmaChannels[] = [0, 1, 2, 3];

    /*!
     *  ======== tccAllocationMaskH ========
     *  32-bit bitmask representing configuration provided list of TCCs
     *  for exclusive DMAN3 allocation.
     *
     *  For example, for TCC's in the range 0-31 the Low Mask
     *  (tccAllocationMaskL) is configured so that a '1' in bit position 'i'
     *  indicates the TCC 'i' is assigned to DMAN3.
     *
     *  This parameter is set to `DMAN3_TCC_FREEMASK_H`.
     */
    config UInt tccAllocationMaskH = 0xffffffff;

    /*!
     *  ======== tccAllocationMaskL ========
     *  32-bit bitmask representing configuration provided list of TCCs
     *  for exclusive DMAN3 allocation.
     *
     *  For example, for TCC's in the range 0-31 the Low Mask
     *  (tccAllocationMaskL) is configured so that a '1' in bit position 'i'
     *  indicates the TCC 'i' is assigned to DMAN3.
     *
     *  This parameter is set to `DMAN3_TCC_FREEMASK_L`.
     */
    config UInt tccAllocationMaskL = 0x00000000;

    /*!
     *  ======= qdmaQueueMap ========
     *  Array contaning the mapping from QDMA Channels to Event Queues
     *
     *  Indicates mapping of all "qdmaChannels" defined above to
     *  particular Event Queue.  For example, `channelQueueMap[0]`
     *  specifies queue number for `qdmaChannel[0]`, etc.
     *
     *  Defaults map all qdmaChannels to Queue# 1
     */
    config UInt qdmaQueueMap[] = [1,1,1,1,1,1,1,1];

    /*!
     *  ======= queueTCMap ========
     * Array contaning the mapping from Event Queues to Transfer Controllers
     *
     * Indicates mapping of individual hardware Event Queues to the Transfer
     * Controllers.
     */
    config UInt queueTCMap[] = [0, 1, 2, 3, 4, 5, 6, 7];

    /*!
     *  ======= queuePri ========
     * Array contaning priorities of the event queues
     *
     * Indicates the priority accorded to each physical event queue.
     */
    config UInt queuePri[] = [3, 7, 0, 0, 0, 0, 0, 0];

    /* These const values must match those in dman3.h */

    const Int MAXGROUPS = 20;  /*! Maximum number of groups for sharing
                                 TCCs and parameter RAM. */

    /* DMAN3 configuration settings  for scratch groups */

    /*!
     *  ======== numTccGroup ========
     *  Arrays containing the number of TCC that will be assigned to groups for
     *  sharing
     *
     *  Channels created with a given group ID will use TCCs and PaRams
     *  allocated for that group ID, and may share them with other channels
     *  created with the same group ID.
     *
     *  This parameter is set to `DMAN3_NUMTCC_GROUP`.
     */
    config Int numTccGroup[MAXGROUPS] = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0,
            0, 0, 0, 0, 0, 0, 0,];

    /*!
     *  ======== numPaRamGroup ========
     *  Arrays containing the number of PaRam entries that will be assigned to
     * groups for sharing.
     *
     *  Channels created with a given group ID will use TCCs and PaRams
     *  allocated for that group ID, and may share them with other channels
     *  created with the same group ID.
     *
     *  This parameter is set to `DMAN3_NUMPARAM_GROUP`.
     */
    config Int numPaRamGroup[MAXGROUPS]= [0, 0, 0, 0, 0, 0, 0, 0, 0, 0,0, 0, 0,
            0, 0, 0, 0, 0, 0, 0,] ;

    /*!
     *  ======= numQdmaGroup =======
     *  Arrays containing the number of Qdma channels that will be assigned to 
     *  groups for sharing.
     *
     *  This configuration is required ONLY if the application uses atleast one 
     *  custom (non-ACPY3) DMA library that will request QDMA channels from
     *  DMAN3.  In this case, the configuration param "customDmaLib" should be 
     *  set to true.
     *
     *  Channels created with a given group ID will use TCCs and PaRams 
     *  allocated for that grup ID, and may share them with other channels  
     *  created with the same group ID. Qdma channels may be shared across
     *  algorithms and scratch groups if all algorithms use the same ACPY3
     *  library. But if even one algorithm uses a custom DMA library, Qdma
     *  channels should be distribued among scratch groups like other EDMA3
     *  resources. 
     */
    config Int numQdmaGroup[MAXGROUPS]; 

    /*
     * TODO:  These "Strings" should be Ints... how do we get a handle to
     * the BIOS objects in javascript-land?
     */

    /*!
     *  ======== debug ========
     *  Enable the debug profile of the DMAN3 library.
     *
     *  This will likely result in a larger and slower library being linked in.
     */
    config bool debug = false;

    /*!
     *  ======== trace ========
     *  Enable trace support
     */
    config bool trace = false;

    /*!
     *  ======== ipcKeyBase ========
     *  Linux only. Base value of keys of Linux IPC objects used by
     *  DMAN3. The IPC objects created by DMAN3 will use keys starting at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for DMAN3. The default value of ipcKeyBase is
     *  ascii code for "NAMD".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using DMAN3 that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x4e414d44;

    /*!
     *  ======== allowUnshared ========
     *  Allow DMAN3-related resources to be granted to an algorithm, even
     *  if there are not enough resources configured into the shared
     *  groupId which the algorithm is a member of.
     *
     *  If this property is set to `false`, the DMAN3 library will fail
     *  to grant DMA channels to an algorithm requesting more TCCs or
     *  PaRams then the number configured for its scratch group.
     *
     *  If this property is `true`, and an algorithm requests more TCCs or
     *  PaRams than the number configured for its scratch group, DMAN3 will
     *  do either of the following:
     *  @p(nlist)
     *     - If no algorithm is currently instantiated for the given scratch
     *       group, DMAN3 will bump up the number of TCCs and PaRams to the
     *       maximum of the number configured and that requested by the
     *       algorithm, for the scratch group. This will remain in effect
     *       until all algorithms for that scratch group are deleted.
     *     - If an algorithm has already been granted DMA channels for the
     *       given scratch group (so the number of TCCs and PaRams for that
     *       scratch group has already been determined by (1) above), and the
     *       number of TCCs or PaRams for the scratch group is insufficient for
     *       the algorithm currently requesting DMA channels, DMAN3 will
     *       allocate new TCCs and PaRams if available. These new TCCs and
     *       PaRams will not be shared by any other algorithm.
     */
    config bool allowUnshared = true;

}
/*
 *  @(#) ti.sdo.fc.dman3; 1, 0, 4,300; 12-1-2010 17:24:24; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

