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

/* Standard Linux headers */
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/videodev2.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Capture.h>
#include <ti/sdo/dmai/ColorSpace.h>
#include <ti/sdo/dmai/BufferGfx.h>

const Capture_Attrs Capture_Attrs_DM6446_DM355_DEFAULT = {
    3,
    Capture_Input_COMPOSITE,
    -1,
    -1,
    -1,
    -1,
    "/dev/video0",
    FALSE,
    VideoStd_AUTO,
    -1,
    ColorSpace_UYVY,
    NULL,
    FALSE,
};

const Capture_Attrs Capture_Attrs_DM6467_DEFAULT = {
    3,
    Capture_Input_COMPONENT,
    -1,
    -1,
    -1,
    -1,
    "/dev/video0",
    FALSE,
    VideoStd_AUTO,
    -1,
    ColorSpace_YUV422PSEMI,
    NULL,
    FALSE,
};

const Capture_Attrs Capture_Attrs_DM365_DEFAULT = {
    3,
    Capture_Input_COMPONENT,
    -1,
    -1,
    -1,
    -1,
    "/dev/video0",
    FALSE,
    VideoStd_AUTO,
    -1,
    ColorSpace_YUV420PSEMI,
    NULL,
    TRUE
};

const Capture_Attrs Capture_Attrs_OMAPL138_DEFAULT = {
    3,
    Capture_Input_COMPOSITE,
    -1,
    -1,
    -1,
    -1,
    "/dev/video0",
    FALSE,
    VideoStd_AUTO,
    -1,
    ColorSpace_YUV422PSEMI,
    NULL,
    FALSE
};

const Capture_Attrs Capture_Attrs_OMAP3530_DEFAULT = {
    3,
    Capture_Input_COMPOSITE,
    -1,
    -1,
    -1,
    -1,
    "/dev/video0",
    FALSE,
    VideoStd_AUTO,
    -1,
    ColorSpace_UYVY,
    NULL,
    FALSE
};

