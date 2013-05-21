/*
 * configwindow.h
 *
 * This module handles the definitions and declarations for 
 * the configuration window.
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

#ifndef CONFIG_WINDOW_H
#define CONFIG_WINDOW_H

#include <QWidget>

#include "messageserver.h"
#include "controlwindow.h"

QT_BEGIN_NAMESPACE
class QCheckBox;
class QComboBox;
class QLabel;
class QPushButton;
class QLineEdit;
class QGroupBox;
QT_END_NAMESPACE

class ConfigWindow : public QWidget
{
    Q_OBJECT

public:
    typedef struct Config {
        QString videoStd;
        QString videoInput;
        QString videoFile;
        QString soundFile;
        QString videoBitRate;
        QString videoCodec;
        QString soundBitRate;
        QString samplingRate;
        QString displayOutput;
        bool looping;
        bool disablePreview;
        bool disableFileWrite;
        bool passthrough;
        bool speechSelected;
        QString demo;
    } Config;

    ConfigWindow(Config& cfg, MessageServer * msgServer, ControlWindow * 
        ctrlWindow);
    ~ConfigWindow();

    /*
     * These values need to match display output options from the demos:
     *  1 - Composite, 2 - S-video, 3 - Component, 4 - DVI, 5 - LCD, 6 - SYSTEM
     */
    enum VideoOutput {
        COMPOSITE_OUTPUT=1, 
        SVIDEO_OUTPUT=2, 
        COMPONENT_OUTPUT=3, 
        DVI_OUTPUT=4, 
        LCD_OUTPUT=5, 
        SYSTEM_OUTPUT=6,
    };

    /*
     * These values need to match the ones from the -I option in the demos
     */
    enum VideoInput {
        COMPOSITE_INPUT=1, 
        SVIDEO_INPUT=2, 
        COMPONENT_INPUT=3, 
        CAMERA_INPUT=4,
    };

private slots:
    void videoBitRateChanged();
    void videoStdChanged();
    void videoCodecChanged();
    void soundCodecChanged();
    void soundBitRateChanged();
    void samplingRateChanged();
    void setLooping(bool looping);
    void setDisablePreview(bool disablePreview);
    void setDisableFileWrite(bool disableFileWrite);
    void setPassthrough(bool passthrough);
    void setEncodeVideo(bool doNotEncode);
    void setEncodeSound(bool doNotEncode);
    void setDeinterlaceVideo(bool deinterlace);
    void browseVideo();
    void browseSound();
    void startDemo();
    void exit();

private:
    enum VideoCodecs {H264, MPEG4, MPEG2};
#ifdef Platform_dm365
    enum SoundCodecs {AAC, G711};
#else // Platform_omap3530
    enum SoundCodecs {G711};
#endif

    QPushButton * createButton(const QString &text, const char *member);
    void createVideoGroupBox(Config& cfg);
    void createSoundGroupBox(Config& cfg);
    void createOtherGroupBox();
    void disableUnusedWidgets(Config& cfg);
    QString getVideoExtension();
    QString getSoundExtension();
    QString getcurrentTime();

    QLabel * m_logo;
    QLabel * m_bannerLabel;
    QLabel * m_videoFileLabel;
    QLabel * m_videoBitRateLabel;
    QLabel * m_videoCodecLabel;
    QLabel * m_soundFileLabel;
    QLabel * m_soundCodecLabel;
    QLabel * m_soundBitRateLabel;
    QLabel * m_samplingRateLabel;
    QLabel * m_videoStdLabel;
    QLineEdit * m_videoFileLineEdit;
    QComboBox * m_videoBitRateComboBox;
    QComboBox * m_videoCodecComboBox;
    QComboBox * m_videoStdComboBox;
    QLineEdit * m_soundFileLineEdit;
    QComboBox * m_soundCodecComboBox;
    QComboBox * m_soundBitRateComboBox;
    QComboBox * m_samplingRateComboBox;
    QCheckBox * m_loopingCheckBox;
    QCheckBox * m_disablePreviewCheckBox;
    QCheckBox * m_disableFileWriteCheckBox;
    QCheckBox * m_passthroughCheckBox;
    QCheckBox * m_encodeVideoCheckBox;
    QCheckBox * m_encodeSoundCheckBox;
    QCheckBox * m_deinterlaceVideoCheckBox;
    QPushButton * m_browseVideoButton;
    QPushButton * m_browseSoundButton;
    QPushButton * m_startButton;
    QPushButton * m_exitButton;

    QGroupBox * m_videoGroupBox;
    QGroupBox * m_soundGroupBox;
    QGroupBox * m_otherGroupBox;

    QString m_videoFile;
    QString m_soundFile;
    QString m_videoBitRate;
    QString m_videoCodec;
    QString m_soundCodec;
    QString m_soundBitRate;
    QString m_samplingRate;
    QString m_videoStd;
    bool m_looping;
    bool m_disablePreview;
    bool m_disableFileWrite;
    bool m_passthrough;
    bool m_encodeVideo;
    bool m_encodeSound;
    bool m_deinterlaceVideo;
    bool m_speechSelected;
    QString m_demo;
    
    MessageServer * m_msgServer;
    ControlWindow * m_ctrlWindow;
};

#endif
