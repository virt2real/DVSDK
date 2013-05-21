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
 *  ======== Core_mem.c ========
 */

#include <string.h>

#include <xdc/runtime/Assert.h>
#include <xdc/runtime/Error.h>
#include <xdc/runtime/Gate.h>
#include <xdc/runtime/Memory.h>
#include <xdc/runtime/IInstance.h>
#include <xdc/runtime/Types.h>

#include "package/internal/Core.xdc.h"

/*
 *  ======== Core_createObject ========
 *
 */
Ptr Core_createObject(const Core_ObjDesc *od, Ptr curObj, SizeT objStrSize,
    Ptr resPrms, const Ptr argPrms, SizeT argPrmsSize, Error_Block *eb)
{
    Types_InstHdr *instHdr;
    Types_PrmsHdr *prmsHdr;
    IInstance_Params *instPrms;
    IArg gateKey;

    Ptr resObj = curObj;

    /* resPrms is initialized with the values from Mod_Object__PARAMS__C */
    memcpy(resPrms, od->prmsInit, od->prmsSize);
    prmsHdr = (Types_PrmsHdr *)resPrms;
    prmsHdr->self = prmsHdr;

    if (argPrms) {
        Assert_isTrue(((const Types_PrmsHdr *)argPrms)->self == argPrms,
            Core_A_initializedParams);

        Core_assignParams(resPrms, argPrms, od->prmsSize,
            sizeof(IInstance_Params));
    }

    instPrms = prmsHdr->instPrms;

    if (curObj == NULL) {

        instHdr = Memory_calloc(od->objHeap, od->objSize, od->objAlign, eb);
        if (!instHdr) {
            return (NULL);
        }

        resObj = instHdr + 1;

        gateKey = Gate_enterSystem();
            instHdr->link.next = od->modLink;
            instHdr->link.prev = od->modLink->prev;
            od->modLink->prev->next = &instHdr->link;
            od->modLink->prev = &instHdr->link;
        Gate_leaveSystem(gateKey);
    }
    else {
        /* We need to ensure that the constructed object is zeroed to be
         * consistent with created objects for which we call calloc.
         */
        SizeT osz = od->objSize - sizeof(Types_InstHdr);

        /* REPLACE WITH AN ASSERT ONCE ROM-COMPATIBILITY CAN BE BROKEN */

        if (objStrSize < osz) {
            Error_raise(NULL, Error_E_generic,
                (IArg)"<Mod>_Struct size is too small", NULL);
        }
        memset(resObj, 0, osz);
    }

    if (od->fxnTab != (Ptr)-1) {
        *((Ptr *)resObj) = od->fxnTab;
    }

    if (od->objName) {
        *((Ptr *)((Char *)resObj + od->objName)) = instPrms->name;
    }

    return (resObj);
}


/*
 *  ======== Core_deleteObject ========
 */
Void Core_deleteObject(const Core_ObjDesc *od, Ptr curObj, Fxn finalFxn,
    Int istat, Bool consFlg)
{
    typedef Void (*FinalFxn1)(Ptr);
    typedef Void (*FinalFxn2)(Ptr, Int);

    Types_InstHdr *instHdr;
    IArg gateKey;

    if (curObj == NULL) {
        return;     /* silently ignore NULL object references */
    }

    if (!consFlg) {
        instHdr = ((Types_InstHdr *)curObj) - 1;

        gateKey = Gate_enterSystem();
            instHdr->link.prev->next = instHdr->link.next;
            instHdr->link.next->prev = instHdr->link.prev;
        
            /* Zeroing pointers in instHdr, so that anyone pointing at this
             * instance can notice that the instance is invalid (CQ10402).
             */
            instHdr->link.prev = NULL;
            instHdr->link.next = NULL;
        Gate_leaveSystem(gateKey);
    }

    if (finalFxn != NULL) {
        if (istat == -1) {
            ((FinalFxn1)finalFxn)(curObj);
        }
        else {
            ((FinalFxn2)finalFxn)(curObj, istat);
        }
    }

    if (!consFlg) {
        Memory_free(od->objHeap, instHdr, od->objSize);
    }
}

/*
 *! Revision History
 *! ================
 *! 10-Mar-2008 sasha	split from Core.c
 */

/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

