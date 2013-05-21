/* --------------------------------------------------------------------------
  FILE      : sdmmc.h
  PROJECT   : TI Booting and Flashing Utilities
  AUTHOR    : Daniel Allred
  DESC      : Header file for the generic low-level SDMMC driver
-------------------------------------------------------------------------- */

#ifndef _SDMMC_H_
#define _SDMMC_H_

#include "tistdtypes.h"

// Prevent C++ name mangling
#ifdef __cplusplus
extern far "c" {
#endif

/************************************************************
* Global Macro Declarations                                 *
************************************************************/

#define SDMMC_OP_TIMEOUT    2048
#define SDMMC_BSYEXP        0x0100
//#define SDMMC_PPLEN         0x0080
#define SDMMC_FNCLK_INIT    1
#define SDMMC_CLK_INIT      300000

/*
 *  Direction of DMA Transfer
 */
#define SDMMC_FROM_MMC          0           // MMCIF to SDRAM
#define SDMMC_TO_MMC            1           // SDRAM to MMCIF

#define SDMMC_STUFF_BITS          0x00000000u
#define SDMMC_VDD_32_34           0x00300000u
#define SDMMC_VDD_32_33           0x00100000u
#define SDMMC_VDD_27_36           0x00FF8000u
#define SDMMC_BSYEXP		       0x0100



/* Response Macros */
#define SDMMC_RSPNONE                   (0x0000u)
#define SDMMC_RSP1                      (0x0200u)
#define SDMMC_RSP2                      (0x0400u)
#define SDMMC_RSP3                      (0x0600u)
#define SDMMC_RSP4                       SDMMC_RSP1
#define SDMMC_RSP5                       SDMMC_RSP1
#define SDMMC_RSP6                       SDMMC_RSP1

/* Command Macros */
#define SDMMC_CMD0                      (0x0000u)
#define SDMMC_CMD1                      (0x0001u)
#define SDMMC_CMD2                      (0x0002u)
#define SDMMC_CMD3                      (0x0003u)
#define SDMMC_CMD4                      (0x0004u)
#define SDMMC_CMD5                      (0x0005u)
#define SDMMC_CMD6                      (0x0006u)
#define SDMMC_CMD7                      (0x0007u)
#define SDMMC_CMD8                      (0x0008u)
#define SDMMC_CMD9                      (0x0009u)
#define SDMMC_CMD10                     (0x000Au)
#define SDMMC_CMD11                     (0x000Bu)
#define SDMMC_CMD12                     (0x000Cu)
#define SDMMC_CMD13                     (0x000Du)
#define SDMMC_CMD14                     (0x000Eu)
#define SDMMC_CMD15                     (0x000Fu)
#define SDMMC_CMD16                     (0x0010u)
#define SDMMC_CMD17                     (0x0011u)
#define SDMMC_CMD18                     (0x0012u)
#define SDMMC_CMD19                     (0x0013u)
#define SDMMC_CMD20                     (0x0014u)
#define SDMMC_CMD21                     (0x0015u)
#define SDMMC_CMD22                     (0x0016u)
#define SDMMC_CMD23                     (0x0017u)
#define SDMMC_CMD24                     (0x0018u)
#define SDMMC_CMD25                     (0x0019u)
#define SDMMC_CMD26                     (0x001Au)
#define SDMMC_CMD27                     (0x001Bu)
#define SDMMC_CMD28                     (0x001Cu)
#define SDMMC_CMD29                     (0x001Du)
#define SDMMC_CMD30                     (0x001Eu)
#define SDMMC_CMD31                     (0x001Fu)
#define SDMMC_CMD32                     (0x0020u)
#define SDMMC_CMD33                     (0x0021u)
#define SDMMC_CMD34                     (0x0022u)
#define SDMMC_CMD35                     (0x0023u)
#define SDMMC_CMD36                     (0x0024u)
#define SDMMC_CMD37                     (0x0025u)
#define SDMMC_CMD38                     (0x0026u)
#define SDMMC_CMD39                     (0x0027u)
#define SDMMC_CMD40                     (0x0028u)
#define SDMMC_CMD41                     (0x0029u)
#define SDMMC_CMD42                     (0x002Au)
#define SDMMC_CMD43                     (0x002Bu)
#define SDMMC_CMD44                     (0x002Cu)
#define SDMMC_CMD45                     (0x002Du)
#define SDMMC_CMD46                     (0x002Eu)
#define SDMMC_CMD47                     (0x002Fu)
#define SDMMC_CMD48                     (0x0030u)
#define SDMMC_CMD49                     (0x0031u)
#define SDMMC_CMD50                     (0x0032u)
#define SDMMC_CMD51                     (0x0033u)
#define SDMMC_CMD52                     (0x0034u)
#define SDMMC_CMD53                     (0x0035u)
#define SDMMC_CMD54                     (0x0036u)
#define SDMMC_CMD55                     (0x0037u)
#define SDMMC_CMD56                     (0x0038u)
#define SDMMC_CMD57                     (0x0039u)
#define SDMMC_CMD58                     (0x003Au)
#define SDMMC_CMD59                     (0x003Bu)
#define SDMMC_CMD60                     (0x003Cu)
#define SDMMC_CMD61                     (0x003Du)
#define SDMMC_CMD62                     (0x003Eu)
#define SDMMC_CMD63                     (0x003Fu)
#define SDMMC_CMD64                     (0x0040u)

/* Commands and their responses */
/* MMC and SD */
#define SDMMC_GO_IDLE_STATE                   (SDMMC_CMD0 | SDMMC_RSPNONE)

#define SDMMC_ALL_SEND_CID                    (SDMMC_CMD2 | SDMMC_RSP2 )
#define SDMMC_SET_DSR                         (SDMMC_CMD4 | SDMMC_RSPNONE)
#define SDMMC_SELECT_CARD                     (SDMMC_CMD7 | SDMMC_RSP1)
#define SDMMC_DESELECT_CARD                   (SDMMC_CMD7 )
#define SDMMC_SEND_CSD                        (SDMMC_CMD9 | SDMMC_RSP2)
#define SDMMC_SEND_CID                        (SDMMC_CMD10| SDMMC_RSP2)
#define SDMMC_SEND_STATUS                     (SDMMC_CMD13 | SDMMC_RSP1)
#define SDMMC_GO_INACTIVE_STATE               (SDMMC_CMD15 | SDMMC_RSPNONE)
#define SDMMC_APP_CMD                         (SDMMC_CMD55 | SDMMC_RSP1 )
#define SDMMC_HICAP_CMD                       (SDMMC_CMD8  | SDMMC_RSP3 )
#define SDMMC_STOP_TRANSMISSION               (SDMMC_CMD12 | SDMMC_RSP1 | SDMMC_BSYEXP)
#define SDMMC_READ_MULTIPLE_BLOCK             (SDMMC_CMD18 | SDMMC_RSP1)
#define SDMMC_WRITE_MULTIPLE_BLOCK            (SDMMC_CMD25 | SDMMC_RSP1 ) /*| SDMMC_BSYEXP)*/

/* Common to SPI & MMC */
#define SDMMC_SET_BLOCKLEN                    (SDMMC_CMD16 | SDMMC_RSP1 )
#define SDMMC_PROGRAM_CSD                     (SDMMC_CMD27 | SDMMC_RSP1 | SDMMC_BSYEXP) /* MMC-bsy, SPI-bsy optional */
#define SDMMC_SET_WRITE_PROT                  (SDMMC_CMD28 | SDMMC_RSP1 | SDMMC_BSYEXP)
#define SDMMC_CLR_WRITE_PROT                  (SDMMC_CMD29 | SDMMC_RSP1 | SDMMC_BSYEXP)
#define SDMMC_SEND_WRITE_PROT                 (SDMMC_CMD30 | SDMMC_RSP1)
#define SDMMC_READ_SINGLE_BLOCK               (SDMMC_CMD17 | SDMMC_RSP1 )
#define SDMMC_WRITE_BLOCK                     (SDMMC_CMD24 | SDMMC_RSP1 )/*| MMC_BSYEXP)*/
#define SDMMC_READ_OCR                        (SDMMC_CMD58 | SDMMC_RSP3 )
#define SDMMC_CRC_ON_OFF                      (SDMMC_CMD59 | SDMMC_RSP1)
  
/* Command parameters */
#define MMCCMD_REG_INITCK             (0x4000u)
#define MMCCMD_REG_PPLEN              (0x0080u)
#define SDMMC_PPLEN			       	  (0x0080)
#define SDMMC_STAT0_DATDNE 			  (0x0001)     ///< Data Done Status


#define SDMMC_OP_TIMEOUT           2048
#define MMC_SEND_OP_COND           (SDMMC_CMD1 | SDMMC_RSP3 )
#define MMC_SET_RELATIVE_ADDR      (SDMMC_CMD3 | SDMMC_RSP1)

#define SD_APP_OP_COND             (SDMMC_CMD41 | SDMMC_RSP3 )
#define SD_SEND_RELATIVE_ADDR      (SDMMC_CMD3 | SDMMC_RSP6 | SDMMC_PPLEN)
#define SD_SET_BUS_WIDTH           (SDMMC_CMD6  | SDMMC_RSP1 | SDMMC_PPLEN)



#define SD_HIGH_CAPACITY_ECHO_PATTERN 0xAA	

/***********************************************************
* Global Typedef declarations                              *
***********************************************************/
typedef enum {
  SDMMC_SET_PASSWD=1, 
  SDMMC_CLR_PASSWD=2,
  SDMMC_LOCK_UNLOCK=4, 
  SDMMC_FORCED_ERASE=8
} SDMMC_CARD_LOCK_MODE;

// Endianness Select
typedef enum _SDMMC_ENDIANNESS_
{
  SDMMC_LITTLE_ENDIAN = 0x00,
  SDMMC_BIG_ENDIAN    = 0x01
}
SDMMC_Endianness;

// Data Bus Width
typedef enum _SDMMC_DATABUS_WIDTH_
{
  SDMMC_1BIT_DATABUS = 0x00,
  SDMMC_4BIT_DATABUS = 0x01
}
SDMMC_DatabusWidth;

typedef enum _SDMMC_FIFO_THRESHOLD_
{
  SDMMC_FIFO_LEVEL_16BYTES = 0x00,  // 16 bytes
  SDMMC_FIFO_LEVEL_32BYTES = 0x01   // 32 Bytes
}
SDMMC_FifoThreshold;

typedef enum _SDMMC_MODES_
{
  SDMMC_MODE_NATIVE = 0x00,
  SDMMC_MODE_SPI    = 0x01
}
SDMMC_Mode;


// Card States as per MMC/SD Specifications
typedef enum _SDMMC_CARD_STATES_
{
  SDMMC_CARD_STATE_IDLE     = 0,
  SDMMC_CARD_STATE_READY    = 1,
  SDMMC_CARD_STATE_IDENT    = 2,
  SDMMC_CARD_STATE_STBY     = 3,
  SDMMC_CARD_STATE_TRAN     = 4,
  SDMMC_CARD_STATE_DATA     = 5,
  SDMMC_CARD_STATE_RCV      = 6,
  SDMMC_CARD_STATE_PRG      = 7,
  SDMMC_CARD_STATE_DIS      = 8,
  SDMMC_CARD_STATE_INA      = 9
}
SDMMC_CardStates;

// DAT3 Edge Detection select
typedef enum _SDMMC_DAT3_EDGE_DETECT_TYPE_
{
  SDMMC_DAT3_EDGE_DETECT_DISABLE    = 0,   // DAT3 edge detection is disabled
  SDMMC_DAT3_EDGE_DETECT_RISE       = 1,   // DAT3 rising edge detection is enabled
  SDMMC_DAT3_EDGE_DETECT_FALL       = 2,   // DAT3 falling edge detection is enabled
  SDMMC_DAT3_EDGE_DETECT_BOTH       = 3    // DAT3 both edge detection is enabled
}
SDMMC_Dat3EdgeDetectType;

// Status bits of Register - Status0
typedef enum _SDMMC_STATUS0_FLAGS_
{
  SDMMC_STATUS0_FLAG_DATDNE         = 0x0001,      // Data Done Status
  SDMMC_STATUS0_FLAG_BSYDNE         = 0x0002,      // Busy Done Status
  SDMMC_STATUS0_FLAG_RSPDNE         = 0x0004,      // Command / Response Done Status
  SDMMC_STATUS0_FLAG_TOUTRD         = 0x0008,      // Time-Out ( read data ) Status
  SDMMC_STATUS0_FLAG_TOUTRS         = 0x0010,      // Time-Out ( response ) Status
  SDMMC_STATUS0_FLAG_CRCWR          = 0x0020,      // CRC error ( write data ) Status
  SDMMC_STATUS0_FLAG_CRCRD          = 0x0040,      // CRC error ( read data ) Status
  SDMMC_STATUS0_FLAG_CRCRS          = 0x0080,      // CRC error ( response ) Status
  SDMMC_STATUS0_FLAG_SPIERR         = 0x0100,      // Data Error ( in SPI mode ) Status
  SDMMC_STATUS0_FLAG_DXRDY          = 0x0200,      // Data Transmit Ready Status
  SDMMC_STATUS0_FLAG_DRRDY          = 0x0400,      // Data Receive Ready Status
  SDMMC_STATUS0_FLAG_DATED          = 0x0800       // DAT3 Edge Detect Status
}
SDMMC_Status0Flags;

// Status bits of Register - Status1
typedef enum _SDMMC_STATUS1_FLAGS_
{
  SDMMC_STATUS1_FLAG_BUSY           = 0x0001,      // Busy Status
  SDMMC_STATUS1_FLAG_CLKSTP         = 0x0002,      // Clock Stop Status
  SDMMC_STATUS1_FLAG_DXEMP          = 0x0004,      // Data transmit empty Status
  SDMMC_STATUS1_FLAG_DRFUL          = 0x0008,      // Data receive full Status
  SDMMC_STATUS1_FLAG_DAT3ST         = 0x0010,      // DAT3 Status
  SDMMC_STATUS1_FLAG_FIFOEMP        = 0x0020,      // FIFO empty status
  SDMMC_STATUS1_FLAG_FIFOFULL       = 0x0040      // FIFO full status
}
SDMMC_Status1Flags;




// Response information received from SDMMC
typedef struct _SDMMC_RESPONSE_DATA_
{
  Uint16 response[8];           // Response of the command
  Uint8 dataResponse;           // Data response
  Uint8 errorToken;             // Error Token
  Uint8 commandIdk;             // Command Index
}
SDMMC_ResponseData;

// SDMMC: Card Status Register
typedef struct _SDMMC_CARD_STATUS_REG_
{
  Uint8  appSpecific;
  Uint8  ready;
  SDMMC_CardStates currentState;
  Uint8  eraseReset;
  Uint8  eccDisabled;
  Uint8  wpEraseSkip;
  Uint16 errorFlags;
  Uint8  multiMediaCard;
}
SDMMC_cardStatusReg;

// Native mode Card CSD Register Information, required by the driver
typedef struct _SDMMC_CSD_REG_INFO_
{
  Uint8  permWriteProtect;
  Uint8  tmpWriteProtect;
  Uint8  writeBlkPartial;
  Uint16 writeBlkLenBytes;
  Uint8  wpGrpEnable;
  Uint8  wpGrpSize;             // Extracting 7 bits: For MMC - 5 bits reqd; For SD - 7 bits reqd. ( have to be taken care by user )
  Uint8  dsrImp;
  Uint8  readBlkMisalign;
  Uint8  writeBlkMisalign;
  Uint8  readBlkPartial;
  Uint16 readBlkLenBytes;
  Uint8  sysSpecVersion;        // These bits are reserved in the case of SD card
  Uint8  sdHighCapacityCard;
}
SDMMC_csdRegInfo;


typedef struct _SDMMC_CONFIG_
{
  SDMMC_Endianness writeEndian;         // Endian select enable while writing
  SDMMC_Endianness readEndian;          // Endian select enable while reading
  SDMMC_Dat3EdgeDetectType dat3Detect;          // DAT3 Edge detection
  Uint8 cardReadyFlag;        // Card Ready flag in SDIO init response TRUE:
                            // Card Ready FALSE: Card not ready
  Uint8 IOflag;               // SDIO I/O function flag TRUE: I/O present FALSE: I/O absent
  Uint8 memoryFlag;           // SD memory function presence flag
                            // TRUE: memory present FALSE: memory absent
  Uint8 numFunctions;         // Number of I/O functions available in SDIO card
  SDMMC_Mode mode;        // SPI mode, TRUE:Enable SPI Mode, FALSE:Enable Native Mode
  Uint8 csEnable;             // Card Select enable when writing, TRUE:CS output
                            // is LOW, FALSE: CS output is HIGH. Valid Only in SPI mode
  Uint8 spiCrcErrCheckEnable; // CRC Error check enabled, TRUE:Enable CRC check,
                            // FALSE:Disable CRC check. Valid Only in SPI mode
  SDMMC_DatabusWidth busWidth;            // Data bus width, Only in Native mode,
                            // SDMMC_DATA_BUS_1:1 bit data bus,
                            // SDMMC_DATA_BUS_4:4 bit data bus
  Uint16 timeoutResponse;     // Timeout value for response, range 0 to 255
                            // MMC CLK clock cycles for Native mode, for
                            // SPI mode timeout value is equal to this
                            // value multiplied by 8 MMC CLK clock cycles
  Uint16 timeoutRead;         // Time out value for data read, range from
                            // 0 to 65535 MMC CLK clock cycles in native mode,
                            // for SPI mode timeout value is equal to this
                            // value multiplied by 8 MMC CLK clock cycles
  SDMMC_FifoThreshold fifoThreshold;     // To set the FIFO depth 16bytes or 32 bytes

}
SDMMC_ConfigObj, *SDMMC_ConfigHandle;
// _SDMMC_INFO_ structure - holds pertinent info for open driver instance
typedef struct _SDMMC_INFO_
{
  SDMMC_ConfigHandle hSDMMCCfg;
  Uint32 relCardAddress;
  SDMMC_ResponseData sdMmcResponse;
  SDMMC_csdRegInfo mmcSdCSDRegInfo;
  Uint32 dataBytesPerBlk;
  Uint32 dataBytesPerBlkPower2;
} 
SDMMC_InfoObj, *SDMMC_InfoHandle;



/************************************************************
* Global Function Declarations                              *
************************************************************/

extern __FAR__ SDMMC_InfoHandle SDMMC_open(Uint32 sdmmcPeripheralNum, SDMMC_ConfigHandle hSDMMCCfg);
extern __FAR__ Uint32 SDMMC_readBytes(SDMMC_InfoHandle hSDMMCInfo, Uint32 addr, Uint32 byteCnt, Uint8 *dest);

#ifndef USE_IN_ROM
extern __FAR__ Uint32 SDMMC_writeBytes(SDMMC_InfoHandle hSDMMCInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src);
extern __FAR__ Uint32 SDMMC_verifyBytes(SDMMC_InfoHandle hSDMMCInfo, Uint32 addr, Uint32 byteCnt, Uint8 *src, Uint8* dest);
extern __FAR__ Uint32 SDMMC_globalErase(SDMMC_InfoHandle hSDMMCInfo);
extern __FAR__ Uint32 SDMMC_eraseBytes(SDMMC_InfoHandle hSDMMCInfo, Uint32 startAddr, Uint32 byteCnt);
#endif



/***********************************************************
* End file                                                 *
***********************************************************/

#ifdef __cplusplus
}
#endif

#endif //_SDMMC_H_

