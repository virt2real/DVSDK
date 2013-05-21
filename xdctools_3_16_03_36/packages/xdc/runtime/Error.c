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
 *  ======== Error.c ========
 */

#include <xdc/runtime/Gate.h>
#include <xdc/runtime/System.h>
#include <xdc/runtime/Text.h>
#include <xdc/runtime/Types.h>

#include <string.h>

#include "package/internal/Error.xdc.h"

/*
 *  ======== Error_init ========
 */
Void Error_init(Error_Block *eb)
{
    if (eb) {
	memset(eb, 0, sizeof (Error_Block));
    }
}

/*
 *  ======== Error_check ========
 */
Bool Error_check(Error_Block *eb)
{
    return (Error_policy == Error_UNWIND && eb != NULL && eb->id != 0);
}

/*
 *  ======== Error_getData ========
 */
Error_Data *Error_getData(Error_Block *eb)
{
    return (&eb->data);
}

/*
 *  ======== Error_getCode ========
 */
UInt16 Error_getCode(Error_Block *eb)
{
    return (Error_idToCode(eb->id));
}

/*
 *  ======== Error_getId ========
 */
Error_Id Error_getId(Error_Block *eb)
{
    return (eb->id);
}

/*
 *  ======== Error_getMsg ========
 */
String Error_getMsg(Error_Block *eb)
{
    return (eb->msg);
}

/*
 *  ======== Error_getSite ========
 */
Types_Site *Error_getSite(Error_Block *eb)
{
    return (&eb->site);
}

/*
 *  ======== Error_print ========
 */
Void Error_print(Error_Block *eb)
{
    if (eb == NULL) {
        return;
    }

    if (eb->msg) {
        Text_putSite(Error_getSite(eb), NULL, -1);
        if (Text_isLoaded) {
            System_aprintf(eb->msg, eb->data.arg[0], eb->data.arg[1]);
        }
        else {
            System_aprintf("error {id:0x%x, args:[0x%x, 0x%x]}",
                eb->id, eb->data.arg[0], eb->data.arg[1]);
        }
        System_printf("\n");
    }
}

/*
 *  ======== Error_raiseX ========
 */
Void Error_raiseX(Error_Block *eb, Types_ModuleId mod, String file, Int line,
    Error_Id id, IArg arg1, IArg arg2)
{
    Error_Block defErr;
    IArg gateKey;
    UInt16 oldCount;

    if (eb == NULL) {
        eb = &defErr;
    }

    Error_init(eb);

    eb->data.arg[0] = arg1;
    eb->data.arg[1] = arg2;
    eb->id = id;
    eb->msg = Text_isLoaded ? Text_ropeText((Text_RopeId)(id >> 16)) : "";
    eb->site.mod = mod;
    eb->site.file = file;
    eb->site.line = line;
    
    gateKey = Gate_enterSystem();
    oldCount = module->count;
    module->count++;
    Gate_leaveSystem(gateKey);

    if (Error_raiseHook != NULL && oldCount < Error_maxDepth) {
        (Error_raiseHook)(eb);
    }

    if (Error_policy == Error_TERMINATE || eb == &defErr) {
        System_abort("xdc.runtime.Error.raise: terminating execution\n");
    }

    gateKey = Gate_enterSystem();
    module->count--;
    Gate_leaveSystem(gateKey);
}

/*
 *! Revision History
 *! ================
 *! 06-Feb-2008 nitya	Removed %$A from Error msgs.Use System_aprintf.
 */
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

