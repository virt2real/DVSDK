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
**|         Copyright (c) 1998-2004 Texas Instruments Incorporated           |**
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
/*
 * File name : saResize.c
 * Decription : This file resizes a 1920x1080 buffer to a 720x480 size.
		The application currently uses buffers allocated by the 
		VDCE driver for input and output. The input is taken from
		a file, copied into the "inaddress", and resizes into 
		"outaddress"
		size of inaddress buffer = 1920x1080x2
		size of outaddress buffer = 720x480x2

  Flow: 
1080i.yuv(file on nfs)->inaddr--->RESIZE--->outaddress->480i.yuv
*/
/******************************************************************************
  Header File Inclusion
******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <linux/davinci_vdce.h>
/******************************************************************************
  Macros
	Changing the following will result in different resizing ratios.
	PITCH:
	The pitch giverns the buffers' offset.(bytes to traverse to get 
	to the next line
	Rest of them are self explanatory.
 ******************************************************************************/
#define DEVICE_NAME	"/dev/DavinciHD_vdce"
#define IN_HEIGHT	1080
#define IN_WIDTH	1920
#define IN_PITCH	1920
#define OUT_HEIGHT       480
#define OUT_WIDTH	 720
#define OUT_PITCH	 720
#define INPUTFILE	"1080i.yuv"
#define OUTPUTFILE	"480_output.yuv"
/******************************************************************************
                        Function Definitions
 ******************************************************************************/
void read_from_file(unsigned char *,char *,int);
void write_to_file(unsigned char *, char *,int);
int  init_vdce_engine(int);
int  resize(int);
char * in_file, * out_file;

static int input_type, output_type, in_height, out_height, in_width, out_width;

void menu()
{
	printf("vpif_userptr_loopback -c <channel> -s <stress test> -p <print frame");
	printf(" number, -m <ntsc or pal>\n");
}

/******************************************************************************
  			Program Main
*******************************************************************************/
int main(int argc, char *argv[])
{
	int ret=0, index,d;
	char shortoptions[] = "i:o:";
	int vdcefd = 0;
	vdce_reqbufs_t	reqbuf;
	vdce_buffer_t buffer;
	void *inaddress,*outaddress;
	
	for (;;) {
		d = getopt_long(argc, argv, shortoptions, (void *)NULL, &index);
		if (-1 == d)
			break;
		switch (d) {
		case 'o':
		case 'O':
			output_type = atoi(optarg);
			break;
		case 'i':
		case 'I':
			input_type = atoi(optarg);
			break;
		default:
			menu();
			exit(1);
		}
	}

	/*STEP1:  Open VDCE device */
	
	vdcefd = open(DEVICE_NAME,O_RDWR);
	if( vdcefd <= 0){
 	        perror("Unable to open VDCE Driver.\n");
                close(vdcefd);
                exit(-1);
	}
        /*
	STEP2: 
	Buffer allocation
	The buffers can be allocated either from 
	the VDCE driver or user pointers can be used
	*/

	/*
	VDCE allocated buffers:
	Request for 1 input buffer of size 1920x1080x2of 4:2:2 format
	Here HEIGHT = Height of Y portion of the buffer.Driver 
	understands that double the size is needed for a 4:2:2 buffer.
	PITCH is NOT restriced to be 1920. It could be more if needed.
	*/
	printf("Hi 1 \n");

	if(input_type == 0)
	{
		in_width = 720;
		in_height = 480;
		in_file = "480i.yuv";
	}
	else if(input_type == 1)
	{
		in_width = 720;
		in_height = 576;
		in_file = "576i.yuv";
	}
	else if(input_type == 2)
	{
		in_width = 1280;
		in_height = 720;
		in_file = "720p.yuv";
	}
	else if(input_type == 3)
	{
		in_width = 1920;
		in_height = 1080;
		in_file = "1080i.yuv";
	}
	else if(input_type == 4)
	{
		in_width = 1920;
		in_height = 1080;
		in_file = "1080p.yuv";
	}

	if(output_type == 0)
	{
		out_width = 720;
		out_height = 480;
		out_file = "480i.yuv";
	}
	else if(output_type == 1)
	{
		out_width = 720;
		out_height = 576;
		out_file = "576i.yuv";
	}
	else if(output_type == 2)
	{
		out_width = 1280;
		out_height = 720;
		out_file = "720p.yuv";
	}
	else if(output_type == 3)
	{
		in_width = 1920;
		in_height = 1080;
		out_file = "1080i.yuv";
	}
	else if(output_type == 4)
	{
		out_width = 1920;
		out_height = 1080;
		out_file = "1080p.yuv";
	}

		
        reqbuf.buf_type = VDCE_BUF_IN;
        reqbuf.num_lines = in_height;
        reqbuf.bytes_per_line = in_width;
        reqbuf.image_type = VDCE_IMAGE_FMT_422;
        reqbuf.count = 1;
        if (ioctl(vdcefd, VDCE_REQBUF, &reqbuf) < 0) {
                perror("buffer allocation error.\n");
                close(vdcefd);
                exit(-1);
        }
	printf("Hi 2 \n");
        /* request for 1 output buffer of size 720x480x2*/
	printf("width = %d \n", out_width);
	printf("height = %d \n", out_height); 
        reqbuf.buf_type = VDCE_BUF_OUT;
        reqbuf.num_lines = out_height;
        reqbuf.bytes_per_line = out_width;
        reqbuf.image_type = VDCE_IMAGE_FMT_422;
        reqbuf.count =1;
        if (ioctl(vdcefd, VDCE_REQBUF, &reqbuf) < 0) {
                perror("buffer allocation error.\n");
                close(vdcefd);
                exit(-1);
        }
	printf("Hi 3 \n");
        /* STEP3:
	Query physical address buffers and map them to user
	space. */
        buffer.buf_type = VDCE_BUF_IN;
        buffer.index = 0;
        if (ioctl(vdcefd, VDCE_QUERYBUF, &buffer) < 0) {
                perror("buffer query  error.\n");
		/*
		closing a device takes care of freeing up
		of the buffers automatically
		*/
                close(vdcefd);
        }
	printf("Hi 4 \n");
        inaddress =
                 mmap(NULL, buffer.size,
                        PROT_READ | PROT_WRITE, MAP_SHARED,
                 vdcefd, buffer.offset);
	printf("Hi 5 \n");
        /* mapping input buffer */
        if (inaddress == MAP_FAILED) {
                perror("\nerror in mmaping output buffer");
                close(vdcefd);
                exit(1);
        }
	printf("Hi 6 \n");
        /* quering physical address for output buffer */
        buffer.buf_type = VDCE_BUF_OUT;
        buffer.index = 0;
        if (ioctl(vdcefd, VDCE_QUERYBUF, &buffer) < 0) {
                perror("buffer query  error.\n");
                close(vdcefd);
        }
	printf("Hi 7 \n");
        outaddress =
                 mmap(NULL, buffer.size,
                        PROT_READ | PROT_WRITE, MAP_SHARED,
                 vdcefd, buffer.offset);
	printf("Hi 8 \n");
        /* mapping output buffer */
        if (outaddress == MAP_FAILED) {
                printf("\nerror in mmaping output buffer");
                close(vdcefd);
                exit(1);
        }
	printf("Hi 9 \n");
	/*STEP4:
	Buffer preperation. Copy the data into an input buffer from a file.
	This step could be different depnding on the app. One could also 
	use the user pointers to prepare the data.
	The way to copy the file into buffer depends on the buffer pitch too. 
	If the pitches of the file and the buffer are different, consider 
	copying them line by line.
	*/
	read_from_file(inaddress,in_file,in_height*in_width*2);
	/*
	STEP5:
	Initialize the parameters of VDCE.
	*/	
	ret = init_vdce_engine(vdcefd);
	if(ret) {
		perror("Cannot initialize Vdce Driver\n");
		return -1;
	}
	printf("Hi 10 \n");
	/* STEP6:
	Issue a call to RESIZE. This requires the input/output buffe pointer 
	info and info regarding usage of either user pointers/driver 
	allocated buffers.
	*/
	ret = resize(vdcefd);
	if(ret<0) {
		perror("resize operation failed\n");
	}
	/* Dump the resized data to file */
	write_to_file(outaddress,out_file,out_height*out_width*2);
	printf("Resize complete. \n\n");
	printf("Hi 10 \n");
	/*STEP7:
	Close the file handle and un map the buffer the buffer
	*/
	munmap(inaddress,in_height*in_width*2);
	munmap(outaddress,out_height*out_width*2);
	close(vdcefd);

}


/*
 *=====================init_vdce_engine===========================*/
/* set the necessary parameters */
int init_vdce_engine(int vdcefd )
{
	vdce_params_t vdce_params;

	/* We want to RESIZE.(as agianst other operations
	like CCV,BLEND etc)
	*/
	vdce_params.vdce_mode = VDCE_OPERATION_RESIZING;

	/* Get the default set of parameters to save ourselves from
	enetring a whole host of parameters and using wrong parameters
	*/
	if (ioctl(vdcefd, VDCE_GET_DEFAULT, &vdce_params) < 0) {
		printf("default params failed error.\n");
		return -1;
	}
	/* change input and output size from the dafaults 
	applicable for the current need
	*/
	vdce_params.common_params.src_hsz_luminance = in_width;
	vdce_params.common_params.src_vsz_luminance = in_height;

	/* set output size  */
	vdce_params.common_params.dst_hsz_luminance = out_width;
	vdce_params.common_params.dst_vsz_luminance= out_height;
	/* 
	   --------------
	   ************** == INTERLACED FRAME or POGRESSIVE FRAME
	   --------------
	   **************
	
	   --------------
	   -------------- == INTERLACED FIELD
	   **************
	   **************
	   PROGRESSIVE indicates that we wish use a full framed buffer.
	   One could also use INTERLACED FRAME.INTERLACED
	   FIELD mode indicates separated fields.
	*/
	if((input_type == 0) || (input_type == 1) || (input_type == 3))
	vdce_params.common_params.src_processing_mode = VDCE_INTERLACED;
	else 
	vdce_params.common_params.src_processing_mode = VDCE_PROGRESSIVE;
	vdce_params.common_params.src_mode = VDCE_FRAME_MODE;
	vdce_params.common_params.res_mode = VDCE_FRAME_MODE;

	/* call ioctl to set parameters */
	if (ioctl(vdcefd, VDCE_SET_PARAMS, &vdce_params) < 0) {
		printf("set params failed \n");
		return -1;
	}
	return 0;
}
/*
 *=====================resize===========================*/
/*This function triggers the resize operation */
int resize(int vdcefd)
{
	vdce_address_start_t runtime_params;

	/* Here 0 is the index of the  Driver allocated buffer.
	For multiple driver allocated buffers, use 0,1,2 etc.
	If one wishes to use user pointers, the index should be set to -1
	 */
	runtime_params.buffers[VDCE_BUF_IN].index =0;/* Index number */
	runtime_params.buffers[VDCE_BUF_OUT].index =0;/* Index number */
	runtime_params.src_horz_pitch = in_width;
	runtime_params.res_horz_pitch = out_width;

        if (ioctl(vdcefd, VDCE_START, &runtime_params) < 0) {
                perror("ge start failed \n");
                return -1;
        }

	return 0;
}

/*
 *=====================read_from_file===========================
 It will take the data from file and fill in ge buffer 
*/

void read_from_file(unsigned char *addr,char *filename,int size)
{
        FILE *fp;
        fp = fopen(filename, "rb");
        if(fp == NULL) {
                printf("Cannot open file \n");
                exit(0);
        }
        fread(addr,size,1,fp);
        fclose(fp);
}
/*
 *=====================write_to_file===========================
It will take the output data and dump into file 
*/

void write_to_file(unsigned char *addr, char *filename, int size)
{
        FILE *fp;
        fp = fopen(filename, "wb");
        if(fp == NULL) {
                printf("Cannot open file = %s\n",filename);
                return ;
        }
        fwrite(addr,size,1,fp);
        fclose(fp);
}
