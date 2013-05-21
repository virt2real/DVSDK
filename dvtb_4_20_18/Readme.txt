==========================================================================================
                                Rules.make related changes
==========================================================================================
Linux
======
# use DVSDK Rules.make for DVTB on Linux
# Add following in the Makefile
-include ../Rules.make

WinCE
======
# use Rules.make present with DVTB installation directory
# Add following in the Makefile
-include Rules.make
==========================================================================================


==========================================================================================
                                  Clean, Build & Install
==========================================================================================

Cleaning:
=========
<DVTB-Source-Root/>$ gmake clean
# this cleans all the platform's intermediate files

To build Linux DVTB for DM355:
==============================
<Linux/DVTB-Source-Root/>$ make dm355
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/dm355/bin
# Make sure that PLATFORM is set to dm355 in the dvsdk Rules.make
 
To build Linux DVTB for DM357:
==============================
<Linux/DVTB-Source-Root/>$ make dm357
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/dm357/bin
# Make sure that PLATFORM is set to dm357 in the dvsdk Rules.make 

To build Linux DVTB for DM365:
==============================
<Linux/DVTB-Source-Root/>$ make dm365
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/dm365/bin
# Make sure that PLATFORM is set to dm365 in the dvsdk Rules.make 

To build Linux DVTB for DM6446:
===============================
<Linux/DVTB-Source-Root/>$ make dm6446
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/dm6446/bin
# Make sure that PLATFORM is set to dm6446 in the dvsdk Rules.make 

To build Linux DVTB for DM6467:
===============================
<Linux/DVTB-Source-Root/>$ make dm6467
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/dm6467/bin
# Make sure that PLATFORM is set to dm6467 in the dvsdk Rules.make 

To build Linux DVTB for OMAP3530:
=================================
<Linux/DVTB-Source-Root/>$ make omap3530
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/omap3530/linux/bin
# Make sure that PLATFORM is set to omap3530 in the dvsdk Rules.make 

To build Linux DVTB for DM3730:
=================================
<Linux/DVTB-Source-Root/>$ make dm3730
# This creates dvtb-r and dvtb-d in packages/ti/sdo/dvtb/dm3730/linux/bin
# Make sure that PLATFORM is set to dm3730 in the dvsdk Rules.make 

To build WinCE DVTB for OMAP3530:
=================================
<WinCE\DVTB-Source-Root/>$ gmake omap3530_w
# This creates dvtb.exe and dvtb-d.exe in packages/ti/sdo/dvtb/omap3530/wince/bin
# Make sure that PLATFORM is set to omap3530 in the Rules.make 

To Install DVTB for OMAP3530 for WINCE:
=======================================
<WinCE\DVTB-Source-Root/>$ gmake omap3530_w_install
# This copies dvtb.exe and dvtb-d.exe to _FLATRELEASEDIR

==========================================================================================
