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
 *  ======== LogClient.h ========
 */

#ifndef LogClient_
#define LogClient_

#include <stdio.h>

#ifdef __cplusplus
extern "C" {
#endif

/*
 *  ======== LogClient_connect ========
 *  Establishes a connection to the server.
 *
 *  This API must called *after* the DSP has been started.
 *
 *  Returns TRUE on success or FALSE for failure (e.g., server MSGQ
 *  cannot be found, DSP not running, etc.)
 */
extern Bool LogClient_connect(Void);


/*
 *  ======== LogClient_disconnect ========
 *  Clean up and disconnect from the LOG server.
 */
extern Void LogClient_disconnect(Void);


/*
 *  ======== LogClient_fwriteLogs ========
 *  Copies DSP logs to FILE stream pointed to by 'out'.
 *
 *  This file has the following format:
 *
 *     <0>              (Uint32) LOG index from LOG_A_TAB
 *     <size>           (Uint32) size of payload in bytes
 *     <[0]-[size-1]>   (Char) payload
 *     <1>              (Uint32) LOG index from LOG_A_TAB
 *     <size>           (Uint32) size of payload in bytes
 *     <[0]-[size-1]>   (Char) payload
 *      ...
 *     <nlogs-1>        (Uint32) LOG index from LOG_A_TAB
 *     <size>           (Uint32) size of payload in bytes
 *     <[0]-[size-1]>   (Char) payload
 *     <-1>             (Uint32) marks end of LOG upload
 *     <0>              (Uint32) pad helps with alignment and debug
 *
 *  Notes:
 *
 *  (1) It is possible to have adjacent records with the
 *  same id header.  This can happen if payload won't fit in single
 *  transfer.
 *
 *  (2) If no data in the LOG, the file will have logid, followed
 *  by '0', and no payload.  This ensures that the file will always
 *  contain data for each LOG (even if no new data on DSP)
 */
extern Void LogClient_fwriteLogs(FILE *out);

/*
 *  ======== LogClient_init ========
 *  must be called before any other API
 */
extern Void LogClient_init(Void);

/*
 *  ======== LogClient_timeSynch ========
 *  Send timeSynch request to DSP.
 */
extern Void LogClient_timeSynch(Void);

#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.sdo.ce.bioslog; 1, 0, 1,326; 12-2-2010 21:18:56; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

