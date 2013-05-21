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
 *  ======== xdc_runtime_Assert_getMask ========
 *  Convert an id into a mask
 */
#define xdc_runtime_Assert_getMask(id) ( \
    (id) ? ((id) & 0x0000FFFF & ~xdc_runtime_Diags_ASSERT) \
         : xdc_runtime_Diags_INTERNAL \
)

/*
 *  ======== xdc_runtime_Assert_isTrue ========
 */
#define xdc_runtime_Assert_isTrue( expr, id ) (\
    (xdc_runtime_Diags_query(xdc_runtime_Diags_ASSERT)) ? ( \
        (((!xdc_runtime_Assert_getMask(id) || xdc_runtime_Diags_query(xdc_runtime_Assert_getMask(id))) && !(expr)) ? \
            xdc_runtime_Assert_raise__I(Module__MID, xdc_FILE__, __LINE__, (id)) : (void)0) \
    ) : (void)0)





/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

