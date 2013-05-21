/*
 * do_resize_422.c
 *
 * Example showing how to use Resizer in One shot mode to do Resize and
 * also format conversion from UYVY to YUV420 Semi planar format (aka
 * NV12 in v4l2 API)
 *
 * The following IP configuration used for this use case
 *
 * SDRAM -> IPIPEIF -> Resizer -> SDRAM
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
#include <string.h>
#include <sys/mman.h>
#include <getopt.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <media/davinci/imp_previewer.h>
#include <media/davinci/imp_resizer.h>
#include <media/davinci/dm365_ipipe.h>

#include "cmem.h"

char dev_name_prev[1][30] = {"/dev/davinci_previewer"};
char dev_name_rsz[1][30] = {"/dev/davinci_resizer"};

void usage()
{
	printf("Usage: do_resize [OPTIONS]\n");
	printf("Options:\n");
	printf("\t-i\t1280x720 UYVY input file\n");
	printf("\t-w\tWidth of the output image (stored in output1.yuv)\n");
	printf("\t-h\tHeight of the output image (stored in output1.yuv)\n");
	printf("\t-x\tCreate a second output image of 640x480 resolution\n");
	printf("\t\t\t0 => Do not create second image [DEFAULT without -x]\n");
	printf("\t\t\t1 => Create a second image\n");
	printf("\t-t\tFormat of the output file\n");
	printf("\t\t\t0 => UYVY format [DEFAULT without -t]\n");
	printf("\t\t\t1 => YUV 420 Semi-Planar format\n");

}
#define MAX_WIDTH  1920
#define MAX_HEIGHT  1080
#define BYTESPERLINE 2
#define INPUT_HEIGHT 720 
#define INPUT_WIDTH 1280 

#define BUF_SIZE ((1280*720) + (1280*360) + 32)
char in_buf[MAX_WIDTH*MAX_HEIGHT*BYTESPERLINE];

#define OUTPUT1_FILE "./output1.yuv"
#define OUTPUT2_FILE "./output2.yuv"
#define ALIGN(x, y)	(((x + (y-1))/y)*y)

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

/* For input and output frame */
struct buf_info input_buffer;
struct buf_info output1_buffer;
struct buf_info output2_buffer;

/*******************************************************************************
 * allocate_user_buffers() allocate buffer using CMEM
 ******************************************************************************/
int allocate_user_buffers(int in_buf_size, int out1_buf_size, int out2_buf_size)
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
	printf("Allocating input buffer :buf size = %d \n", in_buf_size);
	
	input_buffer.user_addr = CMEM_alloc(ALIGN(in_buf_size,4096), &alloc_params);
	if (input_buffer.user_addr) {
		input_buffer.phy_addr = CMEM_getPhys(input_buffer.user_addr);
		if (0 == input_buffer.phy_addr) {
			printf("Failed to get phy cmem buffer address\n");
			return -1;
		}
	} else {
		printf("Failed to allocate cmem buffer\n");
		return -1;
	}
	printf("Got %p from CMEM, phy = %p\n", input_buffer.user_addr,
			(void *)input_buffer.phy_addr);

	printf("Allocating output1 buffer :buf size = %d \n", out1_buf_size);
	output1_buffer.user_addr = CMEM_alloc(ALIGN(out1_buf_size, 4096), &alloc_params);
	if (output1_buffer.user_addr) {
		output1_buffer.phy_addr = CMEM_getPhys(output1_buffer.user_addr);
		if (0 == output1_buffer.phy_addr) {
			printf("Failed to get phy cmem buffer address\n");
			return -1;
		}
	} else {
		printf("Failed to allocate cmem buffer\n");
		return -1;
	}
	printf("Got %p from CMEM, phy = %p\n", output1_buffer.user_addr,
		(void *)output1_buffer.phy_addr);

	printf("Allocating output2 buffer :buf size = %d \n", out2_buf_size);
	output2_buffer.user_addr = CMEM_alloc(ALIGN(out2_buf_size,4096), &alloc_params);
	if (output2_buffer.user_addr) {
		output2_buffer.phy_addr = CMEM_getPhys(output2_buffer.user_addr);
		if (0 == output2_buffer.phy_addr) {
			printf("Failed to get phy cmem buffer address\n");
			return -1;
		}
	} else {
			printf("Failed to allocate cmem buffer\n");
			return -1;
	}
	printf("Got %p from CMEM, phy = %p\n", output2_buffer.user_addr,
			(void *)output2_buffer.phy_addr);
	return 0;
}

int main(int argc, char *argp[])
{
	char shortoptions[] = "i:w:h:t:x:";
	int mode = O_RDWR,c,ret = 0,index;
	int preview_fd, resizer_fd = 0, dev_idx;
	unsigned long oper_mode, user_mode, driver_mode;
	struct prev_channel_config prev_chan_config;
	struct prev_single_shot_config prev_ss_config; // single shot mode configuration
	struct rsz_channel_config rsz_chan_config; // resizer channel config
	struct rsz_single_shot_config rsz_ss_config; // single shot mode configuration
	struct prev_cap cap;
	struct prev_module_param mod_param;
	struct prev_wb wb_params;
	struct imp_reqbufs req_buf;
	struct imp_buffer buf_in[3];
	struct imp_buffer buf_out1[3];
	struct imp_buffer buf_out2[3];
	struct imp_convert convert;
	int i,j;
	char in_file[100] = "";
	FILE *inp_f = NULL, *outp1_f = NULL, *outp2_f = NULL;
	int width = INPUT_WIDTH, height = INPUT_HEIGHT, size;
	int out_format=0;
	unsigned long level;
	short byte=0;
	char out420_buf[BUF_SIZE];
	char *src, *dest;
	int second_output = 0;
	int output1_size, output2_size;

	for(;;) {
		c = getopt_long(argc, argp, shortoptions, NULL, (void *)&index);
		if(-1 == c)
			break;
		switch(c) {
			case 'i':
				strcpy(in_file,optarg);
				break;
			case 'w':
				width = atoi(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 'x':
				second_output = atoi(optarg);
				break;
			case 't':
				out_format = atoi(optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	if (!strcmp(in_file, "")) {
		printf("Use -i option to provide an 1280x720 UYVY input file\n"
				"An example input is located with the sources: "
				"video_720p\n");
		usage();
		exit(1);
	}

	printf("doing resize on in_file = %s and writing out to out_file1 = %s out_file2 = %s\n",
		in_file,OUTPUT1_FILE, OUTPUT2_FILE);
	oper_mode = IMP_MODE_SINGLE_SHOT;

	printf("starting\n");
	inp_f = fopen(in_file, "rb");
	if (inp_f == NULL) {
		perror("Error in opening input file \n");
		ret = -1;
		goto out;
	}
	outp1_f = fopen(OUTPUT1_FILE, "wb");
	if (outp1_f == NULL) {
		perror("Error in opening output file \n");
		ret = -1;
		goto out;
	}

	if (second_output) {
		outp2_f = fopen(OUTPUT2_FILE, "wb");
		if (outp2_f == NULL) {
			perror("Error in opening output file \n");
			ret = -1;
			goto out;
		}
	}

	size = fread(in_buf,1, (INPUT_WIDTH * INPUT_HEIGHT * BYTESPERLINE), inp_f);

	output1_size = width * height * 2;
	output2_size = 640 * 480 * 2;

	if (out_format) {
		output1_size = width * height * 1.5;
		output2_size = 640 * 480 * 1.5;
	}
		
	if (size != (INPUT_WIDTH * INPUT_HEIGHT * BYTESPERLINE)) {
		perror("mismatch between file size and  INPUT_WIDTH * INPUT_HEIGHT * 2\n");
		ret = -1;
		goto out;
	}

	/* Open the resizer */
	printf("Configuring resizer in the chain mode\n");
	printf("Opening resizer device, %s\n",dev_name_rsz[0]);
	resizer_fd = open((const char *)dev_name_rsz[0], mode);
	if(resizer_fd <= 0) {
		printf("Cannot open resizer device\n");
		ret = -1;
		goto out;
	}

	if (ioctl(resizer_fd,RSZ_S_OPER_MODE, &oper_mode) < 0) {
		perror("Can't set operation mode\n");
		ret = -1;
		goto out;
	}

	if (ioctl(resizer_fd,RSZ_G_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		ret = -1;
		goto out;
	}
	printf("RESIZER: Operating mode changed successfully to");
	if (oper_mode == IMP_MODE_SINGLE_SHOT) 
		printf(" %s", "Single Shot\n");
	else
		printf(" %s", "Continuous\n");

	printf("Setting default configuration in Resizer\n");
	bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = 0;
	rsz_chan_config.config = NULL; /* to set defaults in driver */
	if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration for single shot mode\n");
		ret = -1;
		goto out;
	}

	printf("default configuration setting in Resizer successfull\n");
	bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	rsz_chan_config.config = &rsz_ss_config;

	if (ioctl(resizer_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in getting resizer channel configuration from driver\n");
		ret = -1;
		goto out;
	}

	// in the chain mode only output configurations are valid
	// input params are set at the previewer
	rsz_ss_config.input.image_width = INPUT_WIDTH;
	rsz_ss_config.input.image_height = INPUT_HEIGHT;
	rsz_ss_config.input.ppln = rsz_ss_config.input.image_width + 8;
	rsz_ss_config.input.lpfr = rsz_ss_config.input.image_height + 10;
	rsz_ss_config.input.pix_fmt = IPIPE_UYVY;
	if (out_format)
		rsz_ss_config.output1.pix_fmt = IPIPE_YUV420SP;
	else
		rsz_ss_config.output1.pix_fmt = IPIPE_UYVY;
	rsz_ss_config.output1.enable = 1;
	rsz_ss_config.output1.width = width;
	rsz_ss_config.output1.height = height;
	rsz_ss_config.output2.enable = 0;
	if (second_output) {
		rsz_ss_config.output2.enable = 1;
		rsz_ss_config.output2.width = 640;
		rsz_ss_config.output2.height = 480;
		if (out_format)
			rsz_ss_config.output2.pix_fmt = IPIPE_YUV420SP;
		else
			rsz_ss_config.output2.pix_fmt = IPIPE_UYVY;
	}

	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration for single shot mode\n");
		ret = -1;
		goto out;
	}
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);

	// read again and verify
	if (ioctl(resizer_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in getting configuration from driver\n");
		ret = -1;
		goto out;
	}

	if (allocate_user_buffers(size, output1_size, output2_size) < 0) {
		perror("Error in allocating user buffers\n");
		ret = -1;
		goto out;
	}

	bzero(&convert,sizeof(convert));
	bzero(output1_buffer.user_addr, output1_size);
	memcpy(input_buffer.user_addr, in_buf, size);
	convert.in_buff.buf_type = IMP_BUF_IN;
	convert.in_buff.index = -1;
	convert.in_buff.offset = (unsigned int)input_buffer.user_addr;
	convert.in_buff.size = size;
	convert.out_buff1.buf_type = IMP_BUF_OUT1;
	convert.out_buff1.index = -1;
	convert.out_buff1.offset = (unsigned int)output1_buffer.user_addr;
	convert.out_buff1.size = output1_size;
	if (second_output) {
		bzero(output2_buffer.user_addr, output2_size);
		convert.out_buff2.buf_type = IMP_BUF_OUT2;
		convert.out_buff2.index = -1;
		convert.out_buff2.offset = (unsigned int)output2_buffer.user_addr;
		convert.out_buff2.size = output2_size;
	}
	if (ioctl(resizer_fd, RSZ_RESIZE, &convert) < 0) {
		perror("Error in doing preview\n");
		ret = -1;
		goto out;
	} 
	if (out_format)
		size = width * height * 1.5;
	else
		size = width * height * 2;

	printf("size = %d\n", size);

	if (fwrite(output1_buffer.user_addr,1,size,outp1_f) != (
			size)) {
		perror("Error in doing resize\n");
		ret = -1;
		goto out;
	} 

	if (second_output) {
		if (fwrite(output2_buffer.user_addr, 1, output2_size, outp2_f) != output2_size)
			perror("Error in writing to file\n");
	}

out:
	if (resizer_fd) {
		if (!close(resizer_fd))
			printf("resizer closed successfully\n");
		else
			printf("Error in closing resizer\n");
	}
	if (inp_f)
		fclose(inp_f);
	if (outp1_f)
		fclose(outp1_f);
	if (outp2_f)
		fclose(outp2_f);

	return ret;
}

