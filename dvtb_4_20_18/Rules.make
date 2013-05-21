#
# Rules.make
#
# DVTB Rules.make
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

ifndef DVTB_INSTALL_DIR
    DVTB_INSTALL_DIR = .
endif

ifndef DVTB_INSTALL_DIR
   $(error DVTB_INSTALL_DIR must be set )
endif

-include ../Rules.make

ifeq ($(PLATFORM),omap3530_w)
	# Where the RTSC tools package is installed.
	XDC_INSTALL_DIR=C:\ti_tools\xdctools_3_10_05_61

	# WinCE core libraries
	WINCE_LIBS_DIR=$(_PROJECTROOT)/CESYSGEN/SDK/lib/$(_TGTCPU)/retail
	WINCE_LIBS=$(WINCE_LIBS_DIR)/coredll.lib $(WINCE_LIBS_DIR)/corelibc.lib $(WINCE_LIBS_DIR)/ceddk.lib

	#------------------------------------------------------------------------------ 
	# WINCE DEVELOPMENT TOOLS:
	#    Set the location of the WINCE tools
	#------------------------------------------------------------------------------ 
	WINCE_DIR=$(_WINCEROOT)
	WINCE_TOOL_DIR=$(WINCE_DIR)/SDK/BIN/I386/ARM

	EXEC_DIR=$(_FLATRELEASEDIR)
endif

