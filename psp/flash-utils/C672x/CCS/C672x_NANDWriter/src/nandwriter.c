/* --------------------------------------------------------------------------
    FILE        : nandwriter.c 				                             	 	        
    PROJECT     : C672x CCS NAND Flashing Utility
    AUTHOR      : Daniel Allred
    DESC	      : CCS-based utility to flash the C672x in preparation for 
                  NAND booting
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header file 
#include "nandwriter.h"

// NAND driver include
#include "nand.h"
#include "device_nand.h"

// Misc. utility function include
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

static Uint32 nandwriter(void);
static Uint32 LOCAL_writeData(NAND_InfoHandle hNandInfo, Uint8 *srcBuf, Uint32 totalPageCnt);


/************************************************************
* Global Variable Definitions
************************************************************/

//#pragma DATA_SECTION(DDRStart,".ddrram");
//VUint32 __FAR__ DDRStart;

#pragma DATA_SECTION(NANDStart,".aemif_mem");
VUint32 __FAR__ NANDStart;

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
  status = nandwriter();

  if (status != E_PASS)
  {
    DEBUG_printString("\n\nNAND flashing failed!\r\n");
  }
  else
  {
    DEBUG_printString("\n\nNAND boot preparation was successful!\r\n");
  }
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static Uint32 nandwriter()
{
  Uint32 numPagesAIS;

  NAND_InfoHandle  hNandInfo;

  FILE	*fPtr;
  Uint8	*aisPtr;
  Int32	aisFileSize = 0,aisAllocSize = 0;
  Int8  fileName[256];
  Int32 i=0;

  DEBUG_printString("Starting C672x_NANDWriter.\r\n");

#ifdef PADK_FPGA_IN_USE
#define FPGA_CONFIG_REGISTER (*(Uint32 *)0x900060D0)
  // Setup PADK FPGA for this test
  AEMIF->A1CR |= 0x00000001;
	FPGA_CONFIG_REGISTER |= 0x800;
  AEMIF->A1CR &= 0xFFFFFFFC;
#endif

  AEMIF->A1CR = 0x3FFFFFFC;

  // Initialize NAND Flash
  hNandInfo = NAND_open((Uint32)&NANDStart, (Uint8) DEVICE_emifBusWidth());
  
  if (hNandInfo == NULL)
  {
    DEBUG_printString( "\tERROR: NAND Initialization failed.\r\n" );
    return E_FAIL;
  }

  // Read the file from host
  DEBUG_printString("Enter the binary AIS file name to flash (enter 'none' to skip) :\r\n");
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
    aisFileSize = ftell(fPtr);

    if(aisFileSize == 0)
    {
      DEBUG_printString("\tERROR: File read failed.. Closing program.\r\n");
      fclose (fPtr);
      return E_FAIL;
	  }

	  numPagesAIS = 0;
	  while ( (numPagesAIS * hNandInfo->dataBytesPerPage)  < aisFileSize )
	  {
		  numPagesAIS++;
	  }

    //We want to allocate an even number of pages.
    aisAllocSize = numPagesAIS * hNandInfo->dataBytesPerPage;

    // Setup pointer in RAM
    aisPtr = (Uint8 *) UTIL_allocMem(aisAllocSize);

    // Clear memory
	  for (i=0; i<aisAllocSize; i++)
	    aisPtr[i]=0xFF;

    // Go to start of file
    fseek(fPtr,0,SEEK_SET);

    // Read file data
    if (aisFileSize != fread(aisPtr, 1, aisFileSize, fPtr))
    {
      DEBUG_printString("\tWARNING: File Size mismatch.\r\n");
    }

    // Close file
	  fclose (fPtr);

    // Write the file data to the NAND flash
	  if (LOCAL_writeData(hNandInfo, aisPtr, numPagesAIS) != E_PASS)
	  {
		  printf("\tERROR: Write failed.\r\n");
		  return E_FAIL;
	  }

  }



	return E_PASS;
}

// Generic function to write a UBL or Application header and the associated data
static Uint32 LOCAL_writeData(NAND_InfoHandle hNandInfo, Uint8 *srcBuf, Uint32 totalPageCnt)
{
  Uint32    blockNum,pageNum,pageCnt;
  Uint32    numBlks;
  Uint32    i;
  Uint8     *dataPtr;

  gNandTx = (Uint8 *) UTIL_allocMem(NAND_MAX_PAGE_SIZE);
  gNandRx = (Uint8 *) UTIL_allocMem(NAND_MAX_PAGE_SIZE);

  for (i=0; i<NAND_MAX_PAGE_SIZE; i++)  
  {
    gNandTx[i]=0xff;
	  gNandRx[i]=0xff;
  }	
	
  // Get total number of blocks needed
  numBlks = 0;
  while ( (numBlks*hNandInfo->pagesPerBlock)  < totalPageCnt )
  {
    numBlks++;
  }
  DEBUG_printString("Number of blocks needed for data: ");
  DEBUG_printHexInt(numBlks);
  DEBUG_printString("\r\n");

  // Start in block 1 (leave block 0 alone)
  blockNum = 1;

  // Unprotect all blocks of the device
	if (NAND_unProtectBlocks(hNandInfo, blockNum, (hNandInfo->numBlocks-1)) != E_PASS)
	{
		blockNum++;
		DEBUG_printString("Unprotect failed.\r\n");
    return E_FAIL;
	}

  while (blockNum < hNandInfo->numBlocks)
  {
    // Find first good block
    while (NAND_badBlockCheck(hNandInfo,blockNum) != E_PASS)
    {
      blockNum++;
    }

    // Erase the current block
    NAND_eraseBlocks(hNandInfo,blockNum,1);

	  // Start writing in page 0 of current block
    pageNum = 0;
    pageCnt = 0;

    // Setup data pointer
    dataPtr = srcBuf;

    // Start page writing loop
    do
    {
      DEBUG_printString((Uint8 *)"Writing image data to block ");
      DEBUG_printHexInt(blockNum);
      DEBUG_printString((Uint8 *)", page ");
      DEBUG_printHexInt(pageNum);
      DEBUG_printString((Uint8 *)"\r\n");

		  // Write the AIS image data to the NAND device
      if (NAND_writePage(hNandInfo, blockNum,  pageNum, dataPtr) != E_PASS)
      {
        DEBUG_printString("Write failed. Marking block as bad...\n");
        NAND_reset(hNandInfo);
        NAND_badBlockMark(hNandInfo,blockNum);
        dataPtr -=  pageNum * hNandInfo->dataBytesPerPage;
        blockNum++;
		    continue;
      }
    
      UTIL_waitLoop(200);
		
      // Verify the page just written
      if (NAND_verifyPage(hNandInfo, blockNum, pageNum, dataPtr, gNandRx) != E_PASS)
      {
        DEBUG_printString("Verify failed. Marking block as bad...\n");
        NAND_reset(hNandInfo);
        NAND_badBlockMark(hNandInfo,blockNum);
        dataPtr -=  pageNum * hNandInfo->dataBytesPerPage;
        blockNum++;
		    continue;
      }
		
      pageNum++;
      pageCnt++;
      dataPtr +=  hNandInfo->dataBytesPerPage;
  
      if (pageNum == hNandInfo->pagesPerBlock)
      {
        // A block transition needs to take place; go to next good block
        do
        {
          blockNum++;
        }
        while (NAND_badBlockCheck(hNandInfo,blockNum) != E_PASS);

        // Erase the current block
        NAND_eraseBlocks(hNandInfo,blockNum,1);

        pageNum = 0;
		  }
	  } while (pageCnt < totalPageCnt);

    NAND_protectBlocks(hNandInfo);
    break;
  }
  return E_PASS;
}


/***********************************************************
* End file                                                 
************************************************************/

/* --------------------------------------------------------------------------
  HISTORY
    v1.00 - DJA - 24-Mar-2008
      Initial release
-------------------------------------------------------------------------- */

