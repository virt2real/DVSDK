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
 *  ======== Log__epilogue.h ========
 *  Implementation of the Log_* macros
 *
 *  The implementation below relies on five symbols defined by every module
 *  header.  Each of these symbols is a reference to a constant defined in a
 *  separate compilation unit.  The values of these constants are as follows:
 *
 *      Module__MID     - the module's ID (see Text.xs)
 *      Module__LOGOBJ  - the module's logger object
 *      Module__LOGFXN4 - the module's logger's write4 function
 *      Module__LOGFXN8 - the module's logger's write8 function
 *      Module__LOGDEF  - 0 if the module has a logger, non-zero otherwise
 */

/*
 *  ======== xdc_runtime_Log_getMask ========
 */
#define xdc_runtime_Log_getMask(evt) ((evt) & 0x0000ffff)

/*
 *  ======== xdc_runtime_Log_getRope ========
 */
#define xdc_runtime_Log_getRope(evt) ((xdc_runtime_Types_RopeId)((evt) >> 16))

/*
 *  ======== xdc_runtime_Log_getEventId ========
 */
#define xdc_runtime_Log_getEventId(evt) ((xdc_runtime_Log_EventId)((evt) >>16))

/*
 *  ======== xdc_runtime_Log_put* ========
 */
#define xdc_runtime_Log_put4(evt, a1, a2, a3, a4) \
    Module__LOGFXN4(Module__LOGOBJ, evt, (a1), (a2), (a3), (a4))

#define xdc_runtime_Log_put8(evt, a1, a2, a3, a4, a5, a6, a7, a8) \
    Module__LOGFXN8(Module__LOGOBJ, evt, (a1), (a2), (a3), (a4),    \
        (a5), (a6), (a7), (a8))

/*
 *  ======== xdc_runtime_Log_write* ========
 *  Log_Events need to be converted to Type_Events prior to calling Log_put;
 *  the lower 16-bits are a mask that needs to be replaced with the caller's
 *  module ID.
 */
#define xdc_runtime_Log_write0(evt) \
    xdc_runtime_Log_write4(evt, 0, 0, 0, 0)
#define xdc_runtime_Log_write1(evt, a1) \
    xdc_runtime_Log_write4(evt, a1, 0, 0, 0)
#define xdc_runtime_Log_write2(evt, a1, a2) \
    xdc_runtime_Log_write4(evt, a1, a2, 0, 0)
#define xdc_runtime_Log_write3(evt, a1, a2, a3) \
    xdc_runtime_Log_write4(evt, a1, a2, a3, 0)

#define xdc_runtime_Log_write4(evt, a1, a2, a3, a4) \
    ((Module__LOGDEF && xdc_runtime_Diags_query(evt)) ? \
        xdc_runtime_Log_put4( ((evt) & 0xffff0000) | Module__MID, \
            (a1), (a2), (a3), (a4)) : (void)0 \
    )

#define xdc_runtime_Log_write5(evt, a1, a2, a3, a4, a5) \
    xdc_runtime_Log_write8(evt, a1, a2, a3, a4, a5, 0, 0, 0)
#define xdc_runtime_Log_write6(evt, a1, a2, a3, a4, a5, a6) \
    xdc_runtime_Log_write8(evt, a1, a2, a3, a4, a5, a6, 0, 0)
#define xdc_runtime_Log_write7(evt, a1, a2, a3, a4, a5, a6, a7) \
    xdc_runtime_Log_write8(evt, a1, a2, a3, a4, a5, a6, a7, 0)

#define xdc_runtime_Log_write8(evt, a1, a2, a3, a4, a5, a6, a7, a8) \
    ( (Module__LOGDEF && xdc_runtime_Diags_query(evt)) ? \
        xdc_runtime_Log_put8(((evt) & 0xffff0000) | Module__MID, \
            (a1), (a2), (a3), (a4), (a5), (a6), (a7), (a8)) : (void)0 \
    )

/*
 *  ======== xdc_runtime_Log_print* ========
 *  Since "print" events do not have a rope, we use 0 (an invalid rope value)
 *  to construct a Type_Event to pass to Log_put. This has the benefit that
 *  the Type_Event is equal to the module ID: (0 | Module__MID)
 */
#define xdc_runtime_Log_print0(mask, fmt) \
    xdc_runtime_Log_print3(mask, fmt, 0, 0, 0)
#define xdc_runtime_Log_print1(mask, fmt, a1) \
    xdc_runtime_Log_print3(mask, fmt, a1, 0, 0)
#define xdc_runtime_Log_print2(mask, fmt, a1, a2) \
    xdc_runtime_Log_print3(mask, fmt, a1, a2, 0)

#define xdc_runtime_Log_print3(mask, fmt, a1, a2, a3) \
    ( (Module__LOGDEF && xdc_runtime_Diags_query(mask)) ? \
        xdc_runtime_Log_put4(Module__MID, (IArg)fmt, (a1), (a2), (a3)) : (void)0 \
    )

#define xdc_runtime_Log_print4(mask, fmt, a1, a2, a3, a4) \
    xdc_runtime_Log_print6(mask, fmt, a1, a2, a3, a4, 0, 0)
#define xdc_runtime_Log_print5(mask, fmt, a1, a2, a3, a4, a5) \
    xdc_runtime_Log_print6(mask, fmt, a1, a2, a3, a4, a5, 0)

#define xdc_runtime_Log_print6(mask, fmt, a1, a2, a3, a4, a5, a6) \
    ( (Module__LOGDEF && xdc_runtime_Diags_query(mask)) ?    \
        xdc_runtime_Log_put8(Module__MID,                     \
            (IArg)fmt, (a1), (a2), (a3), (a4), (a5), (a6), 0) : (void)0  \
    )
    
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

