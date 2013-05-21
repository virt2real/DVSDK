#!/bin/sh

echo
echo "--------------------------------------------------------------------------------"
echo "Verifying Linux host distribution"
host=`lsb_release -a 2>/dev/null | grep Codename: | awk {'print $2'}`
if [ "$host" != "lucid" ]; then
    echo "Unsupported host machine, only Ubuntu 10.04 LTS supported"
    exit 1
fi
echo "Ubuntu 10.04 LTS found successfully, continuing.."
echo "--------------------------------------------------------------------------------"
echo
