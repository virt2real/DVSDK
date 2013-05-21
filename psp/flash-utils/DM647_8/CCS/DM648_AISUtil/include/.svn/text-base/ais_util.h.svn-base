// ais_util.h -------------------------------------------------------------------------------
//
// Parses an AIS loaded into memory as a char or int array.  Uses DSP/BIOS and requires
// statically-defined LOG object named trace.
// Joseph Coombs, 4-1-08
//
// Copyright (C) 2007 Texas Instruments Incorporated
// All Rights Reserved
// ------------------------------------------------------------------------------------------


// Global Typedefs --------------------------------------------------------------------------

// Generic Function Type
typedef Uint32 (*FxnPtr)();

typedef enum {
	AIS_error		= -1,
	AIS_inProgress	= 0,
	AIS_complete	= 1
} AIS_status;

typedef enum {
	AIS_I2C = 0,
	AIS_UHPI,
	AIS_SPI,
	AIS_UART_BINARY,
	AIS_UART_ASCII
} AIS_device;

typedef struct {
	FxnPtr readFxn, writeFxn, cfgFxn;	// external I/O fxns
	int posN, ioBits;				// length of POS sequence, bits per I/O transaction
	int ioDelay, opcodeDelay;		// delay counts between IO packets, opcodes
	AIS_device hostDevice;
	void *hInst;					// IO handle; pass back to external I/O fxns
} AIS_IO_Obj, *AIS_IO_Handle;


// Global Function Declarations -------------------------------------------------------------
extern far int AIS_parse(void *AIS_root, AIS_IO_Handle hIO);

