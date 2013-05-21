#!/bin/sh

cwd=`dirname $0`
. $cwd/common.sh

portdefault="/dev/ttyS0"
minicomcfg=${HOME}/.minirc.dfl

echo
echo "--------------------------------------------------------------------------------"
echo "This step will set up minicom (serial communication application) for"
echo "DVSDK development"
echo
echo "Which serial port do you want to use with minicom?"
read -p "[ $portdefault ] " port

if [ ! -n "$port" ]; then
    port=$portdefault
fi

if [ -f $minicomcfg ]; then
    cp $minicomcfg $minicomcfg.old
    echo
    echo "Copied existing $minicomcfg to $minicomcfg.old"
fi

echo "pu port             $port
pu baudrate         115200
pu bits             8
pu parity           N
pu stopbits         1
pu minit
pu mreset
pu mdialpre
pu mdialsuf
pu mdialpre2
pu mdialsuf2
pu mdialpre3
pu mdialsuf3
pu mconnect
pu mnocon1          NO CARRIER
pu mnocon2          BUSY
pu mnocon3          NO DIALTONE
pu mnocon4          VOICE
pu rtscts           No" | tee $minicomcfg > /dev/null
check_status

echo
echo "Configuration saved to $minicomcfg. You can change it further from inside"
echo "minicom, see the Software Development Guide for more information."
echo "--------------------------------------------------------------------------------"
