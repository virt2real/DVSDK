#!/bin/sh

cwd=`dirname $0`
. $cwd/common.sh

tftpcfg=/etc/xinetd.d/tftp
tftprootdefault=/tftpboot

tftp() {
    echo "
service tftp
{
protocol = udp
port = 69
socket_type = dgram
wait = yes
user = nobody
server = /usr/sbin/in.tftpd
server_args = $tftproot
disable = no
}
" | sudo tee $tftpcfg > /dev/null
     check_status
     echo
     echo "$tftpcfg successfully created"
}

echo "--------------------------------------------------------------------------------"
echo "Which directory do you want to be your tftp root directory?(if this directory does not exist it will be created for you)"
read -p "[ $tftprootdefault ] " tftproot

if [ ! -n "$tftproot" ]; then
    tftproot=$tftprootdefault
fi
echo $tftproot > $cwd/../.tftproot
echo "--------------------------------------------------------------------------------"

echo
echo "--------------------------------------------------------------------------------"
echo "This step will set up the tftp server in the $tftproot directory."
echo
echo "Note! This command requires you to have administrator priviliges (sudo access) "
echo "on your host."
read -p "Press return to continue"

if [ -d $tftproot ]; then
    echo
    echo "$tftproot already exists, not creating.."
else
    sudo mkdir -p $tftproot
    check_status
    sudo chmod 777 $tftproot
    check_status
    sudo chown nobody $tftproot
    check_status
fi

uimagesrc=`ls -1 $cwd/../psp/prebuilt-images/uImage*.bin`
uimage=`basename $uimagesrc`
if [ -f $tftproot/$uimage ]; then
    echo
    echo "$tftproot/$uimage already exists. The new installed file can be renamed and saved under the new name."
    echo "(r) rename (o) overwrite (s) skip copy "
    read -p "[r] " exists
    case "$exists" in
      s) echo "Skipping copy of $uimage, existing version will be used"
         ;;
      o) sudo cp $uimagesrc $tftproot
         check_status
         echo
         echo "Successfully overwritten $uimage in tftp root directory $tftproot"
         ;;
      *) dte="`date +%m%d%Y`_`date +%H`.`date +%M`"
         echo "Name of new uimage: "
         read -p "[ $uimage.$dte ]" newname
         if [ ! -n "$newname" ]; then
             newname="$uimage.$dte"
         fi
         sudo cp $uimagesrc $tftproot/$newname 
         check_status
         echo
         echo "Successfully copied $uimage to tftp root directory $tftproot as $newname"
         ;;
    esac
else
    sudo cp $uimagesrc $tftproot
    check_status
    echo
    echo "Successfully copied $uimage to tftp root directory $tftproot"
fi

echo
if [ -f $tftpcfg ]; then
    echo "$tftpcfg already exists.."

    if [ "`cat $tftpcfg | grep server_args | cut -d= -f2 | sed 's/^[ ]*//'`" \
          == "$tftproot" ]; then
        echo "$tftproot already exported for TFTP, skipping.."
    else
        echo "Copying old $tftpcfg to $tftpcfg.old"
        sudo cp $tftpcfg $tftpcfg.old
        check_status
        tftp
    fi
else
    tftp
fi

echo
echo "Restarting tftp server"
sudo /etc/init.d/xinetd stop
check_status
sleep 1
sudo /etc/init.d/xinetd start
check_status
echo "--------------------------------------------------------------------------------"
