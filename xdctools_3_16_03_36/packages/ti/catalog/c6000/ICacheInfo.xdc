/*
 *  Copyright (c) 2010 by Texas Instruments and others.
 *  All rights reserved. This program and the accompanying materials
 *  are made available under the terms of the Eclipse Public License v1.0
 *  which accompanies this distribution, and is available at
 *  http://www.eclipse.org/legal/epl-v10.html
 *
 *  Contributors:
 *      Texas Instruments - initial implementation
 *
 * */

/*
 *  ======== ICacheInfo.xdc ========
 */


package ti.catalog.c6000;

metaonly interface ICacheInfo {
    /*!
     *  ======== CacheDesc ========
     *  Structure used by ICpuDataSheet implementations to
     *  specify device cache modes. 
     *   
     *  A map is defined by an ICpuDataSheet implementation
     *  that maps a string denoting a device register setting
     *  to a CacheDesc structure. This maybe used in implementing
     *  the 'getMemoryMap' method. An example of such a map is shown below :
     *
     *   readonly config ti.catalog.c6000.ICacheInfo.CacheDesc cacheMap[string] =  [
         *    ['l1PMode',{desc:"L1P Cache",
         *                map : [["0k",0x0000],
         *                       ["4k",0x1000],
         *                       ["8k",0x2000],
         *                       ["16k",0x4000],
         *                       ["32k",0x8000]],
         *                defaultValue: "0k",
         *                memorySection: "L1PSRAM"}],
         *
         *        ['l1DMode',{desc:"L1D Cache",
         *                map : [["0k",0x0000],
         *                       ["4k",0x1000],
         *                       ["8k",0x2000],
         *                       ["16k",0x4000],
         *                       ["32k",0x8000]],
         *                defaultValue: "0k",
         *                memorySection: "L1DSRAM"}],
         *            
         *    ['l2Mode',{desc:"L2 Cache",
         *                map : [["0k",0x0000],
         *                       ["32k",0x8000],
         *                       ["64k",0x10000],
         *                       ["128k",0x20000],
         *                       ["256k",0x40000]],
         *                defaultValue: "0k",
         *                memorySection: "IRAM"}], 
     *
     *   ];
     *
     *  @_nodoc
     */
    struct CacheDesc {
        string desc;          /*! String describing the register setting */
        unsigned map[string]; /*! A hash of cache modes to cache size*/
        string defaultValue;  /*! The default cache mode for the device */
        string memorySection; /*! The associated memory section */
    };


}
/*
 *  @(#) ti.catalog.c6000; 1, 0, 0, 0,226; 2-23-2010 16:50:37; /db/ztree/library/trees/platform/platform-k32x/src/
 */

