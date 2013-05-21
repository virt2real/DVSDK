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
**|         Copyright (c) 1998-2009 Texas Instruments Incorporated           |**
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
**|                                                                          |**
**+--------------------------------------------------------------------------+**
*******************************************************************************/
/* saDisplay.c
 *
 *
 * This is a sample application to show the display functionality
 * The app puts a moving horizontal bar on the display device in various
 * shades of colors. It displays 1080P@60 mode on the component output.
 * With just the change in the STD and OUTPUTs, the application
 * be made operate in any supported output or standard.
 */
 /******************************************************************************
  Header File Inclusion
 ******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>
#include <media/davinci/videohd.h>
/******************************************************************************
 Macros
 MAX_BUFFER     : Changing the following will result different number of
		  instances of buf_info structure.
 DISPLAY_OUTPUT	: Name of the output interface
 ******************************************************************************/
#define MAX_BUFFER	(1)
#define DISPLAY_OUTPUT	"Component"

static int display_fd = 0;
static char display_dev_name[20] = {"/dev/video2"};

struct buf_info {
	int index;
	unsigned int length;
	char *start;
};

static struct buf_info display_buff_info[MAX_BUFFER];
static int numbuffers = MAX_BUFFER;

/******************************************************************************
                        Function Definitions
 ******************************************************************************/
static int releaseDisplay();
static int startDisplay();
static int stopDisplay();
static void *getDisplayBuffer();
static int putDisplayBuffer( void *addr);
int app_main();

/*
        This routine unmaps all the buffers
        This is the final step.
*/
static int releaseDisplay()
{
	int i;
	for (i = 0; i < numbuffers; i++) {
		munmap(display_buff_info[i].start,
			display_buff_info[i].length);
		display_buff_info[i].start = NULL;
	}
	close(display_fd);
	display_fd = 0;
	return 0;
}
/*
	Starts Streaming
*/
static int startDisplay()
{
	int a = V4L2_BUF_TYPE_VIDEO_OUTPUT, ret, i;
	ret = ioctl(display_fd, VIDIOC_STREAMON, &a);
	if (ret < 0) {
		perror("VIDIOC_STREAMON\n");
		return -1;
	}
	return 0;
}

/*
 Stops Streaming
*/
static int stopDisplay()
{
	int ret, a = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(display_fd, VIDIOC_STREAMOFF, &a);
	return ret;
}

/*
	Does a DEQUEUE and gets/returns the address of the
	dequeued buffer
*/
static void *getDisplayBuffer()
{
	int ret, i;
	struct v4l2_buffer buf;
	memset(&buf, 0, sizeof(buf));
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(display_fd, VIDIOC_DQBUF, &buf);
	if (ret < 0) {
		perror("VIDIOC_DQBUF\n");
		return NULL;
	}
	return display_buff_info[buf.index].start;
}

/*
	Takes the adrress, finds the appropriate index
	of the buffer, and QUEUEs the buffer to display
	If this part is done in the main loop,
	there is no need of this conversionof address
	to index as both are available.
*/
static int putDisplayBuffer( void *addr)
{
	struct v4l2_buffer buf;
	int i, index = 0;
	int ret;
	if (addr == NULL)
		return -1;
	memset(&buf, 0, sizeof(buf));

	for (i = 0; i < numbuffers; i++) {
		if (addr == display_buff_info[i].start) {
			index = display_buff_info[i].index;
			break;
		}
	}
	buf.m.offset = (unsigned long) addr;
	buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf.memory = V4L2_MEMORY_MMAP;
	buf.index = index;
	ret = ioctl(display_fd, VIDIOC_QBUF, &buf);
	return ret;
}

static void usage()
{
	printf("Usage: saDisplay -f <input YUV file> -d <display standard>\n");
	printf("Display Standards:\n");
	printf("\t\t\t0 => NTSC\n");
	printf("\t\t\t1 => PAL\n");
	printf("\t\t\t2 => 525P/60\n");
	printf("\t\t\t3 => 625P/60\n");
	printf("\t\t\t4 => 720P/60\n");
	printf("\t\t\t5 => 720P/50\n");
	printf("\t\t\t6 => 1080I/60\n");
	printf("\t\t\t7 => 1080I/50\n");
	printf("\t\t\t8 => 1080P/50\n");
	printf("\t\t\t9 => 1080P/60\n");
}

int main(int argc, char *argv[])
{
	int mode = O_RDWR;
        struct v4l2_requestbuffers reqbuf;
        v4l2_std_id stdid;
        struct v4l2_buffer buf;
        struct v4l2_format fmt;
	int i = 0, j = 0, l=0,kount=0, d;
	void *displaybuffer;
	int counter = 0;
	int ret = 0;
	struct v4l2_output output;
	int dispheight, disppitch, dispwidth, sizeimage;
	int color = 0;
	char output_name[30] = DISPLAY_OUTPUT;
	char filename[30];
	v4l2_std_id output_std;
	char shortoptions[] = "d:f:?";
	FILE *fptr;

	/* by default use composite */
	for (;;) {
		d = getopt_long(argc, argv, shortoptions, (void *)NULL, &index);
		if (-1 == d)
			break;
		switch (d) {
		case 'f':
			strcpy(filename, optarg);
			break;
		case 'd':
			switch(atoi(optarg)) {
			case 0:
				output_std = V4L2_STD_NTSC;
				break;
			case 1:
				output_std = V4L2_STD_PAL;
				break;
			case 2:
				output_std = V4L2_STD_525P_60;
				break;
			case 3:
				output_std = V4L2_STD_625P_50;
				break;
			case 4:
				output_std = V4L2_STD_720P_60;
				break;
			case 5:
				output_std = V4L2_STD_720P_50;
				break;
			case 6:
				output_std = V4L2_STD_1080I_60;
				break;
			case 7:
				output_std = V4L2_STD_1080I_50;
				break;
			case 8:
				output_std = V4L2_STD_1080P_50;
				break;
			default:
			case 9:
				output_std = V4L2_STD_1080P_60;
				break;
			}
			break;
		default:
			usage();
			exit(1);
		}
	}

	fptr = fopen(filename, "r");
	if (!fptr) {
		printf("Unable to open YUV input file %s\n", filename);
		return -1;
	}

	/* open display channel */
        display_fd = open((const char *)display_dev_name, mode);
        if(display_fd == -1) {
		printf("failed to open display device\n");
		return -1;
        }

	output.index = 0;
	do {
		printf("Output Index %d\n", output.index);
		ret = ioctl(display_fd, VIDIOC_ENUMOUTPUT, &output);
		if (ret < 0) {
			perror("VIDIOC_ENUMOUTPUT\n");
			close(display_fd);
			return -1;
		}
		output.index ++;
	} while(0 == strcmp(output.name, output_name));

	/* Set the Component output on the display. 1080P mode is only
	 * supported on the the component output. */
	ret = ioctl(display_fd, VIDIOC_S_OUTPUT, &output.index);
	if (ret < 0) {
		perror("VIDIOC_S_OUTPUT\n");
		close(display_fd);
		return -1;
	}

	ret = ioctl(display_fd, VIDIOC_S_STD, &output_std);
	if (ret < 0) {
		perror("VIDIOC_S_STD\n");
		close(display_fd);
		return -1;
	}

	/*
	Now for the buffers.Request the number of buffers needed and
	the kind of buffers(User buffers or kernel buffers
	for memory mapping).
	Please note that the return value in the reqbuf.count
	might be lesser than numbuffers under some low memory
	circumstances
	*/

        reqbuf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
        reqbuf.count = numbuffers;
        reqbuf.memory = V4L2_MEMORY_MMAP;

        ret = ioctl(display_fd, VIDIOC_REQBUFS, &reqbuf);
        if (ret<0) {
                printf("Could not allocate the buffers\n");
                return -1;
        }
        /*
	Now map the buffers to the user space so the app can write
	on to them( This is for driver buffers and not for User
	pointers).This is done in two stages:
	1. Query for the buffer info like the phys address
	2. mmap the buffer to user space.

	This information anout the buffers is currently stored in
	a user level data structue
	*/

	numbuffers = reqbuf.count;
        for(i = 0 ; i < reqbuf.count ; i ++) {
		/* query */
                buf.index = i;
                buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
                buf.memory = V4L2_MEMORY_MMAP;
                ret = ioctl(display_fd, VIDIOC_QUERYBUF, &buf);
                if (ret < 0) {
                        printf("quering for buffer info failed\n");
                        return -1;
                }
		/* mmap */
                display_buff_info[i].length = buf.length;
                display_buff_info[i].index = i;
                display_buff_info[i].start =
                        mmap(NULL, buf.length, PROT_READ | PROT_WRITE,
                                MAP_SHARED, display_fd, buf.m.offset);
                        memset(display_buff_info[i].start,0x80,buf.length);

                if ((unsigned int) display_buff_info[i].
                        start == MAP_SHARED) {
                        printf("Cannot mmap = %d buffer\n", i);
                        return -1;
                }
		/*
		After mapping each buffer, it is a good
		idea to first "zero" them out.
		Here it is being set to a mid grey-scale
		Y=0x80, Cb=0x80, Cr=0x80
		*/
		memset(display_buff_info[i].start,0x80,buf.length);
        }

	/*
	It is necessary for applications to know about the
	buffer chacteristics that are set by the driver for
	proper handling of buffers
	These are : width,height,pitch and image size
	*/
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(display_fd, VIDIOC_G_FMT, &fmt);
        if(ret<0){
                printf("Get Format failed\n");
                return -1;
	}
	dispheight = fmt.fmt.pix.height;
	disppitch = fmt.fmt.pix.bytesperline;
	dispwidth = fmt.fmt.pix.width;
	sizeimage = fmt.fmt.pix.sizeimage;

	/*
	Queue all the buffers for the initial pruning
	*/

	fread(display_buff_info[0].start, disppitch * dispheight, 1, fptr);
	fread(display_buff_info[0].start + sizeimage/2, disppitch * dispheight, 1, fptr);
        for (i = 0; i < reqbuf.count; i++) {
                buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
                buf.memory = V4L2_MEMORY_MMAP;
                buf.index = i;
		memcpy(display_buff_info[i].start, display_buff_info[0].start, sizeimage);
                ret = ioctl(display_fd, VIDIOC_QBUF, &buf);
                if (ret < 0) {
                        perror("VIDIOC_QBUF\n");
                        return -1;
                }
        }

	fclose(fptr);


	ret = startDisplay();
	if(ret < 0) {
		printf("Error in starting display\n");
		return ret;
	}

	/*
		Get display buffer
	*/
	displaybuffer = getDisplayBuffer();
	if(NULL == displaybuffer) {
		printf("Error in getting the  display buffer\n");
		return ret;
	}

	/* Now queue it back to display it */
	ret = putDisplayBuffer(displaybuffer);
	if(ret < 0) {
		printf("Error in putting the display buffer\n");
		return ret;
	}

	printf("Hit return to stop display..\n");
	getchar();

	stopDisplay();

	/* open display channel */
	releaseDisplay();

	return ret;
}
