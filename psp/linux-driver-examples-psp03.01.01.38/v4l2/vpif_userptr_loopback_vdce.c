/*
 * vpif_userptr_loopback_cmem.c
 *
 * This is the sample to show DavinciHD capture and display functionality using
 * user pointer buffers. In this example, buffers are allocated using cmem
 * the allocated buffers are used as USERPTR for USERPTR IO on capture side
 * and display side.
 *
 * Flow: Capture -> Display
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
 /******************************************************************************
  Header File Inclusion
 ******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <errno.h>
#include <linux/videodev.h>
#include <linux/videodev2.h>
#include <media/davinci/videohd.h>
#include <linux/davinci_vdce.h>
/******************************************************************************
 Macros
 MAX_BUFFER     : Changing the following will result different number of 
		  instances of buf_info structure.
 BUFFER_HEIGHT	: This indicates maximum height of the image which is 
 		  captured or displayed.
 BUFFER_PITCH	: This indicates maximum widht of the image which is 
 		  captured or displayed.
 DISPLAY_DEVICE : This indicates device to be used for display
 MAXLOOPCOUNT	: This indicates number of frames to be captured and displayed
 ******************************************************************************/
#define MAX_BUFFER		(3)
#define BUFFER_PITCH		(1920)
#define BUFFER_HEIGHT		(1080)
#define DISPLAY_DEVICE		"/dev/video2"
#define MAXLOOPCOUNT		(1000)
#define VDCE_DEVICE		"/dev/DavinciHD_vdce"
#define OUTPUTNAME		"Component"
#define ISINTERLACED(std)       (((std) & V4L2_STD_1080I_60) ||\
				 ((std) & V4L2_STD_1080I_50) ||\
                                 ((std) & V4L2_STD_NTSC) ||\
                                 ((std) & V4L2_STD_PAL))

/******************************************************************************
 Declaration
 	Following structure is used to store information of the buffers which 
	are allocated using VDCE driver and mmaped in the user space.
 ******************************************************************************/
struct buf_info {
	int index;
	unsigned int length;
	char *start;
};

/******************************************************************************
 Globals
	Following variables stores file descriptors returned when opening 
	capture, display and vdce device.
	capture_buff_info and display_buff_info stores mmaped buffer 
	information of capture and display respectively.
	numbuffers is used to store number of buffers actually allocated by 
	the driver.
	outputidx is used to store index of the output to be selected in 
	display depending on the input detecting on the capture.
	capture_std is used to store detected standard.
 ******************************************************************************/

static struct buf_info capture_buff_info[MAX_BUFFER];
static struct buf_info display_buff_info[MAX_BUFFER];

/******************************************************************************
                        Function Definitions
 ******************************************************************************/
static int init_capture(int *capture_fd, int *numbuffers, int input_dx,
			v4l2_std_id * std);
static int start_capture(int *);
static int stop_capture(int *);
static int release_capture(int *, int *);
static int init_display(int *, int *, v4l2_std_id std);
static int release_display(int *, int);
static int start_display(int *);
static int stop_display(int *);
static int allocate_buffers(int *, int);
static char *capture_device;

/*=====================init_capture========================*/
/* This function initializes capture device. It detects   *
 * first input connected on the channel-0 and detects the *
 * standard on that input. It, then, enqueues all the     *
 * buffers in the driver's incoming queue.		  */
static int init_capture(int *capture_fd, int *numbuffers, int input_idx,
			v4l2_std_id * std)
{
	int mode = O_RDWR, ret, j, i;
	struct v4l2_requestbuffers reqbuf;
	struct v4l2_buffer buf;
	struct v4l2_input input;
	struct v4l2_format fmt;
	struct v4l2_standard standard;

	/* Open the channel-0 capture device */
	*capture_fd = open((const char *)capture_device, mode);
	if (capture_fd <= 0) {
		printf("Cannot open = %s device\n", capture_device);
		return -1;
	}

	ret = ioctl(*capture_fd, VIDIOC_S_INPUT, &input_idx);
	if (ret < 0) {
		perror("VIDIOC_S_INPUT\n");
		return -1;
	}

	/* Detect the standard in the input detected */
	ret = ioctl(*capture_fd, VIDIOC_QUERYSTD, std);

	if (ret < 0) {
		perror("VIDIOC_QUERYSTD\n");
		return -1;
	}

	/* Detect the standard in the input detected */
	ret = ioctl(*capture_fd, VIDIOC_S_STD, std);

	if (ret < 0) {
		perror("VIDIOC_QUERYSTD\n");
		return -1;
	}

	/* As the application is using user pointer buffer 
	 * exchange mechanism, it must tell size of the allocated 
	 * buffers so that driver will be able to calculate 
	 * the offsets correctly. */
	memset(&fmt, 0, sizeof(fmt));
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	ret = ioctl(*capture_fd, VIDIOC_G_FMT, &fmt);
	if (ret < 0) {
		perror("G_FMT\n");
		return -1;
	}
	fmt.fmt.pix.bytesperline = BUFFER_PITCH;
	fmt.fmt.pix.sizeimage = BUFFER_PITCH * BUFFER_HEIGHT * 2;
	if (ISINTERLACED(*std))
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	else
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	ret = ioctl(*capture_fd, VIDIOC_S_FMT, &fmt);
	if (ret < 0) {
		perror("S_FMT\n");
		return -1;
	}

	/* Buffer allocation 
	 * Informing the driver that user pointer buffer exchange 
	 * mechanism will be used.
	 * HERE count = number of buffer to be allocated.
	 * type = type of device for which buffers are to be allocated. 
	 * memory = type of the buffers requested i.e. driver allocated or 
	 * user pointer */
	reqbuf.count = *numbuffers;
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	reqbuf.memory = V4L2_MEMORY_USERPTR;

	ret = ioctl(*capture_fd, VIDIOC_REQBUFS, &reqbuf);
	if (ret < 0) {
		perror("cannot allocate memory\n");
		return -1;
	}
	/* Store the number of buffers actually allocated */
	*numbuffers = reqbuf.count;

	/* It is better to zero all the members of buffer structure */
	memset(&buf, 0, sizeof(buf));

	/* Enqueue buffers
	 * Before starting streaming, all the buffers needs to be en-queued 
	 * in the driver incoming queue. These buffers will be used by the 
	 * drive for storing captured frames. */
	/* Enqueue buffers */
	for (i = 0; i < reqbuf.count; i++) {
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.index = i;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.m.userptr = (unsigned long)capture_buff_info[i].start;
		ret = ioctl(*capture_fd, VIDIOC_QBUF, &buf);
		if (ret < 0) {
			perror("VIDIOC_QBUF\n");
			return -1;
		}
	}

	return 0;
}

/*=====================start_capture========================*/
/* This function starts streaming on the capture device	   */
static int start_capture(int *capture_fd)
{
	int a = V4L2_BUF_TYPE_VIDEO_CAPTURE, ret, i;
	/* Here type of device to be streamed on is required to be passed */
	ret = ioctl(*capture_fd, VIDIOC_STREAMON, &a);
	if (ret < 0) {
		perror("VIDIOC_STREAMON\n");
		return -1;
	}
	return 0;
}

/*=====================stop_capture========================*/
/* This function stops streaming on the capture device	  */
static int stop_capture(int *capture_fd)
{
	int ret, i, a = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	/* Here type of device to be streamed off is required to be passed */
	ret = ioctl(*capture_fd, VIDIOC_STREAMOFF, &a);
	if (ret < 0) {
		perror("VIDIOC_STREAMOFF\n");
		return -1;
	}
	return 0;
}

/*=====================release_capture========================*/
/* This function un-maps all the mmapped buffers of capture  *
 * and closes the capture file handle			     */
static int release_capture(int *capture_fd, int *numbuffers)
{
	int i;
	for (i = 0; i < *numbuffers; i++) {
		munmap(capture_buff_info[i].start, capture_buff_info[i].length);
		capture_buff_info[i].start = NULL;
	}
	close(*capture_fd);
	*capture_fd = 0;
	return 0;
}

/*=====================init_display========================*/
/* This function initializes display device. It sets      *
 * output and standard on channel-2. These output and     *
 * standard are same as those detected in capture device. *
 * It, then, enqueues all the buffers in the driver's     *
 * incoming queue.*/
static int init_display(int *display_fd, int *numbuffers, v4l2_std_id std)
{
	int mode = O_RDWR, j;
	struct v4l2_buffer buf;
	int ret, i = 0;
	struct v4l2_requestbuffers reqbuf;
	struct v4l2_format fmt;
	struct v4l2_output output;
	int found = 0;

	/* Open the channel-2 display device */
	*display_fd = open((const char *)DISPLAY_DEVICE, mode);
	if (*display_fd <= -1) {
		printf("Cannot open = %s\n", DISPLAY_DEVICE);
		return -1;
	}

	/* Enumerate outputs */
	output.type = V4L2_OUTPUT_TYPE_ANALOG;
	output.index = 0;
	while ((ret = ioctl(*display_fd, VIDIOC_ENUMOUTPUT, &output) == 0)) {
		if (!strcmp(output.name, OUTPUTNAME)) {
			found = 1;
			break;
		}
		output.index++;
	}

	if (!found) {
		printf("Unable to find output name matching input name\n",
		       OUTPUTNAME);
		return -1;
	}

	/* Set component output */
	ret = ioctl(*display_fd, VIDIOC_S_OUTPUT, &output.index);
	if (ret) {
		perror("cannot allocate memory\n");
		return -1;
	}

	/* Set std */
	ret = ioctl(*display_fd, VIDIOC_S_STD, &std);
	if (ret) {
		perror("cannot allocate memory\n");
		return -1;
	}

	/* Buffer allocation 
	 * Informing the driver that user pointer buffer exchange 
	 * mechanism will be used.
	 * HERE count = number of buffer to be allocated.
	 * type = type of device for which buffers are to be allocated. 
	 * memory = type of the buffers requested i.e. driver allocated or 
	 * user pointer */
	reqbuf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	reqbuf.count = *numbuffers;
	reqbuf.memory = V4L2_MEMORY_USERPTR;

	ret = ioctl(*display_fd, VIDIOC_REQBUFS, &reqbuf);
	if (ret) {
		perror("cannot allocate memory\n");
		return -1;
	}

	*numbuffers = reqbuf.count;

	/* It is better to zero all the members of buffer structure */
	memset(&buf, 0, sizeof(buf));

	/* Enqueue buffers
	 * Before starting streaming, all the buffers needs to be en-queued 
	 * in the driver incoming queue. */
	/* Enqueue buffers */
	for (i = 0; i < reqbuf.count; i++) {
		buf.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.index = i;
		buf.m.userptr = (unsigned long)display_buff_info[i].start;
		ret = ioctl(*display_fd, VIDIOC_QBUF, &buf);
		if (ret < 0) {
			perror("VIDIOC_QBUF\n");
			return -1;
		}
	}
	/* As the application is using user pointer buffer 
	 * exchange mechanism, it must tell size of the allocated 
	 * buffers so that driver will be able to calculate 
	 * the offsets correctly. */
	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(*display_fd, VIDIOC_G_FMT, &fmt);
	if (ret < 0) {
		perror("G_FMT\n");
		return -1;
	}
	fmt.fmt.pix.bytesperline = BUFFER_PITCH;
	fmt.fmt.pix.sizeimage = BUFFER_PITCH * BUFFER_HEIGHT * 2;
	if (ISINTERLACED(std))
		fmt.fmt.pix.field = V4L2_FIELD_INTERLACED;
	else
		fmt.fmt.pix.field = V4L2_FIELD_NONE;
	ret = ioctl(*display_fd, VIDIOC_S_FMT, &fmt);
	if (ret < 0) {
		perror("S_FMT\n");
		return -1;
	}

	return 0;
}

/*=====================release_display========================*/
/* This function un-maps all the mmapped buffers for display *
 * and closes the capture file handle			     */
static int release_display(int *display_fd, int numbuffers)
{
	int i;
	for (i = 0; i < numbuffers; i++) {
		munmap(display_buff_info[i].start, display_buff_info[i].length);
		display_buff_info[i].start = NULL;
	}
	close(*display_fd);
	*display_fd = 0;
	return 0;
}

/*=====================start_display========================*/
/* This function starts streaming on the display device	   */
static int start_display(int *display_fd)
{
	int a = 0, ret, i;
	/* Here type of device to be streamed on is required to be passed */
	a = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(*display_fd, VIDIOC_STREAMON, &a);
	if (ret < 0) {
		perror("VIDIOC_STREAMON\n");
		return -1;
	}
	return 0;
}

/*=====================stop_display========================*/
/* This function stops streaming on the display device	  */
static int stop_display(int *display_fd)
{
	int ret, a = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	ret = ioctl(*display_fd, VIDIOC_STREAMOFF, &a);
	if (ret < 0) {
		perror("display:VIDIOC_STREAMOFF\n");
		return -1;
	}
	return 0;
}

static void usage()
{
	printf("Usage: vpif_userptr_loopback [OPTIONS]\n");
	printf("Options:\n");
	printf("\t-i\tInput interface to use\n");
	printf("\t\t\t0 => Composite input\n");
	printf("\t\t\t1 => S-Video input\n");
	printf("\t\t\t2 => Component input [DEFAULT without -i]\n");
	printf("\nNotes:\n");
	printf("Same kernel image cannot be used for both Component and"
			" Composite video capture.\nThis is because only one of"
			" TVP7002 (Component) or TVP5147 (Composite) can be\n"
			"chosen at a time in the kernel. Please configure"
			" your kernel accordingly.\n");
}

int main(int argc, char *argv[])
{
	int i = 0;
	void *capturebuffer0;
	void *displaybuffer;
	int counter = 0;
	int ret = 0, d, index, input = 2, input_index;
	int bufsize;
	struct v4l2_buffer buf1, buf2;
	unsigned long temp;
	int outputidx = -1;
	int capture_fd, display_fd, vdce_fd;
	int capture_numbuffers = MAX_BUFFER, display_numbuffers = MAX_BUFFER;
	char outputname[15];
	char stdname[15];
	v4l2_std_id std;
	char shortoptions[] = "i:s:p:m:f:l:h:b:t:c:?";

	/* by default use composite */
	for (;;) {
		d = getopt_long(argc, argv, shortoptions, (void *)NULL, &index);
		if (-1 == d)
			break;
		switch (d) {
		case 'i':
			input = atoi(optarg);
			break;
		default:
			usage();
			exit(1);
		}
	}

	if  (input == 0) {
		input_index = 0;
		capture_device = "/dev/video0";
	} else if (input == 1) {
		input_index = 0;
		capture_device = "/dev/video1";
	} else if (input == 2) {
		input_index = 1;
		capture_device  = "/dev/video0";
	} else {
		printf("Unknown input %d\n", input);
		usage();
		exit(1);
	}

	for (i = 0; i < MAX_BUFFER; i++) {
		capture_buff_info[i].start = NULL;
		display_buff_info[i].start = NULL;
	}

	/* STEP1:
	 * Buffer Allocation
	 * Allocate buffers for capture and display devices from the VDCE 
	 * device*/
	ret = allocate_buffers(&vdce_fd, MAX_BUFFER);
	if (ret < 0)
		return -1;

	/* STEP2:
	 * Initialization section
	 * Initialize capture and display devices. 
	 * Here one capture channel is opened and input and standard is 
	 * detected on thatchannel.
	 * Display channel is opened with the same standard that is detected at
	 * capture channel.
	 * */

	/* open capture channel 0 */
	ret = init_capture(&capture_fd, &capture_numbuffers, input_index, &std);
	if (ret < 0) {
		printf("Error in opening capture device for channel 0\n");
		return ret;
	}

	/* open display channel */
	ret = init_display(&display_fd, &display_numbuffers, std);
	if (ret < 0) {
		printf("Error in opening display device\n");
		return ret;
	}

	/* STEP3:
	 * Here display and capture channels are started for streaming. After 
	 * this capture device will start capture frames into enqueued 
	 * buffers and display device will start displaying buffers from 
	 * the qneueued buffers */

	/* start display */
	ret = start_display(&display_fd);
	if (ret < 0) {
		printf("Error in starting display\n");
		return ret;
	}
	/* start capturing for channel 0 */
	ret = start_capture(&capture_fd);
	if (ret < 0) {
		printf("Error in starting capturing for channel 0\n");
		return ret;
	}
	/* It is better to zero out all the members of v4l2_buffer */
	memset(&buf1, 0, sizeof(buf1));
	memset(&buf2, 0, sizeof(buf2));

	/* One buffer is dequeued from display and capture channels.
	 * Capture buffer will be exchanged with display buffer.
	 * All two buffers are put back to respective channels.
	 * This sequence is repeated in loop.
	 * After completion of this loop, channels are stopped.
	 * */
	buf1.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	buf1.memory = V4L2_MEMORY_USERPTR;
	buf2.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	buf2.memory = V4L2_MEMORY_USERPTR;
	while (counter < MAXLOOPCOUNT) {
		ret = ioctl(capture_fd, VIDIOC_DQBUF, &buf1);
		if (ret < 0) {
			perror("capture VIDIOC_DQBUF\n");
			return -1;
		}

		ret = ioctl(display_fd, VIDIOC_DQBUF, &buf2);
		if (ret < 0) {
			perror("display VIDIOC_DQBUF\n");
			return -1;
		}
		temp = buf2.m.userptr;
		buf2.m.userptr = buf1.m.userptr;
		buf1.m.userptr = temp;

		ret = ioctl(display_fd, VIDIOC_QBUF, &buf2);
		if (ret < 0) {
			perror("display VIDIOC_QBUF\n");
			return -1;
		}
		ret = ioctl(capture_fd, VIDIOC_QBUF, &buf1);
		if (ret < 0) {
			perror("capture VIDIOC_QBUF\n");
			return -1;
		}
		counter++;
	}
	/* stop display */
	ret = stop_display(&display_fd);
	if (ret < 0) {
		printf("Error in stopping display\n");
		return ret;
	}
	/* stop capturing for channel 0 */
	ret = stop_capture(&capture_fd);
	if (ret < 0) {
		printf("Error in stopping capturing for channel 0\n");
		return ret;
	}

	/* close capture channel 0 */
	ret = release_capture(&capture_fd, &capture_numbuffers);
	if (ret < 0) {
		printf("Error in closing capture device\n");
		return ret;
	}
	/* Free section
	 * Here channels for capture and display are close.
	 * */
	/* open display channel */
	ret = release_display(&display_fd, display_numbuffers);
	if (ret < 0) {
		printf("Error in closing display device\n");
		return ret;
	}
	/* Close the vdce file handle */
	close(vdce_fd);
	return ret;
}

/*=============================allocate_buffers===================*/
/* This function allocates physically contiguous memory using 	 *
 * VDCE driver for capture and display devices. 		 *
 * Ideally one should use CMEM module for allocating buffers. 	 *
 * Here VDCE module is used to get physically contiguous	 * 
 * buffers. But its not necessary.				 */
static int allocate_buffers(int *vdce_fd, int numbuffers)
{
	int i;
	vdce_reqbufs_t reqbuf;
	vdce_buffer_t buffer;

	/* Open VDCE device */
	*vdce_fd = open(VDCE_DEVICE, O_RDWR);
	if (*vdce_fd <= 0) {
		printf("cannot open %s\n", VDCE_DEVICE);
		return -1;
	}

	/*
	   VDCE allocated buffers:
	   Request for 3 input buffer of size 1920x1080x2of 4:2:2 format
	   Here HEIGHT = Height of Y portion of the buffer.Driver 
	   understands that double the size is needed for a 4:2:2 buffer.
	   PITCH is NOT restriced to be 1920. It could be more if needed.
	 */
	reqbuf.buf_type = VDCE_BUF_IN;
	reqbuf.num_lines = BUFFER_HEIGHT;
	reqbuf.bytes_per_line = BUFFER_PITCH;
	reqbuf.image_type = VDCE_IMAGE_FMT_422;
	reqbuf.count = numbuffers;
	if (ioctl(*vdce_fd, VDCE_REQBUF, &reqbuf) < 0) {
		perror("buffer allocation error.\n");
		close(*vdce_fd);
		exit(-1);
	}

	/* Get the physical address of the buffer and mmap them in 
	 * the user space */
	buffer.buf_type = VDCE_BUF_IN;
	for (i = 0; i < numbuffers; i++) {
		buffer.index = i;
		if (ioctl(*vdce_fd, VDCE_QUERYBUF, &buffer) < 0) {
			perror("buffer query error.\n");
			/*
			   closing a device takes care of freeing up
			   of the buffers automatically
			 */
			close(*vdce_fd);
		}
		capture_buff_info[i].start =
		    mmap(NULL, buffer.size,
			 PROT_READ | PROT_WRITE, MAP_SHARED,
			 *vdce_fd, buffer.offset);
		/* mapping input buffer */
		if (capture_buff_info[i].start == MAP_FAILED) {
			perror("error in mmaping output buffer\n");
			close(*vdce_fd);
			exit(1);
		}
		capture_buff_info[i].index = i;
		capture_buff_info[i].length = buffer.size;
	}

	/*
	   VDCE allocated buffers:
	   Request for 3 output buffer of size 1920x1080x2of 4:2:2 format
	   Here HEIGHT = Height of Y portion of the buffer.Driver 
	   understands that double the size is needed for a 4:2:2 buffer.
	   PITCH is NOT restriced to be 1920. It could be more if needed.
	 */
	reqbuf.buf_type = VDCE_BUF_OUT;
	reqbuf.num_lines = BUFFER_HEIGHT;
	reqbuf.bytes_per_line = BUFFER_PITCH;
	reqbuf.image_type = VDCE_IMAGE_FMT_422;
	reqbuf.count = numbuffers;
	if (ioctl(*vdce_fd, VDCE_REQBUF, &reqbuf) < 0) {
		perror("buffer allocation error.\n");
		close(*vdce_fd);
		exit(-1);
	}

	/* Get the physical address of the buffer and mmap them in 
	 * the user space */
	buffer.buf_type = VDCE_BUF_OUT;
	for (i = 0; i < numbuffers; i++) {
		buffer.index = i;
		if (ioctl(*vdce_fd, VDCE_QUERYBUF, &buffer) < 0) {
			perror("buffer query error.\n");
			close(*vdce_fd);
		}
		display_buff_info[i].start =
		    mmap(NULL, buffer.size,
			 PROT_READ | PROT_WRITE, MAP_SHARED,
			 *vdce_fd, buffer.offset);
		/* mapping input buffer */
		if (display_buff_info[i].start == MAP_FAILED) {
			perror("error in mmaping output buffer\n");
			close(*vdce_fd);
			exit(1);
		}
		display_buff_info[i].index = i;
		display_buff_info[i].length = buffer.size;
	}
	return 0;
}
