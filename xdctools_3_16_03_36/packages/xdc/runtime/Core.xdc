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
 *  ======== Core.xdc ========
 */

package xdc.runtime;

/*!
 *  ======== Core ========
 *  Core instance lifecycle support
 *
 *  The methods defined in this module are called by code that is
 *  generated at configuration time by the `xdc.services.internal.gen`
 *  package.
 *
 *  For every module that supports instance objects, the generated .c
 *  file contains the body of the constructors and destructors for all
 *  instance objects, the generated .h file contains static inline 
 *  functions that call these bodies with a few extra parameters (e.g.,
 *  the size of parameter structs).
 *
 *  @_nodoc
 */

module Core {

    /*!
     *  ======== A_initializedParams ========
     *  Uninitialied parameters structure
     *
     *  This `Assert.Id` is thrown when the generated instance constructor
     *  detects that the instance parameters have not been properly
     *  initialized (by calling the module's `<Mod>_Params_init()` method).
     */
    config Assert.Id A_initializedParams = {
        msg: "A_initializedParams: uninitialized Params struct"
    };

internal:

    struct ObjDesc {
        Ptr             fxnTab;
        Types.Link      *modLink;
        SizeT           objAlign;
        IHeap.Handle    objHeap;
        SizeT           objName;
        SizeT           objSize;
        Ptr             prmsInit;
        SizeT           prmsSize;
    };

    /*
     *  ======== assignLabel ========
     *  Fill-in a Text Label based on iname and whether instances have names
     *
     *  If names are disabled, iname == 0, and named == FALSE
     */
    Void assignLabel(Types.Label *lab, Text.CordAddr iname, Bool named);

    /*
     *  ======== assignParams ========
     *  Common code for all Mod_Params_init()
     *
     *  @param(dstPrms) non-NULL pointer to module's Mod_Params
     *  @param(srcPrms) non-NULL pointer to parameter structure
     *  @param(mpsz)    sizeof module's "_Params" structure
     *  @param(ipsz)    sizeof module's base interface "_IInstance_Params"
     *                  struct
     */
    Void assignParams(Ptr dstPrms, const Ptr srcPrms, SizeT mpsz, SizeT ipsz);

    /*
     *  ======== createObject ========
     *  Common code for all Mod_create() and Mod_construct()
     */
    Ptr createObject(const ObjDesc *od, Ptr curObj, SizeT objStrSize,
        Ptr resPrms, const Ptr argPrms, SizeT argPrmsSize, Error.Block *eb);

    /*
     *  ======== deleteObject ========
     *  Common code for all Mod_delete() and Mod_destruct()
     */
    Void deleteObject(const ObjDesc *od, Ptr curObj, Fxn finalFxn,
        Int istat, Bool consFlg);
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

