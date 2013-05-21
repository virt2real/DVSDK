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
#ifndef _CEAPP_H_
#define _CEAPP_H_

/* API for the Codec-Engine-using subsystem, that hides Codec Engine API from
 * its users
 */

extern int   ceapp_init();            /* initialize the ceapp module */

extern char *ceapp_allocContigBuf(    /* allocate physically contiguous */
                int   bufSize,        /*   buffer of given size; description */
                char *bufDescription  /*   is used only for print */
                );
                
extern int   ceapp_validateBufSizes(  /* confirm that the enc/dec codecs */
                int inBufSize,        /*   support these buffer sizes */
                int encodedBufSize,   /*   for the raw input video, encoded */
                int outBufSize        /*   video data, and decoded output */
                );
                
extern int   ceapp_encodeBuf(         /* encode raw video data in inBuf */
                char *inBuf,          /*   and store result in encodedBuf */
                int   inBufSize,
                char *encodedBuf,
                int   encodedBufSize
                );
                
extern int   ceapp_decodeBuf(         /* decode data from encodedBuf and */
                char *encodedBuf,     /*   store resulting raw data in outBuf */
                int   encodedBufSize,
                char *outBuf,
                int   outBufSize
                );
                
extern void  ceapp_freeContigBuf(     /* free the contiguous buffer */
                char *buf,
                int   bufSize
                );
                
extern void  ceapp_exit();            /* exit the ceapp module */


#endif /* _CEAPP_H_ */

/*
 *  @(#) ti.sdo.ce.examples.apps.video_copy; 1, 0, 0,77; 12-2-2010 21:21:31; /db/atree/library/trees/ce/ce-r11x/src/ xlibrary

 */

