/*
 * capture-previewer-resizer-on-the-fly-bayer
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
#include <media/davinci/dm355_ccdc.h>
#include <media/davinci/imp_previewer.h>
#include <media/davinci/imp_resizer.h>
#include <media/davinci/dm355_ipipe.h>
#include "cmem.h"

#define DISPLAY_INTERFACE_COMPOSITE	"COMPOSITE"
#define DISPLAY_INTERFACE_COMPONENT	"COMPONENT1"
#define DISPLAY_MODE_PAL	"PAL"
#define DISPLAY_MODE_NTSC	"NTSC"
#define DISPLAY_MODE_720P	"720P-60"		
#define DISPLAY_MODE_1080I	"1080I-30"		
/* Standards and output information */
#define ATTRIB_MODE		"mode"
#define ATTRIB_OUTPUT		"output"

char dev_name_prev[1][30] = {"/dev/davinci_previewer"};
char dev_name_rsz[1][30] = {"/dev/davinci_resizer"};

#define APP_NUM_BUFS 6
#define CAPTURE_DEVICE  "/dev/video0"
//#define CAP_FORMAT1		(V4L2_STD_MT9T001_VGA_30FPS)
#define CAP_FORMAT1		(V4L2_STD_MT9T001_480p_30FPS)
#define V4L2VID0_DEVICE    "/dev/video2"
#define V4L2VID1_DEVICE    "/dev/video3"
#define CLEAR(x) memset (&(x), 0, sizeof (x))


#define ALIGN(x, y)	(((x + (y-1))/y)*y)

int buf_size = ALIGN((1920*1080*2), 4096);

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

struct buf_info capture_buffers[APP_NUM_BUFS];
struct buf_info display_buffers[APP_NUM_BUFS];

int flag = 0;
int loop_counter = 500;

static unsigned long long prev_ts;
static unsigned long long curr_ts;
static unsigned long fp_period_average;
static unsigned long fp_period_max;
static unsigned long fp_period_min;
static unsigned long fp_period;

int printfn = 1;
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

void usage()
{
	printf("Usage:capture_prev_rsz_onthe_fly\n");
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
	rsz_cont_config.en_output1 = 1;
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
	
	int preview_fd, ret;
	unsigned int oper_mode;
	struct prev_channel_config prev_chan_config;
	struct prev_continuous_config prev_cont_config; // continuous mode
	struct prev_cap cap;
	struct prev_module_param mod_param;
	struct prev_wb wb;
	struct prev_lum_adj lum_adj;
	struct prev_gamma gamma;
	struct prev_prefilter;
	

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
	
	prev_cont_config.input.gain = 512;
#if 0
	prev_cont_config.input.colp_elep= IPIPE_RED;
	prev_cont_config.input.colp_elop= IPIPE_GREEN_RED;
	prev_cont_config.input.colp_olep= IPIPE_GREEN_BLUE;
	prev_cont_config.input.colp_olop= IPIPE_BLUE;
#endif

/*
	B Gb
	Gr R
*/
#if 1
	prev_cont_config.input.colp_elep= IPIPE_BLUE;
	prev_cont_config.input.colp_elop= IPIPE_GREEN_BLUE;
	prev_cont_config.input.colp_olep= IPIPE_GREEN_RED;
	prev_cont_config.input.colp_olop= IPIPE_RED;
#endif
/*
	GB B 
	R GR
*/
#if 0
	prev_cont_config.input.colp_elep= IPIPE_GREEN_BLUE;
	prev_cont_config.input.colp_elop= IPIPE_BLUE;
	prev_cont_config.input.colp_olep= IPIPE_RED;
	prev_cont_config.input.colp_olop= IPIPE_GREEN_RED;
#endif

/* Gr R
   B Gb
*/
#if 0
	prev_cont_config.input.colp_elep= IPIPE_GREEN_RED;
	prev_cont_config.input.colp_elop= IPIPE_RED;
	prev_cont_config.input.colp_olep= IPIPE_BLUE;
	prev_cont_config.input.colp_olop= IPIPE_GREEN_BLUE;
#endif

	if (ioctl(preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0) {
		perror("Error in setting default configuration\n");
		close(preview_fd);
		return -1;
	}

	bzero(&prev_cont_config, sizeof (struct prev_continuous_config));
	// read again and verify
	if (ioctl(preview_fd, PREV_G_CONFIG, &prev_chan_config) < 0) {
		perror("Error in getting configuration from driver\n");
		close(preview_fd);
		return -1;
	}

	cap.index=0;
	while (1) {
		ret = ioctl(preview_fd , PREV_ENUM_CAP, &cap);
		if (ret < 0) {
			break;	
		}
		// find the defaults for this module
	
		strcpy(mod_param.version,cap.version);
		mod_param.module_id = cap.module_id;
		// try set parameter for this module
		if (cap.module_id == PREV_WB) {
			wb.dgn.integer = 2;
			wb.dgn.decimal = 0;
			wb.gain_r.integer = 2;
			wb.gain_r.decimal = 0x10;
			wb.gain_gr.integer = 1;
			wb.gain_gr.decimal = 0x70;
			wb.gain_gb.integer = 1;
			wb.gain_gb.decimal = 0x70;
			wb.gain_b.integer = 2;
			wb.gain_b.decimal = 0x30;
			mod_param.len = sizeof(struct prev_wb);
			mod_param.param = &wb;
		} else if (cap.module_id == PREV_LUM_ADJ) {
			lum_adj.brightness = 0x10;
			lum_adj.contast = 0x10;
			mod_param.len = sizeof (struct prev_lum_adj);
			mod_param.param = &lum_adj;
		} else if ((cap.module_id == PREV_GAMMA) && flag) {
			printf("Setting gamma for %s\n", cap.module_name);
			bzero((void *)&gamma, sizeof (struct prev_gamma));
			gamma.bypass_r = 0;
			gamma.bypass_b = 0;
			gamma.bypass_g = 0;
			gamma.tbl_sel = IPIPE_GAMMA_TBL_ROM;
			mod_param.len = sizeof (struct prev_gamma);
			mod_param.param = &gamma;
		}
		else {
			// using defaults
			printf("Setting default for %s\n", cap.module_name);
			mod_param.param = NULL;
		}
		if (ioctl(preview_fd, PREV_S_PARAM, &mod_param) < 0) {
			perror("Error in Setting wb params from driver\n");
			close(preview_fd);
			return -1;
		}
		cap.index++;
	}	
	printf("previewer initialized\n");
	return preview_fd;
}

static int configCCDCraw(int capt_fd)
{
	struct ccdc_config_params_raw raw_params = {
       .datasft = 2,
       .mfilt1 = CCDC_NO_MEDIAN_FILTER1,
       .mfilt2 =  CCDC_NO_MEDIAN_FILTER2,
       .med_filt_thres = 0,
       //.ccdc_offset = 0,
       .lpf_enable = 0,
       .alaw = {
          .enable = 0,
          .gama_wd = 0},
       .blk_clamp = {
          .enable = 0,
          .sample_pixel = 1,
          .start_pixel = 0,
          .dc_sub = 0},
       .blk_comp = {
          .b = 0,
          .gb = 0,
          .gr = 0,
          .r = 0},
       .vertical_dft = {
          .ver_dft_en = 0},
       .csc = {
          .enable = 0},

/* Gr R
   B Gb
*/
#if 1
	   .col_pat_field0 = {
		  .elep = CCDC_GREEN_RED,
		  .elop = CCDC_RED,
		  .olep = CCDC_BLUE,
		  .olop = CCDC_GREEN_BLUE},
	   .col_pat_field1 = {
		  .elep = CCDC_GREEN_RED,
		  .elop = CCDC_RED,
		  .olep = CCDC_BLUE,
		  .olop = CCDC_GREEN_BLUE}
#endif
/*
   B Gb
   Gr R
*/
#if 0
	   .col_pat_field0 = {
		  .elep = CCDC_BLUE,
		  .elop = CCDC_GREEN_BLUE,
		  .olep = CCDC_GREEN_RED,
		  .olop = CCDC_RED},
	   .col_pat_field1 = {
		  .elep = CCDC_BLUE,
		  .elop = CCDC_GREEN_BLUE,
		  .olep = CCDC_GREEN_RED,
		  .olop = CCDC_RED},
#endif
    };

    if (-1 == ioctl(capt_fd, VPFE_CMD_S_CCDC_RAW_PARAMS, &raw_params)) {
	perror("error-InitDevice:ioctl:VPFE_CMD_S_CCDC_RAW_PARAMS:");
	return -1;
    }
    return 0;
}
	
static int SetDataFormat(int fdCapture, int width, int height)
{
	v4l2_std_id ipipe_std, cur_std;
	struct v4l2_format fmt;
	struct v4l2_input input;
	int index;
	int ret;

	printf("SetDataFormat:setting std to %d\n", (int)cur_std);

	// first set the input
	input.type = V4L2_INPUT_TYPE_CAMERA;
	input.index = 0;
  	while (-EINVAL != ioctl(fdCapture, VIDIOC_ENUMINPUT, &input)) { 
		printf("input.name = %s\n", input.name);
		if (!strcmp(input.name, "Camera"))
			break;
		input.index++;
  	}

	if (-1 == ioctl (fdCapture, VIDIOC_S_INPUT, &input.index)) {
		perror("ioctl:VIDIOC_S_INPUT failed\n");
		return -1;
	}

  	printf ("InitDevice:ioctl:VIDIOC_S_INPUT, selected input\n");
	printf("\nCalling configCCDCraw()\n");
	ret = configCCDCraw(fdCapture);
	if (ret < 0) {
		perror("error-configCCDCraw");
		return -1;
	} else {
		printf("\nconfigCCDCraw Done\n");
	}

	printf("SetDataFormat:requesting width:%d height:%d\n", width, height);
	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	fmt.fmt.pix.field = V4L2_FIELD_NONE;
	if (-1 == ioctl(fdCapture, VIDIOC_S_FMT, &fmt)) {
		perror("SetDataFormat:ioctl:VIDIOC_S_FMT");
		return -1;
	} else
		printf("\nS_FMT Done\n");

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

int init_camera_capture(int width, int height)
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
	if (SetDataFormat(capt_fd, width, height) < 0) {
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
		buf.m.userptr = (unsigned long)display_buffers[i].user_addr;
		printf("Queing buffer:%d\n", i);

		if (-1 == ioctl(fd_vid1, VIDIOC_QBUF, &buf))
			printf("start_capture_streaming:ioctl:VIDIOC_QBUF:\n");
	}
	/* all done , get set go */
	type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	if (-1 == ioctl(fd_vid1, VIDIOC_STREAMON, &type))
		printf("start_capture_streaming:ioctl:VIDIOC_STREAMON:\n");

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
		strcpy(output, DISPLAY_INTERFACE_COMPOSITE);
		strcpy(mode, DISPLAY_MODE_NTSC);
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (width <= 720 && height <= 576) {
		strcpy(output, DISPLAY_INTERFACE_COMPOSITE);
		strcpy(mode, DISPLAY_MODE_PAL);
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (width <= 1280 && height <= 720) {
		strcpy(output, DISPLAY_INTERFACE_COMPONENT);
		strcpy(mode, DISPLAY_MODE_720P);
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if (width <= 1920 && height <= 1080) {
		strcpy(output, DISPLAY_INTERFACE_COMPONENT);
		strcpy(mode, DISPLAY_MODE_1080I);
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else {
		printf("Cannot display input video resolution width = %d, height = %d\n",
			width, height);
		return -1;
	}

	if (change_sysfs_attrib(ATTRIB_OUTPUT, output))
		return -1;
	if (change_sysfs_attrib(ATTRIB_MODE, mode))
		return -1;


	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;

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

	start_display_streaming(fdDisplay);
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

	for (i = 0; i < (APP_NUM_BUFS/2); i++) {
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
	char shortoptions[] = "w:h:t:f:";
	int mode = O_RDWR,c,ret,index;
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
	int captFrmCnt = 0;
	FILE *outp_f;
	struct v4l2_buffer cap_buf, disp_buf;
	 


	for(;;) {
		c = getopt_long(argc, argp, shortoptions, NULL, (void *)&index);
		if(-1 == c)
			break;
		switch(c) {
			/* output width & height */
			case 'w':
				width = atoi(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 't':
				flag = atoi(optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	outp_f = fopen("test_vga_1.bin", "wb");
	if (outp_f == NULL) {
		perror("Error in opening output file \n");
		exit(1);
	}

	if (allocate_user_buffers() < 0) {
		printf("Unable to Allocate user buffers\n");
		exit(1);
	}	

	// intialize resizer in continuous mode
	rsz_fd = init_resizer(user_mode);
	if (rsz_fd < 0) {
		exit(1);
		fclose(outp_f);
	}

	// initialize previewer in continuous mode
	preview_fd = init_previewer(user_mode);

	if (preview_fd < 0) {
		close(rsz_fd);
		fclose(outp_f);
		exit(1);
	}
	
	// intialize capture
	capt_fd = init_camera_capture(width,height);

	if (capt_fd < 0) {
		close(preview_fd);
		close(rsz_fd);
		fclose(outp_f);
		exit(1);
	}
	
	display_fd = init_display_device(0, width, height);
	if (display_fd < 0) {
		close(preview_fd);
		close(rsz_fd);
		close(capt_fd);
		fclose(outp_f);
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
		fclose(outp_f);
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
		cap_buf.m.userptr = disp_buf.m.userptr;
		disp_buf.m.userptr = temp;
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
		if (captFrmCnt > loop_counter)
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
	fclose(outp_f);
	exit(0);
}

