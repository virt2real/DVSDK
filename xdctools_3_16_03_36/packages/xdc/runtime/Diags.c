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
 *  ======== Diags.c ========
 */
#include <xdc/std.h>
#include <xdc/runtime/Text.h>

#include <string.h>

#include "package/internal/Diags.xdc.h"

#define MASKOPS "=+-"

/*
 *  ======== setMask ========
 */
Void Diags_setMask(String src)
{
    const Diags_DictElem *de;
    Bits16 mask;
    Int len;
    String ops;
    Char op;
    Char bc;
    Char *bcp;
    
    /* if set mask is disabled do nothing; this allows whole program
     * optimizers to remove this function entirely
     */
    if (!Diags_setMaskEnabled) {
        return;
    }

    for (;;) {

        /* find first/next op in the string src */
        ops = strpbrk(src, MASKOPS);
        if (ops == NULL) {
            return;
        }

        /* if the module specification is "", return */
        len = ops - src;    /* len = length of the module specification */
        if (len == 0) {
            return;
        }

        /* get operation from ops string */
        bcp = ops;
        op = *bcp++;    /* op = one of the ops in MASKOPS */

        /* compute mask from ops string */
        mask = 0;
        for (;;) {
            bc = *bcp++;
            if (bc == ';' || bc == '\0') {
                break;
            }
            else if (bc >= '1' && bc <= '8') {
                mask |= 0x100 << (bc - '1');
            }
            else if (bc == 'L') {
                mask |= Diags_LIFECYCLE;
            }
            else if (bc == 'E') {
                mask |= Diags_ENTRY;
            }
            else if (bc == 'X') {
                mask |= Diags_EXIT;
            }
            else if (bc == 'A') {
                mask |= Diags_ASSERT;
            }
            else if (bc == 'I') {
                mask |= Diags_INTERNAL;
            }
            else {
                return;
            }
        }

        /* apply ops to all matching modules */
        for (de = Diags_dictBase; de->modId; de++) {
            
            /* set tmp = length of the module specification */
            Int tmp = len;
            if (Text_matchRope(de->modId, src, &tmp) != -1) {
                /* de->modId matches src[0 - len) */
        
                /* apply mask to the matched module's mask */
                if (op == '+') {
                    *de->maskAddr |= mask;
                }
                else if (op == '-') {
                    *de->maskAddr &= ~mask;
                }
                else {
                    *de->maskAddr = mask;
                }
            }
        }

        /* if we reached the end of the string, return */
        if (bc == '\0') {
            return;
        }

        /* otherwise, move src to end of the operation string and restart */
        src = bcp;
    }
}
/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:57; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

