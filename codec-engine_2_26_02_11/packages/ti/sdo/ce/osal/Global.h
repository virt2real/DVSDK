/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== Global.h ========
 */
#ifndef ti_sdo_ce_osal_Global_
#define ti_sdo_ce_osal_Global_

#ifdef __cplusplus
extern "C" {
#endif

#define Global_EOK          0               /* no error */
#define Global_EFAIL        1               /* unspecified failure */

#define Global_FOREVER      ((UInt)-1)        /* no timeout; wait forever */
#define Global_POLL         ((UInt)-1)        /* timeout immediately */

/*
 *  ======== Global_GTNAME ========
 */
#define Global_GTNAME       "OG"

/*
 *  ======== Global_ArmDspLinkConfigMemTableEntry ========
 */
typedef struct Global_ArmDspLinkConfigMemTableEntry {
    String segmentName;
    Uint32 startAddress;
    Uint32 gppAddress;
    UInt32 sizeInBytes;
    Bool   shared;
    Bool   syncd;
} Global_ArmDspLinkConfigMemTableEntry;

typedef enum {
    BootNoPwr = 0,
    BootPwr,
    NoLoadNoPwr,
    NoLoadPwr,
    NoBoot
} Global_ArmDspLinkDspCtrl;

/*
 *  ======== Global_ArmDspLinkConfig ========
 */
typedef struct Global_ArmDspLinkConfig {
    Global_ArmDspLinkConfigMemTableEntry *memTable;
    Global_ArmDspLinkDspCtrl doDspCtrl;
} Global_ArmDspLinkConfig;


/*
 *  ======== Global_abort ========
 *  abort entire program.
 *
 *  Do not perform normal exit processing; go straight to program termination
 */
extern Void Global_abort(String fmt, ...);

/*
 *  ======== Global_atexit ========
 *  add exit handler
 */
extern Bool Global_atexit(Fxn fxn);

/*
 *  ======== Global_exit ========
 *  calls all functions scheduled to be called atexit, removing them
 *  from the atexit list, and returns; to be used when someone doesn't
 *  want to exit() the application to do cleanup, but instead wants to
 *  clean up directly
 */
extern Void Global_exit(Void);

/*
 *  ======== Global_getCpuLoad ========
 */
extern Int Global_getCpuLoad(Void);

/*
 *  ======== Global_getenv ========
 */
extern String Global_getenv(String name);

/*
 *  ======== Global_getProcessId ========
 *  Get the Id of the calling process.
 */
extern UInt32 Global_getProcessId(Void);

/*
 *  ======== Global_init ========
 *  Initialize the OSAL package
 */
extern Void Global_init(Void);

/*
 *  ======== Global_setSpecialTrace ========
 */
extern Void Global_setSpecialTrace(String mask);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.osal; 2, 0, 2,427; 12-2-2010 21:24:37; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

