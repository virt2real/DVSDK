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
 *  ======== TimestampNull.c ========
 */

#include <xdc/std.h>
#include <xdc/runtime/Types.h>

#include "package/internal/TimestampNull.xdc.h"

/*
 *  ======== TimestampNull_get32 ========
 */
Bits32 TimestampNull_get32()
{
    return (~0);
}

/*
 *  ======== TimestampNull_get64 ========
 */
Void TimestampNull_get64(Types_Timestamp64 *result)
{
    result->lo = result->hi = ~0;
}

/*
 *  ======== TimestampNull_getFreq ========
 */
Void TimestampNull_getFreq(Types_FreqHz *freq)
{
    freq->lo = freq->hi = 0;
}

/*
 *! Revision History
 *! ================
 *! 14-Dec-2007 sasa   added xdc/std.h
 */
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:59; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

