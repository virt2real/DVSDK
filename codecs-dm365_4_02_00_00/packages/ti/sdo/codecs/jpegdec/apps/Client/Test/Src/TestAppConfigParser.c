/******************************************************************************/
/*            Copyright (c) 2006 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/******************************************************************************/

/*!
********************************************************************************
  @file     TestAppConfigParser.c
  @brief    This file contains parsing routines for configuration file
  @author   Multimedia Codecs TI India
  @version  0.0 - Jan 24,2006    initial version
********************************************************************************
*/

/* standard C header files */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Client header file                                                         */
#include "tistdtypes.h"
#include "testFramework.h"


#ifndef MULTI_INSTANCE_TEST


#ifdef C6000
extern far sTokenMapping sTokenMap[] ;
#else
extern sTokenMapping sTokenMap[] ;
#endif

static XDAS_Int8 buf[20000];
//Reads the configuration file content in a buffer and returns the address 
//of the buffer
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

  /****************************************************************************/
  /* Note that ftell() gives us the file size as the file system sees it.     */
  /* The actual file size, as reported by fread() below will be often smaller */ 
  /* due to CR/LF to CR conversion and/or control characters after the dos    */
  /* EOF marker in the file.                                                  */
  /****************************************************************************/
  FileSize = fread (buf, 1, FileSize, fname);
  buf[FileSize] = '\0';
  //fclose (fname);
  return buf;
}


/*!
 ***********************************************************************
 * \brief
 *    Returns the index number from sTokenMap[] for a given parameter name.
 * \param s
 *    parameter name string
 * \return
 *    the index number if the string is a valid parameter name,         \n
 *    -1 for error
 ***********************************************************************
 */
static XDAS_Int32 ParameterNameToMapIndex (XDAS_Int8 *s)
{
  XDAS_Int32 i = 0;


  while (sTokenMap[i].tokenName != NULL)
  {
  
    if (0==strcmp (sTokenMap[i].tokenName, s))
      return i;
    else
      i++;
  }
  return -1;
}

/*!
********************************************************************************
  @fn				XDAS_Int32 ParseContent (XDAS_Int8 *buf, 
                XDAS_Int32 bufsize)
	@brief		Parses the character array buf and writes global variable input, 
            which is defined in configfile.h.  This hack will continue to be 
            necessary to facilitate the addition of new parameters through the 
            sTokenMap[] mechanism-Need compiler-generated addresses in sTokenMap

  @param  buf[IN]     buffer to be parsed
  buffer  bufsize[IN] size of buffer
	@return							status ( PASS/ FAIL)
********************************************************************************
*/

#define MAX_ITEMS_TO_PARSE  1000

static XDAS_Int32 ParseContent (XDAS_Int8 *buf, XDAS_Int32 bufsize,  sTokenMapping *sTokenMap)
{

  XDAS_Int8 *items[MAX_ITEMS_TO_PARSE];
  XDAS_Int32 MapIdx;
  XDAS_Int32 item = 0;
  XDAS_Int32 InString = 0, InItem = 0;
  XDAS_Int8 *p = buf;
  XDAS_Int8 *bufend = &buf[bufsize];
  XDAS_Int32 IntContent;
  XDAS_Int32 i;
  FILE *fpErr = stderr;

// Stage one: Generate an argc/argv-type list in items[], without comments and
// whitespace.
// This is context insensitive and could be done most easily with lex(1).

  while (p < bufend)
  {
    switch (*p)
    {
      case 13:
        p++;
        break;
      case '#':     // Found comment
        *p = '\0';  // Replace '#' with '\0' in case of comment 
                    //immediately following integer or string
        // Skip till EOL or EOF, whichever comes first
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
      case '\t':              // Skip whitespace, leave state unchanged
        if (InString)
          p++;
        else
        {                     // Terminate non-strings once whitespace is found
          *p++ = '\0';
          InItem = 0;
        }
        break;

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
      fprintf(fpErr, " \nParameter Name '%s' not recognized.. ", items[i]);
      return -1 ;

    }
	
	if (strcmp ("=", items[i+1]))
    {
      fprintf(fpErr, " \nfile: '=' expected as the second token in each line.");
      return -1 ;
    }
    sscanf (items[i+2], "%u", &IntContent) ;
	

	if(sTokenMap[MapIdx].size == sizeof(XDAS_UInt16))
    * ((XDAS_UInt16 *) (sTokenMap[MapIdx].place)) = (XDAS_UInt16)IntContent;
	else
	* ((XDAS_Int32 *) (sTokenMap[MapIdx].place)) = IntContent;
	
  }
  
  return 0 ;
}

XDAS_Int32 readparamfile(FILE * fname, sTokenMapping *sTokenMap)
{
  XDAS_Int8 *FileBuffer = NULL ;
  XDAS_Int32 retVal ; 

  //read the content in a buffer
  
  FileBuffer = GetConfigFileContent(fname);


  if(FileBuffer)
  {
    retVal  = ParseContent(FileBuffer,strlen(FileBuffer), sTokenMap);

    return retVal ;
  }
  else
    return -1;
}

#endif
/******************************************************************************/
/*            Copyright (c) 2006 Texas Instruments, Incorporated.             */
/*                           All Rights Reserved.                             */
/******************************************************************************/

