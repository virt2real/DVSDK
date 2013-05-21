using System;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using System.Collections;
using System.Collections.Generic;
using System.Globalization;

namespace UtilLib
{

  /**
   * This struct defines a section of an INI file/stream
   */
  public struct INISection
  {
    /**
     * INI Section Name
     */
    public String iniSectionName;
    
    /**
     * HashTable of the section values
     */
    public Hashtable sectionValues;
  }
  
  public class INI
  {
    /**
     * Function to Parse an input data stream containing INI data
     *
     * @param iniStream is an input Stream object
     */
    public static INISection[] Parse(Stream iniStream)
    {
      List<String> streamLines = new List<String>();
      List<INISection> streamSections = new List<INISection>();
      StreamReader iniSR;
      
      INISection currSec = new INISection();
      Boolean inASection = false;
      Regex iniSecHdr = new Regex("\\[[A-Za-z0-9_]*\\]");

      try
      {
        iniSR = new StreamReader(iniStream);
      }
      catch (Exception e)
      {
        Console.WriteLine(e.Message);
        throw e;
      }
     
      // Get lines of data from the stream
      while (!iniSR.EndOfStream)
      {
        streamLines.Add(iniSR.ReadLine());
      }

      // Parse actually line contents
      for (int i=0; i<streamLines.Count; i++)
      {
        // Get current line from the streamLines List
        String currLine = (streamLines[i]).Trim();
        
        // Ignore comment and empty lines
        if ( (currLine.StartsWith(";")) || (currLine.Equals("")) )
        {
          continue;
        }                                  
          
        // If we find a section header, begin a new section
        Match m = iniSecHdr.Match(currLine);
        if (m.Success)
        {
          if (inASection)
          {
            streamSections.Add(currSec);
          }
          inASection = true;
          currSec = new INISection();
          currSec.iniSectionName = m.Value.ToUpper().Trim('[', ']');
          currSec.sectionValues = new Hashtable();
          Debug.DebugMSG("INI Section: {0}", currSec.iniSectionName);
          continue;
        }

        // If we find key/value paramter pairs, parse the value and key
        if (currLine.Contains("="))
        {
          // Split the name at the '=' sign
          String[] paramAndValue = currLine.Split(new char[1] { '=' }, StringSplitOptions.RemoveEmptyEntries);

          // Trim the param name and value
          paramAndValue[0] = paramAndValue[0].Trim().ToUpper();
          paramAndValue[1] = paramAndValue[1].Trim();

          // Hex values must be prefixed by "0x"
          if (paramAndValue[1].StartsWith("0x") || paramAndValue[1].StartsWith("0X"))
          {
            currSec.sectionValues[paramAndValue[0]]
              = UInt32.Parse(paramAndValue[1].Replace("0x", ""), NumberStyles.AllowHexSpecifier);
          }
          else
          {
            UInt32 value;
            if (UInt32.TryParse(paramAndValue[1], out value))
            {
              currSec.sectionValues[paramAndValue[0]] = value;
            }
            else
            {
              currSec.sectionValues[paramAndValue[0]] = paramAndValue[1];
            }
          }
          Debug.DebugMSG("\t{0} = {1}", paramAndValue[0], currSec.sectionValues[paramAndValue[0]]);
          continue;
        }
        
        // Any other lines throw an error
        throw new Exception(String.Format("Bad INI data at line {0}: {1}.", i, currLine));
      } // End of parsing INI
      
      // Add last section to return value
      if (inASection)
      {
        streamSections.Add(currSec);
      }

      // Return parsed ini sections    
      return streamSections.ToArray();
    }
    
    /**
     * Function to parse an input data stream containing INI data
     *
     * @param iniData is a String containing the INI data
     */    
    public static INISection[] Parse(String iniData)
    {
      ASCIIEncoding ae = new ASCIIEncoding();
      return INI.Parse(ae.GetBytes(iniData));
    }
    
    /**
     * Function to parse an input data stream containing INI data
     *
     * @param iniData is an array of bytes containing the INI data
     */
    public static INISection[] Parse(Byte[] iniData)
    {
      return INI.Parse(new MemoryStream(iniData, false));
    }
    
    /**
     * Function to build an INI data string
     *
     * @param sections is an array of INISection objects
     */
    public static String Build(INISection[] sections)
    {
      StringWriter sw = new StringWriter(new StringBuilder());
      INISection currSection;
      
      for (int i=0; i<sections.Length; i++)
      {
        currSection = sections[i];
        sw.WriteLine("[{0}]",currSection.iniSectionName);
        
        foreach (DictionaryEntry de in  currSection.sectionValues)
        {
          sw.WriteLine("{0} = {1}",de.Key,de.Value);
        }
        sw.WriteLine();
      }
      return sw.GetStringBuilder().ToString();
    }
  }
}