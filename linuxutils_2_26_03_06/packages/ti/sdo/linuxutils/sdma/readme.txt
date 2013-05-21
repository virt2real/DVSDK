
Description
===========
This tree contains a module for managing the SDMA resources (also called DMA4)
on the OMAP3430 (and OMAP3530) from user mode in Linux.

Owner
=====
Rob - Please consult with me before committing changes.

Dependencies
============
Needs a Linux 2.6 kernel, and a GCC tool chain that is verified with this
kernel.  Verified to compile with Cellular Systems Baseport 12.9 Linux 2.6.22
on OMAP3430.

How to build
============

Edit the top level Rules.make. The comments in this file should make the
configuration self explanatory. Then type 'make' followed by 'make install'.
Note that you need to have permissions where your install directory is. Many
target filesystems are owned by root, and therefore you would type 'make'
as a normal user, but 'make install' as root.

The build system works as follows. If a directory is not a leaf in the
directory tree it's Makefile will just be traversing directories below it
(the ones contained in the SUBDIRS file, one on each line).

If the directory is a leaf in the tree the Makefile will take all '*.c' files
and generate an executable from them (except for the "data" dir of course)
with the same name as the directory that contains the files. Note that these
Makefiles need a ROOTDIR file which contains the path to where the Rules.make
is found, as the Makefiles include the system configuration.

When you invoke 'make install' the executables and data will be copied to your
INSTALL_DIR (given in Rules.make). The executables with debugging information
in them will have a 'd' appended to their name.

You can invoke the build system from any level in the tree. Valid targets
are:

make
make release
make debug
make install
make clean
make docs (Top level directory only)

Note! The kernel modules themselves uses the kernel's own build system and
don't follow this convention.

Misc
====
