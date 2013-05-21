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
 *  ======== SysMin.c ========
 */

#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Gate.h>

#include <string.h>

#include "package/internal/SysMin.xdc.h"

/*
 *  ======== SysMin_Module_startup ========
 */
Int SysMin_Module_startup(Int phase)
{
    if (SysMin_bufSize != 0) {
        memset(module->outbuf, 0, SysMin_bufSize);
    }
    return (Startup_DONE);
}

/*
 *  ======== SysMin_abort ========
 */
Void SysMin_abort(String str)
{
    Char ch;    
    
    if (SysMin_bufSize != 0) {
        if (str != NULL) {
            while ((ch = *str++) != '\0') {
                SysMin_putch(ch);
            }
        }

        /* Only flush if configured to do so */
        if (SysMin_flushAtExit) {
            SysMin_flush();
        }
    }
}

/*
 *  ======== SysMin_exit ========
 */
Void SysMin_exit(Int stat)
{
    if ((SysMin_flushAtExit) && (SysMin_bufSize != 0)) {
        SysMin_flush();
    }
}

/*
 *  ======== SysMin_putch ========
 */
Void SysMin_putch(Char ch)
{
    IArg key;
    
    if (SysMin_bufSize != 0) {

        key = Gate_enterSystem();

        if (module->outidx == SysMin_bufSize) {
            module->outidx = 0;
            module->wrapped = TRUE;
        }

        module->outbuf[module->outidx++] = ch;

        Gate_leaveSystem(key);
    }    
}

/*
 *  ======== SysMin_ready ========
 */
Bool SysMin_ready()
{
    /* 
     * Return bufsize here so that when called by System
     * this function gets inlined and helps eliminate code;
     * SysMin_bufSize == 0 => SysMin_ready() == FALSE => functions
     * called only when SysMin_ready() is TRUE can be eliminated(!).
     */
    return (SysMin_bufSize);
}

/*
 *  ======== SysMin_flush ========
 *  Called during SysMin_exit, System_exit or System_flush.
 */
Void SysMin_flush()
{
    IArg key;
    
    key = Gate_enterSystem();
    
    /*
     *  If a wrap occured, we need to flush the "end" of the internal buffer
     *  first to maintain fifo character output order.
     */    
    if (module->wrapped == TRUE) {
        SysMin_outputFunc(module->outbuf + module->outidx,
                          SysMin_bufSize - module->outidx);
    }
    
    SysMin_outputFunc(module->outbuf, module->outidx);
    module->outidx = 0;
    module->wrapped = FALSE;
    
    Gate_leaveSystem(key);
}

/*
 *! Revision History
 *! ================
 *! 24-Jul-2007 toddm   Code review comments. Removed user fxns and added
 *!                     startup
 *! 10-Jul-2007 toddm   flush on on exit and abort.
 *! 13-Jun-2007 nitya   Don't call rts functions.
 *! 08-Jun-2007 nitya   Fixed  17953: Review update
 *! 21-May-2007 cmcc    Fixed generated output function for ROM.
 *! 15-May-2007 toddm	Added template for making HOSTwrite or fwrite call.
                        Also made SysMin gated and added flush interface
 *! 23-Mar-2007 toddm	Added config and HOSTwrite fix
 *! 28-Nov-2006 toddm	Start revision history
 */
 
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

