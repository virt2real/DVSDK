/* --COPYRIGHT--,ESD
 *  Copyright (c) 2008 Texas Instruments. All rights reserved. 
 *  This program and the accompanying materials are made available under the 
 *  terms of the Eclipse Public License v1.0 and Eclipse Distribution License
 *  v. 1.0 which accompanies this distribution. The Eclipse Public License is
 *  available at http://www.eclipse.org/legal/epl-v10.html and the Eclipse
 *  Distribution License is available at 
 *  http://www.eclipse.org/org/documents/edl-v10.php.
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 * --/COPYRIGHT--*/
/*
 *  ======== LoggerBuf.xdc ========
 *
 *! Revision History
 *! ================
 *! 13-Jun-2007 nitya   Fixed SDSCM00020303, SDSCM00020305, SDSCM00020304
 *! 13-Jun-2007 nitya   flushAllInternal cannot be in internal section
 *! 22-Mar-2007 rt      Updated with concepts from avala-e02's LoggerBufAtomic
 */

/*!
 *  ======== LoggerBuf ========
 *  A logger which stores `Log` events in a buffer.
 *
 *  This module provides a logger which captures `{@link Log}` events to a
 *  buffer in realtime. The `Log` events stored in the buffer are
 *  unformatted; `Log` event formatting is deferred until some client reads
 *  the raw event data from the buffer. You can use
 *  `{@link #flush LoggerBuf_flush()}` to process the `Log` events stored
 *  in the buffer and stream the formatted output to stdout
 *  (via `{@link System#printf}`).  Alternatively, you can read a raw event
 *  (via `{@link #getNextEntry}`) and send it to another client that
 *  has the resources to format the event for display.
 *
 *  The implementation of this logger is fast with minimal stack usage
 *  making it appropriate for a realtime application.
 *  This logger writes all `Log` events to a circular buffer.  As a
 *  result, the execution time of all `Log` methods bound to this type
 *  of logger are deterministic (and quite short) because there are no
 *  additional memory allocation calls after the circular buffer was
 *  allocated.
 *
 *  If this logger is used in a preemptive environment, then an appropriate
 *  gate must be assigned to the module. For example, if events are generated
 *  from an interrupt context, then a gate that disables interrupts
 *  must be used.
 *
 *  @p(code)
 *  var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
 *  LoggerBuf.common$.gate = ...some gate instance...
 *  @p
 *
 *  If the buffer type is circular, the log buffer of size
 *  `{@link #numEntries}` contains the last `numEntries` of `Log` events. If
 *  the buffer type is fixed, the log buffer contains the first
 *  `numEntries` events.
 *
 *  @a(Examples)
 *  Configuration example: The following XDC configuration statements
 *  create a logger instance, assign it as the default logger for all
 *  modules, and enable `USER1` logging in all modules of the package
 *  `my.pkg`. See the `{@link Diags#setMaskMeta Diags.setMaskMeta()}` function
 *  for details on specifying the module names.
 *
 *  @p(code)
 *  var Defaults = xdc.useModule('xdc.runtime.Defaults');
 *  var Diags = xdc.useModule('xdc.runtime.Diags');
 *  var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
 *
 *  LoggerBuf.enableFlush = true;
 *  var LoggerBufParams = new LoggerBuf.Params();
 *  LoggerBufParams.exitFlush = true;
 *  Defaults.common$.logger = LoggerBuf.create(LoggerBufParams);
 *  Diags.setMaskMeta("my.pkg.%", Diags.USER1, Diags.RUNTIME_ON);
 *  @p
 */

@ModuleStartup      /* Initialize static instances */
@InstanceFinalize   /* this mod has cleanup fxn when instances are deleted */
@InstanceInitError  /* instance create can fail */
@Gated

module LoggerBuf inherits ILogger {

    /*!
     *  ======== BufType ========
     *  Type of log buffer
     */
    enum BufType {
        BufType_CIRCULAR,  /*! The log buffer wraps, overwriting old entries */
        BufType_FIXED      /*! The log buffer halts collection when full */
    };

    metaonly struct BasicView {
        String label;
        Int lastSerial;
        Int numEntries;
        String type;
        Bool enabledFlag;  
    };

    metaonly struct RecordView {
        Int     serial;
        Long    timestampRaw;
        String  modName;
        String  text;
        Int     eventId;
        String  eventName;
        IArg    arg0;
        IArg    arg1;
        IArg    arg2;
        IArg    arg3;
        IArg    arg4;
        IArg    arg5;
        IArg    arg6;
        IArg    arg7;
    }

    /*!
     *  ======== rovViewInfo ========
     *  @_nodoc
     */
    @Facet
    metaonly config xdc.rov.ViewInfo.Instance rovViewInfo = 
        xdc.rov.ViewInfo.create({
            viewMap: [
                ['Basic', 
                    {
                        type: xdc.rov.ViewInfo.INSTANCE,
                        viewInitFxn: 'viewInitBasic',
                        structName: 'BasicView'
                    }
                ],
                ['Records', 
                    {
                        type: xdc.rov.ViewInfo.INSTANCE_DATA,
                        viewInitFxn: 'viewInitRecords',
                        structName: 'RecordView'
                    }
                ]
            ]
        });

    /*!
     *  ======== StopModeData ========
     *  This data is added to the RTA MetaData file to support stop mode RTA.
     */
    @XmlDtd metaonly struct StopModeData {
        String bufferSymbol;
        Int bufferSize;
    }
    
    /*!
     *  ======== TimestampProxy ========
     *  User supplied time-stamp proxy
     *
     *  This proxy allows `LoggerBuf` to use a timestamp server different
     *  from the server used by `{@link xdc.runtime.Timestamp}`. However, if
     *  not supplied by a user, this proxy defaults to whichever timestamp
     *  server is used by `Timestamp`.
     */
    proxy TimestampProxy inherits ITimestampClient;

    /*!
     *  ======== enableFlush ========
     *  Flush all logs at system exit
     */
    config Bool enableFlush = false;

    /*!
     *  ======== flushAll ========
     *  Flush logs of all instances of `LoggerBuf`
     *
     *  The user is responsible for making sure that no `LoggerBuf` instances
     *  are created or deleted while in this API, by using an appropriate gate.
     */
    Void flushAll();

    /*!
     *  ======== flushAllInternal ========
     *  @_nodoc
     */
    Void flushAllInternal(Int stat);

    /*!
     * @_nodoc
     *  ======== initDecoder ========
     *  Initialize the LoggerBufDecoder for use in the LoggerBuf 'Records' ROV
     *  view.
     */
    function initDecoder();
    
instance:
    /*!
     *  ======== create ========
     *  Create a `LoggerBuf` logger
     *
     *  @see LoggerBuf#Params
     */
    create();

    /*!
     *  ======== numEntries ========
     *  Number of entries in buffer
     *
     *  Each entry is large enough to store one `Log` event containing up to
     *  4 optional arguments.  Events containing more than 4 arguments (such
     *  as those from `{@link Log#write5}`) use 2 entries.
     *
     *  `numEntries` must be a power of 2.
     */
    config Int numEntries = 64;

    /*!
     *  ======== bufType ========
     *  Log buffer type
     */
    config BufType bufType = BufType_CIRCULAR;

    /*!
     *  ======== exitFlush ========
     *  Flush log at system exit
     *
     *  Only used when module parameter `{@link #enableFlush}` is `true`.
     */
    config Bool exitFlush = false;

    /*!
     *  ======== bufSection ========
     *  Section name for the buffer managed by the static instance.
     *
     *  The default section is the 'dataSection' in the platform.
     */
    metaonly config String bufSection = null;

    /*!
     *  ======== bufHeap ========
     *  The heap that contains the `Log` buffer for dynamic instances.
     *
     *  The default value `null` means the buffer will be allocated from
     *  the `{@link Memory#defaultHeapInstance}` heap.
     */
    config IHeap.Handle bufHeap = null;

    /*!
     *  ======== enable ========
     *  Enable a log
     *
     *  @a(returns)
     *  The function returns the state of the log (`TRUE` if enabled,
     *  `FALSE` if disabled) before the call. That allow clients to restore
     *  the previous state.
     */
    Bool enable();

    /*!
     *  ======== disable ========
     *  Disable a log
     *
     *  Events written to a disabled log are silently discarded.
     *
     *  @a(returns)
     *  The function returns the state of the log (`TRUE` if enabled,
     *  `FALSE` if disabled) before the call. That allow clients to restore
     *  the previous state.
     */
    Bool disable();

    /*!
     *  ======== reset ========
     *  Reset a log to empty state and enable it
     *
     *  @a(WARNING)  This method is not synchronized with other instance
     *  methods and, as a result, it must never be called when there is a
     *  chance that another instance method is currently in operation or
     *  when another method on this instance may preempt this call.
     */
    Void reset();

    /*!
     *  ======== flush ========
     *  Read, clear, and output the contents of the log
     *
     *  This method reads, clears, and "prints" each `Log` event (via
     *  `{@link System#printf}`) in the log.
     */
    Void flush();

    /*!
     *  ======== getNextEntry ========
     *  Fills the passed `{@link Log#EventRec}` with the next entry in the log.
     *
     *  This function is used to read and clear `Log` events from the
     *  buffer maintained by the `LoggerBuf` instance. The `Log` event can
     *  then be transmitted and displayed on a host.
     *
     *  A read pointer is maintained in the `LoggerBuf` instance and
     *  points to the next record to read.  Entries are not necessarily
     *  returned in chronological order, since buffers of type
     *  `{@link #BufType_CIRCULAR}` can wrap.
     *
     *  @param(evtRec) pointer to a supplied `EventRec` object where the next
     *                 entry in the log is copied to
     *
     *  @a(returns)
     *  This function reports the number of entries actually read. The only
     *  values that can be returned are:
     *  @p(blist)
     *      - 0   no more entries to read
     *      - 1 or 2 read a complete entry written by `write4` or `write8`
     *      - -1  cleared an incomplete/overwritten entry, more entries to read
     */
    Int getNextEntry(Log.EventRec *evtRec);
    
internal:

    const Int8 FULL = -1;
    const Int8 WRAP = 0;

    const Int8 NEXT = 1;

    struct Entry {
        Types.Timestamp64 tstamp;
        Bits32 serial;
        Types.Event evt;
        IArg arg1;
        IArg arg2;
        IArg arg3;
        IArg arg4;
    };

    struct Instance_State {
        IHeap.Handle bufHeap;
        Entry entryArr[];
        Entry *curEntry;
        Entry *endEntry;
        Entry *readEntry;
        Bits32 serial;
        Int16 numEntries;
        Int8 advance;
        Bool enabled;
        Bool flush;
    };

}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

