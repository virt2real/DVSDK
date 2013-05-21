/* --------------------------------------------------------------------------
  FILE      : nand.h
  PROJECT   : TI Booting and Flashing Utilities
  AUTHOR    : Daniel Allred
  DESC      : Header file for the generic low-level NAND driver code for
              use with the EMIFA peripheral
-------------------------------------------------------------------------- */

#ifndef _NAND_H_
#define _NAND_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

// An assumption is made that ARM-based devices use Linux and 
// therefore use the last four blocks of the NAND as space for 
// an MTD standard bad block table. DSP-based are assumed to 
// not run Linux, and bad blocks are managed in some other fashion.
#if ( defined(__TMS470__) | defined(__GNUC__) )
#define NAND_NUM_BLOCKS_RESERVED_FOR_BBT     (4)
#else
#define NAND_NUM_BLOCKS_RESERVED_FOR_BBT     (0)
#endif

// NAND flash addresses
#define NAND_DATA_OFFSET    DEVICE_NAND_DATA_OFFSET
#define NAND_ALE_OFFSET     DEVICE_NAND_ALE_OFFSET
#define NAND_CLE_OFFSET     DEVICE_NAND_CLE_OFFSET

// NAND timeout 
#define NAND_TIMEOUT        DEVICE_NAND_TIMEOUT

// NAND flash commands
#define NAND_LO_PAGE          (0x00)
#define NAND_HI_PAGE          (0x01)
#define NAND_EXTRA_PAGE       (0x50)

#define NAND_LOCK             (0x2A)
#define NAND_UNLOCK_START     (0x23)
#define NAND_UNLOCK_END       (0x24)

#define NAND_READ_PAGE        (0x00)
#define NAND_READ_30H         (0x30)
#define NAND_RANDOM_READ_PAGE (0x05)
#define NAND_RANDOM_READ_E0H  (0xE0)

#define	NAND_RDID             (0x90)
#define NAND_RDID2            (0x65)
#define NAND_RDIDADD          (0x00)

#define	NAND_RESET            (0xFF)
#define	NAND_STATUS           (0x70)
#define NAND_RDY              (0x40)

#define	NAND_PGRM_START       (0x80)
#define	NAND_RANDOM_PGRM      (0x85)
#define NAND_PGRM_END         (0x10)
#define	NAND_PGM_FAIL         (0x01)

#define	NAND_BERASEC1         (0x60)
#define	NAND_BERASEC2         (0xD0)


// NAND ONFI commands
#define NAND_ONFIRDIDADD        (0x20)
#define NANDONFI_STRING         (0x49464E4F)
#define NANDONFI_RDPARAMPAGE    (0xEC)
#define NANDONFI_

// Status Output
#define NAND_NANDFSR_READY      (0x01)
#define NAND_STATUS_WRITEREADY  (0xC0)
#define NAND_STATUS_ERROR       (0x01)
#define NAND_STATUS_READY       (0x40)
#define NAND_STATUS_PROTECTED   (0x80)

#define NAND_MAX_PAGE_SIZE          (8192)  
#define NAND_MAX_BYTES_PER_OP       DEVICE_NAND_MAX_BYTES_PER_OP
#define NAND_MIN_SPAREBYTES_PER_OP  DEVICE_NAND_MIN_SPAREBYTES_PER_OP    // Min Spare Bytes per operation

// Macro gets the page size in bytes without the spare bytes 
#define NANDFLASH_PAGESIZE(x) ( ( x >> 8 ) << 8 )


/***********************************************************
* Global Typedef declarations                              *
***********************************************************/

// Region Types
typedef enum _NAND_REGION_TYPE_
{
  NAND_REGION_DATA    = 0x0,    // Data Region
  NAND_REGION_SPARE   = 0x1    // Spare Region
}
NAND_RegionType;

// Offset Types
typedef enum _NAND_OFFSET_TYPE_
{
  NAND_OFFSETS_RELTODATA     = 0x0,   // Offsets are relative to start of the data region of the page 
  NAND_OFFSETS_RELTOSPARE    = 0x1    // Offsets are relative to start of spare bytes region
}
NAND_OffsetType;

// NAND_INFO structure - holds pertinent info for open driver instance
typedef struct _NAND_INFO_
{
  Uint32    flashBase;          // Base address of CS memory space where NAND is connected
  Uint8     busWidth;           // NAND bus width
  Uint8     manfID;             // NAND manufacturer ID (just for informational purposes)
  Uint8     devID;              // NAND_TABLE_Devices index (device ID)
  Uint32    numBlocks;          // block count per device
  Uint16    pagesPerBlock;      // page count per block
  Uint16    dataBytesPerPage;   // Number of bytes in a page
  Uint16    spareBytesPerPage;  // Number of spare bytes in a page  
  Uint16    dataBytesPerOp;     // Number of bytes per operation
  Uint16    spareBytesPerOp;    // Number of spare bytes per operation
  Uint8     numOpsPerPage;      // Number of operations to complete a page read/write  
  Uint8     numColAddrBytes;    // Number of Column address cycles
  Uint8     numRowAddrBytes;    // Number of Row address cycles
  Uint8     CSOffset;           // 0 for CS2 space, 1 for CS3 space, 2 for CS4 space, 3 for CS5 space  
  Bool      isLargePage;        // TRUE = Big block device, FALSE = small block device
  Bool      isONFI;             // TRUE = ONFI-compatible device, FALSE = non-ONFI device
  Int32     currBlock;          // current Block in use
  Bool      isBlockGood;        // TRUE=current block is good, FALSE=block is bad
  struct _NAND_PAGE_LAYOUT_   *hPageLayout;
  struct _NAND_ECC_INFO_      *hEccInfo;
  struct _NAND_BB_INFO_       *hBbInfo;
  struct _NAND_CHIP_INFO_     *hChipInfo;
} 
NAND_InfoObj, *NAND_InfoHandle;

// NAND_DEVICE structure - holds supported devices' params
typedef struct _NAND_CHIP_INFO_
{
  const Uint8   devID;              // DeviceID
  const Uint16  numBlocks;          // number of blocks in device
  const Uint8   pagesPerBlock;      // page count per block
  const Uint16  bytesPerPage;       // byte count per page (include spare)
}
NAND_CHIP_InfoObj, *NAND_CHIP_InfoHandle;

// Region object
typedef struct _NAND_REGION_
{
  const NAND_RegionType regionType;
  const NAND_OffsetType offsetType;
  const Uint16 bytesPerOp;
  const Uint16 offsets[16];
}
NAND_RegionObj, *NAND_RegionHandle;

// Device specific page layout struct, consisting of two region objects
typedef struct _NAND_PAGE_LAYOUT_
{
  NAND_RegionObj dataRegion;
  NAND_RegionObj spareRegion;
}
NAND_PAGE_LayoutObj, *NAND_PAGE_LayoutHandle;

// NAND ECC function typedefs
typedef void (*NAND_ECC_Calculate)(NAND_InfoHandle hNandInfo, Uint8 *data, Uint8 *calcECC);
typedef void (*NAND_ECC_Store)(NAND_InfoHandle hNandInfo, Uint8 *spareBytes, Uint8 opNum, Uint8 *calcECC);
typedef void (*NAND_ECC_Enable)( NAND_InfoHandle hNandInfo );
typedef void (*NAND_ECC_Disable)( NAND_InfoHandle hNandInfo );
typedef void (*NAND_ECC_Read)(NAND_InfoHandle hNandInfo, Uint8 *spareBytes, Uint8 opNum, Uint8 *readECC);
typedef Uint32 (*NAND_ECC_Correct)(NAND_InfoHandle hNandInfo, Uint8 *data, Uint8 *readECC);

// Device specific ECC info struct
typedef struct _NAND_ECC_INFO_
{
  const Bool   ECCEnable;                 // Error correction enable (should be on by default)  
  const Uint16 calcECCByteCnt;            // Count of ECC bytes per op as read from HW registers
  const Uint16 storedECCByteCnt;          // Count of ECC bytes per op as stored in the NAND page
  const NAND_ECC_Calculate    fxnCalculate;
  const NAND_ECC_Store        fxnStore;
  const NAND_ECC_Enable       fxnEnable;
  const NAND_ECC_Disable      fxnDisable;
  const NAND_ECC_Read         fxnRead;
  const NAND_ECC_Correct      fxnCorrect;
}
NAND_ECC_InfoObj, *NAND_ECC_InfoHandle;

// NAND Bad Block function typedefs
typedef void (*NAND_BB_MarkSpareBytes)(NAND_InfoHandle hNandInfo, Uint8 *spareBytes);
typedef Uint32 (*NAND_BB_CheckSpareBytes)(NAND_InfoHandle hNandInfo, Uint8 *spareBytes);

// Device specific Bad block info struct
typedef struct _NAND_BB_INFO_
{
  const Bool   BBMarkEnable;                // We can mark bad blocks
  const Bool   BBCheckEnable;               // We can check for bad blocks  
  const NAND_BB_MarkSpareBytes  fxnBBMark;        // Function pointer to mark spare bytes of page
  const NAND_BB_CheckSpareBytes fxnBBCheck;       // Function pointer to check spare bytes of page
}
NAND_BB_InfoObj, *NAND_BB_InfoHandle;

typedef union
{
  Uint8 c;
  Uint16 w;
  Uint32 l;
}
NAND_Data;

typedef union
{
  VUint8 *cp;
  VUint16 *wp;
  VUint32 *lp;
}
NAND_Ptr;


/************************************************************
* Global Function Declarations                              *
************************************************************/

extern NAND_InfoHandle NAND_open(Uint32 baseCSAddr, Uint8 busWidth);
extern Uint32 NAND_reset(NAND_InfoHandle hNandInfo);
extern Uint32 NAND_badBlockCheck(NAND_InfoHandle hNandInfo, Uint32 block);
extern Uint32 NAND_readPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *dest);
extern Uint32 NAND_readSpareBytesOfPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *dest);

#ifndef USE_IN_ROM
extern Bool   NAND_isWriteProtected(NAND_InfoHandle hNandInfo);
extern Uint32 NAND_badBlockMark(NAND_InfoHandle hNandInfo, Uint32 block);
extern Uint32 NAND_writePage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src);
extern Uint32 NAND_writePage_ubl_header(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src);
extern Uint32 NAND_writeOnlySpareBytesOfPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8* spareBytes);
extern Uint32 NAND_verifyPage(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src, Uint8* dest);

extern Uint32 NAND_globalErase(NAND_InfoHandle hNandInfo);
extern Uint32 NAND_eraseBlocks(NAND_InfoHandle hNandInfo, Uint32 startBlkNum, Uint32 blkCount);
extern Uint32 NAND_globalErase_with_bb_check(NAND_InfoHandle hNandInfo);
extern Uint32 NAND_eraseBlocks_with_bb_check(NAND_InfoHandle hNandInfo, Uint32 startBlkNum, Uint32 blkCnt);

extern Uint32 NAND_verifyBlockErased(NAND_InfoHandle hNandInfo, Uint32 block, Uint8* dest);

extern Uint32 NAND_unProtectBlocks(NAND_InfoHandle hNandInfo,Uint32 startBlkNum,Uint32 endBlkNum);
extern void NAND_protectBlocks(NAND_InfoHandle hNandInfo);

#if defined(NAND_ECC_TEST)
extern Uint32 NAND_writePageWithSpareBytes(NAND_InfoHandle hNandInfo, Uint32 block, Uint32 page, Uint8 *src, Uint8 *spareBytes);
#endif

#endif



/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_NAND_H_

