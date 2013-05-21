/****************************************************************
 *  TI Secure Extension to Abstract AISGen Class
 *  (C) 2008, Texas Instruments, Inc.                           
 ****************************************************************/

using System;
using System.Text;
using System.Text.RegularExpressions;
using System.Security.Cryptography;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Threading;
using System.Globalization;
using System.Collections;
using System.Collections.Generic;
using UtilLib;
using UtilLib.IO;
using UtilLib.CRC;
using UtilLib.Crypto;

namespace AISGenLib
{
  public enum SecureType:int
  {
    NONE    = 0x0,
    CUSTOM  = 0x1,
    GENERIC = 0x2
  }
  
  public enum BootLoaderExitType : int
  {
    NONSECURE     = 0x0,
    SECUREWITHSK  = 0x1,
    SECURENOSK    = 0x2,
    NONE          = 0x3
  }
  
  public enum SHA_Algorithm : int
  {
    SHA1 = 0x0,
    SHA256 = 0x1,
    SHA384 = 0x2,
    SHA512 = 0x3
  }
  
  public enum SecureLoadMagic : uint
  {
    // Load module magic ID
    LOADMOD_MAGIC   = 0x70ADC0DE,
    // Key certificate magic ID
    CERT_MAGIC      = 0x70ADCE87,
    // Generic user key magic ID
    GENKEY_MAGIC    = 0xBE40C0DE
  }
  
  public enum SecureLegacyMagic : uint
  {
    // Signed only
    SIGNMOD_MAGIC   = 0x5194C0DE,
    // Signed and Encrypted with CEK
    ENCMOD_MAGIC    = 0x034CC0DE
  }
  
  
  public class SecureBinaryFile:BinaryFile
  {
    public Boolean encrypt;
  }
  
  public class SecureObjectFile:ObjectFile
  {
    public Boolean encrypt;
  }
  
  /// <summary>
  /// Public abstract class (with static parts) to handle generic activities
  /// for device specific AISGen objects.
  /// </summary>
  public abstract partial class AISGen
  {
    // Private security type variable
    private SecureType secureTypeValue;
    
    // Private boot loader exit type
    private BootLoaderExitType bootLoaderExitTypeValue;
  
    // Public property for secure type
    public SecureType secureType
    {
      get { return secureTypeValue; }
      set
      {
        secureTypeValue = value;
      }
    }
    
    //
    public BootLoaderExitType bootLoaderExitType
    {
      get { return bootLoaderExitTypeValue; }
      set 
      {
        bootLoaderExitTypeValue = value;
      }
    }
    
    public Stream signatureStream;
    
    // Encryption Key
    public Byte[] customerEncryptionKey;
    public Byte[] CEKInitialValue;
    public Byte[] keyEncryptionKey;
    public Byte[] genericKeyHeaderData;

    // RSA Object
    public RSACryptoServiceProvider rsaObject;
    
    // Encrypted Section List
    public String[] sectionsToEncrypt;
	
    // Debug info for keeping track of signatures
    public int signatureByteCnt;
    public int signatureCnt;
    
    // Variable for generic secure key header
    public Boolean genericJTAGForceOff;
    
    // Varibale for current selected Hash algorihtm
    public SHA_Algorithm currHashAlgorithmValue;
    public HashAlgorithm currHashAlgorithm;
    
    public Boolean secureLegacyEncryptImage;
    
    
    #region Secure AIS Generation methods

    /// <summary>
    /// SecureGenAIS command.
    /// </summary>
    /// <param name="coffFileName">File name of input .out file</param>
    /// <param name="bootMode">AISGen Object for the particular device</param>
    /// <returns>Bytes of the binary or AIS boot image</returns>
    public static Byte[] SecureGenAIS(String coffFileName,
                                      AISGen devAISGen,
                                      INISection[] iniSecs)
    {
      UInt32 busWidth = 8;
      UInt32 addrWidth = 16;
      UInt32 numTargetSections = 0;
      UInt32 numWords;
      UInt32 entryPoint = 0x00000000;
      Boolean seqReadEn = false;     // Not supported on all devices
      
      Byte[] secureKeyData = null;
      String currHashAlgorithmString = "SHA1";  // Default hash algorithm
            
      Hashtable UARTSendDONE_DataSection=null, UARTSendDONE_TextSection=null;
      
      // Hash tables to keep track of the input object and binary files
      List<SecureObjectFile> objectFiles = new List<SecureObjectFile>();
      List<SecureBinaryFile> binaryFiles = new List<SecureBinaryFile>();
                 
      // COFF file objects for the main application and the AIS extras executable
      COFFFile AISExtrasCF=null;
     
      // Set defaults
      devAISGen.secureType              = SecureType.NONE;
      devAISGen.bootLoaderExitType      = BootLoaderExitType.NONE;
      devAISGen.currHashAlgorithmValue  = SHA_Algorithm.SHA1;
      devAISGen.finalFxnName            = null;
      devAISGen.sectionsToEncrypt       = null;
      devAISGen.rsaObject               = null;
      devAISGen.customerEncryptionKey   = null;
      devAISGen.keyEncryptionKey        = null;
      devAISGen.genericKeyHeaderData    = null;
      devAISGen.currHashAlgorithm       = null;      
      devAISGen.signatureByteCnt        = 0;
      devAISGen.signatureCnt            = 0;
      // List to keep track of loadable sections and their occupied memory ranges
      devAISGen.sectionMemory = new List<MemoryRange>();      
      
      // Setup the binary writer to generate the temp AIS file
      devAISGen.devAISStream              = new MemoryStream();
      EndianBinaryWriter tempAIS_bw       = new EndianBinaryWriter( devAISGen.devAISStream, devAISGen.devEndian);
      
      // Setup the binary writer to store data for signing
      devAISGen.signatureStream           = new MemoryStream();                                                    
      EndianBinaryWriter sig_bw           = new EndianBinaryWriter( devAISGen.signatureStream, devAISGen.devEndian);

      #region INI Data parsing
      // Get data from the GENERAL INI Section
      for (UInt32 i = 0; i < iniSecs.Length; i++)
      {
        INISection sec = iniSecs[i];
        if (sec.iniSectionName.Equals("GENERAL", StringComparison.OrdinalIgnoreCase))
        {
          foreach (DictionaryEntry de in sec.sectionValues)
          {
            // Read buswidth
            if (((String)de.Key).Equals("BUSWIDTH", StringComparison.OrdinalIgnoreCase))
              busWidth = (UInt32)sec.sectionValues["BUSWIDTH"];
            
            // Read BootMode (unless already set)
            if ((((String)de.Key).Equals("BOOTMODE", StringComparison.OrdinalIgnoreCase)) && (devAISGen.bootMode == BootModes.NONE))
              devAISGen.bootMode = (BootModes) Enum.Parse(typeof(BootModes), (String)sec.sectionValues["BOOTMODE"], true);

              // Read Addr width (for I2C/SPI)
            if (((String)de.Key).Equals("ADDRWIDTH", StringComparison.OrdinalIgnoreCase))
              addrWidth = (UInt32)sec.sectionValues["ADDRWIDTH"];
            
            // Sequential Read ENABLE
            if (((String)de.Key).Equals("SEQREADEN", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["SEQREADEN"]).Equals("ON", StringComparison.OrdinalIgnoreCase))
                seqReadEn = true;
              if (((String)sec.sectionValues["SEQREADEN"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                seqReadEn = true;
            }
            
            // Finalize fxn symbol name
            if (((String)de.Key).Equals("FINALFXNSYMBOLNAME", StringComparison.OrdinalIgnoreCase))
            {
              devAISGen.finalFxnName = (String)sec.sectionValues["FINALFXNSYMBOLNAME"];
            }
            
            // Read entrypoint value
            if (((String)de.Key).Equals("ENTRYPOINT", StringComparison.OrdinalIgnoreCase))
              entryPoint = (UInt32)sec.sectionValues["ENTRYPOINT"];            
          }
        }

        if (sec.iniSectionName.Equals("SECURITY", StringComparison.OrdinalIgnoreCase))
        {
          foreach (DictionaryEntry de in sec.sectionValues)
          {
            // Security Type
            if (((String)de.Key).Equals("SECURITYTYPE", StringComparison.OrdinalIgnoreCase))
            {
              devAISGen.secureType = (SecureType) Enum.Parse(typeof(SecureType), (String)sec.sectionValues["SECURITYTYPE"], true);
            }
            
            // Boot exit type
            if (((String)de.Key).Equals("BOOTEXITTYPE", StringComparison.OrdinalIgnoreCase))
            {
              devAISGen.bootLoaderExitType = (BootLoaderExitType) Enum.Parse(typeof(BootLoaderExitType), (String)sec.sectionValues["BOOTEXITTYPE"], true);
            }
            
            // Encrypted section settings
            if (((String)de.Key).Equals("ENCRYPTSECTIONS", StringComparison.OrdinalIgnoreCase))
            {
              Char[] separators = new Char[]{','};
              String encryptSections = (String)sec.sectionValues["ENCRYPTSECTIONS"];
              devAISGen.sectionsToEncrypt = encryptSections.Split(separators,StringSplitOptions.RemoveEmptyEntries);
              for( int k = 0; k<devAISGen.sectionsToEncrypt.Length; k++)
              {
                devAISGen.sectionsToEncrypt[k] = devAISGen.sectionsToEncrypt[k].Trim();
              }
            }
            
            // AES Encryption Key (CEK)
            if (((String)de.Key).Equals("ENCRYPTIONKEY", StringComparison.OrdinalIgnoreCase))
            {
              devAISGen.customerEncryptionKey = new Byte[16];
              devAISGen.CEKInitialValue = new Byte[16];
              String keyString = (String)sec.sectionValues["ENCRYPTIONKEY"];
              if (keyString.Length != 32)
              {
                Console.WriteLine("AES Encryption Key is wrong length!");
                return null;
              }
              for (int j=0; j<keyString.Length; j+=2)
              {
                devAISGen.customerEncryptionKey[(j>>1)] = Convert.ToByte(keyString.Substring(j,2),16);
              }
              
              // Generate IV as encrypted version of AES Key
              using (MemoryStream ms = new MemoryStream(devAISGen.CEKInitialValue))
              {
                Aes myAES = new AesManaged();
                myAES.KeySize = 128;
                myAES.Mode = CipherMode.ECB;
                myAES.Padding = PaddingMode.None;
                ICryptoTransform encryptor = myAES.CreateEncryptor(devAISGen.customerEncryptionKey, new Byte[16]);
                CryptoStream cs = new CryptoStream(ms,encryptor,CryptoStreamMode.Write);
                cs.Write(devAISGen.customerEncryptionKey,0,devAISGen.customerEncryptionKey.Length);
              }
              
              FileIO.SetFileData("cek.bin",devAISGen.customerEncryptionKey,true);
              FileIO.SetFileText("FROM_cek.init",KeyToBinaryString(devAISGen.customerEncryptionKey,0xA,true,true),true);
              FileIO.SetFileData("cek_cbc_iv.bin",devAISGen.CEKInitialValue,true);
            }
            
            // Key Encryption Key (not normally known, here for debug/testing purposes)
            if (((String)de.Key).Equals("KEYENCRYPTIONKEY", StringComparison.OrdinalIgnoreCase))
            {
              devAISGen.keyEncryptionKey = new Byte[16];
              String keyString = (String)sec.sectionValues["KEYENCRYPTIONKEY"];
              if (keyString.Length != 32)
              {
                Console.WriteLine("Key Encryption Key is wrong length!");
                return null;
              }
              for (int j=0; j<keyString.Length; j+=2)
              {
                devAISGen.keyEncryptionKey[(j>>1)] = Convert.ToByte(keyString.Substring(j,2),16);
              }
              
              FileIO.SetFileData("kek.bin",devAISGen.keyEncryptionKey,true);
              FileIO.SetFileText("FROM_kek.init",KeyToBinaryString(devAISGen.keyEncryptionKey,0xE,true,true),true);
            }
            
            // Generic Secure Option to force JTAG off as part of the key loading
            if (((String)de.Key).Equals("GENERICJTAGFORCEOFF", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["GENERICJTAGFORCEOFF"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                devAISGen.genericJTAGForceOff = true;
              else
                devAISGen.genericJTAGForceOff = false;
            }
            
            // Generic Secure Option to select the hash algorithm for signatures
            if (((String)de.Key).Equals("GENERICSHASELECTION", StringComparison.OrdinalIgnoreCase))
            {
              currHashAlgorithmString = (String)sec.sectionValues["GENERICSHASELECTION"];
              devAISGen.currHashAlgorithmValue = (SHA_Algorithm) Enum.Parse(typeof(SHA_Algorithm), (String)sec.sectionValues["GENERICSHASELECTION"], true);
            }
            
            // Generic Key Header file
            if (((String)de.Key).Equals("GENKEYHEADERFILENAME", StringComparison.OrdinalIgnoreCase))
            {
              String genKeyHeaderFileName = (String)sec.sectionValues["GENKEYHEADERFILENAME"];
              devAISGen.genericKeyHeaderData = new Byte[32];
              // Open file, read contents, copy to our AIS array
              using (FileStream tempFS = new FileStream(genKeyHeaderFileName, FileMode.Open, FileAccess.Read))
              {
                tempFS.Read(devAISGen.genericKeyHeaderData,0,32);
              }
            }
            
            // Custom Secure RSA Key File
            if (((String)de.Key).Equals("RSAKEYFILENAME", StringComparison.OrdinalIgnoreCase))
            {
              String rsaKeyFileName = (String)sec.sectionValues["RSAKEYFILENAME"];
              devAISGen.rsaObject = RSAKey.LoadFromFile(rsaKeyFileName);
              
              if (devAISGen.rsaObject == null)
              {
                Console.WriteLine("RSA key loading failed!");
                return null;
              }
              
              // Update the hash algo string if RSA key size is 2048 bits
              if (devAISGen.rsaObject.KeySize == 2048)
              {
                currHashAlgorithmString = "SHA256";
                devAISGen.currHashAlgorithmValue = SHA_Algorithm.SHA256;
              }
              Console.WriteLine("MapNameToOid({1}) = {0}",CryptoConfig.MapNameToOID(currHashAlgorithmString),currHashAlgorithmString);              
            }
          }
        }
        
        if (sec.iniSectionName.Equals("SECURELEGACY", StringComparison.OrdinalIgnoreCase))
        {
          foreach (DictionaryEntry de in sec.sectionValues)
          {        
            // Legacy secure option to encrypt the boot image
            if (((String)de.Key).Equals("ENCRYPTIMAGE", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["ENCRYPTIMAGE"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                devAISGen.secureLegacyEncryptImage = true;
              else
                devAISGen.secureLegacyEncryptImage = false;
            }
          }
          
          devAISGen.bootMode = BootModes.LEGACY;
        }
        
        if (sec.iniSectionName.Equals("BINARYINPUTFILE", StringComparison.OrdinalIgnoreCase))
        {
          SecureBinaryFile currFile = new SecureBinaryFile();
          currFile.fileName = null;
          currFile.useEntryPoint = false;
          currFile.loadAddr = 0x00000000;
          currFile.entryPointAddr = 0x00000000;
          currFile.encrypt = false;
          
          foreach (DictionaryEntry de in sec.sectionValues)
          {
                      
            // File name for binary section data
            if (((String)de.Key).Equals("FILENAME", StringComparison.OrdinalIgnoreCase))
            {
               currFile.fileName = (String) sec.sectionValues["FILENAME"];
            }
            
            // Binary section's load address in the memory map
            if (((String)de.Key).Equals("LOADADDRESS", StringComparison.OrdinalIgnoreCase))
            {
              currFile.loadAddr = (UInt32) sec.sectionValues["LOADADDRESS"];
            }
            
            // Binary section's entry point address in the memory map
            if (((String)de.Key).Equals("ENTRYPOINTADDRESS", StringComparison.OrdinalIgnoreCase))
            {
              currFile.entryPointAddr = (UInt32) sec.sectionValues["ENTRYPOINTADDRESS"];
            }
            
            // Option to specify that this entry point should be used for AIS
            if (((String)de.Key).Equals("USEENTRYPOINT", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["USEENTRYPOINT"]).Equals("YES", StringComparison.OrdinalIgnoreCase))
                currFile.useEntryPoint = true;
              if (((String)sec.sectionValues["USEENTRYPOINT"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                currFile.useEntryPoint = true;
            }
            
            // Option to specify that this entry point should be used for AIS
            if (((String)de.Key).Equals("ENCRYPT", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["ENCRYPT"]).Equals("YES", StringComparison.OrdinalIgnoreCase))
                currFile.encrypt = true;
              if (((String)sec.sectionValues["ENCRYPT"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                currFile.encrypt = true;
            }
          }
          
          if (currFile.fileName == null)
          {
            Console.WriteLine("ERROR: File name must be provided for binary input file.");
            return null;
          }

          if (currFile.loadAddr == 0x00000000)
          {
            Console.WriteLine("ERROR: Valid load address must be provided for binary input file.");
            return null;
          }

          binaryFiles.Add(currFile);
        }
        
        if (sec.iniSectionName.Equals("OBJECTINPUTFILE", StringComparison.OrdinalIgnoreCase))
        {
          SecureObjectFile currFile = new SecureObjectFile();
          currFile.useEntryPoint = false;
          currFile.fileName = null;
          currFile.encrypt = false;
          
          foreach (DictionaryEntry de in sec.sectionValues)
          {  
            // File name for binary section data
            if (((String)de.Key).Equals("FILENAME", StringComparison.OrdinalIgnoreCase))
            {
               currFile.fileName = (String) sec.sectionValues["FILENAME"];
            }
            
            // Option to specify that this entry point should be used for AIS
            if (((String)de.Key).Equals("USEENTRYPOINT", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["USEENTRYPOINT"]).Equals("YES", StringComparison.OrdinalIgnoreCase))
                currFile.useEntryPoint = true;
              if (((String)sec.sectionValues["USEENTRYPOINT"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                currFile.useEntryPoint = true;
            }
            
            // Option to specify that this entry point should be used for AIS
            if (((String)de.Key).Equals("ENCRYPT", StringComparison.OrdinalIgnoreCase))
            {
              if (((String)sec.sectionValues["ENCRYPT"]).Equals("YES", StringComparison.OrdinalIgnoreCase))
                currFile.encrypt = true;
              if (((String)sec.sectionValues["ENCRYPT"]).Equals("TRUE", StringComparison.OrdinalIgnoreCase))
                currFile.encrypt = true;
            }            
          }
          
          if (currFile.fileName == null)
          {
            Console.WriteLine("ERROR: File name must be provided for input object file.");
            return null; 
          }        
          
          objectFiles.Add(currFile);
        }
      }
      
      #endregion        

      
      #region INI data validation
      // INI Input Validation
      // 1) Make sure a secure type has been specified
      if (devAISGen.secureType == SecureType.NONE)
      {
        Console.WriteLine("ERROR: The device's security type was not specified!");
        return null;
      }
      else
      {
        Console.WriteLine("Creating boot image for a {0} secure device.",devAISGen.secureType.ToString().ToLower());
        // 2) Make sure we have a CEK and IV
        if (devAISGen.customerEncryptionKey == null)
        {
          Console.WriteLine("ERROR: No encryption key was specified!");
          return null;
        }
        
        // 3) If custom secure, make sure we have an rsaObject and CEK
        if ((devAISGen.secureType == SecureType.CUSTOM) && (devAISGen.rsaObject == null))
        {
          Console.WriteLine("ERROR: No RSA key file was specified!");
          return null;
        }
        
        // 3b) Make sure RSA key size is supported
        if ((devAISGen.secureType == SecureType.CUSTOM) && (devAISGen.rsaObject != null))
        {
          if ( (devAISGen.rsaObject.KeySize != 1024) && (devAISGen.rsaObject.KeySize != 2048) )
          {
            Console.WriteLine("ERROR: No RSA key size is invalid!");
            return null;
          }
          else
          {
            Console.WriteLine("INFO: RSA key is {0} bits.",devAISGen.rsaObject.KeySize);
          }
        }
        
        // 4) Specify Boot Exit type (if not legacy boot)
        if (devAISGen.bootMode != BootModes.LEGACY)
        {
          if (devAISGen.bootLoaderExitType == BootLoaderExitType.NONE)
          {
            Console.WriteLine("ERROR: No boot loader exit type was specified!");
            return null;
          }
          else
          {
            Console.WriteLine("INFO: Boot exit type has been selected as {0}.",devAISGen.bootLoaderExitType);
          }
        }
        // 5) If generic secure, make sure we have the CEK header info (either encrypted or unencrypted)
        if ((devAISGen.secureType == SecureType.GENERIC) && (devAISGen.genericKeyHeaderData == null))
        {
          Console.WriteLine("WARNING: Encrypted Key Header data is absent - generating plaintext version. ");
          Console.WriteLine("         The Customer Encryption Key will be transferred in plaintext!  ");
        }
        
        // 6) Give warning if generic device and no sections are specified for encryption
        if (devAISGen.bootMode != BootModes.LEGACY)
        {
          if ((devAISGen.secureType == SecureType.GENERIC) && (devAISGen.sectionsToEncrypt == null))
          {
            Console.WriteLine("WARNING: Generic Secure device was specified, but no input sections were indicated for encryption.");
            Console.WriteLine("         Only boot image signing will take place.");
          }
        }
      }

      // 2) Make sure valid hash algorithm was selected      
      try
      {
        devAISGen.currHashAlgorithm = HashAlgorithm.Create(currHashAlgorithmString);
        Console.WriteLine("INFO: Current SHA algorithm is {0}.",devAISGen.currHashAlgorithmValue);
      }
      catch (Exception e)
      {
        Console.WriteLine("Invalid Hash Algorithm Selected. Exception message: {0}.",e.Message);
        return null;
      }
      
      #endregion
      
      
      #region Secure Key Structure and Data preparation
      
      if ( devAISGen.secureType == SecureType.GENERIC )
      {
        if ((devAISGen.genericKeyHeaderData != null) && (devAISGen.genericKeyHeaderData.Length >= 32))
        {
          // Create our own key header
          secureKeyData = new Byte[32];
          Array.Copy(devAISGen.genericKeyHeaderData,0,secureKeyData,0,32);
        }
        else
        {
          // Create our own key header
          secureKeyData = new Byte[32];
          
          // Init with Random Data
          (new Random()).NextBytes(secureKeyData);
                    
          // Copy in the magic word for the generic key header structure
          BitConverter.GetBytes((UInt32)SecureLoadMagic.GENKEY_MAGIC).CopyTo(secureKeyData, 0);
          
          // Insert JTAGForceOff word
          BitConverter.GetBytes( (UInt32) (devAISGen.genericJTAGForceOff ? 0x00000001 : 0x00000000) ).CopyTo(secureKeyData, 4);
          
          // Inset Hash algorithm selection word (right now default to SHA-1
          BitConverter.GetBytes( (UInt32)devAISGen.currHashAlgorithmValue ).CopyTo(secureKeyData, 8);
          
          // Insert key Data (at offset 16)
          devAISGen.customerEncryptionKey.CopyTo(secureKeyData, 16);
          
          // FIXME: For debug write the data out to file
          FileIO.SetFileData("gen_keyhdr_unencrypted.bin",secureKeyData,true);
          
          // FIXME: Debug to write out the encrypted CEK structure (encrypted with KEK, using KEK encrypted KEK as IV)
          if (devAISGen.keyEncryptionKey != null)
          {
            Byte[] iv = new Byte[16];
            using (MemoryStream ms = new MemoryStream(iv))
            {
              Aes myAES = new AesManaged();
              myAES.KeySize = 128;
              myAES.Mode = CipherMode.ECB;
              myAES.Padding = PaddingMode.None;
              ICryptoTransform encryptor = myAES.CreateEncryptor(devAISGen.keyEncryptionKey, new Byte[16]);
              CryptoStream cs = new CryptoStream(ms,encryptor,CryptoStreamMode.Write);
              cs.Write(devAISGen.keyEncryptionKey,0,devAISGen.keyEncryptionKey.Length);
            }
            
            Byte[] encSecureKeyData = new Byte[32];
            using (MemoryStream ms = new MemoryStream(encSecureKeyData))
            {
              Aes myAES = new AesManaged();
              myAES.KeySize = 128;
              myAES.Mode = CipherMode.CBC;
              myAES.Padding = PaddingMode.None;
              ICryptoTransform encryptor = myAES.CreateEncryptor(devAISGen.keyEncryptionKey, iv);
              CryptoStream cs = new CryptoStream(ms,encryptor,CryptoStreamMode.Write);
              cs.Write(secureKeyData,0,secureKeyData.Length);
            }
            
            // FIXME: For debug write the data out to file
            FileIO.SetFileData("gen_keyhdr_encrypted.bin",encSecureKeyData,true);
          }
          
        }
      }
      else if ( devAISGen.secureType == SecureType.CUSTOM )
      {
        // Create RPK Verify Struct
        secureKeyData = RSAKey.CreateCustomSecureKeyVerifyStruct(devAISGen.rsaObject);
        FileIO.SetFileData("rpk_struct.bin",secureKeyData,true);
       
        // Calculate the SHA hash of the Root Public Key
        Byte[] digest = devAISGen.currHashAlgorithm.ComputeHash(secureKeyData);
        
      #if (!OLD_MPK_METHOD)
        for (int i=16;i<digest.Length;i++)
        {
          digest[i-16] ^= digest[i];
        }
      #endif
        
        // Write the expected MPK (hash of RPK structure truncated to 128 bits) in binary format to file mpk.bin
        Byte[] mpk = new Byte[16];
        Array.Copy(digest,0,mpk,0,16);
        FileIO.SetFileData("mpk.bin",mpk,true);
        FileIO.SetFileText("FROM_mpk.init",KeyToBinaryString(mpk,0x12,false,true),true);
      }
            
      #endregion


      #region Handle the case of Legacy boot mode
      
      if (devAISGen.bootMode == BootModes.LEGACY)
      {
        UInt32 fileSize = 0, secureDataSize = 0, totalImgSize = 0, paddingSize = 0;
        UInt32 loadAddr = 0;
        Byte[] fileData;
        
        // Validate an input binary file was given in the INI file
        if (binaryFiles.Count == 0)
        {
          Console.WriteLine("ERROR: You did not supply a binary file section in the INI file!");
          return null;
        }
        if (binaryFiles.Count > 1)
        {
          Console.WriteLine("WARNING: You supplied too many biinary file sections in the INI file.");
          Console.WriteLine("         Only using the first one.");
        }
        
        // Set load addr to start of L2 for legacy boot mode
        loadAddr = devAISGen.Cache[0].startAddr + 0x10;
        
        // Figure out the size of the secure data region (signature + keystruct)
        if (devAISGen.secureType == SecureType.CUSTOM)
        {
          // On custom secure we have rsa keySize bits for signature and modulus of key struct, 
          // plus eight additional bytes from key struct
          secureDataSize = (UInt32) (8 + (devAISGen.rsaObject.KeySize >> 3) + (devAISGen.rsaObject.KeySize >> 3));
        }
        else if (devAISGen.secureType == SecureType.GENERIC)
        {
          // On generic secure we have 32 for key and HashSize bits rounded up to nearst 16 bytes
          // for signature data.
          secureDataSize = (UInt32) (32 + ((((devAISGen.currHashAlgorithm.HashSize >> 3)+15)>>4)<<4));
        }

        // Verify legacy input binary file exists, and get data if it does
        if (File.Exists(binaryFiles[0].fileName))
        {
          Byte[] tempFileData = FileIO.GetFileData(binaryFiles[0].fileName);
          
          fileSize = (UInt32) tempFileData.Length;
          
          totalImgSize = 16 + fileSize + secureDataSize;
                
          if (totalImgSize > 16*1024)
          {
            Console.WriteLine("The input image is too large.  Reduce its size by {0} bytes.", (totalImgSize - (16*1024)));
            return null;
          }
          
          // Figure out how much to pad input file region to acheive complete image ending on 1K boundary
          paddingSize = (((totalImgSize+1023) >> 10) << 10) - totalImgSize;

          // Copy to final data array of fileSize
          fileSize = fileSize + paddingSize;
          fileData = new Byte[fileSize];
          tempFileData.CopyTo(fileData,0);
          
          // Adjust total image size to final amount
          totalImgSize = 16 + fileSize + secureDataSize;
        }
        else
        {
          Console.WriteLine("Error: Binary file was not found!");
          return null;
        }
        
        if ( ((binaryFiles[0].entryPointAddr & 0x00FFFFFF) < loadAddr) ||
             ((binaryFiles[0].entryPointAddr & 0x00FFFFFF) > (loadAddr+fileSize)) )
        {
          Console.WriteLine("ERROR: Entry point falls outside load image region.");
          return null;
        }
      
        // Place header 
        // Config Word - indicates total image size, nor width (if applicable)
        if (busWidth == 16)
        {
          tempAIS_bw.Write((UInt32)(((((totalImgSize >> 10)-1) & 0xF) << 8)|(0x1 << 0)|(0x0 << 4)));
          sig_bw.Write((UInt32)(((((totalImgSize >> 10)-1) & 0xF) << 8)|(0x1 << 0)|(0x0 << 4)));
        }
        else
        {
          tempAIS_bw.Write((UInt32)(((((totalImgSize >> 10)-1) & 0xF) << 8)|(0x0 << 0)|(0x0 << 4)));
          sig_bw.Write((UInt32)(((((totalImgSize >> 10)-1) & 0xF) << 8)|(0x0 << 0)|(0x0 << 4)));
        }
        devAISGen.signatureByteCnt += 4;

        // Magic Number   - indicates signed or encrypted
        if (devAISGen.secureLegacyEncryptImage)
        {
          tempAIS_bw.Write((UInt32)SecureLegacyMagic.ENCMOD_MAGIC);
          sig_bw.Write((UInt32)SecureLegacyMagic.ENCMOD_MAGIC);
        }
        else
        {
          tempAIS_bw.Write((UInt32)SecureLegacyMagic.SIGNMOD_MAGIC);
          sig_bw.Write((UInt32)SecureLegacyMagic.SIGNMOD_MAGIC);
        }
        devAISGen.signatureByteCnt += 4;
        
        // Entry Point    - where to jump within the image upon load     
        tempAIS_bw.Write( (UInt32)binaryFiles[0].entryPointAddr );
        sig_bw.Write( (UInt32)binaryFiles[0].entryPointAddr );
        devAISGen.signatureByteCnt += 4;
        
        // SecureDataSize - size of data following image for key struct & signature
        tempAIS_bw.Write( (UInt32)secureDataSize );
        sig_bw.Write( (UInt32)secureDataSize );
        
        // Now place padded binary contents      
        if (!devAISGen.secureLegacyEncryptImage)
        {
          // Non-encrypted section
          tempAIS_bw.Write(fileData);
          sig_bw.Write(fileData);
        }
        else
        {
          // Encrypted section
          // Write unencrypted data to the signature buffer
          sig_bw.Write(fileData);
                    
          // Encrypt data using CBC algorithm
          try
          {
            Byte[] encData = AesManagedUtil.AesCTSEncrypt(fileData,devAISGen.customerEncryptionKey,devAISGen.CEKInitialValue);
            
            // Write encrypted section data out to AIS data stream
            tempAIS_bw.Write(encData);
          }
          catch(Exception e)
          {
            Console.WriteLine("Exception during encryption operation: {0}",e.Message);
          }
        }
        devAISGen.signatureByteCnt += (Int32) fileSize;
        
        // Now place the key data
        tempAIS_bw.Write(secureKeyData);
        sig_bw.Write(secureKeyData);
        devAISGen.signatureByteCnt += secureKeyData.Length;
        
        // Finally place the signature which covers the entire image
        SecureAISInsertSignature(devAISGen.signatureStream, devAISGen);
        
        // Flush the data and then return to start
        devAISGen.devAISStream.Flush();
        devAISGen.devAISStream.Seek(0,SeekOrigin.Begin);
        
        devAISGen.signatureStream.Close();
        
      }   
      #endregion

      
      #region AIS Generation
      else
      {
        // ---------------------------------------------------------
        // ****************** BEGIN AIS GENERATION *****************
        // ---------------------------------------------------------
        Console.WriteLine("Begining the AIS file generation.");
        
        // Diaplay currently selected boot mode
        Console.WriteLine("AIS file being generated for bootmode: {0}.",Enum.GetName(typeof(BootModes),devAISGen.bootMode));
        
        #region AIS Extras and UARTSendDONE Setup
        //Create the COFF file object for the AISExtras file (if it exists/is defined)
        if (devAISGen.AISExtraFileName != null)
        {
          EmbeddedFileIO.ExtractFile(Assembly.GetExecutingAssembly(), devAISGen.AISExtraFileName, false);

          if (File.Exists(devAISGen.AISExtraFileName))
          {
            // The file exists, so use it
            AISExtrasCF = new COFFFile(devAISGen.AISExtraFileName);
          }
          else
          {
            throw new FileNotFoundException("The AISExtra file, " + devAISGen.AISExtraFileName + ", was not found.");
          }
        }

        // If we have the AISExtras COFF file object, use it to setup the addresses
        // for the AISExtra functions.  These will utilize the L1P and L1D spaces that
        // are usually cache.
        if ( (AISExtrasCF != null) && (devAISGen.AISExtraFunc != null))
        {
          // Use symbols to get address for AISExtra functions and parameters
          for (Int32 i = 0; i < devAISGen.AISExtraFunc.Length; i++)
          {
            Hashtable sym = AISExtrasCF.symFind("_" + devAISGen.AISExtraFunc[i].funcName);
            devAISGen.AISExtraFunc[i].funcAddr = (UInt32)sym["value"];
            sym = AISExtrasCF.symFind(".params");
            devAISGen.AISExtraFunc[i].paramAddr = (UInt32)sym["value"];
          }

          // If the bootMode is UART we need the UARTSendDONE function
          if (devAISGen.bootMode == BootModes.UART)
          {
            // Set address for the UARTSendDone Function in the .text:uart section
            UARTSendDONE_TextSection = AISExtrasCF.secFind(".text:uart");
            UARTSendDONE_DataSection = AISExtrasCF.secFind(".data:uart");
            
            // Eliminate these as loadable since they will be loaded first, separate
            // from the main COFF file
            UARTSendDONE_TextSection["copyToTarget"] = false;
            UARTSendDONE_DataSection["copyToTarget"] = false;
            AISExtrasCF.Header["numTargetSections"] = ((UInt32)AISExtrasCF.Header["numTargetSections"] - (UInt32)2);
            
            // Set the actual run address for the UARTSendDONE function
            if ((UARTSendDONE_TextSection != null) && (UARTSendDONE_DataSection != null))
            {
              Debug.DebugMSG("UART section found");
              devAISGen.UARTSendDONEAddr = (UInt32)UARTSendDONE_TextSection["phyAddr"];
              Hashtable sym = AISExtrasCF.symFind("_UARTSendDONE");
              if (sym != null)
              {
                devAISGen.UARTSendDONEAddr = (UInt32)sym["value"];
                Debug.DebugMSG("UARTSendDONE at 0x{0:X8}",devAISGen.UARTSendDONEAddr);
              }
            }
            else
            {
              Console.WriteLine("UARTSendDONE function not found in AISExtra COFF file!!!");
              return null;
            }
          }
        }

        // Setup boolean indicating whether to include UARTSendDONE jump commands
        if ((devAISGen.bootMode == BootModes.UART) && (devAISGen.UARTSendDONEAddr != 0x0))
            devAISGen.SendUARTSendDONE = true;
        else
            devAISGen.SendUARTSendDONE = false;

        #endregion
              

        #region Write AIS MAGIC Number and initial data
        // Write the premilinary header and fields (everything before first AIS command)
        switch (devAISGen.bootMode)
        {
          case BootModes.EMIFA:
          {
            if (busWidth == 16)
              tempAIS_bw.Write((UInt32)(0x1 << 0)|(0x2 << 4));
            else
              tempAIS_bw.Write((UInt32)(0x0 << 0)|(0x2 << 4));
            tempAIS_bw.Write((UInt32)AIS.MagicNumber);
            break;
          }
          case BootModes.NAND:
          {
            tempAIS_bw.Write((UInt32)AIS.MagicNumber);
            tempAIS_bw.Write((UInt32)0);
            tempAIS_bw.Write((UInt32)0);
            tempAIS_bw.Write((UInt32)0);
            break;
          }
          case BootModes.UART:
          {
            tempAIS_bw.Write((UInt32)AIS.MagicNumber);
            break;
          }
          case BootModes.I2CMASTER:
          {
            if (addrWidth == 16)
              tempAIS_bw.Write((UInt32)2);
            else
              tempAIS_bw.Write((UInt32)1);
            tempAIS_bw.Write((UInt32)AIS.MagicNumber);
            break;
          }
          case BootModes.SPIMASTER:
          {
            if (addrWidth == 24)
              tempAIS_bw.Write((UInt32)3);
            else if (addrWidth == 16)
              tempAIS_bw.Write((UInt32)2);
            else
              tempAIS_bw.Write((UInt32)1);
            tempAIS_bw.Write((UInt32)AIS.MagicNumber);
            break;
          }
          default:
          {
            tempAIS_bw.Write((UInt32)AIS.MagicNumber);
            break;
          }
        };
        
        // Add the AIS magic number to signature buffer
        if ( devAISGen.secureType != SecureType.NONE )
        {
          sig_bw.Write((UInt32)AIS.MagicNumber);
          devAISGen.signatureByteCnt += 4;
        }
        #endregion


        #region Send Secure Key Load command and data
        tempAIS_bw.Write((UInt32)AIS.SecureKeyLoad);
        sig_bw.Write((UInt32)AIS.SecureKeyLoad);
        devAISGen.signatureByteCnt += 4;
        
        tempAIS_bw.Write(secureKeyData);
        sig_bw.Write(secureKeyData);
        devAISGen.signatureByteCnt += secureKeyData.Length;
        #endregion


        #region Send the exit mode type
        if ( devAISGen.secureType != SecureType.NONE )
        {
          // Write AIS opcode
          tempAIS_bw.Write((UInt32)AIS.SetSecExitMode);
          sig_bw.Write((UInt32)AIS.SetSecExitMode);
  		        
          // Write exit type
          tempAIS_bw.Write((UInt32)devAISGen.bootLoaderExitType);
          sig_bw.Write((UInt32)devAISGen.bootLoaderExitType);

          devAISGen.signatureByteCnt += 8;
        }
        #endregion


        #region Send UARTSendDONE sections
        // Send UART code if it exists
        if (devAISGen.SendUARTSendDONE)
        {
          CRCCheckType tempCRCType = devAISGen.crcType;
          devAISGen.crcType = CRCCheckType.NO_CRC;
          devAISGen.SendUARTSendDONE = false;
          SecureAISSectionLoad(AISExtrasCF, UARTSendDONE_TextSection, devAISGen, false);
          SecureAISSectionLoad(AISExtrasCF, UARTSendDONE_DataSection, devAISGen, false);
          devAISGen.SendUARTSendDONE = true;
          devAISGen.crcType = tempCRCType;
        }
        #endregion


        #region ROM Function insertion

        // Insert words for ROM function execution
        for (UInt32 i = 0; i < devAISGen.ROMFunc.Length; i++)
        {
          for (UInt32 j = 0; j < iniSecs.Length; j++)
          {
            if (iniSecs[j].iniSectionName.Equals(devAISGen.ROMFunc[i].iniSectionName))
            {
              UInt32 funcIndex = i;
                                      
              tempAIS_bw.Write((UInt32)AIS.FunctionExec);
              sig_bw.Write((UInt32)AIS.FunctionExec);
              devAISGen.signatureByteCnt += 4;
  			
              tempAIS_bw.Write((((UInt32)devAISGen.ROMFunc[i].numParams) << 16) + ((UInt32)funcIndex));
              sig_bw.Write((((UInt32)devAISGen.ROMFunc[i].numParams) << 16) + ((UInt32)funcIndex));
              devAISGen.signatureByteCnt += 4;
  			
              // Write Paramter values read from INI file
              for (Int32 k = 0; k < devAISGen.ROMFunc[i].numParams; k++)
              {
                //FIXME
                Debug.DebugMSG("\tParam name: {0}, Param num: {1}, Value: {2}\n",
                  devAISGen.ROMFunc[i].paramNames[k],
                  k, 
                  iniSecs[j].sectionValues[devAISGen.ROMFunc[i].paramNames[k].ToUpper()]);
                tempAIS_bw.Write((UInt32)iniSecs[j].sectionValues[devAISGen.ROMFunc[i].paramNames[k].ToUpper()]);
                sig_bw.Write((UInt32)iniSecs[j].sectionValues[devAISGen.ROMFunc[i].paramNames[k].ToUpper()]);
                devAISGen.signatureByteCnt += 4;
              }
              
              //Insert signature
              SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);
              
              // Call UARTSendDONE from AIS Extras if this is for UART boot
              if (devAISGen.SendUARTSendDONE)
              {
                tempAIS_bw.Write((UInt32)AIS.Jump);
                tempAIS_bw.Write(devAISGen.UARTSendDONEAddr);
                
                sig_bw.Write((UInt32)AIS.Jump);
                sig_bw.Write(devAISGen.UARTSendDONEAddr);
                devAISGen.signatureByteCnt += 8;
                
                // Insert signature
                SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);
              }
            }
          }
        }

        #endregion


        #region Insert seqread command
        if (seqReadEn == true)
        {
          tempAIS_bw.Write((UInt32)AIS.SeqReadEnable);
          sig_bw.Write((UInt32)AIS.SeqReadEnable);
          devAISGen.signatureByteCnt += 4;
        }
          
        #endregion


        #region AIS executable data download
        if (AISExtrasCF != null)
        {
          // Load the AISExtras COFF file
          SecureAISCOFFLoad(AISExtrasCF, devAISGen);
          
          // Increment section count
          numTargetSections += (UInt32)AISExtrasCF.Header["numTargetSections"];
        }
        #endregion


        #region AIS Extras init function execution
        //Insert calls for any AISExtra Init functions (like power domains)
        if (AISExtrasCF != null)
        {
          for (UInt32 i = 0; i < devAISGen.AISExtraFunc.Length; i++)
          {
            if (devAISGen.AISExtraFunc[i].isInitFunc)
            {
              for (UInt32 j = 0; j < iniSecs.Length; j++)
              {
                if (iniSecs[j].iniSectionName.Equals(devAISGen.AISExtraFunc[i].iniSectionName))
                {
                  for (UInt32 k = 0; k < devAISGen.AISExtraFunc[i].numParams; k++)
                  {
                    // Write SET command
                    tempAIS_bw.Write((UInt32)AIS.Set);
                    sig_bw.Write((UInt32)AIS.Set);
  				                    
                    //Write type field (32-bit only)
                    tempAIS_bw.Write((UInt32)0x3);
                    sig_bw.Write((UInt32)0x3);
                   
                    // Write appropriate parameter address
                    tempAIS_bw.Write((UInt32) (devAISGen.AISExtraFunc[i].paramAddr + (k * 4)));
                    sig_bw.Write((UInt32) (devAISGen.AISExtraFunc[i].paramAddr + (k * 4)));
                    
                    //Write data to write
                    tempAIS_bw.Write((UInt32)iniSecs[j].sectionValues[devAISGen.AISExtraFunc[i].paramNames[k].ToString()]);
                    sig_bw.Write((UInt32)iniSecs[j].sectionValues[devAISGen.AISExtraFunc[i].paramNames[k].ToString()]);
                    
                    //Write Sleep value (should always be zero)
                    tempAIS_bw.Write((UInt32)0x0);
                    sig_bw.Write((UInt32)0x0);
                    devAISGen.signatureByteCnt += 20;
                    
                    // Insert signature
                    SecureAISInsertSignature(devAISGen.signatureStream, devAISGen);
                  }

                  // Now that params are set, Jump to function
                  tempAIS_bw.Write((UInt32)AIS.Jump);
                  tempAIS_bw.Write(devAISGen.AISExtraFunc[i].funcAddr);
                  sig_bw.Write((UInt32)AIS.Jump);
                  sig_bw.Write(devAISGen.AISExtraFunc[i].funcAddr);
                  devAISGen.signatureByteCnt += 8;
                  
                  // Insert signature
                  SecureAISInsertSignature(devAISGen.signatureStream, devAISGen);

                  // Call UARTSendDONE from AIS Extras if this is for UART boot
                  if (devAISGen.SendUARTSendDONE)
                  {
                    tempAIS_bw.Write((UInt32)AIS.Jump);
                    tempAIS_bw.Write(devAISGen.UARTSendDONEAddr);
                    
                    sig_bw.Write((UInt32)AIS.Jump);
                    sig_bw.Write(devAISGen.UARTSendDONEAddr);
                    devAISGen.signatureByteCnt += 8;
                    
                    // Insert signature
                    SecureAISInsertSignature(devAISGen.signatureStream, devAISGen);
                  }
                }
              }
            }
          }
        }
        #endregion

        Debug.DebugMSG("Starting binary file section loads.");

        #region Insert binary data files as SECTION_LOAD commands
        // Insert binary files
        for (Int32 i=0; i<binaryFiles.Count; i++)
        {
          if (File.Exists(binaryFiles[i].fileName))
          {
            SecureAISBinarySectionLoad(binaryFiles[i].fileName, devAISGen, binaryFiles[i].loadAddr, binaryFiles[i].encrypt);
            Debug.DebugMSG("Binary file {0} found.", binaryFiles[i].fileName);
            
            numTargetSections++;
            
            if (binaryFiles[i].useEntryPoint)
            {
              entryPoint = binaryFiles[i].entryPointAddr;
            }
          }
          else
          {
            Console.WriteLine("WARNING: Binary input file {0} was not found. Skipping.",binaryFiles[i].fileName);
          }
        }        
        #endregion        

        Debug.DebugMSG("Starting object file section loads.");

        #region COFF file parsing and loading
        // Create the COFF file object for the main application being loaded
        if (File.Exists(coffFileName))
        {
          SecureObjectFile currFile = new SecureObjectFile();
          currFile.useEntryPoint = true;
          currFile.fileName = coffFileName;
          currFile.encrypt = false;
          
          // Cycle throught all other object files loaded via INI file and unset their
          // useEntryPoint boolean, warning us as we do
          Boolean showWarning = false;
          for (Int32 i=0; i<objectFiles.Count; i++)
          {
            // Insert binary file
            if (objectFiles[i].useEntryPoint)
            {
              objectFiles[i].useEntryPoint = false;
              showWarning = true;
            }
          }
          
          if (showWarning)
            Console.WriteLine("WARNING: Ignoring useEntryPoint flag from all object file sections of INI file");
          
          objectFiles.Add(currFile);
        }
        
        // Insert object files
        for (Int32 i=0; i<objectFiles.Count; i++)
        {
          if (File.Exists(objectFiles[i].fileName))
          {
            // FIXME: Add support to detect ELF or COFF and support ELF parsing
            
            // Parse the object file
            COFFFile cf = new COFFFile(objectFiles[i].fileName);
            
            if (cf != null)
            {
              String[] tempEncryptString = null;
              if (objectFiles[i].encrypt)
              {
                // If this Object file is specified for encryption, temporarily set 
                // global sectionsToEncrypt string to "ALL"
                tempEncryptString = devAISGen.sectionsToEncrypt;
                devAISGen.sectionsToEncrypt = new String[1]{"ALL"};
                
                // Load the object file contents
                SecureAISCOFFLoad(cf, devAISGen);  

                // Increment section count
                numTargetSections += (UInt32)cf.Header["numTargetSections"];                
                
                // If this Object file is specified for encryption, reset the 
                // global sectionsToEncrypt string to its original value
                devAISGen.sectionsToEncrypt = tempEncryptString;                
              }
              else
              {
                // Load the object file contents
                SecureAISCOFFLoad(cf, devAISGen);
              }
            }
            else
            {
              Console.WriteLine("ERROR: Parsing the input object file {0} failed!",objectFiles[i].fileName);
            }
            
            if (entryPoint == 0x00000000)
            {
              if (objectFiles[i].useEntryPoint)
              {
                entryPoint = (UInt32)cf.Header["optEntryPoint"];
              }
            }
            
            // Insert final function register function
            if (devAISGen.finalFxnName != null)
            {
              Hashtable symbol;
              // Look for the symbol in the Coff file symbols table
              symbol = cf.symFind(devAISGen.finalFxnName);
              
              // If found, insert the command
              if (symbol != null)
              {
                tempAIS_bw.Write((UInt32)AIS.FinalFxnReg);
                tempAIS_bw.Write((UInt32)symbol["value"]);
                sig_bw.Write((UInt32)AIS.FinalFxnReg);
                sig_bw.Write((UInt32)symbol["value"]);
                devAISGen.signatureByteCnt += 8;
                
                Console.WriteLine("Finalize function symbol, '{0}', found as address 0x{1:X8}.",devAISGen.finalFxnName,(UInt32)symbol["value"]);
              }
              else
              {
                Console.WriteLine("Finalize function symbol, '{0}', not found.",devAISGen.finalFxnName);
              }
            }
          
            // Close object file
            if (cf != null)
              cf.Close();
          }
          else
          {
            Console.WriteLine("WARNING: Input object file {0} was not found. Skipping.",objectFiles[i].fileName);
          }
        }
        
        #endregion


        #region Insert Final JUMP_CLOSE command
        tempAIS_bw.Write((UInt32)AIS.Jump_Close);
        tempAIS_bw.Write(entryPoint);
        sig_bw.Write((UInt32)AIS.Jump_Close);
        sig_bw.Write(entryPoint);
        devAISGen.signatureByteCnt += 8;
        
        if (entryPoint == 0x00000000)
          Console.WriteLine("WARNING: Entry point never set or set to invalid value");
        
        // Insert signature
        SecureAISInsertSignature(devAISGen.signatureStream, devAISGen);            

        // Flush the data and then return to start
        devAISGen.devAISStream.Flush();
        devAISGen.devAISStream.Seek(0,SeekOrigin.Begin);

        devAISGen.signatureStream.Close();
        #endregion

        // Console output
        Console.WriteLine("AIS file generation was successful.");
        
        // ---------------------------------------------------------
        // ******************* END AIS GENERATION ******************
        // ---------------------------------------------------------
      }
      #endregion


      #region Prepare the return byte array
      // Now create return byte array based on AIS Stream data
      EndianBinaryReader tempAIS_br;
      tempAIS_br = new EndianBinaryReader(
              devAISGen.devAISStream,
              Endian.LittleEndian);

      numWords = ((UInt32)tempAIS_br.BaseStream.Length) >> 2;
      devAISGen.AISData = new Byte[numWords << 2];   //Each word converts to 4 binary bytes

      Debug.DebugMSG("Number of words in the stream is {0}", numWords);

      // Copy the data to the output Byte array
      for (UInt32 i = 0; i < numWords; i++)
      {
        BitConverter.GetBytes(tempAIS_br.ReadUInt32()).CopyTo(devAISGen.AISData, i * 4);
      }

      // Close the binary reader
      tempAIS_br.Close();
      
      // Close the COFF files since we are done with them
      if (AISExtrasCF != null)
        AISExtrasCF.Close();
      
      // Clean up any embedded file resources that may have been extracted
      EmbeddedFileIO.CleanUpEmbeddedFiles();

      #endregion

      // Return Byte Array
      return devAISGen.AISData;
    }
   
    /// <summary>
    /// SecureGenAIS command.
    /// </summary>
    /// <param name="coffFileName">File name of input .out file</param>
    /// <param name="bootMode">AISGen Object for the particular device</param>
    /// <returns>Bytes of the binary or AIS boot image</returns>
    public static Byte[] SecureGenAIS(String coffFileName,
                                      AISGen devAISGen,
                                      String iniData)
    {
      return SecureGenAIS(coffFileName, devAISGen, INI.Parse(iniData));
    }    
   
    /// <summary>
    /// Secondary genAIS thats calls the first
    /// </summary>
    /// <param name="coffFileName">File name of .out file</param>
    /// <param name="bootmode">String containing desired boot mode</param>
    /// <returns>an Array of bytes to write to create an AIS file</returns>
    public static Byte[] SecureGenAIS(String coffFileName,
                                      String bootmode,
                                      AISGen devAISGen,
                                      INISection[] iniSecs)
    {
      devAISGen.bootMode = (BootModes)Enum.Parse(typeof(BootModes), bootmode, true);
      Console.WriteLine("Chosen bootmode is {0}.", devAISGen.bootMode.ToString());
      return SecureGenAIS(coffFileName, devAISGen, iniSecs);
    }

    /// <summary>
    /// Secondary genAIS thats calls the first
    /// </summary>
    /// <param name="coffFileName">File name of .out file</param>
    /// <param name="bootmode">String containing desired boot mode</param>
    /// <returns>an Array of bytes to write to create an AIS file</returns>
    public static Byte[] SecureGenAIS(String coffFileName,
                                      String bootmode,
                                      AISGen devAISGen,
                                      String iniData)
    {
      return SecureGenAIS(coffFileName, bootmode, devAISGen, INI.Parse(iniData));
    }
    
    /// <summary>
    /// Secondary genAIS thats calls the first
    /// </summary>
    /// <param name="coffFileName">File name of .out file</param>
    /// <param name="bootmode">AISGen.BootModes Enum value containing desired boot mode</param>
    /// <returns>an Array of bytes to write to create an AIS file</returns>
    public static Byte[] SecureGenAIS(String coffFileName,
                                      BootModes bootmode,
                                      AISGen devAISGen,
                                      INISection[] iniSecs)
    {
      devAISGen.bootMode = bootmode;
      Console.WriteLine("Chosen bootmode is {0}.", devAISGen.bootMode.ToString());
      return SecureGenAIS(coffFileName, devAISGen, iniSecs);
    }

    /// <summary>
    /// Secondary genAIS thats calls the first
    /// </summary>
    /// <param name="coffFileName">File name of .out file</param>
    /// <param name="bootmode">AISGen.BootModes Enum value containing desired boot mode</param>
    /// <returns>an Array of bytes to write to create an AIS file</returns>
    public static Byte[] SecureGenAIS(String coffFileName,
                                      BootModes bootmode,
                                      AISGen devAISGen,
                                      String iniData)
    {
      return SecureGenAIS(coffFileName, bootmode, devAISGen, INI.Parse(iniData));
    }
    
    #endregion
    
    /// <summary>
    /// Signature insertion creation and insertion routine
    /// </summary>
    public static retType SecureAISInsertSignature( Stream sigStream, AISGen devAISGen )
    {
      EndianBinaryWriter ebw = new EndianBinaryWriter(
          devAISGen.devAISStream,
          devAISGen.devEndian);
      
      // Make sure all data is present for signature calculation
      sigStream.Flush();
      
      // Reset stream to start
      sigStream.Position = 0;
      
      // Increment signature count
      devAISGen.signatureCnt++;

      // Calculate hash of data
      Byte[] hash = devAISGen.currHashAlgorithm.ComputeHash(sigStream);
      Console.WriteLine("Signature #{0}",devAISGen.signatureCnt);
      Console.WriteLine("\tSignature Hash: {0}",BitConverter.ToString(hash));
      Console.WriteLine("\tSignature Byte Count = {0}",sigStream.Length);
      Byte[] signatureData = null;
      
      // Generate signature via encryption
      if ( devAISGen.secureType == SecureType.GENERIC )
      {
        signatureData = new Byte[32];
               
        // Fill signature data buffer with random bytes
        (new Random()).NextBytes(signatureData);
        
        // Copy calculated SHA hash into signature data buffer
        hash.CopyTo(signatureData,0);

        using (MemoryStream ms = new MemoryStream())
        {
          Aes myAES = new AesManaged();
          myAES.KeySize = 128;
          myAES.Mode = CipherMode.CBC;
          myAES.Padding = PaddingMode.None;
          ICryptoTransform encryptor = myAES.CreateEncryptor(devAISGen.customerEncryptionKey, devAISGen.CEKInitialValue);
          CryptoStream cs = new CryptoStream(ms,encryptor,CryptoStreamMode.Write);
          cs.Write(signatureData,0,signatureData.Length);
          cs.FlushFinalBlock();
          ms.ToArray().CopyTo(signatureData,0);
        }
      }
      else if ( devAISGen.secureType == SecureType.CUSTOM )
      {

        RSAPKCS1SignatureFormatter rsaFormatter = new RSAPKCS1SignatureFormatter(devAISGen.rsaObject);

        // Create a signature for HashValue and return it.
        signatureData = rsaFormatter.CreateSignature(devAISGen.currHashAlgorithm);
        
        // Signature info needs to be revered to work with RSA functionality in ROM
        Array.Reverse(signatureData);
      }
      
      // Write the signature data to the output AIS binary writer
      ebw.Write(signatureData);
        
      // Clear the signature stream now that we have used the data for signature generation
      sigStream.SetLength(0);
      sigStream.Position = 0;
      
      return retType.SUCCESS;
    }
    
    /// <summary>
    /// AIS Section Load command generation
    /// </summary>
    /// <param name="cf">The COFFfile object that the section comes from.</param>
    /// <param name="secHeader">The Hashtable object of the section header to load.</param>
    /// <param name="devAISGen">The specific device AIS generator object.</param>
    /// <returns>retType enumerator indicating success or failure.</returns>
    private static retType SecureAISBinarySectionLoad(
                    String fileName,
                    AISGen devAISGen,
                    UInt32 loadAddress,
                    Boolean encryptSection)
    {
      String secName = fileName;
      UInt32 loadAddr = loadAddress;
      UInt32 secSize = (UInt32) (((new FileInfo(fileName)).Length + 3) >> 2) << 2;
      Byte[] secData = new Byte[secSize];
      Byte[] srcCRCData = new Byte[secSize + 8];
      UInt32 numWords = secSize >> 2;

      // Read file data
      using (FileStream fs = new FileStream(fileName, FileMode.Open, FileAccess.Read))
      {
        if (fs.Read(secData,0,(Int32) fs.Length) != fs.Length)
        {
          Console.WriteLine("ERROR: Reading binary file {0} failed!", fileName);
        }
      }

      EndianBinaryWriter ebw = new EndianBinaryWriter(
          devAISGen.devAISStream,
          devAISGen.devEndian);
          
      EndianBinaryWriter sig_bw = new EndianBinaryWriter(
          devAISGen.signatureStream,
          devAISGen.devEndian);

      // Write Section_Load AIS command, load address, and size
      UInt32 sectionLoadCommand = (encryptSection ? (UInt32)AIS.EncSection_Load : (UInt32)AIS.Section_Load );
      ebw.Write(sectionLoadCommand);
      ebw.Write(loadAddr);
      ebw.Write(secSize);
      sig_bw.Write(sectionLoadCommand);      
      sig_bw.Write(loadAddr);
      sig_bw.Write(secSize);
      devAISGen.signatureByteCnt += 12;        
      
      // Now write contents
      if (!encryptSection)
      {
        // Non-encrypted section
        for (int k = 0; k < numWords; k++)
        {
          ebw.Write(secData[k]);
          sig_bw.Write(secData[k]);
          devAISGen.signatureByteCnt += 4;
        }
      }
      else
      {
        // Encrypted section
        // Write unencrypted data to the signature buffer
        for (int k = 0; k < numWords; k++)
        {
          sig_bw.Write(secData[k]);
          devAISGen.signatureByteCnt += 4;
        }
        Console.WriteLine("Wrote {0} bytes to signature buffer.", numWords *4);
      
        Byte[] tempData = new Byte[numWords * 4];
        EndianBinaryWriter tempEbw = new EndianBinaryWriter(new MemoryStream(tempData), devAISGen.devEndian);
        
        // Write data to the tempData through the endian binary writer/memory stream
        for (int k = 0; k < numWords; k++)
        {
          tempEbw.Write(secData[k]);
        }
        tempEbw.Close();   
        
        // Encrypt data using CTS algorithm
        try
        {
          Byte[] encData = AesManagedUtil.AesCTSEncrypt(tempData,devAISGen.customerEncryptionKey,devAISGen.CEKInitialValue);
          
          // Write encrypted section data out to AIS data stream
          ebw.Write(encData);
        }
        catch(Exception e)
        {
          Console.WriteLine("Exception during encryption operation: {0}",e.Message);
        }
      }
      
      // Add this section's memory range, checking for overlap
      AddMemoryRange(devAISGen, loadAddr, loadAddr+secSize-1);

      // Check if we need to output DONE to the UART
      if (devAISGen.SendUARTSendDONE)
      {
        ebw.Write((UInt32)AIS.Jump);
        ebw.Write(devAISGen.UARTSendDONEAddr);
        sig_bw.Write((UInt32)AIS.Jump);
        sig_bw.Write(devAISGen.UARTSendDONEAddr);
        devAISGen.signatureByteCnt += 8;
        
        SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);
      }

      Debug.DebugMSG("Secure binary section load complete.");

      return retType.SUCCESS;
    }
    
    /// <summary>
    /// AIS Section Load command generation
    /// </summary>
    /// <param name="cf">The COFFfile object that the section comes from.</param>
    /// <param name="secHeader">The Hashtable object of the section header to load.</param>
    /// <param name="devAISGen">The specific device AIS generator object.</param>
    /// <returns>retType enumerator indicating success or failure.</returns>
    private static retType SecureAISSectionLoad(
                    COFFFile cf,
                    Hashtable secHeader,
                    AISGen devAISGen,
                    Boolean encryptSection)
    {
      UInt32 secSize = (UInt32)secHeader["byteSize"];
      String secName = (String)secHeader["name"];
      UInt32 runAddr = (UInt32)secHeader["phyAddr"];
      UInt32 loadAddr = (UInt32)secHeader["virAddr"];
      UInt32 numWords = (UInt32)secHeader["wordSize"];
      UInt32[] secData = cf[secName];
      Byte[] srcCRCData = new Byte[secSize + 8];

      EndianBinaryWriter ebw = new EndianBinaryWriter(
          devAISGen.devAISStream,
          devAISGen.devEndian);
          
      EndianBinaryWriter sig_bw = new EndianBinaryWriter(
          devAISGen.signatureStream,
          devAISGen.devEndian);

      // Write Section_Load AIS command, load address, and size
      if (encryptSection)
      {
        ebw.Write((UInt32)AIS.EncSection_Load);
        ebw.Write(loadAddr);
        ebw.Write(secSize);
        sig_bw.Write((UInt32)AIS.EncSection_Load);
        sig_bw.Write(loadAddr);
        sig_bw.Write(secSize);
        devAISGen.signatureByteCnt += 12;
      }
      else
      {
        ebw.Write((UInt32)AIS.Section_Load);
        ebw.Write(loadAddr);
        ebw.Write(secSize);
        sig_bw.Write((UInt32)AIS.Section_Load);
        sig_bw.Write(loadAddr);
        sig_bw.Write(secSize);
        devAISGen.signatureByteCnt += 12;
      }
      
      // Now write contents
      if (!encryptSection)
      {
        // Non-encrypted section
        for (int k = 0; k < numWords; k++)
        {
          ebw.Write(secData[k]);
          sig_bw.Write(secData[k]);
          devAISGen.signatureByteCnt += 4;
        }
      }
      else
      {
        // Encrypted section
        // Write unencrypted data to the signature buffer
        for (int k = 0; k < numWords; k++)
        {
          sig_bw.Write(secData[k]);
          devAISGen.signatureByteCnt += 4;
        }
        Console.WriteLine("Wrote {0} bytes to signature buffer.", numWords *4);
      
        Byte[] tempData = new Byte[numWords * 4];
        EndianBinaryWriter tempEbw = new EndianBinaryWriter(new MemoryStream(tempData), devAISGen.devEndian);
        
        // Write data to the tempData through the endian binary writer/memory stream
        for (int k = 0; k < numWords; k++)
        {
          tempEbw.Write(secData[k]);
        }
        tempEbw.Close();   
        
        // Encrypt data using CTS algorithm
        try
        {
          Byte[] encData = AesManagedUtil.AesCTSEncrypt(tempData,devAISGen.customerEncryptionKey,devAISGen.CEKInitialValue);
          
          // Write encrypted section data out to AIS data stream
          ebw.Write(encData);
        }
        catch(Exception e)
        {
          Console.WriteLine("Exception during encryption operation: {0}",e.Message);
        }
      }
      
      // Add this section's memory range, checking for overlap
      AddMemoryRange(devAISGen, loadAddr, loadAddr+secSize-1);      

      // Check if we need to output DONE to the UART
      if (devAISGen.SendUARTSendDONE)
      {
        ebw.Write((UInt32)AIS.Jump);
        ebw.Write(devAISGen.UARTSendDONEAddr);
        sig_bw.Write((UInt32)AIS.Jump);
        sig_bw.Write(devAISGen.UARTSendDONEAddr);
        devAISGen.signatureByteCnt += 8;
        
        SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);
      }

      // Check for need to do IDMA relocation
      if (loadAddr != runAddr)
      {
        Boolean LoadInCache = false, RunInL1PCache = false;
        for (int j = 0; j < devAISGen.Cache.Length; j++)
        {
          LoadInCache = (LoadInCache || devAISGen.Cache[j].InCache(loadAddr));
          RunInL1PCache = (RunInL1PCache || 
                             ((devAISGen.Cache[j].InCache(runAddr)) &&
                             (devAISGen.Cache[j].level == CacheLevel.L1) &&
                             (devAISGen.Cache[j].type == CacheType.Program))
                             );
        }
        Debug.DebugMSG("LoadInCache : {0}, RunInL1PCache: {1}", LoadInCache, RunInL1PCache);
        if (RunInL1PCache && LoadInCache)
        {
          //Write Set commands to make the IDMA do transfer
          // Write SET command
          ebw.Write((UInt32)AIS.Set);
          sig_bw.Write((UInt32)AIS.Set);
          //Write type field (32-bit only)
          ebw.Write((UInt32)0x3);
          sig_bw.Write((UInt32)0x3);
          // Write appropriate parameter address
          ebw.Write((UInt32)devAISGen.IDMA[1].IDMA_SRC_ADDR);
          sig_bw.Write((UInt32)devAISGen.IDMA[1].IDMA_SRC_ADDR);
          //Write data to write (the src address)
          ebw.Write((UInt32)loadAddr);
          sig_bw.Write((UInt32)loadAddr);
          //Write Sleep value
          ebw.Write((UInt32)0x0);
          sig_bw.Write((UInt32)0x0);
          devAISGen.signatureByteCnt += 20;

          SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);

          // Write SET command
          ebw.Write((UInt32)AIS.Set);
          sig_bw.Write((UInt32)AIS.Set);
          //Write type field (32-bit only)
          ebw.Write((UInt32)0x3);
          sig_bw.Write((UInt32)0x3);
          // Write appropriate parameter address
          ebw.Write((UInt32)devAISGen.IDMA[1].IDMA_DEST_ADDR);
          sig_bw.Write((UInt32)devAISGen.IDMA[1].IDMA_DEST_ADDR);
          //Write data to write (the dest address)
          ebw.Write((UInt32)runAddr);
          sig_bw.Write((UInt32)runAddr);
          //Write Sleep value
          ebw.Write((UInt32)0x0);
          sig_bw.Write((UInt32)0x0);
          devAISGen.signatureByteCnt += 20;
          
          SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);

          // Write SET command
          ebw.Write((UInt32)AIS.Set);
          sig_bw.Write((UInt32)AIS.Set);
          //Write type field (32-bit only)
          ebw.Write((UInt32)0x3);
          sig_bw.Write((UInt32)0x3);
          // Write appropriate parameter address
          ebw.Write((UInt32)devAISGen.IDMA[1].IDMA_CNT_ADDR);
          sig_bw.Write((UInt32)devAISGen.IDMA[1].IDMA_CNT_ADDR);
          //Write data to write (the byte count - must be multiple of four)
          ebw.Write((UInt32)(numWords * 4));
          sig_bw.Write((UInt32)(numWords * 4));
          //Write Sleep value
          ebw.Write((UInt32)0x1000);
          sig_bw.Write((UInt32)0x1000);
          devAISGen.signatureByteCnt += 20;
          
          SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);

          // Check if we need to output DONE to the UART
          if (devAISGen.SendUARTSendDONE)
          {
            ebw.Write((UInt32)AIS.Jump);
            ebw.Write((UInt32)devAISGen.UARTSendDONEAddr);
            
            sig_bw.Write((UInt32)AIS.Jump);
            sig_bw.Write((UInt32)devAISGen.UARTSendDONEAddr);
			
            devAISGen.signatureByteCnt += 8;
            
            SecureAISInsertSignature(devAISGen.signatureStream,devAISGen);
          }
        }
      }

      Debug.DebugMSG("Secure Section Load complete");

      return retType.SUCCESS;
    }

    /// <summary>
    /// AIS COFF file Load command generation (loads all sections)
    /// </summary>
    /// <param name="cf">The COFFfile object that the section comes from.</param>
    /// <param name="devAISGen">The specific device AIS generator object.</param>
    /// <returns>retType enumerator indicating success or failure.</returns>
    private static retType SecureAISCOFFLoad(
                    COFFFile cf,
                    AISGen devAISGen)
    {
      UInt32 numSymbols, numSections, numTargetSections;
      Hashtable[] symbols, sections, targetSections;
      UInt32 totalLoadableSize = 0;
      UInt32 TIBootSetupAddr = 0x00000000;

      EndianBinaryWriter ebw = new EndianBinaryWriter(
          devAISGen.devAISStream,
          devAISGen.devEndian);
          
      EndianBinaryWriter sig_bw = new EndianBinaryWriter(
          devAISGen.signatureStream,
          devAISGen.devEndian);
     
      if (!devAISGen.devEndian.ToString().Equals(cf.Endianness))
      {
        Console.WriteLine("Endianness mismatch. Device is {0} endian, COFF file is {1} endian",
            devAISGen.devEndian.ToString(),
            cf.Endianness);
        return retType.FAIL;
      }
      
      Console.WriteLine("Section loading starts now");

      // Get COFF file section info
      numSections = (UInt32)cf.Header["numSectionHdrs"];
      sections = cf.Sections;

      // Get COFF file symbol info
      numSymbols = (UInt32)cf.Header["numEntriesInSymTable"];
      symbols = cf.Symbols;

      // Make sure the .TIBoot section is first (if it exists)
      Hashtable firstSection = sections[0];
      for (Int32 i = 1; i < numSections; i++)
      {
        if (((String)sections[i]["name"]).Equals(".TIBoot"))
        {
          sections[0] = sections[i];
          sections[i] = firstSection;
          break;
        }
      }

      // Look for the _TIBootSetup symbol (if it exists)
      for (Int32 i = 0; i < numSymbols; i++)
      {
        if (((String)symbols[i]["name"]).Equals("_TIBootSetup"))
        {
          TIBootSetupAddr = (UInt32)symbols[i]["value"];
          Debug.DebugMSG("Symbol :{0}:", (String)symbols[i]["name"]);
        }
      }

      // Create array of Hashtable describing loadable sections
      numTargetSections = (UInt32)cf.Header["numTargetSections"];
      Debug.DebugMSG("Number of target loadable sections = {0}", numTargetSections);
      targetSections = new Hashtable[numTargetSections];
      Debug.DebugMSG("Loadable Sections:");
      for (Int32 i = 0, j = 0; i < numSections; i++)
      {
        if ((Boolean)sections[i]["copyToTarget"])
        {
          targetSections[j++] = sections[i];
          totalLoadableSize += (UInt32)sections[i]["byteSize"];
          Debug.DebugMSG("\t{0}. Section Name: {1}, Section Size: {2}",j, (String)sections[i]["name"], (UInt32)sections[i]["byteSize"]);
        }
      }
      
      // If the devAISGen.sectionsToEncrypt just says "ALL", then rebuild it with all loadable sections

      // Do all SECTION_LOAD commands (encrypted and/or secure)
      for (Int32 i = 0; i < numTargetSections; i++)
      {
        Boolean encryptSection = false;
        if (devAISGen.sectionsToEncrypt != null)
        {
          if ( (devAISGen.sectionsToEncrypt.Length == 1) && devAISGen.sectionsToEncrypt[0].Equals("ALL"))
          {
            encryptSection = true;
            Console.WriteLine("Encrypting section {0}, since ALL was specified for encryptSections in ini file.",(String)targetSections[i]["name"]);
          }
          else
          {
            if ( Array.IndexOf(devAISGen.sectionsToEncrypt,((String)targetSections[i]["name"])) >= 0 )
            {
              encryptSection = true;
              Console.WriteLine("Encrypting section {0}, since it was explicitly specified in encryptSections in ini file.",(String)targetSections[i]["name"]);
            }
          }
        }
      
        if (SecureAISSectionLoad(cf, targetSections[i], devAISGen, encryptSection) != retType.SUCCESS)
          return retType.FAIL;
        totalLoadableSize += (UInt32)targetSections[i]["byteSize"];
        
        // Check for need to do TIBoot initialization
        if (i == 0)
        {
          if (TIBootSetupAddr != 0)
          {
            ebw.Write((UInt32)AIS.Jump);
            ebw.Write(TIBootSetupAddr);
            sig_bw.Write((UInt32)AIS.Jump);
            sig_bw.Write(TIBootSetupAddr);
            
            devAISGen.signatureByteCnt += 8;
            
            SecureAISInsertSignature(devAISGen.signatureStream, devAISGen);
          }
        }
      } // End of SECTION_LOAD commands
      

      Debug.DebugMSG("AISCOFFLoad Complete");

      return retType.SUCCESS;
    }

    private static String KeyToBinaryString(Byte[] key,UInt32 startAddr,Boolean readProtect, Boolean writeProtect)
    {
      Byte bits40to32 = (Byte) (0 + (readProtect?2:0) + (writeProtect?4:0));    
      StringBuilder sb = new StringBuilder(256);
      
      for (int i= 0; i < (key.Length >> 2); i++)
      {
        sb.AppendFormat("{0:X8} ",startAddr + i);
        sb.Append((Convert.ToString(bits40to32,2)).PadLeft(9,'0'));
        
        // Get bytes of keys in chunks of four, in reverse order, convert to UInt32, Convert to binary string, pad left with zeros, then convert to char array
        Char[] data = Convert.ToString( BitConverter.ToUInt32(key,key.Length-(4*(i+1))), 2).PadLeft(32,'0').ToCharArray();
        
        // Reverse data in array
        Array.Reverse(data);
        
        // Append the reversed binary string into the StringBuilder object        
        sb.Append( new String(data) );
        
        // Finish this line
        sb.Append("\n");
      }
      
      return sb.ToString();
    }    

  }
                        
} //end of AISGenLib namespace

