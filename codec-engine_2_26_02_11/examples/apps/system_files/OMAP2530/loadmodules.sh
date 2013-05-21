#
#  Copyright (c) 2008, Texas Instruments Incorporated
#  All rights reserved.
# 
#  Redistribution and use in source and binary forms, with or without
#  modification, are permitted provided that the following conditions
#  are met:
# 
#  *  Redistributions of source code must retain the above copyright
#     notice, this list of conditions and the following disclaimer.
# 
#  *  Redistributions in binary form must reproduce the above copyright
#     notice, this list of conditions and the following disclaimer in the
#     documentation and/or other materials provided with the distribution.
# 
#  *  Neither the name of Texas Instruments Incorporated nor the names of
#     its contributors may be used to endorse or promote products derived
#     from this software without specific prior written permission.
# 
#  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
#  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
#  THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#  PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR
#  CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
#  EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
#  PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
#  OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
#  WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
#  OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
#  EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#

#
# Default Memory Map
#
# Start Addr    Size    Description
# -------------------------------------------
# 0x80000000    36 MB   Linux
# 0x82400000     8 MB   CMEM
# 0x82C00000     3 MB   DDR2 (BIOS, Codecs, Applications)
# 0x82F00000  1020 KB   DSPLINK (MEM)
# 0x82FFF000     4 KB   DSPLINK (RESET)
# 0x83000000    16 MB   DDRALGHEAP


# insert CMEM driver
#
# Note: phys_end = (addr + 1)
#
# mem: 0x82400000 - 0x82BFFFFF (8 MB), External Memory
# pool:    80 KB, 20 x 4 KB buffers
# pool:  1280 KB, 10 x 128 KB buffers
# pool:  2048 KB, 2 x 1 MB buffers
# heap:  4784 KB, (~4.67 MB)
#
CMEM_MODPARAMS="phys_start=0x82400000 phys_end=0x82C00000 pools=20x4096,10x131072,2x1048576"

if [ -e cmemk.ko ]
    then
        insmod cmemk.ko $CMEM_MODPARAMS
    else
        modprobe cmemk $CMEM_MODPARAMS
fi

# Allow cmem driver to be used by all users
if [ -e /dev/cmem ]
    then
        chmod 666 /dev/cmem
fi

# insert DSP/BIOS Link driver
if [ -e dsplinkk.ko ]
    then
        insmod dsplinkk.ko
    else
        modprobe dsplinkk
fi

# Allow dsplink driver to be used by all users
if [ -e /dev/dsplink ]
    then
        chmod 666 /dev/dsplink
fi

# insert Local Power Manager driver
if [ -e lpm_omap2530.ko ]
    then
        insmod lpm_omap2530.ko
    else
        modprobe lpm_omap2530
fi

# Allow lpm driver to be used by all users
if [ -e /dev/lpm0 ]
    then
        chmod 666 /dev/lpm*
fi

