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
 *  ======== Server ========
 *  DSP Server Configuration interface
 */
@Template("./Server.xdt")

metaonly module Server
{
    /*!
     *  ======== MINPRI ========
     *  Minimum priority that a thread can assume
     *
     *  All threads must have a priority value greater than or equal to
     *  {@link #MINPRI Server.MINPRI} and less than or equal to
     *  {@link #MAXPRI Server.MAXPRI}.
     */
    readonly config Int MINPRI = 1;

    /*!
     *  ======== MAXPRI ========
     *  Maximum priority that a thread can assume
     *
     *  All threads must have a priority value greater than or equal to
     *  {@link #MINPRI Server.MINPRI} and less than or equal to
     *  {@link #MAXPRI Server.MAXPRI}.
     */
    readonly config Int MAXPRI = 15;

    /*!
     *  ======== ThreadAttrs ========
     *  Thread attributes
     *
     *  This structure defines the thread attrubutes for any threads created
     *  by the RMS thread; see Server.threadAttrs.
     */
    struct ThreadAttrs {
        Int stackSize;      /*! minimum stack size required for this thread */
        Int stackMemId;     /*! MEM seg id for the thread's stack */
        Int priority;       /*! priority of the thread */
    };

    /*!
     *  ======== AlgDesc ========
     *  Algorithm descriptor
     *
     *  This structure describes the execution context provided by
     *  the server for an algorithm module.
     *
     *  @field(name)    This string specifies the "local" name used by the
     *                  server to generate instance names
     *  @field(mod)     This field is a module reference that identifies the
     *                  actual module implementing the algorithm to instantiate.
     *                  This module reference is often acquired by a call to
     *                  `xdc.useModule();` like this:
     *                  @p(code)
     *                      modReference = xdc.useModule('package.Module');
     *                  @p
     *  @field(threadAttrs)  This structure defines attributes of the "server"
     *                  thread that will handle instance processing
     *                  requests; e.g., stack size and priority.
     *                  @p(blist)
     *                  -{@link #ThreadAttrs threadAttrs.stackSize}:  This
     *                      field is optional when configuring
     *                      an algorithm in a server, though strongly
     *                      recommended.  Stack overrun is a very common
     *                      cause of system instability.  If it's not supplied
     *                      by the server integrator's script, the stack size
     *                      returned by the codec's
     *                      {@link ICodec#getStackSize()} method will be
     *                      added to the value of
     *                      {@link #stackSizePad stackSizePad}.
     *                  -{@link #ThreadAttrs threadAttrs.stackMemId}:  This
     *                      field is required when configuring
     *                      an algorithm in a server.
     *                  -{@link #ThreadAttrs threadAttrs.priority}:  This
     *                      field is optional (though strongly recommended)
     *                       when configuring an algorithm in a server.
     *                      If it's not supplied by the server integrator's
     *                      script, a default priority will be assigned, and a
     *                      remark will be printed to the console during server
     *                      configuration to indicate which priority was
     *                      assigned to the algorithm.  Note that this priority
     *                      can be overridden at runtime by the application;
     *                      see the various `*_create()` VISA APIs for more
     *                      details.
     *                  @p
     *  @field(groupId) This id specifies which resource sharing group
     *                  this codec will be placed into.  The system
     *                  integrator must ensure that codecs within the same
     *                  group can not pre-empt each other.
     *
     *                  A common technique for assigning groupId's in
     *                  systems where same-priority tasks don't pre-empt
     *                  each other (e.g. DSP/BIOS) is to use the task priority.
     *                  Some systems do not allow sharing resources.  In
     *                  those systems, this parameter is ignored.
     *
     *                  Note that this parameter is ignored if "local" is not
     *                  TRUE.
     */
    struct AlgDesc {
        String      name;        /*! alg nick-name */
        ICodec.Module mod;       /*! alg that implements skeletons */
        ThreadAttrs threadAttrs; /*! thread properties for each alg instance */
        Int         groupId;     /*! group id of the algorithm */
    };

    /*!
     *  ======== threadAttrs ========
     *  Thread attributes for the Server daemon thread
     *
     *  A single Server thread is created within each DSP Server.  This thread
     *  accepts requests to create/destroy algorithm instances.
     *
     *  This thread is sometimes referred to as the Resource Manager Server
     *  (RMS) thread.
     *
     *  The `threadAttrs.stackSize` field is optional when configuring a
     *  server, though strongly recommended.  Stack overrun is a very common
     *  cause of system instability.  If the `threadAttrs.stackSize` field is
     *  not assigned by the server integrator's script, a default value of
     *  1K (1024 bytes) will be added to the value of
     *  {@link #stackSizePad stackSizePad} and used.
     *
     *  The `threadAttrs.priority` field is optional when configuring a
     *  server.  If it is not assigned, by the server integrator's script, a
     *  default value of {@link #MINPRI MINPRI} will be used.
     *
     *  The `threadAttrs.stackMemId` field is optional when configuring a
     *  server.  If it is not assigned, by the server integrator's script, a
     *  default value of 0 will be used.
     */
    config ThreadAttrs threadAttrs;

    /*!
     *  ======== algs ========
     *  Table of all algorithms supported by this DSP Server
     *
     *  See {@link #AlgDesc} documentation for more details.
     */
    config AlgDesc algs[];


    /*!
     *  ======== stackSizePad ========
     *  Pad applied to unconfigured, CE-created threads.
     *
     *  This pad is only applied to algorithm stacks that are not configured,
     *  as well as the {@link #threadAttrs Server thread} if it is not
     *  configured.
     */
    config Int stackSizePad = 8192;


    /*!
     *  ======== traceBufferSize ========
     *  (DEPRECATED) Size of the server trace buffer, in MAUs.
     *
     *  Trace buffer size should be set via {@link
     *  ti.sdo.ce.osal.Global#traceBufferSize}.  Changing
     *  traceBufferSize here is currently supported for backward
     *  compatibility, but will not be supported in the future.
     *
     *  The server trace buffer is a circular buffer of characters written
     *  to by clients of the {@link ti.sdo.ce.osal} Trace interface -
     *  and read by the Engine_*Trace() methods.
     *
     * @_nodoc
     */
    config Int traceBufferSize = 0;

    /*!
     *  ======== autoGenScratchSizeArrays ========
     *  Enable automatic generation of {@link ti.sdo.fc.dskt2.DSKT2 DSKT2}
     *  scratch group size arrays.
     *
     *  This configuration flag enables/disables automatic generation of
     *  the {@link ti.sdo.fc.dskt2.DSKT2#DARAM_SCRATCH_SIZES} and
     *  {@link ti.sdo.fc.dskt2.DSKT2#SARAM_SCRATCH_SIZES} scratch group sizes
     *  arrays.
     *
     *  When enabled (1), the arrays will be automatically generated during
     *  Server configuration, based upon the
     *  {@link ICodec#getDaramScratchSize()} and
     *  {@link ICodec#getSaramScratchSize()} methods of the configured set of
     *  algorithms.
     *
     *  When disabled (0), the engine integrator needs to manually configure
     *  the scratch group sizes arrays.
     */
    config Bool autoGenScratchSizeArrays = 0;

    /*!
     *  ======== SkelCachingPolicy ========
     *  Caching behavior that all skeletons will use.
     */
    enum SkelCachingPolicy {
        LOCALBUFFERINVWB = 0, /*! Invalidate before process, writeback after */
        WBINVALL         = 1, /*! Writeback invalidate all after process */
        NONE             = 2  /*! No cache management of buffers */
    };

    /*!
     *  ======== SkelCachingPolicy ========
     *  Caching behavior that all skeletons will use.
     */
    config SkelCachingPolicy skelCachingPolicy;

    /*!
     *  ======== close ========
     *  internal close method (see package.xs)
     * @_nodoc
     */
    function close();

    /*!
     *  ======== validate ========
     *  internal validate method (see package.xs)
     * @_nodoc
     */
    function validate();
}
/*
 *  @(#) ti.sdo.ce; 1, 0, 6,432; 12-2-2010 21:19:08; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

