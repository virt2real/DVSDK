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
 *  ======== Log.xs ========
 *
 *! Revision History
 *! ================
 *! 06-May-2009 cmcc    Fixed ROV bug SDOCM00057314
 *! 13-Feb-2008 sasha	ensured that desc.mask is 16-bit
 */

/*
 *  ======== lookupEventMessage ========
 *  Returns the format string for the event with the given id.
 */
function lookupEventMessage(eventId)
{
    var Program = xdc.useModule('xdc.rov.Program');
    
    /* Get the Log module's configuration object. */
    var cfg = Program.getModuleConfig('xdc.runtime.Log');
    
    if (cfg.idToInfo["#" + eventId] == undefined) {
        return ("<ERROR: No message found for eventId #" + eventId + ">");
    }
    else {
        return (cfg.idToInfo["#" + eventId].split('::')[1]);
    }
}

/*
 *  ======== getTargetArgSize ========
 *  Returns the target size of a record argument in bytes (not MAUs).
 */
function getTargetArgSize()
{
    /* Guaranteed to be 4 bytes on all targets. */
    return (4);
}
	
/*
 *  ======== lookupEventName ========
 */
function lookupEventName(eventId)
{
    var Program = xdc.useModule('xdc.rov.Program');
    
    /* Get the Log module's configuration object. */
    var cfg = Program.getModuleConfig('xdc.runtime.Log');
    
    if (cfg.idToInfo["#" + eventId] != undefined) {
        return (cfg.idToInfo["#" + eventId].split('::')[0]);
    }
    else if (info.eventId == 0) {
        return ("Log_print");
    }
    else {
        return ("Unrecognized event id: " + eventId);
    }
}

/*
 *  ======== lookupModuleName ========
 */
function lookupModuleName(modId)
{
    var Program = xdc.useModule('xdc.rov.Program');
    
    return (Program.moduleIdToName(modId));
}

/*
 *  ======== getTargetEventRecSize ========
 *  Returns the record size in bytes (not MAUs).
 */
function getTargetEventRecSize()
{
    var Log = xdc.useModule('xdc.runtime.Log');
    
    var bytesPerMau = Program.build.target.bitsPerChar / 8;
        
    return (Log.EventRec.$sizeof() * bytesPerMau);
}

/*
 *  ======== Event$alignof ========
 *  Return alignment required for an encoded value of an EventDesc
 */
function Event$alignof()
{
    return (Program.build.target.stdTypes.t_Int32.align);
}

/*
 *  ======== Event$encode ========
 *  Return a C expression that evaluates to the encoded value of an EventDesc
 */
function Event$encode(desc)
{
    var encodedDesc = "0";
    if (desc) {
        encodedDesc = "(((xdc_runtime_Log_Event)" + desc.$private.id
            + ") << 16 | " + (desc.mask & 0xFFFF) + ")";
    }
    return (encodedDesc);
}

/*
 *  ======== Event$sizeof ========
 *  Return sizeof the encoded value of an EventDesc
 */
function Event$sizeof()
{
    return (Program.build.target.stdTypes.t_Int32.size);
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(obj, params)
{
    var Text = xdc.module('xdc.runtime.Text');
    var Diags = xdc.module('xdc.runtime.Diags');

    for each (var mod in Program.targetModules()) {

        if (mod.PROXY$) {
            continue;
        }

        /* "inherit" the default logger */
        mod.Module__loggerObj = mod.common$.logger;
        if (mod.common$.logger) {
            var cn = mod.common$.logger.$orig.$module.$name.replace(/\./g, '_');
            mod.Module__loggerFxn4 = $externFxn(cn + '_write4__E');
            mod.Module__loggerFxn8 = $externFxn(cn + '_write8__E');
            mod.Module__loggerDefined = true;
        }

        Program.freezeRomConfig(mod.$name, 'Module__loggerFxn4');
        Program.freezeRomConfig(mod.$name, 'Module__loggerFxn8');
        Program.freezeRomConfig(mod.$name, 'Module__loggerDefined');

        /* create an Id for all Log_Event's declared in the module */
        if ('$$logEvtCfgs' in mod && mod.$$logEvtCfgs.length > 0) {
            for each (var cn in mod.$$logEvtCfgs) {
                var desc = mod[cn];
                desc.$private.id = Text.defineRopeCord(desc.msg);
                
                /* TODO: what if id already exists!? */
                this.idToInfo["#" + desc.$private.id] = mod.$name + '.' + cn +
                    '::' + desc.msg;
            }
        }

        /* generate log event ids for loggable fxns in the module */
        var res = null;
        if ('$$loggables' in mod && mod.$$loggables.length > 0) {
            res = "";
            var sep = "";
            var id;
            var msg;
            var desc;
            for each (var fxn in mod.$$loggables) {
                res += sep;
                sep = ",";
                res += fxn.name;

                if (query(mod, 'ENTRY')) {
                    msg = "--> " + fxn.name + ": (" + fxn.entry + ")";
                    desc = new this.EventDesc({msg: msg});
                    id = Text.defineRopeCord(msg);
                    this.idToInfo['#' + id] = mod.$name + '.' + fxn.name +
                        '$ENTRY' + '::' + desc.msg;
                    desc.$private.id = id;
                    id = (id << 16) | Diags.ENTRY;
                }
                else {
                    id = 0;
                }
                res += ":" + id;

                if (query(mod, 'EXIT')) {
                    msg = "<-- " + fxn.name + ": " +
                        (fxn.exit ? fxn.exit : "void");
                    desc = new this.EventDesc({msg: msg});
                    id = Text.defineRopeCord(msg);
                    this.idToInfo['#' + id] = mod.$name + '.' + fxn.name +
                        '$EXIT' + '::' + desc.msg;
                    desc.$private.id = id;
                    id = (id << 16) | Diags.EXIT;
                }
                else {
                    id = 0;
                }
                res += ":" + id;
            }
        }

        /* record any generated event id's in module
         *    $$fxnEvtIds = "fxn_name:enter_id:exit_id,..."
         */
        mod.$$bind('$$fxnEvtIds', res);
    }
}

/*
 *  ======== query ========
 */
function query(mod, dl)
{
    var Defaults = xdc.module('xdc.runtime.Defaults');
    var Diags = xdc.module('xdc.runtime.Diags');

    var sel = 'diags_' + dl;
    
    return (mod.common$[sel] === undefined
        ? (Defaults.common$[sel] != Diags.ALWAYS_OFF)
            : (mod.common$[sel] != Diags.ALWAYS_OFF));
}

/*
 *  ======== validate ========
 */
function validate()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    var Diags = xdc.module('xdc.runtime.Diags');

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];

        /* check all Log_Event's declared in any module */
        if ('$$logEvtCfgs' in mod && mod.$$logEvtCfgs.length > 0) {
            for each (var cn in mod.$$logEvtCfgs) {
                var desc = mod[cn];

                /* check that mask is within UInt16 range */
                if (desc.mask < 0) {
                    this.$logError("value of 'mask' must be non-negative",
                        mod, cn);
                }
                else if (desc.mask > 0xFFFF) {
                    this.$logError("value of 'mask' must be at most 16 bits",
                        mod, cn);
                }
            }
        }
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

