// This module parses an ELF file. This information includes header info.,
// symbol table, section data, etc.

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

#region ELF Identifier Typedefs/Enums
  // ELF Class (invalid, 32-bit, or 64-bit), used in ELF_Identifier
  public enum ELF_FileClass : byte
  {
    ELFCLASS_NONE = 0x0,
    ELFCLASS_32   = 0x1,
    ELFCLASS_64   = 0x2
  }
  
  // ELF Data encoding (endianness), used in ELF_Identifier
  public enum ELF_DataEncoding : byte
  {
    ELFDATA_NONE   = 0x0,
    ELFDATA_2LSB   = 0x1, // Little Endian
    ELFDATA_2MSB   = 0x2  // Big Endian
  }
  
  // ELF File Version, used in ELF_Identifier
  public enum ELF_FileVersion : byte
  {
    ELFVER_NONE       = 0x0,
    ELFVER_CURRENT    = 0x1
  }
  
  // ELF OS/ABI Identification, used in ELF_Identifier
  public enum ELF_OsAbiID : byte
  {
    ELFOSABI_NONE     = 0,    // No extensions or unspecified
    ELFOSABI_HPUX     = 1,    // Hewlett-Packard HP-UX
    ELFOSABI_NETBSD   = 2,    // NetBSD
    ELFOSABI_SOLARIS  = 6,    // Sun Solaris
    ELFOSABI_AIX      = 7,    // AIX
    ELFOSABI_IRIX     = 8,    // IRIX
    ELFOSABI_FREEBSD  = 9,    // FreeBSD
    ELFOSABI_TRU64    = 10,   // Compaq TRU64 UNIX
    ELFOSABI_MODESTO  = 11,   // Novell Modesto
    ELFOSABI_OPENBSD  = 12,   // Open BSD
    ELFOSABI_OPENVMS  = 13,   // Open VMS
    ELFOSABI_NSK      = 14,   // Hewlett-Packard Non-Stop Kernel
    ELFOSABI_AROS     = 15 	  // Amiga Research OS  
  }
  
  // ELF Identifier Structure, used in ELF header
  public struct ELF_Identifier
  {
    public Byte[]            magic;
    public ELF_FileClass     fileClass;
    public ELF_DataEncoding  dataEncoding;
    public ELF_FileVersion   fileVersion;
    public ELF_OsAbiID       osAbiID;
    public Byte              abiVersion;
    public Byte[]            pad;
  }
#endregion


#region ELF Header Typedefs/Enums
  // ELF Type, used in ELF header
  public enum ELF_Type : ushort
  {
    ELFTYPE_NONE    = 0x00C0,
    ELFTYPE_REL     = 0x0001,
    ELFTYPE_EXEC    = 0x0002,
    ELFTYPE_DYN     = 0x0003,
    ELFTYPE_CORE    = 0x0004,
    ELFTYPE_LOOS    = 0xfe00,   // Operating system-specific
    ELFTYPE_HIOS    = 0xfeff,   // Operating system-specific
    ELFTYPE_LOPROC  = 0xff00, 	// Processor-specific
    ELFTYPE_HIPROC  = 0xffff    // Processor-specific      
  }

  // ELF Machine (Architecture) Identifier, used in ELF Header
  public enum ELF_Machine: ushort
  {
    EM_NONE             = 0,    // No machine
    EM_M32              = 1, 	  // AT&T WE 32100
    EM_SPARC            = 2, 	  // SPARC
    EM_386              = 3, 	  // Intel 80386
    EM_68K              = 4,    // Motorola 68000
    EM_88K              = 5,    // Motorola 88000
    EM_860              = 7,    // Intel 80860
    EM_MIPS             = 8,    // MIPS I Architecture
    EM_S370             = 9,    // IBM System/370 Processor
    EM_MIPS_RS3_LE      = 10,   // MIPS RS3000 Little-endian
    EM_PARISC           = 15,   // Hewlett-Packard PA-RISC
    EM_VPP500           = 17,   // Fujitsu VPP500
    EM_SPARC32PLUS      = 18,   // Enhanced instruction set SPARC
    EM_960              = 19,   // Intel 80960
    EM_PPC              = 20,   // PowerPC
    EM_PPC64            = 21,   // 64-bit PowerPC
    EM_S390             = 22,   // IBM System/390 Processor
    EM_V800             = 36,   // NEC V800
    EM_FR20             = 37,   // Fujitsu FR20
    EM_RH32             = 38,   // TRW RH-32
    EM_RCE              = 39,   // Motorola RCE
    EM_ARM              = 40,   // Advanced RISC Machines ARM
    EM_ALPHA            = 41,   // Digital Alpha
    EM_SH               = 42,   // Hitachi SH
    EM_SPARCV9          = 43, 	// SPARC Version 9
    EM_TRICORE          = 44,   // Siemens TriCore embedded processor
    EM_ARC              = 45,   // Argonaut RISC Core, Argonaut Technologies Inc.
    EM_H8_300           = 46,   // Hitachi H8/300
    EM_H8_300H          = 47,   // Hitachi H8/300H
    EM_H8S              = 48,   // Hitachi H8S
    EM_H8_500           = 49,   // Hitachi H8/500
    EM_IA_64            = 50,   // Intel IA-64 processor architecture
    EM_MIPS_X           = 51,   // Stanford MIPS-X
    EM_COLDFIRE         = 52,   // Motorola ColdFire
    EM_68HC12           = 53,   // Motorola M68HC12
    EM_MMA              = 54,   // Fujitsu MMA Multimedia Accelerator
    EM_PCP              = 55,   // Siemens PCP
    EM_NCPU             = 56, 	// Sony nCPU embedded RISC processor
    EM_NDR1             = 57,   // Denso NDR1 microprocessor
    EM_STARCORE         = 58,   // Motorola Star*Core processor
    EM_ME16             = 59,   // Toyota ME16 processor
    EM_ST100            = 60,   // STMicroelectronics ST100 processor
    EM_TINYJ            = 61,   // Advanced Logic Corp. TinyJ embedded processor family
    EM_X86_64           = 62,   // AMD x86-64 architecture
    EM_PDSP             = 63,   // Sony DSP Processor
    EM_PDP10            = 64,   // Digital Equipment Corp. PDP-10
    EM_PDP11            = 65,   // Digital Equipment Corp. PDP-11
    EM_FX66             = 66,   // Siemens FX66 microcontroller
    EM_ST9PLUS          = 67,   // STMicroelectronics ST9+ 8/16 bit microcontroller
    EM_ST7              = 68,   // STMicroelectronics ST7 8-bit microcontroller
    EM_68HC16           = 69,   // Motorola MC68HC16 Microcontroller
    EM_68HC11           = 70,   // Motorola MC68HC11 Microcontroller
    EM_68HC08           = 71,   // Motorola MC68HC08 Microcontroller
    EM_68HC05           = 72,   // Motorola MC68HC05 Microcontroller
    EM_SVX              = 73,   // Silicon Graphics SVx
    EM_ST19             = 74,   // STMicroelectronics ST19 8-bit microcontroller
    EM_VAX              = 75,   // Digital VAX
    EM_CRIS             = 76,   // Axis Communications 32-bit embedded processor
    EM_JAVELIN          = 77,   // Infineon Technologies 32-bit embedded processor
    EM_FIREPATH         = 78,   // Element 14 64-bit DSP Processor
    EM_ZSP              = 79,   // LSI Logic 16-bit DSP Processor
    EM_MMIX             = 80,   // Donald Knuth's educational 64-bit processor
    EM_HUANY            = 81,   // Harvard University machine-independent object files
    EM_PRISM            = 82,   // SiTera Prism
    EM_AVR              = 83,   // Atmel AVR 8-bit microcontroller
    EM_FR30             = 84,   // Fujitsu FR30
    EM_D10V             = 85,   // Mitsubishi D10V
    EM_D30V             = 86,   // Mitsubishi D30V
    EM_V850             = 87,   // NEC v850
    EM_M32R             = 88,   // Mitsubishi M32R
    EM_MN10300          = 89,   // Matsushita MN10300
    EM_MN10200          = 90,   // Matsushita MN10200
    EM_PJ               = 91,   // picoJava
    EM_OPENRISC         = 92,   // OpenRISC 32-bit embedded processor
    EM_ARC_A5           = 93,   // ARC Cores Tangent-A5
    EM_XTENSA           = 94,   // Tensilica Xtensa Architecture
    EM_VIDEOCORE        = 95,   // Alphamosaic VideoCore processor
    EM_TMM_GPP          = 96,   // Thompson Multimedia General Purpose Processor
    EM_NS32K            = 97,   // National Semiconductor 32000 series
    EM_TPC              = 98,   // Tenor Network TPC processor
    EM_SNP1K            = 99,   // Trebia SNP 1000 processor
    EM_ST200            = 100,  // STMicroelectronics (www.st.com) ST200 microcontroller
    EM_IP2K             = 101,  // Ubicom IP2xxx microcontroller family
    EM_MAX              = 102,  // MAX Processor
    EM_CR               = 103,  // National Semiconductor CompactRISC microprocessor
    EM_F2MC16           = 104,  // Fujitsu F2MC16
    EM_MSP430           = 105,  // Texas Instruments embedded microcontroller msp430
    EM_BLACKFIN         = 106,  // Analog Devices Blackfin (DSP) processor
    EM_SE_C33           = 107,  // S1C33 Family of Seiko Epson processors
    EM_SEP              = 108,  // Sharp embedded microprocessor
    EM_ARCA             = 109,  // Arca RISC Microprocessor
    EM_UNICORE          = 110,  // Microprocessor series from PKU-Unity Ltd. and MPRC of Peking University
    EM_TI_C6000         = 140  // Texas Instruments C6000 DSP
  }
  
  // ELF Version, used in ELF Header
  public enum ELF_Version : uint
  {
    EV_NONE       = 0x0,
    EV_CURRENT    = 0x1
  }
  
  public struct ELF_Header
  {
    public ELF_Identifier    e_ident;
    public ELF_Type          e_type;
    public ELF_Machine       e_machine;
    public ELF_Version       e_version;
    public UInt64            e_entry;
    public UInt64            e_phoff;
    public UInt64            e_shoff;
    public UInt32            e_flags;
    public UInt16            e_ehsize;
    public UInt16            e_phentsize;
    public UInt16            e_phnum;
    public UInt16            e_shentsize;
    public UInt16            e_shnum;
    public UInt16            e_shstrndx;
  }
#endregion
  
  
#region ELF Section Typedefs/Enums
  public enum ELF_SectionIndex : ushort
  {
    SHN_UNDEF       = 0,
    SHN_LORESERVE   = 0xff00,
    SHN_LOPROC      = 0xff00,
    SHN_HIPROC      = 0xff1f,
    SHN_LOOS        = 0xff20,
    SHN_HIOS        = 0xff3f,
    SHN_ABS         = 0xfff1,
    SHN_COMMON      = 0xfff2,
    SHN_XINDEX      = 0xffff,
    SHN_HIRESERVE   = 0xffff
  }
  
  public enum ELF_SectionType : uint
  {
    SHT_NULL              = 0,
    SHT_PROGBITS          = 1,
    SHT_SYMTAB            = 2,
    SHT_STRTAB            = 3,
    SHT_RELA              = 4,
    SHT_HASH              = 5,
    SHT_DYNAMIC           = 6,
    SHT_NOTE              = 7,
    SHT_NOBITS            = 8,
    SHT_REL               = 9,
    SHT_SHLIB             = 10,
    SHT_DYNSYM            = 11,
    SHT_INIT_ARRAY        = 14,
    SHT_FINI_ARRAY        = 15,
    SHT_PREINIT_ARRAY     = 16,
    SHT_GROUP             = 17,
    SHT_SYMTAB_SHNDX      = 18,
    SHT_LOOS              = 0x60000000,
    SHT_HIOS              = 0x6fffffff,
    SHT_LOPROC            = 0x70000000,
    SHT_TI_UNWIND         = 0x70000001,
    SHT_TI_PREEMPTMAP     = 0x70000002,
    SHT_TI_ATTRIBUTES     = 0x70000003,
    SHT_TI_ICODE          = 0x70000004,
    SHT_TI_XREF           = 0x70000005,
    SHT_TI_HANDLER        = 0x70000006,
    SHT_TI_INITINFO       = 0x70000007,
    SHT_HIPROC            = 0x7fffffff,
    SHT_LOUSER            = 0x80000000,
    SHT_HIUSER            = 0xffffffff
  }
  
  public enum ELF_SectionFlag : uint
  {
    SHF_WRITE             = 0x1,
    SHF_ALLOC             = 0x2,
    SHF_EXECINSTR         = 0x4,
    SHF_MERGE             = 0x10,
    SHF_STRINGS           = 0x20,
    SHF_INFO_LINK         = 0x40,
    SHF_LINK_ORDER        = 0x80,
    SHF_OS_NONCONFORMING  = 0x100,
    SHF_GROUP             = 0x200,
    SHF_TLS               = 0x400,
    SHF_MASKOS            = 0x0ff00000,
    SHF_MASKPROC          = 0xf0000000
  }
  
  public struct ELF_SectionHeader
  {
    public UInt32	          sh_name;
    public ELF_SectionType  sh_type;
    public UInt64	sh_flags;
    public UInt64	sh_addr;
    public UInt64 sh_offset;
    public UInt64	sh_size;
    public UInt32	sh_link;
    public UInt32	sh_info;
    public UInt64	sh_addralign;
    public UInt64	sh_entsize;
  }  
#endregion
  

#region ELF Segment Typedefs/Enums
  public enum ELF_SegmentType
  {
    PT_NULL             = 0,
    PT_LOAD             = 1,
    PT_DYNAMIC          = 2,
    PT_INTERP           = 3,
    PT_NOTE             = 4,
    PT_SHLIB            = 5,
    PT_PHDR             = 6,
    PT_TLS              = 7,
    PT_LOOS             = 0x60000000,
    PT_HIOS             = 0x6fffffff,
    PT_LOPROC           = 0x70000000,
    PT_HIPROC           = 0x7fffffff
  }
  
  public enum ELF_SegmentFlags : uint
  {
    PF_X                = 0x1,  // Execute
    PF_W                = 0x2, 	// Write
    PF_R                = 0x4,  // Read
    PF_MASKOS           = 0x0ff00000, // Unspecified
    PF_MASKPROC         = 0xf0000000  // Unspecified
  }
  
  public struct ELF_SegmentHeader
  {
    public ELF_SegmentType p_type;
    public UInt32 p_flags;
    public UInt64 p_offset;
    public UInt64 p_vaddr;
    public UInt64 p_paddr;
    public UInt64 p_filesz;
    public UInt64 p_memsz;
    public UInt64 p_align;
  }
#endregion


#region ELF Symbol Typedefs/Enums
  public enum ELF_SymbolType : byte
  {
    STT_NOTYPE    = 0,
    STT_OBJECT    = 1,
    STT_FUNC      = 2,
    STT_SECTION   = 3,
    STT_FILE      = 4,
    STT_COMMON    = 5,
    STT_TLS       = 6,
    STT_LOOS      = 10,
    STT_HIOS      = 12,
    STT_LOPROC    = 13,
    STT_HIPROC    = 15  
  }
  
  public enum ELF_SymbolBinding : byte
  {
    STB_LOCAL   = 0,
    STB_GLOBAL  = 1,
    STB_WEAK    = 2,
    STB_LOOS    = 10,
    STB_HIOS    = 12,
    STB_LOPROC  = 13,
    STB_HIPROC  = 15, 
  }
  
  public enum ELF_SymbolVisibility : byte
  {
    STV_DEFAULT   = 0,
    STV_INTERNAL  = 1,
    STV_HIDDEN    = 2,
    STV_PROTECTED = 3
  }

  public struct ELF_Symbol
  {
    public UInt32                st_name;
    public ELF_SymbolType        st_type;
    public ELF_SymbolBinding     st_binding;
    public ELF_SymbolVisibility  st_visibility;
    public UInt16                st_shndx;
    public UInt64                st_value;
    public UInt64                st_size;
  }  
#endregion

  /// <summary>
  /// Public class to read and parse a C6000 binary ELF file
  /// </summary>
  public class ELFFile
  {
    #region Private internal members
    // ELF Header
    private ELF_Header hdr;
    
    private Stream binFile;
    private Endian endian;
    
    private UInt32 currSecNum;
    private UInt32 currSymNum;
    
    //private Boolean symParsed;
    
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
    /// ELFFile constructor
    /// </summary>
    /// <param name="filename">Input .out filename as a string.</param>
    public ELFFile(String filename)
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
        ParseObjectFile();
      }
      catch (Exception e)
      {
        Console.Write(e.Message);
        throw e;
      }
    }
    #endregion

    
    #region Public Class Methods
    public void dumpSymbolTable()
    {
      symRewind();
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
        EndianBinaryReader ebr;
        
        binFile.Seek(dp,SeekOrigin.Begin);
        
        if ( (flags & 0x0200) != 0)
        {
            // Big Endian DSP
            ebr = new EndianBinaryReader(binFile,Endian.BigEndian);
        }
        else
        {
            // Little Endian DSP
            ebr = new EndianBinaryReader(binFile,Endian.LittleEndian);
        }
        //Debug.DebugMSG("secRead(): " + ebr.endianness.ToString());
                        
        for ( int i = 0; i<ws; i++)
        {
            dataArr[i] = ebr.ReadUInt32();
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
    /// Function to close the COFF file associated with this object
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
    private void ParseObjectFile()
    {
      ELF_SectionHeader secHdr;
    
      // Output console message
      Console.WriteLine("Parsing the input Object file, {0}.", (String) headerRef["fullName"]);
    
      // Parse the ELF header
      try
      {
        hdr = ELFFile.ParseELFHeader(binFile);
      }
      catch (Exception e)
      {
        Console.Write(e.Message);
        return;
      }
      
      // Determine the Endianness and use an EndianBinaryReader Object
      endian = (ELF_DataEncoding.ELFDATA_2LSB == hdr.e_ident.dataEncoding) ? Endian.LittleEndian : Endian.BigEndian;
      EndianBinaryReader ebr = new EndianBinaryReader(binFile,endian);
      
      // Set endianness
      headerRef["endian"] = endian;
      Debug.DebugMSG("Endianness: " + endian.ToString());
      
      // Read the section headers
      headerRef["numSectionHdrs"] = (UInt32) hdr.e_shnum;
      Debug.DebugMSG("numSectionHdrs: " + ((UInt32)headerRef["numSectionHdrs"]).ToString("X4"));      
      headerRef["numBootSections"] = (UInt32)0;
      headerRef["numTargetSections"] = (UInt32)0;      
      ParseSectionHdrs();

      // Find the symbol table section, symbol table entry size, and numbr of symbols
      secFind(".symtab");
      secHdr = ReadSectionHeader(currSecNum);
      if (secHdr.sh_type != ELF_SectionType.SHT_SYMTAB)
      {
        throw new Exception("Symbol table not found in file!");
      }
      headerRef["symbolTableAddr"] = (UInt64) secHdr.sh_offset;
      headerRef["symbolTableEntrySize"] = (UInt32) secHdr.sh_entsize;
      headerRef["numEntriesInSymTable"] =  (UInt32) (secHdr.sh_size / secHdr.sh_entsize);

      Debug.DebugMSG("symbolTableAddr: " + ((UInt64)headerRef["symbolTableAddr"]).ToString("X8"));
      Debug.DebugMSG("symbolTableEntrySize: " + ((UInt32)headerRef["symbolTableEntrySize"]).ToString("X8"));    
      Debug.DebugMSG("numEntriesInSymTable: " + ((UInt32)headerRef["numEntriesInSymTable"]).ToString());
      
      
      // Find the string table section
      secFind(".strtab");
      secHdr = ReadSectionHeader(currSecNum);
      if (secHdr.sh_type != ELF_SectionType.SHT_STRTAB)
      {
        throw new Exception("String table not found in file!");
      }
      // Verify that the section header string table section is flagged as a string section
      if ( ( ((UInt64) secHdr.sh_flags) & ((UInt64) ELF_SectionFlag.SHF_STRINGS) ) == 0 )
      {
        throw new Exception("Section Header String Section is not flagged with SHF_STRINGS.");
      }
      
      headerRef["stringTableAddr"] = (UInt64) secHdr.sh_offset;
      Debug.DebugMSG("stringTableAddr: " + ((UInt64)headerRef["stringTableAddr"]).ToString("X8"));


      // Now parse the symbol table
      ParseSymbolTable();
      
      // Read the remaining pertinent info from header
      headerRef["versionID"] = (UInt32) hdr.e_version;
      Debug.DebugMSG("versionID: " + ((UInt32)headerRef["versionID"]).ToString("X4"));
      
      headerRef["flags"] = hdr.e_flags;
      Debug.DebugMSG("flags: " + ((UInt32)headerRef["flags"]).ToString("X8"));

    } // end ParseObjectFile()

    /// <summary>
    /// Parse the section headers.
    /// </summary>
    private void ParseSectionHdrs()
    {
      UInt32 byteSize, wordSize, numBytesInSectionHdr;
      UInt32 numSections;
      UInt64 flags;
      ELF_SectionHeader secHdr;
      EndianBinaryReader ebr = new EndianBinaryReader(binFile, endian);
      
      numBytesInSectionHdr = hdr.e_shentsize;
                    
      numSections = (UInt32)headerRef["numSectionHdrs"];
      
      if (numSections == (UInt32) ELF_SectionIndex.SHN_UNDEF)
      {
        // FIXME: Get the actual number of sections from the
        // sh_size field of the 0th section header table entry
        secHdr = ReadSectionHeader(0);
        numSections = (UInt32) secHdr.sh_size;
        headerRef["numSectionHdrs"] = (UInt32) secHdr.sh_size;
      }
      Debug.DebugMSG("Section Header Count: " + (UInt32)headerRef["numSectionHdrs"]);
      
      
      // Get Section Header String Table Section Header Index and Section Header String Table Section Address
      if (hdr.e_shstrndx == (UInt16) ELF_SectionIndex.SHN_UNDEF)
      {
        headerRef["stringTableAddr"] = null;
        headerRef["stringHeaderTableIndex"] = null;
        secHdr = new ELF_SectionHeader();
      }
      else if (hdr.e_shstrndx == (UInt16) ELF_SectionIndex.SHN_XINDEX)
      {
        secHdr = ReadSectionHeader(0);
        headerRef["stringHeaderTableIndex"] = (UInt32) secHdr.sh_link;
        secHdr = ReadSectionHeader((UInt32) headerRef["stringHeaderTableIndex"]);
        headerRef["stringTableAddr"] = (UInt64) secHdr.sh_addr;
      }
      else
      {
        headerRef["stringHeaderTableIndex"] = (UInt32) hdr.e_shstrndx;
        secHdr = ReadSectionHeader((UInt32) headerRef["stringHeaderTableIndex"]);
        headerRef["stringTableAddr"] = (UInt64) (secHdr.sh_offset);
      }
      Debug.DebugMSG("Section Header Table Index for Section Header String Table: " + (UInt32)headerRef["stringHeaderTableIndex"]);
      Debug.DebugMSG("String Section Start Addr: 0x" + ((UInt64)headerRef["stringTableAddr"]).ToString("X8"));
      
      // Verify that the section header string table section is flagged as a string section
      flags = (UInt64) secHdr.sh_flags;
      if ( ( flags & ((UInt64) ELF_SectionFlag.SHF_STRINGS) ) == 0 )
      {
        throw new Exception("Section Header String Section is not flagged with SHF_STRINGS.");
      }
      if (secHdr.sh_type != ELF_SectionType.SHT_STRTAB)
      {
        throw new Exception("Section Header String Section is not of type SHT_STRTAB.");
      }
      
      // Cycle through all sections, collecting info about each (name, type, etc.)
      sectionRef = new Hashtable[numSections];
      for (UInt32 secNum = 0; secNum < numSections; secNum++)
      {
        secHdr = ReadSectionHeader((UInt32) secNum);
        sectionRef[secNum] = new Hashtable();
        
        Debug.DebugMSG("Section Header Number = " + secNum);

        ebr.BaseStream.Seek((Int64)(secHdr.sh_name + (UInt64)headerRef["stringTableAddr"]), SeekOrigin.Begin);
        sectionRef[secNum]["name"]    = ELF_getStringFromStringTable();
        sectionRef[secNum]["type"]    = (ELF_SectionType) secHdr.sh_type;
        sectionRef[secNum]["phyAddr"] = (UInt64) secHdr.sh_addr;
        sectionRef[secNum]["virAddr"]   = (UInt64) secHdr.sh_addr;

        byteSize = (UInt32) secHdr.sh_size;
        wordSize = (byteSize + 3) >> 2;
        byteSize = wordSize << 2;
        sectionRef[secNum]["byteSize"]  = byteSize;
        sectionRef[secNum]["wordSize"] = wordSize;
        
        sectionRef[secNum]["flags"] = (UInt64) secHdr.sh_flags;
        
        flags = (UInt64) sectionRef[secNum]["flags"];
        
        // FIXME: Check to see if section should be copied to target
        sectionRef[secNum]["copyToTarget"] = false;
        if ( ( ((UInt64) sectionRef[secNum]["phyAddr"])   != 0 ) &&
             ( ((UInt32) sectionRef[secNum]["byteSize"])  != 0 ) &&
             ( ELF_SectionType.SHT_NULL                   != (ELF_SectionType)sectionRef[secNum]["type"] ) &&
             ( ELF_SectionType.SHT_NOBITS                 != (ELF_SectionType)sectionRef[secNum]["type"] ) &&
             ( ELF_SectionType.SHT_SYMTAB                 != (ELF_SectionType)sectionRef[secNum]["type"] ) &&
             ( ELF_SectionType.SHT_DYNSYM                 != (ELF_SectionType)sectionRef[secNum]["type"] ) &&
             ( ELF_SectionType.SHT_STRTAB                 != (ELF_SectionType)sectionRef[secNum]["type"] )             )
        {
          if ( ( ELF_SectionType.SHT_PROGBITS == (ELF_SectionType)sectionRef[secNum]["type"] ) &&
               ( (flags | ((UInt64) ELF_SectionFlag.SHF_ALLOC)) != 0x0 ) )
          {
            headerRef["numTargetSections"] = ((UInt32)headerRef["numTargetSections"]) + 1;
            sectionRef[secNum]["copyToTarget"] = true;
          }
        }
        
        // If we think this section should be copied to target, make sure it is 
        // in a loadable ELF program segment.  If it is, then update physical 
        // and virtual addresses. If not, then mark it as such.
        if ((Boolean) sectionRef[secNum]["copyToTarget"])
        {
          for (UInt32 segmentNum = 0; segmentNum < (UInt32)hdr.e_phnum; segmentNum++)
          {
            ELF_SegmentHeader segmentHdr = ReadSegmentHeader((UInt32) segmentNum);
            
            // If the segment is of load type, check to see if the current section resides in it
            if (segmentHdr.p_type == ELF_SegmentType.PT_LOAD)
            {
              // Check if data is in the file, and if so then check if the section
              // is within this current header
              if ( ( segmentHdr.p_filesz                         != 0                      ) &&
                   ( segmentHdr.p_vaddr                          <= (UInt64) secHdr.sh_addr) &&
                   ( (segmentHdr.p_vaddr + segmentHdr.p_filesz)  >  (UInt64) secHdr.sh_addr) )
              {
                sectionRef[secNum]["phyAddr"] = (UInt64) segmentHdr.p_paddr;
                sectionRef[secNum]["virAddr"] = (UInt64) segmentHdr.p_vaddr;
              }
            }
          }
        }
        
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"name\"]: " + ((String)sectionRef[secNum]["name"]).ToString());
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"type\"]: " + ((ELF_SectionType)sectionRef[secNum]["type"]).ToString());
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"phyAddr\"]: " + ((UInt64)sectionRef[secNum]["phyAddr"]).ToString("X8"));
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"virAddr\"]: " + ((UInt64)sectionRef[secNum]["virAddr"]).ToString("X8"));        
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"byteSize\"]: " + ((UInt32)sectionRef[secNum]["byteSize"]).ToString("X8"));
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"wordSize\"]: " + ((UInt32)sectionRef[secNum]["wordSize"]).ToString("X8"));
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"flags\"]: " + ((UInt64)sectionRef[secNum]["flags"]).ToString("X8"));
        Debug.DebugMSG("sectionRef[" + secNum.ToString() + "][\"copyToTarget\"]: " + (sectionRef[secNum]["copyToTarget"]).ToString());
        Debug.DebugMSG("");
      }
      
    } // end of ParseSectionHdrs()
    
    /// <summary>
    /// Read the section header from the section header table
    /// </summary>
    private ELF_SectionHeader ReadSectionHeader(UInt32 index)
    {
      EndianBinaryReader ebr = new EndianBinaryReader(binFile, endian);
      ELF_SectionHeader sectionHeader = new ELF_SectionHeader();
     
      // Seek to the start of the section header in section header table
      binFile.Seek((Int64)(hdr.e_shentsize * index + hdr.e_shoff), SeekOrigin.Begin);
      
      //Debug.DebugMSG( "Section["+index+"] = \n{");
      
      sectionHeader.sh_name = ebr.ReadUInt32();
      sectionHeader.sh_type = (ELF_SectionType) ebr.ReadUInt32();
      
      //Debug.DebugMSG(   "  Section Name Index         : " + sectionHeader.sh_name);
      //Debug.DebugMSG(   "  Section Type               : " + sectionHeader.sh_type);
      
      if (ELF_FileClass.ELFCLASS_32 == hdr.e_ident.fileClass)
      {
        sectionHeader.sh_flags      = (UInt64) ebr.ReadUInt32();
        sectionHeader.sh_addr       = (UInt64) ebr.ReadUInt32();
        sectionHeader.sh_offset     = (UInt64) ebr.ReadUInt32();
        sectionHeader.sh_size       = (UInt64) ebr.ReadUInt32();
        
        /*Debug.DebugMSG( "  Section Flags              : 0x" + sectionHeader.sh_flags.ToString("X8"));
        Debug.DebugMSG( "  Section Address            : 0x" + sectionHeader.sh_addr.ToString("X8"));        
        Debug.DebugMSG( "  Section Offset             : 0x" + sectionHeader.sh_offset.ToString("X8"));
        Debug.DebugMSG( "  Section Size               : 0x" + sectionHeader.sh_size.ToString("X8"));*/
      }
      else
      {
        sectionHeader.sh_flags      = ebr.ReadUInt64();
        sectionHeader.sh_addr       = ebr.ReadUInt64();
        sectionHeader.sh_offset     = ebr.ReadUInt64();
        sectionHeader.sh_size       = ebr.ReadUInt64();
        
        /*Debug.DebugMSG( "  Section Flags              : 0x" + sectionHeader.sh_flags.ToString("X16"));
        Debug.DebugMSG( "  Section Address            : 0x" + sectionHeader.sh_addr.ToString("X16"));        
        Debug.DebugMSG( "  Section Offset             : 0x" + sectionHeader.sh_offset.ToString("X16"));
        Debug.DebugMSG( "  Section Size               : 0x" + sectionHeader.sh_size.ToString("X16"));*/
      }
      sectionHeader.sh_link      = ebr.ReadUInt32();
      sectionHeader.sh_info      = ebr.ReadUInt32();
      //Debug.DebugMSG(   "  Section Link Index         : 0x" + sectionHeader.sh_flags.ToString("X8"));
      //Debug.DebugMSG(   "  Section Info Field         : 0x" + sectionHeader.sh_addr.ToString("X8")); 
      
      if (ELF_FileClass.ELFCLASS_32 == hdr.e_ident.fileClass)
      {
        sectionHeader.sh_addralign      = (UInt64) ebr.ReadUInt32();
        sectionHeader.sh_entsize        = (UInt64) ebr.ReadUInt32();
        
        //Debug.DebugMSG( "  Section Addr Aligmnent     : 0x" + sectionHeader.sh_addralign.ToString("X8"));
        //Debug.DebugMSG( "  Section Entry Size         : 0x" + sectionHeader.sh_entsize.ToString("X8"));
      }
      else
      {
        sectionHeader.sh_addralign      = ebr.ReadUInt64();
        sectionHeader.sh_entsize        = ebr.ReadUInt64();
        
        //Debug.DebugMSG( "  Section Addr Aligmnent     : 0x" + sectionHeader.sh_addralign.ToString("X16"));
        //Debug.DebugMSG( "  Section Entry Size         : 0x" + sectionHeader.sh_entsize.ToString("X16"));
      }
      //Debug.DebugMSG("}");
      
      return sectionHeader;
    }
    
    // 
    /// <summary>
    /// Read the segment header from the program header table
    /// </summary>
    private ELF_SegmentHeader ReadSegmentHeader(UInt32 index)
    {
      EndianBinaryReader ebr = new EndianBinaryReader(binFile, endian);
      ELF_SegmentHeader segmentHeader = new ELF_SegmentHeader();
     
      // Seek to the start of the section header in section header table
      binFile.Seek((Int64)(hdr.e_phentsize * index + hdr.e_phoff), SeekOrigin.Begin);
      
      //Debug.DebugMSG( "Segment["+index+"] = \n{");

      // Read segment type
      segmentHeader.p_type = (ELF_SegmentType) ebr.ReadUInt32();
      
      //Debug.DebugMSG(   "  Segment Type               : " + segmentHeader.p_type);
      
      if (ELF_FileClass.ELFCLASS_32 == hdr.e_ident.fileClass)
      {
        segmentHeader.p_offset      = (UInt64) ebr.ReadUInt32();        
        segmentHeader.p_vaddr       = (UInt64) ebr.ReadUInt32();
        segmentHeader.p_paddr       = (UInt64) ebr.ReadUInt32();        
        segmentHeader.p_filesz      = (UInt64) ebr.ReadUInt32();
        segmentHeader.p_memsz       = (UInt64) ebr.ReadUInt32();        
        segmentHeader.p_flags       = (UInt32) ebr.ReadUInt32();
        segmentHeader.p_align       = (UInt64) ebr.ReadUInt32();        
        
        /*
        Debug.DebugMSG( "  Segment Flags              : 0x" + segmentHeader.p_flags.ToString("X8"));        
        Debug.DebugMSG( "  Segment Offset             : 0x" + segmentHeader.p_offset.ToString("X8"));
        Debug.DebugMSG( "  Segment Virtual Address    : 0x" + segmentHeader.p_vaddr.ToString("X8"));
        Debug.DebugMSG( "  Segment Physical Address   : 0x" + segmentHeader.p_paddr.ToString("X8"));
        Debug.DebugMSG( "  Segment File Size          : 0x" + segmentHeader.p_filesz.ToString("X8"));
        Debug.DebugMSG( "  Segment Memory Size        : 0x" + segmentHeader.p_memsz.ToString("X8"));
        Debug.DebugMSG( "  Segment Align              : 0x" + segmentHeader.p_align.ToString("X8"));
        */
      }
      else
      {
        segmentHeader.p_flags       = (UInt32) ebr.ReadUInt32();
        segmentHeader.p_offset      = (UInt64) ebr.ReadUInt64();
        segmentHeader.p_vaddr       = (UInt64) ebr.ReadUInt64();
        segmentHeader.p_paddr       = (UInt64) ebr.ReadUInt64();
        segmentHeader.p_filesz      = (UInt64) ebr.ReadUInt64();
        segmentHeader.p_memsz       = (UInt64) ebr.ReadUInt64();
        segmentHeader.p_align       = (UInt64) ebr.ReadUInt64();
        
        /*
        Debug.DebugMSG( "  Segment Flags              : 0x" + segmentHeader.p_flags.ToString("X8"));
        Debug.DebugMSG( "  Segment Offset             : 0x" + segmentHeader.p_offset.ToString("X16"));
        Debug.DebugMSG( "  Segment Virtual Address    : 0x" + segmentHeader.p_vaddr.ToString("X16"));
        Debug.DebugMSG( "  Segment Physical Address   : 0x" + segmentHeader.p_paddr.ToString("X16"));
        Debug.DebugMSG( "  Segment File Size          : 0x" + segmentHeader.p_filesz.ToString("X16"));
        Debug.DebugMSG( "  Segment Memory Size        : 0x" + segmentHeader.p_memsz.ToString("X16"));
        Debug.DebugMSG( "  Segment Align              : 0x" + segmentHeader.p_align.ToString("X16"));
        */
      }
      
      //Debug.DebugMSG(   "}" );
    
      return segmentHeader;
    }
    

    /// <summary>
    /// Parse the ELF file's symbol table.
    /// </summary>
    private void ParseSymbolTable()
    {
      EndianBinaryReader ebr = new EndianBinaryReader(binFile, endian);
      UInt32 numSymbols = (UInt32) headerRef["numEntriesInSymTable"];
      ELF_Symbol sym;
      Byte info, other;
      
      symRef = new Hashtable[numSymbols];

      // Read the symbol table
      for (UInt32 symNum = 0; symNum < numSymbols; symNum++)
      {
        symRef[symNum] = new Hashtable();
        
        // Go to current symbol
        ebr.BaseStream.Seek((Int64) ((UInt64)headerRef["symbolTableAddr"]) + ((UInt32)headerRef["symbolTableEntrySize"] * symNum),SeekOrigin.Begin);
        sym.st_name       = (UInt32) ebr.ReadUInt32();

        if (ELF_FileClass.ELFCLASS_32 == hdr.e_ident.fileClass)
        {
          sym.st_value    = (UInt64) ebr.ReadUInt32();
          sym.st_size     = (UInt64) ebr.ReadUInt32();
          info            = ebr.ReadByte();
          other           = ebr.ReadByte();
          sym.st_shndx    = ebr.ReadUInt16();
        }
        else
        {
          info            = ebr.ReadByte();
          other           = ebr.ReadByte();
          sym.st_shndx    = ebr.ReadUInt16();
          sym.st_value    = ebr.ReadUInt64();
          sym.st_size     = ebr.ReadUInt64();
        }
        sym.st_type       = (ELF_SymbolType) (info & 0xF);
        sym.st_binding    = (ELF_SymbolBinding) ((info >> 4) & 0xF);
        sym.st_visibility = (ELF_SymbolVisibility) (other & 0x3);
        
        /*
        Debug.DebugMSG( "Symbol[" + symNum + "] = \n{" );
        Debug.DebugMSG( "  Symbol Name Offset        : 0x" + sym.st_name.ToString("X8"));        
        Debug.DebugMSG( "  Symbol Value              : 0x" + sym.st_value.ToString("X16"));
        Debug.DebugMSG( "  Symbol Size               : 0x" + sym.st_size.ToString("X16"));
        Debug.DebugMSG( "  Symbol Type               : "   + sym.st_type);
        Debug.DebugMSG( "  Symbol Binding            : "   + sym.st_binding);
        Debug.DebugMSG( "  Symbol Visibility         : "   + sym.st_visibility);
        Debug.DebugMSG( "  Symbol's Relevant Section : 0x" + sym.st_shndx.ToString("X4"));
        Debug.DebugMSG( "}\n");
        */

        // Move to name in String Table
        ebr.BaseStream.Seek( (Int64) ((UInt64)headerRef["stringTableAddr"]) + (sym.st_name), SeekOrigin.Begin);
        symRef[symNum]["name"] = ELF_getStringFromStringTable();
        Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"name\"]: " + ((String)symRef[symNum]["name"]).ToString());

        symRef[symNum]["value"] = sym.st_value;
        Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"value\"]: " + ((UInt64)symRef[symNum]["value"]).ToString("X8"));

        symRef[symNum]["secNum"] = sym.st_shndx;
        Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"secNum\"]: " + ((UInt16)symRef[symNum]["secNum"]).ToString("X4"));

        symRef[symNum]["type"] = sym.st_type;
        Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"type\"]: " + sym.st_type);
        
        symRef[symNum]["binding"] = sym.st_binding;
        Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"binding\"]: " + sym.st_binding);

        symRef[symNum]["visibility"] = sym.st_visibility;
        Debug.DebugMSG("symRef[" + symNum.ToString() + "][\"visibility\"]: " + sym.st_visibility);

      }      
      Debug.DebugMSG("Parse Symbol Table Done");
    } // end of ParseSymbolTable()
    #endregion

    
    #region Private helper and debug functions
    /// <summary>
    /// Function to retrieve name string either from string table or from current stream pointer.
    /// </summary>
    /// <returns>String containing name.</returns>
    private String ELF_getStringFromStringTable()
    {
      Byte currByte;
      ArrayList name = new ArrayList(128);
      
      EndianBinaryReader ebr =  new EndianBinaryReader(binFile,(Endian) headerRef["endian"]);

      // Read characters and build string until terminating null
      currByte = ebr.ReadByte();
      
      while (currByte != 0)
      {
          name.Add(currByte);
          currByte = ebr.ReadByte();
      }

      if (name.Count > 128)
          Debug.DebugMSG(ASCIIEncoding.ASCII.GetString((Byte[])name.ToArray(typeof(Byte)), 0, name.Count));
      return ASCIIEncoding.ASCII.GetString((Byte[]) name.ToArray(typeof(Byte)), 0, name.Count);
    }
    #endregion


    #region Public Static Class Methods
    public static Boolean IsElfFile(String filename)
    {
      // Get File Details
      FileInfo fi = new FileInfo(filename);
      try
      {
        if (fi.Exists)
        {
          // Parse the input file header
          ParseELFHeader(new FileStream(filename, FileMode.Open, FileAccess.Read));
        }
      }
      catch (Exception e)
      {
        Console.Write(e.Message);
        return false;
      }
      return true;
    }
    
    public static ELF_Header ParseELFHeader(Stream fs)
    {
      ELF_Header hdr;

      // Read ELF Header
      fs.Seek(0, SeekOrigin.Begin);
      BinaryReader br = new BinaryReader(fs);

      hdr.e_ident.magic         = br.ReadBytes(4);
      hdr.e_ident.fileClass     = (ELF_FileClass) br.ReadByte();
      hdr.e_ident.dataEncoding  = (ELF_DataEncoding) br.ReadByte();
      hdr.e_ident.fileVersion   = (ELF_FileVersion) br.ReadByte();
      hdr.e_ident.osAbiID       = (ELF_OsAbiID) br.ReadByte();
      hdr.e_ident.abiVersion    = br.ReadByte();
      hdr.e_ident.pad           = br.ReadBytes(7);
      
      if ( (0x7F != hdr.e_ident.magic[0]) ||
           ('E' != hdr.e_ident.magic[1])  ||
           ('L' != hdr.e_ident.magic[2])  ||
           ('F' != hdr.e_ident.magic[3]) )
      {
        throw new Exception("ELF magic number not found. Not an ELF object file.");
      }
      
      if ( (ELF_FileClass.ELFCLASS_32 != hdr.e_ident.fileClass) &&
           (ELF_FileClass.ELFCLASS_64 != hdr.e_ident.fileClass) )
      {
        throw new Exception("Invalid ELF class. Not a valid ELF object file.");
      }
      
      if ( (ELF_DataEncoding.ELFDATA_2LSB != hdr.e_ident.dataEncoding) &&
           (ELF_DataEncoding.ELFDATA_2MSB != hdr.e_ident.dataEncoding) )
      {
        throw new Exception("Invalid ELF encoding. Not a valid ELF object file.");
      }
      
      if ( (ELF_FileVersion.ELFVER_CURRENT != hdr.e_ident.fileVersion) )
      {
        throw new Exception("Invalid ELF file version. Not a valid ELF object file.");
      }
              
      Debug.DebugMSG("ELF Identifier = \n{");
      Debug.DebugMSG("  magic[0]        : 0x" + hdr.e_ident.magic[0].ToString("X2"));
      Debug.DebugMSG("  magic[1]        : 0x" + hdr.e_ident.magic[1].ToString("X2"));
      Debug.DebugMSG("  magic[2]        : 0x" + hdr.e_ident.magic[2].ToString("X2"));
      Debug.DebugMSG("  magic[3]        : 0x" + hdr.e_ident.magic[3].ToString("X2"));
      Debug.DebugMSG("  fileClass       : " + hdr.e_ident.fileClass);        
      Debug.DebugMSG("  dataEncoding    : " + hdr.e_ident.dataEncoding);        
      Debug.DebugMSG("  fileVersion     : " + hdr.e_ident.fileVersion);
      Debug.DebugMSG("  OS/ABI ID       : " + hdr.e_ident.osAbiID);
      Debug.DebugMSG("  ABIVersion      : " + hdr.e_ident.abiVersion);
      Debug.DebugMSG("}\n\n");
      

      // Now that we have read and parsed the ELF Identifier array,
      // we have enough info to get the rest of the header and 
      // correctly parse entire file            
      Endian endian = (ELF_DataEncoding.ELFDATA_2LSB == hdr.e_ident.dataEncoding) ? Endian.LittleEndian : Endian.BigEndian;
      EndianBinaryReader ebr = new EndianBinaryReader(fs,endian);

      hdr.e_type          = (ELF_Type)    ebr.ReadUInt16();
      hdr.e_machine       = (ELF_Machine) ebr.ReadUInt16();
      hdr.e_version       = (ELF_Version) ebr.ReadUInt32();
      
      Debug.DebugMSG(   "ELF Type                               : " + hdr.e_type);        
      Debug.DebugMSG(   "ELF Machine                            : " + hdr.e_machine);        
      Debug.DebugMSG(   "ELF Version                            : " + hdr.e_version);
      
      // FIXME: Do we need this check? Is it a good idea?
      if (ELF_Type.ELFTYPE_EXEC != hdr.e_type)
      {
        throw new Exception("ELF file type is wrong - not a valid ELF executable.");
      }
      
      // Read entry point and program header and section header offsets
      // The size of these values is class dependent (32- or 64-bit)
      if (ELF_FileClass.ELFCLASS_32 == hdr.e_ident.fileClass)
      {
        hdr.e_entry       = (UInt64) ebr.ReadUInt32();
        hdr.e_phoff       = (UInt64) ebr.ReadUInt32();
        hdr.e_shoff       = (UInt64) ebr.ReadUInt32();
        
        Debug.DebugMSG( "ELF Entry Point                        : 0x" + hdr.e_entry.ToString("X8"));
        Debug.DebugMSG( "ELF Program Header Offset              : 0x" + hdr.e_phoff.ToString("X8"));        
        Debug.DebugMSG( "ELF Section Header Table Offset        : 0x" + hdr.e_shoff.ToString("X8"));
      }
      else
      {
        hdr.e_entry       = ebr.ReadUInt64();    
        hdr.e_phoff       = ebr.ReadUInt64();
        hdr.e_shoff       = ebr.ReadUInt64();
        
        Debug.DebugMSG( "ELF Entry Point                        : 0x" + hdr.e_entry.ToString("X16"));
        Debug.DebugMSG( "ELF Program Header Offset              : 0x" + hdr.e_phoff.ToString("X16"));        
        Debug.DebugMSG( "ELF Section Header Table Offset        : 0x" + hdr.e_shoff.ToString("X16"));
      }
      
      hdr.e_flags         = ebr.ReadUInt32();
      hdr.e_ehsize        = ebr.ReadUInt16();
      hdr.e_phentsize     = ebr.ReadUInt16();
      hdr.e_phnum         = ebr.ReadUInt16();
      hdr.e_shentsize     = ebr.ReadUInt16();
      hdr.e_shnum         = ebr.ReadUInt16();
      hdr.e_shstrndx      = ebr.ReadUInt16();
      
      
      Debug.DebugMSG(   "ELF Header Flags                       : 0x" + hdr.e_flags.ToString("X8"));
      Debug.DebugMSG(   "ELF Header Size In Bytes               : " + hdr.e_ehsize);
      Debug.DebugMSG(   "ELF Program Header Entry Size          : " + hdr.e_phentsize);
      Debug.DebugMSG(   "ELF Program Header Entry Count         : " + hdr.e_phnum);
      Debug.DebugMSG(   "ELF Section Header Table Entry Size    : " + hdr.e_shentsize);
      Debug.DebugMSG(   "ELF Section Header Table Entry Count   : " + hdr.e_shnum);
      Debug.DebugMSG(   "ELF Section Header String Table Index  : " + hdr.e_shstrndx);
      
      // Check for presence of program header
      if ( (hdr.e_phoff == 0) || ((hdr.e_phnum * hdr.e_phentsize) == 0) )
      {
        throw new Exception("No ELF program header. Not a valid ELF executable.");
      }
      
      return hdr;
    }
    #endregion
  } //End ELFFile class

} //end of namespace
