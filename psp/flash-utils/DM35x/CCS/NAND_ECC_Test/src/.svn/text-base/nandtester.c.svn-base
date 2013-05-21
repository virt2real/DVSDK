/* --------------------------------------------------------------------------
    FILE        : nandtester.c 				                             	 	        
    PURPOSE     : NAND writer main program
    PROJECT     : Dm644x CCS NAND Flashing Utility
    AUTHOR      : Daniel Allred
    DESC	      : CCS-based utility to flash the DM644x in preparation for 
                  NAND booting
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "nandtester.h"

// NAND driver include
#include "nand.h"

// Misc. utility function include
#include "util.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/

extern __FAR__ Uint32 ASYNC_CS2_START, ASYNC_CS2_END;

/************************************************************
* Local Macro Declarations                                  *
************************************************************/
#define GOOD_PAGE (0)
#define BAD_PAGE  (1)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/


/************************************************************
* Local Function Declarations                               *
************************************************************/

static Uint32 nandtester(void);
static Uint32 LOCAL_testECC(NAND_InfoHandle hNandInfo, Uint32 numErr, Uint32 *bytePos, Uint32 *bitPos, Uint8 *srcBuf);


/************************************************************
* Global Variable Definitions
************************************************************/

// Global variables for page buffers 
static Uint8* gNandTx;
static Uint8* gNandRx;


/************************************************************
* Global Function Definitions                               *
************************************************************/

void main( void )
{
  int status;

  // Init memory alloc pointer
  UTIL_setCurrMemPtr(0);

  // System init
  if (DEVICE_init() !=E_PASS)
  {
    exit();
  }

  // Execute the NAND flashing
  status = nandtester();

  if (status != E_PASS)
  {
    DEBUG_printString("\n\nNAND ECC test failed!\r\n");
  }
  else
  {
    DEBUG_printString( "\n\nNAND ECC test passed!\r\n" );
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 nandtester()
{
  Uint32 numPagesUBL;

  NAND_InfoHandle  hNandInfo;

  FILE	*fPtr;
  Uint8	*ublPtr;
  Int32	ublFileSize = 0,ublAllocSize = 0;
  Int8  fileName[256];
  Int32 i=0;
  Uint32 numErr, bytePos[4], bitPos[4];

  DEBUG_printString("Starting NAND_ECC_Test.\r\n");

  // Initialize NAND Flash
  hNandInfo = NAND_open((Uint32)&ASYNC_CS2_START, (Uint8) DEVICE_emifBusWidth() );
  
  if (hNandInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NAND Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Read the file from host
  DEBUG_printString("Enter the binary UBL file Name (enter 'none' to skip) :\r\n");
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

    // Read file size
    fseek(fPtr,0,SEEK_END);
    ublFileSize = ftell(fPtr);

    if(ublFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
	  }

	  numPagesUBL = 1;

    //We want to allocate an even number of pages.
    ublAllocSize = numPagesUBL * hNandInfo->dataBytesPerPage;

    // Setup pointer in RAM
    ublPtr = (Uint8 *) UTIL_allocMem(ublAllocSize);

	  for (i=0; i<ublAllocSize; i++)
	    ublPtr[i]=0x00;

    fseek(fPtr,0,SEEK_SET);

    if (hNandInfo->dataBytesPerPage != fread(ublPtr, 1, hNandInfo->dataBytesPerPage, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }

	  fclose (fPtr);
    
    DEBUG_printString("How many bits of error do you want to test?\r\n");
    DEBUG_readHexInt(&numErr);
    
    if (numErr > 4)
    {
      printf("\tERROR: Too many - should be less than 5 .\r\n");
		  return E_FAIL;
    }
    
    for (i = 0; i< numErr; i++)
    {
      DEBUG_printString("Enter byte position for error no. ");
      DEBUG_printHexInt(i+1);
      DEBUG_printString("? \r\n");
      DEBUG_readHexInt(&bytePos[i]);
      
      DEBUG_printString("Enter bit position for error no. ");
      DEBUG_printHexInt(i+1);
      DEBUG_printString("? \r\n");
      DEBUG_readHexInt(&bitPos[i]);
    }
    

	  if (LOCAL_testECC(hNandInfo,numErr,bytePos,bitPos,ublPtr) != E_PASS)
	  {
		  printf("\tERROR: Write failed.\r\n");
		  return E_FAIL;
	  }
  }
  
	return E_PASS;
}

// Generic function to write a UBL or Application header and the associated data
static Uint32 LOCAL_testECC(NAND_InfoHandle hNandInfo, Uint32 numErr, Uint32 *bytePos, Uint32 *bitPos, Uint8 *srcBuf)
{
  Uint32     blockNum;
  Uint32     i;
  Uint8      spareBytesTx[256],spareBytesRx[256];

  gNandTx = (Uint8 *) UTIL_allocMem(NAND_MAX_PAGE_SIZE);
  gNandRx = (Uint8 *) UTIL_allocMem(NAND_MAX_PAGE_SIZE);
  

  for (i=0; i<NAND_MAX_PAGE_SIZE; i++)  
  {
    gNandTx[i]=srcBuf[i];
	  gNandRx[i]=0xff;
  }	
	
  // Start in block #2
  blockNum = 1;

NAND_WRITE_RETRY:
  if (blockNum >= hNandInfo->numBlocks)
	{
    return E_FAIL;
  }
	DEBUG_printString("Attempting to start test in block number ");
	DEBUG_printHexInt(blockNum);
	DEBUG_printString(".\r\n");

	// Unprotect all needed blocks of the Flash 
	if (NAND_unProtectBlocks(hNandInfo,blockNum,1) != E_PASS)
	{
		blockNum++;
		DEBUG_printString("Unprotect failed.\r\n");
		goto NAND_WRITE_RETRY;
	}
		    
	// Erase the block where the header goes and the data starts
  if (NAND_eraseBlocks(hNandInfo,blockNum,1) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Erase failed\n");
    goto NAND_WRITE_RETRY;
  }

  NAND_reset(hNandInfo);

  DEBUG_printString((Uint8 *)"Writing test data to Block ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString((Uint8 *)", Page ");
  DEBUG_printHexInt(GOOD_PAGE);
  DEBUG_printString((Uint8 *)"\r\n");
  
  // Write data to page #0
	if (NAND_writePage(hNandInfo, blockNum, GOOD_PAGE, gNandTx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Write failed\n");
    NAND_reset(hNandInfo);
		goto NAND_WRITE_RETRY;
  }
		
	UTIL_waitLoop(200);

	// Verify the page just written
  if (NAND_verifyPage(hNandInfo, blockNum, GOOD_PAGE, gNandTx, gNandRx) != E_PASS)
  {
    DEBUG_printString("Verify failed. Attempting to clear page\n");
    NAND_reset(hNandInfo);
    NAND_eraseBlocks(hNandInfo,blockNum,1);
    
    blockNum++;
    NAND_reset(hNandInfo);

		goto NAND_WRITE_RETRY;
  }
  
  // Get good ECC from the spare bytes
  if (NAND_readSpareBytesOfPage(hNandInfo, blockNum, GOOD_PAGE, spareBytesRx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Read spare bytes failed\n");
    NAND_reset(hNandInfo);
		goto NAND_WRITE_RETRY;
  }
  
  // Copy good data and good sparebytes data
  for(i=0; i<512; i++)
  {
    gNandTx[i+512] = gNandRx[i];
  }
  for(i=0; i<16; i++)
  {
    spareBytesRx[i+16] = spareBytesRx[i];
  }
  for(i=0; i<hNandInfo->spareBytesPerPage; i++)
  {
    spareBytesTx[i] = spareBytesRx[i];
  }

  // Cause bit errors in second set of 512 bytes and 
  for (i=0; i<numErr; i++)
  {
    gNandTx[512+bytePos[i]] ^= (0x1<<bitPos[i]);
  }
  
  DEBUG_printString((Uint8 *)"Writing errored data to Block ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString((Uint8 *)", Page ");
  DEBUG_printHexInt(BAD_PAGE);
  DEBUG_printString((Uint8 *)"\r\n");

  // Write data without writing spare bytes
  if (NAND_writePageWithSpareBytes(hNandInfo, blockNum, BAD_PAGE, gNandTx, spareBytesTx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Write failed\n");
    NAND_reset(hNandInfo);
		goto NAND_WRITE_RETRY;
  }

  if (NAND_readSpareBytesOfPage(hNandInfo, blockNum, BAD_PAGE, spareBytesRx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Read spare bytes failed\n");
    NAND_reset(hNandInfo);
		goto NAND_WRITE_RETRY;
  }

  for(i=0; i<hNandInfo->spareBytesPerPage; i++)
  {
    if (spareBytesTx[i] != spareBytesRx[i])
    {
      blockNum++;
      DEBUG_printString("Verify spare bytes failed\n");
      NAND_reset(hNandInfo);
		  goto NAND_WRITE_RETRY;
    }
  }

  DEBUG_printString((Uint8 *)"Reading errored data from Block ");
  DEBUG_printHexInt(blockNum);
  DEBUG_printString((Uint8 *)", Page ");
  DEBUG_printHexInt(BAD_PAGE);
  DEBUG_printString((Uint8 *)"\r\n");
  
  // Here is where the error correction should happen
  if (NAND_readPage(hNandInfo, blockNum, BAD_PAGE, gNandRx) != E_PASS)
  {
    blockNum++;
    DEBUG_printString("Read failed\n");
    NAND_reset(hNandInfo);
		goto NAND_WRITE_RETRY;
  }
  
  // Compare what came out of the read page against what was actually stored
  // Differences should indicate corrections that happened
  for(i=0; i<hNandInfo->dataBytesPerPage; i++)
  {
    if (gNandTx[i] != gNandRx[i])
    {
      Uint32 j = 0;
      Uint8 testVal;
      // Assume a correction took place
      DEBUG_printString("Correction at byte position ");
      DEBUG_printHexInt(i-512);
      DEBUG_printString(".\r\n");
      testVal = gNandTx[i] ^ gNandRx[i];
      while (((testVal >> j) & 0x1) != 0x1)
      {
        j++;
      }
            
      if ((testVal >> j) != 0x1)
      {
        DEBUG_printString("Correction Failed.\r\n");
        return E_FAIL;
      }
      else
      {
        DEBUG_printString("Correction at bit position ");
        DEBUG_printHexInt(j);
        DEBUG_printString(".\r\n");
      }
    }
  }
  
  NAND_protectBlocks(hNandInfo);

  return E_PASS;
}


/***********************************************************
* End file                                                 
************************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 02-Nov-2007
      Initial release
-------------------------------------------------------------------------- */

