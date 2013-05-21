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
 *  ======== SyncGeneric.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>

#include "package/internal/SyncGeneric.xdc.h"

/*
 *  ======== SyncGeneric_query ========
 */
Bool  SyncGeneric_query(SyncGeneric_Object *obj, Int qual)
{
    if (obj->userQuery) {
        return (obj->userQuery(qual));
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== SyncGeneric_Instance_init ========
 */
Void  SyncGeneric_Instance_init(SyncGeneric_Object *obj, 
    const SyncGeneric_Params *params)
{
    obj->userSignal = params->userSignal ;   
    obj->signalArg = params->signalArg;   
    obj->userWait = params->userWait; 
    obj->waitArg = params->waitArg;
    obj->userQuery = params->userQuery;
}

/*
 *  ======== SyncGeneric_wait ========
 */
/* ARGSUSED */
Int SyncGeneric_wait(SyncGeneric_Object *obj, UInt timeout, Error_Block *eb)
{
    if (obj->userWait) {
        return (obj->userWait(obj->waitArg, timeout));
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== SyncGeneric_signal ========
 */
Void SyncGeneric_signal(SyncGeneric_Object *obj)
{
    if (obj->userSignal) {
        obj->userSignal(obj->signalArg);
    }
}

/*
 *! Revision History
 *! ================
 *! 07-Feb-2008    nitya    created
 */

/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

