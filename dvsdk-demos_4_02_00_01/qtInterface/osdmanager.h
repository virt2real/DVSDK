/*
 * osdmanager.h
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

#ifndef OSDMANAGER_H
#define OSDMANAGER_H

#include <QtGui>

class OSDManager : public QObject
{
    Q_OBJECT

public:
    typedef enum {
        OUTPUT_COMPOSITE,
        OUTPUT_COMPONENT,
        OUTPUT_LCD,
        OUTPUT_DVI,
        OUTPUT_SVIDEO,
        DisplayOutput_COUNT
    } DisplayOutput;

    typedef enum {
        MODE_NTSC,
        MODE_PAL,
        MODE_480P_60,
        MODE_720P_60,
        MODE_720P_50,
        MODE_VGA,
        MODE_1080I_30,
        DisplayMode_COUNT
    } DisplayMode;

    OSDManager();
    ~OSDManager();
    bool setDisplayOutput(DisplayOutput output);
    bool setDisplayMode(DisplayMode mode);
    bool showOSD();
    bool hideOSD();
    bool showTransOSD();
    bool incTrans();
    bool decTrans();  
    void setBoxDimensions(int x, int y, int width, int height);
    
private:
    bool setupOsd(char *displayEntry);
    bool setupOsd(int width, int height);
    bool setOsdTransparency(int transparency);
    bool writeSysFs(char *fileName, char *val);
    bool readSysFs(char *fileName, char *val, int length);
    bool setDisplayFormat(DisplayMode mode);
    bool setFormat(char * deviceNode, int numBufs, int * fd, int * size, 
        char ** virtPtr, DisplayMode mode);
    bool writeTransValue();
    bool writeTransFbdev(int val, int x, int y, int width, int height);
    bool writeTransSysfs(int val);

    DisplayMode     m_mode;
    int             m_fdDisplay;
    int             m_fdAttr;
    char *          m_virtPtrDisplay;
    char *          m_virtPtrAttr;
    int             m_sizeDisplay;
    int             m_sizeAttr;
    int             m_transValue;
    int             m_x;
    int             m_y;
    int             m_width;
    int             m_height;
};
 
#endif // OSDMANAGER_H
