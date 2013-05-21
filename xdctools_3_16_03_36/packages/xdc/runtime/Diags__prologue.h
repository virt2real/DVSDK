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
 *  ======== Diags__prologue.h ========
 *
 *  This header defines Module__* symbols for every Module__* value used
 *  by the Diags module's headers.  This allows non-module code to
 *  use the Diags module.  These symbols are normally defined in
 *  module internal headers (i.e., package/internal/<mod>.xdc.h) and they
 *  define a "current module context".
 */
#include <xdc/runtime/Main.h>

/*
 *  ======== Module__DGSINCL ========
 */
#undef Module__DGSINCL
#define Module__DGSINCL xdc_runtime_Main_Module__diagsIncluded__C

/*
 *  ======== Module__DGSENAB ========
 */
#undef Module__DGSENAB
#define Module__DGSENAB xdc_runtime_Main_Module__diagsEnabled__C

/*
 *  ======== Module__DGSMASK ========
 */
#undef Module__DGSMASK
#define Module__DGSMASK xdc_runtime_Main_Module__diagsMask__C

/*
 *  ======== Module__MID ========
 */
#undef Module__MID
#define Module__MID xdc_runtime_Main_Module__id__C
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

