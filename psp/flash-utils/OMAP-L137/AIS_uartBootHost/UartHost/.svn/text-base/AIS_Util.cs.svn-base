// ======================================================================= 
//  TEXAS INSTRUMENTS, INC.                                                
// ----------------------------------------------------------------------- 
//                                                                         
// AIS_Util.cs -- Implements AIS_Parser class (C#)
//                                                                         
// Rev 0.0.1                                                               
//                                                                         
//  USAGE                                                                  
//      Include AIS_Util namespace in your project and use the following
//      constructor:
//                                                                         
//          AIS_Parser parser = new AIS_Parser
//                                  (
//                                      AIS_Parser.AIS_<bootPeripheral>,
//                                      FxnDelegate_msg_log,
//                                      FxnDelegate_<bootPeripheral>_read,
//                                      FxnDelegate_<bootPeripheral>_write
//                                  );
//
//      Call parsing function using the contents of a binary AIS file
//      stored in a byte array:
//
//          parser.boot(ais_file_contents);
//                                                                         
//  DESCRIPTION                                                            
//      Parses a binary AIS file passed in as a byte array.  Uses external
//      functions (passed as delegates) for I/O read and write and message
//      logging.  Performs all host operations as described in "Using the
//      D800K001 Bootloader" application note for I2C slave, SPI slave, and
//      UART boot modes.                                                                   
//                                                                         
// ----------------------------------------------------------------------- 
//            Copyright (c) 2008 Texas Instruments, Incorporated.          
//                           All Rights Reserved.                          
// ======================================================================= 

using System;
using System.Collections.Generic;
using System.Text;
using System.Threading;

namespace AIS_Util
{
    // host function delegates (rx, tx, log)
    delegate int ReadFxnDelegate(byte[] rcvBuf, int index, int rcvSize, int timeout);
    delegate int WriteFxnDelegate(byte[] xmtBuf, int index, int xmtSize, int timeout);
    delegate void LogFxnDelegate(String line);

    class AIS_Parser
    {
        // AIS constants
	    public const int AIS_error =      -1;
	    public const int AIS_inProgress =  0;
	    public const int AIS_complete =    1;

	    public const int AIS_I2C =  0;
        public const int AIS_SPI =  1;
	    public const int AIS_UART = 2;

        private const uint AIS_magicWord =       0x41504954;
        private const uint AIS_XMT_START_WORD =  0x58535441;
        private const uint AIS_RCV_START_WORD =  0x52535454;

        private const uint AIS_OP_bootTable =    0x58535907;
        private const uint AIS_OP_seqReadEn =    0x58535963;
        private const uint AIS_OP_sectionLoad =  0x58535901;
        private const uint AIS_OP_cSectionLoad = 0x58535909;
        private const uint AIS_OP_sectionFill =  0x5853590A;
        private const uint AIS_OP_fxnExec =      0x5853590D;
        private const uint AIS_OP_jump =         0x58535905;
        private const uint AIS_OP_jumpClose =    0x58535906;
        private const uint AIS_OP_crcEn =        0x58535903;
        private const uint AIS_OP_crcDis =       0x58535904;
        private const uint AIS_OP_crcReq =       0x58535902;
        private const uint AIS_OP_readWait =     0x58535914;
        private const uint AIS_OP_startOver =    0x58535908;
        private const uint AIS_OP_pingDevice =   0x5853590B;

        // public data members
        public int posN, ioBits, ioDelay, opcodeDelay, ioTimeout;
        public bool waitBOOTME;
        // private members
        private int hostDevice;
        private ReadFxnDelegate readFxn;
        private WriteFxnDelegate writeFxn;
        private LogFxnDelegate logFxn;

        public AIS_Parser(int hostType, LogFxnDelegate hostLogFxn, ReadFxnDelegate hostReadFxn, WriteFxnDelegate hostWriteFxn)
        {
            // apply specified params
            hostDevice = hostType;
            readFxn = hostReadFxn;
            writeFxn = hostWriteFxn;
            logFxn = hostLogFxn;

            // use defaults for others
            posN = 2;
            ioBits = 8;
            ioDelay = 0;
            opcodeDelay = 5;   // 5ms
            ioTimeout = 5000;  // 5s
            waitBOOTME = true;
        }

        // utility functions (were C macros)
        private uint AIS_XMT_START(int bits)
        {
            // return (bits) MSBs or AIS start word
            return AIS_XMT_START_WORD >> (32 - bits);
        }

        private uint AIS_RCV_START(int bits)
        {
            // return (bits) MSBs or AIS start word ACK
            return AIS_RCV_START_WORD >> (32 - bits);
        }

        private uint AIS_opcode2ack(uint opcode)
        {
            // return opcode ACK
            return (opcode & 0xF0FFFFFF) | 0x02000000;
        }

        private int LOCAL_roundUpTo(int num, int mod)
        {
            // round (num) up to nearest multiple of (mod)
            return ( (num + (mod - 1)) / mod * mod);
        }

        private uint LOCAL_b2uint(byte[] ba)
        {
            // convert byte array to uint with little endian order
            return (uint)ba[0] + ((uint)ba[1] << 8) + ((uint)ba[2] << 16) + ((uint)ba[3] << 24);
        }

        private byte[] LOCAL_uint2b(uint ui)
        {
            // convert uint to byte array with little endian order
            byte[] ba = new byte[4];
            ba[0] = (byte)(ui & 0xFF);
            ba[1] = (byte)((ui >> 8) & 0xFF);
            ba[2] = (byte)((ui >> 16) & 0xFF);
            ba[3] = (byte)((ui >> 24) & 0xFF);
            return ba;
        }

        private void LOCAL_delay(int N)
        {
            Thread.Sleep(N);
        }

        // major function
        public int boot(byte[] AIS_Contents)
        {
	        int AIS_Cursor = 0;
            uint command, addr, size, type,
                sleep, data, crc, crcGuess,
                seek, mask, val, args;
            byte[] crcGuessB = new byte[4];
            int i, status;
	        int opsRead = 0;
	        
            // check for magic word first
            command = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
            status = (command == AIS_magicWord) ? AIS_inProgress : AIS_error;
            logFxn(String.Format("(AIS Parse): Read magic word 0x{0:X8}.", command));

        	// UART only: read "BOOTME "
	        if (status == AIS_inProgress && hostDevice == AIS_UART && waitBOOTME)
	        {
		        byte[] rcvInit = new byte[8];
                byte[] corInit = { (byte)'B', (byte)'O', (byte)'O', (byte)'T',
                                   (byte)'M', (byte)'E', (byte)' ', (byte)0 };

                // use longer than normal timeout
                logFxn("(AIS Parse): Waiting for BOOTME...");
		        status = readFxn(rcvInit, 0, 8, ioTimeout * 10);

		        // fail on incorrect sequence or IO error
		        for (i = 0; i < 7; i++)
                    if (rcvInit[i] != corInit[i])
                    {
                        logFxn("(AIS Parse): Read invalid BOOTME string.");
                        status = AIS_error;
                        break;
                    }
	        }

	        while (status == AIS_inProgress)
	        {
		        // perform synchronization on first pass
		        if (opsRead == 0)
		        {
			        // perform SWS
			        logFxn("(AIS Parse): Performing Start-Word Sync...");
			        status = AIS_SWS();
			        if (status == AIS_error)
				        break;		// fail if SWS fails

			        // perform POS
			        logFxn("(AIS Parse): Performing Ping Opcode Sync...");
			        status = AIS_POS(AIS_OP_pingDevice);
			        if (status == AIS_error)
				        continue;	// retry SWS if POS fails
		        }

		        // delay; give bootloader a chance to process previous command
		        LOCAL_delay(opcodeDelay);

		        // read a command
		        command = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
		        logFxn( String.Format("(AIS Parse): Processing command {0}: 0x{1:X8}.", opsRead++, command) );

		        // perform OS
		        logFxn("(AIS Parse): Performing Opcode Sync...");
		        status = AIS_OS(command);

		        if (status == AIS_error)
			        break;		// fail if OS fails

		        switch(command)
		        {
			        case AIS_OP_bootTable:
				        logFxn("(AIS Parse): Loading boot table...");
				        // read: type, addr, data, sleep
				        type = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        addr = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        data = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        sleep = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        // send: type, addr, data, sleep
				        status |= LOCAL_bufWrite(LOCAL_uint2b(type), 0, 4, ioTimeout);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(addr), 0, 4, ioTimeout);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(data), 0, 4, ioTimeout);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(sleep), 0, 4, ioTimeout);
				        break;

			        case AIS_OP_seqReadEn:
				        // no extra IO required
				        logFxn("(AIS Parse): No slave memory present; Sequential Read Enable has no effect.");
				        break;

			        case AIS_OP_sectionLoad:
                    case AIS_OP_cSectionLoad:
                        logFxn("(AIS Parse): Loading section...");
				        // send address
				        addr = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(addr), 0, 4, ioTimeout);
				        // send size
				        size = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(size), 0, 4, ioTimeout);
				        // send data
				        status |= LOCAL_bufWrite(AIS_Contents, AIS_Cursor, LOCAL_roundUpTo((int)size, 4), ioTimeout);
                        LOCAL_parseSkip(ref AIS_Cursor, LOCAL_roundUpTo((int)size, 4));
				        logFxn( String.Format("(AIS Parse): Loaded {0}-byte section to address 0x{1:X8}.", size, addr) );
                        break;

			        case AIS_OP_sectionFill:
				        logFxn("(AIS Parse): Filling section...");
				        // send address
				        addr = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(addr), 0, 4, ioTimeout);
				        // send size
				        size = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(size), 0, 4, ioTimeout);
				        // send type
				        type = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(type), 0, 4, ioTimeout);
				        // send pattern (data)
				        data = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(data), 0, 4, ioTimeout);
				        logFxn( String.Format("(AIS Parse): Filled {0}-byte section with pattern 0x{1:X8}.", size, data) );
				        break;

			        case AIS_OP_crcDis:
				        // no extra IO required
				        logFxn("(AIS Parse): CRC disabled.");
				        break;

			        case AIS_OP_crcEn:
				        // no extra IO required
				        logFxn("(AIS Parse): CRC enabled.");
				        break;

			        case AIS_OP_crcReq:
				        logFxn("(AIS Parse): Requesting CRC...");
				        // read computed CRC
				        status |= LOCAL_bufRead(crcGuessB, 0, 4, ioTimeout);
                        crcGuess = LOCAL_b2uint(crcGuessB);
				        crc = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        if (crcGuess == crc)
				        {
					        // CRC succeeded.  Skip seek value to reach next opcode
					        logFxn("(AIS Parse): CRC passed!");
					        LOCAL_parseSkip(ref AIS_Cursor, 4);
				        }
				        else
				        {
					        // CRC error; send startover opcode and seek AIS
					        logFxn("(AIS Parse): CRC failed!  Sending STARTOVER...");
					        status |= AIS_OS(AIS_OP_startOver);
					        // seek AIS
					        seek = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
					        logFxn( String.Format("(AIS Parse): {0}-byte seek applied.", seek) );
                            LOCAL_parseSkip(ref AIS_Cursor, (int)seek);
				        }
				        break;
        				
			        case AIS_OP_readWait:
				        logFxn("(AIS Parse): Performing read-wait...");
				        // send address
				        addr = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(addr), 0, 4, ioTimeout);
				        // send mask
				        mask = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(mask), 0, 4, ioTimeout);
				        // send value
				        val = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(val), 0, 4, ioTimeout);
				        break;

			        case AIS_OP_fxnExec:
				        logFxn("(AIS Parse): Executing function...");
				        // send function number and number of arguments
				        args = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(args), 0, 4, ioTimeout);
				        args = (args & 0xFFFF0000) >> 16;
				        for (i = 0; i < args; i++)
				        {
					        // send arg i
					        val = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
					        status |= LOCAL_bufWrite(LOCAL_uint2b(val), 0, 4, ioTimeout);
				        }
				        break;

			        case AIS_OP_jump:
				        logFxn("(AIS Parse): Performing jump...");
				        // send address
				        addr = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(addr), 0, 4, ioTimeout);
				        logFxn( String.Format("(AIS Parse): Jump to address 0x{0:X8}.", addr) );
				        break;

			        case AIS_OP_jumpClose:
				        logFxn("(AIS Parse): Performing jump and close...");
				        // send address
				        addr = LOCAL_parseInt(AIS_Contents, ref AIS_Cursor);
				        status |= LOCAL_bufWrite(LOCAL_uint2b(addr), 0, 4, ioTimeout);
				        // parsing complete
				        status = AIS_complete;
				        logFxn( String.Format("(AIS Parse): AIS complete. Jump to address 0x{0:X8}.", addr) );
				        break;

			        case AIS_OP_startOver:
				        // control should never pass here; opcode is not present in AIS files
				        break;

			        // Unrecognized opcode
			        default:
				        logFxn( String.Format("(AIS Parse): Unhandled opcode (0x{0:X8}).", command) );
				        status = AIS_error;
                        break;
		        }
	        }

	        // UART only: read "   DONE"
	        if (status == AIS_complete && hostDevice == AIS_UART)
	        {
		        byte[] rcvEnd = new byte[8];
                byte[] corEnd = { (byte)' ', (byte)' ', (byte)' ', (byte)'D',
                                  (byte)'O', (byte)'N', (byte)'E', (byte)0 };

		        logFxn("(AIS Parse): Waiting for DONE...");
		        status = readFxn(rcvEnd, 0, 8, ioTimeout);

		        // fail on incorrect sequence or IO error
		        for (i = 0; i < 7; i++)
                    if (rcvEnd[i] != corEnd[i])
                    {
                        logFxn("(AIS Parse): Read invalid DONE string.");
                        status = AIS_error;
                        break;
                    }

                // success
                status = AIS_complete;
	        }

            if (status == AIS_complete)
	            logFxn("(AIS Parse): Boot completed successfully.");
            else
                logFxn("(AIS Parse): Boot aborted.");
	        return status;
        }

        // Sync Functions
        private int AIS_SWS()
        {
            uint rcvWord = 0;
            byte[] rcvWordB = new byte[4];
            uint xmtWord = AIS_XMT_START(ioBits);
            int status = 0;

            while (true)
            {
                // send xmt start
                status |= LOCAL_bufWrite(LOCAL_uint2b(xmtWord), 0, ioBits / 8, ioTimeout);
                if (status < 0)
                {
                    status = 0;
                    LOCAL_delay(opcodeDelay);
                    continue;
                }
                // receive word
                status |= LOCAL_bufRead(rcvWordB, 0, ioBits / 8, ioTimeout);
                rcvWord = LOCAL_b2uint(rcvWordB);

                // fail on IO error
                if (status < 0)
                    return AIS_error;

                // break if word is rcv start
                if (rcvWord == AIS_RCV_START(ioBits))
                    break;
            }

            return AIS_inProgress;
        }

        private int AIS_POS(uint command)
        {
            uint xmtWord = command;
            uint rcvWord;
            byte[] rcvWordB = new byte[4];
            int status, i;

            // 1. send ping
            status = LOCAL_bufWrite(LOCAL_uint2b(xmtWord), 0, 4, ioTimeout);
            // receive pong
            status |= LOCAL_bufRead(rcvWordB, 0, 4, ioTimeout);
            rcvWord = LOCAL_b2uint(rcvWordB);

            // fail on improper response or IO error
            if (rcvWord != AIS_opcode2ack(xmtWord) || status < 0)
                return AIS_error;

            LOCAL_delay(opcodeDelay);

            // 2. send N
            xmtWord = (uint)posN;
            // send ping
            status |= LOCAL_bufWrite(LOCAL_uint2b(xmtWord), 0, 4, ioTimeout);
            // receive pong
            status |= LOCAL_bufRead(rcvWordB, 0, 4, ioTimeout);
            rcvWord = LOCAL_b2uint(rcvWordB);

            // fail on improper response or IO error
            if (rcvWord != posN || status < 0)
                return AIS_error;

            // 3. send/receive numerical sequence
            for (i = 1; i <= posN; i++)
            {
                LOCAL_delay(opcodeDelay);

                xmtWord = (uint)i;
                status |= LOCAL_bufWrite(LOCAL_uint2b(xmtWord), 0, 4, ioTimeout);
                status |= LOCAL_bufRead(rcvWordB, 0, 4, ioTimeout);
                rcvWord = LOCAL_b2uint(rcvWordB);

                // fail on improper response or IO error
                if (rcvWord != xmtWord || status < 0)
                    return AIS_error;
            }

            return AIS_inProgress;
        }

        private int AIS_OS(uint command)
        {
            uint xmtWord = command;
            uint rcvWord = 0;
            byte[] rcvWordB = new byte[4];
            int status = 0;
            int retryCnt = 0;
            int retryCntMax = 10;

            while (true)
            {
                // send ping
                status |= LOCAL_bufWrite(LOCAL_uint2b(xmtWord), 0, 4, ioTimeout);
                // receive pong
                if (status >= 0)
                {
                    status |= LOCAL_bufRead(rcvWordB, 0, 4, ioTimeout);
                    rcvWord = LOCAL_b2uint(rcvWordB);
                }

                // fail on IO error
                if (status < 0)
                {
                    LOCAL_delay(opcodeDelay);
                    if (retryCnt++ >= retryCntMax)
                    {
                        logFxn(String.Format("(AIS Parse): Opcode Sync failed after {0} consecutive I/O failures.", retryCnt));
                        return AIS_error;
                    }
                    status = 0;
                    continue;
                }

                // pass on proper response
                if (rcvWord == AIS_opcode2ack(xmtWord))
                {
                    if (retryCnt > 0)
                        logFxn( String.Format("(AIS Parse): Opcode Sync passed after {0} consecutive I/O failures.", retryCnt) );
                    return AIS_inProgress;
                }
            }
        }

        // read int (4 bytes) and advance cursor
        private uint LOCAL_parseInt(byte[] ais, ref int cursor)
        {
            uint token = 0;

            // assemble 4-byte uint in little-endian order
            for (int i = 0; i < 4; i++)
                token += (uint)(ais[cursor + i] << (i * 8));

            cursor += 4;
            return token;
        }

        // advance cursor arbitrary number of bytes (ignore data)
        private void LOCAL_parseSkip(ref int cursor, int n)
        {
	        cursor += n;
        }

        private int LOCAL_bufRead(byte[] buffer, int index, int bytes, int timeout)
        {
	        int rcvSize = ioBits / 8;
	        int status = 0;

            // check that we can read specified byte count cleanly
            if (bytes % rcvSize != 0)
            {
                logFxn( String.Format("(AIS Parse): Cannot read {0} bytes in chunks of {1}!", bytes, rcvSize) );
                return AIS_error;
            }

	        // perform IO transaction in N-bit words
	        for (int i = 0; i < bytes / rcvSize; i++)
	        {
		        status |= readFxn(buffer, index + i * rcvSize, rcvSize, timeout);
		        LOCAL_delay(ioDelay);

		        if (status < 0)
		        {
			        logFxn("(AIS Parse): I/O Error in read!");
			        break;
		        }
	        }

	        return status;
        }

        private int LOCAL_bufWrite(byte[] buffer, int index, int bytes, int timeout)
        {
	        int xmtSize = ioBits / 8;
	        int status = 0;

            // check that we can write specified byte count cleanly
            if (bytes % xmtSize != 0)
            {
                logFxn( String.Format("(AIS Parse): Cannot write {0} bytes in chunks of {1}!", bytes, xmtSize) );
                return AIS_error;
            }
        	
	        // perform IO transaction in N-bit words
	        for (int i = 0; i < bytes / xmtSize; i++)
	        {
		        status |= writeFxn(buffer, index + i * xmtSize, xmtSize, timeout);
		        LOCAL_delay(ioDelay);

		        if (status < 0)
		        {
			        logFxn("(AIS Parse): I/O Error in write!");
			        break;
		        }
	        }

	        return status;
        }
    }
}
