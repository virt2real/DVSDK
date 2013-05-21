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

rmmod *.ko
lsmod

# insert cmemk
# 20 4K buffers, 10 128K buffers  and two 1MB buffers
#insmod cmemk.ko phys_start=0x87800000 phys_end=0x88000000 pools=20x4096,10x131072,2x1048576
#insmod cmemk.ko phys_start=0x87000000 phys_end=0x88000000 pools=1x2457600,1x1843200,1x4297168,1x100000,1x400000,1x300000,1x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x3550000
#insmod cmemk.ko phys_start=0x86500000 phys_end=0x88000000 pools=2x2457600,1x1843200,1x4297168,1x100000,1x400000,1x300000,1x100000,3x100000,1x100000,2x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x100000,1x3550000,6x180,3x38016 allowOverlap=1 phys_start_1=0x00001000 phys_end_1=0x00008000 pools_1=1x28672
#insmod cmemk.ko pools=10x4632,2x59392,2x12672,10x38016,4x518400,3x1000800,1x6291456,1x13635072,2x3932160,1x6266880 phys_start=0x85c00000 phys_end=0x88000000  allowOverlap=1 phys_start_1=0x00001000 phys_end_1=0x00008000 pools_1=1x28672
insmod cmemk.ko pools=4x4632,2x59392,2x12672,2x38016,4x518400,2x1000800,1x6291456,1x3932160,1x921600,1x3133440,1x27270144 phys_start=0x85000000 phys_end=0x88000000  allowOverlap=1 phys_start_1=0x00001000 phys_end_1=0x00008000 pools_1=1x28672
insmod edmak.ko
insmod irqk.ko

lsmod


