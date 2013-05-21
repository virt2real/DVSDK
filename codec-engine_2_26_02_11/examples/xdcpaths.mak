#
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
#

#
#  ======== xdcpaths.mak ========
#  definition of XDC paths and commands
#
#  This makefile constructs the "search path" for the XDCtools where it finds
#  numerous components and packages needed to build Codec Engine examples and
#  programs.  It also assigns various toolchain locations.  See
#  build_instuctions.html for general details about this file.
#
#  USER NOTE:
#  1) you must specify various <component>_INSTALL_DIRs directores below to
#     reflect your installation, where <component> is CE for Codec Engine,
#     BIOS for DSP/BIOS, etc.
#  2) you must specify compiler path and name in CGTOOLS_* variables below
#  3) you can remove some of the devices from the "DEVICES" list and/or remove
#     some of the types of binaries from the "PROGRAMS" list and/or remove
#     some of the OS runtime environments from the "GPPOS" list to reduce
#     the build time (and possibly avoid checking for presence of a component
#     you don't need)

# (Optional) Remove from this list the devices you're not interested in building
#
# Note, this is a space-delimited list.
#
# Note, DM357 is a supported device, but only if PROGRAMS is set to APP_LOCAL,
# indicating an "ARM-only codec" application.  The CE example Servers cannot be
# built for DM357, and since setting PROGRAMS to APP_CLIENT introduces a
# dependency on the Server, we can't support APP_CLIENT on DM357.
DEVICES  := DM6446 DM6467 DM6437 DM355 DM365 OMAP2530 OMAP3530 OMAPL137 OMAPL138 X86

# (Optional) remove from this list the GPP OS's you're not interested in
# building.  In most cases, you'll likely only leave one, as WinCE users don't
# need Linux, and Linux users don't need WinCE (and probably only want _either_
# GCC or uClibc, but not both)
#
# Note, this is a space-delimited list.
GPPOS := LINUX_GCC LINUX_UCLIBC WINCE

# (Optional) Remove from the list the types of programs you're not
# interested in building:
#
# APP_CLIENT -- ARM client for codecs running on the DSP, on dual-CPU systems
# DSP_SERVER -- DSP server with the codecs, running on the DSP, on dual-CPUs
# APP_LOCAL  -- Client+codecs in a single program, whether ARM only or DSP only
#
# Note, this is a space-delimited list.
PROGRAMS := APP_CLIENT DSP_SERVER APP_LOCAL

# (Mandatory) Specify where various components are installed.
# What you need depends on what device(s) you're building for, what type(s) of
# programs you are building for, and whether your Codec Engine distribution
# includes a "cetools" directory. The legend:
# CE      - Codec Engine (needed for ARM and for DSP)
# XDC     - XDC tools (ARM and DSP)
# BIOS    - DSP/BIOS (DSP only)
# DSPLINK - Arm<->DSP communication software (ARM + DSP)
# XDAIS   - XDAIS header files (ARM and DSP)
# FC      - Framework Components, various resource managers (ARM and DSP)
# CMEM    - Contiguous memory manager (ARM only)
# BIOSUTILS - DSP BIOS Utilities (including CPU load monitor) (DSP only)
# EDMA3_LLD - EDMA3 Low Level Driver and resource manager (ARM and DSP)
# LPM       - Local Power Manager (ARM + DSP)
#
# you can omit directory specifications for the components you think you don't
# need (will be warned if you do, based on your DEVICES + PROGRAMS selection
# above).

CE_INSTALL_DIR        := _your_CE_installation_directory_/codec_engine_2_26_02_11
XDC_INSTALL_DIR       := _your_XDCTOOLS_installation_directory/xdctools_3_16_00_18
BIOS_INSTALL_DIR      := _your_BIOS_installation_directory/bios_5_41_00_06
DSPLINK_INSTALL_DIR   := _your_DSPLink_installation_directory/dsplink-1_64-prebuilt

# no need to specify the installation directories below if your CE installation
# has cetools/ directory on top
#
# Note, CMEM_INSTALL_DIR is a misnomer - it should be LINUXUTILS_INSTALL_DIR
# but we've got an existing user base.  Need to fix this later.
USE_CETOOLS_IF_EXISTS := 1
XDAIS_INSTALL_DIR     := _your_xDAIS_installation_directory/xdais_6_26_01_03
FC_INSTALL_DIR        := _your_FC_installation_directory/framework_components_2_26_00_01
CMEM_INSTALL_DIR      := _your_CMEM_installation_directory/linuxutils_2_26_01_02
WINCEUTILS_INSTALL_DIR:= _your_WINCEUTILS_installation_directory/winceutils_1_01_00_01
BIOSUTILS_INSTALL_DIR := _your_BIOSUTILS_installation_directory/biosutils_1_02_02
EDMA3_LLD_INSTALL_DIR := _your_EDMA3_LLD_installation_directory/edma3_lld_01_11_01_04
LPM_INSTALL_DIR       := _your_LPM_installation_directory/local_power_manager_1_24_02_09


# (Mandatory) specify correct compiler paths and names for the architectures
# you'll be building for:

# compiler path and name for Montavista Arm 9 toolchain. NOTE: make sure the
# directory you specify has a "bin" subdirectory
CGTOOLS_V5T := /db/toolsrc/library/tools/vendors/cs/arm/arm-2007q3
CC_V5T := bin/arm-none-linux-gnueabi-gcc
CGTARGET := gnu.targets.arm.GCArmv5T

# compiler path and name for uClibc toolchain. NOTE: make sure the
# directory you specify has a "bin" subdirectory
CGTOOLS_UCARM9 := /db/toolsrc/library/tools/vendors/opensource/buildroot/10122007/build_arm/staging_dir/usr
CC_UCARM9 := bin/arm-linux-gcc

# WinCE toolchain.
WINCE_ROOTDIR := C:/WINCE600
WINCE_PROJECTROOT := $(WINCE_ROOTDIR)/_your_ProjectRoot_/Wince600/TI_EVM_3530_ARMV4I

# compiler path and name for TI C64x toolchain. NOTE: make sure the
# directory you specify has a "bin" subdirectory
CGTOOLS_C64P := /db/toolsrc/library/tools/vendors/ti/c6x/6.0.16/Linux
#CC_C64P      := bin/cl6x

# compiler path and name for TI C674 toolchain. NOTE: make sure the
# directory you specify has a "bin" subdirectory
CGTOOLS_C674 := /db/toolsrc/library/tools/vendors/ti/c6x/6.1.5/Linux
#CC_C674      := bin/cl6x

# compiler path and name for Linux 86 toolchain. NOTE: make sure the
# directory you specify has a "bin" subdirectory
CGTOOLS_LINUX86 := _your_Linux86_installation_directory
#CC_LINUX86   := bin/gcc

# -----------------------------------------------------------------------------

# Most users have no need to modify anything below this line.

# -----------------------------------------------------------------------------

# If we're a subcomponent, allow larger product settings to override our
# defaults.  The variable $(RULES_MAKE) can be overridden on the 'make'
# command-line if the location below is not correct (for example, if you
# want to use a Rules.make from some other location.
RULES_MAKE := $(CE_INSTALL_DIR)/../Rules.make
ifneq ($(wildcard $(RULES_MAKE)),)
include $(RULES_MAKE)
endif

# Note, some good defensive programming here could be to ensure $(DEVICES) and
# $(PROGRAMS) - and others! - don't contain any space characters

#
# Set XDCARGS to some of the variables above.  xdcrules.mak will pass this
# variable to the XDC build engine... which will load config.bld... which will
# extract these variables and use them to determine what to build and which
# toolchains to use.
#
# Note that not all of these variables need to be set to something valid.
# Unfortunately, since these vars are unconditionally assigned, your build line
# will be longer and more noisy than necessary (e.g., it will include CC_V5T
# assignment even if you're just building for WinCE.  While benign, it is
# annoying.  In future releases, we'll clean up this XDCARGS assignment and
# only include the vars that are required.
#
# Some background is here:
#     http://rtsc.eclipse.org/docs-tip/Command_-_xdc#Environment_Variables
#
XDCARGS= DEVICES=\"$(DEVICES)\" \
	 PROGRAMS=\"$(PROGRAMS)\" \
	 GPPOS=\"$(GPPOS)\" \
	 CGTOOLS_V5T=$(CGTOOLS_V5T) \
	 CC_V5T=$(CC_V5T) \
	 CGTOOLS_C64P=$(CGTOOLS_C64P) \
	 CGTOOLS_C674=$(CGTOOLS_C674) \
	 CGTOOLS_UCARM9=$(CGTOOLS_UCARM9) \
	 WINCE_ROOTDIR=$(WINCE_ROOTDIR) \
	 WINCE_PROJECTROOT=$(WINCE_PROJECTROOT) \
	 CGTOOLS_LINUX86=$(CGTOOLS_LINUX86)

# -----------------------------------------------------------------------------

# Utility variables - useful for over-riding these repos from the cmd line
CE_REPO ?= $(CE_INSTALL_DIR)/packages
CETOOLS_REPO ?= $(CE_INSTALL_DIR)/cetools/packages

# figure out what categories of devices we are to build for
ifneq (,$(findstring DM6446,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif
ifneq (,$(findstring DM6467,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif
ifneq (,$(findstring OMAP2530,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif
ifneq (,$(findstring OMAP3530,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif
ifneq (,$(findstring SDP3430,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif
ifneq (,$(findstring OMAPL137,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif
ifneq (,$(findstring OMAPL138,$(DEVICES)))
    DEVICES_DUALCPU := 1
endif

# Determine which components are necessary based on settings above
# Note, this ultimately just sets up the XDCPATH, and provides ease-of-use
# errors when we can catch them here, rather than progress further downstream
# and get [stranger] errors later

# All configurations require CE, XDC, XDAIS and FC
REQUIRE_CE    := 1
REQUIRE_XDC   := 1
REQUIRE_XDAIS := 1
REQUIRE_FC    := 1

ifneq (,$(findstring DM6446,$(DEVICES)))
    ifneq (, $(findstring APP_CLIENT, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_LINUXUTILS := 1
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LPM := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_LINUXUTILS := 1
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LPM := 1
	endif
        ifneq (, $(findstring WINCE, $(GPPOS) ))
            REQUIRE_WINCEUTILS := 1
            REQUIRE_CGTOOLS_WINCE := 1
            REQUIRE_LPM := 1
	endif
    endif
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
	REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_LINUXUTILS := 1
            REQUIRE_CGTOOLS_V5T := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_LINUXUTILS := 1
            REQUIRE_CGTOOLS_UCARM9 := 1
	endif
        ifneq (, $(findstring WINCE, $(GPPOS) ))
            REQUIRE_WINCEUTILS := 1
            REQUIRE_CGTOOLS_WINCE := 1
	endif
    endif
    ifneq (, $(findstring DSP_SERVER, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        REQUIRE_BIOS := 1
        REQUIRE_LPM := 1
        REQUIRE_CGTOOLS_C64P := 1
    endif
endif

ifneq (,$(findstring DM6467,$(DEVICES)))
    ifneq (, $(findstring APP_CLIENT, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
	REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring DSP_SERVER, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
    endif
endif

ifneq (,$(findstring DM355,$(DEVICES)))
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
endif

ifneq (,$(findstring DM357,$(DEVICES)))
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
endif

ifneq (,$(findstring DM365,$(DEVICES)))
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
endif

ifneq (,$(findstring DM6437,$(DEVICES)))
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
        REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
    endif
endif

ifneq (,$(findstring DM648,$(DEVICES)))
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
        REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
    endif
endif

ifneq (,$(findstring OMAP2530,$(DEVICES)))
    ifneq (, $(findstring APP_CLIENT, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
            REQUIRE_LPM := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
            REQUIRE_LPM := 1
	endif
    endif
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
	REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring DSP_SERVER, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        REQUIRE_BIOS := 1
        REQUIRE_LPM := 1
        REQUIRE_CGTOOLS_C64P := 1
    endif
endif

ifneq (,$(findstring OMAP3530,$(DEVICES)))
    ifneq (, $(findstring APP_CLIENT, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
            REQUIRE_LPM := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
            REQUIRE_LPM := 1
	endif
        ifneq (, $(findstring WINCE, $(GPPOS) ))
            REQUIRE_CGTOOLS_WINCE := 1
            REQUIRE_WINCEUTILS := 1
            REQUIRE_LPM := 1
	endif
    endif
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
	REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C64P := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring WINCE, $(GPPOS) ))
            REQUIRE_CGTOOLS_WINCE := 1
            REQUIRE_WINCEUTILS := 1
	endif
    endif
    ifneq (, $(findstring DSP_SERVER, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        REQUIRE_BIOS := 1
        REQUIRE_LPM := 1
        REQUIRE_CGTOOLS_C64P := 1
    endif
endif

ifneq (,$(findstring OMAPL137,$(DEVICES)))
    ifneq (, $(findstring APP_CLIENT, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
	REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C674 := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring DSP_SERVER, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C674 := 1
    endif
endif

ifneq (,$(findstring OMAPL138,$(DEVICES)))
    ifneq (, $(findstring APP_CLIENT, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
	REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C674 := 1
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_V5T := 1
            REQUIRE_LINUXUTILS := 1
	endif
        ifneq (, $(findstring LINUX_UCLIBC, $(GPPOS) ))
            REQUIRE_CGTOOLS_UCARM9 := 1
            REQUIRE_LINUXUTILS := 1
	endif
    endif
    ifneq (, $(findstring DSP_SERVER, $(PROGRAMS) ))
        REQUIRE_LINK := 1
        REQUIRE_BIOS := 1
        REQUIRE_CGTOOLS_C674 := 1
    endif
endif

ifneq (,$(findstring X86,$(DEVICES)))
    ifneq (, $(findstring APP_LOCAL, $(PROGRAMS) ))
        ifneq (, $(findstring LINUX_GCC, $(GPPOS) ))
            REQUIRE_CGTOOLS_LINUX86 := 1
	endif
    endif
endif

# EDMA3LLD is potentially required for all BIOS-based environments
ifeq ($(REQUIRE_BIOS), 1)
    REQUIRE_EDMA3LLD := 1
endif

# Build the XDC path from the necessary components, verifying along the way
# that the required compoments are present
XDC_PATH :=

ERRMSG = which is invalid (could not find file "$(TEST_FILE)"). Set this in <codec engine examples>/xdcpaths.mak! See the build documentation to correct this error.

# CE_INSTALL_DIR is the location of your Codec Engine.
ifeq ($(REQUIRE_CE), 1)
    TEST_FILE := $(CE_REPO)/ti/sdo/ce/package.xdc
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error CE_INSTALL_DIR is set to "$(CE_INSTALL_DIR)", $(ERRMSG))
    endif
    XDC_PATH := $(CE_REPO)
endif

# Add cetools to XDCPATH if 1) $(USE_CETOOLS_IF_EXISTS) is set, and
# 2) the CE distribution has "cetools/"
USING_CETOOLS := 0
ifeq ($(USE_CETOOLS_IF_EXISTS), 1)
    ifneq ($(wildcard $(CETOOLS_REPO)),)
        USING_CETOOLS := 1
        XDC_PATH := $(CETOOLS_REPO);$(XDC_PATH)
    endif
endif
ifeq ($(USING_CETOOLS),0)
    # XDAIS_INSTALL_DIR is the location of your XDAIS distribution
    ifeq ($(REQUIRE_XDAIS), 1)
        TEST_FILE := $(XDAIS_INSTALL_DIR)/packages/ti/xdais/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error XDAIS_INSTALL_DIR is set to "$(XDAIS_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(XDAIS_INSTALL_DIR)/packages
    endif

    # CMEM_INSTALL_DIR is the location of your Linux Utils distribution
    ifeq ($(REQUIRE_LINUXUTILS), 1)
        TEST_FILE := $(CMEM_INSTALL_DIR)/packages/ti/sdo/linuxutils/cmem/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error CMEM_INSTALL_DIR is set to "$(CMEM_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(CMEM_INSTALL_DIR)/packages
    endif

    # WINCEUTILS_INSTALL_DIR is the location of your WinCE Utils distribution
    ifeq ($(REQUIRE_WINCEUTILS), 1)
        TEST_FILE := $(WINCEUTILS_INSTALL_DIR)/packages/ti/sdo/winceutils/cmem/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error WINCEUTILS_INSTALL_DIR is set to "$(WINCEUTILS_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(WINCEUTILS_INSTALL_DIR)/packages
    endif

    # FC_INSTALL_DIR is the location of your Frameworks Components distribution
    ifeq ($(REQUIRE_FC), 1)
        TEST_FILE := $(FC_INSTALL_DIR)/packages/ti/sdo/fc/dskt2/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error FC_INSTALL_DIR is set to "$(FC_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(FC_INSTALL_DIR)/packages
    endif

    # BIOSUTILS_INSTALL_DIR is the location of your BIOSUTILS distribution
    ifeq ($(REQUIRE_BIOS), 1)
        TEST_FILE := $(BIOSUTILS_INSTALL_DIR)/packages/ti/bios/utils/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error BIOSUTILS_INSTALL_DIR is set to "$(BIOSUTILS_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(BIOSUTILS_INSTALL_DIR)/packages
    endif

    # LPM_INSTALL_DIR is the location of your LPM distribution
    ifeq ($(REQUIRE_LPM), 1)
        TEST_FILE := $(LPM_INSTALL_DIR)/packages/ti/bios/power/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error LPM_INSTALL_DIR is set to "$(LPM_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(LPM_INSTALL_DIR)/packages
    endif

    # EDMA3_LLD_INSTALL_DIR is the location of your EDMA3 LLD distribution
    ifeq ($(REQUIRE_EDMA3LLD), 1)
        TEST_FILE := $(EDMA3_LLD_INSTALL_DIR)/packages/ti/sdo/edma3/rm/package.xdc
        ifeq ($(wildcard $(TEST_FILE)),)
            $(error EDMA3_LLD_INSTALL_DIR is set to "$(EDMA3_LLD_INSTALL_DIR)", $(ERRMSG))
        endif
        XDC_PATH := $(XDC_PATH);$(EDMA3_LLD_INSTALL_DIR)/packages
    endif

endif

# BIOS_INSTALL_DIR is the location of your BIOS distribution
ifeq ($(REQUIRE_BIOS), 1)
    TEST_FILE := $(BIOS_INSTALL_DIR)/packages/ti/bios/package.xdc
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error BIOS_INSTALL_DIR is set to "$(BIOS_INSTALL_DIR)", $(ERRMSG))
    endif
    XDC_PATH := $(XDC_PATH);$(BIOS_INSTALL_DIR)/packages
endif

# DSPLINK_INSTALL_DIR is the location of your DSPLINK distribution
ifeq ($(REQUIRE_LINK), 1)
    TEST_FILE := $(DSPLINK_INSTALL_DIR)/dsplink/gpp/package.xdc
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error DSPLINK_INSTALL_DIR is set to "$(DSPLINK_INSTALL_DIR)", $(ERRMSG))
    endif
    XDC_PATH := $(XDC_PATH);$(DSPLINK_INSTALL_DIR)
endif

# XDC_INSTALL_DIR is the location of your XDCTOOLS installation.
ifeq ($(REQUIRE_XDC), 1)
    TEST_FILE := $(XDC_INSTALL_DIR)/packages/xdc/package.xdc
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error XDC_INSTALL_DIR is set to "$(XDC_INSTALL_DIR)", $(ERRMSG))
    endif
endif

# CGTOOLS_C64P is the location of your CGtools for C64P.
ifeq ($(REQUIRE_CGTOOLS_C64P), 1)
    TEST_FILE := $(CGTOOLS_C64P)/bin/cl6x*
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error CGTOOLS_C64P is set to "$(CGTOOLS_C64P)", $(ERRMSG))
    endif
endif

# CGTOOLS_C674 is the location of your CGtools for C674.
ifeq ($(REQUIRE_CGTOOLS_C674), 1)
    TEST_FILE := $(CGTOOLS_C674)/bin/cl6x*
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error CGTOOLS_C674 is set to "$(CGTOOLS_C674)", $(ERRMSG))
    endif
endif

# CGTOOLS_V5T is the location of your CGtools for GCC Linux.
ifeq ($(REQUIRE_CGTOOLS_V5T), 1)
    TEST_FILE := $(CGTOOLS_V5T)/$(CC_V5T)
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error CGTOOLS_V5T/CC_V5T is set to "$(CGTOOLS_V5T)/$(CC_V5T)", $(ERRMSG))
    endif
endif

# CGTOOLS_UCARM9 is the location of your CGtools for uclibc Linux.
ifeq ($(REQUIRE_CGTOOLS_UCARM9), 1)
    TEST_FILE := $(CGTOOLS_UCARM9)/$(CC_UCARM9)
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error CGTOOLS_UCARM9/CC_UCARM9 is set to "$(CGTOOLS_UCARM9)/$(CC_UCARM9)", $(ERRMSG))
    endif
endif

# CGTOOLS_LINUX86 is the location of your CGtools for X86 Linux.
ifeq ($(REQUIRE_CGTOOLS_LINUX86), 1)
    TEST_FILE := $(CGTOOLS_LINUX86)/bin/gcc
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error CGTOOLS_LINUX86 is set to "$(CGTOOLS_LINUX86)", $(ERRMSG))
    endif
endif

# WINCE_PROJECTROOT is the location of your WinCE Project Root.
ifeq ($(REQUIRE_CGTOOLS_WINCE), 1)
    TEST_FILE := $(WINCE_PROJECTROOT)/cesysgen/sdk/inc/stdarg.h
    ifeq ($(wildcard $(TEST_FILE)),)
        $(error WINCE_PROJECTROOT is set to "$(WINCE_PROJECTROOT)", $(ERRMSG))
    endif
endif

# XDC_PATH is complete. Any other components you could add as
# XDC_PATH := <your component>/packages;$(XDC_PATH)
