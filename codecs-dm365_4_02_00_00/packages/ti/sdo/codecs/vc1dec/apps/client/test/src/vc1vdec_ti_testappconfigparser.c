/** ============================================================================
 *  @file   vc1vdec_ti_testappconfigparser.c
 *
 *  @path   $(PROJDIR)\src
 *
 *  @desc   This file contains parsing routines for configuration file
 *  ============================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * ===========================================================================*/

/* ---------------------compilation control switches -------------------------*/


/*******************************************************************************
*                  INCLUDE FILES
*******************************************************************************/
/* -------------------- system and platform files ----------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <std.h>
//#include <xdas.h>
#include <xdc/std.h>
//#include <tistdtypes.h>

#include <ti/xdais/xdas.h>

/*----------------------program files ----------------------------------------*/
#include "vc1vdec_ti_testappdec.h"

/*******************************************************************************
*          EXTERNAL REFERENCES NOTE : only use if not found in header file
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/


/*-----------------------function prototypes ---------------------------------*/

/*******************************************************************************
*            PUBLIC DECLARATIONS Defined here, used elsewhere
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/

#ifdef _TMS320C6X
extern far sTokenMapping sTokenMap[] ;
#else
extern sTokenMapping sTokenMap[] ;
#endif

/*-----------------------function prototypes ---------------------------------*/
/*******************************************************************************
*              PRIVATE DECLARATIONS Defined here, used only here
*******************************************************************************/
/*-----------------------data declarations -----------------------------------*/
static XDAS_Int8 buf[20000];
/*-----------------------function prototypes ---------------------------------*/

/*-----------------------macros ----------------------------------------------*/

/** ============================================================================
* @const  MAX_ITEMS_TO_PARSE
*
* @desc   Specifies the maximum items needed to be parsed
*
* ==============================================================================
*/
#define MAX_ITEMS_TO_PARSE  1000

/* =============================================================================
 *  @func     GetConfigFileContent
 *
 *  @desc     Reads the configuration file content in a buffer and returns the
 *            address of the buffer
 *
 *  @param    fname
 *            Pointer to name of file
 *
 *  @return   XDAS_Int8
 *            Returns address to buffer
 *  ============================================================================
 */
static XDAS_Int8 *GetConfigFileContent (FILE *fname)
{
  XDAS_Int32 FileSize;

  if (0 != fseek (fname, 0, SEEK_END))
  {
    return 0;
  }

  FileSize = ftell (fname);
  if (FileSize < 0 || FileSize > 20000)
  {
    return 0;

  }
  if (0 != fseek (fname, 0, SEEK_SET))
  {
    return 0;
  }

    /*------------------------------------------------------------------------*/
  /* Note that ftell() gives us the file size as the file system sees it.     */
  /* The actual file size, as reported by fread() below will be often smaller */
  /* due to CR/LF to CR conversion and/or control characters after the dos    */
    /*EOF marker in the file.                                                 */
    /*------------------------------------------------------------------------*/
  FileSize = fread (buf, 1, FileSize, fname);
  buf[FileSize] = '\0';
  fclose (fname);
  return buf;
}




/* =============================================================================
 *  @func     ParameterNameToMapIndex
 *
 *  @desc     Returns the index number from sTokenMap[] for a given parameter
 *            name
 *
 *  @param    s
 *            Parameter name string
 *
 *  @return   XDAS_Int32
 *            The index number if the string is a valid parameter name,
 *            -1 for error
 *  ============================================================================
 */
static XDAS_Int32 ParameterNameToMapIndex (xdc_Char *s)
{
  XDAS_Int32 i = 0;

  while (sTokenMap[i].tokenName != NULL)
    if (0==strcmp (sTokenMap[i].tokenName, s))
      return i;
    else
      i++;
  return -1;
}



/* =============================================================================
 *  @func     ParseContent
 *
 *  @desc     Parses the character array buf and writes global variable input,
 *            which is defined in configfile.h.  This hack will continue to be
 *            necessary to facilitate the addition of new parameters through the
 *            sTokenMap[] mechanism-Need compiler-generated addresses in
 *            sTokenMap.
 *
 *  @param    buf[IN]
 *            buffer to be parsed
 *
 *  @param    bufsize[IN]
 *            size of buffer
 *
 *  @return   XDAS_Int32
 *            status ( PASS/ FAIL)
 *  ============================================================================
*/
static XDAS_Int32 ParseContent (xdc_Char *buf, XDAS_Int32 bufsize)
{

  xdc_Char *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 MapIdx;
  XDAS_Int32 item = 0;
  XDAS_Int32 InString = 0, InItem = 0;
  xdc_Char *p = buf;
  xdc_Char *bufend = &buf[bufsize];
  XDAS_Int32 IntContent;
  XDAS_Int32 i;
  FILE *fpErr = stderr;

    /*------------------------------------------------------------------------*/
    /* Stage one: Generate an argc/argv-type list in items[], without comments*/
    /* and whitespace.                                                        */
    /* This is context insensitive and could be done most easily with lex(1). */
    /*------------------------------------------------------------------------*/

  while (p < bufend)
  {
    switch (*p)
    {
      case 13:
        p++;
                break;
            case '#':     /* Found comment*/
                *p = '\0';  /* Replace '#' with '\0' in case of comment */
                /*Immediately following integer or string*/
                /* Skip till EOL or EOF, whichever comes first*/
        while (*p != '\n' && p < bufend)
          p++;
        InString = 0;
        InItem = 0;
        break;
      case '\n':
        InItem = 0;
        InString = 0;
        *p++='\0';
        break;
            case ' ':
            case '\t':              /* Skip whitespace, leave state unchanged*/
        if (InString)
          p++;
                else
                {   /* Terminate non-strings once whitespace is found*/
          *p++ = '\0';
          InItem = 0;
        }
        break;

            case '"':               /* Begin/End of String*/
        *p++ = '\0';
        if (!InString)
        {
          items[item++] = p;
          InItem = ~InItem;
        }
        else
                    InItem = 0;
                InString = ~InString; /* Toggle*/
        break;

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

  for (i=0; i<item; i+= 3)
  {
    if (0 > (MapIdx = ParameterNameToMapIndex (items[i])))
        {
            fprintf(fpErr, " \nParameter Name '%s' not recognized. ", items[i]);
      return -1 ;
    }
    if (strcmp ("=", items[i+1]))
        {
            fprintf(fpErr, " \nfile: '=' expected as the second token in \
                                                                   each line.");
      return -1 ;
    }
    sscanf (items[i+2], "%d", &IntContent) ;
    * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
  }
    return 0 ;
}




/* =============================================================================
 *  @func     readparamfile
 *
 *  @desc     This routine is used to read the params file.
 *
 *  @param    fname
 *            Pointer to name of file
 *
 *  @return   XDAS_Int32
 *            status ( PASS/ FAIL)
 *  ============================================================================
 */
XDAS_Int32 readparamfile(FILE * fname)
{
  xdc_Char *FileBuffer = NULL ;
  XDAS_Int32 retVal ;
    /*read the content in a buffer*/
  FileBuffer = (xdc_Char *)GetConfigFileContent(fname);
  if(FileBuffer)
  {
    retVal  = ParseContent(FileBuffer,strlen(FileBuffer));
    return retVal ;
  }
  else
    return -1;
}
 /*!
  *! Revision History
  *! ================
  *!
  *! 23-Apr-2007   Uday: File name and other changes to meet coding guidelines
  *!                    requirements.
 */

