using System;
using System.IO;
using System.Reflection;
using System.Collections.Generic;
using System.Text;

namespace UtilLib.IO
{
  public class FileIO
  {
    /// <summary>
    /// Function to find and read a file's data
    /// </summary>
    /// <param name="filename">The name of the file to load</param>
    /// <returns></returns>
    public static Byte[] GetFileData(String filename)
    {
      Byte[] data;

      if (!File.Exists(filename))
      {
        throw new FileNotFoundException("File " + filename + " is not present.");
      }

      // Open file and read data
      try
      {
        data = File.ReadAllBytes(filename);
      }
      catch (Exception e)
      {
        Console.WriteLine("Error: "+e.Message);
        throw e;
      }

      return data;
    }
    
    public static String GetFileText(String filename)
    {
      String text;

      if (!File.Exists(filename))
      {
        throw new FileNotFoundException("File " + filename + " is not present.");
      }

      // Open file and read data
      try
      {
        text = File.ReadAllText(filename);
      }
      catch (Exception e)
      {
        Console.WriteLine("Error: "+e.Message);
        throw e;
      }

      return text;
    }

    public static void SetFileData(String filename, Byte[] data, Boolean overwrite)
    {
      // Open file and read data
      try
      {
        if (!File.Exists(filename))
        {
          using (FileStream fs = File.Create(filename)){}
        }
        else if (overwrite)
        {
          using (FileStream fs = File.Create(filename)){}
        }
        
        File.WriteAllBytes(filename,data);
      }
      catch (Exception e)
      {
        Console.WriteLine("Error: "+e.Message);
        throw e;
      }
    }
    
    public static void SetFileText(String filename, String data, Boolean overwrite)
    {
      // Open file and read data
      try
      {
        if (!File.Exists(filename))
        {
          using (FileStream fs = File.Create(filename)){}
        }
        else if (overwrite)
        {
          using (FileStream fs = File.Create(filename)){}
        }

        File.WriteAllText(filename,data);
      }
      catch (Exception e)
      {
        Console.WriteLine("Error: "+e.Message);
        throw e;
      }
    }
    

  }
}
