/* 
 * Copyright (c) 2010, Texas Instruments Incorporated
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * *  Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * *  Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * *  Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
 * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 * 
 */
/*
 *  ======== _lad.h ========
 */

#ifndef _lad_
#define _lad_

#ifdef __cplusplus
extern "C" {
#endif

/* macros for writing to log file: */
#define LOG0(a)  \
    if (logFile == TRUE) {  fprintf(logPtr, a); fflush(logPtr); }

#define LOG1(a, b)  \
    if (logFile == TRUE) {  fprintf(logPtr, a, b); fflush(logPtr); }

#define LOG2(a, b, c)  \
    if (logFile == TRUE) {  fprintf(logPtr, a, b, c); fflush(logPtr); }


/* macros for generating verbose output: */
#define PRINTVERBOSE0(a)  \
    if (verbose == TRUE) {  printf(a); }

#define PRINTVERBOSE1(a, b)  \
    if (verbose == TRUE) {  printf(a, b); }

#define PRINTVERBOSE2(a, b, c)  \
    if (verbose == TRUE) {  printf(a, b, c); }


/* LAD commmand FIFO strings: */
#define LAD_COMMANDFIFO         "/tmp/LAD/LADCMDS"
#define LAD_WORKINGDIR          "/tmp/LAD/"
#define LAD_RESPONSEFIFOPATH    LAD_WORKINGDIR
#define LAD_CMD                 "CMD="
#define LAD_RSP                 "RSP="
#define LAD_NULL                " "
#define LAD_CMDTERMINATOR       ";\n"
#define LAD_SEPARATOR           ";"
#define LAD_PROTOCOLVERSION     "03000000"    /*  MMSSRRRR */

#define LAD_MAXNUMCLIENTS       16      /* max simultaneous clients */ 
#define LAD_MAXNUMLINKCONFIGS   5       /* max number known link configs */ 
#define LAD_CONNECTTIMEOUT      5.0     /* LAD connect response timeout (sec) */
#define LAD_DISCONNECTTIMEOUT   5.0     /* LAD disconnect timeout (sec) */
#define LAD_MAXLENGTHFIFONAME   128     /* max length client FIFO name */ 
#define LAD_MAXLENGTHCOMMAND    512     /* size limit for LAD command string */
#define LAD_MAXLENGTHRESPONSE   512     /* size limit for LAD response string */
#define LAD_MAXLENGTHPROTOVERS  16      /* size limit for protocol version */
#define LAD_MAXLOGFILEPATH      256     /* size limit for LAD log file path */


typedef enum {
    LAD_CONNECT= 0,
    LAD_DISCONNECT = 1,
    LAD_STARTUPDSP = 2,
    LAD_RELEASEDSP = 3,
    LAD_GETDSPSTATUS = 4,
    LAD_EXIT = 5
} _LAD_Command;


#ifdef __cplusplus
}
#endif

#endif
/*
 *  @(#) ti.dsplink.utils.lad; 2, 0, 0,228; 12-2-2010 21:18:39; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

