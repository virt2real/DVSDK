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
 * ======== Settings.xdc ========
 * Configuration for the EDMA3 module to be able to create handles to the
 * resource handles for various scratch groups.
 */


@Template("./Settings.xdt")

metaonly module Settings {

    config UInt controllerId = 0; 

    /*!
     * ======== region ========
     * Id of the EDMA3 Region we will program with the assigned Resources etc.
     * Region number 1 usually corresponds to DSP.
     * Region number 0 usually corresponds to ARM. 
     */
    config UInt region = 1;

    /*!
     *  ======== persistentAllocFxn ========
     *  Function for allocating persistent memory for RMAN's and other IRESMAN
     *  implementation's internal objects.
     *
     *  This is required to be supplied ONLY if
     *  {@link ti.sdo.fc.rman.RMAN#useDSKT2} is set to `false`.
     */
    config String persistentAllocFxn = null;
 
    /*!
     *  ======== persistentFreeFxn ========
     *  Function for freeing persistent memory used by RMAN and other IRESMAN
     *  implementation's internal objects.
     *
     *  This is required to be supplied ONLY if
     *  {@link ti.sdo.fc.rman.RMAN#useDSKT2} is set to `false`.
     */
    config String persistentFreeFxn = null;
 
    /*!
     *  ======== semCreateFxn ========
     * Function to create semaphores used by various individual resource
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void * _semCreate(Int key, Int count);
     */
    config String semCreateFxn = null;
 
    /*!
     *  ======== semDeleteFxn ========
     * Function to delete semaphores used by various individual resource
     * manager(s) registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Void _semDelete(Void * sem);
     */
    config String semDeleteFxn = null;
  
    /*!
     *  ======== semPendFxn ========
     * Function to pend on semaphores used by various resource manager(s)
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     *  Int _semPend(Void * sem, UInt32 timeout);
     */
    config String semPendFxn = null;
 
    /*!
     *  ======== semPostFxn ========
     * Function to post on Semaphores used by various resource manager(s)
     * registered with RMAN.
     *
     *  Function signature is:
     *  @p(code)
     * Void _semPost(Void * sem);
     */
    config String semPostFxn = null;

    /*!
     * ======== maxAlgs ========
     * Maximum number of algorithm instances that will be created  
     */
    config UInt maxAlgs = 32;

    /*!
     * ========= maxRequests ======
     * Maximum number of "active" resource requests that will be 
     * made by the algorithms in each scratch group
     */  
    config UInt maxRequests = 64;

    /*!
     * ======== contiguousPaRams ========
     * Boolean value indicating if PaRams assigned to scratch groups need to be
     * contiguous or not
     */
    config bool contiguousPaRams = true;

    const UInt EDMA3_MAXGROUPS = 20;  /*! Maximum number of groups for sharing
                                 EDMA3 resources. */

    /*!
     * ======== globalInit ========
     * This flag decides if EDMA3 global registers and PaRam entries will be 
     * initialized by this module. 
     * If using on a device where ARM-side drivers might perform the 
     * intialization, set this to false so it doesn't overwrite the ARM-side
     * setup.
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     */
    config Bool globalInit = false;

    /*!
     * ======== globalConfig ========
     * Global configuration required to set the SOC specific configuration of
     * of the EDMA3 device
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     * far EDMA3_GblConfigParams _globalConfig;
     */
    config String globalConfig = null;

    /*!
     * ======== regionConfig ========
     * Instance specific  configuration required to set the region specific
     * resource ownership details of the EDMA3 device
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     * far EDMA3_InstanceInitConfg _regionConfig;
     */
    config String regionConfig = null;

 
    /*!
     * ======== maxTccs ========
     * Arrays containing the maximum number of TCCs that will be assigned to
     * groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     */
    config UInt maxTccs[EDMA3_MAXGROUPS];

    /*!
     * ======== maxPaRams ========
     * Arrays containing the maximum number of PaRams that will be assigned to
     * groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     */
    config UInt maxPaRams[EDMA3_MAXGROUPS];

    /*!
     * ======== maxEdmaChannels ========
     * Array containing the maximum number of Edma Channels that will be
     * assigned to groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     * On devices where DCHMAP doesn't exist, it is recommended to request as
     * many channels as PaRams requested
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     */
    config UInt maxEdmaChannels[EDMA3_MAXGROUPS];

    /*!
     * ======== maxQdmaChannels ========
     * Array containing the maximum number of Qdma Channels that will be
     * assigned to groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     *  This is required to be supplied ONLY if
     *  Application is built for C64P target .
     */
    config UInt maxQdmaChannels[EDMA3_MAXGROUPS];

    /*!
     * ======== debug ========
     *  Enable the debug profile of the EDMA3 library.
     *
     *  This will likely result in a larger and slower library being linked in.
     *
     *  @_nodoc
     */
    config bool debug = false;

    /*!
     * ======== trace ========
     *  Enable trace support
     *  @_nodoc
     */
    config bool trace = false;

    /*!
     *  ======== ipcKeyBase ========
     *  Linux only. Base value of keys of Linux IPC objects used by
     *  EDMA3. The IPC objects created by EDMA3 will use keys starting 
     *  at this
     *  value, and incrementing with each new object. There are currently
     *  three IPC objects, so keys in the range of ipcKeyBase to ipcKeyBase + 2
     *  will be reserved for EDMA3. The default value of ipcKeyBase is
     *  ascii code for "3AMD".
     *
     *  WARNING: This value should only be changed if it conflicts with
     *  another IPC key in the system that cannot be changed. If this value
     *  is changed, all programs using EDMA3 that will be run simultaneously
     *  must have the ipcKeyBase configured to the new value.
     *  @_nodoc
     */
    config UInt ipcKeyBase = 0x33414D44;

    /*!
     * ======== Region ========
     * Deprecated:
     * Id of the EDMA3 Region we will program with the assigned Resources etc.
     * @_nodoc
     */
    config UInt Region = 1;

    /*!
     * ======== GlobalInit ========
     * Deprecated:
     * This flag decides if EDMA3 global registers and PaRam entries will be 
     * initialized by this module. 
     * @_nodoc
     */
    config UInt GlobalInit = false;

    /*!
     * ======== MaxTccs ========
     * Deprecated
     * Arrays containing the maximum number of TCCs that will be assigned to
     * groups for sharing.
     * Algorithms created within a given group ID will share the EDMA3 resources
     * assigned to that group
     * @_nodoc
     */
    config UInt MaxTccs[] = [10,10,10,10,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0];

    /*!
     *  ======== MaxPaRams ========
     * Deprecated
     *  Array containing the maximum number of PaRams that will be assigned to
     *  groups for sharing.
     * @_nodoc
     */
    config UInt MaxPaRams[] = [20, 20, 20, 20, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0];

    /*!
     *  ======== ContigPaRams ========
     * Deprecated
     *  Boolean value indicating if PaRams assigned to scratch groups need
     *  to be contiguous or not.
     * @_nodoc
     */
    config bool ContiguousPaRams = true;

    /*!
     *  ======== MaxEdmaChannels ========
     *  Deprecated
     *  Array containing the maximum number of Edma Channels that will be
     *  assigned to groups for sharing.
     *  @_nodoc
     */
    config UInt MaxEdmaChannels[] = [4, 4, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0];

    /*!
     *  ======== MaxQdmaChannels ========
     *  Deprecated
     *  Array containing the maximum number of Qdma Channels that will be
     *  assigned to groups for sharing.
     *  @_nodoc
     */
    config UInt MaxQdmaChannels[] = [1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
            0, 0, 0, 0, 0, 0];

    /*!
     *  ======== GlobalConfig ========
     *  Deprecated
     *  Global configuration required to set the SOC specific configuration of
     *  of the EDMA3 device.
     *  @_nodoc   
     */
    config String GlobalConfig = null;

    /*!
     *  ======== RegionConfig ========
     *  Deprecated
     *  Instance specific  configuration required to set the region specific
     *  resource ownership details of the EDMA3 device.
     *  @_nodoc   
     */
    config String RegionConfig = null;

}
/*
 *  @(#) ti.sdo.fc.edma3; 3, 0, 0,152; 12-1-2010 17:24:42; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

