/*
 * messageserver.cpp
 *
 * This module handles the definitions and declarations for 
 * the message server, which communicates with the main demo application.
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

#include "messageserver.h"
#include "qtinterface.h"

#include <sys/stat.h>
#include <sys/time.h>
#include <sys/types.h>

#include <stdlib.h>
#include <unistd.h>
#include <linux/stat.h>

/* How often to poll for status updates (usec) */
#define LATENCY 500000

void MessageServer::run()
{
    /* Create the FIFOs if it does not exist */
    umask(0);
    mknod(CMD_FIFO_FILE, S_IFIFO|0666, 0);
    mknod(CONFIG_FIFO_FILE, S_IFIFO|0666, 0);    
    mknod(KB_CMD_FIFO_FILE, S_IFIFO|0666, 0);
    mknod(STATUS_FIFO_FILE, S_IFIFO|0666, 0);

    m_fpCmd = fopen(CMD_FIFO_FILE, "w");  
    m_fpConfig = fopen(CONFIG_FIFO_FILE, "w");
    m_fpKbCmd = fopen(KB_CMD_FIFO_FILE, "r");  
    m_fpStatus = fopen(STATUS_FIFO_FILE, "r");
       
    if ((m_fpCmd == NULL) || (m_fpConfig == NULL) || (m_fpKbCmd == NULL) 
        || (m_fpStatus == NULL)) {
        qFatal("Could not open pipe.\n");
        exit(EXIT_FAILURE);
    }  
    
    setvbuf(m_fpCmd, NULL, _IONBF, 0);
    setvbuf(m_fpConfig, NULL, _IONBF, 0);
    setvbuf(m_fpKbCmd, NULL, _IONBF, 0);
    setvbuf(m_fpStatus, NULL, _IONBF, 0);

    m_quit = false; 
    
    while(!m_quit) {
        fd_set rfds;
        struct timeval tv;
        int retval = 1;
        QString status;
        QtInterface_Command key;

        tv.tv_sec = 0;
        tv.tv_usec = 1;

        while (retval) {
            /* peek to see if there is any status message from demo */
            FD_ZERO(&rfds);
            FD_SET(fileno(m_fpStatus), &rfds);
            retval = select(fileno(m_fpStatus) + 1, &rfds, NULL, NULL, &tv);

            if (retval == -1) {
                qFatal("select error\n");
                exit(EXIT_FAILURE);
            }
            else if (retval) {
                /* Get message and signal to UI */
                getStatus();
            }
        }
        
        FD_ZERO(&rfds);    
        FD_SET(fileno(m_fpKbCmd), &rfds);
        /* peek every second to see if there is any keyboard message */
        retval = select(fileno(m_fpKbCmd) + 1, &rfds, NULL, NULL, &tv);

        if (retval == -1) {
            qFatal("select error\n");
            exit(EXIT_FAILURE);
        }
        else if (retval) {
            /* Get message and signal to UI */
            key = getKbCmd();
            switch (key) 
            {
                case QtInterface_Play:
                    emit playMsg();
                    break;
                case QtInterface_Pause:
                    emit pauseMsg();
                    break;
                case QtInterface_Stop:
                    emit stopMsg();
                    break;
                case QtInterface_Inc:
                    emit incMsg();
                    break;
                case QtInterface_Dec:
                    emit decMsg();
                    break;
                case QtInterface_Hide:
                    emit hideMsg();
                    break;
                default:
                    qWarning("Unsupported keyboard input received.\n");
                    break;
            }
        }       
        usleep(LATENCY);
    }    
    
    /* Close opened pipes */
    fclose(m_fpCmd);
    fclose(m_fpConfig);
    fclose(m_fpKbCmd);
    fclose(m_fpStatus);
}

void MessageServer::getStatus()
{
    char readBuf[QTINTERFACE_MAXSTRINGSIZE];
    QString label, value;
    int position;
  
    /* Get position */
    position = fgetc(m_fpStatus);
    
    /* Get strings */
    fgets(readBuf, (int)QTINTERFACE_MAXSTRINGSIZE, m_fpStatus);
    label = readBuf;
    fgets(readBuf, (int)QTINTERFACE_MAXSTRINGSIZE, m_fpStatus);
    value = readBuf;

    emit statusMsg(position, label.trimmed(), value.trimmed());
}

QtInterface_Command MessageServer::getKbCmd()
{
    QtInterface_Command cmd;
    
    /* Get keyboard input from demo */
    cmd = (QtInterface_Command)fgetc(m_fpKbCmd);    
    
    return cmd;
}

void MessageServer::sendCmd(QtInterface_Command cmd)
{
    if ((cmd == QtInterface_Play) || (cmd == QtInterface_Pause) || 
        (cmd == QtInterface_Stop)) {
        /* Send command via pipe */
        fputc(cmd, m_fpCmd);
    }
    else {
        qFatal("Bad command to send\n");
        exit(EXIT_FAILURE);
    }
}

void MessageServer::sendConfig(char option, QString cfgString)
{
    QString terminatedStr = cfgString + "\n";
    
    /* 
     * Send configuration option. 
     * This consists of the letter identifying it, along with a string
     * associated with it, terminated with a carriage return. 
     */
    fputc(option, m_fpConfig);
    fputs(terminatedStr.toAscii(), m_fpConfig);
}

void MessageServer::quit()
{
    m_quit = true;
}



