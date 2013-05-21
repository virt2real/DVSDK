#!/bin/sh

cwd=`dirname $0`
. $cwd/common.sh

dstdefault="${HOME}/targetfs"
echo "--------------------------------------------------------------------------------"
echo "In which directory do you want to install the target filesystem?(if this directory does not exist it will be created)"
read -p "[ $dstdefault ] " dst

if [ ! -n "$dst" ]; then
    dst=$dstdefault
fi
echo "--------------------------------------------------------------------------------"

echo
echo "--------------------------------------------------------------------------------"
echo "This step will extract the target filesystem to $dst"
echo
echo "Note! This command requires you to have administrator priviliges (sudo access) "
echo "on your host."
read -p "Press return to continue"

extract_fs() {
    fstar=`ls -1 $cwd/../filesystem/??sdk*rootfs.tar.gz`
    sudo mkdir -p $1
    check_status
    sudo tar xzf $fstar -C $1
    check_status
    echo
    echo "Successfully extracted `basename $fstar` to $1"
}

if [ -d $dst ]; then
    echo "$dst already exists"
    echo "(r) rename existing filesystem (o) overwrite existing filesystem (s) skip filesystem extraction"
    read -p "[r] " exists
    case "$exists" in
      s) echo "Skipping filesystem extraction"
         echo "WARNING! Keeping the previous filesystem may cause compatibility problems if you are upgrading the SDK"
         ;; 
      o) sudo rm -rf $dst
         echo "Old $dst removed"
         extract_fs $dst
         ;;
      *) dte="`date +%m%d%Y`_`date +%H`.`date +%M`"
         echo "Path for old filesystem:"
         read -p "[ $dst.$dte ]" old
         if [ ! -n "$old" ]; then
             old="$dst.$dte"
         fi
         sudo mv $dst $old
         check_status
         echo
         echo "Successfully moved old $dst to $old"
         extract_fs $dst
         ;;
    esac
else
    extract_fs $dst
fi
echo $dst > $cwd/../.targetfs
echo "--------------------------------------------------------------------------------"

platform=`grep PLATFORM= $cwd/../Rules.make | cut -d= -f2`
echo
echo "--------------------------------------------------------------------------------"
echo "This step will update the EXEC_DIR variables in the Rules.make file"
echo "This will facilitate the SDK to install (with make install) rebuilt binaries in"
echo "    $dst"
echo
echo "The files will be available from / on the target."
echo
echo "This setting can be changed later by editing Rules.make and changing the"
echo "EXEC_DIR variable."
echo
read -p "Press return to continue"

sed -i "s=EXEC_DIR\=.*$=EXEC_DIR\=$dst=g" $cwd/../Rules.make
check_status

echo "Rules.make edited successfully.."
echo "--------------------------------------------------------------------------------"

echo
echo "--------------------------------------------------------------------------------"
echo "This step will export your target filesystem for NFS access."
echo
echo "Note! This command requires you to have administrator priviliges (sudo access) "
echo "on your host."
read -p "Press return to continue"

grep $dst /etc/exports > /dev/null
if [ "$?" -eq "0" ]; then
    echo "$dst already NFS exported, skipping.."
else
    sudo chmod 666 /etc/exports
    check_status
    sudo echo "$dst *(rw,nohide,insecure,no_subtree_check,async,no_root_squash)" >> /etc/exports
    check_status
    sudo chmod 644 /etc/exports
    check_status
fi

echo
sudo /etc/init.d/nfs-kernel-server stop
check_status
sleep 1
sudo /etc/init.d/nfs-kernel-server start
check_status
echo "--------------------------------------------------------------------------------"
