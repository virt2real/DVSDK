/* --------------------------------------------------------------------------
    FILE        : ECC.cs
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
    DESC        : Error Correction Code calculators for EMIF interfaces
 ----------------------------------------------------------------------------- */

using System;
using System.Collections.Generic;
using System.Text;

namespace UtilLib
{

    public class HammingECC
    {
      
      // *************************************************
      // *              Consts and Enums                 *
      // *************************************************   
      
      private enum colMasks: byte
      {
        evenWhole  = 0xFF,
        evenHalf   = 0x0F,
        oddHalf    = 0xF0,
        evenFourth = 0x33,
        oddFourth  = 0xCC,
        evenEighth = 0x55,
        oddEighth  = 0xAA,
        oddWhole   = 0x00
      }
      
      
      // *************************************************
      // *               Private Members                 *
      // *************************************************
      
      // Total number of message symbols
      private Int32 k;
      
      
      // *************************************************
      // *            Private Constructors               *
      // *************************************************
      
      
      // *************************************************
      // *               Private Methods                 *
      // *************************************************

      
      // *************************************************
      // *        Public properties and Indexer          *
      // *************************************************


      // *************************************************
      // *             Public constructors               *
      // *************************************************
      
      
      public HammingECC(Int32 messageCnt)
      {
        k = messageCnt;
      }
      
      
      // *************************************************
      // *           Public Instance Methods             *
      // *************************************************      

      // Single Bit ECC algorithm
      public Int32 GenerateParity(Byte[] messageData)
      {
        UInt16 oddResult=0, evenResult=0;
        Byte bitParities = 0;
        Byte[] byteParities = new Byte[k];
        
        if (messageData.Length != k)
          throw new ArgumentException("Wrong size.","messageData");

        // Create column parities
        for (int i = 0; i < k; i++)
        {
          bitParities ^= messageData[i];
        }
        
        evenResult |= (UInt16)( (CalcBitWiseParity(bitParities,colMasks.evenHalf) << 2) |
                        (CalcBitWiseParity(bitParities,colMasks.evenFourth) << 1) |
                        (CalcBitWiseParity(bitParities,colMasks.evenEighth) << 0) );

        oddResult |=  (UInt16)( (CalcBitWiseParity(bitParities,colMasks.oddHalf) << 2) |
                       (CalcBitWiseParity(bitParities,colMasks.oddFourth) << 1) |
                       (CalcBitWiseParity(bitParities,colMasks.oddEighth) << 0) );
                       
        // Create row Parities
        for (int i = 0; i < k; i++)
        {
          byteParities[i] = CalcBitWiseParity(messageData[i],colMasks.evenWhole);
        }

        // Place even row parity bits
        for (int i = 0; i < ((Int32) Math.Log(k,2)); i++ )
        {
          Byte val = CalcRowParityBits(byteParities, true, (Int32) Math.Pow(2,i));
          evenResult |= (UInt16) (val << (3+i));

          val = CalcRowParityBits(byteParities, false, (Int32) Math.Pow(2,i));
          oddResult  |= (UInt16) (val << (3+i));
        }
        
        return (Int32) ((oddResult << 16) | (evenResult));
      }
      
      
      // *************************************************
      // *             Public Class Methods              *
      // *************************************************      
        
      private static Byte CalcBitWiseParity(Byte val, colMasks mask)
      {
        Byte result = 0, byteMask = (Byte) mask;
        
        for (int i = 0; i < 8; i++)
        {
          if ((byteMask & 0x1) != 0)
          {
            result ^= (Byte)(val & 1);
          }
          byteMask >>= 1;
          val >>= 1;
        }
        return (Byte)(result & 0x1);
      }
  
      private static Byte CalcRowParityBits(Byte[] byteParities, Boolean even, Int32 chunkSize)
      {
        Byte result = 0;
        for (int i = (even ? 0 : chunkSize); i < byteParities.Length; i += (2*chunkSize))
        {
          for (int j = 0; j < chunkSize; j++)
          {
            result ^= byteParities[i + j];
          }
        }
        return (Byte)(result & 0x1);
      }
    }
  
    public class ReedSolomonECC
    {
      // *************************************************
      // *              Consts and Enums                 *
      // *************************************************    

      
      // *************************************************
      // *               Private Members                 *
      // *************************************************
      
      // Total number of transmitted symbols (message + parity)
      private Int32 N;
      
      // Total number of message symbols
      private Int32 k;
      
      // Total number of correctible symbol errors
      private Int32 s;
      
      // Array of BinaryGaloisFieldElement for building and storing the generator polynomial 
      private BinaryGaloisFieldElement[] generatorPoly;
      
      // The BinaryGaloisField under which all operations take place
      private BinaryGaloisField galoisField;
      
      
      // *************************************************
      // *            Private Constructors               *
      // *************************************************
      
      
      // *************************************************
      // *               Private Methods                 *
      // *************************************************

      
      // *************************************************
      // *        Public properties and Indexer          *
      // *************************************************


      // *************************************************
      // *             Public constructors               *
      // *************************************************

      public ReedSolomonECC(Int32 msgSymbolCnt, Int32 maxCorrectibleErrorCnt, Byte symbolBitWidth)
      {
        k = msgSymbolCnt;
        s = maxCorrectibleErrorCnt;
        N = k + 2*s;
        
        // Create Binary Galois Field ( that is GF(2^symbolBitWidth) )
        galoisField = new BinaryGaloisField(symbolBitWidth);
        
        // Create the generator polynomial, g(x)
        generatorPoly = ReedSolomonECC.createGeneratorPolynomial(galoisField, maxCorrectibleErrorCnt);
      }
      

      // *************************************************
      // *           Public Instance Methods             *
      // *************************************************      
      
      public Int32[] GenerateParity(Int32[] messageData)
      {
        Int32[] retArray = new Int32[2*s];
        BinaryGaloisFieldElement[] data = new BinaryGaloisFieldElement[N];
      
        if (messageData.Length != k)
          throw new ArgumentException("Wrong size.","messageData");

        // Parity is defined parityPoly(x) = x^2s * messagePoly(x) (mod generatorPoly(x))
        // Convert input message data to array of BinaryGaloisFieldElement (implicit cast)
        // Create x^2s * messagePoly(x) by shifting data up by 2s positions
        for (int i=0; i<k; i++)
        {
          data[i+(2*s)] = messageData[i];
        }
        
        // Now do long division using generatorPoly, remainder is parity data
        // Use synthetic division since generatorPoly is monic
        for(int i = N - 1; i >=(2*s); i--)
        {
          if (data[i] != 0)
          {
            for (int j = 1; j <= (2*s); j++)
            {
              data[i - j] = data[i - j] - galoisField.Multiply(data[i],generatorPoly[2*s - j]);
            }
            // Set to zero
            data[i] = 0;
          }
        }
        
        // Copy 2*s pieces of data to the parity symbols array
        for (int i=0; i<(2*s); i++)
        {
          retArray[i] = (Int32) data[i];
        }
        
        // Return parity symbols
        return retArray;
      }
      
      
      // *************************************************
      // *             Public Class Methods              *
      // *************************************************
      
      public static BinaryGaloisFieldElement[] createGeneratorPolynomial(BinaryGaloisField gf, Int32 maxCorrectibleErrorCnt)
      {
        // Generator polynomial, g(x), is of order 2s, so has 2s+1 coefficients
        BinaryGaloisFieldElement[] g = new BinaryGaloisFieldElement[2*maxCorrectibleErrorCnt + 1];
        
        // Make g(x) = 1
        g[0] = 1;
        for (int i = 1; i<=(2*maxCorrectibleErrorCnt); i++)
        {
          // Always make coefficient of x^i term equal to 1
          g[i] = 1;
          
          // Below multiply (g(x) = g[0] + g[1]*x + ... + g[i]*(x^i)) by (x - alpha^i)
          for (int j=(i-1); j > 0; j--)
          {
            if (g[j] != 0)
              g[j] = g[j - 1] - gf.Multiply(gf.AlphaFromIndex(i),g[j]);
            else
              g[j] = g[j - 1];
          }
          // Coefficient of x^0 term is alpha^(1+2+...+i)
          g[0] = gf.AlphaFromIndex( ((i*(i+1))/2) );
        }
        return g;
      }
      
      
      // *************************************************
      // *               Public operators                *
      // *************************************************
      
    }      
        

    public struct BinaryGaloisFieldElement
    {
      // *************************************************
      // *              Consts and Enums                 *
      // *************************************************
      
      
      // *************************************************
      // *               Private Members                 *
      // *************************************************      

      private Int32 value;      
     
      
      // *************************************************
      // *            Private Constructors               *
      // *************************************************
      
      // Private instance constructor. Creates a BinaryGaloisFieldElement
      // with a known value.
      private BinaryGaloisFieldElement(Int32 value)
      {
        this.value = value;
      }
      
      
      // *************************************************
      // *               Private Methods                 *
      // *************************************************      


      // *************************************************
      // *        Public properties and Indexer          *
      // *************************************************

      // The Value property is the known value of this BinaryGaloisFieldElement, or 0 if this
      // BinaryGaloisFieldElement represents an unknown value.
      public int Value
      { 
        get { return value; }
      }

      
      // *************************************************
      // *             Public constructors               *
      // *************************************************      

      
      // *************************************************
      // *                Public methods                 *
      // *************************************************
      
      public static Int32 Order(BinaryGaloisFieldElement x)
      {
        UInt32 Mask = 0x80000000;
        Int32 order = 31;
        
        while (((x.Value & Mask) == 0x0) && (order > 0))
        {
          Mask >>= 1;
          order--;
        }
        
        return order;
      }

      
      // *************************************************
      // *               Public operators                *
      // *************************************************
      
      // Implicit conversion from int to BinaryGaloisFieldElement.
      public static implicit operator BinaryGaloisFieldElement(Int32 x) 
      {
        return new BinaryGaloisFieldElement(x);
      }
      
      public static implicit operator BinaryGaloisFieldElement(Int16 x) 
      {
        return new BinaryGaloisFieldElement((Int32)x);
      }      
      
      public static implicit operator BinaryGaloisFieldElement(SByte x) 
      {
        return new BinaryGaloisFieldElement((Int32)x);
      }
      
      public static implicit operator BinaryGaloisFieldElement(UInt32 x) 
      {
        return new BinaryGaloisFieldElement((Int32)x);
      }
      
      public static implicit operator BinaryGaloisFieldElement(UInt16 x) 
      {
        return new BinaryGaloisFieldElement((Int32)x);
      }      
      
      public static implicit operator BinaryGaloisFieldElement(Byte x) 
      {
        return new BinaryGaloisFieldElement((Int32)x);
      }            

      // Explicit conversion from BinaryGaloisFieldElement to int. Throws an exception if the
      // given BinaryGaloisFieldElement represents an unknown value.
      public static explicit operator Int32(BinaryGaloisFieldElement x)
      {
        return x.value;
      }
   
      // Unary + operator
      public static BinaryGaloisFieldElement operator +(BinaryGaloisFieldElement x)
      {
        return x;
      }

      // Unary - operator
      public static BinaryGaloisFieldElement operator -(BinaryGaloisFieldElement x)
      {
        return x;
      }

      public static BinaryGaloisFieldElement operator +(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return x^y;
      }

      public static BinaryGaloisFieldElement operator -(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return x^y;
      }
      
      public static BinaryGaloisFieldElement operator ^(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value ^ y.value);
      }
      
      public static BinaryGaloisFieldElement operator &(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value & y.value);
      }
      
      public static BinaryGaloisFieldElement operator |(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value | y.value);
      }

      public static BinaryGaloisFieldElement operator <<(BinaryGaloisFieldElement x, Int32 y)
      {
        return (x.value << y);
      }
      
      public static BinaryGaloisFieldElement operator >>(BinaryGaloisFieldElement x, Int32 y)
      {
        return (x.value >> y);
      }

/*
      public static BinaryGaloisFieldElement operator *(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.defined && y.defined) ? x.value * y.value: Null;
      }

      public static BinaryGaloisFieldElement operator /(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.defined && y.defined) ? x.value / y.value: Null;
      }

      public static BinaryGaloisFieldElement operator %(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.defined && y.defined) ? x.value % y.value: Null;
      }
*/


      public static Boolean operator ==(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value == y.value);
      }

      public static Boolean operator !=(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value != y.value);
      }

      public static Boolean operator >(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value > y.value);
      }

      public static Boolean operator <(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value < y.value);
      }

      public static Boolean operator >=(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value >= y.value);
      }

      public static Boolean operator <=(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        return (x.value <= y.value);
      }

      public override Boolean Equals(object obj)
      {
        if (!(obj is BinaryGaloisFieldElement)) 
          return false;
        BinaryGaloisFieldElement x = (BinaryGaloisFieldElement)obj;
        return ((value == x.value));
      }

      public override Int32 GetHashCode()
      {
        return value;
      }

      public override String ToString()
      {
        return Convert.ToString(value,2);
      }
    }
    
    public class BinaryGaloisField
    {
      // *************************************************
      // *              Consts and Enums                 *
      // *************************************************
    
      // Lee & Messerschmitt, p. 453
      private static readonly Int32[] primPoly = new Int32[]
      {
        0x00000000, // 0-th element is don't care
        0x00000000, // 1-st element is don't care
        0x00000007, // 2-nd: poly = x^2 + x + 1
        0x0000000B, // 3-rd: poly = x^3 + x + 1
        0x00000013, // 4-th: poly = x^4 + x + 1
        0x00000025, // 5-th: poly = x^5 + x^2 + 1
        0x00000043, // 6-th: poly = x^6 + x + 1
        0x00000089, // 7-th: poly = x^7 + x^3 + 1
        0x0000011D, // 8-th: poly = x^8 + x^4 + x^3 + x^2 + 1
        0x00000211, // 9-th: poly = x^9 + x^4 + 1        
        0x00000409, // 10-th: poly = x^10 + x^3 + 1
        0x00000805, // 11-th: poly = x^11 + x^2 + 1
        0x00001053, // 12-th: poly = x^12 + x^6 + x^4 + x + 1
        0x0000201B, // 13-th: poly = x^13 + x^4 + x^3 + x + 1
        0x00004443, // 14-th: poly = x^14 + x^10 + x^6 + x + 1
        0x00008003, // 15-th: poly = x^15 + x + 1
        0x0001100B  // 16-th: poly = x^16 + x^12 + x^3 + x + 1
      };

      
      // *************************************************
      // *               Private Members                 *
      // *************************************************
      
      // Currently selected irreducible poly
      private BinaryGaloisFieldElement poly;
      
      // Primitive element, alpha
      private BinaryGaloisFieldElement primElement;
      
      // Length of field
      private Int32 length;
    
      // Field values in order
      private BinaryGaloisFieldElement[] element;
      
      // Field values using cyclic generator alpha
      private BinaryGaloisFieldElement[] alpha;
      
      // Index values for each alpha exponent
      private Int32[] index;
      
      
      // *************************************************
      // *               Private Methods                 *
      // *************************************************
      
      // Create array of in order field elements
      private void GenerateFieldElements()
      {
        element = new BinaryGaloisFieldElement[length];
        
        for (int i = 0; i<length; i++)
        {
          element[i] = i;
        }
      }
      
      // Create array of alpha exponents
      private void GenerateAlphaExponents()
      {
        alpha = new BinaryGaloisFieldElement[length];
        index = new Int32[length];
        
        // This is a dummy value so that alpha^i is at index i;
        alpha[0] = (BinaryGaloisFieldElement) 1;
        index[0] = 1;
        
        for (int i = 1; i<length; i++)
        {
          alpha[i] = Multiply(alpha[i-1],primElement);
          index[alpha[i].Value] = i;
        }
      }      
      
      
      // *************************************************
      // *        Public Properties and Indexer          *
      // *************************************************

      // Field Length
      public Int32 Length
      {
        get
        { 
          return length; 
        }
      }
      
      
      // *************************************************
      // *             Public constructors               *
      // *************************************************
      
      // Public constructor for Binary Galois Field class
      // r is the exponent to which 2 is raised
      public BinaryGaloisField(Int32 r)
      {
        // Set the irreducible polynomial for GF(2^r)
        poly = (BinaryGaloisFieldElement) primPoly[r];
        
        // Set the primitive element alpha
        primElement = (BinaryGaloisFieldElement) 2;
        
        // Set the field length
        length = (1 << r);
        
        // Generate the field elements
        GenerateFieldElements();
        
        // Generate the alpha exponents
        GenerateAlphaExponents();
      }
      
      
      // *************************************************
      // *                Public methods                 *
      // *************************************************
      
      // Array for access to field element
      public BinaryGaloisFieldElement Element(int index)
      {
        return this.element[index];
      }
      
      // Array for access to alpha exponents
      public BinaryGaloisFieldElement AlphaFromIndex(int index)
      {
        //Console.WriteLine("index = {0}",(index % length));
        return this.alpha[(index % (length-1))];
      }
      
      // Array for access to alpha exponents
      public Int32 IndexFromAlpha(BinaryGaloisFieldElement alpha)
      {
        if ( (alpha.Value == 0) || (alpha.Value >= Length) )
          throw new ArgumentException("IndexFromAlpha: Out of range", "alpha");
        return this.index[alpha.Value];
      }
      
      // Assume field Elements are polynomials of max order 15
      public BinaryGaloisFieldElement Multiply(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        BinaryGaloisFieldElement tempVal = (BinaryGaloisFieldElement) 0;
        UInt32 mask = 0x1;
        
        // Perform multiplication
        for (int i = 0; i<16; i++)
        {
          if ((x.Value & mask) != 0)
          {
            tempVal += (y << i);
          }
          mask <<= 1;
        }
        
        // Now take modulo poly
        return Modulo(tempVal,poly);
      }
      
      public BinaryGaloisFieldElement Divide(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        Int32 result = 0x0;
        Int32 ordX, ordY;
        
        ordX = BinaryGaloisFieldElement.Order(x);
        ordY = BinaryGaloisFieldElement.Order(y);
        
        // if x is already of lower order than y, abort
        if ( ordX < ordY)
          return ((BinaryGaloisFieldElement) 0);
        
        // Perform long division
        while (ordX >= ordY)
        {
          if ( (x.Value & (0x1 << ordX)) != 0)
          {
            result = 0x1 << (ordX - ordY);
            x -= (y << (ordX - ordY));
          }
          ordX--;
        }

        return ((BinaryGaloisFieldElement)result);
      }
      
      public BinaryGaloisFieldElement Modulo(BinaryGaloisFieldElement x, BinaryGaloisFieldElement y)
      {
        Int32 ordX, ordY;
        
        ordX = BinaryGaloisFieldElement.Order(x);
        ordY = BinaryGaloisFieldElement.Order(y);
      
        // if x is already of lower order than y, abort
        if (BinaryGaloisFieldElement.Order(x) < BinaryGaloisFieldElement.Order(y))
          return x;
      
        // Keep subtracting mod value until we are in a valid range
        // Perform long division
        while (ordX >= ordY)
        {
          if ( (x.Value & (0x1 << ordX)) != 0)
          {
            x -= (y << (ordX - ordY));
          }
          ordX--;
        }
        return x;
      }
      

      // *************************************************
      // *               Public operators                *
      // *************************************************
      
      
      
    }
}
