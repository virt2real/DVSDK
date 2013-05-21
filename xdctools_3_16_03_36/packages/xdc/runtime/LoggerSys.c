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
 *  ======== LoggerSys.c ========
 */
#include <xdc/std.h>

#include <xdc/runtime/Log.h>
#include <xdc/runtime/Types.h>

#include "package/internal/LoggerSys.xdc.h"

/*
 *  ======== Instance_init =========
 */
Void LoggerSys_Instance_init(LoggerSys_Object *obj,
    const LoggerSys_Params *prms)
{
}

/*
 *  ======== write4 =========
 */
Void LoggerSys_write4(LoggerSys_Object *obj, Types_Event evt,
    IArg a1, IArg a2, IArg a3, IArg a4)
{
    LoggerSys_write8(obj, evt, a1, a2, a3, a4, 0, 0, 0, 0);
}

/*
 *  ======== write8 =========
 */
Void LoggerSys_write8(LoggerSys_Object *obj, Types_Event evt,
    IArg a1, IArg a2, IArg a3, IArg a4, IArg a5, IArg a6, IArg a7, IArg a8)
{
    Log_EventRec evrec;

    LoggerSys_TimestampProxy_get64(&evrec.tstamp);

    evrec.serial = 0;
    evrec.evt = evt;
    evrec.arg[0] = a1;
    evrec.arg[1] = a2;
    evrec.arg[2] = a3;
    evrec.arg[3] = a4;
    evrec.arg[4] = a5;
    evrec.arg[5] = a6;
    evrec.arg[6] = a7;
    evrec.arg[7] = a8;

    Log_doPrint(&evrec);
}

/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

