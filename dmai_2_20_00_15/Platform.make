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
# PLATFORM CONFIGURATION:
#
#    This file configures the platforms for the DMAI Makefile system.
#    The variables are (append _<PLATFORM> at the end of each name):
#
#    PLATFORM_OS          - The operating system to build for, supported
#                           operating systems are currenly linux and bios
#                           (DSP/BIOS). Adding support for a new Operating
#                           System is substantial work.
#    PLATFORM_DEVICE      - The device to build for. See release notes for
#                           currently supported devices.  
#    PLATFORM_PERIPHERALS - Which device driver implementation to use. This
#                           is normally the same as PLATFORM_DEVICE, but some
#                           platforms like dm357 have the same peripheral driver
#                           implementation as another device (in this case
#                           dm6446). Also, if there is no peripheral driver
#                           support for your platform, use 'generic'. This will
#                           still allow you to build and run e.g. the
#                           codec applications.
#    PLATFORM_XDC_TARGET  - The RTSC target to use. This defines which tool
#                           chain you will be using. This is typically set to
#                           gnu.targets.arm.GCArmv5T (generic GCC target) for
#                           Linux and ti.targets.C64P (TMS320C64XX Plus target)
#                           for DSP/BIOS.
#    PLATFORM_XDC         - The RTSC platform to use. This defines which
#                           hardware platform (not only device but H/W board)
#                           you will be using. This in turn will select which
#                           libraries to pull from the DMAI component
#                           dependencies.
#
# Note that you can add your own platform below as long as the target
# operating system is supported.
#
#------------------------------------------------------------------------------

#------------------------------------------------------------------------------
# DM 3730 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm3730_al            = linux
PLATFORM_DEVICE_dm3730_al        = dm3730
PLATFORM_PERIPHERALS_dm3730_al   = omap3530
PLATFORM_XDC_TARGET_dm3730_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_dm3730_al           = ti.platforms.evm3530

#------------------------------------------------------------------------------
# OMAP 3530 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_o3530_al            = linux
PLATFORM_DEVICE_o3530_al        = omap3530
PLATFORM_PERIPHERALS_o3530_al   = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_o3530_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_o3530_al           = ti.platforms.evm3530

#------------------------------------------------------------------------------
# OMAP L137 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_ol137_al            = linux
PLATFORM_DEVICE_ol137_al        = omapl137
PLATFORM_PERIPHERALS_ol137_al   = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_ol137_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_ol137_al           = ti.platforms.evmOMAPL137

#------------------------------------------------------------------------------
# OMAP L138 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_ol138_al            = linux
PLATFORM_DEVICE_ol138_al        = omapl138
PLATFORM_PERIPHERALS_ol138_al   = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_ol138_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_ol138_al           = ti.platforms.evmOMAPL138

#------------------------------------------------------------------------------
# DM355 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm355_al        = linux
PLATFORM_DEVICE_dm355_al    = dm355
PLATFORM_PERIPHERALS_dm355_al   = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_dm355_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_dm355_al       = ti.platforms.evmDM355

#------------------------------------------------------------------------------
# DM365 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm365_al        = linux
PLATFORM_DEVICE_dm365_al    = dm365
PLATFORM_PERIPHERALS_dm365_al   = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_dm365_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_dm365_al       = ti.platforms.evmDM365

#------------------------------------------------------------------------------
# DM368 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm368_al        = linux
PLATFORM_DEVICE_dm368_al    = dm368
PLATFORM_PERIPHERALS_dm368_al   = dm365
PLATFORM_XDC_TARGET_dm368_al    = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_dm368_al       = ti.platforms.evmDM365

#------------------------------------------------------------------------------
# DM6446 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm6446_al       = linux
PLATFORM_DEVICE_dm6446_al   = dm6446
PLATFORM_PERIPHERALS_dm6446_al  = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_dm6446_al   = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_dm6446_al      = ti.platforms.evmDM6446

#------------------------------------------------------------------------------
# DM6467 ARM Linux variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm6467_al       = linux
PLATFORM_DEVICE_dm6467_al   = dm6467
PLATFORM_PERIPHERALS_dm6467_al  = $(PLATFORM_DEVICE)
PLATFORM_XDC_TARGET_dm6467_al   = gnu.targets.arm.GCArmv5T
PLATFORM_XDC_dm6467_al      = ti.platforms.evmDM6467

#------------------------------------------------------------------------------
# DM6467 DSP/BIOS variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm6467_db           = bios
PLATFORM_DEVICE_dm6467_db       = dm6467
PLATFORM_PERIPHERALS_dm6467_db  = generic
PLATFORM_XDC_TARGET_dm6467_db   = ti.targets.C64P
PLATFORM_XDC_dm6467_db          = ti.platforms.evmDM6467

#------------------------------------------------------------------------------
# DM6446 DSP/BIOS variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm6446_db           = bios
PLATFORM_DEVICE_dm6446_db       = dm6446
PLATFORM_PERIPHERALS_dm6446_db  = generic
PLATFORM_XDC_TARGET_dm6446_db   = ti.targets.C64P
PLATFORM_XDC_dm6446_db          = ti.platforms.evmDM6446

#------------------------------------------------------------------------------
# DM6437 DSP/BIOS variables.
#------------------------------------------------------------------------------
PLATFORM_OS_dm6437_db           = bios
PLATFORM_DEVICE_dm6437_db       = dm6437
PLATFORM_PERIPHERALS_dm6437_db  = generic
PLATFORM_XDC_TARGET_dm6437_db   = ti.targets.C64P
PLATFORM_XDC_dm6437_db          = ti.platforms.evmDM6437
