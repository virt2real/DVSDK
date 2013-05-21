#!/bin/sh

echo
echo "--------------------------------------------------------------------------------"
echo "TISDK setup script"
echo
echo "This script will set up your development host for dvsdk development."
echo "Parts of this script require administrator priviliges (sudo access)."
echo "--------------------------------------------------------------------------------"

cwd=`dirname $0`
. $cwd/bin/common.sh

$cwd/bin/setup-host-check.sh
check_status

$cwd/bin/setup-package-install.sh
check_status

$cwd/bin/setup-targetfs-nfs.sh
check_status

$cwd/bin/setup-tftp.sh
check_status

$cwd/bin/setup-minicom.sh
check_status

$cwd/bin/setup-uboot-env.sh
check_status

echo
echo "TISDK setup completed!"
echo "Please continue reading the Software Developer's Guide for more information on"
echo "how to develop software on the EVM"
