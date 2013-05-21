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
 *  ======== SysStd.c ========
 */
 
#include <xdc/std.h>

#include <stdio.h>
#include <stdlib.h>

#include "package/internal/SysStd.xdc.h"

/*
 *  ======== SysStd_abort ========
 */
Void SysStd_abort(String str)
{
    Char ch;
   
    if (str != NULL) {
        while ((ch = *str++) != '\0') {
            putchar(ch);
        }
    }
    fflush(stdout);
}

/*
 *  ======== SysStd_exit ========
 */
Void SysStd_exit(Int stat)
{
    fflush(stdout);
}

/*
 *  ======== SysStd_putch ========
 */
Void SysStd_putch(Char ch)
{
    putchar(ch);
}

/*
 *  ======== SysStd_flush ========
 */
Void SysStd_flush()
{
    fflush(stdout);
}

/*
 *  ======== SysStd_ready ========
 */
Bool SysStd_ready()
{
    return (TRUE);
}

/*
 *! Revision History
 *! ================
 *! 10-Jul-2007 toddm   flush on on exit and abort.
 *! 13-Jun-2007 nitya   Don't call rts functions.
 *! 08-Jun-2007 nitya   handle string in abort()
 *! 15-May-2007 toddm	Added flush
 *! 28-Nov-2006 toddm	Start revision history
 */
 
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

