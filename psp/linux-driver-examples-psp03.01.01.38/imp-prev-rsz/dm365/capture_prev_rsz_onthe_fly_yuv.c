/*
 * capture_prev_rsz-onthe_fly_yuv - Capture and Resize the YUV data
 * and optionally do format conversion from UYVY to NV12
 *
 * This example shows how to do capture from TVP7002 or TVP5146 and
 * do on the fly processing on the captured image such as resize
 * and format conversion. It also shows how to get two resolution
 * images on a per frame basis. When DQBUF call is issued by the
 * application, it gets two frames. The second frame is piggy backed
 * at the end of first frame in the same buffer. So each of the capture
 * buffer has to be large enough to accomodate both frames. 
 * Here is the configuraton of IP for this usecase
 *
 * TVP5146/TVP7002 -> CCDC/ISIF ->IPIPEIF ->IPIPE->Resizer->SDRAM
 *
 * NOTE: This application requires CMEM
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
#include <media/davinci/dm365_ccdc.h>
#include <media/davinci/imp_previewer.h>
#include <media/davinci/imp_resizer.h>
#include <media/davinci/dm365_ipipe.h>
#include <media/davinci/videohd.h>
#include "cmem.h"

char dev_name_prev[1][30] = {"/dev/davinci_previewer"};
char dev_name_rsz[1][30] = {"/dev/davinci_resizer"};

/* APP_NUM_BUFS must be even */
#define APP_NUM_BUFS 6
#define CAPTURE_DEVICE  "/dev/video0"
#define V4L2VID0_DEVICE    "/dev/video2"
#define V4L2VID1_DEVICE    "/dev/video3"
#define CLEAR(x) memset (&(x), 0, sizeof (x))


#define IN_WIDTH 	1280	
#define IN_HEIGHT 	720	
#define OUT_WIDTH 	1280
#define OUT_HEIGHT 	720
#define BYTESPERPIXEL   2
#define WIDTH_NTSC		720
#define HEIGHT_NTSC		480
#define WIDTH_PAL		720
#define HEIGHT_PAL		576
#define WIDTH_720P		1280
#define HEIGHT_720P		720	
#define WIDTH_1080I		1920
#define HEIGHT_1080I		1080
#define DISPLAY_INTERFACE_COMPOSITE	"COMPOSITE"
#define DISPLAY_INTERFACE_COMPONENT	"COMPONENT"
#define DISPLAY_MODE_PAL	"PAL"
#define DISPLAY_MODE_NTSC	"NTSC"
#define DISPLAY_MODE_720P	"720P-60"		
#define DISPLAY_MODE_1080I	"1080I-30"	

/* Standards and output information */
#define ATTRIB_MODE		"mode"
#define ATTRIB_OUTPUT		"output"

#define ALIGN(x, y)	(((x + (y-1))/y)*y)

int buf_size = ALIGN((1920*1080*2), 4096);

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

/* 0 - UYVY, 1 - NV12 */
int out_format=0;
int in_width = IN_WIDTH, in_height = IN_HEIGHT;
int out_width = OUT_WIDTH, out_height = OUT_HEIGHT;

/* Use this to do resize of captured input */
static int resize;
static rsz_width, rsz_height;

static int printfn = 1;
int input_index = 0;
char *inputs[] = { "Composite", "S-Video", "Component" };
static struct v4l2_cropcap cropcap;
static int nWidthFinal;
static int nHeightFinal;
static v4l2_std_id cur_std;
static int rsz_fd, prev_fd;
/* 10 minutes */
static int start_loopCnt = 10000;
/* to reduce fps to 30 fps for 720p capture */
static int half_fps;

/* display 0 - output1 (RSZ_A)) or 1 - output2 (RSZ_B) from resizer */
static int disp_second_output;

/* second output width and height */
static int second_out_width = 320;
static int second_out_height = 240;
int second_output_offset;


struct buf_info capture_buffers[APP_NUM_BUFS];
struct buf_info display_buffers[APP_NUM_BUFS];

static int display_image_size;

#define FRAME_SIZE (1280*720)
#define LINE_OFFSET 0
#define NUM_FRAMES  30
static struct v4l2_rect crop_default = {32, 40, 720, 480 };
static int en_crop;

static unsigned long long prev_ts;
static unsigned long long curr_ts;
static unsigned long fp_period_average;
static unsigned long fp_period_max;
static unsigned long fp_period_min;
static unsigned long fp_period;


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
	
	for (i=0; i < APP_NUM_BUFS/2; i++) {
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
	for (i=0; i < APP_NUM_BUFS/2; i++) {
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

void usage()
{
	printf("Usage: capture_prev_rsz_onthe_fly_yuv [rwufiphxc]\n");
	printf("Options:\n");
	printf("\t-i\tInput interface to use\n");
	printf("\t\t\t0 => Composite input [DEFAULT without -i]\n");
	printf("\t\t\t1 => S-Video input\n");
	printf("\t\t\t2 => Component input\n");
	printf("\t-p\tPrint frame number and timestamp\n");
	printf("\t\t\t0 => Do not print\n");
	printf("\t\t\t1 => Print frame number and timestamp [DEFAULT without -p]\n");
	printf("\t-f\tOutput buffer format\n");
	printf("\t\t\t0 => Frame format UYVY [DEFAULT without -f]\n");
	printf("\t\t\t1 => Frame format NV12\n");
	printf("\t-c\tCropping enable/disable\n");
	printf("\t\t\t0 => Disable cropping [DEFAULT without -c]\n");
	printf("\t\t\t1 => Enable cropping (fixed rectangle of left = 32, "
	"\t\t\t                      top = 40, width = 720, height = 480\n");
	printf("\t-c\tResizing enable/disable\n");
	printf("\t\t\t0 => Disable resizing [DEFAULT without -r]\n");
	printf("\t\t\t1 => Enable resizing (resized dimensions defined by -w and -u)\n");
	printf("\t-w\tResized width (valid only with -r 1)\n");
	printf("\t-u\tResized height (valid only with -r 1)\n");
	printf("\t-h\tDrop frame rate to half (only in case of 720p-60 capture)\n");
	printf("\t\t\t0 => Do not drop frame rate by half [DEFAULT without -h]\n");
	printf("\t\t\t1 => Drop frame rate by half.\n");
	printf("\t-x\tResizer selection\n");
	printf("\t\t\t0 => Display from resizer A output [DEFAULT without -x]\n");
	printf("\t\t\t1 => Display from resizer A output\n");
	printf("Application dependencies:\n");
	printf("The application depends on cmem memory allocator for video "
			"buffers.\nYou can obtain cmem kernel module for DVSDK"
			"package. Insert it into the kernel:\n");
	printf("\tinsmod cmemk.ko phys_start=0x83C00000 phys_end=0x88000000 "
			"pools=7x4149248\n");
	printf("This application requires the resizer to be in 'continous' "
			"mode of operation.\nThat is acheived by passing:\n"
			"\tdm365_imp.oper_mode=0\n"
			"in the boot arguments to the kernel\n");
	printf("The application does not disable the OSD framebuffers, so "
			"they need to be disabled from bootargs passed to kernel\n"
			"\tvideo=davincifb:vid0=off:vid1=off:osd0=0:osd1=0\n");
}

int init_resizer(unsigned int user_mode)
{
	int rsz_fd;
	unsigned int oper_mode;
	struct rsz_channel_config rsz_chan_config;
	struct rsz_continuous_config rsz_cont_config; // continuous mode
	printf("opening resize device\n");
	rsz_fd = open((const char *)dev_name_rsz[0], O_RDWR);
	if(rsz_fd <= 0) {
		printf("Cannot open resize device \n");
		return -1;
	}

	if (ioctl(rsz_fd, RSZ_S_OPER_MODE, &user_mode) < 0) {
		perror("Can't set operation mode\n");
		close(rsz_fd);
		return -1;
	}

	if (ioctl(rsz_fd, RSZ_G_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		close(rsz_fd);
		return -1;
	}

	if (oper_mode == user_mode) 
		printf("Successfully set mode to continuous in resizer\n");
	else {
		printf("failed to set mode to continuous in resizer\n");
		close(rsz_fd);
		return -1;
	}
		
	// set configuration to chain resizer with preview
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain  = 1;
	rsz_chan_config.len = 0;
	rsz_chan_config.config = NULL; /* to set defaults in driver */
	if (ioctl(rsz_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration in resizer\n");
		close(rsz_fd);
		return -1;
	}
	
	printf("default configuration setting in Resizer successfull\n");
	bzero(&rsz_cont_config, sizeof(struct rsz_continuous_config));
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain = 1;
	rsz_chan_config.len = sizeof(struct rsz_continuous_config);
	rsz_chan_config.config = &rsz_cont_config;

	if (ioctl(rsz_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in getting resizer channel configuration from driver\n");
		close(rsz_fd);
		return -1;
	}
		
	// we can ignore the input spec since we are chaining. So only
	// set output specs
	rsz_cont_config.output1.enable = 1;
	if (disp_second_output) {
		rsz_cont_config.output2.enable = 1;
		rsz_cont_config.output2.width = second_out_width;
		rsz_cont_config.output2.height = second_out_height;
		if (out_format)
			rsz_cont_config.output2.pix_fmt = IPIPE_YUV420SP;
		else
			rsz_cont_config.output2.pix_fmt = IPIPE_UYVY;
	} else 
		rsz_cont_config.output2.enable = 0;
	rsz_chan_config.len = sizeof(struct rsz_continuous_config);
	rsz_chan_config.config = &rsz_cont_config;
	if (ioctl(rsz_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting configuration in resizer\n");
		close(rsz_fd);
		return -1;
	}
	printf("Resizer initialized\n");
	return rsz_fd;
}

int init_previewer(unsigned int user_mode)
{
	
	int preview_fd;
	unsigned int oper_mode;
	struct prev_channel_config prev_chan_config;
	struct prev_continuous_config prev_cont_config; // continuous mode
	

	preview_fd = open((const char *)dev_name_prev[0], O_RDWR);
	if(preview_fd <= 0) {
		printf("Cannot open previewer device\n");
		return -1;
	}

	if (ioctl(preview_fd,PREV_S_OPER_MODE, &user_mode) < 0) {
		perror("Can't get operation mode\n");
		close(preview_fd);
		return -1;
	}

	if (ioctl(preview_fd,PREV_G_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		close(preview_fd);
		return -1;
	}

	if (oper_mode == user_mode) 
		printf("Operating mode changed successfully to continuous in previewer");
	else {
		printf("failed to set mode to continuous in resizer\n");
		close(preview_fd);
		return -1;
	}

	printf("Setting default configuration in previewer\n");
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = 0;
	prev_chan_config.config = NULL; /* to set defaults in driver */
	if (ioctl(preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0) {
		perror("Error in setting default configuration\n");
		close(preview_fd);
		return -1;
	}

	printf("default configuration setting in previewer successfull\n");
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = sizeof(struct prev_continuous_config);
	prev_chan_config.config = &prev_cont_config;

	if (ioctl(preview_fd, PREV_G_CONFIG, &prev_chan_config) < 0) {
		perror("Error in getting configuration from driver\n");
		close(preview_fd);
		return -1;
	}
	
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = sizeof(struct prev_continuous_config);
	prev_chan_config.config = &prev_cont_config;
	
	if (ioctl(preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0) {
		perror("Error in setting default configuration\n");
		close(preview_fd);
		return -1;
	}

	printf("previewer initialized\n");
	return preview_fd;
}

/******************************************************************************/
static int set_data_format(int fdCapture)
{
	v4l2_std_id std;
	struct v4l2_format fmt;
	unsigned int min;
	struct v4l2_input input;
	int temp_input;
	int found = 0;
	struct v4l2_crop crop;
	struct v4l2_standard stdinfo;
	struct v4l2_streamparm streamparam;



	// first set the input
	input.type = V4L2_INPUT_TYPE_CAMERA;
	input.index = 0;
	printf("Detecting if driver supports %s\n", inputs[input_index]); 
  	while (0 == ioctl(fdCapture,VIDIOC_ENUMINPUT, &input)) { 
		printf("input.name = %s\n", input.name);
		if (!strcmp(input.name, inputs[input_index])) {
			found = 1;
			break;
		}
		input.index++;
  	}

	if (!found) {
		perror("Can't detect input  from the capture driver\n");
		return -1;
	} 

  	if (-1 == ioctl (fdCapture, VIDIOC_S_INPUT, &input.index))
  	{
		printf ("InitDevice:ioctl:VIDIOC_S_INPUT\n");
      		return -1;
  	}
	if (-1 == ioctl (fdCapture, VIDIOC_G_INPUT, &temp_input))
	{
		printf ("error: InitDevice:ioctl:VIDIOC_G_INPUT\n");
		return -1;
	}
	
	if (temp_input == input.index)
		printf ("InitDevice:ioctl:VIDIOC_G_INPUT, selected input %s \n",
			input.name);
	else {
		printf ("InitDevice:ioctl:VIDIOC_G_INPUT, Couldn't select input\n");
		return -1;
  	}

	if (-1 == ioctl(fdCapture, VIDIOC_QUERYSTD, &std)) {
		printf("set_data_format:ioctl:VIDIOC_QUERYSTD:\n");
		return -1;
	}

	cur_std = std;
	if (std & V4L2_STD_NTSC)
		printf("Input video standard is NTSC.\n");
	else if (std & V4L2_STD_PAL)
		printf("Input video standard is PAL.\n");
	else if (std & V4L2_STD_PAL_M)
		printf("Input video standard is PAL-M.\n");
	else if (std & V4L2_STD_PAL_N)
		printf("Input video standard is PAL-N.\n");
	else if (std & V4L2_STD_SECAM)
		printf("Input video standard is SECAM.\n");
	else if (std & V4L2_STD_PAL_60)
		printf("Input video standard to PAL60.\n");
	else if (std & V4L2_STD_720P_60)
		printf("Input video standard to 720p-60.\n");
	else if (std & V4L2_STD_1080I_60)
		printf("Input video standard to 1080I-60.\n");
	else if (std & V4L2_STD_1080I_50)
		printf("Input video standard to 1080I-50.\n");
	else if (std & V4L2_STD_720P_50)
		printf("Input video standard to 720p-50.\n");
	else if (std & V4L2_STD_525P_60)
		printf("Input video standard to 525p-60.\n");
	else if (std & V4L2_STD_625P_50)
		printf("Input video standard to 625p-50.\n");
	else {
		printf("Detection failed, std = %llx, %llx\n", std, V4L2_STD_NTSC);
		return -1;
	}

	if (-1 == ioctl(fdCapture, VIDIOC_S_STD, &std)) {
		printf("set_data_format:error:ioctl:VIDIOC_S_STD:\n");
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


	CLEAR(fmt);

	if (std & V4L2_STD_NTSC) {
		printf("set_data_format:requesting width:%d height:%d\n",
		       WIDTH_NTSC, HEIGHT_NTSC);
		in_width = WIDTH_NTSC;
		in_height = HEIGHT_NTSC;
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (std & V4L2_STD_525P_60) {
		printf("set_data_format:requesting width:%d height:%d\n",
		       WIDTH_NTSC, HEIGHT_NTSC);
		in_width = WIDTH_NTSC;
		in_height = HEIGHT_NTSC;
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if ((std & V4L2_STD_PAL) ||
		(std & V4L2_STD_PAL_M) ||
		(std & V4L2_STD_PAL_N)) {
		printf("set_data_format:requesting width:%d height:%d\n",
		       WIDTH_PAL, HEIGHT_PAL);
		in_width = WIDTH_PAL;
		in_height = HEIGHT_PAL;
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (std & V4L2_STD_625P_50) {
		printf("set_data_format:requesting width:%d height:%d\n",
		       WIDTH_PAL, HEIGHT_PAL);
		in_width = WIDTH_PAL;
		in_height = HEIGHT_PAL;
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if ((std & V4L2_STD_720P_60) ||
		   (std & V4L2_STD_720P_50)) {
		printf("set_data_format:requesting width:%d height:%d\n",
		       WIDTH_720P, HEIGHT_720P);
		in_width = WIDTH_720P;
		in_height = HEIGHT_720P;
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if ((std & V4L2_STD_1080I_60) ||
		   (std & V4L2_STD_1080I_50)) {
		printf("set_data_format:requesting width:%d height:%d\n",
		       WIDTH_1080I, HEIGHT_1080I);
		in_width = WIDTH_1080I;
		in_height = HEIGHT_1080I;
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	}

	
	if (!resize) {
		out_width = in_width;
		out_height = in_height;
	} else {
		in_width = rsz_width;
		in_height = rsz_height;
		out_width = rsz_width;
		out_height = rsz_height;
	}
	fmt.fmt.pix.width = in_width;
	fmt.fmt.pix.height = in_height;

#if 1
	CLEAR(crop);
	if (en_crop) {
		crop.c = crop_default;
	printf("******Cropping the input @%d,%d,%d,%d***********\n",
		crop.c.top, crop.c.left, crop.c.width, crop.c.height);
	crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fdCapture, VIDIOC_S_CROP, &crop)) {
		perror("set_data_format:ioctl:VIDIOC_S_CROP");
		return -1;
	} else
		printf("\nS_CROP Done\n");
	}
#endif
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (!out_format)
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	else 
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;

	if (-1 == ioctl(fdCapture, VIDIOC_S_FMT, &fmt)) {
		printf("set_data_format:ioctl:VIDIOC_S_FMT\n");
		return -1;
	}
	printf("driver parameters for S_FMT\n");
	printf("fmt.fmt.pix.width  = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);

	if (-1 == ioctl(fdCapture, VIDIOC_G_FMT, &fmt)) {
		printf("set_data_format:ioctl:VIDIOC_QUERYSTD:\n");
		return -1;
	}

	nWidthFinal = fmt.fmt.pix.width;
	nHeightFinal = fmt.fmt.pix.height;

	printf("set_data_format:finally negotiated width:%d height:%d\n",
	       nWidthFinal, nHeightFinal);
	printf("set_data_format:bytesperline = %d, sizeimage = %d\n",
	       fmt.fmt.pix.bytesperline, fmt.fmt.pix.sizeimage);

	/* checking what is finally negotiated */
	if (fmt.fmt.pix.pixelformat == V4L2_PIX_FMT_NV12)
		min = fmt.fmt.pix.width;
	else
		min = fmt.fmt.pix.width * 2;
	if (fmt.fmt.pix.bytesperline < min) {
		printf
		    ("set_data_format:driver reports bytes_per_line:%d(bug)\n",
		     fmt.fmt.pix.bytesperline);
		/*correct it */
		fmt.fmt.pix.bytesperline = min;
	}

	min = fmt.fmt.pix.bytesperline * fmt.fmt.pix.height;
	if (fmt.fmt.pix.sizeimage < min) {
		printf("set_data_format:driver reports size:%d(bug)\n",
		       fmt.fmt.pix.sizeimage);

		/*correct it */
		fmt.fmt.pix.sizeimage = min;
	}
	printf("set_data_format:Finally negitaited width:%d height:%d\n",
	        nWidthFinal, nHeightFinal);
	if (std == V4L2_STD_720P_60 && half_fps) {
		/* set the streaming parameter */
		CLEAR(streamparam);
		streamparam.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		streamparam.parm.capture.timeperframe.numerator = 1;
		streamparam.parm.capture.timeperframe.denominator = 30;
		if (ioctl(fdCapture, VIDIOC_S_PARM , &streamparam) < 0 ) {
			perror("Error in  VIDIOC_S_PARM\n");
			return -1;
		}

		/* verify the params */
		if (ioctl(fdCapture, VIDIOC_G_PARM, &streamparam) < 0) {
			perror("Error in  VIDIOC_G_PARM\n");
			return -1;
		}
		printf("VIDIOC_G_PARM: Got timeperframe.numerator = %d\n",
			streamparam.parm.capture.timeperframe.numerator);
		printf("VIDIOC_G_PARM: Got timeperframe.denominator = %d\n",
			streamparam.parm.capture.timeperframe.denominator);
	}
	return 0;
}

static int InitCaptureBuffers(int fdCapture)
{
	struct v4l2_requestbuffers req;
	int nIndex = 0, i;

	CLEAR(req);
	req.count = APP_NUM_BUFS/2;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_USERPTR;

	if (-1 == ioctl(fdCapture, VIDIOC_REQBUFS, &req)) {
		perror("InitCaptureBuffers:ioctl:VIDIOC_REQBUFS");
		return -1;
	} else
		printf("\nREQBUF Done\n");

	if (req.count != APP_NUM_BUFS/2) {
		printf("VIDIOC_REQBUFS failed for capture");
		return -1;
	}
	return 0;
}

int init_camera_capture(void)
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
	if (set_data_format(capt_fd) < 0) {
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
	ret = start_capture_streaming(capt_fd);
	if (ret) {
		printf("Failed to start capture streaming\n");
		return ret;
	}
	printf("Capture initialized\n");
	return capt_fd;
}

/******************************************************************************/
static int start_display_streaming(int fd_vid1)
{
	int i = 0;
	enum v4l2_buf_type type;

	for (i = 0; i < (APP_NUM_BUFS/2); i++) {
		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.index = i;
		buf.length = buf_size;
		if (disp_second_output) {
			buf.m.userptr = (unsigned long)display_buffers[i].user_addr +
			second_output_offset;
			buf.length = ALIGN((second_out_width * second_out_height * 2), 4096);
		}
		else
			buf.m.userptr = (unsigned long)display_buffers[i].user_addr;
		printf("Queing buffer:%d, before = %p, address = %p\n",
			 i, display_buffers[i].user_addr, buf.m.userptr);

		if (-1 == ioctl(fd_vid1, VIDIOC_QBUF, &buf)) {
			perror("start_display_streaming:ioctl:VIDIOC_QBUF error:\n");
			return -1;
		}
	}
	/* all done , get set go */
	type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	if (-1 == ioctl(fd_vid1, VIDIOC_STREAMON, &type)) {
		printf("start_display_streaming:ioctl:VIDIOC_STREAMON:error\n");
		return -1;
	}

	return 0;
}

// assumes we use ntsc display
int init_display_device(int device)
{
	int fdDisplay;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	int a, ret, i,j;
	struct v4l2_format fmt;
	struct v4l2_crop crop;
	int fd_mode, fd_output;
	enum v4l2_field field;

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

	/* Setup Display */
	if (disp_second_output) {
		field = V4L2_FIELD_INTERLACED;
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE) < 0) {
			close(fdDisplay);
			return -1;
		}
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_NTSC) < 0) {
			close(fdDisplay);
			return -1;
		}
	} else {
		if (out_width <= 720 && out_height <= 480) {
			field = V4L2_FIELD_INTERLACED;
			if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE) < 0) {
				close(fdDisplay);
				return -1;
			}
			if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_NTSC) < 0) {
				close(fdDisplay);
				return -1;
			}
		}
		else if (out_width <= 720 && out_height <= 576) {
			field = V4L2_FIELD_INTERLACED;
			if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE) < 0) {
				close(fdDisplay);
				return -1;
			}
			if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_PAL) < 0) {
				close(fdDisplay);
				return -1;
			}
		}
		else if (out_width <= 1280 && out_height <= 720) {
			field = V4L2_FIELD_NONE;
			if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPONENT) < 0) {
				close(fdDisplay);
				printf("error setting output\n");
				return -1;
			}
			if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_720P) < 0) {
				printf("error setting mode\n");
				close(fdDisplay);
				return -1;
			}
		}
		else if (out_width <= 1920 && out_height <= 1080) {
			field = V4L2_FIELD_INTERLACED;
			if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPONENT) < 0) {
				close(fdDisplay);
				return -1;
			}
			if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_1080I) < 0) {
				close(fdDisplay);
				return -1;
			}
		} else {
			printf("Cannot display this standard\n");
			return -1;
		}
	}

	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	fmt.fmt.pix.field = field;
	if (!disp_second_output) {
		if (out_format == 0) {
			fmt.fmt.pix.bytesperline = out_width * 2;
			fmt.fmt.pix.sizeimage =
		    		fmt.fmt.pix.bytesperline * out_height;
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
		} else {
			fmt.fmt.pix.width = out_width;
			fmt.fmt.pix.height = out_height;
			fmt.fmt.pix.bytesperline = ((out_width + 31) / 32) * 32;
			fmt.fmt.pix.sizeimage =
		    		fmt.fmt.pix.bytesperline * out_height * 1.5;
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
		}
	} else {
		if (out_format == 0) {
			//fmt.fmt.pix.width = second_out_width;
			//fmt.fmt.pix.height = second_out_height;
			fmt.fmt.pix.bytesperline = second_out_width * 2;
			fmt.fmt.pix.sizeimage =
	    			fmt.fmt.pix.bytesperline * second_out_height;
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
		} else {
			fmt.fmt.pix.width = second_out_width;
			fmt.fmt.pix.height = second_out_height;
			fmt.fmt.pix.bytesperline = ((second_out_width + 31) / 32) * 32;
			fmt.fmt.pix.sizeimage =
		    		fmt.fmt.pix.bytesperline * second_out_height * 1.5;
			fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
		}
	}

	ret = ioctl(fdDisplay, VIDIOC_S_FMT, &fmt);
	if (ret) {
		perror("VIDIOC_S_FMT failed\n");
		goto error;
	}

	printf("Updated driver parameters for S_FMT\n");
	printf("fmt.fmt.pix.width  = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);

#if 0
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(fdDisplay, VIDIOC_G_FMT, &fmt);
	if (ret) {
		perror("VIDIOC_G_FMT failed\n");
		goto error;
	}
	printf("driver parameters for G_FMT\n");
	printf("fmt.fmt.pix.width  = %d\n", fmt.fmt.pix.width);
	printf("fmt.fmt.pix.height = %d\n", fmt.fmt.pix.height);
	printf("fmt.fmt.pix.bytesperline = %d\n", fmt.fmt.pix.bytesperline);
	printf("fmt.fmt.pix.sizeimage = %d\n", fmt.fmt.pix.sizeimage);
#endif		
	req.count = APP_NUM_BUFS/2;
	req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	req.memory = V4L2_MEMORY_USERPTR;
	ret = ioctl(fdDisplay, VIDIOC_REQBUFS, &req);
	if (ret) {
		perror("cannot allocate memory\n");
		goto error;
	}

	if (start_display_streaming(fdDisplay) < 0)
		return -1;

	return fdDisplay;
error:
	close(fdDisplay);
	return -1;
}

int start_capture_streaming(int fdCapture)
{
	int i = 0;
	enum v4l2_buf_type type;

	for (i = 0; i < (APP_NUM_BUFS/2); i++) {
		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.index = i;
		buf.length = buf_size;
		buf.m.userptr = (unsigned long)capture_buffers[i].user_addr;

		if (ioctl(fdCapture, VIDIOC_QBUF, &buf) < 0) 
			printf("start_capture_streaming:ioctl:VIDIOC_QBUF: error\n");
		else
			printf("Queing buffer:%d\n", i);
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
		return -1;
	}

	if (close(fd) < 0) {
		perror("Error in closing device\n");
		return -1;
	}
	return 0;
}

int cleanup_display(int fd)
{
	int i;
	enum v4l2_buf_type type;

	type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

	if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type)) {
		perror("cleanup_display :ioctl:VIDIOC_STREAMOFF");
		return -1;
	}

	if (close(fd) < 0) {
		perror("Error in closing device\n");
		return -1;
	}
	return 0;
}

int main(int argc, char *argp[])
{
	char shortoptions[] = "r:w:u:f:i:p:h:x:c:";
	int mode = O_RDWR,c,ret,index, display_index;
	int preview_fd, rsz_fd, capt_fd, display_fd, dev_idx;
	unsigned int oper_mode, user_mode=IMP_MODE_CONTINUOUS;
	struct rsz_channel_config rsz_chan_config;
	struct rsz_continuous_config rsz_cont_config; // continuous mode
	int level;
	int width = 720, height = 480;
	int *capbuf_addr;
	fd_set fds;
	struct timeval tv;
	int r;
	int quit=0;
	struct timezone zone;
	int frame_count=0;
	static int captFrmCnt = 0;
	struct v4l2_buffer cap_buf, disp_buf;
	int temp_index;


	for(;;) {
		c = getopt_long(argc, argp, shortoptions, NULL, (void *)&index);
		if(-1 == c)
			break;
		switch(c) {
		case 'f':
			out_format = atoi(optarg);
			if (out_format < 0 || out_format > 1) {
				printf("Choose 0 - UYVY 1 - NV12 for output pix format\n");
				exit(1);
			}
			break;
		case 'p':
		case 'P':
			printfn = atoi(optarg);
			break;
		case 'h':
			half_fps = atoi(optarg);
			break;
		case 'x':
			disp_second_output = atoi(optarg);
			break;
		case 'c':
			en_crop = atoi(optarg);
			break;
		case 'r':
			resize = atoi(optarg);
			break;
		case 'w':
			rsz_width = atoi(optarg);
			break;
		case 'u':
			rsz_height = atoi(optarg);
			break;

		case 'i':
		case 'I':
			input_index = atoi(optarg);
			if (input_index > 2)
				printf("choose index 0 for Composite,"
					" 1 - Svideo or 2 - component\n");
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

	// intialize resizer in continuous mode
	rsz_fd = init_resizer(user_mode);
	if (rsz_fd < 0) {
		exit(1);
	}

	// initialize previewer in continuous mode
	preview_fd = init_previewer(user_mode);

	if (preview_fd < 0) {
		close(rsz_fd);
		exit(1);
	}
	

	capt_fd = init_camera_capture();

	if (capt_fd < 0) {
		close(preview_fd);
		close(rsz_fd);
		exit(1);
	}
	
	if (!out_format)
		second_output_offset = in_width * in_height * 2;
	else
		second_output_offset = ALIGN(in_width ,32) * in_height * 1.5;

	second_output_offset = ALIGN(second_output_offset, 4096);

	printf("Second output offset = %d\n", second_output_offset);
	display_fd = init_display_device(0);
	if (display_fd < 0) {
		close(preview_fd);
		close(rsz_fd);
		close(capt_fd);
		exit(1);
	}

	printf("Initialized display\n");	


#if 0
	if (ioctl(preview_fd, PREV_DUMP_HW_CONFIG, &level) < 0) {
		perror("Error in debug ioctl\n");
		cleanup_capture(capt_fd);
		cleanup_display(display_fd);
		close(preview_fd);
		close(rsz_fd);
		exit(1);
	} 
#endif

	while (!quit)
	{
		unsigned long temp;

		CLEAR(cap_buf);
		CLEAR(disp_buf);

try1:
		disp_buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		disp_buf.memory = V4L2_MEMORY_USERPTR;
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

		temp = cap_buf.m.userptr;
		if (disp_second_output) {
			cap_buf.m.userptr = disp_buf.m.userptr - second_output_offset;
			disp_buf.m.userptr = temp + second_output_offset;
		} else {
			cap_buf.m.userptr = disp_buf.m.userptr;
			disp_buf.m.userptr = temp;
		}
		//printf("disp_buf.m.userptr = %x\n", disp_buf.m.userptr); 

		ret = ioctl(capt_fd, VIDIOC_QBUF, &cap_buf);
		if (ret < 0) {
			perror("VIDIOC_QBUF for capture failed\n");
			return ret;
		}
		
		ret = ioctl(display_fd, VIDIOC_QBUF, &disp_buf);
		if (ret < 0) {
			perror("VIDIOC_QBUF for display failed\n");
			return ret;
		}
		if (captFrmCnt == 0)
			prev_ts = (cap_buf.timestamp.tv_sec*1000000) + cap_buf.timestamp.tv_usec;
		else {
			curr_ts = (cap_buf.timestamp.tv_sec*1000000) + cap_buf.timestamp.tv_usec;
			fp_period = curr_ts - prev_ts;
			if (captFrmCnt == 1) {
				fp_period_max = fp_period_min = fp_period_average = fp_period;
			}
			else {
				/* calculate jitters and average */
				if (fp_period > fp_period_max)
					fp_period_max = fp_period;
				if (fp_period < fp_period_min)
					fp_period_min = fp_period;
				
				fp_period_average =
					((fp_period_average * captFrmCnt) +
					fp_period)/(captFrmCnt + 1); 
			}
			prev_ts = curr_ts;
		}

		captFrmCnt++;
		
		if (printfn) {
			printf("frame:%5u, ", captFrmCnt);
			printf("buf.timestamp:%lu:%lu\n",
				cap_buf.timestamp.tv_sec, cap_buf.timestamp.tv_usec);
		}
		if (captFrmCnt > 5000)
			break;

	}
	printf("Cleaning capture\n");
	cleanup_capture(capt_fd);
	printf("Cleaning display\n");
	cleanup_display(display_fd);
	printf("Cleaning display - end\n");
	close(preview_fd);
	printf("closing preview- end\n");
	close(rsz_fd);
	printf("closing resize - end\n");
	exit(0);
}

