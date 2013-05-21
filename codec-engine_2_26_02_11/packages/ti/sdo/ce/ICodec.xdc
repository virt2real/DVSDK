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
 *  ======== ICodec ========
 *  Codec Engine algorithm interface
 *
 *  All codecs supported by the codec engine must implement this interface.
 *  This interface provides the Codec Engine runtime the following information:
 *  @p(nlist)
 *      - How much stack space is required by the algorithm during instance
 *        creation (so the runtime can allocate an appropriate stack).
 *      - How much stack space is required by the algorithm during execution
 *        (so the runtime can allocate an appropriate stack).
 *      - The algorithm's entry points for the IALG interface (so the runtime
 *        can lookup the algorithm's functions based on a string name).
 *      - The algorithm's entry points for the optional IDMA3 interface
 *        (so the runtime can allocate DMA resources for the algorithm at
 *         runtime).
 *      - The entry points for "stubs" and "skeletons" in the case that the
 *        algorithm is to be run on a remote processor.
 *      - The size of scratch memory required by the algorithm.
 *  @p
 */
metaonly interface ICodec
{
    /*!
     *  ======== isLocal ========
     *  Require this codec to run "locally"
     *
     *  This configuration parameter determines whether or not the
     *  application requires the codec's library in order to link.
     *  For example, this parameter is set to false in the case that
     *  the application is running on a different CPU than the codec.
     *
     *  @_nodoc
     */
    config Bool isLocal = true;

    /*!
     *  ======== ialgFxns ========
     *  Name of xDAIS alg function table
     *
     *  All xDAIS algorithms must define an IALG_Fxns structure that
     *  contains implementations of the IALG methods.  This configuration
     *  parameter is simply the extern name of this structure.
     */
    readonly config String ialgFxns;

    /*!
     *  ======== idma3Fxns ========
     *  Name of xDAIS alg IDMA3 Interface function table
     *
     *  All xDAIS algorithms that use DMA must define an IDMA3_Fxns structure
     *  containing the pointers to functions implementatng the IDMA3 interface.
     *  If algorithm does not use DMA this structure does not have to be
     *  defined.
     *
     *  This configuration parameter is simply the extern name of this
     *  structure when defined, null otherwise.
     */
    readonly config String idma3Fxns;

    /*!
     *  ======== iresFxns ========
     *  Name of xDAIS alg IRES Interface function table
     *
     *  All xDAIS algorithms that use an IRES resource must define an
     *  IRES_Fxns structure containing the pointers to functions
     *  implementatng the IRES interface.
     *  If algorithm does not use an IRES resource this structure does not
     *  have to be defined.
     *
     *  This configuration parameter is simply the extern name of this
     *  structure when defined, null otherwise.
     *
     *  @see #ialgFxns
     *  @see #idma3Fxns
     */
    readonly config String iresFxns;

    /*!
     *  ======== serverFxns ========
     *  Name of skeleton fxn table
     *
     *  All algorithm's that can run on a remote processor must specify a set
     *  of "stub" functions that marshall arguments to send to the remote
     *  process that runs corresponding "skeletons" to do the actual
     *  processing.  This configuration parameter defines the entry point for
     *  this algorithm's the skeletons (which run on the remote processor).
     *
     *  This is generally not configured by application or server config
     *  scripts, but rather by developers of VISA-like API class extensions.
     *  However, an application or server integrator could use this config
     *  param to configure in custom serverFxns.
     *
     *  @see #stubFxns
     */
    config String serverFxns;

    /*!
     *  ======== stubFxns ========
     *  Name of stubs fxn table
     *
     *  All algorithm's that can run on a remote processor must specify a set
     *  of "stub" functions that marshall arguments to send to the remote
     *  process that runs corresponding "skeletons" to do the actual
     *  processing.  This configuration parameter defines the entry point for
     *  this algorithm's the stubs (which run on the local processor).
     *
     *  This is generally not configured by application or server config
     *  scripts, but rather by developers of VISA-like API class extensions.
     *  However, an application or server integrator could use this config
     *  param to configure in custom stubFxns.
     *
     *  @see #serverFxns
     */
    config String stubFxns;

    /*!
     *  ======== rpcProtocolVersion ========
     *  Version of the Protocol used between the stubFxns and the serverFxns.
     *
     *  This is set by a particular implementation of a stub/skeleton RPC pair,
     *  and is used at runtime to ensure the protocol matches.  This is
     *  important, for example, to ensure that the protocol used by skeletons
     *  built into a server matches that used by the stubs built into the
     *  application.  Specifically, this is typically changed when the
     *  marshalling/unmarshalling message format changes.
     *
     *  This is generally not configured by application or server config
     *  scripts, but rather by developers of VISA-like API class extensions.
     *
     *  This rpcProtocolVersion is built into the local application executable,
     *  as well as the remote server's executable.
     *
     *  Developers of class extensions should ensure this config parameter is
     *  set appropriately by each release of their stubs/skeletons.  If a new
     *  protocol is introduced, implying that updating both would result in
     *  error, the number should be incremented.
     *
     *  There is no "backward-compatibility" requirement in rpcProtocolVersion.
     *  If the version is different, regardless of whether it's larger or
     *  smaller, the creation of algorithms of this class will fail.
     */
    readonly config Int rpcProtocolVersion;

    /*!
     *  ======== uuid =======
     *  Unique algorithm implementation ID
     *
     *  This integer must be a unique ID for every algorithm in a "system",
     *  where the "system" includes all possible DSP Servers.
     *
     *  This id is used by the Codec Engine APIs to identify the algorithm
     *  implementation that will create an instance on a DSP Server.
     *
     *  If a codec doesn't explicitly configure this parameter, a "very likely
     *  unique" ID will be generated.  It is recommended that codecs not
     *  explicitly configure this parameter, and leave it to the system.
     */
    config Int uuid;

    /*!
     *  ======== frameRate ========
     *  Smallest supported frame rate (frames / second)
     *
     *  This is used to compute a default priority assignment for algorithm
     *  threads in a DSP Server.
     *
     *  @_nodoc
     */
    readonly config Int frameRate;

    /*!
     *  ======== codecClassConfigurable ========
     *  True if the class to which the codec belongs (VISA, or custom if not
     *  a VISA) has some special run-time config params
     *
     *  @_nodoc
     */
    readonly config Bool codecClassConfigurable;

    /*!
     *  ======== useCache ========
     *  If set to true, the codec's memory requests will be allocated from
     *  cacheable memory. If set to false, the memory will be allocated from
     *  non-cached memory. If this is not set, the
     *  ti.sdo.ce.alg.Settings.useCache flag will determine whether the
     *  codec's memory will be allocated from cached or non-cached memory.
     */
    config Bool useCache;

    /*!
     *  ======== getCreationStackSize ========
     *  Get the maximum required stack size (in octets) for this algorithm
     *  during algorithm instance creation.
     *
     *  This method is called during DSP Server configuration and is used to
     *  ensure that the instance creation thread on the server has sufficient
     *  stackspace to instantiate the algorithm.  This stack size is typically
     *  the greater of the stack sizes required by the algorithm's
     *  algNumAlloc(), algAlloc(), or algInit() methods.
     */
    Int getCreationStackSize(xdc.cfg.Program.Module prog);

    /*!
     *  ======== getDaramScratchSize ========
     *  Get the maximum scratch size (in octets) required for this algorithm
     *  from DARAM space.
     *
     *  This method is called during DSP Server configuration and is used to
     *  ensure that sufficient scratch space is configured for the specified
     *  set of algorithms.
     */
    Int getDaramScratchSize(xdc.cfg.Program.Module prog);

    /*!
     *  ======== getSaramScratchSize ========
     *  Get the maximum scratch size (in octets) required for this algorithm
     *  from SARAM space.
     *
     *  This method is called during DSP Server configuration and is used to
     *  ensure that sufficient scratch space is configured for the specified
     *  set of algorithms.
     */
    Int getSaramScratchSize(xdc.cfg.Program.Module prog);

    /*!
     *  ======== getStackSize ========
     *  Get the maximum stack size (in octets) required for this algorithm
     *  during its execution phase.
     *
     *  This method is called during DSP Server configuration and is used to
     *  ensure that threads on the server have sufficient stackspace to run
     *  the algorithm.
     */
    Int getStackSize(xdc.cfg.Program.Module prog);

    /*!
     *  ======== getUUID ========
     *  Get a uuid for this codec
     *
     *  This method is used to get the uuid rather than reading the uuid
     *  config parameter; this allows the algorithm producer to let the
     *  system generate a uuid from the algorithm's name.
     *
     *  Individual algorithm's should not implement this methods; the default
     *  (base) implementation provided in the ti.sdo.ce package should be
     *  sufficient.
     *
     *  @_nodoc
     */
    Int getUUID();
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:08; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

