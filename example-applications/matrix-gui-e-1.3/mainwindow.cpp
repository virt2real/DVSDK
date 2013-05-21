/*
 * {module name} MainWindow
 *
 * {module description} Qt application main window
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

#include "mainwindow.h"
#include "menupage.h"
#include "matrixcontrol.h"

MainWindow::MainWindow(QMdiArea * const pMdiArea, const QString &appParameter, bool TopFlag)
{
    m_pMdiArea = pMdiArea;
    m_appParameter = appParameter;

    if (TopFlag)
    {
        m_pMdiArea = new QMdiArea(this);
        setCentralWidget(m_pMdiArea);

        // Enable plugin extensions to WebKit.
        QWebSettings::globalSettings()->setAttribute(QWebSettings::PluginsEnabled, true);

        mControl = new MatrixControl("On");

        // Create web page view for the main menu.
        MenuPage * pMenuPage = new MenuPage(m_pMdiArea, m_appParameter, true, 0, mControl);
        pMenuPage->Launch();
    }
}

// Default to a SVGA size display.

QSize MainWindow::sizeHint() const
{
    QSize size(800, 600);

    return size;
}
// Process launch events for this connected button.
