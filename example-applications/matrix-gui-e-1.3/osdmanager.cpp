/*
 * {module name} OSDManager
 *
 * {module description} OSD manager module
 *
 * Copyright (C) {YEAR} Texas Instruments Incorporated - http://www.ti.com/ 
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#include "osdmanager.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <linux/fb.h>

#define DISPLAY_DEVICE "/dev/fb0"
#define ATTR_DEVICE    "/dev/fb2"
#define NUM_DISPLAY_BUFS 2
#define NUM_ATTR_BUFS    1

static bool openNode(char * deviceNode, int numBufs, int * fd, int * size, 
    char ** virtPtr) 
{
    struct fb_var_screeninfo varInfo;
    struct fb_fix_screeninfo fixInfo;
    
    *fd = open(deviceNode, O_RDWR);

    if (*fd == -1) {
        qFatal("Failed to open fb device %s (%s)\n", deviceNode,
            strerror(errno));
    }
    
    /* Get fixed screen info */
    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
        qFatal("Failed FBIOGET_FSCREENINFO on %s (%s)\n",
                  deviceNode, strerror(errno));
        return false;
    }

    /* Get virtual screen info */
    if (ioctl(*fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOGET_VSCREENINFO on %s (%s)\n",
            deviceNode, strerror(errno));
        return false;
    }

    // qDebug("Found width=%d height=%d, yres_virtual=%d,xres_virtual=%d,"
    //    " line_length=%d\n", varInfo.xres, varInfo.yres, 
    //    varInfo.yres_virtual,varInfo.xres_virtual, fixInfo.line_length);

    varInfo.xoffset         = 0;
    varInfo.yoffset         = 0;

#if defined(Platform_dm365) 
    // Force 480P as matrix is displayed on component output
    varInfo.xres            = 720; 
    varInfo.yres            = 480;
#else
    // Force 480x272 as matrix is displayed on LCD
    varInfo.xres            = 480; 
    varInfo.yres            = 272;
#endif

    varInfo.xres_virtual    = varInfo.xres;
    varInfo.yres_virtual    = varInfo.yres * numBufs;

    /* Set video display format */
    // qDebug("Setting width=%d height=%d, yres_virtual=%d,"
    //          " xres_virtual=%d\n", varInfo.xres, varInfo.yres,
    //          varInfo.yres_virtual, varInfo.xres_virtual);

    if (ioctl(*fd, FBIOPUT_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOPUT_VSCREENINFO on %s (%s)\n",
                  deviceNode, strerror(errno));
        return false;
    }

    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
        qFatal("Failed FBIOGET_FSCREENINFO on %s (%s)\n",
                  deviceNode, strerror(errno));
        return false;
    }

    //qDebug("New width=%d, height=%d, yres_virtual=%d,xres_virtual=%d, "
    //          "line_length=%d\n", varInfo.xres, varInfo.yres,
    //          varInfo.yres_virtual, varInfo.xres_virtual, fixInfo.line_length);


    *virtPtr = (char *) mmap(NULL,
                            fixInfo.line_length * varInfo.yres * numBufs,
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED,
                            *fd, 0);

    if (*virtPtr == MAP_FAILED) {
        qFatal("Failed mmap on %s (%s)\n", deviceNode,
            strerror(errno));
        return false;
    }
    
    memset(*virtPtr, 0, fixInfo.line_length * varInfo.yres);

    if (ioctl(*fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOGET_VSCREENINFO (%s)\n", strerror(errno));
        return false;
    }

    varInfo.yoffset = 0;

    if (ioctl(*fd, FBIOPAN_DISPLAY, &varInfo) == -1) {
        qFatal("Failed FBIOPAN_DISPLAY (%s)\n", strerror(errno));
        return false;
    }

    if (ioctl(*fd, FBIOBLANK, 0)) {
        qFatal("Error enabling %s\n", deviceNode);
        return false;
    }
    
    *size = fixInfo.line_length * varInfo.yres;
    
    return true;    
}

OSDManager::OSDManager()
{
    m_valid = false;
    
    if (!openNode((char *)DISPLAY_DEVICE, NUM_DISPLAY_BUFS, &m_fdDisplay, 
        &m_sizeDisplay, &m_virtPtrDisplay)) {
        return;
    }    

    if (!openNode((char *)ATTR_DEVICE, NUM_ATTR_BUFS, &m_fdAttr, &m_sizeAttr, 
        &m_virtPtrAttr)) {
        return;
    }    
    
    m_valid = true;
}

void OSDManager::setTransparency(Transparency value)
{
    if (m_valid) {
        memset(m_virtPtrAttr, value, m_sizeAttr);
    }

    return;
}
