/* --------------------------------------------------------------------------
    FILE        : sfh.cs
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
    DESC        : Host program for flashing via serial port
 ----------------------------------------------------------------------------- */

using System;
using System.Text;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Threading;
using System.Globalization;
using UtilLib;
using UtilLib.CRC;
using UtilLib.IO;
using UtilLib.ConsoleUtility;

[assembly: AssemblyTitle("SerialFlasherHost")]
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
    UBL_MAGIC_SAFE = 0xA1ACED00,
    UBL_MAGIC_DMA = 0xA1ACED11,	                   /* DMA boot mode */
    UBL_MAGIC_IC = 0xA1ACED22,	                   /* I Cache boot mode */
    UBL_MAGIC_FAST = 0xA1ACED33,	           /* Fast EMIF boot mode */
    UBL_MAGIC_DMA_IC = 0xA1ACED44,	           /* DMA + ICache boot mode */
    UBL_MAGIC_DMA_IC_FAST = 0xA1ACED55,	           /* DMA + ICache + Fast EMIF boot mode */
    UBL_MAGIC_BIN_IMG = 0xA1ACED66,                /* Describes the application image in Flash - indicates that it is binary*/
    UBL_MAGIC_SAFE_DM35x_REVC = 0xA1BCED00,
    UBL_MAGIC_DMA_DM35x_REVC = 0xA1BCED11,	   /* DMA boot mode */
    UBL_MAGIC_IC_DM35x_REVC = 0xA1BCED22,	   /* I Cache boot mode */
    UBL_MAGIC_FAST_DM35x_REVC = 0xA1BCED33,	   /* Fast EMIF boot mode */
    UBL_MAGIC_DMA_IC_DM35x_REVC = 0xA1BCED44,	   /* DMA + ICache boot mode */
    UBL_MAGIC_DMA_IC_FAST_DM35x_REVC = 0xA1BCED55, /* DMA + ICache + Fast EMIF boot mode */
    UBL_MAGIC_BIN_IMG_DM35x_REVC = 0xA1BCED66,     /* Describes the application image in Flash - indicates that it is binary*/
    UBL_MAGIC_NOR_FLASH_NO_UBL = 0xA1ACED77,       /* Download via UART & Burn NOR with u-boot only - legacy option */
    UBL_MAGIC_NOR_FLASH = 0xA1ACED99,              /* Download via UART & Burn NOR with UBL and U-boot */
    UBL_MAGIC_NOR_ERASE = 0xA1ACEDAA,              /* Download via UART & erase the NOR Flash */
    UBL_MAGIC_NAND_FLASH = 0xA1ACEDCC,             /* Download via UART & Flash NAND with UBL and U-boot */
    UBL_MAGIC_NAND_ERASE = 0xA1ACEDDD,	           /* Download via UART & erase the NAND Flash */
    UBL_MAGIC_SDMMC_FLASH = 0xA1ACEDEE,            /* Download via UART & Burn SD/MMC with UBL and U-boot */
    UBL_MAGIC_SDMMC_ERASE = 0xA1ACEDFF,            /* Download via UART erase the SD/MMC Flash */        
  };
    
  /// <summary>
  /// Enumeration of flash types
  /// </summary>
  public enum FlashType : uint
  {
    NONE,
    NOR,
    NAND,
    SD_MMC
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
    /// Baud Rate of serial port
    /// </summary>
    public Int32 SerialPortBaudRate;

    /// <summary>
    /// This should be transmitted alone in response to the BOOTUBL.
    /// </summary>
    public MagicFlags CMDMagicFlag;

    /// <summary>
    /// Type of flash that the application and UBL are targeted to use.  Selects
    /// which embedded UBL to use.
    /// </summary>
    public FlashType UBLFlashType;

    /// <summary>
    /// Global varibale to hold the desired magic flag
    /// </summary>
    public MagicFlags UBLMagicFlag;

    /// <summary>
    /// String containing filename of FLASH UBL file (only needed for flashing)
    /// </summary>
    public String UBLFileName;

    /// <summary>
    /// Address at which the Flash UBL will begin execution (must be 0x100 or greater)
    /// </summary>
    public UInt32 UBLStartAddr;

    /// <summary>
    /// Magic Flag for the application data
    /// </summary>
    public MagicFlags APPMagicFlag;

    /// <summary>
    /// String containing filename of Application file
    /// </summary>
    public String APPFileName;

    /// <summary>
    /// Start address of where the app image should be loaded
    /// </summary>
    public UInt32 APPLoadAddr;

    /// <summary>
    /// Address where the app begin execution 
    /// </summary>
    public UInt32 APPStartAddr;
  }
    
  struct UARTBOOT_Header
  {
    public UInt32 magicNum;      
    public UInt32 startAddr;
    public UInt32 loadAddr;
    public UInt32 byteCnt;
    public UInt32 crcVal;
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
      Console.Write("Usage:\n");
      Console.Write("\tsfh_"+devString+" < -norerase | -nanderase > [<Options>]\n");
      Console.Write("\t\t" + "-norerase\tDo a erase of the NOR flash.\n");
      Console.Write("\t\t" + "-nanderase\tDo a erase of the NAND flash.\n");
      Console.Write("\tsfh_"+devString+" -norflash_noubl [<Options>] <Application binary image>\n");
      Console.Write("\t\t" + "-norflash_noubl\tRestore NOR Flash with bootable application (typically U-Boot).\n");
      Console.Write("\tsfh_"+devString+" -norflash [<Options>] <UBL binary image> <Application binary image>\n");                
      Console.Write("\t\t" + "-norflash\tRestore the NOR Flash with bootable UBL and application (typically U-Boot).\n");                 
      Console.Write("\tsfh_"+devString+" -nandflash [<Options>] <UBL binary image> <Application binary image>\n");
      Console.Write("\t\t" + "-nandflash\tRestore the NAND Flash with bootable UBL and application (typically U-Boot).\n");                 
      Console.Write("\tsfh_"+devString+" -sdflash [<Options>] <UBL binary image> <Application binary image>\n");      
      Console.Write("\t\t" + "-sdflash\tRestore the SD/MMC Flash with bootable UBL and application (typically U-Boot).\n");            
      Console.Write("\n\t" + "<Options> can be the following: " +
                    "\n\t\t" + "-APPStartAddr <Application entry point address>\tSpecify in hex, defaults to 0x81080000." +
                    "\n\t\t" + "-APPLoadAddr <Application image load address>  \tSpecify in hex, defaults to 0x81080000." +      
                    "\n\t\t" + "-UBLStartAddr <UBL entry point address>        \tSpecify in hex, defaults to 0x0100 ." +                    
                    "\n\t\t" + "-h                \tDisplay this help screen."+
                    "\n\t\t" + "-v                \tDisplay more verbose output returned from the "+devString+"."+
                    "\n\t\t" + "-p \"<PortName>\" \tUse <PortName> as the serial port (e.g. COM2, /dev/ttyS1).\n\n");
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
      myCmdParams.UBLFlashType = FlashType.NONE;
      
      myCmdParams.CMDMagicFlag = MagicFlags.MAGIC_NUMBER_INVALID;
      myCmdParams.valid = true;
      myCmdParams.verbose = false;
      myCmdParams.SerialPortName = null;
      myCmdParams.SerialPortBaudRate = 115200;
      
      myCmdParams.APPMagicFlag = MagicFlags.UBL_MAGIC_SAFE;
      myCmdParams.APPFileName = null;
      myCmdParams.APPLoadAddr = 0xFFFFFFFF;
      myCmdParams.APPStartAddr = 0xFFFFFFFF;

#if   DM35X_STANDARD
      myCmdParams.UBLMagicFlag = MagicFlags.UBL_MAGIC_SAFE_DM35x_REVC;
#else
      myCmdParams.UBLMagicFlag = MagicFlags.UBL_MAGIC_SAFE;
#endif
      myCmdParams.UBLFileName = null;
      myCmdParams.UBLStartAddr = 0xFFFFFFFF;

      // For loop for required command type
      for(int i = 0; i<args.Length; i++)
      {
        s = args[i];
        if (s.StartsWith("-"))
        {
          switch (s.Substring(1).ToLower())
          {
            case "norflash":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.UBL_MAGIC_NOR_FLASH;
              else
                myCmdParams.valid = false;
              numFiles = 2;
              myCmdParams.UBLFlashType = FlashType.NOR;
              cmdString = "Flashing NOR with ";
              break;
            case "norflash_noubl":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.UBL_MAGIC_NOR_FLASH_NO_UBL;
              else
                myCmdParams.valid = false;
              numFiles = 1;
              myCmdParams.UBLFlashType = FlashType.NOR;
              cmdString = "Flashing NOR with ";
              break;
            case "sdflash":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.UBL_MAGIC_SDMMC_FLASH;
              else
                myCmdParams.valid = false;
              numFiles = 2;
              myCmdParams.UBLFlashType = FlashType.SD_MMC;
              cmdString = "Flashing SD/MMC with ";
              break;
            case "nandflash":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.UBL_MAGIC_NAND_FLASH;
              else
                myCmdParams.valid = false;
              numFiles = 2;
              myCmdParams.UBLFlashType = FlashType.NAND;
              cmdString = "Flashing NAND with ";
              break;
            case "norerase":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.UBL_MAGIC_NOR_ERASE;
              else
                myCmdParams.valid = false;
              numFiles = 0;
              myCmdParams.UBLFlashType = FlashType.NOR;
              cmdString = "Globally erasing NOR flash.";
              break;
            case "nanderase":
              if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
                myCmdParams.CMDMagicFlag = MagicFlags.UBL_MAGIC_NAND_ERASE;
              else
                myCmdParams.valid = false;
              numFiles = 0;
              myCmdParams.UBLFlashType = FlashType.NAND;
              cmdString = "Globally erasing NAND flash.";
              break;
            default:
              continue;
          }
          argsHandled[i] = true;
          numHandledArgs++;
          
          if (!myCmdParams.valid)
            return myCmdParams;
        }
      } // end of for loop for handling dash params
      
      // Check to make sure a command was selected
      if (myCmdParams.CMDMagicFlag == MagicFlags.MAGIC_NUMBER_INVALID)
      {
        myCmdParams.valid = false;
        return myCmdParams;
      }
      
      // For loop for all other dash options
      try
      {
        for(int i = 0; i<args.Length; i++)
        {
          s = args[i];
          if ((s.StartsWith("-")) && (argsHandled[i] != true))
          {
            switch (s.Substring(1).ToLower())
            {
              case "appstartaddr":
                if (args[i + 1].StartsWith("0x"))
                  args[i + 1] = args[i + 1].Substring(2);
                myCmdParams.APPStartAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
                argsHandled[i + 1] = true;
                numHandledArgs++;
                break;
              case "apploadaddr":
                if (args[i + 1].StartsWith("0x"))
                  args[i + 1] = args[i + 1].Substring(2);
                myCmdParams.APPLoadAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
                argsHandled[i + 1] = true;
                numHandledArgs++;
                break;
              case "ublstartaddr":
                if (args[i + 1].StartsWith("0x"))
                  args[i + 1] = args[i + 1].Substring(2);
                myCmdParams.UBLStartAddr = System.UInt32.Parse(args[i + 1],System.Globalization.NumberStyles.AllowHexSpecifier);
                argsHandled[i + 1] = true;
                numHandledArgs++;
                break;              
              case "p":
                myCmdParams.SerialPortName = args[i + 1];
                argsHandled[i + 1] = true;
                numHandledArgs++;
                break;
              case "baud":
                myCmdParams.SerialPortBaudRate = System.Int32.Parse(args[i + 1]);
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
      }
      catch(Exception e)
      {
        Console.WriteLine(e.Message);
        myCmdParams.valid = false;
        return myCmdParams;
      }
      
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
                cmdString += myCmdParams.APPFileName + ".";
              }
              else
                myCmdParams.valid = false;
              break;
            case 2:
              if (myCmdParams.UBLFileName == null)
              {
                myCmdParams.UBLFileName = args[i];
                cmdString += myCmdParams.UBLFileName + " and ";
              }
              else if (myCmdParams.APPFileName == null)
              {
                myCmdParams.APPFileName = args[i];
                cmdString += myCmdParams.APPFileName + ".";
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
        if (!myCmdParams.valid) 
          return myCmdParams;
      } // end of for loop for handling dash params
        
      // Set default binary execution address on target device
      if (myCmdParams.APPLoadAddr == 0xFFFFFFFF)
        myCmdParams.APPLoadAddr = 0x81080000;

      if (myCmdParams.APPStartAddr == 0xFFFFFFFF)
        myCmdParams.APPStartAddr = 0x81080000;
          
      if (myCmdParams.UBLStartAddr == 0xFFFFFFFF)
        myCmdParams.UBLStartAddr = 0x00000100;
      
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
      Console.WriteLine("   TI Serial Flasher Host Program for " + devString   );
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
        MySP = new SerialPort(cmdParams.SerialPortName, cmdParams.SerialPortBaudRate, Parity.None, 8, StopBits.One);
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
      Boolean status;
      // Try transmitting the first stage boot-loader (UBL) via the RBL
      try
      {      
        String srchStr;
        Byte[] imageData;
        UARTBOOT_Header ackHeader = new UARTBOOT_Header();
        
        if (cmdParams.UBLFlashType == FlashType.NAND)
          srchStr = "sft_"+devString+"_nand.bin";
        else
          srchStr = "sft_"+devString+"_nor.bin";
      
        // Extract the embedded SLT
        EmbeddedFileIO.ExtractFile(System.Reflection.Assembly.GetExecutingAssembly(), srchStr, true);
      
        // Read the extracted embedded SFT data that we will transmit
        imageData = FileIO.GetFileData(srchStr);
        ackHeader.startAddr = 0x0100;   // Default for SFT
        ackHeader.loadAddr  = 0x0020;   // Not used here, but this what the RBL uses
        ackHeader.byteCnt   = (UInt32) imageData.Length;
      
        TransmitUBL(imageData,ackHeader);
            
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

      // Sleep in case we need to abort
      Thread.Sleep(200);
        
      // Code to perform specified command
      try
      {

      BOOTUBLSEQ1:
        // Clear input buffer so we can start looking for BOOTUBL
        MySP.DiscardInBuffer();

        Console.WriteLine("\nWaiting for SFT on the "+devString+"...");
        
        // Wait for the SFT on the device to send the ^BOOTUBL\0 sequence
        if (!SerialIO.waitForSequence("BOOTUBL\0", "BOOTUBL\0", MySP, true))
          goto BOOTUBLSEQ1;
        
        Console.WriteLine("BOOTUBL commmand received. Returning CMD and command...");

        // 8 bytes acknowledge sequence = "    CMD\0"
        MySP.Write("    CMD\0");
        // 8 bytes of magic number
        MySP.Write(((UInt32)cmdParams.CMDMagicFlag).ToString("X8"));
        
        Console.WriteLine("CMD value sent.  Waiting for DONE...");
        
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
          goto BOOTUBLSEQ1;
        
        Console.WriteLine("DONE received. Command was accepted.");

        // Take appropriate action depending on command
        switch (cmdParams.CMDMagicFlag)
        {
          case MagicFlags.UBL_MAGIC_NAND_FLASH:
          {
            status = TransmitUBLandAPP();
            break;
          }
          case MagicFlags.UBL_MAGIC_NOR_FLASH:
          {
            status = TransmitUBLandAPP();
            break;
          }          
          case MagicFlags.UBL_MAGIC_NOR_FLASH_NO_UBL:
          {
            status = TransmitAPP();
            break;
          }
          case MagicFlags.UBL_MAGIC_NOR_ERASE:
          {
            status = TransmitErase();
            break;
          }
          case MagicFlags.UBL_MAGIC_NAND_ERASE:
          {
            status = TransmitErase();
            break;
          }
          default:
          {
            Console.WriteLine("Command not recognized!");
            status = false;
            break;
          }
        }
        if (!status)
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
        
      // Wait for ^^^DONE that indicates SFT is exiting and so can this host program
      if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
        throw new Exception("Final DONE not returned.  Operation failed.");
        
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
//#if (DM35x_REVB || DM36x_REVA)
//#if (DM35x_REVB)
//	MySP.Write("    ACK");
//#else
        MySP.Write("    ACK\0");
//#endif        
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
        // 8 bytes of magic number
        MySP.Write(String.Format("{0:X8}", ackHeader.magicNum));
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
    /// Send command and wait for erase response. (NOR and NAND global erase)
    /// </summary>
    private static Boolean TransmitErase()
    {
      try
      {
        // ^^^DONE\0 that indicates command was executed successfully
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
          return false;

      }
      catch (ObjectDisposedException e)
      {
        Console.WriteLine(e.StackTrace);
        throw e;
      }
      return true;
    }
    
    /// <summary>
    /// Function to transmit the UBL and application for flash
    /// </summary>
    private static Boolean TransmitAPP()
    {         
      Byte[] imageData;
      UARTBOOT_Header ackHeader = new UARTBOOT_Header();

      try
      {          
        // Now Send the application image that will be written to flash
        Console.WriteLine("Sending the Application image");
        imageData = FileIO.GetFileData(cmdParams.APPFileName);
        ackHeader.magicNum = ((UInt32)MagicFlags.UBL_MAGIC_BIN_IMG);
        ackHeader.startAddr = cmdParams.APPStartAddr;
        ackHeader.byteCnt = (UInt32) imageData.Length;
        ackHeader.loadAddr = cmdParams.APPLoadAddr;
        
        if (!TransmitImage(imageData, ackHeader))
          return false;
        
        // ^^^DONE\0 that indicates that application flashing is complete
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
          return false;
          
        return true;
      }
      catch (ObjectDisposedException e)
      {
        Console.WriteLine(e.StackTrace);
        throw e;
      }
    }
      

    /// <summary>
    /// Function to transmit the UBL and application for flash
    /// </summary>
    private static Boolean TransmitUBLandAPP()
    {         
      Byte[] imageData;
      UARTBOOT_Header ackHeader = new UARTBOOT_Header();

      try
      {   
        // First send the UBL image that will be written to flash\
        Console.WriteLine("Sending the UBL image");
        imageData = FileIO.GetFileData(cmdParams.UBLFileName);
        ackHeader.magicNum = (UInt32)cmdParams.UBLMagicFlag;
        ackHeader.startAddr = cmdParams.UBLStartAddr;
        ackHeader.byteCnt = (UInt32) imageData.Length;
        ackHeader.loadAddr = 0x0020;    // Not used here, but this is what RBL assumes
        
        // Actually transmit the data
        if (!TransmitImage(imageData, ackHeader))
          return false;
        
        // ^^^DONE\0 that indicates that UBL flashing is complete
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
          return false;
        
        // Now Send the application image that will be written to flash
        Console.WriteLine("Sending the Application image");
        imageData = FileIO.GetFileData(cmdParams.APPFileName);
        ackHeader.magicNum = ((UInt32)MagicFlags.UBL_MAGIC_BIN_IMG);
        ackHeader.startAddr = cmdParams.APPStartAddr;
        ackHeader.byteCnt = (UInt32) imageData.Length;
        ackHeader.loadAddr = cmdParams.APPLoadAddr;
        
        if (!TransmitImage(imageData, ackHeader))
          return false;
        
        // ^^^DONE\0 that indicates that application flashing is complete
        if (!SerialIO.waitForSequence("   DONE\0", "BOOTUBL\0", MySP, true))
          return false;
          
        return true;
      }
      catch (ObjectDisposedException e)
      {
        Console.WriteLine(e.StackTrace);
        throw e;
      }
    }
    
    #endregion 
    //**********************************************************************************

  }
}
