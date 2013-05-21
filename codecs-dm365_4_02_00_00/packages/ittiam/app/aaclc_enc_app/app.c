/*****************************************************************************/
/*                                                                           */
/*                          HE-AAC V2 Encoder                                */
/*                                                                           */
/*                   ITTIAM SYSTEMS PVT LTD, BANGALORE                       */
/*                          COPYRIGHT(C) 2008                                */
/*                                                                           */
/*  This program is proprietary to Ittiam Systems Pvt. Ltd. and is protected */
/*  under Indian Copyright Act as an unpublished work.Its use and disclosure */
/*  is  limited by  the terms and conditions of a license  agreement. It may */
/*  be copied or  otherwise reproduced or  disclosed  to persons outside the */
/*  licensee 's  organization  except  in  accordance  with  the  terms  and */
/*  conditions of  such an agreement. All  copies and reproductions shall be */
/*  the  property  of Ittiam Systems Pvt.  Ltd. and  must  bear  this notice */
/*  in its entirety.                                                         */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/*  File Name        : app.c                                                 */
/*                                                                           */
/*  Description      : Main processing function selects functions with ptrs  */
/*                                                                           */
/*  List of Functions: 1. ia_fread                                           */
/*                     2. wav_header_decode                                  */
/*                     3. print_usage                                        */
/*                     4. ia_aaclc_enc_set_config_param                 */
/*                     5. ia_display_id_message                              */
/*                     6. ia_aaclc_enc_main_process                     */
/*                     7. main                                               */
/*                                                                           */
/*  Issues / Problems: None                                                  */
/*                                                                           */
/*  Revision History :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        01 08 2006       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/* File includes                                                             */
/*****************************************************************************/
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*****************************************************************************/
/* Process select hash defines                                               */
/*****************************************************************************/
#define WAV_READER
#define DISPLAY_MESSAGE
#define USE_ITTIAM_ERROR_CODE
// #define DYNAMIC_PARAMS_USAGE
#ifndef WIN32
#define ARM_PROFILE
#endif

/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio1/audenc1.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#ifdef USE_ITTIAM_ERROR_CODE
/* This can be disabled to remove ittiam error code printing
and also the ittiam type definitions */
#include "ia_type_def.h"
#include "ia_error_standards.h"
#include "ia_error_handler.h"
#endif
#include "ieaacplusenc.h"
#include "eaacplusenc_ittiam.h"

#ifndef WIN32
FILE *fprofile;
#endif

/* prototypes of functions defined in ceapp.c: */
extern int   ceapp_init(void *params);/* initialize the ceapp module */
extern char *ceapp_allocContigBuf(    /* allocate physically contiguous */
								  int   bufSize,        /*   buffer of given size; description */
								  char *bufDescription  /*   is used only for print */
								  );
extern void  ceapp_freeContigBuf(    /* free the contiguous buffer */
								 char *buf,
								 int   bufSize
								 );
extern void  ceapp_exit();           /* exit the ceapp module */
/***********************/

extern Engine_Handle ceHandle;
extern AUDENC1_Handle encHandle;

/***********************/

#ifdef USE_ITTIAM_ERROR_CODE
VOID ia_aaclc_enc_error_handler_init();
VOID ia_testbench_error_handler_init();

extern ia_error_info_struct ia_testbench_error_info;
extern ia_error_info_struct ia_aaclc_enc_error_info;
#endif
/*****************************************************************************/
/* Constant hash defines                                                     */
/*****************************************************************************/
#define MAX_STACK_PROC 10
#define MAX_MEM_ALLOCS 100
#define IA_MAX_CMD_LINE_LENGTH 300
#define IA_MAX_ARGS 20
#define IA_SCREEN_WIDTH 80

#define PARAMFILE "aaclc_enc_params.txt"

/*****************************************************************************/
/* Multi channel Operation Related Declarations                              */
/*****************************************************************************/
#define FRONT_LEFT             0x1
#define FRONT_RIGHT            0x2
#define FRONT_CENTER           0x4
#define LOW_FREQUENCY          0x8
#define BACK_LEFT              0x10
#define BACK_RIGHT             0x20
#define FRONT_LEFT_OF_CENTER   0x40
#define FRONT_RIGHT_OF_CENTER  0x80
#define BACK_CENTER            0x100


/*****************************************************************************/
/* Error codes for the testbench                                             */
/*****************************************************************************/
#define IA_TESTBENCH_MFMAN_FATAL_MEM_ALLOC_FAILED				0xFFFF8000
#define IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED				0xFFFF8001
#define IA_TESTBENCH_FATAL_INVALID_WAV_HEADER    				0xFFFF8002
#define IA_ENHAACPLUSENC_CONFIG_FATAL_NUM_CHANNELS			0xFFFF8801
#define IA_ENHAACPLUSENC_CONFIG_FATAL_SAMP_FREQ				  0xFFFF8800

/*****************************************************************************/
/* Global variables                                                          */
/*****************************************************************************/
pVOID g_pv_arr_alloc_memory[MAX_MEM_ALLOCS];
WORD  g_w_malloc_count;
FILE *g_pf_inp=NULL, *g_pf_out=NULL;

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/
XDAS_Int32 allocate_audio_io_buffers(
									 XDM1_BufDesc *inBuf,			/* Input XDM buffer pointer */
									 XDM1_BufDesc *outBuf,		/* Output XDM buffer pointer */
									 XDAS_Int32 input_size,		/* Size of input buffer */
									 XDAS_Int32 output_size		/* Size of output buffer */
									 );

XDAS_Int32 free_audio_buffers(
							  XDM1_BufDesc *inBuf,			/* Input XDM buffer pointer */
							  XDM1_BufDesc *outBuf 		/* Output XDM buffer pointer */
							  );

/*****************************************************************************/
/* Global Profiling variables                                                */
/*****************************************************************************/
#ifdef ARM_PROFILE
#include <sys/time.h>
long long itGetMs(void)
{
    struct timeval t;
    long long currTime;

    if(gettimeofday(&t,NULL) == -1)
    {
		printf("Error in gettimeofday. It has returned -1. \n");
    }
    currTime = ((t.tv_sec *1000 *1000) + (t.tv_usec));
    return currTime;
}
#endif

#ifdef DYNAMIC_PARAMS_USAGE
	IAUDENC1_DynamicParams BASE_AUDENC1_DYNAMIC_PARAMS =
	{
		sizeof(IAUDENC1_DynamicParams),
		128000,             /* bitRate     			*/
		44100,              /* SampleRate  			*/
		IAUDIO_2_0,			/* channelMode 		    */
		XDAS_FALSE,			/* lfeFlag 			    */
		IAUDIO_DUALMONO_LR,	/* DualMonoMode		    */
		16,					/* InputBitsPerSample 	*/
	};
#endif

/*****************************************************************************
Allocate input/output buffers for audio codecs
*****************************************************************************/
XDAS_Int32 _allocate_xdm_buffer(
								XDM1_BufDesc *buffer,           /* XDM buffer ptr */
								XDAS_Int32 *buffer_sizes,       /* Pointer to Buffer size values */
								XDAS_Int32 numBufs              /* Number of buffers to be allocated */
								)
{
	XDAS_Int32 i;

	for(i=0; i<numBufs; i++)
	{
        buffer->descs[i].bufSize    = *buffer_sizes++;
//      buffer->descs[i].buf        = ceapp_allocContigBuf(buffer->descs[i].bufSize,  "io_data");
        buffer->descs[i].buf        = malloc(buffer->descs[i].bufSize);
        buffer->descs[i].accessMask = 0;
        if(buffer->descs[i].buf == NULL) return IALG_EFAIL;
	}

	buffer->numBufs = numBufs;
	return (IALG_EOK);
}

/****************************************************************************/
/* It allocates memory for audio buffers of XDMI interface                  */
/* Assumption: Single buffers are allocated for both input and output       */
/****************************************************************************/
XDAS_Int32 allocate_audio_io_buffers(
									 XDM1_BufDesc *inBuf,           /* Input XDM buffer pointer */
									 XDM1_BufDesc *outBuf,          /* Output XDM buffer pointer */
									 XDAS_Int32 input_size,         /* Size of input buffer 	*/
									 XDAS_Int32 output_size         /* Size of output buffer 	*/
									 )
{
	int result;

	result = _allocate_xdm_buffer(inBuf, &input_size, 1);
	if(result == IALG_EFAIL)
	{
		printf("App-> Error allocating input buffer!\n");
		return IALG_EFAIL;
	}

	result = _allocate_xdm_buffer(outBuf, &output_size, 1);

	if(result == IALG_EFAIL)
	{
		printf("App-> Error allocating output buffer!\n");
		return IALG_EFAIL;
	}
	return (IALG_EOK);
}

/****************************************************************************/
/* It frees memory for audio buffers of XDM interface			    		*/
/* Assumption: Single buffers are freed for both input and output	    	*/
/****************************************************************************/
XDAS_Int32 free_audio_buffers(
							  XDM1_BufDesc *inBuf,           /* Input XDM buffer pointer  */
							  XDM1_BufDesc *outBuf           /* Output XDM buffer pointer */
							  )
{

    //		ceapp_freeContigBuf(inBuf->descs[0].buf, inBuf->descs[0].bufSize);
    //		ceapp_freeContigBuf(outBuf->descs[0].buf, outBuf->descs[0].bufSize);

	free(inBuf->descs[0].buf);
	free(outBuf->descs[0].buf);

	return (IALG_EOK);
}



/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_fread                                                 */
/*                                                                           */
/*  Description   : read little endian data irrespective of the endiannness  */
/*                  of the data                                              */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : pVOID buffer[]              							 */
/*                  int size                                                 */
/*                  int nwords                                               */
/*                  FILE *fp                                                 */
/*                                                                           */
/*  Processing    : read little endian data irrespective of the endiannness  */
/*                  of the data                                              */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

int ia_fread(void *buf, int size, int bytes, FILE *fp)
{
	int bytes_read =  fread(buf, size, bytes, fp);
   	return (bytes_read);
}


/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_fwrite                                                */
/*                                                                           */
/*  Description   :  Write data in Little Endian format into the file        */
/*                                                                           */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : pVOID buffer[]              							 */
/*                  int size                                                 */
/*                  int nwords                                               */
/*                  FILE *fp                                                 */
/*                                                                           */
/*  Processing    : Calls fwrite which does the file write.                  */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/
int ia_fwrite(void* pb_buf, FILE* g_pf_out, WORD32 i_out_bytes)
{

		  fwrite(pb_buf, sizeof(char), i_out_bytes, g_pf_out);

		  return 1;
}


/*****************************************************************************/
/*                                                                           */
/*  Function name : wav_header_decode                                        */
/*                                                                           */
/*  Description   : Read wav header and write to config params               */
/*                                                                           */
/*  Inputs        : ia_wav_reader_state_struct *p_state (wav reader state)   */
/*                  WORD8 *inptr (header data)                               */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : Read  wav header                                         */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

#ifdef WAV_READER

WORD32 wav_header_decode(
                               FILE *in_file,
                               UWORD32 *n_channels,
                               UWORD32 *i_channel_mask,
                               UWORD32 *sample_rate,
                               UWORD32 *pcm_sz,
                               WORD32 *length)
{
  WORD8 wav_hdr[40 + 36];
  WORD8 data_start[4];
  WORD16 num_ch;
  UWORD32   f_samp;
  WORD16 output_format;
  WORD32 check, count = 0;
  FLAG wav_format_pcm = 0,wav_format_extensible = 0;
  UWORD16 cbSize = 0;

#ifdef USE_ITTIAM_ERROR_CODE
  ia_error_info_struct *p_proc_err_info = &ia_aaclc_enc_error_info;
#endif

  *i_channel_mask = 0;

  if(fread(wav_hdr, 1, 40, in_file) != 40)
    return 1;

  if(wav_hdr[0]  != 'R' && wav_hdr[1]  != 'I' && wav_hdr[2]  != 'F'
    && wav_hdr[3]  != 'F')
  {
    return 1;
  }



  if(wav_hdr[20] == 01 && wav_hdr[21] == 00)
  {
    wav_format_pcm = 1;
  }
  else if(wav_hdr[20] == ((WORD8)0xFE) && wav_hdr[21] == ((WORD8)0xFF))
  {
    wav_format_extensible = 1;
  }
  else
  {
    return 1;
  }


  num_ch = (WORD16)((UWORD8)wav_hdr[23] * 256 + (UWORD8)wav_hdr[22]);
  f_samp = ((UWORD8)wav_hdr[27] * 256 * 256 * 256);
  f_samp += ((UWORD8)wav_hdr[26] * 256 * 256);
  f_samp += ((UWORD8)wav_hdr[25] * 256);
  f_samp += ((UWORD8)wav_hdr[24]);

  output_format  = ((UWORD8)wav_hdr[35] * 256);
  output_format += ((UWORD8)wav_hdr[34]);

  *n_channels    = num_ch;
  *sample_rate   = f_samp;
  *pcm_sz = output_format;

#ifdef USE_ITTIAM_ERROR_CODE

  if(*pcm_sz != 16)
  {
    ia_error_handler(p_proc_err_info, (signed char *)"",
      IA_TESTBENCH_FATAL_INVALID_WAV_HEADER);
    return(0);
  }

  if((*sample_rate < 8000) || (*sample_rate > 96000))
  {
    ia_error_handler(p_proc_err_info, (signed char *)"",
      IA_ENHAACPLUSENC_CONFIG_FATAL_SAMP_FREQ);
  }

#endif

  if(wav_format_pcm)
  {
    data_start[0] = wav_hdr[36];
    data_start[1] = wav_hdr[37];
    data_start[2] = wav_hdr[38];
    data_start[3] = wav_hdr[39];
  }
  else if(wav_format_extensible)
  {
    cbSize |= ((UWORD8)wav_hdr[37] << 8);
    cbSize |= ((UWORD8)wav_hdr[36]);

    if(fread(&(wav_hdr[40]), 1, (UWORD16)(cbSize - 2 + 4), in_file)
      != (UWORD16)(cbSize - 2 + 4))
      return 1;

    *i_channel_mask = 0;
    *i_channel_mask	|= (UWORD8)wav_hdr[43] << 24;
    *i_channel_mask	|= (UWORD8)wav_hdr[42] << 16;
    *i_channel_mask	|= (UWORD8)wav_hdr[41] << 8;
    *i_channel_mask	|= (UWORD8)wav_hdr[40];


    data_start[0] = wav_hdr[40 + cbSize - 2 + 0];
    data_start[1] = wav_hdr[40 + cbSize - 2 + 1];
    data_start[2] = wav_hdr[40 + cbSize - 2 + 2];
    data_start[3] = wav_hdr[40 + cbSize - 2 + 3];

  }

  check = 1;
  while(check)
  {
    if( data_start[0] == 'd' && data_start[1] == 'a' &&
      data_start[2] == 't' &&  data_start[3] == 'a')
    {
      (fread(length,4,1,in_file));
      check = 0;
    }
    else
    {
      data_start[0] = data_start[1];
      data_start[1] = data_start[2];
      data_start[2] = data_start[3];
      (fread(&data_start[3],1,1,in_file));
    }
    count++;
    if(count > 40)
    {
      *length = 0xffffffff;
      return(1);

    }
  }
  return 0;
}
#endif /* WAV_READER */

/*****************************************************************************/
/*                                                                           */
/*  Function name : print_usage                                              */
/*                                                                           */
/*  Description   : Prints the executables usage                             */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : Prints usage with all options                            */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/
void print_usage()
{

  printf("\nUsage:\n");
  printf("\n<executable> -ifile:<inputfile> -ofile:<outputfile> [options]\n");
  printf("\n[options] can be,");
  printf("\n[-br:<bitrate in bps>]");
  printf("\n[-aac_only:<aac_only flag (0/1)>]");
  printf("\n[-ps_enable:<ps_enable flag (0/1)>]");
  printf("\n[-dual_mono:<dual_mono enable flag (0/1)>]");
  printf("\n[-downmix:<downmix enable flag (0/1)>]");
  printf("\n[-spc:<use_speech_config (0/1)>]");
  printf("\n[-adif:<use_adif_flag (0/1)>]");
  printf("\n[-adts:<use_adts_flag (0/1)>]");
  printf("\n[-nostprepro:<do_not_use_stereo_pre_process (0/1)>]");
  printf("\n[-quality:<quality_level (0/1/2)>]");
  printf("\n[-tns:<use_tns_flag (0/1)>]");
  printf("\n[-num_coup_chan:<number of coupling channels(0,1,2)>]");
  printf("\n[-writepce:<write program config element (0/1)>]");

#ifndef WAV_READER
  printf("\n[-pcmsz:<pcmwordsize>]");
  printf("\n[-chans:<num_chans>]");
  printf("\n[-fs:<sample_rate>]");
  printf("\n[-chan_mask:<channel mask value>]");
#endif
#ifdef WAV_READER
  printf("\n\nwhere, \n  <inputfile> is the input 16-bit WAV file name");
#else
  printf("\n\nwhere, \n  <inputfile> is the input PCM file name");
#endif
  printf("\n  <outputfile> is the output ADTS/ADIF file name");
  printf("\n  <bitrate> is the bit-rate in bits per second. Valid values are ");
  printf("\n    Plain AAC: 8000-576000 bps per channel");
  printf("\n    aacPlus: 16000-144000 bps per channel");
  printf("\n  <aac_only_flag> when equal to 1 encoder operates on Plain AAC.");
  printf("\n    Default is 1 in AAC-LC Build and 0 in HEAAC/v2 build.");
  printf("\n  <ps_enable flag 0 - ps will be disabled..1 - ps will be enabled)>]");
  printf("\n  <dual_mono enable flag 0 - Dual mono operation disabled..1 - dual mono operation enabled)>]");
  printf("\n  <dual_mono flag is applicable only in multichannel mode]");
  printf("\n  <downmix enable flag - applicable only for stereo>]");
  printf("\n  <use_speech_config> set to 1 for good encoding of speech file");
  printf("\n  <use_adif_flag> when set to 1 ADIF header generated.");
  printf("Default is 0");
  printf("\n  <use_adts_flag> when set to 1 ADTS header generated.");
  printf("Default is 1");
  printf("\n  Both <use_adif_flag> and <use_adts_flag> when set to 0 raw file generated.");
  printf("\n  <do_not_use_stereo_pre_process> when set to 1 no stereo pre-processing is used");
  printf("\n    is done. Default is 0");
  printf("\n  <quality_level> controls the quality of encoding.");
  printf("\n    Valid values of 0 to 2. Default is 2 (best quality).");
  printf("\n  <use_tns_flag> controls usage of TNS in encoding. Default 1.");
  printf("\n  <channel mask> sets the channel mask value of the input file.");
  printf("\n  <number of coupling channels> set the number of channel coupling elements present");
  printf("\n  <write program config element>when set pce is written in the bitstream.");

#ifndef WAV_READER
  printf("  <pcmwordsize> is the bits per sample info. Only 16 is valid");
  printf("\n  <num_chans> is the number of channels. Valid values are 1 & 2 for stereo build
             and 1 to 6 for multichannel builds");
  printf("\n  <sample_rate> is the sample rate of input. Valid values are ");
  printf("\n    Plain AAC: 8000-96000 Hz");
  printf("\n    HEAAC: 32000, 44100 & 48000 Hz \n");
#endif
}

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_aaclc_enc_set_config_param                       */
/*                                                                           */
/*  Description   : Set config parameters                                    */
/*                                                                           */
/*  Inputs        : pVOID p_ia_process_api_obj (process API obj)             */
/*                  WORD32 argc (Arguments count)                            */
/*                  char *argv[] (Argument strings)                          */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : Set config params inside API                             */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : IA_ERRORCODE error_value  (Error value)                  */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

WORD32 ia_aaclc_enc_set_config_param(ITTIAM_EAACPLUSENC_Params *params,
                                                WORD32 argc, pWORD8 argv[])
{

  LOOPIDX i;

  for(i = 0; i < argc; i++)
  {
    if(!strncmp((const char *)argv[i], "-help", 5))
    {
      print_usage();
    }

#ifndef WAV_READER
    /* samp freq */
    if(!strncmp((const char *)argv[i], "-fs:", 4))
    {
      char *pb_arg_val = (char *)argv[i] + 4;
      params->s_iaudenc_params.sampleRate = atoi(pb_arg_val);
    }
    /* Total Number of Channels */
    if(!strncmp((const char *)argv[i], "-chans:", 7))
    {
      char *pb_arg_val = (char *)argv[i] + 7;
      params->noChannels = atoi(pb_arg_val);
    }

    /* pcm word size */
    if(!strncmp((const char *)argv[i], "-pcmsz:", 7))
    {
      char *pb_arg_val = (char *)argv[i] + 7;
      params->s_iaudenc_params.inputBitsPerSample = atoi(pb_arg_val);
    }

    /* Channels Mask*/
    if(!strncmp((const char *)argv[i], "-chan_mask:", 11))
    {
      char *pb_arg_val = (char *)argv[i] + 11;
      params->i_channels_mask = atoi(pb_arg_val);

    }
#endif

    /* Number of coupling channels*/
    if(!strncmp((const char *)argv[i], "-num_coup_chan:", 15))
    {
      char *pb_arg_val = (char *)argv[i] + 15;
      params->i_num_coupling_chan = atoi(pb_arg_val);

    }
    /* Write PCE */
    if(!strncmp((const char *)argv[i], "-writepce:", 10))
    {
      char *pb_arg_val = (char *)argv[i] + 10;
      params->write_program_config_element = atoi(pb_arg_val);
    }



    /* Stream bit rate */
    if(!strncmp((const char *)argv[i], "-br:", 4))
    {
      char *pb_arg_val = (char *)argv[i] + 4;
      params->s_iaudenc_params.bitRate = atoi(pb_arg_val);

      fprintf(stdout,"Stream bit rate = %d kbps\n",
              (int)(params->s_iaudenc_params.bitRate/1000));
    }

    /* Don't use aacPLUS mode extensions */
    if(!strncmp((const char *)argv[i], "-aac_only:", 10))
    {
      char *pb_arg_val = (char *)argv[i] + 10;
      params->aacClassic = atoi(pb_arg_val);

    }
    /* PS Enable Flag */
    if(!strncmp((const char *)argv[i], "-ps_enable:", 11))
    {
      char *pb_arg_val = (char *)argv[i] + 11;
      params->psEnable = atoi(pb_arg_val);

    }
    /* Dual Mono Enable Flag */
    if(!strncmp((const char *)argv[i], "-dual_mono:", 11))
    {
      char *pb_arg_val = (char *)argv[i] + 11;
      params->dualMono = atoi(pb_arg_val);

    }
    /* Downmix Enable Flag */
    if(!strncmp((const char *)argv[i], "-downmix:", 9))
    {
      char *pb_arg_val = (char *)argv[i] + 9;
      params->downmix = atoi(pb_arg_val);
    }

    /* Speech config */
    if(!strncmp((const char *)argv[i], "-spc:", 5))
    {
      char *pb_arg_val = (char *)argv[i] + 5;
      params->useSpeechConfig = atoi(pb_arg_val);

    }

    /* Use ADTS */
    if(!strncmp((const char *)argv[i], "-adts:", 6))
    {
      char *pb_arg_val = (char *)argv[i] + 6;
      params->use_ADTS = atoi(pb_arg_val);
      if(params->use_ADTS == 1)
        params->use_ADIF = 0;

    }

    /* Use ADIF */
    if(!strncmp((const char *)argv[i], "-adif:", 6))
    {
      char *pb_arg_val = (char *)argv[i] + 6;
      params->use_ADIF = atoi(pb_arg_val);
      if(params->use_ADIF == 1)
        params->use_ADTS = 0;
    }

    /* Use stereo preprocessing */
    if(!strncmp((const char *)argv[i], "-nostprepro:", 12))
    {
      char *pb_arg_val = (char *)argv[i] + 12;
      params->fNoStereoPreprocessing = atoi(pb_arg_val);
    }

    /* Quality level */
    if(!strncmp((const char *)argv[i], "-quality:", 9))
    {
      char *pb_arg_val = (char *)argv[i] + 9;
      params->invQuant = atoi(pb_arg_val);
    }

    /* Use TNS */
    if(!strncmp((const char *)argv[i], "-tns:", 5))
    {
      char *pb_arg_val = (char *)argv[i] + 5;
      params->useTns = atoi(pb_arg_val);
    }

    /*Use full bandwidth*/
    if(!strncmp((const char *)argv[i], "-full_bandwidth:", 16))
    {
      char *pb_arg_val = (char *)argv[i] + 16;
      params->full_bandwidth = atoi(pb_arg_val);
    }

  }
  return 0;
}

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_aaclc_enc_get_channel_mode                       */
/*                                                                           */
/*  Description   : Fills channel mode and lfe flag input params             */
/*                                                                           */
/*  Inputs        : ITTIAM_EAACPLUSENC_Params *params                        */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : none                                                     */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Tejaswi/Vishal        Created                     */
/*                                                                           */
/*****************************************************************************/
void ia_aaclc_enc_get_channel_mode(ITTIAM_EAACPLUSENC_Params *params)
{

#ifdef USE_ITTIAM_ERROR_CODE
  ia_error_info_struct *p_proc_err_info = &ia_aaclc_enc_error_info;
#endif

  if(params->i_channels_mask == 0)
  {
    if(params->noChannels == 1)
    {
      params->s_iaudenc_params.channelMode = IAUDIO_1_0; /* mono file */
    }
    else if((params->noChannels == 2) && (params->dualMono == 0))
    {
      params->s_iaudenc_params.channelMode = IAUDIO_2_0; /* stereo file */
    }
    else if((params->noChannels == 2) && (params->dualMono == 1))
    {
      params->s_iaudenc_params.channelMode = IAUDIO_11_0; /* dual mono operation */
    }
    else
    {
#ifdef USE_ITTIAM_ERROR_CODE
        ia_error_handler(p_proc_err_info, (signed char *)"",IA_ENHAACPLUSENC_CONFIG_FATAL_NUM_CHANNELS);
#endif
    }

  }/*channel mask*/

  else
  {
    switch(params->i_channels_mask)
    {
    case(FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_3_0;
        /* Left, Right, Center */
        break;
      }
    case(FRONT_LEFT | FRONT_RIGHT | BACK_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_2_1;
        /* Left, Right, SurC */
        break;
      }
      case(FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER
        | BACK_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_3_1;
        /* Left, Right, Center, SurC */
        break;
      }
      case(FRONT_LEFT | FRONT_RIGHT | FRONT_LEFT_OF_CENTER
        | FRONT_RIGHT_OF_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_2_2;
        /* Left, Right, SurL, SurR */
        break;
      }

      case(FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER
        | FRONT_LEFT_OF_CENTER | FRONT_RIGHT_OF_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_3_2;
        /* Left, Right, Center, SurL, SurR */
        break;
      }
      case(FRONT_LEFT | FRONT_RIGHT | FRONT_LEFT_OF_CENTER
        | FRONT_RIGHT_OF_CENTER | BACK_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_2_3;
        /* Left, Right, SurL, SurR, surC */
        break;
      }
      case(FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER
        | FRONT_LEFT_OF_CENTER | FRONT_RIGHT_OF_CENTER | BACK_CENTER):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_3_3;
        /* Left, Right, Center, SurL, SurR, surC */
        break;
      }
      case(FRONT_LEFT | FRONT_RIGHT | FRONT_CENTER
        | FRONT_LEFT_OF_CENTER | FRONT_RIGHT_OF_CENTER | BACK_LEFT
        | BACK_RIGHT):
      {
        params->s_iaudenc_params.channelMode = IAUDIO_3_4;
        /* Left, Right, Center, SurL, SurR, sideL, sideR */
        break;
      }
    default:
      {
        params->s_iaudenc_params.channelMode = -1;
        /* channel mode cannot be specified with the given set of enumerated values */
        /* channels_mask and noChannels fields in the params will be used
        for all channel mode related calculations*/
      }

    }/* switch ends */
  }/* else ends */

  /* check whether LFE is present or not */
  if((params->i_channels_mask) & LOW_FREQUENCY)
  {
    params->s_iaudenc_params.lfeFlag = XDAS_TRUE;
  }
  else
  {
    params->s_iaudenc_params.lfeFlag = XDAS_FALSE;
  }

}

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_display_id_message                                    */
/*                                                                           */
/*  Description   : Display the ID message of the process                    */
/*                                                                           */
/*  Inputs        : WORD8 lib_name[] (library name)                          */
/*                  WORD8 lib_version[] (library version)                    */
/*                  WORD8 api_version[] (API version)                        */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : Display all the information about the process            */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Tejaswi/Vishal        Created                     */
/*                                                                           */
/*****************************************************************************/
#ifdef DISPLAY_MESSAGE

XDAS_Void ia_display_id_message(XDAS_Int8 lib_info[])
{
	XDAS_Int8 str[4][IA_SCREEN_WIDTH] = {
		"ITTIAM SYSTEMS PVT LTD, BANGALORE\n",
			"http:\\\\www.ittiam.com\n",
			"",
			""
	};
	XDAS_Int8 spaces[IA_SCREEN_WIDTH/2 + 1];
	XDAS_Int32 i, spclen;

	strcpy(str[2], lib_info);
	strcat(str[2], "\n");
	strcat(str[4-1], "\n");

	for(i = 0; i < IA_SCREEN_WIDTH/2 + 1; i++)
	{
		spaces[i] = ' ';
	}

	for(i = 0; i < 4; i++)
	{
		spclen = IA_SCREEN_WIDTH/2 - strlen(str[i])/2;
		spaces[spclen] = '\0';
		printf(spaces);
		spaces[spclen] = ' ';
		printf(str[i]);
	}
}
#endif /* DISPLAY_MESSAGE */


/*****************************************************************************/
/*                                                                           */
/*  Function name : ceapp_encodeBuf                                          */
/*                                                                           */
/*  Description   : The main process function which makes the API function   */
/*                  calls.                                                   */
/*                                                                           */
/*  Inputs        : argc,argv                                                */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : Makes the calls to all API functions                     */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : none                                                     */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Tejaswi/Vishal        Created                     */
/*                                                                           */
/*****************************************************************************/

XDAS_Int32 ceapp_encodeBuf(
						   XDAS_Int32 argc,
						   XDAS_Int8 *argv[]
						   )
{
    ITTIAM_EAACPLUSENC_Params params;
	IAUDENC1_DynamicParams dynParams;
	ITTIAM_EAACPLUSENC_InArgs inArgs;
	ITTIAM_EAACPLUSENC_OutArgs outArgs;
	ITTIAM_EAACPLUSENC_Status	status;
	XDM1_BufDesc inBuf, outBuf;

	XDAS_Int32 error_code = IALG_EOK;
	XDAS_Int32 error = -1;
	XDAS_Int32 input_size, output_size;
	XDAS_Int32 i_total_length = 0;
	XDAS_Int32 frame_count = 0;
	XDAS_Int32 result = IALG_EFAIL;

#ifdef ARM_PROFILE
	XDAS_Int32 ctimerLow,tempLow,peak_frame=0;
	XDAS_Int32 PeakCycles = 0;
	float AvgCycles=0.0f;
	float PeakMCPS, AvgMCPS;
#endif

#ifdef USE_ITTIAM_ERROR_CODE
  /*****************************************************************************/
  /* The process error info structure */
  /*****************************************************************************/
	ia_error_info_struct *p_proc_err_info;

  /*****************************************************************************/
  /* The error init function */
  /*****************************************************************************/
	VOID (*p_error_init)();

	p_error_init = ia_aaclc_enc_error_handler_init;
	p_proc_err_info = &ia_aaclc_enc_error_info;

  /*****************************************************************************/
  /* Initialize the error handler  */
  /*****************************************************************************/
	(*p_error_init)();
#endif

	params.s_iaudenc_params.size = sizeof(params);
	dynParams.size = sizeof(dynParams);
	status.s_iaudenc_status.size = sizeof(status);
	inArgs.s_iaudenc_in_args.size = sizeof(inArgs);
	outArgs.s_iaudenc_out_args.size = sizeof(outArgs);

  /*****************************************************************************/
  /* Default setting of Params Structure */
  /*****************************************************************************/
	params = EAACPLUSENCODER_ITTIAM_PARAMS;

	status.s_iaudenc_status.data.buf        = NULL;
	status.s_iaudenc_status.data.bufSize    = 0;
	status.s_iaudenc_status.data.accessMask = 0;

	inArgs.s_iaudenc_in_args.ancData.buf        = NULL;
	inArgs.s_iaudenc_in_args.ancData.bufSize    = 0;
	inArgs.s_iaudenc_in_args.ancData.accessMask = 0;

  /*****************************************************************************/
  /* Initialize the params Structure as per user settings*/
  /*****************************************************************************/
    error_code = ia_aaclc_enc_set_config_param(&params, argc, argv);

#ifdef WAV_READER
  /*****************************************************************************/
  /* Initialize the params Structure as per the contents of wav header*/
  /*****************************************************************************/
	if(wav_header_decode(g_pf_inp, (UWORD32*)&params.noChannels, (UWORD32*)&params.i_channels_mask,
	   (UWORD32*)&params.s_iaudenc_params.sampleRate,
	   (UWORD32*)&params.s_iaudenc_params.inputBitsPerSample, (WORD32*)&i_total_length) == 1)
		{
			fprintf(stdout,"Unable to Read Input WAV File\n");
			return(0);
		}
#else
	// Code to find out the file size

	fseek(g_pf_inp, 0L, SEEK_END);	// seek to end of file

	i_total_length = ftell(g_pf_inp); // get current file pointer

	fseek(g_pf_inp, 0L, SEEK_SET); // seek back to beginning of file


#endif

  /*****************************************************************************/
  /* Fill channel mode and lfe_flag input params                               */
  /*****************************************************************************/
    ia_aaclc_enc_get_channel_mode(&params);

  /*****************************************************************************/
  /* Create instance handle */
  /*****************************************************************************/

	error = ceapp_init(&params);
    if (error != 0) {
		printf("Error in initialisation");
        return(0);
    }

	if (encHandle == NULL)
	{
		printf("Error in initialisation");
        return(0);
	}


  /*****************************************************************************/
  /* Get input and output buffer sizes */
  /*****************************************************************************/
	error = AUDENC1_control(encHandle, XDM_GETSTATUS, &dynParams,
	                        (IAUDENC1_Status *)&status);

	if (error != AUDENC1_EOK) {
	 printf("CEapp-> Audio Encoder control FAILED, error = %d\n", (int)error);
		ceapp_exit();
		return(0);
	}

	input_size  = status.s_iaudenc_status.bufInfo.minInBufSize[0];
	output_size = status.s_iaudenc_status.bufInfo.minOutBufSize[0];

        printf("CEapp-> Input Buffer size = %d\n", (int)input_size);
        printf("CEapp-> Output Buffer size = %d\n", (int)output_size);

  /*****************************************************************************/
  /* Allocate input and output buffers */
  /*****************************************************************************/
	result = allocate_audio_io_buffers(&inBuf, &outBuf, input_size, output_size);

	if(IALG_EOK != result)
	{
		printf("Error in allocating the buffers\n");
		ceapp_exit();
		return 0;
	}

  /*****************************************************************************/
  /* Get version string */
  /*****************************************************************************/
#ifdef DISPLAY_MESSAGE
        status.s_iaudenc_status.data.buf        = outBuf.descs[0].buf;
        status.s_iaudenc_status.data.bufSize    = 64;
        status.s_iaudenc_status.data.accessMask = 0;

        error = AUDENC1_control(encHandle, XDM_GETVERSION, &dynParams,
	                        (IAUDENC1_Status *)&status);

        if (error != IAUDENC1_EOK)
        {
		printf("Error in XDM_GETVERSION");
		free_audio_buffers(&inBuf, &outBuf);
		ceapp_exit();
		return(0);
        }
        ia_display_id_message((XDAS_Int8 *)status.s_iaudenc_status.data.buf);
#endif



	if(encHandle != NULL)
	{
  /*****************************************************************************/
  /* Start Processing Input Data */
  /*****************************************************************************/
		XDAS_Int8 *inputBuffer = inBuf.descs[0].buf;
		XDAS_Int32 bytesConsumed = input_size;

		bytesConsumed = input_size;

		do
		{
			XDAS_Int32 packetLength = 0;
			XDAS_Int32 i_out_bytes;

			if(bytesConsumed > i_total_length )
			{
				// when bytes consumed is more than bytes left, then refill with the leftover and call FLUSH
				packetLength = i_total_length;

				error = AUDENC1_control(encHandle, XDM_FLUSH, &dynParams, (IAUDENC1_Status *)&status);

				if (error != AUDENC1_EOK)
				{
					printf("CEapp-> Audio Encoder control FAILED, error status = %d\n", (int)error);
					free_audio_buffers(&inBuf, &outBuf);
					ceapp_exit();
					return(0);
				}
			}
			else
			{
				packetLength = bytesConsumed;
			}

			ia_fread(inputBuffer, sizeof(WORD8),packetLength, g_pf_inp);
			i_total_length -= packetLength;

  /*****************************************************************************/
  /* Sample Code illustrating the use of Dynamic Params - only bitrate allowed */
  /*****************************************************************************/
#ifdef DYNAMIC_PARAMS_USAGE
		if(frame_count==100)
		{
			dynParams = BASE_AUDENC1_DYNAMIC_PARAMS;
			dynParams.bitRate = 96000;

			error = AUDENC1_control(encHandle,XDM_SETPARAMS, &dynParams,
				(IAUDENC1_Status *) &status);

			if (error != IALG_EOK)
			{
				printf("Error in XDM_SETPARAMS\n");
				free_audio_buffers(&inBuf, &outBuf);
				ceapp_exit();
				return(0);
			}
		}

#endif

  /*****************************************************************************/
  /* Print frame number */
  /*****************************************************************************/
#ifndef ARM_PROFILE
			frame_count++;
			fprintf(stdout,"[%d]\r ",(int)frame_count); fflush(stdout);
#endif

	  	inArgs.s_iaudenc_in_args.numInSamples = (packetLength/params.noChannels/(sizeof(XDAS_Int16)));
		outArgs.i_ittiam_err_code = 0;
		outArgs.s_iaudenc_out_args.extendedError = 0;



#ifdef ARM_PROFILE
			tempLow = itGetMs();
#endif



  /*****************************************************************************/
  /* Perform Encoding of frame data */
  /*****************************************************************************/
			error = AUDENC1_process(encHandle, &inBuf, &outBuf,
				(IAUDENC1_InArgs *)&inArgs, (IAUDENC1_OutArgs *)&outArgs);

#ifdef ARM_PROFILE
#define 	PROCESSOR_SPEED  297 // MHz
			ctimerLow = itGetMs();
			tempLow = (ctimerLow - tempLow) ;
			if(tempLow > PeakCycles)
			{
				PeakCycles = tempLow;
				peak_frame = frame_count;
			}
			AvgCycles += tempLow;
			frame_count++;
			printf("Frame = %d\r",(int)frame_count);
			fprintf(fprofile,"Frame = %d",(int)frame_count);
			fprintf(fprofile,"\tMCPS = %f\n", ((float)(tempLow) * params.s_iaudenc_params.sampleRate * (PROCESSOR_SPEED )/(1024 * (float)(params.aacClassic?1:2))/1000000));
			fflush(stdout);
#endif


			if (error != AUDENC1_EOK) {
				printf("CEapp-> AUDENC1_process() failed, error status=%d\n", (int)error);
				free_audio_buffers(&inBuf, &outBuf);
				ceapp_exit();
				return(0);
			}


	   		bytesConsumed = ((outArgs.s_iaudenc_out_args.numInSamples)* (params.noChannels) * (sizeof(XDAS_Int16)));

			i_out_bytes = outArgs.s_iaudenc_out_args.bytesGenerated;


#ifdef USE_ITTIAM_ERROR_CODE
			_IA_HANDLE_ERROR(p_proc_err_info, (pWORD8)"", outArgs.i_ittiam_err_code);
#endif

			if( XDM_ISFATALERROR(outArgs.s_iaudenc_out_args.extendedError))
			{
				printf("Algorithm has encountered fatal error\n");
				free_audio_buffers(&inBuf, &outBuf);
				ceapp_exit();
				return(0);
			}

			if( outArgs.i_ittiam_err_code)
			{
#ifdef USE_ITTIAM_ERROR_CODE
				ia_error_handler(p_proc_err_info, (signed char *)"", outArgs.i_ittiam_err_code);
#endif
				if(outArgs.i_ittiam_err_code < 0)
				{
					free_audio_buffers(&inBuf, &outBuf);
					ceapp_exit();
					return(0);
				}
			}

			ia_fwrite(outBuf.descs[0].buf, g_pf_out, i_out_bytes);

	 }
	 while(!(outArgs.i_exec_done));

	}

#ifdef ARM_PROFILE
    PeakMCPS = (float)PeakCycles * params.s_iaudenc_params.sampleRate * (PROCESSOR_SPEED)/(1024 * (float)(params.aacClassic?1:2))/1000000;
    AvgMCPS = (float)AvgCycles/frame_count * params.s_iaudenc_params.sampleRate * (PROCESSOR_SPEED)/(1024 * (float)(params.aacClassic?1:2))/1000000;
    printf("Peak:%f\tAvg:%f\n",PeakMCPS,AvgMCPS);
    printf("Peak_Frame = %d\n",(int)(peak_frame+1));
    fprintf(fprofile,"Peak:%f\tAvg:%f\n",PeakMCPS,AvgMCPS);
    fprintf(fprofile,"Peak_Frame = %d\n",(int)peak_frame+1);
#endif

   /*****************************************************************************/
   /* Free all the resources */
   /*****************************************************************************/
	free_audio_buffers(&inBuf, &outBuf);
	ceapp_exit();
    return(0);

}

/*****************************************************************************/
/*                                                                           */
/*  Function Name : main                                                     */
/*                                                                           */
/*  Description   : Main function                                            */
/*                                                                           */
/*  Inputs        : None                                                     */
/*                                                                           */
/*  Globals       : None                                                     */
/*                                                                           */
/*  Processing    : Parse the parameter file and run the main process        */
/*                                                                           */
/*  Outputs       : None                                                     */
/*                                                                           */
/*  Returns       : 0 on success, -1 on error                                */
/*                                                                           */
/*  Issues        : None                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        04 09 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

int main(int argc, char **argv)
{
	FILE *param_file_id = NULL;

	WORD8 curr_cmd[IA_MAX_CMD_LINE_LENGTH];
	WORD32 fargc, curpos;
	WORD32 processcmd = 0;

	WORD8 fargv[IA_MAX_ARGS][IA_MAX_CMD_LINE_LENGTH];

	pWORD8 pargv[IA_MAX_ARGS];

	WORD8 pb_input_file_path[IA_MAX_CMD_LINE_LENGTH] = "";
	WORD8 pb_output_file_path[IA_MAX_CMD_LINE_LENGTH] = "";
#ifdef ARM_PROFILE

    fprofile = fopen ("profile.txt","wt");

	if(fprofile == NULL)
	{
		printf("Unable to open profile file\n");
		exit(0);
	}

#endif
#ifdef USE_ITTIAM_ERROR_CODE
	ia_testbench_error_handler_init();
#endif

	/* initialize Codec Engine runtime first */
	CERuntime_init();

	if(argc == 1)
	{
		param_file_id = fopen(PARAMFILE, "r");
		if(param_file_id == NULL)
		{
			print_usage();
		    return 0;
		}

		/* Process one line at a time */
		while(fgets((char *)curr_cmd, IA_MAX_CMD_LINE_LENGTH, param_file_id))
		{
			curpos = 0;
			fargc = 0;
			/* if it is not a param_file command and if */
			/* CLP processing is not enabled */
			if(curr_cmd[0] != '@' && !processcmd)
			{	/* skip it */
				continue;
			}
			while(sscanf((char *)curr_cmd + curpos, "%s", fargv[fargc]) != EOF)
			{
				if(fargv[0][0]=='/' && fargv[0][1]=='/')
					break;
				if(strcmp((const char *)fargv[0], "@echo") == 0)
					break;
				if(strcmp((const char *)fargv[fargc], "@New_line") == 0)
				{
					fgets((char *)curr_cmd + curpos, IA_MAX_CMD_LINE_LENGTH,
						param_file_id);
					continue;
				}
				curpos += strlen((const char *)fargv[fargc]);
				while(*(curr_cmd + curpos)==' ' || *(curr_cmd + curpos)=='\t')
					curpos++;
				fargc++;
			}

			if(fargc < 1)	/* for blank lines etc. */
				continue;

			if(strcmp((const char *)fargv[0], "@Output_path") == 0)
			{
				if(fargc > 1) strcpy((char *)pb_output_file_path, (const char *)fargv[1]);
				else strcpy((char *)pb_output_file_path, "");
				continue;
			}

			if(strcmp((const char *)fargv[0], "@Input_path") == 0)
			{
				if(fargc > 1) strcpy((char *)pb_input_file_path, (const char *)fargv[1]);
				else strcpy((char *)pb_input_file_path, "");
				continue;
			}

			if(strcmp((const char *)fargv[0], "@Start") == 0)
			{
				processcmd = 1;
				continue;
			}

			if(strcmp((const char *)fargv[0], "@Stop") == 0)
			{
				processcmd = 0;
				continue;
			}

			/* otherwise if this a normal command and its enabled for execution */
			if(processcmd)
			{
				int i;
				int err_code = 0;

				int file_count = 0;
				for(i = 0; i < fargc; i++)
				{
					printf("%s ", fargv[i]);
					pargv[i] = fargv[i];

					if(!strncmp((const char *)fargv[i], "-ifile:", 7))
					{
						pWORD8 pb_arg_val = fargv[i] + 7;
						WORD8 pb_input_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

						strcat((char *)pb_input_file_name, (const char *)pb_input_file_path);
						strcat((char *)pb_input_file_name, (const char *)pb_arg_val);

						g_pf_inp = NULL;
						g_pf_inp = fopen((const char *)pb_input_file_name, "rb");
						if(g_pf_inp == NULL)
						{
#ifdef USE_ITTIAM_ERROR_CODE
							err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
							ia_error_handler(&ia_testbench_error_info,
								(pWORD8)"Input File", err_code);
#endif
						}
						file_count++;
					}

					if(!strncmp((const char *)fargv[i], "-ofile:", 7))
					{
						pWORD8 pb_arg_val = fargv[i] + 7;
						WORD8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

						strcat((char *)pb_output_file_name, (const char *)pb_output_file_path);
						strcat((char *)pb_output_file_name, (const char *)pb_arg_val);

						g_pf_out = NULL;
						g_pf_out = fopen((const char *)pb_output_file_name, "wb");
						if(g_pf_out == NULL)
						{
#ifdef USE_ITTIAM_ERROR_CODE
							err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
							ia_error_handler(&ia_testbench_error_info,
								(pWORD8)"Output File", err_code);
#endif
						}
						file_count++;
					}

				}
				g_w_malloc_count = 0;

				printf("\n");

				if(file_count != 2)
				{
#ifdef USE_ITTIAM_ERROR_CODE
					err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
					ia_error_handler(&ia_testbench_error_info,
						(pWORD8)"Input or Output File", err_code);
#endif
				}
				if(err_code == 0)
					ceapp_encodeBuf(fargc, pargv);

				for(i = 0; i < g_w_malloc_count; i++)
				{
					if(g_pv_arr_alloc_memory[i])
						free(g_pv_arr_alloc_memory[i]);
				}
				if(g_pf_inp)
					fclose(g_pf_inp);
				if(g_pf_out)
					fclose(g_pf_out);

			}
    }
  }
  else
  {
	  int i;
	  int err_code = 0;

	  int file_count = 0;
	  for(i = 1; i < argc; i++)
	  {
      printf("%s ", (char*)argv[i]);

		  if(!strncmp((const char *)argv[i], "-ifile:", 7))
		  {
        pWORD8 pb_arg_val = (char*)(argv[i] + 7);
			  WORD8 pb_input_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

			  strcat((char *)pb_input_file_name, (const char *)pb_input_file_path);
			  strcat((char *)pb_input_file_name, (const char *)pb_arg_val);

			  g_pf_inp = NULL;
			  g_pf_inp = fopen((const char *)pb_input_file_name, "rb");
			  if(g_pf_inp == NULL)
			  {
#ifdef USE_ITTIAM_ERROR_CODE
				  err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
				  ia_error_handler(&ia_testbench_error_info,
					  (pWORD8)"Input File", err_code);
#endif
			  }
			  file_count++;
		  }

		  if(!strncmp((const char *)argv[i], "-ofile:", 7))
		  {
        pWORD8 pb_arg_val = (char*)(argv[i] + 7);
			  WORD8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

			  strcat((char *)pb_output_file_name, (const char *)pb_output_file_path);
			  strcat((char *)pb_output_file_name, (const char *)pb_arg_val);

			  g_pf_out = NULL;
			  g_pf_out = fopen((const char *)pb_output_file_name, "wb");
			  if(g_pf_out == NULL)
			  {
#ifdef USE_ITTIAM_ERROR_CODE
				  err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
				  ia_error_handler(&ia_testbench_error_info,
					  (pWORD8)"Output File", err_code);
#endif
			  }
			  file_count++;
		  }

	  }
	  g_w_malloc_count = 0;

	  printf("\n");
	  if(file_count != 2)
	  {
#ifdef USE_ITTIAM_ERROR_CODE
		  err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
		  ia_error_handler(&ia_testbench_error_info,
			  (pWORD8)"Input or Output File", err_code);
#endif
	  }

	  if(err_code == 0)
      ceapp_encodeBuf(argc - 1, (XDAS_Int8 **)&argv[1]);

	  for(i = 0; i < g_w_malloc_count; i++)
	  {
		  if(g_pv_arr_alloc_memory[i])
			  free(g_pv_arr_alloc_memory[i]);
	  }
	  if(g_pf_inp)
		  fclose(g_pf_inp);
	  if(g_pf_out)
		  fclose(g_pf_out);

  }
#ifdef ARM_PROFILE
  fclose(fprofile);
#endif
    return 0;
} /* end main */

