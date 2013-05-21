/*
 * dvtbAACEncExtParams.h
 *
 * XDM1.0 AACHE Extended parameter Structure Definitions
 *
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/
 * 
 * 
 *  Redistribution and use in source and binary forms, with or without 
 *  modification, are permitted provided that the following conditions 
 *  are met:
 *
 *    Redistributions of source code must retain the above copyright 
 *    notice, this list of conditions and the following disclaimer.
 *
 *    Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the 
 *    documentation and/or other materials provided with the   
 *    distribution.
 *
 *    Neither the name of Texas Instruments Incorporated nor the names of
 *    its contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 *  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
 *  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
 *  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
 *  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
 *  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
 *  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
 *  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 *  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 *  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
 *  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
 *  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
*/

#ifndef AACENC_EXT_PARAMS_H
#define AACENC_EXT_PARAMS_H

typedef enum
{
	AACENC_OBJ_TYP_LC = 2, /*!< AAC Low Complexity  */
	AACENC_OBJ_TYP_HEAAC = 5, /*!< HE AAC              */
	AACENC_OBJ_TYP_PS = 29
/*!< AAC LC + SBR + PS   */
} AACENC_OBJ_TYP;

typedef enum
{
	AACENC_TT_RAW = 0, /*!< Raw Output Format   */
	AACENC_TT_ADIF = 1, /*!< ADIF File Format    */
	AACENC_TT_ADTS = 2
/*!< ADTS File Format    */
} AACENC_TRANSPORT_TYPE;

typedef enum
{
	AACENC_BR_MODE_VBR_1 = 1, /*!< VBR Mode 1            */
	AACENC_BR_MODE_VBR_2 = 2, /*!< VBR Mode 2            */
	AACENC_BR_MODE_VBR_3 = 3, /*!< VBR Mode 3            */
	AACENC_BR_MODE_VBR_4 = 4, /*!< VBR Mode 4            */
	AACENC_BR_MODE_VBR_5 = 5
/*!< VBR Mode 5            */
} AACENC_VBR_MODE;

typedef enum
{
	AACENC_FALSE = 0, /*!< To indicate False  */
	AACENC_TRUE = 1
/*!< To indicate True   */
} AACENC_BOOL_TYPE;

typedef struct IAACENC_Status
{
	IAUDENC1_Status audenc_status; /*!< Basic audio encoder status struct */
	AACENC_OBJ_TYP outputObjectType; /*!< Output Object Type LC/HE/HEv2    */
	AACENC_TRANSPORT_TYPE outFileFormat; /*!< Output File Format            */
} IAACENC_Status;

typedef struct IAACENC_Params
{
	IAUDENC1_Params audenc_params; /*!< Generic encoder creation parameters */
	AACENC_OBJ_TYP outObjectType; /*!< Output Object Type LC/HE/HEv2       */
	AACENC_TRANSPORT_TYPE outFileFormat; /*!< Output File Format             */
	AACENC_BOOL_TYPE useTns; /*!< Flag for activating TNS feature     */
	AACENC_BOOL_TYPE usePns; /*!< Flag for activating PNS feature     */
	AACENC_BOOL_TYPE downMixFlag; /*!< downmixing Flag                   */
	AACENC_VBR_MODE bitRateMode; /*!< Flag for CBR / VBR coding          */
	/*! Replicated from Dynamic Params */
	XDAS_Int32 ancRate; /*!< ancillary Data Rate                 */
} IAACENC_Params;

typedef struct IAACENC_DynamicParams
{
	IAUDENC1_DynamicParams audenc_dynamicparams;
	/*!< generic encoder dynamic parameters  */
	/* For RESET Command */
	AACENC_BOOL_TYPE useTns; /*!< Flag for activating TNS feature     */
	AACENC_BOOL_TYPE usePns; /*!< Flag for activating PNS feature     */
	AACENC_BOOL_TYPE downMixFlag; /*!< downmixing Flag                  */
	AACENC_OBJ_TYP outObjectType; /*!< Output Object Type LC/HE/HEv2     */
	AACENC_TRANSPORT_TYPE outFileFormat; /*!< Output File Format            */
	AACENC_BOOL_TYPE ancFlag; /*!< ancillary data Flag                */
	XDAS_Int32 ancRate; /*!< ancillary Data Rate                */
} IAACENC_DynamicParams;

typedef struct IAACENC_InArgs
{
	IAUDENC1_InArgs audenc_inArgs; /*!< Generic Audio Encoder input Params */
} IAACENC_InArgs;

typedef struct IAACENC_OutArgs
{
	IAUDENC1_OutArgs audenc_outArgs; /*!< Generic Audio Encoder output param */
} IAACENC_OutArgs;
#endif
