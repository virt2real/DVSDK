// This module parses a COFF file created by Texas Instruments TMS DSP
// code generation tools and offers a set of easy to use methods for obtaining
// information from the COFF file. This information includes header info.,
// symbol table, section data, etc.

// Based on COFFFile.pm perl module

using System;
using System.Text;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Threading;
using System.Globalization;
using System.Collections;
using UtilLib;

namespace UtilLib.IO
{
    enum COFFType : uint
    {
        COFF0 = 0x00C0,
        COFF1 = 0x00C1,
        COFF2 = 0x00C2
    }
    
    [Flags]
    enum SectionType : uint
    {
        REG     = 0x00000000,
        DUMMY   = 0x00000001,
        NOLOAD  = 0x00000002,
        GROUP   = 0x00000004,
        PAD     = 0x00000008,
        COPY    = 0x00000010,
        TEXT    = 0x00000020,
        DATA    = 0x00000040,
        BSS     = 0x00000080,
        BLOCK   = 0x00001000,
        PASS    = 0x00002000,
        CLINK   = 0x00004000,
        VECTOR  = 0x00008000,
        PADDED  = 0x00010000
    }

    /// <summary>
    /// Public class to read and parse a C6000 binary COFF file
    /// </summary>
    public class COFFFile
    {
        #region Private internal members
        private Stream binFile;
        private Endian endian;
        private UInt32 currSecNum;
        private UInt32 currSymNum;
        private UInt32 numBytesInHdr;
        private UInt32 numBytesInOptHdr;
        //private Boolean symParsed;
        private COFFType COFFVersion;
        private Hashtable headerRef;
        private Hashtable[] sectionRef;       
        private Hashtable[] symRef;
        #endregion

        #region Public properties and indexers
        public String Endianness
        {
            get { return endian.ToString(); }
        }
        
        public Hashtable Header
        {
            get { return headerRef; }
        }

        /// <summary>
        /// Indexer to return section with specified index
        /// </summary>
        /// <param name="index">Index of section in the COFF file</param>
        /// <returns>Array of section's data</returns>
        public UInt32[] this[UInt32 index]
        {
            get
            {
                return secRead(index);
            }
        }

        /// <summary>
        /// Indexer to return section with specified name
        /// </summary>
        /// <param name="name">Section name we wish to get</param>
        /// <returns>Array of section's data </returns>
        public UInt32[] this[String name]
        {
            get
            {
                return secRead(name);
            }
        }

        public Hashtable[] Sections
        {
            get
            {
                return sectionRef;
            }
        }

        public Hashtable[] Symbols
        {
            get
            {
                return symRef;
            }
        }

        
        #endregion

        #region Class constructors
        /// <summary>
        /// COFFFile constructor
        /// </summary>
        /// <param name="filename">Input .out filename as a string.</param>
        public COFFFile(String filename)
        {
            // Init header hashtable
            headerRef = new Hashtable();
            
            //Get COFF file details
            FileInfo fi = new FileInfo(filename);
            try
            {
                if (fi.Exists)
                    binFile = new FileStream(filename, FileMode.Open, FileAccess.Read);
            }
            catch (Exception e)
            {
                Console.Write(e.Message);
            }
                        
            //Init parsing info
            currSecNum = 0;
            currSymNum = 0;

            headerRef["fullName"] = filename;

            //Parse the COFF file
            try
            {
                ParseCOFFFile();
            }
            catch (Exception e)
            {
                Console.Write(e.Message);
                throw e;
            }

        }

        //public COFFFile(Stream dataStream, String streamName)
        //{
        //    // Init header hashtable
        //    headerRef = new Hashtable();
            
        //    if (dataStream is FileStream)
        //        binFile = dataStream;
        //    else if ((dataStream.CanRead) &&
        //             (dataStream.CanSeek))
        //    {
        //        binFile = dataStream;
        //    }
        //    else
        //    {
        //        throw new Exception("COFF Stream not appropriate for parsing.");
        //    }
            
            
        //    //Init parsing info
        //    currSecNum = 0;
        //    currSymNum = 0;

        //    headerRef["fullName"] = streamName;

        //    //Parse the COFF file
        //    try
        //    {
        //        ParseCOFFFile();
        //    }
        //    catch (Exception e)
        //    {
        //        Console.Write(e.Message);
        //        throw e;
        //    }
        //}

        #endregion

        #region Public Class Methods
        public void dumpSymbolTable()
        {
            //Hashtable sym = 
            symRewind();
            //while (sym != null)
            //{
            //    Console.WriteLine("0x{0:X8}, {1}", ((UInt32)sym["value"]), (String)sym["name"]);
            //    symEnum();
            //}
            Console.WriteLine("\tValue     \tName");
            Console.WriteLine("\t==========\t========");
            foreach (Hashtable sym in symRef)
            {
                if (!((String)sym["name"]).Equals(""))
                {
                    Console.WriteLine("\t0x{0:X8}\t {1}", ((UInt32)sym["value"]), (String)sym["name"]);
                }
            }
        }

        public void dumpFileHeader()
        {
            foreach (DictionaryEntry de in headerRef)
            {
                Console.WriteLine("header[{0}] = {1}", de.Key, de.Value);
            }
        }

        public new String ToString()
        {
            StringBuilder strBuilder = new StringBuilder(512);
            
            foreach (DictionaryEntry de in headerRef)
            {
                strBuilder.Append("header{"+de.Key.ToString()+"} = "+de.Value.ToString() + "\n");
            }

            for (int i = 0; i < sectionRef.Length; i++)
            {
                foreach (DictionaryEntry de in sectionRef[i])
                {
                    strBuilder.Append("sectionHdr["+i+"]{" + de.Key.ToString() + "} = " + de.Value.ToString() + "\n");
                }
            }

            for (int i = 0; i < symRef.Length; i++)
            {
                foreach (DictionaryEntry de in sectionRef[i])
                {
                    strBuilder.Append("symbolHdr[" + i + "]{" + de.Key.ToString() + "} = " + de.Value.ToString() + "\n");
                }
            }

            return strBuilder.ToString();
        }

        #region Section seek and access commands
        
        public Hashtable secRewind()
        {
            //Debug.DebugMSG("secRewind()");
            currSecNum = 0;
            return sectionRef[currSecNum];
        }

        public Hashtable secSeek(UInt32 index)
        {
            //Debug.DebugMSG("secSeek("+index.ToString()+")");
            if ((index >= 0) && (index < ((UInt32)headerRef["numSectionHdrs"])))
            {
                currSecNum = index;
                return sectionRef[currSecNum];
            }
            return null;
        }

        public Hashtable secFind(String secName)
        {
            //Debug.DebugMSG("secFind("+secName+")");
            UInt32 numSections = ((UInt32)headerRef["numSectionHdrs"]);
            for (UInt32 i = 0; i < numSections; i++)
            {
                
                if ( ((String)sectionRef[i]["name"]).Equals(secName))
                {
                    currSecNum = i;
                    return sectionRef[currSecNum];
                }
            }
            return null;
        }

        public Hashtable secEnum()
        {
            UInt32 numSections = ((UInt32)headerRef["numSectionHdrs"]);
            currSecNum++;
            if ( (currSecNum >= 0) && ( currSecNum < numSections ) )
            {
                return sectionRef[currSecNum];
            }
            else
                currSecNum--;
            return null;
        }

        public UInt32[] secRead()
        {
            Hashtable section = sectionRef[currSecNum];
            UInt32 flags = (UInt32)headerRef["flags"];
            UInt32 ws = (UInt32) section["wordSize"];
            UInt32 dp = (UInt32) section["dataPtr"];
            UInt32[] dataArr = new UInt32[ws];
            EndianBinaryReader COFFbr;
            
            binFile.Seek(dp,SeekOrigin.Begin);
            
            if ( (flags & 0x0200) != 0)
            {
                // Big Endian DSP
                COFFbr = new EndianBinaryReader(binFile,Endian.BigEndian);
            }
            else
            {
                // Little Endian DSP
                COFFbr = new EndianBinaryReader(binFile,Endian.LittleEndian);
            }
            //Debug.DebugMSG("secRead(): " + COFFbr.endianness.ToString());
                            
            for ( int i = 0; i<ws; i++)
            {
                dataArr[i] = COFFbr.ReadUInt32();
            }

            return dataArr;
        }

        public UInt32[] secRead(UInt32 secNum)
        {
            secSeek(secNum);
            return secRead();
        }

        public UInt32[] secRead(String secName)
        {
            secFind(secName);
            return secRead();
        }
        #endregion

        #region Symbol seek and access commands
        public Hashtable symRewind()
        {
            //Debug.DebugMSG("symRewind()");
            currSymNum = 0;
            return symRef[currSymNum];
        }

        public Hashtable symSeek( UInt32 index)
        {
            
            //Debug.DebugMSG("symSeek("+index.ToString()+")");
            UInt32 numSymbols = (UInt32)headerRef["numEntriesInSymTable"];
            if ((index>=0) && (index < numSymbols))
            {
                currSymNum = index;
                return symRef[currSymNum];
            }
            return null;
        }

        public Hashtable symFind( String symName)
        {
            //Debug.DebugMSG("symFind("+symName+")");
            UInt32 numSymbols = (UInt32)headerRef["numEntriesInSymTable"];
            for(UInt16 i = 0; i < numSymbols; i++)
            {
                if ( ((String)symRef[i]["name"]).Equals(symName))
                {
                    currSymNum = i;
                    return symRef[currSymNum];
                }
            }
            return null;
        }

        public Hashtable symEnum()
        {
            //Debug.DebugMSG("symEnum()");
            UInt32 numSymbols = (UInt32) headerRef["numEntriesInSymTable"];
            currSymNum++;
            
            if ( (currSymNum >=0) && (currSymNum <= numSymbols) )
            {
                return symRef[currSymNum];
            }
            else
                currSymNum--;
            return null;
        }
        #endregion

        /// <summary>
        /// Fucntion to close the COFF file associated with this object
        /// </summary>
        public void Close()
        {
            binFile.Close();
        }

        #endregion

        #region Private parsing functions
        /// <summary>
        /// Parse the COFF file and put info into public Hashtables
        /// </summary>
        private void ParseCOFFFile()
        {
            UInt32 magicNum;
            UInt32 thisCoff;
            // Output console message
            Console.WriteLine("Parsing the input COFF file, {0}.", (String) headerRef["fullName"]);

            // Check for COFF magic number and endianness
            binFile.Seek(20, SeekOrigin.Begin);
            magicNum = ((UInt32)binFile.ReadByte() << 8) | ((UInt32)binFile.ReadByte());
            Debug.DebugMSG("MagicNum: " + magicNum.ToString("X4"));
            if ( (magicNum == 0x9900) || (magicNum == 0x9700) )
                endian = Endian.LittleEndian;
            else if ( (magicNum == 0x0099) || (magicNum == 0x0097) )
                endian = Endian.BigEndian;
            else
                throw new Exception("Invalid COFF magic number " + magicNum.ToString("X4"));

            // Set endianness
            headerRef["endian"] = endian;
            Debug.DebugMSG("Endianness: " + endian.ToString());
            
            binFile.Seek(0, SeekOrigin.Begin);
            EndianBinaryReader COFFbr = new EndianBinaryReader(binFile,endian);
            
            thisCoff = (UInt32) COFFbr.ReadUInt16();
            if (thisCoff == 0x0099)
            {
                COFFVersion = COFFType.COFF0;
            }
            else if (thisCoff == (UInt16)COFFType.COFF1)
            {
                COFFVersion = COFFType.COFF1;
            }
            else if (thisCoff == (UInt16)COFFType.COFF2)
            {
                COFFVersion = COFFType.COFF2;
            }

            // Read the main COFF header
            headerRef["versionID"] = thisCoff;
            Debug.DebugMSG("versionID: " + thisCoff.ToString("X4"));
            
            headerRef["numSectionHdrs"] = (UInt32) COFFbr.ReadUInt16();
            Debug.DebugMSG("numSectionHdrs: " + ((UInt32)headerRef["numSectionHdrs"]).ToString("X4"));
            
            headerRef["dateStamp"] = COFFbr.ReadUInt32();
            Debug.DebugMSG("datestamp: " + ((UInt32)headerRef["dateStamp"]).ToString("X8"));
            
            headerRef["symbolTableAddr"] = COFFbr.ReadUInt32();
            Debug.DebugMSG("symbolTableAddr: " + ((UInt32)headerRef["symbolTableAddr"]).ToString("X8"));
            
            headerRef["numEntriesInSymTable"] = COFFbr.ReadUInt32();
            Debug.DebugMSG("numEntriesInSymTable: " + ((UInt32)headerRef["numEntriesInSymTable"]).ToString("X8"));

            numBytesInOptHdr = (UInt32) COFFbr.ReadUInt16();
            headerRef["numBytesInOptHdr"] = numBytesInOptHdr;
            Debug.DebugMSG("numBytesInOptHdr: " + ((UInt32)headerRef["numBytesInOptHdr"]).ToString("X4"));

            headerRef["flags"] = (UInt32) COFFbr.ReadUInt16();
            Debug.DebugMSG("flags: " + ((UInt32)headerRef["flags"]).ToString("X4"));

            Debug.DebugMSG("COFFType: " + ((UInt32)COFFType.COFF0).ToString());

            if (COFFVersion != COFFType.COFF0)
            {
                headerRef["magicNum"] = (UInt32) COFFbr.ReadUInt16();
                Debug.DebugMSG("magicNum: " + ((UInt32)headerRef["magicNum"]).ToString("X4"));
                numBytesInHdr = 22;             
            }
            else
            {
                numBytesInHdr = 20;
            }

            headerRef["numBootSections"] = (UInt32)0;
            headerRef["numTargetSections"] = (UInt32)0;

            // Read the optional COFF header
            if (numBytesInOptHdr != 0)
            {
                COFFbr.BaseStream.Seek(numBytesInHdr,SeekOrigin.Begin);
                headerRef["optMagicNumber"] = (UInt32) COFFbr.ReadUInt16();
                Debug.DebugMSG("optMagicNumber: " + ((UInt32)headerRef["optMagicNumber"]).ToString("X4"));

                headerRef["optVersionStamp"] = (UInt32)COFFbr.ReadUInt16();
                Debug.DebugMSG("optVersionStamp: " + ((UInt32)headerRef["optVersionStamp"]).ToString("X4"));

                headerRef["optExeSize"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("optExeSize: " + ((UInt32)headerRef["optExeSize"]).ToString("X8"));

                headerRef["optInitSize"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("optInitSize: " + ((UInt32)headerRef["optInitSize"]).ToString("X8"));

                headerRef["optUninitSize"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("optUninitSize: " + ((UInt32)headerRef["optUninitSize"]).ToString("X8"));

                headerRef["optEntryPoint"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("optEntryPoint: " + ((UInt32)headerRef["optEntryPoint"]).ToString("X8"));
                
                headerRef["optExeAddr"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("optExeAddr: " + ((UInt32)headerRef["optExeAddr"]).ToString("X8"));

                headerRef["optInitAddr"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("optInitAddr: " + ((UInt32)headerRef["optInitAddr"]).ToString("X8"));
            }
           
            // Read the section headers
            ParseSectionHdrs();

            // Parse the symbol table
            ParseSymbolTable();
            
        } // end ParseCOFFFile()

        /// <summary>
        /// Parse the section headers.
        /// </summary>
        private void ParseSectionHdrs()
        {
            UInt32 byteSize, wordSize, numBytesInSectionHdr;
            UInt32 numSections;
            EndianBinaryReader COFFbr = new EndianBinaryReader(binFile, endian);

            if (COFFVersion == COFFType.COFF2)
                numBytesInSectionHdr = 48;
            else
                numBytesInSectionHdr = 40;
                        
            numSections = (UInt32)headerRef["numSectionHdrs"];
            sectionRef = new Hashtable[numSections];
            for (UInt16 secNum = 0; secNum < numSections; secNum++)
            {
                sectionRef[secNum] = new Hashtable();

                COFFbr.BaseStream.Seek(numBytesInSectionHdr * secNum + numBytesInHdr + numBytesInOptHdr, SeekOrigin.Begin);
                sectionRef[secNum]["name"] = COFF_getName();
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"name\"]: " + ((String)sectionRef[secNum]["name"]).ToString());

                COFFbr.BaseStream.Seek(numBytesInSectionHdr * secNum + numBytesInHdr + numBytesInOptHdr + 8, SeekOrigin.Begin);
                sectionRef[secNum]["phyAddr"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"phyAddr\"]: " + ((UInt32)sectionRef[secNum]["phyAddr"]).ToString("X8"));

                sectionRef[secNum].Add("virAddr", COFFbr.ReadUInt32());
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"virAddr\"]: " + ((UInt32)sectionRef[secNum]["virAddr"]).ToString("X8"));

                byteSize = COFFbr.ReadUInt32();
                wordSize = (byteSize + 3) >> 2;
                byteSize = wordSize << 2;

                sectionRef[secNum]["byteSize"] = byteSize;
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"byteSize\"]: " + ((UInt32)sectionRef[secNum]["byteSize"]).ToString("X8"));

                sectionRef[secNum]["wordSize"] = wordSize;
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"wordSize\"]: " + ((UInt32)sectionRef[secNum]["wordSize"]).ToString("X8"));

                sectionRef[secNum]["dataPtr"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"dataPtr\"]: " + ((UInt32)sectionRef[secNum]["dataPtr"]).ToString("X8"));

                sectionRef[secNum]["reloPtr"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"reloPtr\"]: " + ((UInt32)sectionRef[secNum]["reloPtr"]).ToString("X8"));

                sectionRef[secNum]["linePtr"] = COFFbr.ReadUInt32();
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"linePtr\"]: " + ((UInt32)sectionRef[secNum]["linePtr"]).ToString("X8"));

                if (COFFVersion == COFFType.COFF2)
                {
                    sectionRef[secNum].Add("numRelos", COFFbr.ReadUInt32());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"numRelos\"]: " + ((UInt32)sectionRef[secNum]["numRelos"]).ToString("X8"));

                    sectionRef[secNum].Add("numLines", COFFbr.ReadUInt32());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"numLines\"]: " + ((UInt32)sectionRef[secNum]["numLines"]).ToString("X8"));

                    sectionRef[secNum].Add("flags", COFFbr.ReadUInt32());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"flags\"]: " + ((UInt32)sectionRef[secNum]["flags"]).ToString("X8"));

                    sectionRef[secNum].Add("reserved", (UInt32) COFFbr.ReadUInt16());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"reserved\"]: " + ((UInt32)sectionRef[secNum]["reserved"]).ToString("X4"));

                    sectionRef[secNum].Add("memPage", (UInt32) COFFbr.ReadUInt16());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"memPage\"]: " + ((UInt32)sectionRef[secNum]["memPage"]).ToString("X4"));
                }
                else
                {
                    sectionRef[secNum].Add("numRelos", (UInt32) COFFbr.ReadUInt16());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"numRelos\"]: " + ((UInt32)sectionRef[secNum]["numRelos"]).ToString("X4"));

                    sectionRef[secNum].Add("numLines", (UInt32) COFFbr.ReadUInt16());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"numLines\"]: " + ((UInt32)sectionRef[secNum]["numLines"]).ToString("X4"));

                    sectionRef[secNum].Add("flags", (UInt32) COFFbr.ReadUInt16());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"flags\"]: " + ((UInt32)sectionRef[secNum]["flags"]).ToString("X4"));

                    sectionRef[secNum].Add("reserved", (UInt32) COFFbr.ReadByte());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"reserved\"]: " + ((UInt32)sectionRef[secNum]["reserved"]).ToString("X2"));

                    sectionRef[secNum].Add("memPage", (UInt32) COFFbr.ReadByte());
                    Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"memPage\"]: " + ((UInt32)sectionRef[secNum]["memPage"]).ToString("X2"));
                }

                //Check to see if section is bootable
                UInt32 flags = (UInt32)sectionRef[secNum]["flags"];
                
                sectionRef[secNum]["bootable"] = false;
                if ((flags & ((UInt32)(SectionType.TEXT | SectionType.DATA))) != 0)
                {
                    if ((flags & ((UInt32)SectionType.COPY)) == 0)
                    {
                        if (((UInt32)sectionRef[secNum]["byteSize"]) != 0)
                        {
                            headerRef["numBootSections"] = ((UInt32)headerRef["numBootSections"]) + 1;
                            sectionRef[secNum]["bootable"] = true;
                        }
                    }
                }
                
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"bootFlag\"]: " + (sectionRef[secNum]["bootable"]).ToString());

                //Check to see if section should be copied to target
                sectionRef[secNum]["copyToTarget"] = false;
                if ( ( ((UInt32) sectionRef[secNum]["dataPtr"]) != 0 ) &&
                     ( ((UInt32) sectionRef[secNum]["byteSize"]) != 0 ) )
                {
                    if ((flags & ((UInt32)(SectionType.BSS |        // No BSS sections
                                  SectionType.COPY |                // No COPY sections
                                  SectionType.NOLOAD |              // No NOLOAD sections
                                  SectionType.DUMMY))               // No DUMMY sections
                         ) == 0)
                    {
                        headerRef["numTargetSections"] = ((UInt32)headerRef["numTargetSections"]) + 1;
                        sectionRef[secNum]["copyToTarget"] = true;
                    }
                }
                Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"copyToTarget\"]: " + (sectionRef[secNum]["copyToTarget"]).ToString());
            }
        } // end of ParseSectionHdrs()

        /// <summary>
        /// Parse the COFF file's symbol table.
        /// </summary>
        private void ParseSymbolTable()
        {
            EndianBinaryReader COFFbr = new EndianBinaryReader(binFile, endian);
            UInt32 numSymbols = (UInt32) headerRef["numEntriesInSymTable"];
            
            symRef = new Hashtable[numSymbols];

            // Read the symbol table
            for (UInt32 symNum = 0; symNum < numSymbols; symNum++)
            {
                symRef[symNum] = new Hashtable();
                
                COFFbr.BaseStream.Seek(((UInt32)headerRef["symbolTableAddr"]) + (18 * symNum),SeekOrigin.Begin);
                symRef[symNum]["name"] = COFF_getName();
                //Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"name\"]: " + ((String)symRef[symNum]["name"]).ToString());
                
                COFFbr.BaseStream.Seek(((UInt32)headerRef["symbolTableAddr"]) + (18 * symNum) + 8,SeekOrigin.Begin);
                
                symRef[symNum]["value"] = COFFbr.ReadUInt32();
                //Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"value\"]: " + ((UInt32)symRef[symNum]["value"]).ToString("X8"));

                symRef[symNum]["secNum"] = (UInt32) COFFbr.ReadUInt16();
                //Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"secNum\"]: " + ((UInt16)symRef[symNum]["secNum"]).ToString("X4"));

                symRef[symNum]["type"] = (UInt32) COFFbr.ReadUInt16();
                //Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"type\"]: " + ((UInt16)symRef[symNum]["type"]).ToString("X4"));

                symRef[symNum]["class"] = (UInt32) COFFbr.ReadByte();
                //Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"class\"]: " + ((Byte)symRef[symNum]["class"]).ToString("X2"));

                symRef[symNum]["auxNum"] = (UInt32) COFFbr.ReadByte();
                //Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"auxNum\"]: " + ((Byte)symRef[symNum]["auxNum"]).ToString("X2"));
            }
            Debug.DebugMSG("Parse Symbol Table Done");
        } // end of ParseSymbolTable()
        #endregion

        #region Private helper and debug functions
        /// <summary>
        /// Function to retrieve name string either from string table or from current stream pointer.
        /// </summary>
        /// <returns>String containing name.</returns>
        private String COFF_getName()
        {
            Int64 currPos = binFile.Position;
            UInt32 int0,int1;
            Byte currByte;
            ArrayList name = new ArrayList(128);
                        
            EndianBinaryReader COFFbr =  new EndianBinaryReader(binFile,(Endian) headerRef["endian"]);
            int0 = COFFbr.ReadUInt32();
            int1 = COFFbr.ReadUInt32();
            COFFbr.BaseStream.Seek(currPos,SeekOrigin.Begin);
          
            if (int0 == 0x00000000)
            {
                // The name is stored in the string table
                UInt32 stringTableAddr = ((UInt32)headerRef["symbolTableAddr"]) + (18 * ((UInt32)headerRef["numEntriesInSymTable"]));
                COFFbr.BaseStream.Seek((int1 + stringTableAddr),SeekOrigin.Begin);
                
                // Read characters and build string until terminating null
                currByte = COFFbr.ReadByte();
                
                while (currByte != 0)
                {
                    name.Add(currByte);
                    currByte = COFFbr.ReadByte();
                }
            }
            else
            {
                // Read characters straight from string table and build string until terminating null
                currByte = COFFbr.ReadByte();
                while ( (currByte != 0) && (name.Count < 8) )
                {
                    name.Add(currByte);
                    currByte = COFFbr.ReadByte();
                }
            }
            COFFbr.BaseStream.Seek(currPos, SeekOrigin.Begin);
            if (name.Count > 128)
                Debug.DebugMSG(ASCIIEncoding.ASCII.GetString((Byte[])name.ToArray(typeof(Byte)), 0, name.Count));
            return ASCIIEncoding.ASCII.GetString((Byte[]) name.ToArray(typeof(Byte)), 0, name.Count);
        }
    #endregion

    } //End COFFFile class

} //end of namespace
