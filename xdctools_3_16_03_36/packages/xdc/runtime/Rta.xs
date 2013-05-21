/*
 *  ======== genRta ========
 */
function genRta(outputFileName)
{
    var file = new java.io.File(outputFileName);
    file["delete"]();
    var out = new java.io.FileWriter(outputFileName);
    out = new java.io.BufferedWriter(out);

    var rts = xdc.om['xdc.runtime'];

    var data = new rts.Types.RtaDecoderData;
    data.targetName = Program.build.target.$name;
    data.binaryParser = Program.build.target.binaryParser;

    /* 
     * Add all instances of modules which implement ILogger to the meta data.
     * This list is primarily used for supporting control commands.
     */
    var ILogger = xdc.module('xdc.runtime.ILogger');
    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];
        
        /* If this module implements the ILogger interface. */
        if (mod instanceof ILogger.Module) {
            /* Add each of the module's instances. */
            for (var j = 0; j < mod.$instances.length; j++) {
                addLoggerInst(data, mod, mod.$instances[j].$orig, j);
            }
            
            /* get emebdded loggers too */
            for (var j = 0; j < mod.$objects.length; j++) {
                addLoggerInst(data, mod, mod.$objects[j].$orig, j);
            }
        }
    }
    
    /*
     * For each module, store the logger associated with it and its initial
     * diags configuration.
     */
    var targetModules = Program.targetModules();
    for (var i = 0; i < targetModules.length; i++) {
        var mod = targetModules[i];
        if (!mod.PROXY$) {

            var loggerInst = "";
            if (mod.common$.logger == null) {
                loggerInst = "null";
            }
            else if (mod.common$.logger.$orig.instance.name) {
                loggerInst = mod.common$.logger.$orig.instance.name;
            }
            else {
                loggerInst = String(mod.common$.logger.$orig);
            }

            data.modMap[mod.$name] = {
                id: mod.Module__id,
                logger: loggerInst,
                /*
                 * Mask has the form EXLIA00012345678, with 3 unused bits
                 * between Assert and User1
                 */
                diagsMask: String(Number(mod.common$.diags_ENTRY)) +
                       String(Number(mod.common$.diags_EXIT)) +
                       String(Number(mod.common$.diags_LIFECYCLE)) +
                       String(Number(mod.common$.diags_INTERNAL)) +
                       String(Number(mod.common$.diags_ASSERT)) +
                       "000" +
                       String(Number(mod.common$.diags_USER1)) +
                       String(Number(mod.common$.diags_USER2)) +
                       String(Number(mod.common$.diags_USER3)) +
                       String(Number(mod.common$.diags_USER4)) +
                       String(Number(mod.common$.diags_USER5)) +
                       String(Number(mod.common$.diags_USER6)) +
                       String(Number(mod.common$.diags_USER7)) +
                       String(Number(mod.common$.diags_USER8))
            };
        }
    }

    /* Create the event map */
    for (var id in rts.Log.idToInfo) {
        var info = rts.Log.idToInfo[id].split('::');
        data.evtMap[info[0]] = {
            id: Number(id.substring(1)),
            msg: java.net.URLEncoder.encode(info[1], 'UTF-8')
        };
    }

    /* Target specific constants. */
    data.eventSize = rts.Log.EventRec.$sizeof();
    data.argSize = Program.build.target.stdTypes.t_IArg.size;

    data.bitsPerChar = Program.build.target.bitsPerChar;
    data.endian = Program.build.target.model.endian;

    out.write(String(data.$xml()));
    out.write('\n');

    out.close();
}
/*
 *  ======== addLoggerInst ========
 */
function addLoggerInst(data, mod, inst, index)
{    
    data.loggers.length++;
    
    var logger = {};
    
    /* Store the instance name if one was given. */
    if (inst.instance.name) {
        logger.name = inst.instance.name;
    }
    else {
        logger.name = String(inst);
    }
    
    /* Store the type of the logger instance. */
    logger.type = String(mod);
    
    /* Store the meta data provided for this logger instance. */
    var metaArgs = mod.getMetaArgs(inst, index);
    logger.metaArgs = metaArgs;
    
    /* Add the logger to the list */
    data.loggers[data.loggers.length - 1] = logger;
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

