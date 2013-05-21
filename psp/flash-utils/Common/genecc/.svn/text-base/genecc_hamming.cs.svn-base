/* --------------------------------------------------------------------------
    FILE        : genecc_hamming.cs
    PURPOSE     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred    
    DESC        : ECC parity generator for EMIF 2.x Hamming Hardware
 ----------------------------------------------------------------------------- */
using System;
using System.Text;
using System.IO;
using System.Reflection;
using UtilLib;
using UtilLib.IO;

[assembly: AssemblyTitle("genecc")]
[assembly: AssemblyVersion("1.00.*")]

namespace TIBootAndFlash
{
  partial class Program
  {
    private struct ProgramCmdParams
    {
      public String inputfileName;

      public String outputFileName;
      
      public Boolean verbose;

      public Boolean valid;
    }
      
    /// <summary>
    /// Function to display help in case command-line is invalid
    /// </summary>
    static void DispHelp()
    {
      Console.Write("Usage:\n\n");
      Console.Write("genecc_"+devString+" [Options] <Input File Name>\n");
      Console.Write("\t" + "<Option> can be any of the following:\n");
      Console.Write("\t\t" + "-h                   \tShow this help screen.\n");
      Console.Write("\t\t" + "-v                   \tOutput results to console.\n"); 
      Console.Write("\t\t" + "-o <Output File Name>\tExplicitly specify the output filename.\n");
      Console.Write("\t\t" + "                     \tDefault is <input file name>_eccdata.bin\n");
      Console.Write("\n");
    }

    /// <summary>
    /// Function to parse the command line
    /// </summary>
    /// <param name="args">Array of command-line arguments</param>
    /// <returns>Struct of the filled in program arguments</returns>
    private static ProgramCmdParams ParseCmdLine(String[] args)
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
      myCmdParams.verbose = false;
      myCmdParams.outputFileName = null;
      myCmdParams.inputfileName = null;
      defaultExtension = "_eccdata.bin";

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
            case "o":
              myCmdParams.outputFileName = args[i + 1];
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "v":
              myCmdParams.verbose = true;
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
      if ( (!myCmdParams.valid) || (numUnhandledArgs != 1) || (argsHandled[args.Length-1]))
      {
          myCmdParams.valid = false;
          return myCmdParams;
      }
       
      // Get input file
      FileInfo fi = new FileInfo(args[args.Length-1]);
      if (fi.Exists)
      {
        myCmdParams.inputfileName = args[args.Length - 1];
        String extension = Path.GetExtension(fi.Name);
        if (myCmdParams.outputFileName == null)
        {
          myCmdParams.outputFileName = Path.GetFileNameWithoutExtension(fi.Name) + defaultExtension;
        }
      }
      else
      {
        Console.WriteLine("File not found.");
        myCmdParams.valid = false;
        return myCmdParams;
      }

      return myCmdParams;
    }
      
    /// <summary>
    /// Main entry point of application
    /// </summary>
    /// <param name="args">Array of command-line arguments</param>
    /// <returns>Return code: 0 for correct exit, -1 for unexpected exit</returns>
    static Int32 Main(String[] args)
    {
      // Assumes that in AssemblyInfo.cs, the version is specified as 1.0.* or the like,
      // with only 2 numbers specified;  the next two are generated from the date.
      System.Version v = System.Reflection.Assembly.GetExecutingAssembly().GetName().Version;
      
      // v.Build is days since Jan. 1, 2000, v.Revision*2 is seconds since local midnight
      Int32 buildYear = new DateTime( v.Build * TimeSpan.TicksPerDay + v.Revision * TimeSpan.TicksPerSecond * 2 ).AddYears(1999).Year;
      
      // Begin main code
      //Console.Clear();
      Console.WriteLine("-----------------------------------------------------");
      Console.WriteLine("   TI EMIF2.x Hamming ECC Parity Generator for " + devString  );
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
      
      // Create ECC object
      HammingECC h = new HammingECC(512);

      // Create binary writer for saving ECC data to output file
      BinaryWriter bw = new BinaryWriter(new FileStream(cmdParams.outputFileName,FileMode.Create,FileAccess.Write));      
      
      // Read input data from file
      Byte[] fileData = FileIO.GetFileData(cmdParams.inputfileName);
      
      Byte[] subArray = new Byte[512];
      
      
      for (int i=0; i<fileData.Length; i+=512)
      {
        for (int j=0; j<512; j++)
        {
          subArray[j] = (Byte) (((i+j) >= fileData.Length) ? (0xFF) : fileData[i+j]);
        }
        
        // Calculate parity of the message data
        Int32 parity = h.GenerateParity(subArray);
        
        // Prep the parity data and output it to file
        if (cmdParams.verbose)
        {
          Console.WriteLine("NAND operation #{0}",(i/512)+1);
          Console.WriteLine("\tNANDFxECC = 0x{0:X8}", parity);
        }
        bw.Write( parity );
      }
      
      return 0;
    }
  }
}
