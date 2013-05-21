/****************************************************************
 *  TI UtilLib.CRC namespace: CRC-32, CRC-16 code               *
 *  (C) 2008, Texas Instruments, Inc.                           *
 *                                                              *
 * Author:  Daniel Allred                                       *
 * Revision: 13-Jun-2008, added CRC-16 class and routines       *
 *                                                              * 
 ****************************************************************/

using System;
using System.Text;
using UtilLib;

namespace UtilLib.CRC
{
  public enum CRCCalcMethod : uint
  {
    LUT = 1,
    BITWISE =2
  }
  
  public enum CRCType : uint
  {
    ONESHOT = 1,
    INCREMENTAL = 2
  }
  
  public class CRC32
  {
    #region Data members

    private UInt32[] lut;
    private UInt32 poly = 0x04C11DB7; //Bit32 is 1 is always 1 and therefore not needed
    private UInt32 initReg = 0xFFFFFFFF;
    private UInt32 finalReg = 0xFFFFFFFF;
    private Boolean reflected = true; //follows hardware convention that receive bits in reverse order 
    private Int32 numBytesPerRegShift = 1;
    private UInt32 currCRC;
    private CRCType crcType = CRCType.INCREMENTAL;
    private CRCCalcMethod crcCalcMethod = CRCCalcMethod.LUT;

    #endregion

    #region Indexer and Properties
    
    public UInt32 this[int index]
    {
      get
      {
        if (crcCalcMethod == CRCCalcMethod.LUT)
          return lut[index];
        else
          return 0;
      }
    }
    
    public Int32 Length
    {
      get
      {
        if (crcCalcMethod == CRCCalcMethod.LUT)
          return lut.Length;
        else
          return 0;
      }
    }
    
    private Int32 NumBytesPerRegShift
    {
      get { return numBytesPerRegShift; }
      set { numBytesPerRegShift = ((value < 3) && (value > 0)) ? value : 1; }
    }

    public UInt32 CurrentCRC
    {
      get { return currCRC; }
      set { currCRC = value; }
    }
    
    public CRCType CrcType
    {
      get { return crcType;  }
      set { crcType = value; }
    }
    
    public CRCCalcMethod CrcCalcMethod
    {
      get { return crcCalcMethod;  }
      set { crcCalcMethod = value; }
    }
    
    #endregion

    #region Constructors
    /// <summary>
    /// Basic Constructor to generate the standard CRC-32 (used in ethernet packets, Zip files, etc.)
    /// </summary>
    public CRC32() : this(0x04C11DB7, CRCType.ONESHOT)
    {
    }
    
    /// <summary>
    /// Basic Constructor except with a different key (divisor) polynomial
    /// </summary>
    /// <param name="KeyPoly">The user-provided key polynomial (hex number of bits[31-0])</param>
    public CRC32(UInt32 KeyPoly) : this(KeyPoly, 0xFFFFFFFF, 0xFFFFFFFF, true, 1, CRCType.ONESHOT, CRCCalcMethod.LUT)
    {
    }

    /// <summary>
    /// Basic Constructor except with a different key (divisor) polynomial
    /// </summary>
    /// <param name="KeyPoly">The user-provided key polynomial (hex number of bits[31-0])</param>
    /// <param name="CrcType">Indicates whether CRC is incremental (incomplete) or oneshot (complete).</param>
    public CRC32(UInt32 KeyPoly, CRCType CrcType) : this(KeyPoly, 0xFFFFFFFF, 0xFFFFFFFF, true, 1, CrcType, CRCCalcMethod.LUT)
    {
    }

    /// <summary>
    /// Constructor for custom 32-bit CRC object - Don't use this unless you really know
    /// what the heck you are doing.
    /// </summary>
    /// <param name="KeyPoly">Custom key polynomial</param>
    /// <param name="InitialRegVal">Initial register value</param>
    /// <param name="FinalizeXorVal">Value that is xor'd with final CRC</param>
    /// <param name="Reflected">Indicates whether the algorithm expects reflected input bytes</param>
    /// <param name="BytesShiftedPerCycle">How many bytes are handled at a time (1 or 2).
    /// <param name="CrcType">Indicates whether CRC is incremental (incomplete) or oneshot (complete).</param>
    /// <param name="CrcCalcMethod">How many bytes are handled at a time (1 or 2).
    /// The internal table size is determined by this parameter, 1 is most common (leads to 1kbyte table).</param>
    public CRC32( UInt32 KeyPoly,
                  UInt32 InitialRegVal,
                  UInt32 FinalizeXorVal,
                  Boolean Reflected,
                  Int32 BytesShiftedPerCycle,
                  CRCType CrcType,
                  CRCCalcMethod CrcCalcMethod  )
    {
      lut = null;
      poly = KeyPoly;
      initReg = InitialRegVal;
      currCRC = initReg;
      finalReg = FinalizeXorVal;
      reflected = Reflected;
      NumBytesPerRegShift = BytesShiftedPerCycle;
      this.CrcType = CrcType;
      this.CrcCalcMethod = CrcCalcMethod;
      
      // Build the look up table
      BuildTable();
      
      // Call reset to set initial value for currCRC;
      ResetCRC();
    }
    #endregion

    #region Table building method used by Constructors
    /// <summary>
    /// Function to generate the table of values used in the CRC-32 calculation
    /// </summary>
    private void BuildTable()
    {
      Int32 NumBitsPerRegShift = NumBytesPerRegShift*8;
      Int32 tableLen = (Int32) Math.Pow(2.0,NumBitsPerRegShift);
      UInt32 crcAccum;
      lut = new UInt32[tableLen];

      if (reflected)
      {
        for (UInt32 i = 0; i < tableLen; i++)
        {
          crcAccum = ReflectNum(i, NumBitsPerRegShift) << (32 - NumBitsPerRegShift);
          for (Byte j = 0; j < NumBitsPerRegShift; j++)
          {
            if ((crcAccum & 0x80000000) != 0x00000000)
            {
              crcAccum = (crcAccum << 1) ^ poly;
            }
            else
            {
              crcAccum = (crcAccum << 1);
            }
            lut[i] = ReflectNum(crcAccum, 32);
          }
        }
      }
      else
      {
        for (UInt32 i = 0; i < tableLen; i++)
        {
          crcAccum = i << (32 - NumBitsPerRegShift);
          for (Byte j = 0; j < NumBitsPerRegShift; j++)
          {
            if ((crcAccum & 0x80000000) != 0x00000000)
            {
              crcAccum = (crcAccum << 1) ^ poly;
            }
            else
            {
              crcAccum = (crcAccum << 1);
            }
            lut[i] = crcAccum;
          }
        }
      }
    }
    #endregion
                                       
    #region Public Methods
    
    /// <summary>
    /// Calculate the CRC-32 checksum on the given array of bytes
    /// </summary>
    /// <param name="Data">Array of bytes of data.</param>
    /// <returns>The 32-bit CRC of the data.</returns>
    public UInt32 CalculateCRC(Byte[] Data)
    {
      return CalculateCRC(Data,0,Data.Length);
    }

    /// <summary>
    /// Calculate the CRC-32 checksum on the given array of bytes
    /// </summary>
    /// <param name="Data">The input byte array.</param>
    /// <param name="offset">The offset into the Byte array.</param>
    /// <param name="count">The number of bytes to use for the CRC calculation.</param>
    /// <returns>CRC32 value.</returns>
    public UInt32 CalculateCRC(Byte[] Data, int offset, int count)
    {
      if ( CrcType == CRCType.ONESHOT )
      {
        currCRC = initReg;
        if ( CrcCalcMethod == CRCCalcMethod.LUT)
          currCRC = LUTBasedCRC(Data, offset, count);
        else
          currCRC = BitWiseCRC(Data, offset, count);
      }
      else
      {
        currCRC = currCRC ^ finalReg;   // undo XOR from last calculation
        if ( CrcCalcMethod == CRCCalcMethod.LUT)
          currCRC = LUTBasedCRC(Data, offset, count);
        else
          currCRC = BitWiseCRC(Data, offset, count);
      }
      
      // Prep CRC for output
      currCRC = currCRC ^ finalReg;

      return (currCRC);
    }
    

    /// <summary>
    /// Calculate the CRC-32 checksum using LUT.
    /// </summary>
    /// <param name="Data">The input byte array.</param>
    /// <param name="offset">The offset into the Byte array.</param>
    /// <param name="count">The number of bytes to use for the CRC calculation.</param>
    /// <returns>CRC32 value.</returns>
    private UInt32 LUTBasedCRC(Byte[] Data, int offset, int count)
    {
      UInt32 crc = currCRC;
      Int32 len = count;
      Int32 NumBitsPerRegShift = NumBytesPerRegShift * 8;
      UInt32 Mask = (UInt32)(Math.Pow(2.0, NumBitsPerRegShift) - 1);
      
      Debug.DebugMSG("LUT-Based CRC, NumBitsPerRegShift = {0}, Refelected = {1}",NumBitsPerRegShift,reflected);
      Debug.DebugMSG("Offset = {0}, length = {1}",offset,count);
      Debug.DebugMSG("Interim Calculated CRC = 0x{0:X8}",crc);

      // Perform the algorithm on each byte
      if (reflected)
      {
        if (NumBytesPerRegShift == 2)
        {
          for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
          {
            crc = (crc >> NumBitsPerRegShift) ^ lut[(crc & Mask) ^ ((Data[2 * i + 1 + offset] << 8) | Data[2 * i + offset])];
          }
        }
        else
        {
          for (Int32 i = 0; i < len; i++)
          {
            crc = (crc >> NumBitsPerRegShift) ^ lut[(crc & Mask) ^ Data[offset+i]];
            Debug.DebugMSG("Data = {0:X2},Index = {1},Interim Calculated CRC = 0x{2:X8}",Data[offset+i],(crc & Mask) ^ Data[offset+i],crc);
          }
        }
      }
      else
      {
        if (NumBytesPerRegShift == 2)
        {
          for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
          {
            crc = (crc << NumBitsPerRegShift) ^ lut[((crc >> (32 - NumBitsPerRegShift)) & Mask) ^ ((Data[2 * i + offset] << 8) | Data[2 * i + 1 + offset])];
          }
        }
        else
        {
          for (Int32 i = 0; i < len; i++)
          {
            crc = (crc << NumBitsPerRegShift) ^ lut[((crc >> (32 - NumBitsPerRegShift)) & Mask) ^ Data[offset+i]];
            Debug.DebugMSG("Data = {0:X2},Index = {1},Interim Calculated CRC = 0x{2:X8}",Data[offset+i],(crc & Mask) ^ Data[offset+i],crc);
          }
        }
      }
      return crc;
    }
    
    /// <summary>
    /// Calculate the CRC-32 checksum using simple, inefficient bit wise operations.
    /// </summary>
    /// <param name="Data">The input byte array.</param>
    /// <param name="offset">The offset into the Byte array.</param>
    /// <param name="count">The number of bytes to use for the CRC calculation.</param>
    /// <returns>CRC32 value.</returns>
    private UInt32 BitWiseCRC(Byte[] Data, int offset, int count)
    {
      UInt32 crc = initReg;
      Int32 len = Data.Length;
      Int32 NumBitsPerRegShift = NumBytesPerRegShift * 8;
      UInt32 Mask = (UInt32)(Math.Pow(2.0, NumBitsPerRegShift) - 1);

      // Perform the algorithm on each byte
      if (NumBytesPerRegShift == 2)
      {
        for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
        {
          crc = ((crc << NumBitsPerRegShift) + (UInt32)((Data[2 * i] << 8) | Data[2 * i + 1])) ^ lut[((crc >> (32 - NumBitsPerRegShift)) & Mask)];
        }
      }
      else
      {
        for (Int32 i = 0; i < len; i++)
        {
          crc = ((crc << NumBitsPerRegShift) + Data[i]) ^ lut[((crc >> (32 - NumBitsPerRegShift)) & Mask)];
        }
      }
      // Exclusive OR the result with the specified value
      currCRC = (crc ^ finalReg);
      return currCRC;
    }
    
    public void ResetCRC()
    {
      if ( this.CrcType == CRCType.ONESHOT )
        currCRC = initReg;
      else
        // Must do this since incremental calc always
        // "un"-XORs the previous calculations final XOR.
        currCRC = initReg ^ finalReg; 
    }

    /// <summary>
    /// Method to reflect a specified number of bits in the integer
    /// </summary>
    /// <param name="inVal">The unsigned integer value input</param>
    /// <param name="num">The number of lower bits to reflect.</param>
    /// <returns></returns>
    public UInt32 ReflectNum(UInt32 inVal, Int32 num)
    {
        UInt32 outVal = 0x0;

        for (Int32 i = 1; i < (num + 1); i++)
        {
            if ((inVal & 0x1) != 0x0)
            {
                outVal |= (UInt32)(0x1 << (num - i));
            }
            inVal >>= 1;
        }
        return outVal;
    }
            
    #endregion


  }

    public class CRC16
    {
        #region Data members

        private UInt16[] lut;
        private UInt16 poly = 0x8005; //Bit32 is 1 is always 1 and therefore not needed
        private UInt16 initReg = 0xFFFF;
        private UInt16 finalReg = 0xFFFF;
        private Boolean reflected = true; //follows hardware convention that receive bits in reverse order 
        private Int32 numBytesPerRegShift = 1;
        private UInt16 currCRC;

        #endregion

        #region Indexer and Properties
        
        public UInt32 this[int index]
        {
            get{
                return lut[index];
            }
        }
        
        public Int32 Length
        {
            get{
                return lut.Length;
            }
        }
        
        private Int32 NumBytesPerRegShift
        {
            get { return numBytesPerRegShift; }
            set { numBytesPerRegShift = ((value < 3) && (value > 0)) ? value : 1; }
        }

        public UInt16 CurrentCRC
        {
            get { return currCRC; }
            set { currCRC = value; }
        }
        
        #endregion

        #region Constructors
        /// <summary>
        /// Basic Constructor to generate the standard CRC-16 (used in ethernet packets, Zip files, etc.)
        /// </summary>
        public CRC16()
        {
            poly = 0x8005; //Bit32 is 1 by default
            initReg = 0xFFFF;
            finalReg = 0xFFFF;
            currCRC = initReg;
            reflected = true; //follows hardware convention that receive bits in reverse order 
            numBytesPerRegShift = 1;
            BuildTable();
        }

        /// <summary>
        /// Basic Constructor except with a different key (divisor) polynomial
        /// </summary>
        /// <param name="KeyPoly">The user-provided key polynomial (hex number of bits[15-0])</param>
        public CRC16(UInt16 KeyPoly)
        {
            poly = KeyPoly;
            currCRC = initReg;
            BuildTable();
        }

        /// <summary>
        /// Constructor for custom 16-bit CRC object - Don't use this unless you really know
        /// what the heck you are doing.
        /// </summary>
        /// <param name="KeyPoly">Custom key polynomial</param>
        /// <param name="InitialRegVal">Initial register value</param>
        /// <param name="FinalizeXorVal">Value that is xor'd with final CRC</param>
        /// <param name="Reflected">Indicates whether the algorithm expects reflected input bytes</param>
        /// <param name="BytesShiftedPerCycle">How many bytes are handled at a time (1 or 2).
        /// The internal table size is determined by this parameter, 1 is most common (leads to 512 byte table).</param>
        public CRC16(UInt16 KeyPoly,
            UInt16 InitialRegVal,
            UInt16 FinalizeXorVal,
            Boolean Reflected,
            Int32 BytesShiftedPerCycle)
        {
            poly = KeyPoly;
            initReg = InitialRegVal;
            currCRC = initReg;
            finalReg = FinalizeXorVal;
            reflected = Reflected;
            NumBytesPerRegShift = BytesShiftedPerCycle;
            BuildTable();
        }
        #endregion

        #region Table building method used by Constructors
        /// <summary>
        /// Function to generate the table of values used in the CRC-32 calculation
        /// </summary>
        private void BuildTable()
        {
            Int32 NumBitsPerRegShift = NumBytesPerRegShift*8;
            Int32 tableLen = (Int32) Math.Pow(2.0,NumBitsPerRegShift);
            UInt16 crcAccum;
            lut = new UInt16[tableLen];

            if (reflected)
            {
                for (UInt16 i = 0; i < tableLen; i++)
                {
                    crcAccum = (UInt16) (ReflectNum(i, NumBitsPerRegShift) << (16 - NumBitsPerRegShift));
                    for (Byte j = 0; j < NumBitsPerRegShift; j++)
                    {
                        if ((crcAccum & 0x8000) != 0x0000)
                        {
                            crcAccum = (UInt16) ((crcAccum << 1) ^ poly);
                        }
                        else
                        {
                            crcAccum = (UInt16) (crcAccum << 1);
                        }
                        lut[i] = ReflectNum(crcAccum, 16);
                    }
                }
            }
            else
            {
                for (UInt16 i = 0; i < tableLen; i++)
                {
                    crcAccum = (UInt16) (i << (16 - NumBitsPerRegShift));
                    for (Byte j = 0; j < NumBitsPerRegShift; j++)
                    {
                        if ((crcAccum & 0x8000) != 0x0000)
                        {
                            crcAccum = (UInt16) ((crcAccum << 1) ^ poly);
                        }
                        else
                        {
                            crcAccum = (UInt16) (crcAccum << 1);
                        }
                        lut[i] = crcAccum;
                    }
                }
            }
        }
        #endregion
                                       
        #region Public Methods
        
        /// <summary>
        /// Calculate the CRC-32 checksum on the given array of bytes
        /// </summary>
        /// <param name="Data">Array of bytes of data.</param>
        /// <returns>The 32-bit CRC of the data.</returns>
        public UInt16 CalculateCRC(Byte[] Data)
        {
            UInt16 crc = initReg;
            Int32 len = Data.Length;
            Int32 NumBitsPerRegShift = NumBytesPerRegShift * 8;
            UInt16 Mask = (UInt16)(Math.Pow(2.0, NumBitsPerRegShift) - 1);

            // Perform the algorithm on each byte
            if (reflected)
            {
                if (NumBytesPerRegShift == 2)
                {
                    for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
                    {
                        crc = (UInt16) ((crc >> NumBitsPerRegShift) ^ lut[(crc & Mask) ^ ((Data[2 * i + 1] << 8) | Data[2 * i])]);
                    }
                }
                else
                {
                    for (Int32 i = 0; i < len; i++)
                    {
                        crc = (UInt16) (((UInt16)(crc >> NumBitsPerRegShift)) ^ ((UInt16) lut[(crc & Mask) ^ Data[i]]));
                    }
                }
            }
            else
            {
                if (NumBytesPerRegShift == 2)
                {
                    for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
                    {
                        crc = (UInt16) ((crc << NumBitsPerRegShift) ^ lut[((crc >> (16 - NumBitsPerRegShift)) & Mask) ^ ((Data[2 * i] << 8) | Data[2 * i + 1])]);
                    }
                }
                else
                {
                    for (Int32 i = 0; i < len; i++)
                    {
                        crc = (UInt16) ((crc << NumBitsPerRegShift) ^ lut[((crc >> (16 - NumBitsPerRegShift)) & Mask) ^ Data[i]]);
                    }
                }
            }
            // Exclusive OR the result with the specified value
            currCRC = (UInt16) (crc ^ finalReg);
            return currCRC;
        }

        /// <summary>
        /// Calculate the CRC-32 checksum.
        /// </summary>
        /// <param name="Data">The input byte array.</param>
        /// <param name="offset">The offset into the Byte array.</param>
        /// <param name="count">The number of bytes to use for the CRC calculation.</param>
        /// <returns>CRC32 value.</returns>
        public UInt16 CalculateCRC(Byte[] Data, int offset, int count)
        {
            UInt16 crc = initReg;
            Int32 len = count;
            Int32 NumBitsPerRegShift = NumBytesPerRegShift * 8;
            UInt16 Mask = (UInt16)(Math.Pow(2.0, NumBitsPerRegShift) - 1);

            // Perform the algorithm on each byte
            if (reflected)
            {
                if (NumBytesPerRegShift == 2)
                {
                    for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
                    {
                        crc = (UInt16)((crc >> NumBitsPerRegShift) ^ lut[(crc & Mask) ^ ((Data[2 * i + 1 + offset] << 8) | Data[2 * i + offset])]);
                    }
                }
                else
                {
                    for (Int32 i = 0; i < len; i++)
                    {
                        crc = (UInt16)((crc >> NumBitsPerRegShift) ^ lut[(crc & Mask) ^ Data[offset+i]]);
                    }
                }
            }
            else
            {
                if (NumBytesPerRegShift == 2)
                {
                    for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
                    {
                        crc = (UInt16) ((crc << NumBitsPerRegShift) ^ lut[((crc >> (16 - NumBitsPerRegShift)) & Mask) ^ ((Data[2 * i + offset] << 8) | Data[2 * i + 1 + offset])]);
                    }
                }
                else
                {
                    for (Int32 i = 0; i < len; i++)
                    {
                        crc = (UInt16) ((crc << NumBitsPerRegShift) ^ lut[((crc >> (16 - NumBitsPerRegShift)) & Mask) ^ Data[offset+i]]);
                    }
                }
            }
            // Exclusive OR the result with the specified value
            currCRC = (UInt16) (crc ^ finalReg);
            return currCRC;
        }

        public UInt16 SimpleCRC(Byte[] Data)
        {
            UInt16 crc = initReg;
            Int32 len = Data.Length;
            Int32 NumBitsPerRegShift = NumBytesPerRegShift * 8;
            UInt16 Mask = (UInt16)(Math.Pow(2.0, NumBitsPerRegShift) - 1);

            // Perform the algorithm on each byte
            if (NumBytesPerRegShift == 2)
            {
                for (Int32 i = 0; i < (len / NumBytesPerRegShift); i++)
                {
                    crc = (UInt16) (((crc << NumBitsPerRegShift) + (UInt16)((Data[2 * i] << 8) | Data[2 * i + 1])) ^ lut[((crc >> (16 - NumBitsPerRegShift)) & Mask)]);
                }
            }
            else
            {
                for (Int32 i = 0; i < len; i++)
                {
                    crc = (UInt16) (((crc << NumBitsPerRegShift) + Data[i]) ^ lut[((crc >> (16 - NumBitsPerRegShift)) & Mask)]);
                }
            }
            // Exclusive OR the result with the specified value
            currCRC = (UInt16) (crc ^ finalReg);
            return currCRC;
        }

        public UInt16 IncrementalCRC(Byte[] Data)
        {
            UInt16 temp = initReg;
            initReg = (UInt16) (currCRC ^ finalReg);
            CalculateCRC(Data);
            initReg = temp;
            return currCRC;
        }

        /// <summary>
        /// Incrementally calculate the CRC using the result of the previous CRC calculation.
        /// </summary>
        /// <param name="Data">The input byte array.</param>
        /// <param name="offset">The offset into the Byte array.</param>
        /// <param name="count">The number of bytes to use for the CRC calculation.</param>
        /// <returns>The current incremental CRC32 value.</returns>
        public UInt16 IncrementalCRC(Byte[] Data, int offset, int count)
        {
            UInt16 temp = initReg;
            initReg = (UInt16)(currCRC ^ finalReg);
            CalculateCRC(Data,offset,count);
            initReg = temp;
            return currCRC;
        }

        public UInt16 IncrementalSimpleCRC(Byte[] Data)
        {
            UInt16 temp = initReg;
            initReg = currCRC;
            SimpleCRC(Data);
            initReg = temp;
            return currCRC;
        }
        
        public void ResetCRC()
        {
            currCRC = initReg;
        }

        /// <summary>
        /// Method to reflect a specified number of bits in the integer
        /// </summary>
        /// <param name="inVal">The unsigned integer value input</param>
        /// <param name="num">The number of lower bits to reflect.</param>
        /// <returns></returns>
        public UInt16 ReflectNum(UInt16 inVal, Int32 num)
        {
            UInt16 outVal = 0x0;

            for (Int32 i = 1; i < (num + 1); i++)
            {
                if ((inVal & 0x1) != 0x0)
                {
                    outVal |= (UInt16)(0x1 << (num - i));
                }
                inVal >>= 1;
            }
            return outVal;
        }
                
        #endregion
    }    
}
