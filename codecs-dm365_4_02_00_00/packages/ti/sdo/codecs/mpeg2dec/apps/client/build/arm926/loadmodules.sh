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


# insert cmemk
# 20 4K buffers, 10 128K buffers  and two 1MB buffers
#insmod cmemk.ko phys_start=0x87800000 phys_end=0x88000000 pools=20x4096,10x131072,2x1q
insmod cmemk.ko phys_start=0x85000000 phys_end=0x88000000 pools=1x384,1x384,1x896,1x2688,64x4096,1x5632,2x6656,1x10240,1x13184,1x30720,1x58144,1x65792,1x91138,1x173712,1x173712,1x282624,1x2097152,1x6500000,1x13000000,1x19000000
insmod edmak.ko
insmod irqk.ko

lsmod


