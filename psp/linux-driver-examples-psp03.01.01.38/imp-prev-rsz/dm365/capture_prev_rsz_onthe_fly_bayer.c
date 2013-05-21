/*
 * capture_prev_rsz_onthe_fly_bayer - Capture from MT9T031, preview and resize
 * in on the fly mode
 *
 * This example shows how to do capture from MT9T031 and
 * do on the fly processing on the captured image such as IPIPE preview
 * Resize and  format conversion. Here is the configuration of IP for
 * this usecase
 *
 * MT9T031 -> CCDC/ISIF ->IPIPEIF ->IPIPE->Resizer->SDRAM
 *
 * NOTE: This application requires CMEM
 *
 * In this mode, CCDC output is sent to IPIPE and Resizer. 
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
#include <media/davinci/vpfe_capture.h>
#include <media/davinci/imp_previewer.h>
#include <media/davinci/imp_resizer.h>
#include <media/davinci/dm365_ipipe.h>
#include "cmem.h"

char dev_name_prev[1][30] = {"/dev/davinci_previewer"};
char dev_name_rsz[1][30] = {"/dev/davinci_resizer"};

#define APP_NUM_BUFS 6
#define CAPTURE_DEVICE  "/dev/video0"
#define V4L2VID0_DEVICE    "/dev/video2"
#define V4L2VID1_DEVICE    "/dev/video3"
#define CLEAR(x) memset (&(x), 0, sizeof (x))
/* 0 - UYVY, 1 - NV12 */
#define CAMERA_INPUT_MT9T001	"Camera"
#define MAX_STDS	11
#define DISPLAY_INTERFACE_COMPOSITE	"COMPOSITE"
#define DISPLAY_INTERFACE_COMPONENT	"COMPONENT"
#define DISPLAY_MODE_PAL	"PAL"
#define DISPLAY_MODE_NTSC	"NTSC"
#define DISPLAY_MODE_720P	"720P-60"		
#define DISPLAY_MODE_1080I	"1080I-30"		
/* Standards and output information */
#define ATTRIB_MODE		"mode"
#define ATTRIB_OUTPUT		"output"
int max_stds = MAX_STDS;
int regular_col_pat = 1;

/* display 0 - output1 (RSZ_A)) or 1 - output2 (RSZ_B) from resizer */
static int disp_second_output;

/* second output width and height */
static int second_out_width = 320;
static int second_out_height = 240;
int second_output_offset;

struct capt_std_params {
	v4l2_std_id std;
	/* input image params */
	unsigned int scan_width;
	unsigned int scan_height;
	/* crop params */
	struct v4l2_rect crop;
	/* output image params */
	unsigned int image_width;
	unsigned int image_height;
	char *name;
};
	
struct capt_std_params mt9t001_std_params[MAX_STDS] = {
	{	
		//.std = V4L2_STD_MT9T001_VGA_30FPS,
		.scan_width = 640,
		.scan_height = 480,
		.crop = { 0, 0, 640, 480},
		.image_width = 720,
		.image_height = 480,
		.name = "V4L2_STD_MT9T001_VGA_30FPS",
	},
	{
		//.std = V4L2_STD_MT9T001_480p_30FPS,
		.scan_width = 720,
		.scan_height = 480,
		.crop = { 0 , 0, 720, 480},
		.image_width = 720,
		.image_height = 480,
		.name = "V4L2_STD_MT9T001_480p_30FPS",
	},
	{
		//.std = V4L2_STD_MT9T001_576p_25FPS,
		.scan_width = 720,
		.scan_height = 576,
		.crop = { 0 , 0, 720, 576},
		.image_width = 720,
		.image_height = 480,
		.name = "V4L2_STD_MT9T001_576p_25FPS",
	},
	{
		//.std = V4L2_STD_MT9T001_720p_30FPS,
		.scan_width = 1280,
		.scan_height = 720,
		.crop = { 0 , 0, 1280, 720},
		.image_width = 1280,
		.image_height = 720,
		.name = "V4L2_STD_MT9T001_720p_30FPS",
	},
	{
		//.std = V4L2_STD_MT9T001_1080p_18FPS,
		.scan_width = 1920,
		.scan_height = 1080,
		.crop = { 0 , 0, 1920, 1080},
		.image_width = 1920,
		.image_height = 1080,
		.name = "V4L2_STD_MT9T001_1080p_18FPS",
	},
	{
		//.std = V4L2_STD_MT9T001_QXGA_12FPS,
		.scan_width = 2048,
		.scan_height = 1536,
		.crop = { 0 , 0, 2048, 1536},
		.image_width = 1920,
		.image_height = 1080,
		.name = "V4L2_STD_MT9T001_QXGA_12FPS",
	}
};

struct capt_std_params mt9p031_std_params[MAX_STDS] = {
	{	
		//.std = V4L2_STD_MT9P031_VGA_30FPS,
		.scan_width = 640,
		.scan_height = 480,
		.crop = { 0 , 0, 640, 480},
		.image_width = 720,
		.image_height = 480,
		.name = "V4L2_STD_MT9P031_VGA_30FPS",
	},
	{
		//.std = V4L2_STD_MT9P031_480p_30FPS,
		.scan_width = 720,
		.scan_height = 480,
		.crop = { 0 , 0, 720, 480},
		.image_width = 720,
		.image_height = 480,
		.name = "V4L2_STD_MT9P031_480p_30FPS",
	},
	{
		//.std = V4L2_STD_MT9P031_576p_25FPS,
		.scan_width = 720,
		.scan_height = 576,
		.crop = { 0 , 0, 720, 576},
		.image_width = 720,
		.image_height = 576,
		.name = "V4L2_STD_MT9P031_576p_25FPS",
	},
	{
		//.std = V4L2_STD_MT9P031_720p_60FPS,
		.scan_width = 1280,
		.scan_height = 720,
		.crop = { 0 , 0, 1280, 720},
		.image_width = 1280,
		.image_height = 720,
		.name = "V4L2_STD_MT9P031_720p_60FPS",
	},
	{
		//.std = V4L2_STD_MT9P031_1080p_30FPS,
		.scan_width = 1920,
		.scan_height = 1080,
		.crop = { 0 , 0, 1920, 1080},
		.image_width = 1920,
		.image_height = 1080,
		.name = "V4L2_STD_MT9P031_1080p_30FPS",
	},
	{
		//.std = V4L2_STD_MT9P031_1080p_25FPS,
		.scan_width = 1920,
		.scan_height = 1080,
		.crop = { 0 , 0, 1920, 1080},
		.image_width = 1920,
		.image_height = 1080,
		.name = "V4L2_STD_MT9P031_1080p_25FPS",
	},
	{	
		//.std = V4L2_STD_MT9P031_SXGA_30FPS,
		.scan_width = 1280,
		.scan_height = 1024,
		.crop = { 0 , 0, 1280, 1024},
		.image_width = 1280,
		.image_height = 720,
		.name = "V4L2_STD_MT9P031_SXGA_30FPS",
	},
	{	
		//.std = V4L2_STD_MT9P031_UXGA_30FPS,
		.scan_width = 1600,
		.scan_height = 1200,
		.crop = { 0 , 0, 1600, 1200},
		.image_width = 1920,
		.image_height = 1080,
		.name = "V4L2_STD_MT9P031_UXGA_30FPS",
	},
	{	
		//.std = V4L2_STD_MT9P031_QXGA_15FPS,
		.scan_width = 2048,
		.scan_height = 1536,
		.crop = { 0 , 0, 2048, 1536},
		.image_width = 1920,
		.image_height = 1080,
		.name = "V4L2_STD_MT9P031_QXGA_15FPS",
	},
	{	
		//.std = V4L2_STD_MT9P031_720p_30FPS,
		.scan_width = 1280,
		.scan_height = 720,
		.crop = { 0 , 0, 1280, 720},
		.image_width = 1280,
		.image_height = 720,
		.name = "V4L2_STD_MT9P031_720p_30FPS",
	},
	{	
		//.std = V4L2_STD_MT9P031_960p_30FPS,
		.scan_width = 1280,
		.scan_height = 960,
		.crop = { 0 , 0, 1280, 960},
		.image_width = 1280,
		.image_height = 720,
		.name = "V4L2_STD_MT9P031_960p_30FPS",
	},
};

/* used for indexing into above table */
static unsigned int in_std;
	
/* input std param for selected standard */
struct capt_std_params input_std_params;

unsigned char camera_input[20];
int cam_input;

int printfn = 1;

struct app_buf_type {
    void *start;
    int offset;
    int length;
    int index;
};
	
static int output_format;

#define ALIGN(x, y)	(((x + (y-1))/y)*y)

int buf_size = ALIGN((1920*1080*2), 4096);

struct buf_info {
	void *user_addr;
	unsigned long phy_addr;
};

struct buf_info capture_buffers[APP_NUM_BUFS];
struct buf_info display_buffers[APP_NUM_BUFS];

static int display_image_size;
/* to enable gamma correction, enable this */
static int gamma_flag;

//enum ccdc_compress_alg compress_alg = CCDC_ALAW;
//enum ccdc_compress_alg compress_alg = CCDC_DPCM;
enum ccdc_compress_alg compress_alg = CCDC_NO_COMPRESSION;

/* to test mt9p031 set below value to 1 */
int mt_t_or_p = 0;

// flag to enable linearization
static int linearization_en;
// flag to enable color space conversion
// input sensor should output CMYG pattern instead of RGGB
// to test this. This is currently just used for unit
// test verification
static int csc_en;

// vertical line defect correction enable
static int vldfc_en;

// enable culling
// static int en_culling;
static int en_culling;

#define IN_WIDTH 	720
#define IN_HEIGHT 	480
#define OUT_WIDTH 	720
#define OUT_HEIGHT 	480
#define BYTESPERPIXEL 2

static int start_loopCnt = 500;
static int stress_test = 1;
static struct v4l2_rect crop_default = { 320, 240, 320, 240 };
static int en_crop;

static unsigned long long prev_ts;
static unsigned long long curr_ts;
static unsigned long fp_period_average;
static unsigned long fp_period_max;
static unsigned long fp_period_min;
static unsigned long fp_period;

void usage()
{
	printf("Usage:capture_prev_rsz_onthe_fly\n");
}

int init_resizer(unsigned int user_mode, int out_width, int out_height)
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
		printf("Successfully set mode to single shot in resizer\n");
	else {
		printf("failed to set mode to single shot in resizer\n");
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
		if (output_format)
			rsz_cont_config.output2.pix_fmt = IPIPE_YUV420SP;
		else
			rsz_cont_config.output2.pix_fmt = IPIPE_UYVY;
	} else 
		rsz_cont_config.output2.enable = 0;
//	rsz_cont_config.output1.h_flip = 1;
	rsz_chan_config.oper_mode = user_mode;
	rsz_chan_config.chain = 1;
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

int init_previewer(unsigned int user_mode, int in_format)
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

#if 0
/*
	Gb B
	R Gr
*/
	prev_cont_config.input.colp_elep= IPIPE_RED;
	prev_cont_config.input.colp_elop= IPIPE_GREEN_RED;
	prev_cont_config.input.colp_olep= IPIPE_GREEN_BLUE;
	prev_cont_config.input.colp_olop= IPIPE_BLUE;
#endif

/*
	Gr R
	B Gb
*/
	
	/* Some reason, MT9P031 color pattern is flipped horizontally
	 * for some of the scan resolution
	 */
	if (regular_col_pat) {
		prev_cont_config.input.colp_elep= IPIPE_BLUE;
		prev_cont_config.input.colp_elop= IPIPE_GREEN_BLUE;
		prev_cont_config.input.colp_olep= IPIPE_GREEN_RED;
		prev_cont_config.input.colp_olop= IPIPE_RED;
	} else {
		prev_cont_config.input.colp_elep= IPIPE_GREEN_BLUE;
		prev_cont_config.input.colp_elop= IPIPE_BLUE;
		prev_cont_config.input.colp_olep= IPIPE_RED;
		prev_cont_config.input.colp_olop= IPIPE_GREEN_RED;
	}
/* 
   	B Gb
	Gr R
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
#if 0
		if (cap.module_id == PREV_WB) {
			wb.gain_r.integer = 2;
			wb.gain_r.decimal = 0;
			wb.gain_gr.integer = 2;
			wb.gain_gr.decimal = 0;
			wb.gain_gb.integer = 2;
			wb.gain_gb.decimal = 0;
			wb.gain_b.integer = 2;
			wb.gain_b.decimal = 0;
			wb.ofst_r = 0;
			wb.ofst_gb = 0;
			wb.ofst_b = 0;
			mod_param.len = sizeof(struct prev_wb);
			mod_param.param = &wb;

		} else if (cap.module_id == PREV_LUM_ADJ) {
			lum_adj.brightness = 0;
			lum_adj.contrast = 10; 
			mod_param.len = sizeof (struct prev_lum_adj);
			mod_param.param = &lum_adj;
#if 1
		} else if (cap.module_id == PREV_GAMMA && gamma_flag && (!in_format)) {
			printf("Setting gamma for %s\n", cap.module_name);
			bzero((void *)&gamma, sizeof (struct prev_gamma));
			gamma.bypass_r = 0;
			gamma.bypass_b = 0;
			gamma.bypass_g = 0;
			gamma.tbl_sel = IPIPE_GAMMA_TBL_ROM;
			mod_param.len = sizeof (struct prev_gamma);
			mod_param.param = &gamma;
#endif
		}
		else {

#endif
			// using defaults
			printf("Setting default for %s\n", cap.module_name);
			mod_param.param = NULL;
#if 0
		}
#endif
		if (ioctl(preview_fd, PREV_S_PARAM, &mod_param) < 0) {
			printf("Error in Setting %s params from driver\n", cap.module_name);
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
	struct ccdc_config_params_raw raw_params;
	/* Change these values for testing Gain - Offsets */
	struct ccdc_float_16 r = {0, 511};
	struct ccdc_float_16 gr = {0, 511};
	struct ccdc_float_16 gb = {0, 511};
	struct ccdc_float_16 b = {0, 511};
	struct ccdc_float_8 csc_coef_val = { 1, 0 };
	int i;

	bzero(&raw_params, sizeof(raw_params));

	/* First get the parameters */
	if (-1 == ioctl(capt_fd, VPFE_CMD_G_CCDC_RAW_PARAMS, &raw_params)) {
		printf("InitDevice:ioctl:VPFE_CMD_G_CCDC_PARAMS, %p", &raw_params);
		return -1;
	}

	raw_params.compress.alg = CCDC_NO_COMPRESSION;
	raw_params.gain_offset.gain.r_ye = r; 
	raw_params.gain_offset.gain.gr_cy = gr;
	raw_params.gain_offset.gain.gb_g = gb;
	raw_params.gain_offset.gain.b_mg = b;
	raw_params.gain_offset.gain_sdram_en = 1;
	raw_params.gain_offset.gain_ipipe_en = 1;
	raw_params.gain_offset.offset = 0;
	raw_params.gain_offset.offset_sdram_en = 1;
	/* To test linearization, set this to 1, and update the
	 * linearization table with correct data
	 */
	if (linearization_en) {
		raw_params.linearize.en = 1;
		raw_params.linearize.corr_shft = CCDC_1BIT_SHIFT;
		raw_params.linearize.scale_fact.integer = 0;
		raw_params.linearize.scale_fact.decimal = 10;

		for (i = 0; i < CCDC_LINEAR_TAB_SIZE; i++)
			raw_params.linearize.table[i] = i;	
	} else {
		raw_params.linearize.en = 0;
	}
	
	/* CSC */
	if (csc_en) {
		raw_params.df_csc.df_or_csc = 0;
		raw_params.df_csc.csc.en = 1;
		/* I am hardcoding this here. But this should
		 * really match with that of the capture standard
		 */
		raw_params.df_csc.start_pix = 1;
		raw_params.df_csc.num_pixels = 720;
		raw_params.df_csc.start_line = 1;
		raw_params.df_csc.num_lines = 480;
		/* These are unit test values. For real case, use
		 * correct values in this table
		 */
		raw_params.df_csc.csc.coeff[0] = csc_coef_val;
		raw_params.df_csc.csc.coeff[1].decimal = 1;
		raw_params.df_csc.csc.coeff[2].decimal = 2;
		raw_params.df_csc.csc.coeff[3].decimal = 3;
		raw_params.df_csc.csc.coeff[4].decimal = 4;
		raw_params.df_csc.csc.coeff[5].decimal = 5;
		raw_params.df_csc.csc.coeff[6].decimal = 6;
		raw_params.df_csc.csc.coeff[7].decimal = 7;
		raw_params.df_csc.csc.coeff[8].decimal = 8;
		raw_params.df_csc.csc.coeff[9].decimal = 9;
		raw_params.df_csc.csc.coeff[10].decimal = 10;
		raw_params.df_csc.csc.coeff[11].decimal = 11;
		raw_params.df_csc.csc.coeff[12].decimal = 12;
		raw_params.df_csc.csc.coeff[13].decimal = 13;
		raw_params.df_csc.csc.coeff[14].decimal = 14;
		raw_params.df_csc.csc.coeff[15].decimal = 15;
		
	} else {
		raw_params.df_csc.df_or_csc = 0;
		raw_params.df_csc.csc.en = 0;
	}

	/* vertical line defect correction */
	if (vldfc_en) {
		raw_params.dfc.en = 1;
		// correction method
		raw_params.dfc.corr_mode = CCDC_VDFC_HORZ_INTERPOL_IF_SAT;
		// not pixels upper than the defect corrected
		raw_params.dfc.corr_whole_line = 1;
		raw_params.dfc.def_level_shift = CCDC_VDFC_SHIFT_2;
		raw_params.dfc.def_sat_level = 20;
		raw_params.dfc.num_vdefects = 7;
		for (i = 0; i < raw_params.dfc.num_vdefects; i++) {
			raw_params.dfc.table[i].pos_vert = i;
			raw_params.dfc.table[i].pos_horz = i + 1;
			raw_params.dfc.table[i].level_at_pos = i + 5;
			raw_params.dfc.table[i].level_up_pixels = i + 6;
			raw_params.dfc.table[i].level_low_pixels = i + 7;
		}
		printf("DFC enabled\n");
	} else {
		raw_params.dfc.en = 0;
	}

	if (en_culling) {
		
		printf("Culling enabled\n");
		raw_params.culling.hcpat_odd  = 0xaa;
		raw_params.culling.hcpat_even = 0xaa;
		raw_params.culling.vcpat = 0x55;
		raw_params.culling.en_lpf = 1;
	} else {
		raw_params.culling.hcpat_odd  = 0xFF;
		raw_params.culling.hcpat_even = 0xFF;
		raw_params.culling.vcpat = 0xFF;
	}
	
	raw_params.col_pat_field0.olop = CCDC_GREEN_BLUE;
	raw_params.col_pat_field0.olep = CCDC_BLUE;
	raw_params.col_pat_field0.elop = CCDC_RED;
	raw_params.col_pat_field0.elep = CCDC_GREEN_RED;
	raw_params.col_pat_field1.olop = CCDC_GREEN_BLUE;
	raw_params.col_pat_field1.olep = CCDC_BLUE;
	raw_params.col_pat_field1.elop = CCDC_RED;
	raw_params.col_pat_field1.elep = CCDC_GREEN_RED;
	raw_params.data_size = CCDC_12_BITS;
	raw_params.data_shift = CCDC_NO_SHIFT;

	printf("VPFE_CMD_S_CCDC_RAW_PARAMS, size = %d, address = %p\n", sizeof(raw_params),
				&raw_params);
	if (-1 == ioctl(capt_fd, VPFE_CMD_S_CCDC_RAW_PARAMS, &raw_params)) {
		printf("InitDevice:ioctl:VPFE_CMD_S_CCDC_PARAMS, %p", &raw_params);
		return -1;
	}

	return 0;
}
	
static int set_data_format(int fdCapture, v4l2_std_id std, int width, int height)
{
	int ret;
	v4l2_std_id ipipe_std, cur_std;
	struct v4l2_format fmt;
	struct v4l2_input input;
	struct v4l2_crop crop;
	cur_std = ipipe_std = std;

	printf("set_data_format:setting std to %d\n", (int)cur_std);

	// first set the input
	input.type = V4L2_INPUT_TYPE_CAMERA;
	input.index = 0;
  	while (-EINVAL != ioctl(fdCapture, VIDIOC_ENUMINPUT, &input)) { 
		printf("input.name = %s\n", input.name);
		if (!strcmp(input.name, camera_input))
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
		perror("configCCDCraw error");
		return -1;
	} else {
		printf("\nconfigCCDCraw Done\n");
	}


	CLEAR(fmt);
	fmt.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	fmt.fmt.pix.width = width;
	fmt.fmt.pix.height = height;
	if (output_format) {
		printf("Setting format to V4L2_PIX_FMT_NV12 at capture\n");
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
		fmt.fmt.pix.bytesperline = width;
	}
	else {
		printf("Setting format to V4L2_PIX_FMT_UYVY at capture\n");
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
	}
	fmt.fmt.pix.field = V4L2_FIELD_NONE;
	if (-1 == ioctl(fdCapture, VIDIOC_S_FMT, &fmt)) {
		perror("set_data_format:ioctl:VIDIOC_S_FMT");
		return -1;
	} else
		printf("\nS_FMT Done\n");

	if (en_crop) {
		printf("******Cropping the input @%d,%d,%d,%d***********\n", crop_default.top,
			crop_default.left, crop_default.width, crop_default.height);
		input_std_params.crop = crop_default;
		CLEAR(crop);
		crop.c = input_std_params.crop;
		crop.type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
		if (-1 == ioctl(fdCapture, VIDIOC_S_CROP, &crop)) {
			perror("set_data_format:ioctl:VIDIOC_S_CROP");
			return -1;
		} else
			printf("\nS_CROP Done\n");

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

int init_camera_capture(v4l2_std_id std, int width, int height)
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
	if (set_data_format(capt_fd, std, width, height) < 0) {
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
		} else
			buf.m.userptr = (unsigned long)display_buffers[i].user_addr;
		printf("Queing buffer:%d\n", i);

		if (-1 == ioctl(fd_vid1, VIDIOC_QBUF, &buf)) {
			printf("start_display_streaming:ioctl:VIDIOC_QBUF:error\n");
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
int init_display_device(int device, int width, int height)
{
	int fdDisplay;
	struct v4l2_requestbuffers req;
	struct v4l2_buffer buf;
	int a, ret, i,j;
	struct v4l2_format fmt;
	struct v4l2_crop crop;
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

	fmt.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	if (output_format) {
		printf("Setting display pixel format to V4L2_PIX_FMT_NV12\n");
		fmt.fmt.pix.bytesperline = ((width + 31) & ~31);
		fmt.fmt.pix.sizeimage= ((fmt.fmt.pix.bytesperline * height) +
			       (fmt.fmt.pix.bytesperline * (height >> 1)));
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_NV12;
		fmt.fmt.pix.width = width;
		fmt.fmt.pix.height = height;
	} else {
		printf("Setting display pixel format to V4L2_PIX_FMT_UYVY\n");
		fmt.fmt.pix.pixelformat = V4L2_PIX_FMT_UYVY;
		fmt.fmt.pix.bytesperline = width * BYTESPERPIXEL;
		fmt.fmt.pix.sizeimage= (fmt.fmt.pix.bytesperline * height);
	}

	ret = ioctl(fdDisplay, VIDIOC_S_FMT, &fmt);
	if (ret) {
		perror("VIDIOC_S_FMT failed\n");
		goto error;
	}

	req.count = APP_NUM_BUFS/2;
	req.type = V4L2_BUF_TYPE_VIDEO_OUTPUT;
	req.memory = V4L2_MEMORY_USERPTR;
	ret = ioctl(fdDisplay, VIDIOC_REQBUFS, &req);
	if (ret) {
		perror("cannot allocate memory\n");
		goto error;
	}

	start_display_streaming(fdDisplay);
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
	int i, err = 0;
	enum v4l2_buf_type type;
	type = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	
	if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type)) {
		perror("cleanup_capture :ioctl:VIDIOC_STREAMOFF");
		err = -1;
	}

	if (close(fd) < 0) {
		perror("Error in closing device\n");
		err = -1;
	}
	return err;
}

int cleanup_preview(int fd)
{
	int i, err = 0;
	if (close(fd) < 0) {
		perror("Error in closing preview device\n");
		err = -1;
	}
	return err;
}


int cleanup_display(int fd)
{
	int i,err = 0;
	enum v4l2_buf_type type;

	type = V4L2_BUF_TYPE_VIDEO_OUTPUT;

	if (-1 == ioctl(fd, VIDIOC_STREAMOFF, &type)) {
		perror("cleanup_display :ioctl:VIDIOC_STREAMOFF");
		err = -1;
	}

	if (close(fd) < 0) {
		perror("Error in closing device\n");
		err = -1;
	}
	return err;
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

int main(int argc, char *argp[])
{
	char shortoptions[] = "x:t:f:p:s:m:i:o:c:";
	int mode = O_RDWR,c,ret,index, display_index;
	int preview_fd, rsz_fd, capt_fd, display_fd, dev_idx;
	unsigned int oper_mode, user_mode=IMP_MODE_CONTINUOUS;
	int level;
	int width = 720, height = 480;
	int *capbuf_addr;
	fd_set fds;
	struct timeval tv;
	int r, i;
	int quit=0;
	struct timezone zone;
	int in_format=0;
	void *display_buf;
	void *src, *dest;
	int sizeimage;
	struct v4l2_buffer buf;
	int captFrmCnt = 0;
	struct v4l2_buffer cap_buf, disp_buf;

	strcpy(camera_input, CAMERA_INPUT_MT9T001);

	for(;;) {
		c = getopt_long(argc, argp, shortoptions, NULL, (void *)&index);
		if(-1 == c)
			break;
		switch(c) {
			case 't':
				gamma_flag = atoi(optarg);
				break;
			case 'f':
				output_format = atoi(optarg);
				if (output_format < 0 || output_format > 1) {
					printf("Choose 0 - UYVY 1 - NV12 for output pix format\n");
					exit(1);
				}
				break;
			case 'm':
				in_std = atoi(optarg);
				break;
			case 'x':
				disp_second_output = atoi(optarg);
				break;
			case 's':
			case 'S':
				stress_test = atoi(optarg);
				break;
			case 'i':
			case 'I':
				cam_input = atoi(optarg);
				if (cam_input != 0 && cam_input != 1) {
					printf("Select source as as 0 or 1\n");
					exit(0);
				}
				if (cam_input == 0) {
					strcpy(camera_input, CAMERA_INPUT_MT9T001);
					max_stds = 6;
				}
 				break;		
			case 'p':
				printfn = atoi(optarg);
				break;
			case 'c':
				en_crop = atoi(optarg);
				break;

			default:
				usage();
				exit(1);
		}
	}

	if (in_std >= max_stds) {
		printf("in_std is more than maximum, max = %d\n", max_stds);
		exit(1);
	}

	if (!cam_input) {
		input_std_params = mt9t001_std_params[in_std];
	} else {
		input_std_params = mt9p031_std_params[in_std];
	}

	printf("input_std_params: name = %s\n", input_std_params.name);
	printf("input_std_params: output width = %d\n", input_std_params.image_width);

	if (output_format)
		sizeimage = (input_std_params.image_width * input_std_params.image_height) +
			    (input_std_params.image_width * (input_std_params.image_height >>1));
	else
		sizeimage = (input_std_params.image_width * input_std_params.image_height *
			     BYTESPERPIXEL);

	if (allocate_user_buffers() < 0) {
		printf("Unable to Allocate user buffers\n");
		exit(1);
	}	
	// intialize resizer in continuous mode
	rsz_fd = init_resizer(user_mode,
			input_std_params.image_width,
			input_std_params.image_height);

	if (rsz_fd < 0) {
		printf("Error in initializing resizer\n");
		exit(1);
	}

	// initialize previewer in continuous mode
	preview_fd = init_previewer(user_mode, in_format);

	if (preview_fd < 0) {
		close(rsz_fd);
		exit(1);
	}
	
	// intialize capture
	capt_fd = init_camera_capture(
			input_std_params.std,
			input_std_params.image_width,
			input_std_params.image_height);

	if (capt_fd < 0) {
		close(preview_fd);
		close(rsz_fd);
		exit(1);
	}

	if (!output_format)
		second_output_offset =  input_std_params.image_width *
					input_std_params.image_height * 2;
	else
		second_output_offset = ALIGN(input_std_params.image_width,32) *
					  input_std_params.image_height * 1.5;

	second_output_offset = ALIGN(second_output_offset, 4096);

	printf("Second output offset = %d\n", second_output_offset);
	if (!disp_second_output)
		display_fd = init_display_device(0,
				input_std_params.image_width,
				input_std_params.image_height);
	else
		display_fd = init_display_device(0, second_out_width, second_out_height);

	if (display_fd < 0) {
		cleanup_preview(preview_fd);
		close(rsz_fd);
		close(capt_fd);
		exit(1);
	}

	printf("Initialized display\n");	

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
		if (captFrmCnt > 500)
			break;

	}

	printf("Cleaning capture\n");
	cleanup_capture(capt_fd);
	printf("Cleaning display\n");
	cleanup_display(display_fd);
	printf("Cleaning display - end\n");
	cleanup_preview(preview_fd);
	printf("closing preview- end\n");
	close(rsz_fd);
	printf("closing resize - end\n");
	exit(0);
}


