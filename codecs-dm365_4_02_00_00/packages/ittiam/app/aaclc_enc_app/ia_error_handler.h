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
/*  File Name        : ia_error_handler.h                                    */
/*                                                                           */
/*  Description      : Error related function prototypes and definitions     */
/*                                                                           */
/*  List of Functions: None                                                  */
/*                                                                           */
/*  Issues / Problems: None                                                  */
/*                                                                           */
/*  Revision History :                                                       */
/*                                                                           */
/*        DD MM YYYY       Author                Changes                     */
/*        29 07 2005       Tejaswi/Vishal        Created                     */
/*                                                                           */
/*****************************************************************************/

#ifndef __IA_ERROR_HANDLER_H__
#define __IA_ERROR_HANDLER_H__

/*****************************************************************************/
/* File includes                                                             */
/*  ia_type_def.h                                                            */
/*  ia_error_standards.h                                                     */
/*****************************************************************************/

/* these definitions are used by error handling function         */
/* the error handler will work on a structure which identifies a */
/* particular error with a module, context and error_code        */
/* within error_code, MSB identifies FATAL (1), NONFATAL (0)     */
/* next 4 ms_bs identify a class of error                        */

/*****************************************************************************/
/* Constant hash defines                                                     */
/*****************************************************************************/
#define IA_ERROR_NON_FATAL_IDX		0x0
#define IA_ERROR_FATAL_IDX			0x1

#define IA_ERROR_CLASS_0		0x0
#define IA_ERROR_CLASS_1		0x1
#define IA_ERROR_CLASS_2		0x2
#define IA_ERROR_CLASS_3		0x3
#define IA_ERROR_CLASS_4		0x4
#define IA_ERROR_CLASS_5		0x5
#define IA_ERROR_CLASS_6		0x6
#define IA_ERROR_CLASS_7		0x7
#define IA_ERROR_CLASS_8		0x8
#define IA_ERROR_CLASS_9		0x9
#define IA_ERROR_CLASS_A		0xA
#define IA_ERROR_CLASS_B		0xB
#define IA_ERROR_CLASS_C		0xC
#define IA_ERROR_CLASS_D		0xD
#define IA_ERROR_CLASS_E		0xE
#define IA_ERROR_CLASS_F		0xF

/* each module, hence, needs to copy the following structure          */
/* the first index is for FATAL/NONFATAL                              */
/* the second index is for the classes                                */
/* then in a module specific initialization, fill in the following    */
/* structure with the pointers to the particular error message arrays */

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/
typedef struct
{
	pWORD8 pb_module_name;
	pWORD8 ppb_class_names[16];
	WORD8 **ppppb_error_msg_pointers[2][16];
} ia_error_info_struct;

/*****************************************************************************/
/* Function prototypes                                                       */
/*****************************************************************************/
/* this error handler maps the code generated by a module to a error string */
/* pb_context is a string to specify where the module broke                 */
IA_ERRORCODE ia_error_handler(ia_error_info_struct *p_mod_err_info, 
							 WORD8 *pb_context, IA_ERRORCODE code);

/*****************************************************************************/
/* Macro functions                                                           */
/*****************************************************************************/
/* the following macro does a line job of returning back to the parent */
/* in case a fatal error occurs after calling the errorhandler         */
#define _IA_HANDLE_ERROR(p_mod_err_info, context, e) \
	if((e) != IA_NO_ERROR) \
	{ \
		ia_error_handler((p_mod_err_info), (context), (e)); \
		if((e) & IA_FATAL_ERROR) \
			return (e); \
	}
		
#endif /* __IA_ERROR_HANDLER_H__ */
