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
 *  ======== Error.xs ========
 *
 *! Revision History
 *! ================
 *! 13-Feb-2008 sasha	ensured that desc.code is 16-bit
 */

/*
 *  ======== validate ========
 */
function validate()
{
    /* Only process during "cfg" phase */
    if (xdc.om.$name != "cfg") {
        return;
    }

    var Diags = xdc.module('xdc.runtime.Diags');

    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];

        /* check all Error_Desc's declared in any module */
        if ('$$errorDescCfgs' in mod && mod.$$errorDescCfgs.length > 0) {
            for each (var cn in mod.$$errorDescCfgs) {
                var desc = mod[cn];
                
                /* if desc.code is undefined, no problem */
                if (desc.code === undefined) {
                    continue;
                }

                /* check that code is within UInt16 range */
                if (desc.code < 0) {
                    this.$logError("value of code must be non-negative",
                        mod, cn);
                }
                else if (desc.code > 0xFFFF) {
                    this.$logError("value of code must be at most 16 bits",
                        mod, cn);
                }
            }
        }
    }
}

/*
 *  ======== module$static$init ========
 */
function module$static$init(obj, params)
{
    obj.count = 0;

    var Text = xdc.module('xdc.runtime.Text');
    for (var i = 0; i < xdc.om.$modules.length; i++) {
        var mod = xdc.om.$modules[i];

        /* create an Id for all Error_Desc's declared in the module */
        if ('$$errorDescCfgs' in mod && mod.$$errorDescCfgs.length > 0) {
            for each (var cn in mod.$$errorDescCfgs) {
                var desc = mod[cn];
                desc.$private.id = Text.defineRopeCord(desc.msg);
                
                if (desc.code === undefined) {
		    desc.$unseal("code");
                    desc.code = 0;	
		    desc.$seal("code");
                }
            }
        }
    }
}

/* The three functions below must exist for each encoded type defined in this
 * module's spec. sizeof and alignof are invoked if the encoded type is used
 * in a structure, while encode is used when a value of the encoded type
 * needs to be represented on the target.
 * In this case, the encoded type is 'Id', which is why the function names
 * start with that prefix.
 */

/*
 *  ======== Id$alignof ========
 *  Return alignment required for an encoded value of a Desc
 */
function Id$alignof()
{
    return (Program.build.target.stdTypes.t_Int32.align);
}

/*
 *  ======== Id$encode ========
 *  Return a C expression that evaluates to the encoded value of a Desc
 */
function Id$encode(desc)
{
    var encodedDesc = "0";
    if (desc) {
        encodedDesc = "(((xdc_runtime_Error_Id)" + desc.$private.id
            + ") << 16 | " + (desc.code & 0xFFFF) + ")";
    }
    return (encodedDesc);
}

/*
 *  ======== Id$sizeof ========
 *  Return sizeof the encoded value of a Desc
 */
function Id$sizeof()
{
    return (Program.build.target.stdTypes.t_Int32.size);
}

/*
 *  @(#) xdc.runtime; 2, 0, 0, 0,237; 2-22-2010 10:33:58; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

