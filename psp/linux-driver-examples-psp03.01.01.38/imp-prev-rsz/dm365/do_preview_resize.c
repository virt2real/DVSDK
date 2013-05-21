/*
 * do_preview_resize.c
 *
 * Shows how to process a frame using IPIPE and Resizer in One shot mode
 * This requires CMEM
 * 
 * The following IP configuration used for this use case
 *
 * SDRAM -> IPIPEIF -> IPIPE->Resizer -> SDRAM
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

char *dev_name_prev = "/dev/davinci_previewer";
char *dev_name_rsz = "/dev/davinci_resizer";

void usage()
{
	printf("Usage:do_preview_resize -r 0 -i file -o file \n");
}
#define MAX_WIDTH  1920
#define MAX_HEIGHT  1080
#define BYTESPERLINE 2
#define HEIGHT 480 
#define WIDTH 720 
#define OUT_WIDTH  720
#define OUT_HEIGHT 480
#define BUF_SIZE ((1280*720) + (1280*360) + 32)
#define APP_IN_BUFS 1
#define APP_OUT1_BUFS 1
#define APP_OUT2_BUFS 1

struct pix_defect {
	short x_pos;
	short y_pos;
};

/* to print debug logs */
static int en_log = 1;

#define NUM_DPS 10
#define DEFECT_PIX_VAL 0x3FF

static int add_pix_defects;
static int correct_pix_defects;
/* 0 - lut, 1 - otf */
static int lut_or_otf;

struct pix_defect pix_defect_tbl[NUM_DPS] = {
#if 0
		{360, 60},
		{500, 60},
		{360, 80},
		{500, 80},
		{360, 100},
		{500, 100},
		{360, 120},
		{500, 120},
		{360, 140},
		{500, 140}
#endif
		{0, 20},
		{1, 20},
		{2, 20},
		{3, 20},
		{4, 20},
		{5, 20},
		{6, 20},
		{7, 20},
		{8, 20},
		{9, 20}
};

char in_buf[MAX_WIDTH*MAX_HEIGHT*BYTESPERLINE];
static struct prev_lutdpc dpc;
static struct ipipe_lutdpc_entry dpc_table[NUM_DPS];

/***********************************************************************
 *  OTF DPC config params 
 ***********************************************************************/
/* 0 - min-max, 1 - min-max2 */
static int otf_min_max;
/* applicable only for mix-max2 */
/* 0 - otf_2.0, 1 - otf 3.0 */
static int otf_20_30;
static struct prev_otfdpc otfdpc;

/***********************************************************************
 * NF config params
 ***********************************************************************/
static char en_nf1;
static char en_nf2;
static struct prev_nf nf_params = {
	.en = 1,
	.gr_sample_meth = IPIPE_NF_BOX,
	.shft_val = 0,
	.spread_val = 3,
	.apply_lsc_gain = 0,
	.thr = { 120, 130, 135, 140, 150, 160, 170, 200 },
	.str = { 16, 16, 15, 15, 15, 15, 15, 15 },
	.edge_det_min_thr = 0,
	.edge_det_max_thr = 2047
};

/***********************************************************************
 * GIC config params
 ***********************************************************************/
static char en_gic;
static struct prev_gic gic_params = {
	.en = 1,
	.gain = 128,
//	.gic_alg = IPIPE_GIC_ALG_CONST_GAIN,
	.gic_alg = IPIPE_GIC_ALG_ADAPT_GAIN,
	.thr_sel = IPIPE_GIC_THR_REG,
	.thr  = 512,
	.slope = 512,
	.apply_lsc_gain = 0,
	.wt_fn_type = IPIPE_GIC_WT_FN_TYP_DIF,
};	
	
/***********************************************************************
 * WB config params
 ***********************************************************************/

static char en_wb;
static struct prev_wb wb_params = {
	.ofst_r = 0,
	.ofst_gr = 0,
	.ofst_gb = 0,
	.ofst_b = 0,
#if 0
	.gain_r = { 1 , 511 },
	.gain_gr = { 1, 511 },
	.gain_gb = { 1, 511 },
	.gain_b = { 1, 511 }
#endif
	.gain_r = { 2 , 0 },
	.gain_gr = {2, 0 },
	.gain_gb = { 2, 0 },
	.gain_b = { 2, 0 }
};

/***********************************************************************
 * CFA config params
 ***********************************************************************/
static char en_cfa; 
static struct prev_cfa cfa_params = {
	//.alg = IPIPE_CFA_ALG_2DIRAC,
	.alg = IPIPE_CFA_ALG_2DIRAC_DAA,
	// for 2DIR
	.hp_mix_thr_2dir = 30,
	.hp_mix_slope_2dir = 10,
	.hpf_thr_2dir = 1024,
	.hpf_slp_2dir = 0,
	.dir_thr_2dir = 4,
	.dir_slope_2dir = 10, 
	.nd_wt_2dir = 16,
	// for DAA
	.hue_fract_daa = 24,
	.edge_thr_daa = 25,
	.thr_min_daa = 27,
	.thr_slope_daa = 20,
	.slope_min_daa = 50,
	.slope_slope_daa = 40,
	.lp_wt_daa = 16
};

/***********************************************************************
 * RGB2RGB - 1/2 config params
 ***********************************************************************/
static char en_rgb2rgb_1;
static char en_rgb2rgb_2;

static struct prev_rgb2rgb rgb2rgb_1_params = {
#if 0
	.coef_rr = { 1, 0 },
	.coef_gr = { 0, 0 },
	.coef_br = { 0, 0 },
	.coef_rg = { 0, 0 },
	.coef_gg = { 1, 0 },
	.coef_bg = { 0, 0},
	.coef_rb = { 0, 0},
	.coef_gb = { 0, 0},
	.coef_bb = { 1, 0},
#endif
#if 1
	.coef_rr = { 2, 0 },
	.coef_gr = { 1, 0 },
	.coef_br = { 1, 0 },
	.coef_rg = { 1, 0 },
	.coef_gg = { 2, 0 },
	.coef_bg = { 1, 0},
	.coef_rb = { 1, 0},
	.coef_gb = { 1, 0},
	.coef_bb = { 2, 0},
#endif
	.out_ofst_r = 0,
	.out_ofst_g = 0,
	.out_ofst_b = 0
};


/***********************************************************************
 * Gamma config params
 ***********************************************************************/
static char en_gamma;
/* 0 - gamma ram, 1 - gamma rom */
static char gama_rom = 0;


/* Gamma table R/G/B */
#if 1
static struct ipipe_gamma_entry gamma_table[MAX_SIZE_GAMMA];
#define GAMMA_TABLE_FILE "Gamma_Table.txt"
#else
static struct ipipe_gamma_entry gamma_table[MAX_SIZE_GAMMA] = {
 {0,    9}, {9,    9}, {18,    9}, {27,    9}, {36,   9}, {45,   9}, {54,    9}, {63,    9},
 {72,   9}, {81,   8}, {87,    8}, {95,    8}, {103,  8}, {110,  7}, {118,   7}, {125,   7},
 {131,  7}, {138,  6}, {144,   6}, {150,   6}, {156,  6}, {162,  6}, {168,   5}, {173,   5},
 {178,  5}, {173,  5}, {178,   5}, {184,   5}, {189,  5}, {194,  5}, {199,   5}, {204,   5},
 {208,  5}, {213,  5}, {218,   4}, {222,   4}, {226,  4}, {231,  4}, {235,   4}, {239,   4},
 {243,  4}, {248,  4}, {252,   4}, {256,   4}, {259,  4}, {263,  4}, {267,   4}, {271,   4},
 {275,  4}, {278,  4}, {282,   4}, {286,   4}, {289,  4}, {293,  3}, {296,   3}, {300,   3},
 {303,  3}, {307,  3}, {310,   3}, {313,   3}, {317,  3}, {320,  3}, {323,   3}, {326,   3},
 {329,  3}, {333,  3}, {336,   3}, {339,   3}, {342,  3}, {345,  3}, {348,   3}, {351,   3},
 {354,  3}, {357,  3}, {360,   3}, {363,   3}, {365,  3}, {368,  3}, {371,   3}, {374,   3},
 {377,  3}, {380,  3}, {382,   3}, {385,   3}, {388,  3}, {390,  3}, {393,   3}, {396,   3},
 {398,  3}, {401,  3}, {404,   3}, {406,   3}, {409,  3}, {411,  3}, {414,   3}, {417,   3},
 {419,  3}, {422,  2}, {424,   2}, {427,   2}, {429,  2}, {431,  2}, {434,   2}, {436,   2},
 {439,  2}, {441,  2}, {444,   2}, {446,   2}, {448,  2}, {451,  2}, {453,   2}, {455,   2},
 {458,  2}, {460,  2}, {462,   2}, {464,   2}, {467,  2}, {469,  2}, {471,   2}, {473,   2},
 {476,  2}, {478,  2}, {480,   2}, {482,   2}, {485,  2}, {487,  2}, {489,   2}, {491,   2},
 {493,  2}, {495,  2}, {497,   2}, {500,   2}, {502,  2}, {504,  2}, {506,   2}, {508,   2},
 {510,  2}, {512,  2}, {514,   2}, {516,   2}, {518,  2}, {520,  2}, {522,   2}, {524,   2},
 {526,  2}, {528,  2}, {530,   2}, {532,   2}, {534,  2}, {536,  2}, {538,   2}, {540,   2},
 {542,  2}, {544,  2}, {546,   2}, {548,   2}, {550,  2}, {552,  2}, {554,   2}, {556,   2},
 {558,  2}, {559,  2}, {561,   2}, {563,   2}, {565,  2}, {567,  2}, {569,   2}, {571,   2},
 {573,  2}, {574,  2}, {576,   2}, {578,   2}, {580,  2}, {582,  2}, {583,   2}, {585,   2},
 {587,  2}, {589,  2}, {591,   2}, {592,   2}, {594,  2}, {596,  2}, {598,   2}, {600,   2},
 {601,  2}, {603,  2}, {605,   2}, {607,   2}, {608,  2}, {610,  2}, {612,   2}, {613,   2},
 {615,  2}, {617,  2}, {619,   2}, {620,   2}, {622,  2}, {624,  2}, {625,   2}, {627,   2},
 {629,  2}, {630,  2}, {632,   2}, {634,   2}, {635,  2}, {637,  2}, {639,   2}, {640,   2},
 {642,  2}, {644,  2}, {645,   2}, {647,   2}, {649,  2}, {650,  2}, {652,   2}, {653,   2},
 {655,  2}, {657,  2}, {658,   2}, {660,   2}, {661,  2}, {663,  2}, {665,   2}, {666,   2},
 {668,  2}, {669,  2}, {671,   2}, {672,   2}, {674,  2}, {676,  2}, {677,   2}, {679,   2},
 {680,  2}, {682,  2}, {683,   2}, {685,   2}, {686,  2}, {688,  2}, {689,   2}, {691,   2},
 {692,  2}, {694,  2}, {695,   2}, {697,   2}, {698,  2}, {700,  1}, {701,   1}, {703,   1},
 {704,  1}, {706,  1}, {707,   1}, {709,   1}, {710,  1}, {712,  1}, {713,   1}, {715,   1},
 {716,  1}, {718,  1}, {719,   1}, {721,   1}, {722,  1}, {724,  1}, {725,   1}, {726,   1},
 {728,  1}, {729,  1}, {731,   1}, {732,   1}, {734,  1}, {735,  1}, {736,   1}, {738,   1},
 {739,  1}, {741,  1}, {742,   1}, {743,   1}, {745,  1}, {746,  1}, {748,   1}, {749,   1},
 {750,  1}, {752,  1}, {753,   1}, {755,   1}, {756,  1}, {757,  1}, {759,   1}, {760,   1},
 {762,  1}, {763,  1}, {764,   1}, {766,   1}, {767,  1}, {768,  1}, {770,   1}, {771,   1},
 {772,  1}, {774,  1}, {775,   1}, {776,   1}, {778,  1}, {779,  1}, {780,   1}, {782,   1},
 {783,  1}, {784,  1}, {786,   1}, {787,   1}, {788,  1}, {790,  1}, {791,   1}, {792,   1},
 {794,  1}, {795,  1}, {796,   1}, {798,   1}, {799,  1}, {800,  1}, {802,   1}, {803,   1},
 {804,  1}, {805,  1}, {807,   1}, {809,   1}, {811,  1}, {812,  1}, {813,   1}, {814,   1},
 {816,  1}, {817,  1}, {818,   1}, {820,   1}, {821,  1}, {822,  1}, {823,   1}, {825,   1},
 {826,  1}, {827,  1}, {828,   1}, {830,   1}, {831,  1}, {832,  1}, {833,   1}, {835,   1},
 {836,  1}, {837,  1}, {838,   1}, {840,   1}, {841,  1}, {842,  1}, {843,   1}, {844,   1},
 {846,  1}, {847,  1}, {848,   1}, {849,   1}, {851,  1}, {852,  1}, {853,   1}, {854,   1},
 {855,  1}, {857,  1}, {858,   1}, {859,   1}, {860,  1}, {861,  1}, {863,   1}, {864,   1},
 {865,  1}, {866,  1}, {867,   1}, {869,   1}, {870,  1}, {871,  1}, {872,   1}, {873,   1},
 {875,  1}, {876,  1}, {877,   1}, {878,   1}, {879,  1}, {881,  1}, {882,   1}, {883,   1},
 {884,  1}, {885,  1}, {886,   1}, {888,   1}, {889,  1}, {890,  1}, {891,   1}, {892,   1},
 {893,  1}, {894,  1}, {896,   1}, {897,   1}, {898,  1}, {899,  1}, {900,   1}, {901,   1},
 {903,  1}, {904,  1}, {905,   1}, {906,   1}, {907,  1}, {908,  1}, {909,   1}, {910,   1},
 {912,  1}, {913,  1}, {914,   1}, {915,   1}, {916,  1}, {917,  1}, {918,   1}, {920,   1},
 {921,  1}, {922,  1}, {923,   1}, {924,   1}, {925,  1}, {926,  1}, {927,   1}, {928,   1},
 {930,  1}, {931,  1}, {932,   1}, {933,   1}, {934,  1}, {935,  1}, {936,   1}, {937,   1},
 {938,  1}, {939,  1}, {941,   1}, {942,   1}, {943,  1}, {944,  1}, {945,   1}, {946,   1},
 {947,  1}, {948,  1}, {949,   1}, {950,   1}, {951,  1}, {952,  1}, {954,   1}, {955,   1},
 {956,  1}, {957,  1}, {958,   1}, {959,   1}, {960,  1}, {961,  1}, {962,   1}, {963,   1},
 {964,  1}, {965,  1}, {966,   1}, {967,   1}, {969,  1}, {970,  1}, {971,   1}, {972,   1},
 {973,  1}, {974,  1}, {975,   1}, {976,   1}, {977,  1}, {978,  1}, {979,   1}, {980,   1},
 {981,  1}, {982,  1}, {983,   1}, {984,   1}, {985,  1}, {986,  1}, {987,   1}, {988,   1},
 {989,  1}, {990,  1}, {992,   1}, {993,   1}, {994,  1}, {995,  1}, {996,   1}, {997,   1},
 {998,  1}, {999,  1}, {1000,  1}, {1001,  1}, {1002, 1}, {1003, 1}, {1004,  1}, {1005,  1},
 {1006, 1}, {1007, 1}, {1008,  1}, {1009,  1}, {1010, 1}, {1011, 1}, {1012,  1}, {1013,  1},
 {1014, 1}, {1015, 1}, {1016,  1}, {1017,  1}, {1018, 1}, {1019, 1}, {1020,  1}, {1021,  1},
};
#endif

static struct prev_gamma gamma_params = {
	.bypass_r = 0,
	.bypass_b = 0,
	.bypass_g = 0,
	.tbl_sel = IPIPE_GAMMA_TBL_ROM,
};
/***********************************************************************
 * 3D LUT config params
 ***********************************************************************/
#define RED 	0
#define GREEN	1
#define BLUE	2

#define TABLE_3D_R_FILE "table_3D_R.txt"
#define TABLE_3D_G_FILE "table_3D_G.txt"
#define TABLE_3D_B_FILE "table_3D_B.txt"
static char en_3d_lut;
static struct ipipe_3d_lut_entry d3_lut_table[MAX_SIZE_3D_LUT];
static struct prev_3d_lut d3_lut_params = {
	.en = 1,
	.table = d3_lut_table
};

/***********************************************************************
 * RGB2YUV config params
 ***********************************************************************/
static char en_rgb2yuv;
static struct prev_rgb2yuv rgb2yuv_params = {
	// S12Q8
	.coef_ry = { 0, 77},
	//.coef_ry = { 1, 250},
	.coef_gy = { 0, 150},
	//.coef_gy = { 1, 150},
	.coef_by = { 0, 29},
	.coef_rcb = { ((-43 & 0xF00) >> 8), (-43 & 0xFF)},
	.coef_gcb = { ((-85 & 0xF00) >> 8), (-85 & 0xFF)},
	.coef_bcb = { 0, 128},
	.coef_rcr = { 0, 128},
	.coef_gcr = { ((-107 & 0xF00) >> 8), (-107 & 0xFF)},
	.coef_bcr = { ((-21 & 0xF00) >> 8), (-21 & 0xFF)},
	// S11
	.out_ofst_y = 0,
	.out_ofst_cb = 128,
	.out_ofst_cr = 128	
};
/***********************************************************************
 * GBCE config params
 ***********************************************************************/
static char en_gbce;
unsigned short gbce_table[MAX_SIZE_GBCE_LUT];
static struct prev_gbce gbce_params = {
	.en = 1,
	.type = IPIPE_GBCE_Y_VAL_TBL,
	//.type = IPIPE_GBCE_GAIN_TBL,
};
#define GBCE_TABLE_FILE "GBCETable.txt"

/***********************************************************************
 * YUV 422 conversion config params
 ***********************************************************************/
static char en_yuv422_conv;
static struct prev_yuv422_conv yuv422_params = {
	.en_chrom_lpf = 1,
	.chrom_pos = IPIPE_YUV422_CHR_POS_COSITE
	//.chrom_pos = IPIPE_YUV422_CHR_POS_CENTRE 
};

/***********************************************************************
 * Luminance adjustment config params
 ***********************************************************************/
static char en_lum_adj;
static struct prev_lum_adj lum_adj_params = {
	.brightness = 55,
	.contrast = 16
};

/***********************************************************************
 * Edge Enhancement config params
 ***********************************************************************/
static char en_yee;
static short yee_table[MAX_SIZE_YEE_LUT];
static struct prev_yee yee_params = {
	.en = 1,
	//.en_halo_red = 1,
	.en_halo_red = 0,
	//.merge_meth = IPIPE_YEE_ABS_MAX,
	.merge_meth = IPIPE_YEE_EE_ES,
	//.hpf_shft = 5,
	.hpf_shft = 10,
	// S10
	.hpf_coef_00 = 84,
	.hpf_coef_01 = (-8 & 0x3FF),
	.hpf_coef_02 = (-4 & 0x3FF),
	.hpf_coef_10 = (-8 & 0x3FF),
	.hpf_coef_11 = (-4 & 0x3FF),
	.hpf_coef_12 = (-2 & 0x3FF),
	.hpf_coef_20 = (-4 & 0x3FF),
	.hpf_coef_21 = (-2 & 0x3FF),
	.hpf_coef_22 = (-1 & 0x3FF),
	//.yee_thr = 12,
	.yee_thr = 20,
	.es_gain = 128,
	.es_thr1 = 768,
	.es_thr2 = 32,
	.es_gain_grad = 32,
	.es_ofst_grad = 0 
};
#define YEE_TABLE_FILE "EE_Table.txt"

/***********************************************************************
 * CAR config params
 ***********************************************************************/
static char en_car;
static struct prev_car car_params = {
	.en = 1,
	//.meth = IPIPE_CAR_CHR_GAIN_CTRL,
	//.meth = IPIPE_CAR_MED_FLTR,
	.meth = IPIPE_CAR_DYN_SWITCH,
	.gain1 = {255, 5, 128},
	.gain2 = {255, 12, 128},
	.hpf = IPIPE_CAR_HPF_Y,
	.hpf_thr = 32,
	.hpf_shft = 0,
	.sw0 = 255,
	.sw1 = 192	
};
/***********************************************************************
 * CGS config params
 ***********************************************************************/
static char en_cgs;
static struct prev_cgs cgs_params = {
	.en = 1,
	.h_thr = 106,
	.h_slope = 100,
	.h_shft = 0,
	.h_min = 50
};

/* flag = 1, enable a-alaw decompression, 2 - enable dpcm decompression */
static int format_flag;

static int second_out_en;
int second_out_width = 640;
int second_out_height = 480;
int second_out_format = 0;


/* flags for enabling vertical and horizontal flip */
static int out1_horz_flip_en;
static int out1_vert_flip_en;
static int out2_horz_flip_en;
static int out2_vert_flip_en;

int parse_3d_entries(int color, FILE *fp) 
{
	int i, val;
	for (i = 0; i < MAX_SIZE_3D_LUT; i++) {
		if (color == RED) {
			fscanf(fp, "%d", &val);
			d3_lut_table[i].r = val;
			//printf("%d,", val);
			if (d3_lut_table[i].r > 1023) {
				printf("Invalid entry\n");
				return -1;
			}
		}
		else if (color == GREEN) {
			fscanf(fp, "%d", &val);
			d3_lut_table[i].g = val;
			//printf("%d,", val);
			if (d3_lut_table[i].g > 1023) {
				printf("Invalid entry\n");
				return -1;
			}
		}
		else {
			fscanf(fp, "%d", &val);
			d3_lut_table[i].b = val;
			//printf("%d,", val);
			if (d3_lut_table[i].b > 1023) {
				printf("Invalid entry\n");
				return -1;
			}
		}
	}
	if (i != MAX_SIZE_3D_LUT) {
		printf("Table doesn't have enough entries\n");
		return -1;
	}
	printf("\n");
	return 0;
}

int parse_3dLut_tables(void)
{
	int ret = -1;
	FILE *fp1, *fp2, *fp3;

	fp1 = fopen(TABLE_3D_R_FILE, "r");
	if (fp1 == NULL) {
		printf("Error in opening file %s\n", TABLE_3D_R_FILE);
		goto out;
	}
	fp2 = fopen(TABLE_3D_G_FILE, "r");
	if (fp2 == NULL) {
		printf("Error in opening file %s\n", TABLE_3D_G_FILE);
		goto cleanup_file1;
	}
	fp3 = fopen(TABLE_3D_B_FILE, "r");
	if (fp3 == NULL) {
		printf("Error in opening file %s\n", TABLE_3D_B_FILE);
		goto cleanup_file2;
	}
	ret = 0;
	printf("Parsing RED 3D LUT entries\n");
	ret |= parse_3d_entries(RED, fp1);
	printf("Parsing GREEN 3D LUT entries\n");
	ret |= parse_3d_entries(GREEN, fp2);
	printf("Parsing BLUE 3D LUT entries\n");
	ret |= parse_3d_entries(BLUE, fp3);

	fclose(fp3);
cleanup_file2:
	fclose(fp2);
cleanup_file1:
	fclose(fp1);
out:
	return ret;
}

int parse_gbce_table(void)
{
	int ret = -1, val, i;
	FILE *fp;

	fp = fopen(GBCE_TABLE_FILE, "r");
	if (fp == NULL) {
		printf("Error in opening file %s\n", GBCE_TABLE_FILE);
		goto out;
	}

	for (i = 0; i < MAX_SIZE_GBCE_LUT; i++) {
		fscanf(fp, "%d", &val);
		//printf("%d,", val);
		gbce_table[i] = val;
	}
	//printf("\n");
	if (i != MAX_SIZE_GBCE_LUT)
		goto clean_file;	
	ret = 0;
clean_file:
	fclose(fp);
out:
	return ret;
}

int parse_gamma_table(void)
{
	int ret = -1, i;
	FILE *fp;
	int offset, slope;

	fp = fopen(GAMMA_TABLE_FILE, "r");
	if (fp == NULL) {
		printf("Error in opening file %s\n", GAMMA_TABLE_FILE);
		goto out;
	}

	for (i = 0; i < MAX_SIZE_GAMMA; i++) {
		fscanf(fp, "%d\t%d", &offset, &slope);
		//printf("%d\t%d\n", offset, slope);
		gamma_table[i].slope = slope;
		gamma_table[i].offset = offset;
	}
	printf("\n");
	if (i == MAX_SIZE_GAMMA) {
		printf("Got 512 entries\n");		
		gamma_params.tbl_size = IPIPE_GAMMA_TBL_SZ_512;
	} else if (i == 256) {
		printf("Got 256 entries\n");		
		gamma_params.tbl_size = IPIPE_GAMMA_TBL_SZ_256;
	} else if (i == 128) {
		printf("Got 128 entries\n");		
		gamma_params.tbl_size = IPIPE_GAMMA_TBL_SZ_128;
	} else if (i == 64) {
		printf("Got 64 entries\n");		
		gamma_params.tbl_size = IPIPE_GAMMA_TBL_SZ_64;
	} else {
		printf("Not valid file. Need"
			" 512 or 256 or 128 or 64 entries of slope and offset\n");
		goto clean_file;	
	}
	ret = 0;
clean_file:
	fclose(fp);
out:
	return ret;
}

int parse_yee_table(void)
{
	int ret = -1, val, i;
	FILE *fp;

	fp = fopen(YEE_TABLE_FILE, "r");
	if (fp == NULL) {
		printf("Error in opening file %s\n", YEE_TABLE_FILE);
		goto out;
	}

	for (i = 0; i < MAX_SIZE_YEE_LUT; i++) {
		fscanf(fp, "%d", &val);
		printf("%d,", val);
		yee_table[i] = val & 0x1FF;
	}
	printf("\n");
	if (i != MAX_SIZE_YEE_LUT)
		goto clean_file;	
	ret = 0;
clean_file:
	fclose(fp);
out:
	return ret;
}

int main(int argc, char *argp[])
{
	int mode = O_RDWR,c,ret,index;
	int preview_fd, resizer_fd, dev_idx;
	unsigned long oper_mode, user_mode;
	struct prev_channel_config prev_chan_config;
	struct prev_single_shot_config prev_ss_config; // single shot mode configuration
	struct rsz_channel_config rsz_chan_config; // resizer channel config
	struct rsz_single_shot_config rsz_ss_config; // single shot mode configuration
	struct imp_reqbufs req_buf;
	struct imp_buffer buf_in[APP_IN_BUFS];
	struct imp_buffer buf_out1[APP_IN_BUFS];
	struct imp_buffer buf_out2[APP_IN_BUFS];
	struct imp_convert convert;
	int i,j, k;
	char in_file[100], out_file[100], second_out_file[100], answer[20];
	FILE *inp_f, *outp1_f, *outp2_f;
	int width = OUT_WIDTH, height = OUT_HEIGHT, size, expected_size, output1_size, output2_size;
	int out_width, out_height;
	char *input_buffer, *output_buffer1, *output_buffer2;
	unsigned long level;
	short byte=0;
	char *src, *dest;
	int resize = 0, out_format = 0;
	struct prev_cap cap;
	struct prev_module_param mod_params;
	
	printf("input file name :");
	scanf("%s", in_file);
	printf("output file name :");
	scanf("%s", out_file);
	printf("input file format: 0 - Bayer - 16, 1 - Bayer A-law, 2 - Bayer - DPCM :");
	scanf("%d", &format_flag);
	printf("input width :");
	scanf("%d", &width);
	printf("input height:");
	scanf("%d", &height);
	printf("resize (y/n) :");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1)) {
		printf("Selected resize\n");
		resize = 1;
		printf("output width :");
		scanf("%d", &out_width);
		printf("output height:");
		scanf("%d", &out_height);
		printf("output format 0 - UYVY, 1 - YUV420SP:");
		scanf("%d", &out_format);
		printf("flip image horizontally (y/n) :");
		scanf("%s", answer);
		if (!strncmp(answer, "y", 1)) {
			printf("Enabling horizontal flip\n");
			out1_horz_flip_en = 1;
		}
		printf("flip image vertically (y/n) :");
		scanf("%s", answer);
		if (!strncmp(answer, "y", 1)) {
			printf("Enabling vertical flip\n");
			out1_vert_flip_en = 1;
		}
	} else {
		out_width = width;
		out_height = height;
		resize = 0;
	}

	if (!out_format) {
		out_width += 15;
		out_width &= (~15);
		output1_size = out_width * out_height * BYTESPERLINE;
	} else {
		out_width += 31;
		out_width &= (~31);
		output1_size = out_width * out_height * 1.5;
	}
	printf("output1_size = %d\n", output1_size);

	if (resize) {
		printf("Enable second output (y/n) :");
		scanf("%s", answer);
		if (!strncmp(answer, "y", 1)) {
			second_out_en = 1;
			printf("second output file name :");
			scanf("%s", second_out_file);
			printf("second output width :");
			scanf("%d", &second_out_width);
			printf("second output height :");
			scanf("%d", &second_out_height);
			printf("secondf output format 0 - UYVY, 1 - YUV420SP :");
			scanf("%d", &second_out_format);
			printf("flip image horizontally (y/n) :");
			scanf("%s", answer);
			if (!strncmp(answer, "y", 1)) {
				printf("Enabling horizontal flip for second output\n");
				out2_horz_flip_en = 1;
			}
			printf("flip image vertically (y/n) :");
			scanf("%s", answer);
			if (!strncmp(answer, "y", 1)) {
				printf("Enabling vertical flip for second output\n");
				out2_vert_flip_en = 1;
			}
		}
	}
	
	printf("Add pixel defects (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		add_pix_defects = 1;

	printf("correct pixel defects (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1)) {
		correct_pix_defects = 1;
		printf("LUT or OTF correction (0 - LUT, 1 - OTF):");
		scanf("%d", &lut_or_otf);
		if (lut_or_otf) {
			printf("OTF correction method, 0 - Min-Max, 1 - Min-Max2:");
			scanf("%d", &otf_min_max);
			if (otf_min_max) {
				printf("OTF 2.0 or 3.0 (0 - 2.0, 1 - 3.0):");
				scanf("%d", &otf_20_30);
			}
		}
	}

	printf("Apply Noise filter 1 (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_nf1 = 1;
	
	printf("Apply Noise filter 2 (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_nf2 = 1;

	printf("Apply Green Imbalance Correction (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_gic = 1;
	printf("Apply White Balance (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_wb = 1;

	printf("Apply CFA Algs(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_cfa = 1;

	printf("Apply RGB2RGB - 1(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_rgb2rgb_1 = 1;

	printf("Apply RGB2RGB - 2(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_rgb2rgb_2 = 1;

	printf("Apply GAMMA(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_gamma = 1;

	printf("Apply 3D LUT(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_3d_lut = 1;

	printf("Apply RGB2YUV conversion params(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_rgb2yuv = 1;

	printf("Apply GBCE params(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_gbce = 1;

	printf("Apply yuv422 conv params(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_yuv422_conv = 1;

	printf("Apply Luminance Adj params(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_lum_adj = 1;

	printf("Apply Edge Enhancment params(y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_yee = 1;

	printf("Apply Chroma Artifact Reduction (CAR) (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_car = 1;

	printf("Apply Chroma Gain Suppression (CGS) (y/n):");
	scanf("%s", answer);
	if (!strncmp(answer, "y", 1))
		en_cgs = 1;

	if (out_format != 0 && out_format != 1) {
		printf("Invalid output1 format\n");
		exit(1);
	}

	if (second_out_en && second_out_format != 0 && second_out_format != 1) {
		printf("Invalid output2 format\n");
		exit(1);
	}

	if (second_out_en) {
		if (!second_out_format) {
			second_out_width += 15;
			second_out_width &= (~15);
			output2_size = second_out_width * second_out_height * BYTESPERLINE;
		} else {
			second_out_width += 31;
			second_out_width &= (~31);
			output2_size = second_out_width * second_out_height * 1.5;
		}
		printf("output2_size = %d\n", output2_size);
	}

	if (resize)
		printf("doing preview & resize on in_file = %s"
			" and writing out to out_file = %s\n",in_file,out_file);
	else
		printf("doing preview on in_file = %s"
			" and writing out to out_file = %s\n",in_file,out_file);

	if (second_out_en)
		printf("second output file = %s\n", second_out_file);

	oper_mode = IMP_MODE_SINGLE_SHOT;

	printf("starting\n");
	inp_f = fopen(in_file, "rb");
	if (inp_f == NULL) {
		perror("Error in opening input file \n");
		exit(1);
	}
	outp1_f = fopen(out_file, "wb");
	if (outp1_f == NULL) {
		perror("Error in opening output file \n");
		goto inp_file_clean;
	}

	if (en_3d_lut) {
		printf("Parsing 3D LUT tables: %s, %s & %s\n",
			TABLE_3D_G_FILE,
			TABLE_3D_B_FILE,
			TABLE_3D_R_FILE);
		if (parse_3dLut_tables() < 0) {
			perror("Error in parsing 3D LUT table files \n");
			goto inp_file_clean;
		}
	}

	if (en_gbce) {
		printf("Parsing GBCE table: %s\n", GBCE_TABLE_FILE);
		if (parse_gbce_table() < 0) {
			perror("Error in parsing GBCE table file \n");
			goto inp_file_clean;
		}
	}

	if (en_gamma) {
		printf("Parsing Gamma table: %s\n", GAMMA_TABLE_FILE);
		if (parse_gamma_table() < 0) {
			perror("Error in parsing Gamma table file \n");
			goto inp_file_clean;
		}
	}
	if (en_yee) {
		printf("Parsing Edge Enhancement table: %s\n", YEE_TABLE_FILE);
		if (parse_yee_table() < 0) {
			perror("Error in parsing Edge Enhancement table file \n");
			goto inp_file_clean;
		}
	}

	if (second_out_en) {
		outp2_f = fopen(second_out_file, "wb");
		if (outp2_f == NULL) {
			perror("Error in opening output file \n");
			goto file1_clean;
		}
	}

	if (format_flag == 1) {
		expected_size  =  WIDTH * HEIGHT;
		printf("Enable a_alaw decompression, 1 byte per pixel \n");
		size = fread(in_buf,1, expected_size , inp_f);
	} else if (format_flag == 2) {
		expected_size  =  WIDTH * HEIGHT;
		printf("Enable dpcm decompression, 1 byte per pixel\n");
		size = fread(in_buf,1, expected_size, inp_f);
	}
	else {
		printf("No decompression, 2 bytes per pixel\n");
		expected_size  =  WIDTH * HEIGHT * BYTESPERLINE;
		size = fread(in_buf,1, expected_size, inp_f);
	}


	if (add_pix_defects) {
		printf("Adding pixel defects\n");
		for (i = 0; i < NUM_DPS; i++) {
			if (pix_defect_tbl[i].x_pos >= width ||
				pix_defect_tbl[i].y_pos >= height) {
				printf("Skipping pix defect data\n");
				continue;
			}
			
			if (!format_flag) {
				j =  (pix_defect_tbl[i].x_pos * 2) + 
					(pix_defect_tbl[i].y_pos * width * 2); 
			}
			else {
				j =  (pix_defect_tbl[i].x_pos + 
					pix_defect_tbl[i].y_pos * width); 
			}

			in_buf[j] = DEFECT_PIX_VAL & 0xFF;
			in_buf[j + 1] = ((DEFECT_PIX_VAL & 0xFF00) >> 8);
			printf("added defects at = %d", j);
		}
	}
	if (resize) {
		printf("Configuring resizer in the chain mode\n");
		printf("Opening resizer device, %s\n",dev_name_rsz);
		resizer_fd = open(dev_name_rsz, mode);
		if(resizer_fd <= 0) {
			perror("Cannot open resizer device\n");
			goto file2_clean;
		}

		if (ioctl(resizer_fd, RSZ_S_OPER_MODE, &oper_mode) < 0) {
			perror("Can't get operation mode\n");
			goto resize_clean;
		}

		if (ioctl(resizer_fd,RSZ_G_OPER_MODE, &user_mode) < 0) {
			perror("Can't get operation mode\n");
			goto resize_clean;
		}
		if (oper_mode == user_mode)
			printf("RESIZER: Operating mode changed successfully to Single Shot");
		else {
			printf("RESIZER: Couldn't change operation mode to Single Shot");
			goto resize_clean;
		}
		printf("Setting default configuration in Resizer\n");
		bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
		rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
		rsz_chan_config.chain = 1;
		rsz_chan_config.len = 0;
		rsz_chan_config.config = NULL; /* to set defaults in driver */
		if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
			perror("Error in setting default configuration for single shot mode\n");
			goto resize_clean;
		}

		printf("default configuration setting in Resizer successfull\n");
		bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
		rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
		rsz_chan_config.chain = 1;
		rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
		rsz_chan_config.config = &rsz_ss_config;

		if (ioctl(resizer_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
			perror("Error in getting resizer channel configuration from driver\n");
			goto resize_clean;
		}
		printf("default values at driver\n");
		printf("rsz_ss_config.output1.enable = %d\n", rsz_ss_config.output1.enable);
		printf("rsz_ss_config.output1.width = %d, \n", rsz_ss_config.output1.width);
		printf("rsz_ss_config.output1.height = %d\n", rsz_ss_config.output1.height);
		printf("rsz_ss_config.output2.enable = %d\n", rsz_ss_config.output1.enable);
		printf("rsz_ss_config.output2.width = %d\n", rsz_ss_config.output1.width);
		printf("rsz_ss_config.output2.height = %d\n", rsz_ss_config.output1.height);

		// in the chain mode only output configurations are valid
		// input params are set at the previewer
		printf("Changing output width to %d\n", width);
		printf("Changing output height to %d\n", height);

		if (!out_format)
			rsz_ss_config.output1.pix_fmt = IPIPE_UYVY;
		else
			rsz_ss_config.output1.pix_fmt = IPIPE_YUV420SP;
		rsz_ss_config.output1.enable = 1;
		rsz_ss_config.output1.width = out_width;
		rsz_ss_config.output1.height = out_height;
		rsz_ss_config.output1.h_flip = out1_horz_flip_en;
		rsz_ss_config.output1.v_flip = out1_vert_flip_en;
		if (second_out_en) {
			rsz_ss_config.output2.enable = 1;
			rsz_ss_config.output2.width = second_out_width;
			rsz_ss_config.output2.height = second_out_height;
			if (second_out_format)
				rsz_ss_config.output2.pix_fmt = IPIPE_YUV420SP;
			else
				rsz_ss_config.output2.pix_fmt = IPIPE_UYVY;
			rsz_ss_config.output2.h_flip = out2_horz_flip_en;
			rsz_ss_config.output2.v_flip = out2_vert_flip_en;
		}
		rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
		rsz_chan_config.chain = 1;
		rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
		if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
			perror("Error in setting default configuration for single shot mode\n");
			goto resize_clean;
		}
	}

	preview_fd = open(dev_name_prev, mode);
	if(preview_fd <= 0) {
		printf("Cannot open previewer device\n");
		goto resize_clean;
	}

	if (ioctl(preview_fd, PREV_S_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		goto preview_clean;
	}

	if (ioctl(preview_fd, PREV_G_OPER_MODE, &user_mode) < 0) {
		perror("Can't get operation mode\n");
		goto preview_clean;
	}

	if (oper_mode == user_mode) 
		printf("Operating mode changed successfully to single shot in previewer");
	else {
		printf("failed to set mode to single shot in previewer\n");
		goto preview_clean;
	}

	printf("Setting default configuration in previewer\n");
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = 0;
	prev_chan_config.config = NULL; /* to set defaults in driver */
	if (ioctl(preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0) {
		perror("Error in setting default configuration\n");
		goto preview_clean;
	}

	printf("default configuration setting in previewer successfull\n");
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = sizeof(struct prev_single_shot_config);
	prev_chan_config.config = &prev_ss_config;

	if (ioctl(preview_fd, PREV_G_CONFIG, &prev_chan_config) < 0) {
		perror("Error in getting configuration from driver\n");
		goto preview_clean;
	}
	
	prev_chan_config.oper_mode = oper_mode;
	prev_chan_config.len = sizeof(struct prev_single_shot_config);
	prev_chan_config.config = &prev_ss_config;
	prev_ss_config.input.image_width = width;
	prev_ss_config.input.image_height = height;
	prev_ss_config.input.ppln= width * 1.5;
	prev_ss_config.input.lpfr = height + 10;
	if (format_flag == 0) {
		prev_ss_config.input.pix_fmt = IPIPE_BAYER;
		prev_ss_config.input.data_shift = IPIPEIF_5_1_BITS11_0;
	}
	else if (format_flag == 1)
		prev_ss_config.input.pix_fmt = IPIPE_BAYER_8BIT_PACK_ALAW;
	else if (format_flag == 2)
		prev_ss_config.input.pix_fmt = IPIPE_BAYER_8BIT_PACK_DPCM;
	
	if (ioctl(preview_fd, PREV_S_CONFIG, &prev_chan_config) < 0) {
		perror("Error in setting default configuration\n");
		goto preview_clean;
	}
	
	cap.index = 0;
	while (ioctl(preview_fd, PREV_ENUM_CAP, &cap) == 0) {
		/* for each of the tuning module set defaults */
		strcpy(mod_params.version, cap.version);
		/* first setup defaults */
		mod_params.module_id = cap.module_id;
		mod_params.param = NULL;
		if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
			perror("Error in setting default PREV_S_PARAM for dpc\n");
			goto preview_clean;
		}
		printf("Default values set for %s\n", cap.module_name);

		switch (cap.module_id) {
			case PREV_LUTDPC:
			{
				mod_params.len = sizeof(struct prev_lutdpc);
				/* enable defect pixel correction */
				if (correct_pix_defects && !lut_or_otf) {
					dpc.en = 1;
					//dpc.repl_white = 1;
					dpc.repl_white = 0;
					for (i = 0; i < NUM_DPS; i++) {
						dpc_table[i].horz_pos = pix_defect_tbl[i].x_pos;
						dpc_table[i].vert_pos = pix_defect_tbl[i].y_pos;
						//dpc_table[i].method = IPIPE_DPC_CL;
						dpc_table[i].method = IPIPE_DPC_REPL_BY_DOT;
					}
					dpc.table = &dpc_table[0];
					dpc.dpc_size = NUM_DPS;
					mod_params.param = &dpc;
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for dpc\n");
						goto preview_clean;
					} else {
						printf("Success in setting dpc params\n");
					}
				}
				break;
			}
			case PREV_OTFDPC:
			{
				if (correct_pix_defects && lut_or_otf) {
					printf("Doing OTF pixel correction\n");
					otfdpc.en = 1;
					mod_params.len = sizeof(struct prev_otfdpc);
					if (!otf_min_max) {
						printf("choosing Min-Max OTF detection method\n");	
						otfdpc.det_method = IPIPE_DPC_OTF_MIN_MAX;
						/* Set the maximum value for Min max detection
						 * threshold
						 */
						otfdpc.alg_cfg.dpc_2_0.corr_thr.r = 0x300;
						otfdpc.alg_cfg.dpc_2_0.corr_thr.gr = 0x300;
						otfdpc.alg_cfg.dpc_2_0.corr_thr.gb = 0x300;
						otfdpc.alg_cfg.dpc_2_0.corr_thr.b = 0x300;
					}
					else {
						printf("choosing Min-Max2 OTF detection method\n");	
						otfdpc.det_method = IPIPE_DPC_OTF_MIN_MAX2;
						if (otf_20_30) {	
							printf("Choosing DPC 3.0 alg\n");
							otfdpc.alg = IPIPE_OTFDPC_3_0;
							otfdpc.alg_cfg.dpc_3_0.act_adj_shf = 1;
							otfdpc.alg_cfg.dpc_3_0.det_thr = 0x100;
							otfdpc.alg_cfg.dpc_3_0.det_slp = 0x20;
							otfdpc.alg_cfg.dpc_3_0.det_thr_min = 0x300;
							otfdpc.alg_cfg.dpc_3_0.det_thr_max = 0x310;
							otfdpc.alg_cfg.dpc_3_0.corr_thr = 0x100;
							otfdpc.alg_cfg.dpc_3_0.corr_slp = 0x20;
							otfdpc.alg_cfg.dpc_3_0.corr_thr_min = 0x300;
							otfdpc.alg_cfg.dpc_3_0.corr_thr_max = 0x310;
						}
						else {
							printf("Choosing DPC 2.0 alg\n");
							otfdpc.alg_cfg.dpc_2_0.corr_thr.r = 0x300;
							otfdpc.alg = IPIPE_OTFDPC_2_0;
							otfdpc.alg_cfg.dpc_2_0.det_thr.r = 0x300;
							otfdpc.alg_cfg.dpc_2_0.det_thr.gr = 0x300;
							otfdpc.alg_cfg.dpc_2_0.det_thr.gb = 0x300;
							otfdpc.alg_cfg.dpc_2_0.det_thr.b = 0x300;
							otfdpc.alg_cfg.dpc_2_0.corr_thr.r = 0x300;
							otfdpc.alg_cfg.dpc_2_0.corr_thr.gr = 0x300;
							otfdpc.alg_cfg.dpc_2_0.corr_thr.gb = 0x300;
							otfdpc.alg_cfg.dpc_2_0.corr_thr.b = 0x300;
						}
					}
					mod_params.param = &otfdpc;
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						goto preview_clean;
					} else {
						printf("Success in setting otfdpc params\n");
					}
				}
				break;
			}

			case PREV_NF1:
			case PREV_NF2:
			{
				mod_params.param = &nf_params;
				mod_params.len = sizeof(struct prev_nf);
				
				if (en_log && (en_nf1 || en_nf2)) {
					printf("nf_params.en = %d\n", nf_params.en);
					printf("nf_params.gr_sample_meth = %d\n", nf_params.gr_sample_meth);
					printf("nf_params.shft_val = %d\n", nf_params.shft_val);
					printf("nf_params.spread_val = %d\n", nf_params.spread_val);
					printf("nf_params.apply_lsc_gain = %d\n", nf_params.apply_lsc_gain);
					printf("nf_params.edge_det_min_thr = %d\n", nf_params.edge_det_min_thr);
					printf("nf_params.edge_det_max_thr = %d\n", nf_params.edge_det_max_thr);
					printf("thr vals:"); 
					for (i = 0; i < IPIPE_NF_STR_TABLE_SIZE; i++) {
						printf("%d,",nf_params.thr[i]);
					}
					printf("\nstr vals:"); 
					for (i = 0; i < IPIPE_NF_STR_TABLE_SIZE; i++) {
						printf("%d,",nf_params.str[i]);
					}
					printf("\n");
				} 
				if (en_nf1 && cap.module_id == PREV_NF1) {
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for NF1\n");
						goto preview_clean;
					} else {
						printf("Success in setting NF1 params\n");
					}
				}
				if (en_nf2 && cap.module_id == PREV_NF2) {
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for NF2\n");
						goto resize_clean;
					} else {
						printf("Success in setting NF2 params\n");
					}
				}
				break;
			}

			case PREV_GIC:
			{
				mod_params.len = sizeof(struct prev_gic);
				mod_params.param = &gic_params;
				if (en_gic) {
					if (en_log) {
						printf("gic_params.en = %d\n", gic_params.en);
						printf("gic_params.gic_alg = %d\n", gic_params.gic_alg);
						printf("gic_params.gain = %d\n", gic_params.gain);
						printf("gic_params.thr_sel = %d\n", gic_params.thr_sel);
						printf("gic_params.thr = %d\n", gic_params.thr);
						printf("gic_params.slope = %d\n", gic_params.slope);
						printf("gic_params.apply_lsc_gain = %d\n", gic_params.apply_lsc_gain);
						printf("gic_params.wt_fn_type = %d\n", gic_params.wt_fn_type);

					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for GIC\n");
						goto resize_clean;
					} else {
						printf("Success in setting GIC params\n");
					}
				}
				break;
			}

			case PREV_WB:
			{
				mod_params.len = sizeof(struct prev_wb);
				mod_params.param = &wb_params;
				if (en_wb) {
					if (en_log) {
					 	printf("wb_params.ofst_r = %d\n", wb_params.ofst_r);
						printf("wb_params.ofst_gr = %d\n", wb_params.ofst_gr);
						printf("wb_params.ofst_gb = %d\n", wb_params.ofst_gb);
						printf("wb_params.ofst_b = %d\n", wb_params.ofst_b);
					 	printf("wb_params.gain_r = {%d:%d}\n",
							wb_params.gain_r.integer,
							wb_params.gain_r.decimal);
					 	printf("wb_params.gain_gr = {%d:%d}\n",
							wb_params.gain_gr.integer,
							wb_params.gain_gr.decimal);
					 	printf("wb_params.gain_gb = {%d:%d}\n",
							wb_params.gain_gb.integer,
							wb_params.gain_gb.decimal);
					 	printf("wb_params.gain_b = {%d:%d}\n",
							wb_params.gain_b.integer,
							wb_params.gain_b.decimal);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for WB\n");
						goto resize_clean;
					} else {
						printf("Success in setting WB params\n");
					}
				}
				break;
			}
			case PREV_CFA:
			{
				mod_params.len = sizeof(struct prev_cfa);
				mod_params.param = &cfa_params;
				if (en_cfa) {
					if (en_log) {
						printf("cfa_params.alg = %d\n", cfa_params.alg);
						printf("cfa_params.hpf_thr_2dir = %d\n",
								cfa_params.hpf_thr_2dir);
						printf("cfa_params.hpf_slp_2dir = %d\n",
								cfa_params.hpf_slp_2dir);
						printf("cfa_params.hp_mix_thr_2dir = %d\n",
								cfa_params.hp_mix_thr_2dir);
						printf("cfa_params.hp_mix_slope_2dir = %d\n",
								cfa_params.hp_mix_slope_2dir);
						printf("cfa_params.dir_thr_2dir = %d\n",
								cfa_params.dir_thr_2dir);
						printf("cfa_params.dir_slope_2dir = %d\n",
								cfa_params.dir_slope_2dir);
						printf("cfa_params.nd_wt_2dir = %d\n",
								cfa_params.nd_wt_2dir);
						printf("cfa_params.hue_fract_daa = %d\n",
								cfa_params.hue_fract_daa);
						printf("cfa_params.edge_thr_daa = %d\n",
								cfa_params.edge_thr_daa);
						printf("cfa_params.thr_min_daa = %d\n",
								cfa_params.thr_min_daa);
						printf("cfa_params.thr_slope_daa = %d\n",
								cfa_params.thr_slope_daa);
						printf("cfa_params.slope_min_daa = %d\n",
								cfa_params.slope_min_daa);
						printf("cfa_params.slope_slope_daa = %d\n",
								cfa_params.slope_slope_daa);
						printf("cfa_params.lp_wt_daa = %d\n",
								cfa_params.lp_wt_daa);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for CFA\n");
						goto resize_clean;
					} else {
						printf("Success in setting CFA params\n");
					}

				}
				break;
			}

			case PREV_RGB2RGB_1:
			{
				mod_params.len = sizeof(struct prev_rgb2rgb);
				mod_params.param = &rgb2rgb_1_params;
				if (en_rgb2rgb_1) {
					if (en_log) {
						printf("rgb2rgb_1_params.coef_rr = {%d, %d}\n",
							rgb2rgb_1_params.coef_rr.integer,
							rgb2rgb_1_params.coef_rr.decimal);
						printf("rgb2rgb_1_params.coef_gr = {%d, %d}\n",
							rgb2rgb_1_params.coef_gr.integer,
							rgb2rgb_1_params.coef_gr.decimal);
						printf("rgb2rgb_1_params.coef_br = {%d, %d}\n",
							rgb2rgb_1_params.coef_br.integer,
							rgb2rgb_1_params.coef_br.decimal);
						printf("rgb2rgb_1_params.coef_rg = {%d, %d}\n",
							rgb2rgb_1_params.coef_rg.integer,
							rgb2rgb_1_params.coef_rg.decimal);
						printf("rgb2rgb_1_params.coef_gg = {%d, %d}\n",
							rgb2rgb_1_params.coef_gg.integer,
							rgb2rgb_1_params.coef_gg.decimal);
						printf("rgb2rgb_1_params.coef_bg = {%d, %d}\n",
							rgb2rgb_1_params.coef_bg.integer,
							rgb2rgb_1_params.coef_bg.decimal);
						printf("rgb2rgb_1_params.coef_rb = {%d, %d}\n",
							rgb2rgb_1_params.coef_rb.integer,
							rgb2rgb_1_params.coef_rb.decimal);
						printf("rgb2rgb_1_params.coef_gb = {%d, %d}\n",
							rgb2rgb_1_params.coef_gb.integer,
							rgb2rgb_1_params.coef_gb.decimal);
						printf("rgb2rgb_1_params.coef_bb = {%d, %d}\n",
							rgb2rgb_1_params.coef_bb.integer,
							rgb2rgb_1_params.coef_bb.decimal);
						printf("rgb2rgb_1_params.out_ofst_r= %d\n",
							rgb2rgb_1_params.out_ofst_r);
						printf("rgb2rgb_1_params.out_ofst_g= %d\n",
							rgb2rgb_1_params.out_ofst_g);
						printf("rgb2rgb_1_params.out_ofst_b= %d\n",
							rgb2rgb_1_params.out_ofst_b);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for RGB2RGB-1\n");
						goto resize_clean;
					} else {
						printf("Success in setting RGB2RGB-1 params\n");
					}

				}
				
				break;
			}
			case PREV_GAMMA:
			{
				mod_params.len = sizeof(struct prev_gamma);
				mod_params.param = &gamma_params;
				if (en_gamma) {
					if (!gama_rom) {
						gamma_params.tbl_sel = IPIPE_GAMMA_TBL_RAM;
						gamma_params.table_r = gamma_table;
						gamma_params.table_g = gamma_table;
						gamma_params.table_b = gamma_table;
					}
						
					if (en_log) {
						if (!gama_rom)
							printf("Selected RAM table for Gamma\n");
						else
							printf("Selected ROM table for Gamma\n");
					
						printf("gamma_params.bypass_r = %d\n",
							gamma_params.bypass_r);
						printf("gamma_params.bypass_g = %d\n",
							gamma_params.bypass_g);
						printf("gamma_params.bypass_b = %d\n",
							gamma_params.bypass_b);
						printf("gamma_params.tbl_size = %d\n",
							gamma_params.tbl_size);
						printf("gamma_params.tbl_sel = %d\n",
							gamma_params.tbl_sel);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for GAMMA\n");
						goto resize_clean;
					} else {
						printf("Success in setting Gamma params\n");
					}

				}
				break;
			}

			case PREV_RGB2RGB_2:
			{
				mod_params.len = sizeof(struct prev_rgb2rgb);
				mod_params.param = &rgb2rgb_1_params;
				if (en_rgb2rgb_2) {
					if (en_log) {
						printf("rgb2rgb_2_params.coef_rr = {%d, %d}\n",
							rgb2rgb_1_params.coef_rr.integer,
							rgb2rgb_1_params.coef_rr.decimal);
						printf("rgb2rgb_2_params.coef_gr = {%d, %d}\n",
							rgb2rgb_1_params.coef_gr.integer,
							rgb2rgb_1_params.coef_gr.decimal);
						printf("rgb2rgb_2_params.coef_br = {%d, %d}\n",
							rgb2rgb_1_params.coef_br.integer,
							rgb2rgb_1_params.coef_br.decimal);
						printf("rgb2rgb_2_params.coef_rg = {%d, %d}\n",
							rgb2rgb_1_params.coef_rg.integer,
							rgb2rgb_1_params.coef_rg.decimal);
						printf("rgb2rgb_2_params.coef_gg = {%d, %d}\n",
							rgb2rgb_1_params.coef_gg.integer,
							rgb2rgb_1_params.coef_gg.decimal);
						printf("rgb2rgb_2_params.coef_bg = {%d, %d}\n",
							rgb2rgb_1_params.coef_bg.integer,
							rgb2rgb_1_params.coef_bg.decimal);
						printf("rgb2rgb_2_params.coef_rb = {%d, %d}\n",
							rgb2rgb_1_params.coef_rb.integer,
							rgb2rgb_1_params.coef_rb.decimal);
						printf("rgb2rgb_2_params.coef_gb = {%d, %d}\n",
							rgb2rgb_1_params.coef_gb.integer,
							rgb2rgb_1_params.coef_gb.decimal);
						printf("rgb2rgb_2_params.coef_bb = {%d, %d}\n",
							rgb2rgb_1_params.coef_bb.integer,
							rgb2rgb_1_params.coef_bb.decimal);
						printf("rgb2rgb_2_params.out_ofst_r= %d\n",
							rgb2rgb_1_params.out_ofst_r);
						printf("rgb2rgb_2_params.out_ofst_g= %d\n",
							rgb2rgb_1_params.out_ofst_g);
						printf("rgb2rgb_2_params.out_ofst_b= %d\n",
							rgb2rgb_1_params.out_ofst_b);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for RGB2RGB-2\n");
						goto resize_clean;
					} else {
						printf("Success in setting RGB2RGB-2 params\n");
					}
				}
				break;
			}	
			case PREV_3D_LUT:
			{
				mod_params.len = sizeof(struct prev_3d_lut);
				mod_params.param = &d3_lut_params;
				if (en_3d_lut) {
					if (en_log)
						printf("Enabled 3D lut \n");
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for 3D-LUT\n");
						goto resize_clean;
					} else
						printf("Success in setting 3D-LUT params\n");
				}

				break;
			}
			case PREV_RGB2YUV:
			{
				mod_params.len = sizeof(struct prev_rgb2yuv);
				mod_params.param = &rgb2yuv_params;
				if (en_rgb2yuv) {
					if (en_log) {
						printf("Enabled RGB2YUV params setting \n");
						printf("rgb2yuv_params.coef_ry = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_ry.integer,
							rgb2yuv_params.coef_ry.decimal);
						printf("rgb2yuv_params.coef_gy = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_gy.integer,
							rgb2yuv_params.coef_gy.decimal);
						printf("rgb2yuv_params.coef_by = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_by.integer,
							rgb2yuv_params.coef_by.decimal);
						printf("rgb2yuv_params.coef_rcb = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_rcb.integer,
							rgb2yuv_params.coef_rcb.decimal);
						printf("rgb2yuv_params.coef_gcb = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_gcb.integer,
							rgb2yuv_params.coef_gcb.decimal);
						printf("rgb2yuv_params.coef_bcb = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_bcb.integer,
							rgb2yuv_params.coef_bcb.decimal);
						printf("rgb2yuv_params.coef_rcr = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_rcr.integer,
							rgb2yuv_params.coef_rcr.decimal);
						printf("rgb2yuv_params.coef_gcr = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_gcr.integer,
							rgb2yuv_params.coef_gcr.decimal);
						printf("rgb2yuv_params.coef_bcr = {0x%x, 0x%x}\n",
							rgb2yuv_params.coef_bcr.integer,
							rgb2yuv_params.coef_bcr.decimal);
						printf("rgb2yuv_params.out_ofst_y = %x\n",
							rgb2yuv_params.out_ofst_y);
						printf("rgb2yuv_params.out_ofst_cb = %x\n",
							rgb2yuv_params.out_ofst_cb);
						printf("rgb2yuv_params.out_ofst_cr = %x\n",
							rgb2yuv_params.out_ofst_cr);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for RGB2YUV\n");
						goto resize_clean;
					} else
						printf("Success in setting RGB2YUV params\n");
				}

				break;
			}
			case PREV_GBCE:
			{
				mod_params.len = sizeof(struct prev_gbce);
				mod_params.param = &gbce_params;
				if (en_gbce) {
					gbce_params.table = gbce_table;
					if (en_log) {
						printf("Enabled GBCE\n");
						printf("gbce_params.type =  %d\n",
							gbce_params.type);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for GBCE\n");
						goto resize_clean;
					} else
						printf("Success in setting GBCE params\n");
				}
				break;
			}
			case PREV_YUV422_CONV:
			{
				mod_params.len = sizeof(struct prev_yuv422_conv);
				mod_params.param = &yuv422_params;
				if (en_yuv422_conv) {
					if (en_log) {
						printf("Enabled YUV422 conversion params\n");
						printf("yuv422_params.en_chrom_lpf =  %d\n",
							yuv422_params.en_chrom_lpf);
						printf("yuv422_params.chrom_pos =  %d\n",
							yuv422_params.chrom_pos);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for YUV422 conv\n");
						goto resize_clean;
					} else
						printf("Success in setting YUV 422 conv params\n");
				}
				break;
			}
			case PREV_LUM_ADJ:
			{
				mod_params.len = sizeof(struct prev_lum_adj);
				mod_params.param = &lum_adj_params;
				if (en_lum_adj) {
					if (en_log) {
						printf("Enabled Lum. Adj. params\n");
						printf("lum_adj_params.brightness =  %d\n",
							lum_adj_params.brightness);
						printf("lum_adj_params.contrast =  %d\n",
							lum_adj_params.contrast);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for Lum. Adj.\n");
						goto resize_clean;
					} else
						printf("Success in setting Lum. Adj. params\n");
				}
				break;
			}
			case PREV_YEE:
			{
				mod_params.len = sizeof(struct prev_yee);
				mod_params.param = &yee_params;
				if (en_yee) {
					yee_params.table = yee_table;
					if (en_log) {
						printf("yee_params.en = %d\n",
							yee_params.en);
						printf("yee_params.en_halo_red = %d\n",
							yee_params.en_halo_red);
						printf("yee_params.merge_meth = %d\n",
							yee_params.merge_meth);
						printf("yee_params.hpf_shft = %d\n",
							yee_params.hpf_shft);
						printf("yee_params.hpf_coef_00 = %d\n",
							yee_params.hpf_coef_00);
						printf("yee_params.hpf_coef_01 = %d\n",
							yee_params.hpf_coef_01);
						printf("yee_params.hpf_coef_02 = %d\n",
							yee_params.hpf_coef_02);
						printf("yee_params.hpf_coef_10 = %d\n",
							yee_params.hpf_coef_10);
						printf("yee_params.hpf_coef_11 = %d\n",
							yee_params.hpf_coef_11);
						printf("yee_params.hpf_coef_12 = %d\n",
							yee_params.hpf_coef_12);
						printf("yee_params.hpf_coef_20 = %d\n",
							yee_params.hpf_coef_20);
						printf("yee_params.hpf_coef_21 = %d\n",
							yee_params.hpf_coef_21);
						printf("yee_params.hpf_coef_22 = %d\n",
							yee_params.hpf_coef_22);
						printf("yee_params.yee_thr = %d\n",
							yee_params.yee_thr);
						printf("yee_params.es_gain = %d\n",
							yee_params.es_gain);
						printf("yee_params.es_thr1 = %d\n",
							yee_params.es_thr1);
						printf("yee_params.es_thr2 = %d\n",
							yee_params.es_thr2);
						printf("yee_params.es_gain_grad= %d\n",
							yee_params.es_gain_grad);
						printf("yee_params.es_ofst_grad = %d\n",
							yee_params.es_ofst_grad);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for EE.\n");
						goto resize_clean;
					} else
						printf("Success in setting EE params\n");

				}
				break;
			}
			case PREV_CAR:
			{
				mod_params.len = sizeof(struct prev_car);
				mod_params.param = &car_params;
				if (en_car) {
					if (en_log) {
						printf("car_params.en = %d\n",
							car_params.en);
						printf("car_params.meth = %d\n",
							car_params.meth);
						printf("car_params.gain1.gain = %d\n",
							car_params.gain1.gain);
						printf("car_params.gain1.shft = %d\n",
							car_params.gain1.shft);
						printf("car_params.gain1.gain_min = %d\n",
							car_params.gain1.gain_min);
						printf("car_params.gain2.gain = %d\n",
							car_params.gain2.gain);
						printf("car_params.gain2.shft = %d\n",
							car_params.gain2.shft);
						printf("car_params.gain2.gain_min = %d\n",
							car_params.gain2.gain_min);
						printf("car_params.hpf = %d\n",
							car_params.hpf);
						printf("car_params.hpf_thr = %d\n",
							car_params.hpf_thr);
						printf("car_params.hpf_shft = %d\n",
							car_params.hpf_shft);
						printf("car_params.sw0 = %d\n",
							car_params.sw0);
						printf("car_params.sw1 = %d\n",
							car_params.sw1);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for CAR.\n");
						goto resize_clean;
					} else
						printf("Success in setting CAR params\n");
				}
				break;
			}

			case PREV_CGS:
			{
				mod_params.len = sizeof(struct prev_cgs);
				mod_params.param = &cgs_params;
				if (en_cgs) {
					if (en_log) {
						printf("cgs_params.en = %d\n",
							cgs_params.en);
						printf("cgs_params.h_thr = %d\n",
							cgs_params.h_thr);
						printf("cgs_params.h_slope = %d\n",
							cgs_params.h_slope);
						printf("cgs_params.h_shft = %d\n",
							cgs_params.h_shft);
						printf("cgs_params.h_min = %d\n",
							cgs_params.h_min);
					}
					if (ioctl(preview_fd,PREV_S_PARAM, &mod_params) < 0) {
						perror("Error in PREV_S_PARAM for CGS.\n");
						goto resize_clean;
					} else
						printf("Success in setting CGS params\n");
				}
				break;
			}
			
			default:
			// unknown module
			;
		} 
		cap.index++;
	}	
	req_buf.buf_type = IMP_BUF_IN;
	req_buf.size = size;
	req_buf.count = APP_IN_BUFS;
	
	if (ioctl(preview_fd, PREV_REQBUF, &req_buf) < 0) {
		perror("Error in PREV_REQBUF for IMP_BUF_IN\n");
		goto preview_clean;
	} 
		
	for (i = 0; i < APP_IN_BUFS; i++) {
		buf_in[i].index = i;
		buf_in[i].buf_type = IMP_BUF_IN;
		if (ioctl(preview_fd, PREV_QUERYBUF, &buf_in[i]) < 0) {
			perror("Error in PREV_QUERYBUF for IMP_BUF_IN\n");
			goto preview_clean;
		}
	}
	printf("PREV_QUERYBUF successful for IMP_BUF_IN\n");
	req_buf.buf_type = IMP_BUF_OUT1;
	req_buf.size = output1_size;
	req_buf.count = APP_OUT1_BUFS;
	
	if (ioctl(preview_fd, PREV_REQBUF, &req_buf) < 0) {
		perror("Error in PREV_REQBUF for IMP_BUF_OUT1\n");
		goto preview_clean;
	}
	for (i = 0; i < APP_OUT1_BUFS; i++) {
		buf_out1[i].index = i;
		buf_out1[i].buf_type = IMP_BUF_OUT1;
		if (ioctl(preview_fd, PREV_QUERYBUF, &buf_out1[i]) < 0) {
			perror("Error in PREV_QUERYBUF for IMP_BUF_OUT1\n");
			goto preview_clean;
		}
	}
	printf("PREV_QUERYBUF successful for IMP_BUF_OUT1\n");

	if (second_out_en) {
		req_buf.buf_type = IMP_BUF_OUT2;
		req_buf.size = output2_size;
		req_buf.count = APP_OUT2_BUFS;
	
		if (ioctl(preview_fd, PREV_REQBUF, &req_buf) < 0) {
			perror("Error in PREV_REQBUF for IMP_BUF_OUT2\n");
			goto preview_clean;
		}
		for (i = 0; i < APP_OUT2_BUFS; i++) {
			buf_out2[i].index = i;
			buf_out2[i].buf_type = IMP_BUF_OUT2;
			if (ioctl(preview_fd, PREV_QUERYBUF, &buf_out2[i]) < 0) {
				perror("Error in PREV_QUERYBUF for IMP_BUF_OUT2\n");
				goto preview_clean;
			}
		}
	}

	input_buffer = mmap(
			NULL,buf_in[0].size, 
			PROT_READ|PROT_WRITE, 
			MAP_SHARED, 
			preview_fd, 
			buf_in[0].offset);
	
	if (input_buffer == MAP_FAILED) {
		perror("Error in MMAP\n");
		goto preview_clean;
	}

	output_buffer1 = mmap(
			NULL,buf_out1[0].size, 
			PROT_READ|PROT_WRITE, 
			MAP_SHARED, 
			preview_fd, 
			buf_out1[0].offset);
	printf("output offset = %x\n", buf_out1[0].offset);
	if (output_buffer1 == MAP_FAILED) {
		perror("Error in MMAP\n");
		goto mmap_inbuf_clean;
	}

	if (second_out_en) {
		output_buffer2 = mmap(
			NULL,buf_out2[0].size, 
			PROT_READ|PROT_WRITE, 
			MAP_SHARED, 
			preview_fd, 
			buf_out2[0].offset);
		if (output_buffer2 == MAP_FAILED) {
			perror("Error in MMAP\n");
			goto mmap_buf1_clean;
		}
	}

	bzero(&convert,sizeof(convert));
	memcpy(input_buffer,in_buf,(WIDTH*HEIGHT*BYTESPERLINE));
	convert.in_buff.buf_type = IMP_BUF_IN;
	convert.in_buff.index = 0;
	convert.in_buff.offset = buf_in[0].offset;
	convert.in_buff.size = buf_in[0].size;
	convert.out_buff1.buf_type = IMP_BUF_OUT1;
	convert.out_buff1.index = 0;
	convert.out_buff1.offset = buf_out1[0].offset;
	convert.out_buff1.size = buf_out1[0].size;
	if (second_out_en) {
		convert.out_buff2.buf_type = IMP_BUF_OUT2;
		convert.out_buff2.index = 0;
		convert.out_buff2.offset = buf_out2[0].offset;
		convert.out_buff2.size = buf_out2[0].size;
	}
	if (ioctl(preview_fd, PREV_PREVIEW, &convert) < 0) {
		perror("Error in doing preview\n");
		goto mmap_clean;
	} 

	printf("output1 width = %d, height = %d, image size = %d\n",
		out_width, out_height, output1_size); 
	if (second_out_en)
		printf("output2 width = %d, height = %d, image size = %d\n",
			second_out_width, second_out_height, output2_size); 

	if (fwrite(output_buffer1, 1, output1_size, outp1_f) != output1_size) {
		perror("Error in writing to file\n");
		goto mmap_clean;
	} 

	if (second_out_en) {
		if (fwrite(output_buffer2, 1, output2_size, outp2_f) != output2_size)
			perror("Error in writing to file\n");
	}

mmap_clean:
	if (second_out_en)
		munmap(output_buffer2, buf_out2[0].size);
mmap_buf1_clean:
	munmap(output_buffer1, buf_out1[0].size);
mmap_inbuf_clean:
	munmap(input_buffer, buf_in[0].size);
preview_clean:
	if (!close(preview_fd))
		printf("previewer closed successfully\n");
	else
		printf("Error in closing previewer\n");

resize_clean:
	if (resize) {
		if (!close(resizer_fd))
			printf("resizer closed successfully\n");
		else
			printf("Error in closing resizer\n");
	}
file2_clean:
	if (second_out_en)
		fclose(outp2_f);
file1_clean:
	fclose(outp1_f);
inp_file_clean:
	fclose(inp_f);
	return 0;
}

