using System;
using System.IO;
using System.IO.Ports;
using System.Reflection;
using System.Collections.Generic;
using System.Text;

namespace UtilLib.IO
{
  public class SerialIO
  {
        /// <summary>
    /// Waitforsequence with option for verbosity
    /// </summary>
    /// <param name="str">String to look for</param>
    /// <param name="altStr">String to look for but don't want</param>
    /// <param name="sp">SerialPort object.</param>
    /// <param name="verbose">Boolean to indicate verbosity.</param>
    /// <returns>Boolean to indicate if str or altStr was found.</returns>
    public static Boolean waitForSequence(String str, String altStr, SerialPort sp, Boolean verbose)
    {
        Boolean strFound = false, altStrFound = false;
        Byte[] input = new Byte[256];
        String inputStr;
        Int32 i;

        while ((!strFound) && (!altStrFound))
        {

            i = 0;
            do
            {
                input[i++] = (Byte)sp.ReadByte();
                //Console.Write(input[i - 1] + " ");
            } while ( (input[i - 1] != 0) &&
                      (i < (input.Length - 1)) &&
                      (input[i - 1] != 0x0A) &&
                      (input[i - 1] != 0x0D) );

            // Convert to string for comparison
            if ((input[i-1] == 0x0A) || (input[i-1] == 0x0D))
                inputStr = (new ASCIIEncoding()).GetString(input, 0, i-1);
            else
                inputStr = (new ASCIIEncoding()).GetString(input, 0, i);

            if (inputStr.Length == 0)
            {
                continue;
            }

            // Compare Strings to see what came back
            if (verbose)
                Console.WriteLine("\tTarget:\t{0}", inputStr);
            if (inputStr.Contains(altStr))
            {
                altStrFound = true;
                if (String.Equals(str, altStr))
                {
                    strFound = altStrFound;
                }
            }
            else if (inputStr.Contains(str))
            {
                strFound = true;
            }
            else
            {
                strFound = false;
            }
        }
        return strFound;
    }
  }
}
