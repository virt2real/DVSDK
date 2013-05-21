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

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/Display.h>

#include "priv/_Display.h"

#define MODULE_NAME     "Display"

const Display_Attrs Display_Attrs_DM6446_DM355_ATTR_DEFAULT = {
    1,
    Display_Std_FBDEV,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/fb2",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_DM6446_DM355_OSD_DEFAULT = {
    2,
    Display_Std_FBDEV,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/fb0",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_DM6446_DM355_VID_DEFAULT = {
    3,
    Display_Std_FBDEV,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/fb3",
    0,
    ColorSpace_UYVY,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_OMAPL137_OSD_DEFAULT = {
    1,
    Display_Std_FBDEV,
    VideoStd_QVGA,
    Display_Output_LCD,
    "/dev/fb/0",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_OMAPL138_OSD_DEFAULT = {
    1,
    Display_Std_FBDEV,
    VideoStd_QVGA,
    Display_Output_LCD,
    "/dev/fb0",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_OMAPL138_VID_DEFAULT = {
    3,
    Display_Std_V4L2,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/video2",
    0,
    ColorSpace_YUV422PSEMI,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_DM6467_VID_DEFAULT = {
    3,
    Display_Std_V4L2,
    VideoStd_720P_60,
    Display_Output_COMPONENT,
    "/dev/video2",
    0,
    ColorSpace_YUV422PSEMI,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_DM365_VID_DEFAULT = {
    3,
    Display_Std_V4L2,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/video2",
    0,
    ColorSpace_YUV420PSEMI,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_DM365_OSD_DEFAULT = {
    2,
    Display_Std_FBDEV,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/fb0",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_DM365_ATTR_DEFAULT = {
    1,
    Display_Std_FBDEV,
    VideoStd_D1_NTSC,
    Display_Output_COMPOSITE,
    "/dev/fb2",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_O3530_VID_DEFAULT = {
    3,
    Display_Std_V4L2,
    VideoStd_VGA,
    Display_Output_LCD,
    "/dev/video1",
    0,
    ColorSpace_UYVY,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

const Display_Attrs Display_Attrs_O3530_OSD_DEFAULT = {
    1,
    Display_Std_FBDEV,
    VideoStd_VGA,
    Display_Output_LCD,
    "/dev/fb0",
    0,
    ColorSpace_RGB565,
    -1,
    -1,
    FALSE,
    0,
    0,
    FALSE
};

/* Functions defined in Display_fbdev.c */
extern Display_Handle Display_fbdev_create(BufTab_Handle hBufTab,
                                           Display_Attrs *attrs);
extern Int Display_fbdev_get(Display_Handle hDisplay, Buffer_Handle *hBufPtr);
extern Int Display_fbdev_put(Display_Handle hDisplay, Buffer_Handle hBuf);
extern Int Display_fbdev_delete(Display_Handle hDisplay);
extern Int Display_fbdev_control(Display_Handle hDisplay, 
        Display_Control_Message message, void *parameters, BufTab_Handle hBufTab, Display_Attrs *attrs);


/* Functions defined in Display_v4l2.c */
extern Display_Handle Display_v4l2_create(BufTab_Handle hBufTab,
                                          Display_Attrs *attrs);
extern Int Display_v4l2_get(Display_Handle hDisplay, Buffer_Handle *hBuf);
extern Int Display_v4l2_put(Display_Handle hDisplay, Buffer_Handle hBuf);
extern Int Display_v4l2_delete(Display_Handle hDisplay);
extern Int Display_v4l2_control(Display_Handle hDisplay, 
        Display_Control_Message message, void *parameters, BufTab_Handle hBufTab, Display_Attrs *attrs);

/* Function tables for run time lookup */
static Display_Handle (*createFxns[Display_Std_COUNT])(BufTab_Handle hBufTab,
                                                     Display_Attrs *attrs) = {
    Display_v4l2_create,
    Display_fbdev_create,
};

static Int (*deleteFxns[Display_Std_COUNT])(Display_Handle hDisplay) = {
    Display_v4l2_delete,
    Display_fbdev_delete,
};

static Int (*getFxns[Display_Std_COUNT])(Display_Handle hDisplay,
                                       Buffer_Handle *hBufPtr) = {
    Display_v4l2_get,
    Display_fbdev_get,
};

static Int (*putFxns[Display_Std_COUNT])(Display_Handle hDisplay,
                                       Buffer_Handle hBuf) = {
    Display_v4l2_put,
    Display_fbdev_put,
};

static Int (*controlFxns[Display_Std_COUNT])(Display_Handle hDisplay,
                     Display_Control_Message message, void *parameters, BufTab_Handle hBufTab,
                                          Display_Attrs *attrs) = {
    Display_v4l2_control,
    Display_fbdev_control,
};

/******************************************************************************
 * Display_create
 ******************************************************************************/
Display_Handle Display_create(BufTab_Handle hBufTab, Display_Attrs *attrs)
{
    if (attrs->delayStreamon == TRUE &&
        attrs->displayStd == Display_Std_FBDEV) {
        Dmai_err0("delayStreamon == TRUE not valid for FBDEV displays\n");
        return NULL;
    }
    return createFxns[attrs->displayStd](hBufTab, attrs);
}

/******************************************************************************
 * Display_getVideoStd
 ******************************************************************************/
VideoStd_Type Display_getVideoStd(Display_Handle hDisplay)
{
    return hDisplay->videoStd;
}

/******************************************************************************
 * Display_getBufTab
 ******************************************************************************/
BufTab_Handle Display_getBufTab(Display_Handle hDisplay)
{
    return hDisplay->hBufTab;
}

/******************************************************************************
 * Display_getHandle
 ******************************************************************************/
Int Display_getHandle(Display_Handle hDisplay)
{
    return hDisplay->fd;
}

/******************************************************************************
 * Display_delete
 ******************************************************************************/
Int Display_delete(Display_Handle hDisplay)
{
    return deleteFxns[hDisplay->displayStd](hDisplay);
}

/******************************************************************************
 * Display_get
 ******************************************************************************/
Int Display_get(Display_Handle hDisplay, Buffer_Handle *hBufPtr)
{
    return getFxns[hDisplay->displayStd](hDisplay, hBufPtr);
}

/******************************************************************************
 * Display_put
 ******************************************************************************/
Int Display_put(Display_Handle hDisplay, Buffer_Handle hBuf)
{
    return putFxns[hDisplay->displayStd](hDisplay, hBuf);
}

/******************************************************************************
 * Display_control
 ******************************************************************************/
Int Display_control(Display_Handle hDisplay, 
        Display_Control_Message message, void * parameters, BufTab_Handle hBufTab, 
                                          Display_Attrs *attrs)
{
    return controlFxns[hDisplay->displayStd](hDisplay, message, parameters, hBufTab, attrs);
}
