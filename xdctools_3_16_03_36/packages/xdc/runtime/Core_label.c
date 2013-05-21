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
 *  ======== Core_label.c ========
 */

#include <string.h>

#include <xdc/runtime/Text.h>
#include <xdc/runtime/Types.h>

#include "package/internal/Core.xdc.h"

/*
 *  ======== Core_assignLabel ========
 */
Void Core_assignLabel(Types_Label *lab, Text_CordAddr iname, Bool named)
{
    String ns;
    
    lab->named = named;

    if (!named) {
        ns = Text_nameUnknown;
    }
    else if (iname == NULL) {
        ns = Text_nameEmpty;
    }
    else {
        ns = Text_cordText(iname);
        if (ns == NULL) {
            ns = Text_nameStatic;
        }
    }

    lab->iname = ns;
}

/*
 *! Revision History
 *! ================
 *! 10-Mar-2008 sasha	split from Core.c
 */
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

