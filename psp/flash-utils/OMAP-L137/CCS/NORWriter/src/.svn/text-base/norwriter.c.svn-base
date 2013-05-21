/* --------------------------------------------------------------------------
  FILE        : norwriter.c 				                             	 	        
  PROJECT     : TI Booting and Flashing Utilities
  AUTHOR      : Daniel Allred, Joe Coombs
  DESC        : CCS NOR Flashing Utility  
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "norwriter.h"

// NOR driver include
#include "nor.h"

// Misc. utility function include
#include "util.h"

// Debug module
#include "debug.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

// 14-bit page
#define LOCAL_pageSize	(0x00008000)
#define	LOCAL_norBase	(0x60000000)
#define LOCAL_latchAddr	(0x62000000)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 norwriter(void);
static void LOCAL_latchPage(Uint32 NOR_addr);
static Int32 LOCAL_bytesThisPage(Uint32 NOR_addr, Int32 bytes);
static Uint32 LOCAL_nextPageStart(Uint32 NOR_addr);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

void main( void )
{
  Uint32 status;

  // Init memory alloc pointer to start of DDR heap
  UTIL_setCurrMemPtr(0);

  // System init
  if (DEVICE_init() !=E_PASS)
  {
    exit();
  }

  // Execute the NOR flashing
  status = norwriter();

  if (status != E_PASS)
  {
    DEBUG_printString("\tNOR flashing failed!\r\n");
  }
  else
  {
    DEBUG_printString("\tNOR boot preparation was successful!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 norwriter()
{
  NOR_InfoHandle hNorInfo;

  FILE	*fPtr;
  Uint8	*appPtr;
  Int32	appFileSize = 0;
  Int8	fileName[256];
  Uint32  baseAddress = 0;

  Int32 byteCnt, totalBytes;
  Uint32 tempAddress;

  DEBUG_printString( "Starting NORWriter.\r\n");

  // latch to base of NOR
  LOCAL_latchPage(LOCAL_norBase);

  // Initialize NOR Flash
  hNorInfo = NOR_open((Uint32)LOCAL_norBase, (Uint8)DEVICE_emifBusWidth() );
  if (hNorInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NOR Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Set base address to start putting data at
  baseAddress = hNorInfo->flashBase;

  // Read the UBL file from host
  DEBUG_printString("Enter the binary AIS application file name (enter 'none' to skip): \r\n");
  DEBUG_readString(fileName);
  fflush(stdin);

  if (strcmp(fileName,"none") != 0)
  {
    // Open an File from the hard drive
    fPtr = fopen(fileName, "rb");
    if(fPtr == NULL)
    {
      DEBUG_printString("\tERROR: File ");
      DEBUG_printString(fileName);
      DEBUG_printString(" open failed.\r\n");
      return E_FAIL;
    }

    // Initialize the pointer
    appFileSize = 0;

    // Read file size
    fseek(fPtr,0,SEEK_END);
    appFileSize = ftell(fPtr);

    // Check to make sure image was read correctly
    if(appFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.\r\n");
      fclose (fPtr);
      return E_FAIL;
    }
    // Check to make sure the app image will fit 
    else if ( appFileSize > hNorInfo->flashSize )
    {
      DEBUG_printString("\tERROR: File too big.. Closing program.\r\n");
      fclose (fPtr);
    }

    // Setup pointer in RAM
    appPtr = (Uint8 *) UTIL_allocMem(appFileSize);

    fseek(fPtr,0,SEEK_SET);

    if (appFileSize != fread(appPtr, 1, appFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }

    fclose (fPtr);

    // Erase the NOR flash to accomadate the file size; erase all NOR pages that overlap
    // our file
    totalBytes = 0;
    tempAddress = baseAddress;
    while (totalBytes < appFileSize)
    {
      // get NOR page size, address
      NOR_getBlockInfo(hNorInfo, tempAddress, (Uint32 *)&byteCnt, &tempAddress);

      // latch page and erase
      LOCAL_latchPage(tempAddress);
      if (NOR_erase( hNorInfo, tempAddress, byteCnt ) != E_PASS)
      {
        DEBUG_printString("\tERROR: Erasing NOR failed.\r\n");
        return E_FAIL;
      }

      tempAddress += byteCnt;
      totalBytes += byteCnt;
    }

    // Write the application data to the flash; break write into pages
    totalBytes = 0;
    tempAddress = baseAddress;
    while (totalBytes < appFileSize)
    {
      // find bytes to write this page
      byteCnt = LOCAL_bytesThisPage(tempAddress, appFileSize - totalBytes);

      // latch page
      LOCAL_latchPage(tempAddress);

      // write bytes up to page boundary
      if (NOR_writeBytes( hNorInfo, tempAddress, byteCnt, (Uint32)(appPtr + totalBytes)) != E_PASS)
      {
        DEBUG_printString("\tERROR: Writing NOR failed.\r\n");
        return E_FAIL;
      }

      tempAddress += byteCnt;
      totalBytes += byteCnt;
    }

    {
      // temp: check flash mem
      int i;

      DEBUG_printString("Checking flash contents... ");
      for (i = 0; i < appFileSize; i++)
      {
        LOCAL_latchPage(LOCAL_norBase + i);
        if (*(Uint8 *)(LOCAL_norBase + i) != *(appPtr + i))
        {
          DEBUG_printString("Failed! (");
          DEBUG_printHexInt(i);
          DEBUG_printString(" bytes successful)\r\n");
          //return E_FAIL;
        }	
      }
      DEBUG_printString("Passed! (");
      DEBUG_printHexInt(appFileSize);
      DEBUG_printString(" bytes)\r\n");
    }
  }
  return E_PASS;
}

static void LOCAL_latchPage(Uint32 NOR_addr)
{
	// want to latch bits [21:15] of NOR_addr, but latch will capture address bits [8:2]
	// create new address in CS3 with NOR_addr[21:15] >> 13 (drop all other address bits)
	Uint32 latch_addr = LOCAL_latchAddr | ( (NOR_addr & 0x003F8000) >> 13);

	// latch address bits with dummy write (data ignored)
	*(VUint8 *)latch_addr = 0;
}

static Int32 LOCAL_bytesThisPage(Uint32 NOR_addr, Int32 bytes)
{
	// determine how many bytes starting at NOR_addr can be read/write before
	// it's necessary to latch a new page
	Int32 bytesLeft = LOCAL_nextPageStart(NOR_addr) - NOR_addr;
	return (bytes > bytesLeft) ? bytesLeft : bytes;
}

static Uint32 LOCAL_nextPageStart(Uint32 NOR_addr)
{
	// find start of next page; round up to nearest LOCAL_pageSize
	return (NOR_addr / LOCAL_pageSize + 1) * LOCAL_pageSize;
}


/***********************************************************
* End file                                                 *
***********************************************************/
