The DM35x_RevC directory contains files needed for the DM335, DM350, and DM355 devices (Silicon Revision 1.3).  Silicon revision 1.1 is sometimes referred to as revision A.

Silicon revision 1.2 was never released to the market.

Silicon revision 1.3 differs from silicon revision 1.1 in the following manner:

     a)  Silicon revision 1.1 only supports NAND devices with a page size of 512 bytes/page and 2K bytes/page.
         Silicon revision 1.3 supports NAND devices with page sizes of 512 bytes/page, 2K bytes/page, and 4K bytes/page.

     b)  Silicon revision 1.1 used a NAND layout for big block NAND devices with a page size of 2K bytes per page as follows:
               512 bytes data
               16 bytes spare byte area
               512 bytes data
               16 bytes spare byte area
               512 bytes data
               16 bytes spare byte area
               512 bytes data
               16 bytes spare byte area

         Silicon revision 1.3 used a NAND layout for big block NAND devices with a page size of 2K bytes per page as follows:
               2048 bytes data
               64 bytes spare byte area

     c)  Silicon revision 1.3 used a NAND layout similar to silicon revision 1.1 by default.  A different magic number is used in the
         UBL header to select the different NAND layout.

     d)  Silicon revision 1.1 used a lookup table to identify NAND device charactoristics based on the first two bytes returned from the READ_ID
         command.  Devices which were not contained in the lookup table were assigned assumed default configuration.

         Silicon revision 1.3 used a lookup table similar to that used in revision 1.1, but devices not contained in the lookup table were identified 
         using the 3rd and 4th bytes returned by the READ_ID command.


  
