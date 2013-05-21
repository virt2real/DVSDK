/*
 * {module name} ButtonLaunch
 *
 * {module description} Application launch objects for button activation
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

#ifndef BUTTONLAUNCH_H
#define BUTTONLAUNCH_H
 
#include <QtGui>
#include "matrixcontrol.h"

class QProcess;
class MenuPage;

class ButtonLaunch : public QWidget
{
    Q_OBJECT

public:
    ButtonLaunch(MenuPage * const pParentWindow, QMdiArea * const pMdiArea, const QString &appName, const QString &appParameter, bool appTextFlag,
                 bool terminateMatrix, const QString &appDescription, MatrixControl * mControl);

public slots:
    void Launch();
    void TextOutput();
    void ErrorHandler();
    void ReadOutput();
    void Finished();
    void Close();
    void SaveLaunch();
    void turnOffDesc(); 

private:
    QString         m_appName;
    QString         m_appParameter;
    QString         m_pAppDescription;
    QMdiArea *      m_pMdiArea;
    QProcess *      m_pProcess;
    QTextEdit *     m_pTextWindow;
    QPushButton *   m_pCloseButton;
    QMdiSubWindow * m_pSubWindow;
    MenuPage *      m_pParentWindow;
    bool            m_appTextFlag;
    bool            m_terminateMatrix;
    MatrixControl * m_pMControl;
    bool            m_showTestMenu;
};
 
#endif // BUTTONLAUNCH_H
