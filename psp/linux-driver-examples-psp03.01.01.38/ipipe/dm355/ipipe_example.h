/*
 * ipipe_example.h
 *
 * 
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/ 
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
#ifndef _IPIPE_EXAMPLE_H
#define _IPIPE_EXAMPLE_H
struct buffer {
	void *start;
	int offset;
	int length;
	int index;
};

extern struct buffer *buffers;
#define     CAPTURE_DEVICE  "/dev/video0"
#define	DISPLAY_DEVICE  "/dev/fb/3"

#define VGA_WIDTH 	640
#define VGA_HEIGHT 	480
#define HD720P_WIDTH	1280
#define HD720P_HEIGHT	720
#define HD1080P_WIDTH	1920
#define HD1080P_HEIGHT	1080

#define IMAGE_BPP 16
#define DISPLAY_BUFS 	3
#define MIN_BUFFERS	3

#define D1_WIDTH 720
#define D1_HEIGHT 480

#define UYVY_BLACK          0x10801080

#endif /*EOF*/
