/**+--------------------------------------------------------------------------+**
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
#include <linux/videodev2.h>
#include <media/davinci/dm355_ccdc.h>
#include <media/davinci/vpfe_capture.h>
#include <media/davinci/dm355_ipipe.h>
#include <video/davincifb.h>
#include "osd16.h"
#include "test_8.h"
#include "cmem.h"

static struct buffer ipipebuffer;

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define CAPTURE_DEVICE		"/dev/video0"

#define WIDTH_PAL		720
#define HEIGHT_PAL		576
#define WIDTH_NTSC		720
#define HEIGHT_NTSC		480	

#define MIN_BUFFERS		2

#define UYVY_BLACK		0x10801080

/* Device parameters */
#define OSD0_DEVICE		"/dev/fb0"
#define OSD1_DEVICE		"/dev/fb2"
#define FBVID0_DEVICE		"/dev/fb1"
#define FBVID1_DEVICE		"/dev/fb3"

/* Function error codes */
#define SUCCESS			0
#define FAILURE			-1

/* Bits per pixel for video window */
#define YUV_422_BPP		16
#define BITMAP_BPP_8		8

#define DISPLAY_INTERFACE	"COMPOSITE"
#define DISPLAY_MODE_NTSC		"NTSC"
#define DISPLAY_MODE_PAL		"PAL"

#define round_32(width)		((((width) + 31) / 32) * 32 )

/* D1 screen dimensions */
#define VID0_WIDTH		720
#define VID0_HEIGHT		480
#define VID0_BPP		16
#define VID0_FRAME_SIZE		(VID0_WIDTH*VID0_HEIGHT)
#define VID0_VMODE		FB_VMODE_INTERLACED

#define VID1_WIDTH 		720
#define VID1_HEIGHT		480
#define VID1_BPP		16
#define VID1_FRAME_SIZE		(VID1_WIDTH*VID1_HEIGHT)
#define VID1_VMODE		FB_VMODE_INTERLACED

#define OSD0_BPP		4
#define	OSD0_WIDTH		(round_32(240*OSD0_BPP/8) * 8/OSD0_BPP)
#define	OSD0_HEIGHT		120
#define OSD0_FRAME_SIZE		(OSD0_WIDTH*OSD0_HEIGHT)
#define OSD0_VMODE		FB_VMODE_INTERLACED

#define OSD1_BPP		8
#define	OSD1_WIDTH		(round_32(240*OSD1_BPP/8) * 8/OSD1_BPP)
#define	OSD1_HEIGHT		120
#define OSD1_FRAME_SIZE		(OSD1_WIDTH*OSD1_HEIGHT)
#define OSD1_VMODE		FB_VMODE_INTERLACED

/* position */
#define	OSD0_XPOS		0
#define	OSD0_YPOS		0
#define	OSD1_XPOS		300
#define	OSD1_YPOS		250
#define	VID0_XPOS		0
#define	VID0_YPOS		0
#define	VID1_XPOS		0
#define	VID1_YPOS		0

/* Zoom Params */
#define	OSD0_HZOOM		0
#define	OSD0_VZOOM		0
#define	OSD1_HZOOM		0
#define	OSD1_VZOOM		0
#define	VID0_HZOOM		0
#define	VID0_VZOOM		0
#define	VID1_HZOOM		0
#define	VID1_VZOOM		0

/* OSD window blend factor */
#define OSD1_WINDOW_BF		0
#define OSD1_WINDOW_CK		0
#define OSD1_CK			0
#define OSD0_WINDOW_BF		3
#define OSD0_WINDOW_CK		0
#define OSD0_CK			0

#define VIDEO_NUM_BUFS		3
#define OSD_NUM_BUFS		2
#define RED_COLOR 		249
#define BLUE_COLOR 		140	//blue color
#define RAM_CLUT_IDX 		0xFF
#define BITMAP_COLOR		0x11

#define CURSOR_XPOS		100
#define CURSOR_YPOS		100
#define CURSOR_XRES		50
#define CURSOR_YRES		50
#define CURSOR_THICKNESS	1
#define CURSOR_COLOR		0xF9

#define ATTR_BLINK_INTERVAL	1
#define ATTR_BLEND_VAL 		0xaa

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

/*******************************************************************************
 *	STRUCTURE DEFINITIONS
 */

struct ccdc_config_params_raw config_params = {
	.datasft = 2,
	.data_sz = CCDC_DATA_12BITS,
	.mfilt1 = CCDC_NO_MEDIAN_FILTER1,
	.mfilt2 = CCDC_NO_MEDIAN_FILTER2,
	.alaw = {
		.gama_wd = 2,
	},
	.blk_clamp = {
		.sample_pixel = 1,
		.dc_sub = 25
	},
	.col_pat_field0 = {
		.olop = CCDC_GREEN_BLUE,
		.olep = CCDC_BLUE,
		.elop = CCDC_RED,
		.elep = CCDC_GREEN_RED
	},
	.col_pat_field1 = {
		.olop = CCDC_GREEN_BLUE,
		.olep = CCDC_BLUE,
		.elop = CCDC_RED,
		.elep = CCDC_GREEN_RED
	},
};

struct buffer {
	void *start;
	size_t length;
	size_t offset;
};

#define ALIGN(x, y)	(((x + (y-1))/y)*y)
//#define BUF_SIZE	ALIGN((1280*720*1), 4096)
#define NUM_BUFFERS	3

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

struct buf_info user_io_buffers[NUM_BUFFERS];

struct vpbe_test_info {
	int vid0_width;
	int vid0_height;
	int vid0_bpp;
	int vid0_frame_size;
	int vid0_vmode;

	int vid1_width;
	int vid1_height;
	int vid1_bpp;
	int vid1_frame_size;
	int vid1_vmode;

	int osd0_bpp;
	int osd0_width;
	int osd0_height;
	int osd0_frame_size;
	int osd0_vmode;

	int osd1_bpp;
	int osd1_width;
	int osd1_height;
	int osd1_frame_size;
	int osd1_vmode;

	int osd0_xpos;
	int osd0_ypos;
	int osd1_xpos;
	int osd1_ypos;
	int vid0_xpos;
	int vid0_ypos;
	int vid1_xpos;
	int vid1_ypos;

	int osd0_hzoom;
	int osd0_vzoom;
	int osd1_hzoom;
	int osd1_vzoom;
	int vid0_hzoom;
	int vid0_vzoom;
	int vid1_hzoom;
	int vid1_vzoom;

	int osd1_window_bf;
	int osd1_window_ck;
	int osd1_ck;
	int osd0_window_bf;
	int osd0_window_ck;
	int osd0_ck;

	int osd0_coloridx;
	int osd1_coloridx;
	int ram_clut_idx;
	int bitmap_color;

	int cursor_xpos;
	int cursor_ypos;
	int cursor_xres;
	int cursor_yres;
	int cursor_thickness;
	int cursor_color;

	int attr_blink_interval;
	int attr_blend_val;
};

/*******************************************************************************
 *	FILE GLOBALS
 */
static struct vpbe_test_info test_data = {
	VID0_WIDTH,
	VID0_HEIGHT,
	VID0_BPP,
	VID0_FRAME_SIZE,
	VID0_VMODE,

	VID1_WIDTH,
	VID1_HEIGHT,
	VID1_BPP,
	VID1_FRAME_SIZE,
	VID1_VMODE,

	OSD0_BPP,
	OSD0_WIDTH,
	OSD0_HEIGHT,
	OSD0_FRAME_SIZE,
	OSD0_VMODE,

	OSD1_BPP,
	OSD1_WIDTH,
	OSD1_HEIGHT,
	OSD1_FRAME_SIZE,
	OSD1_VMODE,

	OSD0_XPOS,
	OSD0_YPOS,
	OSD1_XPOS,
	OSD1_YPOS,
	VID0_XPOS,
	VID0_YPOS,
	VID1_XPOS,
	VID1_YPOS,

	OSD0_HZOOM,
	OSD0_VZOOM,
	OSD1_HZOOM,
	OSD1_VZOOM,
	VID0_HZOOM,
	VID0_VZOOM,
	VID1_HZOOM,
	VID1_VZOOM,

	OSD1_WINDOW_BF,
	OSD1_WINDOW_CK,
	OSD1_CK,
	OSD0_WINDOW_BF,
	OSD0_WINDOW_CK,
	OSD0_CK,

	BLUE_COLOR,
	RED_COLOR,
	RAM_CLUT_IDX,
	BITMAP_COLOR,

	CURSOR_XPOS,
	CURSOR_YPOS,
	CURSOR_XRES,
	CURSOR_YRES,
	CURSOR_THICKNESS,
	CURSOR_COLOR,

	ATTR_BLINK_INTERVAL,
	ATTR_BLEND_VAL,
};

static int fdCapture = -1;
static struct buffer *buffers = NULL;
static int nBuffers;
static int nWidthFinal;
static int nHeightFinal;
static int quit;
static char *vid0_display[VIDEO_NUM_BUFS];
static char *vid1_display[VIDEO_NUM_BUFS];
static char *osd0_display[OSD_NUM_BUFS];
static char *osd1_display[OSD_NUM_BUFS];
static int fd_vid0, fd_vid1, fd_osd0, fd_osd1;
static struct fb_var_screeninfo vid1_varInfo, osd0_varInfo, osd1_varInfo,
    prev_vid1_var, prev_osd0_var;
static struct fb_fix_screeninfo vid0_fixInfo, vid1_fixInfo, osd0_fixInfo,
    osd1_fixInfo;
static int vid0_size, vid1_size, osd0_size, osd1_size;
static int stress_test = 1;
static int input_std;
static int start_loopCnt = LOOP_COUNT;
static int rgb565_enable;
static int rgb565_enable_osd1;
static int display_out = 1;
static int save_frame = 0;
FILE *file_fp;
static int print_fn = 1;
static int width_final = 640, height_final = 480;
static int BUF_SIZE;
#define CAPTURE_FILE "./capt_frame.yuv"
static int field;
/* 0 - composite
 * 1 - S-video
 * 2 - Camera
 */
static int vpfe_input = 0;

/*******************************************************************************
 *	EXTERN VARIABLES
 */
extern int errno;

/*******************************************************************************
 *	LOCAL FUNCTION PROTOTYPES
 */
static void restore_config(void);
static int initialize_capture(v4l2_std_id * cur_std);
static int start_loop(void);
static int init_capture_device(void);
static int set_data_format(v4l2_std_id * cur_std);
static int init_capture_buffers(void);
static int start_streaming(void);
static int display_frame(char, void *);
static int flip_bitmap_buffers(int, int);
static int flip_video_buffers(int, int);
static int mmap_vid1(void);
static int mmap_osd0(void);
static int display_bitmap_osd0(void);
static int display_bitmap_osd1(void);
static int unmap_and_disable(char);
static int init_osd0_device(int, struct fb_var_screeninfo *);
static int init_vid1_device(int, struct fb_var_screeninfo *);
static int vpbe_UE_1(void);
static void close_all_windows(void);
static int open_all_windows(void);
static int change_sysfs_attrib(char *, char *);

/*******************************************************************************
 *	FUNCTION DEFINITIONS
 */
static void restore_config(void)
{
	struct fb_cursor cursor_info;
	DBGENTER;
	cursor_info.enable = 0;
	cursor_info.image.dx = CURSOR_XPOS;
	cursor_info.image.dy = CURSOR_YPOS;
	cursor_info.image.width = CURSOR_XRES;
	cursor_info.image.height = CURSOR_YRES;
	cursor_info.image.depth = CURSOR_THICKNESS;
	cursor_info.image.fg_color = CURSOR_COLOR;
	if (ioctl(fd_osd1, FBIOGET_FSCREENINFO, &osd1_fixInfo) < 0) {
		perror("\nFailed FBIOGET_FSCREENINFO osd1");
		return;
	}

	/* Get Existing var_screeninfo for vid0 window */
	if (ioctl(fd_osd0, FBIOGET_VSCREENINFO, &osd0_varInfo) < 0) {
		printf("\nFailed FBIOGET_VSCREENINFO");
		return;
	}

	/* Modify the resolution and bpp as required */
	osd0_varInfo.bits_per_pixel = 16;

	/* Set vid0 window format */
	if (ioctl(fd_osd0, FBIOPUT_VSCREENINFO, &osd0_varInfo) < 0) {
		printf("\nFailed FBIOPUT_VSCREENINFO");
		return;
	}

	osd0_display[0] =
	    (char *)mmap(NULL,
			 osd0_fixInfo.line_length * osd0_varInfo.yres_virtual,
			 PROT_READ | PROT_WRITE, MAP_SHARED, fd_osd0, 0);
	osd1_display[0] =
	    (char *)mmap(NULL,
			 osd1_fixInfo.line_length * osd1_varInfo.yres_virtual,
			 PROT_READ | PROT_WRITE, MAP_SHARED, fd_osd1, 0);
	vid1_display[0] =
	    (char *)mmap(NULL,
			 vid1_fixInfo.line_length * vid1_varInfo.yres_virtual,
			 PROT_READ | PROT_WRITE, MAP_SHARED, fd_vid1, 0);

	memset(osd0_display[0], 0x00,
	       osd0_fixInfo.line_length * osd0_varInfo.yres_virtual);
	memset(osd1_display[0], 0x11,
	       osd1_fixInfo.line_length * osd1_varInfo.yres_virtual);
	memset(vid1_display[0], 0x80,
	       vid1_fixInfo.line_length * vid1_varInfo.yres_virtual);

	munmap(osd0_display[0],
	       osd0_fixInfo.line_length * osd0_varInfo.yres_virtual);
	munmap(osd1_display[0],
	       osd1_fixInfo.line_length * osd1_varInfo.yres_virtual);
	munmap(vid1_display[0],
	       vid1_fixInfo.line_length * vid1_varInfo.yres_virtual);

	system("cat /dev/zero > /dev/fb/2 2> /dev/null");

	DBGEXIT;
}

/******************************************************************************/
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

/******************************************************************************/
static int start_loop(void)
{
	struct v4l2_buffer buf;
	static int captFrmCnt = 0;
	char *ptrPlanar = NULL;
  	int dummy;

	ptrPlanar = (char *)calloc(1, nWidthFinal * nHeightFinal * 2);

	InitIpipe(RAW2YUV, width_final, height_final, 720, 480, &ipipebuffer);

	while (!quit) {
		fd_set fds;
		struct timeval tv;
		int r;

		if (stress_test) {
			start_loopCnt--;
			if (start_loopCnt == 0) {
				start_loopCnt = 50;
				break;
			}
		}

		if (!display_out) {
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
		}

		if (display_out) {
			/* Wait for vertical sync */
			if (ioctl(fd_vid1, FBIO_WAITFORVSYNC, &dummy) < -1) {
				printf("Failed FBIO_WAITFORVSYNC\n");
				if (EAGAIN == errno) {
					printf("disp_again\n");
					continue;
				}
				return -1;
			}
		}

		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_USERPTR;

		/* determine ready buffer */
		if (-1 == ioctl(fdCapture, VIDIOC_DQBUF, &buf)) {
			if (EAGAIN == errno)
				printf("capt_again\n");
				continue;
			printf("StartCameraCaputre:ioctl:VIDIOC_DQBUF\n");
			return -1;
		}
		if (captFrmCnt > 100) {
			if (save_frame) {
				fwrite(user_io_buffers[buf.index].user_addr,
					1, (nWidthFinal * nHeightFinal * 1),
					file_fp); 
				save_frame = 0;
				fclose(file_fp);
				printf("Saved file %s\n", CAPTURE_FILE);
				return -1;
			}
		}
		if (display_out) {
			DoIPIPING(RAW2YUV, width_final, height_final, 720,
				  	480,  user_io_buffers[buf.index].phy_addr);
			display_frame(VID1, ipipebuffer.start);
			display_bitmap_osd0();
		}
		if (print_fn)
			printf("time:%lu    frame:%u\n", (unsigned long)time(NULL), captFrmCnt++);


		/* requeue the buffer */
		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf)) {
			printf("StartCameraCaputre:ioctl:VIDIOC_QBUF\n");
			return -1;
		}
	}
	return SUCCESS;
}

/******************************************************************************/
static int init_capture_device(void)
{

	struct v4l2_capability cap;
	int ret;

	/* input-0 is selected by default, so no need to set it */
	if ((fdCapture = open(CAPTURE_DEVICE, O_RDWR )) <= -1) {
		printf("InitDevice:open::\n");
		return -1;
	}

	/* is capture supported? */
	if (-1 == ioctl(fdCapture, VIDIOC_QUERYCAP, &cap)) {
		printf("InitDevice:ioctl:VIDIOC_QUERYCAP:\n");
		return -1;
	}

	ret = ioctl(fdCapture, VPFE_CMD_S_CCDC_RAW_PARAMS , &config_params);
	if (ret < 0) {
		printf("CCDC RAW PARAMS set fail\n");
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
static int set_data_format(v4l2_std_id *cur_std)
{
	v4l2_std_id prev_std;
	struct v4l2_format fmt;
	unsigned int min;
	struct v4l2_input input;
	int temp_input;
	struct v4l2_cropcap cropcap;
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

	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if(vpfe_input == 2)
	{	
		if(input_std == 0)
		{
			fmt.fmt.pix.width = 640;
			fmt.fmt.pix.height = 480;
		}
		else if(input_std == 1)
		{
			fmt.fmt.pix.width = 720;
			fmt.fmt.pix.height = 480;
		}
		else if(input_std == 2)
		{
			fmt.fmt.pix.width = 720;
			fmt.fmt.pix.height = 576;
		}
		else if(input_std == 3)
		{
			fmt.fmt.pix.width = 1280;
			fmt.fmt.pix.height = 720;
		}
		
	}
		//fmt.fmt.pix.width = 1280; //640;	/* SSK Buffer Size */
	//fmt.fmt.pix.height = 720; //480;
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

/******************************************************************************/
static int init_capture_buffers(void)
{
	struct v4l2_requestbuffers req;
	int nIndex = 0;

	CLEAR(req);
	req.count = NUM_BUFFERS;
	req.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	req.memory = V4L2_MEMORY_USERPTR;

	if (-1 == ioctl(fdCapture, VIDIOC_REQBUFS, &req)) {
		printf("init_capture_buffers:ioctl:VIDIOC_REQBUFS\n");
		return -1;
	}
	return 0;
}

/******************************************************************************/
static int start_streaming(void)
{
	int i = 0;
	enum v4l2_buf_type type;

	for (i = 0; i < NUM_BUFFERS; i++) {
		struct v4l2_buffer buf;
		CLEAR(buf);
		buf.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		buf.memory = V4L2_MEMORY_USERPTR;
		buf.index = i;
		buf.m.userptr = (unsigned long)user_io_buffers[i].user_addr;
		buf.length = BUF_SIZE;
		printf("Queing buffer:%d\n", i);

		if (-1 == ioctl(fdCapture, VIDIOC_QBUF, &buf))
			perror("start_streaming:ioctl:VIDIOC_QBUF:\n");
	}
	/* all done , get set go */
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fdCapture, VIDIOC_STREAMON, &type))
		printf("start_streaming:ioctl:VIDIOC_STREAMON:\n");

	return 0;
}

static void capture_streamoff(void)
{
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	if (-1 == ioctl(fdCapture, VIDIOC_STREAMOFF, &type))
		printf("start_streaming:ioctl:VIDIOC_STREAMOFF:\n");
}
/******************************************************************************/
static int display_bitmap_osd0(void)
{
	static unsigned int nDisplayIdx = 1;
	static unsigned int nWorkingIndex = 0;
	int y;
	char *dst;
	char *src;
	int fd;

	dst = osd0_display[nWorkingIndex];
	if (dst == NULL)
		return -1;
	fd = fd_osd0;
	if (rgb565_enable == 1) {	/* RGB565 */
		src = (char *)rgb16;
		for (y = 0; y < test_data.osd0_height; y++) {
			memcpy(dst, src, (test_data.osd0_width * 2));
			dst += osd0_fixInfo.line_length;
			src += (704 * 2);
		}
	} else if (rgb565_enable == 2) {	/* 8 bit bitmap */
		src = (char *)test_8;
		for (y = 0; y < test_data.osd0_height; y++) {
			memcpy(dst, src, (test_data.osd0_width));
			dst += osd0_fixInfo.line_length;
			src += (704);
		}
	} else			/* 1/2/4 bit bitmap and attribute */
		memset(dst, test_data.osd0_coloridx, osd0_size);

	nWorkingIndex = (nWorkingIndex + 1) % OSD_NUM_BUFS;
	nDisplayIdx = (nDisplayIdx + 1) % OSD_NUM_BUFS;

	if ((flip_bitmap_buffers(fd, nDisplayIdx)) < 0)
		return -1;
	return 0;
}

/******************************************************************************/
static int display_bitmap_osd1()
{
	static unsigned int nDisplayIdx = 1;
	static unsigned int nWorkingIndex = 0;
	int y;
	char *dst;
	char *src;
	int fd;

	dst = osd1_display[nWorkingIndex];
	if (dst == NULL)
		return -1;
	fd = fd_osd1;
	if (rgb565_enable_osd1 == 1) {	/* RGB565 */
		src = (char *)rgb16;
		for (y = 0; y < test_data.osd1_height; y++) {
			memcpy(dst, src, (test_data.osd1_width * 2));
			dst += osd1_fixInfo.line_length;
			src += (704 * 2);
		}
	} else if (rgb565_enable_osd1 == 2) {	/* 8 bit bitmap */
		src = (char *)test_8;
		for (y = 0; y < test_data.osd1_height; y++) {
			memcpy(dst, src, (test_data.osd1_width));
			dst += osd1_fixInfo.line_length;
			src += (704);
		}
	} else			/* 1/2/4 bit bitmap and attribute */
		memset(dst, test_data.osd1_coloridx, osd1_size);

	nWorkingIndex = (nWorkingIndex + 1) % OSD_NUM_BUFS;
	nDisplayIdx = (nDisplayIdx + 1) % OSD_NUM_BUFS;

	if ((flip_bitmap_buffers(fd, nDisplayIdx)) < 0)
		return -1;
	return 0;
}

/******************************************************************************/
static int display_frame(char id, void *ptr_buffer)
{
	static unsigned int nDisplayIdx = 0;
	static unsigned int nWorkingIndex = 1;
	int y;
	int yres;
	char *dst;
	char *src;
	int fd;
	unsigned int line_length;

	if (id == VID0) {
		yres = test_data.vid0_height;
		dst = vid0_display[nWorkingIndex];
		if (dst == NULL)
			return -1;
		fd = fd_vid0;
		line_length = vid0_fixInfo.line_length;
	}
	if (id == VID1) {
		yres = test_data.vid1_height;
		dst = vid1_display[nWorkingIndex];
		if (dst == NULL)
			return -1;
		fd = fd_vid1;
		line_length = vid1_fixInfo.line_length;
	}
	src = ptr_buffer;
	for (y = 0; y < yres; y++) {
		memcpy(dst, src, (720 * 2));
		dst += line_length;
		src += (720 * 2);
	}
	nWorkingIndex = (nWorkingIndex + 1) % VIDEO_NUM_BUFS;
	nDisplayIdx = (nDisplayIdx + 1) % VIDEO_NUM_BUFS;
	if ((flip_video_buffers(fd, nDisplayIdx)) < 0)
		return -1;
	return 0;
}

/******************************************************************************/
static int flip_bitmap_buffers(int fd, int buf_index)
{
	struct fb_var_screeninfo var_info;

	if (ioctl(fd, FBIOGET_VSCREENINFO, &var_info) < -1) {
		printf("flip_bitmap_buffers:FBIOGET_VSCREENINFO\n\n");
		return -1;
	}

	var_info.yoffset = var_info.yres * buf_index;

	/* Swap the working buffer for the displayed buffer */
	if (ioctl(fd, FBIOPAN_DISPLAY, &var_info) < -1) {
		printf("flip_bitmap_buffers:FBIOPAN_DISPLAY\n\n");
		return -1;
	}

	return 0;
}

/******************************************************************************/
static int flip_video_buffers(int fd, int buf_index)
{
	int dummy;
	struct fb_var_screeninfo var_info;

	if (ioctl(fd, FBIOGET_VSCREENINFO, &var_info) < -1) {
		printf("flip_video_buffers:FBIOGET_VSCREENINFO\n\n");
		return -1;
	}

	var_info.yoffset = var_info.yres * buf_index;


	/* Swap the working buffer for the displayed buffer */
	if (ioctl(fd, FBIOPAN_DISPLAY, &var_info) < -1) {
		printf("flip_video_buffers:FBIOPAN_DISPLAY\n");
		printf("\n");
		return -1;
	}

	return 0;
}
/******************************************************************************/
static int mmap_vid1(void)
{
	int i;
	vid1_size = vid1_fixInfo.line_length * vid1_varInfo.yres;
	/* Map the video0 buffers to user space */
	vid1_display[0] = (char *)mmap(NULL, vid1_size * VIDEO_NUM_BUFS,
				       PROT_READ | PROT_WRITE, MAP_SHARED,
				       fd_vid1, 0);

	if (vid1_display[0] == MAP_FAILED) {
		printf("\nFailed mmap on %s", FBVID1_DEVICE);
		return FAILURE;
	}

	for (i = 0; i < VIDEO_NUM_BUFS - 1; i++) {
		vid1_display[i + 1] = vid1_display[i] + vid1_size;
		printf("Display buffer %d mapped to address %#lx\n", i + 1,
		       (unsigned long)vid1_display[i + 1]);
	}
	return SUCCESS;
}

/******************************************************************************/
static int mmap_osd0(void)
{
	int i;
	osd0_size = osd0_fixInfo.line_length * osd0_varInfo.yres;

	/* Map the osd0 buffers to user space */
	osd0_display[0] = (char *)mmap(NULL, osd0_size * OSD_NUM_BUFS,
				       PROT_READ | PROT_WRITE, MAP_SHARED,
				       fd_osd0, 0);

	if (osd0_display[0] == MAP_FAILED) {
		printf("\nFailed mmap on %s", OSD0_DEVICE);
		return FAILURE;
	}

	for (i = 0; i < OSD_NUM_BUFS - 1; i++) {
		osd0_display[i + 1] = osd0_display[i] + osd0_size;
		printf("Display buffer %d mapped to address %#lx\n", i + 1,
		       (unsigned long)osd0_display[i + 1]);
	}
	return SUCCESS;
}

/******************************************************************************/
static int unmap_and_disable(char id)
{

	switch (id) {
	case VID0:
		if (munmap(vid0_display[0], vid0_size * VIDEO_NUM_BUFS) == -1) {
			printf("\nFailed munmap on %s", FBVID1_DEVICE);
			return FAILURE;
		}
		break;
	case VID1:
		if (munmap(vid1_display[0], vid1_size * VIDEO_NUM_BUFS) == -1) {
			printf("\nFailed munmap on %s", FBVID1_DEVICE);
			return FAILURE;
		}
		break;
	case OSD0:
		if (munmap(osd0_display[0], osd0_size * OSD_NUM_BUFS) == -1) {
			printf("\nFailed munmap on %s", OSD0_DEVICE);
			return FAILURE;
		}
		break;
	case OSD1:
		if (munmap(osd1_display[0], osd1_size * OSD_NUM_BUFS) == -1) {
			printf("\nFailed munmap on %s", OSD1_DEVICE);
			return FAILURE;
		}
		break;
	default:
		break;
	}
	return SUCCESS;
}

/******************************************************************************/
static int init_osd0_device(int fd_osd0, struct fb_var_screeninfo *var_info)
{
	//vpbe_window_position_t pos;

	if (ioctl(fd_osd0, FBIOGET_FSCREENINFO, &osd0_fixInfo) < 0) {
		printf("\nFailed FBIOGET_FSCREENINFO osd0");
		return FAILURE;
	}

	/* Get Existing var_screeninfo for osd0 window */
	if (ioctl(fd_osd0, FBIOGET_VSCREENINFO, var_info) < 0) {
		printf("\nFailed FBIOGET_VSCREENINFO");
		return FAILURE;
	}
	prev_osd0_var = *var_info;

	/* Modify the resolution and bpp as required */
	var_info->xres = test_data.osd0_width;
	var_info->yres = test_data.osd0_height;
	var_info->bits_per_pixel = test_data.osd0_bpp;
	var_info->vmode = test_data.osd0_vmode;

	/* Change the virtual Y-resolution for buffer flipping (2 buffers) */
	var_info->yres_virtual = var_info->yres * OSD_NUM_BUFS;

	/* Set osd0 window format */
	if (ioctl(fd_osd0, FBIOPUT_VSCREENINFO, var_info) < 0) {
		printf("\nFailed FBIOPUT_VSCREENINFO");
		return FAILURE;
	}

	/* Set window position */

	if (ioctl(fd_osd0, FBIO_SETPOSX, test_data.osd0_xpos) < 0) {
		printf("\nFailed  FBIO_SETPOSX");
		return FAILURE;
	}
	if (ioctl(fd_osd0, FBIO_SETPOSY, test_data.osd0_ypos) < 0) {
		printf("\nFailed  FBIO_SETPOSX");
		return FAILURE;
	}

	/* Enable the window */
	if (ioctl(fd_osd0, FBIOBLANK, 0)) {
		printf("Error enabling OSD0\n");
		return FAILURE;
	}
	return SUCCESS;
}

/******************************************************************************/
static int init_vid1_device(int fd, struct fb_var_screeninfo *var_info)
{
	if (ioctl(fd, FBIOGET_FSCREENINFO, &vid1_fixInfo) < 0) {
		printf("\nFailed FBIOGET_FSCREENINFO vid1");
		return FAILURE;
	}

	/* Get Existing var_screeninfo for vid1 window */
	if (ioctl(fd, FBIOGET_VSCREENINFO, var_info) < 0) {
		printf("\nFailed FBIOGET_VSCREENINFO");
		return FAILURE;
	}

	prev_vid1_var = *var_info;

	/* Modify the resolution and bpp as required */
	var_info->xres = test_data.vid1_width;
	var_info->yres = test_data.vid1_height;
	var_info->vmode = test_data.vid1_vmode;
	var_info->bits_per_pixel = test_data.vid1_bpp;

	/* Change the virtual Y-resolution for buffer flipping (3 buffers) */
	var_info->yres_virtual = var_info->yres * VIDEO_NUM_BUFS;

	/* Set vid1 window format */
	if (ioctl(fd, FBIOPUT_VSCREENINFO, var_info) < 0) {
		printf("\nFailed FBIOPUT_VSCREENINFO");
		return FAILURE;
	}

	/* Set window position */
	if (ioctl(fd_vid1, FBIO_SETPOSX, test_data.vid1_xpos) < 0) {
		printf("\nFailed  FBIO_SETPOS");
		return FAILURE;
	}

	if (ioctl(fd_vid1, FBIO_SETPOSY, test_data.vid1_xpos) < 0) {
		printf("\nFailed  FBIO_SETPOS");
		return FAILURE;
	}

	/* Enable the window */
	if (ioctl(fd_vid1, FBIOBLANK, 0)) {
		printf("Error enabling VID1\n");
		return FAILURE;
	}
	return SUCCESS;
}
/******************************************************************************
 * Example to show vid1 in YUV format, OSD0 in RGB565 format and
 * OSD1 is attribute format.
 ******************************************************************************/
static int vpbe_UE_1(void)
{
	rgb565_enable = 1;
	rgb565_enable_osd1 = 0;
	v4l2_std_id cur_std;
	int ret = 0;

	/* Setup Capture */
	if (initialize_capture(&cur_std) < 0) {
		printf("Failed to intialize capture\n");
		return ret;
	}

	DBGENTER;

	if (vpfe_input == 2) {
		test_data.vid1_width = 720;
		test_data.vid1_height = 480;
	}
	else {
		if (cur_std & V4L2_STD_NTSC) {
		test_data.vid1_width = WIDTH_NTSC;
		test_data.vid1_height = HEIGHT_NTSC;
		} else {
		test_data.vid1_width = WIDTH_PAL;
		test_data.vid1_height = HEIGHT_PAL;
		}
	}

	test_data.vid1_bpp = 16;
	test_data.vid1_vmode = FB_VMODE_INTERLACED;
	test_data.vid1_xpos = 0;
	test_data.vid1_ypos = 0;
	test_data.vid1_hzoom = 0;
	test_data.vid1_vzoom = 0;

	test_data.osd0_width = 150;
	test_data.osd0_height = 150;
	test_data.osd0_bpp = 16;
	test_data.osd0_hzoom = 0;
	test_data.osd0_vzoom = 0;
	test_data.osd0_xpos = 10;
	test_data.osd0_ypos = 10;
#if 0
	if (cur_std & V4L2_STD_NTSC)
		change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_NTSC);
	else
		change_sysfs_attrib(ATTRIB_MODE, DISPLAY_MODE_PAL);
#endif

	if (display_out) {
		if ((init_vid1_device(fd_vid1, &vid1_varInfo)) < 0) {
			printf("\nFailed to init vid1 window ");
			return FAILURE;
		}
		if ((init_osd0_device(fd_osd0, &osd0_varInfo)) < 0) {
			printf("\nFailed to init osd0 window ");
			return FAILURE;
		}

		if (mmap_vid1() == FAILURE)
			return FAILURE;

		if (mmap_osd0() == FAILURE)
			return FAILURE;
	}
	printf("Starting loop..........\n");
	start_loop();

	/* unmap video buffers */
	if (display_out) {
		if (unmap_and_disable(VID1) < 0)
			return FAILURE;
		if (unmap_and_disable(OSD0) < 0)
			return FAILURE;
	}
	DBGEXIT;
	return SUCCESS;
}

/******************************************************************************/
static void close_all_windows(void)
{
	if (fd_vid0)
		close(fd_vid0);
	if (fd_vid1)
		close(fd_vid1);
	if (fd_osd0)
		close(fd_osd0);
	if (fd_osd1)
		close(fd_osd1);
}

/******************************************************************************/
static int open_all_windows(void)
{
	if ((fd_vid0 = open(FBVID0_DEVICE, O_RDWR)) < 0)
		goto open_all_exit;
	if ((fd_vid1 = open(FBVID1_DEVICE, O_RDWR)) < 0)
		goto open_all_exit;
	if ((fd_osd0 = open(OSD0_DEVICE, O_RDWR)) < 0)
		goto open_all_exit;
	if ((fd_osd1 = open(OSD1_DEVICE, O_RDWR)) < 0)
		goto open_all_exit;
	return SUCCESS;
      open_all_exit:
	close_all_windows();
	return FAILURE;
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

/******************************************************************************
 *	Function disables all the four windows to ensure no
 *	window inter-dependency
 */
static int disable_all_windows(void)
{
	int fd;

	// Disbale OSD0
	fd = open(OSD0_DEVICE, O_RDWR);
	if (!fd) {
		printf("Error: cannot open OSD0\n");
		return -1;
	}
	if (ioctl(fd, FBIOBLANK, 1)) {
		printf("Error disabling the window OSD0\n");
		return -2;
	}
	close(fd);

	// Disbale OSD1
	fd = open(OSD1_DEVICE, O_RDWR);
	if (!fd) {
		printf("Error: cannot open OSD1\n");
		return -1;
	}
	if (ioctl(fd, FBIOBLANK, 1)) {
		printf("Error disabling the window OSD0\n");
		return -2;
	}
	close(fd);

	// Disbale VID0
	fd = open(FBVID0_DEVICE, O_RDWR);
	if (!fd) {
		printf("Error: cannot open VID0\n");
		return -1;
	}
	if (ioctl(fd, FBIOBLANK, 1)) {
		printf("Error disabling the window VID0\n");
		return -2;
	}
	close(fd);

	// Disbale VID1
	fd = open(FBVID1_DEVICE, O_RDWR);
	if (!fd) {
		printf("Error: cannot open VID1\n");
		return -1;
	}
	if (ioctl(fd, FBIOBLANK, 1)) {
		printf("Error disabling the window VID1\n");
		return -2;
	}
	close(fd);

	return SUCCESS;
}

/*******************************************************************************
* menu function
*******************************************************************************/
void menu(void)
{
	printf("Usage: fbdev_loopback -s <flag>\n");
	printf("flag = 0 for infinite loop, 1 - for 500 frames\n");
}

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

	
	for (i=0; i < NUM_BUFFERS; i++) {
		user_io_buffers[i].user_addr = CMEM_alloc(BUF_SIZE, &alloc_params);
		if (user_io_buffers[i].user_addr) {
			user_io_buffers[i].phy_addr = CMEM_getPhys(user_io_buffers[i].user_addr);
			if (0 == user_io_buffers[i].phy_addr) {
				printf("Failed to get phy cmem buffer address\n");
				return -1;
			}
		} else {
			printf("Failed to allocate cmem buffer\n");
			return -1;
		}
		printf("Got %p from CMEM, phy = %p\n", user_io_buffers[i].user_addr,
			(void *)user_io_buffers[i].phy_addr);
	}
	return 0;
}

/******************************************************************************/
/* main function */
int main(int argc, char *argv[])
{
	int ret = 0, d, index;
	char shortoptions[] = "i:s:d:w:p:m:f:";

	DBGENTER;

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
		case 's':
		case 'S':
			stress_test = atoi(optarg);
			break;
		case 'd':
		case 'D':
			display_out = atoi(optarg);
			break;

		case 'w':
		case 'W':
			save_frame = atoi(optarg);
			break;
		case 'p':
		case 'P':
			print_fn = atoi(optarg);
			break;
		default:
			menu();
			exit(1);
		}
	}

	file_fp = fopen(CAPTURE_FILE, "wb");
	if (file_fp == NULL) {
		printf("Unable to open %s\n", CAPTURE_FILE);
		exit(1);
	}

	if(vpfe_input == 2)
	{
		if(input_std == 0)
		{
			BUF_SIZE = ALIGN((640*480),4096);
			width_final = 640;
			height_final = 480;
		}
		else if(input_std == 1)
		{
			BUF_SIZE = ALIGN((736*480),4096);
			width_final = 736;
			height_final = 480;
		}
		else if(input_std == 2)
		{
			BUF_SIZE = ALIGN((736*576),4096);
			width_final = 736;
			height_final = 576;
		}
		else if(input_std == 3)
		{
			BUF_SIZE = ALIGN((1280*720),4096);
			width_final = 1280;
			height_final = 720;
		}
	}


	if (display_out) {
		if (open_all_windows() != 0) {
			printf("Test fail\n");
			exit(1);
		}
	}

	if (allocate_user_buffers() < 0) {
			printf("Test fail\n");
			exit(1);
	}

	ret = vpbe_UE_1();
	
	if (ret == SUCCESS)
		capture_streamoff();
	if (display_out) {
		restore_config();
		close_all_windows();
	}
	close(fdCapture);

	CloseIpipe(&ipipebuffer);

	DBGEXIT;
	return ret;
}
