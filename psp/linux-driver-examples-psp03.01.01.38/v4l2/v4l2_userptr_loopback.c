/*
 * v4l2_userptr_loopback
 *
 * Copyright (C) 2009 Texas Instruments Incorporated - http://www.ti.com/
 *
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * Redistributions of source code must retain the above copyright
 * notice, this list of conditions and the following disclaimer.
 *
 * Redistributions in binary form must reproduce the above copyright
 * notice, this list of conditions and the following disclaimer in the
 * documentation and/or other materials provided with the
 * distribution.
 *
 * Neither the name of Texas Instruments Incorporated nor the names of
 * its contributors may be used to endorse or promote products derived
 * from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 * A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
 * OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
 * SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
 * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/
/*******************************************************************************
**+--------------------------------------------------------------------------+**
**|                            ****                                          |**
**|                            ****                                          |**
**|                            ******o***                                    |**
**|                      ********_///_****                                   |**
**|                      ***** /_//_/ ****                                   |**
**|                       ** ** (__/ ****                                    |**
**|                           *********                                      |**
**|                            ****                                          |**
**|                            ***                                           |**
**|                                                                          |**
**|         Copyright (c) 1998-2008 Texas Instruments Incorporated           |**
**|                        ALL RIGHTS RESERVED                               |**
**|                                                                          |**
**| Permission is hereby granted to licensees of Texas Instruments           |**
**| Incorporated (TI) products to use this computer program for the sole     |**
**| purpose of implementing a licensee product based on TI products.         |**
**| No other rights to reproduce, use, or disseminate this computer          |**
**| program, whether in part or in whole, are granted.                       |**
**|                                                                          |**
**| TI makes no representation or warranties with respect to the             |**
**| performance of this computer program, and specifically disclaims         |**
**| any responsibility for any damages, special or consequential,            |**
**| connected with the use of this program.                                  |**
**|																			 |**
**|	File: v4l2_userptr_loopback.c											 	 |**
**|																			 |**
**| Description: 															 |**
**|																			 |**
**|   This is a sample loopback application that sense the input video       |**
**| standard at the composite input and play the same for NTSC/PAL display   |**
**|	at the composite output. This uses MMAP IO for capture and display		 |** 
**|	driver. 				                                                 |**
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/
/*******************************************************************************
 *	HEADER FILES
 */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <linux/fb.h>
#include <time.h>

/* Kernel header file, prefix path comes from makefile */
#include <video/davincifb_ioctl.h>
#include <video/davinci_osd.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>
#include <media/davinci/davinci_display.h>
#include <media/davinci/videohd.h>

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define CAPTURE_DEVICE	"/dev/video0"

#define WIDTH_NTSC		720
#define HEIGHT_NTSC		480
#define WIDTH_PAL		720
#define HEIGHT_PAL		576
#define WIDTH_720P		1280
#define HEIGHT_720P		720	
#define WIDTH_1080I		1920
#define HEIGHT_1080I		1080

#define MIN_BUFFERS	6

#define UYVY_BLACK	0x10801080

/* Device parameters */
#define VID0_DEVICE	"/dev/video2"
#define VID1_DEVICE	"/dev/video3"
#define OSD0_DEVICE	"/dev/fb0"
#define OSD1_DEVICE	"/dev/fb2"

/* Function error codes */
#define SUCCESS		0
#define FAILURE		-1

/* Bits per pixel for video window */
#define YUV_422_BPP	16
#define BITMAP_BPP_8	8

#define DISPLAY_INTERFACE_COMPOSITE	"COMPOSITE"
#define DISPLAY_INTERFACE_COMPONENT	"COMPONENT"
#define DISPLAY_MODE_PAL	"PAL"
#define DISPLAY_MODE_NTSC	"NTSC"
#define DISPLAY_MODE_720P	"720P-60"		
#define DISPLAY_MODE_1080I	"1080I-30"		

#define round_32(width)	((((width) + 31) / 32) * 32 )

#define VIDEO_NUM_BUFS	6

/* Standards and output information */
#define ATTRIB_MODE		"mode"
#define ATTRIB_OUTPUT		"output"

#define LOOP_COUNT		500

#define DEBUG
#ifdef DEBUG
#define DBGENTER  	printf("%s : Enter\n", __FUNCTION__);
#define DBGEXIT		printf("%s : Leave\n", __FUNCTION__);
#define PREV_DEBUG(x)	printf("DEBUG:%s:%s:%s\n",__FUNCTION__,__LINE__,x);
#else
#define DBGENTER
#define DBGEXIT
#define PREV_DEBUG(x)
#endif

#define CLEAR(x)	memset (&(x), 0, sizeof (x))
static int en_capture_to_file;
int num_frame_to_capture = 100;
#define FILE_CAPTURE "./output.yuv"
FILE *fp_capture;
int file_size;


/*******************************************************************************
 *	STRUCTURE DEFINITIONS
 */
struct buffer {
	void *start;
	size_t length;
};

/*******************************************************************************
 *	FILE GLOBALS
 */
static int fdCapture = -1;
static struct buffer *buffers, vid1Buf[VIDEO_NUM_BUFS];
static int nBuffers;
static int nWidthFinal;
static int nHeightFinal;
static int quit;
static int fd_vid1, fd_osd0, fd_osd1;
static int cr_width = 0, cr_height = 0, cr_top = 0, cr_left = 0, crop_en = 0, src_line_len = 0;
static int stress_test = 1;
static int start_loopCnt = LOOP_COUNT;
static struct v4l2_requestbuffers reqbuf;
static int disppitch, dispheight, dispwidth;
static int numbuffers = VIDEO_NUM_BUFS;
static struct v4l2_cropcap cropcap;
static int printfn = 0;
/* 0 - composite
 * 1 - S-video
 * 2 - Camera
 */
int vpfe_input = 0;
static int input_std;
static int field;
char *inputs[] = { "COMPOSITE", "SVIDEO", "COMPONENT" };
int display_image_size = 0;

/*******************************************************************************
 *	EXTERN VARIABLES
 */
extern int errno;

/*******************************************************************************
 *	LOCAL FUNCTION PROTOTYPES
 */
static int initialize_capture(v4l2_std_id * cur_std);
static int put_display_buffer(int, int);
static int get_display_buffer(int);
static int stop_display(int);
static int release_display(int *);
static int release_capture(int *);
static int stop_capture(int);
static int start_loop(void);
static int init_capture_device(void);
static int set_data_format(v4l2_std_id * cur_std);
static int init_capture_buffers(void);
static int start_streaming(void);
static int start_display(int, int, int);
static int init_vid1_device(v4l2_std_id cur_std);
static int vpbe_UE_1();
static int change_sysfs_attrib(char *attribute, char *value);

/*******************************************************************************
 *	FUNCTION DEFINITIONS
 */
static int initialize_capture(v4l2_std_id * cur_std)
{
	int ret;
	printf("initializing capture device\n");
	init_capture_device();
	printf("setting data format\n");
	ret = set_data_format(cur_std);
	if (ret) {
		printf("Error in setting capture format\n");
		return ret;
	}
	printf("initializing capture buffers\n");
	ret = init_capture_buffers();
	if (ret) {
		printf("Failed to initialize capture buffers\n");
		return ret;
	}
	printf("initializing display device\n");
	ret = start_streaming();
	if (ret) {
		printf("Failed to start capture streaming\n");
		return ret;
	}
	return 0;
}

/*******************************************************************************
 *	Takes the address, finds the appropriate index
 *	of the buffer, and QUEUEs the buffer to display
 *	If this part is done in the main loop,
 *	there is no need of this conversionof address
 *	to index as both are available.
 */
static int put_display_buffer(int vid_win, int index)
{
	struct v4l2_buffer buf;
	int i = 0;
	int ret;

	memset(&buf, 0, sizeof(buf));

	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf.memory = V4L2_MEMORY_USERPTR;
	buf.index = index;
	buf.length = display_image_size;
	buf.m.userptr = (unsigned long)buffers[index].start;

	ret = ioctl(vid_win, VIDIOC_QBUF, &buf);
	return ret;
}

/*******************************************************************************
 *	Does a DEQUEUE and gets/returns the address of the
 *	dequeued buffer
 */
static int get_display_buffer(int vid_win)
{
	int ret;
	struct v4l2_buffer buf;
	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(vid_win, VIDIOC_DQBUF, &buf);
	if (ret < 0) {
		perror("VIDIOC_DQBUF\n");
		return -1;
	}
	return buf.index;
}

/*******************************************************************************
 *	Stops Streaming
 */
static int stop_display(int vid_win)
{
	int ret;
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(vid_win, VIDIOC_STREAMOFF, &type);
	return ret;
}

/*******************************************************************************
 *	This routine unmaps all the buffers
 *	This is the final step.
 */
static int release_display(int *vid_win)
{
	close(*vid_win);
	*vid_win = 0;
	return 0;
}

/*******************************************************************************
 *      This routine unmaps all the buffers
 *      This is the final step.
 */
static int release_capture(int *vid_win)
{
	int i;
	for (i = 0; i < MIN_BUFFERS; i++) {
		munmap(buffers[i].start, buffers[i].length);
		buffers[i].start = NULL;
	}
	close(*vid_win);
	*vid_win = 0;
	return 0;
}

/*******************************************************************************
 *      Stops Streaming
 */
static int stop_capture(int vid_win)
{
	int ret;
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(vid_win, VIDIOC_STREAMOFF, &type);
	return ret;
}

/******************************************************************************/
static int start_loop(void)
{
	int ret, display_index;
	struct v4l2_buffer buf;
	static int captFrmCnt = 0;
	unsigned char *displaybuffer = NULL;
	int i;
	char *ptrPlanar = NULL;
	void *src, *dest;

	ptrPlanar = (char *)calloc(1, nWidthFinal * nHeightFinal * 2);

	while (!quit) {
		fd_set fds;
		struct timeval tv;
		int r;


		FD_ZERO(&fds);
		FD_SET(fdCapture, &fds);

		/* Timeout */
		tv.tv_sec = 2;
		tv.tv_usec = 0;
		r = select(fdCapture + 1, &fds, NULL, NULL, &tv);
		if (-1 == r) {
			if (EINTR == errno)
				continue;
			printf("StartCameraCapture:select\n");
			return -1;
		}
		if (0 == r)
			continue;

		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;

		/* determine ready buffer */
		if (-1 == ioctl(fdCapture, VIDIOC_DQBUF, &buf)) {
			if (EAGAIN == errno)
				continue;
			printf("StartCameraCaputre:ioctl:VIDIOC_DQBUF\n");
			return -1;
		}

		if (en_capture_to_file) {
			if (captFrmCnt == num_frame_to_capture) {
				printf("Writing frame %d to file %s, size = %d\n",num_frame_to_capture,
					 FILE_CAPTURE, file_size);
				fwrite(buffers[buf.index].start, 1, file_size, fp_capture);
				printf("Writing file %s complete\n", FILE_CAPTURE);
				fclose(fp_capture);
			}
		}
		if (captFrmCnt <= 1) {
			
			if (!captFrmCnt) {
				printf("5. Test enque first buffer\n");
				ret = start_display(fd_vid1, buf.index, 0);
			}
			else {
				printf("5. Test enque second buffer\n");
				ret = start_display(fd_vid1, buf.index, 1);
			}
			if (ret < 0) {
				printf("\tError: Starting display failed:VID1\n");
				return ret;
			}
			captFrmCnt++;
			continue;
		}
		
		ret = put_display_buffer(fd_vid1, buf.index);
		if (ret < 0) {
			printf("Error in putting the display buffer\n");
			return ret;
		}

		/******************* V4L2 display ********************/
		display_index = get_display_buffer(fd_vid1);
		if (display_index < 0) {
			printf("Error in getting the  display buffer:VID1\n");
			return ret;
		}
		/***************** END V4L2 display ******************/

		
		if (printfn)
			printf("time:%lu    frame:%u\n", (unsigned long)time(NULL),
		       		captFrmCnt++);

		buf.index = display_index;
		/* requeue the buffer */
		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf))
			printf("StartCameraCaputre:ioctl:VIDIOC_QBUF\n");
		if (stress_test) {
			start_loopCnt--;
			if (start_loopCnt == 0) {
				start_loopCnt = 50;
				break;
			}
		}
	}

	return ret;
}

/******************************************************************************/
static int init_capture_device(void)
{
	struct v4l2_capability cap;

	/* input-0 is selected by default, so no need to set it */
	if ((fdCapture = open(CAPTURE_DEVICE, O_RDWR, 0)) <= -1) {
		printf("InitDevice:open::\n");
		return -1;
	}

	/* is capture supported? */
	if (-1 == ioctl(fdCapture, VIDIOC_QUERYCAP, &cap)) {
		printf("InitDevice:ioctl:VIDIOC_QUERYCAP:\n");
		return -1;
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		printf("InitDevice:capture is not supported on:%s\n",
		       CAPTURE_DEVICE);
		return -1;
	}

	/* is MMAP-IO supported? */
	if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
		printf("InitDevice:IO method MMAP is not supported on:%s\n",
		       CAPTURE_DEVICE);
		return -1;
	}

	return 0;
}

/******************************************************************************/
static int set_data_format(v4l2_std_id * cur_std)
{
	v4l2_std_id prev_std;
	struct v4l2_format fmt;
	unsigned int min;
	struct v4l2_input input;
	int temp_input;
	struct v4l2_cropcap cropcap;
	struct v4l2_crop crop;
	struct v4l2_fmtdesc fmt_desc;
	struct v4l2_standard standard;
	int ret;

	// first set the input
	input.type = V4L2_INPUT_TYPE_CAMERA;
	input.index = 0;
  	while ((ret = ioctl(fdCapture,VIDIOC_ENUMINPUT, &input) == 0)) { 
		printf("input.name = %s\n", input.name);
		if ((vpfe_input == 0) && !strcmp(input.name, "Composite"))
			break;
		if ((vpfe_input == 1) && !strcmp(input.name, "S-Video"))
			break;
		if ((vpfe_input == 2) && !strcmp(input.name, "Camera"))
			break;
		if ((vpfe_input == 3) && !strcmp(input.name, "Component"))
			break;
		input.index++;
  	}

	if (ret < 0) {
		printf("Couldn't find the input\n");
		return -1;
	}

	printf("Calling S_INPUT with index = %d\n", input.index);
  	if (-1 == ioctl (fdCapture, VIDIOC_S_INPUT, &input.index))
  	{
		perror("Error:InitDevice:ioctl:VIDIOC_S_INPUT\n");
      		return -1;
  	}
  	printf ("InitDevice:ioctl:VIDIOC_S_INPUT, selected input index = %d\n",
		input.index);

	if (-1 == ioctl (fdCapture, VIDIOC_G_INPUT, &temp_input))
	{
		perror("Error:InitDevice:ioctl:VIDIOC_G_INPUT\n");
		return -1;
	}
	
	if (temp_input == input.index)
		printf ("InitDevice:ioctl:VIDIOC_G_INPUT, selected input, %s\n", input.name);
	else {
		printf ("Error: InitDevice:ioctl:VIDIOC_G_INPUT,");
		printf("Couldn't select %s input\n", input.name);
		return -1;
  	}

	printf("Following standards available at the input\n");
	standard.index = 0;
	if (vpfe_input != 3) {
		while (0 == ioctl (fdCapture, VIDIOC_ENUMSTD, &standard)) {
			printf("standard.index = %d\n", standard.index);
			printf("standard.id = %llx\n", standard.id);
			printf("standard.frameperiod.numerator = %d\n",
				standard.frameperiod.numerator);
			printf("standard.frameperiod.denominator = %d\n",
				standard.frameperiod.denominator);
			printf("standard.framelines = %d\n",
				standard.framelines);
			standard.index++;
		}
	}

#if 0
	*cur_std = V4L2_STD_PAL;

	if (-1 == ioctl(fdCapture, VIDIOC_S_STD, cur_std)) {
		perror("set_data_format:ioctl:VIDIOC_S_STD\n");
		return -1;
	}

#endif
	if (vpfe_input < 2) {
		if (input_std == 0)
			*cur_std = V4L2_STD_NTSC;
		else
			*cur_std = V4L2_STD_PAL;
		printf("Setting standard, std_id - %llx\n",*cur_std); 

		if (-1 == ioctl(fdCapture, VIDIOC_S_STD, cur_std)) {
			perror("set_data_format:ioctl:VIDIOC_S_STD:\n");
			return -1;
		}

		if (-1 == ioctl(fdCapture, VIDIOC_QUERYSTD, cur_std)) {
			perror("set_data_format:ioctl:VIDIOC_QUERYSTD:\n");
			return -1;
		}

		if (*cur_std & V4L2_STD_NTSC)
			printf("Input video standard is NTSC.\n");
		else if (*cur_std & V4L2_STD_PAL)
			printf("Input video standard is PAL.\n");
		else if (*cur_std & V4L2_STD_PAL_M)
			printf("Input video standard is PAL-M.\n");
		else if (*cur_std & V4L2_STD_PAL_N)
			printf("Input video standard is PAL-N.\n");
		else if (*cur_std & V4L2_STD_SECAM)
			printf("Input video standard is SECAM.\n");
		else if (*cur_std & V4L2_STD_PAL_60)
			printf("Input video standard to PAL60.\n");
		else 
			return -1;
	} else if (vpfe_input == 3) {
		if (input_std == 0)
			*cur_std = V4L2_STD_720P_60;
		else
			*cur_std = V4L2_STD_1080I_60;
		printf("Setting standard, std_id - %llx\n",*cur_std); 

		if (-1 == ioctl(fdCapture, VIDIOC_S_STD, cur_std)) {
			perror("set_data_format:ioctl:VIDIOC_S_STD:\n");
			return -1;
		}

		if (-1 == ioctl(fdCapture, VIDIOC_QUERYSTD, cur_std)) {
			perror("set_data_format:ioctl:VIDIOC_QUERYSTD:\n");
			return -1;
		}

		if (*cur_std & V4L2_STD_720P_60)
			printf("Input video standard is 720P-60.\n");
		else if (*cur_std & V4L2_STD_1080I_60)
			printf("Input video standard is 1080I-60.\n");
		else 
			return -1;
	}

	/* select cropping as deault rectangle */
	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (-1 == ioctl(fdCapture, VIDIOC_CROPCAP, &cropcap)) {
		printf("InitDevice:ioctl:VIDIOC_CROPCAP\n");
		/* ignore error */
	}

	printf("Default crop capbility bounds - %d %d %d %d"
	       " ; default - %d %d %d %d \n",
	       cropcap.bounds.left, cropcap.bounds.top,
	       cropcap.bounds.width, cropcap.bounds.height,
	       cropcap.defrect.left, cropcap.defrect.top,
	       cropcap.defrect.width, cropcap.defrect.height);
	printf("set_data_format:setting data format\n");

	CLEAR(fmt_desc);
	fmt_desc.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	printf("Available image formats at the capture driver :-\n");
	while (0 == ioctl(fdCapture, VIDIOC_ENUM_FMT, &fmt_desc)) {
		printf("fmt_desc.index = %d\n", fmt_desc.index);
		printf("fmt_desc.type = %d\n", fmt_desc.type);
		printf("fmt_desc.description = %s\n", fmt_desc.description);
		printf("fmt_desc.pixelformat = %x\n", fmt_desc.pixelformat);
		fmt_desc.index++;
	}
	
	/* Try format with minimum and maximum values */
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = 1;
	fmt.fmt.pix.height = 1;
	if (vpfe_input == 2) {
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
		fmt.fmt.pix.field = V4L2_FIELD_ANY;
	} else {
		fmt.fmt.pix.field = V4L2_FIELD_ANY;
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	}
	printf("*******TRY_FMT (Min resolution) values before calling ioctl*************\n");
	printf("fmt.fmt.pix.width = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.field= %d\n", fmt.fmt.pix.field);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
	if (-1 == ioctl(fdCapture, VIDIOC_TRY_FMT, &fmt))
		printf("Error:set_data_format:ioctl:VIDIOC_TRY_FMT\n");

	printf("*******TRY_FMT values after calling ioctl*************\n");
	printf("fmt.fmt.pix.width = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.field= %d\n", fmt.fmt.pix.field);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
	
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = (1 << 15);
	fmt.fmt.pix.height = (1 << 15);
	if (vpfe_input == 2) {
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
		fmt.fmt.pix.field = V4L2_FIELD_ANY;
	} else {
		fmt.fmt.pix.field = V4L2_FIELD_ANY;
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	}
	printf("*******TRY_FMT (Max resolution) values before calling ioctl*************\n");
	printf("fmt.fmt.pix.width = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.field= %d\n", fmt.fmt.pix.field);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
	if (-1 == ioctl(fdCapture, VIDIOC_TRY_FMT, &fmt))
		printf("Error:set_data_format:ioctl:VIDIOC_TRY_FMT\n");

	printf("*******TRY_FMT values after calling ioctl*************\n");
	printf("fmt.fmt.pix.width = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.field= %d\n", fmt.fmt.pix.field);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);

	if (vpfe_input == 2) {
		if(input_std == 0)
		{
			fmt.fmt.pix.width = 640;
			fmt.fmt.pix.height = 480;
		}
		else if(input_std == 1)
		{
			fmt.fmt.pix.width = 736;
			fmt.fmt.pix.height = 480;
		}
		else if(input_std == 2)
		{
			fmt.fmt.pix.width = 736;
			fmt.fmt.pix.height = 576;
		}
		else if(input_std == 3)
		{
			fmt.fmt.pix.width = 1280;
			fmt.fmt.pix.height = 720;
		}
		else if(input_std == 4)
		{
			fmt.fmt.pix.width = 1920;
			fmt.fmt.pix.height = 1080;
		}
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if (vpfe_input == 3) {
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
		if(input_std == 0)
		{
			fmt.fmt.pix.width = 1280;
			fmt.fmt.pix.height = 720;
			fmt.fmt.pix.field = V4L2_FIELD_NONE;
		}
		else if(input_std == 1)
		{
			fmt.fmt.pix.width = 1920;
			fmt.fmt.pix.height = 1080;
			fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
		}
	} else {
		if (crop_en == 1)
		{
			fmt.fmt.pix.width = cr_width;
			fmt.fmt.pix.height = cr_height;
		}	
		else if (*cur_std & V4L2_STD_NTSC) {
			fmt.fmt.pix.width = WIDTH_NTSC;
			fmt.fmt.pix.height = HEIGHT_NTSC;
			cr_width = WIDTH_NTSC;
			cr_height = HEIGHT_NTSC;
		} else {
			fmt.fmt.pix.width = WIDTH_PAL;
			fmt.fmt.pix.height = HEIGHT_PAL;
			cr_width = WIDTH_PAL;
			cr_height = HEIGHT_PAL;
		}
		
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
		if (field)
			fmt.fmt.pix.field = V4L2_FIELD_SEQ_TB;
		else
			fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	}

	printf("the filed = %d \n", fmt.fmt.pix.field);
	
	#if 0
	fmt.fmt.pix.field = 0;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_YUYV;
	#endif

	if (-1 == ioctl(fdCapture, VIDIOC_S_FMT, &fmt))
		printf("set_data_format:ioctl:VIDIOC_S_FMT\n");

	if (-1 == ioctl(fdCapture, VIDIOC_G_FMT, &fmt))
		printf("set_data_format:ioctl:VIDIOC_QUERYSTD:\n");

	if(crop_en == 1)
	{
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		crop.c.width= cr_width;
		crop.c.height= cr_height;
		crop.c.top  = cr_top;
		crop.c.left = cr_left;
		if(-1 == ioctl(fdCapture, VIDIOC_S_CROP, &crop))
		{
			perror("Error in setting crop \n");
			return -1;
		}
	}
		
	

	nWidthFinal = fmt.fmt.pix.width;
	nHeightFinal = fmt.fmt.pix.height;

	printf("set_data_format:finally negotiated width:%d height:%d\n",
	       nWidthFinal, nHeightFinal);

	/* checking what is finally negotiated */
	min = fmt.fmt.pix.width * 2;
	if (fmt.fmt.pix.bytesperline < min) {
		printf
		    ("set_data_format:driver reports bytes_per_line:%d(bug)\n",
		     fmt.fmt.pix.bytesperline);
		/*correct it */
		fmt.fmt.pix.bytesperline = min;
	} else {
		printf
		    ("set_data_format:driver reports bytes_per_line:%d\n",
		     fmt.fmt.pix.bytesperline);
	}
	src_line_len = fmt.fmt.pix.bytesperline;
	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if (fmt.fmt.pix.sizeimage < min) {
		printf("set_data_format:driver reports size:%d(bug)\n",
		       fmt.fmt.pix.sizeimage);

		/*correct it */
		fmt.fmt.pix.sizeimage = min;
	} else {
		printf("set_data_format:driver reports size:%d\n",
		       fmt.fmt.pix.sizeimage);
	}

	printf("set_data_format:Finally negotiated width:%d height:%d\n",
	       nWidthFinal, nHeightFinal);

	return 0;
}

/******************************************************************************/
static int init_capture_buffers(void)
{
	struct v4l2_requestbuffers req;
	int nIndex = 0;

	CLEAR(req);
	req.count = MIN_BUFFERS;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	if (-1 == ioctl(fdCapture, VIDIOC_REQBUFS, &req)) {
		printf("init_capture_buffers:ioctl:VIDIOC_REQBUFS\n");
		return -1;
	}

	if (req.count < MIN_BUFFERS) {
		printf("init_capture_buffers only:"
		       "%d buffers avilable, can't proceed\n", req.count);
		return -1;
	}

	nBuffers = req.count;
	printf("device buffers:%d\n", req.count);
	buffers = (struct buffer *)calloc(req.count, sizeof(struct buffer));
	if (!buffers) {
		printf("init_capture_buffers:calloc:\n");
		return -1;
	}

	for (nIndex = 0; nIndex < req.count; ++nIndex) {
		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = nIndex;

		if (-1 == ioctl(fdCapture, VIDIOC_QUERYBUF, &buf)) {
			printf("init_capture_buffers:VIDIOC_QUERYBUF:\n\n");
			return -1;
		}

		buffers[nIndex].length = buf.length;
		buffers[nIndex].start =
		    mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
			 MAP_SHARED, fdCapture, buf.m.offset);

		printf("buffer:%d phy:%x mmap:%p length:%d\n", buf.index,
		       buf.m.offset, buffers[nIndex].start, buf.length);

		if (MAP_FAILED == buffers[nIndex].start) {
			printf("init_capture_buffers:mmap:\n");
			return -1;
		}
	}
	return 0;
}

/******************************************************************************/
static int start_streaming(void)
{
	int i = 0;
	enum v4l2_buf_type type;

	for (i = 0; i < nBuffers; i++) {
		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = i;
		printf("Queing buffer:%d\n", i);

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf))
			printf("start_streaming:ioctl:VIDIOC_QBUF:\n");
	}
	/* all done , get set go */
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fdCapture, VIDIOC_STREAMON, &type))
		printf("start_streaming:ioctl:VIDIOC_STREAMON:\n");

	return 0;
}

/******************************************************************************/
static int start_display(int fd, int index, int flag)
{
	int ret;
	struct v4l2_buffer buf;
	enum v4l2_buf_type type;

	bzero(&buf, sizeof(buf));
	/*
	 *      Queue all the buffers for the initial running
	 */
	printf("6. Test enqueuing of buffers - ");
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf.memory = V4L2_MEMORY_USERPTR;
	buf.index = index;
	buf.length = display_image_size;
	buf.m.userptr = (unsigned long)buffers[index].start;
	ret = ioctl(fd, VIDIOC_QBUF, &buf);
	if (ret < 0) {
		printf("fd = %d\n", fd);
		printf("\n\tError: Enqueuing buffer[%d] failed: VID1",
		       index);
		return -1;
	}

	printf("done\n");

	if (flag) {
		printf("7. Test STREAM_ON\n");
		type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		ret = ioctl(fd, VIDIOC_STREAMON, &type);
		if (ret < 0) {
			perror("VIDIOC_STREAMON\n");
			return -1;
		}
	}

	return 0;
}

/******************************************************************************/
static int init_vid1_device(v4l2_std_id cur_std)
{
	int mode = O_RDWR;
	int i = 0, ret = 0;

	struct v4l2_format fmt, setfmt;
	struct v4l2_fmtdesc format;
	struct v4l2_capability capability;

	/* open osd0, osd1 devices and disable */
	fd_osd0 = open(OSD0_DEVICE, mode);
	ioctl(fd_osd0, FBIOBLANK, 1);

	fd_osd1 = open(OSD1_DEVICE, mode);
	ioctl(fd_osd1, FBIOBLANK, 1);

	/*
	 * 1. Open display channel
	 */
	printf("1. Opening VID1 device\n");
	fd_vid1 = open(VID1_DEVICE, mode);
	if (-1 == fd_vid1) {
		printf("failed to open VID1 display device\n");
		return -1;
	}
	printf("done\n");

	/* Testing IOCTLs */
	ret = ioctl(fd_vid1, VIDIOC_QUERYCAP, &capability);
	if (ret < 0) {
		printf("FAILED: QUERYCAP\n");
		return -1;
	}
	printf("fd = %d\n", fd_vid1);
	if (capability.capabilities & V4L2_CAP_VIDEO_OUTPUT)
		printf("Display capability is supported\n");
	if (capability.capabilities & V4L2_CAP_STREAMING)
		printf("Streaming is supported\n");

	while (1) {
		format.index = i;
		format.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		ret = ioctl(fd_vid1, VIDIOC_ENUM_FMT, &format);
		if (ret < 0)
			break;
		printf("description = %s\n", format.description);
		if (format.type == V4L2_BUF_TYPE_VIDEO_OUTPUT)
			printf("Video Display type\n");
		if (format.pixelformat == V4L2_PIX_FMT_UYVY)
			printf("V4L2_PIX_FMT_UYVY\n");
		i++;
	}

	/*
	 * Now for the buffers. Request the number of buffers needed
	 * and the kind of buffers (User buffers or kernel buffers
	 * for memory mapping).
	 * Please note that the return value in the reqbuf.count
	 * might be lesser than numbuffers under some low memory
	 * circumstances
	 */
	printf("2. Test request for buffers\n");
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	reqbuf.count = numbuffers;
	reqbuf.memory = V4L2_MEMORY_USERPTR;
	ret = ioctl(fd_vid1, VIDIOC_REQBUFS, &reqbuf);
	if (ret < 0) {
		printf("\n\tError: Could not allocate the buffers: VID1\n");
		return -1;
	}
	printf("\tNumbers of buffers returned - %d\n", reqbuf.count);
	CLEAR(setfmt);
	setfmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	setfmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	if (cur_std & V4L2_STD_NTSC) {
		printf("init_vid1_device:requesting width:%d height:%d\n",
		       WIDTH_NTSC, HEIGHT_NTSC);
		setfmt.fmt.pix.bytesperline = WIDTH_NTSC * 2;
		setfmt.fmt.pix.sizeimage =
		    setfmt.fmt.pix.bytesperline * HEIGHT_NTSC;
		setfmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if ((cur_std & V4L2_STD_PAL) ||
		(cur_std & V4L2_STD_PAL_M) ||
		(cur_std & V4L2_STD_PAL_N)) {
		printf("init_vid1_device:requesting width:%d height:%d\n",
		       WIDTH_PAL, HEIGHT_PAL);
		setfmt.fmt.pix.bytesperline = WIDTH_PAL * 2;
		setfmt.fmt.pix.sizeimage =
		    setfmt.fmt.pix.bytesperline * HEIGHT_PAL;
		setfmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if ((cur_std & V4L2_STD_720P_60) ||
		   (cur_std & V4L2_STD_720P_50)) {
		printf("init_vid1_device:requesting width:%d height:%d\n",
		       WIDTH_720P, HEIGHT_720P);
		setfmt.fmt.pix.bytesperline = WIDTH_720P * 2;
		setfmt.fmt.pix.sizeimage =
		    setfmt.fmt.pix.bytesperline * HEIGHT_720P;
		setfmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if ((cur_std & V4L2_STD_1080I_60) ||
		   (cur_std & V4L2_STD_1080I_50)) {
		printf("init_vid1_device:requesting width:%d height:%d\n",
		       WIDTH_1080I, HEIGHT_1080I);
		setfmt.fmt.pix.bytesperline = WIDTH_1080I * 2;
		setfmt.fmt.pix.sizeimage =
		    setfmt.fmt.pix.bytesperline * HEIGHT_1080I;
		setfmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else {
		printf("This video cannot be displayed\n");
		close(fd_vid1);
		return -1;
	}

	display_image_size = setfmt.fmt.pix.sizeimage;
	
	ret = ioctl(fd_vid1, VIDIOC_S_FMT, &setfmt);
	if (ret < 0) {
		perror("VIDIOC_S_FMT\n");
		close(fd_vid1);
		return -1;
	} else
		printf(" VIDIOC_S_FMT: PASS\n");

	/*
	 * It is necessary for applications to know about the
	 * buffer chacteristics that are set by the driver for
	 * proper handling of buffers
	 * These are : width,height,pitch and image size
	 */
	printf("3. Test GetFormat\n");
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(fd_vid1, VIDIOC_G_FMT, &fmt);
	if (ret < 0) {
		printf("\tError: Get Format failed: VID1\n");
		return -1;
	}
	dispheight = fmt.fmt.pix.height;
	disppitch = fmt.fmt.pix.bytesperline;
	dispwidth = fmt.fmt.pix.width;

	printf("\tdispheight = %d\n\tdisppitch = %d\n\tdispwidth = %d\n",
	       dispheight, disppitch, dispwidth);
	printf("\timagesize = %d\n", fmt.fmt.pix.sizeimage);
	
	return SUCCESS;
}

/******************************************************************************
 * Example to show vid1 in YUV format,OSD0 in RGB565 format
 *  and OSD1 is attribute format.
 ******************************************************************************/
static int vpbe_UE_1(void)
{
	int ret = 0;
	v4l2_std_id cur_std;

	DBGENTER;

	/* Setup Capture */
	if (initialize_capture(&cur_std) < 0) {
		printf("Failed to intialize capture\n");
		return ret;
	}

	/* Setup Display */
	if (cur_std & V4L2_STD_NTSC) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE))
			return FAILURE;
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_NTSC))
			return FAILURE;
		file_size = WIDTH_NTSC * HEIGHT_NTSC * 2;
	}
	else if (cur_std & V4L2_STD_PAL) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE))
			return FAILURE;
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_PAL))
			return FAILURE;
		file_size = WIDTH_PAL * HEIGHT_PAL * 2;
	}
	else if (cur_std & V4L2_STD_720P_60) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPONENT))
			return FAILURE;
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_720P))
			return FAILURE;
		file_size = WIDTH_720P * HEIGHT_720P * 2;
	}
	else if (cur_std & V4L2_STD_1080I_60) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPONENT))
			return FAILURE;
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_1080I))
			return FAILURE;
		file_size = WIDTH_1080I * HEIGHT_1080I * 2;
	} else {
		printf("Cannot display this standard\n");
		return FAILURE;
	}

	/* Setup VID1 output */
	if ((init_vid1_device(cur_std)) < 0) {
		printf("\nFailed to init vid1 window ");
		return FAILURE;
	}
	
	ret = start_loop();
	if (ret)
		printf("\tError: Video loopback had some errors\n");
	printf("Video loopback completed successfully\n");

	/*
	 * Once the streaming is done  stop the display
	 * hardware
	 */
	printf("8. Test STREAM_OFF - \n");
	ret = stop_display(fd_vid1);
	if (ret < 0) {
		printf("\tError: Could not stop display\n");
		return ret;
	}

	/* Release display channel */
	printf("9. Test buffer unmapping & closing of device - \n");
	release_display(&fd_vid1);

	ret = stop_capture(fdCapture);
	if (ret < 0)
		printf("Error in VIDIOC_STREAMOFF:capture\n");

	release_capture(&fdCapture);
	close(fd_osd0);
	printf("DONE ALL\n\n\n");

	DBGEXIT;
	return ret;
}

/*******************************************************************************
 *	Function will use the SysFS interface to change the output and mode
 */
static int change_sysfs_attrib(char *attribute, char *value)
{
	int sysfd = -1;
	char init_val[32];
	char attrib_tag[128];

	bzero(init_val, sizeof(init_val));
	strcpy(attrib_tag, "/sys/class/davinci_display/ch0/");
	strcat(attrib_tag, attribute);

	sysfd = open(attrib_tag, O_RDWR);
	if (!sysfd) {
		printf("Error: cannot open %d\n", sysfd);
		return FAILURE;
	}
	printf("%s was opened successfully\n", attrib_tag);

	read(sysfd, init_val, 32);
	lseek(sysfd, 0, SEEK_SET);
	printf("Current %s value is %s\n", attribute, init_val);

	write(sysfd, value, 1 + strlen(value));
	lseek(sysfd, 0, SEEK_SET);

	memset(init_val, '\0', 32);
	read(sysfd, init_val, 32);
	lseek(sysfd, 0, SEEK_SET);
	printf("Changed %s to %s\n", attribute, init_val);

	close(sysfd);
	return SUCCESS;
}

/*******************************************************************************
* menu function
*******************************************************************************/
void menu(void)
{
	printf("Usage: v4l2_userptr_loopback [ispmfclhbt?]\n");
	printf("Options:\n");
	printf("\t-i\tInput interface to use\n");
	printf("\t\t\t0 => Composite input [DEFAULT without -i]\n");
	printf("\t\t\t1 => S-Video input\n");
	printf("\t\t\t2 => Camera input\n");
	printf("\t-s\tStress test\n");
	printf("\t\t\t0 => Execute infinitely\n");
	printf("\t\t\t1 => Execute for 500 frames [DEFAULT without -s]\n");
	printf("\t-p\tPrint frame number and timestamp\n");
	printf("\t\t\t0 => Do not print [DEFAULT without -p]\n");
	printf("\t\t\t1 => Print frame number and timestamp\n");
	printf("\t-m\tSet input standard\n");
	printf("\t\t\t0 => NTSC with Composite/S-Video input\n");
	printf("\t\t\t     VGA with Camera input [DEFAULT without -m]\n");
	printf("\t\t\t1 => PAL with Composite/S-Video input\n");
	printf("\t-f\tField display mode (valid only for Composite input)\n");
	printf("\t\t\t0 => Display fields interlaced [DEFAULT without -f]\n");
	printf("\t\t\t1 => Display fields sequentially top and bottom\n");
	printf("\t-c\tCropping enable/disable\n");
	printf("\t\t\t0 => Disable cropping [DEFAULT without -c]\n");
	printf("\t\t\t1 => Enable cropping\n");
	printf("\t-l\tCropping width in decimal (valid only with -c 1)\n");
	printf("\t-h\tCropping height in decimal (valid only with -c 1)\n");
	printf("\t-b\tCropping left in decimal (valid only with -c 1)\n");
	printf("\t-t\tCropping top in decimal (valid only with -c 1)\n");
}


/******************************************************************************/
/* main function */
int main(int argc, char *argv[])
{
	int ret = 0, d, index;
	char shortoptions[] = "i:s:p:m:f:l:h:b:t:c:?";

	DBGENTER;

	/* by default use composite */
	for (;;) {
		d = getopt_long(argc, argv, shortoptions, (void *)NULL, &index);
		if (-1 == d)
			break;
		switch (d) {
		case 'f':
			field = atoi(optarg);
			break;
		case 'i':
			vpfe_input = atoi(optarg);
			break;
		case 'm':
			input_std = atoi(optarg);
			break;
		case 'p':
			printfn = atoi(optarg);
		case 's':
		case 'S':
			stress_test = atoi(optarg);
			break;
		case 'l':
		case 'L':
			cr_width = atoi(optarg);
			break;
		case 'h':
		case 'H':
			cr_height = atoi(optarg);
			break;
		case 'b':
		case 'B':
			cr_left = atoi(optarg);
			break;
		case 't':
		case 'T':
			cr_top = atoi(optarg);
			break;
		case 'c':
		case 'C':
			crop_en = atoi(optarg);
			break;
		default:
			menu();
			exit(1);
		}
	}

	if (en_capture_to_file) {
		fp_capture = fopen(FILE_CAPTURE, "wb");
		if (fp_capture == NULL) {
			printf("Unable to open file %s for capture\n", FILE_CAPTURE);
			exit(1);
		}
	}

	ret = vpbe_UE_1();
	DBGEXIT;
	return ret;
}
