#
#  Copyright 2010 by Texas Instruments Incorporated.
#  
#

#!/bin/sh
#
unset INCLUDE
unset LIB
unset CL

dir=${1%/*}
cmdbin=/cygdrive/${dir%%:*}${dir#?:}
export PATH=$cmdbin:$cmdbin/../../common/msdev98/bin

"$@"
#
#  @(#) microsoft.targets; 1, 0, 2, 0,387; 2-24-2010 16:24:02; /db/ztree/library/trees/xdctargets/xdctargets-b36x/src/
#

