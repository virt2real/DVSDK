#
#  Copyright (c) 2009, Texas Instruments Incorporated
#  All rights reserved.
#
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
#
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
#
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
#
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
#
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
#  ======== Makefile ========
#

# Set location of various tools
XDC_INSTALL_DIR = xdctools_3_16_00_18
FC_INSTALL_DIR = framework_components_2_26_00_01
BIOS_INSTALL_DIR = bios_5_41_00_06
XDAIS_INSTALL_DIR = $(FC_INSTALL_DIR)/fctools
EDMA3_LLD_INSTALL_DIR = $(FC_INSTALL_DIR)/fctools
LINUXUTILS = $(FC_INSTALL_DIR)/fctools
WINCEUTILS = $(FC_INSTALL_DIR)/fctools


# If there is a Rules.make (say, if this is part of a DVSDK install), then use
# all the settings for the variables above from the Rules.make 
RULES_MAKE := ../../Rules.make
-include $(RULES_MAKE)

# Set location of xdc executable
XDC = $(XDC_INSTALL_DIR)/xdc

# Set XDCPATH to contain necessary repositories.
# Note, the '^' character puts 'this' repository first in the XDCPATH.  This is
# necessary because that's where config.bld will be found.
XDCPATH = ^;$(FC_INSTALL_DIR)/fctools/packages;$(XDAIS_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages/;$(BIOS_INSTALL_DIR)/packages;$(LINUXUTILS)/packages;$(EDMA3_LLD_ROOT)/packages;$(WINCEUTILS)/packages;

# How many concurrent build threads (i.e. jobs) do you want to allow to run
JOBS=4

# Conditionally, you can create verbose build output
XDCOPTIONS=v

#######################################################
## Shouldn't have to modify anything below this line ##
#######################################################

export XDCOPTIONS
export XDCPATH

all: .all-packages

# This recursively locates all packages in the "ti" directory, builds
# and releases them
.all-packages:
	$(XDC) release --jobs=$(JOBS) -PR ti

# This recursively cleans all packages in the "ti" directory
clean: clean-packages

clean-packages:
	$(XDC) clean --jobs=$(JOBS) -PR ti

dm365: .edma_only .vicp_only

.edma_only:
	$(XDC) release --jobs=$(JOBS) -P ti/sdo/fc/rman/examples/dummyEdma3 ti/sdo/fc/rman/examples/scratchEdma3

.vicp_only:
	$(XDC) release --jobs=$(JOBS) -P ti/sdo/fc/rman/examples/vicp


