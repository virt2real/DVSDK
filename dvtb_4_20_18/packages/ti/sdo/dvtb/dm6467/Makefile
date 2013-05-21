#
# Makefile
#
# Makefile for DM6467 Linux DVTB
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

DVTB_ROOTDIR = ../../../../..
-include ../../../../../../Rules.make
include pal.src
include TSPA.src
include NONTSPA.src

ifndef CODECS
CODECS=TSPA
endif

ifndef H264CodecPackage
H264CodecPackage=h264dec
endif

TARGET = dvtb
TARGET_DIR = ./bin
REL_LIB = $(TARGET_DIR)/$(TARGET)-r.a
DBG_LIB = $(TARGET_DIR)/$(TARGET)-d.a
EDITLINE_LIB = ./linux/libs/libedit.a
REL_BIN = $(TARGET_DIR)/$(TARGET)-r
DBG_BIN = $(TARGET_DIR)/$(TARGET)-d

XDC_PATH = $(CODEC_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/packages;$(LINK_INSTALL_DIR);$(XDAIS_INSTALL_DIR)/packages;$(CMEM_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/cetools/packages;$(LINK_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages/ti/bios/include;$(XDAIS_INSTALL_DIR)/packages/ti/xdais

#Configuro related
#Base name of app's config script
CONFIGPKG = $(TARGET)_$(notdir $(CURDIR))
CONFIG_BLD := config.bld
XDCTARGET = gnu.targets.arm.GCArmv5T
XDCPLATFORM = ti.platforms.evmDM6467

#Configuro generated files
XDC_COMPILER_FILE = $(CONFIGPKG)/compiler.opt
XDC_LINKER_FILE = $(CONFIGPKG)/linker.cmd

#Path to Configuro utility
CONFIGURO = XDCPATH="$(XDC_PATH)" $(XDC_INSTALL_DIR)/xs xdc.tools.configuro

INCLUDES += -I $(LINUXKERNEL_INSTALL_DIR)/include -I $(XDAIS_INSTALL_DIR)/packages/ti/xdais/include -I $(DVTB_ROOTDIR)/packages/ti/sdo/dvtb/core/inc/linux -I $(DVTB_ROOTDIR)/packages/ti/sdo/dvtb/core/inc/common -I $(CURDIR)/linux -I $(DVTB_ROOTDIR)/packages/ti/sdo/dvtb/pal/linux/v4l2 -I $(DVTB_ROOTDIR)/packages/ti/sdo/dvtb/pal/linux/alsa -I $(LINUXLIBS_INSTALL_DIR)/include -I $(MATCH_PATH)

C_FLAGS += -Wall -fno-strict-aliasing -g -I./libedit -DREADLINE=1 
AR_FLAGS += -r 

ifeq ($(CODECS),TSPA)
VPATH= $(PAL_SRCVPATH) $(TSPA_SRCVPATH)
else
VPATH= $(PAL_SRCVPATH) $(NONTSPA_SRCVPATH)
endif


#LD_LIBS = -lpthread $(EDITLINE_LIB) $(LINUXLIBS_INSTALL_DIR)/lib/libncurses.so $(LINUXLIBS_INSTALL_DIR)/lib/libasound.so
LD_LIBS = -lpthread $(EDITLINE_LIB) -L$(LINUXLIBS_INSTALL_DIR)/lib -Wl,-rpath-link,$(LINUXLIBS_INSTALL_DIR)/lib -lasound -lncursesw

CC = $(MVTOOL_PREFIX)gcc $(INCLUDES) $(C_FLAGS) $(shell cat $(XDC_COMPILER_FILE)) -c
AR = $(MVTOOL_PREFIX)ar
LN = $(MVTOOL_PREFIX)gcc

ifeq ($(H264CodecPackage),h2641080p60vdec)
Flag = -D_DVTB_H2641080p60VDEC_
SOURCE = $(H2641080p60VDEC_SOURCE)
endif

ifeq ($(H264CodecPackage),h264dec)
Flag = -D_DVTB_H264DEC_
SOURCE = $(H264DEC_SOURCE)
endif

ifeq ($(CODECS),TSPA)
REL_FLAGS = $(Flag)
DBG_FLAGS = -g -D_DVEVM_ST_DEBUG_ $(Flag)
REL_OBJ = $(PAL_SOURCE:%.c=%.rel.o) $(TSPA_SOURCE:%.c=%.rel.o) $(SOURCE:%.c=%.rel.o)
DBG_OBJ = $(PAL_SOURCE:%.c=%.dbg.o) $(TSPA_SOURCE:%.c=%.dbg.o) $(SOURCE:%.c=%.dbg.o)
else
REL_FLAGS = -D_DVTB_NONTSPA_ $(Flag)
DBG_FLAGS = -g -D_DVEVM_ST_DEBUG_ -D_DVTB_NONTSPA_ $(Flag)
REL_OBJ = $(PAL_SOURCE:%.c=%.rel.o) $(NONTSPA_SOURCE:%.c=%.rel.o) $(SOURCE:%.c=%.rel.o)
DBG_OBJ = $(PAL_SOURCE:%.c=%.dbg.o) $(NONTSPA_SOURCE:%.c=%.dbg.o) $(SOURCE:%.c=%.dbg.o)
endif


HEADERS = $(wildcard linux/*.h) $(wildcard ../core/inc/common/*.h) $(wildcard ../core/inc/linux/*.h)

.PHONY: clean

.NOTPARALLEL: $(REL_BIN) $(DBG_BIN)

all :: $(REL_BIN) $(DBG_BIN)

#Dependency on Config PACKAGE
$(XDC_COMPILER_FILE) $(XDC_LINKER_FILE) :: $(CONFIGPKG)

#Config package dependency
$(CONFIGPKG) :: $(CONFIGPKG).cfg
	$(CONFIGURO) -c $(MVTOOL_DIR) -o $(CONFIGPKG) -t $(XDCTARGET) -p $(XDCPLATFORM) -b $(CONFIG_BLD) $(CONFIGPKG).cfg
	@mkdir -p bin

$(REL_LIB) :: $(REL_OBJ)
	$(AR) $(AR_FLAGS) $(REL_LIB) $(REL_OBJ)

$(DBG_LIB) :: $(DBG_OBJ) 
	$(AR) $(AR_FLAGS) $(DBG_LIB) $(DBG_OBJ)

$(REL_OBJ) :: %.rel.o: %.c $(HEADERS) $(XDC_COMPILER_FILE)
	$(CC) $(CFLAGS) $(XDC_INCLUDES) $(REL_FLAGS) -o $@ $<

$(DBG_OBJ) :: %.dbg.o: %.c $(HEADERS) $(XDC_COMPILER_FILE)
	$(CC) $(CFLAGS) $(XDC_INCLUDES) $(DBG_FLAGS) -o $@ $<

$(REL_BIN) :: $(REL_LIB) $(XDC_LINKER_FILE)
	$(LN) -o $@ $^ $(LD_LIBS)

$(DBG_BIN) :: $(DBG_LIB) $(XDC_LINKER_FILE)
	$(LN) -o $@ $^ $(LD_LIBS)
	
clean::
	-rm -rf $(REL_OBJ) $(DBG_OBJ) $(H2641080p60VDEC_SOURCE:%.c=%.rel.o) $(H2641080p60VDEC_SOURCE:%.c=%.dbg.o) $(H264DEC_SOURCE:%.c=%.rel.o) $(H264DEC_SOURCE:%.c=%.dbg.o)
	-rm -rf $(REL_LIB)
	-rm -rf $(DBG_LIB)
	-rm -rf $(REL_BIN)
	-rm -rf $(DBG_BIN)
	-rm -rf $(TARGET_DIR)
	-rm -rf $(CONFIGPKG)

