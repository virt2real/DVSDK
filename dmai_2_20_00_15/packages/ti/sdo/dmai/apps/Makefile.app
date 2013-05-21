# --COPYRIGHT--,BSD
#  Copyright (c) 2010, Texas Instruments Incorporated
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
# --/COPYRIGHT--

# Use the main DMAI Rules.make for building apps in this directory
ifndef DMAI_INSTALL_DIR
    DMAI_INSTALL_DIR = ../../../../../..
endif

include $(DMAI_INSTALL_DIR)/Rules.make
include $(DMAI_INSTALL_DIR)/Platform.make

# Convert platform specific variables to general variables
CE_INSTALL_DIR		 = $(strip $(CE_INSTALL_DIR_$(PLATFORM)))
LINK_INSTALL_DIR	 = $(strip $(LINK_INSTALL_DIR_$(PLATFORM)))
CMEM_INSTALL_DIR	 = $(strip $(CMEM_INSTALL_DIR_$(PLATFORM)))
FC_INSTALL_DIR		 = $(strip $(FC_INSTALL_DIR_$(PLATFORM)))
XDAIS_INSTALL_DIR	 = $(strip $(XDAIS_INSTALL_DIR_$(PLATFORM)))
EDMA3_LLD_INSTALL_DIR	 = $(strip $(EDMA3_LLD_INSTALL_DIR_$(PLATFORM)))
LINUXKERNEL_INSTALL_DIR  = $(strip $(LINUXKERNEL_INSTALL_DIR_$(PLATFORM)))
CROSS_COMPILE		 = $(strip $(CROSS_COMPILE_$(PLATFORM)))
CODEC_INSTALL_DIR	 = $(strip $(CODEC_INSTALL_DIR_$(PLATFORM)))
XDC_INSTALL_DIR		 = $(strip $(XDC_INSTALL_DIR_$(PLATFORM)))
BIOSUTILS_INSTALL_DIR	 = $(strip $(BIOSUTILS_INSTALL_DIR_$(PLATFORM)))
BIOS_INSTALL_DIR	 = $(strip $(BIOS_INSTALL_DIR_$(PLATFORM)))
EDMA3_LLD_INSTALL_DIR	 = $(strip $(EDMA3_LLD_INSTALL_DIR_$(PLATFORM)))
CODEGEN_INSTALL_DIR	 = $(strip $(CODEGEN_INSTALL_DIR_$(PLATFORM)))
LPM_INSTALL_DIR		 = $(strip $(LPM_INSTALL_DIR_$(PLATFORM)))
LINUXLIBS_INSTALL_DIR	 = $(strip $(LINUXLIBS_INSTALL_DIR_$(PLATFORM)))
C6ACCEL_INSTALL_DIR	 = $(strip $(C6ACCEL_INSTALL_DIR_$(PLATFORM)))
USER_XDC_PATH    	 = $(strip $(USER_XDC_PATH_$(PLATFORM)))
EXEC_DIR		 = $(strip $(EXEC_DIR_$(PLATFORM)))

PLATFORM_OS		 = $(strip $(PLATFORM_OS_$(PLATFORM)))
PLATFORM_DEVICE		 = $(strip $(PLATFORM_DEVICE_$(PLATFORM)))
PLATFORM_PERIPHERALS	 = $(strip $(PLATFORM_PERIPHERALS_$(PLATFORM)))
PLATFORM_XDC_TARGET	 = $(strip $(PLATFORM_XDC_TARGET_$(PLATFORM)))
PLATFORM_XDC		 = $(strip $(PLATFORM_XDC_$(PLATFORM)))

# Should the full command be echoed to the console during build?
VERBOSE=false

ifeq ($(VERBOSE), true)
    override PRE	=
else
    override PRE	= @
endif

# Which compiler flags should be used?
BUILD_TYPE=debug

ifeq ($(BUILD_TYPE), release)
    CPP_FLAGS		=
    C_FLAGS		= -O2
else
    CPP_FLAGS		= -DNDEBUG
    C_FLAGS		= -g
endif

ifeq ($(strip $(PLATFORM_OS)), linux)
    EXT = 470MV
else
    EXT = 64P
endif

TARGET = $(notdir $(CURDIR))

# Package path for the XDC tools
XDCPATH = $(USER_XDC_PATH);$(DMAI_INSTALL_DIR)/packages;$(CE_INSTALL_DIR)/packages;$(FC_INSTALL_DIR)/packages;$(LINK_INSTALL_DIR);$(XDAIS_INSTALL_DIR)/packages;$(CMEM_INSTALL_DIR)/packages;$(CODEC_INSTALL_DIR)/packages;$(BIOS_INSTALL_DIR)/packages;$(BIOSUTILS_INSTALL_DIR)/packages;$(RTDX_INSTALL_DIR)/packages;$(EDMA3_LLD_INSTALL_DIR)/packages;$(LPM_INSTALL_DIR)/packages;$(C6ACCEL_INSTALL_DIR)/soc/packages

BUILD_TARGET	= $(PLATFORM_OS)/$(TARGET)_$(PLATFORM_DEVICE)
XDC_CFG		= $(PLATFORM_OS)/$(TARGET)_$(PLATFORM_DEVICE)_config
EXEC		= $(BUILD_TARGET).x$(EXT)
MAP		= $(EXEC).map
XDC_CFLAGS	= $(XDC_CFG)/compiler.opt
XDC_LFILE	= $(XDC_CFG)/linker.cmd
XDC_CFGFILE	= $(BUILD_TARGET).cfg
CONFIG_BLD	= $(DMAI_INSTALL_DIR)/packages/config.bld

export CROSS_COMPILE
export CODEGEN_INSTALL_DIR
export XDCPATH
export PLATFORM_XDC

CONFIGURO_LINUX	= $(PRE) $(XDC_INSTALL_DIR)/xs xdc.tools.configuro -t $(PLATFORM_XDC_TARGET) -p $(PLATFORM_XDC) -b $(CONFIG_BLD)
CONFIGURO_BIOS	= $(PRE) $(XDC_INSTALL_DIR)/xs xdc.tools.configuro -c $(CODEGEN_INSTALL_DIR) -t $(PLATFORM_XDC_TARGET) -p $(PLATFORM_XDC) -b $(CONFIG_BLD) --tcf

CPP_FLAGS	+= $(PLATFORM_CPPFLAGS)

GCC_C_FLAGS 	= $(C_FLAGS) -Wall -Werror
C64P_C_FLAGS	= $(C_FLAGS)

GCC_CPP_FLAGS  	= $(CPP_FLAGS) -I$(LINUXKERNEL_INSTALL_DIR)/include
C64P_CPP_FLAGS	= $(CPP_FLAGS) -pdse225 -I$(CODEGEN_INSTALL_DIR)/include -mv6400+ -I$(BIOS_INSTALL_DIR)/packages/ti/bios/include -eo$(PLATFORM_DEVICE).o$(EXT)

GCC_LD_FLAGS	= $(LD_FLAGS) -lpthread -lm -L$(LINUXLIBS_INSTALL_DIR)/lib -lasound
C64P_LD_FLAGS	= $(LD_FLAGS) -z -w -x -c -i$(RTDX_INSTALL_DIR)/packages/ti/rtdx/iom/lib/debug -i$(RTDX_INSTALL_DIR)/packages/ti/rtdx/cio/lib/release -i$(RTDX_INSTALL_DIR)/packages/ti/rtdx/lib/c6000 

SOURCES 	= $(wildcard *.c)
HEADERS		= $(wildcard *.h)

GCC_COMPILE.c 	= $(PRE) $(CROSS_COMPILE)gcc $(GCC_C_FLAGS) $(GCC_CPP_FLAGS) -c $(shell cat $(XDC_CFLAGS)) $(GCC_CPP_FLAGS) -o $@ $<
GCC_LINK.c 	= $(PRE) $(CROSS_COMPILE)gcc $(GCC_LD_FLAGS) -Wl,-Map,$(MAP) -o $@ $^

C64P_COMPILE.c 	= $(PRE) $(CODEGEN_INSTALL_DIR)/bin/cl6x $(C64P_C_FLAGS) $(C64P_CPP_FLAGS) -c $(shell cat $(XDC_CFLAGS)) $(CPP_FLAGS) $< -fr"$(dir $<)"
C64P_LINK.c 	= $(PRE) $(CODEGEN_INSTALL_DIR)/bin/cl6x $(C64P_LD_FLAGS) -m$(MAP) -o $@ $^

ifeq ($(strip $(PLATFORM_OS)), linux)
COMPILE.c	= $(GCC_COMPILE.c)
LINK.c		= $(GCC_LINK.c)
CONFIGURO	= $(CONFIGURO_LINUX)
SOURCES		+= $(wildcard linux/*.c)
HEADERS		+= $(wildcard linux/*.h)
else
COMPILE.c	= $(C64P_COMPILE.c)
LINK.c		= $(C64P_LINK.c)
CONFIGURO	= $(CONFIGURO_BIOS)
SOURCES		+= $(wildcard bios/*.c)
HEADERS		+= $(wildcard bios/*.h)
endif

OBJFILES	= $(SOURCES:%.c=%.$(PLATFORM_DEVICE).o$(EXT))

.PHONY: clean install all doinstall message

all:	$(if $(wildcard $(XDC_CFGFILE)), $(EXEC))

install:	$(if $(wildcard $(EXEC)), doinstall)

doinstall:
	$(PRE) install -d $(EXEC_DIR)
	$(PRE) install $(EXEC) $(EXEC_DIR)
	@echo
	@echo Installed $(TARGET) binaries to $(EXEC_DIR)..

$(EXEC):	$(OBJFILES) $(XDC_LFILE)
	@echo
	@echo Linking $@ from $^..
	$(LINK.c)

$(OBJFILES):	%.$(PLATFORM_DEVICE).o$(EXT): %.c $(HEADERS) $(XDC_CFLAGS)
	@echo Compiling $@ from $<..
	$(COMPILE.c)

$(XDC_LFILE) $(XDC_CFLAGS):	$(XDC_CFGFILE)
	@echo
	@echo ======== Building $(TARGET) ========
	@echo Configuring application using $<
	@echo
	$(CONFIGURO) -o $(XDC_CFG) $(XDC_CFGFILE)

clean:
	@echo Removing generated files..
	$(PRE) -$(RM) -rf *~ *.d .dep $(OBJFILES) $(XDC_CFG) $(EXEC) $(MAP)
