/* --------------------------------------------------------------------------
    FILE        : ais_util.c 				                             	 	        
    PROJECT     : DM648 CCS AIS Utility
    AUTHOR      : Joseph Coombs, Daniel Allred
    DESC        : Parses an AIS loaded into memory as a char or int array, 
                  and runs host interfaces in master mode to boot load an 
                  AIS capable slave.
 ----------------------------------------------------------------------------- */

// C standard I/O library
#include "stdio.h"

// General type include
#include "tistdtypes.h"

// Device specific CSL
#include "device.h"

// This module's header
#include "ais_util.h"


/************************************************************
* Explicit External Declarations                            *
************************************************************/


/************************************************************
* Local Macro Declarations                                  *
************************************************************/

// Configuration Macros ---------------------------------------------------------------------
#define LOCAL_timeoutForever	(-1)
#define LOCAL_timeoutLong		(5000)
// fastboot settings
#define LOCAL_uartFbBaud		(170)	// Primus QT: 170


// AIS Standard Macros (do not change!) -----------------------------------------------------
//#define AIS_OS(a, b)		(AIS_POS(a, b, 0))
#define AIS_magicWord		(0x41504954)
#define AIS_XMT_START_WORD	(0x58535441)
#define AIS_RCV_START_WORD	(0x52535454)
#define AIS_XMT_START(a)	((unsigned int)AIS_XMT_START_WORD >> (32 - a))
#define AIS_RCV_START(a)	((unsigned int)AIS_RCV_START_WORD >> (32 - a))
#define AIS_opcode2ack(a)	((a & 0xF0FFFFFF) | 0x02000000)
#define roundUpTo(a, b)		( (a + (b - 1)) / b * b)


/************************************************************
* Local Typedef Declarations                                *
************************************************************/

typedef enum {
	AIS_OP_bootTable	= 0x58535907,
	AIS_OP_pllCfg		= 0x585359AA,	// NYI; opcode missing
	AIS_OP_spiClkCfg	= 0x585359BB,	// NYI; opcode missing
	AIS_OP_i2cClkCfg	= 0x585359CC,	// NYI; opcode missing
	AIS_OP_seqReadEn	= 0x58535963,
	AIS_OP_fastbootEn	= 0x58535913,
	AIS_OP_emifCfg	 	= 0x585359EE,	// NYI; opcode missing
	AIS_OP_sectionLoad	= 0x58535901,
	AIS_OP_cSectionLoad = 0x58535909,
	AIS_OP_sectionFill	= 0x5853590A,
	AIS_OP_fxnExec		= 0x5853590D,
	AIS_OP_jump			= 0x58535905,
	AIS_OP_jumpClose	= 0x58535906,
	AIS_OP_crcEn		= 0x58535903,
	AIS_OP_crcDis		= 0x58535904,
	AIS_OP_crcReq		= 0x58535902,
	AIS_OP_readWait		= 0x58535914,
	AIS_OP_rootPubKey	= 0x58535920,
	AIS_OP_secSecLoad	= 0x58535922,
	AIS_OP_encSecLoad	= 0x58535921,
	AIS_OP_startOver	= 0x58535908,
	AIS_OP_pingDevice	= 0x5853590B
} AIS_OP;


/************************************************************
* Local Function Declarations                               *
************************************************************/

static int AIS_SWS(AIS_IO_Handle hIO);
static int AIS_POS(AIS_IO_Handle hIO, int command);
static int AIS_OS(AIS_IO_Handle hIO, int command);
static unsigned int LOCAL_parseInt(void **cursor);
//static unsigned char LOCAL_parseChar(void **cursor);
static void LOCAL_parseSkip(void **cursor, int n);

//static int LOCAL_parseCRC(void **cursor, int size, int crc);
static int LOCAL_biteRead(AIS_IO_Handle hIO, void *buffer, int bytes, int timeout);
static int LOCAL_biteWrite(AIS_IO_Handle hIO, void *buffer, int bytes, int timeout);
static void LOCAL_word2ascii(char* word, char *ascii, int bytes);
static int LOCAL_ascii2word(char *ascii, char *word, int bytes);
static void LOCAL_delay(int N);


/************************************************************
* Local Variable Definitions                                *
************************************************************/


/************************************************************
* Global Variable Definitions
************************************************************/


/************************************************************
* Global Function Definitions                               *
************************************************************/

int AIS_parse(void *AIS_root, AIS_IO_Handle hIO)
{
	void **AIS_cursor = &AIS_root;
	int command, addr, size, type, sleep, data, crc, crcGuess, seek, exp, mask, val, args, i, status;
	int opsRead = 0;
	char secureMode = 0;

	// UART only: read "BOOTME "
	if (hIO->hostDevice == AIS_UART_BINARY || hIO->hostDevice == AIS_UART_ASCII)
	{
		char rcvInit[8];
		char corInit[8] = "BOOTME  ";

		DEBUG_printString( "(AIS Parse): Waiting for BOOTME...\r\n");
		status = (*hIO->readFxn)(hIO->hInst, rcvInit, 8, -1);

		// fail on incorrect sequence or IO error
		for (i = 0; i < 7; i++)
			status |= (rcvInit[i] == corInit[i]) ? 0 : -1;
		if (status < 0)
			return AIS_error;
	}

	// check for magic word first
	command = LOCAL_parseInt(AIS_cursor);
	status = (command == AIS_magicWord) ? AIS_inProgress : AIS_error;
	DEBUG_printString("(AIS Parse): Read magic word 0x");
  DEBUG_printHexInt(command);
  DEBUG_printString("\r\n");

	while (status == AIS_inProgress)
	{
		// perform synchronization on first pass
		if (opsRead == 0)
		{
			// perform SWS
			DEBUG_printString( "(AIS Parse): Performing Start-Word Sync...\r\n");
			status = AIS_SWS(hIO);
			if (status == AIS_error)
				break;		// fail if SWS fails

			// perform POS
			DEBUG_printString( "(AIS Parse): Performing Ping Opcode Sync...\r\n");
			status = AIS_POS(hIO, AIS_OP_pingDevice);
			if (status == AIS_error)
				continue;	// retry SWS if POS fails
		}

		// delay; give bootloader a chance to process previous command
		LOCAL_delay(hIO->opcodeDelay);

		// read a command
		command = LOCAL_parseInt(AIS_cursor);
		DEBUG_printString("(AIS Parse): Processing command 0x");
    DEBUG_printHexInt(opsRead++);
    DEBUG_printString(": 0x");
    DEBUG_printHexInt(command);
    DEBUG_printString("\r\n");


		// perform OS
		DEBUG_printString("(AIS Parse): Performing Opcode Sync...\r\n");
		status = AIS_OS(hIO, command);

		if (status == AIS_error)
			break;		// fail if OS fails

		switch(command)
		{
			case AIS_OP_bootTable:
				DEBUG_printString( "(AIS Parse): Loading boot table...\r\n");
				// read: type, addr, data, sleep
				type = LOCAL_parseInt(AIS_cursor);
				addr = LOCAL_parseInt(AIS_cursor);
				data = LOCAL_parseInt(AIS_cursor);
				sleep = LOCAL_parseInt(AIS_cursor);
				// send: type, addr, data, sleep
				status |= LOCAL_biteWrite(hIO, &type, 4, -1);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				status |= LOCAL_biteWrite(hIO, &data, 4, -1);
				status |= LOCAL_biteWrite(hIO, &sleep, 4, -1);
				if (secureMode)
				{
					// secure mode: send 128-byte key
					status |= LOCAL_biteWrite(hIO, *AIS_cursor, 128, -1);
					LOCAL_parseSkip(AIS_cursor, 128);
					DEBUG_printString( "(AIS Parse): Secure mode; sending signature.\r\n");
				}
				break;

			case AIS_OP_seqReadEn:
				// no extra IO required
				DEBUG_printString( "(AIS Parse): No slave memory present; Sequential Read Enable has no effect.\r\n");
				break;

			case AIS_OP_fastbootEn:
				// no extra IO required; configure peripheral for future transactions
				switch (hIO->hostDevice)
				{
					case AIS_UART_BINARY:
					case AIS_UART_ASCII:
						DEBUG_printString( "(AIS Parse): Setting UART baud rate to %u.", LOCAL_uartFbBaud);
						status |= (*hIO->cfgFxn)(hIO->hInst, LOCAL_uartFbBaud);		// set baud rate
						if (status < 0)
							DEBUG_printString( "(AIS Parse): Error configuring UART for Fastboot!\r\n");
						break;

					// TODO: more peripheral-specific configuration required?
					default:
						break;
				}
				DEBUG_printString( "(AIS Parse): Fastboot set.\r\n");
				break;

			case AIS_OP_sectionLoad:
			case AIS_OP_cSectionLoad:
				DEBUG_printString( (command == AIS_OP_sectionLoad) ? "(AIS Parse): Loading section...\r\n" : "(AIS Parse): Loading compressed section...\r\n");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				// send size
				size = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &size, 4, -1);
				// send data
				status |= LOCAL_biteWrite(hIO, *AIS_cursor, roundUpTo(size, 4), -1);
				LOCAL_parseSkip(AIS_cursor, roundUpTo(size, 4));
				DEBUG_printString("(AIS Parse): Loaded 0x");
        DEBUG_printHexInt(size);
        DEBUG_printString("-byte section to address 0x");
        DEBUG_printHexInt(addr);
        DEBUG_printString(".\r\n");
				break;

			case AIS_OP_sectionFill:
				DEBUG_printString( "(AIS Parse): Filling section...\r\n");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				// send size
				size = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &size, 4, -1);
				// send type
				type = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &type, 4, -1);
				// send pattern (data)
				data = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &data, 4, -1);
				DEBUG_printString( "(AIS Parse): Filled %u-byte section with pattern 0x%08X.", size, data);
				break;

			case AIS_OP_rootPubKey:
				DEBUG_printString( "(AIS Parse): Read root public key; entering secure mode.\r\n");
				// send exponent
				exp = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &exp, 4, -1);
				// send size
				size = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &size, 4, -1);
				// NOTE: use only upper half; value listed in 2-byte chunks (convert to bytes)
				size = (size >> 16) * 2;
				// send key
				status |= LOCAL_biteWrite(hIO, *AIS_cursor, size, -1);
				LOCAL_parseSkip(AIS_cursor, size);
				// enable secure mode
				secureMode = 1;
				break;

			case AIS_OP_secSecLoad:
				DEBUG_printString( "(AIS Parse): Loading secure section...\r\n");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				// send size
				size = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &size, 4, -1);
				// send reserved word
				val = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &val, 4, -1);
				// send data
				status |= LOCAL_biteWrite(hIO, *AIS_cursor, roundUpTo(size, 4), -1);
				LOCAL_parseSkip(AIS_cursor, roundUpTo(size, 4));
 				DEBUG_printString("(AIS Parse): Loaded 0x");
        DEBUG_printHexInt(size);
        DEBUG_printString("-byte section to address 0x");
        DEBUG_printHexInt(addr);
        DEBUG_printString(".\r\n");
				break;

			case AIS_OP_encSecLoad:
				DEBUG_printString( "(AIS Parse): Loading encoded section...\r\n");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				// send size
				size = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &size, 4, -1);
				// send reserved word
				val = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &val, 4, -1);
				// send data
				status |= LOCAL_biteWrite(hIO, *AIS_cursor, roundUpTo(size, 16), -1);
				LOCAL_parseSkip(AIS_cursor, roundUpTo(size, 16));
				DEBUG_printString("(AIS Parse): Loaded 0x");
        DEBUG_printHexInt(size);
        DEBUG_printString("-byte section to address 0x");
        DEBUG_printHexInt(addr);
        DEBUG_printString(".\r\n");
				break;

			case AIS_OP_crcDis:
				// no extra IO required
				DEBUG_printString( "(AIS Parse): CRC disabled.\r\n");
				break;

			case AIS_OP_crcEn:
				// no extra IO required
				DEBUG_printString( "(AIS Parse): CRC enabled.\r\n");
				break;

			case AIS_OP_crcReq:
				DEBUG_printString( "(AIS Parse): Requesting CRC...\r\n");
				// read computed CRC
				status |= LOCAL_biteRead(hIO, &crcGuess, 4, -1);
				crc = LOCAL_parseInt(AIS_cursor);
				if (crcGuess == crc)
				{
					// CRC succeeded.  Skip seek value to reach next opcode
					DEBUG_printString( "(AIS Parse): CRC passed!\r\n");
					LOCAL_parseSkip(AIS_cursor, 4);
				}
				else
				{
					// CRC error; send startover opcode and seek AIS
					DEBUG_printString( "(AIS Parse): CRC failed!  Sending STARTOVER...\r\n");
					status |= AIS_OS(hIO, AIS_OP_startOver);
					// seek AIS
					seek = LOCAL_parseInt(AIS_cursor);
   				DEBUG_printString("(AIS Parse): Loaded 0x");
          DEBUG_printHexInt(seek);
          DEBUG_printString("-byte seek applied.\r\n");
					LOCAL_parseSkip(AIS_cursor, seek);
				}
				break;
				
			case AIS_OP_readWait:
				DEBUG_printString( "(AIS Parse): Performing read-wait...\r\n");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				// send mask
				mask = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &mask, 4, -1);
				// send value
				val = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &val, 4, -1);
				if (secureMode)
				{
					// secure mode: send 128-byte key
					status |= LOCAL_biteWrite(hIO, *AIS_cursor, 128, -1);
					LOCAL_parseSkip(AIS_cursor, 128);
					DEBUG_printString( "(AIS Parse): Secure mode; sending signature.\r\n");
				}
				break;

			case AIS_OP_fxnExec:
				DEBUG_printString( "(AIS Parse): Executing function...\r\n");
				// send function number and number of arguments
				args = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &args, 4, -1);
				args = (args & 0xFFFF0000) >> 16;
				for (i = 0; i < args; i++)
				{
					// send arg i
					val = LOCAL_parseInt(AIS_cursor);
					status |= LOCAL_biteWrite(hIO, &val, 4, -1);
				}
				if (secureMode)
				{
					// secure mode: send 128-byte key
					status |= LOCAL_biteWrite(hIO, *AIS_cursor, 128, -1);
					LOCAL_parseSkip(AIS_cursor, 128);
					DEBUG_printString( "(AIS Parse): Secure mode; sending signature.\r\n");
				}
				break;

			case AIS_OP_jump:
				DEBUG_printString( "(AIS Parse): Performing jump...");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				if (secureMode)
				{
					// secure mode: send 128-byte key
					status |= LOCAL_biteWrite(hIO, *AIS_cursor, 128, -1);
					LOCAL_parseSkip(AIS_cursor, 128);
					DEBUG_printString( "(AIS Parse): Secure mode; sending signature.\r\n");
				}
				// TODO:  wait?
				DEBUG_printString( "(AIS Parse): Jump to address 0x");
        DEBUG_printHexInt(addr);
        DEBUG_printString(".\r\n");
				break;

			case AIS_OP_jumpClose:
				DEBUG_printString( "(AIS Parse): Performing jump and close...\r\n");
				// send address
				addr = LOCAL_parseInt(AIS_cursor);
				status |= LOCAL_biteWrite(hIO, &addr, 4, -1);
				if (secureMode)
				{
					// secure mode: send 128-byte key
					status |= LOCAL_biteWrite(hIO, *AIS_cursor, 128, -1);
					LOCAL_parseSkip(AIS_cursor, 128);
					DEBUG_printString( "(AIS Parse): Secure mode; sending signature.\r\n");
				}
				// parsing complete
				status = AIS_complete;
				DEBUG_printString( "(AIS Parse): AIS complete. Jump to address 0x");	// debug
        DEBUG_printHexInt(addr);
        DEBUG_printString(".\r\n");
				break;

			case AIS_OP_startOver:
				// control should never pass here; opcode is not present in AIS files
				break;

			// All other opcodes NYI
			case AIS_OP_pllCfg:
			case AIS_OP_spiClkCfg:
			case AIS_OP_i2cClkCfg:
			case AIS_OP_emifCfg:
			default:
				DEBUG_printString( "(AIS Parse): Unhandled opcode (0x.");
        DEBUG_printHexInt(command);
        DEBUG_printString(").\r\n");
				status = AIS_error;
		}
	}

	// UART only: read "   DONE"
	if (status == AIS_complete && (hIO->hostDevice == AIS_UART_BINARY || hIO->hostDevice == AIS_UART_ASCII))
	{
		char rcvEnd[8];
		char corEnd[8] = "   DONE";
		int i;

		DEBUG_printString( "(AIS Parse): Waiting for DONE...");
		status = (*hIO->readFxn)(hIO->hInst, rcvEnd, 8, -1);

		// fail on incorrect sequence or IO error
		for (i = 0; i < 7; i++)
			status |= (rcvEnd[i] == corEnd[i]) ? 0 : -1;
		status = (status < 0) ? AIS_error : AIS_complete;
	}

	DEBUG_printString("(AIS Parse): Parse completed.  (status:");
  if (status == AIS_complete)
  {
    DEBUG_printString("pass).\r\n");
    return E_PASS;
  }
  else
  {
    DEBUG_printString("fail).\r\n");
    return E_FAIL;
  }
}


// Local Functions --------------------------------------------------------------------------

// Start Word Sync function
static int AIS_SWS(AIS_IO_Handle hIO)
{
	int rcvWord = NULL;
	int xmtWord = AIS_XMT_START(hIO->ioBits);
	int status = 0;

	while (1)
	{
		// send xmt start
		status |= LOCAL_biteWrite(hIO, &xmtWord, hIO->ioBits / 8, -1);
		// temp (TODO: remove)
		if (status < 0)
		{
			status = 0;
			LOCAL_delay(hIO->opcodeDelay);
			continue;
		}
		// receive word
		status |= LOCAL_biteRead(hIO, &rcvWord, hIO->ioBits / 8, 5000);

		// fail on IO error
		if (status < 0)
			return AIS_error;

		// break if word is rcv start
		if (rcvWord == AIS_RCV_START(hIO->ioBits))
			break;
	}

	return AIS_inProgress;
}

static int AIS_POS(AIS_IO_Handle hIO, int command)
{
	int xmtWord = command;
	int rcvWord, status, i;

	// 1. send ping
	status = LOCAL_biteWrite(hIO, &xmtWord, 4, -1);
	// receive pong
	status |= LOCAL_biteRead(hIO, &rcvWord, 4, 5000);	

	// fail on improper response or IO error
	if (rcvWord != AIS_opcode2ack(xmtWord) || status < 0)
		return AIS_error;

	// tmp
	LOCAL_delay(hIO->opcodeDelay);

	// 2. send N
	xmtWord = hIO->posN;
	// send ping
	status |= LOCAL_biteWrite(hIO, &xmtWord, 4, -1);
	// receive pong
	status |= LOCAL_biteRead(hIO, &rcvWord, 4, -1);

	// fail on improper response or IO error
	if (rcvWord != hIO->posN || status < 0)
		return AIS_error;

	// 3. send/receive numerical sequence
	for (i = 1; i <= hIO->posN; i++)
	{
		// tmp
		LOCAL_delay(hIO->opcodeDelay);

		xmtWord = i;
		status |= LOCAL_biteWrite(hIO, &xmtWord, 4, -1);
		status |= LOCAL_biteRead(hIO, &rcvWord, 4, -1);

		// fail on improper response or IO error
		if (rcvWord != xmtWord || status < 0)
			return AIS_error;
	}

	return AIS_inProgress;
}

static int AIS_OS(AIS_IO_Handle hIO, int command)
{
	int xmtWord = command;
	int rcvWord;
	int status = 0;
	int retryCnt = 0;
	int retryCntMax = 10;

	while (1)
	{
		// send ping
		status |= LOCAL_biteWrite(hIO, &xmtWord, 4, -1);
		// receive pong
		if (status >= 0)
			status |= LOCAL_biteRead(hIO, &rcvWord, 4, -1);

		// fail on IO error
		if (status < 0)
		{
			LOCAL_delay(hIO->opcodeDelay);
			if (retryCnt++ >= retryCntMax)
			{
				DEBUG_printString( "(AIS Parse): Opcode Sync failed after %u consecutive I/O failures.", retryCnt);
				return AIS_error;
			}
			status = 0;
			continue;
		}

		// pass on proper response
		if (rcvWord == AIS_opcode2ack(xmtWord))
		{
			if (retryCnt > 0)
				DEBUG_printString( "(AIS Parse): Opcode Sync passed after %u consecutive I/O failures.", retryCnt);
			return AIS_inProgress;
		}
	}
}

// read int (4 bytes) and advance cursor
static unsigned int LOCAL_parseInt(void **cursor)
{
	unsigned char *bytes = *cursor;
	*cursor = (void *)(bytes + 4);

	return (unsigned int)(*bytes) | ((unsigned int)*(bytes + 1) << 8)
				| ((unsigned int)*(bytes + 2) << 16)
				| ((unsigned int)*(bytes + 3) << 24);
}

// read char (1 byte) and advance cursor
/*static unsigned char LOCAL_parseChar(void **cursor)
{
	unsigned char *bytes = *cursor;
	*cursor = (void *)(bytes + 1);

	return *bytes;
}*/

// advance cursor arbitrary number of bytes (ignore data)
static void LOCAL_parseSkip(void **cursor, int n)
{
	char *bytes = *cursor;
	*cursor = (void *)(bytes + n);
}

// advance cursor arbitrary number of bytes and compute crc
// NOTE: Not necessary; computed CRC is provided in AIS
/*static int LOCAL_parseCRC(void **cursor, int size, int crc)
{
	int *data_ptr = *cursor;
	int word, bit, msb, rem, i;

	// data_ptr : Start address of current section (must be 4-byte aligned)
	// size : Size of current section (in bytes)
	// crc : Old crc (from earlier sections) or zero (for first section)

	// Process complete 32-bit words
	for (i = 0; i < size / 4; i++)
	{
		// Load a word from memory
		word = *dataPtr++;

		// Update CRC
		for (bit = 31; bit >= 0; bit--)
		{
			msb = crc & 0x80000000;
			crc = ((word >> bit) & 0x1) ^ (crc << 1);
			if (msb)
				crc ^= 0x04C11DB7; // CRC-32 polynomial
		}
	}

	// Process incomplete last word if present
	rem = size % 4;
	if (rem)
	{
		word = *dataPtr;
		*cursor = ((char *)(*cursor) + rem);

		// Pad incomplete word with zeros to make it complete
		word = (word << rem * 8) >> rem * 8;

		// Update CRC
		for (bit = 31; bit >= 0; bit--)
		{
			msb = crc & 0x80000000;
			crc = ((word >> bit) & 0x1) ^ (crc << 1);
			if (msb)
				crc ^= 0x04C11DB7; // CRC-32 polynomial
		}
	}
}*/

static int LOCAL_biteRead(AIS_IO_Handle hIO, void *buffer, int bytes, int timeout)
{
	char *rcvPtr;
	int rcvSize, i;
	int asciiWord[2];	// assumes largest allowed IO size is 32 bits
	int status = 0;

	// perform IO transaction in N-bit "bites"
	for (i = 0; i < bytes / (hIO->ioBits / 8); i++)
	{
		rcvPtr	= (hIO->hostDevice == AIS_UART_ASCII) ?
					(void *)asciiWord :							// UART mode: receive ASCII string
					(char *)buffer + i * (hIO->ioBits / 8);		// normal: receive byte stream
		rcvSize	= (hIO->hostDevice == AIS_UART_ASCII) ?
					hIO->ioBits / 4 :
					hIO->ioBits / 8;

		status |= (*hIO->readFxn)(hIO->hInst, rcvPtr, rcvSize, timeout);

		if (hIO->hostDevice == AIS_UART_ASCII)
			status |= LOCAL_ascii2word(rcvPtr, (char *)buffer + i * (hIO->ioBits / 8), rcvSize / 2);	// convert from ascii

		LOCAL_delay(hIO->ioDelay);
		
		// TODO: what if bytes % (hIO->ioBits / 8) != 0?
		if (status < 0)
		{
			DEBUG_printString( "(AIS Parse): I/O Error in read!");
			break;
		}
	}

	return status;
}

static int LOCAL_biteWrite(AIS_IO_Handle hIO, void *buffer, int bytes, int timeout)
{
	char *xmtPtr;
	int xmtSize, i;
	int asciiWord[2];	// assumes largest allowed IO size is 32 bits
	int status = 0;
	
	// perform IO transaction in N-bit "bites"
	for (i = 0; i < bytes / (hIO->ioBits / 8); i++)
	{
		xmtPtr = (char *)buffer + i * (hIO->ioBits / 8);
		xmtSize = hIO->ioBits / 8;

		if (hIO->hostDevice == AIS_UART_ASCII)
		{
			// convert word to ASCII string
			LOCAL_word2ascii(xmtPtr, (void *)asciiWord, hIO->ioBits / 8);
			xmtPtr = (void *)asciiWord;
			xmtSize *= 2;
		}

		status |= (*hIO->writeFxn)(hIO->hInst, xmtPtr, xmtSize, timeout);
		LOCAL_delay(hIO->ioDelay);
		// TODO: what if bytes % (hIO->ioBits / 8) != 0?
		if (status < 0)
		{
			DEBUG_printString( "(AIS Parse): I/O Error in write!\r\n");
			break;
		}
	}

	return status;
}

static void LOCAL_word2ascii(char* word, char *ascii, int bytes)
{
	char c;
	int i;

	for (i = 0; i < bytes; i++)
	{
		c = *(word + i) & 0xF;
		*(ascii + 2 * i) = c + (c <= 9) ? '0' : ('A' - 0xA);
		c = (*(word + i) & 0xF0) >> 4;
		*(ascii + 2 * i + 1) = c + (c <= 9) ? '0' : ('A' - 0xA);
	}
}

static int LOCAL_ascii2word(char *ascii, char *word, int bytes)
{
	char c;
	int i;

	for (i = 0; i < bytes * 2; i++)
	{
		c = ascii[i];
		if (c >= '0' && c <= '9')
			c -= '0';
		else if (c >= 'A' && c <= 'F')
			c -= 'A' + 0xA;
		else if (c >= 'a' && c <= 'f')
			c -= 'a' + 0xA;
		else
			return -1;

		word[i / 2] &= 0xF0 >> 4 * (i % 2);		// clear lower/upper nibble (alternate)
		word[i / 2] |= c << 4 * (i % 2);		// add in lower/upper nibble (alternate)
	}

	return 0;
}

static void LOCAL_delay(int N)
{ int j; for (j = 0; j < N; j++) asm(" nop"); }

























