using System;
using System.Collections;
using System.Globalization;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;
using UtilLib;
using UtilLib.IO;

namespace UtilLib.Crypto
{
  public class RSAKey
  {
    private const string PEMStartString         = "-----BEGIN ";
    private const string PEMEndString           = "-----END ";

    private const string PEMPubString           = "PUBLIC KEY-----";    
    private const string PEMPrivString          = "RSA PRIVATE KEY-----";
    private const string PEMPKCS8PrivString     = "PRIVATE KEY-----";
    private const string PEMPKCS8EncPrivString  = "ENCRYPTED PUBLIC KEY-----";

    private static RSACryptoServiceProvider LoadPEMKey(String fileName)
    {
      StreamReader sr = File.OpenText(fileName);
      String fileStr = sr.ReadToEnd().Trim();
      sr.Close();
      
      if( fileStr.StartsWith(PEMStartString+PEMPubString) && fileStr.EndsWith(PEMEndString+PEMPubString) )
      {
        // Public Key PEM file
        Console.WriteLine("Reading PEM public key from file {0}...", fileName);
        return null;
      }
      else if( fileStr.StartsWith(PEMStartString+PEMPrivString) && fileStr.EndsWith(PEMEndString+PEMPrivString) )
      {
        // Unencrypted Private Key PEM file
        byte[] keyBlob = null;
        
        Console.WriteLine("Reading PEM private key from file {0}...", fileName);
        fileStr = TrimPEMData(fileStr);
        try
        {
          // Get binary data from Base64 string
          keyBlob = Convert.FromBase64String (fileStr);

          // Convert binary data to ASN.1 Sequence object and then parse the sequence
          // into RSAPrivateKey Components, then use to create an RSA CSP object.
          return ParseRSAPrivateKey(new Asn1Sequence(keyBlob));
        }
        catch(FormatException )
        {
          Console.WriteLine("Error in the PEM data!");
          return null;
        }
      }
      else if( fileStr.StartsWith(PEMStartString+PEMPKCS8PrivString) && fileStr.EndsWith(PEMEndString+PEMPKCS8PrivString) )
      {
        // Unencrypted PKCS#8 Private Key PEM file
        Console.WriteLine("Reading PKCS#8 PEM private key from file {0}...", fileName);
        return null;
      }
      else if( fileStr.StartsWith(PEMStartString+PEMPKCS8EncPrivString) && fileStr.EndsWith(PEMEndString+PEMPKCS8EncPrivString) )
      {
        // Encrypted PKCS#8 Private Key PEM file
        Console.WriteLine("Reading Encrypted PKCS#8 PEM private key from file {0}...", fileName);
        return null;
      }
      else
        return null;
    }      
        
    private static RSACryptoServiceProvider LoadDERKey(String fileName)
    {
      BinaryReader br = new BinaryReader(File.OpenRead(fileName));
      
      Byte[] fileData = br.ReadBytes((Int32) br.BaseStream.Length);
      
      return ParseRSAPrivateKey(new Asn1Sequence(fileData));
    }
    
    private static RSACryptoServiceProvider LoadXMLKey(String fileName)
    {
      StreamReader sr = File.OpenText(fileName);
      String fileStr = sr.ReadToEnd().Trim();
      sr.Close();
      
      try
      {
        RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
        RSA.FromXmlString(fileStr);
        return RSA;
      }
      catch
      {
        return null;
      }
    }

    private static String TrimPEMData(String pemString)
    {
      Regex rgx = new Regex("-{5}.+-{5}");
      return (rgx.Replace(pemString,"")).Trim();
    }    


    /* ASN.1 definitions from PKCS#1 v2.1
      RSAPublicKey ::= SEQUENCE {
          modulus           INTEGER,  -- n
          publicExponent    INTEGER   -- e 
      }

      -- 
      -- Representation of RSA private key with information for the CRT algorithm.
      --
      RSAPrivateKey ::= SEQUENCE {
          version           Version, 
          modulus           INTEGER,  -- n
          publicExponent    INTEGER,  -- e
          privateExponent   INTEGER,  -- d
          prime1            INTEGER,  -- p
          prime2            INTEGER,  -- q
          exponent1         INTEGER,  -- d mod (p-1)
          exponent2         INTEGER,  -- d mod (q-1) 
          coefficient       INTEGER,  -- (inverse of q) mod p
          otherPrimeInfos   OtherPrimeInfos OPTIONAL 
      }

      Version ::= INTEGER { two-prime(0), multi(1) }
          (CONSTRAINED BY {-- version must be multi if otherPrimeInfos present --})

      OtherPrimeInfos ::= SEQUENCE SIZE(1..MAX) OF OtherPrimeInfo


      OtherPrimeInfo ::= SEQUENCE {
          prime             INTEGER,  -- ri
          exponent          INTEGER,  -- di
          coefficient       INTEGER   -- ti
      } 
    */
    public static RSACryptoServiceProvider ParseRSAPrivateKey(Asn1Sequence RSAPrivateKey)
    {
      Byte[][] RSAPrivateKeyData;
      
      RSAParameters RSAParams = new RSAParameters();

      if ( (RSAPrivateKey.SequenceLength != 9) && (RSAPrivateKey.SequenceLength != 10) )
        throw new ArgumentException("ASN.1 Sequence has wrong number of elements for RSAPrivateKey.");
        
      RSAPrivateKeyData = new Byte[RSAPrivateKey.SequenceLength][];
      
      for(int i=0; i<RSAPrivateKey.SequenceLength; i++)
      {
        RSAPrivateKeyData[i] = RSAPrivateKey[i].ContentsToArray();
        
        // Trim leading zeros if any
        if ( (RSAPrivateKeyData[i][0] == 0x00) && (RSAPrivateKeyData[i].Length > 1) )
        {
          Byte[] temp = new Byte[RSAPrivateKeyData[i].Length - 1];
          Array.Copy(RSAPrivateKeyData[i],1,temp,0,RSAPrivateKeyData[i].Length - 1);
          RSAPrivateKeyData[i] = temp;
        }
      }
      
      // Verify version is v2.1
      //Console.WriteLine(RSAPrivateKeyData[0][0]);
      //Console.WriteLine(RSAPrivateKeyData[0][1]);
      //if( (RSAPrivateKeyData[0][0] != 0x02) || (RSAPrivateKeyData[0][1] != 0x01) )
      //  throw new ArgumentException("ASN.1 RSAPrivateKey Sequence has wrong version number.");
      
      // rsaData[0] is version field
      RSAParams.Modulus     = RSAPrivateKeyData[1];
      RSAParams.Exponent    = RSAPrivateKeyData[2];
      RSAParams.D           = RSAPrivateKeyData[3];
      RSAParams.P           = RSAPrivateKeyData[4];
      RSAParams.Q           = RSAPrivateKeyData[5];
      RSAParams.DP          = RSAPrivateKeyData[6];
      RSAParams.DQ          = RSAPrivateKeyData[7];
      RSAParams.InverseQ    = RSAPrivateKeyData[8];
      
      // Import the params into the RSA CSP
      try
      {
        RSACryptoServiceProvider RSA = new RSACryptoServiceProvider();
        RSA.ImportParameters(RSAParams);
        return RSA;
      }
      catch
      {
        return null;
      }
    }

    
    public static RSACryptoServiceProvider LoadFromFile(String fileName)
    {
      RSACryptoServiceProvider retVal = null;
      
      Console.WriteLine("Reading RSA Key information from file {0}...", fileName);
      
      // Try various formats in turn to see what works
      // Priority is .Net XML format, then PEM from OpenSSL, then DER from OpenSSL
      if( retVal == null ) retVal = LoadXMLKey(fileName);
      if( retVal == null ) retVal = LoadPEMKey(fileName);
      if( retVal == null ) retVal = LoadDERKey(fileName);
      
      if (retVal == null ) 
      {
        Console.WriteLine("Import of RSA key data failed!");
      }
      
      return retVal;
    }
    
    public static Byte[] CreateCustomSecureKeyVerifyStruct(RSA rsa)
    {
      Int32 modSizeInBytes = (rsa.KeySize >> 3);
      Int32 keyStructSize = 8 + modSizeInBytes;
      Byte[] modData = new Byte[modSizeInBytes];
      Byte[] keyVerifyStruct = new Byte[keyStructSize];

      // Zero out the array
      Array.Clear(keyVerifyStruct,0,keyStructSize);

      // Get the RSA Public Key Params
      RSAParameters RSAParams = rsa.ExportParameters(true);

      RSAParams.Exponent.CopyTo(keyVerifyStruct,0);

      BitConverter.GetBytes((Int16) (modSizeInBytes>>1)).CopyTo(keyVerifyStruct,6);
      
      // Modulus Bytes Need to be reversed for RSA code in ROM to work
      RSAParams.Modulus.CopyTo(modData,0);
      Array.Reverse(modData);
      modData.CopyTo(keyVerifyStruct,8);

      return keyVerifyStruct;
    }
  }

  public static class AesManagedUtil
  {
    private static AesManaged aes;
    private static int blockSizeInBytes;
    
    #region Static constructor
    static AesManagedUtil()
    {
      aes = new AesManaged();
      aes.Mode = CipherMode.CBC;
      aes.Padding = PaddingMode.None;
      
      blockSizeInBytes = (aes.BlockSize >> 3);
    }
    #endregion
    
    public static byte[] AesCBCEncrypt( byte[] input, byte[] key, byte[] iv )
    {
      byte[] output;
      int blockCnt;
      
      // Get block count (rounded up so all data is covered)
      blockCnt = (input.Length + (blockSizeInBytes - 1)) / blockSizeInBytes;
      
      // Validate input
      if ((blockCnt * blockSizeInBytes) != input.Length)
      {
        aes.Padding = PaddingMode.PKCS7;
        output = new byte[blockCnt * blockSizeInBytes];
      }
      else
      {
        aes.Padding = PaddingMode.None;
        output = new byte[input.Length];
      }
      
      aes.Key = key;
      aes.IV = iv;
      
      // Use CBC encryption to do CTS, with last two blocks swapped 
     
      // Do complete CBC encryption
      MemoryStream ms = new MemoryStream(output);
      CryptoStream cs = new CryptoStream(ms, aes.CreateEncryptor(), CryptoStreamMode.Write);
      try
      {
        cs.Write(input,0,input.Length);  
      }
      finally
      {
        cs.Close();
        ms.Close();
      }
      
      return output;
    }
    
    
    public static byte[] AesCTSEncrypt( byte[] input, byte[] key, byte[] iv )
    {
      byte[] output;
      byte[] tempIn,tempOut,tempSwap;
      int blockCnt;
                
      // Validate input
      if (input.Length <= blockSizeInBytes)
      {
        aes.Padding = PaddingMode.PKCS7;
        output = new byte[blockSizeInBytes];
      }
      else
      {
        aes.Padding = PaddingMode.None;
        output = new byte[input.Length];
      }
      
      
      aes.Key = key;
      aes.IV = iv;
      
      // Get block count (rounded up so all data is covered)
      blockCnt = (input.Length + (blockSizeInBytes - 1)) / blockSizeInBytes;
      
      if (blockCnt == 1)
      {
        // Do single block CBC encryption with PKCS7 padding
        MemoryStream ms = new MemoryStream(output);
        CryptoStream cs = new CryptoStream(ms, aes.CreateEncryptor(), CryptoStreamMode.Write);
        try
        {
          // Write Partial block
          cs.Write(input,0,input.Length);
          cs.FlushFinalBlock();
        }
        finally
        {
          cs.Close();
          ms.Close();
        }
      }
      else if (blockCnt > 1)
      {
        // Use CBC encryption to do CTS, with last two blocks swapped 
        tempSwap  = new byte[blockSizeInBytes];
        tempIn    = new byte[blockCnt * blockSizeInBytes];
        tempOut   = new byte[blockCnt * blockSizeInBytes];
        input.CopyTo(tempIn,0);
        
        Debug.DebugMSG("Input: {0}",BitConverter.ToString(input,(blockCnt - 2) * blockSizeInBytes));
        Debug.DebugMSG("tempIn: {0}",BitConverter.ToString(tempIn,(blockCnt - 2) * blockSizeInBytes));
        
        // Do complete CBC encryption
        MemoryStream ms = new MemoryStream(tempOut);
        CryptoStream cs = new CryptoStream(ms, aes.CreateEncryptor(), CryptoStreamMode.Write);
        try
        {
          cs.Write(tempIn,0,tempIn.Length);  
        }
        finally
        {
          cs.Close();
          ms.Close();
        }
        
        Debug.DebugMSG("tempOut: {0}",BitConverter.ToString(tempOut,(blockCnt - 2) * blockSizeInBytes));
        
        // Swap last two blocks of ciphertext
        Array.Copy(tempOut,blockSizeInBytes*(blockCnt-2),tempSwap,0,blockSizeInBytes);
        Array.Copy(tempOut,blockSizeInBytes*(blockCnt-1),tempOut,blockSizeInBytes*(blockCnt-2),blockSizeInBytes);
        Array.Copy(tempSwap,0,tempOut,blockSizeInBytes*(blockCnt-1),blockSizeInBytes);
        
        // Truncate to original input length
        Array.Copy(tempOut,0,output,0,input.Length);
        
        Debug.DebugMSG("output: {0}",BitConverter.ToString(output,(blockCnt - 2) * blockSizeInBytes));
      }
      
      return output;
    }
    
    public static byte[] AesCTSDecrypt( byte[] input, byte[] key, byte[] iv )
    {
      byte[] output = new byte[input.Length];
      byte[] tempIn,tempOut,tempSwap;
      int blockCnt;
      AesManaged ecbAes = new AesManaged();
      MemoryStream ms;
      CryptoStream cs;
      
      // Validate input
      if (input.Length <= blockSizeInBytes)
        throw new ArgumentException("Array size too small for Ciphertext Stealing","input");
     
      aes.Key = key;
      aes.IV = iv;
      
      if ( (input.Length % blockSizeInBytes) != 0)
        blockCnt = ((input.Length / blockSizeInBytes) + 1 );
      else
        blockCnt = (input.Length / blockSizeInBytes);
      
      tempSwap  = new byte[blockSizeInBytes];
      tempIn    = new byte[blockCnt * blockSizeInBytes];
      tempOut   = new byte[blockCnt * blockSizeInBytes];
      input.CopyTo(tempIn,0);
            
      // Decrypt second to last input block
      ecbAes.Mode = CipherMode.ECB;
      ecbAes.Padding = PaddingMode.None;
      ecbAes.Key = key;
      ecbAes.IV = iv;
      ms = new MemoryStream(input,(blockCnt-2)*blockSizeInBytes,blockSizeInBytes,false);
      cs = new CryptoStream(ms, ecbAes.CreateDecryptor(), CryptoStreamMode.Read);
      try
      {
        cs.Read(tempSwap,0,tempSwap.Length);
      }
      catch (Exception e)
      {
        Console.WriteLine(e.Message);
        return null;
      }
      finally
      {
        cs.Close();
        ms.Close();
      }
      
      // Append stolen ciphertext bytes from decrypted block to end of input
      int stolenByteCnt = (tempIn.Length - input.Length);
      Array.Copy(tempSwap,tempSwap.Length - stolenByteCnt,tempIn,tempIn.Length-stolenByteCnt,stolenByteCnt);
      
      // Swap last two blocks of ciphertext
      Array.Copy(tempIn,blockSizeInBytes*(blockCnt-2),tempSwap,0,blockSizeInBytes);
      Array.Copy(tempIn,blockSizeInBytes*(blockCnt-1),tempIn,blockSizeInBytes*(blockCnt-2),blockSizeInBytes);
      Array.Copy(tempSwap,0,tempIn,blockSizeInBytes*(blockCnt-1),blockSizeInBytes);
          
      // Do complete CBC encryption
      ms = new MemoryStream(tempIn, false);
      cs = new CryptoStream(ms, aes.CreateDecryptor(), CryptoStreamMode.Read);
      try
      {
        cs.Read(tempOut,0,tempOut.Length);  
      }
      catch (Exception e)
      {
        Console.WriteLine(e.Message);
        return null;
      }
      finally
      {
        cs.Close();
        ms.Close();
      }
      
      // Truncate to original input length
      Array.Copy(tempOut,0,output,0,input.Length);
      
      return output;
    }
  }
  /*
  public class CryptoStreamWithCTS : Stream
  {
    public CryptoStreamWithCTS(): base()
    {
    }
  }
  */
  
  public class AesManagedWithCTS : Aes
  {
  #region Private Class Member
    private AesManaged aes;
  
  #endregion
  
  #region Public Constructor
    public AesManagedWithCTS() : base()
    {
      aes = new AesManaged();
    }
  #endregion
  
  #region Public Override Properties
    public override CipherMode Mode
    {
      get
      {
        return this.ModeValue;
      }
      set
      {
        if (value != CipherMode.CTS)
          aes.Mode = value;
        else
          aes.Mode = CipherMode.CBC;
        ModeValue = value; 
      }
    }
    
    public override PaddingMode Padding
    {
      get
      {
        return aes.Padding;
      }
      set
      {
        aes.Padding = value;
        PaddingValue = aes.Padding;
      }
    }
    
    public override int FeedbackSize
    {
      get
      {
        return aes.FeedbackSize;
      }
      set
      {
        aes.FeedbackSize = value;
        FeedbackSizeValue = aes.FeedbackSize;
      }
    }
    
    public override byte[] IV
    {
      get
      {
        if (this.IVValue == null)
          GenerateIV();
          
        return IVValue;
      }
      set
      {
        if (value == null)
					throw new ArgumentNullException ("IV");
        aes.IV = value;
        this.IVValue = aes.IV;
      }
    }
    
    public override byte[] Key
    {
      get
      {
        if (this.KeyValue == null)
          GenerateKey();
         
        return (byte[]) this.KeyValue.Clone();
      }
      set
      {
        if (value == null)
					throw new ArgumentNullException ("Key");
        aes.Key = value;
        this.KeyValue = aes.Key;
      }
    }
    
    public override int KeySize
    {
      get
      {
        return aes.KeySize;
      }
      set
      {
        aes.KeySize = value;
        KeySizeValue = aes.KeySize;
      }
    }
  #endregion
  
  #region Public Override Functions
    public override ICryptoTransform CreateDecryptor()
    {
      if (this.Mode != CipherMode.CTS)
        return aes.CreateDecryptor();
      else
        return new AesManagedWithCTSTransform(aes, this.Mode, false);
    }
    
    public override ICryptoTransform CreateDecryptor(byte[] key, byte[] iv)
    {
      if (this.Mode != CipherMode.CTS)
        return aes.CreateDecryptor(key,iv);
      else
      {
        aes.Key = key;
        aes.IV = iv;
        return new AesManagedWithCTSTransform(aes, this.Mode, false);
      }
    }
    
    public override ICryptoTransform CreateEncryptor()
    {
      if (this.Mode != CipherMode.CTS)
        return aes.CreateEncryptor();
      else
        return new AesManagedWithCTSTransform(aes, this.Mode, true);
    }
    
    public override ICryptoTransform CreateEncryptor(byte[] key, byte[] iv)
    {
      if (this.Mode != CipherMode.CTS)
        return aes.CreateEncryptor(key,iv);
      else
      {
        aes.Key = key;
        aes.IV = iv;
        return new AesManagedWithCTSTransform(aes, this.Mode, true);
      }
    }

    public override void GenerateIV()
    {
      aes.GenerateIV();
      this.IVValue = aes.IV;
    }
    
    public override void GenerateKey()
    {
      aes.GenerateKey();
      this.KeyValue = aes.Key;
    }
  
  #endregion
  }
  
  internal class AesManagedWithCTSTransform: ICryptoTransform, IDisposable
  {
    protected CipherMode ModeValue;
    protected ICryptoTransform aesTransform;
    protected bool EncryptValue;
    
    private bool disposed;
    private bool flushed;
    
    // Public Class constructor
    public AesManagedWithCTSTransform(AesManaged aes, CipherMode mode, bool encrypt)
    {
      this.ModeValue = mode;
      this.EncryptValue = encrypt;
      if (mode == CipherMode.CTS)
      {
        // Use CBC for simple encryption, ECB for decryption
        if (encrypt)
          aes.Mode = CipherMode.CBC;
        else
          aes.Mode = CipherMode.ECB;
      }
      else
      {
        aes.Mode = mode;
      }
      
      if (encrypt)
      {
        aesTransform = aes.CreateEncryptor();
      }
      else
      {
        aesTransform = aes.CreateDecryptor();
      }
    
    }
    
    ~AesManagedWithCTSTransform () 
		{
			Dispose (false);
		}

    
  #region IDisposable interface implementation
    void IDisposable.Dispose () 
		{
			Dispose (true);
			GC.SuppressFinalize (this);
		}

  
    public virtual void Dispose(bool doDispose)
    {
      if (!disposed)
      {
        if (doDispose)
        {
        
        }
        disposed = true;
        
      }
      
      
    }
  #endregion
    
  
  #region ICryptoTransform interface implementation
    public int InputBlockSize
    {
      get
      {
        return aesTransform.InputBlockSize;
      }
    }
    
    public int OutputBlockSize
    {
      get
      {
        return aesTransform.OutputBlockSize;
      }
    }
    
    public bool CanReuseTransform
    {
      get
      {
        if (ModeValue == CipherMode.CTS)
        {
          return false;
        }
        else
        {
          return aesTransform.CanReuseTransform;
        }
      }
    }
    
    public bool CanTransformMultipleBlocks 
    {
      get
      {
        Console.WriteLine("CanTransformMultipleBlocks = {0}",CanTransformMultipleBlocks);
        if (ModeValue == CipherMode.CTS)
        {
          return true;
        }
        else
        {
          return aesTransform.CanTransformMultipleBlocks;
        }
      }
    }
    
    public virtual int TransformBlock(
      byte[] inputBuffer,
      int inputOffset,
      int inputCount,
      byte[] outputBuffer,
      int outputOffset )
    {
      if (disposed)
        throw new ObjectDisposedException ("Object is disposed");

      // Check input and output params
      Console.WriteLine("Called TransformBlock() with following params:");
      Console.WriteLine("\tinputBuffer.Length = {0}",inputBuffer.Length);
      Console.WriteLine("\tinputOffset = {0}",inputOffset);
      Console.WriteLine("\tinputCount = {0}",inputCount);
      Console.WriteLine("\toutputBuffer.Length = {0}",inputBuffer.Length);
      Console.WriteLine("\toutputOffset = {0}",outputOffset);
    
      if (this.ModeValue != CipherMode.CTS)
        return aesTransform.TransformBlock(inputBuffer, inputOffset, inputCount, outputBuffer, outputOffset);
      else
      {
        //if (EncryptValue)
        {
        // Implement the CTS using AES CBC
        int len = Math.Min(inputCount,(outputBuffer.Length - outputOffset));
        len = Math.Min(len,(inputBuffer.Length - inputOffset));
        Array.Copy( inputBuffer, inputOffset, outputBuffer, outputOffset, len);
        return len;
        }
      }
    }
    
    public virtual byte[] TransformFinalBlock (byte[] inputBuffer, int inputOffset, int inputCount) 
		{
			if (disposed)
				throw new ObjectDisposedException ("Object is disposed");
      
      if (flushed)
        return null;
        
      // Check input params
      Console.WriteLine("Called TransformFinalBlock() with following params:");
      Console.WriteLine("\tinputBuffer.Length = {0}",inputBuffer.Length);
      Console.WriteLine("\tinputOffset = {0}",inputOffset);
      Console.WriteLine("\tinputCount = {0}",inputCount);
      
      byte[] retVal = new byte[inputCount];
      
      Array.Copy( inputBuffer, inputOffset, retVal, 0, inputCount);
      
      flushed = true;
      
      return retVal;
		}
    

  #endregion
    public void Clear()
    {
      Dispose(true);
    }
    
  }
}