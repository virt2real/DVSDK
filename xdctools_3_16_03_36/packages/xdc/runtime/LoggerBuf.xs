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
 *  ======== LoggerBuf.xs ========
 *
 *! Revision History
 *! ================
 *! 08-Jun-2009 sasha	fixed ECL279338
 *! 14-Apr-2008 cmcc    Fixed timestamp in ROV view, CQ56660
 *! 05-Mar-2008 sasha	fixed CQ24033
 *! 25-Feb-2008 sasha	added conditional call to useModule for Memory
 *! 13-Jun-2007	nitya	Hook flushAllInternal by calling System.atexitMeta
 *! 18-Apr-2007 nitya   if enableFlush=true increment System.maxAtexithandlers
 *! 22-Mar-2007 rt      Incorporated LoggerBufAtomic concepts from avala-e02
 */

var Logger = null;

/*
 *  ======== module$use ========
 */
function module$use()
{
    var System = xdc.useModule('xdc.runtime.System');
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Types = xdc.module('xdc.runtime.Types');
    var Timestamp = xdc.module('xdc.runtime.Timestamp');

    Logger = this;
    if (Logger.enableFlush) {
        System.atexitMeta(Logger.flushAllInternal);
    }
    
    /* bind LoggerBuf.TimestampProxy to whatever Timestamp is using,
     * unless LoggerBuf.TimestampProxy was set already.
     */
    if (Logger.TimestampProxy == null) {
        Logger.TimestampProxy = Timestamp.SupportProxy.delegate$;
    }

    /* Memory module is needed only if memoryPolicy is not STATIC_POLICY. */
    if (Defaults.getCommon(Logger, "memoryPolicy") != Types.STATIC_POLICY) {
        xdc.useModule('xdc.runtime.Memory');
    }
    
    
    /* disable trace on timestamp proxy to prevent recursive callbacks */
    var Diags = xdc.module("xdc.runtime.Diags");
    var modName = Logger.TimestampProxy.delegate$.$name;
    Diags.setMaskMeta(modName, Diags.ALL & (~Diags.ASSERT), Diags.ALWAYS_OFF);
}

/*
 *  ======== instance$static$init ========
 */
function instance$static$init(obj, prms)
{
    /*
     * Note: not really needed in static case since the app
     * should not free this object. Here for completeness.
     */
    obj.bufHeap = null;

    obj.enabled = false;
    obj.flush = prms.exitFlush;
    obj.entryArr.length = prms.numEntries;
    obj.curEntry = obj.entryArr.$addrof(0);
    obj.readEntry = obj.entryArr.$addrof(0);
    obj.endEntry = obj.entryArr.$addrof(prms.numEntries - 1);
    obj.advance = Number(prms.bufType);
    obj.numEntries = prms.numEntries;
    obj.serial = 1;

    /*
     *  The following will place a memory buffer into section name. This
     *  buffer is the memory that this instance will manage.
     */
    var Memory = xdc.module('xdc.runtime.Memory');
    Memory.staticPlace(obj.entryArr, 0, prms.bufSection);
}

/*
 *  ======== getMetaArgs ========
 *  Returns meta data to support stop-mode RTA.
 */
function getMetaArgs(inst, instNum)
{
    var LoggerBuf = xdc.module('xdc.runtime.LoggerBuf');
    
    /* Create a new StopModeData structure to populate. */
    var data = new LoggerBuf.StopModeData();
    data.bufferSymbol = "xdc_runtime_LoggerBuf_Instance_State_" + 
                       instNum + "_entryArr__A";;
    data.bufferSize = inst.numEntries * LoggerBuf.Entry.$sizeof();
    
    return (data);
}
 
/*
 *  ======== viewInitBasic ========
 *  Initializes the 'Basic' ROV instance view.
 */
function viewInitBasic(view, obj)
{
    var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
    
    /* Retrieve the LoggerBuf instance's name */
    view.label = Program.getShortName(obj.$label);
    
   /* 
     * Determine the serial number of the last record, convert it to a
     * sequential number.
     */
    view.lastSerial = ((obj.serial + 1) / 2) - 1;
    
    /* Display the configured number of entries. */
    view.numEntries = obj.numEntries;
    
    /* Determine the type of the LoggerBuf, FIXED or CIRCULAR. */
    if ((obj.advance == LoggerBuf.FULL) || 
        (obj.advance == Number(LoggerBuf.BufType_FIXED))) {
        view.type = "FIXED";
    }
    else {
        view.type = "CIRCULAR";
    }
    
    /* Show whether the LoggerBuf instance is currently enabled. */
    view.enabledFlag = obj.enabled;
}

/*
 *  ======== viewInitRecords ========
 *  This function is called once per LoggerBuf instance.
 *
 *  The LoggerBuf 'Records' view leverages the LoggerBufDecoder class so it
 *  uses the same code as Stop-Mode RTA.
 */
function viewInitRecords(view, obj)
{
    xdc.loadPackage('xdc.runtime');
    xdc.loadPackage('xdc.rov');
    var Model = xdc.useModule('xdc.rov.Model');
    var Log = xdc.useModule('xdc.runtime.Log');
    var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
    var Program = xdc.useModule('xdc.rov.Program');
    
    /* Get the memory reader */
    var memReader = Model.getMemoryImageInst();
    
    /* Read the memory. */   
    
    /* Calculate the size of a record. Should be 32-bytes on all targets. */
    var bytesPerMau = Program.build.target.bitsPerChar / 8;
    var recSizeBytes = LoggerBuf.Entry.$sizeof() * bytesPerMau;
    
    /* Calculate the total size of the read. */
    var readSizeBytes = obj.numEntries * recSizeBytes;

    /* Read in the buffer */
    var buffer = memReader.readBytes(Number(obj.entryArr.$addr), readSizeBytes,
                                     true);
    
    /* Initialize the LoggerBufDecoder */
    var LBJava = LoggerBuf.initDecoder();
    
    /* Decode the buffer. This returns an array of xdc.rta.HostEvent objects */
    try {
        var events = LBJava.decodeBuffer(buffer, 0, buffer.length);
    }
    catch (e) {
        print("Caught exception while decoding buffer: " + e);
    }
    
    var eventViews = new Array();    
    
    /* 
     * Copy each of the HostEvent objects into a view element 
     * to be displayed. 
     */
    for (var i = 0; i < events.length; i++) {
        var evt = events[i];
        
        /* Create a new view element. */
        var evtView = Program.newViewStruct('xdc.runtime.LoggerBuf', 'Records');

        /* Fill in the element. */
        evtView.serial = evt.sequenceNum;
        evtView.timestampRaw = evt.timestamp;
        evtView.modName = evt.getModuleName();        
        evtView.text = evt.getEventMsg();
        evtView.eventId = evt.eventId;
        evtView.eventName = evt.getEventName();
        evtView.arg0 = evt.args[0];
        evtView.arg1 = evt.args[1];
        evtView.arg2 = evt.args[2];
        evtView.arg3 = evt.args[3];
        evtView.arg4 = evt.args[4];
        evtView.arg5 = evt.args[5];
        evtView.arg6 = evt.args[6];
        evtView.arg7 = evt.args[7];
        
        eventViews[eventViews.length] = evtView;
    }
    
    /* Populate the Program.InstDataView structure */
    view.label = Program.getShortName(obj.$label);
    if (view.label.equals("")) {
        view.label = String(obj.$addr);
    }
    
    view.elements = eventViews;    
}

/*
 *  ======== initDecoder ========
 *  Creates an instance of the xdc.runtime.LoggerBufDecoder class.
 *  The LoggerBuf 'Records' ROV view uses the LoggerBufDecoder class to decode
 *  the raw bytes into xdc.rta.HostEvent objects. This decoder is shared
 *  between this ROV view and stop mode RTA.
 */
function initDecoder()
{      
    var Program = xdc.useModule('xdc.rov.Program');
    var LoggerBuf = xdc.useModule('xdc.runtime.LoggerBuf');
    var Model = xdc.useModule('xdc.rov.Model');
    var Log = xdc.useModule('xdc.runtime.Log');
    
    /* Check if the decoder has already been created. */
    if (LoggerBuf.$private.LBJava != undefined) {
        return (LoggerBuf.$private.LBJava);
    }
   
    /* Get the IOFReader instance */
    var ofReader = Model.getIOFReaderInst();

    /* 
     * In order to decode the events in a LoggerBuf, the LoggerBufDecoder class
     * requires an object which implements the IEventMetaData interface to
     * provide log event information such as the mapping of an event id to 
     * the event's message. 
     *
     * For ROV, we create a JavaScript object which implements all of the APIs
     * in the IEventMetaData class, then place a Java wrapper on this so that
     * it can be called by the LoggerBufDecoder class.
     */
    var eventData = {
        getOFReader: 
            function() { 
                return (ofReader); 
            },
        lookupEventMessage: 
            function (eventId) { 
                return (Log.lookupEventMessage(eventId)); 
            },    
        getTargetArgSize: 
            function() {
                return (4); 
            },
        lookupEventName: 
            function(eventId) {
                return (Log.lookupEventName(eventId));
            },
        lookupModuleName: 
            function(modId) {
                return (Log.lookupModuleName(modId)); 
            },
        getTargetEventRecSize: 
            function() {
                return (32); 
            }
    };
        
    /* Create the Java wrapper for the IEventMetaData object. */    
    var jEventData = new Packages.xdc.rta.IEventMetaData(eventData);

    /* Required target information */
    var bitsPerChar = Program.build.target.bitsPerChar;    
    var endianStr = Program.build.target.model.endian;
    var endianess = xdc.jre.xdc.rov.TargetType.strToEndianess(endianStr);

    /* Create an instance of the LoggerBufDecoder */
    var LBJava = new Packages.xdc.runtime.LoggerBufDecoder(endianess,
                                                           bitsPerChar, 
                                                           jEventData);
    
    /* 
     * Store off the LoggerBufDecoder instance so we only have to create it
     * once.
     */
    LoggerBuf.$private.LBJava = LBJava;
    
    return (LBJava);
}

/*
 *  ======== validate ========
 *  This function is called by this package's validate() method (defined
 *  in package.xs).  
 */
function validate()
{
    /* this is the module's object */
    if (!this.$used) {
        return;
    }
    
    /* If Memory is not used, and the memory policy is not static, it is an
     * error.
     */
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Types = xdc.module('xdc.runtime.Types');
    if ((Defaults.getCommon(this, "memoryPolicy") != Types.STATIC_POLICY)
        && xdc.module('xdc.runtime.Memory').$used != true) {
        this.$logError("'common$.memoryPolicy' must be 'STATIC_POLICY' "
            + "when 'xdc.runtime.Memory' is not used", this, 
            "common$.memoryPolicy");  
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

