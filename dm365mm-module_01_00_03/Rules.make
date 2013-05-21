# include the rules file to get the path
-include ../../Rules.make

# The directory that points to your kernel source directory. This is used
# for building the cmemk.ko kernel module, as the kernel's build system
# gets invoked. Note that this also means that the below C_FLAGS etc. will
# be ignored when building this particular module.
KERNEL_DIR=$(LINUXKERNEL_INSTALL_DIR)

# Whether or not to use the udev pseudo filesystem to generate the /dev
# filesystem for cmem. This depends on your kernel configuration. If udev is
# not used, the /dev/cmem file has to be created manually using mknod.

USE_UDEV=0

# The maximum number of memory pools for cmem.
MAX_POOLS=10

