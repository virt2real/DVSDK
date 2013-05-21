# Where to copy the resulting executables and data to (when executing 'make
# install') in a proper file structure. This EXEC_DIR should either be visible
# from the target, or you will have to copy this (whole) directory onto the
# target filesystem.
EXEC_DIR=/opt/mv_pro_4.0/montavista/pro/devkit/arm/v5t_le/target/opt/dvevm


# The prefix to be added before the GNU compiler tools (optionally including
# path), i.e. "arm_v5t_le-" or "/opt/bin/arm_v5t_le-".

# For "kernel_org" builds
MVTOOL_PREFIX=/db/toolsrc/library/vendors2005/cs/arm/arm-2008q1-126/bin/arm-none-linux-gnueabi-

# For Davinci builds
#MVTOOL_PREFIX=/db/toolsrc/library/vendors2005/mvl/arm/mvl5.0/montavista/pro/devkit/arm/v5t_le/bin/arm_v5t_le-

# Equivalent path for uClibc compiler tools
UCTOOL_PREFIX=/db/toolsrc/library/vendors2005/opensource/buildroot/10122007/build_arm/staging_dir/usr/bin/arm-linux-


# The directory that points to your kernel source directory. This is used
# for building the cmemk.ko kernel module, as the kernel's build system
# gets invoked. Note that this also means that the below C_FLAGS etc. will
# be ignored when building this particular module.

# For DM355/DM365 2.6.31 Linux kernel
LINUXKERNEL_INSTALL_DIR=/db/toolsrc/library/vendors2005/kernel_org/arm/KERNEL_DEV.DaVinciPSP.03.00.00.00/DaVinci-PSP-SDK-DEV.DaVinciPSP.03.00.00.00/kernel/dm365

# LSP 2.10 used for DM365
#LINUXKERNEL_INSTALL_DIR=/db/toolsrc/library/vendors2005/mvl/arm/LSP_210/REL_LSP_02_10_00_08/dm365/montavista/pro/devkit/lsp/ti-davinci/linux-2.6.18_pro500

#
# The following are kept around for TI developer convenience ...
#
#LINUXKERNEL_INSTALL_DIR=/db/toolsrc/library/vendors2005/mvl/arm/DaVinci-Linux-Rel_mvl401c/Linux
#LINUXKERNEL_INSTALL_DIR=/db/toolsrc/library/vendors2005/mistral/arm/omap2530evm-1.2/linux-2.6.23
#LINUXKERNEL_INSTALL_DIR=/db/toolsrc/library/vendors2005/mvl/arm/omap3/OMAP35x_SDK_0.9.7/src/linux/kernel_org/2.6_kernel
#LINUXKERNEL_INSTALL_DIR=/db/toolsrc/library/vendors2005/wtsd/omap3430/CSSD_Linux_12.9baseport/src/linux/kernel_org/2.6_kernel


# If we're a subcomponent, allow larger product settings to override our
# defaults.  The variable $(RULES_MAKE) can be overridden on the 'make'
# command-line if the location below is not correct (for example, when this
# module is not part of an overlying DVSDK).
RULES_MAKE := ../../../../../../../../Rules.make
-include $(RULES_MAKE)


# Whether or not to use the udev pseudo filesystem to generate the /dev
# filesystem for cmem. This depends on your kernel configuration. If udev is
# not used, the /dev/cmem file has to be created manually using mknod.
USE_UDEV=1

