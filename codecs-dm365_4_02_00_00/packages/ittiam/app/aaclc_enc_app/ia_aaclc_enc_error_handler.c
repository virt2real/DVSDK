/*****************************************************************************/
/*                                                                           */
/*                        Ittiam Audio Standards                             */
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
/*  File Name        : ia_aaclc_enc_error.h                           */
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
/* Ittiam aaclc_enc ErrorCode Definitions                             */
/*****************************************************************************/
/*****************************************************************************/
/* Class 0: API Errors
/*****************************************************************************/
/* Non Fatal Errors */
pWORD8 ppb_ia_aaclc_enc_api_non_fatal[] = {
	(pWORD8)"No Error",
	(pWORD8)"API Command not supported",
	(pWORD8)"API Command type not supported",
	(pWORD8)"Aacplus not available for current settings, reverting to plain aac"
};
/* Fatal Errors */
pWORD8 ppb_ia_aaclc_enc_api_fatal[] = {
	(pWORD8)"Invalid Memory Table Index",
	(pWORD8)"Invalid Library ID String Index",
	(pWORD8)"NULL Pointer: Memory Allocation Error",
	(pWORD8)"Invalid Config Param",
	(pWORD8)"Invalid Execute Type",
	(pWORD8)"Invalid Command",
	(pWORD8)"Memory Allocation Error: Alignment requirement not met",
	(pWORD8)"Failed to initialize downsampler",
	(pWORD8)"Failed to initialize core AAC encoder"
};
/*****************************************************************************/
/* Class 1: Configuration Errors
/*****************************************************************************/
/* Non Fatal Errors */
pWORD8 ppb_ia_aaclc_enc_config_non_fatal[] = {
	(pWORD8)"Cant use PNS, MPEG4 not defined"
};
/* Fatal Errors */
pWORD8 ppb_ia_aaclc_enc_config_fatal[] = {
	(pWORD8)"Invalid Sampling Frequency",
	(pWORD8)"Invalid Total Number of Channels",
	(pWORD8)"Invalid Stream bit rate",
	(pWORD8)"Invalid Channel mode",
	(pWORD8)"Invalid aac classic flag, use 1 or 0",
	(pWORD8)"Invalid Speech config flag, use 1 or 0",
	(pWORD8)"Invalid PCM Word Size, use 16 only",
	(pWORD8)"Invalid ADIF flag, use 1 or 0",
	(pWORD8)"Invalid ADTS flag, use 1 or 0",
	(pWORD8)"Invalid stereo preprocessing flag, use 1 or 0",
	(pWORD8)"Invalid Quality level, use 0, 1 or 2",	         
	(pWORD8)"Invalid TNS flag, use 1 or 0",	
	(pWORD8)"Invalid AAC Classic Mode cannot support PS",
	(pWORD8)"Invalid Channel Mask", 	
	(pWORD8)"Invalid AAC Classic Mode cannot support SBR",
	(pWORD8)"Invalid HE-AAC Mode cannot support PS",
	(pWORD8)"Invalid Write PCE Flag, use 1 or 0",
};

/*****************************************************************************/
/* error info structure                                                      */
/*****************************************************************************/
/* The Module's Error Info Structure */
ia_error_info_struct ia_aaclc_enc_error_info =
{
	/* The Module Name	*/
	(pWORD8)"Ittiam aaclc_enc",
	{
		/* The Class Names	*/
		(pWORD8)"API",
		(pWORD8)"Configuration",
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
/*  Function name : ia_aaclc_enc_error_handler_init                   */
/*                                                                           */
/*  Description   : Initialize the error struct with string pointers         */
/*                                                                           */
/*  Inputs        : none                                                     */
/*                                                                           */
/*  Globals       : ia_error_info_struct ia_aaclc_enc_error_info      */
/*                  pWORD8 ppb_ia_aaclc_enc_api_non_fatal             */
/*                  pWORD8 ppb_ia_aaclc_enc_api_fatal                 */
/*                  pWORD8 ppb_ia_aaclc_enc_config_non_fatal          */
/*                  pWORD8 ppb_ia_aaclc_enc_config_fatal              */
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

VOID ia_aaclc_enc_error_handler_init()
{
	/* The Message Pointers	*/
	ia_aaclc_enc_error_info.ppppb_error_msg_pointers[0][ 0] =
		ppb_ia_aaclc_enc_api_non_fatal;
	ia_aaclc_enc_error_info.ppppb_error_msg_pointers[1][ 0] =
		ppb_ia_aaclc_enc_api_fatal;
	ia_aaclc_enc_error_info.ppppb_error_msg_pointers[0][ 1] =
		ppb_ia_aaclc_enc_config_non_fatal;
	ia_aaclc_enc_error_info.ppppb_error_msg_pointers[1][ 1] =
		ppb_ia_aaclc_enc_config_fatal;
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
/*                  contexts like input_buf or output_buf e.g.  for  given   */
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
		WORD32 is_fatal		  = (((UWORD32)code & 0x8000) >> 15);
		WORD32 err_class    = (((UWORD32)code & 0x7800) >> 11);
		WORD32 err_sub_code	= (((UWORD32)code & 0x07FF));

		printf("\n");
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
