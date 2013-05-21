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
 *  ======== LoggerBuf.c ========
 */

#include <xdc/runtime/Error.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Log.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/Startup.h>
#include <xdc/runtime/Types.h>

#include <stdlib.h>
#include <string.h>

#include "package/internal/LoggerBuf.xdc.h"

/*
 *  ======== LoggerBuf_instanceStartup ========
 */
Void LoggerBuf_instanceStartup(LoggerBuf_Object *obj)
{
    LoggerBuf_reset(obj);
}

/*
 *  ======== Log_Module_startup ========
 */
Int LoggerBuf_Module_startup(Int phase)
{
    Int i;

    /* loop over all "permanent" instances and initialize them */
    for (i = 0; i < LoggerBuf_Object_count(); i++) {
        LoggerBuf_instanceStartup(LoggerBuf_Object_get(NULL, i));
    }

    return (Startup_DONE);
}

/*
 *  ======== Instance_init =========
 */
Int LoggerBuf_Instance_init(LoggerBuf_Object *obj,
    const LoggerBuf_Params *prms, Error_Block *eb)
{
    obj->entryArr = Memory_alloc(prms->bufHeap,
            prms->numEntries * sizeof (LoggerBuf_Entry), 0, eb);

    if (obj->entryArr != NULL) {
        obj->flush = prms->exitFlush;
        obj->bufHeap = prms->bufHeap;
        obj->numEntries = prms->numEntries;
        obj->endEntry = obj->entryArr + (prms->numEntries - 1);
    
        /*
         * The following are set in instanceStartup():
         * obj->serial = 1;
         * obj->curEntry = obj->entryArr;
         * obj->readEntry = obj->entryArr;
         * obj->enabled = TRUE;
         */
        LoggerBuf_instanceStartup(obj);
    }

    return (0);        /* status passed to finalize on error */
}

/*
 *  ======== LoggerBuf_Instance_finalize ========
 */
Void LoggerBuf_Instance_finalize(LoggerBuf_Object *obj, Int status)
{
    if (obj->entryArr != NULL) {
        Memory_free(obj->bufHeap, obj->entryArr,
                    obj->numEntries * sizeof (LoggerBuf_Entry));
    }
}

/*
 *  ======== LoggerBuf_enable ========
 */
Bool LoggerBuf_enable(LoggerBuf_Object *obj)
{
    Bool prev = obj->enabled;
    obj->enabled = TRUE;
    return (prev);
}

/*
 *  ======== LoggerBuf_disable ========
 */
Bool LoggerBuf_disable(LoggerBuf_Object *obj)
{
    Bool prev = obj->enabled;
    obj->enabled = FALSE;
    return (prev);
}

/*
 *  ======== LoggerBuf_reset ========
 */
Void LoggerBuf_reset(LoggerBuf_Object *obj)
{
    memset(obj->entryArr, 0, obj->numEntries * sizeof (LoggerBuf_Entry));

    obj->serial = 1;
    obj->curEntry = obj->entryArr;
    obj->readEntry = obj->entryArr;
    obj->enabled = TRUE;
}

/*
 *  ======== write4 =========
 */
Void LoggerBuf_write4(LoggerBuf_Object *obj, Types_Event evt,
    IArg a1, IArg a2, IArg a3, IArg a4)
{
    IArg key;
    Int adv;
    Int32 ser;
    LoggerBuf_Entry *e;

    if (!obj->enabled) {
        return;
    }

    key = Gate_enterModule();

    /*
     * Record new serial number even if the buffer is FULL.  We do this
     * because a reader (decoder) of the buffer needs to know if events
     * have been missed, and the buffer might become un-FULL at some
     * later time.
     */
    ser = obj->serial;
    obj->serial += 2;

    adv = obj->advance;
    if (adv == LoggerBuf_FULL) {
        goto leave;
    }

    e = obj->curEntry;

    if (e == obj->endEntry) {
        if (adv == LoggerBuf_WRAP) {
            obj->curEntry = obj->entryArr;
        }
        else {
            obj->advance = LoggerBuf_FULL;
        }
    }
    else {
        obj->curEntry = e + 1;
    }

    LoggerBuf_TimestampProxy_get64(&e->tstamp);

    e->serial = ser;
    e->evt = evt;
    e->arg1 = a1;
    e->arg2 = a2;
    e->arg3 = a3;
    e->arg4 = a4;

leave:
    Gate_leaveModule(key);
}

/*
 *  ======== write8 =========
 *
 *  Odd serial numbers indicate a new record, even serial numbers indicate
 *  an "extension" to the previous record.  0 is a sentinal for no record,
 *  but only if it doesn't follow a -1 (0xffffffff).  If a serial number
 *  of 0 follows a serial number of 0xffffffff, it's an extension, otherwise
 *  it's a "no record".
 */
Void LoggerBuf_write8(LoggerBuf_Object *obj, Types_Event evt,
    IArg a1, IArg a2, IArg a3, IArg a4, IArg a5, IArg a6, IArg a7, IArg a8)
{
    /* part1 */
    
    IArg key;
    Int adv;
    Int32 ser;
    LoggerBuf_Entry *e;

    if (!obj->enabled) {
        return;
    }

    key = Gate_enterModule();

    /*
     * Record new serial number even if the buffer is FULL.  We do this
     * because the buffer might become un-FULL at some later time, and
     * a reader (decoder) of the buffer needs to know if events have
     * been missed.
     */
    ser = obj->serial;
    obj->serial += 2;

    adv = obj->advance;
    if (adv == LoggerBuf_FULL) {
        goto leave;
    }

    e = obj->curEntry;
    if (e == obj->endEntry) {
        if (adv == LoggerBuf_WRAP) {
            obj->curEntry = obj->entryArr;
        }
        else {
            obj->advance = LoggerBuf_FULL;
        }
    }
    else {
        obj->curEntry = e + 1;
    }

    LoggerBuf_TimestampProxy_get64(&e->tstamp);

    e->serial = ser;
    e->evt = evt;
    e->arg1 = a1;
    e->arg2 = a2;
    e->arg3 = a3;
    e->arg4 = a4;

    /* part 2 */

    /*
     * We intentionally don't check for a "new" FULL condition here
     * since we want to write only the "extension" record, so a decoder
     * can know that this is an incomplete record and therefore throw
     * it away.  By not checking for FULL here, we end up just overwriting
     * the "starter" record (that was written above) of a two-entry record
     * with the "extension" record.
     */

    e = obj->curEntry;
    if (e == obj->endEntry) {
        if (adv == LoggerBuf_WRAP) {
            obj->curEntry = obj->entryArr;
        }
        else {
            obj->advance = LoggerBuf_FULL;
        }
    }
    else {
        obj->curEntry = e + 1;
    }

    e->serial = ser + 1;
    e->evt = ~0;
    e->arg1 = a5;
    e->arg2 = a6;
    e->arg3 = a7;
    e->arg4 = a8;

leave:
    Gate_leaveModule(key);
}

/*
 *  ======== LoggerBuf_flushAll ========
 */
Void LoggerBuf_flushAll()
{
    Int i;
    LoggerBuf_Object *obj;

    /* flush static instances */
    for (i = 0; i < LoggerBuf_Object_count(); i++) {
        obj = LoggerBuf_Object_get(NULL, i);
        if (obj->flush) {
            LoggerBuf_flush(obj);
        }
    }
    
    /* flush dynamic instances */
    
    /* loop over all dynamic instances */
    for (obj = LoggerBuf_Object_first(); obj != NULL;) {
        if (obj->flush) {
            LoggerBuf_flush(obj);               /* flush obj */
        }
        obj = LoggerBuf_Object_next(obj);   /* get next instance after 'obj' */
    }
}

/*
 *  ======== LoggerBuf_flushAllInternal ========
 */
Void LoggerBuf_flushAllInternal(Int stat)
{
     LoggerBuf_flushAll();
}

/*
 *  ======== LoggerBuf_flush ========
 */
Void LoggerBuf_flush(LoggerBuf_Object *obj)
{
    Int nEntries;
    Log_EventRec evtRec;
    
    /* 'counter' is the maximum number of entries we want to print. Otherwise,
     * we could end up in an infinite loop if events are being generated
     * faster than they are being printed.
     */
    Int counter = obj->numEntries;
    
    for (;;) {
        nEntries = LoggerBuf_getNextEntry(obj, &evtRec);
        if (counter == 0 || nEntries == 0) {
            break;
        }
        else {
            if (nEntries != -1) {
                Log_doPrint(&evtRec);
                counter--;
            }
        }
    }
}

/*
 *  ======== LoggerBuf_getNextEntry ========
 *  "atomically" read and clear the next entry in the log
 *
 *  Returns:
 *      0   - no entry in the log
 *      1,2 - read one or two complete entries (write4, write8)
 *      -1  - read one but there may be another
 *
 *  Below are some notes on the implementation.
 *
 *  Pointers:
 *  - cureEntry points to the next entry to write
 *  - endEntry points to the last entry (not past it)
 *  - readEntry points to the entry that will be read on the next call to
 *    getNextEntry. 
 *
 *  Edge cases:
 *  - An extension record can be orphaned (the base can be missing)
 *  - A base record cannot be missing its extension (the records are written in
 *    order, so the base is always overwritten first)
 *  - The serial number can wrap from 0xFFFFFFFF to 0x0.
 *  - If a base record is at the end of the buffer, its extension may be at
 *    the beginning.
 */
Int LoggerBuf_getNextEntry(LoggerBuf_Object *obj, Log_EventRec *evtRec)
{
    LoggerBuf_Entry *ent;
    LoggerBuf_Entry *nextEnt;
    Int nEntries;
    Bits32 serA;
    IArg key;

    nEntries = 0;

    key = Gate_enterModule();

    ent = obj->readEntry;

    serA = ent->serial;
    if ((serA & 1) != 0) {
        /* serial numbers are odd and start at 1 */
        nEntries++;

        /* reduce two-spaced serial numbers to consecutive ints */
        evtRec->serial = (serA + 1) / 2;
        evtRec->evt = ent->evt;
        evtRec->tstamp = ent->tstamp;
        evtRec->arg[0] = ent->arg1;
        evtRec->arg[1] = ent->arg2;
        evtRec->arg[2] = ent->arg3;
        evtRec->arg[3] = ent->arg4;

        memset(ent, 0, sizeof (LoggerBuf_Entry));

        /* get pointer to next entry */
        if (ent == obj->endEntry) {
            nextEnt = obj->entryArr;
        }
        else {
            nextEnt = ent + 1;
        }

        if (nextEnt->serial == (serA + 1)) {

            /* continuation record */
            nEntries++;

            evtRec->arg[4] = nextEnt->arg1;
            evtRec->arg[5] = nextEnt->arg2;
            evtRec->arg[6] = nextEnt->arg3;
            evtRec->arg[7] = nextEnt->arg4;

            memset(nextEnt, 0, sizeof (LoggerBuf_Entry));

            /* get pointer to next entry */
            if (nextEnt == obj->endEntry) {
                nextEnt = obj->entryArr;
            }
            else {
                nextEnt += 1;
            }
        }
        else {
            evtRec->arg[4] = 0;
            evtRec->arg[5] = 0;
            evtRec->arg[6] = 0;
            evtRec->arg[7] = 0;
        }
    }
    else {
        /*
         * readEntry has an even sequence number, so it's either an
         * incomplete record, or it's empty.  If it's incomplete, we
         * need to toss it by advancing readEntry, but if it's empty
         * we want to do nothing.  We need to be able to distinguish
         * between an incomplete "extension" record that has a serial
         * number of 0 (since it's base record was 0xffffffff) and
         * an empty record, and we do this by checking the evt field,
         * which gets set to ~0 for extension records in write8.
         */
        if ((ent->evt == 0) && (ent->serial == 0)) {
            /* empty record, don't advance read pointer */
            nextEnt = obj->readEntry;
        }
        else if (ent->evt == ~0) {
            /* extension record */
            /* return -1 to indicate there may be more to go */
            nEntries = -1;

            if (ent == obj->endEntry) {
                nextEnt = obj->entryArr;
            }
            else {
                nextEnt = ent + 1;
            }
        }
        else {
            /* return -1 to indicate there may be more to go */
            nEntries = -1;

            /* bogus extension record, clear & advance read pointer */
            memset(ent, 0, sizeof (LoggerBuf_Entry));

            if (ent == obj->endEntry) {
                nextEnt = obj->entryArr;
            }
            else {
                nextEnt = ent + 1;
            }
        }
    }

    obj->readEntry = nextEnt;

    Gate_leaveModule(key);

    return (nEntries);
}

/*
 *! Revision History
 *! ================
 *! 06-May-2009 cmcc     Fixed SDOCM00057436, does not break ROM compatibility
 *! 10-Mar-2008 sasha    Fixed SDSCM00019143
 *! 06-Feb-2008 nitya    Fixed SDSCM00020682 
 *! 13-Jun-2007 nitya    Fixed bug in getNextEntry(). Plug flushAll in xs file
 *! 08-Jun-2007 nitya    Fixed bug in flush(). Hook atexit func in xs file.
 *! 18-Apr-2007 nitya    Use System_atexit() instead of atexit()
 */
 
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

