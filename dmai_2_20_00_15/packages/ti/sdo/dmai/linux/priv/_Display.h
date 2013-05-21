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

#ifndef ti_sdo_dmai__Display_h_
#define ti_sdo_dmai__Display_h_

#include <linux/fb.h>
#if defined(Dmai_Device_omap3530)
#include <linux/omapfb.h>
#endif

typedef struct Display_Object {
    Int                  fd;
    Int                  frameSkip;
    Int                  started;
    Int                  userAlloc;
    Int                  displayIdx;
    Int                  workingIdx;
    Display_Std          displayStd;
    VideoStd_Type        videoStd;
    BufTab_Handle        hBufTab;
    struct _VideoBufDesc *bufDescs;
    struct fb_var_screeninfo origVarInfo;
    Display_Attrs        attrs;
} Display_Object;

extern int _Display_sysfsChange(Display_Output *displayOutput, 
                            char* displayDevice, VideoStd_Type *videoType, 
                            Int *rotation);
extern int _Display_enableDevice(Display_Attrs *attrs, Bool Enable);

#endif // ti_sdo_dmai_Display_h_
