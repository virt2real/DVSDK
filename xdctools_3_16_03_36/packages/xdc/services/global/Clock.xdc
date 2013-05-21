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
/*!
 *  ======== Clock ========
 *  Elapsed time measurement functions
 */
metaonly module Clock {

    /*!
     *  ======== getElapsedTime ========
     *  Get elapsed time from last reset
     */
    function getElapsedTime();

    /*!
     *  ======== enable ========
     *  Enable output from this module
     *
     *  If false, all output is suppressed
     */
    config Bool enable = false;

    /*!
     *  ======== showMemory ========
     *  Enable memory usage output
     *
     *  If false, memory usage output is suppressed
     */
    config Bool showMemory = false;

    /*!
     *  ======== print ========
     *  Report elapsed time from last reset
     */
    void print(String msg);

    /*!
     *  ======== reset ========
     *  Set elapsed time to 0
     */
    void reset();
}
