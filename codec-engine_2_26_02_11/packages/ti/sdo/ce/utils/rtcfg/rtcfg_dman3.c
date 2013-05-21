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
 *  ======== rtcfg_dman3.c ========
 *  DMAN3 configuration for non-RTSC config example. Compile this file as is,
 *  with apps that don't use DMAN3. For apps whose local codecs use DMAN3:
 *
 *    - Copy this file to your app's build directory
 *    - Set USE_DMAN3 to 1 (below)
 *    - Modify as needed.
 */

#include <xdc/std.h>

/*
 *  Set USE_DMAN3 to 1 if the app has a local codec that uses DMAN3, otherwise
 *  set to 0. If USE_DMAN3 is set to 1, the user may need to modify the
 *  fields of the DMAN3_PARAMS structure.
 */
#define USE_DMAN3 0


#if USE_DMAN3

/*
 * ======== ti.sdo.fc.dman3.DMAN3 Configuration ========
 */

#include <ti/sdo/fc/dman3/dman3.h>
#include <ti/sdo/fc/acpy3/acpy3.h>

/*
 *  Base key value for DMAN3 Linux IPC objects. The only reason for modifying
 *  this, is if the value is the same as the key of another Linux IPC object.
 */
UInt32 _DMAN3_ipcKeyBase = 0x4e414d44;


/*
 *  ======== DMAN3_CE_init  ========
 */
Void DMAN3_CE_init()
{
    extern __FAR__ DMAN3_Params DMAN3_PARAMS;

    /* Configure DMAN3_PARAMS as needed. */
    DMAN3_PARAMS.heapInternal = 0;
    DMAN3_PARAMS.heapExternal = 0;

    DMAN3_init();
    ACPY3_init();
}

/*
 *  ======== DMAN3_CE_exit  ========
 */
Void DMAN3_CE_exit()
{
    DMAN3_exit();
    ACPY3_exit();
}

#else

/*
 *  No IDMA3 using algs in the system, and DMAN3 is not configured into the
 *  system.  Stub out these fxn calls.
 */
Void DMAN3_CE_init()
{
}

Void DMAN3_CE_exit()
{
}

int DMAN3_grantDmaChannels(int groupId, void *algHandles, void *dmaFxns,
        int numAlgs)
{
    return (0);
}

int DMAN3_releaseDmaChannels(void *algHandles, void * dmaFxns, int numAlgs)
{
    return (0);
}

#endif
/*
 *  @(#) ti.sdo.ce.utils.rtcfg; 1, 0, 1,28; 12-2-2010 21:28:00; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

