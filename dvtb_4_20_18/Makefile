#
# Makefile
#
# Top level DVTB Makefile
#
# Copyright (C) 2010 Texas Instruments Incorporated - http://www.ti.com/ 
# 
# 
#  Redistribution and use in source and binary forms, with or without 
#  modification, are permitted provided that the following conditions 
#  are met:
#
#    Redistributions of source code must retain the above copyright 
#    notice, this list of conditions and the following disclaimer.
#
#    Redistributions in binary form must reproduce the above copyright
#    notice, this list of conditions and the following disclaimer in the 
#    documentation and/or other materials provided with the   
#    distribution.
#
#    Neither the name of Texas Instruments Incorporated nor the names of
#    its contributors may be used to endorse or promote products derived
#    from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS 
#  "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT 
#  LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
#  A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT 
#  OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, 
#  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT 
#  LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
#  DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
#  THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT 
#  (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE 
#  OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
#

-include ../Rules.make

OMAP3530_WINCE_TARGET = omap3530_w
OMAP3530_WINCE_INSTALL = omap3530_w_install
DM365_TARGET = dm365
DM355_TARGET = dm355
DM6446_TARGET = dm6446
DM6467_TARGET = dm6467
OMAP3530_TARGET = omap3530
DM3730_TARGET = dm3730
DM357_TARGET = dm357
CLEAN_TARGET = clean

OMAP3530_WINCE_ROOTDIR = packages/ti/sdo/dvtb/omap3530/wince
DM365_ROOTDIR = packages/ti/sdo/dvtb/dm365 
DM355_ROOTDIR = packages/ti/sdo/dvtb/dm355 
DM6446_ROOTDIR = packages/ti/sdo/dvtb/dm6446 
DM6467_ROOTDIR = packages/ti/sdo/dvtb/dm6467
OMAP3530_ROOTDIR = packages/ti/sdo/dvtb/omap3530/linux
DM3730_ROOTDIR = packages/ti/sdo/dvtb/dm3730/linux
DM357_ROOTDIR = packages/ti/sdo/dvtb/dm357 

SUBDIRS_LINUX = $(DM365_ROOTDIR) $(DM355_ROOTDIR) $(DM6446_ROOTDIR) $(DM6467_ROOTDIR) $(OMAP3530_ROOTDIR) $(DM3730_ROOTDIR) $(DM357_ROOTDIR)

SUBDIRS_OMAP3530_WINCE = $(OMAP3530_WINCE_ROOTDIR)


CLEANSUBDIRS_LINUX = $(addsuffix .clean, $(SUBDIRS_LINUX))

CLEANSUBDIRS_OMAP3530_WINCE = $(addsuffix .clean, $(SUBDIRS_OMAP3530_WINCE))

.PHONY: $(CLEAN_TARGET) $(SUBDIRS_LINUX) $(SUBDIRS_OMAP3530_WINCE) $(OMAP3530_WINCE_TARGET) $(OMAP3530_WINCE_INSTALL) $(DM365_TARGET) $(DM355_TARGET) $(DM6446_TARGET) $(DM6467_TARGET) $(OMAP3530_ROOTDIR) $(DM3730_ROOTDIR) $(DM357_TARGET)




#Build Section########################

$(DM365_TARGET) : DM365_BUILD

ifeq ($(PLATFORM),$(DM365_TARGET)) 

DM365_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(DM365_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	cd $(DM365_ROOTDIR)&& $(MAKE)
else
DM365_BUILD :
	@echo PLATFORM is not set to \"$(DM365_TARGET)\" in Rules.make. Build aborted.
endif

$(DM355_TARGET) : DM355_BUILD

ifeq ($(PLATFORM),$(DM355_TARGET)) 
DM355_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(DM355_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	cd $(DM355_ROOTDIR)&& $(MAKE)
else
DM355_BUILD :
	@echo PLATFORM is not set to \"$(DM355_TARGET)\" in Rules.make. Build aborted.
endif

$(DM6446_TARGET) : DM6446_BUILD

ifeq ($(PLATFORM),$(DM6446_TARGET))
DM6446_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(DM6446_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	cd $(DM6446_ROOTDIR) && $(MAKE)
else
DM6446_BUILD :
	@echo PLATFORM is not set to \"$(DM6446_TARGET)\" in Rules.make. Build aborted.
endif

$(DM6467_TARGET) : DM6467_BUILD

ifeq ($(PLATFORM),$(DM6467_TARGET))
DM6467_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(DM6467_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo 
	cd $(DM6467_ROOTDIR) && $(MAKE)
else
DM6467_BUILD :
	@echo PLATFORM is not set to \"$(DM6467_TARGET)\" in Rules.make. Build aborted.
endif

$(OMAP3530_TARGET) : OMAP3530_BUILD

ifeq ($(PLATFORM),$(OMAP3530_TARGET))
OMAP3530_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(OMAP3530_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo 
	cd $(OMAP3530_ROOTDIR) && $(MAKE)
else
OMAP3530_BUILD :
	@echo PLATFORM is not set to \"$(OMAP3530_TARGET)\" in Rules.make. Build aborted.
endif

$(DM3730_TARGET) : DM3730_BUILD

ifeq ($(PLATFORM),$(DM3730_TARGET))
DM3730_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(DM3730_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo 
	cd $(DM3730_ROOTDIR) && $(MAKE)
else
DM3730_BUILD :
	@echo PLATFORM is not set to \"$(DM3730_TARGET)\" in Rules.make. Build aborted.
endif


$(DM357_TARGET) : DM357_BUILD

ifeq ($(PLATFORM),$(DM357_TARGET)) 
DM357_BUILD :
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	@echo Building DVTB for $(DM357_TARGET)...
	@echo 
	@echo \*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*\*
	@echo 
	cd $(DM357_ROOTDIR)&& $(MAKE)
else
DM357_BUILD :
	@echo PLATFORM is not set to \"$(DM357_TARGET)\" in Rules.make. Build aborted.
endif


$(OMAP3530_WINCE_TARGET) : OMAP3530_WINCE_BUILD

ifeq ($(PLATFORM),$(OMAP3530_WINCE_TARGET))
OMAP3530_WINCE_BUILD :
	@echo ========================================================================
	@echo Building DVTB for $(OMAP3530_WINCE_TARGET)...
	@echo ========================================================================
	@echo 
	cd $(OMAP3530_WINCE_ROOTDIR) && $(MAKE) o3530_aw
else
OMAP3530_WINCE_BUILD :
	@echo PLATFORM is not set to \"$(OMAP3530_WINCE_TARGET)\" in Rules.make. Build aborted.
endif

#End of Build Section###############



#Install Section########################

$(OMAP3530_WINCE_INSTALL) : OMAP3530_WINCE_INSTALL

ifeq ($(PLATFORM),$(OMAP3530_WINCE_TARGET))
OMAP3530_WINCE_INSTALL :
	@echo ========================================================================
	@echo Installing DVTB for $(OMAP3530_WINCE_TARGET)...
	@echo ========================================================================
	@echo 
	cd $(OMAP3530_WINCE_ROOTDIR) && $(MAKE) install
else
OMAP3530_WINCE_INSTALL :
	@echo PLATFORM is not set to \"$(OMAP3530_WINCE_TARGET)\" in Rules.make. Install aborted.
endif


#Install of Build Section###############



#Clean Section######################

ifeq ($(PLATFORM),$(OMAP3530_WINCE_TARGET))

$(CLEAN_TARGET): $(CLEANSUBDIRS_OMAP3530_WINCE)
$(CLEANSUBDIRS_OMAP3530_WINCE)::
	@echo ========================================================================
	@echo DVTB : Cleaning sub-directory \"$(basename $@)\"...
	@echo ========================================================================
	@$(MAKE) clean -C $(basename $@)
else
$(CLEAN_TARGET): $(CLEANSUBDIRS_LINUX)
$(CLEANSUBDIRS_LINUX)::
	@echo ========================================================================
	@echo DVTB : Cleaning sub-directory \"$(basename $@)\"...
	@echo ========================================================================
	@$(MAKE) clean -C $(basename $@)
endif
#End of Clean Section###############

