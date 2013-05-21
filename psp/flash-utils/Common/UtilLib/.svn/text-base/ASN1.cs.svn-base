using System;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Security.Cryptography;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading;

using UtilLib.IO;

namespace UtilLib
{
  // Public Enums for ASN1 class
  public enum Asn1TagClass : uint
  {
    UNIVERSAL = 0x00,
    APPLICATION = 0x01,
    CONTEXT_SPECIFIC = 0x02,
    PRIVATE = 0x03
  }
  
  public enum Asn1TagType : uint
  {
    PRIMITIVE = 0x00,
    CONSTRUCTED = 0x01
  }

  public enum Asn1TagNumber : uint
  {
    EOC             = 0x00,
    BOOLEAN         = 0x01,
    INTEGER         = 0x02,
    BITSTRING       = 0x03,
    OCTETSTRING     = 0x04,
    NULL            = 0x05,
    OID             = 0x06,
    SEQUENCE        = 0x10,
    SET             = 0x11,
    PRINTABLESTRING = 0x13,
    T61STRING       = 0x14,
    IA5STRING       = 0x16,
    UTCTIME         = 0x17,
    HIGHNUMBER      = 0x1F
  }
  
  public enum Asn1LengthType : uint
  {
    SHORT = 0x00,
    LONG_DEFINITE  = 0x01,
    LONG_INDEFINITE = 0x03
  }

  
  // Base ASN.1 Octet Field class - used as base for Tag and Length classes
  public class Asn1OctetField
  {
    // Private members
    private Byte[] octets;  
    private UInt32 octetFieldLength;
    
    // Public properties/indexer
    public Byte this [int index]
    {
      get { return octets[index]; }
    }
    
    public UInt32 OctetFieldLength
    {
      get { return octetFieldLength; }
    }
    
    // Public constructors
    public Asn1OctetField() : this((UInt32) 0)
    {
      octets = new Byte[16];
    }
    
    public Asn1OctetField(UInt32 length)
    {
      octetFieldLength = length;
      octets = new Byte[length];
    }
    
    // Protected read byte function
    protected Byte ReadByte(Stream dataStream)
    {
      Byte b = Convert.ToByte(dataStream.ReadByte());
      octetFieldLength++;
      if ( octetFieldLength > octets.Length)
      {
        Byte[] temp = new Byte[octets.Length * 2];
        octets.CopyTo(temp,0);
        octets = temp;
      }
      
      octets[octetFieldLength - 1] = b;
      
      return b;
    }
    
    public Byte[] ToArray()
    {
      Byte[] temp = new Byte[octetFieldLength];
      octets.CopyTo(temp,0);
      return temp;
    }
  }
  
  // Class for analyzing ASN.1 Identifier Octets in BER/CER/DER
  public class Asn1Tag : Asn1OctetField
  {
    // Private members
    private Asn1TagNumber tagNumber;
    private Asn1TagType   tagType;
    private Asn1TagClass  tagClass;

    
    // Public properties
    public Asn1TagNumber TagNumber
    {
      get{ return tagNumber; }
    }
    
    public Asn1TagType TagType
    {
      get{ return tagType; }
    }
    
    public Asn1TagClass TagClass
    {
      get{ return tagClass; }
    }
    
    
    // Public Constructors
    public Asn1Tag( Stream dataStream ) : base()
    {
      Byte b = ReadByte(dataStream);
      tagNumber = GetNumber(b);
      tagType   = GetType(b);
      tagClass  = GetClass(b);
      
      if (tagNumber == Asn1TagNumber.HIGHNUMBER)
      {
        UInt32 tagNo = 0;
        b = ReadByte(dataStream);
        if ((b & 0x7F) == 0x00)
          throw new IOException("Invalid tag number!");
        else
        {
          while ((b & 0x80) == 0x80)
          {
            // Get bits from intermdeiate octets
            tagNo |= (UInt32)(b & 0x7F);
            tagNo <<= 7; 
            // Read next byte from dataStream
            b = ReadByte(dataStream);
          }
          
          // Get bits from last octet
          tagNo |= (UInt32) (b & 0x7F);
        }
        tagNumber = (Asn1TagNumber) tagNo;
      }
      
    }
    
    public Asn1Tag( Byte[] dataBytes ) : this(new MemoryStream(dataBytes,false))
    {
    }

    
    // Public Static class methods
    public static Asn1TagNumber GetNumber(Byte tag)
    {
      tag = (Byte) ((tag >> 0) & 0x1F);
      if (Enum.IsDefined(typeof(Asn1TagNumber), (UInt32) tag)) 
        return (Asn1TagNumber) tag;
      else
        throw new ArgumentException(String.Format("Tag number, {0}, is not defined",tag));
    }
    
    public static Asn1TagType GetType(Byte tag)
    {
      tag = (Byte) ((tag >> 5) & 0x01);
      if (Enum.IsDefined(typeof(Asn1TagType), (UInt32) tag))
        return (Asn1TagType) tag;
      else
        throw new ArgumentException(String.Format("Tag type, {0}, is not defined",tag));
    }
    
    public static Asn1TagClass GetClass(Byte tag)
    {
      tag = (Byte) ((tag >> 6) & 0x03);
      if (Enum.IsDefined(typeof(Asn1TagClass), (UInt32) tag))
        return (Asn1TagClass) tag;
      else
        throw new ArgumentException(String.Format("Tag class, {0}, is not defined",tag));
    }

    
    // Static function to parse get the tag number from a data stream
    public static UInt32 ReadTagNumber(Stream dataStream)
    {
      return (UInt32) (new Asn1Tag(dataStream)).TagNumber;
    }
  }
  
  // Class for analyzing ASN.1 Length Octets in BER/CER/DER
  public class Asn1Length : Asn1OctetField
  {
    //  Private class variables
    private UInt32 length;
    private Asn1LengthType lengthType;
    
    
    // Public properties
    public UInt32 Length 
    {
      get { return length; }
    }
    
    public Asn1LengthType LengthType
    {
      get { return lengthType; }
    }
    
    // Public Constructors
    public Asn1Length( Stream dataStream ) : base()
    {
      Byte b = ReadByte(dataStream);
      
      if ((b & 0x80) == 0x00)
      {
        lengthType = Asn1LengthType.SHORT;
        // Short Form
        length = (UInt32) (b & 0x7F);
      }
      else
      {
        length = 0;
        // Long Form
        UInt32 numLengthOctets = (UInt32) (b & 0x7F);
        if (numLengthOctets == 0x00)
        {
          lengthType = Asn1LengthType.LONG_INDEFINITE;
        }
        else
        {
          lengthType = Asn1LengthType.LONG_DEFINITE;        
          while (numLengthOctets > 0)
          {
            b = ReadByte(dataStream);
            length <<= 8;
            length |= b;
            numLengthOctets--;
          }
        }
      }
    }
  
    public Asn1Length( Byte[] dataBytes ) : this(new MemoryStream(dataBytes,false))
    {
    }
    
    
    // Static function to read ASN.1 BER length value from data stream 
    public static UInt32 ReadLength(Stream dataStream)
    {
      return (UInt32) (new Asn1Length(dataStream)).Length;
    }
  }
  
  // Base ASN.1 Object class
  public class Asn1Object
  {
    // Private Members
    protected Asn1Tag identification;
    protected Asn1Length length;
    protected Stream contents;
    
    // Public Properties
    public Asn1Tag ContentID
    {
      get { return identification; }
      set { identification = value; }
    }
    
    public Asn1Length ContentLength
    {
      get { return length; }
      set { length = value; }
    }
    
    public Stream Contents
    {
      get { return contents; }
      set { contents = value; }
    }
    
    // Public contructos
    public Asn1Object()
    {
    }
    
    public Asn1Object(Byte[] asn1Data) : this(new MemoryStream(asn1Data, false))
    {
    }
    
    public Asn1Object(Stream asn1Stream)
    {
      if (!asn1Stream.CanRead) throw new ArgumentException("Input data stream must be readable!");
    
      // Get ID and Length from stream
      identification = new Asn1Tag(asn1Stream);
      length = new Asn1Length(asn1Stream);
     
      // Check if has definite length (only kind currently supported)
      if (length.LengthType == Asn1LengthType.LONG_INDEFINITE)
      {
        // Indefinite Length Streams (terminated by EOC)
        throw new ArgumentException("Indefinite length ASN.1 streams are not supported!");
      }
      else
      {
        // Definite length stream
        if (length.Length == 0)
          contents = null;
        else
        {
          // Create a new Stream containing just the contents bytes
          Byte[] bytesRead = new Byte[length.Length];
          asn1Stream.Read(bytesRead,(Int32)0,(Int32)length.Length);
          contents = new MemoryStream(bytesRead,false);
        }
      }
    }
    
    public Byte[] ContentsToArray()
    {
      if (Contents is MemoryStream)
        return ((MemoryStream) Contents).ToArray();
      else
      {
        Byte[] bytesRead = new Byte[length.Length];
        Contents.Seek(0,SeekOrigin.Begin);
        Contents.Read(bytesRead, (Int32)0, (Int32)length.Length);
        return bytesRead;
      }
    }
    
    public override String ToString()
    {
      UInt32 pos = 0,i=0;
      StringBuilder sb = new StringBuilder();
      
      sb.AppendFormat("{0,5}{1,5:X2}{2,5}: ",pos,ContentID[0],ContentLength.Length);
      sb.AppendFormat("{0} (Class={1},Type={2})\n",ContentID.TagNumber,ContentID.TagClass,ContentID.TagType);
      
      pos += (ContentID.OctetFieldLength + ContentLength.OctetFieldLength);
      
      for (i=0; i<ContentLength.Length; i+=16,pos+=16)
      {
        sb.AppendFormat("{0,5}{1,10:X2}: ",pos," ");
        if ( (ContentLength.Length - i) < 16)
          sb.AppendFormat("  {0}\n", BitConverter.ToString(this.ContentsToArray(),(Int32)i,(Int32)(ContentLength.Length - i)));
        else
          sb.AppendFormat("  {0}\n", BitConverter.ToString(this.ContentsToArray(),(Int32)i,16));
      }
      
      return sb.ToString();
    }
  }
  
  // ASN.1 Sequence Class, inheriting from base ASN.1 Object class
  public class Asn1Sequence : Asn1Object
  {
    // Private array reflecting the sequence of Asn1Object
    private Asn1Object[] seqElements;

    
    // Public indexer/properties
    public Asn1Object this [int index]
    {
      get { return seqElements[index]; }
    }

    public UInt32 SequenceLength
    {
      get { return ((UInt32) seqElements.Length); }
    }


    // Public Constructors
    public Asn1Sequence( Stream asn1Stream ) : base(asn1Stream)
    {
      if (identification.TagNumber != Asn1TagNumber.SEQUENCE)
      {
        throw new ArgumentException("Input data is not an ASN.1 Sequence!");
      }
      
      // Parse through the Sequence and generate array of Asn1Object's
      seqElements = ParseAsn1Sequence(contents, length.Length);
    }
    
    public Asn1Sequence( Byte[] asn1Data ) : base( asn1Data )
    {
      if (identification.TagNumber != Asn1TagNumber.SEQUENCE)
      {
        throw new ArgumentException("Input data is not an ASN.1 Sequence!");
      }
      
      // Parse through the Sequence and generate array of Asn1Object's
      seqElements = ParseAsn1Sequence(contents, length.Length);
    }
    
    public Asn1Sequence( Asn1Object asn1Obj )
    {
      if (asn1Obj.ContentID.TagNumber != Asn1TagNumber.SEQUENCE)
      {
        throw new ArgumentException("Input Object is not an ASN.1 Sequence!");
      }
      
      this.identification = asn1Obj.ContentID;
      this.length = asn1Obj.ContentLength;
      this.contents = asn1Obj.Contents;
      
      // Parse through the Sequence and generate array of Asn1Object's
      seqElements = ParseAsn1Sequence(contents,length.Length);
    }

    
    // Static class functions
    public static Asn1Object[] ParseAsn1Sequence(Byte[] asn1Data)
    {
      return ParseAsn1Sequence(new MemoryStream(asn1Data,false), (UInt32) asn1Data.Length);
    }
    
    public static Asn1Object[] ParseAsn1Sequence(Stream asn1Stream, UInt32 length)
    {
      Asn1Object myObj;
          
      // Create new generic list class for holding Asn1Objects
      List<Asn1Object> myList = new List<Asn1Object>();
      
      while (length > 0)
      {
        myObj = new Asn1Object(asn1Stream);   // Stream position is incremented in object creation
        myList.Add(myObj);
        length -= (myObj.ContentID.OctetFieldLength + myObj.ContentLength.OctetFieldLength + myObj.ContentLength.Length);
      }
      
      if (length != 0)
        throw new IOException("Amount of data parsed did not match amount available!");
            
      return myList.ToArray();
    }
    
  }
/*
  public class Asn1DERSequence : Asn1Sequence
  {
  
  }
  
  public class Asn1BERSequence : Asn1Sequence
  {
  
  }
  
  public class Asn1Set : Asn1Object
  {
  
  } */
}