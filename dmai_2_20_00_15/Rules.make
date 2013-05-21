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

#------------------------------------------------------------------------------
# DVSDK SOFTWARE COMPONENTS:
#
#    Set the locations of the DVSDK software components. Software component
#    locations are specified with an environment variable (e.g. CE_INSTALL_DIR).
#    This variable is typically set to be the most recent version of the
#    software supported by DMAI.
#
#    Each platform has it's own set of DVSDK software components, and the
#    current platform is set using the PLATFORM variable. See the release
#    notes for currently supported platforms, and the user's guide for more
#    information on how to build DMAI.
#
#    Available variables (append _<PLATFORM> at the end of each name):
#
#    CE_INSTALL_DIR          - Points to the installation directory of Codec
#                              Engine. This directory should have a packages/
#                              directory inside.
#    CODEC_INSTALL_DIR       - Points to the installation directory of
#                              multimedia codecs. This directory should have a
#                              packages/ directory inside.
#    LINK_INSTALL_DIR        - Points to the installation directory of DSP Link.
#                              This directory should have a packages/ directory
#                              inside.
#    CMEM_INSTALL_DIR        - Points to the installation directory of CMEM.
#                              This directory should have a packages/ directory
#                              inside.
#    FC_INSTALL_DIR          - Points to the installation directory of Framework
#                              Components. This directory should have a
#                              packages/ directory inside.
#    LPM_INSTALL_DIR         - Points to the installation directory of the Local
#                              Power Manager. This directory should have a
#                              packages/ directory inside.
#    XDAIS_INSTALL_DIR       - Points to the installation directory of the XDAIS
#                              Algorithm Standard. This directory should have a
#                              packages/ directory inside.
#    BIOS_INSTALL_DIR        - Points to the installation directory of the
#                              DSP/BIOS Real Time Operating System. This
#                              directory should have a packages/ directory
#                              inside.
#    LINUXLIBS_INSTALL_DIR   - Points to the installation directory of 
#                              additional linux libraries needed. This
#                              directory should have usr/, lib/ and include/
#                              directories inside.
#    LINUXKERNEL_INSTALL_DIR - Points to the installation directory of the 
#                              Linux kernel. This directory should have
#                              a Documentation/ directory inside.
#    CROSS_COMPILE           - Points to the GCC cross compilation tool chain.
#                              This variable contains the full path including
#                              the prefix up to the actual "gcc" command.
#    XDC_INSTALL_DIR         - Points to the installation directory of the RTSC
#                              tools. This directory should have a packages/
#                              directory inside.
#    EDMA3_LLD_INSTALL_DIR   - Points to where the EDMA3 Low Level Driver
#                              is installed. This directory should have a
#                              packages/ directory inside.
#    CODEGEN_INSTALL_DIR     - Points to where the TI c6x codegen tools are
#                              installed. This directory should have bin/,
#                              lib/ and include/ directories inside.
#    BIOSUTILS_INSTALL_DIR   - Points to where the DSP/BIOS utilities are
#                              installed. This directory should have a
#                              packages/ directory inside.
#    USER_XDC_PATH           - Points to additional RTSC packages to be
#                              included in the build of the applications
#                              separated by semicolon.
#    EXEC_DIR                - Points to where the DMAI applications should
#                              be installed when 'make install' is executed.
#                              Typically this should point to your NFS mounted
#                              target file system for Linux targets.
#
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# The platform to build DMAI for, see release notes for supported platforms.
# Note that each platform override designation contains a suffix such as
# "_al" or "_db".  This is to designate the operating system environment
# for that platform.  The following operating system environments are
# currently supported:
#
#   al:  ARM/Linux
#   db:  DSP/BIOS
#
# This designation is required as some ARM+DSP platforms may support running
# DMAI under multiple environments.
#------------------------------------------------------------------------------
PLATFORM=o3530_al

ARAGO_SDK_INSTALL_DIR = $(HOME)/arago-2009.11-armv5te-linux-gnueabi-sdk/opt/arago-2009.11

#------------------------------------------------------------------------------
# DM 3730 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm3730_al = \
    $(HOME)/codec-engine_2_25_05_16
CMEM_INSTALL_DIR_dm3730_al = \
    $(CE_INSTALL_DIR_dm3730_al)/cetools
FC_INSTALL_DIR_dm3730_al = \
    $(CE_INSTALL_DIR_dm3730_al)/cetools
LPM_INSTALL_DIR_dm3730_al = \
    $(CE_INSTALL_DIR_dm3730_al)/cetools
XDAIS_INSTALL_DIR_dm3730_al = \
    $(CE_INSTALL_DIR_dm3730_al)/cetools
CODEC_INSTALL_DIR_dm3730_al = \
    $(HOME)/codecs-dm3730_1_00_00
LINK_INSTALL_DIR_dm3730_al = \
    $(HOME)/dsplink_1_65_00_02
LINUXLIBS_INSTALL_DIR_dm3730_al = \
    $(HOME)/linux-devkit/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_dm3730_al = \
    $(ARAGO_SDK_INSTALL_DIR)/arm-none-linux-gnueabi/usr
CROSS_COMPILE_dm3730_al = \
    $(HOME)/arm-2009q1/bin/arm-none-linux-gnueabi-
XDC_INSTALL_DIR_dm3730_al = \
    $(HOME)/xdctools_3_16_03_36
C6ACCEL_INSTALL_DIR_dm3730_al = \
    $(HOME)/c6accel_1_00_00_04
EXEC_DIR_dm3730_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# OMAP 3530 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_o3530_al = \
    $(HOME)/codec-engine_2_25_05_16
CMEM_INSTALL_DIR_o3530_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
FC_INSTALL_DIR_o3530_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
LPM_INSTALL_DIR_o3530_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_o3530_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
CODEC_INSTALL_DIR_o3530_al = \
    $(HOME)/codecs-omap3530_1_01_00
LINK_INSTALL_DIR_o3530_al = \
    $(HOME)/dsplink_1_65_00_02
LINUXLIBS_INSTALL_DIR_o3530_al = \
    $(HOME)/linux-devkit/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_o3530_al = \
    $(ARAGO_SDK_INSTALL_DIR)/arm-none-linux-gnueabi/usr
CROSS_COMPILE_o3530_al = \
    $(HOME)/arm-2009q1/bin/arm-none-linux-gnueabi-
XDC_INSTALL_DIR_o3530_al = \
    $(HOME)/xdctools_3_16_03_36
C6ACCEL_INSTALL_DIR_o3530_al = \
    $(HOME)/c6accel_1_00_00_04
EXEC_DIR_o3530_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# OMAPL137 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_ol137_al = \
    $(HOME)/codec_engine_2_25_00_05
CMEM_INSTALL_DIR_ol137_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
FC_INSTALL_DIR_ol137_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_ol137_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
LINK_INSTALL_DIR_ol137_al = \
    $(HOME)/dsplink_linux_1_64
CODEC_INSTALL_DIR_ol137_al = \
    $(HOME)/cs1omapl138_1_00_00-l137
LINUXLIBS_INSTALL_DIR_ol137_al = \
    $(ARAGO_SDK_INSTALL_DIR)/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_ol137_al = \
    $(HOME)/LSP_DaVinci_03_01_00_03
CROSS_COMPILE_ol137_al = \
    $(HOME)/arm-2009q1/bin/arm-none-linux-gnueabi-
USER_XDC_PATH_ol137_al = \
    $(CE_INSTALL_DIR)/examples
XDC_INSTALL_DIR_ol137_al = \
    $(HOME)/xdctools_3_15_01_59
EXEC_DIR_ol137_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# OMAPL138 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_ol138_al = \
    $(HOME)/codec_engine_2_25_00_05
CMEM_INSTALL_DIR_ol138_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
FC_INSTALL_DIR_ol138_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_ol138_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
LINK_INSTALL_DIR_ol138_al = \
    $(HOME)/dsplink_linux_1_64
CODEC_INSTALL_DIR_ol138_al = \
    $(HOME)/cs1omapl138_1_00_00
LINUXLIBS_INSTALL_DIR_ol138_al = \
    $(ARAGO_SDK_INSTALL_DIR)/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_ol138_al = \
    $(HOME)/DaVinci-PSP-SDK-03.20.00.08/src/kernel/linux-03.20.00.08/
CROSS_COMPILE_ol138_al = \
    $(HOME)/arm-2009q1/bin/arm-none-linux-gnueabi-
USER_XDC_PATH_ol138_al = \
    $(CE_INSTALL_DIR)/examples
XDC_INSTALL_DIR_ol138_al = \
    $(HOME)/xdctools_3_15_01_59
C6ACCEL_INSTALL_DIR_ol138_al = \
    $(HOME)/c6accel_1_00_00_04
EXEC_DIR_ol138_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

DVSDK_INSTALL_DIR=${HOME}/ti-dvsdk_dm365-evm_4_00_00_06

#------------------------------------------------------------------------------
# DM368 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/codec-engine_2_25_02_11
CMEM_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/linuxutils_2_25_02_08
FC_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/framework-components_2_25_01_05
XDAIS_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/xdais_6_25_02_11
CODEC_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/codecs-dm365_03_10_00_06
LINUXLIBS_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/linux-devkit/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_dm368_al = \
    $(DVSDK_INSTALL_DIR)/psp/linux-kernel-source
CROSS_COMPILE_dm368_al = \
    /library/cs/arm-2009q1/bin/arm-none-linux-gnueabi-
USER_XDC_PATH_dm368_al = \
    $(CE_INSTALL_DIR_dm368_al)/examples
XDC_INSTALL_DIR_dm368_al = \
    $(DVSDK_4_00_INSTALL_DIR_o3530_al)/xdctools_3_16_03_36
EXEC_DIR_dm368_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

DVSDK_3_10_INSTALL_DIR=${HOME}/dvsdk_3_10_00_16/dvsdk_3_10_00_16

#------------------------------------------------------------------------------
# DM365 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/codec-engine_2_25_02_11
CMEM_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/linuxutils_2_25_02_08
FC_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/framework-components_2_25_01_05
XDAIS_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/xdais_6_25_02_11
CODEC_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/codecs-dm365_03_10_00_06
LINUXLIBS_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/linux-devkit/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_dm365_al = \
    $(DVSDK_INSTALL_DIR)/psp/linux-kernel-source
CROSS_COMPILE_dm365_al = \
    /library/cs/arm-2009q1/bin/arm-none-linux-gnueabi-
USER_XDC_PATH_dm365_al = \
    $(CE_INSTALL_DIR_dm365_al)/examples
XDC_INSTALL_DIR_dm365_al = \
    $(DVSDK_4_00_INSTALL_DIR_o3530_al)/xdctools_3_16_03_36
EXEC_DIR_dm365_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

DVSDK_3_10_INSTALL_DIR=${HOME}/dvsdk_3_10_00_16/dvsdk_3_10_00_16

#------------------------------------------------------------------------------
# DM355 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/codec_engine_2_25_01_06
CMEM_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/linuxutils_2_25_01_06
FC_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/framework_components_2_25_01_05
XDAIS_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/xdais_6_25_01_08
CODEC_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/dm355_codecs_03_10_00_00
LINUXLIBS_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/linuxlibs-2009.11-armv5te
LINUXKERNEL_INSTALL_DIR_dm355_al = \
    $(DVSDK_3_10_INSTALL_DIR)/git
CROSS_COMPILE_dm355_al = \
    /library/cs/arm-2009q1/bin/arm-none-linux-gnueabi-
USER_XDC_PATH_dm355_al = \
    $(CE_INSTALL_DIR_dm355_al)/examples
XDC_INSTALL_DIR_dm355_al = \
    $(HOME)/xdctools_3_16_03_36
EXEC_DIR_dm355_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# DM6446 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm6446_al = \
    $(HOME)/codec_engine_2_25_00_05
CMEM_INSTALL_DIR_dm6446_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
FC_INSTALL_DIR_dm6446_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_dm6446_al = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
LINK_INSTALL_DIR_dm6446_al = \
    $(HOME)/dsplink_linux_1_64
CODEC_INSTALL_DIR_dm6446_al = \
    $(HOME)/dm6446_dvsdk_combos_2_05
LINUXLIBS_INSTALL_DIR_dm6446_al = \
    $(ARAGO_SDK_INSTALL_DIR)/arm-none-linux-gnueabi/usr
LINUXKERNEL_INSTALL_DIR_dm6446_al = \
    $(HOME)/LSP_DaVinci_03_01_00_03
CROSS_COMPILE_dm6446_al = \
    $(HOME)/arm-2009q1/bin/arm-none-linux-gnueabi-
XDC_INSTALL_DIR_dm6446_al = \
    $(HOME)/xdctools_3_15_01_59
EXEC_DIR_dm6446_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# DM6467 ARM Linux components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/codec_engine_2_25_01_06
CMEM_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/linuxutils_2_25_01_06
FC_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/framework_components_2_25_01_05
XDAIS_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/xdais_6_25_01_08
LINK_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/dsplink_linux_1_64
LINUXLIBS_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/linuxlibs-2009.11-armv5te
LINUXKERNEL_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/git
CROSS_COMPILE_dm6467_al = \
    /library/cs/arm-2009q1/bin/arm-none-linux-gnueabi-
CODEC_INSTALL_DIR_dm6467_al = \
    $(DVSDK_3_10_INSTALL_DIR)/cs2dm6467_1_00_00_08
XDC_INSTALL_DIR_dm6467_al = \
    /library/xdc/xdctools_3_15_01_59
EXEC_DIR_dm6467_al = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# DM6467 DSP/BIOS components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm6467_db = \
    $(HOME)/codec_engine_2_25_00_05
FC_INSTALL_DIR_dm6467_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
BIOSUTILS_INSTALL_DIR_dm6467_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_dm6467_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
EDMA3_LLD_INSTALL_DIR_dm6467_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
BIOS_INSTALL_DIR_dm6467_db = \
    $(HOME)/bios_5_33_05
CODEC_INSTALL_DIR_dm6467_db = \
    $(HOME)/dm6467_dvsdk_combos_2_05
CODEGEN_INSTALL_DIR_dm6467_db = \
    $(HOME)/cg6x_6_0_21
XDC_INSTALL_DIR_dm6467_db = \
    $(HOME)/xdctools_3_15_01_59
EXEC_DIR_dm6467_db = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# DM6446 DSP/BIOS components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm6446_db = \
    $(HOME)/codec_engine_2_25_00_05
FC_INSTALL_DIR_dm6446_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
BIOSUTILS_INSTALL_DIR_dm6446_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_dm6446_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
EDMA3_LLD_INSTALL_DIR_dm6446_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
BIOS_INSTALL_DIR_dm6446_db = \
    $(HOME)/bios_5_33_05
CODEGEN_INSTALL_DIR_dm6446_db = \
    $(HOME)/cg6x_6_0_21
CODEC_INSTALL_DIR_dm6446_db = \
    $(HOME)/dm6446_dvsdk_combos_2_05
XDC_INSTALL_DIR_dm6446_db = \
    $(HOME)/xdctools_3_15_01_59
EXEC_DIR_dm6446_db = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)

#------------------------------------------------------------------------------
# DM6437 DSP/BIOS components.
#------------------------------------------------------------------------------
CE_INSTALL_DIR_dm6437_db = \
    $(HOME)/codec_engine_2_25_00_05
FC_INSTALL_DIR_dm6437_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
BIOSUTILS_INSTALL_DIR_dm6437_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
XDAIS_INSTALL_DIR_dm6437_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
EDMA3_LLD_INSTALL_DIR_dm6437_db = \
    $(CE_INSTALL_DIR_o3530_al)/cetools
BIOS_INSTALL_DIR_dm6437_db = \
    $(HOME)/bios_5_33_05
CODEGEN_INSTALL_DIR_dm6437_db = \
    $(HOME)/cg6x_6_0_21
CODEC_INSTALL_DIR_dm6437_db = \
    $(HOME)/dm6446_dvsdk_combos_2_05
XDC_INSTALL_DIR_dm6437_db = \
    $(HOME)/xdctools_3_15_01_59
EXEC_DIR_dm6437_db = \
    $(HOME)/workdir/filesys/opt/dvsdk/$(PLATFORM)
