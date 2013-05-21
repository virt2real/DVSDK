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
 *  ======== TraceUtil ========
 *  TraceUtil Configuration interface
 */
@Template("./TraceUtil.xdt")

metaonly module TraceUtil {

    /*!
     *  ======== PipeCmdAlias ========
     *  Alias' to use for the cmd pipe.
     */
    struct PipeCmdAlias {
        String alias;           /*! alias for a group of pipe commands */
        String cmds[];          /*! list of pipe commands for this alias */
    };

    /*!
     *  ======== Attrs ========
     *  Configuration attributes
     *
     *  This structure describes the initialization settings for the
     *  TraceUtil module; see TraceUtil.attrs.
     *
     *  @field(localTraceMask)  The trace mask to be used on the "local",
     *                          or application processor.
     *
     *  @field(localTraceFile)  The name of the file into which trace output
     *                          will be generated.  This can be a full path
     *                          (e.g. `/tmp/local.txt`), or a path relative
     *                          to the executing application.
     *
     *  @field(dsp0TraceMask)   The trace mask to be used on the "remote"
     *                          server.
     *
     *  @field(dsp0TraceFile)   The name of the file into which trace output
     *                          will be generated.  This can be a full path
     *                          (e.g. `/tmp/dsp0.txt`), or a path relative
     *                          to the executing application.
     *
     *  @field(dsp0BiosFile)    The name of the file into which DSP/BIOS log
     *                          output will be generated.  This can be a
     *                          full path (e.g. `/tmp/dspbios.dat`), or a
     *                          path relative to the executing application.
     *
     *  @field(traceFileFlags)  fopen flags used when opening the various
     *                          trace/log files.  See fopen() documentation
     *                          for details.  For example, to open the files
     *                          in "append" mode (i.e. add to existing file
     *                          content), use "a"; to open in "over-write"
     *                          mode, use "w".
     *
     *  @field(refreshPeriod)   The number of milliseconds to sleep before
     *                          reading the content off the remote servers.
     *                          This will vary based on the amount of trace
     *                          generated, and the size of the trace logs.
     *                          Failure to set this low enough will result
     *                          in data loss.
     */
    struct Attrs {
         String   localTraceMask;   /*! local tracing mask */
         String   localTraceFile;   /*! local tracing file */
         String   dsp0TraceMask;    /*! server's tracing mask */
         String   dsp0TraceFile;    /*! server's tracing file */
         String   dsp0BiosFile;     /*! server's BIOS tracing file */
         String   traceFileFlags;   /*! flags for fopen()ing trace files */
         Int      refreshPeriod;    /*! number of ms before two DSP data gets */
         String   cmdPipeFile;      /*! named pipe to read commands from */
         PipeCmdAlias cmdAliases[]; /*! any aliases for the pipe commands */
    };

    /* various pre-packaged tracing profiles (Configs) */

    /*!
     *  ======== NO_TRACING ========
     *  No tracing or logging of any kind
     */
    const Attrs NO_TRACING = {
        localTraceMask:    "*=",
        localTraceFile:    null,
        dsp0TraceMask:     "*=",
        dsp0TraceFile:     null,
        dsp0BiosFile:      null,
        traceFileFlags:    null,
        refreshPeriod:     0,
        cmdPipeFile:       "/tmp/cecmdpipe",
        cmdAliases: [ ],
    };

    /*!
     *  ======== DEFAULT_TRACING ========
     *  Tracing that prints warnings and errors on the standard output
     */
    const Attrs DEFAULT_TRACING = {
        localTraceMask:    "*=67",
        localTraceFile:    null,
        dsp0TraceMask:     "*=67",
        dsp0TraceFile:     null,
        dsp0BiosFile:      null,
        traceFileFlags:    null,
        refreshPeriod:     300,
        cmdPipeFile:       "/tmp/cecmdpipe",
        cmdAliases: [ ],
    };

    /*!
     *  ======== SOCRATES_TRACING ========
     *  Tracing appropriate for the SoC Analyzer data collection tool.
     *
     *  The default settings here place data files into the `/tmp` directory.
     *  `/tmp` typically provides faster write access than other file
     *  system files, so it is used to lower the overhead of tracing.
     *
     *  Using these default settings, the GPP and DSP generate approximately
     *  400 characters of trace in *each* the localTraceFile and
     *  dsp0TraceFile, for each round trip to/from the DSP.  This includes the
     *  typical `process()` and `control()` calls to each codec.
     *
     *  Using that figure, the user is encouraged to configure the
     *  refreshPeriod and System trace buffers appropriately, so as to reduce
     *  the likelyhood of data loss due to wrapping.
     *
     *  For example, consider an application which utilizes a 30
     *  frame-per-second video codec in parallel with a 50 frame-per-second
     *  audio codec.  Additionally, the audio codec requires calling `process()`
     *  *and* `control()` for each frame - the video only requires a single
     *  process() call.  This application alone will generate approximately
     *  ((50 * 2) + 30) * 400 = 52000 bytes of trace data each second.  If the
     *  default System trace buffer size is used (32768 bytes), the application
     *  needs to ensure the refresh period is less than 650 milliseconds
     *  *not including I/O overhead or potential for pre-emption*.
     */
    const Attrs SOCRATES_TRACING = {
        localTraceMask:    "*=67",
        localTraceFile:    "/tmp/cearmlog.txt",
        dsp0TraceMask:     "*=67",
        dsp0TraceFile:     "/tmp/cedsp0log.txt",
        dsp0BiosFile:      "/tmp/bioslog.dat",

        /* Open the file for writing.  Note, this over-writes existing files. */
        traceFileFlags:    "w",

        refreshPeriod:     0,
        cmdPipeFile:       "/tmp/cecmdpipe",
        cmdAliases: [
            {
                alias: "socrates=on",
                cmds:  [
                       "tracemask=*+5",
                       "dsp0tracemask=*+5,ti.bios+3",
                       "refreshperiod=200",
                ],
            },
            {
                alias: "socrates=off",
                cmds:  [
                       "tracemask=*-5",
                       "refreshperiod=0",
                       "dsp0tracemask=*-5,ti.bios-3"
                ],
            },
        ],
    };

    /*!
     *  ======== FULL_TRACING ========
     *  Enable all tracing.
     */
    const Attrs FULL_TRACING = {
        localTraceMask:    "*=01234567",
        localTraceFile:    "trace/cearmlog.txt",
        dsp0TraceMask:     "*=01234567,ti.bios=01324567",
        dsp0TraceFile:     "trace/cedsp0log.txt",
        dsp0BiosFile:      "trace/bioslog.dat",
        traceFileFlags:    "w",
        refreshPeriod:     100,
        cmdPipeFile:       "/tmp/cecmdpipe",
        cmdAliases: [ ],
    };

    /*!
     *  ======== attrs ========
     *  Tracing configuration; by default set to some very basic tracing
     */
    config Attrs attrs = DEFAULT_TRACING;
}
/*
 *  @(#) ti.sdo.ce.utils.trace; 1, 0, 1,307; 12-2-2010 21:28:05; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

