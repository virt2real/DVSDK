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
/*  File Name        : ia_error_standards.h                                  */
/*                                                                           */
/*  Description      : Error code type definition                            */
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

#ifndef __IA_ERROR_STANDARDS_H__
#define __IA_ERROR_STANDARDS_H__

/*****************************************************************************/
/* File includes                                                             */
/*  ia_type_def.h                                                            */
/*****************************************************************************/

/*****************************************************************************/
/* Type definitions                                                          */
/*****************************************************************************/
typedef WORD32 IA_ERRORCODE;

/*****************************************************************************/
/* Constant hash defines                                                     */
/*****************************************************************************/
#define IA_NO_ERROR					0x00000000
/* error handling 'AND' definition */
#define IA_FATAL_ERROR				0x80000000

#endif /* __IA_ERROR_STANDARDS_H__ */
