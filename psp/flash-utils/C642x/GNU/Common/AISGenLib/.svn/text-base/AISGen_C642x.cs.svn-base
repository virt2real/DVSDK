/* --------------------------------------------------------------------------
    FILE        : AISGen_C642x.cs
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
    DESC        : TI C642x AISGen Class
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
    /// AISGen class that is specific to C642x devices (inherits from abtract base class AISGen)
    /// </summary>
    public class AISGen_C642x:AISGen
    {
        /// <summary>
        /// String definitions for built-in ROM functions
        /// </summary>
        public struct ROMFunctionNames
        {
            public const String PLLConfig = "PLLConfig";
            public const String EMIFConfig = "EMIFConfig";
            public const String DDRConfig = "DDRConfig";
            public const String PINMUXConfig = "PinMuxConfig";
        }

        /// <summary>
        /// String definitions for extra AIS functions
        /// </summary>
        public struct AISExtraFunctionNames
        {
            public const String LPSCTransition = "LPSCTransition";
        }

        /// <summary>
        /// The public constructor for the DM637x device AIS generator.
        /// The constructor is where the device differentiation is defined.
        /// </summary>
        public AISGen_C642x()
        {
            // Define the device name - used for default file names
            devNameShort = "C642x";
            devNameLong = "TMS320C642x";

            // Define the device caches (they are considered internal memories since 
            // bootrom turns off caching) -  two identical sets since the memory map 
            // has the caches at two locations
            Cache = new CacheInfo[6];
            Cache[0].level = CacheLevel.L2;
            Cache[0].type = CacheType.Program | CacheType.Data;
            Cache[0].startAddr = 0x00800000;
            Cache[0].size = 0x20000;
            
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
            Cache[3].size = 0x20000;

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
            
            // Define C642x ROM boot loader functions
            ROMFunc = new ROMFunction[4];
            ROMFunc[0].funcName = AISGen_C642x.ROMFunctionNames.PLLConfig;
            ROMFunc[0].iniSectionName = "PLL";
            ROMFunc[0].numParams = 3;
            ROMFunc[0].paramNames = new String[3] { "PLLM", "PLLDIV1", "CLK_SRC" };

            ROMFunc[1].funcName = AISGen_C642x.ROMFunctionNames.EMIFConfig;
            ROMFunc[1].iniSectionName = "EMIF";
            ROMFunc[1].numParams = 5;
            ROMFunc[1].paramNames = new String[5] { "AB1CR", "AB2CR", "AB3CR", "AB4CR", "NANDFCR" };

            ROMFunc[2].funcName = AISGen_C642x.ROMFunctionNames.DDRConfig;
            ROMFunc[2].iniSectionName = "DDR";
            ROMFunc[2].numParams = 9;
            ROMFunc[2].paramNames = new String[9] { "DDRPLLM","DDRCLKDIV","VPFECLKDIV","CLK_SRC","DDRPHYCR",
                                                    "SDBCR","SDTIMR","SDTIMR2","SDRCR"};

            ROMFunc[3].funcName = AISGen_C642x.ROMFunctionNames.PINMUXConfig;
            ROMFunc[3].iniSectionName = "PINMUX";
            ROMFunc[3].numParams = 2;
            ROMFunc[3].paramNames = new String[2] { "PINMUX0", "PINMUX1" };

            // Configuration info for the AISExtras functions (provided in AISExtraFileName COFF file)
            AISExtraFileName = "AISExtra_"+devNameShort+".out";

            AISExtraFunc = new AISExtraFunction[1];
            AISExtraFunc[0].funcName = AISGen_C642x.AISExtraFunctionNames.LPSCTransition;
            AISExtraFunc[0].iniSectionName = "LPSC";
            AISExtraFunc[0].numParams = 2;
            AISExtraFunc[0].paramNames = new String[2] { "MODNUM", "STATE" };
            AISExtraFunc[0].isInitFunc = true;

            // C642x is little endian
            devEndian = Endian.LittleEndian;

            // Create a temp binary file for this object
            devAISFileName = devNameShort +".ais";
            devAISFileStream = null;

            // INI file describes ROM function parameters
            devINIFileName = devNameShort + ".ini";

            // Default settings for UARTSendDONE function
            UARTSendDONEAddr = 0x0;
            SendUARTSendDONE = false;

            // Default boot mode (can be changed from INI file) for this device
            bootMode = BootModes.NONE;

            // Create default CRC object for this device
            devCRC = new CRC32(0x04C11DB7, 0, 0, false, 1);
            
            crcType = CRCCheckType.NO_CRC;
        } 
    }

} //end of AISGenLib namespace

