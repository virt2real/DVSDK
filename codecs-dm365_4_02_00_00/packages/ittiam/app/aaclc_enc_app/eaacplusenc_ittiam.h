/*
//============================================================================
//
//    FILE NAME : EAACPLUSENC_ITTIAM.h
//
//    ALGORITHM : EAACPLUSENC
//
//    VENDOR    : ITTIAM
//
//    TARGET DSP: C64x
//
//    PURPOSE   : Interface for the EAACPLUSENC_ITTIAM module; ITTIAM's implementation
//                of the IEAACPLUSENC interface.
//
//    Component Wizard for eXpressDSP Version 1.33.00 Auto-Generated Component
//
//    Number of Inputs : 0
//    Number of Outputs: 0
//
//    Creation Date: Tue - 04 July 2006
//    Creation Time: 02:46 PM
//
//============================================================================
*/

#ifndef EAACPLUSENC_ITTIAM_
#define EAACPLUSENC_ITTIAM_

/*#if defined(WIN32) || defined(IA_MVLINUX)
#include "ia_type_def.h"
#include "xdais.h"
#else
#include <std.h>
#include <ialg.h>
#include <xdas.h>
#endif
#include "ieaacplusenc.h"*/

/*
//============================================================================
// EAACPLUSENC_ITTIAM_IALG
//
// ITTIAM's implementation of the IALG interface for EAACPLUSENC
*/
extern IALG_Fxns EAACPLUSENCODER_ITTIAM_IALG;

/*
//============================================================================
// EAACPLUSENC_ITTIAM_IEAACPLUSENC
//
// ITTIAM's implementation of the IEAACPLUSENC interface
*/
extern IEAACPLUSENC_Fxns EAACPLUSENCODER_ITTIAM_IEAACPLUSENCODER;

/*
//============================================================================
// EAACPLUSENC_ITTIAM_init
//
// Initialize the EAACPLUSENC_ITTIAM module as a whole
*/
extern Void EAACPLUSENC_ITTIAM_init(Void);

/*
//============================================================================
// EAACPLUSENC_ITTIAM_exit
//
// Exit the EAACPLUSENC_ITTIAM module as a whole
*/
extern Void EAACPLUSENC_ITTIAM_exit(Void);

#endif	/* EAACPLUSENC_ITTIAM_ */
