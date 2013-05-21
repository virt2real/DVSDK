#!/bin/sh

. `dirname $0`/common.sh

cmd="sudo apt-get install xinetd tftpd nfs-kernel-server minicom build-essential libncurses5-dev uboot-mkimage autoconf automake"
echo "--------------------------------------------------------------------------------"
echo "This step will make sure you have the proper host support packages installed"
echo "using the following command: $cmd"
echo
echo "Note! This command requires you to have administrator priviliges (sudo access) "
echo "on your host."
echo -n "Press return to continue"
read

echo
$cmd
check_status
echo
echo "Package verification and installation successfully completed"
echo "--------------------------------------------------------------------------------"
echo
