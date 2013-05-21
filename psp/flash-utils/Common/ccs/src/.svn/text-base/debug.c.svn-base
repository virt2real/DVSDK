/* ---------------------------------------------------------------------------
  FILE        : debug.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred
  DESC        : Debug utility functions
 ----------------------------------------------------------------------------- */

// Standard I/O
#include <stdio.h>

// General type include
#include "tistdtypes.h"

// This module's header file
#include "debug.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/


/************************************************************
* Local Variable Definitions                                *
\***********************************************************/


/************************************************************
* Global Variable Definitions
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

// Debug print function (could use stdio or maybe UART)
Uint32 DEBUG_printString(String s)
{
  printf(s);
  return E_PASS;
}

Uint32 DEBUG_printHexInt(Uint32 i)
{
  printf("0x%X",i);
  return E_PASS;
}

Uint32 DEBUG_readString(String s)
{
  scanf("%s",s);
  return E_PASS;  
}

Uint32 DEBUG_readChar(Int8 *c)
{
  scanf("%c",c);
  return E_PASS;  
}

Uint32 DEBUG_readHexInt(Uint32 *i)
{
  Int8 s[8];
  Uint8 len,j;
  Uint32 val,baseFactor;

  for(j=0; j<8; j++)
    s[j] = 0xFF;
  
  DEBUG_readString(s);

  len = 0;
  while (len<=8)
  {
    if ( s[len] < 0x30 )
    {
      break;
    }
    else if ( s[len] >= (0x30+10) )
    {
      if (s[len] < 0x41)
      {
        break;
      }
      else if (s[len] >= (0x41+6))
      {
        if ( (s[len] < 0x61) || (s[len] >= (0x61+6)) )
        {
          break;
        }
        else
        {
          s[len] -= (0x61-10);
        }
      }
      else
      {
        s[len] -= (0x41-10);
      }
    }
    else
    {
      s[len] -= 0x30;
    }   
    len++;
  }

  if ((len == 0) || (len>8))
    return E_FAIL;

  baseFactor = 1;
  val = 0;
  for (j=0; j<len; j++)
  {
    val += s[len - j - 1] * baseFactor;
    baseFactor *= 16;
  }
  *i = val;
  
  return E_PASS;
}


/************************************************************
* Local Function Definitions                                *
************************************************************/


/***********************************************************
* End file                                                 *
***********************************************************/



