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

char dev_name_prev[1][30] = {"/dev/davinci_previewer"};
char dev_name_rsz[1][30] = {"/dev/davinci_resizer"};

void usage()
{
	printf("Usage:do_resize_420_420 -i file -o file \n");
}
#define MAX_WIDTH  1920
#define MAX_HEIGHT  1080
#define BYTESPERLINE 3/2
#define BYTESPERLINE_Y 1
#define BYTESPERLINE_UV 1/2
#define INPUT_HEIGHT  720
#define INPUT_WIDTH 1280 

#define OUTPUT_HEIGHT INPUT_HEIGHT/2
#define OUTPUT_WIDTH INPUT_WIDTH/2

#define BUF_SIZE ((1280*720) + (1280*360) + 32)
char in_buf[MAX_WIDTH*MAX_HEIGHT*BYTESPERLINE];

int main(int argc, char *argp[])
{
	char shortoptions[] = "i:o:w:h:t:";
	int mode = O_RDWR,c,ret,index;
	int preview_fd, resizer_fd, dev_idx;
	unsigned long oper_mode, user_mode, driver_mode;
	struct prev_channel_config prev_chan_config;
	struct prev_single_shot_config prev_ss_config; // single shot mode configuration
	struct rsz_channel_config rsz_chan_config; // resizer channel config
	struct rsz_single_shot_config rsz_ss_config; // single shot mode configuration
	struct rsz_reconfig rsz_ss_reconfig; //Reconfiguring the resizer input
	struct prev_cap cap;
	struct prev_module_param mod_param;
	struct prev_wb wb_params;
	struct imp_reqbufs req_buf;
	struct imp_buffer buf_in[3];
	struct imp_buffer buf_out1[3];
	struct imp_buffer buf_out2[3];
	struct imp_convert convert;
	int i,j;
	char in_file[100], out_file[100];
	FILE *inp_f, *outp_f;
	int width = 0, height = 0, size;
	char *input_buffer, *output_buffer;
	int in_format=0;
	unsigned long level;
	short byte=0;
	char out420_buf[BUF_SIZE];
	char *src, *dest;

	for(;;) {
		c = getopt_long(argc, argp, shortoptions, NULL, (void *)&index);
		if(-1 == c)
			break;
		switch(c) {
			case 'i':
				strcpy(in_file,optarg);
				break;
			case 'o':
				strcpy(out_file,optarg);
				break;
			case 'w':
				width = atoi(optarg);
				break;
			case 'h':
				height = atoi(optarg);
				break;
			case 't':
				in_format = atoi(optarg);
				break;
			default:
				usage();
				exit(1);
		}
	}

	printf("doing preview & resize on in_file = %s and writing out to out_file = %s\n",in_file,out_file);
	oper_mode = IMP_MODE_SINGLE_SHOT;

	printf("starting\n");
	inp_f = fopen(in_file, "rb");
	if (inp_f == NULL) {
		perror("Error in opening input file \n");
		exit(1);
	}
	outp_f = fopen(out_file, "wb");
	if (outp_f == NULL) {
		perror("Error in opening output file \n");
		exit(1);
	}

	size = fread(in_buf,1, (INPUT_WIDTH * INPUT_HEIGHT * BYTESPERLINE), inp_f);

	if (size != (INPUT_WIDTH * INPUT_HEIGHT * BYTESPERLINE)) {
		perror("mismatch between file size and  INPUT_WIDTH * INPUT_HEIGHT * 2\n");
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	}
// Setup resizer
	/* Open the resizer */
	printf("Configuring resizer in the chain mode\n");
	printf("Opening resizer device, %s\n",dev_name_rsz[0]);
	resizer_fd = open((const char *)dev_name_rsz[0], mode);
	if(resizer_fd <= 0) {
		printf("Cannot open resizer device\n");
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	}

	if (ioctl(resizer_fd,RSZ_S_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		fclose(inp_f);
		fclose(outp_f);
		close(resizer_fd);
		exit(1);
	}

	if (ioctl(resizer_fd,RSZ_G_OPER_MODE, &oper_mode) < 0) {
		perror("Can't get operation mode\n");
		fclose(inp_f);
		fclose(outp_f);
		close(resizer_fd);
		exit(1);
	}
	printf("RESIZER: Operating mode changed successfully to");
	if (oper_mode == IMP_MODE_SINGLE_SHOT) 
		printf(" %s", "Single Shot\n");
	else
		printf(" %s", "Continuous\n");

	printf("Setting default configuration in Resizer\n");
	bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = 0;
	rsz_chan_config.config = NULL; /* to set defaults in driver */
	if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration for single shot mode\n");
		fclose(inp_f);
		fclose(outp_f);
		close(resizer_fd);
		exit(1);
	}

	printf("default configuration setting in Resizer successfull\n");
	bzero(&rsz_ss_config, sizeof(struct rsz_single_shot_config));
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	rsz_chan_config.config = &rsz_ss_config;

	if (ioctl(resizer_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in getting resizer channel configuration from driver\n");
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	}

#if 0
	printf("Following are the default settings\n");
	printf("rsz_ss_config.input.image_width = %d\n",rsz_ss_config.input.image_width);
	printf("rsz_ss_config.input.image_height = %d\n",rsz_ss_config.input.image_height);
	printf("rsz_ss_config.input.vst = %d\n",rsz_ss_config.input.vst);
	printf("rsz_ss_config.input.hst = %d\n",rsz_ss_config.input.hst);
	printf("rsz_ss_config.input.ppln = %d\n",rsz_ss_config.input.ppln);
	printf("rsz_ss_config.input.lpfr = %d\n",rsz_ss_config.input.lpfr);
	printf("rsz_ss_config.input.clk_div.m = %d\n",rsz_ss_config.input.clk_div.m);
	printf("rsz_ss_config.input.clk_div.n = %d\n",rsz_ss_config.input.clk_div.n);
	//printf("rsz_ss_config.input.data_shift = %d\n", rsz_ss_config.input.data_shift); 
	//printf("rsz_ss_config.input.dec_en = %d\n",rsz_ss_config.input.dec_en);
	printf("rsz_ss_config.input.rsz = %d\n",rsz_ss_config.input.rsz);
	printf("rsz_ss_config.input.avg_filter_en = %d\n",rsz_ss_config.input.avg_filter_en);
//	printf("rsz_ss_config.input.dpc.en = %d\n",rsz_ss_config.input.dpc.en);
//	printf("rsz_ss_config.input.dpc.thr = %d\n",rsz_ss_config.input.dpc.thr);
//	printf("rsz_ss_config.input.gain = %d\n",rsz_ss_config.input.gain);
//	printf("rsz_ss_config.input.clip = %d\n",rsz_ss_config.input.clip);
	printf("rsz_ss_config.input.align_sync = %d\n",rsz_ss_config.input.align_sync);
	printf("rsz_ss_config.input.rsz_start = %d\n",rsz_ss_config.input.rsz_start);
	printf("rsz_ss_config.input.pix_fmt = %d\n",rsz_ss_config.input.pix_fmt);
//	printf("rsz_ss_config.input.pix_order = %d\n",rsz_ss_config.input.pix_order);
//	printf("rsz_ss_config.input.colp_olop = %d\n",rsz_ss_config.input.colp_olop);
//	printf("rsz_ss_config.input.colp_olep = %d\n",rsz_ss_config.input.colp_olep);
//	printf("rsz_ss_config.input.colp_elop = %d\n",rsz_ss_config.input.colp_elop);
//	printf("rsz_ss_config.input.colp_elep = %d\n",rsz_ss_config.input.colp_elep);

	printf("rsz_ss_config.output1.enable = %d\n",rsz_ss_config.output1.enable);
	printf("rsz_ss_config.output1.pix_fmt = %d\n",rsz_ss_config.output1.pix_fmt);
	printf("rsz_ss_config.output1.h_flip = %d\n",rsz_ss_config.output1.h_flip);
	printf("rsz_ss_config.output1.v_flip = %d\n",rsz_ss_config.output1.v_flip);
	printf("rsz_ss_config.output1.width = %d\n",rsz_ss_config.output1.width);
	printf("rsz_ss_config.output1.height = %d\n",rsz_ss_config.output1.height);
	printf("rsz_ss_config.output1.vst_y = %d\n",rsz_ss_config.output1.vst_y);
	printf("rsz_ss_config.output1.vst_c = %d\n",rsz_ss_config.output1.vst_c);
	printf("rsz_ss_config.output1.v_lpf_int_y = %d\n",rsz_ss_config.output1.v_lpf_int_y);
	printf("rsz_ss_config.output1.v_lpf_int_c = %d\n",rsz_ss_config.output1.v_lpf_int_c);
//	printf("rsz_ss_config.output1.lpf_user_val = %d\n",rsz_ss_config.output1.lpf_user_val);
	printf("rsz_ss_config.output2.enable = %d\n",rsz_ss_config.output2.enable);
	printf("rsz_ss_config.output2.pix_fmt = %d\n",rsz_ss_config.output2.pix_fmt);
	printf("rsz_ss_config.output2.width = %d\n",rsz_ss_config.output2.width);
	printf("rsz_ss_config.output2.height = %d\n",rsz_ss_config.output2.height);
	
#endif
	// in the chain mode only output configurations are valid
	// input params are set at the previewer
	rsz_ss_config.input.image_width = INPUT_WIDTH;
	rsz_ss_config.input.image_height = INPUT_HEIGHT;
	rsz_ss_config.input.ppln = rsz_ss_config.input.image_width + 8;
	rsz_ss_config.input.lpfr = rsz_ss_config.input.image_height + 10;
	rsz_ss_config.input.line_length = 0;
	rsz_ss_config.input.pix_fmt = IPIPE_420SP_Y;
	rsz_ss_config.output1.pix_fmt = IPIPE_YUV420SP;
	rsz_ss_config.output1.enable = 1;
	rsz_ss_config.output1.width = OUTPUT_WIDTH;
	rsz_ss_config.output1.height = OUTPUT_HEIGHT;
	rsz_ss_config.output2.enable = 0;

	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration for single shot mode\n");
		fclose(inp_f);
		fclose(outp_f);
		close(resizer_fd);
		exit(1);
	}
	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);

	// read again and verify
	if (ioctl(resizer_fd, RSZ_G_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in getting configuration from driver\n");
		fclose(inp_f);
		fclose(outp_f);
		close(resizer_fd);
		exit(1);
	}
	

	//Request buffer
	req_buf.buf_type = IMP_BUF_IN;
	req_buf.size = (INPUT_WIDTH * INPUT_HEIGHT * BYTESPERLINE);
	req_buf.count = 1;
	
	if (ioctl(resizer_fd, RSZ_REQBUF, &req_buf) < 0) {
		perror("Error in PREV_REQBUF for IMP_BUF_IN\n");
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	} 
		
	for (i = 0; i < 1; i++) {
		buf_in[i].index = i;
		buf_in[i].buf_type = IMP_BUF_IN;
		if (ioctl(resizer_fd, RSZ_QUERYBUF, &buf_in[i]) < 0) {
			perror("Error in PREV_QUERYBUF for IMP_BUF_IN\n");
			close(resizer_fd);
			fclose(inp_f);
			fclose(outp_f);
			exit(1);
		}
	}
	printf("PREV_QUERYBUF successful for IMP_BUF_IN\n");
	req_buf.buf_type = IMP_BUF_OUT1;
	req_buf.size = (INPUT_WIDTH*INPUT_HEIGHT*BYTESPERLINE);
	req_buf.count = 1;
	
	if (ioctl(resizer_fd, RSZ_REQBUF, &req_buf) < 0) {
		perror("Error in PREV_REQBUF for IMP_BUF_OUT1\n");
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	}
	for (i = 0; i < 1; i++) {
		buf_out1[i].index = i;
		buf_out1[i].buf_type = IMP_BUF_OUT1;
		if (ioctl(resizer_fd, RSZ_QUERYBUF, &buf_out1[i]) < 0) {
			perror("Error in PREV_QUERYBUF for IMP_BUF_OUT1\n");
			close(resizer_fd);
			fclose(inp_f);
			fclose(outp_f);
			exit(1);
		}
	}
	printf("PREV_QUERYBUF successful for IMP_BUF_OUT1\n");
	input_buffer = mmap(
			NULL,buf_in[0].size, 
			PROT_READ|PROT_WRITE, 
			MAP_SHARED, 
			resizer_fd, 
			buf_in[0].offset);
	
	printf("input offset = %x \n", buf_in[0].offset);

	if (input_buffer == MAP_FAILED) {
		perror("Error in MMAP\n");
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	}

	output_buffer = mmap(
			NULL,buf_out1[0].size, 
			PROT_READ|PROT_WRITE, 
			MAP_SHARED, 
			resizer_fd, 
			buf_out1[0].offset);
	printf("output offset = %x\n", buf_out1[0].offset);
	if (output_buffer == MAP_FAILED) {
		perror("Error in MMAP\n");
		munmap(input_buffer, buf_in[0].size);
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	}
#if 0
	if (ioctl(resizer_fd, RSZ_DUMP_HW_CONFIG, &level) < 0) {
		perror("Error in debug ioctl\n");
		munmap(input_buffer, buf_in[0].size);
		munmap(output_buffer, buf_out1[0].size);
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	} 

#endif
	bzero(&convert,sizeof(convert));
	memcpy(input_buffer,in_buf,(INPUT_WIDTH*INPUT_HEIGHT*BYTESPERLINE));
	convert.in_buff.buf_type = IMP_BUF_IN;
	convert.in_buff.index = 0;
	convert.in_buff.offset = buf_in[0].offset;
	convert.in_buff.size = rsz_ss_config.input.image_width*rsz_ss_config.input.image_height*BYTESPERLINE_Y;
	convert.out_buff1.buf_type = IMP_BUF_OUT1;
	convert.out_buff1.index = 0;
	convert.out_buff1.offset = buf_out1[0].offset;
	convert.out_buff1.size = rsz_ss_config.output1.width*rsz_ss_config.output1.height*BYTESPERLINE_Y;

//Resize Y first
	if (ioctl(resizer_fd, RSZ_RESIZE, &convert) < 0) {
		perror("Error in doing preview\n");
		munmap(input_buffer, buf_in[0].size);
		munmap(output_buffer, buf_out1[0].size);
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	} 
	printf("\r\n Y resizing complete. Now doing UV resizing");
#if 1
	convert.in_buff.offset = buf_in[0].offset + (rsz_ss_config.input.image_width*rsz_ss_config.input.image_height*BYTESPERLINE_Y);	
	convert.out_buff1.offset = buf_out1[0].offset+(rsz_ss_config.output1.width*rsz_ss_config.output1.height*BYTESPERLINE_Y);
	
	rsz_ss_config.input.image_width = INPUT_WIDTH;
	rsz_ss_config.input.image_height = INPUT_HEIGHT/2;
	rsz_ss_config.input.ppln = rsz_ss_config.input.image_width + 8;
	rsz_ss_config.input.lpfr = rsz_ss_config.input.image_height + 10;
	rsz_ss_config.input.line_length = 0;
	rsz_ss_config.input.pix_fmt = IPIPE_420SP_C;
	rsz_ss_config.output1.pix_fmt = IPIPE_YUV420SP;
	rsz_ss_config.output1.enable = 1;
	rsz_ss_config.output1.width = OUTPUT_WIDTH;
	rsz_ss_config.output1.height = OUTPUT_HEIGHT;
	rsz_ss_config.output2.enable = 0;

	rsz_chan_config.oper_mode = IMP_MODE_SINGLE_SHOT;
	rsz_chan_config.chain = 0;
	rsz_chan_config.len = sizeof(struct rsz_single_shot_config);
	if (ioctl(resizer_fd, RSZ_S_CONFIG, &rsz_chan_config) < 0) {
		perror("Error in setting default configuration for single shot mode\n");
		fclose(inp_f);
		fclose(outp_f);
		close(resizer_fd);
		exit(1);
	}

	//Configure for UV and then resize UV
	convert.in_buff.size = rsz_ss_config.input.image_width*rsz_ss_config.input.image_height;
	convert.out_buff1.size = rsz_ss_config.output1.width*rsz_ss_config.output1.height/2;

	if (ioctl(resizer_fd, RSZ_RESIZE, &convert) < 0) {
		perror("Error in doing preview\n");
		munmap(input_buffer, buf_in[0].size);
		munmap(output_buffer, buf_out1[0].size);
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	} 

	size = (OUTPUT_WIDTH * OUTPUT_HEIGHT*BYTESPERLINE );
#else
	size = (OUTPUT_WIDTH * OUTPUT_HEIGHT);
#endif
	printf("size = %d\n", size);

	if (fwrite(output_buffer,1,size,outp_f) != (
			size)) {
		perror("Error in doing resize\n");
		munmap(input_buffer, buf_in[0].size);
		munmap(output_buffer, buf_out1[0].size);
		close(resizer_fd);
		fclose(inp_f);
		fclose(outp_f);
		exit(1);
	} 

	munmap(input_buffer, buf_in[0].size);
	munmap(output_buffer, buf_out1[0].size);
	if (!close(resizer_fd))
		printf("resizer closed successfully\n");
	else
		printf("Error in closing resizer\n");
	fclose(inp_f);
	fclose(outp_f);
	return 0;
}

