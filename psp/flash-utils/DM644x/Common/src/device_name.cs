/* --------------------------------------------------------------------------
    FILE        : device_name.cs
    PROJECT     : TI Booting and Flashing Utilities
    AUTHOR      : Daniel Allred
    DESC        : Name adaptor for DM644x parts
 ----------------------------------------------------------------------------- */

using System;
using System.Text;
 
namespace TIBootAndFlash
{
  partial class Program
  {
#if DM6441
    public static String devString = "DM6441";
#elif DM6441LV
    public static String devString = "DM6441LV";
#else
     public static String devString = "DM644x";
#endif
  }
}