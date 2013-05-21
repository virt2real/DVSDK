/** ==========================================================================
 *  @file   mpeg2vdec_ti_configParser.c
 *
 *  @path   $(PROJDIR)\Src
 *
 *  @desc  This file contains parsing routines for configuration file.
 *
 *  ==========================================================================
 *  Copyright (c) Texas Instruments Inc 2006, 2007
 *
 *  Use of this software is controlled by the terms and conditions found
 *  in the license agreement under which this software has been supplied
 * =========================================================================*/


/* -------------------- compilation control switches -----------------------*/


/****************************************************************************
*   INCLUDE FILES
*****************************************************************************/

/* -------------------- system and platform files ------------------------- */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xdc/std.h>
#include <ti/xdais/xdas.h>
/* ------------------------- program files -------------------------------- */
#ifndef BASE_PARAM
#include "mpeg2vdec_ti_arm926testapp.h"
#else
#include "mpeg2vdec_ti_arm926testapp_base.h"
#endif
/****************************************************************************
*   EXTERNAL REFERENCES NOTE : only use if not found in header file
*****************************************************************************/

/* ------------------------ data declarations ----------------------------- */
extern sTokenMapping sTokenMap[] ;

/* ----------------------- function prototypes ---------------------------- */


/****************************************************************************
*   PUBLIC DECLARATIONS Defined here, used elsewhere
*****************************************************************************/

/* ----------------------- data declarations ------------------------------ */

/* ---------------------- function prototypes ----------------------------- */


/****************************************************************************
*   PRIVATE DECLARATIONS Defined here, used only here
*****************************************************************************/

/* ---------------------- data declarations ------------------------------- */
static XDAS_Int8 buf[20000];

/* --------------------- function prototypes ------------------------------ */


/* ---------------------------- macros ------------------------------------ */


/* ===========================================================================
 *  @func   GetConfigFileContent()
 *
 *  @desc   Reads the configuration file content in a buffer and returns the
 *          address
 *          .
 *  @param  FILE *fname
 *          File pointer of config file.
 *
 *  @return One line of data fron the config file other wise zero.
 * ===========================================================================
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

    /* Note that ftell() gives us the file size as the file system sees it.
     * The actual file size, as reported by fread() below will be often
     * smaller due to CR/LF to CR conversion and/or control characters after
     * the dos EOF marker in the file.
     */
    FileSize = fread (buf, 1, FileSize, fname);
    buf[FileSize] = '\0';
    fclose (fname);
    return buf;
} /* GetConfigFileContent() */



/* ===========================================================================
 *  @func   ParameterNameToMapIndex()
 *
 *  @desc   Returns the index number from sTokenMap[] for a given parameter
 *          name
 *          .
 *  @param  XDAS_Int8 *s
 *          name string.
 *
 *  @return Index number if the string is a valid parameter name,
 *          -1 for error
 * ===========================================================================
 */
static XDAS_Int32 ParameterNameToMapIndex(XDAS_Int8 *s)
{
    XDAS_Int32 i = 0;

    while(sTokenMap[i].tokenName != NULL)
    {
        if(0 == strcmp((const char *)(sTokenMap[i].tokenName),(const char *) s))
        {
            return i;
        }
        else
        {
            i++;
        }
    }
    return -1;
} /* ParameterNameToMapIndex() */



/* ===========================================================================
 *  @func   ParseContent()
 *
 *  @desc   Parses the character array buf and writes global variable input,
 *          which is defined in configfile.h.  This hack will continue to be
 *          necessary to facilitate the addition of new parameters through the
 *          sTokenMap[] mechanism-Need compiler-generated addresses in
 *          sTokenMap
 *          .
 *  @param  buf
 *          buffer to be parsed.
 *
 *  @param  bufsize
 *          size of buffer.
 *
 *  @return status ( PASS/ FAIL)
 * ===========================================================================
 */
#define MAX_ITEMS_TO_PARSE  1000
static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize)
{

    XDAS_Int8  *items[MAX_ITEMS_TO_PARSE];
    XDAS_Int32 MapIdx;
    XDAS_Int32 item     = 0;
    XDAS_Int32 InString = 0;
    XDAS_Int32 InItem   = 0;
    XDAS_Int8  *p       = buf;
    XDAS_Int8  *bufend  = &buf[bufsize];
    XDAS_Int32 IntContent;
    XDAS_Int32 i;
    FILE       *fpErr   = stderr;

    /* Stage one: Generate an argc/argv-type list in items[], without comments
     * and whitespace.
     * This is context insensitive and could be done most easily with lex(1).
     */

    while (p < bufend)
    {
        switch (*p)
        {
            case 13:
                    p++;
                    break;
            case '#':
                    /* Found comment Replace '#' with '\0' in case of comment
                     * immediately following integer or string Skip till
                     *  EOL or EOF, whichever comes first
                     */
                    *p = '\0';
                    while (*p != '\n' && p < bufend)
                    {
                        p++;
                    }
                    InString = 0;
                    InItem = 0;
                    break;
            case '\n':
                    InItem   = 0;
                    InString = 0;
                    *p++='\0';
                    break;
            case ' ':
            case '\t':           /* Skip whitespace, leave state unchanged  */
                    if (InString)
                    {
                        p++;
                    }
                    else
                    {     /* Terminate non-strings once whitespace is found */
                        *p++ = '\0';
                        InItem = 0;
                    }
                    break;

            case '"':               /* Begin/End of String                  */
                    *p++ = '\0';
                    if (!InString)
                    {
                        items[item++] = p;
                        InItem = ~InItem;
                    }
                    else
                    {
                        InItem = 0;
                    }
                    InString = ~InString; /* Toggle                         */
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

    for(i=0 ; i<item ; i += 3)
    {
        if(0 < (MapIdx = ParameterNameToMapIndex(items[i])))
        {
            /*fprintf(fpErr,"\nParameter Name '%s' not recognized", items[i]);
            return -1 ;*/
        }
        if (strcmp ("=", (const char *)(items[i+1])))
        {
            fprintf(fpErr,
                     "\nfile:'=' expected as the second token in each line.");
            return -1 ;
        }
        sscanf ((const char *)(items[i+2]), "%d", &IntContent) ;
        * ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
    }
    return 0 ;
}  /* ParseContent () */



/* ===========================================================================
 *  @func   readparamfile()
 *
 *  @desc   Parses the config parametr file and stores the value in global
 *          structure (sTokenMapping sTokenMap).
 *          .
 *  @param  FILE * fname
 *          Confile parameter file pointer.
 *
 *  @return status ( PASS/ FAIL)
 * ===========================================================================
 */
XDAS_Int32 readparamfile(FILE * fname)
{
    XDAS_Int8 *FileBuffer = NULL ;
    XDAS_Int32 retVal ;

    /* read the content in a buffer                                         */
    FileBuffer = GetConfigFileContent(fname);
    if(FileBuffer)
    {
        retVal  = ParseContent(FileBuffer,strlen((const char *)FileBuffer));
        return retVal ;
    }
    else
    {
        return -1;
    }
} /* readparamfile() */



/*!
 *! Revision History
 *! ================
 *! 16-Aug-2007   Kumar    :  Incorporated code review comments.
 *! 01-Jul-2006   Prashanth:  Created.
 *!
 */
