 /* --------------------------------------------------------------------------
    FILE        : AISGen_OMAP-L138.cs
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
    DESC        : Concrete AISGen class implemenatation for OMAP-L138
 ----------------------------------------------------------------------------- */

using System;
using System.Text;
using System.Text.RegularExpressions;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Threading;
using System.Globalization;
using System.Collections;
using UtilLib.IO;
using UtilLib.CRC;

namespace AISGenLib
{
  /// <summary>
  /// AISGen class that is specific to DM643x devices (inherits from abtract base class AISGen)
  /// </summary>
  public class AISGen_OMAP_L138:AISGen
  {
    /// <summary>
    /// String definitions for built-in ROM functions
    /// </summary>
    public struct ROMFunctionNames
    {
      public const String PLL0Config          = "PLL0Config";
      public const String PLL1Config          = "PLL1Config";
      public const String PeriphClockConfig   = "PeriphClockConfig";
      public const String EMIF3AConfigDDR     = "EMIF3AConfigDDR";
      public const String EMIF25ConfigSDRAM   = "EMIF25ConfigSDRAM";
      public const String EMIF25ConfigAsync   = "EMIF25ConfigAsync";
      public const String PLLandClockConfig   = "PLLandClockConfig";
      public const String PSCConfig           = "PSCConfig";
      public const String PINMUXConfig        = "PinMuxConfig";
      public const String FastBoot            = "FastBoot";
      public const String IOPUConfig          = "IOPUConfig";
      public const String MPUConfig           = "MPUConfig";
      public const String TAPSConfig          = "TAPSConfig";
    }
    
    /// <summary>
    /// The public constructor for the DM637x device AIS generator.
    /// The constructor is where the device differentiation is defined.
    /// </summary>
    public AISGen_OMAP_L138()
    {
      // Define the device name - used for default file names
      devNameShort = "OMAP-L138";
      devNameLong = "OMAPL138";

      // Define the device caches (they are considered internal memories since 
      // bootrom turns off caching) -  two identical sets since the memory map 
      // has the caches at two locations
      Cache = new CacheInfo[6];
      Cache[0].level = CacheLevel.L2;
      Cache[0].type = CacheType.Program | CacheType.Data;
      Cache[0].startAddr = 0x00800000;
      Cache[0].size = 0x40000;
            
      Cache[1].level = CacheLevel.L1;
      Cache[1].type = CacheType.Program;
      Cache[1].startAddr = 0x00E08000;
      Cache[1].size = 0x8000;
            
      Cache[2].level = CacheLevel.L1;
      Cache[2].type = CacheType.Data;
      Cache[2].startAddr = 0x00F10000;
      Cache[2].size = 0x8000;

      Cache[3].level = CacheLevel.L2;
      Cache[3].type = CacheType.Program | CacheType.Data;
      Cache[3].startAddr = 0x10800000;
      Cache[3].size = 0x40000;

      Cache[4].level = CacheLevel.L1;
      Cache[4].type = CacheType.Program;
      Cache[4].startAddr = 0x10E08000;
      Cache[4].size = 0x8000;

      Cache[5].level = CacheLevel.L1;
      Cache[5].type = CacheType.Data;
      Cache[5].startAddr = 0x10F10000;
      Cache[5].size = 0x8000;

      // Define the IDMA channels for internal memory transfers
      IDMA = new IDMARegisters[2];
      IDMA[0] = new IDMARegisters(0, 0x01820000);
      IDMA[1] = new IDMARegisters(1, 0x01820100);
            
      // Define OMAP-L138 ROM boot loader functions
      ROMFunc = new ROMFunction[13];
      ROMFunc[0].funcName = ROMFunctionNames.PLL0Config;
      ROMFunc[0].iniSectionName = "PLL0CONFIG";
      ROMFunc[0].numParams = 2;
      ROMFunc[0].paramNames = new String[2] { "PLL0CFG0", "PLL0CFG1" };
      
      ROMFunc[1].funcName = ROMFunctionNames.PLL1Config;
      ROMFunc[1].iniSectionName = "PLL1CONFIG";
      ROMFunc[1].numParams = 2;
      ROMFunc[1].paramNames = new String[2] { "PLL1CFG0", "PLL1CFG1" };
      
      ROMFunc[2].funcName = ROMFunctionNames.PeriphClockConfig;
      ROMFunc[2].iniSectionName = "PERIPHCLKCFG";
      ROMFunc[2].numParams = 1;
      ROMFunc[2].paramNames = new String[1] { "PERIPHCLKCFG" };

      ROMFunc[3].funcName = ROMFunctionNames.EMIF3AConfigDDR;
      ROMFunc[3].iniSectionName = "EMIF3DDR";
      ROMFunc[3].numParams = 8;
      ROMFunc[3].paramNames = new String[8] { "PLL1CFG0", "PLL1CFG1", "DDRPHYC1R", "SDCR", "SDTIMR", "SDTIMR2", "SDRCR", "CLK2XSRC" };

      ROMFunc[4].funcName = ROMFunctionNames.EMIF25ConfigSDRAM;
      ROMFunc[4].iniSectionName = "EMIF25SDRAM";
      ROMFunc[4].numParams = 5;
      ROMFunc[4].paramNames = new String[5] { "SDBCR", "SDTIMR", "SDRSRPDEXIT", "SDRCR", "DIV4p5_CLK_ENABLE" };
      
      ROMFunc[5].funcName = ROMFunctionNames.EMIF25ConfigAsync;
      ROMFunc[5].iniSectionName = "EMIF25ASYNC";
      ROMFunc[5].numParams = 5;
      ROMFunc[5].paramNames = new String[5] { "A1CR", "A2CR", "A3CR", "A4CR", "NANDFCR" };
      
      ROMFunc[6].funcName = ROMFunctionNames.PLLandClockConfig;
      ROMFunc[6].iniSectionName = "PLLANDCLOCKCONFIG";
      ROMFunc[6].numParams = 3;
      ROMFunc[6].paramNames = new String[3] { "PLL0CFG0", "PLL0CFG1", "PERIPHCLKCFG" };
      
      ROMFunc[7].funcName = ROMFunctionNames.PSCConfig;
      ROMFunc[7].iniSectionName = "PSCCONFIG";
      ROMFunc[7].numParams = 1;
      ROMFunc[7].paramNames = new String[1] { "LPSCCFG" };

      ROMFunc[8].funcName = ROMFunctionNames.PINMUXConfig;
      ROMFunc[8].iniSectionName = "PINMUX";
      ROMFunc[8].numParams = 3;
      ROMFunc[8].paramNames = new String[3] { "REGNUM", "MASK", "VALUE" };
      
      ROMFunc[9].funcName = ROMFunctionNames.FastBoot;
      ROMFunc[9].iniSectionName = "FASTBOOT";
      ROMFunc[9].numParams = 0;
      ROMFunc[9].paramNames = null;
      
      ROMFunc[10].funcName = ROMFunctionNames.IOPUConfig;
      ROMFunc[10].iniSectionName = "IOPUCONFIG";
      ROMFunc[10].numParams = 2;
      ROMFunc[10].paramNames = new String[2] { "IOPUSELECT", "MPPAVALUE" };
      
      ROMFunc[11].funcName = ROMFunctionNames.MPUConfig;
      ROMFunc[11].iniSectionName = "MPUCONFIG";
      ROMFunc[11].numParams = 4;
      ROMFunc[11].paramNames = new String[4] { "MPUSELECT", "STARTADDR" ,"ENDADDR" ,"MPPAVALUE" };
      
      ROMFunc[12].funcName = ROMFunctionNames.TAPSConfig;
      ROMFunc[12].iniSectionName = "TAPSCONFIG";
      ROMFunc[12].numParams = 1;
      ROMFunc[12].paramNames = new String[1] { "TAPSCFG" };
      
      // Configuration info for the AISExtras functions (provided in AISExtraFileName COFF file)
/*      AISExtraFileName = null;

      AISExtraFunc = null;*/
      AISExtraFileName = "AISExtra_"+devNameShort+".out";

      AISExtraFunc = new AISExtraFunction[1];
      AISExtraFunc[0].funcName = "MakeROMEmulatableAndWait";
      AISExtraFunc[0].iniSectionName = "OPENROMFORDEBUG";
      AISExtraFunc[0].numParams = 0;
      AISExtraFunc[0].paramNames = null;
      AISExtraFunc[0].isInitFunc = true;      

      // OMAP-L138 is little endian
      devEndian = Endian.LittleEndian;
      
      // OMAP-L138 AIS data is little endian;
      devAISEndian = Endian.LittleEndian;

      // Default settings for UARTSendDONE function
      UARTSendDONEAddr = 0x0;
      SendUARTSendDONE = false;

      // Default boot mode (can be changed from INI file) for this device
      bootMode = BootModes.NONE;

      // Create default CRC object for this device
      devCRC = new CRC32(0x04C11DB7, 0xFFFFFFFF, 0xFFFFFFFF, true, 1, UtilLib.CRC.CRCType.INCREMENTAL, UtilLib.CRC.CRCCalcMethod.LUT);
      
      crcType = CRCCheckType.NO_CRC;
    } 
  }
} //end of AISGenLib namespace
