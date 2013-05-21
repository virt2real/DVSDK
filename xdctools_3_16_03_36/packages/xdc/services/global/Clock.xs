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
 *  ======== _t0 ========
 *  global clock counter
 */
var _t0 = 0;        /* time of last reset */
var _prev = 0;      /* time of last print */

/*
 *  ======== getElapsedTime ========
 */
function getElapsedTime()
{
    return (java.lang.System.currentTimeMillis() - _t0);
}

/*
 *  ======== print ========
 */
function print(msg)
{
    if (this.enable) {
	var mem = "";
	if (this.showMemory) {
	    var rt = java.lang.Runtime.getRuntime();
	    mem = "used: " + (rt.totalMemory() - rt.freeMemory()) + ", ";
	}
        var cur = java.lang.System.currentTimeMillis();
	xdc.global.print(mem + "dt =", cur - _prev, msg);
        _prev = cur;
    }
}

/*
 *  ======== reset ========
 */
function reset()
{
    _prev = _t0 = java.lang.System.currentTimeMillis();
}

