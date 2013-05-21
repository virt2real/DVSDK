/* --COPYRIGHT--,EPL
 *  Copyright (c) 2008 Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 * 
 *  Contributors:
 *      Texas Instruments - initial implementation
 * 
 * --/COPYRIGHT--*/
/*
 *  ======== ViewInfo ========
 */
package xdc.rov

/*!
 *  ======== ViewInfo ========
 *  Describes the ROV views supported by a particular module.
 */
@Facet
metaonly module ViewInfo {
    /*!
     * ======== ViewType ========
     * ROV view type
     */
    metaonly enum ViewType {
        INSTANCE,
        MODULE,
        INSTANCE_DATA,
        MODULE_DATA,
        RAW
    }
    
    /*!
     *  ======== View ========
     *  ROV View descriptor
     */
    metaonly struct View {
        ViewType type;
        String viewInitFxn;	
        String structName;	
    }
    
instance:
    
    /*!
     *  ======== viewMap ========
     *  Specifies the ROV views for the module.
     *
     *  Maps the view name to the View descriptor.
     */
    metaonly config View viewMap[string];

    /*!
     *  ======== showRawTab ========
     */
    metaonly config Bool showRawTab = true;

}
/*
 *  @(#) xdc.rov; 1, 0, 0,237; 2-22-2010 10:33:39; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

