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
 *  ======== Defaults.xdc ========
 *
 *! Revision History
 *! ================
 *! 19-Feb-2008 sasha   Added getCommon() meta function
 */

package xdc.runtime;

/*!
 *  ======== Defaults ========
 *  Default attributes inherited by all target modules
 *
 *  This module defines default values for `common$` structure. If other 
 *  modules do not set `common$` properties explicitly, these values will be
 *  used.
 */
module Defaults {

    /*! 
     *  ======== common$ ========
     *  Defaults inherited by all target modules
     *
     *  This structure defines the default values for the configuration
     *  parameters shared by all modules in a system.  Unless otherwise
     *  noted, setting one of the fields defined below will set the
     *  corresponding value for all modules in the system which have not
     *  been explicitly set; i.e., it will establish a default value for
     *  the parameter.
     *
     *  @a(diags_ASSERT) 
     *  Enables asserts at runtime. Default is `ALWAYS_ON`
     *
     *  @a(diags_ENTRY)
     *  Enables entry trace for all functions. Default is `ALWAYS_OFF`
     *
     *  @a(diags_EXIT)
     *  Enables exit trace for all functions. Default is `ALWAYS_OFF`
     *
     *  @a(diags_INTERNAL)
     *  Enables internal asserts. Default is `ALWAYS_OFF`. When set to
     *  `ALWAYS_ON`, requires `diags_ASSERT` to be `ALWAYS_ON`.
     *
     *  @a(diags_LIFECYCLE)
     *  Enables lifecycle logs. These logs are written during creates
     *  and deletes. Default is `ALWAYS_OFF`. 
     *
     *  @a(diags_USER)
     *  Each `diags_USER` field controls a separate user-defined
     *  logging level. Default is `ALWAYS_OFF` for all `diags_USER` fileds.
     *
     *  @a(gate)
     *  Default gate used by all modules which are declared as being `@Gated`.
     *  By default, this parameter points to an instance of `{@link GateNull}`,
     *  which means there is no protection.
     *
     *  @a(gateParams)
     *  The default parameters used to create gates at runtime. See
     *  `{@link Types#Common$.gateParams}`.  Default is `null`.
     *
     *  @a(instanceHeap)
     *  Specify heap to be used for module instances. Default is `null`.
     *  If `instanceHeap` is `null`, instances will be allocated from
     *  the heap specified by `{@link Memory#defaultHeapInstance}`.
     *  
     *  @a(instanceSection)
     *  Specify section to be used to place module instances. Default is
     *  `null`.
     *
     *  @a(logger)
     *  Default logger used by modules to write logs. By default there is 
     *  no logger.
     *
     *  @a(memoryPolicy)
     *  Used to specify type of application. `Types.STATIC_POLICY` is used when
     *  all objects are created statically. `Types.CREATE_POLICY` is used when 
     *  the application creates objects at runtime. `Types.DELETE_POLICY` is
     *  used when the application creates and deletes objects at runtime. This
     *  helps eliminate unwanted create and delete code.
     *
     *  @a(namedInstance)
     *  This parameter should be set to true if space needs to be allocated in
     *  instance objects for instance names. Allocating space for a name
     *  allows object view tools to display the names. The runtime functions
     *  `Mod_Handle_name()` and `Mod_Handle_label()` defined for each module
     *  `Mod` can be used to retrieve the name at runtime.
     *
     *  @a(namedModule)
     *  This field allows the name of the module to be retained on the target.
     *  Setting this to `false` will save space but will also prevent
     *  the target from being able to display the module names appearing
     *  in `Log` events and `Error`s.
     *
     *  Setting `namedModule` to `false` causes all modules, except for
     *  `{@link Memory}` and `{@link Main}` to be unnamed by default.  To
     *  eliminate the string names for these modules you must explicitly
     *  set their `common$.namedModule` parameters to `false`; without these
     *  two names, target-side display of error messages is somewhat cryptic.
     *
     *  @a(romPatchTable)
     *  Specify whether modules that are allocated to ROM are patchable.
     */
    override metaonly config Types.Common$ common$ = {
        diags_ASSERT:       Diags.ALWAYS_ON,
        diags_ENTRY:        Diags.ALWAYS_OFF,
        diags_EXIT:         Diags.ALWAYS_OFF,
        diags_INTERNAL:     Diags.ALWAYS_OFF,
        diags_LIFECYCLE:    Diags.ALWAYS_OFF,
        diags_USER1:        Diags.ALWAYS_OFF,
        diags_USER2:        Diags.ALWAYS_OFF,
        diags_USER3:        Diags.ALWAYS_OFF,
        diags_USER4:        Diags.ALWAYS_OFF,
        diags_USER5:        Diags.ALWAYS_OFF,
        diags_USER6:        Diags.ALWAYS_OFF,
        diags_USER7:        Diags.ALWAYS_OFF,
        diags_USER8:        Diags.ALWAYS_OFF,
        fxntab:             true,
        gate:               null,
        gateParams:         null,
        instanceHeap:       null,
        instanceSection:    null,
        logger:             null,
        memoryPolicy:       Types.DELETE_POLICY,
        namedInstance:      false,
        namedModule:        true,
        romPatchTable:      false,
    };

    /*!
     *  ======== getCommon ========
     *  Get a specified common parameter from a module
     *
     *  Get the value of a member of the structure `common$` based on
     *  defaults and the current value of the parameter.
     *
     *  @param(eb)	module whose parameter is queried
     *
     *  @param(param)	string naming the queried parameter
     *
     *  @a(returns)
     *  Returns the value of the parameter named `param` from the module
     *  `mod`.
     */
    metaonly Any getCommon(IModule.Module mod, String param);
};
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

