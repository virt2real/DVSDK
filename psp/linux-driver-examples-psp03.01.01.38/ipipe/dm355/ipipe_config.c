/*
 * ipipe_config.c
 *
 * 
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
/*************************************************************************
 *	HEADER FILES
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>

/* Kernel header file, prefix path comes from makefile */
#include <media/davinci/dm355_ipipe.h>
#include "ipipe_example.h"
#include "ipipe_config.h"
#include "config_table.h"

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define MAX_WIDTH 1280

/*******************************************************************************
 *	FILE GLOBALS
 */
struct ipipe_params params;
struct ipipe_buffer t_buff;
static int ipipefd = -1;
static void config_ipipe(ipipe_dpaths_fmt_t data_fmt, int i_width,
			 int i_height, int o_width, int o_height);

void InitIpipe(ipipe_dpaths_fmt_t data_fmt, int i_width, int i_height,
	       int o_width, int o_height, struct buffer *ipipebuffer)
{
	struct ipipe_reqbufs reqbufs;
	int ret;

	/* open the IPIPE driver */
	ipipefd = open("/dev/dm355_ipipe", O_RDWR);
	if (ipipefd < 0) {
		printf("\nError opening device");
		exit(0);
	}
	config_ipipe(data_fmt, i_width, i_height, o_width, o_height);
	reqbufs.buf_type = IPIPE_BUF_OUT;
	reqbufs.size = o_height * ((o_width * 2 + 31) & (~31));
	reqbufs.count = 1;
	ret = ioctl(ipipefd, IPIPE_REQBUF, &reqbufs);
	if (ret < 0) {
		printf("\ncannot get the requested buffer");

		/*goto out; */
		exit(0);
	}
	t_buff.index = 0;
	t_buff.buf_type = IPIPE_BUF_OUT;
	ret = ioctl(ipipefd, IPIPE_QUERYBUF, &t_buff);
	if (ret < 0) {
		printf("\ncannot get out buffer address");

		/*goto out; */
		exit(0);
	}
	ipipebuffer->length = t_buff.size;
	ipipebuffer->start =
	    mmap(NULL, t_buff.size, PROT_READ | PROT_WRITE, MAP_SHARED, ipipefd,
		 t_buff.offset);
	ipipebuffer->offset = t_buff.offset;
	if (ipipebuffer->start == MAP_FAILED) {
		printf("\ncannot mmap buffer");

		/*goto out; */
		exit(0);
	}
}

void DoIPIPING(ipipe_dpaths_fmt_t data_fmt, int i_width, int i_height,
	       int o_width, int o_height, int offset)
{
	struct ipipe_convert convert;
	int ret;

	/* configure ipipe */
	config_ipipe(data_fmt, i_width, i_height, o_width, o_height);

	/* Pass capture buffer directly to ipipeiewer */
	convert.in_buff.buf_type = IPIPE_BUF_IN;
	convert.in_buff.index = -1;
	convert.in_buff.offset = offset;
	convert.in_buff.size = i_width * i_height * 2;
	convert.out_buff.index = -1;
	convert.out_buff.buf_type = IPIPE_BUF_OUT;
	convert.out_buff.offset = t_buff.offset;
	convert.out_buff.size = o_width * o_height * 2;

	/* Start ipipe operation */
	ret = ioctl(ipipefd, IPIPE_START, &convert);
	if (ret < 0) {
		printf("DoIPIPING: Cannot convert ");
		exit(0);
	}
}

void CloseIpipe(struct buffer *ipipebuffer)
{
	munmap(ipipebuffer->start, ipipebuffer->length);
	close(ipipefd);
	ipipefd = -1;
}

static void config_ipipe(ipipe_dpaths_fmt_t data_fmt, int i_width,
			 int i_height, int o_width, int o_height)
{
	int ret;
	ret = ioctl(ipipefd, IPIPE_SET_PARAM, NULL);
	if (ret < 0) {
		printf("IPIPE_SET_PARAM fail\n");
		exit(0);
	}
	ret = ioctl(ipipefd, IPIPE_GET_PARAM, &params);
	if (ret < 0) {
		printf("IPIPE_GET_PARAM fail\n");
		exit(0);
	}
	if (data_fmt == RAW2YUV) {
		params.ipipeif_param.source = SDRAM_RAW;
	} else {
		params.ipipeif_param.source = SDRAM_YUV;
	}
	params.ipipeif_param.hnum = i_width;
	params.ipipeif_param.vnum = i_height;
	//params.ipipeif_param.glob_hor_size = 1200;
	params.ipipeif_param.glob_hor_size = 1290;
	params.ipipeif_param.glob_ver_size = i_height + 10;
//	params.ipipeif_param.adofs = ((i_width * 2 + 31) & (~31));
	params.ipipeif_param.adofs = ((i_width * 1));
	params.ipipeif_param.ialaw = 1;
	params.ipipeif_param.pack_mode = 1;
	params.ipipeif_param.gain = 0x200;
	params.ipipeif_param.clk_div = DIVIDE_SIXTH;
	params.ipipe_dpaths_fmt = data_fmt;
	params.ipipe_vst = 0;
	params.ipipe_hst = 0;
	params.ipipe_vsz = i_height - 1;
	params.ipipe_hsz = i_width - 1;
	if (o_width > 640) {
		params.rsz_rsc_param[0].rsz_h_dif = (i_width * 256 / o_width);
		params.rsz_rsc_param[0].rsz_v_dif =
		    ((i_height) * 256 / o_height);
		params.rsz_rsc_param[0].rsz_o_hsz = o_width - 1;
		params.rsz_rsc_param[0].rsz_o_vsz = o_height - 1;
		params.ext_mem_param[0].rsz_sdr_oft =
		    ((o_width * 2 + 31) & (~31));
		params.ext_mem_param[0].rsz_sdr_ptr_e = o_height;
		params.rsz_en[0] = ENABLE;
		params.rsz_en[1] = DISABLE;
	} else {
		params.rsz_rsc_param[1].rsz_h_dif = (i_width * 256 / o_width);
		params.rsz_rsc_param[1].rsz_v_dif =
		    (i_height * 256 / o_height);;
		params.rsz_rsc_param[1].rsz_o_hsz = o_width - 1;
		params.rsz_rsc_param[1].rsz_o_vsz = o_height - 1;
		params.ext_mem_param[1].rsz_sdr_oft =
		    ((o_width * 2 + 31) & (~31));
		params.ext_mem_param[1].rsz_sdr_ptr_e = o_height;
		params.rsz_en[1] = ENABLE;
		params.rsz_en[0] = DISABLE;
	}
	params.prefilter.pre_en = DISABLE;
	params.false_color_suppresion.fcs_en = DISABLE;
	params.edge_enhancer.yee_emf = DISABLE;
	params.rgb2yuv.yuv_adj_ctr = 0x10;
	params.wb.wb2_dgn = 0x200;
	params.wb.wb2_wg_r = 0x110;
	params.wb.wb2_wg_gr = 0xf0;
	params.wb.wb2_wg_gb = 0xf0;
	params.wb.wb2_wg_b = 0x130;
	params.ipipe_colpat_elep = GREEN_RED;
	params.ipipe_colpat_elop = RED;
	params.ipipe_colpat_olep = BLUE;
	params.ipipe_colpat_olop = GREEN_BLUE;
	params.rgb2rgb.gmm_cfg_bypr = 0;
	params.rgb2rgb.gmm_cfg_bypg = 0;
	params.rgb2rgb.gmm_cfg_bypb = 0;
	params.rgb2rgb.gmm_cfg_tbl = 1;

	ret = ioctl(ipipefd, IPIPE_SET_PARAM, &params);
	if (ret < 0) {
		printf("IPIPE_SET_PARAM fail\n");
		exit(0);
	}
}
