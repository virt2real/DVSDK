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

DMAI_INSTALL_DIR = ../../../..

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
    CPP_FLAGS	= -DNDEBUG
    C_FLAGS	= -O2
else
    CPP_FLAGS	=
    C_FLAGS	= -g
endif

ifeq ($(strip $(PLATFORM_OS)), linux)
    EXT = 470MV
else
    EXT = 64P
endif

# Which kernel arch header to be used ?
ifeq ($(PLATFORM), o3530_al)
    PLATFORM_ARCH  = plat-omap
else
ifeq ($(PLATFORM), dm3730_al)
    PLATFORM_ARCH  = plat-omap
else
    PLATFORM_ARCH  = mach-davinci
endif
endif

# If exist then include autoconf.h
LINUXKERNEL_AUTOCONF=$(LINUXKERNEL_INSTALL_DIR)/include/linux/autoconf.h 
ifneq ($(strip $(wildcard $(LINUXKERNEL_AUTOCONF))),)
 HAVE_AUTOCONFIG =-include $(LINUXKERNEL_INSTALL_DIR)/include/linux/autoconf.h
endif

XDCPATH	+= $(XDC_INSTALL_DIR)/packages;$(DMAI_INSTALL_DIR)/packages;$(CODEC_INSTALL_DIR)/packages

CPP_FLAGS	+= -I$(XDC_INSTALL_DIR)/packages -I$(DMAI_INSTALL_DIR)/packages -I$(CE_INSTALL_DIR)/packages -I$(FC_INSTALL_DIR)/packages -I$(XDAIS_INSTALL_DIR)/packages -I$(CODEC_INSTALL_DIR)/packages -DDmai_Device_$(PLATFORM_DEVICE)

GCC_CPP_FLAGS	+= $(CPP_FLAGS) -I$(LINUXKERNEL_INSTALL_DIR)/include -I$(LINUXKERNEL_INSTALL_DIR)/arch/arm/include -I$(LINUXKERNEL_INSTALL_DIR)/arch/arm/$(PLATFORM_ARCH)/include $(HAVE_AUTOCONFIG) -I$(CMEM_INSTALL_DIR)/packages -I$(LINK_INSTALL_DIR) -DDmai_BuildOs_linux -Dxdc_target_types__=gnu/targets/std.h -I$(LINUXLIBS_INSTALL_DIR)/include -Dxdc_target_name__=arm/GCArmv5T
C64P_CPP_FLAGS	+= $(CPP_FLAGS) -I$(BIOS_INSTALL_DIR)/packages/ti/bios/include -I$(BIOS_INSTALL_DIR)/packages -DDmai_BuildOs_bios -Dxdc_target__='<ti/targets/std.h>' -I$(CODEGEN_INSTALL_DIR)/include -mv6400+ -pdse225 -eo$(PLATFORM_DEVICE).o$(EXT)

GCC_C_FLAGS	+= $(C_FLAGS) -Wall -Werror
C64P_C_FLAGS	+= $(C_FLAGS)

GNU_AR_FLAGS	+= $(AR_FLAGS)
C64P_AR_FLAGS	+= $(AR_FLAGS)

GCC_COMPILE.c	= $(PRE) $(CROSS_COMPILE)gcc $(GCC_CPP_FLAGS) $(GCC_C_FLAGS) -c -o $@ $<
GCC_AR.c	= $(PRE) $(CROSS_COMPILE)ar rc $(AR_FLAGS) $@ $^

C64P_COMPILE.c	= $(PRE) $(CODEGEN_INSTALL_DIR)/bin/cl6x $(C64P_CPP_FLAGS) $(C64P_C_FLAGS) -c $< -fr"$(dir $@)"
C64P_AR.c	= $(PRE) $(CODEGEN_INSTALL_DIR)/bin/ar6x $(C64P_AR_FLAGS) r $@ $^

ifeq ($(PLATFORM_OS),linux)
COMPILE.c	= $(GCC_COMPILE.c)
AR.c		= $(GCC_AR.c)
else
COMPILE.c	= $(C64P_COMPILE.c)
AR.c		= $(C64P_AR.c)
endif

HEADERS		=  $(wildcard *.h) $(wildcard ce/*.h)
HEADERS		+= $(wildcard $(PLATFORM_OS)/priv/*.h)
HEADERS		+= $(wildcard $(PLATFORM_OS)/$(PLATFORM_PERIPHERALS)/priv/*.h)

SOURCES		=  $(wildcard *.c) $(wildcard ce/*.c)
SOURCES		+= $(wildcard $(PLATFORM_OS)/*.c)
SOURCES		+= $(wildcard $(PLATFORM_OS)/$(PLATFORM_PERIPHERALS)/*.c)

OBJFILES	=  $(addprefix obj/,$(SOURCES:%.c=%.$(PLATFORM_DEVICE).o$(EXT)))

ifeq ($(PLATFORM), dm3730_al)
    TARGET		= lib/dmai_$(PLATFORM_OS)_omap3530.a$(EXT)

else 
ifeq ($(PLATFORM), dm368_al)
    TARGET		= lib/dmai_$(PLATFORM_OS)_dm365.a$(EXT) 

else
    TARGET		= lib/dmai_$(PLATFORM_OS)_$(PLATFORM_DEVICE).a$(EXT)
endif
endif

XDC_CMD		= $(PRE) $(XDC_INSTALL_DIR)/xdc XDCTARGETS="$(PLATFORM_XDC_TARGET)"

export CROSS_COMPILE
export CODEGEN_INSTALL_DIR
export XDCPATH
export PLATFORM_XDC

.PHONY: clean install all message

all:	message $(TARGET) package/package.defs.h

install:

message:
	@echo "Building dmai for $(PLATFORM).."
	@echo 

package/package.defs.h:	package.xdc package.xs package.bld
	@echo
	@echo Building package interface for dmai..
	$(XDC_CMD)

$(TARGET):	$(OBJFILES)
	@echo
	@echo Archiving $@ from $^..
	@mkdir -p $(dir $@)
	$(AR.c)

$(OBJFILES): obj/%.$(PLATFORM_DEVICE).o$(EXT): %.c $(HEADERS)
	@echo Compiling $@ from $<..
	@mkdir -p $(dir $@)
	$(COMPILE.c)

clean:
	@echo Removing generated files..
	$(PRE) $(XDC_CMD) clean
	$(PRE) -$(RM) -rf lib/* obj/* *~ *.mak .xdcenv.mak
