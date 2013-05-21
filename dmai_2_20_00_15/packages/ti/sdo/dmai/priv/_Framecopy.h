/* --COPYRIGHT--,BSD
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
 * --/COPYRIGHT--*/

#ifndef ti_sdo_dmai__Framecopy_h_
#define ti_sdo_dmai__Framecopy_h_

#include <xdc/std.h>

typedef struct Framecopy_CommonObject {
    Int      accel;
    Int      sdma;
} Framecopy_CommonObject;

/* Accelerated functions */
#if defined(Dmai_Device_omap3530) || defined(Dmai_Device_dm3730)
extern Framecopy_Handle Framecopy_sdma_accel_create(Framecopy_Attrs *attrs);
extern Int Framecopy_sdma_accel_config(Framecopy_Handle hFc,
                                       Buffer_Handle hSrcBuf,
                                       Buffer_Handle hDstBuf);
extern Int Framecopy_sdma_accel_execute(Framecopy_Handle hFc,
                                        Buffer_Handle hSrcBuf,
                                        Buffer_Handle hDstBuf);
extern Int Framecopy_sdma_accel_delete(Framecopy_Handle hFc);

extern Framecopy_Handle Framecopy_resizer_accel_create(Framecopy_Attrs *attrs);
extern Int Framecopy_resizer_accel_config(Framecopy_Handle hFc,
                                          Buffer_Handle hSrcBuf,
                                          Buffer_Handle hDstBuf);
extern Int Framecopy_resizer_accel_execute(Framecopy_Handle hFc,
                                           Buffer_Handle hSrcBuf,
                                           Buffer_Handle hDstBuf);
extern Int Framecopy_resizer_accel_delete(Framecopy_Handle hFc);
#else
extern Framecopy_Handle Framecopy_accel_create(Framecopy_Attrs *attrs);
extern Int Framecopy_accel_config(Framecopy_Handle hFc,
                                  Buffer_Handle hSrcBuf, Buffer_Handle hDstBuf);
extern Int Framecopy_accel_execute(Framecopy_Handle hFc,
                                    Buffer_Handle hSrcBuf,
                                    Buffer_Handle hDstBuf);
extern Int Framecopy_accel_delete(Framecopy_Handle hFc);
#endif

#endif // ti_sdo_dmai__Framecopy_h_
