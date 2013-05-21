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
 *  ======== SyncNull.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Error.h>
#include "package/internal/SyncNull.xdc.h"

/*
 *  ======== SyncNull_query ========
 */
/* ARGSUSED */
Bool  SyncNull_query(SyncNull_Object *obj, Int qual)
{
    return (FALSE);
}

/*
 *  ======== SyncNull_wait ========
 */
/* ARGSUSED */
Int SyncNull_wait(SyncNull_Object *obj, UInt timeout, Error_Block *eb)
{
    return (FALSE);
}

/*
 *  ======== SyncNull_signal ========
 */
/* ARGSUSED */
Void SyncNull_signal(SyncNull_Object *obj)
{
}


/*
 *! Revision History
 *! ================
 *! 07-Feb-2008    nitya    created
 */

/*
 *  @(#) xdc.runtime.knl; 1, 0, 0,46; 2-22-2010 10:33:52; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

