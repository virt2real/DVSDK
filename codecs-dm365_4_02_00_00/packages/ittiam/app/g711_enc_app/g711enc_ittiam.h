/*****************************************************************************/
/*                                                                           */
/*                            G.711 CODEC                                        */
/*                  ITTIAM SYSTEMS PVT LTD, BANGALORE                        */
/*                           COPYRIGHT(C) 2006                               */
/*                                                                           */
/*  This program  is  proprietary to  Ittiam  Systems  Private  Limited  and */
/*  is protected under Indian  Copyright Law as an unpublished work. Its use */
/*  and  disclosure  is  limited by  the terms  and  conditions of a license */
/*  agreement. It may not be copied or otherwise  reproduced or disclosed to */
/*  persons outside the licensee's organization except in accordance with the*/
/*  terms  and  conditions   of  such  an  agreement.  All  copies  and      */
/*  reproductions shall be the property of Ittiam Systems Private Limited and*/
/*  must bear this notice in its entirety.                                   */
/*                                                                           */
/*****************************************************************************/

/*****************************************************************************/
/*                                                                           */
/*  File Name         : ig711encode_ittiam.h                                 */
/*                                                                           */
/*  Description       : vtable (function pointers) declared here             */
/*                                                                           */
/*  List of Functions : Just data types defined                              */
/*                                                                           */
/*  Issues / Problems : None                                                 */
/*                                                                           */
/*  Revision History  :                                                      */
/*                                                                           */
/*         DD MM YYYY   Author(s)       Changes (Describe the changes made)  */
/*         22 06 2006   Kumar          Initial                               */
/*                                                                           */
/*****************************************************************************/


/*
 *  ======== g711encode_ittiam.h ========
 *  Interface for the G711ENCODE_ITTIAM module; ITTIAM's implementation 
 *  of the IG711ENCODE interface
 */
#ifndef G711ENCODE_ITTIAM_
#define G711ENCODE_ITTIAM_

/*****************************************************************************/
/* Constant Macros                                                           */
/*****************************************************************************/
/* None */

/*****************************************************************************/
/* Function Macros                                                           */
/*****************************************************************************/
/* None */

/*****************************************************************************/
/* Typedefs                                                                  */
/*****************************************************************************/
/* None */

/*****************************************************************************/
/* Enums                                                                     */
/*****************************************************************************/
/* None */

/*****************************************************************************/
/* Structure                                                                 */
/*****************************************************************************/

/*
 *  ======== G711ENCODE_ITTIAM_IALG ========
 *  ITTIAM's implementation of the IALG interface for G711ENCODE
 */

#ifdef _TMS320C6400
extern far IALG_Fxns G711ENCODER_ITTIAM_IALG;
#else
extern IALG_Fxns G711ENCODER_ITTIAM_IALG;
#endif

/*
 *  ======== G711ENCODE_ITTIAM_IG711ENCODE ========
 *  ITTIAM's implementation of the IG711ENCODE interface
 */

extern
#ifdef G711_ENCODER_LIB_EXPORTS
__declspec(dllexport)
#endif

#ifdef G711_ENCODER_LIB_IMPORTS
__declspec(dllimport)
#endif

#ifdef _TMS320C6400
	far G711ENC_ITTIAM_Fxns G711ENCODER_ITTIAM_IG711ENCODER;
#else
	G711ENC_ITTIAM_Fxns G711ENCODER_ITTIAM_IG711ENCODER;
#endif

#endif  /* G711ENCODE_ITTIAM_ */
