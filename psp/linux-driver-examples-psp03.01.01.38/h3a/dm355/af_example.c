/*
 * af_example
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
#include <media/davinci/dm355_af.h>
#include <linux/videodev2.h>
#include <media/davinci/vpfe_capture.h>
#include <media/davinci/vpfe_types.h>
#include <media/davinci/dm355_ccdc.h>

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define DRIVER_NAME	"/dev/dm355_af"
#define CAPTURE_DEVICE  "/dev/video0"
#define CLEAR(x) memset (&(x), 0, sizeof (x))
#define WIDTH 	640 //1224
#define HEIGHT 	480 //456
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
void *buffer_stat;
int startLoopCnt = 10;

/* af_Functional_TC2_1
 * Function to test AF_S_PARAM ioctl
 */
int af_Functional_TC2_1(void)
{
	struct af_configuration *config;
	int fd, result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}
	/* Allocate memory for Configuration Structure */
	config = (struct af_configuration *)
	    malloc(sizeof(struct af_configuration));
	/* Enable Alaw */
	config->alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config->hmf_config.enable = H3A_AF_DISABLE;
	config->hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config->iir_config.hz_start_pos = 2;
	config->paxel_config.height = 4;
	config->paxel_config.width = 8;
	config->paxel_config.line_incr = 2;
	config->paxel_config.vt_start = 4;
	config->paxel_config.hz_start = 4;
	config->paxel_config.hz_cnt = 16;
	config->paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config->mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config->iir_config.coeff_set0[index] = iir0[index];
		config->iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config->rgb_pos = GR_BG_BAYER;
	/* Call AF_S_PARAM to do the configuration */
	result = ioctl(fd, AF_S_PARAM, config);
	printf("No of bytes that are required by the application  %d", result);
	/* Disable the engine */
	ioctl(fd, AF_DISABLE);
	if (config)
		free(config);
	return 0;

}

/* af_Functional_TC2_2
 * Function to test AF_G_PARAM ioctl
 */
int af_Functional_TC2_2(void)
{
	struct af_configuration *config, *config1;
	int index = 0;
	int fd, result;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}

	/* Allocate memory for Configuration Structure */
	config = (struct af_configuration *)
	    malloc(sizeof(struct af_configuration));
	/* Enable Alaw */
	config->alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config->hmf_config.enable = H3A_AF_DISABLE;
	config->hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config->iir_config.hz_start_pos = 2;
	config->paxel_config.height = 4;
	config->paxel_config.width = 8;
	config->paxel_config.line_incr = 2;
	config->paxel_config.vt_start = 4;
	config->paxel_config.hz_start = 4;
	config->paxel_config.hz_cnt = 16;
	config->paxel_config.vt_cnt = 4;
	/* Set Accumulator mode */
	config->mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config->iir_config.coeff_set0[index] = iir0[index];
		config->iir_config.coeff_set1[index] = iir1[index];
	}
	/* Allocate memory for Configuration Structure */
	config1 = (struct af_configuration *)
	    malloc(sizeof(struct af_configuration));
	/* Set RGBPOSITION */
	config->rgb_pos = GR_BG_BAYER;
	/* Call AF_S_PARAM to do the configuration */
	result = ioctl(fd, AF_S_PARAM, config);
	printf("\nNo of bytes that are required by the applicatiob  %d",
	       result);
	result = ioctl(fd, AF_G_PARAM, config1);
	printf("\n ************************Paxel Paramters***********");
	printf("\nPaxel Height : %d", config1->paxel_config.height);
	printf("\nPaxel Width : %d", config1->paxel_config.width);
	printf("\nPaxel Horizontal Start : %d", config1->paxel_config.hz_start);
	printf("\nPaxel Vertical Start : %d", config1->paxel_config.vt_start);
	printf("\nPaxel Line Increment : %d", config1->paxel_config.line_incr);
	printf("\n *****************COEFFICIENT SET0*********");
	for (index = 0; index < 11; index++) {
		printf("\n IIR Coefficient %d : %d", index + 1,
		       config1->iir_config.coeff_set0[index]);

	}
	printf("\n *****************COEFFICIENT SET1*********");
	for (index = 0; index < 11; index++) {
		printf("\n IIR Coefficient %d : %d", index + 1,
		       config1->iir_config.coeff_set1[index]);
	}
	printf("\n IIRSH : %d", config1->iir_config.hz_start_pos);
	printf("\n *********************HMF CONFIGURATION ******");
	printf("\n HMF LAW : %d", config1->hmf_config.enable);
	printf("\n HMF THRESHOLD : %d", config1->hmf_config.threshold);
	printf("\n ************************PCR CONTENTS ********");
	printf("\n ACCUMULATORMODE\tALAW\tRGBOS");
	printf("\n%d\t\t%d\t\t%d", config->mode, config->alaw_enable,
	       config->rgb_pos);
	printf("\nNo of bytes that are required by the applicatiob  %d",
	       result);
	/* Disable the engine */
	ioctl(fd, AF_DISABLE);
	if (config)
		free(config);

	return 0;

}

/* af_Functional_TC2_3
 *Function to test AF_ENABLE ioctl
 */
int af_Functional_TC2_3(void)
{
	struct af_configuration *config;
	int index = 0, fd, result;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}

	/* Allocate memory for Configuration Structure */
	config = (struct af_configuration *)
	    malloc(sizeof(struct af_configuration));
	/* Disable Alaw */
	config->alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config->hmf_config.enable = H3A_AF_DISABLE;
	config->hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config->iir_config.hz_start_pos = 2;
	config->paxel_config.height = 8;
	config->paxel_config.width = 8;
	config->paxel_config.line_incr = 2;
	config->paxel_config.vt_start = 4;
	config->paxel_config.hz_start = 4;
	config->paxel_config.hz_cnt = 8;
	config->paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config->mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config->iir_config.coeff_set0[index] = iir0[index];
		config->iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config->rgb_pos = GR_BG_BAYER;
	/* Call AF_S_PARAM to do the configuration */
	result = ioctl(fd, AF_S_PARAM, config);
	printf("No of bytes that are required by the application  %d", result);
	/*Call AF_ENABLE to enable AF Engine */
	result = ioctl(fd, AF_ENABLE);
	printf("Result : %d", result);
	/* Disable the engine */
	ioctl(fd, AF_DISABLE);
	if (config)
		free(config);

	return 0;
}

/* af_Functional_TC2_4
 * Function to test AF_DISABLE ioctl
 */
int af_Functional_TC2_4(void)
{
	int fd;
	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}
	/*Call AF_DISABLE to disable AF Engine */
	ioctl(fd, AF_DISABLE);
	/* Close Driver */
	close(fd);
	return 0;
}

/* af_Functional_TC2_5
 * Function will pass invalid ioctl. The driver should return ENOTTY error code
 */
int af_Functional_TC2_5(void)
{
	int fd;
	int ret;
	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}
	ret = ioctl(fd, 1234);
	if (ret < 0) {
		perror("");
	}

	return 0;

}

/* af_Functional_TC2_6
 * Function to enable AF Engine without configuring hardware.
 * The driver should return AF_ERR_SETUP error code
 */
int af_Functional_TC2_6(void)
{
	int fd;
	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}
	ioctl(fd, AF_ENABLE);
	/* Close Driver */

	return 0;

}

/* af_Functional_TC3_1
 * Function will pass invalid paramteter to ioctl AF_S_PARAM.
 * The driver should return  error code
 */
int af_Functional_TC3_1(void)
{
	struct af_configuration config;
	int index = 0, fd, result;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("\n Error in opening AF Device");
		return -1;
	}
	/* Disable Alaw */
	config.alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 200000;
	config.paxel_config.height = 8000;
	config.paxel_config.width = 8000;
	config.paxel_config.line_incr = 2;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 89;
	config.paxel_config.vt_cnt = 800;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	/* Call AF_S_PARAM to do the configuration */
	result = ioctl(fd, AF_S_PARAM, &config);
	printf("\n errno %d", errno);
	printf("Return Value of AF_S_PARAM : %d", result);
	/* Disable the engine */
	ioctl(fd, AF_DISABLE);
	close(fd);
	return 0;
}

static int InitCaptureDevice(void)
{
	/* input-0 is selected by default, so no need to set it */
	if ((fdCapture = open(CAPTURE_DEVICE, O_RDWR | O_NONBLOCK, 0)) <= -1) { 
		printf("InitDevice:open::\n");
		return -1;
	}

	return 0;
}
int StartLoop_stress(void)
{
	struct v4l2_buffer buf;
	FILE *fp1;
	fp1 = fopen("af_samp.txt", "w");

	printf("\n Buffer size s %d", buff_size);

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
			printf("StartCameraCaputre:ioctl:VIDIOC_DQBUF\n");
			return -1;
		}

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			printf("StartCameraCaputre:ioctl:VIDIOC_QBUF\n");
		}

	}

	return 0;
}
int StartLoop(void)
{
	struct v4l2_buffer buf;
	int *k11;
	int result;
	int count = 0;
	FILE *fp1;
	fp1 = fopen("af_samp.txt", "w");

	printf("\n Buffer size s %d", buff_size);

	buffer_stat = (void *)malloc(buff_size);
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

	/* Enable the engine */
	if (ioctl(fd, AF_ENABLE) < 0) {
		printf("ioctl AF_ENABLE fail. \n");
		if (fd)
			close(fd);
		return -1;
	}
	printf("\n Reading...%d\n", buff_size);
	result = read(fd, (void *)buffer_stat, buff_size);

	if (result < 0) {
		printf("\n Read Failed");
	}
	printf("\n NO OF BYTES READ %d", result);

	if (result > 0) {

		printf("\nOutput is in file af_samp.txt");
		k11 = (int *)buffer_stat;

		for (count = 0; count < buff_size / 4; count++) {
			fprintf(fp1, "\n%d", k11[count]);
			/*printf("\n@%d@",k11[count]);*/
		}

	} else {
		printf("\n *** NOT ABLE TO READ*****");
		return -1;
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

int af_Functional_TC6_2(void)
{
	struct af_configuration config;
	int result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_ENABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 255;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AF_S_PARAM, &config);
	if (buff_size < 0) {
		printf("ioctl AF_S_PARAM fail \n");

		return -1;
	}

	result = StartLoop();
	if (result < 0) {
		printf("\n error in StartLOOP");
		return -1;
	}
	/* Disable the engine */
	if (ioctl(fd, AF_DISABLE) < 0) {
		printf("ioctl AF_DISABLE fail. \n");
	}
	return 0;

}
int af_Functional_TC6_1(void)
{
	struct af_configuration config;
	int result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_ENABLE;
	config.hmf_config.threshold = 255;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AF_S_PARAM, &config);
	if (buff_size < 0) {
		printf("ioctl AF_S_PARAM fail \n");
		return -1;
	}

	result = StartLoop();
	if (result < 0) {
		printf("\n error in StartLOOP");
		return -1;
	}
	/* Disable the engine */
	if (ioctl(fd, AF_DISABLE) < 0) {
		printf("ioctl AF_DISABLE fail. \n");
	}
	return 0;

}
int af_Functional_TC4_1(void)
{
	struct af_configuration config;
	int result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AF_S_PARAM, &config);
	if (buff_size < 0) {
		printf("ioctl AF_S_PARAM fail \n");
		return -1;
	}

	result = StartLoop();
	if (result < 0) {
		printf("\n error in StartLOOP");
		return -1;
	}
	/* Disable the engine */
	if (ioctl(fd, AF_DISABLE) < 0) {
		printf("ioctl AF_DISABLE fail. \n");
	}
	return 0;

}
int af_Stress(void)
{
	struct af_configuration config;
	int result = 0, index;
	int stress_count = 0;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_DISABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_ENABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AF_S_PARAM, &config);
	if (buff_size < 0) {
		printf("ioctl AF_S_PARAM fail \n");
		return -1;
	}

	buffer_stat = (void *)malloc(buff_size);
	result = StartLoop_stress();
	if (result < 0) {
		printf("\n error in StartLOOP");
		return -1;
	}			/* Enable the engine */
	if (ioctl(fd, AF_ENABLE) < 0) {
		printf("ioctl AF_ENABLE fail. \n");
		if (fd)
			close(fd);
		return -1;
	}
	printf("\n Reading...%d\n", buff_size);
	while (1) {
		result = read(fd, (void *)buffer_stat, buff_size);
		stress_count++;
		printf("\n Cnt : %d", stress_count);
		if (result < 0) {

			printf("\n Read Failed");
			return -1;
		}
	}
	/* Disable the engine */
	if (ioctl(fd, AF_DISABLE) < 0) {
		printf("ioctl AF_DISABLE fail. \n");
	}
	return 0;

}

int af_Functional_TC5_1(void)
{
	struct af_configuration config;
	int result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };
	void *buffer_stat1;
	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_ENABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	ioctl(fd, AF_S_PARAM, &config);
	buff_size =
	    config.paxel_config.hz_cnt * config.paxel_config.vt_cnt * 32;

	if (buff_size < 0) {
		printf("ioctl AF_S_PARAM fail \n");
		if (fd)
			close(fd);
		return -1;
	}
	buffer_stat1 = malloc(buff_size);
	result = read(fd, buffer_stat1, buff_size);
	if (result <= 0) {
		printf("\n Unable to read");
	}

	/* Disable the engine */
	if (ioctl(fd, AF_DISABLE) < 0) {
		printf("ioctl AF_DISABLE fail. \n");
		return -1;
	}
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
=====================af_Functional_TC5_3===========================
*/
/*Application will issue two read calls.
 Second read call should be blocked until new statistics are available.
This can be verified by measuring time taken by read call*/

int af_Functional_TC5_3(void)
{
	struct af_configuration config;
	int result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	struct timeval ptime, ntime, resulttime;
	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_ENABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AF_S_PARAM, &config);
	result = StartLoop();
	if (result < 0) {
		printf("\n error in StartLOOP");
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
	ioctl(fd, AF_DISABLE);
	return 0;
}
int af_Performance_TC1_1(void)
{
	struct af_configuration config;
	int result = 0, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };

	/*Open AF driver */
	fd = open(DRIVER_NAME, O_RDWR);
	if (fd < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_ENABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 2;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 2;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 36;
	config.paxel_config.vt_cnt = 76;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	buff_size = ioctl(fd, AF_S_PARAM, &config);
	result = StartLoop();
	if (result < 0) {
		printf("\n error in StartLOOP");
		return -1;
	}

	/* Disable the engine */
	if (ioctl(fd, AF_DISABLE) < 0) {
		printf("ioctl AF_DISABLE fail. \n");
	}
	return 0;
}
void *af_TC5_2_Test(int id);
/*
=====================af_Functional_TC5_2===========================
*/
/* Create two threads in the application
.Driver should return error to the second thread.*/
int af_Functional_TC5_2(void)
{
	pthread_t ch1_thread, ch2_thread;
	struct af_configuration config;
	int result, status, index;
	int iir0[12] = { 64, 0, 0, 21, 22, 21, 0, 0, -16, 32, -16 };
	int iir1[12] = { 64, 0, 0, 21, 22, 21, 0, -29, -16, 32, -16 };
	/*Open AF driver */
	fd_thread = open(DRIVER_NAME, O_RDWR);
	if (fd_thread < 0) {
		printf("Error in opening AF Device\n");
		return -1;
	}
	/* Select input source as SDRAM */

	/* Enable Alaw */
	config.alaw_enable = H3A_AF_ENABLE;
	/*Set Horizontal Median filter */
	config.hmf_config.enable = H3A_AF_DISABLE;
	config.hmf_config.threshold = 100;
	/* Set paxel Parmateres */
	config.iir_config.hz_start_pos = 2;
	config.paxel_config.height = 8;
	config.paxel_config.width = 8;
	config.paxel_config.line_incr = 4;
	config.paxel_config.vt_start = 4;
	config.paxel_config.hz_start = 4;
	config.paxel_config.hz_cnt = 8;
	config.paxel_config.vt_cnt = 8;
	/* Set Accumulator mode */
	config.mode = ACCUMULATOR_SUMMED;
	/* Set IIR Filter Parameters */
	for (index = 0; index < 11; index++) {
		config.iir_config.coeff_set0[index] = iir0[index];
		config.iir_config.coeff_set1[index] = iir1[index];
	}
	/* Set RGBPOSITION */
	config.rgb_pos = GR_BG_BAYER;
	printf("\n Before SEt Params");
	/* Call AF_S_PARAM to do the configuration */
	size_buff_thread = ioctl(fd_thread, AF_S_PARAM, &config);

	result = StartLoop_thread();
	printf("\n enabling the engine");
	ioctl(fd_thread, AF_ENABLE);
	printf("\n BUFFER SIZE IS %d", size_buff_thread);
	if (result < 0) {
		printf("\n Error in Streaming");
		status = ioctl(fd_thread, AF_DISABLE);
		close(fd);
		return -1;
	}
	printf("\nbefore thread ");
	pthread_create(&ch2_thread, NULL, (void *)af_TC5_2_Test, (void *)1);
	pthread_create(&ch1_thread, NULL, (void *)af_TC5_2_Test, (void *)2);

	printf("\after thread ");
	printf("\n @@ JOININGIN THE THREAD ");
	pthread_join(ch1_thread, (void **)0);
	pthread_join(ch2_thread, (void **)0);
	status = ioctl(fd_thread, AF_DISABLE);
	close(fd_thread);
	end_capture();
	return 0;
}

void af_DumptoFile(void *buffer, unsigned int buff_size, char *filename)
{
	int count;
	FILE *fp1;
	int *temp;
	temp = (int *)buffer;
	fp1 = fopen(filename, "w");
	for (count = 0; count < (buff_size / 4); count++) {
		/*printf("\n Data %d",temp[count]);*/
		fprintf(fp1, "\n%d", (int)temp[count]);
	}
}

/*
=====================af_Functional_TC5_2_Test===========================
*/
/* Function us called by thread*/

void *af_TC5_2_Test(int id)
{
	int result;
	void *buffer_stat1;
	buffer_stat1 = (void *)malloc(size_buff_thread);
	printf("HELLO I M THREAD %d\n", id);
	/* Open AF Driver */
	printf("\n SIZE OF BUFFER IS %d", size_buff_thread);

	if (size_buff_thread > 0)
		buffer_stat1 = malloc(size_buff_thread);
	result = read(fd_thread, (void *)buffer_stat1, size_buff_thread);
	printf("\n RESULT of READ IS %d", result);

	if (result > 0) {
		printf("\n HI i m printing for thread %d", id);
		if (id == 1) {
			af_DumptoFile(buffer_stat1, size_buff_thread,
				      "tc5_2_1stthread.txt");
		} else {
			af_DumptoFile(buffer_stat1, size_buff_thread,
				      "tc5_2_2ndthread.txt");
		}
	}

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

/*
=====================af_Functional_TC7_1===========================
*/
/* Function to test multiple open Calls .
Driver should support single application.*/
int af_Functional_TC7_1(void)
{

	int fd1, fd2;
	/*Open AF driver */
	fd1 = open(DRIVER_NAME, O_RDWR);
	if (fd1 < 0) {
		printf("\n Error in opening file");
		return -1;
	}
	fd2 = open(DRIVER_NAME, O_RDWR);
	if (fd2 < 0) {
		printf("\n Error in opening file");
		return -1;
	}
	return 0;

}
void usage_vpfe(char *abc)
{
	printf("VPFE Integrated Application\n");
	printf("./a.out -t <test_no> -g <sensor_gain> -e <sensor_shutter>\n");
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
	/* Process command line parameters */
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
				af_Functional_TC2_1();
				break;
			case 2:
				af_Functional_TC2_2();
				break;
			case 3:
				af_Functional_TC2_3();
				break;
			case 4:

				af_Functional_TC2_4();
				break;
			case 5:

				af_Functional_TC2_5();
				break;
			case 6:
				af_Functional_TC2_6();
				break;
			}
			break;
		case 3:
			switch (no) {
			case 1:
				af_Functional_TC3_1();
				break;
			default:
				usage();
				exit(1);
			}
			break;
		case 4:
			af_Functional_TC4_1();
			break;
		case 5:
			switch (no) {
			case 1:

				af_Functional_TC5_1();
				break;
			case 2:

				af_Functional_TC5_2();
				break;
			case 3:

				af_Functional_TC5_3();
				break;
			default:
				usage();
				exit(1);
			}
			break;
		case 6:
			switch (no) {
			case 1:
				af_Functional_TC6_1();
				break;
			case 2:
				af_Functional_TC6_2();
				break;
			}
			break;
		case 7:
			af_Functional_TC7_1();
			break;
		}
	case 'i':
	case 'I':
		break;
	case 's':
	case 'S':
		af_Stress();
		/*af_Stress_TC1_1();*/
		break;
	case 'p':
	case 'P':

		af_Performance_TC1_1();
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
