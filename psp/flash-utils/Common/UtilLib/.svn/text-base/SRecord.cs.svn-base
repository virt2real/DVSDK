using System;
using System.Text;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Threading;
using System.Globalization;

namespace UtilLib
{
    class SRecord
    {
        /// <summary>
        /// Function to convert the input filestream into an byte array in S-record format.
        /// </summary>
        /// <param name="inputFileStream">The input filestream that encapsulates the
        /// input binary file.</param>
        /// <param name="startAddr">The starting address of the RAM location where the binary data
        /// encapsulated by the S-record will be stored.</param>
        /// <returns>A byte array of the file data.</returns>
        public static Byte[] bin2srec(Stream inputStream, UInt32 startAddr)
        {
            Int64 totalLen;
            BinaryReader fileBR = new BinaryReader(inputStream);
            StringBuilder fileSB;
            String fileName;
            String shortFileName;
            Byte[] currChar = new Byte[1];
            Byte[] currDataRecord;
            Int32 i, checksum8 = 0;
            Int32 recordSize = 16;
            UInt32 memAddr = startAddr;

            // Set the actual length
            totalLen = fileBR.BaseStream.Length;
            fileSB = new StringBuilder(4 * (int)totalLen);

            // Set S-record filename (real name or fake)
            if (inputStream is FileStream)
                fileName = ((FileStream)inputStream).Name;
            else
                fileName = "ublDaVinci.bin";

            // Make sure we are at the right place in the stream
            fileBR.BaseStream.Seek(0x0, SeekOrigin.Begin);

            // Get filename (this is S-record module name)
            if (Path.HasExtension(fileName))
                shortFileName = Path.GetFileNameWithoutExtension(fileName) + ".hex";
            else
                shortFileName = Path.GetFileName(fileName) + ".hex";

            // Make sure S-record module name fits in 20 byte field
            if (shortFileName.Length > 20)
                shortFileName = shortFileName.Substring(0, 20);

            // Create first s-record (S0 record)
            fileSB.Append("S0");
            // Write length field
            fileSB.AppendFormat("{0:X2}", shortFileName.Length + 3);
            checksum8 += (Byte)(shortFileName.Length + 3);
            // Write address field
            fileSB.Append("0000");
            // Write name field
            for (i = 0; i < shortFileName.Length; i++)
            {
                currChar = (new ASCIIEncoding()).GetBytes(shortFileName.Substring(i, 1));
                checksum8 += currChar[0];
                fileSB.AppendFormat("{0:X2}", currChar[0]);
            }
            // Write Checksum field
            fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

            // Write collection of S3 records (actual binary data)
            i = (Int32)totalLen;

            while (i >= recordSize)
            {
                checksum8 = 0;
                // Write S3 record label
                fileSB.Append("S3");
                // Write length field (4 address bytes + 16 data bytes + 1 checksum byte)
                fileSB.AppendFormat("{0:X2}", recordSize + 5);
                checksum8 += (recordSize + 5);

                // Write address field and update it
                fileSB.AppendFormat("{0:X8}", memAddr);
                currDataRecord = System.BitConverter.GetBytes(memAddr);
                for (int j = 0; j < 4; j++)
                {
                    checksum8 += currDataRecord[j];
                }

                // Write out the bytes of data
                currDataRecord = fileBR.ReadBytes(recordSize);
                for (int j = 0; j < recordSize; j++)
                {
                    fileSB.AppendFormat("{0:X2}", currDataRecord[j]);
                    checksum8 += currDataRecord[j];
                }
                //Write out checksum and linefeed character
                fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

                memAddr += (UInt32)recordSize; i -= recordSize;
            }

            // Finish out the record if anything is left over
            if (i > 0)
            {
                checksum8 = 0;
                // Write S3 record label
                fileSB.Append("S3");
                // Write length field (4 address bytes + 16 data bytes + 1 checksum byte)
                fileSB.AppendFormat("{0:X2}", i + 5);
                checksum8 += (i + 5);

                // Write address field and update it
                fileSB.AppendFormat("{0:X8}", memAddr);
                currDataRecord = System.BitConverter.GetBytes(memAddr);
                for (int j = 0; j < 4; j++)
                {
                    checksum8 += currDataRecord[j];
                }

                // Write out the bytes of data
                currDataRecord = fileBR.ReadBytes(i);
                for (int j = 0; j < i; j++)
                {
                    fileSB.AppendFormat("{0:X2}", currDataRecord[j]);
                    checksum8 += currDataRecord[j];
                }
                //Write out checksum and linefeed character
                fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

                memAddr += (UInt32)i; i = 0;

            }

            // Write out the final record (S7 record)
            checksum8 = 0;
            // Write S7 record label
            fileSB.Append("S7");
            // Write length field (4 address bytes + 1 checksum byte)
            fileSB.AppendFormat("{0:X2}", 5);
            checksum8 += 5;

            // Write execution start address field and update it
            fileSB.AppendFormat("{0:X8}", startAddr);
            currDataRecord = System.BitConverter.GetBytes(startAddr);
            for (int j = 0; j < 4; j++)
            {
                checksum8 += currDataRecord[j];
            }
            //Write out checksum and linefeed character
            fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

            return (new ASCIIEncoding()).GetBytes(fileSB.ToString());

        }
        
        /// <summary>
        /// Function to convert the input binary byte array into an byte array in S-record format.
        /// </summary>
        /// <param name="inputFileStream">The input filestream that encapsulates the
        /// input binary file.</param>
        /// <param name="startAddr">The starting address of the RAM location where the binary data
        /// encapsulated by the S-record will be stored.</param>
        /// <param name="recordSize">The size in bytes of each S-record (line) of the output.</param>
        /// <returns>A byte array of the file data.</returns>
        public static Byte[] bin2srec(Byte[] inputData, UInt32 startAddr, Int32 recordSize)
        {
            Int64 totalLen;
            StringBuilder fileSB;
            String fileName;
            String shortFileName;
            Byte[] currChar = new Byte[1];
            Byte[] currDataRecord;
            Int32 i, checksum8 = 0;
            UInt32 memAddr = startAddr;

            // Set the actual length
            totalLen = inputData.Length;
            fileSB = new StringBuilder(4 * (int)totalLen);

            // Set S-record filename (real name or fake)
            //if (inputStream is FileStream)
            //    fileName = ((FileStream)inputStream).Name;
            //else
                fileName = "ublDaVinci.bin";

            // Make sure we are at the right place in the stream
            //fileBR.BaseStream.Seek(0x0, SeekOrigin.Begin);

            // Get filename (this is S-record module name)
            if (Path.HasExtension(fileName))
                shortFileName = Path.GetFileNameWithoutExtension(fileName) + ".hex";
            else
                shortFileName = Path.GetFileName(fileName) + ".hex";

            // Make sure S-record module name fits in 20 byte field
            if (shortFileName.Length > 20)
                shortFileName = shortFileName.Substring(0, 20);

            // Create first s-record (S0 record)
            fileSB.Append("S0");
            // Write length field
            fileSB.AppendFormat("{0:X2}", shortFileName.Length + 3);
            checksum8 += (Byte)(shortFileName.Length + 3);
            // Write address field
            fileSB.Append("0000");
            // Write name field
            for (i = 0; i < shortFileName.Length; i++)
            {
                currChar = (new ASCIIEncoding()).GetBytes(shortFileName.Substring(i, 1));
                checksum8 += currChar[0];
                fileSB.AppendFormat("{0:X2}", currChar[0]);
            }
            // Write Checksum field
            fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

            // Write collection of S3 records (actual binary data)
            i = (Int32)totalLen;

            while (i >= recordSize)
            {
                checksum8 = 0;
                // Write S3 record label
                fileSB.Append("S3");
                // Write length field (4 address bytes + 16 data bytes + 1 checksum byte)
                fileSB.AppendFormat("{0:X2}", recordSize + 5);
                checksum8 += (recordSize + 5);

                // Write address field and update it
                fileSB.AppendFormat("{0:X8}", memAddr);
                currDataRecord = System.BitConverter.GetBytes(memAddr);
                for (int j = 0; j < 4; j++)
                {
                    checksum8 += currDataRecord[j];
                }

                // Write out the bytes of data
                //currDataRecord = fileBR.ReadBytes(recordSize);
                
                for (int j = 0; j < recordSize; j++)
                {
                    //fileSB.AppendFormat("{0:X2}", currDataRecord[j]);
                    fileSB.AppendFormat("{0:X2}", inputData[j + (memAddr - startAddr)]);
                    //checksum8 += currDataRecord[j];
                    checksum8 += inputData[j + (memAddr - startAddr)];
                }
                //Write out checksum and linefeed character
                fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

                memAddr += (UInt32)recordSize; i -= recordSize;
            }

            // Finish out the record if anything is left over
            if (i > 0)
            {
                checksum8 = 0;
                // Write S3 record label
                fileSB.Append("S3");
                // Write length field (4 address bytes + 16 data bytes + 1 checksum byte)
                fileSB.AppendFormat("{0:X2}", i + 5);
                checksum8 += (i + 5);

                // Write address field and update it
                fileSB.AppendFormat("{0:X8}", memAddr);
                currDataRecord = System.BitConverter.GetBytes(memAddr);
                for (int j = 0; j < 4; j++)
                {
                    checksum8 += currDataRecord[j];
                }

                // Write out the bytes of data
                //currDataRecord = fileBR.ReadBytes(i);
                for (int j = 0; j < i; j++)
                {
                    //fileSB.AppendFormat("{0:X2}", currDataRecord[j]);
                    fileSB.AppendFormat("{0:X2}", inputData[j + (memAddr - startAddr)]);
                    //checksum8 += currDataRecord[j];
                    checksum8 += inputData[j + (memAddr - startAddr)];
                }
                //Write out checksum and linefeed character
                fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

                memAddr += (UInt32)i; i = 0;

            }

            // Write out the final record (S7 record)
            checksum8 = 0;
            // Write S7 record label
            fileSB.Append("S7");
            // Write length field (4 address bytes + 1 checksum byte)
            fileSB.AppendFormat("{0:X2}", 5);
            checksum8 += 5;

            // Write execution start address field and update it
            fileSB.AppendFormat("{0:X8}", startAddr);
            currDataRecord = System.BitConverter.GetBytes(startAddr);
            for (int j = 0; j < 4; j++)
            {
                checksum8 += currDataRecord[j];
            }
            //Write out checksum and linefeed character
            fileSB.AppendFormat("{0:X2}\x0A", ((checksum8 & 0xFF) ^ 0xFF));

            return (new ASCIIEncoding()).GetBytes(fileSB.ToString());
        }

    }
}
