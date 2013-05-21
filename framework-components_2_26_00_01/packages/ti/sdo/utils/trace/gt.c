/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 * ======== gt.c ========
 */

#include <xdc/std.h>
#include <stdarg.h>
#include <string.h>

#ifdef _LINT_
#undef _LINT_
#endif

#include "gt.h"

#define GT_WILD '*'

#define GT_CLEAR        '='
#define GT_ON           '+'
#define GT_OFF          '-'

#define MAXMODNAMELENGTH 50

/* types/levels of prefix, that the user can set through
 * GT_set("GT_prefix=<level>")
 *  : nothing
 * 0: print calling module short name (after the last dot)
 * 1: print calling module name in original (long) form
 * 2: print trace call's class
 * 3: print thread ID
 * 4: print stack
 */
#define PREFIXMASK "GT_prefix"

#define PREFIX_SHORTNAME    1
#define PREFIX_LONGNAME     2
#define PREFIX_NAME         (PREFIX_LONGNAME | PREFIX_SHORTNAME)
#define PREFIX_CLASS        4
#define PREFIX_TID          8
#define PREFIX_STACK        16
#define PREFIX_TIMESTAMP    32

/* time formats, that the user can set through
 * GT_set("GT_time=<class>")
 *  : @0x:<microseconds in hex>:
 * 1: @<seconds>,<milliseconds>,<microseconds>us, e.g. @4,021,348us:
 * 2: <seconds>.<milliseconds>s                   e.g. @0.001s:
 * 3: +<milliseconds>,<microseconds>us -- delta from previous, not counting
 *    print time, e.g. @+0,000,259us:
 */
#define TIMEMASK      "GT_time"
#define TIME_USEC      1
#define TIME_SEC       2
#define TIME_DELTAUSEC 4
#define TIME_TICKS     8

typedef enum {
    GT_SEP,
    GT_NAME,
    GT_OP,
    GT_DIGITS
} State;

/* type for the linked list of module (name, flags) pairs */
typedef struct ModNameListElem {
    String modName;
    UInt8  flags;
    struct ModNameListElem *next;
} ModNameListElem;

static ModNameListElem *modNameList = NULL;

/* default prefix mask */
static UInt8 prefixMask = PREFIX_TIMESTAMP | PREFIX_TID | PREFIX_LONGNAME;

/* default time mask */
static UInt8 timeMask = 0;

/* initial mask for all modules (set when module name is "*") */
static UInt8 initModFlags = 0;

static Bool curInit = FALSE;
static String separator = " ,;/";

/* ID for the thread for which tracing is to be disabled; -1 means no one */
static Int idForDisabledThread = -1;

static Void applyOp(UInt8 *mask, Char op, UInt8 opMask);
static Bool addModName(String modName, UInt8 flags);
static ModNameListElem *findElem(String modName);
static Bool getModNameFlagsAddr(String modName, UInt8 **modNameFlagsAddr);
static Bool setModNameFlags(String modName, UInt8 flags);
static Void wildcardUpdate(String pattern, char op, UInt8 mask);
static Void error(String String);
static Void setMask(String modName, Char op, UInt8 mask);

/*
 *  ======== _GT_create ========
 *  purpose:
 *      Creates GT mask.
 */
Void _GT_create(GT_Mask *mask, String modName)
{
    UInt8 *modNameFlagsAddr;

    /* check if modName entry exists yet; if not, add it, setting its flags
     * to current "allmodnames" flags, i.e. ones set by the wildcard.
     */
    if (getModNameFlagsAddr(modName, &modNameFlagsAddr) == FALSE) {
        addModName(modName, initModFlags);
        getModNameFlagsAddr(modName, &modNameFlagsAddr);
    }

    mask->modName = modName;
    mask->flags   = modNameFlagsAddr;
}

/*
 *  ======== GT_curTime ========
 */
UInt32 GT_curTime(Void)
{
    return (GT->TIMEFXN != NULL ? GT->TIMEFXN() : 0);
}

/*
 *  ======== GT_disable ========
 *  temporarily disables all tracing, regardless of masks
 *  [dm]TODO:L this lets only one thread at a time to turn off its
 *  tracing, which is likely to be sufficient; otherwise, we should
 *  keep a list of threads with disabled flag, search the list at
 *  every trace, protect it... so, decide whether to implement all that
 *  or to remove this TODO.
 */
Void GT_disable(Void)
{
    idForDisabledThread = (GT->TIDFXN == NULL) ? 0 : (*GT->TIDFXN)();
}

/*
 *  ======== GT_disable ========
 *  enables all tracing back to what it was before disable()
 */
Void GT_enable(Void)
{
    idForDisabledThread = -1;
}

/*
 *  ======== GT_getModNameFlags ========
 */
Bool GT_getModNameFlags(String modName, UInt8 *flags)
{
    ModNameListElem *elem;

    elem = findElem(modName);
    if (elem != NULL) {
        *flags = elem->flags;
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== GT_init ========
 *  purpose:
 *      Initializes GT module.
 */
#ifdef GT_init
#undef GT_init
#endif
Void GT_init(void)
{
    if (!curInit) {
        curInit = TRUE;

        /* initialize the module providing GT functions like print */
        if (GT->INITFXN != NULL) {
            GT->INITFXN();
        }
    }
}

/*
 *  ======== _GT_set ========
 *  purpose:
 *      Sets the trace String format.
 */

Void _GT_set(String str)
{
    State   state;
    String  sep;
    Char    op = GT_CLEAR;
    Bool    maskValid;
    Int16   digit;
    Char    modName[MAXMODNAMELENGTH];
    Int     modNameLength = 0;
    UInt8   mask = 0x0;             /* no tracing */

    if (str == NULL) {
        return;
    }

    maskValid = FALSE;
    state = GT_SEP;
    while (*str != '\0') {
        switch ((Int)state) {

            case (Int)GT_SEP:
                maskValid = FALSE;
                sep = separator;
                while (*sep != '\0') {
                    if (*str == *sep) {
                        str++;
                        break;
                    }
                    else {
                        sep++;
                    }
                }
                if (*sep == '\0') {
                    state = GT_NAME;
                    modName[modNameLength = 0] = '\0';
                }
                break;

            case (Int)GT_NAME:
                if ( (*str >= 'A' && *str <= 'Z') ||
                     (*str >= 'a' && *str <= 'z') ||
                     (*str >= '0' && *str <= '9') ||
                     (*str == '.' || *str == '_') ||
                     (*str == GT_WILD)
                   ) {
                    if (modNameLength < MAXMODNAMELENGTH - 1) {
                        modName[modNameLength++] = *str;
                    }
                    str++;
                }
                else {
                    /* we assume anything else must be an operator */
                    modName[modNameLength] = '\0';
                    state = GT_OP;
                }
                break;

            case (Int)GT_OP:
                op = *str;
                mask = 0x0;     /* no tracing */
                switch (op) {
                    case (Int)GT_CLEAR:
                        maskValid = TRUE;
                    case (Int)GT_ON:
                    case (Int)GT_OFF:
                        state = GT_DIGITS;
                        str++;
                        break;
                    default :
                        state = GT_SEP;
                        break;
                }
                break;

            case (Int)GT_DIGITS:
                digit = (Int16)(*str - '0');
                if ((digit >= 0) && (digit <= 7)) {
                    mask |= (0x01 << digit);
                    maskValid = TRUE;
                    str++;
                }
                else {
                    if (maskValid == TRUE) {
                        setMask(modName, op, mask);
                        maskValid = FALSE;
                    }
                    state = GT_SEP;
                }
                break;
            default :
                error("illegal trace mask");
                break;
        }
    }

    if (maskValid) {
        modName[modNameLength] = '\0';
        setMask(modName, op, mask);
    }
}

/*
 *  ======== _GT_trace ========
 *  purpose:
 *      Prints the input String onto standard output
 */

Int _GT_trace(GT_Mask *mask, Int class, String format, ...)
{
    Int arg1, arg2, arg3, arg4, arg5, arg6;
    va_list va;
    Int tid = -1;
    Char *modName = mask->modName;
    Int classLevel = 0;
    UInt32 time;
    static UInt32 lastTime = 0;

    va_start(va, format);

    arg1 = va_arg(va, Int);
    arg2 = va_arg(va, Int);
    arg3 = va_arg(va, Int);
    arg4 = va_arg(va, Int);
    arg5 = va_arg(va, Int);
    arg6 = va_arg(va, Int);

    va_end(va);

    /* check if tracing is disabled for the current thread */
    if (idForDisabledThread != -1) {
        tid = (GT->TIDFXN == NULL) ? 0 : (*GT->TIDFXN)();
        if (tid == idForDisabledThread) {
            return (0);
        }
    }

    /* get thread ID if it is needed */
    if ((prefixMask & PREFIX_TID) && (tid == -1)) {
        tid = (GT->TIDFXN == NULL) ? 0 : (*GT->TIDFXN)();
    }

    /* acquire lock for the print */
    if (GT->LOCKFXN != NULL) {
        GT->LOCKFXN();
    }

    /* check if the prefix mask is the default one; if so, do it quickly */
    if (prefixMask == (PREFIX_TIMESTAMP | PREFIX_TID | PREFIX_LONGNAME)
        && timeMask == 0) {   /* "GT_prefix=134, GT_time=" */
        time = GT->TIMEFXN != NULL ? GT->TIMEFXN() : 0;
        (*GT->PRINTFXN)("@0x%08x:[T:0x%08x] %s - ", time, tid, modName);
    }
    else {
        /* otherwise, check if it's one of the several favorites and do them
         * quickly, too; if the current mask is a non-common one, build the
         * prefix from scratch
         */
        Uint8 tmpMask = prefixMask;

        /* redefine tmpMask to simplify checks below */
        if (tmpMask & PREFIX_NAME) {
            /* compute short name (if necessary) */
            if ((tmpMask & PREFIX_NAME) == PREFIX_SHORTNAME) {
                /* this should be pre-computed !!!! */
                Int lastWordPos;
                for (lastWordPos = strlen(modName);
                     (lastWordPos > 0) && (modName[lastWordPos - 1] != '.');
                     --lastWordPos);
                modName += lastWordPos;
            }

            tmpMask |= PREFIX_NAME;
        }
        
        /* calculate class level (if necessary) */
        if (tmpMask & PREFIX_CLASS) {
            for (; (class & 1) == 0; classLevel++, class >>= 1);
        }

        /* check for favorite common prefixes */
        if (tmpMask ==
             (PREFIX_TIMESTAMP | PREFIX_CLASS | PREFIX_TID | PREFIX_NAME)) {

            time = (GT->TIMEFXN != NULL) ? GT->TIMEFXN() : 0;
            if (timeMask == TIME_DELTAUSEC) {   /* "GT_time=0" */
                UInt32 deltaTime = time - lastTime;
                (*GT->PRINTFXN)("@+%03d,%03dus: [+%d T:0x%08x] %s - ",
                                deltaTime / 1000, deltaTime % 1000,
                                classLevel, tid, modName);
            }
            else if (timeMask == TIME_USEC) {  /* "GT_time=1" */
                (*GT->PRINTFXN)("@%d,%03d,%03dus: [+%d T:0x%08x] %s - ",
                                time / 1000000, (time / 1000) % 1000,
                                time % 1000, classLevel, tid, modName);
            }
            else if (timeMask == TIME_SEC) {   /* "GT_time=2" */
                (*GT->PRINTFXN)("@%d.%03ds: [+%d T:0x%08x] %s - ",
                                time / 1000000, (time / 1000) % 1000,
                                classLevel, tid, modName);
            }
            else if (timeMask == TIME_TICKS) {  /* "GT_time=3" */
                (*GT->PRINTFXN)("@%d,%03d,%03dtk: [+%d T:0x%08x] %s - ",
                                time / 1000000, (time / 1000) % 1000,
                                time % 1000, classLevel, tid, modName);
            }
            else {
                (*GT->PRINTFXN)("@0x%08x: [+%d T:0x%08x] %s - ", time,
                               classLevel, tid, modName);
             }
        }
        else if (tmpMask == (PREFIX_TID | PREFIX_CLASS | PREFIX_NAME)) {
            (*GT->PRINTFXN)("[+%d T:0x%08x] %s - ", classLevel, tid, modName);
        }
        else if (tmpMask == (PREFIX_TID | PREFIX_CLASS)) {
            (*GT->PRINTFXN)("[+%d T:0x%08x] - ", classLevel, tid);
        }
        else if (tmpMask == (PREFIX_CLASS | PREFIX_NAME)) {
            (*GT->PRINTFXN)("[+%d] %s - ", classLevel, modName);
        }
        else if (tmpMask == PREFIX_NAME) {
            (*GT->PRINTFXN)("[] %s - ", modName);
        }
        else if (tmpMask == 0) {
            (*GT->PRINTFXN)("[] ");
        }
        else {
            if (tmpMask & PREFIX_TIMESTAMP) {
                time = GT->TIMEFXN != NULL ? GT->TIMEFXN() : 0;
                if (timeMask == TIME_DELTAUSEC) {
                    UInt32 deltaTime = time - lastTime;
                    (*GT->PRINTFXN)("@+%03d,%03dus: ", deltaTime / 1000,
                                   deltaTime % 1000);
                }
                else if (timeMask == TIME_USEC) {
                    (*GT->PRINTFXN)("@%d,%03d,%03dus: ", time / 1000000,
                                   (time / 1000) % 1000, time % 1000);
                }
                else if (timeMask == TIME_SEC) {
                    (*GT->PRINTFXN)("@%d.%03ds: ", time / 1000000,
                                   (time / 1000) % 1000);
                }
                else if (timeMask == TIME_TICKS) {
                    (*GT->PRINTFXN)("@%d,%03d,%03dtk: ", time / 1000000,
                                   (time / 1000) % 1000, time % 1000);
                }
                else {
                    (*GT->PRINTFXN)("@0x%08x:", time);
                }
            }
            (*GT->PRINTFXN)("[");
            if (tmpMask & PREFIX_CLASS) {
                (*GT->PRINTFXN)("+%d", classLevel);
            }
            if (tmpMask & PREFIX_TID) {
                (*GT->PRINTFXN)(" T:0x%08x", tid);
            }
            if (tmpMask & PREFIX_STACK) {
                (*GT->PRINTFXN)(" S:0x%08x", &mask);
            }
            (*GT->PRINTFXN)("] ");
            if (tmpMask & PREFIX_NAME) {
                (*GT->PRINTFXN)("%s - ", modName);
            }
        }
    }

    (*GT->PRINTFXN)(format, arg1, arg2, arg3, arg4, arg5, arg6);

    /* release the lock for the print */
    if (GT->UNLOCKFXN != NULL) {
        GT->UNLOCKFXN();
    }

    /* if the app user is interested in delta times, find out the current time
     * ("lastTime") and use it as a basis when computing the delta next time
     * around; by calling time() now we discount the duration of the print
     * call itself
     */
    if ((prefixMask & PREFIX_TIMESTAMP) && (timeMask == TIME_DELTAUSEC)) {
        lastTime =  GT->TIMEFXN != NULL ? GT->TIMEFXN() : 0;
    }

    return (0);
}

/*
 *  ======== addModName ========
 *  adds module (name, flags) to the linked list of modules
 */
static Bool addModName(String modName, UInt8 flags)
{
    ModNameListElem *elem;

    /* create module list element */
    elem = (ModNameListElem *)(*GT->MALLOCFXN)(sizeof(ModNameListElem));
    if (elem == NULL) {
        error("Memory alloc for ModNameListElem failed");
        return (FALSE);
    }

    /* create space for the module name and copy it */
    elem->modName = (String)(*GT->MALLOCFXN)(strlen(modName) + 1);
    if (elem->modName == NULL) {
        error("Memory alloc for ModNameListElem name failed");
        (*GT->FREEFXN)(elem, sizeof(ModNameListElem));
    }
    strcpy(elem->modName, modName);

    elem->flags = flags;

    /* atomically(TODO) add module element to list */
    elem->next = modNameList;
    modNameList = elem;
    /* [dm]TODO:L the above must be protected;
     * [dm]TODO:L what is alloced must be freed, on exit maybe
     */
    return (TRUE);
}

/*
 *  ======== applyOp ========
 *  applies given operation and mask on the set of flags
 */
static Void applyOp(UInt8 *mask, Char op, UInt8 opMask)
{
    switch (op) {
        case (Int)GT_CLEAR:
            *mask = opMask;
            break;
        case (Int)GT_ON:
            *mask |= opMask;
            break;
        case (Int)GT_OFF:
            *mask &= ~opMask;
            break;
        default :
            error("illegal trace mask");
            break;
    }
}

/*
 *  ======== error ========
 *  purpose:
 *      Prints errors onto the standard output.
 */
static Void error(String String)
{
    (*GT->PRINTFXN)("GT: %s", String);
}

/*
 *  ======== findElem ========
 *  finds element in the list
 */
static ModNameListElem *findElem(String modName)
{
    ModNameListElem *elem;

    for (elem = modNameList; elem != NULL; elem = elem->next) {
        if (!strncmp(modName, elem->modName, MAXMODNAMELENGTH)) {
            return (elem);
        }
    }
    return (NULL);
}

/*
 *  ======== getModNameFlagsAddr ========
 *  returns the address of the flags field for the given module
 */
static Bool getModNameFlagsAddr(String modName, UInt8 **modNameFlagsAddr)
{
    ModNameListElem *elem;

    elem = findElem(modName);
    if (elem != NULL) {
        *modNameFlagsAddr = &(elem->flags);
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== setMask ========
 *  purpose:
 *      Sets mask for the GT module.
 */
static Void setMask(String modName, Char op, UInt8 mask)
{
    UInt8  modNameFlags;

    if (!strcmp(modName, PREFIXMASK)) {
        applyOp(&prefixMask, op, mask);
    }
    else if (!strcmp(modName, TIMEMASK)) {
        applyOp(&timeMask, op, mask);
    }
    else if (strchr(modName, GT_WILD) != NULL) {
        wildcardUpdate(modName, op, mask);
    }
    else {  /* "normal" module name */
        if (GT_getModNameFlags(modName, &modNameFlags)) {
            applyOp(&modNameFlags, op, mask);
            setModNameFlags(modName, modNameFlags);
        }
        else {      /* module name has not been created yet */
            modNameFlags = initModFlags;
            applyOp(&modNameFlags, op, mask);
            addModName(modName, modNameFlags);
        }
    }
}

/*
 *  ======== setModNameFlags ========
 */
static Bool setModNameFlags(String modName, UInt8 flags)
{
    ModNameListElem *elem;

    elem = findElem(modName);
    if (elem != NULL) {
        elem->flags = flags;
        return (TRUE);
    }
    else {
        return (FALSE);
    }
}

/*
 *  ======== wildcardUpdate ========
 *  updates flags for all modules
 */
static Void wildcardUpdate(String pattern, char op, UInt8 mask)
{
    ModNameListElem *elem;
    Int len = strchr(pattern, GT_WILD) - pattern;
    
    /* treat names with leading '*' as a special case that means update
     * the internal variable initModFlags.  This allows one to set trace
     * for all modules even before they have been created
     */
    if (len == 0) {
        applyOp(&initModFlags, op, mask);   
    }

    for (elem = modNameList; elem != NULL; elem = elem->next) {
        if (strncmp(pattern, elem->modName, len) == 0) {
            applyOp(&elem->flags, op, mask);
        }
    }
}
/*
 *  @(#) ti.sdo.utils.trace; 1, 0, 0,186; 12-1-2010 17:26:17; /db/atree/library/trees/fc/fc-p01x/src/ xlibrary

 */

