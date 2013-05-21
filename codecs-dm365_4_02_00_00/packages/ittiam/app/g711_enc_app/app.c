/*****************************************************************************/
/*                                                                           */
/*                           Ittiam G711 Encoder                              */
/*                                                                           */
/*                   ITTIAM SYSTEMS PVT LTD, BANGALORE                       */
/*                          COPYRIGHT(C) 2005                                */
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


/*****************************************************************************/
/* File includes                                                             */
/*****************************************************************************/

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* include various CodecEngine header files */
#include <xdc/std.h>
#include <ti/sdo/ce/Engine.h>
#include <ti/sdo/ce/osal/Memory.h>
#include <ti/sdo/ce/speech1/sphenc1.h>
#include <ti/sdo/ce/CERuntime.h>
#include <ti/sdo/ce/trace/gt.h>
#include <ti/xdais/dm/ispeech1_pcm.h>


//#include "timerutil.h"

//#define ENABLE_CE_PROFILE

#ifdef ENABLE_CE_PROFILE
#define TEST_MODE   PROFILE_TEST
#else
#define TEST_MODE   NO_TEST
#endif /* ENABLE_CE_PROFILE */
//#define PROFILE_ON 1
#ifdef PROFILE_ON
#include "test_utility.h"
#endif


//#define USE_ITTIAM_ERROR_CODE
#ifdef USE_ITTIAM_ERROR_CODE
#include "ia_type_def.h"
#include "ia_error_standards.h"
#include "ia_error_handler.h"
#endif

#include "ig711enc.h"
#include "g711enc_ittiam.h"


/*****************************************************************************/
/* Process select hash defines                                               */
/*****************************************************************************/
//#define WAV_HEADER

/*****************************************************************************/
/* Constant hash defines                                                     */
/*****************************************************************************/
#define PARAMFILE "g711_enc_params.txt"

#define MAX_STACK_PROC 10
#define MAX_MEM_ALLOCS 100
#define IA_MAX_CMD_LINE_LENGTH 300
#define IA_MAX_ARGS 20
#define IA_SCREEN_WIDTH 80

/**************************************************************/

#ifdef USE_ITTIAM_ERROR_CODE
extern ia_error_info_struct ia_testbench_error_info;
extern ia_error_info_struct ia_g711_enc_error_info;
#endif

/*****************************************************************************/
/* Error codes for the testbench                                             */
/*****************************************************************************/
#define IA_TESTBENCH_MFMAN_FATAL_MEM_ALLOC_FAILED               0xFFFF8000
#define IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED               0xFFFF8001

/**************************************************************/
FILE *g_pf_inp;
FILE *g_pf_out;

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

extern SPHENC1_Handle encHandle;

G711ENC_ITTIAM_Params G711ENC_ITTIAM_PARAMS1 = {
    {
        sizeof(G711ENC_ITTIAM_Params),
        160,    /* Input frame size in samples              */
        ISPEECH1_PCM_COMPAND_ALAW,      /* compandingLaw    */
        0,      /* packingType not applicable               */
        0,      /* vadSelection  not applicable;            */
        0,      /* codecSelection not applicable            */
        64,     /* Fixed bitrate in kbps                    */
        0,      /* reserved not used                        */
        0,      /* tablesPtr not used                       */
    },
};


/*****************************************************************************
Allocate input/output buffers for audio codecs
*****************************************************************************/
XDAS_Int32 _allocate_xdm_buffer(
                                XDM1_SingleBufDesc *buffer,        /* XDM buffer ptr */
                                XDAS_Int32 *buffer_sizes,   /* Pointer to Buffer size values */
                                XDAS_Int32 numBufs          /* Number of buffers to be allocated */
                                )
{
    XDAS_Int32 i;

    for(i=0; i<numBufs; i++)
    {
        buffer->bufSize    = *buffer_sizes++;
        buffer->buf        = ceapp_allocContigBuf(buffer->bufSize,  "io_data");
        buffer->accessMask = 0;
        if(buffer->buf == NULL) return IALG_EFAIL;
    }


    return (IALG_EOK);
}

/* It allocates memory for audio buffers of XDMI interface.
* Assumption: Single buffers are allocated for both input and output.
*/
XDAS_Int32 allocate_speech_io_buffers(
                                     XDM1_SingleBufDesc *inBufs,           /* Input XDM buffer pointer */
                                     XDM1_SingleBufDesc *outBufs,      /* Output XDM buffer pointer */
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

/* It frees memory for speech buffers of XDMI interface.
* Assumption: Single buffers are freed for both input and output.
*/
XDAS_Int32 free_speech_buffers(
                              XDM1_SingleBufDesc *inBufs,          /* Input XDM buffer pointer */
                              XDM1_SingleBufDesc *outBufs      /* Output XDM buffer pointer */
                              )
{

    ceapp_freeContigBuf(inBufs->buf, inBufs->bufSize);
    ceapp_freeContigBuf(outBufs->buf, outBufs->bufSize);

    return (IALG_EOK);
}


/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_display_id_message                                    */
/*                                                                           */
/*  Description   : Display the ID message of the process                    */
/*                                                                           */
/*  Inputs        : XDAS_UInt8 lib_info[] (library name)                     */
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



#define IA_G711_ENC_ERROR_ACTION(ps_err_string) \
    printf(ps_err_string);\
    ceapp_exit();\
    free_speech_buffers(&inBuf, &outBuf);


/*****************************************************************************/
/*                                                                           */
/*  Function name : ceapp_encodeBuf                                          */
/*                                                                           */
/*  Description   : Actual encoding of the stream                            */
/*                                                                           */
/*  Inputs        : XDAS_Int32 argc (Arguments count)                        */
/*                  XDAS_Int *argv[] (Argument strings)                      */
/*                                                                           */
/*  Globals       : XDAS_Void * g_pv_arr_alloc_memory[MAX_MEM_ALLOCS];       */
/*                  XDAS_Int32  g_w_malloc_count;                            */
/*                  FILE *g_pf_inp, *g_pf_out;                               */
/*                                                                           */
/*  Processing    : Actual encoding of the stream                            */
/*                                                                           */
/*  Outputs       : None                                                     */
/*                                                                           */
/*  Returns       : XDAS_Int32 error_value  (Error value)                    */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Tejaswi/Vishal        Created                     */
/*                                                                           */
/*****************************************************************************/

/*
 *  ======== ceapp_encodeBuf ========
 */
XDAS_Int32 ceapp_encodeBuf(XDAS_Int32 argc, XDAS_Int8 *argv[])
{
    XDAS_Int32 bytesConsumed = 0, fread_bytes = 0;
    XDAS_Int32 k, i;
    XDAS_Int32 ret_status=0, frame_cnt = 0;

    XDAS_Int32 input_size, output_size;

    G711ENC_ITTIAM_Params  params;

    XDM1_SingleBufDesc inBuf, outBuf;
    G711ENC_ITTIAM_InArgs inArgs;
    G711ENC_ITTIAM_OutArgs outArgs;

    G711ENC_ITTIAM_DynamicParams dynParams;
    G711ENC_ITTIAM_Status    status;

    //XDAS_Int32 packetLength;
    XDAS_Int32  conv_type = ISPEECH1_PCM_COMPAND_ALAW;
    XDAS_Int32 i_out_bytes, i_total_bytes = 0;
#ifdef WAV_HEADER
    XDAS_Int32 wave_header = 0;
#endif
    XDAS_Int32  g711_encode_input_size, g711_encode_output_size, frame_length = 160;

    params.base.size = sizeof(params);
    dynParams.base.size = sizeof(dynParams);
    status.base.size = sizeof(status);
    inArgs.base.size = sizeof(inArgs);
    outArgs.base.size = sizeof(outArgs);

    /* Initializing status data buffer with zero to prevent illegal access inside CE */
    status.base.data.buf = NULL;
    status.base.data.bufSize = 0;
    status.base.data.accessMask = 0;

    /* No downmix or upmix supported so initialize */
    /* inargs variables to retain original channelMode */

    for(i = 0; i < argc; i++)
    {
        /* PCM Word Size (For single input file) */
        if(!strncmp(argv[i], "-fl:", 4))
        {
            XDAS_Int8 *pb_arg_val = argv[i] + 4;
            frame_length = atoi(pb_arg_val);
        }

        /* Frame Synch Enable/Disable */
        if(!strncmp(argv[i], "-conv:", 6))
        {
            XDAS_Int8 *pb_arg_val = argv[i] + 6;
            conv_type = atoi(pb_arg_val);
        }

    }

    /* Update the parameter fields here */
    params = G711ENC_ITTIAM_PARAMS1; /*  Set to default parameters */
	params.base.compandingLaw = conv_type;
    params.base.bitRate         = (XDAS_Int16)64;
    params.base.frameSize       = (XDAS_Int16)frame_length;

    /* Create instance handle */
    ret_status = ceapp_init(&params);
    if (ret_status != 0) {
        printf("Error in initialisation\n");
        return(0);
    }

    /* Allocate input and output buffers */
    ret_status = SPHENC1_control(encHandle, XDM_GETSTATUS, (ISPHENC1_DynamicParams *)&dynParams,
        (ISPHENC1_Status *)&status);

    if (ret_status != SPHENC1_EOK) {
        printf("CEapp-> Speech Encoder control FAILED, ret_status = %d\n", (int)ret_status);
        ceapp_exit();
        return(0);
    }

    input_size = status.base.bufInfo.minInBufSize[0];
    output_size = status.base.bufInfo.minOutBufSize[0];

    printf("Input buffer size = %d\n", input_size);
    printf("Output buffer size = %d\n", output_size);

    ret_status = allocate_speech_io_buffers(&inBuf, &outBuf, input_size, output_size);
    if (ret_status != IALG_EOK)
    {
        printf("Error in I/O buffer allocation\n");
        ceapp_exit();
        free_speech_buffers(&inBuf, &outBuf);
        return(0);
    }

    if(outBuf.bufSize >= 64)
    {
        status.base.data.buf = outBuf.buf;
        status.base.data.bufSize = outBuf.bufSize;
        ret_status = SPHENC1_control(encHandle, XDM_GETVERSION,(ISPHENC1_DynamicParams*)&dynParams,
            (ISPHENC1_Status*)&status);
        if (ret_status != SPHENC1_EOK)
        {
            printf("Error in XDM_GETVERSION\n");
            ceapp_exit();
            free_speech_buffers(&inBuf, &outBuf);
            return(0);
        }

        ia_display_id_message((XDAS_Int8 *)status.base.data.buf);
    }
    else
    {
        printf("Not enough buffer to do get version info\n");
        ceapp_exit();
        free_speech_buffers(&inBuf, &outBuf);
        return(0);
    }

    g711_encode_input_size  = frame_length;

    inArgs.base.data.buf = NULL;
    inArgs.base.data.bufSize = 0;

#ifdef PROFILE_ON
    algo_testing(TEST_MODE, OPEN);
#endif

	do{
		//XDAS_Int8 *inputBuffer = inBuf.buf;
		/*for(k = 0; k < (input_size - bytesConsumed); k++)
		{
			inputBuffer[k] = inputBuffer[k + bytesConsumed];
		}*/
		/*fread_bytes = fread(inputBuffer + (input_size) - bytesConsumed, 1,
			bytesConsumed, g_pf_inp);*/
		fread_bytes = fread(inBuf.buf, 1, g711_encode_input_size, g_pf_inp);
		g711_encode_output_size = fread_bytes>>1;

		//packetLength = packetLength - (bytesConsumed - fread_bytes);

		if(fread_bytes <= 0)
		{
			printf("Input over\n");
			break;
			/* Indicate that input is over */
			ret_status = SPHENC1_control(encHandle, XDM_FLUSH, (ISPHENC1_DynamicParams *)&dynParams,
				(ISPHENC1_Status *)&status);

			if (ret_status != IALG_EOK)
			{
				IA_G711_ENC_ERROR_ACTION("CEapp-> Speech Encoder control FAILED\n Input over\n");
				break;
			}

		}

		inBuf.bufSize = fread_bytes;
		printf("App-> Processing frame %d...\n", (int)(++frame_cnt));

#ifdef PROFILE_ON
		/* Start profiling */
		algo_testing(TEST_MODE, START);
#endif
		ret_status = SPHENC1_process(encHandle, &inBuf, &outBuf,
			(ISPHENC1_InArgs *)&inArgs, (ISPHENC1_OutArgs *)&outArgs);

#ifdef PROFILE_ON
		/* Stop profiling */
		algo_testing(TEST_MODE, STOP);
#endif
		if (ret_status != SPHENC1_EOK) {
			IA_G711_ENC_ERROR_ACTION("CEapp-> SPHENC1_process() failed\n");
			return(0);
		}

		fwrite(outBuf.buf, 1, g711_encode_output_size, g_pf_out);
		fflush(g_pf_out);

	}while (1);


#ifdef PROFILE_ON
    /* Close the testing module */
	algo_testing(TEST_MODE, CLOSE);
#endif

    ceapp_exit();
    printf("Ce app exit done\n");
    free_speech_buffers(&inBuf, &outBuf);
    printf("Speech buffers freed\n");
    return 0;
}


void print_usage()
{
    printf("\n Usage \n");
    printf("\n <exceutable> -ifile:<input_file> -ofile:<out_file> [options]\n");
    printf("\n[options] can be,");
    printf("\n[-fl:<frame_length>]");
    printf("\n[-conv:<conv_type>]");
    printf("\n\nwhere, \n  <inputfile> is the input encoded file name");
    printf("\n  <outputfile> is the output file name");
    printf("\n  <frame_length> Frame length in bytes. Default is 160");
    printf("\n  <conv_type> Conversion type");
    printf("\n    conv_type. Default ISPEECH1_PCM_COMPAND_ALAW \n");

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

    /* BUG FIX: function moved from ceapp_init() in ceapp.c */
    CERuntime_init();

#if DSP_ONLY_PLATFORM
    argc = 1;
#endif
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
            {   /* skip it */
                continue;
            }

#if DSP_ONLY_PLATFORM
            while(sscanf((char *)curr_cmd + curpos, "%s", fargv[fargc]) != 0)
#else
            while(sscanf((char *)curr_cmd + curpos, "%s", fargv[fargc]) != EOF)
#endif
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

            if(fargc < 1)   /* for blank lines etc. */
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
#ifdef USE_ITTIAM_ERROR_CODE
                            ia_error_handler(&ia_testbench_error_info,
                                (WORD8 *)"Input File", err_code);
#endif
                        }
                        file_count++;
                    }

                    if(!strncmp((const char *)fargv[i], "-ofile:", 7))
                    {
                        XDAS_Int8 *pb_arg_val = fargv[i] + 7;
                        XDAS_Int8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

                        strcat((char *)pb_output_file_name, (const char *)pb_output_file_path);
                        strcat((char *)pb_output_file_name, (const char *)pb_arg_val);

                        g_pf_out = NULL;
                        g_pf_out = fopen((const char *)pb_output_file_name, "wb");
                        if(g_pf_out == NULL)
                        {
                            err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
#ifdef USE_ITTIAM_ERROR_CODE
                            ia_error_handler(&ia_testbench_error_info,
                                (WORD8 *)"Output File", err_code);
#endif
                        }
                        file_count++;
                    }

                }
                printf("\n");
                if(file_count!=2)
                {
                    err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
#ifdef USE_ITTIAM_ERROR_CODE
                    ia_error_handler(&ia_testbench_error_info,
                        (WORD8 *)"Input or Output File", err_code);
#endif
                }


                if(err_code == 0)
                    ceapp_encodeBuf(fargc, pargv);

                if(g_pf_inp)
                    fclose(g_pf_inp);
                if(g_pf_out)
                    fclose(g_pf_out);

            }
        }
    }
    else
    {
        XDAS_Int32 i;
        XDAS_Int32 err_code = 0;
        XDAS_Int32 file_count=0;


        err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
        for(i = 1; i < argc; i++)
        {
            printf("%s ", argv[i]);

            if(!strncmp((const char *)argv[i], "-ifile:", 7))
            {
                XDAS_Int8 *pb_arg_val = argv[i] + 7;
                XDAS_Int8 pb_input_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

                err_code = 0;
                strcat((char *)pb_input_file_name, (const char *)pb_input_file_path);
                strcat((char *)pb_input_file_name, (const char *)pb_arg_val);

                g_pf_inp = NULL;
                g_pf_inp = fopen((const char *)pb_input_file_name, "rb");
                if(g_pf_inp == NULL)
                {
                    err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
#ifdef USE_ITTIAM_ERROR_CODE
                    ia_error_handler(&ia_testbench_error_info,
                        (XDAS_Int8 *)"Input File", err_code);
#endif
                }
                file_count++;
            }

            if(!strncmp((const char *)argv[i], "-ofile:", 7))
            {
                XDAS_Int8 *pb_arg_val = argv[i] + 7;
                XDAS_Int8 pb_output_file_name[IA_MAX_CMD_LINE_LENGTH] = "";

                strcat((char *)pb_output_file_name, (const char *)pb_output_file_path);
                strcat((char *)pb_output_file_name, (const char *)pb_arg_val);

                g_pf_out = NULL;
                g_pf_out = fopen((const char *)pb_output_file_name, "wb");
                if(g_pf_out == NULL)
                {
                    err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
#ifdef USE_ITTIAM_ERROR_CODE
                    ia_error_handler(&ia_testbench_error_info,
                        (XDAS_Int8 *)"Output File", err_code);
#endif
                }
                file_count++;
            }

        }

        printf("\n");
        if(file_count!=2)
        {
            err_code = IA_TESTBENCH_MFMAN_FATAL_FILE_OPEN_FAILED;
#ifdef USE_ITTIAM_ERROR_CODE
            ia_error_handler(&ia_testbench_error_info,
                (XDAS_Int8 *)"Input or Output File", err_code);
#endif
        }
#ifdef USE_ITTIAM_ERROR_CODE
        ia_error_handler(&ia_testbench_error_info,
            (XDAS_Int8 *)"Input or Output File", err_code);
#endif
        if(err_code == 0)
            ceapp_encodeBuf(argc - 1, (XDAS_Int8 **)&argv[1]);

        if(g_pf_inp)
            fclose(g_pf_inp);
        if(g_pf_out)
            fclose(g_pf_out);

    }


    return 0;
}/* end ia_param_file_process */



