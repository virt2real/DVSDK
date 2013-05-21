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
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#include <xdc/std.h>
#include <ti/sdo/dmai/Cpu.h>
#include <ti/sdo/dmai/Dmai.h>
#include <ti/sdo/dmai/BufTab.h>
#include <ti/sdo/dmai/Display.h>
#include <ti/sdo/dmai/BufferGfx.h>
#include <ti/sdo/dmai/ColorSpace.h>

#include "priv/_VideoBuf.h"
#include "../priv/_Display.h"

#define MODULE_NAME     "Display"

/* Black color in UYVY format */
#define UYVY_BLACK      0x10801080


/******************************************************************************
 * setDisplayBuffer
 ******************************************************************************/
static Int setDisplayBuffer(Display_Handle hDisplay, Int displayIdx)
{
    return Dmai_EOK;
}

/******************************************************************************
 * cleanup
 ******************************************************************************/
static Int cleanup(Display_Handle hDisplay)
{
    Int                      ret     = Dmai_EOK;
    BufTab_Handle            hBufTab = hDisplay->hBufTab;
    struct fb_var_screeninfo varInfo;
    struct fb_fix_screeninfo fixInfo;

    if (hDisplay->fd != -1) {
        if (ioctl(hDisplay->fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
            Dmai_err1("Failed FBIOGET_FSCREENINFO (%s)\n", strerror(errno));
            ret = Dmai_EFAIL;
        }

        if (ioctl(hDisplay->fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
            Dmai_err1("Failed ioctl FBIOGET_VSCREENINFO (%s)\n",
                      strerror(errno));
            ret =  Dmai_EFAIL;
        }
        
        if (ioctl(hDisplay->fd, FBIOPUT_VSCREENINFO, &hDisplay->origVarInfo) 
                == -1) {
            Dmai_err1("Failed FBIOGET_FSCREENINFO (%s)\n", strerror(errno));
            ret = Dmai_EFAIL;
        }

        if (hBufTab) {
            munmap(Buffer_getUserPtr(BufTab_getBuf(hBufTab, 0)),
                   fixInfo.line_length * varInfo.yres_virtual);

            free(hBufTab);
        }

        setDisplayBuffer(hDisplay, 0);

        close(hDisplay->fd);
    }

    free(hDisplay);

    return ret;
}

/******************************************************************************
 * Display_fbdev_create
 ******************************************************************************/
Display_Handle Display_fbdev_create(BufTab_Handle hBufTab, Display_Attrs *attrs)
{
    BufferGfx_Attrs         gfxAttrs       = BufferGfx_Attrs_DEFAULT;
    struct fb_var_screeninfo varInfo;
    struct fb_fix_screeninfo fixInfo;
    Int                      displaySize;
    Int                      bufIdx;
    Int8                    *virtPtr;
    Int32                    physPtr;
    Int32                    height, width;
    Display_Handle           hDisplay;
    Buffer_Handle            hBuf;

    if (attrs == NULL) {
        Dmai_err0("Must supply valid attrs\n");
        return NULL;
    }

    if (hBufTab != NULL) {
        Dmai_err0("FBdev display does not accept user allocated buffers\n");
        return NULL;
    }

    hDisplay = calloc(1, sizeof(Display_Object));

    if (hDisplay == NULL) {
        Dmai_err0("Failed to allocate space for Display Object\n");
        return NULL;
    }

    /* Open video display device */
    hDisplay->fd = open(attrs->displayDevice, O_RDWR);

    if (hDisplay->fd == -1) {
        Dmai_err2("Failed to open fb device %s (%s)\n", attrs->displayDevice,
                                                        strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    /* Get fixed screen info */
    if (ioctl(hDisplay->fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
        Dmai_err2("Failed FBIOGET_FSCREENINFO on %s (%s)\n",
                  attrs->displayDevice, strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    /* Get virtual screen info */
    if (ioctl(hDisplay->fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
        Dmai_err2("Failed FBIOGET_VSCREENINFO on %s (%s)\n",
                  attrs->displayDevice, strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    Dmai_dbg5("Found width=%d height=%d, yres_virtual=%d,xres_virtual=%d,"
              " line_length=%d\n", varInfo.xres, varInfo.yres, 
                varInfo.yres_virtual,varInfo.xres_virtual, fixInfo.line_length);

    /* Save current virtual screen info. */
    memcpy(&hDisplay->origVarInfo, &varInfo, sizeof(struct fb_var_screeninfo));

    /* If video standard is set to auto then use current height and width */
    if (attrs->videoStd == VideoStd_AUTO) {
        width = varInfo.xres;
        height = varInfo.yres;
    }
    else {
        VideoStd_getResolution(attrs->videoStd, &width, &height);
    }

    varInfo.xoffset         = 0;
    varInfo.yoffset         = 0;
    varInfo.xres            = width;
    varInfo.yres            = height;
    varInfo.xres_virtual    = width;
    varInfo.yres_virtual    = varInfo.yres * attrs->numBufs;

    /* Set video display format */
    Dmai_dbg4("Setting width=%d height=%d, yres_virtual=%d,"
              " xres_virtual=%d\n", varInfo.xres, varInfo.yres, 
              varInfo.yres_virtual, varInfo.xres_virtual);

    if (ioctl(hDisplay->fd, FBIOPUT_VSCREENINFO, &varInfo) == -1) {
        Dmai_err2("Failed FBIOPUT_VSCREENINFO on %s (%s)\n",
                  attrs->displayDevice, strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    if (ioctl(hDisplay->fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
        Dmai_err2("Failed FBIOGET_FSCREENINFO on %s (%s)\n",
                  attrs->displayDevice, strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    Dmai_dbg5("New width=%d, height=%d, yres_virtual=%d,xres_virtual=%d, "
              "line_length=%d\n", varInfo.xres, varInfo.yres, 
              varInfo.yres_virtual, varInfo.xres_virtual, fixInfo.line_length);

    gfxAttrs.dim.width          = varInfo.xres;
    gfxAttrs.colorSpace         = attrs->colorSpace;
    gfxAttrs.dim.height         = varInfo.yres;
    gfxAttrs.dim.lineLength     = fixInfo.line_length;
    gfxAttrs.bAttrs.reference   = TRUE;
    displaySize                 = fixInfo.line_length * varInfo.yres;

    hBufTab = BufTab_create(attrs->numBufs, displaySize,
                            BufferGfx_getBufferAttrs(&gfxAttrs));

    if (hBufTab == NULL) {
        Dmai_err0("Failed to allocate BufTab for display buffers\n");
        cleanup(hDisplay);
        return NULL;
    }

    hBuf = BufTab_getBuf(hBufTab, 0);

    Buffer_setNumBytesUsed(hBuf, varInfo.xres * varInfo.yres *
                                 varInfo.bits_per_pixel / 8);
    virtPtr = (Int8 *) mmap (NULL,
                             displaySize * attrs->numBufs,
                             PROT_READ | PROT_WRITE,
                             MAP_SHARED,
                             hDisplay->fd, 0);

    if (virtPtr == MAP_FAILED) {
        Dmai_err2("Failed mmap on %s (%s)\n", attrs->displayDevice,
                                              strerror(errno));
        cleanup(hDisplay);
        return NULL;
    }

    if (Buffer_setUserPtr(hBuf, virtPtr) < 0) {
        cleanup(hDisplay);
        return NULL;
    }

    _Dmai_blackFill(hBuf);

    Dmai_dbg3("Display buffer %d mapped to %#lx has physical address %#lx\n", 0,
              (Int32) virtPtr, physPtr);

    for (bufIdx=1; bufIdx < attrs->numBufs; bufIdx++) {
        hBuf = BufTab_getBuf(hBufTab, bufIdx);
        Buffer_setNumBytesUsed(hBuf, varInfo.xres * varInfo.yres *
                                     varInfo.bits_per_pixel / 8);

        virtPtr = virtPtr + displaySize;
        Buffer_setUserPtr(hBuf, virtPtr);
        _Dmai_blackFill(hBuf);

        Dmai_dbg3("Display buffer %d mapped to %#lx, physical address %#lx\n",
                  bufIdx, (unsigned long) virtPtr, physPtr);
    }

    hDisplay->hBufTab = hBufTab;
    hDisplay->displayIdx = 0;
    hDisplay->workingIdx = attrs->numBufs > 1 ? 1 : 0;
    hDisplay->displayStd = Display_Std_FBDEV;

    if (setDisplayBuffer(hDisplay, hDisplay->displayIdx) < 0) {
        cleanup(hDisplay);
        return NULL;
    }

    return hDisplay;
}

/******************************************************************************
 * Display_fbdev_delete
 ******************************************************************************/
Int Display_fbdev_delete(Display_Handle hDisplay)
{
    Int ret = Dmai_EOK;

    if (hDisplay) {
        ret = cleanup(hDisplay);
    }

    return ret;
}

/******************************************************************************
 * Display_fbdev_get
 ******************************************************************************/
Int Display_fbdev_get(Display_Handle hDisplay, Buffer_Handle *hBufPtr)
{
    Int dummy;
    BufTab_Handle hBufTab = hDisplay->hBufTab;

    assert(hDisplay);
    assert(hBufPtr);

    dummy = 1;
    *hBufPtr = BufTab_getBuf(hBufTab, hDisplay->workingIdx);

    return Dmai_EOK;
}

/******************************************************************************
 * Display_fbdev_put
 ******************************************************************************/
Int Display_fbdev_put(Display_Handle hDisplay, Buffer_Handle hBuf)
{
    BufTab_Handle hBufTab = hDisplay->hBufTab;
    Int32 numBufs;

    assert(hDisplay);
    assert(hBuf);

    numBufs = BufTab_getNumBufs(hBufTab);

    hDisplay->displayIdx = (hDisplay->displayIdx + 1) % numBufs;
    hDisplay->workingIdx = (hDisplay->workingIdx + 1) % numBufs;

    return setDisplayBuffer(hDisplay, hDisplay->displayIdx);
}

/******************************************************************************
 * Display_fbdev_control
 ******************************************************************************/
Int Display_fbdev_control(Display_Handle hDisplay, 
                          Display_Control_Message message,
                          void * parameters,
                          BufTab_Handle hBufTab, Display_Attrs *attrs)
{
    return Dmai_EOK;
}
