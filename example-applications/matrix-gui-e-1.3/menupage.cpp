/*
 * {module name} MenuPage
 *
 * {module description} Launch a menu page view
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

#include "menupage.h"
#include "buttonfactory.h"
#include "buttonlaunch.h"

// Create an object to store the name of the app associated with this button.

MenuPage::MenuPage(QMdiArea * const pMdiArea, const QString &appParameter, bool TopFlag, MenuPage * ParentWindow, MatrixControl * mControl)
{
    m_pMdiArea = pMdiArea;
    m_appParameter = appParameter;
    m_TopFlag = TopFlag;
    m_pParentWindow = ParentWindow;
    m_pControl = mControl;
}

// Process launch events for this connected button.

void MenuPage::Launch()
{
    // Create a webpage rendering surface window.
    m_pView = new QWebView(m_pMdiArea);

    // Create our custom plugin factory and register it to this page view.
    ButtonFactory * pButtonFactory = new ButtonFactory(this, m_pMdiArea, m_pView, m_pControl);
    m_pView->page()->setPluginFactory(pButtonFactory);

    // Read, parse, render and display HTML file specified on command line.
    m_pView->load(QUrl(m_appParameter));

    // Create subwindow to display web page without standard window title bar.
    m_pSubWindow = m_pMdiArea->addSubWindow(m_pView);

    // Make the window full screen size.
    m_pSubWindow->resize(QApplication::desktop()->size());

    // Restrict window resizing.
    m_pSubWindow->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    // Remove standard window title bar and minimize and close buttons.
    m_pSubWindow->setWindowFlags(Qt::FramelessWindowHint);

    m_pSubWindow->setStyleSheet("background-color: black");
    m_pSubWindow->show();
    m_pSubWindow->setFocus();
    if(m_pParentWindow != 0) {
      m_pParentWindow->Disable();
    }
    if (!m_TopFlag) {
        m_pSubWindow->move(m_pParentWindow->pos());
    }

    //qDebug() << "Launched Menu: " << m_appParameter;
}

// Make this menu visible and active.

void MenuPage::Enable()
{
    m_pSubWindow->setEnabled(true);
    m_pSubWindow->show();
    m_pSubWindow->setFocus();
}

// Make this menu inactive.

void MenuPage::Disable()
{
    m_pSubWindow->clearFocus();
    m_pSubWindow->setEnabled(false);
}

// Close this menu.

void MenuPage::Close()
{
    int ret=QMessageBox::No;
    if (m_TopFlag)
    {
        QMessageBox     msgBox;
        msgBox.setStyleSheet("Height: 64px");
        msgBox.setText("Are you sure you want to Exit?");
        msgBox.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
        msgBox.setIcon(QMessageBox::Question);
        ret=msgBox.exec();
    }
    if(ret==QMessageBox::Yes  || !m_TopFlag)
    {
      m_pView->close();
      m_pSubWindow->close();

      if(m_pParentWindow != 0 && !m_TopFlag) {
        m_pParentWindow->Enable();
      }
      //qDebug() << "Closed Menu";

      // Close Matrix if this is the main menu.
      if(ret==QMessageBox::Yes)
      {
        m_pMdiArea->close();
        QCoreApplication::quit();
      }
    }
}

void MenuPage::SavePlaunch(ButtonLaunch * pLaunch)
{
    qDebug() << "Made it save pLaunch" << "\n";
    m_pLaunch = pLaunch;
}

void MenuPage::LaunchApp(void)
{
    m_pLaunch->turnOffDesc();
    m_pLaunch->Launch();
}

void MenuPage::CloseMenu(void)
{
    m_pView->close();
    m_pSubWindow->close();
}
