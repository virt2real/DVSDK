/* --------------------------------------------------------------------------
    FILE        : ais.c                                             
    PURPOSE     : AIS parsing routines
    PROJECT     : DM648 UBL for application loading
    AUTHOR      : Daniel Allred
    DESC        : These AIS parsing routines are used by the UBL to 
                  handle the application image in AIS format that we want to 
                  boot.  The AIS image is parsed and a entry point address is
                  returned.
 ----------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file
#include "ais.h"

// DEBUG module
#include "debug.h"

// Common UTIL module
#include "util.h"


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

static Uint32 readWord(void ** addr);
static Uint32 updateCRC(Uint32 *addr, Uint32 size, Uint32 currCRC);


/************************************************************
* Local Variable Definitions                                *
\***********************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

void *AIS_parseImage(void *baseAddr)
{
  Uint16 crcEnabled = 0;
  Uint16 done = 0;
  Uint32 aisCmd;
  AIS_fxnPtr branchAddress = NULL;
  Uint32 *sectionLoadAddr;
  Uint8 *byteAddr;
  Uint32 sectionSize;
  Uint32 dataWord;
  Uint32 bootEntryType;
  Uint32 bootEntryAddress;
  Uint32 bootEntryData;
  Uint32 bootEntryDelay;
  Uint32 bootEntryStartBit;
  Uint32 bootEntryStopBit;
  Uint32 bootEntryFieldMask;
  Uint32 currentCRC;
  Uint32 expectedCRC;
  Uint32 i,j;
  Int32 seek_value;
  Uint8 crcErrorCount;
  void *currAddr = baseAddr;
  
  crcErrorCount = 0;
  currentCRC = 0;

  while(!done) 
  {
    aisCmd = readWord(&currAddr);
    if ((aisCmd & AIS_PROTOCOL_COMMAND_PREFIX_MASK) != AIS_PROTOCOL_COMMAND_PREFIX)
    {
      DEBUG_printString("Invalid AIS command.\r\n");
      return NULL;
    }
    if (((aisCmd & 0xFF) > 0x5F) && ((aisCmd & 0xFF) < 0x80))
    {
      DEBUG_printString("Unsupported AIS command.\r\n");
      return NULL;
    }
    switch (aisCmd & 0xFF)
    {
      case AIS_PROTOCOL_SECTION_LOAD: //1     
      {
        sectionLoadAddr = (Uint32 *) readWord(&currAddr);
        sectionSize     = (Uint32) readWord(&currAddr);
        j = (sectionSize % 4);
         
        for(i = 0; i < (sectionSize/4); ++i) 
        {
          sectionLoadAddr[i] = readWord(&currAddr);
        }
         
        if (j != 0)
        {
          dataWord = (Uint32) readWord(&currAddr);
          byteAddr = (Uint8 *)(sectionLoadAddr+i);
          for(i = 0; i < j; ++i)
          {
            byteAddr[i] = dataWord & 0xFF;
            dataWord >>= 8;
          }
        }

        if(crcEnabled)
        {
          currentCRC = updateCRC((Uint32 *)(&sectionLoadAddr), 4, currentCRC);
          currentCRC = updateCRC((Uint32 *)(&sectionSize), 4, currentCRC);
          currentCRC = updateCRC((Uint32 *) sectionLoadAddr, sectionSize, currentCRC);
        }
        break;
      }
                     
      case AIS_PROTOCOL_REQUEST_CRC:  //2
      {    
        expectedCRC = (Uint32) readWord(&currAddr);
        if(expectedCRC != currentCRC)
        {
          seek_value = (int)( (Uint32) readWord(&currAddr) );
          currentCRC=0;
          crcErrorCount++;
          if( crcErrorCount >= AIS_PROTOCOL_MAX_NUM_CRC_ERRORS )
          {
            DEBUG_printString("Too Many CRC Errors.\r\n");
            return NULL;
          }      
          currAddr = (void *)(((Uint32)currAddr) + (int)seek_value);
        }
        else
        {
          seek_value = (int)( (Uint32) readWord(&currAddr) );
          currentCRC=0;      
          crcErrorCount = 0;      
        }        
        break;
      }
                      
      case AIS_PROTOCOL_ENABLE_CRC:   //3   
      {
        crcEnabled = TRUE;
        currentCRC = 0;
        break;
      }
                    
      case AIS_PROTOCOL_DISABLE_CRC:  //4  
      {
        crcEnabled = FALSE;
        currentCRC = 0;
        break;
      }
      
      case AIS_PROTOCOL_JUMP:         //5
      {
        branchAddress = (AIS_fxnPtr)readWord(&currAddr);
        (*branchAddress)();
        break;
      }
                     
      case AIS_PROTOCOL_JUMP_CLOSE:   //6
      {
        branchAddress = (AIS_fxnPtr)readWord(&currAddr);
        done = AIS_BOOT_COMPLETE;
        break;
      }
      
      case AIS_PROTOCOL_SET:          //7          
      {
        bootEntryType       = readWord(&currAddr);
        bootEntryAddress    = readWord(&currAddr);
        bootEntryData       = readWord(&currAddr);
        bootEntryDelay      = readWord(&currAddr);
      
        switch(bootEntryType & 0xFF)
        {
          case BOOT_TABLE_TYPE_Byte:
            *((Uint8 *)bootEntryAddress) = (Uint8)bootEntryData;
            break;
          case BOOT_TABLE_TYPE_Short:
            *((Uint16 *)bootEntryAddress) = (Uint16)bootEntryData;
            break;
          case BOOT_TABLE_TYPE_Int:
            *((Uint32 *)bootEntryAddress) = (Uint32)bootEntryData;
            break;
          case BOOT_TABLE_TYPE_Field:
            bootEntryStartBit = ( bootEntryType & 0xFF00 ) >> 8;
            bootEntryStopBit  = ( bootEntryType & 0xFF0000 ) >> 16;
            bootEntryFieldMask = ~(((1<<(bootEntryStopBit-bootEntryStartBit+1))-1)<<bootEntryStartBit);
            *((Uint32 *)bootEntryAddress) &= bootEntryFieldMask;
            *((Uint32 *)bootEntryAddress)  |= (bootEntryData<<bootEntryStartBit);            
            break;
          case BOOT_TABLE_TYPE_Bits:
            bootEntryStartBit = ( bootEntryType & 0xFF00 ) >> 8;
            bootEntryStopBit  = ( bootEntryType & 0xFF0000 ) >> 16;
            bootEntryFieldMask = ~(((1<<(bootEntryStopBit-bootEntryStartBit+1))-1)<<bootEntryStartBit);
            bootEntryFieldMask &= *((Uint32 *)bootEntryAddress);
            bootEntryFieldMask |= (bootEntryData<<bootEntryStartBit);
            *((Uint32 *)bootEntryAddress) = bootEntryFieldMask;
            break;
        }
        if(bootEntryDelay)
          UTIL_waitLoop(bootEntryDelay);
        break;        
      }
                     
      case AIS_PROTOCOL_STARTOVER:    //8
      {
        currentCRC = 0;  
        currAddr = baseAddr;
        break;
      }
                                 
      case AIS_PROTOCOL_COMPSECTION_LOAD: //9 
      {
        sectionLoadAddr = (Uint32 *) readWord(&currAddr);
        sectionSize     = (Uint32)   readWord(&currAddr);
        j = (sectionSize % 4);

        for(i = 0; i < sectionSize/4; ++i)
        {
          sectionLoadAddr[i] = readWord(&currAddr);
        }
        if (sectionSize %4 != 0)
        {
          dataWord = readWord(&currAddr);
          byteAddr = (Uint8 *)(sectionLoadAddr+i);
          for(i = 0; i< sectionSize % 4; ++i)
          {
            byteAddr[i] = dataWord & 0xFF;
            dataWord >>= 8;
          }
        }
  
        if(crcEnabled)
        {
          currentCRC = updateCRC((Uint32 *)(&sectionLoadAddr), 4, currentCRC);
          currentCRC = updateCRC((Uint32 *)(&sectionSize), 4, currentCRC);
          currentCRC = updateCRC((Uint32 *) sectionLoadAddr, sectionSize, currentCRC);
        }
      }
      
      case AIS_PROTOCOL_SECTION_FILL:  //10 
      {
        sectionLoadAddr = (Uint32 *) readWord(&currAddr);
        sectionSize     = (Uint32)   readWord(&currAddr);
        j = (sectionSize % 4);

        dataWord = readWord(&currAddr);
                   
        for(i = 0; i < sectionSize/4; ++i) 
        {
          sectionLoadAddr[i] = dataWord;
        }
                
        if (j != 0) 
        {
          dataWord = readWord(&currAddr);
          byteAddr = (Uint8 *)(sectionLoadAddr+i);
          for(i = 0; i < j; ++i)
          {
            byteAddr[i] = dataWord & 0xFF;
            dataWord >>= 8;
          }
        }
          
        if(crcEnabled)
        {
          currentCRC = updateCRC((Uint32 *)(&sectionLoadAddr), 4, currentCRC);
          currentCRC = updateCRC((Uint32 *)(&sectionSize), 4, currentCRC);
          currentCRC = updateCRC((Uint32 *) sectionLoadAddr, sectionSize, currentCRC);
        }
        break;
      }
                      
      case AIS_PROTOCOL_PING_DEVICE:   //11
      {
        break;
      }

      case AIS_PROTOCOL_GET:   //12
      {
        bootEntryType       = readWord(&currAddr);
        bootEntryAddress    = readWord(&currAddr);
        bootEntryData       = readWord(&currAddr);
        bootEntryDelay      = readWord(&currAddr);
        // Not supported for the UBL
        break;
      }
      
      case AIS_PROTOCOL_FUNCTION_EXECUTE:     //13
      {
        dataWord            = readWord(&currAddr);
        for (i = 0; i< ((dataWord & 0xFFFF0000)>>16); i++)
        {
          readWord(&currAddr);
        }
        // Not supported for the UBL
        break;
      }
       
      default:  
      {
        DEBUG_printString("Unsupported AIS command.\r\n");
        done = AIS_BOOT_COMPLETE;  
      }
    }
  }               
  return branchAddress;
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 readWord(void ** addr)
{
  Uint32 retVal = NULL;
  retVal = *((Uint32*) *addr);
  *addr = (void *) ( ((Uint32)(*addr)) + 4);
  return retVal;
}

static Uint32 updateCRC(Uint32 *addr, Uint32 size, Uint32 currCRC)
{
  return NULL;
}


/************************************************************
* End file                                                  *
************************************************************/

/* --------------------------------------------------------------------------
    HISTORY
        v1.00  -  DJA  -  15-Nov-2007
           Initial release 
 ----------------------------------------------------------------------------- */



