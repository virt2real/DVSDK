/*
 ******************************************************************************
 *  
 * DM36x Based H.264 Decoder
 *
 * "DM36x Based H.264 Decoder is software module developed on TI's DM36x.
 * This module is capable of decoding H.264 bit-stream" 
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 ******************************************************************************
 */
/** ===========================================================================
* @file ih264vdec_tii.h
*
* @path $(PROJDIR)\src
*
* @brief This File contains declaration of vendor's interface 
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
#ifndef IH264VDEC_TII_
#define IH264VDEC_TII_
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
/* ----- system and platform files ----------------------------*/
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
/*
 *  ======== H264VDEC_TI_IALG ========
 *  TI's implementation of the IALG interface for H264VDEC
 */
extern IALG_Fxns H264VDEC_TI_IALG;

/*--------function prototypes ---------------------------------*/
extern IH264VDEC_Fxns H264VDEC_TI_IH264VDEC;

extern IRES_Fxns H264VDEC_TI_IRES;


#endif  /* IH264VDEC_TII */
/*!
*! Revision History
*! ================
*! 05-Jan-2006 Dinesh Kumar: Created.
*/
