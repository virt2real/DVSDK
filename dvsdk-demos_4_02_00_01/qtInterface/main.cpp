/*
 * main.cpp
 *
 * QT user interface for DVSDK demos
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

#include <stdlib.h>

#include <QApplication>
#include <QStringList>
#include <QWSServer>

#include "qtinterface.h"
#include "configwindow.h"
#include "osdmanager.h"
#include "controlwindow.h"


static void usage()
{
    fprintf(stderr, "This application is meant to be launched by the DVSDK \
        demos, and is not supposed to be run standalone.\n");
    exit(1);
}

static void extractConfig(ConfigWindow::Config & cfg, const QStringList& args)
{
    cfg.looping = false;
    cfg.passthrough = false;
    cfg.speechSelected = false;
    cfg.disablePreview = false;
    cfg.disableFileWrite = false;

    for (int i = 0; i < args.count(); i++) {
        const QString &at = args.at(i);
        if (at.startsWith("-h")) {
            usage();
        }
        else if (at.startsWith("-d")) {
            cfg.demo = args.at(++i);           
        }
        else if (at.startsWith("-v")) {
            if (cfg.demo == "Encodedecode") {
                cfg.videoCodec = args.at(++i);
            }
            else if ((cfg.demo == "Decode") || (cfg.demo == "Encode")) {
                cfg.videoFile = args.at(++i);
            }

        }
        else if (at.startsWith("-a")) {
            cfg.speechSelected = false;
            cfg.soundFile = args.at(++i);
        }
        else if (at.startsWith("-s")) {
            cfg.speechSelected = true;
            cfg.soundFile = args.at(++i);
        }
        else if (at.startsWith("-b")) {
            cfg.videoBitRate = args.at(++i);
        }
        else if (at.startsWith("-u")) {
            cfg.samplingRate = args.at(++i);
        }
        else if (at.startsWith("-l")) {
            cfg.looping = true;
        }
        else if (at.startsWith("-w")) {
            cfg.disablePreview = true;
        }
        else if (at.startsWith("-f")) {
            cfg.disableFileWrite = true;
        }
        else if (at.startsWith("-p")) {
            if (cfg.demo == "Encode") {
                cfg.soundBitRate = args.at(++i);
            }
            else if (cfg.demo == "Encodedecode") {
                cfg.passthrough = true;
            }
        }
        else if (at.startsWith("-I")) {
            cfg.videoInput = args.at(++i);
        }
        else if (at.startsWith("-y")) {
            cfg.videoStd = args.at(++i);
        }
    }
}

int main(int argc, char *argv[])
{
    OSDManager osd;
    ConfigWindow::Config cfg;

    // Find the argument that specifies the video standard
    for (int i = 0; i < argc; i++) {
        if (strcmp(argv[i], "-y") == 0) {
            cfg.videoStd = argv[i+1];
        }
        else if (strcmp(argv[i], "-O") == 0) {
            cfg.displayOutput = argv[i+1];
        }
    }

    /*
     * Set the display output for OSD
     * Note that we must initialize OSD prior to creating app, or QT gets
     * confused when the app exits.
     * Accepted display output options (-O) are as follow:
     *  1 - Composite, 2 - S-video, 3 - Component, 4 - DVI, 5 - LCD, 6 - SYSTEM
     */
    switch (cfg.displayOutput.toUInt()) {
        case ConfigWindow::COMPOSITE_OUTPUT:
            if (!osd.setDisplayOutput(OSDManager::OUTPUT_COMPOSITE)) {
                qFatal("Could not set display output in interface\n");
                return -1;
            }
            break;
        case ConfigWindow::SVIDEO_OUTPUT:
            if (!osd.setDisplayOutput(OSDManager::OUTPUT_SVIDEO)) {
                qFatal("Could not set display output in interface\n");
                return -1;
            }
            break;
        case ConfigWindow::COMPONENT_OUTPUT:
            if (!osd.setDisplayOutput(OSDManager::OUTPUT_COMPONENT)) {
                qFatal("Could not set display output in interface\n");
                return -1;
            }
            break;
        case ConfigWindow::DVI_OUTPUT:
            if (!osd.setDisplayOutput(OSDManager::OUTPUT_DVI)) {
                qFatal("Could not set display output in interface\n");
                return -1;
            }
            break;
        case ConfigWindow::LCD_OUTPUT:
            if (!osd.setDisplayOutput(OSDManager::OUTPUT_LCD)) {
                qFatal("Could not set display output in interface\n");
                return -1;
            }
            break;
        case ConfigWindow::SYSTEM_OUTPUT:
            /* do not do anything */
            break;
        default:
            qFatal("Unsupported video standard passed to interface\n");
            return -1;
    }

    /* 
     * Set the display mode based on video standard passed on command line
     * Accepted video standard options (-y) are as follow:
     *  1 - NTSC, 2 - PAL, 3 - 720P 60Hz, 4 - 720P 50 Hz, 6 - VGA, 
     *  7 - 480P 60 Hz
     */
    switch (cfg.videoStd.toUInt()) {
        case 1: //Video Std NTSC
            if (!osd.setDisplayMode(OSDManager::MODE_NTSC)) {
                qFatal("Could not set display mode in interface\n");
                return -1;
            }
            break;
        case 2:  //Video Std PAL
            if (!osd.setDisplayMode(OSDManager::MODE_PAL)) {
                qFatal("Could not set display mode in interface\n");
                return -1;
            }
            break;
        case 6:  //Video Std VGA
            if (!osd.setDisplayMode(OSDManager::MODE_VGA)) {
                qFatal("Could not set display mode in interface\n");
                return -1;
            }
            break;
        case 3:  //Video Std 720P 60Hz
#ifdef Platform_omap3530
            /* 
             * On OMAP we need to use the full screen for the OSD, given the 
             * OSD window is mobile. On other platforms, we reduce the 
             * resolution of the OSD to save on bandwidth.
             */
            if (!osd.setDisplayMode(OSDManager::MODE_720P_60)) {
                qFatal("Could not set display mode in interface\n");
                return -1;
            }
            break;
#endif
        case 4:  //Video Std 720P 50Hz
        case 5:  //Video Std 1080I 30Hz
        case 7:  //Video Std 480P 60Hz     
            if (!osd.setDisplayMode(OSDManager::MODE_480P_60)) {
                qFatal("Could not set display mode in interface\n");
                return -1;
            }
            break;
        default:
            qFatal("Unsupported video standard passed to interface\n");
            return -1;
    }

#ifdef Platform_omap3530
    QWSServer::setBackground(QBrush(QColor(0, 0, 0, 0)));
#endif

    qDebug("Starting interface\n"); 
    QApplication app(argc, argv);

    const QStringList args(app.arguments());
    extractConfig(cfg, args);

    /* Create message server */
    MessageServer msgServer;
    /* Start message server to interact with demo */
    msgServer.start(QThread::HighPriority);

    /* Create control window */
    ControlWindow ctrlWindow(&msgServer, &osd);

    /* Create configuration Window */
    ConfigWindow window(cfg, &msgServer, &ctrlWindow);
    /* Show Configuration Window */
    window.showFullScreen();
 
    osd.showTransOSD();

    return app.exec();
}

