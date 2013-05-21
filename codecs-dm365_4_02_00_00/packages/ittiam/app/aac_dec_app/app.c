/*****************************************************************************/
/*                                                                           */
/*                        Enhanced aacPlus Decoder                           */
/*                                                                           */
/*                   ITTIAM SYSTEMS PVT LTD, BANGALORE                       */
/*                          COPYRIGHT(C) 2004                                */
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
/*  File Name        : main.c                                                */
/*                                                                           */
/*  Description      : Non-Codec-Engine-using part of the Arm-side Linux app,*/
/*                     that at certain points talks to the Codec-Engine-using*/
/*                     part of the Arm-side Linux application.   The latter  */
/*                     module is in file ceapp.c.                            */
/*                     The call flow is: main.c functions -> ceapp.c funcs   */
/*                     or CodecEngine libs                                   */
/*                                                                           */
/*  Issues / Problems: None                                                  */
/*                                                                           */
/*  Revision History :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

/*
Main for enhanced aacPlus decoding
*/

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/audio1/auddec1.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>

#define USE_ITTIAM_ERROR_CODE
#ifdef USE_ITTIAM_ERROR_CODE
#include "ia_type_def.h"
#include "ia_error_standards.h"
#include "ia_error_handler.h"
#endif

#include "ienhaacpdec.h"
#include "enhaacpdec_ittiam.h"

#ifndef WIN32
#define ARM_PROFILE
#endif

#ifdef ARM_PROFILE
	#include <sys/time.h>

	#define CLK_FREQ_BOARD_MHZ 216  // 297 for Davinci

#endif

#ifdef ARM_PROFILE
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

#ifdef USE_ITTIAM_ERROR_CODE
extern ia_error_info_struct ia_testbench_error_info;
extern ia_error_info_struct ia_enhaacplus_dec_error_info;
#define _IA_ENHAACPLUS_DEC_HANDLER(arg1, arg2, arg3) ia_error_handler(arg1, arg2, arg3)
#else
#define _IA_ENHAACPLUS_DEC_HANDLER(arg1, arg2, arg3)
#endif

/*****************************************************************************/
/* Process select hash defines                                               */
/*****************************************************************************/
#define WAV_HEADER
#define DISPLAY_MESSAGE
#define REINIT_FOR_ERROR
//#define ERROR_PATTERN_READ

/*****************************************************************************/
/* Constant hash defines                                                     */
/*****************************************************************************/
#define MAX_STACK_PROC 10
#define MAX_MEM_ALLOCS 100
#define IA_MAX_CMD_LINE_LENGTH 300
#define IA_MAX_ARGS 20
#define IA_SCREEN_WIDTH 80

#define PARAMFILE "aac_dec_params.txt"

/*****************************************************************************/
/* Error codes for the testbench                                             */
/*****************************************************************************/
#define IA_TESTBENCH_MFMAN_FATAL_MEM_ALLOC_FAILED				0xFFFF8000
#define IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED				0xFFFF8001


/*****************************************************************************/
/* Global variables                                                          */
/*****************************************************************************/
XDAS_Void * g_pv_arr_alloc_memory[MAX_MEM_ALLOCS];
XDAS_Int32  g_w_malloc_count;
FILE *g_pf_out;
FILE *g_pf_inp;

#ifdef ERROR_PATTERN_READ
FILE *g_pf_err = NULL;     /* file pointer to error pattern file */
#endif
/*************************************************************************/

static XDAS_Int32 ia_num_ch_from_ch_mode(XDAS_Int32 channel_mode)
{
    switch(channel_mode)
    {
    case IAUDIO_1_0:
        return 1;
    case IAUDIO_2_0:
        return 2;
    case IAUDIO_11_0:
        return 2;
    case IAUDIO_3_0:
        return 3;
    case IAUDIO_2_1:
        return 3;
    case IAUDIO_3_1:
        return 4;
    case IAUDIO_2_2:
        return 4;
    case IAUDIO_3_2:
        return 5;
    case IAUDIO_2_3:
        return 5;
    case IAUDIO_3_3:
        return 6;
    case IAUDIO_3_4:
        return 7;
    default:
        return 0;
    }
}


/* prototypes of functions defined in ceapp.c: */
extern int   ceapp_init(void *params);            /* initialize the ceapp module */
extern char *ceapp_allocContigBuf(    /* allocate physically contiguous */
                int   bufSize,        /*   buffer of given size; description */
                char *bufDescription  /*   is used only for print */
                );
extern void  ceapp_freeContigBuf(    /* free the contiguous buffer */
                char *buf,
                int   bufSize
                );
extern void  ceapp_exit();           /* exit the ceapp module */

extern AUDDEC1_Handle decHandle;

/*****************************************************************************
Allocate input/output buffers for audio codecs
*****************************************************************************/
XDAS_Int32 _allocate_xdm_buffer(
                                XDM1_BufDesc *buffer,        /* XDM buffer ptr */
                                XDAS_Int32 *buffer_sizes,   /* Pointer to Buffer size values */
                                XDAS_Int32 numBufs          /* Number of buffers to be allocated */
                                )
{
    XDAS_Int32 i;

    for(i=0; i<numBufs; i++)
    {
        buffer->descs[i].bufSize    = *buffer_sizes++;
        buffer->descs[i].buf        = ceapp_allocContigBuf(buffer->descs[i].bufSize,  "io_data");
        buffer->descs[i].accessMask = 0;
        if(buffer->descs[i].buf == NULL) return IALG_EFAIL;
    }

    buffer->numBufs = numBufs;

    return (IALG_EOK);
}

/* It allocates memory for audio buffers of XDMI interface.
* Assumption: Single buffers are allocated for both input and output.
*/
XDAS_Int32 allocate_audio_io_buffers(
                                     XDM1_BufDesc *inBufs,           /* Input XDM buffer pointer */
                                     XDM1_BufDesc *outBufs,      /* Output XDM buffer pointer */
                                     XDAS_Int32 input_size,     /* Size of input buffer */
                                     XDAS_Int32 output_size     /* Size of output buffer */
                                     )
{
    int result;

    result = _allocate_xdm_buffer(inBufs, &input_size, 1);
    if(result == IALG_EFAIL)
    {
        printf("App-> Error allocating input buffer!\n");
        return IALG_EFAIL;
    }

    result = _allocate_xdm_buffer(outBufs, &output_size, 1);

    if(result == IALG_EFAIL)
    {
        printf("App-> Error allocating output buffer!\n");
        return IALG_EFAIL;
    }
    return (IALG_EOK);
}

/* It frees memory for audio buffers of XDMI interface.
* Assumption: Single buffers are freed for both input and output.
*/
XDAS_Int32 free_audio_buffers(
                              XDM1_BufDesc *inBuf,          /* Input XDM buffer pointer */
                              XDM1_BufDesc *outBuf      /* Output XDM buffer pointer */
                              )
{

    ceapp_freeContigBuf(inBuf->descs[0].buf, inBuf->descs[0].bufSize);
    ceapp_freeContigBuf(outBuf->descs[0].buf, outBuf->descs[0].bufSize);

    return (IALG_EOK);
}


#ifdef ERROR_PATTERN_READ
/*****************************************************************************/
/*                                                                           */
/*  Function name : ReadErrorPatternFile                                     */
/*                                                                           */
/*  Description   : The function reads the frameError flag from a file.      */
/*                                                                           */
/*  Inputs        : FILE *epf (Input file to read from)                      */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Outputs       : none                                                     */
/*                                                                           */
/*  Returns       : 1 if the frame is ok, else 0                             */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Ittiam                Created                     */
/*                                                                           */
/*****************************************************************************/

static char ReadErrorPatternFile(FILE *epf)
{
    char tmp;
    XDAS_Int32 readOk;

    if (!epf)
        return 1;

    readOk = fscanf(epf, "%c\n", &tmp);
    if (readOk != 1) {
        rewind(epf);
        fscanf(epf, "%c\n", &tmp);
    }
    if (tmp == '0')
        return 1;
    else
        return 0;
}
#endif


#ifdef WAV_HEADER

/*****************************************************************************/
/*                                                                           */
/*  Function name : write16_bits_lh                                          */
/*                                                                           */
/*  Description   : write 16 bits low high (always little endian)            */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : XDAS_Void * g_pv_arr_alloc_memory[MAX_MEM_ALLOCS];             */
/*                  XDAS_Int32  g_w_malloc_count;                            */
/*                  FILE *g_pf_inp, *g_pf_out;                               */
/*                                                                           */
/*  Processing    : write 16 bits low high (always little endian)            */
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

static XDAS_Void write16_bits_lh(FILE *fp, XDAS_Int32 i)
{
    putc(i & 0xff, fp);
    putc((i >> 8) & 0xff, fp);
}

/*****************************************************************************/
/*                                                                           */
/*  Function name : write32_bits_lh                                          */
/*                                                                           */
/*  Description   : write 32 bits low high (always little endian)            */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : FILE* fp (file to write)                                 */
/*                  XDAS_Int32 i (value to write)                            */
/*                                                                           */
/*  Processing    : write 32 bits low high (always little endian)            */
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

static XDAS_Void write32_bits_lh(FILE *fp, XDAS_Int32 i)
{
    write16_bits_lh(fp, (XDAS_Int32)(i & 0xffffL));
    write16_bits_lh(fp, (XDAS_Int32)((i >> 16) & 0xffffL));
}

/*****************************************************************************/
/*                                                                           */
/*  Function name : write_wav_header                                         */
/*                                                                           */
/*  Description   : Write wav header to a wav file                           */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : FILE* fp (file to write)                                 */
/*                  XDAS_Int32 pcmbytes (total bytes in wav file)            */
/*                  XDAS_Int32 freq (sampling freq)                          */
/*                  XDAS_Int32 channels (output channels)                    */
/*                  XDAS_Int32 bits (bits per sample)                        */
/*                                                                           */
/*  Processing    : Write wav header                                         */
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

WORD32 write_wav_header(
   FILE *fp,
   WORD32 pcmbytes,
   WORD32 freq,
   WORD32 channels,
   WORD32 bits,
   WORD32 i_channel_mask)
{

	if (channels > 2)
	{
		WORD32 bytes = (bits + 7) / 8;
		fwrite("RIFF", 1, 4, fp); /* label */
		write32_bits_lh(fp, pcmbytes + 44 - 8); /* length in bytes without header */
		fwrite("WAVEfmt ", 2, 4, fp); /* 2 labels */
		/* tag for WAVE_FORMAT_EXTENSIBLE */
		if(channels > 2)
		{
			write16_bits_lh(fp, 0x28);
			write16_bits_lh(fp, 0x00);
			write16_bits_lh(fp, 0xfffe);
		}
		else
		{
            write32_bits_lh(fp, 2 + 2 + 4 + 4 + 2 + 2); /* length of PCM format decl area */
            write16_bits_lh(fp, 1); /* is pcm? */
        }

        write16_bits_lh(fp, channels);
        write32_bits_lh(fp, freq);
        write32_bits_lh(fp, freq * channels * bytes); /* bps */
        write16_bits_lh(fp, channels * bytes);
        write16_bits_lh(fp, bits);

        /* tag for WAVE_FORMAT_EXTENSIBLE */
        if (channels > 2)
        {
            write16_bits_lh(fp, 0x16);
            write16_bits_lh(fp, 0x10);/*Samples.wReserved*/
            write32_bits_lh(fp, i_channel_mask); /* dwChannelMask */

            write32_bits_lh(fp, 0x0001); /* SubFormat.Data1 */
            write32_bits_lh(fp, 0x00100000); /* SubFormat.Data2 and SubFormat.Data3 */

            write16_bits_lh(fp, 0x0080);
            write16_bits_lh(fp, 0xAA00);

            write16_bits_lh(fp, 0x3800);
            write16_bits_lh(fp, 0x719b);
            /*
            write16_bits_lh(fp, 0x6166);
            write16_bits_lh(fp, 0x7463);

              write16_bits_lh(fp, 0x0004);
              write16_bits_lh(fp, 0x0000);

                write16_bits_lh(fp, 0x5800);
                write16_bits_lh(fp, 0x0028);
            */      }


            fwrite("data", 1, 4, fp);
            write32_bits_lh(fp, pcmbytes);

            return (ferror(fp) ? -1 : 0);


    }
    else
    {
        XDAS_Int32 bytes = (bits + 7) / 8;
        fwrite("RIFF", 1, 4, fp); /* label */
        write32_bits_lh(fp, pcmbytes + 44 - 8); /* length in bytes without header */
        fwrite("WAVEfmt ", 2, 4, fp); /* 2 labels */
        write32_bits_lh(fp, 2 + 2 + 4 + 4 + 2 + 2); /* length of PCM format decl area */
        write16_bits_lh(fp, 1); /* is pcm? */
        write16_bits_lh(fp, channels);
        write32_bits_lh(fp, freq);
        write32_bits_lh(fp, freq * channels * bytes); /* bps */
        write16_bits_lh(fp, channels * bytes);
        write16_bits_lh(fp, bits);
        fwrite("data", 1, 4, fp);
        write32_bits_lh(fp, pcmbytes);

        return (ferror(fp) ? -1 : 0);

    }
}
/* WAV_HEADER */
#endif
#ifdef DISPLAY_MESSAGE

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_display_id_message                                    */
/*                                                                           */
/*  Description   : Display the ID message of the process                    */
/*                                                                           */
/*  Inputs        : XDAS_Int8 lib_name[] (library name)                      */
/*                  XDAS_Int8 lib_version[] (library version)                */
/*                  XDAS_Int8 api_version[] (API version)                    */
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

void print_usage()
{
    printf("\n Usage \n");
    printf("\n <exceutable> -ifile:<input_file> -ofile:<out_file> [options]\n");
    printf("\n[options] can be,");
#ifdef ERROR_PATTERN_READ
    printf("\n[-errfile:<error_pattern_file>]");
#endif
    printf("\n[-pcmsz:<pcmwordsize>]");
    printf("\n[-dmix:<down_mix>]");
#ifdef RESAMPLE_SUPPORT
    /* By default not available */
    printf("\n[-f08:<out_08khz>]");
    printf("\n[-f16:<out_16khz>]");
#endif
    printf("\n[-tostereo:<interleave_to_stereo>]");
    printf("\n[-dsample:<down_sample_sbr>]");
    printf("\n[-fs:<RAW_sample_rate>]");
    printf("\n[-nosync:<disable_sync>]");
    printf("\n[-sbrup:<auto_sbr_upsample>]");

    printf("\n[-maxchannel:<maximum_num_channels>]");
    printf("\n[-coupchannel:<coupling_channel>]");
    printf("\n[-downmix:<down_mix_stereo>]");

    printf("\n\nwhere, \n  <inputfile> is the input AAC file name");
    printf("\n  <outputfile> is the output file name");
#ifdef ERROR_PATTERN_READ
    printf("\n  <error_pattern_file> is the error pattern file name");
#endif
    printf("\n  <pcmwordsize> is the bits per sample info. Only 16 is valid");

    printf("\n  <down_mix> is to enable/disable always mono output. Default 0");
#ifdef RESAMPLE_SUPPORT
    printf("\n  <out_08khz> is to enable/disable 8 kHz output. Default 0 ");
    printf("\n  <out_16khz> is to enable/disable 16 kHz output. Default 0 ");
#endif
    printf("\n  <interleave_to_stereo> is to enable/disable always ");
    printf("\n    interleaved to stereo output. Default 1 ");
    printf("\n  <down_sample_sbr> is to enable/disable down-sampled SBR ");
    printf("\n    output. Default auto identification from header");
    printf("\n  <RAW_sample_rate> is to indicate the core AAC sample rate for");
    printf("\n    a RAW stream. If this is specified no other file format");
    printf("\n    headers are searched for. \n");
    printf("\n  <disable_sync> is to disable the ADTS/ADIF sync search i.e");
    printf("\n    when enabled the decoder expects the header to ");
    printf("\n    be at the start of input buffer. Default 0");
    printf("\n  <auto_sbr_upsample> is to enable(1) or disable(0) auto SBR upsample ");
    printf("\n    in case of stream changing from SBR present to SBR not present. Default 1");
    printf("\n  <maximum_num_channels> is the number of maxiumum ");
    printf("\n    channels the input may have. Default is 6 (5.1)");

    printf("\n  <coupling_channel> is element instance tag of ");
    printf("\n    independent coupling channel to be mixed. Default is 0");
    printf("\n    Used in multichannel libraries only");
    printf("\n  <down_mix_stereo> is flag for Downmix. Give 1 to");
    printf("\n    get stereo (downmix) output. Default is 0");
    printf("\n    Used in multichannel libraries only");

}

void enhaacplus_dec_set_param(ITTIAM_ENHAACPDEC_Params *params,XDAS_Int32 argc,
                              XDAS_Int8 *argv[], XDAS_Int32 *pi_desired_cm,
                              XDAS_Int32 *pi_desired_lfeflag,
                              XDAS_Int32 *pi_downsample)
{
    XDAS_Int32 i;
    params->s_iauddec_params.size = sizeof(ITTIAM_ENHAACPDEC_Params);
    for(i = 0; i < argc; i++)
    {
        /* PCM Word Size (For single input file) */
        if(!strncmp((char *)argv[i], "-pcmsz:", 7))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 7);
            XDAS_UInt32 ui_pcm_wd_sz = atoi(pb_arg_val);
            params->s_iauddec_params.outputPCMWidth = ui_pcm_wd_sz;
            
        }
        /* Down-mix stereo to mono. */
        if(!strncmp((char *)argv[i], "-dmix:", 6))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 6);
            XDAS_UInt32 ui_down_mix = atoi(pb_arg_val);
            if(ui_down_mix == 1)
            {
                *pi_desired_cm = IAUDIO_1_0;//ui_down_mix;
                *pi_desired_lfeflag = XDAS_FALSE;
            }
        }
        /* Resample the output to 8 kHz. */
        if(!strncmp((char *)argv[i], "-f08:", 5))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 5);
            XDAS_UInt32 ui_08khz_out = atoi(pb_arg_val);
            params->i_flag_08khz_out = ui_08khz_out;
        }
        /* Resample the output to 16 kHz. */
        if(!strncmp((char *)argv[i], "-f16:", 5))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 5);
            XDAS_UInt32 ui_16khz_out = atoi(pb_arg_val);
            params->i_flag_16khz_out = ui_16khz_out;
        }
        /* Interleave mono output to stereo */
        if(!strncmp((char *)argv[i], "-tostereo:", 10))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 10);
            XDAS_UInt32 ui_to_stereo = atoi(pb_arg_val);
            if(ui_to_stereo == 1)
            {
                *pi_desired_cm = IAUDIO_2_0;//ui_to_stereo;
                *pi_desired_lfeflag = XDAS_FALSE;
                params->i_interleave = 1 ;
            }
            else
            {
				params->i_interleave = 0 ;
			}
        }
        /* Downsampled synthesis to be used */
        if(!strncmp((char *)argv[i], "-dsample:", 9))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 9);
            XDAS_UInt32 ui_dsample = atoi(pb_arg_val);
            *pi_downsample = ui_dsample;
        }
        /* To indicate if its a MP4 file or not. */
        if(!strncmp((char *)argv[i], "-mp4:", 5))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 5);
            XDAS_UInt32 ui_mp4_flag = atoi(pb_arg_val);
            params->i_mp4_flag = ui_mp4_flag;
        }
        /* To indicate if sync word search to be done or not. */
        if(!strncmp((char *)argv[i], "-nosync:", 8))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 8);
            XDAS_UInt32 ui_disable_sync = atoi(pb_arg_val);
            params->i_disable_sync = ui_disable_sync;
        }
        /* To indicate if auto SBR upsample has to be enabled or not. */
        if(!strncmp((char *)argv[i], "-sbrup:", 7))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 7);
            XDAS_UInt32 ui_auto_sbr_upsample = atoi(pb_arg_val);
            params->i_auto_sbr_upsample = ui_auto_sbr_upsample;

        }
        /* To indicate sample rate for a RAW bit-stream. */
        if(!strncmp((char *)argv[i], "-fs:", 4))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 4);
            XDAS_UInt32 ui_samp_freq = atoi(pb_arg_val);
            params->i_sampfreq = ui_samp_freq;
        }
        /* To indicate the number of maximum channels */
        if(!strncmp((char *)argv[i], "-maxchannel:", 12))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 12);
            XDAS_UInt32 ui_max_ch = atoi(pb_arg_val);
            params->i_max_channels = ui_max_ch;
        }
        /* To indicate the number of coupling channels to be used for coupling */
        if(!strncmp((char *)argv[i], "-coupchannel:", 13))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 13);
            XDAS_UInt32 ui_coupling_channel = atoi(pb_arg_val);
            params->i_coupling_channel = ui_coupling_channel;
        }
        /* Down-mix Multichannel to stereo */
        if(!strncmp((char *)argv[i], "-downmix:", 9))
        {
            XDAS_Int8 *pb_arg_val = (XDAS_Int8 *)(argv[i] + 9);
            XDAS_UInt32 ui_downmix_mc_to_stereo = atoi(pb_arg_val);
            if(ui_downmix_mc_to_stereo == 1)
            {
                *pi_desired_cm = IAUDIO_2_0;//ui_downmix_mc_to_stereo;
                *pi_desired_lfeflag = XDAS_FALSE;
            }
        }
    }
    return;
}

#ifdef WAV_HEADER

#define IA_ENHAACPLUS_DEC_ERROR_ACTION(ps_err_string) \
    printf(ps_err_string);\
    ceapp_exit();\
    free_audio_buffers(&inBufs, &outBufs);\
    if(outArgs.i_init_done)\
    {\
        if(!fseek(g_pf_out, 0, SEEK_SET))\
          write_wav_header(g_pf_out, i_total_bytes,\
          status.s_iauddec_status.sampleRate,\
          ia_num_ch_from_ch_mode(status.s_iauddec_status.channelMode) + status.s_iauddec_status.lfeFlag,\
          status.s_iauddec_status.outputBitsPerSample,\
          status.i_channel_mask);\
    }

#else

#define IA_ENHAACPLUS_DEC_ERROR_ACTION(ps_err_string) \
    printf("Error in XDM_GETSTATUS");\
    ceapp_exit();\
    free_audio_buffers(&inBufs, &outBufs);

#endif


/*
 *  ======== ceapp_decodeBuf ========
 */
#ifdef REINIT_FOR_ERROR
XDAS_Int32 ceapp_decodeBuf(XDAS_Int32 argc, XDAS_Int8 *argv[],
                           XDAS_Int8 *pb_output_file_name)
#else
XDAS_Int32 ceapp_decodeBuf(XDAS_Int32 argc, XDAS_Int8 *argv[])
#endif
{
    ITTIAM_ENHAACPDEC_Status status;
    ITTIAM_ENHAACPDEC_Params params;
    ITTIAM_ENHAACPDEC_DynamicParams dparams;

    XDM1_BufDesc inBufs, outBufs;
    ITTIAM_ENHAACPDEC_InArgs inArgs;
    ITTIAM_ENHAACPDEC_OutArgs outArgs;

    XDAS_Int32 errorFlag, process_err;

    XDAS_Int32 input_size, output_size;
    XDAS_Int8 *inputBuffer ;

    XDAS_Int32 i_bytes_consumed, ret_status=0, frame_cnt = 0;
    XDAS_Int32 i_buff_size,wave_header = 0;
    XDAS_UInt32 ui_inp_size = 0;
    XDAS_Int32 i_out_bytes, i_bytes_read, i_total_bytes = 0;

    XDAS_Int32 i;
    XDAS_Int32 i_num_fatal_err = 0;
    XDAS_Int32 i_num_nonfatal_err = 0;

#ifdef REINIT_FOR_ERROR
    XDAS_Int32 i_op_file_cnt = 0;
#endif
    XDAS_Int32 i_desired_cm = -1, i_desired_lfeflag = -1;
    XDAS_Int32 i_downsample = 0;

#ifdef ARM_PROFILE
        int frame_count_b = 0;
		long long cycles_b = 0;
		long long  start1_b, stop1_b;
		double  Curr_b, Ave_b = 0, Sum_b = 0;
		double Peak_b = 0;
		WORD32 Peak_frame_b = 0;
#endif

    memset(&params, 0, sizeof(params));
    memset(&dparams, 0, sizeof(dparams));
    memset(&status, 0, sizeof(status));
    memset(&inArgs, 0, sizeof(inArgs));
    memset(&outArgs, 0, sizeof(outArgs));

    params.s_iauddec_params.size = sizeof(params);
    dparams.s_iauddec_dynparams.size = sizeof(dparams);
    status.s_iauddec_status.size = sizeof(status);
    inArgs.s_iauddec_in_args.size = sizeof(inArgs);
    outArgs.s_iauddec_outargs.size = sizeof(outArgs);

    params = ENHAACPDECODER_ITTIAM_PARAMS;

    /* Initialize the params Structure */
    enhaacplus_dec_set_param(&params, argc, argv, &i_desired_cm, &i_desired_lfeflag, &i_downsample);

    /* Initialize the Functions Structure */
    ret_status = ceapp_init(&params);
    if (ret_status != 0) {
        printf("Error in initialisation\n");
        return(0);
    }

    ret_status = AUDDEC1_control(decHandle, XDM_GETSTATUS, (IAUDDEC1_DynamicParams *)&dparams,
        (IAUDDEC1_Status *)&status);
    if (ret_status != AUDDEC1_EOK) {
        printf("CEapp-> Audio Decoder control FAILED, ret_status = %d\n", (int)ret_status);
        ceapp_exit();
        return(0);
    }

    input_size = status.s_iauddec_status.bufInfo.minInBufSize[0];
    output_size = status.s_iauddec_status.bufInfo.minOutBufSize[0];

    errorFlag = allocate_audio_io_buffers(&inBufs, &outBufs, input_size, output_size);
    if (errorFlag != IALG_EOK)
    {
        printf("Error in I/O buffer alloc\n");
        ceapp_exit();
        free_audio_buffers(&inBufs, &outBufs);
        return(0);
    }

    if(outBufs.descs[0].bufSize >= 64)
    {
        status.s_iauddec_status.data.buf = outBufs.descs[0].buf;
        status.s_iauddec_status.data.bufSize = outBufs.descs[0].bufSize;
        ret_status = AUDDEC1_control(decHandle, XDM_GETVERSION,(IAUDDEC1_DynamicParams*)&dparams,
            (IAUDDEC1_Status*)&status);
        if (ret_status != AUDDEC1_EOK)
        {
            printf("Error in XDM_GETVERSION\n");
            ceapp_exit();
            return(0);
        }

        ia_display_id_message((XDAS_Int8 *)status.s_iauddec_status.data.buf);
    }
    else
    {
        printf("Not enough buffer to do get version info\n");
        ceapp_exit();
        free_audio_buffers(&inBufs, &outBufs);
        return(0);
    }
    
    if(i_downsample == 1)
    {
        dparams.s_iauddec_dynparams.downSampleSbrFlag = XDAS_TRUE;
        ret_status = AUDDEC1_control(decHandle, XDM_SETPARAMS,(IAUDDEC1_DynamicParams*)&dparams,
            (IAUDDEC1_Status*)&status);
        if (ret_status != AUDDEC1_EOK)
        {
            printf("Error in XDM_SETPARAMS\n");
            ceapp_exit();
            free_audio_buffers(&inBufs, &outBufs);
            return(0);
        }
    }


    if (decHandle != NULL)
    {
        inputBuffer = inBufs.descs[0].buf;

        ui_inp_size = input_size;
        i_bytes_consumed = ui_inp_size;
        i_buff_size = ui_inp_size;

#ifdef REINIT_FOR_ERROR
INIT_AGAIN:
#endif

        do
        {
            if ((ui_inp_size - (i_buff_size - i_bytes_consumed)) > 0)
            {
                for (i = 0; i < (i_buff_size - i_bytes_consumed); i++)
                {
                    inputBuffer[i] = inputBuffer[i + i_bytes_consumed];
                }
                i_bytes_read = fread(inputBuffer + (i_buff_size) - i_bytes_consumed, 1,
                    (ui_inp_size - (i_buff_size - i_bytes_consumed)), g_pf_inp);

                i_buff_size = i_buff_size - (i_bytes_consumed - i_bytes_read);

                if(i_bytes_read <= 0)
                {

                    ret_status = AUDDEC1_control(decHandle, XDM_FLUSH, (IAUDDEC1_DynamicParams *)&dparams,
                        (IAUDDEC1_Status *)&status);

                    if (ret_status != AUDDEC1_EOK)
                    {
                        IA_ENHAACPLUS_DEC_ERROR_ACTION("CEapp-> Audio Decoder control FAILED\n")
                        return(0);
                    }

                }
            }
            inArgs.s_iauddec_in_args.numBytes = i_buff_size;
            inArgs.s_iauddec_in_args.desiredChannelMode = i_desired_cm;
            inArgs.s_iauddec_in_args.lfeFlag = i_desired_lfeflag;

            //process call
			printf("App-> Processing frame %d...\r", ++frame_cnt);

#ifdef ARM_PROFILE
			start1_b= itGetMs();
#endif
			process_err = AUDDEC1_process(decHandle, &inBufs, &outBufs,
                (IAUDDEC1_InArgs *)&inArgs, (IAUDDEC1_OutArgs *)&outArgs);

#ifdef ARM_PROFILE
			stop1_b= itGetMs();
			cycles_b += (stop1_b - start1_b);
#endif

            i_bytes_consumed = outArgs.s_iauddec_outargs.bytesConsumed;

            if(outArgs.i_ittiam_err_code)
            {
                _IA_ENHAACPLUS_DEC_HANDLER(&ia_enhaacplus_dec_error_info,
                    (WORD8 *)"", outArgs.i_ittiam_err_code);

#ifdef REINIT_FOR_ERROR
                if(outArgs.i_ittiam_err_code < 0)
                {
                    i_num_fatal_err++;
                    if(i_num_fatal_err > 20)
                    {
                        IA_ENHAACPLUS_DEC_ERROR_ACTION("Too many fatal errors encountered, terminating re-init attempts\n");
                        return(0);
                    }

                }
                else
                {
                    i_num_nonfatal_err++;
                    if(i_num_nonfatal_err > 100)
                    {
                        IA_ENHAACPLUS_DEC_ERROR_ACTION("Too many non fatal errors encountered, terminating re-init attempts\n");
                        return(0);
                    }

                }
                {
                    XDAS_Int8 pb_file_cnt_arr[9];
                    i_op_file_cnt++;
                    wave_header = 0;
                    i_out_bytes = (outArgs.s_iauddec_outargs.numSamples) * 
                                  (outArgs.i_output_bits_per_sample/8) *
                                   (ia_num_ch_from_ch_mode(outArgs.s_iauddec_outargs.channelMode) + outArgs.s_iauddec_outargs.lfeFlag);
                    i_total_bytes += i_out_bytes;

                    fwrite(outBufs.descs[0].buf, sizeof(XDAS_Int8), i_out_bytes, g_pf_out);

                    ret_status = AUDDEC1_control(decHandle, XDM_RESET, (IAUDDEC1_DynamicParams *)&dparams,
                        (IAUDDEC1_Status *)&status);

                    if(ret_status != AUDDEC1_EOK)
                    {
                        IA_ENHAACPLUS_DEC_ERROR_ACTION("Error in XDM_RESET\n");
                        return(0);
                    }

#ifdef WAV_HEADER
                    ret_status = AUDDEC1_control(decHandle, XDM_GETSTATUS, (IAUDDEC1_DynamicParams *)&dparams,
                        (IAUDDEC1_Status *)&status);

                    if(ret_status != IALG_EOK)
                    {
                        IA_ENHAACPLUS_DEC_ERROR_ACTION("Error in XDM_GETSTATUS\n");
                        return(0);
                    }

                    if(!fseek(g_pf_out, 0, SEEK_SET))
                        write_wav_header(g_pf_out, i_total_bytes,
                            status.s_iauddec_status.sampleRate,
                            ia_num_ch_from_ch_mode(status.s_iauddec_status.channelMode) + status.s_iauddec_status.lfeFlag,
                            status.s_iauddec_status.outputBitsPerSample,
                            status.i_channel_mask);
#endif
                    fclose(g_pf_out);
                    i_total_bytes = 0;
                    sprintf((char *)pb_file_cnt_arr, "_%03d.wav", (int)i_op_file_cnt);
                    if(i_op_file_cnt == 1)
                        strcpy((char *)(pb_output_file_name + strlen(pb_output_file_name) - 4),
                            (const char *)pb_file_cnt_arr);
                    else
                        strcpy((char *)(pb_output_file_name + strlen(pb_output_file_name) - 8),
                            (const char *)pb_file_cnt_arr);

                    g_pf_out = fopen((const char *)pb_output_file_name, "wb");

                    if(g_pf_out == NULL)
                    {
                        _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                            (WORD8 *)"Output File",
                            IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED);
                        return(0);
                    }

                    goto INIT_AGAIN;
                }
#endif
            }

            if( (outArgs.i_ittiam_err_code < 0) ||
                (process_err != AUDDEC1_EOK))
            {
				if(XDM_ISFATALERROR(outArgs.s_iauddec_outargs.extendedError))
				{
                IA_ENHAACPLUS_DEC_ERROR_ACTION("CEapp-> AUDDEC1_process() failed\n");
                return(0);
				}
            }

            if(outArgs.i_init_done && (wave_header == 0))
            {
                ret_status = AUDDEC1_control(decHandle, XDM_GETSTATUS, (IAUDDEC1_DynamicParams *)&dparams,
                    (IAUDDEC1_Status *)&status);

                if(ret_status != AUDDEC1_EOK)
                {
                    IA_ENHAACPLUS_DEC_ERROR_ACTION("Error in XDM_GETSTATUS\n");
                    return(0);
                }

#ifdef WAV_HEADER
                write_wav_header(g_pf_out, 0x7fffffff,
                    status.s_iauddec_status.sampleRate,
                    ia_num_ch_from_ch_mode(status.s_iauddec_status.channelMode) + status.s_iauddec_status.lfeFlag,
                    status.s_iauddec_status.outputBitsPerSample,
                    status.i_channel_mask);
#endif

                wave_header = 1;
                /* Channel mode to tell MONO/STEREO/DUAL-MONO/NONE_OF_THESE */
                if(status.i_channel_mode == 0)
                    printf("Channel Mode: MONO_OR_PS\n");
                else if(status.i_channel_mode == 1)
                    printf("Channel Mode: STEREO\n");
                else if(status.i_channel_mode == 2)
                    printf("Channel Mode: DUAL-MONO\n");
                else
                    printf("Channel Mode: NONE_OF_THESE or MULTICHANNEL\n");

                /* Channel mode to tell SBR PRESENT/NOT_PRESENT */
                if(status.i_sbr_mode == 0)
                    printf("SBR Mode: NOT_PRESENT\n");
                else if(status.i_sbr_mode == 1)
                    printf("SBR Mode: PRESENT\n");
                else
                    printf("SBR Mode: ILLEGAL\n");
            }

            i_out_bytes = (outArgs.s_iauddec_outargs.numSamples) * (outArgs.i_output_bits_per_sample/8)
                            * (ia_num_ch_from_ch_mode(outArgs.s_iauddec_outargs.channelMode) + outArgs.s_iauddec_outargs.lfeFlag);
            i_total_bytes += i_out_bytes;

            fwrite(outBufs.descs[0].buf, sizeof(XDAS_Int8), i_out_bytes, g_pf_out);




#ifdef ARM_PROFILE
			if(i_out_bytes)
			{
				int i_out_samples = i_out_bytes / ((status.s_iauddec_status.outputBitsPerSample/8) * status.i_num_channels) ;

				if (frame_cnt > 3)
				{

					double i_out_samples_per_ch = i_out_samples;
					Curr_b = (((double)cycles_b / 1000000) * CLK_FREQ_BOARD_MHZ) /
						(i_out_samples_per_ch / status.s_iauddec_status.sampleRate);
					Sum_b += Curr_b;
					Ave_b = Sum_b / frame_cnt;
					if (Peak_b < Curr_b)
					{
						Peak_b = Curr_b;
						Peak_frame_b = frame_cnt;
					}
				}
				cycles_b = 0;
			}
#endif



            /* Do till the process execution is done */
      } while(!outArgs.i_exec_done);

#ifdef WAV_HEADER
      ret_status = AUDDEC1_control(decHandle, XDM_GETSTATUS, (IAUDDEC1_DynamicParams *)&dparams,
          (IAUDDEC1_Status *)&status);
      
      if(ret_status != AUDDEC1_EOK)
      {
          IA_ENHAACPLUS_DEC_ERROR_ACTION("Error in XDM_GETSTATUS\n");
          return(0);
      }
      
      if(!fseek(g_pf_out, 0, SEEK_SET))
          write_wav_header(g_pf_out, i_total_bytes,status.s_iauddec_status.sampleRate,
          ia_num_ch_from_ch_mode(status.s_iauddec_status.channelMode) + status.s_iauddec_status.lfeFlag,status.s_iauddec_status.outputBitsPerSample, status.i_channel_mask);
#endif
    }
    printf("\nApp-> Finished decoding...\n");
    ceapp_exit();
    free_audio_buffers(&inBufs, &outBufs);
_end_of_decode:
#ifdef ARM_PROFILE
		fprintf(stderr,"\n Peak MCPS = %f\n",Peak_b);
		fprintf(stderr," Avg MCPS = %f\n",Ave_b);
		fprintf(stderr," Peak frame = %d\n",Peak_frame_b);
#endif

    return 0;
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

int main(int argc, char** argv)
{
    FILE *param_file_id;

    XDAS_Int8 curr_cmd[IA_MAX_CMD_LINE_LENGTH];
    XDAS_Int32 fargc, curpos;
    XDAS_Int32 processcmd = 0;

    XDAS_Int8 fargv[IA_MAX_ARGS][IA_MAX_CMD_LINE_LENGTH];

    XDAS_Int8 *pargv[IA_MAX_ARGS];

    XDAS_Int8 pb_input_file_path[IA_MAX_CMD_LINE_LENGTH] = "";
    XDAS_Int8 pb_output_file_path[IA_MAX_CMD_LINE_LENGTH] = "";
#ifdef REINIT_FOR_ERROR
    XDAS_Int8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";
#endif

    /* This function has been moved from ceapp_init() in ceapp.c */
    CERuntime_init();
    ia_enhaacplus_dec_error_handler_init();
	ia_testbench_error_handler_init();


    if(argc == 1)
    {
        param_file_id = fopen(PARAMFILE, "r");
        if(param_file_id==NULL)
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
                    XDAS_Int32 i;
                    XDAS_Int32 err_code = 0;
                    XDAS_Int32 file_count=0;

                    for(i = 0; i < fargc; i++)
                    {
                        printf("%s ", fargv[i]);
                        pargv[i] = fargv[i];

                        if(!strncmp((const char *)fargv[i], "-ifile:", 7))
                        {
                            XDAS_Int8 *pb_arg_val = fargv[i] + 7;
                            XDAS_Int8 pb_input_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

                            strcat((char *)pb_input_file_name, (const char *)pb_input_file_path);
                            strcat((char *)pb_input_file_name, (const char *)pb_arg_val);

                            g_pf_inp = NULL;
                            g_pf_inp = fopen((const char *)pb_input_file_name, "rb");

                            if(g_pf_inp == NULL)
                            {
                                err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                                _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                                    (WORD8 *)"Input File", err_code);
                            }
                            file_count++;
                        }

                        if(!strncmp((const char *)fargv[i], "-ofile:", 7))
                        {
                            XDAS_Int8 *pb_arg_val = fargv[i] + 7;
#ifndef REINIT_FOR_ERROR
                            XDAS_Int8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";
#endif

                            strcpy((char *)pb_output_file_name, (const char *)pb_output_file_path);
                            strcat((char *)pb_output_file_name, (const char *)pb_arg_val);

                            g_pf_out = NULL;
                            g_pf_out = fopen((const char *)pb_output_file_name, "wb");
                            if(g_pf_out == NULL)
                            {
                                err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                                _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                                    (WORD8 *)"Output File", err_code);
                            }
                            file_count++;
                        }

#ifdef ERROR_PATTERN_READ
                        if(!strncmp((const char *)fargv[i], "-errfile:", 9))
                        {
                            XDAS_Int8 *pb_arg_val = fargv[i] + 9;
                            g_pf_err = fopen((const char *)pb_arg_val, "r");
                            if(g_pf_err == NULL)
                            {
                                err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                                _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                                    (WORD8 *)"Error Pattern File", err_code);
                            }
                        }
#endif
                    }
                    g_w_malloc_count = 0;

                    printf("\n");
                    if(file_count!=2)
                    {
                        err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                        _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                            (WORD8 *)"Input or Output File", err_code);
                    }


                    if(err_code == 0)
                    {
#ifdef REINIT_FOR_ERROR
                        ceapp_decodeBuf(fargc, pargv, pb_output_file_name);
#else
                        ceapp_decodeBuf(fargc, pargv);
#endif
                    }

                    for(i = 0; i < g_w_malloc_count; i++)
                    {
                        if(g_pv_arr_alloc_memory[i])
                            free(g_pv_arr_alloc_memory[i]);
                    }
                    if(g_pf_out)
                        fclose(g_pf_out);

                    if(g_pf_inp)
                        fclose(g_pf_inp);
#ifdef ERROR_PATTERN_READ
                    if (g_pf_err)
                        fclose(g_pf_err);
#endif
                }
        }
        fclose(param_file_id);
    }
    else
    {
        XDAS_Int32 i;
        XDAS_Int32 err_code = 0;
        XDAS_Int32 file_count=0;

        for(i = 1; i < argc; i++)
        {
            pargv[i] = fargv[i];
            strcpy((char *)fargv[i], (char *)argv[i]);
            printf("%s ", pargv[i]);

            if(!strncmp((const char *)pargv[i], "-ifile:", 7))
            {
                XDAS_Int8 *pb_arg_val = pargv[i] + 7;
                XDAS_Int8 pb_input_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

                err_code = 0;
                strcat((char *)pb_input_file_name, (const char *)pb_input_file_path);
                strcat((char *)pb_input_file_name, (const char *)pb_arg_val);

                g_pf_inp = NULL;
                g_pf_inp = fopen((const char *)pb_input_file_name, "rb");
                if(g_pf_inp == NULL)
                {
                    err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                    _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                        (WORD8 *)"Input File", err_code);
                }
                file_count++;
            }

            if(!strncmp((const char *)pargv[i], "-ofile:", 7))
            {
                XDAS_Int8 *pb_arg_val = pargv[i] + 7;
#ifndef REINIT_FOR_ERROR
                XDAS_Int8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";
#endif

                strcat((char *)pb_output_file_name, (const char *)pb_output_file_path);
                strcat((char *)pb_output_file_name, (const char *)pb_arg_val);

                g_pf_out = NULL;
                g_pf_out = fopen((const char *)pb_output_file_name, "wb");
                if(g_pf_out == NULL)
                {
                    err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                    _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                        (WORD8 *)"Output File", err_code);
                }
                file_count++;
            }

#ifdef ERROR_PATTERN_READ
            if(!strncmp((const char *)pargv[i], "-errfile:", 9))
            {
                XDAS_Int8 *pb_arg_val = pargv[i] + 9;
                g_pf_err = fopen((const char *)pb_arg_val, "r");
                if(g_pf_err == NULL)
                {
                    err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
                    _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                        (WORD8 *)"Error Pattern File", err_code);
                }
            }
#endif
        }
        g_w_malloc_count = 0;

        printf("\n");
        if(file_count!=2)
        {
            err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
            _IA_ENHAACPLUS_DEC_HANDLER(&ia_testbench_error_info,
                (WORD8 *)"Input or Output File", err_code);
        }

        if(err_code == 0)
        {
            ceapp_decodeBuf(argc - 1, (XDAS_Int8 **)&pargv[1]
#ifdef REINIT_FOR_ERROR
                , pb_output_file_name
#endif
                );
        }

        for(i = 0; i < g_w_malloc_count; i++)
        {
            if(g_pv_arr_alloc_memory[i])
                free(g_pv_arr_alloc_memory[i]);
        }
        if(g_pf_out)
            fclose(g_pf_out);

        if(g_pf_inp)
            fclose(g_pf_inp);
#ifdef ERROR_PATTERN_READ
        if (g_pf_err)
            fclose(g_pf_err);
#endif
    }

    return 0;
}/* end main */

