/*
 ******************************************************************************
 *  
 * DM36x Based H.264 Decoder Test Application
 *
 * "DM36x Based H.264 Decoder Test application is software module developed on TI's DM36x.
 * This module shows XDM interface for H.264 Video Decoder.
 * Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
 * ALL RIGHTS RESERVED 
 ******************************************************************************
 */
/** ===========================================================================
* @file testappconfigparser.c
*
* @path $(PROJDIR)\src
*
* @brief This File contains function definitions for a standard implementation 
*        of a test configuration file parser. These functiosn parses the input 
*        configuration files and assigns user provided values to a global 
*        token mapping structure based on predefined tokens.
* =============================================================================
*/
/* ------compilation control switches -------------------------*/
/***************************************************************
*  INCLUDE FILES                                                
****************************************************************/
/* ----- system and platform files ----------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
#include <ti/xdais/dm/ividdec2.h>

/*-------program files ----------------------------------------*/
#include "TestAppDecoder.h"
/***************************************************************
*  EXTERNAL REFERENCES NOTE : only use if not found in header file
****************************************************************/
/*--------data declarations -----------------------------------*/
#ifdef _TMS320C6X
extern far sTokenMapping sTokenMap[] ;
#else
extern sTokenMapping sTokenMap[] ;
#endif
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PUBLIC DECLARATIONS Defined here, used elsewhere
****************************************************************/
/*--------data declarations -----------------------------------*/
/*--------function prototypes ---------------------------------*/
/****************************************************************
*  PRIVATE DECLARATIONS Defined here, used only here
****************************************************************/
/*--------function prototypes ---------------------------------*/
/*--------macros ----------------------------------------------*/
/* Maximum number of lines/parameters settigns this parser can
 * support. 
 */
#define MAX_ITEMS_TO_PARSE  1000
/* Supports Parameter files which are as big as 20,000 bytes. for
 * every input configuration setting - input stream 
 */
#define MAX_PARAM_FILE_SIZE_IN_BYTES 20000
/*--------data declarations -----------------------------------*/
/* Define a global static array into which the entire parameter 
 * file is read in
 */
static XDAS_Int8 buf[MAX_PARAM_FILE_SIZE_IN_BYTES];
/*--------function definitions---------------------------------*/
/*****************************************************************************/
/**
*@func  GetConfigFileContent()
*@brief  Reads in the entire parameter file into a global buffer and returns 
*           the buffer address.
*
*@param  FILE *fname
*           Input file pointer from where the contents are read into the buffer
*
*@return 0 - if file size is greater than MAX_PARAM_FILE_SIZE_IN_BYTES
*           or if some other file operationr elated errors occur.
*        buffer address - from where the data can be accessed.
*/
/*****************************************************************************/
static XDAS_Int8 *GetConfigFileContent (FILE *fname)
{
  XDAS_Int32 FileSize;
  /* Seek to end of file */
  if (0 != fseek (fname, 0, SEEK_END))
    return 0;
  /* Get the file size usign ftell */
  FileSize = ftell (fname);
  /* Check fi the file size is beyond set limits */
  if (FileSize < 0 || FileSize > MAX_PARAM_FILE_SIZE_IN_BYTES)
    return 0;
  /* return back the file pointer to starting of the file */
  if (0 != fseek (fname, 0, SEEK_SET))
    return 0;
/****************************************************************************/
/* Note that ftell() gives us the file size as the file system sees it.     */
/* The actual file size, as reported by fread() below will be often smaller */ 
/* due to CR/LF to CR conversion and/or control characters after the dos    */
/* EOF marker in the file.                                                  */
/****************************************************************************/
  FileSize = fread (buf, 1, FileSize, fname);
  /* Terminate the input buffer with NULL */
  buf[FileSize] = '\0';
  return buf;
}

/*****************************************************************************/
/**
*@func  ParameterNameToMapIndex()
*@brief  Returns the index number from sTokenMap[] for a given parameter name.
*
*@param  XDAS_Int8 *s
*           parameter name string
*
*@return The index number if the string is a valid parameter name,         
 *      -1 for error
*/
/*****************************************************************************/
static XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s)
{
  XDAS_Int32 i = 0;
  /* Keep searching for parameters for all elements in the Token array */
  while (sTokenMap[i].tokenName != NULL)
  {
    /* Check if the given parameters name matches with user entered param 
     * names 
     */
    if (0==strcmp((xdc_Char *)sTokenMap[i].tokenName,(xdc_Char *)s))
        /* If match is successful return the index into the Token array - whose
        * entry matches with the given parameter name */
      return i;
    else
        /* continue to the next index int he Token array */
      i++;
  }
  return -1;
}

/*****************************************************************************/
/**
*@func  ParseContent
*@brief  Parses the character array buf and writes global variable input, 
*         which is defined in configfile.h.  This hack will continue to be 
*         necessary to facilitate the addition of new parameters through the 
*         sTokenMap[] mechanism-Need compiler-generated addresses in sTokenMap
*
*@param  XDAS_Int8 *buf
*           buffer to be parsed
*
*@param XDAS_Int32 bufsize
*           size of buffer
*
*@return 0 - if successfully parsed all the elements in param file and their 
*           values read into the memory addresses given in token mappign array.
 *      -1 For any file read operation related errors or if unknown parameter
 *          names are entered or if the parameter file syntax is not in 
 *          compliance with the below implementation.
*
*@note  Please refer to the user guide for intended syntax of the parameter 
*           file -in the released sample code.
*/
/*****************************************************************************/
static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize)
{
  /* Total number of parameter initialisation lines in the file
   * this excludes comment lines and blank lines if any */
  XDAS_Int8 *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 item = 0;
  /* Index into the token map array - into which the 
   * corresponding parameter values needs to be initialised 
   * from the param file
   */
  XDAS_Int32 MapIdx;
  /* Flags - which indicate the current state of the state machine 
   * InString - indicates that buffer pointer is currently in between a valid
   * string - which inturn can contain multiple items
   * InItem - indicates that buffer pointer is within a valid item */
  XDAS_Int32 InString = 0, InItem = 0;
  /* Dynamic pointer movign allong the param file buffer byte-by-byte */
  XDAS_Int8 *p = buf;
  /* end of buffer - used for terminating the parse loop */
  XDAS_Int8 *bufend = &buf[bufsize];
  /* Parameter value read from the file */
  XDAS_Int32 IntContent;
  /* loop counter */
  XDAS_Int32 i;
  FILE *fpErr = stderr;

    /* Stage one: Generate an argc/argv-type list in items[], 
    * excluding comments and whitespaces. This is context insensitive 
    * and could be done most easily with lex(1).
    */
  while (p < bufend)
  {
    switch (*p)
    {
      /* blank space - skip the character and go to next */
      case 13:
        p++;
        break;
      /* Found a comment line skip all characters until end-of-line is found */
      case '#':
        *p = '\0';  /* Replace '#' with '\0' in case of comment 
                    immediately following the integer or string */
        // Skip till EOL or EOF, whichever comes first
        while (*p != '\n' && p < bufend)  
          p++;
        InString = 0;
        InItem = 0;
        break;
      /* end of line - skip the character and go to next - reset the
       * InItem flag to indicate that we are not in any valid item */
      case '\n':
        InItem = 0;
        InString = 0;
        *p++='\0';
        break;
      /* Whitespaces and tabs indicate end of an item - if the state machine
       *  is within a string */
      case ' ':
      case '\t':  // Skip whitespace, leave state unchanged
        if (InString)
          p++;
        else
        {                     
        /* Terminate non-strings once whitespace is found */
          *p++ = '\0';
          InItem = 0;
        }
        break;
      /* begining or end of string - toggle the string indication flag */
      case '"':               // Begin/End of String
        *p++ = '\0';
        if (!InString)
        {
          items[item++] = p;
          InItem = ~InItem;
        }
        else
          InItem = 0;
        InString = ~InString; // Toggle
        break;
      /* Any othe character is taken into the item provided the
       *  state machine is within a valid Item
       */
      default:
        if (!InItem)
        {
          items[item++] = p;
          InItem = ~InItem;
        }
        p++;
    }
  }

  item--;
  /* for all the items found - check if they correspond to any valid parameter
   * names specified by the user through token map array 
   * Note: Contigous three items are grouped into triplets. Thsi oredered 
   * triplet is used to identify the valid parameter entry in the Token map 
   * array. 
   * First item in the triplet has to eb a parameter name.
   * Second item has to be a "=" symbol
   * Third item has to be a integer value.
   * Any violation of the above order in the triplets found would lead to error 
   * condition
   */
  for (i=0; i<item; i+= 3)
  {
    /* Get the map index into the token map array - corresponding to the 
     * first item - in a item-triplet
     */
    if (0 > (MapIdx = ParameterNameToMapIndex (items[i])))
    {
      fprintf(fpErr, " \nParameter Name '%s' not recognized.. ", items[i]);
      return -1 ;

    }
    /* Assert if the second item is indeed "=" symbol */
    if (strcmp ("=", (xdc_Char *)items[i+1]))
    {
      fprintf(fpErr, " \nfile: '=' expected as the second token in each line.");
      return -1 ;
    }
    /* Convert the thrid item into an integer and populate the corresponding 
     * entry in the token map array with this value */
    sscanf ((xdc_Char *)items[i+2], "%d", &IntContent) ;
    * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
  }
  return 0 ;
}

/*****************************************************************************/
/**
*@func  readparamfile
*@brief  Reads the entire param file contents into a global buffer - which is 
*         used for parsing.
*
*@param  XDAS_Int8 *buf
*           buffer to be parsed
*
*@param FILE * fname
*           File pointer opened with the intended param file name 
*
*@return 0 - if successfully parsed all the elements in param file and their 
*           values read into the memory addresses given in token mapping array.
 *      -1 For any file read operation related errors or if unknown parameter
 *          names are entered or if the parameter file syntax is not in 
 *          compliance with the below implementation.
*
*@note  Please refer to the user guide for intended syntax of the parameter 
*           file -in the released sample code.
*/
/*****************************************************************************/
XDAS_Int32 readparamfile(FILE * fname)
{
  XDAS_Int8 *FileBuffer = NULL ;
  XDAS_Int32 retVal ; 

  /* Read entire content in a buffer */
  FileBuffer = GetConfigFileContent(fname);
 /* if the buffer address is NULL then return error */
  if(FileBuffer)
  {
    /* Parse every string into items and group them into triplets. 
     * Decode these ordered triplets into correspondign indices in the global
     * Token Map arrray provided by the user. 
     */
    retVal  = ParseContent(FileBuffer, strlen((xdc_Char *)FileBuffer));
    return retVal ;
  }
  else
    return -1;
}
/******************************************************************************/
/*            Copyright (c) 2006 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/******************************************************************************/
/*!
*! Revision History
*! ================
*! 21-Aug-2007   Vinay: Incorporated review comments.
*! 31-May-2007 Vinay M K: Modified to comply with MMCodecs 
*!                        coding guidelines.
*/
