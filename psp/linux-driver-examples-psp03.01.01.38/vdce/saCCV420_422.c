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
 * File name : saCCV420_422.c
 * Decription : This file does the chroma conversion on 1920*1080 image size
		of format 4:2:0 to a 4:2:2 format.
		The application currently uses buffers allocated by the 
		VDCE driver for input and output. The input is taken from
		a file, copied into the "inaddress", and after doing choroma
		conversion stores into 	"outaddress".
		size of inaddress buffer = (1920x1080x3)/2
		size of outaddress buffer = (1920*1080*2)

  Flow: 
1080i_420.yuv(file on nfs)->inaddr--->CCV420_422--->outaddress->1080i_422.yuv
 */
/******************************************************************************
  Header File Inclusion
******************************************************************************/
#include <stdio.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <string.h>
#include <sys/mman.h>
#include <stdlib.h>
#include <linux/davinci_vdce.h>
/******************************************************************************
  Macros
	Changing the following will result in different image convesrions .
	PITCH:
	The pitch giverns the buffers' offset.(bytes to traverse to get 
	to the next line
	Rest of them are self explanatory.
 ******************************************************************************/
#define DEVICE_NAME	"/dev/DavinciHD_vdce"
#define IN_HEIGHT	1080
#define IN_WIDTH	1920
#define IN_PITCH	1920
#define OUT_HEIGHT      1080
#define OUT_WIDTH	1920
#define OUT_PITCH	1920
#define INPUTFILE	"1080i_420.yuv"
#define OUTPUTFILE	"1080_422.yuv"
/******************************************************************************
                        Function Definitions
 ******************************************************************************/
void read_from_file(unsigned char *,char *,int);
void write_to_file(unsigned char *, char *,int);
int  init_vdce_engine(int);
int  ccv420_422(int);
/******************************************************************************
  			Program Main
*******************************************************************************/
int main(int argc, char *argv[])
{
	int ret=0;
	int vdcefd = 0;
	vdce_reqbufs_t	reqbuf;
	vdce_buffer_t buffer;
	void *inaddress,*outaddress;
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
	Request for 1 input buffer of size (1920x1080x3)/2 of 4:2:0 format
	Here HEIGHT = Height of Y portion of the buffer.Driver 
	understands that size 1.5 times the size is needed for a 4:2:0 buffer.
	PITCH is NOT restriced to be 1920. It could be more if needed.
	*/
        reqbuf.buf_type = VDCE_BUF_IN;
        reqbuf.num_lines = IN_HEIGHT;
        reqbuf.bytes_per_line = IN_PITCH;
        reqbuf.image_type = VDCE_IMAGE_FMT_420;
        reqbuf.count = 1;
        if (ioctl(vdcefd, VDCE_REQBUF, &reqbuf) < 0) {
                perror("buffer allocation error.\n");
                close(vdcefd);
                exit(-1);
        }

        /* request for 1 output buffer of size 1920x1080x2*/
        reqbuf.buf_type = VDCE_BUF_OUT;
        reqbuf.num_lines = OUT_HEIGHT;
        reqbuf.bytes_per_line = OUT_PITCH;
        reqbuf.image_type = VDCE_IMAGE_FMT_422;
        reqbuf.count =1;
        if (ioctl(vdcefd, VDCE_REQBUF, &reqbuf) < 0) {
                perror("buffer allocation error.\n");
                close(vdcefd);
                exit(-1);
        }

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
        inaddress =
                 mmap(NULL, buffer.size,
                        PROT_READ | PROT_WRITE, MAP_SHARED,
                 vdcefd, buffer.offset);
        /* mapping input buffer */
        if (inaddress == MAP_FAILED) {
                perror("\nerror in mmaping output buffer");
                close(vdcefd);
                exit(1);
        }

        /* quering physical address for output buffer */
        buffer.buf_type = VDCE_BUF_OUT;
        buffer.index = 0;
        if (ioctl(vdcefd, VDCE_QUERYBUF, &buffer) < 0) {
                perror("buffer query  error.\n");
                close(vdcefd);
        }
        outaddress =
                 mmap(NULL, buffer.size,
                        PROT_READ | PROT_WRITE, MAP_SHARED,
                 vdcefd, buffer.offset);
        /* mapping output buffer */
        if (outaddress == MAP_FAILED) {
                printf("\nerror in mmaping output buffer");
                close(vdcefd);
                exit(1);
        }

	/*STEP4:
	Buffer preperation. Copy the data into an input buffer from a file.
	This step could be different depnding on the app. One could also 
	use the user pointers to prepare the data.The way to copy the 
	file into buffer depends on the buffer pitch too. If 
	the pitches of the file and the buffer are different, consider copying 
	them line by line.
	*/
	read_from_file(inaddress,INPUTFILE,((IN_HEIGHT*IN_PITCH*3)/2));
	/*
	STEP5:
	Initialize the parameters of VDCE.
	*/	
	ret = init_vdce_engine(vdcefd);
	if(ret) {
		perror("Cannot initialize Vdce Driver\n");
		return -1;
	}

	/* STEP6:
	Issue a call to CCV. This requires the input/output buffer pointer info
	and info regarding usage of either user pointers/driver allocated 
	buffers.
	*/
	ret = ccv420_422(vdcefd);
	if(ret<0) {
		perror("ccv operation failed\n");
	}
	/* Dump the CCV 422 fromat data to file */
	write_to_file(outaddress,OUTPUTFILE,OUT_HEIGHT*OUT_PITCH*2);
	printf("Color conversion 420->422 complete. Output written to"
			" file %s\n", OUTPUTFILE);
	printf("Use the saDisplay application to view the output on a "
			"connected display\n");

	/*STEP7:
	Close the file handle and unmap the buffer
	*/
	munmap(inaddress,(IN_HEIGHT*IN_PITCH*3)/2);
        munmap(outaddress,OUT_HEIGHT*OUT_PITCH*2);
	close(vdcefd);

}


/*
 *=====================init_vdce_engine===========================*/
/* set the necessary parameters */
int init_vdce_engine(int vdcefd )
{
	vdce_params_t vdce_params;

	/* We want to do CCV.(as agianst other operations
	like CCV,RESIZE etc)
	*/
	vdce_params.vdce_mode = VDCE_OPERATION_CHROMINANCE_CONVERSION;

	/* Get the default set of parameters to save ourselves from
	enetring a whole host of parameters and using wrong parameters
	*/
	if (ioctl(vdcefd, VDCE_GET_DEFAULT, &vdce_params) < 0) {
		printf("default params failed error.\n");
		return -1;
	}
	/* 
	420 - 422 Conversion 
	1920*1080 Y data to 1920*1080  Y data
	1920*540 C data to 1902*1080 C data
	
	Set the chrominance conversion type . It can be also of
	type conversting image of 422 to 420 or from 420 format to 420
	format.*/
	vdce_params.vdce_mode_params.ccv_params.conversion_type =
						 VDCE_CCV_MODE_420_422;

	/* change input and output size from the dafaults 
	applicable for the current need
	*/
	vdce_params.common_params.src_hsz_luminance = IN_WIDTH;
	vdce_params.common_params.src_vsz_luminance = IN_HEIGHT;

	/* set output size  */
	vdce_params.common_params.dst_hsz_luminance = OUT_WIDTH;
	vdce_params.common_params.dst_vsz_luminance= OUT_HEIGHT;
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
	   One could also use INTERLACED FRAME. for the same.INTERLACED
	   FIELD mode indicates separated fields.
	*/
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
 *=====================ccv420_422===========================*/
/*This function triggers the ccv operation */
int ccv420_422(int vdcefd)
{
	vdce_address_start_t runtime_params;

	/* Here 0 is the index of the  Driver allocated buffer.
	For multiple driver allocated buffers, use 0,1,2 etc.
	If one wishes to use user pointers, the index should be set to -1
	 */
	runtime_params.buffers[VDCE_BUF_IN].index =0;/* Index number */
	runtime_params.buffers[VDCE_BUF_OUT].index =0;/* Index number */
	runtime_params.src_horz_pitch = IN_PITCH;
	runtime_params.res_horz_pitch = OUT_PITCH;

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
                printf("Cannot open file %s. You should find it along with"
				" example source code\n", filename);
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
                printf("Cannot open file %s for writing.\n",filename);
                return ;
        }
        fwrite(addr,size,1,fp);
        fclose(fp);
}
