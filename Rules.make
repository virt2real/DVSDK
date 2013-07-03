MOD_DIR=.

# Define target platform.
PLATFORM=dm365

# The installation directory of the DVSDK.
#DVSDK_INSTALL_DIR=/usr/local/dvsdk
DVSDK_INSTALL_DIR=.

# For backwards compatibility
DVEVM_INSTALL_DIR=$(DVSDK_INSTALL_DIR)

# Where the Codec Engine package is installed.
CE_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/codec-engine_2_26_02_11

# Where the codecs are installed.
CODEC_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/codecs-dm365_4_02_00_00

# Where DMAI package is installed.
DMAI_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/dmai_2_20_00_15

# Where the SDK demos are installed
DEMO_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/dvsdk-demos_4_02_00_01

# Where the DVTB package is installed.
DVTB_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/dvtb_4_20_18

# Where the Framework Components package is installed.
FC_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/framework-components_2_26_00_01

# Where the DM365mm module is installed.
DM365MM_MODULE_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/dm365mm-module_01_00_03

# Where the PSP is installed.
PSP_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/psp

# Where the MFC Linux Utils package is installed.
#LINUXUTILS_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/linuxutils_2_26_01_02
LINUXUTILS_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/linuxutils_2_26_03_06
CMEM_INSTALL_DIR=$(LINUXUTILS_INSTALL_DIR)

# Where the XDAIS package is installed.
XDAIS_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/xdais_6_26_01_03

# Where the RTSC tools package is installed.
XDC_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/xdctools_3_16_03_36

# The directory that points to your kernel source directory.
#LINUXKERNEL_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/psp/linux-2.6.32.17-psp03.01.01.39
#LINUXKERNEL_INSTALL_DIR=/opt/GIT/3.9/linux-davinci

# Where temporary Linux headers and libs are installed.
LINUXLIBS_INSTALL_DIR=$(DVSDK_INSTALL_DIR)/linux-devkit/arm-none-linux-gnueabi/usr

# The prefix to be added before the GNU compiler tools (optionally including # path), i.e. "arm_v5t_le-" or "/opt/bin/arm_v5t_le-".
#CSTOOL_DIR=/opt/codesourcery/arm-2009q1/
#CSTOOL_DIR=/opt/codesourcery/arm-2010q1/
#CSTOOL_PREFIX=$(CSTOOL_DIR)/bin/arm-none-linux-gnueabi-

MVTOOL_DIR=$(CSTOOL_DIR)
MVTOOL_PREFIX=$(CSTOOL_PREFIX)

# Where to copy the resulting executables
EXEC_DIR=$(MOD_DIR)/install/$(PLATFORM)

