/*
 * capture-previewer-resizer-single-shot YUV mode, user pointer 
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
#include <stdio.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/mman.h>
#include <getopt.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>
#include <media/davinci/vpfe_capture.h>	
#include <media/davinci/imp_previewer.h>
#include <media/davinci/imp_resizer.h>
#include <media/davinci/dm365_ipipe.h>
#include "cmem.h"

char dev_name_prev[1][30] = {"/dev/davinci_previewer"};
char dev_name_rsz[1][30] = {"/dev/davinci_resizer"};
#define DISPLAY_INTERFACE_COMPOSITE	"COMPOSITE"
#define DISPLAY_INTERFACE_COMPONENT	"COMPONENT1"
#define DISPLAY_MODE_PAL	"PAL"
#define DISPLAY_MODE_NTSC	"NTSC"
#define DISPLAY_MODE_720P	"720P-60"		
#define DISPLAY_MODE_1080I	"1080I-30"		
/* Standards and output information */
#define ATTRIB_MODE		"mode"
#define ATTRIB_OUTPUT		"output"

#define APP_NUM_BUFS 3
#define CAPTURE_DEVICE  "/dev/video0"
#define CAP_FORMAT1		VPFE_STD_AUTO

#define V4L2VID0_DEVICE    "/dev/video2"
#define V4L2VID1_DEVICE    "/dev/video3"
#define CLEAR(x) memset (&(x), 0, sizeof (x))
int en_preview_rsz=1;

#define ALIGN(x, y)	(((x + (y-1))/y)*y)

int buf_size = ALIGN((1920*1080*2), 4096);

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

static int printfn = 1;
struct buf_info capture_buffers[APP_NUM_BUFS];
struct buf_info display_buffers[APP_NUM_BUFS];

static int out_format;

/* IN_XXX should match with CAP_FORMAT1 */
#define IN_WIDTH 	720
#define IN_HEIGHT 	480
#define OUT_WIDTH 	720
#define OUT_HEIGHT 	480
#define BYTESPERPIXEL 2

/*******************************************************************************
 * allocate_user_buffers() allocate buffer using CMEM
 ******************************************************************************/
int allocate_user_buffers(void)
{
	void *pool;
	int i;

	CMEM_AllocParams  alloc_params;
	printf("calling cmem utilities for allocating frame buffers\n");
	CMEM_init();

	alloc_params.type = CMEM_POOL;
	alloc_params.flags = CMEM_NONCACHED;
	alloc_params.alignment = 32;
	pool = CMEM_allocPool(0, &alloc_params);

	if (NULL == pool) {
		printf("Failed to allocate cmem pool\n");
		return -1;
	}
	printf("Allocating capture buffers :buf size = %d \n", buf_size);
	
	for (i=0; i < APP_NUM_BUFS; i++) {
		capture_buffers[i].user_addr = CMEM_alloc(buf_size, &alloc_params);
		if (capture_buffers[i].user_addr) {
			capture_buffers[i].phy_addr = CMEM_getPhys(capture_buffers[i].user_addr);
			if (0 == capture_buffers[i].phy_addr) {
				printf("Failed to get phy cmem buffer address\n");
				return -1;
			}
		} else {
			printf("Failed to allocate cmem buffer\n");
			return -1;
		}
		printf("Got %p from CMEM, phy = %p\n", capture_buffers[i].user_addr,
			(void *)capture_buffers[i].phy_addr);
	}

	printf("Allocating display buffers :buf size = %d \n", buf_size);
	for (i=0; i < APP_NUM_BUFS; i++) {
		display_buffers[i].user_addr = CMEM_alloc(buf_size, &alloc_params);
		if (display_buffers[i].user_addr) {
			display_buffers[i].phy_addr = CMEM_getPhys(display_buffers[i].user_addr);
			if (0 == display_buffers[i].phy_addr) {
				printf("Failed to get phy cmem buffer address\n");
				return -1;
			}
		} else {
			printf("Failed to allocate cmem buffer\n");
			return -1;
		}
		printf("Got %p from CMEM, phy = %p\n", display_buffers[i].user_addr,
			(void *)display_buffers[i].phy_addr);
	}

	return 0;
}

void usage()
{
	printf("Usage:capture_prev_rsz_onthe_fly\n");
}

int init_resizer(unsigned int user_mode, int in_width, int in_height,
		int out_width, int out_height)
{
	int rsz_fd;
	unsigned int oper_mode;
	struct rsz_channel_config rsz_chan_config;
	struct rsz_single_shot_config rsz_ss_config; // continuous mode
	printf("opening resize device\n");
	rsz_fd = open((const char *)dev_name_rsz[0], O_RDWR);
	if(rsz_fd <= 0) {
		printf("Cannot open resize device \n");
		return -1;
	}

	if (ioctl(rsz_fd, RSZ_S_OPER_MODE, &user_mode) < 0) {
		perror("Can't get operation mode\n");
		close(rsz_fd);
		return -1;
	}

	if (ioctl(rsz_fd, RSZ_G_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		close(rsz_fd);
		return -1;
	}

	if (oper_mode == user_mode) 
		printf("Successfully set mode to single shot in resizer\n");
	else {
		printf("failed to set mode to single shot in resizer\n");
		close(rsz_fd);
		return -1;
	}
		
	// set configuration to chain resizer with preview
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain  = 0;
	rsz_chan_config.len = 0;
	rsz_chan_config.config = NULL; /* to set defaults in driver */
	if (ioctl(rsz_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration in resizer\n");
		close(rsz_fd);
		return -1;
	}
	
	printf("default configuration setting in Resizer successfull\n");
	bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	rsz_chan_config.config = &rsz_ss_config;

	if (ioctl(rsz_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in getting resizer channel configuration from driver\n");
		close(rsz_fd);
		return -1;
	}
		
	// we can ignore the input spec since we are chaining. So only
	// set output specs
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_ss_config.input.image_width = in_width;
	rsz_ss_config.input.image_height = in_height/2;
	rsz_ss_config.input.ppln = in_width + 8;
	rsz_ss_config.input.lpfr = in_height+ 10;
	rsz_ss_config.input.line_length = ((in_width * 4) + 31) & ~0x1f;
	rsz_ss_config.input.clk_div.m = 1;
	rsz_ss_config.input.clk_div.n = 5;
	rsz_ss_config.input.pix_fmt = IPIPE_UYVY;
	if (out_format)
		rsz_ss_config.output1.pix_fmt = IPIPE_YUV420SP;
	else
		rsz_ss_config.output1.pix_fmt = IPIPE_UYVY;
	rsz_ss_config.output1.enable = 1;
	rsz_ss_config.output1.width = out_width;
	rsz_ss_config.output1.height = out_height;	
	rsz_ss_config.output2.enable = 0;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	rsz_chan_config.config = &rsz_ss_config;
	if (ioctl(rsz_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting configuration in resizer\n");
		close(rsz_fd);
		return -1;
	}
	printf("Resizer initialized\n");
	return rsz_fd;
}

int do_resize(int rsz_fd, 
				int in_width,
				int in_height,
				void *capbuf_addr, 
				void *display_buf,
				int out_width,
				int out_height)
{
	struct imp_convert convert;
	int index;

	bzero(&convert,sizeof(convert));
	convert.in_buff.buf_type = IMP_BUF_IN;
	convert.in_buff.index = -1;
	convert.in_buff.offset = (unsigned int)capbuf_addr;
	convert.in_buff.size = in_width*in_height*2;

	for (index=0; index < APP_NUM_BUFS; index++) {
		if (capture_buffers[index].user_addr == capbuf_addr) {
			break;
		}
	}
	if (index == APP_NUM_BUFS) {
		printf("Couldn't find display buffer index\n");
		return -1;
	}

	convert.out_buff1.buf_type = IMP_BUF_OUT1;
	convert.out_buff1.index = -1;
	convert.out_buff1.offset = (unsigned int)display_buf;
	convert.out_buff1.size = out_width * out_height * BYTESPERPIXEL;
	if (ioctl(rsz_fd, RSZ_RESIZE, &convert) < 0) {
		perror("Error in doing preview\n");
		return -1;
	} 
	return 0;
}
	
static int SetDataFormat(int fdCapture, v4l2_std_id *std, int *width, int *height)
{
	v4l2_std_id cur_std;
	struct v4l2_format fmt;
	struct v4l2_input input;
	int ret;

	printf("SetDataFormat:setting std to %d\n", (int)cur_std);

	// first set the input
	input.type = V4L2_INPUT_TYPE_CAMERA;
	input.index = 0;
  	while (0 == ioctl(fdCapture,VIDIOC_ENUMINPUT, &input)) { 
		printf("input.name = %s\n", input.name);
		if (!strcmp(input.name, "Composite"))
			break;
		input.index++;
  	}

  	if (ioctl (fdCapture, VIDIOC_S_INPUT, &input.index) < 0)
  	{
      		printf ("InitDevice:ioctl:VIDIOC_S_INPUT\n");
      		return -1;
  	}

  	printf ("InitDevice:ioctl:VIDIOC_S_INPUT, selected %s INPUT input\n",
		 input.name);
	if (ioctl(fdCapture, VIDIOC_QUERYSTD, &cur_std) < 0) {
		perror("set_data_format:ioctl:VIDIOC_QUERYSTD:\n");
		return -1;
	}

	if (cur_std & V4L2_STD_NTSC) {
                printf("Input video standard is NTSC.\n");
		*width = 720;
		*height = 480;
	} else if ((cur_std & V4L2_STD_PAL) || (cur_std & V4L2_STD_PAL_M) ||
        	   (cur_std & V4L2_STD_PAL_N) || (cur_std & V4L2_STD_PAL_60)) {
                printf("Input video standard is PAL.\n");
		*width = 720;
		*height = 576;
	} else
                return -1;

	if (ioctl(fdCapture, VIDIOC_S_STD, &cur_std) < 0) {
		perror("SetDataFormat:error:ioctl:VIDIOC_S_STD:");
		return -1;
	} else
		printf("\nS_STD Done WITH std = %llu\n", cur_std);

	sleep(1);
	if (ioctl(fdCapture, VIDIOC_G_STD, &cur_std) < 0) {
		perror("SetDataFormat:ioctl:VIDIOC_G_STD: failed");
		return -1;
	}

	printf("SetDataFormat:requesting width:%d height:%d\n", width, height);
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = *width;
	fmt.fmt.pix.height = *height;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	if (-1 == ioctl(fdCapture, VIDIOC_S_FMT, &fmt)) {
		perror("SetDataFormat:ioctl:VIDIOC_S_FMT");
		return -1;
	} else
		printf("\nS_FMT Done\n");
	*std = cur_std;
	return 0;
}

static int InitCaptureBuffers(int fdCapture)
{
	struct v4l2_requestbuffers req;
	int nIndex = 0, i;

	CLEAR(req);
	req.count = APP_NUM_BUFS;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_USERPTR;

	if (-1 == ioctl(fdCapture, VIDIOC_REQBUFS, &req)) {
		perror("InitCaptureBuffers:ioctl:VIDIOC_REQBUFS");
		return -1;
	} else
		printf("\nREQBUF Done\n");

	return 0;
}

int init_camera_capture(v4l2_std_id *std, int *width, int *height)
{
	int capt_fd;
    int ret = 0;
    struct v4l2_capability cap;

    if ((capt_fd = open(CAPTURE_DEVICE, O_RDWR | O_NONBLOCK, 0)) <= -1) {

        perror("init_camera_capture:open::");
		return -1;
    }

    /*Is capture supported? */
    if (-1 == ioctl(capt_fd, VIDIOC_QUERYCAP, &cap)) {
        perror("init_camera_capture:ioctl:VIDIOC_QUERYCAP:");
		close(capt_fd);
		return -1;
    }

    if (!(cap.capabilities & V4L2_CAP_VIDEO_CAPTURE)) {
        printf("InitDevice:capture is not supported on:%s\n",
               CAPTURE_DEVICE);
		close(capt_fd);
		return -1;
    }

    /*is MMAP-IO supported? */
    if (!(cap.capabilities & V4L2_CAP_STREAMING)) {
        printf
            ("InitDevice:IO method MMAP is not supported on:%s\n",
             CAPTURE_DEVICE);
		close(capt_fd);
		return -1;
    }

	printf("setting data format\n");
	if (SetDataFormat(capt_fd, std, width, height) < 0) {
		printf("SetDataFormat failed\n");
		close(capt_fd);
		return -1;
	}

	printf("initializing capture buffers\n");
	if (InitCaptureBuffers(capt_fd) < 0) {
		printf("InitCaptureBuffers failed\n");
		close(capt_fd);
		return -1;
	}
	printf("Capture initialized\n");
	return capt_fd;
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
		return -1;
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
	return 0;
}

// assumes we use ntsc display
int init_display_device(int device, int width, int height)
{
	int fdDisplay;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	int a, ret, i,j;
	struct v4l2_format fmt;
	struct v4l2_crop crop;
	int fd_mode, fd_output;
	char output[40], mode[40];

	if (device == 0) {
		if ((fdDisplay = open(V4L2VID0_DEVICE, O_RDWR)) < 0) {
			printf("Open failed for vid0\n");
			return -1;
		}
	}
	else if (device == 1)
	{
		if ((fdDisplay = open(V4L2VID1_DEVICE, O_RDWR)) < 0) {
			printf("Open failed for vid1\n");
			return -1;
		}
	} else {
		printf("Invalid device id\n");
		return -1;
	}

	CLEAR(fmt);
	if (width <= 720 && height <= 480) {
		width = 720;
		height = 480;
		strcpy(output, DISPLAY_INTERFACE_COMPOSITE);
		strcpy(mode, DISPLAY_MODE_NTSC);
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (width <= 720 && height <= 576) {
		width = 720;
		height = 576;
		strcpy(output, DISPLAY_INTERFACE_COMPOSITE);
		strcpy(mode, DISPLAY_MODE_PAL);
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (width <= 1280 && height <= 720) {
		width = 1280;
		height = 720;
		strcpy(output, DISPLAY_INTERFACE_COMPONENT);
		strcpy(mode, DISPLAY_MODE_720P);
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if (width <= 1920 && height <= 1080) {
		width = 1920;
		height = 1080;
		strcpy(output, DISPLAY_INTERFACE_COMPONENT);
		strcpy(mode, DISPLAY_MODE_1080I);
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else {
		printf("Cannot display input video resolution width = %d, height = %d\n",
			width, height);
		return -1;
	}

	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	if (!out_format)
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	else {
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
		fmt.fmt.pix.bytesperline = (fmt.fmt.pix.width + 31) & ~0x1f;
		fmt.fmt.pix.sizeimage= fmt.fmt.pix.bytesperline * height * 1.5;
	}

	ret = ioctl(fdDisplay, VIDIOC_S_FMT, &fmt);
	if (ret) {
		perror("VIDIOC_S_FMT failed\n");
		goto error;
	}

#if 0
	crop.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	crop.c.width = width;
	crop.c.height = height;
	crop.c.top = 0;
	crop.c.left = 0;
	if ( ioctl(fdDisplay, VIDIOC_S_CROP, &crop) == -1 ) {
		perror("VIDIOC_S_CROP failed\n");
		for (j = 0; j < req.count; j++)
			munmap(display_buffers[j].start,display_buffers[j].length);
		goto error;
	}
#endif
		
	req.count = APP_NUM_BUFS;
	req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	req.memory = V4L2_MEMORY_USERPTR;
	ret = ioctl(fdDisplay, VIDIOC_REQBUFS, &req);
	if (ret) {
		perror("cannot allocate memory\n");
		goto error;
	}

	/* Enqueue buffers */
	for (i = 0; i < req.count; i++) {
		bzero(&buf, sizeof(buf));
		buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		buf.index = i;
		buf.length = width*height*BYTESPERPIXEL;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.m.userptr = (unsigned long)display_buffers[i].user_addr;
		ret = ioctl(fdDisplay, VIDIOC_QBUF, &buf);
		if (ret) {
			printf("VIDIOC_QBUF\n");
			goto error;
		}
	}

	a = 0;
	ret = ioctl(fdDisplay, VIDIOC_STREAMON, &a);
	if (ret < 0) {
		perror("VIDIOC_STREAMON failed\n");
		goto error;
	}
	printf("Enabled streaming on display device\n");
	return fdDisplay;
error:
	close(fdDisplay);
	return -1;
}

int start_capture_streaming(int fdCapture)
{
	int i = 0;
	enum v4l2_buf_type type;

	for (i = 0; i < APP_NUM_BUFS; i++) {
		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.index = i;
		buf.length = buf_size;
		buf.m.userptr = (unsigned long)capture_buffers[i].user_addr;
		printf("Queing buffer:%d\n", i);

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			perror("StartStreaming:VIDIOC_QBUF failed");
			return -1;
		} else
			printf("\nQ_BUF Done\n");

	}
	/* all done , get set go */
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fdCapture, VIDIOC_STREAMON, &type)) {
		perror("StartStreaming:ioctl:VIDIOC_STREAMON:");
		return -1;
	} else
		printf("\nSTREAMON Done\n");

	return 0;
}

int cleanup_capture(int fd)
{
	int i;
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type)) {
		perror("cleanup_capture :ioctl:VIDIOC_STREAMOFF");
	}

	if (close(fd) < 0)
		perror("Error in closing device\n");
}

int cleanup_preview(int fd)
{
	int i;
	if (close(fd) < 0)
		perror("Error in closing preview device\n");
}


int cleanup_display(int fd)
{
	int i;
	enum v4l2_buf_type type;

	type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

	if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type)) {
		perror("cleanup_display :ioctl:VIDIOC_STREAMOFF");
	}

	if (close(fd) < 0)
		perror("Error in closing device\n");
}

int main(int argc, char *argp[])
{
	char shortoptions[] = "w:h:f:p:";
	int mode = O_RDWR,c,ret,index, disp_index;
	int preview_fd, rsz_fd, capt_fd, display_fd, dev_idx;
	unsigned int oper_mode, user_mode=IMP_MODE_SINGLE_SHOT;
	int level;
	int in_width = IN_WIDTH, in_height = IN_HEIGHT;
	int out_width = OUT_WIDTH, out_height = OUT_HEIGHT;
	int *capbuf_addr;
	fd_set fds;
	struct timeval tv;
	int r, i;
	int quit=0;
	struct timezone zone;
	int frame_count=0;
	v4l2_std_id std;
	struct v4l2_buffer cap_buf, disp_buf;
	int sizeimage;

	for(;;) {
		c = getopt_long(argc, argp, shortoptions, NULL, (void *)&index);
		if(-1 == c)
			break;
		switch(c) {
			case 'w':
				out_width = atoi(optarg);
				break;
			case 'h':
				out_height = atoi(optarg);
				break;
			case 'f':
				out_format = atoi(optarg);
				break;
			case 'p':
				printfn = atoi(optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	if (allocate_user_buffers() < 0) {
		printf("Unable to Allocate user buffers\n");
		exit(1);
	}	

	// intialize capture
	capt_fd = init_camera_capture(&std, &in_width, &in_height);

	if (capt_fd < 0)
		exit(1);

	// intialize resizer in single-shot mode
	rsz_fd = init_resizer(user_mode, in_width, in_height, out_width, out_height);
	if (rsz_fd < 0) {
		close(capt_fd);
		exit(1);
	}

	display_fd = init_display_device(0, out_width, out_height);
	if (display_fd < 0) {
		close(rsz_fd);
		close(capt_fd);
		exit(1);
	}

	printf("Initialized display\n");	
	if (start_capture_streaming(capt_fd) < 0) {
		cleanup_capture(capt_fd);
		cleanup_display(display_fd);
		close(rsz_fd);
		exit(1);
	}

#if 0
	if (ioctl(preview_fd, PREV_DUMP_HW_CONFIG, &level) < 0) {
		perror("Error in debug ioctl\n");
		cleanup_capture(capt_fd);
		cleanup_display(display_fd);
		close(rsz_fd);
		exit(1);
	} 
#endif

	while (!quit)
	{
                fd_set fds;
                struct timeval tv;
                int r;
		unsigned long temp;

		CLEAR(cap_buf);
		CLEAR(disp_buf);

                FD_ZERO(&fds);
                FD_SET(capt_fd, &fds);
                tv.tv_sec = 2;
                tv.tv_usec = 0;
                r = select(capt_fd + 1, &fds, NULL, NULL, &tv);
                if (-1 == r) {
                        if (EINTR == errno)
                                continue;
                        printf("StartCameraCapture:select\n");
                        return -1;
                }
                if (0 == r)
                        continue;

try1:
		disp_buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		disp_buf.memory = V4L2_MEMORY_USERPTR;
		//printf("VIDIOC_DQBUF for display, index = %d\n", disp_buf.index);
		ret =  ioctl(display_fd, VIDIOC_DQBUF, &disp_buf);
		if (ret < 0) {
			if (errno == EAGAIN) {
				goto try1;
			}
			perror("VIDIOC_DQBUF for display failed\n");
			return ret;
		}
		
		cap_buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		cap_buf.memory = V4L2_MEMORY_USERPTR;
try2:
		ret = ioctl(capt_fd, VIDIOC_DQBUF, &cap_buf);
		if (ret < 0) {
			if (errno == EAGAIN) {
				goto try2;
			}
			perror("VIDIOC_DQBUF for capture failed\n");
			return ret;
		}

		if (do_resize(rsz_fd, 
				in_width, 
				in_height,
				(void *)cap_buf.m.userptr,
				(void *)disp_buf.m.userptr,
				out_width,
				out_height) < 0) {
			printf("preview error\n");
			
		}

		/* Now Queue the buffer back to respective drivers */
		ret = ioctl(capt_fd, VIDIOC_QBUF, &cap_buf);
		if (ret < 0) {
			perror("VIDIOC_QBUF for capture failed\n");
			return ret;
		}

		if (!out_format)
			sizeimage = out_width * out_height * BYTESPERPIXEL;
		else
			sizeimage = (((out_width + 31) & ~0x1f) *
							out_height * 3)/2;

		disp_buf.length = ALIGN(sizeimage, 4096);

		//printf("VIDIOC_QBUF for display, index = %d\n", disp_buf.index);
		ret = ioctl(display_fd, VIDIOC_QBUF, &disp_buf);
		if (ret < 0) {
			perror("VIDIOC_QBUF for display failed\n");
			return ret;
		}


		if (printfn) {
			printf("frame:%5u, ", frame_count);
			printf("buf.timestamp:%lu:%lu\n",
				cap_buf.timestamp.tv_sec, cap_buf.timestamp.tv_usec);
		}
		frame_count++;
		if (frame_count == 500000) {
			quit = 1;
		}
	}
	printf("Cleaning capture\n");
	cleanup_capture(capt_fd);
	printf("Cleaning display\n");
	cleanup_display(display_fd);
	printf("Cleaning display - end\n");
	close(rsz_fd);
	printf("closing resize - end\n");
	exit(0);
}

