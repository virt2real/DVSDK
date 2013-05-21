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
 *  ======== Engine ========
 *  Engine Configuration interface
 */
@Template("./Engine.xdt")

metaonly module Engine {

    /*!
     *  ======== local ========
     *  Default engine used by clients of the VISA API's that pass NULL for
     *  the engine handle
     *
     *  @_nodoc
     */
    config Engine.Instance local;

    /*!
     *  ======== MAXGROUPID ========
     *  Maximum group id.
     */
    const Int MAXGROUPID = 20;

    /*!
     *  ======== noCommName ========
     *  Create a Comm which doesn't pollute the Comm namespace.
     *
     *  Some ipc implementations (not all!) support creating an unnamed
     *  Comm.  DSP Link is adding support for this, the WinCE port will have
     *  support before the Linux port.  To help bridge the gap until all
     *  Link ports have this feature, and so we continue to work with Link
     *  releases that don't have this feature, CE is temporarily introducing
     *  this `noCommName` boolean.
     *
     *  The default behavior is "as before", but for users that require
     *  unnamed Comm creates (e.g. kernel mode WinCE users), they can set
     *  this config param to `true` - on ipc ports that support it(!).
     *
     *  The intent is to remove this `noCommName config param as soon as
     *  all Link ports support it, so don't get attached to it!
     *
     *  @_nodoc
     */
    config Bool noCommName = false;

    /*!
     *  ======== AlgDesc ========
     *  Algorithm descriptor
     *
     *  Each engine "contains" multiple algorithms described by AlgDesc
     *  structures.
     *
     *  @field(name)    This string specifies the "local" name used by the
     *                  application to identify the algorithm to instantiate
     *  @field(mod)     This field is a module reference that identifies the
     *                  actual module implementing the algorithm to instantiate
     *  @field(local)   If true, the algorithm should be instantiated on the
     *                  "local" CPU; otherwise the server will create an
     *                  instance of the algorithm identifed by `mod`.
     *  @field(groupId) This id specifies which resource sharing group
     *                  this codec will be placed into.  This 'group' concept
     *                  is used by the framework to ensure algorithms in the
     *                  same group don't pre-empt each other and corrupt the
     *                  shared resources.
     *
     *                  Note that this parameter is ignored if `local` is not
     *                  TRUE.
     */
    struct AlgDesc {
        String          name;       /*! Alg nick-name */
        ICodec.Module   mod;        /*! The alg implementation */
        Bool            local;      /*! Run algorithm locally */
        Int             groupId;    /*! Alg group ID for sharing resources */
    };

    /*!
     *  ======== createFromServer ========
     *  Create an Engine from a Server package
     *
     *  Given a Server package and an executable in that package, this method
     *  creates an Engine instance and initializes it from details in the
     *  Server provided.
     *
     *  An Engine instance created this way has all the codecs that exist
     *  in the Server executable - with codec names matching the names
     *  configured into the Server, and is configured to use an appropriate
     *  memory map and other DSP-specific info.
     *
     *  Example usage:
     *  @p(code)
     *  var myEngine = Engine.createFromServer("video_copy",
     *                     "./video_copy.x64P",
     *                     "ti.sdo.ce.examples.servers.video_copy");
     *
     *  @param(engineName)        Name to be used for the engine created
     *  @param(serverExecutable)  Path to the server executable (including the
     *                            executable), relative from server package
     *  @param(serverPackage)     Name of the server package
     *
     *  @a(returns)               An Engine instance of the same type as
     *                            if {@link #create create()} were called.
     */
    function createFromServer(engineName, serverExecutable, serverPackage);


    /*!
     *  ======== getDspMemTableFromServer ========
     *  Get a remote processor's memory table from a Server package
     *
     *  Given a Server package and an executable in that package, this method
     *  returns an object that contains the Server's memory map details.
     *
     *  For example:
     *  @p(code)
     *  myEngine.armDspLinkConfig.memTable =
     *      Engine.getDspMemTableFromServer(
     *                     "./video_copy.x64P",
     *                     "ti.sdo.ce.examples.servers.video_copy" );
     *
     *  @p
     *  There is no need to use this method when the preferred
     *  {@link #createFromServer createFromServer()} method is used first.
     *
     *  @param(serverExecutable)  Path to the server executable (including the
     *                            executable), relative from server package
     *  @param(serverPackage)     Name of the server package
     *
     *  @a(returns)               A DSP memory table "map" object, of type
     *                            ti.sdo.ce.osal.Global.
     *                            ArmDspLinkConfigMemTableEntry[string]
     *
     *  @see createFromServer
     */
    function getDspMemTableFromServer(serverExecutable, serverPackage);

    /*!
     *  ======== close ========
     *  Internal close method (see package.xs)
     * @_nodoc
     */
    function close();

    /*!
     *  ======== validate ========
     *  Internal validate method (see package.xs)
     * @_nodoc
     */
    function validate();

    /*!
     * ======== usesIDMA3 ========
     * Returns true if there is an engine with a local alg that implements
     * idma3Fxns. This function is used to determine whether or not DMAN3
     * library needs to be linked in.
     *
     * @_nodoc
     */
    bool usesIDMA3();

    /*!
     * ======== usesIRES ========
     * Returns true if there is an engine with a local alg that implements
     * iresFxns. This function is used to determine whether or not RMAN
     * library needs to be linked in.
     *
     * @_nodoc
     */
    bool usesIRES();

    /*!
     *  ======== hasServer ========
     *  Returns true if there is an engine with a remote alg, or an engine
     *  that uses a server.
     *
     *  @_nodoc
     */
    bool hasServer();

instance:

    /*!
     *  ======== create ========
     *  Create Engine instance
     *
     *  Parameters:
     *  @p(dlist)
     *      - `name`
     *          Name of this engine; this name is used by clients via the
     *          `Engine_open()` API to identify the collection of algorithms
     *          available.
     *
     *      - `algs`
     *          Array of algorithms this engine supports
     *
     *      - `server`
     *          Optional name of the DSP Server; this name is used (if
     *          necessary) to load and start any associated DSP CPUs required
     *          to support this Engine instance
     */
    create(String name, AlgDesc algs[]);

    /*!
     *  ======== name ========
     *  Name of this engine.
     *
     *  This string provided by the application in the `Engine_open()` call.
     */
    config String name;

    /*!
     *  ======== algs ========
     *  Array of algorithms available in an Engine
     *
     *  An array of algorithms which this Engine instance provides.  A mix
     *  of local and remote algorithms can be specified in this array.
     *
     *  {@link #createFromServer createFromServer()} can be used to populate
     *  this array with algorithms configured into a remote Server.
     *
     *  @see createFromServer
     */
    config AlgDesc algs[];

    /*!
     *  ======== server ========
     *  Optional name of the remote server.
     *
     *  This parameter is only necessary when there are algorithms configured
     *  to run remotely - i.e., their `local` field is set to false.
     *
     *  Engines containing these remote algorithms will need to set
     *  this `server` parameter to the name of the binary which should
     *  be loaded on the remote processor.
     */
    config String server;

    /*!
     *  ======== armDspLinkConfig ========
     *  ARM-side DSP Link configuration
     *
     *  The ARM-side DSP Link configuration.  If left undefined will revert to
     *  ti.sdo.ce.ipc.DEFAULT_ARMDSPLINKCONFIG, but with a warning
     *
     *  Applies only to CE configurations where
     *  osal.Global.runtimeEnv == DSPLINK_LINUX
     *
     *  @p
     *  There is no need to use this method when the preferred
     *  {@link #createFromServer createFromServer()} method is used first.
     *
     *  @see createFromServer
     */
    config ti.sdo.ce.ipc.IIpc.ArmDspLinkConfig armDspLinkConfig;

   /*!
     *  ======== linkCfg ========
     *  Optional name of DSP Link configuration.
     *
     *  This parameter is only needed when LAD is used to
     *  arbitrate control of the DSP server
     */
    config String linkCfg;
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:07; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

