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
/*!
 *  ======== IInstance ========
 *  Common instance params
 *
 *  Every module's instance parameter structure contains a pointer to an
 *  `IInstance.Params` structure named `instance`.  So, every instance
 *  parameter defined in this interface may optionally be set when
 *  creating (or constructing) any module's instances.
 */
interface IInstance {

instance:

    /*! 
     *  ======== name ========
     *  Name of the instance
     *
     *  It is possible to "bind" a name to each instance of any module
     *  at the time the instance is created (or constructed).  
     *  @p(code)
     *      ModA_Params params;
     *      ModA_Params_init(&params);
     *      params.instance->name = "myInstance";
     *      ModA_create(&params, NULL);
     *  @p
     *
     *  The name field must be assigned a pointer to a buffer that persists
     *  as long as the instance that it names exists.  Only a reference to
     *  the name is retained in the instance, the name is not copied to a
     *  secondary buffer.
     *
     *  If instances have been configured to not support names, it is still
     *  possible to assign to the `instance.name` field of the parameter
     *  structure (as shown above).  However, the pointer is not retained
     *  and methods that normally return an instance's name will return
     *  `NULL` instead.
     */
    config String name = null;
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

