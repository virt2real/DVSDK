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
 *  ======== Memory.xs ========
 *
 *! Revision History
 *! ================
 *! 19-Dec-2008 sasha	module$use runs only when ROM assembly is imported
 *! 10-Jul-2007 toddm	If defaultHeapInstance is null or undefined, create
 *!                     heap.
 *! 08-Jun-2007 nitya	If defaultHeapInstance=null, do not create heap.
 *! 25-Sep-2006 toddm   Introduced idea of sections instead of heaps for
 *!                     the placement of static items.
 *! 18-Jul-2005 sasha   created
 */

/*
 *  ======== module$use ========
 */
function module$use()
{

    /* This code runs here only when ROM assembly is imported, and Memory
     * is in that assembly. In that case, we need this code to run as early
     * as useModule(). For all other use cases, we want to set default
     * values very late, after all other packages had a chance to set those
     * values. That's why this same code is repeated in xdc.runtime.close().
     * For now, we don't have a better solution for a use case when one 
     * package only wants to use module, but another one, which closes later,
     * wants also to set module's parameters.
     */     
    if (Program.$capsule._romAsm != undefined) {
        for each (var m in Program.$capsule._romAsm.modules) {
            if (m.name == this.$name) {
                /*
                 *  Make sure it has a default instance. This instance is used in
                 *  Memory_alloc if NULL is specified for the heap.
                 */
                if (this.defaultHeapInstance == null) {
                    var HeapStd = xdc.useModule('xdc.runtime.HeapStd');
                    this.defaultHeapInstance = HeapStd.create(
                        {size: this.defaultHeapSize});
                }
                this.HeapProxy = this.defaultHeapInstance.$module;

                /* declare that instances may come from different modules; the
                 * generated HeapProxy function stub must call through a vtable
                 * pointer rather than directly call the HeapProxy module
                 */
                this.HeapProxy.abstractInstances$ = true;
            }
        }
    }
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(obj)
{
    obj.maxDefaultTypeAlign = getMaxDefaultTypeAlignMeta();
}

/*
 *  ======== staticPlace ========
 */
function staticPlace(obj, align, sectionName)
{
    var Program = xdc.module('xdc.cfg.Program');
    var target  = Program.build.target;    

    obj.$$alloc(sectionName, align);    

    if ((target.alignDirectiveSupported == false) && (align != 0) &&
        (align != 1)) {
        return (false);
    }

    return (true);
}

/*
 *  ======== getMaxDefaultTypeAlignMeta ========
 */
function getMaxDefaultTypeAlignMeta()
{
    var Program = xdc.module('xdc.cfg.Program');
    var target  = Program.build.target;

    var align = 0;

    for (var k in target.stdTypes) {
        if (align < target.stdTypes[k].align) {
            align = target.stdTypes[k].align;
        }
    }
    return (align);
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

