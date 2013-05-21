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
/*  File Name         : g711_decode_ittiam.h                                 */
/*                                                                           */
/*  Description       : extern vtable ITTIAM_G711DEC_FXNS declared here      */
/*                                                                           */
/*  List of Functions : None                                                 */
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
 *  ======== g711decode_ittiam.h ========
 *  Interface for the G711DECODE_ITTIAM module; ITTIAM's implementation 
 *  of the IG711DECODE interface
 */
#ifndef G711DECODE_ITTIAM_
#define G711DECODE_ITTIAM_

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
 *  ======== G711DECODE_ITTIAM_IALG ========
 *  ITTIAM's implementation of the IALG interface for G711DECODE
 */

#ifdef _TMS320C6400
extern far IALG_Fxns G711DECODER_ITTIAM_IALG;
#else
extern IALG_Fxns G711DECODER_ITTIAM_IALG;
#endif

/*
 *  ======== G711DECODE_ITTIAM_IG711DECODE ========
 *  ITTIAM's implementation of the IG711DECODE interface
 */

extern
#ifdef G711_DECODER_LIB_EXPORTS
__declspec(dllexport)
#endif

#ifdef G711_DECODER_LIB_IMPORTS
__declspec(dllimport)
#endif

#ifdef _TMS320C6400
	far G711DEC_ITTIAM_Fxns G711DECODER_ITTIAM_IG711DECODER;
#else
	G711DEC_ITTIAM_Fxns G711DECODER_ITTIAM_IG711DECODER;
#endif

#endif  /* G711DECODE_ITTIAM_ */
