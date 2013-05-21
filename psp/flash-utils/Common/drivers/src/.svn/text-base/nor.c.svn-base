/* --------------------------------------------------------------------------
  FILE      : nor.c 				                             	 	        
  PROJECT   : TI Boot and Flashing Utilities
  AUTHOR    : Daniel Allred
  DESC	    : Generic NOR driver file for EMIFA peripheral
-------------------------------------------------------------------------- */

// General type include
#include "tistdtypes.h"

// This module's header file  
#include "nor.h"

// Device specific CSL
#include "device.h"

// Misc. utility function include
#include "util.h"

// Project specific debug functionality
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

static VUint8 *LOCAL_flashMakeAddr (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset);
static void LOCAL_flashMakeCmd (NOR_InfoHandle hNorInfo, Uint8 cmd, void *cmdbuf);
static void LOCAL_flashWriteCmd (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset, Uint8 cmd);
static void LOCAL_flashWriteData(NOR_InfoHandle hNorInfo, Uint32 address, Uint32 data);
static Uint32 LOCAL_flashVerifyDataBuffer(NOR_InfoHandle hNorInfo, Uint32 address, void* data, Uint32 numBytes);
static Uint32 LOCAL_flashReadData(NOR_InfoHandle hNorInfo, Uint32 address, Uint32 offset);
static Bool LOCAL_flashIsSetAll (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset, Uint8 mask);
static Bool LOCAL_flashIsSetSome (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset, Uint8 mask);
static NOR_Data LOCAL_flashReadCFIBytes (NOR_InfoHandle hNorInfo, Uint32 offset, Uint8 numBytes);
static Bool LOCAL_flashCFIIsEqual (NOR_InfoHandle hNorInfo, Uint32 offset, Uint8 val);
// Flash Identification and discovery
static Uint32   LOCAL_flashQueryCFI( NOR_InfoHandle hNorInfo );


// Empty commands for when neither command set is used
static Uint32   Unsupported_Erase(NOR_InfoHandle hNorInfo, Uint32 address);
static Uint32   Unsupported_Write(NOR_InfoHandle hNorInfo, Uint32 address, VUint32 data);
static Uint32   Unsupported_BufferWrite(NOR_InfoHandle hNorInfo, Uint32, VUint8[], Uint32 );
static Uint32   Unsupported_ID(NOR_InfoHandle hNorInfo);
static void     Unsupported_SoftReset(NOR_InfoHandle hNorInfo);


//Intel pointer-mapped commands
static Uint32   Intel_Erase( NOR_InfoHandle hNorInfo, VUint32 blkAddr);
static Uint32   Intel_Write( NOR_InfoHandle hNorInfo, Uint32 address, VUint32 data );
static Uint32   Intel_BufferWrite( NOR_InfoHandle hNorInfo, Uint32 address, VUint8 data[], Uint32 numBytes );
static Uint32   Intel_ID( NOR_InfoHandle hNorInfo );
static void     Intel_SoftReset(NOR_InfoHandle hNorInfo);
// Misc. Intel commands
static Uint32   LOCAL_IntelClearLock(NOR_InfoHandle hNorInfo, Uint32 blkAddr);
static Uint32   LOCAL_IntelSetLock(NOR_InfoHandle hNorInfo, Uint32 blkAddr);
static Uint32   LOCAL_IntelLockStatusCheck(NOR_InfoHandle hNorInfo);
static void     LOCAL_IntelClearStatus(NOR_InfoHandle hNorInfo);
static void     LOCAL_IntelWaitForStatusComplete(NOR_InfoHandle hNorInfo);


//AMD pointer-mapped commands
static Uint32   AMD_Erase(NOR_InfoHandle hNorInfo, Uint32 blkAddr);
static Uint32   AMD_Write(NOR_InfoHandle hNorInfo, Uint32 address, VUint32 data );
static Uint32   AMD_BufferWrite(NOR_InfoHandle hNorInfo, Uint32 address, VUint8 data[], Uint32 numBytes );
static Uint32   AMD_ID(NOR_InfoHandle hNorInfo);
static void     AMD_SoftReset(NOR_InfoHandle hNorInfo);
// Misc. AMD commands
static void     LOCAL_AMDPrefixCommands(NOR_InfoHandle hNorInfo);
static void     LOCAL_AMDWriteBufAbortReset(NOR_InfoHandle hNorInfo);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions                               *
************************************************************/

const NOR_FxnsTable AMD_NOR_FxnsTable = 
{
  &(AMD_Write),
  &(AMD_BufferWrite),
  &(AMD_Erase),
  &(AMD_ID),
  &(AMD_SoftReset)
};

const NOR_FxnsTable Intel_NOR_FxnsTable = 
{
  &(Intel_Write),
  &(Intel_BufferWrite),
  &(Intel_Erase),
  &(Intel_ID),
  &(Intel_SoftReset)
};

const NOR_FxnsTable Unsupported_NOR_FxnsTable = 
{
  &(Unsupported_Write),
  &(Unsupported_BufferWrite),
  &(Unsupported_Erase),
  &(Unsupported_ID),
  &(Unsupported_SoftReset)
};


/************************************************************
* Global Function Definitions                               *
************************************************************/

NOR_InfoHandle NOR_open(Uint32 baseCSAddr, Uint8 busWidth)
{
  NOR_InfoHandle hNorInfo;

  // Alloc the main NOR structue
  hNorInfo = (NOR_InfoHandle) UTIL_callocMem(sizeof(NOR_InfoObj));
  if (!hNorInfo)
    return NULL;

  // Set NOR flash base address
  hNorInfo->flashBase = baseCSAddr;
    
  //Get the CSOffset ( can be 0 through (CSL_DEVICE_NUMBER_CE_REGION -1) )
  hNorInfo->CSOffset = 0;
  while (hNorInfo->CSOffset < DEVICE_EMIF_NUMBER_CE_REGION)
  {
    if ( hNorInfo->flashBase == 
         (DEVICE_EMIF_FIRST_CE_START_ADDR + 
         (DEVICE_EMIF_INTER_CE_REGION_SIZE * hNorInfo->CSOffset) ) )
    {
      break;
    }
    hNorInfo->CSOffset++;
  }

  if (hNorInfo->CSOffset == DEVICE_EMIF_NUMBER_CE_REGION)
    return NULL;

  // Set width to 8 or 16
  hNorInfo->busWidth = busWidth;

  // Try both Intel and AMD resets ( we don't know yet which we need)
  AMD_SoftReset(hNorInfo);
  Intel_SoftReset(hNorInfo);

  // Perform CFI Query
  DEBUG_printString("CFI Query...");
  if (LOCAL_flashQueryCFI(hNorInfo) != E_PASS)
  {
    DEBUG_printString("failed.\r\n");
    return NULL;
  }
    
  // Setup function pointers
  DEBUG_printString("passed.\r\nNOR Initialization:\r\n");
    
  DEBUG_printString("\tCommand Set: ");    
  switch (hNorInfo->commandSet)
  {
    case AMD_BASIC_CMDSET:
    case AMD_EXT_CMDSET:
      hNorInfo->hNorFxns   = (NOR_FxnsHandle) &AMD_NOR_FxnsTable;
/*      Flash_Erase          = &AMD_Erase;
      Flash_BufferWrite    = &AMD_BufferWrite;
      Flash_Write          = &AMD_Write;
      Flash_ID             = &AMD_ID;*/
      DEBUG_printString("AMD\r\n");
      break;
    case INTEL_BASIC_CMDSET:
    case INTEL_EXT_CMDSET:
      hNorInfo->hNorFxns   = (NOR_FxnsHandle) &Intel_NOR_FxnsTable;
/*      Flash_Erase          = &Intel_Erase;
      Flash_BufferWrite    = &Intel_BufferWrite;
      Flash_Write          = &Intel_Write;
      Flash_ID             = &Intel_ID;*/
      DEBUG_printString("Intel\r\n");
      break;
    default:
      hNorInfo->hNorFxns   = NULL;
/*      Flash_Write          = &Unsupported_Write;
      Flash_BufferWrite    = &Unsupported_BufferWrite;
      Flash_Erase          = &Unsupported_Erase;
      Flash_ID             = &Unsupported_ID;*/
      DEBUG_printString("Unknown\r\n");
      break;
  }
  if ((*(hNorInfo->hNorFxns->id))(hNorInfo) != E_PASS)
//  if ( (*Flash_ID)(hNorInfo) != E_PASS)
  {
    DEBUG_printString("NOR ID failed.\r\n");
    return NULL;
  }
        
  DEBUG_printString("\tManufacturer: ");
  switch(hNorInfo->manfID)
  {
    case AMD:
      DEBUG_printString("AMD");
      break;
    case FUJITSU:
      DEBUG_printString("FUJITSU");
      break;
    case INTEL:
      DEBUG_printString("INTEL");
      break;
    case MICRON:
      DEBUG_printString("MICRON");
      break;
    case SAMSUNG:
      DEBUG_printString("SAMSUNG");
      break;
    case SHARP:
      DEBUG_printString("SHARP");
      break;
    default:
      DEBUG_printString("Unknown");
      break;
  }
  DEBUG_printString("\r\n");
  DEBUG_printString("\tSize: ");
  DEBUG_printHexInt(hNorInfo->flashSize>>20);
  DEBUG_printString(" MB\r\n");
    
  return hNorInfo;    
}

// Get info on block address and sizes
Uint32 NOR_getBlockInfo(NOR_InfoHandle hNorInfo, Uint32 address, Uint32* blockSize, Uint32* blockAddr)
{
  Int32 i;
  Uint32 currRegionAddr, nextRegionAddr;
        
  currRegionAddr = (Uint32) hNorInfo->flashBase;
  if ((address < currRegionAddr) || (address >= (currRegionAddr+hNorInfo->flashSize)))
  {
    return E_FAIL;
  }
    
  for(i=0; i< (hNorInfo->numberRegions); i++)
  {
    nextRegionAddr = currRegionAddr + (hNorInfo->blockSize[i] * hNorInfo->numberBlocks[i]);
    if ( (currRegionAddr <= address) && (nextRegionAddr > address) )
    {
      *blockSize = hNorInfo->blockSize[i];
      *blockAddr = address & (~((*blockSize) - 1));
      break;
    }
    currRegionAddr = nextRegionAddr;
  }
  return E_PASS;
}

//Global Erase NOR Flash
Uint32 NOR_globalErase(NOR_InfoHandle hNorInfo)
{
  return NOR_erase( hNorInfo, (VUint32) hNorInfo->flashBase, (VUint32) hNorInfo->flashSize );
}

void NOR_reset(NOR_InfoHandle hNorInfo)
{
  hNorInfo->hNorFxns->reset(hNorInfo);
}

// Erase Flash Block
Uint32 NOR_erase(NOR_InfoHandle hNorInfo, VUint32 start_address, VUint32 size)
{
  Uint32 i;
	VUint32 addr  = start_address;
	VUint32 range = start_address + size;
	Uint32 blockSize, blockAddr;
	
	DEBUG_printString("Erasing the NOR Flash\r\n");
	
  while (addr < range)
  {
    if (NOR_getBlockInfo(hNorInfo, addr, &blockSize, &blockAddr) != E_PASS)
    {
      DEBUG_printString("Address out of range");
      return E_FAIL;
    }
		
		//Increment to the next block
    if ((*(hNorInfo->hNorFxns->erase))(hNorInfo, blockAddr) != E_PASS)
//    if ( (*Flash_Erase)(hNorInfo, blockAddr) != E_PASS)
    {
      DEBUG_printString("Erase failure at block address ");
      DEBUG_printHexInt(blockAddr);
      DEBUG_printString("\r\n");
      return E_FAIL;
    }
    
    // Verify erase was correct
    NOR_reset(hNorInfo);  // Put NOR into read mode
    for (i=0; i< blockSize; i+=4)
    {
      if ( *((Uint32 *)(addr+i)) != 0xFFFFFFFF)
      {
        DEBUG_printString("Erase failure at address ");
        DEBUG_printHexInt((addr+i));
        DEBUG_printString(".\r\n");
        return E_FAIL;
      }
    }
    
    
    addr = blockAddr + blockSize;
	    
    // Show status messages
    DEBUG_printString("Erased through ");
    DEBUG_printHexInt(addr);
    DEBUG_printString("\r\n");

  }

  DEBUG_printString("Erase Completed\r\n");

  return(E_PASS);
}

// NOR_WriteBytes
Uint32 NOR_writeBytes( NOR_InfoHandle hNorInfo, Uint32 writeAddress, Uint32 numBytes, Uint32 readAddress)
{
  Uint32  blockSize, blockAddr;
  Int32   i;
  Uint32  retval = E_PASS;

  DEBUG_printString("Writing the NOR Flash\r\n");

  // Make numBytes even if needed
  if (numBytes & 0x00000001)
  {
    numBytes++;
  }

  if (NOR_getBlockInfo(hNorInfo, writeAddress, &blockSize, &blockAddr) != E_PASS)
  {
    DEBUG_printString("Address out of range\r\n");
    return E_FAIL;
  }

  while (numBytes > 0)
  {
    if(  (hNorInfo->bufferSize == 1) || (numBytes < hNorInfo->bufferSize) || (writeAddress & (hNorInfo->bufferSize-1)) )
    {
      if ((*(hNorInfo->hNorFxns->write))(hNorInfo, writeAddress, LOCAL_flashReadData(hNorInfo,readAddress,0) ) != E_PASS)
//      if ((*Flash_Write)(hNorInfo, writeAddress, LOCAL_flashReadData(hNorInfo,readAddress,0) ) != E_PASS)
      {
        DEBUG_printString("\r\nNormal write failed.\r\n");
        retval = E_FAIL;
      }
      else
      {
        numBytes     -= hNorInfo->busWidth;
        writeAddress += hNorInfo->busWidth;
        readAddress  += hNorInfo->busWidth;
      }
    }
    else
    {
      // Try to use buffered writes
      if((*(hNorInfo->hNorFxns->bufferWrite))(hNorInfo, writeAddress, (VUint8 *)readAddress, hNorInfo->bufferSize) == E_PASS)
//      if((*Flash_BufferWrite)(hNorInfo, writeAddress, (VUint8 *)readAddress, hNorInfo->bufferSize) == E_PASS)
      {
        numBytes -= hNorInfo->bufferSize;
        writeAddress += hNorInfo->bufferSize;
        readAddress  += hNorInfo->bufferSize;
      }
      else
      {
        DEBUG_printString("\r\nBuffered write failed. Trying normal write\r\n");
        // Try normal writes as a backup
        for(i = 0; i<(hNorInfo->bufferSize>>1); i++)
        {
          if ((*(hNorInfo->hNorFxns->write))(hNorInfo, writeAddress, LOCAL_flashReadData(hNorInfo,readAddress,0) ) != E_PASS)
//          if ((*Flash_Write)(hNorInfo, writeAddress, LOCAL_flashReadData(hNorInfo,readAddress,0) ) != E_PASS)
          {
            DEBUG_printString("\r\nNormal write also failed\r\n");
            retval = E_FAIL;
            break;
          }
          else
          {
            numBytes     -= hNorInfo->busWidth;
            writeAddress += hNorInfo->busWidth;
            readAddress  += hNorInfo->busWidth;
          }
        }
      }
    }

    // Output status info on the write operation
    if (retval == E_PASS)
    {    
      if  ( ((writeAddress & (~((blockSize>>2)-1))) == writeAddress) || (numBytes == 0) )
      {
        DEBUG_printString("NOR Write OK through ");
        DEBUG_printHexInt(writeAddress);
        DEBUG_printString(".\r\n");

        if (NOR_getBlockInfo(hNorInfo, writeAddress, &blockSize, &blockAddr) != E_PASS)
        {
          DEBUG_printString("Address out of range");
          return E_FAIL;
        }
      }
    }
    else
    {
      DEBUG_printString( "NOR Write Failed...Aborting!\r\n");
      return E_FAIL;
    }
  }
  return retval;
}


/************************************************************
* Local Function Definitions                                *
************************************************************/

static VUint8 *LOCAL_flashMakeAddr (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset)
{
  return ((VUint8 *) ( blkAddr + (offset * hNorInfo->maxTotalWidth)));
}

static void LOCAL_flashMakeCmd (NOR_InfoHandle hNorInfo, Uint8 cmd, void *cmdbuf)
{
  Int32 i;
  Uint8 *cp = (Uint8 *) cmdbuf;

  for (i = hNorInfo->busWidth; i > 0; i--)
    *cp++ = (i & (hNorInfo->chipOperatingWidth - 1)) ? 0x00 : cmd;
}

static void LOCAL_flashWriteCmd (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset, Uint8 cmd)
{
  volatile NOR_Ptr addr;
  NOR_Data cmdword;

  addr.cp = LOCAL_flashMakeAddr (hNorInfo, blkAddr, offset);
  LOCAL_flashMakeCmd ( hNorInfo, cmd, &cmdword);
  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      *addr.cp = cmdword.c;
      break;
    case BUS_16BIT:
      *addr.wp = cmdword.w;
      break;
  }
}

static void LOCAL_flashWriteData(NOR_InfoHandle hNorInfo, Uint32 address, Uint32 data)
{
  volatile NOR_Ptr pAddr;
  NOR_Data dataword;
  dataword.l = data;

  pAddr.cp = (VUint8*) address;

  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      *pAddr.cp = dataword.c;
      break;
    case BUS_16BIT:
      *pAddr.wp = dataword.w;
      break;
  }
}

/* Used only once */
static Uint32 LOCAL_flashVerifyDataBuffer(NOR_InfoHandle hNorInfo, Uint32 address, void* data, Uint32 numBytes)
{
  volatile NOR_Ptr pAddr, pData;
  VUint8* endAddress;
		
  pData.cp = (VUint8*) data;
  pAddr.cp = (VUint8*) address;
  endAddress =(VUint8*)(address+numBytes);
  while (pAddr.cp < endAddress)
  {
    switch (hNorInfo->busWidth)
    {
      case BUS_8BIT:
        if ( (*pAddr.cp++) != (*pData.cp++) )
          return E_FAIL;
        break;
      case BUS_16BIT:
        if ( (*pAddr.wp++) != (*pData.wp++) )
          return E_FAIL;
        break;
    }
  }
  return E_PASS;
}

static Uint32 LOCAL_flashReadData(NOR_InfoHandle hNorInfo, Uint32 address, Uint32 offset)
{
  volatile NOR_Ptr pAddr;
  NOR_Data dataword;
  dataword.l = 0x00000000;

  pAddr.cp = LOCAL_flashMakeAddr(hNorInfo, address, offset);
	
  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      dataword.c = *pAddr.cp;
      break;      
    case BUS_16BIT:
      dataword.w = *pAddr.wp;
      break;
	}
	return dataword.l;
}

static Bool LOCAL_flashIsSetAll (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset, Uint8 mask)
{
  volatile NOR_Ptr addr;
	NOR_Data maskword;
  Bool retval = TRUE;
  Uint32 temp;

  maskword.l = 0x00000000;

  addr.cp = LOCAL_flashMakeAddr (hNorInfo, blkAddr, offset);
  temp = *addr.wp;
  LOCAL_flashMakeCmd (hNorInfo, mask, &maskword);
  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      temp = *addr.cp;
      retval = ((maskword.c & temp) == maskword.c);
      break;
    case BUS_16BIT:
      temp = *addr.wp;
      retval = ((maskword.w & temp) == maskword.w);
      break;
	}
  return retval;
}

static Bool LOCAL_flashIsSetSome (NOR_InfoHandle hNorInfo, Uint32 blkAddr, Uint32 offset, Uint8 mask)
{
  volatile NOR_Ptr addr;
  NOR_Data maskword;
	
  Bool retval = TRUE;

  addr.cp = LOCAL_flashMakeAddr (hNorInfo, blkAddr, offset);
  LOCAL_flashMakeCmd (hNorInfo, mask, &maskword);
  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      retval = (maskword.c & *addr.cp);
      break;
    case BUS_16BIT:
      retval = (maskword.w & *addr.wp);
      break;
  }
  return retval;
}

static NOR_Data LOCAL_flashReadCFIBytes (NOR_InfoHandle hNorInfo, Uint32 offset, Uint8 numBytes)
{
  Int32 i;
  NOR_Data readword;
  Uint8* pReadword = &readword.c;
	
  for (i = 0; i < numBytes; i++)
  {
    *pReadword++ = *(LOCAL_flashMakeAddr (hNorInfo, hNorInfo->flashBase, offset+i));
  }
	
  return readword;
}

static Bool LOCAL_flashCFIIsEqual (NOR_InfoHandle hNorInfo, Uint32 offset, Uint8 val)
{
  volatile NOR_Ptr addr;
  NOR_Data testword;
	
  Bool retval = TRUE;

  addr.cp = LOCAL_flashMakeAddr (hNorInfo, hNorInfo->flashBase, offset);
  LOCAL_flashMakeCmd (hNorInfo, val, &testword);
  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      retval = (testword.c == *addr.cp);
      break;
    case BUS_16BIT:
      retval = (testword.w == *addr.wp);
      break;
	}
  return retval;
}

// Query the chip to check for CFI table and data
static Uint32 LOCAL_flashQueryCFI( NOR_InfoHandle hNorInfo )
{                
  Int32 i;
  Uint32 blkVal; 
    
  // Six possible NOR Flash Configurations
  //  1) Bus in x8 mode, x8 only device (chipOperatingWidth = 8-bit, busWidth = 8-bit, maxTotalWidth = 8-bit)
  //  2) Bus in x8 mode, single x8/x16 flash operating in x8 mode (chipOperatingWidth = 8-bit, busWidth = 8-bit, maxTotalWidth = 16-bit)
  //  3) Bus in x16 mode, single x8/x16 or x16-only flash operating in x16 mode (chipOperatingWidth = 16-bit, busWidth = 16-bit, maxTotalWidth = 16-bit)
  //  4) Bus in x16 mode, two x8 flash operating in parallel. (chipOperatingWidth = 8-bit, busWidth = 16-bit, maxTotalWidth = 16-bit)
  //  5) Bus in x16 mode, two x8/x16 flash, each in x8 mode, operating in parallel  (chipOperatingWidth = 8-bit, busWidth = 16-bit, maxTotalWidth = 32-bit)
  //  6) Bus in x16 mode, single x16/x32 flash operating in x16 mode (chipOperatingWidth = 16-bit, busWidth = 16-bit, maxTotalWidth = 32-bit)
  // hNorInfo->chipOperatingWidth is the actual data bus width of the NOR flash(es)
  // hNorInfo->busWidth is the operating width of the EMIF (8 or 16)
  // hNorInfo->maxTotalWidth is total possible data bus width that the NOR flash supports (or flashes combined support)
  for (hNorInfo->chipOperatingWidth = BUS_8BIT; hNorInfo->chipOperatingWidth <= hNorInfo->busWidth;  hNorInfo->chipOperatingWidth <<= 1)
  {
    for (hNorInfo->maxTotalWidth = hNorInfo->busWidth; hNorInfo->maxTotalWidth <= (hNorInfo->busWidth*2); hNorInfo->maxTotalWidth <<= 1)
    {
      // Specify number of devices
      hNorInfo->numberDevices = 0;
      while ( hNorInfo->numberDevices * hNorInfo->chipOperatingWidth < hNorInfo->busWidth)
        hNorInfo->numberDevices++;
                        
      // Enter the CFI Query mode
      LOCAL_flashWriteCmd (hNorInfo, hNorInfo->flashBase, 0, CFI_EXIT_CMD);
      LOCAL_flashWriteCmd (hNorInfo, hNorInfo->flashBase, CFI_QRY_CMD_ADDR, CFI_QRY_CMD);

      // Check for Query QRY values
      if ( LOCAL_flashCFIIsEqual ( hNorInfo, CFI_Q, 'Q') && 
      LOCAL_flashCFIIsEqual ( hNorInfo, CFI_R, 'R') && 
      LOCAL_flashCFIIsEqual ( hNorInfo, CFI_Y, 'Y') )
			{               
        hNorInfo->commandSet = (NOR_CmdSet) (LOCAL_flashReadCFIBytes(hNorInfo,CFI_CMDSET,2).w);
        hNorInfo->flashSize = 0x1 << LOCAL_flashReadCFIBytes(hNorInfo,CFI_DEVICESIZE,1).c * hNorInfo->numberDevices;
        hNorInfo->numberRegions = LOCAL_flashReadCFIBytes(hNorInfo,CFI_NUMBLKREGIONS,1).c;
        hNorInfo->bufferSize = 0x1 << LOCAL_flashReadCFIBytes(hNorInfo,CFI_WRITESIZE,2).w * hNorInfo->numberDevices;
                
        // Get info on sector sizes in each erase region of device
        for (i = 0;i < hNorInfo->numberRegions; i++)
        {    
          blkVal = LOCAL_flashReadCFIBytes(hNorInfo,(CFI_BLKREGIONS+i*CFI_BLKREGIONSIZE),4).l;
          hNorInfo->numberBlocks[i] = (blkVal&0x0000FFFF) + 1;
          hNorInfo->blockSize[i]    = ((blkVal&0xFFFF0000) ? ( ((blkVal>>16)&0xFFFF) * 256) : 128) * hNorInfo->numberDevices;
        }
                
        // Exit CFI mode 
        LOCAL_flashWriteCmd (hNorInfo,hNorInfo->flashBase, 0, CFI_EXIT_CMD);
			    
        return E_PASS;
      }
    }        
  }
    
  LOCAL_flashWriteCmd (hNorInfo,hNorInfo->flashBase, 0, CFI_EXIT_CMD);   
  return E_FAIL;
}


// ------------------------ Default empty commands ---------------------------

static Uint32 Unsupported_Write( NOR_InfoHandle hNorInfo, Uint32 address, VUint32 data)
{
  return E_FAIL;
}
static Uint32 Unsupported_BufferWrite(NOR_InfoHandle hNorInfo, Uint32 address, VUint8 data[], Uint32 length )
{
  return E_FAIL;
}
static Uint32 Unsupported_Erase(NOR_InfoHandle hNorInfo, Uint32 address)
{
  return E_FAIL;
}
static Uint32 Unsupported_ID(NOR_InfoHandle hNorInfo)
{
  return E_FAIL;
}

static void Unsupported_SoftReset(NOR_InfoHandle hNorInfo)
{

}


// ------------------- Begin of Intel specific commands ----------------------
//ID flash
static Uint32 Intel_ID( NOR_InfoHandle hNorInfo )
{
    // Intel Exit back to read array mode
    Intel_SoftReset(hNorInfo);
    
    // Write ID command
    LOCAL_flashWriteCmd(hNorInfo,hNorInfo->flashBase, 0, INTEL_ID_CMD);
        
    //Read Manufacturer's ID
    hNorInfo->manfID = (NOR_ManfID) LOCAL_flashReadData(hNorInfo, hNorInfo->flashBase, INTEL_MANFID_ADDR);
    
    // Read Device ID
    hNorInfo->devID1 = (Uint16) (NOR_ManfID) LOCAL_flashReadData(hNorInfo, hNorInfo->flashBase, INTEL_DEVID_ADDR);
    hNorInfo->devID2 = 0x0000;
        
    // Intel Exit back to read array mode
    Intel_SoftReset(hNorInfo); 
    
    return E_PASS;
}

// Reset back to Read array mode
static void Intel_SoftReset(NOR_InfoHandle hNorInfo)
{
    // Intel Exit back to read array mode
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, 0, INTEL_RESET);
}

// Clear status register
static void LOCAL_IntelClearStatus(NOR_InfoHandle hNorInfo)
{
    // Intel clear status
    LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase,0,INTEL_CLEARSTATUS_CMD);
}

// Remove block write protection
static Uint32 LOCAL_IntelClearLock(NOR_InfoHandle hNorInfo, Uint32 blkAddr)
{

	// Write the Clear Lock Command
    LOCAL_flashWriteCmd(hNorInfo, blkAddr,0,INTEL_LOCK_CMD0);

    LOCAL_flashWriteCmd(hNorInfo, blkAddr,0,INTEL_UNLOCK_BLOCK_CMD);

    // Check Status
	return LOCAL_IntelLockStatusCheck(hNorInfo);
}

// Write-protect a block
static Uint32 LOCAL_IntelSetLock(NOR_InfoHandle hNorInfo, Uint32 blkAddr)
{
	// Write the Set Lock Command	
  LOCAL_flashWriteCmd(hNorInfo, blkAddr,0,INTEL_LOCK_CMD0);            
	
  LOCAL_flashWriteCmd(hNorInfo, blkAddr,0,INTEL_LOCK_BLOCK_CMD);

  // Check Status
  return LOCAL_IntelLockStatusCheck(hNorInfo);
}

static void LOCAL_IntelWaitForStatusComplete(NOR_InfoHandle hNorInfo)
{
    while ( !LOCAL_flashIsSetAll(hNorInfo, hNorInfo->flashBase, 0, BIT7) );
}

static Uint32 LOCAL_IntelLockStatusCheck(NOR_InfoHandle hNorInfo)
{
    Uint32 retval = E_PASS;
    //Uint8 status;

    LOCAL_IntelWaitForStatusComplete(hNorInfo);

    //status = flash_read_uint16((Uint32)hNorInfo->flashBase,0);
    //if ( status & BIT5 )
    if (LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0, (BIT5 | BIT3)))
    {
        retval = E_FAIL;
		/*if ( status & BIT4 )
        {
			DEBUG_printString("Command Sequence Error\r\n");
		}
		else
		{
			DEBUG_printString("Clear Lock Error\r\n");
		}*/
	}
	/*if ( status & BIT3 )
	{
		retval = E_FAIL;
		//DEBUG_printString("Voltage Range Error\n");
    }*/
	
	// Clear status
	LOCAL_IntelClearStatus(hNorInfo);
	
	// Put chip back into read array mode.
	Intel_SoftReset(hNorInfo);
	
	// Set Timings back to Optimum for Read
	return retval;
}

// Erase Block
static Uint32 Intel_Erase(NOR_InfoHandle hNorInfo, VUint32 blkAddr)
{
	Uint32 retval = E_PASS;
	
	// Clear Lock Bits
	retval |= LOCAL_IntelClearLock(hNorInfo,blkAddr);
	
	// Send Erase commands
	LOCAL_flashWriteCmd(hNorInfo,blkAddr,0,INTEL_ERASE_CMD0);
	LOCAL_flashWriteCmd(hNorInfo,blkAddr,0,INTEL_ERASE_CMD1);
	
	// Wait until Erase operation complete
	LOCAL_IntelWaitForStatusComplete(hNorInfo);
    
  // Verify successful erase                       
  if ( LOCAL_flashIsSetSome(hNorInfo,hNorInfo->flashBase, 0, BIT5) )
    retval = E_FAIL;
    
	// Put back into Read Array mode.
	Intel_SoftReset(hNorInfo);
	
	return retval;
}

// Write data
static Uint32 Intel_Write(NOR_InfoHandle hNorInfo, Uint32 address, VUint32 data )
{
  Uint32 retval = E_PASS;

  // Send Write command
  LOCAL_flashWriteCmd(hNorInfo,address,0,INTEL_WRITE_CMD);
  LOCAL_flashWriteData(hNorInfo,address, data);

  // Wait until Write operation complete
  LOCAL_IntelWaitForStatusComplete(hNorInfo);

  // Verify successful program
  if ( LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0, (BIT4|BIT3)) )
  {
    //DEBUG_printString("Write Op Failed.\r\n", FALSE);
    retval = E_FAIL;
  }

  // Put back into Read Array mode.
	Intel_SoftReset(hNorInfo);
                          
  return retval;
}

// Buffer write data
static Uint32 Intel_BufferWrite(NOR_InfoHandle hNorInfo, Uint32 address, VUint8 data[], Uint32 numBytes )
{
	Uint32 retval = E_PASS;
	Uint32 timeoutCnt = 0, shift;

	// Send Write_Buff_Load command   
  do {
    LOCAL_flashWriteCmd(hNorInfo,address,0,INTEL_WRT_BUF_LOAD_CMD);
    timeoutCnt++;
  }while( (!LOCAL_flashIsSetAll(hNorInfo,hNorInfo->flashBase, 0, BIT7)) && (timeoutCnt < 0x00010000) );

  if (timeoutCnt >= 0x10000)
  {
    retval = E_TIMEOUT;
  }
  else
  {
    volatile NOR_Ptr pAddr, pData;
    VUint8* endAddress;
    
    //Establish correct shift value
    shift = 0;
    while ((hNorInfo->busWidth >> shift) > 1)
      shift++;

    // Write Length (either numBytes or numBytes/2)	    
    LOCAL_flashWriteCmd(hNorInfo, address, 0, (numBytes >> shift) - 1);

    // Write buffer data
    pData.cp = (VUint8*) data;
    pAddr.cp = (VUint8*) address;
    endAddress =(VUint8*)(pAddr.cp + numBytes);
    while (pAddr.cp < endAddress)
    {
      switch (hNorInfo->busWidth)
      {
        case BUS_8BIT:
          *pAddr.cp++ = *pData.cp++;
          break;
        case BUS_16BIT:
          *pAddr.wp++ = *pData.wp++;
          break;
      }
    }

    // Send write buffer confirm command
    LOCAL_flashWriteCmd(hNorInfo, address, 0,INTEL_WRT_BUF_CONF_CMD);

    // Check status
    LOCAL_IntelWaitForStatusComplete(hNorInfo);
    
    // Verify program was successful
    if ( LOCAL_flashIsSetSome(hNorInfo, hNorInfo->flashBase, 0, BIT4) )
    {
      retval = E_FAIL;
    }

    // Put back into Read Array mode.
    Intel_SoftReset(hNorInfo);
    if (retval == E_PASS)
    {
      retval = LOCAL_flashVerifyDataBuffer(hNorInfo, address, (void*)data, numBytes);
      if (retval != E_PASS)
        DEBUG_printString("Data verify failed.\r\n");
    }    
  }

  return retval;
}
// -------------------- End of Intel specific commands -----------------------



// -------------------- Begin of AMD specific commands -----------------------

// Identify the Manufacturer and Device ID 
static Uint32 AMD_ID( NOR_InfoHandle hNorInfo )
{
  // Exit back to read array mode
  AMD_SoftReset(hNorInfo);

  // Write ID commands
  LOCAL_AMDPrefixCommands(hNorInfo);
  LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD2_ADDR, AMD_ID_CMD);

  // Read manufacturer's ID
  hNorInfo->manfID = (NOR_ManfID) LOCAL_flashReadData(hNorInfo,hNorInfo->flashBase, AMD_MANFID_ADDR);
    
  // Read device ID
  hNorInfo->devID1 = (Uint16) LOCAL_flashReadData(hNorInfo,hNorInfo->flashBase, AMD_DEVID_ADDR0);
    
  // Read additional ID bytes if needed
  if ( (hNorInfo->devID1 & 0xFF ) == AMD_ID_MULTI )
    hNorInfo->devID2 = LOCAL_flashReadCFIBytes(hNorInfo, AMD_DEVID_ADDR1, 2).w;
  else
    hNorInfo->devID2 = 0x0000;
        
  // Exit back to read array mode
  AMD_SoftReset(hNorInfo);
    
  return E_PASS;
}

static void AMD_SoftReset(NOR_InfoHandle hNorInfo)
{
	// Reset Flash to be in Read Array Mode
	LOCAL_flashWriteCmd(hNorInfo,hNorInfo->flashBase,AMD_CMD2_ADDR,AMD_RESET);
  UTIL_waitLoop(5000);
}

// AMD Prefix Commands
static void LOCAL_AMDPrefixCommands(NOR_InfoHandle hNorInfo)
{
  LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD0_ADDR, AMD_CMD0);
  LOCAL_flashWriteCmd(hNorInfo, hNorInfo->flashBase, AMD_CMD1_ADDR, AMD_CMD1);
}

// Erase Block
static Uint32 AMD_Erase(NOR_InfoHandle hNorInfo, Uint32 blkAddr)
{
  Uint32 retval = E_PASS;
  Uint32 cnt = 0;

  // Send commands
  LOCAL_AMDPrefixCommands(hNorInfo);
  LOCAL_flashWriteCmd(hNorInfo,hNorInfo->flashBase, AMD_CMD2_ADDR, AMD_BLK_ERASE_SETUP_CMD);
  LOCAL_AMDPrefixCommands(hNorInfo);
  LOCAL_flashWriteCmd(hNorInfo,blkAddr, 0x0, AMD_BLK_ERASE_CMD);
	
  // Poll DQ7 and DQ15 for status
  while ( !LOCAL_flashIsSetAll(hNorInfo,blkAddr, 0, BIT7) )
  {
    cnt++;
  }

  UTIL_waitLoop(1000);
    
  // Check data
  if ( !LOCAL_flashIsSetAll(hNorInfo, blkAddr, 0, AMD_BLK_ERASE_DONE) )
    retval = E_FAIL;
	
  // Flash Mode: Read Array
  AMD_SoftReset(hNorInfo);
    
  return retval;
}

// AMD Flash Write
static Uint32 AMD_Write(NOR_InfoHandle hNorInfo, Uint32 address, VUint32 data )
{
  Uint32 retval = E_PASS;
	
  // Send Commands
  LOCAL_AMDPrefixCommands(hNorInfo);
  LOCAL_flashWriteCmd(hNorInfo,hNorInfo->flashBase, AMD_CMD2_ADDR, AMD_PROG_CMD);
  LOCAL_flashWriteData(hNorInfo,address, data);

  // Wait for ready.
  while(TRUE)
  {
    if ( (LOCAL_flashReadData(hNorInfo, address, 0 ) & (BIT7 | BIT15) ) == (data & (BIT7 | BIT15) ) )
    {
      break;
    }
    else
    {
      if(LOCAL_flashIsSetAll(hNorInfo, address, 0, BIT5))
      {
        if ( (LOCAL_flashReadData(hNorInfo, address, 0 ) & (BIT7 | BIT15) ) != (data & (BIT7 | BIT15) ) )
        {
          DEBUG_printString("Timeout ocurred.\r\n");
          retval = E_FAIL;
        }
        break;				
      }
    }
  }
	
  // Return Read Mode
	AMD_SoftReset(hNorInfo);
	
	// Verify the data.
  if ( (retval == E_PASS) && ( LOCAL_flashReadData(hNorInfo, address, 0) != data) )
    retval = E_FAIL;
	
	return retval;
}

// AMD flash buffered write
static Uint32 AMD_BufferWrite(NOR_InfoHandle hNorInfo, Uint32 address, VUint8 data[], Uint32 numBytes )
{
  Uint32 startAddress = address;
  Uint32 blkAddress, blkSize;
  Uint32 data_temp;
  Uint32 retval = E_PASS;
  Uint32 shift;
  volatile NOR_Ptr pAddr, pData;
  VUint8* endAddress;
	
  // Get block base address and size
  NOR_getBlockInfo(hNorInfo, address, &blkSize, &blkAddress);
			
  // Write the Write Buffer Load command
  LOCAL_AMDPrefixCommands(hNorInfo);
  LOCAL_flashWriteCmd(hNorInfo, blkAddress, 0, AMD_WRT_BUF_LOAD_CMD);
        
  //Establish correct shift value
  shift = 0;
  while ((hNorInfo->busWidth >> shift) > 1)
    shift++;
    
  // Write Length (either numBytes or numBytes/2)	    
  LOCAL_flashWriteCmd(hNorInfo, blkAddress, 0, (numBytes >> shift) - 1);
	
	// Write Data
  pData.cp = (VUint8*) data;
  pAddr.cp = (VUint8*) address;
  endAddress =(VUint8*)(pAddr.cp + numBytes);
  while (pAddr.cp < endAddress)
  {
    switch (hNorInfo->busWidth)
    {
      case BUS_8BIT:
        *pAddr.cp++ = *pData.cp++;
        break;
      case BUS_16BIT:
        *pAddr.wp++ = *pData.wp++;
        break;
    }
  }

  // Put last data written at start of data buffer - For AMD verification
  switch (hNorInfo->busWidth)
  {
    case BUS_8BIT:
      address = (Uint32)(endAddress-1);
      break;
    case BUS_16BIT:
      address = (Uint32)(endAddress-2);
      break;
  }  
  
		
  // Program Buffer to Flash Confirm Write
  LOCAL_flashWriteCmd(hNorInfo, blkAddress, 0, AMD_WRT_BUF_CONF_CMD);                  

  UTIL_waitLoop(1000);
    
  // Read last data item                  
  data_temp = LOCAL_flashReadData(hNorInfo, (Uint32) (data + (address - startAddress)), 0);
        
	while(TRUE)
	{
    if( (LOCAL_flashReadData(hNorInfo, address, 0 ) & (BIT7 | BIT15)) == (data_temp & (BIT7 | BIT15) ) )
    {
      break;
    }
    else
    {
      // Timeout has occurred
      if(LOCAL_flashIsSetAll(hNorInfo,address, 0, BIT5))
      {
        if( (LOCAL_flashReadData(hNorInfo,address, 0 ) & (BIT7 | BIT15)) != (data_temp & (BIT7 | BIT15) ) )
        {
          DEBUG_printString("Timeout ocurred.\r\n");
          retval = E_FAIL;
        }
        break;
      }
      // Abort has occurred
      if(LOCAL_flashIsSetAll(hNorInfo, address, 0, BIT1))
      {
        if( (LOCAL_flashReadData(hNorInfo, address, 0 ) & (BIT7 | BIT15)) != (data_temp & (BIT7 | BIT15) ) )
        {
          DEBUG_printString("Abort ocurred.\r\n");
          retval = E_FAIL;
          LOCAL_AMDWriteBufAbortReset (hNorInfo);
        }
        break;
      }
    }
  }
	
  // Put chip back into read array mode.
  AMD_SoftReset(hNorInfo);
  if (retval == E_PASS)
  {
    retval = LOCAL_flashVerifyDataBuffer(hNorInfo, startAddress,(void*)data, numBytes);
    if (retval != E_PASS)
      DEBUG_printString("Data verify failed.\r\n");
  }
  return retval;
}

// AMD Write Buf Abort Reset Flash
static void LOCAL_AMDWriteBufAbortReset(NOR_InfoHandle hNorInfo)
{
  // Reset Flash to be in Read Array Mode
  LOCAL_AMDPrefixCommands(hNorInfo);
  AMD_SoftReset(hNorInfo);
}

// --------------------- End of AMD specific commands ------------------------


/***********************************************************
* End file                                                 *
***********************************************************/

/* --------------------------------------------------------------------------
	HISTORY
    v1.00 - DJA - 16-Aug-2007
      Initial Release
    v1.01 - DJA - 02-Nov-2007
      Code cleanup, minor mod to erase function
-------------------------------------------------------------------------- */

