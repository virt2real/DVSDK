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
/*  File Name        : ia_enhaacplus_dec_error.h                             */
/*                                                                           */
/*  Description      : Module specific error codes definitions               */
/*                                                                           */
/*  List of Functions: None                                                  */
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
#include <stdio.h>
#include "ia_type_def.h"
#include "ia_error_standards.h"
#include "ia_error_handler.h"

/*****************************************************************************/
/* Global memory constants                                                   */
/*****************************************************************************/
/*****************************************************************************/
/* Ittiam enhaacplus_dec ErrorCode Definitions                               */
/*****************************************************************************/
/*****************************************************************************/
/* Class 0: API Errors
/*****************************************************************************/
/* Non Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_api_non_fatal[] = {
	(pWORD8)"No Error",
	(pWORD8)"API Command not supported",
	(pWORD8)"API Command type not supported"
};
/* Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_api_fatal[] = {
	(pWORD8)"Invalid Memory Table Index",
	(pWORD8)"Invalid Library ID String Index",
	(pWORD8)"NULL Pointer: Memory Allocation Error",
	(pWORD8)"Invalid Config Param",
	(pWORD8)"Invalid Execute Type",
	(pWORD8)"Invalid Command",
	(pWORD8)"Memory Allocation Error: Alignment requirement not met"
};
/*****************************************************************************/
/* Class 1: Configuration Errors
/*****************************************************************************/
/* Non Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_config_non_fatal[] = {
	(pWORD8)"Invalid Output PCM Word Size. Setting to default, 16 ",
	(pWORD8)"Invalid Down-mix flag option. Setting to default, 0 ",
	(pWORD8)"Invalid 8 khz output flag option. Setting to default, 0 ",
	(pWORD8)"Invalid 16 khz output flag option. Setting to default, 0 ",
	(pWORD8)"Invalid interleave to stereo flag option. Setting to default, 1 ",
	(pWORD8)"Invalid downsample flag option. Setting to default, 0 ",
	(pWORD8)"Invalid Frame OK option. Setting to default, 1 ",
	(pWORD8)"Invalid MP4 Flag option. Setting to default, 0 ",
	(pWORD8)"Invalid maximum number of channels. limiting to between 2 and 8",
	(pWORD8)"Invalid instance for coupling channel. Setting to default 1",
	(pWORD8)"Following feature is not supported in this build. ",
	(pWORD8)"Invalid Disable Sync Flag option. Setting to default, 0 ",
	(pWORD8)"Invalid Auto SBR upsample option. Setting to default, 1 "

};
/* Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_config_fatal[] = {
	(pWORD8)"Invalid Sample rate specified for RAW decoding"
};
/*****************************************************************************/
/* Class 2: Initialization Errors
/*****************************************************************************/
/* Non Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_init_non_fatal[] = {
	(pWORD8)"Both 16 kHz and 8 kHz output config set. Giving 16 kHz output",
	(pWORD8)"Output sampling frequency is 8 kHz, 16 kHz output disabled ",
	(pWORD8)"Header not found at the beginning of input data continuing syncing"
};
/* Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_init_fatal[] = {
	(pWORD8)"AAC Decoder initialization failed",
	(pWORD8)"End of input reached during initialization",
	(pWORD8)"No. of channels in stream greater than max channels defined"
};
/*****************************************************************************/
/* Class 3: Execution Errors
/*****************************************************************************/
/* Non Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_exe_non_fatal[] = {
	(pWORD8)"ADTS syncronization is lost. Re-syncing",
	(pWORD8)"Though SBR was present in previous frame, not present in current frame (SBR turned off)",
	(pWORD8)"SBR was not present in previous frame, but it is present in current frame (SBR turned on)",
	(pWORD8)"ADTS header CRC check failed",
	(pWORD8)"Input bytes insufficient for decoding"
};
/* Fatal Errors */
pWORD8 ppb_ia_enhaacplus_dec_exe_fatal[] = {
	(pWORD8)"Error in AAC decoding",
	(pWORD8)"Invalid code book number in Huffman decoding",
	(pWORD8)"LTP data found, not supported",
	(pWORD8)"Channel coupling not supported",
//	(pWORD8)"Program Config element decoding not supported",
//	(pWORD8)"LFE decoding not supported",
	(pWORD8)"Gain control not supported",
	(pWORD8)"TNS data of range is errorneous",
	(pWORD8)"TNS data of order is greater than maximum order",	
	(pWORD8)"Element instance tag mismatch, because of new channel mode",
	(pWORD8)"Scale factor exceeds the transmitted boundary",
	(pWORD8)"Max huffman decoded value exceeded",
	(pWORD8)"The base sampling frequency has changed in ADTS header"
};

/*****************************************************************************/
/* error info structure                                                      */
/*****************************************************************************/
/* The Module's Error Info Structure */
ia_error_info_struct ia_enhaacplus_dec_error_info =
{
	/* The Module Name	*/
	(pWORD8)"Ittiam enhaacplus_dec",
	{
		/* The Class Names	*/
		(pWORD8)"API",
		(pWORD8)"Configuration",
		(pWORD8)"Initialization",
		(pWORD8)"Execution",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)""
	},
	{
        {
		    /* The Message Pointers	*/
		    ppb_ia_enhaacplus_dec_api_non_fatal, 
            ppb_ia_enhaacplus_dec_config_non_fatal, 
            ppb_ia_enhaacplus_dec_init_non_fatal, 
            ppb_ia_enhaacplus_dec_exe_non_fatal, NULL, NULL, NULL, NULL, 
		    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
        }, 
        {
		    ppb_ia_enhaacplus_dec_api_fatal, 
            ppb_ia_enhaacplus_dec_config_fatal, 
            ppb_ia_enhaacplus_dec_init_fatal, 
            ppb_ia_enhaacplus_dec_exe_fatal, NULL, NULL, NULL, NULL, 
		    NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
        }
	}
};

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_enhaacplus_dec_error_handler_init                     */
/*                                                                           */
/*  Description   : Initialize the error struct with string pointers         */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : ia_error_info_struct ia_enhaacplus_dec_error_info        */
/*                  pWORD8 ppb_ia_enhaacplus_dec_api_non_fatal               */
/*                  pWORD8 ppb_ia_enhaacplus_dec_api_fatal                   */
/*                  pWORD8 ppb_ia_enhaacplus_dec_config_non_fatal            */
/*                  pWORD8 ppb_ia_enhaacplus_dec_config_fatal                */
/*                  pWORD8 ppb_ia_enhaacplus_dec_init_non_fatal              */
/*                  pWORD8 ppb_ia_enhaacplus_dec_init_fatal                  */
/*                  pWORD8 ppb_ia_enhaacplus_dec_exe_non_fatal               */
/*                  pWORD8 ppb_ia_enhaacplus_dec_exe_fatal                   */
/*                                                                           */
/*  Processing    : Init the struct with error string pointers               */
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

VOID ia_enhaacplus_dec_error_handler_init()
{
	/* The Message Pointers	*/
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[0][ 0] =
		ppb_ia_enhaacplus_dec_api_non_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[1][ 0] =
		ppb_ia_enhaacplus_dec_api_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[0][ 1] =
		ppb_ia_enhaacplus_dec_config_non_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[1][ 1] = 
		ppb_ia_enhaacplus_dec_config_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[0][ 2] =
		ppb_ia_enhaacplus_dec_init_non_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[1][ 2] =
		ppb_ia_enhaacplus_dec_init_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[0][ 3] =
		ppb_ia_enhaacplus_dec_exe_non_fatal;
	ia_enhaacplus_dec_error_info.ppppb_error_msg_pointers[1][ 3] =
		ppb_ia_enhaacplus_dec_exe_fatal;
}

/*****************************************************************************/
/* ia_testbench ErrorCode Definitions                                        */
/*****************************************************************************/
/*****************************************************************************/
/* Class 0: Memory & File Manager Errors
/*****************************************************************************/
/* Non Fatal Errors */
/* Fatal Errors */
pWORD8 ppb_ia_testbench_mem_file_man_fatal[] = {
	(pWORD8)"Memory Allocation Error",
	(pWORD8)"File Open Failed"
};

/*****************************************************************************/
/* error info structure                                                      */
/*****************************************************************************/
/* The Module's Error Info Structure */
ia_error_info_struct ia_testbench_error_info =
{
	/* The Module Name	*/
	(pWORD8)"ia_testbench",
	{
		/* The Class Names	*/
		(pWORD8)"Memory & File Manager",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)"",
		(pWORD8)""
	},
	{
		/* The Message Pointers	*/
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL,
		NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL
	}
};

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_testbench_error_handler_init                          */
/*                                                                           */
/*  Description   : Initialize the error struct with string pointers         */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : ia_error_info_struct ia_testbench_error_info             */
/*                  pWORD8 ppb_ia_testbench_mem_file_man_fatal               */
/*                                                                           */
/*  Processing    : Init the struct with error string pointers               */
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

VOID ia_testbench_error_handler_init()
{
	/* The Message Pointers	*/
	ia_testbench_error_info.ppppb_error_msg_pointers[1][ 0] =
		ppb_ia_testbench_mem_file_man_fatal;
}

/*****************************************************************************/
/*                                                                           */
/*  Function name : ia_error_handler                                         */
/*                                                                           */
/*  Description   : Called Prints the status error code from the err_info    */
/*                                                                           */
/*  Inputs        : ia_error_info_struct *p_mod_err_info (Error info struct) */
/*                  WORD8 *pb_context (Context of error)                     */
/*                  IA_ERRORCODE code (Error code)                           */
/*                                                                           */
/*  Globals       : none                                                     */
/*                                                                           */
/*  Processing    : whenever any module calls the errorhandler,  it  informs */
/*                  it about the module for which it is called and a context */
/*                  in which it was  called  in addition to  the  error_code */
/*                  the message is displayed  based  on the  module's  error */
/*                  message  array  that maps to  the error_code the context */
/*                  gives specific info in which the error occured  e.g. for */
/*                  testbench   module,  memory  allocator   can   call  the */
/*                  errorhandler   for  memory  inavailability  in   various */
/*                  contexts like input_buf or output_buf e.g.  for  mp3_enc */
/*                  module, there can be various instances running.  context */
/*                  can be used to  identify  the  particular  instance  the */
/*                  error handler is being called for                        */
/*                                                                           */
/*  Outputs       : None                                                     */
/*                                                                           */
/*  Returns       : IA_ERRORCODE error_value  (Error value)                  */
/*                                                                           */
/*  Issues        : none                                                     */
/*                                                                           */
/*  Revision history :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Tejaswi/Vishal        Created                     */
/*                                                                           */
/*****************************************************************************/

IA_ERRORCODE ia_error_handler(ia_error_info_struct *p_mod_err_info,
							 WORD8 *pb_context, IA_ERRORCODE code)
{
	if(code == IA_NO_ERROR)
	{
		return IA_NO_ERROR;
	}
	{
		WORD is_fatal     = (((UWORD)code & 0x8000) >> 15);
		WORD err_class    = (((UWORD)code & 0x7800) >> 11);
		WORD err_sub_code = (((UWORD)code & 0x07FF));

		if(!is_fatal)
		{
			printf("non ");
		}
		printf("fatal error: ");

		if(p_mod_err_info->pb_module_name != NULL)
		{
			printf("%s: ", p_mod_err_info->pb_module_name);
		}
		if(p_mod_err_info->ppb_class_names[err_class] != NULL)
		{
			printf("%s: ", p_mod_err_info->ppb_class_names[err_class]);
		}
		if(pb_context != NULL)
		{
			printf("%s: ", pb_context);
		}
		printf("%s\n", p_mod_err_info->ppppb_error_msg_pointers
			[is_fatal][err_class][err_sub_code]);
	}
	return IA_NO_ERROR;
}

