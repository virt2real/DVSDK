/*
 * osdmanager.cpp
 *
 * This module handles the definitions and declarations for 
 * the OSD manager.
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
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

#define STD_D1_WIDTH        720     /**< Width in pixels of D1 */
#define STD_D1_NTSC_HEIGHT  480     /**< Height in pixels of D1 NTSC */
#define STD_D1_PAL_HEIGHT   576     /**< Height in pixels of D1 PAL */

#define STD_480P_WIDTH      720     /**< Width in pixels for 480P */
#define STD_480P_HEIGHT     480     /**< Height in pixels for 480P */

#define STD_720P_WIDTH      1280    /**< Width in pixels of 720P */
#define STD_720P_HEIGHT     720     /**< Height in pixels of 720P */

#define STD_1080I_WIDTH     1920    /**< Width in pixels of 1080I */
#define STD_1080I_HEIGHT    1080    /**< Height in pixels of 1080I */

#define DISPLAY_DEVICE           "/dev/fb0"
#define NUM_DISPLAY_BUFS         2

#ifdef Platform_dm365
    #define SYSFS_OUTPUT            "/sys/class/davinci_display/ch0/output"
    #define SYSFS_MODE              "/sys/class/davinci_display/ch0/mode"
    #define ATTR_DEVICE             "/dev/fb2"
    #define NUM_ATTR_BUFS           1
    #define FBDEV_OSD               "/dev/fb0"

    #define MAX_TRANSPARENCY            0x77
    #define MIN_TRANSPARENCY            0x0
    #define NORMAL_TRANSPARENCY         0x55
    #define INC_TRANSPARENCY            0x11
    #define MIN_VISIBLE_TRANSPARENCY    0x11

    /* Strings for sysfs video output variables */
    static char * outputStrings[] = {
        (char *)"COMPOSITE",
        (char *)"COMPONENT",
        (char *)"LCD",
    };

    /* Strings for sysfs video mode variables */
    static char * modeStrings[] = {
        (char *)"NTSC",
        (char *)"PAL",
        (char *)"480P-60",
        (char *)"720P-60",
        (char *)"720P-50",
        (char *)"VGA",
        (char *)"1080I-30",
    };

    static void cleanup(int fd, char * virtPtr,
                        struct fb_var_screeninfo * varInfo, 
                        struct fb_fix_screeninfo * fixInfo)
    {
        if (virtPtr != NULL) {
            munmap(virtPtr, fixInfo->line_length * varInfo->yres_virtual);
        }
        ::close(fd);
    }
#else // Platform_omap3530
    #define DSSFILE "/sys/devices/platform/omapdss/%s"
    #define FBDEV_OSD "/dev/fb0"

    #define writeDss(x,y) \
        sprintf(fmt, DSSFILE, (x)); \
        if (writeSysFs(fmt, (y)) != true) return false

    #define MIN_TRANSPARENCY            0x00
    #define MAX_TRANSPARENCY            0xff
    #define NORMAL_TRANSPARENCY         0xaa
    #define INC_TRANSPARENCY            0x11
    #define MIN_VISIBLE_TRANSPARENCY    0x33
#endif

#define OMAP_DSS_GLOBAL_ALPHA \
    "/sys/devices/platform/omapdss/overlay0/global_alpha"

OSDManager::OSDManager()
{
    m_x = 0;
    m_y = 0;
    m_width = STD_480P_WIDTH;
    m_height = STD_480P_HEIGHT;
}

bool OSDManager::setFormat(char * deviceNode, int numBufs, int * fd, int * size, 
    char ** virtPtr, DisplayMode mode) 
{
#ifdef Platform_dm365
    struct fb_var_screeninfo varInfo;
    struct fb_fix_screeninfo fixInfo;
    *virtPtr = NULL;

    *fd = ::open(deviceNode, O_RDWR);

    if (*fd == -1) {
        qFatal("Failed to open fb device %s (%s)\n", deviceNode,
            strerror(errno));
        return false;
    }
 
    /* Get fixed screen info */
    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
        qFatal("Failed FBIOGET_FSCREENINFO on %s (%s)\n",
                  deviceNode, strerror(errno));
        cleanup(*fd, NULL, NULL, NULL);
        return false;
    }

    /* Get virtual screen info */
    if (ioctl(*fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOGET_VSCREENINFO on %s (%s)\n",
            deviceNode, strerror(errno));
        cleanup(*fd, NULL, NULL, NULL);
        return false;
    }

    // qDebug("Found width=%d height=%d, yres_virtual=%d,xres_virtual=%d,"
    //    " line_length=%d\n", varInfo.xres, varInfo.yres, 
    //    varInfo.yres_virtual,varInfo.xres_virtual, fixInfo.line_length);

    varInfo.xoffset         = 0;
    varInfo.yoffset         = 0;

    switch (mode) { 
        case MODE_PAL:
            varInfo.xres        = STD_D1_WIDTH; 
            varInfo.yres        = STD_D1_PAL_HEIGHT;
            break;
        case MODE_NTSC:
        case MODE_480P_60:
            varInfo.xres        = STD_D1_WIDTH; 
            varInfo.yres        = STD_D1_NTSC_HEIGHT;
            break;
        case MODE_720P_60:
        case MODE_720P_50:
            varInfo.xres        = STD_720P_WIDTH; 
            varInfo.yres        = STD_720P_HEIGHT;
            break;
        case MODE_1080I_30:
            varInfo.xres        = STD_1080I_WIDTH;
            varInfo.yres        = STD_1080I_HEIGHT;
            break;
        default:
            qFatal("Unsupported standard\n");
            cleanup(*fd, NULL, NULL, NULL);
            return false;
    }

    varInfo.xres_virtual    = varInfo.xres;
    varInfo.yres_virtual    = varInfo.yres * numBufs;

    /* Set video display format */
    if (ioctl(*fd, FBIOPUT_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOPUT_VSCREENINFO on %s (%s)\n",
                  deviceNode, strerror(errno));
        cleanup(*fd, NULL, NULL, NULL);
        return false;
    }

    if (ioctl(*fd, FBIOGET_FSCREENINFO, &fixInfo) == -1) {
        qFatal("Failed FBIOGET_FSCREENINFO on %s (%s)\n",
                  deviceNode, strerror(errno));
        cleanup(*fd, NULL, NULL, NULL);
        return false;
    }

    *virtPtr = (char *) mmap(NULL,
                            fixInfo.line_length * varInfo.yres * numBufs,
                            PROT_READ | PROT_WRITE,
                            MAP_SHARED,
                            *fd, 0);

    if (*virtPtr == MAP_FAILED) {
        qFatal("Failed mmap on %s (%s)\n", deviceNode,
            strerror(errno));
        cleanup(*fd, NULL, NULL, NULL);
        return false;
    }
    
    memset(*virtPtr, 0, fixInfo.line_length * varInfo.yres);

    if (ioctl(*fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOGET_VSCREENINFO (%s)\n", strerror(errno));
        cleanup(*fd, *virtPtr, &varInfo, &fixInfo);
        return false;
    }

    varInfo.yoffset = 0;

    if (ioctl(*fd, FBIOPAN_DISPLAY, &varInfo) == -1) {
        qFatal("Failed FBIOPAN_DISPLAY (%s)\n", strerror(errno));
        cleanup(*fd, *virtPtr, &varInfo, &fixInfo);
        return false;
    }

    if (ioctl(*fd, FBIOBLANK, 0)) {
        qFatal("Error enabling %s\n", deviceNode);
        cleanup(*fd, *virtPtr, &varInfo, &fixInfo);
        return false;
    }
    
    *size = fixInfo.line_length * varInfo.yres;

    cleanup(*fd, *virtPtr, &varInfo, &fixInfo);
#else
    /* Keep compiler happy */
    deviceNode = deviceNode;
    numBufs = numBufs;
    fd = fd;
    size = size;
    virtPtr = virtPtr;
    mode = mode;
#endif

    return true;
}

bool OSDManager::setDisplayFormat(DisplayMode mode)
{
#ifdef Platform_dm365
    /* Setup display device */
    if (!setFormat((char *)DISPLAY_DEVICE, NUM_DISPLAY_BUFS, &m_fdDisplay, 
        &m_sizeDisplay, &m_virtPtrDisplay, mode)) {
        return false;
    }  

    /* Setup attribute device */
    if (!setFormat((char *)ATTR_DEVICE, NUM_ATTR_BUFS, &m_fdAttr, &m_sizeAttr, 
        &m_virtPtrAttr, mode)) {
        return false;
    }
#else
    /* Keep compiler happy */
    mode = mode;
#endif

    return true;
}

bool OSDManager::setDisplayMode(DisplayMode mode)
{
#ifdef Platform_dm365
    char sysFsFileName[] = SYSFS_MODE;

    m_mode = mode;

    if (writeSysFs(sysFsFileName, modeStrings[mode]) 
        < 0) {
        qFatal("Could not write display mode to sysfs\n");
        return false;
    }

    if (!setDisplayFormat(mode)) {
        qFatal("Could not set display format in interface\n");
        return false;
    }
#else // Platform_omap3530
    m_mode = mode;
#endif

    return true;
}

bool OSDManager::setupOsd(int width, int height)
{
    int fd;
    struct fb_var_screeninfo varInfo;

    fd = open(FBDEV_OSD, O_RDWR);

    if (fd == -1) {
        qFatal("Failed to open %s\n", FBDEV_OSD);
        return false;
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &varInfo) == -1) {
        qFatal("Failed FBIOGET_VSCREENINFO on /dev/fb0 (%s)\n",
               strerror(errno));
        close(fd);
        return false;
    }

    /* Change the resolution */
    varInfo.xres            = width;
    varInfo.yres            = height;
    varInfo.xres_virtual    = width;
    varInfo.yres_virtual    = height;

    /* Set up ARGB8888 */
    varInfo.red.length      = 8;
    varInfo.green.length    = 8;
    varInfo.blue.length     = 8;
    varInfo.transp.length   = 8;
    varInfo.transp.offset   = 24;
    varInfo.red.offset      = 16;
    varInfo.green.offset    = 8;
    varInfo.blue.offset     = 0;
    varInfo.bits_per_pixel  = 32;

    if (ioctl(fd, FBIOPUT_VSCREENINFO, &varInfo) < 0) {
        printf("Failed FBIOPUT_VSCREENINFO on /dev/fb0 (%s)\n",
               strerror(errno));
        return false;
    }

    return true;
}

bool OSDManager::readSysFs(char *fileName, char *val, int length)
{
    FILE *fp;
    int ret;
    int len;
    char *tok;

    fp = fopen(fileName, "r");

    if (fp == NULL) {
        printf("Failed to open %s for reading\n", fileName);
        return false;
    }

    memset(val, '\0', length);

    ret = fread(val, 1, length, fp);

    if (ret < 1) {
        printf("Failed to read sysfs variable from %s\n", fileName);
        return false;
    }

    tok = strtok(val, "\n");
    len = tok ? strlen(tok) : strlen(val);
    val[len] = '\0';

    fclose(fp);

    return true;
}

bool OSDManager::setDisplayOutput(DisplayOutput output)
{
#ifdef Platform_dm365
    char sysFsFileName[] = SYSFS_OUTPUT;

    if (writeSysFs(sysFsFileName, outputStrings[output]) 
        < 0) {
        qFatal("Could not write display output to sysfs\n");
        return false;
    }
#else // Platform_omap3530
    /* The mode is dictated by the output */
    char fmt[200];

    writeDss((char *) "overlay0/enabled", (char *) "0");
    writeDss((char *) "overlay1/enabled", (char *) "0");
    writeDss((char *) "overlay2/enabled", (char *) "0");

    system("echo \"\" > /sys/devices/platform/omapdss/overlay0/manager");
    system("echo \"\" > /sys/devices/platform/omapdss/overlay1/manager");
    system("echo \"\" > /sys/devices/platform/omapdss/overlay2/manager");

    writeDss((char *) "display0/enabled", (char *) "0");
    writeDss((char *) "display1/enabled", (char *) "0");
    writeDss((char *) "display2/enabled", (char *) "0");

    switch(output) {
        case OSDManager::OUTPUT_LCD:
            if (setupOsd(480, 640) != true) {
                return false;
            }
            writeDss((char *) "overlay0/manager", (char *) "lcd");
            writeDss((char *) "overlay1/manager", (char *) "lcd");
            writeDss((char *) "overlay2/manager", (char *) "lcd");
            writeDss((char *) "manager0/display", (char *) "lcd");
            writeDss((char *) "display0/timings",
                     (char *) "19200,480/1/28/2,640/1/1/1");
            writeDss((char *) "display0/enabled", (char *) "1");
            writeDss((char *) "overlay0/enabled", (char *) "1");
            break;
        case OSDManager::OUTPUT_COMPOSITE:
        case OSDManager::OUTPUT_SVIDEO:
            if (setupOsd(720, 482) != true) {
                return false;
            }
            writeDss((char *) "overlay0/manager", (char *) "tv");
            writeDss((char *) "overlay1/manager", (char *) "tv");
            writeDss((char *) "overlay2/manager", (char *) "tv");
            writeDss((char *) "display1/enabled", (char *) "1");
            writeDss((char *) "overlay0/enabled", (char *) "1");
            writeDss((char *) "display1/timings",
                     (char *) "13500,720/16/58/64,482/6/31/6");
            break;
        case OSDManager::OUTPUT_DVI:
            if (setupOsd(1280, 720) != true) {
                return false;
            }
            writeDss((char *) "manager0/display", (char *) "dvi");
            writeDss((char *) "overlay0/manager", (char *) "lcd");
            writeDss((char *) "overlay1/manager", (char *) "lcd");
            writeDss((char *) "overlay2/manager", (char *) "lcd");
            writeDss((char *) "overlay0/enabled", (char *) "1");
            writeDss((char *) "display2/timings",
                     (char *) "72434,1280/190/120/32,720/13/3/5");
            writeDss((char *) "display2/enabled", (char *) "1");
            break;
        default:
            /* Should not happen */
            break;
    }
#endif

    return true;
}

bool OSDManager::writeSysFs(char *fileName, char *val)
{
    FILE *fp;
    char *valString;

    valString = (char *)malloc(strlen(val) + 1);

    if (valString == NULL) {
        qFatal("Failed to allocate memory for temporary string\n");
        return false;
    }

    fp = fopen(fileName, "w");

    if (fp == NULL) {
        qFatal("Failed to open %s for writing\n", fileName);
        free(valString);
        return false;
    }

    if (fwrite(val, strlen(val) + 1, 1, fp) != 1) {
        qFatal("Failed to write sysfs variable %s to %s\n",
                  fileName, val);
        fclose(fp);
        free(valString);
        return false;
    }

    fclose(fp);

    free(valString);

    return true;
}

bool OSDManager::writeTransValue()
{
#ifdef Platform_omap3530
    char trans[10];
    sprintf(trans, "%d", m_transValue);
    return writeSysFs(
        (char *) "/sys/devices/platform/omapdss/overlay0/global_alpha", trans);
#else // Platform_dm365
        return writeTransFbdev(m_transValue, m_x, m_y, m_width, m_height);
#endif

    return false;
}


bool OSDManager::writeTransSysfs(int val)
{
    FILE *fptr;
    char str[4];

    sprintf(str, "%d", val);

    fptr = fopen(OMAP_DSS_GLOBAL_ALPHA, "w");

    if (fptr == NULL) {
        qFatal("Failed to open handle");
        return false;
    }

    fwrite(str, 4, 1, fptr);
    fclose(fptr);

    return true;
}

bool OSDManager::writeTransFbdev(int val, int x, int y, int width, int height)
{
#if Platform_dm365
    struct fb_var_screeninfo    vScreenInfo;
    struct fb_fix_screeninfo    fScreenInfo;
    unsigned short              *attrDisplay;
    int attrSize;
    int bitsPerPixel;
    int offset;

    int fd = open("/dev/fb2", O_RDWR);
    if (fd < 0) {
        qFatal("Failed to open /dev/fb2");
        return false;
    }
    
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fScreenInfo) == -1) {
        ::close(fd);
        qFatal("Failed to get fixed screen info");
        return false;
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &vScreenInfo) == -1) {
        ::close(fd);
        qFatal("Failed to get virtual screen info");
        return false;
    }

    attrSize = fScreenInfo.line_length * vScreenInfo.yres;
    bitsPerPixel = 8 * fScreenInfo.line_length / vScreenInfo.xres;

    attrDisplay = (unsigned short *) mmap(NULL, attrSize, 
        PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (attrDisplay == MAP_FAILED) {
        qFatal("Failed to map the attribute window");
        ::close(fd);
        return false;
    }

    // First make full screen transparent
    memset(attrDisplay, MIN_TRANSPARENCY, attrSize);

    // Write transparency value to rectangle defined by function arguments
    for (int i = y; i < y + height; i++) {
        offset = ((x * bitsPerPixel) / 8 + (fScreenInfo.line_length * i)) / 
            sizeof(unsigned short);
        memset(attrDisplay + offset, val, bitsPerPixel * width / 8);
    }
 
    munmap(attrDisplay, attrSize);
    ::close(fd);
#else
    val = val;
    x = x;
    y = y;
    width = width;
    height = height;
#endif

    return true;
}


bool OSDManager::incTrans()
{
    if (m_transValue + INC_TRANSPARENCY <= MAX_TRANSPARENCY) {
        m_transValue += INC_TRANSPARENCY;
    }
    else {
        m_transValue = MAX_TRANSPARENCY;
    }
    return writeTransValue();
}

bool OSDManager::decTrans()
{
    /* 
     * We make sure the OSD does not completely disappear when decrementing
     * transparency
     */
    if (m_transValue - INC_TRANSPARENCY > MIN_VISIBLE_TRANSPARENCY) {
        m_transValue -= INC_TRANSPARENCY;
    }
    else {
        m_transValue = MIN_VISIBLE_TRANSPARENCY;
    }
    return writeTransValue();
}

bool OSDManager::showTransOSD()
{
    m_transValue = NORMAL_TRANSPARENCY;
    return writeTransValue();
}

bool OSDManager::hideOSD()
{
    m_transValue = MIN_TRANSPARENCY;
    return writeTransValue();
}

bool OSDManager::showOSD()
{
    m_transValue = MAX_TRANSPARENCY;
    return writeTransValue();
}

void OSDManager::setBoxDimensions(int x, int y, int width, int height)
{
    m_x = x;
    m_y = y;
    m_width = width;
    m_height = height;
}

OSDManager::~OSDManager()
{
    showOSD();
}

