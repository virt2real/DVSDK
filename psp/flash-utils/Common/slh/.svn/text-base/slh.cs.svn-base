/* --------------------------------------------------------------------------
    FILE        : slh.cs
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
    DESC        : Host console app for serial loading
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
using UtilLib.ConsoleUtility;

[assembly: AssemblyTitle("SerialLoaderHost")]
[assembly: AssemblyVersion("1.50.*")]


namespace TIBootAndFlash
{
  /// <summary>
  /// Enumeration for Magic Flags that the UBL expects to see
  /// </summary>
  public enum MagicFlags : uint
  {
    MAGIC_NUMBER_VALID = 0xA1ACED00,
    MAGIC_NUMBER_INVALID = 0xFFFFFFFF,
    SLT_MAGIC_LOADIMAGE_IRAM = 0xA1ACED00,  // Download a UBL-like image to execute directly in IRAM
    SLT_MAGIC_LOADIMAGE_DDR = 0xA1ACEDEE	  // Download SLT and then load image to DDR via it
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
    /// Boolean to control the verbosity of output
    /// </summary>
    public Boolean verbose;
    
    /// <summary>
    /// Name of serial port used for communications
    /// </summary>
    public String SerialPortName;

    /// <summary>
    /// This should be transmitted alone in response to the BOOTPSP.
    /// </summary>
    public MagicFlags CMDMagicFlag;

    /// <summary>
    /// String containing filename of Application file
    /// </summary>
    public String APPFileName;

    /// <summary>
    /// Address where the app should be decoded to and 
    /// run from (if appropriate).
    /// </summary>
    public UInt32 APPLoadAddr;

    /// <summary>
    /// Address where the app begin execution 
    /// </summary>
    public UInt32 APPStartAddr;
  }
  
  struct UARTBOOT_Header
  {
    public UInt32      startAddr;
    public UInt32      loadAddr;
    public UInt32      byteCnt;
    public UInt32      crcVal;
  }
    
  /// <summary>
  /// Main program Class
  /// </summary>
  partial class Program
  {
    //**********************************************************************************
    #region Class variables and members

    /// <summary>
    /// Global main Serial Port Object
    /// </summary>
    public static SerialPort MySP;
            
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

    /// <summary>
    /// String to hold the summary of operation program will attempt.
    /// </summary>
    public static String cmdString;


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
      Console.Write("\n\tslh_"+devString+" <-load2IRAM | -load2DDR> [<Options> [<Optional Params>]] <Binary Image File>");
      Console.Write("\n\t\t" + "-load2IRAM\tLoad a small UBL-like image to IRAM.");
      Console.Write("\n\t\t" + "-load2DDR\tLoad a larger image to DDR.\n");
      Console.Write("\n\t" + "<Options> can be the following: " +
                    "\n\t\t" + "-startAddr <entry point address>\tSpecify entry point in hex." +
                    "\n\t\t" + "-loadAddr <image load address>  \tSpecify load address in hex. (only with load2DDR mode)" +
                    "\n\t\t" +"-h                               \tDisplay this help screen."+
                    "\n\t\t" +"-v                               \tDisplay more verbose output returned from the "+devString+"."+
                    "\n\t\t" +"-p <PortName>                    \tUse <PortName> as the serial port (e.g. COM2, /dev/ttyS1).\n\n");
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

      // Set Defualts for application
      myCmdParams.CMDMagicFlag = MagicFlags.MAGIC_NUMBER_INVALID;
      myCmdParams.valid = true;
      myCmdParams.verbose = false;
      myCmdParams.SerialPortName = null;

      myCmdParams.APPFileName = null;
      myCmdParams.APPLoadAddr = 0xFFFFFFFF;
      myCmdParams.APPStartAddr = 0xFFFFFFFF;
      
      // For loop for required load type
      for(int i = 0; i<args.Length; i++)
      {
        s = args[i];
        if (s.StartsWith("-"))
        {
          switch (s.Substring(1).ToLower())
          {
            case "load2iram":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.SLT_MAGIC_LOADIMAGE_IRAM;
              else
                myCmdParams.valid = false;
              myCmdParams.APPLoadAddr = 0x0020;
              myCmdParams.APPStartAddr = 0x0100;
              numFiles = 1;
              cmdString = "Loading image to ARM IRAM ";
              break;
            case "load2ddr":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.SLT_MAGIC_LOADIMAGE_DDR;
              else
                myCmdParams.valid = false;
              myCmdParams.APPLoadAddr = 0x80000000;
              myCmdParams.APPStartAddr = 0x80000000;
              numFiles = 1;
              cmdString = "Loading image to DDR";
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
      
      if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
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
            case "startaddr":
              if (args[i + 1].StartsWith("0x"))
                args[i + 1] = args[i + 1].Substring(2);
              myCmdParams.APPStartAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "loadaddr":
              if (args[i + 1].StartsWith("0x"))
                args[i + 1] = args[i + 1].Substring(2);
              myCmdParams.APPLoadAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
              argsHandled[i + 1] = true;
              numHandledArgs++;
              break;
            case "p":
              myCmdParams.SerialPortName = args[i + 1];
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
          if (!myCmdParams.valid)
            return myCmdParams;
        }
      } // end of for loop for handling dash params
     
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
              if (myCmdParams.APPFileName == null)
              {
                myCmdParams.APPFileName = args[i];
              }
              else
                myCmdParams.valid = false;
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
      
      //Setup default serial port name
      if (myCmdParams.SerialPortName == null)
      {
        int p = (int)Environment.OSVersion.Platform;
        if ((p == 4) || (p == 128)) //Check for unix/linux
        {
          Console.WriteLine("Platform is Unix/Linux.");
          myCmdParams.SerialPortName = "/dev/ttyS0";
        }
        else
        {
          Console.WriteLine("Platform is Windows.");
          myCmdParams.SerialPortName = "COM1";
        }
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
      Console.WriteLine("   TI Serial Loader Host Program for " + devString    );
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
      else
      {
        Console.Write(cmdString + "\n\n\n");
      }
                             
      try
      {
        Console.WriteLine("Attempting to connect to device " + cmdParams.SerialPortName + "...");
        MySP = new SerialPort(cmdParams.SerialPortName, 115200, Parity.None, 8, StopBits.One);
        MySP.Encoding = Encoding.ASCII;
        MySP.Open();
      }
      catch(Exception e)
      {
        if (e is UnauthorizedAccessException)
        {
          Console.WriteLine(e.Message);
          Console.WriteLine("This application failed to open the COM port.");
          Console.WriteLine("Most likely it is in use by some other application.");
          return -1;
        }
        Console.WriteLine(e.Message);
        return -1;
      }

      Console.WriteLine("Press any key to end this program at any time.\n");
      
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
        Console.WriteLine("\n\nInterfacing to the "+devString+" via UART failed." +
            "\nPlease reset or power-cycle the board and try again...");
        return -1;
      }
      
    }
    #endregion
    //**********************************************************************************
    

    //**********************************************************************************
    #region Code for UART interfacing thread

    /// <summary>
    /// The main function of the thread where all the cool stuff happens
    /// to interface with the device
    /// </summary>
    public static void WorkerThreadStart()
    {
      switch (cmdParams.CMDMagicFlag)
      {
        case MagicFlags.SLT_MAGIC_LOADIMAGE_IRAM:
        {
          TransmitAppToIRAM();
          break;
        }
        case MagicFlags.SLT_MAGIC_LOADIMAGE_DDR:
        {
          // Send SLT and the app to DDR
          TransmitSLTAndApp();
          
          // Wait for second ^^^DONE that indicates SLT is done
          if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
            throw new Exception("Final DONE not returned.  Operation failed.");
          
          break;
        }
        default:
        {
          Console.WriteLine("Command not recognized!");
          break;
        }
      }
      
      // Clean up any embedded files we extracted
      EmbeddedFileIO.CleanUpEmbeddedFiles();
       
      // Everything worked, so change boolean status
      workerThreadSucceeded = true;
    }

    /// <summary>
    /// Function to Transmit the UBL via the device ROM Serial boot
    /// </summary>
    private static void TransmitUBL(Byte[] imageData,UARTBOOT_Header ackHeader)
    {
      // Local Variables for building up output
      StringBuilder UBLsb;
      CRC32 MyCRC;
      ProgressBar progressBar;
      Int32 blockCnt;      

      UBLsb = new StringBuilder(imageData.Length * 2);
      
      // Read the data from the UBL file into the appropriate structures
      for (int i=0; i<imageData.Length; i+=sizeof(UInt32))
      {
        UBLsb.AppendFormat("{0:X8}", System.BitConverter.ToUInt32(imageData,i));
      }

      // Create CRC object and use it to calculate the UBL file's CRC
      // Note that this CRC is not quite the standard CRC-32 algorithm
      // commonly in use since the final register value is not XOR'd
      // with 0xFFFFFFFF.  As a result the CRC value returned here
      // will be the bitwise inverse of the standard CRC-32 value.
      MyCRC = new CRC32(0x04C11DB7, 0xFFFFFFFF, 0x00000000, true, 1, CRCType.ONESHOT, CRCCalcMethod.LUT);
      ackHeader.crcVal = MyCRC.CalculateCRC(imageData);
      ackHeader.byteCnt = (UInt32) imageData.Length;

      try
      {
      BOOTMESEQ:
        Console.WriteLine("\nWaiting for the "+devString+"...");

        // Wait for the device to send the ^BOOTME/0 sequence
        if (SerialIO.waitForSequence(" BOOTME\0", " BOOTME\0", MySP, cmdParams.verbose))
            Console.WriteLine("BOOTME commmand received. Returning ACK and header...");
        else
            goto BOOTMESEQ;

        // Output 28 Bytes for the ACK sequence and header
        // 8 bytes acknowledge sequence = "    ACK\0"
#if (DM35x_REVB || DM36x_REVA)
        MySP.Write("    ACK");
#else
        MySP.Write("    ACK\0");
#endif
        // 8 bytes of CRC data = ASCII string of 8 hex characters
        MySP.Write(ackHeader.crcVal.ToString("X8"));
        
        // 4 bytes of UBL data size = ASCII string of 4 hex characters (3800h = 14336d)
        MySP.Write(ackHeader.byteCnt.ToString("X4"));
        
        // 4 bytes of start address = ASCII string of 4 hex characters (>=0100h)
        MySP.Write(ackHeader.startAddr.ToString("X4"));
        
        // 4 bytes of constant zeros = "0000"
        MySP.Write("0000");
        Console.WriteLine("ACK command sent. Waiting for BEGIN command... ");

        // Wait for the BEGIN sequence
        if (SerialIO.waitForSequence("  BEGIN\0", " BOOTME\0", MySP,true))
            Console.WriteLine("BEGIN commmand received. Sending CRC table...");
        else
            goto BOOTMESEQ;

        // Send the 1024 byte (256 word) CRC table
        progressBar = new ProgressBar();
        progressBar.Update(0.0,"Sending CRC table...");
        for (int i = 0; i < MyCRC.Length; i++)
        {
            MySP.Write(MyCRC[i].ToString("x8"));
            progressBar.Percent = (((Double)(i+1))/MyCRC.Length);
        }
        progressBar.Update(100.0,"CRC table sent.");
        Console.WriteLine("Waiting for DONE...");

        // Wait for the first DONE sequence
        if (SerialIO.waitForSequence("   DONE\0", " BOOTME\0", MySP, cmdParams.verbose))
            Console.WriteLine("DONE received.  Sending the UBL...");
        else
            goto BOOTMESEQ;

        // Send the contents of the UBL file (as hex text)
        progressBar = new ProgressBar();
        progressBar.Update(0.0,"Sending UBL...");
        blockCnt = UBLsb.Length/128;
        for (int i = 0; i < (blockCnt*128); i+=128)
        {
          MySP.Write(UBLsb.ToString(i,128));
          progressBar.Percent = (((Double)(i+1))/UBLsb.Length);
        }
        // Write last (possibly partial) block
        MySP.Write(UBLsb.ToString(blockCnt*128,UBLsb.Length - (blockCnt*128) ));
        progressBar.Update(100.0,"UBL sent.");

        // Wait for the second DONE sequence
        if (SerialIO.waitForSequence("   DONE\0", " BOOTME\0", MySP, cmdParams.verbose))
            Console.WriteLine("DONE received.  UBL was accepted.");
        else
            goto BOOTMESEQ;

        Console.WriteLine("UBL transmitted successfully.\n");

      }
      catch (ObjectDisposedException e)
      {
        Console.WriteLine(e.StackTrace);
        throw e;
      }
    }

    /// <summary>
    /// Function to transmit the application code via the SLT, which is now 
    /// running on the device.  This code is specific to the supplied SLT.
    /// If the the TI supplied SLT is modified or a different boot loader is
    /// used, this code will need to be modified.
    /// </summary>
    private static Boolean TransmitImage(Byte[] imageData, UARTBOOT_Header ackHeader)
    {
      ProgressBar progressBar;
      UInt32 blockCnt;

      try
      {
        Console.WriteLine("Waiting for SENDIMG sequence...");
        if (!SerialIO.waitForSequence("SENDIMG\0", "BOOTUBL\0", MySP, cmdParams.verbose))
          return false;
          
        Console.WriteLine("SENDIMG received. Returning ACK and header for image data...");

        // Output 36 Bytes for the ACK sequence and header
        // 8 bytes acknowledge sequence = "    ACK\0"
        MySP.Write("    ACK\0");
        // 8 bytes of binary execution address = ASCII string of 8 hex characters
        MySP.Write(String.Format("{0:X8}", ackHeader.startAddr));
        // 8 bytes of data size = ASCII string of 8 hex characters
        MySP.Write(String.Format("{0:X8}", ackHeader.byteCnt));
        // 8 bytes of binary load address = ASCII string of 8 hex characters
        MySP.Write(String.Format("{0:X8}", ackHeader.loadAddr));
        // 4 bytes of constant zeros = "0000"
        MySP.Write("0000");

        Console.WriteLine("ACK command sent. Waiting for BEGIN command... ");

        // Wait for the ^^BEGIN\0 sequence
        if (!SerialIO.waitForSequence("  BEGIN\0", "BOOTUBL\0", MySP, cmdParams.verbose))
          return false;
        
        Console.WriteLine("BEGIN commmand received.");

        // Send the image data
        progressBar = new ProgressBar();
        progressBar.Update(0.0,"Sending Image data...");
        blockCnt = ackHeader.byteCnt/128;
        for (int i = 0; i < (blockCnt*128); i+=128)
        {
          MySP.Write(imageData, i, 128);
          progressBar.Percent = (((Double)(i+1))/ackHeader.byteCnt);
        }
        // Write last (possibly partial) block
        MySP.Write(imageData, (Int32) (blockCnt*128),(Int32) (ackHeader.byteCnt - (blockCnt*128)) );
        progressBar.Update(100.0,"Image data sent.");
        
        Console.WriteLine("Waiting for DONE...");

        // Wait for first ^^^DONE\0 to indicate data received
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, cmdParams.verbose))
          return false;
        
        Console.WriteLine("DONE received.  All bytes of image data received...");
      }
      catch (ObjectDisposedException e)
      {
        Console.WriteLine(e.StackTrace);
        throw e;
      }
      return true;
    }

    /// <summary>
    /// Function used to handle the -load2IRAM command-line option
    /// </summary>
    private static void TransmitAppToIRAM()
    {
      // Local Variables for holding file data
      Byte[] imageData;
      UARTBOOT_Header ackHeader = new UARTBOOT_Header();

      // Read the image data we will transmit
      imageData = FileIO.GetFileData(cmdParams.APPFileName);
      ackHeader.startAddr = cmdParams.APPStartAddr;
      ackHeader.loadAddr = 0x0020;    // Not used here, but this is the value used by the RBL
      ackHeader.byteCnt   = (UInt32) imageData.Length;

      TransmitUBL(imageData,ackHeader);
    }
    
    /// <summary>
    /// Function used to handle the -load2DDR command-line option
    private static void TransmitSLTAndApp()
    {
      // Local Variables for holding file data
      Byte[] imageData;
      UARTBOOT_Header ackHeader = new UARTBOOT_Header();
      
      // Extract the embedded SLT
      EmbeddedFileIO.ExtractFile(System.Reflection.Assembly.GetExecutingAssembly(), "slt_"+devString+".bin", true);
      
      // Read the extracted embedded SLT data that we will transmit
      imageData = FileIO.GetFileData("slt_"+devString+".bin");
      ackHeader.startAddr = 0x0100;   // Default for SLT
      ackHeader.byteCnt   = (UInt32) imageData.Length;
      ackHeader.loadAddr  = 0x0020;   // Not used here, but this what the RBL uses      
      TransmitUBL(imageData,ackHeader);
        
      // Sleep in case we need to abort
      Thread.Sleep(200);
        
      // Code to perform specified command
      try
      {
      BOOTUBLSEQ1:
        // Send the UBL command
        // Clear input buffer so we can start looking for BOOTUBL
        MySP.DiscardInBuffer();

        Console.WriteLine("\nWaiting for SLT on the "+devString+"...");
        
        // Wait for the UBL on the device to send the ^BOOTUBL\0 sequence
        if (!SerialIO.waitForSequence("BOOTUBL\0", "BOOTUBL\0", MySP, true))
          goto BOOTUBLSEQ1;
        
        Console.WriteLine("BOOTUBL commmand received. Returning CMD and command...");

        // 8 bytes acknowledge sequence = "    CMD\0"
        MySP.Write("    CMD\0");
        // 8 bytes of magic number
        MySP.Write(((UInt32)cmdParams.CMDMagicFlag).ToString("X8"));
        
        Console.WriteLine("CMD value sent.  Waiting for DONE...");
        
        // Wait for ^^^DONE letting us know the command was accepted
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, cmdParams.verbose))
          goto BOOTUBLSEQ1;
          
        Console.WriteLine("DONE received. Command was accepted.");
 
        // Local Variables for reading APP file
        imageData = FileIO.GetFileData(cmdParams.APPFileName);
        
        ackHeader.startAddr = cmdParams.APPStartAddr;          // App entry point
        ackHeader.loadAddr  = cmdParams.APPLoadAddr;            // App load address
        ackHeader.byteCnt   = (UInt32) imageData.Length;        // App byte cnt

        if (!TransmitImage(imageData,ackHeader))
          goto BOOTUBLSEQ1;
            
      }
      catch (Exception e)
      {
        if (e is ThreadAbortException)
        {
          Thread.Sleep(1000);
        }
        else
        {
          Console.WriteLine(e.Message);
        }
        return;
      }        
    }
                
    #endregion 
    //**********************************************************************************

    }
}
