/*
 * {module name} Main
 *
 * {module description} Standard C Main
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
#include "customstyle.h"
#include "osdmanager.h"

int main(int argc, char * argv[])
{
#if defined(Platform_dm365) || defined(Platform_dm368)
    // If OSD is available enable it and set the transparency
    OSDManager * pOsdMan = new OSDManager();
    pOsdMan->setTransparency(OSDManager::MAX_TRANSPARENCY);
#endif

    QApplication matrix(argc, argv);
    QApplication::setStyle(new CustomStyle);
//Commented out to enable the mouse
//    QApplication::setOverrideCursor(QCursor(Qt::BlankCursor));

    // Create a new window to display a web page.
    MainWindow * pWindow = new MainWindow(0, QString(argv[1]), true);

    // Make the window full screen size.
    pWindow->resize(QApplication::desktop()->size());

    // Restrict window resizing.
    pWindow->setSizePolicy(QSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed));

    // Remove standard window title bar and minimize and close buttons.
    pWindow->setWindowFlags(Qt::FramelessWindowHint);

    // Display the new window.
    pWindow->show();

    QObject::connect(&matrix, SIGNAL(lastWindowClosed()), &matrix, SLOT(quit()));

    return matrix.exec();
}
