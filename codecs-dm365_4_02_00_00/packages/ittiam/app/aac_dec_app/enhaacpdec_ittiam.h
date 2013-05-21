/*
//============================================================================
//
//    FILE NAME : ENHAACPDEC_IS.h
//
//    ALGORITHM : ENHAACPDEC
//
//    VENDOR    : IS
//
//    TARGET DSP: C64x
//
//    PURPOSE   : Interface for the ENHAACPDEC_IS module; IS's implementation
//                of the IENHAACPDEC interface.
//
//    Component Wizard for eXpressDSP Version 1.33.00 Auto-Generated Component
//
//    Number of Inputs : 1
//    Number of Outputs: 1
//
//    Creation Date: Wed - 21 June 2006
//    Creation Time: 06:24 PM
//
//============================================================================
*/

#ifndef ENHAACPDEC_IS_
#define ENHAACPDEC_IS_

/* Requires the following include files #include "ienhaacpdec.h" */


/*
//============================================================================
// ENHAACPDEC_IS_IALG
//
// IS's implementation of the IALG interface for ENHAACPDEC
*/
extern IALG_Fxns ENHAACPDECODER_ITTIAM_IALG;

/*
//============================================================================
// ENHAACPDEC_ITTIAM_IENHAACPDEC
//
// IS's implementation of the IENHAACPDEC interface
*/
extern ITTIAM_ENHAACPDEC_Fxns ENHAACPDECODER_ITTIAM_IENHAACPDECODER;

/*
//============================================================================
// ENHAACPDEC_ITTIAM_init
//
// Initialize the ENHAACPDEC_ITTIAM module as a whole
*/
extern Void ENHAACPDEC_ITTIAM_init(Void);

/*
//============================================================================
// ENHAACPDEC_ITTIAM_exit
//
// Exit the ENHAACPDEC_ITTIAM module as a whole
*/
extern Void ENHAACPDEC_ITTIAM_exit(Void);

#endif	/* ENHAACPDEC_ITTIAM_ */
