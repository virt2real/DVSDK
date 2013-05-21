/*
 * controlwindow.cpp
 *
 * This module handles the definitions and declarations for 
 * the control window in the user interface.
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

#include <QMouseEvent>

#include "qtinterface.h"
#include "controlwindow.h"

/* Maximum number of info items that can be displayed at once */
#define MAXITEMS 12

/* Status box characteristics */
#define STATUS_X       (QApplication::desktop()->width() / 4) 
#define STATUS_Y       (QApplication::desktop()->height() / 8)
#define STATUS_WIDTH   (QApplication::desktop()->width() / 2)
#define STATUS_HEIGHT  (QApplication::desktop()->height() / 3)
#define STATUS_MARGIN  (STATUS_HEIGHT / 8)

ControlWindow::ControlWindow(MessageServer * msgServer, OSDManager * osd)
{   
    QSize iconSize(30, 30);

    m_msgServer = msgServer;
    m_osd = osd;

    m_paused = false;
    m_hidden = false;

    m_playButton = new QToolButton;
    m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    m_playButton->setIconSize(iconSize);
    m_playButton->setToolTip(tr("Play/Pause"));
    connect(m_playButton, SIGNAL(clicked(bool)), this, SLOT(togglePause()));

    m_stopButton = new QToolButton;
    m_stopButton->setIcon(style()->standardIcon(QStyle::SP_MediaStop));
    m_stopButton->setIconSize(iconSize);
    m_stopButton->setToolTip(tr("Stop"));
    connect(m_stopButton, SIGNAL(clicked(bool)), this, SLOT(stop()));

    m_incButton = new QToolButton;
    m_incButton->setIcon(style()->standardIcon(QStyle::SP_ArrowUp));
    m_incButton->setIconSize(iconSize);
    m_incButton->setToolTip(tr("Increase visibility"));
    connect(m_incButton, SIGNAL(clicked(bool)), this, SLOT(incTrans()));

    m_decButton = new QToolButton;
    m_decButton->setIcon(style()->standardIcon(QStyle::SP_ArrowDown));
    m_decButton->setIconSize(iconSize);
    m_decButton->setToolTip(tr("Decrease visibility"));
    connect(m_decButton, SIGNAL(clicked(bool)), this, SLOT(decTrans()));

    m_hideButton = new QToolButton;
    m_hideButton->setIcon(style()->standardIcon(QStyle::SP_DialogCloseButton));
    m_hideButton->setIconSize(iconSize);
    m_hideButton->setToolTip(tr("Hide OSD"));
    connect(m_hideButton, SIGNAL(clicked(bool)), this, SLOT(hideOSD()));
    
    connect(m_msgServer, SIGNAL(statusMsg(int, QString, QString)), this, 
        SLOT(statusMessage(int, QString, QString)));
    
    /* Wire the signals from msgServer to corresponding slots */
    connect(m_msgServer, SIGNAL(playMsg()), this, SLOT(playFromKb()));
    connect(m_msgServer, SIGNAL(pauseMsg()), this, SLOT(pauseFromKb()));
    connect(m_msgServer, SIGNAL(stopMsg()), this, SLOT(stopFromKb()));
    connect(m_msgServer, SIGNAL(incMsg()), this, SLOT(incTrans()));
    connect(m_msgServer, SIGNAL(decMsg()), this, SLOT(decTrans()));
    connect(m_msgServer, SIGNAL(hideMsg()), this, SLOT(toggleVisibility()));

    createInfoGroupBox();
    
    QBoxLayout * buttonsLayout = new QHBoxLayout;
    buttonsLayout->addStretch();
    buttonsLayout->addWidget(m_playButton);
    buttonsLayout->addWidget(m_stopButton);
    buttonsLayout->addWidget(m_incButton);
    buttonsLayout->addWidget(m_decButton);
    buttonsLayout->addWidget(m_hideButton);
    buttonsLayout->addStretch();

#ifdef Platform_omap3530
    this->setGeometry(QRect(STATUS_X, STATUS_Y, STATUS_WIDTH, STATUS_HEIGHT));

    QPalette p = this->palette();
    p.setColor(QPalette::Window, QColor(255,255,255,255));
    this->setPalette(p);

    Qt::WindowFlags flags = Qt::Dialog;
    flags |= Qt::CustomizeWindowHint;
    flags |= Qt::WindowTitleHint;
    this->setWindowFlags(flags);
    this->setWindowTitle("Texas Instruments");
#endif

    QBoxLayout * layout = new QVBoxLayout;
    layout->addWidget(m_infoGroupBox);
    layout->addLayout(buttonsLayout);    
#ifdef Platform_dm365
    layout->setContentsMargins(STATUS_X, STATUS_Y, STATUS_X, 
        QApplication::desktop()->height() - STATUS_Y - STATUS_HEIGHT);
#endif

    setLayout(layout);
}

void ControlWindow::createInfoGroupBox()
{
    m_infoGroupBox = new QGroupBox(tr("Info"));

    QFont labelFont("Times", 9);
    m_info = new QLabel[MAXITEMS];
    
    for (int i = 0; i < MAXITEMS; i++) {
        m_info[i].setFont(labelFont);
    }

    QBoxLayout * infoLayout1 = new QVBoxLayout;
    for (int i = 0; i < MAXITEMS/2; i++) {
        infoLayout1->addWidget(&m_info[i]);
    }    

    QBoxLayout * infoLayout2 = new QVBoxLayout;
    for (int i = MAXITEMS/2; i < MAXITEMS; i++) {
        infoLayout2->addWidget(&m_info[i]);
    }   
        
    QBoxLayout * fullLayout = new QHBoxLayout;
    fullLayout->addLayout(infoLayout1);
    fullLayout->addLayout(infoLayout2);

    m_infoGroupBox->setLayout(fullLayout);
}

void ControlWindow::showFullScreen()
{
    // Setup OSD as a little box
#ifdef Platform_dm365
    m_osd->setBoxDimensions(STATUS_X - STATUS_MARGIN, STATUS_Y - STATUS_MARGIN, 
        STATUS_WIDTH + 2 * STATUS_MARGIN, STATUS_HEIGHT + 2 * STATUS_MARGIN);
#endif
    m_osd->showTransOSD();

    QCursor::setPos(STATUS_X, STATUS_Y);
    setMouseTracking(true);
#ifdef Platform_dm365
    QWidget::showFullScreen();
#else // Platform_omap3530
    QWidget::show();
#endif
}

void ControlWindow::mouseMoveEvent(QMouseEvent * e)
{
#ifdef Platform_dm365
    int x = e->pos().x();
    int y = e->pos().y();

    /* 
     * Keep mouse cursor within box boundaries
     */
    if (e->pos().x() < (STATUS_X - STATUS_MARGIN)) {
        x = STATUS_X - STATUS_MARGIN;
    }
    else if (e->pos().x() > (STATUS_X + STATUS_WIDTH + STATUS_MARGIN)) {
        x = STATUS_X + STATUS_WIDTH + STATUS_MARGIN;
    }
    
    if (e->pos().y() < (STATUS_Y - STATUS_MARGIN)) {
        y = STATUS_Y - STATUS_MARGIN;
    }
    else if (e->pos().y() > (STATUS_Y + STATUS_HEIGHT + STATUS_MARGIN)) {
        y = STATUS_Y + STATUS_HEIGHT + STATUS_MARGIN;
    }

    if ((x != e->pos().x()) || (y != e->pos().y())) {
        QCursor::setPos(x, y);
    }
#endif

    QWidget::mouseMoveEvent(e);
}

void ControlWindow::hideOSD()
{
    m_hidden = true;
    m_osd->hideOSD();

#ifdef Platform_omap3530
    this->setGeometry(QRect(0, 0, QApplication::desktop()->width(),
                            QApplication::desktop()->height()));
#endif

    // Hide all widgets so that they do not respond to events when OSD is off
    m_infoGroupBox->hide();
    m_playButton->hide();
    m_stopButton->hide();
    m_incButton->hide();
    m_decButton->hide();
    m_hideButton->hide();
}

void ControlWindow::toggleVisibility()
{
    if (m_hidden) {
        m_hidden = false;
        m_osd->showTransOSD();
    }
    else {
        m_hidden = true;
        m_osd->hideOSD();
    }
}

void ControlWindow::incTrans()
{
    m_osd->incTrans();
}

void ControlWindow::decTrans()
{
    m_osd->decTrans();
}

void ControlWindow::togglePause()
{
    /* Send pause command to demo and toggle button image */
    if (m_paused) {
        m_paused = false;
        m_msgServer->sendCmd(QtInterface_Play);
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
    else {
        m_paused = true;
        m_msgServer->sendCmd(QtInterface_Pause);
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));
    }    
}

void ControlWindow::stop()
{
    /* Send stop command to demo */
    m_msgServer->sendCmd(QtInterface_Stop);
}

void ControlWindow::stopFromKb()
{
    /* 
     * Stop received from keyboard. Note that final stop signal from demo is 
     * also treated as if it is a keyboard triggered.
     */
    close();
}

void ControlWindow::playFromKb()
{
    /* Play received from keyboard. Update GUI if necessary */
    if (m_paused) {
        // Go into play state
        m_paused = false;    
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPause));
    }
}

void ControlWindow::pauseFromKb()
{
    /* Pause received from keyboard. Update GUI if necessary */
    if (!m_paused) {
        // Go into paused state
        m_paused = true;    
        m_playButton->setIcon(style()->standardIcon(QStyle::SP_MediaPlay));   
    }
}

ControlWindow::~ControlWindow()
{
    /* Terminate message server thread and wait for completion */
    m_msgServer->quit();
    m_msgServer->wait(ULONG_MAX);
}

void ControlWindow::statusMessage(int position, QString label, QString value)
{   
    QString textToDisplay;
     
    /* Update info on OSD */
    textToDisplay = label + ' ' + value;
    m_info[position - 1].setText(textToDisplay);
}

void ControlWindow::mousePressEvent(QMouseEvent *e)
{
    e->accept();

    // Show all widgets when OSD is turned back on
    if (m_hidden) {
#ifdef Platform_omap3530
        this->setGeometry(QRect(STATUS_X, STATUS_Y,
                                STATUS_WIDTH, STATUS_HEIGHT));
#endif

        m_infoGroupBox->show();
        m_playButton->show();
        m_stopButton->show();
        m_incButton->show();
        m_decButton->show();
        m_hideButton->show();

        m_hidden = false;
        m_osd->showTransOSD();
    }
}


