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

#include "buttonlaunch.h"
#include "customstyle.h"
#include "menupage.h"
#include "matrixcontrol.h"

// Create an object to store the name of the app associated with this button.

ButtonLaunch::ButtonLaunch(MenuPage * const pParentWindow, QMdiArea * const pMdiArea, const QString &appName, const QString &appParameter, bool appTextFlag,
                           bool terminateMatrix, const QString &appDescription, MatrixControl * mControl)
{
    m_appName = appName;
    m_appParameter = appParameter;
    m_pMdiArea = pMdiArea;
    m_pParentWindow = pParentWindow;
    m_appTextFlag = appTextFlag;
    m_terminateMatrix = terminateMatrix;
    m_pAppDescription = appDescription;
    m_pMControl = mControl;
    m_showTestMenu = true;
}

// Process launch events for this connected button.

void ButtonLaunch::Launch()
{
    // If Description mode is on, Save the application launch, launch a description if one is 
    // available, otherwise run the application as normal
    if(m_pMControl->getDescMode() == "On" && m_pAppDescription != "" && m_showTestMenu )
    {
        SaveLaunch();
        MenuPage * pMenuPage = new MenuPage(m_pMdiArea, m_pAppDescription, false , m_pParentWindow, m_pMControl);
        pMenuPage->Launch();
    }
    else
    {
        m_showTestMenu = true;

       // Create a process to run the app.
       m_pProcess = new QProcess(this);
       m_pProcess->setProcessChannelMode(QProcess::MergedChannels);
       // Disable parent menu while this process is running to prevent false button triggering.
       m_pParentWindow->Disable();

       connect(m_pProcess, SIGNAL(error(QProcess::ProcessError)), this, SLOT(ErrorHandler()));
       if (m_appTextFlag)
       {
           // Hook signals for apps that generate stdout text.
           connect(m_pProcess, SIGNAL(readyRead()), this, SLOT(TextOutput()));
       }
       else    // For apps that do not need a window to display stdout text.
       {
           connect(m_pProcess, SIGNAL(finished(int, QProcess::ExitStatus)), m_pParentWindow, SLOT(Enable()));
       }
       // Launch the app by its stored name.
       QStringList appParameters;
       appParameters << m_appParameter;

       if (!m_terminateMatrix) {
           m_pProcess->start(m_appName, appParameters, QIODevice::ReadOnly | 
               QIODevice::Text);
       }
       else {
           // If we need to terminate the matrix we must start the application as 
           // a detached process.
           m_pProcess->startDetached(m_appName, appParameters);
       } 
    }
    //qDebug() << "Launched App: " << m_appName << " " << m_appParameter;
}

// Create a window to display text output from the process.

void ButtonLaunch::ErrorHandler()
{
       m_pParentWindow->Enable();
       //qDebug() << "Error encountered";
}
void ButtonLaunch::TextOutput()
{
    // Prevent this from being called twice.
    disconnect(m_pProcess, SIGNAL(readyRead()), this, SLOT(TextOutput()));

    // Create a subwindow to display stdout text from the app.
    m_pTextWindow = new QTextEdit(this);
    m_pTextWindow->setStyleSheet("QScrollBar{min-width: 30; min-height: 30}");
    m_pTextWindow->setFontPointSize(16);

    // Display the text window the same size as the main menu.

    m_pSubWindow = m_pMdiArea->addSubWindow(m_pTextWindow);
    m_pSubWindow->resize(m_pMdiArea->size());
    m_pSubWindow->setWindowFlags(Qt::FramelessWindowHint);
    m_pSubWindow->show();
    m_pSubWindow->setFocus();

    // Hook signals to handle additional text output and process closing.
    connect(m_pProcess, SIGNAL(readyRead()), this, SLOT(ReadOutput()));
    connect(m_pProcess, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(Finished()));

    //qDebug() << "TextOutput";
    ReadOutput();
}

// Append text from the process to the display window.

void ButtonLaunch::ReadOutput()
{
    // Capture and display stdout text from the app.

    QString string;

    do {
        string = m_pProcess->readLine(200);
        m_pTextWindow->append(string.trimmed());
    } while (!string.isEmpty());

    //qDebug() << "ReadOutput";
}

// Close the display window when the process is finished.

void ButtonLaunch::Finished()
{
    ReadOutput();

    // Calculate the position for the Close button in the bottom right corner.
    const QPoint position(m_pTextWindow->size().width() - 140, m_pTextWindow->size().height() - 80);

    // Create the close button with a text label.
    m_pCloseButton = new QPushButton("&Close", m_pTextWindow);
    m_pCloseButton->setMinimumSize(QSize(64, 64));
    m_pCloseButton->move(position);
    m_pCloseButton->show();

    // Connect button events to close this object.
    connect(m_pCloseButton, SIGNAL(clicked(bool)), this, SLOT(Close()));

    //qDebug() << "Finished";
}

// Close the process.

void ButtonLaunch::Close()
{
    // Force parent menu to be visible.
    m_pParentWindow->Enable();

    // Close the app's text subwindow and process.
    m_pTextWindow->close();
    m_pProcess->close();
    m_pSubWindow->close();

    //qDebug() << "Process Ended: " << m_appName;
}
void ButtonLaunch::SaveLaunch()
{
     // Save the app launch, until you exit the test description
      m_pParentWindow->SavePlaunch(this);
}
void ButtonLaunch::turnOffDesc()
{
    m_showTestMenu = false;
}
