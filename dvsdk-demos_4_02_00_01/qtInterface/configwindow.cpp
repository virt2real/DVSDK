/*
 * configwindow.cpp
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

#include <QtGui>

#include "configwindow.h"
#include "controlwindow.h"

#define DEFAULT_VIDEO_FILE "/usr/share/ti/data/videos/myvideo"
#define DEFAULT_SOUND_FILE "/usr/share/ti/data/sounds/mysound"

ConfigWindow::ConfigWindow(Config& cfg, MessageServer * msgServer, 
    ControlWindow * ctrlWindow)
{
    QString datetime = getcurrentTime();
    m_msgServer = msgServer;
    m_ctrlWindow = ctrlWindow;
    
    m_demo = cfg.demo;
    m_videoFile = cfg.videoFile;
    m_soundFile = cfg.soundFile;
    m_speechSelected = cfg.speechSelected;

    m_logo = new QLabel(tr(""));
    m_logo->setPixmap(QPixmap(":images/hdr_ti_logo.png"));

    QFont serifFont("Times", 22, QFont::Bold);
    m_bannerLabel = new QLabel(m_demo + tr(" Demo"));
    m_bannerLabel->setFont(serifFont);

    createVideoGroupBox(cfg);
    createSoundGroupBox(cfg);
    createOtherGroupBox();

    QGridLayout *buttonsLayout = new QGridLayout;
    m_startButton = createButton(tr("Start demo"), SLOT(startDemo()));
    m_exitButton = createButton(tr("Exit"), SLOT(exit()));
    buttonsLayout->setRowMinimumHeight(2, 60);
    buttonsLayout->addWidget(m_logo, 1, 0, 1, 1);
    buttonsLayout->addWidget(m_startButton, 1, 2, 1, 1);
    buttonsLayout->addWidget(m_exitButton, 1, 3, 1, 1);
    buttonsLayout->setColumnStretch(0, 10);
    buttonsLayout->setColumnStretch(1, 10);

    QVBoxLayout *mainLayout = new QVBoxLayout;

    mainLayout->addWidget(m_bannerLabel);
    mainLayout->addWidget(m_videoGroupBox);
    mainLayout->addWidget(m_soundGroupBox);
    mainLayout->addWidget(m_otherGroupBox);
    mainLayout->addLayout(buttonsLayout);

    mainLayout->setStretchFactor(m_bannerLabel, 1);
    mainLayout->setStretchFactor(m_videoGroupBox, 5);
    mainLayout->setStretchFactor(m_soundGroupBox, 5);
    mainLayout->setStretchFactor(m_otherGroupBox, 2);

    /* To prevent rows from overlapping one another */
    mainLayout->setSpacing(0);
    
    mainLayout->setContentsMargins(0,0,0,0);
    #if defined(Platform_dm365)
    mainLayout->setContentsMargins(50,39,50,39);
    #endif
  
    setLayout(mainLayout);

    disableUnusedWidgets(cfg);

    if (!m_videoBitRateComboBox->isHidden()) {
        videoBitRateChanged();
    }
    if (!m_videoCodecComboBox->isHidden()) {
        videoCodecChanged();
    }
    if (!m_videoStdComboBox->isHidden()) {
        if (cfg.videoStd == "3") {
            m_videoStdComboBox->setCurrentIndex(0);   //720P
        }
        else {
            m_videoStdComboBox->setCurrentIndex(1);   //1080I
        }
        videoStdChanged();
    }
    if (!m_soundCodecComboBox->isHidden()) {
        soundCodecChanged();
    }
    if (!m_soundBitRateComboBox->isHidden()) {
        soundBitRateChanged();
    }
    if (!m_samplingRateComboBox->isHidden()) {
        samplingRateChanged();
    }
    if (!m_loopingCheckBox->isHidden()) {
        m_loopingCheckBox->setChecked(cfg.looping);
    }
    if (!m_disablePreviewCheckBox->isHidden()) {
        m_disablePreviewCheckBox->setChecked(cfg.disablePreview);
    }
    if (!m_disableFileWriteCheckBox->isHidden()) {
        m_disableFileWriteCheckBox->setChecked(cfg.disableFileWrite);
    }
    if (!m_passthroughCheckBox->isHidden()) {
        m_passthroughCheckBox->setChecked(cfg.passthrough);
    }
    if (!m_encodeVideoCheckBox->isHidden()) {
        m_encodeVideoCheckBox->setChecked(false);
    }
    if (!m_encodeSoundCheckBox->isHidden()) {
        m_encodeSoundCheckBox->setChecked(true); // Sound is disabled by default
    }

    /* 
     * For encode demo, set default filenames given we do not officially
     * support keyboard input.
     */
    if (cfg.demo == "Encode") { 
        if (cfg.videoFile.isEmpty()) {   
            m_videoFile = DEFAULT_VIDEO_FILE + datetime + getVideoExtension();
            m_videoFileLineEdit->setText(m_videoFile);
        }
        if (cfg.soundFile.isEmpty()) {
            m_soundFile = DEFAULT_SOUND_FILE + datetime + getSoundExtension();
            m_soundFileLineEdit->setText(m_soundFile);
        }
    }

    setWindowTitle(tr("Demo configuration"));
}

QString ConfigWindow::getcurrentTime()
{
  char buffer[256];
  time_t curtime;
  struct tm *loctime;

  /* Get the current time.  */
  curtime = time (NULL);

  /* Convert it to local time representation.  */
  loctime = localtime (&curtime);

  /* Print it out in a nice format.  */
  strftime (buffer, 256, "_%I_%M", loctime);

  QString qstring(buffer);

  return qstring;
}

void ConfigWindow::createVideoGroupBox(Config& cfg)
{
    m_videoGroupBox = new QGroupBox(tr("Video"));
    QGridLayout *layout = new QGridLayout;

    m_browseVideoButton = createButton(tr("Browse..."), SLOT(browseVideo()));

    m_videoFileLineEdit = new QLineEdit;
    m_videoFileLineEdit->setText(cfg.videoFile);
    m_videoFileLabel = new QLabel(tr("Video file:"));
    m_videoFileLabel->setBuddy(m_videoFileLineEdit);

    m_videoBitRateComboBox = new QComboBox;
    m_videoBitRateComboBox->addItem(tr("0.5 Mbps"), 500000);
    m_videoBitRateComboBox->addItem(tr("1 Mbps"), 1000000);
    m_videoBitRateComboBox->addItem(tr("2 Mbps"), 2000000);
    m_videoBitRateComboBox->addItem(tr("4 Mbps"), 4000000);
#ifdef Platform_dm365
    m_videoBitRateComboBox->addItem(tr("8 Mbps"), 8000000);
#endif
    m_videoBitRateComboBox->setToolTip("Note: Increasing bit rate may reduce" 
        " performance.");

    /* Set default to 1 Mbps */
    m_videoBitRateComboBox->setCurrentIndex(1);

    m_videoBitRateLabel = new QLabel(tr("Video bit rate:"));
    m_videoBitRateLabel->setBuddy(m_videoBitRateComboBox);

    m_videoCodecComboBox = new QComboBox;
    m_videoCodecComboBox->addItem(tr("H264"), "h264");
    m_videoCodecComboBox->addItem(tr("MPEG4"), "mpeg4");
#ifdef Platform_dm365
    m_videoCodecComboBox->addItem(tr("MPEG2"), "mpeg2");
#endif

    m_videoCodecLabel = new QLabel(tr("Codec:"));
    m_videoCodecLabel->setBuddy(m_videoCodecComboBox);

    m_videoStdComboBox = new QComboBox;
    m_videoStdComboBox->addItem(tr("720"), "3");   // -y3 in demo
    m_videoStdComboBox->addItem(tr("1080"), "5");  // -y5 in demo

    m_videoStdLabel = new QLabel(tr("HD video standard:"));
    m_videoStdLabel->setBuddy(m_videoStdComboBox);

    m_encodeVideoCheckBox = new QCheckBox(tr("Disable video"));
    m_deinterlaceVideoCheckBox = new QCheckBox(tr("Deinterlace"));

    connect(m_deinterlaceVideoCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setDeinterlaceVideo(bool)));
    connect(m_encodeVideoCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setEncodeVideo(bool)));
    connect(m_videoBitRateComboBox, SIGNAL(activated(int)),
            this, SLOT(videoBitRateChanged()));
    connect(m_videoCodecComboBox, SIGNAL(activated(int)),
            this, SLOT(videoCodecChanged()));
    connect(m_videoStdComboBox, SIGNAL(activated(int)),
            this, SLOT(videoStdChanged()));

    layout->addWidget(m_videoFileLabel, 1, 0, Qt::AlignLeft);
    layout->addWidget(m_videoFileLineEdit, 1, 1, 1, 5);
    layout->addWidget(m_browseVideoButton, 1, 6);
    layout->addWidget(m_videoCodecLabel, 2, 0, Qt::AlignRight);
    layout->addWidget(m_videoCodecComboBox, 2, 1);
    layout->addWidget(m_videoBitRateLabel, 2, 2, Qt::AlignRight);
    layout->addWidget(m_videoBitRateComboBox, 2, 3);
    layout->addWidget(m_encodeVideoCheckBox, 2, 4);
    layout->addWidget(m_deinterlaceVideoCheckBox, 2, 5);
    layout->addWidget(m_videoStdLabel, 3, 4);
    layout->addWidget(m_videoStdComboBox, 3, 5);

    m_videoGroupBox->setLayout(layout);
}

void ConfigWindow::createSoundGroupBox(Config& cfg)
{
    m_soundGroupBox = new QGroupBox(tr("Sound"));
    QGridLayout *layout = new QGridLayout;

    m_browseSoundButton = createButton(tr("Browse..."), SLOT(browseSound()));

    m_soundFileLineEdit = new QLineEdit;
    m_soundFileLineEdit->setText(cfg.soundFile);
    m_soundFileLabel = new QLabel(tr("Sound file:"));
    m_soundFileLabel->setBuddy(m_soundFileLineEdit);

    m_soundCodecComboBox = new QComboBox;
#ifdef Platform_dm365
    m_soundCodecComboBox->addItem(tr("AAC"), "aac");
#endif
    m_soundCodecComboBox->addItem(tr("G711"), "g711");

    m_soundCodecLabel = new QLabel(tr("Codec:"));
    m_soundCodecLabel->setBuddy(m_soundCodecComboBox);

    m_soundBitRateComboBox = new QComboBox;
    m_soundBitRateComboBox->addItem(tr("96 kbps"), 96000);
    m_soundBitRateComboBox->addItem(tr("128 kbps"), 128000);
    m_soundBitRateComboBox->addItem(tr("160 kbps"), 160000);
    m_soundBitRateComboBox->setToolTip("Note: Increasing bit rate may reduce" 
        " performance.");

    m_soundBitRateLabel = new QLabel(tr("Audio bit rate:"));
    m_soundBitRateLabel->setBuddy(m_soundBitRateComboBox);

    m_samplingRateComboBox = new QComboBox;
    m_samplingRateComboBox->addItem(tr("16 kHz"), 16000);
    m_samplingRateComboBox->addItem(tr("44.1 kHz"), 44100);
    m_samplingRateComboBox->addItem(tr("48 kHz"), 48000);
    m_samplingRateComboBox->setToolTip("Note: Increasing sample rate may " 
        "reduce performance.");

    m_samplingRateLabel = new QLabel(tr("Audio sample rate:"));
    m_samplingRateLabel->setBuddy(m_samplingRateComboBox);

    m_encodeSoundCheckBox = new QCheckBox(tr("Disable sound"));

    connect(m_encodeSoundCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setEncodeSound(bool)));
    connect(m_soundCodecComboBox, SIGNAL(activated(int)),
            this, SLOT(soundCodecChanged()));
    connect(m_soundBitRateComboBox, SIGNAL(activated(int)),
            this, SLOT(soundBitRateChanged()));
    connect(m_samplingRateComboBox, SIGNAL(activated(int)),
            this, SLOT(samplingRateChanged()));

    layout->addWidget(m_soundFileLabel, 1, 0, Qt::AlignLeft);
    layout->addWidget(m_soundFileLineEdit, 1, 1, 1, 5);
    layout->addWidget(m_browseSoundButton, 1, 6);
    layout->addWidget(m_soundCodecLabel, 2, 0, Qt::AlignRight);
    layout->addWidget(m_soundCodecComboBox, 2, 1);
    layout->addWidget(m_encodeSoundCheckBox, 2, 4);
    layout->addWidget(m_soundBitRateLabel, 3, 2, Qt::AlignRight);
    layout->addWidget(m_soundBitRateComboBox, 3, 3);
    layout->addWidget(m_samplingRateLabel, 3, 4, Qt::AlignRight);
    layout->addWidget(m_samplingRateComboBox, 3, 5);

    m_soundGroupBox->setLayout(layout);
}

void ConfigWindow::createOtherGroupBox()
{
    m_otherGroupBox = new QGroupBox(tr("Other Options"));
    QHBoxLayout *layout = new QHBoxLayout;

    m_loopingCheckBox = new QCheckBox(tr("Repeat"));
    m_disablePreviewCheckBox = new QCheckBox(tr("Disable Preview"));
    m_disableFileWriteCheckBox = new QCheckBox(tr("Do not save encoded data"));
    m_passthroughCheckBox = new QCheckBox(
        tr("Passthrough (run demos without codecs)"));

    m_disablePreviewCheckBox->setToolTip("Disabling preview helps improve "
        "performance.");
    m_disableFileWriteCheckBox->setToolTip("Disabling file i/o helps improve "
        "performance.");

    connect(m_loopingCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setLooping(bool)));
    connect(m_disablePreviewCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setDisablePreview(bool)));
    connect(m_disableFileWriteCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setDisableFileWrite(bool)));
    connect(m_passthroughCheckBox, SIGNAL(toggled(bool)),
            this, SLOT(setPassthrough(bool)));

    layout->addWidget(m_loopingCheckBox);
    layout->addWidget(m_disablePreviewCheckBox);
    layout->addWidget(m_disableFileWriteCheckBox);
    layout->addWidget(m_passthroughCheckBox);

    m_otherGroupBox->setLayout(layout);
}

QPushButton * ConfigWindow::createButton(const QString &text, 
    const char *member)
{
    /* Create a push button */
    QPushButton * button = new QPushButton(text);
    connect(button, SIGNAL(clicked()), this, member);
    return button;
}

void ConfigWindow::browseVideo()
{
    QString selectedFilter = "Videos (*.264 *.m2v *.mpeg4 *.m4v *.mpeg2)";
    QString selectedFile;

    /* Use a file dialog to get file name */
    if (m_demo == "Encode") {
        selectedFile = QFileDialog::getSaveFileName(this, tr("Video File"),
            tr("/usr/share/ti/data/videos"), 
            tr("Videos (*.264 *.mpeg2 *.m2v *.mpeg4 *.m4v)"),
            &selectedFilter);
    }
    else {
        selectedFile = QFileDialog::getOpenFileName(this, tr("Video File"),
            tr("/usr/share/ti/data/videos"), 
            tr("Videos (*.264 *.mpeg2 *.m2v *.mpeg4 *.m4v)"),
            &selectedFilter);
    }
    
    /* 
     * If user cancels, ignore selectedFile. Otherwise record it.
     */
    if (!selectedFile.isEmpty()) {
        m_videoFile = selectedFile;
        m_videoFileLineEdit->setText(m_videoFile);
    }
}

void ConfigWindow::disableUnusedWidgets(Config& cfg)
{
    if (cfg.demo == "Decode") {
        m_videoCodecLabel->hide();
        m_videoBitRateLabel->hide();
        m_soundCodecLabel->hide();
        m_soundBitRateLabel->hide();
        m_samplingRateLabel->hide();
        m_videoCodecComboBox->hide();
        m_videoBitRateComboBox->hide();
        m_soundCodecComboBox->hide();
        m_soundBitRateComboBox->hide();
        m_samplingRateComboBox->hide();
        m_passthroughCheckBox->hide();
        m_encodeVideoCheckBox->hide();
        m_encodeSoundCheckBox->hide();
        m_deinterlaceVideoCheckBox->hide();
        m_disablePreviewCheckBox->hide();
        m_disableFileWriteCheckBox->hide();

        /* For component output, we want to give user option to select res */
        if (cfg.displayOutput.toInt() != COMPONENT_OUTPUT) {
            m_videoStdComboBox->hide();
            m_videoStdLabel->hide();
        }
    }
    else if (cfg.demo == "Encode") {
        m_loopingCheckBox->hide();
        m_passthroughCheckBox->hide();

#ifdef Platform_omap3530
        m_otherGroupBox->hide();
        m_soundBitRateComboBox->hide();
        m_soundBitRateLabel->hide();
        m_samplingRateComboBox->hide();
        m_samplingRateLabel->hide();
#else // Platform_dm365
        m_deinterlaceVideoCheckBox->hide();
#endif

        /* 
         * Since we currently do not have official keyboard support, we disable
         * the browse buttons and rely on command line to provide filenames.
         * Comment out these lines to enable filename selection for Encode demo.
         */
        m_browseVideoButton->hide();
        m_browseSoundButton->hide();
        m_videoFileLineEdit->setEnabled(false);
        m_soundFileLineEdit->setEnabled(false); 

        if (m_speechSelected) {
            m_soundBitRateComboBox->setVisible(false);
            m_soundBitRateComboBox->setVisible(false);
            m_samplingRateComboBox->setVisible(false);
            m_samplingRateComboBox->setVisible(false);
        }

        /* 
         * Display the video standard selector only in the special case when
         * using the camera in the encode demo while displaying on component.
         */
        if ((cfg.videoInput.toInt() != CAMERA_INPUT) || 
            (cfg.displayOutput.toInt() != COMPONENT_OUTPUT)) {
            m_videoStdComboBox->hide();
            m_videoStdLabel->hide();
        }
    }
    else if (cfg.demo == "Encodedecode") {
        m_videoFileLabel->hide();
        m_videoStdLabel->hide();
        m_soundFileLabel->hide();
        m_soundCodecLabel->hide();
        m_soundBitRateLabel->hide();
        m_samplingRateLabel->hide();
        m_videoFileLineEdit->hide();
        m_soundFileLineEdit->hide();
        m_soundCodecComboBox->hide();
        m_soundBitRateComboBox->hide();
        m_samplingRateComboBox->hide();
        m_videoStdComboBox->hide();
        m_loopingCheckBox->hide();
        m_browseVideoButton->hide();
        m_browseSoundButton->hide();
        m_soundGroupBox->hide();
        m_encodeVideoCheckBox->hide();
        m_encodeSoundCheckBox->hide();
        m_deinterlaceVideoCheckBox->hide();
        m_disablePreviewCheckBox->hide();
        m_disableFileWriteCheckBox->hide();
    }

    /* Disable unneeded widgets based on configuration from command line */
    if (!cfg.videoBitRate.isEmpty()) {
        m_videoBitRateLabel->hide();
        m_videoBitRateComboBox->hide();
    }
    if (!cfg.soundBitRate.isEmpty()) {
        m_soundBitRateLabel->hide();
        m_soundBitRateComboBox->hide();
    }
    if (!cfg.samplingRate.isEmpty()) {
        m_samplingRateLabel->hide();
        m_samplingRateComboBox->hide();
    }
    if (!cfg.videoCodec.isEmpty()) {
        m_videoCodecLabel->hide();
        m_videoCodecComboBox->hide();
    }
    if (!cfg.videoFile.isEmpty()) {
        m_videoCodecLabel->hide();
        m_videoCodecComboBox->hide();
        m_encodeVideoCheckBox->hide();
    }
    if (!cfg.soundFile.isEmpty()) {
        m_soundCodecLabel->hide();
        m_soundCodecComboBox->hide();
        m_encodeSoundCheckBox->hide();
    }
    if (cfg.passthrough == true) {
        m_otherGroupBox->hide();
        m_passthroughCheckBox->hide();
    }
    if (cfg.looping == true) {
        m_otherGroupBox->hide();
        m_loopingCheckBox->hide();
    }
    if (cfg.disablePreview == true) {
        m_disablePreviewCheckBox->hide();
    }
    if (cfg.disableFileWrite == true) {
        m_disableFileWriteCheckBox->hide();
        if (cfg.disablePreview == true) {
            m_otherGroupBox->hide();
        }
    }
}

void ConfigWindow::browseSound()
{
    QString selectedFilter = "Audio (*.aac)";
    QString selectedFile;

    /* Use a file dialog to get file name */
    if (m_demo == "Encode") {
        selectedFile = QFileDialog::getSaveFileName(this, tr("Sound File"),
            tr("/usr/share/ti/data/sounds"), 
            tr("Audio (*.aac);;Speech (*.g711)"),
            &selectedFilter);
    }
    else {
        selectedFile = QFileDialog::getOpenFileName(this, tr("Sound File"),
            tr("/usr/share/ti/data/sounds"), 
            tr("Audio (*.aac);;Speech (*.g711)"),
            &selectedFilter);
    }

    /* 
     * If user cancels, ignore selectedFile. Otherwise record it.
     */
    if (!selectedFile.isEmpty()) {
        m_soundFile = selectedFile;
        m_soundFileLineEdit->setText(m_soundFile);
    }
}


QString ConfigWindow::getVideoExtension()
{
    QString extension = "";

    switch (m_videoCodecComboBox->currentIndex()) {
        case H264:
            extension = ".264"; 
            break;
        case MPEG4:
            extension = ".mpeg4";
            break;
        case MPEG2:
            extension = ".m2v";
            break;
        default:
            qCritical("Bad value in video codec combo box\n");
    }

    return extension;
}

QString ConfigWindow::getSoundExtension()
{
    QString extension = "";

    switch (m_soundCodecComboBox->currentIndex()) {
#ifdef Platform_dm365
        case AAC:
            extension = ".aac";
            m_speechSelected = false;
            break;
#endif
        case G711:
            extension = ".g711";
            m_speechSelected = true;
            break;
        default:
            qCritical("Bad value in sound codec combo box\n");
            break;
    }

    return extension;
}

void ConfigWindow::startDemo()
{
    /* Send config to demo process */

    if (!m_videoFileLineEdit->isHidden()) {
        if (m_encodeVideoCheckBox->isHidden() || 
            !m_encodeVideoCheckBox->isChecked()) {
            m_msgServer->sendConfig('v', m_videoFileLineEdit->text());
        }
    }

    if (!m_soundFileLineEdit->isHidden()) {
        if (m_encodeSoundCheckBox->isHidden() || 
            !m_encodeSoundCheckBox->isChecked()) {        
            if (m_soundFileLineEdit->text().endsWith(".g711")) {
                m_msgServer->sendConfig('s', m_soundFileLineEdit->text());
            }
            else {
                m_msgServer->sendConfig('a', m_soundFileLineEdit->text());
            }
        }
    }

    if (!m_videoBitRateComboBox->isHidden()) {
          m_msgServer->sendConfig('b', m_videoBitRateComboBox->itemData(
              m_videoBitRateComboBox->currentIndex()).toString());      
    }
    if (!m_videoCodecComboBox->isHidden()) {
          if (m_demo == "Encodedecode") {      
              m_msgServer->sendConfig('v', m_videoCodecComboBox->itemData(
                  m_videoCodecComboBox->currentIndex()).toString()); 
          }
    }
    if (!m_videoStdComboBox->isHidden()) {   
        m_msgServer->sendConfig('y', m_videoStdComboBox->itemData(
            m_videoStdComboBox->currentIndex()).toString()); 
    }
    if (!m_soundBitRateComboBox->isHidden()) {
          m_msgServer->sendConfig('p', m_soundBitRateComboBox->itemData(
              m_soundBitRateComboBox->currentIndex()).toString());     
    }
    if (!m_samplingRateComboBox->isHidden()) {
          m_msgServer->sendConfig('u', m_samplingRateComboBox->itemData(
              m_samplingRateComboBox->currentIndex()).toString());     
    }
    if (!m_loopingCheckBox->isHidden()) {
        if (m_loopingCheckBox->isChecked()) {
            m_msgServer->sendConfig('l', "");
        }
    }
    if (!m_disablePreviewCheckBox->isHidden()) {
        if (m_disablePreviewCheckBox->isChecked()) {
            m_msgServer->sendConfig('w', "");
        }
    }
    if (!m_disableFileWriteCheckBox->isHidden()) {
        if (m_disableFileWriteCheckBox->isChecked()) {
            m_msgServer->sendConfig('f', "");
        }
    }
    if (!m_passthroughCheckBox->isHidden()) {
        if (m_passthroughCheckBox->isChecked()) {
            m_msgServer->sendConfig('p', "");
        }
    }
    if (!m_deinterlaceVideoCheckBox->isHidden()) {
        if (m_deinterlaceVideoCheckBox->isChecked()) {
            m_msgServer->sendConfig('d', "");
        }
    }

    /* Send ETB to mark end of configuration transmission */
    m_msgServer->sendConfig('\27', "");
    
    /* Close configuration window */
    hide();
    
    /* launch UI */
    m_ctrlWindow->showFullScreen();
}

void ConfigWindow::exit()
{
    QString empty = "";

    /* Stop the demo process */
    m_msgServer->sendConfig('\33', empty);
    
    /* Exit the user interface */
    QApplication::exit();
}

void ConfigWindow::videoBitRateChanged()
{
    m_videoBitRate = m_videoBitRateComboBox->itemData(
        m_videoBitRateComboBox->currentIndex(), Qt::UserRole).toString();
}

void ConfigWindow::videoCodecChanged()
{
    QString extension;

    m_videoCodec = m_videoCodecComboBox->itemData(
        m_videoCodecComboBox->currentIndex(), Qt::UserRole).toString();
    if (m_demo == "Encode") {
        /* adjust file extension to match codec selection */
        if (!m_videoFile.endsWith(getVideoExtension())) {
            QStringList list = m_videoFile.split(".");
            if (list.count() > 1) {
                m_videoFile = "";
                for (int i = 0; i < list.count() - 1; i++) {
                    m_videoFile += list[i] + ".";
                }
            }
            extension = getVideoExtension();
            m_videoFile += extension.remove('.');
            m_videoFileLineEdit->setText(m_videoFile);
        }
    }
}

void ConfigWindow::videoStdChanged()
{
    m_videoStd = m_videoStdComboBox->itemData(
        m_videoStdComboBox->currentIndex(), Qt::UserRole).toString();
}

void ConfigWindow::soundCodecChanged()
{
    QString extension;

    m_soundCodec = m_soundCodecComboBox->itemData(
        m_soundCodecComboBox->currentIndex(), Qt::UserRole).toString();
    if (m_demo == "Encode") {
        /* adjust file extension to match codec selection */
        if (!m_soundFile.endsWith(getSoundExtension())) {
            QStringList list = m_soundFile.split(".");
            if (list.count() > 1) {
                m_soundFile = "";
                for (int i = 0; i < list.count() - 1; i++) {
                    m_soundFile += list[i] + ".";
                }
            }
            extension = getSoundExtension();
            m_soundFile += extension.remove('.');
            m_soundFileLineEdit->setText(m_soundFile);

            /* disable irrelevant combo boxes when speech codec selected */
            if (m_speechSelected) {
                m_soundBitRateComboBox->setVisible(false);
                m_soundBitRateLabel->setVisible(false);
                m_samplingRateComboBox->setVisible(false);
                m_samplingRateLabel->setVisible(false);
            }
            else {
                m_soundBitRateComboBox->setVisible(true);
                m_soundBitRateLabel->setVisible(true);
                m_samplingRateComboBox->setVisible(true);
                m_samplingRateLabel->setVisible(true);
            }
        }
    }
}

void ConfigWindow::soundBitRateChanged()
{
    m_soundBitRate = m_soundBitRateComboBox->itemData(
        m_soundBitRateComboBox->currentIndex(), Qt::UserRole).toString();
}

void ConfigWindow::samplingRateChanged()
{
    m_samplingRate = m_samplingRateComboBox->itemData(
        m_samplingRateComboBox->currentIndex(), Qt::UserRole).toString();
}

void ConfigWindow::setLooping(bool looping)
{
    m_looping = looping;
}

void ConfigWindow::setDisablePreview(bool disablePreview)
{
    m_disablePreview = disablePreview;
}

void ConfigWindow::setDisableFileWrite(bool disableFileWrite)
{
    m_disableFileWrite = disableFileWrite;
}

void ConfigWindow::setPassthrough(bool passthrough)
{
    m_passthrough = passthrough;
    if (passthrough) {
        m_videoCodecComboBox->setEnabled(false);
        m_videoBitRateComboBox->setEnabled(false);
    }
    else {
       m_videoCodecComboBox->setEnabled(true);
       m_videoBitRateComboBox->setEnabled(true);
    }
}

void ConfigWindow::setDeinterlaceVideo(bool deinterlace)
{
    m_deinterlaceVideo = deinterlace;
}

void ConfigWindow::setEncodeVideo(bool doNotEncode)
{
    m_encodeVideo = !doNotEncode;

    // Disable video options when disabling video encode
    if (doNotEncode) {
        m_videoCodecComboBox->setEnabled(false);
        m_videoBitRateComboBox->setEnabled(false);
        m_videoStdComboBox->setEnabled(false);
    }
    else {
        m_videoCodecComboBox->setEnabled(true);
        m_videoBitRateComboBox->setEnabled(true);
        m_videoStdComboBox->setEnabled(true);
    }
}

void ConfigWindow::setEncodeSound(bool doNotEncode)
{
    m_encodeSound = !doNotEncode;

    // Disable sound options when disabling sound encode
    if (doNotEncode) {
        m_soundCodecComboBox->setEnabled(false);
        m_soundBitRateComboBox->setEnabled(false);
        m_samplingRateComboBox->setEnabled(false);
    }
    else {
        m_soundCodecComboBox->setEnabled(true);
        m_soundBitRateComboBox->setEnabled(true);
        m_samplingRateComboBox->setEnabled(true);
    }
}

ConfigWindow::~ConfigWindow()
{
}

