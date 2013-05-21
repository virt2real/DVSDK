/*
 * aew_example
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
/*************************************************************************
 *	HEADER FILES
 */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <getopt.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>

/* Kernel header file, prefix path comes from makefile */
#include <media/davinci/dm355_aew.h>
#include <linux/videodev2.h>
#include <media/davinci/vpfe_capture.h>
#include <media/davinci/vpfe_types.h>
#include <media/davinci/dm355_ccdc.h>

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define DRIVER_NAME	"/dev/dm355_aew"
#define CAPTURE_DEVICE  "/dev/video0"
#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define WIDTH 	640
#define HEIGHT 	480
#define MIN_BUFFERS 2

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
int stress_test = 1;
static int quit = 0;
struct v4l2_cropcap cropcap;
static int fdCapture = -1;
struct buffer *buffers = NULL;
static int nBuffers = 0;
static int nWidthFinal = 0;
static int nHeightFinal = 0;
int fd, buff_size;
int fd_thread;
unsigned int size_buff_thread;

/* aew_Functional_TC2_1
 * Function to test AEW_S_PARAM ioctl
 */
int aew_Functional_TC2_1(void)
{
	struct aew_configuration *config;
	int result;
	int fd;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;
	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	/* Configure Window Parameters */
	config->window_config.width = 100;
	config->window_config.height = 2;
	config->window_config.hz_line_incr = 8;
	config->window_config.vt_line_incr = 8;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 31;
	config->window_config.vt_start = 12;
	config->window_config.hz_start = 128;
	/* Configure black window parameter */
	config->blackwindow_config.height = 4;
	config->blackwindow_config.vt_start = 11;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_ENABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;
	/* Call AEW_S_PARAM to set Parameters */
	printf("\n error no instance 1 %d", errno);
	result = ioctl(fd, AEW_S_PARAM, config);
	printf("\n IOCTL S_PARAM Return Value : %d", result);
	printf("\n error no %d", errno);
	ioctl(fd, AEW_DISABLE);
	if (config)
		free(config);
	/* Close Driver File */
	close(fd);
	return 0;
}

/* aew_Functional_TC2_2 */
/* Function to test AEW_G_PARAM ioctl*/
int aew_Functional_TC2_2(void)
{

	struct aew_configuration *config;
	struct aew_configuration *config1;
	int result;
	int fd;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;

	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config1 = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 100;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 8;
	config->window_config.vt_line_incr = 8;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 31;
	config->window_config.vt_start = 12;
	config->window_config.hz_start = 128;
	/* Configure black window parameter */
	config->blackwindow_config.height = 10;
	config->blackwindow_config.vt_start = 11;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_ENABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;
	printf("\n IOCTL G_PARAM  : %d", result);
	result = ioctl(fd, AEW_S_PARAM, config);
	printf("\n IOCTL S_PARAM  : %d", result);
	printf("\n Error no %d", errno);
	/* Call get parmaters to get parameters */
	result = ioctl(fd, AEW_G_PARAM, config1);
	printf("\n IOCTL G_PARAM  : %d", result);
	printf("\n Error no %d", errno);
	printf("\n******************************************");
	printf("\n Window Height : %d", config1->window_config.height);
	printf("\n Window Width : %d", config1->window_config.width);
	printf("\n Window Vertical Start : %d",
	       config1->window_config.vt_start);
	printf("\n Window Horizontal Start : %d",
	       config1->window_config.hz_start);
	printf("\n Window Vertical Count : %d", config1->window_config.vt_cnt);
	printf("\n Window Horizontal Count : %d",
	       config1->window_config.hz_cnt);
	printf("\n Window Vertical Line Increment: %d",
	       config1->window_config.vt_line_incr);
	printf("\n Window Horizontal Line Increment : %d",
	       config1->window_config.hz_line_incr);
	printf("\n Saturuation Limit : %d", config1->saturation_limit);

	ioctl(fd, AEW_DISABLE);
	if (config)
		free(config);
	if (config1)
		free(config1);
	/* Close Driver File */
	close(fd);
	return 0;
}

/* aew_Functional_TC2_3 */
/* Function to test AEW_ENABLE ioctl*/
int aew_Functional_TC2_3(void)
{
	struct aew_configuration *config;
	int result;
	int fd;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;

	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 100;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 8;
	config->window_config.vt_line_incr = 8;
	config->window_config.vt_cnt = 12;
	config->window_config.hz_cnt = 31;
	config->window_config.vt_start = 12;
	config->window_config.hz_start = 128;
	/* Configure black window parameter */
	config->blackwindow_config.height = 2;
	config->blackwindow_config.vt_start = 11;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_ENABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;

	/* Call AEW_S_PARAM to set Parameters */
	result = ioctl(fd, AEW_S_PARAM, config);

	printf("\n IOCTL S_PARAM  : %d", result);
	/* Call AEW_ENABLE to enable AEW Engine */
	result = ioctl(fd, AEW_ENABLE);
	printf("\n IOCTL AEW_ENABLE  : %d", result);
	/*ioctl(fd,AEW_DISABLE); */
	if (config)
		free(config);
	/* Close Driver File */
	close(fd);
	return 0;
}

/* aew_Functional_TC2_5 */
/* Function to test invalid IOCTL*/
int aew_Functional_TC2_5(void)
{
	int fd, result;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;
	}
	result = ioctl(fd, 1232);
	/* Close Driver File */
	close(fd);
	printf("\n IOCTL 1232  : %d", result);
	printf("\n Error no %d", errno);
	return 0;
}

/* aew_Functional_TC2_5 */
/* Function to test AEW_DISABLE IOCTL*/
int aew_Functional_TC2_4(void)
{
	int fd, result;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;
	}
	result = ioctl(fd, AEW_DISABLE);
	/* Close Driver File */
	close(fd);
	printf("\n Error no %d", errno);
	return 0;
}

/* aew_Functional_TC2_6 */
/* Function to test AEW_ENABLE ioctl without configuring the hardware .
Driver should return error */
int aew_Functional_TC2_6(void)
{
	int fd, result;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;

	}
	/* Call AEW_ENABLE to enable AEW Engine */
	ioctl(fd, AEW_ENABLE);
	printf("\n IOCTL ENABLE  : %d", result);
	/* Close Driver File */
	close(fd);
	return 0;
}

/* aew_Functional_TC3_1 */
/* Function to pass invalid parameter in AEW_S_PARAM ioctl.
Driver should return error code .*/
int aew_Functional_TC3_1(void)
{
	struct aew_configuration *config;
	int result;
	int fd;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;

	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 1000;
	config->window_config.height = 10;
	config->window_config.hz_line_incr = 8;
	config->window_config.vt_line_incr = 8;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 31;
	config->window_config.vt_start = 12;
	config->window_config.hz_start = 128;
	/* Configure black window parameter */
	config->blackwindow_config.height = 10;
	config->blackwindow_config.vt_start = 11;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;

	/* Call AEW_S_PARAM to set Parameters */
	result = ioctl(fd, AEW_S_PARAM, config);
	printf("\n IOCTL S_PARAM Return Value : %d", result);
	printf("\n error no %d", errno);
	ioctl(fd, AEW_DISABLE);
	if (config)
		free(config);
	/* Close Driver File */
	close(fd);
	return 0;

}
static int InitCaptureDevice(void)
{
	/*input-0 is selected by default, so no need to set it */
	if ((fdCapture = open(CAPTURE_DEVICE, O_RDWR | O_NONBLOCK, 0)) <= -1) {

		printf("InitDevice:open::\n");
		return -1;
	}
#if 0
	/*is capture supported? */
	if (-1 == ioctl(fdCapture, VIDIOC_QUERYCAP, &cap)) {
		printf("InitDevice:ioctl:VIDIOC_QUERYCAP:\n");
		return -1;
	}

	if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
		printf("InitDevice:capture is not supported on:%s\n",
		       CAPTURE_DEVICE);
		return -1;
	}

	/*is MMAP-IO supported? */
	if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
		printf
		    ("InitDevice:IO method MMAP is not supported on:%s\n",
		     CAPTURE_DEVICE);
		return -1;
	}

	/*select cropping as deault rectangle */
	cropcap.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	if (-1 == ioctl(fdCapture, VIDIOC_CROPCAP, &cropcap)) {
		printf("InitDevice:ioctl:VIDIOC_CROPCAP\n");
		/*ignore error */
	}

	printf
	    ("Default crop capbility bounds - %d %d %d %d ; default - %d %d %d %d \n",
	     cropcap.bounds.left, cropcap.bounds.top, cropcap.bounds.width,
	     cropcap.bounds.height, cropcap.defrect.left,
	     cropcap.defrect.top, cropcap.defrect.width,
	     cropcap.defrect.height);
#endif
	return 0;
}

void *buffer_stat;
int startLoopCnt = 10;

int StartLoop(void)
{
	struct v4l2_buffer buf;
	unsigned short int *k11;
	int result;
	int count = 0;
	FILE *fp1;
	fp1 = fopen("aew_samp.txt", "w");
	printf("\n Buffer size s %d", buff_size);
	if (buff_size < 0) {
		printf("\n error in StartLoop");
		printf("\n Buffer size is invalid");
		return -1;
	}

	printf("\n Allocating the buffer");
	buffer_stat = (void *)malloc(buff_size);
	if (buffer_stat == NULL) {
		printf("\n error in StartLoop");
		printf("\n Alloction in failure");
		return -1;
	}
	while (!quit) {
		fd_set fds;
		struct timeval tv;
		int r;

		if (stress_test) {
			startLoopCnt--;
			if (startLoopCnt == 0) {
				/*printf("\nexit from while\n");*/
				startLoopCnt = 10;
				break;
			}
		}
		FD_ZERO(&fds);
		FD_SET(fdCapture, &fds);

		/* Timeout. */
		tv.tv_sec = 2;
		tv.tv_usec = 0;

		r = select(fdCapture + 1, &fds, NULL, NULL, &tv);

		if (-1 == r) {
			if (EINTR == errno)
				continue;

			printf("StartCameraCaputre:select\n");
			return -1;
		}

		if (0 == r) {
			continue;
		}

		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		/*determine ready buffer */

		if (-1 == ioctl(fdCapture, VIDIOC_DQBUF, &buf)) {
			printf("\n error in StartLoop");
			printf("StartCameraCaputre:ioctl:VIDIOC_DQBUF\n");
			return -1;
		}

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			printf("\n error in StartLoop");
			printf("StartCameraCaputre:ioctl:VIDIOC_QBUF\n");
			return -1;
		}

	}

	/* Enable the engine */
	if (ioctl(fd, AEW_ENABLE) < 0) {
		printf("\n error in StartLoop");
		printf("ioctl AEW_ENABLE fail. \n");
		return -1;
	}

	result = read(fd, (void *)buffer_stat, buff_size);
	printf("\n RESULT OF READ %d", result);
	if (result < 0) {
		printf("\n error in StartLoop");
		printf("\n Read Failed");
		return -1;
	}
	if (result > 0) {
		printf("\n Output File : af_samp.txt");

		k11 = (unsigned short int *)buffer_stat;

		for (count = 0; count < buff_size / 2; count++) {
			fprintf(fp1, "\n%d", (unsigned short int)k11[count]);
			/*printf("\n@%d@",(unsigned short int)k11[count]);*/
		}

	} else {
		printf("\n error in StartLoop");
		printf("\nNOT ABLE TO READ");

	}
	return 0;

}
int StartLoop_stress(void)
{
	struct v4l2_buffer buf;

	if (buff_size < 0) {
		printf("\n error in StartLoop");
		printf("\n Buffer size is invalid");
		return -1;
	}

	printf("\n Allocating the buffer");

	if (buffer_stat == NULL) {
		printf("\n error in StartLoop");
		printf("\n Alloction in failure");
		return -1;
	}
	while (!quit) {
		fd_set fds;
		struct timeval tv;
		int r;

		if (stress_test) {
			startLoopCnt--;
			if (startLoopCnt == 0) {
				printf("\nexit from while\n");
				startLoopCnt = 10;
				break;
			}
		}
		FD_ZERO(&fds);
		FD_SET(fdCapture, &fds);

		/* Timeout. */
		tv.tv_sec = 2;
		tv.tv_usec = 0;

		r = select(fdCapture + 1, &fds, NULL, NULL, &tv);

		if (-1 == r) {
			if (EINTR == errno)
				continue;

			printf("StartCameraCaputre:select\n");
			return -1;
		}

		if (0 == r) {
			continue;
		}

		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		/*determine ready buffer */

		if (-1 == ioctl(fdCapture, VIDIOC_DQBUF, &buf)) {
			printf("\n error in StartLoop");
			printf("StartCameraCaputre:ioctl:VIDIOC_DQBUF\n");
			return -1;
		}

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			printf("\n error in StartLoop");
			printf("StartCameraCaputre:ioctl:VIDIOC_QBUF\n");
			return -1;
		}

	}
	return 0;
}
static int SetDataFormat(void)
{
	v4l2_std_id prev_std, cur_std;
	struct v4l2_format fmt;
	struct v4l2_input input;
	int temp_input;
	struct v4l2_standard standard;
	int ret;
	unsigned int min;

	// first set the input
	input.type = V4L2_INPUT_TYPE_CAMERA;
	input.index = 0;
  	while ((ret = ioctl(fdCapture,VIDIOC_ENUMINPUT, &input) == 0)) { 
		printf("input.name = %s\n", input.name);
		if (!strcmp(input.name, "Camera"))
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
	while (0 == ioctl (fdCapture, VIDIOC_ENUMSTD, &standard)) {
		printf("standard.index = %d\n", standard.index);	
		printf("standard.id = %llx\n", standard.id);	
		printf("standard.frameperiod.numerator = %d\n", standard.frameperiod.numerator);	
		printf("standard.frameperiod.denominator = %d\n", standard.frameperiod.denominator);	
		printf("standard.framelines = %d\n", standard.framelines);	
		standard.index++;
	}

	printf("SetDataFormat:setting data format\n");
	printf("SetDataFormat:requesting width:%d height:%d\n", WIDTH, HEIGHT);
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = WIDTH;	/* SSK Buffer Size */
	fmt.fmt.pix.height = HEIGHT;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_SBGGR8;
	/* the field can be either interlaced together or
	   separated in a top, bottom fashion */
	fmt.fmt.pix.field = V4L2_FIELD_NONE;
	if (-1 == ioctl(fdCapture, VIDIOC_S_FMT, &fmt)) {
		printf("SetDataFormat:ioctl:VIDIOC_S_FMT\n");
	}

	if (-1 == ioctl(fdCapture, VIDIOC_G_FMT, &fmt)) {
		printf("SetDataFormat:ioctl:VIDIOC_QUERYSTD:\n");
	}

	nWidthFinal = fmt.fmt.pix.width;
	nHeightFinal = fmt.fmt.pix.height;

	printf("SetDataFormat:finally negotiated width:%d height:%d\n",
	       nWidthFinal, nHeightFinal);

	/*checking what is finally negotiated */
	min = fmt.fmt.pix.width * 2;
	if (fmt.fmt.pix.bytesperline < min) {
		printf
		    ("SetDataFormat:driver reports bytes_per_line:%d(bug)\n",
		     fmt.fmt.pix.bytesperline);
		/*correct it */
		fmt.fmt.pix.bytesperline = min;
	}

	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if (fmt.fmt.pix.sizeimage < min) {
		printf("SetDataFormat:driver reports size:%d(bug)\n",
		       fmt.fmt.pix.sizeimage);

		/*correct it */
		fmt.fmt.pix.sizeimage = min;
	}

	printf("SetDataFormat:Finally negitaited width:%d height:%d\n",
	       nWidthFinal, nHeightFinal);

	return 0;
}

static int InitCaptureBuffers(void)
{
	struct v4l2_requestbuffers req;
	int nIndex = 0;

	CLEAR(req);
	req.count = MIN_BUFFERS;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_MMAP;

	if (-1 == ioctl(fdCapture, VIDIOC_REQBUFS, &req)) {
		printf("InitCaptureBuffers:ioctl:VIDIOC_REQBUFS\n");
		return -1;
	}

	if (req.count < MIN_BUFFERS) {
		printf
		    ("InitCaptureBuffers only:%d buffers avilable, can't proceed\n",
		     req.count);
		return -1;
	}

	nBuffers = req.count;
	printf("device buffers:%d\n", req.count);
	buffers = (struct buffer *)calloc(req.count, sizeof(struct buffer));
	if (!buffers) {
		printf("InitCaptureBuffers:calloc:\n");
		return -1;
	}

	for (nIndex = 0; nIndex < req.count; ++nIndex) {

		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		buf.index = nIndex;

		if (-1 == ioctl(fdCapture, VIDIOC_QUERYBUF, &buf)) {
			printf("InitCaptureBuffers:ioctl:VIDIOC_QUERYBUF:\n");
			return -1;
		}

		buffers[nIndex].length = buf.length;
		buffers[nIndex].start =
		    mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
			 MAP_SHARED, fdCapture, buf.m.offset);

		printf("buffer:%d phy:%x mmap:%p length:%d\n", buf.index,
		       buf.m.offset, buffers[nIndex].start, buf.length);

		if (MAP_FAILED == buffers[nIndex].start) {
			printf("InitCaptureBuffers:mmap:\n");
			return -1;
		}
	}

	return 0;
}

static int StartStreaming(void)
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

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			printf("StartStreaming:ioctl:VIDIOC_QBUF:\n");
		}
		printf("Queing buffer:%d done \n", i);
	}
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fdCapture, VIDIOC_STREAMON, &type)) {
		printf("StartStreaming:ioctl:VIDIOC_STREAMON:\n");
	}

	return 0;
}

int end_capture()
{
	int type = V4L2_BUF_TYPE_VIDEO_CAPTURE;

	/* end capturing by calling STREAMOFF ioctl */
	if (-1 == ioctl(fdCapture, VIDIOC_STREAMOFF, &type)) {
		/*perror("StopStreaming:ioctl:VIDIOC_STREAMOFF");*/
	}

	close(fdCapture);
	return 0;
}

int aew_Functional_TC6_2(void)
{
	struct aew_configuration *config;
	int result = 0;

	/*Open AEW driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AEW Device\n");
		return -1;
	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 8;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	config->blackwindow_config.height = 8;
	config->blackwindow_config.vt_start = 2;

	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;

	/* Set Saturation limit */
	config->saturation_limit = 255;

	printf("\n Before SEt Params");
	/* Call AEW_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AEW_S_PARAM, config);
	if (buff_size < 0) {
		printf("\n error in aew_Functional_TC6_2");
		printf("ioctl AEW_S_PARAM fail \n");
		return -1;
	}

	result = StartLoop();
	if (result < 0) {
		printf("\n error in streaming");
		return -1;
	}

	/* Disable the engine */
	if (ioctl(fd, AEW_DISABLE) < 0) {
		printf("ioctl AEW_DISABLE fail. \n");
		printf("\n error in aew_Functional_TC6_2");
	}
	return 0;

}

int aew_Functional_TC6_1()
{
	struct aew_configuration *config;
	int result = 0;

	/*Open AEW driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AEW Device\n");
		return -1;
	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 8;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	config->blackwindow_config.height = 8;
	config->blackwindow_config.vt_start = 2;

	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_ENABLE;

	/* Set Saturation limit */
	config->saturation_limit = 255;

	printf("\n Before SEt Params");
	/* Call AEW_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AEW_S_PARAM, config);
	if (buff_size < 0) {
		printf("\n error in aew_Functional_TC6_2");
		printf("ioctl AEW_S_PARAM fail \n");
		return -1;
	}
	result = StartLoop();
	if (result < 0) {
		printf("\n Error in start loop fucntion");

		return -1;
	}
	/* Disable the engine */
	if (ioctl(fd, AEW_DISABLE) < 0) {
		printf("\n error in aew_Functional_TC6_2");
		printf("ioctl AEW_DISABLE fail. \n");
		return -1;
	}
	return 0;
}

int aew_Stress()
{

	struct aew_configuration *config;
	int result = 0;
	int stress_count = 0;

	/*Open AEW driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AEW Device\n");
		return -1;
	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 8;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	config->blackwindow_config.height = 8;
	config->blackwindow_config.vt_start = 2;

	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;

	/* Set Saturation limit */
	config->saturation_limit = 255;

	printf("\n Before SEt Params");
	/* Call AEW_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AEW_S_PARAM, config);
	if (buff_size < 0) {
		printf("\n error in aew_Functional_TC6_2");
		printf("ioctl AEW_S_PARAM fail \n");
		return -1;
	}
	buffer_stat = (void *)malloc(buff_size);
	result = StartLoop_stress();
	if (result < 0) {
		printf("\n Error in start loop fucntion");

		return -1;
	}
	/* Enable the engine */
	if (ioctl(fd, AEW_ENABLE) < 0) {
		printf("\n error in StartLoop");
		printf("ioctl AEW_ENABLE fail. \n");
		return -1;
	}
	while (1) {
		stress_count++;
		result = read(fd, (void *)buffer_stat, buff_size);
		printf("\n cnt %d", stress_count);
		if (result < 0) {
			printf("\n error in StartLoop");
			printf("\n Read Failed");
			return -1;
		}
	}
	/* Disable the engine */
	if (ioctl(fd, AEW_DISABLE) < 0) {
		printf("\n error in aew_Functional_TC6_2");
		printf("ioctl AEW_DISABLE fail. \n");
		return -1;
	}
	return 0;
}
int aew_Functional_TC5_1(void)
{
	struct aew_configuration *config;
	int result;
	void *buffer_stat;
	int fd;
	unsigned int size_buff;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;

	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 16;
	config->window_config.hz_cnt = 32;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	/* Configure black window parameter */
	config->blackwindow_config.height = 4;
	config->blackwindow_config.vt_start = 100;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;
	/* Call AEW_S_PARAM to set Parameters */
	result = ioctl(fd, AEW_S_PARAM, config);
	/* Call AEW_ENABLE to enable AEW Engine */
	ioctl(fd, AEW_ENABLE);
	size_buff =
	    (config->window_config.hz_cnt) * (config->window_config.vt_cnt) *
	    16;

	buffer_stat = NULL;
	buffer_stat = (unsigned short int *)malloc(size_buff);
	if (buffer_stat < 0) {
		perror("");
	}
	result = read(fd, (unsigned short int *)buffer_stat, size_buff);
	if (result < 0)
		printf("\n Error in reading");
	ioctl(fd, AEW_DISABLE);
	if (config)
		free(config);
	if (buffer_stat)
		free(buffer_stat);
	/* Close Driver File */
	close(fd);
	end_capture();
	return 0;

}

int timeval_subtract(struct timeval *result, struct timeval *x,
		     struct timeval *y)
{
	/* Perform the carry for the later subtraction by updating y. */
	if (x->tv_usec < y->tv_usec) {
		int nsec = (y->tv_usec - x->tv_usec) / 1000000 + 1;
		y->tv_usec -= 1000000 * nsec;
		y->tv_sec += nsec;
	}
	if (x->tv_usec - y->tv_usec > 1000000) {
		int nsec = (x->tv_usec - y->tv_usec) / 1000000;
		y->tv_usec += 1000000 * nsec;
		y->tv_sec -= nsec;
	}

	/* Compute the time remaining to wait.
	   tv_usec is certainly positive. */
	result->tv_sec = x->tv_sec - y->tv_sec;
	result->tv_usec = x->tv_usec - y->tv_usec;

	/* Return 1 if result is negative. */
	return x->tv_sec < y->tv_sec;
}
int StartLoop_thread(void)
{
	struct v4l2_buffer buf;
	
	while (!quit) {
		fd_set fds;
		struct timeval tv;
		int r;

		if (stress_test) {
			startLoopCnt--;
			if (startLoopCnt == 0) {
				printf("\nexit from while\n");
				startLoopCnt = 10;
				break;
			}
		}
		FD_ZERO(&fds);
		FD_SET(fdCapture, &fds);

		/* Timeout. */
		tv.tv_sec = 2;
		tv.tv_usec = 0;

		r = select(fdCapture + 1, &fds, NULL, NULL, &tv);

		if (-1 == r) {
			if (EINTR == errno)
				continue;

			printf("StartCameraCaputre:select\n");
			return -1;
		}

		if (0 == r) {
			continue;
		}

		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_MMAP;
		/*determine ready buffer */

		if (-1 == ioctl(fdCapture, VIDIOC_DQBUF, &buf)) {
			printf("StartCameraCaputre:ioctl:VIDIOC_DQBUF\n");
			return -1;
		}

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			printf("StartCameraCaputre:ioctl:VIDIOC_QBUF\n");
		}

	}

	return 0;
}

/*
=====================aew_Functional_TC5_3===========================
*/
/*Application will issue two read calls.
 Second read call should be blocked until new statistics are available.
This can be verified by measuring time taken by read call*/
int aew_Functional_TC5_3(void)
{
	struct aew_configuration *config;
	int result;
	short int *k11;
	int count;
	struct timeval ptime, ntime, resulttime;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening device file");
		return -1;

	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 8;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	/* Configure black window parameter */
	config->blackwindow_config.height = 4;
	config->blackwindow_config.vt_start = 100;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;

	/* Call AEW_S_PARAM to set Parameters */
	buff_size = ioctl(fd, AEW_S_PARAM, config);
	/* Call AEW_ENABLE to enable AEW Engine */

	if (buff_size < 0) {
		printf("\n Error in setting Paramters");
		return -1;
	}

	printf("\n SIze _ buffer  %d ", buff_size);

	if (buffer_stat < 0) {
		perror("Error in tc5_3");
		return -1;
	}

	result = StartLoop();
	if (result < 0) {
		printf("\n error in streaming");
		return -1;
	}

	gettimeofday(&ptime, NULL);

	result = read(fd, buffer_stat, buff_size);

	gettimeofday(&ntime, NULL);
	if (result <= 0) {
		printf("result = %d\n", result);
		if (result < 0)
			perror("error\n");
	}
	timeval_subtract(&resulttime, &ntime, &ptime);

	printf("Difference is %d sec, %d msec\n",
	       resulttime.tv_sec, resulttime.tv_usec / 1000);

	gettimeofday(&ptime, NULL);
	result = read(fd, buffer_stat, buff_size);
	gettimeofday(&ntime, NULL);
	if (result <= 0) {
		printf("result = %d\n", result);
		if (result < 0)
			perror("error\n");
	}
	timeval_subtract(&resulttime, &ntime, &ptime);

	printf("Difference is %d sec, %d msec\n",
	       resulttime.tv_sec, resulttime.tv_usec / 1000);

	gettimeofday(&ptime, NULL);
	result = read(fd, buffer_stat, buff_size);
	gettimeofday(&ntime, NULL);
	if (result <= 0) {
		printf("result = %d\n", result);
		if (result < 0)
			perror("error\n");
	}
	timeval_subtract(&resulttime, &ntime, &ptime);

	printf("Difference is %d sec, %d msec\n",
	       resulttime.tv_sec, resulttime.tv_usec / 1000);

	if (result >= 0) {

		k11 = (short int *)buffer_stat;
#if 0
		for (count = 0; count < buff_size / 2; count++) {
			fprintf(fp1, "\n%d", (short int)k11[count]);
			printf("\n@%d@", (short int)k11[count]);
		}
#endif
	}

	ioctl(fd, AEW_DISABLE);

	return 0;

}
int aew_Performance_TC1_1(void)
{
	struct aew_configuration *config;
	int result = 0;

	/*Open AEW driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AEW Device\n");
		return -1;
	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	
	config->window_config.width = 8;
	config->window_config.height = 2;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 72;
	config->window_config.hz_cnt = 36;
	config->window_config.vt_start = 2;
	config->window_config.hz_start = 4;
	config->blackwindow_config.height = 2;
	config->blackwindow_config.vt_start = 4;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;

#if 0
	/* Minimum Configuration */
	config->window_config.width = 32;
	config->window_config.height = 32;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 4;
	config->window_config.hz_cnt = 4;
	config->window_config.vt_start = 6;
	config->window_config.hz_start = 6;
	config->blackwindow_config.height = 4;
	config->blackwindow_config.vt_start = 6;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;
#endif
#if 0

	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 30;
	config->window_config.hz_cnt = 15;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	config->blackwindow_config.height = 8;
	config->blackwindow_config.vt_start = 2;
	config->alaw_enable = H3A_AEW_DISABLE;
	config->saturation_limit = 100;

	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;

	/* Set Saturation limit */
	config->saturation_limit = 255;

#endif
	printf("\n Before SEt Params");
	/* Call AEW_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AEW_S_PARAM, config);
	if (buff_size < 0) {
		printf("ioctl AEW_S_PARAM fail \n");
		if (fd)
			close(fd);
		return -1;
	}

	result = StartLoop();
	if (result < 0) {
		printf("\n error in streaming");
		return -1;
	}

	/* Disable the engine */
	if (ioctl(fd, AEW_DISABLE) < 0) {
		printf("ioctl AEW_DISABLE fail. \n");
	}
	return 0;

}

void *aew_TC5_2_Test(int id);
/*
=====================aew_Functional_TC5_2===========================
*/
/* Create two threads in the application
.Driver should return error to the second thread.*/

int aew_Functional_TC5_2(void)
{
	pthread_t ch1_thread, ch2_thread;
	struct aew_configuration *config;
	int result, status;
	fd_thread = open(DRIVER_NAME, O_RDWR);
	if (fd_thread < 0) {
		printf("\n Error in opening device file");
		return -1;
	}
	/* Allocate Memory For Configuration Structure */
	config = (struct aew_configuration *)
	    malloc(sizeof(struct aew_configuration));
	config->window_config.width = 8;
	config->window_config.height = 8;
	config->window_config.hz_line_incr = 2;
	config->window_config.vt_line_incr = 2;
	config->window_config.vt_cnt = 8;
	config->window_config.hz_cnt = 8;
	config->window_config.vt_start = 4;
	config->window_config.hz_start = 4;
	/* Configure black window parameter */
	config->blackwindow_config.height = 4;
	config->blackwindow_config.vt_start = 100;
	/* Enable ALaw */
	config->alaw_enable = H3A_AEW_DISABLE;
	/* Set Saturation limit */
	config->saturation_limit = 100;
	/* Call S_PARAM to set parameters */
	size_buff_thread = ioctl(fd_thread, AEW_S_PARAM, config);
	/* Call AEW_ENABLE to enable AEW Engine */

	result = StartLoop_thread();

	printf("\n enabling the engine");
	ioctl(fd_thread, AEW_ENABLE);
	printf("\n BUFFER SIZE IS %d", size_buff_thread);
	if (result < 0) {
		printf("\n Error in streaming");
		status = ioctl(fd_thread, AEW_DISABLE);
		close(fd);
		return -1;
	}
	printf("\nbefore thread ");
	pthread_create(&ch2_thread, NULL, (void *)aew_TC5_2_Test, (void *)1);
	pthread_create(&ch1_thread, NULL, (void *)aew_TC5_2_Test, (void *)2);

	printf("\after thread ");
	printf("\n @@ JOININGIN THE THREAD ");
	pthread_join(ch1_thread, (void **)0);
	pthread_join(ch2_thread, (void **)0);
	status = ioctl(fd_thread, AEW_DISABLE);
	if (status < 0)
		perror("");

	if (config)
		free(config);
	close(fd_thread);
	end_capture();
	printf("\n exiting from the main");
	exit(0);
}

int aew_Functional_TC7_1(void)
{

	int fd, fd1;
	/* Open AEW Driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening file");
		return -1;
	}
	fd1 = open(DRIVER_NAME, O_RDWR);
	if (fd1 < 0) {
		printf("\n Error in opening file");
		return -1;
	}
	close(fd);
	close(fd1);
	return 0;
}

void aew_DumptoFile(void *buffer, unsigned int buff_size, char *filename)
{
	int count;
	FILE *fp1;
	unsigned short int *temp;
	temp = (unsigned short int *)buffer;
	fp1 = fopen(filename, "w");
	for (count = 0; count < (buff_size / 2); count++) {
		/*printf("\n Data %d",temp[count]);*/
		fprintf(fp1, "\n Data : %d", (unsigned short int)temp[count]);
	}
}

/*
=====================aew_Functional_TC5_2_Test===========================
*/
/* Function us called by thread*/

void *aew_TC5_2_Test(int id)
{
	int result;
	void *buffer_stat1;
	buffer_stat1 = (void *)malloc(size_buff_thread);
	printf("HELLO I M THREAD %d\n", id);
	/* Open AEW Driver */
	printf("\n SIZE OF BUFFER IS %d", size_buff_thread);

	if (size_buff_thread > 0)
		buffer_stat1 = malloc(size_buff_thread);
	result = read(fd_thread, (short int *)buffer_stat1, size_buff_thread);
	printf("\n RESULT of READ IS %d", result);
#if 1
	if (result > 0) {
		printf("\n HI i m printing for thread %d", id);
		if (id == 1) {
			aew_DumptoFile(buffer_stat1, size_buff_thread,
				       "tc5_2_1stthread.txt");
		} else {
			aew_DumptoFile(buffer_stat1, size_buff_thread,
				       "tc5_2_2ndthread.txt");
		}
	}
#endif
	if (buffer_stat1)
		free(buffer_stat1);
	return 0;

}

void usage(void)
{
	printf("\n test_af -t type of test case F,I,S,P \
	\n-c test case number \n-n number in test case\n");
	printf("\n F-functional Test case");
	printf("\n S- Stress Test case");
	printf("\n P-Performance Test case");

}
int main(int argc, char *argv[])
{
	char type;
	char shortoptions[] = "t:c:n:";
	int testcase, no, index, c;
	int test_val = 0;

	test_val = InitCaptureDevice();

	test_val = SetDataFormat();
	if (test_val < 0) {
		printf("\n Error in SetDataFormat");
		return -1;
	}
	test_val = InitCaptureBuffers();
	if (test_val < 0) {
		printf("\n Error in InitCaptureBuffers");
		return -1;
	}
	test_val = StartStreaming();
	if (test_val < 0) {
		printf("\n Error in StartStreaming");
		return -1;
	}

	for (;;) {
		c = getopt_long(argc, argv, shortoptions, NULL, &index);

		if (c == -1)
			break;

		switch (c) {
		case 0:
			break;
		case 't':
		case 'T':
			type = optarg[0];
			break;
		case 'c':
		case 'C':
			testcase = atoi(optarg);
			break;
		case 'n':
		case 'N':
			no = atoi(optarg);
			break;
		default:
			usage();
			exit(1);
		}
	}
	printf("type = %c, test case = %d, number = %d\n", type, testcase, no);

	switch (type) {
	case 'f':
	case 'F':
		printf("f");
		switch (testcase) {
		case 2:
			switch (no) {
			case 1:
				aew_Functional_TC2_1();
				break;
			case 2:
				aew_Functional_TC2_2();
				break;
			case 3:
				aew_Functional_TC2_3();
				break;
			case 4:

				aew_Functional_TC2_4();
				break;
			case 5:

				aew_Functional_TC2_5();
				break;
			case 6:
				aew_Functional_TC2_6();
				break;
			}
			break;
		case 3:
			switch (no) {
			case 1:
				aew_Functional_TC3_1();
				break;
			default:
				usage();
				exit(1);
			}
			break;
		case 4:
			aew_Functional_TC6_2();
			break;
		case 5:
			switch (no) {
			case 1:

				aew_Functional_TC5_1();
				break;
			case 2:

				aew_Functional_TC5_2();
				break;
			case 3:

				aew_Functional_TC5_3();
				break;
			default:
				usage();
				exit(1);
			}
			break;
		case 6:
			switch (no) {
			case 1:
				aew_Functional_TC6_1();
				break;
			case 2:
				aew_Functional_TC6_2();
				break;
			default:
				usage();
				exit(1);
			}
			break;
		case 7:
			aew_Functional_TC7_1();
			break;
		default:
			usage();
			exit(1);
		}
	case 'i':
	case 'I':
		break;
	case 's':
	case 'S':
		aew_Stress();

		break;
	case 'p':
	case 'P':

		aew_Performance_TC1_1();
		break;
	default:
		usage();
		exit(1);
	}

	end_capture();

	/* Close Driver */
	if (fd)
		close(fd);
	if (buffer_stat)
		free(buffer_stat);
	return 0;
}
