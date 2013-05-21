/*
 * controlwindow.h
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
#ifndef _CONTROLWINDOW_H
#define _CONTROLWINDOW_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QToolButton>
#include <QFileDialog>
#include <QStyle>
#include <QTimer>

#include "messageserver.h"
#include "osdmanager.h"

class ControlWindow : public QWidget
{
    Q_OBJECT

public slots:
    void showFullScreen();

public:
    ControlWindow(MessageServer * msgServer, OSDManager * osd);    
    ~ControlWindow();

private slots: 
    void togglePause();
    void statusMessage(int position, QString label, QString value);
    void hideOSD();
    void toggleVisibility();
    void incTrans();
    void decTrans();
    void stop();
    void stopFromKb();
    void playFromKb();
    void pauseFromKb();

private:
    void createInfoGroupBox();

    QLabel * m_info;
    QGroupBox * m_infoGroupBox;
    QToolButton * m_stopButton;
    QToolButton * m_playButton;
    QToolButton * m_hideButton;
    QToolButton * m_incButton;
    QToolButton * m_decButton;
    OSDManager * m_osd;
    MessageServer * m_msgServer;
    bool m_paused;
    bool m_hidden;

protected:
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void mouseMoveEvent(QMouseEvent * event);
};

#endif
