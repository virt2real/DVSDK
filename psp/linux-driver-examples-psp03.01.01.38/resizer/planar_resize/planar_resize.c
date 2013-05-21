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
/* Application for 20 upsampling of8bit planar data*/
/* Header files */
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/time.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <time.h>

/* Kernel header file, prefix path comes from makefile */
#include <linux/davinci_resizer.h>

/*******************************************************************************
 *	LOCAL DEFINES
 */
#define QMUL  (0x100)
#define COEF(nr, dr)   ( (short)( ((nr)*(int)QMUL)/(dr) ) )	/* coeff = nr/dr */
#define RDRV_RESZ_SPEC__MAX_FILTER_COEFF 32
#define IN_HEIGHT			480
#define IN_WIDTH			640
#define IN_PITCH			640
#define OUT_HEIGHT			240
#define OUT_WIDTH			320
#define OUT_PITCH			320
#define IMAGE_WIDTH			1280
#define IMAGE_HEIGHT			720

short gRDRV_reszFilter4TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF] = {
	0, 256, 0, 0, -6, 246, 16, 0, -7, 219, 44, 0, -5, 179, 83, -1, -3,
	130, 132, -3, -1, 83, 179, -5, 0, 44, 219, -7, 0, 16, 246, -6
};
short gRDRV_reszFilter7TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF] = {
	-1, 19, 108, 112, 19, -1, 0, 0, 0, 6, 88, 126, 37, -1, 0, 0,
	0, 0, 61, 134, 61, 0, 0, 0, 0, -1, 37, 126, 88, 6, 0, 0
};

/*
short gRDRV_reszFilter4TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF] = {
 COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4),
  COEF(1, 4), COEF(1, 4), COEF(1, 4), COEF(1, 4)
};

short gRDRV_reszFilter7TapHighQuality[RDRV_RESZ_SPEC__MAX_FILTER_COEFF] = {
  COEF(1, 7), COEF(1, 7), COEF(1, 7), COEF(1, 7),
  COEF(1, 7), COEF(1, 7), COEF(1, 7),0,
  COEF(1, 7), COEF(1, 7), COEF(1, 7), COEF(1, 7),
  COEF(1, 7), COEF(1, 7), COEF(1, 7), 0,
  COEF(1, 7), COEF(1, 7), COEF(1, 7), COEF(1, 7),
  COEF(1, 7), COEF(1, 7), COEF(1, 7), 0,
  COEF(1, 7), COEF(1, 7), COEF(1, 7), COEF(1, 7),
  COEF(1, 7), COEF(1, 7), COEF(1, 7), 0,
};*/

/*******************************************************************************
 *	FUNCTION DEFINITIONS
 */
/* resize test case of 8 bit data with 2x upsampling different for y cb and cr data*/
/* channel 1 contains y data 2 contains cb data 3 contains cr data*/
int main()
{
	struct rsz_params ch1_params;
	struct rsz_buffer ch1_bufd;
	struct rsz_reqbufs ch1_req_outbufs, ch1_req_inbufs;
	struct rsz_resize ch1_resize;
	char *ch1_inBuf = 0;
	char *ch1_outBuf = 0;
	char *ch1_map_ptr_dest = 0, *ch1_map_ptr_src = 0;
	int ch1_fd;

	/* Channel 2 variable */
	struct rsz_params ch2_params;
	struct rsz_buffer ch2_bufd;
	struct rsz_reqbufs ch2_req_outbufs, ch2_req_inbufs;
	struct rsz_resize ch2_resize;

	char *ch2_inBuf = 0;
	char *ch2_outBuf = 0;
	char *ch2_map_ptr_dest = 0, *ch2_map_ptr_src = 0;
	int ch2_fd;

	/*Channel 3 */
	struct rsz_params ch3_params;
	struct rsz_buffer ch3_bufd;
	struct rsz_reqbufs ch3_req_outbufs, ch3_req_inbufs;
	struct rsz_resize ch3_resize;

	char *ch3_inBuf = 0;
	char *ch3_outBuf = 0;
	char *ch3_map_ptr_dest = 0, *ch3_map_ptr_src = 0;
	int ch3_fd;

	FILE *ydata;
	FILE *cbdata;
	FILE *crdata;
	FILE *outputimage;

	/* input files */
	ydata = fopen("yfinaldeci.bin", "rb");
	cbdata = fopen("cbfinaldeci.bin", "rb");
	crdata = fopen("crfinaldeci.bin", "rb");

	/* output file in format first all y data than all u and than all v */
	outputimage = fopen("8bitfinaloutput.YUV", "wb");

	int i;

	/*openning a channel */
	ch1_fd = open("/dev/davinci_resizer", O_RDWR);

	if (ch1_fd < 0) {
		printf("\n Resizer device open  failed");
		return 1;
	}
	/* allocating the memory to input buffer */
	ch1_req_inbufs.buf_type = RSZ_BUF_IN;
	ch1_req_inbufs.size = IN_HEIGHT * IN_WIDTH;
	ch1_req_inbufs.count = 1;

	printf("starting memory allocation \n");

	if (ioctl(ch1_fd, RSZ_REQBUF, &ch1_req_inbufs) == -1) {
		printf("buffer allocation error.\n");
		close(ch1_fd);
		exit(-1);
	}
	/* allocating the memory to output buffer */
	ch1_req_outbufs.buf_type = RSZ_BUF_OUT;
	ch1_req_outbufs.size = OUT_HEIGHT * OUT_WIDTH;
	ch1_req_outbufs.count = 1;

	if (ioctl(ch1_fd, RSZ_REQBUF, &ch1_req_outbufs) == -1) {
		printf("buffer allocation error");
		close(ch1_fd);
		exit(-1);
	}
	/* getting physical address for mmap */
	ch1_bufd.buf_type = RSZ_BUF_IN;
	ch1_bufd.index = 0;
	if (ioctl(ch1_fd, RSZ_QUERYBUF, &ch1_bufd) == -1) {
		printf("query buffer failed \n");
		close(ch1_fd);
		exit(-1);
	}
	ch1_resize.in_buf.offset = ch1_bufd.offset;

	ch1_inBuf = ch1_map_ptr_src =
	    (char *)mmap(0, IN_HEIGHT * IN_WIDTH, PROT_READ | PROT_WRITE,
			 MAP_SHARED, ch1_fd, ch1_bufd.offset);
	if (ch1_inBuf == MAP_FAILED) {
		printf("\n error in mmaping input buffer");
		close(ch1_fd);
		exit(1);
	}
	printf("the inbuf after returning offset is %p \n", ch1_inBuf);
	printf("mmap done  \n");

	/* map the output buffers to user space */
	ch1_bufd.buf_type = RSZ_BUF_OUT;
	ch1_bufd.index = 0;
	if (ioctl(ch1_fd, RSZ_QUERYBUF, &ch1_bufd) == -1) {
		printf(" query buffer failed \n");
		close(ch1_fd);
		exit(-1);
	}
	ch1_resize.out_buf.offset = ch1_bufd.offset;
	ch1_outBuf = ch1_map_ptr_dest =
	    (char *)mmap(0, OUT_HEIGHT * OUT_WIDTH,
			 PROT_READ | PROT_WRITE, MAP_SHARED, ch1_fd,
			 ch1_bufd.offset);
	if (ch1_outBuf == MAP_FAILED) {
		printf("\nerror in mmaping output buffer");
		close(ch1_fd);
		exit(1);
	}
	printf("the  outbuf offset after retutning is %p \n", ch1_outBuf);

	printf("mmap  \n");
	printf("\n Configuartion of parameters \n");

	ch1_params.in_hsize = IN_WIDTH;
	ch1_params.in_vsize = IN_HEIGHT;	/* only 1 filed of NTSC image */
	ch1_params.in_pitch = IN_PITCH;
	ch1_params.cbilin = 0;	/* filter with luma for low pass */
	ch1_params.pix_fmt = RSZ_PIX_FMT_PLANAR;
	ch1_params.out_hsize = OUT_WIDTH;
	ch1_params.out_vsize = OUT_HEIGHT;
	ch1_params.out_pitch = OUT_PITCH;
	ch1_params.vert_starting_pixel = 0;
	ch1_params.horz_starting_pixel = 0;
	ch1_params.inptyp = RSZ_INTYPE_PLANAR_8BIT;
	ch1_params.hstph = 0;
	ch1_params.vstph = 0;
	ch1_params.yenh_params.type = RSZ_YENH_DISABLE;

	/* If the resize ration is less between 1/2x to 4x use these coefficients */
	/* else use  gRDRV_reszFilter7TapHighQuality */
	for (i = 0; i < 32; i++)
		ch1_params.hfilt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	for (i = 0; i < 32; i++)
		ch1_params.vfilt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	if (ioctl(ch1_fd, RSZ_S_PARAM, &ch1_params) == -1) {
		printf(" Setting parameters failed \n");
		close(ch1_fd);
		exit(-1);
	}
	/* taking the input image y componnent from the whole image of 720*1280 */
	for (i = 0; i < IN_HEIGHT; i++) {

		fread(ch1_inBuf, 1, IN_WIDTH, ydata);
		ch1_inBuf = ch1_inBuf + IN_WIDTH;
		fseek(ydata, (IMAGE_WIDTH - IN_WIDTH), SEEK_CUR);

	}

	printf("mem copy finished \n");

	/*Channel 2 */

	/* openning a channel */
	ch2_fd = open("/dev/davinci_resizer", O_RDWR);
	if (ch2_fd < 0) {
		printf("\n Resizer device open  failed");
		return 1;
	}
	/* allocating memory to input buffer */
	ch2_req_inbufs.buf_type = RSZ_BUF_IN;
	ch2_req_inbufs.size = (IN_HEIGHT * (IN_WIDTH / 2));
	ch2_req_inbufs.count = 1;

	printf("starting memory allocation \n");

	if (ioctl(ch2_fd, RSZ_REQBUF, &ch2_req_inbufs) == -1) {
		printf("buffer allocation error.\n");
		close(ch2_fd);
		exit(-1);
	}
	/* allocating memory to output buffer */
	ch2_req_outbufs.buf_type = RSZ_BUF_OUT;
	ch2_req_outbufs.size = (OUT_HEIGHT * (OUT_WIDTH / 2));
	ch2_req_outbufs.count = 1;

	/* requesting the physical address */
	if (ioctl(ch2_fd, RSZ_REQBUF, &ch2_req_outbufs) == -1) {
		printf("buffer allocation error");
		close(ch2_fd);
		exit(-1);
	}

	ch2_bufd.buf_type = RSZ_BUF_IN;
	ch2_bufd.index = 0;
	if (ioctl(ch2_fd, RSZ_QUERYBUF, &ch2_bufd) == -1) {
		printf("query buffer failed \n");
		close(ch2_fd);
		exit(-1);
	}
	ch2_resize.in_buf.offset = ch2_bufd.offset;

	ch2_inBuf = ch2_map_ptr_src =
	    (char *)mmap(0, (IN_HEIGHT * (IN_WIDTH / 2)),
			 PROT_READ | PROT_WRITE, MAP_SHARED, ch2_fd,
			 ch2_bufd.offset);
	if (ch2_inBuf == MAP_FAILED) {
		printf("\n error in mmaping input buffer");
		close(ch2_fd);
		exit(1);
	}
	printf("the inbuf after returning offset is %p \n", ch2_inBuf);
	printf("mmap done  \n");

	/* map the output buffers to user space */
	ch2_bufd.buf_type = RSZ_BUF_OUT;
	ch2_bufd.index = 0;
	if (ioctl(ch2_fd, RSZ_QUERYBUF, &ch2_bufd) == -1) {
		printf(" query buffer failed \n");
		close(ch2_fd);
		exit(-1);
	}
	ch2_resize.out_buf.offset = ch2_bufd.offset;
	ch2_outBuf = ch2_map_ptr_dest =
	    (char *)mmap(0, (OUT_HEIGHT * (OUT_WIDTH / 2)),
			 PROT_READ | PROT_WRITE, MAP_SHARED, ch2_fd,
			 ch2_bufd.offset);
	if (ch2_outBuf == MAP_FAILED) {
		printf("\nerror in mmaping output buffer");
		close(ch2_fd);
		exit(1);
	}
	printf("the  outbuf offset after retutning is %p \n", ch2_outBuf);

	printf("mmap  \n");
	printf("\n Configuartion of parameters \n");

	ch2_params.in_hsize = (IN_WIDTH / 2);
	ch2_params.in_vsize = IN_HEIGHT;	/* only 1 filed of NTSC image */
	ch2_params.in_pitch = (IN_PITCH / 2);
	ch2_params.cbilin = 0;	/* filter with luma for low pass */
	ch2_params.pix_fmt = RSZ_PIX_FMT_PLANAR;
	ch2_params.out_hsize = (OUT_WIDTH / 2);
	ch2_params.out_vsize = OUT_HEIGHT;
	ch2_params.out_pitch = (OUT_PITCH / 2);
	ch2_params.vert_starting_pixel = 0;
	ch2_params.horz_starting_pixel = 0;
	ch2_params.inptyp = RSZ_INTYPE_PLANAR_8BIT;
	ch2_params.hstph = 0;
	ch2_params.vstph = 0;
	ch2_params.yenh_params.type = RSZ_YENH_DISABLE;

	/* If the resize ration is less between 1/2x to 4x use these coefficients */
	/* else use  gRDRV_reszFilter7TapHighQuality */
	for (i = 0; i < 32; i++)
		ch2_params.hfilt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	for (i = 0; i < 32; i++)
		ch2_params.vfilt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	if (ioctl(ch2_fd, RSZ_S_PARAM, &ch2_params) == -1) {
		printf(" Setting parameters failed \n");
		close(ch2_fd);
		exit(-1);
	}
	/* taking the input image cb componnent from the whole image of 720*640 */
	for (i = 0; i < IN_HEIGHT; i++) {

		fread(ch2_inBuf, 1, (IN_WIDTH / 2), cbdata);

		ch2_inBuf = ch2_inBuf + (IN_WIDTH / 2);
		fseek(cbdata, ((IMAGE_WIDTH / 2) - (IN_WIDTH / 2)), SEEK_CUR);

	}

	printf("mem copy finished \n");

	/* Channel 3 */
	/* openning a channel */
	ch3_fd = open("/dev/davinci_resizer", O_RDWR);

	if (ch3_fd < 0) {
		printf("\n Resizer device open  failed");
		return 1;
	}
	/*allocating input buffer memory */
	ch3_req_inbufs.buf_type = RSZ_BUF_IN;
	ch3_req_inbufs.size = (IN_HEIGHT * (IN_WIDTH / 2));
	ch3_req_inbufs.count = 1;

	printf("starting memory allocation \n");

	if (ioctl(ch3_fd, RSZ_REQBUF, &ch3_req_inbufs) == -1) {
		printf("buffer allocation error.\n");
		close(ch3_fd);
		exit(-1);

	}
	/*allocating output buffer memory */
	ch3_req_outbufs.buf_type = RSZ_BUF_OUT;
	ch3_req_outbufs.size = (OUT_HEIGHT * (OUT_WIDTH / 2));
	ch3_req_outbufs.count = 1;

	if (ioctl(ch3_fd, RSZ_REQBUF, &ch3_req_outbufs) == -1) {
		printf("buffer allocation error");
		close(ch3_fd);
		exit(-1);
	}

	ch3_bufd.buf_type = RSZ_BUF_IN;
	ch3_bufd.index = 0;
	if (ioctl(ch3_fd, RSZ_QUERYBUF, &ch3_bufd) == -1) {
		printf("query buffer failed \n");
		close(ch3_fd);
		exit(-1);
	}
	ch3_resize.in_buf.offset = ch3_bufd.offset;

	ch3_inBuf = ch3_map_ptr_src =
	    (char *)mmap(0, (IN_HEIGHT * (IN_WIDTH / 2)),
			 PROT_READ | PROT_WRITE, MAP_SHARED, ch3_fd,
			 ch3_bufd.offset);
	if (ch3_inBuf == MAP_FAILED) {
		printf("\n error in mmaping input buffer");
		close(ch3_fd);
		exit(1);
	}
	printf("the inbuf after returning offset is %p \n", ch3_inBuf);
	printf("mmap done  \n");

	/* map the output buffers to user space */
	ch3_bufd.buf_type = RSZ_BUF_OUT;
	ch3_bufd.index = 0;
	if (ioctl(ch3_fd, RSZ_QUERYBUF, &ch3_bufd) == -1) {
		printf(" query buffer failed \n");
		close(ch3_fd);
		exit(-1);
	}
	ch3_resize.out_buf.offset = ch3_bufd.offset;
	ch3_outBuf = ch3_map_ptr_dest =
	    (char *)mmap(0, (OUT_HEIGHT * (OUT_WIDTH / 2)),
			 PROT_READ | PROT_WRITE, MAP_SHARED, ch3_fd,
			 ch3_bufd.offset);
	if (ch3_outBuf == MAP_FAILED) {
		printf("\nerror in mmaping output buffer");
		close(ch3_fd);
		exit(1);
	}
	printf("the  outbuf offset after retutning is %p \n", ch3_outBuf);

	printf("mmap  \n");
	printf("\n Configuartion of parameters \n");

	ch3_params.in_hsize = (IN_WIDTH / 2);
	ch3_params.in_vsize = IN_HEIGHT;	/* only 1 filed of NTSC image */
	ch3_params.in_pitch = (IN_PITCH / 2);
	ch3_params.cbilin = 0;	/* filter with luma for low pass */
	ch3_params.pix_fmt = RSZ_PIX_FMT_PLANAR;
	ch3_params.out_hsize = (OUT_WIDTH / 2);
	ch3_params.out_vsize = OUT_HEIGHT;
	ch3_params.out_pitch = (OUT_PITCH / 2);
	ch3_params.vert_starting_pixel = 0;
	ch3_params.horz_starting_pixel = 0;
	ch3_params.inptyp = RSZ_INTYPE_PLANAR_8BIT;
	ch3_params.hstph = 0;
	ch3_params.vstph = 0;
	ch3_params.yenh_params.type = RSZ_YENH_DISABLE;

	/* If the resize ration is less between 1/2x to 4x use these coefficients */
	/* else use  gRDRV_reszFilter7TapHighQuality */
	for (i = 0; i < 32; i++)
		ch3_params.hfilt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	for (i = 0; i < 32; i++)
		ch3_params.vfilt_coeffs[i] = gRDRV_reszFilter4TapHighQuality[i];

	if (ioctl(ch3_fd, RSZ_S_PARAM, &ch3_params) == -1) {
		printf(" Setting parameters failed \n");
		close(ch3_fd);
		exit(-1);
	}
	/* taking the input image cr componnent from the whole image of 720*640 */
	for (i = 0; i < IN_HEIGHT; i++) {

		fread(ch3_inBuf, 1, (IN_WIDTH / 2), crdata);
		ch3_inBuf = ch3_inBuf + (IN_WIDTH / 2);
		fseek(crdata, ((IMAGE_WIDTH / 2) - (IN_WIDTH / 2)), SEEK_CUR);

	}

	printf("mem copy finished \n");

	/*channel 1 resizing */

	ch1_resize.in_buf.index = -1;
	ch1_resize.out_buf.index = -1;
	ch1_resize.in_buf.size = IN_HEIGHT * IN_WIDTH;
	ch1_resize.out_buf.size = OUT_HEIGHT * OUT_WIDTH;

	printf("\nresize in offset = %x, resize out offset = %x\n",
	       ch1_resize.in_buf.offset, ch1_resize.out_buf.offset);

	if (ioctl(ch1_fd, RSZ_RESIZE, &ch1_resize) == -1) {
		printf(" Resize failed \n");
		close(ch1_fd);
		exit(-1);
	}

	/*fwrite((void *)ch1_outBuf,1,640*640,ydataoutput); */

	printf("Resizing finished \n");
	/*Channel 2 resizing */
	ch2_resize.in_buf.index = -1;
	ch2_resize.out_buf.index = -1;
	ch2_resize.in_buf.size = (IN_HEIGHT * (IN_WIDTH / 2));
	ch2_resize.out_buf.size = (OUT_HEIGHT * (OUT_WIDTH / 2));

	printf("\nresize in offset = %x, resize out offset = %x\n",
	       ch2_resize.in_buf.offset, ch2_resize.out_buf.offset);

	if (ioctl(ch2_fd, RSZ_RESIZE, &ch2_resize) == -1) {
		printf(" Resize failed \n");
		close(ch2_fd);
		exit(-1);
	}

	printf("Resizing finished \n");

	/*Channel 3 resizing */
	ch3_resize.in_buf.index = -1;
	ch3_resize.out_buf.index = -1;
	ch3_resize.in_buf.size = (IN_HEIGHT * (IN_WIDTH / 2));
	ch3_resize.out_buf.size = (OUT_HEIGHT * (OUT_WIDTH / 2));

	printf("\nresize in offset = %x, resize out offset = %x\n",
	       ch3_resize.in_buf.offset, ch3_resize.out_buf.offset);

	if (ioctl(ch3_fd, RSZ_RESIZE, &ch3_resize) == -1) {
		printf(" Resize failed \n");
		close(ch3_fd);
		exit(-1);
	}

	printf("Resizing finished \n");

	/* getting the output image */

	fwrite((void *)ch1_outBuf, 1, (OUT_HEIGHT * OUT_WIDTH), outputimage);
	fwrite((void *)ch2_outBuf, 1, (OUT_HEIGHT * (OUT_WIDTH / 2)),
	       outputimage);
	fwrite((void *)ch3_outBuf, 1, (OUT_HEIGHT * (OUT_WIDTH / 2)),
	       outputimage);

	fclose(outputimage);
	printf("resize completed \n");
	/* Closing a channel */
	close(ch1_fd);
	close(ch2_fd);
	close(ch3_fd);
	return 0;
}
