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
 *  ======== package.xs ========
 *
 *! Revision History
 *! ================
 *! 23-Apr-2007 rf      moved close/validate to xdc.runtime
 *! 25-Sep-2006 toddm	Moved memory handling into close.  
 *! 28-Jun-2006 sasa	moved close to close() in Model.xs
 *! 13-Jun-2006 sasa	added check if MODULE_STARTUP is a module attribute
 *!			for compatibility with xdc-m
 *! 19-Jul-2005 sasa	added else clause where Memory.$used is set to 0
 */

/*
 *  ======== init ========
 */
function init()
{
}

/*
 *  ======== close ========
 */
function close()
{
}

/*
 *  ======== validate ========
 */
function validate()
{
    for (var sym in Program.symbol) {
        var obj = Program.symbol[sym];

        if (typeof(obj) == 'number'
	    || ('$category' in obj && obj.$category == 'Instance')) {
	    continue;
	}

        Program.$logError("value of symbol '" + sym +
            "' must be a number or instance object", Program);
    }
    
    var map = Program.getSectMap();
    
    for (var key in map) {
        if (map[key].loadSegment != null && map[key].loadSegment != undefined &&
            map[key].loadAddress != null && map[key].loadAddress != undefined) {
            Program.$logError("Section '" + key + "' defines both loadSegment "
            + "and loadAddress.", Program);
        }
        if (map[key].runSegment != null && map[key].runSegment != undefined &&
            map[key].runAddress != null && map[key].runAddress != undefined) {
            Program.$logError("Section '" + key + "' defines both runSegment " +
            "and runAddress.", Program);
        }
        if (map[key].loadAlign != null && map[key].loadAlign != undefined &&
            map[key].loadAddress != null && map[key].loadAddress != undefined) {
            Program.$logError("Section '" + key + "' defines both loadAlign "
            + "and loadAddress.", Program);
        }
        if (map[key].runAlign != null && map[key].runAlign != undefined &&
            map[key].runAddress != null && map[key].runAddress != undefined) {
            Program.$logError("Section '" + key + "' defines both runAlign " +
            "and runAddress.", Program);
        }
    }
    
}
/*
 *  @(#) xdc.cfg; 1, 0, 2, 0,237; 2-22-2010 10:33:11; /db/ztree/library/trees/xdc/xdc-u17x/src/packages/
 */

