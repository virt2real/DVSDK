/*
 * display.c
 *
 * Display application used to streamon and streamoff.
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
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <getopt.h>
#include <sys/mman.h>
#include <sys/time.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>
#include "cmem.h"
char dev_name[2][20] = { "/dev/video2", "/dev/video3" };

int frame_no;
#define MAX_WIDTH  1920
#define MAX_HEIGHT  1080
#define BYTESPERLINE 2

#define NUM_BUF	3
char in_buf[MAX_WIDTH*MAX_HEIGHT*BYTESPERLINE];
char temp_buf[MAX_WIDTH*MAX_HEIGHT*BYTESPERLINE];

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

#define IS_VALID_CHANNEL(ch)  (((ch) == 0) || ((ch) == 1))

void usage()
{
	printf("Usage: display [OPTIONS]\n");
	printf("Options:\n");
	printf("\t-f\tName of the input file\n");
	printf("\t-c\tDisplay channel number [DEFAULT 0 without -c]\n");
	printf("\t-w\tWidth of the image to display [ DEFAULT 720 without -w]\n");
	printf("\t-h\tHeight of the image to display [DEFAULT 480 without -h]\n");
	printf("\t-t\tFormat of the output file\n");
	printf("\t\t\t0 => UYVY format [DEFAULT without -t]\n");
	printf("\t\t\t1 => YUV 420 Semi-Planar format\n");
}

#define ALIGN(x, y)	(((x + (y-1))/y)*y)

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

struct buf_info display_buffer[NUM_BUF];

/*******************************************************************************
 * allocate_user_buffers() allocate buffer using CMEM
 ******************************************************************************/
int allocate_user_buffers(int buf_size)
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
	printf("Allocating display buffer :buf size = %d \n", buf_size);
	
	for (i=0; i < NUM_BUF; i++) {
		display_buffer[i].user_addr = CMEM_alloc(buf_size, &alloc_params);
		if (display_buffer[i].user_addr) {
			display_buffer[i].phy_addr = CMEM_getPhys(display_buffer[i].user_addr);
			if (0 == display_buffer[i].phy_addr) {
				printf("Failed to get phy cmem buffer address\n");
				return -1;
			}
		} else {
			printf("Failed to allocate cmem buffer\n");
			return -1;
		}
		printf("Got %p from CMEM, phy = %p\n", display_buffer[i].user_addr,
			(void *)display_buffer[i].phy_addr);
	}

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

int main(int argc, char *argv[])
{
	char shortoptions[] = "c:f:t:w:h:";
	int mode = O_RDWR, c, ret,ret1, j, i,k;
	int index=0, found = 0;
	int fd, ch_no = 0, numbuffers = 3, a;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	struct buf_info *buff_info;
	struct v4l2_format fmt;
	void *addr1;
	int counter=0;
	static int captFrmCnt = 0;
	v4l2_std_id std;
	struct v4l2_crop crop;
	char *src, *dest;
	char in_file[100] = "";
	FILE *inp_f, *out_f;
	int width = 720 , height = 480, size, expected_size;
	int format = 0; //UYVY
	char temp;

	for (;;) {
		c = getopt_long(argc, argv, shortoptions, (void *) NULL,
				&index);
		if (-1 == c)
			break;
		switch (c) {
			case 'c':
				ch_no = atoi(optarg);
				break;
			case 'f':
				strcpy(in_file,optarg);
				break;
			case 'w':
				width = atoi(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 't':
				format = atoi(optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	if (!IS_VALID_CHANNEL(ch_no)) {
		printf("Invalid channel id");
		exit(0);
	}

	if (!strcmp(in_file, "")) {
		printf("Use -f option to provide an input file\n"
			"An example input is located with the sources: "
				"video_720p (1280x720 UYVY format)\n");
		usage();
		exit(1);
	}

	printf("displaying in_file = %s with width = %d, height = %d\n",in_file,width,height);

	
	expected_size = width * height * BYTESPERLINE;


	bzero (&fmt, sizeof(fmt));
	if (format == 1) {
		// 420 output display. round width to next 32 byte boundary
		width = (width + 31) & (~31);	
		printf("width = %d\n", width);
		expected_size = (width * height) + (width * height / 2);
	}

	if (allocate_user_buffers(ALIGN(expected_size, 4096)) < 0) {
		printf("Unable to allocate user buffer\n");
		exit(1);
	}

	inp_f = fopen(in_file, "rb");
	if (inp_f == NULL) {
		perror("Error in opening input file \n");
		exit(1);
	}

	size = fread(in_buf,1, expected_size, inp_f);

	printf("read size = %d, expected size = %d\n", size, expected_size);
	if (size < expected_size) {
		printf("mismatch between file size and  expected size\n");
		printf("size = %d, expected size = %d\n", size, expected_size);
		fclose(inp_f);
		exit(1);
	}
	fclose(inp_f);

	/* Now choose the display output mode based on resolution of the image */
	if (width <= 720 && height <= 480) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE) < 0) {
			printf("Unable to change display output to %s\n",
				DISPLAY_INTERFACE_COMPOSITE);
			fclose(inp_f);
			exit(1);
		}
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_NTSC) < 0) {
			printf("Unable to change display mode to %s\n",
				DISPLAY_MODE_NTSC);
			fclose(inp_f);
			exit(1);
		}
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;

	} else if (width <= 720 && height <= 576) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPOSITE) < 0) {
			printf("Unable to change display output to %s\n",
				DISPLAY_INTERFACE_COMPOSITE);
			fclose(inp_f);
			exit(1);
		}
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_PAL) < 0) {
			printf("Unable to change display mode to %s\n",
				DISPLAY_MODE_PAL);
			fclose(inp_f);
			exit(1);
		}
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else if (width <= 1280 && height <= 720) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPONENT) < 0) {
			printf("Unable to change display output to %s\n",
				DISPLAY_INTERFACE_COMPONENT);
			fclose(inp_f);
			exit(1);
		}
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_720P) < 0) {
			printf("Unable to change display mode to %s\n",
				DISPLAY_MODE_720P);
			fclose(inp_f);
			exit(1);
		}
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	} else if (width <= 1920 && height <= 1080) {
		if (change_sysfs_attrib(ATTRIB_OUTPUT, DISPLAY_INTERFACE_COMPONENT) < 0) {
			printf("Unable to change display output to %s\n",
				DISPLAY_INTERFACE_COMPONENT);
			fclose(inp_f);
			exit(1);
		}
		if (change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_1080I) < 0) {
			printf("Unable to change display mode to %s\n",
				DISPLAY_MODE_1080I);
			fclose(inp_f);
			exit(1);
		}
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	} else {
		printf("Unable to display this resolution image\n");
		exit(1);
	}
	bzero((void *)&req,sizeof(struct v4l2_requestbuffers));
	fd = open((const char *)dev_name[ch_no], mode);
	if (fd <= 0) {
		printf("Cannot open = %s device\n", dev_name[ch_no]);
		exit(1);
	}

	
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	if (format == 0) {
		width += 15;
		width &= (~15);
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;	
	}
	else {
		width += 31;
		width &= (~31);
		fmt.fmt.pix.bytesperline = width;
		fmt.fmt.pix.sizeimage = width * height * 1.5;
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;	
	}
	fmt.fmt.pix.height = height;
	fmt.fmt.pix.width = width;
	ret = ioctl(fd, VIDIOC_S_FMT, &fmt);
	if (ret) {
		perror("VIDIOC_S_FMT\n");
		close(fd);
		exit(1);
	}

	
	req.count = NUM_BUF;
	req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	req.memory = V4L2_MEMORY_USERPTR;

	ret = ioctl(fd, VIDIOC_REQBUFS, &req);
	if (ret) {
		perror("cannot allocate memory\n");
		close(fd);
		exit(1);
	}

	crop.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	crop.c.top  = 0;
	crop.c.left = 0;
	crop.c.width= width;
	crop.c.height= height;

	ret = ioctl(fd, VIDIOC_S_CROP, &crop);
	if (ret) {
		perror("VIDIOC_S_CROP\n");
		close(fd);
		exit(0);
	}
	
	
	/* Enqueue buffers */
	for (i = 0; i < req.count; i++)
   	{
		memcpy(display_buffer[i].user_addr, in_buf, size);
		bzero(&buf, sizeof(struct v4l2_buffer));
		buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		buf.index = i;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.length = ALIGN(size, 4096);
		buf.m.userptr = display_buffer[i].user_addr;
		ret = ioctl(fd, VIDIOC_QBUF, &buf);
		//memset(buff_info[i].start,0xff,buff_info[i].length);
		if (ret)
        	{
			perror("VIDIOC_QBUF\n");
			close(fd);
			exit(1);
		}
	}



	a = 0;
	ret = ioctl(fd, VIDIOC_STREAMON, &a);
	if (ret < 0)
    	{
		perror("VIDIOC_STREAMON\n");
		close(fd);
		exit(1);
	}

	getchar();
	ret = ioctl(fd, VIDIOC_STREAMOFF, &a);
	if (ret) {
		perror("VIDIOC_STREAMOFF\n");
		close(fd);
		exit(1);
	}
	
	close(fd);
	return 0;
}
