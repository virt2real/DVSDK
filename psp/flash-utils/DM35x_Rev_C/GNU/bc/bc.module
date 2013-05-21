/* --------------------------------------------------------------------------
    FILE        : bc.cs
    PURPOSE     : Host console app for binary creation (prefixing of header)
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
 ----------------------------------------------------------------------------- */

using System;
using System.Text;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Threading;
using System.Globalization;
using UtilLib;
using UtilLib.IO;
using UtilLib.CRC;

[assembly: AssemblyTitle("BinCreator")]
[assembly: AssemblyVersion("1.00.*")]

namespace TIBootAndFlash
{
  /// <summary>
  /// Enumeration for Magic Flags that the UBL expects to see
  /// </summary>
  public enum MagicFlags : uint
  {
    MAGIC_NUMBER_VALID   = 0xA1ACED00,
    MAGIC_NUMBER_UBL     = 0xA1ACED00,
    MAGIC_NUMBER_UBOOT   = 0xA1ACED66,
    MAGIC_NUMBER_INVALID = 0xFFFFFFFF
  };


  /// <summary>
  /// Structure to hold command parameters
  /// </summary>
  struct ProgramCmdParams
  {
    /// <summary>
    /// Flag to indicate if command line is valid
    /// </summary>
    public Boolean valid;

    /// <summary>
    /// This should be transmitted alone in response to the BOOTPSP.
    /// </summary>
    public MagicFlags CMDMagicFlag;

    /// <summary>
    /// String containing filename of the input binary file
    /// </summary>
    public String inFileName;

    /// <summary>
    /// String containing filename of the output binary file
    /// </summary>
    public String outFileName;

    /// <summary>
    /// Address where the app should be decoded to and 
    /// run from (if appropriate).
    /// </summary>
    public UInt32 loadAddr;

    /// <summary>
    /// Address where the app begin execution 
    /// </summary>
    public UInt32 startAddr;
    
    /// <summary>
    /// Block number where header and binary will start being written to
    /// </summary>
    public UInt32 blockNum;
    
    /// <summary>
    /// Page size (in bytes) of the NAND device that the image will be written to
    /// </summary>
    public UInt32 pageSize;
  }
  
    
  /// <summary>
  /// Main program Class
  /// </summary>
  partial class Program
  {
    //**********************************************************************************
    #region Class variables and members
          
    /// <summary>
    /// The main thread used to actually execute everything
    /// </summary>
    public static Thread workerThread;

    /// <summary>
    /// Global boolean to indicate successful completion of workerThread
    /// </summary>
    public static Boolean workerThreadSucceeded = false;

    /// <summary>
    /// Public variable to hold needed command line and program parameters
    /// </summary>
    public static ProgramCmdParams cmdParams;


    #endregion
    //**********************************************************************************


    //**********************************************************************************
    #region Code for Main thread

    /// <summary>
    /// Help Display Function
    /// </summary>
    private static void DispHelp()
    {
      Console.Write("Usage:");
      Console.Write("\n\tbc_"+devString+" <Required Options> [<Other Options>] <Binary Image File>\n");
      Console.Write("\n\t" + "<Required Options> must contain the following: " +
                    "\n\t\t" + "-blockNum <block number>         \tBlock image will be written to (should be >= 1)." +
                    "\n\t\t" + "-pageSize <page size in bytes>   \tNAND device's page size in bytes (512, 2048, 4096).\n" );
      Console.Write("\n\t" + "<Other Options> can be the following: " +
                    "\n\t\t" + "-uboot                           \tFormat header for U-boot image, otherwise default for UBL" +
                    "\n\t\t" + "-startAddr <entry point address> \tSpecify entry point in hex." +
                    "\n\t\t" + "-loadAddr <image load address>   \tSpecify load address in hex." +
                    "\n\t\t" + "-o <Output file name>            \tSpecify output file name if you don't like default" +                    
                    "\n\t\t" + "-h                               \tDisplay this help screen.\n");
      Console.Write("\n\t" + "The default start addresses and load addresses are as follows" +
                    "\n\t\t" + "UBL Start Addr: 0x0100, UBL Load Addr: 0x0020 (this is fixed by UBL)" +
                    "\n\t\t" + "U-boot Start Addr: 0x81080000, U-boot Load Addr: 0x81080000\n" );
      Console.Write("\n\t" + "The images produced by this utility are expected to be used within the" +
                    "\n\t" + "U-boot enviroment and to be flashed using the U-boot nand commands." +
                    "\n\t" + "The user should ensure that the page size is correct and that the image" +
                    "\n\t" + "is written to the block specified when the image was created." );
    }   
 
    /// <summary>
    /// Parse the command line into the appropriate internal command structure
    /// </summary>
    /// <param name="args">The array of strings passed to the command line.</param>
    public static ProgramCmdParams ParseCmdLine(String[] args)
    {
      ProgramCmdParams myCmdParams =  new ProgramCmdParams();
      Boolean[] argsHandled = new Boolean[args.Length];
      Int32 numFiles = -1;
      UInt32 numUnhandledArgs,numHandledArgs=0;
      String s;

      if (args.Length == 0)
      {
          myCmdParams.valid = false;
          return myCmdParams;
      }

      // Initialize array of handled argument booleans to false
      for (int i = 0; i < argsHandled.Length; i++ )
        argsHandled[i] = false;

      // Set Defualts for parsing
      myCmdParams.CMDMagicFlag  = MagicFlags.MAGIC_NUMBER_INVALID;
      myCmdParams.valid         = true;
      myCmdParams.inFileName    = null;
      myCmdParams.outFileName   = null;
      myCmdParams.loadAddr      = 0xFFFFFFFF;
      myCmdParams.startAddr     = 0xFFFFFFFF;

      // For loop for required options
      for(int i = 0; i<args.Length; i++)
      {
        s = args[i];
        if (s.StartsWith("-"))
        {
          switch (s.Substring(1).ToLower())
          {
            case "pagesize":
              if (args[i + 1].StartsWith("0x"))
              {
                args[i + 1] = args[i + 1].Substring(2);
                myCmdParams.pageSize = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
              }
              else
              {
                myCmdParams.pageSize = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.Number);
              }
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "blocknum":
              if (args[i + 1].StartsWith("0x"))
              {
                args[i + 1] = args[i + 1].Substring(2);
                myCmdParams.blockNum = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
              }
              else
              {
                myCmdParams.blockNum = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.Number);
              }
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            default:
              continue;
          }
          argsHandled[i] = true;
          numHandledArgs++;
          
          if (!myCmdParams.valid)
            return myCmdParams;
        }
      }
      
      // Must have received pageSize, blockNum, and their values
      if (numHandledArgs != 4)
      {
        myCmdParams.valid = false;
        return myCmdParams;
      }

      // For loop for all other dash options
      for(int i = 0; i<args.Length; i++)
      {
        s = args[i];
        if ((s.StartsWith("-")) && (argsHandled[i] != true))
        {
          switch (s.Substring(1).ToLower())
          {
            case "uboot":
              myCmdParams.CMDMagicFlag = MagicFlags.MAGIC_NUMBER_UBOOT;
              myCmdParams.valid = true;
              break;
            case "startaddr":
              if (args[i + 1].StartsWith("0x"))
                args[i + 1] = args[i + 1].Substring(2);
              myCmdParams.startAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "loadaddr":
              if (args[i + 1].StartsWith("0x"))
                args[i + 1] = args[i + 1].Substring(2);
              myCmdParams.loadAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
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
          if (!myCmdParams.valid)
            return myCmdParams;
        }
      } // end of for loop for handling dash params
      
      // We should always expect 1 binary file for input
      numFiles = 1;
     
      // Verify that the number of unhandled arguments is equal to numFiles
      // If not, then there is a problem.
      numUnhandledArgs = (UInt32) (args.Length - numHandledArgs);
      if (numUnhandledArgs != numFiles)
      {
        myCmdParams.valid = false;
        return myCmdParams;
      }
                
      // This for loop handles all othe params (namely filenames)
      for (int i = 0; i < args.Length; i++)
      {
        if (!argsHandled[i])
        {
          switch (numFiles)
          {
            case 1:
              if (myCmdParams.inFileName == null)
              {
                myCmdParams.inFileName = args[i];
              }
              else
              {
                myCmdParams.valid = false;
              }
              break;
            default:
              myCmdParams.valid = false;
              break;
          }
        }    
        argsHandled[i] = true;
        numHandledArgs++;
        if (!myCmdParams.valid) return myCmdParams;
      } // end of for loop handling file name inputs

      // default to UBL usage
      if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
          myCmdParams.CMDMagicFlag = MagicFlags.MAGIC_NUMBER_UBL;
      
      // Set output file name to default      
      if (myCmdParams.outFileName == null)
      {
        myCmdParams.outFileName = 
          Path.GetFileNameWithoutExtension(myCmdParams.inFileName) + "_withNANDHeader" + Path.GetExtension(myCmdParams.inFileName);
      }
      
      // Set start and load addresses to default if not provided
      if (myCmdParams.startAddr == 0xFFFFFFFF)
      {
        if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_UBL)
          myCmdParams.startAddr = 0x00000100;
        else
          myCmdParams.startAddr = 0x81080000;
      }
      
      if (myCmdParams.loadAddr == 0xFFFFFFFF)
      {
        if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_UBL)
          myCmdParams.loadAddr = 0x00000020;  // Not used for UBL, but this is the value the RBL uses
        else
          myCmdParams.loadAddr = 0x81080000;
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
      Console.Clear();
      Console.WriteLine("-----------------------------------------------------");
      Console.WriteLine("   TI Binary Creator for " + devString                );
      Console.WriteLine("   (C) "+buildYear+", Texas Instruments, Inc."        );
      Console.WriteLine("   Ver. "+v.Major+"."+v.Minor.ToString("D2")          );
      Console.WriteLine("-----------------------------------------------------");
      Console.Write("\n\n");

      // Parse command line
      cmdParams = ParseCmdLine(args);
      if (!cmdParams.valid)
      {
        DispHelp();
        return -1;
      }

      Console.WriteLine("Preparing binary image with header prepended...\n");
      Console.WriteLine("  Intended NAND device has {0} byte pages.",cmdParams.pageSize);
      Console.WriteLine("  Image intended for block {0}.",cmdParams.blockNum);
      Console.WriteLine("  Image entry point is 0x{0:X8}.",cmdParams.startAddr);
      Console.WriteLine("  Image load address is 0x{0:X8}.",cmdParams.loadAddr);
      
      
      // Setup the thread that will actually do all the work of interfacing to
      // the Device boot ROM.  Start that thread.
      workerThread = new Thread(new ThreadStart(Program.WorkerThreadStart));
      workerThread.Start();

      // Wait for a key to terminate the program
      while ((workerThread.IsAlive) && (!Console.KeyAvailable))
      {
        Thread.Sleep(1000);
      }
                 
      // If a key is pressed then abort the worker thread and close the serial port
      try
      {
        if (Console.KeyAvailable)
        {
          Console.ReadKey();
          Console.WriteLine("Aborting program...");
          workerThread.Abort();
        }
        else if (workerThread.IsAlive)
        {
          Console.WriteLine("Aborting program...");
          workerThread.Abort();
        }
        
        while ((workerThread.ThreadState & ThreadState.Stopped) != ThreadState.Stopped){}
      }
      catch (Exception e)
      {
        Console.WriteLine("Abort thread error...");
        Console.WriteLine(e.GetType());
        Console.WriteLine(e.Message);
      }
      
      if (workerThreadSucceeded)
      {
        Console.WriteLine("\nOperation completed successfully.");
        return 0;
      }
      else
      {
        Console.WriteLine("\nOperation did NOT complete successfully.");
        return -1;
      }
    }
    #endregion
    //**********************************************************************************
    

    //**********************************************************************************
    #region Code for binary image generation

    /// <summary>
    /// The main function of the thread where all the cool stuff happens
    /// to interface with the device
    /// </summary>
    public static void WorkerThreadStart()
    {
      // Local Variables for holding file data
      Byte[] inImageData;
      Byte[] outImageData; 
      UInt32 numPages;
      
      // Read the image data we will transmit
      inImageData = FileIO.GetFileData(cmdParams.inFileName);
      
      // Get number of pages occupied by the binary image
      numPages = ((UInt32)inImageData.Length) / cmdParams.pageSize;
      if ((numPages * cmdParams.pageSize) < inImageData.Length)
        numPages++;
      
      //Allocate output image data and initialize it
      outImageData = new Byte[cmdParams.pageSize * (numPages+1)];
      for (UInt32 i = 0; i < outImageData.Length; i++)
      {
        outImageData[i] = (Byte) 0xFF;
      }

      // Fill in the header
      BitConverter.GetBytes((UInt32)cmdParams.CMDMagicFlag).CopyTo(outImageData, 0);
      BitConverter.GetBytes((UInt32)cmdParams.startAddr   ).CopyTo(outImageData, 4);
      BitConverter.GetBytes((UInt32)numPages              ).CopyTo(outImageData, 8);
      BitConverter.GetBytes((UInt32)cmdParams.blockNum    ).CopyTo(outImageData, 12);
      BitConverter.GetBytes((UInt32)1                     ).CopyTo(outImageData, 16);
      BitConverter.GetBytes((UInt32)cmdParams.loadAddr    ).CopyTo(outImageData, 20);
      
      // Fill in binary data
      inImageData.CopyTo(outImageData, cmdParams.pageSize);
      
      // Write new file out to disk
      File.WriteAllBytes(cmdParams.outFileName,outImageData);
       
      // Everything worked, so change boolean status
      workerThreadSucceeded = true;
    }                
    #endregion 
    //**********************************************************************************
  }
}
