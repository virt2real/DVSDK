/* --------------------------------------------------------------------------
    FILE        : HexAIS.cs
    PURPOSE     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred    
    DESC        : Secure HEX generator for OMAP-L138
 ----------------------------------------------------------------------------- */

using System;
using System.Text;
using System.IO;
using AISGenLib;
using System.Reflection;
using UtilLib;
using UtilLib.IO;
using UtilLib.HexConv;

[assembly: AssemblyTitle("SecureHexAIS")]
[assembly: AssemblyVersion("1.00.*")]

namespace TIBootAndFlash
{
  partial class Program
  {
    private enum ConvType: uint
    {
      Exec2Bin    = 0,
      Exec2CArray = 1,
      Exec2Srec   = 2,
      Exec2Text   = 3
    };

    private struct ProgramCmdParams
    {
      // Program conversion type
      public ConvType convType;

      public String inputfileName;

      public String iniFileName;

      public String outFileName;

      public Boolean valid;
    }
      
    /// <summary>
    /// Function to display help in case command-line is invalid
    /// </summary>
    static void DispHelp()
    {
      Console.Write("Usage:\n\n");
      Console.Write("SecureHexAIS_"+devString+"[Options] <Input File Name>\n");
      Console.Write("\t" + "<Option> can be any of the following:\n");
      Console.Write("\t\t" + "-h                   \tShow this help screen.\n");        
      Console.Write("\t\t" + "-ini <INI file name> \tSpecify the ini file (default is " + devString + ".ini).\n");            
      Console.Write("\t\t" + "-otype <Output Type> \tSpecify type of output file, from following:.\n");
      Console.Write("\t\t" + "     binary          \t     Create a binary AIS file (.bin), default.\n");
      Console.Write("\t\t" + "     carray          \t     Create a text file with AIS data in a C array (.c).\n");
      Console.Write("\t\t" + "     srecord         \t     Create a Motorola S-record format (.srec).\n");
      Console.Write("\t\t" + "     text            \t     Create a text file with AIS data as ASCII text (.txt).\n");
      Console.Write("\t\t" + "-o <Output File Name>\tExplicitly specify the output filename.\n");
      Console.Write("\t\t" + "                     \tDefault is input file name with extension based on\n");
      Console.Write("\t\t" + "                     \toutput type.\n");
      Console.Write("\n");
      Console.Write("Note that all hex outputs are written in Motorola S3 hex format with destination\n");
      Console.Write("address pointing the start of the "+devString+" AEMIF CS2 memory region.\n");
    }

    /// <summary>
    /// Function to parse the command line
    /// </summary>
    /// <param name="args">Array of command-line arguments</param>
    /// <returns>Struct of the filled in program arguments</returns>
    static ProgramCmdParams ParseCmdLine(String[] args)
    {
      ProgramCmdParams myCmdParams = new ProgramCmdParams();
      Boolean[] argsHandled = new Boolean[args.Length];

      UInt32 numUnhandledArgs, numHandledArgs = 0;
      String s,defaultExtension;

      // Check for no argumnents
      if (args.Length == 0)
      {
        myCmdParams.valid = false;
        return myCmdParams;
      }

      // Set Defaults
      myCmdParams.valid = true;
      myCmdParams.outFileName = null;
      myCmdParams.iniFileName = null;
      myCmdParams.inputfileName = null;
      myCmdParams.convType = ConvType.Exec2Bin;
      defaultExtension = ".bin";

      // Initialize array of handled argument booleans to false
      for (int i = 0; i < argsHandled.Length; i++)
        argsHandled[i] = false;

      // For loop to check for all dash options
      for (int i = 0; i < args.Length; i++)
      {
        s = args[i];
        if (s.StartsWith("-"))
        {
          switch (s.Substring(1).ToLower())
          {
            case "otype":
              String temp = args[i + 1];
              if (temp.ToLower().Equals("binary"))
              {
                myCmdParams.convType = ConvType.Exec2Bin;
                defaultExtension = ".bin";
              }
              else if (temp.ToLower().Equals("carray"))
              {
                myCmdParams.convType = ConvType.Exec2CArray;
                defaultExtension = ".c";
              }
              else if (temp.ToLower().Equals("srecord"))
              {
                myCmdParams.convType = ConvType.Exec2Srec;
                defaultExtension = ".srec";
              }
              else if (temp.ToLower().Equals("text"))
              {
                myCmdParams.convType = ConvType.Exec2Text;
                defaultExtension = ".txt";
              }
              else
              {
                myCmdParams.valid = false;
              }
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "ini":
              myCmdParams.iniFileName = args[i + 1];
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "o":
              myCmdParams.outFileName = args[i + 1];
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            default:
              myCmdParams.valid = false;
              break;
          }
          argsHandled[i] = true;
          numHandledArgs++;
        }
      }
      numUnhandledArgs = (UInt32)(args.Length - numHandledArgs);
      
      // Check to make sure we are still valid
      if ( (!myCmdParams.valid))
      {
          return myCmdParams;
      }
      
      // Check to see if one last arg is still left - if so it is input object filename
      if ((numUnhandledArgs == 1) && (!argsHandled[args.Length-1]))
      {
        // Get input file
        FileInfo fi = new FileInfo(args[args.Length-1]);
        if (fi.Exists)
        {
          myCmdParams.inputfileName = args[args.Length - 1];
          String extension = Path.GetExtension(fi.Name);
          if (myCmdParams.outFileName == null)
          {
            myCmdParams.outFileName = Path.GetFileNameWithoutExtension(fi.Name) + defaultExtension;
          }
        }
      }
      
      if (myCmdParams.outFileName == null)
      {
        myCmdParams.outFileName = devString + "_boot_image.ais";
      }

      return myCmdParams;
    }
      
    /// <summary>
    /// Main program.
    /// </summary>
    /// <param name="args">Input commandline arguments</param>
    /// <returns>Return code</returns>
    static Int32 Main(String[] args)
    {          
        // Assumes that in AssemblyInfo.cs, the version is specified as 1.0.* or the like,
        // with only 2 numbers specified;  the next two are generated from the date.
        System.Version v = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
        
        // v.Build is days since Jan. 1, 2000, v.Revision*2 is seconds since local midnight
        Int32 buildYear = new DateTime( v.Build * TimeSpan.TicksPerDay + v.Revision * TimeSpan.TicksPerSecond * 2 ).AddYears(1999).Year;
        
        // Begin main code
        Console.Clear();
        Console.WriteLine("-----------------------------------------------------");
        Console.WriteLine("   TI AIS Hex File Generator for " + devString   );
        Console.WriteLine("   (C) "+buildYear+", Texas Instruments, Inc."        );
        Console.WriteLine("   Ver. "+v.Major+"."+v.Minor.ToString("D2")          );
        Console.WriteLine("-----------------------------------------------------");
        Console.Write("\n\n");            
        

        // Parse the input command line parameters
        ProgramCmdParams cmdParams = ParseCmdLine(args);
        if (!cmdParams.valid)
        {
            DispHelp();
            return -1;
        }   
        
        // Now proceed with main program
        FileStream tempAIS_fs = null;
        Byte[] AISData, convertedData;
                                
        AISGen_DM643x_Secure generator = new AISGen_DM643x_Secure();
          
        // Update the default INI file name to the one supplied on the command line
        if (cmdParams.iniFileName == null)
        {
          cmdParams.iniFileName = generator.DeviceNameShort + ".ini";
        }
        
        // Read the INI data from file
        INISection[] iniSecs = INI.Parse(new FileStream(cmdParams.iniFileName, FileMode.Open, FileAccess.Read));
        
        // Force section-by-section CRC checks (may be overridden in INI file)
        generator.CRCType = CRCCheckType.SECTION_CRC;

        // Do the AIS generation
        try
        {
          AISData = AISGen.SecureGenAIS(cmdParams.inputfileName, generator, iniSecs);   
        }
        catch (Exception e)
        {
          System.Diagnostics.StackTrace trace = new System.Diagnostics.StackTrace(e, true);
        
          Console.WriteLine(e.StackTrace);
          Console.WriteLine(e.Message);
          Console.WriteLine("Unhandled Exception!!! Application will now exit.");
          return -1;
        }
        
        // Check if SecureAISGen completed successfully
        if (AISData == null)
        {
          Console.WriteLine("AIS conversion failed.");
          return -1;
        }
        
        using (tempAIS_fs = new FileStream(cmdParams.outFileName, FileMode.Create, FileAccess.Write))
        {
          Console.WriteLine("Saving output as {0}.", cmdParams.outFileName);
        
          // Convert the AIS data to the correct output format
          switch ( cmdParams.convType )
          {
            case ConvType.Exec2Bin:
              tempAIS_fs.Write(AISData, 0, (int)AISData.Length);
              break;
            case ConvType.Exec2CArray:
              convertedData = CArray.bin2CArray(AISData, 4);
              tempAIS_fs.Write(convertedData, 0, (int)convertedData.Length);
              break;
            case ConvType.Exec2Srec:
              convertedData = SRecord.bin2srec(AISData, 0x60000000, 32);
              tempAIS_fs.Write(convertedData, 0, (int)convertedData.Length);
              break;
            case ConvType.Exec2Text:
              Console.WriteLine("Mode Not supported.");
              //Byte[] val = SRecord.bin2srec(aisData, 0x60000000, 32);
              break;            
          }
        }
                
        Console.WriteLine("Conversion complete.");
        return 0;
    }
  }
}
