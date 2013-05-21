From Joe Coombs (j-coombs@ti.com):

1. Create a struct of type AIS_IO_Obj, which contains information on the peripheral device to be used during the AIS boot: 
    a. Function pointers for read operation, write operation, and a config function (currently unused).  The read and write functions take parameters: device instance pointer (see f, below), buffer pointer, buffer size, and timeout value. 
    b. Length of ping opcode sync sequence (typically 2) 
    c. I/O word width (typically 8-, 16-, or 32-bit) 
    d. Delay counts (used to force waits between commands) 
    e. Code indicating peripheral type (currently used to distinguish UART boot cases to insert “BOOTME” step) 
    f. Peripheral instance pointer.  Parameter passed to read/write functions.  In my program, I use this to pass a PSP driver handle. 
2. Load the AIS contents into memory (i.e. in a big array). 
3. Call AIS_parse with two parameters: a pointer to the AIS contents, and a pointer to the AIS_IO_Obj struct. 
 

Example:

// prepare to parse AIS
AIS_IO_Obj IOo;
IOo.readFxn       = LOCAL_i2cRead;
IOo.writeFxn      = LOCAL_i2cWrite;
IOo.posN          = 2;                    // length 2 POS sequence
IOo.ioBits        = 16;                   // 16-bit IO transactions
IOo.ioDelay       = 0x7FFF;               // delay between I/O transactions (count from 0 to delay) // I2C0: 0x7FFF; I2C1: 0x7FFFF
IOo.opcodeDelay = 0x3FFFF;                // delay between opcodes
IOo.hostDevice    = AIS_I2C;
IOo.hInst         = hBlock;               // passed back to local IO fxns

 

// configure I2C as master
self->flags = PSP_I2C_MASTER | PSP_I2C_START | PSP_I2C_STOP;

 

// parse AIS
status = AIS_parse(aisArray, &IOo);


The code in ais_util.c should be fairly self-explanatory.  The only things that should probably be removed are 
the LOG_printf calls, which I used for debug purposes.  Let me know if you have any questions or suggestions; 
I’ll be using this program again in the next couple weeks to validate the Primus bootloader on silicon.

